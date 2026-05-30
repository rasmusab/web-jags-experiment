model in "equiv.bug"
data in "equivmiss-data.R"
compile, nchains(2) 
inits in "equiv-init.R"
initialize
update 1000
monitor set theta
monitor set equivalence
monitor set sigma
monitor set Y[1,1]
monitor set Y[3,2]
monitor set Y[6,2]
update 10000 
coda *
