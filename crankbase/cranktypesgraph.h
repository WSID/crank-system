#ifndef CRANKTYPESGRAPH_H
#define CRANKTYPESGRAPH_H

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
#error cranktypesgraph.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

struct _CrankTypesGraph;
typedef struct _CrankTypesGraph CrankTypesGraph;

#define CRANK_TYPE_TYPES_GRAPH (crank_types_graph_get_type ())

GType crank_types_graph_get_type (void);



G_GNUC_MALLOC
CrankTypesGraph*	crank_types_graph_new (void);

CrankTypesGraph*	crank_types_graph_ref (			CrankTypesGraph*	graph	);

void				crank_types_graph_unref (		CrankTypesGraph*	graph	);


void				crank_types_graph_set (			CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length,
													const GValue*		value	);

gboolean			crank_types_graph_get (			CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length,
													GValue*				value	);

gboolean			crank_types_graph_has (			CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length	);

gboolean			crank_types_graph_lookup (		CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length,
													GValue*				value	);

const GType*		crank_types_graph_lookup_types (CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length	);

gboolean			crank_types_graph_lookup_full (	CrankTypesGraph*	self,
													const GType*		key,
													const guint			key_length,
													GType**				key_orig,
													GValue*				value	);

gboolean			crank_types_graph_remove (		CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length	);


const GType*		crank_types_graph_gir_lookup_types (CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length,
													guint*				ret_length	);

gboolean			crank_types_graph_gir_lookup_full (	CrankTypesGraph*	self,
													const GType*		key,
													const guint			key_length,
													GType**		key_orig,
													guint*				ret_length,
													GValue*				value	);

GList*				crank_types_graph_get_key_lengths (	CrankTypesGraph*	self );

GList*				crank_types_graph_get_keys_by_length (	CrankTypesGraph*	self,
													const guint			length		);

GList*				crank_types_graph_get_values_by_length ( CrankTypesGraph*	self,
													const guint			length		);

G_END_DECLS

#endif /* CRANKTYPESGRAPH_H */
