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

#include <glib.h>

#include "crankbase.h"

//////// Declaration ///////////////////////////////////////////////////////////

static void		test_uint_equal (void);

static void		test_uint_hash (void);

static void		test_uint_to_string (void);

static void		test_uint_is_empty (void);

static void		test_uint_is_unit (void);

static void		test_uint_length (void);

static void		test_uint_contains (void);

static void		test_uint_get (void);

static void		test_uint_index_of (void);

static void		test_uint_clamp (void);

static void		test_uint_intersection (void);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (	gint   argc,
      	gchar *argv[] )
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/crank/base/range/uint/equal",		test_uint_equal	);
	g_test_add_func ("/crank/base/range/uint/hash",			test_uint_hash	);
	g_test_add_func ("/crank/base/range/uint/to_string",	test_uint_to_string	);
	g_test_add_func ("/crank/base/range/uint/is_empty",		test_uint_is_empty	);
	g_test_add_func ("/crank/base/range/uint/is_unit",		test_uint_is_unit	);
	g_test_add_func ("/crank/base/range/uint/length",		test_uint_length	);
	g_test_add_func ("/crank/base/range/uint/contains",		test_uint_contains	);
	g_test_add_func ("/crank/base/range/uint/get",			test_uint_get	);
	g_test_add_func ("/crank/base/range/uint/index_of",		test_uint_index_of	);
	g_test_add_func ("/crank/base/range/uint/clamp",		test_uint_clamp	);
	g_test_add_func ("/crank/base/range/uint/intersection",	test_uint_intersection	);
	
	g_test_run ();

	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static void
test_uint_equal ( void )
{
	CrankRanUint	a = {0, 4};
	CrankRanUint	b = {3, 5};
	CrankRanUint	c = {0, 4};
	
	g_assert (! crank_ran_uint_equal (&a, &b));
	g_assert (crank_ran_uint_equal (&a, &c));
}

static void
test_uint_hash ( void )
{
	CrankRanUint	a = {0, 4};
	CrankRanUint	b = {3, 5};
	CrankRanUint	c = {0, 4};
	
	g_assert_cmpuint (crank_ran_uint_hash (&a), !=, crank_ran_uint_hash (&b));
	g_assert_cmpuint (crank_ran_uint_hash (&a), ==, crank_ran_uint_hash (&c));
}

static void
test_uint_to_string (void)
{
	CrankRanUint	a = {3, 5};
	gchar*			astr = crank_ran_uint_to_string (&a);
	
	g_assert_cmpstr ("[3, 5)", ==, astr);
	
	g_free (astr);
}

static void
test_uint_is_empty (void)
{
	CrankRanUint	a = {3, 4};
	g_assert (! crank_ran_uint_is_empty (&a));
	
	crank_ran_uint_init (&a, 6, 6);
	g_assert (crank_ran_uint_is_empty (&a));
}

static void
test_uint_is_unit (void)
{
	CrankRanUint	a = {3, 4};
	g_assert (crank_ran_uint_is_unit (&a));
	
	crank_ran_uint_init (&a, 6, 6);
	g_assert (! crank_ran_uint_is_unit (&a));
}

static void
test_uint_length (void)
{
	CrankRanUint	a;
	
	crank_ran_uint_init (&a, 3, 5);
	
	g_assert_cmpuint (crank_ran_uint_get_length (&a), ==, 2);
}

static void
test_uint_contains (void)
{
	CrankRanUint	a;
	
	crank_ran_uint_init (&a, 4, 8);
	
	g_assert (crank_ran_uint_contains (&a, 4));
	g_assert (crank_ran_uint_contains (&a, 7));
	
	g_assert (! crank_ran_uint_contains (&a, 3));
	g_assert (! crank_ran_uint_contains (&a, 8));
}

static void
test_uint_get (void)
{
	CrankRanUint	a;
	
	crank_ran_uint_init (&a, 10, 110);
	
	g_assert_cmpuint (crank_ran_uint_get (&a, 0.25f), ==, 35);
}

static void
test_uint_index_of (void)
{
	CrankRanUint	a;
	crank_ran_uint_init (&a, 10, 110);
	
	crank_assert_cmpfloat (crank_ran_uint_index_of (&a, 60), ==, 0.5f);
}

static void
test_uint_clamp (void)
{
	CrankRanUint	a;
	crank_ran_uint_init (&a, 55, 95);
	
	g_assert_cmpuint (crank_ran_uint_clamp (&a, 43), ==, 55);
	g_assert_cmpuint (crank_ran_uint_clamp (&a, 77), ==, 77);
	g_assert_cmpuint (crank_ran_uint_clamp (&a, 99), ==, 95);
}

static void
test_uint_intersection (void)
{
	CrankRanUint	a;
	CrankRanUint	b;
	CrankRanUint	c;
	
	CrankRanUint	d;
	CrankRanUint	e;
	
	crank_ran_uint_init (&a, 20, 35);
	crank_ran_uint_init (&b, 45, 80);
	crank_ran_uint_init (&c, 30, 60);
	
	g_assert (! crank_ran_uint_intersection (&a, &b, &d));
	g_assert (crank_ran_uint_intersection (&a, &c, &e));
	
	g_assert_cmpuint (e.start, ==, 30);
	g_assert_cmpuint (e.end, ==, 35);
}
