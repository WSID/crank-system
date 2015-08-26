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
#include "crankpermutation.h"
#include "crankcomplex.h"
#include "crankveccommon.h"
#include "crankvecfloat.h"
#include "crankveccplxfloat.h"
#include "crankadvmat.h"

#include "crankmatfloat.h"
#include "crankmatcplxfloat.h"


/**
 * SECTION: crankmatcplxfloat
 * @title: Complex Float Matrices
 * @short_description: Complex float valued matrices.
 * @stability: unstable
 * @include: crankbase.h
 *
 * Crank System provides free sized complex matrix for container of complex
 * vectors.
 *
 * Though it's main use is container of complex vector, it defines matrix
 * operations like float matrix types.
 *
 * Currently following operations are supported.
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
 *
 * # Notes about involuement of advanced operations.
 *
 * If matrices grows bigger, then it is harder and requires much operations to
 * get its property. Therefore, we need to use advanced operations to decompose
 * matrices to more simpler form.
 * For example: Crank System uses LU Decomposition to get determinent of matrices.
 */


G_DEFINE_BOXED_TYPE(CrankMatCplxFloatN, crank_mat_cplx_float_n,
					crank_mat_cplx_float_n_dup,\
					crank_mat_cplx_float_n_free)

/**
 * crank_mat_cplx_float_n_init:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @...: Elements.
 *
 * Initialize a matrix with given elements.
 */
void
crank_mat_cplx_float_n_init (	CrankMatCplxFloatN*	mat,
								const guint		rn,
								const guint		cn,
								...	)
{
  	va_list	varargs;
  	guint	i;

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);

  	va_start (varargs, cn);

  	for (i = 0; i < rn*cn; i++)
		crank_cplx_float_copy (va_arg (varargs, CrankCplxFloat*), mat->data + i);

  	va_end (varargs);
}

/**
 * crank_mat_cplx_float_n_init_arr:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @marr: (array): An array of matrix.
 *
 * Initialize a matrix with given array.
 */
void
crank_mat_cplx_float_n_init_arr (	CrankMatCplxFloatN* mat,
									const guint			rn,
									const guint			cn,
								   	CrankCplxFloat*		marr	)
{
  	guint	count = rn*cn;

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);

	memcpy (mat->data, marr, sizeof(CrankCplxFloat) * count);
}

/**
 * crank_mat_cplx_float_n_init_arr_take:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @marr: (array) (transfer full): An array of matrix.
 *
 * Initialize a matrix by taking given array
 */
void
crank_mat_cplx_float_n_init_arr_take (	CrankMatCplxFloatN* mat,
										const guint			rn,
										const guint			cn,
									   	CrankCplxFloat*		marr	)
{
  	mat->data = marr;
  	mat->rn = rn;
 	mat->cn = cn;
}


/**
 * crank_mat_cplx_float_n_init_rv:
 * @mat: (out): A Matrix.
 * @rn: Row count
 * @...: Row vectors.
 *
 * Initialize a matrix with given row vectors.
 */
void
crank_mat_cplx_float_n_init_rv (	CrankMatCplxFloatN*	mat,
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
		CrankVecCplxFloatN*	rv = va_arg (varargs_cn, CrankVecCplxFloatN*);

		cn = MAX(cn, rv->n);
	}
  	va_end (varargs_cn);

  	// Phase 2: Copy actual data to matrix data.
	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);

  	for (i = 0; i < rn; i++) {
	 	CrankVecCplxFloatN*	rv = va_arg (varargs_data, CrankVecCplxFloatN*);

	  	memcpy (mat->data + (i * cn), rv->data, rv->n);
	}
  	va_end (varargs_data);
}

/**
 * crank_mat_cplx_float_n_init_rvarr:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @rvarr: (array length=rn): An array of row vectors.
 *
 * Initialize a matrix with array of row vectors.
 */
void
crank_mat_cplx_float_n_init_rvarr (	CrankMatCplxFloatN*		mat,
								  	const guint			rn,
	 								CrankVecCplxFloatN*	rvarr	)
{
  	guint	i;
  	guint	cn = 0;

  	for (i = 0; i < rn; i++) cn = MAX(cn, (rvarr + i)->n);

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);
	
  	for (i = 0; i < rn; i++)
	  	memcpy (mat->data + (i * cn), (rvarr + i)->data, (rvarr + i)->n);
}

/**
 * crank_mat_cplx_float_n_init_rvparr:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @rvparr: (array length=rn): An array of row vectors.
 *
 * Initialize a matrix with array of row vectors.
 */
void
crank_mat_cplx_float_n_init_rvparr (	CrankMatCplxFloatN*		mat,
									  	const guint				rn,
	 									CrankVecCplxFloatN**	rvparr	)
{
  	guint	i;
  	guint	cn = 0;

  	for (i = 0; i < rn; i++) cn = MAX(cn, rvparr[i]->n);

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);
	
  	for (i = 0; i < rn; i++)
	  	memcpy (mat->data + (i * cn), rvparr[i]->data, rvparr[i]->n);
}

/**
 * crank_mat_cplx_float_n_init_cv:
 * @mat: (out): A Matrix.
 * @cn: Column count.
 * @...: Column Vectors.
 *
 * Initialize a matrix with column vectors.
 */
void
crank_mat_cplx_float_n_init_cv (	CrankMatCplxFloatN*	mat,
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
		CrankVecCplxFloatN*	cv = va_arg (varargs_rn, CrankVecCplxFloatN*);

	  	rn = MAX (rn, cv->n);
	}
  	va_end (varargs_rn);

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);
	
  	for (i = 0; i < cn; i++) {
		CrankVecCplxFloatN*	cv = va_arg (varargs_data, CrankVecCplxFloatN*);

	  	for (j = 0; j < cv->n; j++) {
	  		crank_cplx_float_copy ((cv->data + j), mat->data + (rn * j) + i);
		}
	}
  	va_end (varargs_data);

}

/**
 * crank_mat_cplx_float_n_init_cvarr:
 * @mat: (out): A Matrix.
 * @cn: Column count.
 * @cvarr: (array length=cn): An array of column vectors.
 *
 * Initialize a matrix with an array of column vectors.
 */
void
crank_mat_cplx_float_n_init_cvarr (	CrankMatCplxFloatN* 	mat,
								 	const guint				cn,
								 	CrankVecCplxFloatN*		cvarr	)
{
  	guint	rn = 0;
  	guint	i;
  	guint	j;

  	for (i = 0; i < cn; i++) rn = MAX (rn, (cvarr + i)->n);

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);
	
  	for (i = 0; i < cn; i++) {
	  	for (j = 0; j < (cvarr + i)->n; j++) {
	  		crank_cplx_float_copy((cvarr + i)->data + j, mat->data + (rn * j) + i);
		}
	}
}

/**
 * crank_mat_cplx_float_n_init_cvparr:
 * @mat: (out): A Matrix.
 * @cn: Column count.
 * @cv[arr: (array length=cn): An array of column vectors.
 *
 * Initialize a matrix with an array of column vectors.
 */
void
crank_mat_cplx_float_n_init_cvparr (	CrankMatCplxFloatN* 	mat,
									 	const guint				cn,
									 	CrankVecCplxFloatN**	cvparr	)
{
  	guint	rn = 0;
  	guint	i;
  	guint	j;

  	for (i = 0; i < cn; i++) rn = MAX (rn, cvparr[i]->n);

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);
	
  	for (i = 0; i < cn; i++) {
	  	for (j = 0; j < cvparr[i]->n; j++) {
	  		crank_cplx_float_copy(cvparr[i]->data + j, mat->data + (rn * j) + i);
		}
	}
}

/**
 * crank_mat_cplx_float_n_init_diag:
 * @mat: (out): A Matrix.
 * @n: Element count.
 * @...: Diagonal elements.
 *
 * Initialize a matrix with diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_cplx_float_n_init_diag (	CrankMatCplxFloatN*	mat,
									const guint		n,
								 	...	)
{
  	va_list	varargs;
  	guint	i;

  	va_start (varargs, n);

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, n, n);
	
 	for (i = 0; i < n; i++)
 		crank_cplx_float_copy (va_arg (varargs, CrankCplxFloat*), mat->data + (n*i) + i);

  	va_end (varargs);
}

/**
 * crank_mat_cplx_float_n_init_diag_arr:
 * @mat: (out): A Matrix.
 * @n: Element count.
 * @darr: (array length=n): An array of diagonal elements.
 *
 * Initialize a matrix with an array of diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_cplx_float_n_init_diag_arr (	CrankMatCplxFloatN*	mat,
									 	const guint			n,
										CrankCplxFloat*		darr	)
{
  	guint	i;

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, n, n);
	
 	for (i = 0; i < n; i++)
 		crank_cplx_float_copy (darr + i, mat->data + (n*i) + i);
}

/**
 * crank_mat_cplx_float_n_init_diag_vec:
 * @mat: (out): A Matrix.
 * @dvec: A vector with diagonal components.
 *
 * Initialize a matrix with a vector of diagonal elements.
 * Other elements are initialized with 0.
 */
void
crank_mat_cplx_float_n_init_diag_vec (	CrankMatCplxFloatN*	mat,
										CrankVecCplxFloatN*	dvec	)
{
	crank_mat_cplx_float_n_init_diag_arr (mat, dvec->n, dvec->data);
}

/**
 * crank_mat_cplx_float_n_init_fill:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @fill: A fill value to fill the matrix.
 *
 * Initialize a matrix by filling with a value.
 */
void
crank_mat_cplx_float_n_init_fill (	CrankMatCplxFloatN*	mat,
								 	const guint			rn,
								 	const guint			cn,
									CrankCplxFloat*		fill	)
{
  	guint	i;
  	guint	j;

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);
	
  	for (i = 0; i < rn; i++)
		for (j = 0; j < cn; j++)
			crank_cplx_float_copy (fill, mat->data + (cn * i) + j);
}

/**
 * crank_mat_cplx_float_n_init_cimm:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @...: Elements.
 *
 * Initialize a matrix with given elements. This function is different from
 * crank_mat_cplx_float_n_init(), as this function expects a pair of #gfloat,
 * rather than #CrankCplxFloat.
 */
void
crank_mat_cplx_float_n_init_cimm (	CrankMatCplxFloatN*	mat,
									const guint		rn,
									const guint		cn,
									...	)
{
  	va_list	varargs;
  	guint	i;

	CRANK_MAT_ALLOC (mat, CrankCplxFloat, rn, cn);

  	va_start (varargs, cn);

  	for (i = 0; i < rn*cn; i++)
		crank_cplx_float_init_valist (mat->data + i, varargs);

  	va_end (varargs);
}

/**
 * crank_mat_cplx_float_n_init_cuarr:
 * @mat: (out): A Matrix.
 * @rn: Row count.
 * @cn: Column count.
 * @...: Array of unrolled complex elements into real and imaginary parts.
 *
 * Initialize a matrix with given elements. This function is different from
 * crank_mat_cplx_float_n_init(), as this function expects a pair of #gfloat,
 * rather than #CrankCplxFloat.
 */
void
crank_mat_cplx_float_n_init_cuarr (	CrankMatCplxFloatN*	mat,
									const guint			rn,
									const guint			cn,
									const guint*		cuarr	)
{
	crank_mat_cplx_float_n_init_arr (mat, rn, cn, (CrankCplxFloat*)cuarr);
}


/**
 * crank_mat_cplx_float_n_copy:
 * @mat: A Matrix.
 * @other: (out): Another matrix.
 *
 * Copies a matrix to other matrix.
 */
void
crank_mat_cplx_float_n_copy (	CrankMatCplxFloatN*	mat,
					   			CrankMatCplxFloatN*	other	)
{
	crank_mat_cplx_float_n_init_arr (other, mat->rn, mat->cn, mat->data);
}

/**
 * crank_mat_cplx_float_n_dup:
 * @mat: A Matrix
 *
 * Allocates a matrix and copy on it.
 *
 * Returns: an allocated copy. Free it with g_free()
 */
CrankMatCplxFloatN*
crank_mat_cplx_float_n_dup (	CrankMatCplxFloatN*	mat	)
{
  	CrankMatCplxFloatN*	result = g_new (CrankMatCplxFloatN, 1);
	crank_mat_cplx_float_n_copy (mat, result);
  	return result;
}

/**
 * crank_mat_cplx_float_n_fini:
 * @mat: A Matrix to reset.
 *
 * Resets a matrix and frees its associated memory block.
 */
void
crank_mat_cplx_float_n_fini (	CrankMatCplxFloatN*	mat	)
{
  	g_free (mat->data);
  	mat->rn = 0;
  	mat->cn = 0;
}

/**
 * crank_mat_cplx_float_n_free:
 * @mat: A Matrix to free.
 *
 * Frees allocated matrix.
 */
void
crank_mat_cplx_float_n_free (	CrankMatCplxFloatN*	mat	)
{
	crank_mat_cplx_float_n_fini (mat);
  	g_free (mat);
}


//////// Basic Operations //////////////////////////////////////////////////////

/**
 * crank_mat_cplx_float_n_hash:
 * @a: (type CrankMatCplxFloatN): A matrix.
 *
 * Gets hash value of a matrix.
 * This is useful when using matrix as key or value for #GHashTable.
 *
 * Returns: hash value of a matrix.
 */
guint
crank_mat_cplx_float_n_hash (	gconstpointer	a	)
{
	const CrankMatCplxFloatN*	mat = (const CrankMatCplxFloatN*)a;
  	guint	i;
  	guint	j;
  	guint	count;

  	guint	hash;

  	hash =  g_direct_hash (GINT_TO_POINTER (mat->rn)) +
  			g_direct_hash (GINT_TO_POINTER (mat->cn));

	count = mat->rn * mat->cn;

  	for (i = 0; i < count; i++) {
		hash += crank_cplx_float_hash (mat->data + i);
		hash *= 33;
	}

  	return hash;
}

/**
 * crank_mat_cplx_float_n_equal:
 * @a: (type CrankMatCplxFloatN): A matrix.
 * @b: (type CrankMatCplxFloatN): A matrix.
 *
 * Compares the value of matrix and check their equality.
 * This is useful when using matrix as a key.
 *
 * Returns: %TRUE if the two are same.
 */
gboolean
crank_mat_cplx_float_n_equal (	gconstpointer	a,
								gconstpointer	b	)
{
	const CrankMatCplxFloatN*	mat_a = (const CrankMatCplxFloatN*)a;
	const CrankMatCplxFloatN*	mat_b = (const CrankMatCplxFloatN*)b;

  	guint	i;
  	guint	j;
  	guint	count;

  	if (	(mat_a->rn != mat_b->rn) ||
	   		(mat_a->cn != mat_b->cn))	return FALSE;

	count = mat_a->rn * mat_a->cn;
	
	for (i = 0; i < count; i++) {
		if (! crank_cplx_float_equal (mat_a->data + i, mat_b->data + i)) return FALSE;
	}

  	return TRUE;
}

/**
 * crank_mat_cplx_float_n_to_string:
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
crank_mat_cplx_float_n_to_string (	CrankMatCplxFloatN*	mat	)
{
  	return crank_mat_cplx_float_n_to_string_full (mat, "[", ", ", "]", "[", ", ", "]", CRANK_CPLX_FLOAT_DEFFORMAT);
}

/**
 * crank_mat_cplx_float_n_to_string_full:
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
crank_mat_cplx_float_n_to_string_full (	CrankMatCplxFloatN*	mat,
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
	  		g_string_append (builder,
	  				crank_cplx_float_to_string_full (mat->data + (i * mat->cn) + j, format)	);

		}
		g_string_append (builder, row_right);

	  }

  	g_string_append (builder, mat_right);

	str = builder->str;

	g_string_free (builder, FALSE);
	return str;
}

/**
 * crank_mat_cplx_float_n_get_row_size:
 * @mat: A Matrix.
 *
 * Gets row size (Row count) of given matrix.
 *
 * Returns: Row count of matrix.
 */
guint
crank_mat_cplx_float_n_get_row_size (	CrankMatCplxFloatN*	mat	)
{
	return mat->rn;
}

/**
 * crank_mat_cplx_float_n_get_col_size:
 * @mat: A Matrix.
 *
 * Gets column size (Column count) of given matrix.
 *
 * Returns: Column count of matrix.
 */
guint
crank_mat_cplx_float_n_get_col_size (	CrankMatCplxFloatN*	mat	)
{
	return mat->cn;
}

/**
 * crank_mat_cplx_float_n_get:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 * @value: (out): Value of element.
 *
 * Gets element at given indices.
 */
void
crank_mat_cplx_float_n_get (	CrankMatCplxFloatN*	mat,
							  	const guint			i,
							  	const guint			j,
							  	CrankCplxFloat*		value	)
{
	crank_cplx_float_copy (mat->data + (i*mat->cn) + j, value);
}

/**
 * crank_mat_cplx_float_n_set:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 * @value: Value of element.
 *
 * Sets element at given indices.
 */
void
crank_mat_cplx_float_n_set (	CrankMatCplxFloatN*	mat,
							  	const guint			i,
							  	const guint			j,
							  	CrankCplxFloat*		value	)
{
	crank_cplx_float_copy (value, mat->data + (mat->cn * i) + j);
}

/**
 * crank_mat_cplx_float_n_peek:
 * @mat: A Matrix.
 * @i: A row index.
 * @j: A Column index.
 *
 * Peeks element at given indices.
 *
 * Returns: (transfer none): A element at position.
 */
CrankCplxFloat*
crank_mat_cplx_float_n_peek (	CrankMatCplxFloatN*	mat,
							  	const guint			i,
							  	const guint			j	)
{
	return (mat->data + (i*mat->cn) + j);
}

/**
 * crank_mat_cplx_float_n_get_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: (out): A Row vector.
 *
 * Gets a row vector at given index.
 */
void
crank_mat_cplx_float_n_get_row (	CrankMatCplxFloatN*	mat,
							  		const guint			index,
							  		CrankVecCplxFloatN*	row	)
{
  	crank_vec_cplx_float_n_init_arr (row, mat->cn, mat->data + mat->cn * index);
}

/**
 * crank_mat_cplx_float_n_set_row:
 * @mat: A Matrix.
 * @index: A index.
 * @row: A Row vector.
 *
 * Sets a row vector at given index.
 */
void
crank_mat_cplx_float_n_set_row (	CrankMatCplxFloatN*	mat,
								  	const guint			index,
								  	CrankVecCplxFloatN*	row	)
{
  	g_return_if_fail (row->n <= mat->cn);
  	memcpy (mat->data + mat->cn * index,
  			row->data,
  			row->n * sizeof (CrankCplxFloat));
}


/**
 * crank_mat_cplx_float_n_get_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: (out): A Column vector.
 *
 * Gets a column vector at given index.
 */
void
crank_mat_cplx_float_n_get_col (	CrankMatCplxFloatN*	mat,
						  			const guint			index,
						  			CrankVecCplxFloatN*	col	)
{
  	guint	i;
  	CrankCplxFloat*	data;

  	data = g_new (CrankCplxFloat, mat->rn);
  	for (i = 0; i < mat->rn; i++)
  		crank_cplx_float_copy (	mat->data + (mat->cn * i) + index,
  								data + i);

  	crank_vec_cplx_float_n_init_arr_take (col, mat->rn, data);
}

/**
 * crank_mat_cplx_float_n_set_col:
 * @mat: A Matrix.
 * @index: A index.
 * @col: A Column vector.
 *
 * Sets a column vector at given index.
 */
void
crank_mat_cplx_float_n_set_col (	CrankMatCplxFloatN*	mat,
								  	const guint			index,
								  	CrankVecCplxFloatN*	col	)
{
  	guint i;

  	g_return_if_fail (col->n <= mat->rn);
  	for (i = 0; i < mat->rn; i++)
  		crank_cplx_float_copy (	col->data + i,
  								mat->data + (mat->cn * i) + index);
}

/**
 * crank_mat_cplx_float_n_slice_row:
 * @mat: A Matrix.
 * @start: Starting index.
 * @end: Ending index.
 * @r: (out): A Sliced Matrix.
 *
 * Slices rows of a matrix.
 */
void
crank_mat_cplx_float_n_slice_row (	CrankMatCplxFloatN*	mat,
									const guint		start,
									const guint		end,
									CrankMatCplxFloatN*	r	)
{
	crank_mat_cplx_float_n_slice (mat, start, 0, end, mat->cn, r);
}


/**
 * crank_mat_cplx_float_n_slice_col:
 * @mat: A Matrix.
 * @start: Starting index.
 * @end: Ending index.
 * @r: (out): A Sliced Matrix.
 *
 * Slices columns of a matrix.
 */
void
crank_mat_cplx_float_n_slice_col (	CrankMatCplxFloatN*	mat,
									const guint		start,
									const guint		end,
									CrankMatCplxFloatN*	r	)
{
	crank_mat_cplx_float_n_slice (mat, 0, start, mat->rn, end, r);
}


/**
 * crank_mat_cplx_float_n_slice:
 * @mat: A Matrix.
 * @row_start: Starting row index.
 * @col_start: Starting column index.
 * @row_end: Ending row index.
 * @col_end: Ending column index.
 * @r: (out): A Sliced Matrix.
 *
 * Slices a matrix.
 */
void
crank_mat_cplx_float_n_slice (	CrankMatCplxFloatN*	mat,
								const guint		row_start,
								const guint		col_start,
								const guint		row_end,
								const guint		col_end,
								CrankMatCplxFloatN*	r	)
{
	guint	i;
	guint	j;
	
	guint			rn;
	guint			cn;
	CrankCplxFloat*	data;
	
	g_return_if_fail (row_start <= row_end);
	g_return_if_fail (col_start <= col_end);
	
	rn = row_end - row_start;
	cn = col_end - col_start;
	data = g_new (CrankCplxFloat, rn * cn);
	
	for (i = 0; i < rn; i++) {
		for (j = 0; j < cn; j++) {
			crank_mat_cplx_float_n_get (
					mat,
					i + row_start,
					j + col_start,
					data + (i * cn) + j );
		}
	}
	
	crank_mat_cplx_float_n_init_arr_take (r, rn, cn, data);
}

/**
 * crank_mat_cplx_float_n_is_empty:
 * @mat: A Matrix to check.
 *
 * Checks a matrix is empty. (has zero row or col)
 *
 * Returns: Whether matrix is empty.
 */
gboolean
crank_mat_cplx_float_n_is_empty (	CrankMatCplxFloatN*	mat	)
{
	return (mat->rn == 0) || (mat->cn == 0);
}

/**
 * crank_mat_cplx_float_n_is_square:
 * @mat: A Matrix to check.
 *
 * Checks a matrix is square matrix.
 *
 * Returns: Whether matrix is square matrix.
 */
gboolean
crank_mat_cplx_float_n_is_square (	CrankMatCplxFloatN*	mat	)
{
	return (mat->rn == mat->cn);
}

/**
 * crank_mat_cplx_float_n_is_identity:
 * @mat: A Matrix to check.
 *
 * Checks a matrix is identity matrix.
 *
 * Returns: Whether matrix is identity matrix.
 */
gboolean
crank_mat_cplx_float_n_is_identity (	CrankMatCplxFloatN*	mat	)
{
	if (crank_mat_cplx_float_n_is_square (mat)) {
		guint	i;
		guint	j;
		
		for (i = 0; i < mat->rn; i++) {
			for (j = 0; j < mat->rn; j++) {
				CrankCplxFloat*	element = mat->data + (i + mat->cn) + j;
				if (i == j) {
					if (! ((element->real == 1) && (element->imag == 0)))
						return FALSE;
				}
				else {
					if (! ((element->real == 0) && (element->imag == 0)))
						return FALSE;
				}
			}
		}
		return TRUE;
	}
	else return FALSE;
}

/**
 * crank_mat_cplx_float_n_is_zero:
 * @mat: A Matrix to check.
 *
 * Checks a matrix is zero matrix, whose all elements are 0.
 *
 * Returns: Whether matrix is zero matrix.
 */
gboolean
crank_mat_cplx_float_n_is_zero (	CrankMatCplxFloatN*	mat	)
{
	guint	i;
	guint	count = mat->rn * mat->cn;
	
	for (i = 0; i < count; i++) {
		CrankCplxFloat*	element = mat->data + i;
		if (! ((element->real == 0) && (element->imag == 0)))
			return FALSE;
	}
	return TRUE;
}


/**
 * crank_mat_cplx_float_n_is_upper_tri:
 * @mat: A Matrix to check.
 *
 * Checks a matrix is upper triangular matrix.
 *
 * Returns: Whether matrix is upper triangular matrix.
 */
gboolean
crank_mat_cplx_float_n_is_upper_tri(CrankMatCplxFloatN*	mat	)
{
	if (crank_mat_cplx_float_n_is_square (mat)) {
		guint	i;
		guint	j;
		
		for (i = 0; i < mat->rn; i++ ) {
			for (j = 0; j < i; j++) {
				CrankCplxFloat*	e = mat->data + (i + mat->cn) + j;
				if (! ((e->real == 0) && (e->imag == 0))) return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

/**
 * crank_mat_cplx_float_n_is_lower_tri:
 * @mat: A Matrix to check.
 *
 * Checks a matrix is lower triangular matrix.
 *
 * Returns: Whether matrix is lower triangular matrix.
 */
gboolean
crank_mat_cplx_float_n_is_lower_tri(CrankMatCplxFloatN*	mat	)
{
	if (crank_mat_cplx_float_n_is_square (mat)) {
		guint	i;
		guint	j;
		
		for (i = 0; i < mat->rn; i++ ) {
			for (j = i+1; j < mat->cn; j++) {
				CrankCplxFloat*	e = mat->data + (i + mat->cn) + j;
				if (! ((e->real == 0) && (e->imag == 0))) return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

/**
 * crank_mat_cplx_float_n_is_diag:
 * @mat: A Matrix to check.
 *
 * Checks a matrix is diagonal matrix.
 *
 * Returns: Whether matrix is diagonal matrix.
 */
gboolean
crank_mat_cplx_float_n_is_diag (	CrankMatCplxFloatN*	mat	)
{
	if (crank_mat_cplx_float_n_is_square (mat)) {
		guint	i;
		guint	j;
		
		for (i = 0; i < mat->rn; i++ ) {
			for (j = 0; j < mat->cn; j++) {
				CrankCplxFloat*	e;
				
				if (i != j) {
					e = mat->data + (i + mat->cn) + j;
					if (! ((e->real == 0) && (e->imag == 0))) return FALSE;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

/**
 * crank_mat_cplx_float_n_is_symmetric:
 * @mat: A Matrix to check.
 *
 * Checks a matrix is symmetric matrix.
 *
 * Returns: Whether matrix is symmetric matrix.
 */
gboolean
crank_mat_cplx_float_n_is_symmetric (	CrankMatCplxFloatN*	mat	)
{
	if (crank_mat_cplx_float_n_is_square (mat)) {
		guint	i;
		guint	j;
		
		for (i = 1; i < mat->rn; i++) {
			for (j = 0; j < i; j++) {
				if (! crank_cplx_float_equal (	mat->data + (i + mat->cn) + j,
												mat->data + (j + mat->cn) + i ))
					return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

/**
 * crank_mat_cplx_float_n_has_nan:
 * @mat: A Matrix to check.
 *
 * Checks a matrix has NaN value.
 *
 * If a matrix has NaN value, operations result in scalar NaN, or vector/matrix
 * contain NaN values.
 *
 * Returns: Whether matrix has NaN.
 */
gboolean
crank_mat_cplx_float_n_has_nan (	CrankMatCplxFloatN* mat )
{
	guint i;
	guint n;
	
	n = mat->rn * mat->cn;
	
	for (i = 0; i < n; i++) {
		if (crank_cplx_float_has_nan(mat->data + i)) return TRUE;
	}
	return FALSE;
}


/**
 * crank_mat_cplx_float_n_has_inf:
 * @mat: A Matrix to check.
 *
 * Checks a matrix has infinity.
 *
 * If a matrix has NaN value, operations result in scalar infinity, or vector/
 * matrix contain infinity values.
 *
 * Returns: Whether matrix has infinity.
 */
gboolean
crank_mat_cplx_float_n_has_inf (	CrankMatCplxFloatN* mat )
{
	guint i;
	guint n;
	
	n = mat->rn * mat->cn;
	
	for (i = 0; i < n; i++) {
		if (crank_cplx_float_has_inf(mat->data + i)) return TRUE;
	}
	return FALSE;
}



/**
 * crank_mat_cplx_float_n_get_tr:
 * @mat: A Matrix
 * @tr: (out): Trace of matrix.
 *
 * Gets a trace of matrix.
 *
 * A trace is sum of diagonal elements.
 *
 * Returns: A trace of matrix.
 */
void
crank_mat_cplx_float_n_get_tr (	CrankMatCplxFloatN*	mat,
								CrankCplxFloat*		tr	)
{
	guint	i;

	crank_cplx_float_init (tr, 0, 0);

	CRANK_MAT_WARN_IF_NON_SQUARE("MatCplxFloatN", "tr", mat);	

	for (i = 0; i < mat->rn; i++)
		crank_cplx_float_add_self (tr, mat->data + (mat->cn * i) + i);
}

/**
 * crank_mat_cplx_float_n_get_det:
 * @mat: A Matrix
 * @det: (out): Determinant of 
 *
 * Gets a determinent of matrix.
 *
 * This is computed by LU Decomposition, for performance.
 *
 * Returns: A determinent of matrix.
 */
void
crank_mat_cplx_float_n_get_det (	CrankMatCplxFloatN* mat,
									CrankCplxFloat*		det	)
{
	CrankMatCplxFloatN	l;
	CrankMatCplxFloatN	u;
	
	guint i;
	
	CRANK_MAT_WARN_IF_NON_SQUARE("MatCplxFloatN", "det", mat);
	
	
	if (crank_lu_mat_cplx_float_n (mat, &l, &u)) {
	
		crank_cplx_float_init (det, 1.0f, 0.0f);
		
		for (i = 0; i < mat->rn; i++) {
		
			CrankCplxFloat	lcomp;
			crank_mat_cplx_float_n_get (&l, i, i, &lcomp);
			crank_cplx_float_mul_self (det, &lcomp);
		}
			
		crank_mat_cplx_float_n_fini (&l);
		crank_mat_cplx_float_n_fini (&u);
	}
	else {
		crank_cplx_float_init (det, 0.0f, 0.0f);
	}
}

/**
 * crank_mat_cplx_float_n_get_diag:
 * @mat: A Matrix.
 * @r: (out): A Diagonal vector.
 *
 * Gets diagonal components as vector.
 */
void
crank_mat_cplx_float_n_get_diag (CrankMatCplxFloatN*	mat,
								CrankVecCplxFloatN*		r	)
{
	guint	i;

	CRANK_MAT_WARN_IF_NON_SQUARE("MatCplxFloatN", "diag", mat);
	
	CrankCplxFloat*	data = g_new (CrankCplxFloat, mat->rn);
	
	for (i = 0; i < mat->rn; i++)
		crank_mat_cplx_float_n_get (mat, i, i, data + i);
	
	crank_vec_cplx_float_n_init_arr_take (r, mat->rn, data);
}

/**
 * crank_mat_cplx_float_n_get_cof:
 * @mat: A Matrix.
 * @r: (out): A cofactor matrix.
 *
 * Gets a cofactor matrix.
 */
void
crank_mat_cplx_float_n_get_cof (	CrankMatCplxFloatN*	mat,
								  	CrankMatCplxFloatN*	r	)
{
	CRANK_MAT_WARN_IF_NON_SQUARE("MatCplxFloatN", "cof", mat);	
	crank_mat_cplx_float_n_get_adj (mat, r);
  	crank_mat_cplx_float_n_transpose_self (r);
}

/**
 * crank_mat_cplx_float_n_get_adj:
 * @mat: A Matrix.
 * @r: (out): A adjugate matrix.
 *
 * Gets a adjugate matrix.
 */
void
crank_mat_cplx_float_n_get_adj (	CrankMatCplxFloatN*	mat,
								  	CrankMatCplxFloatN*	r	)
{
	CrankMatCplxFloatN	l;
	CrankMatCplxFloatN	u;
	CrankMatCplxFloatN	linv;
	CrankMatCplxFloatN	uinv;
	CrankCplxFloat		det;
	
	guint i;
	
	CRANK_MAT_WARN_IF_NON_SQUARE("MatCplxFloatN", "adj", mat);
	
	if (crank_lu_mat_cplx_float_n (mat, &l, &u)) {
	
		crank_cplx_float_init (&det, 1.0f, 0.0f);
		
		for (i = 0; i < mat->rn; i++) {
			CrankCplxFloat	lcomp;
			crank_mat_cplx_float_n_get (&l, i, i, &lcomp);
			crank_cplx_float_mul_self (&det, &lcomp);
		}
		
		crank_mat_cplx_float_n_lower_tri_invserse (&l, &linv);
		crank_mat_cplx_float_n_upper_tri_invserse (&u, &uinv);
		
		crank_mat_cplx_float_n_mul (&uinv, &linv, r);
		crank_mat_cplx_float_n_muls_self (r, &det);
		
		crank_mat_cplx_float_n_fini (&l);
		crank_mat_cplx_float_n_fini (&u);
		crank_mat_cplx_float_n_fini (&linv);
		crank_mat_cplx_float_n_fini (&uinv);
	}
}

/**
 * crank_mat_cplx_float_n_get_real:
 * @mat: A Matrix.
 * @r: (out): Real part of matrix.
 *
 * Gets real part of elements as matrix.
 */
void
crank_mat_cplx_float_n_get_real (	CrankMatCplxFloatN*	mat,
									CrankMatFloatN*		r	)
{
	guint	i;
	guint	count;
	
	gfloat*	data =	g_new (gfloat, mat->rn * mat->cn);
	
	count = mat->rn * mat->cn;
	
	for (i = 0; i < count; i++) {
		data[i] = mat->data[i].real;
	}
	
	r->data = data;
	r->rn = mat->rn;
	r->cn = mat->cn;
}


/**
 * crank_mat_cplx_float_n_get_imag:
 * @mat: A Matrix.
 * @r: (out): Real part of matrix.
 *
 * Gets imaginary part of elements as matrix.
 */
void
crank_mat_cplx_float_n_get_imag (	CrankMatCplxFloatN*	mat,
									CrankMatFloatN*		r	)
{
	guint	i;
	guint	count;
	
	gfloat*	data =	g_new (gfloat, mat->rn * mat->cn);
	
	count = mat->rn * mat->cn;
	
	for (i = 0; i < count; i++) {
		data[i] = mat->data[i].imag;
	}
	
	r->data = data;
	r->rn = mat->rn;
	r->cn = mat->cn;
}

/**
 * crank_mat_cplx_float_n_set_real:
 * @mat: A Matrix.
 * @r: Real part of matrix.
 *
 * Gets real part of elements as matrix.
 */
void
crank_mat_cplx_float_n_set_real (	CrankMatCplxFloatN*	mat,
									CrankMatFloatN*		r	)
{
	guint	i;
	guint	count;
	
	count = mat->rn * mat->cn;
	
	for (i = 0; i < count; i++) {
		mat->data[i].real = r->data[i];
	}
}


/**
 * crank_mat_cplx_float_n_set_imag:
 * @mat: A Matrix.
 * @r: Real part of matrix.
 *
 * Gets imaginary part of elements as matrix.
 */
void
crank_mat_cplx_float_n_set_imag (	CrankMatCplxFloatN*	mat,
									CrankMatFloatN*		r	)
{
	guint	i;
	guint	count;
	
	count = mat->rn * mat->cn;
	
	for (i = 0; i < count; i++) {
		mat->data[i].imag = r->data[i];
	}
}

/**
 * crank_mat_cplx_float_n_neg:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Negates a matrix.
 */
void
crank_mat_cplx_float_n_neg (	CrankMatCplxFloatN*	a,
					  			CrankMatCplxFloatN* r	)
{
  	guint	i;
  	guint	j;

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

	for (i = 0; i < a->rn; i ++) {
		for (j = 0; j < a->cn; j ++) {
			guint	ei = (a->cn * i) + j;
			crank_cplx_float_neg (a->data + ei, r->data + ei);
		}
	}
}

/**
 * crank_mat_cplx_float_n_transpose:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets a transpose of matrix.
 */
void
crank_mat_cplx_float_n_transpose (	CrankMatCplxFloatN*	a,
									CrankMatCplxFloatN*	r	)
{
  	guint	i;
  	guint	j;

  	CrankCplxFloat*	data = g_new (CrankCplxFloat, a->rn * a->cn);

  	for (i = 0; i < a->rn; i++)
	  	for (j = 0; j < a->cn; j++)
	  		crank_cplx_float_copy (
	  				a->data + (i * a->cn) + j,
	  				data + (j * a->rn) + i		);

  	crank_mat_cplx_float_n_init_arr_take (r, a->cn, a->rn, data);
}

/**
 * crank_mat_cplx_float_n_inverse:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets an inverse of matrix.
 * If the matrix is singular, then NaN matrix may be returned.
 */
void
crank_mat_cplx_float_n_inverse (	CrankMatCplxFloatN*	a,
						  			CrankMatCplxFloatN*	r	)
{
	CrankMatCplxFloatN	l;
	CrankMatCplxFloatN	u;
	
	guint i;
	
	CRANK_MAT_WARN_IF_NON_SQUARE("MatCplxFloatN", "inverse", a);
	
	if (crank_lu_mat_cplx_float_n (a, &l, &u)) {
	
		CrankMatCplxFloatN	linv;
		CrankMatCplxFloatN	uinv;
		
		crank_mat_cplx_float_n_lower_tri_invserse (&l, &linv);
		crank_mat_cplx_float_n_upper_tri_invserse (&u, &uinv);
		
		crank_mat_cplx_float_n_mul (&uinv, &linv, r);
			
		crank_mat_cplx_float_n_fini (&l);
		crank_mat_cplx_float_n_fini (&u);
		crank_mat_cplx_float_n_fini (&linv);
		crank_mat_cplx_float_n_fini (&uinv);
	}
	else {
		// TODO: Warn a things.
	}
}


/**
 * crank_mat_cplx_float_n_conjugate:
 * @a: A Matrix
 * @r: (out): A Matrix to store result.
 *
 * Gets an conjugation of matrix.
 */
void
crank_mat_cplx_float_n_conjugate (	CrankMatCplxFloatN*	a,
									CrankMatCplxFloatN*	r	)
{
	guint	i;
	guint	count;

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;
	
	count = a->rn * a->cn;
	
	for (i = 0; i < count; i++) {
		crank_cplx_float_conjugate (a->data + i, r->data + i);
	}
}

/**
 * crank_mat_cplx_float_n_star:
 * @a: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Gets a star of matrix, a.k.a, conjugate transpose.
 */
void
crank_mat_cplx_float_n_star (	CrankMatCplxFloatN*	a,
								CrankMatCplxFloatN*	r	)
{
  	guint	i;
  	guint	j;

  	CrankCplxFloat*	data = g_new (CrankCplxFloat, a->rn * a->cn);

  	for (i = 0; i < a->rn; i++)
	  	for (j = 0; j < a->cn; j++)
	  		crank_cplx_float_conjugate (
	  				a->data + (i * a->cn) + j,
	  				data + (j * a->rn) + i		);

  	crank_mat_cplx_float_n_init_arr_take (r, a->cn, a->rn, data);
}

/**
 * crank_mat_cplx_float_n_neg_self:
 * @a: A Matrix.
 *
 * Negates a matrix.
 */
void
crank_mat_cplx_float_n_neg_self (	CrankMatCplxFloatN*	a	)
{
  	guint	i;
  	guint	n;

	n = a->rn * a->cn;

	for (i = 0; i < n; i ++)	crank_cplx_float_neg_self (a->data + i);
}

/**
 * crank_mat_cplx_float_n_transpose_self:
 * @a: A Matrix.
 *
 * Gets a transpose of matrix.
 */
void
crank_mat_cplx_float_n_transpose_self (	CrankMatCplxFloatN*	a	)
{
  	guint	i;
  	guint	j;

  	CrankCplxFloat*	data = g_new (CrankCplxFloat, a->rn * a->cn);

  	for (i = 0; i < a->rn; i++)
	  	for (j = 0; j < a->cn; j++)
	  		crank_cplx_float_copy (
	  				a->data + (i * a->cn) + j,
	  				data + (j * a->rn) + i		);

	g_free (a->data);
  	crank_mat_cplx_float_n_init_arr_take (a, a->cn, a->rn, data);
}

/**
 * crank_mat_cplx_float_n_inverse_self:
 * @a: A Matrix.
 *
 * Gets an inverse of matrix.
 * If the matrix is singular, then NaN matrix may be returned.
 */
void
crank_mat_cplx_float_n_inverse_self (	CrankMatCplxFloatN*	a	)
{
	CrankMatCplxFloatN	l;
	CrankMatCplxFloatN	u;
	
	guint i;
	
	CRANK_MAT_WARN_IF_NON_SQUARE("MatCplxFloatN", "inverse", a);
	
	if (crank_lu_mat_cplx_float_n (a, &l, &u)) {
	
		CrankMatCplxFloatN	linv;
		CrankMatCplxFloatN	uinv;
		
		crank_mat_cplx_float_n_lower_tri_invserse (&l, &linv);
		crank_mat_cplx_float_n_upper_tri_invserse (&u, &uinv);
		
		crank_mat_cplx_float_n_fini (a);
		crank_mat_cplx_float_n_mul (&uinv, &linv, a);
			
		crank_mat_cplx_float_n_fini (&l);
		crank_mat_cplx_float_n_fini (&u);
		crank_mat_cplx_float_n_fini (&linv);
		crank_mat_cplx_float_n_fini (&uinv);
	}
	else {
		// TODO: Warn a things.
	}
}


/**
 * crank_mat_cplx_float_n_conjugate_self:
 * @a: A Matrix
 *
 * Gets an conjugation of matrix.
 */
void
crank_mat_cplx_float_n_conjugate_self (	CrankMatCplxFloatN*	a	)
{
	guint	i;
	guint	n;
	
	n = a->rn * a->cn;
	
	for (i = 0; i < n; i++)		crank_cplx_float_conjugate_self (a->data + i);
}

/**
 * crank_mat_cplx_float_n_star_self:
 * @a: A Matrix.
 *
 * Gets a star of matrix, a.k.a, conjugate transpose.
 */
void
crank_mat_cplx_float_n_star_self (	CrankMatCplxFloatN*	a	)
{
  	guint	i;
  	guint	j;

  	CrankCplxFloat*	data = g_new (CrankCplxFloat, a->rn * a->cn);

  	for (i = 0; i < a->rn; i++)
	  	for (j = 0; j < a->cn; j++)
	  		crank_cplx_float_conjugate (
	  				a->data + (i * a->cn) + j,
	  				data + (j * a->rn) + i		);

	g_free (a->data);
  	crank_mat_cplx_float_n_init_arr_take (a, a->cn, a->rn, data);
}

/**
 * crank_mat_cplx_float_n_mulrs:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by scalar.
 */
void
crank_mat_cplx_float_n_mulrs (	CrankMatCplxFloatN*	a,
					 	  		const gfloat		b,
					 	  		CrankMatCplxFloatN*	r	)
{
	guint	i;
  	guint	j;
  	
  	g_return_if_fail (a != r);

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

  	for (i = 0; i < a->rn; i++)
	  	for (j = 0; j < a->cn; j++)
	  		crank_cplx_float_mulr (	a->data + (i * a->cn) + j,
	  								b,
	  								r->data + (i * a->cn) + j	);
}

/**
 * crank_mat_cplx_float_n_divrs:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Divides a matrix by scalar.
 */
void
crank_mat_cplx_float_n_divrs (	CrankMatCplxFloatN*	a,
						   		const gfloat		b,
						   		CrankMatCplxFloatN*	r	)
{
  	g_return_if_fail (a != r);
  	crank_mat_cplx_float_n_mulrs (a, 1 / b, r);
}

/**
 * crank_mat_cplx_float_n_muls:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by scalar.
 */
void
crank_mat_cplx_float_n_muls (	CrankMatCplxFloatN*	a,
					 	  		CrankCplxFloat*		b,
					 	  		CrankMatCplxFloatN*	r	)
{
	guint	i;
  	guint	j;

  	g_return_if_fail (a != r);

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

  	for (i = 0; i < a->rn; i++)
	  	for (j = 0; j < a->cn; j++)
	  		crank_cplx_float_mul (	a->data + (i * a->cn) + j,
	  								b,
	  								r->data + (i * a->cn) + j	);
}

/**
 * crank_mat_cplx_float_n_divs:
 * @a: A Matrix.
 * @b: A Scalar.
 * @r: (out): A Matrix to store result.
 *
 * Divides a matrix by scalar.
 */
void
crank_mat_cplx_float_n_divs (	CrankMatCplxFloatN*	a,
						   		CrankCplxFloat*		b,
						   		CrankMatCplxFloatN*	r	)
{
	CrankCplxFloat	binv;
	
  	g_return_if_fail (a != r);

	crank_cplx_float_inverse (b, &binv);
  	crank_mat_cplx_float_n_muls (a, &binv, r);
}




/**
 * crank_mat_cplx_float_n_mulrs_self:
 * @a: A Matrix.
 * @b: A Scalar.
 *
 * Multiplies a matrix by scalar.
 */
void
crank_mat_cplx_float_n_mulrs_self (	CrankMatCplxFloatN*	a,
					 	  			const gfloat		b	)
{
	guint	i;
  	guint	n;
  	
  	n = a->rn * a->cn;

  	for (i = 0; i < n; i++)
  		crank_cplx_float_mulr_self (	a->data + i,	b	);
}

/**
 * crank_mat_cplx_float_n_divrs_self:
 * @a: A Matrix.
 * @b: A Scalar.
 *
 * Divides a matrix by scalar.
 */
void
crank_mat_cplx_float_n_divrs_self (	CrankMatCplxFloatN*	a,
						   			const gfloat		b	)
{
  	crank_mat_cplx_float_n_mulrs_self (a, 1 / b);
}

/**
 * crank_mat_cplx_float_n_muls_self:
 * @a: A Matrix.
 * @b: A Scalar.
 *
 * Multiplies a matrix by scalar.
 */
void
crank_mat_cplx_float_n_muls_self (	CrankMatCplxFloatN*	a,
					 	  			CrankCplxFloat*		b	)
{
	guint	i;
  	guint	n;

	n = a->rn * a->cn;

  	for (i = 0; i < n; i++)
  		crank_cplx_float_mul_self (	a->data + i,	b	);
}

/**
 * crank_mat_cplx_float_n_divs_self:
 * @a: A Matrix.
 * @b: A Scalar.
 *
 * Divides a matrix by scalar.
 */
void
crank_mat_cplx_float_n_divs_self (	CrankMatCplxFloatN*	a,
						   			CrankCplxFloat*		b	)
{
	CrankCplxFloat	binv;
	crank_cplx_float_inverse (b, &binv);
  	crank_mat_cplx_float_n_muls_self (a, &binv);
}




/**
 * crank_mat_cplx_float_n_mulrv:
 * @a: A Matrix.
 * @b: A Vector.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by vector.
 */
void
crank_mat_cplx_float_n_mulrv (	CrankMatCplxFloatN*	a,
						   		CrankVecFloatN*		b,
						   		CrankVecCplxFloatN*	r	)
{
  	guint	i;
  	guint	j;

  	CrankCplxFloat*	data;

  	g_return_if_fail (a->cn == b->n);

  	data = g_new0 (CrankCplxFloat, a->rn);

  	for (i = 0; i < a->rn; i++) {
		for (j = 0; j < a->cn; j++) {
			CrankCplxFloat	mul;
			crank_cplx_float_mulr (	a->data + (a->cn * i) + j,
									b->data [j],
									&mul	);
			crank_cplx_float_add_self (	data + i,	&mul	);
		}
	}

  	crank_vec_cplx_float_n_init_arr_take (r, a->rn, data);
}

/**
 * crank_mat_cplx_float_n_mulv:
 * @a: A Matrix.
 * @b: A Vector.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies a matrix by vector.
 */
void
crank_mat_cplx_float_n_mulv (	CrankMatCplxFloatN*	a,
						   		CrankVecCplxFloatN*	b,
						   		CrankVecCplxFloatN*	r	)
{
  	guint	i;
  	guint	j;

  	CrankCplxFloat*	data;
  	
  	g_return_if_fail (b != r);

  	g_return_if_fail (a->cn == b->n);

  	data = g_new0 (CrankCplxFloat, a->rn);

  	for (i = 0; i < a->rn; i++) {
		for (j = 0; j < a->cn; j++) {
			CrankCplxFloat	mul;
			crank_cplx_float_mul (	a->data + (a->cn * i) + j,
									b->data + j,
									&mul	);
			crank_cplx_float_add_self (	data + i,	&mul	);
		}
	}

  	crank_vec_cplx_float_n_init_arr_take (r, a->rn, data);
}


/**
 * crank_mat_cplx_float_n_addr:
 * @a: A Matrix
 * @b: A Matrix
 * @r: (out): A Matrix to store result.
 *
 * Adds a matrix.
 */
void
crank_mat_cplx_float_n_addr (	CrankMatCplxFloatN*	a,
					  			CrankMatFloatN*	b,
					  			CrankMatCplxFloatN*	r	)
{
  	guint	i;
  	guint	j;

	g_return_if_fail (a != r);
	CRANK_MAT_WARN_IF_SIZE_MISMATCH2("MatCplxFloatN", "add-real", a, b);

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

  	for (i = 0; i < a->rn; i++) {
	  	for (j = 0; j < a->cn; j++) {
	  		guint	ei = (i * a->cn) + j;
			crank_cplx_float_addr (a->data + ei,	b->data[ei],	r->data + ei);
		}
	}
}

/**
 * crank_mat_cplx_float_n_subr:
 * @a: A Matrix
 * @b: A Matrix
 * @r: (out): A Matrix to store result.
 *
 * Subtracts a matrix.
 */
void
crank_mat_cplx_float_n_subr (	CrankMatCplxFloatN*	a,
							  	CrankMatFloatN*	b,
							  	CrankMatCplxFloatN*	r	)
{
  	guint	i;
  	guint	j;

	g_return_if_fail (a != r);
	CRANK_MAT_WARN_IF_SIZE_MISMATCH2("MatCplxFloatN", "sub-real", a, b);

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

  	for (i = 0; i < a->rn; i++) {
	  	for (j = 0; j < a->cn; j++) {
	  		guint	ei = (i * a->cn) + j;
			crank_cplx_float_subr (a->data + ei,	b->data [ei],	r->data + ei);
		}
	}
}

/**
 * crank_mat_cplx_float_n_mulr:
 * @a: A Matrix.
 * @b: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies two matrices.
 */
void
crank_mat_cplx_float_n_mulr (	CrankMatCplxFloatN*	a,
					  			CrankMatFloatN* b,
					  			CrankMatCplxFloatN* r	)
{
  	guint	i;
  	guint	j;
  	guint	k;

  	CrankCplxFloat*	data;

	g_return_if_fail (a != r);
  	g_return_if_fail (a->cn == b->rn);

  	data = g_new0 (CrankCplxFloat, a->rn * b->cn);

  	for (i = 0; i < a->rn; i++) {
		for (j = 0; j < b->cn; j++) {
			for (k = 0; k < a->cn; k++) {
				CrankCplxFloat	mul;
				crank_cplx_float_mulr (	a->data + (a->cn * i) + k,
										b->data [(b->cn * k) + j],
										&mul	);

				crank_cplx_float_add_self (	data + (b->cn * i) + j,
											&mul	);
			}
		}
	}

  	crank_mat_cplx_float_n_init_arr_take (r, a->rn, b->cn, data);
}


/**
 * crank_mat_cplx_float_n_add:
 * @a: A Matrix
 * @b: A Matrix
 * @r: (out): A Matrix to store result.
 *
 * Adds a matrix.
 */
void
crank_mat_cplx_float_n_add (	CrankMatCplxFloatN*	a,
					  			CrankMatCplxFloatN*	b,
					  			CrankMatCplxFloatN*	r	)
{
  	guint	i;
  	guint	j;

	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_MAT_WARN_IF_SIZE_MISMATCH2("MatCplxFloatN", "add", a, b);

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

  	for (i = 0; i < a->rn; i++) {
	  	for (j = 0; j < a->cn; j++) {
	  		guint	ei = (i * a->cn) + j;
			crank_cplx_float_add (a->data + ei,	b->data + ei,	r->data + ei);
		}
	}
}

/**
 * crank_mat_cplx_float_n_sub:
 * @a: A Matrix
 * @b: A Matrix
 * @r: (out): A Matrix to store result.
 *
 * Subtracts a matrix.
 */
void
crank_mat_cplx_float_n_sub (	CrankMatCplxFloatN*	a,
							  	CrankMatCplxFloatN*	b,
							  	CrankMatCplxFloatN*	r	)
{
  	guint	i;
  	guint	j;

	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_MAT_WARN_IF_SIZE_MISMATCH2("MatCplxFloatN", "sub", a, b);

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

  	for (i = 0; i < a->rn; i++) {
	  	for (j = 0; j < a->cn; j++) {
	  		guint	ei = (i * a->cn) + j;

			crank_cplx_float_sub (a->data + ei,	b->data + ei,	r->data + ei);
		}
	}
}

/**
 * crank_mat_cplx_float_n_mul:
 * @a: A Matrix.
 * @b: A Matrix.
 * @r: (out): A Matrix to store result.
 *
 * Multiplies two matrices.
 */
void
crank_mat_cplx_float_n_mul (	CrankMatCplxFloatN*	a,
					  			CrankMatCplxFloatN* b,
					  			CrankMatCplxFloatN* r	)
{
  	guint	i;
  	guint	j;
  	guint	k;

  	CrankCplxFloat*	data;

	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
  	g_return_if_fail (a->cn == b->rn);

  	data = g_new0 (CrankCplxFloat, a->rn * b->cn);

  	for (i = 0; i < a->rn; i++) {
		for (j = 0; j < b->cn; j++) {
			for (k = 0; k < a->cn; k++) {
				CrankCplxFloat	mul;
				crank_cplx_float_mul (	a->data + (a->cn * i) + k,
										b->data + (b->cn * k) + j,
										&mul	);

				crank_cplx_float_add_self (	data + (b->cn * i) + j,
											&mul	);
			}
		}
	}

  	crank_mat_cplx_float_n_init_arr_take (r, a->rn, b->cn, data);
}





/**
 * crank_mat_cplx_float_n_addr_self:
 * @a: A Matrix
 * @b: A Matrix
 *
 * Adds a matrix.
 */
void
crank_mat_cplx_float_n_addr_self (	CrankMatCplxFloatN*	a,
					  				CrankMatFloatN*		b	)
{
  	guint	i;
  	guint	n;

	CRANK_MAT_WARN_IF_SIZE_MISMATCH2 ("MatCplxFloatN", "addr-self", a, b);
	
	n = a->rn * a->cn;

	for (i = 0; i < n; i++)
		crank_cplx_float_addr_self (a->data + i, b->data[i]);
}

/**
 * crank_mat_cplx_float_n_subr_self:
 * @a: A Matrix
 * @b: A Matrix
 *
 * Subtracts a matrix.
 */
void
crank_mat_cplx_float_n_subr_self (	CrankMatCplxFloatN*	a,
							  		CrankMatFloatN*		b	)
{
  	guint	i;
  	guint	n;

	CRANK_MAT_WARN_IF_SIZE_MISMATCH2 ("MatCplxFloatN", "subr-self", a, b);

	n = a->rn * a->cn;

  	for (i = 0; i < n; i++)
		crank_cplx_float_subr_self (a->data + i, b->data [i]);
}

/**
 * crank_mat_cplx_float_n_mulr_self:
 * @a: A Matrix.
 * @b: A Matrix.
 *
 * Multiplies two matrices.
 */
void
crank_mat_cplx_float_n_mulr_self (	CrankMatCplxFloatN*	a,
						  			CrankMatFloatN* 	b	)
{
  	guint	i;
  	guint	j;
  	guint	k;

  	CrankCplxFloat*	data;

	
  	g_return_if_fail (a->cn == b->rn);

  	data = g_new0 (CrankCplxFloat, a->rn * b->cn);

  	for (i = 0; i < a->rn; i++) {
		for (j = 0; j < b->cn; j++) {
			for (k = 0; k < a->cn; k++) {
				CrankCplxFloat	mul;
				crank_cplx_float_mulr (	a->data + (a->cn * i) + k,
										b->data [(b->cn * k) + j],
										&mul	);

				crank_cplx_float_add_self (	data + (b->cn * i) + j,
											&mul	);
			}
		}
	}

	g_free (a->data);
  	crank_mat_cplx_float_n_init_arr_take (a, a->rn, b->cn, data);
}


/**
 * crank_mat_cplx_float_n_add_self:
 * @a: A Matrix
 * @b: A Matrix
 *
 * Adds a matrix.
 */
void
crank_mat_cplx_float_n_add_self (	CrankMatCplxFloatN*	a,
					  				CrankMatCplxFloatN*	b	)
{
  	guint	i;
  	guint	n;

	CRANK_MAT_WARN_IF_SIZE_MISMATCH2 ("MatCplxFloatN", "add-self", a, b);

	n = a->rn * a->cn;

  	for (i = 0; i < n; i++)
		crank_cplx_float_add_self (a->data + i, b->data + i);
}

/**
 * crank_mat_cplx_float_n_sub_self:
 * @a: A Matrix
 * @b: A Matrix
 *
 * Subtracts a matrix.
 */
void
crank_mat_cplx_float_n_sub_self (	CrankMatCplxFloatN*	a,
							  		CrankMatCplxFloatN*	b	)
{
  	guint	i;
  	guint	n;

	CRANK_MAT_WARN_IF_SIZE_MISMATCH2 ("MatCplxFloatN", "sub-self", a, b);

	n = a->rn * a->cn;

  	for (i = 0; i < n; i++)
		crank_cplx_float_sub_self (a->data + i,	b->data + i);
}

/**
 * crank_mat_cplx_float_n_mul_self:
 * @a: A Matrix.
 * @b: A Matrix.
 *
 * Multiplies two matrices.
 */
void
crank_mat_cplx_float_n_mul_self (	CrankMatCplxFloatN*	a,
					  				CrankMatCplxFloatN* b	)
{
  	guint	i;
  	guint	j;
  	guint	k;

  	CrankCplxFloat*	data;

  	g_return_if_fail (a->cn == b->rn);

  	data = g_new0 (CrankCplxFloat, a->rn * b->cn);

  	for (i = 0; i < a->rn; i++) {
		for (j = 0; j < b->cn; j++) {
			for (k = 0; k < a->cn; k++) {
				CrankCplxFloat	mul;
				crank_cplx_float_mul (	a->data + (a->cn * i) + k,
										b->data + (b->cn * k) + j,
										&mul	);

				crank_cplx_float_add_self (	data + (b->cn * i) + j,
											&mul	);
			}
		}
	}

	g_free (a->data);
  	crank_mat_cplx_float_n_init_arr_take (a, a->rn, b->cn, data);
}




/**
 * crank_mat_cplx_float_n_mixs:
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
crank_mat_cplx_float_n_mixs (	CrankMatCplxFloatN* a,
						  	CrankMatCplxFloatN* b,
						  	const gfloat	c,
						  	CrankMatCplxFloatN*	r	)
{
	guint	i;
  	guint	j;

	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_MAT_WARN_IF_SIZE_MISMATCH2 ("MatCplxFloatN", "mix-scalar", a, b);

  	gfloat d = 1 - c;

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

  	for (i = 0; i < a->rn; i++) {
	  	for (j = 0; j < a->cn; j++) {
	  		guint	ei = (i * a->cn) + j;

			crank_cplx_float_mix (	a->data + ei,
									b->data + ei,	c,
									r->data + ei);
		}
	}
}

/**
 * crank_mat_cplx_float_n_mix:
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
crank_mat_cplx_float_n_mix (	CrankMatCplxFloatN*	a,
					  			CrankMatCplxFloatN* b,
					  			CrankMatFloatN*		c,
					  			CrankMatCplxFloatN*	r	)
{
	guint	i;
  	guint	j;

	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_MAT_WARN_IF_SIZE_MISMATCH3 ("MatCplxFloatN", "mix-scalar", a, b, c);

	r->data = g_new (CrankCplxFloat, a->rn * a->cn);
	r->rn = a->rn;
	r->cn = a->cn;

  	for (i = 0; i < a->rn; i++) {
	  	for (j = 0; j < a->cn; j++) {
	  		guint	ei = (i * a->cn) + j;

			crank_cplx_float_mix (	a->data + ei,
									b->data + ei, c->data[ei],
									r->data + ei	);
		}
	}
}


//////// Shuffling /////////////////////////////////////////////////////////////

/**
 * crank_mat_cplx_float_n_shuffle_row:
 * @a: A Matrix
 * @p: A Permutation to shuffle row.
 * @r: (out): A Matrix to store result.
 *
 * Shuffles row vectors by given permutation.
 */
void
crank_mat_cplx_float_n_shuffle_row (	CrankMatCplxFloatN*		a,
								CrankPermutation*	p,
								CrankMatCplxFloatN*		r	)
{
	CrankCplxFloat*	data;
	guint	i;
	guint	j;
	
	if (a->rn == p->n) {
		data = g_new (CrankCplxFloat, a->rn * a->cn);
	
		for (i = 0; i < a->rn; i++) {
			guint ni = crank_permutation_get (p, i);
			
			for (j = 0; j < a->cn; j++)
				crank_mat_cplx_float_n_get (a, ni, j, data + (i * a->cn) + j);
		}
		
		crank_mat_cplx_float_n_init_arr_take (r, a->rn, a->cn, data);
	}
	
	else {
		g_warning ("MatFloatN: shuffle row: size mismatch: %ux%u, %u",
				a->rn, a->cn, p->n);
	}
}


/**
 * crank_mat_cplx_float_n_shuffle_col:
 * @a: A Matrix
 * @p: A Permutation to shuffle row.
 * @r: (out): A Matrix to store result.
 *
 * Shuffles row vectors by given permutation.
 */
void
crank_mat_cplx_float_n_shuffle_col (	CrankMatCplxFloatN*		a,
								CrankPermutation*	p,
								CrankMatCplxFloatN*		r	)
{
	CrankCplxFloat*	data;
	guint	i;
	guint	j;
	
	if (a->cn == p->n) {
		data = g_new (CrankCplxFloat, a->rn * a->cn);
	
		for (i = 0; i < a->rn; i++) {
			for (j = 0; j < a->cn; j++) {
				crank_mat_cplx_float_n_get (a, i, crank_permutation_get (p, j), data + (i * a->cn) + j);
			}
		}
		
		crank_mat_cplx_float_n_init_arr_take (r, a->rn, a->cn, data);
	}
	
	else {
		g_warning ("MatFloatN: shuffle row: size mismatch: %ux%u, %u",
				a->rn, a->cn, p->n);
	}
}


//////// Supplement Operations /////////////////////////////////////////////////

/**
 * crank_mat_cplx_float_n_upper_tri_invserse:
 * @a: A Matrix
 * @r: (out): A Matrix.
 *
 * Calculates inverse of upper triangular components.
 *
 * This is used to calculating inverse with decompositions.
 */
void
crank_mat_cplx_float_n_upper_tri_invserse (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	r	)
{
	guint	i;
	guint	j;
	guint	k;
	
	static CrankCplxFloat	ZERO = {0.0f, 0.0f};

	CRANK_MAT_WARN_IF_NON_SQUARE ("MatCplxFloatN", "upper-triangular-inverse", a);
	
	crank_mat_cplx_float_n_init_fill (r, a->rn, a->rn, &ZERO);
	
	
	// Initialize diagonal components.
	for (i = 0; i < a->rn; i++) {
		CrankCplxFloat	dcomp;
		crank_mat_cplx_float_n_get (a, i, i, &dcomp);
		
		crank_cplx_float_inverse_self (&dcomp);
		
		crank_mat_cplx_float_n_set (r, i, i, &dcomp);
	}
	
	for (i = 1; i < a->rn; i++) {
		for (j = 0; j < a->rn - i; j++) {
		
			CrankCplxFloat	sum = {0.0f, 0.0f};
			CrankCplxFloat	div;
			
			for (k = 1; k <= i; k++) {
				CrankCplxFloat	acomp;
				CrankCplxFloat	rcomp;
				CrankCplxFloat	addment;
				
				crank_mat_cplx_float_n_get (a, j, j + k, &acomp);
				crank_mat_cplx_float_n_get (r, j + k, j + i, &rcomp);
				
				crank_cplx_float_mul (&acomp, &rcomp, &addment);
				crank_cplx_float_add_self (&sum, &addment);
			}
			
			crank_mat_cplx_float_n_get (a, j, j, &div);
			
			crank_cplx_float_div_self (&sum, &div);
			crank_cplx_float_neg_self (&sum);
			
			crank_mat_cplx_float_n_set (r, j, j + i, &sum);
		}
	}
}


/**
 * crank_mat_cplx_float_n_lower_tri_invserse:
 * @a: A Matrix
 * @r: (out): A Matrix.
 *
 * Calculates inverse of lower triangular components.
 *
 * This is used to calculating inverse with decompositions.
 */
void
crank_mat_cplx_float_n_lower_tri_invserse (	CrankMatCplxFloatN*	a,
											CrankMatCplxFloatN*	r	)
{
	guint	i;
	guint	j;
	guint	k;
	
	static CrankCplxFloat ZERO = {0, 0};

	CRANK_MAT_WARN_IF_NON_SQUARE ("MatCplxFloatN", "lower-triangular-inverse", a);
	
	crank_mat_cplx_float_n_init_fill (r, a->rn, a->rn, &ZERO);
	
	
	// Initialize diagonal components.
	for (i = 0; i < a->rn; i++) {
		CrankCplxFloat	dcomp;
		crank_mat_cplx_float_n_get (a, i, i, &dcomp);
		
		crank_cplx_float_inverse_self (&dcomp);
		
		crank_mat_cplx_float_n_set (r, i, i, &dcomp);
	}
	
	for (i = 1; i < a->rn; i++) {
		for (j = 0; j < a->rn - i; j++) {
			CrankCplxFloat	sum = {0.0f, 0.0f};
			CrankCplxFloat	div;
			for (k = 1; k <= i; k++) {
				CrankCplxFloat	acomp;
				CrankCplxFloat	rcomp;
				CrankCplxFloat	addment;
				
				crank_mat_cplx_float_n_get (a, j + k, j, &acomp);
				crank_mat_cplx_float_n_get (r, j + i, j + k, &rcomp);
				
				crank_cplx_float_mul (&acomp, &rcomp, &addment);
				crank_cplx_float_add_self (&sum, &addment);
			}
			crank_mat_cplx_float_n_get (a, j, j, &div);
			
			crank_cplx_float_div_self (&sum, &div);
			crank_cplx_float_neg_self (&sum);
			
			crank_mat_cplx_float_n_set (r, j + i, j, &sum);
		}
	}
}


/**
 * crank_mat_cplx_float_n_diag_invserse:
 * @a: A Matrix
 * @r: (out): A Matrix.
 *
 * Calculates inverse of diagonal components.
 *
 * This is used to calculating inverse with decompositions.
 */
void
crank_mat_cplx_float_n_diag_invserse (	CrankMatCplxFloatN*	a,
										CrankMatCplxFloatN*	r	)
{
	guint	i;
	
	static CrankCplxFloat ZERO = {0, 0};

	CRANK_MAT_WARN_IF_NON_SQUARE ("MatCplxFloatN", "diag-inverse", a);
	
	crank_mat_cplx_float_n_init_fill (r, a->rn, a->rn, &ZERO);
	
	// Initialize diagonal components.
	for (i = 0; i < a->rn; i++) {
		CrankCplxFloat	dcomp;
		crank_mat_cplx_float_n_get (a, i, i, &dcomp);
		
		crank_cplx_float_inverse_self (&dcomp);
		
		crank_mat_cplx_float_n_set (r, i, i, &dcomp);
	}
}