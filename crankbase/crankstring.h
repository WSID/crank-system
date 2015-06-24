#ifndef CRANKSTRING_H
#define CRANKSTRING_H

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
