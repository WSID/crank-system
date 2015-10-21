include ../../glib-tap.mk

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		$(CRANK_SHAPE_CFLAGS) \
		-I $(top_srcdir)/crankbase \
		-I $(top_srcdir)/crankshape \
		-lm

TEST_SHAPE_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la \
		$(top_builddir)/crankshape/libcrankshape.la

# 대상 목록
test_programs= \
		test_euler

test_euler_SOURCES= test_euler.c
test_euler_LDADD= $(TEST_SHAPE_LDADD)
