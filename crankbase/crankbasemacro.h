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
 * @title: Crank System Basic Macros
 * @short_description: Defines macros for basic actinos
 * @stability: Unstable
 * @include: crankbase.h
 *
 * This section defines utility macros that used in Crank System.
 *
 * Currently, Crank System provides following macros.
 *
 * - Operations on Arrays.
 * - Iteration macros.
 *
 *
 * # Operations on Arrays.
 *
 * Macros are provided for simplified oprations involved with arrays.
 * 
 * # Iteration macros
 *
 * There are so many time to iterate over something. The macros defined here
 * helps iterate over them.
 * 
 * The macros are fall into two category.
 *
 * * BEGIN and END
 * * DO
 *
 * BEGIN and END macros are paired macro, marking start and end of loop.
 *
 * DO macro receives BLOCK parameter so it expands a loop that executes BLOCK.
 *
 * <example>
 *   <title>Getting sum of #gint from variadic arguments.</title>
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
 *   <title>Getting sum of #gint from variadic arguments.</title>
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
 * @a: Array to duplicate.
 * @G: Type of elements.
 * @l: Length of @a.
 *
 * Duplicates an array using g_memdup().
 *
 * Returns: (transfer container): Copied array. Free by g_free() after use.
 */
#define CRANK_ARRAY_DUP(a, G, l) ((G*)g_memdup ((a), l * sizeof (G)))

/**
 * CRANK_ARRAY_CMP:
 * @a: Array to compare.
 * @b: Array to compare.
 * @G: Type of elements.
 * @n: Length of @a and @b.
 *
 * Compares same sized array using <function>memcmp</function>.
 *
 * Returns: (type gint): Comparsion result.
 */
#define CRANK_ARRAY_CMP(a, b, G, n) (memcmp((a), (b), (n) * sizeof (G)))

/**
 * CRANK_ARRAY_ADD:
 * @T: Type of array.
 * @a: (array length=n): Array to add element.
 * @n: Item count of @a. (Valid length of @a)
 * @c: allocated length of @a.
 * @I: (type T): Item to append.
 *
 * Note:
 * #GArray and #GPtrArray provides more convinient functions and macros to
 * manipulate. You are advised to use them, rather than using triplet of pointer,
 * length, alloc-size.
 *
 * Append item in array. If allocation size is sufficient, then reallocates
 * array by g_renew()
 */
#define CRANK_ARRAY_ADD(T, a, n, c, I) \
	if (n == c) { c = (c) ? (c << 1) : 1; a = g_renew(T, a, c); } a[n++] = (I)

/**
 * CRANK_FOREACH_ARRAY_BEGIN:
 * @a: (array length=l): Array to iterate over.
 * @G: Type of elements.
 * @e: name of iteration variable (element).
 * @l: length of @a.
 *
 * Marks begin of loop that iterate over an array.
 *
 * Mark end with #CRANK_FOREACH_ARRAY_END
 */
#define CRANK_FOREACH_ARRAY_BEGIN(a, G, e, l) \
	{   int _crank_macro_i; \
		for (_crank_macro_i = 0; _crank_macro_i < l; _crank_macro_i++) { \
		G e = a[_crank_macro_i];

/**
 * CRANK_FOREACH_ARRAY_END:
 * 
 * Marks end of loop from %CRANK_FOREACH_ARRAY_BEGIN
 */
#define CRANK_FOREACH_ARRAY_END \
	} }

/**
 * CRANK_FOREACH_ARRAY_DO:
 * @a: (array length=l): Array to iterate over.
 * @G: Type of elements.
 * @e: Name of iteration variable (element).
 * @l: length of @a.
 * @BLOCK: Content of the loop.
 *
 * Iterate over @a with @BLOCK
 */
#define CRANK_FOREACH_ARRAY_DO(a, G, e, l, BLOCK) \
	CRANK_FOREACH_ARRAY_BEGIN (a, G, e, l) \
		BLOCK \
	CRANK_FOREACH_ARRAY_END



/**
 * CRANK_FOREACH_VALIST_BEGIN:
 * @va: va_list to iterate over.
 * @G: Type of elements.
 * @e: Name of iteration variable (element).
 * @f: End marker for @va.
 *
 * Mark begin of loop that iterate over @va.
 * The loop will iterate till it gets @f.
 *
 * Mark end with #CRANK_FOREACH_VALIST_END.
 */
#define CRANK_FOREACH_VALIST_BEGIN(va, G, e, f) \
    do { \
      G e = va_arg (va, G); \
      if (e == f) break;


/**
 * CRANK_FOREACH_VALIST_END:
 *
 * Marks end of %CRANK_FOREACH_VALIST_BEGIN.
 */
#define CRANK_FOREACH_VALIST_END \
    } while (TRUE);


/**
 * CRANK_FOREACH_VALIST_DO:
 * @va: va_list to iterate over.
 * @G: Type of elements.
 * @e: Name of iteration variable. (element)
 * @f: End marker for @va.
 * @BLOCK: Content of the loop.
 *
 * Iterates over @va with @BLOCK.
 */
#define CRANK_FOREACH_VALIST_DO(va, G, e, f, BLOCK) \
	CRANK_FOREACH_VALIST_BEGIN(va, G, e, f) \
		BLOCK \
	CRANK_FOREACH_VALIST_END




/**
 * CRANK_FOREACH_VARARG_BEGIN:
 * @param_last: Last fixed element of current function.
 * @G: Type of elements.
 * @e: Name of iteration variable. (element)
 * @f: End marker for @va.
 *
 * Marks begin of loop that iterates over variadic arguments of current function.
 *
 * Mark end with %CRANK_FOREACH_VARARG_END.
 */
#define CRANK_FOREACH_VARARG_BEGIN(param_last, G, e, f) \
    { \
      va_list _crank_macro_varargs; \
      va_start (_crank_macro_varargs, param_last); \
      CRANK_FOREACH_VALIST_BEGIN (_crank_macro_varargs, G, e, f)

/**
 * CRANK_FOREACH_VARARG_END:
 *
 * Marks end of %CRANK_FOREACH_VARARG_BEGIN.
 */
#define CRANK_FOREACH_VARARG_END \
      CRANK_FOREACH_VALIST_END \
      va_end (_crank_macro_varargs); \
    }


/**
 * CRANK_FOREACH_VARARG_DO:
 * @param_last: Last fixed element of current function.
 * @G: Type of elements.
 * @e: Name of iteration variable. (element)
 * @f: End marker for @va.
 * @BLOCK: Content of loop..
 *
 * Iterates over variadic arguments with @BLOCK.
 */
#define CRANK_FOREACH_VARARG_DO(param_last, G, e, f, BLOCK) \
	CRANK_FOREACH_VARARG_BEGIN(param_last, G, e, f) \
		BLOCK \
	CRANK_FOREACH_VARARG_END


/**
 * CRANK_FOREACH_GLIST_BEGIN:
 * @l: #GList to iterate over.
 * @G: Type of element.
 * @e: Name of iteration variable. (element)
 *
 * Marks begin of loop that iterates over a #GList.
 *
 * Mark end with %CRANK_FOREACH_GLIST_END
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
 * Marks end of %CRANK_FOREACH_GLIST_BEGIN.
 */
#define CRANK_FOREACH_GLIST_END \
		} \
	}

/**
 * CRANK_FOREACH_GLIST_DO:
 * @l: #GList to iterate over.
 * @G: Type of element.
 * @e: Name of iteration variable. (element)
 * @BLOCK: Contents of the loop.
 *
 * Iterates over a #GList with @BLOCK.
 */
#define CRANK_FOREACH_GLIST_DO(l, G, e, BLOCK) \
	CRANK_FOREACH_GLIST_BEGIN (l, G, e) \
		BLOCK \
	CRANK_FOREACH_GLIST_END


/**
 * CRANK_FOREACH_G_PTR_ARRAY_BEGIN:
 * @arr: (type GPtrArray): #GPtrArray to iterate over.
 * @G: Type of element.
 * @e: Name of iteration variable. (element)
 *
 * Marks begin of loop that iterates over #GPtrArray.
 *
 * Mark end with %CRANK_FOREACH_ARRAY_END.
 */
#define CRANK_FOREACH_G_PTR_ARRAY_BEGIN(arr, G, e) \
	CRANK_FOREACH_ARRAY_BEGIN((arr)->pdata, gpointer, _crank_macro_ptr, (arr)->len) \
	G e = (G) _crank_macro_ptr;

/**
 * CRANK_FOREACH_G_PTR_ARRAY_END:
 *
 * Marks end of %CRANK_FOREACH_G_PTR_ARRAY_BEGIN.
 */
#define CRANK_FOREACH_G_PTR_ARRAY_END \
	CRANK_FOREACH_ARRAY_END

/**
 * CRANK_FOREACH_G_PTR_ARRAY_DO:
 * @arr: (type GPtrArray): #GPtrArray to iterate over.
 * @G: Type of element.
 * @e: Name of iteration variable. (element)
 * @BLOCK: Content of loop.
 *
 * Iterates over a #GPtrArray, with @BLOCK.
 */
#define CRANK_FOREACH_G_PTR_ARRAY_DO(arr, G, e, BLOCK) \
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN(arr, G, e) \
		BLOCK \
	CRANK_FOREACH_G_PTR_ARRAY_END

G_END_DECLS

#endif /* CRANKBASEMACRO_H */
