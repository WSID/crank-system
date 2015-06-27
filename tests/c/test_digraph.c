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

//////// Definition ////////////////////////////////////////////////////////////

typedef struct _TestDigraphFixture {
	CrankDigraph*		digraph;
	CrankDigraphNode*	nodes[16];
	CrankDigraphEdge*	edges[16];
} TestDigraphFixture;

static gboolean	testutil_accumulator_graph (	CrankDigraphNode*	node,
												gpointer			pointer	);


static void	test_digraph_setup (			TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

static void	test_digraph_teardown (			TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

static void	test_digraph_get_nodes (		TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

static void	test_digraph_get_edges (		TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

static void	test_digraph_disconnect (		TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

static void	test_digraph_disconnect_edge (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

static void	test_digraph_node_get_data (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
										
static void	test_digraph_node_get_in_edges (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
static void	test_digraph_node_get_out_edges (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
										
static void	test_digraph_node_get_in_nodes (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
static void	test_digraph_node_get_out_nodes (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
static void	test_digraph_node_get_indegree (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
static void	test_digraph_node_get_outdegree (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
static void	test_digraph_node_is_adjacent (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
static void	test_digraph_node_is_adjacent_from (	TestDigraphFixture*	fixture,
													gconstpointer		userdata	);
											
static void	test_digraph_node_is_adjacent_to (	TestDigraphFixture*	fixture,
												gconstpointer		userdata	);

static void	test_digraph_node_foreach_depth (	TestDigraphFixture*	fixture,
												gconstpointer		userdata	);
										
static void	test_digraph_node_foreach_breadth (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
static void	test_digraph_edge_get_data (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

static void	test_digraph_edge_get_tail (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

static void	test_digraph_edge_get_head (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint argc, gchar **argv)
{
	g_test_init (&argc, &argv, NULL);

	g_test_add ("/crank/base/digraph/nodes",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_get_nodes,
			test_digraph_teardown	);

	g_test_add ("/crank/base/digraph/edges",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_get_edges,
			test_digraph_teardown	);

	g_test_add ("/crank/base/digraph/disconnect",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_disconnect,
			test_digraph_teardown	);

	g_test_add ("/crank/base/digraph/disconnect/edge",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_disconnect_edge,
			test_digraph_teardown	);


	g_test_add ("/crank/base/digraph/node/data",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_get_data,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/in/edges",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_get_in_edges,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/out/edges",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_get_out_edges,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/in/nodes",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_get_in_nodes,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/out/nodes",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_get_out_nodes,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/in/degree",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_get_indegree,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/out/degree",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_get_outdegree,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/adjacent",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_is_adjacent,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/adjacent/from",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_is_adjacent_from,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/node/adjacent/to",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_is_adjacent_to,
			test_digraph_teardown	);

	g_test_add ("/crank/base/digraph/node/foreach/depth",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_foreach_depth,
			test_digraph_teardown	);

	g_test_add ("/crank/base/digraph/node/foreach/breadth",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_node_foreach_breadth,
			test_digraph_teardown	);
			
	g_test_add ("/crank/base/digraph/edge/data",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_edge_get_data,
			test_digraph_teardown	);

	g_test_add ("/crank/base/digraph/edge/tail",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_edge_get_tail,
			test_digraph_teardown	);

	g_test_add ("/crank/base/digraph/edge/head",
			TestDigraphFixture,
			NULL,
			test_digraph_setup,
			test_digraph_edge_get_head,
			test_digraph_teardown	);
	
	g_test_run ();

	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static gboolean
testutil_accumulator_graph (	CrankDigraphNode*	node,
								gpointer			userdata	)
{
	GValue	value = { 0 };
	GList**	list_ptr =	(GList**) userdata;
	*list_ptr = g_list_append (*list_ptr, node);
	
	g_value_init (&value, G_TYPE_INT);
	
	crank_digraph_node_get_data (node, &value);
	
	g_message ("Node value: %s", g_strdup_value_contents (&value));
	
	g_value_unset (&value);
	return TRUE;
}
								

static void
test_digraph_setup (	TestDigraphFixture*	fixture,
					gconstpointer		userdata	)
{
	GValue	node_v = {0};
	GValue	edge_v = {0};
	
	gint	i;

	fixture->digraph = crank_digraph_new ();
	
	g_value_init (&node_v, G_TYPE_INT);
	g_value_init (&edge_v, G_TYPE_FLOAT);
	
	for (i = 0; i < 9; i++) {
		g_value_set_int (&node_v, i);
		fixture->nodes[i] = crank_digraph_add (fixture->digraph, &node_v);
	}
	
	// 0
	
	// 1->2, 1->3, 2->3
	g_value_set_float (&edge_v, 17.3f);
	fixture->edges[0] = crank_digraph_connect (fixture->digraph,
			fixture->nodes[1],
			fixture->nodes[2],
			&edge_v);
	
	g_value_set_float (&edge_v, 32.1f);
	fixture->edges[1] = crank_digraph_connect (fixture->digraph,
			fixture->nodes[1],
			fixture->nodes[3],
			&edge_v);
	
	g_value_set_float (&edge_v, 18.3f);
	fixture->edges[2] = crank_digraph_connect (fixture->digraph,
			fixture->nodes[2],
			fixture->nodes[3],
			&edge_v);
	
	// 4->5, 4->6, 4->7, 5->8, 7->6
	
	g_value_set_float (&edge_v, 21.3f);
	fixture->edges[3] = crank_digraph_connect (fixture->digraph,
			fixture->nodes[4],
			fixture->nodes[5],
			&edge_v);
	
	g_value_set_float (&edge_v, 10.5f);
	fixture->edges[4] = crank_digraph_connect (fixture->digraph,
			fixture->nodes[4],
			fixture->nodes[6],
			&edge_v);
	
	g_value_set_float (&edge_v, 17.5f);
	fixture->edges[5] = crank_digraph_connect (fixture->digraph,
			fixture->nodes[4],
			fixture->nodes[7],
			&edge_v);
	
	g_value_set_float (&edge_v, 9.4f);
	fixture->edges[6] = crank_digraph_connect (fixture->digraph,
			fixture->nodes[5],
			fixture->nodes[8],
			&edge_v);
	
	g_value_set_float (&edge_v, 19.6f);
	fixture->edges[7] = crank_digraph_connect (fixture->digraph,
			fixture->nodes[7],
			fixture->nodes[6],
			&edge_v);
	
	
	g_value_unset (&node_v);
	g_value_unset (&edge_v);
}

static void
test_digraph_teardown (	TestDigraphFixture*	fixture,
						gconstpointer		userdata	)
{
	crank_digraph_unref (fixture->digraph);
}

static void
test_digraph_get_nodes (	TestDigraphFixture*	fixture,
						gconstpointer		userdata	)
{
	GPtrArray*		nodes;
	guint			i;
	guint			j;
	
	nodes = crank_digraph_get_nodes (fixture->digraph);
	
	// Checks the nodes we got, are same to nodes in fixture.
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++)
			if (fixture->nodes[i] == g_ptr_array_index(nodes, j)) break;
		if (j == 9) g_test_fail ();
	}
	
}

static void
test_digraph_get_edges (	TestDigraphFixture*	fixture,
						gconstpointer		userdata	)
{
	GPtrArray*			edges;
	guint			i;
	guint			j;
	
	edges = crank_digraph_get_edges (fixture->digraph);
	
	
	// Checks the edges we got, are same to edges in fixture.
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++)
			if (fixture->edges[i] == g_ptr_array_index(edges, j)) break;
		if (j == 8) g_test_fail ();
	}
}

static void
test_digraph_disconnect (	TestDigraphFixture*	fixture,
						gconstpointer		userdata	)
{
	GPtrArray*	edges;
								
	g_assert (	 crank_digraph_disconnect (	fixture->digraph,
											fixture->nodes[2],
											fixture->nodes[3])	);
											
	g_assert (	 crank_digraph_disconnect (	fixture->digraph,
											fixture->nodes[4],
											fixture->nodes[6])	);

	// Removing non existing edge.
	g_assert (! crank_digraph_disconnect (	fixture->digraph,
											fixture->nodes[0],
											fixture->nodes[1])	);
											
	// Removing reversed edge.
	g_assert (! crank_digraph_disconnect (	fixture->digraph,
											fixture->nodes[6],
											fixture->nodes[7])	);
	
	// Removing non-directly connected one.
	g_assert (! crank_digraph_disconnect (	fixture->digraph,
											fixture->nodes[4],
											fixture->nodes[8])	);

	// Removing already removed one
	g_assert (! crank_digraph_disconnect (	fixture->digraph,
											fixture->nodes[4],
											fixture->nodes[6])	);
	
	edges = crank_digraph_get_edges (fixture->digraph);
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (edges, CrankDigraphEdge*, edge)
	
		g_assert (edge != fixture->edges[2]);
		g_assert (edge != fixture->edges[4]);
	
	CRANK_FOREACH_G_PTR_ARRAY_END
}

static void
test_digraph_disconnect_edge (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GPtrArray*		edges;
						
	crank_digraph_disconnect_edge (fixture->digraph, fixture->edges[2]);
	crank_digraph_disconnect_edge (fixture->digraph, fixture->edges[4]);
	
	
	edges = crank_digraph_get_edges (fixture->digraph);
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (edges, CrankDigraphEdge*, edge)
	
		g_assert (edge != fixture->edges[2]);
		g_assert (edge != fixture->edges[4]);
	
	CRANK_FOREACH_G_PTR_ARRAY_END
}


static void
test_digraph_node_get_data (	TestDigraphFixture*	fixture,
							gconstpointer		userdata	)
{
	GValue	node_v = {0};
	guint	i;
	
	g_value_init (&node_v, G_TYPE_INT);
	
	for (i = 0; i < 9; i ++) {
		crank_digraph_node_get_data (fixture->nodes[i], &node_v);
		g_assert_cmpint (g_value_get_int (&node_v), ==, i);
	}
}

static void
test_digraph_node_get_in_edges (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GPtrArray*	edge_list;
	
	edge_list = crank_digraph_node_get_in_edges (fixture->nodes[3]);
	
	g_assert (g_ptr_array_index (edge_list, 0) == fixture->edges[1]);
	g_assert (g_ptr_array_index (edge_list, 1) == fixture->edges[2]);
}

static void
test_digraph_node_get_out_edges (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GPtrArray*	edge_list;
	
	edge_list = crank_digraph_node_get_out_edges (fixture->nodes[4]);
	
	g_assert (g_ptr_array_index (edge_list, 0) == fixture->edges[3]);
	g_assert (g_ptr_array_index (edge_list, 1) == fixture->edges[4]);
	g_assert (g_ptr_array_index (edge_list, 2) == fixture->edges[5]);
}

static void
test_digraph_node_get_in_nodes (	TestDigraphFixture*	fixture,
									gconstpointer		userdata	)
{
	GList*	node_list;
	
	node_list = crank_digraph_node_get_in_nodes (fixture->nodes[3]);
	
	g_assert (g_list_find (node_list, fixture->nodes[1]) != NULL);
	g_assert (g_list_find (node_list, fixture->nodes[2]) != NULL);
	
	g_list_free (node_list);
}

static void
test_digraph_node_get_out_nodes (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GList*	node_list;
	
	node_list = crank_digraph_node_get_out_nodes (fixture->nodes[4]);
	
	g_assert (g_list_find (node_list, fixture->nodes[5]) != NULL);
	g_assert (g_list_find (node_list, fixture->nodes[6]) != NULL);
	g_assert (g_list_find (node_list, fixture->nodes[7]) != NULL);
	
	g_list_free (node_list);
}

static void
test_digraph_node_get_indegree (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	g_assert_cmpuint (crank_digraph_node_get_indegree (fixture->nodes[2]), ==, 1);
	g_assert_cmpuint (crank_digraph_node_get_indegree (fixture->nodes[5]), ==, 1);
	g_assert_cmpuint (crank_digraph_node_get_indegree (fixture->nodes[6]), ==, 2);
}

static void
test_digraph_node_get_outdegree (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	g_assert_cmpuint (crank_digraph_node_get_outdegree (fixture->nodes[2]), ==, 1);
	g_assert_cmpuint (crank_digraph_node_get_outdegree (fixture->nodes[5]), ==, 1);
	g_assert_cmpuint (crank_digraph_node_get_outdegree (fixture->nodes[6]), ==, 0);
}

static void
test_digraph_node_is_adjacent (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	g_assert (crank_digraph_node_is_adjacent (fixture->nodes[2], fixture->nodes[3]));
	g_assert (crank_digraph_node_is_adjacent (fixture->nodes[4], fixture->nodes[6]));
	
	g_assert (crank_digraph_node_is_adjacent (fixture->nodes[6], fixture->nodes[7]));
	
	g_assert (! crank_digraph_node_is_adjacent (fixture->nodes[0], fixture->nodes[2]));
	g_assert (! crank_digraph_node_is_adjacent (fixture->nodes[4], fixture->nodes[8]));
}


static void
test_digraph_node_is_adjacent_from (	TestDigraphFixture*	fixture,
										gconstpointer		userdata	)
{
	g_assert (crank_digraph_node_is_adjacent_from (fixture->nodes[3], fixture->nodes[2]));
	g_assert (crank_digraph_node_is_adjacent_from (fixture->nodes[6], fixture->nodes[4]));
	
	g_assert (! crank_digraph_node_is_adjacent_from (fixture->nodes[7], fixture->nodes[6]));
	
	g_assert (! crank_digraph_node_is_adjacent_from (fixture->nodes[2], fixture->nodes[0]));
	g_assert (! crank_digraph_node_is_adjacent_from (fixture->nodes[8], fixture->nodes[4]));
}


static void
test_digraph_node_is_adjacent_to (	TestDigraphFixture*	fixture,
										gconstpointer		userdata	)
{
	g_assert (crank_digraph_node_is_adjacent_to (fixture->nodes[2], fixture->nodes[3]));
	g_assert (crank_digraph_node_is_adjacent_to (fixture->nodes[4], fixture->nodes[6]));
	
	g_assert (! crank_digraph_node_is_adjacent_to (fixture->nodes[6], fixture->nodes[7]));
	
	g_assert (! crank_digraph_node_is_adjacent_to (fixture->nodes[0], fixture->nodes[2]));
	g_assert (! crank_digraph_node_is_adjacent_to (fixture->nodes[4], fixture->nodes[8]));
}

static void
test_digraph_node_foreach_depth (	TestDigraphFixture*	fixture,
							gconstpointer		userdata	)
{
	GList*		node_list = NULL;
	
	g_assert (	crank_digraph_node_foreach_depth (	fixture->nodes[0],
													testutil_accumulator_graph,
													&node_list	)	);

	g_assert ( node_list->data == fixture->nodes[0] );
	g_assert_cmpint ( g_list_length (node_list), ==, 1);
	
	g_list_free (node_list);
	node_list = NULL;
	
	g_assert (	crank_digraph_node_foreach_depth (	fixture->nodes[1],
													testutil_accumulator_graph,
													&node_list	)	);

	g_assert_cmpint ( g_list_length (node_list), ==, 3);
	g_assert ( g_list_nth_data (node_list, 0) == fixture->nodes[1]	);
	g_assert ( g_list_nth_data (node_list, 1) == fixture->nodes[3]	);
	g_assert ( g_list_nth_data (node_list, 2) == fixture->nodes[2]	);
	
	g_list_free (node_list);
	node_list = NULL;
	
	g_assert (	crank_digraph_node_foreach_depth (	fixture->nodes[4],
													testutil_accumulator_graph,
													&node_list	)	);

	g_assert_cmpint ( g_list_length (node_list), ==, 5);
	g_assert ( g_list_nth_data (node_list, 0) == fixture->nodes[4]	);
	g_assert ( g_list_nth_data (node_list, 1) == fixture->nodes[7]	);
	g_assert ( g_list_nth_data (node_list, 2) == fixture->nodes[6]	);
	g_assert ( g_list_nth_data (node_list, 3) == fixture->nodes[5]	);
	g_assert ( g_list_nth_data (node_list, 4) == fixture->nodes[8]	);
	
	g_list_free (node_list);
	node_list = NULL;
}
										
static void
test_digraph_node_foreach_breadth (	TestDigraphFixture*	fixture,
									gconstpointer		userdata	)
{
	GList*		node_list = NULL;
	
	g_assert (	crank_digraph_node_foreach_breadth (	fixture->nodes[0],
														testutil_accumulator_graph,
														&node_list	)	);

	g_assert ( g_list_nth_data (node_list, 0) == fixture->nodes[0] );
	g_assert_cmpint ( g_list_length (node_list), ==, 1);

	
	g_list_free (node_list);
	node_list = NULL;
	
	g_assert (	crank_digraph_node_foreach_breadth (	fixture->nodes[1],
														testutil_accumulator_graph,
														&node_list	)	);

	g_assert ( g_list_nth_data (node_list, 0) == fixture->nodes[1]	);
	g_assert ( g_list_nth_data (node_list, 1) == fixture->nodes[2]	);
	g_assert ( g_list_nth_data (node_list, 2) == fixture->nodes[3]	);
	g_assert_cmpint ( g_list_length (node_list), ==, 3);
	
	g_list_free (node_list);
	node_list = NULL;
	
	g_assert (	crank_digraph_node_foreach_breadth (	fixture->nodes[4],
														testutil_accumulator_graph,
														&node_list	)	);

	g_assert ( g_list_nth_data (node_list, 0) == fixture->nodes[4]	);
	g_assert ( g_list_nth_data (node_list, 1) == fixture->nodes[5]	);
	g_assert ( g_list_nth_data (node_list, 2) == fixture->nodes[6]	);
	g_assert ( g_list_nth_data (node_list, 3) == fixture->nodes[7]	);
	g_assert ( g_list_nth_data (node_list, 4) == fixture->nodes[8]	);
	g_assert_cmpint ( g_list_length (node_list), ==, 5);
	
	g_list_free (node_list);
	node_list = NULL;
}


static void
test_digraph_edge_get_data (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GValue	edge_v = {0};
	
	g_value_init (&edge_v, G_TYPE_FLOAT);
	
	crank_digraph_edge_get_data (fixture->edges[5], &edge_v);

	g_assert_cmpfloat (g_value_get_float (&edge_v), ==, 17.5f);

	g_value_unset (&edge_v);
}

static void
test_digraph_edge_get_tail (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	g_assert (crank_digraph_edge_get_tail (fixture->edges[3]) == fixture->nodes[4]);
	g_assert (crank_digraph_edge_get_tail (fixture->edges[5]) == fixture->nodes[4]);
	g_assert (crank_digraph_edge_get_tail (fixture->edges[7]) == fixture->nodes[7]);
}
static void
test_digraph_edge_get_head (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	g_assert (crank_digraph_edge_get_head (fixture->edges[1]) == fixture->nodes[3]);
	g_assert (crank_digraph_edge_get_head (fixture->edges[2]) == fixture->nodes[3]);
	g_assert (crank_digraph_edge_get_head (fixture->edges[4]) == fixture->nodes[6]);
}
