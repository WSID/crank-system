## tests: 라이브러리 테스트

include ../glib-tap.mk


# 대상 목록
test_programs= \
		test_vala \
		test_func_holder \
		test_singular \
		test_types_graph


# test_func_holder
test_vala_VALAFLAGS= \
		--pkg=crank-base-0.0 \
		--vapidir=$(top_builddir)/crankbase

test_vala_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

test_vala_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_vala_SOURCES= \
		test_vala.vala


# test_func_holder
test_func_holder_VALAFLAGS= \
		--pkg=crank-base-0.0 \
		--vapidir=$(top_builddir)/crankbase

test_func_holder_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

test_func_holder_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_func_holder_SOURCES= \
		test_func_holder.vala
		
		
test_singular_VALAFLAGS= \
		--pkg=crank-base-0.0 \
		--vapidir=$(top_builddir)/crankbase

test_singular_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

test_singular_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_singular_SOURCES= \
		test_singular.vala


test_types_graph_VALAFLAGS= \
		--pkg=crank-base-0.0 \
		--vapidir=$(top_builddir)/crankbase

test_types_graph_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

test_types_graph_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_types_graph_SOURCES= \
		test_types_graph.vala
