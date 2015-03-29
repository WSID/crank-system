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
#include "cranktypesgraph.h"

/**
 * SECTION: cranktypesgraph
 * @short_description: 여러 타입 정보를 관리하는 그래프입니다.
 * @title: CrankTypesGraph
 * @stability: Unstable
 * @include: crankbase.h
 */


typedef struct _CrankTypesNode CrankTypesNode;
typedef struct _CrankTypesRoot CrankTypesRoot;



struct _CrankTypesNode {
	GType*				types;
	guint				ntypes;

	CrankTypesNode**	type_parent;
	CrankTypesNode**	type_children;
	CrankTypesNode**	type_prev;
	CrankTypesNode**	type_next;
	
	gpointer	data;
};

struct _CrankTypesRoot {
	guint				ntypes;
	
	CrankTypesNode**	root_nodes;
};


/**
 * CrankTypesGraph:
 *
 * 여러 타입 정보를 관리하는 그래프입니다.
 */
struct _CrankTypesGraph {
	CrankTypesRoot**	roots;
	guint				nroots;
	
	GDestroyNotify		value_destroy;
	
	guint 	_refc;
};

G_DEFINE_BOXED_TYPE (CrankTypesGraph,
		crank_types_graph,
		crank_types_graph_ref,
		crank_types_graph_unref)



/**
 * crank_types_graph_new:
 *
 * 새로운 타입 그래프를 생성합니다.
 *
 * Returns: (transfer full): 생성된 #CrankTypesGraph입니다.
 */
CrankTypesGraph*
crank_types_graph_new (void)
{
	return crank_types_graph_new_full (NULL);
}


/**
 * crank_types_graph_new:
 * @value_destroy: 값이 제거되거나 그래프가 해제될 때 값을 해제할 함수입니다.
 *
 * 새로운 타입 그래프를 생성합니다.
 *
 * Returns: (transfer full): 생성된 #CrankTypesGraph입니다.
 */
CrankTypesGraph*
crank_types_graph_new_full (GDestroyNotify value_destroy)
{
	CrankTypesGraph*	graph = g_new (CrankTypesGraph, 1);
	
	graph->roots = g_new (CrankTypesRoot*, 4);
	graph->nroots = 4;
	
	graph->value_destroy = value_destroy;
	
	graph->_refc = 1;
	
	return graph;
}

/**
 * crank_types_graph_ref:
 * @graph: 타입 그래프입니다.
 *
 * 레퍼런스 카운트를 1 증가시킵니다.
 *
 * Returns: (transfer full): 레퍼런스 카운트가 1 증가된 @graph입니다.
 */
CrankTypesGraph*
crank_types_graph_ref (CrankTypesGraph*	graph)
{
	g_atomic_int_inc (& (graph->_refc));
}

/**
 * crank_types_graph_unref:
 * @graph: 타입 그래프입니다.
 *
 * 레퍼런스 카운트를 1 감소시킵니다. 만일 레퍼런스 카운트가 0이 되면 그래프는
 * 해제됩니다.
 */
void
crank_types_graph_unref (CrankTypesGraph*	graph)
{
	if (g_atomic_int_dec_and_test (& (graph->_refc)) ) {
		g_free (graph->roots);
		g_free (graph);
	}
}


void
crank_types_graph_set ( CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length,
						gconstpointer		value	)
{
	// do nothing for now
}

gconstpointer
crank_types_graph_get ( CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length	)
{
	return NULL;
}

gboolean
crank_types_graph_has (	CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length	)
{
	return FALSE;
}

gconstpointer
crank_types_graph_lookup (	CrankTypesGraph*	graph,
							const GType*		key,
							const guint			key_length	)
{
	return NULL;
}

const GType*
crank_types_graph_lookup_types (CrankTypesGraph*	graph,
								const GType*		key,
								const guint			key_length	)
{
	return NULL;
}

gboolean
crank_types_graph_lookup_full (	CrankTypesGraph*	graph,
								const GType*		key,
								const guint			key_length,
								const GType**		key_orig,
								gpointer*			value	)
{
	*key_orig = NULL;
	*value = NULL;
	return FALSE;
}

gboolean
crank_types_graph_remove (	CrankTypesGraph*	graph,
							const GType*		key,
							const guint			key_length	)
{
	return FALSE;
}
