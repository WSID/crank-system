#ifndef CRANKBENCH_H
#define CRANKBENCH_H

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


G_BEGIN_DECLS

//////// Structure declaration /////////////////////////////////////////////////

typedef struct _CrankBenchParamNode CrankBenchParamNode;
typedef struct _CrankBenchSuite CrankBenchSuite;
typedef struct _CrankBenchCase CrankBenchCase;
typedef struct _CrankBenchRun CrankBenchRun;

/**
 * CrankBenchFunc:
 * @run: A Benchmark run.
 * @userdata: (closure): A userdata for this function.
 *
 * A type for benchmarking function. As benchmarking can be repeated, Crank
 * System provides state object, instead of providing access to global structures.
 */
typedef void (*CrankBenchFunc) (CrankBenchRun *run,
                                gpointer       userdata);



//////// Overall ///////////////////////////////////////////////////////////////

void                  crank_bench_init                    (guint           *argc,
                                                           gchar         ***argv);

gboolean              crank_bench_is_initialized          (void);

gint                  crank_bench_run                     (void);

CrankBenchSuite      *crank_bench_get_root                (void);

CrankBenchSuite      *crank_bench_get_suite               (const gchar           *path);

CrankBenchCase       *crank_bench_get_case                (const gchar           *path);

void                  crank_bench_add                     (const gchar           *path,
                                                           CrankBenchFunc         func,
                                                           gpointer               userdata,
                                                           GDestroyNotify         destroy);

void                  crank_bench_add_with_param          (const gchar           *path,
                                                           CrankBenchFunc         func,
                                                           gpointer               userdata,
                                                           GDestroyNotify         destroy,
                                                           CrankBenchParamNode   *param);

void                  crank_bench_set_param               (const gchar           *path,
                                                           CrankBenchParamNode   *param);

//////// CrankBenchParamNode ///////////////////////////////////////////////////

CrankBenchParamNode  *crank_bench_param_node_new          (void);

void                  crank_bench_param_node_free         (CrankBenchParamNode   *node);

CrankBenchParamNode  *crank_bench_param_node_dup          (CrankBenchParamNode   *node);

CrankBenchParamNode  *crank_bench_param_node_dup1         (CrankBenchParamNode   *node);

const GValue         *crank_bench_param_node_get          (CrankBenchParamNode   *node,
                                                           const gchar           *name);

guint                 crank_bench_param_node_get_uint     (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const guint            defval);

gint                  crank_bench_param_node_get_int      (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const gint             defval);

gfloat                crank_bench_param_node_get_float    (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const gfloat           defval);

gdouble               crank_bench_param_node_get_double   (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const gdouble          defval);

void                  crank_bench_param_node_set          (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const GValue          *value);

void                  crank_bench_param_node_set_uint     (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const guint            value);

void                  crank_bench_param_node_set_int      (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const gint             value);

void                  crank_bench_param_node_set_float    (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const gfloat           value);

void                  crank_bench_param_node_set_double   (CrankBenchParamNode   *node,
                                                           const gchar           *name,
                                                           const gdouble          value);


const GHashTable     *crank_bench_param_node_get_table    (CrankBenchParamNode   *node);

void                  crank_bench_param_node_set_table    (CrankBenchParamNode   *node,
                                                           GHashTable            *table);

gboolean              crank_bench_param_node_is_placeholder(CrankBenchParamNode  *node);


CrankBenchParamNode  *crank_bench_param_node_get_parent   (CrankBenchParamNode   *node);

const GPtrArray      *crank_bench_param_node_get_children (CrankBenchParamNode   *node);


void                  crank_bench_param_node_add_child    (CrankBenchParamNode   *node,
                                                           CrankBenchParamNode   *child);

gboolean              crank_bench_param_node_remove_child (CrankBenchParamNode   *node,
                                                           CrankBenchParamNode   *child);

CrankBenchParamNode  *crank_bench_param_node_add_placeholder(CrankBenchParamNode *node);

CrankBenchParamNode **crank_bench_param_node_add_placeholders(CrankBenchParamNode *node,
                                                              guint                n);


CrankBenchParamNode  *crank_bench_param_node_composite    (CrankBenchParamNode   *a,
                                                           CrankBenchParamNode   *b);

//////// CrankBenchSuite ///////////////////////////////////////////////////////

CrankBenchSuite      *crank_bench_suite_new               (const gchar           *name,
                                                           CrankBenchParamNode   *param);

void                  crank_bench_suite_free              (CrankBenchSuite       *suite);


const gchar          *crank_bench_suite_get_name          (CrankBenchSuite       *suite);


void                  crank_bench_suite_set_name          (CrankBenchSuite       *suite,
                                                           const gchar           *name);


CrankBenchParamNode  *crank_bench_suite_get_param         (CrankBenchSuite       *suite);

void                  crank_bench_suite_set_param         (CrankBenchSuite       *suite,
                                                           CrankBenchParamNode   *param);

CrankBenchSuite      *crank_bench_suite_get_parent        (CrankBenchSuite       *suite);

gchar                *crank_bench_suite_get_path          (CrankBenchSuite       *suite);

void                  crank_bench_suite_add_suite         (CrankBenchSuite       *suite,
                                                           CrankBenchSuite       *child);

gboolean              crank_bench_suite_remove_suite      (CrankBenchSuite       *suite,
                                                           CrankBenchSuite       *child);

void                  crank_bench_suite_add_case          (CrankBenchSuite       *suite,
                                                           CrankBenchCase        *bcase);

gboolean              crank_bench_suite_remove_case       (CrankBenchSuite       *suite,
                                                           CrankBenchCase        *bcase);

GPtrArray            *crank_bench_suite_get_suites        (CrankBenchSuite       *suite);

GPtrArray            *crank_bench_suite_get_cases         (CrankBenchSuite       *suite);

CrankBenchSuite      *crank_bench_suite_get_suite         (CrankBenchSuite       *suite,
                                                           const gchar           *name);

CrankBenchCase       *crank_bench_suite_get_case          (CrankBenchSuite       *suite,
                                                           const gchar           *name);

GNode                *crank_bench_suite_run               (CrankBenchSuite       *suite,
                                                           CrankBenchParamNode   *param);


//////// CrankBenchCase ////////////////////////////////////////////////////////

CrankBenchCase       *crank_bench_case_new                (const gchar           *name,
                                                           CrankBenchParamNode   *param,
                                                           CrankBenchFunc         func,
                                                           gpointer               userdata,
                                                           GDestroyNotify         destroy);

void                  crank_bench_case_free               (CrankBenchCase        *bcase);


CrankBenchParamNode  *crank_bench_case_get_param          (CrankBenchCase        *bcase);

void                  crank_bench_case_set_param          (CrankBenchCase        *bcase,
                                                           CrankBenchParamNode   *param);

gchar                *crank_bench_case_get_path           (CrankBenchCase        *bcase);


CrankBenchSuite      *crank_bench_case_get_parent         (CrankBenchCase        *bcase);

GNode                *crank_bench_case_run                (CrankBenchCase        *bcase,
                                                           CrankBenchParamNode   *param);


//////// CrankBenchRun /////////////////////////////////////////////////////////

void              crank_bench_run_skip                    (CrankBenchRun         *run,
                                                           const gchar           *message);

void              crank_bench_run_fail                    (CrankBenchRun         *run,
                                                           const gchar           *message);

gboolean          crank_bench_run_is_running              (CrankBenchRun         *run);

GHashTable       *crank_bench_run_get_params              (CrankBenchRun         *run);

GValue           *crank_bench_run_get_param               (CrankBenchRun         *run,
                                                           const gchar           *name);

gint              crank_bench_run_get_param_int           (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const int              defval);

guint             crank_bench_run_get_param_uint          (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const guint            defval);

gfloat            crank_bench_run_get_param_float         (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const gfloat           defval);

gdouble           crank_bench_run_get_param_double        (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const gdouble          defval);

void              crank_bench_run_add_result              (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           GValue                *value);

void              crank_bench_run_add_result_int          (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const gint             value);

void              crank_bench_run_add_result_uint         (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const guint            value);

void              crank_bench_run_add_result_float        (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const gfloat           value);

void              crank_bench_run_add_result_double       (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const gdouble          value);

void              crank_bench_run_timer_start             (CrankBenchRun         *run);

gdouble           crank_bench_run_timer_elapsed           (CrankBenchRun         *run);

gdouble           crank_bench_run_timer_add_result_elapsed(CrankBenchRun         *run,
                                                           const gchar           *name);

gboolean          crank_bench_run_rand_boolean            (CrankBenchRun         *run);

gint32            crank_bench_run_rand_int                (CrankBenchRun         *run);

gint32            crank_bench_run_rand_int_range          (CrankBenchRun         *run,
                                                           const gint32           begin,
                                                           const gint32           end);


gdouble           crank_bench_run_rand_double             (CrankBenchRun         *run);

gdouble           crank_bench_run_rand_double_range       (CrankBenchRun         *run,
                                                           const gdouble          begin,
                                                           const gdouble          end);



G_END_DECLS


#endif
