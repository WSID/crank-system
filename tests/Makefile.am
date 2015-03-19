## tests: 라이브러리 테스트

include ../glib-tap.mk

# 대상 목록
test_programs= \
		test_base_macro \
		test_func_holder


# test_dummy
test_dummy_CFLAGS= \
		$(CRANK_DUMMY_CFLAGS) \
		-I $(top_srcdir)/crankdummy

test_dummy_LDADD= \
		$(CRANK_DUMMY_LIBS) \
		$(top_builddir)/crankdummy/libcrankdummy.la

test_dummy_SOURCES= \
		test_dummy.c


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
test_func_holder_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

test_func_holder_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

test_func_holder_SOURCES= \
		test_func_holder.c
