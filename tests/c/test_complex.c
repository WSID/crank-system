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

static void		test_equal ( void );

static void		test_get_norm ( void );

static void		test_neg ( void );

static void		test_inverse ( void );

static void		test_conjugate ( void );

static void		test_unit ( void );

static void		test_addr ( void );

static void		test_subr ( void );

static void		test_mulr ( void );

static void		test_divr ( void );

static void		test_rsubr ( void );

static void		test_rdivr ( void );

static void		test_add ( void );

static void		test_sub ( void );

static void 	test_mul ( void );

static void		test_div ( void );

static void		test_mul_conj ( void );

static void		test_mix ( void );

static void		test_ln ( void );

static void		test_exp ( void );

//////// Main //////////////////////////////////////////////////////////////////

gint
main (	gint   argc,
      	gchar *argv[] )
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/crank/base/cplx/float/equal",		test_equal		);
	g_test_add_func ("/crank/base/cplx/float/get_norm",		test_get_norm	);
	g_test_add_func ("/crank/base/cplx/float/neg",			test_neg		);
	g_test_add_func ("/crank/base/cplx/float/inverse",		test_inverse	);
	g_test_add_func ("/crank/base/cplx/float/conjugate",	test_conjugate	);
	g_test_add_func ("/crank/base/cplx/float/unit",			test_unit		);
	g_test_add_func ("/crank/base/cplx/float/addr",			test_addr		);
	g_test_add_func ("/crank/base/cplx/float/subr",			test_subr		);
	g_test_add_func ("/crank/base/cplx/float/mulr",			test_mulr		);
	g_test_add_func ("/crank/base/cplx/float/divr",			test_divr		);
	g_test_add_func ("/crank/base/cplx/float/rsubr",		test_rsubr		);
	g_test_add_func ("/crank/base/cplx/float/rdivr",		test_rdivr		);
	g_test_add_func ("/crank/base/cplx/float/add",			test_add		);
	g_test_add_func ("/crank/base/cplx/float/sub",			test_sub		);
	g_test_add_func ("/crank/base/cplx/float/mul",			test_mul		);
	g_test_add_func ("/crank/base/cplx/float/div",			test_div		);
	g_test_add_func ("/crank/base/cplx/float/mul_conj",		test_mul_conj	);
	g_test_add_func ("/crank/base/cplx/float/mix",			test_mix		);
	g_test_add_func ("/crank/base/cplx/float/ln",			test_ln			);
	g_test_add_func ("/crank/base/cplx/float/exp",			test_exp		);
	
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
		g_error (
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



static void
test_equal ( void )
{
	CrankCplxFloat	a = {3.0f, 4.0f};
	CrankCplxFloat	b = {3.0f, 4.0f};
	CrankCplxFloat	c = {4.0f, 3.0f};
	
	g_assert (crank_cplx_float_equal (&a, &b));
	g_assert (! crank_cplx_float_equal (&a, &c));
}

static void
test_get_norm ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	test_assert_float (crank_cplx_float_get_norm (&cplx), 5.0f);
}

static void
test_neg ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_neg (&cplx, &cplx);
	
	test_assert_float (cplx.real, -3.0f);
	test_assert_float (cplx.imag, -4.0f);
}

static void
test_inverse ( void )
{
	// (3 + 4i) (0.12 - 0.16i) =
	//	0.36 + 0.48i - 0.48i + 0.64 =
	//	1
	
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_inverse (&cplx, &cplx);
	
	test_assert_float (cplx.real, 0.12f);
	test_assert_float (cplx.imag, -0.16f);
}

static void
test_conjugate ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_conjugate (&cplx, &cplx);
	
	test_assert_float (cplx.real, 3.0f);
	test_assert_float (cplx.imag, -4.0f);
}

static void
test_unit ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_unit (&cplx, &cplx);
	
	test_assert_float (cplx.real, 0.6f);
	test_assert_float (cplx.imag, 0.8f);
}

static void
test_addr ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_addr (&cplx, 2.0f, &cplx);
	
	test_assert_float (cplx.real, 5.0f);
	test_assert_float (cplx.imag, 4.0f);
}

static void
test_subr ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_subr (&cplx, 2.0f, &cplx);
	
	test_assert_float (cplx.real, 1.0f);
	test_assert_float (cplx.imag, 4.0f);
}

static void
test_mulr ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_mulr (&cplx, 2.0f, &cplx);
	
	test_assert_float (cplx.real, 6.0f);
	test_assert_float (cplx.imag, 8.0f);
}

static void
test_divr ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_divr (&cplx, 2.0f, &cplx);
	
	test_assert_float (cplx.real, 1.5f);
	test_assert_float (cplx.imag, 2.0f);
}

static void
test_rsubr ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_rsubr (&cplx, 2.0f, &cplx);
	
	test_assert_float (cplx.real, -1.0f);
	test_assert_float (cplx.imag, -4.0f);
}

static void
test_rdivr ( void )
{
	CrankCplxFloat	cplx = {3.0f, 4.0f};
	
	crank_cplx_float_rdivr (&cplx, 2.0f, &cplx);
	
	test_assert_float (cplx.real, 0.24f);
	test_assert_float (cplx.imag, -0.32f);
}

static void
test_add ( void )
{
	CrankCplxFloat	a = {3.0f, 4.0f};
	CrankCplxFloat	b = {5.0f, 12.0f};
	
	crank_cplx_float_add (&a, &b, &a);
	
	test_assert_float (a.real, 8.0f);
	test_assert_float (a.imag, 16.0f);
}

static void
test_sub ( void )
{
	CrankCplxFloat	a = {3.0f, 4.0f};
	CrankCplxFloat	b = {5.0f, 12.0f};
	
	crank_cplx_float_sub (&a, &b, &a);
	
	test_assert_float (a.real, -2.0f);
	test_assert_float (a.imag, -8.0f);
}

static void
test_mul ( void )
{
	// (3 + 4i)(5 + 12i)
	// = 15 + 20i + 36i - 48
	// = -33 + 56i
	
	CrankCplxFloat	a = {3.0f, 4.0f};
	CrankCplxFloat	b = {5.0f, 12.0f};
	
	crank_cplx_float_mul (&a, &b, &a);
	
	test_assert_float (a.real, -33.0f);
	test_assert_float (a.imag, 56.0f);
}

static void
test_div ( void )
{
	// (3 + 4i)/(5 + 12i) = (a + bi)
	
	// (a + bi)(5 + 12i) = 5a + 5bi + 12ai - 12b
	// = (5a - 12b) + (5b + 12a)i
	//
	// 5a - 12b = 3
	// 12a + 5b = 4
	//
	// 196a = 15 + 48 = 63
	// a = 63 / 169
	//
	// 196b = 20 - 36 = -16
	// b = -16 / 169
	
	CrankCplxFloat	a = {3.0f, 4.0f};
	CrankCplxFloat	b = {5.0f, 12.0f};
	
	crank_cplx_float_div (&a, &b, &a);
	
	test_assert_float (a.real, (63.0f / 169.0f));
	test_assert_float (a.imag, (-16.0f / 169.0f));
}

static void
test_mul_conj ( void )
{
	// (3 + 4i)(5 - 12i)
	// = 15 + 20i - 36i + 48
	// = 63 - 16i
	
	CrankCplxFloat	a = {3.0f, 4.0f};
	CrankCplxFloat	b = {5.0f, 12.0f};
	
	crank_cplx_float_mul_conj (&a, &b, &a);
	
	test_assert_float (a.real, 63.0f);
	test_assert_float (a.imag, -16.0f);
}

static void
test_mix ( void )
{
	CrankCplxFloat	a = {3.0f, 4.0f};
	CrankCplxFloat	b = {5.0f, 12.0f};
	
	crank_cplx_float_mix (&a, &b, 0.25f, &a);
	
	test_assert_float (a.real, 3.5f);
	test_assert_float (a.imag, 6.0f);
}

static void
test_ln ( void )
{
	CrankCplxFloat	a = {3.0f, 4.0f};
	
	crank_cplx_float_ln (&a, &a);
	
	test_assert_float (a.real, 1.6094f);
	test_assert_float (a.imag, 0.9273f);
}

static void
test_exp ( void )
{
	CrankCplxFloat	a = {3.0f, 4.0f};
	
	crank_cplx_float_exp (&a, &a);
	
	test_assert_float (a.real, -15.2008f);
	test_assert_float (a.imag, -13.1287f);
}
