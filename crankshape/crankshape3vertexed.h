#ifndef CRANKSHAPE3VERTEXED_H
#define CRANKSHAPE3VERTEXED_H

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
#error crankshape3vertexed.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

#include "crankbox.h"
#include "crankshapemisc.h"
#include "crankshape2.h"
#include "crankshape3.h"
#include "crankshape3finite.h"

G_BEGIN_DECLS

/**
 * CrankShape3VertexedVData
 * @nedges: Number of edges.
 * @edges: (array length=nedges): Edge ids.
 * @nfaces: Number of faces.
 * @faces: (array length=nfaces): Face ids.
 *
 * Association data for a vertex.
 */
typedef struct _CrankShape3VertexedVData {
  guint nedges;
  guint *edges;
  guint nfaces;
  guint *faces;
} CrankShape3VertexedVData;

/**
 * CrankShape3VertexedEData
 * @vertices: Vertex ids.
 * @nfaces: Number of faces.
 * @faces: (array length=nfaces): Face ids.
 *
 * Association data for an edge.
 */
typedef struct _CrankShape3VertexedEData {
  guint vertices[2];
  guint nfaces;
  guint *faces;
} CrankShape3VertexedEData;

/**
 * CrankShape3VertexedVData
 * @nvertices: Number of vertices.
 * @vertices: (array length=nvertices): Vertex ids.
 * @nedges: Number of edges.
 * @edges: (array length=nedges): Edge ids.
 *
 * Association data for a face.
 */
typedef struct _CrankShape3VertexedFData {
  guint nvertices;
  guint *vertices;
  guint nedges;
  guint *edges;
} CrankShape3VertexedFData;

#define CRANK_TYPE_SHAPE3_VERTEXED crank_shape3_vertexed_get_type()
G_DECLARE_DERIVABLE_TYPE (CrankShape3Vertexed,
                          crank_shape3_vertexed,
                          CRANK, SHAPE3_VERTEXED,
                          CrankShape3Finite)

/**
 * CrankShape3VertexedClass:
 * @get_dimension: Slot for crank_shape3_vertexed_get_dimension()
 * @get_nvertices: Slot for crank_shape3_vertexed_get_nvertices()
 * @get_nedges: Slot for crank_shape3_vertexed_get_nedges()
 * @get_nfaces: Slot for crank_shape3_vertexed_get_nfaces()
 * @get_vertex_pos: Slot for crank_shape3_vertexed_get_vertex_pos()
 * @get_vertex_edges: Slot for crank_shape3_vertexed_get_vertex_edges()
 * @get_vertex_faces: Slot for crank_shape3_vertexed_get_vertex_faces()
 * @get_edge_vertices: Slot for crank_shape3_vertexed_get_edge_vertices()
 * @get_edge_faces: Slot for crank_shape3_vertexed_get_edge_faces()
 * @get_face_winding: Slot for crank_shape3_vertexed_get_face_winding()
 * @get_face_vertices: Slot for crank_shape3_vertexed_get_face_vertices()
 * @get_face_edges: Slot for crank_shape3_vertexed_get_face_edges()
 * @get_face_as_shape: Slot for crank_shape3_vertexed_get_face_as_shape()
 * @get_farthest_vertex: Slot for crank_shape3_vertexed_get_farthest_vertex()
 *
 * Virtual function table for #CrankShape3VertexedClass
 */
struct _CrankShape3VertexedClass {
  /*< private >*/
  CrankShape3FiniteClass _parent;

  /*< public >*/
  guint (*get_dimension)    (CrankShape3Vertexed *shape);
  guint (*get_nvertices)    (CrankShape3Vertexed *shape);
  guint (*get_nedges)       (CrankShape3Vertexed *shape);
  guint (*get_nfaces)       (CrankShape3Vertexed *shape);


  /*< public >*/
  void  (*get_vertex_pos)   (CrankShape3Vertexed *shape,
                             const guint             vid,
                             CrankVecFloat3         *pos);

  guint*(*get_vertex_edges) (CrankShape3Vertexed *shape,
                             const guint             vid,
                             guint                  *neids);

  guint*(*get_vertex_faces) (CrankShape3Vertexed *shape,
                             const guint             vid,
                             guint                  *nfids);

  /*< private >*/
  gpointer _PADDING7;


  /*< public >*/
  void  (*get_edge_vertices)(CrankShape3Vertexed *shape,
                             const guint             eid,
                             guint                  *vids);

  void  (*get_edge_faces)   (CrankShape3Vertexed *shape,
                             const guint             eid,
                             guint                  *fids);

  /*< private >*/
  gpointer _PADDING10;
  gpointer _PADDING11;


  /*< public >*/
  CrankWinding (*get_face_winding) (CrankShape3Vertexed *shape,
                                    const guint          fid);

  guint*(*get_face_vertices)(CrankShape3Vertexed *shape,
                             const guint             fid,
                             guint                  *nvids);

  guint*(*get_face_edges)   (CrankShape3Vertexed *shape,
                             const guint             fid,
                             guint                  *neids);

  CrankShape2Polygon* (*get_face_as_shape) (CrankShape3Vertexed *shape,
                                            const guint             fid,
                                            CrankTrans3            *pos);

  /*< public >*/
  guint (*get_farthest_vertex)(CrankShape3Vertexed *shape,
                               CrankVecFloat3         *dir);

  /*< private >*/
  gpointer _PADDING17;
  gpointer _PADDING18;
  gpointer _PADDING19;

};


//////// Shape Property ////////////////////////////////////////////////////////

guint crank_shape3_vertexed_get_dimension                   (CrankShape3Vertexed *shape);

guint crank_shape3_vertexed_get_nvertices                   (CrankShape3Vertexed *shape);

guint crank_shape3_vertexed_get_nedges                      (CrankShape3Vertexed *shape);

guint crank_shape3_vertexed_get_nfaces                      (CrankShape3Vertexed *shape);

//////// Vertex Property ///////////////////////////////////////////////////////

void crank_shape3_vertexed_get_vertex_pos                      (CrankShape3Vertexed *shape,
                                                                const guint          vid,
                                                                CrankVecFloat3      *pos);

guint *crank_shape3_vertexed_get_vertex_edges                  (CrankShape3Vertexed *shape,
                                                                const guint          vid,
                                                                guint               *neids);

guint *crank_shape3_vertexed_get_vertex_faces                  (CrankShape3Vertexed *shape,
                                                                const guint          vid,
                                                                guint               *nfids);

//////// Edge Property /////////////////////////////////////////////////////////

void crank_shape3_vertexed_get_edge_vertices                   (CrankShape3Vertexed *shape,
                                                                const guint          eid,
                                                                guint               *vids);

void crank_shape3_vertexed_get_edge_faces                      (CrankShape3Vertexed *shape,
                                                                const guint          eid,
                                                                guint               *fids);

//////// Face Property /////////////////////////////////////////////////////////

CrankWinding crank_shape3_vertexed_get_face_winding            (CrankShape3Vertexed *shape,
                                                                const guint          fid);

guint *crank_shape3_vertexed_get_face_vertices                 (CrankShape3Vertexed *shape,
                                                                const guint          fid,
                                                                guint               *nvids);

guint *crank_shape3_vertexed_get_face_edges                    (CrankShape3Vertexed *shape,
                                                                const guint          fid,
                                                                guint               *neids);

CrankShape2Polygon *crank_shape3_vertexed_get_face_as_shape    (CrankShape3Vertexed *shape,
                                                                const guint          fid,
                                                                CrankTrans3         *pos);


//////// Nearest item picker ///////////////////////////////////////////////////

guint crank_shape3_vertexed_get_farthest_vertex                (CrankShape3Vertexed *shape,
                                                                CrankVecFloat3      *dir);


//////// Possible functions ////////////////////////////////////////////////////
// CrankDigraph *crank_shape3_vertexed_get_ve_digraph (CrankShape3Vertexed *shape);
//
// void crank_shape3_vertexed_assert_euler (CrankShape3Vertexed);

G_END_DECLS

#endif
