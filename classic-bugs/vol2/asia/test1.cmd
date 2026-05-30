model in "asia.bug"
data in asia-data.R
compile, nchains(2) 
initialize
update 10000
monitor set smoking
monitor set tuberculosis 
monitor set lung.cancer 
monitor set bronchitis 
monitor set either 
monitor set xray 
update 10000 
coda *

