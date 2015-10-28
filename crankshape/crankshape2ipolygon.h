#ifndef CRANKSHAPE2IPOLYGON_H
#define CRANKSHAPE2IPOLYGON_H

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
#error crankshape2ipolygon.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "crankshape2.h"
#include "cranktrans.h"

G_BEGIN_DECLS

//////// Type declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE2_IPOLYGON crank_shape2_ipolygon_get_type ()

G_DECLARE_INTERFACE (CrankShape2IPolygon,
                     crank_shape2_ipolygon,
                     CRANK, SHAPE2_IPOLYGON,
                     CrankShape2)

/**
 * CrankShape2IPolygonInterface:
 *
 * A Virtual function table for the interface.
 */
struct _CrankShape2IPolygonInterface {
  GTypeInterface        _interface;

  guint               (*get_nvertices)         (CrankShape2IPolygon    *shape);

  void                (*get_vertex)            (CrankShape2IPolygon    *shape,
                                                guint                   index,
                                                CrankVecFloat2         *vertex);



  guint               (*get_nedges)            (CrankShape2IPolygon    *shape);

  void                (*get_edge)              (CrankShape2IPolygon    *shape,
                                                guint                   index,
                                                CrankRanFloat          *edge,
                                                CrankTrans2            *position);

  void                (*get_edge_vertices)     (CrankShape2IPolygon    *shape,
                                                guint                   index,
                                                CrankPairUint          *vertices);

  void                (*get_edge_normal)       (CrankShape2IPolygon    *shape,
                                                guint                   index,
                                                CrankVecFloat2         *normal);




  guint               (*get_farthest_vertex)   (CrankShape2IPolygon    *shape,
                                                CrankVecFloat2         *direction,
                                                CrankVecFloat2         *vertex);
};



//////// Function prototypes ///////////////////////////////////////////////////

guint           crank_shape2_ipolygon_get_nvertices    (CrankShape2IPolygon *shape);

void            crank_shape2_ipolygon_get_vertex       (CrankShape2IPolygon *shape,
                                                        guint                index,
                                                        CrankVecFloat2      *vertex);


guint           crank_shape2_ipolygon_get_nedges       (CrankShape2IPolygon *shape);

void            crank_shape2_ipolygon_get_edge         (CrankShape2IPolygon *shape,
                                                        guint                index,
                                                        CrankRanFloat       *edge,
                                                        CrankTrans2         *position);



void            crank_shape2_ipolygon_get_edge_vertices(CrankShape2IPolygon *shape,
                                                        guint                index,
                                                        CrankPairUint       *vertices);

void            crank_shape2_ipolygon_get_edge_normal  (CrankShape2IPolygon *shape,
                                                        guint                index,
                                                        CrankVecFloat2      *normal);



guint           crank_shape2_ipolygon_get_farthest_vertex (CrankShape2IPolygon *shape,
                                                           CrankVecFloat2      *direction,
                                                           CrankVecFloat2      *vertex);

#endif
