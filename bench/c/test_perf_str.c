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

//////// Testing Variables /////////////////////////////////////////////////////

static guint N   = 4096;
static guint R   = 8;


//////// Declaration ///////////////////////////////////////////////////////////

typedef void (*BenchFunc) (gpointer userdata);

struct TestPayloadBench {
  BenchFunc func;
  gpointer user_data;
};

static void   test_add_bench (const gchar *path,
                              BenchFunc    bench,
                              gpointer     user_data);
static void   test_meta_bench (gconstpointer data);

static gchar *test_gen_double_strings (void);

static void   bench_read_double (void);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint   argc,
      gchar *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_message ("N: %u", N);
  g_test_message ("R: %u", R);

  test_add_bench ("/crank/base/string/perf/read/double",
                  (BenchFunc)bench_read_double, NULL);

  g_test_run ();

  return 0;
}


//////// Definition ////////////////////////////////////////////////////////////
static void
test_add_bench (const gchar *test_path,
                BenchFunc    bench,
                gpointer     user_data)
{
  struct TestPayloadBench *payload = g_new (struct TestPayloadBench, 1);

  payload->func = bench;
  payload->user_data = user_data;

  g_test_add_data_func_full (test_path, payload, test_meta_bench, g_free);
}

static void
test_meta_bench (gconstpointer user_data)
{
  guint i;

  struct  TestPayloadBench *payload = (struct TestPayloadBench*)user_data;

  for (i = 0; i < R; i++)
    payload->func (payload->user_data);
}

static gchar*
test_gen_double_string (gdouble **array)
{
  guint i;
  gdouble *marray;
  gchar *strs;
  GString *str;

  marray = g_new (gdouble, N);
  str = g_string_new (NULL);

  for (i = 0; i < N; i++)
    {
      gint value_int = g_test_rand_int_range (-1000000000, 1000000000);
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
bench_read_double (void)
{
  guint i;
  gdouble *actual_value;
  gdouble *crank_value;
  gdouble *std_value;

  gdouble crank_errsum = 0;
  gdouble std_errsum = 0;

  gchar *str;

  str = test_gen_double_string (&actual_value);
  crank_value = g_new (gdouble, N);
  std_value = g_new (gdouble, N);


  g_test_timer_start ();
  {
    gchar *ptr = str;
    for (i = 0; i < N; i++)
      {
        std_value[i] = strtod (ptr, &ptr);
        if (std_value[i] == 0)
          {
            g_test_fail ();
            return;
          }
      }
  }
  g_test_minimized_result (g_test_timer_elapsed (), "std_read_double");

  g_test_timer_start ();
  {
    guint pos = 0;
    CrankReadDecResult res;
    gdouble err;
    for (i = 0; i < N; i++)
      {
        if (!crank_str_scan_double (str, &pos, crank_value + i,
                                    &res) || (res != 0))
          {
            g_test_fail ();
            return;
          }
      }

  }

  g_test_minimized_result (g_test_timer_elapsed (), "crank_read_double");

  for (i = 0; i < N; i++)
    {
      crank_errsum += ABS((actual_value[i] / crank_value[i]) - 1);
      std_errsum += ABS((actual_value[i] / std_value[i]) - 1);
    }
  g_test_minimized_result (crank_errsum / N, "crank_read_double_err");
  g_test_minimized_result (std_errsum / N, "std_read_double_err");

  g_free (str);
  g_free (actual_value);
  g_free (crank_value);
  g_free (std_value);
}