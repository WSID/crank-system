## tests: 라이브러리 테스트

include ../../glib-tap.mk

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

TEST_BASE_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

# 대상 목록
test_programs= \
		test_perf_digraph

test_perf_digraph_LDADD=  $(TEST_BASE_LDADD)
