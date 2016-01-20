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
#include "crankshapemisc.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////

typedef struct _CrankBox2 CrankBox2;

typedef struct _CrankBox3 CrankBox3;


#define CRANK_TYPE_BOX2 crank_box2_get_type ()
GType           crank_box2_get_type (void);

#define CRANK_TYPE_BOX3 crank_box3_get_type ()
GType           crank_box3_get_type (void);

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


/**
 * CrankBox3:
 * @start: Start of box.
 * @end: End of box.
 *
 * Represents a box shaped range between two #CrankVecFloat3.
 */
struct _CrankBox3 {
  CrankVecFloat3        start;
  CrankVecFloat3        end;
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

void            crank_box2_gets        (CrankBox2      *box,
                                        const gfloat    index,
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




void            crank_box3_init        (CrankBox3      *box,
                                        CrankVecFloat3 *start,
                                        CrankVecFloat3 *end);

void            crank_box3_init_uvec   (CrankBox3      *box,
                                        const gfloat    start_x,
                                        const gfloat    start_y,
                                        const gfloat    start_z,
                                        const gfloat    end_x,
                                        const gfloat    end_y,
                                        const gfloat    end_z);

void            crank_box3_init_range  (CrankBox3      *box,
                                        CrankRanFloat  *x,
                                        CrankRanFloat  *y,
                                        CrankRanFloat  *z);

void            crank_box3_init_unit   (CrankBox3      *box);

void            crank_box3_copy        (CrankBox3      *box,
                                        CrankBox3      *other);

CrankBox3      *crank_box3_dup         (CrankBox3      *box);


gboolean        crank_box3_has_inf     (CrankBox3      *box);

gboolean        crank_box3_has_nan     (CrankBox3      *box);



void            crank_box3_get_x       (CrankBox3      *box,
                                        CrankRanFloat  *x);

void            crank_box3_get_y       (CrankBox3      *box,
                                        CrankRanFloat  *y);

void            crank_box3_get_z       (CrankBox3      *box,
                                        CrankRanFloat  *z);

void            crank_box3_get_dimen   (CrankBox3      *box,
                                        CrankVecFloat3 *dimen);

gfloat          crank_box3_get_diaglen (CrankBox3      *box);





gboolean        crank_box3_contains    (CrankBox3      *box,
                                        CrankVecFloat3 *value);

void            crank_box3_get         (CrankBox3      *box,
                                        CrankVecFloat3 *index,
                                        CrankVecFloat3 *res);

void            crank_box3_gets        (CrankBox3      *box,
                                        const gfloat    index,
                                        CrankVecFloat3 *res);

void            crank_box3_index_of    (CrankBox3      *box,
                                        CrankVecFloat3 *value,
                                        CrankVecFloat3 *index);

void            crank_box3_clamp       (CrankBox3      *box,
                                        CrankVecFloat3 *value,
                                        CrankVecFloat3 *res);

gboolean        crank_box3_get_intersection (CrankBox3 *box,
                                             CrankBox3 *other,
                                             CrankBox3 *intersect);

G_END_DECLS

#endif
