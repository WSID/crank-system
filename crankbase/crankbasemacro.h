#ifndef CRANKBASEMACRO_H
#define CRANKBASEMACRO_H

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
 * CRANK_ARRAY_FILL:
 * @a: Array to fill.
 * @G: Type of element.
 * @n: Item count of @a.
 * @v: Value to fill.
 *
 * Fill an array by given value.
 */
#define CRANK_ARRAY_FILL(a, G, n, v) \
	CRANK_FOREACH_IRANGE_DO(i, n, {a[i] = (G)v;})





/**
 * CRANK_FOREACH_RANGE_BEGIN:
 * @G: Type of iteration variable.
 * @e: Name of iteration variable.
 * @rs: Start of range.
 * @re: End of range.
 * @inc: Increasement.
 *
 * Marks begin of loop that iterates over [@rs, @re) with @inc.
 *
 * Mark end with #CRANK_FOREACH_RANGE_END
 */
#define CRANK_FOREACH_RANGE_BEGIN(G, e, rs, re, inc) \
	{	G e; \
		for (e = rs; e < re; e = e + inc) {

/**
 * CRANK_FOREACH_RANGE_END:
 *
 * Marks end of loop of %CRANK_FOREACH_RANGE_BEGIN
 */
#define CRANK_FOREACH_RANGE_END \
	} }

/**
 * CRANK_FOREACH_RANGE_DO:
 * @G: Type of iteration variable.
 * @e: Name of iteration variable.
 * @rs: Start of range.
 * @re: End of range.
 * @inc: Increasement.
 * @BLOCK: block to iterate.
 *
 * Iterates over range [@rs, @re) with @BLOCK.
 */
#define CRANK_FOREACH_RANGE_DO(G, e, rs, re, inc, BLOCK) \
	CRANK_FOREACH_RANGE_BEGIN (G, e, rs, re, inc) \
		BLOCK \
	CRANK_FOREACH_RANGE_END



/**
 * CRANK_FOREACH_IRANGE_BEGIN:
 * @e: Name of iteration variable.
 * @n: End of range.
 *
 * Marks begin of loop that iterates over [0, @n).
 * Note that @n is not included.
 *
 * Mark end with #CRANK_FOREACH_IRANGE_END
 */
#define CRANK_FOREACH_IRANGE_BEGIN(e, n) \
	CRANK_FOREACH_RANGE_BEGIN (gint, e, 0, n, 1)

/**
 * CRANK_FOREACH_IRANGE_END:
 *
 * Marks end of loop of %CRANK_FOREACH_IRANGE_BEGIN
 */
#define CRANK_FOREACH_IRANGE_END \
	CRANK_FOREACH_RANGE_END

/**
 * CRANK_FOREACH_IRANGE_DO:
 * @e: Name of iteration variable.
 * @n: End of range.
 * @BLOCK: Block to iterate.
 *
 * Iterates over range [0, @n) with @BLOCK.
 */
#define CRANK_FOREACH_IRANGE_DO(e, n, BLOCK) \
	CRANK_FOREACH_IRANGE_BEGIN (e, n) \
		BLOCK \
	CRANK_FOREACH_IRANGE_END


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
	CRANK_FOREACH_IRANGE_BEGIN (_crank_macro_i, l) \
		G e = a[_crank_macro_i];

/**
 * CRANK_FOREACH_ARRAY_END:
 * 
 * Marks end of loop from %CRANK_FOREACH_ARRAY_BEGIN
 */
#define CRANK_FOREACH_ARRAY_END \
	CRANK_FOREACH_IRANGE_END

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
