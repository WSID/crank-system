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

#define _CRANKBASE_INSIDE

#include <math.h>
#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankfunction.h"
#include "crankiter.h"
#include "crankveccommon.h"
#include "crankvecbool.h"
#include "crankvecint.h"
#include "crankvecfloat.h"
#include "crankmatfloat.h"

/**
 * SECTION: crankvecfloat
 * @title: Float Vectors
 * @short_description: Vectors that have float elements.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Crank System provides 2, 3, 4, and free sized float vectors for convinience.
 *
 * Currently following operations are supported.
 *
 * It is compared to vec in GLSL
 *
 * # Type Conversion.
 *
 * Float vector types are frequently used and can be converted to other types.
 *
 * For fixed-sized types, it can be converted to variadic sized vector types.
 *
 * <table><title>Type Conversion of #CrankVecFloat2</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool2 </entry>
 *             <entry>crank_vec_float2_init_from_vb() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry>From #CrankVecInt2 </entry>
 *             <entry>crank_vec_float2_init_from_vi() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_float2_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_float2_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloatN.</entry>
 *             <entry>crank_vec_float_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecFloatN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecFloat3</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool3 </entry>
 *             <entry>crank_vec_float3_init_from_vb() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry>From #CrankVecInt3 </entry>
 *             <entry>crank_vec_float3_init_from_vi() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_float3_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_float3_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloatN.</entry>
 *             <entry>crank_vec_float_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecFloatN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecFloat4</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool4 </entry>
 *             <entry>crank_vec_float4_init_from_vb() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry>From #CrankVecInt4 </entry>
 *             <entry>crank_vec_float4_init_from_vi() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_float4_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_float4_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloatN.</entry>
 *             <entry>crank_vec_float_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecFloatN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecFloatN</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBoolN </entry>
 *             <entry>crank_vec_float_n_init_from_vb() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry>From #CrankVecIntN </entry>
 *             <entry>crank_vec_float_n_init_from_vi() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry>From #CrankVecFloat2</entry>
 *             <entry>crank_vec_float_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>From #CrankVecFloat3</entry>
 *             <entry>crank_vec_float_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>From #CrankVecFloat4</entry>
 *             <entry>crank_vec_float_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_float_n_to_string()</entry>
 *             <entry>GValue Transform</entry> </row>
 *       <row> <entry>crank_vec_float_n_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecCplxFloatN.</entry>
 *             <entry>crank_vec_cplx_float_n_init_from_vf()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecCplxFloatN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */


const gfloat CRANK_VEC_FLOAT_S0[4] = {0, 0, 0, 0};
const gfloat CRANK_VEC_FLOAT_S1[4] = {1, 1, 1, 1};

const CrankVecFloat2 * const crank_vec_float2_static_zero =
    (const CrankVecFloat2*) CRANK_VEC_FLOAT_S0;
const CrankVecFloat3 * const crank_vec_float3_static_zero =
    (const CrankVecFloat3*) CRANK_VEC_FLOAT_S0;
const CrankVecFloat4 * const crank_vec_float4_static_zero =
    (const CrankVecFloat4*) CRANK_VEC_FLOAT_S0;

const CrankVecFloat2 * const crank_vec_float2_static_one =
    (const CrankVecFloat2*) CRANK_VEC_FLOAT_S1;
const CrankVecFloat3 * const crank_vec_float3_static_one =
    (const CrankVecFloat3*) CRANK_VEC_FLOAT_S1;
const CrankVecFloat4 * const crank_vec_float4_static_one =
    (const CrankVecFloat4*) CRANK_VEC_FLOAT_S1;



#define CMP(a, b) (((a) > (b)) - ((a) < (b)))

static void crank_vec_float2_transform_from_vb (const GValue *src,
                                                GValue       *dest);

static void crank_vec_float2_transform_from_vi (const GValue *src,
                                                GValue       *dest);

static void crank_vec_float2_transform_to_string (const GValue *src,
                                                  GValue       *dest);

G_DEFINE_BOXED_TYPE_WITH_CODE (
  CrankVecFloat2,
  crank_vec_float2,
  crank_vec_float2_dup,
  g_free,
  {
    g_value_register_transform_func (CRANK_TYPE_VEC_BOOL2,
                                     g_define_type_id,
                                     crank_vec_float2_transform_from_vb);

    g_value_register_transform_func (CRANK_TYPE_VEC_INT2,
                                     g_define_type_id,
                                     crank_vec_float2_transform_from_vi);

    g_value_register_transform_func (g_define_type_id,
                                     G_TYPE_STRING,
                                     crank_vec_float2_transform_to_string);
  })

/**
 * crank_vec_float2_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_float2_init (CrankVecFloat2 *vec,
                       const gfloat    x,
                       const gfloat    y)
{
  vec->x = x;
  vec->y = y;
}

/**
 * crank_vec_float2_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=2): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_float2_init_arr (CrankVecFloat2 *vec,
                           const gfloat   *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
}

/**
 * crank_vec_float2_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_float2_init_valist (CrankVecFloat2 *vec,
                              va_list         varargs)
{
  vec->x = va_arg (varargs, gdouble);
  vec->y = va_arg (varargs, gdouble);
}

/**
 * crank_vec_float2_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_float2_init_fill (CrankVecFloat2 *vec,
                            gfloat          fill)
{
  vec->x = fill;
  vec->y = fill;
}

/**
 * crank_vec_float2_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_float2_init_from_vb (CrankVecFloat2      *vec,
                               const CrankVecBool2 *vb)
{
  vec->x = vb->x ? 1 : 0;
  vec->y = vb->y ? 1 : 0;
}

/**
 * crank_vec_float2_init_from_vi:
 * @vec: (out): Vector to initialize.
 * @vi: Integer vector.
 *
 * Initialize vector from integer vector.
 */
void
crank_vec_float2_init_from_vi (CrankVecFloat2     *vec,
                               const CrankVecInt2 *vi)
{
  vec->x = vi->x;
  vec->y = vi->y;
}


/**
 * crank_vec_float2_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_float2_copy (const CrankVecFloat2 *vec,
                       CrankVecFloat2       *other)
{
  memcpy (other, vec, sizeof(CrankVecFloat2));
}

/**
 * crank_vec_float2_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecFloat2*
crank_vec_float2_dup (const CrankVecFloat2 *vec)
{
  return (CrankVecFloat2*) g_memdup (vec, sizeof (CrankVecFloat2));
}

/**
 * crank_vec_float2_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
gfloat
crank_vec_float2_get (const CrankVecFloat2 *vec,
                      const guint           index)
{
  return ((gfloat*)vec)[index];
}

/**
 * crank_vec_float2_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_float2_set (CrankVecFloat2 *vec,
                      const guint     index,
                      const gfloat    value)
{
  ((gfloat*)vec)[index] = value;
}

/**
 * crank_vec_float2_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a float vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_float2_foreach (const CrankVecFloat2 *vec,
                          CrankBoolFloatFunc    func,
                          gpointer              userdata)
{
  if (func (vec->x, userdata) &&
      func (vec->y, userdata))
    return TRUE;
  else
    return FALSE;
}

/**
 * crank_vec_float2_iterator:
 * @vec: A Vector
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_float2_iterator (CrankVecFloat2    *vec,
                           CrankIterMemFloat *iter)
{
  crank_iter_mem_float_init_with_count (iter, (gfloat*)vec, 2);
}

//////// Basic operation ////////

/**
 * crank_vec_float2_hash:
 * @a: (type CrankVecFloat2): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_float2_hash (gconstpointer a)
{
  const CrankVecFloat2 *vec = a;

  guint hash;
  hash = crank_float_hash (&(vec->x));
  hash = crank_float_hash (&(vec->y)) + hash * 37;
  return hash;
}

/**
 * crank_vec_float2_equal:
 * @a: (type CrankVecFloat2): Vector to compare.
 * @b: (type CrankVecFloat2): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_float2_equal (gconstpointer a,
                        gconstpointer b)
{
  CrankVecFloat2 *veca = (CrankVecFloat2*)a;
  CrankVecFloat2 *vecb = (CrankVecFloat2*)b;

  return ((veca->x == vecb->x) &&
          (veca->y == vecb->y));
}

/**
 * crank_vec_float2_equal_delta:
 * @a: (type CrankVecFloat2): Vector to compare.
 * @b: (type CrankVecFloat2): Vector to compare.
 * @d: Allowed difference to be considered equal.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_float2_equal_delta (gconstpointer a,
                              gconstpointer b,
                              const gfloat  d)
{
  CrankVecFloat2 *veca = (CrankVecFloat2*)a;
  CrankVecFloat2 *vecb = (CrankVecFloat2*)b;

  CrankVecFloat2 vecd;
  gfloat         dm;
  gfloat         dd;

  crank_vec_float2_sub (vecb, veca, &vecd);

  dm = crank_vec_float2_get_magn_sq (&vecd);
  dd = d * d;

  return (dm < dd);
}

/**
 * crank_vec_float2_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_float2_to_string (const CrankVecFloat2 *vec)
{
  return crank_vec_float2_to_string_full (vec, "(", ", ", ")", "%g");
}

/**
 * crank_vec_float2_to_string_full:
 * @vec: Vector to string.
 * @left: Left string, which indicates that vector's start.
 * @in: Delimiter, which is inserted between elements.
 * @right: Right string. which indicates that vector's end.
 * @format: Format to use with elements.
 *
 * Construct string from vector, with given format.
 *
 * Returns: (transfer full): stringified items of value.
 */
gchar*
crank_vec_float2_to_string_full (const CrankVecFloat2 *vec,
                                 const gchar    *left,
                                 const gchar    *in,
                                 const gchar    *right,
                                 const gchar    *format)
{
  GString *strb = g_string_new (left);
  gchar *result;

  g_string_append_printf (strb, format, vec->x);
  g_string_append (strb, in);

  g_string_append_printf (strb, format, vec->y);
  g_string_append (strb, right);

  result = strb->str;

  g_string_free (strb, FALSE);

  return result;
}


//////// Standard vector property ///////

/**
 * crank_vec_float2_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
gfloat
crank_vec_float2_get_magn_sq (const CrankVecFloat2 *vec)
{
  return (vec->x * vec->x) +
         (vec->y * vec->y);
}

/**
 * crank_vec_float2_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_float2_get_magn (const CrankVecFloat2 *vec)
{
  gfloat sq = crank_vec_float2_get_magn_sq (vec);
  return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_float2_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_float2_neg (const CrankVecFloat2 *a,
                      CrankVecFloat2       *r)
{
  r->x = -(a->x);
  r->y = -(a->y);
}


/**
 * crank_vec_float2_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_float2_neg_self (CrankVecFloat2 *a)
{
  a->x = -(a->x);
  a->y = -(a->y);
}


/**
 * crank_vec_float2_unit:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float2_unit (const CrankVecFloat2 *a,
                       CrankVecFloat2       *r)
{
  crank_vec_float2_divs (a, crank_vec_float2_get_magn (a), r);
}


/**
 * crank_vec_float2_unit_self:
 * @a: A vector
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float2_unit_self (CrankVecFloat2 *a)
{
  crank_vec_float2_divs_self (a, crank_vec_float2_get_magn (a));
}

//////// Scalar operations ////////

/**
 * crank_vec_float2_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_float2_muls (const CrankVecFloat2 *a,
                       const gfloat          b,
                       CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);

  r->x = a->x * b;
  r->y = a->y * b;
}

/**
 * crank_vec_float2_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_float2_muls_self (CrankVecFloat2 *a,
                            const gfloat    b)
{
  a->x *= b;
  a->y *= b;
}

/**
 * crank_vec_float2_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_float2_divs (const CrankVecFloat2 *a,
                       const gfloat          b,
                       CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);

  r->x = a->x / b;
  r->y = a->y / b;
}

/**
 * crank_vec_float2_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_float2_divs_self (CrankVecFloat2 *a,
                            const gfloat    b)
{
  a->x /= b;
  a->y /= b;
}


//////// Standard vector operations ////////

/**
 * crank_vec_float2_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_float2_add (const CrankVecFloat2 *a,
                      const CrankVecFloat2 *b,
                      CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x + b->x;
  r->y = a->y + b->y;
}

/**
 * crank_vec_float2_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_float2_add_self (CrankVecFloat2       *a,
                           const CrankVecFloat2 *b)
{
  a->x += b->x;
  a->y += b->y;
}

/**
 * crank_vec_float2_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_float2_sub (const CrankVecFloat2 *a,
                      const CrankVecFloat2 *b,
                      CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x - b->x;
  r->y = a->y - b->y;
}

/**
 * crank_vec_float2_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_float2_sub_self (CrankVecFloat2       *a,
                           const CrankVecFloat2 *b)
{
  a->x -= b->x;
  a->y -= b->y;
}

/**
 * crank_vec_float2_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
gfloat
crank_vec_float2_dot (const CrankVecFloat2 *a,
                      const CrankVecFloat2 *b)
{
  return (a->x) * (b->x) + (a->y) * (b->y);
}

/**
 * crank_vec_float2_crs:
 * @a: A vector
 * @b: A vector
 *
 * Gets Z component of cross product of two vectors.
 *
 * Returns: Cross product of two vectors, as scalar.
 */
gfloat
crank_vec_float2_crs (const CrankVecFloat2 *a,
                      const CrankVecFloat2 *b)
{
  return (a->x) * (b->y) - (a->y) * (b->x);
}

//////// Component vector operations ////////

/**
 * crank_vec_float2_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_float2_cmpmul (const CrankVecFloat2 *a,
                         const CrankVecFloat2 *b,
                         CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x * b->x;
  r->y = a->y * b->y;
}

/**
 * crank_vec_float2_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_float2_cmpmul_self (CrankVecFloat2       *a,
                              const CrankVecFloat2 *b)
{
  a->x *= b->x;
  a->y *= b->y;
}

/**
 * crank_vec_float2_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise division.
 */
void
crank_vec_float2_cmpdiv (const CrankVecFloat2 *a,
                         const CrankVecFloat2 *b,
                         CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x / b->x;
  r->y = a->y / b->y;
}

/**
 * crank_vec_float2_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise division.
 */
void
crank_vec_float2_cmpdiv_self (CrankVecFloat2       *a,
                              const CrankVecFloat2 *b)
{
  a->x /= b->x;
  a->y /= b->y;
}

/**
 * crank_vec_float2_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_float2_cmpless (const CrankVecFloat2 *a,
                          const CrankVecFloat2 *b,
                          CrankVecBool2        *r)
{
  r->x = (a->x) < (b->x);
  r->y = (a->y) < (b->y);
}

/**
 * crank_vec_float2_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_float2_cmpeq (const CrankVecFloat2 *a,
                        const CrankVecFloat2 *b,
                        CrankVecBool2        *r)
{
  r->x = (a->x) == (b->x);
  r->y = (a->y) == (b->y);
}

/**
 * crank_vec_float2_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is greater than counterpart of @b
 */
void
crank_vec_float2_cmpgreater (const CrankVecFloat2 *a,
                             const CrankVecFloat2 *b,
                             CrankVecBool2        *r)
{
  r->x = (a->x) > (b->x);
  r->y = (a->y) > (b->y);
}

/**
 * crank_vec_float2_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets compare result of each components.
 */
void
crank_vec_float2_cmpcmp (const CrankVecFloat2 *a,
                         const CrankVecFloat2 *b,
                         CrankVecInt2         *r)
{
  r->x = CMP(a->x, b->x);
  r->y = CMP(a->y, b->y);
}

/**
 * crank_vec_float2_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_float2_min (const CrankVecFloat2 *a,
                      const CrankVecFloat2 *b,
                      CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MIN (a->x, b->x);
  r->y = MIN (a->y, b->y);
}

/**
 * crank_vec_float2_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_float2_max (const CrankVecFloat2 *a,
                      const CrankVecFloat2 *b,
                      CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MAX (a->x, b->x);
  r->y = MAX (a->y, b->y);
}

/**
 * crank_vec_float2_abs:
 * @a: A Vector.
 * @r: (out): A vector to store result.
 *
 * Gets absolute value of each components.
 */
void
crank_vec_float2_abs (const CrankVecFloat2 *a,
                      CrankVecFloat2       *r)
{
  g_return_if_fail (a != r);

  r->x = ABS (a->x);
  r->y = ABS (a->y);
}


/**
 * crank_vec_float2_abs_self:
 * @a: A Vector.
 *
 * Applys absolute value of each components.
 */
void
crank_vec_float2_abs_self (CrankVecFloat2 *a)
{
  a->x = ABS (a->x);
  a->y = ABS (a->y);
}

/**
 * crank_vec_float2_mulm:
 * @a: A Vector
 * @b: A Matrix
 * @r: (out): A Vector to store result.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_float2_mulm (const CrankVecFloat2 *a,
                       const CrankMatFloat2 *b,
                       CrankVecFloat2       *r)
{
  gfloat nx, ny;

  g_return_if_fail (a != r);

  nx = (a->x * b->m00) + (a->y * b->m10);
  ny = (a->x * b->m01) + (a->y * b->m11);

  r->x = nx;
  r->y = ny;
}


/**
 * crank_vec_float2_mulm_self:
 * @a: A Vector
 * @b: A Matrix
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_float2_mulm_self (CrankVecFloat2       *a,
                            const CrankMatFloat2 *b)
{
  gfloat nx, ny;

  nx = (a->x * b->m00) + (a->y * b->m10);
  ny = (a->x * b->m01) + (a->y * b->m11);

  a->x = nx;
  a->y = ny;
}

/**
 * crank_vec_float2_mixs:
 * @a: A vector.
 * @b: A vector.
 * @c: A scalar factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a * (1-c)) + (b * c)
 */
void
crank_vec_float2_mixs (const CrankVecFloat2 *a,
                       const CrankVecFloat2 *b,
                       const gfloat          c,
                       CrankVecFloat2       *r)
{
  gfloat d = 1.0f - c;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x * d + b->x * c;
  r->y = a->y * d + b->y * c;
}


/**
 * crank_vec_float2_mix:
 * @a: A vector.
 * @b: A vector.
 * @c: A factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a cmpmul c) + (b cmpmul ({1, 1} - c))
 */
void
crank_vec_float2_mix (const CrankVecFloat2 *a,
                      const CrankVecFloat2 *b,
                      const CrankVecFloat2 *c,
                      CrankVecFloat2       *r)
{
  CrankVecFloat2 d;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  g_return_if_fail (c != r);

  d.x = 1.0f - c->x;
  d.y = 1.0f - c->y;

  r->x = a->x * d.x + b->x * c->x;
  r->y = a->y * d.y + b->y * c->y;
}

//////// GValue Transform //////////////////////////////////////////////////////

static void
crank_vec_float2_transform_from_vb (const GValue *src,
                                    GValue       *dest)
{
  CrankVecFloat2 *vf = g_new (CrankVecFloat2, 1);
  CrankVecBool2 *vb = (CrankVecBool2*) g_value_get_boxed (src);

  crank_vec_float2_init_from_vb (vf, vb);

  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float2_transform_from_vi (const GValue *src,
                                    GValue       *dest)
{
  CrankVecFloat2 *vf = g_new (CrankVecFloat2, 1);
  CrankVecInt2 *vi = (CrankVecInt2*) g_value_get_boxed (src);

  crank_vec_float2_init_from_vi (vf, vi);

  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float2_transform_to_string (const GValue *src,
                                      GValue       *dest)
{
  CrankVecFloat2 *vf = (CrankVecFloat2*) g_value_get_boxed (src);
  gchar *res = crank_vec_float2_to_string (vf);
  g_value_take_string (dest, res);
}







static void crank_vec_float3_transform_from_vb (const GValue *src,
                                                GValue       *dest);

static void crank_vec_float3_transform_from_vi (const GValue *src,
                                                GValue       *dest);

static void crank_vec_float3_transform_to_string (const GValue *src,
                                                  GValue       *dest);

G_DEFINE_BOXED_TYPE_WITH_CODE (
  CrankVecFloat3,
  crank_vec_float3,
  crank_vec_float3_dup,
  g_free,
  {
    g_value_register_transform_func (CRANK_TYPE_VEC_BOOL3,
                                     g_define_type_id,
                                     crank_vec_float3_transform_from_vb);

    g_value_register_transform_func (CRANK_TYPE_VEC_INT3,
                                     g_define_type_id,
                                     crank_vec_float3_transform_from_vi);

    g_value_register_transform_func (g_define_type_id,
                                     G_TYPE_STRING,
                                     crank_vec_float3_transform_to_string);
  })

/**
 * crank_vec_float3_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_float3_init (CrankVecFloat3 *vec,
                       const gfloat    x,
                       const gfloat    y,
                       const gfloat    z)
{
  vec->x = x;
  vec->y = y;
  vec->z = z;
}

/**
 * crank_vec_float3_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=3): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_float3_init_arr (CrankVecFloat3 *vec,
                           const gfloat   *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
  vec->z = arr[2];
}

/**
 * crank_vec_float3_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_float3_init_valist (CrankVecFloat3 *vec,
                              va_list         varargs)
{
  vec->x = va_arg (varargs, gdouble);
  vec->y = va_arg (varargs, gdouble);
  vec->z = va_arg (varargs, gdouble);
}

/**
 * crank_vec_float3_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_float3_init_fill (CrankVecFloat3 *vec,
                            const gfloat    fill)
{
  vec->x = fill;
  vec->y = fill;
  vec->z = fill;
}

/**
 * crank_vec_float3_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_float3_init_from_vb (CrankVecFloat3      *vec,
                               const CrankVecBool3 *vb)
{
  vec->x = vb->x ? 1 : 0;
  vec->y = vb->y ? 1 : 0;
  vec->z = vb->z ? 1 : 0;
}

/**
 * crank_vec_float3_init_from_vi:
 * @vec: (out): Vector to initialize.
 * @vi: Integer vector.
 *
 * Initialize vector from integer vector.
 */
void
crank_vec_float3_init_from_vi (CrankVecFloat3     *vec,
                               const CrankVecInt3 *vi)
{
  vec->x = vi->x;
  vec->y = vi->y;
  vec->z = vi->z;
}


/**
 * crank_vec_float3_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_float3_copy (const CrankVecFloat3 *vec,
                       CrankVecFloat3       *other)
{
  memcpy (other, vec, sizeof(CrankVecFloat3));
}

/**
 * crank_vec_float3_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecFloat3*
crank_vec_float3_dup (const CrankVecFloat3 *vec)
{
  return (CrankVecFloat3*) g_memdup (vec, sizeof (CrankVecFloat3));
}

/**
 * crank_vec_float3_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
gfloat
crank_vec_float3_get (const CrankVecFloat3 *vec,
                      const guint           index)
{
  return ((gfloat*)vec)[index];
}

/**
 * crank_vec_float3_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_float3_set (CrankVecFloat3 *vec,
                      const guint     index,
                      const gfloat    value)
{
  ((gfloat*)vec)[index] = value;
}

/**
 * crank_vec_float3_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a float vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_float3_foreach (const CrankVecFloat3 *vec,
                          CrankBoolFloatFunc    func,
                          gpointer              userdata)
{
  if (func (vec->x, userdata) &&
      func (vec->y, userdata) &&
      func (vec->z, userdata))
    return TRUE;
  else
    return FALSE;
}

/**
 * crank_vec_float3_iterator:
 * @vec: A Vector
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_float3_iterator (CrankVecFloat3    *vec,
                           CrankIterMemFloat *iter)
{
  crank_iter_mem_float_init_with_count (iter, (gfloat*)vec, 3);
}


//////// Basic operation ////////

/**
 * crank_vec_float3_hash:
 * @a: (type CrankVecFloat3): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_float3_hash (gconstpointer a)
{
  const CrankVecFloat3 *vec = a;
  guint hash;
  hash = crank_float_hash (&(vec->x));
  hash = crank_float_hash (&(vec->y)) + hash * 37;
  hash = crank_float_hash (&(vec->z)) + hash * 37;

  return hash;
}

/**
 * crank_vec_float3_equal:
 * @a: (type CrankVecFloat3): Vector to compare.
 * @b: (type CrankVecFloat3): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_float3_equal (gconstpointer a,
                        gconstpointer b)
{
  CrankVecFloat3 *veca = (CrankVecFloat3*)a;
  CrankVecFloat3 *vecb = (CrankVecFloat3*)b;

  return ((veca->x == vecb->x) &&
          (veca->y == vecb->y) &&
          (veca->z == vecb->z));
}

/**
 * crank_vec_float3_equal_delta:
 * @a: (type CrankVecFloat3): Vector to compare.
 * @b: (type CrankVecFloat3): Vector to compare.
 * @d: Allowed difference to be considered equal.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_float3_equal_delta (gconstpointer a,
                              gconstpointer b,
                              const gfloat  d)
{
  CrankVecFloat3 *veca = (CrankVecFloat3*)a;
  CrankVecFloat3 *vecb = (CrankVecFloat3*)b;

  CrankVecFloat3 vecd;
  gfloat         dm;
  gfloat         dd;

  crank_vec_float3_sub (vecb, veca, &vecd);

  dm = crank_vec_float3_get_magn_sq (&vecd);
  dd = d * d;

  return (dm < dd);
}

/**
 * crank_vec_float3_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_float3_to_string (const CrankVecFloat3 *vec)
{
  return crank_vec_float3_to_string_full (vec, "(", ", ", ")", "%g");
}

/**
 * crank_vec_float3_to_string_full:
 * @vec: Vector to string.
 * @left: Left string, which indicates that vector's start.
 * @in: Delimiter, which is inserted between elements.
 * @right: Right string. which indicates that vector's end.
 * @format: Format to use with elements.
 *
 * Construct string from vector, with given format.
 *
 * Returns: (transfer full): stringified items of value.
 */
gchar*
crank_vec_float3_to_string_full (const CrankVecFloat3 *vec,
                                 const gchar          *left,
                                 const gchar          *in,
                                 const gchar          *right,
                                 const gchar          *format)
{
  GString *strb = g_string_new (left);
  gchar *result;

  g_string_append_printf (strb, format, vec->x);
  g_string_append (strb, in);

  g_string_append_printf (strb, format, vec->y);
  g_string_append (strb, in);

  g_string_append_printf (strb, format, vec->z);
  g_string_append (strb, right);

  result = strb->str;

  g_string_free (strb, FALSE);

  return result;
}


//////// Standard vector property ///////

/**
 * crank_vec_float3_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
gfloat
crank_vec_float3_get_magn_sq (const CrankVecFloat3 *vec)
{
  return (vec->x * vec->x) +
         (vec->y * vec->y) +
         (vec->z * vec->z);
}

/**
 * crank_vec_float3_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_float3_get_magn (const CrankVecFloat3 *vec)
{
  gfloat sq = crank_vec_float3_get_magn_sq (vec);
  return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_float3_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_float3_neg (const CrankVecFloat3 *a,
                      CrankVecFloat3       *r)
{
  r->x = -(a->x);
  r->y = -(a->y);
  r->z = -(a->z);
}

/**
 * crank_vec_float3_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_float3_neg_self (CrankVecFloat3 *a)
{
  a->x = -(a->x);
  a->y = -(a->y);
  a->z = -(a->z);
}

/**
 * crank_vec_float3_unit:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float3_unit (const CrankVecFloat3 *a,
                       CrankVecFloat3       *r)
{
  crank_vec_float3_divs (a, crank_vec_float3_get_magn (a), r);
}

/**
 * crank_vec_float3_unit_self:
 * @a: A vector
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float3_unit_self (CrankVecFloat3 *a)
{
  crank_vec_float3_divs_self (a, crank_vec_float3_get_magn (a));
}


//////// Scalar operations ////////

/**
 * crank_vec_float3_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_float3_muls (const CrankVecFloat3 *a,
                       const gfloat          b,
                       CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);

  r->x = a->x * b;
  r->y = a->y * b;
  r->z = a->z * b;
}

/**
 * crank_vec_float3_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_float3_muls_self (CrankVecFloat3 *a,
                            const gfloat    b)
{
  a->x *= b;
  a->y *= b;
  a->z *= b;
}

/**
 * crank_vec_float3_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_float3_divs (const CrankVecFloat3 *a,
                       const gfloat          b,
                       CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);

  r->x = a->x / b;
  r->y = a->y / b;
  r->z = a->z / b;
}

/**
 * crank_vec_float3_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_float3_divs_self (CrankVecFloat3 *a,
                            const gfloat    b)
{
  a->x /= b;
  a->y /= b;
  a->z /= b;
}


//////// Standard vector operations ////////

/**
 * crank_vec_float3_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_float3_add (const CrankVecFloat3 *a,
                      const CrankVecFloat3 *b,
                      CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x + b->x;
  r->y = a->y + b->y;
  r->z = a->z + b->z;
}

/**
 * crank_vec_float3_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_float3_add_self (CrankVecFloat3       *a,
                           const CrankVecFloat3 *b)
{
  a->x += b->x;
  a->y += b->y;
  a->z += b->z;
}

/**
 * crank_vec_float3_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_float3_sub (const CrankVecFloat3 *a,
                      const CrankVecFloat3 *b,
                      CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x - b->x;
  r->y = a->y - b->y;
  r->z = a->z - b->z;
}

/**
 * crank_vec_float3_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_float3_sub_self (CrankVecFloat3       *a,
                           const CrankVecFloat3 *b)
{
  a->x -= b->x;
  a->y -= b->y;
  a->z -= b->z;
}

/**
 * crank_vec_float3_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
gfloat
crank_vec_float3_dot (const CrankVecFloat3 *a,
                      const CrankVecFloat3 *b)
{
  return (a->x) * (b->x) + (a->y) * (b->y) + (a->z) * (b->z);
}

/**
 * crank_vec_float3_crs:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Get cross product of two vectors.
 */
void
crank_vec_float3_crs (const CrankVecFloat3 *a,
                      const CrankVecFloat3 *b,
                      CrankVecFloat3       *r)
{
  gfloat nx;
  gfloat ny;
  gfloat nz;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  nx = (a->y * b->z) - (a->z * b->y);
  ny = (a->z * b->x) - (a->x * b->z);
  nz = (a->x * b->y) - (a->y * b->x);

  r->x = nx;
  r->y = ny;
  r->z = nz;
}

/**
 * crank_vec_float3_crs_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Get cross product of two vectors.
 */
void
crank_vec_float3_crs_self (CrankVecFloat3       *a,
                           const CrankVecFloat3 *b)
{
  gfloat nx = (a->y * b->z) - (a->z * b->y);
  gfloat ny = (a->z * b->x) - (a->x * b->z);
  gfloat nz = (a->x * b->y) - (a->y * b->x);

  a->x = nx;
  a->y = ny;
  a->z = nz;
}

//////// Component vector operations ////////

/**
 * crank_vec_float3_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_float3_cmpmul (const CrankVecFloat3 *a,
                         const CrankVecFloat3 *b,
                         CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x * b->x;
  r->y = a->y * b->y;
  r->z = a->z * b->z;
}

/**
 * crank_vec_float3_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_float3_cmpmul_self (CrankVecFloat3       *a,
                              const CrankVecFloat3 *b)
{
  a->x *= b->x;
  a->y *= b->y;
  a->z *= b->z;
}

/**
 * crank_vec_float3_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise division.
 */
void
crank_vec_float3_cmpdiv (const CrankVecFloat3 *a,
                         const CrankVecFloat3 *b,
                         CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x / b->x;
  r->y = a->y / b->y;
  r->z = a->z / b->z;
}

/**
 * crank_vec_float3_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise division.
 */
void
crank_vec_float3_cmpdiv_self (CrankVecFloat3       *a,
                              const CrankVecFloat3 *b)
{
  a->x /= b->x;
  a->y /= b->y;
  a->z /= b->z;
}

/**
 * crank_vec_float3_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_float3_cmpless (const CrankVecFloat3 *a,
                          const CrankVecFloat3 *b,
                          CrankVecBool3        *r)
{
  r->x = (a->x) < (b->x);
  r->y = (a->y) < (b->y);
  r->z = (a->z) < (b->z);
}

/**
 * crank_vec_float3_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_float3_cmpeq (const CrankVecFloat3 *a,
                        const CrankVecFloat3 *b,
                        CrankVecBool3        *r)
{
  r->x = (a->x) == (b->x);
  r->y = (a->y) == (b->y);
  r->z = (a->z) == (b->z);
}

/**
 * crank_vec_float3_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is greater than counterpart of @b
 */
void
crank_vec_float3_cmpgreater (const CrankVecFloat3 *a,
                             const CrankVecFloat3 *b,
                             CrankVecBool3        *r)
{
  r->x = (a->x) > (b->x);
  r->y = (a->y) > (b->y);
  r->z = (a->z) > (b->z);
}

/**
 * crank_vec_float3_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets compare result of each components.
 */
void
crank_vec_float3_cmpcmp (const CrankVecFloat3 *a,
                         const CrankVecFloat3 *b,
                         CrankVecInt3         *r)
{
  r->x = CMP(a->x, b->x);
  r->y = CMP(a->y, b->y);
  r->z = CMP(a->z, b->z);
}

/**
 * crank_vec_float3_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_float3_min (const CrankVecFloat3 *a,
                      const CrankVecFloat3 *b,
                      CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MIN (a->x, b->x);
  r->y = MIN (a->y, b->y);
  r->z = MIN (a->z, b->z);
}

/**
 * crank_vec_float3_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_float3_max (const CrankVecFloat3 *a,
                      const CrankVecFloat3 *b,
                      CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MAX (a->x, b->x);
  r->y = MAX (a->y, b->y);
  r->z = MAX (a->z, b->z);
}

/**
 * crank_vec_float3_abs:
 * @a: A Vector.
 * @r: (out): A vector to store result.
 *
 * Gets absolute value of each components.
 */
void
crank_vec_float3_abs (const CrankVecFloat3 *a,
                      CrankVecFloat3       *r)
{
  g_return_if_fail (a != r);

  r->x = ABS (a->x);
  r->y = ABS (a->y);
  r->z = ABS (a->z);
}


/**
 * crank_vec_float3_abs_self:
 * @a: A Vector.
 *
 * Applys absolute value of each components.
 */
void
crank_vec_float3_abs_self (CrankVecFloat3 *a)
{
  a->x = ABS (a->x);
  a->y = ABS (a->y);
  a->z = ABS (a->z);
}

/**
 * crank_vec_float3_mulm:
 * @a: A Vector
 * @b: A Matrix
 * @r: (out): A Vector to store result.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_float3_mulm (const CrankVecFloat3 *a,
                       const CrankMatFloat3 *b,
                       CrankVecFloat3       *r)
{
  gfloat nx, ny, nz;

  g_return_if_fail (a != r);

  nx = (a->x * b->m00) + (a->y * b->m10) + (a->z * b->m20);
  ny = (a->x * b->m01) + (a->y * b->m11) + (a->z * b->m21);
  nz = (a->x * b->m02) + (a->y * b->m12) + (a->z * b->m22);

  r->x = nx;
  r->y = ny;
  r->z = nz;
}

/**
 * crank_vec_float3_mulm_self:
 * @a: A Vector
 * @b: A Matrix
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_float3_mulm_self (CrankVecFloat3       *a,
                            const CrankMatFloat3 *b)
{
  gfloat nx, ny, nz;

  nx = (a->x * b->m00) + (a->y * b->m10) + (a->z * b->m20);
  ny = (a->x * b->m01) + (a->y * b->m11) + (a->z * b->m21);
  nz = (a->x * b->m02) + (a->y * b->m12) + (a->z * b->m22);

  a->x = nx;
  a->y = ny;
  a->z = nz;
}


/**
 * crank_vec_float3_mixs:
 * @a: A vector.
 * @b: A vector.
 * @c: A scalar factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a * (1-c)) + (b * c)
 */
void
crank_vec_float3_mixs (const CrankVecFloat3 *a,
                       const CrankVecFloat3 *b,
                       const gfloat          c,
                       CrankVecFloat3       *r)
{
  gfloat d;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  d = 1.0f - c;

  r->x = a->x * d + b->x * c;
  r->y = a->y * d + b->y * c;
  r->z = a->z * d + b->z * c;
}


/**
 * crank_vec_float3_mix:
 * @a: A vector.
 * @b: A vector.
 * @c: A factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a cmpmul c) + (b cmpmul ({1, 1, 1} - c))
 */
void
crank_vec_float3_mix (const CrankVecFloat3 *a,
                      const CrankVecFloat3 *b,
                      const CrankVecFloat3 *c,
                      CrankVecFloat3       *r)
{
  CrankVecFloat3 d;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  g_return_if_fail (c != r);

  d.x = 1.0f - c->x;
  d.y = 1.0f - c->y;
  d.z = 1.0f - c->z;

  r->x = a->x * d.x + b->x * c->x;
  r->y = a->y * d.y + b->y * c->y;
  r->z = a->z * d.z + b->z * c->z;
}

//////// GValue Transform //////////////////////////////////////////////////////

static void
crank_vec_float3_transform_from_vb (const GValue *src,
                                    GValue       *dest)
{
  CrankVecFloat3 *vf = g_new (CrankVecFloat3, 1);
  CrankVecBool3 *vb = (CrankVecBool3*) g_value_get_boxed (src);

  crank_vec_float3_init_from_vb (vf, vb);

  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float3_transform_from_vi (const GValue *src,
                                    GValue       *dest)
{
  CrankVecFloat3 *vf = g_new (CrankVecFloat3, 1);
  CrankVecInt3 *vi = (CrankVecInt3*) g_value_get_boxed (src);

  crank_vec_float3_init_from_vi (vf, vi);

  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float3_transform_to_string (const GValue *src,
                                      GValue       *dest)
{
  CrankVecFloat3 *vf = (CrankVecFloat3*) g_value_get_boxed (src);
  gchar *str = crank_vec_float3_to_string (vf);

  g_value_take_string (dest, str);
}






static void crank_vec_float4_transform_from_vb (const GValue *src,
                                                GValue       *dest);

static void crank_vec_float4_transform_from_vi (const GValue *src,
                                                GValue       *dest);

static void crank_vec_float4_transform_to_string (const GValue *src,
                                                  GValue       *dest);

G_DEFINE_BOXED_TYPE_WITH_CODE (
  CrankVecFloat4,
  crank_vec_float4,
  crank_vec_float4_dup,
  g_free,
  {
    g_value_register_transform_func (CRANK_TYPE_VEC_BOOL4,
                                     g_define_type_id,
                                     crank_vec_float4_transform_from_vb);

    g_value_register_transform_func (CRANK_TYPE_VEC_INT4,
                                     g_define_type_id,
                                     crank_vec_float4_transform_from_vi);

    g_value_register_transform_func (g_define_type_id,
                                     G_TYPE_STRING,
                                     crank_vec_float4_transform_to_string);
  })

/**
 * crank_vec_float4_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 * @w: Fourth vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_float4_init (CrankVecFloat4 *vec,
                       const gfloat    x,
                       const gfloat    y,
                       const gfloat    z,
                       const gfloat    w)
{
  vec->x = x;
  vec->y = y;
  vec->z = z;
  vec->w = w;
}

/**
 * crank_vec_float4_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=3): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_float4_init_arr (CrankVecFloat4 *vec,
                           const gfloat   *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
  vec->z = arr[2];
  vec->w = arr[3];
}

/**
 * crank_vec_float4_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_float4_init_valist (CrankVecFloat4 *vec,
                              va_list         varargs)
{
  vec->x = va_arg (varargs, gdouble);
  vec->y = va_arg (varargs, gdouble);
  vec->z = va_arg (varargs, gdouble);
  vec->w = va_arg (varargs, gdouble);
}

/**
 * crank_vec_float4_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_float4_init_fill (CrankVecFloat4 *vec,
                            const gfloat    fill)
{
  vec->x = fill;
  vec->y = fill;
  vec->z = fill;
  vec->w = fill;
}

/**
 * crank_vec_float4_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_float4_init_from_vb (CrankVecFloat4      *vec,
                               const CrankVecBool4 *vb)
{
  vec->x = vb->x ? 1 : 0;
  vec->y = vb->y ? 1 : 0;
  vec->z = vb->z ? 1 : 0;
  vec->w = vb->w ? 1 : 0;
}

/**
 * crank_vec_float4_init_from_vi:
 * @vec: (out): Vector to initialize.
 * @vi: Integer vector.
 *
 * Initialize vector from integer vector.
 */
void
crank_vec_float4_init_from_vi (CrankVecFloat4     *vec,
                               const CrankVecInt4 *vi)
{
  vec->x = vi->x;
  vec->y = vi->y;
  vec->z = vi->z;
  vec->w = vi->w;
}


/**
 * crank_vec_float4_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_float4_copy (const CrankVecFloat4 *vec,
                       CrankVecFloat4       *other)
{
  memcpy (other, vec, sizeof(CrankVecFloat4));
}

/**
 * crank_vec_float4_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecFloat4*
crank_vec_float4_dup (const CrankVecFloat4 *vec)
{
  return (CrankVecFloat4*) g_memdup (vec, sizeof (CrankVecFloat4));
}

/**
 * crank_vec_float4_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
gfloat
crank_vec_float4_get (const CrankVecFloat4 *vec,
                      const guint           index)
{
  return ((gfloat*)vec)[index];
}

/**
 * crank_vec_float4_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_float4_set (CrankVecFloat4 *vec,
                      const guint     index,
                      const gfloat    value)
{
  ((gfloat*)vec)[index] = value;
}

/**
 * crank_vec_float4_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a float vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_float4_foreach (const CrankVecFloat4 *vec,
                          CrankBoolFloatFunc    func,
                          gpointer              userdata)
{
  if (func (vec->x, userdata) &&
      func (vec->y, userdata) &&
      func (vec->z, userdata) &&
      func (vec->w, userdata))
    return TRUE;
  else
    return FALSE;
}

/**
 * crank_vec_float4_iterator:
 * @vec: A Vector
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_float4_iterator (CrankVecFloat4    *vec,
                           CrankIterMemFloat *iter)
{
  crank_iter_mem_float_init_with_count (iter, (gfloat*)vec, 4);
}


//////// Basic operation ////////

/**
 * crank_vec_float4_hash:
 * @a: (type CrankVecFloat4): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_float4_hash (gconstpointer a)
{
  const CrankVecFloat4 *vec = a;

  guint hash;
  hash = crank_float_hash (&(vec->x));
  hash = crank_float_hash (&(vec->y)) + hash * 37;
  hash = crank_float_hash (&(vec->z)) + hash * 37;
  hash = crank_float_hash (&(vec->w)) + hash * 37;

  return hash;
}

/**
 * crank_vec_float4_equal:
 * @a: (type CrankVecFloat4): Vector to compare.
 * @b: (type CrankVecFloat4): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_float4_equal (gconstpointer a,
                        gconstpointer b)
{
  CrankVecFloat4 *veca = (CrankVecFloat4*)a;
  CrankVecFloat4 *vecb = (CrankVecFloat4*)b;

  return ((veca->x == vecb->x) &&
          (veca->y == vecb->y) &&
          (veca->z == vecb->z) &&
          (veca->w == vecb->w));
}

/**
 * crank_vec_float4_equal_delta:
 * @a: (type CrankVecFloat4): Vector to compare.
 * @b: (type CrankVecFloat4): Vector to compare.
 * @d: Allowed difference to be considered equal.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_float4_equal_delta (gconstpointer a,
                              gconstpointer b,
                              const gfloat  d)
{
  CrankVecFloat4 *veca = (CrankVecFloat4*)a;
  CrankVecFloat4 *vecb = (CrankVecFloat4*)b;

  CrankVecFloat4 vecd;
  gfloat         dm;
  gfloat         dd;

  crank_vec_float4_sub (vecb, veca, &vecd);

  dm = crank_vec_float4_get_magn_sq (&vecd);
  dd = d * d;

  return (dm < dd);
}

/**
 * crank_vec_float4_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_float4_to_string (const CrankVecFloat4 *vec)
{
  return crank_vec_float4_to_string_full (vec, "(", ", ", ")", "%g");
}

/**
 * crank_vec_float4_to_string_full:
 * @vec: Vector to string.
 * @left: Left string, which indicates that vector's start.
 * @in: Delimiter, which is inserted between elements.
 * @right: Right string. which indicates that vector's end.
 * @format: Format to use with elements.
 *
 * Construct string from vector, with given format.
 *
 * Returns: (transfer full): stringified items of value.
 */
gchar*
crank_vec_float4_to_string_full (const CrankVecFloat4 *vec,
                                 const gchar          *left,
                                 const gchar          *in,
                                 const gchar          *right,
                                 const gchar          *format)
{
  GString *strb = g_string_new (left);
  gchar *result;

  g_string_append_printf (strb, format, vec->x);
  g_string_append (strb, in);

  g_string_append_printf (strb, format, vec->y);
  g_string_append (strb, in);

  g_string_append_printf (strb, format, vec->z);
  g_string_append (strb, in);

  g_string_append_printf (strb, format, vec->w);
  g_string_append (strb, right);

  result = strb->str;

  g_string_free (strb, FALSE);

  return result;
}


//////// Standard vector property ///////

/**
 * crank_vec_float4_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
gfloat
crank_vec_float4_get_magn_sq (const CrankVecFloat4 *vec)
{
  return (vec->x * vec->x) +
         (vec->y * vec->y) +
         (vec->z * vec->z) +
         (vec->w * vec->w);
}

/**
 * crank_vec_float4_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_float4_get_magn (const CrankVecFloat4 *vec)
{
  gfloat sq = crank_vec_float4_get_magn_sq (vec);
  return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_float4_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_float4_neg (const CrankVecFloat4 *a,
                      CrankVecFloat4       *r)
{
  r->x = -(a->x);
  r->y = -(a->y);
  r->z = -(a->z);
  r->w = -(a->w);
}

/**
 * crank_vec_float4_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_float4_neg_self (CrankVecFloat4 *a)
{
  a->x = -(a->x);
  a->y = -(a->y);
  a->z = -(a->z);
  a->w = -(a->w);
}

/**
 * crank_vec_float4_unit:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float4_unit (const CrankVecFloat4 *a,
                       CrankVecFloat4       *r)
{
  crank_vec_float4_divs (a, crank_vec_float4_get_magn (a), r);
}

/**
 * crank_vec_float4_unit_self:
 * @a: A vector
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float4_unit_self (CrankVecFloat4 *a)
{
  crank_vec_float4_divs_self (a, crank_vec_float4_get_magn (a));
}


//////// Scalar operations ////////

/**
 * crank_vec_float4_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_float4_muls (const CrankVecFloat4 *a,
                       const gfloat          b,
                       CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);

  r->x = a->x * b;
  r->y = a->y * b;
  r->z = a->z * b;
  r->w = a->w * b;
}

/**
 * crank_vec_float4_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_float4_muls_self (CrankVecFloat4 *a,
                            const gfloat    b)
{
  a->x *= b;
  a->y *= b;
  a->z *= b;
  a->w *= b;
}

/**
 * crank_vec_float4_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_float4_divs (const CrankVecFloat4 *a,
                       const gfloat          b,
                       CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);

  r->x = a->x / b;
  r->y = a->y / b;
  r->z = a->z / b;
  r->w = a->w / b;
}

/**
 * crank_vec_float4_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_float4_divs_self (CrankVecFloat4 *a,
                            const gfloat    b)
{
  a->x /= b;
  a->y /= b;
  a->z /= b;
  a->w /= b;
}


//////// Standard vector operations ////////

/**
 * crank_vec_float4_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_float4_add (const CrankVecFloat4 *a,
                      const CrankVecFloat4 *b,
                      CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x + b->x;
  r->y = a->y + b->y;
  r->z = a->z + b->z;
  r->w = a->w + b->w;
}

/**
 * crank_vec_float4_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_float4_add_self (CrankVecFloat4       *a,
                           const CrankVecFloat4 *b)
{
  a->x += b->x;
  a->y += b->y;
  a->z += b->z;
  a->w += b->w;
}

/**
 * crank_vec_float4_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_float4_sub (const CrankVecFloat4 *a,
                      const CrankVecFloat4 *b,
                      CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x - b->x;
  r->y = a->y - b->y;
  r->z = a->z - b->z;
  r->w = a->w - b->w;
}

/**
 * crank_vec_float4_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_float4_sub_self (CrankVecFloat4       *a,
                           const CrankVecFloat4 *b)
{
  a->x -= b->x;
  a->y -= b->y;
  a->z -= b->z;
  a->w -= b->w;
}

/**
 * crank_vec_float4_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
gfloat
crank_vec_float4_dot (const CrankVecFloat4 *a,
                      const CrankVecFloat4 *b)
{
  return (a->x) * (b->x) +
         (a->y) * (b->y) +
         (a->z) * (b->z) +
         (a->w) * (b->w);
}


//////// Component vector operations ////////

/**
 * crank_vec_float4_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_float4_cmpmul (const CrankVecFloat4 *a,
                         const CrankVecFloat4 *b,
                         CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x * b->x;
  r->y = a->y * b->y;
  r->z = a->z * b->z;
  r->w = a->w * b->w;
}

/**
 * crank_vec_float4_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_float4_cmpmul_self (CrankVecFloat4       *a,
                              const CrankVecFloat4 *b)
{
  a->x *= b->x;
  a->y *= b->y;
  a->z *= b->z;
  a->w *= b->w;
}

/**
 * crank_vec_float4_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise division.
 */
void
crank_vec_float4_cmpdiv (const CrankVecFloat4 *a,
                         const CrankVecFloat4 *b,
                         CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x / b->x;
  r->y = a->y / b->y;
  r->z = a->z / b->z;
  r->w = a->w / b->w;
}

/**
 * crank_vec_float4_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise division.
 */
void
crank_vec_float4_cmpdiv_self (CrankVecFloat4       *a,
                              const CrankVecFloat4 *b)
{
  a->x /= b->x;
  a->y /= b->y;
  a->z /= b->z;
  a->w /= b->w;
}


/**
 * crank_vec_float4_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_float4_cmpless (const CrankVecFloat4 *a,
                          const CrankVecFloat4 *b,
                          CrankVecBool4        *r)
{
  r->x = (a->x) < (b->x);
  r->y = (a->y) < (b->y);
  r->z = (a->z) < (b->z);
  r->w = (a->w) < (b->w);
}

/**
 * crank_vec_float4_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_float4_cmpeq (const CrankVecFloat4 *a,
                        const CrankVecFloat4 *b,
                        CrankVecBool4        *r)
{
  r->x = (a->x) == (b->x);
  r->y = (a->y) == (b->y);
  r->z = (a->z) == (b->z);
  r->w = (a->w) == (b->w);
}

/**
 * crank_vec_float4_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is greater than counterpart of @b
 */
void
crank_vec_float4_cmpgreater (const CrankVecFloat4 *a,
                             const CrankVecFloat4 *b,
                             CrankVecBool4        *r)
{
  r->x = (a->x) > (b->x);
  r->y = (a->y) > (b->y);
  r->z = (a->z) > (b->z);
  r->w = (a->w) > (b->w);
}

/**
 * crank_vec_float4_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets compare result of each components.
 */
void
crank_vec_float4_cmpcmp (const CrankVecFloat4 *a,
                         const CrankVecFloat4 *b,
                         CrankVecInt4         *r)
{
  r->x = CMP(a->x, b->x);
  r->y = CMP(a->y, b->y);
  r->z = CMP(a->z, b->z);
  r->w = CMP(a->w, b->w);
}

/**
 * crank_vec_float4_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_float4_min (const CrankVecFloat4 *a,
                      const CrankVecFloat4 *b,
                      CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MIN (a->x, b->x);
  r->y = MIN (a->y, b->y);
  r->z = MIN (a->z, b->z);
  r->w = MIN (a->w, b->w);
}

/**
 * crank_vec_float4_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_float4_max (const CrankVecFloat4 *a,
                      const CrankVecFloat4 *b,
                      CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MAX (a->x, b->x);
  r->y = MAX (a->y, b->y);
  r->z = MAX (a->z, b->z);
  r->w = MAX (a->w, b->w);
}

/**
 * crank_vec_float4_abs:
 * @a: A Vector.
 * @r: (out): A vector to store result.
 *
 * Gets absolute value of each components.
 */
void
crank_vec_float4_abs (const CrankVecFloat4 *a,
                      CrankVecFloat4       *r)
{
  g_return_if_fail (a != r);

  r->x = ABS (a->x);
  r->y = ABS (a->y);
  r->z = ABS (a->z);
  r->w = ABS (a->w);
}


/**
 * crank_vec_float4_abs_self:
 * @a: A Vector.
 *
 * Applys absolute value of each components.
 */
void
crank_vec_float4_abs_self (CrankVecFloat4 *a)
{
  a->x = ABS (a->x);
  a->y = ABS (a->y);
  a->z = ABS (a->z);
  a->w = ABS (a->w);
}


/**
 * crank_vec_float4_mulm:
 * @a: A Vector
 * @b: A Matrix
 * @r: (out): A Vector to store result.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_float4_mulm (const CrankVecFloat4 *a,
                       const CrankMatFloat4 *b,
                       CrankVecFloat4       *r)
{
  gfloat nx, ny, nz, nw;

  g_return_if_fail (a != r);

  nx = (a->x * b->m00) + (a->y * b->m10) + (a->z * b->m20) + (a->w * b->m30);
  ny = (a->x * b->m01) + (a->y * b->m11) + (a->z * b->m21) + (a->w * b->m31);
  nz = (a->x * b->m02) + (a->y * b->m12) + (a->z * b->m22) + (a->w * b->m32);
  nw = (a->x * b->m03) + (a->y * b->m13) + (a->z * b->m23) + (a->w * b->m33);

  r->x = nx;
  r->y = ny;
  r->z = nz;
  r->w = nw;
}

/**
 * crank_vec_float4_mulm_self:
 * @a: A Vector
 * @b: A Matrix
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_float4_mulm_self (CrankVecFloat4       *a,
                            const CrankMatFloat4 *b)
{
  gfloat nx, ny, nz, nw;

  nx = (a->x * b->m00) + (a->y * b->m10) + (a->z * b->m20) + (a->w * b->m30);
  ny = (a->x * b->m01) + (a->y * b->m11) + (a->z * b->m21) + (a->w * b->m31);
  nz = (a->x * b->m02) + (a->y * b->m12) + (a->z * b->m22) + (a->w * b->m32);
  nw = (a->x * b->m03) + (a->y * b->m13) + (a->z * b->m23) + (a->w * b->m33);

  a->x = nx;
  a->y = ny;
  a->z = nz;
  a->w = nw;
}

/**
 * crank_vec_float4_mixs:
 * @a: A vector.
 * @b: A vector.
 * @c: A scalar factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a * (1-c)) + (b * c)
 */
void
crank_vec_float4_mixs (const CrankVecFloat4 *a,
                       const CrankVecFloat4 *b,
                       const gfloat          c,
                       CrankVecFloat4       *r)
{
  gfloat d;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  d = 1.0f - c;

  r->x = a->x * d + b->x * c;
  r->y = a->y * d + b->y * c;
  r->z = a->z * d + b->z * c;
  r->w = a->w * d + b->w * c;
}


/**
 * crank_vec_float4_mix:
 * @a: A vector.
 * @b: A vector.
 * @c: A factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a cmpmul c) + (b cmpmul ({1, 1, 1, 1} - c))
 */
void
crank_vec_float4_mix (const CrankVecFloat4 *a,
                      const CrankVecFloat4 *b,
                      const CrankVecFloat4 *c,
                      CrankVecFloat4       *r)
{
  CrankVecFloat4 d;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  g_return_if_fail (c != r);

  d.x = 1.0f - c->x;
  d.y = 1.0f - c->y;
  d.z = 1.0f - c->z;
  d.w = 1.0f - c->w;

  r->x = a->x * d.x + b->x * c->x;
  r->y = a->y * d.y + b->y * c->y;
  r->z = a->z * d.z + b->z * c->z;
  r->w = a->w * d.w + b->w * c->w;
}

//////// GValue Transform //////////////////////////////////////////////////////

static void
crank_vec_float4_transform_from_vb (const GValue *src,
                                    GValue       *dest)
{
  CrankVecFloat4 *vf = g_new (CrankVecFloat4, 1);
  CrankVecBool4 *vb = (CrankVecBool4*) g_value_get_boxed (src);

  crank_vec_float4_init_from_vb (vf, vb);
  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float4_transform_from_vi (const GValue *src,
                                    GValue       *dest)
{
  CrankVecFloat4 *vf = g_new (CrankVecFloat4, 1);
  CrankVecInt4 *vi = (CrankVecInt4*) g_value_get_boxed (src);

  crank_vec_float4_init_from_vi (vf, vi);
  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float4_transform_to_string (const GValue *src,
                                      GValue       *dest)
{
  CrankVecFloat4 *vf = (CrankVecFloat4*) g_value_get_boxed (src);
  gchar *str = crank_vec_float4_to_string (vf);

  g_value_take_string (dest, str);
}








static void crank_vec_float_n_transform_from_vb (const GValue *src,
                                                 GValue       *dest);

static void crank_vec_float_n_transform_from_vi (const GValue *src,
                                                 GValue       *dest);

static void crank_vec_float_n_transform_from_v2 (const GValue *src,
                                                 GValue       *dest);

static void crank_vec_float_n_transform_from_v3 (const GValue *src,
                                                 GValue       *dest);

static void crank_vec_float_n_transform_from_v4 (const GValue *src,
                                                 GValue       *dest);

static void crank_vec_float_n_transform_to_string (const GValue *src,
                                                   GValue       *dest);

G_DEFINE_BOXED_TYPE_WITH_CODE (
  CrankVecFloatN,
  crank_vec_float_n,
  crank_vec_float_n_dup,
  g_free,
  {
    g_value_register_transform_func (CRANK_TYPE_VEC_BOOL_N,
                                     g_define_type_id,
                                     crank_vec_float_n_transform_from_vb);

    g_value_register_transform_func (CRANK_TYPE_VEC_INT_N,
                                     g_define_type_id,
                                     crank_vec_float_n_transform_from_vi);

    g_value_register_transform_func (CRANK_TYPE_VEC_FLOAT2,
                                     g_define_type_id,
                                     crank_vec_float_n_transform_from_v2);

    g_value_register_transform_func (CRANK_TYPE_VEC_FLOAT3,
                                     g_define_type_id,
                                     crank_vec_float_n_transform_from_v3);

    g_value_register_transform_func (CRANK_TYPE_VEC_FLOAT4,
                                     g_define_type_id,
                                     crank_vec_float_n_transform_from_v4);

    g_value_register_transform_func (g_define_type_id,
                                     G_TYPE_STRING,
                                     crank_vec_float_n_transform_to_string);
  })

/**
 * crank_vec_float_n_init:
 * @vec: (out): Vector to initialize.
 * @n: size of vector.
 * @...: element of vector.
 *
 * Initializes vector with given components.
 */
void
crank_vec_float_n_init (CrankVecFloatN *vec,
                        const guint     n,
                        ...)
{
  va_list varargs;

  va_start (varargs, n);

  crank_vec_float_n_init_valist (vec, n, varargs);

  va_end (varargs);
}

/**
 * crank_vec_float_n_init_arr:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @arr: (array length=n): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_float_n_init_arr (CrankVecFloatN *vec,
                            const guint     n,
                            const gfloat   *arr)
{
  guint i;

  CRANK_VEC_ALLOC (vec, gfloat, n);
  for (i = 0; i < n; i++)
    vec->data[i] = arr[i];
}

/**
 * crank_vec_float_n_init_arr_take:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @arr: (transfer full): Array that contains elements.
 *
 * Initializes vector by taking array as data.
 */
void
crank_vec_float_n_init_arr_take (CrankVecFloatN *vec,
                                 const guint     n,
                                 gfloat         *arr)
{
  vec->n = n;
  vec->data = arr;
}

/**
 * crank_vec_float_n_init_valist:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_float_n_init_valist (CrankVecFloatN *vec,
                               const guint     n,
                               va_list         varargs)
{
  guint i;

  CRANK_VEC_ALLOC(vec,gfloat,n);
  for (i = 0; i < n; i++)
    vec->data[i] = va_arg (varargs, gdouble);
}

/**
 * crank_vec_float_n_init_fill:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_float_n_init_fill (CrankVecFloatN *vec,
                             const guint     n,
                             const gfloat    fill)
{
  guint i;

  CRANK_VEC_ALLOC(vec,gfloat,n);
  for (i = 0; i < n; i++)
    vec->data[i] = fill;
}

/**
 * crank_vec_float_n_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_float_n_init_from_vb (CrankVecFloatN       *vec,
                                const CrankVecBoolN  *vb)
{
  guint i;

  CRANK_VEC_ALLOC(vec,gfloat,vb->n);
  for (i = 0; i < vb->n; i++)
    vec->data[i] = vb->data[i] ? 1.0f : 0.0f;
}

/**
 * crank_vec_float_n_init_from_vi:
 * @vec: (out): Vector to initialize.
 * @vi: Integer vector.
 *
 * Initialize vector from integer vector.
 */
void
crank_vec_float_n_init_from_vi (CrankVecFloatN       *vec,
                                const CrankVecIntN   *vi)
{
  guint i;

  CRANK_VEC_ALLOC(vec,gfloat,vi->n);
  for (i = 0; i < vi->n; i++)
    vec->data[i] = vi->data[i];
}


/**
 * crank_vec_float_n_fini:
 * @vec: Vector to finalize.
 *
 * Frees all allocated memory and unsets @vec to point 0-sized vector at %NULL.
 */
void
crank_vec_float_n_fini (CrankVecFloatN *vec)
{
  g_free (vec->data);
  vec->data = NULL;
  vec->n = 0;
}


/**
 * crank_vec_float_n_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_float_n_copy (const CrankVecFloatN *vec,
                        CrankVecFloatN       *other)
{
  crank_vec_float_n_init_arr (other, vec->n, vec->data);
}

/**
 * crank_vec_float_n_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecFloatN*
crank_vec_float_n_dup (const CrankVecFloatN *vec)
{
  CrankVecFloatN *result = g_new0 (CrankVecFloatN, 1);
  crank_vec_float_n_copy (vec, result);
  return result;
}

/**
 * crank_vec_float_n_free:
 * @vec: Vector to free.
 *
 * Frees all allocated memory and frees struct too.
 */
void
crank_vec_float_n_free (CrankVecFloatN *vec)
{
  crank_vec_float_n_fini (vec);
  g_free (vec);
}

/**
 * crank_vec_float_n_get_size:
 * @vec: A Vector.
 *
 * Gets size of a vector.
 *
 * Returns: Size of vector.
 */
guint
crank_vec_float_n_get_size (const CrankVecFloatN *vec)
{
  return vec->n;
}

/**
 * crank_vec_float_n_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
gfloat
(crank_vec_float_n_get) (const CrankVecFloatN *vec,
                         const guint     index)
{
  return CRANK_VEC_GET (vec, index);
}

/**
 * crank_vec_float_n_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
(crank_vec_float_n_set) (CrankVecFloatN *vec,
                         const guint     index,
                         const gfloat    value)
{
  CRANK_VEC_SET (vec, index, value);
}

/**
 * crank_vec_float_n_prepend:
 * @vec: Vector to insert element.
 * @value: Value of element.
 *
 * Prepends an element to vector.
 */
void
crank_vec_float_n_prepend (CrankVecFloatN *vec,
                           const gfloat    value)
{
  crank_vec_float_n_insert (vec, 0, value);
}

/**
 * crank_vec_float_n_append:
 * @vec: Vector to insert element.
 * @value: Value of element.
 *
 * Appends an element to vector.
 */
void
crank_vec_float_n_append (CrankVecFloatN *vec,
                          const gfloat    value)
{
  crank_vec_float_n_insert (vec, vec->n, value);
}

/**
 * crank_vec_float_n_insert:
 * @vec: Vector to insert element.
 * @index: Index to insert element.
 * @value: Value of element.
 *
 * Inserts an element to vector.
 */
void
crank_vec_float_n_insert (CrankVecFloatN *vec,
                          const guint     index,
                          const gfloat    value)
{
  guint i;

  g_return_if_fail (index <= vec->n);

  vec->n++;
  vec->data = g_renew (gfloat, vec->data, vec->n);

  for (i = vec->n - 1; index < i; i--)
    vec->data[i] = vec->data[i - 1];

  vec->data[index] = value;
}

/**
 * crank_vec_float_n_remove:
 * @vec: Vector to remove element.
 * @index: Index to remove element.
 *
 * Removes an element from vector.
 */
void
crank_vec_float_n_remove (CrankVecFloatN *vec,
                          const guint     index)
{
  guint i;

  g_return_if_fail (index < vec->n);

  vec->n--;

  for (i = index; i < vec->n; i++)
    vec->data[i] = vec->data[i + 1];

  vec->data = g_renew (gfloat, vec->data, vec->n);
}

/**
 * crank_vec_float_n_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a float vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_float_n_foreach (const CrankVecFloatN *vec,
                           CrankBoolFloatFunc    func,
                           gpointer              userdata)
{
  guint i;

  for (i = 0; i < vec->n; i++)
    if (!func (vec->data[i], userdata))
      return FALSE;

  return TRUE;
}

/**
 * crank_vec_float_n_iterator:
 * @vec: A Vector
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_float_n_iterator (CrankVecFloatN    *vec,
                            CrankIterMemFloat *iter)
{
  crank_iter_mem_float_init_with_count (iter, vec->data, vec->n);
}


//////// Basic operation ////////

/**
 * crank_vec_float_n_hash:
 * @a: (type CrankVecFloatN): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_float_n_hash (gconstpointer a)
{
  const CrankVecFloatN *vec = a;

  guint i;
  guint hash = 0;

  for (i = 0; i < vec->n; i++)
    hash += crank_float_hash (vec->data + i) + hash * 37;

  return hash;
}

/**
 * crank_vec_float_n_equal:
 * @a: (type CrankVecFloatN): Vector to compare.
 * @b: (type CrankVecFloatN): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_float_n_equal (gconstpointer a,
                         gconstpointer b)
{
  CrankVecFloatN *veca = (CrankVecFloatN*)a;
  CrankVecFloatN *vecb = (CrankVecFloatN*)b;

  guint n;
  guint i;

  if (veca->n != vecb->n)
    return FALSE;

  n = veca->n;

  for (i = 0; i < n; i++)
    {
      if (veca->data[i] != vecb->data[i])
        return FALSE;
    }

  return TRUE;
}

/**
 * crank_vec_float_n_equal_delta:
 * @a: (type CrankVecFloatN): Vector to compare.
 * @b: (type CrankVecFloatN): Vector to compare.
 * @d: Allowed difference to be considered equal.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_float_n_equal_delta (gconstpointer a,
                               gconstpointer b,
                               const gfloat  d)
{
  CrankVecFloatN *veca = (CrankVecFloatN*)a;
  CrankVecFloatN *vecb = (CrankVecFloatN*)b;

  CrankVecFloatN vecd;
  gfloat         dm;
  gfloat         dd;

  if (veca->n != vecb->n)
    return FALSE;

  crank_vec_float_n_sub (vecb, veca, &vecd);

  dm = crank_vec_float_n_get_magn_sq (&vecd);
  dd = d * d;

  return (dm < dd);
}

/**
 * crank_vec_float_n_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_float_n_to_string (const CrankVecFloatN *vec)
{
  return crank_vec_float_n_to_string_full (vec, "(", ", ", ")", "%g");
}

/**
 * crank_vec_float_n_to_string_full:
 * @vec: Vector to string.
 * @left: Left string, which indicates that vector's start.
 * @in: Delimiter, which is inserted between elements.
 * @right: Right string. which indicates that vector's end.
 * @format: Format to use with elements.
 *
 * Construct string from vector, with given format.
 *
 * Returns: (transfer full): stringified items of value.
 */
gchar*
crank_vec_float_n_to_string_full (const CrankVecFloatN *vec,
                                  const gchar          *left,
                                  const gchar          *in,
                                  const gchar          *right,
                                  const gchar          *format)
{
  GString *strb = g_string_new (left);
  gchar *result;

  guint i;

  if (vec->n != 0)
    {
      g_string_append_printf (strb, format, vec->data[0]);

      for (i = 1; i < vec->n; i++)
        {
          g_string_append (strb, in);
          g_string_append_printf (strb, format, vec->data[i]);
        }
    }
  g_string_append (strb, right);

  result = strb->str;

  g_string_free (strb, FALSE);

  return result;
}


//////// Classification ////////////////////////////////////////////////////////

/**
 * crank_vec_float_n_is_zero:
 * @vec: A Vector
 *
 * Checks whether the vector is "Zero Vector", whose all components are 0.
 *
 * Returns: Whether the vector is "zero vector".
 */
gboolean
crank_vec_float_n_is_zero (const CrankVecFloatN *vec)
{
  guint i;

  for (i = 0; i < vec->n; i++)
    {
      if (vec->data[i] != 0)
        return FALSE;
    }

  return TRUE;
}

/**
 * crank_vec_float_n_is_one:
 * @vec: A Vector
 *
 * Checks whether the vector has all components as 1.
 *
 * Returns: Whether the vector has all components as 1.
 */
gboolean
crank_vec_float_n_is_one (const CrankVecFloatN *vec)
{
  guint i;

  for (i = 0; i < vec->n; i++)
    {
      if (vec->data[i] != 1)
        return FALSE;
    }

  return TRUE;
}

/**
 * crank_vec_float_n_is_unit:
 * @vec: A Vector
 *
 * Checks whether the magnitude of vector is 1.
 *
 * Returns: Whether the magnitude of vector is 1.
 */
gboolean
crank_vec_float_n_is_unit (const CrankVecFloatN *vec)
{
  gfloat magnsq = crank_vec_float_n_get_magn_sq (vec);

  return (0.9999f <= magnsq) && (magnsq <= 1.0001f);
}

/**
 * crank_vec_float_n_is_empty:
 * @vec: A Vector
 *
 * Checks whether the vector is empty.
 *
 * Returns: Whether the vector is empty.
 */
gboolean
crank_vec_float_n_is_empty (const CrankVecFloatN *vec)
{
  return vec->n == 0;
}

/**
 * crank_vec_float_n_has_nan:
 * @vec: A Vector
 *
 * Chechks whether the vector has NaN.
 *
 * Returns: Whether the vector has NaN.
 */
gboolean
crank_vec_float_n_has_nan (const CrankVecFloatN *vec)
{
  guint i;

  for (i = 0; i < vec->n; i++)
    {
      if (isnanf (vec->data[i]))
        return TRUE;
    }
  return FALSE;
}

/**
 * crank_vec_float_n_has_inf:
 * @vec: A Vector
 *
 * Chechks whether the vector has infinity.
 *
 * Returns: Whether the vector has (inf).
 */
gboolean
crank_vec_float_n_has_inf (const CrankVecFloatN *vec)
{
  guint i;

  for (i = 0; i < vec->n; i++)
    {
      if (isinff (vec->data[i]))
        return TRUE;
    }
  return FALSE;
}

//////// Standard vector property ///////

/**
 * crank_vec_float_n_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
gfloat
crank_vec_float_n_get_magn_sq (const CrankVecFloatN *vec)
{
  gfloat result = 0;
  guint i;

  for (i = 0; i < vec->n; i++)
    result += vec->data[i] * vec->data[i];

  return result;
}

/**
 * crank_vec_float_n_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_float_n_get_magn (const CrankVecFloatN *vec)
{
  gfloat sq = crank_vec_float_n_get_magn_sq (vec);
  return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_float_n_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_float_n_neg (const CrankVecFloatN *a,
                       CrankVecFloatN       *r)
{
  guint i;

  CRANK_VEC_ALLOC (r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i];
}


/**
 * crank_vec_float_n_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_float_n_neg_self (CrankVecFloatN *a)
{
  guint i;

  for (i = 0; i < a->n; i++)
    a->data[i] = -a->data[i];
}


/**
 * crank_vec_float_n_unit:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float_n_unit (const CrankVecFloatN *a,
                        CrankVecFloatN       *r)
{
  crank_vec_float_n_divs (a, crank_vec_float_n_get_magn (a), r);
}


/**
 * crank_vec_float_n_unit_self:
 * @a: A vector
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float_n_unit_self (CrankVecFloatN *a)
{
  crank_vec_float_n_divs_self (a, crank_vec_float_n_get_magn (a));
}


//////// Scalar operations ////////

/**
 * crank_vec_float_n_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_float_n_muls (const CrankVecFloatN *a,
                        const gfloat          b,
                        CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);

  CRANK_VEC_ALLOC(r,gfloat,a->n);
  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] * b;
}

/**
 * crank_vec_float_n_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_float_n_muls_self (CrankVecFloatN *a,
                             const gfloat    b)
{
  guint i;

  for (i = 0; i < a->n; i++)
    a->data[i] *= b;
}

/**
 * crank_vec_float_n_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_float_n_divs (const CrankVecFloatN *a,
                        const gfloat          b,
                        CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);

  CRANK_VEC_ALLOC(r,gfloat,a->n);
  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] / b;
}

/**
 * crank_vec_float_n_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_float_n_divs_self (CrankVecFloatN *a,
                             const gfloat    b)
{
  guint i;

  for (i = 0; i < a->n; i++)
    a->data[i] /= b;
}


//////// Standard vector operations ////////

/**
 * crank_vec_float_n_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_float_n_add (const CrankVecFloatN *a,
                       const CrankVecFloatN *b,
                       CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "add", a, b);
  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] + b->data[i];
}

/**
 * crank_vec_float_n_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_float_n_add_self (CrankVecFloatN       *a,
                            const CrankVecFloatN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "add-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] += b->data[i];
}

/**
 * crank_vec_float_n_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_float_n_sub (const CrankVecFloatN *a,
                       const CrankVecFloatN *b,
                       CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "sub", a, b);
  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] - b->data[i];
}

/**
 * crank_vec_float_n_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_float_n_sub_self (CrankVecFloatN       *a,
                            const CrankVecFloatN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "sub-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] -= b->data[i];
}

/**
 * crank_vec_float_n_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
gfloat
crank_vec_float_n_dot (const CrankVecFloatN *a,
                       const CrankVecFloatN *b)
{
  gfloat result = 0;
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2_RET ("VecFloatN", "dot", a, b, 0.0f);

  for (i = 0; i < a->n; i++)
    result += a->data[i] * b->data[i];
  return result;
}

//////// Component vector operations ////////

/**
 * crank_vec_float_n_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_float_n_cmpmul (const CrankVecFloatN *a,
                          const CrankVecFloatN *b,
                          CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "cmpmul", a, b);
  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] * b->data[i];
}

/**
 * crank_vec_float_n_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_float_n_cmpmul_self (CrankVecFloatN       *a,
                               const CrankVecFloatN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "cmpmul-self", a, b);
  for (i = 0; i < a->n; i++)
    a->data[i] *= b->data[i];
}

/**
 * crank_vec_float_n_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise division.
 */
void
crank_vec_float_n_cmpdiv (const CrankVecFloatN *a,
                          const CrankVecFloatN *b,
                          CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "cmpdiv", a, b);
  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] / b->data[i];
}

/**
 * crank_vec_float_n_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise division.
 */
void
crank_vec_float_n_cmpdiv_self (CrankVecFloatN       *a,
                               const CrankVecFloatN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "cmpdiv-self", a, b);
  for (i = 0; i < a->n; i++)
    a->data[i] /= b->data[i];
}

/**
 * crank_vec_float_n_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_float_n_cmpless (const CrankVecFloatN *a,
                           const CrankVecFloatN *b,
                           CrankVecBoolN        *r)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "cmpless", a, b);
  CRANK_VEC_ALLOC(r, gboolean, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] < b->data[i];
}

/**
 * crank_vec_float_n_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_float_n_cmpeq (const CrankVecFloatN *a,
                         const CrankVecFloatN *b,
                         CrankVecBoolN        *r)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "cmpeq", a, b);
  CRANK_VEC_ALLOC(r, gboolean, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] == b->data[i];
}

/**
 * crank_vec_float_n_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is greater than counterpart of @b
 */
void
crank_vec_float_n_cmpgreater (const CrankVecFloatN *a,
                              const CrankVecFloatN *b,
                              CrankVecBoolN        *r)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "cmpgreater", a, b);
  CRANK_VEC_ALLOC(r, gboolean, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] > b->data[i];
}

/**
 * crank_vec_float_n_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets compare result of each components.
 */
void
crank_vec_float_n_cmpcmp (const CrankVecFloatN *a,
                          const CrankVecFloatN *b,
                          CrankVecIntN         *r)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "cmpcmp", a, b);
  CRANK_VEC_ALLOC(r, gint, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = CMP (a->data[i], b->data[i]);
}

/**
 * crank_vec_float_n_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_float_n_min (const CrankVecFloatN *a,
                       const CrankVecFloatN *b,
                       CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "min", a, b);
  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = MIN (a->data[i], b->data[i]);
}

/**
 * crank_vec_float_n_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_float_n_max (const CrankVecFloatN *a,
                       const CrankVecFloatN *b,
                       CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "max", a, b);
  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = MAX (a->data[i], b->data[i]);
}


/**
 * crank_vec_float_n_abs:
 * @a: A Vector.
 * @r: (out): A vector to store result.
 *
 * Gets absolute value of each components.
 */
void
crank_vec_float_n_abs (const CrankVecFloatN *a,
                       CrankVecFloatN       *r)
{
  guint i;

  g_return_if_fail (a != r);

  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = ABS (a->data[i]);
}

/**
 * crank_vec_float_n_abs_self:
 * @a: A Vector.
 *
 * Gets absolute value of each components.
 */
void
crank_vec_float_n_abs_self (CrankVecFloatN *a)
{
  guint i;

  for (i = 0; i < a->n; i++)
    a->data[i] = ABS (a->data[i]);
}


/**
 * crank_vec_float_n_mulm:
 * @a: A vector.
 * @b: A Matrox.
 * @r: (out): A vector to store result.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_float_n_mulm (const CrankVecFloatN *a,
                        const CrankMatFloatN *b,
                        CrankVecFloatN       *r)
{
  g_return_if_fail (a != r);

  if (a->n == b->rn)
    {
      guint i;
      guint j;
      gfloat *data;

      data = g_new0 (gfloat, b->cn);

      for (i = 0; i < b->cn; i++)
        for (j = 0; j < a->n; j++)
          data[i] += a->data[j] * b->data[(b->cn * j) + i];

      crank_vec_float_n_init_arr_take (r, b->cn, data);
    }
  else
    g_warning ("VecFloatN: mulm: size mismatch: %u, %ux%u", a->n, b->rn, b->cn);


}


/**
 * crank_vec_float_n_mulm_self:
 * @a: A vector.
 * @b: A Matrox.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_float_n_mulm_self (CrankVecFloatN       *a,
                             const CrankMatFloatN *b)
{
  if (a->n == b->rn)
    {
      guint i;
      guint j;
      gfloat *data;

      data = g_new0 (gfloat, b->cn);

      for (i = 0; i < b->cn; i++)
        for (j = 0; j < a->n; j++)
          data[i] += a->data[j] * b->data[(b->cn * j) + i];

      g_free (a->data);
      crank_vec_float_n_init_arr_take (a, b->cn, data);
    }
  else
    g_warning ("VecFloatN: mulm-self: size mismatch: %u, %ux%u",
               a->n,
               b->rn,
               b->cn);
}

/**
 * crank_vec_float_n_mixs:
 * @a: A vector.
 * @b: A vector.
 * @c: A scalar factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a * (1-c)) + (b * c)
 */
void
crank_vec_float_n_mixs (const CrankVecFloatN *a,
                        const CrankVecFloatN *b,
                        const gfloat          c,
                        CrankVecFloatN       *r)
{
  guint i;
  gfloat d;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  d = 1.0f - c;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecFloatN", "mixs", a, b);
  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] * d + b->data[i] * c;
}


/**
 * crank_vec_float_n_mix:
 * @a: A vector.
 * @b: A vector.
 * @c: A factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a cmpmul c) + (b cmpmul ({1, 1, ..., 1} - c))
 */
void
crank_vec_float_n_mix (const CrankVecFloatN *a,
                       const CrankVecFloatN *b,
                       const CrankVecFloatN *c,
                       CrankVecFloatN       *r)
{
  gfloat d;
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  g_return_if_fail (c != r);

  CRANK_VEC_WARN_IF_SIZE_MISMATCH3 ("VecFloatN", "mix", a, b, c);
  CRANK_VEC_ALLOC(r, gfloat, a->n);

  for (i = 0; i < a->n; i++)
    {
      d = 1.0f - c->data[i];
      r->data[i] =    a->data[i] * d + b->data[i] * c->data[i];
    }
}

//////// GValue Transform //////////////////////////////////////////////////////

static void
crank_vec_float_n_transform_from_vb (const GValue *src,
                                     GValue       *dest)
{
  CrankVecFloatN *vf = g_new (CrankVecFloatN, 1);
  CrankVecBoolN *vb = (CrankVecBoolN*) g_value_get_boxed (src);

  crank_vec_float_n_init_from_vb (vf, vb);
  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float_n_transform_from_vi (const GValue *src,
                                     GValue       *dest)
{
  CrankVecFloatN *vf = g_new (CrankVecFloatN, 1);
  CrankVecIntN *vi = (CrankVecIntN*) g_value_get_boxed (src);

  crank_vec_float_n_init_from_vi (vf, vi);
  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float_n_transform_from_v2 (const GValue *src,
                                     GValue       *dest)
{
  CrankVecFloatN *vf = g_new (CrankVecFloatN, 1);
  gfloat *array = (gfloat*) g_value_get_boxed (src);

  crank_vec_float_n_init_arr (vf, 2, array);
  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float_n_transform_from_v3 (const GValue *src,
                                     GValue       *dest)
{
  CrankVecFloatN *vf = g_new (CrankVecFloatN, 1);
  gfloat *array = (gfloat*) g_value_get_boxed (src);

  crank_vec_float_n_init_arr (vf, 3, array);

  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float_n_transform_from_v4 (const GValue *src,
                                     GValue       *dest)
{
  CrankVecFloatN *vf = g_new (CrankVecFloatN, 1);
  gfloat *array = (gfloat*) g_value_get_boxed (src);

  crank_vec_float_n_init_arr (vf, 4, array);

  g_value_take_boxed (dest, vf);
}

static void
crank_vec_float_n_transform_to_string (const GValue *src,
                                       GValue       *dest)
{
  CrankVecFloatN *vf = (CrankVecFloatN*) g_value_get_boxed (src);
  gchar *str = crank_vec_float_n_to_string (vf);
  g_value_take_string (dest, str);
}
