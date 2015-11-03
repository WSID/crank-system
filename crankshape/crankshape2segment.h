#ifndef CRANKSHAPE2SEGMENT_H
#define CRANKSHAPE2SEGMENT_H

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
#error crankshape2segment.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "crankbox.h"
#include "crankshape2.h"
#include "crankshape2finite.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE2_SEGMENT crank_shape2_segment_get_type ()

G_DECLARE_FINAL_TYPE (CrankShape2Segment,
                      crank_shape2_segment,
                      CRANK, SHAPE2_SEGMENT,
                      CrankShape2Polygon)


//////// Constructors //////////////////////////////////////////////////////////

CrankShape2Segment *crank_shape2_segment_new (const gfloat length);

CrankShape2Segment *crank_shape2_segment_new_with_positoin (const gfloat  length,
                                                            CrankTrans2  *position);

CrankShape2Segment *crank_shape2_segment_new_with_points (CrankVecFloat2 *a,
                                                          CrankVecFloat2 *b);

//////// Property getter/setters ///////////////////////////////////////////////

gfloat          crank_shape2_segment_get_length (CrankShape2Segment *shape);

void            crank_shape2_segment_set_length (CrankShape2Segment *shape,
                                                 const gfloat        length);




G_END_DECLS

#endif
