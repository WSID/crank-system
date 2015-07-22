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

#include <glib.h>

#include "crankbase.h"

//////// Declaration ///////////////////////////////////////////////////////////

static void	test_lu (void);

static void	test_lu_p (void);

static void test_gram_schmidt (void);

static void test_qr_householder (void);

static void test_qr_givens (void);

static void test_eval_power (void);

static void test_eval_qr (void);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (	gint   argc,
      	gchar *argv[] )
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/crank/base/advmat/lu/mat/float/n", test_lu);

	g_test_add_func ("/crank/base/advmat/lup/mat/float/n", test_lu_p);

	g_test_add_func ("/crank/base/advmat/qr/gram_schmidt/mat/float/n", test_gram_schmidt);
	
	g_test_add_func ("/crank/base/advmat/qr/householder/mat/float/n", test_qr_householder);
	
	g_test_add_func ("/crank/base/advmat/qr/givens/mat/float/n", test_qr_givens);
	
	g_test_add_func ("/crank/base/advmat/eval/power/mat/float/n", test_eval_power);
	
	g_test_add_func ("/crank/base/advmat/eval/qr/mat/float/n", test_eval_qr);
	g_test_run ();

	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////


static void
test_lu (void)
{
	CrankMatFloatN	a = {0};
  	CrankMatFloatN	l = {0};
  	CrankMatFloatN	u = {0};

  	g_message ("initializing A");
  	crank_mat_float_n_init (&a, 3, 3,
		3.0f,	12.0f,	21.0f,
		8.0f,	39.0f,	84.0f,
		2.0f,	16.0f,	49.0f	);
  	g_message ("initialized A");

	g_assert (crank_lu_mat_float_n (&a, &l, &u));

	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 0, 0), ==,  3.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 0, 1), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 0, 2), ==, 0.0f);

	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 1, 0), ==, 8.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 1, 1), ==, 7.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 1, 2), ==, 0.0f);

	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 2, 0), ==, 2.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 2, 1), ==, 8.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 2, 2), ==, 3.0f);


	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 0, 0), ==, 1.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 0, 1), ==, 4.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 0, 2), ==, 7.0f);

	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 1, 0), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 1, 1), ==, 1.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 1, 2), ==, 4.0f);

	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 2, 0), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 2, 1), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 2, 2), ==, 1.0f);

	crank_mat_float_n_fini (&a);
	crank_mat_float_n_fini (&l);
	crank_mat_float_n_fini (&u);
}


static void
test_lu_p (void)
{
	CrankMatFloatN	a = {0};
	CrankPermutation p = {0};
  	CrankMatFloatN	l = {0};
  	CrankMatFloatN	u = {0};

  	crank_mat_float_n_init (&a, 3, 3,
  		0.0f,	4.0f,	3.0f,
		3.0f,	6.0f,	6.0f,
		2.0f,	20.0f,	8.0f	);

	g_assert (crank_lu_p_mat_float_n (&a, &p, &l, &u));
	
	g_assert_cmpuint (crank_permutation_get (&p, 0), ==, 1);
	g_assert_cmpuint (crank_permutation_get (&p, 1), ==, 2);
	g_assert_cmpuint (crank_permutation_get (&p, 2), ==, 0);

	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 0, 0), ==, 3.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 0, 1), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 0, 2), ==, 0.0f);

	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 1, 0), ==, 2.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 1, 1), ==, 16.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 1, 2), ==, 0.0f);

	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 2, 0), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 2, 1), ==, 4.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&l, 2, 2), ==, 2.0f);


	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 0, 0), ==, 1.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 0, 1), ==, 2.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 0, 2), ==, 2.0f);

	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 1, 0), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 1, 1), ==, 1.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 1, 2), ==, 0.25f);

	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 2, 0), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 2, 1), ==, 0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&u, 2, 2), ==, 1.0f);

	crank_mat_float_n_fini (&a);
	crank_permutation_fini (&p);
	crank_mat_float_n_fini (&l);
	crank_mat_float_n_fini (&u);
}

static void
test_gram_schmidt (void)
{
	CrankMatFloatN	a = {0};
	CrankMatFloatN	q = {0};
	CrankMatFloatN	r = {0};
	
	crank_mat_float_n_init (&a, 3, 3,
		3.0f,	4.0f,	1.0f,
		2.0f,	2.0f,	1.0f,
		4.0f,	2.0f,	1.0f	);

	g_assert (crank_gram_schmidt_mat_float_n (&a, &q, &r));
	
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 0, 0), ==,  0.5571f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 0, 1), ==,  0.7459f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 0, 2), ==, -0.3651f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 1, 0), ==,  0.3714f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 1, 1), ==,  0.1695f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 1, 2), ==,  0.9129f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 2, 0), ==,  0.7428f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 2, 1), ==, -0.6442f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&q, 2, 2), ==, -0.1826f);
	
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 0), ==,  5.3852f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 1), ==,  4.4567f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 2), ==,  1.6713f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 0), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 1), ==,  2.0342f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 2), ==,  0.2712f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 0), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 1), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 2), ==,  0.3651f);
	
	crank_mat_float_n_fini (&a);
	crank_mat_float_n_fini (&q);
	crank_mat_float_n_fini (&r);
}

static void
test_qr_householder (void)
{
	CrankMatFloatN	a = {0};
	CrankMatFloatN	r = {0};
	
	crank_mat_float_n_init (&a, 3, 3,
		3.0f,	4.0f,	1.0f,
		2.0f,	2.0f,	1.0f,
		4.0f,	2.0f,	1.0f	);

	g_assert (crank_qr_householder_mat_float_n (&a, &r));
	
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 0), ==,  5.3852f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 1), ==,  4.4567f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 2), ==,  1.6713f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 0), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 1), ==,  2.0342f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 2), ==,  0.2712f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 0), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 1), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 2), ==,  0.3651f);
	
	
	crank_mat_float_n_fini (&a);
	crank_mat_float_n_fini (&r);
}

static void
test_qr_givens (void)
{
	CrankMatFloatN	a = {0};
	CrankMatFloatN	r = {0};
	
	crank_mat_float_n_init (&a, 3, 3,
		3.0f,	4.0f,	1.0f,
		2.0f,	2.0f,	1.0f,
		4.0f,	2.0f,	1.0f	);

	g_assert (crank_qr_givens_mat_float_n (&a, &r));
	
	g_message ("%s", crank_mat_float_n_to_string (&r));
	
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 0), ==,  5.3852f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 1), ==,  4.4567f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 0, 2), ==,  1.6713f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 0), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 1), ==,  2.0342f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 1, 2), ==,  0.2712f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 0), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 1), ==,  0.0f);
	crank_assert_cmpfloat (crank_mat_float_n_get (&r, 2, 2), ==,  0.3651f);
	
	
	crank_mat_float_n_fini (&a);
	crank_mat_float_n_fini (&r);
}

static void
test_eval_power (void)
{
	CrankMatFloatN	a = {0};
	CrankVecFloatN	evec = {0};
	
	crank_mat_float_n_init (&a, 3, 3,
		1.0f,	2.0f,	3.0f,
		2.0f,	4.0f,	9.0f,
		3.0f,	9.0f,	16.0f	);

	crank_assert_cmpfloat (crank_eval_power_mat_float_n (&a, NULL, &evec), ==, 21.4467f);
	
	crank_assert_cmpfloat (crank_vec_float_n_get (&evec, 0), ==, 0.1729f);
	crank_assert_cmpfloat (crank_vec_float_n_get (&evec, 1), ==, 0.4671f);
	crank_assert_cmpfloat (crank_vec_float_n_get (&evec, 2), ==, 0.8671f);
	
	crank_vec_float_n_fini (&evec);
	crank_mat_float_n_fini (&a);
}

static void
test_eval_qr (void)
{
	CrankMatFloatN	a = {0};
	GHashTable*		t;
	GHashTableIter	iter;
	
	gfloat*			key;
	guint*			value;
	
	guint			i;
	
	crank_mat_float_n_init (&a, 3, 3,
		1.0f,	2.0f,	3.0f,
		2.0f,	4.0f,	9.0f,
		3.0f,	9.0f,	16.0f	);

	t = crank_eval_qr_mat_float_n (&a);
	
	g_assert_nonnull (t);
	
	g_hash_table_iter_init (&iter, t);
	
	for (i = 0; i < 3; i++) {
		g_assert (g_hash_table_iter_next (&iter,
				(gpointer *)&key,
				(gpointer *)&value	));
	
		if ( 1.0f < *key )
			crank_assert_cmpfloat (*key, ==, 21.4467f);
		else if ( 0.0f < *key)
			crank_assert_cmpfloat (*key, ==, 0.4618f);
		else crank_assert_cmpfloat (*key, ==, -0.9085f);
		
		g_assert_cmpuint (GPOINTER_TO_INT (value), ==, 1);
	}
	
	crank_mat_float_n_fini (&a);
	g_hash_table_unref (t);
}
