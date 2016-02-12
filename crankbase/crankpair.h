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


#define CRANK_TYPE_PAIR_POINTER (crank_pair_pointer_get_type())
GType   crank_pair_pointer_get_type(void);

typedef struct _CrankPairPointer CrankPairPointer;

/**
 * CrankPairPointer:
 * @a: First element.
 * @b: Second element.
 *
 * Represents a pair of #gpointer.
 */
struct _CrankPairPointer {
  gpointer  a;
  gpointer  b;
};



//////// Public Functions //////////////////////////////////////////////////////

void                crank_pair_uint_init          (CrankPairUint       *pair,
                                                   const guint          a,
                                                   const guint          b);

void                crank_pair_uint_init_array    (CrankPairUint       *pair,
                                                   const guint*         array);



void                crank_pair_uint_copy          (const CrankPairUint *pair,
                                                   CrankPairUint       *other);

CrankPairUint      *crank_pair_uint_dup           (const CrankPairUint *pair);



void                crank_pair_uint_swap          (const CrankPairUint *a,
                                                   CrankPairUint       *r);

void                crank_pair_uint_swap_self     (CrankPairUint       *a);





void                crank_pair_pointer_init       (CrankPairPointer *pair,
                                                   gpointer          a,
                                                   gpointer          b);

void                crank_pair_pointer_init_array (CrankPairPointer *pair,
                                                   gpointer         *array);

void                crank_pair_pointer_copy       (const CrankPairPointer *pair,
                                                   CrankPairPointer       *other);

CrankPairPointer   *crank_pair_pointer_dup        (const CrankPairPointer *pair);


void                crank_pair_pointer_swap       (const CrankPairPointer *a,
                                                   CrankPairPointer       *r);

void                crank_pair_pointer_swap_self  (CrankPairPointer       *a);


void                crank_pair_pointer_foreach    (CrankPairPointer       *pair,
                                                   GFunc                   func,
                                                   gpointer                userdata);

G_END_DECLS

#endif
