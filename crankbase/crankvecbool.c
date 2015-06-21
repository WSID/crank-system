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

/**
 * SECTION: crankvecbool
 * @title: Boolean vector
 * @short_description: Vectors that have boolean elements.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Represents vectors that have boolean elements.
 *
 * In mathematics, %TRUE and %FALSE cannot be composed as elements of vector,
 * as they cannot form a field. Anyway because of characteristic of #gboolean,
 * 'Boolean vectors' have differences from float vectors.
 *
 * * Boolean vectors have logical operations while float ones have airthmetic operations
 * * Boolean vectors have any, all property while float ones have magnitude/norm.
 *
 * * Componentwise Operations
 *    * and, or, xor, not
 * * Property
 *    * all, any
 *
 * Provided macros are following
 *
 * * TRUE, FALSE: Initialization list that all elements are %TRUE or %FALSE.
 * * I, J, K, L: Initialization list that one of element is %TRUE.
 *
 * Compared to bvec in GLSL.
 */

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankvecbool.h"

G_DEFINE_BOXED_TYPE (CrankVecBool2, crank_vec_bool2, crank_vec_bool2_copy, g_free)


/**
 * crank_vec_bool2_init:
 * @vec: (out): Vector to initialize.
 * @x: First vector element.
 * @y: Second vector element.
 *
 * Initialize elements from arguments.
 */
void
crank_vec_bool2_init	(	CrankVecBool2*	vec,
							gboolean		x,
							gboolean		y	)
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
crank_vec_bool2_init_arr	(	CrankVecBool2*	vec,
								gboolean*		arr	)
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
crank_vec_bool2_init_valist	(	CrankVecBool2*	vec,
								va_list			varargs	)
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
crank_vec_bool2_init_fill	(	CrankVecBool2*	vec,
								const gboolean	fill	)
{
	vec->x = fill;
	vec->y = fill;
}


/**
 * crank_vec_bool2_copy:
 * @vec: Vector to copy
 *
 * Copies a vector. Free with g_free () after use.
 *
 * Returns: (transfer full):  Copied vector. Free with g_free().
 */
CrankVecBool2*
crank_vec_bool2_copy	(	CrankVecBool2*	vec	)
{
	return (CrankVecBool2*) g_memdup (vec, sizeof (CrankVecBool2));
}


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
crank_vec_bool2_get	(	CrankVecBool2*	vec,
						const guint		index	)
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
crank_vec_bool2_set	(	CrankVecBool2*	vec,
						const guint		index,
						const gboolean	value	)
{
	((gboolean*)vec)[index] = value;
}

/**
 * crank_vec_bool2_and:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component AND of @a and @b.
 */
void
crank_vec_bool2_and	(	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	r->x = a->x && b->x;
	r->y = a->y && b->y;
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
crank_vec_bool2_or	(	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	r->x = a->x || b->x;
	r->y = a->y || b->y;
}

/**
 * crank_vec_bool2_xor:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component of exclusive or of @a and @b.
 */
void
crank_vec_bool2_xor	(	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	r->x = a->x != b->x;
	r->y = a->y != b->y;
}


/**
 * crank_vec_bool2_not:
 * @a: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component NOT of @a.
 */
void
crank_vec_bool2_not	(	CrankVecBool2*	a,
						CrankVecBool2*	r	)
{
	r->x = ! a->x;
	r->y = ! a->y;
}

/**
 * crank_vec_bool2_andv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool2_and(). Some language may use "and" as
 * keyword or operator.
 */
void
crank_vec_bool2_andv (	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
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
 * keyword or operator.
 */
void
crank_vec_bool2_orv (	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	crank_vec_bool2_or (a, b, r);
}

/**
 * crank_vec_bool2_notv:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool2_not(). Some language may use "not" as
 * keyword or operator.
 */
void
crank_vec_bool2_notv (	CrankVecBool2*	a,
						CrankVecBool2*	r	)
{
	crank_vec_bool2_not (a, r);
}

/**
 * crank_vec_bool2_get_any:
 * @vec: A vector.
 * 
 * Checks there is any element be %TRUE.
 *
 * Returns: Whether there is any element be %TRUE.
 */
gboolean
crank_vec_bool2_get_any	(	CrankVecBool2*	vec	)
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
crank_vec_bool2_get_all	(	CrankVecBool2*	vec	)
{
	return (vec->x && vec->y);
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
crank_vec_bool2_equal	(	gconstpointer a,
							gconstpointer b	)
{
	const CrankVecBool2* veca = (const CrankVecBool2*) a;
	const CrankVecBool2* vecb = (const CrankVecBool2*) b;

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
crank_vec_bool2_hash	(	gconstpointer a	)
{
	const CrankVecBool2* vec = (const CrankVecBool2*) a;
	
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
crank_vec_bool2_to_string	(	CrankVecBool2*	vec	)
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
crank_vec_bool2_to_string_full (CrankVecBool2*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	on_true,
								const gchar*	on_false	)
{
	return g_strdup_printf ("%s%s%s%s%s",
			left,
			vec->x ? on_true : on_false,
			in,
			vec->y ? on_true : on_false,
			right	);
}





G_DEFINE_BOXED_TYPE (CrankVecBool3, crank_vec_bool3, crank_vec_bool3_copy, g_free)

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
crank_vec_bool3_init	(	CrankVecBool3*	vec,
							gboolean		x,
							gboolean		y,
							gboolean		z	)
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
crank_vec_bool3_init_arr	(	CrankVecBool3*	vec,
								gboolean*		arr	)
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
crank_vec_bool3_init_valist	(	CrankVecBool3*	vec,
								va_list			varargs	)
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
crank_vec_bool3_init_fill	(	CrankVecBool3*	vec,
								const gboolean	fill	)
{
	vec->x = fill;
	vec->y = fill;
	vec->z = fill;
}


/**
 * crank_vec_bool3_copy:
 * @vec: Vector to copy
 *
 * Copies a vector. Free with g_free () after use.
 *
 * Returns: (transfer full):  Copied vector. Free with g_free().
 */
CrankVecBool3*
crank_vec_bool3_copy	(	CrankVecBool3*	vec	)
{
	return (CrankVecBool3*) g_memdup (vec, sizeof (CrankVecBool3));
}

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
crank_vec_bool3_get	(	CrankVecBool3*	vec,
						const guint		index	)
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
crank_vec_bool3_set	(	CrankVecBool3*	vec,
						const guint		index,
						const gboolean	value	)
{
	((gboolean*)vec)[index] = value;
}

/**
 * crank_vec_bool3_and:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component AND of @a and @b.
 */
void
crank_vec_bool3_and	(	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	r->x = a->x && b->x;
	r->y = a->y && b->y;
	r->z = a->z && b->z;
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
crank_vec_bool3_or	(	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	r->x = a->x || b->x;
	r->y = a->y || b->y;
	r->z = a->z || b->z;
}

/**
 * crank_vec_bool3_xor:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component of exclusive OR of @a and @b.
 */
void
crank_vec_bool3_xor	(	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	r->x = a->x != b->x;
	r->y = a->y != b->y;
	r->z = a->z != b->z;
}

/**
 * crank_vec_bool3_not:
 * @a: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component NOT of @a.
 */
void
crank_vec_bool3_not	(	CrankVecBool3*	a,
						CrankVecBool3*	r	)
{
	r->x = ! a->x;
	r->y = ! a->y;
}

/**
 * crank_vec_bool3_andv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool3_and(). Some language may use "and" as
 * keyword or operator.
 */
void
crank_vec_bool3_andv (	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
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
 * keyword or operator.
 */
void
crank_vec_bool3_orv (	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	crank_vec_bool3_or (a, b, r);
}

/**
 * crank_vec_bool3_notv:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool3_not(). Some language may use "not" as
 * keyword or operator.
 */
void
crank_vec_bool3_notv (	CrankVecBool3*	a,
						CrankVecBool3*	r	)
{
	crank_vec_bool3_not (a, r);
}


/**
 * crank_vec_bool3_get_any:
 * @vec: A vector.
 * 
 * Checks there is any element be %TRUE.
 *
 * Returns: Whether there is any element be %TRUE.
 */
gboolean
crank_vec_bool3_get_any	(	CrankVecBool3*	vec	)
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
crank_vec_bool3_get_all	(	CrankVecBool3*	vec	)
{
	return (vec->x && vec->y && vec->z);
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
crank_vec_bool3_equal	(	gconstpointer a,
							gconstpointer b	)
{
	const CrankVecBool3* veca = (const CrankVecBool3*) a;
	const CrankVecBool3* vecb = (const CrankVecBool3*) b;
	return	(veca->x == vecb->x) &&
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
crank_vec_bool3_hash	(	gconstpointer	a	)
{
	const CrankVecBool3* vec = (const CrankVecBool3*) a;
	return g_direct_hash (
			GINT_TO_POINTER(	(vec->x) +
								(vec->y << 1) +
								(vec->z << 2)	));
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
crank_vec_bool3_to_string	(	CrankVecBool3*	vec	)
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
crank_vec_bool3_to_string_full (CrankVecBool3*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	on_true,
								const gchar*	on_false	)
{
	return g_strdup_printf ("%s%s%s%s%s%s%s",
			left,
			vec->x ? on_true : on_false,
			in,
			vec->y ? on_true : on_false,
			in,
			vec->z ? on_true : on_false,
			right	);
}






G_DEFINE_BOXED_TYPE (CrankVecBool4, crank_vec_bool4, crank_vec_bool4_copy, g_free)

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
crank_vec_bool4_init	(	CrankVecBool4*	vec,
							gboolean		x,
							gboolean		y,
							gboolean		z,
							gboolean		w	)
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
crank_vec_bool4_init_arr	(	CrankVecBool4*	vec,
								gboolean*		arr	)
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
crank_vec_bool4_init_valist	(	CrankVecBool4*	vec,
								va_list			varargs	)
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
crank_vec_bool4_init_fill	(	CrankVecBool4*	vec,
								const gboolean	fill	)
{
	vec->x = fill;
	vec->y = fill;
	vec->z = fill;
	vec->w = fill;
}

/**
 * crank_vec_bool4_copy:
 * @vec: Vector to copy
 *
 * Copies a vector. Free with g_free () after use.
 *
 * Returns: (transfer full): Copied vector. Free with g_free().
 */
CrankVecBool4*
crank_vec_bool4_copy	(	CrankVecBool4*	vec	)
{
	return (CrankVecBool4*) g_memdup (vec, sizeof (CrankVecBool4));
}

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
crank_vec_bool4_get	(	CrankVecBool4*	vec,
						const guint		index	)
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
crank_vec_bool4_set	(	CrankVecBool4*	vec,
						const guint		index,
						const gboolean	value	)
{
	((gboolean*)vec)[index] = value;
}

/**
 * crank_vec_bool4_and:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component AND of @a and @b.
 */
void
crank_vec_bool4_and	(	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	r->x = a->x && b->x;
	r->y = a->y && b->y;
	r->z = a->z && b->z;
	r->w = a->w && b->w;
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
crank_vec_bool4_or	(	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	r->x = a->x || b->x;
	r->y = a->y || b->y;
	r->z = a->z || b->z;
	r->w = a->w || b->w;
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
crank_vec_bool4_xor	(	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	r->x = a->x != b->x;
	r->y = a->y != b->y;
	r->z = a->z != b->z;
	r->w = a->w != b->w;
}

/**
 * crank_vec_bool4_not:
 * @a: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component NOT of @a and @b.
 */
void
crank_vec_bool4_not	(	CrankVecBool4*	a,
						CrankVecBool4*	r	)
{
	r->x = ! a->x;
	r->y = ! a->y;
	r->z = ! a->z;
	r->w = ! a->w;
}
/**
 * crank_vec_bool4_andv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool4_and(). Some language may use "and" as
 * keyword or operator.
 */
void
crank_vec_bool4_andv (	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
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
 * keyword or operator.
 */
void
crank_vec_bool4_orv (	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	crank_vec_bool4_or (a, b, r);
}

/**
 * crank_vec_bool4_notv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool4_not(). Some language may use "not" as
 * keyword or operator.
 */
void
crank_vec_bool4_notv (	CrankVecBool4*	a,
						CrankVecBool4*	r	)
{
	crank_vec_bool4_not (a, r);
}


/**
 * crank_vec_bool4_get_any:
 * @vec: A vector.
 * 
 * Checks there is any element be %TRUE.
 *
 * Returns: Whether there is any element be %TRUE.
 */
gboolean
crank_vec_bool4_get_any	(	CrankVecBool4*	vec	)
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
crank_vec_bool4_get_all	(	CrankVecBool4*	vec	)
{
	return (vec->x && vec->y && vec->z && vec->w);
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
crank_vec_bool4_equal	(	gconstpointer	a,
							gconstpointer	b	)
{
	const CrankVecBool4* veca = (const CrankVecBool4*) a;
	const CrankVecBool4* vecb = (const CrankVecBool4*) b;
	return	(veca->x == vecb->x) &&
			(veca->y == vecb->y) &&
			(veca->z == vecb->z) &&
			(veca->w == vecb->w);
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
crank_vec_bool4_hash	(	gconstpointer a	)
{
	const CrankVecBool4* vec = (const CrankVecBool4*) a;
	return g_direct_hash (
			GINT_TO_POINTER(	(vec->x) +
								(vec->y << 1) +
								(vec->z << 2) +
								(vec->w << 3)	));
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
crank_vec_bool4_to_string	(	CrankVecBool4*	vec	)
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
crank_vec_bool4_to_string_full (CrankVecBool4*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	on_true,
								const gchar*	on_false	)
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
			right	);
}





G_DEFINE_BOXED_TYPE (CrankVecBoolN, crank_vec_bool_n,
		crank_vec_bool_n_copy,
		crank_vec_bool_n_free)

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
crank_vec_bool_n_init	(	CrankVecBoolN*	vec,
							const guint		n,
							...	)
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
crank_vec_bool_n_init_arr	(	CrankVecBoolN*	vec,
								const guint		n,
								gboolean*		arr	)
{
	if (vec->data != NULL) g_free (vec->data);
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
crank_vec_bool_n_init_valist	(	CrankVecBoolN*	vec,
									const guint		n,
									va_list			varargs	)
{
	guint	i;
	
	if (vec->data != NULL) g_free (vec->data);
	vec->n = n;
	vec->data = g_new (gboolean, n);
	
	for (i = 0; i < n; i++) vec->data[i] = va_arg (varargs, gboolean);
	
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
crank_vec_bool_n_init_fill	(	CrankVecBoolN*	vec,
								const guint		n,
								const gboolean	fill	)
{
	guint	i;
	
	if (vec->data != NULL) g_free (vec->data);
	vec->n = n;
	vec->data = g_new (gboolean, n);
	
	for (i = 0; i < n; i++) vec->data[i] = fill;
	
}


/**
 * crank_vec_bool_n_fini:
 * @vec: A vector to unset.
 *
 * Frees associated resources and unset @vec.
 */
void
crank_vec_bool_n_fini	(	CrankVecBoolN*	vec	)
{
	g_free (vec->data);
	vec->n = 0;
}

/**
 * crank_vec_bool_n_free:
 * @vec: A vector to free.
 *
 * Frees associated resources and frees @vec.
 */
void
crank_vec_bool_n_free	(	CrankVecBoolN*	vec	)
{
	crank_vec_bool_n_fini (vec);
	g_free (vec);
}


/**
 * crank_vec_bool_n_copy:
 * @vec: Vector to copy
 *
 * Copies a vector. Free with crank_vec_bool_n_free() after use.
 *
 * Returns: (transfer full): Copied vector. Free with g_free().
 */
CrankVecBoolN*
crank_vec_bool_n_copy	(	CrankVecBoolN*	vec	)
{
	CrankVecBoolN* result = g_new0 (CrankVecBoolN, 1);
	
	crank_vec_bool_n_init_arr (result, vec->n, vec->data);
	return result;
}

/**
 * crank_vec_bool_n_get_size:
 * @vec: Vector to get size.
 *
 * Gets size of vector. This can be obtained from @vec->n.
 *
 * Returns: Size of vector.
 */
guint
crank_vec_bool_n_get_size	(	CrankVecBoolN*	vec	)
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
crank_vec_bool_n_get	(	CrankVecBoolN*	vec,
							const guint		index	)
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
crank_vec_bool_n_set	(	CrankVecBoolN*	vec,
							const guint		index,
							const gboolean	value	)
{
	vec->data[index] = value;
}

/**
 * crank_vec_bool_n_and:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component AND of @a and @b.
 */
void
crank_vec_bool_n_and	(	CrankVecBoolN*	a,
							CrankVecBoolN*	b,
							CrankVecBoolN*	r	)
{
	guint i;
	
	if (r->data != NULL) g_free (r->data);
	
	r->n = MIN(a->n, b->n);
	r->data = g_new (gboolean, r->n);
	
	for (i = 0; i < r->n; i++)
		r->data[i] = (a->data[i]) && (b->data[i]);
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
crank_vec_bool_n_or	(	CrankVecBoolN*	a,
						CrankVecBoolN*	b,
						CrankVecBoolN*	r	)
{
	CrankVecBoolN* l;
	CrankVecBoolN* s;
	
	guint i;
	
	if (r->data != NULL) g_free (r->data);
	
	if (a->n < b->n) {
		l = b;
		s = a;
	}
	else {
		l = a;
		s = b;
	}
	
	r->n =		l->n;
	r->data = 	g_new (gboolean, r->n);
	
	for (i = 0; i < s->n; i++)
		r->data[i] = a->data[i] || b->data[i] ;
	
	memcpy (	(r->data + s->n),
				(l->data + s->n),
				sizeof(gboolean) *(l->n - s->n)	);
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
crank_vec_bool_n_xor	(	CrankVecBoolN*	a,
							CrankVecBoolN*	b,
							CrankVecBoolN*	r	)
{
	CrankVecBoolN* l;
	CrankVecBoolN* s;
	
	guint i;
	
	if (r->data != NULL) g_free (r->data);
	
	if (a->n < b->n) {
		l = b;
		s = a;
	}
	else {
		l = a;
		s = b;
	}
	
	r->n =		l->n;
	r->data = 	g_new (gboolean, r->n);
	
	for (i = 0; i < s->n; i++) r->data[i] = a->data[i] != b->data[i] ;
	
	memcpy (	(r->data + s->n),
				(l->data + s->n),
				sizeof(gboolean) *(l->n - s->n)	);
}


/**
 * crank_vec_bool_n_not:
 * @a: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets Component NOT of @a and @b.
 */
void
crank_vec_bool_n_not	(	CrankVecBoolN*	a,
							CrankVecBoolN*	r	)
{
	guint i;
	
	if (r->data != NULL) g_free (r->data);

	r->n = a->n;
	r->data = g_new (gboolean, r->n);
	
	for (i = 0; i < r->n; i++) r->data[i] = !(a->data[i]);
}

/**
 * crank_vec_bool_n_andv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool_n_and(). Some language may use "and" as
 * keyword or operator.
 */
void
crank_vec_bool_n_andv (	CrankVecBoolN*	a,
						CrankVecBoolN*	b,
						CrankVecBoolN*	r	)
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
 * keyword or operator.
 */
void
crank_vec_bool_n_orv (	CrankVecBoolN*	a,
						CrankVecBoolN*	b,
						CrankVecBoolN*	r	)
{
	crank_vec_bool_n_or (a, b, r);
}

/**
 * crank_vec_bool_n_notv:
 * @a: A vector.
 * @r: (out): A vector to store result.
 *
 * Another name for crank_vec_bool_n_not(). Some language may use "not" as
 * keyword or operator.
 */
void
crank_vec_bool_n_notv (	CrankVecBoolN*	a,
						CrankVecBoolN*	r	)
{
	crank_vec_bool_n_not (a, r);
}

/**
 * crank_vec_bool_n_get_any:
 * @vec: A vector.
 * 
 * Checks there is any element be %TRUE.
 *
 * Returns: Whether there is any element be %TRUE.
 */
gboolean
crank_vec_bool_n_get_any	(	CrankVecBoolN*	vec	)
{
	CRANK_FOREACH_ARRAY_BEGIN (vec->data, gboolean, e, vec->n)
		if (e) return TRUE;
	CRANK_FOREACH_ARRAY_END
	
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
crank_vec_bool_n_get_all	(	CrankVecBoolN*	vec	)
{
	CRANK_FOREACH_ARRAY_BEGIN (vec->data, gboolean, e, vec->n)
		if (! e) return FALSE;
	CRANK_FOREACH_ARRAY_END
	
	return TRUE;
}

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
crank_vec_bool_n_equal	(	gconstpointer a,
							gconstpointer b	)
{
	const CrankVecBoolN*	veca = (const CrankVecBoolN*) a;
	const CrankVecBoolN*	vecb = (const CrankVecBoolN*) b;
	
	guint i;
	if (veca->n != vecb->n) return FALSE;
	
	for (i = 0; i < veca->n; i++)
		if (veca->data[i] != vecb->data[i]) return FALSE;
	
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
crank_vec_bool_n_hash	(	gconstpointer a	)
{
	const CrankVecBoolN* vec  = (const CrankVecBoolN*) a;
	
	guint	i;
	guint	value = 0;
	
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
crank_vec_bool_n_to_string	(	CrankVecBoolN*	vec	)
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
crank_vec_bool_n_to_string_full (CrankVecBoolN*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	on_true,
								const gchar*	on_false	)
{
	GString*	str;
	gchar*		result;
	
	str = g_string_new (left);
	
	if (0 < vec->n) {
		g_string_append (str, vec->data[0] ? on_true : on_false );
		
		CRANK_FOREACH_ARRAY_BEGIN (vec->data, gboolean, e, vec->n)
			g_string_append (str, in );
			g_string_append (str, e ? on_true : on_false );
		CRANK_FOREACH_ARRAY_END
	}
	
	g_string_append (str, right);
	
	result = str->str;
	g_string_free (str, FALSE);
	
	return result;
}

