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
 
#include <string.h>
#include <glib.h>

#include "crankbase.h"

void		test_add	(void);
void		test_sub	(void);
void		test_mul	(void);
void		test_div	(void);
void		test_neg	(void);
void		test_inc	(void);
void		test_dec	(void);
void		test_lshift	(void);
void		test_rshift	(void);
void		test_leq	(void);
void		test_eq		(void);
void		test_geq	(void);
void		test_std_lshift	(void);
void		test_std_rshift	(void);
void		test_std_leq	(void);
void		test_std_eq		(void);
void		test_std_geq	(void);


gint
main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/book/add", test_add );
	g_test_add_func ("/crank/base/book/sub", test_sub );
	g_test_add_func ("/crank/base/book/mul", test_mul );
	g_test_add_func ("/crank/base/book/div", test_div );
	g_test_add_func ("/crank/base/book/neg", test_neg );
	g_test_add_func ("/crank/base/book/inc", test_inc );
	g_test_add_func ("/crank/base/book/dec", test_dec );
	g_test_add_func ("/crank/base/book/lshift", test_lshift );
	g_test_add_func ("/crank/base/book/rshift", test_rshift );
	g_test_add_func ("/crank/base/book/leq", test_leq );
	g_test_add_func ("/crank/base/book/eq", test_eq );
	g_test_add_func ("/crank/base/book/geq", test_geq );
	
	g_test_add_func ("/crank/base/book/std/lshift", test_std_lshift );
	g_test_add_func ("/crank/base/book/std/rshift", test_std_rshift );
	g_test_add_func ("/crank/base/book/std/leq", test_std_leq );
	g_test_add_func ("/crank/base/book/std/eq", test_std_eq );
	g_test_add_func ("/crank/base/book/std/geq", test_std_geq );
	
	g_test_run ();
}


void
test_add (void)
{
	GValue value_a = {0};
	GValue value_b = {0};
	GValue value_r = {0};
	
	{
		gchar	ch_a;
		gchar	ch_b;
		gchar	ch_r;
	
		ch_a = (gchar) g_test_rand_int_range (G_MININT8, G_MAXINT8);
		ch_b = (gchar) g_test_rand_int_range (G_MININT8, G_MAXINT8);
		ch_r = ch_a + ch_b;
	
		g_value_init (&value_a, G_TYPE_CHAR);
		g_value_init (&value_b, G_TYPE_CHAR);
	
		g_value_set_schar (&value_a, ch_a);
		g_value_set_schar (&value_b, ch_b);
		
	
		g_assert (crank_base_add (&value_r, &value_a, &value_b));
		g_assert_cmpint (g_value_get_schar (&value_r), ==, ch_r);
	
		g_value_unset (&value_a);
		g_value_unset (&value_b);
		g_value_unset (&value_r);
	}
	
	{
		gint	int_a;
		gint	int_b;
		gint	int_r;
		
		int_a = g_test_rand_int ();
		int_b = g_test_rand_int ();
		int_r = int_a + int_b;
		
		g_value_init (&value_a, G_TYPE_INT);
		g_value_init (&value_b, G_TYPE_INT);
	
		g_value_set_int (&value_a, int_a);
		g_value_set_int (&value_b, int_b);
	
		g_assert (crank_base_add (&value_r, &value_a, &value_b));
		g_assert_cmpint (g_value_get_int (&value_r), ==, int_r);
	
		g_value_unset (&value_a);
		g_value_unset (&value_b);
		g_value_unset (&value_r);
	}
	
	{
		glong	long_a;
		glong	long_b;
		glong	long_r;
		
		long_a = (glong) g_test_rand_double_range (G_MINLONG, G_MAXLONG);
		long_b = (glong) g_test_rand_double_range (G_MINLONG, G_MAXLONG);
		long_r = long_a + long_b;
		
		g_value_init (&value_a, G_TYPE_LONG);
		g_value_init (&value_b, G_TYPE_LONG);
	
		g_value_set_long (&value_a, long_a);
		g_value_set_long (&value_b, long_b);
	
		g_assert (crank_base_add (&value_r, &value_a, &value_b));
		g_assert_cmpint (g_value_get_long (&value_r), ==, long_r);
	
		g_value_unset (&value_a);
		g_value_unset (&value_b);
		g_value_unset (&value_r);
	}
	
	{
		gint64	int64_a;
		gint64	int64_b;
		gint64	int64_r;
		
		int64_a = (gint64) g_test_rand_double_range (G_MININT64, G_MAXINT64);
		int64_b = (gint64) g_test_rand_double_range (G_MININT64, G_MAXINT64);
		int64_r = int64_a + int64_b;
		
		g_value_init (&value_a, G_TYPE_INT64);
		g_value_init (&value_b, G_TYPE_INT64);
	
		g_value_set_int64 (&value_a, int64_a);
		g_value_set_int64 (&value_b, int64_b);
	
		g_assert (crank_base_add (&value_r, &value_a, &value_b));
		g_assert_cmpint (g_value_get_int64 (&value_r), ==, int64_r);
	
		g_value_unset (&value_a);
		g_value_unset (&value_b);
		g_value_unset (&value_r);
	}
}

void
test_sub (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 10);
	g_value_set_int (&value_b, 27);
	
	g_assert (crank_base_sub (&value_r, &value_a, &value_b));
	g_assert_cmpint (g_value_get_int (&value_r), ==, (10 - 27));
}

void
test_mul (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 10);
	g_value_set_int (&value_b, 27);
	
	g_assert (crank_base_mul (&value_r, &value_a, &value_b));
	g_assert_cmpint (g_value_get_int (&value_r), ==, (10 * 27));
}

void
test_div (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 30);
	g_value_set_int (&value_b, 6);
	
	g_assert (crank_base_div (&value_r, &value_a, &value_b));
	g_assert_cmpint (g_value_get_int (&value_r), ==, (30 / 6));
}

void
test_neg (void)
{
	GValue	value_a = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	
	g_value_set_int (&value_a, 10);
	
	g_assert (crank_base_neg (&value_r, &value_a));
	g_assert_cmpint (g_value_get_int (&value_r), ==, (-10));
}

void
test_inc (void)
{
	GValue	value_a = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	
	g_value_set_int (&value_a, 10);
	
	g_assert (crank_base_inc (&value_r, &value_a));
	g_assert_cmpint (g_value_get_int (&value_r), ==, (11));
}

void
test_dec (void)
{
	GValue	value_a = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	
	g_value_set_int (&value_a, 10);
	
	g_assert (crank_base_dec (&value_r, &value_a));
	g_assert_cmpint (g_value_get_int (&value_r), ==, (9));
}

void
test_lshift (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_UINT);
	
	g_value_set_int (&value_a, 157);
	g_value_set_uint (&value_b, 3);
	
	g_assert (crank_base_lshift (&value_r, &value_a, &value_b));
	g_assert_cmpint (g_value_get_int (&value_r), ==, (157 << 3));
}

void
test_rshift (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_UINT);
	
	g_value_set_int (&value_a, 157);
	g_value_set_uint (&value_b, 3);
	
	g_assert (crank_base_rshift (&value_r, &value_a, &value_b));
	g_assert_cmpint (g_value_get_int (&value_r), ==, (157 >> 3));
}

void
test_leq (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 153);
	g_value_set_int (&value_b, 7);
	
	g_assert (crank_base_leq (&value_r, &value_a, &value_b));
	g_assert_false (g_value_get_boolean (&value_r));
}


void
test_eq (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 153);
	g_value_set_int (&value_b, 7);
	
	g_assert (crank_base_eq (&value_r, &value_a, &value_b));
	g_assert_false (g_value_get_boolean (&value_r));
}


void
test_geq (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 153);
	g_value_set_int (&value_b, 7);
	
	g_assert (crank_base_geq (&value_r, &value_a, &value_b));
	g_assert_true (g_value_get_boolean (&value_r));
}


void
test_std_lshift (void)
{
	GValue	value_a = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_set_int (&value_a, 157);
	
	crank_base_std_lshift (&value_r, &value_a, 3);
	g_assert_cmpint (g_value_get_int (&value_r), ==, 157 << 3);
}

void
test_std_rshift (void)
{
	GValue	value_a = {0};
	
	GValue	value_r = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_set_int (&value_a, 157);
	
	crank_base_std_rshift (&value_r, &value_a, 3);
	g_assert_cmpint (g_value_get_int (&value_r), ==, 157 >> 3);
}

void
test_std_leq (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 153);
	g_value_set_int (&value_b, 7);
	
	g_assert_false (crank_base_std_leq (&value_a, &value_b));
}

void
test_std_eq (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 153);
	g_value_set_int (&value_b, 7);
	
	g_assert_false (crank_base_std_eq (&value_a, &value_b));
}

void
test_std_geq (void)
{
	GValue	value_a = {0};
	GValue	value_b = {0};
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	
	g_value_set_int (&value_a, 153);
	g_value_set_int (&value_b, 7);
	
	g_assert_true (crank_base_std_geq (&value_a, &value_b));
}
