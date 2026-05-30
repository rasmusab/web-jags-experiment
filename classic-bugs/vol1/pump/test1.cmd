model in "pump.bug"
data in "pump-data.R"
compile, nchains(2)
inits in "pump-init.R"
initialize
update 1000 
monitor set theta
monitor set alpha
monitor set beta
update 5000
coda *
