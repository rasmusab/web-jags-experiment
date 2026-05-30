const regressionModel = `model {
  for (i in 1:N) {
    y[i] ~ dnorm(mu[i], tau)
    mu[i] <- alpha + beta * x[i]
  }

  alpha ~ dnorm(0, 1.0E-6)
  beta ~ dnorm(0, 1.0E-6)
  tau ~ dgamma(0.001, 0.001)
}`;

const tableSeed = [
  ["N", "x", "y", "", "", ""],
  [14, -2.1, 0.4, "", "", ""],
  ["", -1.7, 0.2, "", "", ""],
  ["", -1.2, 1.0, "", "", ""],
  ["", -0.8, 1.1, "", "", ""],
  ["", -0.4, 1.7, "", "", ""],
  ["", 0.1, 2.0, "", "", ""],
  ["", 0.4, 2.1, "", "", ""],
  ["", 0.8, 2.6, "", "", ""],
  ["", 1.2, 3.0, "", "", ""],
  ["", 1.6, 3.6, "", "", ""],
  ["", 2.0, 3.7, "", "", ""],
  ["", 2.4, 4.4, "", "", ""],
  ["", 2.9, 4.7, "", "", ""],
  ["", 3.3, 5.0, "", "", ""],
  ["", "", "", "", "", ""],
];

const palette = ["#0f766e", "#2f5f98", "#b13f22", "#71651f", "#6c4d8f", "#28705d"];

const state = {
  module: null,
  api: null,
  tableData: [],
};

const elements = {
  model: document.querySelector("#model-input"),
  iterations: document.querySelector("#iterations-input"),
  seed: document.querySelector("#seed-input"),
  run: document.querySelector("#run-button"),
  reset: document.querySelector("#reset-button"),
  addRow: document.querySelector("#add-row-button"),
  addColumn: document.querySelector("#add-column-button"),
  dataTable: document.querySelector("#data-table"),
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

function resetExample() {
  elements.model.value = regressionModel;
  elements.iterations.value = "1500";
  elements.seed.value = "20260505";
  setTableData(tableSeed);
}

function normalizeRows(rows, minWidth = 6, minHeight = 16) {
  const width = Math.max(minWidth, ...rows.map((row) => row.length));
  const normalized = rows.map((row) =>
    Array.from({ length: width }, (_, index) => String(row[index] ?? "")),
  );
  while (normalized.length < minHeight) {
    normalized.push(Array(width).fill(""));
  }
  return normalized;
}

function renderTable() {
  const fragment = document.createDocumentFragment();

  state.tableData.forEach((row, rowIndex) => {
    const tableRow = document.createElement("tr");
    row.forEach((value, columnIndex) => {
      const cell = document.createElement(rowIndex === 0 ? "th" : "td");
      cell.contentEditable = "true";
      cell.spellcheck = false;
      cell.dataset.row = String(rowIndex);
      cell.dataset.column = String(columnIndex);
      cell.textContent = value;
      cell.setAttribute("aria-label", `Row ${rowIndex + 1}, column ${columnIndex + 1}`);
      tableRow.append(cell);
    });
    fragment.append(tableRow);
  });

  elements.dataTable.replaceChildren(fragment);
}

function setTableData(rows) {
  state.tableData = normalizeRows(rows);
  renderTable();
}

function tableWidth() {
  return Math.max(1, ...state.tableData.map((row) => row.length));
}

function ensureTableSize(rowCount, columnCount) {
  const width = Math.max(tableWidth(), columnCount);
  while (state.tableData.length < rowCount) {
    state.tableData.push(Array(width).fill(""));
  }
  state.tableData.forEach((row) => {
    while (row.length < width) {
      row.push("");
    }
  });
}

function focusCell(row, column) {
  requestAnimationFrame(() => {
    elements.dataTable.querySelector(`[data-row="${row}"][data-column="${column}"]`)?.focus();
  });
}

function addRow() {
  state.tableData.push(Array(tableWidth()).fill(""));
  renderTable();
  focusCell(state.tableData.length - 1, 0);
}

function addColumn() {
  state.tableData.forEach((row) => row.push(""));
  renderTable();
  focusCell(0, tableWidth() - 1);
}

function moveFocus(row, column) {
  const lastRow = state.tableData.length - 1;
  const lastColumn = tableWidth() - 1;
  const nextRow = Math.max(0, Math.min(row, lastRow));
  const nextColumn = Math.max(0, Math.min(column, lastColumn));
  focusCell(nextRow, nextColumn);
}

function cleanCell(value) {
  return String(value ?? "").trim();
}

function parseNumericCell(name, value, rowNumber) {
  const text = cleanCell(value);
  if (!text) {
    return null;
  }
  const number = Number(text);
  if (!Number.isFinite(number)) {
    throw new Error(`${name} row ${rowNumber} is not numeric`);
  }
  return number;
}

function parseRaggedTable() {
  const rows = state.tableData;
  const width = Math.max(...rows.map((row) => row.length));
  const entries = [];
  const seen = new Set();

  for (let col = 0; col < width; col += 1) {
    const name = cleanCell(rows[0]?.[col]);
    if (!name) {
      continue;
    }
    if (!/^[A-Za-z.][A-Za-z0-9._]*$/.test(name)) {
      throw new Error(`Invalid variable name "${name}"`);
    }
    if (seen.has(name)) {
      throw new Error(`Duplicate variable name "${name}"`);
    }
    seen.add(name);

    const values = [];
    for (let row = 1; row < rows.length; row += 1) {
      const value = parseNumericCell(name, rows[row]?.[col], row + 1);
      if (value !== null) {
        values.push(value);
      }
    }
    if (values.length === 0) {
      continue;
    }
    entries.push({
      name,
      dims: values.length === 1 ? [1] : [values.length],
      values,
    });
  }

  if (entries.length === 0) {
    throw new Error("The data table is empty");
  }
  return entries;
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

function requireOk(handle, ok, step) {
  if (!ok) {
    throw new Error(`${step}: ${state.api.lastError(handle) || "unknown error"}`);
  }
}

function setData(handle, entry) {
  const dimsPtr = state.module._malloc(entry.dims.length * 4);
  const valuesPtr = state.module._malloc(entry.values.length * 8);
  try {
    state.module.HEAPU32.set(entry.dims, dimsPtr / 4);
    state.module.HEAPF64.set(entry.values, valuesPtr / 8);
    requireOk(
      handle,
      state.api.setData(handle, entry.name, dimsPtr, entry.dims.length, valuesPtr, entry.values.length),
      `set data ${entry.name}`,
    );
  } finally {
    state.module._free(valuesPtr);
    state.module._free(dimsPtr);
  }
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

async function runModel() {
  const dataEntries = parseRaggedTable();
  const iterations = Number.parseInt(elements.iterations.value, 10);
  const seed = Number.parseInt(elements.seed.value, 10);
  if (!Number.isInteger(iterations) || iterations <= 0) {
    throw new Error("Iterations must be a positive integer");
  }
  if (!Number.isInteger(seed) || seed <= 0) {
    throw new Error("Seed must be a positive integer");
  }

  const started = performance.now();
  const handle = state.api.create();
  try {
    requireOk(handle, state.api.setSeed(seed), "set seed");
    requireOk(handle, state.api.clearData(handle), "clear data");
    dataEntries.forEach((entry) => setData(handle, entry));
    requireOk(handle, state.api.checkModel(handle, elements.model.value), "check model");
    requireOk(handle, state.api.compile(handle, 1, 0), "compile");
    requireOk(handle, state.api.initialize(handle), "initialize");

    const parameters = JSON.parse(state.api.parameterNames(handle));
    if (parameters.length === 0) {
      throw new Error("No unobserved stochastic parameters were found to monitor");
    }
    parameters.forEach((name) => {
      requireOk(handle, state.api.setMonitor(handle, name, 1, "trace"), `set monitor ${name}`);
    });

    const batchSize = 100;
    let remaining = iterations;
    while (remaining > 0) {
      const batch = Math.min(batchSize, remaining);
      requireOk(handle, state.api.update(handle, batch), "update");
      remaining -= batch;
      setStatus(`Running ${iterations - remaining}/${iterations}`);
      await new Promise((resolve) => setTimeout(resolve, 0));
    }

    const raw = state.api.dumpMonitors(handle, "trace", 1);
    if (!raw) {
      throw new Error(state.api.lastError(handle) || "monitor dump failed");
    }
    const monitors = JSON.parse(raw);
    renderSummary(monitors);
    renderPlots(monitors);

    const first = Object.values(monitors)[0];
    elements.parameterCount.textContent = String(Object.keys(monitors).length);
    elements.sampleCount.textContent = String(first?.values?.length ?? 0);
    elements.elapsed.textContent = `${Math.round(performance.now() - started)} ms`;
    setStatus(`Complete. Monitored ${parameters.join(", ")}`);
  } finally {
    state.api.destroy(handle);
  }
}

async function initializeRuntime() {
  state.module = await createJagsModule({
    locateFile: (path) => path.endsWith(".wasm") ? `../build/${path}` : path,
  });
  state.api = {
    create: state.module.cwrap("jags_create", "number", []),
    destroy: state.module.cwrap("jags_destroy", null, ["number"]),
    lastError: state.module.cwrap("jags_last_error", "string", ["number"]),
    setSeed: state.module.cwrap("jags_set_seed", "number", ["number"]),
    checkModel: state.module.cwrap("jags_check_model", "number", ["number", "string"]),
    clearData: state.module.cwrap("jags_clear_data", "number", ["number"]),
    setData: state.module.cwrap("jags_set_data", "number", ["number", "string", "number", "number", "number", "number"]),
    compile: state.module.cwrap("jags_compile", "number", ["number", "number", "number"]),
    initialize: state.module.cwrap("jags_initialize", "number", ["number"]),
    parameterNames: state.module.cwrap("jags_parameter_names", "string", ["number"]),
    update: state.module.cwrap("jags_update", "number", ["number", "number"]),
    setMonitor: state.module.cwrap("jags_set_monitor", "number", ["number", "string", "number", "string"]),
    dumpMonitors: state.module.cwrap("jags_dump_monitors", "string", ["number", "string", "number"]),
  };
  elements.run.disabled = false;
  setStatus("Ready");
}

elements.dataTable.addEventListener("input", (event) => {
  const cell = event.target.closest("td, th");
  if (!cell) {
    return;
  }
  const row = Number(cell.dataset.row);
  const column = Number(cell.dataset.column);
  state.tableData[row][column] = cell.textContent.replace(/\n/g, " ").trim();
});

elements.dataTable.addEventListener("keydown", (event) => {
  const cell = event.target.closest("td, th");
  if (!cell) {
    return;
  }
  const row = Number(cell.dataset.row);
  const column = Number(cell.dataset.column);

  if (event.key === "Tab") {
    event.preventDefault();
    const direction = event.shiftKey ? -1 : 1;
    const nextColumn = column + direction;
    if (nextColumn < 0) {
      moveFocus(row - 1, tableWidth() - 1);
    } else if (nextColumn >= tableWidth()) {
      moveFocus(row + 1, 0);
    } else {
      moveFocus(row, nextColumn);
    }
  }

  if (event.key === "Enter") {
    event.preventDefault();
    moveFocus(row + 1, column);
  }
});

elements.dataTable.addEventListener("paste", (event) => {
  const cell = event.target.closest("td, th");
  const text = event.clipboardData?.getData("text/plain");
  if (!cell || !text || (!text.includes("\t") && !text.includes("\n"))) {
    return;
  }

  event.preventDefault();
  const startRow = Number(cell.dataset.row);
  const startColumn = Number(cell.dataset.column);
  const pastedRows = text.replace(/\r/g, "").split("\n");
  if (pastedRows[pastedRows.length - 1] === "") {
    pastedRows.pop();
  }
  const cells = pastedRows.map((row) => row.split("\t"));
  const pastedWidth = Math.max(...cells.map((row) => row.length));

  ensureTableSize(startRow + cells.length, startColumn + pastedWidth);
  cells.forEach((row, rowOffset) => {
    row.forEach((value, columnOffset) => {
      state.tableData[startRow + rowOffset][startColumn + columnOffset] = value.trim();
    });
  });
  renderTable();
  focusCell(startRow, startColumn);
});

elements.reset.addEventListener("click", resetExample);
elements.addRow.addEventListener("click", addRow);
elements.addColumn.addEventListener("click", addColumn);
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

resetExample();
initializeRuntime().catch((error) => setStatus(error.message, true));
