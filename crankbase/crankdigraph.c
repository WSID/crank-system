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

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankvalue.h"
#include "crankdigraph.h"

/**
 * SECTION: crankdigraph
 * @short_description: 유향 그래프를 나타냅니다.
 * @title:  CrankDigraph
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 이 구조체는 유향 그래프를 나타내는 구조체입니다.
 *
 * # 그래프의 구현에 대하여
 *
 * 그래프는 노드들과 그들을 이어주는 변으로 구성되어 있습니다. 다른 종류의
 * 자료구조와는 달리, 노드간 연결 관계에서도 값을 지정하는 경우가 많습니다.
 *
 * 따라서 변이 값을 가지는 다양한 사용에 대응하기 위해 변에 대해서도 구조체가
 * 정의되어 있습니다.
 *
 * 인접 리스트 방식과 비슷하게, 각 노드별로 변들의 리스트를 가집니다.
 *
 * 참조: #CrankDigraphNode, #CrankDigraphEdge
 *
 * # 그래프 노드와 변들의 라이프사이클
 *
 * 그래프 노드와 변들은 그래프에 완전히 종속적입니다. 그러한 특성으로 인해 해당
 * 구조체들의 메모리 할당 및 해제는 완전히 그래프에 의해 이루어집니다.
 *
 * 그래프 종속적인 특징에 의해 해당 구조체들의 #GType은 정의되지 않습니다.
 */

G_DEFINE_BOXED_TYPE (CrankDigraph, crank_digraph, crank_digraph_ref, crank_digraph_unref);

/**
 * CrankDigraph:
 *
 * 유향 그래프를 나타내는 자료 구조입니다. 자세한 사항은 섹션 설명을 참조하기
 * 바랍니다.
 */
struct _CrankDigraph {
	GList*	nodes;
	GList*	edges;

  	guint	_refc;
};

/**
 * CrankDigraphNode:
 *
 * 유향 그래프의 노드를 나타냅니다.
 */
struct _CrankDigraphNode {
	GValue		data;

	GList*	in_edges;
	GList*	out_edges;
};

/**
 * CrankDigraphEdge:
 *
 * 유향 그래프의 변을 나타냅니다.
 */
struct _CrankDigraphEdge {
	GValue		data;

	CrankDigraphNode*	tail;
	CrankDigraphNode*	head;
};


//////// 내부 선언부 ///////////////////////////////////////////////////////////

CrankDigraphNode*	crank_digraph_node_new (			const GValue*	data	);

void			crank_digraph_node_free (			CrankDigraphNode*	node	);

CrankDigraphEdge*	crank_digraph_edge_new (			const GValue*	data,
												CrankDigraphNode*	tail,
												CrankDigraphNode*	head		);

void			crank_digraph_edge_free (			CrankDigraphEdge*	edge	);

//////// 구현부 ////////////////////////////////////////////////////////////////

/**
 * crank_digraph_new:
 *
 * 빈 그래프를 생성합니다.
 *
 * Returns: (transfer full): 생성된 그래프입니다.
 */
CrankDigraph*
crank_digraph_new (void)
{
	CrankDigraph*	graph = g_new (CrankDigraph, 1);

  	graph->nodes = NULL;
 	graph->edges = NULL;

  	graph->_refc = 1;

 	return graph;
}

/**
 * crank_digraph_new_with_nodes:
 * @nnodes: 노드의 개수입니다.
 * @values: (array length=nnodes): 정점의 값들입니다.
 *
 * 주어진 값들을 가지고 노드를 생성하여, 그래프를 생성합니다.
 *
 * Returns: (transfer full): 생성된 그래프입니다.
 */
CrankDigraph*
crank_digraph_new_with_nodes (	const guint		nnodes,
								const GValue*	values	)
{
	CrankDigraph*	graph = crank_digraph_new ();
	guint			i;
	
	for (i = 0; i < nnodes; i ++)
		crank_digraph_add (graph, values + i);
	
	return graph;
}

/**
 * crank_digraph_new_full:
 * @nnodes: 노드의 개수입니다.
 * @values: (array length=nnodes): 정점의 값들입니다.
 * @nedges: 변의 개수입니다.
 * @edges: (array length=nedges): 변의 연결 관계와 값입니다.
 *
 * 주어진 값들을 가지고 노드를 생성합니다. 그리고 @edges의 인덱스를 이용하여
 * 변을 구성합니다.
 *
 * Returns: (transfer full): 생성된 그래프입니다.
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
		
		tail = (CrankDigraphNode*) g_list_nth_data (graph->nodes, edges[i].tail);
		head = (CrankDigraphNode*) g_list_nth_data (graph->nodes, edges[i].head);
		
		crank_digraph_connect (graph, tail, head, & edges[i].data);
	}

 	return graph;
}


/**
 * crank_digraph_ref:
 * @graph: 그래프입니다.
 *
 * 그래프의 참조를 1 증가시킵니다.
 *
 * Returns: (transfer full): 참조가 1 증가된 그래프입니다.
 */
CrankDigraph*
crank_digraph_ref (	CrankDigraph*		graph	)
{
	g_atomic_int_inc (& (graph->_refc));
	
	return graph;
}

/**
 * crank_digraph_unref:
 * @graph: (transfer full): 그래프입니다.
 *
 * 그래프의 참조를 1 감소시킵니다. 만일 참조가 0이라면, 그래프는 해제됩니다.
 */
void
crank_digraph_unref (	CrankDigraph*		graph	)
{
	if (g_atomic_int_dec_and_test (& graph->_refc)) {
		g_list_free_full (graph->nodes, (GDestroyNotify) crank_digraph_node_free);
		g_list_free_full (graph->edges, (GDestroyNotify) crank_digraph_edge_free);
		g_free (graph);
	}
}

/**
 * crank_digraph_copy:
 * @graph: 복사할 그래프입니다.
 *
 * 그래프를 복사합니다.
 *
 * Returns: (transfer full): 복사된 그래프입니다.
 */
CrankDigraph*
crank_digraph_copy (	CrankDigraph*	graph	)
{
	// Hash table은 노드-인덱스를 보관하기 위해 사용합니다.
	CrankDigraph*	clone;
	GHashTable*		table;

	clone = crank_digraph_new ();
	table = g_hash_table_new (g_direct_hash, g_direct_equal);

	CRANK_FOREACH_GLIST_BEGIN (graph->nodes, CrankDigraphNode*, node)

		g_hash_table_insert (table,
				node,
				crank_digraph_add (clone, & node->data)	);

	CRANK_FOREACH_GLIST_END

	CRANK_FOREACH_GLIST_BEGIN (graph->edges, CrankDigraphEdge*, edge)

		CrankDigraphNode*	tail;
		CrankDigraphNode*	head;

		tail = g_hash_table_lookup (table, edge->tail);
		head = g_hash_table_lookup (table, edge->head);

		crank_digraph_connect (graph, tail, head, & edge->data);

	CRANK_FOREACH_GLIST_END

	g_hash_table_unref (table);

	return clone;
}


/**
 * crank_digraph_get_nodes:
 * @graph: 그래프입니다.
 *
 * 그래프에서 노드들을 얻습니다.
 *
 * Returns: (transfer none) (element-type CrankDigraphNode): 노드들의 모음입니다.
 */
GList*
crank_digraph_get_nodes (	CrankDigraph*	graph	)
{
	return graph->nodes;
}

/**
 * crank_digraph_get_edges:
 * @graph: 그래프입니다.
 *
 * 그래프에서 변들을 얻습니다.
 *
 * Returns: (transfer none) (element-type CrankDigraphEdge): 변들의 모음입니다.
 */
GList*
crank_digraph_get_edges (	CrankDigraph*	graph	)
{
	return graph->edges;
}

/**
 * crank_digraph_depth_first:
 * @graph: 그래프입니다.
 * @start: 시작할 노드입니다.
 * @callback: (scope call): 노드마다 호출할 함수입니다.
 * @userdata: (closure): @callback의 함수입니다.
 *
 * 그래프에서 깊이 우선 반복을 수행합니다.
 *
 * @callback에서 %FALSE을 호출하여 반복을 중단할 수 있습니다.
 *
 * Returns: 반복이 중도 중단되지 않고 계속 되었는지.
 */
gboolean
crank_digraph_depth_first (	CrankDigraph*			graph,
							CrankDigraphNode*		start,
							CrankDigraphCallback	callback,
							gpointer				userdata	)
{
  	GHashTable*		set;
  	GQueue*			queue;

  	GList*				edge_list;
  	CrankDigraphEdge*	edge;
  	CrankDigraphNode*	node;

  	if (! callback (graph, start, userdata)) return FALSE;
  	if (start->out_edges == NULL) return TRUE;

	set = g_hash_table_new (g_direct_hash, g_direct_equal);
	queue = g_queue_new ();

  	g_hash_table_add (set, start);

  	edge_list = start->out_edges;
  	
	while (TRUE) {
		edge = edge_list->data;
		node = edge->head;

		// Process node.
		if (! g_hash_table_contains (set, node)){
			if (! callback (graph, node, userdata)) {
				g_hash_table_unref (set);
				g_queue_free (queue);
				return FALSE;
			}
			g_hash_table_add (set, node);

			if (node->out_edges != NULL) {
				g_queue_push_head (queue, edge_list);
				edge_list = node->out_edges;
				continue;
			}
		}

		// Pick next edge_list to process.
		edge_list = edge_list->next;
		while (edge_list == NULL) {
			if (g_queue_is_empty (queue)) {
				g_hash_table_unref (set);
				g_queue_free (queue);
				return TRUE;
			}
			edge_list = ((GList*) g_queue_pop_head (queue))->next;
		}
	}

	g_hash_table_unref (set);
	g_queue_free (queue);

	return TRUE;
}
/**
 * crank_digraph_breadth_first:
 * @graph: 그래프입니다.
 * @start: 시작할 노드입니다.
 * @callback: (scope call): 노드마다 호출할 함수입니다.
 * @userdata: (closure): @callback의 함수입니다.
 *
 * 그래프에서 넓이 우선 반복을 수행합니다.
 *
 * @callback에서 %FALSE을 호출하여 반복을 중단할 수 있습니다.
 *
 * Returns: 반복이 중도 중단되지 않고 계속 되었는지.
 */
gboolean
crank_digraph_breadth_first (	CrankDigraph*			graph,
								CrankDigraphNode*		start,
								CrankDigraphCallback	callback,
								gpointer				userdata	)
{
  	GHashTable*		set;
  	GQueue*			queue;

  	GList*				edge_list;
  	CrankDigraphNode*	node;

  	if (! callback (graph, start, userdata)) return FALSE;
  	if (start->out_edges == NULL) return TRUE;

	set = g_hash_table_new (g_direct_hash, g_direct_equal);
	queue = g_queue_new ();

  	g_hash_table_add (set, start);

  	edge_list = start->out_edges;
  	
	while (TRUE) {
		CRANK_FOREACH_GLIST_BEGIN (edge_list, CrankDigraphEdge*, edge)
			node = edge->head;

			// Process node.
			if (! g_hash_table_contains (set, node)){
				if (! callback (graph, node, userdata)) {
					g_hash_table_unref (set);
					g_queue_free (queue);
					return FALSE;
				}
				g_hash_table_add (set, node);

				if (node->out_edges != NULL) {
					g_queue_push_head (queue, edge_list);
					edge_list = node->out_edges;
					continue;
				}
			}
		CRANK_FOREACH_GLIST_END

		if (g_queue_is_empty (queue)) {
			g_hash_table_unref (set);
			g_queue_free (queue);
			return TRUE;
		}
		
		edge_list = g_queue_pop_tail (queue);
	}

	g_hash_table_unref (set);
	g_queue_free (queue);

	return TRUE;
}
/**
 * crank_digraph_add:
 * @graph: 그래프입니다.
 * @value: 노드의 값입니다.
 *
 * 그래프에서 @value를 값으로 가지는 노드를 추가합니다.
 *
 * Returns: (transfer none): 추가된 노드입니다.
 */
CrankDigraphNode*
crank_digraph_add (	CrankDigraph*		graph,
					const GValue*	value	)
{
	CrankDigraphNode* node = crank_digraph_node_new (value);
	
	graph->nodes = g_list_append (graph->nodes, node);
	
	return node;
}

/**
 * crank_digraph_remove:
 * @graph: 그래프입니다.
 * @node: 제거할 노드입니다.
 *
 * 그래프에서 노드를 제거합니다.
 */
void
crank_digraph_remove (	CrankDigraph*		graph,
						CrankDigraphNode*	node	)
{
	CRANK_FOREACH_GLIST_BEGIN (node->in_edges, CrankDigraphEdge*, e)
	
		e->tail->out_edges = g_list_remove (e->tail->out_edges, e);
		graph->edges = g_list_remove (graph->edges, e);
		crank_digraph_edge_free (e);
		
	CRANK_FOREACH_GLIST_END
	
	
	CRANK_FOREACH_GLIST_BEGIN (node->out_edges, CrankDigraphEdge*, e)
	
		e->head->in_edges = g_list_remove (e->head->in_edges, e);
		graph->edges = g_list_remove (graph->edges, e);
		crank_digraph_edge_free (e);
		
	CRANK_FOREACH_GLIST_END
	
	graph->nodes = g_list_remove (graph->nodes, node);
	
	crank_digraph_node_free (node);
}

/**
 * crank_digraph_connect:
 * @graph: 그래프입니다.
 * @tail: 변의 꼬리 노드입니다.
 * @head: 변의 머리 노드입니다.
 * @edge_value: (nullable): 변의 값입니다.
 *     NULL을 통해 값이 없는 변을 구성할 수 있습니다.
 *
 * @from과 @to를 연결하여 변을 구성합니다.
 *
 * Returns: (transfer none) (nullable):
 *        연결된 변입니다. 만일 두 변이 연결되어 있다면 NULL을 반환합니다.
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
	tail->out_edges = g_list_append (tail->out_edges, edge);
	head->in_edges = g_list_append (head->in_edges, edge);
	
	graph->edges = g_list_append (graph->edges, edge);
	
	return edge;
}

/**
 * crank_digraph_connect_void:
 * @graph: 그래프입니다.
 * @tail: 변의 꼬리 노드입니다.
 * @head: 변의 머리 노드입니다.
 *
 * @from과 @to를 연결하여 변을 구성합니다. 그래프의 연결 관계만 고려할 경우
 * 사용할 수 있습니다.
 *
 * Returns: (transfer none) (nullable):
 *        연결된 변입니다. 만일 두 변이 연결되어 있다면 NULL을 반환합니다.
 */
CrankDigraphEdge*
crank_digraph_connect_void (	CrankDigraph*		graph,
							CrankDigraphNode*	tail,
							CrankDigraphNode*	head	)
{
	return crank_digraph_connect (graph, tail, head, NULL);
}

/**
 * crank_digraph_disconnect:
 * @graph: 그래프입니다.
 * @tail: 연결을 끊을 노드입니다.
 * @head: 연결을 끊을 노드입니다.
 *
 * @from에서 @to로 이어지는 변을 찾아 연결을 끊습니다.
 *
 * Returns: @from -> @to로 이어지는 변을 제거하면 %TRUE입니다.
 */
gboolean
crank_digraph_disconnect (	CrankDigraph*		graph,
							CrankDigraphNode*	tail,
							CrankDigraphNode*	head	)
{
	CRANK_FOREACH_GLIST_BEGIN (tail->out_edges, CrankDigraphEdge*, e)
		if (e->head == head) {
			crank_digraph_disconnect_edge (graph, e);
			return TRUE;
		}
	CRANK_FOREACH_GLIST_END
	
	return FALSE;
}

/**
 * crank_digraph_disconnect_edge:
 * @graph: 그래프입니다.
 * @e: 제거할 변입니다.
 *
 * 주어진 변을 그래프에서 제거합니다.
 *
 * Note: 확실히 존재하는 변을 제거하므로 확실히 제거되었는지 확인할 필요가
 *       없습니다.
 */
void
crank_digraph_disconnect_edge (	CrankDigraph*		graph,
								CrankDigraphEdge*	e		)
{
	e->tail->out_edges = g_list_remove (e->tail->out_edges, e);
	e->head->in_edges = g_list_remove (e->head->in_edges, e);
	graph->edges = g_list_remove (graph->edges, e);
	
	crank_digraph_edge_free (e);
}







/**
 * crank_digraph_node_get_data:
 * @node: 값을 얻을 노드입니다.
 * @value: 값을 저장할 #GValue입니다.
 *
 * 값을 얻습니다. @value는 해당 값을 저장한 타입에 맞게 초기화 되어야 합니다.
 */
void
crank_digraph_node_get_data (	CrankDigraphNode*	node,
								GValue*			value	)
{
	g_value_copy (& node->data, value);
}
														
/**
 * crank_digraph_node_set_data:
 * @node: 노드입니다.
 * @value: 노드에 설정할 값입니다.
 *
 * 노드에 값을 설정합니다.
 *
 */
void
crank_digraph_node_set_data (	CrankDigraphNode*	node,
								const GValue*		value	)
{
	crank_value_overwrite (& node->data, value);
}
													
/**
 * crank_digraph_node_type_of:
 * @node: 노드입니다.
 *
 * 노드가 가지고 있는 #GValue의 타입을 얻습니다.
 *
 * Returns: 노드의 #GValue의 타입입니다.
 */
GType
crank_digraph_type_of (	CrankDigraphNode*	node	)
{
	return G_VALUE_TYPE (& node->data );
}

/**
 * crank_digraph_node_get_in_nodes:
 * @node: 노드입니다.
 *
 * 이 노드로 들어오는 변을 가진 노드들을 얻습니다.
 *
 * #GList가 매번 생성되므로, 사용이 끝나면 g_list_free() 로 해제해야 합니다.
 *
 * Returns: (transfer container) (element-type CrankDigraphNode):
 *        이 노드로 들어오는 노드들입니다.
 */
GList*
crank_digraph_node_get_in_nodes (	CrankDigraphNode*	node	)
{
	GList*	result = NULL;
	GList*	iter;
	
	for (iter = node->in_edges; iter != NULL; iter = iter->next) {
		g_message ("for edge %p:", iter->data);
		CrankDigraphEdge* edge = (CrankDigraphEdge*) (iter->data);
		result = g_list_prepend (result, edge->tail);
	}
	
	result = g_list_reverse (result);
	
	return result;
}

/**
 * crank_digraph_node_get_out_nodes:
 * @node: 노드입니다.
 *
 * 이 노드에서 나가는 변을 가진 노드들을 얻습니다.
 *
 * #GList가 매번 생성되므로, 사용이 끝나면 g_list_free() 로 해제해야 합니다.
 *
 * Returns: (transfer container) (element-type CrankDigraphNode):
 *        이 노드에서 나가는 노드들입니다.
 */
GList*
crank_digraph_node_get_out_nodes (	CrankDigraphNode*	node	)
{
	GList*	result = NULL;
	GList*	iter;
	
	for (iter = node->out_edges; iter != NULL; iter = iter->next) {
		CrankDigraphEdge* edge = (CrankDigraphEdge*) iter->data;
		result = g_list_prepend (result, edge->head);
	}
	
	result = g_list_reverse (result);
	
	return result;
}

/**
 * crank_digraph_node_get_in_edges:
 * @node: 노드입니다.
 *
 * 이 노드로 들어오는 변들을 얻습니다.
 *
 * Returns: (transfer none) (element-type CrankDigraphEdge):
 *        이 노드로 들어오는 변들입니다.
 */
GList*
crank_digraph_node_get_in_edges (	CrankDigraphNode*	node	)
{
	return node->in_edges;
}

/**
 * crank_digraph_node_get_out_edges:
 * @node: 노드입니다.
 *
 * 이 노드에서 나가는 변들을 얻습니다.
 *
 * Returns: (transfer none) (element-type CrankDigraphEdge):
 *        이 노드에서 나가는 변들입니다.
 */
GList*
crank_digraph_node_get_out_edges (	CrankDigraphNode*	node	)
{
	return node->out_edges;
}

/**
 * crank_digraph_node_get_indegree:
 * @node: 노드입니다.
 *
 * 이 노드로 들어오는 변의 개수입니다.
 *
 * Returns: 이 노드로 들어오는 변의 개수입니다.
 */
guint
crank_digraph_node_get_indegree (	CrankDigraphNode*	node	)
{
	return g_list_length (node->in_edges);
}

/**
 * crank_digraph_node_get_outdegree:
 * @node: 노드입니다.
 *
 * 이 노드에서 나가는 변의 개수입니다.
 *
 * Returns: 이 노드에서 나가는 변의 개수입니다.
 */
guint
crank_digraph_node_get_outdegree (	CrankDigraphNode*	node	)
{
	return g_list_length (node->out_edges);
}

/**
 * crank_digraph_node_is_adjacent:
 * @node: 노드입니다.
 * @other: 다른 노드입니다.
 *
 * 노드가 서로 이어져 있는지 확인합니다.
 *
 * Returns: @node에서 @other로 이어지는 변이 있는지 확인합니다.
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
 * @node: 노드입니다.
 * @other: 다른 노드입니다.
 *
 * @other가 @node로 들어오는 변을 가지는지 확인합니다.
 *
 * Returns: @other가 @node에 대해 direct predecessor 확인합니다.
 */
gboolean
crank_digraph_node_is_adjacent_from (	CrankDigraphNode*	node,
										CrankDigraphNode*	other	)
{
	CRANK_FOREACH_GLIST_BEGIN(node->in_edges, CrankDigraphEdge*, e)
		if (e->tail == other) return TRUE;
	CRANK_FOREACH_GLIST_END
	
	return FALSE;
}

/**
 * crank_digraph_node_is_adjacent_to:
 * @node: 노드입니다.
 * @other: 다른 노드입니다.
 *
 * @other가 @node에서 나오는 변을 가지는지 확인합니다.
 *
 * Returns: @other가 @node에 대해 direct successor인지 확인합니다.
 */
gboolean
crank_digraph_node_is_adjacent_to (	CrankDigraphNode*	node,
									CrankDigraphNode*	other	)
{
	CRANK_FOREACH_GLIST_BEGIN(node->out_edges, CrankDigraphEdge*, e)
		if (e->head == other) return TRUE;
	CRANK_FOREACH_GLIST_END
	
	return FALSE;
}


/**
 * crank_digraph_edge_get_data:
 * @edge: 변입니다.
 * @value: 값이 저장될 #GValue입니다. 해당하는 타입으로 미리 초기화 되어야 합니다.
 *
 * 변에서 데이터를 얻습니다.
 */
void
crank_digraph_edge_get_data (	CrankDigraphEdge*	edge,
							GValue*			value	)
{
	g_value_copy (& edge->data, value);
}

/**
 * crank_digraph_edge_set_data:
 * @edge: 변입니다.
 * @value: (nullable): 변에 설정할 값입니다.
 *
 * 변에 값을 설정합니다.
 */
void
crank_digraph_edge_set_data (	CrankDigraphEdge*	edge,
								const GValue*		value	)
{
	crank_value_overwrite (& edge->data, value);
}

/**
 * crank_digraph_edge_type_of:
 * @edge: 변입니다.
 *
 * 변의 #GValue의 타입을 얻습니다.
 *
 * Returns: 변의 #GValue의 타입입니다.
 */
GType
crank_digraph_edge_type_of (	CrankDigraphEdge*	edge	)
{
	return G_VALUE_TYPE (& edge->data);
}

/**
 * crank_digraph_edge_get_tail:
 * @edge: 변입니다.
 *
 * 변의 꼬리 노드를 얻습니다.
 *
 * Returns: (transfer none): 변의 꼬리 노드입니다.
 */
CrankDigraphNode*
crank_digraph_edge_get_tail (	CrankDigraphEdge*	edge	)
{
	return edge->tail;
}

/**
 * crank_digraph_edge_get_head:
 * @edge: 변입니다.
 *
 * 변의 머리 노드를 얻습니다.
 *
 * Returns: (transfer none): 변의 머리 노드입니다.
 */
CrankDigraphNode*
crank_digraph_edge_get_head (	CrankDigraphEdge*	edge	)
{
	return edge->head;
}



/**
 * crank_digraph_add_pointer:
 * @graph: 그래프입니다.
 * @ptype: 포인터의 GType입니다. 혹은 %G_TYPE_POINTER를 사용할 수 있습니다.
 * @pointer: 포인터입니다.
 *
 * 포인터 값을 가진 노드를 추가합니다.
 *
 * Returns: (transfer none): 추가된 노드입니다.
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
 * @graph: 그래프입니다.
 * @btype: 포인터의 GType입니다.
 * @boxed: 포인터입니다.
 *
 * 박스 값을 가진 노드를 추가합니다.
 *
 * Returns: (transfer none): 추가된 노드입니다.
 */
CrankDigraphNode*
crank_digraph_add_boxed (	CrankDigraph*	graph,
							const GType		btype,
							gpointer		boxed )
{
	GValue				value = { 0 };
	CrankDigraphNode*	node;
	
	g_value_init (&value, btype);
	g_value_set_pointer (&value, boxed);
	
	node = crank_digraph_add (graph, &value);
	
	g_value_unset (&value);
	
	return node;
}


/**
 * crank_digraph_add_object:
 * @graph: 그래프입니다.
 * @object: 객체입니다.
 *
 * 객체 값을 가진 노드를 추가합니다.
 *
 * Returns: (transfer none): 추가된 노드입니다.
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
 * crank_digraph_connect_float:
 * @graph: 그래프입니다.
 * @tail: 꼬리 노드입니다.
 * @head: 머리 노드입니다.
 * @value: 변의 값입니다.
 *
 * 단정도 부동 소수 값을 가진 변을 추가합니다.
 *
 * Returns: (transfer none): 추가된 변입니다.
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
 * @graph: 그래프입니다.
 * @tail: 꼬리 노드입니다.
 * @head: 머리 노드입니다.
 * @value: 변의 값입니다.
 *
 * 배정도 부동 소수 값을 가진 변을 추가합니다.
 *
 * Returns: (transfer none): 추가된 변입니다.
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
 * @graph: 그래프입니다.
 * @tail: 꼬리 노드입니다.
 * @head: 머리 노드입니다.
 * @ptype: 포인터의 타입입니다.
 * @pointer: 포인터입니다.
 *
 * 포인터 값을 가진 변을 추가합니다.
 *
 * Returns: (transfer none): 추가된 변입니다.
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
 * @graph: 그래프입니다.
 * @tail: 꼬리 노드입니다.
 * @head: 머리 노드입니다.
 * @btype: 박스의 타입입니다.
 * @boxed: 박스입니다.
 *
 * 박스 값을 가진 변을 추가합니다.
 *
 * Returns: (transfer none): 추가된 변입니다.
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
 * @graph: 그래프입니다.
 * @tail: 꼬리 노드입니다.
 * @head: 머리 노드입니다.
 * @object: 객체입니다.
 *
 * 객체 값을 가진 변을 추가합니다.
 *
 * Returns: (transfer none): 추가된 변입니다.
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
 * @node: 노드입니다.
 *
 * 노드로부터 포인터 값을 얻습니다.
 *
 * Returns: (transfer none): 포인터 값입니다.
 */
gpointer
crank_digraph_node_get_pointer (	CrankDigraphNode*	node	)
{
	return g_value_get_pointer (& node->data);
}

/**
 * crank_digraph_node_get_boxed:
 * @node: 노드입니다.
 *
 * 노드로부터 박스 값을 얻습니다.
 *
 * Returns: (transfer none): 박스 값입니다.
 */
gpointer
crank_digraph_node_get_boxed (	CrankDigraphNode*	node	)
{
	return g_value_get_boxed (& node->data);
}

/**
 * crank_digraph_node_get_object:
 * @node: 노드입니다.
 *
 * 노드로부터 객체 값을 얻습니다.
 *
 * Returns: (transfer none): 객체 값입니다.
 */
GObject*
crank_digraph_node_get_object (	CrankDigraphNode*	node	)
{
	return g_value_get_object (& node->data);
}



/**
 * crank_digraph_edge_get_float:
 * @edge: 변입니다.
 *
 * 변으로부터 단정도 부동 소수 값을 얻습니다.
 *
 * Returns: 변의 소수 값입니다.
 */
gfloat
crank_digraph_edge_get_float (	CrankDigraphEdge*	edge	)
{
	return g_value_get_float (& edge->data);
}

/**
 * crank_digraph_edge_get_double:
 * @edge: 변입니다.
 *
 * 변으로부터 배정도 부동 소수 값을 얻습니다.
 *
 * Returns: 변의 소수 값입니다.
 */
gdouble
crank_digraph_edge_get_double (	CrankDigraphEdge*	edge	)
{
	return g_value_get_double (& edge->data);
}

/**
 * crank_digraph_edge_get_pointer:
 * @edge: 변입니다.
 *
 * 변으로부터 포인터 값을 얻습니다.
 *
 * Returns: 변의 포인터 값입니다.
 */
gpointer
crank_digraph_edge_get_pointer (	CrankDigraphEdge*	edge	)
{
	return g_value_get_pointer (& edge->data);
}

/**
 * crank_digraph_edge_get_boxed:
 * @edge: 변입니다.
 *
 * 변으로부터 박스 값을 얻습니다.
 *
 * Returns: 변의 박스 값입니다.
 */
gpointer
crank_digraph_edge_get_boxed (	CrankDigraphEdge*	edge	)
{
	return g_value_get_boxed (& edge->data);
}

/**
 * crank_digraph_edge_get_object:
 * @edge: 변입니다.
 *
 * 변으로부터 객체 값을 얻습니다.
 *
 * Returns: 변의 객체 값입니다.
 */
GObject*
crank_digraph_edge_get_object (	CrankDigraphEdge*	edge	)
{
	return g_value_get_object (& edge->data);
}

/*
 * crank_digraph_node_new: (private)
 * @value: 값입니다.
 *
 * 새로운 노드를 생성합니다.
 */
CrankDigraphNode*
crank_digraph_node_new (	const GValue*	value	)
{
	CrankDigraphNode*	node = g_slice_new0 (CrankDigraphNode);
	
	crank_value_overwrite (& node->data, value);
	
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
 * @data: 값입니다.
 *
 * 새로운 노드를 생성합니다.
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
