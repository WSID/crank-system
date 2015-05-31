/* Copyright (C) 2015, WSID   */

/* This file is part of Crank System.
 *
 *  Crank System is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  Crank System is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with Crank System.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#define _CRANKBASE_INSIDE

#include <math.h>
#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankvecbool.h"
#include "crankvecint.h"
#include "crankvecfloat.h"

/**
 * SECTION: crankvecfloat
 * @title: Float vectors.
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
#define EQ

G_DEFINE_BOXED_TYPE (CrankVecFloat2, crank_vec_float2, crank_vec_float2_copy, g_free)

/**
 * crank_vec_float2_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 *
 * Initializes vector with given components.
 */
void
crank_vec_float2_init	(	CrankVecFloat2*	vec,
							gfloat			x,
							gfloat			y	)
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
crank_vec_float2_init_arr	(	CrankVecFloat2*	vec,
								gfloat*			arr	)
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
crank_vec_float2_init_valist	(	CrankVecFloat2*	vec,
									va_list			varargs	)
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
crank_vec_float2_init_fill	(	CrankVecFloat2*	vec,
								gfloat			fill	)
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
crank_vec_float2_init_from_vb	(	CrankVecFloat2*	vec,
								CrankVecBool2*	vb		)
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
crank_vec_float2_init_from_vi	(	CrankVecFloat2*	vec,
									CrankVecInt2*	vi		)
{
	vec->x = vi->x;
	vec->y = vi->y;
}


/**
 * crank_vec_float2_copy:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by g_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecFloat2*
crank_vec_float2_copy			(	CrankVecFloat2*	vec	)
{
	CrankVecFloat2* result = g_new (CrankVecFloat2, 1);
	
	crank_vec_float2_init_arr (result, (gfloat*)vec);
	
	return result;
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
crank_vec_float2_get	(	CrankVecFloat2*	vec,
							const guint		index	)
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
crank_vec_float2_set			(	CrankVecFloat2*	vec,
									const guint		index,
									const gfloat		value	)
{
	((gfloat*)vec)[index] = value;
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
crank_vec_float2_hash (	gconstpointer	a	)
{
	const CrankVecFloat2*	vec = a;
	
	gdouble	dx;
	gdouble	dy;
	guint	hash;
	
	dx = vec->x;
	dy = vec->y;
	
	g_message ("Hashing (%lg, %lg)", dx, dy);
	g_message ("Hash value of each item: (%u, %u)", g_double_hash (&dx),  g_double_hash (&dy));
	
	hash =	g_double_hash (&dx) +
			g_double_hash (&dy) + 37;
	
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
gboolean		crank_vec_float2_equal (			gconstpointer	a,
												gconstpointer	b	)
{
	CrankVecFloat2*	veca = (CrankVecFloat2*)a;
	CrankVecFloat2*	vecb = (CrankVecFloat2*)b;
	
	return ((veca->x == vecb->x) &&
			(veca->y == vecb->y));
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
crank_vec_float2_to_string (	CrankVecFloat2*	vec	)
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
crank_vec_float2_to_string_full (	CrankVecFloat2*	vec,
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
 * crank_vec_float2_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
gfloat
crank_vec_float2_get_magn_sq	(	CrankVecFloat2*	vec	)
{
	return 	(vec->x * vec->x) +
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
crank_vec_float2_get_magn	(	CrankVecFloat2*	vec	)
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
crank_vec_float2_neg (	CrankVecFloat2*	a,
						CrankVecFloat2*	r	)
{
	r->x = - (a->x);
	r->y = - (a->y);
}


/**
 * crank_vec_float2_unit:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_float2_unit (	CrankVecFloat2*	a,
						CrankVecFloat2*	r	)
{
	crank_vec_float2_divs (a, crank_vec_float2_get_magn (a), r);
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
crank_vec_float2_muls	(	CrankVecFloat2*	a,
							const gfloat		b,
							CrankVecFloat2*	r	)
{
	r->x = a->x * b;
	r->y = a->y * b;
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
crank_vec_float2_divs	(	CrankVecFloat2*	a,
						const gfloat		b,
						CrankVecFloat2*	r	)
{
	r->x = a->x / b;
	r->y = a->y / b;
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
void			crank_vec_float2_add			(	CrankVecFloat2*	a,
													CrankVecFloat2*	b,
													CrankVecFloat2*	r	)
{
	r->x = a->x + b->x;
	r->y = a->y + b->y;
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
crank_vec_float2_sub	(	CrankVecFloat2*	a,
						CrankVecFloat2*	b,
						CrankVecFloat2*	r	)
{
	r->x = a->x - b->x;
	r->y = a->y - b->y;
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
crank_vec_float2_dot	(	CrankVecFloat2*	a,
						CrankVecFloat2*	b	)
{
	return (a->x) * (b->x) + (a->y) * (b->y);
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
crank_vec_float2_cmpmul	(	CrankVecFloat2*	a,
							CrankVecFloat2*	b,
							CrankVecFloat2*	r	)
{
	r->x = a->x * b->x;
	r->y = a->y * b->y;
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
crank_vec_float2_cmpdiv	(	CrankVecFloat2*	a,
							CrankVecFloat2*	b,
							CrankVecFloat2*	r	)
{
	r->x = a->x / b->x;
	r->y = a->y / b->y;
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
crank_vec_float2_cmpless	(	CrankVecFloat2*	a,
							CrankVecFloat2*	b,
							CrankVecBool2*	r	)
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
crank_vec_float2_cmpeq	(	CrankVecFloat2*	a,
							CrankVecFloat2*	b,
							CrankVecBool2*	r	)
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
crank_vec_float2_cmpgreater	(	CrankVecFloat2*	a,
								CrankVecFloat2*	b,
								CrankVecBool2*	r	)
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
crank_vec_float2_cmpcmp	(		CrankVecFloat2*	a,
								CrankVecFloat2*	b,
								CrankVecInt2*	r	)
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
crank_vec_float2_min (	CrankVecFloat2*	a,
						CrankVecFloat2*	b,
						CrankVecFloat2*	r	)
{
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
crank_vec_float2_max (	CrankVecFloat2*	a,
						CrankVecFloat2*	b,
						CrankVecFloat2*	r	)
{
	r->x = MAX (a->x, b->x);
	r->y = MAX (a->y, b->y);
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
crank_vec_float2_mixs (	CrankVecFloat2*	a,
						CrankVecFloat2*	b,
						const gfloat	c,
						CrankVecFloat2*	r	)
{
	gfloat d = 1.0f - c;
	
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
crank_vec_float2_mix (	CrankVecFloat2*	a,
						CrankVecFloat2*	b,
						CrankVecFloat2*	c,
						CrankVecFloat2*	r	)
{
	CrankVecFloat2 d = {1.0f - c->x, 1.0f - c->y};
	
	r->x = a->x * d.x + b->x * c->x;
	r->y = a->y * d.y + b->y * c->y;
}
