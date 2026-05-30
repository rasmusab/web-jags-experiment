model in "epil2.bug"
data in epil-data.R
load glm
compile, nchains(2)
inits in epil-inits.R
initialize
update 1000
monitor set alpha0, thin(5)
monitor set alpha.Base, thin(5)
monitor set alpha.Trt, thin(5)
monitor set alpha.BT, thin(5)
monitor set alpha.Age, thin(5)
monitor set alpha.V4, thin(5)
monitor set sigma.b1, thin(5)
update 5000
coda *
