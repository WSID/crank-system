
AM_CFLAGS= \
		$(CRANK_BASE_DEMO_CFLAGS) \
		-I $(top_srcdir)/crankbase \
		-lm

EXTRA_DIST= crankdemomatrix.gresources.xml crankdemomatpad.ui crankdemomatrix.ui

bin_PROGRAMS=crank-demo-matrix

noinst_HEADERS= \
		crankdemomatpad.h

crank_demo_matrix_SOURCES= \
		crankdemomatrix.c \
		crankdemomatpad.c \
		crankdemomatrix_res.c

crank_demo_matrix_LDADD= \
		$(CRANK_BASE_DEMO_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

crankdemomatrix_res.c: crankdemomatrix.gresources.xml crankdemomatpad.ui crankdemomatrix.ui
	glib-compile-resources --generate-source --target=crankdemomatrix_res.c crankdemomatrix.gresources.xml

CLEANFILES= crankdemomatrix_res.c
