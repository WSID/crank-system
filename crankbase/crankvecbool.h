#ifndef CRANKBOOLVEC_H
#define CRANKBOOLVEC_H

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
#error crankboolvec.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankiter.h"
#include "crankveccommon.h"

G_BEGIN_DECLS

/**
 * CrankVecBool2:
 * @x: First vector element.
 * @y: Second vector element.
 *
 * Represents a boolean vector. Compared to bvec2 in GLSL.
 */

struct _CrankVecBool2 {
  gboolean x;
  gboolean y;
};

#define CRANK_TYPE_VEC_BOOL2    (crank_vec_bool2_get_type ())
GType          crank_vec_bool2_get_type    (void);

//////// Initialization ////////////////////////////////////////////////////////

void           crank_vec_bool2_init        (CrankVecBool2 *vec,
                                            gboolean       x,
                                            gboolean       y);

void           crank_vec_bool2_init_arr    (CrankVecBool2 *vec,
                                            gboolean      *arr);

void           crank_vec_bool2_init_valist (CrankVecBool2 *vec,
                                            va_list        varargs);

void           crank_vec_bool2_init_fill   (CrankVecBool2 *vec,
                                            const gboolean fill);


//////// Basic Operations //////////////////////////////////////////////////////

void           crank_vec_bool2_copy        (CrankVecBool2 *vec,
                                            CrankVecBool2 *other);

CrankVecBool2 *crank_vec_bool2_dup         (CrankVecBool2 *vec);


gboolean       crank_vec_bool2_equal       (gconstpointer a,
                                            gconstpointer b);

guint          crank_vec_bool2_hash        (gconstpointer a);


gchar         *crank_vec_bool2_to_string   (CrankVecBool2 *vec);

gchar         *crank_vec_bool2_to_string_full (CrankVecBool2 *vec,
                                               const gchar   *left,
                                               const gchar   *in,
                                               const gchar   *right,
                                               const gchar   *on_true,
                                               const gchar   *on_false);


//////// Basic property ////////////////////////////////////////////////////////

gboolean       crank_vec_bool2_get_any     (CrankVecBool2 *vec);

gboolean       crank_vec_bool2_get_all     (CrankVecBool2 *vec);

guint          crank_vec_bool2_get_count   (CrankVecBool2 *vec);

gfloat         crank_vec_bool2_get_ratio   (CrankVecBool2 *vec);

//////// Function as collection ////////////////////////////////////////////////

gboolean       crank_vec_bool2_get         (CrankVecBool2 *vec,
                                            const guint    index);

void           crank_vec_bool2_set         (CrankVecBool2 *vec,
                                            const guint    index,
                                            const gboolean value);

gboolean       crank_vec_bool2_foreach     (CrankVecBool2    *vec,
                                            CrankBoolBoolFunc func,
                                            gpointer          userdata);

void           crank_vec_bool2_iterator    (CrankVecBool2    *vec,
                                            CrankIterMemBool *iter);


//////// Vector - Vector Operations ////////////////////////////////////////////

void           crank_vec_bool2_and         (CrankVecBool2 *a,
                                            CrankVecBool2 *b,
                                            CrankVecBool2 *r);
void           crank_vec_bool2_and_self    (CrankVecBool2 *a,
                                            CrankVecBool2 *b);

void           crank_vec_bool2_or          (CrankVecBool2 *a,
                                            CrankVecBool2 *b,
                                            CrankVecBool2 *r);

void           crank_vec_bool2_or_self     (CrankVecBool2 *a,
                                            CrankVecBool2 *b);

void           crank_vec_bool2_xor         (CrankVecBool2 *a,
                                            CrankVecBool2 *b,
                                            CrankVecBool2 *r);

void           crank_vec_bool2_xor_self    (CrankVecBool2 *a,
                                            CrankVecBool2 *b);

void           crank_vec_bool2_not         (CrankVecBool2 *a,
                                            CrankVecBool2 *r);

void           crank_vec_bool2_not_self    (CrankVecBool2 *a);


void           crank_vec_bool2_andv        (CrankVecBool2 *a,
                                            CrankVecBool2 *b,
                                            CrankVecBool2 *r);

void           crank_vec_bool2_orv         (CrankVecBool2 *a,
                                            CrankVecBool2 *b,
                                            CrankVecBool2 *r);

void           crank_vec_bool2_notv        (CrankVecBool2 *a,
                                            CrankVecBool2 *r);



/**
 * CrankVecBool3:
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 *
 * Represents a boolean vector. Compared to bvec3 in GLSL.
 */
struct _CrankVecBool3 {
  gboolean x;
  gboolean y;
  gboolean z;
};

#define CRANK_TYPE_VEC_BOOL3    (crank_vec_bool3_get_type ())
GType          crank_vec_bool3_get_type    (void);

//////// Initialization ////////////////////////////////////////////////////////

void           crank_vec_bool3_init        (CrankVecBool3 *vec,
                                            gboolean       x,
                                            gboolean       y,
                                            gboolean       z);

void           crank_vec_bool3_init_arr    (CrankVecBool3 *vec,
                                            gboolean      *arr);

void           crank_vec_bool3_init_valist (CrankVecBool3 *vec,
                                            va_list        varargs);

void           crank_vec_bool3_init_fill   (CrankVecBool3 *vec,
                                            const gboolean fill);


//////// Basic Operations //////////////////////////////////////////////////////

void           crank_vec_bool3_copy        (CrankVecBool3 *vec,
                                            CrankVecBool3 *other);

CrankVecBool3 *crank_vec_bool3_dup         (CrankVecBool3 *vec);

gboolean       crank_vec_bool3_equal       (gconstpointer a,
                                            gconstpointer b);

guint          crank_vec_bool3_hash        (gconstpointer a);

gchar         *crank_vec_bool3_to_string   (CrankVecBool3 *vec);

gchar         *crank_vec_bool3_to_string_full (CrankVecBool3 *vec,
                                               const gchar   *left,
                                               const gchar   *in,
                                               const gchar   *right,
                                               const gchar   *on_true,
                                               const gchar   *on_false);


//////// Basic Properties //////////////////////////////////////////////////////

gboolean       crank_vec_bool3_get_any     (CrankVecBool3 *vec);

gboolean       crank_vec_bool3_get_all     (CrankVecBool3 *vec);

guint          crank_vec_bool3_get_count   (CrankVecBool3 *vec);

gfloat         crank_vec_bool3_get_ratio   (CrankVecBool3 *vec);


//////// Function as collection ////////////////////////////////////////////////

gboolean       crank_vec_bool3_get         (CrankVecBool3 *vec,
                                            const guint    index);

void           crank_vec_bool3_set         (CrankVecBool3 *vec,
                                            const guint    index,
                                            const gboolean value);

gboolean       crank_vec_bool3_foreach     (CrankVecBool3    *vec,
                                            CrankBoolBoolFunc func,
                                            gpointer          userdata);

void           crank_vec_bool3_iterator    (CrankVecBool3    *vec,
                                            CrankIterMemBool *iter);


//////// Vector - Vector Operations ////////////////////////////////////////////

void           crank_vec_bool3_and         (CrankVecBool3 *a,
                                            CrankVecBool3 *b,
                                            CrankVecBool3 *r);

void           crank_vec_bool3_and_self    (CrankVecBool3 *a,
                                            CrankVecBool3 *b);

void           crank_vec_bool3_or          (CrankVecBool3 *a,
                                            CrankVecBool3 *b,
                                            CrankVecBool3 *r);

void           crank_vec_bool3_or_self     (CrankVecBool3 *a,
                                            CrankVecBool3 *b);

void           crank_vec_bool3_xor         (CrankVecBool3 *a,
                                            CrankVecBool3 *b,
                                            CrankVecBool3 *r);

void           crank_vec_bool3_xor_self    (CrankVecBool3 *a,
                                            CrankVecBool3 *b);

void           crank_vec_bool3_not         (CrankVecBool3 *a,
                                            CrankVecBool3 *r);

void           crank_vec_bool3_not_self    (CrankVecBool3 *a);


void           crank_vec_bool3_andv        (CrankVecBool3 *a,
                                            CrankVecBool3 *b,
                                            CrankVecBool3 *r);

void           crank_vec_bool3_orv         (CrankVecBool3 *a,
                                            CrankVecBool3 *b,
                                            CrankVecBool3 *r);
void           crank_vec_bool3_notv        (CrankVecBool3 *a,
                                            CrankVecBool3 *r);




/**
 * CrankVecBool4:
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 * @w: Fourth vector element.
 *
 * Represents a boolean vector. Compared to bvec4 in GLSL.
 */
struct _CrankVecBool4 {
  gboolean x;
  gboolean y;
  gboolean z;
  gboolean w;
};

#define CRANK_TYPE_VEC_BOOL4    (crank_vec_bool4_get_type ())
GType          crank_vec_bool4_get_type    (void);

//////// Initialization ////////////////////////////////////////////////////////

void           crank_vec_bool4_init        (CrankVecBool4 *vec,
                                            gboolean       x,
                                            gboolean       y,
                                            gboolean       z,
                                            gboolean       w);

void           crank_vec_bool4_init_arr    (CrankVecBool4 *vec,
                                            gboolean      *arr);

void           crank_vec_bool4_init_valist (CrankVecBool4 *vec,
                                            va_list        varargs);

void           crank_vec_bool4_init_fill   (CrankVecBool4 *vec,
                                            const gboolean fill);


//////// Basic Operations //////////////////////////////////////////////////////

void           crank_vec_bool4_copy        (CrankVecBool4 *vec,
                                            CrankVecBool4 *other);

CrankVecBool4 *crank_vec_bool4_dup         (CrankVecBool4 *vec);

gboolean       crank_vec_bool4_equal       (gconstpointer a,
                                            gconstpointer b);

guint          crank_vec_bool4_hash        (gconstpointer a);

gchar         *crank_vec_bool4_to_string   (CrankVecBool4 *vec);

gchar         *crank_vec_bool4_to_string_full (CrankVecBool4 *vec,
                                               const gchar   *left,
                                               const gchar   *in,
                                               const gchar   *right,
                                               const gchar   *on_true,
                                               const gchar   *on_false);


//////// Basic Properties //////////////////////////////////////////////////////

gboolean       crank_vec_bool4_get_any     (CrankVecBool4 *vec);

gboolean       crank_vec_bool4_get_all     (CrankVecBool4 *vec);

guint          crank_vec_bool4_get_count   (CrankVecBool4 *vec);

gfloat         crank_vec_bool4_get_ratio   (CrankVecBool4 *vec);


//////// Functions as collection ///////////////////////////////////////////////

gboolean       crank_vec_bool4_get         (CrankVecBool4 *vec,
                                            const guint    index);

void           crank_vec_bool4_set         (CrankVecBool4 *vec,
                                            const guint    index,
                                            const gboolean value);

gboolean       crank_vec_bool4_foreach     (CrankVecBool4    *vec,
                                            CrankBoolBoolFunc func,
                                            gpointer          userdata);

void           crank_vec_bool4_iterator    (CrankVecBool4    *vec,
                                            CrankIterMemBool *iter);


//////// Vector - Vector Operations ////////////////////////////////////////////

void           crank_vec_bool4_and         (CrankVecBool4 *a,
                                            CrankVecBool4 *b,
                                            CrankVecBool4 *r);

void           crank_vec_bool4_and_self    (CrankVecBool4 *a,
                                            CrankVecBool4 *b);

void           crank_vec_bool4_or          (CrankVecBool4 *a,
                                            CrankVecBool4 *b,
                                            CrankVecBool4 *r);

void           crank_vec_bool4_or_self     (CrankVecBool4 *a,
                                            CrankVecBool4 *b);

void           crank_vec_bool4_xor         (CrankVecBool4 *a,
                                            CrankVecBool4 *b,
                                            CrankVecBool4 *r);

void           crank_vec_bool4_xor_self    (CrankVecBool4 *a,
                                            CrankVecBool4 *b);

void           crank_vec_bool4_not         (CrankVecBool4 *a,
                                            CrankVecBool4 *r);

void           crank_vec_bool4_not_self    (CrankVecBool4 *a);



void           crank_vec_bool4_andv        (CrankVecBool4 *a,
                                            CrankVecBool4 *b,
                                            CrankVecBool4 *r);

void           crank_vec_bool4_orv         (CrankVecBool4 *a,
                                            CrankVecBool4 *b,
                                            CrankVecBool4 *r);

void           crank_vec_bool4_notv        (CrankVecBool4 *a,
                                            CrankVecBool4 *r);




/**
 * CrankVecBoolN:
 * @data: (array length=n): Data of boolean vector.
 * @n: Size of vector.
 *
 * Arbitarily sized boolean vector.
 */
struct _CrankVecBoolN {
  gboolean *data;
  guint n;
};

#define CRANK_TYPE_VEC_BOOL_N   (crank_vec_bool4_get_type ())
GType          crank_vec_bool_n_get_type   (void);


//////// Initialization and finalization ///////////////////////////////////////

void           crank_vec_bool_n_init       (CrankVecBoolN *vec,
                                            const guint    n,
                                            ...);

void           crank_vec_bool_n_init_arr   (CrankVecBoolN *vec,
                                            const guint    n,
                                            gboolean      *arr);

void           crank_vec_bool_n_init_valist (CrankVecBoolN *vec,
                                             const guint    n,
                                             va_list        varargs);

void           crank_vec_bool_n_init_fill  (CrankVecBoolN *vec,
                                            const guint    n,
                                            const gboolean fill);

void           crank_vec_bool_n_fini       (CrankVecBoolN *vec);

void           crank_vec_bool_n_copy       (CrankVecBoolN *vec,
                                            CrankVecBoolN *other);

CrankVecBoolN *crank_vec_bool_n_dup        (CrankVecBoolN *vec);

void           crank_vec_bool_n_free       (CrankVecBoolN *vec);


//////// Basic Operations //////////////////////////////////////////////////////

gboolean       crank_vec_bool_n_equal      (gconstpointer a,
                                            gconstpointer b);

guint          crank_vec_bool_n_hash       (gconstpointer a);

gchar         *crank_vec_bool_n_to_string  (CrankVecBoolN *vec);

gchar         *crank_vec_bool_n_to_string_full (CrankVecBoolN *vec,
                                                const gchar   *left,
                                                const gchar   *in,
                                                const gchar   *right,
                                                const gchar   *on_true,
                                                const gchar   *on_false);

//////// Classification ////////////////////////////////////////////////////////

gboolean       crank_vec_bool_n_is_false (CrankVecBoolN *vec);

gboolean       crank_vec_bool_n_is_true (CrankVecBoolN *vec);

gboolean       crank_vec_bool_n_is_empty (CrankVecBoolN *vec);

//////// Basic Properties //////////////////////////////////////////////////////

gboolean       crank_vec_bool_n_get_any    (CrankVecBoolN *vec);

gboolean       crank_vec_bool_n_get_all    (CrankVecBoolN *vec);

guint          crank_vec_bool_n_get_count  (CrankVecBoolN *vec);

gfloat         crank_vec_bool_n_get_ratio  (CrankVecBoolN *vec);


//////// Functions as collection ///////////////////////////////////////////////

guint          crank_vec_bool_n_get_size   (CrankVecBoolN *vec);

gboolean       crank_vec_bool_n_get        (CrankVecBoolN *vec,
                                            const guint    index);

void           crank_vec_bool_n_set        (CrankVecBoolN *vec,
                                            const guint    index,
                                            const gboolean value);

void           crank_vec_bool_n_prepend    (CrankVecBoolN *vec,
                                            const gboolean value);

void           crank_vec_bool_n_append     (CrankVecBoolN *vec,
                                            const gboolean value);

void           crank_vec_bool_n_insert     (CrankVecBoolN *vec,
                                            const guint    index,
                                            const gboolean value);

void           crank_vec_bool_n_remove     (CrankVecBoolN *vec,
                                            const guint    index);

gboolean       crank_vec_bool_n_foreach    (CrankVecBoolN    *vec,
                                            CrankBoolBoolFunc func,
                                            gpointer          userdata);

void           crank_vec_bool_n_iterator   (CrankVecBoolN    *vec,
                                            CrankIterMemBool *iter);


//////// Vector - Vector Operations ////////////////////////////////////////////

void           crank_vec_bool_n_and        (CrankVecBoolN *a,
                                            CrankVecBoolN *b,
                                            CrankVecBoolN *r);

void           crank_vec_bool_n_and_self   (CrankVecBoolN *a,
                                            CrankVecBoolN *b);

void           crank_vec_bool_n_or         (CrankVecBoolN *a,
                                            CrankVecBoolN *b,
                                            CrankVecBoolN *r);

void           crank_vec_bool_n_or_self    (CrankVecBoolN *a,
                                            CrankVecBoolN *b);

void           crank_vec_bool_n_xor        (CrankVecBoolN *a,
                                            CrankVecBoolN *b,
                                            CrankVecBoolN *r);

void           crank_vec_bool_n_xor_self   (CrankVecBoolN *a,
                                            CrankVecBoolN *b);

void           crank_vec_bool_n_not        (CrankVecBoolN *a,
                                            CrankVecBoolN *r);

void           crank_vec_bool_n_not_self   (CrankVecBoolN *a);



void           crank_vec_bool_n_andv       (CrankVecBoolN *a,
                                            CrankVecBoolN *b,
                                            CrankVecBoolN *r);

void           crank_vec_bool_n_orv        (CrankVecBoolN *a,
                                            CrankVecBoolN *b,
                                            CrankVecBoolN *r);

void           crank_vec_bool_n_notv       (CrankVecBoolN *a,
                                            CrankVecBoolN *r);

G_END_DECLS

#endif //CRANKBOOLVEC_H