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
 * Returns: (transfer container): 복사된 배열입니다. 사용 후 g_free()를 사용하여야 합니다. 
 */
#define CRANK_ARRAY_DUP(a, G, l) ((G*)g_memdup ((a), l * sizeof (G)))


/**
 * CRANK_FOREACH_ARRAY_BEGIN:
 * @a: 내용을 열람할 array
 * @G: 내용의 형 (type)입니다.
 * @e: 내용의 이름입니다.
 * @l: 내용의 길이입니다.
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
 * CRANK_FOREACH_VALIST_BEGIN:
 * @va: 내용을 열람할 va_list
 * @G: 내용의 형 (type) 입니다.
 * @e: 내용의 이름입니다.
 * @f: 마지막을 표시하는 값입니다.
 *
 * 주어진 va_list의 각각에 대해 loop를 시작합니다.
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
 * @va: va_list입니다.
 * @G: 타입
 * @e: 변수
 * @f: 마지막
 * @BLOCK: 실행 코드
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
 * 함수에 주어진 가변 인자 각각에 대해 loop를 시작합니다.
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

#define CRANK_FOREACH_VARARG_DO(param_last, G, e, f, BLOCK) \
	CRANK_FOREACH_VARARG_BEGIN(param_last, G, e, f) \
		BLOCK \
	CRANK_FOREACH_VARARG_END

G_END_DECLS

#endif /* CRANKBASEMACRO_H */
