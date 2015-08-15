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

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankrange.h"

/**
 * SECTION: crankrange
 * @title: Range of primitives.
 * @short_description: Structures represent ranges.
 * @usability: unstable
 * @include: crankbase.h
 *
 * Crank System provides simple range representations for convenience.
 *
 * Ranges can be used for requirements of values, specifying memory block, and
 * basic of shape processing.
 *
 * <table frame="all"><title>Supported Operations</title>
 *   <tgroup cols="2" align="left" colsep="1" rowsep="1">
 *     <colspec colname="op" />
 *     <thead>
 *       <row>
 *         <entry>Operations</entry>
 *         <entry>Detailed</entry>
 *       </row>
 *     </thead>
 *     <tbody>
 *       <row>
 *         <entry>Initialization</entry>
 *         <entry>basic, lengthened, unit</entry>
 *       </row>
 *       <row>
 *         <entry>Attributes</entry>
 *         <entry>length</entry>
 *       </row>
 *       <row>
 *         <entry>Value Operations</entry>
 *         <entry>Contains, get, index of, clamp</entry>
 *       </row>
 *       <row>
 *         <entry>Raneg Operations</entry>
 *         <entry>Intersection</entry>
 *       </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 
 * # Get and Index of
 *
 * Getting operations on range can be thought as mix operation of start and end
 * point.
 *
 * Index of operations on range can be thought as inverse operations of get
 * operations.
 *
 * # Differece of contains and clamp in meaning of range.
 *
 * The range represents a range with one open end, which is in form of [a, b).
 * As a result, contains function will return %FALSE on end point.
 *
 * But, for clamp, it would not work as we cannot determine valid value when
 * value is out of range at end side. so for clamp operation, it will work as if
 * range was [a, b], instead of [a, b).
 *
 * This will make some wicked point that a clamped value might still out of
 * range.
 *
 * # Pointer Range
 *
 * Pointer ranges are generally used for memory block. So this has more
 * operations, specialized for pointers. Note that they all also requires
 * size of chunk/steps.
 * <itemizedlist>
 *   <listitem>count: number of chunk in range.</listitem>
 *   <listitem>get_step: get value after steps with given size (which probably
 *              size of element type)</listitem>
 *   <listitem>n_step: get index of step with given size.</listitem>
 * </itemizedlist>
 */

G_DEFINE_BOXED_TYPE(CrankRanUint, crank_ran_uint, crank_ran_uint_dup, g_free)
G_DEFINE_BOXED_TYPE(CrankRanInt, crank_ran_int, crank_ran_int_dup, g_free)
G_DEFINE_BOXED_TYPE(CrankRanFloat, crank_ran_float, crank_ran_float_dup, g_free)
G_DEFINE_BOXED_TYPE(CrankRanPtr, crank_ran_ptr, crank_ran_ptr_dup, g_free)

//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_ran_uint_init:
 * @ran: (out): A Range
 * @start: Start of range.
 * @end: End of range.
 *
 * Initialize a range with given two points.
 */
void
crank_ran_uint_init (	CrankRanUint*	ran,
						const guint		start,
						const guint		end		)
{
	ran->start = start;
	ran->end = end;
}


/**
 * crank_ran_uint_init_diff:
 * @ran: (out): A Range
 * @start: Start of range.
 * @diff: Difference of start and end.
 *
 * Initialize a range with start point and difference.
 */
void
crank_ran_uint_init_diff (	CrankRanUint*	ran,
							const guint		start,
							const guint		diff	)
{
	crank_ran_uint_init (ran, start, start + diff);
}


/**
 * crank_ran_uint_init_unit:
 * @ran: (out): A Range
 * @start: Start of range.
 *
 * Initialize a range with start point, with unit length.
 *
 * For numeric values, it is 1.
 */
void
crank_ran_uint_init_unit (	CrankRanUint*	ran,
							const guint		start	)
{
	crank_ran_uint_init_diff (ran, start, 1);
}


//////// Basic Functions ///////////////////////////////////////////////////////


/**
 * crank_ran_uint_copy:
 * @ran: A Range
 * @other: (out): Copied range.
 *
 * Copies a range to other
 */
void
crank_ran_uint_copy (	CrankRanUint*	ran,
						CrankRanUint*	other	)
{
	crank_ran_uint_init (other, ran->start, ran->end	);
}


/**
 * crank_ran_uint_dup:
 * @ran: A Range
 *
 * Allocates new range and copies on it.
 *
 * Returns: (transfer full): Copied range, free with g_free()
 */
CrankRanUint*
crank_ran_uint_dup (	CrankRanUint*	ran	)
{
	CrankRanUint*	result = g_new (CrankRanUint, 1);
	crank_ran_uint_copy (ran, result);
}


/**
 * crank_ran_uint_equal:
 * @a: (type CrankRanUint): A Range
 * @b: (type CrankRanUint): A Range
 *
 * Compares two range and checks they are same.
 *
 * Returns: Whether the two are same.
 */
gboolean
crank_ran_uint_equal (	gconstpointer	a,
						gconstpointer	b	)
{
	CrankRanUint*	aran = (CrankRanUint*)	a;
	CrankRanUint*	bran = (CrankRanUint*)	b;
	
	return ((aran->start == bran->start) && (aran->end == bran->end));
}


/**
 * crank_ran_uint_hash:
 * @a: (type CrankRanUint): A Range
 *
 * Gets hash value of range.
 *
 * Returns: Hash value of range.
 */
guint
crank_ran_uint_hash (	gconstpointer	a	)
{
	CrankRanUint*	ran = (CrankRanUint*) a;
	
	return	g_int_hash (& (ran->start)) * 33 +
			g_int_hash (& (ran->end));
}


/**
 * crank_ran_uint_to_string:
 * @ran: A Range
 *
 * Gets string representation of range.
 *
 * Returns: (transfer full): String representation, free with g_free().
 */
gchar*
crank_ran_uint_to_string (	CrankRanUint*	ran	)
{
	return crank_ran_uint_to_string_full (ran, CRANK_RAN_UINT_DEFFORMAT);
}


/**
 * crank_ran_uint_to_string_full:
 * @ran: A Range
 * @format: Format string for range. Consumes two uint parameters.
 *
 * Gets string representation of range, with given format.
 *
 * Returns: (transfer full): String representation, free with g_free().
 */
gchar*
crank_ran_uint_to_string_full (	CrankRanUint*	ran,
								const gchar*	format	)
{
	return g_strdup_printf (format, ran->start, ran->end);
}

//////// Classification ////////////////////////////////////////////////////////

/**
 * crank_ran_uint_is_empty:
 * @ran: A Range
 *
 * Checks whether it is empty range, which has zero-length.
 *
 * Returns: whether it is empty range.
 */
gboolean
crank_ran_uint_is_empty (	CrankRanUint*	ran	)
{
	return (ran->start == ran->end);
}


/**
 * crank_ran_uint_is_unit:
 * @ran: A Range
 *
 * Checks whether it is unit range, which has unit length.
 *
 * Returns: whether it is unit range.
 */
gboolean
crank_ran_uint_is_unit (	CrankRanUint*	ran )
{
	return (crank_ran_uint_get_length (ran) == 1);
}

//////// Attributes ////////////////////////////////////////////////////////////

/**
 * crank_ran_uint_get_length:
 * @ran: A Range.
 *
 * Gets length of range.
 *
 * Returns: The length of range.
 */
guint
crank_ran_uint_get_length (	CrankRanUint*	ran	)
{
	return ran->end - ran->start;
}

//////// Range function ////////////////////////////////////////////////////////

/**
 * crank_ran_uint_contains:
 * @ran: A Range.
 * @value: A Value
 *
 * Checks whether the value is in the range.
 *
 * Returns: Whetehr the value is in the range.
 */
gboolean
crank_ran_uint_contains (	CrankRanUint*	ran,
							const guint		value	)
{
	return ((ran->start) <= value) && (value < (ran->end));
}

/**
 * crank_ran_uint_get:
 * @ran: A Range.
 * @index: A Index.
 *
 * Gets interpolated value between start and end point.
 *
 * If @index is out of range of [0, 1], the appropriate value is returned, which
 * also out of range [@ran->start, @ran->end].
 *
 * Returns: A interpolated value.
 */ 
guint
crank_ran_uint_get (	CrankRanUint*	ran,
						const gfloat	index	)
{
	guint	len = crank_ran_uint_get_length (ran);
	
	if (index < 0)	return ran->start - (guint)(-index * len);
	else			return ran->start + (guint)(index * len);
}

/**
 * crank_ran_uint_index_of:
 * @ran: A Range.
 * @value: A Value.
 *
 * Gets index from value, which index meets,
 *    * (@ran->start * (1 - index)) + (@ran->end * index) == @value.
 *
 * You can think this as inverse operation of crank_ran_uint_get().
 *
 * Returns: A index for given value.
 */
gfloat
crank_ran_uint_index_of (	CrankRanUint*	ran,
							const guint		value	)
{
	guint	len = crank_ran_uint_get_length (ran);
	
	if (value < ran->start)	return -(gfloat)(ran->start - value) / len;
	else					return (gfloat)(value - ran->start) / len;
}

/**
 * crank_ran_uint_clamp:
 * @ran: A Range.
 * @value: A Value.
 * 
 * Clamps a given value with in the range.
 *
 * Note
 *     crank_ran_uint_contains() checks for [start, end), while this function
 *     works for [start, end]. So the result does not guaranteed to be evaluated
 *     to be %TRUE in crank_ran_uint_contains().
 *
 * Returns: A Clamped value.
 */
guint
crank_ran_uint_clamp (	CrankRanUint*	ran,
						const guint		value	)
{
	return CLAMP (value, ran->start, ran->end);
}


//////// Range - Range operations //////////////////////////////////////////////

/**
 * crank_ran_uint_intersection:
 * @a: A Range.
 * @b: A Range
 * @r: (out): A Intersection of @a and @b, or empty range if there is no intersection.
 *
 * Gets intersection of two range.
 *
 * If there is no intersection, it returns %FALSE, and initialize @r with empty
 * range.
 *
 * Returns: whether if @a and @b has intersection.
 */
gboolean
crank_ran_uint_intersection (	CrankRanUint*	a,
								CrankRanUint*	b,
								CrankRanUint*	r	)
{
	if ((b->start) < (a->end) && (a->start) < (b->end)) {
		crank_ran_uint_init (	r,
			MAX(a->start, b->start),
			MIN(a->end, b->end)	);
		return TRUE;
	}
	else {
		r->start = 0;
		r->end = 0;
		return FALSE;
	}
}




//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_ran_int_init:
 * @ran: (out): A Range
 * @start: Start of range.
 * @end: End of range.
 *
 * Initialize a range with given two points.
 */
void
crank_ran_int_init (	CrankRanInt*	ran,
						const gint		start,
						const gint		end		)
{
	ran->start = start;
	ran->end = end;
}

/**
 * crank_ran_int_init_diff:
 * @ran: (out): A Range
 * @start: Start of range.
 * @diff: Difference of start and end.
 *
 * Initialize a range with start point and difference.
 */
void
crank_ran_int_init_diff (	CrankRanInt*	ran,
							const gint		start,
							const guint		diff	)
{
	crank_ran_int_init (ran, start, start + diff);
}

/**
 * crank_ran_int_init_unit:
 * @ran: (out): A Range
 * @start: Start of range.
 *
 * Initialize a range with start point, with unit length.
 *
 * For numeric values, it is 1.
 */
void
crank_ran_int_init_unit (	CrankRanInt*	ran,
							const gint		start 	)
{
	crank_ran_int_init_diff (ran, start, 1);
}



//////// Basic Functions ///////////////////////////////////////////////////////

/**
 * crank_ran_int_copy:
 * @ran: A Range
 * @other: (out): Copied range.
 *
 * Copies a range to other
 */
void
crank_ran_int_copy (	CrankRanInt*	ran,
						CrankRanInt*	other	)
{
	crank_ran_int_init (other, ran->start, ran->end);
}

/**
 * crank_ran_int_dup:
 * @ran: A Range
 *
 * Allocates new range and copies on it.
 *
 * Returns: (transfer full): Copied range, free with g_free()
 */
CrankRanInt*
crank_ran_int_dup (	CrankRanInt*	ran	)
{
	CrankRanInt*	result = g_new (CrankRanInt, 1);
	crank_ran_int_copy (ran, result);
	return result;
}

/**
 * crank_ran_int_equal:
 * @a: (type CrankRanInt): A Range
 * @b: (type CrankRanInt): A Range
 *
 * Compares two range and checks they are same.
 *
 * Returns: Whether the two are same.
 */
gboolean
crank_ran_int_equal (	gconstpointer	a,
						gconstpointer	b	)
{
	CrankRanInt*	rana = (CrankRanInt*)a;
	CrankRanInt*	ranb = (CrankRanInt*)b;
	return (rana->start == ranb->start) && (rana->end == ranb->end);
}

/**
 * crank_ran_int_hash:
 * @a: (type CrankRanInt): A Range
 *
 * Gets hash value of range.
 *
 * Returns: Hash value of range.
 */
guint
crank_ran_int_hash (	gconstpointer	a	)
{
	CrankRanInt*	ran = (CrankRanInt*)a;
	
	return	g_int_hash (& ran->start) * 33 +
			g_int_hash (& ran->end);
}

/**
 * crank_ran_int_to_string:
 * @ran: A Range
 *
 * Gets string representation of range.
 *
 * Returns: (transfer full): String representation, free with g_free().
 */
gchar*
crank_ran_int_to_string (	CrankRanInt*	ran	)
{
	return crank_ran_int_to_string_full (ran,
			CRANK_RAN_INT_DEFFORMAT);
}

/**
 * crank_ran_int_to_string_full:
 * @ran: A Range
 * @format: Format string for range. Consumes two int parameters.
 *
 * Gets string representation of range, with given format.
 *
 * Returns: (transfer full): String representation, free with g_free().
 */
gchar*		crank_ran_int_to_string_full (	CrankRanInt*	ran,
											const gchar*	format	)
{
	return g_strdup_printf (format, ran->start, ran->end);
}

								
//////// Classification ////////////////////////////////////////////////////////

/**
 * crank_ran_int_is_empty:
 * @ran: A Range
 *
 * Checks whether it is empty range, which has zero-length.
 *
 * Returns: whether it is empty range.
 */
gboolean
crank_ran_int_is_empty (	CrankRanInt*	ran		)
{
	return (ran->start == ran->end);
}


/**
 * crank_ran_int_is_unit:
 * @ran: A Range
 *
 * Checks whether it is unit range, which has unit length.
 *
 * Returns: whether it is unit range.
 */
gboolean
crank_ran_int_is_unit (	CrankRanInt*	ran		)
{
	return crank_ran_int_get_length (ran) == 1;
}

//////// Attributes ////////////////////////////////////////////////////////////

/**
 * crank_ran_int_get_length:
 * @ran: A Range.
 *
 * Gets length of range.
 *
 * Returns: The length of range.
 */
guint
crank_ran_int_get_length (	CrankRanInt*	ran	)
{
	return (guint)(ran->end - ran->start);
}


//////// Range function ////////////////////////////////////////////////////////

/**
 * crank_ran_int_contains:
 * @ran: A Range.
 * @value: A Value
 *
 * Checks whether the value is in the range.
 *
 * Returns: Whether the value is in the range.
 */
gboolean
crank_ran_int_contains (	CrankRanInt*	ran,
							const gint		value	)
{
	return (ran->start < value) && (value < ran->end);
}


/**
 * crank_ran_int_get:
 * @ran: A Range.
 * @index: A Index.
 *
 * Gets interpolated value between start and end point.
 *
 * If @index is out of range of [0, 1], the appropriate value is returned, which
 * also out of range [@ran->start, @ran->end].
 *
 * Returns: A interpolated value.
 */ 
gint
crank_ran_int_get (	CrankRanInt*	ran,
					const gfloat	index	)
{
	guint	len = crank_ran_int_get_length (ran);
	
	if (index < 0)	return ran->start - (gint)(-index * len);
	else			return ran->start + (gint)(index * len);
}


/**
 * crank_ran_int_index_of:
 * @ran: A Range.
 * @value: A Value.
 *
 * Gets index from value, which index meets,
 *    * (@ran->start * (1 - index)) + (@ran->end * index) == @value.
 *
 * You can think this as inverse operation of crank_ran_int_get().
 *
 * Returns: A index for given value.
 */
gfloat
crank_ran_int_index_of (	CrankRanInt*	ran,
							const gint		value	)
{
	guint	len = crank_ran_int_get_length (ran);
	
	if (value < ran->start)	return -(gfloat)(ran->start - value) / len;
	else					return (gfloat)(value - ran->start) / len;
}


/**
 * crank_ran_int_clamp:
 * @ran: A Range.
 * @value: A Value.
 * 
 * Clamps a given value with in the range.
 *
 * clamp function and contains function has different checking boundary. See
 * crank_ran_uint_clamp() for detailed notes.
 *
 * Returns: A Clamped value.
 */
gint
crank_ran_int_clamp (	CrankRanInt*	ran,
						const gint		value	)
{
	return CLAMP (value, ran->start, ran->end);
}


/**
 * crank_ran_int_intersection:
 * @a: A Range.
 * @b: A Range
 * @r: (out): A Intersection of @a and @b, or empty range if there is no intersection.
 *
 * Gets intersection of two range.
 *
 * If there is no intersection, it returns %FALSE, and initialize @r with empty
 * range.
 *
 * Returns: whether if @a and @b has intersection.
 */
gboolean
crank_ran_int_intersection (	CrankRanInt*	a,
								CrankRanInt*	b,
								CrankRanInt*	r	)
{
	if ((b->start) < (a->end) && (a->start) < (b->end)) {
		crank_ran_int_init (	r,
			MAX(a->start, b->start),
			MIN(a->end, b->end)	);
		return TRUE;
	}
	else {
		r->start = 0;
		r->end = 0;
		return FALSE;
	}
}






//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_ran_float_init:
 * @ran: (out): A Range
 * @start: Start of range.
 * @end: End of range.
 *
 * Initialize a range with given two points.
 */
void
crank_ran_float_init (	CrankRanFloat*	ran,
						const gfloat	start,
						const gfloat	end		)
{
	ran->start = start;
	ran->end = end;
}

/**
 * crank_ran_float_init_diff:
 * @ran: (out): A Range
 * @start: Start of range.
 * @diff: Difference of start and end.
 *
 * Initialize a range with start point and difference.
 */
void
crank_ran_float_init_diff (	CrankRanFloat*	ran,
							const gfloat	start,
							const gfloat	diff	)
{
	crank_ran_float_init (ran, start, start + diff);
}

/**
 * crank_ran_float_init_unit:
 * @ran: (out): A Range
 * @start: Start of range.
 *
 * Initialize a range with start point, with unit length.
 *
 * For numeric values, it is 1.
 */
void
crank_ran_float_init_unit (	CrankRanFloat*	ran,
							const gfloat	start 	)
{
	crank_ran_float_init_diff (ran, start, 1);
}


//////// Basic Functions ///////////////////////////////////////////////////////

/**
 * crank_ran_float_copy:
 * @ran: A Range
 * @other: (out): Copied range.
 *
 * Copies a range to other
 */
void
crank_ran_float_copy (	CrankRanFloat*	ran,
						CrankRanFloat*	other	)
{
	crank_ran_float_init (other, ran->start, ran->end);
}

/**
 * crank_ran_float_dup:
 * @ran: A Range
 *
 * Allocates new range and copies on it.
 *
 * Returns: (transfer full): Copied range, free with g_free()
 */
CrankRanFloat*
crank_ran_float_dup (	CrankRanFloat*	ran	)
{
	CrankRanFloat*	result = g_new (CrankRanFloat, 1);
	crank_ran_float_copy (ran, result);
	return result;
}

/**
 * crank_ran_float_equal:
 * @a: (type CrankRanFloat): A Range
 * @b: (type CrankRanFloat): A Range
 *
 * Compares two range and checks they are same.
 *
 * Returns: Whether the two are same.
 */
gboolean
crank_ran_float_equal (	gconstpointer	a,
						gconstpointer	b	)
{
	return crank_ran_float_equal_delta (a, b, 0.0001f);
}

/**
 * crank_ran_float_equal_delta:
 * @a: (type CrankRanFloat): A Range
 * @b: (type CrankRanFloat): A Range
 * @d: A Delta
 *
 * Compares two range and checks they are sufficiently same, which has difference
 * less than given delta.
 *
 * Returns: Whether the two are sufficiently same.
 */
gboolean
crank_ran_float_equal_delta (	gconstpointer	a,
								gconstpointer	b,
								const gfloat	d	)
{
	CrankRanFloat*	rana;
	CrankRanFloat*	ranb;
	
	gfloat			err;

	err = ABS(ranb->start - rana->start) + ABS(ranb->end - rana->end);

	return (err < d);
}


/**
 * crank_ran_float_hash:
 * @a: (type CrankRanFloat): A Range
 *
 * Gets hash value of range.
 *
 * Returns: Hash value of range.
 */
guint
crank_ran_float_hash (	gconstpointer	a	)
{
	CrankRanFloat*	ran;
	
	gdouble	start = ran->start;
	gdouble end = ran->end;
	
	return	g_double_hash (&start) * 33 +
			g_double_hash (&end);
}

/**
 * crank_ran_float_to_string:
 * @ran: A Range
 *
 * Gets string representation of range.
 *
 * Returns: (transfer full): String representation, free with g_free().
 */
gchar*
crank_ran_float_to_string (	CrankRanFloat*	ran	)
{
	crank_ran_float_to_string_full (ran,
			CRANK_RAN_FLOAT_DEFFORMAT	);
}

/**
 * crank_ran_float_to_string_full:
 * @ran: A Range
 * @format: Format string for range. Consumes two float parameters.
 *
 * Gets string representation of range, with given format.
 *
 * Returns: (transfer full): String representation, free with g_free().
 */
gchar*
crank_ran_float_to_string_full (	CrankRanFloat*	ran,
									const gchar*	format	)
{
	return g_strdup_printf (format, ran->start, ran->end);
}

											
//////// Classification ////////////////////////////////////////////////////////

/**
 * crank_ran_float_is_empty:
 * @ran: A Range
 *
 * Checks whether it is empty range, which has zero-length.
 *
 * Returns: whether it is empty range.
 */
gboolean
crank_ran_float_is_empty (	CrankRanFloat*	ran		)
{
	return (ran->start == ran->end);
}

/**
 * crank_ran_float_is_unit:
 * @ran: A Range
 *
 * Checks whether it is unit range, which has unit length.
 *
 * Returns: whether it is unit range.
 */
gboolean
crank_ran_float_is_unit (	CrankRanFloat*	ran		)
{
	return crank_ran_float_get_length (ran) == 1;
}

/**
 * crank_ran_float_is_nan:
 * @ran: A Range
 *
 * Checks whether it is undetermined range. If any one of end points is NaN, then
 * the whole range is considered NaN, as it cannot determine which numbers are
 * in the range.
 *
 * NaN ranges returns %FALSE for most boolean functions and NaN for most value
 * functions.
 *
 * Returns: whether it is NaN range.
 */
gboolean
crank_ran_float_is_nan (	CrankRanFloat*	ran		)
{
	return isnanf(ran->start) || isnanf(ran->end);
}

/**
 * crank_ran_float_has_inf:
 * @ran: A Range
 *
 * Checks whether any end point is infinity.
 *
 * Returns: whether it has infinity.
 */
gboolean
crank_ran_float_has_inf (	CrankRanFloat*	ran		)
{
	return	crank_ran_float_has_pinf (ran) ||
			crank_ran_float_has_ninf (ran);
}

/**
 * crank_ran_float_has_pinf:
 * @ran: A Range
 *
 * Checks whether end point is positive infinity.
 *
 * Returns: whether it has positive infinity.
 */
gboolean
crank_ran_float_has_pinf (	CrankRanFloat*	ran	)
{
	return	isinff (ran->end) && (0 < ran->end);
}

/**
 * crank_ran_float_has_ninf:
 * @ran: A Range
 *
 * Checks whether start point is negative infinity.
 *
 * Returns: whether it has negative infinity.
 */
gboolean
crank_ran_float_has_ninf (	CrankRanFloat*	ran		)
{
	return	isinff (ran->start) && (ran->start < 0);
}

//////// Attributes ////////////////////////////////////////////////////////////

/**
 * crank_ran_float_get_length:
 * @ran: A Range.
 *
 * Gets length of range.
 *
 * Returns: The length of range.
 */
gfloat
crank_ran_float_get_length (	CrankRanFloat*	ran	)
{
	return ran->end - ran->start;
}

//////// Range function ////////////////////////////////////////////////////////

/**
 * crank_ran_float_contains:
 * @ran: A Range.
 * @value: A Value
 *
 * Checks whether the value is in the range.
 *
 * Returns: Whether the value is in the range.
 */
gboolean
crank_ran_float_contains (	CrankRanFloat*	ran,
							const gfloat	value	)
{
	return	(ran->start <= value) && (value < ran->end);
}

/**
 * crank_ran_float_get:
 * @ran: A Range.
 * @index: A Index.
 *
 * Gets interpolated value between start and end point.
 *
 * If @index is out of range of [0, 1], the appropriate value is returned, which
 * also out of range [@ran->start, @ran->end].
 *
 * Returns: A interpolated value.
 */ 
gfloat
crank_ran_float_get (	CrankRanFloat*	ran,
						const gfloat	index	)
{
	return	fmaf (crank_ran_float_get_length (ran), index, ran->start);
}

/**
 * crank_ran_float_index_of:
 * @ran: A Range.
 * @value: A Value.
 *
 * Gets index from value, which index meets,
 *    * (@ran->start * (1 - index)) + (@ran->end * index) == @value.
 *
 * You can think this as inverse operation of crank_ran_int_get().
 *
 * Returns: A index for given value.
 */
gfloat
crank_ran_float_index_of (	CrankRanFloat*	ran,
							const gfloat	value	)
{
	gfloat	len = crank_ran_float_get_length (ran);
	gfloat	diff = value - ran->start;
	return diff / len;
}

/**
 * crank_ran_float_clamp:
 * @ran: A Range.
 * @value: A Value.
 * 
 * Clamps a given value with in the range.
 *
 * clamp function and contains function has different checking boundary. See
 * crank_ran_uint_clamp() for detailed notes.
 *
 * Returns: A Clamped value.
 */
gfloat
crank_ran_float_clamp (	CrankRanFloat*	ran,
						const gfloat	value	)
{
	return CLAMP(value, ran->start, ran->end);
}

/**
 * crank_ran_float_intersection:
 * @a: A Range.
 * @b: A Range
 * @r: (out): A Intersection of @a and @b, or empty range if there is no intersection.
 *
 * Gets intersection of two range.
 *
 * If there is no intersection, it returns %FALSE, and initialize @r with empty
 * range.
 *
 * Returns: whether if @a and @b has intersection.
 */
gboolean
crank_ran_float_intersection (	CrankRanFloat*	a,
								CrankRanFloat*	b,
								CrankRanFloat*	r	)
{
	if ((b->start) < (a->end) && (a->start) < (b->end)) {
		crank_ran_float_init (	r,
			MAX(a->start, b->start),
			MIN(a->end, b->end)	);
		return TRUE;
	}
	else {
		r->start = 0;
		r->end = 0;
		return FALSE;
	}
}






//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_ran_ptr_init:
 * @ran: (out): A Range
 * @start: Start of range.
 * @end: End of range.
 *
 * Initialize a range with given two points.
 */
void
crank_ran_ptr_init (	CrankRanPtr*	ran,
						gpointer		start,
						gpointer		end		)
{
	ran->start = start;
	ran->end = end;
}

/**
 * crank_ran_ptr_init_diff:
 * @ran: (out): A Range
 * @start: Start of range.
 * @diff: Difference of start and end.
 *
 * Initialize a range with start point and difference.
 */
void
crank_ran_ptr_init_diff (	CrankRanPtr*	ran,
							gpointer		start,
							gsize			diff	)
{
	crank_ran_ptr_init (ran, start, CRANK_PTR_ADD (start, diff));
}

//////// Basic Functions ///////////////////////////////////////////////////////

/**
 * crank_ran_ptr_copy:
 * @ran: A Range
 * @other: (out): Copied range.
 *
 * Copies a range to other
 */
void
crank_ran_ptr_copy (	CrankRanPtr*	ran,
						CrankRanPtr*	other	)
{
	crank_ran_ptr_init (other, ran->start, ran->end);
}

/**
 * crank_ran_ptr_dup:
 * @ran: A Range
 *
 * Allocates new range and copies on it.
 *
 * Returns: (transfer full): Copied range, free with g_free()
 */
CrankRanPtr*
crank_ran_ptr_dup (	CrankRanPtr*	ran	)
{
	CrankRanPtr*	result = g_new (CrankRanPtr, 1);
	crank_ran_ptr_copy (ran, result);
	return result;
}

/**
 * crank_ran_ptr_equal:
 * @a: (type CrankRanPtr): A Range
 * @b: (type CrankRanPtr): A Range
 *
 * Compares two range and checks they are same.
 *
 * Returns: Whether the two are same.
 */
gboolean
crank_ran_ptr_equal (	gconstpointer	a,
						gconstpointer	b	)
{
	CrankRanPtr*	rana = (CrankRanPtr*)a;
	CrankRanPtr*	ranb = (CrankRanPtr*)b;
	
	return (rana->start == ranb->start) && (rana->end == ranb->end);
}

/**
 * crank_ran_ptr_hash:
 * @a: (type CrankRanPtr): A Range
 *
 * Gets hash value of range.
 *
 * Returns: Hash value of range.
 */
guint
crank_ran_ptr_hash (	gconstpointer	a	)
{
	CrankRanPtr*	ran = (CrankRanPtr*)a;

	return	g_direct_hash (ran->start) * 33 +
			g_direct_hash (ran->end);
}

/**
 * crank_ran_ptr_to_string:
 * @ran: A Range
 *
 * Gets string representation of range.
 *
 * Returns: (transfer full): String representation, free with g_free().
 */
gchar*
crank_ran_ptr_to_string (	CrankRanPtr*	ran	)
{
	return crank_ran_ptr_to_string_full (ran,
			CRANK_RAN_PTR_DEFFORMAT);
}

/**
 * crank_ran_ptr_to_string_full:
 * @ran: A Range
 * @format: Format string for range. Consumes two int parameters.
 *
 * Gets string representation of range, with given format.
 *
 * Returns: (transfer full): String representation, free with g_free().
 */
gchar*
crank_ran_ptr_to_string_full (	CrankRanPtr*	ran,
								const gchar*	format	)
{
	return g_strdup_printf (format, ran->start, ran->end);
}
											
											
											
//////// Classification ////////////////////////////////////////////////////////

/**
 * crank_ran_ptr_is_empty:
 * @ran: A Range
 *
 * Checks whether it is empty range, which has zero-length.
 *
 * Returns: whether it is empty range.
 */
gboolean
crank_ran_ptr_is_empty (	CrankRanPtr*	ran		)
{
	return ran->start == ran->end;
}

//////// Attributes ////////////////////////////////////////////////////////////

/**
 * crank_ran_ptr_get_length:
 * @ran: A Range.
 *
 * Gets length of range.
 *
 * Returns: The length of range.
 */
gsize
crank_ran_ptr_get_length (	CrankRanPtr*	ran	)
{
	return CRANK_PTR_DIFF(ran->end, ran->start);
}

//////// Range function ////////////////////////////////////////////////////////


/**
 * crank_ran_ptr_get_count:
 * @ran: A Range.
 * @size: size of chunks.
 *
 * Gets count of chunk in range. This might be useful if the range represents
 * array.
 *
 * Returns: The count of chunk.
 */
guint
crank_ran_ptr_get_count (	CrankRanPtr*	ran,
							const gsize		size	)
{
	return (guint)(crank_ran_ptr_get_length(ran)/size);
}

/**
 * crank_ran_ptr_contains:
 * @ran: A Range.
 * @value: A Value
 *
 * Checks whether the value is in the range.
 *
 * Returns: Whether the value is in the range.
 */
gboolean
crank_ran_ptr_contains (	CrankRanPtr*	ran,
							gpointer		value	)
{
	return (ran->start <= value) && (value < ran->end);	
}

/**
 * crank_ran_ptr_get:
 * @ran: A Range.
 * @index: A Index.
 *
 * Gets interpolated value between start and end point.
 *
 * If @index is out of range of [0, 1], the appropriate value is returned, which
 * also out of range [@ran->start, @ran->end].
 *
 * Returns: (transfer none): A interpolated value.
 */ 
gpointer
crank_ran_ptr_get (	CrankRanPtr*	ran,
					const gfloat	index	)
{
	gsize	len = crank_ran_ptr_get_length (ran);
	
	return CRANK_PTR_ADD(ran->start, (gsize)(len * index));
}

/**
 * crank_ran_ptr_index_of:
 * @ran: A Range.
 * @value: A Value.
 *
 * Gets index from value, which index meets,
 *    * (@ran->start * (1 - index)) + (@ran->end * index) == @value.
 *
 * You can think this as inverse operation of crank_ran_int_get().
 *
 * Returns: A index for given value.
 */
gfloat
crank_ran_ptr_index_of (	CrankRanPtr*	ran,
							gpointer		value	)
{
	gsize	len = crank_ran_ptr_get_length (ran);
	gsize	diff = (gsize)value - (gsize)ran->start;
	
	return ((gfloat)diff) / len;
}

/**
 * crank_ran_ptr_clamp:
 * @ran: A Range.
 * @value: A Value.
 * 
 * Clamps a given value with in the range.
 *
 * clamp function and contains function has different checking boundary. See
 * crank_ran_uint_clamp() for detailed notes.
 *
 * Returns: (transfer none): A Clamped value.
 */
gpointer
crank_ran_ptr_clamp (	CrankRanPtr*	ran,
						gpointer		value	)
{
	return CLAMP (value, ran->start, ran->end);
}


/**
 * crank_ran_ptr_get_step:
 * @ran: A Range.
 * @step: Count of steps.
 * @step_size: Size of steps.
 * 
 * Gets pointer that away given step from start. It might be useful for working
 * with arrays.
 *
 * Returns: (transfer none): A Stepped pointer from start.
 */
gpointer
crank_ran_ptr_get_step (	CrankRanPtr*	ran,
							const guint		step,
							const gsize		step_size	)
{
	return CRANK_PTR_ADD2 (ran->start, step_size, step);
}

/**
 * crank_ran_ptr_n_step:
 * @ran: A Range.
 * @value: value to count steps.
 * @step_size: Size of steps.
 * 
 * Count the steps to @value. It might be useful for working with arrays.
 *
 * Returns: Count of step to @value.
 */
guint
crank_ran_ptr_n_step (	CrankRanPtr*	ran,
						gpointer		value,
						const gsize		step_size	)
{
	return (guint)(((gsize)value - (gsize)ran->start) / step_size);
}

/**
 * crank_ran_ptr_intersection:
 * @a: A Range.
 * @b: A Range
 * @r: (out): A Intersection of @a and @b, or empty range if there is no intersection.
 *
 * Gets intersection of two range.
 *
 * If there is no intersection, it returns %FALSE, and initialize @r with empty
 * range.
 *
 * Returns: whether if @a and @b has intersection.
 */
gboolean
crank_ran_ptr_intersection (	CrankRanPtr*	a,
								CrankRanPtr*	b,
								CrankRanPtr*	r	)
{
	if ((b->start) < (a->end) && (a->start) < (b->end)) {
		crank_ran_ptr_init (	r,
			MAX(a->start, b->start),
			MIN(a->end, b->end)	);
		return TRUE;
	}
	else {
		r->start = NULL;
		r->end = NULL;
		return FALSE;
	}
}

