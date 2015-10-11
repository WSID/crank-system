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

typedef struct _CrankBenchParamStore CrankBenchParamStore;
typedef struct _CrankBenchSuite CrankBenchSuite;
typedef struct _CrankBenchCase CrankBenchCase;
typedef struct _CrankBenchRun CrankBenchRun;

typedef void (*CrankBenchFunc) (CrankBenchRun *run,
                                gpointer       userdata);



//////// Overall ///////////////////////////////////////////////////////////////

void                  crank_bench_init                    (guint           *argc,
                                                           gchar         ***argv);

gint                  crank_bench_run                     (void);

CrankBenchSuite      *crank_bench_get_root                (void);

//////// CrankBenchParamStore ///////////////////////////////////////////////////////

CrankBenchParamStore *crank_bench_param_store_new         (const guint            length);

guint                 crank_bench_param_store_get_length  (CrankBenchParamStore  *param);

void                  crank_bench_param_store_set_length  (CrankBenchParamStore  *param,
                                                           const guint            length);

guint                 crank_bench_param_store_get_repeat  (CrankBenchParamStore  *param,
                                                           const guint            index);

void                  crank_bench_param_store_set_repeat  (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const guint            repeat);

GHashTable           *crank_bench_param_store_get_table   (CrankBenchParamStore  *param,
                                                           const guint            index);

void                  crank_bench_param_store_set_table   (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           GHashTable            *table);


GValue               *crank_bench_param_store_get         (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name);

void                  crank_bench_param_store_set         (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name,
                                                           GValue                *value);

gint                  crank_bench_param_store_get_int     (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name);

guint                 crank_bench_param_store_get_uint    (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name);

gfloat                crank_bench_param_store_get_float   (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name);

gdouble               crank_bench_param_store_get_double  (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name);


void                  crank_bench_param_store_set_int     (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name,
                                                           const gint             value);

void                  crank_bench_param_store_set_uint    (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name,
                                                           const guint            value);

void                  crank_bench_param_store_set_float   (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name,
                                                           const gfloat           value);

void                  crank_bench_param_store_set_double  (CrankBenchParamStore  *param,
                                                           const guint            index,
                                                           const gchar           *name,
                                                           const gdouble          value);



//////// CrankBenchSuite ///////////////////////////////////////////////////////

void                  crank_bench_suite_new               (const gchar           *name,
                                                           CrankBenchParamStore  *param);

const gchar          *crank_bench_suite_get_name          (CrankBenchSuite       *suite);


void                  crank_bench_suite_set_name          (CrankBenchSuite       *suite,
                                                           const gchar           *name);


CrankBenchParamStore  *crank_bench_suite_get_param        (CrankBenchSuite       *suite);

void                  crank_bench_suite_set_param         (CrankBenchSuite       *suite,
                                                           CrankBenchParamStore  *param);


void                  crank_bench_suite_add_suite         (CrankBenchSuite       *suite,
                                                           CrankBenchSuite       *child);

void                  crank_bench_suite_add_case          (CrankBenchSuite       *suite,
                                                           CrankBenchCase        *bcase);

GList*                crank_bench_suite_run               (CrankBenchSuite       *suite);


//////// CrankBenchCase ////////////////////////////////////////////////////////

void              crank_bench_case_new                    (const gchar           *name,
                                                           CrankBenchParamStore  *param,
                                                           CrankBenchFunc         func,
                                                           gpointer               userdata);

GList*            crank_bench_case_run                    (CrankBenchCase        *bcase);


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
                                                           const gchar           *name);

guint             crank_bench_run_get_param_uint          (CrankBenchRun         *run,
                                                           const gchar           *name);

gfloat            crank_bench_run_get_param_float         (CrankBenchRun         *run,
                                                           const gchar           *name);

gdouble           crank_bench_run_get_param_double        (CrankBenchRun         *run,
                                                           const gchar           *name);

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
