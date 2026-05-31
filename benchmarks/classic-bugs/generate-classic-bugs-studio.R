#!/usr/bin/env Rscript

args <- commandArgs(trailingOnly = TRUE)
repo_root <- if (length(args) >= 1) normalizePath(args[[1]], mustWork = TRUE) else getwd()
bugs_root <- file.path(repo_root, "classic-bugs")
out_dir <- file.path(repo_root, "demos", "bugs-studio")
out_file <- file.path(out_dir, "classic-bugs-examples.js")
seed <- 1234L
studio_min_adapt <- 1000L
studio_min_burnin <- 5000L
studio_min_samples <- 5000L

if (!requireNamespace("jsonlite", quietly = TRUE)) {
  stop("The jsonlite R package is required", call. = FALSE)
}
if (!requireNamespace("rjags", quietly = TRUE)) {
  stop("The rjags R package is required", call. = FALSE)
}
if (!requireNamespace("coda", quietly = TRUE)) {
  stop("The coda R package is required", call. = FALSE)
}

split_field <- function(value) {
  if (is.na(value) || !nzchar(value)) {
    character()
  } else {
    strsplit(value, "|", fixed = TRUE)[[1]]
  }
}

first_path <- function(paths) {
  paths <- paths[nzchar(paths)]
  if (length(paths) == 0) NA_character_ else paths[[1]]
}

repo_path <- function(file) {
  if (is.na(file) || !nzchar(file)) {
    return(file)
  }
  if (grepl("^(/|[A-Za-z]:)", file)) {
    return(file)
  }
  file.path(repo_root, file)
}

read_values_file <- function(file) {
  if (is.na(file) || !nzchar(file)) {
    return(NULL)
  }
  env <- new.env(parent = baseenv())
  sys.source(file, envir = env, keep.source = FALSE)
  as.list(env, all.names = TRUE)
}

entry_value <- function(value) {
  if (is.factor(value)) {
    value <- as.integer(value)
  }
  if (!(is.numeric(value) || is.integer(value) || is.logical(value))) {
    return(NULL)
  }
  dims <- dim(value)
  values <- as.numeric(value)
  if (length(values) == 0) {
    return(NULL)
  }
  if (is.null(dims) && length(values) == 1) {
    if (is.na(values[[1]])) NULL else values[[1]]
  } else {
    list(
      dims = as.integer(if (is.null(dims)) length(values) else dims),
      values = unname(values)
    )
  }
}

json_values <- function(values) {
  if (is.null(values)) {
    return(setNames(list(), character()))
  }
  entries <- list()
  for (name in names(values)) {
    if (startsWith(name, ".")) {
      next
    }
    converted <- entry_value(values[[name]])
    if (!is.null(converted)) {
      entries[[name]] <- converted
    }
  }
  if (length(entries) == 0) {
    return(setNames(list(), character()))
  }
  entries
}

latest_benchmark_csv <- function(results_dir) {
  files <- list.files(
    results_dir,
    pattern = "^classic-bugs-benchmark-[0-9]{8}-[0-9]{6}[.]csv$",
    full.names = TRUE
  )
  if (length(files) == 0) {
    stop("No benchmark CSV files found in ", results_dir, call. = FALSE)
  }
  files[[length(sort(files))]]
}

load_modules <- function(modules) {
  for (module in split_field(modules)) {
    if (nzchar(module)) {
      rjags::load.module(module, quiet = TRUE)
    }
  }
}

reference_summary <- function(row, data, inits, monitors) {
  load_modules(row$modules)
  set.seed(seed)
  model <- rjags::jags.model(
    file = row$model_file,
    data = data,
    inits = inits,
    n.chains = row$n_chains,
    n.adapt = row$n_adapt,
    quiet = TRUE
  )
  if (row$burnin > 0) {
    update(model, row$burnin, progress.bar = "none")
  }
  samples <- rjags::coda.samples(
    model,
    variable.names = monitors,
    n.iter = row$n_iter,
    thin = row$thin,
    progress.bar = "none"
  )
  matrix <- as.matrix(samples)
  quantiles <- t(apply(matrix, 2, stats::quantile, probs = c(0.025, 0.5, 0.975),
                       na.rm = TRUE))
  data.frame(
    parameter = colnames(matrix),
    mean = colMeans(matrix, na.rm = TRUE),
    sd = apply(matrix, 2, stats::sd, na.rm = TRUE),
    q2.5 = quantiles[, 1],
    q50 = quantiles[, 2],
    q97.5 = quantiles[, 3],
    n = nrow(matrix),
    row.names = NULL,
    check.names = FALSE
  )
}

format_number <- function(value) {
  if (!is.finite(value)) {
    return("NA")
  }
  formatC(value, digits = 5, format = "fg", flag = "#")
}

reference_comments <- function(summary, row) {
  header <- c(
    "",
    sprintf(
      "# rjags reference summary (seed=%d; chains=%d; n.adapt=%d; burnin=%d; n.iter=%d; thin=%d)",
      seed, row$n_chains, row$n_adapt, row$burnin, row$n_iter, row$thin
    ),
    "# parameter                         mean          sd        q2.5         q50       q97.5    n"
  )
  body <- vapply(seq_len(nrow(summary)), function(index) {
    item <- summary[index, ]
    sprintf(
      "# %-28s %11s %11s %11s %11s %11s %5d",
      item$parameter,
      format_number(item$mean),
      format_number(item$sd),
      format_number(item$q2.5),
      format_number(item$q50),
      format_number(item$q97.5),
      item$n
    )
  }, character(1))
  paste(c(header, body), collapse = "\n")
}

benchmark_file <- file.path(repo_root, "benchmarks", "classic-bugs",
                            "classic-bugs-benchmark.csv")
if (!file.exists(benchmark_file)) {
  benchmark_file <- latest_benchmark_csv(file.path(bugs_root, "results"))
}
benchmark <- utils::read.csv(benchmark_file, stringsAsFactors = FALSE)
benchmark <- benchmark[benchmark$rjags_ok & benchmark$wasm_ok, , drop = FALSE]
benchmark <- benchmark[order(benchmark$id), , drop = FALSE]

examples <- vector("list", nrow(benchmark))
for (i in seq_len(nrow(benchmark))) {
  row <- benchmark[i, ]
  row$model_file <- repo_path(row$model_file)
  row$data_file <- repo_path(row$data_file)
  row$init_file <- repo_path(row$init_file)
  row$n_adapt <- max(as.integer(row$n_adapt), studio_min_adapt, na.rm = TRUE)
  row$burnin <- max(as.integer(row$burnin), studio_min_burnin, na.rm = TRUE)
  row$n_iter <- max(as.integer(row$n_iter), studio_min_samples, na.rm = TRUE)
  cat("[", i, "/", nrow(benchmark), "] ", row$id, "\n", sep = "")
  data <- read_values_file(row$data_file)
  inits <- read_values_file(row$init_file)
  monitors <- split_field(row$monitors)
  model_text <- paste(readLines(row$model_file, warn = FALSE), collapse = "\n")

  reference <- tryCatch(
    reference_summary(row, data, inits, monitors),
    error = function(error) {
      data.frame(
        parameter = "reference unavailable",
        mean = NA_real_,
        sd = NA_real_,
        q2.5 = NA_real_,
        q50 = NA_real_,
        q97.5 = NA_real_,
        n = 0L,
        error = conditionMessage(error),
        check.names = FALSE
      )
    }
  )
  comments <- if ("error" %in% names(reference)) {
    paste0("\n# rjags reference summary unavailable: ", reference$error[[1]])
  } else {
    reference_comments(reference, row)
  }

  examples[[i]] <- list(
    id = row$id,
    label = paste(row$id, basename(row$model_file), sep = " - "),
    model = paste0(model_text, "\n", comments),
    data = json_values(data),
    inits = json_values(inits),
    nChains = row$n_chains,
    nAdapt = row$n_adapt,
    burnin = row$burnin,
    nIter = row$n_iter,
    thin = row$thin
  )
}

dir.create(out_dir, recursive = TRUE, showWarnings = FALSE)
json <- jsonlite::toJSON(examples, auto_unbox = TRUE, null = "null", na = "null",
                         digits = NA, pretty = TRUE)
writeLines(c(
  "// Generated by benchmarks/classic-bugs/generate-classic-bugs-studio.R.",
  "// Source: classic-bugs plus benchmarks/classic-bugs/classic-bugs-benchmark.csv.",
  paste0("window.CLASSIC_BUGS_EXAMPLES = ", json, ";")
), out_file)
cat("Wrote ", normalizePath(out_file, mustWork = FALSE), "\n", sep = "")
