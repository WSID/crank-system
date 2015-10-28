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

#include <glib.h>
#include <glib-object.h>
#include "crankpair.h"

/**
 * SECTION: crankpair
 * @title: Pairs
 * @short_description: Pair types.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Type described here is pair structure types.
 */

//////// Type definition /////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankPairUint,
                     crank_pair_uint,
                     crank_pair_uint_dup,
                     g_free)

//////// Public functions ///////////////////////////////////

/**
 * crank_pair_uint_init:
 * @pair: (out): A Pair.
 * @a: A element.
 * @b: A element.
 *
 * Initialize a pair with member.
 */
void
crank_pair_uint_init (CrankPairUint *pair,
                      const guint    a,
                      const guint    b)
{
  pair->a = a;
  pair->b = b;
}

/**
 * crank_pair_uint_init_array:
 * @pair: (out): A Pair.
 * @array: (array fixed-size=2): Array of elements
 *
 * Initialize a pair with array.
 */
void
crank_pair_uint_init_array (CrankPairUint *pair,
                            const guint   *array)
{
  pair->a = array[0];
  pair->b = array[1];
}

/**
 * crank_pair_uint_copy:
 * @pair: A Pair.
 * @other: (out): A Pair same as @pair.
 *
 * Copy a @pair to @other.
 */
void
crank_pair_uint_copy (CrankPairUint *pair,
                      CrankPairUint *other)
{
  other->a = pair->a;
  other->b = pair->b;
}

/**
 * crank_pair_uint_dup:
 * @pair: A Pair.
 *
 * Duplicates a @pair on heap.
 *
 * Returns: (transfer full): A Pair same as @pair.
 */
CrankPairUint*
crank_pair_uint_dup (CrankPairUint *pair)
{
  CrankPairUint *result = g_new (CrankPairUint, 1);

  crank_pair_uint_copy (pair, result);

  return result;
}


/**
 * crank_pair_uint_swap:
 * @a: A Pair.
 * @r: (out): A Pair with swapped members.
 *
 * Swap elements in a pair.
 */
void
crank_pair_uint_swap (CrankPairUint *a,
                      CrankPairUint *r)
{
  r->b = a->a;
  r->a = a->b;
}

/**
 * crank_pair_uint_swap_self:
 * @a: A Pair.
 *
 * Swap elements in a pair.
 */
void
crank_pair_uint_swap_self (CrankPairUint *a)
{
  guint temp = a->a;
  a->a = a->b;
  a->b = temp;
}
