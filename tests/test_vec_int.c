/* Copyright (C) 2015, WSID   */

/* This file is part of Crank System.
 *
 *  Crank System is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  Crank System is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with Crank System.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include "crankbase.h"

void	test_2_get (void)
{
	CrankVecInt2	a = {3, 4};
	
	g_assert_cmpint (crank_vec_int2_get (&a, 0), ==, 3);
	g_assert_cmpint (crank_vec_int2_get (&a, 1), ==, 4);
}

void	test_2_hash (void)
{
	CrankVecInt2	a = {g_test_rand_int (), g_test_rand_int ()};
	CrankVecInt2	b = {g_test_rand_int (), g_test_rand_int ()};
	CrankVecInt2	c = {a.x, a.y};
	
	guint			ah = crank_vec_int2_hash (&a);
	guint			bh = crank_vec_int2_hash (&b);
	guint			ch = crank_vec_int2_hash (&c);
	
	g_assert_cmpuint (ah, !=, bh);
	g_assert_cmpuint (ah, ==, ch);
}


void	test_2_equal (void)
{
	CrankVecInt2	a = {g_test_rand_int (), g_test_rand_int ()};
	CrankVecInt2	b = {g_test_rand_int (), g_test_rand_int ()};
	CrankVecInt2	c = {a.x, a.y};
	
	g_assert (! crank_vec_int2_equal (&a, &b));
	g_assert (  crank_vec_int2_equal (&a, &c));
}


void	test_2_to_string (void)
{
	CrankVecInt2	a = {3, 4};
	gchar*			astr = crank_vec_int2_to_string (&a);
	
	g_assert_cmpstr (astr, ==, "(3, 4)");
}


void	test_2_magn (void)
{
	CrankVecInt2	a = {3, 4};
	
	g_assert_cmpuint (crank_vec_int2_get_magn_sq (&a), ==, 25);
	g_assert_cmpfloat (crank_vec_int2_get_magn (&a), ==, 5.0f);
}


void	test_2_muls (void)
{
	CrankVecInt2	a = {3, 4};
	
	crank_vec_int2_muls (&a, 2, &a);
	
	g_assert_cmpint (a.x, ==, 6);
	g_assert_cmpint (a.y, ==, 8);
}


void	test_2_divs (void)
{
	CrankVecInt2	a = {3, 4};
	
	crank_vec_int2_divs (&a, 2, &a);
	
	g_assert_cmpint (a.x, ==, 1);
	g_assert_cmpint (a.y, ==, 2);
}


void	test_2_mods (void)
{
	CrankVecInt2	a = {9, 13};
	
	crank_vec_int2_mods (&a, 7, &a);
	
	g_assert_cmpint (a.x, ==, 2);
	g_assert_cmpint (a.y, ==, 6);
}


void	test_2_add (void)
{
	CrankVecInt2	a = {3, 4};
	CrankVecInt2	b = {5, 12};
	
	crank_vec_int2_add (&a, &b, &a);
	
	g_assert_cmpint (a.x, ==, 8);
	g_assert_cmpint (a.y, ==, 16);
}


void	test_2_sub (void)
{
	CrankVecInt2	a = {3, 4};
	CrankVecInt2	b = {5, 12};
	
	crank_vec_int2_sub (&a, &b, &a);
	
	g_assert_cmpint (a.x, ==, -2);
	g_assert_cmpint (a.y, ==, -8);
}


void	test_2_dot (void)
{
	CrankVecInt2	a = {3, 4};
	CrankVecInt2	b = {5, 12};
	
	g_assert_cmpint (crank_vec_int2_dot (&a, &b), ==, 63);
}


void	test_2_cmpmul (void)
{
	CrankVecInt2	a = {3, 4};
	CrankVecInt2	b = {5, 12};
	
	crank_vec_int2_cmpmul (&a, &b, &a);
	
	g_assert_cmpint (a.x, ==, 15);
	g_assert_cmpint (a.y, ==, 48);
}


void	test_2_cmpdiv (void)
{
	CrankVecInt2	a = {3, 4};
	CrankVecInt2	b = {5, 12};
	
	crank_vec_int2_cmpdiv (&b, &a, &b);
	
	g_assert_cmpint (b.x, ==, 1);
	g_assert_cmpint (b.y, ==, 3);
}


void	test_2_cmpmod (void)
{
	CrankVecInt2	a = {3, 4};
	CrankVecInt2	b = {5, 12};
	
	crank_vec_int2_cmpmod (&b, &a, &b);
	
	g_assert_cmpint (b.x, ==, 2);
	g_assert_cmpint (b.y, ==, 0);
}


void	test_2_cmpless (void)
{
	CrankVecInt2	a = {17, 21};
	CrankVecInt2	b = {53, 20};
	CrankVecBool2	r;
	
	crank_vec_int2_cmpless (&a, &b, &r);
	
	g_assert_true  (r.x);
	g_assert_false (r.y);
}
	

void	test_2_cmpeq (void)
{
	CrankVecInt2	a = {17, 20};
	CrankVecInt2	b = {53, 20};
	CrankVecBool2	r;
	
	crank_vec_int2_cmpeq (&a, &b, &r);
	
	g_assert_false (r.x);
	g_assert_true  (r.y);
}


void	test_2_cmpgreater (void)
{
	CrankVecInt2	a = {17, 21};
	CrankVecInt2	b = {53, 20};
	CrankVecBool2	r;
	
	crank_vec_int2_cmpgreater (&a, &b, &r);
	
	g_assert_false (r.x);
	g_assert_true  (r.y);
}


void	test_2_cmpcmp (void)
{
	CrankVecInt2	a = {17, 21};
	CrankVecInt2	b = {53, 20};
	CrankVecInt2	r;
	
	crank_vec_int2_cmpcmp (&a, &b, &r);
	
	g_assert_cmpint (r.x, <, 0);
	g_assert_cmpint (r.y, >, 0);
}


void	test_2_min (void)
{
	CrankVecInt2	a = {17, 21};
	CrankVecInt2	b = {53, 20};
	CrankVecInt2	r;
	
	crank_vec_int2_min (&a, &b, &r);
	
	g_assert_cmpint (r.x, ==, 17);
	g_assert_cmpint (r.y, ==, 20);
}


void	test_2_max (void)
{
	CrankVecInt2	a = {17, 21};
	CrankVecInt2	b = {53, 20};
	CrankVecInt2	r;
	
	crank_vec_int2_max (&a, &b, &r);
	
	g_assert_cmpint (r.x, ==, 53);
	g_assert_cmpint (r.y, ==, 21);
}









void	test_n_get (void)
{
	CrankVecIntN	a = {0};
	
	crank_vec_int_n_init (&a, 2, 3, 4);
		
	g_assert_cmpint (crank_vec_int_n_get (&a, 0), ==, 3);
	g_assert_cmpint (crank_vec_int_n_get (&a, 1), ==, 4);
	
	crank_vec_int_n_fini (&a);
}

void	test_n_hash (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};
	CrankVecIntN	c = {0};
	
	crank_vec_int_n_init (&a, 2, g_test_rand_int (), g_test_rand_int ());
	crank_vec_int_n_init (&b, 2, g_test_rand_int (), g_test_rand_int ());
	crank_vec_int_n_init_arr (&c, 2, a.data);
	
	guint			ah = crank_vec_int_n_hash (&a);
	guint			bh = crank_vec_int_n_hash (&b);
	guint			ch = crank_vec_int_n_hash (&c);
	
	g_assert_cmpuint (ah, !=, bh);
	g_assert_cmpuint (ah, ==, ch);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
	crank_vec_int_n_fini (&c);
}


void	test_n_equal (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};
	CrankVecIntN	c = {0};
	
	crank_vec_int_n_init (&a, 2, g_test_rand_int (), g_test_rand_int ());
	crank_vec_int_n_init (&b, 2, g_test_rand_int (), g_test_rand_int ());
	crank_vec_int_n_init_arr (&c, 2, a.data);
	
	g_assert (! crank_vec_int_n_equal (&a, &b));
	g_assert (  crank_vec_int_n_equal (&a, &c));
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
	crank_vec_int_n_fini (&c);
}


void	test_n_to_string (void)
{
	CrankVecIntN	a = {0};
	
	crank_vec_int_n_init (&a, 5, 3, 4, 5, 6, 7);
	
	gchar*			astr = crank_vec_int_n_to_string (&a);
	
	g_assert_cmpstr (astr, ==, "(3, 4, 5, 6, 7)");
	
	crank_vec_int_n_fini (&a);
}


void	test_n_magn (void)
{
	CrankVecIntN	a = {0};
	
	crank_vec_int_n_init (&a, 2, 3, 4);
	
	g_assert_cmpuint (crank_vec_int_n_get_magn_sq (&a), ==, 25);
	g_assert_cmpfloat (crank_vec_int_n_get_magn (&a), ==, 5.0f);

	crank_vec_int_n_fini (&a);
}


void	test_n_muls (void)
{
	CrankVecIntN	a = {0};
	
	crank_vec_int_n_init (&a, 2, 3, 4);

	crank_vec_int_n_muls (&a, 2, &a);

	g_assert_cmpint (a.data[0], ==, 6);
	g_assert_cmpint (a.data[1], ==, 8);
	
	crank_vec_int_n_fini (&a);
}


void	test_n_divs (void)
{
	CrankVecIntN	a = {0};
	
	crank_vec_int_n_init (&a, 2, 3, 4);
	
	crank_vec_int_n_divs (&a, 2, &a);
	
	g_assert_cmpint (a.data[0], ==, 1);
	g_assert_cmpint (a.data[1], ==, 2);
	
	crank_vec_int_n_fini (&a);
}


void	test_n_mods (void)
{
	CrankVecIntN	a = {0};
	
	crank_vec_int_n_init (&a, 2, 32, 48);
	
	crank_vec_int_n_mods (&a, 7, &a);
	
	g_assert_cmpint (a.data[0], ==, 4);
	g_assert_cmpint (a.data[1], ==, 6);
	
	crank_vec_int_n_fini (&a);
}


void	test_n_add (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};

	crank_vec_int_n_init (&a, 2, 3, 4);
	crank_vec_int_n_init (&b, 2, 5, 12);
	
	crank_vec_int_n_add (&a, &b, &a);
	
	g_assert_cmpint (a.data[0], ==, 8);
	g_assert_cmpint (a.data[1], ==, 16);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
}


void	test_n_sub (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};

	crank_vec_int_n_init (&a, 2, 3, 4);
	crank_vec_int_n_init (&b, 2, 5, 12);
	
	crank_vec_int_n_sub (&a, &b, &a);
	
	g_assert_cmpint (a.data[0], ==, -2);
	g_assert_cmpint (a.data[1], ==, -8);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
}


void	test_n_dot (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};

	crank_vec_int_n_init (&a, 2, 3, 4);
	crank_vec_int_n_init (&b, 2, 5, 12);
	
	g_assert_cmpint (crank_vec_int_n_dot (&a, &b), ==, 63);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
}


void	test_n_cmpmul (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};

	crank_vec_int_n_init (&a, 2, 3, 4);
	crank_vec_int_n_init (&b, 2, 5, 12);
	
	crank_vec_int_n_cmpmul (&a, &b, &a);
	
	g_assert_cmpint (a.data[0], ==, 15);
	g_assert_cmpint (a.data[1], ==, 48);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
}


void	test_n_cmpdiv (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};

	crank_vec_int_n_init (&a, 2, 3, 4);
	crank_vec_int_n_init (&b, 2, 5, 12);
	
	crank_vec_int_n_cmpdiv (&b, &a, &b);
	
	g_assert_cmpint (b.data[0], ==, 1);
	g_assert_cmpint (b.data[1], ==, 3);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
}


void	test_n_cmpmod (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};

	crank_vec_int_n_init (&a, 2, 3, 4);
	crank_vec_int_n_init (&b, 2, 5, 12);
	
	crank_vec_int_n_cmpmod (&b, &a, &b);
	
	g_assert_cmpint (b.data[0], ==, 2);
	g_assert_cmpint (b.data[1], ==, 0);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
}


void	test_n_cmpless (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};
	CrankVecBoolN	r = {0};
	
	crank_vec_int_n_init (&a, 2, 17, 19);
	crank_vec_int_n_init (&b, 2, 53, 20);
	
	crank_vec_int_n_cmpless (&a, &b, &r);
	
	g_assert_true  (r.data[0]);
	g_assert_true  (r.data[1]);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
	crank_vec_bool_n_fini (&r);
}
	

void	test_n_cmpeq (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};
	CrankVecBoolN	r = {0};
	
	crank_vec_int_n_init (&a, 2, 17, 20);
	crank_vec_int_n_init (&b, 2, 53, 20);
	
	crank_vec_int_n_cmpeq (&a, &b, &r);
	
	g_assert_false (r.data[0]);
	g_assert_true  (r.data[1]);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
	crank_vec_bool_n_fini (&r);
}


void	test_n_cmpgreater (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};
	CrankVecBoolN	r = {0};
	
	crank_vec_int_n_init (&a, 2, 17, 19);
	crank_vec_int_n_init (&b, 2, 53, 20);
	
	crank_vec_int_n_cmpgreater (&a, &b, &r);
	
	g_assert_false (r.data[0]);
	g_assert_false (r.data[1]);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
	crank_vec_bool_n_fini (&r);
}


void	test_n_cmpcmp (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};
	CrankVecIntN	r = {0};
	
	crank_vec_int_n_init (&a, 2, 17, 19);
	crank_vec_int_n_init (&b, 2, 53, 20);
	
	crank_vec_int_n_cmpcmp (&a, &b, &r);
	
	g_assert_cmpint (r.data[0], <, 0);
	g_assert_cmpint (r.data[1], <, 0);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
	crank_vec_int_n_fini (&r);
}


void	test_n_min (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};
	CrankVecIntN	r = {0};
	
	crank_vec_int_n_init (&a, 2, 17, 19);
	crank_vec_int_n_init (&b, 2, 53, 20);
	
	crank_vec_int_n_min (&a, &b, &r);
	
	g_assert_cmpint (r.data[0], ==, 17);
	g_assert_cmpint (r.data[1], ==, 19);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
	crank_vec_int_n_fini (&r);
}


void	test_n_max (void)
{
	CrankVecIntN	a = {0};
	CrankVecIntN	b = {0};
	CrankVecIntN	r = {0};
	
	crank_vec_int_n_init (&a, 2, 17, 19);
	crank_vec_int_n_init (&b, 2, 53, 20);
	
	crank_vec_int_n_max (&a, &b, &r);
	
	g_assert_cmpint (r.data[0], ==, 53);
	g_assert_cmpint (r.data[1], ==, 20);
	
	crank_vec_int_n_fini (&a);
	crank_vec_int_n_fini (&b);
	crank_vec_int_n_fini (&r);
}


void	main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/vec/int/2/get", test_2_get);
	g_test_add_func ("/crank/base/vec/int/2/hash", test_2_hash);
	g_test_add_func ("/crank/base/vec/int/2/equal", test_2_equal);
	g_test_add_func ("/crank/base/vec/int/2/to_string", test_2_to_string);
	g_test_add_func ("/crank/base/vec/int/2/magn", test_2_magn);
	g_test_add_func ("/crank/base/vec/int/2/muls", test_2_muls);
	g_test_add_func ("/crank/base/vec/int/2/divs", test_2_divs);
	g_test_add_func ("/crank/base/vec/int/2/mods", test_2_mods);
	g_test_add_func ("/crank/base/vec/int/2/add", test_2_add);
	g_test_add_func ("/crank/base/vec/int/2/sub", test_2_sub);
	g_test_add_func ("/crank/base/vec/int/2/dot", test_2_dot);
	g_test_add_func ("/crank/base/vec/int/2/cmpmul", test_2_cmpmul);
	g_test_add_func ("/crank/base/vec/int/2/cmpdiv", test_2_cmpdiv);
	g_test_add_func ("/crank/base/vec/int/2/cmpmod", test_2_cmpmod);
	g_test_add_func ("/crank/base/vec/int/2/cmpless", test_2_cmpless);
	g_test_add_func ("/crank/base/vec/int/2/cmpeq", test_2_cmpeq);
	g_test_add_func ("/crank/base/vec/int/2/cmpgreater", test_2_cmpgreater);
	g_test_add_func ("/crank/base/vec/int/2/cmpcmp", test_2_cmpcmp);
	g_test_add_func ("/crank/base/vec/int/2/min", test_2_min);
	g_test_add_func ("/crank/base/vec/int/2/max", test_2_max);
	
	g_test_add_func ("/crank/base/vec/int/n/get", test_n_get);
	g_test_add_func ("/crank/base/vec/int/n/hash", test_n_hash);
	g_test_add_func ("/crank/base/vec/int/n/equal", test_n_equal);
	g_test_add_func ("/crank/base/vec/int/n/to_string", test_n_to_string);
	g_test_add_func ("/crank/base/vec/int/n/magn", test_n_magn);
	g_test_add_func ("/crank/base/vec/int/n/muls", test_n_muls);
	g_test_add_func ("/crank/base/vec/int/n/divs", test_n_divs);
	g_test_add_func ("/crank/base/vec/int/n/mods", test_n_mods);
	g_test_add_func ("/crank/base/vec/int/n/add", test_n_add);
	g_test_add_func ("/crank/base/vec/int/n/sub", test_n_sub);
	g_test_add_func ("/crank/base/vec/int/n/dot", test_n_dot);
	g_test_add_func ("/crank/base/vec/int/n/cmpmul", test_n_cmpmul);
	g_test_add_func ("/crank/base/vec/int/n/cmpdiv", test_n_cmpdiv);
	g_test_add_func ("/crank/base/vec/int/n/cmpmod", test_n_cmpmod);
	g_test_add_func ("/crank/base/vec/int/n/cmpless", test_n_cmpless);
	g_test_add_func ("/crank/base/vec/int/n/cmpeq", test_n_cmpeq);
	g_test_add_func ("/crank/base/vec/int/n/cmpgreater", test_n_cmpgreater);
	g_test_add_func ("/crank/base/vec/int/n/cmpcmp", test_n_cmpcmp);
	g_test_add_func ("/crank/base/vec/int/n/min", test_n_min);
	g_test_add_func ("/crank/base/vec/int/n/max", test_n_max);
	
	g_test_run ();
}
