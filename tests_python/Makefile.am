# tests_python
# Python에서 Crank System을 테스트합니다.

TESTS= \
	test_func_holder.py \
	test_singular.py \
	test_types_graph.py \
	test_base_book.py

AM_TESTS_ENVIRONMENT= \
	LD_LIBRARY_PATH=$(top_builddir)/crankbase/.libs/ \
	GI_TYPELIB_PATH=$(top_builddir)/crankbase/ \
	export LD_LIBRARY_PATH \
	export GI_TYPELIB_PATH;

LOG_COMPILER= $(PYTHON)

