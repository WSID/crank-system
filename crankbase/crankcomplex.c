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

#include <stdarg.h>
#include <math.h>
#include <glib.h>
#include <glib-object.h>

#include "crankcomplex.h"

/**
 * SECTION: crankcomplex
 * @title: Complex value
 * @short_description: Complex values.
 * @usability: unstable
 * @includes: crankbase.h
 *
 * A Crank System provides Complex Numbers.
 *
 * Currently, only float complex type is provided.
 * 
 * * Property
 *    * Norm, and square of norm.
 * * Unary Operations
 *    * Negate
 *    * Inverse
 *    * Conjugation
 * * Cplx - Scalar
 *    * Add, Sub, Mul, Div
 * * Scalar - Cplx
 *    * Sub, Div
 * * Cplx - Cplx
 *    * Add, Sub, Mul, Div
 *    * Mul-conjugate
 * * Ternary
 *    * Mix
 */


//////// Type function declaration /////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (	CrankCplxFloat,
						crank_cplx_float,
						crank_cplx_float_dup,
						g_free	);

//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_cplx_float_init:
 * @cplx: (out): A Complex to initialize.
 * @real: Real part.
 * @imag: Imaginary part.
 *
 * Initialize a complex with given parts.
 */
void
crank_cplx_float_init (	CrankCplxFloat*	cplx,
						gfloat			real,
						gfloat			imag	)
{
	cplx->real = real;
	cplx->imag = imag;
}

/**
 * crank_cplx_float_init_arr:
 * @cplx: (out): A Complex to initialize.
 * @parts: (array fixed-size=2): Parts.
 *
 * Initialize a complex with given parts.
 */
void
crank_cplx_float_init_arr (	CrankCplxFloat*	cplx,
							gfloat*			parts	)
{
	cplx->real = parts[0];
	cplx->imag = parts[1];
}

/**
 * crank_cplx_float_init_valist:
 * @cplx: (out): A Complex to initialize.
 * @varargs: Variadic arguments. should contains 2 double values.
 *
 * Initialize a complex with given parts from variadic arguments.
 */
void
crank_cplx_float_init_valist (	CrankCplxFloat*	cplx,
								va_list			varargs	)
{
	cplx->real = (gfloat) (va_arg(varargs, gdouble));
	cplx->imag = (gfloat) (va_arg(varargs, gdouble));
}

/**
 * crank_cplx_float_init_fill:
 * @cplx: (out): A Complex to initialize.
 * @fill: A filling element.
 *
 * Initialize a complex by filling given value.
 */
void
crank_cplx_float_init_fill (	CrankCplxFloat*	cplx,
								gfloat			fill	)
{
	cplx->real = fill;
	cplx->imag = fill;
}

//////// Basic Operations //////////////////////////////////////////////////////

/**
 * crank_cplx_float_copy:
 * @cplx: A Complex.
 * @other: (out): A Complex to store copy.
 *
 * Copies a complex.
 */
void
crank_cplx_float_copy (	CrankCplxFloat*	cplx,
						CrankCplxFloat*	other	)
{
	other->real = cplx->real;
	other->imag = cplx->imag;
}
					
/**
 * crank_cplx_float_dup:
 * @cplx: A Complex.
 *
 * Allocates a memory for complex and copies on it.
 *
 * Allocated memory should be freed by g_free().
 *
 * Returns: Allocated complex.
 */				
CrankCplxFloat*
crank_cplx_float_dup (	CrankCplxFloat*	cplx	)
{
	CrankCplxFloat* result = g_new (CrankCplxFloat, 1);
	crank_cplx_float_copy (cplx, result);
	return result;
}

/**
 * crank_cplx_float_equal:
 * @a: (type CrankCplxFloat): A Complex.
 * @b: (type CrankCplxFloat): A Complex.
 *
 * Checks two complexes are equal.
 *
 * Returns: whether they are equal.
 */
gboolean
crank_cplx_float_equal (	gconstpointer	a,
							gconstpointer	b	)
{
	CrankCplxFloat*	ac = (CrankCplxFloat*)a;
	CrankCplxFloat*	bc = (CrankCplxFloat*)b;
	
	return ((ac->real == bc->real) && (ac->imag == bc->imag));
}

/**
 * crank_cplx_float_hash:
 * @a: (type CrankCplxFloat): A Complex.
 *
 * Returns hash value of complex. This is useful when using Complex values
 * with #GHashTable.
 *
 * Returns: A hash value.s
 */
guint
crank_cplx_float_hash (		gconstpointer	a	)
{
	CrankCplxFloat*	ac = (CrankCplxFloat*)a;
	
	gdouble	r = ac->real;
	gdouble i = ac->imag;
	
	return g_double_hash (&r) + g_double_hash (&i);
}

/**
 * crank_cplx_float_to_string:
 * @cplx: A Complex value.
 *
 * Stringify a complex value as,
 *
 * |[ 
 *    3.2 + (-1.34i)
 * ]|
 * 
 * Returns: String representation of complex. Free with g_free()
 */
gchar*
crank_cplx_float_to_string (	CrankCplxFloat*	cplx	)
{
	return crank_cplx_float_to_string_full (	cplx,
												"", " + ", "", "%g", "(%gi)");
}

/**
 * crank_cplx_float_to_string_full:
 * @cplx: A Complex value.
 * @left: Left, marking start of complex.
 * @mid: Middle, separates real and imaginary parts.
 * @right: Right, marking end of complex.
 * @format_real: Format for real part - should comsume 1 float value.
 * @format_imag: Format for imaginary part - should consume 1 float value.
 *
 * Stringify complex value into string.
 *
 * Returns: String representation of complex. Free with g_free()
 */
gchar*		crank_cplx_float_to_string_full (	CrankCplxFloat*	cplx,
												const gchar*	left,
												const gchar*	mid,
												const gchar*	right,
												const gchar*	format_real,
												const gchar*	format_imag	)
{
	GString*	builder = g_string_new (left);
	gchar*		result;
	
	g_string_append_printf (builder, format_real, cplx->real);
	
	g_string_append (builder, mid);
	
	g_string_append_printf (builder, format_imag, cplx->imag);
	
	g_string_append (builder, right);
	
	result = builder->str;
	
	g_string_free (builder, FALSE);
	
	return result;
}

//////// Unary Operations //////////////////////////////////////////////////////
/**
 * crank_cplx_float_get_norm_sq:
 * @cplx: A Complex.
 *
 * Gets square of norm.
 * 
 * Returns: Square of norm of complex.
 */
gfloat
crank_cplx_float_get_norm_sq (	CrankCplxFloat*	cplx	)
{
	return cplx->real * cplx->real + cplx->imag * cplx->imag;
}

/**
 * crank_cplx_float_get_norm:
 * @cplx: A Complex.
 * 
 * Gets norm of complex.
 *
 * Returns: Norm.
 */
gfloat
crank_cplx_float_get_norm (		CrankCplxFloat*	cplx	)
{
	return sqrtf(crank_cplx_float_get_norm_sq(cplx));
}

/**
 * crank_cplx_float_conjugate:
 * @a: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets a conjugate.
 */
void
crank_cplx_float_conjugate (	CrankCplxFloat*	a,
								CrankCplxFloat*	r	)
{
	r->real = a->real;
	r->imag = - a->imag;
}

/**
 * crank_cplx_float_neg:
 * @a: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets a negation. (- @a)
 */
void
crank_cplx_float_neg (	CrankCplxFloat*	a,
						CrankCplxFloat*	r	)
{
	r->real = - a->real;
	r->imag = - a->imag;
}

/**
 * crank_cplx_float_inverse:
 * @a: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets a invert. (1 / @a)
 */
void
crank_cplx_float_inverse (	CrankCplxFloat*	a,
							CrankCplxFloat*	r	)
{
	gfloat norm_sq = a->real * a->real + a->imag * a->imag;
	
	r->real = a->real / norm_sq;
	r->imag = -a->imag / norm_sq;
}



//////// Cplx - Real Operations ////////////////////////////////////////////////

/**
 * crank_cplx_float_addr:
 * @a: A Complex.
 * @b: A real value.
 * @r: (out): A Complex to store result.
 *
 * Gets a addition of complex and scalar.
 */
void
crank_cplx_float_addr (	CrankCplxFloat*	a,
						gfloat			b,
						CrankCplxFloat*	r		)
{
	r->real = a->real + b;
	r->imag = a->imag;
}

/**
 * crank_cplx_float_subr:
 * @a: A Complex.
 * @b: A real value.
 * @r: (out): A Complex to store result.
 *
 * Gets a subtration of complex by scalar.
 */
void
crank_cplx_float_subr (	CrankCplxFloat*	a,
						gfloat			b,
						CrankCplxFloat*	r		)
{
	r->real = a->real - b;
	r->imag = a->imag;
}

/**
 * crank_cplx_float_mulr:
 * @a: A Complex.
 * @b: A real value.
 * @r: (out): A Complex to store result.
 *
 * Gets a multiplication of complex by scalar.
 */
void
crank_cplx_float_mulr (	CrankCplxFloat*	a,
						gfloat			b,
						CrankCplxFloat*	r		)
{
	r->real = a->real * b;
	r->imag = a->imag * b;
}

/**
 * crank_cplx_float_divr:
 * @a: A Complex.
 * @b: A real value.
 * @r: (out): A Complex to store result.
 *
 * Gets a division of complex by scalar.
 */
void
crank_cplx_float_divr (	CrankCplxFloat*	a,
						gfloat			b,
						CrankCplxFloat*	r		)
{
	r->real = a->real / b;
	r->imag = a->imag / b;
}


//////// Real - Cplx Operations ////////////////////////////////////////////////

/**
 * crank_cplx_float_rsubr:
 * @a: A Complex.
 * @b: A real value.
 * @r: (out): A Complex to store result.
 *
 * Gets subtraction of scalar by complex.
 */
void
crank_cplx_float_rsubr (	CrankCplxFloat*	a,
							gfloat			b,
							CrankCplxFloat*	r		)
{
	r->real = b - a->real;
	r->imag = - a->imag;
}

/**
 * crank_cplx_float_rdivr:
 * @a: A Complex.
 * @b: A real value.
 * @r: (out): A Complex to store result.
 *
 * Gets division of scalar by complex.
 */
void
crank_cplx_float_rdivr (	CrankCplxFloat*	a,
							gfloat			b,
							CrankCplxFloat*	r		)
{
	gfloat	anorm_sq = crank_cplx_float_get_norm_sq (a);
	
	gfloat nr = (b * a->real) / anorm_sq;
	gfloat ni = (- b * a->imag) / anorm_sq;
	
	r->real = nr;
	r->imag = ni;
}

//////// Cplx - Cplx Operations ////////////////////////////////////////////////

/**
 * crank_cplx_float_add:
 * @a: A Complex.
 * @b: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets a addition of two complex.
 */
void
crank_cplx_float_add (	CrankCplxFloat*	a,
						CrankCplxFloat*	b,
						CrankCplxFloat*	r	)
{
	r->real = a->real + b->real;
	r->imag = a->imag + b->imag;
}
										
/**
 * crank_cplx_float_sub:
 * @a: A Complex.
 * @b: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets a subtration of two complex.
 */
void
crank_cplx_float_sub (	CrankCplxFloat*	a,
						CrankCplxFloat*	b,
						CrankCplxFloat*	r	)
{
	r->real = a->real - b->real;
	r->imag = a->imag - b->imag;
}

/**
 * crank_cplx_float_mul:
 * @a: A Complex.
 * @b: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets a multiplication of two complex.
 */
void
crank_cplx_float_mul (	CrankCplxFloat*	a,
						CrankCplxFloat*	b,
						CrankCplxFloat*	r	)
{
	gfloat nr = a->real * b->real - a->imag * b->imag;
	gfloat ni = a->real * b->imag + a->imag * b->real;
	r->real = nr;
	r->imag = ni;
}

/**
 * crank_cplx_float_div:
 * @a: A Complex.
 * @b: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets a division of two complex.
 */
void
crank_cplx_float_div (	CrankCplxFloat*	a,
						CrankCplxFloat*	b,
						CrankCplxFloat*	r	)
{
	gfloat	bnorm_sq = crank_cplx_float_get_norm_sq (b);
	
	gfloat nr = (a->real * b->real + a->imag * b->imag) / bnorm_sq;
	gfloat ni = (b->real * a->imag - a->real * b->imag) / bnorm_sq;
	
	r->real = nr;
	r->imag = ni;
}

/**
 * crank_cplx_float_mul_conj:
 * @a: A Complex.
 * @b: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Multiplies @a with conjugate of @b.
 */
void		crank_cplx_float_mul_conj (	CrankCplxFloat*	a,
										CrankCplxFloat*	b,
										CrankCplxFloat*	r	)
{
	gfloat nr = a->real * b->real + a->imag * b->imag;
	gfloat ni = - a->real * b->imag + a->imag * b->real;
	r->real = nr;
	r->imag = ni;
}

//////// Ternary Operations ////////////////////////////////////////////////////

/**
 * crank_cplx_float_mix:
 * @a: A Complex.
 * @b: A Complex.
 * @c: A scalar.
 * @r: (out): A Complex to store result.
 *
 * Gets a mixture of two complex.
 */
void
crank_cplx_float_mix (	CrankCplxFloat*	a,
						CrankCplxFloat*	b,
						gfloat			c,
						CrankCplxFloat*	r	)
{
	gfloat	d = 1 - c;
	
	r->real = a->real * d + b->real * c;
	r->imag = a->imag * d + b->imag * c;
}
