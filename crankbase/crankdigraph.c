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
#define _CRANKBASE_INSIDE

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankvalue.h"
#include "crankdigraph.h"

/**
 * SECTION: crankdigraph
 * @title:  CrankDigraph
 * @short_description: A data structure for digraph.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * This structure represents a digraph.
 *
 * # Implementation of digraph.
 *
 * A graph has it's nodes and edges that connects them. Unlike other type of
 * data structure, Connections itself may have their own values.
 *
 * To incorporate to cases that edges has value, structure has been defined for 
 * edges too.
 * 
 * In this implementation, each node has edge list, rather than adjacent list.
 *
 * REF: #CrankDigraphNode, #CrankDigraphEdge
 *
 * # Life cycle of CrankDigraphNode and CrankDigraphEdge
 *
 * As nodes and edges are part of graph, memory management is done at graph
 * level. because of that, they don't have GType.
 */

G_DEFINE_BOXED_TYPE (CrankDigraph, crank_digraph, crank_digraph_ref, crank_digraph_unref);

/**
 * CrankDigraph:
 *
 * A structure for digraph.
 */
struct _CrankDigraph {
	GPtrArray*	nodes;
	GPtrArray*	edges;

  	guint	_refc;
};

/**
 * CrankDigraphNode:
 *
 * A structure for node.
 */
struct _CrankDigraphNode {
	GValue		data;

	GPtrArray*	in_edges;
	GPtrArray*	out_edges;
};

/**
 * CrankDigraphEdge:
 *
 * A structure for edge.
 */
struct _CrankDigraphEdge {
	GValue		data;

	CrankDigraphNode*	tail;
	CrankDigraphNode*	head;
};


//////// Internal Declaration //////////////////////////////////////////////////

CrankDigraphNode*	crank_digraph_node_new (			const GValue*	data	);

void				crank_digraph_node_free (			CrankDigraphNode*	node	);

CrankDigraphEdge*	crank_digraph_edge_new (			const GValue*	data,
														CrankDigraphNode*	tail,
														CrankDigraphNode*	head		);

void				crank_digraph_edge_free (			CrankDigraphEdge*	edge	);

//////// Definition ////////////////////////////////////////////////////////////

/**
 * crank_digraph_new:
 *
 * Constructs an empty digraph.
 *
 * Returns: (transfer full): Newly created digraph.
 */
CrankDigraph*
crank_digraph_new (void)
{
	CrankDigraph*	graph = g_new (CrankDigraph, 1);

  	graph->nodes = g_ptr_array_new_with_free_func ((GDestroyNotify)crank_digraph_node_free);
  	graph->edges = g_ptr_array_new_with_free_func ((GDestroyNotify)crank_digraph_edge_free);

  	graph->_refc = 1;

 	return graph;
}

/**
 * crank_digraph_new_with_nodes:
 * @nnodes: Count of nodes.
 * @values: (array length=nnodes): Values of nodes.
 *
 * Constructs a digraph with given values. The values are used for nodes.
 *
 * Returns: (transfer full): Newly created digraph.
 */
CrankDigraph*
crank_digraph_new_with_nodes (	const guint		nnodes,
								const GValue*	values	)
{
	CrankDigraph*	graph = crank_digraph_new ();
	guint			i;
	
	for (i = 0; i < nnodes; i ++)	crank_digraph_add (graph, values + i);
	
	return graph;
}

/**
 * crank_digraph_new_full:
 * @nnodes: Count of nodes.
 * @values: (array length=nnodes): Values of nodes.
 * @nedges: Count of edges.
 * @edges: (array length=nedges): Values of edges.
 *
 * Constructs a digraph with given values. As nodes are unavailable on
 * construction, nodes are pointed by index.
 *
 * Returns: (transfer full): Newly created digraph
 */
CrankDigraph*
crank_digraph_new_full (	const guint		nnodes,
							const GValue*	values,
							const guint		nedges,
							const CrankDigraphEdgeIndex*	edges	)
{
	CrankDigraph*	graph = crank_digraph_new_with_nodes (nnodes, values);
	guint			i;
	
	for (i = 0; i < nedges; i++) {
		CrankDigraphNode*	tail;
		CrankDigraphNode*	head;
		
		tail = (CrankDigraphNode*) g_ptr_array_index (graph->nodes, edges[i].tail);
		head = (CrankDigraphNode*) g_ptr_array_index (graph->nodes, edges[i].head);
		
		crank_digraph_connect (graph, tail, head, & edges[i].data);
	}

 	return graph;
}


/**
 * crank_digraph_ref:
 * @graph: A digraph.
 *
 * Increase reference count by 1.
 *
 * Returns: (transfer full): A digraph with increased reference count.
 */
CrankDigraph*
crank_digraph_ref (	CrankDigraph*		graph	)
{
	g_atomic_int_inc (& (graph->_refc));
	return graph;
}

/**
 * crank_digraph_unref:
 * @graph: (transfer full): A digraph.
 *
 * Decreases reference count by 1. If reference count reaches 0, then digraph
 * is freed.
 */
void
crank_digraph_unref (	CrankDigraph*		graph	)
{
	if (g_atomic_int_dec_and_test (& graph->_refc)) {
		g_ptr_array_free (graph->nodes, TRUE);
		g_ptr_array_free (graph->edges, TRUE);
		g_free (graph);
	}
}


/**
 * crank_digraph_get_nodes:
 * @graph: A digraph.
 *
 * Gets the nodes of graph.
 *
 * Returns: (transfer none) (element-type CrankDigraphNode): Nodes of graph.
 */
GPtrArray*
crank_digraph_get_nodes (	CrankDigraph*	graph	)
{
	return graph->nodes;
}

/**
 * crank_digraph_get_edges:
 * @graph: A digraph.
 *
 * Gets the edges of graph.
 *
 * Returns: (transfer none) (element-type CrankDigraphEdge): Edges of graph.
 */
GPtrArray*
crank_digraph_get_edges (	CrankDigraph*	graph	)
{
	return graph->edges;
}

/**
 * crank_digraph_index_of_node:
 * @graph: A digraph.
 * @node: A node.
 *
 * Gets index of node in graph. The index can be used with adjacency matrices.
 *
 * Note:
 * The index can be changed as graph changes.
 * 
 * Returns: Index of node in graph. If node is not in graph, -1 is returned.
 */
gint
crank_digraph_index_of_node (	CrankDigraph*		graph,
								CrankDigraphNode*	node	)
{
	gint i;
	
	for (i = 0; i < graph->nodes->len; i++)
		if (node == graph->nodes->pdata[i]) return i;
	
	return -1;
}

/**
 * crank_digraph_index_of_edge:
 * @graph: A digraph.
 * @edge: An edge.
 *
 * Gets index of edge in graph.
 *
 * Note:
 * The index can be changed as graph changes.
 *
 * Returns: Index of edge in graph. If edge is not in graph, -1 is returned.
 */
gint
crank_digraph_index_of_edge (	CrankDigraph*		graph,
								CrankDigraphEdge*	edge	)
{
	gint i;
	
	for (i = 0; i < graph->edges->len; i++)
		if (edge == graph->edges->pdata[i]) return i;
	
	return -1;
}

/**
 * crank_digraph_nth_node:
 * @graph: A digraph.
 * @index: Index of node.
 *
 * Gets a node at index.
 *
 * Note:
 * The index can be changed as graph changes.
 * 
 * Returns: (transfer none) (nullable): The node at the index or %NULL if index
 *        is out of bound.
 */
CrankDigraphNode*
crank_digraph_nth_node (	CrankDigraph*	graph,
							guint			index	)
{
	if (index < graph->nodes->len)
		return (CrankDigraphNode*) g_ptr_array_index (graph->nodes, index);
	else return NULL;
}

/**
 * crank_digraph_nth_edge:
 * @graph: A digraph.
 * @index: Index of edge..
 *
 * Gets a edge at index.
 *
 * Note:
 * The index can be changed as graph changes.
 * 
 * Returns: (transfer none) (nullable): The edge at the index or %NULL if index
 *        is out of bound.
 */
CrankDigraphEdge*
crank_digraph_nth_edge (	CrankDigraph*	graph,
							guint			index	)
{
	if (index < graph->edges->len)
		return (CrankDigraphEdge*) g_ptr_array_index (graph->edges, index);
	else return NULL;
}

/**
 * crank_digraph_add:
 * @graph: A digraph.
 * @value: Value for new node.
 *
 * Creates a node with given value.
 *
 * Returns: (transfer none): Newly created and added node.
 */
CrankDigraphNode*
crank_digraph_add (	CrankDigraph*		graph,
					const GValue*	value	)
{
	CrankDigraphNode* node = crank_digraph_node_new (value);
	
	g_ptr_array_add (graph->nodes, node);
	
	return node;
}

/**
 * crank_digraph_remove:
 * @graph: A digraph.
 * @node: A node to remove.
 *
 * Removes a node from graph. All connected edges to the nodes are removed also.
 */
void
crank_digraph_remove (	CrankDigraph*		graph,
						CrankDigraphNode*	node	)
{
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (node->in_edges, CrankDigraphEdge*, e)
	
		g_ptr_array_remove_fast (e->tail->out_edges, e);
		g_ptr_array_remove_fast (graph->edges, e);
		
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (node->out_edges, CrankDigraphEdge*, e)
	
		g_ptr_array_remove_fast (e->head->in_edges, e);
		g_ptr_array_remove_fast (graph->edges, e);
		
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	g_ptr_array_remove_fast (graph->nodes, node);
}

/**
 * crank_digraph_connect:
 * @graph: A digraph.
 * @tail: Tail node of edge.
 * @head: Head node of edge..
 * @edge_value: (nullable): Value for new edge.
 *
 * Creates an edge connects @from and @to. @edge_value may be %NULL if
 * value of edge is not matter of use case.
 *
 * Returns: (transfer none) (nullable):
 *        Newly created edge that connects two nodes. If there is already a edge
 *        that connects, no edge is created and returns %NULL.
 */
CrankDigraphEdge*
crank_digraph_connect (	CrankDigraph*		graph,
						CrankDigraphNode*	tail,
						CrankDigraphNode*	head,
						const GValue*		edge_value	)
{
	CrankDigraphEdge*		edge;
	
	if (crank_digraph_node_is_adjacent_to (tail, head)) {
		g_warning ("Trying to connect already connected nodes.");
		return NULL;
	}
	
	edge = crank_digraph_edge_new (edge_value, tail, head);
	g_ptr_array_add (tail->out_edges, edge);
	g_ptr_array_add (head->in_edges, edge);
	g_ptr_array_add (graph->edges, edge);
	
	return edge;
}

/**
 * crank_digraph_disconnect:
 * @graph: A digraph.
 * @tail: Tail node to disconnect.
 * @head: Head node to disconnect.
 *
 * Removes the edge that connects two nodes. If there is no edge, it returns
 * %FALSE
 *
 * Returns: %TRUE, if a edge connects @from and @to, is removed.
 */
gboolean
crank_digraph_disconnect (	CrankDigraph*		graph,
							CrankDigraphNode*	tail,
							CrankDigraphNode*	head	)
{
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (tail->out_edges, CrankDigraphEdge*, e)
		if (e->head == head) {
			crank_digraph_disconnect_edge (graph, e);
			return TRUE;
		}
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	return FALSE;
}

/**
 * crank_digraph_disconnect_edge:
 * @graph: A digraph.
 * @e: A edge to remove.
 *
 * Removes a edge from digraph.
 */
void
crank_digraph_disconnect_edge (	CrankDigraph*		graph,
								CrankDigraphEdge*	e		)
{
	g_ptr_array_remove_fast (e->tail->out_edges, e);
	g_ptr_array_remove_fast (e->head->in_edges, e);
	g_ptr_array_remove_fast (graph->edges, e);
}

/**
 * crank_digraph_reverse:
 * @graph: A digraph.
 *
 * Reverses a graph.
 */
void
crank_digraph_reverse (	CrankDigraph*	graph	)
{
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (graph->nodes, CrankDigraphNode*, node)
	
		GPtrArray*	temp = node->in_edges;
		node->in_edges = node->out_edges;
		node->out_edges = temp;
	
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (graph->edges, CrankDigraphEdge*, edge)
		
		CrankDigraphNode*	temp = edge->head;
		edge->head = edge->tail;
		edge->tail = temp;
		
	CRANK_FOREACH_G_PTR_ARRAY_END
}

/**
 * crank_digraph_copy:
 * @graph: A digraph to copy.
 *
 * Copies a digraph.
 *
 * Returns: (transfer full): A copied digraph.
 */
CrankDigraph*
crank_digraph_copy (	CrankDigraph*	graph	)
{
	// Hash table은 노드-인덱스를 보관하기 위해 사용합니다.
	CrankDigraph*	clone;
	GHashTable*		table;

	clone = crank_digraph_new ();
	table = g_hash_table_new (g_direct_hash, g_direct_equal);

	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (graph->nodes, CrankDigraphNode*, node)

		g_hash_table_insert (table,
				node,
				crank_digraph_add (clone, & node->data)	);

	CRANK_FOREACH_G_PTR_ARRAY_END

	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (graph->edges, CrankDigraphEdge*, edge)

		CrankDigraphNode*	tail;
		CrankDigraphNode*	head;

		tail = g_hash_table_lookup (table, edge->tail);
		head = g_hash_table_lookup (table, edge->head);

		crank_digraph_connect (graph, tail, head, & edge->data);

	CRANK_FOREACH_G_PTR_ARRAY_END

	g_hash_table_unref (table);

	return clone;
}






/**
 * crank_digraph_node_get_data:
 * @node: A node to get data.
 * @value: #GValue to store value of node.
 *
 * Gets value of node.
 */
void
crank_digraph_node_get_data (	CrankDigraphNode*	node,
								GValue*			value	)
{
	g_value_copy (& node->data, value);
}
														
/**
 * crank_digraph_node_set_data:
 * @node: A node to set data.
 * @value: #GValue to set value of node.
 *
 * Sets value of node.
 */
void
crank_digraph_node_set_data (	CrankDigraphNode*	node,
								const GValue*		value	)
{
	crank_value_overwrite (& node->data, value);
}
													
/**
 * crank_digraph_node_type_of:
 * @node: A node.
 *
 * Gets #GType of #GValue.
 *
 * Returns: GType of GValue.
 */
GType
crank_digraph_type_of (	CrankDigraphNode*	node	)
{
	return G_VALUE_TYPE (& node->data );
}

/**
 * crank_digraph_node_get_in_nodes:
 * @node: A node.
 *
 * Gets nodes that have incomming edges to this node.
 *
 * Returns: (transfer container) (element-type CrankDigraphNode):
 *        Nodes that have incomming edges to this node.
 */
GList*
crank_digraph_node_get_in_nodes (	CrankDigraphNode*	node	)
{
	GList*	result = NULL;
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (node->in_edges, CrankDigraphEdge*, edge)
	
		result = g_list_prepend (result, edge->tail);
	
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	result = g_list_reverse (result);
	
	return result;
}

/**
 * crank_digraph_node_get_out_nodes:
 * @node: A node.
 *
 * Gets nodes that have outgoing edges from this node.
 *
 * Returns: (transfer container) (element-type CrankDigraphNode):
 *        Nodes that have outgoing edges from this node.
 */
GList*
crank_digraph_node_get_out_nodes (	CrankDigraphNode*	node	)
{
	GList*	result = NULL;
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (node->out_edges, CrankDigraphEdge*, edge)
	
		result = g_list_prepend (result, edge->head);
	
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	result = g_list_reverse (result);
	
	return result;
}

/**
 * crank_digraph_node_get_in_edges:
 * @node: A node.
 *
 * Gets incomming edges to this node.
 *
 * Returns: (transfer none) (element-type CrankDigraphEdge):
 *        Incomming edges to this node.
 */
GPtrArray*
crank_digraph_node_get_in_edges (	CrankDigraphNode*	node	)
{
	return node->in_edges;
}

/**
 * crank_digraph_node_get_out_edges:
 * @node: A node.
 *
 * Gets outgoing edges from this node.
 *
 * Returns: (transfer none) (element-type CrankDigraphEdge):
 *        Outgoing edges to this node.
 */
GPtrArray*
crank_digraph_node_get_out_edges (	CrankDigraphNode*	node	)
{
	return node->out_edges;
}

/**
 * crank_digraph_node_get_indegree:
 * @node: A node.
 *
 * Gets indegree (number of incomming nodes) of this node.
 *
 * Returns: Indegree of this node.
 */
guint
crank_digraph_node_get_indegree (	CrankDigraphNode*	node	)
{
	return node->in_edges->len;
}

/**
 * crank_digraph_node_get_outdegree:
 * @node: A node.
 *
 * Gets outdegree (number of outgoing nodes) of this node.
 *
 * Returns: Outgoing of this node.
 */
guint
crank_digraph_node_get_outdegree (	CrankDigraphNode*	node	)
{
	return node->out_edges->len;
}

/**
 * crank_digraph_node_is_adjacent:
 * @node: A node.
 * @other: Other node.
 *
 * Check there is an edge between @node and @other.
 *
 * Returns: Whether there is an edge bewteen @node and @other.
 */
gboolean
crank_digraph_node_is_adjacent (	CrankDigraphNode* node,
									CrankDigraphNode* other	)
{
	return	crank_digraph_node_is_adjacent_to (node, other) ||
			crank_digraph_node_is_adjacent_to (other, node);
}

/**
 * crank_digraph_node_is_adjacent_from:
 * @node: A node.
 * @other: Other node.
 *
 * Check @node has incomming edge from @other.
 *
 * Returns: Whether @node has incomming edge to @other.
 */
gboolean
crank_digraph_node_is_adjacent_from (	CrankDigraphNode*	node,
										CrankDigraphNode*	other	)
{
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN(node->in_edges, CrankDigraphEdge*, e)
		if (e->tail == other) return TRUE;
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	return FALSE;
}

/**
 * crank_digraph_node_is_adjacent_to:
 * @node: A node.
 * @other: Other node.
 *
 * Check @node has outgoing edge to @other.
 *
 * Returns: Whether @node has outgoing edge from @other
 */
gboolean
crank_digraph_node_is_adjacent_to (	CrankDigraphNode*	node,
									CrankDigraphNode*	other	)
{
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN(node->out_edges, CrankDigraphEdge*, e)
		if (e->head == other) return TRUE;
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	return FALSE;
}


/**
 * crank_digraph_node_foreach_depth:
 * @node: A node.
 * @func: (scope call): A function to iterate over.
 * @userdata: (closure): userdata for @func.
 *
 * Performs depth-first iteration.
 *
 * Iteration can be stopped by returning %FALSE from @func.
 *
 * Returns: %FALSE, if @func returns %FALSE.
 */
gboolean
crank_digraph_node_foreach_depth (	CrankDigraphNode*		node,
									CrankDigraphNodeFunc	func,
									gpointer				userdata	)
{
	GHashTable*			visited_set;
	GQueue*				visiting_queue;
	
	CrankDigraphNode*	subnode;
	gboolean			result;
	
	visited_set = g_hash_table_new (g_direct_hash, g_direct_equal);
	visiting_queue = g_queue_new ();
	
	g_queue_push_tail (visiting_queue, node);
	result = TRUE;
	
	while (! g_queue_is_empty (visiting_queue)) {
		subnode = (CrankDigraphNode*) g_queue_pop_tail (visiting_queue);
		
		if (! g_hash_table_contains (visited_set, subnode)) {
			g_hash_table_add (visited_set, subnode);
			result = func (subnode, userdata);
			
			if (! result) break;
			
			// Adds each sub item on queue/stack.
			CRANK_FOREACH_G_PTR_ARRAY_BEGIN (
					crank_digraph_node_get_out_edges (subnode),
					CrankDigraphEdge*, edge	)
					
				g_queue_push_tail (visiting_queue, crank_digraph_edge_get_head (edge));
				
			CRANK_FOREACH_G_PTR_ARRAY_END
		}
	}
	
	g_queue_free (visiting_queue);
	g_hash_table_unref (visited_set);
	
	return result;
}

/**
 * crank_digraph_node_foreach_breadth:
 * @node: A node.
 * @func: (scope call): A function to iterate over.
 * @userdata: (closure): userdata for @func.
 *
 * Performs depth-first iteration.
 *
 * Iteration can be stopped by returning %FALSE from @func.
 *
 * Returns: %FALSE, if @func returns %FALSE.
 */
gboolean
crank_digraph_node_foreach_breadth (	CrankDigraphNode*		node,
										CrankDigraphNodeFunc	func,
										gpointer				userdata	)
{
	GHashTable*			visited_set;
	GQueue*				visiting_queue;
	
	CrankDigraphNode*	subnode;
	gboolean			result;
	
	visited_set = g_hash_table_new (g_direct_hash, g_direct_equal);
	visiting_queue = g_queue_new ();
	
	g_queue_push_tail (visiting_queue, node);
	result = TRUE;
	
	while (! g_queue_is_empty (visiting_queue)) {
		subnode = (CrankDigraphNode*) g_queue_pop_head (visiting_queue);
		
		if (! g_hash_table_contains (visited_set, subnode)) {
			g_hash_table_add (visited_set, subnode);
			result = func (subnode, userdata);
			
			if (! result) break;
			
			// Adds each sub item on queue/stack.
			CRANK_FOREACH_G_PTR_ARRAY_BEGIN (
					crank_digraph_node_get_out_edges (subnode),
					CrankDigraphEdge*, edge	)
					
				g_queue_push_tail (visiting_queue, crank_digraph_edge_get_head (edge));
				
			CRANK_FOREACH_G_PTR_ARRAY_END
		}
	}
	
	g_queue_free (visiting_queue);
	g_hash_table_unref (visited_set);
	
	return result;
}





/**
 * crank_digraph_edge_get_data:
 * @edge: An edge.
 * @value: A #GValue to store edge's value. Should be initialized with
 *        appropriate type.
 *
 * Gets value from an edge.
 */
void
crank_digraph_edge_get_data (	CrankDigraphEdge*	edge,
								GValue*			value	)
{
	g_value_copy (& edge->data, value);
}

/**
 * crank_digraph_edge_set_data:
 * @edge: An edge.
 * @value: (nullable): A #GValue to set edge's value.
 *
 * Sets value of edge.
 */
void
crank_digraph_edge_set_data (	CrankDigraphEdge*	edge,
								const GValue*		value	)
{
	crank_value_overwrite (& edge->data, value);
}

/**
 * crank_digraph_edge_type_of:
 * @edge: An edge.
 *
 * Gets #GType of #GValue that the edge holds.
 *
 * Returns: GType of GValue.
 */
GType
crank_digraph_edge_type_of (	CrankDigraphEdge*	edge	)
{
	return G_VALUE_TYPE (& edge->data);
}

/**
 * crank_digraph_edge_get_tail:
 * @edge: An edge.
 *
 * Gets the tail node of edge.
 *
 * Returns: (transfer none): Tail node of edge.
 */
CrankDigraphNode*
crank_digraph_edge_get_tail (	CrankDigraphEdge*	edge	)
{
	return edge->tail;
}

/**
 * crank_digraph_edge_get_head:
 * @edge: An edge.
 *
 * Gets the head node of edge.
 *
 * Returns: (transfer none): Head node of edge.
 */
CrankDigraphNode*
crank_digraph_edge_get_head (	CrankDigraphEdge*	edge	)
{
	return edge->head;
}



/**
 * crank_digraph_add_pointer:
 * @graph: A digraph.
 * @ptype: GType for @pointer. %G_TYPE_POINTER may be passed.
 * @pointer: A pointer.
 *
 * Adds a pointer valued node.
 *
 * Returns: (transfer none): Newly added node.
 */
CrankDigraphNode*
crank_digraph_add_pointer (	CrankDigraph*	graph,
							const GType		ptype,
							gpointer		pointer )
{
	GValue				value = { 0 };
	CrankDigraphNode*	node;
	
	g_value_init (&value, ptype);
	g_value_set_pointer (&value, pointer);
	
	node = crank_digraph_add (graph, &value);
	
	g_value_unset (&value);
	
	return node;
}

/**
 * crank_digraph_add_boxed:
 * @graph: A digraph.
 * @btype: GType for @boxed.
 * @boxed: A boxed.
 *
 * Adds a boxed valued node.
 *
 * Returns: (transfer none): Newly added node.
 */
CrankDigraphNode*
crank_digraph_add_boxed (	CrankDigraph*	graph,
							const GType		btype,
							gpointer		boxed )
{
	GValue				value = { 0 };
	CrankDigraphNode*	node;
	
	g_value_init (&value, btype);
	g_value_set_boxed (&value, boxed);
	
	node = crank_digraph_add (graph, &value);
	
	g_value_unset (&value);
	
	return node;
}


/**
 * crank_digraph_add_object:
 * @graph: A digraph.
 * @object: A GObject.
 *
 * Adds a #GObject valued node.
 *
 * Returns: (transfer none): Newly added node.
 */
CrankDigraphNode*
crank_digraph_add_object (	CrankDigraph*	graph,
							GObject*		object )
{
	GValue				value = { 0 };
	CrankDigraphNode*	node;
	
	g_value_init (&value, G_TYPE_OBJECT);
	g_value_set_object (&value, object);
	
	node = crank_digraph_add (graph, &value);
	
	g_value_unset (&value);
	
	return node;
}




/**
 * crank_digraph_connect_void:
 * @graph: A digraph.
 * @tail: Tail node for edge.
 * @head: Head node for edge.
 *
 * Creates a valueless edge that connects @tail and @head.
 *
 * Returns: (transfer none) (nullable):
 *        Newly created edge that connects two nodes. If there is already a edge
 *        that connects, no edge is created and returns %NULL.
 */
CrankDigraphEdge*
crank_digraph_connect_void (	CrankDigraph*		graph,
							CrankDigraphNode*	tail,
							CrankDigraphNode*	head	)
{
	return crank_digraph_connect (graph, tail, head, NULL);
}

/**
 * crank_digraph_connect_float:
 * @graph: A digraph.
 * @tail: Tail node for edge.
 * @head: Head node for edge.
 * @value: Value of edge.
 *
 * Creates a float-valued edge that connects @tail and @head.
 *
 * Returns: (transfer none) (nullable):
 *        Newly created edge that connects two nodes. If there is already a edge
 *        that connects, no edge is created and returns %NULL.
 */
CrankDigraphEdge*
crank_digraph_connect_float (	CrankDigraph*		graph,
								CrankDigraphNode*	tail,
								CrankDigraphNode*	head,
								const gfloat		value	)
{
	GValue				edgev = { 0 };
	CrankDigraphEdge*	edge;
	
	g_value_init (&edgev, G_TYPE_FLOAT);
	g_value_set_float (&edgev, value);
	
	edge = crank_digraph_connect (graph, tail, head, &edgev);
	
	g_value_unset (&edgev);
	
	return edge;
}

/**
 * crank_digraph_connect_double:
 * @graph: A digraph.
 * @tail: Tail node for edge.
 * @head: Head node for edge.
 * @value: Value of edge.
 *
 * Creates a double-valued edge that connects @tail and @head.
 *
 * Returns: (transfer none) (nullable):
 *        Newly created edge that connects two nodes. If there is already a edge
 *        that connects, no edge is created and returns %NULL.
 */
CrankDigraphEdge*
crank_digraph_connect_double (	CrankDigraph*		graph,
								CrankDigraphNode*	tail,
								CrankDigraphNode*	head,
								const gdouble		value	)
{
	GValue				edgev = { 0 };
	CrankDigraphEdge*	edge;
	
	g_value_init (&edgev, G_TYPE_DOUBLE);
	g_value_set_double (&edgev, value);
	
	edge = crank_digraph_connect (graph, tail, head, &edgev);
	
	g_value_unset (&edgev);
	
	return edge;
}

/**
 * crank_digraph_connect_pointer:
 * @graph: A digraph.
 * @tail: Tail node for edge.
 * @head: Head node for edge.
 * @ptype: Type of @pointer.
 * @pointer: Pointer for edge.
 *
 * Creates a pointer-valued edge that connects @tail and @head.
 *
 * Returns: (transfer none) (nullable):
 *        Newly created edge that connects two nodes. If there is already a edge
 *        that connects, no edge is created and returns %NULL.
 */
CrankDigraphEdge*
crank_digraph_connect_pointer (	CrankDigraph*		graph,
								CrankDigraphNode*	tail,
								CrankDigraphNode*	head,
								const GType			ptype,
								gpointer			pointer	)
{
	GValue				edgev = { 0 };
	CrankDigraphEdge*	edge;
	
	g_value_init (&edgev, ptype);
	g_value_set_pointer (&edgev, pointer);
	
	edge = crank_digraph_connect (graph, tail, head, &edgev);
	
	g_value_unset (&edgev);
	
	return edge;
}


/**
 * crank_digraph_connect_boxed:
 * @graph: A digraph.
 * @tail: Tail node for edge.
 * @head: Head node for edge.
 * @btype: Type of @boxed
 * @boxed: Boxed for edge.
 *
 * Creates a boxed-valued edge that connects @tail and @head.
 *
 * Returns: (transfer none) (nullable):
 *        Newly created edge that connects two nodes. If there is already a edge
 *        that connects, no edge is created and returns %NULL.
 */
CrankDigraphEdge*
crank_digraph_connect_boxed (	CrankDigraph*		graph,
								CrankDigraphNode*	tail,
								CrankDigraphNode*	head,
								const GType			btype,
								gpointer			boxed	)
{
	GValue				edgev = { 0 };
	CrankDigraphEdge*	edge;
	
	g_value_init (&edgev, btype);
	g_value_set_boxed (&edgev, boxed);
	
	edge = crank_digraph_connect (graph, tail, head, &edgev);
	
	g_value_unset (&edgev);
	
	return edge;
}


/**
 * crank_digraph_connect_object:
 * @graph: A digraph.
 * @tail: Tail node for edge.
 * @head: Head node for edge.
 * @object: #GObject for edge.
 *
 * Creates a object-valued edge that connects @tail and @head.
 *
 * Returns: (transfer none) (nullable):
 *        Newly created edge that connects two nodes. If there is already a edge
 *        that connects, no edge is created and returns %NULL.
 */
CrankDigraphEdge*
crank_digraph_connect_object (	CrankDigraph*		graph,
								CrankDigraphNode*	tail,
								CrankDigraphNode*	head,
								GObject*			object	)
{
	GValue				edgev = { 0 };
	CrankDigraphEdge*	edge;
	
	g_value_init (&edgev, G_TYPE_OBJECT);
	g_value_set_object (&edgev, object);
	
	edge = crank_digraph_connect (graph, tail, head, &edgev);
	
	g_value_unset (&edgev);
	
	return edge;
}


/**
 * crank_digraph_node_get_pointer:
 * @node: A node.
 *
 * Gets a pointer value of node.
 *
 * Returns: (transfer none): Pointer value of node.
 */
gpointer
crank_digraph_node_get_pointer (	CrankDigraphNode*	node	)
{
	return g_value_get_pointer (& node->data);
}

/**
 * crank_digraph_node_get_boxed:
 * @node: A node.
 *
 * Gets a boxed value of node.
 *
 * Returns: (transfer none): Boxed value of node.
 */
gpointer
crank_digraph_node_get_boxed (	CrankDigraphNode*	node	)
{
	return g_value_get_boxed (& node->data);
}

/**
 * crank_digraph_node_get_object:
 * @node: A node.
 *
 * Gets a #GObject value of node.
 *
 * Returns: (transfer none): GObject value of node.
 */
GObject*
crank_digraph_node_get_object (	CrankDigraphNode*	node	)
{
	return g_value_get_object (& node->data);
}



/**
 * crank_digraph_edge_get_float:
 * @edge: A edge.
 *
 * Gets a float value of edge.
 *
 * Returns: Float value of edge.
 */
gfloat
crank_digraph_edge_get_float (	CrankDigraphEdge*	edge	)
{
	return g_value_get_float (& edge->data);
}

/**
 * crank_digraph_edge_get_double:
 * @edge: An edge.
 *
 * Gets a double value of edge.
 *
 * Returns: Double value of edge.
 */
gdouble
crank_digraph_edge_get_double (	CrankDigraphEdge*	edge	)
{
	return g_value_get_double (& edge->data);
}

/**
 * crank_digraph_edge_get_pointer:
 * @edge: An edge.
 *
 * Gets a pointer value of edge.
 *
 * Returns: (transfer none): Pointer value of edge.
 */
gpointer
crank_digraph_edge_get_pointer (	CrankDigraphEdge*	edge	)
{
	return g_value_get_pointer (& edge->data);
}

/**
 * crank_digraph_edge_get_boxed:
 * @edge: An edge.
 *
 * Gets a boxed value of edge.
 *
 * Returns: (transfer none): Boxed value of edge.
 */
gpointer
crank_digraph_edge_get_boxed (	CrankDigraphEdge*	edge	)
{
	return g_value_get_boxed (& edge->data);
}

/**
 * crank_digraph_edge_get_object:
 * @edge: An edge.
 *
 * Gets a #GObject value of edge.
 *
 * Returns: (transfer none): GObject value of edge.
 */
GObject*
crank_digraph_edge_get_object (	CrankDigraphEdge*	edge	)
{
	return g_value_get_object (& edge->data);
}


/**
 * crank_digraph_node_set_pointer:
 * @node: A node.
 * @ptype: #GType of @pointer.
 * @pointer: Pointer to set the value.
 *
 * Sets value of node to pointer.
 */
void
crank_digraph_node_set_pointer (	CrankDigraphNode*	node,
									const GType			ptype,
									gpointer			pointer	)
{
	crank_value_overwrite_pointer (& node->data, ptype, pointer);
}

/**
 * crank_digraph_node_set_boxed:
 * @node: A node.
 * @btype: #GType of @boxed.
 * @boxed: A boxed.
 *
 * Sets value of node to boxed.
 */
void
crank_digraph_node_set_boxed (	CrankDigraphNode*	node,
								const GType			btype,
								gpointer			boxed	)
{
	crank_value_overwrite_boxed (& node->data, btype, boxed);
}

/**
 * crank_digraph_node_set_object:
 * @node: A node.
 * @object: A #GObject.
 *
 * Sets value of node to #GObject
 */
void
crank_digraph_node_set_object (	CrankDigraphNode*	node,
								GObject*			object )
{
	crank_value_overwrite_object (& node->data, object);
}




/**
 * crank_digraph_edge_set_float:
 * @edge: An edge.
 * @value: A float value.
 *
 * Sets value of edge to float.
 */
void
crank_digraph_edge_set_float (	CrankDigraphEdge*	edge,
								const gfloat		value	)
{
	crank_value_overwrite_init (& edge->data, G_TYPE_FLOAT);
	g_value_set_float (& edge->data, value);
}

/**
 * crank_digraph_edge_set_double:
 * @edge: An edge.
 * @value: A double value.
 *
 * Sets value of edge to double.
 */
void
crank_digraph_edge_set_double (	CrankDigraphEdge*	edge,
								const gdouble		value	)
{
	crank_value_overwrite_init (& edge->data, G_TYPE_DOUBLE);
	g_value_set_double (& edge->data, value);
}

/**
 * crank_digraph_edge_set_pointer:
 * @edge: An edge.
 * @ptype: #GType of @pointer.
 * @pointer: A pointer value.
 *
 * Sets value of edge to pointer.
 */
void
crank_digraph_edge_set_pointer (	CrankDigraphEdge*	edge,
									const GType			ptype,
									gpointer			pointer	)
{
	crank_value_overwrite_pointer (& edge->data, ptype, pointer);
}

/**
 * crank_digraph_edge_set_boxed:
 * @edge: An edge.
 * @btype: #GType of @boxed.
 * @boxed: (transfer none): A boxed value.
 *
 * Sets value of edge to boxed.
 */
void
crank_digraph_edge_set_boxed (	CrankDigraphEdge*	edge,
								const GType			btype,
								gpointer			boxed	)
{
	crank_value_overwrite_boxed (& edge->data, btype, boxed);
}

/**
 * crank_digraph_edge_set_object:
 * @edge: An edge.
 * @object: (transfer none): A #GObject.
 *
 * Sets value of edge to object.
 */
void
crank_digraph_edge_set_object (	CrankDigraphEdge*	edge,
								GObject*			object )
{
	crank_value_overwrite_object (& edge->data, object);
}



//////// Internal Functions ////////

/*
 * crank_digraph_node_new: (private)
 * @value: Value.
 *
 * Constructs new node.
 */
CrankDigraphNode*
crank_digraph_node_new (	const GValue*	value	)
{
	CrankDigraphNode*	node = g_slice_new0 (CrankDigraphNode);

	crank_value_overwrite (& node->data, value);
	
	node->in_edges = g_ptr_array_new ();
	node->out_edges = g_ptr_array_new ();
	
	return node;
}

void
crank_digraph_node_free (	CrankDigraphNode*	node	)
{
	if (G_IS_VALUE (& node->data)) g_value_unset (& node->data);
	
	g_slice_free (CrankDigraphNode, node);
}

/*
 * crank_digraph_edge_new: (private)
 * @data: Value.
 *
 * Constructs new edge with given nodes.
 */
CrankDigraphEdge*
crank_digraph_edge_new (	const GValue*	value,
							CrankDigraphNode*	tail,
							CrankDigraphNode*	head	)
{
	CrankDigraphEdge* edge = g_slice_new0 (CrankDigraphEdge);
	
	if (value != NULL) crank_value_overwrite (& edge->data, value);
	
	edge->tail = tail;
	edge->head = head;
	
	return edge;
}

void
crank_digraph_edge_free (	CrankDigraphEdge*	edge	)
{
	if (G_IS_VALUE (& edge->data)) g_value_unset (& edge->data);
	
	g_slice_free (CrankDigraphEdge, edge);
}
