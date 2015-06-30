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

static gboolean	test_counter (	const gboolean	value,
								gpointer		userdata	);

static void	test_2_equal (void);
static void	test_2_hash (void);
static void	test_2_to_string (void);
static void	test_2_get (void);
static void test_2_foreach (void);
static void	test_2_and (void);
static void	test_2_or (void);
static void	test_2_xor (void);
static void	test_2_not (void);
static void	test_2_any (void);
static void	test_2_all (void);

static void	test_n_equal (void);
static void	test_n_hash (void);
static void	test_n_to_string (void);
static void	test_n_get (void);
static void test_n_insert (void);
static void test_n_remove (void);
static void test_n_foreach (void);
static void	test_n_and (void);
static void	test_n_or (void);
static void	test_n_xor (void);
static void	test_n_not (void);
static void	test_n_any (void);
static void	test_n_all (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/vec/bool/2/equal", test_2_equal);
	g_test_add_func ("/crank/base/vec/bool/2/hash", test_2_hash);
	g_test_add_func ("/crank/base/vec/bool/2/to_string", test_2_to_string);
	g_test_add_func ("/crank/base/vec/bool/2/get", test_2_get);
	g_test_add_func ("/crank/base/vec/bool/2/foreach", test_2_foreach);
	g_test_add_func ("/crank/base/vec/bool/2/and", test_2_and);
	g_test_add_func ("/crank/base/vec/bool/2/or", test_2_or);
	g_test_add_func ("/crank/base/vec/bool/2/xor", test_2_xor);
	g_test_add_func ("/crank/base/vec/bool/2/not", test_2_not);
	g_test_add_func ("/crank/base/vec/bool/2/any", test_2_any);
	g_test_add_func ("/crank/base/vec/bool/2/all", test_2_all);
	
	g_test_add_func ("/crank/base/vec/bool/n/equal", test_n_equal);
	g_test_add_func ("/crank/base/vec/bool/n/hash", test_n_hash);
	g_test_add_func ("/crank/base/vec/bool/n/to_string", test_n_to_string);
	g_test_add_func ("/crank/base/vec/bool/n/get", test_n_get);
	g_test_add_func ("/crank/base/vec/bool/n/insert", test_n_insert);
	g_test_add_func ("/crank/base/vec/bool/n/remove", test_n_remove);
	g_test_add_func ("/crank/base/vec/bool/n/foreach", test_n_foreach);
	g_test_add_func ("/crank/base/vec/bool/n/and", test_n_and);
	g_test_add_func ("/crank/base/vec/bool/n/or", test_n_or);
	g_test_add_func ("/crank/base/vec/bool/n/xor", test_n_xor);
	g_test_add_func ("/crank/base/vec/bool/n/not", test_n_not);
	g_test_add_func ("/crank/base/vec/bool/n/any", test_n_any);
	g_test_add_func ("/crank/base/vec/bool/n/all", test_n_all);
	
	g_test_run ();
	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static gboolean
test_counter (	const gboolean	value,
				gpointer		userdata	)
{
	guint*	counts = (guint*) userdata;

	if (value) {
		(*counts) ++;
	}

	return TRUE;
}




static void
test_2_get (void)
{
	CrankVecBool2	a = {TRUE, FALSE};
	
	g_assert (crank_vec_bool2_get (&a, 0) == TRUE);
	g_assert (crank_vec_bool2_get (&a, 1) == FALSE);
}

static void
test_2_foreach (void)
{
	CrankVecBool2	a = {TRUE, FALSE};
	guint			count = 0;

	g_assert (crank_vec_bool2_foreach (&a, test_counter, &count));
	g_assert_cmpint (count, ==, 1);
}

static void
test_2_and (void)
{
	CrankVecBool2	a = {TRUE, TRUE};
	CrankVecBool2	b = {FALSE, TRUE};

	CrankVecBool2	c;

	crank_vec_bool2_and (&a, &b, &c);

  	g_assert (c.x == FALSE);
  	g_assert (c.y == TRUE);
}

static void
test_2_or (void)
{
	CrankVecBool2	a = {FALSE, FALSE};
	CrankVecBool2	b = {FALSE, TRUE};

	CrankVecBool2	c;

	crank_vec_bool2_or (&a, &b, &c);

  	g_assert (c.x == FALSE);
  	g_assert (c.y == TRUE);
}

static void
test_2_xor (void)
{
	CrankVecBool2	a = {TRUE, FALSE};
	CrankVecBool2	b = {TRUE, TRUE};

	CrankVecBool2	c;

	crank_vec_bool2_xor (&a, &b, &c);

  	g_assert (c.x == FALSE);
  	g_assert (c.y == TRUE);
}

static void
test_2_not (void)
{
	CrankVecBool2	a = {TRUE, FALSE};

	CrankVecBool2	c;

	crank_vec_bool2_not (&a, &c);

  	g_assert (c.x == FALSE);
  	g_assert (c.y == TRUE);
}

static void
test_2_any (void)
{
	CrankVecBool2	a = {FALSE, FALSE};
	CrankVecBool2	b = {FALSE, TRUE};

  	g_assert (crank_vec_bool2_get_any (&a) == FALSE);
  	g_assert (crank_vec_bool2_get_any (&b) == TRUE);
}

static void
test_2_all (void)
{
	CrankVecBool2	a = {TRUE, FALSE};
	CrankVecBool2	b = {TRUE, TRUE};

  	g_assert (crank_vec_bool2_get_all (&a) == FALSE);
  	g_assert (crank_vec_bool2_get_all (&b) == TRUE);
}

static void
test_2_equal (void)
{
	CrankVecBool2	a = {TRUE, TRUE};
	CrankVecBool2	b = {TRUE, TRUE};
	CrankVecBool2	c = {TRUE, FALSE};
	
	g_assert (  crank_vec_bool2_equal (&a, &b));
	g_assert (! crank_vec_bool2_equal (&a, &c));
}

static void
test_2_hash (void)
{
	CrankVecBool2	a = {TRUE, TRUE};
	CrankVecBool2	b = {TRUE, TRUE};
	CrankVecBool2	c = {TRUE, FALSE};
	
	guint			ah = crank_vec_bool2_hash (&a);
	guint			bh = crank_vec_bool2_hash (&b);
	guint			ch = crank_vec_bool2_hash (&c);
	
	g_assert_cmpuint (ah, ==, bh);
	g_assert_cmpuint (ah, !=, ch);
}

static void
test_2_to_string (void)
{
	CrankVecBool2	a = {FALSE, TRUE};
	gchar*			astr = crank_vec_bool2_to_string (&a);
	
	g_assert_cmpstr (astr, ==, "(false, true)");
	
	g_free (astr);
}



static void
test_n_equal (void)
{
	CrankVecBoolN	a = {0};
	CrankVecBoolN	b = {0};
	CrankVecBoolN	c = {0};
	
	crank_vec_bool_n_init (&a, 3, TRUE, FALSE, TRUE);
	crank_vec_bool_n_init (&b, 3, TRUE, FALSE, TRUE);
	crank_vec_bool_n_init (&c, 3, TRUE, TRUE, TRUE);
	
	g_assert (  crank_vec_bool_n_equal (&a, &b));
	g_assert (! crank_vec_bool_n_equal (&a, &c));
}

static void
test_n_hash (void)
{
	CrankVecBoolN	a = {0};
	CrankVecBoolN	b = {0};
	CrankVecBoolN	c = {0};
	
	crank_vec_bool_n_init (&a, 3, TRUE, FALSE, TRUE);
	crank_vec_bool_n_init (&b, 3, TRUE, FALSE, TRUE);
	crank_vec_bool_n_init (&c, 3, TRUE, TRUE, TRUE);
	
	guint			a_hash = crank_vec_bool_n_hash (&a);
	guint			b_hash = crank_vec_bool_n_hash (&b);
	guint			c_hash = crank_vec_bool_n_hash (&c);
	
	g_assert_cmpuint (a_hash, ==, b_hash);
	g_assert_cmpuint (a_hash, !=, c_hash);
}
static void
test_n_get (void)
{
	CrankVecBoolN	a = {0};
	
	crank_vec_bool_n_init (&a, 5, TRUE, TRUE, FALSE, FALSE, TRUE);
	
	g_assert (crank_vec_bool_n_get (&a, 0) == TRUE);
	g_assert (crank_vec_bool_n_get (&a, 1) == TRUE);
	g_assert (crank_vec_bool_n_get (&a, 2) == FALSE);
	g_assert (crank_vec_bool_n_get (&a, 3) == FALSE);
	g_assert (crank_vec_bool_n_get (&a, 4) == TRUE);
	
	crank_vec_bool_n_fini (&a);
}

static void
test_n_insert (void)
{
	CrankVecBoolN	a = {0};
	crank_vec_bool_n_init (&a, 4, TRUE, FALSE, FALSE, TRUE);

	crank_vec_bool_n_insert (&a, 2, TRUE);

	g_assert_cmpint (crank_vec_bool_n_get_size (&a), ==, 5);
	g_assert (crank_vec_bool_n_get (&a, 0) == TRUE);
	g_assert (crank_vec_bool_n_get (&a, 1) == FALSE);
	g_assert (crank_vec_bool_n_get (&a, 2) == TRUE);
	g_assert (crank_vec_bool_n_get (&a, 3) == FALSE);
	g_assert (crank_vec_bool_n_get (&a, 4) == TRUE);

	crank_vec_bool_n_fini (&a);
}

static void
test_n_remove (void)
{
	CrankVecBoolN	a = {0};
	crank_vec_bool_n_init (&a, 4, TRUE, FALSE, FALSE, TRUE);

	crank_vec_bool_n_remove (&a, 2);

	g_assert_cmpint (crank_vec_bool_n_get_size (&a), ==, 3);
	g_assert (crank_vec_bool_n_get (&a, 0) == TRUE);
	g_assert (crank_vec_bool_n_get (&a, 1) == FALSE);
	g_assert (crank_vec_bool_n_get (&a, 2) == TRUE);

	crank_vec_bool_n_fini (&a);
}

static void
test_n_foreach (void)
{
	CrankVecBoolN	a = {0};
	guint			count = 0;

	crank_vec_bool_n_init (&a, 5, TRUE, TRUE, FALSE, FALSE, TRUE);

	g_assert (crank_vec_bool_n_foreach (&a, test_counter, &count));
	g_assert_cmpint (count, ==, 3);

	crank_vec_bool_n_fini (&a);
}

static void
test_n_and (void)
{
	CrankVecBoolN	a = {0};
	CrankVecBoolN	b = {0};

	CrankVecBoolN	c = {0};

	crank_vec_bool_n_init (&a, 4, TRUE, TRUE, FALSE, FALSE);
	crank_vec_bool_n_init (&b, 2, FALSE, TRUE);

	crank_vec_bool_n_and (&a, &b, &c);

	g_assert (crank_vec_bool_n_get_size (&c) == 2);
  	g_assert (crank_vec_bool_n_get (&c, 0) == FALSE);
  	g_assert (crank_vec_bool_n_get (&c, 1) == TRUE);
	
	crank_vec_bool_n_fini (&a);
	crank_vec_bool_n_fini (&b);
	crank_vec_bool_n_fini (&c);
}

static void
test_n_or (void)
{
	CrankVecBoolN	a = {0};
	CrankVecBoolN	b = {0};

	CrankVecBoolN	c = {0};

	crank_vec_bool_n_init (&a, 4, FALSE, FALSE, FALSE, TRUE);
	crank_vec_bool_n_init (&b, 2, FALSE, TRUE);

	crank_vec_bool_n_or (&a, &b, &c);

  	g_assert (crank_vec_bool_n_get (&c, 0) == FALSE);
  	g_assert (crank_vec_bool_n_get (&c, 1) == TRUE);
  	g_assert (crank_vec_bool_n_get (&c, 2) == FALSE);
  	g_assert (crank_vec_bool_n_get (&c, 3) == TRUE);
	
	crank_vec_bool_n_fini (&a);
	crank_vec_bool_n_fini (&b);
	crank_vec_bool_n_fini (&c);
}

static void
test_n_xor (void)
{
	CrankVecBoolN	a = {0};
	CrankVecBoolN	b = {0};
	
	CrankVecBoolN	c = {0};
	
	crank_vec_bool_n_init (&a, 4, FALSE, FALSE, FALSE, TRUE);
	crank_vec_bool_n_init (&b, 2, FALSE, TRUE);
	
	crank_vec_bool_n_xor (&a, &b, &c);
	
	g_assert (crank_vec_bool_n_get (&c, 0) == FALSE);
  	g_assert (crank_vec_bool_n_get (&c, 1) == TRUE);
  	g_assert (crank_vec_bool_n_get (&c, 2) == FALSE);
  	g_assert (crank_vec_bool_n_get (&c, 3) == TRUE);
	
	crank_vec_bool_n_fini (&a);
	crank_vec_bool_n_fini (&b);
	crank_vec_bool_n_fini (&c);
}

static void
test_n_not (void)
{
	CrankVecBoolN	a = {0};
	
	CrankVecBoolN	c = {0};
	
	crank_vec_bool_n_init (&a, 4, FALSE, FALSE, FALSE, TRUE);
	
	crank_vec_bool_n_not (&a, &c);
	
	g_assert (crank_vec_bool_n_get (&c, 0) == TRUE);
  	g_assert (crank_vec_bool_n_get (&c, 1) == TRUE);
  	g_assert (crank_vec_bool_n_get (&c, 2) == TRUE);
  	g_assert (crank_vec_bool_n_get (&c, 3) == FALSE);
	
	crank_vec_bool_n_fini (&a);
	crank_vec_bool_n_fini (&c);
}

static void
test_n_any (void)
{
	CrankVecBoolN	a = {0};
	CrankVecBoolN	b = {0};
	
	crank_vec_bool_n_init (&a, 4, FALSE, FALSE, FALSE, TRUE);
	crank_vec_bool_n_init (&b, 2, FALSE, FALSE );
	
	g_assert (crank_vec_bool_n_get_any (&a) == TRUE);
  	g_assert (crank_vec_bool_n_get_any (&b) == FALSE);
	
	crank_vec_bool_n_fini (&a);
	crank_vec_bool_n_fini (&b);
}

static void
test_n_all (void)
{
	CrankVecBoolN	a = {0};
	CrankVecBoolN	b = {0};
	
	crank_vec_bool_n_init (&a, 4, FALSE, FALSE, FALSE, TRUE);
	crank_vec_bool_n_init (&b, 2, TRUE, TRUE );
	
	g_assert (crank_vec_bool_n_get_all (&a) == FALSE);
  	g_assert (crank_vec_bool_n_get_all (&b) == TRUE);
  	
	crank_vec_bool_n_fini (&a);
	crank_vec_bool_n_fini (&b);
}

static void
test_n_to_string (void)
{
	CrankVecBoolN	a = {0};
	gchar*			astr;
	
	crank_vec_bool_n_init (&a, 4, FALSE, FALSE, FALSE, TRUE);
	astr = crank_vec_bool_n_to_string (&a);
	
	g_assert_cmpstr (astr, ==, "(false, false, false, true)");
	
	g_free (astr);
}
