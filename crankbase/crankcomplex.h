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

void			crank_cplx_float_init_fill (CrankCplxFloat*	cplx,
											gfloat			fill	);

//////// Basic Operations //////////////////////////////////////////////////////

void			crank_cplx_float_copy (	CrankCplxFloat*	cplx,
										CrankCplxFloat*	other	);
									
CrankCplxFloat*	crank_cplx_float_dup (	CrankCplxFloat*	cplx	);

gboolean	crank_cplx_float_equal (	gconstpointer	a,
										gconstpointer	b	);
										
guint		crank_cplx_float_hash (		gconstpointer	a	);

gchar*		crank_cplx_float_to_string (		CrankCplxFloat*	cplx	);

gchar*		crank_cplx_float_to_string_full (	CrankCplxFloat*	cplx,
										const gchar*	left,
										const gchar*	mid,
										const gchar*	right,
										const gchar*	format_real,
										const gchar*	format_imag	);

//////// Unary Operations //////////////////////////////////////////////////////
gfloat		crank_cplx_float_get_norm_sq (	CrankCplxFloat*	cplx	);

gfloat		crank_cplx_float_get_norm (		CrankCplxFloat*	cplx	);

void		crank_cplx_float_conjugate (	CrankCplxFloat*	a,
											CrankCplxFloat*	r	);
										
void		crank_cplx_float_neg (			CrankCplxFloat*	a,
											CrankCplxFloat*	r	);

void		crank_cplx_float_inverse (		CrankCplxFloat*	a,
											CrankCplxFloat*	r	);

//////// Cplx - Real Operations ////////////////////////////////////////////////

void		crank_cplx_float_addr (		CrankCplxFloat*	a,
										gfloat			b,
										CrankCplxFloat*	r		);

void		crank_cplx_float_subr (		CrankCplxFloat*	a,
										gfloat			b,
										CrankCplxFloat*	r		);

void		crank_cplx_float_mulr (		CrankCplxFloat*	a,
										gfloat			b,
										CrankCplxFloat*	r		);

void		crank_cplx_float_divr (		CrankCplxFloat*	a,
										gfloat			b,
										CrankCplxFloat*	r		);

//////// Real - Cplx Operations ////////////////////////////////////////////////

void		crank_cplx_float_rsubr (	CrankCplxFloat*	a,
										gfloat			b,
										CrankCplxFloat*	r		);

void		crank_cplx_float_rdivr (	CrankCplxFloat*	a,
										gfloat			b,
										CrankCplxFloat*	r		);

//////// Cplx - Cplx Operations ////////////////////////////////////////////////

void		crank_cplx_float_add (		CrankCplxFloat*	a,
										CrankCplxFloat*	b,
										CrankCplxFloat*	r	);
										
void		crank_cplx_float_sub (		CrankCplxFloat*	a,
										CrankCplxFloat*	b,
										CrankCplxFloat*	r	);
										
void		crank_cplx_float_mul (		CrankCplxFloat*	a,
										CrankCplxFloat*	b,
										CrankCplxFloat*	r	);

void		crank_cplx_float_div (		CrankCplxFloat*	a,
										CrankCplxFloat*	b,
										CrankCplxFloat*	r	);

void		crank_cplx_float_mul_conj (	CrankCplxFloat*	a,
										CrankCplxFloat*	b,
										CrankCplxFloat*	r	);

//////// Ternary Operations ////////////////////////////////////////////////////

void		crank_cplx_float_mix (		CrankCplxFloat*	a,
										CrankCplxFloat*	b,
										gfloat			c,
										CrankCplxFloat*	r	);



#endif
