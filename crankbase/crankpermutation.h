#ifndef CRANKPERMUTATION_H
#define CRANKPERMUTATION_H

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

#ifndef _CRANKBASE_INSIDE
#error	crankpermutation.h cannot be included directly.
#endif

G_BEGIN_DECLS

/**
 * CrankPermutation:
 * @data: (array length=n): Data array
 * @n: Element count.
 *
 * Represents permutation.
 */
typedef struct _CrankPermutation {
	guint*	data;
	guint	n;
} CrankPermutation;

#define CRANK_TYPE_PERMUTATION (crank_permutation_get_type ())
GType			crank_permutation_get_type (void);


//////// Initialization ////////////////////////////////////////////////////////

void				crank_permutation_init	(			CrankPermutation*	p,
														const guint			n,
														...	);

void				crank_permutation_init_arr (		CrankPermutation*	p,
														const guint			n,
														const guint*		data	);

void				crank_permutation_init_arr_take (	CrankPermutation*	p,
														const guint			n,
														guint*				data	);

void				crank_permutation_init_identity (	CrankPermutation*	p,
														const guint			n	);

void				crank_permutation_copy (			CrankPermutation*	p,
														CrankPermutation*	q	);

CrankPermutation*	crank_permutation_dup (				CrankPermutation*	p	);


void				crank_permutation_fini (			CrankPermutation*	p	);

void				crank_permutation_free (			CrankPermutation*	p	);



//////// Collections ///////////////////////////////////////////////////////////

guint			crank_permutation_get_size (	CrankPermutation*	p	);

guint			crank_permutation_get (			CrankPermutation*	p,
												const guint			i	);

gint			crank_permutation_index_of (	CrankPermutation*	p,
												const guint			v	);

//////// Operations ////////////////////////////////////////////////////////////

gint			crank_permutation_get_sign (	CrankPermutation*	p	);

gboolean		crank_permutation_check_valid (	CrankPermutation*	p	);

void			crank_permutation_swap (		CrankPermutation*	p,
												const guint			i,
												const guint			j	);

void			crank_permutation_reverse (		CrankPermutation*	p,
												CrankPermutation*	q	);

void			crank_permutation_inverse (		CrankPermutation*	p,
												CrankPermutation*	q	);

void			crank_permutation_shuffle (		CrankPermutation*	p,
												CrankPermutation*	q,
												CrankPermutation*	r	);

G_END_DECLS

#endif 
