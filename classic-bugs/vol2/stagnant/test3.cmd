model in "stagnant2.bug"
data in "stagnant-data.R"
compile, nchains(2)
parameters in "stagnant-inits3.R"
initialize
update 1000
monitor set alpha, thin(10)
monitor set x.change, thin(10)
update 100000
coda *

