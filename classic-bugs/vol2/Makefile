JAGS ?= /usr/local/bin/jags
TIME = /usr/bin/time
EXAMPLES ?= asia biops eyes stagnant pigs \
         alli beetles birats dugongs hearts jaw orange schools 

all:

bench:
	@echo "Creating new benchmark results"
	@for d in $(EXAMPLES); do \
	    (echo $${d}; \
	    cd $${d}; \
	    for cmdfile in `ls test*.cmd`; do \
	       echo "Running " $${cmdfile}; \
	       ($(JAGS) $${cmdfile} && \
	       R --vanilla --quiet < ../../R/bench.R && \
	       mv dumpdata.R bench-$${cmdfile%%.cmd}.R;) || exit 1; \
	    done;) || exit 1;\
	done;

check: clean
	@echo "Checking output against benchmark results"
	@for d in $(EXAMPLES); do \
	   (cd $${d} && \
	    for cmdfile in `ls test*.cmd`; do \
	      (cp bench-$${cmdfile%%.cmd}.R bench.R &&  \
	      $(JAGS) $${cmdfile} && \
	      R --vanilla --quiet < ../../R/check.R && \
	      rm bench.R;) || exit 1; \
	    done;) || exit 1;\
	done;

Rcheck: 
	@echo "Checking output against benchmark results"
	@for d in $(EXAMPLES); do \
	   (cd $${d} && \
	   for cmdfile in `ls test*.R`; do \
	      R --vanilla  < $${cmdfile} || exit 1; \
	   done;) || exit 1;\
	done;

checktime:
	rm -f times
	@for d in $(EXAMPLES); do \
	   (cd $${d} && \
	    for cmdfile in `ls test*.cmd`; do \
	      ($(TIME)  -f "$${d} $${cmdfile} %e %U %S" -o ../times -a \
	      $(JAGS) $${cmdfile};) || exit 1; \
	    done;) || exit 1;\
	done;

clean:
	@for d in $(EXAMPLES); do \
	   (cd $${d} && rm -f core jags.out jags.ind jags.dump \
            CODAchain*.txt CODAindex.txt gmon.out) || exit 1; \
	done;

distclean: clean
	@for d in $(EXAMPLES); do \
	   (cd $${d} && rm -f bench-*.R) || exit 1; \
	done;
