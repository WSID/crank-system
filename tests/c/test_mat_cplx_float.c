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


static void		test_n_equal (void);
static void		test_n_to_string (void);

static void		test_n_get (void);
static void		test_n_get_row (void);
static void		test_n_get_col (void);
static void		test_n_slice (void);

static void		test_n_tr (void);
static void		test_n_det (void);
static void		test_n_cof (void);
static void		test_n_adj (void);
static void		test_n_diag (void);

static void		test_n_neg (void);
static void		test_n_transpose (void);
static void		test_n_inverse (void);

static void		test_n_mulrs (void);
static void		test_n_divrs (void);
static void		test_n_mulv (void);
static void		test_n_add (void);
static void		test_n_sub (void);
static void		test_n_mul (void);
static void		test_n_mixs (void);
static void		test_n_mix (void);

static void		test_n_shuffle_row (void);
static void		test_n_shuffle_col (void);


//////// Main //////////////////////////////////////////////////////////////////

gint	main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);

  	g_test_add_func ("/crank/base/mat/float/n/equal",		test_n_equal);
  	g_test_add_func ("/crank/base/mat/float/n/to_string",	test_n_to_string);
  	g_test_add_func ("/crank/base/mat/float/n/get",			test_n_get);
  	g_test_add_func ("/crank/base/mat/float/n/get_row",		test_n_get_row);
  	g_test_add_func ("/crank/base/mat/float/n/get_col",		test_n_get_col);
  	g_test_add_func ("/crank/base/mat/float/n/slice",		test_n_slice);
  	g_test_add_func ("/crank/base/mat/float/n/tr",			test_n_tr);
  	g_test_add_func ("/crank/base/mat/float/n/det",			test_n_det);
  	g_test_add_func ("/crank/base/mat/float/n/cof",			test_n_cof);
  	g_test_add_func ("/crank/base/mat/float/n/adj",			test_n_adj);
  	g_test_add_func ("/crank/base/mat/float/n/neg",			test_n_neg);
  	g_test_add_func ("/crank/base/mat/float/n/diag",		test_n_diag);
  	g_test_add_func ("/crank/base/mat/float/n/transpose",	test_n_transpose);
  	g_test_add_func ("/crank/base/mat/float/n/inverse",		test_n_inverse);
  	g_test_add_func ("/crank/base/mat/float/n/mulrs",		test_n_mulrs);
  	g_test_add_func ("/crank/base/mat/float/n/divrs",		test_n_divrs);
  	g_test_add_func ("/crank/base/mat/float/n/mulv",		test_n_mulv);
  	g_test_add_func ("/crank/base/mat/float/n/add",			test_n_add);
  	g_test_add_func ("/crank/base/mat/float/n/sub",			test_n_sub);
  	g_test_add_func ("/crank/base/mat/float/n/mul",			test_n_mul);
  	g_test_add_func ("/crank/base/mat/float/n/mixs",		test_n_mixs);
  	g_test_add_func ("/crank/base/mat/float/n/mix",			test_n_mix);
  	
  	g_test_add_func ("/crank/base/mat/float/n/shuffle/row",	test_n_shuffle_row);
  	g_test_add_func ("/crank/base/mat/float/n/shuffle/col",	test_n_shuffle_col);

  	g_test_run ();
  	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////




static void
test_n_equal (void)
{
	CrankMatCplxFloatN	a;
  	CrankMatCplxFloatN	b;
  	CrankMatCplxFloatN	c;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f	);

  	crank_mat_cplx_float_n_init_uc (&b, 2, 2,
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f	);

  	crank_mat_cplx_float_n_init_uc (&c, 2, 2,
			1.0f, 2.0f, 3.0f, 4.0f,
			4.0f, 5.0f, 6.0f, 7.0f	);

	g_assert (  crank_mat_cplx_float_n_equal (&a, &b));
	g_assert (! crank_mat_cplx_float_n_equal (&a, &c));

  	crank_mat_cplx_float_n_fini (&a);
  	crank_mat_cplx_float_n_fini (&b);
  	crank_mat_cplx_float_n_fini (&c);
}

static void
test_n_to_string (void)
{
	CrankMatCplxFloatN	a;
  	gchar*			astr;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
			1.0f, 2.0f, 3.0f, 4.0f,
			4.0f, 5.0f, 6.0f, 7.0f	);

  	astr = crank_mat_cplx_float_n_to_string (&a);

  	g_assert_cmpstr (astr, ==, "[[1 + (2i), 3 + (4i)], [4 + (5i), 6 + (7i)]]");

  	crank_mat_cplx_float_n_fini (&a);
}

static void
test_n_get (void)
{
	CrankMatCplxFloatN	a;
	CrankCplxFloat		v;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);

	
	crank_mat_cplx_float_n_get (&a, 0, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 1.0f, 2.0f);
	
	crank_mat_cplx_float_n_get (&a, 0, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 3.0f, 4.0f);
	
	crank_mat_cplx_float_n_get (&a, 1, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 4.0f, 5.0f);
	
	crank_mat_cplx_float_n_get (&a, 1, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 6.0f, 7.0f);

  	crank_mat_cplx_float_n_fini (&a);
}

static void
test_n_get_row (void)
{
	CrankMatCplxFloatN	a;
  	CrankVecCplxFloatN	r = {0};

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);

	crank_mat_cplx_float_n_get_row (&a, 0, &r);

	g_assert_cmpuint (r.n, ==, 2);
  	crank_assert_eqcplxfloat_cimm (r.data + 0, 1.0f, 2.0f);
  	crank_assert_eqcplxfloat_cimm (r.data + 1, 3.0f, 4.0f);

	crank_mat_cplx_float_n_get_row (&a, 1, &r);

	g_assert_cmpuint (r.n, ==, 2);
  	crank_assert_eqcplxfloat_cimm (r.data + 0, 4.0f, 5.0f);
  	crank_assert_eqcplxfloat_cimm (r.data + 1, 6.0f, 7.0f);

	crank_mat_cplx_float_n_fini (&a);
  	crank_vec_cplx_float_n_fini (&r);
}

static void
test_n_get_col (void)
{
	CrankMatCplxFloatN	a;
  	CrankVecCplxFloatN	c = {0};

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);

	crank_mat_cplx_float_n_get_col (&a, 0, &c);

  	g_assert_cmpuint (c.n, ==, 2);
  	crank_assert_eqcplxfloat_cimm (c.data + 0, 1.0f, 2.0f);
  	crank_assert_eqcplxfloat_cimm (c.data + 1, 4.0f, 5.0f);

  	crank_mat_cplx_float_n_get_col (&a, 1, &c);

  	g_assert_cmpuint (c.n, ==, 2);
  	crank_assert_eqcplxfloat_cimm (c.data + 0, 3.0f, 4.0f);
  	crank_assert_eqcplxfloat_cimm (c.data + 1, 6.0f, 7.0f);

  	crank_mat_cplx_float_n_fini (&a);
  	crank_vec_cplx_float_n_fini (&c);
}

static void
test_n_slice (void)
{
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	b;
	
	crank_mat_cplx_float_n_init_uc (&a, 3, 3,
			1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
			4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
			7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);

	crank_mat_cplx_float_n_slice (&a, 1, 1, 3, 2, &b);
	
	g_assert_cmpuint (b.rn, ==, 2);
	g_assert_cmpuint (b.cn, ==, 1);
	
	crank_assert_eqcplxfloat_cimm (b.data + 0, 5.0f, 5.5f);
	crank_assert_eqcplxfloat_cimm (b.data + 1, 8.0f, 4.0f);
	
	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
}

static void
test_n_tr (void)
{
	CrankMatCplxFloatN	a;
	CrankCplxFloat		tr;
	
	crank_mat_cplx_float_n_init_uc (&a, 3, 3,
			1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
			4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
			7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);

	crank_mat_cplx_float_n_get_tr (&a, &tr);
	crank_assert_eqcplxfloat_cimm (&tr, 15.0f, 11.5f);

  	crank_mat_cplx_float_n_fini (&a);
}

static void
test_n_det (void)
{
	CrankMatCplxFloatN	a;
	CrankCplxFloat		det;
	
	crank_mat_cplx_float_n_init_uc (&a, 3, 3,
			1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
			4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
			7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);

	crank_mat_cplx_float_n_get_det (&a, &det);
	crank_assert_eqcplxfloat_cimm (&det, 4.0f, -1.75f);

  	crank_mat_cplx_float_n_fini (&a);
}

static void
test_n_cof (void)
{
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	cof;
	
	crank_mat_cplx_float_n_init_uc (&a, 3, 3,
			1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
			4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
			7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);

	crank_mat_cplx_float_n_get_cof (&a, &cof);
	
	crank_assert_eqcplxfloat_cimm (cof.data + 0,	-1.7500f,  -4.0000f);
	crank_assert_eqcplxfloat_cimm (cof.data + 1,	 3.5000f,   8.0000f);
	crank_assert_eqcplxfloat_cimm (cof.data + 2,	-1.7500f,  -4.0000f);
	crank_assert_eqcplxfloat_cimm (cof.data + 3,	-0.7500f,  16.5000f);
	crank_assert_eqcplxfloat_cimm (cof.data + 4,	-3.0000f, -24.0000f);
	crank_assert_eqcplxfloat_cimm (cof.data + 5,	 3.2500f,   8.5000f);
	crank_assert_eqcplxfloat_cimm (cof.data + 6,	 5.5000f, -11.0000f);
	crank_assert_eqcplxfloat_cimm (cof.data + 7,	-4.5000f,  16.0000f);
	crank_assert_eqcplxfloat_cimm (cof.data + 8,	 0.0000f,  -6.0000f);

  	crank_mat_cplx_float_n_fini (&a);
  	crank_mat_cplx_float_n_fini (&cof);
}

static void
test_n_adj (void)
{
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	adj;
	
	crank_mat_cplx_float_n_init_uc (&a, 3, 3,
			1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
			4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
			7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);

	crank_mat_cplx_float_n_get_adj (&a, &adj);
	
	crank_assert_eqcplxfloat_cimm (adj.data + 0,	-1.7500f,  -4.0000f);
	crank_assert_eqcplxfloat_cimm (adj.data + 1,	-0.7500f,  16.5000f);
	crank_assert_eqcplxfloat_cimm (adj.data + 2,	 5.5000f, -11.0000f);
	crank_assert_eqcplxfloat_cimm (adj.data + 3,	 3.5000f,   8.0000f);
	crank_assert_eqcplxfloat_cimm (adj.data + 4,	-3.0000f, -24.0000f);
	crank_assert_eqcplxfloat_cimm (adj.data + 5,	-4.5000f,  16.0000f);
	crank_assert_eqcplxfloat_cimm (adj.data + 6,	-1.7500f,  -4.0000f);
	crank_assert_eqcplxfloat_cimm (adj.data + 7,	 3.2500f,   8.5000f);
	crank_assert_eqcplxfloat_cimm (adj.data + 8,	 0.0000f,  -6.0000f);

  	crank_mat_cplx_float_n_fini (&a);
  	crank_mat_cplx_float_n_fini (&adj);
}

static void
test_n_diag (void)
{
	CrankMatCplxFloatN	a;
	CrankVecCplxFloatN	b = {0};

	crank_mat_cplx_float_n_init_uc (&a, 3, 3,
			1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
			4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
			7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);
			
	crank_mat_cplx_float_n_get_diag (&a, &b);
	
	crank_assert_eqcplxfloat_cimm (b.data + 0, 1.0f, 1.5f);
	crank_assert_eqcplxfloat_cimm (b.data + 1, 5.0f, 5.5f);
	crank_assert_eqcplxfloat_cimm (b.data + 2, 9.0f, 4.5f);

	crank_mat_cplx_float_n_fini (&a);
	crank_vec_cplx_float_n_fini (&b);
}

static void
test_n_neg (void)
{
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	b;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
	crank_mat_cplx_float_n_neg (&a, &b);
	
	crank_assert_eqcplxfloat_cimm (b.data + 0,	-1.0f, -2.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 1,	-3.0f, -4.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 2,	-4.0f, -5.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 3,	-6.0f, -7.0f);
	
	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
}

static void
test_n_transpose (void)
{
	
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	b;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 3,
		1.0f, 2.0f, 	3.0f, 4.0f, 	5.0f, 6.0f,
		7.0f, 8.0f, 	9.0f, 10.0f,	11.0f, 12.0f);
		
	crank_mat_cplx_float_n_transpose (&a, &b);
	
	g_assert_cmpuint (b.rn, ==, 3);
	g_assert_cmpuint (b.cn, ==, 2);
	
	crank_assert_eqcplxfloat_cimm (b.data + 0,	1.0f, 2.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 1,	7.0f, 8.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 2,	3.0f, 4.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 3,	9.0f, 10.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 4,	5.0f, 6.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 5,	11.0f, 12.0f);
	
	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
}

static void
test_n_inverse (void)
{
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	ainv;
	
	crank_mat_cplx_float_n_init_uc (&a, 3, 3,
			1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
			4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
			7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);

	crank_mat_cplx_float_n_inverse (&a, &ainv);
	
	crank_assert_eqcplxfloat_cimm (ainv.data + 0,	0.0f, -1.0f);
	crank_assert_eqcplxfloat_cimm (ainv.data + 1,	-1.6721f, 3.3934f);
	crank_assert_eqcplxfloat_cimm (ainv.data + 2,	2.1639f, -1.8033f);
	crank_assert_eqcplxfloat_cimm (ainv.data + 3,	0.0f, 2.0f);
	crank_assert_eqcplxfloat_cimm (ainv.data + 4,	1.5738f, -5.3115f);
	crank_assert_eqcplxfloat_cimm (ainv.data + 5,	-2.4131f, 2.9443f);
	crank_assert_eqcplxfloat_cimm (ainv.data + 6,	0.0f, -1.0f);
	crank_assert_eqcplxfloat_cimm (ainv.data + 7,	-0.0984f, 2.0820f);
	crank_assert_eqcplxfloat_cimm (ainv.data + 8,	0.5508f, -1.2590f);

  	crank_mat_cplx_float_n_fini (&a);
  	crank_mat_cplx_float_n_fini (&ainv);
}

static void
test_n_mulrs (void)
{
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	b;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
	crank_mat_cplx_float_n_mulrs (&a, 3, &b);
	
	crank_assert_eqcplxfloat_cimm (b.data + 0,	3.0f, 6.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 1,	9.0f, 12.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 2,	12.0f, 15.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 3,	18.0f, 21.0f);
	
	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
}

static void
test_n_divrs (void)
{
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	b;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
	crank_mat_cplx_float_n_divrs (&a, 2.0f, &b);
	
	crank_assert_eqcplxfloat_cimm (b.data + 0,	0.5f, 1.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 1,	1.5f, 2.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 2,	2.0f, 2.5f);
	crank_assert_eqcplxfloat_cimm (b.data + 3,	3.0f, 3.5f);
	
	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
}

static void
test_n_mulv (void)
{
	CrankMatCplxFloatN	a;
	CrankVecCplxFloatN	b = {0};
	CrankVecCplxFloatN	c = {0};

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
	crank_vec_cplx_float_n_init_uc (&b, 2,
		2.0f, 3.0f, 5.0f, 7.0f);

	crank_mat_cplx_float_n_mulv (&a, &b, &c);
	
	crank_assert_eqcplxfloat_cimm (c.data + 0, -17.0f, 48.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 1, -26.0f, 99.0f);
	
	crank_vec_cplx_float_n_fini (&c);
	crank_vec_cplx_float_n_fini (&b);
	crank_mat_cplx_float_n_fini (&a);
}

static void
test_n_add (void)
{
  	CrankMatCplxFloatN	a;
  	CrankMatCplxFloatN	b;
  	CrankMatCplxFloatN	c;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
  	crank_mat_cplx_float_n_init_uc (&b, 2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f	);

  	crank_mat_cplx_float_n_add (&a, &b, &c);

	crank_assert_eqcplxfloat_cimm (c.data + 0, 3.0f, 5.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 1, 8.0f, 11.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 2, 8.0f, 7.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 3, 7.0f, 10.0f);

  	crank_mat_cplx_float_n_fini (&c);
  	crank_mat_cplx_float_n_fini (&b);
  	crank_mat_cplx_float_n_fini (&a);
}

static void
test_n_sub (void)
{
  	CrankMatCplxFloatN	a;
  	CrankMatCplxFloatN	b;
  	CrankMatCplxFloatN	c;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
  	crank_mat_cplx_float_n_init_uc (&b, 2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f	);

  	crank_mat_cplx_float_n_sub (&a, &b, &c);

	crank_assert_eqcplxfloat_cimm (c.data + 0, -1.0f, -1.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 1, -2.0f, -3.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 2, 0.0f, 3.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 3, 5.0f, 4.0f);

  	crank_mat_cplx_float_n_fini (&a);
  	crank_mat_cplx_float_n_fini (&b);
  	crank_mat_cplx_float_n_fini (&c);
}

static void
test_n_mul (void)
{
  	CrankMatCplxFloatN	a;
  	CrankMatCplxFloatN	b;
  	CrankMatCplxFloatN	c;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
  	crank_mat_cplx_float_n_init_uc (&b, 2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f	);

	crank_mat_cplx_float_n_mul (&a, &b, &c);
	
	g_assert_cmpuint (c.rn, ==, 2);
	g_assert_cmpuint (c.cn, ==, 2);

	crank_assert_eqcplxfloat_cimm (c.data + 0, 0.0f, 29.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 1, -18.0f, 30.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 2, 3.0f, 62.0f);
	crank_assert_eqcplxfloat_cimm (c.data + 3, -30.0f, 78.0f);
	
	crank_mat_cplx_float_n_fini (&c);
	crank_mat_cplx_float_n_fini (&b);
	crank_mat_cplx_float_n_fini (&a);
}

static void
test_n_mixs (void)
{
  	CrankMatCplxFloatN	a;
  	CrankMatCplxFloatN	b;
  	CrankMatCplxFloatN	c;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
  	crank_mat_cplx_float_n_init_uc (&b, 2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f	);
		
	crank_mat_cplx_float_n_mixs (&a, &b, 0.5, &c);
	
	crank_assert_eqcplxfloat_cimm (c.data + 0, 1.5f, 2.5f);
	crank_assert_eqcplxfloat_cimm (c.data + 1, 4.0f, 5.5f);
	crank_assert_eqcplxfloat_cimm (c.data + 2, 4.0f, 3.5f);
	crank_assert_eqcplxfloat_cimm (c.data + 3, 3.5f, 5.0f);
	
	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
	crank_mat_cplx_float_n_fini (&c);
}

static void
test_n_mix (void)
{
	CrankMatCplxFloatN	a;
	CrankMatCplxFloatN	b;
	CrankMatFloatN		c = {0};
	CrankMatCplxFloatN	d;

  	crank_mat_cplx_float_n_init_uc (&a, 2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	
  	crank_mat_cplx_float_n_init_uc (&b, 2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f	);
	
	crank_mat_float_n_init (&c, 2, 2,
		0.0f, 0.3f,
		0.6f, 0.9f);

	crank_mat_cplx_float_n_mix (&a, &b, &c, &d);
	
	crank_assert_eqcplxfloat_cimm (d.data + 0, 1.0f, 2.0f);
	crank_assert_eqcplxfloat_cimm (d.data + 1, 3.6f, 4.9f);
	crank_assert_eqcplxfloat_cimm (d.data + 2, 4.0f, 3.2f);
	crank_assert_eqcplxfloat_cimm (d.data + 3, 1.5f, 3.4f);
	
	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
	crank_mat_float_n_fini (&c);
	crank_mat_cplx_float_n_fini (&d);
}

static void
test_n_shuffle_row (void)
{
	CrankMatCplxFloatN		a;
	CrankMatCplxFloatN		b;
	CrankPermutation		p;
	
	crank_mat_cplx_float_n_init_uc (&a, 4, 1,
		1.0f, 3.0f,
		7.0f, 2.0f,
		1.0f, 4.0f,
		3.0f, 1.0f	);

	crank_permutation_init (&p, 4,
		1, 3, 0, 2	);

	crank_mat_cplx_float_n_shuffle_row (&a, &p, &b);
	
	crank_assert_eqcplxfloat_cimm (b.data + 0, 7.0f, 2.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 1, 3.0f, 1.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 2, 1.0f, 3.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 3, 1.0f, 4.0f);

	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
	crank_permutation_fini (&p);
}

static void
test_n_shuffle_col (void)
{
	CrankMatCplxFloatN		a;
	CrankMatCplxFloatN		b;
	CrankPermutation		p;
	
	crank_mat_cplx_float_n_init_uc (&a, 1, 4,
		1.0f, 7.0f, 	1.0f, 3.0f,		3.0f, 2.0f, 	4.0f, 1.0f	);

	crank_permutation_init (&p, 4,
		1, 3, 0, 2	);

	crank_mat_cplx_float_n_shuffle_col (&a, &p, &b);
	
	crank_assert_eqcplxfloat_cimm (b.data + 0, 1.0f, 3.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 1, 4.0f, 1.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 2, 1.0f, 7.0f);
	crank_assert_eqcplxfloat_cimm (b.data + 3, 3.0f, 2.0f);

	crank_mat_cplx_float_n_fini (&a);
	crank_mat_cplx_float_n_fini (&b);
	crank_permutation_fini (&p);
}
