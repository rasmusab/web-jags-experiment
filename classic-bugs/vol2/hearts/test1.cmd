model in "hearts.bug" 
data in "hearts-data.R"
compile, nchains(2)
parameters in "hearts-inits.R"
initialize
update 1000
monitor set theta
monitor set beta
monitor set p
update 10000
coda *

