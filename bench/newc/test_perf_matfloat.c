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

//////// Declaration ///////////////////////////////////////////////////////////

static void test_gen_mat_float_n (CrankBenchRun *run, CrankMatFloatN *mat);

static void bench_mat_slice4 (CrankBenchRun *run);

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


  // Add Benchmark cases
  crank_bench_add ("/crank/base/mat/float/n/bench/slice4",
                   (CrankBenchFunc)bench_mat_slice4, NULL, NULL);

  crank_bench_set_param ("/", params);

  crank_bench_run ();

  return 0;
}


//////// Definition ////////////////////////////////////////////////////////////


static void
test_gen_mat_float_n (CrankBenchRun  *run,
                      CrankMatFloatN *mat)
{
  guint i;
  guint N = crank_bench_run_get_param_uint (run, "N", 4);

  crank_mat_float_n_init_fill (mat, N, N, 0.0f);

  for (i = 0; i < N * N; i++)
    {
      mat->data[i] = crank_bench_run_rand_double (run);
    }
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

