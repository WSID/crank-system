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
//
static void test_gen_mat_float_n (CrankBenchRun *run, CrankMatFloatN *mat);
static void test_gen_mat_float_n_sym (CrankBenchRun *run, CrankMatFloatN *mat);
static void test_gen_mat_float_4 (CrankBenchRun *run, CrankMatFloat4 *mat);

static void bench_mat_slice4 (CrankBenchRun *run);
static void bench_mat_transpose (CrankBenchRun *run);
static void bench_mat_mul (CrankBenchRun *run);
static void bench_mat_inv (CrankBenchRun *run);
static void bench_mat4_mul (CrankBenchRun *run);

static void bench_mat_lu (CrankBenchRun *run);
static void bench_mat_ch (CrankBenchRun *run);
static void bench_mat_ldl (CrankBenchRun *run);
static void bench_mat_gram_schmidt (CrankBenchRun *run);
static void bench_mat_householder (CrankBenchRun *run);
static void bench_mat_givens (CrankBenchRun *run);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint   argc,
      gchar *argv[])
{
  CrankBenchParamNode  *params;
  CrankBenchParamNode **vparams;

  crank_bench_init (&argc, &argv);


  // Fill parameters
  params = crank_bench_param_node_new ();

  crank_bench_param_node_set_uint (params, "repeat", 8);
  crank_bench_param_node_set_uint (params, "N", 128);

  vparams = crank_bench_param_node_add_placeholders (params, 3);
  crank_bench_param_node_set_uint (vparams[0], "N", 256);
  crank_bench_param_node_set_uint (vparams[1], "N", 512);

  crank_bench_param_node_set_uint (vparams[2], "repeat", 2);
  crank_bench_param_node_set_uint (vparams[2], "N", 1024);
  vparams = crank_bench_param_node_add_placeholders (vparams[2], 2);
  crank_bench_param_node_set_uint (vparams[0], "N", 2048);
  crank_bench_param_node_set_uint (vparams[1], "N", 4096);


  crank_bench_add ("/crank/base/mat/float/n/bench/slice4",
                   (CrankBenchFunc)bench_mat_slice4, NULL, NULL);
  crank_bench_add ("/crank/base/mat/float/n/bench/transpose",
                   (CrankBenchFunc)bench_mat_transpose, NULL, NULL);
  crank_bench_add ("/crank/base/mat/float/n/bench/mul",
                   (CrankBenchFunc)bench_mat_mul, NULL, NULL);
  crank_bench_add ("/crank/base/mat/float/n/bench/inv",
                   (CrankBenchFunc)bench_mat_inv, NULL, NULL);
  crank_bench_add ("/crank/base/mat/float/4/bench/mul",
                   (CrankBenchFunc)bench_mat4_mul, NULL, NULL);

  crank_bench_add ("/crank/base/mat/float/n/bench/lu",
                   (CrankBenchFunc)bench_mat_lu, NULL, NULL);
  crank_bench_add ("/crank/base/mat/float/n/bench/ch",
                   (CrankBenchFunc)bench_mat_ch, NULL, NULL);
  crank_bench_add ("/crank/base/mat/float/n/bench/ldl",
                   (CrankBenchFunc)bench_mat_ldl, NULL, NULL);
  crank_bench_add ("/crank/base/mat/float/n/bench/qr/gram-schmidt",
                   (CrankBenchFunc)bench_mat_gram_schmidt, NULL, NULL);
  //test_add_bench ("/crank/base/mat/float/n/perf/qr/householder",
  //		(BenchFunc)bench_mat_householder, NULL	);
  // We don't use it for now.
  // This will take so long, as slicing out a matrix.
  crank_bench_add ("/crank/base/mat/float/n/bench/qr/givens",
                  (CrankBenchFunc)bench_mat_givens, NULL, NULL);

  // We don't do bench for eval algorithms for now.
  // The algorithms might be failing/ or may have different time to finish by
  // matrix, which is randomly generated.
  //
  // Benchmarking them might meanning-less unless we have optimization like
  // eigenvalue shifting, etc..

  crank_bench_set_param ("/", params);

  return crank_bench_run ();
}


//////// Definition ////////////////////////////////////////////////////////////


static void
test_gen_mat_float_n (CrankBenchRun  *run,
                      CrankMatFloatN *mat)
{
  guint i;
  guint n = crank_bench_run_get_param_uint (run, "N", 4);

  crank_mat_float_n_init_arr_take (mat, n, n,
                                   crank_bench_run_rand_float_array (run, n*n));
}

static void
test_gen_mat_float_n_sym (CrankBenchRun  *run,
                          CrankMatFloatN *mat)
{
  guint i;
  guint j;
  guint n = crank_bench_run_get_param_uint (run, "N", 4);

  crank_mat_float_n_init_fill (mat, n, n, 0.0f);

  for (i = 0; i < n; i++)
    {
      crank_mat_float_n_set (mat, i, i, crank_bench_run_rand_float (run));

      for (j = i + 1; j < n; j++)
        {
          crank_mat_float_n_set (mat, i, j, crank_bench_run_rand_float (run));
          crank_mat_float_n_set (mat, j, i, crank_bench_run_rand_float (run));
        }
    }
}

static void
test_gen_mat_float_n_pd (CrankBenchRun  *run,
                         CrankMatFloatN *mat)
{
  guint i;
  guint n = crank_bench_run_get_param_uint (run, "N", 4);

  CrankMatFloatN a;

  crank_mat_float_n_init_fill (&a, n, n, 0.0f);

  test_gen_mat_float_n (run, &a);

  for (i = 0; i < n; i++)
    {
      gfloat *ep = a.data + (i * (n + 1));
      gfloat e = *ep;

      *ep = ABS (e) + 1.0f;
    }

  crank_mat_float_n_transpose (&a, mat);
  crank_mat_float_n_mul_self (mat, &a);
  crank_mat_float_n_fini (&a);
}

static void
test_gen_mat_float_4 (CrankBenchRun  *run,
                      CrankMatFloat4 *mat)
{
  guint i;
  gfloat *matp = (gfloat*) mat;

  for (i = 0; i < 16; i++)
    matp[i] = crank_bench_run_rand_float (run);
}





static void
bench_mat_slice4 (CrankBenchRun *run)
{
  guint N = crank_bench_run_get_param_uint (run, "N", 4);

  CrankMatFloatN a;
  CrankMatFloatN s[4];
  guint hn = N / 2;

  test_gen_mat_float_n (run, &a);

  crank_bench_run_timer_start (run);

  crank_mat_float_n_slice (&a, 0, 0, hn, hn, s + 0);
  crank_mat_float_n_slice (&a, hn, 0, N, hn, s + 1);
  crank_mat_float_n_slice (&a, 0, hn, hn, N, s + 2);
  crank_mat_float_n_slice (&a, hn, hn, N, N, s + 3);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (s + 0);
  crank_mat_float_n_fini (s + 1);
  crank_mat_float_n_fini (s + 2);
  crank_mat_float_n_fini (s + 3);
}



static void
bench_mat_transpose (CrankBenchRun *run)
{
  CrankMatFloatN a;
  CrankMatFloatN b;

  test_gen_mat_float_n (run, &a);

  crank_bench_run_timer_start (run);

  crank_mat_float_n_transpose (&a, &b);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
}


static void
bench_mat_mul (CrankBenchRun *run)
{
  CrankMatFloatN a;
  CrankMatFloatN b;
  CrankMatFloatN c;

  test_gen_mat_float_n (run, &a);
  test_gen_mat_float_n (run, &b);

  crank_bench_run_timer_start (run);

  crank_mat_float_n_mul (&a, &b, &c);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&c);
}


static void
bench_mat_inv (CrankBenchRun *run)
{
  CrankMatFloatN a;
  CrankMatFloatN b;

  test_gen_mat_float_n (run, &a);

  crank_bench_run_timer_start (run);

  crank_mat_float_n_inverse (&a, &b);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
}

static void
bench_mat4_mul (CrankBenchRun *run)
{
  guint j;
  guint n;

  n = crank_bench_run_get_param_uint (run, "N", 0);

  CrankMatFloat4 *mats = g_new (CrankMatFloat4, n);
  CrankMatFloat4 res = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };

  for (j = 0; j < n; j++)
    test_gen_mat_float_4 (run, mats + j);

  crank_bench_run_timer_start (run);

  for (j = 0; j < n; j++)
    crank_mat_float4_mul_self (&res, mats + j);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  g_free (mats);
}

static void
bench_mat_lu (CrankBenchRun *run)
{
  CrankMatFloatN a;
  CrankMatFloatN b;
  CrankMatFloatN c;

  test_gen_mat_float_n (run, &a);

  crank_bench_run_timer_start (run);

  crank_lu_mat_float_n (&a, &b, &c);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&c);
}

static void
bench_mat_ch (CrankBenchRun *run)
{
  gboolean res;
  CrankMatFloatN a;
  CrankMatFloatN b;

  test_gen_mat_float_n_pd (run, &a);

  crank_bench_run_timer_start (run);

  res = crank_ch_mat_float_n (&a, &b);

  crank_bench_run_timer_add_result_elapsed (run, "time");


  if (!res)
    crank_bench_run_fail (run,
      "Cholesky decomp failed! This means that generation may have isssues.");
  else
    crank_mat_float_n_fini (&b);

  crank_mat_float_n_fini (&a);
}

static void
bench_mat_ldl (CrankBenchRun *run)
{
  gboolean res;
  CrankMatFloatN a;
  CrankMatFloatN b;
  CrankVecFloatN c;

  test_gen_mat_float_n_pd (run, &a);

  crank_bench_run_timer_start (run);

  res = crank_ldl_mat_float_n (&a, &b, &c);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  if (!res)
    crank_bench_run_fail (run,
      "LDLT decomp failed! This means that generation may have isssues.");
  else
    {
      crank_mat_float_n_fini (&b);
      crank_vec_float_n_fini (&c);
    }

  crank_mat_float_n_fini (&a);
}


static void
bench_mat_gram_schmidt (CrankBenchRun *run)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};
  CrankMatFloatN c = {0};

  test_gen_mat_float_n (run, &a);

  crank_bench_run_timer_start (run);

  if (!crank_gram_schmidt_mat_float_n (&a, &b, &c))
    {
      crank_bench_run_fail (run,
        "QR decomp failed! This means that generation may have isssues.");
    }

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&c);
}

static void
bench_mat_householder (CrankBenchRun *run)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};

  test_gen_mat_float_n (run, &a);

  crank_bench_run_timer_start (run);

  if (!crank_qr_householder_mat_float_n (&a, &b))
    {
      crank_bench_run_fail (run,
        "QR decomp failed! This means that generation may have isssues.");
    }

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
}

static void
bench_mat_givens (CrankBenchRun *run)
{
  guint i;

  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};

  test_gen_mat_float_n (run, &a);

  crank_bench_run_timer_start (run);

  if (!crank_qr_givens_mat_float_n (&a, &b))
    {
      crank_bench_run_fail (run,
         "QR decomp failed! This means that generation may have isssues.");
    }

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_mat_float_n_fini (&a);
  //crank_mat_float_n_fini (&b);
}
