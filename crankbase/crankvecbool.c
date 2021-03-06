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

/**
 * SECTION: crankvecbool
 * @title: Boolean Vectors
 * @short_description: Vectors that have boolean elements.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Represents vectors that have boolean elements.
 *
 * In mathematics, %TRUE and %FALSE cannot be composed as elements of vector,
 * as they cannot form a field. As elements are #gboolean, 'Boolean vectors'
 * have differences from float vectors.
 *
 * * Boolean vectors have logical operations while float ones have airthmetic operations
 * * Boolean vectors have any, all property while float ones have magnitude/norm.
 *
 * Compared to bvec in GLSL.
 *
 * # Type Conversion.
 *
 * Boolean vector types are seldomly used, but for convenience, it can be
 * converted to numeric value type.
 *
 * For fixed-sized types, it can be converted to variadic sized vector types.
 *
 * <table><title>Type Conversion of #CrankVecBool2</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_bool2_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_bool2_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecBoolN.</entry>
 *             <entry>crank_vec_bool_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecBoolN</entry> </row>
 *
 *       <row> <entry>To #CrankVecInt2</entry>
 *             <entry>crank_vec_int2_init_from_vb()</entry>
 *             <entry>GValue Transform, Defined in #CrankVecInt2</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloat2.</entry>
 *             <entry>crank_vec_float2_init_from_vb()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecFloat2</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecBool3</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_bool3_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_bool3_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecBoolN.</entry>
 *             <entry>crank_vec_bool_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecBoolN</entry> </row>
 *
 *       <row> <entry>To #CrankVecInt3</entry>
 *             <entry>crank_vec_int3_init_from_vb()</entry>
 *             <entry>GValue Transform, Defined in #CrankVecInt3</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloat3.</entry>
 *             <entry>crank_vec_float3_init_from_vb()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecFloat3</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecBool4</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_bool4_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_bool4_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecBoolN.</entry>
 *             <entry>crank_vec_bool_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecBoolN</entry> </row>
 *
 *       <row> <entry>To #CrankVecInt4</entry>
 *             <entry>crank_vec_int4_init_from_vb()</entry>
 *             <entry>GValue Transform, Defined in #CrankVecInt4</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloat4.</entry>
 *             <entry>crank_vec_float4_init_from_vb()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecFloat4</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecBoolN</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool2</entry>
 *             <entry>crank_vec_bool_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>From #CrankVecBool3</entry>
 *             <entry>crank_vec_bool_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>From #CrankVecBool4</entry>
 *             <entry>crank_vec_bool_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>To #CrankVecIntN</entry>
 *             <entry>crank_vec_int_n_init_from_vb()</entry>
 *             <entry>GValue Transform, Defined in #CrankVecIntN</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_bool_n_to_string()</entry>
 *             <entry>GValue Transform</entry> </row>
 *       <row> <entry>crank_vec_bool_n_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecIntN.</entry>
 *             <entry>crank_vec_int_n_init_from_vb()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecIntN</entry> </row>
 *
 *       <row> <entry>To #CrankVecFloatN.</entry>
 *             <entry>crank_vec_float_n_init_from_vb()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecFloatN</entry> </row>
 *
 *       <row> <entry>To #CrankVecCplxFloatN.</entry>
 *             <entry>crank_vec_cplx_float_n_init_from_vb()</entry>
 *             <entry>GValue Transform,
 *                    Defined in #CrankVecCplxFloatN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankiter.h"
#include "crankbasemacro.h"
#include "crankveccommon.h"
#include "crankvecbool.h"



//////// GValue converter //////////////////////////////////////////////////////

static void crank_vec_bool2_transform_to_string (const GValue *src,
                                                 GValue       *dest);


G_DEFINE_BOXED_TYPE_WITH_CODE (CrankVecBool2,
                               crank_vec_bool2,
                               crank_vec_bool2_dup,
                               g_free,
                               {
                                 g_value_register_transform_func (
                                   g_define_type_id,
                                   G_TYPE_STRING,
                                   crank_vec_bool2_transform_to_string);
                               })


//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_vec_bool2_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 *
 * Initialize elements from arguments.
 */
void
crank_vec_bool2_init (CrankVecBool2 *vec,
                      gboolean       x,
                      gboolean       y)
{
  vec->x = x;
  vec->y = y;
}

/**
 * crank_vec_bool2_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=2): Array of elements.
 *
 * Initialize elements from array.
 */
void
crank_vec_bool2_init_arr (CrankVecBool2 *vec,
                          gboolean      *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
}

/**
 * crank_vec_bool2_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list of elements.
 *
 * Initialize elements from 2 variadic arguments.
 */
void
crank_vec_bool2_init_valist (CrankVecBool2 *vec,
                             va_list        varargs)
{
  vec->x = va_arg (varargs, gboolean);
  vec->y = va_arg (varargs, gboolean);
}

/**
 * crank_vec_bool2_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: Value to fill.
 *
 * Fill elements by @fill value.
 */
void
crank_vec_bool2_init_fill (CrankVecBool2 *vec,
                           const gboolean fill)
{
  vec->x = fill;
  vec->y = fill;
}


//////// Basic Operations //////////////////////////////////////////////////////


/**
 * crank_vec_bool2_copy:
 * @vec: Vector to copy
 * @other: (out): Other vector to paste.
 *
 * Copies a vector to other.
 */
void
crank_vec_bool2_copy (CrankVecBool2 *vec,
                      CrankVecBool2 *other)
{
  memcpy (other, vec, sizeof (CrankVecBool2));
}

/**
 * crank_vec_bool2_dup:
 * @vec: Vector to copy
 *
 * Copies a vector. Free with g_free () after use.
 *
 * Returns: (transfer full):  Copied vector. Free with g_free().
 */
CrankVecBool2*
crank_vec_bool2_dup (CrankVecBool2 *vec)
{
  return (CrankVecBool2*) g_memdup (vec, sizeof (CrankVecBool2));
}


/**
 * crank_vec_bool2_equal:
 * @a: (type CrankVecBool2): A vector.
 * @b: (type CrankVecBool2): A vector.
 *
 * Checks whether two vectors are equal.
 *
 * Returns: Whether two vectors are equal.
 */
gboolean
crank_vec_bool2_equal (gconstpointer a,
                       gconstpointer b)
{
  const CrankVecBool2 *veca = (const CrankVecBool2*) a;
  const CrankVecBool2 *vecb = (const CrankVecBool2*) b;

  return (veca->x == vecb->x) && (veca->y == vecb->y);
}


/**
 * crank_vec_bool2_hash:
 * @a: (type CrankVecBool2): A vector.
 *
 * Gets hash value of vector.
 *
 * Returns: Hash value of vector.
 */
guint
crank_vec_bool2_hash (gconstpointer a)
{
  const CrankVecBool2 *vec = (const CrankVecBool2*) a;

  return g_direct_hash (GINT_TO_POINTER((vec->x) + (vec->y << 1)));
}

/**
 * crank_vec_bool2_to_string:
 * @vec: A vector.
 *
 * Stringify a given vector.
 * The format will be. (for example of {TRUE, FALSE})
 * |[
 *   (true, false)
 * ]|
 *
 * Returns: String representation of vector.
 */
gchar*
crank_vec_bool2_to_string (CrankVecBool2 *vec)
{
  return crank_vec_bool2_to_string_full (vec, "(", ", ", ")", "true", "false");
}

/**
 * crank_vec_bool2_to_string_full:
 * @vec: A vector.
 * @left: Left delimiter.
 * @in: Middle delimiter that divides components.
 * @right: Right delimiter.
 * @on_true: String representation of %TRUE.
 * @on_false: String representation of %FALSE.
 *
 * Stringify a given vector with given string parts.
 * The order of part will be (for example of {TRUE, FALSE})
 * |[
 *   left on_true in on_false right
 * ]|
 *
 * Returns: String representation of vector.
 */
gchar*
crank_vec_bool2_to_string_full (CrankVecBool2 *vec,
                                const gchar   *left,
                                const gchar   *in,
                                const gchar   *right,
                                const gchar   *on_true,
                                const gchar   *on_false)
{
  return g_strdup_printf ("%s%s%s%s%s",
                          left,
                          vec->x ? on_true : on_false,
                          in,
                          vec->y ? on_true : on_false,
                          right);
}


//////// Basic Properties //////////////////////////////////////////////////////


/**
 * crank_vec_bool2_get_any:
 * @vec: A vector.
 *
 * Checks there is any element be %TRUE.
 *
 * Returns: Whether there is any element be %TRUE.
 */
gboolean
crank_vec_bool2_get_any (CrankVecBool2 *vec)
{
  return (vec->x || vec->y);
}

/**
 * crank_vec_bool2_get_all:
 * @vec: A vector.
 *
 * Checks whether all elements are %TRUE.
 *
 * Returns: Whether all elements are %TRUE.
 */
gboolean
crank_vec_bool2_get_all (CrankVecBool2 *vec)
{
  return (vec->x && vec->y);
}

/**
 * crank_vec_bool2_get_count:
 * @vec: A Vector.
 *
 * Gets count of %TRUE in this vector.
 *
 * Returns: Count of %TRUE.
 */
guint
crank_vec_bool2_get_count (CrankVecBool2 *vec)
{
  guint count = 0;
  if (vec->x)
    count++;
  if (vec->y)
    count++;

  return count;
}

/**
 * crank_vec_bool2_get_ratio:
 * @vec: A Vector.
 *
 * Gets ratio of %TRUE in this vector.
 *
 * Returns: Ratio of %TRUE.
 */
gfloat
crank_vec_bool2_get_ratio (CrankVecBool2 *vec)
{
  return crank_vec_bool2_get_count (vec) * 0.5f;
}


/**
 * crank_vec_bool2_foreach:
 * @vec: A vector
 * @func: (scope call): A function to iterate.
 * @userdata: (closure): A userdata for @func.
 *
 * Iterates over a boolean vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_bool2_foreach (CrankVecBool2    *vec,
                         CrankBoolBoolFunc func,
                         gpointer          userdata)
{
  if (func (vec->x, userdata) &&
      func (vec->y, userdata))
    return TRUE;
  else
    return FALSE;
}


/**
 * crank_vec_bool2_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for the vector.
 */
void
crank_vec_bool2_iterator (CrankVecBool2    *vec,
                          CrankIterMemBool *iter)
{
  crank_iter_mem_bool_init_with_count (iter, (gboolean*)vec, 2);
}

//////// Functions as collection ///////////////////////////////////////////////


/**
 * crank_vec_bool2_get:
 * @vec: A vector to get element.
 * @index: Index of element.
 *
 * Gets element from vector.
 *
 * Returns: Element of @vec at @index.
 */
gboolean
crank_vec_bool2_get (CrankVecBool2 *vec,
                     const guint    index)
{
  return ((gboolean*)vec)[index];
}

/**
 * crank_vec_bool2_set:
 * @vec: A vector to set element.
 * @index: Index of element.
 * @value: Element to set.
 *
 * Sets element in vector.
 */
void
crank_vec_bool2_set (CrankVecBool2 *vec,
                     const guint    index,
                     const gboolean value)
{
  ((gboolean*)vec)[index] = value;
}


//////// Vector - Vector Operations ////////////////////////////////////////////


/**
 * crank_vec_bool2_and:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component AND of @a and @b.
 */
void
crank_vec_bool2_and (CrankVecBool2 *a,
                     CrankVecBool2 *b,
                     CrankVecBool2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x && b->x;
  r->y = a->y && b->y;
}

/**
 * crank_vec_bool2_and_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component AND to @a.
 */
void
crank_vec_bool2_and_self (CrankVecBool2 *a,
                          CrankVecBool2 *b)
{
  a->x = a->x && b->x;
  a->y = a->y && b->y;
}


/**
 * crank_vec_bool2_or:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component OR of @a and @b.
 */
void
crank_vec_bool2_or (CrankVecBool2 *a,
                    CrankVecBool2 *b,
                    CrankVecBool2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x || b->x;
  r->y = a->y || b->y;
}

/**
 * crank_vec_bool2_or_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component OR to @a.
 */
void
crank_vec_bool2_or_self (CrankVecBool2 *a,
                         CrankVecBool2 *b)
{
  a->x = a->x || b->x;
  a->y = a->y || b->y;
}

/**
 * crank_vec_bool2_xor:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component XOR of @a and @b.
 */
void
crank_vec_bool2_xor (CrankVecBool2 *a,
                     CrankVecBool2 *b,
                     CrankVecBool2 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x != b->x;
  r->y = a->y != b->y;
}

/**
 * crank_vec_bool2_xor_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component XOR to @a.
 */
void
crank_vec_bool2_xor_self (CrankVecBool2 *a,
                          CrankVecBool2 *b)
{
  a->x = a->x != b->x;
  a->y = a->y != b->y;
}

/**
 * crank_vec_bool2_not:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component NOT of @a.
 */
void
crank_vec_bool2_not (CrankVecBool2 *a,
                     CrankVecBool2 *r)
{
  g_return_if_fail (a != r);

  r->x = !a->x;
  r->y = !a->y;
}

/**
 * crank_vec_bool2_not_self:
 * @a: A vector.
 *
 * Apply Component NOT to @a.
 */
void
crank_vec_bool2_not_self (CrankVecBool2 *a)
{
  a->x = !a->x;
  a->y = !a->y;
}

/**
 * crank_vec_bool2_andv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool2_and(). Some language may use "and" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool2_andv (CrankVecBool2 *a,
                      CrankVecBool2 *b,
                      CrankVecBool2 *r)
{
  crank_vec_bool2_and (a, b, r);
}

/**
 * crank_vec_bool2_orv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool2_and(). Some language may use "or" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool2_orv (CrankVecBool2 *a,
                     CrankVecBool2 *b,
                     CrankVecBool2 *r)
{
  crank_vec_bool2_or (a, b, r);
}

/**
 * crank_vec_bool2_notv:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool2_not(). Some language may use "not" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool2_notv (CrankVecBool2 *a,
                      CrankVecBool2 *r)
{
  crank_vec_bool2_not (a, r);
}

//////// GValue conversions ////////////////////////////////////////////////////

static void
crank_vec_bool2_transform_to_string (const GValue *src,
                                     GValue       *dest)
{
  CrankVecBool2 *vec = (CrankVecBool2*) g_value_get_boxed (src);
  gchar *str = crank_vec_bool2_to_string (vec);

  g_value_take_string (dest, str);
}






static void crank_vec_bool3_transform_to_string (const GValue *src,
                                                 GValue       *dest);


G_DEFINE_BOXED_TYPE_WITH_CODE (CrankVecBool3,
                               crank_vec_bool3,
                               crank_vec_bool3_dup,
                               g_free,
                               {
                                 g_value_register_transform_func (
                                   g_define_type_id,
                                   G_TYPE_STRING,
                                   crank_vec_bool3_transform_to_string);
                               })


//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_vec_bool3_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 *
 * Initialize elements from arguments.
 */
void
crank_vec_bool3_init (CrankVecBool3 *vec,
                      gboolean       x,
                      gboolean       y,
                      gboolean       z)
{
  vec->x = x;
  vec->y = y;
  vec->z = z;
}

/**
 * crank_vec_bool3_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=3): Array of elements.
 *
 * Initialize elements from array.
 */
void
crank_vec_bool3_init_arr (CrankVecBool3 *vec,
                          gboolean      *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
  vec->z = arr[2];
}

/**
 * crank_vec_bool3_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_lost of elements.
 *
 * Initialize elements from 3 variadic arguments.
 */
void
crank_vec_bool3_init_valist (CrankVecBool3 *vec,
                             va_list        varargs)
{
  vec->x = va_arg (varargs, gboolean);
  vec->y = va_arg (varargs, gboolean);
  vec->z = va_arg (varargs, gboolean);
}


/**
 * crank_vec_bool3_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: Value to fill.
 *
 * Fill elements by @fill value.
 */
void
crank_vec_bool3_init_fill (CrankVecBool3 *vec,
                           const gboolean fill)
{
  vec->x = fill;
  vec->y = fill;
  vec->z = fill;
}


//////// Basic Operations //////////////////////////////////////////////////////


/**
 * crank_vec_bool3_copy:
 * @vec: Vector to copy
 * @other: (out): Other vector to paste.
 *
 * Copies a vector.
 */
void
crank_vec_bool3_copy (CrankVecBool3 *vec,
                      CrankVecBool3 *other)
{
  memcpy (other, vec, sizeof (CrankVecBool3));
}

/**
 * crank_vec_bool3_dup:
 * @vec: Vector to copy
 *
 * Copies a vector. Free with g_free () after use.
 *
 * Returns: (transfer full):  Copied vector. Free with g_free().
 */
CrankVecBool3*
crank_vec_bool3_dup (CrankVecBool3 *vec)
{
  return (CrankVecBool3*) g_memdup (vec, sizeof (CrankVecBool3));
}

/**
 * crank_vec_bool3_equal:
 * @a: (type CrankVecBool3): A vector.
 * @b: (type CrankVecBool3): A vector.
 *
 * Checks whether two vectors are equal.
 *
 * Returns: Whether two vectors are equal.
 */
gboolean
crank_vec_bool3_equal (gconstpointer a,
                       gconstpointer b)
{
  const CrankVecBool3 *veca = (const CrankVecBool3*) a;
  const CrankVecBool3 *vecb = (const CrankVecBool3*) b;
  return (veca->x == vecb->x) &&
         (veca->y == vecb->y) &&
         (veca->z == vecb->z);
}

/**
 * crank_vec_bool3_hash:
 * @a: (type CrankVecBool3): A vector.
 *
 * Gets hash value of vector.
 *
 * Returns: Hash value of vector.
 */
guint
crank_vec_bool3_hash (gconstpointer a)
{
  const CrankVecBool3 *vec = (const CrankVecBool3*) a;
  return g_direct_hash (
    GINT_TO_POINTER(    (vec->x) +
                        (vec->y << 1) +
                        (vec->z << 2)   ));
}

/**
 * crank_vec_bool3_to_string:
 * @vec: A vector.
 *
 * Stringify a given vector.
 * The format will be. (for example of {TRUE, FALSE, FALSE})
 * |[
 *   (true, false, false)
 * ]|
 *
 * Returns: String representation of vector.
 */
gchar*
crank_vec_bool3_to_string (CrankVecBool3 *vec)
{
  return crank_vec_bool3_to_string_full (vec, "(", ", ", ")", "true", "false");
}

/**
 * crank_vec_bool3_to_string_full:
 * @vec: A vector.
 * @left: Left delimiter.
 * @in: Middle delimiter that divides components.
 * @right: Right delimiter.
 * @on_true: String representation of %TRUE.
 * @on_false: String representation of %FALSE.
 *
 * Stringify a given vector with given string parts.
 * The order of part will be (for example of {TRUE, FALSE, FALSE})
 * |[
 *   left on_true in on_false in on_false right
 * ]|
 *
 * Returns: String representation of vector.
 */
gchar*
crank_vec_bool3_to_string_full (CrankVecBool3 *vec,
                                const gchar   *left,
                                const gchar   *in,
                                const gchar   *right,
                                const gchar   *on_true,
                                const gchar   *on_false)
{
  return g_strdup_printf ("%s%s%s%s%s%s%s",
                          left,
                          vec->x ? on_true : on_false,
                          in,
                          vec->y ? on_true : on_false,
                          in,
                          vec->z ? on_true : on_false,
                          right);
}


//////// Basic Properties //////////////////////////////////////////////////////


/**
 * crank_vec_bool3_get_any:
 * @vec: A vector.
 *
 * Checks there is any element be %TRUE.
 *
 * Returns: Whether there is any element be %TRUE.
 */
gboolean
crank_vec_bool3_get_any (CrankVecBool3 *vec)
{
  return (vec->x || vec->y || vec->z);
}

/**
 * crank_vec_bool3_get_all:
 * @vec: A vector.
 *
 * Checks whether all elements are %TRUE.
 *
 * Returns: Whether all elements are %TRUE.
 */
gboolean
crank_vec_bool3_get_all (CrankVecBool3 *vec)
{
  return (vec->x && vec->y && vec->z);
}

/**
 * crank_vec_bool3_get_count:
 * @vec: A Vector.
 *
 * Gets count of %TRUE in this vector.
 *
 * Returns: Count of %TRUE.
 */
guint
crank_vec_bool3_get_count (CrankVecBool3 *vec)
{
  guint count = 0;
  if (vec->x)
    count++;
  if (vec->y)
    count++;
  if (vec->z)
    count++;

  return count;
}

/**
 * crank_vec_bool3_get_ratio:
 * @vec: A Vector.
 *
 * Gets ratio of %TRUE in this vector.
 *
 * Returns: Ratio of %TRUE.
 */
gfloat
crank_vec_bool3_get_ratio (CrankVecBool3 *vec)
{
  return crank_vec_bool3_get_count (vec) / 3.0f;
}

//////// Functions as collection ///////////////////////////////////////////////


/**
 * crank_vec_bool3_get:
 * @vec: A vector to get element.
 * @index: Index of element.
 *
 * Gets element from vector.
 *
 * Returns: Element of @vec at @index.
 */
gboolean
crank_vec_bool3_get (CrankVecBool3 *vec,
                     const guint    index)
{
  return ((gboolean*)vec)[index];
}

/**
 * crank_vec_bool3_set:
 * @vec: A vector to set element.
 * @index: Index of element.
 * @value: Element to set.
 *
 * Sets element of vector.
 */
void
crank_vec_bool3_set (CrankVecBool3 *vec,
                     const guint    index,
                     const gboolean value)
{
  ((gboolean*)vec)[index] = value;
}

/**
 * crank_vec_bool3_foreach:
 * @vec: A vector
 * @func: (scope call): A function to iterate.
 * @userdata: (closure): A userdata for @func.
 *
 * Iterates over a boolean vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_bool3_foreach (CrankVecBool3    *vec,
                         CrankBoolBoolFunc func,
                         gpointer          userdata)
{
  if (func (vec->x, userdata) &&
      func (vec->y, userdata) &&
      func (vec->z, userdata))
    return TRUE;
  else
    return FALSE;
}

/**
 * crank_vec_bool3_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for the vector.
 */
void
crank_vec_bool3_iterator (CrankVecBool3    *vec,
                          CrankIterMemBool *iter)
{
  crank_iter_mem_bool_init_with_count (iter, (gboolean*)vec, 3);
}

//////// Vector - Vector Operations ////////////////////////////////////////////


/**
 * crank_vec_bool3_and:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component AND of @a and @b.
 */
void
crank_vec_bool3_and (CrankVecBool3 *a,
                     CrankVecBool3 *b,
                     CrankVecBool3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x && b->x;
  r->y = a->y && b->y;
  r->z = a->z && b->z;
}

/**
 * crank_vec_bool3_and_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component AND to @a.
 */
void
crank_vec_bool3_and_self (CrankVecBool3 *a,
                          CrankVecBool3 *b)
{
  a->x = a->x && b->x;
  a->y = a->y && b->y;
  a->z = a->z && b->z;
}

/**
 * crank_vec_bool3_or:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component OR of @a and @b.
 */
void
crank_vec_bool3_or (CrankVecBool3 *a,
                    CrankVecBool3 *b,
                    CrankVecBool3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x || b->x;
  r->y = a->y || b->y;
  r->z = a->z || b->z;
}

/**
 * crank_vec_bool3_or_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component OR to @a.
 */
void
crank_vec_bool3_or_self (CrankVecBool3 *a,
                         CrankVecBool3 *b)
{
  a->x = a->x || b->x;
  a->y = a->y || b->y;
  a->z = a->z || b->z;
}

/**
 * crank_vec_bool3_xor:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component XOR of @a and @b.
 */
void
crank_vec_bool3_xor (CrankVecBool3 *a,
                     CrankVecBool3 *b,
                     CrankVecBool3 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x != b->x;
  r->y = a->y != b->y;
  r->z = a->z != b->z;
}

/**
 * crank_vec_bool3_xor_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component XOR to @a.
 */
void
crank_vec_bool3_xor_self (CrankVecBool3 *a,
                          CrankVecBool3 *b)
{
  a->x = a->x != b->x;
  a->y = a->y != b->y;
  a->z = a->z != b->z;
}

/**
 * crank_vec_bool3_not:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component NOT of @a.
 */
void
crank_vec_bool3_not (CrankVecBool3 *a,
                     CrankVecBool3 *r)
{
  g_return_if_fail (a != r);

  r->x = !a->x;
  r->y = !a->y;
}

/**
 * crank_vec_bool3_not_self:
 * @a: A vector.
 *
 * Apply Component NOT to @a.
 */
void
crank_vec_bool3_not_self (CrankVecBool3 *a)
{
  a->x = !a->x;
  a->y = !a->y;
  a->z = !a->z;
}

/**
 * crank_vec_bool3_andv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool3_and(). Some language may use "and" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool3_andv (CrankVecBool3 *a,
                      CrankVecBool3 *b,
                      CrankVecBool3 *r)
{
  crank_vec_bool3_and (a, b, r);
}

/**
 * crank_vec_bool3_orv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool3_or(). Some language may use "or" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool3_orv (CrankVecBool3 *a,
                     CrankVecBool3 *b,
                     CrankVecBool3 *r)
{
  crank_vec_bool3_or (a, b, r);
}

/**
 * crank_vec_bool3_notv:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool3_not(). Some language may use "not" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool3_notv (CrankVecBool3 *a,
                      CrankVecBool3 *r)
{
  crank_vec_bool3_not (a, r);
}

//////// GValue conversions ////////////////////////////////////////////////////

static void
crank_vec_bool3_transform_to_string (const GValue *src,
                                     GValue       *dest)
{
  CrankVecBool3 *vb = (CrankVecBool3*) g_value_get_boxed (src);
  gchar *str = crank_vec_bool3_to_string (vb);
  g_value_take_string (dest, str);
}







static void crank_vec_bool4_transform_to_string (const GValue *src,
                                                 GValue       *dest);


G_DEFINE_BOXED_TYPE_WITH_CODE (CrankVecBool4,
  crank_vec_bool4,
  crank_vec_bool4_dup,
  g_free,
  {
   g_value_register_transform_func (
     g_define_type_id,
     G_TYPE_STRING,
     crank_vec_bool4_transform_to_string);
  })

//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_vec_bool4_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 * @w: Fourth vector element.
 *
 * Initialize elements from arguments.
 */
void
crank_vec_bool4_init (CrankVecBool4 *vec,
                      gboolean       x,
                      gboolean       y,
                      gboolean       z,
                      gboolean       w)
{
  vec->x = x;
  vec->y = y;
  vec->z = z;
  vec->w = w;
}


/**
 * crank_vec_bool4_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=4): Array of elements.
 *
 * Initialize elements from array.
 */
void
crank_vec_bool4_init_arr (CrankVecBool4 *vec,
                          gboolean      *arr)
{
  vec->x = arr[0];
  vec->y = arr[1];
  vec->z = arr[2];
  vec->w = arr[3];
}

/**
 * crank_vec_bool4_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list of elements.
 *
 * Initialize elements from 4 variadic arguments.
 */
void
crank_vec_bool4_init_valist (CrankVecBool4 *vec,
                             va_list        varargs)
{
  vec->x = va_arg (varargs, gboolean);
  vec->y = va_arg (varargs, gboolean);
  vec->z = va_arg (varargs, gboolean);
  vec->w = va_arg (varargs, gboolean);
}


/**
 * crank_vec_bool4_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: Value to fill.
 *
 * Fill elements by @fill value.
 */
void
crank_vec_bool4_init_fill (CrankVecBool4 *vec,
                           const gboolean fill)
{
  vec->x = fill;
  vec->y = fill;
  vec->z = fill;
  vec->w = fill;
}


//////// Basic Operations //////////////////////////////////////////////////////


/**
 * crank_vec_bool4_copy:
 * @vec: Vector to copy
 * @other: (out): Other vector to paste.
 *
 * Copies a vector.
 */
void
crank_vec_bool4_copy (CrankVecBool4 *vec,
                      CrankVecBool4 *other)
{
  memcpy (other, vec, sizeof (CrankVecBool4));
}


/**
 * crank_vec_bool4_dup:
 * @vec: Vector to copy
 *
 * Copies a vector. Free with g_free () after use.
 *
 * Returns: (transfer full): Copied vector. Free with g_free().
 */
CrankVecBool4*
crank_vec_bool4_dup (CrankVecBool4 *vec)
{
  return (CrankVecBool4*) g_memdup (vec, sizeof (CrankVecBool4));
}

/**
 * crank_vec_bool4_hash:
 * @a: (type CrankVecBool4): A vector.
 *
 * Gets hash value of vector.
 *
 * Returns: Hash value of vector.
 */
guint
crank_vec_bool4_hash (gconstpointer a)
{
  const CrankVecBool4 *vec = (const CrankVecBool4*) a;
  return g_direct_hash (
    GINT_TO_POINTER(    (vec->x) +
                        (vec->y << 1) +
                        (vec->z << 2) +
                        (vec->w << 3)   ));
}

/**
 * crank_vec_bool4_to_string:
 * @vec: A vector.
 *
 * Stringify a given vector.
 * The format will be. (for example of {TRUE, FALSE, FALSE, TRUE})
 * |[
 *   (true, false, false, true)
 * ]|
 *
 * Returns: String representation of vector.
 */
gchar*
crank_vec_bool4_to_string (CrankVecBool4 *vec)
{
  return crank_vec_bool4_to_string_full (vec, "(", ", ", ")", "true", "false");
}


/**
 * crank_vec_bool4_to_string_full:
 * @vec: A vector.
 * @left: Left delimiter.
 * @in: Middle delimiter that divides components.
 * @right: Right delimiter.
 * @on_true: String representation of %TRUE.
 * @on_false: String representation of %FALSE.
 *
 * Stringify a given vector with given string parts.
 * The order of part will be (for example of {TRUE, FALSE, FALSE, TRUE})
 * |[
 *   left on_true in on_false in on_false in on_true right
 * ]|
 *
 * Returns: String representation of vector.
 */
gchar*
crank_vec_bool4_to_string_full (CrankVecBool4 *vec,
                                const gchar   *left,
                                const gchar   *in,
                                const gchar   *right,
                                const gchar   *on_true,
                                const gchar   *on_false)
{
  return g_strdup_printf ("%s%s%s%s%s%s%s%s%s",
                          left,
                          vec->x ? on_true : on_false,
                          in,
                          vec->y ? on_true : on_false,
                          in,
                          vec->z ? on_true : on_false,
                          in,
                          vec->w ? on_true : on_false,
                          right);
}



//////// Basic Properties /////////////////////////////////////////////////////


/**
 * crank_vec_bool4_get_any:
 * @vec: A vector.
 *
 * Checks there is any element be %TRUE.
 *
 * Returns: Whether there is any element be %TRUE.
 */
gboolean
crank_vec_bool4_get_any (CrankVecBool4 *vec)
{
  return (vec->x || vec->y || vec->z || vec->w);
}


/**
 * crank_vec_bool4_get_all:
 * @vec: A vector.
 *
 * Checks whether all elements are %TRUE.
 *
 * Returns: Whether all elements are %TRUE.
 */
gboolean
crank_vec_bool4_get_all (CrankVecBool4 *vec)
{
  return (vec->x && vec->y && vec->z && vec->w);
}

/**
 * crank_vec_bool4_get_count:
 * @vec: A Vector.
 *
 * Gets count of %TRUE in this vector.
 *
 * Returns: Count of %TRUE.
 */
guint
crank_vec_bool4_get_count (CrankVecBool4 *vec)
{
  guint count = 0;
  if (vec->x)
    count++;
  if (vec->y)
    count++;
  if (vec->z)
    count++;
  if (vec->w)
    count++;

  return count;
}

/**
 * crank_vec_bool4_get_ratio:
 * @vec: A Vector.
 *
 * Gets ratio of %TRUE in this vector.
 *
 * Returns: Ratio of %TRUE.
 */
gfloat
crank_vec_bool4_get_ratio (CrankVecBool4 *vec)
{
  return crank_vec_bool4_get_count (vec) * 0.25f;
}


//////// Functions as collection ///////////////////////////////////////////////


/**
 * crank_vec_bool4_get:
 * @vec: A vector to get element.
 * @index: Index of element.
 *
 * Gets element of vector.
 *
 * Returns: Element of @vec at @index.
 */
gboolean
crank_vec_bool4_get (CrankVecBool4 *vec,
                     const guint    index)
{
  return ((gboolean*)vec)[index];
}

/**
 * crank_vec_bool4_set:
 * @vec: A vector to set element.
 * @index: Index of element.
 * @value: Element to set.
 *
 * Sets element of vector.
 */
void
crank_vec_bool4_set (CrankVecBool4 *vec,
                     const guint    index,
                     const gboolean value)
{
  ((gboolean*)vec)[index] = value;
}

/**
 * crank_vec_bool4_foreach:
 * @vec: A vector
 * @func: (scope call): A function to iterate.
 * @userdata: (closure): A userdata for @func.
 *
 * Iterates over a boolean vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_bool4_foreach (CrankVecBool4    *vec,
                         CrankBoolBoolFunc func,
                         gpointer          userdata)
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
 * crank_vec_bool4_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for the vector.
 */
void
crank_vec_bool4_iterator (CrankVecBool4    *vec,
                          CrankIterMemBool *iter)
{
  crank_iter_mem_bool_init_with_count (iter, (gboolean*)vec, 4);
}

//////// Vector - Vector Operations ////////////////////////////////////////////


/**
 * crank_vec_bool4_and:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component AND of @a and @b.
 */
void
crank_vec_bool4_and (CrankVecBool4 *a,
                     CrankVecBool4 *b,
                     CrankVecBool4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x && b->x;
  r->y = a->y && b->y;
  r->z = a->z && b->z;
  r->w = a->w && b->w;
}

/**
 * crank_vec_bool4_and_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component AND to @a.
 */
void
crank_vec_bool4_and_self (CrankVecBool4 *a,
                          CrankVecBool4 *b)
{
  a->x = a->x && b->x;
  a->y = a->y && b->y;
  a->z = a->z && b->z;
  a->w = a->w && b->w;
}

/**
 * crank_vec_bool4_or:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component OR of @a and @b.
 */
void
crank_vec_bool4_or (CrankVecBool4 *a,
                    CrankVecBool4 *b,
                    CrankVecBool4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x || b->x;
  r->y = a->y || b->y;
  r->z = a->z || b->z;
  r->w = a->w || b->w;
}

/**
 * crank_vec_bool4_or_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component OR to @a.
 */
void
crank_vec_bool4_or_self (CrankVecBool4 *a,
                         CrankVecBool4 *b)
{
  a->x = a->x || b->x;
  a->y = a->y || b->y;
  a->z = a->z || b->z;
  a->w = a->w || b->w;
}

/**
 * crank_vec_bool4_xor:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component exclusive or of @a and @b.
 */
void
crank_vec_bool4_xor (CrankVecBool4 *a,
                     CrankVecBool4 *b,
                     CrankVecBool4 *r)
{
  g_return_if_fail (a != r);
  g_return_if_fail (b != r);

  r->x = a->x != b->x;
  r->y = a->y != b->y;
  r->z = a->z != b->z;
  r->w = a->w != b->w;
}

/**
 * crank_vec_bool4_xor_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component XOR to @a.
 */
void
crank_vec_bool4_xor_self (CrankVecBool4 *a,
                          CrankVecBool4 *b)
{
  a->x = a->x != b->x;
  a->y = a->y != b->y;
  a->z = a->z != b->z;
  a->w = a->w != b->w;
}


/**
 * crank_vec_bool4_not:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component NOT of @a and @b.
 */
void
crank_vec_bool4_not (CrankVecBool4 *a,
                     CrankVecBool4 *r)
{
  g_return_if_fail (a != r);

  r->x = !a->x;
  r->y = !a->y;
  r->z = !a->z;
  r->w = !a->w;
}

/**
 * crank_vec_bool4_not_self:
 * @a: A vector.
 *
 * Apply Component NOT to @a.
 */
void
crank_vec_bool4_not_self (CrankVecBool4 *a)
{
  a->x = !a->x;
  a->y = !a->y;
  a->z = !a->z;
  a->w = !a->w;
}

/**
 * crank_vec_bool4_andv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool4_and(). Some language may use "and" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool4_andv (CrankVecBool4 *a,
                      CrankVecBool4 *b,
                      CrankVecBool4 *r)
{
  crank_vec_bool4_and (a, b, r);
}

/**
 * crank_vec_bool4_orv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool4_or(). Some language may use "or" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool4_orv (CrankVecBool4 *a,
                     CrankVecBool4 *b,
                     CrankVecBool4 *r)
{
  crank_vec_bool4_or (a, b, r);
}

/**
 * crank_vec_bool4_notv:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool4_not(). Some language may use "not" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool4_notv (CrankVecBool4 *a,
                      CrankVecBool4 *r)
{
  crank_vec_bool4_not (a, r);
}
/**
 * crank_vec_bool4_equal:
 * @a: (type CrankVecBool4): A vector.
 * @b: (type CrankVecBool4): A vector.
 *
 * Checks whether two vectors are equal.
 *
 * Returns: Whether two vectors are equal.
 */
gboolean
crank_vec_bool4_equal (gconstpointer a,
                       gconstpointer b)
{
  const CrankVecBool4 *veca = (const CrankVecBool4*) a;
  const CrankVecBool4 *vecb = (const CrankVecBool4*) b;
  return (veca->x == vecb->x) &&
         (veca->y == vecb->y) &&
         (veca->z == vecb->z) &&
         (veca->w == vecb->w);
}

//////// GValue conversions ////////////////////////////////////////////////////

static void
crank_vec_bool4_transform_to_string (const GValue *src,
                                     GValue       *dest)
{
  CrankVecBool4 *vb = (CrankVecBool4*) g_value_get_boxed (src);
  gchar *str = crank_vec_bool4_to_string (vb);
  g_value_take_string (dest, str);
}









static void crank_vec_bool_n_transform_from_v2 (const GValue *src,
                                                GValue       *dest);

static void crank_vec_bool_n_transform_from_v3 (const GValue *src,
                                                GValue       *dest);

static void crank_vec_bool_n_transform_from_v4 (const GValue *src,
                                                GValue       *dest);

static void crank_vec_bool_n_transform_to_string (const GValue *src,
                                                  GValue       *dest);


G_DEFINE_BOXED_TYPE_WITH_CODE (CrankVecBoolN,
                               crank_vec_bool_n,
                               crank_vec_bool_n_dup,
                               crank_vec_bool_n_free,
                               {
                                 g_value_register_transform_func (
                                   CRANK_TYPE_VEC_BOOL2,
                                   g_define_type_id,
                                   crank_vec_bool_n_transform_from_v2);

                                 g_value_register_transform_func (
                                   CRANK_TYPE_VEC_BOOL3,
                                   g_define_type_id,
                                   crank_vec_bool_n_transform_from_v3);

                                 g_value_register_transform_func (
                                   CRANK_TYPE_VEC_BOOL4,
                                   g_define_type_id,
                                   crank_vec_bool_n_transform_from_v4);

                                 g_value_register_transform_func (
                                   g_define_type_id,
                                   G_TYPE_STRING,
                                   crank_vec_bool_n_transform_to_string);
                               })

//////// Initialization and finalization ///////////////////////////////////////

/**
 * crank_vec_bool_n_init:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @...: Vector elements.
 *
 * Initialize elements from arguments.
 * Unset with crank_vec_bool_n_fini() after use.
 */
void
crank_vec_bool_n_init (CrankVecBoolN *vec,
                       const guint    n,
                       ...)
{
  va_list varargs;

  va_start (varargs, n);

  crank_vec_bool_n_init_valist (vec, n, varargs);

  va_end (varargs);
}

/**
 * crank_vec_bool_n_init_arr:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @arr: (array length=n): Array of elements.
 *
 * Initialize elements from array.
 * Unset with crank_vec_bool_n_fini() after use.
 */
void
crank_vec_bool_n_init_arr (CrankVecBoolN *vec,
                           const guint    n,
                           gboolean      *arr)
{
  vec->data = CRANK_ARRAY_DUP(arr, gboolean, n);
  vec->n = n;
}

/**
 * crank_vec_bool_n_init_valist:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @varargs: va_list of elements.
 *
 * Initialize elements from given count of variadic arguments.
 * Unset with crank_vec_bool_n_fini() after use.
 */
void
crank_vec_bool_n_init_valist (CrankVecBoolN *vec,
                              const guint    n,
                              va_list        varargs)
{
  guint i;

  CRANK_VEC_ALLOC(vec,gboolean,n);
  for (i = 0; i < n; i++)
    vec->data[i] = va_arg (varargs, gboolean);

}

/**
 * crank_vec_bool_n_init_fill:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @fill: Value to fill.
 *
 * Fill elements by @fill value.
 * Unset with crank_vec_bool_n_fini() after use.
 */
void
crank_vec_bool_n_init_fill (CrankVecBoolN *vec,
                            const guint    n,
                            const gboolean fill)
{
  guint i;

  CRANK_VEC_ALLOC(vec,gboolean,n);
  for (i = 0; i < n; i++)
    vec->data[i] = fill;

}


/**
 * crank_vec_bool_n_fini:
 * @vec: A vector to unset.
 *
 * Frees associated resources and unset @vec.
 */
void
crank_vec_bool_n_fini (CrankVecBoolN *vec)
{
  g_free (vec->data);
  vec->n = 0;
}

/**
 * crank_vec_bool_n_copy:
 * @vec: Vector to copy
 * @other: (out): Other vector to paste.
 *
 * Copies a vector.
 */
void
crank_vec_bool_n_copy (CrankVecBoolN *vec,
                       CrankVecBoolN *other)
{
  crank_vec_bool_n_init_arr (other, vec->n, vec->data);
}

/**
 * crank_vec_bool_n_dup:
 * @vec: Vector to copy
 *
 * Copies a vector. Free with crank_vec_bool_n_free() after use.
 *
 * Returns: (transfer full): Copied vector. Free with g_free().
 */
CrankVecBoolN*
crank_vec_bool_n_dup (CrankVecBoolN *vec)
{
  CrankVecBoolN *result = g_new0 (CrankVecBoolN, 1);

  crank_vec_bool_n_copy (vec, result);
  return result;
}

/**
 * crank_vec_bool_n_free:
 * @vec: A vector to free.
 *
 * Frees associated resources and frees @vec.
 */
void
crank_vec_bool_n_free (CrankVecBoolN *vec)
{
  crank_vec_bool_n_fini (vec);
  g_free (vec);
}


//////// Basic Operations //////////////////////////////////////////////////////


/**
 * crank_vec_bool_n_equal:
 * @a: (type CrankVecBoolN): A vector.
 * @b: (type CrankVecBoolN): A vector.
 *
 * Checks whether two vectors are equal.
 *
 * Returns: Whether two vectors are equal.
 */
gboolean
crank_vec_bool_n_equal (gconstpointer a,
                        gconstpointer b)
{
  const CrankVecBoolN *veca = (const CrankVecBoolN*) a;
  const CrankVecBoolN *vecb = (const CrankVecBoolN*) b;

  guint i;
  if (veca->n != vecb->n)
    return FALSE;

  for (i = 0; i < veca->n; i++)
    if (veca->data[i] != vecb->data[i])
      return FALSE;

  return TRUE;
}


/**
 * crank_vec_bool_n_hash:
 * @a: (type CrankVecBoolN): A vector.
 *
 * Gets hash value of vector.
 *
 * Returns: Hash value of vector.
 */
guint
crank_vec_bool_n_hash (gconstpointer a)
{
  const CrankVecBoolN *vec  = (const CrankVecBoolN*) a;

  guint i;
  guint value = 0;

  for (i = 0; i < vec->n; i++)
    value = value ^ ((vec->data[i] ? 1 : 0) << (i & 31));

  return g_direct_hash (GINT_TO_POINTER (value));
}

/**
 * crank_vec_bool_n_to_string:
 * @vec: A vector.
 *
 * Stringify a given vector.
 * The format will be. (for example of {TRUE, FALSE, FALSE, TRUE, TRUE})
 * |[
 *   (true, false, false, true, true)
 * ]|
 *
 * Returns: String representation of vector.
 */
gchar*
crank_vec_bool_n_to_string (CrankVecBoolN *vec)
{
  return crank_vec_bool_n_to_string_full (vec, "(", ", ", ")", "true", "false");
}

/**
 * crank_vec_bool_n_to_string_full:
 * @vec: A vector.
 * @left: Left delimiter.
 * @in: Middle delimiter that divides components.
 * @right: Right delimiter.
 * @on_true: String representation of %TRUE.
 * @on_false: String representation of %FALSE.
 *
 * Stringify a given vector with given string parts.
 * The order of part will be (for example of {TRUE, FALSE, FALSE, TRUE, TRUE})
 * |[
 *   left on_true in on_false in on_false in on_true in on_true right
 * ]|
 *
 * Returns: String representation of vector.
 */
gchar*
crank_vec_bool_n_to_string_full (CrankVecBoolN *vec,
                                 const gchar   *left,
                                 const gchar   *in,
                                 const gchar   *right,
                                 const gchar   *on_true,
                                 const gchar   *on_false)
{
  GString *str;
  gchar *result;

  str = g_string_new (left);

  if (0 < vec->n)
    {
      guint i;
      g_string_append (str, vec->data[0] ? on_true : on_false);

      for (i = 1; i < vec->n; i++)
        {
          g_string_append (str, in);
          g_string_append (str, vec->data[i] ? on_true : on_false);
        }
    }

  g_string_append (str, right);

  result = str->str;
  g_string_free (str, FALSE);

  return result;
}


//////// Classification ////////////////////////////////////////////////////////

/**
 * crank_vec_bool_n_is_false:
 * @vec: A Vector.
 *
 * Checks the vector is filled with %FALSE.
 *
 * Returns: Whether this is "false vector".
 */
gboolean
crank_vec_bool_n_is_false (CrankVecBoolN *vec)
{
  guint i;
  for (i = 0; i < vec->n; i++)
    {
      if (vec->data[i])
        return FALSE;
    }
  return TRUE;
}

/**
 * crank_vec_bool_n_is_true:
 * @vec: A Vector.
 *
 * Checks the vector is filled with %TRUE.
 *
 * Returns: Whether this is "true vector".
 */
gboolean
crank_vec_bool_n_is_true (CrankVecBoolN *vec)
{
  guint i;
  for (i = 0; i < vec->n; i++)
    {
      if (! vec->data[i])
        return TRUE;
    }
  return FALSE;
}

/**
 * crank_vec_bool_n_is_empty:
 * @vec: A Vector.
 *
 * Checks the vector is empty.
 *
 * Returns: Whether this is empty.
 */
gboolean
crank_vec_bool_n_is_empty (CrankVecBoolN *vec)
{
  return vec->n == 0;
}


//////// Basic Properties //////////////////////////////////////////////////////


/**
 * crank_vec_bool_n_get_any:
 * @vec: A vector.
 *
 * Checks there is any element be %TRUE.
 *
 * Returns: Whether there is any element be %TRUE.
 */
gboolean
crank_vec_bool_n_get_any (CrankVecBoolN *vec)
{
  guint i;

  for (i = 0; i < vec->n; i++)
    {
      if (vec->data[i])
        return TRUE;
    }
  return FALSE;
}

/**
 * crank_vec_bool_n_get_all:
 * @vec: A vector.
 *
 * Checks whether all elements are %TRUE.
 *
 * Returns: Whether all elements are %TRUE.
 */
gboolean
crank_vec_bool_n_get_all (CrankVecBoolN *vec)
{
  guint i;
  for (i = 0; i < vec->n; i++)
    {
      if (! vec->data[i])
        return FALSE;
    }
  return TRUE;
}

/**
 * crank_vec_bool_n_get_count:
 * @vec: A Vector.
 *
 * Gets count of %TRUE in this vector.
 *
 * Returns: Count of %TRUE.
 */
guint
crank_vec_bool_n_get_count (CrankVecBoolN *vec)
{
  guint count = 0;

  guint i;

  for (i = 0; i < vec->n; i++)
    {
      if (vec->data[i])
        count++;
    }
  return count;
}

/**
 * crank_vec_bool_n_get_ratio:
 * @vec: A Vector.
 *
 * Gets ratio of %TRUE in this vector.
 *
 * Returns: Ratio of %TRUE.
 */
gfloat
crank_vec_bool_n_get_ratio (CrankVecBoolN *vec)
{
  return crank_vec_bool_n_get_count (vec) / vec->n;
}


//////// Functions as collection ///////////////////////////////////////////////


/**
 * crank_vec_bool_n_get_size:
 * @vec: Vector to get size.
 *
 * Gets size of vector. This can be obtained from @vec->n.
 *
 * Returns: Size of vector.
 */
guint
crank_vec_bool_n_get_size (CrankVecBoolN *vec)
{
  return vec->n;
}


/**
 * crank_vec_bool_n_get:
 * @vec: A vector to get element.
 * @index: Index of element.
 *
 * Gets element of vector.
 *
 * Returns: Element of @vec at @index.
 */
gboolean
crank_vec_bool_n_get (CrankVecBoolN *vec,
                      const guint    index)
{
  return vec->data[index];
}

/**
 * crank_vec_bool_n_set:
 * @vec: A vector to set element.
 * @index: Index of element.
 * @value: Element to set.
 *
 * Sets element of vector.
 */
void
crank_vec_bool_n_set (CrankVecBoolN *vec,
                      const guint    index,
                      const gboolean value)
{
  vec->data[index] = value;
}

/**
 * crank_vec_bool_n_prepend:
 * @vec: A vector.
 * @value: A value to insert in vector.
 *
 * Prepends @value to @vec.
 */
void
crank_vec_bool_n_prepend (CrankVecBoolN *vec,
                          const gboolean value)
{
  crank_vec_bool_n_insert (vec, 0, value);
}

/**
 * crank_vec_bool_n_append:
 * @vec: A vector.
 * @value: A value to insert in vector.
 *
 * Appends @value to @vec.
 */
void
crank_vec_bool_n_append (CrankVecBoolN *vec,
                         const gboolean value)
{
  crank_vec_bool_n_insert (vec, vec->n, value);
}

/**
 * crank_vec_bool_n_insert:
 * @vec: A vector.
 * @index: Index to insert value.
 * @value: A value to insert in vector.
 *
 * Inserts @value to @vec at @index.
 */
void
crank_vec_bool_n_insert (CrankVecBoolN *vec,
                         const guint    index,
                         const gboolean value)
{
  guint i;

  vec->data = g_renew (gboolean, vec->data, vec->n + 1);

  for (i = vec->n; index < i; i--)
    vec->data[i] = vec->data[i - 1];

  vec->data[index] = value;
  vec->n++;
}

/**
 * crank_vec_bool_n_remove:
 * @vec: A vector
 * @index: A index to remove.
 *
 * Removes an element from a boolean vector.
 */
void
crank_vec_bool_n_remove (CrankVecBoolN *vec,
                         const guint    index)
{
  guint i;

  vec->n--;

  for (i = index; i < vec->n; i++)
    vec->data[i] = vec->data[i + 1];

  vec->data = g_renew (gboolean, vec->data, vec->n);
}

/**
 * crank_vec_bool_n_foreach:
 * @vec: A vector
 * @func: (scope call): A function to iterate.
 * @userdata: (closure): A userdata for @func.
 *
 * Iterates over a boolean vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_bool_n_foreach (CrankVecBoolN    *vec,
                          CrankBoolBoolFunc func,
                          gpointer          userdata)
{
  guint i;

  if (vec->data != NULL)
    {
      for (i = 0; i < vec->n; i++)
        if (!func (vec->data[i], userdata))
          return FALSE;
    }

  return TRUE;
}

/**
 * crank_vec_bool_n_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for the vector.
 */
void
crank_vec_bool_n_iterator (CrankVecBoolN    *vec,
                           CrankIterMemBool *iter)
{
  crank_iter_mem_bool_init_with_count (iter, vec->data, vec->n);
}


//////// Vector - Vector Operations ////////////////////////////////////////////


/**
 * crank_vec_bool_n_and:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component AND of @a and @b.
 */
void
crank_vec_bool_n_and (CrankVecBoolN *a,
                      CrankVecBoolN *b,
                      CrankVecBoolN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecBoolN", "and", a, b);

  CRANK_VEC_ALLOC (r,gboolean,a->n);
  for (i = 0; i < a->n; i++)
    r->data[i] = (a->data[i]) && (b->data[i]);
}

/**
 * crank_vec_bool_n_and_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component AND to @a.
 */
void
crank_vec_bool_n_and_self (CrankVecBoolN *a,
                           CrankVecBoolN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecBoolN", "and-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] = (a->data[i] && b->data[i]);
}

/**
 * crank_vec_bool_n_or:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component OR of @a and @b.
 */
void
crank_vec_bool_n_or (CrankVecBoolN *a,
                     CrankVecBoolN *b,
                     CrankVecBoolN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecBoolN", "or", a, b);

  CRANK_VEC_ALLOC (r,gboolean,a->n);
  for (i = 0; i < a->n; i++)
    r->data[i] = a->data[i] || b->data[i];
}

/**
 * crank_vec_bool_n_or_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component OR to @a.
 */
void
crank_vec_bool_n_or_self (CrankVecBoolN *a,
                          CrankVecBoolN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecBoolN", "or-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] = (a->data[i] || b->data[i]);
}

/**
 * crank_vec_bool_n_xor:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component exclusive or of @a and @b.
 */
void
crank_vec_bool_n_xor (CrankVecBoolN *a,
                      CrankVecBoolN *b,
                      CrankVecBoolN *r)
{
  guint i;

  g_return_if_fail (a != r);
  g_return_if_fail (b != r);
  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecBoolN", "xor", a, b);

  CRANK_VEC_ALLOC (r,gboolean,a->n);
  for (i = 0; i < a->n; i++)
    r->data[i] = (a->data[i] != b->data[i]);
}

/**
 * crank_vec_bool_n_xor_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Apply Component XOR to @a.
 */
void
crank_vec_bool_n_xor_self (CrankVecBoolN *a,
                           CrankVecBoolN *b)
{
  guint i;

  CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecBoolN", "xor-self", a, b);

  for (i = 0; i < a->n; i++)
    a->data[i] = (a->data[i] != b->data[i]);
}

/**
 * crank_vec_bool_n_not:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets Component NOT of @a and @b.
 */
void
crank_vec_bool_n_not (CrankVecBoolN *a,
                      CrankVecBoolN *r)
{
  guint i;

  g_return_if_fail (a != r);

  CRANK_VEC_ALLOC (r,gboolean,a->n);
  for (i = 0; i < r->n; i++)
    r->data[i] = !(a->data[i]);
}

/**
 * crank_vec_bool_n_not_self:
 * @a: A vector.
 *
 * Apply Component NOT to @a.
 */
void
crank_vec_bool_n_not_self (CrankVecBoolN *a)
{
  guint i;

  for (i = 0; i < a->n; i++)
    a->data[i] = !a->data[i];
}

/**
 * crank_vec_bool_n_andv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool_n_and(). Some language may use "and" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool_n_andv (CrankVecBoolN *a,
                       CrankVecBoolN *b,
                       CrankVecBoolN *r)
{
  crank_vec_bool_n_and (a, b, r);
}

/**
 * crank_vec_bool_n_orv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool_n_or(). Some language may use "or" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool_n_orv (CrankVecBoolN *a,
                      CrankVecBoolN *b,
                      CrankVecBoolN *r)
{
  crank_vec_bool_n_or (a, b, r);
}

/**
 * crank_vec_bool_n_notv:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool_n_not(). Some language may use "not" as
 * keyword or operator and cannot be used as function name.
 */
void
crank_vec_bool_n_notv (CrankVecBoolN *a,
                       CrankVecBoolN *r)
{
  crank_vec_bool_n_not (a, r);
}

//////// GValue conversions ////////////////////////////////////////////////////

static void
crank_vec_bool_n_transform_from_v2 (const GValue *src,
                                    GValue       *dest)
{
  CrankVecBoolN *vb = g_new (CrankVecBoolN, 1);
  gboolean *array = (gboolean*) g_value_get_boxed (src);

  crank_vec_bool_n_init_arr (vb, 2, array);
  g_value_take_boxed (dest, vb);
}

static void
crank_vec_bool_n_transform_from_v3 (const GValue *src,
                                    GValue       *dest)
{
  CrankVecBoolN *vb = g_new (CrankVecBoolN, 1);
  gboolean *array = (gboolean*) g_value_get_boxed (src);

  crank_vec_bool_n_init_arr (vb, 3, array);
  g_value_take_boxed (dest, vb);
}

static void
crank_vec_bool_n_transform_from_v4 (const GValue *src,
                                    GValue       *dest)
{
  CrankVecBoolN *vb = g_new (CrankVecBoolN, 1);
  gboolean *array = (gboolean*) g_value_get_boxed (src);

  crank_vec_bool_n_init_arr (vb, 4, array);
  g_value_take_boxed (dest, vb);
}

static void
crank_vec_bool_n_transform_to_string (const GValue *src,
                                      GValue       *dest)
{
  CrankVecBoolN *vb = g_value_get_boxed (src);
  gchar *str = crank_vec_bool_n_to_string (vb);

  g_value_take_string (dest, str);
}
