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
 * * Topology sorting
 * * Minimum distance path
 *   * Dijkstra
 *   * A*
 * # Operations result in tree of Nodes
 * * Spanning Tree
 *   * Dijkstra full
 *   * Minimum Spanning Tree algorithms.
 *
 * TODO:
 *    add tsort (topology sort)
 *    add A*
 *
 * TODO-future:
 *    add tsort on MatBoolN
 *    add dijkstra on MatFloatN
 *    add A* on MatFloatN
 */
 
static void
crank_advgraph_free_float (gpointer	f)
{
	g_slice_free (gfloat, f);
}

static void
crank_advgraph_set_float (GHashTable* table, gpointer key, gfloat value)
{
	gfloat*	ptr = g_slice_new (gfloat);
	
	*ptr = value;
	
	g_hash_table_insert (table, key, ptr);
}

static gfloat
crank_advgraph_get_float (GHashTable* table, gpointer key, const gfloat def)
{
	gfloat*	ptr = (gfloat*) g_hash_table_lookup (table, key);
	return (ptr == NULL) ? def : *ptr;
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
crank_dijkstra_digraph (	CrankDigraphNode*			from,
							CrankDigraphNode*			to,
							CrankDigraphEdgeFloatFunc	edge_func,
							gpointer					userdata	)
{
	GList*				result = NULL;
	CrankDigraphNode*	result_node;
	
	GHashTable*	dist;
	GHashTable*	visited;
	GHashTable*	visiting;
	GHashTable*	prev;
	
	// Initializing
	dist 		= g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, crank_advgraph_free_float);
	visited		= g_hash_table_new (g_direct_hash, g_direct_equal);
	visiting	= g_hash_table_new (g_direct_hash, g_direct_equal);
	prev 		= g_hash_table_new (g_direct_hash, g_direct_equal);
	
	g_hash_table_add (visiting, from);
	crank_advgraph_set_float (dist, from, 0.0f);
	
	// Looping.
	while (g_hash_table_size (visiting) != 0) {
		GHashTableIter		visiting_iter;
		
		// TODO: Pick more better name
		gfloat				cost = INFINITY;
		CrankDigraphNode*	node;
		gfloat				cost_candidate;
		CrankDigraphNode* 	node_candidate;
	
	
		// Pick next node to check.
		g_hash_table_iter_init (&visiting_iter, visiting);
		while (	g_hash_table_iter_next (
				&visiting_iter,
				(gpointer*)&node_candidate,
				NULL) )
		{
			cost_candidate = crank_advgraph_get_float (dist, node_candidate, INFINITY);
			if (cost_candidate < cost) {
				node = node_candidate;
				cost = cost_candidate;
			}
		}
		g_hash_table_remove (visiting, node);
		
		// Process node
		g_hash_table_add (visited, node);
		
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (
				crank_digraph_node_get_out_edges (node),
				CrankDigraphEdge*, edge
		)
			CrankDigraphNode*	next_node = crank_digraph_edge_get_head (edge);
			gfloat				edge_cost = edge_func (edge, userdata);
			gfloat				next_cost = crank_advgraph_get_float (dist, next_node, INFINITY);
			gfloat				next_cost_new = cost + edge_cost;
			
			if (next_cost_new < next_cost) {
				g_hash_table_insert (prev, next_node, node);
				crank_advgraph_set_float (dist, next_node, next_cost_new);
			
				if (! g_hash_table_contains (visited, next_node))
					g_hash_table_add (visiting, next_node);
			}
		CRANK_FOREACH_G_PTR_ARRAY_END
		
		// If we found the way to @to, then stop loop.
		if (node == to) break;
	}
	
	// Build up path.
	result_node = to;
	while (result_node != NULL) {
		 result = g_list_prepend (result, result_node);
		 result_node = g_hash_table_lookup (prev, result_node);
	}
	
	if (result->data != from) {
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
 * @edge_func: (scope call): cost function for each edge.
 * @edge_userdata: (closure edge_func): userdata for @edge_func.
 * @heuristic_func: (scope call): estimated cost function for each node to destination
 * @heuristic_userdata: (closure heuristic_userdata): userdata for @heuristic_func
 *
 * Gets reasonably short path for a graph. (Not always returns shortest path,
 * but generally short paths. _
 *
 * If edge_func returns negative value, this will behave incorrectly.
 *
 * Returns: (nullable) (transfer container) (element-type CrankDigraphNode)
 *    Path as list of Nodes.
 */
GList*
crank_astar_digraph (	CrankDigraphNode*			from,
						CrankDigraphNode*			to,
						CrankDigraphEdgeFloatFunc	edge_func,
						gpointer					edge_userdata,
						CrankDigraphHeuristicFunc	heuristic_func,
						gpointer					heuristic_userdata	)
{
	GList*				result = NULL;
	CrankDigraphNode*	result_node;
	
	GHashTable*	dist_from;
	GHashTable*	dist_to;
	GHashTable*	visited;
	GHashTable*	visiting;
	GHashTable*	prev;
	
	// Initializing
	dist_from	= g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, crank_advgraph_free_float);
	dist_to		= g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, crank_advgraph_free_float);
	visited		= g_hash_table_new (g_direct_hash, g_direct_equal);
	visiting	= g_hash_table_new (g_direct_hash, g_direct_equal);
	prev 		= g_hash_table_new (g_direct_hash, g_direct_equal);
	
	g_hash_table_add (visiting, from);
	crank_advgraph_set_float (dist_from, from, 0.0f);
	crank_advgraph_set_float (dist_to, from, heuristic_func (from, to, heuristic_userdata));
	
	g_message ("From: %p [%f]", from, heuristic_func (from, to, heuristic_userdata));
	
	// Looping.
	while (g_hash_table_size (visiting) != 0) {
		GHashTableIter		visiting_iter;
		
		// TODO: Pick more better name
		gfloat				cost = INFINITY;
		CrankDigraphNode*	node = NULL;
		gfloat				cost_candidate;
		CrankDigraphNode* 	node_candidate;
	
	
		// Pick next node to check.
		g_hash_table_iter_init (&visiting_iter, visiting);
		while (	g_hash_table_iter_next (
				&visiting_iter,
				(gpointer*)&node_candidate,
				NULL) )
		{
			cost_candidate = crank_advgraph_get_float (dist_to, node_candidate, INFINITY);
			if (cost_candidate < cost) {
				node = node_candidate;
				cost = cost_candidate;
			}
		}
		g_hash_table_remove (visiting, node);
		
		// Process node
		g_hash_table_add (visited, node);
		
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (
				crank_digraph_node_get_out_edges (node),
				CrankDigraphEdge*, edge
		)
			CrankDigraphNode*	next_node = crank_digraph_edge_get_head (edge);
			gfloat				edge_cost = edge_func (edge, edge_userdata);
			gfloat				next_cost = crank_advgraph_get_float (dist_from, next_node, INFINITY);
			gfloat				next_cost_new = cost + edge_cost;
			
			if (next_cost_new < next_cost) {
				g_hash_table_insert (prev, next_node, node);
				crank_advgraph_set_float (dist_from, next_node, next_cost_new);
				crank_advgraph_set_float (dist_to, next_node,
						next_cost_new +
						heuristic_func (next_node, to, heuristic_userdata) );
						
				if (! g_hash_table_contains (visited, next_node))
					g_hash_table_add (visiting, next_node);
			}
			
		CRANK_FOREACH_G_PTR_ARRAY_END
		
		// If we found the way to @to, then stop loop.
		if (node == to) break;
	}
	
	// Build up path.
	result_node = to;
	while (result_node != NULL) {
		 result = g_list_prepend (result, result_node);
		 result_node = g_hash_table_lookup (prev, result_node);
	}
	
	if (result->data != from) {
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
 * crank_dijkstra_full_digraph:
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
 * Returns: (transfer container) (element-type CrankDigraphNode*):
 *    The tree of #CrankDigraphNode
 */
GNode*
crank_dijkstra_full_digraph (	CrankDigraphNode*			from,
								CrankDigraphEdgeFloatFunc	edge_func,
								gpointer					userdata	)
{
	GNode*				result = NULL;
	
	GHashTable*	dist;
	GHashTable*	visited;
	GHashTable*	visiting;
	GHashTable*	treenode;
	
	// Initializing
	dist 		= g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, crank_advgraph_free_float);
	visited		= g_hash_table_new (g_direct_hash, g_direct_equal);
	visiting	= g_hash_table_new (g_direct_hash, g_direct_equal);
	treenode 	= g_hash_table_new (g_direct_hash, g_direct_equal);
	
	g_hash_table_add (visiting, from);
	g_hash_table_insert (visiting, from, g_node_new (from));
	crank_advgraph_set_float (dist, from, 0.0f);
	
	// Looping.
	while (g_hash_table_size (visiting) != 0) {
		GHashTableIter		visiting_iter;
		
		gfloat				cost = INFINITY;
		CrankDigraphNode*	node;
		gfloat				cost_candidate;
		CrankDigraphNode* 	node_candidate;
	
	
		// Pick next node to check.
		g_hash_table_iter_init (&visiting_iter, visiting);
		while (	g_hash_table_iter_next (
				&visiting_iter,
				(gpointer*)&node_candidate,
				NULL) )
		{
			cost_candidate = crank_advgraph_get_float (dist, node_candidate, INFINITY);
			if (cost_candidate < cost) {
				node = node_candidate;
				cost = cost_candidate;
			}
		}
		g_hash_table_remove (visiting, node);
		
		
		// Process node
		g_hash_table_add (visited, node);
		
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (
				crank_digraph_node_get_out_edges (node),
				CrankDigraphEdge*, edge
		)
			CrankDigraphNode*	next_node = crank_digraph_edge_get_head (edge);
			gfloat				edge_cost = edge_func (edge, userdata);
			gfloat				next_cost = crank_advgraph_get_float (dist, next_node, INFINITY);
			gfloat				next_cost_new = cost + edge_cost;
			
			if (next_cost_new < next_cost) {
				GNode*	gnode = g_hash_table_lookup (treenode, node);
				GNode*	next_gnode = g_hash_table_lookup (treenode, next_node);
				
				g_node_unlink (next_gnode);
				g_node_append (gnode, next_gnode);
				
				g_hash_table_insert (treenode, next_node, next_gnode);
				crank_advgraph_set_float (dist, next_node, next_cost_new);
			
				if (! g_hash_table_contains (visited, next_node))
					g_hash_table_add (visiting, next_node);
			}
		CRANK_FOREACH_G_PTR_ARRAY_END
	}
	
	g_hash_table_unref (dist);
	g_hash_table_unref (visited);
	g_hash_table_unref (visiting);
	g_hash_table_unref (treenode);
	
	return result;
}
