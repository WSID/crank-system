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

//////// Testing Variables /////////////////////////////////////////////////////

static guint		N	= 1024;
static guint		R	= 8;


//////// Declaration ///////////////////////////////////////////////////////////

static void test_gen_mat_float_n (CrankMatFloatN* mat);

static void test_mat_mul (void);
static void test_mat_mul_self (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_message ("N: %u", N);
	g_test_message ("R: %u", R);
	
	g_test_add_func ("/crank/base/mat/float/n/perf/mul",
			test_mat_mul);
	g_test_add_func ("/crank/base/mat/float/n/perf/mul_self",
			test_mat_mul_self);
	
	g_test_run ();

	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static void
test_gen_mat_float_n (CrankMatFloatN* mat)
{
	guint i;
	
	crank_mat_float_n_init_fill (mat, N, N, 0.0f);
	
	for (i = 0; i < N*N; i++) {
		mat->data[i] = g_test_rand_double ();
	}
}



static void
test_mat_mul (void)
{
	guint i;
	
	for (i = 0; i < R; i++) {
		CrankMatFloatN	a;
		CrankMatFloatN	b;
		CrankMatFloatN	c;
			
		test_gen_mat_float_n (&a);
		test_gen_mat_float_n (&b);
		
		g_test_timer_start ();
		
		crank_mat_float_n_mul (&a, &b, &c);
		
		g_test_minimized_result ( g_test_timer_elapsed (), "mul");
		
		crank_mat_float_n_fini (&a);
		crank_mat_float_n_fini (&b);
		crank_mat_float_n_fini (&c);
	}
}

static void
test_mat_mul_self (void)
{
	guint i;
	
	for (i = 0; i < R; i++) {
		CrankMatFloatN	a;
		CrankMatFloatN	b;
			
		test_gen_mat_float_n (&a);
		test_gen_mat_float_n (&b);
		
		g_test_timer_start ();
		
		crank_mat_float_n_mul_self (&a, &b);
		
		g_test_minimized_result ( g_test_timer_elapsed (), "mul-self");
		
		crank_mat_float_n_fini (&a);
		crank_mat_float_n_fini (&b);
	}
}
