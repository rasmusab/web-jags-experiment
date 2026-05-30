/* 
   Since the autocorrelation of node r is very strong, we set a long
   thinning interval.
*/
model in "mice.bug"
data in "mice-data.R"
compile, nchains(2)
inits in "mice-init.R"
initialize
update 10000
monitor set veh.control, thin(50)
monitor set test.sub, thin(50) 
monitor set pos.control, thin(50) 
monitor set r, thin(50) 
monitor set median, thin(50) 
update 500000
coda *
exit
