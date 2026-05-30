model in "eyes.bug" 
data in "eyes-data.R"
load mix
compile, nchains(2)
parameters in "eyes-inits1.R"
initialize
update 5000 
monitor set P 
monitor set lambda 
monitor set sigma 
monitor set l0
update 5000 
coda *

