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

//////// Private Macros ////////////////////////////////////////////////////////
#define DET4(a, b, c, d) \
	((a) * (d) - (b) * (c))



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
  	return	DET4(mat->m00, mat->m01, mat->m10, mat->m11);
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
	crank_vec_float3_init_arr (((CrankVecFloat3*)mat) + 2, (gfloat*)rv2);
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
			crank_vec_float3_to_string_full (((CrankVecFloat3*)mat) + 0, row_left, row_in, row_right, format)	);

	g_string_append (builder, mat_in);
  	g_string_append (builder,
			crank_vec_float3_to_string_full (((CrankVecFloat3*)mat) + 1, row_left, row_in, row_right, format)	);

	g_string_append (builder, mat_in);
  	g_string_append (builder,
			crank_vec_float3_to_string_full (((CrankVecFloat3*)mat) + 2, row_left, row_in, row_right, format)	);

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
  	return	(mat->m00 * DET4(mat->m11, mat->m12, mat->m21, mat->m22)) -
  			(mat->m01 * DET4(mat->m10, mat->m12, mat->m20, mat->m22)) +
  			(mat->m02 * DET4(mat->m10, mat->m11, mat->m20, mat->m21));
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
  	r->m00 =	DET4(mat->m11, mat->m12, mat->m21, mat->m22);
  	r->m01 = -	DET4(mat->m10, mat->m12, mat->m20, mat->m22);
  	r->m02 =	DET4(mat->m10, mat->m11, mat->m20, mat->m21);

  	r->m10 = -	DET4(mat->m01, mat->m02, mat->m21, mat->m22);
  	r->m11 =	DET4(mat->m00, mat->m02, mat->m20, mat->m22);
  	r->m12 = -	DET4(mat->m00, mat->m01, mat->m20, mat->m21);

  	r->m20 =	DET4(mat->m01, mat->m02, mat->m11, mat->m12);
  	r->m21 = -	DET4(mat->m00, mat->m02, mat->m10, mat->m12);
  	r->m22 =	DET4(mat->m00, mat->m01, mat->m10, mat->m11);
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







G_DEFINE_BOXED_TYPE (CrankMatFloat4, crank_mat_float4, crank_mat_float4_dup, g_free)

/**
 * crank_mat_float4_init:
 * @mat: (out): A Matrix.
 * @m00: Matrix element.
 * @m01: Matrix element.
 * @m02: Matrix element.
 * @m03: Matrix element.
 * @m10: Matrix element.
 * @m11: Matrix element.
 * @m12: Matrix element.
 * @m13: Matrix element.
 * @m20: Matrix element.
 * @m21: Matrix element.
 * @m22: Matrix element.
 * @m23: Matrix element.
 * @m30: Matrix element.
 * @m31: Matrix element.
 * @m32: Matrix element.
 * @m33: Matrix element.
 *
 * Initialize a matrix with given elements.
 */
void
crank_mat_float4_init (	CrankMatFloat4*	mat,
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
					   	const gfloat	m33	)
{
	mat->m00 = m00;
  	mat->m01 = m01;
  	mat->m02 = m02;
  	mat->m03 = m03;
  	mat->m10 = m10;
  	mat->m11 = m11;
  	mat->m12 = m12;
  	mat->m13 = m13;
  	mat->m20 = m20;
  	mat->m21 = m21;
  	mat->m22 = m22;
  	mat->m23 = m23;
  	mat->m30 = m30;
  	mat->m31 = m31;
  	mat->m32 = m32;
  	mat->m33 = m33;
}

/**
 * crank_mat_float4_init_arr:
 * @mat: (out): A Matrix.
 * @marr: (array fixed-size=16): An array of matrix.
 *
 * Initialize a matrix with given array.
 */
void
crank_mat_float4_init_arr (	CrankMatFloat4* mat,
						   	const gfloat*	marr	)
{
	memcpy (mat, marr, sizeof(gfloat) * 16);
}

/**
 * crank_mat_float4_init_rv:
 * @mat: (out): A Matrix.
 * @rv0: A Row vector.
 * @rv1: A Row vector.
 * @rv2: A Row vector.
 * @rv3: A Row vector.
 *
 * Initialize a matrix with given row vectors.
 */
void
crank_mat_float4_init_rv (	CrankMatFloat4*	mat,
						  	CrankVecFloat4*	rv0,
						  	CrankVecFloat4*	rv1,
						  	CrankVecFloat4*	rv2,
						  	CrankVecFloat4* rv3	)
{
	crank_vec_float4_init_arr ((CrankVecFloat4*)mat,       (gfloat*)rv0);
	crank_vec_float4_init_arr (((CrankVecFloat4*)mat) + 1, (gfloat*)rv1);
	crank_vec_float4_init_arr (((CrankVecFloat4*)mat) + 2, (gfloat*)rv2);
  	crank_vec_float4_init_arr (((CrankVecFloat4*)mat) + 3, (gfloat*)rv3);
}

/**
 * crank_mat_float4_init_rvarr:
 * @mat: (out): A Matrix.
 * @rvarr: (array fixed-size=4): An array of row vectors.
 *
 * Initialize a matrix with array of row vectors.
 */
void
crank_mat_float4_init_rvarr (	CrankMatFloat4*		mat,
 								CrankVecFloat4**	rvarr	)
{
	crank_mat_float4_init_rv (mat, rvarr[0], rvarr[1], rvarr[2], rvarr[3]);
}

/**
 * crank_mat_float4_init_cv:
 * @mat: (out): A Matrix.
 * @cv0: A Column Vector.
 * @cv1: A Column Vector.
 * @cv2: A Column Vector.
 * @cv3: A Column Vector.
 *
 * Initialize a matrix with column vectors.
 */
void
crank_mat_float4_init_cv (	CrankMatFloat4*	mat,
						  	CrankVecFloat4*	cv0,
						  	CrankVecFloat4*	cv1,
						  	CrankVecFloat4*	cv2,
						  	CrankVecFloat4*	cv3	)
{
	mat->m00 = cv0->x;
  	mat->m01 = cv1->x;
  	mat->m02 = cv2->x;
  	mat->m03 = cv3->x;
	mat->m10 = cv0->y;
  	mat->m11 = cv1->y;
  	mat->m12 = cv2->y;
  	mat->m13 = cv3->y;
  	mat->m20 = cv0->z;
  	mat->m21 = cv1->z;
  	mat->m22 = cv2->z;
  	mat->m23 = cv3->z;
  	mat->m30 = cv0->w;
  	mat->m31 = cv1->w;
  	mat->m32 = cv2->w;
  	mat->m33 = cv3->w;
}

/**
 * crank_mat_float4_init_cvarr:
 * @mat: (out): A Matrix.
 * @cvarr: (array fixed-size=4): An array of column vectors.
 *
 * Initialize a matrix with an array of column vectors.
 */
void
crank_mat_float4_init_cvarr (	CrankMatFloat4* 	mat,
							 	CrankVecFloat4**	cvarr	)
{
	crank_mat_float4_init_cv (mat, cvarr[0], cvarr[1], cvarr[2], cvarr[3]);
}

/**
 * crank_mat_float4_init_diag:
 * @mat: (out): A Matrix.
 * @m00: A diagonal element.
 * @m11: A diagonal element.
 * @m22: A diagonal element.
 * @m33: A diagonal element.
 *
 * Initialize a matrix with diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_float4_init_diag (	CrankMatFloat4*	mat,
								const gfloat	m00,
								const gfloat	m11,
								const gfloat	m22,
								const gfloat	m33	)
{
  	mat->m00 = m00;
  	mat->m01 = 0;
  	mat->m02 = 0;
  	mat->m03 = 0;
  	mat->m10 = 0;
  	mat->m11 = m11;
  	mat->m12 = 0;
  	mat->m13 = 0;
  	mat->m20 = 0;
  	mat->m21 = 0;
  	mat->m22 = m22;
  	mat->m23 = 0;
  	mat->m30 = 0;
  	mat->m31 = 0;
  	mat->m32 = 0;
  	mat->m33 = m33;
}

/**
 * crank_mat_float4_init_diag_arr:
 * @mat: (out): A Matrix.
 * @darr: (array fixed-size=4): An array of diagonal elements.
 *
 * Initialize a matrix with an array of diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_float4_init_diag_arr (	CrankMatFloat4*	mat,
									const gfloat*	darr	)
{
	crank_mat_float4_init_diag (mat, darr[0], darr[1], darr[2], darr[3]);
}

/**
 * crank_mat_float4_init_fill:
 * @mat: (out): A Matrix.
 * @fill: A fill value to fill the matrix.
 *
 * Initialize a matrix by filling with a value.
 */
void
crank_mat_float4_init_fill (	CrankMatFloat4*	mat,
								const gfloat	fill	)
{
	mat->m00 = fill;
  	mat->m01 = fill;
  	mat->m02 = fill;
  	mat->m03 = fill;
  	mat->m10 = fill;
  	mat->m11 = fill;
  	mat->m12 = fill;
  	mat->m13 = fill;
  	mat->m20 = fill;
  	mat->m21 = fill;
  	mat->m22 = fill;
  	mat->m23 = fill;
  	mat->m30 = fill;
  	mat->m31 = fill;
  	mat->m32 = fill;
  	mat->m33 = fill;
}

/**
 * crank_mat_float4_copy:
 * @mat: A Matrix.
 * @other: (out): Another matrix.
 *
 * Copies a matrix to other matrix.
 */
void
crank_mat_float4_copy (	CrankMatFloat4*	mat,
					   	CrankMatFloat4*	other	)
{
	crank_mat_float4_init_arr (other, (gfloat*) mat);
}

/**
 * crank_mat_float4_dup:
 * @mat: A Matrix
 *
 * Allocates a matrix and copy on it.
 *
 * Returns: an allocated copy. Free it with g_free()
 */
CrankMatFloat4*
crank_mat_float4_dup (	CrankMatFloat4*	mat	)
{
  	CrankMatFloat4*	result = g_new (CrankMatFloat4, 1);
	crank_mat_float4_copy (mat, result);
  	return result;
}


//////// Basic Operations //////////////////////////////////////////////////////

/**
 * crank_mat_float4_hash:
 * @a: (type CrankMatFloat4): A matrix.
 *
 * Gets hash value of a matrix.
 * This is useful when using matrix as key or value for #GHashTable.
 *
 * Returns: hash value of a matrix.
 */
guint
crank_mat_float4_hash (	gconstpointer	a	)
{
	const CrankMatFloat4*	mat = (const CrankMatFloat4*)a;

  	gdouble dm00 = mat->m00;
  	gdouble dm01 = mat->m01;
  	gdouble dm02 = mat->m02;
  	gdouble dm03 = mat->m03;
  	gdouble dm10 = mat->m10;
  	gdouble dm11 = mat->m11;
  	gdouble dm12 = mat->m12;
  	gdouble dm13 = mat->m13;
  	gdouble dm20 = mat->m20;
  	gdouble dm21 = mat->m21;
  	gdouble	dm22 = mat->m22;
  	gdouble	dm23 = mat->m23;
  	gdouble dm30 = mat->m30;
  	gdouble dm31 = mat->m31;
  	gdouble	dm32 = mat->m32;
  	gdouble	dm33 = mat->m33;

  	return	g_double_hash (&dm00) +
  			g_double_hash (&dm01) +
  			g_double_hash (&dm02) +
  			g_double_hash (&dm03) +
  			g_double_hash (&dm10) +
  			g_double_hash (&dm11) +
  			g_double_hash (&dm12) +
  			g_double_hash (&dm13) +
  			g_double_hash (&dm20) +
  			g_double_hash (&dm21) +
  			g_double_hash (&dm22) +
  			g_double_hash (&dm23) +
  			g_double_hash (&dm30) +
  			g_double_hash (&dm31) +
  			g_double_hash (&dm32) +
  			g_double_hash (&dm33);
}

/**
 * crank_mat_float4_equal:
 * @a: (type CrankMatFloat4): A matrix.
 * @b: (type CrankMatFloat4): A matrix.
 *
 * Compares the value of matrix and check their equality.
 * This is useful when using matrix as a key.
 *
 * Returns: %TRUE if the two are same.
 */
gboolean
crank_mat_float4_equal (	gconstpointer	a,
							gconstpointer	b	)
{
	const CrankMatFloat4*	mat_a = (const CrankMatFloat4*)a;
	const CrankMatFloat4*	mat_b = (const CrankMatFloat4*)b;

  	return	(mat_a->m00 == mat_b->m00) &&
  			(mat_a->m01 == mat_b->m01) &&
  			(mat_a->m02 == mat_b->m02) &&
  			(mat_a->m03 == mat_b->m03) &&
  			(mat_a->m10 == mat_b->m10) &&
  			(mat_a->m11 == mat_b->m11) &&
  			(mat_a->m12 == mat_b->m12) &&
  			(mat_a->m13 == mat_b->m13) &&
  			(mat_a->m20 == mat_b->m20) &&
  			(mat_a->m21 == mat_b->m21) &&
  			(mat_a->m22 == mat_b->m22) &&
  			(mat_a->m23 == mat_b->m23) &&
  			(mat_a->m30 == mat_b->m30) &&
  			(mat_a->m31 == mat_b->m31) &&
  			(mat_a->m32 == mat_b->m32) &&
  			(mat_a->m33 == mat_b->m33);
}

/**
 * crank_mat_float4_to_string:
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
crank_mat_float4_to_string (	CrankMatFloat4*	mat	)
{
  	return crank_mat_float4_to_string_full (mat, "[", ", ", "]", "[", ", ", "]", "%g");
}

/**
 * crank_mat_float4_to_string_full:
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
crank_mat_float4_to_string_full (	CrankMatFloat4*	mat,
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
			crank_vec_float4_to_string_full (((CrankVecFloat4*)mat) + 0, row_left, row_in, row_right, format)	);

	g_string_append (builder, mat_in);
  	g_string_append (builder,
			crank_vec_float4_to_string_full (((CrankVecFloat4*)mat) + 1, row_left, row_in, row_right, format)	);

	g_string_append (builder, mat_in);
  	g_string_append (builder,
			crank_vec_float4_to_string_full (((CrankVecFloat4*)mat) + 2, row_left, row_in, row_right, format)	);

	g_string_append (builder, mat_in);
  	g_string_append (builder,
			crank_vec_float4_to_string_full (((CrankVecFloat4*)mat) + 3, row_left, row_in, row_right, format)	);

  	g_string_append (builder, mat_right);

	str = builder->str;

	g_string_free (builder, FALSE);
	return str;
}

/**
 * crank_mat_float4_get:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 *
 * Gets element at given indices.
 *
 * Returns: Element at given indices.
 */
gfloat
crank_mat_float4_get (	CrankMatFloat4*	mat,
					  	const guint		i,
					  	const guint		j	)
{
	return ((gfloat*)mat) [(4 * i)  +  j];
}

/**
 * crank_mat_float4_set:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 * @value: Value of element.
 *
 * Sets element at given indices.
 */
void
crank_mat_float4_set (	CrankMatFloat4*	mat,
					  	const guint		i,
					  	const guint		j,
					  	const gfloat	value	)
{
	((gfloat*)mat) [(3 * i)  +  j] = value;
}

/**
 * crank_mat_float4_get_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: (out): A Row vector.
 *
 * Gets a row vector at given index.
 */
void
crank_mat_float4_get_row (	CrankMatFloat4*	mat,
						  	const guint		index,
						  	CrankVecFloat4*	row	)
{
  	crank_vec_float4_init_arr (row, ((gfloat*)mat) + 4 * index);
}

/**
 * crank_mat_float4_set_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: A Row vector.
 *
 * Sets a row vector at given index.
 */
void
crank_mat_float4_set_row (	CrankMatFloat4*	mat,
						  	const guint		index,
						  	CrankVecFloat4*	row	)
{
  	crank_vec_float4_init_arr (((CrankVecFloat4*)mat) + index, (gfloat*)row);
}


/**
 * crank_mat_float4_get_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: (out): A Column vector.
 *
 * Gets a column vector at given index.
 */
void
crank_mat_float4_get_col (	CrankMatFloat4*	mat,
						  	const guint		index,
						  	CrankVecFloat4*	col	)
{
  	gfloat*	ptr = ((gfloat*)mat) + index;
	col->x = ptr[0];
  	col->y = ptr[4];
  	col->z = ptr[8];
  	col->w = ptr[12];
}

/**
 * crank_mat_float4_set_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: A Column vector.
 *
 * Sets a column vector at given index.
 */
void
crank_mat_float4_set_col (	CrankMatFloat4*	mat,
						  	const guint		index,
						  	CrankVecFloat4*	col	)
{
  	gfloat*	ptr = ((gfloat*)mat) + index;
  	ptr[0] = col->x;
 	ptr[4] = col->y;
 	ptr[8] = col->z;
 	ptr[12] = col->w;
}

/**
 * crank_mat_float4_get_tr:
 * @mat: A Matrix
 *
 * Gets a trace of matrix.
 *
 * A trace is sum of diagonal elements.
 *
 * Returns: A trace of matrix.
 */
gfloat
crank_mat_float4_get_tr (	CrankMatFloat4*	mat	)
{
  	return	mat->m00 + mat->m11 + mat->m22 + mat->m33;
}

/**
 * crank_mat_float4_get_det:
 * @mat: A Matrix
 *
 * Gets a determinent of matrix.
 *
 * Returns: A determinent of matrix.
 */
gfloat
crank_mat_float4_get_det (	CrankMatFloat4* mat	)
{
  	return 	(DET4(mat->m00, mat->m01, mat->m10, mat->m11) *
			 DET4(mat->m22, mat->m23, mat->m32, mat->m33)) -

  			(DET4(mat->m00, mat->m02, mat->m10, mat->m12) *
	  		 DET4(mat->m21, mat->m23, mat->m31, mat->m33)) +

  			(DET4(mat->m00, mat->m03, mat->m10, mat->m13) *
	  		 DET4(mat->m21, mat->m22, mat->m31, mat->m32)) +

  			(DET4(mat->m01, mat->m02, mat->m11, mat->m12) *
	  		 DET4(mat->m20, mat->m23, mat->m30, mat->m33)) -

  			(DET4(mat->m01, mat->m03, mat->m11, mat->m13) *
	  		 DET4(mat->m20, mat->m22, mat->m30, mat->m32)) +

  			(DET4(mat->m02, mat->m03, mat->m12, mat->m13) *
	  		 DET4(mat->m20, mat->m21, mat->m30, mat->m31));
}

/**
 * crank_mat_float4_get_cof:
 * @mat: A Matrix.
 * @r: (out): A cofactor matrix.
 *
 * Gets a cofactor matrix.
 */
void
crank_mat_float4_get_cof (	CrankMatFloat4*	mat,
						  	CrankMatFloat4*	r	)
{
  	gfloat	m01_01 = DET4(mat->m00, mat->m01, mat->m10, mat->m11);
  	gfloat	m01_02 = DET4(mat->m00, mat->m02, mat->m10, mat->m12);
  	gfloat	m01_03 = DET4(mat->m00, mat->m03, mat->m10, mat->m13);
  	gfloat	m01_12 = DET4(mat->m01, mat->m02, mat->m11, mat->m12);
  	gfloat	m01_13 = DET4(mat->m01, mat->m03, mat->m11, mat->m13);
  	gfloat	m01_23 = DET4(mat->m02, mat->m03, mat->m12, mat->m13);

  	gfloat	m23_01 = DET4(mat->m20, mat->m21, mat->m30, mat->m31);
  	gfloat	m23_02 = DET4(mat->m20, mat->m22, mat->m30, mat->m32);
  	gfloat	m23_03 = DET4(mat->m20, mat->m23, mat->m30, mat->m33);
  	gfloat	m23_12 = DET4(mat->m21, mat->m22, mat->m31, mat->m32);
  	gfloat	m23_13 = DET4(mat->m21, mat->m23, mat->m31, mat->m33);
  	gfloat	m23_23 = DET4(mat->m22, mat->m23, mat->m32, mat->m33);

  	r->m00 = 	mat->m11 * m23_23 - mat->m12 * m23_13 + mat->m13 * m23_12;
  	r->m01 = -	mat->m10 * m23_23 + mat->m12 * m23_03 - mat->m13 * m23_02;
  	r->m02 =	mat->m10 * m23_13 - mat->m11 * m23_03 + mat->m13 * m23_01;
  	r->m03 = -	mat->m10 * m23_12 + mat->m11 * m23_02 - mat->m12 * m23_01;

  	r->m10 = -	mat->m01 * m23_23 + mat->m02 * m23_13 - mat->m03 * m23_12;
  	r->m11 =	mat->m00 * m23_23 - mat->m02 * m23_03 + mat->m03 * m23_02;
  	r->m12 = -	mat->m00 * m23_13 + mat->m01 * m23_03 - mat->m03 * m23_01;
  	r->m13 =	mat->m00 * m23_12 - mat->m01 * m23_02 + mat->m02 * m23_01;

	r->m20 =	m01_12 * mat->m33 - m01_13 * mat->m32 - m01_23 * mat->m31;
	r->m21 = -	m01_02 * mat->m33 + m01_03 * mat->m32 + m01_23 * mat->m30;
	r->m22 =	m01_01 * mat->m33 - m01_03 * mat->m31 - m01_13 * mat->m30;
	r->m23 = -	m01_01 * mat->m32 + m01_02 * mat->m31 + m01_12 * mat->m30;

	r->m30 =	m01_12 * mat->m23 + m01_13 * mat->m22 - m01_23 * mat->m21;
	r->m31 = -	m01_02 * mat->m23 - m01_03 * mat->m22 + m01_23 * mat->m20;
	r->m32 =	m01_01 * mat->m23 + m01_03 * mat->m21 - m01_13 * mat->m20;
	r->m33 = -	m01_01 * mat->m22 - m01_02 * mat->m21 + m01_12 * mat->m20;
}

/**
 * crank_mat_float4_get_adj:
 * @mat: A Matrix.
 * @r: (out): A adjugate matrix.
 *
 * Gets a adjugate matrix.
 */
void
crank_mat_float4_get_adj (	CrankMatFloat4*	mat,
						  	CrankMatFloat4*	r	)
{
	crank_mat_float4_get_cof (mat, r);
  	crank_mat_float4_transpose (r, r);
}

/**
 * crank_mat_float4_neg:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Negates a matrix.
 */
void
crank_mat_float4_neg (	CrankMatFloat4*	a,
					  	CrankMatFloat4* r	)
{
	r->m00 = - a->m00;
  	r->m01 = - a->m01;
  	r->m02 = - a->m02;
  	r->m03 = - a->m03;
  	r->m10 = - a->m10;
  	r->m11 = - a->m11;
  	r->m12 = - a->m12;
  	r->m13 = - a->m13;
	r->m20 = - a->m20;
  	r->m21 = - a->m21;
  	r->m22 = - a->m22;
  	r->m23 = - a->m23;
	r->m30 = - a->m30;
  	r->m31 = - a->m31;
  	r->m32 = - a->m32;
  	r->m33 = - a->m33;
}

/**
 * crank_mat_float4_transpose:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets a transpose of matrix.
 */
void
crank_mat_float4_transpose (	CrankMatFloat4*	a,
								CrankMatFloat4*	r	)
{
  	if (a != r) {
		r->m00 = a->m00;
	  	r->m01 = a->m10;
	  	r->m02 = a->m20;
	  	r->m03 = a->m30;
	  	r->m10 = a->m01;
	  	r->m11 = a->m11;
	  	r->m12 = a->m21;
	  	r->m13 = a->m31;
	  	r->m20 = a->m02;
	  	r->m21 = a->m12;
	  	r->m22 = a->m22;
	  	r->m23 = a->m32;
	  	r->m30 = a->m03;
	  	r->m31 = a->m13;
	  	r->m32 = a->m23;
	  	r->m33 = a->m33;
	}
  	else {
	  	gfloat temp;

	  	temp = a->m01;
	  	a->m01 = a->m10;
	  	a->m10 = temp;

	  	temp = a->m02;
	  	a->m02 = a->m20;
	  	a->m20 = temp;

	  	temp = a->m03;
	  	a->m03 = a->m30;
	  	a->m30 = temp;

	  	temp = a->m12;
	  	a->m12 = a->m21;
	  	a->m21 = temp;

	  	temp = a->m13;
	  	a->m13 = a->m31;
	  	a->m31 = temp;

	  	temp = a->m23;
	  	a->m23 = a->m32;
	  	a->m32 = temp;
	}
}

/**
 * crank_mat_float4_inverse:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets an inverse of matrix.
 * If the matrix is singular, then NaN matrix may be returned.
 */
void
crank_mat_float4_inverse (	CrankMatFloat4*	a,
						  	CrankMatFloat4*	r	)
{
  	CrankMatFloat4	adj;
  	gfloat	det = crank_mat_float4_get_det (a);

  	crank_mat_float4_get_adj (a, &adj);
	crank_mat_float4_divs (&adj, det, r);
}

/**
 * crank_mat_float4_muls:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by scalar.
 */
void
crank_mat_float4_muls (	CrankMatFloat4*	a,
					   	const gfloat	b,
					   	CrankMatFloat4*	r	)
{
	r->m00 = a->m00 * b;
	r->m01 = a->m01 * b;
  	r->m02 = a->m02 * b;
  	r->m03 = a->m03 * b;
	r->m10 = a->m10 * b;
	r->m11 = a->m11 * b;
  	r->m12 = a->m12 * b;
  	r->m13 = a->m13 * b;
	r->m20 = a->m20 * b;
	r->m21 = a->m21 * b;
  	r->m22 = a->m22 * b;
  	r->m23 = a->m23 * b;
	r->m30 = a->m30 * b;
	r->m31 = a->m31 * b;
  	r->m32 = a->m32 * b;
  	r->m33 = a->m33 * b;
}

/**
 * crank_mat_float4_divs:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Divides a matrix by scalar.
 */
void
crank_mat_float4_divs (	CrankMatFloat4*	a,
					   	const gfloat	b,
					   	CrankMatFloat4*	r	)
{
  	crank_mat_float4_muls (a, 1 / b, r);
}


/**
 * crank_mat_float4_mulv:
 * @a: A Matrix.
 * @b: A Vector.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by vector.
 */
void
crank_mat_float4_mulv (	CrankMatFloat4*	a,
					   	CrankVecFloat4*	b,
					   	CrankVecFloat4*	r	)
{
  	gfloat nx = (a->m00 * b->x) + (a->m01 * b->y) + (a->m02 * b->z) * (a->m03 * b->w);
  	gfloat ny = (a->m10 * b->x) + (a->m11 * b->y) + (a->m12 * b->z) * (a->m13 * b->w);
  	gfloat nz = (a->m20 * b->x) + (a->m21 * b->y) + (a->m22 * b->z) * (a->m23 * b->w);
  	gfloat nw = (a->m30 * b->x) + (a->m31 * b->y) + (a->m32 * b->z) * (a->m33 * b->w);

  	r->x = nx;
  	r->y = ny;
  	r->z = nz;
  	r->w = nw;
}

/**
 * crank_mat_float4_mul:
 * @a: A Matrix.
 * @b: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies two matrices.
 */
void
crank_mat_float4_mul (	CrankMatFloat4*	a,
					  	CrankMatFloat4* b,
					  	CrankMatFloat4* r	)
{
	CrankMatFloat4	nr;

  	nr.m00 = (a->m00 * b->m00) + (a->m01 * b->m10) + (a->m02 * b->m20) + (a->m03 * b->m30);
  	nr.m01 = (a->m00 * b->m01) + (a->m01 * b->m11) + (a->m02 * b->m21) + (a->m03 * b->m31);
  	nr.m02 = (a->m00 * b->m02) + (a->m01 * b->m12) + (a->m02 * b->m22) + (a->m03 * b->m32);
  	nr.m02 = (a->m00 * b->m03) + (a->m01 * b->m13) + (a->m02 * b->m23) + (a->m03 * b->m33);

  	nr.m10 = (a->m10 * b->m00) + (a->m11 * b->m10) + (a->m12 * b->m20) + (a->m13 * b->m30);
  	nr.m11 = (a->m10 * b->m01) + (a->m11 * b->m11) + (a->m12 * b->m21) + (a->m13 * b->m31);
  	nr.m12 = (a->m10 * b->m02) + (a->m11 * b->m12) + (a->m12 * b->m22) + (a->m13 * b->m32);
  	nr.m12 = (a->m10 * b->m03) + (a->m11 * b->m13) + (a->m12 * b->m23) + (a->m13 * b->m33);

  	nr.m20 = (a->m20 * b->m00) + (a->m21 * b->m10) + (a->m22 * b->m20) + (a->m23 * b->m30);
  	nr.m21 = (a->m20 * b->m01) + (a->m21 * b->m11) + (a->m22 * b->m21) + (a->m23 * b->m31);
  	nr.m22 = (a->m20 * b->m02) + (a->m21 * b->m12) + (a->m22 * b->m22) + (a->m23 * b->m32);
  	nr.m22 = (a->m20 * b->m03) + (a->m21 * b->m13) + (a->m22 * b->m23) + (a->m23 * b->m33);

  	nr.m30 = (a->m30 * b->m00) + (a->m31 * b->m10) + (a->m32 * b->m20) + (a->m33 * b->m30);
  	nr.m31 = (a->m30 * b->m01) + (a->m31 * b->m11) + (a->m32 * b->m21) + (a->m33 * b->m31);
  	nr.m32 = (a->m30 * b->m02) + (a->m31 * b->m12) + (a->m32 * b->m22) + (a->m33 * b->m32);
  	nr.m32 = (a->m30 * b->m03) + (a->m31 * b->m13) + (a->m32 * b->m23) + (a->m33 * b->m33);

  	crank_mat_float4_copy (r, &nr);
}

/**
 * crank_mat_float4_mixs:
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
crank_mat_float4_mixs (	CrankMatFloat4* a,
					  	CrankMatFloat4* b,
					  	const gfloat	c,
					  	CrankMatFloat4*	r	)
{
  	gfloat d = 1 - c;

	r->m00 = (a->m00 * d) + (b->m00 * c);
	r->m01 = (a->m01 * d) + (b->m01 * c);
	r->m02 = (a->m02 * d) + (b->m02 * c);
	r->m03 = (a->m03 * d) + (b->m03 * c);
	r->m10 = (a->m10 * d) + (b->m10 * c);
	r->m11 = (a->m11 * d) + (b->m11 * c);
	r->m12 = (a->m12 * d) + (b->m12 * c);
	r->m13 = (a->m13 * d) + (b->m13 * c);
	r->m20 = (a->m20 * d) + (b->m20 * c);
	r->m21 = (a->m21 * d) + (b->m21 * c);
	r->m22 = (a->m22 * d) + (b->m22 * c);
	r->m23 = (a->m23 * d) + (b->m23 * c);
	r->m30 = (a->m30 * d) + (b->m30 * c);
	r->m31 = (a->m31 * d) + (b->m31 * c);
	r->m32 = (a->m32 * d) + (b->m32 * c);
	r->m33 = (a->m33 * d) + (b->m33 * c);
}

/**
 * crank_mat_float4_mix:
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
crank_mat_float4_mix (	CrankMatFloat4*	a,
					  	CrankMatFloat4* b,
					  	CrankMatFloat4*	c,
					  	CrankMatFloat4*	r	)
{
	r->m00 = (a->m00 * (1 - c->m00)) + (b->m00 * c->m00);
	r->m01 = (a->m01 * (1 - c->m01)) + (b->m01 * c->m01);
	r->m02 = (a->m02 * (1 - c->m02)) + (b->m02 * c->m02);
	r->m03 = (a->m03 * (1 - c->m03)) + (b->m03 * c->m03);
	r->m10 = (a->m10 * (1 - c->m10)) + (b->m10 * c->m10);
	r->m11 = (a->m11 * (1 - c->m11)) + (b->m11 * c->m11);
	r->m12 = (a->m12 * (1 - c->m12)) + (b->m12 * c->m12);
	r->m13 = (a->m13 * (1 - c->m13)) + (b->m13 * c->m13);
	r->m20 = (a->m20 * (1 - c->m20)) + (b->m20 * c->m20);
	r->m21 = (a->m21 * (1 - c->m21)) + (b->m21 * c->m21);
	r->m22 = (a->m22 * (1 - c->m22)) + (b->m22 * c->m22);
	r->m23 = (a->m23 * (1 - c->m23)) + (b->m23 * c->m23);
	r->m30 = (a->m30 * (1 - c->m30)) + (b->m30 * c->m30);
	r->m31 = (a->m31 * (1 - c->m31)) + (b->m31 * c->m31);
	r->m32 = (a->m32 * (1 - c->m32)) + (b->m32 * c->m32);
	r->m33 = (a->m33 * (1 - c->m33)) + (b->m33 * c->m33);
}









//////// Internal Declaration //////////////////////////////////////////////////

void		crank_mat_float_n_realloc	(	CrankMatFloatN*	mat,
								 			const guint		rn,
								 			const guint		cn	);



G_DEFINE_BOXED_TYPE(CrankMatFloatN, crank_mat_float_n,
					crank_mat_float_n_dup,\
					crank_mat_float_n_free)

/**
 * crank_mat_float_n_init:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @...: Elements.
 *
 * Initialize a matrix with given elements.
 */
void
crank_mat_float_n_init (	CrankMatFloatN*	mat,
							const guint		rn,
							const guint		cn,
							...	)
{
  	va_list	varargs;
  	guint	i;

  	crank_mat_float_n_realloc (mat, rn, cn);

  	va_start (varargs, cn);

  	for (i = 0; i < rn*cn; i++)
		mat->data[i] = (gfloat) (va_arg(varargs, gdouble));

  	va_end (varargs);
}

/**
 * crank_mat_float_n_init_arr:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @marr: (array): An array of matrix.
 *
 * Initialize a matrix with given array.
 */
void
crank_mat_float_n_init_arr (	CrankMatFloatN* mat,
								const guint		rn,
								const guint		cn,
							   	const gfloat*	marr	)
{
  	guint	count = rn*cn;

  	crank_mat_float_n_realloc (mat, rn, cn);

	memcpy (mat->data, marr, sizeof(gfloat) * count);
}

/**
 * crank_mat_float_n_init_arr_take:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @marr: (array) (transfer full): An array of matrix.
 *
 * Initialize a matrix by taking given array
 */
void
crank_mat_float_n_init_arr_take (	CrankMatFloatN* mat,
									const guint		rn,
									const guint		cn,
								   	gfloat*	marr	)
{
  	g_free (mat->data);
  	mat->data = marr;
  	mat->rn = rn;
 	mat->cn = cn;
}


/**
 * crank_mat_float_n_init_rv:
 * @mat: (out): A Matrix.
 * @rn: Row count
 * @...: Row vectors.
 *
 * Initialize a matrix with given row vectors.
 */
void
crank_mat_float_n_init_rv (	CrankMatFloatN*	mat,
						  	const guint		rn,
						   	...	)
{
  	va_list	varargs_cn;
  	va_list	varargs_data;
  	guint	i;
  	guint	cn = 0;

  	va_start (varargs_cn, rn);
  	va_copy (varargs_data, varargs_cn);

  	// Phase 1: get max length of row vectors.
	for (i = 0; i < rn; i++) {
		CrankVecFloatN*	rv = va_arg (varargs_cn, CrankVecFloatN*);

		cn = MAX(cn, rv->n);
	}
  	va_end (varargs_cn);

  	// Phase 2: Copy actual data to matrix data.
  	crank_mat_float_n_realloc (mat, rn, cn);

  	for (i = 0; i < rn; i++) {
	 	CrankVecFloatN*	rv = va_arg (varargs_data, CrankVecFloatN*);

	  	memcpy (mat->data + (i * cn), rv->data, rv->n);
	}
  	va_end (varargs_data);
}

/**
 * crank_mat_float_n_init_rvarr:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @rvarr: (array length=rn): An array of row vectors.
 *
 * Initialize a matrix with array of row vectors.
 */
void
crank_mat_float_n_init_rvarr (	CrankMatFloatN*		mat,
							  	const guint			rn,
 								CrankVecFloatN**	rvarr	)
{
  	guint	i;
  	guint	cn = 0;

  	for (i = 0; i < rn; i++) cn = MAX(cn, rvarr[i]->n);

  	crank_mat_float_n_realloc (mat, rn, cn);
  	for (i = 0; i < rn; i++)
	  	memcpy (mat->data + (i * cn), rvarr[i]->data, rvarr[i]->n);
}

/**
 * crank_mat_float_n_init_cv:
 * @mat: (out): A Matrix.
 * @cn: Column count.
 * @...: Column Vectors.
 *
 * Initialize a matrix with column vectors.
 */
void
crank_mat_float_n_init_cv (	CrankMatFloatN*	mat,
						   	const guint		cn,
							...	)
{
  	va_list	varargs_rn;
  	va_list varargs_data;

  	guint	rn = 0;
  	guint	i;
  	guint	j;

  	va_start (varargs_rn, cn);
  	va_copy (varargs_data, varargs_rn);

  	for (i = 0; i < cn; i++) {
		CrankVecFloatN*	cv = va_arg (varargs_rn, CrankVecFloatN*);

	  	rn = MAX (rn, cv->n);
	}
  	va_end (varargs_rn);

  	crank_mat_float_n_realloc (mat, rn, cn);
  	for (i = 0; i < cn; i++) {
		CrankVecFloatN*	cv = va_arg (varargs_data, CrankVecFloatN*);

	  	for (j = 0; j < cv->n; j++) {
	  		mat->data[(rn * j) + i] = cv->data[j];
		}
	}
  	va_end (varargs_data);

}

/**
 * crank_mat_float_n_init_cvarr:
 * @mat: (out): A Matrix.
 * @cn: Column count.
 * @cvarr: (array length=cn): An array of column vectors.
 *
 * Initialize a matrix with an array of column vectors.
 */
void
crank_mat_float_n_init_cvarr (	CrankMatFloatN* 	mat,
							 	const guint			cn,
							 	CrankVecFloatN**	cvarr	)
{
  	guint	rn = 0;
  	guint	i;
  	guint	j;

  	for (i = 0; i < cn; i++) rn = MAX (rn, cvarr[i]->n);

  	crank_mat_float_n_realloc (mat, rn, cn);
  	for (i = 0; i < cn; i++) {
	  	for (j = 0; j < cvarr[i]->n; j++) {
	  		mat->data[(rn * j) + i] = cvarr[i]->data[j];
		}
	}
}

/**
 * crank_mat_float_n_init_diag:
 * @mat: (out): A Matrix.
 * @n: Element count.
 * @...: Diagonal elements.
 *
 * Initialize a matrix with diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_float_n_init_diag (	CrankMatFloatN*	mat,
								const guint		n,
							 	...	)
{
  	va_list	varargs;
  	guint	i;

  	va_start (varargs, n);

  	crank_mat_float_n_realloc (mat, n, n);
 	for (i = 0; i < n; i++)
	 	mat->data[(n * i) + i] = va_arg (varargs, gdouble);

  	va_end (varargs);
}

/**
 * crank_mat_float_n_init_diag_arr:
 * @mat: (out): A Matrix.
 * @n: Element count.
 * @darr: (array length=n): An array of diagonal elements.
 *
 * Initialize a matrix with an array of diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_float_n_init_diag_arr (	CrankMatFloatN*	mat,
								 	const guint		n,
									const gfloat*	darr	)
{
  	guint	i;

  	crank_mat_float_n_realloc (mat, n, n);
 	for (i = 0; i < n; i++)
	 	mat->data[(n * i) + i] = darr[i];
}

/**
 * crank_mat_float_n_init_fill:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @fill: A fill value to fill the matrix.
 *
 * Initialize a matrix by filling with a value.
 */
void
crank_mat_float_n_init_fill (	CrankMatFloatN*	mat,
							 	const guint		rn,
							 	const guint		cn,
								const gfloat	fill	)
{
  	guint	i;
  	guint	j;

  	crank_mat_float_n_realloc (mat, rn, cn);
  	for (i = 0; i < rn; i++)
		for (j = 0; j < cn; j++)
			mat->data[(cn * i) + j] = fill;
}

/**
 * crank_mat_float_n_copy:
 * @mat: A Matrix.
 * @other: (out): Another matrix.
 *
 * Copies a matrix to other matrix.
 */
void
crank_mat_float_n_copy (	CrankMatFloatN*	mat,
					   		CrankMatFloatN*	other	)
{
	crank_mat_float_n_init_arr (other, mat->rn, mat->cn, mat->data);
}

/**
 * crank_mat_float_n_dup:
 * @mat: A Matrix
 *
 * Allocates a matrix and copy on it.
 *
 * Returns: an allocated copy. Free it with g_free()
 */
CrankMatFloatN*
crank_mat_float_n_dup (	CrankMatFloatN*	mat	)
{
  	CrankMatFloatN*	result = g_new (CrankMatFloatN, 1);
	crank_mat_float_n_copy (mat, result);
  	return result;
}

/**
 * crank_mat_float_n_fini:
 * @mat: A Matrix to reset.
 *
 * Resets a matrix and frees its associated memory block.
 */
void
crank_mat_float_n_fini (	CrankMatFloatN*	mat	)
{
	crank_mat_float_n_realloc (mat, 0, 0);
}

/**
 * crank_mat_float_n_free:
 * @mat: A Matrix to free.
 *
 * Frees allocated matrix.
 */
void
crank_mat_float_n_free (	CrankMatFloatN*	mat	)
{
	crank_mat_float_n_fini (mat);
  	g_free (mat);
}


//////// Basic Operations //////////////////////////////////////////////////////

/**
 * crank_mat_float_n_hash:
 * @a: (type CrankMatFloatN): A matrix.
 *
 * Gets hash value of a matrix.
 * This is useful when using matrix as key or value for #GHashTable.
 *
 * Returns: hash value of a matrix.
 */
guint
crank_mat_float_n_hash (	gconstpointer	a	)
{
	const CrankMatFloatN*	mat = (const CrankMatFloatN*)a;
  	guint	i;
  	guint	j;

  	guint	hash;

  	hash =  g_direct_hash (GINT_TO_POINTER (mat->rn)) +
  			g_direct_hash (GINT_TO_POINTER (mat->cn));

  	for (i = 0; i < mat->rn; i++) {
	  	for (j = 0; j < mat->cn; j++) {
	  		gdouble dm = mat->data[(mat->cn * i) + j];
			hash += g_double_hash (&dm);
		}
	}

  	return hash;
}

/**
 * crank_mat_float_n_equal:
 * @a: (type CrankMatFloatN): A matrix.
 * @b: (type CrankMatFloatN): A matrix.
 *
 * Compares the value of matrix and check their equality.
 * This is useful when using matrix as a key.
 *
 * Returns: %TRUE if the two are same.
 */
gboolean
crank_mat_float_n_equal (	gconstpointer	a,
							gconstpointer	b	)
{
	const CrankMatFloatN*	mat_a = (const CrankMatFloatN*)a;
	const CrankMatFloatN*	mat_b = (const CrankMatFloatN*)b;

  	guint	i;
  	guint	j;

  	if (	(mat_a->rn != mat_b->rn) ||
	   		(mat_a->cn != mat_b->cn))	return FALSE;

	for (i = 0; i < mat_a->rn; i++) {
		for (j = 0; j < mat_a->cn; j++) {

			guint	ei = i * mat_a->cn + j;

			if (mat_a->data[ei] != mat_b->data[ei]) return FALSE;
		}
	}

  	return TRUE;
}

/**
 * crank_mat_float_n_to_string:
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
crank_mat_float_n_to_string (	CrankMatFloatN*	mat	)
{
  	return crank_mat_float_n_to_string_full (mat, "[", ", ", "]", "[", ", ", "]", "%g");
}

/**
 * crank_mat_float_n_to_string_full:
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
crank_mat_float_n_to_string_full (	CrankMatFloatN*	mat,
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

  	guint		i;
  	guint		j;

  	builder = g_string_new (mat_left);

  	for (i = 0; i < mat->rn; i++) {
	  	if (0 < i) g_string_append (builder, mat_in);

	  	g_string_append (builder, row_left);
	  	for (j = 0; j < mat->cn; j++) {
	  		if (0 < j) g_string_append (builder, row_in);
	  		g_string_append_printf (builder, format, mat->data[(i * mat->cn) + j]);

		}
		g_string_append (builder, row_right);

	  }

  	g_string_append (builder, mat_right);

	str = builder->str;

	g_string_free (builder, FALSE);
	return str;
}

/**
 * crank_mat_float_n_get_row_size:
 * @mat: A Matrix.
 *
 * Gets row size (Row count) of given matrix.
 *
 * Returns: Row count of matrix.
 */
guint
crank_mat_float_n_get_row_size (	CrankMatFloatN*	mat	)
{
	return mat->rn;
}

/**
 * crank_mat_float_n_get_col_size:
 * @mat: A Matrix.
 *
 * Gets column size (Column count) of given matrix.
 *
 * Returns: Column count of matrix.
 */
guint
crank_mat_float_n_get_col_size (	CrankMatFloatN*	mat	)
{
	return mat->cn;
}

/**
 * crank_mat_float_n_get:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 *
 * Gets element at given indices.
 *
 * Returns: Element at given indices.
 */
gfloat
crank_mat_float_n_get (	CrankMatFloatN*	mat,
					  	const guint		i,
					  	const guint		j	)
{
	return mat->data [(mat->cn * i)  +  j];
}

/**
 * crank_mat_float_n_set:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 * @value: Value of element.
 *
 * Sets element at given indices.
 */
void
crank_mat_float_n_set (	CrankMatFloatN*	mat,
					  	const guint		i,
					  	const guint		j,
					  	const gfloat	value	)
{
	mat->data [(mat->cn * i)  +  j] = value;
}

/**
 * crank_mat_float_n_get_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: (out): A Row vector.
 *
 * Gets a row vector at given index.
 */
void
crank_mat_float_n_get_row (	CrankMatFloatN*	mat,
						  	const guint		index,
						  	CrankVecFloatN*	row	)
{
  	crank_vec_float_n_init_arr (row, mat->cn, mat->data + mat->cn * index);
}

/**
 * crank_mat_float_n_set_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: A Row vector.
 *
 * Sets a row vector at given index.
 */
void
crank_mat_float_n_set_row (	CrankMatFloatN*	mat,
						  	const guint		index,
						  	CrankVecFloatN*	row	)
{
  	g_return_if_fail (row->n <= mat->cn);
  	memcpy (mat->data + mat->cn * index, row->data, row->n);
}


/**
 * crank_mat_float_n_get_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: (out): A Column vector.
 *
 * Gets a column vector at given index.
 */
void
crank_mat_float_n_get_col (	CrankMatFloatN*	mat,
						  	const guint		index,
						  	CrankVecFloatN*	col	)
{
  	guint	i;
  	gfloat*	data;

  	data = g_new (gfloat, mat->rn);
  	for (i = 0; i < mat->rn; i++)
		data[i] = mat->data[(mat->cn * i) + index];

  	crank_vec_float_n_init_arr_take (col, mat->rn, data);
}

/**
 * crank_mat_float_n_set_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: A Column vector.
 *
 * Sets a column vector at given index.
 */
void
crank_mat_float_n_set_col (	CrankMatFloatN*	mat,
						  	const guint		index,
						  	CrankVecFloatN*	col	)
{
  	guint i;

  	g_return_if_fail (col->n <= mat->rn);
  	for (i = 0; i < mat->rn; i++)
		mat->data[(mat->cn * i) + index] = col->data[i];
}

/**
 * crank_mat_float_n_get_tr:
 * @mat: A Matrix
 *
 * Gets a trace of matrix.
 *
 * A trace is sum of diagonal elements.
 *
 * Returns: A trace of matrix.
 */
gfloat
crank_mat_float_n_get_tr (	CrankMatFloatN*	mat	)
{
  	gfloat	tr = 0.0f;
	guint	i;

	g_return_val_if_fail (crank_mat_float_n_is_square (mat), 0.0f);

	for (i = 0; i < mat->rn; i++) {
		tr += mat->data [(mat->cn * i) + i];
	}

  	return tr;
}

/**
 * crank_mat_float_n_get_det:
 * @mat: A Matrix
 *
 * Gets a determinent of matrix.
 *
 * Returns: A determinent of matrix.
 */
gfloat
crank_mat_float_n_get_det (	CrankMatFloatN* mat	)
{
  	g_warning ("Function not implemented.");
  	// For now we just return 0.
  	// We need LU, or QR Decompositions, to calculate determinent in reasonable time.
  	return 0;
}

/**
 * crank_mat_float_n_get_cof:
 * @mat: A Matrix.
 * @r: (out): A cofactor matrix.
 *
 * Gets a cofactor matrix.
 */
void
crank_mat_float_n_get_cof (	CrankMatFloatN*	mat,
						  	CrankMatFloatN*	r	)
{
  	g_warning ("Function not implemented.");
  	return;
}

/**
 * crank_mat_float_n_get_adj:
 * @mat: A Matrix.
 * @r: (out): A adjugate matrix.
 *
 * Gets a adjugate matrix.
 */
void
crank_mat_float_n_get_adj (	CrankMatFloatN*	mat,
						  	CrankMatFloatN*	r	)
{
	crank_mat_float_n_get_cof (mat, r);
  	crank_mat_float_n_transpose (r, r);
}

/**
 * crank_mat_float_n_is_square:
 * @mat: A Matrix.
 *
 * Checks it is a square matrix.
 *
 * A Square matrix have trace, determinent.
 * And may have inverse matrix.
 *
 * Returns: Whether this is a square matrix.
 */
gboolean
crank_mat_float_n_is_square (	CrankMatFloatN*	a	)
{
	return (a->rn == a->cn);
}

/**
 * crank_mat_float_n_neg:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Negates a matrix.
 */
void
crank_mat_float_n_neg (	CrankMatFloatN*	a,
					  	CrankMatFloatN* r	)
{
  	guint	i;
  	guint	j;

  	if (a != r) crank_mat_float_n_realloc (r, a->rn, a->cn);

	for (i = 0; i < a->rn; i ++) {
		for (j = 0; j < a->cn; j ++) {
			r->data[(i * a->cn) + j] =  - a->data[(i * a->cn) + j];
		}
	}
}

/**
 * crank_mat_float_n_transpose:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets a transpose of matrix.
 */
void
crank_mat_float_n_transpose (	CrankMatFloatN*	a,
								CrankMatFloatN*	r	)
{
  	guint	i;
  	guint	j;

  	gfloat*	data = g_new (gfloat, a->rn * a->cn);

  	for (i = 0; i < a->rn; i++)
	  	for (j = 0; j < a->cn; j++)
	  		data[(j * a->rn) + i] = a->data[(i * a->cn) + j];

	g_message ("%u, %u", a->cn, a->rn);
  	crank_mat_float_n_init_arr_take (r, a->cn, a->rn, data);
}

/**
 * crank_mat_float_n_inverse:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets an inverse of matrix.
 * If the matrix is singular, then NaN matrix may be returned.
 */
void
crank_mat_float_n_inverse (	CrankMatFloatN*	a,
						  	CrankMatFloatN*	r	)
{
  	g_warning ("Not Implemented function.");
  	return;
}

/**
 * crank_mat_float_n_muls:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by scalar.
 */
void
crank_mat_float_n_muls (	CrankMatFloatN*	a,
					 	  	const gfloat	b,
					 	  	CrankMatFloatN*	r	)
{
	guint	i;
  	guint	j;

	if (a != r) crank_mat_float_n_realloc (r, a->rn, a->cn);

  	for (i = 0; i < a->rn; i++)
	  	for (j = 0; j < a->cn; j++)
	  		r->data[(i * a->cn) + j] = a->data[(i * a->cn) + j] * b;
}

/**
 * crank_mat_float_n_divs:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Divides a matrix by scalar.
 */
void
crank_mat_float_n_divs (	CrankMatFloatN*	a,
						   	const gfloat	b,
						   	CrankMatFloatN*	r	)
{
  	crank_mat_float_n_muls (a, 1 / b, r);
}


/**
 * crank_mat_float_n_mulv:
 * @a: A Matrix.
 * @b: A Vector.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by vector.
 */
void
crank_mat_float_n_mulv (	CrankMatFloatN*	a,
						   	CrankVecFloatN*	b,
						   	CrankVecFloatN*	r	)
{
  	guint	i;
  	guint	j;

  	gfloat*	data;

  	g_return_if_fail (a->cn == b->n);

  	data = g_new0 (gfloat, a->rn);

  	for (i = 0; i < a->rn; i++) {
		for (j = 0; j < a->cn; j++) {
			data[i] +=
				a->data[(a->cn * i) + j] * b->data[j];
		}
	}

  	crank_vec_float_n_init_arr_take (r, a->rn, data);
}

/**
 * crank_mat_float_n_mul:
 * @a: A Matrix.
 * @b: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies two matrices.
 */
void
crank_mat_float_n_mul (	CrankMatFloatN*	a,
					  	CrankMatFloatN* b,
					  	CrankMatFloatN* r	)
{
  	guint	i;
  	guint	j;
  	guint	k;

  	gfloat*	data;

  	g_return_if_fail (a->cn == b->rn);

  	data = g_new0 (gfloat, a->rn * b->cn);

  	for (i = 0; i < a->rn; i++) {
		for (j = 0; j < b->cn; j++) {
			for (k = 0; k < a->cn; k++) {
				data[(b->cn * i) + j] +=
					a->data[(a->cn * i) + k] *
					b->data[(b->cn * k) + j];
			}
		}
	}

  	crank_mat_float_n_init_arr_take (r, a->rn, b->cn, data);
}

/**
 * crank_mat_float_n_mixs:
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
crank_mat_float_n_mixs (	CrankMatFloatN* a,
						  	CrankMatFloatN* b,
						  	const gfloat	c,
						  	CrankMatFloatN*	r	)
{
	guint	i;
  	guint	j;

  	g_return_if_fail (a->rn == b->rn);
  	g_return_if_fail (a->cn == b->cn);

  	gfloat d = 1 - c;

  	if ((a != r) && (b != r)) crank_mat_float_n_realloc (r, a->rn, a->cn);

  	for (i = 0; i < a->rn; i++) {
	  	for (j = 0; j < a->cn; j++) {
	  		guint	ei = (i * a->cn) + j;

			r->data[ei] = a->data[ei] * d + b->data[ei] * c;
		}
	}
}

/**
 * crank_mat_float_n_mix:
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
crank_mat_float_n_mix (	CrankMatFloatN*	a,
					  	CrankMatFloatN* b,
					  	CrankMatFloatN*	c,
					  	CrankMatFloatN*	r	)
{
	guint	i;
  	guint	j;

  	g_return_if_fail (a->rn == b->rn);
  	g_return_if_fail (a->cn == b->cn);
  	g_return_if_fail (a->rn == c->rn);
  	g_return_if_fail (a->cn == c->cn);

  	if ((a != r) && (b != r) && (c != r)) crank_mat_float_n_realloc (r, a->rn, a->cn);

  	for (i = 0; i < a->rn; i++) {
	  	for (j = 0; j < a->cn; j++) {
	  		guint	ei = (i * a->cn) + j;

	  		gfloat	ce = c->data[ei];
	  		gfloat	de = 1 - ce;

			r->data[ei] = a->data[ei] * de + b->data[ei] * ce;
		}
	}
}


//////// Internal Definition ///////////////////////////////////////////////////

void
crank_mat_float_n_realloc (CrankMatFloatN *mat,
                           const guint     rn,
                           const guint     cn)
{
	mat->data = g_renew (gfloat, mat->data, rn * cn);
 	mat->rn = rn;
  	mat->cn = cn;
}
