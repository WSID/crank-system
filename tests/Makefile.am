## tests: 라이브러리 테스트

include ../glib-tap.mk

# 대상 목록
test_programs= \
		test_base_macro \
		test_types_graph \
		test_func_holder

# test_base_macro
test_base_macro_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

test_base_macro_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_base_macro_SOURCES= \
		test_base_macro.c


# test_func_holder
test_types_graph_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

test_types_graph_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_types_graph_SOURCES= \
		test_types_graph.c
		

# test_func_holder
test_func_holder_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

test_func_holder_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_func_holder_SOURCES= \
		test_func_holder.c
