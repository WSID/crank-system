#ifndef CRANKSHAPE2VERTEXED_H
#define CRANKSHAPE2VERTEXED_H

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
#error crankshape2vertexed.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "cranktrans.h"
#include "crankshape2.h"
#include "crankshape2finite.h"

G_BEGIN_DECLS

//////// Type declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE2_VERTEXED crank_shape2_vertexed_get_type ()

G_DECLARE_DERIVABLE_TYPE (CrankShape2Vertexed,
                          crank_shape2_vertexed,
                          CRANK, SHAPE2_VERTEXED,
                          CrankShape2Finite)
/**
 * CrankShape2Vertexed:
 *
 * Structure represents a shape with vertices and possibly edges.
 */


/**
 * CrankShape2VertexedClass:
 * @get_dimension: Slot for crank_shape2_vertexed_get_dimension()
 * @get_nvertices: Slot for crank_shape2_vertexed_get_nvertices()
 * @get_nedges: Slot for crank_shape2_vertexed_get_nedges()
 * @get_vertex_pos: Slot for crank_shape2_vertexed_get_vertex_pos()
 * @get_vertex_edges: Slot for crank_shape2_vertexed_get_vertex_edges()
 * @get_edge_vertices: Slot for crank_shape2_vertexed_get_edge_vertices()
 * @get_farthest_vertex: Slot for crank_shape2_vertexed_get_farthest_vertex()
 * @get_normal_edge: Slot for crank_shape2_vertexed_get_normal_edge()
 *
 * A Virtual function table for the interface.
 */
struct _CrankShape2VertexedClass {
  /*< private >*/
  CrankShape2FiniteClass  _parent;

  /*< public >*/
  // Shape properties

  guint               (*get_dimension)         (CrankShape2Vertexed    *shape);

  guint               (*get_nvertices)         (CrankShape2Vertexed    *shape);

  guint               (*get_nedges)            (CrankShape2Vertexed    *shape);

  // Vertex properties
  void                (*get_vertex_pos)        (CrankShape2Vertexed    *shape,
                                                guint                   vid,
                                                CrankVecFloat2         *pos);

  void                (*get_vertex_edges)      (CrankShape2Vertexed    *shape,
                                                guint                   vid,
                                                guint                 **eids,
                                                guint                 *neids);

  // Edge properties
  void                (*get_edge_vertices)    (CrankShape2Vertexed     *shape,
                                               guint                    eid,
                                               guint                   *vids);

  // Element picker
  guint               (*get_farthest_vertex)   (CrankShape2Vertexed    *shape,
                                                CrankVecFloat2         *direction);
};



//////// Shape Properties //////////////////////////////////////////////////////

guint           crank_shape2_vertexed_get_dimension    (CrankShape2Vertexed *shape);

guint           crank_shape2_vertexed_get_nvertices    (CrankShape2Vertexed *shape);

guint           crank_shape2_vertexed_get_nedges       (CrankShape2Vertexed *shape);


//////// Vertex Properties /////////////////////////////////////////////////////

void            crank_shape2_vertexed_get_vertex_pos   (CrankShape2Vertexed *shape,
                                                        guint                vid,
                                                        CrankVecFloat2      *pos);

void            crank_shape2_vertexed_get_vertex_edges (CrankShape2Vertexed  *shape,
                                                        guint                 vid,
                                                        guint               **eids,
                                                        guint                *neids);

//////// Edge Properties ///////////////////////////////////////////////////////
void            crank_shape2_vertexed_get_edge_vertices (CrankShape2Vertexed *shape,
                                                         guint                eid,
                                                         guint               *vids);


//////// Element picker ////////////////////////////////////////////////////////

guint           crank_shape2_vertexed_get_farthest_vertex (CrankShape2Vertexed *shape,
                                                          CrankVecFloat2      *direction);



#endif
