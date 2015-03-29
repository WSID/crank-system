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

G_GNUC_MALLOC
CrankTypesGraph*	crank_types_graph_new_full (GDestroyNotify value_destroy);

CrankTypesGraph*	crank_types_graph_ref (			CrankTypesGraph*	graph	);

void				crank_types_graph_unref (		CrankTypesGraph*	graph	);


void				crank_types_graph_set (			CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length,
													gconstpointer		value	);

gconstpointer		crank_types_graph_get (			CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length	);

gboolean			crank_types_graph_has (			CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length	);

gconstpointer		crank_types_graph_lookup (		CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length	);

const GType*		crank_types_graph_lookup_types (CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length	);

gboolean			crank_types_graph_lookup_full (	CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length,
													const GType**		key_orig,
													gpointer*			value	);

gboolean			crank_types_graph_remove (		CrankTypesGraph*	graph,
													const GType*		key,
													const guint			key_length	);

G_END_DECLS

#endif /* CRANKTYPESGRAPH_H */
