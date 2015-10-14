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

typedef enum _CrankBenchRunState {
  CRANK_BENCH_RUN_NOT_RUN = 0 << 0,
  CRANK_BENCH_RUN_RUNNING = 1 << 0,
  CRANK_BENCH_RUN_FINISHED = 2 << 0,

  CRANK_BENCH_RUN_SUCCES = 0 << 4,
  CRANK_BENCH_RUN_SKIP = 1 << 4,
  CRANK_BENCH_RUN_FAIL = 2 << 4,

  CRANK_BENCH_RUN_MASK_RUN_STATE = 15,
  CRANK_BENCH_RUN_MASK_RES_STATE = 15 << 4
} CrankBenchRunState;

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

/**
 * CrankBenchRun:
 *
 * A structure represents a running benchmark.
 */
struct _CrankBenchRun {
  CrankBenchCase       *bcase;
  guint                 runno;
  CrankBenchRunState    state;
  gchar                *message;

  GHashTable           *param;
  GQueue               *result_journal;

  GTimer               *timer_run;
  GTimer               *timer_user;

  GRand                *random;


  GHashTable           *result;
};

//////// Private functions /////////////////////////////////////////////////////

GHashTable             *_crank_bench_dup_table          (GHashTable   *other);

GHashTable             *_crank_bench_table_composite    (GHashTable   *prev,
                                                         GHashTable   *add);

CrankBenchSuite        *_crank_bench_get_suite_common   (const gchar  *path,
                                                         gchar       **case_name,
                                                         gboolean      make_suite);

GList                  *_crank_bench_case_run1          (CrankBenchCase      *bcase,
                                                         CrankBenchParamNode *param,
                                                         GHashTable          *param_prev);

CrankBenchRun          *_crank_bench_run_new            (CrankBenchCase *bcase,
                                                         GHashTable     *param,
                                                         const guint     run_no);

void                    _crank_bench_run_free           (CrankBenchRun  *run);

void                    _crank_bench_run_do             (CrankBenchRun  *run);

void                    _crank_bench_run_list_write     (GList          *runlist,
                                                         gpointer        stream);

gboolean                _crank_bench_run_list_write_node(GNode          *runnode,
                                                         gpointer        userdata);

G_END_DECLS

#endif
