#ifndef CRANKSHAPE3SEGMENT_H
#define CRANKSHAPE3SEGMENT_H

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
#error crankshape3segment.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "crankbox.h"
#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE3_SEGMENT crank_shape3_segment_get_type ()

G_DECLARE_FINAL_TYPE (CrankShape3Segment,
                      crank_shape3_segment,
                      CRANK, SHAPE3_SEGMENT,
                      CrankShape3Vertexed)


//////// Constructors //////////////////////////////////////////////////////////

CrankShape3Segment  *crank_shape3_segment_new (const gfloat length);

//////// Property getter/setter ////////////////////////////////////////////////

gfloat              crank_shape3_segment_get_length (CrankShape3Segment *shape);

void                crank_shape3_segment_set_length (CrankShape3Segment *shape,
                                                     const gfloat        length);


G_END_DECLS

#endif
