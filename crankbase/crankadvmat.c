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

#include "crankveccommon.h"
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
 *   A = L U
 *
 *   L is lower triangular matrix.
 *
 *   U is upper triangular matrix.
 *   * Crout's Method.
 */


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
