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
 * @short_description: Crank System Macro 모음
 * @title: Crank System 기본 매크로
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 이 섹션에서는 Crank System 에서 쓰이는 보조적인 매크로들을 정의합니다.
 *
 * 현재 Crank System은 다음의 매크로를 제공합니다.
 *
 * - 간편한 반복작업
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
 * @G: 내용의 형 (type) 입니다.
 * @e: 내용의 이름입니다.
 * @f: 마지막을 표시하는 값입니다.
 *
 * 함수에 주어진 가변 인자 각각에 대해 반복하는 loop를 구성합니다.
 *
 * #CRANK_FOREACH_VARARG_END로 끝을 지정합니다.
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
 * @param_list: 현재 함수의 마지막 고정 인자 이름입니다.
 * @G: 각 항목의 형 (type) 입니다.
 * @e: 항목의 이름입니다.
 * @f: 마지막을 표시하는 값입니다.
 * @BLOCK: 항목에 대해 반복되어 실행될 코드입니다.
 *
 * 현재 함수의 가변 인자의 각각 항목에 대해 @BLOCK을 수행합니다.
 */
#define CRANK_FOREACH_VARARG_DO(param_last, G, e, f, BLOCK) \
	CRANK_FOREACH_VARARG_BEGIN(param_last, G, e, f) \
		BLOCK \
	CRANK_FOREACH_VARARG_END

G_END_DECLS

#endif /* CRANKBASEMACRO_H */
