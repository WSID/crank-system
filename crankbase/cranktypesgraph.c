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
#define _CRANKBASE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankvalue.h"
#include "crankdigraph.h"
#include "cranktypesgraph.h"

/**
 * SECTION: cranktypesgraph
 * @title: CrankTypesGraph
 * @short_description: Data structure to manage arrays of types.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * CrankTypesGraph is a key-value data structure that manages datas, by relation
 * of arrays of types. This data structures is mainly backing for
 * #CrankFuncHolder, to passing functions for given types.
 *
 * # Keys and Values
 *
 * #CrankTypesGraph uses array of #GType as key. Therefore, pointer of array and
 * length should be passed. And result array of crank_types_graph_lookup()
 * familes have same length as arrays that passed.
 *
 * #CrankTypesGraph stores data in #GValue. Datas should be passed by #GValue.
 *
 * When setting data, Any #GValue can be passed. When receiving data, #GValue
 * should be initialized with appropriate type.
 *
 * # is-a relationship of types # {#is_a}
 *
 * If inheritence of types A, B, C, D and E is defined as below,
 *
 * -A
 *   - B
 *   - C
 *     - D
 *     - E
 *
 * Then the followings are true, for is-a relationship.
 *
 * - E is a A
 * - C is a A
 * - B is not a D ...
 *
 * In #CrankTypesGraph, two arrays are considered to have is-a relation if,
 *
 * - Same size of array.
 * - Each element of one array has is-a relation to matching element of other
 *    array.
 *
 *    For example, To have [C, D] is a [A, B], C should be A, D should be B.
 *
 * Therefore, the followings are true.
 *
 * - [A] is not a [A, A]
 * - [D, E] is a [A, C]
 * - [C, E] is not a [E, C]
 *
 * Types Graph manages array of types, rather than single type. So one array
 * may have is-a relation to other. If this is happens, #CrankTypesGraph will
 * return the array with most derived types. (Which has most largest sum of
 * depth of types.)
 */

//////// Internal Structure Declaration ////////////////////////////////////////

typedef struct _CrankTypesGraphData	CrankTypesGraphData;

static G_GNUC_MALLOC
gchar*				crank_typestring (				const GType*	types,
													const guint		ntypes	);

static
gboolean			crank_types_is_a (				const GType*	types_a,
													const GType*	types_b,
													const guint		ntypes	);

static
CrankTypesGraphData*	crank_types_graph_data_new	(	const GType*	types,
													const guint		ntypes,
													const GValue*	value	);	

static
void				crank_types_graph_data_free (	CrankTypesGraphData*	data);

//////// CrankTypesNode
													
static G_GNUC_MALLOC
gchar*				crank_types_node_typestring (	CrankDigraphNode*	node	);

static
gboolean			crank_types_node_add (			CrankDigraph*		digraph,
													CrankDigraphNode*	parent,
													CrankDigraphNode*	node	);
static
CrankDigraphNode*	crank_types_node_get (			CrankDigraphNode* parent,
													const GType*	key,
													const guint		key_length	);
static
gboolean			crank_types_node_lookup (		CrankDigraphNode* parent,
													const GType*	key,
													const guint		key_length,
										  			GList**			lookup_list	);
													
//////// CrankTypesRoot
													
static
void				crank_types_root_remove (		CrankDigraph*		digraph,
													CrankDigraphNode*	root,
													CrankDigraphNode*	node		);


//////// Internal Structure Definition /////////////////////////////////////////

struct _CrankTypesGraphData {
	GType*				types;	// Node value
	guint				ntypes;
	
	guint				types_depth;
	
	GValue				value;
};

/*
 * crank_typestring:
 * @types: (array length=ntypes): An array of #GType.
 * @ntypes: Length of @types.
 *
 * Creates string representation of type array.
 * Generally, it is used for debugging.
 *
 * Returns: Comma separated names of type.
 */
static G_GNUC_MALLOC gchar*
crank_typestring	(	const GType*	types,
						const guint		ntypes	)
{
	GString*	str_builder;
	gchar*		str;
		
	// We can guarantee that we have at least 1 type in node->types.
	str_builder = g_string_new (g_type_name (types[0]));
	
	CRANK_FOREACH_ARRAY_BEGIN ((types + 1), GType, type, ntypes - 1)
		g_string_append (str_builder, ", ");
		g_string_append (str_builder, g_type_name (type));
	CRANK_FOREACH_ARRAY_END
	
	str = str_builder->str;
	g_string_free (str_builder, FALSE);
	
	return str;
}

/*
 * crank_types_is_a:
 * @types: (array length=ntypes): An array of #GType.
 * @types_is_a: (array length=ntypes): An array of #GType.
 * @ntypes: Length of both array.
 *
 * Checks @types is a @types_is_a. Used when inserting nodes.
 *
 * Returns: Whether @types is a @types_is_a.
 */
static gboolean
crank_types_is_a	(	const GType*	types,
						const GType*	types_is_a,
						const guint		ntypes	)
{
	guint i;
	
	if (types == NULL) return FALSE;
	if (types_is_a == NULL) return TRUE;
	
	for (i = 0; i < ntypes; i++) {
		if (! g_type_is_a(types[i], types_is_a[i])) return FALSE;
	}
	return TRUE;
}

static CrankTypesGraphData*
crank_types_graph_data_new (const GType* types, const guint ntypes, const GValue* value )
{
	CrankTypesGraphData* data = g_new (CrankTypesGraphData, 1);

	data->types = CRANK_ARRAY_DUP (types, GType, ntypes);
	data->ntypes = ntypes;
	data->types_depth = 0;
	
	if (types != NULL) {
		CRANK_FOREACH_ARRAY_DO(data->types, GType, type, data->ntypes, {
			data->types_depth += g_type_depth (type);
		})
	}
	
	memset (&data->value, 0, sizeof(GValue));
	crank_value_overwrite (&data->value, value);
	
	return data;
}

static void
crank_types_graph_data_free (CrankTypesGraphData*	data)
{
	g_free (data->types);
	if (G_IS_VALUE(&data->value)) g_value_unset (&data->value);
	
	g_free (data);
}


static G_GNUC_MALLOC gchar*
crank_types_node_typestring (	CrankDigraphNode*	node	)
{
	CrankTypesGraphData*	data = crank_digraph_node_get_pointer (node);
	return crank_typestring (data->types, data->ntypes);
}

static gboolean
crank_types_node_add (	CrankDigraph*		digraph,
						CrankDigraphNode*	parent,
						CrankDigraphNode*	node	)
{
	CrankTypesGraphData*		pdata = crank_digraph_node_get_pointer (parent);
	CrankTypesGraphData*		ndata = crank_digraph_node_get_pointer (node);
	
	GPtrArray*		pout_edges =	crank_digraph_node_get_out_edges (parent);
	
	// Checks that node is ancestor of parent.
	if (crank_types_is_a (ndata->types, pdata->types, ndata->ntypes)) {
		gboolean add_to_subnode = FALSE;
	
		// Checks if the node is ancestor of subnodes.
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (pout_edges, CrankDigraphEdge*, edge)
			
			CrankDigraphNode* sub = crank_digraph_edge_get_head (edge);
			if (crank_types_node_add (digraph, sub, node))
				add_to_subnode = TRUE;
			
		CRANK_FOREACH_G_PTR_ARRAY_END
		
		// If no subnode is connected to node, connect it to parent.
		if (! add_to_subnode) {
			// If subnode is ancestor of node, connect it, unlinking from parent.
			CRANK_FOREACH_G_PTR_ARRAY_BEGIN (pout_edges, CrankDigraphEdge*, edge)
			
				CrankDigraphNode* sub = crank_digraph_edge_get_head (edge);
				CrankTypesGraphData* sdata = crank_digraph_node_get_pointer (sub);
		
				if (crank_types_is_a(sdata->types, ndata->types, ndata->ntypes)) {
					crank_digraph_disconnect (digraph, parent, sub);
					crank_digraph_connect_void (digraph, node, sub);
				}

			CRANK_FOREACH_G_PTR_ARRAY_END

			crank_digraph_connect_void (digraph, parent, node);
		}
		
		return TRUE;
	}

	else return FALSE;
}

static CrankDigraphNode*
crank_types_node_get (	CrankDigraphNode* parent,
						const GType*	key,
						const guint		key_length	)
{
	CrankDigraphNode*	result;
	CrankTypesGraphData*	pdata;
	GPtrArray*				pout_edges;
	
	pdata = crank_digraph_node_get_pointer (parent);
	pout_edges = crank_digraph_node_get_out_edges (parent);

	if (	(pdata->types != NULL) &&
			(CRANK_ARRAY_CMP (pdata->types, key, GType, key_length) == 0)	) {
		return parent;
	}
	
	else if (crank_types_is_a (key, pdata->types, key_length)) {
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (pout_edges, CrankDigraphEdge*, edge)
		
			CrankDigraphNode*	sub = crank_digraph_edge_get_head (edge);
			
			result = crank_types_node_get (sub, key, key_length);
			if (result != NULL) return result;
			
		CRANK_FOREACH_G_PTR_ARRAY_END
	}
	
	return NULL;
}

static gboolean
crank_types_node_lookup (	CrankDigraphNode* parent,
							const GType*	key,
							const guint		key_length,
						 	GList**			lookup_list	)
{
	CrankTypesGraphData*	pdata = crank_digraph_node_get_pointer (parent);
	if (	(pdata->types != NULL) &&
			(CRANK_ARRAY_CMP (pdata->types, key, GType, key_length) == 0)	) {
		if (g_list_find(*lookup_list, parent) == NULL) {
			*lookup_list = g_list_prepend (*lookup_list, parent);
			return TRUE;
		}
	}

	else if (crank_types_is_a (key, pdata->types, key_length)) {
		GPtrArray*	pout_edges = crank_digraph_node_get_out_edges (parent);
		gboolean	list_added = FALSE;

		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (pout_edges, CrankDigraphEdge*, edge)
			CrankDigraphNode*	sub = crank_digraph_edge_get_head (edge);
			list_added =
					list_added ||
					crank_types_node_lookup (sub, key, key_length, lookup_list);
		CRANK_FOREACH_G_PTR_ARRAY_END
		
		if (list_added) return TRUE;
		else {
			if (g_list_find(*lookup_list, parent) == NULL) {
				*lookup_list = g_list_prepend (*lookup_list, parent);
				return TRUE;
			}
		}
	}
	
	return FALSE;
}


//////// CrankTypesRoot

static void
crank_types_root_remove (	CrankDigraph*		digraph,
							CrankDigraphNode*	root,
							CrankDigraphNode*	node	)
{
	CrankTypesGraphData*	ndata;
	GPtrArray*		out_edges;
	GPtrArray*		in_edges;
	
	ndata = crank_digraph_node_get_pointer (node);
	out_edges = crank_digraph_node_get_out_edges (node);
	in_edges = crank_digraph_node_get_in_edges (node);
	
	// Disconnect from subnodes.
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN(out_edges, CrankDigraphEdge*, out_edge)
		CrankDigraphNode* subnode = crank_digraph_edge_get_head (out_edge);
		
		if (crank_digraph_node_get_indegree (subnode) == 1) {
		
			CRANK_FOREACH_G_PTR_ARRAY_BEGIN(in_edges, CrankDigraphEdge*, in_edge)
				CrankDigraphNode* pnode = crank_digraph_edge_get_tail (in_edge);
				crank_digraph_connect_void (digraph, pnode, subnode);
			CRANK_FOREACH_G_PTR_ARRAY_END
			
		}
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	crank_types_graph_data_free (
			crank_digraph_node_get_pointer (node)	);
	crank_digraph_remove (digraph, node);
}

////////// Declaration /////////////////////////////////////////////////////////

/**
 * CrankTypesGraph:
 *
 * 여러 타입 정보를 관리하는 그래프입니다.
 */
struct _CrankTypesGraph {
	CrankDigraph*		base;
	
	CrankDigraphNode**	roots;
	guint				nroots;
	
	guint 			_refc;
};

G_DEFINE_BOXED_TYPE (CrankTypesGraph,
		crank_types_graph,
		crank_types_graph_ref,
		crank_types_graph_unref)

static
CrankDigraphNode*		crank_types_graph_get_root (		CrankTypesGraph*	graph,
														const guint			key_length	);

static
CrankDigraphNode*		crank_types_graph_lookup_node (		CrankTypesGraph*	graph,
														const GType*		key,
														const guint			key_length	);




//////// Definition ////////////////////////////////////////////////////////////


//////// Internal functions

static CrankDigraphNode*
crank_types_graph_get_root (	CrankTypesGraph*	graph,
								const guint			key_length	)
{
	guint	i;
	guint	root_len;

	root_len = graph->nroots;

	if (graph->nroots < key_length) {
		while (graph->nroots < key_length) {
			graph->nroots = graph->nroots >> 1;
		}
		graph->roots = g_renew (CrankDigraphNode*, graph->roots, graph->nroots);
		for (i = root_len; i < graph->nroots; i++)
			graph->roots[i] = NULL;
	}

	if (graph->roots[key_length] == NULL) {
		GValue					value = { 0 };
		
		CrankTypesGraphData*	data = crank_types_graph_data_new (NULL, key_length, &value);
		
		graph->roots[key_length] = crank_digraph_add_pointer (graph->base, G_TYPE_POINTER, data);
	}

	return graph->roots[key_length];
}

static CrankDigraphNode*
crank_types_graph_lookup_node (	CrankTypesGraph*	graph,
							  	const GType*		key,
							  	const guint			key_length	)
{
	// For future, more way to pick one from candidates.

	CrankDigraphNode*	root;
	CrankDigraphNode*	node = NULL;
  	GList*				lookup_list = NULL;

	root = crank_types_graph_get_root (graph, key_length);
	crank_types_node_lookup (root, key, key_length, &lookup_list);

  	if (lookup_list != NULL) {
		GList* i;
	  	guint	depth_max = 0;
	 	guint	depth;
	 	
	 	CRANK_FOREACH_GLIST_BEGIN (lookup_list, CrankDigraphNode*, lookup_node)
			CrankTypesGraphData* data = crank_digraph_node_get_pointer (lookup_node);
			
	  		depth = data->types_depth;
	  		
	  		if (depth_max < depth) {
				depth_max = depth;
		  		node = lookup_node;
			}
		CRANK_FOREACH_GLIST_END
	}
	
  	return node;
}

//////// Functions

/**
 * crank_types_graph_new: (constructor)
 *
 * Constructs empty types graph.
 *
 * Returns: (transfer full): Newly created #CrankTypesGraph.
 */
CrankTypesGraph*
crank_types_graph_new (void)
{
	CrankTypesGraph*	graph = g_new (CrankTypesGraph, 1);
	
	graph->base = crank_digraph_new ();
	
	graph->roots = g_new0 (CrankDigraphNode*, 4);
	graph->nroots = 4;
	
	graph->_refc = 1;
	
	return graph;
}

/**
 * crank_types_graph_ref:
 * @graph: A types graph.
 *
 * Increase reference count by 1.
 *
 * Returns: (transfer full): @graph with increased reference count.
 */
CrankTypesGraph*
crank_types_graph_ref (CrankTypesGraph*	graph)
{
	g_atomic_int_inc (& (graph->_refc));
  	return graph;
}

/**
 * crank_types_graph_unref:
 * @graph: A types graph.
 *
 * Decrease reference count by 1. If reference count reaches 0, the graph is
 * freed.
 */
void
crank_types_graph_unref (CrankTypesGraph*	graph)
{
	if (g_atomic_int_dec_and_test (& (graph->_refc)) ) {
		
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (	crank_digraph_get_nodes (graph->base), CrankDigraphNode*,	node)
			
			crank_types_graph_data_free (
					(CrankTypesGraphData*) crank_digraph_node_get_pointer (node));
		
		CRANK_FOREACH_G_PTR_ARRAY_END
		
		crank_digraph_unref (graph->base);
	
		g_free (graph->roots);
		g_free (graph);
	}
}

/**
 * crank_types_graph_set:
 * @graph: A types graph.
 * @key: (array length=key_length): A key to set value.
 * @key_length: Size of the key.
 * @value: Value to set.
 *
 * Set a value of types graph by given key.
 */
void
crank_types_graph_set ( CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length,
						const GValue*		value	)
{
	CrankDigraphNode*		root;
	CrankDigraphNode*		node;
	CrankTypesGraphData*	data;
	
	root = crank_types_graph_get_root (graph, key_length);
	node = crank_types_node_get (root, key, key_length);
	
	if (node == NULL) {
		data = crank_types_graph_data_new (	key, key_length, value );
		node = crank_digraph_add_pointer (graph->base, G_TYPE_POINTER, data);
		crank_types_node_add (graph->base, root, node);
		
	}
	else {
		data = crank_digraph_node_get_pointer (node);
	  	crank_value_overwrite (&data->value, value);
	}
}

/**
 * crank_types_graph_get:
 * @graph: A types graph.
 * @key: (array length=key_length): A key to set value.
 * @key_length: Size of the key.
 * @value: Value to get. It should be initialized by appropriate type.
 *
 * Gets value for given key.
 *
 * Use crank_types_graph_lookup() if [is-a relationship][is_a] should be
 * considered.
 *
 * Returns: %TRUE if the key exists.
 */
gboolean
crank_types_graph_get ( CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length,
						GValue*				value	)
{
	CrankDigraphNode*		root;
	CrankDigraphNode*		node;
	CrankTypesGraphData*	data;
	
	root = crank_types_graph_get_root (graph, key_length);
	node = crank_types_node_get (root, key, key_length);
	
	if (node != NULL) {
		data = crank_digraph_node_get_pointer (node);
		g_value_copy(&data->value, value);
		return TRUE;
	}
	return FALSE;
}

/**
 * crank_types_graph_has:
 * @graph: A types graph.
 * @key: (array length=key_length): A key to check existence.
 * @key_length: Size of the key.
 *
 * Checks existence of key in a graph.
 *
 * Returns: %FALSE, If the key does not exist.
 */
gboolean
crank_types_graph_has (	CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length	)
{
	CrankDigraphNode*		root;
	CrankDigraphNode*		node;
	
	root = crank_types_graph_get_root (graph, key_length);
	node = crank_types_node_get (root, key, key_length);
	
	return node != NULL;
}

/**
 * crank_types_graph_lookup:
 * @graph: A types graph.
 * @key: (array length=key_length): A key to look up.
 * @key_length: Size of the key.
 * @value: A GValue to store value. It should be initialized with appropriate
 *         type.
 *
 * Looks up value which matches to given key. Even the key does not exist, the
 * value of most appropriate key on graph is retrieved.
 *
 * Returns: %FALSE, If there is no matching key.
 */
gboolean
crank_types_graph_lookup (	CrankTypesGraph*	graph,
							const GType*		key,
							const guint			key_length,
							GValue*				value	)
{
	CrankDigraphNode*	node = crank_types_graph_lookup_node (
			graph, key, key_length );
	
	if (node != NULL) {
		CrankTypesGraphData*	data = crank_digraph_node_get_pointer (node);
		g_value_copy(&data->value, value);
		return TRUE;
	}
	return node != NULL;
}


/**
 * crank_types_graph_lookup_types:
 * @graph: A types graph.
 * @key: (array length=key_length): A key to look up.
 * @key_length: Size of the key.
 *
 * Looks up most appropriate key for given key. If the given key exists in graph,
 * the given key is returned.
 *
 * Returns: (array length=key_length) (nullable): Most appropriate key for @key.
 */
const GType*
crank_types_graph_lookup_types (CrankTypesGraph*	graph,
								const GType*		key,
								const guint			key_length	)
{
	CrankDigraphNode*	node = crank_types_graph_lookup_node (
			graph, key, key_length );
			
	if (node != NULL) {
		CrankTypesGraphData*	data = crank_digraph_node_get_pointer (node);
		
		return data->types;
	}
	else {
		return NULL;
	}
}

/**
 * crank_types_graph_lookup_full:
 * @graph: A types graph.
 * @key: (array length=key_length): A key to look up.
 * @key_length: Size of the key.
 * @key_orig: (out) (array length=key_length) (transfer none):
 *         Return location for most appropriate key.
 * @value: A GValue to store value.
 *
 * Looks up appropriate key and its value for @key.
 *
 * Returns: %FALSE if there is no matching key.
 */
gboolean
crank_types_graph_lookup_full (	CrankTypesGraph*	graph,
								const GType*		key,
								const guint			key_length,
								GType**				key_orig,
								GValue*				value	)
{
	CrankDigraphNode* node = crank_types_graph_lookup_node (
			graph, key, key_length );
	
	if (node != NULL) {
		CrankTypesGraphData*	data = crank_digraph_node_get_pointer (node);
		g_value_copy (&data->value, value);
		*key_orig = data->types;
	}
	
	return node != NULL;
}

/**
 * crank_types_graph_remove:
 * @graph: A types graph.
 * @key: (array length=key_length): A key to remove.
 * @key_length: Size of the key.
 *
 * Removes a key from graph.
 *
 * Returns: %TRUE if the key existed and was removed.
 */
gboolean
crank_types_graph_remove (	CrankTypesGraph*	graph,
							const GType*		key,
							const guint			key_length	)
{
	CrankDigraphNode* root;
	CrankDigraphNode*	node;
	
	root = crank_types_graph_get_root (graph, key_length);
	node = crank_types_node_get (root, key, key_length);
	
	if (node != NULL) {
		crank_types_root_remove (graph->base, root, node);
		return TRUE;
	}
	
	return FALSE;
}



/**
 * crank_types_graph_gir_lookup_types: (rename-to crank_types_graph_lookup_types)
 * @graph: A types graph.
 * @key: (array length=key_length): A key to look up.
 * @key_length: Size of the key.
 * @ret_length: Location to copy @key_length.
 *
 * Looks up most appropriate key for given key.
 *
 * This function returns length of returned array, so less problem with
 * pyGObject, Vala, etc.
 *
 * Returns: (array length=ret_length): Most appropriate key for @key.
 */
const GType*
crank_types_graph_gir_lookup_types (CrankTypesGraph*	graph,
									const GType*		key,
									const guint			key_length,
									guint*				ret_length	)
{
	*ret_length = key_length;
	return crank_types_graph_lookup_types (graph, key, key_length);
}

/**
 * crank_types_graph_gir_lookup_full: (rename-to crank_types_graph_lookup_full)
 * @graph: A types graph.
 * @key: (array length=key_length): A key to look up.
 * @key_length: Size of the key.
 * @key_orig: (out) (array length=ret_length) (transfer none):
 *        The location for most appropriate key.
 * @ret_length: (out): Location to copy @key_length.
 * @value: 값입니다.
 *
 * Looks up the key and value for given key.
 *
 * This function returns length of returned array, so less problem with
 * pyGObject, Vala, etc.
 *
 * Returns: %FALSE if there is no matching key.
 */
gboolean
crank_types_graph_gir_lookup_full (	CrankTypesGraph*	graph,
									const GType*		key,
									const guint			key_length,
									GType**				key_orig,
									guint*				ret_length,
									GValue*				value		)
{
	*ret_length = key_length;
	return crank_types_graph_lookup_full (graph, key, key_length, key_orig, value);
}

/**
 * crank_types_graph_get_key_lengths:
 * @graph: A types graph.
 *
 * Gets lengths of all keys.
 *
 * For ([int], [float], [int, float]), it returns 1, 2.
 *
 * Returns: (element-type gint) (transfer container):
 *         The lengths of keys the graph holds.
 */
GList*
crank_types_graph_get_key_lengths ( CrankTypesGraph*	graph )
{
	GList*	lengths = NULL;
	gint	i;
	
	for (i = 0; i < graph->nroots; i++) {
		if (graph->roots[i] != NULL) lengths = g_list_append (lengths, GINT_TO_POINTER(i));
	}
	return lengths;
}
