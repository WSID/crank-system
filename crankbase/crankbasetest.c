/* Copyright (C) 2015, WSID   */

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#define _CRANKBASE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbasetest.h"

//////// Private functions /////////////////////////////////////////////////////
static void		crank_test_meta_expected_fail (	gconstpointer	userdata	);


//////// Adding meta test-case /////////////////////////////////////////////////
/**
 * crank_test_add_func_expected_fail: (skip)
 * @path: A Test path.
 * @func: A testing function, supposed to fail.
 * 
 * Adds a test case that checks given test fails.
 * 
 * If given function does not fail, then the test is considered to be failed.
 */
void
crank_test_add_func_expected_fail (	const gchar*	path,
									GTestFunc		func	)
{
	gchar*	func_path = g_strdup_printf ("/_crank/subprocess/efail%s", path);
	
	g_test_add_func (func_path, func);
	g_test_add_data_func_full (path, func_path, crank_test_meta_expected_fail, g_free);
}


//////// Meta testcases ////////////////////////////////////////////////////////
static void
crank_test_meta_expected_fail (	gconstpointer	userdata	)
{
	gchar*	efail_path = (gchar*) userdata;
	
	g_test_trap_subprocess (efail_path, 0, G_TEST_SUBPROCESS_INHERIT_STDERR);
	g_test_trap_assert_failed ();
}