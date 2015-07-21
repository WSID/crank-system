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
 
#include <string.h>
#include <glib.h>

#include "crankbase.h"


//////// Declaration ///////////////////////////////////////////////////////////

static void test_assert_eqarray (void);
static void test_assert_eqarray_subprocess (void);

static void test_assert_eqarray_float (void);
static void test_assert_eqarray_float_subprocess (void);

static void	test_assert_cmpfloat (void);
static void	test_assert_cmpfloat_subprocess (void);

static void	test_assert_eqcplxfloat (void);
static void	test_assert_eqcplxfloat_subprocess (void);

//////// Main //////////////////////////////////////////////////////////////////
gint
main	(gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/test/eqarray", test_assert_eqarray);
	g_test_add_func ("/crank/base/test/eqarray/subprocess", test_assert_eqarray_subprocess);
	
	g_test_add_func ("/crank/base/test/eqarray/float", test_assert_eqarray_float);
	g_test_add_func ("/crank/base/test/eqarray/float/subprocess", test_assert_eqarray_float_subprocess);

	g_test_add_func ("/crank/base/test/cmpfloat", test_assert_cmpfloat);
	g_test_add_func ("/crank/base/test/cmpfloat/subprocess", test_assert_cmpfloat_subprocess);
	
	g_test_add_func ("/crank/base/test/eqcplxfloat", test_assert_eqcplxfloat);
	g_test_add_func ("/crank/base/test/eqcplxfloat/subprocess", test_assert_eqcplxfloat_subprocess);

	g_test_run ();
	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static gchar*
double_to_string (gpointer	ptr) {
	return g_strdup_printf ("%g", *((gdouble*)ptr));
}

static void
test_assert_eqarray (void) {

	gdouble a[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	gdouble b[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	
	crank_assert_eqarray (gdouble, a, 10, b, 10, g_double_equal, double_to_string, NULL);
	
	g_test_trap_subprocess ("/crank/base/test/eqarray/subprocess",
			0, G_TEST_SUBPROCESS_INHERIT_STDERR	);
	
	g_test_trap_assert_failed ();
}

static void
test_assert_eqarray_subprocess (void) {
	gdouble a[10] = { 1.0, 2.0, 3.0, 4.0, 4.9, 6.0, 7.0, 8.0, 9.0, 10.0};
	gdouble b[10] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	
	crank_assert_eqarray (gdouble, a, 10, b, 10, g_double_equal, double_to_string, NULL);
}



static void
test_assert_eqarray_float (void) {

	gfloat a[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	gfloat b[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	
	crank_assert_eqarray_float (a, 10, b, 10, NULL);
	
	g_test_trap_subprocess ("/crank/base/test/eqarray/subprocess",
			0, G_TEST_SUBPROCESS_INHERIT_STDERR	);
	
	g_test_trap_assert_failed ();
}

static void
test_assert_eqarray_float_subprocess (void) {
	gfloat a[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	gfloat b[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	
	crank_assert_eqarray_float (a, 10, b, 10, NULL);
}



static void
test_assert_cmpfloat (void) {
	// Tests whether assertion actually allows errors within given errors.
	crank_assert_cmpfloat_d (3.0f, ==, 3.5f, 1.0f);
	crank_assert_cmpfloat_d (2.0f, <, 3.5f, 1.0f);
	
	g_test_trap_subprocess ("/crank/base/test/cmpfloat/subprocess",
			0, G_TEST_SUBPROCESS_INHERIT_STDERR	);
	
	g_test_trap_assert_failed ();
}

static void
test_assert_cmpfloat_subprocess (void) {
	// Tests whether assertion can actually fails.
	crank_assert_cmpfloat_d ( 7.5f, <, 3.5f, 1.0f);
}

static void
test_assert_eqcplxfloat (void) {
	CrankCplxFloat	a = {3.0f, 2.0f};
	CrankCplxFloat	b = {3.5f, 2.1f};
	CrankCplxFloat	c = {2.9f, 1.4f};
	
	// Tests whether assertion actually allows errors within given errors.
	crank_assert_eqcplxfloat_d (&a, &b, 1.0f);
	crank_assert_eqcplxfloat_d (&a, &c, 1.0f);
	
	g_test_trap_subprocess ("/crank/base/test/eqcplxfloat/subprocess",
			0, G_TEST_SUBPROCESS_INHERIT_STDERR	);
	
	g_test_trap_assert_failed ();
}

static void
test_assert_eqcplxfloat_subprocess (void) {
	// Tests whether assertion can actually fails.
	CrankCplxFloat	a = {3.0f, 2.0f};
	CrankCplxFloat	b = {4.2f, 2.0f};
	
	crank_assert_eqcplxfloat_d (&a, &b, 1.0f);
}
