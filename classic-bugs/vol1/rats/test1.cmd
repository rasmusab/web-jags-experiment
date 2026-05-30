model in "rats.bug"
data in "rats-data.R"
compile, nchains(2)
inits in "rats-init.R"
initialize
update 1000 
monitor set alpha0 
monitor set beta.c 
update 10000
coda *
