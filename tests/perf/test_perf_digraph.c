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

CrankDigraph*
create_rand_graph (guint node_count,	gfloat connect_ratio);

void
test_complete_graph (void);

void
test_depth_first (void);

void
test_breadth_first (void);

gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);
	
	g_test_add_func ("/crank/base/digraph/perf/complete_graph",
			test_complete_graph);
	
	g_test_add_func ("/crank/base/digraph/perf/depth_first",
			test_depth_first);
	
	g_test_add_func ("/crank/base/digraph/perf/breadth_first",
			test_breadth_first);
	
	g_test_run ();

	return 0;
}





gboolean		doing_nothing (CrankDigraph* digraph, CrankDigraphNode* node, gpointer userdata)
{
	return TRUE;
}


CrankDigraph*	create_rand_graph (	guint	node_count,
									gfloat	connect_ratio	)
{
	CrankDigraph*		graph = crank_digraph_new ();
	CrankDigraphNode**	nodes;
	
	guint			connect_possible = node_count * (node_count - 1);
	guint			connect_count = (guint)	(connect_possible * connect_ratio);
	
	guint			i;
	guint			j;
	
	g_test_message ("Node count: %u", node_count);
	g_test_message ("Connect ratio: %f", connect_ratio);
	g_test_message ("Connect count: %u", connect_count);
	
	for (i = 0; i < node_count; i++) {
		crank_digraph_add_pointer (graph, G_TYPE_POINTER, NULL);
	}
	
	nodes = (CrankDigraphNode**) (crank_digraph_get_nodes (graph) -> pdata);
	
	// Add edges
	for (i = 0; i < node_count; i++) {
		for (j = 0; j < i; j++) {
			if (g_test_rand_int_range (0, connect_possible) < connect_count) {
				crank_digraph_connect_void (graph, nodes[i], nodes[j]);
				connect_count --;
			}
			connect_possible --;
		}
		
		for (j = i+1; j < node_count; j++) {
			if (g_test_rand_int_range (0, connect_possible) < connect_count) {
				crank_digraph_connect_void (graph, nodes[i], nodes[j]);
				connect_count --;
			}
			connect_possible --;
		}
	}
	
	return graph;
}


void			test_complete_graph (void)
{
	// Constructs Complete digraph with 1024 nodes
	
	// 1024 nodes are constructed.
	// 1047552 edges are constructed.
	
	// The individual nodes are given integer value as index.
	
	CrankDigraph*		digraph;
	CrankDigraphNode**	nodes;
	
	guint			i;
	guint			j;
	
	guint			n = 1024;
	
	
	g_test_timer_start ();
	
	digraph = crank_digraph_new ();
	nodes = g_new (CrankDigraphNode*, n);
	
	// build nodes
	for (i = 0; i < n; i++) {
		GValue	value = { 0 };
		g_value_init (&value, G_TYPE_INT);
		
		g_value_set_int (&value, i);
		
		nodes[i] = crank_digraph_add (digraph, &value);
	}
	g_test_message ("Nodes built");

	// build edges	
	for (i = 0; i < n; i++) {
		for (j = 0; j < i; j++) {
			crank_digraph_connect_void (digraph, nodes[i], nodes[j]);
		}
		for (j = i + 1; j < n; j++) {
			crank_digraph_connect_void (digraph, nodes[i], nodes[j]);
		}
	}
	
	g_test_message ("Time: %lf", g_test_timer_elapsed ());
	
	g_free (nodes);
	crank_digraph_unref (digraph);
}

void			test_depth_first (void)
{
	CrankDigraph*		digraph;
	CrankDigraphNode*	node;
	
	digraph = create_rand_graph (1024, 0.7f);
	node = g_ptr_array_index (crank_digraph_get_nodes (digraph), 0);
	
	g_test_message ("Graph built");
	
	g_test_timer_start ();
	
	// perform a depth first iteration
	crank_digraph_depth_first (digraph, node, doing_nothing, NULL);
	
	g_test_message ("Time: %lf", g_test_timer_elapsed ());
	
	crank_digraph_unref (digraph);
}

void			test_breadth_first (void)
{
	CrankDigraph*		digraph;
	CrankDigraphNode*	node;
	
	digraph = create_rand_graph (1024, 0.7f);
	node = g_ptr_array_index (crank_digraph_get_nodes (digraph), 0);
	
	g_test_message ("Graph built");
	
	g_test_timer_start ();
	
	// perform a depth first iteration
	crank_digraph_breadth_first (digraph, node, doing_nothing, NULL);
	
	g_test_message ("Time: %lf", g_test_timer_elapsed ());
	
	crank_digraph_unref (digraph);
}
