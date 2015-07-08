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

static void		test_check_valid (void);

static void		test_sign (void);

static void		test_swap (void);

static void		test_reverse (void);

static void		test_inverse (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);

  	g_test_add_func ("/crank/base/permutation/check_valid",
					test_check_valid);
					
  	g_test_add_func ("/crank/base/permutation/sign",
					test_sign);
					
  	g_test_add_func ("/crank/base/permutation/swap",
					test_swap);
					
  	g_test_add_func ("/crank/base/permutation/reverse",
					test_reverse);
					
  	g_test_add_func ("/crank/base/permutation/inverse",
					test_inverse);

  	g_test_run ();
  	return 0;
}

//////// Definition ////////////////////////////////////////////////////////////

static void
test_check_valid (void)
{
	CrankPermutation	p = {0};
	CrankPermutation	q = {0};
	CrankPermutation	r = {0};
	
	crank_permutation_init (&p, 5, 0, 1, 2, 3, 4);
	crank_permutation_init (&q, 5, 0, 3, 0, 2, 4);
	crank_permutation_init (&r, 5, 0, 6, 3, 4, 7);
	
	g_assert (  crank_permutation_check_valid (&p));
	g_assert (! crank_permutation_check_valid (&q));
	g_assert (! crank_permutation_check_valid (&r));
	
	crank_permutation_fini (&p);
	crank_permutation_fini (&q);
	crank_permutation_fini (&r);
}

static void
test_sign (void)
{
	CrankPermutation	p = {0};
	
	crank_permutation_init (&p, 5, 2, 1, 3, 4, 0);
	
	g_assert_cmpint (crank_permutation_get_sign (&p), ==, -1);
	
	crank_permutation_fini (&p);
}

static void
test_swap (void)
{
	CrankPermutation	p = {0};
	
	crank_permutation_init (&p, 5, 0, 1, 3, 2, 4);
	
	crank_permutation_swap (&p, 2, 3);
	
	g_assert_cmpuint (crank_permutation_get (&p, 2), ==, 2);
	g_assert_cmpuint (crank_permutation_get (&p, 3), ==, 3);
	
	crank_permutation_fini (&p);
}

static void
test_reverse (void)
{
	CrankPermutation	p = {0};
	
	crank_permutation_init (&p, 5, 0, 1, 3, 2, 4);
	
	crank_permutation_reverse (&p, &p);
	
	g_assert_cmpuint (crank_permutation_get (&p, 0), ==, 4);
	g_assert_cmpuint (crank_permutation_get (&p, 1), ==, 2);
	g_assert_cmpuint (crank_permutation_get (&p, 2), ==, 3);
	g_assert_cmpuint (crank_permutation_get (&p, 3), ==, 1);
	g_assert_cmpuint (crank_permutation_get (&p, 4), ==, 0);
	
	crank_permutation_fini (&p);
}

static void
test_inverse (void)
{
	CrankPermutation	p = {0};
	
	crank_permutation_init (&p, 5, 0, 1, 3, 2, 4);
	
	crank_permutation_inverse (&p, &p);
	
	g_assert_cmpuint (crank_permutation_get (&p, 0), ==, 0);
	g_assert_cmpuint (crank_permutation_get (&p, 1), ==, 1);
	g_assert_cmpuint (crank_permutation_get (&p, 2), ==, 3);
	g_assert_cmpuint (crank_permutation_get (&p, 3), ==, 2);
	g_assert_cmpuint (crank_permutation_get (&p, 4), ==, 4);
	
	crank_permutation_fini (&p);
}
