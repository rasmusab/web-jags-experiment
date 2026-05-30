model in "jaw-constant.bug"
data in "jaw-data.R" 
compile, nchains(2)
parameters in "jaw-inits.R"
initialize
load dic
update 1000
monitor set beta0
monitor set mu
monitor set Sigma2
monitor set RSS
monitor set deviance
update 10000
coda *

