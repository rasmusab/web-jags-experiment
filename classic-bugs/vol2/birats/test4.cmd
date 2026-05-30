model in "birats4.bug"
data in birats-data.R
compile, nchains(2)
inits in birats-inits.R
initialize
update 1000
monitor set mu.beta, thin(10) 
monitor set sigma.beta, thin(10)
monitor set r, thin(10)
monitor set alpha0, thin(10)
update 10000 
coda *

