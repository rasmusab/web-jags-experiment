classic_bugs_ref <- function(path) {
  structure(list(path = path), class = "classic_bugs_ref")
}

classic_bugs_ref_path <- function(value) {
  if (inherits(value, "classic_bugs_ref")) {
    return(value$path)
  }
  NA_character_
}

classic_bugs_capture_test <- function(test_file) {
  test_file <- normalizePath(test_file, mustWork = TRUE)
  test_dir <- dirname(test_file)
  capture <- new.env(parent = emptyenv())
  capture$model_file <- NA_character_
  capture$data_files <- character()
  capture$init_file <- NA_character_
  capture$modules <- character()
  capture$n_chains <- NA_integer_
  capture$n_adapt <- 1000L
  capture$burnin <- 0L
  capture$n_iter <- NA_integer_
  capture$thin <- 1L
  capture$monitors <- character()

  env <- new.env(parent = baseenv())
  env$read.jagsdata <- function(file) {
    path <- normalizePath(file.path(test_dir, file), mustWork = FALSE)
    classic_bugs_ref(path)
  }
  env$read.data <- env$read.jagsdata
  env$load.module <- function(name, ...) {
    capture$modules <- unique(c(capture$modules, as.character(name)))
    invisible(TRUE)
  }
  env$jags.model <- function(file, data = NULL, inits = NULL, n.chains = 1,
                             n.adapt = 1000, ...) {
    capture$model_file <- normalizePath(file.path(test_dir, file), mustWork = FALSE)
    data_path <- classic_bugs_ref_path(data)
    if (!is.na(data_path)) {
      capture$data_files <- unique(c(capture$data_files, data_path))
    }
    init_path <- classic_bugs_ref_path(inits)
    if (!is.na(init_path)) {
      capture$init_file <- init_path
    }
    capture$n_chains <- as.integer(n.chains)
    capture$n_adapt <- as.integer(n.adapt)
    structure(list(), class = "classic_bugs_model_stub")
  }
  env$update <- function(object, n.iter, ...) {
    if (inherits(object, "classic_bugs_model_stub")) {
      capture$burnin <- capture$burnin + as.integer(n.iter)
    }
    invisible(object)
  }
  env$coda.samples <- function(model, variable.names, n.iter, thin = 1, ...) {
    capture$monitors <- as.character(variable.names)
    capture$n_iter <- as.integer(n.iter)
    capture$thin <- as.integer(thin)
    structure(list(), class = "classic_bugs_coda_stub")
  }
  env$check.fun <- function(...) invisible(TRUE)
  env$source <- function(file, ...) {
    basename_file <- basename(file)
    path <- normalizePath(file.path(test_dir, file), mustWork = FALSE)
    if (grepl("data", basename_file, ignore.case = TRUE) &&
        !grepl("^bench", basename_file)) {
      capture$data_files <- unique(c(capture$data_files, path))
    }
    invisible(TRUE)
  }

  tryCatch(
    sys.source(test_file, envir = env, keep.source = FALSE),
    error = function(error) {
      capture$error <- conditionMessage(error)
    }
  )

  parts <- strsplit(test_file, .Platform$file.sep, fixed = TRUE)[[1]]
  volume <- parts[match(TRUE, parts %in% c("vol1", "vol2"))]
  example <- basename(dirname(test_file))
  test_name <- tools::file_path_sans_ext(basename(test_file))

  data.frame(
    id = paste(volume, example, test_name, sep = "/"),
    volume = volume,
    example = example,
    test = test_name,
    test_file = test_file,
    model_file = capture$model_file,
    data_files = paste(capture$data_files, collapse = "|"),
    init_file = capture$init_file,
    modules = paste(capture$modules, collapse = "|"),
    n_chains = capture$n_chains,
    n_adapt = capture$n_adapt,
    burnin = capture$burnin,
    n_iter = capture$n_iter,
    thin = capture$thin,
    monitors = paste(capture$monitors, collapse = "|"),
    discovery_error = if (exists("error", capture, inherits = FALSE)) capture$error else NA_character_,
    stringsAsFactors = FALSE
  )
}

discover_classic_bugs <- function(root = "classic-bugs") {
  root <- normalizePath(root, mustWork = TRUE)
  test_files <- list.files(root, pattern = "^test[0-9]+[.]R$", recursive = TRUE,
                           full.names = TRUE)
  rows <- lapply(sort(test_files), classic_bugs_capture_test)
  do.call(rbind, rows)
}

if (sys.nframe() == 0) {
  args <- commandArgs(trailingOnly = TRUE)
  root <- if (length(args) >= 1) args[[1]] else "classic-bugs"
  out <- if (length(args) >= 2) args[[2]] else file.path(root, "results", "classic-bugs-index.csv")
  dir.create(dirname(out), recursive = TRUE, showWarnings = FALSE)
  index <- discover_classic_bugs(root)
  utils::write.csv(index, out, row.names = FALSE)
  print(table(index$volume, useNA = "ifany"))
  cat("Wrote ", normalizePath(out, mustWork = FALSE), "\n", sep = "")
}
