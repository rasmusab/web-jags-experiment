model in "dugongs.bug"
data in "dugongs-data.R"
compile, nchains(2)
parameters in "dugongs-inits.R"
initialize
update 1000
monitor set U3 
monitor set alpha 
monitor set beta 
monitor set gamma 
monitor set sigma 
update 10000 
coda *

