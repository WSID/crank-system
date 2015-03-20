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

static  GType   _crank_test_rand_g_type_pool[9] = {
	 G_TYPE_UCHAR,
	 G_TYPE_CHAR,
	 G_TYPE_INT,
	 G_TYPE_UINT,
	 G_TYPE_LONG,
	 G_TYPE_ULONG,
	 G_TYPE_INT64,
	 G_TYPE_UINT64,
	 G_TYPE_BOOLEAN
};

GType	   _crank_test_rand_g_type (void);

gboolean  subject_function (gint a, gint b);


void	test_func_type_new (void);
void	test_func_type_new_with_types (void);

void	test_func_type_hash (void);
void	test_func_type_equal (void);
void	test_func_type_to_string (void);

void	test_func_holder_new (void);


gint
main (gint   argc,
      gchar *argv[])
{
  g_test_init (&argc, &argv, NULL);
	
  g_test_add_func ("/wsid/crank/base/functype/new",
      test_func_type_new);
	
  g_test_add_func ("/wsid/crank/base/functype/newwithtypes",
      test_func_type_new_with_types);

	g_test_add_func ("/wsid/crank/base/functype/hash",
          test_func_type_hash);
	
	g_test_add_func ("/wsid/crank/base/functype/equal",
          test_func_type_equal);
	
	g_test_add_func ("/wsid/crank/base/functype/tostring",
          test_func_type_to_string);

  g_test_add_func ("/wsid/crank/base/funcholder",
      test_func_holder_new);

  g_test_run ();

  return 0;
}




GType
_crank_test_rand_g_type (void)
{
	return _crank_test_rand_g_type_pool[ g_test_rand_int_range (0, 9) ];
}




gboolean
subject_function (gint a, gint b)
{
  return (a % b) == 0;
}



void
test_func_type_new (void)
{
	GType*  param_types;
	guint   param_length;
  
	CrankFuncType* ftype = crank_func_type_new (
		G_TYPE_BOOLEAN,
		G_TYPE_INT,
		G_TYPE_CHAR,
		G_TYPE_NONE);

	g_assert (G_TYPE_BOOLEAN == crank_func_type_get_return_type (ftype));
	g_assert (G_TYPE_INT == crank_func_type_get_param_type (ftype, 0));
	g_assert (G_TYPE_CHAR == crank_func_type_get_param_type (ftype, 1));
	g_assert (G_TYPE_NONE == crank_func_type_get_param_type (ftype, 2));

	g_assert (2 == crank_func_type_get_nparam_types (ftype));

	// Tests crank_func_type_get_param_types ()
	param_types = crank_func_type_get_param_types(ftype, &param_length);

	g_assert_cmpuint (2, ==, param_length);
	g_assert (G_TYPE_INT == param_types[0]);
	g_assert (G_TYPE_CHAR == param_types[1]);

	crank_func_type_unref (ftype);
}

void
test_func_type_new_with_types (void) {
	GType   param_types_in[2];
	
	GType*  param_types;
	guint   param_length;

	param_types_in[0] = G_TYPE_INT;
	param_types_in[1] = G_TYPE_CHAR;
  
	CrankFuncType* ftype = crank_func_type_new_with_types (
		G_TYPE_BOOLEAN,
        param_types_in, 2);

	g_assert (G_TYPE_BOOLEAN == crank_func_type_get_return_type (ftype));
	g_assert (G_TYPE_INT == crank_func_type_get_param_type (ftype, 0));
	g_assert (G_TYPE_CHAR == crank_func_type_get_param_type (ftype, 1));
	g_assert (G_TYPE_NONE == crank_func_type_get_param_type (ftype, 2));

	g_assert (2 == crank_func_type_get_nparam_types (ftype));

	// Tests crank_func_type_get_param_types ()
	param_types = crank_func_type_get_param_types(ftype, &param_length);

	g_assert_cmpuint (2, ==, param_length);
	g_assert (G_TYPE_INT == param_types[0]);
	g_assert (G_TYPE_CHAR == param_types[1]);

	crank_func_type_unref (ftype);
}

void
test_func_type_hash (void)
{
	CrankFuncType* ftype_a;
	CrankFuncType* ftype_b;
	
	GType   r_type;
	GType   p_types[2];

	guint hash_a;
	guint hash_b;

	r_type = _crank_test_rand_g_type ();
	p_types[0] = _crank_test_rand_g_type ();
	p_types[1] = _crank_test_rand_g_type ();

	ftype_a = crank_func_type_new_with_types (r_type, p_types, 2);
	ftype_b = crank_func_type_new_with_types (r_type, p_types, 2);

	hash_a = crank_func_type_hash (ftype_a);
	hash_b = crank_func_type_hash (ftype_b);

	g_assert_cmpuint (hash_a, ==, hash_b);
}

void
test_func_type_equal (void)
{
	CrankFuncType* ftype_a;
	CrankFuncType* ftype_b;
	
	GType   r_type;
	GType   p_types[2];

	guint hash_a;
	guint hash_b;

	r_type = _crank_test_rand_g_type ();
	p_types[0] = _crank_test_rand_g_type ();
	p_types[1] = _crank_test_rand_g_type ();

	ftype_a = crank_func_type_new_with_types (r_type, p_types, 2);
	ftype_b = crank_func_type_new_with_types (r_type, p_types, 2);

	g_assert (crank_func_type_equal (ftype_a, ftype_b));
}

void
test_func_type_to_string (void)
{
	CrankFuncType* ftype;

	ftype = crank_func_type_new (   G_TYPE_BOOLEAN,
    		G_TYPE_INT,
    		G_TYPE_CHAR,
    		G_TYPE_NONE );
	
	g_assert_cmpstr ("gboolean (gint, gchar)", ==, crank_func_type_to_string (ftype));
}

void
test_func_holder_new (void)
{
  
  CrankFuncHolder* holder = crank_func_holder_new (
      G_CALLBACK(subject_function), NULL,
      G_TYPE_BOOLEAN,
      G_TYPE_INT,
      G_TYPE_INT,
      G_TYPE_NONE);
  
  crank_func_holder_free (holder);
  
}
