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

typedef struct {
  CrankDigraph *graph;
  CrankDigraphNode *nodes[16];
  CrankDigraphEdge *edges[32];
} TestFixtureDigraph;

void   test_fixture_init (TestFixtureDigraph *ft,
                          gconstpointer       userdata);

void   test_fixture_fini (TestFixtureDigraph *ft,
                          gconstpointer       userdata);

gfloat testutil_edge_distance (CrankDigraphEdge *edge,
                               gpointer          userdata);

gfloat testutil_heuristic (CrankDigraphNode *from,
                           CrankDigraphNode *to,
                           gpointer          userdata);

void   test_dijkstra (TestFixtureDigraph *ft,
                      gconstpointer       userdata);

void   test_astar (TestFixtureDigraph *ft,
                   gconstpointer       userdata);


//////// Main //////////////////////////////////////////////////////////////////

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


//////// Definition ////////////////////////////////////////////////////////////

void
test_fixture_init (TestFixtureDigraph *ft,
                   gconstpointer       userdata)
{
  CrankVecInt2 pos;

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
  ft->edges[0] =
    crank_digraph_connect_void (ft->graph, ft->nodes[0], ft->nodes[4]);
  ft->edges[1] =
    crank_digraph_connect_void (ft->graph, ft->nodes[4], ft->nodes[0]);

  // edge 2, 3 for [0, 7]
  ft->edges[2] =
    crank_digraph_connect_void (ft->graph, ft->nodes[0], ft->nodes[7]);
  ft->edges[3] =
    crank_digraph_connect_void (ft->graph, ft->nodes[7], ft->nodes[0]);

  // edge 0, 1 for [1, 3]
  ft->edges[4] =
    crank_digraph_connect_void (ft->graph, ft->nodes[1], ft->nodes[3]);
  ft->edges[5] =
    crank_digraph_connect_void (ft->graph, ft->nodes[3], ft->nodes[1]);

  // edge 0, 1 for [1, 5]
  ft->edges[6] =
    crank_digraph_connect_void (ft->graph, ft->nodes[1], ft->nodes[5]);
  ft->edges[7] =
    crank_digraph_connect_void (ft->graph, ft->nodes[5], ft->nodes[1]);

  // edge 0, 1 for [1, 6]
  ft->edges[8] =
    crank_digraph_connect_void (ft->graph, ft->nodes[1], ft->nodes[6]);
  ft->edges[9] =
    crank_digraph_connect_void (ft->graph, ft->nodes[6], ft->nodes[1]);

  // edge 0, 1 for [2, 3]
  ft->edges[10] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[2],
                                              ft->nodes[3]);
  ft->edges[11] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[3],
                                              ft->nodes[2]);

  // edge 0, 1 for [2, 4]
  ft->edges[12] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[2],
                                              ft->nodes[4]);
  ft->edges[13] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[4],
                                              ft->nodes[2]);

  // edge 0, 1 for [2, 5]
  ft->edges[14] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[2],
                                              ft->nodes[5]);
  ft->edges[15] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[5],
                                              ft->nodes[2]);

  // edge 0, 1 for [3, 6]
  ft->edges[16] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[3],
                                              ft->nodes[6]);
  ft->edges[17] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[6],
                                              ft->nodes[3]);

  // edge 0, 1 for [4, 6]
  ft->edges[18] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[4],
                                              ft->nodes[6]);
  ft->edges[19] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[6],
                                              ft->nodes[4]);

  // edge 0, 1 for [6, 7]
  ft->edges[20] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[6],
                                              ft->nodes[7]);
  ft->edges[21] = crank_digraph_connect_void (ft->graph,
                                              ft->nodes[7],
                                              ft->nodes[6]);
}

void
test_fixture_fini (TestFixtureDigraph *ft,
                   gconstpointer       userdata)
{
  crank_digraph_unref (ft->graph);
}


gfloat
testutil_edge_distance (CrankDigraphEdge *edge,
                        gpointer          userdata)
{
  CrankDigraphNode *tail;
  CrankDigraphNode *head;

  CrankVecInt2 disp;

  tail = crank_digraph_edge_get_tail (edge);
  head = crank_digraph_edge_get_head (edge);

  crank_vec_int2_init_arr (
    &disp,
    (gint*) crank_digraph_node_get_boxed (head) );

  crank_vec_int2_sub_self (&disp,
                           (CrankVecInt2*) crank_digraph_node_get_boxed (tail));

  return crank_vec_int2_get_magn (&disp);
}

gfloat
testutil_heuristic (CrankDigraphNode *from,
                    CrankDigraphNode *to,
                    gpointer          userdata)
{
  CrankVecInt2 disp;

  crank_vec_int2_init_arr (
    &disp,
    (gint*) crank_digraph_node_get_boxed (to)   );

  crank_vec_int2_sub_self (&disp,
                           (CrankVecInt2*) crank_digraph_node_get_boxed (from));

  return crank_vec_int2_get_magn (&disp);
}

void
test_dijkstra (TestFixtureDigraph *ft,
               gconstpointer       userdata)
{
  GList *path;

  path = crank_dijkstra_digraph (ft->nodes[0],
                                 ft->nodes[1],
                                 testutil_edge_distance,
                                 NULL);

  crank_assert_eq_glist_imm (path,
                             ft->nodes[0],
                             ft->nodes[4],
                             ft->nodes[2],
                             ft->nodes[3],
                             ft->nodes[1]);

  g_list_free (path);
}

void
test_astar (TestFixtureDigraph *ft,
            gconstpointer       userdata)
{
  GList *path;

  path = crank_astar_digraph (ft->nodes[5], ft->nodes[7],
                              testutil_edge_distance, NULL,
                              testutil_heuristic, NULL);

  crank_assert_eq_glist_imm (path,
                             ft->nodes[5],
                             ft->nodes[2],
                             ft->nodes[4],
                             ft->nodes[0],
                             ft->nodes[7]);

  g_list_free (path);
}