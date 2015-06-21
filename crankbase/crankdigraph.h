#ifndef CRANKGRAPH_H
#define CRANKGRAPH_H

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

#ifndef _CRANKBASE_INSIDE
#error crankdigraph.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS


typedef struct _CrankDigraph		CrankDigraph;
typedef struct _CrankDigraphNode	CrankDigraphNode;
typedef struct _CrankDigraphEdge	CrankDigraphEdge;

#define	CRANK_TYPE_DIGRAPH		(crank_digraph_get_type())
GType			crank_digraph_get_type (void);


typedef struct _CrankDigraphEdgeIndex	CrankDigraphEdgeIndex;

/**
 * CrankDigraphEdgeIndex:
 * @data: Value of data.
 * @tail: Index of tail node.
 * @head: Index of head node.
 *
 * A structure to specify value of edge, in digraph constructor.
 *
 * As nodes are not available on construction, nodes are specified by indices.
 */
struct _CrankDigraphEdgeIndex {
	GValue		data;

  	guint		tail;
  	guint		head;
};


/**
 * CrankDigraphNodeFunc:
 * @node: A node.
 * @userdata: (closure): Userdata.
 *
 * A function type for iterating over nodes.
 *
 * Returns: Return %TRUE to keep iteration.
 */
typedef	gboolean	(*CrankDigraphNodeFunc)		(		CrankDigraphNode*	node,
														gpointer			userdata	);

CrankDigraph*		crank_digraph_new (void);

CrankDigraph*		crank_digraph_new_with_nodes (		const guint			nnodes,
											 			const GValue*		values	);

CrankDigraph*		crank_digraph_new_full		(		const guint			nnodes,
														const GValue*		values,
														const guint			nedges,
														const CrankDigraphEdgeIndex*	edges	);
														

CrankDigraph*		crank_digraph_ref (					CrankDigraph*		graph	);

void				crank_digraph_unref (				CrankDigraph*		graph	);


GPtrArray*			crank_digraph_get_nodes (			CrankDigraph*		graph	);

GPtrArray*			crank_digraph_get_edges (			CrankDigraph*		graph	);

gint				crank_digraph_index_of_node (		CrankDigraph*		graph,
														CrankDigraphNode*	node	);

gint				crank_digraph_index_of_edge (		CrankDigraph*		graph,
														CrankDigraphEdge*	edge	);

CrankDigraphNode*	crank_digraph_nth_node (			CrankDigraph*		graph,
														guint				index	);

CrankDigraphEdge*	crank_digraph_nth_edge (			CrankDigraph*		graph,
														guint				index	);
														

CrankDigraphNode*	crank_digraph_add (					CrankDigraph*		graph,
														const GValue*		value	);

void				crank_digraph_remove (				CrankDigraph*		graph,
														CrankDigraphNode*	node	);

CrankDigraphEdge*	crank_digraph_connect (				CrankDigraph*		graph,
														CrankDigraphNode*	tail,
														CrankDigraphNode* 	head,
														const GValue*		edge_value		);

gboolean			crank_digraph_disconnect (			CrankDigraph*		graph,
														CrankDigraphNode*	tail,
														CrankDigraphNode*	head	);

void				crank_digraph_disconnect_edge (		CrankDigraph*		graph,
                             	      					CrankDigraphEdge*	e	);


void				crank_digraph_reverse (				CrankDigraph*		graph	);

CrankDigraph*		crank_digraph_copy (				CrankDigraph*		graph	);





void				crank_digraph_node_get_data (		CrankDigraphNode*	node,
														GValue*				value	);
														
void				crank_digraph_node_set_data (		CrankDigraphNode*	node,
														const GValue*		value	);

GType				crank_digraph_node_type_of (		CrankDigraphNode*	node	);

GList*				crank_digraph_node_get_in_nodes (	CrankDigraphNode*	node	);

GList*				crank_digraph_node_get_out_nodes (	CrankDigraphNode*	node	);

GPtrArray*			crank_digraph_node_get_in_edges (	CrankDigraphNode* 	node	);

GPtrArray*			crank_digraph_node_get_out_edges (	CrankDigraphNode*	node	);

guint				crank_digraph_node_get_indegree (	CrankDigraphNode*	node	);

guint				crank_digraph_node_get_outdegree(	CrankDigraphNode*	node	);



gboolean			crank_digraph_node_is_adjacent (	CrankDigraphNode*	node,
														CrankDigraphNode*	other	);

gboolean			crank_digraph_node_is_adjacent_from (	CrankDigraphNode*	node,
															CrankDigraphNode*	other	);

gboolean			crank_digraph_node_is_adjacent_to (	CrankDigraphNode*	node,
														CrankDigraphNode*	other	);

gboolean			crank_digraph_node_foreach_depth (	CrankDigraphNode*		node,
														CrankDigraphNodeFunc	func,
														gpointer				userdata	);

gboolean			crank_digraph_node_foreach_breadth (	CrankDigraphNode*		node,
														CrankDigraphNodeFunc	func,
														gpointer				userdata	);

														



void				crank_digraph_edge_get_data (		CrankDigraphEdge*	edge,
														GValue*				value	);

void				crank_digraph_edge_set_data (		CrankDigraphEdge*	edge,
														const GValue*		value	);

GType				crank_digraph_edge_type_of (		CrankDigraphEdge*	edge	);

CrankDigraphNode*	crank_digraph_edge_get_tail (		CrankDigraphEdge*	edge	);

CrankDigraphNode*	crank_digraph_edge_get_head (		CrankDigraphEdge*	edge	);






CrankDigraphNode*	crank_digraph_add_pointer (			CrankDigraph*		graph,
														const GType			ptype,
														gpointer			pointer	);

CrankDigraphNode*	crank_digraph_add_boxed	(			CrankDigraph*		graph,
														const GType			btype,
														gpointer			boxed	);

CrankDigraphNode*	crank_digraph_add_object	(		CrankDigraph*		graph,
														GObject*			object	);


												
CrankDigraphEdge*	crank_digraph_connect_void (		CrankDigraph*		graph,
														CrankDigraphNode*	tail,
														CrankDigraphNode* 	head	);

CrankDigraphEdge*	crank_digraph_connect_float (		CrankDigraph*		graph,
														CrankDigraphNode*	tail,
														CrankDigraphNode*	head,
														gfloat				value	);

CrankDigraphEdge*	crank_digraph_connect_double (		CrankDigraph*		graph,
														CrankDigraphNode*	tail,
														CrankDigraphNode*	head,
														gdouble				value	);

CrankDigraphEdge*	crank_digraph_connect_pointer (		CrankDigraph*		graph,
														CrankDigraphNode*	tail,
														CrankDigraphNode*	head,
														const GType			ptype,
														gpointer			pointer	);
														
CrankDigraphEdge*	crank_digraph_connect_boxed (		CrankDigraph*		graph,
														CrankDigraphNode*	tail,
														CrankDigraphNode*	head,
														const GType			btype,
														gpointer			boxed	);
														
CrankDigraphEdge*	crank_digraph_connect_object (		CrankDigraph*		graph,
														CrankDigraphNode*	tail,
														CrankDigraphNode*	head,
														GObject*			object	);



gpointer			crank_digraph_node_get_pointer (	CrankDigraphNode*	node	);

gpointer			crank_digraph_node_get_boxed (		CrankDigraphNode*	node	);

GObject*			crank_digraph_node_get_object (		CrankDigraphNode*	node	);


gfloat				crank_digraph_edge_get_float (		CrankDigraphEdge*	edge	);

gdouble				crank_digraph_edge_get_double (		CrankDigraphEdge*	edge	);

gpointer			crank_digraph_edge_get_pointer (	CrankDigraphEdge*	edge	);

gpointer			crank_digraph_edge_get_boxed (		CrankDigraphEdge*	edge	);

GObject*			crank_digraph_edge_get_object (		CrankDigraphEdge*	edge	);


void				crank_digraph_node_set_pointer (	CrankDigraphNode*	node,
														const GType			ptype,
														gpointer			pointer	);

void				crank_digraph_node_set_boxed (		CrankDigraphNode*	node,
														const GType			btype,
														gpointer			boxed	);

void				crank_digraph_node_set_object (		CrankDigraphNode*	node,
														GObject*			object	);


void				crank_digraph_edge_set_float (		CrankDigraphEdge*	edge,
														const gfloat		value	);

void				crank_digraph_edge_set_double (		CrankDigraphEdge*	edge,
														const gdouble		value	);

void				crank_digraph_edge_set_pointer (	CrankDigraphEdge*	edge,
														const GType			ptype,
														gpointer			pointer	);

void				crank_digraph_edge_set_boxed (		CrankDigraphEdge*	edge,
														const GType			btype,
														gpointer			boxed	);

void				crank_digraph_edge_set_object (		CrankDigraphEdge*	edge,
														GObject*			object	);

G_END_DECLS

#endif /* CRANKGRAPH_H */
