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
#include "crankvecint.h"

/**
 * SECTION: crankvecint
 * @title: Integer Vectors
 * @short_description: Vectors that have integer elements.
 * @stability: unstable
 * @include: crankbase.h
 *
 * Crank System provides 2, 3, 4, and free sized int vectors for convinience.
 *
 * Currently following operations are supported.
 *
 * It is compared to vec in GLSL
 *
 * # Type Conversion.
 * 
 * Integer vector types are seldomly used, but for convenience, it can be
 * converted to other types
 *
 * For fixed-sized types, it can be converted to variadic sized vector types.
 *
 * <table><title>Type Conversion of #CrankVecInt2</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool2</entry>
 *             <entry>crank_vec_int2_init_from_vb()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_int2_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_int2_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecIntN.</entry>
 *             <entry>crank_vec_int_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecIntN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecInt3</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool3</entry>
 *             <entry>crank_vec_int3_init_from_vb()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_int3_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_int3_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecIntN.</entry>
 *             <entry>crank_vec_int_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecIntN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecInt4</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBool4</entry>
 *             <entry>crank_vec_int4_init_from_vb()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_int4_to_string()</entry>
 *             <entry>GValue Transform</entry></row>
 *       <row> <entry>crank_vec_int4_to_string_full()</entry> </row>
 *
 *       <row> <entry>To #CrankVecIntN.</entry>
 *             <entry>crank_vec_int_n_init_arr()</entry>
 *             <entry>GValue Transform,
 *                    cast vector into array,
 *                    Defined in #CrankVecIntN</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 *
 * <table><title>Type Conversion of #CrankVecIntN</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrnakVecBoolN</entry>
 *             <entry>crank_vec_int_n_init_from_vb()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry>From #CrankVecInt2</entry>
 *             <entry>crank_vec_int_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>From #CrankVecInt3</entry>
 *             <entry>crank_vec_int_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry>From #CrankVecInt4</entry>
 *             <entry>crank_vec_int_n_init_arr()</entry>
 *             <entry>GValue Transform, Cast vector into array</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_int_n_to_string()</entry>
 *             <entry>GValue Transform</entry> </row>
 *       <row> <entry>crank_vec_int_n_to_string_full()</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */


#define CMP(a, b) (((a) > (b)) - ((a) < (b)))


static void	crank_vec_int2_transform_from_b (	const GValue*	src,
												GValue*			dest	);
												
static void crank_vec_int2_transform_to_string (const GValue*	src,
												GValue*			dest	);

G_DEFINE_BOXED_TYPE_WITH_CODE (
		CrankVecInt2,
		crank_vec_int2,
		crank_vec_int2_dup,
		g_free,
		{
			g_value_register_transform_func (	CRANK_TYPE_VEC_BOOL2,
												g_define_type_id,
												crank_vec_int2_transform_from_b	);
												
			g_value_register_transform_func (	g_define_type_id,
												G_TYPE_STRING,
												crank_vec_int2_transform_to_string	);
		} )

/**
 * crank_vec_int2_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_int2_init	(	CrankVecInt2*	vec,
							gint			x,
							gint			y	)
{
	vec->x = x;
	vec->y = y;
}

/**
 * crank_vec_int2_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=2): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_int2_init_arr	(	CrankVecInt2*	vec,
								gint*			arr	)
{
	vec->x = arr[0];
	vec->y = arr[1];
}

/**
 * crank_vec_int2_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_int2_init_valist	(	CrankVecInt2*	vec,
									va_list			varargs	)
{
	vec->x = va_arg (varargs, gdouble);
	vec->y = va_arg (varargs, gdouble);
}

/**
 * crank_vec_int2_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_int2_init_fill	(	CrankVecInt2*	vec,
								gint			fill	)
{
	vec->x = fill;
	vec->y = fill;
}

/**
 * crank_vec_int2_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_int2_init_from_vb	(	CrankVecInt2*	vec,
								CrankVecBool2*	vb		)
{
	vec->x = vb->x ? 1 : 0;
	vec->y = vb->y ? 1 : 0;
}


/**
 * crank_vec_int2_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_int2_copy			(	CrankVecInt2*	vec,
					   			CrankVecInt2*	other	)
{
  	memcpy (other, vec, sizeof (CrankVecInt2));
}


/**
 * crank_vec_int2_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecInt2*
crank_vec_int2_dup			(	CrankVecInt2*	vec	)
{
  	return (CrankVecInt2*) g_memdup (vec, sizeof (CrankVecInt2));
}

/**
 * crank_vec_int2_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
gint
crank_vec_int2_get	(	CrankVecInt2*	vec,
						const guint		index	)
{
	return ((gint*)vec)[index];
}

/**
 * crank_vec_int2_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_int2_set			(	CrankVecInt2*	vec,
								const guint		index,
								const gint		value	)
{
	((gint*)vec)[index] = value;
}

/**
 * crank_vec_int2_foreach:
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
crank_vec_int2_foreach (	CrankVecInt2*		vec,
							CrankBoolIntFunc	func,
							gpointer			userdata	)
{
	if (	func (vec->x, userdata) &&
	 		func (vec->y, userdata) )
		return TRUE;
	else
		return FALSE;
}

/**
 * crank_vec_int2_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_int2_iterator (	CrankVecInt2*		vec,
							CrankIterMemInt*	iter	)
{
	crank_iter_mem_int_init_with_count (iter, (gint*)vec, 2);
}

//////// Basic operation ////////

/**
 * crank_vec_int2_hash:
 * @a: (type CrankVecInt2): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_int2_hash (	gconstpointer	a	)
{
	const CrankVecInt2*	vec = a;
	guint				hash;
	
	hash  = g_direct_hash (GINT_TO_POINTER(vec->x));
	hash += g_direct_hash (GINT_TO_POINTER(vec->y)) + 37;
	
	return hash;
}

/**
 * crank_vec_int2_equal:
 * @a: (type CrankVecInt2): Vector to compare.
 * @b: (type CrankVecInt2): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean		crank_vec_int2_equal (			gconstpointer	a,
												gconstpointer	b	)
{
	CrankVecInt2*	veca = (CrankVecInt2*)a;
	CrankVecInt2*	vecb = (CrankVecInt2*)b;
	
	return ((veca->x == vecb->x) &&
			(veca->y == vecb->y));
}

/**
 * crank_vec_int2_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_int2_to_string (	CrankVecInt2*	vec	)
{
	return crank_vec_int2_to_string_full (vec, "(", ", ", ")", "%d");
}

/**
 * crank_vec_int2_to_string_full:
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
crank_vec_int2_to_string_full (	CrankVecInt2*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	format	)
{
	GString*	strb = g_string_new (left);
	gchar*		result;
	
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
 * crank_vec_int2_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
guint
crank_vec_int2_get_magn_sq	(	CrankVecInt2*	vec	)
{
	guint vx = (guint) ABS(vec->x);
	guint vy = (guint) ABS(vec->y);
	
	return (vx * vx) + (vy * vy);
}

/**
 * crank_vec_int2_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_int2_get_magn	(	CrankVecInt2*	vec	)
{
	gfloat sq = (gfloat) crank_vec_int2_get_magn_sq (vec);
	return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_int2_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_int2_neg (	CrankVecInt2*	a,
						CrankVecInt2*	r	)
{
	r->x = - (a->x);
	r->y = - (a->y);
}

/**
 * crank_vec_int2_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_int2_neg_self (	CrankVecInt2*	a	)
{
	a->x = - (a->x);
	a->y = - (a->y);
}



//////// Scalar operations ////////

/**
 * crank_vec_int2_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_int2_muls	(	CrankVecInt2*	a,
						const gint		b,
						CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x * b;
	r->y = a->y * b;
}

/**
 * crank_vec_int2_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_int2_muls_self	(	CrankVecInt2*	a,
								const gint		b	)
{
	a->x *= b;
	a->y *= b;
}

/**
 * crank_vec_int2_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_int2_divs	(	CrankVecInt2*	a,
						const gint		b,
						CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x / b;
	r->y = a->y / b;
}

/**
 * crank_vec_int2_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_int2_divs_self	(	CrankVecInt2*	a,
								const gint		b	)
{
	a->x /= b;
	a->y /= b;
}


/**
 * crank_vec_int2_mods:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Gets modular of each component.
 */
void
crank_vec_int2_mods	(	CrankVecInt2*	a,
						const gint		b,
						CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x % b;
	r->y = a->y % b;
}
/**
 * crank_vec_int2_mods_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies modular of each component.
 */
void
crank_vec_int2_mods_self	(	CrankVecInt2*	a,
								const gint		b	)
{
	a->x %= b;
	a->y %= b;
}

//////// Standard vector operations ////////

/**
 * crank_vec_int2_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_int2_add			(	CrankVecInt2*	a,
								CrankVecInt2*	b,
								CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x + b->x;
	r->y = a->y + b->y;
}

/**
 * crank_vec_int2_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Applies addition to a vector.
 */
void
crank_vec_int2_add_self	(	CrankVecInt2*	a,
							CrankVecInt2*	b	)
{
	a->x += b->x;
	a->y += b->y;
}

/**
 * crank_vec_int2_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_int2_sub	(	CrankVecInt2*	a,
						CrankVecInt2*	b,
						CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x - b->x;
	r->y = a->y - b->y;
}

/**
 * crank_vec_int2_sub_self:
 * @a: A vector.
 * @b: A vector.
 * *
 * Applies subtraction to a vector.
 */
void
crank_vec_int2_sub_self	(	CrankVecInt2*	a,
							CrankVecInt2*	b	)
{
	a->x -= b->x;
	a->y -= b->y;
}

/**
 * crank_vec_int2_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
gint
crank_vec_int2_dot	(	CrankVecInt2*	a,
						CrankVecInt2*	b	)
{
	return (a->x) * (b->x) + (a->y) * (b->y);
}
//////// Component vector operations ////////

/**
 * crank_vec_int2_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_int2_cmpmul	(	CrankVecInt2*	a,
							CrankVecInt2*	b,
							CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x * b->x;
	r->y = a->y * b->y;
}

/**
 * crank_vec_int2_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Applies component-wise multiplication on a vector.
 */
void
crank_vec_int2_cmpmul_self	(	CrankVecInt2*	a,
								CrankVecInt2*	b	)
{
	a->x *= b->x;
	a->y *= b->y;
}


/**
 * crank_vec_int2_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise division.
 */
void
crank_vec_int2_cmpdiv	(	CrankVecInt2*	a,
							CrankVecInt2*	b,
							CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x / b->x;
	r->y = a->y / b->y;
}

/**
 * crank_vec_int2_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Applies component-wise division on a vector.
 */
void
crank_vec_int2_cmpdiv_self	(	CrankVecInt2*	a,
								CrankVecInt2*	b	)
{
	a->x /= b->x;
	a->y /= b->y;
}

/**
 * crank_vec_int2_cmpmod:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise modular.
 */
void
crank_vec_int2_cmpmod	(	CrankVecInt2*	a,
							CrankVecInt2*	b,
							CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x % b->x;
	r->y = a->y % b->y;
}

/**
 * crank_vec_int2_cmpmod_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Applies component-wise modular on a vector.
 */
void
crank_vec_int2_cmpmod_self	(	CrankVecInt2*	a,
								CrankVecInt2*	b	)
{
	a->x %= b->x;
	a->y %= b->y;
}

/**
 * crank_vec_int2_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_int2_cmpless	(	CrankVecInt2*	a,
							CrankVecInt2*	b,
							CrankVecBool2*	r	)
{
	r->x = (a->x) < (b->x);
	r->y = (a->y) < (b->y);
}
												
/**
 * crank_vec_int2_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_int2_cmpeq	(	CrankVecInt2*	a,
							CrankVecInt2*	b,
							CrankVecBool2*	r	)
{
	r->x = (a->x) == (b->x);
	r->y = (a->y) == (b->y);
}
												
/**
 * crank_vec_int2_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a is greater than counterpart of @b
 */					
void
crank_vec_int2_cmpgreater	(	CrankVecInt2*	a,
								CrankVecInt2*	b,
								CrankVecBool2*	r	)
{
	r->x = (a->x) > (b->x);
	r->y = (a->y) > (b->y);
}
					
/**
 * crank_vec_int2_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets compare result of each components.
 */	
void
crank_vec_int2_cmpcmp	(		CrankVecInt2*	a,
								CrankVecInt2*	b,
								CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = CMP(a->x, b->x);
	r->y = CMP(a->y, b->y);
}

/**
 * crank_vec_int2_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_int2_min (	CrankVecInt2*	a,
						CrankVecInt2*	b,
						CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = MIN (a->x, b->x);
	r->y = MIN (a->y, b->y);
}

/**
 * crank_vec_int2_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_int2_max (	CrankVecInt2*	a,
						CrankVecInt2*	b,
						CrankVecInt2*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = MAX (a->x, b->x);
	r->y = MAX (a->y, b->y);
}



//////// GValue Transformation /////////////////////////////////////////////////

static void
crank_vec_int2_transform_from_b (	const GValue*	src,
									GValue*			dest	)
{
	CrankVecInt2*	res = g_new (CrankVecInt2, 1);
	crank_vec_int2_init_from_vb (res, (CrankVecBool2*) g_value_get_boxed (src));
	g_value_take_boxed (dest, res);
}

static void
crank_vec_int2_transform_to_string (const GValue*	src,
									GValue*			dest	)
{
	g_value_take_string (dest,
			crank_vec_int2_to_string ((CrankVecInt2*) g_value_get_boxed (src)));
}







static void	crank_vec_int3_transform_from_b (	const GValue*	src,
												GValue*			dest	);
												
static void crank_vec_int3_transform_to_string (const GValue*	src,
												GValue*			dest	);

G_DEFINE_BOXED_TYPE_WITH_CODE (
		CrankVecInt3,
		crank_vec_int3,
		crank_vec_int3_dup,
		g_free,
		{
			g_value_register_transform_func (	CRANK_TYPE_VEC_BOOL3,
												g_define_type_id,
												crank_vec_int3_transform_from_b	);
												
			g_value_register_transform_func (	g_define_type_id,
												G_TYPE_STRING,
												crank_vec_int3_transform_to_string	);
		} )

/**
 * crank_vec_int3_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_int3_init	(	CrankVecInt3*	vec,
						gint			x,
						gint			y,
						gint			z	)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

/**
 * crank_vec_int3_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=3): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_int3_init_arr	(	CrankVecInt3*	vec,
							gint*			arr	)
{
	vec->x = arr[0];
	vec->y = arr[1];
	vec->z = arr[2];
}

/**
 * crank_vec_int3_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_int3_init_valist	(	CrankVecInt3*	vec,
								va_list			varargs	)
{
	vec->x = va_arg (varargs, gint);
	vec->y = va_arg (varargs, gint);
	vec->z = va_arg (varargs, gint);
}

/**
 * crank_vec_int3_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_int3_init_fill	(	CrankVecInt3*	vec,
								gint			fill	)
{
	vec->x = fill;
	vec->y = fill;
	vec->z = fill;
}

/**
 * crank_vec_int3_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_int3_init_from_vb	(	CrankVecInt3*	vec,
								CrankVecBool3*	vb		)
{
	vec->x = vb->x ? 1 : 0;
	vec->y = vb->y ? 1 : 0;
	vec->z = vb->z ? 1 : 0;
}


/**
 * crank_vec_int3_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_int3_copy			(	CrankVecInt3*	vec,
					   			CrankVecInt3*	other	)
{
  	memcpy (other, vec, sizeof (CrankVecInt3));
}


/**
 * crank_vec_int3_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecInt3*
crank_vec_int3_dup			(	CrankVecInt3*	vec	)
{
  	return (CrankVecInt3*) g_memdup (vec, sizeof (CrankVecInt3));
}

/**
 * crank_vec_int3_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
gint
crank_vec_int3_get	(	CrankVecInt3*	vec,
						const guint		index	)
{
	return ((gint*)vec)[index];
}

/**
 * crank_vec_int3_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_int3_set			(	CrankVecInt3*	vec,
								const guint		index,
								const gint		value	)
{
	((gint*)vec)[index] = value;
}

/**
 * crank_vec_int3_foreach:
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
crank_vec_int3_foreach (	CrankVecInt3*		vec,
							CrankBoolIntFunc	func,
							gpointer			userdata	)
{
	if (	func (vec->x, userdata) &&
	 		func (vec->y, userdata) &&
			func (vec->z, userdata) )
		return TRUE;
	else
		return FALSE;
}

/**
 * crank_vec_int3_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_int3_iterator (	CrankVecInt3*		vec,
							CrankIterMemInt*	iter	)
{
	crank_iter_mem_int_init_with_count (iter, (gint*)vec, 3);
}

//////// Basic operation ////////

/**
 * crank_vec_int3_hash:
 * @a: (type CrankVecInt3): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_int3_hash (	gconstpointer	a	)
{
	const CrankVecInt3*	vec = a;
	guint				hash;
	
	hash  = g_direct_hash (GINT_TO_POINTER(vec->x));
	hash += g_direct_hash (GINT_TO_POINTER(vec->y)) + 37;
	hash += g_direct_hash (GINT_TO_POINTER(vec->z)) + 129;
	
	return hash;
}

/**
 * crank_vec_int3_equal:
 * @a: (type CrankVecInt3): Vector to compare.
 * @b: (type CrankVecInt3): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean		crank_vec_int3_equal (			gconstpointer	a,
												gconstpointer	b	)
{
	CrankVecInt3*	veca = (CrankVecInt3*)a;
	CrankVecInt3*	vecb = (CrankVecInt3*)b;
	
	return ((veca->x == vecb->x) &&
			(veca->y == vecb->y) &&
			(veca->z == vecb->z));
}

/**
 * crank_vec_int3_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4, 5)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_int3_to_string (	CrankVecInt3*	vec	)
{
	return crank_vec_int3_to_string_full (vec, "(", ", ", ")", "%d");
}

/**
 * crank_vec_int3_to_string_full:
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
crank_vec_int3_to_string_full (	CrankVecInt3*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	format	)
{
	GString*	strb = g_string_new (left);
	gchar*		result;
	
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
 * crank_vec_int3_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
guint
crank_vec_int3_get_magn_sq	(	CrankVecInt3*	vec	)
{
	guint vx = (guint) ABS(vec->x);
	guint vy = (guint) ABS(vec->y);
	guint vz = (guint) ABS(vec->z);
	
	return (vx * vx) + (vy * vy) + (vz * vz);
}

/**
 * crank_vec_int3_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_int3_get_magn	(	CrankVecInt3*	vec	)
{
	gfloat sq = (gfloat) crank_vec_int3_get_magn_sq (vec);
	return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_int3_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_int3_neg (	CrankVecInt3*	a,
						CrankVecInt3*	r	)
{
	r->x = - (a->x);
	r->y = - (a->y);
	r->z = - (a->z);
}

/**
 * crank_vec_int3_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_int3_neg_self (	CrankVecInt3*	a	)
{
	a->x = - (a->x);
	a->y = - (a->y);
	a->z = - (a->z);
}



//////// Scalar operations ////////

/**
 * crank_vec_int3_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_int3_muls	(	CrankVecInt3*	a,
						const gint		b,
						CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x * b;
	r->y = a->y * b;
	r->z = a->z * b;
}

/**
 * crank_vec_int3_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication on a vector.
 */
void
crank_vec_int3_muls_self	(	CrankVecInt3*	a,
								const gint		b	)
{
	a->x *= b;
	a->y *= b;
	a->z *= b;
}

/**
 * crank_vec_int3_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_int3_divs	(	CrankVecInt3*	a,
						const gint		b,
						CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x / b;
	r->y = a->y / b;
	r->z = a->z / b;
}

/**
 * crank_vec_int3_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division on a vector.
 */
void
crank_vec_int3_divs_self	(	CrankVecInt3*	a,
								const gint		b	)
{
	a->x /= b;
	a->y /= b;
	a->z /= b;
}

/**
 * crank_vec_int3_mods:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Gets modular of each component.
 */
void
crank_vec_int3_mods	(	CrankVecInt3*	a,
						const gint		b,
						CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x % b;
	r->y = a->y % b;
	r->z = a->z % b;
}

/**
 * crank_vec_int3_mods_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies modular on a vector.
 */
void
crank_vec_int3_mods_self	(	CrankVecInt3*	a,
								const gint		b)
{
	a->x %= b;
	a->y %= b;
	a->z %= b;
}

//////// Standard vector operations ////////

/**
 * crank_vec_int3_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_int3_add			(	CrankVecInt3*	a,
								CrankVecInt3*	b,
								CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x + b->x;
	r->y = a->y + b->y;
	r->z = a->z + b->z;
}

/**
 * crank_vec_int3_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_int3_add_self	(	CrankVecInt3*	a,
							CrankVecInt3*	b	)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

/**
 * crank_vec_int3_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_int3_sub	(	CrankVecInt3*	a,
						CrankVecInt3*	b,
						CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x - b->x;
	r->y = a->y - b->y;
	r->z = a->z - b->z;
}

/**
 * crank_vec_int3_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_int3_sub_self	(	CrankVecInt3*	a,
							CrankVecInt3*	b	)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

/**
 * crank_vec_int3_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
gint
crank_vec_int3_dot	(	CrankVecInt3*	a,
						CrankVecInt3*	b	)
{
	return 	(a->x) * (b->x) +
			(a->y) * (b->y) +
			(a->z) * (b->z);
}

/**
 * crank_vec_int3_crs:
 * @a: A vector
 * @b: A vector
 * @r: (out): A vector to store result.
 *
 * Gets cross product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
void
crank_vec_int3_crs	(	CrankVecInt3*	a,
						CrankVecInt3*	b,
						CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	guint	nx = (a->y * b->z) - (a->z * b->y);
	guint	ny = (a->z * b->x) - (a->x * b->z);
	guint	nz = (a->x * b->y) - (a->y * b->x);
	
	r->x = nx;
	r->y = ny;
	r->z = nz;
}

/**
 * crank_vec_int3_crs_self:
 * @a: A vector
 * @b: A vector
 *
 * Gets cross product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
void
crank_vec_int3_crs_self	(	CrankVecInt3*	a,
							CrankVecInt3*	b	)
{
	guint	nx = (a->y * b->z) - (a->z * b->y);
	guint	ny = (a->z * b->x) - (a->x * b->z);
	guint	nz = (a->x * b->y) - (a->y * b->x);
	
	a->x = nx;
	a->y = ny;
	a->z = nz;
}



//////// Component vector operations ////////

/**
 * crank_vec_int3_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_int3_cmpmul	(	CrankVecInt3*	a,
							CrankVecInt3*	b,
							CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x * b->x;
	r->y = a->y * b->y;
	r->z = a->z * b->z;
}

/**
 * crank_vec_int3_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_int3_cmpmul_self	(	CrankVecInt3*	a,
								CrankVecInt3*	b	)
{
	a->x *= b->x;
	a->y *= b->y;
	a->z *= b->z;
}


/**
 * crank_vec_int3_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise division.
 */
void
crank_vec_int3_cmpdiv	(	CrankVecInt3*	a,
							CrankVecInt3*	b,
							CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x / b->x;
	r->y = a->y / b->y;
	r->z = a->z / b->z;
}

/**
 * crank_vec_int3_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise division.
 */
void
crank_vec_int3_cmpdiv_self	(	CrankVecInt3*	a,
								CrankVecInt3*	b	)
{
	a->x /= b->x;
	a->y /= b->y;
	a->z /= b->z;
}

/**
 * crank_vec_int3_cmpmod:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise modular.
 */
void
crank_vec_int3_cmpmod	(	CrankVecInt3*	a,
							CrankVecInt3*	b,
							CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x % b->x;
	r->y = a->y % b->y;
	r->z = a->z % b->z;
}

/**
 * crank_vec_int3_cmpmod_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise modular.
 */
void
crank_vec_int3_cmpmod_self	(	CrankVecInt3*	a,
								CrankVecInt3*	b	)
{
	a->x %= b->x;
	a->y %= b->y;
	a->z %= b->z;
}

/**
 * crank_vec_int3_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_int3_cmpless	(	CrankVecInt3*	a,
							CrankVecInt3*	b,
							CrankVecBool3*	r	)
{
	r->x = (a->x) < (b->x);
	r->y = (a->y) < (b->y);
	r->z = (a->z) < (b->z);
}
												
/**
 * crank_vec_int3_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_int3_cmpeq	(	CrankVecInt3*	a,
							CrankVecInt3*	b,
							CrankVecBool3*	r	)
{
	r->x = (a->x) == (b->x);
	r->y = (a->y) == (b->y);
	r->z = (a->z) == (b->z);
}
												
/**
 * crank_vec_int3_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a is greater than counterpart of @b
 */					
void
crank_vec_int3_cmpgreater	(	CrankVecInt3*	a,
								CrankVecInt3*	b,
								CrankVecBool3*	r	)
{
	r->x = (a->x) > (b->x);
	r->y = (a->y) > (b->y);
	r->z = (a->z) > (b->z);
}
					
/**
 * crank_vec_int3_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets compare result of each components.
 */	
void
crank_vec_int3_cmpcmp	(		CrankVecInt3*	a,
								CrankVecInt3*	b,
								CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = CMP(a->x, b->x);
	r->y = CMP(a->y, b->y);
	r->z = CMP(a->z, b->z);
}

/**
 * crank_vec_int3_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_int3_min (	CrankVecInt3*	a,
						CrankVecInt3*	b,
						CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = MIN (a->x, b->x);
	r->y = MIN (a->y, b->y);
	r->z = MIN (a->z, b->z);
}

/**
 * crank_vec_int3_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_int3_max (	CrankVecInt3*	a,
						CrankVecInt3*	b,
						CrankVecInt3*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = MAX (a->x, b->x);
	r->y = MAX (a->y, b->y);
	r->z = MAX (a->z, b->z);
}

//////// GValue Transformation /////////////////////////////////////////////////

static void
crank_vec_int3_transform_from_b (	const GValue*	src,
									GValue*			dest	)
{
	CrankVecInt3*	res = g_new (CrankVecInt3, 1);
	crank_vec_int3_init_from_vb (res, (CrankVecBool3*) g_value_get_boxed (src));
	g_value_take_boxed (dest, res);
}

static void
crank_vec_int3_transform_to_string (const GValue*	src,
									GValue*			dest	)
{
	g_value_take_string (dest,
			crank_vec_int3_to_string ((CrankVecInt3*) g_value_get_boxed (src)));
}








static void	crank_vec_int4_transform_from_b (	const GValue*	src,
												GValue*			dest	);
												
static void crank_vec_int4_transform_to_string (const GValue*	src,
												GValue*			dest	);

G_DEFINE_BOXED_TYPE_WITH_CODE (
		CrankVecInt4,
		crank_vec_int4,
		crank_vec_int4_dup,
		g_free,
		{
			g_value_register_transform_func (	CRANK_TYPE_VEC_BOOL4,
												g_define_type_id,
												crank_vec_int4_transform_from_b	);
												
			g_value_register_transform_func (	g_define_type_id,
												G_TYPE_STRING,
												crank_vec_int4_transform_to_string	);
		} )

/**
 * crank_vec_int4_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 * @w: Fourth vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_int4_init	(	CrankVecInt4*	vec,
						gint			x,
						gint			y,
						gint			z,
						gint			w	)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	vec->w = w;
}

/**
 * crank_vec_int4_init_arr:
 * @vec: (out): Vector to initialize.
 * @arr: (array fixed-size=4): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_int4_init_arr	(	CrankVecInt4*	vec,
							gint*			arr	)
{
	vec->x = arr[0];
	vec->y = arr[1];
	vec->z = arr[2];
	vec->w = arr[3];
}

/**
 * crank_vec_int4_init_valist:
 * @vec: (out): Vector to initialize.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_int4_init_valist	(	CrankVecInt4*	vec,
								va_list			varargs	)
{
	vec->x = va_arg (varargs, gint);
	vec->y = va_arg (varargs, gint);
	vec->z = va_arg (varargs, gint);
	vec->w = va_arg (varargs, gint);
}

/**
 * crank_vec_int4_init_fill:
 * @vec: (out): Vector to initialize.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_int4_init_fill	(	CrankVecInt4*	vec,
								gint			fill	)
{
	vec->x = fill;
	vec->y = fill;
	vec->z = fill;
	vec->w = fill;
}

/**
 * crank_vec_int4_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_int4_init_from_vb	(	CrankVecInt4*	vec,
								CrankVecBool4*	vb		)
{
	vec->x = vb->x ? 1 : 0;
	vec->y = vb->y ? 1 : 0;
	vec->z = vb->z ? 1 : 0;
	vec->w = vb->w ? 1 : 0;
}


/**
 * crank_vec_int4_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_int4_copy			(	CrankVecInt4*	vec,
					   			CrankVecInt4*	other	)
{
  	memcpy (other, vec, sizeof (CrankVecInt4));
}


/**
 * crank_vec_int4_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecInt4*
crank_vec_int4_dup			(	CrankVecInt4*	vec	)
{
  	return (CrankVecInt4*) g_memdup (vec, sizeof (CrankVecInt4));
}

/**
 * crank_vec_int4_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
gint
crank_vec_int4_get	(	CrankVecInt4*	vec,
						const guint		index	)
{
	return ((gint*)vec)[index];
}

/**
 * crank_vec_int4_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_int4_set			(	CrankVecInt4*	vec,
								const guint		index,
								const gint		value	)
{
	((gint*)vec)[index] = value;
}

/**
 * crank_vec_int4_foreach:
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
crank_vec_int4_foreach (	CrankVecInt4*		vec,
							CrankBoolIntFunc	func,
							gpointer			userdata	)
{
	if (	func (vec->x, userdata) &&
	 		func (vec->y, userdata) &&
			func (vec->z, userdata) &&
			func (vec->w, userdata) )
		return TRUE;
	else
		return FALSE;
}

/**
 * crank_vec_int4_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_int4_iterator (	CrankVecInt4*		vec,
							CrankIterMemInt*	iter	)
{
	crank_iter_mem_int_init_with_count (iter, (gint*)vec, 4);
}

//////// Basic operation ////////

/**
 * crank_vec_int4_hash:
 * @a: (type CrankVecInt4): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_int4_hash (	gconstpointer	a	)
{
	const CrankVecInt4*	vec = a;
	guint				hash;
	
	hash  = g_direct_hash (GINT_TO_POINTER(vec->x));
	hash += g_direct_hash (GINT_TO_POINTER(vec->y)) + 37;
	hash += g_direct_hash (GINT_TO_POINTER(vec->z)) + 129;
	hash += g_direct_hash (GINT_TO_POINTER(vec->w)) + 1973;
	
	return hash;
}

/**
 * crank_vec_int4_equal:
 * @a: (type CrankVecInt4): Vector to compare.
 * @b: (type CrankVecInt4): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean		crank_vec_int4_equal (			gconstpointer	a,
												gconstpointer	b	)
{
	CrankVecInt4*	veca = (CrankVecInt4*)a;
	CrankVecInt4*	vecb = (CrankVecInt4*)b;
	
	return ((veca->x == vecb->x) &&
			(veca->y == vecb->y) &&
			(veca->z == vecb->z) &&
			(veca->w == vecb->w));
}

/**
 * crank_vec_int4_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4, 5, 6)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_int4_to_string (	CrankVecInt4*	vec	)
{
	return crank_vec_int4_to_string_full (vec, "(", ", ", ")", "%d");
}

/**
 * crank_vec_int4_to_string_full:
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
crank_vec_int4_to_string_full (	CrankVecInt4*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	format	)
{
	GString*	strb = g_string_new (left);
	gchar*		result;
	
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
 * crank_vec_int4_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
guint
crank_vec_int4_get_magn_sq	(	CrankVecInt4*	vec	)
{
	guint vx = (guint) ABS(vec->x);
	guint vy = (guint) ABS(vec->y);
	guint vz = (guint) ABS(vec->z);
	guint vw = (guint) ABS(vec->w);
	
	return (vx * vx) + (vy * vy) + (vz * vz) + (vw * vw);
}

/**
 * crank_vec_int4_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_int4_get_magn	(	CrankVecInt4*	vec	)
{
	gfloat sq = (gfloat) crank_vec_int4_get_magn_sq (vec);
	return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_int4_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_int4_neg (	CrankVecInt4*	a,
						CrankVecInt4*	r	)
{
	r->x = - (a->x);
	r->y = - (a->y);
	r->z = - (a->z);
	r->w = - (a->w);
}

/**
 * crank_vec_int4_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_int4_neg_self (	CrankVecInt4*	a	)
{
	a->x = - (a->x);
	a->y = - (a->y);
	a->z = - (a->z);
	a->w = - (a->w);
}


//////// Scalar operations ////////

/**
 * crank_vec_int4_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_int4_muls	(	CrankVecInt4*	a,
						const gint		b,
						CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x * b;
	r->y = a->y * b;
	r->z = a->z * b;
	r->w = a->w * b;
}

/**
 * crank_vec_int4_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_int4_muls_self	(	CrankVecInt4*	a,
								const gint		b	)
{
	a->x *= b;
	a->y *= b;
	a->z *= b;
	a->w *= b;
}

/**
 * crank_vec_int4_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_int4_divs	(	CrankVecInt4*	a,
						const gint		b,
						CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x / b;
	r->y = a->y / b;
	r->z = a->z / b;
	r->w = a->w / b;
}

/**
 * crank_vec_int4_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_int4_divs_self	(	CrankVecInt4*	a,
								const gint		b	)
{
	a->x /= b;
	a->y /= b;
	a->z /= b;
	a->w /= b;
}

/**
 * crank_vec_int4_mods:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Gets modular of each component.
 */
void
crank_vec_int4_mods	(	CrankVecInt4*	a,
						const gint		b,
						CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);

	r->x = a->x % b;
	r->y = a->y % b;
	r->z = a->z % b;
	r->w = a->w % b;
}

/**
 * crank_vec_int4_mods_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Gets modular of each component.
 */
void
crank_vec_int4_mods_self	(	CrankVecInt4*	a,
								const gint		b	)
{
	a->x %= b;
	a->y %= b;
	a->z %= b;
	a->w %= b;
}

//////// Standard vector operations ////////

/**
 * crank_vec_int4_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_int4_add			(	CrankVecInt4*	a,
								CrankVecInt4*	b,
								CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x + b->x;
	r->y = a->y + b->y;
	r->z = a->z + b->z;
	r->w = a->w + b->w;
}

/**
 * crank_vec_int4_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_int4_add_self	(	CrankVecInt4*	a,
							CrankVecInt4*	b	)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	a->w += b->w;
}

/**
 * crank_vec_int4_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_int4_sub	(	CrankVecInt4*	a,
						CrankVecInt4*	b,
						CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x - b->x;
	r->y = a->y - b->y;
	r->z = a->z - b->z;
	r->w = a->w - b->w;
}

/**
 * crank_vec_int4_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_int4_sub_self	(	CrankVecInt4*	a,
							CrankVecInt4*	b	)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	a->w -= b->w;
}

/**
 * crank_vec_int4_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
gint
crank_vec_int4_dot	(	CrankVecInt4*	a,
						CrankVecInt4*	b	)
{
	return 	(a->x) * (b->x) +
			(a->y) * (b->y) +
			(a->z) * (b->z) +
			(a->w) * (b->w);
}

//////// Component vector operations ////////

/**
 * crank_vec_int4_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_int4_cmpmul	(	CrankVecInt4*	a,
							CrankVecInt4*	b,
							CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x * b->x;
	r->y = a->y * b->y;
	r->z = a->z * b->z;
	r->w = a->w * b->w;
}

/**
 * crank_vec_int4_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_int4_cmpmul_self	(	CrankVecInt4*	a,
								CrankVecInt4*	b	)
{
	a->x *= b->x;
	a->y *= b->y;
	a->z *= b->z;
	a->w *= b->w;
}

/**
 * crank_vec_int4_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise division.
 */
void
crank_vec_int4_cmpdiv	(	CrankVecInt4*	a,
							CrankVecInt4*	b,
							CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x / b->x;
	r->y = a->y / b->y;
	r->z = a->z / b->z;
	r->w = a->w / b->w;
}

/**
 * crank_vec_int4_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise division.
 */
void
crank_vec_int4_cmpdiv_self	(	CrankVecInt4*	a,
								CrankVecInt4*	b	)
{
	a->x /= b->x;
	a->y /= b->y;
	a->z /= b->z;
	a->w /= b->w;
}

/**
 * crank_vec_int4_cmpmod:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise modular.
 */
void
crank_vec_int4_cmpmod	(	CrankVecInt4*	a,
							CrankVecInt4*	b,
							CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = a->x % b->x;
	r->y = a->y % b->y;
	r->z = a->z % b->z;
	r->w = a->w % b->w;
}

/**
 * crank_vec_int4_cmpmod_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise modular.
 */
void
crank_vec_int4_cmpmod_self	(	CrankVecInt4*	a,
								CrankVecInt4*	b	)
{
	a->x %= b->x;
	a->y %= b->y;
	a->z %= b->z;
	a->w %= b->w;
}

/**
 * crank_vec_int4_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_int4_cmpless	(	CrankVecInt4*	a,
							CrankVecInt4*	b,
							CrankVecBool4*	r	)
{
	r->x = (a->x) < (b->x);
	r->y = (a->y) < (b->y);
	r->z = (a->z) < (b->z);
	r->w = (a->w) < (b->w);
}
												
/**
 * crank_vec_int4_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_int4_cmpeq	(	CrankVecInt4*	a,
							CrankVecInt4*	b,
							CrankVecBool4*	r	)
{
	r->x = (a->x) == (b->x);
	r->y = (a->y) == (b->y);
	r->z = (a->z) == (b->z);
	r->w = (a->w) == (b->w);
}
												
/**
 * crank_vec_int4_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a is greater than counterpart of @b
 */					
void
crank_vec_int4_cmpgreater	(	CrankVecInt4*	a,
								CrankVecInt4*	b,
								CrankVecBool4*	r	)
{
	r->x = (a->x) > (b->x);
	r->y = (a->y) > (b->y);
	r->z = (a->z) > (b->z);
	r->w = (a->w) > (b->w);
}
					
/**
 * crank_vec_int4_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets compare result of each components.
 */	
void
crank_vec_int4_cmpcmp	(		CrankVecInt4*	a,
								CrankVecInt4*	b,
								CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = CMP(a->x, b->x);
	r->y = CMP(a->y, b->y);
	r->z = CMP(a->z, b->z);
	r->w = CMP(a->w, b->w);
}

/**
 * crank_vec_int4_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_int4_min (	CrankVecInt4*	a,
						CrankVecInt4*	b,
						CrankVecInt4*	r	)
{
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);

	r->x = MIN (a->x, b->x);
	r->y = MIN (a->y, b->y);
	r->z = MIN (a->z, b->z);
	r->w = MIN (a->w, b->w);
}

/**
 * crank_vec_int4_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_int4_max (	CrankVecInt4*	a,
						CrankVecInt4*	b,
						CrankVecInt4*	r	)
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
crank_vec_int4_transform_from_b (	const GValue*	src,
									GValue*			dest	)
{
	CrankVecInt4*	res = g_new (CrankVecInt4, 1);
	crank_vec_int4_init_from_vb (res, (CrankVecBool4*) g_value_get_boxed (src));
	g_value_take_boxed (dest, res);
}

static void
crank_vec_int4_transform_to_string (const GValue*	src,
									GValue*			dest	)
{
	g_value_take_string (dest,
			crank_vec_int4_to_string ((CrankVecInt4*) g_value_get_boxed (src)));
}







static void	crank_vec_int_n_transform_from_b (	const GValue*	src,
												GValue*			dest	);
												
static void	crank_vec_int_n_transform_from_v2 (	const GValue*	src,
												GValue*			dest	);
												
static void	crank_vec_int_n_transform_from_v3 (	const GValue*	src,
												GValue*			dest	);
												
static void	crank_vec_int_n_transform_from_v4 (	const GValue*	src,
												GValue*			dest	);
												
static void crank_vec_int_n_transform_to_string (const GValue*	src,
												GValue*			dest	);


G_DEFINE_BOXED_TYPE_WITH_CODE (
		CrankVecIntN,
		crank_vec_int_n,
		crank_vec_int_n_dup,
		crank_vec_int_n_free,
		{
			g_value_register_transform_func (	CRANK_TYPE_VEC_BOOL_N,
												g_define_type_id,
												crank_vec_int_n_transform_from_b	);
												
			g_value_register_transform_func (	CRANK_TYPE_VEC_INT2,
												g_define_type_id,
												crank_vec_int_n_transform_from_v2	);
												
			g_value_register_transform_func (	CRANK_TYPE_VEC_INT3,
												g_define_type_id,
												crank_vec_int_n_transform_from_v3	);
												
			g_value_register_transform_func (	CRANK_TYPE_VEC_INT4,
												g_define_type_id,
												crank_vec_int_n_transform_from_v4	);
												
			g_value_register_transform_func (	g_define_type_id,
												G_TYPE_STRING,
												crank_vec_int_n_transform_to_string	);
		} )

/**
 * crank_vec_int_n_init:
 * @vec: (out): Vector to initialize.
 * @n: length of vector.
 * @...: elements of vector.
 *
 * Initializes vector with given components.
 */
void
crank_vec_int_n_init	(	CrankVecIntN*	vec,
							const guint		n,
							...	)
{
	va_list	varargs;
	va_start (varargs, n);
	
	crank_vec_int_n_init_valist (vec, n, varargs);
	
	va_end (varargs);
}

/**
 * crank_vec_int_n_init_arr:
 * @vec: (out): Vector to initialize.
 * @n: length of vector
 * @arr: (array length=n): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_int_n_init_arr	(	CrankVecIntN*	vec,
								const guint		n,
								gint*			arr	)
{
	vec->data = CRANK_ARRAY_DUP (arr, gint, n);
	vec->n = n;
}

/**
 * crank_vec_int_n_init_valist:
 * @vec: (out): Vector to initialize.
 * @n: length of vector
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_int_n_init_valist	(	CrankVecIntN*	vec,
								const guint		n,
								va_list			varargs	)
{
	guint i;

	CRANK_VEC_ALLOC(vec,gint,n);
	
	for (i = 0; i <n; i++) {
		vec->data[i] = va_arg (varargs, gint);
	}
}

/**
 * crank_vec_int_n_init_fill:
 * @vec: (out): Vector to initialize.
 * @n: length of vector
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_int_n_init_fill	(	CrankVecIntN*	vec,
								const guint		n,
								gint			fill	)
{
	guint i;

	CRANK_VEC_ALLOC(vec,gint,n);
	
	for (i = 0; i < n; i++) {
		vec->data[i] = fill;
	}
}

/**
 * crank_vec_int_n_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector, which has same length of it.
 */
void
crank_vec_int_n_init_from_vb	(	CrankVecIntN*	vec,
									CrankVecBoolN*	vb		)
{
	guint i;

	CRANK_VEC_ALLOC(vec,gint,vb->n);
	
	for (i = 0; i < vb->n; i++) {
		vec->data[i] = vb->data[i] ? 1 : 0;
	}
}

/**
 * crank_vec_int_n_fini:
 * @vec: Vector to finalize.
 *
 * Finalize the datas and unset the vector, so that @vec will point 0-length data at %NULL.
 */
 void
 crank_vec_int_n_fini			(	CrankVecIntN*	vec	)
{
	g_free (vec->data);
	vec->n = 0;
	vec->data = NULL;
}


/**
 * crank_vec_int_n_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_int_n_copy			(	CrankVecIntN*	vec,
									CrankVecIntN*	other	)
{
	crank_vec_int_n_init_arr (other, vec->n, vec->data);
}

/**
 * crank_vec_int_n_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecIntN*
crank_vec_int_n_dup			(	CrankVecIntN*	vec	)
{
  	CrankVecIntN*	result = g_new0 (CrankVecIntN, 1);

  	crank_vec_int_n_init_arr (result, vec->n, vec->data);

  	return result;
}

/**
 * crank_vec_int_n_free:
 * @vec: Vector to free.
 *
 * Frees an allocated vector. Use with crank_vec_int_n_dup().
 */
void
crank_vec_int_n_free ( CrankVecIntN*	vec )
{
	crank_vec_int_n_fini (vec);
	g_free (vec);
}

/**
 * crank_vec_int_n_get_size:
 * @vec: Vector to get size.
 *
 * Gets size of vector.
 *
 * Returns: Size of vector.
 */
guint
crank_vec_int_n_get_size (	CrankVecIntN*	vec	)
{
	return vec->n;
}

/**
 * crank_vec_int_n_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 *
 * Gets element of vector at @index.
 *
 * Returns: element on vector.
 */
gint
crank_vec_int_n_get	(	CrankVecIntN*	vec,
						const guint		index	)
{
	return vec->data[index];
}

/**
 * crank_vec_int_n_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_int_n_set			(	CrankVecIntN*	vec,
								const guint		index,
								const gint		value	)
{
	vec->data[index] = value;
}

/**
 * crank_vec_int_n_prepend:
 * @vec: A Vector to insert element.
 * @value: Value of element.
 *
 * Prepends an element to vector.
 */
void
crank_vec_int_n_prepend (	CrankVecIntN*	vec,
						 	const gint		value	)
{
  	crank_vec_int_n_insert (vec, 0, value);
}

/**
 * crank_vec_int_n_append:
 * @vec: A Vector to insert element.
 * @value: Value of element.
 *
 * Appends an element to vector.
 */
void
crank_vec_int_n_append (	CrankVecIntN*	vec,
							const gint		value	)
{
  	crank_vec_int_n_insert (vec, vec->n, value);
}

/**
 * crank_vec_int_n_insert:
 * @vec: A Vector to insert element.
 * @index: Index to insert element.
 * @value: Value of element.
 *
 * Insert an element to vector.
 */
void
crank_vec_int_n_insert (	CrankVecIntN*	vec,
							const guint		index,
							const gint		value	)
{
	guint	i = 0;

	g_return_if_fail (index <= vec->n);

	vec->data = g_renew (gint, vec->data, vec->n + 1);

  	for (i = vec->n - 1; index <= i; i--)
		vec->data[i + 1] = vec->data[i];

	vec->data[index] = value;

  	vec->n ++;
}

/**
 * crank_vec_int_n_remove:
 * @vec: A Vector to remove element.
 * @index: Index to remove element.
 *
 * Remove an element from vector.
 */
void
crank_vec_int_n_remove (	CrankVecIntN*	vec,
							const guint		index	)
{
	guint	i = 0;

	g_return_if_fail (index < vec->n);

  	vec->n--;
  	for (i = index; i < vec->n; i++)
		vec->data[i] = vec->data[i + 1];

	vec->data = g_renew (gint, vec->data, vec->n);
}

/**
 * crank_vec_int_n_foreach:
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
crank_vec_int_n_foreach (	CrankVecIntN*		vec,
							CrankBoolIntFunc	func,
							gpointer			userdata	)
{
  	guint	i;

  	for (i = 0; i < vec->n; i++)
	  	if (! func(vec->data[i], userdata)) return FALSE;

  	return TRUE;
}

/**
 * crank_vec_int_n_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_int_n_iterator (	CrankVecIntN*		vec,
							CrankIterMemInt*	iter	)
{
	crank_iter_mem_int_init_with_count (iter, vec->data, vec->n);
}

//////// Basic operation ////////

/**
 * crank_vec_int_n_hash:
 * @a: (type CrankVecIntN): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_int_n_hash (	gconstpointer	a	)
{
	const CrankVecIntN*	vec = a;
	guint				hash = 0;
	
	guint				i;
	
	CRANK_FOREACH_ARRAY_DO (vec->data, gint, e, vec->n,
			{hash += g_direct_hash (GINT_TO_POINTER(e)) + 37;}	)
	
	return hash;
}

/**
 * crank_vec_int_n_equal:
 * @a: (type CrankVecIntN): Vector to compare.
 * @b: (type CrankVecIntN): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean		crank_vec_int_n_equal (			gconstpointer	a,
												gconstpointer	b	)
{
	CrankVecIntN*	veca = (CrankVecIntN*)a;
	CrankVecIntN*	vecb = (CrankVecIntN*)b;
	
	guint			i;
	
	for (i = 0; i < veca->n; i ++) {
		if (veca->data[i] != vecb->data[i]) return FALSE;
	}
	return TRUE;
}

/**
 * crank_vec_int_n_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3, 4, 5, 6)
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_int_n_to_string (	CrankVecIntN*	vec	)
{
	return crank_vec_int_n_to_string_full (vec, "(", ", ", ")", "%d");
}

/**
 * crank_vec_int_n_to_string_full:
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
crank_vec_int_n_to_string_full (	CrankVecIntN*	vec,
									const gchar*	left,
									const gchar*	in,
									const gchar*	right,
									const gchar*	format	)
{
	GString*	strb = g_string_new (left);
	gchar*		result;
	
	guint		i;
	
	if (0 < vec->n) {
		g_string_append_printf (strb, format, vec->data[0]);
		
		for (i = 1; i < vec->n; i++) {
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
 * crank_vec_int_n_is_zero:
 * @vec: A Vector.
 * 
 * Checks whether the vector is "Zero vector", whose all components are 0.
 *
 * Returns: whether the vector is "zero vector".
 */
gboolean
crank_vec_int_n_is_zero (	CrankVecIntN*	vec	)
{
	guint	i;
	
	for (i = 0; i < vec->n; i++) {
		if (vec->data[i] != 0) return FALSE;
	}
	return TRUE;
}

/**
 * crank_vec_int_n_is_one:
 * @vec: A Vector.
 * 
 * Checks whether the vector has all components as 1. This kind of vectors are
 * often identity in component-wise operations.
 *
 * Returns: whether the vector has all component as 1.
 */
gboolean
crank_vec_int_n_is_one (	CrankVecIntN*	vec	)
{
	guint	i;
	
	for (i = 0; i < vec->n; i++) {
		if (vec->data[i] != 1) return FALSE;
	}
	return TRUE;
}

/**
 * crank_vec_int_n_is_empty:
 * @vec: A Vector.
 * 
 * Checks whether the vector is empty.
 *
 * Returns: whether the vector is empty.
 */
gboolean
crank_vec_int_n_is_empty (	CrankVecIntN*	vec	)
{
	return vec->n == 0;
}

//////// Standard vector property ///////

/**
 * crank_vec_int_n_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
guint
crank_vec_int_n_get_magn_sq	(	CrankVecIntN*	vec	)
{
	guint		result = 0;
	
	CRANK_FOREACH_ARRAY_BEGIN (vec->data, gint, e, vec->n)
		guint u = (guint) ABS(e);
		result += u*u;
	CRANK_FOREACH_ARRAY_END
	
	return result;
}

/**
 * crank_vec_int_n_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_int_n_get_magn	(	CrankVecIntN*	vec	)
{
	gfloat sq = (gfloat) crank_vec_int_n_get_magn_sq (vec);
	return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_int_n_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_int_n_neg (	CrankVecIntN*	a,
						CrankVecIntN*	r	)
{
	guint	i;
	
	CRANK_VEC_ALLOC(r,gint,a->n);
	
	for (i = 0; i < a->n; i++)		r->data[i] = - a->data[i];
}

/**
 * crank_vec_int_n_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_int_n_neg_self (	CrankVecIntN*	a	)
{
	guint	i;
	for (i = 0; i < a->n; i++)		a->data[i] = - a->data[i];
}



//////// Scalar operations ////////

/**
 * crank_vec_int_n_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_int_n_muls	(	CrankVecIntN*	a,
							const gint		b,
							CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	
	CRANK_VEC_ALLOC(r,gint,a->n);
	
	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] * b;
}

/**
 * crank_vec_int_n_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_int_n_muls_self	(	CrankVecIntN*	a,
								const gint		b	)
{
	guint	i;
	for (i = 0; i < a->n; i++)		a->data[i] *= b;
}

/**
 * crank_vec_int_n_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_int_n_divs	(	CrankVecIntN*	a,
							const gint		b,
							CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	CRANK_VEC_ALLOC(r,gint,a->n);
	
	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] / b;
}

/**
 * crank_vec_int_n_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_int_n_divs_self	(	CrankVecIntN*	a,
								const gint		b	)
{
	guint	i;
	
	for (i = 0; i < a->n; i++)		a->data[i] /= b;
}

/**
 * crank_vec_int_n_mods:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Gets modular of each component.
 */
void
crank_vec_int_n_mods	(	CrankVecIntN*	a,
						const gint		b,
						CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	CRANK_VEC_ALLOC(r,gint,a->n);
	
	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] % b;
}

/**
 * crank_vec_int_n_mods_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Gets modular of each component.
 */
void
crank_vec_int_n_mods_self	(	CrankVecIntN*	a,
								const gint		b	)
{
	guint	i;
	for (i = 0; i < a->n; i++)		a->data[i] %= b;
}

//////// Standard vector operations ////////

/**
 * crank_vec_int_n_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_int_n_add			(	CrankVecIntN*	a,
								CrankVecIntN*	b,
								CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "add", a, b);
	CRANK_VEC_ALLOC(r,gint,a->n);

	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] + b->data[i];
}

/**
 * crank_vec_int_n_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_int_n_sub	(	CrankVecIntN*	a,
						CrankVecIntN*	b,
						CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "sub", a, b);
	CRANK_VEC_ALLOC(r,gint,a->n);

	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] - b->data[i];
}

/**
 * crank_vec_int_n_dot:
 * @a: A vector
 * @b: A vector
 *
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
gint
crank_vec_int_n_dot	(	CrankVecIntN*	a,
						CrankVecIntN*	b	)
{
	gint	result = 0;
	guint	i;
	
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2_RET("VecIntN", "dot", a, b, 0.0f);
	
	for (i = 0; i < a->n; i++)		result += (a->data[i] * b->data[i]);
	
	return result;
}

//////// Component vector operations ////////

/**
 * crank_vec_int_n_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_int_n_cmpmul	(	CrankVecIntN*	a,
							CrankVecIntN*	b,
							CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpmul", a, b);
	CRANK_VEC_ALLOC(r,gint,a->n);

	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] * b->data[i];
}

/**
 * crank_vec_int_n_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Apply component-wise multiplication.
 */
void
crank_vec_int_n_cmpmul_self	(	CrankVecIntN*	a,
								CrankVecIntN*	b	)
{
	guint	i;
	
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpmul-self", a, b);

	for (i = 0; i < a->n; i++)		a->data[i] *= b->data[i];
}

/**
 * crank_vec_int_n_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise division.
 */
void
crank_vec_int_n_cmpdiv	(	CrankVecIntN*	a,
							CrankVecIntN*	b,
							CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpdiv", a, b);
	CRANK_VEC_ALLOC(r,gint,a->n);

	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] / b->data[i];
}

/**
 * crank_vec_int_n_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Apply component-wise multiplication.
 */
void
crank_vec_int_n_cmpdiv_self	(	CrankVecIntN*	a,
								CrankVecIntN*	b	)
{
	guint	i;
	
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpdiv-self", a, b);

	for (i = 0; i < a->n; i++)		a->data[i] /= b->data[i];
}

/**
 * crank_vec_int_n_cmpmod:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise modular.
 */
void
crank_vec_int_n_cmpmod	(	CrankVecIntN*	a,
							CrankVecIntN*	b,
							CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpmod", a, b);
	CRANK_VEC_ALLOC(r,gint,a->n);

	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] % b->data[i];
}

/**
 * crank_vec_int_n_cmpmod_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Apply component-wise multiplication.
 */
void
crank_vec_int_n_cmpmod_self	(	CrankVecIntN*	a,
								CrankVecIntN*	b	)
{
	guint	i;
	
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpmod-self", a, b);

	for (i = 0; i < a->n; i++)		a->data[i] %= b->data[i];
}

/**
 * crank_vec_int_n_cmpless:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a is less than counterpart of @b
 */
void
crank_vec_int_n_cmpless	(	CrankVecIntN*	a,
							CrankVecIntN*	b,
							CrankVecBoolN*	r	)
{
	guint	i;
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpless", a, b);
	CRANK_VEC_ALLOC(r,gboolean,a->n);

	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] < b->data[i];
}
												
/**
 * crank_vec_int_n_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_int_n_cmpeq	(	CrankVecIntN*	a,
							CrankVecIntN*	b,
							CrankVecBoolN*	r	)
{
	guint	i;
	
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpeq", a, b);
	CRANK_VEC_ALLOC(r,gboolean,a->n);

	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] == b->data[i];
}
												
/**
 * crank_vec_int_n_cmpgreater:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a is greater than counterpart of @b
 */					
void
crank_vec_int_n_cmpgreater	(	CrankVecIntN*	a,
								CrankVecIntN*	b,
								CrankVecBoolN*	r	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpgreater", a, b);
	CRANK_VEC_ALLOC(r,gboolean,a->n);

	for (i = 0; i < a->n; i++)		r->data[i] = a->data[i] > b->data[i];
}
					
/**
 * crank_vec_int_n_cmpcmp:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets compare result of each components.
 */	
void
crank_vec_int_n_cmpcmp	(		CrankVecIntN*	a,
								CrankVecIntN*	b,
								CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "cmpcmp", a, b);
	CRANK_VEC_ALLOC(r,gint,a->n);

	for (i = 0; i < a->n; i++) {
		r->data[i] = CMP (a->data[i], b->data[i]);
	}
}

/**
 * crank_vec_int_n_min:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets smaller value of each components.
 */
void
crank_vec_int_n_min (	CrankVecIntN*	a,
						CrankVecIntN*	b,
						CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "min", a, b);
	CRANK_VEC_ALLOC(r,gint,a->n);

	for (i = 0; i < a->n; i++) {
		r->data[i] = MIN (a->data[i], b->data[i]);
	}
}

/**
 * crank_vec_int_n_max:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Gets greater value of each components.
 */
void
crank_vec_int_n_max (	CrankVecIntN*	a,
						CrankVecIntN*	b,
						CrankVecIntN*	r	)
{
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecIntN", "max", a, b);
	CRANK_VEC_ALLOC(r,gint,a->n);

	for (i = 0; i < a->n; i++) {
		r->data[i] = MAX (a->data[i], b->data[i]);
	}
}

//////// GValue Transformation /////////////////////////////////////////////////

static void
crank_vec_int_n_transform_from_b (	const GValue*	src,
									GValue*			dest	)
{
	CrankVecIntN*	res = g_new (CrankVecIntN, 1);
	crank_vec_int_n_init_from_vb (res, (CrankVecBoolN*) g_value_get_boxed (src));
	g_value_take_boxed (dest, res);
}

static void
crank_vec_int_n_transform_from_v2 (	const GValue*	src,
									GValue*			dest	)
{
	CrankVecIntN*	res = g_new (CrankVecIntN, 1);
	crank_vec_int_n_init_arr (res, 2, (gint*) g_value_get_boxed (src));
	
	g_value_take_boxed (dest, res);
}

static void
crank_vec_int_n_transform_from_v3 (	const GValue*	src,
									GValue*			dest	)
{
	CrankVecIntN*	res = g_new (CrankVecIntN, 1);
	crank_vec_int_n_init_arr (res, 3, (gint*) g_value_get_boxed (src));
	
	g_value_take_boxed (dest, res);
}

static void
crank_vec_int_n_transform_from_v4 (	const GValue*	src,
									GValue*			dest	)
{
	CrankVecIntN*	res = g_new (CrankVecIntN, 1);
	crank_vec_int_n_init_arr (res, 4, (gint*) g_value_get_boxed (src));
	
	g_value_take_boxed (dest, res);
}

static void
crank_vec_int_n_transform_to_string (const GValue*	src,
									GValue*			dest	)
{
	g_value_take_string (dest,
			crank_vec_int_n_to_string ((CrankVecIntN*) g_value_get_boxed (src)));
}




