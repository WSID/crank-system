#ifndef CRANKBOX_H
#define CRANKBOX_H

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

#ifndef _CRANKSHAPE_INSIDE
#error crankbox.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////

typedef struct _CrankBox2 CrankBox2;

#define CRANK_TYPE_BOX2 crank_box2_get_type ()
GType           crank_box2_get_type (void);

/**
 * CrankBox2:
 * @start: Start of box.
 * @end: End of box.
 *
 * Represents a box shaped range between two #CrankVecFloat2.
 */
struct _CrankBox2 {
  CrankVecFloat2        start;
  CrankVecFloat2        end;
};


//////// Function prototypes ///////////////////////////////////////////////////

void            crank_box2_init        (CrankBox2      *box,
                                        CrankVecFloat2 *start,
                                        CrankVecFloat2 *end);

void            crank_box2_init_uvec   (CrankBox2      *box,
                                        const gfloat    start_x,
                                        const gfloat    start_y,
                                        const gfloat    end_x,
                                        const gfloat    end_y);

void            crank_box2_init_range  (CrankBox2      *box,
                                        CrankRanFloat  *x,
                                        CrankRanFloat  *y);

void            crank_box2_init_unit   (CrankBox2      *box);

void            crank_box2_copy        (CrankBox2      *box,
                                        CrankBox2      *other);

CrankBox2      *crank_box2_dup         (CrankBox2      *box);


gboolean        crank_box2_has_inf     (CrankBox2      *box);

gboolean        crank_box2_has_nan     (CrankBox2      *box);



void            crank_box2_get_x       (CrankBox2      *box,
                                        CrankRanFloat  *x);

void            crank_box2_get_y       (CrankBox2      *box,
                                        CrankRanFloat  *y);

void            crank_box2_get_dimen   (CrankBox2      *box,
                                        CrankVecFloat2 *dimen);

gfloat          crank_box2_get_diaglen (CrankBox2      *box);





gboolean        crank_box2_contains    (CrankBox2      *box,
                                        CrankVecFloat2 *value);

void            crank_box2_get         (CrankBox2      *box,
                                        CrankVecFloat2 *index,
                                        CrankVecFloat2 *res);

void            crank_box2_index_of    (CrankBox2      *box,
                                        CrankVecFloat2 *value,
                                        CrankVecFloat2 *index);

void            crank_box2_clamp       (CrankBox2      *box,
                                        CrankVecFloat2 *value,
                                        CrankVecFloat2 *res);

gboolean        crank_box2_get_intersection (CrankBox2 *box,
                                             CrankBox2 *other,
                                             CrankBox2 *intersect);

G_END_DECLS

#endif
