library(coda)
source("bench.R")
x <- read.openbugs()
checkstats <- summary(x)$statistics
if (is.matrix(benchstats)) {
  rnb <- order(rownames(benchstats))
  rnc <- order(rownames(checkstats))
  z <- (benchstats[rnb,1] - checkstats[rnc,1])
  z <- ifelse(z==0, 0, z/benchstats[rnb,2])
} else {
  z <- (benchstats[1] - checkstats[1])
  z <- ifelse(z==0, 0, z/benchstats[2])
}
print(z)
if (any(abs(z) > 0.15)) {
  stop("FAIL")
} else {
  cat("OK\n")
}
