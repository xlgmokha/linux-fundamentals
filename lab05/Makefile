
#############################################################################

include ../make/defaults.mk

clean:
	rm -f procs threads $(DESTDIR)/procs $(DESTDIR)/threads

procs: procs.c Makefile
	$(CC) -o $@ $<
	cp procs $(DESTDIR)

threads: threads.c Makefile
	$(CC) -o $@ $< -lpthread
	cp threads $(DESTDIR)

sched: sched.c Makefile
	$(CC) -o $@ $< -lpthread
	cp sched $(DESTDIR)

