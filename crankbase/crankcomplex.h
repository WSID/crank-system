#ifndef CRANKCOMPLEX_H
#define CRANKCOMPLEX_H

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
#error crankcomplex.h cannot be included directly.
#endif

#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>

//////// Struct declaration ////////////////////////////////////////////////////

/**
 * CRANK_CPLX_FLOAT_DEFFORMAT: (value "%g + (%gi)")
 *
 * Default format for crank_cplx_float_to_string_full().
 */
#define CRANK_CPLX_FLOAT_DEFFORMAT "%g + (%gi)"

/**
 * CrankCplxFloat:
 * @real: Real part of complex.
 * @imag: Imaginary part of complex.
 *
 * Represents a float complex value
 */
typedef struct _CrankCplxFloat {
	gfloat	real;
	gfloat	imag;
} CrankCplxFloat;

GType		crank_cplx_float_get_type (void);

#define CRANK_TYPE_CPLX_FLOAT (crank_cplx_float_get_type())


//////// Initialization ////////////////////////////////////////////////////////

void		crank_cplx_float_init (			CrankCplxFloat*	cplx,
											gfloat			real,
											gfloat			imag	);

void		crank_cplx_float_init_arr (		CrankCplxFloat*	cplx,
											gfloat*			parts	);

void		crank_cplx_float_init_valist (	CrankCplxFloat*	cplx,
											va_list			varargs	);

void		crank_cplx_float_init_fill (	CrankCplxFloat*	cplx,
											gfloat			fill	);

//////// Basic Operations //////////////////////////////////////////////////////

void		crank_cplx_float_copy (			CrankCplxFloat*	cplx,
											CrankCplxFloat*	other	);
									
CrankCplxFloat*	crank_cplx_float_dup (		CrankCplxFloat*	cplx	);

gboolean	crank_cplx_float_equal (		gconstpointer	a,
											gconstpointer	b	);

gboolean	crank_cplx_float_equal_delta (	CrankCplxFloat*	a,
											CrankCplxFloat*	b,
											const gfloat	d	);
										
guint		crank_cplx_float_hash (			gconstpointer	a	);

gchar*		crank_cplx_float_to_string (	CrankCplxFloat*	cplx	);

gchar*		crank_cplx_float_to_string_full (	CrankCplxFloat*	cplx,
											const gchar*	format	);

//////// Unary Operations //////////////////////////////////////////////////////
gfloat		crank_cplx_float_get_norm_sq (	CrankCplxFloat*	cplx	);

gfloat		crank_cplx_float_get_norm (		CrankCplxFloat*	cplx	);

gfloat		crank_cplx_float_get_arg (		CrankCplxFloat*	cplx	);
										
void		crank_cplx_float_neg (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);

void		crank_cplx_float_inverse (		CrankCplxFloat*	a,
											CrankCplxFloat*	r	);

void		crank_cplx_float_conjugate (	CrankCplxFloat*	a,
											CrankCplxFloat*	r	);
											
void		crank_cplx_float_unit (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);
											
										
void		crank_cplx_float_neg_self (		CrankCplxFloat*	a	);

void		crank_cplx_float_inverse_self (	CrankCplxFloat*	a	);

void		crank_cplx_float_conjugate_self (	CrankCplxFloat*	a	);
											
void		crank_cplx_float_unit_self (	CrankCplxFloat*	a	);

//////// Cplx - Real Operations ////////////////////////////////////////////////

void		crank_cplx_float_addr (			CrankCplxFloat*	a,
											gfloat			b,
											CrankCplxFloat*	r		);

void		crank_cplx_float_subr (			CrankCplxFloat*	a,
											gfloat			b,
											CrankCplxFloat*	r		);

void		crank_cplx_float_mulr (			CrankCplxFloat*	a,
											gfloat			b,
											CrankCplxFloat*	r		);

void		crank_cplx_float_divr (			CrankCplxFloat*	a,
											gfloat			b,
											CrankCplxFloat*	r		);



void		crank_cplx_float_addr_self (	CrankCplxFloat*	a,
											gfloat			b	);

void		crank_cplx_float_subr_self (	CrankCplxFloat*	a,
											gfloat			b	);

void		crank_cplx_float_mulr_self (	CrankCplxFloat*	a,
											gfloat			b	);

void		crank_cplx_float_divr_self (	CrankCplxFloat*	a,
											gfloat			b	);

//////// Real - Cplx Operations ////////////////////////////////////////////////

void		crank_cplx_float_rsubr (		CrankCplxFloat*	a,
											gfloat			b,
											CrankCplxFloat*	r		);

void		crank_cplx_float_rdivr (		CrankCplxFloat*	a,
											gfloat			b,
											CrankCplxFloat*	r		);

//////// Cplx - Cplx Operations ////////////////////////////////////////////////

void		crank_cplx_float_add (			CrankCplxFloat*	a,
											CrankCplxFloat*	b,
											CrankCplxFloat*	r	);
										
void		crank_cplx_float_sub (			CrankCplxFloat*	a,
											CrankCplxFloat*	b,
											CrankCplxFloat*	r	);
										
void		crank_cplx_float_mul (			CrankCplxFloat*	a,
											CrankCplxFloat*	b,
											CrankCplxFloat*	r	);

void		crank_cplx_float_div (			CrankCplxFloat*	a,
											CrankCplxFloat*	b,
											CrankCplxFloat*	r	);

void		crank_cplx_float_add_self (		CrankCplxFloat*	a,
											CrankCplxFloat*	b	);
										
void		crank_cplx_float_sub_self (		CrankCplxFloat*	a,
											CrankCplxFloat*	b	);
										
void		crank_cplx_float_mul_self (		CrankCplxFloat*	a,
											CrankCplxFloat*	b	);

void		crank_cplx_float_div_self (		CrankCplxFloat*	a,
											CrankCplxFloat*	b	);
										

void		crank_cplx_float_mul_conj (		CrankCplxFloat*	a,
											CrankCplxFloat*	b,
											CrankCplxFloat*	r	);

//////// Ternary Operations ////////////////////////////////////////////////////

void		crank_cplx_float_mix (			CrankCplxFloat*	a,
											CrankCplxFloat*	b,
											gfloat			c,
											CrankCplxFloat*	r	);


//////// Exponential Operations ////////////////////////////////////////////////

void		crank_cplx_float_ln (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);

void		crank_cplx_float_exp (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);

void		crank_cplx_float_pow (			CrankCplxFloat*	a,
											CrankCplxFloat*	b,
											CrankCplxFloat*	r	);

//////// Hyperbolic Operations /////////////////////////////////////////////////

void		crank_cplx_float_sinh (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);
											
void		crank_cplx_float_cosh (			CrankCplxFloat* a,
											CrankCplxFloat*	r	);

void		crank_cplx_float_tanh (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);
											
//////// Trigonometric Operations //////////////////////////////////////////////

void		crank_cplx_float_sin (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);

void		crank_cplx_float_cos (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);

void		crank_cplx_float_tan (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);


#endif
