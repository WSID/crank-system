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

static void		test_assert_float_real (	const gchar*	file,
											const guint		line,
											const gchar*	func,
											const gchar*	a_str,
											const gchar*	b_str,
											gfloat			a,
											gfloat			b	);

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
	
	g_test_run ();
	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static void
test_assert_float_real (	const gchar*	file,
							const guint		line,
							const gchar*	func,
							const gchar*	a_str,
							const gchar*	b_str,
							gfloat			a,
							gfloat			b)
{
	if ((a < b - 0.0001f) || (b + 0.0001f < a)) {
		g_warning (
				"%s:%u:%s: assertion failed: (%s == %s): (%g == %g)"
				" (with diff of %g)",
				file, line, func,
				a_str, b_str,
				a, b, b - a );
	}
}

#define test_assert_float(a, b) \
	test_assert_float_real(\
			__FILE__, \
			__LINE__, \
			G_STRFUNC, \
			G_STRINGIFY(a), \
			G_STRINGIFY(b), \
			a, \
			b)


static gboolean
test_accumulation (	CrankCplxFloat*	value,
				   	gpointer		userdata	)
{
	CrankCplxFloat* subject = (CrankCplxFloat*) userdata;
	crank_cplx_float_add (value, subject, subject);
  	return TRUE;
}





static void	test_n_get (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 3.0f);
	test_assert_float (v.imag, 4.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 5.0f);
	test_assert_float (v.imag, 12.0f);
}


static void test_n_insert (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v = {10.0f, 15.0f};

	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
  	crank_vec_cplx_float_n_insert (&a, 1, &v);

	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 3.0f);
	test_assert_float (v.imag, 4.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 10.0f);
	test_assert_float (v.imag, 15.0f);
	
	crank_vec_cplx_float_n_get (&a, 2, &v);
	test_assert_float (v.real, 5.0f);
	test_assert_float (v.imag, 12.0f);
}


static void test_n_remove (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v;

  	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
  	crank_vec_cplx_float_n_remove (&a, 1);

	g_assert_cmpuint (crank_vec_cplx_float_n_get_size (&a), ==, 1);
  	crank_vec_cplx_float_n_get (&a, 0, &v);
  	test_assert_float (v.real, 5.0f);
  	test_assert_float (v.imag, 12.0f);
}


static void test_n_foreach (void)
{
	CrankVecCplxFloatN 	a = {0};
	CrankCplxFloat		sum = {0, 0};

  	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);

  	g_assert (crank_vec_cplx_float_n_foreach (&a, test_accumulation, &sum));

  	test_assert_float (sum.real, 8.0f);
  	test_assert_float (sum.imag, 16.0f);
}


static void	test_n_equal (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecCplxFloatN	c = {0};

	crank_vec_cplx_float_n_init_imm (&a, 2,
			g_test_rand_double (),
			g_test_rand_double (),
			g_test_rand_double (),
			g_test_rand_double ()	);
	crank_vec_cplx_float_n_init_imm (&b, 2,
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
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	test_assert_float (crank_vec_cplx_float_n_get_magn_sq (&a), 194.0f);
	test_assert_float (crank_vec_cplx_float_n_get_magn (&a), 13.9284f);
}


static void	test_n_unit (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_unit (&a, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 0.2154f);
	test_assert_float (v.imag, 0.2872f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 0.3590f);
	test_assert_float (v.imag, 0.8615f);
}


static void	test_n_muls (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		b = {2.0f, 3.0f};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_muls (&a, &b, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, -6.0f);
	test_assert_float (v.imag, 17.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, -26.0f);
	test_assert_float (v.imag, 39.0f);
}


static void	test_n_divs (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		b = {2.0f, 3.0f};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_divs (&a, &b, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 1.3846f);
	test_assert_float (v.imag, -0.0769f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 3.5385f);
	test_assert_float (v.imag, 0.6923f);
}


static void	test_n_mulrs (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_mulrs (&a, 2.0f, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 6.0f);
	test_assert_float (v.imag, 8.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 10.0f);
	test_assert_float (v.imag, 24.0f);
}


static void	test_n_divrs (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	crank_vec_cplx_float_n_divrs (&a, 2.0f, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 1.5f);
	test_assert_float (v.imag, 2.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 2.5f);
	test_assert_float (v.imag, 6.0f);
}


static void	test_n_add (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_imm (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_add (&a, &b, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 5.0f);
	test_assert_float (v.imag, 7.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 10.0f);
	test_assert_float (v.imag, 22.0f);
}


static void	test_n_sub (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_imm (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_sub (&a, &b, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 1.0f);
	test_assert_float (v.imag, 1.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 0.0f);
	test_assert_float (v.imag, 2.0f);
}


static void	test_n_dot (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_imm (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_dot (&a, &b, &v);
	test_assert_float (v.real, 163.0f);
	test_assert_float (v.imag, 9.0f);
	
}


static void	test_n_cmpmul (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_imm (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_cmpmul (&a, &b, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, -6.0f);
	test_assert_float (v.imag, 17.0f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, -95.0f);
	test_assert_float (v.imag, 110.0f);
}


static void	test_n_cmpdiv (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_imm (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_cmpdiv (&a, &b, &a);
	
	crank_vec_cplx_float_n_get (&a, 0, &v);
	test_assert_float (v.real, 1.3846f);
	test_assert_float (v.imag, -0.0769f);
	
	crank_vec_cplx_float_n_get (&a, 1, &v);
	test_assert_float (v.real, 1.16f);
	test_assert_float (v.imag, 0.08f);
}
	

static void	test_n_cmpeq (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecBoolN	r = {0};
	crank_vec_cplx_float_n_init_imm (&a, 3, 2.0f, 3.0f, 4.0f, 6.0f, 17.0f, 20.0f);
	crank_vec_cplx_float_n_init_imm (&b, 3, 2.0f, 2.0f, 4.0f, 6.0f, 53.0f, 55.0f);
	
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
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_imm (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	crank_vec_cplx_float_n_mixs (&a, &b, 0.2f, &r);
	
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	test_assert_float (v.real, 2.8f);
	test_assert_float (v.imag, 3.8f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	test_assert_float (v.real, 5.0f);
	test_assert_float (v.imag, 11.6f);
}


static void	test_n_mulrm (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankMatFloatN	b = {0};
	CrankVecCplxFloatN	r = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 3, 3.0f, 4.0f, 5.0f, 12.0f, 2.0f, 3.0f);
	crank_mat_float_n_init (&b, 3, 2,
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f	);

	crank_vec_cplx_float_n_mulrm (&a, &b, &r);

	crank_vec_cplx_float_n_get (&r, 0, &v);
	test_assert_float (v.real, 28.0f);
	test_assert_float (v.imag, 55.0f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	test_assert_float (v.real, 38.0f);
	test_assert_float (v.imag, 74.0f);

  	crank_vec_cplx_float_n_fini (&a);
  	crank_mat_float_n_fini (&b);
  	crank_vec_cplx_float_n_fini (&r);
}


static void	test_n_mix (void)
{
	CrankVecCplxFloatN	a = {0};
	CrankVecCplxFloatN	b = {0};
	CrankVecFloatN	c = {0};
	CrankVecCplxFloatN	r = {0};
	CrankCplxFloat		v;
	crank_vec_cplx_float_n_init_imm (&a, 2, 3.0f, 4.0f, 5.0f, 12.0f);
	crank_vec_cplx_float_n_init_imm (&b, 2, 2.0f, 3.0f, 5.0f, 10.0f);
	crank_vec_float_n_init (&c, 2, 0.6f, 0.5f);
	
	crank_vec_cplx_float_n_mix (&a, &b, &c, &r);
	
	crank_vec_cplx_float_n_get (&r, 0, &v);
	test_assert_float (v.real, 2.4f);
	test_assert_float (v.imag, 3.4f);
	
	crank_vec_cplx_float_n_get (&r, 1, &v);
	test_assert_float (v.real, 5.0f);
	test_assert_float (v.imag, 11.0f);
}

