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


struct _CrankSingularClass {
	/*< private >*/
	GObjectClass				parent_class;

	/*< public >*/
  	void		(*first_construct)				(CrankSingular*			self);

	/*< private >*/
	CrankSingularClassPrivate*	priv;
};


#define CRANK_TYPE_SINGULAR		(crank_singular_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSingular, crank_singular, CRANK, SINGULAR, GObject);

gboolean		crank_singular_has			(GType	type);
CrankSingular*	crank_singular_get			(GType	type);
CrankSingular*	crank_singular_peek 		(GType	type);

G_END_DECLS

#endif /* CRANKSINGULAR_H */
