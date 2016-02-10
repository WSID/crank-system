#ifndef CRANKBITS_H
#define CRANKBITS_H

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
#error crankbits.h cannot be included directly.
#endif

#include <glib.h>

guint   crank_bits_shift_to_left32  (guint32 *subject);

guint   crank_bits_shift_to_left64  (guint64 *subject);

guint64 crank_bits_remquo_2_64      (guint64  divisor,
                                     guint64 *remainder);


guint32 crank_bits_least_pow2_32    (const guint32 number);

guint64 crank_bits_least_pow2_64    (const guint64 number);

/**
 * CRANK_ADD_CARRY64:
 * @a: A 64-bit integer.
 * @b: A 64-bit integer.
 * @r: (out): A 64-bit result.
 *
 * Adds two 64-bit integer and returns its carry.
 * It is used to perform additions in various operations. *
 *
 * Returns: The carry of its result, as #gboolean.
 */
#define CRANK_ADD_CARRY64(a,b,r)    ((*(r) = (a) + (b)), (b) > *(r))
/**
 * CRANK_IADD_CARRY64:
 * @a: A 64-bit integer.
 * @b: A 64-bit integer.
 *
 * Adds two 64-bit integer and returns its carry.
 * It is used to perform additions in various operations.
 *
 * Returns: The carry of its result, as #gboolean.
 */
#define CRANK_IADD_CARRY64(a,b)     ((*(a) += (b)), (b) > *(a))

/**
 * CRANK_SUB_CARRY64:
 * @a: A 64-bit integer.
 * @b: A 64-bit integer.
 * @r: (out): A 64-bit result.
 *
 * Subtracts two 64-bit integer and returns its burrow.
 * It is used to perform additions in various operations.
 *
 * Returns: The burrow of its result, as #gboolean.
 */
#define CRANK_SUB_CARRY64(a,b,r)    ((*(r) = (a) - (b)), (a) < (b))


#endif //CRANKBITS_H
