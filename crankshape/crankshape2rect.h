#ifndef CRANKSHAPE2RECT_H
#define CRANKSHAPE2RECT_H

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
#error crankshape2rect.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2polygon.h"

G_BEGIN_DECLS
//////// Type Declaration //////////////////////////////////////////////////////

/**
 * CrankShape2RectVertex:
 * @CRANK_SHAPE2_RECT_VERTEX_LEFTUP: Left upper vertex.
 * @CRANK_SHAPE2_RECT_VERTEX_RIGHTUP: Right upper vertex.
 * @CRANK_SHAPE2_RECT_VERTEX_RIGHTDOWN: Right lower vertex.
 * @CRANK_SHAPE2_RECT_VERTEX_LEFTDOWN: Left lower vertex.
 *
 * Vertex ID for #CrankShape2Rect.
 */
typedef enum {
  CRANK_SHAPE2_RECT_VERTEX_LEFTUP,
  CRANK_SHAPE2_RECT_VERTEX_RIGHTUP,
  CRANK_SHAPE2_RECT_VERTEX_RIGHTDOWN,
  CRANK_SHAPE2_RECT_VERTEX_LEFTDOWN
} CrankShape2RectVertex;


#define CRANK_TYPE_SHAPE2_RECT crank_shape2_rect_get_type ()

G_DECLARE_FINAL_TYPE (CrankShape2Rect,
                      crank_shape2_rect,
                      CRANK, SHAPE2_RECT,
                      CrankShape2Polygon)


//////// Constructors //////////////////////////////////////////////////////////

CrankShape2Rect *crank_shape2_rect_new (CrankVecFloat2 *size);

CrankShape2Rect *crank_shape2_rect_new_with_wh (gfloat width,
                                                gfloat height);

CrankShape2Rect *crank_shape2_rect_new_unit (void);

CrankShape2Rect *crank_shape2_rect_new_square (gfloat size);


//////// Properties ////////////////////////////////////////////////////////////

void            crank_shape2_rect_get_size (CrankShape2Rect *shape,
                                            CrankVecFloat2  *size);

void            crank_shape2_rect_set_size (CrankShape2Rect *shape,
                                            CrankVecFloat2  *size);


gfloat          crank_shape2_rect_get_width (CrankShape2Rect *shape);

void            crank_shape2_rect_set_width (CrankShape2Rect *shape,
                                             const gfloat     width);


gfloat          crank_shape2_rect_get_height (CrankShape2Rect *shape);

void            crank_shape2_rect_set_height (CrankShape2Rect *shape,
                                              const gfloat     height);

gboolean        crank_shape2_rect_is_square (CrankShape2Rect *shape);

G_END_DECLS

#endif
