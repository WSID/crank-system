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

#include <stdlib.h>
#include <string.h>
#include <glib.h>


#include "crankvalue.h"
#include "crankstring.h"
#include "crankbench.h"
#include "crankbench-private.h"

/**
 * SECTION:crankbench
 * @title: Benchmarking
 * @short_description: Functions for benchmarking.
 * @stability: unstable
 * @include: crankbase.h
 *
 * Crank System also provides benchmarking system. (for, mainly, crank system
 * itself)
 *
 * Benchmarking System is designed in reference to GTest Framework. Benchmarking
 * System has similarity to GTest Framework. But this has different objective,
 * this has different to GTest Framework.
 *
 * * Similarity
 *   * Suite, Case style hierarchy
 *
 * * Differece
 *   * Testing Result
 *     * Benchmarking System: Each test case adds result.
 *     * GTest Framework: Each test case performs assertions.
 *   * Output
 *     * Benchmarking System: Test results are printed as CSV.
 *     * GTest Framework: Pass or Fail, optionally performance (though not used
 *       frequently). Recently, TAP protocol can be used.
 */


//////// Variables /////////////////////////////////////////////////////////////

static gboolean         crank_bench_initialized = FALSE;
static CrankBenchSuite *crank_bench_root = NULL;


//////// Overall ///////////////////////////////////////////////////////////////

/**
 * crank_bench_init:
 * @argc: (inout): Number of commandline arguments
 * @argv: (inout) (array length=argc): Commandline arguments
 *
 * Initialize benchmarking system.
 */
void
crank_bench_init (guint   *argc,
                  gchar ***argv)
{
  if (crank_bench_initialized)
    g_error ("CrankBench: Being doubly initialized.");

  // for now, don't take arguments.


  // Initialize Benchmarking System.

  crank_bench_root = crank_bench_suite_new ("", NULL);

  crank_bench_initialized = TRUE;
}

/**
 * crank_bench_is_initialized:
 *
 * Checks whether benchmarking system is initialized.
 *
 * Returns: Whether benchmarking system is initialized.
 */
gboolean
crank_bench_is_initialized (void)
{
  return crank_bench_initialized;
}



/**
 * crank_bench_run:
 *
 * Runs benchmark and returns exit code to return in <function>main</function>.
 *
 * Returns: Exit code to return in main.
 */
gint
crank_bench_run (void)
{
  GNode*         result_node;


  // Perform benchmark.

  result_node = crank_bench_suite_run (crank_bench_root, NULL);


  // Write to output
  g_node_traverse (result_node,
                   G_PRE_ORDER,
                   G_TRAVERSE_LEAVES,
                   -1,
                   _crank_bench_run_list_write_node,
                   NULL);

  return 0;
}



/**
 * crank_bench_get_root:
 *
 * Gets root benchmark suite.
 *
 * Returns: (transfer none): The root benchmark suite.
 */
CrankBenchSuite*
crank_bench_get_root (void)
{
  return crank_bench_root;
}

/**
 * crank_bench_get_suite:
 * @path: A Benchmark path
 *
 * Gets a benchmark suite at @path. If suite is not present at @path, %NULL is
 * returned.
 *
 * Returns: (transfer none) (nullable): A Benchmark suite at @path, or %NULL if fail.
 */
CrankBenchSuite*
crank_bench_get_suite (const gchar *path)
{
  CrankBenchSuite *suite = NULL;
  gchar           *case_name = NULL;

  suite = _crank_bench_get_suite_common (path, &case_name, FALSE);

  if ((suite != NULL) && (case_name[0] != '\0'))
      suite = crank_bench_suite_get_suite (suite, case_name);

  g_free (case_name);
  return suite;
}

/**
 * crank_bench_get_case:
 * @path: A Benchmark path.
 *
 * Gets a benchmark case at @path. If case is not present at @path, %NULL is
 * returned.
 *
 * Returns: (transfer none) (nullable): A Benchmark case at @path, or %NULL if fail.
 */
CrankBenchCase*
crank_bench_get_case (const gchar *path)
{
  CrankBenchSuite *suite = NULL;
  CrankBenchCase  *bcase = NULL;
  gchar           *case_name = NULL;

  suite = _crank_bench_get_suite_common (path, &case_name, FALSE);

  if (suite == NULL)
    {
      if (case_name[0] == '\0')
        g_warning ("Missing case name: %s", path);
      else
        bcase = crank_bench_suite_get_case (suite, case_name);
    }

  g_free (case_name);
  return bcase;
}


/**
 * crank_bench_add:
 * @path: A Benchmark path.
 * @func: (scope notified): A Benchmarking function.
 * @userdata: (closure): Userdata for @func
 * @destroy: (destroy userdata): Destroy for @func
 *
 * Adds benchmark case at given @path, with @func.
 */
void
crank_bench_add (const gchar    *path,
                 CrankBenchFunc  func,
                 gpointer        userdata,
                 GDestroyNotify  destroy)
{
  crank_bench_add_with_param (path, func, userdata, destroy, NULL);
}

/**
 * crank_bench_add_with_param:
 * @path: A Benchmark path.
 * @func: (scope notified): A Benchmarking function.
 * @userdata: (closure): Userdata for @func
 * @destroy: (destroy userdata): Destroy for @func
 * @param: (nullable): A Benchmark parameter in form of
 *     #GNode <#GHashTable <#GQuark, #GValue*>>
 *
 * Adds benchmark case at given @path, with @func, applying @param.
 */
void
crank_bench_add_with_param (const gchar    *path,
                            CrankBenchFunc  func,
                            gpointer        userdata,
                            GDestroyNotify  destroy,
                            GNode          *param)
{
  CrankBenchSuite *suite = NULL;
  CrankBenchCase  *bcase = NULL;
  gchar           *case_name = NULL;

  suite = _crank_bench_get_suite_common (path, &case_name, TRUE);

  if (suite == NULL)
    {
      g_error ("Benchmark case cannot added because of malformed path");
    }

  else if (case_name[0] == '\0')
    {
      g_error ("Missing case name: %s", path);
    }

  else
    {
      bcase = crank_bench_suite_get_case (suite, case_name);

      if (bcase != NULL)
        {
          g_error ("Adding benchmark case to already occupied path: %s", path);
        }
      else
        {
          bcase = crank_bench_case_new (case_name, param, func, userdata, destroy);
          crank_bench_suite_add_case (suite, bcase);
        }
    }

  g_free (case_name);
}

/**
 * crank_bench_set_param:
 * @path: A Benchmark path.
 * @param: (nullable): A Benchmark parameter in form of
 *     #GNode <#GHashTable <#GQuark, #GValue*>>
 *
 * sets a parameter to suite or case at @path.
 */
void
crank_bench_set_param (const gchar *path,
                       GNode       *param)
{
  CrankBenchSuite *suite = NULL;
  CrankBenchCase  *bcase = NULL;
  gchar           *case_name = NULL;

  suite = _crank_bench_get_suite_common (path, &case_name, FALSE);

  if ((suite != NULL) && (case_name[0] != '\0'))
    {
      bcase = crank_bench_suite_get_case (suite, case_name);

      if (bcase == NULL)
        suite = crank_bench_suite_get_suite (suite, case_name);
    }

  g_free (case_name);

  if (bcase != NULL)
    crank_bench_case_set_param (bcase, param);
  else if (suite != NULL)
    crank_bench_suite_set_param (suite, param);
}



//////// CrankBenchSuite ///////////////////////////////////////////////////////

/**
 * crank_bench_suite_new:
 * @name: A Name of benchmark suite.
 * @param: (nullable): A Benchmark parameter in form of
 *     #GNode <#GHashTable <#GQuark, #GValue*>>
 *
 * Creates new benchmark suite.
 *
 * Returns: (transfer full): A newly created benchmark suite.
 */
CrankBenchSuite*
crank_bench_suite_new (const gchar *name,
                       GNode       *param)
{
  CrankBenchSuite *suite = g_slice_new (CrankBenchSuite);

  suite->name = g_strdup (name);
  suite->parent = NULL;
  suite->subsuites = g_ptr_array_new_with_free_func ((GDestroyNotify)crank_bench_suite_free);
  suite->cases = g_ptr_array_new_with_free_func ((GDestroyNotify)crank_bench_case_free);
  suite->param = _crank_bench_dup_param (param);

  return suite;
}

/**
 * crank_bench_suite_free:
 * @suite: A benchmark suite.
 *
 * Frees a benchmark suite, and deallocate all its resources. Sub-suites and
 * cases are also freed.
 */
void
crank_bench_suite_free (CrankBenchSuite *suite)
{
  g_free (suite->name);
  g_ptr_array_unref (suite->subsuites);
  g_ptr_array_unref (suite->cases);
  _crank_bench_free_param (suite->param);

  g_slice_free (CrankBenchSuite, suite);
}

/**
 * crank_bench_suite_get_name:
 * @suite: A benchmark suite.
 *
 * Gets a name of suite.
 *
 * Returns: Name of the suite.
 */
const gchar*
crank_bench_suite_get_name (CrankBenchSuite *suite)
{
  return suite->name;
}

/**
 * crank_bench_suite_set_name:
 * @suite: A benchmark suite.
 * @name: New name of suite.
 *
 * Sets a name of suite.
 */
void
crank_bench_suite_set_name (CrankBenchSuite *suite,
                            const gchar     *name)
{
  g_free (suite->name);
  suite->name = g_strdup (name);
}

/**
 * crank_bench_suite_get_param:
 * @suite: A benchmark suite.
 *
 * Gets benchmark parameter of suite.
 *
 * Returns: (nullable) (transfer none): Parameter of suite, which is
 *     #GNode <#GHashTable <#GQuark, #GValue*>>.
 */
GNode*
crank_bench_suite_get_param (CrankBenchSuite *suite)
{
  return suite->param;
}

/**
 * crank_bench_suite_set_param:
 * @suite: A benchmark suite.
 * @param: (nullable): A Benchmark parameter in form of
 *     #GNode <#GHashTable <#GQuark, #GValue*>>
 *
 * Sets benchmark parameter of suite.
 */
void
crank_bench_suite_set_param (CrankBenchSuite *suite,
                             GNode           *param)
{
  _crank_bench_free_param (suite->param);
  suite->param = _crank_bench_dup_param (param);

}

/**
 * crank_bench_suite_get_parent:
 * @suite: A benchmark suite.
 *
 * Gets parent suite of benchmark suite.
 *
 * Returns: (transfer none) (nullable): A parent suite.
 */
CrankBenchSuite*
crank_bench_suite_get_parent (CrankBenchSuite *suite)
{
  return suite->parent;
}

/**
 * crank_bench_suite_get_path:
 * @suite: A benchmark suite.
 *
 * Gets path of benchmark suite.
 *
 * Returns: (transfer full): A path of suite.
 */
gchar*
crank_bench_suite_get_path (CrankBenchSuite *suite)
{
  GString           *path_builder;
  GQueue             path_queue = G_QUEUE_INIT;
  CrankBenchSuite   *iter;

  iter = suite;
  while (iter != NULL)
    {
      g_queue_push_tail (&path_queue, iter);
      iter = iter->parent;
    }

  path_builder = g_string_new (NULL);
  while (! g_queue_is_empty (&path_queue))
    {
      iter = (CrankBenchSuite*) g_queue_pop_tail (&path_queue);
      g_string_append (path_builder, iter->name);
      g_string_append_c (path_builder, '/');
    }

  return g_string_free (path_builder, FALSE);
}

/**
 * crank_bench_suite_add_suite:
 * @suite: A benchmark suite.
 * @child: (transfer full): Child benchmark suite.
 *
 * Add child suite to this suite.
 */
void
crank_bench_suite_add_suite (CrankBenchSuite *suite,
                             CrankBenchSuite *child)
{
  if (crank_bench_suite_get_suite (suite, child->name) != NULL)
    {
      g_warning ("Adding suite with same name: %s", child->name);
    }
  else
    {
      g_ptr_array_add (suite->subsuites, child);
      child->parent = suite;
    }
}

/**
 * crank_bench_suite_remove_suite:
 * @suite: A benchmark suite.
 * @child: Child benchmark suite.
 *
 * Remove child suite from this suite.
 *
 * Returns: If child suite was removed from this suite.
 */
gboolean
crank_bench_suite_remove_suite (CrankBenchSuite *suite,
                                CrankBenchSuite *child)
{
  if (g_ptr_array_remove (suite->subsuites, child))
    {
      child->parent = NULL;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

/**
 * crank_bench_suite_add_case:
 * @suite: A benchmark suite.
 * @bcase: (transfer full): A benchmark case.
 *
 * Add benchmark case to this suite.
 */
void
crank_bench_suite_add_case (CrankBenchSuite *suite,
                            CrankBenchCase  *bcase)
{
  if (crank_bench_suite_get_case (suite, bcase->name) != NULL)
    {
      g_warning ("Adding case with same name: %s", bcase->name);
    }
  else
    {
      g_ptr_array_add (suite->cases, bcase);
      bcase->parent = suite;
    }
}

/**
 * crank_bench_suite_remove_case:
 * @suite: A benchmark suite.
 * @bcase: A benchmark case.
 *
 * Remove benchmark case from this suite.
 *
 * Returns: If benchmark case was removed from this suite.
 */
gboolean
crank_bench_suite_remove_case (CrankBenchSuite *suite,
                               CrankBenchCase  *bcase)
{
  if (g_ptr_array_remove (suite->cases, bcase))
    {
      bcase->parent = NULL;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

/**
 * crank_bench_suite_get_suites:
 * @suite: A benchmark suite.
 *
 * Gets all its child suites.
 *
 * Returns: (transfer none) (element-type CrankBenchSuite): Its child suites.
 */
GPtrArray*
crank_bench_suite_get_suites (CrankBenchSuite *suite)
{
  return suite->subsuites;
}

/**
 * crank_bench_suite_get_cases:
 * @suite: A benchmark suite.
 *
 * Gets all its benchmark cases.
 *
 * Returns: (transfer none) (element-type CrankBenchCase): Its benchmark cases.
 */
GPtrArray*
crank_bench_suite_get_cases (CrankBenchSuite *suite)
{
  return suite->cases;
}

/**
 * crank_bench_suite_get_suite:
 * @suite: A benchmark suite.
 * @name: A name of child suite.
 *
 * Gets a child suite by name.
 *
 * Returns: (transfer none): A child suite with given @name.
 */
CrankBenchSuite*
crank_bench_suite_get_suite (CrankBenchSuite *suite,
                             const gchar     *name)
{
  guint i;

  for (i = 0; i < suite->subsuites->len; i++)
    {
      CrankBenchSuite *subsuite = (CrankBenchSuite*)suite->subsuites->pdata[i];

      if (strcmp (name, subsuite->name) == 0)
        return subsuite;
    }
  return NULL;
}

/**
 * crank_bench_suite_get_case:
 * @suite: A benchmark suite.
 * @name: A name of benchmark case.
 *
 * Gets a benchmark case by name.
 *
 * Returns: (transfer none): A benchmark case with given @name.
 */
CrankBenchCase*
crank_bench_suite_get_case (CrankBenchSuite *suite,
                            const gchar     *name)
{
  guint i;

  for (i = 0; i < suite->cases->len; i++)
    {
      CrankBenchCase *bcase = (CrankBenchCase*)suite->cases->pdata[i];

      if (strcmp (name, bcase->name) == 0)
        return bcase;
    }
  return NULL;
}

/**
 * crank_bench_suite_run:
 * @suite: A benchmark suite.
 * @param: (nullable): A Benchmark parameter in form of
 *     #GNode <#GHashTable <#GQuark, #GValue*>>
 *
 * Runs benchmark suite, recursively.
 *
 * Returns: (transfer none): A benchmark case with given @name.
 */
GNode*
crank_bench_suite_run (CrankBenchSuite *suite,
                       GNode           *param)
{
  GNode *mparam;

  GNode *node;
  guint i;

  if (suite->param == NULL)
    mparam = param;
  else if (param == NULL)
    mparam = suite->param;
  else
    mparam = _crank_bench_param_composite (param, suite->param);

  node = g_node_new (NULL);

  for (i = 0; i < suite->cases->len; i++)
    {
      CrankBenchCase *bcase = (CrankBenchCase*)suite->cases->pdata[i];
      g_node_append (node, crank_bench_case_run (bcase, mparam));
    }

  for (i = 0; i < suite->subsuites->len; i++)
    {
      CrankBenchSuite *subsuite = (CrankBenchSuite*)suite->subsuites->pdata[i];
      g_node_append (node, crank_bench_suite_run (subsuite, mparam));
    }

  if ((suite->param != NULL) && (param != NULL))
    _crank_bench_free_param (mparam);

  return node;
}

//////// CrankBenchCase ////////////////////////////////////////////////////////

/**
 * crank_bench_case_new:
 * @name: name of benchmark case.
 * @param: (nullable): A Benchmark parameter in form of
 *     #GNode <#GHashTable <#GQuark, #GValue*>>
 * @func: (scope notified): A benchmark function.
 * @userdata: (closure): Userdata for @func.
 * @destroy: (destroy userdata): Destroy function for @userdata.
 *
 * Creates new benchmark case.
 *
 * Returns: (transfer full): Newly created benchmark case.
 */
CrankBenchCase*
crank_bench_case_new (const gchar    *name,
                      GNode          *param,
                      CrankBenchFunc  func,
                      gpointer        userdata,
                      GDestroyNotify  destroy)
{
  CrankBenchCase *bcase = g_slice_new (CrankBenchCase);

  bcase->name = g_strdup (name);
  bcase->param = _crank_bench_dup_param (param);
  bcase->func = func;
  bcase->userdata = userdata;
  bcase->destroy = destroy;

  return bcase;
}

/**
 * crank_bench_case_free:
 * @bcase: A benchmark case.
 *
 * Frees a benchmark case, and deallocates its resources.
 */
void
crank_bench_case_free (CrankBenchCase *bcase)
{
  g_free (bcase->name);
  _crank_bench_free_param (bcase->param);
  bcase->destroy (bcase->userdata);

  g_slice_free (CrankBenchCase, bcase);
}

/**
 * crank_bench_case_get_param:
 * @bcase: A benchmark case.
 *
 * Gets benchmark parameter of case.
 *
 * Returns: (nullable) (transfer none): Benchmark parameter, which is
 *     #GNode <#GHashTable <#GQuark, #GValue*>>.
 */
GNode*
crank_bench_case_get_param (CrankBenchCase *bcase)
{
  return bcase->param;
}

/**
 * crank_bench_case_set_param:
 * @bcase: A benchmark case.
 * @param: (nullable) (transfer none): Benchmark parameter, which is
 *     #GNode <#GHashTable <#GQuark, #GValue*>>.
 *
 * Sets benchmark parameter of case.
 */
void
crank_bench_case_set_param (CrankBenchCase *bcase,
                            GNode          *param)
{
  _crank_bench_free_param (bcase->param);
  bcase->param = _crank_bench_dup_param (param);
}


/**
 * crank_bench_case_get_path:
 * @bcase: A benchmark case.
 *
 * Gets path of benchmark case.
 *
 * Returns: (transfer full): A path of case.
 */
gchar*
crank_bench_case_get_path (CrankBenchCase *bcase)
{
  GString           *path_builder;
  GQueue             path_queue = G_QUEUE_INIT;
  CrankBenchSuite   *iter;

  iter = bcase->parent;
  while (iter != NULL)
    {
      g_queue_push_tail (&path_queue, iter);
      iter = iter->parent;
    }

  path_builder = g_string_new (NULL);
  while (! g_queue_is_empty (&path_queue))
    {
      iter = (CrankBenchSuite*) g_queue_pop_tail (&path_queue);
      g_string_append (path_builder, iter->name);
      g_string_append_c (path_builder, '/');
    }
  g_string_append (path_builder, bcase->name);

  return g_string_free (path_builder, FALSE);
}

/**
 * crank_bench_case_get_parent:
 * @bcase: A benchmark case.
 *
 * Gets parent of benchmark case.
 *
 * Returns: (transfer none): A parent suite of case.
 */
CrankBenchSuite*
crank_bench_case_get_parent (CrankBenchCase *bcase)
{
  return bcase->parent;
}

/**
 * crank_bench_case_run:
 * @bcase: A benchmark case.
 * @param: (nullable) (transfer none): Benchmark parameter, which is
 *     #GNode <#GHashTable <#GQuark, #GValue*>>.
 *
 * Runs a single benchmark case.
 *
 * Returns: (transfer full): A run result, which is #GNode <#GList <#CrankBenchRun>>
 */
GNode*
crank_bench_case_run (CrankBenchCase *bcase,
                      GNode          *param)
{
  GNode *mparam;
  GNode *node;  // GNode < GList <CrankBenchRun>>

  if (bcase->param == NULL)
    mparam = param;
  else if (param == NULL)
    mparam = bcase->param;
  else
    mparam = _crank_bench_param_composite (param, bcase->param);

  if (mparam == NULL)
    {
      gchar *path = crank_bench_case_get_path (bcase);
      g_warning ("No test parameter for case %s", path);
      g_free (path);
      return g_node_new (NULL);
    }

  node = g_node_new (_crank_bench_case_run1 (bcase, mparam, NULL));

  if ((bcase->param != NULL) && (param != NULL))
    _crank_bench_free_param (mparam);

  return node;
}

//////// CrankBenchRun /////////////////////////////////////////////////////////

/**
 * crank_bench_run_skip:
 * @run: A benchmark run.
 * @message: A message for skipping.
 *
 * Marks this run as skipped. This will not stop benchmarking, so function should
 * stop itself.
 */
void
crank_bench_run_skip (CrankBenchRun *run,
                      const gchar   *message)
{
  gchar *path;

  switch (run->state & CRANK_BENCH_RUN_MASK_RUN_STATE)
    {
    case CRANK_BENCH_RUN_NOT_RUN:
    case CRANK_BENCH_RUN_RUNNING:
      break;

    case CRANK_BENCH_RUN_FINISHED:
      path = crank_bench_case_get_path (run->bcase);
      g_error ("Marking skip on already finished run.");
      g_free (path);
      return;
    }

  switch (run->state & CRANK_BENCH_RUN_MASK_RES_STATE)
    {
    case CRANK_BENCH_RUN_SUCCES:
      run->state = (run->state & ~CRANK_BENCH_RUN_MASK_RES_STATE) |
                   CRANK_BENCH_RUN_SKIP;
      run->message = g_strdup (message);
      break;

    case CRANK_BENCH_RUN_SKIP:
      break;

    case CRANK_BENCH_RUN_FAIL:
      path = crank_bench_case_get_path (run->bcase);
      g_error ("Marking skip on failed run.");
      g_free (path);
      break;
    }
}

/**
 * crank_bench_run_fail:
 * @run: A benchmark run.
 * @message: A message for failing.
 *
 * Marks this run as failed. This will not stop benchmarking, so function should
 * stop itself.
 *
 * Note that this is benchmarking, failing benchmarking should not happened
 * frequently.
 */
void
crank_bench_run_fail (CrankBenchRun *run,
                      const gchar   *message)
{
  gchar *path;

  switch (run->state & CRANK_BENCH_RUN_MASK_RUN_STATE)
    {
    case CRANK_BENCH_RUN_NOT_RUN:
    case CRANK_BENCH_RUN_RUNNING:
      break;

    case CRANK_BENCH_RUN_FINISHED:
      path = crank_bench_case_get_path (run->bcase);
      g_error ("Marking fail on already finished run: %s", path);
      g_free (path);
      return;
    }

  switch (run->state & CRANK_BENCH_RUN_MASK_RES_STATE)
    {
    case CRANK_BENCH_RUN_SUCCES:
      run->state = (run->state & ~CRANK_BENCH_RUN_MASK_RES_STATE) |
                   CRANK_BENCH_RUN_FAIL;
      run->message = g_strdup (message);
      break;

    case CRANK_BENCH_RUN_SKIP:
      path = crank_bench_case_get_path (run->bcase);
      g_error ("Marking fail on skipped run: %s", path);
      g_free (path);
      break;

    case CRANK_BENCH_RUN_FAIL:
      break;
    }
}

/**
 * crank_bench_is_running:
 * @run: A benchmark run.
 *
 * Gets whether this run is running.
 *
 * Returns: Whether this run is running.
 */
gboolean
crank_bench_is_running (CrankBenchRun *run)
{
  return (run->state & CRANK_BENCH_RUN_MASK_RUN_STATE) == CRANK_BENCH_RUN_RUNNING;
}

/**
 * crank_bench_run_get_params:
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
 * crank_bench_run_get_param:
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
 * crank_bench_run_get_param_int:
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
 * crank_bench_run_get_param_uint:
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
 * crank_bench_run_get_param_float:
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
 * crank_bench_run_get_param_double:
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
 * crank_bench_run_add_result:
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
 * crank_bench_run_add_result_int:
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
 * crank_bench_run_add_result_uint:
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
 * crank_bench_run_add_result_float:
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
 * crank_bench_run_add_result_double:
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
 * crank_bench_run_timer_start:
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
 * crank_bench_run_timer_elapsed:
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
 * crank_bench_run_timer_add_result_elapsed:
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
 * crank_bench_run_rand_boolean:
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
 * crank_bench_run_rand_int:
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
 * crank_bench_run_rand_int_range:
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
 * crank_bench_run_rand_double:
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
 * crank_bench_run_rand_double_range:
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

//////// Private functions /////////////////////////////////////////////////////

/*
 * _crank_bench_dup_table:
 * @table: (transfer none) (element-type gpointer GValue):
 *     A table to duplicate.
 *
 * Duplicates a #GHashTable with duplicated #GValue. Keys are not duplicated.
 *
 * Returns: (transfer full) (element-type gpointer GValue):
 *     A duplicated table.
 */
GHashTable*
_crank_bench_dup_table (GHashTable *table)
{
  if (table == NULL)
    {
      return NULL;
    }
  else
    {
      GHashTable *res = crank_value_table_create (g_direct_hash, g_direct_equal);
      GHashTableIter i;
      gpointer       ik;
      GValue        *iv;

      g_hash_table_iter_init (&i, table);

      while (g_hash_table_iter_next (&i, &ik, (gpointer*) &iv))
        g_hash_table_insert (res, ik, crank_value_dup (iv));

      return res;
    }
}

gboolean
_crank_bench_node_free_table (GNode    *node,
                              gpointer  userdata)
{
  if (node->data != NULL)
    {
      GHashTable *table = (GHashTable*) node->data;
      g_hash_table_unref (table);
    }
}

GNode*
_crank_bench_dup_param (GNode *param)
{
  return (param == NULL) ? NULL : g_node_copy_deep (param,
                                                    (GCopyFunc)_crank_bench_dup_table,
                                                    NULL);
}

void
_crank_bench_free_param (GNode *param)
{
  if (param != NULL)
    {
      g_node_traverse (param, G_IN_ORDER, G_TRAVERSE_ALL, -1, _crank_bench_node_free_table, NULL);
      g_node_destroy (param);
    }
}

GHashTable*
_crank_bench_table_composite (GHashTable *prev,
                              GHashTable *add)
{
  if (prev == NULL)
    {
      return _crank_bench_dup_table (add);
    }
  else if (add == NULL)
    {
      return _crank_bench_dup_table (prev);
    }
  else
    {
      GHashTable *result = _crank_bench_dup_table (prev);

      GHashTableIter i;
      gpointer       ik;
      GValue        *iv;

      g_hash_table_iter_init (&i, add);
      while (g_hash_table_iter_next (&i, &ik, (gpointer*) &iv))
        {
          GValue *value = g_hash_table_lookup (result, ik);

          if (value != NULL)
            crank_value_overwrite (value, iv);
          else
            g_hash_table_insert (result, ik, crank_value_dup (iv));
        }
      return result;
    }
}

GNode*
_crank_bench_param_composite (GNode *prev,
                              GNode *add)
{
  GNode *result = NULL;

  if (add != NULL)
    {
      GHashTable *restable;
      GNode *prevc = prev->children;
      GNode *addc = add->children;

      restable = _crank_bench_table_composite ((GHashTable*) prev->data,
                                               (GHashTable*) add->data);
      result = g_node_new (restable);

      while ((prevc != NULL) && (addc != NULL))
        {
          g_node_append (result, _crank_bench_param_composite (prevc, addc));
          prevc = prevc->next;
          addc = addc->next;
        }
      while (prevc != NULL)
        {
          g_node_append (result, _crank_bench_dup_param(prevc));
          prevc = prevc->next;
        }
      while (addc != NULL)
        {
          g_node_append (result, _crank_bench_dup_param(addc));
          addc = addc->next;
        }
    }
  else
    {
      result = _crank_bench_dup_param (prev);
    }
  return result;
}

/*
 * _crank_bench_get_suite_common:
 * @path: A Benchmark path.
 * @case_name: (out): A name for #CrankBenchCase.
 * @make_suite: Make suite if does not exist.
 *
 * A common private function for getting #CrankBenchSuite.
 *
 * Returns: (transfer none): A CrankBenchSuite.
 */
CrankBenchSuite*
_crank_bench_get_suite_common (const gchar  *path,
                               gchar       **case_name,
                               gboolean      make_suite)
{
  CrankBenchSuite *psuite = NULL;
  CrankBenchSuite *suite = NULL;
  gchar          **path_entries = NULL;
  guint            npath_entries;

  gboolean fail;
  guint i = 0;

  fail = ! crank_str_read_path (path,
                                &i,
                                &path_entries,
                                (CrankReadStrFunc)crank_str_read_canonical_word,
                                NULL);
  fail = fail || (path[i] != '\0');

  if (fail)
    {
      *case_name = NULL;
      g_warning ("Path is malformed: %s", path);
    }

  else if (path_entries[0][0] != '\0')
    {
      *case_name = NULL;
      g_warning ("Path should start with '/': %s", path);
    }

  else
    {
      npath_entries = g_strv_length (path_entries);
      npath_entries --;

      psuite = crank_bench_root;
      if (make_suite)
        {
          for (i = 1; i < npath_entries; i++)
            {
              suite = crank_bench_suite_get_suite (psuite, path_entries[i]);
              if (suite == NULL)
                {
                  suite = crank_bench_suite_new (path_entries[i], NULL);
                  crank_bench_suite_add_suite (psuite, suite);
                }
              psuite = suite;
            }
        }
      else
        {
          for (i = 1; i < npath_entries; i++)
            {
              suite = crank_bench_suite_get_suite (psuite, path_entries[i]);
              psuite = suite;
              if (suite == NULL)
                break;
            }
        }
      *case_name = (i == npath_entries) ? g_strdup (path_entries[i]) : NULL;
    }

  g_strfreev (path_entries);
  return psuite;
}

/*
 * _crank_bench_case_run1:
 * @bcase: A Benchmark case.
 * @param: A GNode <GHashTable <GQuark, GValue*>?>, which is n-ary tree of
 *     benchmark parameters.
 * @param_prev: (nullable): Inherited parameters from upper node.
 *
 * Runs benchmark cases for each parameters that passed by @param, repeating
 * for each repeat count passed by each paramter.
 *
 * Returns: A GList <CrankBenchRun>, which is list of each result of single run.
 */
GList*
_crank_bench_case_run1 (CrankBenchCase *bcase,
                        GNode          *param,
                        GHashTable     *param_prev)
{
  GNode         *param_child;
  GHashTable    *param1;

  GList         *list = NULL;

  guint i;
  guint repeat;

  if (param->data == NULL)
    param1 = param_prev;
  else if (param_prev == NULL)
    param1 = (GHashTable*) param->data;
  else
    param1 = _crank_bench_table_composite (param_prev, (GHashTable*)param->data);

  repeat = crank_value_table_get_uint (param1,
                                       GINT_TO_POINTER(g_quark_from_static_string ("repeat")),
                                       0);

  // Run benchmarks.
  if (repeat != 0)
    {
      for (i = 0; i < repeat; i++)
        {
          CrankBenchRun *run = _crank_bench_run_new (bcase, param1, i);

          _crank_bench_run_do (run);
          list = g_list_append (list, run);
        }
    }


  // Recurse to children.
  param_child = param->children;
  while (param_child != NULL)
    {
      list = g_list_concat (list, _crank_bench_case_run1 (bcase, param_child, param1));
      param_child = param_child->next;
    }


  if ((param->data != NULL) && (param_prev != NULL))
    g_hash_table_unref (param1);

  return list;

}

/**
 * _crank_bench_run_new:
 * @bcase: A Benchmark case.
 * @param: Parameters for benchmark.
 * @run_no: Run number.
 *
 * Creates a benchmark run for @run_no th run, with @param.
 *
 * Retunrs: (transfer full): A Benchmark run.
 */
CrankBenchRun*
_crank_bench_run_new (CrankBenchCase *bcase,
                      GHashTable     *param,
                      const guint     run_no)
{
  CrankBenchRun *run = g_slice_new (CrankBenchRun);

  run->bcase = bcase;
  run->runno = run_no;
  run->state = CRANK_BENCH_RUN_NOT_RUN;
  run->message = NULL;

  run->param = g_hash_table_ref (param);
  run->result_journal = g_queue_new ();

  run->timer_run = g_timer_new ();
  run->timer_user = g_timer_new ();

  run->random = g_rand_new ();

  run->result = NULL;

  return run;
}

/*
 * _crank_bench_run_free:
 * @run: A Benchmark run.
 *
 * Frees a benchmark run.
 */
void
_crank_bench_run_free (CrankBenchRun *run)
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

/*
 * _crank_bench_run_do:
 * @run: A Benchmark run.
 *
 * Performs a run of benchmark.
 */
void
_crank_bench_run_do (CrankBenchRun *run)
{
  // Check run state.
  switch (run->state & CRANK_BENCH_RUN_MASK_RUN_STATE)
    {
    case CRANK_BENCH_RUN_RUNNING:
      g_warning ("Try running already running run.");
      return;

    case CRANK_BENCH_RUN_FINISHED:
      g_warning ("Try running already finished run.");
      return;

    case CRANK_BENCH_RUN_NOT_RUN:
      break;
      // default.
    }

  // Run case.
  run->state = (run->state & ~CRANK_BENCH_RUN_MASK_RUN_STATE) |
                CRANK_BENCH_RUN_RUNNING;

  g_timer_start (run->timer_run);
  run->bcase->func (run, run->bcase->userdata);
  g_timer_stop (run->timer_run);

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
    }
}

void
_crank_bench_run_list_write (GList         *runlist,
                             gpointer       stream)
{
  GArray *param_order;  // GArray <GQuark>
  GArray *result_order; // GArray <GQuark>

  CrankBenchCase *bcase;

  GList *iter;

  GString *strbuild;
  gchar *strhold;

  guint i;

  if (runlist == NULL)
    return;

  param_order = g_array_new (FALSE, FALSE, sizeof (GQuark));
  result_order = g_array_new (FALSE, FALSE, sizeof (GQuark));

  GQuark quark_repeat = g_quark_from_string ("repeat");

  bcase = ((CrankBenchRun*)runlist->data)->bcase;


  // Collects used parameters and result names.
  for (iter = runlist; iter != NULL; iter = iter->next)
    {
      CrankBenchRun *run;
      GHashTableIter piter;
      gpointer       piterkey;
      GHashTableIter riter;
      gpointer       riterkey;

      run = (CrankBenchRun*) iter->data;

      g_hash_table_iter_init (&piter, run->param);
      while (g_hash_table_iter_next (&piter, &piterkey, NULL))
        {
          GQuark piterkeyq = (GQuark) GPOINTER_TO_INT(piterkey);

          if (piterkeyq == quark_repeat)
            continue;

          for (i = 0; i < param_order->len; i++)
            {
              if (piterkeyq == g_array_index (param_order, GQuark, i))
                break;
            }
          if (i == param_order->len)
            {
              g_array_append_val (param_order, piterkeyq);
            }
        }

      g_hash_table_iter_init (&riter, run->result);
      while (g_hash_table_iter_next (&riter, &riterkey, NULL))
        {
          GQuark riterkeyq = (GQuark) GPOINTER_TO_INT(riterkey);

          for (i = 0; i < result_order->len; i++)
            {
              if (riterkeyq == g_array_index (result_order, GQuark, i))
                break;
            }
          if (i == result_order->len)
            {
              g_array_append_val (result_order, riterkeyq);
            }
        }

    }

  // Print out case result.

  strhold = crank_bench_case_get_path (bcase);
  strbuild = g_string_new (strhold);
  g_free (strhold);

  g_string_append_c (strbuild, '\n');

  g_string_append (strbuild, "R,\tN");

  for (i = 0; i < param_order->len; i++)
    {
      g_string_append_printf (strbuild,
                              ",\t%s",
                              g_quark_to_string (g_array_index (param_order,
                                                                GQuark,
                                                                i)));
    }

  for (i = 0; i < result_order->len; i++)
    {
      g_string_append_printf (strbuild,
                              ",\t%s",
                              g_quark_to_string (g_array_index (result_order,
                                                                GQuark,
                                                                i)));
    }
  g_string_append_c (strbuild, '\n');

  for (iter = runlist; iter != NULL; iter = iter->next)
    {
      CrankBenchRun *run;

      run = (CrankBenchRun*) iter->data;

      g_string_append_printf (strbuild,
                              "%u,\t%u",
                              crank_value_table_get_uint (run->param,
                                                          GINT_TO_POINTER(quark_repeat),
                                                          0),
                              run->runno);

      for (i = 0; i < param_order->len; i++)
        {
          GValue  strvalue = {0};
          GValue *pvalue;
          GQuark  param_quark;

          param_quark = g_array_index (param_order, GQuark, i);

          g_value_init (&strvalue, G_TYPE_STRING);

          pvalue = (GValue*) g_hash_table_lookup (run->param,
                                                  GINT_TO_POINTER (param_quark));

          if (pvalue == NULL)
            {
              g_string_append (strbuild, ",\t<empty>");
            }
          else if (! g_value_transform (pvalue, &strvalue))
            {
              g_string_append (strbuild, ",\t<value>");
            }
          else
            {
              g_string_append_printf (strbuild,
                                      ",\t%s",
                                      g_value_get_string (&strvalue));
            }

          g_value_unset (&strvalue);
        }

      for (i = 0; i < result_order->len; i++)
        {
          GValue  strvalue = {0};
          GValue *pvalue;
          GQuark  result_quark;

          result_quark = g_array_index (result_order, GQuark, i);

          g_value_init (&strvalue, G_TYPE_STRING);

          pvalue = (GValue*) g_hash_table_lookup (run->result,
                                                  GINT_TO_POINTER(result_quark));

          if (pvalue == NULL)
            {
              g_string_append (strbuild, ",\t<empty>");
            }
          else if (! g_value_transform (pvalue, &strvalue))
            {
              g_string_append (strbuild, ",\t<value>");
            }
          else
            {
              g_string_append_printf (strbuild,
                                      ",\t%s",
                                      g_value_get_string (&strvalue));
            }

          g_value_unset (&strvalue);
        }
      g_string_append_c (strbuild, '\n');
    }


  g_print ("%s", strbuild->str);

  g_string_free (strbuild, TRUE);

  g_array_unref (param_order);
  g_array_unref (result_order);
}

gboolean
_crank_bench_run_list_write_node (GNode    *runnode,
                                  gpointer  usredata)
{
  _crank_bench_run_list_write ((GList*)         runnode->data,
                               NULL);

  return FALSE;
}
