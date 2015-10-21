## tests: 라이브러리 테스트

include ../../glib-tap.mk

AM_VALAFLAGS= \
		--pkg=crank-base-0.0 \
		--pkg=crank-shape-0.0 \
		--vapidir=$(top_builddir)/crankbase \
		--vapidir=$(top_builddir)/crankshape

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase \
		-I $(top_srcdir)/crankshape


# 대상 목록
test_programs= \
		test_euler




test_euler_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(CRANK_SHAPE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la \
		$(top_builddir)/crankshape/libcrankshape.la

test_euler_SOURCES= \
		test_euler.vala

