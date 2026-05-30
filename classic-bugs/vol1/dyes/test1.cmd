model in dyes.bug
data in dyes-data.R
compile, nchains(2)
parameters in dyes-init.R
initialize
update 5000 
monitor set theta, thin(50)
monitor set sigma2.within, thin(50)
monitor set sigma2.between, thin(50)
monitor set f.between, thin(50)
update 100000 
coda *
