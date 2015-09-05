
AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase \
		-lm

bin_PROGRAMS=crank-demo-matrix

crank_demo_matrix_SOURCES= \
		crankdemomatrix.c

crank_demo_matrix_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la
