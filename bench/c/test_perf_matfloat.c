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

static guint		N	= 512;
static guint		R	= 8;


//////// Declaration ///////////////////////////////////////////////////////////

static void test_gen_mat_float_n (		CrankMatFloatN* mat);
static void test_gen_mat_float_n_sym (	CrankMatFloatN* mat);
static void	test_gen_mat_float_4 (		CrankMatFloat4* mat);

static void test_mat_mul (void);
static void test_mat_mul_self (void);
static void test_mat4_mul (void);

static void test_mat_lu (void);
static void test_mat_gram_schmidt (void);
static void test_mat_householder (void);
static void test_mat_givens (void);

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
	g_test_add_func ("/crank/base/mat/float/4/perf/mul",
			test_mat4_mul);
			
	g_test_add_func ("/crank/base/mat/float/n/perf/lu",
			test_mat_lu	);
	g_test_add_func ("/crank/base/mat/float/n/perf/qr/gram-schmidt",
			test_mat_gram_schmidt	);
	//g_test_add_func ("/crank/base/mat/float/n/perf/qr/householder",
	//		test_mat_householder	);
	// We don't use it for now.
	// This will take so long, as slicing out a matrix.
	g_test_add_func ("/crank/base/mat/float/n/perf/qr/givens",
			test_mat_givens	);
	
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
test_gen_mat_float_n_sym (CrankMatFloatN* mat)
{
	guint i;
	guint j;
	
	crank_mat_float_n_init_fill (mat, N, N, 0.0f);
	
	for (i = 0; i < N; i++) {
		crank_mat_float_n_set (mat, i, i, (gfloat) g_test_rand_double ());
		
		for (j = i + 1; j < N; j++) {
			crank_mat_float_n_set (mat, i, j, (gfloat) g_test_rand_double ());
			crank_mat_float_n_set (mat, j, i, (gfloat) g_test_rand_double ());
		}
	}
}

static void
test_gen_mat_float_n_pd (CrankMatFloatN* mat)
{
	guint i;
	guint j;
	
	CrankMatFloatN	a;
	CrankMatFloatN	b;
	
	crank_mat_float_n_init_fill (&a, N, N, 0.0f);
	crank_mat_float_n_init_fill (&b, N, N, 0.0f);
	
	for (i = 0; i < N; i++) {
		gfloat	e = (gfloat) g_test_rand_double ();
		gfloat	ep = ABS (e) + 1;
		crank_mat_float_n_set (&a, i, i, ep);
		crank_mat_float_n_set (&b, i, i, ep);
		
		for (j = i + 1; j < N; j++) {
			e = (gfloat) g_test_rand_double ();
			ep = ABS (e) + 1;
			crank_mat_float_n_set (&a, i, j, ep);
			crank_mat_float_n_set (&b, j, i, ep);
		}
	}
	
	crank_mat_float_n_mul (&a, &b, mat);
}

static void
test_gen_mat_float_4 (CrankMatFloat4* mat)
{
	guint i;
	gfloat*	matp = (gfloat*) mat;
	
	for (i = 0; i < 16; i++) matp[i] = g_test_rand_double ();
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

static void
test_mat4_mul (void)
{
	guint i;
	guint j;
	
	for (i = 0; i < R; i++) {
		CrankMatFloat4*	mats = g_new (CrankMatFloat4, N);
		CrankMatFloat4 res = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
		
		for (j = 0; j < N; j++) {
			test_gen_mat_float_4 (mats + j);
		}
		
		g_test_timer_start ();
		
		for (j = 0; j < N; j++) crank_mat_float4_mul_self (&res, mats + j);
		
		g_test_minimized_result ( g_test_timer_elapsed (), "mul4");
		
		g_free (mats);
	}
}

static void
test_mat_lu (void)
{
	guint i;
	
	for (i = 0; i < R; i++) {
		CrankMatFloatN	a;
		CrankMatFloatN	b;
		CrankMatFloatN	c;
			
		test_gen_mat_float_n (&a);
		
		g_test_timer_start ();
		
		crank_lu_mat_float_n (&a, &b, &c);
		
		g_test_minimized_result ( g_test_timer_elapsed (), "lu");
		
		crank_mat_float_n_fini (&a);
		crank_mat_float_n_fini (&b);
		crank_mat_float_n_fini (&c);
	}
}

static void
test_mat_gram_schmidt (void)
{
	guint i;
	
	for (i = 0; i < R; i++) {
		CrankMatFloatN	a = {0};
		CrankMatFloatN	b = {0};
		CrankMatFloatN	c = {0};
			
		test_gen_mat_float_n (&a);
		
		g_test_timer_start ();
		
		if (! crank_gram_schmidt_mat_float_n (&a, &b, &c)) {
			g_test_message ("QR decomp failed! This means that generation may have isssues.");
		}
		
		g_test_minimized_result ( g_test_timer_elapsed (), "qr-gram-schmidt");
		
		crank_mat_float_n_fini (&a);
		crank_mat_float_n_fini (&b);
		crank_mat_float_n_fini (&c);
	}
}

static void
test_mat_householder (void)
{
	guint i;
	
	for (i = 0; i < R; i++) {
		CrankMatFloatN	a = {0};
		CrankMatFloatN	b = {0};
			
		test_gen_mat_float_n (&a);
		
		g_test_timer_start ();
		
		if (! crank_qr_householder_mat_float_n (&a, &b)) {
			g_test_message ("QR decomp failed! This means that generation may have isssues.");
		}
		
		g_test_minimized_result ( g_test_timer_elapsed (), "qr-householder");
		
		crank_mat_float_n_fini (&a);
		crank_mat_float_n_fini (&b);
	}
}

static void
test_mat_givens (void)
{
	guint i;
	
	for (i = 0; i < R; i++) {
		CrankMatFloatN	a = {0};
		CrankMatFloatN	b = {0};
			
		test_gen_mat_float_n (&a);
		
		g_test_timer_start ();
		
		if (! crank_qr_givens_mat_float_n (&a, &b)) {
			g_test_message ("QR decomp failed! This means that generation may have isssues.");
		}
		
		g_test_minimized_result ( g_test_timer_elapsed (), "qr-givens");
		
		crank_mat_float_n_fini (&a);
		//crank_mat_float_n_fini (&b);
	}
}
