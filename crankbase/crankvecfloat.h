#ifndef CRANKVECFLOAT_H
#define CRANKVECFLOAT_H

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
#error crankvecfloat.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankiter.h"
#include "crankveccommon.h"

G_BEGIN_DECLS

/**
 * CRANK_VEC_FLOAT_S0: (skip)
 *
 * Static vector filled with 0.
 */
const gfloat CRANK_VEC_FLOAT_S0[4];

/**
 * CRANK_VEC_FLOAT_S1: (skip)
 *
 * Static vector filled with 1.
 */
const gfloat CRANK_VEC_FLOAT_S1[4];

/**
 * crank_vec_float2_static_zero:
 *
 * Static vector filled with 0.
 */
const CrankVecFloat2 * const crank_vec_float2_static_zero;

/**
 * crank_vec_float3_static_zero:
 *
 * Static vector filled with 0.
 */
const CrankVecFloat3 * const crank_vec_float3_static_zero;

/**
 * crank_vec_float4_static_zero:
 *
 * Static vector filled with 0.
 */
const CrankVecFloat4 * const crank_vec_float4_static_zero;

/**
 * crank_vec_float2_static_one:
 *
 * Static vector filled with 0.
 */
const CrankVecFloat2 * const crank_vec_float2_static_one;

/**
 * crank_vec_float3_static_one:
 *
 * Static vector filled with 0.
 */
const CrankVecFloat3 * const crank_vec_float3_static_one;

/**
 * crank_vec_float4_static_one:
 *
 * Static vector filled with 0.
 */
const CrankVecFloat4 * const crank_vec_float4_static_one;


/**
 * CrankVecFloat2:
 * @x: First element.
 * @y: Second element.
 *
 * Float vector. Compared to vec2 in GLSL.
 */
struct _CrankVecFloat2 {
  gfloat x;
  gfloat y;
};

#define CRANK_TYPE_VEC_FLOAT2   (crank_vec_float2_get_type ())
GType           crank_vec_float2_get_type   (void);


void            crank_vec_float2_init       (CrankVecFloat2 *vec,
                                             const gfloat    x,
                                             const gfloat    y);

void            crank_vec_float2_init_arr   (CrankVecFloat2 *vec,
                                             const gfloat   *arr);

void            crank_vec_float2_init_valist (CrankVecFloat2 *vec,
                                              va_list         varargs);

void            crank_vec_float2_init_fill  (CrankVecFloat2 *vec,
                                             const gfloat    fill);

void            crank_vec_float2_init_from_vb (CrankVecFloat2      *vec,
                                               const CrankVecBool2 *vb);

void            crank_vec_float2_init_from_vi (CrankVecFloat2     *vec,
                                               const CrankVecInt2 *vi);

void            crank_vec_float2_copy       (const CrankVecFloat2 *vec,
                                             CrankVecFloat2       *other);

CrankVecFloat2 *crank_vec_float2_dup        (const CrankVecFloat2 *vec);

gfloat          crank_vec_float2_get        (const CrankVecFloat2 *vec,
                                             const guint           index);

void            crank_vec_float2_set        (CrankVecFloat2 *vec,
                                             const guint     index,
                                             const gfloat    value);

gboolean        crank_vec_float2_foreach    (const CrankVecFloat2 *vec,
                                             CrankBoolFloatFunc    func,
                                             gpointer              userdata);

void            crank_vec_float2_iterator   (CrankVecFloat2    *vec,
                                             CrankIterMemFloat *iter);

//////// Basic operation ////////

guint           crank_vec_float2_hash       (gconstpointer a);

gboolean        crank_vec_float2_equal      (gconstpointer a,
                                             gconstpointer b);

gboolean        crank_vec_float2_equal_delta(gconstpointer a,
                                             gconstpointer b,
                                             const gfloat  d);

gchar          *crank_vec_float2_to_string  (const CrankVecFloat2 *vec);

gchar          *crank_vec_float2_to_string_full (const CrankVecFloat2 *vec,
                                                 const gchar          *left,
                                                 const gchar          *in,
                                                 const gchar          *right,
                                                 const gchar          *format);


//////// Standard vector property ///////

gfloat          crank_vec_float2_get_magn_sq        (const CrankVecFloat2 *vec);

gfloat          crank_vec_float2_get_magn           (const CrankVecFloat2 *vec);


//////// Standard unary operations ////////

void            crank_vec_float2_neg            (const CrankVecFloat2 *a,
                                                 CrankVecFloat2       *r);

void            crank_vec_float2_neg_self       (CrankVecFloat2 *a);

void            crank_vec_float2_unit           (const CrankVecFloat2 *a,
                                                 CrankVecFloat2       *r);

void            crank_vec_float2_unit_self      (CrankVecFloat2 *a);


//////// Scalar operations ////////

void            crank_vec_float2_muls           (const CrankVecFloat2 *a,
                                                 const gfloat          b,
                                                 CrankVecFloat2       *r);

void            crank_vec_float2_muls_self      (CrankVecFloat2 *a,
                                                 const gfloat    b);

void            crank_vec_float2_divs           (const CrankVecFloat2 *a,
                                                 const gfloat          b,
                                                 CrankVecFloat2       *r);

void            crank_vec_float2_divs_self      (CrankVecFloat2 *a,
                                                 const gfloat    b);

//////// Standard vector operations ////////

void            crank_vec_float2_add            (const CrankVecFloat2 *a,
                                                 const CrankVecFloat2 *b,
                                                 CrankVecFloat2       *r);

void            crank_vec_float2_add_self       (CrankVecFloat2       *a,
                                                 const CrankVecFloat2 *b);

void            crank_vec_float2_sub            (const CrankVecFloat2 *a,
                                                 const CrankVecFloat2 *b,
                                                 CrankVecFloat2       *r);

void            crank_vec_float2_sub_self       (CrankVecFloat2       *a,
                                                 const CrankVecFloat2 *b);

gfloat          crank_vec_float2_dot            (const CrankVecFloat2 *a,
                                                 const CrankVecFloat2 *b);

gfloat          crank_vec_float2_crs            (const CrankVecFloat2 *a,
                                                 const CrankVecFloat2 *b);

//////// Component vector operations ////////

void            crank_vec_float2_cmpmul     (const CrankVecFloat2 *a,
                                             const CrankVecFloat2 *b,
                                             CrankVecFloat2       *r);

void            crank_vec_float2_cmpmul_self(CrankVecFloat2       *a,
                                             const CrankVecFloat2 *b);

void            crank_vec_float2_cmpdiv     (const CrankVecFloat2 *a,
                                             const CrankVecFloat2 *b,
                                             CrankVecFloat2       *r);

void            crank_vec_float2_cmpdiv_self(CrankVecFloat2       *a,
                                             const CrankVecFloat2 *b);

void            crank_vec_float2_cmpless    (const CrankVecFloat2 *a,
                                             const CrankVecFloat2 *b,
                                             CrankVecBool2        *r);

void            crank_vec_float2_cmpeq      (const CrankVecFloat2 *a,
                                             const CrankVecFloat2 *b,
                                             CrankVecBool2        *r);

void            crank_vec_float2_cmpgreater (const CrankVecFloat2 *a,
                                             const CrankVecFloat2 *b,
                                             CrankVecBool2        *r);

void            crank_vec_float2_cmpcmp (const CrankVecFloat2 *a,
                                         const CrankVecFloat2 *b,
                                         CrankVecInt2         *r);

void            crank_vec_float2_min    (const CrankVecFloat2 *a,
                                         const CrankVecFloat2 *b,
                                         CrankVecFloat2       *r);

void            crank_vec_float2_max    (const CrankVecFloat2 *a,
                                         const CrankVecFloat2 *b,
                                         CrankVecFloat2       *r);

void            crank_vec_float2_abs    (const CrankVecFloat2 *a,
                                         CrankVecFloat2       *r);

void            crank_vec_float2_abs_self(CrankVecFloat2 *a);

//////// Matrix Operations /////////////////////////////////////////////////////

void            crank_vec_float2_mulm (const CrankVecFloat2 *a,
                                       const CrankMatFloat2 *b,
                                       CrankVecFloat2       *r);

void            crank_vec_float2_mulm_self (CrankVecFloat2       *a,
                                            const CrankMatFloat2 *b);


//////// Ternary Operations ////////

void            crank_vec_float2_mixs   (const CrankVecFloat2 *a,
                                         const CrankVecFloat2 *b,
                                         const gfloat          c,
                                         CrankVecFloat2       *r);

void            crank_vec_float2_mix    (const CrankVecFloat2 *a,
                                         const CrankVecFloat2 *b,
                                         const CrankVecFloat2 *c,
                                         CrankVecFloat2       *r);






/**
 * CrankVecFloat3:
 * @x: First element.
 * @y: Second element.
 * @z: Third element.
 *
 * Float vector. Compared to vec3 in GLSL.
 */
struct _CrankVecFloat3 {
  gfloat x;
  gfloat y;
  gfloat z;
};

#define CRANK_TYPE_VEC_FLOAT3   (crank_vec_float3_get_type ())
GType           crank_vec_float3_get_type   (void);


void            crank_vec_float3_init       (CrankVecFloat3 *vec,
                                             const gfloat    x,
                                             const gfloat    y,
                                             const gfloat    z);

void            crank_vec_float3_init_arr   (CrankVecFloat3 *vec,
                                             const gfloat   *arr);

void            crank_vec_float3_init_valist (CrankVecFloat3 *vec,
                                              va_list         varargs);

void            crank_vec_float3_init_fill  (CrankVecFloat3 *vec,
                                             const gfloat    fill);

void            crank_vec_float3_init_from_vb (CrankVecFloat3      *vec,
                                               const CrankVecBool3 *vb);

void            crank_vec_float3_init_from_vi (CrankVecFloat3     *vec,
                                               const CrankVecInt3 *vi);

void            crank_vec_float3_copy       (const CrankVecFloat3 *vec,
                                             CrankVecFloat3       *other);

CrankVecFloat3 *crank_vec_float3_dup        (const CrankVecFloat3 *vec);

gfloat          crank_vec_float3_get        (const CrankVecFloat3 *vec,
                                             const guint           index);

void            crank_vec_float3_set        (CrankVecFloat3 *vec,
                                             const guint     index,
                                             const gfloat    value);

gboolean        crank_vec_float3_foreach    (const CrankVecFloat3 *vec,
                                             CrankBoolFloatFunc    func,
                                             gpointer              userdata);

void            crank_vec_float3_iterator   (CrankVecFloat3    *vec,
                                             CrankIterMemFloat *iter);

//////// Basic operation ////////

guint           crank_vec_float3_hash       (gconstpointer a);

gboolean        crank_vec_float3_equal      (gconstpointer a,
                                             gconstpointer b);

gboolean        crank_vec_float3_equal_delta(gconstpointer a,
                                             gconstpointer b,
                                             const gfloat  d);

gchar          *crank_vec_float3_to_string  (const CrankVecFloat3 *vec);

gchar          *crank_vec_float3_to_string_full (const CrankVecFloat3 *vec,
                                                 const gchar          *left,
                                                 const gchar          *in,
                                                 const gchar          *right,
                                                 const gchar          *format);


//////// Standard vector property ///////

gfloat          crank_vec_float3_get_magn_sq  (const CrankVecFloat3 *vec);

gfloat          crank_vec_float3_get_magn     (const CrankVecFloat3 *vec);


//////// Standard unary operations ////////

void            crank_vec_float3_neg          (const CrankVecFloat3 *a,
                                               CrankVecFloat3       *r);

void            crank_vec_float3_neg_self     (CrankVecFloat3       *a);

void            crank_vec_float3_unit         (const CrankVecFloat3 *a,
                                               CrankVecFloat3       *r);

void            crank_vec_float3_unit_self    (CrankVecFloat3       *a);


//////// Scalar operations ////////

void            crank_vec_float3_muls         (const CrankVecFloat3 *a,
                                               const gfloat          b,
                                               CrankVecFloat3       *r);

void            crank_vec_float3_muls_self    (CrankVecFloat3 *a,
                                               const gfloat    b);

void            crank_vec_float3_divs         (const CrankVecFloat3 *a,
                                               const gfloat          b,
                                               CrankVecFloat3       *r);

void            crank_vec_float3_divs_self    (CrankVecFloat3 *a,
                                               const gfloat    b);

//////// Standard vector operations ////////

void            crank_vec_float3_add          (const CrankVecFloat3 *a,
                                               const CrankVecFloat3 *b,
                                               CrankVecFloat3       *r);

void            crank_vec_float3_add_self     (CrankVecFloat3       *a,
                                               const CrankVecFloat3 *b);

void            crank_vec_float3_sub          (const CrankVecFloat3 *a,
                                               const CrankVecFloat3 *b,
                                               CrankVecFloat3       *r);

void            crank_vec_float3_sub_self     (CrankVecFloat3       *a,
                                               const CrankVecFloat3 *b);

gfloat          crank_vec_float3_dot          (const CrankVecFloat3 *a,
                                               const CrankVecFloat3 *b);

void            crank_vec_float3_crs          (const CrankVecFloat3 *a,
                                               const CrankVecFloat3 *b,
                                               CrankVecFloat3       *r);

void            crank_vec_float3_crs_self     (CrankVecFloat3       *a,
                                               const CrankVecFloat3 *b);


//////// Component vector operations ////////

void            crank_vec_float3_cmpmul     (const CrankVecFloat3 *a,
                                             const CrankVecFloat3 *b,
                                             CrankVecFloat3       *r);

void            crank_vec_float3_cmpmul_self(CrankVecFloat3       *a,
                                             const CrankVecFloat3 *b);

void            crank_vec_float3_cmpdiv     (const CrankVecFloat3 *a,
                                             const CrankVecFloat3 *b,
                                             CrankVecFloat3       *r);

void            crank_vec_float3_cmpdiv_self(CrankVecFloat3       *a,
                                             const CrankVecFloat3 *b);


void            crank_vec_float3_cmpless    (const CrankVecFloat3 *a,
                                             const CrankVecFloat3 *b,
                                             CrankVecBool3        *r);

void            crank_vec_float3_cmpeq      (const CrankVecFloat3 *a,
                                             const CrankVecFloat3 *b,
                                             CrankVecBool3        *r);

void            crank_vec_float3_cmpgreater (const CrankVecFloat3 *a,
                                             const CrankVecFloat3 *b,
                                             CrankVecBool3        *r);

void            crank_vec_float3_cmpcmp (const CrankVecFloat3 *a,
                                         const CrankVecFloat3 *b,
                                         CrankVecInt3         *r);

void            crank_vec_float3_min    (const CrankVecFloat3 *a,
                                         const CrankVecFloat3 *b,
                                         CrankVecFloat3       *r);

void            crank_vec_float3_max    (const CrankVecFloat3 *a,
                                         const CrankVecFloat3 *b,
                                         CrankVecFloat3       *r);

void            crank_vec_float3_abs    (const CrankVecFloat3 *a,
                                         CrankVecFloat3       *r);

void            crank_vec_float3_abs_self(CrankVecFloat3 *a);

//////// Matrix operations ////////

void            crank_vec_float3_mulm   (const CrankVecFloat3 *a,
                                         const CrankMatFloat3 *b,
                                         CrankVecFloat3       *r);

void            crank_vec_float3_mulm_self(CrankVecFloat3       *a,
                                           const CrankMatFloat3 *b);


//////// Ternary Operations ////////

void            crank_vec_float3_mixs   (const CrankVecFloat3 *a,
                                         const CrankVecFloat3 *b,
                                         const gfloat          c,
                                         CrankVecFloat3       *r);

void            crank_vec_float3_mix    (const CrankVecFloat3 *a,
                                         const CrankVecFloat3 *b,
                                         const CrankVecFloat3 *c,
                                         CrankVecFloat3       *r);






/**
 * CrankVecFloat4:
 * @x: First element.
 * @y: Second element.
 * @z: Third element.
 * @w: Fourth element.
 *
 * Float vector. Compared to vec3 in GLSL.
 */
struct _CrankVecFloat4 {
  gfloat x;
  gfloat y;
  gfloat z;
  gfloat w;
};

#define CRANK_TYPE_VEC_FLOAT4   (crank_vec_float4_get_type ())
GType           crank_vec_float4_get_type   (void);


void            crank_vec_float4_init       (CrankVecFloat4 *vec,
                                             const gfloat    x,
                                             const gfloat    y,
                                             const gfloat    z,
                                             const gfloat    w);

void            crank_vec_float4_init_arr   (CrankVecFloat4 *vec,
                                             const gfloat   *arr);

void            crank_vec_float4_init_valist (CrankVecFloat4 *vec,
                                              va_list         varargs);

void            crank_vec_float4_init_fill  (CrankVecFloat4 *vec,
                                             const gfloat    fill);

void            crank_vec_float4_init_from_vb (CrankVecFloat4      *vec,
                                               const CrankVecBool4 *vb);

void            crank_vec_float4_init_from_vi (CrankVecFloat4     *vec,
                                               const CrankVecInt4 *vi);

void            crank_vec_float4_copy       (const CrankVecFloat4 *vec,
                                             CrankVecFloat4 *other);

CrankVecFloat4 *crank_vec_float4_dup        (const CrankVecFloat4 *vec);

gfloat          crank_vec_float4_get        (const CrankVecFloat4 *vec,
                                             const guint     index);

void            crank_vec_float4_set        (CrankVecFloat4 *vec,
                                             const guint     index,
                                             const gfloat    value);

gboolean        crank_vec_float4_foreach    (const CrankVecFloat4 *vec,
                                             CrankBoolFloatFunc    func,
                                             gpointer              userdata);

void            crank_vec_float4_iterator   (CrankVecFloat4    *vec,
                                             CrankIterMemFloat *iter);

//////// Basic operation ////////

guint           crank_vec_float4_hash       (gconstpointer a);

gboolean        crank_vec_float4_equal      (gconstpointer a,
                                             gconstpointer b);

gboolean        crank_vec_float4_equal_delta(gconstpointer a,
                                             gconstpointer b,
                                             const gfloat  d);

gchar          *crank_vec_float4_to_string  (const CrankVecFloat4 *vec);

gchar          *crank_vec_float4_to_string_full (const CrankVecFloat4 *vec,
                                                 const gchar          *left,
                                                 const gchar          *in,
                                                 const gchar          *right,
                                                 const gchar          *format);


//////// Standard vector property ///////

gfloat          crank_vec_float4_get_magn_sq        (const CrankVecFloat4 *vec);

gfloat          crank_vec_float4_get_magn           (const CrankVecFloat4 *vec);


//////// Standard unary operations ////////

void            crank_vec_float4_neg            (const CrankVecFloat4 *a,
                                                 CrankVecFloat4       *r);

void            crank_vec_float4_neg_self       (CrankVecFloat4 *a);

void            crank_vec_float4_unit           (const CrankVecFloat4 *a,
                                                 CrankVecFloat4       *r);

void            crank_vec_float4_unit_self      (CrankVecFloat4 *a);


//////// Scalar operations ////////

void            crank_vec_float4_muls           (const CrankVecFloat4 *a,
                                                 const gfloat          b,
                                                 CrankVecFloat4       *r);

void            crank_vec_float4_muls_self      (CrankVecFloat4 *a,
                                                 const gfloat    b);

void            crank_vec_float4_divs           (const CrankVecFloat4 *a,
                                                 const gfloat          b,
                                                 CrankVecFloat4       *r);

void            crank_vec_float4_divs_self      (CrankVecFloat4 *a,
                                                 const gfloat    b);

//////// Standard vector operations ////////

void            crank_vec_float4_add            (const CrankVecFloat4 *a,
                                                 const CrankVecFloat4 *b,
                                                 CrankVecFloat4       *r);

void            crank_vec_float4_add_self       (CrankVecFloat4       *a,
                                                 const CrankVecFloat4 *b);

void            crank_vec_float4_sub            (const CrankVecFloat4 *a,
                                                 const CrankVecFloat4 *b,
                                                 CrankVecFloat4       *r);

void            crank_vec_float4_sub_self       (CrankVecFloat4       *a,
                                                 const CrankVecFloat4 *b);

gfloat          crank_vec_float4_dot            (const CrankVecFloat4 *a,
                                                 const CrankVecFloat4 *b);

//////// Component vector operations ////////

void            crank_vec_float4_cmpmul     (const CrankVecFloat4 *a,
                                             const CrankVecFloat4 *b,
                                             CrankVecFloat4       *r);

void            crank_vec_float4_cmpmul_self(CrankVecFloat4       *a,
                                             const CrankVecFloat4 *b);

void            crank_vec_float4_cmpdiv     (const CrankVecFloat4 *a,
                                             const CrankVecFloat4 *b,
                                             CrankVecFloat4       *r);

void            crank_vec_float4_cmpdiv_self(CrankVecFloat4       *a,
                                             const CrankVecFloat4 *b);


void            crank_vec_float4_cmpless    (const CrankVecFloat4 *a,
                                             const CrankVecFloat4 *b,
                                             CrankVecBool4        *r);

void            crank_vec_float4_cmpeq      (const CrankVecFloat4 *a,
                                             const CrankVecFloat4 *b,
                                             CrankVecBool4        *r);

void            crank_vec_float4_cmpgreater (const CrankVecFloat4 *a,
                                             const CrankVecFloat4 *b,
                                             CrankVecBool4        *r);

void            crank_vec_float4_cmpcmp (const CrankVecFloat4 *a,
                                         const CrankVecFloat4 *b,
                                         CrankVecInt4         *r);

void            crank_vec_float4_min    (const CrankVecFloat4 *a,
                                         const CrankVecFloat4 *b,
                                         CrankVecFloat4       *r);

void            crank_vec_float4_max    (const CrankVecFloat4 *a,
                                         const CrankVecFloat4 *b,
                                         CrankVecFloat4       *r);

void            crank_vec_float4_abs    (const CrankVecFloat4 *a,
                                         CrankVecFloat4       *r);

void            crank_vec_float4_abs_self(CrankVecFloat4 *a);

//////// Matrix operations ////////

void            crank_vec_float4_mulm   (const CrankVecFloat4 *a,
                                         const CrankMatFloat4 *b,
                                         CrankVecFloat4       *r);

void            crank_vec_float4_mulm_self(CrankVecFloat4       *a,
                                           const CrankMatFloat4 *b);

//////// Ternary Operations ////////

void            crank_vec_float4_mixs   (const CrankVecFloat4 *a,
                                         const CrankVecFloat4 *b,
                                         const gfloat          c,
                                         CrankVecFloat4       *r);

void            crank_vec_float4_mix    (const CrankVecFloat4 *a,
                                         const CrankVecFloat4 *b,
                                         const CrankVecFloat4 *c,
                                         CrankVecFloat4       *r);






/**
 * CrankVecFloatN:
 * @data: (array length=n): Array to store elements.
 * @n: size of data.
 *
 * Struct to point variable size of float vector.
 */
struct _CrankVecFloatN {
  gfloat *data;
  guint n;
};

#define CRANK_TYPE_VEC_FLOAT_N  (crank_vec_float_n_get_type ())
GType           crank_vec_float_n_get_type  (void);

void            crank_vec_float_n_init      (CrankVecFloatN *vec,
                                             const guint     n,
                                             ...);

void            crank_vec_float_n_init_arr  (CrankVecFloatN *vec,
                                             const guint     n,
                                             const gfloat   *arr);

void            crank_vec_float_n_init_arr_take (CrankVecFloatN *vec,
                                                 const guint     n,
                                                 gfloat         *arr);

void            crank_vec_float_n_init_valist (CrankVecFloatN *vec,
                                               const guint     n,
                                               va_list         varargs);

void            crank_vec_float_n_init_fill (CrankVecFloatN *vec,
                                             const guint     n,
                                             const gfloat    fill);

void            crank_vec_float_n_init_from_vb (CrankVecFloatN       *vec,
                                                const CrankVecBoolN  *vb);

void            crank_vec_float_n_init_from_vi (CrankVecFloatN       *vec,
                                                const CrankVecIntN   *vi);

void            crank_vec_float_n_fini      (CrankVecFloatN *vec);

void            crank_vec_float_n_copy      (const CrankVecFloatN *vec,
                                             CrankVecFloatN *other);

CrankVecFloatN *crank_vec_float_n_dup       (const CrankVecFloatN *vec);

void            crank_vec_float_n_free      (CrankVecFloatN *vec);

guint           crank_vec_float_n_get_size  (const CrankVecFloatN *vec);

gfloat          crank_vec_float_n_get       (const CrankVecFloatN *vec,
                                             const guint           index);

void            crank_vec_float_n_set       (CrankVecFloatN *vec,
                                             const guint     index,
                                             const gfloat    value);

void            crank_vec_float_n_prepend   (CrankVecFloatN *vec,
                                             const gfloat    value);

void            crank_vec_float_n_append    (CrankVecFloatN *vec,
                                             const gfloat    value);

void            crank_vec_float_n_insert    (CrankVecFloatN *vec,
                                             const guint     index,
                                             const gfloat    value);

void            crank_vec_float_n_remove    (CrankVecFloatN *vec,
                                             const guint     index);

gboolean        crank_vec_float_n_foreach   (const CrankVecFloatN *vec,
                                             CrankBoolFloatFunc    func,
                                             gpointer              userdata);

void            crank_vec_float_n_iterator  (CrankVecFloatN    *vec,
                                             CrankIterMemFloat *iter);

//////// Basic operation ////////

guint           crank_vec_float_n_hash      (gconstpointer a);

gboolean        crank_vec_float_n_equal     (gconstpointer a,
                                             gconstpointer b);

gboolean        crank_vec_float_n_equal_delta(gconstpointer a,
                                              gconstpointer b,
                                              const gfloat  d);

gchar          *crank_vec_float_n_to_string (const CrankVecFloatN *vec);

gchar          *crank_vec_float_n_to_string_full (const CrankVecFloatN *vec,
                                                  const gchar    *left,
                                                  const gchar    *in,
                                                  const gchar    *right,
                                                  const gchar    *format);

//////// Classification ////////////////////////////////////////////////////////

gboolean        crank_vec_float_n_is_zero           (const CrankVecFloatN *vec);

gboolean        crank_vec_float_n_is_one            (const CrankVecFloatN *vec);

gboolean        crank_vec_float_n_is_unit           (const CrankVecFloatN *vec);

gboolean        crank_vec_float_n_is_empty          (const CrankVecFloatN *vec);

gboolean        crank_vec_float_n_has_nan           (const CrankVecFloatN *vec);

gboolean        crank_vec_float_n_has_inf           (const CrankVecFloatN *vec);

//////// Standard vector property ///////

gfloat          crank_vec_float_n_get_magn_sq       (const CrankVecFloatN *vec);

gfloat          crank_vec_float_n_get_magn          (const CrankVecFloatN *vec);


//////// Standard unary operations ////////

void            crank_vec_float_n_neg           (const CrankVecFloatN *a,
                                                 CrankVecFloatN *r);

void            crank_vec_float_n_neg_self      (CrankVecFloatN *a);

void            crank_vec_float_n_unit          (const CrankVecFloatN *a,
                                                 CrankVecFloatN *r);

void            crank_vec_float_n_unit_self     (CrankVecFloatN *a);


//////// Scalar operations ////////

void            crank_vec_float_n_muls          (const CrankVecFloatN *a,
                                                 const gfloat    b,
                                                 CrankVecFloatN *r);

void            crank_vec_float_n_muls_self     (CrankVecFloatN *a,
                                                 const gfloat    b);

void            crank_vec_float_n_divs          (const CrankVecFloatN *a,
                                                 const gfloat    b,
                                                 CrankVecFloatN *r);

void            crank_vec_float_n_divs_self     (CrankVecFloatN *a,
                                                 const gfloat    b);

//////// Standard vector operations ////////

void            crank_vec_float_n_add           (const CrankVecFloatN *a,
                                                 const CrankVecFloatN *b,
                                                 CrankVecFloatN       *r);

void            crank_vec_float_n_add_self      (CrankVecFloatN       *a,
                                                 const CrankVecFloatN *b);

void            crank_vec_float_n_sub           (const CrankVecFloatN *a,
                                                 const CrankVecFloatN *b,
                                                 CrankVecFloatN *r);

void            crank_vec_float_n_sub_self      (CrankVecFloatN *a,
                                                 const CrankVecFloatN *b);

gfloat          crank_vec_float_n_dot           (const CrankVecFloatN *a,
                                                 const CrankVecFloatN *b);

//////// Component vector operations ////////

void            crank_vec_float_n_cmpmul    (const CrankVecFloatN *a,
                                             const CrankVecFloatN *b,
                                             CrankVecFloatN       *r);

void            crank_vec_float_n_cmpmul_self(CrankVecFloatN       *a,
                                              const CrankVecFloatN *b);

void            crank_vec_float_n_cmpdiv    (const CrankVecFloatN *a,
                                             const CrankVecFloatN *b,
                                             CrankVecFloatN       *r);

void            crank_vec_float_n_cmpdiv_self(CrankVecFloatN       *a,
                                              const CrankVecFloatN *b);


void            crank_vec_float_n_cmpless   (const CrankVecFloatN *a,
                                             const CrankVecFloatN *b,
                                             CrankVecBoolN        *r);

void            crank_vec_float_n_cmpeq     (const CrankVecFloatN *a,
                                             const CrankVecFloatN *b,
                                             CrankVecBoolN        *r);

void            crank_vec_float_n_cmpgreater    (const CrankVecFloatN *a,
                                                 const CrankVecFloatN *b,
                                                 CrankVecBoolN        *r);

void            crank_vec_float_n_cmpcmp    (const CrankVecFloatN *a,
                                             const CrankVecFloatN *b,
                                             CrankVecIntN         *r);

void            crank_vec_float_n_min   (const CrankVecFloatN *a,
                                         const CrankVecFloatN *b,
                                         CrankVecFloatN       *r);

void            crank_vec_float_n_max   (const CrankVecFloatN *a,
                                         const CrankVecFloatN *b,
                                         CrankVecFloatN       *r);

void            crank_vec_float_n_abs   (const CrankVecFloatN *a,
                                         CrankVecFloatN       *r);

void            crank_vec_float_n_abs_self (CrankVecFloatN *a);

//////// Matrix operations ////////

void            crank_vec_float_n_mulm  (const CrankVecFloatN *a,
                                         const CrankMatFloatN *b,
                                         CrankVecFloatN       *r);

void            crank_vec_float_n_mulm_self(CrankVecFloatN       *a,
                                            const CrankMatFloatN *b);

//////// Ternary Operations ////////

void            crank_vec_float_n_mixs  (const CrankVecFloatN *a,
                                         const CrankVecFloatN *b,
                                         const gfloat          c,
                                         CrankVecFloatN       *r);

void            crank_vec_float_n_mix   (const CrankVecFloatN *a,
                                         const CrankVecFloatN *b,
                                         const CrankVecFloatN *c,
                                         CrankVecFloatN       *r);

//////// Macro variant of operations ///////////////////////////////////////////

#define crank_vec_float_n_get(vec,index)        CRANK_VEC_GET(vec,index)
#define crank_vec_float_n_set(vec,index,value)  CRANK_VEC_SET(vec,index,value)

G_END_DECLS

#endif //CRANKBOOLVEC_H
