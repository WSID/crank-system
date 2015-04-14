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

	
static GType key1[1];
static GType key2[2];

static GType key1_x[1];
static GType key1_y[1];

static GType key2_x[2];
static GType key2_y[2];


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
	key1[0] = G_TYPE_OBJECT;
	key2[0] = G_TYPE_OBJECT;
	key2[1] = G_TYPE_OBJECT;

	key1_x[0] = G_TYPE_BINDING;
	key1_y[0] = G_TYPE_GTYPE;

	key2_x[0] = G_TYPE_INT;
	key2_x[1] = G_TYPE_INT;
	key2_y[0] = G_TYPE_OBJECT;
	key2_y[1] = G_TYPE_BINDING;
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
	
	g_value_set_string (&value, "value for GObject");
	crank_types_graph_set (*graph_ptr, key1, 1, &value);
	
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
	
	// Test
	g_assert (crank_types_graph_get(graph, key2, 2, &value));
	g_assert_cmpstr (
			g_value_get_string (&value), ==,
			"value for GObject, GObject");
	
	g_assert (crank_types_graph_get(graph, key1, 1, &value));
	g_assert_cmpstr (
			g_value_get_string (&value), ==,
			"value for GObject");
	
	g_assert_false (crank_types_graph_get (graph, key1_x, 1, &value));
	g_assert_false (crank_types_graph_get (graph, key1_y, 1, &value));
	
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
	
	g_assert_true (crank_types_graph_has (graph, key1, 1));
	g_assert_true (crank_types_graph_has (graph, key2, 2));
	
	g_assert_false (crank_types_graph_has (graph, key1_x, 1));
	g_assert_false (crank_types_graph_has (graph, key1_y, 1));
	
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
	
	
	g_assert (crank_types_graph_lookup(graph, key1, 1, &value));
	g_assert_cmpstr(
			g_value_get_string (&value), ==,
			"value for GObject");
			
	g_assert (crank_types_graph_lookup(graph, key2, 2, &value));
	g_assert_cmpstr(
			g_value_get_string (&value), ==,
			"value for GObject, GObject");
	
	g_assert (crank_types_graph_lookup(graph, key1_x, 1, &value));
	g_assert_cmpstr(
			g_value_get_string (&value), ==,
			"value for GObject");
	
	g_assert_false (crank_types_graph_lookup (graph, key1_y, 1, &value));
	
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
	const GType*	lookup_key1;
	const GType*	lookup_key2;
	
	const GType*	lookup_key1_x;
	const GType*	lookup_key1_y;
	const GType*	lookup_key2_x;
	const GType*	lookup_key2_y;
	

	CrankTypesGraph* graph = *(CrankTypesGraph**) fixture;

	lookup_key1 = crank_types_graph_lookup_types (graph, key1, 1);
	lookup_key2 = crank_types_graph_lookup_types (graph, key2, 2);
	lookup_key1_x = crank_types_graph_lookup_types (graph, key1_x, 1);
	lookup_key1_y = crank_types_graph_lookup_types (graph, key1_y, 1);
	lookup_key2_x = crank_types_graph_lookup_types (graph, key2_x, 2);
	lookup_key2_y = crank_types_graph_lookup_types (graph, key2_y, 2);
	
	g_assert_true (CRANK_ARRAY_CMP (lookup_key1, key1, GType, 1) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2, key2, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key1_x, key1, GType, 1) == 0);
	g_assert_null (lookup_key1_y);
	g_assert_null (lookup_key2_x);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_y, key2, GType, 2) == 0);
}

void
test_types_graph_lookup_full (	CrankTypesGraph**	fixture,
								gconstpointer		userdata	)
{
	const GType*	lookup_key1;
	const GType*	lookup_key2;
	
	const GType*	lookup_key1_x;
	const GType*	lookup_key1_y;
	const GType*	lookup_key2_x;
	const GType*	lookup_key2_y;
	
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;
	
	GValue				value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1, 1, &lookup_key1, &value));
	g_assert_cmpstr (
			g_value_get_string(&value), ==,
			"value for GObject");
			
	g_assert_true (crank_types_graph_lookup_full (graph, key2, 2, &lookup_key2, &value));
	g_assert_cmpstr (
			g_value_get_string(&value), ==,
			"value for GObject, GObject");
			
	g_assert_true (crank_types_graph_lookup_full (graph, key1_x, 1, &lookup_key1_x, &value));
	g_assert_cmpstr (
			g_value_get_string(&value), ==,
			"value for GObject");
			
	g_assert_false (crank_types_graph_lookup_full (graph, key1_y, 1, &lookup_key1_y, &value));
	
	g_assert_false (crank_types_graph_lookup_full (graph, key2_x, 2, &lookup_key2_x, &value));
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_y, 2, &lookup_key2_y, &value));
	g_assert_cmpstr (
			g_value_get_string(&value), ==,
			"value for GObject, GObject");
			
	
	g_assert_true (CRANK_ARRAY_CMP (lookup_key1, key1, GType, 1) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2, key2, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key1_x, key1, GType, 1) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_y, key2, GType, 2) == 0);
}

void
test_types_graph_remove (	CrankTypesGraph**	fixture,
							gconstpointer		userdata	)
{
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;
	
	g_assert_false (crank_types_graph_remove (graph, key1_x, 1));
	g_assert_false (crank_types_graph_remove (graph, key1_y, 1));
	g_assert_false (crank_types_graph_remove (graph, key2_x, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_y, 2));
	
	g_assert_true (crank_types_graph_remove (graph, key1, 1));
	g_assert_true (crank_types_graph_remove (graph, key2, 2));
}
