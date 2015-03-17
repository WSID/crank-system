## tests: 라이브러리 테스트

include ../glib-tap.mk

# 대상 목록
test_programs=test_dummy


# test_dummy
test_dummy_CFLAGS= \
		$(CRANK_DUMMY_CFLAGS) \
		-I $(top_srcdir)/crankdummy

test_dummy_LDADD= \
		$(CRANK_DUMMY_LIBS) \
		$(top_builddir)/crankdummy/libcrankdummy.la

test_dummy_SOURCES= \
		test_dummy.c
