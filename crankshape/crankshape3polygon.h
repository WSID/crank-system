#ifndef CRANKSHAPE3POLYGON_H
#define CRANKSHAPE3POLYGON_H

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
#error crankshape3polygon.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "cranktrans.h"
#include "crankshape2.h"
#include "crankshape2vertexed.h"
#include "crankshape2polygon.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE3_POLYGON crank_shape3_polygon_get_type()
G_DECLARE_DERIVABLE_TYPE (CrankShape3Polygon,
                          crank_shape3_polygon,
                          CRANK, SHAPE3_POLYGON,
                          CrankShape3Vertexed)

/**
 * CrankShape3PolygonClass:
 * @get_winding: Slot for crank_shape3_polygon_get_winding()
 * @get_vertex_pos2: Slot for crank_shape3_polygon_get_vertex_pos2()
 * @get_edge_normal: Slot for crank_shape3_polygon_get_edge_normal()
 * @get_normal_edge: Slot for crank_shape3_polygon_get_normal_edge()
 *
 * Virtual function table for #CrankShape3Polygon.
 */
struct _CrankShape3PolygonClass {
  CrankShape3VertexedClass _parent;

  CrankWinding (*get_winding)    (CrankShape3Polygon *shape);

  void    (*get_vertex_pos2)     (CrankShape3Polygon *shape,
                                  guint               vid,
                                  CrankVecFloat2     *pos);

  void    (*get_edge_normal)     (CrankShape3Polygon *shape,
                                  guint               eid,
                                  CrankVecFloat2     *normal);

  guint   (*get_normal_edge)     (CrankShape3Polygon *shape,
                                  CrankVecFloat2     *normal);
};


//////// Shape Properties //////////////////////////////////////////////////////

CrankWinding crank_shape3_polygon_get_winding (CrankShape3Polygon *shape);


//////// VFunc Wrappers ////////////////////////////////////////////////////////

void  crank_shape3_polygon_get_vertex_pos2 (CrankShape3Polygon *shape,
                                            guint               vid,
                                            CrankVecFloat2     *pos);

void  crank_shape3_polygon_get_edge_normal (CrankShape3Polygon *shape,
                                            guint               eid,
                                            CrankVecFloat2     *normal);

guint crank_shape3_polygon_get_normal_edge (CrankShape3Polygon *shape,
                                            CrankVecFloat2     *normal);

G_END_DECLS

#endif
