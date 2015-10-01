## bench: Benchmark functions.

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

clean-local:
	for bench in $(bench_programs); \
	do rm $$bench.log ; \
	done

mostlyclean-local:
	rm *.log

# We are using gtester, a kind of deprecated tool
# This is not a Pass-Fail Tests. TAP protocol would not be appropriate for it.
.PHONY: bench cpylog

bench: $(bench_programs)
	for bench in $(bench_programs); \
	do gtester $$bench -o $$bench.log ; \
	done

cpylog: $(bench_programs)
	for bench in $(bench_programs); \
	do cp $$bench.log $$bench-`date +%Y-%m-%d`.log ; \
	done

