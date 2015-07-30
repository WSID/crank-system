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

#include <stdarg.h>
#include <glib.h>

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

void				crank_permutation_init_valist (		CrankPermutation*	p,
														const guint			n,
														va_list				varargs	);


void				crank_permutation_init_identity (	CrankPermutation*	p,
														const guint			n	);


void				crank_permutation_init_compare_sarray (	CrankPermutation*	p,
															const guint			n,
															const gsize			gsz,
															gpointer			garr,
															GCompareFunc		gcmp	);

void				crank_permutation_init_compare_sarray_data (	CrankPermutation*	p,
																	const guint			n,
																	const gsize			gsz,
																	gpointer			garr,
																	GCompareDataFunc	gcmp,
																	gpointer			userdata	);

/**
 * crank_permutation_init_compare_array: (skip)
 * @p: A Permutation
 * @n: Size of permutation.
 * @G: type of element.
 * @garr: (element-type G): An array.
 * @gcmp: Compare function for base ordering.
 *
 * Initialize permutation from ordering of array, by base ordering given by
 * @gcmp. if array is sorted, the permutation becomes identity. 
 *
 */ 
#define	crank_permutation_init_compare_array(p, n, G, garr, gcmp) \
					crank_permutation_init_compare_sarray ((p), (n), sizeof (G), (garr), (gcmp))

/**
 * crank_permutation_init_compare_array_data: (skip)
 * @p: A Permutation
 * @n: Size of permutation.
 * @G: type of element.
 * @garr: (element-type G): An array.
 * @gcmp: Compare function for base ordering.
 * @userdata: (closure): Userdata for @gcmp.
 *
 * Initialize permutation from ordering of array, by base ordering given by
 * @gcmp. if array is sorted, the permutation becomes identity. 
 *
 */ 
#define	crank_permutation_init_compare_array_data(p, n, G, garr, gcmp, userdata) \
					crank_permutation_init_compare_sarray_data ((p), (n), sizeof (G), (garr), (gcmp), (userdata))


void				crank_permutation_init_compare_parray (	CrankPermutation*	p,
															const guint			n,
															gpointer*			garr,
															GCompareFunc		gcmp	);

void				crank_permutation_init_compare_parray_data (	CrankPermutation*	p,
																	const guint			n,
																	gpointer*			garr,
																	GCompareDataFunc	gcmp,
																	gpointer			userdata	);

void				crank_permutation_init_compare_array_int (	CrankPermutation*	p,
																const guint			n,
																gint*				arr,
																GCompareFunc		cmp	);

void				crank_permutation_init_compare_array_uint (	CrankPermutation*	p,
																const guint			n,
																guint*				arr,
																GCompareFunc		cmp	);

void				crank_permutation_init_compare_array_float (CrankPermutation*	p,
																const guint			n,
																gfloat*				arr,
																GCompareFunc		cmp	);

void				crank_permutation_init_compare_array_int_data (		CrankPermutation*	p,
																		const guint			n,
																		gint*				arr,
																		GCompareDataFunc	cmp,
																		gpointer			userdata	);

void				crank_permutation_init_compare_array_uint_data (	CrankPermutation*	p,
																		const guint			n,
																		guint*				arr,
																		GCompareDataFunc	cmp,
																		gpointer			userdata	);

void				crank_permutation_init_compare_array_float_data (	CrankPermutation*	p,
																		const guint			n,
																		gfloat*				arr,
																		GCompareDataFunc	cmp,
																		gpointer			userdata	);


void				crank_permutation_copy (			CrankPermutation*	p,
														CrankPermutation*	q	);

CrankPermutation*	crank_permutation_dup (				CrankPermutation*	p	);


void				crank_permutation_fini (			CrankPermutation*	p	);

void				crank_permutation_free (			CrankPermutation*	p	);


//////// Basics ////////////////////////////////////////////////////////////////


gboolean		crank_permutation_equal (		gconstpointer		p,
												gconstpointer		q	);

guint			crank_permutation_hash (		gconstpointer		p	);

gchar*			crank_permutation_to_string (	CrankPermutation*	p	);


//////// Collections ///////////////////////////////////////////////////////////

guint			crank_permutation_get_size (	CrankPermutation*	p	);

guint			crank_permutation_get (			CrankPermutation*	p,
												const guint			i	);

gint			crank_permutation_index_of (	CrankPermutation*	p,
												const guint			v	);

guint*			crank_permutation_slice (		CrankPermutation*	p,
												const guint			from,
												const guint			to	);

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

void			crank_permutation_reverse_self (CrankPermutation*	p	);

void			crank_permutation_inverse_self (CrankPermutation*	p	);

void			crank_permutation_shuffle_self (CrankPermutation*	p,
												CrankPermutation*	q	);


//////// Shuffling /////////////////////////////////////////////////////////////

gpointer		crank_permutation_shuffle_sarray (	CrankPermutation*	p,
													const gsize			gsz,
													gpointer			arr	);

/**
 * crank_permutation_shuffle_array: (skip)
 * @p: A Permutation
 * @G: type of element.
 * @arr: (element-type G): An array.
 *
 * Stores shuffle result into newly allocated array. Copy is done by memcpy.
 *
 * Returns: (element-type G) (transfer container):
 *    An array holding shuffled elemets. free with g_free()
 */ 
#define			crank_permutation_shuffle_array(p,G,arr) \
					crank_permutation_shuffle_sarray ((p),sizeof(G),(void**)(arr));

gpointer*		crank_permutation_shuffle_parray (	CrankPermutation*	p,
													gpointer*			arr	);

gboolean*		crank_permutation_shuffle_array_boolean (	CrankPermutation*	p,
															gboolean*			arr	);

gint*			crank_permutation_shuffle_array_int (		CrankPermutation*	p,
															gint*				arr	);

gfloat*			crank_permutation_shuffle_array_float (		CrankPermutation*	p,
															gfloat*				arr	);


//////// GI Support ////////////////////////////////////////////////////////////

guint*		crank_permutation__gi_slice (	CrankPermutation*	p,
											const guint			from,
											const guint			to,
											guint*				result_len	);

//////// Vala Support //////////////////////////////////////////////////////////


void		crank_permutation_init_vala_compare_sarray (	const guint			n,
													const gsize			gsz,
													gpointer			garr,
													GCompareFunc		gcmp,
													CrankPermutation*	p	);

void		crank_permutation_init_vala_compare_sarray_data (	const guint			n,
															const gsize			gsz,
															gpointer			garr,
															GCompareDataFunc	gcmp,
															gpointer			userdata,
															CrankPermutation*	p	);


void		crank_permutation_init_vala_compare_parray (	const guint			n,
													gpointer*			garr,
													GCompareFunc		gcmp,
													CrankPermutation*	p	);

void		crank_permutation_init_vala_compare_parray_data (	const guint			n,
															gpointer*			garr,
															GCompareDataFunc	gcmp,
															gpointer			userdata,
															CrankPermutation*	p	);


gpointer*	crank_permutation_vala_shuffle_parray (	CrankPermutation*	p,
													gpointer*			arr,
													guint*				rn	);

gboolean*	crank_permutation_vala_shuffle_array_boolean (	CrankPermutation*	p,
														gboolean*			arr,
														guint*				rn	);

gint*		crank_permutation_vala_shuffle_array_int (	CrankPermutation*	p,
														gint*				arr,
														guint*				rn	);

gfloat*		crank_permutation_vala_shuffle_array_float (	CrankPermutation*	p,
														gfloat*				arr,
														guint*				rn	);


G_END_DECLS

#endif 
