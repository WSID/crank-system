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

#include <string.h>

#include <glib.h>
#include <glib-object.h>

#define _CRANKBASE_INSIDE
#include "crankstring.h"

/**
 * SECTION: crankstring
 * @title: 문자열 조작 함수들
 * @short_description: 문자열 조작을 위한 유틸리티 함수들
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 간단히 문자열을 조작하거나 읽어들이기 위한 함수 모음입니다.
 *
 * Parsing 등과 같은 복잡한 문자열 관련 기능은 해당 기능을 제공하는
 * 라이브러리에서 수행해야 합니다.
 * 
 * python등과 같은 언어에서는 되도록이면 해당 언어에서 제공하는 기능을 사용하는
 * 것이 좋습니다.
 *
 * # 문자열 읽어들이기
 *
 * crankbase.h는 문자열을 읽어들이고 값을 간단히 읽어올 수 있는 함수들을 가지고
 * 있습니다. 현재 문자열을 읽어들이는 함수는 3개로 구분되어 있습니다.
 *
 *
 * 1. read 계열
 *
 *    이 함수들은 문자열을 주어진 위치에서 읽어들입니다. read 계열과 scan 계열은
 *    처리를 위해 gboolean을 반환하며, 실질적인 값은 out parameter를 통해 전달
 *    됩니다.
 *    <programlisting language="C">
 *        gboolean		read_[something] (	const gchar* str,
 *        									guint* pos,
 *        									something* stn [, 함수별 추가 항목]);
 *    </programlisting>
 *
 *    이에 다음과 같이 사용 가능합니다.
 *    |[ <!-- language="C" -->
 *        crank_str_read_space (str, &i, NULL);
 *        if (! crank_str_read_word (str, &i, &word_a)) return NULL;
 *        
 *        crank_str_read_space (str, &i, NULL);
 *        if (! crank_str_read_word (str, &i, &word_b)) {
 *            g_free (word_a);
 *            return NULL;
 *        }
 *        ....
 *    ]|
 *
 * 2. scan 계열
 *
 *    이 함수들은 문자열을 공백을 건너뛰고 읽어들입니다. 공백 처리를 생략하므로
 *    crank_str_read_space()를 생략할 수 있습니다. 다음의 형식으로 구성되어
 *    있습니다.
 *    <programlisting language="C">
 *        gboolean		scan_[something] (	const gchar* str,
 *        									guint* pos,
 *        									something* stn [, 함수별 추가 항목]);
 *    </programlisting>
 *
 *    위 항목을 다음과 같이 사용할 수 있습니다.
 *    |[ <!-- language="C" -->
 *        if (! crank_str_scan_word (str, &i, &word_a)) return NULL;
 *
 *        if (! crank_str_scan_word (str, &i, &word_b)) {
 *            g_free (word_a);
 *            return NULL;
 *        }
 *        ....
 *    ]|
 *
 * 3. check 계열
 *
 *    이 함수들은 문자열에서 주어진 항목을 가지고 있는지 확인합니다. 공백 처리를
 *    생략하며, 일부 여러개를 확인하는 함수들은 #gboolean외에 다른 값을 반환할
 *    수 있습니다.
 *    다음의 형식으로 이루어져 있습니다.
 *    <programlisting language="C">
 *        gboolean		check_[something] (	const gchar* str,
 *        									guint* pos,
 *        									something stn [, 함수별 추가 항목]);
 *
 *        gint			check_[something]s (const gchar* str,
 *        									guint* pos,
 *        									something* stn,
 *        									guint nstn [, 함수별 추가 항목]);
 *
 *        ....
 *    </programlisting>
 */

/**
 * crank_str_read_space:
 * @str: 읽어들일 문자열입니다.
 * @position: (inout): 위치입니다.
 * @space: (out) (optional): 공백 기호의 개수입니다.
 *
 * 공백을 읽어들이고 @position을 공백이 아닌 위치로 옮깁니다.
 *
 * Returns: 공백이 존재하면 %TRUE입니다.
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
 * @str: 읽어들일 문자열입니다.
 * @position: (inout): 위치입니다.
 * @word_ptr: (nullable) (optional) (out): 읽어들인 단어입니다. 단어를 읽지
 * 못하면 %NULL이 저장됩니다. 저장된 단어는 g_free()로 해제하면 됩니다.
 *
 * 단어을 읽어들이고 @position을 단어가 아닌 위치로 옮깁니다.
 *
 * Returns: 단어를 읽어들였으면 %TRUE입니다.
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
 * @str: 읽어들일 문자열입니다.
 * @position: (inout): 위치입니다.
 * @word_ptr: (nullable) (optional) (out): 읽어들인 단어입니다. 단어를 읽지
 * 못하면 %NULL이 저장됩니다. 저장된 단어는 g_free()로 해제하면 됩니다.
 *
 * 단어을 읽어들이고 @position을 단어가 아닌 위치로 옮깁니다.
 * 공백은 자동으로 생략합니다.
 *
 * Returns: 단어를 읽어들였으면 %TRUE입니다.
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
 * @str: 읽어들일 문자열입니다.
 * @position: (inout): 위치입니다.
 * @char_ptr: (type gchar) (optional) (out): 읽어들인 문자입니다. 문자를 읽지
 * 못하면 '\0'이 저장됩니다.
 *
 * 문자를 읽어들이고 그 다음 위치로 이동합니다.
 * 공백은 건너 뜁니다.
 *
 * Returns: 문자를 읽어들이지 못하면 %FALSE
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
 * @str: 읽어들일 문자열입니다.
 * @position: (inout): 위치입니다.
 * @check_item: 확인할 문자입니다.
 *
 * 다음 문자가 @check_item인지 확인합니다.
 * 공백은 건너 뜁니다.
 *
 * Returns: 읽어들인 문자가 일치하지 않으면 %FALSE
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
 * @str: 읽어들일 문자열입니다.
 * @position: (inout): 위치입니다.
 * @check_items: (type gchar) (array length=ncheck_items): 확인할 문자들입니다.
 * @ncheck_items: @check_items의 길이입니다.
 *
 * 다음 문자가 @check_items 중 하나에 속해있는지 확인하고 @check_items에서의
 * 해당 인덱스를 반환합니다.
 * 공백은 건너 뜁니다.
 *
 * Returns: 읽어들인 문자가 @check_items 중에 존재하지 않으면 -1
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
 * @str: 읽어들일 문자열입니다.
 * @position: (inout): 위치입니다.
 * @check_items: 확인할 문자들입니다.
 *
 * 다음 문자가 @check_items 중 하나에 속해있는지 확인하고 @check_items에서의
 * 해당 인덱스를 반환합니다.
 * 공백은 건너 뜁니다.
 *
 * Returns: 읽어들인 문자가 @check_items 중에 존재하지 않으면 -1
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
