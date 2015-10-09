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
 * @title: Basic Utility Macros
 * @short_description: Basic utility macros that frequently used.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * This section defines utility macros that used in Crank System.
 *
 * * Pointer arithmetics
 * * Operations on Arrays.
 */

#include <string.h>
#include <stdarg.h>
#include <glib.h>

G_BEGIN_DECLS

/**
 * CRANK_PTR_ADD:
 * @p: A Pointer to add.
 * @sz: A size.
 *
 * Performs arithmetic addition on pointer, which is @p + @sz.
 *
 * Returns: Addition of pointer and size.
 */
#define CRANK_PTR_ADD(p,sz) (gpointer)((gsize)(p) + (sz))

/**
 * CRANK_PTR_ADD2:
 * @p: A Pointer to add
 * @sz: A size.
 * @n: Multiplication cofactor; count of @sz.
 *
 * Performs arithmetic addition on pointer, which is @p + (@sz * @n). This is
 * useful when dealing with arrays.
 *
 * Returns: Addition of pointer and size.
 */
#define CRANK_PTR_ADD2(p,sz,n) CRANK_PTR_ADD(p,(sz) * (n))

/**
 * CRANK_PTR_DIFF:
 * @p: A Pointer.
 * @q: Another pointer.
 *
 * Performes arithmetic subtract on pointer, which is @p - @q.
 *
 * Returns: Subtraction of pointer, in type of gsize.
 */
#define CRANK_PTR_DIFF(p,q) ((gsize)(p) - (gsize)(q))



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
 * Compares same sized array using <function>memcmp<!-- -->()</function>.
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
 * <note><para>
 * #GArray and #GPtrArray are more easier to manipulate. You are advised to use
 * them, rather than using triplet of pointer, length, alloc-size.
 * </para></note>
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
  G_STMT_START {                     \
    G* _cbmp = a;                    \
    G* _cbme = _cbmp + n;            \
    while (_cbmp < _cbme)            \
      *(_cbmp++) = v;                \
  } G_STMT_END

G_END_DECLS
#endif
