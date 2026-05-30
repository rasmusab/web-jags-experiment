library(coda)
x <- read.openbugs()
benchstats <- summary(x)$statistics
dump("benchstats")
