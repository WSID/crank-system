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

/**
 * CrankReadDecResult:
 * @CRANK_READ_DEC_OVERFLOW:
 *    The type cannot hold value of large magnificent, so value will be clamped
 *    in type's possible range.
 * @CRANK_READ_DEC_UNDERFLOW:
 *    The type cannot hold value of small magnificent, so value will be parsed
 *    into 0.
 * @CRANK_READ_DEC_TRUNC_PRECISE:
 *    The type cannot hold value of precision, so that explicit truncation
 *    happens.
 * @CRANK_READ_DEC_SYMBOL:
 *    Symbol words are read instead of numbers, like "inf", or "NaN".
 *
 * This flag is used to add additional information about reading value from
 * string.
 */
typedef enum _CrankReadDecResult {
	CRANK_READ_DEC_OVERFLOW = 1 << 0,
	CRANK_READ_DEC_UNDERFLOW = 1 << 1,
	CRANK_READ_DEC_TRUNC_PRECISE = 1 << 2,
	CRANK_READ_DEC_SYMBOL = 1 << 3
} CrankReadDecResult;

/**
 * CrankStrCheckFlags:
 * @CRANK_STR_CHECK_MASK_CASE_INSENSITIVE:
 *     Mask value for case insensitive comparsion.
 * @CRANK_STR_CHECK_CI_NORMAL:
 *     Performs normal case insensitive comparsion.
 * @CRANK_STR_CHECK_CI_IN_LOWERCASE:
 *     Input items are lowercase.
 * @CRANK_STR_CHECK_CI_IN_UPPERCASE:
 *     Input items are uppercase.
 *
 * This flag is used to adjust check operations.
 */
typedef enum _CrankStrCheckFlags {
	CRANK_STR_CHECK_MASK_CASE_INSENSITIVE = 3 << 0,
	CRANK_STR_CHECK_CI_NORMAL =	   1 << 0,
	CRANK_STR_CHECK_CI_IN_LOWERCASE = 2 << 0,
	CRANK_STR_CHECK_CI_IN_UPPERCASE = 3 << 2
} CrankStrCheckFlags;

//////// Reading functions

gboolean			crank_str_read_space				(	const gchar*		str,
															guint*				position,
															guint*				space	);

gboolean			crank_str_read_word					(	const gchar*		str,
															guint*				position,
															gchar**				word_ptr	);

gboolean			crank_str_read_uint64				(	const gchar*		str,
															guint*				position,
															guint64*			uint_ptr,
															gboolean*			overflowed	);

gboolean			crank_str_read_int64				(	const gchar*		str,
															guint*				position,
															gint64*				int_ptr,
															gint*				overflowed	);

gboolean			crank_str_read_double				(	const gchar*		str,
															guint*				position,
															gdouble*			value_ptr,
															CrankReadDecResult*	read_flags	);
															

//////// Scanning Function

gboolean			crank_str_scan_word					(	const gchar*		str,
															guint*				position,
															gchar**				word_ptr	);

gboolean			crank_str_scan_char					(	const gchar*		str,
															guint*				position,
															gchar*				char_ptr	);

gboolean			crank_str_scan_uint64				(	const gchar*		str,
															guint*				position,
															guint64*			uint_ptr,
															gboolean*			overflowed	);

gboolean			crank_str_scan_int64				(	const gchar*		str,
															guint*				position,
															gint64*				int_ptr,
															gint*				overflowed	);

gboolean			crank_str_scan_double				(	const gchar*		str,
															guint*				position,
															gdouble*			value_ptr,
															CrankReadDecResult*	result		);

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

gint				crank_str_check_words				(	const gchar*		str,
															guint*				position,
															const gchar**		check_words,
															CrankStrCheckFlags	flags	);


G_END_DECLS

#endif
