#ifndef CRANKBASEMACRO_H
#define CRANKBASEMACRO_H

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
#error crankbasemacro.h cannot be included directly.
#endif

/**
 * SECTION:crankbasemacro
 * @title: Crank System 기본 매크로
 * @short_description: 기본적인 동작들을 매크로로 정의합니다.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 이 섹션에서는 Crank System 에서 쓰이는 보조적인 매크로들을 정의합니다.
 *
 * 현재 Crank System은 다음의 매크로를 제공합니다.
 *
 * - 배열 작업
 * - 간편한 반복작업
 *
 *
 * # 배열 작업
 *
 * 배열에 대한 작업을 간소하게 하기 위한 소정의 매크로를 제공합니다.
 * 
 * # 간편한 반복작업
 *
 * 특정 목록이나 배열에 대해 반복 작업을 수행해야 하는 일이 잦습니다. 이때, loop를
 * 보다 간편하게 작성할 수 있도록 도움을 줍니다. 
 *
 * 짧은 loop로 확장되는 매크로가 있는 반면 (예: #CRANK_FOREACH_VALIST_DO), 긴
 * loop를 구성할 때 처음과 끝을 표시하는 매크로도 있습니다.
 *
 * <example>
 *   <title>가변인자로 들어온 #gint들을 더합니다.</title>
 *   <programlisting language="C">
 *		gint sum (gint first, ...) {
 *			gint result = first;
 *			CRANK_FOREACH_VARARG_BEGIN (first, gint, element, 0)
 *				result += element;
 *			CRANK_FOREACH_VARARG_END
 *			return result;
 *		}
 *   </programlisting>
 * </example>
 
 * <example>
 *   <title>가변인자로 들어온 #gint들을 더합니다.</title>
 *   <programlisting language="C">
 *		gint sum (gint first, ...) {
 *			gint result = first;
 *			CRANK_FOREACH_VARARG_DO (first, gint, element, 0, {result += element;})
 *			return result;
 *		}
 *   </programlisting>
 * </example>
 */

#include <string.h>
#include <stdarg.h>
#include <glib.h>

G_BEGIN_DECLS

/**
 * CRANK_ARRAY_DUP:
 * @a: 배열입니다.
 * @G: 배열의 구성형입니다.
 * @l: 배열의 길이입니다.
 *
 * 배열을 g_memdup()을 사용하여 복사합니다.
 *
 * Returns: (transfer container): 복사된 배열입니다. 사용 후 g_free()로 해제하여야
 *  합니다.
 */
#define CRANK_ARRAY_DUP(a, G, l) ((G*)g_memdup ((a), l * sizeof (G)))

/**
 * CRANK_ARRAY_CMP:
 * @a: 배열입니다.
 * @b: 배열입니다.
 * @G: 배열의 구성형입니다.
 * @n: 배열의 갯수입니다.
 *
 * 같은 크기의 배열을 <function>memcmp</function>을 이용하여 비교합니다.
 *
 * Returns: (type gint): 비교 결과입니다.
 */
#define CRANK_ARRAY_CMP(a, b, G, n) (memcmp((a), (b), (n) * sizeof (G)))

/**
 * CRANK_ARRAY_ADD:
 * @T: 타입입니다.
 * @a: (array length=n) (type T): 값을 추가할 배열입니다.
 * @n: 배열이 가지고 있는 항목의 개수입니다. (배열의 유효한 길이)
 * @c: 배열이 할당된 길이입니다.
 * @I: (type T): 배열에 추가될 항목입니다.
 *
 * 배열에 항목을 추가합니다. 만일 배열의 개수가 할당량을 넘어가는 경우, 배열은
 * g_renew()을 통해 재 할당됩니다.
 */
#define CRANK_ARRAY_ADD(T, a, n, c, I) \
	if (n == c) { c = (c) ? (c << 1) : 1; a = g_renew(T, a, c); } a[n++] = (I)

/**
 * CRANK_FOREACH_ARRAY_BEGIN:
 * @a: (array length=l): 각 항목에 대해 loop를 반복할 배열
 * @G: 각 항목의 형 (type)입니다.
 * @e: 각 항목의 이름입니다.
 * @l: @a의 길이입니다.
 *
 * 배열의 각 항목에 대해 반복하는 loop를 구성합니다.
 *
 * #CRANK_FOREACH_ARRAY_END로 끝을 표시합니다.
 */
#define CRANK_FOREACH_ARRAY_BEGIN(a, G, e, l) \
	{   int _crank_macro_i; \
		for (_crank_macro_i = 0; _crank_macro_i < l; _crank_macro_i++) { \
		G e = a[_crank_macro_i];

/**
 * CRANK_FOREACH_ARRAY_END:
 * 
 * %CRANK_FOREACH_ARRAY_BEGIN의 끝을 표시합니다.
 */
#define CRANK_FOREACH_ARRAY_END \
	} }

/**
 * CRANK_FOREACH_ARRAY_DO:
 * @a: (array length=l): 각 항목에 대해 loop를 반복할 배열
 * @G: 각 항목의 형 (type)입니다.
 * @e: 각 항목의 이름입니다.
 * @l: @a의 길이입니다.
 * @BLOCK: 항목에 대해 반복되어 실행될 코드입니다.
 *
 * 배열에 각 항목에 대해 @BLOCK을 수행합니다.
 */
#define CRANK_FOREACH_ARRAY_DO(a, G, e, l, BLOCK) \
	CRANK_FOREACH_ARRAY_BEGIN (a, G, e, l) \
		BLOCK \
	CRANK_FOREACH_ARRAY_END



/**
 * CRANK_FOREACH_VALIST_BEGIN:
 * @va: 각 항목에 대해 loop를 반복할 va_list
 * @G: 각 항목의 형 (type) 입니다.
 * @e: 항목의 이름입니다.
 * @f: 마지막을 표시하는 값입니다.
 *
 * 주어진 <structname>va_list</structname>의 각각에 항목에 대해 반복하는 loop를
 * 구성합니다.
 *
 * #CRANK_FOREACH_VALIST_END로 끝을 표시합니다.
 */
#define CRANK_FOREACH_VALIST_BEGIN(va, G, e, f) \
    do { \
      G e = va_arg (va, G); \
      if (e == f) break;


/**
 * CRANK_FOREACH_VALIST_END:
 *
 * %CRANK_FOREACH_VALIST_BEGIN의 끝을 지정합니다.
 */
#define CRANK_FOREACH_VALIST_END \
    } while (TRUE);


/**
 * CRANK_FOREACH_VALIST_DO:
 * @va: 각 항목에 대해 loop를 반복할 va_list
 * @G: 각 항목의 형 (type) 입니다.
 * @e: 항목의 이름입니다.
 * @f: 마지막을 표시하는 값입니다.
 * @BLOCK: 항목에 대해 반복되어 실행될 코드입니다.
 *
 * 주어진 <structname>va_list</structname>의 각각 항목에 대해 @BLOCK을 수행합니다.
 */
#define CRANK_FOREACH_VALIST_DO(va, G, e, f, BLOCK) \
	CRANK_FOREACH_VALIST_BEGIN(va, G, e, f) \
		BLOCK \
	CRANK_FOREACH_VALIST_END




/**
 * CRANK_FOREACH_VARARG_BEGIN:
 * @param_last: 마지막 고정인자 이름입니다.
 * @G: 각 항목의 형 (type) 입니다.
 * @e: 각 항목의 이름입니다.
 * @f: 마지막을 표시하는 값입니다.
 *
 * 함수에 주어진 가변 인자 각각에 대해 반복하는 loop를 구성합니다.
 *
 * %CRANK_FOREACH_VARARG_END로 끝을 지정합니다.
 */
#define CRANK_FOREACH_VARARG_BEGIN(param_last, G, e, f) \
    { \
      va_list _crank_macro_varargs; \
      va_start (_crank_macro_varargs, param_last); \
      CRANK_FOREACH_VALIST_BEGIN (_crank_macro_varargs, G, e, f)

/**
 * CRANK_FOREACH_VARARG_END:
 *
 * %CRANK_FOREACH_VARARG_BEGIN의 끝을 지정합니다.
 */
#define CRANK_FOREACH_VARARG_END \
      CRANK_FOREACH_VALIST_END \
      va_end (_crank_macro_varargs); \
    }


/**
 * CRANK_FOREACH_VARARG_DO:
 * @param_last: 현재 함수의 마지막 고정 인자 이름입니다.
 * @G: 각 항목의 형 (type) 입니다.
 * @e: 각 항목의 이름입니다.
 * @f: 마지막을 표시하는 값입니다.
 * @BLOCK: 항목에 대해 반복되어 실행될 코드입니다.
 *
 * 현재 함수의 가변 인자의 각각 항목에 대해 @BLOCK을 수행합니다.
 */
#define CRANK_FOREACH_VARARG_DO(param_last, G, e, f, BLOCK) \
	CRANK_FOREACH_VARARG_BEGIN(param_last, G, e, f) \
		BLOCK \
	CRANK_FOREACH_VARARG_END


/**
 * CRANK_FOREACH_GLIST_BEGIN:
 * @l: 반복할 GList입니다.
 * @G: 각 항목의 형 (type) 입니다.
 * @e: 각 항목의 이름입니다.
 *
 * #GList에 대해 반복하는 루프의 시작을 표시합니다.
 */
#define CRANK_FOREACH_GLIST_BEGIN(l, G, e) \
	{ \
		GList*	_crank_macro_iter; 			\
		for (	_crank_macro_iter = l; 		\
				_crank_macro_iter != NULL;	\
				_crank_macro_iter = _crank_macro_iter -> next ) { \
			G	e = (G) _crank_macro_iter -> data;

/**
 * CRANK_FOREACH_GLIST_END:
 *
 * %CRANK_FOREACH_GLIST_BEGIN로 표시한 루프의 끝을 지정합니다.
 */
#define CRANK_FOREACH_GLIST_END \
		} \
	}

/**
 * CRANK_FOREACH_GLIST_DO:
 * @l: 반복할 GList입니다.
 * @G: 각 항목의 형 (type) 입니다.
 * @e: 각 항목의 이름입니다.
 * @BLOCK: 항목에 대해 반복되어 실행될 코드입니다.
 *
 * GList의 각 항목에 대해 @BLOCK을 수행합니다.
 */
#define CRANK_FOREACH_GLIST_DO(l, G, e, BLOCK) \
	CRANK_FOREACH_GLIST_BEGIN (l, G, e) \
		BLOCK \
	CRANK_FOREACH_GLIST_END


/**
 * CRANK_FOREACH_G_PTR_ARRAY_BEGIN:
 * @arr: (type GPtrArray): 내용을 수행할 #GPtrArray입니다.
 * @G: 각 항목의 형(type)입니다.
 * @e: 각 항목의 이름입니다.
 *
 * 주어진 #GPtrArray의 각 항목에 대해 루프를 수행합니다.
 *
 * 루프의 끝은 %CRANK_FOREACH_ARRAY_END로 지정합니다.
 */
#define CRANK_FOREACH_G_PTR_ARRAY_BEGIN(arr, G, e) \
	CRANK_FOREACH_ARRAY_BEGIN((arr)->pdata, gpointer, _crank_macro_ptr, (arr)->len) \
	G e = (G) _crank_macro_ptr;

/**
 * CRANK_FOREACH_G_PTR_ARRAY_END:
 *
 * %CRANK_FOREACH_G_PTR_ARRAY_BEGIN으로 시작된 루프의 끝을 지정합니다.
 */
#define CRANK_FOREACH_G_PTR_ARRAY_END \
	CRANK_FOREACH_ARRAY_END

/**
 * CRANK_FOREACH_G_PTR_ARRAY_DO:
 * @arr: (type GPtrArray): 내용을 수행할 #GPtrArray입니다.
 * @G: 각 항목의 형(type)입니다.
 * @e: 각 항목의 이름입니다.
 * @BLOCK: 항목에 대해 반복되어 실행될 코드입니다.
 *
 * 주어진 #GPtrArray의 각 항목에 대해 주어진 코드를 실행합니다.
 */
#define CRANK_FOREACH_G_PTR_ARRAY_DO(arr, G, e, BLOCK) \
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN(arr, G, e) \
		BLOCK \
	CRANK_FOREACH_G_PTR_ARRAY_END

G_END_DECLS

#endif /* CRANKBASEMACRO_H */
