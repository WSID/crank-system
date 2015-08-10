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

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankiter.h"
#include "crankpermutation.h"


/**
 * SECTION: crankpermutation
 * @title: Permutation
 * @short_description: Permutations, or placing of ordered items.
 * @stability: unstable
 * @include: crankbase.h
 *
 * A Permutation is a placing of ordered items. In this structure, items are
 * represented in #guint, starting from 0.
 *
 * # Validity of permutation
 *
 * #CrankPermutation represents a permutation of n of unsigned integer 0, ...,
 * (n-1). But it is implemented with an array, which may have various or/and
 * duplicated data.
 *
 * Therefore, validity of permutation would be checked, before shuffling.
 *
 * A valid permutation is,
 * * do not contains element > (n-1)
 * * do not contains duplicated elements.
 *
 * Validity can be checked by crank_permutation_check_valid()
 *
 * # Shuffling
 *
 * #CrankPermutation supports shuffling of array. for example,
 * crank_permutation_shuffle_array_float() is used to shuffling float values.
 *
 * On the other hand, it is possible to initialize permutation from array and
 * comparsion functions. In the case, comparsion function declares base ordering
 * of element.
 *
 * # Supported Operations
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
 *         <entry>arguments, array, identity, order of elements in array</entry>
 *       </row>
 *       <row>
 *         <entry>Attributes</entry>
 *         <entry>sign</entry>
 *       </row>
 *       <row>
 *         <entry>Unary Operations</entry>
 *         <entry>Reverse, Inverse</entry>
 *       </row>
 *       <row>
 *         <entry>Binary Operations</entry>
 *         <entry>Shuffle</entry>
 *       </row>
 *       <row>
 *         <entry>Modification</entry>
 *         <entry>swap</entry>
 *       </row>
 *       <row>
 *         <entry>Shuffling</entry>
 *         <entry>arrays, pointer arrays</entry>
 *       </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */


//////// Internal Declaration //////////////////////////////////////////////////

struct _CrankPermutationSortData {
	gpointer			array;
	gsize				esize;
	
	GCompareDataFunc	func;
	gpointer			userdata;
};										

static gint		crank_permutation_sortf (	gconstpointer	a,
											gconstpointer	b,
											gpointer		udata	);

static gint		crank_permutation_sortpf (	gconstpointer	a,
											gconstpointer	b,
											gpointer		udata	);


G_DEFINE_BOXED_TYPE (
		CrankPermutation,
		crank_permutation,
		crank_permutation_dup,
		crank_permutation_free	);

//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_permutation_init:
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @...: Element of permutation.
 *
 * Initialize a permutation with given elements.
 *
 * Validity is not checked in initializing. You should check validity by
 * crank_permutation_check_valid(), before using.
 */
void
crank_permutation_init (	CrankPermutation*	p,
							const guint			n,
							...	)
{
	va_list	varargs;
	va_start (varargs, n);
	
	crank_permutation_init_valist (p, n, varargs);
	
	va_end (varargs);
}

/**
 * crank_permutation_init_arr:
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @data: (array length=n): Element of permutation.
 *
 * Initialize a permutation with given elements.
 *
 * Validity is not checked in initializing. You should check validity by
 * crank_permutation_check_valid(), before using.
 */
void
crank_permutation_init_arr (	CrankPermutation*	p,
								const guint			n,
								const guint*		data	)
{
	g_return_if_fail (p != NULL);

	p->n = n;
	p->data = g_memdup (data, n * sizeof (guint));
}

/**
 * crank_permutation_init_arr_take:
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @data: (array length=n) (transfer full): Element of permutation.
 *
 * Initialize a permutation with given elements.
 *
 * Validity is not checked in initializing. You should check validity by
 * crank_permutation_check_valid(), before using.
 */
void
crank_permutation_init_arr_take (	CrankPermutation*	p,
									const guint			n,
									guint*				data	)
{
	g_return_if_fail (p != NULL);
	
	p->n = n;
	p->data = data;
}


/**
 * crank_permutation_init_valist:
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @varargs: Element of permutation.
 *
 * Initialize a permutation with elements given by va_list.
 *
 * Validity is not checked in initializing. You should check validity by
 * crank_permutation_check_valid(), before using.
 */
void
crank_permutation_init_valist (	CrankPermutation*	p,
								const guint			n,
								va_list				varargs	)
{
	guint	i;
	
	g_return_if_fail (p != NULL);
	
	p->n = n;
	p->data = g_new (guint, n);
	
	for (i = 0; i < n; i++) p->data[i] = va_arg (varargs, guint);
}


/**
 * crank_permutation_init_identity:
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 *
 * Initialize a identity permutation, which is
 * * {0, 1, 2, .... (n-1)}
 */
void
crank_permutation_init_identity (	CrankPermutation*	p,
									const guint			n	)
{
	guint	i;
	
	g_return_if_fail (p != NULL);
	
	p->n = n;
	p->data = g_new (guint, n);
	for (i = 0; i < n; i++)	p->data[i] = i;
}


/**
 * crank_permutation_init_compare_sarray: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @gsz: Size of elements.
 * @garr: Array of elements.
 * @gcmp: (scope call): Function to compare elements, to give ordering of elements.
 *
 * Initialize a permutation with ordering of elements in array.
 *
 * This function expects base ordering given by @gcmp. If elements are in base
 * ordering, the permutation will be initialized into identity permutation.
 *
 * Note
 * In Vala, this function has generic paramter, still have to pass size and
 * length of array.
 *
 * |[
 *    GCompareFunc<float?> float_compare = ...;
 *
 *    float array[5] = {...};
 *    Crank.Permutation p = Crank.Permutation.compare_sarray<float?> (
 *            5, sizeof(float), (void*)array, float_compare);
 * ]| 
 */
void
crank_permutation_init_compare_sarray (	CrankPermutation*	p,
										const guint			n,
										const gsize			gsz,
										gpointer			garr,
										GCompareFunc		gcmp	)
{
	crank_permutation_init_compare_sarray_data (p, n, gsz, garr,
			(GCompareDataFunc) (void*) gcmp, NULL);
}


/**
 * crank_permutation_init_compare_sarray_data: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @gsz: Size of elements.
 * @garr: Array of elements.
 * @gcmp: (scope call): Function to compare elements, to give ordering of elements.
 * @userdata: (closure): A userdata for data
 *
 * Initialize a permutation with ordering of elements in array. This function
 * is same as crank_permutation_init_compare_sarray(), except it receives
 * @userdata.
 */
void
crank_permutation_init_compare_sarray_data (	CrankPermutation*	p,
												const guint			n,
												const gsize			gsz,
												gpointer			garr,
												GCompareDataFunc	gcmp,
												gpointer			userdata	)
{
	struct _CrankPermutationSortData	sdata = {garr, sizeof(gpointer),gcmp, userdata};
	GArray*	arr;
	guint	i;
	
	g_return_if_fail (p != NULL);

	arr = g_array_sized_new (FALSE, FALSE, sizeof (gint), n);

	guint*	data = g_new (guint, n);
	
	for (i = 0; i < n; i++) g_array_append_val (arr, i);
	
	g_array_sort_with_data (arr, crank_permutation_sortf, &sdata);
	
	crank_permutation_init_arr_take (p, n, (guint*)arr->data);
	
	g_array_free (arr, FALSE);
}


/**
 * crank_permutation_init_compare_parray: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @garr: (array length=n): Array of elements.
 * @gcmp: (scope call): Function to compare elements, to give ordering of elements.
 *
 * Initialize a permutation with ordering of elements in array. This function is
 * similar to crank_permutation_init_compare_sarray(), but it works on elements
 * rather than address of elements.
 */
void
crank_permutation_init_compare_parray (	CrankPermutation*	p,
										const guint			n,
										gpointer*			garr,
										GCompareFunc		gcmp	)
{
	crank_permutation_init_compare_parray_data (p, n, garr,
			(GCompareDataFunc) (void*) gcmp, NULL);
}


/**
 * crank_permutation_init_compare_parray_data: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @garr: (array length=n): Array of elements.
 * @gcmp: (scope call): Function to compare elements, to give ordering of elements.
 * @userdata: (closure): A userdata for data
 *
 * Initialize a permutation with ordering of elements in array. This function is
 * similar to crank_permutation_init_compare_parray(), but it receives
 * @userdata.
 */
void
crank_permutation_init_compare_parray_data (	CrankPermutation*	p,
												const guint			n,
												gpointer*			garr,
												GCompareDataFunc	gcmp,
												gpointer			userdata	)
{
	struct _CrankPermutationSortData	sdata = {garr, sizeof(gpointer),gcmp, userdata};
	GArray*	arr;
	guint*	data;
	
	guint	i;
	
	g_return_if_fail (p != NULL);
	
	arr = g_array_sized_new (FALSE, FALSE, sizeof (gint), n);
	data = g_new (guint, n);
	
	for (i = 0; i < n; i++) g_array_append_val (arr, i);
	
	g_array_sort_with_data (arr, crank_permutation_sortpf, &sdata);
	
	crank_permutation_init_arr_take (p, n, (guint*)arr->data);
	
	g_array_free (arr, FALSE);
}


/**
 * crank_permutation_init_compare_array_int: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @arr: (array length=n): Array of elements.
 * @cmp: (scope call) (nullable): Function to compare elements, to give ordering
 *    of elements.
 *
 * Initialize a permutation with ordering of elements in array. This function
 * works on int arrays.
 * 
 * This function expectes comparsion function that compares int pointers, not
 * ints.
 */
void
crank_permutation_init_compare_array_int (	CrankPermutation*	p,
											const guint			n,
											gint*				arr,
											GCompareFunc		cmp	)
{
	if (cmp == NULL) cmp = crank_int_compare;
	crank_permutation_init_compare_array (p, n, gint, arr, cmp);
}

/**
 * crank_permutation_init_compare_array_uint: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @arr: (array length=n): Array of elements.
 * @cmp: (scope call) (nullable): Function to compare elements, to give ordering
 *    of elements.
 *
 * Initialize a permutation with ordering of elements in array. This function
 * works on unsigned int arrays.
 * 
 * This function expectes comparsion function that compares uint pointers, not
 * uints.
 */
void
crank_permutation_init_compare_array_uint (	CrankPermutation*	p,
											const guint			n,
											guint*				arr,
											GCompareFunc		cmp	)
{
	if (cmp == NULL) cmp = crank_uint_compare;
	crank_permutation_init_compare_array (p, n, guint, arr, cmp);
}

/**
 * crank_permutation_init_compare_array_float: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @arr: (array length=n): Array of elements.
 * @cmp: (scope call) (nullable): Function to compare elements, to give ordering
 *    of elements.
 *
 * Initialize a permutation with ordering of elements in array. This function
 * works on float arrays.
 */
void
crank_permutation_init_compare_array_float (	CrankPermutation*	p,
												const guint			n,
												gfloat*				arr,
												GCompareFunc		cmp	)
{
	if (cmp == NULL) cmp = crank_float_compare;
	crank_permutation_init_compare_array (p, n, gfloat, arr, cmp);
}


/**
 * crank_permutation_init_compare_array_int_data: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @arr: (array length=n): Array of elements.
 * @cmp: (scope call) (nullable): Function to compare elements, to give ordering
 *    of elements.
 * @userdata: (closure): A userdata for @cmp
 *
 * Initialize a permutation with ordering of elements in array. This function
 * works on int arrays.
 * 
 * This function expectes comparsion function that compares int pointers, not
 * ints.
 */
void
crank_permutation_init_compare_array_int_data (	CrankPermutation*	p,
												const guint			n,
												gint*				arr,
												GCompareDataFunc	cmp,
												gpointer			userdata	)
{
	if (cmp == NULL) cmp = (GCompareDataFunc) crank_int_compare;
	crank_permutation_init_compare_array_data (p, n, gint, arr, cmp, userdata);
}

/**
 * crank_permutation_init_compare_array_uint_data: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @arr: (array length=n): Array of elements.
 * @cmp: (scope call) (nullable): Function to compare elements, to give ordering
 *    of elements.
 * @userdata: (closure): A userdata for @cmp
 *
 * Initialize a permutation with ordering of elements in array. This function
 * works on unsigned int arrays.
 * 
 * This function expectes comparsion function that compares uint pointers, not
 * uints.
 */
void
crank_permutation_init_compare_array_uint_data (	CrankPermutation*	p,
													const guint			n,
													guint*				arr,
													GCompareDataFunc	cmp,
													gpointer			userdata	)
{
	if (cmp == NULL) cmp = (GCompareDataFunc) crank_uint_compare;
	crank_permutation_init_compare_array_data (p, n, guint, arr, cmp, userdata);
}

/**
 * crank_permutation_init_compare_array_float_data: (skip)
 * @p: (out): A Permutation.
 * @n: Size of permutation.
 * @arr: (array length=n): Array of elements.
 * @cmp: (scope call) (nullable): Function to compare elements, to give ordering
 *    of elements.
 * @userdata: (closure): A userdata for @cmp
 *
 * Initialize a permutation with ordering of elements in array. This function
 * works on float arrays.
 */
void
crank_permutation_init_compare_array_float_data (	CrankPermutation*	p,
													const guint			n,
													gfloat*				arr,
													GCompareDataFunc	cmp,
													gpointer			userdata	)
{
	if (cmp == NULL) cmp = (GCompareDataFunc) crank_float_compare;
	crank_permutation_init_compare_array_data (p, n, gfloat, arr, cmp, userdata);
}



/**
 * crank_permutation_copy:
 * @p: A Permutation.
 * @q: (out): A permutation.
 *
 * Copies a permutation to @q.
 */
void
crank_permutation_copy (	CrankPermutation*	p,
							CrankPermutation*	q	)
{
	crank_permutation_init_arr (q, p->n, p->data);
}

/**
 * crank_permutation_dup:
 * @p: A Permutation.
 *
 * Allocates and copies a permutation.
 *
 * Returns: new allocated permutation. free with crank_permutation_free()
 */
CrankPermutation*
crank_permutation_dup (	CrankPermutation*	p	)
{
	CrankPermutation*	result = g_new (CrankPermutation, 1);
	
	crank_permutation_copy (p, result);
	
	return result;
}



/**
 * crank_permutation_fini:
 * @p: A Permutation.
 *
 * Resets a permutation into 0 sized permutation, and frees associated memories.
 */
void
crank_permutation_fini (	CrankPermutation*	p	)
{
	g_clear_pointer (& p->data, g_free);
	p->n = 0;
}

/**
 * crank_permutation_free:
 * @p: A Permutation.
 *
 * Frees an allocated permutation.
 */
void
crank_permutation_free (	CrankPermutation*	p	)
{
	crank_permutation_fini (p);
	g_free (p);
}


//////// Basics ////////////////////////////////////////////////////////////////

/**
 * crank_permutation_equal:
 * @p: (type CrankPermutation) (nullable): A Permutation
 * @q: (type CrankPermutation) (nullable): A Permutation
 *
 * Checks that two permutations are same.
 *
 * Returns: If two permutations are same.
 */
gboolean
crank_permutation_equal (	gconstpointer		p,
							gconstpointer		q	)
{
	CrankPermutation*	pp = (CrankPermutation*)p;
	CrankPermutation*	pq = (CrankPermutation*)q;
	
	if (pp == NULL)			return pq == NULL;
	else if (pq == NULL)	return FALSE;
	
	if (pp->n == pq->n) {
		guint	i;
		for (i = 0; i < pp->n; i++) {
			if (pp->data[i] != pq->data[i]) return FALSE;
		}
		return TRUE;
	}
	
	return FALSE;
}


/**
 * crank_permutation_hash:
 * @p: (type CrankPermutation) (nullable): A Permutation
 *
 * Constructs a hash value of permutation.
 *
 * Returns: Hash value of permutation
 */
guint
crank_permutation_hash (	gconstpointer		p	)
{
	CrankPermutation*	pp = (CrankPermutation*)p;
	guint 	sum = 0;
	guint	i;
	
	if (pp == NULL) return 0;
	
	for (i = 0; i < pp->n; i++) {
		sum += g_int_hash (pp->data + i);
		sum *= 23;
	}
	
	return sum;
}


/**
 * crank_permutation_to_string:
 * @p: A Permutation
 *
 * Stringify a permutation.
 *
 * Returns: (transfer full): String representation of permutation.
 */
gchar*
crank_permutation_to_string (	CrankPermutation*	p	)
{
	GString*	builder;
	gchar*		result;
	guint		i;
	
	g_return_val_if_fail (p != NULL, NULL);
	
	builder = g_string_new ("(");
	
	if (0 < p->n) {
		g_string_append_printf(builder, "%u", p->data[0]);
	
		for (i = 1; i < p->n; i++)
			g_string_append_printf (builder, ", %u", p->data[i]);
	}
	
	g_string_append_c (builder, ')');
	
	result = builder->str;
	
	g_string_free (builder, FALSE);
	
	return result;
}




//////// Collections ///////////////////////////////////////////////////////////

/**
 * crank_permutation_is_empty:
 * @p: A Permutation.
 *
 * checks whether it is empty. (has 0 element.)
 *
 * Returns: Whether it is empty.
 */
gboolean
crank_permutation_is_empty (	CrankPermutation*	p	)
{
	g_return_val_if_fail (p != NULL, TRUE);
	
	return p->n == 0;
}

/**
 * crank_permutation_get_size:
 * @p: A Permutation.
 *
 * Gets size of permutation.
 *
 * Returns: size of permutation.
 */
guint
crank_permutation_get_size (	CrankPermutation*	p	)
{
	g_return_val_if_fail (p != NULL, 0);

	return p->n;
}

/**
 * crank_permutation_get:
 * @p: A Permutation.
 * @i: Index of element.
 *
 * Gets element of permutation.
 *
 * Note that the there is no crank_permutation_set function.
 * This is because it cannot ensure that validity of permutation.
 *
 * Returns: Value of element.
 */
guint
crank_permutation_get (	CrankPermutation*	p,
						const guint			i	)
{
	g_return_val_if_fail (p != NULL, 0);
	g_return_val_if_fail (i < p->n, 0);
	
	return p->data[i];
}

/**
 * crank_permutation_index_of:
 * @p: A Permutation.
 * @v: Value of element.
 *
 * Gets index of element.
 *
 * Returns: Index of element or, -1 if value is not found.
 */
gint
crank_permutation_index_of (	CrankPermutation*	p,
								const guint			v	)
{
	guint	i;
	
	g_return_val_if_fail (v < p->n, -1);
	
	for (i = 0; i < p->n; i++)
		if (p->data[i] == v) return i;
	
	return -1;
}

/**
 * crank_permutation_slice: (skip)
 * @p: A Permutation.
 * @from: Index to start slicing.
 * @to: Index to end slicing.
 *
 * Gets slice of permutation. This slice may not be valid permutation.
 *
 * Attempt to get empty slice results in %NULL.
 *
 * Returns: (array) (transfer full) (nullable): sliced data in permutation.
 */
guint*
crank_permutation_slice (	CrankPermutation*	p,
							const guint			from,
							const guint			to	)
{
	guint*	result;
	guint	i;
	guint	n;

	g_return_val_if_fail (p, NULL);
	g_return_val_if_fail (from <= to, NULL);
	g_return_val_if_fail (to <= p->n, NULL);
	
	n = to - from;
	result = g_new (guint, n);
	
	for (i = 0; i < n; i++) {
		result [i] = p->data [i + from];
	}
	
	return result;
}

/**
 * crank_permutation_iterator:
 * @p: A Permutation.
 * @iter: (out): A Iterator.
 *
 * Initializes a iterator for a permutation.
 */
void
crank_permutation_iterator (	CrankPermutation*	p,
								CrankIterMemUint*	iter )
{
	crank_iter_mem_uint_init_with_count (iter, p->data, p->n);
}

/**
 * crank_permutation_foreach:
 * @p: A Permutation.
 * @func: (scope call): A Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a permutation with given function.
 *
 * By returning %TRUE, iteration continues.
 * By returning %FALSE, iteration breaks.
 *
 * Returns: Whether iteration was fully done without breaking.
 */
gboolean
crank_permutation_foreach (	CrankPermutation*	p,
							CrankBoolUintFunc	func,
							gpointer			userdata	)
{
	guint		i;
	
	for (i = 0; i < p->n; i++)
		if (! func (p->data[i], userdata)) return FALSE;
	
	return TRUE;
}


//////// Operations ////////////////////////////////////////////////////////////

/**
 * crank_permutation_is_identity:
 * @p: A Permutation.
 *
 * Checks whether it is identity permutation.
 *
 * Returns: Whether it is identity permutation.
 */
gboolean
crank_permutation_is_identity (	CrankPermutation*	p	)
{
	guint i;

	g_return_val_if_fail (p != NULL, FALSE);
	
	for (i = 0; i < p->n; i++) if (p->data[i] != i) return FALSE;
	return TRUE;
}


/**
 * crank_permutation_get_inversion:
 * @p: A Permutation.
 *`
 * Gets inversion number of permutation.
 *
 * Returns: Inversion number of pemutation.
 */
guint
crank_permutation_get_inversion (	CrankPermutation*	p	)
{
	guint	i;
	guint	j;
	guint	inversion = 0;
	
	g_return_val_if_fail (p != NULL, 0);
	
	for (i = 0; i < p->n; i++)
		for (j = i + 1; j < p->n; j++)
			if (p->data[i] < p->data[j]) inversion++;
	
	return inversion;
}
	

/**
 * crank_permutation_get_sign:
 * @p: A Permutation
 *
 * Gets sign of permutation.
 *
 * If @p is 0 sized permutation, 0 is returned.
 *
 * Returns: 1 or -1, or 0.
 */
gint
crank_permutation_get_sign (	CrankPermutation*	p	)
{
	g_return_val_if_fail (p != NULL, 0);
	if (crank_permutation_is_empty (p)) return 0;
	return (crank_permutation_get_inversion (p) % 2 != 0) ? -1 : 1;
}


/**
 * crank_permutation_get_ascents:
 * @p: A Permutation.
 * @rn: Length of returned array.
 *
 * Gets all of indices of ascents. (increasing point - p[i] where p[i] < p[i+ 1])
 *
 * For permutation like (0 1 2 ... (n-1)) => ((n-1), (n-2), .... 0), it returns
 * %NULL
 *
 * Returns: (array length=rn) (transfer container) (nullable):
 *    Indices of ascents.
 */
guint*
crank_permutation_get_ascents (	CrankPermutation*	p,
								guint*				rn	)
{
	guint	i;
	guint*	result;
	guint	n = 0;

	g_return_val_if_fail (rn != NULL, NULL);
	g_return_val_if_fail (p != NULL, NULL);
	
	result = g_new (guint, p->n - 1);
	
	for (i = 0; i < p->n - 1; i++) {
		if (p->data[i] < p->data[i+1]) {
			result[n] = i;
			n++;
		}
	}
	*rn = n;
	return g_renew (guint, result, n);
}

/**
 * crank_permutation_get_descents:
 * @p: A Permutation.
 * @rn: Length of returned array.
 *
 * Gets all of indices of descents. (Decreasing point - p[i] where p[i] > p[i+ 1])
 *
 * For permutation like (0 1 2 ... (n-1)) => ((n-1), (n-2), .... 0), it returns
 * %NULL
 *
 * Returns: (array length=rn) (transfer container) (nullable):
 *    Indices of descents.
 */
guint*
crank_permutation_get_descents (	CrankPermutation*	p,
									guint*				rn	)
{
	guint	i;
	guint*	result;
	guint	n = 0;

	g_return_val_if_fail (rn != NULL, NULL);
	g_return_val_if_fail (p != NULL, NULL);
	
	result = g_new (guint, p->n - 1);
	
	for (i = 0; i < p->n - 1; i++) {
		if (p->data[i] > p->data[i+1]) {
			result[n] = i;
			n++;
		}
	}
	*rn = n;
	return g_renew (guint, result, n);
}

/**
 * crank_permutation_get_excedances:
 * @p: A Permutation.
 * @rn: Length of returned array.
 *
 * Gets all of indices of excedances. (p[i], where i < p[i])
 *
 * Returns: (array length=rn) (transfer container) (nullable):
 *    Indices of excedances.
 */
guint*
crank_permutation_get_excedances (	CrankPermutation*	p,
									guint*				rn	)
{
	guint	i;
	guint*	result;
	guint	n = 0;

	g_return_val_if_fail (rn != NULL, NULL);
	g_return_val_if_fail (p != NULL, NULL);
	
	result = g_new (guint, p->n);
	
	for (i = 0; i < p->n; i++) {
		if (p->data[i] > i) {
			result[n] = i;
			n++;
		}
	}
	*rn = n;
	return g_renew (guint, result, n);
}

/**
 * crank_permutation_check_valid:
 * @p: A Permutation.
 *
 * Checks whether the permutation is valid permutation.
 * This means permutation has no duplicate, and has 0 ~ (n-1) as element.
 *
 * Returns: Whether @p is valid permutation.
 */
gboolean
crank_permutation_check_valid (	CrankPermutation*	p	)
{
	guint	i;
	guint	j;
	
	g_return_val_if_fail (p != NULL, FALSE);
	
	for (i = 0; i < p->n; i++) {
		if (p->n <= p->data[i]) return FALSE;
	
		for (j = i + 1; j < p->n; j++)
			if (p->data[i] == p->data[j]) return FALSE;
	}
	
	return TRUE;
}
 

/**
 * crank_permutation_swap:
 * @p: A Permutation.
 * @i: Index.
 * @j: Index.
 *
 * Swaps two element of permutation.
 *
 * This inverts sign of permutation.
 */
void
crank_permutation_swap (	CrankPermutation*	p,
							const guint			i,
							const guint			j	)
{
	guint	temp;
	
	g_return_if_fail (p != NULL);
	
	temp = p->data[i];
	p->data[i] = p->data[j];
	p->data[j] = temp;
}

/**
 * crank_permutation_reverse:
 * @p: A Permutation.
 * @q: (out): A Permutation to store result.
 *
 * Reverse a permutation, so that first element placed to last.
 *
 * If (size % 4) is 2 or 3, reversed permutation has inverted sign of original
 * permutation.
 *
 * This means
 * * {1, 3, 4, 2, 5}
 * becomes
 * * {5, 2, 4, 3, 1}
 */
void
crank_permutation_reverse (		CrankPermutation*	p,
								CrankPermutation*	q	)
{
	guint	i;
	guint*	data;
	
	g_return_if_fail (p != NULL);
	g_return_if_fail (q != NULL);
	g_return_if_fail (p != q);
	
	data = g_new (guint, p->n);
	
	for (i = 0; i < p->n; i++)
		data[p->n - 1 - i] = p->data[i];
	
	crank_permutation_init_arr_take (q, p->n, data);
}

/**
 * crank_permutation_inverse:
 * @p: A Permutation.
 * @q: (out): A Permutation to store result.
 *
 * Inverse a permutation. Inverted permutation reverts original permutation.
 *
 * Inverted permutation has same sign of original permutation.
 *
 * This means
 * * {1, 3, 4, 2, 5}
 * becomes
 * * {5, 4, 2, 3, 1}
 */
void
crank_permutation_inverse (	CrankPermutation*	p,
							CrankPermutation*	q	)
{
	guint	i;
	guint*	data;
	
	g_return_if_fail (p != NULL);
	g_return_if_fail (q != NULL);
	g_return_if_fail (p != q);
	
	data = g_new (guint, p->n);
	
	for (i = 0; i < p->n; i++)
		data[p->data[i]] = i;

	crank_permutation_init_arr_take (q, p->n, data);
}


/**
 * crank_permutation_shuffle:
 * @p: A Permutation.
 * @q: A Permutation.
 * @r: (out): A Permutation to store result.
 *
 * Shuffles @p with order of @q.
 *
 * The sign of result, is product of two permutations.
 */
void
crank_permutation_shuffle (	CrankPermutation*	p,
							CrankPermutation*	q,
							CrankPermutation*	r	)
{
	guint 	i;
	guint*	data;
	
	crank_permutation_init (r, 0);
	
	g_return_if_fail (p != NULL);
	g_return_if_fail (q != NULL);
	g_return_if_fail (r != NULL);
	g_return_if_fail (p != r);
	
	if (p->n != q->n) {
		g_warning ("Permutation: shuffle: size mismatch: %u, %u", p->n, q->n);
		return;
	}
	
	data = g_new (guint, p->n);
	
	for (i = 0; i < p->n; i++)
		data[i] = p->data[ q->data[i] ];
	
	crank_permutation_init_arr_take (r, p->n, data);
}


/**
 * crank_permutation_reverse_self:
 * @p: A Permutation
 *
 * Reverses a permutation. See crank_permutation_reverse().
 */
void
crank_permutation_reverse_self (	CrankPermutation*	p	)
{
	guint 	i;
	guint*	data;
	
	g_return_if_fail (p != NULL);
	
	data = g_new (guint, p->n);
	
	for (i = 0; i < p->n; i++)	data[p->n - 1 - i] = p->data[i];
	
	g_free (p->data);
	p->data = data;
}


/**
 * crank_permutation_inverse_self:
 * @p: A Permutation
 *
 * Inverses a permutation. See crank_permutation_inverse().
 */
void
crank_permutation_inverse_self (	CrankPermutation*	p	)
{
	guint 	i;
	guint*	data;
	
	g_return_if_fail (p != NULL);
	
	data = g_new (guint, p->n);
	
	for (i = 0; i < p->n; i++)	data[p->data[i]] = i;
	
	g_free (p->data);
	p->data = data;
}


/**
 * crank_permutation_shuffle_self:
 * @p: A Permutation
 * @q: A Permutation
 *
 * Shuffles permutation with other permutation. See crank_permutation_shuffle().
 */
void
crank_permutation_shuffle_self (CrankPermutation*	p,
								CrankPermutation*	q	)
{
	guint 	i;
	guint*	data;
	
	g_return_if_fail (p != NULL);
	g_return_if_fail (q != NULL);
	
	if (p->n != q->n) {
		g_warning ("Permutation: shuffle: size mismatch: %u, %u", p->n, q->n);
		return;
	}
	
	data = g_new (guint, p->n);
	
	for (i = 0; i < p->n; i++)
		data[i] = p->data[ q->data[i] ];
	
	g_free (p->data);
	p->data = data;
}



//////// Shuffling /////////////////////////////////////////////////////////////

/**
 * crank_permutation_shuffle_sarray: (skip)
 * @p: A Permutation
 * @gsz: Size of elements.
 * @arr: An array.
 *
 * Stores shuffle result into newly allocated array. Copy is done by memcpy.
 *
 * Returns: An array holding shuffled elemets.
 */ 
gpointer
crank_permutation_shuffle_sarray (	CrankPermutation*	p,
									const gsize			gsz,
									gpointer			arr	)
{
	guint8*	arr_mem = (guint8*) arr;
	guint8* result = g_malloc (gsz * p->n);
	guint	i;
	guint	j;
	
	g_return_val_if_fail (p != NULL, NULL);
	g_return_val_if_fail (gsz != 0, NULL);
	g_return_val_if_fail (arr != NULL, NULL);
	
	arr_mem = (guint8*) arr;
	result = g_malloc (gsz * p->n);
	
	for (i = 0; i < p->n; i++) {
		j = crank_permutation_get (p, i);
		
		memcpy (result + (gsz * j),  arr_mem + (gsz * i),   gsz);
	}
	
	return result;
}

/**
 * crank_permutation_shuffle_parray: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 *
 * Stores shuffle result into newly allocated array.
 *
 * Returns: An array holding shuffled elemets.
 */ 
gpointer*
crank_permutation_shuffle_parray (	CrankPermutation*	p,
									gpointer*			arr	)
{
	gpointer* result;
	guint	i;
	guint	j;
	
	g_return_val_if_fail (p != NULL, NULL);
	g_return_val_if_fail (arr != NULL, NULL);
	
	result = g_new (gpointer, p->n);
	
	for (i = 0; i < p->n; i++) {
		j = crank_permutation_get (p, i);
		result[j] = arr[i];
	}
	
	return result;
}



/**
 * crank_permutation_shuffle_array_boolean: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 *
 * Stores shuffle result into newly allocated array.
 *
 * Returns: An array holding shuffled elemets.
 */
gboolean*
crank_permutation_shuffle_array_boolean (	CrankPermutation*	p,
											gboolean*			arr	)
{
	gboolean* result;
	guint	i;
	guint	j;
	
	g_return_val_if_fail (p != NULL, NULL);
	g_return_val_if_fail (arr != NULL, NULL);
	
	result = g_new (gboolean, p->n);
	
	for (i = 0; i < p->n; i++) {
		j = crank_permutation_get (p, i);
		result[j] = arr[i];
	}
	
	return result;
}

/**
 * crank_permutation_shuffle_array_int: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 *
 * Stores shuffle result into newly allocated array.
 *
 * Returns: (transfer container): An array holding shuffled elemets.
 */
gint*
crank_permutation_shuffle_array_int (	CrankPermutation*	p,
										gint*				arr	)
{
	gint* result;
	guint	i;
	guint	j;
	
	g_return_val_if_fail (p != NULL, NULL);
	g_return_val_if_fail (arr != NULL, NULL);
	
	result = g_new (gint, p->n);
	
	for (i = 0; i < p->n; i++) {
		j = crank_permutation_get (p, i);
		result[j] = arr[i];
	}
	
	return result;
}

/**
 * crank_permutation_shuffle_array_uint: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 *
 * Stores shuffle result into newly allocated array.
 *
 * Returns: (transfer container): An array holding shuffled elemets.
 */
guint*
crank_permutation_shuffle_array_uint (	CrankPermutation*	p,
										guint*				arr	)
{
	guint* result;
	guint	i;
	guint	j;
	
	g_return_val_if_fail (p != NULL, NULL);
	g_return_val_if_fail (arr != NULL, NULL);
	
	result = g_new (gint, p->n);
	
	for (i = 0; i < p->n; i++) {
		j = crank_permutation_get (p, i);
		result[j] = arr[i];
	}
	
	return result;
}


/**
 * crank_permutation_shuffle_array_float: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 *
 * Stores shuffle result into newly allocated array.
 *
 * Returns: (transfer container): An array holding shuffled elemets.
 */
gfloat*
crank_permutation_shuffle_array_float (	CrankPermutation*	p,
										gfloat*				arr	)
{
	gfloat* result;
	guint	i;
	guint	j;
	
	g_return_val_if_fail (p != NULL, NULL);
	g_return_val_if_fail (arr != NULL, NULL);
	
	result = g_new (gfloat, p->n);
	
	for (i = 0; i < p->n; i++) {
		j = crank_permutation_get (p, i);
		result[j] = arr[i];
	}
	
	return result;
}


//////// GI Support ////////////////////////////////////////////////////////////

/**
 * crank_permutation__gi_slice: (rename-to crank_permutation_slice)
 * @p: A Permutation.
 * @from: Index to start slicing.
 * @to: Index to end slicing.
 * @result_len: (out): Length of slice.
 *
 * Gets slice of permutation. This slice may not be valid permutation.
 *
 * Attempt to get empty slice results in %NULL.
 *
 * Returns: (array length=result_len) (transfer full) (nullable):
 *    sliced data in permutation.
 */
guint*
crank_permutation__gi_slice (	CrankPermutation*	p,
								const guint			from,
								const guint			to,
								guint*				result_len	)
{
	guint*	result = crank_permutation_slice (p, from, to);
	
	*result_len = G_UNLIKELY(result == NULL) ? 0 : (to - from);
	
	return result;
}


//////// Vala Support //////////////////////////////////////////////////////////


/**
 * crank_permutation_init_vala_compare_sarray: (skip)
 * @n: Size of permutation.
 * @gsz: Size of elements.
 * @garr: Array of elements.
 * @gcmp: (scope call): Function to compare elements, to give ordering of elements.
 * @p: (out): A Permutation.
 *
 * Vala specific function.
 */ 
void
crank_permutation_init_vala_compare_sarray (	const guint			n,
												const gsize			gsz,
												gpointer			garr,
												GCompareFunc		gcmp,
												CrankPermutation*	p	)
{
	crank_permutation_init_compare_sarray (p, n, gsz, garr, gcmp);
}

/**
 * crank_permutation_init_vala_compare_sarray_data: (skip)
 * @n: Size of permutation.
 * @gsz: Size of elements.
 * @garr: Array of elements.
 * @gcmp: (scope call): Function to compare elements, to give ordering of elements.
 * @userdata: (closure): Userdata for @gcmp.
 * @p: (out): A Permutation.
 *
 * Vala specific function.
 */ 
void
crank_permutation_init_vala_compare_sarray_data (	const guint			n,
													const gsize			gsz,
													gpointer			garr,
													GCompareDataFunc	gcmp,
													gpointer			userdata,
													CrankPermutation*	p	)
{
	crank_permutation_init_compare_sarray_data (p, n, gsz, garr, gcmp, userdata);
}

/**
 * crank_permutation_init_vala_compare_parray: (skip)
 * @n: Size of permutation.
 * @garr: (array length=n): Array of elements.
 * @gcmp: (scope call): Function to compare elements, to give ordering of elements.
 * @p: (out): A Permutation.
 *
 * Vala specific function.
 */ 
void
crank_permutation_init_vala_compare_parray (	const guint			n,
												gpointer*			garr,
												GCompareFunc		gcmp,
												CrankPermutation*	p	)
{
	crank_permutation_init_compare_parray (p, n, garr, gcmp);
}

/**
 * crank_permutation_init_vala_compare_parray_data: (skip)
 * @n: Size of permutation.
 * @garr: (array length=n): Array of elements.
 * @gcmp: (scope call): Function to compare elements, to give ordering of elements.
 * @userdata: (closure): Userdata for @gcmp.
 * @p: (out): A Permutation.
 *
 * Vala specific function.
 */ 
void
crank_permutation_init_vala_compare_parray_data (	const guint			n,
													gpointer*			garr,
													GCompareDataFunc	gcmp,
													gpointer			userdata,
													CrankPermutation*	p	)
{
	crank_permutation_init_compare_parray_data (p, n, garr, gcmp, userdata);
}
															
/**
 * crank_permutation_vala_shuffle_parray: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 * @rn: length of returned array
 *
 * Stores shuffle result into newly allocated array. Copy is done by memcpy.
 *
 * This function is for vala.
 *
 * Returns: (array length=rn) (transfer container):
 *    An array holding shuffled elemets. Free with g_free().
 */ 
gpointer*
crank_permutation_vala_shuffle_parray (	CrankPermutation*	p,
										gpointer*			arr,
										guint*				rn	)
{
	if (rn != NULL) *rn = p->n;
	return crank_permutation_shuffle_parray (p, arr);
}

/**
 * crank_permutation_vala_shuffle_array_boolean: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 * @rn: length of returned array
 *
 * Stores shuffle result into newly allocated array.
 *
 * This function is for vala.
 *
 * Returns: (array length=rn) (transfer container):
 *    An array holding shuffled elemets. Free with g_free().
 */ 
gboolean*
crank_permutation_vala_shuffle_array_boolean (	CrankPermutation*	p,
												gboolean*			arr,
												guint*				rn	)
{
	if (rn != NULL) *rn = p->n;
	return crank_permutation_shuffle_array_boolean (p, arr);
}

/**
 * crank_permutation_vala_shuffle_array_int: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 * @rn: length of returned array
 *
 * Stores shuffle result into newly allocated array.
 *
 * This function is for vala.
 *
 * Returns: (array length=rn) (transfer container):
 *    An array holding shuffled elemets. Free with g_free().
 */ 
gint*
crank_permutation_vala_shuffle_array_int (	CrankPermutation*	p,
												gint*				arr,
												guint*				rn	)
{
	if (rn != NULL) *rn = p->n;
	return crank_permutation_shuffle_array_int (p, arr);
}

/**
 * crank_permutation_vala_shuffle_array_uint: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 * @rn: length of returned array
 *
 * Stores shuffle result into newly allocated array.
 *
 * This function is for vala.
 *
 * Returns: (array length=rn) (transfer container):
 *    An array holding shuffled elemets. Free with g_free().
 */ 
guint*
crank_permutation_vala_shuffle_array_uint (	CrankPermutation*	p,
											guint*				arr,
											guint*				rn	)
{
	if (rn != NULL) *rn = p->n;
	return crank_permutation_shuffle_array_uint (p, arr);
}

/**
 * crank_permutation_vala_shuffle_array_float: (skip)
 * @p: A Permutation
 * @arr: (array): An array.
 * @rn: length of returned array
 *
 * Stores shuffle result into newly allocated array.
 *
 * This function is for vala.
 *
 * Returns: (array length=rn) (transfer container):
 *    An array holding shuffled elemets. Free with g_free().
 */ 
gfloat*
crank_permutation_vala_shuffle_array_float (	CrankPermutation*	p,
												gfloat*				arr,
												guint*				rn	)
{
	if (rn != NULL) *rn = p->n;
	return crank_permutation_shuffle_array_float (p, arr);
}

//////// Internal Definition ///////////////////////////////////////////////////

static gint
crank_permutation_sortf (	gconstpointer		a,
							gconstpointer		b,
							gpointer			userdata	)
{
	struct _CrankPermutationSortData*	sdata =
		(struct _CrankPermutationSortData*)	userdata;
	
	gpointer	apt = ((guint8*)(sdata->array)) + *((guint*)a) * sdata->esize;
	gpointer	bpt = ((guint8*)(sdata->array)) + *((guint*)b) * sdata->esize;
	
	return sdata->func (apt, bpt, sdata->userdata);
}

static gint
crank_permutation_sortpf (	gconstpointer		a,
							gconstpointer		b,
							gpointer			userdata	)
{
	struct _CrankPermutationSortData*	sdata =
		(struct _CrankPermutationSortData*)	userdata;
	
	gpointer	apt = ((gpointer*)(sdata->array)) [*((guint*)a)];
	gpointer	bpt = ((gpointer*)(sdata->array)) [*((guint*)b)];
	
	return sdata->func (apt, bpt, sdata->userdata);
}
