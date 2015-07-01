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
 * @title: Integer vectors.
 * @short_description: Vectors that have integer elements.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Crank System provides 2, 3, 4, and free sized float vectors for convinience.
 *
 * Currently following operations are supported.
 *
 * It is compared to vec in GLSL
 *
 * * Basic Operations
 *    * hashing
 *    * equality check
 *    * stringify
 * * Vector properties
 *    * Magnitude/Norm
 * * Unary operations.
 *    * Negate
 *    * Unitify
 * * Scalar operations
 *    * Scalar multiplication
 *    * Scalar division
 * * Vector operations
 *    * Vector addition
 *    * Vector subtration
 *    * Dot product
 * * Component operations
 *    * Component multiplication
 *    * Component division
 *    * Component comparsion
 *    * minimum/maximum
 */


#define CMP(a, b) (((a) > (b)) - ((a) < (b)))

G_DEFINE_BOXED_TYPE (CrankVecInt2, crank_vec_int2, crank_vec_int2_copy, g_free)

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
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecInt2*
crank_vec_int2_copy			(	CrankVecInt2*	vec	)
{
	CrankVecInt2* result = g_new (CrankVecInt2, 1);
	
	crank_vec_int2_init_arr (result, (gint*)vec);
	
	return result;
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
	r->x = a->x * b;
	r->y = a->y * b;
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
	r->x = a->x / b;
	r->y = a->y / b;
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
	r->x = a->x % b;
	r->y = a->y % b;
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
	r->x = a->x + b->x;
	r->y = a->y + b->y;
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
	r->x = a->x - b->x;
	r->y = a->y - b->y;
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
	r->x = a->x * b->x;
	r->y = a->y * b->y;
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
	r->x = a->x / b->x;
	r->y = a->y / b->y;
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
	r->x = a->x % b->x;
	r->y = a->y % b->y;
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
	r->x = MAX (a->x, b->x);
	r->y = MAX (a->y, b->y);
}








G_DEFINE_BOXED_TYPE (CrankVecInt3, crank_vec_int3, crank_vec_int3_copy, g_free)

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
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecInt3*
crank_vec_int3_copy			(	CrankVecInt3*	vec	)
{
	CrankVecInt3* result = g_new (CrankVecInt3, 1);
	
	crank_vec_int3_init_arr (result, (gint*)vec);
	
	return result;
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
	r->x = a->x * b;
	r->y = a->y * b;
	r->z = a->z * b;
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
	r->x = a->x / b;
	r->y = a->y / b;
	r->z = a->z / b;
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
	r->x = a->x % b;
	r->y = a->y % b;
	r->z = a->z % b;
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
	r->x = a->x + b->x;
	r->y = a->y + b->y;
	r->z = a->z + b->z;
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
	r->x = a->x - b->x;
	r->y = a->y - b->y;
	r->z = a->z - b->z;
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
 * Gets dot product of two vectors.
 *
 * Returns: dot product of two vectors.
 */
void
crank_vec_int3_crs	(	CrankVecInt3*	a,
						CrankVecInt3*	b,
						CrankVecInt3*	r	)
{
	guint	nx = (a->y * b->z) - (a->z * b->y);
	guint	ny = (a->z * b->x) - (a->x * b->z);
	guint	nz = (a->x * b->y) - (a->y * b->x);
	
	r->x = nx;
	r->y = ny;
	r->z = nz;
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
	r->x = a->x * b->x;
	r->y = a->y * b->y;
	r->z = a->z * b->z;
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
	r->x = a->x / b->x;
	r->y = a->y / b->y;
	r->z = a->z / b->z;
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
	r->x = a->x % b->x;
	r->y = a->y % b->y;
	r->z = a->z % b->z;
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
	r->x = MAX (a->x, b->x);
	r->y = MAX (a->y, b->y);
	r->z = MAX (a->z, b->z);
}







G_DEFINE_BOXED_TYPE (CrankVecInt4, crank_vec_int4, crank_vec_int4_copy, g_free)

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
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecInt4*
crank_vec_int4_copy			(	CrankVecInt4*	vec	)
{
	CrankVecInt4* result = g_new (CrankVecInt4, 1);
	
	crank_vec_int4_init_arr (result, (gint*)vec);
	
	return result;
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
	r->x = a->x * b;
	r->y = a->y * b;
	r->z = a->z * b;
	r->w = a->w * b;
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
	r->x = a->x / b;
	r->y = a->y / b;
	r->z = a->z / b;
	r->w = a->w / b;
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
	r->x = a->x % b;
	r->y = a->y % b;
	r->z = a->z % b;
	r->w = a->w % b;
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
	r->x = a->x + b->x;
	r->y = a->y + b->y;
	r->z = a->z + b->z;
	r->w = a->w + b->w;
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
	r->x = a->x - b->x;
	r->y = a->y - b->y;
	r->z = a->z - b->z;
	r->w = a->w - b->w;
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
	r->x = a->x * b->x;
	r->y = a->y * b->y;
	r->z = a->z * b->z;
	r->w = a->w * b->w;
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
	r->x = a->x / b->x;
	r->y = a->y / b->y;
	r->z = a->z / b->z;
	r->w = a->w / b->w;
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
	r->x = a->x % b->x;
	r->y = a->y % b->y;
	r->z = a->z % b->z;
	r->w = a->w % b->w;
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
	r->x = MAX (a->x, b->x);
	r->y = MAX (a->y, b->y);
	r->z = MAX (a->z, b->z);
	r->w = MAX (a->w, b->w);
}








G_DEFINE_BOXED_TYPE (CrankVecIntN, crank_vec_int_n, crank_vec_int_n_copy, g_free)

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
	g_free (vec->data);

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

	g_free (vec->data);
	
	vec->data = g_new (gint, n);
	vec->n = n;
	
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

	g_free (vec->data);
	
	vec->data = g_new (gint, n);
	vec->n = n;
	
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

	g_free (vec->data);
	
	vec->data = g_new (gint, vb->n);
	vec->n = vb->n;
	
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
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecIntN*
crank_vec_int_n_copy			(	CrankVecIntN*	vec	)
{
	CrankVecIntN* result = g_new (CrankVecIntN, 1);
	
	crank_vec_int_n_init_arr (result, vec->n, vec->data);
	
	return result;
}

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
	
	if (r->n != a->n) {
		r->n = a->n;
		r->data = g_renew (gint, r->data, r->n);
	}
	
	for (i = 0; i < a->n; i++) {
		r->data[i] = - a->data[i];
	}
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
	
	if (r->n != a->n) {
		r->n = a->n;
		r->data = g_renew (gint, r->data, r->n);
	}
	
	for (i = 0; i < a->n; i++) {
		r->data[i] = a->data[i] * b;
	}
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
	
	if (r->n != a->n) {
		r->n = a->n;
		r->data = g_renew (gint, r->data, r->n);
	}
	
	for (i = 0; i < a->n; i++) {
		r->data[i] = a->data[i] / b;
	}
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
	
	if (r->n != a->n) {
		r->n = a->n;
		r->data = g_renew (gint, r->data, r->n);
	}
	
	for (i = 0; i < a->n; i++) {
		r->data[i] = a->data[i] % b;
	}
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gint, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = a->data[i] + b->data[i];
		}
	}
	else g_warning ("VecIntN: add: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gint, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = a->data[i] - b->data[i];
		}
	}
	else g_warning ("VecIntN: sub: size mismatch: %d, %d", a->n, b->n);
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
	
	if (a->n == b->n) {
		for (i = 0; i < a->n; i++) {
			result += (a->data[i] * b->data[i]);
		}
	}
	else g_warning ("VecIntN: dot: size mismatch: %d, %d", a->n, b->n);
	
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gint, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = a->data[i] * b->data[i];
		}
	}
	else g_warning ("VecIntN: cmpmul: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gint, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = a->data[i] / b->data[i];
		}
	}
	else g_warning ("VecIntN: cmpdiv: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gint, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = a->data[i] % b->data[i];
		}
	}
	else g_warning ("VecIntN: cmpmod: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gboolean, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = a->data[i] < b->data[i];
		}
	}
	else g_warning ("VecIntN: cmpless: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gboolean, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = a->data[i] == b->data[i];
		}
	}
	else g_warning ("VecIntN: cmpeq: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gboolean, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = a->data[i] > b->data[i];
		}
	}
	else g_warning ("VecIntN: cmpgreater: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gint, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = CMP (a->data[i], b->data[i]);
		}
	}
	else g_warning ("VecIntN: cmpcmp: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gint, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = MIN (a->data[i], b->data[i]);
		}
	}
	else g_warning ("VecIntN: min: size mismatch: %d, %d", a->n, b->n);
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
	if (a->n == b->n) {
		if (r->n != a->n) {
			r->n = a->n;
			r->data = g_renew (gint, r->data, r->n);
		}
	
		for (i = 0; i < a->n; i++) {
			r->data[i] = MAX (a->data[i], b->data[i]);
		}
	}
	else g_warning ("VecIntN: max: size mismatch: %d, %d", a->n, b->n);
}







