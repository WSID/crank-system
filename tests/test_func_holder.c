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
  	CrankFuncType*		ftype_int;
  	CrankFuncType*		ftype_float;
  	CrankFuncType*		ftype_string;
  	GClosure*			closure_int;
  	GClosure*			closure_float;
  	GClosure*			closure_string;
} FixtureFuncHolder;

gint	subject_function_int (const gint a, const gint b);
gfloat	subject_function_float (const gfloat a, const gfloat b);
gchar*	subject_function_string (const gchar* a, const gchar* b);

gint	subject_mul_int		(const gint a,		const gint b);
gfloat	subject_mul_float	(const gfloat a,	const gfloat b);

gint	subject_neg_int		(const gint a);
gfloat	subject_neg_float	(const gfloat a);

enum FixtureFuncBookIndex {
	FIXTURE_FUNC_ADD,
	FIXTURE_FUNC_MUL,
	FIXTURE_FUNC_NEG
};

typedef struct _FixtureFuncBook {
	CrankFuncBook*		book;
	
	CrankFuncHolder*	holder_add;
	CrankFuncHolder*	holder_mul;
	CrankFuncHolder*	holder_neg;
	
} FixtureFuncBook;

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
							 		gconstpointer		userdata	);
void	test_func_holder_teardown (	FixtureFuncHolder*	fixture,
                                	gconstpointer       userdata	);



void	test_func_holder_setget_name (void);

void	test_func_holder_get (		FixtureFuncHolder*	fixture,
						   			gconstpointer		userdata	);
						   			
void	test_func_holder_get_by_param_types (		FixtureFuncHolder*	fixture,
						   							gconstpointer		userdata	);
						   			
void	test_func_holder_remove (	FixtureFuncHolder*	fixture,
							  		gconstpointer		userdata	);
							  		
void	test_func_holder_remove_by_param_types (	FixtureFuncHolder*	fixture,
							  						gconstpointer		userdata	);
							  		
void	test_func_holder_lookup_return_type (	FixtureFuncHolder*	fixture,
							  					gconstpointer		userdata	);
							  		
void	test_func_holder_invoke (	FixtureFuncHolder*	fixture,
							  		gconstpointer		userdata	);
							  		
void	test_func_holder_invokev (	FixtureFuncHolder*	fixture,
							  		gconstpointer		userdata	);
							  		
void	test_func_holder_invoke_overwrite (	FixtureFuncHolder*	fixture,
							  				gconstpointer		userdata	);
							  		
void	test_func_holder_setup_set_func (	FixtureFuncHolder* 	fixture,
							 				gconstpointer		userdata	);



void	test_func_book_setup (		FixtureFuncBook*	fixture,
									gconstpointer		userdata	);

void	test_func_book_teardown (	FixtureFuncBook*	fixture,
									gconstpointer		userdata	);

void	test_func_book_get_name	(void);

void	test_func_book_get (	FixtureFuncBook*	fixture,
								gconstpointer		userdata	);

void	test_func_book_index_of (	FixtureFuncBook*	fixture,
									gconstpointer		userdata	);

void	test_func_book_get_by_name (	FixtureFuncBook*	fixture,
										gconstpointer		userdata	);
										
void	test_func_book_get_by_qname (	FixtureFuncBook*	fixture,
										gconstpointer		userdata	);
										
void	test_func_book_remove (	FixtureFuncBook*	fixture,
								gconstpointer		userdata	);
										
void	test_func_book_remove_by_name (	FixtureFuncBook*	fixture,
										gconstpointer		userdata	);
										
void	test_func_book_remove_by_qname (	FixtureFuncBook*	fixture,
											gconstpointer		userdata	);
								
void	test_func_book_invoke (	FixtureFuncBook*	fixture,
								gconstpointer		userdata	);
								
void	test_func_book_invoke_name (	FixtureFuncBook*	fixture,
										gconstpointer		userdata	);

void	test_func_book_invoke_qname (	FixtureFuncBook*	fixture,
										gconstpointer		userdata	);
								
void	test_func_book_invoke_overwrite (	FixtureFuncBook*	fixture,
											gconstpointer		userdata	);
								
void	test_func_book_invoke_overwrite_name (	FixtureFuncBook*	fixture,
												gconstpointer		userdata	);

void	test_func_book_invoke_overwrite_qname (	FixtureFuncBook*	fixture,
												gconstpointer		userdata	);
								
void	test_func_book_invokev (	FixtureFuncBook*	fixture,
									gconstpointer		userdata	);

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
			
	g_test_add ("/wsid/crank/base/funcholder/get_by_param_types",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_get_by_param_types,
			test_func_holder_teardown);
			
	g_test_add ("/wsid/crank/base/funcholder/remove",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_remove,
			test_func_holder_teardown);
			
	g_test_add ("/wsid/crank/base/funcholder/remove_by_param_types",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_remove_by_param_types,
			test_func_holder_teardown);

	g_test_add ("/wsid/crank/base/funcholder/lookup_return_type",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_lookup_return_type,
			test_func_holder_teardown);
			
	g_test_add ("/wsid/crank/base/funcholder/invoke",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_invoke,
			test_func_holder_teardown);
			
	g_test_add ("/wsid/crank/base/funcholder/invokev",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_invokev,
			test_func_holder_teardown);
			
	g_test_add ("/wsid/crank/base/funcholder/invoke_overwrite",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup,
			test_func_holder_invoke_overwrite,
			test_func_holder_teardown);
	
	g_test_add ("/wsid/crank/base/funcholder/setfunc",
			FixtureFuncHolder,
			NULL,
			test_func_holder_setup_set_func,
			test_func_holder_invoke,
			test_func_holder_teardown);
			
	g_test_add_func ("/wsid/crank/base/funcbook/getname",
			test_func_book_get_name);

	g_test_add ("/wsid/crank/base/funcbook/get",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_get,
			test_func_book_teardown);

	g_test_add ("/wsid/crank/base/funcbook/index_of",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_index_of,
			test_func_book_teardown);

	g_test_add ("/wsid/crank/base/funcbook/get_by_name",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_get_by_name,
			test_func_book_teardown);

	g_test_add ("/wsid/crank/base/funcbook/get_by_qname",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_get_by_qname,
			test_func_book_teardown);
			
	g_test_add ("/wsid/crank/base/funcbook/remove/index",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_remove,
			test_func_book_teardown);
			
	g_test_add ("/wsid/crank/base/funcbook/remove/name",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_remove_by_name,
			test_func_book_teardown);
			
	g_test_add ("/wsid/crank/base/funcbook/remove/qname",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_remove_by_qname,
			test_func_book_teardown);
			
	g_test_add ("/wsid/crank/base/funcbook/invoke/index",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_invoke,
			test_func_book_teardown);

	g_test_add ("/wsid/crank/base/funcbook/invoke/name",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_invoke_name,
			test_func_book_teardown);
			
	g_test_add ("/wsid/crank/base/funcbook/invoke/qname",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_invoke_qname,
			test_func_book_teardown);
			
	g_test_add ("/wsid/crank/base/funcbook/invoke_overwrite/index",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_invoke_overwrite,
			test_func_book_teardown);

	g_test_add ("/wsid/crank/base/funcbook/invoke_overwrite/name",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_invoke_overwrite_name,
			test_func_book_teardown);
			
	g_test_add ("/wsid/crank/base/funcbook/invoke_overwrite/qname",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_invoke_overwrite_qname,
			test_func_book_teardown);

			
	g_test_add ("/wsid/crank/base/funcbook/invokev/index",
			FixtureFuncBook,
			NULL,
			test_func_book_setup,
			test_func_book_invokev,
			test_func_book_teardown);
			
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

gint
subject_mul_int (const gint a, const gint b)
{
	return a * b;
}

gfloat
subject_mul_float (const gfloat a, const gfloat b)
{
	return a * b;
}


gint
subject_neg_int (const gint a)
{
	return -a;
}

gfloat
subject_neg_float (const gfloat a)
{
	return -a;
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
  	
  	fixture->ftype_int = crank_func_type_new_with_types (
  			G_TYPE_INT, fixture->types_int, 2	);
  			
  	fixture->ftype_float = crank_func_type_new_with_types (
  			G_TYPE_FLOAT, fixture->types_float, 2	);
  			
  	fixture->ftype_string = crank_func_type_new_with_types (
  			G_TYPE_STRING, fixture->types_string, 2	);

  	fixture->closure_int = 		g_cclosure_new (
  			(GCallback)subject_function_int, NULL, NULL);

  	fixture->closure_float = 	g_cclosure_new (
  			(GCallback)subject_function_float, NULL, NULL);
  
  	fixture->closure_string = 	g_cclosure_new (
  			(GCallback)subject_function_string, NULL, NULL);

  	g_closure_set_marshal (fixture->closure_int, g_cclosure_marshal_generic);
  	g_closure_set_marshal (fixture->closure_float, g_cclosure_marshal_generic);
  	g_closure_set_marshal (fixture->closure_string, g_cclosure_marshal_generic);

  	crank_func_holder_set (fixture->holder, fixture->ftype_int, fixture->closure_int);
  	crank_func_holder_set (fixture->holder, fixture->ftype_float, fixture->closure_float);
  	crank_func_holder_set (fixture->holder, fixture->ftype_string, fixture->closure_string);
}

void
test_func_holder_teardown (	FixtureFuncHolder*	fixture,
						   	gconstpointer		userdata	)
{
	crank_func_holder_unref (fixture->holder);
	crank_func_type_unref (fixture->ftype_int);
	crank_func_type_unref (fixture->ftype_float);
	crank_func_type_unref (fixture->ftype_string);
  	g_closure_unref (fixture->closure_int);
  	g_closure_unref (fixture->closure_float);
  	g_closure_unref (fixture->closure_string);
}

void
test_func_holder_get (	FixtureFuncHolder*	fixture,
					  	gconstpointer		userdata	)
{
	CrankFuncType*	ftype_int = crank_func_type_new (	G_TYPE_INT,
			G_TYPE_INT,
			G_TYPE_INT,
			G_TYPE_NONE	);
	
	CrankFuncType*	ftype_float = crank_func_type_new (	G_TYPE_FLOAT,
			G_TYPE_FLOAT,
			G_TYPE_FLOAT,
			G_TYPE_NONE	);
			
	CrankFuncType*	ftype_string = crank_func_type_new (	G_TYPE_STRING,
			G_TYPE_STRING,
			G_TYPE_STRING,
			G_TYPE_NONE	);
	
	g_assert ( crank_func_holder_get (fixture->holder, ftype_int)
				==
				fixture->closure_int);
				
	g_assert ( crank_func_holder_get (fixture->holder, ftype_float)
				==
				fixture->closure_float);
				
	g_assert ( crank_func_holder_get (fixture->holder, ftype_string)
				==
				fixture->closure_string);
	
	crank_func_type_unref (ftype_int);
	crank_func_type_unref (ftype_float);
	crank_func_type_unref (ftype_string);
}

void
test_func_holder_get_by_param_types (	FixtureFuncHolder*	fixture,
					  					gconstpointer		userdata	)
{
  	g_assert (
  			crank_func_holder_get_by_param_types (
  					fixture->holder, fixture->types_int, 2)
  			==
			fixture->closure_int	);
	
  	g_assert (
  			crank_func_holder_get_by_param_types (
  					fixture->holder, fixture->types_float, 2)
  			==
			fixture->closure_float	);

  	g_assert (
  			crank_func_holder_get_by_param_types (
  					fixture->holder, fixture->types_string, 2)
  			==
			fixture->closure_string	);
}

void
test_func_holder_remove (	FixtureFuncHolder*	fixture,
					  		gconstpointer		userdata	)
{
	CrankFuncType*	ftype_int = crank_func_type_new (	G_TYPE_INT,
			G_TYPE_INT,
			G_TYPE_INT,
			G_TYPE_NONE	);
	
	CrankFuncType*	ftype_float = crank_func_type_new (	G_TYPE_FLOAT,
			G_TYPE_FLOAT,
			G_TYPE_FLOAT,
			G_TYPE_NONE	);
			
	CrankFuncType*	ftype_string = crank_func_type_new (	G_TYPE_STRING,
			G_TYPE_STRING,
			G_TYPE_STRING,
			G_TYPE_NONE	);
			
  	g_assert (crank_func_holder_remove (fixture->holder, ftype_int));
  	g_assert (crank_func_holder_remove (fixture->holder, ftype_float));
  	g_assert (! crank_func_holder_remove (fixture->holder, ftype_int));
  	g_assert (crank_func_holder_remove (fixture->holder, ftype_string));
  	
	crank_func_type_unref (ftype_int);
	crank_func_type_unref (ftype_float);
	crank_func_type_unref (ftype_string);
}

void
test_func_holder_remove_by_param_types (	FixtureFuncHolder*	fixture,
					  						gconstpointer		userdata	)
{
  	g_assert (crank_func_holder_remove_by_param_types (fixture->holder, fixture->types_int, 2));
  	g_assert (crank_func_holder_remove_by_param_types (fixture->holder, fixture->types_float, 2));
  	g_assert (! crank_func_holder_remove_by_param_types (fixture->holder, fixture->types_int, 2));
  	g_assert (crank_func_holder_remove_by_param_types (fixture->holder, fixture->types_string, 2));
}

void
test_func_holder_lookup_return_type (	FixtureFuncHolder*	fixture,
										gconstpointer		userdata	)
{
	g_assert (crank_func_holder_lookup_return_type (fixture->holder, fixture->types_int, 2)
			== G_TYPE_INT);
	g_assert (crank_func_holder_lookup_return_type (fixture->holder, fixture->types_float, 2)
			== G_TYPE_FLOAT);
	g_assert (crank_func_holder_lookup_return_type (fixture->holder, fixture->types_string, 2)
			== G_TYPE_STRING);
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


void
test_func_holder_invokev (	FixtureFuncHolder*	fixture,
						 	gconstpointer		userdata	)
{
  	GValue	value_result = G_VALUE_INIT;
  	GValue	value_a = G_VALUE_INIT;
  	GValue	value_b = G_VALUE_INIT;

  	g_value_init (&value_result, G_TYPE_INT);
  	g_value_init (&value_a, G_TYPE_INT);
  	g_value_init (&value_b, G_TYPE_INT);

  	g_value_set_int (&value_a, 3);
  	g_value_set_int (&value_b, 5);

  	crank_func_holder_invokev (fixture->holder, &value_result, NULL, 2, &value_a, &value_b);

  	g_assert_cmpint (g_value_get_int (&value_result), ==, 8);

  	g_value_unset (&value_result);
  	g_value_unset (&value_a);
  	g_value_unset (&value_b);

  	g_value_init (&value_result, G_TYPE_FLOAT);
  	g_value_init (&value_a, G_TYPE_FLOAT);
  	g_value_init (&value_b, G_TYPE_FLOAT);

  	g_value_set_float (&value_a, 27.81f);
  	g_value_set_float (&value_b, 22.19f);

  	crank_func_holder_invokev (fixture->holder, &value_result, NULL, 2, &value_a, &value_b);

  	g_assert_cmpfloat (g_value_get_float (&value_result), ==, 50.00f);

  	g_value_unset (&value_result);
  	g_value_unset (&value_a);
  	g_value_unset (&value_b);

  	g_value_init (&value_result, G_TYPE_STRING);
  	g_value_init (&value_a, G_TYPE_STRING);
  	g_value_init (&value_b, G_TYPE_STRING);

  	g_value_set_string (&value_a, "This cake ");
  	g_value_set_string (&value_b, "is a lie!");

  	crank_func_holder_invokev (fixture->holder, &value_result, NULL, 2, &value_a, &value_b);

  	g_assert_cmpstr (g_value_get_string (&value_result), ==, "This cake is a lie!");
}


void
test_func_holder_invoke_overwrite (	FixtureFuncHolder*	fixture,
						 	gconstpointer		userdata	)
{
  	GValue				value_result = G_VALUE_INIT;
  	GValue				value_arg[2] = {G_VALUE_INIT, G_VALUE_INIT};

  	g_value_init (value_arg, G_TYPE_INT);
  	g_value_init (value_arg + 1, G_TYPE_INT);

  	g_value_set_int (value_arg, 3);
  	g_value_set_int (value_arg + 1, 5);

  	crank_func_holder_invoke_overwrite (fixture->holder, &value_result, 2, value_arg, NULL);

  	g_assert_cmpint (g_value_get_int (&value_result), ==, 8);

  	g_value_unset (value_arg);
  	g_value_unset (value_arg + 1);

  	g_value_init (value_arg, G_TYPE_FLOAT);
  	g_value_init (value_arg + 1, G_TYPE_FLOAT);

  	g_value_set_float (value_arg, 27.81f);
  	g_value_set_float (value_arg + 1, 22.19f);

  	crank_func_holder_invoke_overwrite (fixture->holder, &value_result, 2, value_arg, NULL);

  	g_assert_cmpfloat (g_value_get_float (&value_result), ==, 50.00f);

  	g_value_unset (value_arg);
  	g_value_unset (value_arg + 1);

  	g_value_init (value_arg, G_TYPE_STRING);
  	g_value_init (value_arg + 1, G_TYPE_STRING);

  	g_value_set_string (value_arg, "This cake ");
  	g_value_set_string (value_arg + 1, "is a lie!");

  	crank_func_holder_invoke_overwrite (fixture->holder, &value_result, 2, value_arg, NULL);

  	g_assert_cmpstr (g_value_get_string (&value_result), ==, "This cake is a lie!");
}
void
test_func_holder_setup_set_func (	FixtureFuncHolder* 	fixture,
									gconstpointer		userdata	)
{
  	fixture->holder =	crank_func_holder_new ("test-holder");

  	fixture->types_int[0] = G_TYPE_INT;
  	fixture->types_int[1] = G_TYPE_INT;

  	fixture->types_float[0] = G_TYPE_FLOAT;
  	fixture->types_float[1] = G_TYPE_FLOAT;

  	fixture->types_string[0] = G_TYPE_STRING;
  	fixture->types_string[1] = G_TYPE_STRING;
  	
  	fixture->ftype_int = crank_func_type_new_with_types (
  			G_TYPE_INT, fixture->types_int, 2	);
  			
  	fixture->ftype_float = crank_func_type_new_with_types (
  			G_TYPE_FLOAT, fixture->types_float, 2	);
  			
  	fixture->ftype_string = crank_func_type_new_with_types (
  			G_TYPE_STRING, fixture->types_string, 2	);

  	fixture->closure_int = 		g_cclosure_new (
  			(GCallback)subject_function_int, NULL, NULL);

  	fixture->closure_float = 	g_cclosure_new (
  			(GCallback)subject_function_float, NULL, NULL);
  
  	fixture->closure_string = 	g_cclosure_new (
  			(GCallback)subject_function_string, NULL, NULL);

  	crank_func_holder_set_func (fixture->holder, fixture->ftype_int,
  			(CrankCallback)subject_function_int, NULL, NULL, NULL);
  			
  	crank_func_holder_set_func (fixture->holder, fixture->ftype_float,
  			(CrankCallback)subject_function_float, NULL, NULL, NULL);
  			
  	crank_func_holder_set_func (fixture->holder, fixture->ftype_string,
  			(CrankCallback)subject_function_string, NULL, NULL, NULL);
}


void
test_func_book_setup (	FixtureFuncBook*	fixture,
						gconstpointer		userdata	)
{
	CrankFuncType* ftype_i_ii;
	CrankFuncType* ftype_f_ff;
	
	CrankFuncType* ftype_i_i;
	CrankFuncType* ftype_f_f;

	fixture->book = crank_func_book_new_with_name ("test-book");
	
	fixture->holder_add = crank_func_holder_new ("add");
	fixture->holder_mul = crank_func_holder_new ("mul");
	fixture->holder_neg = crank_func_holder_new ("neg");
	
	crank_func_book_set (fixture->book, FIXTURE_FUNC_ADD, fixture->holder_add);
	crank_func_book_set (fixture->book, FIXTURE_FUNC_MUL, fixture->holder_mul);
	crank_func_book_set (fixture->book, FIXTURE_FUNC_NEG, fixture->holder_neg);
	
	ftype_i_ii = crank_func_type_new (G_TYPE_INT,
			G_TYPE_INT, G_TYPE_INT, 		G_TYPE_NONE );
			
	ftype_f_ff = crank_func_type_new (G_TYPE_FLOAT,
			G_TYPE_FLOAT, G_TYPE_FLOAT, 		G_TYPE_NONE );
			
	ftype_i_i = crank_func_type_new (G_TYPE_INT,
			G_TYPE_INT, 		G_TYPE_NONE );
			
	ftype_f_f = crank_func_type_new (G_TYPE_FLOAT,
			G_TYPE_FLOAT, 		G_TYPE_NONE );
	
	crank_func_holder_set_func (fixture->holder_add, ftype_i_ii,
			(CrankCallback) subject_function_int, NULL, NULL, NULL);
			
	crank_func_holder_set_func (fixture->holder_add, ftype_f_ff,
			(CrankCallback) subject_function_float, NULL, NULL, NULL);
			
	crank_func_holder_set_func (fixture->holder_mul, ftype_i_ii,
			(CrankCallback) subject_mul_int, NULL, NULL, NULL);
			
	crank_func_holder_set_func (fixture->holder_mul, ftype_f_ff,
			(CrankCallback) subject_mul_float, NULL, NULL, NULL);
	
	crank_func_holder_set_func (fixture->holder_neg, ftype_i_i,
			(CrankCallback) subject_neg_int, NULL, NULL, NULL);
	
	crank_func_holder_set_func (fixture->holder_neg, ftype_f_f,
			(CrankCallback) subject_neg_float, NULL, NULL, NULL);

	crank_func_type_unref (ftype_i_ii);
	crank_func_type_unref (ftype_f_ff);
	crank_func_type_unref (ftype_i_i);
	crank_func_type_unref (ftype_f_f);
}

void
test_func_book_teardown (	FixtureFuncBook*	fixture,
							gconstpointer		userdata	)
{
	crank_func_holder_unref (fixture->holder_add);
	crank_func_holder_unref (fixture->holder_mul);
	crank_func_holder_unref (fixture->holder_neg);
	
	crank_func_book_unref (fixture->book);
}

void
test_func_book_get_name (void)
{
	CrankFuncBook*	book = crank_func_book_new_with_name ("a-book");
	
	g_assert_cmpstr (crank_func_book_get_name (book), ==, "a-book");
	g_assert_cmpint (crank_func_book_get_qname (book), ==, g_quark_from_string ("a-book"));
	
	
	crank_func_book_set_name (book, "necronomicon");
	
	g_assert_cmpstr (crank_func_book_get_name (book), ==, "necronomicon");
	g_assert_cmpint (crank_func_book_get_qname (book), ==, g_quark_from_string("necronomicon"));
	
	crank_func_book_unref (book);
}

void
test_func_book_get (	FixtureFuncBook*	fixture,
						gconstpointer		userdata	)
{
	g_assert (crank_func_book_get (fixture->book, FIXTURE_FUNC_ADD) == fixture->holder_add);
	g_assert (crank_func_book_get (fixture->book, FIXTURE_FUNC_MUL) == fixture->holder_mul);
	g_assert (crank_func_book_get (fixture->book, FIXTURE_FUNC_NEG) == fixture->holder_neg);
}

void
test_func_book_index_of (	FixtureFuncBook*	fixture,
							gconstpointer		userdata	)
{
	g_assert (crank_func_book_index_of (fixture->book, fixture->holder_add) == FIXTURE_FUNC_ADD);
	g_assert (crank_func_book_index_of (fixture->book, fixture->holder_mul) == FIXTURE_FUNC_MUL);
	g_assert (crank_func_book_index_of (fixture->book, fixture->holder_neg) == FIXTURE_FUNC_NEG);
}

void
test_func_book_get_by_name (	FixtureFuncBook*	fixture,
								gconstpointer		userdata	)
{
	g_assert (crank_func_book_get_by_name (fixture->book, "add") == fixture->holder_add);
	g_assert (crank_func_book_get_by_name (fixture->book, "mul") == fixture->holder_mul);
	g_assert (crank_func_book_get_by_name (fixture->book, "neg") == fixture->holder_neg);
}

void
test_func_book_get_by_qname (	FixtureFuncBook*	fixture,
								gconstpointer		userdata	)
{
	GQuark addq = g_quark_from_string ("add");
	GQuark mulq = g_quark_from_string ("mul");
	GQuark negq = g_quark_from_string ("neg");

	g_assert (crank_func_book_get_by_qname (fixture->book, addq) == fixture->holder_add);
	g_assert (crank_func_book_get_by_qname (fixture->book, mulq) == fixture->holder_mul);
	g_assert (crank_func_book_get_by_qname (fixture->book, negq) == fixture->holder_neg);
}

void
test_func_book_remove ( FixtureFuncBook* 	fixture,
						gconstpointer		userdata	)
{
	g_assert (crank_func_book_remove (fixture->book, FIXTURE_FUNC_ADD));
	g_assert (crank_func_book_remove (fixture->book, FIXTURE_FUNC_MUL));
	g_assert (crank_func_book_remove (fixture->book, FIXTURE_FUNC_NEG));
	g_assert (! crank_func_book_remove (fixture->book, FIXTURE_FUNC_ADD));
	
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_ADD));
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_MUL));
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_NEG));
}

void
test_func_book_remove_by_name ( FixtureFuncBook* 	fixture,
								gconstpointer		userdata	)
{
	g_assert (crank_func_book_remove_by_name (fixture->book, "add"));
	g_assert (crank_func_book_remove_by_name (fixture->book, "mul"));
	g_assert (crank_func_book_remove_by_name (fixture->book, "neg"));
	g_assert (! crank_func_book_remove_by_name (fixture->book, "add"));
	
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_ADD));
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_MUL));
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_NEG));
}

void
test_func_book_remove_by_qname ( 	FixtureFuncBook* 	fixture,
									gconstpointer		userdata	)
{
	GQuark addq = g_quark_from_string ("add");
	GQuark mulq = g_quark_from_string ("mul");
	GQuark negq = g_quark_from_string ("neg");

	g_assert (crank_func_book_remove_by_qname (fixture->book, addq));
	g_assert (crank_func_book_remove_by_qname (fixture->book, mulq));
	g_assert (crank_func_book_remove_by_qname (fixture->book, negq));
	g_assert (! crank_func_book_remove_by_qname (fixture->book, addq));
	
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_ADD));
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_MUL));
	g_assert_null (crank_func_book_get (fixture->book, FIXTURE_FUNC_NEG));
}

void
test_func_book_invoke (	FixtureFuncBook*	fixture,
						gconstpointer		userdata	)
{
	GValue	int_value = G_VALUE_INIT;
	GValue	float_value = G_VALUE_INIT;
	
	GValue	arg_values[2] = {G_VALUE_INIT, G_VALUE_INIT};
	
	
	g_value_init (&int_value, G_TYPE_INT);
	g_value_init (&float_value, G_TYPE_FLOAT);
	
	g_value_init (arg_values + 0, G_TYPE_INT);
	g_value_init (arg_values + 1, G_TYPE_INT);
	g_value_set_int (arg_values + 0, 17);
	g_value_set_int (arg_values + 1, 32);
	
	g_assert (crank_func_book_invoke (fixture->book, FIXTURE_FUNC_ADD,
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 + 32);
	
	
	g_assert (crank_func_book_invoke (fixture->book, FIXTURE_FUNC_MUL,
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 * 32);
	
	
	g_assert (crank_func_book_invoke (fixture->book, FIXTURE_FUNC_NEG,
			&int_value, 1, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, -17);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&int_value);
	
	
	g_value_init (arg_values + 0, G_TYPE_FLOAT);
	g_value_init (arg_values + 1, G_TYPE_FLOAT);
	g_value_set_float (arg_values + 0, 2.4f);
	g_value_set_float (arg_values + 1, 4.8f);
	
	g_assert (crank_func_book_invoke (fixture->book, FIXTURE_FUNC_ADD,
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f + 4.8f);
	
	
	g_assert (crank_func_book_invoke (fixture->book, FIXTURE_FUNC_MUL,
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f * 4.8f);
	
	
	g_assert (crank_func_book_invoke (fixture->book, FIXTURE_FUNC_NEG,
			&float_value, 1, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, -2.4f);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&float_value);
}


void
test_func_book_invoke_name (	FixtureFuncBook*	fixture,
								gconstpointer		userdata	)
{
	GValue	int_value = G_VALUE_INIT;
	GValue	float_value = G_VALUE_INIT;
	
	GValue	arg_values[2] = {G_VALUE_INIT, G_VALUE_INIT};
	
	
	g_value_init (&int_value, G_TYPE_INT);
	g_value_init (&float_value, G_TYPE_FLOAT);
	
	g_value_init (arg_values + 0, G_TYPE_INT);
	g_value_init (arg_values + 1, G_TYPE_INT);
	g_value_set_int (arg_values + 0, 17);
	g_value_set_int (arg_values + 1, 32);
	
	g_assert (crank_func_book_invoke_name (fixture->book, "add",
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 + 32);
	
	
	g_assert (crank_func_book_invoke_name (fixture->book, "mul",
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 * 32);
	
	
	g_assert (crank_func_book_invoke_name (fixture->book, "neg",
			&int_value, 1, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, -17);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&int_value);
	
	
	g_value_init (arg_values + 0, G_TYPE_FLOAT);
	g_value_init (arg_values + 1, G_TYPE_FLOAT);
	g_value_set_float (arg_values + 0, 2.4f);
	g_value_set_float (arg_values + 1, 4.8f);
	
	g_assert (crank_func_book_invoke_name (fixture->book, "add",
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f + 4.8f);
	
	
	g_assert (crank_func_book_invoke_name (fixture->book, "mul",
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f * 4.8f);
	
	
	g_assert (crank_func_book_invoke_name (fixture->book, "neg",
			&float_value, 1, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, -2.4f);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&float_value);
}


void
test_func_book_invoke_qname (	FixtureFuncBook*	fixture,
								gconstpointer		userdata	)
{
	GValue	int_value = G_VALUE_INIT;
	GValue	float_value = G_VALUE_INIT;
	
	GValue	arg_values[2] = {G_VALUE_INIT, G_VALUE_INIT};
	
	GQuark	addq = g_quark_from_string ("add");
	GQuark	mulq = g_quark_from_string ("mul");
	GQuark	negq = g_quark_from_string ("neg");
	
	g_value_init (&int_value, G_TYPE_INT);
	g_value_init (&float_value, G_TYPE_FLOAT);
	
	g_value_init (arg_values + 0, G_TYPE_INT);
	g_value_init (arg_values + 1, G_TYPE_INT);
	g_value_set_int (arg_values + 0, 17);
	g_value_set_int (arg_values + 1, 32);
	
	g_assert (crank_func_book_invoke_qname (fixture->book, addq,
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 + 32);
	
	
	g_assert (crank_func_book_invoke_qname (fixture->book, mulq,
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 * 32);
	
	
	g_assert (crank_func_book_invoke_qname (fixture->book, negq,
			&int_value, 1, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, -17);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&int_value);
	
	
	g_value_init (arg_values + 0, G_TYPE_FLOAT);
	g_value_init (arg_values + 1, G_TYPE_FLOAT);
	g_value_set_float (arg_values + 0, 2.4f);
	g_value_set_float (arg_values + 1, 4.8f);
	
	g_assert (crank_func_book_invoke_qname (fixture->book, addq,
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f + 4.8f);
	
	
	g_assert (crank_func_book_invoke_qname (fixture->book, mulq,
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f * 4.8f);
	
	
	g_assert (crank_func_book_invoke_qname (fixture->book, negq,
			&float_value, 1, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, -2.4f);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&float_value);
}

void
test_func_book_invoke_overwrite (	FixtureFuncBook*	fixture,
									gconstpointer		userdata	)
{
	GValue	int_value = G_VALUE_INIT;
	GValue	float_value = G_VALUE_INIT;
	
	GValue	arg_values[2] = {G_VALUE_INIT, G_VALUE_INIT};
	
	g_value_init (arg_values + 0, G_TYPE_INT);
	g_value_init (arg_values + 1, G_TYPE_INT);
	g_value_set_int (arg_values + 0, 17);
	g_value_set_int (arg_values + 1, 32);
	
	g_assert (crank_func_book_invoke_overwrite (fixture->book, FIXTURE_FUNC_ADD,
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 + 32);
	
	
	g_assert (crank_func_book_invoke_overwrite (fixture->book, FIXTURE_FUNC_MUL,
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 * 32);
	
	
	g_assert (crank_func_book_invoke_overwrite (fixture->book, FIXTURE_FUNC_NEG,
			&int_value, 1, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, -17);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&int_value);
	
	
	g_value_init (arg_values + 0, G_TYPE_FLOAT);
	g_value_init (arg_values + 1, G_TYPE_FLOAT);
	g_value_set_float (arg_values + 0, 2.4f);
	g_value_set_float (arg_values + 1, 4.8f);
	
	g_assert (crank_func_book_invoke_overwrite (fixture->book, FIXTURE_FUNC_ADD,
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f + 4.8f);
	
	
	g_assert (crank_func_book_invoke_overwrite (fixture->book, FIXTURE_FUNC_MUL,
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f * 4.8f);
	
	
	g_assert (crank_func_book_invoke_overwrite (fixture->book, FIXTURE_FUNC_NEG,
			&float_value, 1, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, -2.4f);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&float_value);
}


void
test_func_book_invoke_overwrite_name (	FixtureFuncBook*	fixture,
										gconstpointer		userdata	)
{
	GValue	int_value = G_VALUE_INIT;
	GValue	float_value = G_VALUE_INIT;
	
	GValue	arg_values[2] = {G_VALUE_INIT, G_VALUE_INIT};
	
	
	g_value_init (arg_values + 0, G_TYPE_INT);
	g_value_init (arg_values + 1, G_TYPE_INT);
	g_value_set_int (arg_values + 0, 17);
	g_value_set_int (arg_values + 1, 32);
	
	g_assert (crank_func_book_invoke_overwrite_name (fixture->book, "add",
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 + 32);
	
	
	g_assert (crank_func_book_invoke_overwrite_name (fixture->book, "mul",
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 * 32);
	
	
	g_assert (crank_func_book_invoke_overwrite_name (fixture->book, "neg",
			&int_value, 1, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, -17);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&int_value);
	
	
	g_value_init (arg_values + 0, G_TYPE_FLOAT);
	g_value_init (arg_values + 1, G_TYPE_FLOAT);
	g_value_set_float (arg_values + 0, 2.4f);
	g_value_set_float (arg_values + 1, 4.8f);
	
	g_assert (crank_func_book_invoke_overwrite_name (fixture->book, "add",
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f + 4.8f);
	
	
	g_assert (crank_func_book_invoke_overwrite_name (fixture->book, "mul",
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f * 4.8f);
	
	
	g_assert (crank_func_book_invoke_overwrite_name (fixture->book, "neg",
			&float_value, 1, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, -2.4f);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&float_value);
}


void
test_func_book_invoke_overwrite_qname (	FixtureFuncBook*	fixture,
										gconstpointer		userdata	)
{
	GValue	int_value = G_VALUE_INIT;
	GValue	float_value = G_VALUE_INIT;
	
	GValue	arg_values[2] = {G_VALUE_INIT, G_VALUE_INIT};
	
	GQuark	addq = g_quark_from_string ("add");
	GQuark	mulq = g_quark_from_string ("mul");
	GQuark	negq = g_quark_from_string ("neg");
	
	g_value_init (arg_values + 0, G_TYPE_INT);
	g_value_init (arg_values + 1, G_TYPE_INT);
	g_value_set_int (arg_values + 0, 17);
	g_value_set_int (arg_values + 1, 32);
	
	g_assert (crank_func_book_invoke_overwrite_qname (fixture->book, addq,
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 + 32);
	
	
	g_assert (crank_func_book_invoke_overwrite_qname (fixture->book, mulq,
			&int_value, 2, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 * 32);
	
	
	g_assert (crank_func_book_invoke_overwrite_qname (fixture->book, negq,
			&int_value, 1, arg_values, NULL));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, -17);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&int_value);
	
	
	g_value_init (arg_values + 0, G_TYPE_FLOAT);
	g_value_init (arg_values + 1, G_TYPE_FLOAT);
	g_value_set_float (arg_values + 0, 2.4f);
	g_value_set_float (arg_values + 1, 4.8f);
	
	g_assert (crank_func_book_invoke_overwrite_qname (fixture->book, addq,
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f + 4.8f);
	
	
	g_assert (crank_func_book_invoke_overwrite_qname (fixture->book, mulq,
			&float_value, 2, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, 2.4f * 4.8f);
	
	
	g_assert (crank_func_book_invoke_overwrite_qname (fixture->book, negq,
			&float_value, 1, arg_values, NULL));
	
	g_assert_cmpfloat (g_value_get_float (&float_value), ==, -2.4f);
	
	g_value_unset (arg_values + 0);
	g_value_unset (arg_values + 1);
	g_value_unset (&float_value);
}


void
test_func_book_invokev (	FixtureFuncBook*	fixture,
						gconstpointer		userdata	)
{
	GValue	int_value = G_VALUE_INIT;
	
	GValue	value_a = G_VALUE_INIT;
	GValue	value_b = G_VALUE_INIT;
	
	g_value_init (&int_value, G_TYPE_INT);
	
	g_value_init (&value_a, G_TYPE_INT);
	g_value_init (&value_b, G_TYPE_INT);
	g_value_set_int (&value_a, 17);
	g_value_set_int (&value_b, 32);
	
	g_assert (crank_func_book_invokev (fixture->book, FIXTURE_FUNC_ADD,
			&int_value, NULL, 2, &value_a, &value_b));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 + 32);
	
	
	g_assert (crank_func_book_invokev (fixture->book, FIXTURE_FUNC_MUL,
			&int_value, NULL, 2, &value_a, &value_b));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, 17 * 32);
	
	
	g_assert (crank_func_book_invokev (fixture->book, FIXTURE_FUNC_NEG,
			&int_value, NULL, 1, &value_a));
	
	g_assert_cmpint (g_value_get_int (&int_value), ==, -17);
	
	g_value_unset (&value_a);
	g_value_unset (&value_b);
	g_value_unset (&int_value);
}
