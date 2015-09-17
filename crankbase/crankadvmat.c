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

#include <math.h>

#include <glib.h>
#include <glib-object.h>

#include "crankpermutation.h"
#include "crankveccommon.h"
#include "crankvecbool.h"
#include "crankvecfloat.h"
#include "crankveccplxfloat.h"
#include "crankmatfloat.h"
#include "crankmatcplxfloat.h"
#include "crankadvmat.h"

/**
 * SECTION: crankadvmat
 * @title: Advanced Matrix Operations.
 * @short_description: Advanced Operations to ease other matrix operations.
 * @stability: unstable
 * @include: crankbase.h
 *
 * Sometimes, Matrices are used to build up linear model. Crank System provides
 * advanced operations on matrices for convenience.
 *
 * # Decomposition
 *
 * Sometimes basic operations, like determinent, takes so long time if done
 * just by their definition.
 *
 * But when decomposition come into play, some operation can be done quickly.
 *
 * For example, when LU decomposition is found, determinent can be obtained by
 * multipling diagonal components of each factors, and it tooks
 * O(n<superscript>3</superscript>).
 * * Getting LU decomposition takes O(n<superscript>3</superscript>) times.
 * * And getting product of diagonal components takes O(n) times.
 * This is much faster than O(n!) times.
 * 
 * <table><title>Decompositions</title>
 *   <tgroup cols="2" align="left" colsep="1" rowsep="0">
 *     <thead>
 *       <row>
 *         <entry>Name and description</entry>
 *         <entry>Factors</entry>
 *       </row>
 *     </thead>
 *     <tbody>
 *       <row>
 *         <entry morerows="1">
 *           LU Decomposition
 *           <para>A = L U </para>
 *           <para>A is non-singular</para>
 *           <para>Crank System uses Crout's Method</para></entry>
 *         <entry>L
 *           <para>Lower triangular</para></entry>
 *       </row>
 *
 *       <row>
 *         <entry>U
 *           <para>Upper triangular</para>
 *           <para>All diagonal components are 1</para></entry>
 *       </row>
 
 *       <row>
 *         <entry>
 *           Cholesky Decomposition
 *           <para>A = L L<superscript>*</superscript> </para>
 *           <para>A is hermitian</para>
 *           <para>A is positive/semi-positive definite</para> </entry>
 *         <entry>L
 *           <para>Lower triangular</para></entry>
 *       </row>
 
 *       <row>
 *         <entry morerows="1">
 *           LDLT Decomposition
 *           <para>A = L D L<superscript>*</superscript> </para>
 *           <para>A is hermitian</para>
 *           <para>A is positive/semi-positive definite</para>
 *           <para>Avoids <function>sqrt</function>()</para></entry>
 *         <entry>L
 *           <para>Lower triangular</para></entry>
 *       </row>
 *       <row>
 *         <entry>D
 *           <para>Diagonal Matrix</para>
 *           <para>Crank System returns diagonal vector instad of matrix.</para></entry>
 *       </row>
 *
 *       <row>
 *         <entry morerows="1">
 *           QR Decomposition
 *           <para>A = Q R </para>
 *           <para>Crank Ststem provides 3 method to perform.
 *             <itemizedlist>
 *               <listitem>Gram Schmidt</listitem>
 *               <listitem>Householder</listitem>
 *               <listitem>Givens</listitem>
 *             </itemizedlist></para>
 *           <para>Crank System does not support rectangular matrices</para></entry>
 *         <entry>Q
 *           <para>Orthogonal/Unitary matrix</para></entry>
 *       </row>
 *       <row>
 *         <entry>R
 *           <para>Upper triangular matrix</para></entry>
 *       </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */



/**
 * crank_lu_mat_float_n:
 * @a: A Square matrix.
 * @l: (out): Lower triangular factor.
 * @u: (out): Upper triangular factor, whose all diagonal components are 1.
 *
 * Try to get LU decomposition of @a.
 *
 * This implementation uses Crout's Method. So all diagonal elements of @u will
 * be 1.
 *
 * Note that this does not perform pivoting. If pivoting is required, then use
 * crank_lu_p_mat_float_n().
 *
 * Time: O((@a->rn)<superscript>3</superscript>)
 *
 * Returns: Whether @a has LU Decomposition.
 */
gboolean
crank_lu_mat_float_n (	CrankMatFloatN*	a,
					  	CrankMatFloatN*	l,
					  	CrankMatFloatN*	u	)
{
	guint	i;
  	guint	j;
  	guint	k;

  	guint	n;
  	
  	g_return_val_if_fail (a != l, FALSE);
  	g_return_val_if_fail (a != u, FALSE);

	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatFloatN", "lu", a, FALSE);

  	n = a->rn;

  	if (n == 0) return TRUE;

  	if (n == 1) {
	  	if (a->data[0] != 0) {
			crank_mat_float_n_init (l, 1, 1, a->data[0]);
			crank_mat_float_n_init (u, 1, 1, 1.0f);
		  	return TRUE;
		}
		// If a == [[0]] then a is singular and cannot be defactorized.
		else return FALSE;
	}

	crank_mat_float_n_init_fill (l, n, n, 0);
	crank_mat_float_n_init_fill (u, n, n, 0);

  	for (i = 0; i < n; i++) {
	  	// l: column i
		for (j = i; j < n; j++) {
			gfloat	sum = 0;

			for (k = 0; k < i; k++) {
				sum +=	crank_mat_float_n_get (l, j, k) *
						crank_mat_float_n_get (u, k, i);
			}
			crank_mat_float_n_set (l, j, i,
					crank_mat_float_n_get (a, j, i) - sum);
		}


		// u: row i
		crank_mat_float_n_set (u, i, i, 1);
	  	for (j = i + 1; j < n; j++) {
	  		gfloat	sum = 0;
	  		gfloat	ln = crank_mat_float_n_get (l, i, i);

			if (ln == 0) {
			  	crank_mat_float_n_fini (l);
			  	crank_mat_float_n_fini (u);
			  	return FALSE;
			}

	  		for (k = 0; k < i; k++) {
				sum +=	crank_mat_float_n_get (l, i, k) *
		  				crank_mat_float_n_get (u, k, j);
			}
			crank_mat_float_n_set (u, i, j,
					(crank_mat_float_n_get (a, i, j) - sum)/ln);
		}
	}

  	return TRUE;
}

/**
 * crank_lu_p_mat_float_n:
 * @a: A Square matrix.
 * @p: (out): Pivoting result.
 * @l: (out): Lower triangular factor.
 * @u: (out): Upper triangular factor, whose all diagonal components are 1.
 *
 * Try to get LU decomposition of @a, with pivoting.
 *
 * Sometimes, some matrices are not able to be factorized, even not being
 * singular matrices. In this case, pivoting enables these matrices to be
 * decomposited.
 *
 * Generally, the decompositions are expressed with permutation matrices, but
 * in this function, the pivot result is returned as #CrankPermutation.
 *
 * For implementation detail, please see crank_lu_mat_float_n().
 *
 * Time: O((@a->rn)<superscript>3</superscript>)
 *
 * Returns: Whether @a has LU Decomposition.
 */
gboolean
crank_lu_p_mat_float_n (	CrankMatFloatN*		a,
							CrankPermutation*	p,
							CrankMatFloatN*		l,
							CrankMatFloatN*		u	)
{
	guint			i;
	guint			j;
	CrankMatFloatN	na;
  	
  	g_return_val_if_fail (a != l, FALSE);
  	g_return_val_if_fail (a != u, FALSE);
	
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatFloatN", "lu-pivot", a, FALSE);
	
	// Do pivoting.
	// Maximaze diagnoal component.
	crank_permutation_init_identity (p, a->rn);
	
	for (i = 0; i < a->rn; i++) {
		guint	max_index = i;
		gfloat	max =
				ABS (crank_mat_float_n_get (a,	crank_permutation_get (p, i), i));
				
		for (j = i + 1; j < a->rn; j++) {
			gfloat	cur =
				ABS (crank_mat_float_n_get (a, 	crank_permutation_get (p, j), i));
			
			if (max < cur) {
				max_index = j;
				max = cur;
			}
		}
	
		crank_permutation_swap (p, i, max_index);
	}
	
	// Do LU Decomposition.
	crank_mat_float_n_shuffle_row (a, p, &na);
	return crank_lu_mat_float_n (&na, l, u);
}

/**
 * crank_ch_mat_float_n:
 * @a: A Symmetric matrix.
 * @l: (out): A Lower triangular matrix.
 *
 * Performs cholesky decomposition on @a, which results in @l, which meets a
 * statement below.
 *
 * * @l.mul (@l.transpose()) == @a.
 *
 * Time: O((@a->rn)<superscript>3</superscript>)
 *
 * Returns: Whether cholesky decomposition performed on @a.
 */
gboolean
crank_ch_mat_float_n (CrankMatFloatN*	a,
					  CrankMatFloatN*	l	)
{
	guint	i;
	guint	j;
	guint	k;

	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("advmat", "ch-MatFloatN", a, FALSE);
	
	crank_mat_float_n_init_fill (l, a->rn, a->rn, 0.0f);
	
	// Proceed row by row.
	for (i = 0; i < a->rn; i++) {
		gfloat l_ij;
		
		// Gets l[i, j] = (a[i, j] - l[i,0]*l[j,0] - l[i,1]*l[j,1] ...) / l[j,j]
		
		for (j = 0; j < i; j++) {
			gfloat d;
		
			l_ij = crank_mat_float_n_get (a, i, j);
			for (k = 0; k < j; k++) {
				l_ij -=	crank_mat_float_n_get (l, i, k) *
						crank_mat_float_n_get (l, j, k);
			}
			l_ij /= crank_mat_float_n_get (l, j, j);
			crank_mat_float_n_set (l, i, j, l_ij);
		}
		
		
		// Gets l[i, i] == a[i, i] - l[i, 0]**2 - ....
		
		l_ij = crank_mat_float_n_get (a, i, i);
		for (k = 0; k < i; k++) {
			gfloat	e = crank_mat_float_n_get (l, i, k);
			l_ij -= e*e;
		}
		
		if (l_ij < 0.0f) {
			crank_mat_float_n_fini (l);
			return FALSE;
		}
		crank_mat_float_n_set (l, i, i, sqrtf (l_ij));
	}
	
	return TRUE;
}

/**
 * crank_ldl_mat_float_n:
 * @a: A Symmetric atrix.
 * @l: (out): A Lower triangular matrix.
 * @d: (out): A Diagonal components.
 *
 * Performs LDLT decomposition on @a, which results in @l, @d, which is
 *
 * * @l.mul (D.mul (@l.transpose())) == @a.
 *
 * where D is diagonal matrix whose diagonal is @d.
 *
 * This implementation is differ classical LDLT, by returning diagonal
 * vector rather than diagonal matrix.
 *
 * LDLT avoids performing sqrt on diagonal elements, while multiplication happens
 * more than Cholskey Decomposition.
 *
 * Time: O((@a->rn)<superscript>3</superscript>)
 *
 * Returns: Whether cholesky decomposition performed on @a.
 */
gboolean
crank_ldl_mat_float_n (CrankMatFloatN*	a,
					   CrankMatFloatN*	l,
					   CrankVecFloatN*	d	)
{
	guint	i;
	guint	j;
	guint	k;

	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("advmat", "ch-MatFloatN", a, FALSE);
	
	crank_mat_float_n_init_fill (l, a->rn, a->rn, 0.0f);
	crank_vec_float_n_init_fill (d, a->rn, 0.0f);
	
	// Proceed row by row.
	for (i = 0; i < a->rn; i++) {
		gfloat l_ij;
		
		// Gets l[i, j] = ( a[i, j]
		//                  - l[i,0] * l[j,0] * d[0]
		//                  - l[i,1] * l[j,1] * d[1] ...) / d[j]
		
		for (j = 0; j < i; j++) {
		
			l_ij = crank_mat_float_n_get (a, i, j);
			for (k = 0; k < j; k++) {
				l_ij -=	crank_mat_float_n_get (l, i, k) *
						crank_mat_float_n_get (l, j, k) *
						crank_vec_float_n_get (d, k);
			}
			l_ij /= crank_vec_float_n_get (d, j);
			crank_mat_float_n_set (l, i, j, l_ij);
		}
		
		
		// Gets d[i] == a[i, i] - l[i, 0]**2 * d[0] - ....
		
		l_ij = crank_mat_float_n_get (a, i, i);
		for (k = 0; k < i; k++) {
			gfloat	e = crank_mat_float_n_get (l, i, k);
			l_ij -= e*e * crank_vec_float_n_get (d, k);
		}
		
		if (l_ij < 0.0f) {
			crank_mat_float_n_fini (l);
			crank_vec_float_n_fini (d);
			return FALSE;
		}
		crank_vec_float_n_set (d, i, l_ij);
		crank_mat_float_n_set (l, i, i, 1.0f);
	}
	
	return TRUE;
}

/**
 * crank_gram_schmidt_mat_float_n:
 * @a: A Matrix.
 * @q: (out): A Resulting Orthogonal Matrix.
 * @r: (out): The upper triangular.
 *
 * Gets QR Decomposition by Gram Schmidt process.
 *
 * Time: O((@a->rn)<superscript>3</superscript>)
 *
 * Returns: %TRUE if @a has QR Decomposition.
 */
gboolean
crank_gram_schmidt_mat_float_n (	CrankMatFloatN*		a,
									CrankMatFloatN*		q,
									CrankMatFloatN*		r	)
{
	CrankVecFloatN*	e;
	
	guint	i;
	guint	j;
	guint	k;
	
	g_return_val_if_fail (a != q, FALSE);
	g_return_val_if_fail (a != r, FALSE);
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatFloatN", "gram-schmidt", a, FALSE);
	
	e = g_new (CrankVecFloatN, a->rn);
	crank_mat_float_n_init_fill (r, a->rn, a->rn, 0);
	
	for (i = 0; i < a->rn; i++) {
		CrankVecFloatN	ac;
		CrankVecFloatN	u;
		gfloat			umagn;
		
		// u = a.col[i]
		crank_mat_float_n_get_col (a, i, &ac);
		crank_vec_float_n_copy (&ac, &u);
	
		// u -= proj(a.col[i], e[0..(i-1)])
		// r = a.col[i] dot e
		for (j = 0; j < i; j++) {
			CrankVecFloatN	proj;
			gfloat			dot;
			dot = crank_vec_float_n_dot (e + j, &ac);
			
			crank_vec_float_n_muls (e + j, dot, &proj);
			
			crank_vec_float_n_sub_self (&u, &proj);
			crank_mat_float_n_set (r, j, i, dot);
		}
	
		// e[i] = u.unit
		umagn = crank_vec_float_n_get_magn (&u);
		crank_mat_float_n_set (r, i, i, umagn);
		crank_vec_float_n_divs (&u, umagn, e + i);
		crank_vec_float_n_fini (&u);
	}

	crank_mat_float_n_init_col_arr (q, a->rn, e);
	
	for (k = 0; k < a->rn; k++) crank_vec_float_n_fini (e + k);
	g_free (e);
	
	return TRUE;
}

/**
 * crank_qr_householder_mat_float_n:
 * @a: A Matrix.
 * @r: (out): A Lower triangular matrix.
 *
 * Performs QR Decomposition by householder method.
 
 * Time: O((@a->rn)<superscript>3</superscript>)
 *
 * Returns: %TRUE if @a has QR Decomposition.
 */
gboolean
crank_qr_householder_mat_float_n (	CrankMatFloatN*	a,
									CrankMatFloatN*	r	)
{
	guint			i;
	guint			j;
	guint			k;
	
	CrankMatFloatN	pa = {0};
	CrankMatFloatN	qi = {0};
	CrankMatFloatN	qpai = {0};
	CrankVecFloatN	an = {0};
	
	g_return_val_if_fail (a != r, FALSE);
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatFloatN", "gram-schmidt", a, FALSE);
	
	if (a->rn == 1) {
		crank_mat_float_n_init (r, 0, 0,
				crank_mat_float_n_get (a, 0, 0));
		return TRUE;
	}


	// Setup initial state.
	crank_mat_float_n_copy (a, &pa);
	crank_mat_float_n_init_fill (r, a->rn, a->rn, 0.0f);
	
	for (i = 0; i < a->rn - 1; i++) {
		// Initialize an
		crank_mat_float_n_get_col (&pa, 0, &an);

		crank_vec_float_n_set (&an, 0,
				crank_vec_float_n_get (&an, 0) -
				crank_vec_float_n_get_magn (&an));

		crank_vec_float_n_unit_self (&an);
		
		// Initialize qi			
		crank_mat_float_n_init_fill (&qi, a->rn - i, a->rn - i, 0.0f);
		
		for (j = 0; j < a->rn - i; j++) {
			for (k = 0; k < a->rn - i; k++) {
				crank_mat_float_n_set (&qi, j, k,
						- 2 *
						crank_vec_float_n_get (&an, j) *
						crank_vec_float_n_get (&an, k));
			}
			
			crank_mat_float_n_set (&qi, j, j,
					1 + crank_mat_float_n_get (&qi, j, j));
		}
		
		crank_mat_float_n_mul (&qi, &pa, &qpai);
		
		// Resulting row 0 of qpai is part of r
		// and rest part is next pa
		for (j = 0; j < a->rn - i; j++) {
			crank_mat_float_n_set (r, i, i + j,
					crank_mat_float_n_get (&qpai, 0, j));
		}
		// FIXME: Replace slicing by other actions.
		// Slicing requires allocation and copying.
		crank_mat_float_n_slice (&qpai, 1, 1, qpai.rn, qpai.cn, &pa);
	}
	// Fill last part of r
	crank_mat_float_n_set(r, (a->rn - 1), (a->rn - 1),
			crank_mat_float_n_get (&qpai, 1, 1));
	
	crank_mat_float_n_fini (&pa);
	crank_mat_float_n_fini (&qi);
	crank_mat_float_n_fini (&qpai);
	crank_vec_float_n_fini (&an);
	return TRUE;
}

/**
 * crank_qr_givens_mat_float_n:
 * @a: A Matrix.
 * @r: (out): A Lower triangular matrix.
 *
 * Performs QR Decomposition by Givens rotation.
 
 * Time: O((@a->rn)<superscript>3</superscript>)
 *
 * Returns: %TRUE if @a has QR Decomposition.
 */
gboolean
crank_qr_givens_mat_float_n (	CrankMatFloatN*	a,
								CrankMatFloatN*	r	)
{
	guint	i;
	guint	j;
	guint	k;
	
	CrankMatFloatN	pa = {0};
	
	
	g_return_val_if_fail (a != r, FALSE);
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatFloatN", "qr-givens", a, FALSE);
	
	if (a->rn == 1) {
		crank_mat_float_n_init (r, 1, 1,
				crank_mat_float_n_get (a, 0, 0));
		return TRUE;
	}
	
	crank_mat_float_n_init_fill (r, a->rn, a->rn, 0.0f);
	crank_mat_float_n_copy (a, &pa);
	
	for (i = 0; i < a->rn - 1; i++) {
		for (j = a->rn - 1; i < j; j--) {
			CrankVecFloat2 x = {
					crank_mat_float_n_get (&pa, j - 1, i),
					crank_mat_float_n_get (&pa, j, i)};
			
			if ((x.x == 0) && (x.y == 0)) {
				crank_mat_float_n_fini (&pa);
				crank_mat_float_n_fini (r);
				
				return FALSE;
			}
			
			crank_vec_float2_unit_self (&x);
			
			// Multiplies Givens rotation matrix.
			//
			// We don't build up Full givens rotation matrix,
			// instead we apply this with sin, cos value.
			for (k = i; k < a->rn; k++) {
				gfloat*	paa = pa.data + (a->cn * (j - 1)) + k;
				gfloat*	pab = paa + (a->cn);
							
				gfloat	e = *paa;
				gfloat	f = *pab;
				
				*paa = 	e * x.x + f * x.y;
				*pab = - e * x.y + f * x.x;
			}
		}
		
		for (j = i; j < a->rn; j++) {
			crank_mat_float_n_set (r, i, j,
				crank_mat_float_n_get (&pa, i, j));
		}
	}
	
	crank_mat_float_n_set (r, a->rn - 1, a->rn - 1, pa.data[(a->rn * a->rn) - 1]);
	
	crank_mat_float_n_fini (&pa);
	
	return TRUE;
}

/**
 * crank_eval_power_mat_float_n:
 * @a: A Matrix.
 * @b: (nullable): A Seed vector.
 * @evec: (optional) (out): Associated eigenvector.
 *
 * Gets a eigenvalue of given matrix, by power method.
 *
 * The returned value is most dominent eigenvalue whose associated eigenvector
 * is not orthogonal to seed vector.
 *
 * If it failed to convergent, it returns NaN.
 *
 * If @b is %NULL, this uses first column as seed.
 *
 * Returns: Most dominent eigenvalue whose eigenvector is not orthogonal to @b.
 */
gfloat
crank_eval_power_mat_float_n (	CrankMatFloatN*	a,
								CrankVecFloatN*	b,
								CrankVecFloatN*	evec	)
{
	CrankVecFloatN	bs;
	CrankVecFloatN	bsmv;
	gfloat			magn = INFINITY;
	
	gfloat			dsp = INFINITY;
	gfloat			ds = INFINITY;
	
	gfloat			eval = 0.0f;
	
	CrankVecFloatN	diff;
	
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatFloatN", "power-method", a, 0.0f);
	
	if (b != NULL)
		crank_vec_float_n_copy (b, &bs);
	else
		crank_mat_float_n_get_col (a, 0, &bs);
	
	
	
	do {
		dsp = ds;
		crank_vec_float_n_copy (&bs, &diff);
		
		// Iterate: b = (a * b) / (a * b).magn
		// bsmv = a * bs
		// bs = bsmv unit.
		
		crank_mat_float_n_mulv (a, &bs, &bsmv);
		crank_vec_float_n_unit (&bsmv, &bs);
		crank_vec_float_n_fini (&bsmv);
		
		//Gets a eigen value.
		// lambda = b * a * b / (b.magn)
		//
		// As b is normalized, b.magn == 1
		//
		// bsmv = a * bs
		// eval = bs dot bsmv
		
		crank_mat_float_n_mulv (a, &bs, &bsmv);
		eval = crank_vec_float_n_dot (&bs, &bsmv);
		
		crank_vec_float_n_fini (&bsmv);
		
		crank_vec_float_n_sub_self (&diff, &bs);
		
		ds = crank_vec_float_n_get_magn_sq (&diff);
		
		if (dsp < ds) {
			crank_vec_float_n_fini (&bs);
			return NAN;
		}
	}
	while (0.0000001f < (dsp - ds));
	
	if (ds > 0.0000001f) {
		if (evec != NULL) crank_vec_float_n_init_arr_take (evec, 0, NULL);
		crank_vec_float_n_fini (&bs);
		return NAN;
	}
	else {
		guint i;
	
		if (evec != NULL) crank_vec_float_n_copy (&bs, evec);

		crank_vec_float_n_fini (&bs);
		crank_vec_float_n_fini (&bsmv);
		
		return eval;
	}
}

/**
 * crank_eval_qr_mat_float_n:
 * @a: A Matrix.
 * @evals: (out): A Vector contains eigenvalues.
 *
 * Eigenvalues are calculated by QR Algorithm; If QR Decompisition is not
 * possible, an 0-sized vector is returned.
 *
 * If the matrix has complex eigenvalues, this function will fill NAN in that
 * place.
 */
void
crank_eval_qr_mat_float_n (	CrankMatFloatN*	a,
							CrankVecFloatN*	evals	)
{
	CrankMatFloatN	ai;
	CrankMatFloatN	qi;
	CrankMatFloatN	ri;
	
	CrankVecFloatN	offdiag;
	CrankVecBoolN	nonconv;
	gboolean		cont;
	
	guint	i;
	guint	j;
	
	CRANK_MAT_WARN_IF_NON_SQUARE ("Advmat-MatFloatN", "qr-iteration", a);
	
	crank_vec_float_n_init_fill (&offdiag, a->rn - 1, INFINITY);
	crank_vec_bool_n_init_fill (&nonconv, a->rn - 1, FALSE);
	
	cont = TRUE;
	
	crank_mat_float_n_copy (a, &ai);
	
	while (cont) {
		if (! crank_gram_schmidt_mat_float_n (&ai, &qi, &ri)) {
			crank_mat_float_n_fini (&ai);
			crank_vec_float_n_fini (evals);
			return;
		}
		
		crank_mat_float_n_fini (&ai);
		crank_mat_float_n_mul (&ri, &qi, &ai);
		
		cont = FALSE;
		for (i = 0; i < a->rn; i++) { 
			for (j = 0; j + 1 < i; j++) {
				gfloat e = crank_mat_float_n_get (&ai, i, j);
				// Checks for elements are smaller than reasonably small value.
				//TODO: Make a way to adjust this value.
				
				if (e < -0.0001f || 0.0001f < e) {
					cont = TRUE;
					break;
				}
			}
			if (cont) break;
		}
		
		if (! cont) {
			for (i = 0; i < a->rn - 1; i++) {
				if (! crank_vec_bool_n_get (&nonconv, i)) {
				
					gfloat e = ABS (crank_mat_float_n_get (&ai, i+1, i));

					if (crank_vec_float_n_get (&offdiag, i) < e)
						crank_vec_bool_n_set (&nonconv, i, TRUE);
					
					else {
						crank_vec_float_n_set (&offdiag, i, e);
						if (0.0001f < e) {
							cont = TRUE;
							break;
						}
					}
				}
			}
		}
	}
	
	crank_mat_float_n_get_diag (&ai, evals);
	
	for (i = 0; i < a->rn - 1; i++) {
		if (crank_vec_bool_n_get (&nonconv, i)) {
			crank_vec_float_n_set (evals, i, NAN);
			crank_vec_float_n_set (evals, i + 1, NAN);
			i++;
		}
	}
	
	crank_vec_bool_n_fini (&nonconv);
	crank_mat_float_n_fini (&ai);
	crank_mat_float_n_fini (&qi);
	crank_mat_float_n_fini (&ri);
}


/**
 * crank_lu_mat_cplx_float_n:
 * @a: A Matrix.
 * @l: (out): Lower triangular factor.
 * @u: (out): Upper triangular factor.
 *
 * Try to get LU decomposition of @a.
 *
 * This implementation uses Crout's Method. So all diagonal elements of @u will
 * be 1.
 *
 * Note that this does not perform pivoting. If pivoting is required, then use
 * crank_lu_p_mat_cplx_float_n().
 *
 * Returns: Whether @a has LU Decomposition.
 */
gboolean
crank_lu_mat_cplx_float_n (	CrankMatCplxFloatN*	a,
						  	CrankMatCplxFloatN*	l,
						  	CrankMatCplxFloatN*	u	)
{
	guint	i;
  	guint	j;
  	guint	k;

  	guint	n;
  	
  	static CrankCplxFloat	ZERO = {0, 0};
  	static CrankCplxFloat	ONE = {1, 0};
  	
  	g_return_val_if_fail (a != l, FALSE);
  	g_return_val_if_fail (a != u, FALSE);

	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatCplxFloatN", "lu", a, FALSE);

  	n = a->rn;

  	if (n == 0) return TRUE;

  	if (n == 1) {
	  	if (! crank_cplx_float_is_zero (a->data)) {
			crank_mat_cplx_float_n_init (l, 1, 1, a->data + 0);
			crank_mat_cplx_float_n_init_uc (u, 1, 1, 1.0f, 0.0f);
		  	return TRUE;
		}
		// If a == [[0]] then a is singular and cannot be defactorized.
		else return FALSE;
	}

	crank_mat_cplx_float_n_init_fill (l, n, n, &ZERO);
	crank_mat_cplx_float_n_init_fill (u, n, n, &ZERO);
	
  	for (i = 0; i < n; i++) {
	  	// l: column i
		for (j = i; j < n; j++) {
			CrankCplxFloat	sum = {0.0f, 0.0f};
			CrankCplxFloat	lpart;
			CrankCplxFloat	upart;
			CrankCplxFloat	lupart;
			CrankCplxFloat	apart;
			
			for (k = 0; k < i; k++) {
				crank_mat_cplx_float_n_get (l, j, k, &lpart);
				crank_mat_cplx_float_n_get (u, k, i, &upart);
				
				crank_cplx_float_mul (&lpart, &upart, &lupart);
				crank_cplx_float_add_self (&sum, &lupart);
			}
			
			crank_mat_cplx_float_n_get (a, j, i, &apart);
			crank_cplx_float_sub_self (&apart, &sum);
			crank_mat_cplx_float_n_set (l, j, i, &apart);
		}


		// u: row i
		crank_mat_cplx_float_n_set (u, i, i, &ONE);
	  	for (j = i + 1; j < n; j++) {
			CrankCplxFloat	sum = {0.0f, 0.0f};
			CrankCplxFloat	lpart;
			CrankCplxFloat	upart;
			CrankCplxFloat	lupart;
			CrankCplxFloat	apart;
			
			CrankCplxFloat	ldpart;

	  		crank_mat_cplx_float_n_get (l, i, i, &ldpart);

			if (crank_cplx_float_is_zero (&ldpart)) {
			  	crank_mat_cplx_float_n_fini (l);
			  	crank_mat_cplx_float_n_fini (u);
			  	return FALSE;
			}

	  		for (k = 0; k < i; k++) {
	  			crank_mat_cplx_float_n_get (l, i, k, &lpart);
	  			crank_mat_cplx_float_n_get (u, k, j, &upart);	
	  			crank_cplx_float_mul (&lpart, &upart, &lupart);
				crank_cplx_float_add_self (&sum, &lupart);
			}
			
			crank_mat_cplx_float_n_get (a, i, j, &apart);
			crank_cplx_float_sub_self (&apart, &sum);
			crank_cplx_float_div_self (&apart, &ldpart);
			crank_mat_cplx_float_n_set (u, i, j, &apart);
		}
	}

  	return TRUE;
}


/**
 * crank_lu_p_mat_cplx_float_n:
 * @a: A Matrix.
 * @p: (out): Pivoting result.
 * @l: (out): Lower triangular factor.
 * @u: (out): Upper triangular factor.
 *
 * Try to get LU decomposition of @a, with pivoting.
 *
 * Sometimes, some matrices are not able to be factorized, even not being
 * singular matrices. In this case, pivoting enables these matrices to be
 * decomposited.
 *
 * Generally, the decompositions are expressed with permutation matrices, but
 * in this function, the pivot result is returned as #CrankPermutation.
 *
 * For implementation detail, please see crank_lu_mat_float_n().
 *
 * Returns: Whether @a has LU Decomposition.
 */
gboolean
crank_lu_p_mat_cplx_float_n (	CrankMatCplxFloatN*		a,
								CrankPermutation*		p,
								CrankMatCplxFloatN*		l,
								CrankMatCplxFloatN*		u	)
{
	guint				i;
	guint				j;
	CrankMatCplxFloatN	na;
  	
  	g_return_val_if_fail (a != l, FALSE);
  	g_return_val_if_fail (a != u, FALSE);
	
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatCplxFloatN", "lu-pivot", a, FALSE);
	
	// Do pivoting.
	// Maximaze diagnoal component.
	crank_permutation_init_identity (p, a->rn);
	
	for (i = 0; i < a->rn; i++) {
		CrankCplxFloat	max;
		gfloat			max_normsq;
		guint			max_index = i;

		crank_mat_cplx_float_n_get (a,	crank_permutation_get (p, i), i, &max);
		max_normsq = crank_cplx_float_get_norm_sq (&max);
				
		for (j = i + 1; j < a->rn; j++) {
			CrankCplxFloat	cur;
			gfloat			cur_normsq;
			
			crank_mat_cplx_float_n_get (a, 	crank_permutation_get (p, j), i, &cur);
			cur_normsq = crank_cplx_float_get_norm_sq (&cur);
			if (max_normsq < cur_normsq) {
				max_index = j;
				max_normsq = cur_normsq;
			}
		}
	
		crank_permutation_swap (p, i, max_index);
	}
	
	// Do LU Decomposition.
	crank_mat_cplx_float_n_shuffle_row (a, p, &na);
	return crank_lu_mat_cplx_float_n (&na, l, u);
}

/**
 * crank_ch_mat_cplx_float_n:
 * @a: A Matrix.
 * @l: (out): A Lower triangular matrix.
 *
 * Performs cholesky decomposition on @a, which results in @l, which
 *
 * * @l.mul (@l.star()) == @a.
 *
 * Returns: Whether cholesky decomposition performed on @a.
 */
gboolean
crank_ch_mat_cplx_float_n (	CrankMatCplxFloatN*	a,
					  		CrankMatCplxFloatN*	l	)
{
	guint	i;
	guint	j;
	guint	k;

	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("advmat", "ch-MatCplxFloatN", a, FALSE);
	
	crank_mat_cplx_float_n_init_fill_uc (l, a->rn, a->rn, 0.0f, 0.0f);
	
	// Proceed row by row.
	for (i = 0; i < a->rn; i++) {
		CrankCplxFloat l_ij;
		
		// Gets l[i, j] = (a[i, j] - l[i,0]*l[j,0] - l[i,1]*l[j,1] ...) / l[j,j]
		
		for (j = 0; j < i; j++) {
			gfloat d;
		
			crank_mat_cplx_float_n_get (a, i, j, &l_ij);
			for (k = 0; k < j; k++) {
				CrankCplxFloat	ik_jk;
				
				crank_cplx_float_mul_conj (
						crank_mat_cplx_float_n_peek (l, i, k),
						crank_mat_cplx_float_n_peek (l, j, k),
						&ik_jk									);
				
				crank_cplx_float_sub_self (&l_ij, &ik_jk);
			}
			crank_cplx_float_div_self (&l_ij, crank_mat_cplx_float_n_peek (l, j, j));
			crank_mat_cplx_float_n_set (l, i, j, &l_ij);
		}
		
		
		// Gets l[i, i] == a[i, i] - l[i, 0]**2 - ....
		
		crank_mat_cplx_float_n_get (a, i, i, &l_ij);
		for (k = 0; k < i; k++) {
			CrankCplxFloat*	ep = crank_mat_cplx_float_n_peek (l, i, k);
			gfloat	esq = crank_cplx_float_get_norm_sq (ep);
			
			crank_cplx_float_subr_self (&l_ij, esq);
		}
		
		// Diagonal component should be real positive.
		// as complex multiplication of its conjugate is always positive real.
		//
		// In other word, @l_ij is negative or imaginary, there is no cholesky
		// decomposition.
		if (l_ij.real < 0) {
			crank_mat_cplx_float_n_fini (l);
			return FALSE;
		}
		
		crank_cplx_float_sqrt_self (&l_ij);
		crank_mat_cplx_float_n_set (l, i, i, &l_ij);
	}
	
	return TRUE;
}


/**
 * crank_gram_schmidt_mat_cplx_float_n:
 * @a: A Matrix.
 * @q: (out): A Resulting Orthogonal Matrix.
 * @r: (out): The upper triangular.
 *
 * Gets QR Decomposition by Gram Schmidt process.
 *
 * Returns: %TRUE if @a has QR Decomposition.
 */
gboolean
crank_gram_schmidt_mat_cplx_float_n (	CrankMatCplxFloatN*		a,
										CrankMatCplxFloatN*		q,
										CrankMatCplxFloatN*		r	)
{
	CrankVecCplxFloatN*		e;
	
	static CrankCplxFloat	ZERO = {0.0f, 0.0f};
	static CrankCplxFloat	ONE = {1.0f, 0.0f};
	
	guint	i;
	guint	j;
	guint	k;
	
	g_return_val_if_fail (a != q, FALSE);
	g_return_val_if_fail (a != r, FALSE);
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatCplxFloatN", "gram-schmidt", a, FALSE);
	
	e = g_new (CrankVecCplxFloatN, a->rn);
	crank_mat_cplx_float_n_init_fill (r, a->rn, a->rn, &ZERO);
	
	for (i = 0; i < a->rn; i++) {
		CrankVecCplxFloatN	ac;
		CrankVecCplxFloatN	u;
		CrankCplxFloat		ii;
		
		// u = a.col[i]
		crank_mat_cplx_float_n_get_col (a, i, &ac);
		crank_vec_cplx_float_n_copy (&ac, &u);
	
		// u -= proj(a.col[i], e[0..(i-1)])
		// r = a.col[i] dot e
		for (j = 0; j < i; j++) {
			CrankVecCplxFloatN	proj;
			CrankCplxFloat		dot;
			crank_vec_cplx_float_n_dot (&ac, e + j, &dot);
			
			crank_vec_cplx_float_n_muls (e + j, &dot, &proj);
			
			crank_vec_cplx_float_n_sub_self (&u, &proj);
			crank_mat_cplx_float_n_set (r, j, i, &dot);
		}
	
		// e[i] = u.unit
		
		crank_cplx_float_init (&ii, crank_vec_cplx_float_n_get_magn (&u), 0);
		crank_mat_cplx_float_n_set (r, i, i, &ii);
		crank_vec_cplx_float_n_unit (&u, e + i);
		crank_vec_cplx_float_n_fini (&u);
	}

	crank_mat_cplx_float_n_init_col_arr (q, a->rn, e);

	for (i = 0; i < a->rn; i++) {
		crank_vec_cplx_float_n_fini (e + i);
	}
	g_free (e);
	
	return TRUE;
}

/**
 * crank_qr_householder_mat_cplx_float_n:
 * @a: A Matrix.
 * @r: (out): A Lower triangular matrix.
 *
 * Performs QR Decomposition by householder method.
 *
 * Returns: %TRUE if @a has QR Decomposition.
 */
gboolean
crank_qr_householder_mat_cplx_float_n (	CrankMatCplxFloatN*	a,
										CrankMatCplxFloatN*	r	)
{
	guint			i;
	guint			j;
	guint			k;
	
	CrankMatCplxFloatN	pa = {0};
	CrankMatCplxFloatN	qi = {0};
	CrankMatCplxFloatN	qpai = {0};
	CrankCplxFloat		ancomp;
	
	static CrankCplxFloat	ZERO = {0.0f, 0.0f};
	static CrankCplxFloat	ONE = {1.0f, 0.0f};
	
	
	g_return_val_if_fail (a != r, FALSE);
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatCplxFloatN", "qr-householder", a, FALSE);
	
	if (a->rn == 1) {
		crank_mat_cplx_float_n_init (r, 1, 1, &ZERO);
		return TRUE;
	}


	// Setup initial state.
	crank_mat_cplx_float_n_copy (a, &pa);
	crank_mat_cplx_float_n_init_fill (r, a->rn, a->rn, &ZERO);
	
	for (i = 0; i < a->rn - 1; i++) {
		CrankVecCplxFloatN	an;
		CrankVecCplxFloatN	u;
		CrankCplxFloat		factor;
		CrankCplxFloat		factor_a;
		CrankCplxFloat		factor_b;
	
		// Initialize an
		crank_mat_cplx_float_n_get_col (&pa, 0, &an);
		crank_vec_cplx_float_n_copy (&an, &u);

		crank_vec_cplx_float_n_get (&an, 0, &ancomp);
		crank_cplx_float_subr_self (&ancomp, crank_vec_cplx_float_n_get_magn (&an));
		crank_vec_cplx_float_n_set (&u, 0, &ancomp);

		crank_vec_cplx_float_n_unit_self (&u);
		
		// Initialize qi			
		crank_mat_cplx_float_n_init_fill (&qi, a->rn - i, a->rn - i, &ZERO);
				
		crank_vec_cplx_float_n_dot (&u, &an, &factor_a);
		crank_vec_cplx_float_n_dot (&an, &u, &factor_b);
		
		crank_cplx_float_div (&factor_a, &factor_b, &factor);
		crank_cplx_float_addr_self (&factor, 1.0f);
		crank_cplx_float_neg_self (&factor);
		
		
		for (j = 0; j < a->rn - i; j++) {
			for (k = 0; k < a->rn - i; k++) {
				CrankCplxFloat	ujcomp;
				CrankCplxFloat	ukcomp;
				CrankCplxFloat	qicomp;
				crank_vec_cplx_float_n_get (&u, j, &ujcomp);
				crank_vec_cplx_float_n_get (&u, k, &ukcomp);
				crank_cplx_float_mul_conj (&ujcomp, &ukcomp, &qicomp);
				crank_cplx_float_mul_self (&qicomp, &factor);
				
				crank_mat_cplx_float_n_set (&qi, j, k, &qicomp);
			}
			
			CrankCplxFloat	qjcomp;
			
			crank_mat_cplx_float_n_get (&qi, j, j, &qjcomp);
			crank_cplx_float_addr_self (&qjcomp, 1.0f);
			crank_mat_cplx_float_n_set (&qi, j, j, &qjcomp);
		}
		
		crank_mat_cplx_float_n_mul (&qi, &pa, &qpai);
		
		// Resulting row 0 of qpai is part of r
		// and rest part is next pa
		for (j = 0; j < a->rn - i; j++) {
			crank_mat_cplx_float_n_set (r, i, i + j,
					crank_mat_cplx_float_n_peek (&qpai, 0, j));
		}
		crank_mat_cplx_float_n_slice (&qpai, 1, 1, qpai.rn, qpai.cn, &pa);
		crank_vec_cplx_float_n_fini (&an);
		crank_vec_cplx_float_n_fini (&u);
	}
	// Fill last part of r
	crank_mat_cplx_float_n_get (&qpai, 1, 1, &ancomp);
	crank_cplx_float_init (&ancomp, crank_cplx_float_get_norm (&ancomp), 0.0f);
	
	crank_mat_cplx_float_n_set(r, (a->rn - 1), (a->rn - 1), &ancomp);
	
	crank_mat_cplx_float_n_fini (&pa);
	crank_mat_cplx_float_n_fini (&qi);
	crank_mat_cplx_float_n_fini (&qpai);
	return TRUE;
}



/**
 * crank_qr_givens_mat_cplx_float_n:
 * @a: A Matrix.
 * @r: (out): A Lower triangular matrix.
 *
 * Performs QR Decomposition by Givens rotation.
 *
 * Returns: %TRUE if @a has QR Decomposition.
 */
gboolean
crank_qr_givens_mat_cplx_float_n (	CrankMatCplxFloatN*	a,
									CrankMatCplxFloatN*	r	)
{
	guint	i;
	guint	j;
	guint	k;
	
	CrankMatCplxFloatN	pa;
	CrankCplxFloat		last;
	
	
	static CrankCplxFloat	ZERO = {0.0f, 0.0f};
	static CrankCplxFloat	ONE = {1.0f, 0.0f};
	
	
	g_return_val_if_fail (a != r, FALSE);
	CRANK_MAT_WARN_IF_NON_SQUARE_RET ("Advmat-MatCplxFloatN", "qr-givens", a, FALSE);
	
	if (a->rn == 1) {
		crank_mat_cplx_float_n_init (r, 1, 1,
				crank_mat_cplx_float_n_peek (a, 0, 0));
		return TRUE;
	}
	
	crank_mat_cplx_float_n_init_fill (r, a->rn, a->rn, &ZERO);
	crank_mat_cplx_float_n_copy (a, &pa);
	
	for (i = 0; i < a->rn - 1; i++) {
		guint	n = a->rn - i;
		
		for (j = n - 1; 0 < j; j--) {
			CrankCplxFloat 	x;
			CrankCplxFloat 	y;
			
			gfloat			magn;
			
			crank_mat_cplx_float_n_get (&pa, j - 1, 0, &x);
			crank_mat_cplx_float_n_get (&pa, j, 0, &y);
			
			if (crank_cplx_float_is_zero (&x) || crank_cplx_float_is_zero (&y)) {
				crank_mat_cplx_float_n_fini (&pa);
				crank_mat_cplx_float_n_fini (r);
				
				return FALSE;
			}
			
			magn = sqrtf ( 	crank_cplx_float_get_norm_sq (&x) +
							crank_cplx_float_get_norm_sq (&y) );

			crank_cplx_float_divr_self (&x, magn);
			crank_cplx_float_divr_self (&y, magn);
			
			// Multiplies Givens rotation matrix.
			//
			// We don't build up Full givens rotation matrix,
			// instead we apply this with sin, cos value.
			for (k = 0; k < n; k++) {
				CrankCplxFloat	e;
				CrankCplxFloat	f;
				
				CrankCplxFloat	ea;
				CrankCplxFloat	fa;
				CrankCplxFloat	addment;
			
				crank_mat_cplx_float_n_get (&pa, j - 1, k, &e);
				crank_mat_cplx_float_n_get (&pa, j, k, &f);
				
				crank_cplx_float_mul_conj (&e, &x, &ea);
				crank_cplx_float_mul_conj (&f, &y, &fa);
				crank_cplx_float_add (&ea, &fa, &addment);
				
				crank_mat_cplx_float_n_set (&pa, j-1, k, &addment);
				
				crank_cplx_float_mul (&e, &y, &ea);
				crank_cplx_float_mul (&f, &x, &fa);
				crank_cplx_float_sub (&fa, &ea, &addment);
						
				crank_mat_cplx_float_n_set (&pa, j, k, &addment);
			}
		}
		
		for (j = 0; j < n; j++) {
			crank_mat_cplx_float_n_set (r, i, i + j,
				crank_mat_cplx_float_n_peek (&pa, 0, j));
		}
		
		crank_mat_cplx_float_n_slice (&pa, 1, 1, pa.rn, pa.cn, &pa);
	}
	
	crank_cplx_float_init (&last, crank_cplx_float_get_norm (pa.data + 0), 0.0f);
	
	crank_mat_cplx_float_n_set (r, a->rn - 1, a->rn - 1, &last);
	
	crank_mat_cplx_float_n_fini (&pa);
	
	return TRUE;
}
