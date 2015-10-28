#ifndef CRANKPAIR_H
#define CRANKPAIR_H

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
#error crankpair.h cannot included directly.
#endif

#include <glib.h>
#include <glib-object.h>


G_BEGIN_DECLS

//////// Type Definition ///////////////////////////////////////////////////////

#define CRANK_TYPE_PAIR_UINT crank_pair_uint_get_type()
GType   crank_pair_uint_get_type (void);

typedef struct _CrankPairUint  CrankPairUint;

/**
 * CrankPairUint:
 * @a: First element.
 * @b: Second element.
 *
 * Reperesents a pair of #guint.
 */
struct _CrankPairUint {
  guint a;
  guint b;
};


//////// Public Functions //////////////////////////////////////////////////////

void            crank_pair_uint_init (CrankPairUint *pair,
                                      const guint    a,
                                      const guint    b);

void            crank_pair_uint_init_array (CrankPairUint *pair,
                                            const guint*   array);



void            crank_pair_uint_copy (CrankPairUint *pair,
                                      CrankPairUint *other);

CrankPairUint  *crank_pair_uint_dup (CrankPairUint *pair);



void            crank_pair_uint_swap (CrankPairUint *a,
                                      CrankPairUint *r);


void            crank_pair_uint_swap_self (CrankPairUint *a);

G_END_DECLS

#endif