/* Trivial linear regression model
*/
model in line.bug
data in line-data.R
compile, nchains(2)
inits in line-inits.R
initialize
update 1000
monitor set alpha
monitor set beta
monitor set sigma 
monitor set tau 
update 10000 
coda *
