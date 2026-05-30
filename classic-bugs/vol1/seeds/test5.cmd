/* SEEDS example with uniform prior on the standard deviation of the
   random effects. The results should be identical to test4, although
   the parameterization of the model is different.
*/
model in "seedspar.bug" 
data in "seeds-data.R"
load glm
compile, nchains(2)
inits in "seeds-init.R"
initialize
update 5000 
monitor set alpha0 , thin(10)
monitor set alpha1 , thin(10)
monitor set alpha2 , thin(10)
monitor set alpha12 , thin(10)
monitor set sigma , thin(10)
update 10000 
coda *

