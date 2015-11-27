#ifndef CRANKSHAPE2TRIANGLE_H
#define CRANKSHAPE2TRIANGLE_H

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
#error crankshape2triangle.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "crankbox.h"
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2vertexed.h"
#include "crankshape2polygon.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE2_TRIANGLE crank_shape2_triangle_get_type ()

G_DECLARE_FINAL_TYPE (CrankShape2Triangle,
                      crank_shape2_triangle,
                      CRANK, SHAPE2_TRIANGLE,
                      CrankShape2Polygon)


//////// Constructors //////////////////////////////////////////////////////////

CrankShape2Triangle *crank_shape2_triangle_new (CrankVecFloat2 *vertices);

CrankShape2Triangle *crank_shape2_triangle_new_regular (const gfloat radius);

G_END_DECLS

#endif
