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

#include <glib.h>
#include <glib-object.h>

#include "crankpermutation.h"
#include "crankveccommon.h"
#include "crankvecfloat.h"
#include "crankmatfloat.h"
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
 * multipling diagonal components of each factors, and it tooks O(n cube).
 * * Getting LU decomposition takes O(n cube) times.
 * * And getting product of diagonal components takes O(n) times.
 * This is much faster than O(n!) times.
 *
 *
 *
 * Currently Crank System provides,
 * * LU Decomposition
 *   * A = L U
 *     * L is lower triangular matrix.
 *     * U is upper triangular matrix.
 *   * Crout's Method.
 *
 * * QR Decomposition
 *   * A = Q R
 *     * Q is Orthogonal Matrix.
 *     * R is upper triangular matrix.
 *   * Gram Schmidt Process
 *   * Householder Method (Does not return Q)
 */


static guint	float_hash (gconstpointer	v);
static gboolean	float_equal (gconstpointer	v1, gconstpointer	v2);
static gfloat*	float_dup (gfloat			f);
static void		destroy_slice_float		(gpointer		ptr);



/**
 * crank_lu_mat_float_n:
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
 * crank_lu_p_mat_float_n().
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

  	if (! crank_mat_float_n_is_square (a)) {
	  	crank_mat_float_n_fini (l);
	  	crank_mat_float_n_fini (u);
	  	g_warning ("Adv: MatFloatN: lu: non square: %u, %u", a->rn, a->cn);
	  	return FALSE;
	}

  	n = a->rn;

  	if (n == 0) {
	  	crank_mat_float_n_fini (l);
	  	crank_mat_float_n_fini (u);
	  	return TRUE;
	}

  	if (n == 1) {
	  	if (a->data[0] != 0) {
			crank_mat_float_n_init (l, 1, 1, a->data[0]);
			crank_mat_float_n_init (u, 1, 1, 1.0f);
		  	return TRUE;
		}
		else {
			// If a == [[0]] then a is singular and cannot be defactorized.
		  	crank_mat_float_n_fini (l);
		  	crank_mat_float_n_fini (u);
		  	return FALSE;
		}
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
crank_lu_p_mat_float_n (	CrankMatFloatN*		a,
							CrankPermutation*	p,
							CrankMatFloatN*		l,
							CrankMatFloatN*		u	)
{
	guint			i;
	guint			j;
	CrankMatFloatN	na = {0};
	

  	if (! crank_mat_float_n_is_square (a)) {
	  	crank_mat_float_n_fini (l);
	  	crank_mat_float_n_fini (u);
	  	g_warning ("Adv: MatFloatN: lu_p: non square: %u, %u", a->rn, a->cn);
	  	return FALSE;
	}
	
	// Do pivoting.
	// Maximaze diagnoal component.
	crank_permutation_init_identity (p, a->rn);
	
	for (i = 0; i < a->rn; i++) {
		guint	max_index = i;
		gfloat	max =
				crank_mat_float_n_get (a,	crank_permutation_get (p, i), i);
				
		for (j = i + 1; j < a->rn; j++) {
			gfloat	cur =
				crank_mat_float_n_get (a, 	crank_permutation_get (p, j), i);
			
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
 * crank_gram_schmidt_mat_float_n:
 * @a: A Matrix.
 * @q: (out): A Resulting Orthogonal Matrix.
 * @r: (out): The upper triangular.
 *
 * Gets QR Decomposition by Gram Schmidt process.
 *
 * Returns: %TRUE if @a has QR Decomposition.
 */
gboolean
crank_gram_schmidt_mat_float_n (	CrankMatFloatN*		a,
									CrankMatFloatN*		q,
									CrankMatFloatN*		r	)
{
	CrankVecFloatN*		e;
	CrankVecFloatN**	ep;
	
	guint	i;
	guint	j;
	guint	k;
	
	if (a->rn == a->cn) {
		e = g_new0 (CrankVecFloatN, a->rn);
		crank_mat_float_n_init_fill (r, a->rn, a->rn, 0);
		
		for (i = 0; i < a->rn; i++) {
			CrankVecFloatN	ac;
			CrankVecFloatN	u;
			
			// u = a.col[i]
			crank_mat_float_n_get_col (a, i, &ac);
			crank_vec_float_n_copy (&ac, &u);
		
			// u -= proj(a.col[i], e[0..(i-1)])
			// r = a.col[i] dot e
			for (j = 0; j < i; j++) {
				CrankVecFloatN	proj;
				gfloat			dot;
				dot = crank_vec_float_n_dot (e + j, &ac);
				
				// If QR decomposition is not possible, return.
				if (dot == 0.0f) {
					for (k = 0; k < i; k++) crank_vec_float_n_fini (e + k);
					g_free (e);
					crank_vec_float_n_fini (&ac);
					crank_vec_float_n_fini (&u);
					crank_mat_float_n_fini (q);
					crank_mat_float_n_fini (r);
					return FALSE;
				}
				
				crank_vec_float_n_muls (e + j, dot, &proj);
				
				crank_vec_float_n_sub_self (&u, &proj);
				crank_mat_float_n_set (r, j, i, dot);
			}
		
			// e[i] = u.unit
			crank_mat_float_n_set (r, i, i, crank_vec_float_n_get_magn (&u));
			crank_vec_float_n_unit (&u, e + i);
			crank_vec_float_n_fini (&u);
		}
		
		ep = g_new (CrankVecFloatN*, a->rn);
		for (i = 0; i < a->rn; i++) ep[i] = e + i;

		crank_mat_float_n_init_cvarr (q, a->rn, ep);

		for (i = 0; i < a->rn; i++) {
			crank_vec_float_n_fini (e + i);
		}
		g_free (e);
		g_free (ep);
		
		return TRUE;
	}
	else {
		g_warning ("Adv: MatFloatN: gram schmidt: non square: %u, %u",
				a->rn, a->cn);
		return FALSE;
	}
}

/**
 * crank_qr_householder_mat_float_n:
 * @a: A Matrix.
 * @r: (out): A Lower triangular matrix.
 *
 * Performs QR Decomposition by householder method.
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
	
	if (a->rn == a->cn) {
	
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
	else {
		g_warning ("Adv: MatFloatN: QR householder: unsupported size: not square: %u, %u",
				a->rn, a->cn);
		return FALSE;
	}
}

/**
 * crank_qr_givens_mat_float_n:
 * @a: A Matrix.
 * @r: (out): A Lower triangular matrix.
 *
 * Performs QR Decomposition by Givens rotation.
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
	
	if (a->rn == a->cn) {
	
		if (a->rn == 1) {
			crank_mat_float_n_init (r, 0, 0,
					crank_mat_float_n_get (a, 0, 0));
			return TRUE;
		}
		
		crank_mat_float_n_init_fill (r, a->rn, a->rn, 0.0f);
		crank_mat_float_n_copy (a, &pa);
		
		for (i = 0; i < a->rn - 1; i++) {
			guint	n = a->rn - i;
			
			for (j = n - 1; 0 < j; j--) {
				CrankVecFloat2 x = {
						crank_mat_float_n_get (&pa, j - 1, 0),
						crank_mat_float_n_get (&pa, j, 0)};
				
				if ((x.x == 0) && (x.y == 0)) {
					crank_mat_float_n_fini (&pa);
					crank_mat_float_n_fini (r);
					
					return FALSE;
				}
				
				crank_vec_float2_unit (&x, &x);
				
				// Multiplies Givens rotation matrix.
				//
				// We don't build up Full givens rotation matrix,
				// instead we apply this with sin, cos value.
				for (k = 0; k < n; k++) {
					gfloat	e = crank_mat_float_n_get (&pa, j - 1, k);
					gfloat	f = crank_mat_float_n_get (&pa, j, k);
					
					crank_mat_float_n_set (&pa, j-1, k,
							e * x.x + f * x.y);
							
					crank_mat_float_n_set (&pa, j, k,
							- e * x.y + f * x.x);
				}
			}
			
			for (j = 0; j < n; j++) {
				crank_mat_float_n_set (r, i, i + j,
					crank_mat_float_n_get (&pa, 0, j));
			}
			
			crank_mat_float_n_slice (&pa, 1, 1, pa.rn, pa.cn, &pa);
		}
		
		crank_mat_float_n_set (r, a->rn - 1, a->rn - 1, pa.data[0]);
		
		crank_mat_float_n_fini (&pa);
		
		return TRUE;
	}
	else {
		g_warning ("Adv: MatFloatN: QR householder: unsupported size: not square: %u, %u",
				a->rn, a->cn);
		return FALSE;
	}
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
	if (crank_mat_float_n_is_square (a)) {
		CrankVecFloatN	bs;
		CrankVecFloatN	bsmv;
		gfloat			magn = 0;
		gfloat			magnp = 0;
		
		if (b != NULL) {
			crank_vec_float_n_copy (b, &bs);
		}
		else {
			crank_mat_float_n_get_col (a, 0, &bs);
		}
		
		do {
			magnp = magn;
			crank_mat_float_n_mulv (a, &bs, &bsmv);
			magn = crank_vec_float_n_get_magn (&bsmv);
			crank_vec_float_n_divs (&bsmv, magn, &bs);
			
			crank_vec_float_n_fini (&bsmv);
		}
		while (0.0001f < ABS (magn - magnp));
		
		if (evec != NULL) crank_vec_float_n_copy (&bs, evec);
		crank_vec_float_n_fini (&bs);
		return magn;
	}
	else {
		g_warning ("Adv: MatFloatN: Power: not square: %u, %u",
				a->rn, a->cn);
		return 0.0f/0.0f;
	}
}

/**
 * crank_eval_qr_mat_float_n:
 * @a: A Matrix.
 * @evals: (out): A Vector contains eigenvalues.
 *
 * Eigenvalues are calculated by QR Algorithm; If QR Decompisition is not
 * possible, an 0-sized vector is returned.
 */
void
crank_eval_qr_mat_float_n (	CrankMatFloatN*	a,
							CrankVecFloatN*	evals	)
{
	CrankMatFloatN	ai = {0};
	CrankMatFloatN	qi = {0};
	CrankMatFloatN	ri = {0};
	gboolean		cont;
	
	guint	i;
	guint	j;
	
	cont = TRUE;
	
	if (! crank_gram_schmidt_mat_float_n (a, &qi, &ri)) {
		crank_vec_float_n_fini (evals);
		return;
	}
	
	while (cont) {
		
		crank_mat_float_n_mul (&ri, &qi, &ai);
		
		cont = FALSE;
		for (i = 0; i < a->rn; i++) { 
			for (j = 0; j < i; j++) {
				// Checks for elements are smaller than reasonably small value.
				//TODO: Make a way to adjust this value.
				
				if (0.0001f < crank_mat_float_n_get (&ai, i, j)) {
					cont = TRUE;
					break;
				}
			}
			if (cont) break;
		}
		
		if (cont) {
			if (! crank_gram_schmidt_mat_float_n (&ai, &qi, &ri)) {
				crank_mat_float_n_fini (&ai);
				crank_vec_float_n_fini (evals);
				return;
			}
		}
	}
	
	crank_mat_float_n_get_diag (&ai, evals);
	
	crank_mat_float_n_fini (&ai);
	crank_mat_float_n_fini (&qi);
	crank_mat_float_n_fini (&ri);
}



static guint
float_hash (gconstpointer	f) {
	gdouble d = (gdouble) (*(gfloat*)f);
	
	return g_double_hash (&d);
}

static gboolean
float_equal (gconstpointer	p1, gconstpointer	p2) {
	gfloat f1 = *(gfloat*)p1;
	gfloat f2 = *(gfloat*)p2;
	return (p1 == p2);
}

static gfloat*
float_dup (gfloat	f) {
	gfloat*	result = g_slice_new (gfloat);
	*result = f;
	return result;
}

static void
destroy_slice_float (gpointer	ptr) {
	g_slice_free (gfloat, ptr);
}
