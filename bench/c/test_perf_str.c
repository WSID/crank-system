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

#include <stdlib.h>
#include <glib.h>

#include "crankbase.h"

//////// Declaration ///////////////////////////////////////////////////////////

static gchar *test_gen_double_strings (CrankBenchRun *run,
                                       gdouble **array);

static void   bench_read_double (CrankBenchRun *run);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint   argc,
      gchar *argv[])
{
  CrankBenchParamNode  *params;

  crank_bench_init (&argc, &argv);

  crank_bench_add ("/crank/base/string/read/double",
                   (CrankBenchFunc)bench_read_double, NULL, NULL);

  params = crank_bench_param_node_new ();

  crank_bench_param_node_set_uint (params, "repeat", 8);
  crank_bench_param_node_set_uint (params, "N", 10240);

  crank_bench_set_param ("/", params);

  crank_bench_param_node_free (params);

  return crank_bench_run ();
}


//////// Definition ////////////////////////////////////////////////////////////

static gchar*
test_gen_double_string (CrankBenchRun *run, gdouble **array)
{
  guint n;
  guint i;
  gdouble *marray;
  gchar *strs;
  GString *str;

  n = crank_bench_run_get_param_uint (run, "N", 0);

  marray = g_new (gdouble, n);
  str = g_string_new (NULL);

  for (i = 0; i < n; i++)
    {
      gint32 value_int = crank_bench_run_rand_int_range (run, -1000000000, 1000000000);
      gdouble value_double = ((gdouble)value_int) / 10000000000;
      marray[i] = value_double;

      g_string_append_printf (str, "%0.8g   ", value_double);
    }


  *array = marray;
  strs = str->str;
  g_string_free (str, FALSE);

  return strs;
}


static void
bench_read_double (CrankBenchRun *run)
{
  guint i;
  guint n;
  gdouble *actual_value;
  gdouble *crank_value;
  gdouble *std_value;

  gdouble crank_errsum = 0;
  gdouble std_errsum = 0;

  gchar *str;

  n = crank_bench_run_get_param_uint (run, "N", 0);

  str = test_gen_double_string (run, &actual_value);
  crank_value = g_new (gdouble, n);
  std_value = g_new (gdouble, n);


  crank_bench_run_timer_start (run);
  {
    gchar *ptr = str;
    for (i = 0; i < n; i++)
      {
        std_value[i] = strtod (ptr, &ptr);
        if (std_value[i] == 0)
          {
            g_test_fail ();
            return;
          }
      }
  }
  crank_bench_run_timer_add_result_elapsed (run, "std-read-double");

  crank_bench_run_timer_start (run);
  {
    guint pos = 0;
    CrankReadDecResult res;
    gdouble err;
    for (i = 0; i < n; i++)
      {
        if (!crank_str_scan_double (str, &pos, crank_value + i,
                                    &res) || (res != 0))
          {
            g_test_fail ();
            return;
          }
      }

  }
  crank_bench_run_timer_add_result_elapsed (run, "crank-read-double");

  for (i = 0; i < n; i++)
    {
      crank_errsum += ABS((actual_value[i] / crank_value[i]) - 1);
      std_errsum += ABS((actual_value[i] / std_value[i]) - 1);
    }
  crank_bench_run_add_result_double (run, "crank-read-double-err", crank_errsum / n);
  crank_bench_run_add_result_double (run, "std-read-double-err", std_errsum / n);

  g_free (str);
  g_free (actual_value);
  g_free (crank_value);
  g_free (std_value);
}
