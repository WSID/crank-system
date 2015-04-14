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

	
static GType key1_a[1];
static GType key1_b[1];
static GType key1_c[1];
static GType key1_d[1];
static GType key1_e[1];
static GType key1_x[1];

static GType key2[2];


static GType key2_x[2];
static GType key2_y[2];

//////// Test Subjects Types ///////////////////////////////////////////////////

#define TEST_DEFINE_TEST_TYPE(Type, type, NS, T, parent, parent_GTYPE) \
		typedef struct _##Type##Class { \
			parent##Class	parent_class; \
		} Type##Class; \
		\
		G_DECLARE_DERIVABLE_TYPE (Type, type, NS, T, parent); \
		G_DEFINE_TYPE (Type, type, parent_GTYPE); \
		\
		static void type##_class_init ( Type##Class* c) {} \
		static void type##_init (Type* i) {}

/* 테스트를 위해서만 만들어진 클래스들입니다.
 *
 * TestA
 * - TestB
 *   - TestC
 *   - TestD
 * - TestE
 */

#define TEST_TYPE_A	(test_a_get_type ())
TEST_DEFINE_TEST_TYPE(TestA, test_a, TEST, A, GObject, G_TYPE_OBJECT);

#define TEST_TYPE_B	(test_b_get_type ())
TEST_DEFINE_TEST_TYPE(TestB, test_b, TEST, B, TestA, TEST_TYPE_A);

#define TEST_TYPE_C	(test_c_get_type ())
TEST_DEFINE_TEST_TYPE(TestC, test_c, TEST, C, TestB, TEST_TYPE_B);

#define TEST_TYPE_D	(test_d_get_type ())
TEST_DEFINE_TEST_TYPE(TestD, test_d, TEST, D, TestB, TEST_TYPE_B);

#define TEST_TYPE_E	(test_e_get_type ())
TEST_DEFINE_TEST_TYPE(TestE, test_e, TEST, E, TestA, TEST_TYPE_A);

#define TEST_TYPE_X	(test_x_get_type ())
TEST_DEFINE_TEST_TYPE(TestX, test_x, TEST, X, GObject, G_TYPE_OBJECT);


//////// Test Cases ////////////////////////////////////////////////////////////

typedef void	(*TestTypeGraphFunc) (	CrankTypesGraph**	fixture,
										gconstpointer		userdata	);

void	test_init_types_graph (void);



static inline
void	test_add_types_graph (		const gchar*		test_path,
									gconstpointer		userdata,
									TestTypeGraphFunc	func		);



void	test_types_graph_setup (	CrankTypesGraph**	graph_ptr,
                                	gconstpointer		userdata	);
void	test_types_graph_teardown (	CrankTypesGraph**	graph_ptr,
                                   	gconstpointer		userdata	);


void	test_types_graph_new (void);

void	test_types_graph_get (		CrankTypesGraph**	fixture,
                              		gconstpointer	userdata	);
void	test_types_graph_has (		CrankTypesGraph**	fixture,
									gconstpointer		userdata	);
									
void	test_types_graph_lookup (	CrankTypesGraph**	fixture,
									gconstpointer		userdata	);
void	test_types_graph_lookup_types (	CrankTypesGraph**	fixture,
										gconstpointer		userdata	);
void	test_types_graph_lookup_full (	CrankTypesGraph**	fixture,
										gconstpointer		userdata	);
void	test_types_graph_remove (	CrankTypesGraph**	fixture,
									gconstpointer		userdata	);


gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);
	
	test_init_types_graph ();
	
	g_test_add_func ("/wsid/crank/base/types_graph/new",
			test_types_graph_new);
	
	test_add_types_graph ("/wsid/crank/base/types_graph/get",
			NULL,	test_types_graph_get	);
	test_add_types_graph ("/wsid/crank/base/types_graph/has",
			NULL,	test_types_graph_has	);
			
	test_add_types_graph("/wsid/crank/base/types_graph/lookup/basic",
			NULL,	test_types_graph_lookup);
	test_add_types_graph ("/wsid/crank/base/types_graph/lookup/types",
			NULL,	test_types_graph_lookup_types);
	test_add_types_graph ("/wsid/crank/base/types_graph/lookup/full",
			NULL,	test_types_graph_lookup_full);
	test_add_types_graph ("/wsid/crank/base/types_graph/remove",
			NULL,	test_types_graph_remove);

	g_test_run ();

	return 0;
}



void
test_init_types_graph (void)
{
	key1_a[0] = TEST_TYPE_A;
	key1_b[0] = TEST_TYPE_B;
	key1_c[0] = TEST_TYPE_C;
	key1_d[0] = TEST_TYPE_D;
	key1_e[0] = TEST_TYPE_E;
	key1_x[0] = TEST_TYPE_X;
	
	key2[0] = TEST_TYPE_A;
	key2[1] = TEST_TYPE_A;


	key2_x[0] = G_TYPE_INT;
	key2_x[1] = G_TYPE_INT;
	key2_y[0] = TEST_TYPE_A;
	key2_y[1] = TEST_TYPE_D;
}


static inline void
test_add_types_graph (	const gchar*		test_path,
						gconstpointer		userdata,
						TestTypeGraphFunc	func		)
{
	g_test_add (test_path,
			CrankTypesGraph*,
			userdata,
			test_types_graph_setup,
			func,
			test_types_graph_teardown	);
}




void
test_types_graph_setup (	CrankTypesGraph**	graph_ptr,
                            gconstpointer		userdata	)
{
	*graph_ptr = crank_types_graph_new ();
	
	GValue value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_value_set_string (&value, "value for A");
	crank_types_graph_set (*graph_ptr, key1_a, 1, &value);
	
	g_value_set_string (&value, "value for D");
	crank_types_graph_set (*graph_ptr, key1_d, 1, &value);
	
	g_value_set_string (&value, "value for E");
	crank_types_graph_set (*graph_ptr, key1_e, 1, &value);
	
	g_value_set_string (&value, "value for GObject, GObject");
	crank_types_graph_set (*graph_ptr, key2, 2, &value);
}

void
test_types_graph_teardown (	CrankTypesGraph**	graph_ptr,
                           	gconstpointer		userdata	)
{
	crank_types_graph_unref (*graph_ptr);
}





void
test_types_graph_new (void)
{
	CrankTypesGraph* graph = crank_types_graph_new ();
	
	crank_types_graph_unref (graph);
}

void
test_types_graph_get (	CrankTypesGraph**	fixture,
                        gconstpointer		userdata	)
{
	CrankTypesGraph*	graph = *(CrankTypesGraph**) fixture;
	
	GValue				value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	// Test for 1
	g_assert (crank_types_graph_get(graph, key1_a, 1, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for A");
	
	g_assert (! crank_types_graph_get(graph, key1_b, 1, &value));
	
	g_assert (! crank_types_graph_get(graph, key1_c, 1, &value));
	
	g_assert (crank_types_graph_get(graph, key1_d, 1, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for D");
	
	g_assert (crank_types_graph_get(graph, key1_e, 1, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for E");
	
	g_assert (! crank_types_graph_get(graph, key1_x, 1, &value));
	
	
	// Test for 2
	g_assert (crank_types_graph_get(graph, key2, 2, &value));
	g_assert_cmpstr (
			g_value_get_string (&value), ==,
			"value for GObject, GObject");
	
	
	g_assert_false (crank_types_graph_get (graph, key2_x, 2, &value));
	g_assert_false (crank_types_graph_get (graph, key2_y, 2, &value));
}

void
test_types_graph_has (	CrankTypesGraph**	fixture,
                        gconstpointer		userdata	)
{
	CrankTypesGraph* graph = *(CrankTypesGraph**) fixture;

	GValue				value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_assert_true (crank_types_graph_has (graph, key1_a, 1));
	g_assert_false (crank_types_graph_has (graph, key1_b, 1));
	g_assert_false (crank_types_graph_has (graph, key1_c, 1));
	g_assert_true (crank_types_graph_has (graph, key1_d, 1));
	g_assert_true (crank_types_graph_has (graph, key1_e, 1));
	g_assert_false (crank_types_graph_has (graph, key1_x, 1));
	
	g_assert_true (crank_types_graph_has (graph, key2, 2));
	g_assert_false (crank_types_graph_has (graph, key2_x, 2));
	g_assert_false (crank_types_graph_has (graph, key2_y, 2));
}

void
test_types_graph_lookup (	CrankTypesGraph**	fixture,
							gconstpointer		userdata	)
{
	CrankTypesGraph* graph = *(CrankTypesGraph**) fixture;

	GValue				value = G_VALUE_INIT;

	g_value_init (&value, G_TYPE_STRING);
	
	
	g_assert (crank_types_graph_lookup(graph, key1_a, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for A");
	
	g_assert (crank_types_graph_lookup(graph, key1_b, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for A");
	
	g_assert (crank_types_graph_lookup(graph, key1_c, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for A");
	
	g_assert (crank_types_graph_lookup(graph, key1_d, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for D");
	
	g_assert (crank_types_graph_lookup(graph, key1_e, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for E");
	
	g_assert (! crank_types_graph_lookup(graph, key1_x, 1, &value));
			
	g_assert (crank_types_graph_lookup(graph, key2, 2, &value));
	g_assert_cmpstr(
			g_value_get_string (&value), ==,
			"value for GObject, GObject");
			
	g_assert_false (crank_types_graph_lookup (graph, key2_x, 2, &value));
	
	g_assert (crank_types_graph_lookup(graph, key2_y, 2, &value));
	g_assert_cmpstr(
			g_value_get_string (&value), ==,
			"value for GObject, GObject");
}

void
test_types_graph_lookup_types (	CrankTypesGraph**	fixture,
								gconstpointer		userdata	)
{
	const GType*	lookup_key1_a;
	const GType*	lookup_key1_b;
	const GType*	lookup_key1_c;
	const GType*	lookup_key1_d;
	const GType*	lookup_key1_e;
	const GType*	lookup_key1_x;
	
	const GType*	lookup_key2;
	const GType*	lookup_key2_x;
	const GType*	lookup_key2_y;
	

	CrankTypesGraph* graph = *(CrankTypesGraph**) fixture;

	lookup_key1_a = crank_types_graph_lookup_types (graph, key1_a, 1);
	lookup_key1_b = crank_types_graph_lookup_types (graph, key1_b, 1);
	lookup_key1_c = crank_types_graph_lookup_types (graph, key1_c, 1);
	lookup_key1_d = crank_types_graph_lookup_types (graph, key1_d, 1);
	lookup_key1_e = crank_types_graph_lookup_types (graph, key1_e, 1);
	lookup_key1_x = crank_types_graph_lookup_types (graph, key1_x, 1);
	
 	lookup_key2 = crank_types_graph_lookup_types (graph, key2, 2);
	lookup_key2_x = crank_types_graph_lookup_types (graph, key2_x, 2);
	lookup_key2_y = crank_types_graph_lookup_types (graph, key2_y, 2);
	
	g_assert (CRANK_ARRAY_CMP (lookup_key1_a, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_b, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_c, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_d, key1_d, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_e, key1_e, GType, 1) == 0);
	g_assert_null (lookup_key1_x);
	
	
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2, key2, GType, 2) == 0);
	g_assert_null (lookup_key2_x);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_y, key2, GType, 2) == 0);
}

void
test_types_graph_lookup_full (	CrankTypesGraph**	fixture,
								gconstpointer		userdata	)
{
	const GType*	lookup_key1_a;
	const GType*	lookup_key1_b;
	const GType*	lookup_key1_c;
	const GType*	lookup_key1_d;
	const GType*	lookup_key1_e;
	const GType*	lookup_key1_x;
	
	const GType*	lookup_key2;
	const GType*	lookup_key2_x;
	const GType*	lookup_key2_y;
	
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;
	
	GValue				value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_a, 1, &lookup_key1_a, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for A");
			
	g_assert_true (crank_types_graph_lookup_full (graph, key1_b, 1, &lookup_key1_b, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for A");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_c, 1, &lookup_key1_c, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for A");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_d, 1, &lookup_key1_d, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for D");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_e, 1, &lookup_key1_e, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for E");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_x, 1, &lookup_key1_x, &value));
			
			
	g_assert_true (crank_types_graph_lookup_full (graph, key2, 2, &lookup_key2, &value));
	g_assert_cmpstr (
			g_value_get_string(&value), ==,
			"value for GObject, GObject");
	
	g_assert_false (crank_types_graph_lookup_full (graph, key2_x, 2, &lookup_key2_x, &value));
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_y, 2, &lookup_key2_y, &value));
	g_assert_cmpstr (
			g_value_get_string(&value), ==,
			"value for GObject, GObject");
			
	
	g_assert (CRANK_ARRAY_CMP (lookup_key1_a, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_b, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_c, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_d, key1_d, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_e, key1_e, GType, 1) == 0);
	g_assert_null (lookup_key1_x);
	
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2, key2, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_y, key2, GType, 2) == 0);
}

void
test_types_graph_remove (	CrankTypesGraph**	fixture,
							gconstpointer		userdata	)
{
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;

	g_assert_false (crank_types_graph_remove (graph, key1_b, 1));	
	g_assert_false (crank_types_graph_remove (graph, key1_c, 1));
	g_assert_false (crank_types_graph_remove (graph, key1_x, 1));
	g_assert_false (crank_types_graph_remove (graph, key2_x, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_y, 2));
	
	g_assert_true (crank_types_graph_remove (graph, key1_d, 1));
	g_assert_true (crank_types_graph_remove (graph, key1_a, 1));
	g_assert_true (crank_types_graph_remove (graph, key1_e, 1));
	g_assert_true (crank_types_graph_remove (graph, key2, 2));
}
