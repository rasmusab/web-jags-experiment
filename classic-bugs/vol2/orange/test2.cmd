model in mvotree.bug
data in mvotree-data.R
compile, nchains(2)
parameters in mvotree-inits.R
initialize
update 10000
monitor set mu, thin(10)
monitor set sigma, thin(10)
monitor set sigmaC, thin(10)
update 100000
coda *

