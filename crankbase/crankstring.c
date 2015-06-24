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

#define _CRANKBASE_INSIDE

#include <string.h>

#include <glib.h>
#include <glib-object.h>

#define _CRANKBASE_INSIDE
#include "crankstring.h"

/**
 * SECTION: crankstring
 * @title: Simple String Reading
 * @short_description: Utility for String read and manipulation.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * The functions provides simple function to read data from string.
 *
 * For complex string functions like parsing, Libraries that provides these
 * function should be consulted.
 * 
 * If possible, when using other language like python, use their own string
 * functions rather than using this functions.
 *
 * # Reading string.
 *
 * crankbase.h has simple functions to read string and retrieve their value.
 * Currently, these functions are in 3 groups.
 *
 *
 * 1. read family.
 *
 *    The function reads string in given position. read and scan families 
 *    returns gboolean for iterated processing. Actual values are returned
 *    through out parameters.
 *    |[ <-- language="C" --!>
 *        gboolean      read_[something] (  const gchar* str,
 *                                          guint* pos,
 *                                          something* stn [, 함수별 추가 항목]);
 *    ]|
 *
 *    They can be used like this.
 *    |[ <-- language="C" --!>
 *        crank_str_read_space (str, &i, NULL);
 *        if (! crank_str_read_word (str, &i, &amp;word_a)) return NULL;
 *        
 *        crank_str_read_space (str, &i, NULL);
 *        if (! crank_str_read_word (str, &i, &word_b)) {
 *            g_free (word_a);
 *            return NULL;
 *        }
 *        ....
 *    ]|
 *
 * 2. scan family.
 *
 *    These functions skips spaces before reading string. 
 *    |[ <-- language="C" --!>
 *        gboolean      scan_[something] (  const gchar* str,
 *                                          guint* pos,
 *                                          something* stn [, 함수별 추가 항목]);
 *    ]|
 *
 *    They can be used like this.
 *    |[ <-- language="C" --!>
 *        if (! crank_str_scan_word (str, &i, &word_a)) return NULL;
 *
 *        if (! crank_str_scan_word (str, &i, &word_b)) {
 *            g_free (word_a);
 *            return NULL;
 *        }
 *        ....
 *    ]|
 *
 * 3. check family
 *
 *    The functions will check that certain item is on the string. It skips
 *    spaces before reading.
 *    Some function might return other type rather than #gboolean, if it checks
 *    multiple items.
 *    |[ <-- language="C" --!>
 *        gboolean      check_[something] ( const gchar* str,
 *                                          guint* pos,
 *                                          something stn [, 함수별 추가 항목]);
 *
 *        gint          check_[something]s (const gchar* str,
 *                                          guint* pos,
 *                                          something* stn,
 *                                          guint nstn [, 함수별 추가 항목]);
 *
 *        ....
 *    ]|
 */

/**
 * crank_str_read_space:
 * @str: string to read.
 * @position: (inout): position.
 * @space: (out) (optional): count of space characters.
 *
 * Reads @str for space and moves @position into the non-space character.
 *
 * Returns: %TRUE if there is a space.
 */
gboolean
crank_str_read_space (	const gchar*		str,
						guint*				position,
						guint*				space	)
{
	guint		i_start;
	guint		i;

	i_start = *position;

	for (i = i_start; g_ascii_isspace (str[i]); i++) {}

	if (space != NULL)
		*space = i - i_start;

	*position = i;
	return (i != i_start);
}

/**
 * crank_str_read_word:
 * @str: string to read.
 * @position: (inout): position.
 * @word_ptr: (nullable) (optional) (out): Read word. If it cannot read, %NULL
 *        will be returned. free with g_free() after use.
 *
 * Reads @str and moves position into non-word character.
 *
 * Returns: %TRUE if it read a word.
 */
gboolean
crank_str_read_word (	const gchar*		str,
						guint*				position,
						gchar**				word_ptr	)
{
	guint		i_start;
	guint		i;

	guint		i_len;

	i_start = *position;

	for (i = i_start; g_ascii_isalnum (str[i]); i++) {}
	i_len = i - i_start;

	if (word_ptr != NULL)
		*word_ptr = (i_len != 0) ? g_strndup (str + i_start, i_len) : NULL;

	*position = i;
	return (i != i_start);
}

//////// Scanning Function

/**
 * crank_str_scan_word:
 * @str: String to scan.
 * @position: (inout): position.
 * @word_ptr: (nullable) (optional) (out): Scanned word. If it cannot read,
 *        %NULL will be stored. free with g_free() after use.
 *
 * Reads @str and moves position into non-word character. Skips space before
 * it reads.
 *
 * Returns: %TRUE if it read a word.
 */
gboolean
crank_str_scan_word (	const gchar*		str,
						guint*				position,
						gchar**				word_ptr	)
{
	guint	i;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	if (crank_str_read_word (str, &i, word_ptr)) {
		*position = i;
		return TRUE;
	}
	else {
		if (word_ptr != NULL) *word_ptr = NULL;
		return FALSE;
	}
}

/**
 * crank_str_scan_char:
 * @str: String to scan.
 * @position: (inout): position.
 * @char_ptr: (type gchar) (optional) (out): Scanned char. If it cannot read,
 *        '\0' will be stored.
 *
 * Reads @str and moves position into next character. Skips space before
 * it reads.
 *
 * Returns: %TRUE if it reads a non-space character.
 */
gboolean
crank_str_scan_char (	const gchar*		str,
						guint*				position,
						gchar*				char_ptr	)
{
	guint	i;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	if (char_ptr != NULL) *char_ptr = str[i];
	
	if (str[i] != '\0') {
		*position = i + 1;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//////// Checking Function

/**
 * crank_str_check_char:
 * @str: String to check.
 * @position: (inout): position.
 * @check_item: item to check.
 *
 * Checks next character is @check_item and moves @position to next if it is.
 * Skips space before it reads.
 *
 * Returns: Whether the scanned character is equal to check_item.
 */
gboolean
crank_str_check_char (	const gchar*		str,
						guint*				position,
						gchar				check_item	)
{
	guint	i;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	if (str[i] == check_item) {
		*position = i + 1;
		return TRUE;
	}
	else return FALSE;
}


/**
 * crank_str_check_chars:
 * @str: String to check.
 * @position: (inout): position.
 * @check_items: (type gchar) (array length=ncheck_items): Items to check.
 * @ncheck_items: Length of @check_items.
 *
 * Checks next character is one of @check_items, and moves @position to next if it is.
 * Skips space before it reads.
 *
 * Returns: The index of read character at @check_items, or -1 for absences.
 */
gint
crank_str_check_chars (	const gchar*		str,
						guint*				position,
						const gchar*		check_items,
						guint				ncheck_items	)
{
	guint	i;
	guint	j;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	for (j = 0; j < ncheck_items; j++) {
		if (str[i] == check_items[j]) {
			*position = i + 1;
			return j;
		}
	}

	return -1;
}


/**
 * crank_str_check_chars_str:
 * @str: String to check.
 * @position: (inout): position.
 * @check_items: Items to check.
 *
 * Checks next character is one of @check_items, and moves @position ot next if it is.
 * Skips space before it reads.
 *
 * Returns: The index of read character at @check_items, or -1 for absences
 */
gint
crank_str_check_chars_str (	const gchar*		str,
							guint*				position,
							const gchar*		check_items	)
{
	guint	i;
	guint	j;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	for (j = 0; check_items[j] != '\0'; j++) {
		if (str[i] == check_items[j]) {
			*position = i + 1;
			return j;
		}
	}

	return -1;
}
