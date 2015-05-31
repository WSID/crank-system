#ifndef CRANKADVGRAPH_H
#define CRANKADVGRAPH_H

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
#error crankadvgraph.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/**
 * CrankDigraphNodeFloatFunc:
 * @node: node to evaluate.
 * @userdata: (closure): userdata.
 *
 * Evaluate #CrankDigraphNode to #gfloat.
 *
 * Returns: evaluation for @node
 */
typedef	gfloat	(*CrankDigraphNodeFloatFunc)	(	CrankDigraphNode*	node,
													gpointer			userdata	);

/**
 * CrankDigraphNodeDoubleFunc:
 * @node: node to evaluate.
 * @userdata: (closure): userdata.
 *
 * Evaluate #CrankDigraphNode to #gdouble.
 *
 * Returns: evaluation for @node
 */
typedef gdouble	(*CrankDigraphNodeDoubleFunc)	(	CrankDigraphNode*	node,
													gpointer			userdata	);

/**
 * CrankDigraphEdgeFloatFunc:
 * @edge: edge to evaluate.
 * @userdata: (closure): userdata.
 *
 * Evaluate #CrankDigraphEdge to #gfloat. (For example, cost for edges.)
 *
 * Returns: evaluation for @edge
 */
typedef gfloat	(*CrankDigraphEdgeFloatFunc)	(	CrankDigraphEdge*	edge,
													gpointer			userdata	);

/**
 * CrankDigraphEdgeDoubleFunc:
 * @edge: edge to evaluate.
 * @userdata: (closure): userdata.
 *
 * Evaluate #CrankDigraphEdge to #gdouble. (For example, cost for edges.)
 *
 * Returns: evaluation for @edge
 */
typedef gdouble	(*CrankDigraphEdgeDoubleFunc)	(	CrankDigraphEdge*	edge,
													gpointer			userdata	);

/**
 * CrankDigraphHeuristicFunc:
 * @from: starting node.
 * @to: destination node.
 * @userdata: (closure): userdata.
 *
 * Estimates cost from @from to @to.
 *
 * Returns: estimation of cost between @from and @to.
 */
typedef gfloat	(*CrankDigraphHeuristicFunc)	(	CrankDigraphNode*	from,
													CrankDigraphNode*	to,
													gpointer			userdata	);





GList*		crank_dijkstra_digraph (				CrankDigraphNode*			from,
													CrankDigraphNode*			to,
													CrankDigraphEdgeFloatFunc	edge_func,
													gpointer					userdata	);

GList*		crank_astar_digraph (					CrankDigraphNode*			from,
													CrankDigraphNode*			to,
													CrankDigraphEdgeFloatFunc	edge_func,
													gpointer					edge_userdata,
													CrankDigraphHeuristicFunc	heuristic_func,
													gpointer					heuristic_userdata	);

GNode*		crank_dijkstra_full_digraph (			CrankDigraphNode*			from,
													CrankDigraphEdgeFloatFunc	edge_func,
													gpointer					userdata	);

G_END_DECLS

#endif
