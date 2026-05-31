#ifndef JAGS_WASM_CONFIG_H_
#define JAGS_WASM_CONFIG_H_

#define PACKAGE_BUGREPORT "https://sourceforge.net/projects/mcmc-jags/"
#define PACKAGE_NAME "JAGS"
#define PACKAGE_STRING "JAGS 4.3.2"
#define PACKAGE_TARNAME "JAGS"
#define PACKAGE_URL ""
#define PACKAGE_VERSION "4.3.2"

#define IEEE_754 1
#define HAVE_WORKING_ISFINITE 1

#define F77_FUNC(name,NAME) name ## _
#define F77_FUNC_(name,NAME) name ## _

#endif /* JAGS_WASM_CONFIG_H_ */
