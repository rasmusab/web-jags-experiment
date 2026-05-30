model in "salm-pareto.bug"
data in "salm-data.R"
load glm
compile, nchains(2)
inits in "salm-init.R"
initialize
update 1000 
monitor set alpha
monitor set beta
monitor set gamma
monitor set sigma
load dic
monitor set deviance
update 5000
coda *
