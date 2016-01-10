AM_CFLAGS = \
	$(CRANK_VISUAL_DEMO_CFLAGS) \
	-I $(top_srcdir)/crankbase \
	-I $(top_srcdir)/crankshape \
	-I $(top_srcdir)/crankcore \
	-I $(top_srcdir)/crankvisual \
	-lm

bin_PROGRAMS= crank-demo-triangles

noinst_HEADERS= \
		crankdemorenderabletriangle.h

crank_demo_triangles_SOURCES= \
		crankdemotriangles.c \
		crankdemorenderabletriangle.c

crank_demo_triangles_LDADD= \
		$(CRANK_VISUAL_DEMO_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la \
		$(top_builddir)/crankshape/libcrankshape.la \
		$(top_builddir)/crankcore/libcrankcore.la \
		$(top_builddir)/crankvisual/libcrankvisual.la
