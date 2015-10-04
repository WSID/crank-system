#ifndef CRANKVECCPLXFLOAT_H
#define CRANKVECCPLXFLOAT_H

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

#ifndef _CRANKBASE_INSIDE
#error crankveccplxfloat.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankcomplex.h"
#include "crankveccommon.h"

struct _CrankVecCplxFloatN {
  CrankCplxFloat *data;
  guint n;
};

#define CRANK_TYPE_VEC_CPLX_FLOAT_N (crank_vec_cplx_float_n_get_type ())
GType               crank_vec_cplx_float_n_get_type (void);

void                crank_vec_cplx_float_n_init     (
  CrankVecCplxFloatN *vec,
  const guint         n,
  ...);

void                crank_vec_cplx_float_n_init_arr (
  CrankVecCplxFloatN *vec,
  const guint         n,
  CrankCplxFloat     *arr);

void                crank_vec_cplx_float_n_init_arr_take (
  CrankVecCplxFloatN *vec,
  const guint         n,
  CrankCplxFloat     *arr);

void                crank_vec_cplx_float_n_init_valist (
  CrankVecCplxFloatN *vec,
  const guint         n,
  va_list             varargs);

void                crank_vec_cplx_float_n_init_fill    (
  CrankVecCplxFloatN *vec,
  const guint         n,
  CrankCplxFloat     *fill);


void                crank_vec_cplx_float_n_init_uc      (
  CrankVecCplxFloatN *vec,
  const guint         n,
  ...);

void                crank_vec_cplx_float_n_init_valistuc (
  CrankVecCplxFloatN *vec,
  const guint         n,
  va_list             varargs);

void                crank_vec_cplx_float_n_init_ucarr (
  CrankVecCplxFloatN *vec,
  const guint         n,
  const gfloat       *real,
  const gfloat       *imag);

void                crank_vec_cplx_float_n_init_arruc (
  CrankVecCplxFloatN *vec,
  const guint         n,
  const gfloat       *arr);

void                crank_vec_cplx_float_n_init_fill_uc (
  CrankVecCplxFloatN *vec,
  const guint         n,
  const gfloat        real,
  const gfloat        imag);

void                crank_vec_cplx_float_n_init_ucv (
  CrankVecCplxFloatN *vec,
  CrankVecFloatN     *real,
  CrankVecFloatN     *imag);

void                crank_vec_cplx_float_n_init_from_vb (
  CrankVecCplxFloatN *vec,
  CrankVecBoolN      *vb);

void                crank_vec_cplx_float_n_init_from_vi (
  CrankVecCplxFloatN *vec,
  CrankVecIntN       *vi);

void                crank_vec_cplx_float_n_init_from_vf (
  CrankVecCplxFloatN *vec,
  CrankVecFloatN     *vf);

void                crank_vec_cplx_float_n_fini     (CrankVecCplxFloatN *vec);

void                crank_vec_cplx_float_n_copy     (CrankVecCplxFloatN *vec,
                                                     CrankVecCplxFloatN *other);

CrankVecCplxFloatN *crank_vec_cplx_float_n_dup      (CrankVecCplxFloatN *vec);

void                crank_vec_cplx_float_n_free     (CrankVecCplxFloatN *vec);

guint               crank_vec_cplx_float_n_get_size (CrankVecCplxFloatN *vec);

void                crank_vec_cplx_float_n_get      (CrankVecCplxFloatN *vec,
                                                     const guint         index,
                                                     CrankCplxFloat     *value);

void                crank_vec_cplx_float_n_set      (CrankVecCplxFloatN *vec,
                                                     const guint         index,
                                                     CrankCplxFloat     *value);

void                crank_vec_cplx_float_n_prepend  (CrankVecCplxFloatN *vec,
                                                     CrankCplxFloat     *value);

void                crank_vec_cplx_float_n_append   (CrankVecCplxFloatN *vec,
                                                     CrankCplxFloat     *value);

void                crank_vec_cplx_float_n_insert   (CrankVecCplxFloatN *vec,
                                                     const guint         index,
                                                     CrankCplxFloat     *value);

void                crank_vec_cplx_float_n_remove   (CrankVecCplxFloatN *vec,
                                                     const guint         index);

gboolean            crank_vec_cplx_float_n_foreach  (
  CrankVecCplxFloatN    *vec,
  CrankBoolCplxFloatFunc func,
  gpointer               userdata);

void                crank_vec_cplx_float_n_iterator (CrankVecCplxFloatN *vec,
                                                     CrankIterMemStruct *iter);

//////// Basic operation ////////

guint               crank_vec_cplx_float_n_hash     (gconstpointer a);

gboolean            crank_vec_cplx_float_n_equal        (gconstpointer a,
                                                         gconstpointer b);

gchar              *crank_vec_cplx_float_n_to_string    (
  CrankVecCplxFloatN *vec);

gchar              *crank_vec_cplx_float_n_to_string_full (
  CrankVecCplxFloatN *vec,
  const gchar        *left,
  const gchar        *in,
  const gchar        *right,
  const gchar        *format);


//////// Classification ////////////////////////////////////////////////////////

gboolean            crank_vec_cplx_float_n_is_zero          (
  CrankVecCplxFloatN *vec);

gboolean            crank_vec_cplx_float_n_is_one           (
  CrankVecCplxFloatN *vec);

gboolean            crank_vec_cplx_float_n_is_unit          (
  CrankVecCplxFloatN *vec);

gboolean            crank_vec_cplx_float_n_is_empty         (
  CrankVecCplxFloatN *vec);

gboolean            crank_vec_cplx_float_n_is_pure_real     (
  CrankVecCplxFloatN *vec);

gboolean            crank_vec_cplx_float_n_is_pure_imag     (
  CrankVecCplxFloatN *vec);


gboolean            crank_vec_cplx_float_n_has_nan          (
  CrankVecCplxFloatN *vec);

gboolean            crank_vec_cplx_float_n_has_inf          (
  CrankVecCplxFloatN *vec);

//////// Standard vector property ///////

gfloat              crank_vec_cplx_float_n_get_magn_sq      (
  CrankVecCplxFloatN *vec);

gfloat              crank_vec_cplx_float_n_get_magn         (
  CrankVecCplxFloatN *vec);

void                crank_vec_cplx_float_n_get_real         (
  CrankVecCplxFloatN *vec,
  CrankVecFloatN     *real);

void                crank_vec_cplx_float_n_get_imag         (
  CrankVecCplxFloatN *vec,
  CrankVecFloatN     *imag);

void                crank_vec_cplx_float_n_set_real         (
  CrankVecCplxFloatN *vec,
  CrankVecFloatN     *real);

void                crank_vec_cplx_float_n_set_imag         (
  CrankVecCplxFloatN *vec,
  CrankVecFloatN     *imag);


//////// Standard unary operations ////////

void                crank_vec_cplx_float_n_neg          (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_neg_self     (
  CrankVecCplxFloatN *a);

void                crank_vec_cplx_float_n_unit         (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_unit_self    (
  CrankVecCplxFloatN *a);

void                crank_vec_cplx_float_n_conjugate    (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_conjugate_self(
  CrankVecCplxFloatN *a);


//////// Scalar operations ////////

void                crank_vec_cplx_float_n_muls     (CrankVecCplxFloatN *a,
                                                     CrankCplxFloat     *b,
                                                     CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_muls_self(CrankVecCplxFloatN *a,
                                                     CrankCplxFloat     *b);

void                crank_vec_cplx_float_n_mulrs    (CrankVecCplxFloatN *a,
                                                     const gfloat        b,
                                                     CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_mulrs_self(CrankVecCplxFloatN *a,
                                                      const gfloat        b);

void                crank_vec_cplx_float_n_divs     (CrankVecCplxFloatN *a,
                                                     CrankCplxFloat     *b,
                                                     CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_divs_self(CrankVecCplxFloatN *a,
                                                     CrankCplxFloat     *b);

void                crank_vec_cplx_float_n_divrs    (CrankVecCplxFloatN *a,
                                                     const gfloat        b,
                                                     CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_divrs_self(CrankVecCplxFloatN *a,
                                                      const gfloat        b);

//////// Standard vector operations ////////

void                crank_vec_cplx_float_n_add          (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_add_self     (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b);

void                crank_vec_cplx_float_n_addr         (
  CrankVecCplxFloatN *a,
  CrankVecFloatN     *b,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_addr_self    (
  CrankVecCplxFloatN *a,
  CrankVecFloatN     *b);

void                crank_vec_cplx_float_n_sub          (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_sub_self     (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b);

void                crank_vec_cplx_float_n_subr_self    (
  CrankVecCplxFloatN *a,
  CrankVecFloatN     *b);

void                crank_vec_cplx_float_n_subr         (
  CrankVecCplxFloatN *a,
  CrankVecFloatN     *b,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_dot          (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b,
  CrankCplxFloat     *r);

//////// Component vector operations ////////

void                crank_vec_cplx_float_n_cmpmul       (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_cmpmul_self  (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b);

void                crank_vec_cplx_float_n_cmpmulr      (
  CrankVecCplxFloatN *a,
  CrankVecFloatN     *b,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_cmpmulr_self (
  CrankVecCplxFloatN *a,
  CrankVecFloatN     *b);

void                crank_vec_cplx_float_n_cmpdiv       (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_cmpdiv_self  (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b);

void                crank_vec_cplx_float_n_cmpdivr      (
  CrankVecCplxFloatN *a,
  CrankVecFloatN     *b,
  CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_cmpdivr_self (
  CrankVecCplxFloatN *a,
  CrankVecFloatN     *b);


void                crank_vec_cplx_float_n_cmpeq        (
  CrankVecCplxFloatN *a,
  CrankVecCplxFloatN *b,
  CrankVecBoolN      *r);
//////// Matrix operations ////////

void                crank_vec_cplx_float_n_mulm     (CrankVecCplxFloatN *a,
                                                     CrankMatCplxFloatN *b,
                                                     CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_mulm_self(CrankVecCplxFloatN *a,
                                                     CrankMatCplxFloatN *b);

void                crank_vec_cplx_float_n_mulrm    (CrankVecCplxFloatN *a,
                                                     CrankMatFloatN     *b,
                                                     CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_mulrm_self   (
  CrankVecCplxFloatN *a,
  CrankMatFloatN     *b);

//////// Ternary Operations ////////

void                crank_vec_cplx_float_n_mixs (CrankVecCplxFloatN *a,
                                                 CrankVecCplxFloatN *b,
                                                 gfloat              c,
                                                 CrankVecCplxFloatN *r);

void                crank_vec_cplx_float_n_mix  (CrankVecCplxFloatN *a,
                                                 CrankVecCplxFloatN *b,
                                                 CrankVecFloatN     *c,
                                                 CrankVecCplxFloatN *r);

#endif