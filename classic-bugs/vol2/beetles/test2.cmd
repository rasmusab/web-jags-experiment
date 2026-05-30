model in "beetles-probit.bug" 
data in "beetles-data.R"
compile, nchains(2)
parameters in "beetles-inits.R"
initialize
update 1000
monitor set alpha
monitor set beta
monitor set r.hat
monitor set D
update 10000
coda *

