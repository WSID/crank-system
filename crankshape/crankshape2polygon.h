#ifndef CRANKSHAPE2POLYGON_H
#define CRANKSHAPE2POLYGON_H

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
#error crankshape2polygon.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "cranktrans.h"
#include "crankshapemisc.h"
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2vertexed.h"

G_BEGIN_DECLS

//////// Type declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE2_POLYGON crank_shape2_polygon_get_type ()

G_DECLARE_DERIVABLE_TYPE (CrankShape2Polygon,
                          crank_shape2_polygon,
                          CRANK, SHAPE2_POLYGON,
                          CrankShape2Vertexed)
/**
 * CrankShape2Polygon:
 *
 * Structure represents a polygon shape
 */


/**
 * CrankShape2PolygonClass:
 * @get_winding: Slot for crank_shape2_polygon_get_winding()
 * @get_edge_normal: Slot for crank_shape2_polygon_get_edge_normal()
 * @get_normal_edge: Slot for crank_shape2_polygon_get_normal_edge()
 *
 * A Virtual function table for the interface.
 */
struct _CrankShape2PolygonClass {
  /*< private >*/
  CrankShape2VertexedClass  _parent;

  /*< public >*/
  CrankWinding        (*get_winding)           (CrankShape2Polygon    *shape);


  void                (*get_edge_normal)       (CrankShape2Polygon    *shape,
                                                guint                   index,
                                                CrankVecFloat2         *normal);

  guint               (*get_normal_edge)     (CrankShape2Polygon *shape,
                                              CrankVecFloat2     *normal);
};


//////// Polygon Properties ////////////////////////////////////////////////////

CrankWinding    crank_shape2_polygon_get_winding (CrankShape2Polygon *shape);


//////// Edge Properties ///////////////////////////////////////////////////////

void            crank_shape2_polygon_get_edge_normal  (CrankShape2Polygon *shape,
                                                        guint                index,
                                                        CrankVecFloat2      *normal);

guint           crank_shape2_polygon_get_normal_edge     (CrankShape2Polygon *shape,
                                                          CrankVecFloat2      *normal);

#endif
