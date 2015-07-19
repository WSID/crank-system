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

#include <glib.h>
#include <glib-object.h>

#include <stdarg.h>

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
 * # Operations
 *
 * Supported operations are,
 * * properties
 *    * sign
 * * Unary operations
 *    * Reverse
 *    * Inverse
 * * Binary operations
 *    * Shuffle
 * * Modification
 *    * swap
 */


//////// Internal Declaration //////////////////////////////////////////////////

static void		crank_permutation_realloc (	CrankPermutation*	p,
											const guint			n	);
										


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
	guint	i;
	
	crank_permutation_realloc (p, n);
	
	va_start (varargs, n);
	
	for (i = 0; i < n; i++) p->data[i] = va_arg (varargs, guint);
	
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
	g_free (p->data);
	p->data = g_memdup (data, n * sizeof (guint));
	p->n = n;
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
	g_free (p->data);
	p->data = data;
	p->n = n;
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
	
	crank_permutation_realloc (p, n);
	
	for (i = 0; i < n; i++)	p->data[i] = i;
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


//////// Collections ///////////////////////////////////////////////////////////

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
	
	if (v < p->n) return -1;
	
	for (i = 0; i < p->n; i++)
		if (p->data[i] == v) return i;
	
	return -1;
}

//////// Operations ////////////////////////////////////////////////////////////

/**
 * crank_permutation_get_sign:
 * @p: A Permutation
 *
 * Gets sign of permutation.
 *
 * This function counts number of smaller elements that comes after each
 * elements. If number is even, sign will be +, and for odd, -.
 *
 * The permutation {1, 3, 4, 2, 5} will have + sign.
 * * for 1, every element is larger than 1.
 * * for 3, 2 is smaller than 3.
 * * for 4, 2 is smaller than 4.
 * * for 2, every element comes after, are larger than 2.
 * * for 5, no more element comes.
 *
 * If sign is +, then 1 is returned, for -, -1 is returned.
 *
 * If @p is 0 sized permutation, 0 is returned.
 *
 * Returns: 1 or -1, or 0.
 */
gint
crank_permutation_get_sign (	CrankPermutation*	p	)
{
	guint	i;
	guint	j;
	guint	inversion = 0;
	
	if (p->n == 0) return 0;
	
	for (i = 0; i < p->n; i++)
		for (j = i + 1; j < p->n; j++)
			if (p->data[i] < p->data[j]) inversion++;
	
	return (inversion % 2 != 0) ? -1 : 1;
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
	guint	temp = p->data[i];
	
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
	guint*	data = g_new (guint, p->n);
	
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
	guint*	data = g_new (guint, p->n);
	
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
	
	if (p->n != q->n) {
		g_warning ("Permutation: shuffle: size mismatch: %u, %u", p->n, q->n);
		crank_permutation_fini (r);
		return;
	}
	
	data = g_new (guint, p->n);
	
	for (i = 0; i < p->n; i++)
		data[i] = p->data[ q->data[i] ];
	
	crank_permutation_init_arr_take (r, p->n, data);
}

//////// Internal Definition ///////////////////////////////////////////////////

static void
crank_permutation_realloc (	CrankPermutation*	p,
							const guint			n	)
{
	p->data = g_renew (guint, p->data, n);
	p->n = n;
}
