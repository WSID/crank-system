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
	CrankVecBool2	a = {TRUE, FALSE};
	
	g_assert (crank_vec_bool2_get (&a, 0) == TRUE);
	g_assert (crank_vec_bool2_get (&a, 1) == FALSE);
}

void	test_2_and (void)
{
	CrankVecBool2	a = {TRUE, TRUE};
	CrankVecBool2	b = {FALSE, TRUE};

	CrankVecBool2	c;

	crank_vec_bool2_and (&a, &b, &c);

  	g_assert (c.x == FALSE);
  	g_assert (c.y == TRUE);
}

void	test_2_or (void)
{
	CrankVecBool2	a = {FALSE, FALSE};
	CrankVecBool2	b = {FALSE, TRUE};

	CrankVecBool2	c;

	crank_vec_bool2_or (&a, &b, &c);

  	g_assert (c.x == FALSE);
  	g_assert (c.y == TRUE);
}

void	test_2_xor (void)
{
	CrankVecBool2	a = {TRUE, FALSE};
	CrankVecBool2	b = {TRUE, TRUE};

	CrankVecBool2	c;

	crank_vec_bool2_xor (&a, &b, &c);

  	g_assert (c.x == FALSE);
  	g_assert (c.y == TRUE);
}

void	test_2_not (void)
{
	CrankVecBool2	a = {TRUE, FALSE};

	CrankVecBool2	c;

	crank_vec_bool2_not (&a, &c);

  	g_assert (c.x == FALSE);
  	g_assert (c.y == TRUE);
}

void	test_2_any (void)
{
	CrankVecBool2	a = {FALSE, FALSE};
	CrankVecBool2	b = {FALSE, TRUE};

  	g_assert (crank_vec_bool2_get_any (&a) == FALSE);
  	g_assert (crank_vec_bool2_get_any (&b) == TRUE);
}

void	test_2_all (void)
{
	CrankVecBool2	a = {TRUE, FALSE};
	CrankVecBool2	b = {TRUE, TRUE};

  	g_assert (crank_vec_bool2_get_all (&a) == FALSE);
  	g_assert (crank_vec_bool2_get_all (&b) == TRUE);
}

void	test_2_equal (void)
{
	CrankVecBool2	a = {TRUE, TRUE};
	CrankVecBool2	b = {TRUE, TRUE};
	CrankVecBool2	c = {TRUE, FALSE};
	
	g_assert (  crank_vec_bool2_equal (&a, &b));
	g_assert (! crank_vec_bool2_equal (&a, &c));
}

void	test_2_hash (void)
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




void	test_n_get (void)
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

void	test_n_and (void)
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

void	test_n_or (void)
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

void	test_n_xor (void)
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

void	test_n_not (void)
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

void	test_n_any (void)
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

void	test_n_all (void)
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


void	main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/vec/bool/2/get", test_2_get);
	g_test_add_func ("/crank/base/vec/bool/2/and", test_2_and);
	g_test_add_func ("/crank/base/vec/bool/2/or", test_2_or);
	g_test_add_func ("/crank/base/vec/bool/2/xor", test_2_xor);
	g_test_add_func ("/crank/base/vec/bool/2/not", test_2_not);
	g_test_add_func ("/crank/base/vec/bool/2/any", test_2_any);
	g_test_add_func ("/crank/base/vec/bool/2/all", test_2_all);
	
	g_test_add_func ("/crank/base/vec/bool/n/get", test_n_get);
	g_test_add_func ("/crank/base/vec/bool/n/and", test_n_and);
	g_test_add_func ("/crank/base/vec/bool/n/or", test_n_or);
	g_test_add_func ("/crank/base/vec/bool/n/xor", test_n_xor);
	g_test_add_func ("/crank/base/vec/bool/n/not", test_n_not);
	g_test_add_func ("/crank/base/vec/bool/n/any", test_n_any);
	g_test_add_func ("/crank/base/vec/bool/n/all", test_n_all);
	
	g_test_run ();
}
