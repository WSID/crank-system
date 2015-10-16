#ifndef CRANKBENCHRESULT_H
#define CRANKBENCHRESULT_H

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
#include "crankbenchrun.h"

G_BEGIN_DECLS

//////// CrankBenchResult //////////////////////////////////////////////////////

CrankBenchResultSuite  *crank_bench_result_suite_new            (CrankBenchSuite       *suite);

void                    crank_bench_result_suite_free           (CrankBenchResultSuite *result);

CrankBenchSuite        *crank_bench_result_suite_get_suite      (CrankBenchResultSuite *result);

CrankBenchResultSuite  *crank_bench_result_suite_get_parent     (CrankBenchResultSuite *result);

void                    crank_bench_result_suite_add_sresult    (CrankBenchResultSuite *result,
                                                                 CrankBenchResultSuite *sres);

void                    crank_bench_result_suite_add_cresult    (CrankBenchResultSuite *result,
                                                                 CrankBenchResultCase  *cres);

gboolean                crank_bench_result_suite_remove_sresult (CrankBenchResultSuite *result,
                                                                 CrankBenchResultSuite *sres);

gboolean                crank_bench_result_suite_remove_cresult (CrankBenchResultSuite *result,
                                                                 CrankBenchResultCase  *cres);

GPtrArray              *crank_bench_result_suite_get_sresults   (CrankBenchResultSuite *result);

GPtrArray              *crank_bench_result_suite_get_cresults   (CrankBenchResultSuite *result);

CrankBenchResultSuite  *crank_bench_result_suite_get_sresult    (CrankBenchResultSuite *result,
                                                                 const gchar           *name);

CrankBenchResultCase   *crank_bench_result_suite_get_cresult    (CrankBenchResultSuite *result,
                                                                 const gchar           *name);

GList                  *crank_bench_result_suite_get_cresults_flat (CrankBenchResultSuite *result);

GList                  *crank_bench_result_suite_get_runs        (CrankBenchResultSuite *result);

GList                  *crank_bench_result_suite_get_runs_flat   (CrankBenchResultSuite *result);

void                    crank_bench_result_suite_postprocess     (CrankBenchResultSuite *result);



CrankBenchResultCase   *crank_bench_result_case_new              (CrankBenchCase        *bcase);

void                    crank_bench_result_case_free             (CrankBenchResultCase  *result);

CrankBenchCase         *crank_bench_result_case_get_case         (CrankBenchResultCase  *result);

CrankBenchResultSuite  *crank_bench_result_case_get_parent       (CrankBenchResultCase  *result);

void                    crank_bench_result_case_add_run          (CrankBenchResultCase *result,
                                                                  CrankBenchRun        *run);

GPtrArray              *crank_bench_result_case_get_runs         (CrankBenchResultCase  *result);

GList                  *crank_bench_result_case_get_run_list     (CrankBenchResultCase  *result);



void                    crank_bench_result_case_postprocess      (CrankBenchResultCase *result);

G_END_DECLS


#endif
