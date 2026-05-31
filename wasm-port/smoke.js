const path = require("path");

const modulePath = process.env.JAGS_WASM_MODULE ||
  path.join(__dirname, "..", "dist", "openblas", "jags.js");

const createJagsModule = require(modulePath);

function main() {
  return createJagsModule().then((Module) => {
    const create = Module.cwrap("jags_create", "number", []);
    const destroy = Module.cwrap("jags_destroy", null, ["number"]);
    const lastError = Module.cwrap("jags_last_error", "string", ["number"]);
    const setSeed = Module.cwrap("jags_set_seed", "number", ["number"]);
    const checkModel = Module.cwrap("jags_check_model", "number", ["number", "string"]);
    const clearData = Module.cwrap("jags_clear_data", "number", ["number"]);
    const setDataRaw = Module.cwrap("jags_set_data", "number",
      ["number", "string", "number", "number", "number", "number"]);
    const compile = Module.cwrap("jags_compile", "number", ["number", "number", "number"]);
    const initialize = Module.cwrap("jags_initialize", "number", ["number"]);
    const parameterNames = Module.cwrap("jags_parameter_names", "string", ["number"]);
    const update = Module.cwrap("jags_update", "number", ["number", "number"]);
    const setMonitor = Module.cwrap("jags_set_monitor", "number",
      ["number", "string", "number", "string"]);
    const dumpMonitors = Module.cwrap("jags_dump_monitors", "string",
      ["number", "string", "number"]);
    const iteration = Module.cwrap("jags_iteration", "number", ["number"]);

    const handle = create();

    function requireOk(value, step) {
      if (!value) {
        throw new Error(`${step}: ${lastError(handle)}`);
      }
    }

    function setData(name, dims, values) {
      const dimsPtr = Module._malloc(dims.length * 4);
      const valuesPtr = Module._malloc(values.length * 8);
      try {
        Module.HEAPU32.set(dims, dimsPtr / 4);
        Module.HEAPF64.set(values, valuesPtr / 8);
        requireOk(setDataRaw(handle, name, dimsPtr, dims.length, valuesPtr, values.length),
          `set data ${name}`);
      }
      finally {
        Module._free(valuesPtr);
        Module._free(dimsPtr);
      }
    }

    try {
      setSeed(1234);
      requireOk(clearData(handle), "clear data");
      setData("N", [1], [5]);
      setData("y", [5], [1.1, 0.9, 1.0, 1.2, 0.8]);

      const model = `
        model {
          for (i in 1:N) {
            y[i] ~ dnorm(mu, tau)
          }
          mu ~ dnorm(0, 1.0E-6)
          tau ~ dgamma(0.001, 0.001)
        }
      `;

      requireOk(checkModel(handle, model), "check model");
      requireOk(compile(handle, 1, 0), "compile");
      requireOk(initialize(handle), "initialize");
      const parameters = JSON.parse(parameterNames(handle));
      if (!parameters.includes("mu") || !parameters.includes("tau")) {
        throw new Error(`unexpected parameter names: ${parameters.join(", ")}`);
      }
      requireOk(setMonitor(handle, "mu", 1, "trace"), "set monitor");
      requireOk(update(handle, 100), "update");

      const monitors = JSON.parse(dumpMonitors(handle, "trace", 1));
      if (!monitors.mu || monitors.mu.values.length === 0) {
        throw new Error("missing mu monitor output");
      }

      console.log(JSON.stringify({
        iteration: iteration(handle),
        mu_samples: monitors.mu.values.length,
        mu_first: monitors.mu.values[0],
      }));
    }
    finally {
      destroy(handle);
    }
  });
}

main().catch((error) => {
  console.error(error.stack || error.message);
  process.exit(1);
});
