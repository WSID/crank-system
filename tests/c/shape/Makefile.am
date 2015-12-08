include ../../glib-tap.mk

AM_CFLAGS= \
		$(CRANK_BASE_CFLAGS) \
		$(CRANK_SHAPE_CFLAGS) \
		-I $(top_srcdir)/crankbase \
		-I $(top_srcdir)/crankshape \
		-lm

TEST_SHAPE_LDADD= \
		$(CRANK_BASE_LIBS) \
		$(top_builddir)/crankbase/libcrankbase.la \
		$(top_builddir)/crankshape/libcrankshape.la

# 대상 목록
test_programs= \
		test_euler \
		test_rot \
		test_trans \
		test_misc \
		test_gjk \
		test_poly_struct

test_euler_SOURCES= test_euler.c
test_euler_LDADD= $(TEST_SHAPE_LDADD)

test_rot_SOURCES= test_rot.c
test_rot_LDADD= $(TEST_SHAPE_LDADD)

test_trans_SOURCES= test_trans.c
test_trans_LDADD= $(TEST_SHAPE_LDADD)

test_misc_SOURCES= test_misc.c
test_misc_LDADD= $(TEST_SHAPE_LDADD)

test_gjk_SOURCES= test_gjk.c
test_gjk_LDADD= $(TEST_SHAPE_LDADD)

test_poly_struct_SOURCES= test_poly_struct.c
test_poly_struct_LDADD= $(TEST_SHAPE_LDADD)
