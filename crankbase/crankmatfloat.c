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

#include <string.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankfunction.h"
#include "crankveccommon.h"
#include "crankvecfloat.h"

#include "crankmatfloat.h"

G_DEFINE_BOXED_TYPE (CrankMatFloat2, crank_mat_float2, crank_mat_float2_dup, g_free)


/**
 * SECTION: crankmatfloat
 * @title: Float Matrices.
 * @short_description: Float valued matrices.
 * @stability: unstable
 * @include: crankbase.h
 *
 * Crank System provides 2x2 sized float vectors for convenience.
 *
 * Currently following operations are supported.
 *
 * It is compared to mat in GLSL
 *
 * * Basic Operations
 *    * hashing
 *    * equality check
 *    * stringify
 * * Matrix properties
 *    * trace
 *    * determinent
 *    * cofactor and adjugate matrices
 * * Unary operations
 *    * negate
 *    * transpose
 *    * inverse
 * * Scalar operations
 *    * Scalar multiplication
 *    * Scalar division
 * * Vector operations
 *    * Vector multiplication (Matrix * Vector)
 * * Matrix operations
 *    * Matrix multiplication
 * * Ternary Operations
 *    * Mixing by scalar
 *    * Component mixing by matrix.
 */



/**
 * crank_mat_float2_init:
 * @mat: (out): A Matrix.
 * @m00: Matrix element.
 * @m01: Matrix element.
 * @m10: Matrix element.
 * @m11: Matrix element.
 *
 * Initialize a matrix with given elements.
 */
void
crank_mat_float2_init (	CrankMatFloat2*	mat,
					   	const gfloat	m00,
					   	const gfloat	m01,
					   	const gfloat	m10,
					   	const gfloat	m11	)
{
	mat->m00 = m00;
  	mat->m01 = m01;
  	mat->m10 = m10;
  	mat->m11 = m11;
}

/**
 * crank_mat_float2_init_arr:
 * @mat: (out): A Matrix.
 * @marr: (array fixed-size=4): An array of matrix.
 *
 * Initialize a matrix with given array.
 */
void
crank_mat_float2_init_arr (	CrankMatFloat2* mat,
						   	const gfloat*	marr	)
{
	memcpy (mat, marr, sizeof(gfloat) * 4);
}

/**
 * crank_mat_float2_init_rv:
 * @mat: (out): A Matrix.
 * @rv0: A Row vector.
 * @rv1: A Row vector.
 *
 * Initialize a matrix with given row vectors.
 */
void
crank_mat_float2_init_rv (	CrankMatFloat2*	mat,
						  	CrankVecFloat2*	rv0,
						  	CrankVecFloat2*	rv1	)
{
	crank_vec_float2_init_arr ((CrankVecFloat2*)mat,       (gfloat*)rv0);
	crank_vec_float2_init_arr (((CrankVecFloat2*)mat) + 1, (gfloat*)rv1);
}

/**
 * crank_mat_float2_init_rvarr:
 * @mat: (out): A Matrix.
 * @rvarr: (array fixed-size=2): An array of row vectors.
 *
 * Initialize a matrix with array of row vectors.
 */
void
crank_mat_float2_init_rvarr (	CrankMatFloat2*		mat,
 								CrankVecFloat2**	rvarr	)
{
	crank_mat_float2_init_rv (mat, rvarr[0], rvarr[1]);
}

/**
 * crank_mat_float2_init_cv:
 * @mat: (out): A Matrix.
 * @cv0: A Column Vector.
 * @cv1: A Column Vector.
 *
 * Initialize a matrix with column vectors.
 */
void
crank_mat_float2_init_cv (	CrankMatFloat2*	mat,
						  	CrankVecFloat2*	cv0,
						  	CrankVecFloat2*	cv1	)
{
	mat->m00 = cv0->x;
  	mat->m01 = cv1->x;
	mat->m10 = cv0->y;
  	mat->m11 = cv1->y;
}

/**
 * crank_mat_float2_init_cvarr:
 * @mat: (out): A Matrix.
 * @cvarr: (array fixed-size=2): An array of column vectors.
 *
 * Initialize a matrix with an array of column vectors.
 */
void
crank_mat_float2_init_cvarr (	CrankMatFloat2* 	mat,
							 	CrankVecFloat2**	cvarr	)
{
	crank_mat_float2_init_cv (mat, cvarr[0], cvarr[1]);
}

/**
 * crank_mat_float2_init_diag:
 * @mat: (out): A Matrix.
 * @m00: A diagonal element.
 * @m11: A diagonal element.
 *
 * Initialize a matrix with diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_float2_init_diag (	CrankMatFloat2*	mat,
								const gfloat	m00,
								const gfloat	m11	)
{
  	mat->m00 = m00;
  	mat->m01 = 0;
  	mat->m10 = 0;
  	mat->m11 = m11;
}

/**
 * crank_mat_float2_init_diag_arr:
 * @mat: (out): A Matrix.
 * @darr: (array fixed-size=2): An array of diagonal elements.
 *
 * Initialize a matrix with an array of diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_float2_init_diag_arr (	CrankMatFloat2*	mat,
									const gfloat*	darr	)
{
	crank_mat_float2_init_diag (mat, darr[0], darr[1]);
}

/**
 * crank_mat_float2_init_fill:
 * @mat: (out): A Matrix.
 * @fill: A fill value to fill the matrix.
 *
 * Initialize a matrix by filling with a value.
 */
void
crank_mat_float2_init_fill (	CrankMatFloat2*	mat,
								const gfloat	fill	)
{
	mat->m00 = fill;
  	mat->m01 = fill;
  	mat->m10 = fill;
  	mat->m11 = fill;
}

/**
 * crank_mat_float2_copy:
 * @mat: A Matrix.
 * @other: (out): Another matrix.
 *
 * Copies a matrix to other matrix.
 */
void
crank_mat_float2_copy (	CrankMatFloat2*	mat,
					   	CrankMatFloat2*	other	)
{
	crank_mat_float2_init_arr (other, (gfloat*) mat);
}

/**
 * crank_mat_float2_dup:
 * @mat: A Matrix
 *
 * Allocates a matrix and copy on it.
 *
 * Returns: an allocated copy. Free it with g_free()
 */
CrankMatFloat2*
crank_mat_float2_dup (	CrankMatFloat2*	mat	)
{
  	CrankMatFloat2*	result = g_new (CrankMatFloat2, 1);
	crank_mat_float2_copy (mat, result);
  	return result;
}


//////// Basic Operations //////////////////////////////////////////////////////

/**
 * crank_mat_float2_hash:
 * @a: (type CrankMatFloat2): A matrix.
 *
 * Gets hash value of a matrix.
 * This is useful when using matrix as key or value for #GHashTable.
 *
 * Returns: hash value of a matrix.
 */
guint
crank_mat_float2_hash (	gconstpointer	a	)
{
	const CrankMatFloat2*	mat = (const CrankMatFloat2*)a;

  	gdouble dm00 = mat->m00;
  	gdouble dm01 = mat->m01;
  	gdouble dm10 = mat->m10;
  	gdouble dm11 = mat->m11;

  	return	g_double_hash (&dm00) +
  			g_double_hash (&dm01) +
  			g_double_hash (&dm10) +
  			g_double_hash (&dm11);
}

/**
 * crank_mat_float2_equal:
 * @a: (type CrankMatFloat2): A matrix.
 * @b: (type CrankMatFloat2): A matrix.
 *
 * Compares the value of matrix and check their equality.
 * This is useful when using matrix as a key.
 *
 * Returns: %TRUE if the two are same.
 */
gboolean
crank_mat_float2_equal (	gconstpointer	a,
							gconstpointer	b	)
{
	const CrankMatFloat2*	mat_a = (const CrankMatFloat2*)a;
	const CrankMatFloat2*	mat_b = (const CrankMatFloat2*)b;

  	return	(mat_a->m00 == mat_b->m00) &&
  			(mat_a->m01 == mat_b->m01) &&
  			(mat_a->m10 == mat_b->m10) &&
  			(mat_a->m11 == mat_b->m11);
}

/**
 * crank_mat_float2_to_string:
 * @mat: A Matrix.
 *
 * Stringify a matrix to string.
 * A typical identity matrix can be expressed like below.
 *
 * |[
 *     [[1.000, 0.000], [0.000, 1.000]]
 * ]|
 *
 * Returns: string representation of matrix.
 */
gchar*
crank_mat_float2_to_string (	CrankMatFloat2*	mat	)
{
  	return crank_mat_float2_to_string_full (mat, "[", ", ", "]", "[", ", ", "]", "%g");
}

/**
 * crank_mat_float2_to_string_full:
 * @mat: A Matrix.
 * @mat_left: Start of matrix.
 * @mat_in: Divider for row vectors.
 * @mat_right: End of matrix.
 * @row_left: Start of row.
 * @row_in: Divider for elements.
 * @row_right: End of matrix.
 * @format: Format for each element. should consume 1 float parameter.
 *
 * Stringify a matrix to string, with given parts.
 *
 * Returns: string representation of matrix.
 */
gchar*
crank_mat_float2_to_string_full (	CrankMatFloat2*	mat,
								 	const gchar*	mat_left,
								 	const gchar*	mat_in,
								 	const gchar*	mat_right,
								 	const gchar*	row_left,
								 	const gchar*	row_in,
								 	const gchar*	row_right,
								 	const gchar*	format	)
{
  	GString*	builder;
	gchar*		str;

  	builder = g_string_new (mat_left);
  	g_string_append (builder,
			crank_vec_float2_to_string_full (((CrankVecFloat2*)mat) + 0, row_left, row_in, row_right, format)	);

	g_string_append (builder, mat_in);
  	g_string_append (builder,
			crank_vec_float2_to_string_full (((CrankVecFloat2*)mat) + 1, row_left, row_in, row_right, format)	);

  	g_string_append (builder, mat_right);

	str = builder->str;

	g_string_free (builder, FALSE);
	return str;
}

/**
 * crank_mat_float2_get:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 *
 * Gets element at given indices.
 *
 * Returns: Element at given indices.
 */
gfloat
crank_mat_float2_get (	CrankMatFloat2*	mat,
					  	const guint		i,
					  	const guint		j	)
{
	return ((gfloat*)mat) [(2 * i)  +  j];
}

/**
 * crank_mat_float2_set:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 * @value: Value of element.
 *
 * Sets element at given indices.
 */
void
crank_mat_float2_set (	CrankMatFloat2*	mat,
					  	const guint		i,
					  	const guint		j,
					  	const gfloat	value	)
{
	((gfloat*)mat) [(2 * i)  +  j] = value;
}

/**
 * crank_mat_float2_get_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: (out): A Row vector.
 *
 * Gets a row vector at given index.
 */
void
crank_mat_float2_get_row (	CrankMatFloat2*	mat,
						  	const guint		index,
						  	CrankVecFloat2*	row	)
{
  	crank_vec_float2_init_arr (row, ((gfloat*)mat) + 2 * index);
}

/**
 * crank_mat_float2_set_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: A Row vector.
 *
 * Sets a row vector at given index.
 */
void
crank_mat_float2_set_row (	CrankMatFloat2*	mat,
						  	const guint		index,
						  	CrankVecFloat2*	row	)
{
  	crank_vec_float2_init_arr (((CrankVecFloat2*)mat) + index, (gfloat*)row);
}


/**
 * crank_mat_float2_get_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: (out): A Column vector.
 *
 * Gets a column vector at given index.
 */
void
crank_mat_float2_get_col (	CrankMatFloat2*	mat,
						  	const guint		index,
						  	CrankVecFloat2*	col	)
{
  	gfloat*	ptr = ((gfloat*)mat) + index;
	col->x = ptr[0];
  	col->y = ptr[2];
}

/**
 * crank_mat_float2_set_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: A Column vector.
 *
 * Sets a column vector at given index.
 */
void
crank_mat_float2_set_col (	CrankMatFloat2*	mat,
						  	const guint		index,
						  	CrankVecFloat2*	col	)
{
  	gfloat*	ptr = ((gfloat*)mat) + index;
  	ptr[0] = col->x;
 	ptr[2] = col->y;
}

/**
 * crank_mat_float2_get_tr:
 * @mat: A Matrix
 *
 * Gets a trace of matrix.
 *
 * A trace is sum of diagonal elements.
 *
 * Returns: A trace of matrix.
 */
gfloat
crank_mat_float2_get_tr (	CrankMatFloat2*	mat	)
{
  	return	mat->m00 + mat->m11;
}

/**
 * crank_mat_float2_get_det:
 * @mat: A Matrix
 *
 * Gets a determinent of matrix.
 *
 * Returns: A determinent of matrix.
 */
gfloat
crank_mat_float2_get_det (	CrankMatFloat2* mat	)
{
  	return	(mat->m00 * mat->m11) -
  			(mat->m01 * mat->m10);
}

/**
 * crank_mat_float2_get_cof:
 * @mat: A Matrix.
 * @r: (out): A cofactor matrix.
 *
 * Gets a cofactor matrix.
 */
void
crank_mat_float2_get_cof (	CrankMatFloat2*	mat,
						  	CrankMatFloat2*	r	)
{
	r->m00 = 	mat->m11;
  	r->m01 = -	mat->m10;
  	r->m10 = -	mat->m01;
  	r->m11 = 	mat->m00;
}

/**
 * crank_mat_float2_get_adj:
 * @mat: A Matrix.
 * @r: (out): A adjugate matrix.
 *
 * Gets a adjugate matrix.
 */
void
crank_mat_float2_get_adj (	CrankMatFloat2*	mat,
						  	CrankMatFloat2*	r	)
{
	crank_mat_float2_get_cof (mat, r);
  	crank_mat_float2_transpose (r, r);
}

/**
 * crank_mat_float2_neg:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Negates a matrix.
 */
void
crank_mat_float2_neg (	CrankMatFloat2*	a,
					  	CrankMatFloat2* r	)
{
	r->m00 = - a->m00;
  	r->m01 = - a->m01;
  	r->m10 = - a->m10;
  	r->m11 = - a->m11;
}

/**
 * crank_mat_float2_transpose:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets a transpose of matrix.
 */
void
crank_mat_float2_transpose (	CrankMatFloat2*	a,
								CrankMatFloat2*	r	)
{
  	if (a != r) {
		r->m00 = a->m00;
	  	r->m01 = a->m10;
	  	r->m10 = a->m01;
	  	r->m11 = a->m11;
	}
  	else {
	  	gfloat temp;

	  	temp = a->m01;
	  	a->m01 = a->m10;
	  	a->m10 = temp;
	}
}

/**
 * crank_mat_float2_inverse:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets an inverse of matrix.
 * If the matrix is singular, then NaN matrix may be returned.
 */
void
crank_mat_float2_inverse (	CrankMatFloat2*	a,
						  	CrankMatFloat2*	r	)
{
  	gfloat	det = crank_mat_float2_get_det (a);

	if (a != r) {
		r->m00 = a->m11 / det;
		r->m11 = a->m00 / det;
		r->m01 = - a->m01 / det;
		r->m10 = - a->m10 / det;
	}
  	else {
		gfloat temp;

		temp = a->m00 / det;
	  	a->m00 = a->m11 / det;
	  	a->m11 = temp;

	  	a->m01 /= -det;
	  	a->m10 /= -det;
	}
}

/**
 * crank_mat_float2_muls:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by scalar.
 */
void
crank_mat_float2_muls (	CrankMatFloat2*	a,
					   	const gfloat	b,
					   	CrankMatFloat2*	r	)
{
	r->m00 = a->m00 * b;
	r->m01 = a->m01 * b;
	r->m10 = a->m10 * b;
	r->m11 = a->m11 * b;
}

/**
 * crank_mat_float2_divs:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Divides a matrix by scalar.
 */
void
crank_mat_float2_divs (	CrankMatFloat2*	a,
					   	const gfloat	b,
					   	CrankMatFloat2*	r	)
{
	r->m00 = a->m00 / b;
	r->m01 = a->m01 / b;
	r->m10 = a->m10 / b;
	r->m11 = a->m11 / b;
}


/**
 * crank_mat_float2_mulv:
 * @a: A Matrix.
 * @b: A Vector.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by vector.
 */
void
crank_mat_float2_mulv (	CrankMatFloat2*	a,
					   	CrankVecFloat2*	b,
					   	CrankVecFloat2*	r	)
{
	r->x = a->m00 * b->x + a->m01 * b->y;
  	r->y = a->m10 * b->x + a->m11 * b->y;
}

/**
 * crank_mat_float2_mul:
 * @a: A Matrix.
 * @b: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies two matrices.
 */
void
crank_mat_float2_mul (	CrankMatFloat2*	a,
					  	CrankMatFloat2* b,
					  	CrankMatFloat2* r	)
{
	CrankMatFloat2	nr;

  	nr.m00 = (a->m00 * b->m00) + (a->m01 * b->m10);
  	nr.m01 = (a->m00 * b->m01) + (a->m01 * b->m11);
  	nr.m10 = (a->m10 * b->m00) + (a->m11 * b->m10);
  	nr.m11 = (a->m10 * b->m01) + (a->m11 * b->m11);

  	crank_mat_float2_init_arr (r, (gfloat*)&nr);
}

/**
 * crank_mat_float2_mixs:
 * @a: A Matrix.
 * @b: A Matrix.
 * @c: A coefficient scalar.
 * @r: (out): A Matrix to store result.
 *
 * Mixes two matrix.
 *
 * The result is calculated by,
 * * (a * (1 - c)) + (b * c)
 */
void
crank_mat_float2_mixs (	CrankMatFloat2* a,
					  	CrankMatFloat2* b,
					  	const gfloat	c,
					  	CrankMatFloat2*	r	)
{
  	gfloat d = 1 - c;

	r->m00 = (a->m00 * d) + (b->m00 * c);
	r->m01 = (a->m01 * d) + (b->m01 * c);
	r->m10 = (a->m10 * d) + (b->m10 * c);
	r->m11 = (a->m11 * d) + (b->m11 * c);
}

/**
 * crank_mat_float2_mix:
 * @a: A Matrix
 * @b: A Matrix
 * @c: A coefficient matrix.
 * @r: (out): A Matrix to store result.
 *
 * Mixes two matrix.
 *
 * The result is calculated by,
 * * r[i, j] = (a[i, j] * (1 - c[i, j]) + (b[i, j] * c[i, j])
 */
void
crank_mat_float2_mix (	CrankMatFloat2*	a,
					  	CrankMatFloat2* b,
					  	CrankMatFloat2*	c,
					  	CrankMatFloat2*	r	)
{
	r->m00 = (a->m00 * (1 - c->m00)) + (b->m00 * c->m00);
	r->m01 = (a->m01 * (1 - c->m01)) + (b->m01 * c->m01);
	r->m10 = (a->m10 * (1 - c->m10)) + (b->m10 * c->m10);
	r->m11 = (a->m11 * (1 - c->m11)) + (b->m11 * c->m11);
}







G_DEFINE_BOXED_TYPE (CrankMatFloat3, crank_mat_float3, crank_mat_float3_dup, g_free)

/**
 * crank_mat_float3_init:
 * @mat: (out): A Matrix.
 * @m00: Matrix element.
 * @m01: Matrix element.
 * @m02: Matrix element.
 * @m10: Matrix element.
 * @m11: Matrix element.
 * @m12: Matrix element.
 * @m20: Matrix element.
 * @m21: Matrix element.
 * @m22: Matrix element.
 *
 * Initialize a matrix with given elements.
 */
void
crank_mat_float3_init (	CrankMatFloat3*	mat,
					   	const gfloat	m00,
					   	const gfloat	m01,
					   	const gfloat	m02,
					   	const gfloat	m10,
					   	const gfloat	m11,
					   	const gfloat	m12,
					   	const gfloat	m20,
					   	const gfloat	m21,
					   	const gfloat	m22	)
{
	mat->m00 = m00;
  	mat->m01 = m01;
  	mat->m02 = m02;
  	mat->m10 = m10;
  	mat->m11 = m11;
  	mat->m12 = m12;
  	mat->m20 = m20;
  	mat->m21 = m21;
  	mat->m22 = m22;
}

/**
 * crank_mat_float3_init_arr:
 * @mat: (out): A Matrix.
 * @marr: (array fixed-size=9): An array of matrix.
 *
 * Initialize a matrix with given array.
 */
void
crank_mat_float3_init_arr (	CrankMatFloat3* mat,
						   	const gfloat*	marr	)
{
	memcpy (mat, marr, sizeof(gfloat) * 9);
}

/**
 * crank_mat_float3_init_rv:
 * @mat: (out): A Matrix.
 * @rv0: A Row vector.
 * @rv1: A Row vector.
 * @rv2: A Row vector.
 *
 * Initialize a matrix with given row vectors.
 */
void
crank_mat_float3_init_rv (	CrankMatFloat3*	mat,
						  	CrankVecFloat3*	rv0,
						  	CrankVecFloat3*	rv1,
						  	CrankVecFloat3*	rv2	)
{
	crank_vec_float3_init_arr ((CrankVecFloat3*)mat,       (gfloat*)rv0);
	crank_vec_float3_init_arr (((CrankVecFloat3*)mat) + 1, (gfloat*)rv1);
	crank_vec_float3_init_arr (((CrankVecFloat3*)mat) + 2, (gfloat*)rv1);
}

/**
 * crank_mat_float3_init_rvarr:
 * @mat: (out): A Matrix.
 * @rvarr: (array fixed-size=3): An array of row vectors.
 *
 * Initialize a matrix with array of row vectors.
 */
void
crank_mat_float3_init_rvarr (	CrankMatFloat3*		mat,
 								CrankVecFloat3**	rvarr	)
{
	crank_mat_float3_init_rv (mat, rvarr[0], rvarr[1], rvarr[2]);
}

/**
 * crank_mat_float3_init_cv:
 * @mat: (out): A Matrix.
 * @cv0: A Column Vector.
 * @cv1: A Column Vector.
 * @cv2: A Column Vector.
 *
 * Initialize a matrix with column vectors.
 */
void
crank_mat_float3_init_cv (	CrankMatFloat3*	mat,
						  	CrankVecFloat3*	cv0,
						  	CrankVecFloat3*	cv1,
						  	CrankVecFloat3*	cv2	)
{
	mat->m00 = cv0->x;
  	mat->m01 = cv1->x;
  	mat->m02 = cv2->x;
	mat->m10 = cv0->y;
  	mat->m11 = cv1->y;
  	mat->m12 = cv2->y;
  	mat->m20 = cv0->z;
  	mat->m21 = cv1->z;
  	mat->m22 = cv2->z;
}

/**
 * crank_mat_float3_init_cvarr:
 * @mat: (out): A Matrix.
 * @cvarr: (array fixed-size=3): An array of column vectors.
 *
 * Initialize a matrix with an array of column vectors.
 */
void
crank_mat_float3_init_cvarr (	CrankMatFloat3* 	mat,
							 	CrankVecFloat3**	cvarr	)
{
	crank_mat_float3_init_cv (mat, cvarr[0], cvarr[1], cvarr[2]);
}

/**
 * crank_mat_float3_init_diag:
 * @mat: (out): A Matrix.
 * @m00: A diagonal element.
 * @m11: A diagonal element.
 * @m22: A diagonal element.
 *
 * Initialize a matrix with diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_float3_init_diag (	CrankMatFloat3*	mat,
								const gfloat	m00,
								const gfloat	m11,
								const gfloat	m22	)
{
  	mat->m00 = m00;
  	mat->m01 = 0;
  	mat->m02 = 0;
  	mat->m10 = 0;
  	mat->m11 = m11;
  	mat->m12 = 0;
  	mat->m20 = 0;
  	mat->m21 = 0;
  	mat->m22 = m22;
}

/**
 * crank_mat_float3_init_diag_arr:
 * @mat: (out): A Matrix.
 * @darr: (array fixed-size=3): An array of diagonal elements.
 *
 * Initialize a matrix with an array of diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_float3_init_diag_arr (	CrankMatFloat3*	mat,
									const gfloat*	darr	)
{
	crank_mat_float3_init_diag (mat, darr[0], darr[1], darr[2]);
}

/**
 * crank_mat_float3_init_fill:
 * @mat: (out): A Matrix.
 * @fill: A fill value to fill the matrix.
 *
 * Initialize a matrix by filling with a value.
 */
void
crank_mat_float3_init_fill (	CrankMatFloat3*	mat,
								const gfloat	fill	)
{
	mat->m00 = fill;
  	mat->m01 = fill;
  	mat->m02 = fill;
  	mat->m10 = fill;
  	mat->m11 = fill;
  	mat->m12 = fill;
  	mat->m20 = fill;
  	mat->m21 = fill;
  	mat->m22 = fill;
}

/**
 * crank_mat_float3_copy:
 * @mat: A Matrix.
 * @other: (out): Another matrix.
 *
 * Copies a matrix to other matrix.
 */
void
crank_mat_float3_copy (	CrankMatFloat3*	mat,
					   	CrankMatFloat3*	other	)
{
	crank_mat_float3_init_arr (other, (gfloat*) mat);
}

/**
 * crank_mat_float3_dup:
 * @mat: A Matrix
 *
 * Allocates a matrix and copy on it.
 *
 * Returns: an allocated copy. Free it with g_free()
 */
CrankMatFloat3*
crank_mat_float3_dup (	CrankMatFloat3*	mat	)
{
  	CrankMatFloat3*	result = g_new (CrankMatFloat3, 1);
	crank_mat_float3_copy (mat, result);
  	return result;
}


//////// Basic Operations //////////////////////////////////////////////////////

/**
 * crank_mat_float3_hash:
 * @a: (type CrankMatFloat3): A matrix.
 *
 * Gets hash value of a matrix.
 * This is useful when using matrix as key or value for #GHashTable.
 *
 * Returns: hash value of a matrix.
 */
guint
crank_mat_float3_hash (	gconstpointer	a	)
{
	const CrankMatFloat3*	mat = (const CrankMatFloat3*)a;

  	gdouble dm00 = mat->m00;
  	gdouble dm01 = mat->m01;
  	gdouble dm02 = mat->m02;
  	gdouble dm10 = mat->m10;
  	gdouble dm11 = mat->m11;
  	gdouble dm12 = mat->m12;
  	gdouble dm20 = mat->m20;
  	gdouble dm21 = mat->m21;
  	gdouble	dm22 = mat->m22;

  	return	g_double_hash (&dm00) +
  			g_double_hash (&dm01) +
  			g_double_hash (&dm02) +
  			g_double_hash (&dm10) +
  			g_double_hash (&dm11) +
  			g_double_hash (&dm12) +
  			g_double_hash (&dm20) +
  			g_double_hash (&dm21) +
  			g_double_hash (&dm22);
}

/**
 * crank_mat_float3_equal:
 * @a: (type CrankMatFloat3): A matrix.
 * @b: (type CrankMatFloat3): A matrix.
 *
 * Compares the value of matrix and check their equality.
 * This is useful when using matrix as a key.
 *
 * Returns: %TRUE if the two are same.
 */
gboolean
crank_mat_float3_equal (	gconstpointer	a,
							gconstpointer	b	)
{
	const CrankMatFloat3*	mat_a = (const CrankMatFloat3*)a;
	const CrankMatFloat3*	mat_b = (const CrankMatFloat3*)b;

  	return	(mat_a->m00 == mat_b->m00) &&
  			(mat_a->m01 == mat_b->m01) &&
  			(mat_a->m02 == mat_b->m02) &&
  			(mat_a->m10 == mat_b->m10) &&
  			(mat_a->m11 == mat_b->m11) &&
  			(mat_a->m12 == mat_b->m12) &&
  			(mat_a->m20 == mat_b->m20) &&
  			(mat_a->m21 == mat_b->m21) &&
  			(mat_a->m22 == mat_b->m22);
}

/**
 * crank_mat_float3_to_string:
 * @mat: A Matrix.
 *
 * Stringify a matrix to string.
 * A typical identity matrix can be expressed like below.
 *
 * |[
 *     [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
 * ]|
 *
 * Returns: string representation of matrix.
 */
gchar*
crank_mat_float3_to_string (	CrankMatFloat3*	mat	)
{
  	return crank_mat_float3_to_string_full (mat, "[", ", ", "]", "[", ", ", "]", "%g");
}

/**
 * crank_mat_float3_to_string_full:
 * @mat: A Matrix.
 * @mat_left: Start of matrix.
 * @mat_in: Divider for row vectors.
 * @mat_right: End of matrix.
 * @row_left: Start of row.
 * @row_in: Divider for elements.
 * @row_right: End of matrix.
 * @format: Format for each element. should consume 1 float parameter.
 *
 * Stringify a matrix to string, with given parts.
 *
 * Returns: string representation of matrix.
 */
gchar*
crank_mat_float3_to_string_full (	CrankMatFloat3*	mat,
								 	const gchar*	mat_left,
								 	const gchar*	mat_in,
								 	const gchar*	mat_right,
								 	const gchar*	row_left,
								 	const gchar*	row_in,
								 	const gchar*	row_right,
								 	const gchar*	format	)
{
  	GString*	builder;
	gchar*		str;

  	builder = g_string_new (mat_left);
  	g_string_append (builder,
			crank_vec_float2_to_string_full (((CrankVecFloat2*)mat) + 0, row_left, row_in, row_right, format)	);

	g_string_append (builder, mat_in);
  	g_string_append (builder,
			crank_vec_float2_to_string_full (((CrankVecFloat2*)mat) + 1, row_left, row_in, row_right, format)	);

	g_string_append (builder, mat_in);
  	g_string_append (builder,
			crank_vec_float2_to_string_full (((CrankVecFloat2*)mat) + 2, row_left, row_in, row_right, format)	);

  	g_string_append (builder, mat_right);

	str = builder->str;

	g_string_free (builder, FALSE);
	return str;
}

/**
 * crank_mat_float3_get:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 *
 * Gets element at given indices.
 *
 * Returns: Element at given indices.
 */
gfloat
crank_mat_float3_get (	CrankMatFloat3*	mat,
					  	const guint		i,
					  	const guint		j	)
{
	return ((gfloat*)mat) [(3 * i)  +  j];
}

/**
 * crank_mat_float3_set:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 * @value: Value of element.
 *
 * Sets element at given indices.
 */
void
crank_mat_float3_set (	CrankMatFloat3*	mat,
					  	const guint		i,
					  	const guint		j,
					  	const gfloat	value	)
{
	((gfloat*)mat) [(3 * i)  +  j] = value;
}

/**
 * crank_mat_float3_get_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: (out): A Row vector.
 *
 * Gets a row vector at given index.
 */
void
crank_mat_float3_get_row (	CrankMatFloat3*	mat,
						  	const guint		index,
						  	CrankVecFloat3*	row	)
{
  	crank_vec_float3_init_arr (row, ((gfloat*)mat) + 3 * index);
}

/**
 * crank_mat_float3_set_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: A Row vector.
 *
 * Sets a row vector at given index.
 */
void
crank_mat_float3_set_row (	CrankMatFloat3*	mat,
						  	const guint		index,
						  	CrankVecFloat3*	row	)
{
  	crank_vec_float3_init_arr (((CrankVecFloat3*)mat) + index, (gfloat*)row);
}


/**
 * crank_mat_float3_get_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: (out): A Column vector.
 *
 * Gets a column vector at given index.
 */
void
crank_mat_float3_get_col (	CrankMatFloat3*	mat,
						  	const guint		index,
						  	CrankVecFloat3*	col	)
{
  	gfloat*	ptr = ((gfloat*)mat) + index;
	col->x = ptr[0];
  	col->y = ptr[3];
  	col->z = ptr[6];
}

/**
 * crank_mat_float3_set_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: A Column vector.
 *
 * Sets a column vector at given index.
 */
void
crank_mat_float3_set_col (	CrankMatFloat3*	mat,
						  	const guint		index,
						  	CrankVecFloat3*	col	)
{
  	gfloat*	ptr = ((gfloat*)mat) + index;
  	ptr[0] = col->x;
 	ptr[3] = col->y;
 	ptr[6] = col->z;
}

/**
 * crank_mat_float3_get_tr:
 * @mat: A Matrix
 *
 * Gets a trace of matrix.
 *
 * A trace is sum of diagonal elements.
 *
 * Returns: A trace of matrix.
 */
gfloat
crank_mat_float3_get_tr (	CrankMatFloat3*	mat	)
{
  	return	mat->m00 + mat->m11 + mat->m22;
}

/**
 * crank_mat_float3_get_det:
 * @mat: A Matrix
 *
 * Gets a determinent of matrix.
 *
 * Returns: A determinent of matrix.
 */
gfloat
crank_mat_float3_get_det (	CrankMatFloat3* mat	)
{
  	return	(mat->m00 * mat->m11 * mat->m22) +
  			(mat->m01 * mat->m12 * mat->m20) +
			(mat->m02 * mat->m10 * mat->m21) -
  			(mat->m00 * mat->m12 * mat->m21) -
  			(mat->m01 * mat->m10 * mat->m22) -
  			(mat->m02 * mat->m11 * mat->m20);
}

/**
 * crank_mat_float3_get_cof:
 * @mat: A Matrix.
 * @r: (out): A cofactor matrix.
 *
 * Gets a cofactor matrix.
 */
void
crank_mat_float3_get_cof (	CrankMatFloat3*	mat,
						  	CrankMatFloat3*	r	)
{
	r->m00 = 	((mat->m11 * mat->m22) - (mat->m12 * mat->m21));
  	r->m01 = -	((mat->m10 * mat->m22) - (mat->m12 * mat->m20));
  	r->m02 = 	((mat->m10 * mat->m21) - (mat->m11 * mat->m20));

  	r->m10 = -	((mat->m01 * mat->m22) - (mat->m02 * mat->m21));
  	r->m11 = 	((mat->m00 * mat->m22) - (mat->m02 * mat->m20));
  	r->m12 = -	((mat->m00 * mat->m21) - (mat->m01 * mat->m20));

	r->m20 = 	((mat->m01 * mat->m12) - (mat->m02 * mat->m11));
  	r->m21 = -	((mat->m00 * mat->m12) - (mat->m02 * mat->m10));
  	r->m22 = 	((mat->m00 * mat->m11) - (mat->m01 * mat->m10));
}

/**
 * crank_mat_float3_get_adj:
 * @mat: A Matrix.
 * @r: (out): A adjugate matrix.
 *
 * Gets a adjugate matrix.
 */
void
crank_mat_float3_get_adj (	CrankMatFloat3*	mat,
						  	CrankMatFloat3*	r	)
{
	crank_mat_float3_get_cof (mat, r);
  	crank_mat_float3_transpose (r, r);
}

/**
 * crank_mat_float3_neg:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Negates a matrix.
 */
void
crank_mat_float3_neg (	CrankMatFloat3*	a,
					  	CrankMatFloat3* r	)
{
	r->m00 = - a->m00;
  	r->m01 = - a->m01;
  	r->m02 = - a->m02;
  	r->m10 = - a->m10;
  	r->m11 = - a->m11;
  	r->m12 = - a->m12;
	r->m20 = - a->m20;
  	r->m21 = - a->m21;
  	r->m22 = - a->m22;
}

/**
 * crank_mat_float3_transpose:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets a transpose of matrix.
 */
void
crank_mat_float3_transpose (	CrankMatFloat3*	a,
								CrankMatFloat3*	r	)
{
  	if (a != r) {
		r->m00 = a->m00;
	  	r->m01 = a->m10;
	  	r->m02 = a->m20;
	  	r->m10 = a->m01;
	  	r->m11 = a->m11;
	  	r->m12 = a->m21;
	  	r->m20 = a->m02;
	  	r->m21 = a->m12;
	  	r->m22 = a->m22;
	}
  	else {
	  	gfloat temp;

	  	temp = a->m01;
	  	a->m01 = a->m10;
	  	a->m10 = temp;

	  	temp = a->m02;
	  	a->m02 = a->m20;
	  	a->m20 = temp;

	  	temp = a->m12;
	  	a->m12 = a->m21;
	  	a->m21 = temp;
	}
}

/**
 * crank_mat_float3_inverse:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets an inverse of matrix.
 * If the matrix is singular, then NaN matrix may be returned.
 */
void
crank_mat_float3_inverse (	CrankMatFloat3*	a,
						  	CrankMatFloat3*	r	)
{
  	CrankMatFloat3	adj;
  	gfloat	det = crank_mat_float3_get_det (a);

  	crank_mat_float3_get_adj (a, &adj);
	crank_mat_float3_divs (&adj, det, r);
}

/**
 * crank_mat_float3_muls:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by scalar.
 */
void
crank_mat_float3_muls (	CrankMatFloat3*	a,
					   	const gfloat	b,
					   	CrankMatFloat3*	r	)
{
	r->m00 = a->m00 * b;
	r->m01 = a->m01 * b;
  	r->m02 = a->m02 * b;
	r->m10 = a->m10 * b;
	r->m11 = a->m11 * b;
  	r->m12 = a->m12 * b;
	r->m20 = a->m20 * b;
	r->m21 = a->m21 * b;
  	r->m22 = a->m22 * b;
}

/**
 * crank_mat_float3_divs:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Divides a matrix by scalar.
 */
void
crank_mat_float3_divs (	CrankMatFloat3*	a,
					   	const gfloat	b,
					   	CrankMatFloat3*	r	)
{
	r->m00 = a->m00 / b;
	r->m01 = a->m01 / b;
  	r->m02 = a->m02 / b;
	r->m10 = a->m10 / b;
	r->m11 = a->m11 / b;
  	r->m12 = a->m12 / b;
	r->m20 = a->m20 / b;
	r->m21 = a->m21 / b;
  	r->m22 = a->m22 / b;
}


/**
 * crank_mat_float3_mulv:
 * @a: A Matrix.
 * @b: A Vector.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by vector.
 */
void
crank_mat_float3_mulv (	CrankMatFloat3*	a,
					   	CrankVecFloat3*	b,
					   	CrankVecFloat3*	r	)
{
  	gfloat nx = (a->m00 * b->x) + (a->m01 * b->y) + (a->m02 * b->z);
  	gfloat ny = (a->m10 * b->x) + (a->m11 * b->y) + (a->m12 * b->z);
  	gfloat nz = (a->m20 * b->x) + (a->m21 * b->y) + (a->m22 * b->z);

  	r->x = nx;
  	r->y = ny;
  	r->z = nz;
}

/**
 * crank_mat_float3_mul:
 * @a: A Matrix.
 * @b: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies two matrices.
 */
void
crank_mat_float3_mul (	CrankMatFloat3*	a,
					  	CrankMatFloat3* b,
					  	CrankMatFloat3* r	)
{
	CrankMatFloat3	nr;

  	nr.m00 = (a->m00 * b->m00) + (a->m01 * b->m10) + (a->m02 * b->m20);
  	nr.m01 = (a->m00 * b->m01) + (a->m01 * b->m11) + (a->m02 * b->m21);
  	nr.m02 = (a->m00 * b->m02) + (a->m01 * b->m12) + (a->m02 * b->m22);

  	nr.m10 = (a->m10 * b->m00) + (a->m11 * b->m10) + (a->m12 * b->m20);
  	nr.m11 = (a->m10 * b->m01) + (a->m11 * b->m11) + (a->m12 * b->m21);
  	nr.m12 = (a->m10 * b->m02) + (a->m11 * b->m12) + (a->m12 * b->m22);

  	nr.m20 = (a->m20 * b->m00) + (a->m21 * b->m10) + (a->m22 * b->m20);
  	nr.m21 = (a->m20 * b->m01) + (a->m21 * b->m11) + (a->m22 * b->m21);
  	nr.m22 = (a->m20 * b->m02) + (a->m21 * b->m12) + (a->m22 * b->m22);

  	crank_mat_float3_copy (r, &nr);
}

/**
 * crank_mat_float3_mixs:
 * @a: A Matrix.
 * @b: A Matrix.
 * @c: A coefficient scalar.
 * @r: (out): A Matrix to store result.
 *
 * Mixes two matrix.
 *
 * The result is calculated by,
 * * (a * (1 - c)) + (b * c)
 */
void
crank_mat_float3_mixs (	CrankMatFloat3* a,
					  	CrankMatFloat3* b,
					  	const gfloat	c,
					  	CrankMatFloat3*	r	)
{
  	gfloat d = 1 - c;

	r->m00 = (a->m00 * d) + (b->m00 * c);
	r->m01 = (a->m01 * d) + (b->m01 * c);
	r->m02 = (a->m02 * d) + (b->m02 * c);
	r->m10 = (a->m10 * d) + (b->m10 * c);
	r->m11 = (a->m11 * d) + (b->m11 * c);
	r->m12 = (a->m12 * d) + (b->m12 * c);
	r->m20 = (a->m20 * d) + (b->m20 * c);
	r->m21 = (a->m21 * d) + (b->m21 * c);
	r->m22 = (a->m22 * d) + (b->m22 * c);
}

/**
 * crank_mat_float3_mix:
 * @a: A Matrix
 * @b: A Matrix
 * @c: A coefficient matrix.
 * @r: (out): A Matrix to store result.
 *
 * Mixes two matrix.
 *
 * The result is calculated by,
 * * r[i, j] = (a[i, j] * (1 - c[i, j]) + (b[i, j] * c[i, j])
 */
void
crank_mat_float3_mix (	CrankMatFloat3*	a,
					  	CrankMatFloat3* b,
					  	CrankMatFloat3*	c,
					  	CrankMatFloat3*	r	)
{
	r->m00 = (a->m00 * (1 - c->m00)) + (b->m00 * c->m00);
	r->m01 = (a->m01 * (1 - c->m01)) + (b->m01 * c->m01);
	r->m02 = (a->m02 * (1 - c->m02)) + (b->m02 * c->m02);
	r->m10 = (a->m10 * (1 - c->m10)) + (b->m10 * c->m10);
	r->m11 = (a->m11 * (1 - c->m11)) + (b->m11 * c->m11);
	r->m12 = (a->m12 * (1 - c->m12)) + (b->m12 * c->m12);
	r->m20 = (a->m20 * (1 - c->m20)) + (b->m20 * c->m20);
	r->m21 = (a->m21 * (1 - c->m21)) + (b->m21 * c->m21);
	r->m22 = (a->m22 * (1 - c->m22)) + (b->m22 * c->m22);
}
