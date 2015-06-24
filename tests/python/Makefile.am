# tests_python
# Python에서 Crank System을 테스트합니다.

TESTS= \
	test_vec_bool.py \
	test_vec_int.py \
	test_vec_float.py \
	test_digraph.py

AM_TESTS_ENVIRONMENT= \
	LD_LIBRARY_PATH=$(top_builddir)/crankbase/.libs/ \
	GI_TYPELIB_PATH=$(top_builddir)/crankbase/ \
	export LD_LIBRARY_PATH \
	export GI_TYPELIB_PATH;

LOG_COMPILER= $(PYTHON)

