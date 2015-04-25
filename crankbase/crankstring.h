#ifndef CRANKSTRING_H
#define CRANKSTRING_H

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
#error crankstring.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

//////// Reading functions

gboolean			crank_str_read_space				(	const gchar*		str,
															guint*				position,
															guint*				space	);

gboolean			crank_str_read_word					(	const gchar*		str,
															guint*				position,
															gchar**				word_ptr	);

//////// Scanning Function

gboolean			crank_str_scan_word					(	const gchar*		str,
															guint*				position,
															gchar**				word_ptr	);

gboolean			crank_str_scan_char					(	const gchar*		str,
															guint*				position,
															gchar*				char_ptr	);

//////// Checking Function

gboolean			crank_str_check_char				(	const gchar*		str,
															guint*				position,
															gchar				check_item	);

gint				crank_str_check_chars				(	const gchar*		str,
															guint*				position,
															const gchar*		check_items,
															guint				ncheck_items	);

gint				crank_str_check_chars_str			(	const gchar*		str,
															guint*				position,
															const gchar*		check_items	);

G_END_DECLS

#endif
