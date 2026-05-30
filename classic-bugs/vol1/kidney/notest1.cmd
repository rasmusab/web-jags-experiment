model in "kidney.bug"
data in "kidney-data.R"
compile, nchains(2)
inits in "kidney-init.R"
initialize
update 10000
monitor set alpha, thin(50)
monitor set beta.age, thin(50)
monitor set beta.sex, thin(50)
monitor set beta.disease[2], thin(50) 
monitor set beta.disease[3], thin(50) 
monitor set beta.disease[4], thin(50) 
monitor set r, thin(50) 
monitor set sigma, thin(50) 
update 50000 
coda *
