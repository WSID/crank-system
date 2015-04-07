## tests: 라이브러리 테스트

include ../glib-tap.mk

TEST_BASE_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		-I $(top_srcdir)/crankbase

TEST_BASE_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la

# 대상 목록
test_programs= \
		test_base_macro \
		test_types_graph \
		test_func_holder \
		test_singular

# test_base_macro
test_base_macro_CFLAGS= $(TEST_BASE_CFLAGS)
test_base_macro_LDADD= $(TEST_BASE_LDADD)



# test_func_holder
test_types_graph_CFLAGS= $(TEST_BASE_CFLAGS)
test_types_graph_LDADD= $(TEST_BASE_LDADD)

		

# test_func_holder
test_func_holder_CFLAGS= $(TEST_BASE_CFLAGS)
test_func_holder_LDADD= $(TEST_BASE_LDADD)


test_singular_CFLAGS= $(TEST_BASE_CFLAGS)
test_singular_LDADD= $(TEST_BASE_LDADD)
