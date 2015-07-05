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





/**
 * CrankMatFloat3:
 * @m00: A Matrix element.
 * @m01: A Matrix element.
 * @m02: A Matrix element.
 * @m10: A Matrix element.
 * @m11: A Matrix element.
 * @m12: A Matrix element.
 * @m20: A Matrix element.
 * @m21: A Matrix element.
 * @m22: A Matrix element.
 *
 * 3x3 Float Matrix.
 */
struct _CrankMatFloat3 {
	gfloat	m00;
	gfloat	m01;
  	gfloat	m02;
	gfloat	m10;
	gfloat	m11;
  	gfloat	m12;
  	gfloat	m20;
  	gfloat	m21;
  	gfloat	m22;
};

#define CRANK_TYPE_MAT_FLOAT3	(crank_mat_float3_get_type ())
GType			crank_mat_float3_get_type	(void);

/**
 * CRANK_MAT_FLOAT3_0:
 *
 * A zero matrix.
 */
#define CRANK_MAT_FLOAT3_0	{\
	0.0f, 0.0f, 0.0f, \
  	0.0f, 0.0f, 0.0f, \
  	0.0f, 0.0f, 0.0f}

/**
 * CRANK_MAT_FLOAT3_I:
 *
 * A identity matrix.
 */
#define CRANK_MAT_FLOAT3_I	{\
  	1.0f, 0.0f, 0.0f,\
  	0.0f, 1.0f, 0.0f,\
  	0.0f, 0.0f, 1.0f}


void		crank_mat_float3_init (	CrankMatFloat3*	mat,
									const gfloat	m00,
									const gfloat	m01,
							 		const gfloat	m02,
									const gfloat	m10,
									const gfloat	m11,
							 		const gfloat	m12,
							 		const gfloat	m20,
							 		const gfloat	m21,
							 		const gfloat	m22	);

void		crank_mat_float3_init_arr (	CrankMatFloat3*	mat,
										const gfloat*	marr	);

void		crank_mat_float3_init_rv (	CrankMatFloat3*	mat,
										CrankVecFloat3*	rv0,
										CrankVecFloat3* rv1,
										CrankVecFloat3*	rv2	);

void		crank_mat_float3_init_rvarr (	CrankMatFloat3*		mat,
											CrankVecFloat3**	rvarr	);

void		crank_mat_float3_init_cv (	CrankMatFloat3*			mat,
										CrankVecFloat3*			cv0,
										CrankVecFloat3*			cv1,
										CrankVecFloat3*			cv2	);

void		crank_mat_float3_init_cvarr (	CrankMatFloat3*			mat,
											CrankVecFloat3**		cvarr );

void		crank_mat_float3_init_diag (	CrankMatFloat3*	mat,
											const gfloat	m00,
											const gfloat	m11,
								  			const gfloat	m22	);

void		crank_mat_float3_init_diag_arr (	CrankMatFloat3*	mat,
												const gfloat*	darr	);

void		crank_mat_float3_init_fill (	CrankMatFloat3* mat,
								  			const gfloat	fill	);

void		crank_mat_float3_copy (			CrankMatFloat3*	mat,
							 				CrankMatFloat3*	other	);

CrankMatFloat3*	crank_mat_float3_dup (	CrankMatFloat3*	mat	);

//////// Basic operations ////////

guint		crank_mat_float3_hash (		gconstpointer	a	);

gboolean	crank_mat_float3_equal (	gconstpointer	a,
										gconstpointer	b	);

gchar*		crank_mat_float3_to_string (	CrankMatFloat3*	mat	);

gchar*		crank_mat_float3_to_string_full (	CrankMatFloat3*	mat,
												const gchar*	mat_left,
												const gchar*	mat_in,
												const gchar*	mat_right,
												const gchar*	row_left,
												const gchar*	row_in,
												const gchar*	row_right,
												const gchar*	format	);

//////// Collectional functions ////////

gfloat		crank_mat_float3_get (		CrankMatFloat3*	mat,
										const guint		i,
										const guint		j	);

void		crank_mat_float3_set (		CrankMatFloat3*	mat,
										const guint		i,
										const guint		j,
										const gfloat	value	);

void		crank_mat_float3_get_row (	CrankMatFloat3*	mat,
										guint			index,
										CrankVecFloat3*	row		);

void		crank_mat_float3_set_row (	CrankMatFloat3*	mat,
										guint			index,
										CrankVecFloat3*	row		);

void		crank_mat_float3_get_col (	CrankMatFloat3*	mat,
										guint			index,
										CrankVecFloat3*	col		);

void		crank_mat_float3_set_col (	CrankMatFloat3*	mat,
										guint			index,
										CrankVecFloat3*	col		);


//////// Property of matrices ////////

gfloat		crank_mat_float3_get_tr (	CrankMatFloat3*	mat	);

gfloat		crank_mat_float3_get_det (	CrankMatFloat3*	mat	);

void		crank_mat_float3_get_cof (	CrankMatFloat3*	mat,
										CrankMatFloat3*	r	);

void		crank_mat_float3_get_adj (	CrankMatFloat3*	mat,
										CrankMatFloat3*	r	);

//////// Unary operations ////////

void		crank_mat_float3_neg (	CrankMatFloat3*	a,
									CrankMatFloat3*	r	);

void		crank_mat_float3_transpose (	CrankMatFloat3*	a,
											CrankMatFloat3*	r	);

void		crank_mat_float3_inverse (	CrankMatFloat3*	a,
										CrankMatFloat3*	r	);

//////// Scalar operations ////////

void		crank_mat_float3_muls (	CrankMatFloat3*	a,
									const gfloat	b,
									CrankMatFloat3*	r	);

void		crank_mat_float3_divs (	CrankMatFloat3*	a,
									const gfloat	b,
									CrankMatFloat3*	r	);

//////// Vector operations ////////

void		crank_mat_float3_mulv (	CrankMatFloat3*	a,
									CrankVecFloat3*	b,
									CrankVecFloat3*	r	);

//////// Matrix operations ////////

void		crank_mat_float3_mul (	CrankMatFloat3*	a,
									CrankMatFloat3*	b,
									CrankMatFloat3* r	);

//////// Ternary operaions ////////

void		crank_mat_float3_mixs (	CrankMatFloat3*	a,
									CrankMatFloat3*	b,
									const gfloat	c,
									CrankMatFloat3*	r	);

void		crank_mat_float3_mix (	CrankMatFloat3*	a,
									CrankMatFloat3*	b,
									CrankMatFloat3*	c,
									CrankMatFloat3*	r	);






/**
 * CrankMatFloat4:
 * @m00: A Matrix element.
 * @m01: A Matrix element.
 * @m02: A Matrix element.
 * @m03: A Matrix element.
 * @m10: A Matrix element.
 * @m11: A Matrix element.
 * @m12: A Matrix element.
 * @m13: A Matrix element.
 * @m20: A Matrix element.
 * @m21: A Matrix element.
 * @m22: A Matrix element.
 * @m23: A Matrix element.
 * @m30: A Matrix element.
 * @m31: A Matrix element.
 * @m32: A Matrix element.
 * @m33: A Matrix element.
 *
 * 4x4 Float Matrix.
 */
struct _CrankMatFloat4 {
	gfloat	m00;
	gfloat	m01;
  	gfloat	m02;
  	gfloat	m03;
	gfloat	m10;
	gfloat	m11;
  	gfloat	m12;
  	gfloat	m13;
  	gfloat	m20;
  	gfloat	m21;
  	gfloat	m22;
  	gfloat	m23;
  	gfloat	m30;
  	gfloat	m31;
  	gfloat	m32;
  	gfloat	m33;
};

#define CRANK_TYPE_MAT_FLOAT4	(crank_mat_float4_get_type ())
GType			crank_mat_float4_get_type	(void);

/**
 * CRANK_MAT_FLOAT4_0:
 *
 * A zero matrix.
 */
#define CRANK_MAT_FLOAT4_0	{\
	0.0f, 0.0f, 0.0f, 0.0f, \
  	0.0f, 0.0f, 0.0f, 0.0f, \
  	0.0f, 0.0f, 0.0f, 0.0f, \
  	0.0f, 0.0f, 0.0f, 0.0f}

/**
 * CRANK_MAT_FLOAT4_I:
 *
 * A identity matrix.
 */
#define CRANK_MAT_FLOAT4_I	{\
  	1.0f, 0.0f, 0.0f, 0.0f, \
  	0.0f, 1.0f, 0.0f, 0.0f, \
  	0.0f, 0.0f, 1.0f, 0.0f, \
  	0.0f, 0.0f, 0.0f, 1.0f}


void		crank_mat_float4_init (	CrankMatFloat4*	mat,
									const gfloat	m00,
									const gfloat	m01,
							 		const gfloat	m02,
							 		const gfloat	m03,
									const gfloat	m10,
									const gfloat	m11,
							 		const gfloat	m12,
							 		const gfloat	m13,
							 		const gfloat	m20,
							 		const gfloat	m21,
							 		const gfloat	m22,
							 		const gfloat	m23,
							 		const gfloat	m30,
							 		const gfloat	m31,
							 		const gfloat	m32,
							 		const gfloat	m33	);

void		crank_mat_float4_init_arr (	CrankMatFloat4*	mat,
										const gfloat*	marr	);

void		crank_mat_float4_init_rv (	CrankMatFloat4*	mat,
										CrankVecFloat4*	rv0,
										CrankVecFloat4* rv1,
										CrankVecFloat4*	rv2,
										CrankVecFloat4*	rv3	);

void		crank_mat_float4_init_rvarr (	CrankMatFloat4*		mat,
											CrankVecFloat4**	rvarr	);

void		crank_mat_float4_init_cv (	CrankMatFloat4*			mat,
										CrankVecFloat4*			cv0,
										CrankVecFloat4*			cv1,
										CrankVecFloat4*			cv2,
										CrankVecFloat4*			cv3	);

void		crank_mat_float4_init_cvarr (	CrankMatFloat4*			mat,
											CrankVecFloat4**		cvarr );

void		crank_mat_float4_init_diag (	CrankMatFloat4*	mat,
											const gfloat	m00,
											const gfloat	m11,
								  			const gfloat	m22,
								  			const gfloat	m33	);

void		crank_mat_float4_init_diag_arr (	CrankMatFloat4*	mat,
												const gfloat*	darr	);

void		crank_mat_float4_init_fill (	CrankMatFloat4* mat,
								  			const gfloat	fill	);

void		crank_mat_float4_copy (			CrankMatFloat4*	mat,
							 				CrankMatFloat4*	other	);

CrankMatFloat4*	crank_mat_float4_dup (	CrankMatFloat4*	mat	);

//////// Basic operations ////////

guint		crank_mat_float4_hash (		gconstpointer	a	);

gboolean	crank_mat_float4_equal (	gconstpointer	a,
										gconstpointer	b	);

gchar*		crank_mat_float4_to_string (	CrankMatFloat4*	mat	);

gchar*		crank_mat_float4_to_string_full (	CrankMatFloat4*	mat,
												const gchar*	mat_left,
												const gchar*	mat_in,
												const gchar*	mat_right,
												const gchar*	row_left,
												const gchar*	row_in,
												const gchar*	row_right,
												const gchar*	format	);

//////// Collectional functions ////////

gfloat		crank_mat_float4_get (		CrankMatFloat4*	mat,
										const guint		i,
										const guint		j	);

void		crank_mat_float4_set (		CrankMatFloat4*	mat,
										const guint		i,
										const guint		j,
										const gfloat	value	);

void		crank_mat_float4_get_row (	CrankMatFloat4*	mat,
										guint			index,
										CrankVecFloat4*	row		);

void		crank_mat_float4_set_row (	CrankMatFloat4*	mat,
										guint			index,
										CrankVecFloat4*	row		);

void		crank_mat_float4_get_col (	CrankMatFloat4*	mat,
										guint			index,
										CrankVecFloat4*	col		);

void		crank_mat_float4_set_col (	CrankMatFloat4*	mat,
										guint			index,
										CrankVecFloat4*	col		);


//////// Property of matrices ////////

gfloat		crank_mat_float4_get_tr (	CrankMatFloat4*	mat	);

gfloat		crank_mat_float4_get_det (	CrankMatFloat4*	mat	);

void		crank_mat_float4_get_cof (	CrankMatFloat4*	mat,
										CrankMatFloat4*	r	);

void		crank_mat_float4_get_adj (	CrankMatFloat4*	mat,
										CrankMatFloat4*	r	);

//////// Unary operations ////////

void		crank_mat_float4_neg (	CrankMatFloat4*	a,
									CrankMatFloat4*	r	);

void		crank_mat_float4_transpose (	CrankMatFloat4*	a,
											CrankMatFloat4*	r	);

void		crank_mat_float4_inverse (	CrankMatFloat4*	a,
										CrankMatFloat4*	r	);

//////// Scalar operations ////////

void		crank_mat_float4_muls (	CrankMatFloat4*	a,
									const gfloat	b,
									CrankMatFloat4*	r	);

void		crank_mat_float4_divs (	CrankMatFloat4*	a,
									const gfloat	b,
									CrankMatFloat4*	r	);

//////// Vector operations ////////

void		crank_mat_float4_mulv (	CrankMatFloat4*	a,
									CrankVecFloat4*	b,
									CrankVecFloat4*	r	);

//////// Matrix operations ////////

void		crank_mat_float4_mul (	CrankMatFloat4*	a,
									CrankMatFloat4*	b,
									CrankMatFloat4* r	);

//////// Ternary operaions ////////

void		crank_mat_float4_mixs (	CrankMatFloat4*	a,
									CrankMatFloat4*	b,
									const gfloat	c,
									CrankMatFloat4*	r	);

void		crank_mat_float4_mix (	CrankMatFloat4*	a,
									CrankMatFloat4*	b,
									CrankMatFloat4*	c,
									CrankMatFloat4*	r	);






/**
 * CrankMatFloatN:
 * @data: Matrix data array.
 * @rn: row count.
 * @cn: column count.
 *
 * Variable sized Float Matrix.
 */
struct _CrankMatFloatN {
	gfloat*		data;
	guint		rn;
	guint		cn;
};

#define CRANK_TYPE_MAT_FLOAT_N	(crank_mat_float_n_get_type ())
GType			crank_mat_float_n_get_type	(void);


void		crank_mat_float_n_init (	CrankMatFloatN*	mat,
										const guint		rn,
										const guint		cn,
										...);

void		crank_mat_float_n_init_arr (	CrankMatFloatN*	mat,
										const guint			rn,
										const guint			cn,
										const gfloat*		marr	);

void		crank_mat_float_n_init_arr_take (	CrankMatFloatN*	mat,
									   			const guint		rn,
									   			const guint		cn,
									   			gfloat*	marr	);

void		crank_mat_float_n_init_rv (	CrankMatFloatN*	mat,
										const guint		rn,
										...	);

void		crank_mat_float_n_init_rvarr (	CrankMatFloatN*		mat,
											const guint 		rn,
											CrankVecFloatN**	rvarr	);

void		crank_mat_float_n_init_cv (	CrankMatFloatN*			mat,
										const guint				cn,
										...);

void		crank_mat_float_n_init_cvarr (	CrankMatFloatN*			mat,
											const guint				cn,
											CrankVecFloatN**		cvarr );

void		crank_mat_float_n_init_diag (	CrankMatFloatN*	mat,
											const guint		n,
											...	);

void		crank_mat_float_n_init_diag_arr (	CrankMatFloatN*	mat,
												const guint		n,
												const gfloat*	darr	);

void		crank_mat_float_n_init_fill (	CrankMatFloatN* mat,
											const guint		rn,
											const guint		cn,
								  			const gfloat	fill	);

void		crank_mat_float_n_fini (	CrankMatFloatN*	mat	);

void		crank_mat_float_n_copy (			CrankMatFloatN*	mat,
							 				CrankMatFloatN*	other	);

CrankMatFloatN*	crank_mat_float_n_dup (	CrankMatFloatN*	mat	);

void		crank_mat_float_n_free (	CrankMatFloatN*	mat	);

//////// Basic operations ////////

guint		crank_mat_float_n_hash (		gconstpointer	a	);

gboolean	crank_mat_float_n_equal (	gconstpointer	a,
										gconstpointer	b	);

gchar*		crank_mat_float_n_to_string (	CrankMatFloatN*	mat	);

gchar*		crank_mat_float_n_to_string_full (	CrankMatFloatN*	mat,
												const gchar*	mat_left,
												const gchar*	mat_in,
												const gchar*	mat_right,
												const gchar*	row_left,
												const gchar*	row_in,
												const gchar*	row_right,
												const gchar*	format	);

//////// Collectional functions ////////

guint		crank_mat_float_n_get_row_size (	CrankMatFloatN* mat	);

guint		crank_mat_float_n_get_col_size (	CrankMatFloatN* mat	);

gfloat		crank_mat_float_n_get (		CrankMatFloatN*	mat,
										const guint		i,
										const guint		j	);

void		crank_mat_float_n_set (		CrankMatFloatN*	mat,
										const guint		i,
										const guint		j,
										const gfloat	value	);

void		crank_mat_float_n_get_row (	CrankMatFloatN*	mat,
										guint			index,
										CrankVecFloatN*	row		);

void		crank_mat_float_n_set_row (	CrankMatFloatN*	mat,
										guint			index,
										CrankVecFloatN*	row		);

void		crank_mat_float_n_get_col (	CrankMatFloatN*	mat,
										guint			index,
										CrankVecFloatN*	col		);

void		crank_mat_float_n_set_col (	CrankMatFloatN*	mat,
										guint			index,
										CrankVecFloatN*	col		);


//////// Property of matrices ////////

gboolean	crank_mat_float_n_is_square (	CrankMatFloatN*	mat	);

gfloat		crank_mat_float_n_get_tr (	CrankMatFloatN*	mat	);

gfloat		crank_mat_float_n_get_det (	CrankMatFloatN*	mat	);

void		crank_mat_float_n_get_cof (	CrankMatFloatN*	mat,
										CrankMatFloatN*	r	);

void		crank_mat_float_n_get_adj (	CrankMatFloatN*	mat,
										CrankMatFloatN*	r	);

//////// Unary operations ////////

void		crank_mat_float_n_neg (	CrankMatFloatN*	a,
									CrankMatFloatN*	r	);

void		crank_mat_float_n_transpose (	CrankMatFloatN*	a,
											CrankMatFloatN*	r	);

void		crank_mat_float_n_inverse (	CrankMatFloatN*	a,
										CrankMatFloatN*	r	);

//////// Scalar operations ////////

void		crank_mat_float_n_muls (	CrankMatFloatN*	a,
									const gfloat	b,
									CrankMatFloatN*	r	);

void		crank_mat_float_n_divs (	CrankMatFloatN*	a,
									const gfloat	b,
									CrankMatFloatN*	r	);

//////// Vector operations ////////

void		crank_mat_float_n_mulv (	CrankMatFloatN*	a,
									CrankVecFloatN*	b,
									CrankVecFloatN*	r	);

//////// Matrix operations ////////

void		crank_mat_float_n_mul (	CrankMatFloatN*	a,
									CrankMatFloatN*	b,
									CrankMatFloatN* r	);

//////// Ternary operaions ////////

void		crank_mat_float_n_mixs (	CrankMatFloatN*	a,
									CrankMatFloatN*	b,
									const gfloat	c,
									CrankMatFloatN*	r	);

void		crank_mat_float_n_mix (	CrankMatFloatN*	a,
									CrankMatFloatN*	b,
									CrankMatFloatN*	c,
									CrankMatFloatN*	r	);

G_END_DECLS

#endif //CRANKMATFLOAT_H
