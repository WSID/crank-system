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
		test_vala \
		test_string \
		test_digraph \
		test_vec_bool \
		test_vec_int \
		test_vec_float


# test_func_holder
test_vala_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_vala_SOURCES= \
		test_vala.vala



test_string_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_string_SOURCES= \
		test_string.vala
		

test_digraph_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_digraph_SOURCES= \
		test_digraph.vala

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
