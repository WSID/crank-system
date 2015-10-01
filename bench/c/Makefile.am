## tests: 라이브러리 테스트

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

TEST_BASE_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

bench_programs = \
		test_perf_digraph \
		test_perf_matfloat \
		test_perf_str

test_perf_digraph_LDADD=  $(TEST_BASE_LDADD)
test_perf_matfloat_LDADD=  $(TEST_BASE_LDADD)
test_perf_str_LDADD=  $(TEST_BASE_LDADD)





noinst_PROGRAMS= $(bench_programs)

# We are use gtester, a kind of deprecated tool
# This is not a Pass-Fail Tests. TAP protocol would not be appropriate for it.
bench-local: $(bench_programs)
	sh ../bench_helper.sh gen $(bench_programs)

cpylog: $(bench_programs)
	sh ../bench_helper.sh cpy . `date +%Y-%m-%d` $(bench_programs)

