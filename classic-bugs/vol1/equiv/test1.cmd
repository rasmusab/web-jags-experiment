model in equiv.bug
data in equiv-data.R
compile, nchains(2) 
inits in equiv-init.R
initialize
update 1000
monitor set theta
monitor set equivalence
monitor set sigma
update 10000 
coda *
