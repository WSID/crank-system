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
#include <stdarg.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>

#include "crankbasemacro.h"
#include "crankbasemisc.h"
#include "crankvalue.h"
#include "crankstring.h"
#include "crankbench.h"
#include "crankbench-private.h"
#include "crankbenchrun.h"
#include "crankbenchresult.h"

/**
 * SECTION:crankbench
 * @title: Benchmark.
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
 * # Concepts.
 *
 * Benchmark system has similar concept to Unit tests.
 *
 * * Benchmark case: A group of measurements for single action.
 * * Benchmark suite: A group of cases and child suites to aggregate results.
 *
 * But it introduces new concepts, for benchmarking.
 *
 * * Benchmark parameters: Unlike unit tests, benchmark should be run in various
 *       situation. For this, benchmark parameters are needed.
 * * Benchmark runs: As benchmark cases are runned for several repeats,
 *       measurements are aggregated into each runs.
 * * Benchmark results: For benchmark, their results are not just pass or fail,
 *       but more than them. As single case generates multiple set of results,
 *       they are aggregated by cases and then by suites.
 *
 * # Suite and Cases.
 *
 * Benchmark system is designed to create suites and cases implicitly with path,
 * like GTest Framework, so generally you don't have to take care of suites and
 * cases.
 *
 * |[
 *     crank_bench_add ("/crank/base/mat/float/n/mul", bench_float_n_mul, NULL, NULL, NULL);
 * ]|
 *
 * This will constructs benchmark suites "crank", "base", "mat", "float", "n",
 * and case "mul" with given function.
 *
 * # Parameters
 *
 * It is frequnetly to perform benchmark with various situations. for complex
 * configuration for parameters, Benchmark system uses 2-level parameter
 * composition.
 *
 * Each suites and cases have parameter tree. In each tree, parameters are
 * stored in each node, in from of #GHashTable of #GQuark and #GValue. (can be
 * obtained by crank_bench_param_node_get_table())
 *
 * Suites and cases will inherit parameter tree from their parents, and for
 * each parameter node, they will inherit parameters from parent node.
 *
 * # Special Parameters.
 *
 * Some parameters are used by Benchmark system to accomodate runs.
 *
 * <table>
 *   <title>Special Parameters used by Benchmarking system</title>
 *   <tgroup cols="3">
 *     <thead>
 *       <row><entry>Type</entry>
 *            <entry>Name</entry>
 *            <entry>Description</entry></row>
 *     </thead>
 *
 *     <tbody>
 *       <row><entry>#guint</entry>
 *            <entry>repeat</entry>
 *            <entry>Repeat counts: how many runs will run for this parameters</entry></row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */


//////// Variables /////////////////////////////////////////////////////////////

static gboolean         crank_bench_initialized = FALSE;
static CrankBenchSuite *crank_bench_root = NULL;

static gboolean         crank_bench_message_stdout = FALSE;
static gboolean         crank_bench_message_quiet = FALSE;

static CrankBenchListOption crank_bench_list_option = CRANK_BENCH_LIST_NONE;

static GOptionEntry crank_bench_options[] = {
  {"message-stdout", '\0', G_OPTION_FLAG_NONE,
    G_OPTION_ARG_NONE, &crank_bench_message_stdout,
    "Prints message into stdout.", NULL},

  {"message-quiet", 'q', G_OPTION_FLAG_NONE,
    G_OPTION_ARG_NONE, &crank_bench_message_quiet,
    "Quiet: Do not print message.", NULL},

  {"list", 'l', G_OPTION_FLAG_OPTIONAL_ARG,
    G_OPTION_ARG_CALLBACK, &_crank_bench_arg_list,
    "list benchmark cases and parameters.", "none,case,tree,all"},

  {NULL}
};


//////// Overall ///////////////////////////////////////////////////////////////

/**
 * crank_bench_init: (skip)
 * @argc: (inout): Number of commandline arguments
 * @argv: (inout) (array length=argc): Commandline arguments
 *
 * Initialize benchmarking system.
 */
void
crank_bench_init (guint   *argc,
                  gchar ***argv)
{
  GOptionContext *context;
  GError *err = NULL;

  if (crank_bench_initialized)
    g_error ("CrankBench: Being doubly initialized.");


  context = g_option_context_new ("- a benchmark.");
  g_option_context_add_main_entries (context, crank_bench_options, NULL);
  if (! g_option_context_parse (context, argc, argv, &err))
    {
      g_error ("Option parsing error: %s\n", err->message);
      exit (0);
    }

  // Initialize Benchmarking System.
  crank_bench_root = crank_bench_suite_new ("", NULL);
  crank_bench_initialized = TRUE;


}

/**
 * crank_bench_is_initialized: (skip)
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
 * crank_bench_run: (skip)
 *
 * Runs benchmark and returns exit code to return in <function>main</function>.
 *
 * Returns: Exit code to return in main.
 */
gint
crank_bench_run (void)
{
  CrankBenchResultSuite *result;

  if (crank_bench_list_option == CRANK_BENCH_LIST_CASE)
    {
      _crank_bench_list_case (crank_bench_root);
      return 0;
    }

  if (crank_bench_list_option == CRANK_BENCH_LIST_TREE)
    {
      _crank_bench_list_tree (crank_bench_root);
      return 0;
    }

  if (crank_bench_list_option == CRANK_BENCH_LIST_ALL)
    {
      _crank_bench_list_all (crank_bench_root);
      return 0;
    }



  crank_bench_message ("\nRunning\n");
  result = crank_bench_suite_run (crank_bench_root, NULL);


  crank_bench_message ("\nPostprocessing\n");
  crank_bench_result_suite_process (result);


  crank_bench_message ("\nEmitting\n");
  return _crank_bench_run_result_emit (result);
}


/**
 * crank_bench_message: (skip)
 * @format: Format string for message.
 * @...: Printf style parameters for @format.
 *
 * Prints messages. This will be printed through stderr, so this won't mess up
 * with benchmark result. (though user has options to mix them if he wants both
 * of result and message together.)
 *
 * Returns: the number of bytes emitted as message.
 */
gint
crank_bench_message (const gchar *format,
                     ...)
{
  va_list vararg;
  gint result = 0;

  if (crank_bench_message_quiet)
    return 0;

  va_start (vararg, format);

  result = g_vfprintf (crank_bench_message_stdout ? stdout : stderr,
                       format, vararg);

  va_end (vararg);
  return result;
}

/**
 * crank_bench_value_string: (skip)
 * @value: (nullable): A value to get string.
 *
 * Creates string value from @value.
 *
 * As benchmark have to check for various values, Crank System provides simple
 * value stringification function.
 *
 * For %NULL, it returns "&lt;empty&gt;", for stringification is not availiable,
 * it returns "&lt;value&gt;".
 *
 * Returns: (transfer full): a stringification result.
 */
gchar*
crank_bench_value_string (const GValue *value)
{
  GValue strval = {0};
  gchar* str;

  if (value == NULL)
    return g_strdup ("<empty>");

  g_value_init (&strval, G_TYPE_STRING);

  if (g_value_transform (value, &strval))
    str = g_value_dup_string (&strval);
  else
    str = g_strdup ("<value>");

  g_value_unset (&strval);
  return str;
}

/**
 * crank_bench_get_root: (skip)
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
 * crank_bench_get_suite: (skip)
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
 * crank_bench_get_case: (skip)
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
 * crank_bench_add: (skip)
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
 * crank_bench_add_with_param: (skip)
 * @path: A Benchmark path.
 * @func: (scope notified): A Benchmarking function.
 * @userdata: (closure): Userdata for @func
 * @destroy: (destroy userdata): Destroy for @func
 * @param: (nullable): A Parameter node.
 *
 * Adds benchmark case at given @path, with @func, applying @param.
 */
void
crank_bench_add_with_param (const gchar         *path,
                            CrankBenchFunc       func,
                            gpointer             userdata,
                            GDestroyNotify       destroy,
                            CrankBenchParamNode *param)
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
 * crank_bench_set_param: (skip)
 * @path: A Benchmark path.
 * @param: (nullable): A Parameter node.
 *
 * sets a parameter to suite or case at @path.
 */
void
crank_bench_set_param (const gchar         *path,
                       CrankBenchParamNode *param)
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
  else
    g_warning ("Suite or case at path does not exist: %s", path);
}


//////// CrankBenchParamNode ///////////////////////////////////////////////////

/**
 * crank_bench_param_node_new: (skip)
 *
 * Constructs an empty #CrankBenchParamNode.
 *
 * Returns: (transfer full): Newly created #CrankBenchParamNode.
 */
CrankBenchParamNode*
crank_bench_param_node_new (void)
{
  CrankBenchParamNode *node = g_slice_new (CrankBenchParamNode);

  node->parent = NULL;
  node->children = g_ptr_array_new_with_free_func ((GDestroyNotify)
                                                   crank_bench_param_node_free);
  node->table = crank_value_table_create (g_direct_hash, g_direct_equal);

  return node;
}

/**
 * crank_bench_param_node_free: (skip)
 * @node: A Parameter node.
 *
 * Frees a tree of #CrankBenchParamNode, which means that its children also
 * freed.
 */
void
crank_bench_param_node_free (CrankBenchParamNode *node)
{
  if (node == NULL)
    return;

  g_ptr_array_unref (node->children);
  g_hash_table_unref (node->table);
  g_slice_free (CrankBenchParamNode, node);
}

/**
 * crank_bench_param_node_dup: (skip)
 * @node: A Parameter node.
 *
 * Duplicates a tree of #CrankBenchParamNode.
 *
 * Returns: (transfer full): Duplicated node.
 */
CrankBenchParamNode*
crank_bench_param_node_dup (CrankBenchParamNode *node)
{
  CrankBenchParamNode *dup;
  guint i;

  if (node == NULL)
    return NULL;

  dup = crank_bench_param_node_dup1 (node);
  for (i = 0; i < node->children->len; i++)
    {
      CrankBenchParamNode *subnode;

      subnode = crank_bench_param_node_dup (node->children->pdata[i]);
      crank_bench_param_node_add_child (dup, subnode);
    }

  return dup;
}

/**
 * crank_bench_param_node_dup1: (skip)
 * @node : A Parameter node.
 *
 * Duplicates single #CrankBenchParamNode. The duplication will have no child.
 *
 * Returns: (transfer full): Duplicated single node.
 */
CrankBenchParamNode*
crank_bench_param_node_dup1 (CrankBenchParamNode *node)
{
  CrankBenchParamNode *dup;

  if (node == NULL)
    return NULL;

  dup = crank_bench_param_node_new ();
  crank_bench_param_node_set_table (dup, node->table);

  return dup;
}

/**
 * crank_bench_param_node_get: (skip)
 * @node: A Parameter node.
 * @name: Parameter name.
 *
 * Gets a parameter by name, in form of #GValue.
 *
 * Returns: (transfer none) (nullable): A Value of parameter or %NULL if
 *     parameter with @name does not exist.
 */
const GValue*
crank_bench_param_node_get (CrankBenchParamNode *node,
                            const gchar         *name)
{
  return g_hash_table_lookup (node->table, CRANK_QUARK_FROM_STRING (name));
}

/**
 * crank_bench_param_node_get_uint: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @defval: Default value for failure
 *
 * Gets a unsigned integer parameter by name.
 *
 * Returns: A unsigned integer value of parameter or @defval if parameter with
 *     @name does not exist or is not unsigned integer.
 */
guint
crank_bench_param_node_get_uint (CrankBenchParamNode *node,
                                 const gchar         *name,
                                 const guint          defval)
{
  return crank_value_table_get_uint (node->table,
                                     CRANK_QUARK_FROM_STRING (name),
                                     defval);
}

/**
 * crank_bench_param_node_get_int: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @defval: Default value for failure
 *
 * Gets a integer parameter by name.
 *
 * Returns: A integer value of parameter or @defval if parameter with @name does
 *     not exist or is not integer.
 */
gint
crank_bench_param_node_get_int (CrankBenchParamNode *node,
                                const gchar         *name,
                                const gint           defval)
{
  return crank_value_table_get_int (node->table,
                                    CRANK_QUARK_FROM_STRING (name),
                                    defval);
}

/**
 * crank_bench_param_node_get_float: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @defval: Default value for failure
 *
 * Gets a float parameter by name.
 *
 * Returns: A float value of parameter or @defval if parameter with @name does
 *     not exist or is not float.
 */
gfloat
crank_bench_param_node_get_float (CrankBenchParamNode *node,
                                  const gchar         *name,
                                  const gfloat         defval)
{
  return crank_value_table_get_float (node->table,
                                      CRANK_QUARK_FROM_STRING (name),
                                      defval);
}

/**
 * crank_bench_param_node_get_double: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @defval: Default value for failure
 *
 * Gets a double parameter by name.
 *
 * Returns: A double value of parameter or @defval if parameter with @name does
 *     not exist or is not double.
 */
gdouble
crank_bench_param_node_get_double (CrankBenchParamNode *node,
                                   const gchar         *name,
                                   const gdouble        defval)
{
  return crank_value_table_get_double (node->table,
                                       CRANK_QUARK_FROM_STRING (name),
                                       defval);
}

/**
 * crank_bench_param_node_set: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @value: (transfer none): A value
 *
 * Sets a paramenter in form of #GValue.
 */
void
crank_bench_param_node_set (CrankBenchParamNode *node,
                            const gchar         *name,
                            const GValue        *value)
{
  crank_value_table_set (node->table, CRANK_QUARK_FROM_STRING (name), value);
}

/**
 * crank_bench_param_node_set_uint: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @value: A value
 *
 * Sets a unsigned integer paramenter.
 */
void
crank_bench_param_node_set_uint (CrankBenchParamNode *node,
                                 const gchar         *name,
                                 const guint          value)
{
  crank_value_table_set_uint (node->table,
                              CRANK_QUARK_FROM_STRING (name),
                              value);
}

/**
 * crank_bench_param_node_set_int: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @value: A value
 *
 * Sets a integer paramenter.
 */
void
crank_bench_param_node_set_int (CrankBenchParamNode *node,
                                const gchar         *name,
                                const gint          value)
{
  crank_value_table_set_int (node->table,
                             CRANK_QUARK_FROM_STRING (name),
                             value);
}

/**
 * crank_bench_param_node_set_float: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @value: A value
 *
 * Sets a float paramenter.
 */
void
crank_bench_param_node_set_float (CrankBenchParamNode *node,
                                  const gchar         *name,
                                  const gfloat         value)
{
  crank_value_table_set_float (node->table,
                               CRANK_QUARK_FROM_STRING (name),
                               value);
}

/**
 * crank_bench_param_node_set_double: (skip)
 * @node : A Parameter node.
 * @name: Parameter name.
 * @value: A value
 *
 * Sets a double paramenter.
 */
void
crank_bench_param_node_set_double (CrankBenchParamNode *node,
                                   const gchar         *name,
                                   const gdouble        value)
{
  crank_value_table_set_double (node->table,
                                CRANK_QUARK_FROM_STRING (name),
                                value);
}

/**
 * crank_bench_param_node_get_table: (skip)
 * @node : A Parameter node.
 *
 * Gets a parameter table, which is #GHashTable<#GQuark, #GValue*>.
 *
 * Returns: (transfer none) (element-type GQuark GValue): A parameter table.
 */
GHashTable*
crank_bench_param_node_get_table (CrankBenchParamNode *node)
{
  return node->table;
}

/**
 * crank_bench_param_node_set_table: (skip)
 * @node: A Parameter node.
 * @table: (transfer none) (element-type GQuark GValue): A parameter table.
 *
 * Sets a parameter table, which is #GHashTable<#GQuark, #GValue*>.
 */
void
crank_bench_param_node_set_table (CrankBenchParamNode *node,
                                  GHashTable          *table)
{
  g_hash_table_remove_all (node->table);
  crank_value_table_overlay (node->table, table, NULL);
}

/**
 * crank_bench_param_node_is_placeholder: (skip)
 * @node: A Parameter node.
 *
 * Checks whether it is a placeholder item.
 *
 * Often #CrankBenchParamNode s are composited through #CrankBenchSuite, some
 * portion of tree are empty, so that higher entities can come in as they were
 * in parent suites.
 *
 * See also: crank_bench_param_node_composite()
 *
 * Returns: whether it is a placeholder item.
 */
gboolean
crank_bench_param_node_is_placeholder (CrankBenchParamNode *node)
{
  return g_hash_table_size (node->table) == 0;
}

/**
 * crank_bench_param_node_get_parent: (skip)
 * @node: A Parameter node.
 *
 * Gets parent node of this @node.
 *
 * Returns: (transfer none) (nullable): The parent node, or %NULL if it is root.
 */
CrankBenchParamNode*
crank_bench_param_node_get_parent (CrankBenchParamNode *node)
{
  return node->parent;
}

/**
 * crank_bench_param_node_get_children: (skip)
 * @node: A parameter node.
 *
 * Gets childrens of this @node.
 *
 * Returns: (transfer none) (element-type CrankBenchParamNode):
 *     The children nodes.
 */
GPtrArray*
crank_bench_param_node_get_children (CrankBenchParamNode *node)
{
  return node->children;
}

/**
 * crank_bench_param_node_add_child: (skip)
 * @node: A parameter node.
 * @child: (transfer full): A children node.
 *
 * Add child node to this node.
 */
void
crank_bench_param_node_add_child (CrankBenchParamNode *node,
                                  CrankBenchParamNode *child)
{
  g_return_if_fail (child->parent == NULL);

  child->parent = node;
  g_ptr_array_add (node->children, child);
}

/**
 * crank_bench_param_node_remove_child: (skip)
 * @node: A parameter node.
 * @child: (transfer none): A children node.
 *
 * Remove a child node from this node.
 *
 * Returns: Whether the child node was removed.
 */
gboolean
crank_bench_param_node_remove_child (CrankBenchParamNode *node,
                                     CrankBenchParamNode *child)
{
  if (child->parent != node) return FALSE;

  child->parent = NULL;
  return g_ptr_array_remove (node->children, child);
}

/**
 * crank_bench_param_node_add_placeholder: (skip)
 * @node: A parameter node.
 *
 * A shorthand for adding empty node to this node.
 *
 * Returns: (transfer none): Added placeholder.
 */
CrankBenchParamNode*
crank_bench_param_node_add_placeholder (CrankBenchParamNode *node)
{
  CrankBenchParamNode *placeholder = crank_bench_param_node_new ();
  crank_bench_param_node_add_child (node, placeholder);
  return placeholder;
}

/**
 * crank_bench_param_node_add_placeholders: (skip)
 * @node: A parameter node.
 * @n: Number of placeholders to add.
 *
 * A shorthand for adding multiple empty nodes to this node.
 *
 * Returns: (array) (transfer none): Array of added placeholders.
 */
CrankBenchParamNode**
crank_bench_param_node_add_placeholders (CrankBenchParamNode *node,
                                         guint                n)
{
  guint len;
  guint i;

  len = node->children->len;

  for (i = 0; i < n; i++)
    crank_bench_param_node_add_child (node, crank_bench_param_node_new ());

  return (CrankBenchParamNode **)(node->children->pdata + len);
}

/**
 * crank_bench_param_node_composite: (skip)
 * @a: A Parameter node.
 * @b: (transfer none): Other parameter node to overlay on @a.
 *
 * Creates composite parameter node tree, of both tree of @a and @b. @b will
 * override on @a when part of both overlaps to each other.
 *
 * Returns: (transfer full): A composite parameter node tree
 */
CrankBenchParamNode*
crank_bench_param_node_composite (CrankBenchParamNode *a,
                                  CrankBenchParamNode *b)
{
  CrankBenchParamNode *node;
  guint i;
  guint n;
  // This is based on simple rule.
  // If one part is missing, return dup of other.
  // Both are present, composite and iterate.

  if (a == NULL)
    return crank_bench_param_node_dup (b);
  else if (b == NULL)
    return crank_bench_param_node_dup (a);

  // First composite the nodes themselves.

  node = crank_bench_param_node_dup1 (a);
  crank_value_table_overlay (node->table, b->table, NULL);

  n = MIN (a->children->len, b->children->len);

  for (i = 0; i < n; i++)
    {
      CrankBenchParamNode *subnode;

      subnode = crank_bench_param_node_composite (a->children->pdata[i],
                                                  b->children->pdata[i]);

      crank_bench_param_node_add_child (node, subnode);
    }

  for (; i < a->children->len; i++)
    {
      CrankBenchParamNode *subnode;
      subnode = crank_bench_param_node_dup (a->children->pdata[i]);

      crank_bench_param_node_add_child (node, subnode);
    }

  for (; i < b->children->len; i++)
    {
      CrankBenchParamNode *subnode;
      subnode = crank_bench_param_node_dup (b->children->pdata[i]);

      crank_bench_param_node_add_child (node, subnode);
    }

  return node;
}


//////// CrankBenchSuite ///////////////////////////////////////////////////////

/**
 * crank_bench_suite_new: (skip)
 * @name: A Name of benchmark suite.
 * @param: (nullable) (transfer none): A Parameter node to use.
 *
 * Creates new benchmark suite.
 *
 * Returns: (transfer full): A newly created benchmark suite.
 */
CrankBenchSuite*
crank_bench_suite_new (const gchar         *name,
                       CrankBenchParamNode *param)
{
  CrankBenchSuite *suite = g_slice_new (CrankBenchSuite);

  suite->name = g_strdup (name);
  suite->parent = NULL;
  suite->subsuites = g_ptr_array_new_with_free_func ((GDestroyNotify)crank_bench_suite_free);
  suite->cases = g_ptr_array_new_with_free_func ((GDestroyNotify)crank_bench_case_free);
  suite->param = crank_bench_param_node_dup (param);

  return suite;
}

/**
 * crank_bench_suite_free: (skip)
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
  crank_bench_param_node_free (suite->param);

  g_slice_free (CrankBenchSuite, suite);
}

/**
 * crank_bench_suite_get_name: (skip)
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
 * crank_bench_suite_set_name: (skip)
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
 * crank_bench_suite_get_param: (skip)
 * @suite: A benchmark suite.
 *
 * Gets benchmark parameters of suite.
 *
 * Returns: (nullable) (transfer none): A Parameter node, or %NULL if there is
 *     no parameter.
 */
CrankBenchParamNode*
crank_bench_suite_get_param (CrankBenchSuite *suite)
{
  return suite->param;
}

/**
 * crank_bench_suite_set_param: (skip)
 * @suite: A benchmark suite.
 * @param: (nullable) (transfer none): A tree of parameter node, or %NULL to
 *     remove parameter.
 *
 * Sets benchmark parameters of suite.
 */
void
crank_bench_suite_set_param (CrankBenchSuite     *suite,
                             CrankBenchParamNode *param)
{
  crank_bench_param_node_free (suite->param);
  suite->param = crank_bench_param_node_dup (param);

}

/**
 * crank_bench_suite_get_parent: (skip)
 * @suite: A benchmark suite.
 *
 * Gets parent suite of benchmark suite.
 *
 * Returns: (transfer none) (nullable): A parent suite, or %NULL if it is root.
 */
CrankBenchSuite*
crank_bench_suite_get_parent (CrankBenchSuite *suite)
{
  return suite->parent;
}

/**
 * crank_bench_suite_get_path: (skip)
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
 * crank_bench_suite_add_suite: (skip)
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
 * crank_bench_suite_remove_suite: (skip)
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
 * crank_bench_suite_add_case: (skip)
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
 * crank_bench_suite_remove_case: (skip)
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
 * crank_bench_suite_get_suites: (skip)
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
 * crank_bench_suite_get_cases: (skip)
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
 * crank_bench_suite_get_suite: (skip)
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
 * crank_bench_suite_get_case: (skip)
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
 * crank_bench_suite_run: (skip)
 * @suite: A benchmark suite.
 * @param: (nullable) (transfer none): A Parameter node, from higher suite or
 *     test runner.
 *
 * Runs benchmark suite, recursively.
 *
 * Returns: (transfer full): A benchmark result.
 */
CrankBenchResultSuite*
crank_bench_suite_run (CrankBenchSuite     *suite,
                       CrankBenchParamNode *param)
{
  CrankBenchResultSuite *result;
  CrankBenchParamNode *mparam;
  guint i;

  if (suite->param == NULL)
    mparam = param;
  else if (param == NULL)
    mparam = suite->param;
  else
    mparam = crank_bench_param_node_composite (param, suite->param);

  result = crank_bench_result_suite_new (suite);

  for (i = 0; i < suite->cases->len; i++)
    {
      CrankBenchCase *bcase = (CrankBenchCase*)suite->cases->pdata[i];
      CrankBenchResultCase *cres = crank_bench_case_run (bcase, mparam);
      crank_bench_result_suite_add_cresult (result, cres);
    }

  for (i = 0; i < suite->subsuites->len; i++)
    {
      CrankBenchSuite *subsuite = (CrankBenchSuite*)suite->subsuites->pdata[i];
      CrankBenchResultSuite *sres = crank_bench_suite_run (subsuite, mparam);
      crank_bench_result_suite_add_sresult (result, sres);
    }

  if ((suite->param != NULL) && (param != NULL))
    crank_bench_param_node_free (mparam);

  return result;
}

//////// CrankBenchCase ////////////////////////////////////////////////////////

/**
 * crank_bench_case_new: (skip)
 * @name: name of benchmark case.
 * @param: (nullable): A Parameter node.
 * @func: (scope notified): A benchmark function.
 * @userdata: (closure): Userdata for @func.
 * @destroy: (destroy userdata): Destroy function for @userdata.
 *
 * Creates new benchmark case.
 *
 * Returns: (transfer full): Newly created benchmark case.
 */
CrankBenchCase*
crank_bench_case_new (const gchar         *name,
                      CrankBenchParamNode *param,
                      CrankBenchFunc       func,
                      gpointer             userdata,
                      GDestroyNotify       destroy)
{
  CrankBenchCase *bcase = g_slice_new (CrankBenchCase);

  bcase->name = g_strdup (name);
  bcase->param = crank_bench_param_node_dup (param);
  bcase->func = func;
  bcase->userdata = userdata;
  bcase->destroy = destroy;

  return bcase;
}

/**
 * crank_bench_case_free: (skip)
 * @bcase: A benchmark case.
 *
 * Frees a benchmark case, and deallocates its resources.
 */
void
crank_bench_case_free (CrankBenchCase *bcase)
{
  g_free (bcase->name);
  crank_bench_param_node_free (bcase->param);
  bcase->destroy (bcase->userdata);

  g_slice_free (CrankBenchCase, bcase);
}


/**
 * crank_bench_case_get_name: (skip)
 * @bcase: A Benchmark case.
 *
 * Gets name of benchmark case.
 *
 * Returns: (transfer none): The name of case.
 */
const gchar*
crank_bench_case_get_name (CrankBenchCase *bcase)
{
  return bcase->name;
}


/**
 * crank_bench_case_set_name: (skip)
 * @bcase: A Benchmark case.
 * @name: (transfer none): The new name of case.
 *
 * Set name of benchmark case.
 */
void
crank_bench_case_set_name (CrankBenchCase *bcase,
                           const gchar    *name)
{
  g_free (bcase->name);
  bcase->name = g_strdup (name);
}


/**
 * crank_bench_case_get_param: (skip)
 * @bcase: A benchmark case.
 *
 * Gets benchmark parameter of case.
 *
 * Returns: (nullable) (transfer none): A Parameter node or %NULL, if case does
 *     not have parameter.
 */
CrankBenchParamNode*
crank_bench_case_get_param (CrankBenchCase *bcase)
{
  return bcase->param;
}

/**
 * crank_bench_case_set_param: (skip)
 * @bcase: A benchmark case.
 * @param: (nullable) (transfer none): A parameter node or %NULL, to remove
 *     parameter.
 *
 * Sets benchmark parameter of case.
 */
void
crank_bench_case_set_param (CrankBenchCase      *bcase,
                            CrankBenchParamNode *param)
{
  crank_bench_param_node_free (bcase->param);
  bcase->param = crank_bench_param_node_dup (param);
}


/**
 * crank_bench_case_get_path: (skip)
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
 * crank_bench_case_get_parent: (skip)
 * @bcase: A benchmark case.
 *
 * Gets parent of benchmark case.
 *
 * Returns: (transfer none): A parent suite of case or %NULL, if case is not
 *     added yet.
 */
CrankBenchSuite*
crank_bench_case_get_parent (CrankBenchCase *bcase)
{
  return bcase->parent;
}

/**
 * crank_bench_case_run: (skip)
 * @bcase: A benchmark case.
 * @param: (nullable) (transfer none): A Parameter node from suites or test
 *     runners.
 *
 * Runs benchmarks for single case.
 *
 * Returns: (transfer full): A run result.
 */
CrankBenchResultCase*
crank_bench_case_run (CrankBenchCase      *bcase,
                      CrankBenchParamNode *param)
{
  CrankBenchResultCase *result;
  CrankBenchParamNode *mparam;
  gchar *path;

  path = crank_bench_case_get_path (bcase);

  if (bcase->param == NULL)
    mparam = param;
  else if (param == NULL)
    mparam = bcase->param;
  else
    mparam = crank_bench_param_node_composite (param, bcase->param);

  result = crank_bench_result_case_new (bcase);

  crank_bench_message ("%s: ", path);

  if (mparam == NULL)
    {
      crank_bench_message ("SKIP\n");
      g_warning ("No benchmark parameter for case %s", path);
    }
  else
    {
      _crank_bench_case_run1 (bcase, result, mparam, NULL);

      if ((bcase->param != NULL) && (param != NULL))
        crank_bench_param_node_free (mparam);

      crank_bench_message ("OK\n");
    }


  g_free (path);
  return result;
}
//////// Private functions /////////////////////////////////////////////////////

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

gboolean
_crank_bench_arg_list (const gchar  *option_name,
                       const gchar  *value,
                       gpointer      workbench,
                       GError      **error)
{
  if (value == NULL)
    {
      crank_bench_list_option = CRANK_BENCH_LIST_CASE;
    }
  else
    {
      gchar *lvalue = g_ascii_strdown (value, -1);

      crank_bench_list_option =
          (strcmp (lvalue, "none") == 0) ? CRANK_BENCH_LIST_NONE :
          (strcmp (lvalue, "case") == 0) ? CRANK_BENCH_LIST_CASE :
          (strcmp (lvalue, "tree") == 0) ? CRANK_BENCH_LIST_TREE :
          (strcmp (lvalue, "all") == 0)  ? CRANK_BENCH_LIST_ALL :
          -1;

      if (crank_bench_list_option == -1)
        {
          g_set_error (error,
                       G_OPTION_ERROR,
                       G_OPTION_ERROR_BAD_VALUE,
                       "Bad Value: "
                       "--%s option only allows "
                           "\"none\", \"case\", \"tree\", \"all\": "
                       "received %s",
                       option_name,
                       value);
        }
      g_free (lvalue);
    }
  return (crank_bench_list_option != -1);
}


void
_crank_bench_list_case (CrankBenchSuite *suite)
{
  GString *gstr = g_string_new (NULL);

  _crank_bench_list_case_gstr (suite, gstr);

  g_string_free (gstr, TRUE);
}

void
_crank_bench_list_case_gstr (CrankBenchSuite *suite,
                             GString         *gstr)
{
  guint pos;
  guint i;

  g_string_append_printf (gstr, "%s/", suite->name);
  pos = gstr->len;

  for (i = 0; i < suite->cases->len; i++)
    {
      CrankBenchCase *bcase;

      bcase = (CrankBenchCase*) suite->cases->pdata[i];

      crank_bench_message ("%s%s\n", gstr->str, bcase->name);
    }

  for (i = 0; i < suite->subsuites->len; i++)
    {
      CrankBenchSuite *subsuite;

      subsuite = (CrankBenchSuite*) suite->subsuites->pdata[i];

      g_string_truncate (gstr, pos);
      _crank_bench_list_case_gstr (subsuite, gstr);
    }
}

void
_crank_bench_list_tree (CrankBenchSuite *suite)
{
  _crank_bench_list_tree_suite (suite, 0);
}

void
_crank_bench_list_tree_suite (CrankBenchSuite *suite,
                              const guint      depth)
{
  guint ndepth;
  guint i;

  ndepth = depth + 1;

  crank_bench_message ("%*s%s/\n", depth * 2, "", suite->name);

  for (i = 0; i < suite->cases->len; i++)
    {
      CrankBenchCase *bcase;

      bcase = (CrankBenchCase*) suite->cases->pdata[i];

      crank_bench_message ("%*s%s\n", ndepth * 2, "", bcase->name);
    }

  for (i = 0; i < suite->subsuites->len; i++)
    {
      CrankBenchSuite *subsuite;

      subsuite = (CrankBenchSuite*) suite->subsuites->pdata[i];
      _crank_bench_list_tree_suite (subsuite, ndepth);
    }
}


void
_crank_bench_list_all (CrankBenchSuite *suite)
{
  _crank_bench_list_all_suite (suite, 0);
}

void
_crank_bench_list_all_suite (CrankBenchSuite *suite,
                              const guint      depth)
{
  guint ndepth;
  guint i;

  ndepth = depth + 1;

  crank_bench_message ("%*s%s/\n", depth * 2, "", suite->name);
  _crank_bench_list_all_param (suite->param, ndepth);
  crank_bench_message ("\n");

  for (i = 0; i < suite->cases->len; i++)
    {
      CrankBenchCase *bcase;

      bcase = (CrankBenchCase*) suite->cases->pdata[i];

      crank_bench_message ("%*s%s\n", ndepth * 2, "", bcase->name);
      _crank_bench_list_all_param (bcase->param, ndepth + 1);
      crank_bench_message ("\n");
    }

  for (i = 0; i < suite->subsuites->len; i++)
    {
      CrankBenchSuite *subsuite;

      subsuite = (CrankBenchSuite*) suite->subsuites->pdata[i];
      _crank_bench_list_all_suite (subsuite, ndepth);
    }
}

void
_crank_bench_list_all_param (CrankBenchParamNode *param,
                             const guint          depth)
{
  guint ndepth = depth + 1;

  if (param == NULL)
    {
      crank_bench_message ("%*sNo Parameter Modification.\n", depth * 2, "");
      return;
    }

  {
    GHashTable *table;
    GHashTableIter ti;
    gpointer tik, tiv;

    table = crank_bench_param_node_get_table (param);
    g_hash_table_iter_init (&ti, table);
    while (g_hash_table_iter_next (&ti, &tik, &tiv))
      {
        gchar *vstring = crank_bench_value_string ((GValue*)tiv);
        crank_bench_message ("%*s%s = %s;\n",
                             depth * 2,
                             "",
                             CRANK_QUARK_TO_STRING (tik),
                             vstring);
        g_free (vstring);
      }
  }

  {
    GPtrArray *children;
    guint i;

    children = crank_bench_param_node_get_children (param);

    for (i = 0; i <children->len; i++)
      {
        CrankBenchParamNode *child = (CrankBenchParamNode*) children->pdata[i];

        if (crank_bench_param_node_is_placeholder (child))
          {
            crank_bench_message ("%*s{}\n", depth * 2, "");
          }
        else
          {
            crank_bench_message ("%*s{\n", depth * 2, "");
            _crank_bench_list_all_param (child, ndepth);
            crank_bench_message ("%*s}\n", depth * 2, "");
          }
      }
  }

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
void
_crank_bench_case_run1 (CrankBenchCase      *bcase,
                        CrankBenchResultCase *result,
                        CrankBenchParamNode *param,
                        GHashTable          *param_prev)
{
  GHashTable    *param1;

  guint i;
  guint repeat;

  if (crank_bench_param_node_is_placeholder (param))
    {
      param1 = param_prev;
    }
  else if (param_prev == NULL)
    {
      param1 = param->table;
    }
  else
    {
      param1 = crank_value_table_dup (param_prev, g_direct_hash, g_direct_equal, NULL, NULL);
      crank_value_table_overlay (param1, param->table, NULL);
    }

  repeat = crank_value_table_get_uint (param1,
                                       CRANK_QUARK_FROM_STRING("repeat"),
                                       0);

  for (i = 0; i < repeat; i++)
    {
      CrankBenchRun *run = crank_bench_run_new (bcase, param1, i);
      crank_bench_run_run (run);
      crank_bench_result_case_add_run (result, run);
    }

  // Recurse to children.
  for (i = 0; i < param->children->len; i++)
    {
      CrankBenchParamNode *param_child;

      param_child = (CrankBenchParamNode*) param->children->pdata[i];
      _crank_bench_case_run1 (bcase, result, param_child, param1);
    }

  if ((! crank_bench_param_node_is_placeholder (param)) && (param_prev != NULL))
    g_hash_table_unref (param1);
}

void
_crank_bench_emit_output (const gchar *format,
                          ...)
{
  va_list vararg;

  va_start (vararg, format);
  g_vprintf (format, vararg);
  va_end (vararg);
}


gint
_crank_bench_run_result_emit (CrankBenchResultSuite *result)
{
  GList *caselist;
  GList *iter;

  gint exitcode = 0;

  caselist = crank_bench_result_suite_get_cresults_flat (result);
  for (iter = caselist; iter != NULL; iter = iter->next)
    {
      CrankBenchResultCase *caseresult;
      caseresult = (CrankBenchResultCase*)iter->data;

      exitcode = exitcode ||
                 _crank_bench_run_result_emit_case (caseresult);
    }
  return exitcode;
}

gint
_crank_bench_run_result_emit_case (CrankBenchResultCase *result)
{
  CrankBenchCase *bcase;

  GList *run_list;
  GList *run_iter;

  GHashTable *params;
  GHashTable *results;

  guint nparams;
  guint nresults;

  GQuark* parray;
  GQuark* rarray;

  GHashTableIter hi;
  gpointer hik;

  GString *strbuild;

  guint nfail = 0;
  guint nskip = 0;

  guint i;


  // Prepare things.
  GQuark quark_repeat = g_quark_from_string ("repeat");
  gpointer quark_repeatq = GINT_TO_POINTER (quark_repeat);


  bcase = crank_bench_result_case_get_case (result);
  run_list = crank_bench_result_case_get_run_list (result);

  if (run_list == NULL)
    return 0;

  params = crank_bench_run_list_get_param_names (run_list);
  results = crank_bench_run_list_get_result_names (run_list);

  g_hash_table_remove (params, quark_repeatq);

  nparams = g_hash_table_size (params);
  nresults = g_hash_table_size (results);


  parray = g_new (GQuark, nparams);
  rarray = g_new (GQuark, nresults);

  i = 0;
  g_hash_table_iter_init (&hi, params);
  while (g_hash_table_iter_next (&hi, &hik, NULL))
    parray[i++] = (GQuark) GPOINTER_TO_INT (hik);

  i = 0;
  g_hash_table_iter_init (&hi, results);
  while (g_hash_table_iter_next (&hi, &hik, NULL))
    rarray[i++] = (GQuark) GPOINTER_TO_INT (hik);

  strbuild = g_string_new (NULL);

  // Print out case result.

  // Print out path!
  {
    gchar *path = crank_bench_case_get_path (bcase);
    g_string_append_printf (strbuild, "%s\n", path);
    g_free (path);
  }


  // Print header.
  {
    const gchar** headerpv;
    const gchar** headerrv;
    gchar* headerp;
    gchar* headerr;

    headerpv = crank_qarray_to_strv (parray, nparams);
    headerrv = crank_qarray_to_strv (rarray, nresults);
    headerp = g_strjoinv (",\t", (gchar**)headerpv);
    headerr = g_strjoinv (",\t", (gchar**)headerrv);

    g_string_append_printf (strbuild, "R   ,N   ,\t%s,\t%s\n", headerp, headerr);

    g_free (headerpv);
    g_free (headerrv);
    g_free (headerp);
    g_free (headerr);
  }

  for (run_iter = run_list; run_iter != NULL; run_iter = run_iter->next)
    {
      CrankBenchRun *run;
      gchar** recordpv = NULL;
      gchar** recordrv = NULL;
      gchar* recordp;
      gchar* recordr;

      run = (CrankBenchRun*) run_iter->data;

      recordpv = crank_bench_run_getq_params_to_strv (run, parray, nparams);
      recordp = g_strjoinv (",\t", recordpv);

      if (crank_bench_run_is_failed (run))
        {
          recordr = g_strdup_printf ("FAIL: %s", crank_bench_run_get_message (run));
          nfail ++;
        }
      else if (crank_bench_run_is_skipped (run))
        {
          recordr = g_strdup_printf ("SKIP: %s", crank_bench_run_get_message (run));
          nskip ++;
        }
      else
        {
          recordrv = crank_bench_run_getq_results_to_strv (run, rarray, nresults);
          recordr = g_strjoinv (",\t", recordrv);
        }


      g_string_append_printf (strbuild,
                              "%3u,%3u,\t%s,\t%s\n",
                              crank_bench_run_get_param_uint (run, "repeat", 0),
                              crank_bench_run_get_run_no (run),
                              recordp,
                              recordr);

      g_free (recordpv);
      g_free (recordrv);
      g_free (recordp);
      g_free (recordr);
    }

  // Add aggregation results.

  g_string_append_printf (strbuild, "SKIPS:%u,\tFAILS:%u\n", nskip, nfail);

  _crank_bench_emit_output ("%s\n", strbuild->str);
  g_string_free (strbuild, TRUE);

  g_hash_table_unref (params);
  g_hash_table_unref (results);
  g_free (parray);
  g_free (rarray);

  g_list_free (run_list);

  return (nfail != 0) || (nskip != 0);
}
