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
#include "crankvalue.h"
#include "crankstring.h"
#include "crankbench.h"
#include "crankbench-private.h"
#include "crankbenchrun.h"

/**
 * SECTION: crankbenchresult
 * @title: Benchmark Results.
 * @short_description: Benchmark results.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * This section describes Benchmark results.
 */

//////// CrankBenchResultSuite /////////////////////////////////////////////////

/**
 * crank_bench_result_suite_new: (skip)
 * @suite: (transfer none): A Benchmark suite to reference.
 *
 * Constructs a result refers to @suite.
 *
 * Returns: (transfer full): Newly created result.
 */
CrankBenchResultSuite*
crank_bench_result_suite_new (CrankBenchSuite *suite)
{
  CrankBenchResultSuite* result = g_slice_new (CrankBenchResultSuite);

  result->parent = NULL;
  result->sresults = g_ptr_array_new_with_free_func ((GDestroyNotify)
                                                     crank_bench_result_suite_free);
  result->cresults = g_ptr_array_new_with_free_func ((GDestroyNotify)
                                                     crank_bench_result_case_free);

  result->suite = suite;

  return result;
}

/**
 * crank_bench_result_suite_free: (skip)
 * @result: A Benchmark result.
 *
 * Frees a result and sub-results under this result.
 */
void
crank_bench_result_suite_free (CrankBenchResultSuite *result)
{
  g_ptr_array_unref (result->sresults);
  g_ptr_array_unref (result->cresults);

  g_slice_free (CrankBenchResultSuite, result);
}

/**
 * crank_bench_result_suite_get_suite: (skip)
 * @result: A Benchmark result.
 *
 * Gets a benchmark suite associated to this result.
 *
 * Returns: (transfer none): A Benchmark suite.
 */
CrankBenchSuite*
crank_bench_result_suite_get_suite (CrankBenchResultSuite *result)
{
  return result->suite;
}

/**
 * crank_bench_result_suite_get_parent: (skip)
 * @result: A Benchmark result.
 *
 * Gets parent result of this result.
 *
 * Result: (transfer none) (nullable): Parent result or %NULL, if this is root.
 */
CrankBenchResultSuite*
crank_bench_result_suite_get_parent (CrankBenchResultSuite *result)
{
  return result->parent;
}

/**
 * crank_bench_result_suite_add_sresult: (skip):
 * @result: A Benchmark result.
 * @sres: (transfer full): Another result to be added under.
 *
 * Adds benchmark result as child of this result.
 */
void
crank_bench_result_suite_add_sresult (CrankBenchResultSuite *result,
                                      CrankBenchResultSuite *sres)
{
  g_return_if_fail (sres->parent == NULL);

  sres->parent = result;
  g_ptr_array_add (result->sresults, sres);
}

/**
 * crank_bench_result_suite_add_cresult: (skip):
 * @result: A Benchmark result.
 * @cres: (transfer full): A Benchmakr case result to be added under.
 *
 * Adds benchmark result as child of this result.
 */
void
crank_bench_result_suite_add_cresult (CrankBenchResultSuite *result,
                                      CrankBenchResultCase  *cres)
{
  g_return_if_fail (cres->parent == NULL);

  cres->parent = result;
  g_ptr_array_add (result->cresults, cres);
}

/**
 * crank_bench_result_suite_remove_sresult: (skip):
 * @result: A Benchmark result.
 * @sres: (transfer none): A child result.
 *
 * Removes child benchmark result from this result.
 *
 * Returns: Whether the child was removed.
 */
gboolean
crank_bench_result_suite_remove_sresult (CrankBenchResultSuite *result,
                                         CrankBenchResultSuite *sres)
{
  if (sres->parent != result)
    return FALSE;

  sres->parent = NULL;
  return g_ptr_array_remove (result->sresults, sres);
}

/**
 * crank_bench_result_suite_remove_cresult: (skip):
 * @result: A Benchmark result.
 * @cres: (transfer none): A child result.
 *
 * Removes child benchmark result from this result.
 *
 * Returns: Whether the child was removed.
 */
gboolean
crank_bench_result_suite_return_cresult (CrankBenchResultSuite *result,
                                         CrankBenchResultCase  *cres)
{
  if (cres->parent != NULL);

  cres->parent = NULL;
  return g_ptr_array_remove (result->cresults, cres);
}

/**
 * crank_bench_result_suite_get_sresults: (skip)
 * @result: A Benchmark result.
 *
 * Gets all child benchmark results.
 *
 * Returns: (transfer none) (element-type CrankBenchResultSuite):
 *     Child results.
 */
GPtrArray*
crank_bench_result_suite_get_sresults (CrankBenchResultSuite *result)
{
  return result->sresults;
}

/**
 * crank_bench_result_suite_get_cresults: (skip)
 * @result: A Benchmark result.
 *
 * Gets all child benchmark results.
 *
 * Returns: (transfer none) (element-type CrankBenchResultCase):
 *     Child results.
 */
GPtrArray*
crank_bench_result_suite_get_cresults (CrankBenchResultSuite *result)
{
  return result->cresults;
}

/**
 * crank_bench_result_suite_get_sresult: (skip)
 * @result: A Benchmark result.
 * @name: A name of associated suite.
 *
 * Gets a child benchmark result by name of associated suite.
 *
 * Returns: (transfer none) (nullable): A child result or %NULL if such result
 *     is not found.
 */
CrankBenchResultSuite*
crank_bench_result_suite_get_sresult (CrankBenchResultSuite *result,
                                      const gchar           *name)
{
  guint i;
  for (i = 0; i < result->sresults->len; i++)
    {
      CrankBenchResultSuite* sres;

      sres = (CrankBenchResultSuite*) result->sresults->pdata[i];

      if (strcmp (name, sres->suite->name) == 0)
        return sres;
    }
  return NULL;
}

/**
 * crank_bench_result_suite_get_cresult: (skip)
 * @result: A Benchmark result.
 * @name: A name of associated case.
 *
 * Gets a child benchmark result by name of associated case.
 *
 * Returns: (transfer none) (nullable): A child result or %NULL if such result
 *     is not found.
 */
CrankBenchResultCase*
crank_bench_result_suite_get_cresult (CrankBenchResultSuite *result,
                                      const gchar           *name)
{
  guint i;
  for (i = 0; i < result->cresults->len; i++)
    {
      CrankBenchResultCase* cres;

      cres = (CrankBenchResultCase*) result->cresults->pdata[i];

      if (strcmp (name, cres->bcase->name) == 0)
        return cres;
    }
  return NULL;
}

/**
 * crank_bench_result_suite_get_cresults_flat: (skip)
 * @result: A benchmark result.
 *
 * Gets all case results of this result and child results. (recursively).
 *
 * Returns: (element-type CrankBenchResultCase) (transfer container): All case
 *     results of this and child results.
 */
GList*
crank_bench_result_suite_get_cresults_flat (CrankBenchResultSuite *result)
{
  GList *list = NULL;
  guint i;

  for (i = 0; i < result->cresults->len; i++)
    list = g_list_prepend (list, result->cresults->pdata[i]);

  list = g_list_reverse (list);

  for (i = 0; i < result->sresults->len; i++)
    {
      CrankBenchResultSuite* subresult;
      subresult = (CrankBenchResultSuite*) result->sresults->pdata[i];

      GList *sublist = crank_bench_result_suite_get_cresults_flat (subresult);

      list = g_list_concat (list, sublist);
    }
  return list;
}

/**
 * crank_bench_result_suite_get_runs: (skip)
 * @result: A Benchmark result.
 *
 * Gets all runs on case result of this result.
 *
 * Returns: (element-type CrankBenchRun) (transfer container): All result runs
 *     of this result.
 */
GList*
crank_bench_result_suite_get_runs (CrankBenchResultSuite *result)
{
  GList *list;
  guint i;
  guint j;

  list = NULL;
  for (i = 0; i < result->cresults->len; i++)
    {
      CrankBenchResultCase *cresult;
      cresult = (CrankBenchResultCase*) result->cresults->pdata[i];

      for (j = 0; j < cresult->runs->len; j++)
        list = g_list_append (list, cresult->runs->pdata[i]);
    }

  return list;
}

/**
 * crank_bench_result_suite_get_runs_flat: (skip)
 * @result: A Benchmark result.
 *
 * Gets all runs on case result of this result and child results. (recursively)
 *
 * Returns: (element-type CrankBenchRun) (transfer container): All result runs
 *     of this result.
 */
GList*
crank_bench_result_suite_get_runs_flat (CrankBenchResultSuite *result)
{
  GList *list;
  guint i;

  list = crank_bench_result_suite_get_runs (result);

  for (i = 0; i <result->sresults->len; i++)
    {
      CrankBenchResultSuite* subresult;
      subresult = (CrankBenchResultSuite*) result->sresults->pdata[i];

      GList *sublist = crank_bench_result_suite_get_runs_flat (subresult);

      list = g_list_concat (list, sublist);
    }
  return list;
}





//////// CrankBenchResultCase //////////////////////////////////////////////////

/**
 * crank_bench_result_case_new: (skip)
 * @bcase: (transfer none): A Benchmark case.
 *
 * Constructs a result refers to @bcase.
 *
 * Returns: (transfer full): A Benchmark result.
 */
CrankBenchResultCase*
crank_bench_result_case_new (CrankBenchCase *bcase)
{
  CrankBenchResultCase* result = g_slice_new (CrankBenchResultCase);

  result->parent = NULL;
  result->bcase = bcase;
  result->runs = g_ptr_array_new_with_free_func ((GDestroyNotify)
                                                 crank_bench_run_free);

  result->param_names = g_hash_table_new (g_direct_hash, g_direct_equal);
  result->result_names =  g_hash_table_new (g_direct_hash, g_direct_equal);

  return result;
}

/**
 * crank_bench_result_case_free: (skip)
 * @result: A benchmark result.
 *
 * Frees a result and its run results.
 */
void
crank_bench_result_case_free (CrankBenchResultCase *result)
{
  g_ptr_array_unref (result->runs);

  g_hash_table_unref (result->param_names);
  g_hash_table_unref (result->result_names);

  g_slice_free (CrankBenchResultCase, result);
}

/**
 * crank_bench_result_case_get_case: (skip)
 * @result: A benchmark result.
 *
 * Gets a benchmark case that this refers to.
 *
 * Returns: (transfer none): A Benchmark case.
 */
CrankBenchCase*
crank_bench_result_case_get_case (CrankBenchResultCase *result)
{
  return result->bcase;
}

/**
 * crank_bench_result_case_get_parent: (skip)
 * @result: A Benchmark result.
 *
 * Gets parent result of this result.
 *
 * Returns: (transfer none) (nullable): Parent result or %NULL, if this is not
 *     added yet.
 */
CrankBenchResultSuite*
crank_bench_result_case_get_parent (CrankBenchResultCase *result)
{
  return result->parent;
}

/**
 * crank_bench_result_case_get_runs:
 * @result: A Benchmark result.
 *
 * Gets all runs in this result.
 *
 * Returns: (transfer none) (element-type CrankBenchRun):
 *     Runs in this result.
 */
GPtrArray*
crank_bench_result_case_get_runs (CrankBenchResultCase *result)
{
  return result->runs;
}

/**
 * crank_bench_result_case_get_param_names: (skip)
 * @result: A Benchmark result.
 *
 * Gets parameter names used in this case, in form of #GHashTable<#GQuark>
 *
 * Returns: (transfer none) (element-type GQuark GQuark):
 *     Names of benchmark parameters.
 */
GHashTable*
crank_bench_result_case_get_param_names (CrankBenchResultCase *result)
{
  return result->param_names;
}

/**
 * crank_bench_result_case_get_result_names: (skip)
 * @result: A Benchmark result.
 *
 * Gets result names used in this case, in form of #GHashTable<#GQuark>
 *
 * Returns: (transfer none) (element-type GQuark GQuark):
 *     Names of benchmark result columns.
 */
GHashTable*
crank_bench_result_case_get_result_names (CrankBenchResultCase *result)
{
  return result->result_names;
}




//////// Private functions /////////////////////////////////////////////////////

void
_crank_bench_result_suite_postprocess (CrankBenchResultSuite *result)
{
  // For now doing nothing, but propagate throughout to whole result trees.

  g_ptr_array_foreach (result->cresults,
                       (GFunc)_crank_bench_result_case_postprocess,
                       NULL);

  g_ptr_array_foreach (result->sresults,
                       (GFunc)_crank_bench_result_suite_postprocess,
                       NULL);
}

void
_crank_bench_result_case_postprocess (CrankBenchResultCase *result)
{
  gchar *path = crank_bench_case_get_path (result->bcase);

  g_fprintf (stderr, "%s: ", path);

  g_ptr_array_foreach (result->runs, (GFunc)crank_bench_run_postprocess, NULL);

  // Accumulate all names used in runs.
  g_ptr_array_foreach (result->runs, (GFunc)_crank_bench_result_case_pp_accum, result);

  g_fprintf (stderr, "OK\n");
}

void
_crank_bench_result_case_pp_accum (CrankBenchRun        *run,
                                   CrankBenchResultCase *result)
{
  _crank_bench_set_join (result->param_names, crank_bench_run_get_params (run));
  _crank_bench_set_join (result->result_names, crank_bench_run_get_results (run));
}
