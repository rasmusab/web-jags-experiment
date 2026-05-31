jags_wasm_find_file <- function(relative_path) {
  current <- normalizePath(getwd(), mustWork = TRUE)
  repeat {
    candidate <- file.path(current, relative_path)
    if (file.exists(candidate)) {
      return(normalizePath(candidate, mustWork = TRUE))
    }
    parent <- dirname(current)
    if (identical(parent, current)) {
      break
    }
    current <- parent
  }
  stop("Could not locate ", relative_path, call. = FALSE)
}

jags_wasm_default_js <- function() {
  Sys.getenv("JAGS_WASM_JS", jags_wasm_find_file("dist/openblas/jags.js"))
}

jags_wasm_default_wasm <- function() {
  Sys.getenv("JAGS_WASM_WASM", jags_wasm_find_file("dist/openblas/jags.wasm"))
}

jags_wasm_v8_context <- function(js_path = jags_wasm_default_js(),
                                 wasm_path = jags_wasm_default_wasm()) {
  if (!requireNamespace("V8", quietly = TRUE)) {
    stop("The V8 R package is required", call. = FALSE)
  }
  js_path <- normalizePath(js_path, mustWork = TRUE)
  wasm_path <- normalizePath(wasm_path, mustWork = TRUE)

  ctx <- V8::v8()
  wasm_binary <- readBin(wasm_path, "raw", n = file.info(wasm_path)$size)
  ctx$assign("jagsWasmBinary", wasm_binary)
  ctx$eval("
    globalThis.window = globalThis;
    globalThis.console = console;
  ")
  ctx$source(js_path)
  ctx$eval("
    (async () => {
      globalThis.jagsModule = await createJagsModule({ wasmBinary: jagsWasmBinary });
      return true;
    })()
  ", await = TRUE)

  ctx$eval('
    (function() {
      const Module = globalThis.jagsModule;
      const api = {
        create: Module.cwrap("jags_create", "number", []),
        destroy: Module.cwrap("jags_destroy", null, ["number"]),
        lastError: Module.cwrap("jags_last_error", "string", ["number"]),
        setSeed: Module.cwrap("jags_set_seed", "number", ["number"]),
        checkModel: Module.cwrap("jags_check_model", "number", ["number", "string"]),
        clearData: Module.cwrap("jags_clear_data", "number", ["number"]),
        setDataRaw: Module.cwrap("jags_set_data", "number",
          ["number", "string", "number", "number", "number", "number"]),
        setParameterRaw: Module.cwrap("jags_set_parameter", "number",
          ["number", "number", "string", "number", "number", "number", "number"]),
        compile: Module.cwrap("jags_compile", "number", ["number", "number", "number"]),
        initialize: Module.cwrap("jags_initialize", "number", ["number"]),
        adaptOff: Module.cwrap("jags_adapt_off", "number", ["number"]),
        update: Module.cwrap("jags_update", "number", ["number", "number"]),
        setMonitor: Module.cwrap("jags_set_monitor", "number",
          ["number", "string", "number", "string"]),
        dumpMonitors: Module.cwrap("jags_dump_monitors", "string",
          ["number", "string", "number"]),
        parameterNames: Module.cwrap("jags_parameter_names", "string", ["number"]),
        iteration: Module.cwrap("jags_iteration", "number", ["number"])
      };

      function arrayify(value) {
        return Array.isArray(value) ? value : [value];
      }

      function valuesToNumbers(values) {
        return arrayify(values).map((value) => value === null ? Number.NaN : Number(value));
      }

      function setArray(handle, entry, setter) {
        const dims = arrayify(entry.dims).map((value) => Number(value));
        const values = valuesToNumbers(entry.values);
        const dimsPtr = Module._malloc(dims.length * 4);
        const valuesPtr = Module._malloc(values.length * 8);
        try {
          Module.HEAPU32.set(dims, dimsPtr / 4);
          Module.HEAPF64.set(values, valuesPtr / 8);
          return setter(handle, entry.name, dimsPtr, dims.length, valuesPtr, values.length);
        } finally {
          Module._free(valuesPtr);
          Module._free(dimsPtr);
        }
      }

      function requireOk(handle, value, step) {
        if (!value) {
          throw new Error(step + ": " + (api.lastError(handle) || "unknown error"));
        }
      }

      globalThis.jagsRunSpec = function(specJson) {
        const spec = JSON.parse(specJson);
        const handle = api.create();
        const monitorFailures = [];

        try {
          requireOk(handle, api.setSeed(Number(spec.seed || 1)), "set seed");
          requireOk(handle, api.clearData(handle), "clear data");

          for (const entry of arrayify(spec.data || [])) {
            requireOk(handle, setArray(handle, entry, api.setDataRaw), "set data " + entry.name);
          }

          requireOk(handle, api.checkModel(handle, spec.model), "check model");
          requireOk(handle, api.compile(handle, Number(spec.nChains || 1),
            spec.generateData ? 1 : 0), "compile");

          const inits = arrayify(spec.inits || []);
          for (let chainIndex = 0; chainIndex < inits.length; chainIndex += 1) {
            for (const entry of arrayify(inits[chainIndex] || [])) {
              const setter = (h, name, dimsPtr, ndim, valuesPtr, length) =>
                api.setParameterRaw(h, chainIndex + 1, name, dimsPtr, ndim, valuesPtr, length);
              requireOk(handle, setArray(handle, entry, setter),
                "set initial value " + entry.name + " chain " + (chainIndex + 1));
            }
          }

          requireOk(handle, api.initialize(handle), "initialize");

          const nAdapt = Number(spec.nAdapt || 0);
          if (nAdapt > 0) {
            requireOk(handle, api.update(handle, nAdapt), "adapt");
          }
          requireOk(handle, api.adaptOff(handle), "adapt off");

          const nBurnin = Number(spec.burnin || 0);
          if (nBurnin > 0) {
            requireOk(handle, api.update(handle, nBurnin), "burnin");
          }

          for (const name of arrayify(spec.monitorBases || [])) {
            const ok = api.setMonitor(handle, name, Number(spec.thin || 1), "trace");
            if (!ok) {
              const failure = { name: name, error: api.lastError(handle) || "unknown error" };
              if (spec.allowMonitorFailures) {
                monitorFailures.push(failure);
              } else {
                throw new Error("set monitor " + name + ": " + failure.error);
              }
            }
          }

          const nIter = Number(spec.nIter || 0);
          if (nIter > 0) {
            requireOk(handle, api.update(handle, nIter), "sample");
          }

          const raw = api.dumpMonitors(handle, "trace", 0);
          if (!raw) {
            throw new Error(api.lastError(handle) || "monitor dump failed");
          }

          return JSON.stringify({
            iteration: api.iteration(handle),
            parameterNames: JSON.parse(api.parameterNames(handle)),
            monitorFailures: monitorFailures,
            monitors: JSON.parse(raw)
          });
        } finally {
          api.destroy(handle);
        }
      };
    })();
  ')

  structure(list(ctx = ctx, js_path = js_path, wasm_path = wasm_path),
            class = "jags_wasm_v8_context")
}

jags_wasm_entry <- function(name, value) {
  if (startsWith(name, ".")) {
    return(NULL)
  }
  if (is.factor(value)) {
    value <- as.integer(value)
  }
  if (!(is.numeric(value) || is.integer(value) || is.logical(value))) {
    stop("Only numeric, integer, logical, and factor arrays are supported: ", name,
         call. = FALSE)
  }
  dims <- dim(value)
  values <- as.numeric(value)
  if (length(values) == 0) {
    return(NULL)
  }
  if (is.null(dims)) {
    dims <- if (length(values) == 1) 1L else length(values)
  }
  list(name = name, dims = as.integer(dims), values = unname(values))
}

jags_wasm_entries <- function(values) {
  if (is.null(values)) {
    return(list())
  }
  if (!is.list(values) || is.null(names(values))) {
    stop("JAGS data and inits must be named lists", call. = FALSE)
  }
  entries <- Map(jags_wasm_entry, names(values), values)
  Filter(Negate(is.null), unname(entries))
}

jags_wasm_inits_by_chain <- function(inits, n_chains) {
  if (is.null(inits)) {
    return(vector("list", n_chains))
  }
  is_chain_list <- is.list(inits) &&
    length(inits) == n_chains &&
    all(vapply(inits, function(x) is.list(x) && !is.null(names(x)), logical(1)))
  chain_values <- if (is_chain_list) inits else rep(list(inits), n_chains)
  lapply(chain_values, jags_wasm_entries)
}

jags_wasm_monitor_bases <- function(monitors) {
  unique(sub("\\[.*$", "", as.character(monitors)))
}

jags_wasm_run <- function(context,
                          model,
                          data = list(),
                          inits = NULL,
                          monitors,
                          n_chains = 1,
                          n_adapt = 1000,
                          burnin = 0,
                          n_iter = 1000,
                          thin = 1,
                          seed = 1,
                          allow_monitor_failures = TRUE,
                          generate_data = grepl("data[[:space:]]*[{]",
                                                paste(model, collapse = "\n"))) {
  if (!inherits(context, "jags_wasm_v8_context")) {
    stop("context must come from jags_wasm_v8_context()", call. = FALSE)
  }
  if (length(monitors) == 0) {
    stop("At least one monitor is required", call. = FALSE)
  }
  spec <- list(
    model = paste(model, collapse = "\n"),
    data = jags_wasm_entries(data),
    inits = jags_wasm_inits_by_chain(inits, n_chains),
    monitors = as.character(monitors),
    monitorBases = jags_wasm_monitor_bases(monitors),
    nChains = as.integer(n_chains),
    nAdapt = as.integer(n_adapt),
    burnin = as.integer(burnin),
    nIter = as.integer(n_iter),
    thin = as.integer(thin),
    seed = as.integer(seed),
    allowMonitorFailures = isTRUE(allow_monitor_failures),
    generateData = isTRUE(generate_data)
  )
  spec_json <- jsonlite::toJSON(spec, auto_unbox = TRUE, na = "null",
                                null = "null", digits = 17)
  result_json <- context$ctx$call("jagsRunSpec", as.character(spec_json))
  jsonlite::fromJSON(result_json, simplifyVector = FALSE)
}

jags_wasm_values <- function(monitor) {
  vapply(monitor$values, function(value) {
    if (is.null(value)) NA_real_ else as.numeric(value)
  }, numeric(1))
}

jags_wasm_select_monitor_names <- function(available, requested) {
  requested <- as.character(requested)
  keep <- rep(FALSE, length(available))
  for (monitor in requested) {
    if (grepl("[", monitor, fixed = TRUE)) {
      keep <- keep | available == monitor
    } else {
      keep <- keep | available == monitor | startsWith(available, paste0(monitor, "["))
    }
  }
  available[keep]
}

jags_wasm_index_names <- function(name, dims) {
  if (length(dims) == 1 && dims[[1]] == 1) {
    return(name)
  }
  grid <- expand.grid(lapply(dims, seq_len))
  paste0(name, "[", apply(grid, 1, paste, collapse = ","), "]")
}

jags_wasm_expand_monitor <- function(name, monitor) {
  dims <- as.integer(unlist(monitor$dim, use.names = FALSE))
  values <- jags_wasm_values(monitor)
  if (length(dims) < 3) {
    matrix(values, ncol = 1, dimnames = list(NULL, name))
  } else {
    parameter_dims <- dims[seq_len(length(dims) - 2)]
    n_parameter <- prod(parameter_dims)
    n_sample <- prod(utils::tail(dims, 2))
    mat <- t(matrix(values, nrow = n_parameter, ncol = n_sample))
    colnames(mat) <- jags_wasm_index_names(name, parameter_dims)
    mat
  }
}

jags_wasm_monitor_matrix <- function(result, requested = NULL) {
  monitors <- result$monitors
  if (length(monitors) == 0) {
    return(matrix(numeric(), nrow = 0, ncol = 0))
  }
  expanded <- do.call(cbind, Map(jags_wasm_expand_monitor, names(monitors), monitors))
  names_available <- colnames(expanded)
  names_selected <- if (is.null(requested)) names_available else
    jags_wasm_select_monitor_names(names_available, requested)
  if (length(names_selected) == 0) {
    return(matrix(numeric(), nrow = 0, ncol = 0))
  }
  expanded[, names_selected, drop = FALSE]
}

jags_wasm_summary <- function(matrix) {
  if (ncol(matrix) == 0) {
    return(data.frame(parameter = character(), mean = numeric(), sd = numeric(),
                      n = integer()))
  }
  data.frame(
    parameter = colnames(matrix),
    mean = colMeans(matrix, na.rm = TRUE),
    sd = apply(matrix, 2, stats::sd, na.rm = TRUE),
    n = nrow(matrix),
    row.names = NULL
  )
}
