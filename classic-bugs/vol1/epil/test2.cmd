model in epil3.bug
data in epil-data.R
load glm
compile, nchains(2)
inits in epil-inits.R
initialize
update 1000 
monitor set alpha0, thin(10)
monitor set alpha.Base, thin(10)
monitor set alpha.Trt, thin(10)
monitor set alpha.BT, thin(10)
monitor set alpha.Age, thin(10)
monitor set alpha.V4, thin(10)
monitor set sigma.b1, thin(10)
monitor set sigma.b, thin(10)
update 10000
coda *
