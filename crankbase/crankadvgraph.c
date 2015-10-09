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

#include <math.h>
#include <glib.h>
#include <glib-object.h>

#define _CRANKBASE_INSIDE

#include "crankbasemacro.h"
#include "crankdigraph.h"
#include "crankadvgraph.h"

/**
 * SECTION: crankadvgraph
 * @title: Advanced Operations on Graphs
 * @short_description: Advanced operations on graphs.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Crank System provides advanced operations on graphs (and matrices)
 *
 * # Operations result in list of Nodes
 * * Minimum distance path
 *   * Dijkstra
 *   * A*
 * # Operations result in tree of Nodes
 * * Minimum distance path
 *   * Dijkstra full
 */

static void
crank_advgraph_free_float (gpointer f)
{
  g_slice_free (gfloat, f);
}

static void
crank_advgraph_set_float (GHashTable *table,
                          gpointer    key,
                          gfloat      value)
{
  gfloat *ptr = g_slice_new (gfloat);

  *ptr = value;

  g_hash_table_insert (table, key, ptr);
}

static gfloat
crank_advgraph_get_float (GHashTable  *table,
                          gpointer     key,
                          const gfloat def)
{
  gfloat *ptr = (gfloat*) g_hash_table_lookup (table, key);
  return (ptr == NULL) ? def : *ptr;
}

static gpointer
crank_advgraph_table_min (GHashTable *set,
                          GHashTable *table,
                          gfloat     *value)
{
  GHashTableIter iter;
  gpointer result;
  gpointer result_candidate = NULL;
  gfloat mvalue = INFINITY;

  g_hash_table_iter_init (&iter, set);

  while (g_hash_table_iter_next (&iter, &result_candidate, NULL))
    {
      gfloat mvalue_candidate =
          crank_advgraph_get_float (table, result_candidate, INFINITY);

      if (mvalue_candidate < mvalue)
        {
          mvalue = mvalue_candidate;
          result = result_candidate;
        }
    }

  if (value != NULL) *value = mvalue;
  return result;
}

/**
 * crank_dijkstra_digraph:
 * @from: starting node
 * @to: destination node
 * @edge_func: (scope call): cost function for each edge.
 * @userdata: (closure): user data
 *
 * Gets minimum path from @from node to @to node.
 *
 * Negative value returned from @edge_func will leads to incorrect behavior.
 *
 * If @from is not connected to @to, then result will be %NULL
 *
 * Returns: (nullable) (transfer container) (element-type CrankDigraphNode*):
 *    The path as list of #CrankDigraphNode
 */
GList*
crank_dijkstra_digraph (CrankDigraphNode         *from,
                        CrankDigraphNode         *to,
                        CrankDigraphEdgeFloatFunc edge_func,
                        gpointer                  userdata)
{
  GList *result = NULL; // List<CrankDigraphNode>
  CrankDigraphNode *result_node;

  GHashTable *dist;     // HashTable<CrankDigraphNode,gfloat>
  GHashTable *visited;  // Set<CrankDigraphNode>
  GHashTable *visiting; // Set<CrankDigarphNode>
  GHashTable *prev;     // HashTable<CrankDigraphNode, CrankDigraphNode>                        //

  guint i;

  // Initializing
  dist        = g_hash_table_new_full (g_direct_hash,
                                       g_direct_equal,
                                       NULL,
                                       crank_advgraph_free_float);
  visited     = g_hash_table_new (g_direct_hash, g_direct_equal);
  visiting    = g_hash_table_new (g_direct_hash, g_direct_equal);
  prev        = g_hash_table_new (g_direct_hash, g_direct_equal);

  g_hash_table_add (visiting, from);
  crank_advgraph_set_float (dist, from, 0.0f);

  // Looping.
  while (g_hash_table_size (visiting) != 0)
    {
      CrankDigraphNode *node;
      gfloat cost;
      GPtrArray* out_edges;

      // Pick one of node.
      node = (CrankDigraphNode*) crank_advgraph_table_min (visiting, dist, &cost);
      g_hash_table_remove (visiting, node);
      g_hash_table_add (visited, node);

      // Process picked node
      out_edges = crank_digraph_node_get_out_edges (node);
      for (i = 0; i < out_edges->len; i++)
        {
          CrankDigraphEdge *edge = (CrankDigraphEdge*) out_edges->pdata[i];
          CrankDigraphNode *next_node = crank_digraph_edge_get_head (edge);

          gfloat edge_cost = edge_func (edge, userdata);
          gfloat next_cost = crank_advgraph_get_float (dist,
                                                       next_node,
                                                       INFINITY);
          gfloat next_cost_new = cost + edge_cost;

          if (next_cost_new < next_cost)
            {
              g_hash_table_insert (prev, next_node, node);
              crank_advgraph_set_float (dist, next_node, next_cost_new);

              if (!g_hash_table_contains (visited, next_node))
                g_hash_table_add (visiting, next_node);
            }
        }

      // If we found the way to @to, then stop loop.
      if (node == to)
        break;
    }

  // Build up path.
  result_node = to;
  while (result_node != NULL)
    {
      result = g_list_prepend (result, result_node);
      result_node = g_hash_table_lookup (prev, result_node);
    }

  if (result->data != from)
    {
      g_list_free (result);
      result = NULL;
    }

  g_hash_table_unref (dist);
  g_hash_table_unref (visited);
  g_hash_table_unref (visiting);
  g_hash_table_unref (prev);

  return result;
}

/**
 * crank_astar_digraph:
 * @from: starting node
 * @to: destination node
 * @edge_func: (scope call) (closure edge_userdata):
 *     cost function for each edge.
 * @edge_userdata: userdata for @edge_func.
 * @heuristic_func: (scope call) (closure heuristic_userdata):
 *     estimated cost function for each node to destination
 * @heuristic_userdata: userdata for @heuristic_func
 *
 * Gets reasonably short path for a graph. (Not always returns shortest path,
 * but generally short paths.)
 *
 * If @edge_func returns negative value, this will behave incorrectly.
 * If @edge_func returns 0 or positive constant value, this will behave like dijkstra.
 *
 * Returns: (nullable) (transfer container) (element-type CrankDigraphNode):
 *    Path as list of Nodes.
 */
GList*
crank_astar_digraph (CrankDigraphNode         *from,
                     CrankDigraphNode         *to,
                     CrankDigraphEdgeFloatFunc edge_func,
                     gpointer                  edge_userdata,
                     CrankDigraphHeuristicFunc heuristic_func,
                     gpointer                  heuristic_userdata)
{
  GList *result = NULL;
  CrankDigraphNode *result_node;

  GHashTable *dist_from; // HashTable <CrankDigraphNode,gfloat>
  GHashTable *dist_to;   // HashTable <CrankDigraphNode,gfloat>
  GHashTable *visited;   // Set <CrankDigarphNode>
  GHashTable *visiting;  // Set <CrankDigraphNode>
  GHashTable *prev;      // HashTable <CrankDigraphNode,CrankDigraphNode>

  // Initializing
  dist_from   = g_hash_table_new_full (g_direct_hash,
                                       g_direct_equal,
                                       NULL,
                                       crank_advgraph_free_float);
  dist_to     = g_hash_table_new_full (g_direct_hash,
                                       g_direct_equal,
                                       NULL,
                                       crank_advgraph_free_float);
  visited     = g_hash_table_new (g_direct_hash, g_direct_equal);
  visiting    = g_hash_table_new (g_direct_hash, g_direct_equal);
  prev        = g_hash_table_new (g_direct_hash, g_direct_equal);

  g_hash_table_add (visiting, from);
  crank_advgraph_set_float (dist_from, from, 0.0f);
  crank_advgraph_set_float (dist_to, from,
                            heuristic_func (from, to, heuristic_userdata));

  // Looping.
  while (g_hash_table_size (visiting) != 0)
    {
      gfloat cost;
      CrankDigraphNode *node = NULL;

      GPtrArray *out_edges;
      guint i;


      // Pick next node to check.
      node = (CrankDigraphNode*) crank_advgraph_table_min (visiting, dist_to, &cost);
      g_hash_table_remove (visiting, node);
      g_hash_table_add (visited, node);

      // Process node

      out_edges = crank_digraph_node_get_out_edges (node);
      for (i = 0; i < out_edges->len; i++)
        {
          CrankDigraphEdge *edge = (CrankDigraphEdge*) out_edges->pdata[i];
          CrankDigraphNode *next_node = crank_digraph_edge_get_head (edge);
          gfloat edge_cost = edge_func (edge, edge_userdata);
          gfloat next_cost = crank_advgraph_get_float (dist_from,
                                                       next_node,
                                                       INFINITY);
          gfloat next_cost_new = cost + edge_cost;

          if (next_cost_new < next_cost)
            {
              g_hash_table_insert (prev, next_node, node);
              crank_advgraph_set_float (dist_from, next_node, next_cost_new);
              crank_advgraph_set_float (dist_to, next_node,
                                        next_cost_new +
                                        heuristic_func (next_node, to,
                                                        heuristic_userdata) );

              if (!g_hash_table_contains (visited, next_node))
                g_hash_table_add (visiting, next_node);
            }
        }

      // If we found the way to @to, then stop loop.
      if (node == to)
        break;
    }

  // Build up path.
  result_node = to;
  while (result_node != NULL)
    {
      result = g_list_prepend (result, result_node);
      result_node = g_hash_table_lookup (prev, result_node);
    }

  if (result->data != from)
    {
      g_list_free (result);
      result = NULL;
    }

  g_hash_table_unref (dist_from);
  g_hash_table_unref (dist_to);
  g_hash_table_unref (visited);
  g_hash_table_unref (visiting);
  g_hash_table_unref (prev);

  return result;
}



/**
 * crank_dijkstra_full_digraph: (skip)
 * @from: starting node
 * @edge_func: (scope call): cost function for each edge.
 * @userdata: (closure): user data
 *
 * Gets minimum path tree from @from node.
 *
 * The resulting tree will contains only connected nodes from @from.
 *
 * If @from is sole disconnected node, then the tree contains only @from
 *
 * Returns: The tree of #CrankDigraphNode
 */
GNode*
crank_dijkstra_full_digraph (CrankDigraphNode         *from,
                             CrankDigraphEdgeFloatFunc edge_func,
                             gpointer                  userdata)
{
  GNode *result = NULL;

  GHashTable *dist;     // HashTable <CrankDigraphNode,gfloat>
  GHashTable *visited;  // Set <CrankDigraphNode>
  GHashTable *visiting; // Set <CrankDigraphNode>
  GHashTable *treenode; // HashTable <CrankDigraphNode,GNode<CrankDigraphNode>>

  // Initializing
  dist        = g_hash_table_new_full (g_direct_hash,
                                       g_direct_equal,
                                       NULL,
                                       crank_advgraph_free_float);
  visited     = g_hash_table_new (g_direct_hash, g_direct_equal);
  visiting    = g_hash_table_new (g_direct_hash, g_direct_equal);
  treenode    = g_hash_table_new (g_direct_hash, g_direct_equal);

  g_hash_table_add (visiting, from);
  g_hash_table_insert (visiting, from, g_node_new (from));
  crank_advgraph_set_float (dist, from, 0.0f);

  // Looping.
  while (g_hash_table_size (visiting) != 0)
    {
      GHashTableIter visiting_iter;

      gfloat cost = INFINITY;
      CrankDigraphNode *node;

      GPtrArray *out_edges;
      guint i;


      // Pick next node to check.
      node = (CrankDigraphNode*) crank_advgraph_table_min (visiting, dist, &cost);
      g_hash_table_remove (visiting, node);
      g_hash_table_add (visited, node);

      // Process node
      out_edges = crank_digraph_node_get_out_edges (node);

      for (i = 0; i < out_edges->len; i++)
        {
          CrankDigraphEdge *edge = out_edges->pdata[i];
          CrankDigraphNode *next_node = crank_digraph_edge_get_head (edge);
          gfloat edge_cost = edge_func (edge, userdata);
          gfloat next_cost = crank_advgraph_get_float (dist, next_node, INFINITY);
          gfloat next_cost_new = cost + edge_cost;

          if (next_cost_new < next_cost)
            {
              GNode *gnode = g_hash_table_lookup (treenode, node);
              GNode *next_gnode = g_hash_table_lookup (treenode, next_node);

              g_node_unlink (next_gnode);
              g_node_append (gnode, next_gnode);

              g_hash_table_insert (treenode, next_node, next_gnode);
              crank_advgraph_set_float (dist, next_node, next_cost_new);

              if (!g_hash_table_contains (visited, next_node))
                g_hash_table_add (visiting, next_node);
            }
        }
    }

  g_hash_table_unref (dist);
  g_hash_table_unref (visited);
  g_hash_table_unref (visiting);
  g_hash_table_unref (treenode);

  return result;
}
