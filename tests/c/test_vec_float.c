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

void	test_assert_float_real (	const gchar*	file,
								const guint		line,
								const gchar*	func,
								const gchar*	a_str,
								const gchar*	b_str,
								gfloat			a,
								gfloat			b)
{
	if ((a < b - 0.0001f) || (b + 0.0001f < a)) {
		g_printerr ("%s:%u:%s: assertion failed: (%s == %s): (%g == %g) (with diff of %g)",
				file, line, func,
				a_str, b_str,
				a, b, b - a );
	}
}

#define test_assert_float(a, b) \
	test_assert_float_real(__FILE__, __LINE__, G_STRFUNC, \
			G_STRINGIFY(a), G_STRINGIFY(b), \
			a, b)






void	test_2_get (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	
	test_assert_float (crank_vec_float2_get (&a, 0), 3.0f);
	test_assert_float (crank_vec_float2_get (&a, 1), 4.0f);
}


void	test_2_equal (void)
{
	CrankVecFloat2	a = {(gfloat) g_test_rand_double (), (gfloat) g_test_rand_double ()};
	CrankVecFloat2	b = {(gfloat) g_test_rand_double (), (gfloat) g_test_rand_double ()};
	CrankVecFloat2	c = {a.x, a.y};
	
	g_assert (! crank_vec_float2_equal (&a, &b));
	g_assert (  crank_vec_float2_equal (&a, &c));
}


void	test_2_to_string (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	gchar*			astr = crank_vec_float2_to_string (&a);
	
	g_assert_cmpstr (astr, ==, "(3, 4)");
}


void	test_2_magn (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	
	test_assert_float (crank_vec_float2_get_magn_sq (&a), 25.0f);
	test_assert_float (crank_vec_float2_get_magn (&a), 5.0f);
}


void	test_2_unit (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	
	crank_vec_float2_unit (&a, &a);
	
	test_assert_float (a.x, 0.6f);
	test_assert_float (a.y, 0.8f);
}


void	test_2_muls (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	
	crank_vec_float2_muls (&a, 2.0f, &a);
	
	test_assert_float (a.x, 6.0f);
	test_assert_float (a.y, 8.0f);
}


void	test_2_divs (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	
	crank_vec_float2_divs (&a, 2.0f, &a);
	
	test_assert_float (a.x, 1.5f);
	test_assert_float (a.y, 2.0f);
}


void	test_2_add (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	
	crank_vec_float2_add (&a, &b, &a);
	
	test_assert_float (a.x, 8.0f);
	test_assert_float (a.y, 16.0f);
}


void	test_2_sub (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	
	crank_vec_float2_sub (&a, &b, &a);
	
	test_assert_float (a.x, -2.0f);
	test_assert_float (a.y, -8.0f);
}


void	test_2_dot (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	
	test_assert_float (crank_vec_float2_dot (&a, &b), 63.0f);
}


void	test_2_cmpmul (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	
	crank_vec_float2_cmpmul (&a, &b, &a);
	
	test_assert_float (a.x, 15.0f);
	test_assert_float (a.y, 48.0f);
}


void	test_2_cmpdiv (void)
{
	CrankVecFloat2	a = {3.0f, 4.0f};
	CrankVecFloat2	b = {5.0f, 12.0f};
	
	crank_vec_float2_cmpdiv (&b, &a, &b);
	
	test_assert_float (b.x, (5.0f / 3.0f));
	test_assert_float (b.y, 3.0f);
}


void	test_2_cmpless (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecBool2	r;
	
	crank_vec_float2_cmpless (&a, &b, &r);
	
	g_assert_true  (r.x);
	g_assert_false (r.y);
}
	

void	test_2_cmpeq (void)
{
	CrankVecFloat2	a = {17.0f, 20.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecBool2	r;
	
	crank_vec_float2_cmpeq (&a, &b, &r);
	
	g_assert_false (r.x);
	g_assert_true  (r.y);
}


void	test_2_cmpgreater (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecBool2	r;
	
	crank_vec_float2_cmpgreater (&a, &b, &r);
	
	g_assert_false (r.x);
	g_assert_true  (r.y);
}


void	test_2_cmpcmp (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecInt2	r;
	
	crank_vec_float2_cmpcmp (&a, &b, &r);
	
	g_assert_cmpint (r.x, <, 0);
	g_assert_cmpint (r.y, >, 0);
}


void	test_2_min (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_min (&a, &b, &r);
	
	test_assert_float (r.x, 17.0f);
	test_assert_float (r.y, 20.0f);
}


void	test_2_max (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {53.0f, 20.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_max (&a, &b, &r);
	
	test_assert_float (r.x, 53.0f);
	test_assert_float (r.y, 21.0f);
}


void	test_2_mixs (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {32.0f, 11.0f};
	CrankVecFloat2	r;
	
	crank_vec_float2_mixs (&a, &b, 0.2f, &r);
	
	test_assert_float (r.x, 20.0f);
	test_assert_float (r.y, 19.0f);
}


void	test_2_mix (void)
{
	CrankVecFloat2	a = {17.0f, 21.0f};
	CrankVecFloat2	b = {32.0f, 11.0f};
	CrankVecFloat2	c = {0.6f, 0.5f};
	CrankVecFloat2	r;
	
	crank_vec_float2_mix (&a, &b, &c, &r);
	
	test_assert_float (r.x, 26.0f);
	test_assert_float (r.y, 16.0f);
}





void	test_n_get (void)
{
	CrankVecFloatN	a = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	test_assert_float (crank_vec_float_n_get (&a, 0), 3.0f);
	test_assert_float (crank_vec_float_n_get (&a, 1), 4.0f);
}


void	test_n_equal (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	CrankVecFloatN	c = {0};

	crank_vec_float_n_init (&a, 2,
			g_test_rand_double (),
			g_test_rand_double ()	);
	crank_vec_float_n_init (&b, 2,
			g_test_rand_double (),
			g_test_rand_double ()	);
	crank_vec_float_n_init_arr (&c, a.n, a.data);
	
	g_assert (! crank_vec_float_n_equal (&a, &b));
	g_assert (  crank_vec_float_n_equal (&a, &c));
}


void	test_n_to_string (void)
{
	CrankVecFloatN	a = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	gchar*			astr = crank_vec_float_n_to_string (&a);
	
	g_assert_cmpstr (astr, ==, "(3, 4)");
}


void	test_n_magn (void)
{
	CrankVecFloatN	a = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	test_assert_float (crank_vec_float_n_get_magn_sq (&a), 25.0f);
	test_assert_float (crank_vec_float_n_get_magn (&a), 5.0f);
}


void	test_n_unit (void)
{
	CrankVecFloatN	a = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	crank_vec_float_n_unit (&a, &a);
	
	test_assert_float (a.data[0], 0.6f);
	test_assert_float (a.data[1], 0.8f);
}


void	test_n_muls (void)
{
	CrankVecFloatN	a = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	crank_vec_float_n_muls (&a, 2.0f, &a);
	
	test_assert_float (a.data[0], 6.0f);
	test_assert_float (a.data[1], 8.0f);
}


void	test_n_divs (void)
{
	CrankVecFloatN	a = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	
	crank_vec_float_n_divs (&a, 2.0f, &a);
	
	test_assert_float (a.data[0], 1.5f);
	test_assert_float (a.data[1], 2.0f);
}


void	test_n_add (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_vec_float_n_add (&a, &b, &a);
	
	test_assert_float (a.data[0], 8.0f);
	test_assert_float (a.data[1], 16.0f);
}


void	test_n_sub (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_vec_float_n_sub (&a, &b, &a);
	
	test_assert_float (a.data[0], -2.0f);
	test_assert_float (a.data[1], -8.0f);
}


void	test_n_dot (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	test_assert_float (crank_vec_float_n_dot (&a, &b), 63.0f);
}


void	test_n_cmpmul (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_vec_float_n_cmpmul (&a, &b, &a);
	
	test_assert_float (a.data[0], 15.0f);
	test_assert_float (a.data[1], 48.0f);
}


void	test_n_cmpdiv (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 3.0f, 4.0f);
	crank_vec_float_n_init (&b, 2, 5.0f, 12.0f);
	
	crank_vec_float_n_cmpdiv (&b, &a, &b);
	
	test_assert_float (b.data[0], (5.0f / 3.0f));
	test_assert_float (b.data[1], 3.0f);
}


void	test_n_cmpless (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecBoolN	r = {0};
	
	crank_vec_float_n_cmpless (&a, &b, &r);
	
	g_assert_true  (r.data[0]);
	g_assert_false (r.data[1]);
}
	

void	test_n_cmpeq (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 17.0f, 20.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecBoolN	r = {0};
	
	crank_vec_float_n_cmpeq (&a, &b, &r);
	
	g_assert_false (r.data[0]);
	g_assert_true  (r.data[1]);
}


void	test_n_cmpgreater (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecBoolN	r = {0};
	
	crank_vec_float_n_cmpgreater (&a, &b, &r);
	
	g_assert_false (r.data[0]);
	g_assert_true  (r.data[1]);
}


void	test_n_cmpcmp (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecIntN	r = {0};
	
	crank_vec_float_n_cmpcmp (&a, &b, &r);
	
	g_assert_cmpint (r.data[0], <, 0);
	g_assert_cmpint (r.data[1], >, 0);
}


void	test_n_min (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecFloatN	r = {0};
	
	crank_vec_float_n_min (&a, &b, &r);
	
	test_assert_float (r.data[0], 17.0f);
	test_assert_float (r.data[1], 20.0f);
}


void	test_n_max (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 53.0f, 20.0f);
	CrankVecFloatN	r = {0};
	
	crank_vec_float_n_max (&a, &b, &r);
	
	test_assert_float (r.data[0], 53.0f);
	test_assert_float (r.data[1], 21.0f);
}


void	test_n_mixs (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 32.0f, 11.0f);
	CrankVecFloatN	r = {0};
	
	crank_vec_float_n_mixs (&a, &b, 0.2f, &r);
	
	test_assert_float (r.data[0], 20.0f);
	test_assert_float (r.data[1], 19.0f);
}


void	test_n_mix (void)
{
	CrankVecFloatN	a = {0};
	CrankVecFloatN	b = {0};
	CrankVecFloatN	c = {0};
	crank_vec_float_n_init (&a, 2, 17.0f, 21.0f);
	crank_vec_float_n_init (&b, 2, 32.0f, 11.0f);
	crank_vec_float_n_init (&c, 2, 0.6f, 0.5f);
	CrankVecFloatN	r = {0};
	
	crank_vec_float_n_mix (&a, &b, &c, &r);
	
	test_assert_float (r.data[0], 26.0f);
	test_assert_float (r.data[1], 16.0f);
}



void	main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/vec/float/2/get", test_2_get);
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
	g_test_add_func ("/crank/base/vec/float/2/mixs", test_2_mixs);
	g_test_add_func ("/crank/base/vec/float/2/mix", test_2_mix);
	
	g_test_add_func ("/crank/base/vec/float/n/get", test_n_get);
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
	g_test_add_func ("/crank/base/vec/float/n/mixs", test_n_mixs);
	g_test_add_func ("/crank/base/vec/float/n/mix", test_n_mix);
	
	g_test_run ();
}
