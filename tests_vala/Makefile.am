## tests: 라이브러리 테스트

include ../glib-tap.mk


# 대상 목록
test_programs= \
		test_func_holder

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
