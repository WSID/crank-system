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

static void test_always_pass (void);
static void test_always_fail (void);


static void test_test_expected_fail_onpass (void);

static void test_assert_eqarray_float (void);
static void test_assert_eqarray_float_fail (void);

static void test_assert_eqarray_float_imm (void);
static void test_assert_eqarray_float_imm_fail (void);

static void test_assert_eqarray_pointer (void);
static void test_assert_eqarray_pointer_fail (void);

static void test_assert_eqarray_pointer_imm (void);
static void test_assert_eqarray_pointer_imm_fail (void);

static void test_assert_eqarray_pointer_imm (void);
static void test_assert_eqarray_pointer_imm_fail (void);

static void test_assert_eq_glist_imm (void);
static void test_assert_eq_glist_imm_fail (void);

static void test_assert_eq_gptrarray_imm (void);
static void test_assert_eq_gptrarray_imm_fail (void);

static void	test_assert_cmpfloat (void);
static void	test_assert_cmpfloat_fail (void);

static void	test_assert_eqcplxfloat (void);
static void	test_assert_eqcplxfloat_fail (void);

static void	test_assert_eqcplxfloat_cimm (void);
static void	test_assert_eqcplxfloat_cimm_fail (void);

//////// Main //////////////////////////////////////////////////////////////////
gint
main	(gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);
	
	crank_test_add_func_expected_fail (
			"/crank/base/test/expected_fail",
			test_always_fail	);
	
	
	g_test_add_func (
			"/crank/base/test/expected_fail/onpass",
			test_test_expected_fail_onpass	);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/expected_fail/subprocess",
			test_always_pass);
	
	
	g_test_add_func (
			"/crank/base/test/eq/array/float",
			test_assert_eqarray_float	);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/eq/array/float/fail",
			test_assert_eqarray_float_fail	);
	
	
	g_test_add_func (
			"/crank/base/test/eq/array/float/imm",
			test_assert_eqarray_float_imm	);

	crank_test_add_func_expected_fail (
			"/crank/base/test/eq/array/float/imm/fail",
			test_assert_eqarray_float_imm_fail	);
	
	
	g_test_add_func (
			"/crank/base/test/eq/array/pointer",
			test_assert_eqarray_pointer	);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/eq/array/pointer/fail",
			test_assert_eqarray_pointer_fail	);
	
	
	g_test_add_func (
			"/crank/base/test/eq/array/pointer/imm",
			test_assert_eqarray_pointer_imm	);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/eq/array/pointer/imm/fail",
			test_assert_eqarray_pointer_imm_fail	);
	
	
	g_test_add_func (
			"/crank/base/test/eq/glist/imm",
			test_assert_eq_glist_imm	);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/eq/glist/imm/fail",
			test_assert_eq_glist_imm_fail	);
	
	
	g_test_add_func (
			"/crank/base/test/eq/gptrarray/imm",
			test_assert_eq_gptrarray_imm	);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/eq/gptrarray/imm/fail",
			test_assert_eq_gptrarray_imm_fail	);
			
			
			
	
	g_test_add_func (
			"/crank/base/test/cmpfloat",
			test_assert_cmpfloat	);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/cmpfloat/fail",
			test_assert_cmpfloat_fail	);
	
	
	
	g_test_add_func (
			"/crank/base/test/eq/cplxfloat",
			test_assert_eqcplxfloat);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/eq/cplxfloat/fail",
			test_assert_eqcplxfloat_fail	);
			
	
	g_test_add_func (
			"/crank/base/test/eq/cplxfloat/cimm",
			test_assert_eqcplxfloat_cimm);
			
	crank_test_add_func_expected_fail (
			"/crank/base/test/eq/cplxfloat/cimm/fail",
			test_assert_eqcplxfloat_cimm_fail	);


	g_test_run ();
	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////


static void
test_always_pass (void) {
	// Tests 1 + 1 == 2
	g_assert_cmpuint ((1 + 1), ==, 2);
}

static void
test_always_fail (void) {
	// Tests 0 == 1, which is obviously wrong.
	g_assert_cmpuint (0, ==, 1);
}


static void
test_test_expected_fail_onpass (void) {
	g_test_trap_subprocess (
			"/crank/base/test/expected_fail/subprocess",
			0,
			G_TEST_SUBPROCESS_INHERIT_STDERR);
	g_test_trap_assert_failed ();
}




static void
test_assert_eqarray_float (void) {

	gfloat a[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	gfloat b[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	
	crank_assert_eqarray_float (a, 10, b, 10, NULL);
}

static void
test_assert_eqarray_float_fail (void) {
	gfloat a[10] = { 1.0f, 2.1f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	gfloat b[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	
	crank_assert_eqarray_float (a, 10, b, 10, NULL);
}




static void
test_assert_eqarray_float_imm (void) {

	gfloat a[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
	
	crank_assert_eqarray_float_imm (a, 4, NULL, 1.0f, 2.0f, 3.0f, 4.0f);
}

static void
test_assert_eqarray_float_imm_fail (void) {

	gfloat a[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
	
	crank_assert_eqarray_float_imm (a, 4, NULL, 1.0f, 2.1f, 3.0f, 4.0f);
}



static void
test_assert_eqarray_pointer (void) {
	gpointer a[4] = {
		GINT_TO_POINTER(0x1111),
		GINT_TO_POINTER(0x2222),
		GINT_TO_POINTER(0x3333),
		GINT_TO_POINTER(0x4444)	};
	gpointer b[4] = {
		GINT_TO_POINTER(0x1111),
		GINT_TO_POINTER(0x2222),
		GINT_TO_POINTER(0x3333),
		GINT_TO_POINTER(0x4444)	};
	
	crank_assert_eqarray_pointer (a, 4, b, 4);
}

static void
test_assert_eqarray_pointer_fail (void) {
	gpointer a[4] = {
		GINT_TO_POINTER(0x1111),
		GINT_TO_POINTER(0x1112),
		GINT_TO_POINTER(0x3333),
		GINT_TO_POINTER(0x4444)	};
	gpointer b[4] = {
		GINT_TO_POINTER(0x1111),
		GINT_TO_POINTER(0x2222),
		GINT_TO_POINTER(0x3333),
		GINT_TO_POINTER(0x4444)	};
	
	crank_assert_eqarray_pointer (a, 4, b, 4);
}



static void
test_assert_eqarray_pointer_imm (void) {
	gpointer a[4] = {
		GINT_TO_POINTER(0x1111),
		GINT_TO_POINTER(0x2222),
		GINT_TO_POINTER(0x3333),
		GINT_TO_POINTER(0x4444)	};
		
	crank_assert_eqarray_pointer_imm (a, 4,
		GINT_TO_POINTER(0x1111),
		GINT_TO_POINTER(0x2222),
		GINT_TO_POINTER(0x3333),
		GINT_TO_POINTER(0x4444)	);
}

static void
test_assert_eqarray_pointer_imm_fail (void) {
	gpointer a[4] = {
		GINT_TO_POINTER(0x1111),
		GINT_TO_POINTER(0x2220),
		GINT_TO_POINTER(0x3333),
		GINT_TO_POINTER(0x4444)	};
	
	crank_assert_eqarray_pointer_imm (a, 4,
			GINT_TO_POINTER(0x1111),
			GINT_TO_POINTER(0x2222),
			GINT_TO_POINTER(0x3333),
			GINT_TO_POINTER(0x4444)	);
}



static void
test_assert_eq_glist_imm (void) {
	GList*	a = NULL;
	
	a = g_list_append (a, GINT_TO_POINTER(0x1000));
	a = g_list_append (a, GINT_TO_POINTER(0x2000));
	a = g_list_append (a, GINT_TO_POINTER(0x3000));
	a = g_list_append (a, GINT_TO_POINTER(0x4000));

	crank_assert_eq_glist_imm (a,
			GINT_TO_POINTER(0x1000),
			GINT_TO_POINTER(0x2000),
			GINT_TO_POINTER(0x3000),
			GINT_TO_POINTER(0x4000)	);

	g_list_free (a);
}

static void
test_assert_eq_glist_imm_fail (void) {
	GList*	a = NULL;
	
	a = g_list_append (a, GINT_TO_POINTER(0x1000));
	a = g_list_append (a, GINT_TO_POINTER(0x2000));
	a = g_list_append (a, GINT_TO_POINTER(0x3100));
	a = g_list_append (a, GINT_TO_POINTER(0x4000));

	crank_assert_eq_glist_imm (a,
			GINT_TO_POINTER(0x1000),
			GINT_TO_POINTER(0x2000),
			GINT_TO_POINTER(0x3000),
			GINT_TO_POINTER(0x4000)	);

	g_list_free (a);
}



static void
test_assert_eq_gptrarray_imm (void) {
	GPtrArray*	a = g_ptr_array_new ();
	
	g_ptr_array_add (a, GINT_TO_POINTER(0x1000));
	g_ptr_array_add (a, GINT_TO_POINTER(0x2000));
	g_ptr_array_add (a, GINT_TO_POINTER(0x3000));
	g_ptr_array_add (a, GINT_TO_POINTER(0x4000));

	crank_assert_eq_gptrarray_imm (a,
			GINT_TO_POINTER(0x1000),
			GINT_TO_POINTER(0x2000),
			GINT_TO_POINTER(0x3000),
			GINT_TO_POINTER(0x4000)	);

	g_ptr_array_unref (a);
}

static void
test_assert_eq_gptrarray_imm_fail (void) {
	GPtrArray*	a = g_ptr_array_new ();
	
	g_ptr_array_add (a, GINT_TO_POINTER(0x4000));
	g_ptr_array_add (a, GINT_TO_POINTER(0x3000));
	g_ptr_array_add (a, GINT_TO_POINTER(0x2000));
	g_ptr_array_add (a, GINT_TO_POINTER(0x1000));

	crank_assert_eq_gptrarray_imm (a,
			GINT_TO_POINTER(0x1000),
			GINT_TO_POINTER(0x2000),
			GINT_TO_POINTER(0x3000),
			GINT_TO_POINTER(0x4000)	);

	g_ptr_array_unref (a);
}


static void
test_assert_cmpfloat (void) {
	// Tests whether assertion actually allows errors within given errors.
	crank_assert_cmpfloat_d (3.0f, ==, 3.5f, 1.0f);
	crank_assert_cmpfloat_d (2.0f, <, 3.5f, 1.0f);
}

static void
test_assert_cmpfloat_fail (void) {
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
}

static void
test_assert_eqcplxfloat_fail (void) {
	// Tests whether assertion can actually fails.
	CrankCplxFloat	a = {3.0f, 2.0f};
	CrankCplxFloat	b = {4.2f, 2.0f};
	
	crank_assert_eqcplxfloat_d (&a, &b, 1.0f);
}


static void
test_assert_eqcplxfloat_cimm (void) {
	CrankCplxFloat	a = {3.0f, 2.0f};
	
	// Tests whether assertion actually allows errors within given errors.
	crank_assert_eqcplxfloat_d_cimm (&a, 3.5f, 2.1f, 1.0f);
	crank_assert_eqcplxfloat_d_cimm (&a, 2.9f, 1.4f, 1.0f);
}

static void
test_assert_eqcplxfloat_cimm_fail (void) {
	// Tests whether assertion can actually fails.
	CrankCplxFloat	a = {3.0f, 2.0f};
	
	crank_assert_eqcplxfloat_d_cimm (&a, 4.2f, 2.0f, 1.0f);
}
