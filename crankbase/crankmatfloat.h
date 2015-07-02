#ifndef CRANKMATFLOAT_H
#define CRANKMATFLOAT_H

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
#include "crankveccommon.h"

G_BEGIN_DECLS

/**
 * CrankMatFloat2:
 * @m00: A Matrix element.
 * @m01: A Matrix element.
 * @m10: A Matrix element.
 * @m11: A Matrix element.
 *
 * 2x2 Float Matrix.
 */
struct _CrankMatFloat2 {
	gfloat	m00;
	gfloat	m01;
	gfloat	m10;
	gfloat	m11;
};

#define CRANK_TYPE_MAT_FLOAT2	(crank_mat_float2_get_type ())
GType			crank_mat_float2_get_type	(void);

/**
 * CRANK_MAT_FLOAT2_0:
 *
 * A zero matrix.
 */
#define CRANK_MAT_FLOAT2_0	{0.0f, 0.0f, 0.0f, 0.0f}

/**
 * CRANK_MAT_FLOAT2_I:
 *
 * A identity matrix.
 */
#define CRANK_MAT_FLOAT2_I	{1.0f, 0.0f, 0.0f, 1.0f}


void		crank_mat_float2_init (	CrankMatFloat2*	mat,
									const gfloat	m00,
									const gfloat	m01,
									const gfloat	m10,
									const gfloat	m11	);

void		crank_mat_float2_init_arr (	CrankMatFloat2*	mat,
										const gfloat*	marr	);

void		crank_mat_float2_init_rv (	CrankMatFloat2*	mat,
										CrankVecFloat2*	rv0,
										CrankVecFloat2* rv1	);

void		crank_mat_float2_init_rvarr (	CrankMatFloat2*		mat,
											CrankVecFloat2**	rvarr	);

void		crank_mat_float2_init_cv (	CrankMatFloat2*			mat,
										CrankVecFloat2*			cv0,
										CrankVecFloat2*			cv1	);

void		crank_mat_float2_init_cvarr (	CrankMatFloat2*			mat,
											CrankVecFloat2**		cvarr );

void		crank_mat_float2_init_diag (	CrankMatFloat2*	mat,
											const gfloat	m00,
											const gfloat	m11	);

void		crank_mat_float2_init_diag_arr (	CrankMatFloat2*	mat,
												const gfloat*	darr	);

void		crank_mat_float2_init_fill (	CrankMatFloat2* mat,
								  			const gfloat	fill	);

void		crank_mat_float2_copy (			CrankMatFloat2*	mat,
							 				CrankMatFloat2*	other	);

CrankMatFloat2*	crank_mat_float2_dup (	CrankMatFloat2*	mat	);

//////// Basic operations ////////

guint		crank_mat_float2_hash (	gconstpointer	a	);

gboolean	crank_mat_float2_equal (	gconstpointer	a,
										gconstpointer	b	);

gchar*		crank_mat_float2_to_string (	CrankMatFloat2*	mat	);

gchar*		crank_mat_float2_to_string_full (	CrankMatFloat2*	mat,
												const gchar*	mat_left,
												const gchar*	mat_in,
												const gchar*	mat_right,
												const gchar*	row_left,
												const gchar*	row_in,
												const gchar*	row_right,
												const gchar*	format	);

//////// Collectional functions ////////

gfloat		crank_mat_float2_get (		CrankMatFloat2*	mat,
										const guint		i,
										const guint		j	);

void		crank_mat_float2_set (		CrankMatFloat2*	mat,
										const guint		i,
										const guint		j,
										const gfloat	value	);

void		crank_mat_float2_get_row (	CrankMatFloat2*	mat,
										guint			index,
										CrankVecFloat2*	row		);

void		crank_mat_float2_set_row (	CrankMatFloat2*	mat,
										guint			index,
										CrankVecFloat2*	row		);

void		crank_mat_float2_get_col (	CrankMatFloat2*	mat,
										guint			index,
										CrankVecFloat2*	col		);

void		crank_mat_float2_set_col (	CrankMatFloat2*	mat,
										guint			index,
										CrankVecFloat2*	col		);


//////// Property of matrices ////////

gfloat		crank_mat_float2_get_tr (	CrankMatFloat2*	mat	);

gfloat		crank_mat_float2_get_det (	CrankMatFloat2*	mat	);

void		crank_mat_float2_get_cof (	CrankMatFloat2*	mat,
										CrankMatFloat2*	r	);

void		crank_mat_float2_get_adj (	CrankMatFloat2*	mat,
										CrankMatFloat2*	r	);

//////// Unary operations ////////

void		crank_mat_float2_neg (	CrankMatFloat2*	a,
									CrankMatFloat2*	r	);

void		crank_mat_float2_transpose (	CrankMatFloat2*	a,
											CrankMatFloat2*	r	);

void		crank_mat_float2_inverse (	CrankMatFloat2*	a,
										CrankMatFloat2*	r	);

//////// Scalar operations ////////

void		crank_mat_float2_muls (	CrankMatFloat2*	a,
									const gfloat	b,
									CrankMatFloat2*	r	);

void		crank_mat_float2_divs (	CrankMatFloat2*	a,
									const gfloat	b,
									CrankMatFloat2*	r	);

//////// Vector operations ////////

void		crank_mat_float2_mulv (	CrankMatFloat2*	a,
									CrankVecFloat2*	b,
									CrankVecFloat2*	r	);

//////// Matrix operations ////////

void		crank_mat_float2_mul (	CrankMatFloat2*	a,
									CrankMatFloat2*	b,
									CrankMatFloat2* r	);

//////// Ternary operaions ////////

void		crank_mat_float2_mixs (	CrankMatFloat2*	a,
									CrankMatFloat2*	b,
									const gfloat	c,
									CrankMatFloat2*	r	);

void		crank_mat_float2_mix (	CrankMatFloat2*	a,
									CrankMatFloat2*	b,
									CrankMatFloat2*	c,
									CrankMatFloat2*	r	);

G_END_DECLS

#endif //CRANKMATFLOAT_H
