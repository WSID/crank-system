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


gint
main (gint   argc,
      gchar *argv[])
{
  g_test_init (&argc, &argv, NULL);

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
	CrankTypesGraph* graph = crank_types_graph_new_full (g_free);
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	crank_types_graph_set (graph, key1, 1, "value for GObject");
	crank_types_graph_set (graph, key2, 2, "value for GObject, GObject");
	
	g_assert_cmpstr (
			(gchar*)crank_types_graph_get(graph, key1, 1), ==,
			"value for GObject");
	g_assert_cmpstr (
			(gchar*)crank_types_graph_get(graph, key2, 2), ==,
			"value for GObject, GObject");
	
	g_assert_null (crank_types_graph_get (graph, key1_x, 1));
	g_assert_null (crank_types_graph_get (graph, key1_y, 1));
	
	g_assert_null (crank_types_graph_get (graph, key2_x, 2));
	g_assert_null (crank_types_graph_get (graph, key2_y, 2));
	
	crank_types_graph_unref (graph);
}

void
test_types_graph_has (void)
{
	CrankTypesGraph* graph = crank_types_graph_new_full (g_free);
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	crank_types_graph_set (graph, key1, 1, "value for GObject");
	crank_types_graph_set (graph, key2, 2, "value for GObject, GObject");
	
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
	CrankTypesGraph* graph = crank_types_graph_new_full (g_free);
	
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	crank_types_graph_set (graph, key1, 1, "value for GObject");
	crank_types_graph_set (graph, key2, 2, "value for GObject, GObject");
	
	
	g_assert_cmpstr (
			(gchar*)crank_types_graph_lookup(graph, key1, 1), ==,
			"value for GObject");
	g_assert_cmpstr (
			(gchar*)crank_types_graph_lookup(graph, key2, 2), ==,
			"value for GObject, GObject");
	
	g_assert_cmpstr (
			(gchar*)crank_types_graph_lookup(graph, key1_x, 1), ==,
			"value for GObject");
	g_assert_null (crank_types_graph_lookup (graph, key1_y, 1));
	
	g_assert_null (crank_types_graph_lookup (graph, key2_x, 2));
	g_assert_cmpstr (
			(gchar*)crank_types_graph_lookup(graph, key2_y, 2), ==,
			"value for GObject, GObject");
}

void
test_types_graph_lookup_types (void)
{
	GType*	lookup_key1;
	GType*	lookup_key2;
	
	GType*	lookup_key1_x;
	GType*	lookup_key1_y;
	GType*	lookup_key2_x;
	GType*	lookup_key2_y;
	

	CrankTypesGraph* graph = crank_types_graph_new_full (g_free);
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	crank_types_graph_set (graph, key1, 1, "value for GObject");
	crank_types_graph_set (graph, key2, 2, "value for GObject, GObject");
	
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
	GType*	lookup_key1;
	GType*	lookup_key2;
	
	GType*	lookup_key1_x;
	GType*	lookup_key1_y;
	GType*	lookup_key2_x;
	GType*	lookup_key2_y;
	
	gchar*	lookup_key1_v;
	gchar*	lookup_key2_v;
	
	gchar*	lookup_key1_x_v;
	gchar*	lookup_key1_y_v;
	gchar*	lookup_key2_x_v;
	gchar*	lookup_key2_y_v;

	CrankTypesGraph* graph = crank_types_graph_new_full (g_free);
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	crank_types_graph_set (graph, key1, 1, "value for GObject");
	crank_types_graph_set (graph, key2, 2, "value for GObject, GObject");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1, 1, &lookup_key1, &lookup_key1_v));
	g_assert_true (crank_types_graph_lookup_full (graph, key2, 1, &lookup_key2, &lookup_key2_v));
	g_assert_true (crank_types_graph_lookup_full (graph, key1_x, 1, &lookup_key1_x, &lookup_key1_x_v));
	g_assert_false (crank_types_graph_lookup_full (graph, key1_y, 1, &lookup_key1_y, &lookup_key1_y_v));
	g_assert_false (crank_types_graph_lookup_full (graph, key2_x, 1, &lookup_key2_x, &lookup_key2_x_v));
	g_assert_true (crank_types_graph_lookup_full (graph, key2_y, 1, &lookup_key2_y, &lookup_key2_y_v));
	
	g_assert_true (CRANK_ARRAY_CMP (lookup_key1, key1, GType, 1) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2, key2, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key1_x, key1, GType, 1) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_y, key2, GType, 2) == 0);
	
	g_assert_cmpstr (lookup_key1_v, ==, "value for GObject");
	g_assert_cmpstr (lookup_key2_v, ==, "value for GObject, GObject");
	g_assert_cmpstr (lookup_key1_x_v, ==, "value for GObject");
	g_assert_cmpstr (lookup_key2_y_v, ==, "value for GObject, GObject");
	
	crank_types_graph_unref (graph);
}

void
test_types_graph_remove (void)
{
	CrankTypesGraph* graph = crank_types_graph_new_full (g_free);
	
	GType key1[] = {G_TYPE_OBJECT};
	GType key2[] = {G_TYPE_OBJECT, G_TYPE_OBJECT};
	
	GType key1_x[] = {G_TYPE_BINDING};
	GType key1_y[] = {G_TYPE_GTYPE};
	
	GType key2_x[] = {G_TYPE_INT, G_TYPE_INT};
	GType key2_y[] = {G_TYPE_OBJECT, G_TYPE_BINDING};
	
	crank_types_graph_set (graph, key1, 1, "value for GObject");
	crank_types_graph_set (graph, key2, 2, "value for GObject, GObject");
	
	g_assert_false (crank_types_graph_remove (graph, key1_x, 1));
	g_assert_false (crank_types_graph_remove (graph, key1_y, 1));
	g_assert_false (crank_types_graph_remove (graph, key2_x, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_y, 2));
	
	g_assert_true (crank_types_graph_remove (graph, key1, 1));
	g_assert_true (crank_types_graph_remove (graph, key2, 2));
	
	crank_types_graph_unref (graph);
}
