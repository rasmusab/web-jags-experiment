model in blocker.bug
data in blocker-data.R
load glm
compile, nchains(2)
parameters in blocker-init.R
initialize
update 3000
monitor set d, thin(10)
monitor set delta.new, thin(10)
monitor set sigma, thin(10)
update 30000 
coda *
