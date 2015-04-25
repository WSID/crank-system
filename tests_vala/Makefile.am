## tests: 라이브러리 테스트

include ../glib-tap.mk

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
		test_func_holder \
		test_singular \
		test_types_graph


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
		

# test_func_holder
test_func_holder_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_func_holder_SOURCES= \
		test_func_holder.vala
		

test_singular_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_singular_SOURCES= \
		test_singular.vala


test_types_graph_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_types_graph_SOURCES= \
		test_types_graph.vala
