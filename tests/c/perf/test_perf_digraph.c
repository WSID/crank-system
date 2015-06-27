/* Copyright (C) 2015, WSID   */

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <glib.h>

#include "crankbase.h"


//////// Declaration ///////////////////////////////////////////////////////////

static gfloat		cost_edge_func (		CrankDigraphEdge*	edge,
											gpointer			userdata	);

static gfloat		heuristic_func (		CrankDigraphNode*	from,
											CrankDigraphNode*	to,
											gpointer			userdata	);

static CrankDigraph*	create_rand_graph (	guint				node_count,
											gfloat 				connect_ratio);

static void	test_complete_graph (void);

static void	test_depth_first (void);

static void	test_breadth_first (void);

static void	test_dijkstra (void);

//static void	test_astar (void);


//////// Main //////////////////////////////////////////////////////////////////

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

	g_test_add_func ("/crank/base/digraph/perf/dijkstra",
			test_dijkstra);
	
	g_test_run ();

	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static gboolean
doing_nothing (	CrankDigraphNode*	node,
				gpointer			userdata)
{
	return TRUE;
}


static gfloat
cost_edge_func (	CrankDigraphEdge*	edge,
					gpointer			uesrdata	)
{
	CrankDigraphNode*	tail;
	CrankDigraphNode*	head;

	CrankVecInt3	diff;
	
	tail = crank_digraph_edge_get_tail (edge);
	head = crank_digraph_edge_get_head (edge);
	
	crank_vec_int3_init_arr (&diff, (gint*) crank_digraph_node_get_boxed (head));
	
	crank_vec_int3_sub (	&diff,
							(CrankVecInt3*) crank_digraph_node_get_boxed (tail),
							&diff	);
	
	return crank_vec_int3_get_magn (&diff);
}

static gfloat
heuristic_func (	CrankDigraphNode*	from,
					CrankDigraphNode*	to,
					gpointer			uesrdata	)
{
	CrankVecInt3	diff;
	
	crank_vec_int3_init_arr (&diff, (gint*) crank_digraph_node_get_boxed (to));
	
	crank_vec_int3_sub (	&diff,
							(CrankVecInt3*) crank_digraph_node_get_boxed (from),
							&diff	);
	
	return crank_vec_int3_get_magn (&diff);
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
		CrankVecInt3	pos =
				{	g_test_rand_int_range (-1024, 1023),
					g_test_rand_int_range (-1024, 1023),
					g_test_rand_int_range (-1024, 1023)	};

		crank_digraph_add_boxed (graph, CRANK_TYPE_VEC_INT3, &pos);
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


static void	test_complete_graph (void)
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

static void	test_depth_first (void)
{
	CrankDigraph*		digraph;
	CrankDigraphNode*	node;
	
	digraph = create_rand_graph (1024, 0.1f);
	node = g_ptr_array_index (crank_digraph_get_nodes (digraph), 0);
	
	g_test_message ("Graph built");
	
	g_test_timer_start ();
	
	// perform a depth first iteration
	crank_digraph_node_foreach_depth (node, doing_nothing, NULL);
	
	g_test_message ("Time: %lf", g_test_timer_elapsed ());
	
	crank_digraph_unref (digraph);
}

static void	test_breadth_first (void)
{
	CrankDigraph*		digraph;
	CrankDigraphNode*	node;
	
	digraph = create_rand_graph (1024, 0.1f);
	node = g_ptr_array_index (crank_digraph_get_nodes (digraph), 0);
	
	g_test_message ("Graph built");
	
	g_test_timer_start ();
	
	// perform a depth first iteration
	crank_digraph_node_foreach_breadth (node, doing_nothing, NULL);
	
	g_test_message ("Time: %lf", g_test_timer_elapsed ());
	
	crank_digraph_unref (digraph);
}


static void	test_dijkstra (void)
{
	CrankDigraph*	digraph;
	CrankDigraphNode*	node_from;
	CrankDigraphNode*	node_to;
	
	GList*			path;
	
	digraph = create_rand_graph (1024, 0.1f);
	node_from = g_ptr_array_index (crank_digraph_get_nodes (digraph), 511);
	node_to = g_ptr_array_index (crank_digraph_get_nodes (digraph), 512);
	g_test_message ("Graph built");
	
	g_test_timer_start ();
	
	// perform dijkstra path finding
	path = 	crank_dijkstra_digraph (node_from, node_to, cost_edge_func, NULL);
	
	g_test_message ("Time: %lf", g_test_timer_elapsed ());
	g_test_message ("Path length: %u", g_list_length (path));
	
	g_list_free (path);
	
	crank_digraph_unref (digraph);
}
