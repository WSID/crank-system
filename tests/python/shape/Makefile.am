# tests_python

TESTS= \
	test_euler.py \
	test_rot.py \
	test_trans.py \
	test_gjk.py \
	test_basics.py

AM_TESTS_ENVIRONMENT= \
	LD_LIBRARY_PATH=$(top_builddir)/crankbase/.libs/:$(top_builddir)/crankshape/.libs/ \
	GI_TYPELIB_PATH=$(top_builddir)/crankbase/:$(top_builddir)/crankshape/ \
	export LD_LIBRARY_PATH \
	export GI_TYPELIB_PATH;

LOG_COMPILER= $(PYTHON)

EXTRA_DIST=$(TESTS)
