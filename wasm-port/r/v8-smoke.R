source("wasm-port/r/jags_wasm_v8.R")

context <- jags_wasm_v8_context()

model <- "
model {
  for (i in 1:N) {
    y[i] ~ dnorm(mu, tau)
  }
  mu ~ dnorm(0, 1.0E-6)
  tau ~ dgamma(0.001, 0.001)
}
"

data <- list(
  N = 5,
  y = c(1.1, 0.9, 1.0, 1.2, 0.8)
)

result <- jags_wasm_run(
  context = context,
  model = model,
  data = data,
  monitors = c("mu", "tau"),
  n_chains = 1,
  n_adapt = 0,
  burnin = 0,
  n_iter = 100,
  thin = 1,
  seed = 1234
)

samples <- jags_wasm_monitor_matrix(result, c("mu", "tau"))
summary <- jags_wasm_summary(samples)

print(list(
  iteration = result$iteration,
  samples = nrow(samples),
  summary = summary
))
