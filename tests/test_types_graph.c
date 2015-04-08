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


void	test_types_graph_new (void);
void	test_types_graph_get (void);

void	test_types_graph_has (void);
void	test_types_graph_lookup (void);
void	test_types_graph_lookup_types (void);
void	test_types_graph_lookup_full (void);
void	test_types_graph_remove (void);


gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/wsid/crank/base/types_graph/new",
			test_types_graph_new);
	g_test_add_func ("/wsid/crank/base/types_graph/get",
			test_types_graph_get);
	g_test_add_func ("/wsid/crank/base/types_graph/has",
			test_types_graph_has);
	g_test_add_func ("/wsid/crank/base/types_graph/lookup/basic",
			test_types_graph_lookup);
	g_test_add_func ("/wsid/crank/base/types_graph/lookup/types",
			test_types_graph_lookup_types);
	g_test_add_func ("/wsid/crank/base/types_graph/lookup/full",
			test_types_graph_lookup_full);
	g_test_add_func ("/wsid/crank/base/types_graph/remove",
			test_types_graph_remove);

	g_test_run ();

	return 0;
}



void
test_types_graph_new (void)
{
	CrankTypesGraph* graph = crank_types_graph_new ();
	
	crank_types_graph_unref (graph);
}

void
test_types_graph_get (void)
{
	CrankTypesGraph*	graph = crank_types_graph_new ();
	GValue				value = G_VALUE_INIT;
	GValue				value_test = G_VALUE_INIT;
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	g_value_init (&value, G_TYPE_STRING);
	g_value_init (&value_test, G_TYPE_STRING);
	
	g_value_set_string (&value, "value for GObject");
	crank_types_graph_set (graph, key1, 1, &value);
	
	g_value_set_string (&value, "value for GObject, GObject");
	crank_types_graph_set (graph, key2, 2, &value);
	
	// Test
	g_assert (crank_types_graph_get(graph, key2, 2, &value_test));
	g_assert_cmpstr (
			g_value_get_string (&value_test), ==,
			"value for GObject, GObject");
	
	g_assert (crank_types_graph_get(graph, key1, 1, &value_test));
	g_assert_cmpstr (
			g_value_get_string (&value_test), ==,
			"value for GObject");
	
	g_assert_false (crank_types_graph_get (graph, key1_x, 1, &value_test));
	g_assert_false (crank_types_graph_get (graph, key1_y, 1, &value_test));
	
	g_assert_false (crank_types_graph_get (graph, key2_x, 2, &value_test));
	g_assert_false (crank_types_graph_get (graph, key2_y, 2, &value_test));
	
	crank_types_graph_unref (graph);
}

void
test_types_graph_has (void)
{
	CrankTypesGraph* graph = crank_types_graph_new ();
	GValue				value = G_VALUE_INIT;
	GValue				value_test = G_VALUE_INIT;
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	g_value_init (&value, G_TYPE_STRING);
	g_value_init (&value_test, G_TYPE_STRING);
	
	g_value_set_string (&value, "value for GObject");
	crank_types_graph_set (graph, key1, 1, &value);
	
	g_value_set_string (&value, "value for GObject, GObject");
	crank_types_graph_set (graph, key2, 2, &value);
	
	g_assert_true (crank_types_graph_has (graph, key1, 1));
	g_assert_true (crank_types_graph_has (graph, key2, 2));
	
	g_assert_false (crank_types_graph_has (graph, key1_x, 1));
	g_assert_false (crank_types_graph_has (graph, key1_y, 1));
	
	g_assert_false (crank_types_graph_has (graph, key2_x, 2));
	g_assert_false (crank_types_graph_has (graph, key2_y, 2));
	
	crank_types_graph_unref (graph);
}

void
test_types_graph_lookup (void)
{
	CrankTypesGraph* graph = crank_types_graph_new ();
	GValue				value = G_VALUE_INIT;
	GValue				value_test = G_VALUE_INIT;
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	g_value_init (&value, G_TYPE_STRING);
	g_value_init (&value_test, G_TYPE_STRING);
	
	g_value_set_string (&value, "value for GObject");
	crank_types_graph_set (graph, key1, 1, &value);
	
	g_value_set_string (&value, "value for GObject, GObject");
	crank_types_graph_set (graph, key2, 2, &value);
	
	
	
	g_assert (crank_types_graph_lookup(graph, key1, 1, &value_test));
	g_assert_cmpstr(
			g_value_get_string (&value_test), ==,
			"value for GObject");
			
	g_assert (crank_types_graph_lookup(graph, key2, 2, &value_test));
	g_assert_cmpstr(
			g_value_get_string (&value_test), ==,
			"value for GObject, GObject");
	
	g_assert (crank_types_graph_lookup(graph, key1_x, 1, &value_test));
	g_assert_cmpstr(
			g_value_get_string (&value_test), ==,
			"value for GObject");
	
	g_assert_false (crank_types_graph_lookup (graph, key1_y, 1, &value_test));
	
	g_assert_false (crank_types_graph_lookup (graph, key2_x, 2, &value_test));
	
	g_assert (crank_types_graph_lookup(graph, key2_y, 2, &value_test));
	g_assert_cmpstr(
			g_value_get_string (&value_test), ==,
			"value for GObject, GObject");
}

void
test_types_graph_lookup_types (void)
{
	const GType*	lookup_key1;
	const GType*	lookup_key2;
	
	const GType*	lookup_key1_x;
	const GType*	lookup_key1_y;
	const GType*	lookup_key2_x;
	const GType*	lookup_key2_y;
	

	CrankTypesGraph* graph = crank_types_graph_new ();
	GValue				value = G_VALUE_INIT;
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_value_set_string (&value, "value for GObject");
	crank_types_graph_set (graph, key1, 1, &value);
	
	g_value_set_string (&value, "value for GObject, GObject");
	crank_types_graph_set (graph, key2, 2, &value);
	
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
test_types_graph_lookup_full (void)
{
	const GType*	lookup_key1;
	const GType*	lookup_key2;
	
	const GType*	lookup_key1_x;
	const GType*	lookup_key1_y;
	const GType*	lookup_key2_x;
	const GType*	lookup_key2_y;
	
	CrankTypesGraph* graph = crank_types_graph_new ();
	GValue				value = G_VALUE_INIT;
	GValue				value_test = G_VALUE_INIT;
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	g_value_init (&value, G_TYPE_STRING);
	g_value_init (&value_test, G_TYPE_STRING);
	
	g_value_set_string (&value, "value for GObject");
	crank_types_graph_set (graph, key1, 1, &value);
	
	g_value_set_string (&value, "value for GObject, GObject");
	crank_types_graph_set (graph, key2, 2, &value);
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1, 1, &lookup_key1, &value_test));
	g_assert_cmpstr (
			g_value_get_string(&value_test), ==,
			"value for GObject");
			
	g_assert_true (crank_types_graph_lookup_full (graph, key2, 2, &lookup_key2, &value_test));
	g_assert_cmpstr (
			g_value_get_string(&value_test), ==,
			"value for GObject, GObject");
			
	g_assert_true (crank_types_graph_lookup_full (graph, key1_x, 1, &lookup_key1_x, &value_test));
	g_assert_cmpstr (
			g_value_get_string(&value_test), ==,
			"value for GObject");
			
	g_assert_false (crank_types_graph_lookup_full (graph, key1_y, 1, &lookup_key1_y, &value_test));
	
	g_assert_false (crank_types_graph_lookup_full (graph, key2_x, 2, &lookup_key2_x, &value_test));
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_y, 2, &lookup_key2_y, &value_test));
	g_assert_cmpstr (
			g_value_get_string(&value_test), ==,
			"value for GObject, GObject");
			
	
	g_assert_true (CRANK_ARRAY_CMP (lookup_key1, key1, GType, 1) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2, key2, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key1_x, key1, GType, 1) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_y, key2, GType, 2) == 0);
	
	crank_types_graph_unref (graph);
}

void
test_types_graph_remove (void)
{
	CrankTypesGraph* graph = crank_types_graph_new ();
	GValue				value = G_VALUE_INIT;
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_value_set_string (&value, "value for GObject");
	crank_types_graph_set (graph, key1, 1, &value);
	
	g_value_set_string (&value, "value for GObject, GObject");
	crank_types_graph_set (graph, key2, 2, &value);
	
	g_assert_false (crank_types_graph_remove (graph, key1_x, 1));
	g_assert_false (crank_types_graph_remove (graph, key1_y, 1));
	g_assert_false (crank_types_graph_remove (graph, key2_x, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_y, 2));
	
	g_assert_true (crank_types_graph_remove (graph, key1, 1));
	g_assert_true (crank_types_graph_remove (graph, key2, 2));
	
	crank_types_graph_unref (graph);
}
