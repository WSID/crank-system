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
#include "crankveccommon.h"
#include "crankvecbool.h"
#include "crankvecuint.h"
#include "crankvecint.h"

/**
 * SECTION: crankvecuint
 * @title: Integer Vectors
 * @short_description: Vectors that have integer elements.
 * @stability: unstable
 * @include: crankbase.h
 *
 * Crank System provides 2, 3, 4, and free sized unsigned int vectors for
 * convinience.
 *
 * It is compared to uvec in GLSL
 *
 * # Type Conversion.
 *
 * Unsigned integer vector types are seldomly used, but for convenience, it can
 * be converted to other types
 *
 * For fixed-sized types, it can be converted to variadic sized vector types.
 *
 * <table><title>Type Conversion of #CrankVecUint2</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool2</entry>
 *             <entry>crank_vec_uint2_init_from_vb()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_uint2_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_uint2_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecUintN.</entry>
 *             <entry>crank_vec_uint_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecUintN</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloat2.</entry>
 *             <entry>crank_vec_float2_init_from_vi()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecFloat2</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecUint3</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool3</entry>
 *             <entry>crank_vec_uint3_init_from_vb()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_uint3_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_uint3_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecUintN.</entry>
 *             <entry>crank_vec_uint_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecUintN</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloat3.</entry>
 *             <entry>crank_vec_float3_init_from_vi()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecFloat3</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecUint4</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool4</entry>
 *             <entry>crank_vec_uint4_init_from_vb()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_uint4_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_uint4_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecUintN.</entry>
 *             <entry>crank_vec_uint_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecUintN</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloat4.</entry>
 *             <entry>crank_vec_float4_init_from_vi()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecFloat4</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecUintN</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrnakVecBoolN</entry>
 *             <entry>crank_vec_uint_n_init_from_vb()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry>From #CrankVecUint2</entry>
 *             <entry>crank_vec_uint_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>From #CrankVecUint3</entry>
 *             <entry>crank_vec_uint_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>From #CrankVecUint4</entry>
 *             <entry>crank_vec_uint_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_uint_n_to_string()</entry>
 *             <entry>GValue Transform</entry> </row>
 *       <row> <entry>crank_vec_uint_n_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloatN.</entry>
 *             <entry>crank_vec_float_n_init_from_vi()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecFloatN</entry> </row>
 *
 *       <row> <entry>To #CrankVecCplxFloatN.</entry>
 *             <entry>crank_vec_cplx_float_n_init_from_vi()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecCplxFloatN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */


#define CMP(a, b) (((a) > (b)) - ((a) < (b)))


static void crank_vec_uint2_transform_from_b (const GValue *src,
                                             GValue       *dest);

static void crank_vec_uint2_transform_to_string (const GValue *src,
                                                GValue       *dest);

G_DEFINE_BOXED_TYPE_WITH_CODE (
  CrankVecUint2,
  crank_vec_uint2,
  crank_vec_uint2_dup,
  g_free,
  {
    g_value_register_transform_func (CRANK_TYPE_VEC_BOOL2,
                                     g_define_type_id,
                                     crank_vec_uint2_transform_from_b);

    g_value_register_transform_func (g_define_type_id,
                                     G_TYPE_STRING,
                                     crank_vec_uint2_transform_to_string);
  })

/**
 * crank_vec_uint2_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_uint2_init (CrankVecUint2 *vec,
                      const guint    x,
                      const guint    y)
{
  vec->x = x;
  vec->y = y;
}

/**
 * crank_vec_uint2_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=2): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_uint2_init_arr (CrankVecUint2 *vec,
                          guint         *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
}

/**
 * crank_vec_uint2_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_uint2_init_valist (CrankVecUint2 *vec,
                            va_list       varargs)
{
  vec->x = va_arg (varargs, gdouble);
  vec->y = va_arg (varargs, gdouble);
}

/**
 * crank_vec_uint2_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_uint2_init_fill (CrankVecUint2 *vec,
                           const guint    fill)
{
  vec->x = fill;
  vec->y = fill;
}

/**
 * crank_vec_uint2_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_uint2_init_from_vb (CrankVecUint2  *vec,
                             CrankVecBool2 *vb)
{
  vec->x = vb->x ? 1 : 0;
  vec->y = vb->y ? 1 : 0;
}


/**
 * crank_vec_uint2_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_uint2_copy (CrankVecUint2 *vec,
                     CrankVecUint2 *other)
{
  memcpy (other, vec, sizeof (CrankVecUint2));
}


/**
 * crank_vec_uint2_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecUint2*
crank_vec_uint2_dup (CrankVecUint2 *vec)
{
  return (CrankVecUint2*) g_memdup (vec, sizeof (CrankVecUint2));
}

/**
 * crank_vec_uint2_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
guint
crank_vec_uint2_get (CrankVecUint2 *vec,
                     const guint   index)
{
  return ((gint*)vec)[index];
}

/**
 * crank_vec_uint2_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_uint2_set (CrankVecUint2 *vec,
                     const guint   index,
                     const guint   value)
{
  ((gint*)vec)[index] = value;
}

/**
 * crank_vec_uint2_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a int vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_uint2_foreach (CrankVecUint2    *vec,
                        CrankBoolUintFunc func,
                        gpointer         userdata)
{
  if (func (vec->x, userdata) && func (vec->y, userdata) )
    return TRUE;
  else
    return FALSE;
}

/**
 * crank_vec_uint2_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_uint2_iterator (CrankVecUint2    *vec,
                         CrankIterMemUint *iter)
{
  crank_iter_mem_uint_init_with_count (iter, (guint*)vec, 2);
}

//////// Basic operation ////////

/**
 * crank_vec_uint2_hash:
 * @a: (type CrankVecUint2): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_uint2_hash (gconstpointer a)
{
  const CrankVecUint2 *vec = a;
  guint hash;

  hash = g_direct_hash (GINT_TO_POINTER(vec->x));
  hash = g_direct_hash (GINT_TO_POINTER(vec->y)) + hash * 37;

  return hash;
}

/**
 * crank_vec_uint2_equal:
 * @a: (type CrankVecUint2): Vector to compare.
 * @b: (type CrankVecUint2): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_uint2_equal (gconstpointer a,
                      gconstpointer b)
{
  CrankVecUint2 *veca = (CrankVecUint2*)a;
  CrankVecUint2 *vecb = (CrankVecUint2*)b;

  return ((veca->x == vecb->x) && (veca->y == vecb->y));
}

/**
 * crank_vec_uint2_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_uint2_to_string (CrankVecUint2 *vec)
{
  return crank_vec_uint2_to_string_full (vec, "(", ", ", ")", "%d");
}

/**
 * crank_vec_uint2_to_string_full:
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
crank_vec_uint2_to_string_full (CrankVecUint2 *vec,
                               const gchar  *left,
                               const gchar  *in,
                               const gchar  *right,
                               const gchar  *format)
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
 * crank_vec_uint2_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
guint
crank_vec_uint2_get_magn_sq (CrankVecUint2 *vec)
{
  guint vx = (guint) ABS(vec->x);
  guint vy = (guint) ABS(vec->y);

  return (vx * vx) + (vy * vy);
}

/**
 * crank_vec_uint2_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_uint2_get_magn (CrankVecUint2 *vec)
{
  gfloat sq = (gfloat) crank_vec_uint2_get_magn_sq (vec);
  return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_uint2_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_uint2_neg (CrankVecUint2 *a,
                    CrankVecUint2 *r)
{
  r->x = -(a->x);
  r->y = -(a->y);
}

/**
 * crank_vec_uint2_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_uint2_neg_self (CrankVecUint2 *a)
{
  a->x = -(a->x);
  a->y = -(a->y);
}



//////// Scalar operations ////////

/**
 * crank_vec_uint2_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_uint2_muls (CrankVecUint2 *a,
                      const guint    b,
                      CrankVecUint2 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x * b;
  r->y = a->y * b;
}

/**
 * crank_vec_uint2_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_uint2_muls_self (CrankVecUint2 *a,
                           const guint    b)
{
  a->x *= b;
  a->y *= b;
}

/**
 * crank_vec_uint2_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_uint2_divs (CrankVecUint2 *a,
                      const guint    b,
                      CrankVecUint2 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x / b;
  r->y = a->y / b;
}

/**
 * crank_vec_uint2_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_uint2_divs_self (CrankVecUint2 *a,
                           const guint    b)
{
  a->x /= b;
  a->y /= b;
}


/**
 * crank_vec_uint2_mods:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Gets modular of each component.
 */
void
crank_vec_uint2_mods (CrankVecUint2 *a,
                      const guint    b,
                      CrankVecUint2 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x % b;
  r->y = a->y % b;
}
/**
 * crank_vec_uint2_mods_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies modular of each component.
 */
void
crank_vec_uint2_mods_self (CrankVecUint2 *a,
                           const guint    b)
{
  a->x %= b;
  a->y %= b;
}

//////// Standard vector operations ////////

/**
 * crank_vec_uint2_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_uint2_add (CrankVecUint2 *a,
                     CrankVecUint2 *b,
                     CrankVecUint2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x + b->x;
  r->y = a->y + b->y;
}

/**
 * crank_vec_uint2_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Applies addition to a vector.
 */
void
crank_vec_uint2_add_self (CrankVecUint2 *a,
                         CrankVecUint2 *b)
{
  a->x += b->x;
  a->y += b->y;
}

/**
 * crank_vec_uint2_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_uint2_sub (CrankVecUint2 *a,
                    CrankVecUint2 *b,
                    CrankVecUint2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x - b->x;
  r->y = a->y - b->y;
}

/**
 * crank_vec_uint2_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Applies subtraction to a vector.
 */
void
crank_vec_uint2_sub_self (CrankVecUint2 *a,
                         CrankVecUint2 *b)
{
  a->x -= b->x;
  a->y -= b->y;
}

/**
 * crank_vec_uint2_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
guint
crank_vec_uint2_dot (CrankVecUint2 *a,
                     CrankVecUint2 *b)
{
  return (a->x) * (b->x) + (a->y) * (b->y);
}
//////// Component vector operations ////////

/**
 * crank_vec_uint2_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_uint2_cmpmul (CrankVecUint2 *a,
                       CrankVecUint2 *b,
                       CrankVecUint2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x * b->x;
  r->y = a->y * b->y;
}

/**
 * crank_vec_uint2_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Applies component-wise multiplication on a vector.
 */
void
crank_vec_uint2_cmpmul_self (CrankVecUint2 *a,
                            CrankVecUint2 *b)
{
  a->x *= b->x;
  a->y *= b->y;
}


/**
 * crank_vec_uint2_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise division.
 */
void
crank_vec_uint2_cmpdiv (CrankVecUint2 *a,
                       CrankVecUint2 *b,
                       CrankVecUint2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x / b->x;
  r->y = a->y / b->y;
}

/**
 * crank_vec_uint2_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Applies component-wise division on a vector.
 */
void
crank_vec_uint2_cmpdiv_self (CrankVecUint2 *a,
                            CrankVecUint2 *b)
{
  a->x /= b->x;
  a->y /= b->y;
}

/**
 * crank_vec_uint2_cmpmod:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise modular.
 */
void
crank_vec_uint2_cmpmod (CrankVecUint2 *a,
                       CrankVecUint2 *b,
                       CrankVecUint2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x % b->x;
  r->y = a->y % b->y;
}

/**
 * crank_vec_uint2_cmpmod_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Applies component-wise modular on a vector.
 */
void
crank_vec_uint2_cmpmod_self (CrankVecUint2 *a,
                            CrankVecUint2 *b)
{
  a->x %= b->x;
  a->y %= b->y;
}

/**
 * crank_vec_uint2_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_uint2_cmpless (CrankVecUint2  *a,
                        CrankVecUint2  *b,
                        CrankVecBool2 *r)
{
  r->x = (a->x) < (b->x);
  r->y = (a->y) < (b->y);
}

/**
 * crank_vec_uint2_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_uint2_cmpeq (CrankVecUint2  *a,
                       CrankVecUint2  *b,
                       CrankVecBool2 *r)
{
  r->x = (a->x) == (b->x);
  r->y = (a->y) == (b->y);
}

/**
 * crank_vec_uint2_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is greater than counterpart of @b
 */
void
crank_vec_uint2_cmpgreater (CrankVecUint2  *a,
                           CrankVecUint2  *b,
                           CrankVecBool2 *r)
{
  r->x = (a->x) > (b->x);
  r->y = (a->y) > (b->y);
}

/**
 * crank_vec_uint2_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets compare result of each components.
 */
void
crank_vec_uint2_cmpcmp (CrankVecUint2 *a,
                        CrankVecUint2 *b,
                        CrankVecInt2 *r)
{
  r->x = CMP(a->x, b->x);
  r->y = CMP(a->y, b->y);
}

/**
 * crank_vec_uint2_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_uint2_min (CrankVecUint2 *a,
                    CrankVecUint2 *b,
                    CrankVecUint2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MIN (a->x, b->x);
  r->y = MIN (a->y, b->y);
}

/**
 * crank_vec_uint2_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_uint2_max (CrankVecUint2 *a,
                    CrankVecUint2 *b,
                    CrankVecUint2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MAX (a->x, b->x);
  r->y = MAX (a->y, b->y);
}



//////// GValue Transformation /////////////////////////////////////////////////

static void
crank_vec_uint2_transform_from_b (const GValue *src,
                                 GValue       *dest)
{
  CrankVecUint2 *vi = g_new (CrankVecUint2, 1);
  CrankVecBool2 *vb = (CrankVecBool2*) g_value_get_boxed (src);
  crank_vec_uint2_init_from_vb (vi, vb);
  g_value_take_boxed (dest, vi);
}

static void
crank_vec_uint2_transform_to_string (const GValue *src,
                                    GValue       *dest)
{
  CrankVecUint2 *vi = (CrankVecUint2*) g_value_get_boxed (src);
  gchar *str = crank_vec_uint2_to_string (vi);
  g_value_take_string (dest, str);
}







static void crank_vec_uint3_transform_from_b (const GValue *src,
                                             GValue       *dest);

static void crank_vec_uint3_transform_to_string (const GValue *src,
                                                GValue       *dest);

G_DEFINE_BOXED_TYPE_WITH_CODE (
  CrankVecUint3,
  crank_vec_uint3,
  crank_vec_uint3_dup,
  g_free,
  {
    g_value_register_transform_func (CRANK_TYPE_VEC_BOOL3,
                                     g_define_type_id,
                                     crank_vec_uint3_transform_from_b);

    g_value_register_transform_func (g_define_type_id,
                                     G_TYPE_STRING,
                                     crank_vec_uint3_transform_to_string);
  })

/**
 * crank_vec_uint3_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_uint3_init (CrankVecUint3 *vec,
                      const guint    x,
                      const guint    y,
                      const guint    z)
{
  vec->x = x;
  vec->y = y;
  vec->z = z;
}

/**
 * crank_vec_uint3_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=3): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_uint3_init_arr (CrankVecUint3 *vec,
                          guint         *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
  vec->z = arr[2];
}

/**
 * crank_vec_uint3_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_uint3_init_valist (CrankVecUint3 *vec,
                            va_list       varargs)
{
  vec->x = va_arg (varargs, gint);
  vec->y = va_arg (varargs, gint);
  vec->z = va_arg (varargs, gint);
}

/**
 * crank_vec_uint3_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_uint3_init_fill (CrankVecUint3 *vec,
                           const guint    fill)
{
  vec->x = fill;
  vec->y = fill;
  vec->z = fill;
}

/**
 * crank_vec_uint3_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_uint3_init_from_vb (CrankVecUint3  *vec,
                             CrankVecBool3 *vb)
{
  vec->x = vb->x ? 1 : 0;
  vec->y = vb->y ? 1 : 0;
  vec->z = vb->z ? 1 : 0;
}


/**
 * crank_vec_uint3_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_uint3_copy (CrankVecUint3 *vec,
                     CrankVecUint3 *other)
{
  memcpy (other, vec, sizeof (CrankVecUint3));
}


/**
 * crank_vec_uint3_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecUint3*
crank_vec_uint3_dup (CrankVecUint3 *vec)
{
  return (CrankVecUint3*) g_memdup (vec, sizeof (CrankVecUint3));
}

/**
 * crank_vec_uint3_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
guint
crank_vec_uint3_get (CrankVecUint3 *vec,
                     const guint   index)
{
  return ((gint*)vec)[index];
}

/**
 * crank_vec_uint3_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_uint3_set (CrankVecUint3 *vec,
                     const guint    index,
                     const guint    value)
{
  ((gint*)vec)[index] = value;
}

/**
 * crank_vec_uint3_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a int vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_uint3_foreach (CrankVecUint3    *vec,
                        CrankBoolUintFunc func,
                        gpointer         userdata)
{
  if (func (vec->x, userdata) &&
      func (vec->y, userdata) &&
      func (vec->z, userdata) )
    return TRUE;
  else
    return FALSE;
}

/**
 * crank_vec_uint3_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_uint3_iterator (CrankVecUint3    *vec,
                         CrankIterMemUint *iter)
{
  crank_iter_mem_uint_init_with_count (iter, (guint*)vec, 3);
}

//////// Basic operation ////////

/**
 * crank_vec_uint3_hash:
 * @a: (type CrankVecUint3): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_uint3_hash (gconstpointer a)
{
  const CrankVecUint3 *vec = a;
  guint hash;

  hash = g_direct_hash (GINT_TO_POINTER(vec->x));
  hash = g_direct_hash (GINT_TO_POINTER(vec->y)) + hash * 37;
  hash = g_direct_hash (GINT_TO_POINTER(vec->z)) + hash * 37;

  return hash;
}

/**
 * crank_vec_uint3_equal:
 * @a: (type CrankVecUint3): Vector to compare.
 * @b: (type CrankVecUint3): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_uint3_equal (gconstpointer a,
                      gconstpointer b)
{
  CrankVecUint3 *veca = (CrankVecUint3*)a;
  CrankVecUint3 *vecb = (CrankVecUint3*)b;

  return ((veca->x == vecb->x) &&
          (veca->y == vecb->y) &&
          (veca->z == vecb->z));
}

/**
 * crank_vec_uint3_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4, 5)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_uint3_to_string (CrankVecUint3 *vec)
{
  return crank_vec_uint3_to_string_full (vec, "(", ", ", ")", "%d");
}

/**
 * crank_vec_uint3_to_string_full:
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
crank_vec_uint3_to_string_full (CrankVecUint3 *vec,
                               const gchar  *left,
                               const gchar  *in,
                               const gchar  *right,
                               const gchar  *format)
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
 * crank_vec_uint3_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
guint
crank_vec_uint3_get_magn_sq (CrankVecUint3 *vec)
{
  guint vx = (guint) ABS(vec->x);
  guint vy = (guint) ABS(vec->y);
  guint vz = (guint) ABS(vec->z);

  return (vx * vx) + (vy * vy) + (vz * vz);
}

/**
 * crank_vec_uint3_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_uint3_get_magn (CrankVecUint3 *vec)
{
  gfloat sq = (gfloat) crank_vec_uint3_get_magn_sq (vec);
  return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_uint3_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_uint3_neg (CrankVecUint3 *a,
                    CrankVecUint3 *r)
{
  r->x = -(a->x);
  r->y = -(a->y);
  r->z = -(a->z);
}

/**
 * crank_vec_uint3_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_uint3_neg_self (CrankVecUint3 *a)
{
  a->x = -(a->x);
  a->y = -(a->y);
  a->z = -(a->z);
}



//////// Scalar operations ////////

/**
 * crank_vec_uint3_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_uint3_muls (CrankVecUint3 *a,
                      const guint    b,
                      CrankVecUint3 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x * b;
  r->y = a->y * b;
  r->z = a->z * b;
}

/**
 * crank_vec_uint3_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication on a vector.
 */
void
crank_vec_uint3_muls_self (CrankVecUint3 *a,
                           const guint    b)
{
  a->x *= b;
  a->y *= b;
  a->z *= b;
}

/**
 * crank_vec_uint3_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_uint3_divs (CrankVecUint3 *a,
                      const guint    b,
                      CrankVecUint3 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x / b;
  r->y = a->y / b;
  r->z = a->z / b;
}

/**
 * crank_vec_uint3_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division on a vector.
 */
void
crank_vec_uint3_divs_self (CrankVecUint3 *a,
                           const guint    b)
{
  a->x /= b;
  a->y /= b;
  a->z /= b;
}

/**
 * crank_vec_uint3_mods:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Gets modular of each component.
 */
void
crank_vec_uint3_mods (CrankVecUint3 *a,
                      const guint    b,
                      CrankVecUint3 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x % b;
  r->y = a->y % b;
  r->z = a->z % b;
}

/**
 * crank_vec_uint3_mods_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies modular on a vector.
 */
void
crank_vec_uint3_mods_self (CrankVecUint3 *a,
                           const guint    b)
{
  a->x %= b;
  a->y %= b;
  a->z %= b;
}

//////// Standard vector operations ////////

/**
 * crank_vec_uint3_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_uint3_add (CrankVecUint3 *a,
                    CrankVecUint3 *b,
                    CrankVecUint3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x + b->x;
  r->y = a->y + b->y;
  r->z = a->z + b->z;
}

/**
 * crank_vec_uint3_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_uint3_add_self (CrankVecUint3 *a,
                         CrankVecUint3 *b)
{
  a->x += b->x;
  a->y += b->y;
  a->z += b->z;
}

/**
 * crank_vec_uint3_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_uint3_sub (CrankVecUint3 *a,
                    CrankVecUint3 *b,
                    CrankVecUint3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x - b->x;
  r->y = a->y - b->y;
  r->z = a->z - b->z;
}

/**
 * crank_vec_uint3_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_uint3_sub_self (CrankVecUint3 *a,
                         CrankVecUint3 *b)
{
  a->x -= b->x;
  a->y -= b->y;
  a->z -= b->z;
}

/**
 * crank_vec_uint3_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
guint
crank_vec_uint3_dot (CrankVecUint3 *a,
                     CrankVecUint3 *b)
{
  return (a->x) * (b->x) +
         (a->y) * (b->y) +
         (a->z) * (b->z);
}

/**
 * crank_vec_uint3_crs:
 * @a: A vector
 * @b: A vector
 * @r: (out): A vector to store result.
 *
 * Gets cross product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
void
crank_vec_uint3_crs (CrankVecUint3 *a,
                    CrankVecUint3 *b,
                    CrankVecUint3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  guint nx = (a->y * b->z) - (a->z * b->y);
  guint ny = (a->z * b->x) - (a->x * b->z);
  guint nz = (a->x * b->y) - (a->y * b->x);

  r->x = nx;
  r->y = ny;
  r->z = nz;
}

/**
 * crank_vec_uint3_crs_self:
 * @a: A vector
 * @b: A vector
 *
 * Gets cross product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
void
crank_vec_uint3_crs_self (CrankVecUint3 *a,
                         CrankVecUint3 *b)
{
  guint nx = (a->y * b->z) - (a->z * b->y);
  guint ny = (a->z * b->x) - (a->x * b->z);
  guint nz = (a->x * b->y) - (a->y * b->x);

  a->x = nx;
  a->y = ny;
  a->z = nz;
}



//////// Component vector operations ////////

/**
 * crank_vec_uint3_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_uint3_cmpmul (CrankVecUint3 *a,
                       CrankVecUint3 *b,
                       CrankVecUint3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x * b->x;
  r->y = a->y * b->y;
  r->z = a->z * b->z;
}

/**
 * crank_vec_uint3_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_uint3_cmpmul_self (CrankVecUint3 *a,
                            CrankVecUint3 *b)
{
  a->x *= b->x;
  a->y *= b->y;
  a->z *= b->z;
}


/**
 * crank_vec_uint3_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise division.
 */
void
crank_vec_uint3_cmpdiv (CrankVecUint3 *a,
                       CrankVecUint3 *b,
                       CrankVecUint3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x / b->x;
  r->y = a->y / b->y;
  r->z = a->z / b->z;
}

/**
 * crank_vec_uint3_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise division.
 */
void
crank_vec_uint3_cmpdiv_self (CrankVecUint3 *a,
                            CrankVecUint3 *b)
{
  a->x /= b->x;
  a->y /= b->y;
  a->z /= b->z;
}

/**
 * crank_vec_uint3_cmpmod:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise modular.
 */
void
crank_vec_uint3_cmpmod (CrankVecUint3 *a,
                       CrankVecUint3 *b,
                       CrankVecUint3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x % b->x;
  r->y = a->y % b->y;
  r->z = a->z % b->z;
}

/**
 * crank_vec_uint3_cmpmod_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise modular.
 */
void
crank_vec_uint3_cmpmod_self (CrankVecUint3 *a,
                            CrankVecUint3 *b)
{
  a->x %= b->x;
  a->y %= b->y;
  a->z %= b->z;
}

/**
 * crank_vec_uint3_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_uint3_cmpless (CrankVecUint3  *a,
                        CrankVecUint3  *b,
                        CrankVecBool3 *r)
{
  r->x = (a->x) < (b->x);
  r->y = (a->y) < (b->y);
  r->z = (a->z) < (b->z);
}

/**
 * crank_vec_uint3_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_uint3_cmpeq (CrankVecUint3  *a,
                      CrankVecUint3  *b,
                      CrankVecBool3 *r)
{
  r->x = (a->x) == (b->x);
  r->y = (a->y) == (b->y);
  r->z = (a->z) == (b->z);
}

/**
 * crank_vec_uint3_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is greater than counterpart of @b
 */
void
crank_vec_uint3_cmpgreater (CrankVecUint3  *a,
                           CrankVecUint3  *b,
                           CrankVecBool3 *r)
{
  r->x = (a->x) > (b->x);
  r->y = (a->y) > (b->y);
  r->z = (a->z) > (b->z);
}

/**
 * crank_vec_uint3_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets compare result of each components.
 */
void
crank_vec_uint3_cmpcmp (CrankVecUint3 *a,
                        CrankVecUint3 *b,
                        CrankVecInt3  *r)
{
  r->x = CMP(a->x, b->x);
  r->y = CMP(a->y, b->y);
  r->z = CMP(a->z, b->z);
}

/**
 * crank_vec_uint3_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_uint3_min (CrankVecUint3 *a,
                    CrankVecUint3 *b,
                    CrankVecUint3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MIN (a->x, b->x);
  r->y = MIN (a->y, b->y);
  r->z = MIN (a->z, b->z);
}

/**
 * crank_vec_uint3_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_uint3_max (CrankVecUint3 *a,
                    CrankVecUint3 *b,
                    CrankVecUint3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MAX (a->x, b->x);
  r->y = MAX (a->y, b->y);
  r->z = MAX (a->z, b->z);
}

//////// GValue Transformation /////////////////////////////////////////////////

static void
crank_vec_uint3_transform_from_b (const GValue *src,
                                 GValue       *dest)
{
  CrankVecUint3 *vi = g_new (CrankVecUint3, 1);
  CrankVecBool3 *vb = (CrankVecBool3*) g_value_get_boxed (src);

  crank_vec_uint3_init_from_vb (vi, vb);
  g_value_take_boxed (dest, vi);
}

static void
crank_vec_uint3_transform_to_string (const GValue *src,
                                    GValue       *dest)
{
  CrankVecUint3 *vi = (CrankVecUint3*) g_value_get_boxed (src);
  gchar *str = crank_vec_uint3_to_string (vi);
  g_value_take_string (dest, str);
}








static void crank_vec_uint4_transform_from_b (const GValue *src,
                                             GValue       *dest);

static void crank_vec_uint4_transform_to_string (const GValue *src,
                                                GValue       *dest);

G_DEFINE_BOXED_TYPE_WITH_CODE (
  CrankVecUint4,
  crank_vec_uint4,
  crank_vec_uint4_dup,
  g_free,
  {
    g_value_register_transform_func (CRANK_TYPE_VEC_BOOL4,
                                     g_define_type_id,
                                     crank_vec_uint4_transform_from_b);

    g_value_register_transform_func (g_define_type_id,
                                     G_TYPE_STRING,
                                     crank_vec_uint4_transform_to_string);
  })

/**
 * crank_vec_uint4_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 * @w: Fourth vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_uint4_init (CrankVecUint4 *vec,
                      const guint    x,
                      const guint    y,
                      const guint    z,
                      const guint    w)
{
  vec->x = x;
  vec->y = y;
  vec->z = z;
  vec->w = w;
}

/**
 * crank_vec_uint4_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=4): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_uint4_init_arr (CrankVecUint4 *vec,
                          guint         *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
  vec->z = arr[2];
  vec->w = arr[3];
}

/**
 * crank_vec_uint4_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_uint4_init_valist (CrankVecUint4 *vec,
                            va_list       varargs)
{
  vec->x = va_arg (varargs, gint);
  vec->y = va_arg (varargs, gint);
  vec->z = va_arg (varargs, gint);
  vec->w = va_arg (varargs, gint);
}

/**
 * crank_vec_uint4_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_uint4_init_fill (CrankVecUint4 *vec,
                           const guint    fill)
{
  vec->x = fill;
  vec->y = fill;
  vec->z = fill;
  vec->w = fill;
}

/**
 * crank_vec_uint4_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_uint4_init_from_vb (CrankVecUint4  *vec,
                              CrankVecBool4 *vb)
{
  vec->x = vb->x ? 1 : 0;
  vec->y = vb->y ? 1 : 0;
  vec->z = vb->z ? 1 : 0;
  vec->w = vb->w ? 1 : 0;
}


/**
 * crank_vec_uint4_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_uint4_copy (CrankVecUint4 *vec,
                      CrankVecUint4 *other)
{
  memcpy (other, vec, sizeof (CrankVecUint4));
}


/**
 * crank_vec_uint4_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecUint4*
crank_vec_uint4_dup (CrankVecUint4 *vec)
{
  return (CrankVecUint4*) g_memdup (vec, sizeof (CrankVecUint4));
}

/**
 * crank_vec_uint4_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
guint
crank_vec_uint4_get (CrankVecUint4 *vec,
                     const guint   index)
{
  return ((gint*)vec)[index];
}

/**
 * crank_vec_uint4_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_uint4_set (CrankVecUint4 *vec,
                     const guint   index,
                     const guint   value)
{
  ((gint*)vec)[index] = value;
}

/**
 * crank_vec_uint4_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a int vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_uint4_foreach (CrankVecUint4    *vec,
                        CrankBoolUintFunc func,
                        gpointer         userdata)
{
  if (func (vec->x, userdata) &&
      func (vec->y, userdata) &&
      func (vec->z, userdata) &&
      func (vec->w, userdata) )
    return TRUE;
  else
    return FALSE;
}

/**
 * crank_vec_uint4_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_uint4_iterator (CrankVecUint4    *vec,
                         CrankIterMemUint *iter)
{
  crank_iter_mem_uint_init_with_count (iter, (guint*)vec, 4);
}

//////// Basic operation ////////

/**
 * crank_vec_uint4_hash:
 * @a: (type CrankVecUint4): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_uint4_hash (gconstpointer a)
{
  const CrankVecUint4 *vec = a;
  guint hash;

  hash = g_direct_hash (GINT_TO_POINTER(vec->x));
  hash = g_direct_hash (GINT_TO_POINTER(vec->y)) + hash * 37;
  hash = g_direct_hash (GINT_TO_POINTER(vec->z)) + hash * 37;
  hash = g_direct_hash (GINT_TO_POINTER(vec->w)) + hash * 37;

  return hash;
}

/**
 * crank_vec_uint4_equal:
 * @a: (type CrankVecUint4): Vector to compare.
 * @b: (type CrankVecUint4): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_uint4_equal (gconstpointer a,
                      gconstpointer b)
{
  CrankVecUint4 *veca = (CrankVecUint4*)a;
  CrankVecUint4 *vecb = (CrankVecUint4*)b;

  return ((veca->x == vecb->x) &&
          (veca->y == vecb->y) &&
          (veca->z == vecb->z) &&
          (veca->w == vecb->w));
}

/**
 * crank_vec_uint4_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4, 5, 6)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_uint4_to_string (CrankVecUint4 *vec)
{
  return crank_vec_uint4_to_string_full (vec, "(", ", ", ")", "%d");
}

/**
 * crank_vec_uint4_to_string_full:
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
crank_vec_uint4_to_string_full (CrankVecUint4 *vec,
                               const gchar  *left,
                               const gchar  *in,
                               const gchar  *right,
                               const gchar  *format)
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
 * crank_vec_uint4_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
guint
crank_vec_uint4_get_magn_sq (CrankVecUint4 *vec)
{
  guint vx = (guint) ABS(vec->x);
  guint vy = (guint) ABS(vec->y);
  guint vz = (guint) ABS(vec->z);
  guint vw = (guint) ABS(vec->w);

  return (vx * vx) + (vy * vy) + (vz * vz) + (vw * vw);
}

/**
 * crank_vec_uint4_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_uint4_get_magn (CrankVecUint4 *vec)
{
  gfloat sq = (gfloat) crank_vec_uint4_get_magn_sq (vec);
  return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_uint4_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_uint4_neg (CrankVecUint4 *a,
                    CrankVecUint4 *r)
{
  r->x = -(a->x);
  r->y = -(a->y);
  r->z = -(a->z);
  r->w = -(a->w);
}

/**
 * crank_vec_uint4_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_uint4_neg_self (CrankVecUint4 *a)
{
  a->x = -(a->x);
  a->y = -(a->y);
  a->z = -(a->z);
  a->w = -(a->w);
}


//////// Scalar operations ////////

/**
 * crank_vec_uint4_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_uint4_muls (CrankVecUint4 *a,
                      const guint    b,
                      CrankVecUint4 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x * b;
  r->y = a->y * b;
  r->z = a->z * b;
  r->w = a->w * b;
}

/**
 * crank_vec_uint4_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_uint4_muls_self (CrankVecUint4 *a,
                           const guint    b)
{
  a->x *= b;
  a->y *= b;
  a->z *= b;
  a->w *= b;
}

/**
 * crank_vec_uint4_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_uint4_divs (CrankVecUint4 *a,
                      const guint    b,
                      CrankVecUint4 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x / b;
  r->y = a->y / b;
  r->z = a->z / b;
  r->w = a->w / b;
}

/**
 * crank_vec_uint4_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_uint4_divs_self (CrankVecUint4 *a,
                           const guint    b)
{
  a->x /= b;
  a->y /= b;
  a->z /= b;
  a->w /= b;
}

/**
 * crank_vec_uint4_mods:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Gets modular of each component.
 */
void
crank_vec_uint4_mods (CrankVecUint4 *a,
                      const guint    b,
                      CrankVecUint4 *r)
{
  g_return_if_fail (a != r);

  r->x = a->x % b;
  r->y = a->y % b;
  r->z = a->z % b;
  r->w = a->w % b;
}

/**
 * crank_vec_uint4_mods_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Gets modular of each component.
 */
void
crank_vec_uint4_mods_self (CrankVecUint4 *a,
                           const guint    b)
{
  a->x %= b;
  a->y %= b;
  a->z %= b;
  a->w %= b;
}

//////// Standard vector operations ////////

/**
 * crank_vec_uint4_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_uint4_add (CrankVecUint4 *a,
                    CrankVecUint4 *b,
                    CrankVecUint4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x + b->x;
  r->y = a->y + b->y;
  r->z = a->z + b->z;
  r->w = a->w + b->w;
}

/**
 * crank_vec_uint4_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_uint4_add_self (CrankVecUint4 *a,
                         CrankVecUint4 *b)
{
  a->x += b->x;
  a->y += b->y;
  a->z += b->z;
  a->w += b->w;
}

/**
 * crank_vec_uint4_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_uint4_sub (CrankVecUint4 *a,
                    CrankVecUint4 *b,
                    CrankVecUint4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x - b->x;
  r->y = a->y - b->y;
  r->z = a->z - b->z;
  r->w = a->w - b->w;
}

/**
 * crank_vec_uint4_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_uint4_sub_self (CrankVecUint4 *a,
                         CrankVecUint4 *b)
{
  a->x -= b->x;
  a->y -= b->y;
  a->z -= b->z;
  a->w -= b->w;
}

/**
 * crank_vec_uint4_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
guint
crank_vec_uint4_dot (CrankVecUint4 *a,
                     CrankVecUint4 *b)
{
  return (a->x) * (b->x) +
         (a->y) * (b->y) +
         (a->z) * (b->z) +
         (a->w) * (b->w);
}

//////// Component vector operations ////////

/**
 * crank_vec_uint4_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_uint4_cmpmul (CrankVecUint4 *a,
                       CrankVecUint4 *b,
                       CrankVecUint4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x * b->x;
  r->y = a->y * b->y;
  r->z = a->z * b->z;
  r->w = a->w * b->w;
}

/**
 * crank_vec_uint4_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_uint4_cmpmul_self (CrankVecUint4 *a,
                            CrankVecUint4 *b)
{
  a->x *= b->x;
  a->y *= b->y;
  a->z *= b->z;
  a->w *= b->w;
}

/**
 * crank_vec_uint4_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise division.
 */
void
crank_vec_uint4_cmpdiv (CrankVecUint4 *a,
                       CrankVecUint4 *b,
                       CrankVecUint4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x / b->x;
  r->y = a->y / b->y;
  r->z = a->z / b->z;
  r->w = a->w / b->w;
}

/**
 * crank_vec_uint4_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise division.
 */
void
crank_vec_uint4_cmpdiv_self (CrankVecUint4 *a,
                            CrankVecUint4 *b)
{
  a->x /= b->x;
  a->y /= b->y;
  a->z /= b->z;
  a->w /= b->w;
}

/**
 * crank_vec_uint4_cmpmod:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise modular.
 */
void
crank_vec_uint4_cmpmod (CrankVecUint4 *a,
                       CrankVecUint4 *b,
                       CrankVecUint4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x % b->x;
  r->y = a->y % b->y;
  r->z = a->z % b->z;
  r->w = a->w % b->w;
}

/**
 * crank_vec_uint4_cmpmod_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Gets component-wise modular.
 */
void
crank_vec_uint4_cmpmod_self (CrankVecUint4 *a,
                            CrankVecUint4 *b)
{
  a->x %= b->x;
  a->y %= b->y;
  a->z %= b->z;
  a->w %= b->w;
}

/**
 * crank_vec_uint4_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_uint4_cmpless (CrankVecUint4  *a,
                        CrankVecUint4  *b,
                        CrankVecBool4 *r)
{
  r->x = (a->x) < (b->x);
  r->y = (a->y) < (b->y);
  r->z = (a->z) < (b->z);
  r->w = (a->w) < (b->w);
}

/**
 * crank_vec_uint4_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_uint4_cmpeq (CrankVecUint4  *a,
                      CrankVecUint4  *b,
                      CrankVecBool4 *r)
{
  r->x = (a->x) == (b->x);
  r->y = (a->y) == (b->y);
  r->z = (a->z) == (b->z);
  r->w = (a->w) == (b->w);
}

/**
 * crank_vec_uint4_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is greater than counterpart of @b
 */
void
crank_vec_uint4_cmpgreater (CrankVecUint4  *a,
                           CrankVecUint4  *b,
                           CrankVecBool4 *r)
{
  r->x = (a->x) > (b->x);
  r->y = (a->y) > (b->y);
  r->z = (a->z) > (b->z);
  r->w = (a->w) > (b->w);
}

/**
 * crank_vec_uint4_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets compare result of each components.
 */
void
crank_vec_uint4_cmpcmp (CrankVecUint4 *a,
                        CrankVecUint4 *b,
                        CrankVecInt4 *r)
{
  r->x = CMP(a->x, b->x);
  r->y = CMP(a->y, b->y);
  r->z = CMP(a->z, b->z);
  r->w = CMP(a->w, b->w);
}

/**
 * crank_vec_uint4_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_uint4_min (CrankVecUint4 *a,
                    CrankVecUint4 *b,
                    CrankVecUint4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MIN (a->x, b->x);
  r->y = MIN (a->y, b->y);
  r->z = MIN (a->z, b->z);
  r->w = MIN (a->w, b->w);
}

/**
 * crank_vec_uint4_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_uint4_max (CrankVecUint4 *a,
                    CrankVecUint4 *b,
                    CrankVecUint4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = MAX (a->x, b->x);
  r->y = MAX (a->y, b->y);
  r->z = MAX (a->z, b->z);
  r->w = MAX (a->w, b->w);
}

//////// GValue Transformation /////////////////////////////////////////////////

static void
crank_vec_uint4_transform_from_b (const GValue *src,
                                 GValue       *dest)
{
  CrankVecUint4 *vi = g_new (CrankVecUint4, 1);
  CrankVecBool4 *vb = (CrankVecBool4*) g_value_get_boxed (src);
  crank_vec_uint4_init_from_vb (vi, vb);
  g_value_take_boxed (dest, vi);
}

static void
crank_vec_uint4_transform_to_string (const GValue *src,
                                    GValue       *dest)
{
  CrankVecUint4 *vi = (CrankVecUint4*) g_value_get_boxed (src);
  gchar *str = crank_vec_uint4_to_string (vi);
  g_value_take_string (dest, str);
}







static void crank_vec_uint_n_transform_from_b (const GValue *src,
                                              GValue       *dest);

static void crank_vec_uint_n_transform_from_v2 (const GValue *src,
                                               GValue       *dest);

static void crank_vec_uint_n_transform_from_v3 (const GValue *src,
                                               GValue       *dest);

static void crank_vec_uint_n_transform_from_v4 (const GValue *src,
                                               GValue       *dest);

static void crank_vec_uint_n_transform_to_string (const GValue *src,
                                                 GValue       *dest);


G_DEFINE_BOXED_TYPE_WITH_CODE (
  CrankVecUintN,
  crank_vec_uint_n,
  crank_vec_uint_n_dup,
  crank_vec_uint_n_free,
  {
    g_value_register_transform_func (CRANK_TYPE_VEC_BOOL_N,
                                     g_define_type_id,
                                     crank_vec_uint_n_transform_from_b);

    g_value_register_transform_func (CRANK_TYPE_VEC_INT2,
                                     g_define_type_id,
                                     crank_vec_uint_n_transform_from_v2);

    g_value_register_transform_func (CRANK_TYPE_VEC_INT3,
                                     g_define_type_id,
                                     crank_vec_uint_n_transform_from_v3);

    g_value_register_transform_func (CRANK_TYPE_VEC_INT4,
                                     g_define_type_id,
                                     crank_vec_uint_n_transform_from_v4);

    g_value_register_transform_func (g_define_type_id,
                                     G_TYPE_STRING,
                                     crank_vec_uint_n_transform_to_string);
  })

/**
 * crank_vec_uint_n_init:
 * @vec: (out): Vector to initialize.
 * @n: length of vector.
 * @...: elements of vector.
 *
 * Initializes vector with given components.
 */
void
crank_vec_uint_n_init (CrankVecUintN *vec,
                      const guint   n,
                      ...)
{
  va_list varargs;
  va_start (varargs, n);

  crank_vec_uint_n_init_valist (vec, n, varargs);

  va_end (varargs);
}

/**
 * crank_vec_uint_n_init_arr:
 * @vec: (out): Vector to initialize.
 * @n: length of vector
 * @arr: (array length=n): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_uint_n_init_arr (CrankVecUintN *vec,
                           const guint    n,
                           guint         *arr)
{
  vec->data = CRANK_ARRAY_DUP (arr, guint, n);
  vec->n = n;
}

/**
 * crank_vec_uint_n_init_valist:
 * @vec: (out): Vector to initialize.
 * @n: length of vector
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_uint_n_init_valist (CrankVecUintN *vec,
                             const guint   n,
                             va_list       varargs)
{
  guint i;

  CRANK_VEC_ALLOC(vec,guint,n);

  for (i = 0; i < n; i++)
    {
      vec->data[i] = va_arg (varargs, gint);
    }
}

/**
 * crank_vec_uint_n_init_fill:
 * @vec: (out): Vector to initialize.
 * @n: length of vector
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_uint_n_init_fill (CrankVecUintN *vec,
                            const guint    n,
                            const guint    fill)
{
  guint i;

  CRANK_VEC_ALLOC(vec,guint,n);

  for (i = 0; i < n; i++)
    {
      vec->data[i] = fill;
    }
}

/**
 * crank_vec_uint_n_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector, which has same length of it.
 */
void
crank_vec_uint_n_init_from_vb (CrankVecUintN  *vec,
                              CrankVecBoolN *vb)
{
  guint i;

  CRANK_VEC_ALLOC(vec,guint,vb->n);

  for (i = 0; i < vb->n; i++)
    {
      vec->data[i] = vb->data[i] ? 1 : 0;
    }
}

/**
 * crank_vec_uint_n_fini:
 * @vec: Vector to finalize.
 *
 * Finalize the datas and unset the vector, so that @vec will point 0-length data at %NULL.
 */
void
crank_vec_uint_n_fini (CrankVecUintN *vec)
{
  g_free (vec->data);
  vec->n = 0;
  vec->data = NULL;
}


/**
 * crank_vec_uint_n_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_uint_n_copy (CrankVecUintN *vec,
                      CrankVecUintN *other)
{
  crank_vec_uint_n_init_arr (other, vec->n, vec->data);
}

/**
 * crank_vec_uint_n_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecUintN*
crank_vec_uint_n_dup (CrankVecUintN *vec)
{
  CrankVecUintN *result = g_new0 (CrankVecUintN, 1);

  crank_vec_uint_n_init_arr (result, vec->n, vec->data);

  return result;
}

/**
 * crank_vec_uint_n_free:
 * @vec: Vector to free.
 *
 * Frees an allocated vector. Use with crank_vec_uint_n_dup().
 */
void
crank_vec_uint_n_free (CrankVecUintN *vec)
{
  crank_vec_uint_n_fini (vec);
  g_free (vec);
}

/**
 * crank_vec_uint_n_get_size:
 * @vec: Vector to get size.
 *
 * Gets size of vector.
 *
 * Returns: Size of vector.
 */
guint
crank_vec_uint_n_get_size (CrankVecUintN *vec)
{
  return vec->n;
}

/**
 * crank_vec_uint_n_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
guint
crank_vec_uint_n_get (CrankVecUintN *vec,
                      const guint   index)
{
  return vec->data[index];
}

/**
 * crank_vec_uint_n_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_uint_n_set (CrankVecUintN *vec,
                      const guint   index,
                      const guint   value)
{
  vec->data[index] = value;
}

/**
 * crank_vec_uint_n_prepend:
 * @vec: A Vector to insert element.
 * @value: Value of element.
 *
 * Prepends an element to vector.
 */
void
crank_vec_uint_n_prepend (CrankVecUintN *vec,
                          const guint    value)
{
  crank_vec_uint_n_insert (vec, 0, value);
}

/**
 * crank_vec_uint_n_append:
 * @vec: A Vector to insert element.
 * @value: Value of element.
 *
 * Appends an element to vector.
 */
void
crank_vec_uint_n_append (CrankVecUintN *vec,
                         const guint    value)
{
  crank_vec_uint_n_insert (vec, vec->n, value);
}

/**
 * crank_vec_uint_n_insert:
 * @vec: A Vector to insert element.
 * @index: Index to insert element.
 * @value: Value of element.
 *
 * Insert an element to vector.
 */
void
crank_vec_uint_n_insert (CrankVecUintN *vec,
                         const guint   index,
                         const guint   value)
{
  guint i = 0;

  g_return_if_fail (index <= vec->n);

  vec->data = g_renew (guint, vec->data, vec->n + 1);

  for (i = vec->n - 1; index <= i; i--)
    vec->data[i + 1] = vec->data[i];

  vec->data[index] = value;

  vec->n++;
}

/**
 * crank_vec_uint_n_remove:
 * @vec: A Vector to remove element.
 * @index: Index to remove element.
 *
 * Remove an element from vector.
 */
void
crank_vec_uint_n_remove (CrankVecUintN *vec,
                         const guint   index)
{
  guint i = 0;

  g_return_if_fail (index < vec->n);

  vec->n--;
  for (i = index; i < vec->n; i++)
    vec->data[i] = vec->data[i + 1];

  vec->data = g_renew (guint, vec->data, vec->n);
}

/**
 * crank_vec_uint_n_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a int vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_uint_n_foreach (CrankVecUintN    *vec,
                         CrankBoolUintFunc func,
                         gpointer         userdata)
{
  guint i;

  for (i = 0; i < vec->n; i++)
    if (!func(vec->data[i], userdata))
      return FALSE;

  return TRUE;
}

/**
 * crank_vec_uint_n_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_uint_n_iterator (CrankVecUintN    *vec,
                           CrankIterMemUint *iter)
{
  crank_iter_mem_uint_init_with_count (iter, vec->data, vec->n);
}

//////// Basic operation ////////

/**
 * crank_vec_uint_n_hash:
 * @a: (type CrankVecUintN): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_uint_n_hash (gconstpointer a)
{
  const CrankVecUintN *vec = a;
  guint hash = 0;

  guint i;

  for (i = 0; i < vec->n; i++)
    hash = (hash * 37) + g_direct_hash (GINT_TO_POINTER(vec->data[i]));

  return hash;
}

/**
 * crank_vec_uint_n_equal:
 * @a: (type CrankVecUintN): Vector to compare.
 * @b: (type CrankVecUintN): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean
crank_vec_uint_n_equal (gconstpointer a,
                       gconstpointer b)
{
  CrankVecUintN *veca = (CrankVecUintN*)a;
  CrankVecUintN *vecb = (CrankVecUintN*)b;

  guint i;

  for (i = 0; i < veca->n; i++)
    {
      if (veca->data[i] != vecb->data[i])
        return FALSE;
    }
  return TRUE;
}

/**
 * crank_vec_uint_n_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4, 5, 6)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_uint_n_to_string (CrankVecUintN *vec)
{
  return crank_vec_uint_n_to_string_full (vec, "(", ", ", ")", "%d");
}

/**
 * crank_vec_uint_n_to_string_full:
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
crank_vec_uint_n_to_string_full (CrankVecUintN *vec,
                                const gchar  *left,
                                const gchar  *in,
                                const gchar  *right,
                                const gchar  *format)
{
  GString *strb = g_string_new (left);
  gchar *result;

  guint i;

  if (0 < vec->n)
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
 * crank_vec_uint_n_is_zero:
 * @vec: A Vector.
 *
 * Checks whether the vector is "Zero vector", whose all components are 0.
 *
 * Returns: whether the vector is "zero vector".
 */
gboolean
crank_vec_uint_n_is_zero (CrankVecUintN *vec)
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
 * crank_vec_uint_n_is_one:
 * @vec: A Vector.
 *
 * Checks whether the vector has all components as 1. This kind of vectors are
 * often identity in component-wise operations.
 *
 * Returns: whether the vector has all component as 1.
 */
gboolean
crank_vec_uint_n_is_one (CrankVecUintN *vec)
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
 * crank_vec_uint_n_is_empty:
 * @vec: A Vector.
 *
 * Checks whether the vector is empty.
 *
 * Returns: whether the vector is empty.
 */
gboolean
crank_vec_uint_n_is_empty (CrankVecUintN *vec)
{
  return vec->n == 0;
}

//////// Standard vector property ///////

/**
 * crank_vec_uint_n_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
guint
crank_vec_uint_n_get_magn_sq (CrankVecUintN *vec)
{
  guint result = 0;
  guint i;

  for (i = 0; i < vec->n; i++)
    {
      guint u = (guint) ABS(vec->data[i]);
      result += u * u;
    }

  return result;
}

/**
 * crank_vec_uint_n_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_uint_n_get_magn (CrankVecUintN *vec)
{
  gfloat sq = (gfloat) crank_vec_uint_n_get_magn_sq (vec);
  return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_uint_n_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_uint_n_neg (CrankVecUintN *a,
                     CrankVecUintN *r)
{
  guint i;

  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = -a->data[i];
}

/**
 * crank_vec_uint_n_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_uint_n_neg_self (CrankVecUintN *a)
{
  guint i;
  for (i = 0; i < a->n; i++)
    a->data[i] = -a->data[i];
}



//////// Scalar operations ////////

/**
 * crank_vec_uint_n_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_uint_n_muls (CrankVecUintN *a,
                       const guint    b,
                       CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);

  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] * b;
}

/**
 * crank_vec_uint_n_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_uint_n_muls_self (CrankVecUintN *a,
                            const guint    b)
{
  guint i;
  for (i = 0; i < a->n; i++)
    a->data[i] *= b;
}

/**
 * crank_vec_uint_n_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_uint_n_divs (CrankVecUintN *a,
                       const guint    b,
                       CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] / b;
}

/**
 * crank_vec_uint_n_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_uint_n_divs_self (CrankVecUintN *a,
                            const guint    b)
{
  guint i;

  for (i = 0; i < a->n; i++)
    a->data[i] /= b;
}

/**
 * crank_vec_uint_n_mods:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Gets modular of each component.
 */
void
crank_vec_uint_n_mods (CrankVecUintN *a,
                       const guint    b,
                       CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] % b;
}

/**
 * crank_vec_uint_n_mods_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Gets modular of each component.
 */
void
crank_vec_uint_n_mods_self (CrankVecUintN *a,
                            const guint    b)
{
  guint i;
  for (i = 0; i < a->n; i++)
    a->data[i] %= b;
}

//////// Standard vector operations ////////

/**
 * crank_vec_uint_n_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_uint_n_add (CrankVecUintN *a,
                     CrankVecUintN *b,
                     CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "add", a, b);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] + b->data[i];
}
/**
 * crank_vec_uint_n_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_uint_n_add_self (CrankVecUintN *a,
                          CrankVecUintN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "add-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] += b->data[i];
}

/**
 * crank_vec_uint_n_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_uint_n_sub (CrankVecUintN *a,
                     CrankVecUintN *b,
                     CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "sub", a, b);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] - b->data[i];
}

/**
 * crank_vec_uint_n_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_uint_n_sub_self (CrankVecUintN *a,
                          CrankVecUintN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "sub-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] -= b->data[i];
}

/**
 * crank_vec_uint_n_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
guint
crank_vec_uint_n_dot (CrankVecUintN *a,
                      CrankVecUintN *b)
{
  gint result = 0;
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2_RET("VecIntN", "dot", a, b, 0.0f);

  for (i = 0; i < a->n; i++)
    result += (a->data[i] * b->data[i]);

  return result;
}

//////// Component vector operations ////////

/**
 * crank_vec_uint_n_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise multiplication.
 */
void
crank_vec_uint_n_cmpmul (CrankVecUintN *a,
                        CrankVecUintN *b,
                        CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpmul", a, b);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] * b->data[i];
}

/**
 * crank_vec_uint_n_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply component-wise multiplication.
 */
void
crank_vec_uint_n_cmpmul_self (CrankVecUintN *a,
                             CrankVecUintN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpmul-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] *= b->data[i];
}

/**
 * crank_vec_uint_n_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise division.
 */
void
crank_vec_uint_n_cmpdiv (CrankVecUintN *a,
                        CrankVecUintN *b,
                        CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpdiv", a, b);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] / b->data[i];
}

/**
 * crank_vec_uint_n_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply component-wise multiplication.
 */
void
crank_vec_uint_n_cmpdiv_self (CrankVecUintN *a,
                             CrankVecUintN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpdiv-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] /= b->data[i];
}

/**
 * crank_vec_uint_n_cmpmod:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets component-wise modular.
 */
void
crank_vec_uint_n_cmpmod (CrankVecUintN *a,
                        CrankVecUintN *b,
                        CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpmod", a, b);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] % b->data[i];
}

/**
 * crank_vec_uint_n_cmpmod_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply component-wise multiplication.
 */
void
crank_vec_uint_n_cmpmod_self (CrankVecUintN *a,
                             CrankVecUintN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpmod-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] %= b->data[i];
}

/**
 * crank_vec_uint_n_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_uint_n_cmpless (CrankVecUintN  *a,
                         CrankVecUintN  *b,
                         CrankVecBoolN *r)
{
  guint i;
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpless", a, b);
  CRANK_VEC_ALLOC(r,gboolean,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] < b->data[i];
}

/**
 * crank_vec_uint_n_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_uint_n_cmpeq (CrankVecUintN  *a,
                       CrankVecUintN  *b,
                       CrankVecBoolN *r)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpeq", a, b);
  CRANK_VEC_ALLOC(r,gboolean,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] == b->data[i];
}

/**
 * crank_vec_uint_n_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets each component of @a is greater than counterpart of @b
 */
void
crank_vec_uint_n_cmpgreater (CrankVecUintN  *a,
                            CrankVecUintN  *b,
                            CrankVecBoolN *r)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpgreater", a, b);
  CRANK_VEC_ALLOC(r,gboolean,a->n);

  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] > b->data[i];
}

/**
 * crank_vec_uint_n_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets compare result of each components.
 */
void
crank_vec_uint_n_cmpcmp (CrankVecUintN *a,
                        CrankVecUintN *b,
                        CrankVecIntN *r)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpcmp", a, b);
  CRANK_VEC_ALLOC(r,gint,a->n);

  for (i = 0; i < a->n; i++)
    {
      r->data[i] = CMP (a->data[i], b->data[i]);
    }
}

/**
 * crank_vec_uint_n_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_uint_n_min (CrankVecUintN *a,
                     CrankVecUintN *b,
                     CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "min", a, b);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    {
      r->data[i] = MIN (a->data[i], b->data[i]);
    }
}

/**
 * crank_vec_uint_n_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_uint_n_max (CrankVecUintN *a,
                     CrankVecUintN *b,
                     CrankVecUintN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "max", a, b);
  CRANK_VEC_ALLOC(r,guint,a->n);

  for (i = 0; i < a->n; i++)
    {
      r->data[i] = MAX (a->data[i], b->data[i]);
    }
}

//////// GValue Transformation /////////////////////////////////////////////////

static void
crank_vec_uint_n_transform_from_b (const GValue *src,
                                  GValue       *dest)
{
  CrankVecUintN *vi = g_new (CrankVecUintN, 1);
  CrankVecBoolN *vb = (CrankVecBoolN*) g_value_get_boxed (src);
  crank_vec_uint_n_init_from_vb (vi, vb);
  g_value_take_boxed (dest, vi);
}

static void
crank_vec_uint_n_transform_from_v2 (const GValue *src,
                                   GValue       *dest)
{
  CrankVecUintN *vi = g_new (CrankVecUintN, 1);
  guint *array = (guint*) g_value_get_boxed (src);

  crank_vec_uint_n_init_arr (vi, 2, array);
  g_value_take_boxed (dest, vi);
}

static void
crank_vec_uint_n_transform_from_v3 (const GValue *src,
                                   GValue       *dest)
{
  CrankVecUintN *vi = g_new (CrankVecUintN, 1);
  guint *array = (guint*) g_value_get_boxed (src);

  crank_vec_uint_n_init_arr (vi, 3, array);
  g_value_take_boxed (dest, vi);
}

static void
crank_vec_uint_n_transform_from_v4 (const GValue *src,
                                   GValue       *dest)
{
  CrankVecUintN *vi = g_new (CrankVecUintN, 1);
  guint *array = (guint*) g_value_get_boxed (src);

  crank_vec_uint_n_init_arr (vi, 4, array);
  g_value_take_boxed (dest, vi);
}

static void
crank_vec_uint_n_transform_to_string (const GValue *src,
                                     GValue       *dest)
{
  CrankVecUintN *vi = (CrankVecUintN*) g_value_get_boxed (src);
  gchar *str = crank_vec_uint_n_to_string (vi);
  g_value_take_string (dest, str);
}
