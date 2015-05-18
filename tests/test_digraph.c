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

typedef struct _TestDigraphFixture {
	CrankDigraph*		digraph;
	CrankDigraphNode*	nodes[16];
	CrankDigraphEdge*	edges[16];
} TestDigraphFixture;

void		test_digraph_setup (		TestDigraphFixture*	fixture,
									gconstpointer		userdata	);

void		test_digraph_teardown (	TestDigraphFixture*	fixture,
									gconstpointer		userdata	);

void		test_digraph_get_nodes (	TestDigraphFixture*	fixture,
									gconstpointer		userdata	);

void		test_digraph_get_edges (	TestDigraphFixture*	fixture,
									gconstpointer		userdata	);

void		test_digraph_disconnect (	TestDigraphFixture*	fixture,
									gconstpointer		userdata	);

void		test_digraph_disconnect_edge (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);

void		test_digraph_node_get_data (	TestDigraphFixture*	fixture,
										gconstpointer		userdata	);
										
void		test_digraph_node_get_in_edges (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
void		test_digraph_node_get_out_edges (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
										
void		test_digraph_node_get_in_nodes (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
void		test_digraph_node_get_out_nodes (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
void		test_digraph_node_get_indegree (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
void		test_digraph_node_get_outdegree (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
void		test_digraph_node_is_adjacent (	TestDigraphFixture*	fixture,
											gconstpointer		userdata	);
											
void		test_digraph_node_is_adjacent_from (	TestDigraphFixture*	fixture,
													gconstpointer		userdata	);
											
void		test_digraph_node_is_adjacent_to (	TestDigraphFixture*	fixture,
												gconstpointer		userdata	);

void		test_digraph_edge_get_tail (	TestDigraphFixture*	fixture,
										gconstpointer		userdata	);

void		test_digraph_edge_get_head (	TestDigraphFixture*	fixture,
										gconstpointer		userdata	);

gint
main (gint   argc,
      gchar *argv[])
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


void
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

void
test_digraph_teardown (	TestDigraphFixture*	fixture,
						gconstpointer		userdata	)
{
	crank_digraph_unref (fixture->digraph);
}

void
test_digraph_get_nodes (	TestDigraphFixture*	fixture,
						gconstpointer		userdata	)
{
	GList*			node_list;
	guint			i;
	
	node_list = crank_digraph_get_nodes (fixture->digraph);
	
	
	// 얻은 노드들이 픽스쳐에서 얻은 노드들과 같은지 봅니다.
	for (i = 0; i < 9; i++)
		g_assert (g_list_find (node_list, fixture->nodes[i]) != NULL);
}

void
test_digraph_get_edges (	TestDigraphFixture*	fixture,
						gconstpointer		userdata	)
{
	GList*			edge_list;
	guint			i;
	
	edge_list = crank_digraph_get_edges (fixture->digraph);
	
	
	// 얻은 변들이 픽스쳐에서 얻은 변들과 같은지 봅니다.
	for (i = 0; i < 8; i++)
		g_assert (g_list_find (edge_list, fixture->edges[i]) != NULL);
}

void
test_digraph_disconnect (	TestDigraphFixture*	fixture,
						gconstpointer		userdata	)
{
	GList*		edge_list;
								
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
	
	edge_list = crank_digraph_get_edges (fixture->digraph);
	
	g_assert (g_list_find (edge_list, fixture->edges[2]) == NULL);
	g_assert (g_list_find (edge_list, fixture->edges[4]) == NULL);
}

void
test_digraph_disconnect_edge (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GList*		edge_list = crank_digraph_get_edges (fixture->digraph);
						
	crank_digraph_disconnect_edge (fixture->digraph, fixture->edges[2]);
	crank_digraph_disconnect_edge (fixture->digraph, fixture->edges[4]);
	
	g_assert (g_list_find (edge_list, fixture->edges[2]) == NULL);
	g_assert (g_list_find (edge_list, fixture->edges[4]) == NULL);
}




void
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

void
test_digraph_node_get_in_edges (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GList*	edge_list;
	
	edge_list = crank_digraph_node_get_in_edges (fixture->nodes[3]);
	
	g_assert (g_list_find (edge_list, fixture->edges[1]) != NULL);
	g_assert (g_list_find (edge_list, fixture->edges[2]) != NULL);
}

void
test_digraph_node_get_out_edges (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GList*	edge_list;
	
	edge_list = crank_digraph_node_get_out_edges (fixture->nodes[4]);
	
	g_assert (g_list_find (edge_list, fixture->edges[3]) != NULL);
	g_assert (g_list_find (edge_list, fixture->edges[4]) != NULL);
	g_assert (g_list_find (edge_list, fixture->edges[5]) != NULL);
}

void
test_digraph_node_get_in_nodes (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	GList*	node_list;
	
	node_list = crank_digraph_node_get_in_nodes (fixture->nodes[3]);
	
	g_assert (g_list_find (node_list, fixture->nodes[1]) != NULL);
	g_assert (g_list_find (node_list, fixture->nodes[2]) != NULL);
	
	g_list_free (node_list);
}

void
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

void
test_digraph_node_get_indegree (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	g_assert_cmpuint (crank_digraph_node_get_indegree (fixture->nodes[2]), ==, 1);
	g_assert_cmpuint (crank_digraph_node_get_indegree (fixture->nodes[5]), ==, 1);
	g_assert_cmpuint (crank_digraph_node_get_indegree (fixture->nodes[6]), ==, 2);
}

void
test_digraph_node_get_outdegree (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	g_assert_cmpuint (crank_digraph_node_get_outdegree (fixture->nodes[2]), ==, 1);
	g_assert_cmpuint (crank_digraph_node_get_outdegree (fixture->nodes[5]), ==, 1);
	g_assert_cmpuint (crank_digraph_node_get_outdegree (fixture->nodes[6]), ==, 0);
}

void
test_digraph_node_is_adjacent (	TestDigraphFixture*	fixture,
								gconstpointer		userdata	)
{
	g_assert (crank_digraph_node_is_adjacent (fixture->nodes[2], fixture->nodes[3]));
	g_assert (crank_digraph_node_is_adjacent (fixture->nodes[4], fixture->nodes[6]));
	
	g_assert (crank_digraph_node_is_adjacent (fixture->nodes[6], fixture->nodes[7]));
	
	g_assert (! crank_digraph_node_is_adjacent (fixture->nodes[0], fixture->nodes[2]));
	g_assert (! crank_digraph_node_is_adjacent (fixture->nodes[4], fixture->nodes[8]));
}


void
test_digraph_node_is_adjacent_from (	TestDigraphFixture*	fixture,
										gconstpointer		userdata	)
{
	g_assert (crank_digraph_node_is_adjacent_from (fixture->nodes[3], fixture->nodes[2]));
	g_assert (crank_digraph_node_is_adjacent_from (fixture->nodes[6], fixture->nodes[4]));
	
	g_assert (! crank_digraph_node_is_adjacent_from (fixture->nodes[7], fixture->nodes[6]));
	
	g_assert (! crank_digraph_node_is_adjacent_from (fixture->nodes[2], fixture->nodes[0]));
	g_assert (! crank_digraph_node_is_adjacent_from (fixture->nodes[8], fixture->nodes[4]));
}


void
test_digraph_node_is_adjacent_to (	TestDigraphFixture*	fixture,
										gconstpointer		userdata	)
{
	g_assert (crank_digraph_node_is_adjacent_to (fixture->nodes[2], fixture->nodes[3]));
	g_assert (crank_digraph_node_is_adjacent_to (fixture->nodes[4], fixture->nodes[6]));
	
	g_assert (! crank_digraph_node_is_adjacent_to (fixture->nodes[6], fixture->nodes[7]));
	
	g_assert (! crank_digraph_node_is_adjacent_to (fixture->nodes[0], fixture->nodes[2]));
	g_assert (! crank_digraph_node_is_adjacent_to (fixture->nodes[4], fixture->nodes[8]));
}

void
test_digraph_edge_get_data (	TestDigraphFixture*	fixture,
							gconstpointer		userdata	)
{
	GValue	edge_v = {0};
	
	g_value_init (&edge_v, G_TYPE_FLOAT);
	
	crank_digraph_edge_get_data (fixture->edges[5], &edge_v);

	g_assert_cmpfloat (g_value_get_float (&edge_v), ==, 17.5f);

	g_value_unset (&edge_v);
}

void
test_digraph_edge_get_tail (	TestDigraphFixture*	fixture,
							gconstpointer		userdata	)
{
	g_assert (crank_digraph_edge_get_tail (fixture->edges[3]) == fixture->nodes[4]);
	g_assert (crank_digraph_edge_get_tail (fixture->edges[5]) == fixture->nodes[4]);
	g_assert (crank_digraph_edge_get_tail (fixture->edges[7]) == fixture->nodes[7]);
}
void
test_digraph_edge_get_head (	TestDigraphFixture*	fixture,
							gconstpointer		userdata	)
{
	g_assert (crank_digraph_edge_get_head (fixture->edges[1]) == fixture->nodes[3]);
	g_assert (crank_digraph_edge_get_head (fixture->edges[2]) == fixture->nodes[3]);
	g_assert (crank_digraph_edge_get_head (fixture->edges[4]) == fixture->nodes[6]);
}
