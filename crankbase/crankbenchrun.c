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

#define _CRANKBASE_INSIDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>

#include "crankbasemacro.h"
#include "crankbasemisc.h"
#include "crankvalue.h"
#include "crankstring.h"
#include "crankbench.h"
#include "crankbenchrun.h"

/**
 * SECTION:crankbenchrun
 * @title: Benchmark Run
 * @short_description: Run state for benchmarking.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * This represents state of benchmarking.
 *
 * Benchmark parameters can be obtained through crank_bench_run_get_param()
 * family. Results can be added by crank_bench_run_add_result() family.
 *
 * #CrankBenchRun also has utility functions like random generations, timer.
 *
 * # Getting results.
 *
 * After postprocessing, results can be obtained crank_bench_run_get_result()
 * family. For convenience, not only string and #GQuark, but array of them are
 * also avaliable, for getting result and parameters.
 *
 * Results are added in queue and won't be available before postprocessing.
 */


typedef struct _CrankBenchResultEntry {
  GQuark   name;
  GValue   value;
} CrankBenchResultEntry;


/**
 * CrankBenchRun:
 *
 * A structure represents a running benchmark.
 */
struct _CrankBenchRun {
  /*<private>*/
  CrankBenchCase       *bcase;
  guint                 runno;
  CrankBenchRunState    state;
  CrankBenchRunMark     mark;
  gchar                *message;

  gconstpointer         _PADDING5;
  gconstpointer         _PADDING6;
  gconstpointer         _PADDING7;

  GQueue               *result_journal;
  GHashTable           *param;

  gconstpointer         _PADDING10;
  gconstpointer         _PADDING11;

  GTimer               *timer_run;
  GTimer               *timer_user;
  GRand                *random;

  gconstpointer         _PADDING15;
  gconstpointer         _PADDING16;
  gconstpointer         _PADDING17;
  gconstpointer         _PADDING18;
  gconstpointer         _PADDING19;


  GHashTable           *result;

  gconstpointer         _PADDING21;
  gconstpointer         _PADDING22;
  gconstpointer         _PADDING23;
};


//////// CrankBenchRun /////////////////////////////////////////////////////////



/**
 * crank_bench_run_new: (skip)
 * @bcase: (transfer none): A Benchmark case.
 * @param: (transfer none): Parameters for benchmark.
 * @run_no: Run number.
 *
 * Creates a benchmark run for @run_no th run, with @param.
 *
 * Retunrs: (transfer full): A Benchmark run.
 */
CrankBenchRun*
crank_bench_run_new (CrankBenchCase *bcase,
                      GHashTable     *param,
                      const guint     run_no)
{
  CrankBenchRun *run = g_slice_new (CrankBenchRun);

  run->bcase = bcase;
  run->runno = run_no;
  run->state = CRANK_BENCH_RUN_NOT_RUN;
  run->mark = CRANK_BENCH_RUN_SUCCESS;
  run->message = NULL;

  run->param = g_hash_table_ref (param);
  run->result_journal = g_queue_new ();

  run->timer_run = g_timer_new ();
  run->timer_user = g_timer_new ();

  run->random = g_rand_new ();

  run->result = NULL;

  return run;
}


/**
 * crank_bench_run_free:
 * @run: A Benchmark run.
 *
 * Frees a benchmark run.
 */
void
crank_bench_run_free (CrankBenchRun *run)
{
  g_free (run->message);

  g_hash_table_unref (run->param);

  while (! g_queue_is_empty (run->result_journal))
    g_slice_free (CrankBenchResultEntry, g_queue_pop_tail (run->result_journal));
  g_queue_free (run->result_journal);

  g_timer_destroy (run->timer_run);
  g_timer_destroy (run->timer_user);

  g_rand_free (run->random);

  g_hash_table_unref (run->result);

  g_slice_free (CrankBenchRun, run);
}

/**
 * crank_bench_run_get_run_no: (skip)
 * @run: A Benchmark run.
 *
 * Get run number of this run. This is 0 for first repeat, and so on.
 *
 * Returns: Repeat numbers.
 */
guint
crank_bench_run_get_run_no (CrankBenchRun *run)
{
  return run->runno;
}

/**
 * crank_bench_run_is_running: (skip)
 * @run: A benchmark run.
 *
 * Gets whether this run is running.
 *
 * Returns: Whether this run is running.
 */
gboolean
crank_bench_run_is_running (CrankBenchRun *run)
{
  return run->state == CRANK_BENCH_RUN_RUNNING;
}

/**
 * crank_bench_run_is_processed: (skip)
 * @run: A benchmark run.
 *
 * Gets whether this run is processed, and its result is available.
 *
 * Returns: Whether this run is processed.
 */
gboolean
crank_bench_run_is_processed (CrankBenchRun *run)
{
  return run->state == CRANK_BENCH_RUN_PROCESSED;
}

/**
 * crank_bench_run_is_failed: (skip)
 * @run: A Benchmark run.
 *
 * Gets whether this run is marked failure.
 *
 * Returns: Whether this run is failed.
 */
gboolean
crank_bench_run_is_failed (CrankBenchRun *run)
{
  return run->state == CRANK_BENCH_RUN_FAIL;
}

/**
 * crank_bench_run_is_skipped: (skip)
 * @run: A Benchmark run.
 *
 * Gets whether this run is marked skip.
 *
 * Returns: Whether this run is skipped.
 */
gboolean
crank_bench_run_is_skipped (CrankBenchRun *run)
{
  return run->state == CRANK_BENCH_RUN_SKIP;
}

/**
 * crank_bench_run_get_state: (skip)
 * @run: A Benchmark run.
 *
 * Gets state of this run.
 *
 * Returns: State of this run.
 */
CrankBenchRunState
crank_bench_run_get_state (CrankBenchRun *run)
{
  return run->state;
}

/**
 * crank_bench_run_get_mark: (skip)
 * @run: A Benchmark run.
 *
 * Gets mark of this run. As this is benchmarking, generally it should be
 * %CRANK_BENCH_RUN_SUCCESS.
 *
 * Returns: Mark of this run.
 */
CrankBenchRunMark
crank_bench_run_get_mark (CrankBenchRun *run)
{
  return run->mark;
}

/**
 * crank_bench_run_get_message: (skip)
 * @run: A Benchmark run.
 *
 * Gets message on this run, if it was not succesful.
 *
 * Returns: (nullable) (transfer none): Message on the run or %NULL, if it was
 *     succesful.
 */
gchar*
crank_bench_run_get_message (CrankBenchRun *run)
{
  return run->message;
}

/**
 * crank_bench_run_skip: (skip)
 * @run: A benchmark run.
 * @message: A message for skipping.
 *
 * Marks this run as skipped.
 *
 * This is only allowed before or during benchmark, and have not been marked.
 *
 * Exceptionally, multiple call of this functions are allowed.
 */
void
crank_bench_run_skip (CrankBenchRun *run,
                      const gchar   *message)
{
  crank_bench_run_set_mark (run, CRANK_BENCH_RUN_SKIP, message);
}

/**
 * crank_bench_run_fail: (skip)
 * @run: A benchmark run.
 * @message: A message for failing.
 *
 * Marks this run as failed.
 *
 * This is only allowed before or during benchmark, and have not been marked.
 *
 * Exceptionally, multiple call of this functions are allowed.
 *
 * This does not finish calling function, so that function itself can produce
 * more information before returning.
 *
 * Note that this is benchmarking, failing benchmarking should not happened
 * frequently, as bugs should be caught in unit tests or etc.
 */
void
crank_bench_run_fail (CrankBenchRun *run,
                      const gchar   *message)
{
  crank_bench_run_set_mark (run, CRANK_BENCH_RUN_FAIL, message);
}

/**
 * crank_bench_run_set_mark: (skip)
 * @run: A benchmark run.
 * @mark: A mark.
 * @message: A message for mark.
 *
 * Set mark for benchmark.
 *
 * This is only allowed before or during benchmark, and have not been marked.
 *
 * Exceptionally, marking for same mark is allowed.
 *
 * This does not finish calling function, so that function itself can produce
 * more information before returning.
 */
void
crank_bench_run_set_mark (CrankBenchRun     *run,
                          CrankBenchRunMark  mark,
                          const gchar       *message)
{
  gchar *path;
  switch (run->state)
    {
    case CRANK_BENCH_RUN_NOT_RUN:
    case CRANK_BENCH_RUN_RUNNING:
      break;

    case CRANK_BENCH_RUN_FINISHED:
      path = crank_bench_case_get_path (run->bcase);
      g_error ("Marking on already finished run: %s", path);
      g_free (path);
      return;

    case CRANK_BENCH_RUN_PROCESSED:
      path = crank_bench_case_get_path (run->bcase);
      g_error ("Marking on already processed run: %s", path);
      g_free (path);
      return;
    }

  if (run->mark == CRANK_BENCH_RUN_SUCCESS)
    {
      run->mark = mark;
      run->message = g_strdup (message);
    }

  else if (run->mark != mark)
    {
      path = crank_bench_case_get_path (run->bcase);
      g_error ("Marking already marked run: %s", path);
      g_free (path);
    }
}

/**
 * crank_bench_run_get_params: (skip)
 * @run: A benchmark run.
 *
 * Gets benchmark parameters as #GHashTable<#GQuark, #GValue*>
 *
 * Returns: (transfer none) (element-type GQuark GValue):
 *     benchmark parameters.
 */
GHashTable*
crank_bench_run_get_params (CrankBenchRun *run)
{
  return run->param;
}

/**
 * crank_bench_run_get_param: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 *
 * Gets a benchmark parameter by @name.
 *
 * Returns: (transfer none) (nullable): A benchmark parameter as #GValue. or
 *     %NULL if fail.
 */
GValue*
crank_bench_run_get_param (CrankBenchRun *run,
                           const gchar   *name)
{
  GQuark qname = g_quark_try_string (name);

  return (GValue*) g_hash_table_lookup (run->param, GINT_TO_POINTER(qname));
}

/**
 * crank_bench_run_get_param_int: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets integer benchmark parameter by @name.
 *
 * Returns: A integer benchmark parameter, or @defval if fail.
 */
gint
crank_bench_run_get_param_int (CrankBenchRun *run,
                               const gchar   *name,
                               const gint     defval)
{
  GQuark qname = g_quark_try_string (name);
  return crank_value_table_get_int (run->param, GINT_TO_POINTER(qname), defval);
}

/**
 * crank_bench_run_get_param_uint: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets unsigned integer benchmark parameter by @name.
 *
 * Returns: A unsigned integer benchmark parameter, or @defval if fail.
 */
guint
crank_bench_run_get_param_uint (CrankBenchRun *run,
                                const gchar   *name,
                                const guint    defval)
{
  GQuark qname = g_quark_try_string (name);
  return crank_value_table_get_uint (run->param, GINT_TO_POINTER(qname), defval);
}

/**
 * crank_bench_run_get_param_float: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets float benchmark parameter by @name.
 *
 * Returns: A float benchmark parameter, or @defval if fail.
 */
gfloat
crank_bench_run_get_param_float (CrankBenchRun *run,
                                 const gchar   *name,
                                 const gfloat   defval)
{
  GQuark qname = g_quark_try_string (name);
  return crank_value_table_get_float (run->param, GINT_TO_POINTER(qname), defval);
}

/**
 * crank_bench_run_get_param_double: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets double benchmark parameter by @name.
 *
 * Returns: A double benchmark parameter, or @defval if fail.
 */
gdouble
crank_bench_run_get_param_double (CrankBenchRun *run,
                                  const gchar   *name,
                                  const gdouble  defval)
{
  GQuark qname = g_quark_try_string (name);
  return crank_value_table_get_double (run->param, GINT_TO_POINTER(qname), defval);
}



/**
 * crank_bench_run_getq_param: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 *
 * Gets a benchmark parameter by @name.
 *
 * Returns: (transfer none) (nullable): A benchmark parameter as #GValue. or
 *     %NULL if fail.
 */
GValue*
crank_bench_run_getq_param (CrankBenchRun *run,
                            const GQuark   name)
{
  return (GValue*) g_hash_table_lookup (run->param, GINT_TO_POINTER(name));
}

/**
 * crank_bench_run_getq_param_int: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets integer benchmark parameter by @name.
 *
 * Returns: A integer benchmark parameter, or @defval if fail.
 */
gint
crank_bench_run_getq_param_int (CrankBenchRun *run,
                               const GQuark    name,
                               const gint      defval)
{
  return crank_value_table_get_int (run->param, GINT_TO_POINTER(name), defval);
}

/**
 * crank_bench_run_getq_param_uint: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets unsigned integer benchmark parameter by @name.
 *
 * Returns: A unsigned integer benchmark parameter, or @defval if fail.
 */
guint
crank_bench_run_getq_param_uint (CrankBenchRun *run,
                                 const GQuark   name,
                                 const guint    defval)
{
  return crank_value_table_get_uint (run->param, GINT_TO_POINTER(name), defval);
}

/**
 * crank_bench_run_getq_param_float: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets float benchmark parameter by @name.
 *
 * Returns: A float benchmark parameter, or @defval if fail.
 */
gfloat
crank_bench_run_getq_param_float (CrankBenchRun *run,
                                  const GQuark   name,
                                  const gfloat   defval)
{
  return crank_value_table_get_float (run->param, GINT_TO_POINTER(name), defval);
}

/**
 * crank_bench_run_getq_param_double: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets double benchmark parameter by @name.
 *
 * Returns: A double benchmark parameter, or @defval if fail.
 */
gdouble
crank_bench_run_getq_param_double (CrankBenchRun *run,
                                   const GQuark   name,
                                   const gdouble  defval)
{
  return crank_value_table_get_double (run->param, GINT_TO_POINTER(name), defval);
}




/**
 * crank_bench_run_add_result: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @value: (transfer none): A value.
 *
 * Adds result on this run with @name.
 */
void
crank_bench_run_add_result (CrankBenchRun *run,
                            const gchar   *name,
                            GValue        *value)
{
  CrankBenchResultEntry *entry = g_slice_new (CrankBenchResultEntry);

  entry->name = g_quark_from_string (name);
  crank_value_overwrite (& (entry->value), value);

  g_queue_push_tail (run->result_journal, entry);
}

/**
 * crank_bench_run_add_result_int: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @value: A value.
 *
 * Adds integer result on this run with @name.
 */
void
crank_bench_run_add_result_int (CrankBenchRun *run,
                                const gchar   *name,
                                const gint     value)
{
  CrankBenchResultEntry *entry = g_slice_new (CrankBenchResultEntry);

  entry->name = g_quark_from_string (name);
  crank_value_overwrite_int (& (entry->value), value);

  g_queue_push_tail (run->result_journal, entry);
}

/**
 * crank_bench_run_add_result_uint: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @value: A value.
 *
 * Adds unsigned integer result on this run with @name.
 */
void
crank_bench_run_add_result_uint (CrankBenchRun *run,
                                 const gchar   *name,
                                 const guint    value)
{
  CrankBenchResultEntry *entry = g_slice_new (CrankBenchResultEntry);

  entry->name = g_quark_from_string (name);
  crank_value_overwrite_uint (& (entry->value), value);

  g_queue_push_tail (run->result_journal, entry);
}

/**
 * crank_bench_run_add_result_float: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @value: A value.
 *
 * Adds float result on this run with @name.
 */
void
crank_bench_run_add_result_float (CrankBenchRun *run,
                                  const gchar   *name,
                                  const gfloat   value)
{
  CrankBenchResultEntry *entry = g_slice_new (CrankBenchResultEntry);

  entry->name = g_quark_from_string (name);
  crank_value_overwrite_float (& (entry->value), value);

  g_queue_push_tail (run->result_journal, entry);
}

/**
 * crank_bench_run_add_result_double: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @value: A value.
 *
 * Adds double result on this run with @name.
 */
void
crank_bench_run_add_result_double (CrankBenchRun *run,
                                   const gchar   *name,
                                   const double   value)
{
  CrankBenchResultEntry *entry = g_slice_new (CrankBenchResultEntry);

  entry->name = g_quark_from_string (name);
  crank_value_overwrite_double (& (entry->value), value);

  g_queue_push_tail (run->result_journal, entry);
}

/**
 * crank_bench_run_timer_start: (skip)
 * @run: A benchmark run.
 *
 * Starts a timer. CrankBenchRun will hold a #GTimer for you. If you need more
 * complex time measurement, check elapesed time for multiple time, or use
 * your own one or more #GTimer.
 */
void
crank_bench_run_timer_start (CrankBenchRun *run)
{
  g_timer_start (run->timer_user);
}

/**
 * crank_bench_run_timer_elapsed: (skip)
 * @run: A benchmark run.
 *
 * Gets elapsed time from when crank_bench_run_timer_start() .
 *
 * Returns: how long time has been from last call of
 *     crank_bench_run_timer_start()
 */
gdouble
crank_bench_run_timer_elapsed (CrankBenchRun *run)
{
  return g_timer_elapsed (run->timer_user, NULL);
}

/**
 * crank_bench_run_timer_add_result_elapsed: (skip)
 * @run: A benchmark run.
 * @name: A result name
 *
 * Adds elapsed time as double result with @name, from when
 * crank_bench_run_timer_start().
 *
 * Returns: how long time has been from last call of
 *     crank_bench_run_timer_start()
 */
gdouble
crank_bench_run_timer_add_result_elapsed (CrankBenchRun *run,
                                          const gchar   *name)
{
  gdouble elapsed = crank_bench_run_timer_elapsed (run);
  crank_bench_run_add_result_double (run, name, elapsed);
  return elapsed;
}

/**
 * crank_bench_run_rand_boolean: (skip)
 * @run: A benchmark run.
 *
 * Returns random boolean; %TRUE or %FALSE randomly.
 *
 * #CrankBenchRun will hold a #GRand for you.
 *
 * Returns: A random boolean.
 */
gboolean
crank_bench_run_rand_boolean (CrankBenchRun *run)
{
  return g_rand_boolean (run->random);
}

/**
 * crank_bench_run_rand_int: (skip)
 * @run: A benchmark run.
 *
 * Returns random integer.
 *
 * Returns: A random integer.
 */
gint32
crank_bench_run_rand_int (CrankBenchRun *run)
{
  return g_rand_int (run->random);
}

/**
 * crank_bench_run_rand_int_range: (skip)
 * @run: A benchmark run.
 * @begin: Begin of range.
 * @end: End of range.
 *
 * Returns random integer in the range: [@begin, @end).
 *
 * Returns: A random integer in the range.
 */
gint32
crank_bench_run_rand_int_range (CrankBenchRun *run,
                                const gint32   begin,
                                const gint32   end)
{
  return g_rand_int_range (run->random, begin, end);
}

/**
 * crank_bench_run_rand_float: (skip)
 * @run: A benchmark run.
 *
 * Returns random float.
 *
 * Returns: A random float.
 */
gfloat
crank_bench_run_rand_float (CrankBenchRun *run)
{
  return (gfloat) g_rand_double (run->random);
}

/**
 * crank_bench_run_rand_float_range: (skip)
 * @run: A benchmark run.
 * @begin: Begin of range.
 * @end: End of range.
 *
 * Returns random float in the range: [@begin, @end).
 *
 * Returns: A random float in the range.
 */
gfloat
crank_bench_run_rand_float_range (CrankBenchRun *run,
                                   const gfloat   begin,
                                   const gfloat   end)
{
  return (gfloat) g_rand_double_range (run->random, (gdouble)begin, (gdouble)end);
}

/**
 * crank_bench_run_rand_double: (skip)
 * @run: A benchmark run.
 *
 * Returns random double.
 *
 * Returns: A random double.
 */
gdouble
crank_bench_run_rand_double (CrankBenchRun *run)
{
  return g_rand_double (run->random);
}

/**
 * crank_bench_run_rand_double_range: (skip)
 * @run: A benchmark run.
 * @begin: Begin of range.
 * @end: End of range.
 *
 * Returns random double in the range: [@begin, @end).
 *
 * Returns: A random double in the range.
 */
gdouble
crank_bench_run_rand_double_range (CrankBenchRun *run,
                                   const gdouble  begin,
                                   const gdouble  end)
{
  return g_rand_double_range (run->random, begin, end);
}

/**
 * crank_bench_run_rand_float_array: (skip)
 * @run: A benchmark run.
 * @length: Length of required random array.
 *
 * Constructs random float array of given @length.
 *
 * Returns: (array) (transfer container): A random float array.
 */
gfloat*
crank_bench_run_rand_float_array (CrankBenchRun *run,
                                  const guint    length)
{
  gfloat *result = g_new (gfloat, length);
  guint i;
  for (i = 0;i < length; i++)
    result[i] = (gfloat) g_rand_double (run->random);

  return result;
}

/**
 * crank_bench_run_rand_double_array: (skip)
 * @run: A benchmark run.
 * @length: Length of required random array.
 *
 * Constructs random double array of given @length.
 *
 * Returns: (array) (transfer container): A random double array.
 */
gdouble*
crank_bench_run_rand_double_array (CrankBenchRun *run,
                                  const guint    length)
{
  gdouble *result = g_new (gdouble, length);
  guint i;
  for (i = 0;i < length; i++)
    result[i] = g_rand_double (run->random);

  return result;
}


/**
 * crank_bench_run_run:
 * @run: A Benchmark run.
 *
 * Performs single run of benchmark.
 */
void
crank_bench_run_run (CrankBenchRun *run)
{
  // Check run state.
  switch (run->state)
    {
    case CRANK_BENCH_RUN_RUNNING:
      g_warning ("Try running already running run.");
      return;

    case CRANK_BENCH_RUN_FINISHED:
      g_warning ("Try running finished run.");
      return;

    case CRANK_BENCH_RUN_PROCESSED:
      g_warning ("Try running processed run.");
      return;

    case CRANK_BENCH_RUN_NOT_RUN:
      break;
      // default.
    }

  // Run case.
  run->state = CRANK_BENCH_RUN_RUNNING;

  g_timer_start (run->timer_run);
  crank_bench_case_invoke (run->bcase, run);
  g_timer_stop (run->timer_run);

  run->state = CRANK_BENCH_RUN_FINISHED;
}

/**
 * crank_bench_run_process:
 * @run: A Benchmark run.
 *
 * Process this run for result. Results are available after process.
 */
void
crank_bench_run_process (CrankBenchRun* run)
{
  // Check for finished run.
  // Check run state.
  switch (run->state)
    {
    case CRANK_BENCH_RUN_NOT_RUN:
    case CRANK_BENCH_RUN_RUNNING:
      g_warning ("Try processing not finished run.");
      return;

    case CRANK_BENCH_RUN_FINISHED:
      break;

    case CRANK_BENCH_RUN_PROCESSED:
      g_warning ("Try processing already processed run.");
      return;
    }

  // Process result.
  run->result = crank_value_table_create (g_direct_hash, g_direct_equal);
  while (! g_queue_is_empty(run->result_journal))
    {
      CrankBenchResultEntry *entry;
      entry = (CrankBenchResultEntry*) g_queue_pop_head (run->result_journal);

      if (g_hash_table_contains (run->result, GINT_TO_POINTER(entry->name)))
        {
          g_info ("Currently multiple value emit is not supported. :-< : %s",
                  g_quark_to_string (entry->name));
        }
      else
        {
          g_hash_table_insert (run->result,
                               GINT_TO_POINTER (entry->name),
                               crank_value_dup (& entry->value));
        }
      g_slice_free (CrankBenchResultEntry, entry);
    }

  run->state = CRANK_BENCH_RUN_PROCESSED;
}

/**
 * crank_bench_run_get_results:
 * @run: A Benchmark run.
 *
 * Gets result of run. Results will be ready after postprocessing.
 *
 * Returns: (nullable) (transfer none) (element-type GQuark GValue):
 *     Results or %NULL, if postprocessed.
 */
GHashTable*
crank_bench_run_get_results (CrankBenchRun *run)
{
  return run->result;
}

/**
 * crank_bench_run_get_result: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 *
 * Gets a benchmark result by @name.
 *
 * Returns: (transfer none) (nullable): A benchmark result as #GValue. or %NULL
 *     if fail.
 */
GValue*
crank_bench_run_get_result (CrankBenchRun *run,
                            const gchar   *name)
{
  return (GValue*) g_hash_table_lookup (run->result, CRANK_QUARK_TRY_STRING(name));
}

/**
 * crank_bench_run_get_result_int: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @defval: Default value if @name is not found.
 *
 * Gets integer result by @name.
 *
 * Returns: A integer result, or @defval if fail.
 */
gint
crank_bench_run_get_result_int (CrankBenchRun *run,
                                const gchar   *name,
                                const gint     defval)
{
  return crank_value_table_get_int (run->result, CRANK_QUARK_TRY_STRING(name), defval);
}

/**
 * crank_bench_run_get_result_uint: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @defval: Default value if @name is not found.
 *
 * Gets unsigned integer result by @name.
 *
 * Returns: A unsigned integer result, or @defval if fail.
 */
guint
crank_bench_run_get_result_uint (CrankBenchRun *run,
                                 const gchar   *name,
                                 const guint    defval)
{
  return crank_value_table_get_uint (run->result, CRANK_QUARK_TRY_STRING(name), defval);
}

/**
 * crank_bench_run_get_result_float: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @defval: Default value if @name is not found.
 *
 * Gets float result by @name.
 *
 * Returns: A float result, or @defval if fail.
 */
gfloat
crank_bench_run_get_result_float (CrankBenchRun *run,
                                  const gchar   *name,
                                  const gfloat   defval)
{
  return crank_value_table_get_float (run->result, CRANK_QUARK_TRY_STRING(name), defval);
}

/**
 * crank_bench_run_get_result_double: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 * @defval: Default value if @name is not found.
 *
 * Gets double result by @name.
 *
 * Returns: A double result, or @defval if fail.
 */
gdouble
crank_bench_run_get_result_double (CrankBenchRun *run,
                                   const gchar   *name,
                                   const gdouble  defval)
{
  return crank_value_table_get_double (run->result, CRANK_QUARK_TRY_STRING(name), defval);
}



/**
 * crank_bench_run_getq_result: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 *
 * Gets a benchmark result by @name.
 *
 * Returns: (transfer none) (nullable): A benchmark parameter as #GValue. or
 *     %NULL if fail.
 */
GValue*
crank_bench_run_getq_result (CrankBenchRun *run,
                             const GQuark   name)
{
  return (GValue*) g_hash_table_lookup (run->result, GINT_TO_POINTER(name));
}

/**
 * crank_bench_run_getq_result_int: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets integer result by @name.
 *
 * Returns: A integer result, or @defval if fail.
 */
gint
crank_bench_run_getq_result_int (CrankBenchRun *run,
                                 const GQuark   name,
                                 const gint     defval)
{
  return crank_value_table_get_int (run->result, GINT_TO_POINTER(name), defval);
}

/**
 * crank_bench_run_getq_result_uint: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets unsigned integer result by @name.
 *
 * Returns: A unsigned integer result, or @defval if fail.
 */
guint
crank_bench_run_getq_result_uint (CrankBenchRun *run,
                                  const GQuark   name,
                                  const guint    defval)
{
  return crank_value_table_get_uint (run->result, GINT_TO_POINTER(name), defval);
}

/**
 * crank_bench_run_getq_result_float: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets float result by @name.
 *
 * Returns: A float result, or @defval if fail.
 */
gfloat
crank_bench_run_getq_result_float (CrankBenchRun *run,
                                   const GQuark   name,
                                   const gfloat   defval)
{
  return crank_value_table_get_float (run->result, GINT_TO_POINTER(name), defval);
}

/**
 * crank_bench_run_getq_result_double: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 * @defval: Default value if @name is not found.
 *
 * Gets double benchmark parameter by @name.
 *
 * Returns: A double benchmark parameter, or @defval if fail.
 */
gdouble
crank_bench_run_getq_result_double (CrankBenchRun *run,
                                   const GQuark   name,
                                   const gdouble  defval)
{
  return crank_value_table_get_double (run->result, GINT_TO_POINTER(name), defval);
}


/**
 * crank_bench_run_get_param_to_string: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 *
 * Gets stringified parameter with @name.
 *
 * This function is not useful durning benchmarking, but useful when building
 * output.
 *
 * Returns: (transfer full): A stringified parameter.
 */
gchar*
crank_bench_run_get_param_to_string (CrankBenchRun *run,
                                     const gchar   *name)
{
  return crank_bench_value_string (crank_bench_run_get_param (run, name));
}

/**
 * crank_bench_run_getq_param_to_string: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 *
 * Gets stringified parameter with @name.
 *
 * This function is not useful durning benchmarking, but useful when building
 * output.
 *
 * Returns: (transfer full): A stringified parameter.
 */
gchar*
crank_bench_run_getq_param_to_string (CrankBenchRun *run,
                                     const GQuark   name)
{
  return crank_bench_value_string (crank_bench_run_getq_param (run, name));
}


/**
 * crank_bench_run_get_result_to_string: (skip)
 * @run: A benchmark run.
 * @name: A result name.
 *
 * Gets stringified result with @name.
 *
 * Returns: (transfer full): A stringified result.
 */
gchar*
crank_bench_run_get_result_to_string (CrankBenchRun *run,
                                      const gchar   *name)
{
  return crank_bench_value_string (crank_bench_run_get_result (run, name));
}

/**
 * crank_bench_run_getq_result_to_string: (skip)
 * @run: A benchmark run.
 * @name: A parameter name.
 *
 * Gets stringified parameter with @name.
 *
 * Returns: (transfer full): A stringified result.
 */
gchar*
crank_bench_run_getq_result_to_string (CrankBenchRun *run,
                                       const GQuark   name)
{
  return crank_bench_value_string (crank_bench_run_getq_result (run, name));
}


/**
 * crank_bench_run_get_params_to_strv: (skip)
 * @run: A benchmark run.
 * @names: (array zero-terminated): Parameter names.
 *
 * Gets stringified parameters with given @names.
 *
 * Returns: (transfer full) (array zero-terminated):
 *     Stringified values of parameters.
 */
gchar**
crank_bench_run_get_params_to_strv (CrankBenchRun  *run,
                                    const gchar   **names)
{
  gchar **strv;
  guint nnames;
  guint i;

  nnames = g_strv_length ((gchar**) names);
  strv = g_new (gchar*, nnames + 1);

  for (i = 0; i < nnames; i++)
    strv[i] = crank_bench_run_get_param_to_string (run, names[i]);

  strv[nnames] = NULL;
  return strv;
}

/**
 * crank_bench_run_getq_params_to_strv: (skip)
 * @run: A benchmark run.
 * @names: (array length=nnames): Parameter names.
 * @nnames: length of @names.
 *
 * Gets stringified parameters with given @names.
 *
 * Returns: (transfer full) (array zero-terminated):
 *     Stringified values of parameters.
 */
gchar**
crank_bench_run_getq_params_to_strv (CrankBenchRun *run,
                                     const GQuark  *names,
                                     const guint    nnames)
{
  gchar **strv;
  guint i;

  strv = g_new (gchar*, nnames + 1);

  for (i = 0; i < nnames; i++)
    strv[i] = crank_bench_run_getq_param_to_string (run, names[i]);

  strv[nnames] = NULL;

  return strv;
}

/**
 * crank_bench_run_get_results_to_strv: (skip)
 * @run: A benchmark run.
 * @names: (array zero-terminated): Parameter names.
 *
 * Gets stringified results with given @names.
 *
 * Returns: (transfer full) (array zero-terminated):
 *     Stringified values of results.
 */
gchar**
crank_bench_run_get_results_to_strv (CrankBenchRun *run,
                                     const gchar  **names)
{
  gchar **strv;
  guint nnames;
  guint i;

  nnames = g_strv_length ((gchar**)names);
  strv = g_new (gchar*, nnames + 1);

  for (i = 0; i < nnames; i++)
    strv[i] = crank_bench_run_get_result_to_string (run, names[i]);

  strv[nnames] = NULL;
  return strv;
}

/**
 * crank_bench_run_getq_results_to_strv: (skip)
 * @run: A benchmark run.
 * @names: (array length=nnames): Parameter names.
 * @nnames: length of @names.
 *
 * Gets stringified results with given @names.
 *
 * Returns: (transfer full) (array zero-terminated):
 *     Stringified values of results.
 */
gchar**
crank_bench_run_getq_results_to_strv (CrankBenchRun *run,
                                      const GQuark  *names,
                                      const guint    nnames)
{
  gchar **strv;
  guint i;

  strv = g_new (gchar*, nnames + 1);

  for (i = 0; i < nnames; i++)
    strv[i] = crank_bench_run_getq_result_to_string (run, names[i]);

  strv[nnames] = NULL;
  return strv;
}




/**
 * crank_bench_run_list_get_param_names: (skip)
 * @runlist: (element-type CrankBenchRun): List of runs.
 *
 * Gets all parameter names among in run list, as #GHashTable<#GQuark, #GQuark>
 *
 * Returns: (transfer container) (element-type GQuark GQuark):
 *     All parameter names used in all runs in @runlist.
 */
GHashTable*
crank_bench_run_list_get_param_names (GList *runlist)
{
  GHashTable *names;

  GList *i;

  if (runlist == NULL)
    return NULL;

  names = g_hash_table_new (g_direct_hash, g_direct_equal);

  for (i = runlist; i != NULL; i = i->next)
    {
      CrankBenchRun *run = (CrankBenchRun*) i->data;

      crank_set_overlay (names, run->param);
    }

  return names;
}

/**
 * crank_bench_run_list_get_result_names: (skip)
 * @runlist: (element-type CrankBenchRun): List of runs.
 *
 * Gets all result names among in run list, as #GHashTable<#GQuark, #GQuark>
 *
 * Returns: (transfer container) (element-type GQuark GQuark):
 *     All parameter names used in all runs in @runlist.
 */
GHashTable*
crank_bench_run_list_get_result_names (GList *runlist)
{
  GHashTable *names;

  GList *i;

  if (runlist == NULL)
    return NULL;

  names = g_hash_table_new (g_direct_hash, g_direct_equal);

  for (i = runlist; i != NULL; i = i->next)
    {
      CrankBenchRun *run = (CrankBenchRun*) i->data;

      crank_set_overlay (names, run->result);
    }

  return names;
}
