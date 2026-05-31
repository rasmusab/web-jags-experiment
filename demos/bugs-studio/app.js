const palette = ["#0f766e", "#2f5f98", "#b13f22", "#71651f", "#6c4d8f", "#28705d"];
const maxMonitoredSeries = 30;

const runtimeOptions = {
  openblas: {
    label: "OpenBLAS",
    baseUrl: "../../dist/openblas",
    fileScriptUrl: "../../dist/openblas/jags-file.js",
  },
};

const examples = Array.isArray(window.CLASSIC_BUGS_EXAMPLES) ? window.CLASSIC_BUGS_EXAMPLES : [];

const state = {
  module: null,
  api: null,
  runtime: null,
};

const elements = {
  example: document.querySelector("#example-select"),
  model: document.querySelector("#model-input"),
  data: document.querySelector("#data-input"),
  inits: document.querySelector("#inits-input"),
  chains: document.querySelector("#chains-input"),
  adapt: document.querySelector("#adapt-input"),
  burnin: document.querySelector("#burnin-input"),
  iterations: document.querySelector("#iterations-input"),
  thin: document.querySelector("#thin-input"),
  seed: document.querySelector("#seed-input"),
  run: document.querySelector("#run-button"),
  reset: document.querySelector("#reset-button"),
  status: document.querySelector("#status"),
  parameterCount: document.querySelector("#parameter-count"),
  sampleCount: document.querySelector("#sample-count"),
  elapsed: document.querySelector("#elapsed-time"),
  summary: document.querySelector("#summary-table"),
  plots: document.querySelector("#plots"),
};

function setStatus(message, isError = false) {
  elements.status.textContent = message;
  elements.status.classList.toggle("error", isError);
}

function arrayify(value) {
  if (value === undefined || value === null) {
    return [];
  }
  return Array.isArray(value) ? value : [value];
}

function uniqueValues(values) {
  return [...new Set(values.filter((value) => typeof value === "string" && value.length > 0))];
}

function monitorBaseName(name) {
  return String(name).replace(/\[.*$/, "");
}

function stripComments(text) {
  return text
    .split("\n")
    .map((line) => line.replace(/#.*/, ""))
    .join("\n");
}

function splitTopLevelCommas(text) {
  const entries = [];
  let depth = 0;
  let start = 0;
  for (let index = 0; index < text.length; index += 1) {
    const char = text[index];
    if (char === "[") {
      depth += 1;
    } else if (char === "]") {
      depth = Math.max(0, depth - 1);
    } else if (char === "," && depth === 0) {
      entries.push(text.slice(start, index).trim());
      start = index + 1;
    }
  }
  entries.push(text.slice(start).trim());
  return entries.filter(Boolean);
}

function runtimeCandidates() {
  const params = new URLSearchParams(window.location.search);
  const requested = params.get("runtime");
  if (requested) {
    const key = requested.toLowerCase();
    if (runtimeOptions[key]) {
      return [runtimeOptions[key]];
    }
    const baseUrl = requested.replace(/\/$/, "");
    return [{ label: requested, baseUrl, fileScriptUrl: `${baseUrl}/jags-file.js` }];
  }
  return [runtimeOptions.openblas];
}

function isFilePage() {
  return window.location.protocol === "file:";
}

function loadRuntimeScript(scriptUrl) {
  return new Promise((resolve, reject) => {
    globalThis.__jagsRuntimeFactory = undefined;
    const script = document.createElement("script");
    script.async = true;
    script.src = scriptUrl;
    script.onload = () => {
      if (typeof globalThis.__jagsRuntimeFactory !== "function") {
        reject(new Error(`${scriptUrl} did not define a JAGS runtime factory`));
        return;
      }
      resolve(globalThis.__jagsRuntimeFactory);
    };
    script.onerror = () => reject(new Error(`Could not load ${scriptUrl}`));
    document.head.append(script);
  });
}

async function loadRuntimeSource(scriptUrl) {
  const response = await fetch(scriptUrl);
  if (!response.ok) {
    throw new Error(`Could not load ${scriptUrl}: ${response.status}`);
  }
  const source = await response.text();
  const script = document.createElement("script");
  globalThis.__jagsRuntimeFactory = undefined;
  script.text = `
globalThis.__jagsRuntimeFactory = (() => {
${source}
return createJagsModule;
})();
//# sourceURL=${new URL(scriptUrl, window.location.href).href}
`;
  document.head.append(script);
  if (typeof globalThis.__jagsRuntimeFactory !== "function") {
    throw new Error(`${scriptUrl} did not define createJagsModule`);
  }
  return globalThis.__jagsRuntimeFactory;
}

function loadRuntimeFactory(candidate) {
  if (isFilePage()) {
    return loadRuntimeScript(candidate.fileScriptUrl);
  }
  return loadRuntimeSource(`${candidate.baseUrl}/jags.js`);
}

async function createRuntimeModule() {
  const errors = [];
  for (const candidate of runtimeCandidates()) {
    try {
      setStatus(`Loading JAGS runtime (${candidate.label})...`);
      const createModule = await loadRuntimeFactory(candidate);
      const module = await createModule({
        locateFile: (path) => path.endsWith(".wasm") ? `${candidate.baseUrl}/${path}` : path,
      });
      state.runtime = candidate;
      return module;
    } catch (error) {
      errors.push(`${candidate.label}: ${error.message}`);
    }
  }
  throw new Error(`Could not load a JAGS runtime. ${errors.join(" | ")}`);
}

function selectedExample() {
  return examples.find((example) => example.id === elements.example.value) || examples[0] || null;
}

function populateExamples() {
  elements.example.replaceChildren(...examples.map((example) => {
    const option = document.createElement("option");
    option.value = example.id;
    option.textContent = example.label || example.id;
    return option;
  }));
}

function clearResults() {
  elements.parameterCount.textContent = "0";
  elements.sampleCount.textContent = "0";
  elements.elapsed.textContent = "0 ms";
  elements.summary.innerHTML = "";
  elements.plots.innerHTML = "";
}

function declarationEntries(model) {
  const match = stripComments(model).match(/\bvar\b([\s\S]*?);/);
  if (!match) {
    return [];
  }
  return splitTopLevelCommas(match[1]).map((entry) => {
    const normalized = entry.replace(/\s+/g, " ");
    const parsed = normalized.match(/^([A-Za-z.][A-Za-z0-9._]*)(?:\s*\[([^\]]*)\])?/);
    if (!parsed || parsed[1].startsWith(".")) {
      return null;
    }
    return {
      name: parsed[1],
      dimensions: parsed[2] ? splitTopLevelCommas(parsed[2]) : [],
    };
  }).filter(Boolean);
}

function matchingBraceIndex(text, openIndex) {
  let depth = 0;
  for (let index = openIndex; index < text.length; index += 1) {
    if (text[index] === "{") {
      depth += 1;
    } else if (text[index] === "}") {
      depth -= 1;
      if (depth === 0) {
        return index;
      }
    }
  }
  return -1;
}

function inferIndexedAssignmentsInSegment(segment, loopBounds, entries) {
  const assignmentPattern = /([A-Za-z.][A-Za-z0-9._]*)\s*\[([^\]]+)\]\s*(?:<-|~)/g;
  let assignment = assignmentPattern.exec(segment);
  while (assignment) {
    const dimensions = splitTopLevelCommas(assignment[2]).map((index) => {
      const trimmed = index.trim();
      if (!trimmed) {
        return null;
      }
      return loopBounds.get(trimmed) || (/^\d+$/.test(trimmed) ? trimmed : null);
    });
    if (dimensions.length > 0 && dimensions.every((dimension) => dimension !== null)) {
      const name = assignment[1];
      const existing = entries.get(name);
      if (!existing || dimensions.length > existing.dimensions.length) {
        entries.set(name, { name, dimensions });
      }
    }
    assignment = assignmentPattern.exec(segment);
  }
}

function inferIndexedEntries(model) {
  const stripped = stripComments(model);
  const entries = new Map();

  function walk(start, end, loopBounds) {
    const loopPattern = /for\s*\(\s*([A-Za-z.][A-Za-z0-9._]*)\s+in\s+1\s*:\s*([A-Za-z.][A-Za-z0-9._]*|\d+)\s*\)\s*\{/g;
    loopPattern.lastIndex = start;
    let cursor = start;
    let loop = loopPattern.exec(stripped);

    while (loop && loop.index < end) {
      inferIndexedAssignmentsInSegment(stripped.slice(cursor, loop.index), loopBounds, entries);
      const openIndex = loopPattern.lastIndex - 1;
      const closeIndex = matchingBraceIndex(stripped, openIndex);
      if (closeIndex < 0 || closeIndex > end) {
        break;
      }

      const nestedBounds = new Map(loopBounds);
      nestedBounds.set(loop[1], loop[2]);
      walk(openIndex + 1, closeIndex, nestedBounds);
      cursor = closeIndex + 1;
      loopPattern.lastIndex = cursor;
      loop = loopPattern.exec(stripped);
    }

    inferIndexedAssignmentsInSegment(stripped.slice(cursor, end), loopBounds, entries);
  }

  walk(0, stripped.length, new Map());
  return [...entries.values()];
}

function dataBlockAssignedNames(model) {
  const match = stripComments(model).match(/\bdata\s*\{([\s\S]*?)\}\s*model\b/);
  if (!match) {
    return [];
  }
  const names = [];
  const assignmentPattern = /([A-Za-z.][A-Za-z0-9._]*)(?:\s*\[[^\]]*\])?\s*<-/g;
  let assignment = assignmentPattern.exec(match[1]);
  while (assignment) {
    names.push(assignment[1]);
    assignment = assignmentPattern.exec(match[1]);
  }
  return names;
}

function modelAssignedNames(model) {
  const stripped = stripComments(model);
  const names = [];
  const assignmentPattern = /([A-Za-z.][A-Za-z0-9._]*)(?:\s*\[[^\]]*\])?\s*(?:<-|~)/g;
  let assignment = assignmentPattern.exec(stripped);
  while (assignment) {
    names.push(assignment[1]);
    assignment = assignmentPattern.exec(stripped);
  }
  return new Set(names);
}

function dataScalarMap(dataEntries) {
  const scalars = new Map();
  for (const entry of dataEntries) {
    if (entry.values.length === 1 && Number.isFinite(entry.values[0])) {
      scalars.set(entry.name, entry.values[0]);
    }
  }
  return scalars;
}

function evaluateDimensionExpression(expression, scalars) {
  const substituted = expression.replace(/\b[A-Za-z.][A-Za-z0-9._]*\b/g, (name) =>
    scalars.has(name) ? String(scalars.get(name)) : "NaN",
  );
  if (!/^[0-9eE+\-*/().\sNa]+$/.test(substituted)) {
    return null;
  }
  try {
    const value = Function(`"use strict"; return (${substituted});`)();
    return Number.isInteger(value) && value > 0 ? value : null;
  } catch (_error) {
    return null;
  }
}

function declarationSize(entry, scalars) {
  if (!entry) {
    return null;
  }
  if (entry.dimensions.length === 0) {
    return 1;
  }
  const sizes = entry.dimensions.map((dimension) => evaluateDimensionExpression(dimension, scalars));
  if (sizes.some((size) => size === null)) {
    return null;
  }
  return sizes.reduce((product, size) => product * size, 1);
}

function selectMonitorCandidates(candidates) {
  const selected = [];
  const skipped = [];
  const seen = new Set();
  let estimatedSeries = 0;

  for (const candidate of candidates) {
    if (seen.has(candidate.name)) {
      continue;
    }
    seen.add(candidate.name);

    const size = candidate.size ?? 1;
    const skipReason = size > maxMonitoredSeries
      ? `estimated ${size} series`
      : estimatedSeries + size > maxMonitoredSeries
        ? `would exceed ${maxMonitoredSeries} displayed series`
        : "";
    if (skipReason) {
      skipped.push({ name: candidate.name, reason: skipReason });
      continue;
    }
    selected.push(candidate.name);
    estimatedSeries += size;
  }

  return { selected, skipped, estimatedSeries };
}

function monitorCandidates(model, parameters, dataEntries) {
  const dataNames = new Set(dataEntries.map((entry) => entry.name));
  dataBlockAssignedNames(model).forEach((name) => dataNames.add(name));
  const assignedNames = modelAssignedNames(model);
  const scalars = dataScalarMap(dataEntries);
  const declarations = declarationEntries(model);
  const declarationByName = new Map(declarations.map((entry) => [entry.name, entry]));
  const inferredByName = new Map(inferIndexedEntries(model).map((entry) => [entry.name, entry]));
  const declaredMonitors = declarations
    .map((entry) => ({
      name: monitorBaseName(entry.name),
      size: declarationSize(entry, scalars),
      source: "declaration",
    }))
    .filter((candidate) =>
      assignedNames.has(candidate.name) && !dataNames.has(candidate.name) && candidate.size !== null,
    );
  const stochasticParameters = arrayify(parameters)
    .map(monitorBaseName)
    .filter((name) => !dataNames.has(name))
    .map((name) => ({
      name,
      size: declarationSize(declarationByName.get(name), scalars) ??
        declarationSize(inferredByName.get(name), scalars) ??
        1,
      source: "parameter",
    }));
  return selectMonitorCandidates([...declaredMonitors, ...stochasticParameters]);
}

function setMonitors(handle, candidates, thin) {
  const failures = [];
  const active = [];
  for (const name of candidates) {
    const ok = state.api.setMonitor(handle, name, thin, "trace");
    if (ok) {
      active.push(name);
    } else {
      failures.push({ name, error: state.api.lastError(handle) || "unknown error" });
    }
  }
  if (active.length === 0) {
    const details = failures.map((failure) => `${failure.name}: ${failure.error}`).join(" | ");
    throw new Error(`No monitors could be set${details ? `. ${details}` : ""}`);
  }
  return { active, failures };
}

function product(values) {
  return values.reduce((total, value) => total * value, 1);
}

function parameterIndexLabel(index, dims) {
  if (dims.length === 0) {
    return "";
  }
  const subscripts = [];
  let cursor = index;
  for (const dim of dims) {
    subscripts.push((cursor % dim) + 1);
    cursor = Math.floor(cursor / dim);
  }
  return `[${subscripts.join(",")}]`;
}

function expandMonitorSeries(monitors, nChains) {
  const expanded = {};
  for (const [name, array] of Object.entries(monitors)) {
    const dims = Array.isArray(array.dim) ? array.dim : [];
    const values = Array.isArray(array.values) ? array.values : [];
    const sampleRank = dims.length >= 2 && dims[dims.length - 1] === nChains ? 2 : 1;
    const parameterDims = dims.slice(0, Math.max(0, dims.length - sampleRank));
    const parameterSize = Math.max(1, product(parameterDims));
    const sampleSize = parameterSize > 0 ? Math.floor(values.length / parameterSize) : 0;

    for (let parameterIndex = 0; parameterIndex < parameterSize; parameterIndex += 1) {
      const series = [];
      for (let sampleIndex = 0; sampleIndex < sampleSize; sampleIndex += 1) {
        series.push(values[parameterIndex + sampleIndex * parameterSize]);
      }
      expanded[`${name}${parameterIndexLabel(parameterIndex, parameterDims)}`] = {
        dim: [sampleSize],
        values: series,
      };
    }
  }
  return expanded;
}

function limitMonitors(monitors, nChains) {
  const entries = Object.entries(expandMonitorSeries(monitors, nChains));
  return {
    data: Object.fromEntries(entries.slice(0, maxMonitoredSeries)),
    total: entries.length,
    displayed: Math.min(entries.length, maxMonitoredSeries),
  };
}

function formatJsonValue(value, level = 0) {
  const indent = "  ".repeat(level);
  const childIndent = "  ".repeat(level + 1);
  if (value === null || typeof value !== "object") {
    return JSON.stringify(value);
  }
  if (Array.isArray(value)) {
    return `[${value.map((item) => formatJsonValue(item, 0)).join(", ")}]`;
  }
  const entries = Object.entries(value);
  if (entries.length === 0) {
    return "{}";
  }
  const body = entries.map(([key, item]) =>
    `${childIndent}${JSON.stringify(key)}: ${formatJsonValue(item, level + 1)}`,
  ).join(",\n");
  return `{\n${body}\n${indent}}`;
}

function applyExample() {
  const example = selectedExample();
  if (!example) {
    setStatus("No classic BUGS examples were loaded", true);
    return;
  }
  elements.model.value = example.model;
  elements.data.value = formatJsonValue(example.data);
  elements.inits.value = formatJsonValue(example.inits && !Array.isArray(example.inits) ? example.inits : {});
  elements.chains.value = String(example.nChains ?? 2);
  elements.adapt.value = String(example.nAdapt ?? 1000);
  elements.burnin.value = String(example.burnin ?? 5000);
  elements.iterations.value = String(example.nIter ?? 5000);
  elements.thin.value = String(example.thin ?? 1);
  clearResults();
}

function ensureIntegerInput(element, label, minimum) {
  const value = Number.parseInt(element.value, 10);
  if (!Number.isInteger(value) || value < minimum) {
    throw new Error(`${label} must be an integer >= ${minimum}`);
  }
  return value;
}

function numberValue(value, label) {
  if (value === null || (typeof value === "number" && Number.isNaN(value))) {
    return Number.NaN;
  }
  const number = Number(value);
  if (!Number.isFinite(number)) {
    throw new Error(`${label} must be numeric or null`);
  }
  return number;
}

function nestedArrayDims(value) {
  const dims = [];
  let cursor = value;
  while (Array.isArray(cursor)) {
    dims.push(cursor.length);
    cursor = cursor[0];
  }
  return dims;
}

function flattenArray(value, dims, label, depth = 0) {
  if (depth === dims.length) {
    return [numberValue(value, label)];
  }
  if (!Array.isArray(value) || value.length !== dims[depth]) {
    throw new Error(`${label} is not a rectangular array`);
  }
  return value.flatMap((item) => flattenArray(item, dims, label, depth + 1));
}

function normalizeDataValue(name, value) {
  if (value === null || typeof value === "number") {
    return { name, dims: [1], values: [numberValue(value, name)] };
  }
  if (Array.isArray(value)) {
    const dims = nestedArrayDims(value);
    if (dims.length === 0 || dims.some((dim) => dim <= 0)) {
      throw new Error(`${name} must not be an empty array`);
    }
    return { name, dims, values: flattenArray(value, dims, name) };
  }
  if (value && value.dims !== undefined && value.values !== undefined) {
    const dims = (Array.isArray(value.dims) ? value.dims : [value.dims]).map((dim) => {
      const number = Number(dim);
      if (!Number.isInteger(number) || number <= 0) {
        throw new Error(`${name} has invalid dimensions`);
      }
      return number;
    });
    const rawValues = Array.isArray(value.values) ? value.values : [value.values];
    const values = rawValues.map((item) => numberValue(item, name));
    const expected = dims.reduce((product, dim) => product * dim, 1);
    if (expected !== values.length) {
      throw new Error(`${name} length does not match dimensions`);
    }
    return { name, dims, values };
  }
  throw new Error(`${name} must be a number, array, null, or { dims, values } object`);
}

function parseData() {
  const raw = JSON.parse(elements.data.value);
  if (!raw || Array.isArray(raw) || typeof raw !== "object") {
    throw new Error("Data JSON must be an object keyed by variable name");
  }
  return Object.entries(raw).map(([name, value]) => normalizeDataValue(name, value));
}

function parseInits() {
  const raw = JSON.parse(elements.inits.value || "{}");
  if (!raw || Array.isArray(raw) || typeof raw !== "object") {
    throw new Error("Initial Values JSON must be an object keyed by parameter name");
  }
  return Object.entries(raw).map(([name, value]) => normalizeDataValue(name, value));
}

function requireOk(handle, ok, step) {
  if (!ok) {
    throw new Error(`${step}: ${state.api.lastError(handle) || "unknown error"}`);
  }
}

function setArray(handle, item, apply) {
  const dims = Array.isArray(item.dims) ? item.dims : [item.dims];
  const values = Array.isArray(item.values) ? item.values : [item.values];
  const dimsPtr = state.module._malloc(dims.length * 4);
  const valuesPtr = state.module._malloc(values.length * 8);
  try {
    state.module.HEAPU32.set(dims, dimsPtr / 4);
    state.module.HEAPF64.set(values.map((value) => numberValue(value, item.name)), valuesPtr / 8);
    return apply(dimsPtr, dims.length, valuesPtr, values.length);
  } finally {
    state.module._free(valuesPtr);
    state.module._free(dimsPtr);
  }
}

function setData(handle, item) {
  requireOk(
    handle,
    setArray(handle, item, (dimsPtr, ndim, valuesPtr, length) =>
      state.api.setData(handle, item.name, dimsPtr, ndim, valuesPtr, length),
    ),
    `set data ${item.name}`,
  );
}

function setInitialValues(handle, entries, nChains) {
  if (entries.length === 0) {
    return;
  }
  for (let chain = 1; chain <= nChains; chain += 1) {
    for (const item of entries) {
      requireOk(
        handle,
        setArray(handle, item, (dimsPtr, ndim, valuesPtr, length) =>
          state.api.setParameter(handle, chain, item.name, dimsPtr, ndim, valuesPtr, length),
        ),
        `set initial value ${item.name} chain ${chain}`,
      );
    }
  }
}

function mean(values) {
  return values.reduce((total, value) => total + value, 0) / values.length;
}

function sd(values) {
  if (values.length < 2) {
    return 0;
  }
  const avg = mean(values);
  return Math.sqrt(values.reduce((total, value) => total + (value - avg) ** 2, 0) /
    (values.length - 1));
}

function quantile(values, probability) {
  if (values.length === 0) {
    return NaN;
  }
  const sorted = [...values].sort((a, b) => a - b);
  const index = (sorted.length - 1) * probability;
  const lower = Math.floor(index);
  const upper = Math.ceil(index);
  if (lower === upper) {
    return sorted[lower];
  }
  return sorted[lower] + (sorted[upper] - sorted[lower]) * (index - lower);
}

function format(value) {
  if (!Number.isFinite(value)) {
    return "";
  }
  return Math.abs(value) >= 1000 || Math.abs(value) < 0.001
    ? value.toExponential(3)
    : value.toFixed(4);
}

function renderSummary(monitors) {
  const rows = Object.entries(monitors).map(([name, array]) => {
    const values = array.values.filter(Number.isFinite);
    return `
      <tr>
        <td>${name}</td>
        <td>${format(mean(values))}</td>
        <td>${format(sd(values))}</td>
        <td>${format(quantile(values, 0.025))}</td>
        <td>${format(quantile(values, 0.5))}</td>
        <td>${format(quantile(values, 0.975))}</td>
      </tr>
    `;
  }).join("");

  elements.summary.innerHTML = `
    <table>
      <thead>
        <tr>
          <th>Parameter</th>
          <th>Mean</th>
          <th>SD</th>
          <th>2.5%</th>
          <th>Median</th>
          <th>97.5%</th>
        </tr>
      </thead>
      <tbody>${rows}</tbody>
    </table>
  `;
}

function layout(title) {
  return {
    title: { text: title, font: { size: 15 } },
    margin: { l: 46, r: 18, t: 44, b: 42 },
    paper_bgcolor: "rgba(255,255,255,0)",
    plot_bgcolor: "#ffffff",
    font: { family: "Avenir Next, Segoe UI, sans-serif", color: "#151719" },
    xaxis: { zeroline: false, gridcolor: "#e7eee9" },
    yaxis: { zeroline: false, gridcolor: "#e7eee9" },
  };
}

function renderPlots(monitors) {
  if (!window.Plotly) {
    throw new Error("Plotly failed to load. Check network access to cdn.plot.ly.");
  }

  elements.plots.innerHTML = "";
  Object.entries(monitors).forEach(([name, array], index) => {
    const values = array.values.filter(Number.isFinite);
    const color = palette[index % palette.length];
    const card = document.createElement("section");
    card.className = "parameter-card";
    const trace = document.createElement("div");
    const hist = document.createElement("div");
    trace.className = "chart";
    hist.className = "chart";
    card.append(trace, hist);
    elements.plots.append(card);

    Plotly.react(trace, [{
      y: values,
      type: "scatter",
      mode: "lines",
      line: { color, width: 1.3 },
      hovertemplate: `${name}: %{y:.4f}<extra></extra>`,
    }], layout(`${name} trace`), { responsive: true, displayModeBar: false });

    Plotly.react(hist, [{
      x: values,
      type: "histogram",
      histnorm: "probability density",
      marker: { color, opacity: 0.76 },
      hovertemplate: `${name}: %{x:.4f}<extra></extra>`,
    }], layout(`${name} posterior`), { responsive: true, displayModeBar: false });
  });
}

function hasDataBlock(model) {
  return /\bdata\s*\{/.test(model);
}

function modelTextForRun() {
  const marker = elements.model.value.search(/\n\s*# rjags reference summary/);
  return marker >= 0 ? elements.model.value.slice(0, marker) : elements.model.value;
}

async function runModel() {
  const dataEntries = parseData();
  const initEntries = parseInits();
  const nChains = ensureIntegerInput(elements.chains, "Chains", 1);
  const nAdapt = ensureIntegerInput(elements.adapt, "Adapt", 0);
  const burnin = ensureIntegerInput(elements.burnin, "Burn-in", 0);
  const iterations = ensureIntegerInput(elements.iterations, "Samples", 1);
  const thin = ensureIntegerInput(elements.thin, "Thin", 1);
  const seed = ensureIntegerInput(elements.seed, "Seed", 1);
  const modelText = modelTextForRun();
  const started = performance.now();
  const handle = state.api.create();

  try {
    requireOk(handle, state.api.setSeed(seed), "set seed");
    requireOk(handle, state.api.clearData(handle), "clear data");
    dataEntries.forEach((entry) => setData(handle, entry));
    requireOk(handle, state.api.checkModel(handle, modelText), "check model");
    requireOk(handle, state.api.compile(handle, nChains, hasDataBlock(modelText) ? 1 : 0), "compile");
    setInitialValues(handle, initEntries, nChains);
    requireOk(handle, state.api.initialize(handle), "initialize");

    const parameters = JSON.parse(state.api.parameterNames(handle));

    if (nAdapt > 0) {
      requireOk(handle, state.api.update(handle, nAdapt), "adapt");
    }
    requireOk(handle, state.api.adaptOff(handle), "adapt off");
    if (burnin > 0) {
      requireOk(handle, state.api.update(handle, burnin), "burn-in");
    }

    const monitorSelection = monitorCandidates(modelText, parameters, dataEntries);
    const monitorSetup = setMonitors(handle, monitorSelection.selected, thin);

    const batchSize = 100;
    let remaining = iterations;
    while (remaining > 0) {
      const batch = Math.min(batchSize, remaining);
      requireOk(handle, state.api.update(handle, batch), "sample");
      remaining -= batch;
      setStatus(`Running ${iterations - remaining}/${iterations}`);
      await new Promise((resolve) => setTimeout(resolve, 0));
    }

    const raw = state.api.dumpMonitors(handle, "trace", 1);
    if (!raw) {
      throw new Error(state.api.lastError(handle) || "monitor dump failed");
    }
    const monitors = limitMonitors(JSON.parse(raw), nChains);
    renderSummary(monitors.data);
    renderPlots(monitors.data);

    const first = Object.values(monitors.data)[0];
    elements.parameterCount.textContent = monitors.total > monitors.displayed
      ? `${monitors.displayed}/${monitors.total}`
      : String(monitors.displayed);
    elements.sampleCount.textContent = String(first?.values?.length ?? 0);
    elements.elapsed.textContent = `${Math.round(performance.now() - started)} ms`;
    const truncated = monitors.total > monitors.displayed
      ? ` Showing first ${monitors.displayed} of ${monitors.total}.`
      : "";
    const failed = monitorSetup.failures.length > 0
      ? ` ${monitorSetup.failures.length} requested monitor(s) failed.`
      : "";
    const skipped = monitorSelection.skipped.length > 0
      ? ` Skipped ${monitorSelection.skipped.length} oversized/over-cap monitor(s).`
      : "";
    setStatus(`Complete. Monitored ${monitors.total} parameter series.${truncated}${failed}${skipped}`);
  } finally {
    state.api.destroy(handle);
  }
}

async function initializeRuntime() {
  state.module = await createRuntimeModule();
  state.api = {
    create: state.module.cwrap("jags_create", "number", []),
    destroy: state.module.cwrap("jags_destroy", null, ["number"]),
    lastError: state.module.cwrap("jags_last_error", "string", ["number"]),
    setSeed: state.module.cwrap("jags_set_seed", "number", ["number"]),
    checkModel: state.module.cwrap("jags_check_model", "number", ["number", "string"]),
    clearData: state.module.cwrap("jags_clear_data", "number", ["number"]),
    setData: state.module.cwrap("jags_set_data", "number", ["number", "string", "number", "number", "number", "number"]),
    setParameter: state.module.cwrap("jags_set_parameter", "number", ["number", "number", "string", "number", "number", "number", "number"]),
    compile: state.module.cwrap("jags_compile", "number", ["number", "number", "number"]),
    initialize: state.module.cwrap("jags_initialize", "number", ["number"]),
    adaptOff: state.module.cwrap("jags_adapt_off", "number", ["number"]),
    update: state.module.cwrap("jags_update", "number", ["number", "number"]),
    parameterNames: state.module.cwrap("jags_parameter_names", "string", ["number"]),
    setMonitor: state.module.cwrap("jags_set_monitor", "number", ["number", "string", "number", "string"]),
    dumpMonitors: state.module.cwrap("jags_dump_monitors", "string", ["number", "string", "number"]),
  };
  elements.run.disabled = examples.length === 0;
  setStatus(`Ready (${state.runtime.label})`);
}

elements.example.addEventListener("change", applyExample);
elements.reset.addEventListener("click", applyExample);
elements.run.addEventListener("click", async () => {
  elements.run.disabled = true;
  setStatus("Starting...");
  await new Promise((resolve) => requestAnimationFrame(resolve));
  try {
    await runModel();
  } catch (error) {
    setStatus(error.message, true);
  } finally {
    elements.run.disabled = false;
  }
});

populateExamples();
applyExample();
initializeRuntime().catch((error) => setStatus(error.message, true));
