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
  	crank_vec_float2_init_arr (((CrankVecFloat2*)mat) + 2 * index, (gfloat*)row);
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
