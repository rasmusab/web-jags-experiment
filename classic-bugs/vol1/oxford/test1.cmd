/* Due to very high autocorrelation for sigma, we set a very long thinning
   interval
*/
model in "oxford.bug"
data in "oxford-data.R"
load glm
compile, nchains(2)
inits in "oxford-init.R"
initialize
update 1000
monitor set alpha, thin(10)
monitor set beta1, thin(10)
monitor set beta2, thin(10)
monitor set sigma, thin(10)
update 20000
coda *
