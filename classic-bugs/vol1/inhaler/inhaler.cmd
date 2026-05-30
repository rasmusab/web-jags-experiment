model in inhaler.bug
data in inhaler-data.R
compile, nchains(2)
parameters in inhaler-inits.R
initialize
update 1000
monitor set a, thin(10)
monitor set beta, thin(10)
monitor set kappa, thin(10)
monitor set log.sigma, thin(10)
monitor set pi, thin(10)
monitor set sigma, thin(10)
update 10000
coda *
