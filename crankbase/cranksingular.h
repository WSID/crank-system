#ifndef CRANKSINGULAR_H
#define CRANKSINGULAR_H

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
#error cranksingular.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _CrankSingular				CrankSingular;
typedef struct _CrankSingularClass			CrankSingularClass;
typedef struct _CrankSingularClassPrivate	CrankSingularClassPrivate;

struct _CrankSingular {
	GObject			parent_instance;
};

struct _CrankSingularClass {
	GObjectClass				parent_class;
	CrankSingularClassPrivate*	priv;
};


#define CRANK_TYPE_SINGULAR		(crank_singular_get_type())
#define CRANK_SINGULAR(i)	\
		(G_TYPE_CHECK_INSTANCE_CAST((i), CRANK_TYPE_SINGULAR, CrankSingular))
#define CRANK_IS_SINGULAR(i)\
		(G_TYPE_CHECK_INSTANCE_TYPE((i), CRANK_TYPE_SINGULAR))
#define CRANK_SINGULAR_CLASS(c)	\
		(G_TYPE_CHECK_CLASS_CAST((c), CRANK_TYPE_SINGULAR, CrankSingularClass))
#define CRANK_IS_SINGULAR_CLASS(c) \
		(G_TYPE_CHECK_CLASS_TYPE((c), CRANK_TYPE_SINGULAR))
#define CRANK_SINGULAR_GET_CLASS(i) \
		(G_TYPE_INSTANCE_GET_CLASS((i), CRANK_TYPE_SINGULAR, CrankSingularClass))

GType crank_singular_get_type (void);


CrankSingular*	crank_singular_type_try_get	(GType	type);
void			crank_singular_type_setup	(GType	type, ...);
gboolean		crank_singular_type_teardown	(GType	type);

CrankSingular*	crank_singular_class_get		(CrankSingularClass*	c, ...);
CrankSingular*	crank_singular_class_try_get	(CrankSingularClass*	c);
void			crank_singular_class_setup		(CrankSingularClass*	c, ...);
gboolean		crank_singular_class_teardown	(CrankSingularClass*	c);


G_END_DECLS

#endif /* CRANKSINGULAR_H */
