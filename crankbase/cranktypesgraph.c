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
#include "cranktypesgraph.h"

/**
 * SECTION: cranktypesgraph
 * @short_description: 여러 타입 정보를 관리하는 그래프입니다.
 * @title: CrankTypesGraph
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 타입 그래프는 여러 타입의 배열을 상관관계에 따라 그래프화 하여 이어 놓은 것
 * 입니다.
 * 이 자료 구조는 #CrankFuncHolder에서 인자들의 타입에 따라 호출을 적절한 함수로
 * 넘기기 위한 것입니다.
 *
 * # 키와 값의 형식
 *
 * #CrankTypesGraph는 #GType의 배열을 키로 사용합니다. 따라서, 배열의 포인터와
 * 길이를 넘겨주어야 합니다. 또한 반드시 crank_types_graph_lookup() (와 다른
 * 함수들)의 결과는 반드시 같은 길이의 키로 반환됩니다.
 *
 * #CrankTypesGraph에서는 값을 #GValue에 저장합니다. 이는 #GValue을 통해 값을
 * 전달하고 전달 받습니다.
 *
 * 값을 설정할 경우에는 임의의 #GValue을 전달하는 것이 가능합니다. 값을 받을
 * 경우, #GValue는 해당 타입을 받을 수 있도록 초기화 되어야 합니다.
 *
 * # 타입 배열에 대한 is-a 관계 # {#is_a}
 *
 * -A
 *   - B
 *   - C
 *     - D
 *     - E
 *
 *
 * 타입 A, B, C, D, E가 위의 상속 관계를 가질 경우, 예를 들어, 두 클래스간
 * is-a 관계는 다음과 같습니다.
 *
 *
 * - E is a A
 * - C is a A
 * - B is not a D ...
 *
 * 타입 배열간 is-a 관계는 두 개의 규칙을 만족하면 성립합니다.
 *
 * - 두 배열의 길이가 같을 것
 * - 각각의 원소가 서로 대응되는 원소에 대해 is-a 관계를 가질 것
 *
 *    예를 들면, [a, b] is a [c, d]가 되기 위해서는 a is a c, b is a d가 되어야
 *    합니다.
 *
 * 따라서 이 예에서는 다음의 관계가 성립합니다.
 *
 * - [A] is not a [A, A]
 * - [D, E] is a [A, C]
 * - [C, E] is not a [E, C]
 * - ...
 *
 * 타입 그래프는 여러 개의 타입을 가지는 배열을 관리합니다. 따라서 하나의 타입
 * 배열은 여러 개의 타입 배열에 대해 is-a 관계를 가질 수 있습니다. 만일 이러한
 * 경우가 발생하는 경우 #CrankTypesGraph는 가장 구체적인 타입 배열에 대한 값으로
 * 조회합니다. 
 */

//////// 내부 전용 구조체 선언부 ///////////////////////////////////////////////

typedef struct _CrankTypesNode		CrankTypesNode;
typedef struct _CrankTypesRoot		CrankTypesRoot;
typedef struct _CrankTypesNodeAdd	CrankTypesNodeAdd;

static G_GNUC_MALLOC
gchar*				crank_typestring (				const GType*	types,
													const guint		ntypes	);

static
gboolean			crank_types_is_a (				const GType*	types_a,
													const GType*	types_b,
													const guint		ntypes	);

//////// CrankTypesNode

static G_GNUC_MALLOC
CrankTypesNode*		crank_types_node_new (			const GType*	types,
													const guint		ntypes	);
													
static inline
CrankTypesNode*		crank_types_node_ref (			CrankTypesNode* node	);

static inline
void				crank_types_node_unref (		CrankTypesNode* node	);
													
static G_GNUC_MALLOC
gchar*				crank_types_node_typestring (	CrankTypesNode*	node	);

static
gboolean			crank_types_node_add (			CrankTypesNode* parent,
													CrankTypesNode* node	);
static
CrankTypesNode*		crank_types_node_get (			CrankTypesNode* parent,
													const GType*	key,
													const guint		key_length	);
static
gboolean			crank_types_node_lookup (		CrankTypesNode* parent,
													const GType*	key,
													const guint		key_length,
										  			GList**			lookup_list	);
													
static inline
void				crank_types_node_parent (		CrankTypesNode* parent,
													CrankTypesNode* node		);

static inline
void				crank_types_node_unparent (		CrankTypesNode* parent,
													CrankTypesNode* node		);

//////// CrankTypesRoot

static G_GNUC_MALLOC
CrankTypesRoot*		crank_types_root_new (			const guint		ntypes	);

static
void				crank_types_root_free (			CrankTypesRoot* root	);

static
void				crank_types_root_add (			CrankTypesRoot* parent,
													CrankTypesNode* node	);
static
CrankTypesNode*		crank_types_root_get (			CrankTypesRoot* parent,
													const GType*	key,
													const guint		key_length	);
static
GList*				crank_types_root_lookup (		CrankTypesRoot* parent,
													const GType*	key,
													const guint		key_length	);
													
static
void				crank_types_root_remove (		CrankTypesRoot*	parent,
													CrankTypesNode* node		);


//////// 내부 전용 구조체 구현부 ///////////////////////////////////////////////

struct _CrankTypesNode {
	GType*				types;
	guint				ntypes;
	
	guint				types_depth;

	GPtrArray*			parent_nodes;
	GPtrArray*			child_nodes;
	
	GValue				value;
	
	guint				_refc;
};

struct _CrankTypesRoot {
	guint				ntypes;
	
	GPtrArray*			child_nodes;
};

//////// CrankTypesNode

/*
 * crank_typestring:
 * @types: (array length=ntypes): #GType 배열입니다.
 * @ntypes: @types 배열의 길이입니다.
 *
 * 타입들을 문자열로 표현해야 할 경우 사용됩니다. 주로 디버깅 스트링으로 내부적
 * 노드를 표현할 때 사용합니다.
 *
 * Returns: 타입 이름을 콤마로 구분한 문자열입니다.
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
 * @types: (array length=ntypes): #GType 배열입니다.
 * @types_is_a: (array length=types): #GType 배열입니다.
 * @ntypes: 두 배열의 길이입니다.
 *
 * @types과 @types_is_a가 is-a관계인지 확인합니다. 노드를 삽입할
 * 때 사용합니다.
 *
 * Returns: @types가 @types_is_a와 is-a관계인지 확인합니다.
 */
static gboolean
crank_types_is_a	(	const GType*	types,
						const GType*	types_is_a,
						const guint		ntypes	)
{
	guint i;
	
	for (i = 0; i < ntypes; i++) {
		if (! g_type_is_a(types[i], types_is_a[i])) return FALSE;
	}
	return TRUE;
}

static CrankTypesNode*
crank_types_node_new (	const GType* types, const guint ntypes )
{
	CrankTypesNode* node = g_new (CrankTypesNode, 1);
	
	node->types = CRANK_ARRAY_DUP (types, GType, ntypes);
	node->ntypes = ntypes;
	
	node->types_depth = 0;
	CRANK_FOREACH_ARRAY_DO(node->types, GType, type, node->ntypes, {
		node->types_depth += g_type_depth (type);
	})
		
	node->parent_nodes = g_ptr_array_new ();
	node->child_nodes = g_ptr_array_new_with_free_func (
			(GDestroyNotify)crank_types_node_unref);
	
	memset (&node->value, 0, sizeof(GValue));
	
	node->_refc = 0;
	
	return node;
}

static inline CrankTypesNode*
crank_types_node_ref (	CrankTypesNode* node	)
{
	g_atomic_int_inc(&node->_refc);
	return node;
}

static inline void
crank_types_node_unref ( CrankTypesNode* node	)
{
	if (g_atomic_int_dec_and_test(&node->_refc)) {
		g_value_unset (&node->value);
	
		g_ptr_array_free (node->parent_nodes, TRUE);
		g_ptr_array_free (node->child_nodes, TRUE);
	
		g_free (node->types);
	
		g_free (node);
	}
}

static G_GNUC_MALLOC gchar*
crank_types_node_typestring (	CrankTypesNode*	node	)
{
	return crank_typestring (node->types, node->ntypes);
}

static gboolean
crank_types_node_add (	CrankTypesNode* parent,
						CrankTypesNode*	node	)
{
	// 먼저 하위 노드에 속하는지 확인합니다.
	if (crank_types_is_a (node->types, parent->types, node->ntypes)) {
		gboolean add_to_subnode = FALSE;
	
		// 자손과 연결되는지 확인합니다.
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (parent->child_nodes, CrankTypesNode*, sub)
			if (crank_types_node_add (sub, node)) {
				add_to_subnode = TRUE;
			}
		CRANK_FOREACH_G_PTR_ARRAY_END
		
		// 부모와 연결합니다.
		if (! add_to_subnode) {
			// node의 하위에 해당하는 항목들은 node에 연결합니다..
			CRANK_FOREACH_G_PTR_ARRAY_BEGIN (parent->child_nodes, CrankTypesNode*, sub)
		
				if (crank_types_is_a(sub->types, node->types, node->ntypes)) {
					crank_types_node_unparent (parent, sub);
					crank_types_node_parent (node, sub);
				}

			CRANK_FOREACH_G_PTR_ARRAY_END

			crank_types_node_parent (parent, node);
		}
		
		return TRUE;
	}

	else return FALSE;
}

static CrankTypesNode*
crank_types_node_get (	CrankTypesNode* parent,
						const GType*	key,
						const guint		key_length	)
{
	CrankTypesNode*	result;

	if (CRANK_ARRAY_CMP (parent->types, key, GType, key_length) == 0) {
		return parent;
	}
	
	else if (crank_types_is_a (key, parent->types, key_length)) {	
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (parent->child_nodes, CrankTypesNode*, sub)
			result = crank_types_node_get (sub, key, key_length);
			if (result != NULL) return result;
		CRANK_FOREACH_ARRAY_END
	}
	
	return NULL;
}

static gboolean
crank_types_node_lookup (	CrankTypesNode* parent,
							const GType*	key,
							const guint		key_length,
						 	GList**			lookup_list	)
{
	if (CRANK_ARRAY_CMP (parent->types, key, GType, key_length) == 0) {
		if (g_list_find(*lookup_list, parent) == NULL) {
			*lookup_list = g_list_prepend (*lookup_list, parent);
			return TRUE;
		}
	}

	else if (crank_types_is_a (key, parent->types, key_length)) {
		gboolean	list_added = FALSE;

		CRANK_FOREACH_G_PTR_ARRAY_BEGIN (parent->child_nodes, CrankTypesNode*, sub)
			list_added =
					list_added ||
					crank_types_node_lookup (sub, key, key_length, lookup_list);
		CRANK_FOREACH_ARRAY_END
		
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

static inline void
crank_types_node_parent (	CrankTypesNode*	parent,
							CrankTypesNode* node	)
{
	g_ptr_array_add (node->parent_nodes, parent);
	g_ptr_array_add (parent->child_nodes, crank_types_node_ref (node));
}

static inline void
crank_types_node_unparent (	CrankTypesNode*	parent,
							CrankTypesNode*	node	)
{
	g_ptr_array_remove (node->parent_nodes, parent);
	g_ptr_array_remove (parent->child_nodes, node);
}

//////// CrankTypesRoot

static CrankTypesRoot*
crank_types_root_new (	const guint ntypes )
{
	CrankTypesRoot* root = g_new (CrankTypesRoot, 1);
	
	root->ntypes = ntypes;
	root->child_nodes = g_ptr_array_new_with_free_func (
			(GDestroyNotify)crank_types_node_unref);
	
	return root;
}

void
crank_types_root_free ( CrankTypesRoot* root )
{
	g_ptr_array_free (root->child_nodes, TRUE);
	g_free (root);
}

void
crank_types_root_add ( 	CrankTypesRoot* root,
						CrankTypesNode* node 	)
{
	gboolean has_parent_node = FALSE;
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (root->child_nodes, CrankTypesNode*, sub)

		if (crank_types_node_add (sub, node)) has_parent_node = TRUE;

	CRANK_FOREACH_G_PTR_ARRAY_END

	if (! has_parent_node)
		g_ptr_array_add (root->child_nodes, crank_types_node_ref (node));
}


static CrankTypesNode*
crank_types_root_get (	CrankTypesRoot* parent,
						const GType*	key,
						const guint		key_length	)
{
	CrankTypesNode*	result = NULL;
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (parent->child_nodes, CrankTypesNode*, sub)
		result = crank_types_node_get (sub, key, key_length);
		if (result != NULL) return result;
	CRANK_FOREACH_ARRAY_END
	
	return NULL;
}

static GList*
crank_types_root_lookup (	CrankTypesRoot* parent,
							const GType*	key,
							const guint		key_length	)
{
	GList*	result = NULL;

	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (parent->child_nodes, CrankTypesNode*, sub)
		crank_types_node_lookup (sub, key, key_length, &result);
	CRANK_FOREACH_ARRAY_END
	return result;
}

static void
crank_types_root_remove (	CrankTypesRoot*	root,
							CrankTypesNode*	node	)
{
	gboolean is_node_root;

	is_node_root = (node->parent_nodes->len == 0);
	
	crank_types_node_ref (node);
				
	// 먼저 하위 노드로부터 연결을 끊습니다.
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN(node->child_nodes, CrankTypesNode*, subnode)
		g_ptr_array_remove (subnode->parent_nodes, node);
		
		if (subnode->parent_nodes->len == 0) {
		
			if (! is_node_root) {
				CRANK_FOREACH_G_PTR_ARRAY_BEGIN(node->parent_nodes, CrankTypesNode*, pnode)
					crank_types_node_parent (pnode, subnode);
				CRANK_FOREACH_G_PTR_ARRAY_END
			}
			
			else {
				g_ptr_array_add (root->child_nodes, subnode);
			}
			
		}
	CRANK_FOREACH_G_PTR_ARRAY_END
	
			
	if (! is_node_root) {
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN(node->parent_nodes, CrankTypesNode*, pnode)
			g_ptr_array_remove (pnode->child_nodes, node);
		CRANK_FOREACH_G_PTR_ARRAY_END
	}
	else {
		g_ptr_array_remove (root->child_nodes, node);
	}
}

////////// 선언부 //////////////////////////////////////////////////////////////

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

static
CrankTypesRoot*		crank_types_graph_get_root (		CrankTypesGraph*	graph,
														const guint			key_length	);

static
CrankTypesNode*		crank_types_graph_lookup_node (		CrankTypesGraph*	graph,
														const GType*		key,
														const guint			key_length	);




//////// 구현부 ////////////////////////////////////////////////////////////////


//////// 내부 전용 함수

static CrankTypesRoot*
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
		graph->roots = g_renew (CrankTypesRoot*, graph->roots, graph->nroots);
		for (i = root_len; i < graph->nroots; i++)
			graph->roots[i] = NULL;
	}

	if (graph->roots[key_length] == NULL)
		graph->roots[key_length] = crank_types_root_new (key_length);

	return graph->roots[key_length];
}

static CrankTypesNode*
crank_types_graph_lookup_node (	CrankTypesGraph*	graph,
							  	const GType*		key,
							  	const guint			key_length	)
{
	// For future, more way to pick one from candidates.
	//TODO: 픽 방식을 정할 수 있도록 합니다.
	
	CrankTypesRoot* root;
	CrankTypesNode*	node = NULL;
  	GList*			lookup_list;

	root = crank_types_graph_get_root (graph, key_length);
	lookup_list = crank_types_root_lookup (root, key, key_length);

  	if (lookup_list != NULL) {
		GList* i;
	  	guint	depth_max = 0;
	 	guint	depth;

	  	for (i = lookup_list; i != NULL; i = i->next) {
	  		depth = ((CrankTypesNode*) i->data)->types_depth;
	  		
	  		if (depth_max < depth) {
				depth_max = depth;
		  		node = (CrankTypesNode*)i->data;
			}
		}
	}
	
  	return node;
}

//////// 외부 공개 함수들

/**
 * crank_types_graph_new: (constructor)
 *
 * 새로운 타입 그래프를 생성합니다.
 *
 * Returns: (transfer full): 생성된 #CrankTypesGraph입니다.
 */
CrankTypesGraph*
crank_types_graph_new (void)
{
	CrankTypesGraph*	graph = g_new (CrankTypesGraph, 1);
	
	graph->roots = g_new0 (CrankTypesRoot*, 4);
	graph->nroots = 4;
	
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
  	return graph;
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
		CRANK_FOREACH_ARRAY_BEGIN (graph->roots, CrankTypesRoot*, root, graph->nroots)
			if (root != NULL) crank_types_root_free (root);
		CRANK_FOREACH_ARRAY_END
	
		g_free (graph->roots);
		g_free (graph);
	}
}

/**
 * crank_types_graph_set:
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 값을 설정하고자 하는 키입니다.
 * @key_length: 값을 설정하고자 하는 키의 길이입니다.
 * @value: 값입니다.
 *
 * 타입 그래프에서 키에 대한 값을 설정합니다.
 */
void
crank_types_graph_set ( CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length,
						const GValue*		value	)
{
	CrankTypesRoot* root;
	CrankTypesNode*	node;
	
	root = crank_types_graph_get_root (graph, key_length);
	node = crank_types_root_get (root, key, key_length);
	
	if (node == NULL) {
		node = crank_types_node_new (key, key_length);
		crank_types_root_add (root, node);
	}
  	crank_value_overwrite (&node->value, value);
}

/**
 * crank_types_graph_get:
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 값을 얻고자 하는 키입니다.
 * @key_length: 값을 얻고자 하는 키의 길이입니다.
 * @value: 값이 저장되는 곳입니다.
 *    해당 값의 타입으로 초기화 되어 있어야 합니다.
 *
 * 타입 그래프에서 키에 대한 값을 얻어옵니다. 만일 [is-a][is_a] 관계로 조회해야
 * 할 경우, crank_types_graph_lookup()으로 조회해야 합니다.
 *
 * Returns: 해당 키가 존재하지 않으면 %FALSE입니다.
 */
gboolean
crank_types_graph_get ( CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length,
						GValue*				value	)
{
	CrankTypesRoot* root;
	CrankTypesNode*	node;
	
	root = crank_types_graph_get_root (graph, key_length);
	node = crank_types_root_get (root, key, key_length);
	
	if (node != NULL) {
		g_value_copy(&node->value, value);
		return TRUE;
	}
	return FALSE;
}

/**
 * crank_types_graph_has:
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 조회하고자 하는 키입니다.
 * @key_length: 조회하고자 하는 키의 길이입니다.
 *
 * 타입 그래프에서 해당 키가 존재하는지 확인합니다. 만일 [is-a][is_a] 관계로
 * 조회해야 할 경우, crank_types_graph_lookup_types()로 확인 가능합니다.
 *
 * Returns: 해당 키가 존재하지 않으면 %FALSE입니다.
 */
gboolean
crank_types_graph_has (	CrankTypesGraph*	graph,
						const GType*		key,
						const guint			key_length	)
{
	CrankTypesRoot* root;
	CrankTypesNode*	node;
	
	root = crank_types_graph_get_root (graph, key_length);
	node = crank_types_root_get (root, key, key_length);
	
	return node != NULL;
}

/**
 * crank_types_graph_lookup:
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 조회하고자 하는 키입니다.
 * @key_length: 조회하고자 하는 키의 길이입니다.
 * @value: 값이 저장되는 곳입니다.
 *    해당 값의 타입으로 초기화 되어 있어야 합니다.
 *
 * 타입 그래프에서 키에 해당하는 값을 얻습니다. 키가 존재하지 않더라도,
 * [is-a](#is_a) 관계가 만족되는 키에서 값을 얻어오게 됩니다.
 *
 * Returns: 해당 키가 존재하지 않으면 %FALSE입니다.
 */
gboolean
crank_types_graph_lookup (	CrankTypesGraph*	graph,
							const GType*		key,
							const guint			key_length,
							GValue*				value	)
{
	CrankTypesNode*	node = crank_types_graph_lookup_node (
			graph, key, key_length );
	
	if (node != NULL) {
		g_value_copy(&node->value, value);
		return TRUE;
	}
	return node != NULL;
}


/**
 * crank_types_graph_lookup_types:
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 조회하고자 하는 키입니다.
 * @key_length: 조회하고자 하는 키의 길이입니다.
 *
 * 타입 그래프에서 등록된 키 중에서 주어진 키와 [is-a][is_a] 관계를 맺고 있는
 * 키를 얻습니다.
 *
 * 이는 키의 존재를 확인할 때에도 사용 가능합니다.
 *
 * Returns: (array length=key_length): 해당 @key에 대응되는 원래 키입니다.
 */
const GType*
crank_types_graph_lookup_types (CrankTypesGraph*	graph,
								const GType*		key,
								const guint			key_length	)
{
	CrankTypesNode*	node = crank_types_graph_lookup_node (
			graph, key, key_length );
	
	return (node != NULL) ? node->types : NULL;
}

/**
 * crank_types_graph_lookup_full:
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 조회하고자 하는 키입니다.
 * @key_length: 조회하고자 하는 키의 길이입니다.
 * @key_orig: (out) (array length=key_length) (transfer none): 키의 원래 키입니다.
 * @value: 값입니다.
 *
 * 타입 그래프에서 키에 해당하는 원래 키와 값을 얻습니다.
 *
 * Returns: 해당 키가 존재하지 않으면 %FALSE입니다.
 */
gboolean
crank_types_graph_lookup_full (	CrankTypesGraph*	graph,
								const GType*		key,
								const guint			key_length,
								GType**				key_orig,
								GValue*				value	)
{
	CrankTypesNode* node = crank_types_graph_lookup_node (
			graph, key, key_length );
	
	if (node != NULL) {
		g_value_copy (&node->value, value);
		*key_orig = node->types;
	}
	
	return node != NULL;
}

/**
 * crank_types_graph_remove:
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 제거하고자 하는 키입니다.
 * @key_length: 제거하고자 하는 키의 길이입니다.
 *
 * 타입 그래프에서 주어진 키를 제거합니다. 키의 [is-a](#id-1.2.4.7.3) 관계는
 * 고려되지 않습니다.
 *
 * Returns: 해당 키가 존재하여, 제거되었으면 %TRUE입니다.
 */
gboolean
crank_types_graph_remove (	CrankTypesGraph*	graph,
							const GType*		key,
							const guint			key_length	)
{
	CrankTypesRoot* root;
	CrankTypesNode*	node;
	
	root = crank_types_graph_get_root (graph, key_length);
	node = crank_types_root_get (root, key, key_length);
	
	if (node != NULL) {
		crank_types_root_remove (root, node);
		return TRUE;
	}
	
	return FALSE;
}



/**
 * crank_types_graph_gir_lookup_types: (rename-to crank_types_graph_lookup_types)
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 조회하고자 하는 키입니다.
 * @key_length: 조회하고자 하는 키의 길이입니다.
 * @ret_length: @key_length의 값을 복사할 위치입니다.
 *
 * 타입 그래프에서 등록된 키 중에서 주어진 키와 [is-a][is_a] 관계를 맺고 있는
 * 키를 얻습니다.
 *
 * 이 함수는 반환되는 배열의 길이를 명시적으로 반환하여, pyGObject, Vala 등에서
 * 문제를 일으키지 않고 사용할 수 있도록 만들어졌습니다.
 *
 * Returns: (array length=ret_length): 해당 @key에 대응되는 원래 키입니다.
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
 * @graph: 타입 그래프입니다.
 * @key: (array length=key_length): 조회하고자 하는 키입니다.
 * @key_length: 조회하고자 하는 키의 길이입니다.
 * @key_orig: (out) (array length=ret_length) (transfer none): 키의 원래 키입니다.
 * @ret_length: (out): @key_length의 값이 복사될 위치입니다.
 * @value: 값입니다.
 *
 * 타입 그래프에서 주어진 키에 해당하는 원래 키와 값을 얻습니다.
 *
 * 이 함수는 반환되는 배열의 길이를 명시적으로 반환하여, pyGObject, Vala 등에서
 * 문제를 일으키지 않고 사용할 수 있도록 만들어졌습니다.
 *
 * Returns: 해당 키가 존재하지 않으면 %FALSE입니다.
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
 * @graph: 타입 그래프입니다.
 *
 * 타입 그래프에서 키의 길이들을 모두 구합니다.
 *
 * 예를 들면, ([int], [float], [int, float])에 대해서 1과 2를 반환합니다.
 *
 * Returns: (element-type gint) (transfer container): 키의 길이들입니다.
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


/**
 * crank_types_graph_get_keys_by_length:
 * @graph: 타입 그래프입니다.
 * @length: 키들의 길이입니다.
 *
 * 타입 그래프에서 주어진 길이에 해당하는 키들을 모두 구합니다.
 *
 * Returns: (element-type GType*) (transfer container): 키들입니다.
 */
GList*
crank_types_graph_get_keys_by_length (	CrankTypesGraph*	graph,
										const guint			length	)
{
	GList*	keys = NULL;
	GQueue*		queue;
	GHashTable*	set;
	CrankTypesRoot*	root;
	
	queue = g_queue_new ();
	set = g_hash_table_new (g_direct_hash, g_direct_equal);
	
	if (graph->nroots <= length) return NULL;
	
	root = graph->roots[length];
	if (root == NULL) return NULL;
	
	// broad-first iteration을 수행합니다.
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (root->child_nodes, CrankTypesNode*, node)
		g_queue_push_tail (queue, node);
		g_hash_table_add (set, node);
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	while (! g_queue_is_empty (queue)) {
		CrankTypesNode* node = (CrankTypesNode*) g_queue_pop_head (queue);
		
		keys = g_list_append (keys, node->types);
		
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN(node->child_nodes, CrankTypesNode*, child)
			if (! g_hash_table_contains (set, child)) {
				g_queue_push_tail (queue, child);
				g_hash_table_add (set, child);
			}
		CRANK_FOREACH_G_PTR_ARRAY_END
	}
	
	return keys;
}



/**
 * crank_types_graph_get_values_by_length:
 * @graph: 타입 그래프입니다.
 * @length: 키들의 길이입니다.
 *
 * 타입 그래프에서 주어진 길이에 해당하는 키에 대응하는 값들을 모두 구합니다.
 *
 * Returns: (element-type GValue) (transfer container): 값들입니다.
 */
GList*
crank_types_graph_get_values_by_length (	CrankTypesGraph*	graph,
											const guint			length	)
{
	GList*	values = NULL;
	GQueue*		queue;
	GHashTable*	set;
	CrankTypesRoot*	root;
	
	queue = g_queue_new ();
	set = g_hash_table_new (g_direct_hash, g_direct_equal);
	
	if (graph->nroots <= length) return NULL;
	
	root = graph->roots[length];
	if (root == NULL) return NULL;
	
	// broad-first iteration을 수행합니다.
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN (root->child_nodes, CrankTypesNode*, node)
		g_queue_push_tail (queue, node);
		g_hash_table_add (set, node);
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	while (! g_queue_is_empty (queue)) {
		CrankTypesNode* node = (CrankTypesNode*) g_queue_pop_head (queue);
		
		values = g_list_append (values, &node->value);
		
		CRANK_FOREACH_G_PTR_ARRAY_BEGIN(node->child_nodes, CrankTypesNode*, child)
			if (! g_hash_table_contains (set, child)) {
				g_queue_push_tail (queue, child);
				g_hash_table_add (set, child);
			}
		CRANK_FOREACH_G_PTR_ARRAY_END
	}
	
	return values;
}
