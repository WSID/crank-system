SUBDIRS=c

# if TEST_PYTHON
# SUBDIRS+= python
# endif

# if ENABLE_VAPIGEN
# SUBDIRS+= vala
# endif

.PHONY: bench

bench:
	for DIR in $(SUBDIRS); do \
	    $(MAKE) -C $$DIR bench ; \
	done
