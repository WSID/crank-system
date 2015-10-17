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

static gfloat        cost_edge_func (CrankDigraphEdge *edge,
                                     gpointer          userdata);

static gfloat        heuristic_func (CrankDigraphNode *from,
                                     CrankDigraphNode *to,
                                     gpointer          userdata);

static CrankDigraph *create_rand_graph (CrankBenchRun *run);

static void          test_complete_graph (CrankBenchRun *run);

static void          test_depth_first (CrankBenchRun *run);

static void          test_breadth_first (CrankBenchRun *run);

static void          test_dijkstra (CrankBenchRun *run);

//static void	test_astar (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint   argc,
      gchar *argv[])
{
  CrankBenchParamNode  *params;

  crank_bench_init (&argc, &argv);

  crank_bench_add ("/crank/base/digraph/complete-graph",
                   (CrankBenchFunc)test_complete_graph, NULL, NULL);

  crank_bench_add ("/crank/base/digraph/depth-first",
                   (CrankBenchFunc)test_depth_first, NULL, NULL);

  crank_bench_add ("/crank/base/digraph/breadth-first",
                   (CrankBenchFunc)test_breadth_first, NULL, NULL);

  crank_bench_add ("/crank/base/digraph/dijkstra",
                   (CrankBenchFunc)test_dijkstra, NULL, NULL);

  params = crank_bench_param_node_new ();

  crank_bench_param_node_set_uint (params, "repeat", 8);
  crank_bench_param_node_set_uint (params, "N", 1024);
  crank_bench_param_node_set_float (params, "connect-ratio", 0.1f);

  crank_bench_set_param ("/", params);

  crank_bench_param_node_free (params);

  return crank_bench_run ();
}


//////// Definition ////////////////////////////////////////////////////////////

static gboolean
doing_nothing (CrankDigraphNode *node,
               gpointer          userdata)
{
  return TRUE;
}


static gfloat
cost_edge_func (CrankDigraphEdge *edge,
                gpointer          uesrdata)
{
  CrankDigraphNode *tail;
  CrankDigraphNode *head;

  CrankVecFloat3 diff;

  tail = crank_digraph_edge_get_tail (edge);
  head = crank_digraph_edge_get_head (edge);

  crank_vec_float3_init_arr (&diff, (gfloat*) crank_digraph_node_get_boxed (head));

  crank_vec_float3_sub_self (&diff,
                           (CrankVecFloat3*) crank_digraph_node_get_boxed (
                             tail) );

  return crank_vec_float3_get_magn (&diff);
}

static gfloat
heuristic_func (CrankDigraphNode *from,
                CrankDigraphNode *to,
                gpointer          uesrdata)
{
  CrankVecFloat3 diff;

  crank_vec_float3_init_arr (&diff, (gfloat*) crank_digraph_node_get_boxed (to));

  crank_vec_float3_sub_self (&diff,
                            (CrankVecFloat3*) crank_digraph_node_get_boxed (
                             from) );

  return crank_vec_float3_get_magn (&diff);
}


CrankDigraph*
create_rand_graph (CrankBenchRun *run)
{
  CrankDigraph *graph = crank_digraph_new ();
  CrankDigraphNode **nodes;

  guint node_count = crank_bench_run_get_param_uint (run, "N", 0);
  gfloat connect_ratio = crank_bench_run_get_param_float (run, "connect-ratio", 0.0f);

  guint connect_possible = node_count * (node_count - 1);
  guint connect_count = (guint) (connect_possible * connect_ratio);

  guint i;
  guint j;

  for (i = 0; i < node_count; i++)
    {
      CrankVecFloat3 pos =
      {
        crank_bench_run_rand_float (run),
        crank_bench_run_rand_float (run),
        crank_bench_run_rand_float (run)
      };

      crank_digraph_add_boxed (graph, CRANK_TYPE_VEC_FLOAT3, &pos);
    }

  nodes = (CrankDigraphNode**) (crank_digraph_get_nodes (graph)->pdata);

  // Add edges
  for (i = 0; i < node_count; i++)
    {
      for (j = 0; j < i; j++)
        {
          if (crank_bench_run_rand_int_range (run, 0, connect_possible) < connect_count)
            {
              crank_digraph_connect_void (graph, nodes[i], nodes[j]);
              connect_count--;
            }
          connect_possible--;
        }

      for (j = i + 1; j < node_count; j++)
        {
          if (crank_bench_run_rand_int_range (run, 0, connect_possible) < connect_count)
            {
              crank_digraph_connect_void (graph, nodes[i], nodes[j]);
              connect_count--;
            }
          connect_possible--;
        }
    }

  return graph;
}


static void
test_complete_graph (CrankBenchRun *run)
{
  // Constructs Complete digraph with 1024 nodes

  // 1024 nodes are constructed.
  // 1047552 edges are constructed.

  // The individual nodes are given integer value as index.

  CrankDigraph *digraph;
  CrankDigraphNode **nodes;

  guint i;
  guint j;

  guint n = crank_bench_run_get_param_uint (run, "N", 0);


  crank_bench_run_timer_start (run);

  digraph = crank_digraph_new ();
  nodes = g_new (CrankDigraphNode*, n);

  // build nodes
  for (i = 0; i < n; i++)
    {
      GValue value = { 0 };
      g_value_init (&value, G_TYPE_INT);

      g_value_set_int (&value, i);

      nodes[i] = crank_digraph_add (digraph, &value);
    }

  crank_bench_run_timer_add_result_elapsed (run, "time-node");

  // build edges
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < i; j++)
        {
          crank_digraph_connect_void (digraph, nodes[i], nodes[j]);
        }
      for (j = i + 1; j < n; j++)
        {
          crank_digraph_connect_void (digraph, nodes[i], nodes[j]);
        }
    }

  crank_bench_run_timer_add_result_elapsed (run, "time-all");

  g_free (nodes);
  crank_digraph_unref (digraph);
}

static void
test_depth_first (CrankBenchRun *run)
{
  CrankDigraph *digraph;
  CrankDigraphNode *node;

  digraph = create_rand_graph (run);
  node = g_ptr_array_index (crank_digraph_get_nodes (digraph), 0);


  crank_bench_run_timer_start (run);

  // perform a depth first iteration
  crank_digraph_node_foreach_depth (node, doing_nothing, NULL);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_digraph_unref (digraph);
}

static void
test_breadth_first (CrankBenchRun *run)
{
  CrankDigraph *digraph;
  CrankDigraphNode *node;

  digraph = create_rand_graph (run);
  node = g_ptr_array_index (crank_digraph_get_nodes (digraph), 0);

  crank_bench_run_timer_start (run);

  // perform a depth first iteration
  crank_digraph_node_foreach_breadth (node, doing_nothing, NULL);

  crank_bench_run_timer_add_result_elapsed (run, "time");

  crank_digraph_unref (digraph);
}


static void
test_dijkstra (CrankBenchRun *run)
{
  CrankDigraph *digraph;
  CrankDigraphNode *node_from;
  CrankDigraphNode *node_to;

  GList *path;
  guint n = crank_bench_run_get_param_uint (run, "N", 0);

  digraph = create_rand_graph (run);
  node_from = g_ptr_array_index (crank_digraph_get_nodes (digraph), n / 2);
  node_to = g_ptr_array_index (crank_digraph_get_nodes (digraph), (n / 2) + 1);

  crank_bench_run_timer_start (run);

  // perform dijkstra path finding
  path =  crank_dijkstra_digraph (node_from, node_to, cost_edge_func, NULL);

  crank_bench_run_timer_add_result_elapsed (run, "time");
  crank_bench_run_add_result_uint (run, "path-length", g_list_length (path));

  g_list_free (path);

  crank_digraph_unref (digraph);
}
