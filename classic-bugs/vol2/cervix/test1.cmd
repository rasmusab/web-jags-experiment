load glm
model in "cervix.bug" 
data in "cervix-data.R"
compile, nchains(2) 
parameters in "cervix-inits.R"
initialize
update 1000
monitor set beta0C, thin(10) 
monitor set beta, thin(10) 
monitor set phi, thin(10) 
monitor set gamma1, thin(10) 
monitor set gamma2, thin(10) 
update 10000
coda *

