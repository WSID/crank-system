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

static gboolean	test_accumulation (			CrankCplxFloat*	value,
							   				gpointer		userdata	);

static void	test_n_get (void);
static void	test_n_insert (void);
static void test_n_remove (void);
static void	test_n_foreach (void);
static void	test_n_equal (void);
static void	test_n_to_string (void);
static void	test_n_magn (void);
static void	test_n_muls (void);
static void	test_n_divs (void);
static void	test_n_mulrs (void);
static void	test_n_divrs (void);
static void	test_n_add (void);
static void	test_n_sub (void);
static void	test_n_dot (void);
static void	test_n_cmpmul (void);
static void	test_n_cmpdiv (void);
static void	test_n_cmpmod (void);
static void	test_n_cmpeq (void);
static void	test_n_mulrm (void);
static void	test_n_mixs (void);
static void	test_n_mix (void);

static void test_n_init_arruc (void);
static void test_n_init_ucarr (void);
static void test_n_init_ucv (void);
static void test_n_init_fill_uc (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (	gint argc, gchar** argv	)
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/vec/cplx/float/n/get", test_n_get);
  	g_test_add_func ("/crank/base/vec/cplx/float/n/insert", test_n_insert);
	g_test_add_func ("/crank/base/vec/cplx/float/n/foreach", test_n_foreach);
	g_test_add_func ("/crank/base/vec/cplx/float/n/equal", test_n_equal);
	g_test_add_func ("/crank/base/vec/cplx/float/n/magn", test_n_magn);
	g_test_add_func ("/crank/base/vec/cplx/float/n/muls", test_n_muls);
	g_test_add_func ("/crank/base/vec/cplx/float/n/divs", test_n_divs);
	g_test_add_func ("/crank/base/vec/cplx/float/n/mulrs", test_n_mulrs);
	g_test_add_func ("/crank/base/vec/cplx/float/n/divrs", test_n_divrs);
	g_test_add_func ("/crank/base/vec/cplx/float/n/add", test_n_add);
	g_test_add_func ("/crank/base/vec/cplx/float/n/sub", test_n_sub);
	g_test_add_func ("/crank/base/vec/cplx/float/n/dot", test_n_dot);
	g_test_add_func ("/crank/base/vec/cplx/float/n/cmpmul", test_n_cmpmul);
	g_test_add_func ("/crank/base/vec/cplx/float/n/cmpdiv", test_n_cmpdiv);
	g_test_add_func ("/crank/base/vec/cplx/float/n/cmpeq", test_n_cmpeq);
  	g_test_add_func ("/crank/base/vec/cplx/float/n/mulrm", test_n_mulrm);
	g_test_add_func ("/crank/base/vec/cplx/float/n/mixs", test_n_mixs);
	g_test_add_func ("/crank/base/vec/cplx/float/n/mix", test_n_mix);
	
	g_test_add_func ("/crank/base/vec/cplx/float/n/init/arruc", test_n_init_arruc);
	g_test_add_func ("/crank/base/vec/cplx/float/n/init/ucarr", test_n_init_ucarr);
	g_test_add_func ("/crank/base/vec/cplx/float/n/init/ucv", test_n_init_ucv);
	g_test_add_func ("/crank/base/vec/cplx/float/n/init/fill_uc", test_n_init_fill_uc);
	
	g_test_run ();
	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////


static gboolean
test_accumulation (	CrankCplxFloat*	value,
				   	gpointer		userdata	)
{
	CrankCplxFloat* subject = (CrankCplxFloat*) userdata;
	crank_cplx_float_add_self (subject, value);
  	return TRUE;
}





static void	test_n_get (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 3.0f, 4.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 5.0f, 12.0f);
}


static void test_n_insert (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v = {10.0f, 15.0f};

	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
  	crank_vec_cplx_float_n_insert (&a, 1, &v);

	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 3.0f, 4.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 10.0f, 15.0f);
	
	crank_vec_cplx_float_n_get (&a, 2, &v);
	crank_assert_eqcplxfloat_cimm (&v, 5.0f, 12.0f);
}


static void test_n_remove (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v;

  	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
  	crank_vec_cplx_float_n_remove (&a, 1);

	g_assert_cmpuint (crank_vec_cplx_float_n_get_size (&a), ==, 1);
  	crank_vec_cplx_float_n_get (&a, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 5.0f, 12.0f);
}


static void test_n_foreach (void)
{
	CrankVecCplxFloatN 	a = {0};
	CrankCplxFloat		sum = {0, 0};

  	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);

  	g_assert (crank_vec_cplx_float_n_foreach (&a, test_accumulation, &sum));

	crank_assert_eqcplxfloat_cimm (&sum, 8.0f, 16.0f);
}


static void	test_n_equal (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecCplxFloatN	c = {0};

	crank_vec_cplx_float_n_init_uc (&a, 2,
			g_test_rand_double (),
			g_test_rand_double (),
			g_test_rand_double (),
			g_test_rand_double ()	);
	crank_vec_cplx_float_n_init_uc (&b, 2,
			g_test_rand_double (),
			g_test_rand_double (),
			g_test_rand_double (),
			g_test_rand_double ()	);
			
	crank_vec_cplx_float_n_copy (&a, &c);
	
	g_assert (! crank_vec_cplx_float_n_equal (&a, &b));
	g_assert (  crank_vec_cplx_float_n_equal (&a, &c));
}


static void	test_n_magn (void)
{
	CrankVecCplxFloatN	a = {0};
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_assert_cmpfloat (crank_vec_cplx_float_n_get_magn_sq (&a), ==, 194.0f);
	crank_assert_cmpfloat (crank_vec_cplx_float_n_get_magn (&a), ==, 13.9284f);
}


static void	test_n_unit (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_unit (&a, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 0.2154f, 0.2872f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 0.3590f, 0.8615f);
}


static void	test_n_muls (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		b = {2.0f, 3.0f};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_muls (&a, &b, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, -6.0f, 17.0f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, -26.0f, 39.0f);
}


static void	test_n_divs (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		b = {2.0f, 3.0f};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_divs (&a, &b, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 1.3846f, -0.0769f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 3.5385f, 0.6923f);
}


static void	test_n_mulrs (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_mulrs (&a, 2.0f, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 6.0f, 8.0f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 10.0f, 24.0f);
}


static void	test_n_divrs (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_divrs (&a, 2.0f, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 1.5f, 2.0f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 2.5f, 6.0f);
}


static void	test_n_add (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_uc (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_add (&a, &b, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 5.0f, 7.0f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 10.0f, 22.0f);
}


static void	test_n_sub (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_uc (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_sub (&a, &b, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 1.0f, 1.0f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 0.0f, 2.0f);
}


static void	test_n_dot (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_uc (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_dot (&a, &b, &v);
	crank_assert_eqcplxfloat_cimm (&v, 163.0f, 9.0f);
	
}


static void	test_n_cmpmul (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_uc (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_cmpmul (&a, &b, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, -6.0f, 17.0f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, -95.0f, 110.0f);
}


static void	test_n_cmpdiv (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecCplxFloatN	r;
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_uc (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_cmpdiv (&a, &b, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 1.3846f, -0.0769f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 1.16f, 0.08f);
}
	

static void	test_n_cmpeq (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecBoolN		r = {0};
	crank_vec_cplx_float_n_init_uc (&a, 3, 2.0f, 3.0f, 4.0f, 6.0f, 17.0f, 20.0f);
	crank_vec_cplx_float_n_init_uc (&b, 3, 2.0f, 2.0f, 4.0f, 6.0f, 53.0f, 55.0f);
	
	crank_vec_cplx_float_n_cmpeq (&a, &b, &r);
	
	g_assert_false (r.data[0]);
	g_assert_true  (r.data[1]);
	g_assert_false (r.data[2]);
}


static void	test_n_mixs (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecCplxFloatN	r = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_uc (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_mixs (&a, &b, 0.2f, &r);
	
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 2.8f, 3.8f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 5.0f, 11.6f);
}


static void	test_n_mulrm (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankMatFloatN		b = {0};
	CrankVecCplxFloatN	r = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 3, 3.0f, 4.0f, 5.0f, 12.0f, 2.0f, 3.0f);
	crank_mat_float_n_init (&b, 3, 2,
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f	);

	crank_vec_cplx_float_n_mulrm (&a, &b, &r);

	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 28.0f, 55.0f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 38.0f, 74.0f);

  	crank_vec_cplx_float_n_fini (&a);
  	crank_mat_float_n_fini (&b);
  	crank_vec_cplx_float_n_fini (&r);
}


static void	test_n_mix (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecFloatN		c = {0};
	CrankVecCplxFloatN	r = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_uc (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_uc (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	crank_vec_float_n_init (&c, 2, 0.6f, 0.5f);
	
	crank_vec_cplx_float_n_mix (&a, &b, &c, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	crank_assert_eqcplxfloat_cimm (&v, 2.4f, 3.4f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	crank_assert_eqcplxfloat_cimm (&v, 5.0f, 11.0f);
}

static void
test_n_init_arruc (void)
{
	CrankVecCplxFloatN a;
	gfloat e[6] = {2.0f, 4.0f,		1.0f, 3.0f,		6.0f, 4.0f};
			
	crank_vec_cplx_float_n_init_arruc (&a, 3, e);
	
	crank_assert_eqcplxfloat_cimm (a.data + 0, 2.0f, 4.0f);
	crank_assert_eqcplxfloat_cimm (a.data + 1, 1.0f, 3.0f);
	crank_assert_eqcplxfloat_cimm (a.data + 2, 6.0f, 4.0f);
	
	crank_vec_cplx_float_n_fini (&a);
}

static void
test_n_init_ucarr (void)
{
  CrankVecCplxFloatN a;
  gfloat r[3] = {2.0f, 1.0f, 6.0f};
  gfloat i[3] = {4.0f, 3.0f, 4.0f};
  
  crank_vec_cplx_float_n_init_ucarr (&a, 3, r, i);
	
	crank_assert_eqcplxfloat_cimm (a.data + 0, 2.0f, 4.0f);
	crank_assert_eqcplxfloat_cimm (a.data + 1, 1.0f, 3.0f);
	crank_assert_eqcplxfloat_cimm (a.data + 2, 6.0f, 4.0f);
	
	crank_vec_cplx_float_n_fini (&a);
}

static void
test_n_init_ucv (void)
{
  CrankVecCplxFloatN a;
  CrankVecFloatN r;
  CrankVecFloatN i;
  
  crank_vec_float_n_init (&r, 3, 2.0f, 1.0f, 6.0f);
  crank_vec_float_n_init (&i, 3, 4.0f, 3.0f, 4.0f);
  
  crank_vec_cplx_float_n_init_ucv (&a, &r, &i);
	
	crank_assert_eqcplxfloat_cimm (a.data + 0, 2.0f, 4.0f);
	crank_assert_eqcplxfloat_cimm (a.data + 1, 1.0f, 3.0f);
	crank_assert_eqcplxfloat_cimm (a.data + 2, 6.0f, 4.0f);

  crank_vec_cplx_float_n_fini (&a);
  crank_vec_float_n_fini (&r);
  crank_vec_float_n_fini (&i);
}

static void
test_n_init_fill_uc (void)
{
  CrankVecCplxFloatN a;
  
  crank_vec_cplx_float_n_init_fill_uc (&a, 3, 2.0f, 5.0f);
	
	crank_assert_eqcplxfloat_cimm (a.data + 0, 2.0f, 5.0f);
	crank_assert_eqcplxfloat_cimm (a.data + 1, 2.0f, 5.0f);
	crank_assert_eqcplxfloat_cimm (a.data + 2, 2.0f, 5.0f);
	
	crank_vec_cplx_float_n_fini (&a);
}
