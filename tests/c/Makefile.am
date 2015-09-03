## tests: 라이브러리 테스트

include ../glib-tap.mk

SUBDIRS= .

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase \
		-lm

TEST_BASE_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

# 대상 목록
test_programs= \
		test_base_test \
		test_string \
		test_base_macro \
		test_value \
		test_range \
		test_iter \
		test_permutation \
		test_complex \
		test_quaternion \
		test_vec_bool \
		test_vec_int \
		test_vec_float \
		test_vec_cplx_float \
		test_mat_float \
		test_mat_cplx_float \
		test_advmat \
		test_digraph \
		test_advgraph 


test_base_test_LDADD= $(TEST_BASE_LDADD)

test_string_LDADD= $(TEST_BASE_LDADD)

test_base_macro_LDADD= $(TEST_BASE_LDADD)

test_value_LDADD= $(TEST_BASE_LDADD)

test_range_LDADD= $(TEST_BASE_LDADD)

test_iter_LDADD= $(TEST_BASE_LDADD)

test_permutation_LDADD= $(TEST_BASE_LDADD)

test_complex_LDADD=  $(TEST_BASE_LDADD)

test_quaternion_LDADD=  $(TEST_BASE_LDADD)

test_vec_bool_LDADD=  $(TEST_BASE_LDADD)

test_vec_int_LDADD=  $(TEST_BASE_LDADD)

test_vec_float_LDADD=  $(TEST_BASE_LDADD)

test_vec_cplx_float_LDADD=  $(TEST_BASE_LDADD)


test_mat_float_LDADD=  $(TEST_BASE_LDADD)

test_mat_cplx_float_LDADD=  $(TEST_BASE_LDADD)

test_advmat_LDADD=  $(TEST_BASE_LDADD)

test_digraph_LDADD=  $(TEST_BASE_LDADD)

test_advgraph_LDADD=  $(TEST_BASE_LDADD)
