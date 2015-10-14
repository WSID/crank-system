## bench: Benchmark functions.

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

TEST_BASE_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

bench_programs = \
		test_perf_matfloat

test_perf_matfloat_LDADD=  $(TEST_BASE_LDADD)

noinst_PROGRAMS= $(bench_programs)

.PHONY: bench

bench: $(bench_programs)
	for bench in $(bench_programs); \
	do $$bench ; \
	done
