#ifndef CRANKMATCPLXFLOAT_H
#define CRANKMATCPLXFLOAT_H

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
#error crankmatfloat.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankpermutation.h"
#include "crankcomplex.h"
#include "crankveccommon.h"

G_BEGIN_DECLS

/**
 * CrankMatCplxFloatN:
 * @data: Matrix data array.
 * @rn: row count.
 * @cn: column count.
 *
 * Variable sized Float Matrix.
 */
struct _CrankMatCplxFloatN {
	CrankCplxFloat*	data;
	guint			rn;
	guint			cn;
};

#define CRANK_TYPE_MAT_CPLX_FLOAT_N	(crank_mat_cplx_float_n_get_type ())
GType			crank_mat_cplx_float_n_get_type	(void);


void		crank_mat_cplx_float_n_init (	CrankMatCplxFloatN*	mat,
											const guint		rn,
											const guint		cn,
											...);

void		crank_mat_cplx_float_n_init_arr (	CrankMatCplxFloatN*	mat,
												const guint			rn,
												const guint			cn,
												CrankCplxFloat*		marr	);

void		crank_mat_cplx_float_n_init_arr_take (	CrankMatCplxFloatN*	mat,
										   			const guint			rn,
										   			const guint			cn,
										   			CrankCplxFloat*		marr	);

void		crank_mat_cplx_float_n_init_row (	CrankMatCplxFloatN*	mat,
												const guint		rn,
												...	);

void		crank_mat_cplx_float_n_init_row_arr (	CrankMatCplxFloatN*		mat,
												const guint 			rn,
												CrankVecCplxFloatN*		rarrv	);

void		crank_mat_cplx_float_n_init_row_parr (	CrankMatCplxFloatN*		mat,
													const guint 			rn,
													CrankVecCplxFloatN**	rparrv	);

void		crank_mat_cplx_float_n_init_col (	CrankMatCplxFloatN*			mat,
												const guint				cn,
												...);

void		crank_mat_cplx_float_n_init_col_arr (	CrankMatCplxFloatN*		mat,
												const guint				cn,
												CrankVecCplxFloatN*		carrv );

void		crank_mat_cplx_float_n_init_col_parr (	CrankMatCplxFloatN*		mat,
													const guint				cn,
													CrankVecCplxFloatN**	cparrv );

void		crank_mat_cplx_float_n_init_diag (	CrankMatCplxFloatN*	mat,
												const guint			n,
												...	);

void		crank_mat_cplx_float_n_init_diag_arr (	CrankMatCplxFloatN*	mat,
													const guint			n,
													CrankCplxFloat*		darr	);

void		crank_mat_cplx_float_n_init_diag_vec (	CrankMatCplxFloatN*	mat,
									   				CrankVecCplxFloatN*	dvec	);

void		crank_mat_cplx_float_n_init_fill (	CrankMatCplxFloatN* mat,
												const guint			rn,
												const guint			cn,
									  			CrankCplxFloat*		fill	);



void		crank_mat_cplx_float_n_init_uc (	CrankMatCplxFloatN*	mat,
												const guint			rn,
												const guint			cn,
												...	);
void		crank_mat_cplx_float_n_init_arruc (CrankMatCplxFloatN*	mat,
											   const guint			rn,
										 	   const guint			cn,
										       const gfloat*		mucarr	);

void		crank_mat_cplx_float_n_init_ucarr(	CrankMatCplxFloatN*	mat,
												const guint			rn,
												const guint			cn,
												const gfloat*		real,
												const gfloat*		imag	);

void		crank_mat_cplx_float_n_init_ucm(CrankMatCplxFloatN* mat,
									  		CrankMatFloatN*		real,
									  		CrankMatFloatN*		imag);

void		crank_mat_cplx_float_n_init_row_uc (CrankMatCplxFloatN* mat,
											  const guint		  rn,
											  ...);

void		crank_mat_cplx_float_n_init_row_arruc (CrankMatCplxFloatN* mat,
												  const guint		  rn,
												  CrankVecFloatN*	  rarrucv);

void		crank_mat_cplx_float_n_init_row_parruc (CrankMatCplxFloatN* mat,
												  const guint		  rn,
												  CrankVecFloatN**	  rarrucpv);

void		crank_mat_cplx_float_n_init_col_uc (CrankMatCplxFloatN* mat,
											  const guint		  cn,
											  ...);

void		crank_mat_cplx_float_n_init_col_arruc (CrankMatCplxFloatN* mat,
												  const guint		  cn,
												  CrankVecFloatN*	  carrucv);

void		crank_mat_cplx_float_n_init_col_parruc (CrankMatCplxFloatN* mat,
												  const guint		  cn,
												  CrankVecFloatN**	  carrucpv);

void		crank_mat_cplx_float_n_init_diag_uc (CrankMatCplxFloatN*	mat,
										  		const guint			n,
										  		... );

void		crank_mat_cplx_float_n_init_diag_arruc (CrankMatCplxFloatN*	mat,
											 	   const guint			n,
											 	   const gfloat*		arruc);

void		crank_mat_cplx_float_n_init_diag_ucarr (CrankMatCplxFloatN*	mat,
											 		const guint			n,
											 		const gfloat*		real,
											 		const gfloat*		imag);

void		crank_mat_cplx_float_n_init_diag_ucv (CrankMatCplxFloatN*	mat,
										   		 CrankVecFloatN*		real,
										   	     CrankVecFloatN*		imag);

void		crank_mat_cplx_float_n_init_fill_uc (CrankMatCplxFloatN* mat,
										  		const guint			rn,
										  		const guint			cn,
										  		const gfloat		real,
										  		const gfloat		imag);


void		crank_mat_cplx_float_n_fini (	CrankMatCplxFloatN*	mat	);

void		crank_mat_cplx_float_n_copy (	CrankMatCplxFloatN*	mat,
							 				CrankMatCplxFloatN*	other	);

CrankMatCplxFloatN*	crank_mat_cplx_float_n_dup (	CrankMatCplxFloatN*	mat	);

void		crank_mat_cplx_float_n_free (	CrankMatCplxFloatN*	mat	);

//////// Basic operations ////////

guint		crank_mat_cplx_float_n_hash (		gconstpointer	a	);

gboolean	crank_mat_cplx_float_n_equal (	gconstpointer	a,
										gconstpointer	b	);

gchar*		crank_mat_cplx_float_n_to_string (	CrankMatCplxFloatN*	mat	);

gchar*		crank_mat_cplx_float_n_to_string_full (	CrankMatCplxFloatN*	mat,
													const gchar*	mat_left,
													const gchar*	mat_in,
													const gchar*	mat_right,
													const gchar*	row_left,
													const gchar*	row_in,
													const gchar*	row_right,
													const gchar*	format	);

//////// Collectional functions ////////

guint		crank_mat_cplx_float_n_get_row_size (	CrankMatCplxFloatN* mat	);

guint		crank_mat_cplx_float_n_get_col_size (	CrankMatCplxFloatN* mat	);

void		crank_mat_cplx_float_n_get (		CrankMatCplxFloatN*	mat,
												const guint			i,
												const guint			j,
												CrankCplxFloat*		value	);

void		crank_mat_cplx_float_n_set (		CrankMatCplxFloatN*	mat,
												const guint			i,
												const guint			j,
												CrankCplxFloat*		value	);

CrankCplxFloat*	crank_mat_cplx_float_n_peek (	CrankMatCplxFloatN*	mat,
												const guint			i,
												const guint			j	);

void		crank_mat_cplx_float_n_get_row (	CrankMatCplxFloatN*	mat,
												const guint			index,
												CrankVecCplxFloatN*	row		);

void		crank_mat_cplx_float_n_set_row (	CrankMatCplxFloatN*	mat,
												const guint			index,
												CrankVecCplxFloatN*	row		);

void		crank_mat_cplx_float_n_set_row_real(CrankMatCplxFloatN* mat,
												const guint			index,
												CrankVecFloatN* 	row_real);

void		crank_mat_cplx_float_n_set_row_imag(CrankMatCplxFloatN* mat,
												const guint			index,
												CrankVecFloatN* 	row_imag);

void		crank_mat_cplx_float_n_get_col (	CrankMatCplxFloatN*	mat,
												const guint		index,
												CrankVecCplxFloatN*	col		);

void		crank_mat_cplx_float_n_set_col (	CrankMatCplxFloatN*	mat,
												const guint			index,
												CrankVecCplxFloatN*	col		);

void		crank_mat_cplx_float_n_set_col_real(CrankMatCplxFloatN* mat,
												const guint			index,
												CrankVecFloatN* 	col_real);

void		crank_mat_cplx_float_n_set_col_imag(CrankMatCplxFloatN* mat,
												const guint			index,
												CrankVecFloatN* 	col_imag);

void		crank_mat_cplx_float_n_slice_row (	CrankMatCplxFloatN*	mat,
												const guint			start,
												const guint			end,
												CrankMatCplxFloatN*	r		);
										
void		crank_mat_cplx_float_n_slice_col (	CrankMatCplxFloatN*	mat,
												const guint			start,
												const guint			end,
												CrankMatCplxFloatN*		r		);

void		crank_mat_cplx_float_n_slice (	CrankMatCplxFloatN*	mat,
											const guint		row_start,
											const guint		col_start,
											const guint		row_end,
											const guint		col_end,
											CrankMatCplxFloatN*	r		);


//////// Classification ////////////////////////////////////////////////////////

gboolean	crank_mat_cplx_float_n_is_square (	CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_is_identity(	CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_is_zero (	CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_is_upper_tri(CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_is_lower_tri(CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_is_diag (	CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_is_symmetric(CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_is_hermitian(CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_has_nan (	CrankMatCplxFloatN* mat	);

gboolean	crank_mat_cplx_float_n_has_inf (	CrankMatCplxFloatN* mat	);

gboolean	crank_mat_cplx_float_n_is_pure_real(CrankMatCplxFloatN*	mat	);

gboolean	crank_mat_cplx_float_n_is_pure_imag(CrankMatCplxFloatN*	mat	);

//////// Attributes ////////////////////////////////////////////////////////////

void		crank_mat_cplx_float_n_get_tr (	CrankMatCplxFloatN*	mat,
											CrankCplxFloat*		tr	);

void		crank_mat_cplx_float_n_get_det (	CrankMatCplxFloatN*	mat,
												CrankCplxFloat*		det	);

void		crank_mat_cplx_float_n_get_cof (	CrankMatCplxFloatN*	mat,
												CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_get_adj (	CrankMatCplxFloatN*	mat,
												CrankMatCplxFloatN*	r	);
										
void		crank_mat_cplx_float_n_get_diag (	CrankMatCplxFloatN*	mat,
												CrankVecCplxFloatN*	r	);


void		crank_mat_cplx_float_n_get_real (	CrankMatCplxFloatN*	mat,
												CrankMatFloatN*		r	);

void		crank_mat_cplx_float_n_get_imag (	CrankMatCplxFloatN*	mat,
												CrankMatFloatN*		r	);


void		crank_mat_cplx_float_n_set_real (	CrankMatCplxFloatN*	mat,
												CrankMatFloatN*		r	);

void		crank_mat_cplx_float_n_set_imag (	CrankMatCplxFloatN*	mat,
												CrankMatFloatN*		r	);

//////// Unary operations ////////

void		crank_mat_cplx_float_n_neg (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_neg_self (	CrankMatCplxFloatN*	a	);

void		crank_mat_cplx_float_n_transpose (	CrankMatCplxFloatN*	a,
												CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_transpose_self (	CrankMatCplxFloatN*	a	);

void		crank_mat_cplx_float_n_inverse (	CrankMatCplxFloatN*	a,
												CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_inverse_self (	CrankMatCplxFloatN*	a	);

gboolean	crank_mat_cplx_float_n_try_inverse (	CrankMatCplxFloatN*	a,
													CrankMatCplxFloatN*	r	);
	
gboolean	crank_mat_cplx_float_n_try_inverse_self (	CrankMatCplxFloatN*	a	);
											

void		crank_mat_cplx_float_n_conjugate (	CrankMatCplxFloatN*	a,
												CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_conjugate_self (	CrankMatCplxFloatN*	a	);

void		crank_mat_cplx_float_n_star (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_star_self (	CrankMatCplxFloatN*	a	);

//////// Scalar operations ////////

void		crank_mat_cplx_float_n_mulrs (	CrankMatCplxFloatN*	a,
											const gfloat	b,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_mulrs_self (	CrankMatCplxFloatN*	a,
												const gfloat		b	);

void		crank_mat_cplx_float_n_muls (	CrankMatCplxFloatN*	a,
											CrankCplxFloat*		b,
											CrankMatCplxFloatN*	r	);
void		crank_mat_cplx_float_n_muls_self (	CrankMatCplxFloatN*	a,
												CrankCplxFloat*		b	);

void		crank_mat_cplx_float_n_mulrv (	CrankMatCplxFloatN*	a,
											CrankVecFloatN*		b,
											CrankVecCplxFloatN*	r	);

void		crank_mat_cplx_float_n_mulv (	CrankMatCplxFloatN*	a,
											CrankVecCplxFloatN*	b,
											CrankVecCplxFloatN*	r	);

void		crank_mat_cplx_float_n_mulr (	CrankMatCplxFloatN*	a,
											CrankMatFloatN*	b,
											CrankMatCplxFloatN* r	);

void		crank_mat_cplx_float_n_mulr_self (	CrankMatCplxFloatN*	a,
												CrankMatFloatN*		b	);

void		crank_mat_cplx_float_n_mul (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	b,
											CrankMatCplxFloatN* r	);

void		crank_mat_cplx_float_n_mul_self (	CrankMatCplxFloatN*	a,
												CrankMatCplxFloatN*	b	);

void		crank_mat_cplx_float_n_divrs (	CrankMatCplxFloatN*	a,
											const gfloat	b,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_divrs_self (	CrankMatCplxFloatN*	a,
												const gfloat		b	);

void		crank_mat_cplx_float_n_divs (	CrankMatCplxFloatN*	a,
											CrankCplxFloat*		b,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_divs_self (	CrankMatCplxFloatN*	a,
												CrankCplxFloat*		b	);


void		crank_mat_cplx_float_n_addr (	CrankMatCplxFloatN*	a,
											CrankMatFloatN*	b,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_addr_self (	CrankMatCplxFloatN*	a,
												CrankMatFloatN*		b	);

void		crank_mat_cplx_float_n_add (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	b,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_add_self (	CrankMatCplxFloatN*	a,
												CrankMatCplxFloatN*	b	);

void		crank_mat_cplx_float_n_subr (	CrankMatCplxFloatN*	a,
											CrankMatFloatN*	b,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_subr_self (	CrankMatCplxFloatN*	a,
												CrankMatFloatN*		b	);

void		crank_mat_cplx_float_n_sub (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	b,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_sub_self (	CrankMatCplxFloatN*	a,
												CrankMatCplxFloatN*	b	);

//////// Ternary operaions ////////

void		crank_mat_cplx_float_n_mixs (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	b,
											const gfloat	c,
											CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_mix (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	b,
											CrankMatFloatN*		c,
											CrankMatCplxFloatN*	r	);
									
//////// Shuffling ////////

void		crank_mat_cplx_float_n_shuffle_row (	CrankMatCplxFloatN*		a,
													CrankPermutation*	p,
													CrankMatCplxFloatN*		r	);

void		crank_mat_cplx_float_n_shuffle_col (	CrankMatCplxFloatN*		a,
													CrankPermutation*	p,
													CrankMatCplxFloatN*		r	);
											

//////// Supplement Operations /////////////////////////////////////////////////

void		crank_mat_cplx_float_n_upper_tri_inverse (	CrankMatCplxFloatN*	a,
														CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_lower_tri_inverse (	CrankMatCplxFloatN*	a,
														CrankMatCplxFloatN*	r	);

void		crank_mat_cplx_float_n_diag_inverse (	CrankMatCplxFloatN*	a,
													CrankMatCplxFloatN*	r	);
											
G_END_DECLS

#endif
