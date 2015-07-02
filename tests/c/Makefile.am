## tests: 라이브러리 테스트

include ../glib-tap.mk

SUBDIRS=. perf

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase \
		-lm

TEST_BASE_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

# 대상 목록
test_programs= \
		test_string \
		test_base_macro \
		test_value \
		test_vec_bool \
		test_vec_int \
		test_vec_float \
		test_digraph \
		test_advgraph \
		test_mat_float

test_string_LDADD= $(TEST_BASE_LDADD)

test_base_macro_LDADD= $(TEST_BASE_LDADD)

test_value_LDADD= $(TEST_BASE_LDADD)


test_vec_bool_LDADD=  $(TEST_BASE_LDADD)

test_vec_int_LDADD=  $(TEST_BASE_LDADD)

test_vec_float_LDADD=  $(TEST_BASE_LDADD)

test_digraph_LDADD=  $(TEST_BASE_LDADD)

test_advgraph_LDADD=  $(TEST_BASE_LDADD)

test_mat_float_LDADD=  $(TEST_BASE_LDADD)
