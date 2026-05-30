source("classic-bugs/R/discover-classic-bugs.R")
source("JAGS-4.3.2/wasm/r/jags_wasm_v8.R")

`%||%` <- function(x, y) if (is.null(x)) y else x

read_classic_bugs_data <- function(file) {
  if (is.na(file) || !nzchar(file)) {
    return(NULL)
  }
  env <- new.env(parent = baseenv())
  sys.source(file, envir = env, keep.source = FALSE)
  as.list(env, all.names = TRUE)
}

first_path <- function(paths) {
  paths <- paths[nzchar(paths)]
  if (length(paths) == 0) NA_character_ else paths[[1]]
}

split_field <- function(value) {
  if (is.na(value) || !nzchar(value)) {
    character()
  } else {
    strsplit(value, "|", fixed = TRUE)[[1]]
  }
}

scale_iterations <- function(value, scale, min_value) {
  if (is.na(value) || value <= 0) {
    return(0L)
  }
  as.integer(max(min_value, ceiling(value * scale)))
}

load_rjags_modules <- function(modules) {
  for (module in modules) {
    if (nzchar(module)) {
      rjags::load.module(module, quiet = TRUE)
    }
  }
}

run_rjags_case <- function(case, data, inits, monitors, n_adapt, burnin,
                           n_iter, thin, seed) {
  if (!requireNamespace("rjags", quietly = TRUE)) {
    stop("The rjags package is required", call. = FALSE)
  }
  if (!requireNamespace("coda", quietly = TRUE)) {
    stop("The coda package is required", call. = FALSE)
  }

  set.seed(seed)
  load_rjags_modules(split_field(case$modules))
  started <- proc.time()[["elapsed"]]
  model <- rjags::jags.model(
    file = case$model_file,
    data = data,
    inits = inits,
    n.chains = case$n_chains,
    n.adapt = n_adapt,
    quiet = TRUE
  )
  if (burnin > 0) {
    update(model, burnin, progress.bar = "none")
  }
  samples <- rjags::coda.samples(
    model,
    variable.names = monitors,
    n.iter = n_iter,
    thin = thin,
    progress.bar = "none"
  )
  elapsed <- proc.time()[["elapsed"]] - started
  matrix <- as.matrix(samples)
  summary <- data.frame(
    parameter = colnames(matrix),
    mean = colMeans(matrix, na.rm = TRUE),
    sd = apply(matrix, 2, stats::sd, na.rm = TRUE),
    n = nrow(matrix),
    row.names = NULL
  )
  list(ok = TRUE, elapsed = elapsed, summary = summary, samples = matrix)
}

run_wasm_case <- function(context, case, model_text, data, inits, monitors,
                          n_adapt, burnin, n_iter, thin, seed) {
  started <- proc.time()[["elapsed"]]
  result <- jags_wasm_run(
    context = context,
    model = model_text,
    data = data,
    inits = inits,
    monitors = monitors,
    n_chains = case$n_chains,
    n_adapt = n_adapt,
    burnin = burnin,
    n_iter = n_iter,
    thin = thin,
    seed = seed,
    allow_monitor_failures = TRUE
  )
  elapsed <- proc.time()[["elapsed"]] - started
  matrix <- jags_wasm_monitor_matrix(result, monitors)
  summary <- jags_wasm_summary(matrix)
  list(
    ok = TRUE,
    elapsed = elapsed,
    summary = summary,
    samples = matrix,
    monitor_failures = result$monitorFailures,
    iteration = result$iteration
  )
}

compare_summaries <- function(rjags_summary, wasm_summary) {
  common <- intersect(rjags_summary$parameter, wasm_summary$parameter)
  if (length(common) == 0) {
    return(list(n_common = 0L, max_abs_z = NA_real_, median_abs_z = NA_real_))
  }
  r <- rjags_summary[match(common, rjags_summary$parameter), ]
  w <- wasm_summary[match(common, wasm_summary$parameter), ]
  scale <- pmax(r$sd, 1e-12)
  z <- (w$mean - r$mean) / scale
  list(
    n_common = length(common),
    max_abs_z = max(abs(z), na.rm = TRUE),
    median_abs_z = stats::median(abs(z), na.rm = TRUE)
  )
}

compact_error <- function(error) {
  paste(strsplit(conditionMessage(error), "\n", fixed = TRUE)[[1]], collapse = " ")
}

benchmark_classic_bugs <- function(root = "classic-bugs",
                                   ids = NULL,
                                   max_cases = Inf,
                                   iter_scale = 1,
                                   min_iter = 200,
                                   seed = 1234,
                                   tolerance = 0.5,
                                   out_dir = file.path(root, "results")) {
  dir.create(out_dir, recursive = TRUE, showWarnings = FALSE)
  index <- discover_classic_bugs(root)
  index <- index[is.na(index$discovery_error), , drop = FALSE]
  if (!is.null(ids)) {
    index <- index[index$id %in% ids | index$example %in% ids, , drop = FALSE]
  }
  if (is.finite(max_cases)) {
    index <- head(index, max_cases)
  }

  context <- jags_wasm_v8_context()
  rows <- vector("list", nrow(index))

  for (i in seq_len(nrow(index))) {
    case <- index[i, ]
    cat("[", i, "/", nrow(index), "] ", case$id, "\n", sep = "")

    data_paths <- split_field(case$data_files)
    data <- read_classic_bugs_data(first_path(data_paths))
    inits <- read_classic_bugs_data(case$init_file)
    monitors <- split_field(case$monitors)
    model_text <- readLines(case$model_file, warn = FALSE)

    n_adapt <- scale_iterations(case$n_adapt, iter_scale, min_iter)
    burnin <- scale_iterations(case$burnin, iter_scale, min_iter)
    n_iter <- scale_iterations(case$n_iter, iter_scale, min_iter)

    rjags_result <- tryCatch(
      run_rjags_case(case, data, inits, monitors, n_adapt, burnin, n_iter,
                     case$thin, seed),
      error = function(error) list(ok = FALSE, error = compact_error(error))
    )
    wasm_result <- tryCatch(
      run_wasm_case(context, case, model_text, data, inits, monitors, n_adapt,
                    burnin, n_iter, case$thin, seed),
      error = function(error) list(ok = FALSE, error = compact_error(error))
    )

    comparison <- if (isTRUE(rjags_result$ok) && isTRUE(wasm_result$ok)) {
      compare_summaries(rjags_result$summary, wasm_result$summary)
    } else {
      list(n_common = 0L, max_abs_z = NA_real_, median_abs_z = NA_real_)
    }

    monitor_failures <- if (isTRUE(wasm_result$ok) &&
                            length(wasm_result$monitor_failures) > 0) {
      vapply(wasm_result$monitor_failures, function(x) {
        paste0(x$name, ": ", x$error)
      }, character(1))
    } else {
      character()
    }

    rows[[i]] <- data.frame(
      id = case$id,
      model_file = case$model_file,
      data_file = first_path(data_paths),
      init_file = case$init_file,
      modules = case$modules,
      monitors = case$monitors,
      n_chains = case$n_chains,
      n_adapt = n_adapt,
      burnin = burnin,
      n_iter = n_iter,
      thin = case$thin,
      rjags_ok = isTRUE(rjags_result$ok),
      wasm_ok = isTRUE(wasm_result$ok),
      rjags_elapsed = if (isTRUE(rjags_result$ok)) rjags_result$elapsed else NA_real_,
      wasm_elapsed = if (isTRUE(wasm_result$ok)) wasm_result$elapsed else NA_real_,
      wasm_over_rjags_elapsed = if (isTRUE(rjags_result$ok) && isTRUE(wasm_result$ok)) {
        wasm_result$elapsed / rjags_result$elapsed
      } else {
        NA_real_
      },
      n_common = comparison$n_common,
      max_abs_z = comparison$max_abs_z,
      median_abs_z = comparison$median_abs_z,
      comparable = isTRUE(comparison$n_common > 0 && comparison$max_abs_z <= tolerance),
      rjags_error = if (isTRUE(rjags_result$ok)) NA_character_ else rjags_result$error,
      wasm_error = if (isTRUE(wasm_result$ok)) NA_character_ else wasm_result$error,
      wasm_monitor_failures = paste(monitor_failures, collapse = " | "),
      stringsAsFactors = FALSE
    )

    utils::write.csv(do.call(rbind, rows[seq_len(i)]),
                     file.path(out_dir, "classic-bugs-benchmark-progress.csv"),
                     row.names = FALSE)
  }

  results <- do.call(rbind, rows)
  stamp <- format(Sys.time(), "%Y%m%d-%H%M%S")
  csv <- file.path(out_dir, paste0("classic-bugs-benchmark-", stamp, ".csv"))
  rds <- file.path(out_dir, paste0("classic-bugs-benchmark-", stamp, ".rds"))
  utils::write.csv(results, csv, row.names = FALSE)
  saveRDS(results, rds)
  attr(results, "csv") <- csv
  attr(results, "rds") <- rds
  results
}

parse_args <- function(args) {
  values <- list()
  for (arg in args) {
    if (startsWith(arg, "--")) {
      parts <- strsplit(sub("^--", "", arg), "=", fixed = TRUE)[[1]]
      key <- parts[[1]]
      value <- if (length(parts) > 1) paste(parts[-1], collapse = "=") else "TRUE"
      values[[key]] <- value
    }
  }
  values
}

if (sys.nframe() == 0) {
  args <- parse_args(commandArgs(trailingOnly = TRUE))
  root <- args$root %||% "classic-bugs"
  ids <- if (!is.null(args$ids)) strsplit(args$ids, ",", fixed = TRUE)[[1]] else NULL
  max_cases <- if (!is.null(args$max_cases)) as.numeric(args$max_cases) else Inf
  iter_scale <- if (!is.null(args$iter_scale)) as.numeric(args$iter_scale) else 1
  min_iter <- if (!is.null(args$min_iter)) as.numeric(args$min_iter) else 200
  seed <- if (!is.null(args$seed)) as.integer(args$seed) else 1234L
  tolerance <- if (!is.null(args$tolerance)) as.numeric(args$tolerance) else 0.5

  results <- benchmark_classic_bugs(
    root = root,
    ids = ids,
    max_cases = max_cases,
    iter_scale = iter_scale,
    min_iter = min_iter,
    seed = seed,
    tolerance = tolerance
  )
  print(table(rjags = results$rjags_ok, wasm = results$wasm_ok))
  cat("Comparable cases: ", sum(results$comparable, na.rm = TRUE), "\n", sep = "")
  print(results[, c("id", "rjags_ok", "wasm_ok", "rjags_elapsed",
                    "wasm_elapsed", "wasm_over_rjags_elapsed", "n_common",
                    "max_abs_z", "comparable")], row.names = FALSE)
  cat("Wrote ", attr(results, "csv"), "\n", sep = "")
}
