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
#include "crankveccommon.h"
#include "crankvecfloat.h"
#include "crankquaternion.h"

/**
 * SECTION: crankquaternion
 * @title: Quaternion value
 * @short_description: Quaternion values.
 * @usability: unstable
 * @includes: crankbase.h
 *
 * A Crank System provides quaternions, for various purpose.
 *
 * Currently, only float quaternion type is provided.
 *
 * # Rotation Representation
 *
 * Quaternions are frequently used, for rotation representation. BLAHBLAH
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
 *         <entry>arguments, complex arguments, array, valist, complex valist, fill</entry>
 *       </row>
 *       <row>
 *         <entry>Attributes</entry>
 *         <entry>wx, yz, imag, norm, norm_sq</entry>
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
 *         <entry>Binary Operations with Complex values</entry>
 *         <entry>add, sub, mul</entry>
 *       </row>
 *       <row>
 *         <entry>Binary Operations with Quaternion values</entry>
 *         <entry>add, sub, mul</entry>
 *       </row>
 *       <row>
 *         <entry>Ternary Operations</entry>
 *         <entry>mix</entry>
 *       </row>
 *       <row>
 *         <entry>Exponential</entry>
 *         <entry>ln, exp, pow</entry>
 *       </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */


//////// Type function declaration /////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (	CrankQuatFloat,
						crank_quat_float,
						crank_quat_float_dup,
						g_free	);

//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_quat_float_init:
 * @quat: (out): A Quaternion to initialize.
 * @w: Real part of quaternion.
 * @x: Imaginary part of quaternion.
 * @y: Imaginary part of quaternion.
 * @z: Imaginary part of quaternion.
 *
 * Initialize a quaternion with given parts.
 */
void
crank_quat_float_init (	CrankQuatFloat*	quat,
						gfloat			w,
						gfloat			x,
						gfloat			y,
						gfloat			z	)
{
	quat->w = w;
	quat->x = x;
	quat->y = y;
	quat->z = z;
}

/**
 * crank_quat_float_init_cplx:
 * @quat: (out): A Quaternion to initialize.
 * @wx: First half part of quaternion.
 * @yz: Last half part of quaternion.
 *
 * Initialize a quaternion with given parts. 
 */
void
crank_quat_float_init_cplx (	CrankQuatFloat*	quat,
								CrankCplxFloat* wx,
								CrankCplxFloat* yz	)
{
	quat->w = wx->real;
	quat->x = wx->imag;
	quat->y = yz->real;
	quat->z = yz->imag;
}

/**
 * crank_quat_float_init_arr:
 * @quat: (out): A Quaternion to initialize.
 * @parts: (array fixed-size=4): Parts.
 *
 * Initialize a quaternion with given parts.
 */
void
crank_quat_float_init_arr (	CrankQuatFloat*	quat,
							gfloat*			parts	)
{
	quat->w = parts[0];
	quat->x = parts[1];
	quat->y = parts[2];
	quat->z = parts[3];
}

/**
 * crank_quat_float_init_valist:
 * @quat: (out): A Quaternion to initialize.
 * @varargs: Variadic arguments. should contains 4 double values.
 *
 * Initialize a quaternion with given parts from variadic arguments.
 */
void
crank_quat_float_init_valist (	CrankQuatFloat*	quat,
								va_list			varargs	)
{
	quat->w = (gfloat) (va_arg(varargs, gdouble));
	quat->x = (gfloat) (va_arg(varargs, gdouble));
	quat->y = (gfloat) (va_arg(varargs, gdouble));
	quat->z = (gfloat) (va_arg(varargs, gdouble));
}

/**
 * crank_quat_float_init_valist_cplx:
 * @quat: (out): A Quaternion to initialize.
 * @varargs: Variadic arguments. should contains 2 #CrankCplxFloat.
 *
 * Initialize a quaternion with given complexes from variadic arguments.
 */
void
crank_quat_float_init_valist_cplx (	CrankQuatFloat*	quat,
									va_list			varargs	)
{
	CrankCplxFloat*	cplx;
	cplx = va_arg(varargs, CrankCplxFloat*);
	quat->w = cplx->real;
	quat->x = cplx->imag;
	
	cplx = va_arg(varargs, CrankCplxFloat*);
	quat->y = cplx->real;
	quat->z = cplx->imag;
}

/**
 * crank_quat_float_init_fill:
 * @quat: (out): A Quaternion to initialize.
 * @fill: A filling element.
 *
 * Initialize a quaternion by filling given value.
 */
void
crank_quat_float_init_fill (	CrankQuatFloat*	quat,
								gfloat			fill	)
{
	quat->w = fill;
	quat->x = fill;
	quat->y = fill;
	quat->z = fill;
}

//////// Basic Operations //////////////////////////////////////////////////////

/**
 * crank_quat_float_copy:
 * @quat: A Quaternion.
 * @other: (out): A Quaternion to store copy.
 *
 * Copies a quaternion.
 */
void
crank_quat_float_copy (	CrankQuatFloat*	quat,
						CrankQuatFloat*	other	)
{
	other->w = quat->w;
	other->x = quat->x;
	other->y = quat->y;
	other->z = quat->z;
}
					
/**
 * crank_quat_float_dup:
 * @quat: A Quaternion.
 *
 * Allocates a memory for quaternion and copies on it.
 *
 * Allocated memory should be freed by g_free().
 *
 * Returns: Allocated quaternion.
 */				
CrankQuatFloat*
crank_quat_float_dup (	CrankQuatFloat*	quat	)
{
	CrankQuatFloat* result = g_new (CrankQuatFloat, 1);
	crank_quat_float_copy (quat, result);
	return result;
}

/**
 * crank_quat_float_equal:
 * @a: (type CrankQuatFloat): A Quaternion.
 * @b: (type CrankQuatFloat): A Quaternion.
 *
 * Checks two quaterniones are equal.
 *
 * Returns: whether they are equal.
 */
gboolean
crank_quat_float_equal (	gconstpointer	a,
							gconstpointer	b	)
{
	CrankQuatFloat*	ac = (CrankQuatFloat*)a;
	CrankQuatFloat*	bc = (CrankQuatFloat*)b;
	
	return ((ac->w == bc->w) && (ac->x == bc->x) && (ac->y == bc->y) && (ac->z == bc->z));
}

/**
 * crank_quat_float_equal_delta:
 * @a: A Quaternion.
 * @b: A Quaternion.
 * @d: Delta value.
 *
 * Checks two quaterniones are sufficiently equal, which means they are close to
 * each other so that we can say they are almost equal.
 *
 * Differences are calculated by distance between them.
 *
 * Returns: whether they are equal.
 */
gboolean
crank_quat_float_equal_delta (	CrankQuatFloat*	a,
								CrankQuatFloat*	b,
								const gfloat	d	)
{
	CrankQuatFloat	diff;
	crank_quat_float_sub (b, a, &diff);
	
	return (crank_quat_float_get_norm (&diff) <= d);
}

/**
 * crank_quat_float_hash:
 * @a: (type CrankQuatFloat): A Quaternion.
 *
 * Returns hash value of quaternion. This is useful when using Quaternion values
 * with #GHashTable.
 *
 * Returns: A hash value.
 */
guint
crank_quat_float_hash (		gconstpointer	a	)
{
	CrankQuatFloat*	ac = (CrankQuatFloat*)a;
	
	gdouble	w = ac->w;
	gdouble x = ac->x;
	gdouble y = ac->y;
	gdouble z = ac->z;
	
	return ( ( (g_double_hash (&w) * 33 +
			     g_double_hash (&x)) * 33 +
			      g_double_hash (&y)) * 33 +
			       g_double_hash (&z));
}

/**
 * crank_quat_float_to_string:
 * @quat: A Quaternion value.
 *
 * Stringify a quaternion value as,
 *
 * |[ 
 *    3.2 + (-1.34i) + (2.23j) + (3.13k)
 * ]|
 * 
 * Returns: String representation of quaternion. Free with g_free()
 */
gchar*
crank_quat_float_to_string (	CrankQuatFloat*	quat	)
{
	return crank_quat_float_to_string_full (	quat, CRANK_QUAT_FLOAT_DEFFORMAT);
}

/**
 * crank_quat_float_to_string_full:
 * @quat: A Quaternion value.
 * @format: A format to stringify quaternion - consumes 2 parameters.
 *
 * Stringify quaternion value into string.
 *
 * It internally uses g_strdup_printf(), so @format consumes 4 float parameters,
 * for real value, first imaginary value, ....
 *
 * Returns: String representation of quaternion. Free with g_free()
 */
gchar*		crank_quat_float_to_string_full (	CrankQuatFloat*	quat,
												const gchar*	format	)
{
	return g_strdup_printf (format, quat->w, quat->x, quat->y, quat->z);
}

//////// Unary Operations //////////////////////////////////////////////////////

/**
 * crank_quat_float_get_wx:
 * @quat: A Quaternion value.
 * @wx: (out): Value of wx
 *
 * Gets values of first 2 parts as #CrankCplxFloat.
 */
void
crank_quat_float_get_wx (	CrankQuatFloat*	quat,
							CrankCplxFloat*	wx		)
{
	wx->real = quat->w;
	wx->imag = quat->x;
}

/**
 * crank_quat_float_get_yz:
 * @quat: A Quaternion value.
 * @yz: (out): Value of yz
 *
 * Gets values of last 2 parts as #CrankCplxFloat.
 */
void
crank_quat_float_get_yz (	CrankQuatFloat*	quat,
							CrankCplxFloat*	yz		)
{
	yz->real = quat->y;
	yz->imag = quat->z;
}

/**
 * crank_quat_float_get_imag:
 * @quat: A Quaternion value.
 * @imag: (out): Imaginary value of quaternion.
 *
 * Gets values of 3 imaginary parts as #CrankVecFloat3.
 */
void
crank_quat_float_get_imag (	CrankQuatFloat*	quat,
							CrankVecFloat3*	imag		)
{
	imag->x = quat->x;
	imag->y = quat->y;
	imag->z = quat->z;
}

/**
 * crank_quat_float_set_wx:
 * @quat: A Quaternion value.
 * @wx: Value of wx
 *
 * Sets values of first 2 parts by #CrankCplxFloat.
 */
void
crank_quat_float_set_wx (	CrankQuatFloat*	quat,
							CrankCplxFloat*	wx		)
{
	quat->w = wx->real;
	quat->x = wx->imag;
}

/**
 * crank_quat_float_set_yz:
 * @quat: A Quaternion value.
 * @yz: Value of yz
 *
 * Sets values of last 2 parts by #CrankCplxFloat.
 */
void
crank_quat_float_set_yz (	CrankQuatFloat*	quat,
							CrankCplxFloat*	yz		)
{
	quat->y = yz->real;
	quat->z = yz->imag;
}

/**
 * crank_quat_float_set_imag:
 * @quat: A Quaternion value.
 * @imag: Imaginary value of quaternion.
 *
 * Sets values of 3 imaginary parts by #CrankVecFloat3.
 */
void
crank_quat_float_set_imag (	CrankQuatFloat*	quat,
							CrankVecFloat3*	imag		)
{
	quat->x = imag->x;
	quat->y = imag->y;
	quat->z = imag->z;
}

/**
 * crank_quat_float_get_norm_sq:
 * @quat: A Quaternion.
 *
 * Gets square of norm.
 * 
 * Returns: Square of norm of quaternion.
 */
gfloat
crank_quat_float_get_norm_sq (	CrankQuatFloat*	quat	)
{
	return (quat->w * quat->w) + (quat->x * quat->x) + (quat->y * quat->y) + (quat->z * quat->z);
}

/**
 * crank_quat_float_get_norm:
 * @quat: A Quaternion.
 * 
 * Gets norm of quaternion.
 *
 * Returns: Norm.
 */
gfloat
crank_quat_float_get_norm (		CrankQuatFloat*	quat	)
{
	return sqrtf(crank_quat_float_get_norm_sq(quat));
}

/**
 * crank_quat_float_conjugate:
 * @a: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a conjugate.
 */
void
crank_quat_float_conjugate (	CrankQuatFloat*	a,
								CrankQuatFloat*	r	)
{
	r->w = a->w;
	r->x = - a->x;
	r->y = - a->y;
	r->z = - a->z;
}

/**
 * crank_quat_float_neg:
 * @a: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a negation. (- @a)
 */
void
crank_quat_float_neg (	CrankQuatFloat*	a,
						CrankQuatFloat*	r	)
{
	r->w = - a->w;
	r->x = - a->x;
	r->y = - a->y;
	r->z = - a->z;
}

/**
 * crank_quat_float_inverse:
 * @a: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a invert. (1 / @a)
 */
void
crank_quat_float_inverse (	CrankQuatFloat*	a,
							CrankQuatFloat*	r	)
{
	gfloat norm_sq_inv = 1 / crank_quat_float_get_norm_sq (a);
	
	r->w = a->w * norm_sq_inv;
	r->x = -a->x * norm_sq_inv;
	r->y = -a->y * norm_sq_inv;
	r->z = -a->z * norm_sq_inv;
}

/**
 * crank_quat_float_unit:
 * @a: A Quaternion
 * @r: (out): A Quaternion to store result.
 * 
 * Gets unit quaternion. (@a / |@a|)
 */
void
crank_quat_float_unit (	CrankQuatFloat*	a,
						CrankQuatFloat*	r	)
{
	gfloat	norm = crank_quat_float_get_norm (a);
	
	crank_quat_float_divr (a, norm, r);
}



/**
 * crank_quat_float_conjugate_self:
 * @a: A Quaternion.
 *
 * Sets @a as conjugate of itself.
 */
void
crank_quat_float_conjugate_self (	CrankQuatFloat*	a	)
{
	a->x = - a->x;
	a->y = - a->y;
	a->z = - a->z;
}

/**
 * crank_quat_float_neg_self:
 * @a: A Quaternion.
 *
 * Sets @a as negation of itself. (- @a)
 */
void
crank_quat_float_neg_self (	CrankQuatFloat*	a	)
{
	a->w = - a->w;
	a->x = - a->x;
	a->y = - a->y;
	a->z = - a->z;
}

/**
 * crank_quat_float_inverse_self:
 * @a: A Quaternion.
 *
 * Sets @a as invert of self. (1 / @a)
 */
void
crank_quat_float_inverse_self (	CrankQuatFloat*	a	)
{
	gfloat norm_sq_inv = 1 / crank_quat_float_get_norm_sq (a);
	
	a->w *= norm_sq_inv;
	a->x *= -norm_sq_inv;
	a->y *= -norm_sq_inv;
	a->z *= -norm_sq_inv;
}

/**
 * crank_quat_float_unit_self:
 * @a: A Quaternion
 * 
 * Sets @a as its unit quaternion. (@a / |@a|)
 */
void
crank_quat_float_unit_self (	CrankQuatFloat*	a	)
{
	gfloat	norm = crank_quat_float_get_norm (a);
	
	crank_quat_float_divr_self (a, norm);
}

//////// Quat - Real Operations ////////////////////////////////////////////////

/**
 * crank_quat_float_addr:
 * @a: A Quaternion.
 * @b: A real value.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a addition of quaternion and scalar.
 */
void
crank_quat_float_addr (	CrankQuatFloat*	a,
						gfloat			b,
						CrankQuatFloat*	r		)
{
	r->w = a->w + b;
	r->x = a->x;
	r->y = a->y;
	r->z = a->z;
}

/**
 * crank_quat_float_subr:
 * @a: A Quaternion.
 * @b: A real value.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a subtration of quaternion by scalar.
 */
void
crank_quat_float_subr (	CrankQuatFloat*	a,
						gfloat			b,
						CrankQuatFloat*	r		)
{
	r->w = a->w - b;
	r->x = a->x;
	r->y = a->y;
	r->z = a->z;
}

/**
 * crank_quat_float_mulr:
 * @a: A Quaternion.
 * @b: A real value.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a multiplication of quaternion by scalar.
 */
void
crank_quat_float_mulr (	CrankQuatFloat*	a,
						gfloat			b,
						CrankQuatFloat*	r		)
{
	r->w = a->w * b;
	r->x = a->x * b;
	r->y = a->y * b;
	r->z = a->z * b;
}

/**
 * crank_quat_float_divr:
 * @a: A Quaternion.
 * @b: A real value.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a division of quaternion by scalar.
 */
void
crank_quat_float_divr (	CrankQuatFloat*	a,
						gfloat			b,
						CrankQuatFloat*	r		)
{
	gfloat	b_inv = 1 / b;
	r->w = a->w * b_inv;
	r->x = a->x * b_inv;
	r->y = a->y * b_inv;
	r->z = a->z * b_inv;
}




/**
 * crank_quat_float_addr_self:
 * @a: A Quaternion.
 * @b: A real value.
 *
 * Applies a addition by scalar to a quaternion.
 */
void
crank_quat_float_addr_self (	CrankQuatFloat*	a,
								gfloat			b		)
{
	a->w += b;
}

/**
 * crank_quat_float_subr_self:
 * @a: A Quaternion.
 * @b: A real value.
 *
 * Applies a subtration by scalar to a quaternion.
 */
void
crank_quat_float_subr_self (	CrankQuatFloat*	a,
								gfloat			b		)
{
	a->w -= b;
}

/**
 * crank_quat_float_mulr_self:
 * @a: A Quaternion.
 * @b: A real value.
 *
 * Applies a multiplication by scalar to a quaternion.
 */
void
crank_quat_float_mulr_self (	CrankQuatFloat*	a,
								gfloat			b		)
{
	a->w *= b;
	a->x *= b;
	a->y *= b;
	a->z *= b;
}

/**
 * crank_quat_float_divr_self:
 * @a: A Quaternion.
 * @b: A real value.
 *
 * Applies a division by scalar to a quaternion.
 */
void
crank_quat_float_divr_self (	CrankQuatFloat*	a,
								gfloat			b		)
{
	gfloat	b_inv = 1 / b;
	a->w *= b_inv;
	a->x *= b_inv;
	a->y *= b_inv;
	a->z *= b_inv;
}

//////// Real - Quat Operations ////////////////////////////////////////////////

/**
 * crank_quat_float_rsubr:
 * @a: A Quaternion.
 * @b: A real value.
 * @r: (out): A Quaternion to store result.
 *
 * Gets subtraction of scalar by quaternion.
 */
void
crank_quat_float_rsubr (	CrankQuatFloat*	a,
							gfloat			b,
							CrankQuatFloat*	r		)
{
	r->w = b - a->w;
	r->x = - a->x;
	r->y = - a->y;
	r->z = - a->z;
}

/**
 * crank_quat_float_rdivr:
 * @a: A Quaternion.
 * @b: A real value.
 * @r: (out): A Quaternion to store result.
 *
 * Gets division of scalar by quaternion.
 */
void
crank_quat_float_rdivr (	CrankQuatFloat*	a,
							gfloat			b,
							CrankQuatFloat*	r		)
{
	gfloat b_over_norm_sq = b / crank_quat_float_get_norm_sq (a);
	
	r->w = a->w * b_over_norm_sq;
	r->x = -a->x * b_over_norm_sq;
	r->y = -a->y * b_over_norm_sq;
	r->z = -a->z * b_over_norm_sq;
}


//////// Quat - Cplx Operations ////////////////////////////////////////////////

/**
 * crank_quat_float_addc:
 * @a: A Quaternion.
 * @b: A Complex.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a addition of quaternion and complex.
 */
void
crank_quat_float_addc (	CrankQuatFloat*	a,
						CrankCplxFloat*	b,
						CrankQuatFloat*	r	)
{
	r->w = a->w + b->real;
	r->x = a->x + b->imag;
	r->y = a->y;
	r->z = a->z;
}
										
/**
 * crank_quat_float_subc:
 * @a: A Quaternion.
 * @b: A Complex.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a subtration of quaternion by complex.
 */
void
crank_quat_float_subc (	CrankQuatFloat*	a,
						CrankCplxFloat*	b,
						CrankQuatFloat*	r	)
{
	r->w = a->w - b->real;
	r->x = a->x - b->imag;
	r->y = a->y;
	r->z = a->z;
}

/**
 * crank_quat_float_mulc:
 * @a: A Quaternion.
 * @b: A Complex.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a multiplication of quaternion by complex.
 */
void
crank_quat_float_mulc (	CrankQuatFloat*	a,
						CrankCplxFloat*	b,
						CrankQuatFloat*	r	)
{
	r->w = (a->w * b->real) - (a->x * b->imag);
	r->x = (a->x * b->real) + (a->w * b->imag);
	r->y = (a->y * b->real) + (a->z * b->imag);
	r->z = (a->z * b->real) - (a->y * b->imag);
}

/**
 * crank_quat_float_addc_self:
 * @a: A Quaternion.
 * @b: A Complex.
 *
 * Applies a addition by a complex.
 */
void
crank_quat_float_addc_self (	CrankQuatFloat*	a,
								CrankCplxFloat*	b	)
{
	a->w += b->real;
	a->x += b->imag;
}
										
/**
 * crank_quat_float_subc_self:
 * @a: A Quaternion.
 * @b: A Complex.
 *
 * Applies a subtration by a complex.
 */
void
crank_quat_float_subc_self (	CrankQuatFloat*	a,
								CrankCplxFloat*	b	)
{
	a->w -= b->real;
	a->x -= b->imag;
}

/**
 * crank_quat_float_mulc_self:
 * @a: A Quaternion.
 * @b: A Complex.
 *
 * Applies a multiplication by a complex.
 */
void
crank_quat_float_mulc_self (	CrankQuatFloat*	a,
								CrankCplxFloat*	b	)
{
	CrankQuatFloat	result;
	crank_quat_float_mulc (a, b, &result);
	crank_quat_float_copy (&result, a);
}


//////// Quat - Quat Operations ////////////////////////////////////////////////

/**
 * crank_quat_float_add:
 * @a: A Quaternion.
 * @b: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a addition of two quaternion.
 */
void
crank_quat_float_add (	CrankQuatFloat*	a,
						CrankQuatFloat*	b,
						CrankQuatFloat*	r	)
{
	r->w = a->w + b->w;
	r->x = a->x + b->x;
	r->y = a->y + b->y;
	r->z = a->z + b->z;
}
										
/**
 * crank_quat_float_sub:
 * @a: A Quaternion.
 * @b: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a subtration of two quaternion.
 */
void
crank_quat_float_sub (	CrankQuatFloat*	a,
						CrankQuatFloat*	b,
						CrankQuatFloat*	r	)
{
	r->w = a->w - b->w;
	r->x = a->x - b->x;
	r->y = a->y - b->y;
	r->z = a->z - b->z;
}

/**
 * crank_quat_float_mul:
 * @a: A Quaternion.
 * @b: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a multiplication of two quaternion.
 */
void
crank_quat_float_mul (	CrankQuatFloat*	a,
						CrankQuatFloat*	b,
						CrankQuatFloat*	r	)
{
	r->w = (a->w * b->w) - (a->x * b->x) - (a->y * b->y) - (a->z * b->z);
	r->x = (a->x * b->w) + (a->w * b->x) - (a->z * b->y) + (a->y * b->z);
	r->y = (a->y * b->w) + (a->z * b->x) + (a->w * b->y) - (a->x * b->z);
	r->z = (a->z * b->w) - (a->y * b->x) + (a->x * b->y) + (a->w * b->z);
}

/**
 * crank_quat_float_add_self:
 * @a: A Quaternion.
 * @b: A Quaternion.
 *
 * Applies a addition by a quaternion.
 */
void
crank_quat_float_add_self (	CrankQuatFloat*	a,
							CrankQuatFloat*	b	)
{
	a->w += b->w;
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}
										
/**
 * crank_quat_float_sub_self:
 * @a: A Quaternion.
 * @b: A Quaternion.
 *
 * Applies a subtration by a quaternion.
 */
void
crank_quat_float_sub_self (	CrankQuatFloat*	a,
							CrankQuatFloat*	b	)
{
	a->w -= b->w;
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

/**
 * crank_quat_float_mul_self:
 * @a: A Quaternion.
 * @b: A Quaternion.
 *
 * Applies a multiplication by a quaternion.
 */
void
crank_quat_float_mul_self (	CrankQuatFloat*	a,
							CrankQuatFloat*	b	)
{
	CrankQuatFloat	result;
	crank_quat_float_mul (a, b, &result);
	crank_quat_float_copy (&result, a);
}

/**
 * crank_quat_float_mul_conj:
 * @a: A Quaternion.
 * @b: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Multiplies @a with conjugate of @b.
 */
void		crank_quat_float_mul_conj (	CrankQuatFloat*	a,
										CrankQuatFloat*	b,
										CrankQuatFloat*	r	)
{
	r->w = (a->w * b->w) + (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	r->x = (a->x * b->w) - (a->w * b->x) + (a->z * b->y) - (a->y * b->z);
	r->y = (a->y * b->w) - (a->z * b->x) - (a->w * b->y) + (a->x * b->z);
	r->z = (a->z * b->w) + (a->y * b->x) - (a->x * b->y) - (a->w * b->z);
}

//////// Ternary Operations ////////////////////////////////////////////////////

/**
 * crank_quat_float_mix:
 * @a: A Quaternion.
 * @b: A Quaternion.
 * @c: A scalar.
 * @r: (out): A Quaternion to store result.
 *
 * Gets a mixture of two quaternion.
 */
void
crank_quat_float_mix (	CrankQuatFloat*	a,
						CrankQuatFloat*	b,
						gfloat			c,
						CrankQuatFloat*	r	)
{
	gfloat	d = 1 - c;
	
	r->w = (a->w * d) + (b->w * c);
	r->x = (a->x * d) + (b->x * c);
	r->y = (a->y * d) + (b->y * c);
	r->z = (a->z * d) + (b->z * c);
}


//////// Exponential Operations ////////////////////////////////////////////////

/**
 * crank_quat_float_ln:
 * @a: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets Natural log from a quaternion.
 *
 * As periodic characteristic of exponential, returned quaternion will have
 * imaginary part in [0, 2 * PI} or being NAN (if @a is 0)
 */
void
crank_quat_float_ln (	CrankQuatFloat*	a,
						CrankQuatFloat*	r	)
{
	CrankVecFloat3*	imag = (CrankVecFloat3*) (& a->x);

	gfloat		norm;
	gfloat		norm_imag;
	gfloat		ac;
	
	norm = crank_quat_float_get_norm (a);
	norm_imag = crank_vec_float3_get_magn (imag);
	ac = acosf (a->w / norm);
	
	r->w = logf (norm);
	r->x = a->x * ac / norm_imag;
	r->y = a->y * ac / norm_imag;
	r->z = a->z * ac / norm_imag;
}

/**
 * crank_quat_float_exp:
 * @a: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets e-based exponential of quaternion.
 */
void
crank_quat_float_exp (	CrankQuatFloat*	a,
						CrankQuatFloat*	r	)
{
	CrankVecFloat3*	imag = (CrankVecFloat3*) (& a->x);
	
	gfloat			exp_w;
	gfloat			norm_imag;
	gfloat			c;
	gfloat			s;
	
	exp_w = expf (a->w);
	norm_imag = crank_vec_float3_get_magn (imag);
	
	c = cosf (norm_imag);
	s = sinf (norm_imag);

	r->w = exp_w * c;
	r->x = exp_w * s * a->x / norm_imag;
	r->y = exp_w * s * a->y / norm_imag;
	r->z = exp_w * s * a->z / norm_imag;
}

/**
 * crank_quat_float_powr:
 * @a: A Quaternion.
 * @b: A Quaternion.
 * @r: (out): A Quaternion to store result.
 *
 * Gets power of quaternion over real exponents.
 */
void
crank_quat_float_powr (	CrankQuatFloat*	a,
						const gfloat 	b,
						CrankQuatFloat*	r	)
{
	CrankVecFloat3*	imag = (CrankVecFloat3*) (& a->x);
	
	gfloat	norm;
	gfloat	norm_imag;
	
	gfloat	norm_b;
	gfloat	angle;
	
	gfloat	c;
	gfloat	s;
	
	norm = crank_quat_float_get_norm (a);
	norm_imag = crank_vec_float3_get_magn (imag);
	
	norm_b = powf (norm, b);
	angle = b * acos (a->w / norm);
	
	c = cosf (angle);
	s = sinf (angle);
	
	r->w = norm_b * c;
	r->x = norm_b * s * a->x / norm_imag;
	r->y = norm_b * s * a->y / norm_imag;
	r->z = norm_b * s * a->z / norm_imag;
}
