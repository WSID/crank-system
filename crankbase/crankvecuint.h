#ifndef CRANKVECUINT_H
#define CRANKVECUINT_H

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
#error crankvecuint.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankveccommon.h"

G_BEGIN_DECLS

/**
 * CrankVecUint2:
 * @x: First element.
 * @y: Second element.
 *
 * integer vector. Compared to uvec2 in GLSL.
 */
struct _CrankVecUint2 {
  guint x;
  guint y;
};

#define CRANK_TYPE_VEC_UINT2 (crank_vec_uint2_get_type ())
GType         crank_vec_uint2_get_type (void);



void          crank_vec_uint2_init        (CrankVecUint2 *vec,
                                           const guint    x,
                                           const guint    y);

void          crank_vec_uint2_init_arr    (CrankVecUint2 *vec,
                                           guint         *arr);

void          crank_vec_uint2_init_valist (CrankVecUint2 *vec,
                                           va_list       varargs);

void          crank_vec_uint2_init_fill   (CrankVecUint2 *vec,
                                           const guint    fill);

void          crank_vec_uint2_init_from_vb(CrankVecUint2 *vec,
                                           CrankVecBool2 *vb);

void          crank_vec_uint2_copy        (CrankVecUint2 *vec,
                                           CrankVecUint2 *other);

CrankVecUint2 *crank_vec_uint2_dup        (CrankVecUint2 *vec);

guint          crank_vec_uint2_get         (CrankVecUint2 *vec,
                                           const guint   index);

void          crank_vec_uint2_set         (CrankVecUint2 *vec,
                                           const guint    index,
                                           const guint    value);

gboolean      crank_vec_uint2_foreach     (CrankVecUint2    *vec,
                                           CrankBoolUintFunc func,
                                           gpointer         userdata);

void          crank_vec_uint2_iterator    (CrankVecUint2    *vec,
                                           CrankIterMemUint *iter);

//////// Basic operation ////////

guint         crank_vec_uint2_hash        (gconstpointer a);

gboolean      crank_vec_uint2_equal       (gconstpointer a,
                                           gconstpointer b);

gchar        *crank_vec_uint2_to_string   (CrankVecUint2 *vec);

gchar        *crank_vec_uint2_to_string_full(CrankVecUint2 *vec,
                                             const gchar  *left,
                                             const gchar  *in,
                                             const gchar  *right,
                                             const gchar  *format);


//////// Standard vector property ///////

guint         crank_vec_uint2_get_magn_sq      (CrankVecUint2 *vec);

gfloat        crank_vec_uint2_get_magn         (CrankVecUint2 *vec);


//////// Standard unary operations ////////

void          crank_vec_uint2_neg         (CrankVecUint2 *a,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_neg_self    (CrankVecUint2 *a);

//////// Scalar operations ////////

void          crank_vec_uint2_muls        (CrankVecUint2 *a,
                                           const guint    b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_divs        (CrankVecUint2 *a,
                                           const guint    b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_mods        (CrankVecUint2 *a,
                                           const guint    b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_muls_self   (CrankVecUint2 *a,
                                           const guint    b);

void          crank_vec_uint2_divs_self   (CrankVecUint2 *a,
                                           const guint    b);

void          crank_vec_uint2_mods_self   (CrankVecUint2 *a,
                                           const guint    b);


//////// Standard vector operations ////////

void          crank_vec_uint2_add         (CrankVecUint2 *a,
                                           CrankVecUint2 *b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_add_self    (CrankVecUint2 *a,
                                           CrankVecUint2 *b);

void          crank_vec_uint2_sub         (CrankVecUint2 *a,
                                           CrankVecUint2 *b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_sub_self    (CrankVecUint2 *a,
                                           CrankVecUint2 *b);

guint         crank_vec_uint2_dot         (CrankVecUint2 *a,
                                           CrankVecUint2 *b);

//////// Component vector operations ////////

void          crank_vec_uint2_cmpmul      (CrankVecUint2 *a,
                                           CrankVecUint2 *b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_cmpmul_self (CrankVecUint2 *a,
                                           CrankVecUint2 *b);

void          crank_vec_uint2_cmpdiv      (CrankVecUint2 *a,
                                           CrankVecUint2 *b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_cmpdiv_self (CrankVecUint2 *a,
                                           CrankVecUint2 *b);

void          crank_vec_uint2_cmpmod      (CrankVecUint2 *a,
                                           CrankVecUint2 *b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_cmpmod_self (CrankVecUint2 *a,
                                           CrankVecUint2 *b);

void          crank_vec_uint2_cmpless     (CrankVecUint2  *a,
                                           CrankVecUint2  *b,
                                           CrankVecBool2 *r);

void          crank_vec_uint2_cmpeq       (CrankVecUint2  *a,
                                           CrankVecUint2  *b,
                                           CrankVecBool2 *r);

void          crank_vec_uint2_cmpgreater  (CrankVecUint2  *a,
                                           CrankVecUint2  *b,
                                           CrankVecBool2 *r);

void          crank_vec_uint2_cmpcmp  (CrankVecUint2 *a,
                                       CrankVecUint2 *b,
                                       CrankVecInt2  *r);

void          crank_vec_uint2_min (CrankVecUint2 *a,
                                   CrankVecUint2 *b,
                                   CrankVecUint2 *r);

void          crank_vec_uint2_max (CrankVecUint2 *a,
                                   CrankVecUint2 *b,
                                   CrankVecUint2 *r);





/**
 * CrankVecUint3:
 * @x: First element.
 * @y: Second element.
 * @z: Third element.
 *
 * integer vector. Compared to ivec3 in GLSL.
 */
struct _CrankVecUint3 {
  guint x;
  guint y;
  guint z;
};

#define CRANK_TYPE_VEC_UINT3 (crank_vec_uint3_get_type ())
GType         crank_vec_uint3_get_type (void);



void          crank_vec_uint3_init        (CrankVecUint3 *vec,
                                           const guint    x,
                                           const guint    y,
                                           const guint    z);

void          crank_vec_uint3_init_arr    (CrankVecUint3 *vec,
                                           guint         *arr);

void          crank_vec_uint3_init_valist (CrankVecUint3 *vec,
                                           va_list       varargs);

void          crank_vec_uint3_init_fill   (CrankVecUint3 *vec,
                                           const guint    fill);

void          crank_vec_uint3_init_from_vb(CrankVecUint3  *vec,
                                           CrankVecBool3 *vb);

void          crank_vec_uint3_copy        (CrankVecUint3 *vec,
                                           CrankVecUint3 *other);

CrankVecUint3 *crank_vec_uint3_dup        (CrankVecUint3 *vec);

guint         crank_vec_uint3_get         (CrankVecUint3 *vec,
                                           const guint   index);

void          crank_vec_uint3_set         (CrankVecUint3 *vec,
                                           const guint   index,
                                           const guint   value);

gboolean      crank_vec_uint3_foreach     (CrankVecUint3    *vec,
                                           CrankBoolUintFunc func,
                                           gpointer         userdata);

void          crank_vec_uint3_iterator    (CrankVecUint3    *vec,
                                           CrankIterMemUint *iter);

//////// Basic operation ////////

guint         crank_vec_uint3_hash (gconstpointer a);

gboolean      crank_vec_uint3_equal (gconstpointer a,
                                     gconstpointer b);

gchar        *crank_vec_uint3_to_string (CrankVecUint3 *vec);

gchar        *crank_vec_uint3_to_string_full(CrankVecUint3 *vec,
                                             const gchar  *left,
                                             const gchar  *in,
                                             const gchar  *right,
                                             const gchar  *format);


//////// Standard vector property ///////

guint         crank_vec_uint3_get_magn_sq      (CrankVecUint3 *vec);

gfloat        crank_vec_uint3_get_magn         (CrankVecUint3 *vec);


//////// Standard unary operations ////////

void          crank_vec_uint3_neg         (CrankVecUint3 *a,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_neg_self    (CrankVecUint3 *a);


//////// Scalar operations ////////

void          crank_vec_uint3_muls        (CrankVecUint3 *a,
                                           const guint    b,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_divs        (CrankVecUint3 *a,
                                           const guint    b,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_mods        (CrankVecUint3 *a,
                                           const guint    b,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_muls_self   (CrankVecUint3 *a,
                                           const guint    b);

void          crank_vec_uint3_divs_self   (CrankVecUint3 *a,
                                           const guint    b);

void          crank_vec_uint3_mods_self   (CrankVecUint3 *a,
                                           const guint    b);


//////// Standard vector operations ////////

void          crank_vec_uint3_add         (CrankVecUint3 *a,
                                           CrankVecUint3 *b,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_add_self    (CrankVecUint3 *a,
                                           CrankVecUint3 *b);

void          crank_vec_uint3_sub         (CrankVecUint3 *a,
                                           CrankVecUint3 *b,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_sub_self    (CrankVecUint3 *a,
                                           CrankVecUint3 *b);

guint         crank_vec_uint3_dot         (CrankVecUint3 *a,
                                           CrankVecUint3 *b);

void          crank_vec_uint3_crs         (CrankVecUint3 *a,
                                           CrankVecUint3 *b,
                                           CrankVecUint3 *r);
void          crank_vec_uint3_crs_self    (CrankVecUint3 *a,
                                           CrankVecUint3 *b);

//////// Component vector operations ////////

void          crank_vec_uint3_cmpmul       (CrankVecUint3 *a,
                                           CrankVecUint3 *b,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_cmpmul_self  (CrankVecUint3 *a,
                                           CrankVecUint3 *b);

void          crank_vec_uint3_cmpdiv       (CrankVecUint3 *a,
                                           CrankVecUint3 *b,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_cmpdiv_self  (CrankVecUint3 *a,
                                           CrankVecUint3 *b);

void          crank_vec_uint3_cmpmod       (CrankVecUint3 *a,
                                           CrankVecUint3 *b,
                                           CrankVecUint3 *r);

void          crank_vec_uint3_cmpmod_self  (CrankVecUint3 *a,
                                           CrankVecUint3 *b);

void          crank_vec_uint3_cmpless      (CrankVecUint3  *a,
                                           CrankVecUint3  *b,
                                           CrankVecBool3 *r);

void          crank_vec_uint3_cmpeq        (CrankVecUint3  *a,
                                           CrankVecUint3  *b,
                                           CrankVecBool3 *r);

void          crank_vec_uint3_cmpgreater   (CrankVecUint3  *a,
                                           CrankVecUint3  *b,
                                           CrankVecBool3 *r);

void          crank_vec_uint3_cmpcmp   (CrankVecUint3 *a,
                                        CrankVecUint3 *b,
                                        CrankVecInt3  *r);

void          crank_vec_uint3_min  (CrankVecUint3 *a,
                                   CrankVecUint3 *b,
                                   CrankVecUint3 *r);

void          crank_vec_uint3_max  (CrankVecUint3 *a,
                                   CrankVecUint3 *b,
                                   CrankVecUint3 *r);





/**
 * CrankVecUint4:
 * @x: First element.
 * @y: Second element.
 * @z: Third element.
 * @w: Fourth element.
 *
 * integer vector. Compared to ivec4 in GLSL.
 */
struct _CrankVecUint4 {
  guint x;
  guint y;
  guint z;
  guint w;
};

#define CRANK_TYPE_VEC_UINT4 (crank_vec_uint4_get_type ())
GType         crank_vec_uint4_get_type (void);



void          crank_vec_uint4_init        (CrankVecUint4 *vec,
                                           const guint    x,
                                           const guint    y,
                                           const guint    z,
                                           const guint    w);

void          crank_vec_uint4_init_arr    (CrankVecUint4 *vec,
                                           guint         *arr);

void          crank_vec_uint4_init_valist (CrankVecUint4 *vec,
                                           va_list       varargs);

void          crank_vec_uint4_init_fill   (CrankVecUint4 *vec,
                                           const guint    fill);

void          crank_vec_uint4_init_from_vb(CrankVecUint4  *vec,
                                           CrankVecBool4 *vb);

void          crank_vec_uint4_copy        (CrankVecUint4 *vec,
                                           CrankVecUint4 *other);

CrankVecUint4 *crank_vec_uint4_dup        (CrankVecUint4 *vec);

guint         crank_vec_uint4_get         (CrankVecUint4 *vec,
                                           const guint   index);

void          crank_vec_uint4_set         (CrankVecUint4 *vec,
                                           const guint   index,
                                           const guint   value);

gboolean      crank_vec_uint4_foreach     (CrankVecUint4    *vec,
                                           CrankBoolUintFunc func,
                                           gpointer          userdata);

void          crank_vec_uint4_iterator    (CrankVecUint4    *vec,
                                           CrankIterMemUint *iter);

//////// Basic operation ////////

guint         crank_vec_uint4_hash (gconstpointer a);

gboolean      crank_vec_uint4_equal(gconstpointer a,
                                    gconstpointer b);

gchar        *crank_vec_uint4_to_string (CrankVecUint4 *vec);

gchar        *crank_vec_uint4_to_string_full(CrankVecUint4 *vec,
                                             const gchar  *left,
                                             const gchar  *in,
                                             const gchar  *right,
                                             const gchar  *format);


//////// Standard vector property ///////

guint         crank_vec_uint4_get_magn_sq      (CrankVecUint4 *vec);

gfloat        crank_vec_uint4_get_magn         (CrankVecUint4 *vec);


//////// Standard unary operations ////////

void          crank_vec_uint4_neg          (CrankVecUint4 *a,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_neg_self     (CrankVecUint4 *a);


//////// Scalar operations ////////

void          crank_vec_uint4_muls        (CrankVecUint4 *a,
                                           const guint    b,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_muls_self   (CrankVecUint4 *a,
                                           const guint    b);

void          crank_vec_uint4_divs        (CrankVecUint4 *a,
                                           const guint    b,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_divs_self   (CrankVecUint4 *a,
                                           const guint    b);

void          crank_vec_uint4_mods        (CrankVecUint4 *a,
                                           const guint    b,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_mods_self   (CrankVecUint4 *a,
                                           const guint    b);


//////// Standard vector operations ////////

void          crank_vec_uint4_add         (CrankVecUint4 *a,
                                           CrankVecUint4 *b,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_add_self    (CrankVecUint4 *a,
                                           CrankVecUint4 *b);

void          crank_vec_uint4_sub         (CrankVecUint4 *a,
                                           CrankVecUint4 *b,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_sub_self    (CrankVecUint4 *a,
                                           CrankVecUint4 *b);

guint         crank_vec_uint4_dot         (CrankVecUint4 *a,
                                           CrankVecUint4 *b);

//////// Component vector operations ////////

void          crank_vec_uint4_cmpmul      (CrankVecUint4 *a,
                                           CrankVecUint4 *b,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_cmpmul_self (CrankVecUint4 *a,
                                           CrankVecUint4 *b);

void          crank_vec_uint4_cmpdiv      (CrankVecUint4 *a,
                                           CrankVecUint4 *b,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_cmpdiv_self (CrankVecUint4 *a,
                                           CrankVecUint4 *b);

void          crank_vec_uint4_cmpmod      (CrankVecUint4 *a,
                                           CrankVecUint4 *b,
                                           CrankVecUint4 *r);

void          crank_vec_uint4_cmpmod_self (CrankVecUint4 *a,
                                           CrankVecUint4 *b);

void          crank_vec_uint4_cmpless     (CrankVecUint4  *a,
                                           CrankVecUint4  *b,
                                           CrankVecBool4 *r);

void          crank_vec_uint4_cmpeq       (CrankVecUint4  *a,
                                           CrankVecUint4  *b,
                                           CrankVecBool4 *r);

void          crank_vec_uint4_cmpgreater  (CrankVecUint4  *a,
                                           CrankVecUint4  *b,
                                           CrankVecBool4 *r);

void          crank_vec_uint4_cmpcmp  (CrankVecUint4 *a,
                                       CrankVecUint4 *b,
                                       CrankVecInt4  *r);

void          crank_vec_uint4_min (CrankVecUint4 *a,
                                   CrankVecUint4 *b,
                                   CrankVecUint4 *r);

void          crank_vec_uint4_max (CrankVecUint4 *a,
                                   CrankVecUint4 *b,
                                   CrankVecUint4 *r);





/**
 * CrankVecUintN:
 * @data: (array length=n): data
 * @n: size of vector.
 *
 * Variable sized integer vector.
 */
struct _CrankVecUintN {
  guint *data;
  guint n;
};

#define CRANK_TYPE_VEC_UINT_N    (crank_vec_uint_n_get_type ())
GType         crank_vec_uint_n_get_type    (void);

void          crank_vec_uint_n_init        (CrankVecUintN *vec,
                                            const guint    n,
                                            ...);

void          crank_vec_uint_n_init_arr    (CrankVecUintN *vec,
                                            const guint    n,
                                            guint         *arr);

void          crank_vec_uint_n_init_valist (CrankVecUintN *vec,
                                            const guint    n,
                                            va_list        varargs);

void          crank_vec_uint_n_init_fill   (CrankVecUintN *vec,
                                            const guint    n,
                                            const guint    fill);

void          crank_vec_uint_n_init_from_vb(CrankVecUintN  *vec,
                                            CrankVecBoolN *vb);

void          crank_vec_uint_n_fini        (CrankVecUintN *vec);

void          crank_vec_uint_n_copy        (CrankVecUintN *vec,
                                            CrankVecUintN *other);

CrankVecUintN *crank_vec_uint_n_dup        (CrankVecUintN *vec);

void          crank_vec_uint_n_free        (CrankVecUintN *vec);

guint         crank_vec_uint_n_get_size    (CrankVecUintN *vec);

guint         crank_vec_uint_n_get         (CrankVecUintN *vec,
                                            const guint   index);

void          crank_vec_uint_n_set         (CrankVecUintN *vec,
                                            const guint   index,
                                            const guint   value);

void          crank_vec_uint_n_prepend     (CrankVecUintN *vec,
                                            const guint    value);

void          crank_vec_uint_n_append      (CrankVecUintN *vec,
                                            const guint    value);

void          crank_vec_uint_n_insert      (CrankVecUintN *vec,
                                            const guint    index,
                                            const guint    value);

void          crank_vec_uint_n_remove      (CrankVecUintN *vec,
                                            const guint   index);

gboolean      crank_vec_uint_n_foreach     (CrankVecUintN     *vec,
                                            CrankBoolUintFunc func,
                                            gpointer          userdata);

void          crank_vec_uint_n_iterator    (CrankVecUintN    *vec,
                                            CrankIterMemUint *iter);

//////// Basic operation ////////

guint         crank_vec_uint_n_hash (gconstpointer a);

gboolean      crank_vec_uint_n_equal (gconstpointer a,
                                     gconstpointer b);

gchar        *crank_vec_uint_n_to_string (CrankVecUintN *vec);

gchar        *crank_vec_uint_n_to_string_full(CrankVecUintN *vec,
                                              const gchar  *left,
                                              const gchar  *in,
                                              const gchar  *right,
                                              const gchar  *format);

//////// Classification ////////////////////////////////////////////////////////

gboolean      crank_vec_uint_n_is_zero        (CrankVecUintN *vec);

gboolean      crank_vec_uint_n_is_one         (CrankVecUintN *vec);

gboolean      crank_vec_uint_n_is_empty       (CrankVecUintN *vec);


//////// Standard vector property ///////

guint         crank_vec_uint_n_get_magn_sq    (CrankVecUintN *vec);

gfloat        crank_vec_uint_n_get_magn       (CrankVecUintN *vec);


//////// Standard unary operations ////////

void          crank_vec_uint_n_neg         (CrankVecUintN *a,
                                            CrankVecUintN *r);

void          crank_vec_uint_n_neg_self    (CrankVecUintN *a);


//////// Scalar operations ////////

void          crank_vec_uint_n_muls       (CrankVecUintN *a,
                                           const guint    b,
                                           CrankVecUintN *r);

void          crank_vec_uint_n_divs       (CrankVecUintN *a,
                                           const guint    b,
                                           CrankVecUintN *r);

void          crank_vec_uint_n_mods       (CrankVecUintN *a,
                                           const guint    b,
                                           CrankVecUintN *r);


void          crank_vec_uint_n_muls_self  (CrankVecUintN *a,
                                           const guint    b);

void          crank_vec_uint_n_divs_self  (CrankVecUintN *a,
                                           const guint    b);

void          crank_vec_uint_n_mods_self  (CrankVecUintN *a,
                                           const guint    b);


//////// Standard vector operations ////////

void          crank_vec_uint_n_add        (CrankVecUintN *a,
                                           CrankVecUintN *b,
                                           CrankVecUintN *r);

void          crank_vec_uint_n_add_self   (CrankVecUintN *a,
                                           CrankVecUintN *b);

void          crank_vec_uint_n_sub        (CrankVecUintN *a,
                                           CrankVecUintN *b,
                                           CrankVecUintN *r);

void          crank_vec_uint_n_sub_self   (CrankVecUintN *a,
                                           CrankVecUintN *b);

guint         crank_vec_uint_n_dot        (CrankVecUintN *a,
                                           CrankVecUintN *b);

//////// Component vector operations ////////

void          crank_vec_uint_n_cmpmul     (CrankVecUintN *a,
                                           CrankVecUintN *b,
                                           CrankVecUintN *r);

void          crank_vec_uint_n_cmpmul_self(CrankVecUintN *a,
                                           CrankVecUintN *b);

void          crank_vec_uint_n_cmpdiv     (CrankVecUintN *a,
                                           CrankVecUintN *b,
                                           CrankVecUintN *r);

void          crank_vec_uint_n_cmpdiv_self(CrankVecUintN *a,
                                           CrankVecUintN *b);

void          crank_vec_uint_n_cmpmod     (CrankVecUintN *a,
                                           CrankVecUintN *b,
                                           CrankVecUintN *r);

void          crank_vec_uint_n_cmpmod_self(CrankVecUintN *a,
                                           CrankVecUintN *b);

void          crank_vec_uint_n_cmpless    (CrankVecUintN  *a,
                                           CrankVecUintN  *b,
                                           CrankVecBoolN *r);

void          crank_vec_uint_n_cmpeq      (CrankVecUintN  *a,
                                           CrankVecUintN  *b,
                                           CrankVecBoolN *r);

void          crank_vec_uint_n_cmpgreater (CrankVecUintN  *a,
                                           CrankVecUintN  *b,
                                           CrankVecBoolN *r);

void          crank_vec_uint_n_cmpcmp (CrankVecUintN *a,
                                       CrankVecUintN *b,
                                       CrankVecIntN  *r);

void          crank_vec_uint_n_min(CrankVecUintN *a,
                                   CrankVecUintN *b,
                                   CrankVecUintN *r);

void          crank_vec_uint_n_max(CrankVecUintN *a,
                                   CrankVecUintN *b,
                                   CrankVecUintN *r);



G_END_DECLS

#endif //CRANKBOOLVEC_H
