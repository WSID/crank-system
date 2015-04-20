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

typedef struct _FixtureFuncHolder {
  	CrankFuncHolder*	holder;
  	GType				types_int[2];
  	GType				types_float[2];
  	GType				types_string[2];
  	GClosure*			closure_int;
  	GClosure*			closure_float;
  	GClosure*			closure_string;
} FixtureFuncHolder;

gint	subject_function_int (const gint a, const gint b);
gfloat	subject_function_float (const gfloat a, const gfloat b);
gchar*	subject_function_string (const gchar* a, const gchar* b);

void	test_func_type_new (void);
void	test_func_type_new_with_types (void);

void	test_func_type_hash (void);
void	test_func_type_equal (void);
void	test_func_type_to_string (void);

void	test_func_type_compatible_to (void);
void	test_func_type_compatible_to_param_size (void);

void	test_func_type_arg_match_exactually (void);
void	test_func_type_arg_match (void);
void	test_func_type_arg_match_transformable (void);

void	test_func_holder_setup (	FixtureFuncHolder* 	fixture,
							 		gconstpointer			userdata	);
void	test_func_holder_teardown (	FixtureFuncHolder*	fixture,
                                	gconstpointer          	userdata	);

void	test_func_holder_setget_name (void);

void	test_func_holder_get (		FixtureFuncHolder*	fixture,
						   			gconstpointer			userdata	);
void	test_func_holder_invoke (	FixtureFuncHolder*	fixture,
							  		gconstpointer			userdata	);


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
	
	g_test_add_func ("/wsid/crank/base/functype/compatible/basic",
          test_func_type_compatible_to);
	
	g_test_add_func ("/wsid/crank/base/functype/compatible/paramsize",
          test_func_type_compatible_to_param_size);
	
	g_test_add_func ("/wsid/crank/base/functype/argmatch/exactually",
          test_func_type_arg_match_exactually);
          
	g_test_add_func ("/wsid/crank/base/functype/argmatch/normal",
          test_func_type_arg_match);
          
	g_test_add_func ("/wsid/crank/base/functype/argmatch/transformable",
          test_func_type_arg_match_transformable);
    
    g_test_add_func ("/wsid/crank/base/funcholder/setget_name",
    		test_func_holder_setget_name);

	g_test_add ("/wsid/crank/base/funcholder/get",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_get,
			test_func_holder_teardown);

	g_test_add ("/wsid/crank/base/funcholder/invoke",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_invoke,
			test_func_holder_teardown);

  g_test_run ();

  return 0;
}




GType
_crank_test_rand_g_type (void)
{
	return _crank_test_rand_g_type_pool[ g_test_rand_int_range (0, 9) ];
}




gint
subject_function_int (const gint a, const gint b)
{
  	g_test_message ("invoked int function (%d, %d)", a, b);
  	return a + b;
}

gfloat
subject_function_float (const gfloat a, const gfloat b)
{
  	g_test_message ("invoked float function (%f, %f)", a, b);
  	return a + b;
}

gchar*
subject_function_string (const gchar* a, const gchar* b)
{
	guint 	a_len;
  	guint 	b_len;

  	gchar*	result;

  	g_test_message ("invoked string function (%s, %s)", a, b);
  	a_len = strlen (a);
  	b_len = strlen (b);

  	result = g_new (gchar, a_len + b_len + 1);

  	memcpy (result, a, a_len);
  	memcpy (result + a_len, b, b_len);
  	result[a_len + b_len] = '\0';

  	return result;
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
	
	crank_func_type_unref (ftype_a);
	crank_func_type_unref (ftype_b);
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
	
	crank_func_type_unref (ftype_a);
	crank_func_type_unref (ftype_b);
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

	crank_func_type_unref (ftype);
}


void
test_func_type_compatible_to (void)
{
	CrankFuncType* ftype_from;
	CrankFuncType* ftype_to;

	ftype_from = crank_func_type_new (
        G_TYPE_BINDING,
        G_TYPE_OBJECT,
        G_TYPE_NONE);

	ftype_to = crank_func_type_new (
        G_TYPE_OBJECT,
        G_TYPE_BINDING,
        G_TYPE_NONE);

	g_assert (crank_func_type_compatible_to (ftype_from, ftype_to));

	crank_func_type_unref (ftype_from);
	crank_func_type_unref (ftype_to);
}

void
test_func_type_compatible_to_param_size (void)
{
	CrankFuncType* ftype_from;
	CrankFuncType* ftype_to;

	ftype_from = crank_func_type_new (
        G_TYPE_BOOLEAN,
        G_TYPE_INT,
        G_TYPE_NONE);

	ftype_to = crank_func_type_new (
	        G_TYPE_BOOLEAN,
	        G_TYPE_INT,
	        G_TYPE_INT,
	        G_TYPE_NONE);

	g_assert (crank_func_type_compatible_to (ftype_from, ftype_to));

	crank_func_type_unref (ftype_from);
	crank_func_type_unref (ftype_to);
}

void
test_func_type_arg_match_exactually (void)
{
	CrankFuncType* ftype;
	GType types_a[] = {G_TYPE_INT, G_TYPE_FLOAT};
	GType types_b[] = {G_TYPE_INT, G_TYPE_DOUBLE};
	GType types_c[] = {G_TYPE_INT};
	GType types_d[] = {G_TYPE_INT, G_TYPE_FLOAT, G_TYPE_BOOLEAN};

	ftype = crank_func_type_new (
        G_TYPE_BOOLEAN,
        G_TYPE_INT,
        G_TYPE_FLOAT,
        G_TYPE_NONE);

	g_assert (crank_func_type_arg_match_exactually (ftype, types_a, 2));
	g_assert (! crank_func_type_arg_match_exactually (ftype, types_b, 2));
	g_assert (! crank_func_type_arg_match_exactually (ftype, types_c, 1));
	g_assert (! crank_func_type_arg_match_exactually (ftype, types_d, 3));

	crank_func_type_unref (ftype);
}

void
test_func_type_arg_match (void)
{
	CrankFuncType* ftype;
	GType types_a[] = {G_TYPE_OBJECT, G_TYPE_INT};
	GType types_b[] = {G_TYPE_INT, G_TYPE_DOUBLE};
	GType types_c[] = {G_TYPE_BINDING, G_TYPE_INT};

	ftype = crank_func_type_new (
        G_TYPE_BOOLEAN,
        G_TYPE_OBJECT,
        G_TYPE_INT,
        G_TYPE_NONE);

	g_assert (crank_func_type_arg_match (ftype, types_a, 2));
	g_assert (! crank_func_type_arg_match (ftype, types_b, 2));
	g_assert (crank_func_type_arg_match (ftype, types_c, 2));

	crank_func_type_unref (ftype);
}


void
test_func_type_arg_match_transformable (void)
{
	CrankFuncType* ftype;
	GType types_a[] = {G_TYPE_OBJECT, G_TYPE_INT};
	GType types_b[] = {G_TYPE_OBJECT, G_TYPE_DOUBLE};
	GType types_c[] = {G_TYPE_BINDING, G_TYPE_FLOAT};
	GType types_d[] = {G_TYPE_STRING, G_TYPE_FLOAT};

	ftype = crank_func_type_new (
        G_TYPE_BOOLEAN,
        G_TYPE_OBJECT,
        G_TYPE_INT,
        G_TYPE_NONE);

	g_assert (crank_func_type_arg_match_transformable (ftype, types_a, 2));
	g_assert (crank_func_type_arg_match_transformable (ftype, types_b, 2));
	g_assert (crank_func_type_arg_match_transformable (ftype, types_c, 2));
	g_assert (! crank_func_type_arg_match_transformable (ftype, types_d, 2));

	crank_func_type_unref (ftype);
}

void
test_func_holder_setget_name	(void)
{
	GQuark				holder_name = g_quark_from_string ("test-holder");
	CrankFuncHolder*	holder = crank_func_holder_new ("test-holder");
	
	g_assert_cmpstr (crank_func_holder_get_name (holder), ==, "test-holder");
	g_assert (crank_func_holder_get_qname (holder) == holder_name);
	
	holder_name = g_quark_from_string ("another-name");
	crank_func_holder_set_name (holder, "another-name");
	
	g_assert_cmpstr (crank_func_holder_get_name (holder), ==, "another-name");
	g_assert (crank_func_holder_get_qname (holder) == holder_name);
	
	holder_name = g_quark_from_string ("last-chance");
	crank_func_holder_set_qname (holder, holder_name);
	
	g_assert_cmpstr (crank_func_holder_get_name (holder), ==, "last-chance");
	g_assert (crank_func_holder_get_qname (holder) == holder_name);
}

void
test_func_holder_setup (	FixtureFuncHolder* 	fixture,
							gconstpointer		userdata	)
{
  	fixture->holder =	crank_func_holder_new ("test-holder");

  	fixture->types_int[0] = G_TYPE_INT;
  	fixture->types_int[1] = G_TYPE_INT;

  	fixture->types_float[0] = G_TYPE_FLOAT;
  	fixture->types_float[1] = G_TYPE_FLOAT;

  	fixture->types_string[0] = G_TYPE_STRING;
  	fixture->types_string[1] = G_TYPE_STRING;

  	fixture->closure_int = 		g_cclosure_new (
  			(GCallback)subject_function_int, NULL, NULL);

  	fixture->closure_float = 	g_cclosure_new (
  			(GCallback)subject_function_float, NULL, NULL);
  
  	fixture->closure_string = 	g_cclosure_new (
  			(GCallback)subject_function_string, NULL, NULL);

  	g_closure_set_marshal (fixture->closure_int, g_cclosure_marshal_generic);
  	g_closure_set_marshal (fixture->closure_float, g_cclosure_marshal_generic);
  	g_closure_set_marshal (fixture->closure_string, g_cclosure_marshal_generic);

  	crank_func_holder_set (fixture->holder, fixture->types_int, 2, fixture->closure_int);
  	crank_func_holder_set (fixture->holder, fixture->types_float, 2, fixture->closure_float);
  	crank_func_holder_set (fixture->holder, fixture->types_string, 2, fixture->closure_string);
}

void
test_func_holder_teardown (	FixtureFuncHolder*	fixture,
						   	gconstpointer		userdata	)
{
	crank_func_holder_unref (fixture->holder);
  	g_closure_unref (fixture->closure_int);
  	g_closure_unref (fixture->closure_float);
  	g_closure_unref (fixture->closure_string);
}

void
test_func_holder_get (	FixtureFuncHolder*	fixture,
					  	gconstpointer		userdata	)
{
  	g_assert (crank_func_holder_get (fixture->holder, fixture->types_int, 2) ==
			 	fixture->closure_int);
  	g_assert (crank_func_holder_get (fixture->holder, fixture->types_float, 2) ==
			 	fixture->closure_float);
  	g_assert (crank_func_holder_get (fixture->holder, fixture->types_string, 2) ==
			 	fixture->closure_string);
}

void
test_func_holder_invoke (	FixtureFuncHolder*	fixture,
						 	gconstpointer		userdata	)
{
  	GValue				value_result = G_VALUE_INIT;
  	GValue				value_arg[2] = {G_VALUE_INIT, G_VALUE_INIT};

  	g_value_init (&value_result, G_TYPE_INT);
  	g_value_init (value_arg, G_TYPE_INT);
  	g_value_init (value_arg + 1, G_TYPE_INT);

  	g_value_set_int (value_arg, 3);
  	g_value_set_int (value_arg + 1, 5);

  	crank_func_holder_invoke (fixture->holder, &value_result, 2, value_arg, NULL);

  	g_assert_cmpint (g_value_get_int (&value_result), ==, 8);

  	g_value_unset (&value_result);
  	g_value_unset (value_arg);
  	g_value_unset (value_arg + 1);

  	g_value_init (&value_result, G_TYPE_FLOAT);
  	g_value_init (value_arg, G_TYPE_FLOAT);
  	g_value_init (value_arg + 1, G_TYPE_FLOAT);

  	g_value_set_float (value_arg, 27.81f);
  	g_value_set_float (value_arg + 1, 22.19f);

  	crank_func_holder_invoke (fixture->holder, &value_result, 2, value_arg, NULL);

  	g_assert_cmpfloat (g_value_get_float (&value_result), ==, 50.00f);

  	g_value_unset (&value_result);
  	g_value_unset (value_arg);
  	g_value_unset (value_arg + 1);

  	g_value_init (&value_result, G_TYPE_STRING);
  	g_value_init (value_arg, G_TYPE_STRING);
  	g_value_init (value_arg + 1, G_TYPE_STRING);

  	g_value_set_string (value_arg, "This cake ");
  	g_value_set_string (value_arg + 1, "is a lie!");

  	crank_func_holder_invoke (fixture->holder, &value_result, 2, value_arg, NULL);

  	g_assert_cmpstr (g_value_get_string (&value_result), ==, "This cake is a lie!");
}
