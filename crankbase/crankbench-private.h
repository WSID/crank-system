#ifndef CRANKBENCH_PRIVATE_H
#define CRANKBENCH_PRIVATE_H

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

#include "crankbench.h"

G_BEGIN_DECLS


//////// Private type declaration //////////////////////////////////////////////

typedef enum {
  CRANK_BENCH_LIST_NONE,
  CRANK_BENCH_LIST_CASE,
  CRANK_BENCH_LIST_TREE,
  CRANK_BENCH_LIST_ALL
} CrankBenchListOption;

typedef struct _CrankBenchResultEntry {
  GQuark   name;
  GValue   value;
} CrankBenchResultEntry;

//////// Structure Definition //////////////////////////////////////////////////

/**
 * CrankBenchParamNode:
 *
 * A structure represents benchmarking parameters variation hierarchy.
 */
struct _CrankBenchParamNode {
  CrankBenchParamNode  *parent;
  GPtrArray            *children;
  GHashTable           *table;
};

/**
 * CrankBenchSuite:
 *
 * A structure represents a collection of benchmark cases.
 */
struct _CrankBenchSuite {
  gchar               *name;
  CrankBenchSuite     *parent;
  CrankBenchParamNode *param;

  GPtrArray *subsuites;
  GPtrArray *cases;
};

/**
 * CrankBenchCase:
 *
 * A structure represents a benchmark case.
 */
struct _CrankBenchCase {
  gchar               *name;

  CrankBenchSuite     *parent;
  CrankBenchParamNode *param;

  CrankBenchFunc func;
  gpointer       userdata;
  GDestroyNotify destroy;
};

//////// Private functions /////////////////////////////////////////////////////

CrankBenchSuite        *_crank_bench_get_suite_common   (const gchar  *path,
                                                         gchar       **case_name,
                                                         gboolean      make_suite);

gboolean                _crank_bench_arg_list           (const gchar  *option_name,
                                                         const gchar  *value,
                                                         gpointer      workbench,
                                                         GError      **error);

void                    _crank_bench_list_case          (CrankBenchSuite     *suite);

void                    _crank_bench_list_case_gstr     (CrankBenchSuite     *suite,
                                                         GString             *gstr);

void                    _crank_bench_list_tree          (CrankBenchSuite     *suite);

void                    _crank_bench_list_tree_suite    (CrankBenchSuite     *suite,
                                                         const guint          depth);

void                    _crank_bench_list_all           (CrankBenchSuite     *suite);

void                    _crank_bench_list_all_suite     (CrankBenchSuite     *suite,
                                                         const guint          depth);

void                    _crank_bench_list_all_param     (CrankBenchParamNode *suite,
                                                         const guint          depth);



void                    _crank_bench_case_run1          (CrankBenchCase      *bcase,
                                                         CrankBenchResultCase *result,
                                                         CrankBenchParamNode *param,
                                                         GHashTable          *param_prev);

void                    _crank_bench_emit_output        (const gchar *format, ...);

gint                    _crank_bench_run_result_emit    (CrankBenchResultSuite *result);

gint                    _crank_bench_run_result_emit_case(CrankBenchResultCase  *result);
G_END_DECLS

#endif
