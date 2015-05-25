#ifndef CRANKVALUE_H
#define CRANKVALUE_H

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
#error crankvalue.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

void			crank_value_overwrite_init (	GValue*			value,
								   				const GType		type	);

void			crank_value_overwrite (			GValue*			value,
							  					const GValue*	from	);

void			crank_value_overwrite_boolean (	GValue*			value,
									  			const gboolean	bool_value	);

void			crank_value_overwrite_int (		GValue*			value,
								  				const gint		int_value	);

void			crank_value_overwrite_string (	GValue*			value,
									 			const gchar*	str_value	);

void			crank_value_overwrite_object (	GValue*			value,
									 			GObject*		obj_value	);

void			crank_value_overwrite_boxed (	GValue*			value,
												const GType		value_type,
												gpointer		boxed_value	);

void			crank_value_overwrite_pointer (	GValue*			value,
												const GType		value_type,
									  			gpointer		pointer_value	);

void			crank_value_array_overwrite (	GValue*		array,
												gint		nitem,
												...	);

void			crank_value_array_overwrite_va (GValue*		array,
												gint		nitem,
												va_list		varargs	);

void			crank_value_array_overwrite_array ( GValue*	array,
												gint		nitem,
												GValue*		other	);

void			crank_value_array_unset (		GValue*		array,
												guint		narray	);

G_END_DECLS

#endif //CRANKVALUE_H
