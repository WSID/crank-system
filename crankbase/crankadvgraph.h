#ifndef CRANKADVGRAPH_H
#define CRANKADVGRAPH_H

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
