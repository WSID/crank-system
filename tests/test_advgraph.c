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

typedef struct {
	CrankDigraph*		graph;
	CrankDigraphNode*	nodes[16];
	CrankDigraphNode*	edges[32];
} TestFixtureDigraph;

void
test_fixture_init (	TestFixtureDigraph*	ft,
					gpointer			userdata	)
{
	CrankVecInt2	pos;
	
	ft->graph = crank_digraph_new ();
	
	// The nodes are positioned According to below map. (lines are edges)
	//
	//    -5-4-3-2-1 0 1 2 3 4 5 6
	//  6                        0
	//  5                    ---/|
	//  4                ---/    |
	//  3              4/        |
	//  2    5-\       |\        |
	//  1   /   --\    2|        7
	//  0   |      --3/ |       /
	// -1   |     /   \ \      /
	// -2  /    /-     \ |   -/
	// -3  |  /-        \|  /
	// -4  |/-           \ /
	// -5  1-------------6/     

	//0 at (6, 6)
	crank_vec_int2_init (&pos, 6, 6);
	ft->nodes[0] = crank_digraph_add_boxed (ft->graph, CRANK_TYPE_VEC_INT2, &pos);
	
	//1 at (-5, -5)
	crank_vec_int2_init (&pos, -5, -5);
	ft->nodes[1] = crank_digraph_add_boxed (ft->graph, CRANK_TYPE_VEC_INT2, &pos);
	
	//2 at (1, 1)
	crank_vec_int2_init (&pos, 1, 1);
	ft->nodes[2] = crank_digraph_add_boxed (ft->graph, CRANK_TYPE_VEC_INT2, &pos);
	
	//3 at (0, 0)
	crank_vec_int2_init (&pos, 0, 0);
	ft->nodes[3] = crank_digraph_add_boxed (ft->graph, CRANK_TYPE_VEC_INT2, &pos);
	
	//4 at (1, 3)
	crank_vec_int2_init (&pos, 1, 3);
	ft->nodes[4] = crank_digraph_add_boxed (ft->graph, CRANK_TYPE_VEC_INT2, &pos);
	
	//5 at (-4, 2)
	crank_vec_int2_init (&pos, -4, 2);
	ft->nodes[5] = crank_digraph_add_boxed (ft->graph, CRANK_TYPE_VEC_INT2, &pos);
	
	//6 at (2, -5)
	crank_vec_int2_init (&pos, 2, -5);
	ft->nodes[6] = crank_digraph_add_boxed (ft->graph, CRANK_TYPE_VEC_INT2, &pos);
	
	//7 at (6, 1)
	crank_vec_int2_init (&pos, 6, 1);
	ft->nodes[7] = crank_digraph_add_boxed (ft->graph, CRANK_TYPE_VEC_INT2, &pos);
	
	
	// edge 0, 1 for [0, 4]
	ft->edges[0] = crank_digraph_connect_void (ft->graph, ft->nodes[0], ft->nodes[4]);
	ft->edges[1] = crank_digraph_connect_void (ft->graph, ft->nodes[4], ft->nodes[0]);
	
	// edge 2, 3 for [0, 7]
	ft->edges[2] = crank_digraph_connect_void (ft->graph, ft->nodes[0], ft->nodes[7]);
	ft->edges[3] = crank_digraph_connect_void (ft->graph, ft->nodes[7], ft->nodes[0]);
	
	// edge 0, 1 for [1, 3]
	ft->edges[4] = crank_digraph_connect_void (ft->graph, ft->nodes[1], ft->nodes[3]);
	ft->edges[5] = crank_digraph_connect_void (ft->graph, ft->nodes[3], ft->nodes[1]);
	
	// edge 0, 1 for [1, 5]
	ft->edges[6] = crank_digraph_connect_void (ft->graph, ft->nodes[1], ft->nodes[5]);
	ft->edges[7] = crank_digraph_connect_void (ft->graph, ft->nodes[5], ft->nodes[1]);
	
	// edge 0, 1 for [1, 6]
	ft->edges[8] = crank_digraph_connect_void (ft->graph, ft->nodes[1], ft->nodes[6]);
	ft->edges[9] = crank_digraph_connect_void (ft->graph, ft->nodes[6], ft->nodes[1]);
	
	// edge 0, 1 for [2, 3]
	ft->edges[10] = crank_digraph_connect_void (ft->graph, ft->nodes[2], ft->nodes[3]);
	ft->edges[11] = crank_digraph_connect_void (ft->graph, ft->nodes[3], ft->nodes[2]);
	
	// edge 0, 1 for [2, 4]
	ft->edges[12] = crank_digraph_connect_void (ft->graph, ft->nodes[2], ft->nodes[4]);
	ft->edges[13] = crank_digraph_connect_void (ft->graph, ft->nodes[4], ft->nodes[2]);
	
	// edge 0, 1 for [2, 5]
	ft->edges[14] = crank_digraph_connect_void (ft->graph, ft->nodes[2], ft->nodes[5]);
	ft->edges[15] = crank_digraph_connect_void (ft->graph, ft->nodes[5], ft->nodes[2]);
	
	// edge 0, 1 for [3, 6]
	ft->edges[16] = crank_digraph_connect_void (ft->graph, ft->nodes[3], ft->nodes[6]);
	ft->edges[17] = crank_digraph_connect_void (ft->graph, ft->nodes[6], ft->nodes[3]);
	
	// edge 0, 1 for [4, 6]
	ft->edges[18] = crank_digraph_connect_void (ft->graph, ft->nodes[4], ft->nodes[6]);
	ft->edges[19] = crank_digraph_connect_void (ft->graph, ft->nodes[6], ft->nodes[4]);
	
	// edge 0, 1 for [6, 7]
	ft->edges[20] = crank_digraph_connect_void (ft->graph, ft->nodes[6], ft->nodes[7]);
	ft->edges[21] = crank_digraph_connect_void (ft->graph, ft->nodes[7], ft->nodes[6]);
}

void
test_fixture_fini (	TestFixtureDigraph*	ft,
					gpointer			userdata	)
{
	crank_digraph_unref (ft->graph);
}


gfloat
testutil_edge_distance (CrankDigraphEdge*	edge,
						gpointer			userdata	)
{
	CrankDigraphNode*	tail;
	CrankDigraphNode*	head;
	
	CrankVecInt2	disp;
	
	tail = crank_digraph_edge_get_tail (edge);
	head = crank_digraph_edge_get_head (edge);

	crank_vec_int2_init_arr (
			&disp,
			(gint*)	crank_digraph_node_get_boxed (head)	);

	crank_vec_int2_sub (&disp, (CrankVecInt2*) crank_digraph_node_get_boxed (tail), &disp);
	
	return crank_vec_int2_get_magn (&disp);
}

gfloat
testutil_heuristic (CrankDigraphNode*	from,
					CrankDigraphNode*	to,
					gpointer			userdata	)
{
	CrankVecInt2	disp;

	crank_vec_int2_init_arr (
			&disp,
			(gint*)	crank_digraph_node_get_boxed (to)	);

	crank_vec_int2_sub (&disp, (CrankVecInt2*) crank_digraph_node_get_boxed (from), &disp);
	
	return crank_vec_int2_get_magn (&disp);
}

void
test_dijkstra (	TestFixtureDigraph*	ft,
				gpointer			userdata	)
{
	GList*	path;
	
	path = crank_dijkstra_digraph (ft->nodes[0], ft->nodes[1], testutil_edge_distance, NULL);
	
	g_assert_cmpint (g_list_length (path), ==, 5);
	g_assert (g_list_nth_data (path, 0) == ft->nodes[0]);
	g_assert (g_list_nth_data (path, 1) == ft->nodes[4]);
	g_assert (g_list_nth_data (path, 2) == ft->nodes[2]);
	g_assert (g_list_nth_data (path, 3) == ft->nodes[3]);
	g_assert (g_list_nth_data (path, 4) == ft->nodes[1]);
	
	g_list_free (path);
}

void
test_astar (	TestFixtureDigraph*	ft,
				gpointer			userdata	)
{
	GList*	path;
	
	path = crank_astar_digraph (ft->nodes[5], ft->nodes[7], 
			testutil_edge_distance, NULL,
			testutil_heuristic, NULL	);
	
	g_assert_cmpint (g_list_length (path), ==, 5);
	g_assert (g_list_nth_data (path, 0) == ft->nodes[5]);
	g_assert (g_list_nth_data (path, 1) == ft->nodes[2]);
	g_assert (g_list_nth_data (path, 2) == ft->nodes[4]);
	g_assert (g_list_nth_data (path, 3) == ft->nodes[0]);
	g_assert (g_list_nth_data (path, 4) == ft->nodes[7]);
	
	g_list_free (path);
}	



gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);

	g_test_add ("/crank/base/advgraph/dijkstra/digraph",
			TestFixtureDigraph,
			NULL,
			test_fixture_init,
			test_dijkstra,
			test_fixture_fini);
			
	g_test_add ("/crank/base/advgraph/astar/digraph",
			TestFixtureDigraph,
			NULL,
			test_fixture_init,
			test_astar,
			test_fixture_fini);
	
	g_test_run ();

	return 0;
}

