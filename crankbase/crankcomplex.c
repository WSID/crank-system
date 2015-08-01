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
 * A Crank System provides Complex Numbers, for simpler modeling and base
 * entities for quaternions.
 *
 * Currently, only float complex type is provided.
 *
 * # Supported Operations
 *
 * <table frame="all"><title>Supported Operations</title>
 *   <tgroup cols="2" align="left" colsep="1" rowsep="1">
 *     <colspec colname="op" />
 *     <thead>
 *       <row>
 *         <entry>Operations</entry>
 *         <entry>Detailed</entry>
 *       </row>
 *     </thead>
 *     <tbody>
 *       <row>
 *         <entry>Initialization</entry>
 *         <entry>arguments, array, valist, fill</entry>
 *       </row>
 *       <row>
 *         <entry>Attributes</entry>
 *         <entry>arg, norm, norm_sq</entry>
 *       </row>
 *       <row>
 *         <entry>Unary Operations</entry>
 *         <entry>Negate, Inverse, Conjugate, Unit</entry>
 *       </row>
 *       <row>
 *         <entry>Binary Operations with real values</entry>
 *         <entry>add, sub, mul, div</entry>
 *       </row>
 *       <row>
 *         <entry>Swapped Binary Operations with real values</entry>
 *         <entry>rsub, rdiv</entry>
 *       </row>
 *       <row>
 *         <entry>Ternary Operations</entry>
 *         <entry>mix</entry>
 *       </row>
 *       <row>
 *         <entry>Exponential</entry>
 *         <entry>ln, exp, pow</entry>
 *       </row>
 *       <row>
 *         <entry>Hyperbolic</entry>
 *         <entry>sinh, cosh, tanh</entry>
 *       </row>
 *       <row>
 *         <entry>Trigonometric</entry>
 *         <entry>sin, cos, tan</entry>
 *       </row>
 *     </tbody>
 *   </tgroup>
 * </table>
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
 * crank_cplx_float_equal_delta:
 * @a: A Complex.
 * @b: A Complex.
 * @d: Delta value.
 *
 * Checks two complexes are sufficiently equal, which means they are close to
 * each other so that we can say they are almost equal.
 *
 * Differences are calculated by distance between them.
 *
 * Returns: whether they are equal.
 */
gboolean
crank_cplx_float_equal_delta (	CrankCplxFloat*	a,
								CrankCplxFloat*	b,
								const gfloat	d	)
{
	CrankCplxFloat	diff;
	crank_cplx_float_sub (b, a, &diff);
	
	return (crank_cplx_float_get_norm (&diff) <= d);
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
	return crank_cplx_float_to_string_full (	cplx, CRANK_CPLX_FLOAT_DEFFORMAT);
}

/**
 * crank_cplx_float_to_string_full:
 * @cplx: A Complex value.
 * @format: A format to stringify complex - consumes 2 parameters.
 *
 * Stringify complex value into string.
 *
 * It internally uses g_strdup_printf(), so @format consumes 2 float parameters.
 * First one is real value, and second one is imaginary value.
 *
 * Returns: String representation of complex. Free with g_free()
 */
gchar*		crank_cplx_float_to_string_full (	CrankCplxFloat*	cplx,
												const gchar*	format	)
{
	return g_strdup_printf (format, cplx->real, cplx->imag);
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
 * crank_cplx_float_get_arg:
 * @cplx: A Complex.
 *
 * Gets argument of complex, which is angle between real axis, on complex plane.
 *
 * Returns: Argument of complex.
 */
gfloat
crank_cplx_float_get_arg (	CrankCplxFloat*	cplx	)
{
	return atan2f (cplx->imag, cplx->real);
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
	gfloat norm_sq = crank_cplx_float_get_norm_sq (a);
	
	r->real = a->real / norm_sq;
	r->imag = -a->imag / norm_sq;
}

/**
 * crank_cplx_float_unit:
 * @a: A Complex
 * @r: (out): A Complex to store result.
 * 
 * Gets unit complex. (@a / |@a|)
 */
void
crank_cplx_float_unit (	CrankCplxFloat*	a,
						CrankCplxFloat*	r	)
{
	gfloat	norm = crank_cplx_float_get_norm (a);
	
	crank_cplx_float_divr (a, norm, r);
}



/**
 * crank_cplx_float_conjugate_self:
 * @a: A Complex.
 *
 * Sets @a as conjugate of itself.
 */
void
crank_cplx_float_conjugate_self (	CrankCplxFloat*	a	)
{
	a->imag = - a->imag;
}

/**
 * crank_cplx_float_neg_self:
 * @a: A Complex.
 *
 * Sets @a as negation of itself. (- @a)
 */
void
crank_cplx_float_neg_self (	CrankCplxFloat*	a	)
{
	a->real = - a->real;
	a->imag = - a->imag;
}

/**
 * crank_cplx_float_inverse_self:
 * @a: A Complex.
 *
 * Sets @a as invert of self. (1 / @a)
 */
void
crank_cplx_float_inverse_self (	CrankCplxFloat*	a	)
{
	gfloat norm_sq = crank_cplx_float_get_norm_sq (a);
	
	a->real = a->real / norm_sq;
	a->imag = -a->imag / norm_sq;
}

/**
 * crank_cplx_float_unit_self:
 * @a: A Complex
 * 
 * Sets @a as its unit complex. (@a / |@a|)
 */
void
crank_cplx_float_unit_self (	CrankCplxFloat*	a	)
{
	gfloat	norm = crank_cplx_float_get_norm (a);
	
	crank_cplx_float_divr_self (a, norm);
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




/**
 * crank_cplx_float_addr_self:
 * @a: A Complex.
 * @b: A real value.
 *
 * Applies a addition by scalar to a complex.
 */
void
crank_cplx_float_addr_self (	CrankCplxFloat*	a,
								gfloat			b		)
{
	a->real += b;
}

/**
 * crank_cplx_float_subr_self:
 * @a: A Complex.
 * @b: A real value.
 *
 * Applies a subtration by scalar to a complex.
 */
void
crank_cplx_float_subr_self (	CrankCplxFloat*	a,
								gfloat			b		)
{
	a->real -= b;
}

/**
 * crank_cplx_float_mulr_self:
 * @a: A Complex.
 * @b: A real value.
 *
 * Applies a multiplication by scalar to a complex.
 */
void
crank_cplx_float_mulr_self (	CrankCplxFloat*	a,
								gfloat			b		)
{
	a->real *= b;
	a->imag *= b;
}

/**
 * crank_cplx_float_divr_self:
 * @a: A Complex.
 * @b: A real value.
 *
 * Applies a division by scalar to a complex.
 */
void
crank_cplx_float_divr_self (	CrankCplxFloat*	a,
								gfloat			b		)
{
	a->real /= b;
	a->imag /= b;
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
 * crank_cplx_float_add_self:
 * @a: A Complex.
 * @b: A Complex.
 *
 * Applies a addition by a complex.
 */
void
crank_cplx_float_add_self (	CrankCplxFloat*	a,
							CrankCplxFloat*	b	)
{
	a->real += b->real;
	a->imag += b->imag;
}
										
/**
 * crank_cplx_float_sub_self:
 * @a: A Complex.
 * @b: A Complex.
 *
 * Applies a subtration by a complex.
 */
void
crank_cplx_float_sub_self (	CrankCplxFloat*	a,
							CrankCplxFloat*	b	)
{
	a->real -= b->real;
	a->imag -= b->imag;
}

/**
 * crank_cplx_float_mul_self:
 * @a: A Complex.
 * @b: A Complex.
 *
 * Applies a multiplication by a complex.
 */
void
crank_cplx_float_mul_self (	CrankCplxFloat*	a,
							CrankCplxFloat*	b	)
{
	gfloat nr = a->real * b->real - a->imag * b->imag;
	gfloat ni = a->real * b->imag + a->imag * b->real;
	a->real = nr;
	a->imag = ni;
}

/**
 * crank_cplx_float_div_self:
 * @a: A Complex.
 * @b: A Complex.
 *
 * Applies a division by a complex.
 */
void
crank_cplx_float_div_self (	CrankCplxFloat*	a,
							CrankCplxFloat*	b	)
{
	gfloat	bnorm_sq = crank_cplx_float_get_norm_sq (b);
	
	gfloat nr = (a->real * b->real + a->imag * b->imag) / bnorm_sq;
	gfloat ni = (b->real * a->imag - a->real * b->imag) / bnorm_sq;
	
	a->real = nr;
	a->imag = ni;
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


//////// Exponential Operations ////////////////////////////////////////////////

/**
 * crank_cplx_float_ln:
 * @a: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets Natural log from a complex.
 *
 * As periodic characteristic of exponential, returned complex will have
 * imaginary part in [0, 2 * PI} or being NAN (if @a is 0)
 */
void
crank_cplx_float_ln (	CrankCplxFloat*	a,
						CrankCplxFloat*	r	)
{
	gfloat	norm;
	
	norm = crank_cplx_float_get_norm (a);
	
	if (norm == 0) {
		r->real = - INFINITY;
		r->imag = NAN;
	}
	else {
		gfloat	arg = crank_cplx_float_get_arg (a);
		
		r->real = logf (norm);
		r->imag = arg;
	}
}

/**
 * crank_cplx_float_exp:
 * @a: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets e-based exponential of complex.
 */
void
crank_cplx_float_exp (	CrankCplxFloat*	a,
						CrankCplxFloat*	r	)
{
	if (a->real == - INFINITY) {
		r->real = 0;
		r->imag = 0;
	}
	else {
		gfloat	norm = expf (a->real);
		
		r->real = norm * cosf (a->imag);
		r->imag = norm * sinf (a->imag);
	}
}

/**
 * crank_cplx_float_pow:
 * @a: A Complex.
 * @b: A Complex.
 * @r: (out): A Complex to store result.
 *
 * Gets power of two complex.
 */
void
crank_cplx_float_pow (	CrankCplxFloat*	a,
						CrankCplxFloat* b,
						CrankCplxFloat*	r	)
{
	// pow is exp(b * ln(a))
	
	// nb = b * ln(a)
	// nb := ln(a)
	// nb :*= b
	CrankCplxFloat	nb;
	
	crank_cplx_float_ln (a, &nb);
	crank_cplx_float_mul_self (&nb, b);
	
	crank_cplx_float_exp (&nb, r);
}


//////// Hyperbolic Operations /////////////////////////////////////////////////

/**
 * crank_cplx_float_sinh:
 * @a: A Complex
 * @r: (out): A Complex to store result.
 *
 * Gets sinh of complex.
 */
void
crank_cplx_float_sinh (	CrankCplxFloat*	a,
						CrankCplxFloat* r	)
{
	CrankCplxFloat	e_p;
	CrankCplxFloat	e_m;
	
	crank_cplx_float_exp (a, &e_p);
	crank_cplx_float_inverse (&e_p, &e_m);
	
	crank_cplx_float_sub (&e_p, &e_m, r);
	crank_cplx_float_divr_self (r, 2.0f);
}
						
						
/**
 * crank_cplx_float_cosh:
 * @a: A Complex
 * @r: (out): A Complex to store result.
 *
 * Gets sinh of complex.
 */
void
crank_cplx_float_cosh (	CrankCplxFloat*	a,
						CrankCplxFloat* r	)
{
	CrankCplxFloat	e_p;
	CrankCplxFloat	e_m;
	
	crank_cplx_float_exp (a, &e_p);
	crank_cplx_float_inverse (&e_p, &e_m);
	
	crank_cplx_float_add (&e_p, &e_m, r);
	crank_cplx_float_divr_self (r, 2.0f);
}						
						
/**
 * crank_cplx_float_tanh:
 * @a: A Complex
 * @r: (out): A Complex to store result.
 *
 * Gets sinh of complex.
 */
void
crank_cplx_float_tanh (	CrankCplxFloat*	a,
						CrankCplxFloat* r	)
{
	CrankCplxFloat	e_p;
	CrankCplxFloat	e_m;
	CrankCplxFloat	divisor;
	
	crank_cplx_float_exp (a, &e_p);
	crank_cplx_float_inverse (&e_p, &e_m);
	
	crank_cplx_float_sub (&e_p, &e_m, r);
	crank_cplx_float_add (&e_p, &e_m, &divisor);
	
	crank_cplx_float_div_self (r, &divisor);
}

//////// Trigonometric Operations //////////////////////////////////////////////

/**
 * crank_cplx_float_sin:
 * @a: A Complex
 * @r: (out): A Complex to store result.
 *
 * Gets sin of complex.
 */
void
crank_cplx_float_sin (	CrankCplxFloat*	a,
						CrankCplxFloat*	r	)
{
	gfloat	sr	= sinf (a->real);
	gfloat	cr	= cosf (a->real);
	gfloat	shi	= sinhf (a->imag);
	gfloat	chi	= coshf (a->imag);
	
	r->real =	(sr * chi);
	r->imag =	(cr * shi);
}

/**
 * crank_cplx_float_cos:
 * @a: A Complex
 * @r: (out): A Complex to store result.
 *
 * Gets cos of complex.
 */
void
crank_cplx_float_cos (	CrankCplxFloat*	a,
						CrankCplxFloat*	r	)
{
	gfloat	sr	= sinf (a->real);
	gfloat	cr	= cosf (a->real);
	gfloat	shi	= sinhf (a->imag);
	gfloat	chi	= coshf (a->imag);
	
	r->real =	(cr * chi);
	r->imag =	-(sr * shi);
}

/**
 * crank_cplx_float_tan:
 * @a: A Complex
 * @r: (out): A Complex to store result.
 *
 * Gets tan of complex.
 */
void
crank_cplx_float_tan (	CrankCplxFloat*	a,
						CrankCplxFloat*	r	)
{
	CrankCplxFloat	s;
	CrankCplxFloat	c;
	
	crank_cplx_float_sin (a, &s);
	crank_cplx_float_cos (a, &c);
	
	crank_cplx_float_div (&s, &c, r);
}
