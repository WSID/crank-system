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

static void	test_assert_float_real (	const gchar*	file,
										const guint		line,
										const gchar*	func,
										const gchar*	a_str,
										const gchar*	b_str,
										gfloat			a,
										gfloat			b);


static void	test_lu (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (	gint   argc,
      	gchar *argv[] )
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/crank/base/advmat/lu/mat/float/n", test_lu);

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

	test_assert_float (crank_mat_float_n_get (&l, 0, 0), 3.0f);
	test_assert_float (crank_mat_float_n_get (&l, 0, 1), 0.0f);
	test_assert_float (crank_mat_float_n_get (&l, 0, 2), 0.0f);

	test_assert_float (crank_mat_float_n_get (&l, 1, 0), 8.0f);
	test_assert_float (crank_mat_float_n_get (&l, 1, 1), 7.0f);
	test_assert_float (crank_mat_float_n_get (&l, 1, 2), 0.0f);

	test_assert_float (crank_mat_float_n_get (&l, 2, 0), 2.0f);
	test_assert_float (crank_mat_float_n_get (&l, 2, 1), 8.0f);
	test_assert_float (crank_mat_float_n_get (&l, 2, 2), 3.0f);


	test_assert_float (crank_mat_float_n_get (&u, 0, 0), 1.0f);
	test_assert_float (crank_mat_float_n_get (&u, 0, 1), 4.0f);
	test_assert_float (crank_mat_float_n_get (&u, 0, 2), 7.0f);

	test_assert_float (crank_mat_float_n_get (&u, 1, 0), 0.0f);
	test_assert_float (crank_mat_float_n_get (&u, 1, 1), 1.0f);
	test_assert_float (crank_mat_float_n_get (&u, 1, 2), 4.0f);

	test_assert_float (crank_mat_float_n_get (&u, 2, 0), 0.0f);
	test_assert_float (crank_mat_float_n_get (&u, 2, 1), 0.0f);
	test_assert_float (crank_mat_float_n_get (&u, 2, 2), 1.0f);

	crank_mat_float_n_fini (&a);
	crank_mat_float_n_fini (&l);
	crank_mat_float_n_fini (&u);
}
