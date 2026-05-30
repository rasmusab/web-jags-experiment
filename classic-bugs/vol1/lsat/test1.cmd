model in lsat.bug
data in lsat-data.R
load glm
compile, nchains(2)
inits in lsat-init.R
initialize
update 1000 
monitor set alpha 
monitor set beta 
update 2000 
coda *
