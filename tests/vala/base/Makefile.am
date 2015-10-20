## tests: 라이브러리 테스트

include ../../glib-tap.mk

AM_VALAFLAGS= \
		--pkg=crank-base-0.0 \
		--vapidir=$(top_builddir)/crankbase

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase


# 대상 목록
test_programs= \
		test_base_test \
		test_string \
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




test_base_test_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_base_test_SOURCES= \
		test_base_test.vala



test_string_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_string_SOURCES= \
		test_string.vala


test_range_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_range_SOURCES= \
		test_range.vala


test_iter_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_iter_SOURCES= \
		test_iter.vala

test_permutation_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_permutation_SOURCES= \
		test_permutation.vala


test_complex_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_complex_SOURCES= \
		test_complex.vala


test_quaternion_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_quaternion_SOURCES= \
		test_quaternion.vala


test_vec_bool_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_vec_bool_SOURCES= \
		test_vec_bool.vala


test_vec_int_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_vec_int_SOURCES= \
		test_vec_int.vala


test_vec_float_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_vec_float_SOURCES= \
		test_vec_float.vala


test_vec_cplx_float_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_vec_cplx_float_SOURCES= \
		test_vec_cplx_float.vala


test_mat_float_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_mat_float_SOURCES= \
		test_mat_float.vala


test_mat_cplx_float_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_mat_cplx_float_SOURCES= \
		test_mat_cplx_float.vala


test_advmat_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_advmat_SOURCES= \
		test_advmat.vala


test_digraph_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_digraph_SOURCES= \
		test_digraph.vala


test_advgraph_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_advgraph_SOURCES= \
		test_advgraph.vala
