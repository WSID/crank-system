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
static void	test_uint_iter (void);

static void test_uint_iter_foreach (void);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (	gint   argc,
      	gchar *argv[] )
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/crank/base/iter/uint",			test_uint_iter	);
	g_test_add_func ("/crank/base/iter/uint/foreach",	test_uint_iter_foreach	);
	
	g_test_run ();

	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////
static gboolean
test_accum_uint (const guint	value, gpointer	pointer)
{
	guint*	prod_sum = (guint*)pointer;
	
	prod_sum[0] *= value;
	prod_sum[1] += value;
	
	g_message ("value: %u", value);
	
	return TRUE;
}


static void
test_uint_iter (void) {
	guint	array[] = {3, 9, 1, 3, 2, 5, 5 ,9, 7};	
	guint	narray = G_N_ELEMENTS(array);
	
	guint	prod = 1;
	guint	sum = 0;

	CrankIterMemUint	iter;
	
	
	crank_iter_mem_uint_init_with_count (&iter, array, narray);
	
	
	while (crank_iter_mem_uint_next (&iter)) {
		guint	val = crank_iter_mem_uint_get (&iter);
		
		prod *= val;
		sum += val;
	}
	
	g_assert_cmpuint (prod, ==, 255150);
	g_assert_cmpuint (sum, ==, 44);
}

static void
test_uint_iter_foreach (void) {
	guint	array[] = {3, 9, 1, 3, 2, 5, 5 ,9, 7};	
	guint	narray = G_N_ELEMENTS(array);
	
	guint	prod_sum[2] = {1, 0};
	
	CrankIterMemUint	iter;
	
	crank_iter_mem_uint_init_with_count (&iter, array, narray);
	
	crank_iter_mem_uint_foreach (&iter, test_accum_uint, &prod_sum);
	
	g_assert_cmpuint (prod_sum[0], ==, 255150);
	g_assert_cmpuint (prod_sum[1], ==, 44);
}
