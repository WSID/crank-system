#ifndef CRANKQUATERNION_H
#define CRANKQUATERNION_H

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
#error crankquaternion.h cannot be included directly.
#endif

#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>

#include "crankcomplex.h"
#include "crankveccommon.h"

//////// Struct declaration ////////////////////////////////////////////////////

/**
 * CRANK_QUAT_FLOAT_DEFFORMAT:
 *
 * Default format for crank_quat_float_to_string_full().
 */
#define CRANK_QUAT_FLOAT_DEFFORMAT "%g + (%gi) + (%gj) + (%gk)"

/**
 * CrankQuatFloat:
 * @w: Real part of quaternion.
 * @x: Imaginary part of quaternion.
 * @y: Imaginary part of quaternion.
 * @z: Imaginary part of quaternion.
 *
 * Represents a float complex value
 */
typedef struct _CrankQuatFloat {
	gfloat	w;
	gfloat	x;
	gfloat	y;
	gfloat	z;
} CrankQuatFloat;

GType		crank_quat_float_get_type (void);

#define CRANK_TYPE_QUAT_FLOAT (crank_quat_float_get_type())


//////// Initialization ////////////////////////////////////////////////////////

void		crank_quat_float_init (			CrankQuatFloat*	quat,
											gfloat			w,
											gfloat			x,
											gfloat			y,
											gfloat			z	);

void		crank_quat_float_init_cplx (	CrankQuatFloat*	quat,
											CrankCplxFloat*	wx,
											CrankCplxFloat*	yz	);

void		crank_quat_float_init_arr (		CrankQuatFloat*	quat,
											gfloat*			parts	);

void		crank_quat_float_init_valist (	CrankQuatFloat*	quat,
											va_list			varargs	);

void		crank_quat_float_init_valist_cplx (	CrankQuatFloat*	quat,
												va_list			varargs	);

void		crank_quat_float_init_fill (	CrankQuatFloat*	quat,
											gfloat			fill	);

void		crank_quat_float_init_rot 	(	CrankQuatFloat*	quat,
											const gfloat	angle,
											CrankVecFloat3*	axis	);

void		crank_quat_float_init_rotimm (	CrankQuatFloat*	quat,
											const gfloat	angle,
											const gfloat	x,
											const gfloat	y,
											const gfloat	z		);

//////// Basic Operations //////////////////////////////////////////////////////

void		crank_quat_float_copy (			CrankQuatFloat*	quat,
											CrankQuatFloat*	other	);
									
CrankQuatFloat*	crank_quat_float_dup (		CrankQuatFloat*	quat	);

gboolean	crank_quat_float_equal (		gconstpointer	a,
											gconstpointer	b	);

gboolean	crank_quat_float_equal_delta (	CrankQuatFloat*	a,
											CrankQuatFloat*	b,
											const gfloat	d	);
										
guint		crank_quat_float_hash (			gconstpointer	a	);
										
guint		crank_quat_float_hash1 (		gconstpointer	a	);

gchar*		crank_quat_float_to_string (	CrankQuatFloat*	quat	);

gchar*		crank_quat_float_to_string_full (	CrankQuatFloat*	quat,
												const gchar*	format	);
												
//////// Classification ////////////////////////////////////////////////////////

gboolean	crank_quat_float_is_zero (		CrankQuatFloat* quat	);

gboolean	crank_quat_float_is_one (		CrankQuatFloat* quat	);

gboolean	crank_quat_float_is_unit (		CrankQuatFloat* quat	);

gboolean	crank_quat_float_is_pure_real (	CrankQuatFloat* quat	);

gboolean	crank_quat_float_is_pure_imag (	CrankQuatFloat* quat	);

gboolean	crank_quat_float_has_nan (		CrankQuatFloat*	quat	);

gboolean	crank_quat_float_has_inf (		CrankQuatFloat*	quat	);

//////// Attributes ////////////////////////////////////////////////////////////

void		crank_quat_float_get_wx (		CrankQuatFloat*	quat,
											CrankCplxFloat*	wx	);
											
void		crank_quat_float_get_yz (		CrankQuatFloat*	quat,
											CrankCplxFloat*	yz	);

void		crank_quat_float_get_imag (		CrankQuatFloat*	quat,
											CrankVecFloat3*	imag	);

gfloat		crank_quat_float_get_rangle (	CrankQuatFloat*	quat	);

void		crank_quat_float_get_raxis (	CrankQuatFloat*	quat,
											CrankVecFloat3*	axis	);
											
void		crank_quat_float_set_wx (		CrankQuatFloat*	quat,
											CrankCplxFloat*	wx	);
											
void		crank_quat_float_set_yz (		CrankQuatFloat*	quat,
											CrankCplxFloat*	yz	);

void		crank_quat_float_set_imag (		CrankQuatFloat*	quat,
											CrankVecFloat3*	imag	);

gfloat		crank_quat_float_get_norm_sq (	CrankQuatFloat*	quat	);

gfloat		crank_quat_float_get_norm (		CrankQuatFloat*	quat	);
										
void		crank_quat_float_neg (			CrankQuatFloat*	a,

//////// Unary Operations //////////////////////////////////////////////////////
											CrankQuatFloat*	r	);

void		crank_quat_float_inverse (		CrankQuatFloat*	a,
											CrankQuatFloat*	r	);

void		crank_quat_float_conjugate (	CrankQuatFloat*	a,
											CrankQuatFloat*	r	);
											
void		crank_quat_float_unit (			CrankQuatFloat*	a,
											CrankQuatFloat*	r	);
											
										
void		crank_quat_float_neg_self (		CrankQuatFloat*	a	);

void		crank_quat_float_inverse_self (	CrankQuatFloat*	a	);

void		crank_quat_float_conjugate_self (	CrankQuatFloat*	a	);
											
void		crank_quat_float_unit_self (	CrankQuatFloat*	a	);

//////// Quat - Real Operations ////////////////////////////////////////////////

void		crank_quat_float_addr (			CrankQuatFloat*	a,
											gfloat			b,
											CrankQuatFloat*	r		);

void		crank_quat_float_subr (			CrankQuatFloat*	a,
											gfloat			b,
											CrankQuatFloat*	r		);

void		crank_quat_float_mulr (			CrankQuatFloat*	a,
											gfloat			b,
											CrankQuatFloat*	r		);

void		crank_quat_float_divr (			CrankQuatFloat*	a,
											gfloat			b,
											CrankQuatFloat*	r		);



void		crank_quat_float_addr_self (	CrankQuatFloat*	a,
											gfloat			b	);

void		crank_quat_float_subr_self (	CrankQuatFloat*	a,
											gfloat			b	);

void		crank_quat_float_mulr_self (	CrankQuatFloat*	a,
											gfloat			b	);

void		crank_quat_float_divr_self (	CrankQuatFloat*	a,
											gfloat			b	);

//////// Real - Quat Operations ////////////////////////////////////////////////

void		crank_quat_float_rsubr (		CrankQuatFloat*	a,
											gfloat			b,
											CrankQuatFloat*	r		);

void		crank_quat_float_rdivr (		CrankQuatFloat*	a,
											gfloat			b,
											CrankQuatFloat*	r		);

//////// Quat - Cplx Operations ////////////////////////////////////////////////

void		crank_quat_float_addc (			CrankQuatFloat*	a,
											CrankCplxFloat*	b,
											CrankQuatFloat*	r	);

void		crank_quat_float_subc (			CrankQuatFloat*	a,
											CrankCplxFloat*	b,
											CrankQuatFloat*	r	);

void		crank_quat_float_mulc (			CrankQuatFloat*	a,
											CrankCplxFloat*	b,
											CrankQuatFloat*	r	);

void		crank_quat_float_addc_self (	CrankQuatFloat*	a,
											CrankCplxFloat*	b	);

void		crank_quat_float_subc_self (	CrankQuatFloat*	a,
											CrankCplxFloat*	b	);

void		crank_quat_float_mulc_self (	CrankQuatFloat*	a,
											CrankCplxFloat*	b	);


//////// Quat - Quat Operations ////////////////////////////////////////////////

void		crank_quat_float_add (			CrankQuatFloat*	a,
											CrankQuatFloat*	b,
											CrankQuatFloat*	r	);
										
void		crank_quat_float_sub (			CrankQuatFloat*	a,
											CrankQuatFloat*	b,
											CrankQuatFloat*	r	);
										
void		crank_quat_float_mul (			CrankQuatFloat*	a,
											CrankQuatFloat*	b,
											CrankQuatFloat*	r	);

void		crank_quat_float_add_self (		CrankQuatFloat*	a,
											CrankQuatFloat*	b	);
										
void		crank_quat_float_sub_self (		CrankQuatFloat*	a,
											CrankQuatFloat*	b	);
										
void		crank_quat_float_mul_self (		CrankQuatFloat*	a,
											CrankQuatFloat*	b	);

void		crank_quat_float_mul_conj (		CrankQuatFloat*	a,
											CrankQuatFloat*	b,
											CrankQuatFloat*	r	);

//////// Ternary Operations ////////////////////////////////////////////////////

void		crank_quat_float_mix (			CrankQuatFloat*	a,
											CrankQuatFloat*	b,
											gfloat			c,
											CrankQuatFloat*	r	);


//////// Exponential Operations ////////////////////////////////////////////////

void		crank_quat_float_ln (			CrankQuatFloat*	a,
											CrankQuatFloat*	r	);

void		crank_quat_float_exp (			CrankQuatFloat*	a,
											CrankQuatFloat*	r	);

void		crank_quat_float_powr (			CrankQuatFloat*	a,
											const gfloat	b,
											CrankQuatFloat*	r	);
											
											
//////// Rotation Operations ///////////////////////////////////////////////////

void		crank_quat_float_rotatev (	CrankQuatFloat*	quat,
										CrankVecFloat3*	vec,
										CrankVecFloat3*	r		);
											

#endif
