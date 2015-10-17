#ifndef CRANKBENCHRUN_H
#define CRANKBENCHRUN_H

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

typedef struct _CrankBenchCase CrankBenchCase;

typedef enum _CrankBenchRunState CrankBenchRunState;
typedef enum _CrankBenchRunMark CrankBenchRunMark;

/**
 * CrankBenchRunState: (skip)
 * @CRANK_BENCH_RUN_NOT_RUN: Run is not runned.
 * @CRANK_BENCH_RUN_RUNNING: Run is running.
 * @CRANK_BENCH_RUN_FINISHED: Run is finished.
 * @CRANK_BENCH_RUN_PROCESSED: Run is processed and its results are available.
 *
 * Enumeration for state of runs.
 */
enum _CrankBenchRunState {
  CRANK_BENCH_RUN_NOT_RUN,
  CRANK_BENCH_RUN_RUNNING,
  CRANK_BENCH_RUN_FINISHED,
  CRANK_BENCH_RUN_PROCESSED
};

/**
 * CrankBenchRunMark: (skip)
 * @CRANK_BENCH_RUN_SUCCESS: Run is finished succesfully.
 * @CRANK_BENCH_RUN_SKIP: Run is skipped.
 * @CRANK_BENCH_RUN_FAIL: Run is failed.
 *
 * Enumeration for marks on runs. As this is benchmark, generally all run should
 * be finished successfully. Any errors should have been caught in unit test or
 * etc.
 */
enum _CrankBenchRunMark {
  CRANK_BENCH_RUN_SUCCESS,
  CRANK_BENCH_RUN_SKIP,
  CRANK_BENCH_RUN_FAIL
};

//////// CrankBenchRun /////////////////////////////////////////////////////////

CrankBenchRun    *crank_bench_run_new                     (CrankBenchCase        *bcase,
                                                           GHashTable            *param,
                                                           const guint            run_no);

void              crank_bench_run_free                    (CrankBenchRun         *run);

void              crank_bench_run_do                      (CrankBenchRun         *run);

void              crank_bench_run_postprocess             (CrankBenchRun         *run);


guint             crank_bench_run_get_run_no              (CrankBenchRun         *run);


gboolean          crank_bench_run_is_running              (CrankBenchRun         *run);

gboolean          crank_bench_run_is_processed            (CrankBenchRun         *run);

gboolean          crank_bench_run_is_failed               (CrankBenchRun         *run);

gboolean          crank_bench_run_is_skipped              (CrankBenchRun         *run);

CrankBenchRunState crank_bench_run_get_state              (CrankBenchRun         *run);

CrankBenchRunMark crank_bench_run_get_mark                (CrankBenchRun         *run);

gchar            *crank_bench_run_get_message             (CrankBenchRun         *run);

//////// Marking run as skip or fail ///////////////////////////////////////////
//
void              crank_bench_run_skip                    (CrankBenchRun         *run,
                                                           const gchar           *message);

void              crank_bench_run_fail                    (CrankBenchRun         *run,
                                                           const gchar           *message);

void              crank_bench_run_set_mark                (CrankBenchRun         *run,
                                                           CrankBenchRunMark      mark,
                                                           const gchar           *message);


//////// Functions for benchmarking ////////////////////////////////////////////

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

GValue           *crank_bench_run_getq_param              (CrankBenchRun         *run,
                                                           const GQuark           name);

gint              crank_bench_run_getq_param_int          (CrankBenchRun         *run,
                                                           const GQuark           name,
                                                           const int              defval);

guint             crank_bench_run_getq_param_uint         (CrankBenchRun         *run,
                                                           const GQuark           name,
                                                           const guint            defval);

gfloat            crank_bench_run_getq_param_float        (CrankBenchRun         *run,
                                                           const GQuark           name,
                                                           const gfloat           defval);

gdouble           crank_bench_run_getq_param_double       (CrankBenchRun         *run,
                                                           const GQuark           name,
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

gfloat            crank_bench_run_rand_float              (CrankBenchRun         *run);

gfloat            crank_bench_run_rand_float_range        (CrankBenchRun         *run,
                                                           const gfloat           begin,
                                                           const gfloat           end);


gdouble           crank_bench_run_rand_double             (CrankBenchRun         *run);

gdouble           crank_bench_run_rand_double_range       (CrankBenchRun         *run,
                                                           const gdouble          begin,
                                                           const gdouble          end);

gfloat*           crank_bench_run_rand_float_array        (CrankBenchRun         *run,
                                                           const guint            length);

gdouble*          crank_bench_run_rand_double_array       (CrankBenchRun         *run,
                                                           const guint            length);

/////// Functions for results //////////////////////////////////////////////////

GHashTable       *crank_bench_run_get_results             (CrankBenchRun         *run);

GValue           *crank_bench_run_get_result              (CrankBenchRun         *run,
                                                           const gchar           *name);

gint              crank_bench_run_get_result_int          (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const int              defval);

guint             crank_bench_run_get_result_uint         (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const guint            defval);

gfloat            crank_bench_run_get_result_float        (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const gfloat           defval);

gdouble           crank_bench_run_get_result_double       (CrankBenchRun         *run,
                                                           const gchar           *name,
                                                           const gdouble          defval);

GValue           *crank_bench_run_getq_result             (CrankBenchRun         *run,
                                                           const GQuark           name);

gint              crank_bench_run_getq_result_int         (CrankBenchRun         *run,
                                                           const GQuark           name,
                                                           const int              defval);

guint             crank_bench_run_getq_result_uint        (CrankBenchRun         *run,
                                                           const GQuark           name,
                                                           const guint            defval);

gfloat            crank_bench_run_getq_result_float       (CrankBenchRun         *run,
                                                           const GQuark           name,
                                                           const gfloat           defval);

gdouble           crank_bench_run_getq_result_double      (CrankBenchRun         *run,
                                                           const GQuark           name,
                                                           const gdouble          defval);


gchar            *crank_bench_run_get_param_to_string     (CrankBenchRun         *run,
                                                           const gchar           *name);

gchar            *crank_bench_run_getq_param_to_string    (CrankBenchRun         *run,
                                                           const GQuark           name);

gchar            *crank_bench_run_get_result_to_string    (CrankBenchRun         *run,
                                                           const gchar           *name);

gchar            *crank_bench_run_getq_result_to_string   (CrankBenchRun         *run,
                                                           const GQuark           name);



gchar           **crank_bench_run_get_params_to_strv      (CrankBenchRun         *run,
                                                           const gchar          **names);

gchar           **crank_bench_run_getq_params_to_strv     (CrankBenchRun         *run,
                                                           const GQuark          *names,
                                                           const guint            nnames);

gchar           **crank_bench_run_get_results_to_strv     (CrankBenchRun         *run,
                                                           const gchar          **names);

gchar           **crank_bench_run_getq_results_to_strv    (CrankBenchRun         *run,
                                                           const GQuark          *names,
                                                           const guint            nnames);


/////// Functions for list of runs /////////////////////////////////////////////

GHashTable       *crank_bench_run_list_get_param_names    (GList                 *runlist);

GHashTable       *crank_bench_run_list_get_result_names   (GList                 *runlist);

#endif
