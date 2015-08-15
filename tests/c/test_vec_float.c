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

static gboolean	test_accumulation (			const gfloat	value,
							   				gpointer		userdata	);

static void	test_2_get (void);
static void test_2_foreach (void);
static void	test_2_equal (void);
static void	test_2_to_string (void);
static void	test_2_magn (void);
static void	test_2_muls (void);
static void	test_2_divs (void);
static void	test_2_add (void);
static void	test_2_sub (void);
static void	test_2_dot (void);
static void	test_2_cmpmul (void);
static void	test_2_cmpdiv (void);
static void	test_2_cmpmod (void);
static void	test_2_cmpless (void);
static void	test_2_cmpeq (void);
static void	test_2_cmpgreater (void);
static void	test_2_cmpcmp (void);
static void	test_2_min (void);
static void	test_2_max (void);
static void	test_2_mulm (void);
static void	test_2_mixs (void);
static void	test_2_mix (void);

static void	test_n_get (void);
static void	test_n_insert (void);
static void test_n_remove (void);
static void	test_n_foreach (void);
static void	test_n_equal (void);
static void	test_n_to_string (void);
static void	test_n_magn (void);
static void	test_n_muls (void);
static void	test_n_divs (void);
static void	test_n_add (void);
static void	test_n_sub (void);
static void	test_n_dot (void);
static void	test_n_cmpmul (void);
static void	test_n_cmpdiv (void);
static void	test_n_cmpmod (void);
static void	test_n_cmpless (void);
static void	test_n_cmpeq (void);
static void	test_n_cmpgreater (void);
static void	test_n_cmpcmp (void);
static void	test_n_min (void);
static void	test_n_max (void);
static void	test_n_mulm (void);
static void	test_n_mixs (void);
static void	test_n_mix (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (	gint argc, gchar** argv	)
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/vec/float/2/get", test_2_get);
	g_test_add_func ("/crank/base/vec/float/2/foreach", test_2_foreach);
	g_test_add_func ("/crank/base/vec/float/2/equal", test_2_equal);
	g_test_add_func ("/crank/base/vec/float/2/to_string", test_2_to_string);
	g_test_add_func ("/crank/base/vec/float/2/magn", test_2_magn);
	g_test_add_func ("/crank/base/vec/float/2/muls", test_2_muls);
	g_test_add_func ("/crank/base/vec/float/2/divs", test_2_divs);
	g_test_add_func ("/crank/base/vec/float/2/add", test_2_add);
	g_test_add_func ("/crank/base/vec/float/2/sub", test_2_sub);
	g_test_add_func ("/crank/base/vec/float/2/dot", test_2_dot);
	g_test_add_func ("/crank/base/vec/float/2/cmpmul", test_2_cmpmul);
	g_test_add_func ("/crank/base/vec/float/2/cmpdiv", test_2_cmpdiv);
	g_test_add_func ("/crank/base/vec/float/2/cmpless", test_2_cmpless);
	g_test_add_func ("/crank/base/vec/float/2/cmpeq", test_2_cmpeq);
	g_test_add_func ("/crank/base/vec/float/2/cmpgreater", test_2_cmpgreater);
	g_test_add_func ("/crank/base/vec/float/2/cmpcmp", test_2_cmpcmp);
	g_test_add_func ("/crank/base/vec/float/2/min", test_2_min);
	g_test_add_func ("/crank/base/vec/float/2/max", test_2_max);
  	g_test_add_func ("/crank/base/vec/float/2/mulm", test_2_mulm);
	g_test_add_func ("/crank/base/vec/float/2/mixs", test_2_mixs);
	g_test_add_func ("/crank/base/vec/float/2/mix", test_2_mix);
	
	g_test_add_func ("/crank/base/vec/float/n/get", test_n_get);
  	g_test_add_func ("/crank/base/vec/float/n/insert", test_n_insert);
	g_test_add_func ("/crank/base/vec/float/n/foreach", test_n_foreach);
	g_test_add_func ("/crank/base/vec/float/n/equal", test_n_equal);
	g_test_add_func ("/crank/base/vec/float/n/to_string", test_n_to_string);
	g_test_add_func ("/crank/base/vec/float/n/magn", test_n_magn);
	g_test_add_func ("/crank/base/vec/float/n/muls", test_n_muls);
	g_test_add_func ("/crank/base/vec/float/n/divs", test_n_divs);
	g_test_add_func ("/crank/base/vec/float/n/add", test_n_add);
	g_test_add_func ("/crank/base/vec/float/n/sub", test_n_sub);
	g_test_add_func ("/crank/base/vec/float/n/dot", test_n_dot);
	g_test_add_func ("/crank/base/vec/float/n/cmpmul", test_n_cmpmul);
	g_test_add_func ("/crank/base/vec/float/n/cmpdiv", test_n_cmpdiv);
	g_test_add_func ("/crank/base/vec/float/n/cmpless", test_n_cmpless);
	g_test_add_func ("/crank/base/vec/float/n/cmpeq", test_n_cmpeq);
	g_test_add_func ("/crank/base/vec/float/n/cmpgreater", test_n_cmpgreater);
	g_test_add_func ("/crank/base/vec/float/n/cmpcmp", test_n_cmpcmp);
	g_test_add_func ("/crank/base/vec/float/n/min", test_n_min);
	g_test_add_func ("/crank/base/vec/float/n/max", test_n_max);
  	g_test_add_func ("/crank/base/vec/float/n/mulm", test_n_mulm);
	g_test_add_func ("/crank/base/vec/float/n/mixs", test_n_mixs);
	g_test_add_func ("/crank/base/vec/float/n/mix", test_n_mix);
	
	g_test_run ();
	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////




static gboolean
test_accumulation (	const gfloat	value,
				   	gpointer		userdata	)
{
	gfloat*	sum	=	(gfloat*)userdata;

	(*sum) += value;
  	return TRUE;
}





static void	test_2_get (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	
	crank_assert_cmpfloat (crank_vec_float2_get (&a, 0), ==, 3.0f);
	crank_assert_cmpfloat (crank_vec_float2_get (&a, 1), ==, 4.0f);
}

static void test_2_foreach (void)
{
	CrankVecFloat2 	a = {3.0f, 4.0f};
  	gfloat			sum = 0.0f;

  	g_assert (crank_vec_float2_foreach (&a, test_accumulation, &sum));

  	crank_assert_cmpfloat (sum, ==, 7.0f);
}


static void	test_2_equal (void)
{
	CrankVecFloat2	a = {(gfloat) g_test_rand_double (), (gfloat) g_test_rand_double ()};
	CrankVecFloat2	b = {(gfloat) g_test_rand_double (), (gfloat) g_test_rand_double ()};
	CrankVecFloat2	c = {a.x, a.y};
	
	g_assert (! crank_vec_float2_equal (&a, &b));
	g_assert (  crank_vec_float2_equal (&a, &c));
}


static void	test_2_to_string (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	gchar*			astr = crank_vec_float2_to_string (&a);
	
	g_assert_cmpstr (astr, ==, "(3, 4)");
}


static void	test_2_magn (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	
	crank_assert_cmpfloat (crank_vec_float2_get_magn_sq (&a), ==, 25.0f);
	crank_assert_cmpfloat (crank_vec_float2_get_magn (&a), ==, 5.0f);
}


static void	test_2_unit (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_unit (&a, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 0.6f, 0.8f);
}


static void	test_2_muls (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_muls (&a, 2.0f, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 6.0f, 8.0f);
}


static void	test_2_divs (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_divs (&a, 2.0f, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 1.5f, 2.0f);
}


static void	test_2_add (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_add (&a, &b, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 8.0f, 16.0f);
}


static void	test_2_sub (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_sub (&a, &b, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, -2.0f, -8.0f);
}


static void	test_2_dot (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	
	crank_assert_cmpfloat (crank_vec_float2_dot (&a, &b), ==, 63.0f);
}


static void	test_2_cmpmul (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_cmpmul (&a, &b, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 15.0f, 48.0f);
}


static void	test_2_cmpdiv (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_cmpdiv (&b, &a, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, (5.0f / 3.0f), 3.0f);
}


static void	test_2_cmpless (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecBool2	r;
	
	crank_vec_float2_cmpless (&a, &b, &r);
	
	g_assert_true  (r.x);
	g_assert_false (r.y);
}
	

static void	test_2_cmpeq (void)
{
	CrankVecFloat2	a = {17.0f, 20.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecBool2	r;
	
	crank_vec_float2_cmpeq (&a, &b, &r);
	
	g_assert_false (r.x);
	g_assert_true  (r.y);
}


static void	test_2_cmpgreater (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecBool2	r;
	
	crank_vec_float2_cmpgreater (&a, &b, &r);
	
	g_assert_false (r.x);
	g_assert_true  (r.y);
}


static void	test_2_cmpcmp (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecInt2	r;
	
	crank_vec_float2_cmpcmp (&a, &b, &r);
	
	g_assert_cmpint (r.x, <, 0);
	g_assert_cmpint (r.y, >, 0);
}


static void	test_2_min (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_min (&a, &b, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 17.0f, 20.0f);
}


static void	test_2_max (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_max (&a, &b, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 53.0f, 21.0f);
}


static void test_2_mulm (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
  	CrankMatFloat2	b = {1.0f, 2.0f,	3.0f, 4.0f};
	CrankVecFloat2	r;

  	crank_vec_float2_mulm (&a, &b, &r);

	crank_assert_eq_vecfloat2_imm (&r, 15.0f, 22.0f);
}


static void	test_2_mixs (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {32.0f, 11.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_mixs (&a, &b, 0.2f, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 20.0f, 19.0f);
}


static void	test_2_mix (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {32.0f, 11.0f};
	CrankVecFloat2	c = {0.6f, 0.5f};
	CrankVecFloat2	r;
	
	crank_vec_float2_mix (&a, &b, &c, &r);
	
	crank_assert_eq_vecfloat2_imm (&r, 26.0f, 16.0f);
}





static void	test_n_get (void)
{
	CrankVecFloatN	a;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	crank_assert_cmpfloat (crank_vec_float_n_get (&a, 0), ==, 3.0f);
	crank_assert_cmpfloat (crank_vec_float_n_get (&a, 1), ==, 4.0f);

	crank_vec_float_n_fini (&a);
}


static void test_n_insert (void)
{
	CrankVecFloatN	a;

  	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
  	crank_vec_float_n_insert (&a, 1, 12.0f);

	crank_assert_eq_vecfloat_n_imm (&a, 3.0f, 12.0f, 4.0f);

	crank_vec_float_n_fini (&a);
}


static void test_n_remove (void)
{
	CrankVecFloatN	a;

  	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
  	crank_vec_float_n_remove (&a, 1);

	crank_assert_eq_vecfloat_n_imm (&a, 3.0f);

	crank_vec_float_n_fini (&a);
}


static void test_n_foreach (void)
{
	CrankVecFloatN 	a;
  	gfloat			sum = 0.0f;

  	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);

  	g_assert (crank_vec_float_n_foreach (&a, test_accumulation, &sum));

  	crank_assert_cmpfloat (sum, ==, 7.0f);

	crank_vec_float_n_fini (&a);
}


static void	test_n_equal (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	CrankVecFloatN	c;

	crank_vec_float_n_init (&a, 2,
			g_test_rand_double (),
			g_test_rand_double ()	);
	crank_vec_float_n_init (&b, 2,
			g_test_rand_double (),
			g_test_rand_double ()	);
	crank_vec_float_n_init_arr (&c, a.n, a.data);
	
	g_assert (! crank_vec_float_n_equal (&a, &b));
	g_assert (  crank_vec_float_n_equal (&a, &c));
	
	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&c);
}


static void	test_n_to_string (void)
{
	CrankVecFloatN	a;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	gchar*			astr = crank_vec_float_n_to_string (&a);
	
	g_assert_cmpstr (astr, ==, "(3, 4)");

	crank_vec_float_n_fini (&a);
}


static void	test_n_magn (void)
{
	CrankVecFloatN	a;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	crank_assert_cmpfloat (crank_vec_float_n_get_magn_sq (&a), ==, 25.0f);
	crank_assert_cmpfloat (crank_vec_float_n_get_magn (&a), ==, 5.0f);

	crank_vec_float_n_fini (&a);
}


static void	test_n_unit (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	r;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	crank_vec_float_n_unit (&a, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, 0.6f, 0.8f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&r);
}


static void	test_n_muls (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	r;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	crank_vec_float_n_muls (&a, 2.0f, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, 6.0f, 8.0f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&r);
}


static void	test_n_divs (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	r;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	crank_vec_float_n_divs (&a, 2.0f, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, 1.5f, 2.0f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&r);
}


static void	test_n_add (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	CrankVecFloatN	r;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_vec_float_n_add (&a, &b, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, 8.0f, 16.0f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&r);
}


static void	test_n_sub (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	CrankVecFloatN	r;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_vec_float_n_sub (&a, &b, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, -2.0f, -8.0f);
	
	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&r);
}


static void	test_n_dot (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_assert_cmpfloat (crank_vec_float_n_dot (&a, &b), ==, 63.0f);
	
	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
}


static void	test_n_cmpmul (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	CrankVecFloatN	r;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_vec_float_n_cmpmul (&a, &b, &r);
	
	crank_assert_eq_vecfloat_n_imm (&r, 15.0f, 48.0f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&r);
}


static void	test_n_cmpdiv (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	CrankVecFloatN	r;
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_vec_float_n_cmpdiv (&b, &a, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, (5.0f / 3.0f), 3.0f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&r);
}


static void	test_n_cmpless (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecBoolN	r;
	
	crank_vec_float_n_cmpless (&a, &b, &r);
	
	g_assert_true  (r.data[0]);
	g_assert_false (r.data[1]);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_bool_n_fini (&r);
}
	

static void	test_n_cmpeq (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	crank_vec_float_n_init (&a, 2, 17.0f, 20.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecBoolN	r;
	
	crank_vec_float_n_cmpeq (&a, &b, &r);
	
	g_assert_false (r.data[0]);
	g_assert_true  (r.data[1]);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_bool_n_fini (&r);
}


static void	test_n_cmpgreater (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecBoolN	r;
	
	crank_vec_float_n_cmpgreater (&a, &b, &r);
	
	g_assert_false (r.data[0]);
	g_assert_true  (r.data[1]);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_bool_n_fini (&r);
}


static void	test_n_cmpcmp (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecIntN	r;
	
	crank_vec_float_n_cmpcmp (&a, &b, &r);
	
	g_assert_cmpint (r.data[0], <, 0);
	g_assert_cmpint (r.data[1], >, 0);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_int_n_fini (&r);
}


static void	test_n_min (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecFloatN	r;
	
	crank_vec_float_n_min (&a, &b, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, 17.0f, 20.0f);
	
	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&r);
}


static void	test_n_max (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecFloatN	r;
	
	crank_vec_float_n_max (&a, &b, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, 53.0f, 21.0f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&r);
}


static void	test_n_mixs (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 32.0f, 11.0f);
	CrankVecFloatN	r;
	
	crank_vec_float_n_mixs (&a, &b, 0.2f, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, 20.0f, 19.0f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&r);
}


static void	test_n_mulm (void)
{
	CrankVecFloatN	a;
	CrankMatFloatN	b = {0};
	CrankVecFloatN	r;
	crank_vec_float_n_init (&a, 3, 2.0f, 5.0f, 7.0f);
	crank_mat_float_n_init (&b, 3, 2,
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f	);

	crank_vec_float_n_mulm (&a, &b, &r);

	crank_assert_eq_vecfloat_n_imm(&r, 52.0f, 66.0f);

  	crank_vec_float_n_fini (&a);
  	crank_mat_float_n_fini (&b);
  	crank_vec_float_n_fini (&r);
}


static void	test_n_mix (void)
{
	CrankVecFloatN	a;
	CrankVecFloatN	b;
	CrankVecFloatN	c;
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 32.0f, 11.0f);
	crank_vec_float_n_init (&c, 2, 0.6f, 0.5f);
	CrankVecFloatN	r;
	
	crank_vec_float_n_mix (&a, &b, &c, &r);
	
	crank_assert_eq_vecfloat_n_imm(&r, 26.0f, 16.0f);

	crank_vec_float_n_fini (&a);
	crank_vec_float_n_fini (&b);
	crank_vec_float_n_fini (&c);
	crank_vec_float_n_fini (&r);
}

