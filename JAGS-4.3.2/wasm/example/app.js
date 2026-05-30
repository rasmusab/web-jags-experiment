const regressionModel = `model {
  for (i in 1:N) {
    y[i] ~ dnorm(mu[i], tau)
    mu[i] <- alpha + beta * x[i]
  }

  alpha ~ dnorm(0, 1.0E-6)
  beta ~ dnorm(0, 1.0E-6)
  tau ~ dgamma(0.001, 0.001)
  sigma <- 1 / sqrt(tau)
}`;

const regressionData = {
  N: 14,
  x: [-2.1, -1.7, -1.2, -0.8, -0.4, 0.1, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.9, 3.3],
  y: [0.4, 0.2, 1.0, 1.1, 1.7, 2.0, 2.1, 2.6, 3.0, 3.6, 3.7, 4.4, 4.7, 5.0],
};

const colors = ["#1f7a68", "#b5471b", "#38598b", "#7b6f2d", "#6d4c86"];

const state = {
  module: null,
  api: null,
};

const elements = {
  model: document.querySelector("#model-input"),
  data: document.querySelector("#data-input"),
  iterations: document.querySelector("#iterations-input"),
  seed: document.querySelector("#seed-input"),
  monitors: document.querySelector("#monitors-input"),
  run: document.querySelector("#run-button"),
  reset: document.querySelector("#reset-example"),
  status: document.querySelector("#status"),
  iteration: document.querySelector("#iteration-value"),
  sample: document.querySelector("#sample-value"),
  elapsed: document.querySelector("#elapsed-value"),
  summary: document.querySelector("#summary-table"),
  regressionPlot: document.querySelector("#regression-plot"),
  traceGrid: document.querySelector("#trace-grid"),
  histGrid: document.querySelector("#hist-grid"),
};

function setStatus(text, isError = false) {
  elements.status.textContent = text;
  elements.status.classList.toggle("error", isError);
}

function resetExample() {
  elements.model.value = regressionModel;
  elements.data.value = JSON.stringify(regressionData, null, 2);
  elements.iterations.value = "1500";
  elements.seed.value = "20260505";
  elements.monitors.value = "alpha, beta, sigma";
}

function quantile(values, p) {
  if (values.length === 0) {
    return NaN;
  }
  const sorted = [...values].sort((a, b) => a - b);
  const index = (sorted.length - 1) * p;
  const lower = Math.floor(index);
  const upper = Math.ceil(index);
  if (lower === upper) {
    return sorted[lower];
  }
  return sorted[lower] + (sorted[upper] - sorted[lower]) * (index - lower);
}

function mean(values) {
  return values.reduce((total, value) => total + value, 0) / values.length;
}

function sd(values) {
  if (values.length < 2) {
    return 0;
  }
  const avg = mean(values);
  const variance = values.reduce((total, value) => total + (value - avg) ** 2, 0) /
    (values.length - 1);
  return Math.sqrt(variance);
}

function formatNumber(value) {
  if (!Number.isFinite(value)) {
    return "";
  }
  return Math.abs(value) >= 1000 || Math.abs(value) < 0.001
    ? value.toExponential(3)
    : value.toFixed(4);
}

function normalizeDataValue(name, value) {
  if (typeof value === "number") {
    return { dims: [1], values: [value] };
  }
  if (Array.isArray(value)) {
    return { dims: [value.length], values: value };
  }
  if (value && Array.isArray(value.values)) {
    const dims = Array.isArray(value.dims) ? value.dims : [value.values.length];
    return { dims, values: value.values };
  }
  throw new Error(`Invalid data entry for ${name}`);
}

function parseData() {
  const raw = JSON.parse(elements.data.value);
  return Object.entries(raw).map(([name, value]) => {
    const normalized = normalizeDataValue(name, value);
    if (normalized.dims.some((dim) => !Number.isInteger(dim) || dim <= 0)) {
      throw new Error(`${name} has invalid dimensions`);
    }
    if (normalized.values.some((value) => !Number.isFinite(value))) {
      throw new Error(`${name} contains a non-finite value`);
    }
    const expected = normalized.dims.reduce((product, dim) => product * dim, 1);
    if (expected !== normalized.values.length) {
      throw new Error(`${name} length does not match dimensions`);
    }
    return { name, ...normalized };
  });
}

function parseMonitors() {
  return elements.monitors.value
    .split(",")
    .map((name) => name.trim())
    .filter(Boolean);
}

function requireOk(handle, ok, step) {
  if (!ok) {
    throw new Error(`${step}: ${state.api.lastError(handle) || "unknown error"}`);
  }
}

function setData(handle, item) {
  const dimsPtr = state.module._malloc(item.dims.length * 4);
  const valuesPtr = state.module._malloc(item.values.length * 8);
  try {
    state.module.HEAPU32.set(item.dims, dimsPtr / 4);
    state.module.HEAPF64.set(item.values, valuesPtr / 8);
    requireOk(
      handle,
      state.api.setData(handle, item.name, dimsPtr, item.dims.length, valuesPtr, item.values.length),
      `set data ${item.name}`,
    );
  } finally {
    state.module._free(valuesPtr);
    state.module._free(dimsPtr);
  }
}

function plotLayout(title, extra = {}) {
  return {
    title: { text: title, font: { size: 15 } },
    margin: { l: 48, r: 22, t: 46, b: 42 },
    paper_bgcolor: "rgba(255,255,255,0)",
    plot_bgcolor: "#ffffff",
    font: { family: "Avenir Next, Segoe UI, sans-serif", color: "#17191c" },
    xaxis: { zeroline: false, gridcolor: "#ebe5d9" },
    yaxis: { zeroline: false, gridcolor: "#ebe5d9" },
    ...extra,
  };
}

function renderSummary(monitors) {
  const rows = Object.entries(monitors).map(([name, array]) => {
    const values = array.values.filter(Number.isFinite);
    return `
      <tr>
        <td>${name}</td>
        <td>${formatNumber(mean(values))}</td>
        <td>${formatNumber(sd(values))}</td>
        <td>${formatNumber(quantile(values, 0.025))}</td>
        <td>${formatNumber(quantile(values, 0.5))}</td>
        <td>${formatNumber(quantile(values, 0.975))}</td>
      </tr>
    `;
  }).join("");

  elements.summary.innerHTML = `
    <table>
      <thead>
        <tr>
          <th>Node</th>
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

function renderMonitorPlots(monitors) {
  elements.traceGrid.innerHTML = "";
  elements.histGrid.innerHTML = "";

  Object.entries(monitors).forEach(([name, array], index) => {
    const values = array.values.filter(Number.isFinite);
    const color = colors[index % colors.length];

    const traceNode = document.createElement("div");
    traceNode.className = "plot";
    elements.traceGrid.append(traceNode);
    Plotly.react(traceNode, [{
      y: values,
      mode: "lines",
      type: "scatter",
      line: { color, width: 1.4 },
      hovertemplate: `${name}: %{y:.4f}<extra></extra>`,
    }], plotLayout(`${name} trace`), { responsive: true, displayModeBar: false });

    const histNode = document.createElement("div");
    histNode.className = "plot";
    elements.histGrid.append(histNode);
    Plotly.react(histNode, [{
      x: values,
      type: "histogram",
      histnorm: "probability density",
      marker: { color, opacity: 0.72 },
      hovertemplate: `${name}: %{x:.4f}<extra></extra>`,
    }], plotLayout(`${name} posterior`), { responsive: true, displayModeBar: false });
  });
}

function renderRegression(monitors, dataEntries) {
  const data = Object.fromEntries(dataEntries.map((item) => [item.name, item]));
  const alpha = monitors.alpha?.values?.filter(Number.isFinite);
  const beta = monitors.beta?.values?.filter(Number.isFinite);
  const x = data.x?.values;
  const y = data.y?.values;

  if (!alpha?.length || !beta?.length || !x?.length || !y?.length) {
    Plotly.react(elements.regressionPlot, [], plotLayout("Regression fit"), {
      responsive: true,
      displayModeBar: false,
    });
    return;
  }

  const xmin = Math.min(...x);
  const xmax = Math.max(...x);
  const grid = Array.from({ length: 80 }, (_, i) => xmin + (xmax - xmin) * i / 79);
  const count = Math.min(alpha.length, beta.length);
  const fit = grid.map((gx) => {
    const predictions = Array.from({ length: count }, (_, i) => alpha[i] + beta[i] * gx);
    return {
      mean: mean(predictions),
      lower: quantile(predictions, 0.025),
      upper: quantile(predictions, 0.975),
    };
  });

  const traces = [
    {
      x,
      y,
      type: "scatter",
      mode: "markers",
      name: "data",
      marker: { size: 8, color: "#17191c" },
    },
    {
      x: grid,
      y: fit.map((item) => item.upper),
      type: "scatter",
      mode: "lines",
      name: "97.5%",
      line: { width: 0, color: "rgba(31,122,104,0)" },
      hoverinfo: "skip",
    },
    {
      x: grid,
      y: fit.map((item) => item.lower),
      type: "scatter",
      mode: "lines",
      name: "95% interval",
      fill: "tonexty",
      fillcolor: "rgba(31,122,104,0.18)",
      line: { width: 0, color: "rgba(31,122,104,0)" },
      hoverinfo: "skip",
    },
    {
      x: grid,
      y: fit.map((item) => item.mean),
      type: "scatter",
      mode: "lines",
      name: "posterior mean",
      line: { color: "#1f7a68", width: 3 },
      hovertemplate: "fit: %{y:.4f}<extra></extra>",
    },
  ];

  Plotly.react(elements.regressionPlot, traces, plotLayout("Regression fit", {
    xaxis: { title: "x", zeroline: false, gridcolor: "#ebe5d9" },
    yaxis: { title: "y", zeroline: false, gridcolor: "#ebe5d9" },
    showlegend: true,
    legend: { orientation: "h", y: 1.12 },
  }), { responsive: true, displayModeBar: false });
}

async function runModel() {
  const dataEntries = parseData();
  const monitors = parseMonitors();
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
    dataEntries.forEach((item) => setData(handle, item));
    requireOk(handle, state.api.checkModel(handle, elements.model.value), "check model");
    requireOk(handle, state.api.compile(handle, 1, 0), "compile");
    requireOk(handle, state.api.initialize(handle), "initialize");
    monitors.forEach((name) => {
      requireOk(handle, state.api.setMonitor(handle, name, 1, "trace"), `set monitor ${name}`);
    });

    const batchSize = 100;
    let remaining = iterations;
    while (remaining > 0) {
      const batch = Math.min(batchSize, remaining);
      requireOk(handle, state.api.update(handle, batch), "update");
      remaining -= batch;
      setStatus(`Running... ${iterations - remaining}/${iterations}`);
      await new Promise((resolve) => setTimeout(resolve, 0));
    }

    const raw = state.api.dumpMonitors(handle, "trace", 1);
    if (!raw) {
      throw new Error(state.api.lastError(handle) || "monitor dump failed");
    }
    const monitorData = JSON.parse(raw);
    renderSummary(monitorData);
    renderRegression(monitorData, dataEntries);
    renderMonitorPlots(monitorData);

    const firstMonitor = Object.values(monitorData)[0];
    elements.iteration.textContent = String(state.api.iteration(handle));
    elements.sample.textContent = String(firstMonitor?.values?.length ?? 0);
    elements.elapsed.textContent = `${Math.round(performance.now() - started)} ms`;
    setStatus("Complete");
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
    update: state.module.cwrap("jags_update", "number", ["number", "number"]),
    setMonitor: state.module.cwrap("jags_set_monitor", "number", ["number", "string", "number", "string"]),
    dumpMonitors: state.module.cwrap("jags_dump_monitors", "string", ["number", "string", "number"]),
    iteration: state.module.cwrap("jags_iteration", "number", ["number"]),
  };
  elements.run.disabled = false;
  setStatus("Ready");
}

elements.reset.addEventListener("click", resetExample);
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
initializeRuntime().catch((error) => {
  setStatus(error.message, true);
});
