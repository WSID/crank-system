#ifndef CRANKSHAPE2_H
#define CRANKSHAPE2_H

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
#error crankshape2.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankbox.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////


typedef struct _CrankShape2IPolygon CrankShape2IPolygon;
typedef struct _CrankShape2IFinite CrankShape2IFinite;


#define CRANK_TYPE_SHAPE2 crank_shape2_get_type ()

G_DECLARE_DERIVABLE_TYPE (CrankShape2, crank_shape2, CRANK, SHAPE2, GObject)

/**
 * CrankShape2Class:
 * @approximate_polygon: Slot for crank_shape2_approximate_polygon().
 * @clip: Slot for crank_shape2_clip().
 *
 * Virtual Function table and signal handler table for shape class.
 */
struct _CrankShape2Class {
  /* <private> */
  GObjectClass          _parent_class;

  /* <public> */
  CrankShape2IPolygon*(*approximate_polygon) (CrankShape2  *shape,
                                              const gfloat  vdistance);

  CrankShape2IFinite *(*clip)                (CrankShape2  *shape,
                                              CrankBox2    *box);
  /* <private> */
  gpointer _PADDING2;
  gpointer _PADDING3;

};





//////// Function prototypes ///////////////////////////////////////////////////

CrankShape2IPolygon  *crank_shape2_approximate_polygon (CrankShape2  *shape,
                                                  const gfloat  vdistance);

CrankShape2IFinite   *crank_shape2_clip (CrankShape2 *shape,
                                         CrankBox2   *box);


G_END_DECLS

#endif 
