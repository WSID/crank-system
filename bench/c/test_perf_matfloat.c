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
static guint		R	= 4;


//////// Declaration ///////////////////////////////////////////////////////////

typedef void	(*BenchFunc) (gpointer	userdata);

struct TestPayloadBench {
	BenchFunc	func;
	gpointer	user_data;
};

static void test_add_bench (			const gchar*	path,
										BenchFunc		bench,
										gpointer		user_data	);
static void	test_meta_bench (			gconstpointer	data	);

static void test_gen_mat_float_n (		CrankMatFloatN* mat);
static void test_gen_mat_float_n_sym (	CrankMatFloatN* mat);
static void	test_gen_mat_float_4 (		CrankMatFloat4* mat);

static void bench_mat_mul (void);
static void bench_mat_inv (void);
static void bench_mat4_mul (void);

static void bench_mat_lu (void);
static void bench_mat_ch (void);
static void bench_mat_gram_schmidt (void);
static void bench_mat_householder (void);
static void bench_mat_givens (void);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_message ("N: %u", N);
	g_test_message ("R: %u", R);
	
	test_add_bench ("/crank/base/mat/float/n/bench/mul",
			(BenchFunc)bench_mat_mul, NULL);
	test_add_bench ("/crank/base/mat/float/n/bench/inv",
			(BenchFunc)bench_mat_inv, NULL);
	test_add_bench ("/crank/base/mat/float/4/bench/mul",
			(BenchFunc)bench_mat4_mul, NULL);
			
	test_add_bench ("/crank/base/mat/float/n/bench/lu",
			(BenchFunc)bench_mat_lu, NULL	);
	test_add_bench ("/crank/base/mat/float/n/bench/ch",
			(BenchFunc)bench_mat_ch, NULL	);
	test_add_bench ("/crank/base/mat/float/n/bench/qr/gram-schmidt",
			(BenchFunc)bench_mat_gram_schmidt, NULL	);
	//test_add_bench ("/crank/base/mat/float/n/perf/qr/householder",
	//		(BenchFunc)bench_mat_householder	);
	// We don't use it for now.
	// This will take so long, as slicing out a matrix.
	test_add_bench ("/crank/base/mat/float/n/bench/qr/givens",
			(BenchFunc)bench_mat_givens, NULL	);
			
	// We don't do bench for eval algorithms for now.
	// The algorithms might be failing/ or may have different time to finish by
	// matrix, which is randomly generated.
	//
	// Benchmarking them might meanning-less unless we have optimization like
	// eigenvalue shifting, etc..
	
	g_test_run ();

	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////
static void
test_add_bench (	const gchar*	test_path,
					BenchFunc		bench,
					gpointer		user_data	)
{
	struct TestPayloadBench*	payload = g_new (struct TestPayloadBench, 1);
	
	payload->func = bench;
	payload->user_data = user_data;
	
	g_test_add_data_func_full ( test_path, payload, test_meta_bench, g_free );
}

static void
test_meta_bench (	gconstpointer	user_data	)
{
	guint i;
	
	struct	TestPayloadBench*	payload = (struct TestPayloadBench*)user_data;
	
	for (i = 0; i < R; i++) payload->func (payload->user_data);
}



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
	
	CrankMatFloatN	a;
	
	crank_mat_float_n_init_fill (&a, N, N, 0.0f);
	
	test_gen_mat_float_n (&a);
	
	for (i = 0; i < N; i++) {
		gfloat*	ep = a.data + (i * (N + 1));
		gfloat e = *ep;
		
		*ep = ABS (e) + 1.0f;
	}
	
	crank_mat_float_n_transpose (&a, mat);
	crank_mat_float_n_mul_self (mat, &a);
	crank_mat_float_n_fini (&a);
}

static void
test_gen_mat_float_4 (CrankMatFloat4* mat)
{
	guint i;
	gfloat*	matp = (gfloat*) mat;
	
	for (i = 0; i < 16; i++) matp[i] = g_test_rand_double ();
}


static void
bench_mat_mul (void)
{
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


static void
bench_mat_inv (void)
{
	CrankMatFloatN	a;
	CrankMatFloatN	b;
		
	test_gen_mat_float_n (&a);
	
	g_test_timer_start ();
	
	crank_mat_float_n_inverse (&a, &b);
	
	g_test_minimized_result ( g_test_timer_elapsed (), "mul");
	
	crank_mat_float_n_fini (&a);
	crank_mat_float_n_fini (&b);
}

static void
bench_mat4_mul (void)
{
	guint j;
	
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

static void
bench_mat_lu (void)
{
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

static void
bench_mat_ch (void)
{
	gboolean		res;
	CrankMatFloatN	a;
	CrankMatFloatN	b;
	
	test_gen_mat_float_n_pd (&a);

	g_test_timer_start ();

	res = crank_ch_mat_float_n (&a, &b);

	g_test_minimized_result ( g_test_timer_elapsed (), "ch");

	if (!res)
		g_test_message ("Cholesky decomp failed! This means that generation may have isssues.");
	else crank_mat_float_n_fini (&b);

	crank_mat_float_n_fini (&a);
}


static void
bench_mat_gram_schmidt (void)
{
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

static void
bench_mat_householder (void)
{
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

static void
bench_mat_givens (void)
{
	guint i;
	
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
