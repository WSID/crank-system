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

static void		test_2_equal (void);
static void		test_2_to_string (void);

static void		test_2_get (void);
static void		test_2_get_row (void);
static void		test_2_get_col (void);

static void		test_2_tr (void);
static void		test_2_det (void);
static void		test_2_cof (void);
static void		test_2_adj (void);

static void		test_2_neg (void);
static void		test_2_transpose (void);
static void		test_2_inverse (void);

static void		test_2_muls (void);
static void		test_2_divs (void);
static void		test_2_mulv (void);
static void		test_2_mul (void);
static void		test_2_mixs (void);
static void		test_2_mix (void);


//////// Main //////////////////////////////////////////////////////////////////

gint	main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);

  	g_test_add_func ("/crank/base/mat/float/2/equal",		test_2_equal);
  	g_test_add_func ("/crank/base/mat/float/2/to_string",	test_2_to_string);
  	g_test_add_func ("/crank/base/mat/float/2/get",			test_2_get);
  	g_test_add_func ("/crank/base/mat/float/2/get_row",		test_2_get_row);
  	g_test_add_func ("/crank/base/mat/float/2/get_col",		test_2_get_col);
  	g_test_add_func ("/crank/base/mat/float/2/tr",			test_2_tr);
  	g_test_add_func ("/crank/base/mat/float/2/det",			test_2_det);
  	g_test_add_func ("/crank/base/mat/float/2/cof",			test_2_cof);
  	g_test_add_func ("/crank/base/mat/float/2/adj",			test_2_adj);
  	g_test_add_func ("/crank/base/mat/float/2/neg",			test_2_neg);
  	g_test_add_func ("/crank/base/mat/float/2/transpose",	test_2_transpose);
  	g_test_add_func ("/crank/base/mat/float/2/inverse",		test_2_inverse);
  	g_test_add_func ("/crank/base/mat/float/2/muls",		test_2_muls);
  	g_test_add_func ("/crank/base/mat/float/2/divs",		test_2_divs);
  	g_test_add_func ("/crank/base/mat/float/2/mulv",		test_2_mulv);
  	g_test_add_func ("/crank/base/mat/float/2/mul",			test_2_mul);
  	g_test_add_func ("/crank/base/mat/float/2/mixs",		test_2_mixs);
  	g_test_add_func ("/crank/base/mat/float/2/mix",			test_2_mix);

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
		g_printerr (
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
test_2_equal (void)
{
  	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankMatFloat2 b = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankMatFloat2 c = {0.0f, 0.0f,		0.0f, 0.0f};

  	g_assert (  crank_mat_float2_equal (&a, &b));
  	g_assert (! crank_mat_float2_equal (&a, &c));
}

static void
test_2_to_string (void)
{
	CrankMatFloat2	a = {1.0f, 2.0f, 3.0f, 4.0f};
  	gchar*			astr = crank_mat_float2_to_string (&a);

  	g_assert_cmpstr (astr, ==, "[[1, 2], [3, 4]]");

  	g_free (astr);
}


static void
test_2_get (void)
{
  	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f };

  	test_assert_float (crank_mat_float2_get (&a, 0, 0), 1.0f);
  	test_assert_float (crank_mat_float2_get (&a, 0, 1), 2.0f);
  	test_assert_float (crank_mat_float2_get (&a, 1, 0), 3.0f);
  	test_assert_float (crank_mat_float2_get (&a, 1, 1), 4.0f);
}

static void
test_2_get_row (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankVecFloat2 rv;

  	crank_mat_float2_get_row (&a, 0, &rv);

  	test_assert_float (rv.x, 1.0f);
  	test_assert_float (rv.y, 2.0f);

  	crank_mat_float2_get_row (&a, 1, &rv);

  	test_assert_float (rv.x, 3.0f);
  	test_assert_float (rv.y, 4.0f);
}

static void
test_2_get_col (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankVecFloat2 cv;

  	crank_mat_float2_get_col (&a, 0, &cv);

  	test_assert_float (cv.x, 1.0f);
  	test_assert_float (cv.y, 3.0f);

  	crank_mat_float2_get_col (&a, 1, &cv);

  	test_assert_float (cv.x, 2.0f);
  	test_assert_float (cv.y, 4.0f);
}

static void
test_2_tr (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};

  	test_assert_float (crank_mat_float2_get_tr (&a), 5.0f);
}

static void
test_2_det (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};

  	test_assert_float (crank_mat_float2_get_det (&a), -2.0f);
}

static void
test_2_cof (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankMatFloat2 cof;

  	crank_mat_float2_get_cof (&a, &cof);

  	test_assert_float (cof.m00,  4.0f);
  	test_assert_float (cof.m01, -3.0f);
  	test_assert_float (cof.m10, -2.0f);
  	test_assert_float (cof.m11,  1.0f);
}

static void
test_2_adj (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
	CrankMatFloat2 adj;

  	crank_mat_float2_get_adj (&a, &adj);

  	test_assert_float (adj.m00,  4.0f);
  	test_assert_float (adj.m01, -2.0f);
  	test_assert_float (adj.m10, -3.0f);
  	test_assert_float (adj.m11,  1.0f);
}

static void
test_2_neg (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};

  	crank_mat_float2_neg (&a, &a);

  	test_assert_float (a.m00, -1.0f);
  	test_assert_float (a.m01, -2.0f);
  	test_assert_float (a.m10, -3.0f);
  	test_assert_float (a.m11, -4.0f);
}

static void
test_2_transpose (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};

  	crank_mat_float2_transpose (&a, &a);

  	test_assert_float (a.m00, 1.0f);
  	test_assert_float (a.m01, 3.0f);
  	test_assert_float (a.m10, 2.0f);
  	test_assert_float (a.m11, 4.0f);
}

static void
test_2_inverse (void)
{
  	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};

  	crank_mat_float2_inverse (&a, &a);

  	test_assert_float (a.m00, -2.0f);
  	test_assert_float (a.m01,  1.0f);
  	test_assert_float (a.m10,  1.5f);
  	test_assert_float (a.m11, -0.5f);
}


static void
test_2_muls (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};

  	crank_mat_float2_muls (&a, 2.0f, &a);

  	test_assert_float (a.m00, 2.0f);
  	test_assert_float (a.m01, 4.0f);
  	test_assert_float (a.m10, 6.0f);
  	test_assert_float (a.m11, 8.0f);
}

static void
test_2_divs (void)
{
	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};

  	crank_mat_float2_divs (&a, 2.0f, &a);

  	test_assert_float (a.m00, 0.5f);
  	test_assert_float (a.m01, 1.0f);
  	test_assert_float (a.m10, 1.5f);
  	test_assert_float (a.m11, 2.0f);
}

static void
test_2_mulv (void)
{
  	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankVecFloat2 b = {3.0f, 4.0f};

  	crank_mat_float2_mulv (&a, &b, &b);

  	test_assert_float (b.x, 11.0f);
  	test_assert_float (b.y, 25.0f);
}

static void
test_2_mul (void)
{
  	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankMatFloat2 b = {3.0f, 6.0f,		9.0f, 12.0f};

  	crank_mat_float2_mul (&a, &b, &a);

  	test_assert_float (a.m00, 21.0f);
  	test_assert_float (a.m01, 30.0f);
  	test_assert_float (a.m10, 45.0f);
  	test_assert_float (a.m11, 54.0f);
}

static void
test_2_mixs (void)
{
  	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankMatFloat2 b = {3.0f, 6.0f,		9.0f, 12.0f};

	crank_mat_float2_mixs (&a, &b, 0.5f, &a);

  	test_assert_float (a.m00, 2.0f);
  	test_assert_float (a.m01, 4.0f);
  	test_assert_float (a.m10, 6.0f);
  	test_assert_float (a.m11, 8.0f);
}

static void
test_2_mix (void)
{
  	CrankMatFloat2 a = {1.0f, 2.0f,		3.0f, 4.0f};
  	CrankMatFloat2 b = {3.0f, 6.0f,		9.0f, 12.0f};
  	CrankMatFloat2 c = {0.0f, 0.25f,	0.5f, 0.75f};

	crank_mat_float2_mix (&a, &b, &c, &a);

  	test_assert_float (a.m00, 1.0f);
  	test_assert_float (a.m01, 3.0f);
  	test_assert_float (a.m10, 6.0f);
  	test_assert_float (a.m11, 12.0f);
}
