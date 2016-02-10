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
#include "crankiter.h"
#include "crankveccommon.h"

G_BEGIN_DECLS

/**
 * crank_vec_uint2_zero:
 *
 * Static zero vector, whose all elements are 0.
 */
extern const CrankVecUint2 *crank_vec_uint2_zero;

/**
 * crank_vec_uint3_zero:
 *
 * Static zero vector, whose all elements are 0.
 */
extern const CrankVecUint3 *crank_vec_uint3_zero;

/**
 * crank_vec_uint4_zero:
 *
 * Static zero vector, whose all elements are 0.
 */
extern const CrankVecUint4 *crank_vec_uint4_zero;



/**
 * crank_vec_uint2_one:
 *
 * Static one vector, whose all elements are 1.
 */
extern const CrankVecUint2 *crank_vec_uint2_one;

/**
 * crank_vec_uint3_one:
 *
 * Static one vector, whose all elements are 1.
 */
extern const CrankVecUint3 *crank_vec_uint3_one;

/**
 * crank_vec_uint4_one:
 *
 * Static one vector, whose all elements are 1.
 */
extern const CrankVecUint4 *crank_vec_uint4_one;

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



void          crank_vec_uint2_init        (CrankVecUint2       *vec,
                                           const guint          x,
                                           const guint          y);

void          crank_vec_uint2_init_arr    (CrankVecUint2       *vec,
                                           guint               *arr);

void          crank_vec_uint2_init_valist (CrankVecUint2       *vec,
                                           va_list              varargs);

void          crank_vec_uint2_init_fill   (CrankVecUint2       *vec,
                                           const guint          fill);

void          crank_vec_uint2_init_from_vb(CrankVecUint2       *vec,
                                           const CrankVecBool2 *vb);

void          crank_vec_uint2_copy        (const CrankVecUint2 *vec,
                                           CrankVecUint2       *other);

CrankVecUint2 *crank_vec_uint2_dup        (const CrankVecUint2 *vec);

guint          crank_vec_uint2_get        (const CrankVecUint2 *vec,
                                           const guint          index);

void          crank_vec_uint2_set         (const CrankVecUint2 *vec,
                                           const guint          index,
                                           const guint          value);

gboolean      crank_vec_uint2_foreach     (const CrankVecUint2 *vec,
                                           CrankBoolUintFunc    func,
                                           gpointer             userdata);

void          crank_vec_uint2_iterator    (const CrankVecUint2 *vec,
                                           CrankIterMemUint    *iter);

//////// Basic operation ////////

guint         crank_vec_uint2_hash        (gconstpointer        a);

gboolean      crank_vec_uint2_equal       (gconstpointer        a,
                                           gconstpointer        b);

gchar        *crank_vec_uint2_to_string   (const CrankVecUint2 *vec);

gchar        *crank_vec_uint2_to_string_full(const CrankVecUint2 *vec,
                                             const gchar       *left,
                                             const gchar       *in,
                                             const gchar       *right,
                                             const gchar       *format);


//////// Standard vector property ///////

guint         crank_vec_uint2_get_magn_sq (const CrankVecUint2 *vec);

gfloat        crank_vec_uint2_get_magn    (const CrankVecUint2 *vec);


//////// Standard unary operations ////////

void          crank_vec_uint2_neg         (const CrankVecUint2 *a,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_neg_self    (CrankVecUint2       *a);

//////// Scalar operations ////////

void          crank_vec_uint2_muls        (const CrankVecUint2 *a,
                                           const guint    b,
                                           CrankVecUint2 *r);

void          crank_vec_uint2_divs        (const CrankVecUint2 *a,
                                           const guint          b,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_mods        (const CrankVecUint2 *a,
                                           const guint          b,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_muls_self   (CrankVecUint2 *a,
                                           const guint    b);

void          crank_vec_uint2_divs_self   (CrankVecUint2 *a,
                                           const guint    b);

void          crank_vec_uint2_mods_self   (CrankVecUint2 *a,
                                           const guint    b);


//////// Standard vector operations ////////

void          crank_vec_uint2_add         (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_add_self    (CrankVecUint2       *a,
                                           const CrankVecUint2 *b);

void          crank_vec_uint2_sub         (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_sub_self    (CrankVecUint2       *a,
                                           const CrankVecUint2 *b);

guint         crank_vec_uint2_dot         (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b);

//////// Component vector operations ////////

void          crank_vec_uint2_cmpmul      (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_cmpmul_self (CrankVecUint2       *a,
                                           const CrankVecUint2 *b);

void          crank_vec_uint2_cmpdiv      (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_cmpdiv_self (CrankVecUint2       *a,
                                           const CrankVecUint2 *b);

void          crank_vec_uint2_cmpmod      (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_cmpmod_self (CrankVecUint2       *a,
                                           const CrankVecUint2 *b);

void          crank_vec_uint2_cmpless     (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecBool2       *r);

void          crank_vec_uint2_cmpeq       (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecBool2       *r);

void          crank_vec_uint2_cmpgreater  (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecBool2       *r);

void          crank_vec_uint2_cmpcmp      (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecInt2        *r);

void          crank_vec_uint2_min         (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecUint2       *r);

void          crank_vec_uint2_max         (const CrankVecUint2 *a,
                                           const CrankVecUint2 *b,
                                           CrankVecUint2       *r);





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



void          crank_vec_uint3_init        (CrankVecUint3       *vec,
                                           const guint          x,
                                           const guint          y,
                                           const guint          z);

void          crank_vec_uint3_init_arr    (CrankVecUint3       *vec,
                                           guint               *arr);

void          crank_vec_uint3_init_valist (CrankVecUint3       *vec,
                                           va_list              varargs);

void          crank_vec_uint3_init_fill   (CrankVecUint3       *vec,
                                           const guint          fill);

void          crank_vec_uint3_init_from_vb(CrankVecUint3       *vec,
                                           const CrankVecBool3 *vb);

void          crank_vec_uint3_copy        (const CrankVecUint3 *vec,
                                           CrankVecUint3       *other);

CrankVecUint3 *crank_vec_uint3_dup        (const CrankVecUint3 *vec);

guint         crank_vec_uint3_get         (const CrankVecUint3 *vec,
                                           const guint          index);

void          crank_vec_uint3_set         (CrankVecUint3       *vec,
                                           const guint          index,
                                           const guint          value);

gboolean      crank_vec_uint3_foreach     (const CrankVecUint3 *vec,
                                           CrankBoolUintFunc    func,
                                           gpointer             userdata);

void          crank_vec_uint3_iterator    (const CrankVecUint3 *vec,
                                           CrankIterMemUint    *iter);

//////// Basic operation ////////

guint         crank_vec_uint3_hash        (gconstpointer        a);

gboolean      crank_vec_uint3_equal       (gconstpointer        a,
                                           gconstpointer        b);

gchar        *crank_vec_uint3_to_string   (const CrankVecUint3 *vec);

gchar        *crank_vec_uint3_to_string_full(const CrankVecUint3 *vec,
                                             const gchar         *left,
                                             const gchar         *in,
                                             const gchar         *right,
                                             const gchar         *format);


//////// Standard vector property ///////

guint         crank_vec_uint3_get_magn_sq (const CrankVecUint3 *vec);

gfloat        crank_vec_uint3_get_magn    (const CrankVecUint3 *vec);


//////// Standard unary operations ////////

void          crank_vec_uint3_neg         (const CrankVecUint3 *a,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_neg_self    (CrankVecUint3       *a);


//////// Scalar operations ////////

void          crank_vec_uint3_muls        (const CrankVecUint3 *a,
                                           const guint          b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_divs        (const CrankVecUint3 *a,
                                           const guint          b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_mods        (const CrankVecUint3 *a,
                                           const guint          b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_muls_self   (CrankVecUint3       *a,
                                           const guint          b);

void          crank_vec_uint3_divs_self   (CrankVecUint3       *a,
                                           const guint          b);

void          crank_vec_uint3_mods_self   (CrankVecUint3       *a,
                                           const guint          b);


//////// Standard vector operations ////////

void          crank_vec_uint3_add         (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_add_self    (CrankVecUint3       *a,
                                           const CrankVecUint3 *b);

void          crank_vec_uint3_sub         (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_sub_self    (CrankVecUint3       *a,
                                           const CrankVecUint3 *b);

guint         crank_vec_uint3_dot         (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b);

void          crank_vec_uint3_crs         (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecInt3        *r);

//////// Component vector operations ////////

void          crank_vec_uint3_cmpmul      (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_cmpmul_self (CrankVecUint3       *a,
                                           const CrankVecUint3 *b);

void          crank_vec_uint3_cmpdiv      (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_cmpdiv_self (CrankVecUint3       *a,
                                           const CrankVecUint3 *b);

void          crank_vec_uint3_cmpmod      (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_cmpmod_self (CrankVecUint3       *a,
                                           const CrankVecUint3 *b);

void          crank_vec_uint3_cmpless     (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecBool3       *r);

void          crank_vec_uint3_cmpeq       (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecBool3       *r);

void          crank_vec_uint3_cmpgreater  (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecBool3       *r);

void          crank_vec_uint3_cmpcmp      (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecInt3        *r);

void          crank_vec_uint3_min         (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecUint3       *r);

void          crank_vec_uint3_max         (const CrankVecUint3 *a,
                                           const CrankVecUint3 *b,
                                           CrankVecUint3       *r);





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



void          crank_vec_uint4_init        (CrankVecUint4       *vec,
                                           const guint          x,
                                           const guint          y,
                                           const guint          z,
                                           const guint          w);

void          crank_vec_uint4_init_arr    (CrankVecUint4       *vec,
                                           guint               *arr);

void          crank_vec_uint4_init_valist (CrankVecUint4       *vec,
                                           va_list              varargs);

void          crank_vec_uint4_init_fill   (CrankVecUint4       *vec,
                                           const guint          fill);

void          crank_vec_uint4_init_from_vb(CrankVecUint4       *vec,
                                           CrankVecBool4       *vb);

void          crank_vec_uint4_copy        (const CrankVecUint4 *vec,
                                           CrankVecUint4       *other);

CrankVecUint4 *crank_vec_uint4_dup        (const CrankVecUint4 *vec);

guint         crank_vec_uint4_get         (const CrankVecUint4 *vec,
                                           const guint          index);

void          crank_vec_uint4_set         (CrankVecUint4       *vec,
                                           const guint          index,
                                           const guint          value);

gboolean      crank_vec_uint4_foreach     (const CrankVecUint4 *vec,
                                           CrankBoolUintFunc    func,
                                           gpointer             userdata);

void          crank_vec_uint4_iterator    (const CrankVecUint4 *vec,
                                           CrankIterMemUint    *iter);

//////// Basic operation ////////

guint         crank_vec_uint4_hash        (gconstpointer a);

gboolean      crank_vec_uint4_equal       (gconstpointer a,
                                           gconstpointer b);

gchar        *crank_vec_uint4_to_string   (const CrankVecUint4 *vec);

gchar        *crank_vec_uint4_to_string_full(const CrankVecUint4 *vec,
                                             const gchar  *left,
                                             const gchar  *in,
                                             const gchar  *right,
                                             const gchar  *format);


//////// Standard vector property ///////

guint         crank_vec_uint4_get_magn_sq (const CrankVecUint4 *vec);

gfloat        crank_vec_uint4_get_magn    (const CrankVecUint4 *vec);


//////// Standard unary operations ////////

void          crank_vec_uint4_neg         (const CrankVecUint4 *a,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_neg_self    (CrankVecUint4       *a);


//////// Scalar operations ////////

void          crank_vec_uint4_muls        (const CrankVecUint4 *a,
                                           const guint          b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_muls_self   (CrankVecUint4       *a,
                                           const guint          b);

void          crank_vec_uint4_divs        (const CrankVecUint4 *a,
                                           const guint          b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_divs_self   (CrankVecUint4       *a,
                                           const guint          b);

void          crank_vec_uint4_mods        (const CrankVecUint4 *a,
                                           const guint          b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_mods_self   (CrankVecUint4       *a,
                                           const guint          b);


//////// Standard vector operations ////////

void          crank_vec_uint4_add         (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_add_self    (CrankVecUint4       *a,
                                           const CrankVecUint4 *b);

void          crank_vec_uint4_sub         (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_sub_self    (CrankVecUint4       *a,
                                           const CrankVecUint4 *b);

guint         crank_vec_uint4_dot         (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b);

//////// Component vector operations ////////

void          crank_vec_uint4_cmpmul      (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_cmpmul_self (CrankVecUint4       *a,
                                           const CrankVecUint4 *b);

void          crank_vec_uint4_cmpdiv      (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_cmpdiv_self (CrankVecUint4       *a,
                                           const CrankVecUint4 *b);

void          crank_vec_uint4_cmpmod      (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_cmpmod_self (CrankVecUint4       *a,
                                           const CrankVecUint4 *b);

void          crank_vec_uint4_cmpless     (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecBool4       *r);

void          crank_vec_uint4_cmpeq       (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecBool4       *r);

void          crank_vec_uint4_cmpgreater  (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecBool4       *r);

void          crank_vec_uint4_cmpcmp      (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecInt4        *r);

void          crank_vec_uint4_min         (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecUint4       *r);

void          crank_vec_uint4_max         (const CrankVecUint4 *a,
                                           const CrankVecUint4 *b,
                                           CrankVecUint4       *r);





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

void          crank_vec_uint_n_init        (CrankVecUintN       *vec,
                                            const guint          n,
                                            ...);

void          crank_vec_uint_n_init_arr    (CrankVecUintN       *vec,
                                            const guint          n,
                                            guint               *arr);

void          crank_vec_uint_n_init_valist (CrankVecUintN       *vec,
                                            const guint          n,
                                            va_list              varargs);

void          crank_vec_uint_n_init_fill   (CrankVecUintN       *vec,
                                            const guint          n,
                                            const guint          fill);

void          crank_vec_uint_n_init_from_vb(CrankVecUintN       *vec,
                                            const CrankVecBoolN *vb);

void          crank_vec_uint_n_fini        (CrankVecUintN       *vec);

void          crank_vec_uint_n_copy        (const CrankVecUintN *vec,
                                            CrankVecUintN       *other);

CrankVecUintN *crank_vec_uint_n_dup        (const CrankVecUintN *vec);

void          crank_vec_uint_n_free        (CrankVecUintN       *vec);

guint         crank_vec_uint_n_get_size    (const CrankVecUintN *vec);

guint         crank_vec_uint_n_get         (const CrankVecUintN *vec,
                                            const guint          index);

void          crank_vec_uint_n_set         (CrankVecUintN       *vec,
                                            const guint          index,
                                            const guint          value);

void          crank_vec_uint_n_prepend     (CrankVecUintN       *vec,
                                            const guint          value);

void          crank_vec_uint_n_append      (CrankVecUintN       *vec,
                                            const guint          value);

void          crank_vec_uint_n_insert      (CrankVecUintN       *vec,
                                            const guint          index,
                                            const guint          value);

void          crank_vec_uint_n_remove      (CrankVecUintN       *vec,
                                            const guint          index);

gboolean      crank_vec_uint_n_foreach     (const CrankVecUintN *vec,
                                            CrankBoolUintFunc    func,
                                            gpointer             userdata);

void          crank_vec_uint_n_iterator    (const CrankVecUintN *vec,
                                            CrankIterMemUint    *iter);

//////// Basic operation ////////

guint         crank_vec_uint_n_hash        (gconstpointer        a);

gboolean      crank_vec_uint_n_equal       (gconstpointer        a,
                                            gconstpointer        b);

gchar        *crank_vec_uint_n_to_string   (const CrankVecUintN *vec);

gchar        *crank_vec_uint_n_to_string_full(const CrankVecUintN *vec,
                                              const gchar         *left,
                                              const gchar         *in,
                                              const gchar         *right,
                                              const gchar         *format);

//////// Classification ////////////////////////////////////////////////////////

gboolean      crank_vec_uint_n_is_zero     (const CrankVecUintN *vec);

gboolean      crank_vec_uint_n_is_one      (const CrankVecUintN *vec);

gboolean      crank_vec_uint_n_is_empty    (const CrankVecUintN *vec);


//////// Standard vector property ///////

guint         crank_vec_uint_n_get_magn_sq (const CrankVecUintN *vec);

gfloat        crank_vec_uint_n_get_magn    (const CrankVecUintN *vec);


//////// Standard unary operations ////////

void          crank_vec_uint_n_neg         (const CrankVecUintN *a,
                                            CrankVecUintN       *r);

void          crank_vec_uint_n_neg_self    (CrankVecUintN       *a);


//////// Scalar operations ////////

void          crank_vec_uint_n_muls        (const CrankVecUintN *a,
                                            const guint          b,
                                            CrankVecUintN       *r);

void          crank_vec_uint_n_divs        (const CrankVecUintN *a,
                                            const guint          b,
                                            CrankVecUintN       *r);

void          crank_vec_uint_n_mods        (const CrankVecUintN *a,
                                            const guint          b,
                                            CrankVecUintN       *r);


void          crank_vec_uint_n_muls_self   (CrankVecUintN *a,
                                            const guint    b);

void          crank_vec_uint_n_divs_self   (CrankVecUintN *a,
                                            const guint    b);

void          crank_vec_uint_n_mods_self   (CrankVecUintN *a,
                                            const guint    b);


//////// Standard vector operations ////////

void          crank_vec_uint_n_add        (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecUintN       *r);

void          crank_vec_uint_n_add_self   (CrankVecUintN       *a,
                                           const CrankVecUintN *b);

void          crank_vec_uint_n_sub        (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecUintN       *r);

void          crank_vec_uint_n_sub_self   (CrankVecUintN       *a,
                                           const CrankVecUintN *b);

guint         crank_vec_uint_n_dot        (const CrankVecUintN *a,
                                           const CrankVecUintN *b);

//////// Component vector operations ////////

void          crank_vec_uint_n_cmpmul     (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecUintN       *r);

void          crank_vec_uint_n_cmpmul_self(CrankVecUintN       *a,
                                           const CrankVecUintN *b);

void          crank_vec_uint_n_cmpdiv     (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecUintN       *r);

void          crank_vec_uint_n_cmpdiv_self(CrankVecUintN       *a,
                                           const CrankVecUintN *b);

void          crank_vec_uint_n_cmpmod     (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecUintN       *r);

void          crank_vec_uint_n_cmpmod_self(CrankVecUintN       *a,
                                           const CrankVecUintN *b);

void          crank_vec_uint_n_cmpless    (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecBoolN       *r);

void          crank_vec_uint_n_cmpeq      (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecBoolN       *r);

void          crank_vec_uint_n_cmpgreater (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecBoolN       *r);

void          crank_vec_uint_n_cmpcmp     (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecIntN        *r);

void          crank_vec_uint_n_min        (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecUintN       *r);

void          crank_vec_uint_n_max        (const CrankVecUintN *a,
                                           const CrankVecUintN *b,
                                           CrankVecUintN       *r);



G_END_DECLS

#endif //CRANKBOOLVEC_H
