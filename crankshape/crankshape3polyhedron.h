#ifndef CRANKSHAPE3POLYHEDRON_H
#define CRANKSHAPE3POLYHEDRON_H

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
#error crankshape3polyhedron.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

#include "crankbox.h"
#include "crankshape2.h"
#include "crankshape3.h"
#include "crankshape3finite.h"

G_BEGIN_DECLS

#define CRANK_TYPE_SHAPE3_POLYHEDRON crank_shape3_polyhedron_get_type()
G_DECLARE_DERIVABLE_TYPE (CrankShape3Polyhedron,
                          crank_shape3_polyhedron,
                          CRANK, SHAPE3_POLYHEDRON,
                          CrankShape3Finite)

/**
 * CrankShape3PolyhedronVInfo:
 * @nedges: Number of edges.
 * @edges: (array length=nedges): Edge ids.
 * @faces: (array length=nedges): Face ids.
 */
typedef struct _CrankShape3PolyhedronVData {
  guint nedges;
  guint *edges;
  guint *faces;
} CrankShape3PolyhedronVData;

/**
 * CrankShape3PolyhedronEInfo:
 * @verts: Vertices ids.
 * @faces: Face ids.
 */
typedef struct _CrankShape3PolyhedronEData {
  guint verts[2];
  guint faces[2];
} CrankShape3PolyhedronEData;

/**
 * CrankShape3PolyhedronFInfo:
 * @nverts: Number of edges.
 * @verts: (array length=nverts): Vertices ids.
 * @edges: (array length=nverts): Face ids.
 */
typedef struct _CrankShape3PolyhedronFData {
  guint nverts;
  guint *verts;
  guint *edges;
} CrankShape3PolyhedronFData;

/**
 * CrankShape3PolyhedronClass:
 * @get_nvertices: Slot for crank_shape3_polyhedron_get_nvertices()
 * @get_nedges: Slot for crank_shape3_polyhedron_get_nedges()
 * @get_nfaces: Slot for crank_shape3_polyhedron_get_nfaces()
 * @get_vertex_pos: Slot for crank_shape3_polyhedron_get_vertex_pos()
 * @get_vertex_edges: Slot for crank_shape3_polyhedron_get_vertex_edges()
 * @get_vertex_faces: Slot for crank_shape3_polyhedron_get_vertex_faces()
 * @get_edge_vertices: Slot for crank_shape3_polyhedron_get_edge_vertices()
 * @get_edge_faces: Slot for crank_shape3_polyhedron_get_edge_faces()
 * @get_face_vertices: Slot for crank_shape3_polyhedron_get_face_vertices()
 * @get_face_edges: Slot for crank_shape3_polyhedron_get_face_edges()
 * @get_face_normal: Slot for crank_shape3_polyhedron_get_face_normal()
 * @get_face_as_shape: Slot for crank_shape3_polyhedron_get_face_as_shape()
 * @get_farthest_vertex: Slot for crank_shape3_polyhedron_get_farthest_vertex()
 * @get_normal_face: Slot for crank_shape3_polyhedron_get_normal_face()
 *
 * Virtual function table for #CrankShape3PolyhedronClass
 */
struct _CrankShape3PolyhedronClass {
  /*< private >*/
  CrankShape3FiniteClass _parent;

  /*< public >*/
  guint (*get_nvertices)    (CrankShape3Polyhedron *shape);
  guint (*get_nedges)       (CrankShape3Polyhedron *shape);
  guint (*get_nfaces)       (CrankShape3Polyhedron *shape);

  /*< private >*/
  gpointer _PADDING3;


  /*< public >*/
  void  (*get_vertex_pos)   (CrankShape3Polyhedron *shape,
                             const guint             vid,
                             CrankVecFloat3         *pos);

  guint*(*get_vertex_edges) (CrankShape3Polyhedron *shape,
                             const guint             vid,
                             guint                  *neids);

  guint*(*get_vertex_faces) (CrankShape3Polyhedron *shape,
                             const guint             vid,
                             guint                  *nfids);

  /*< private >*/
  gpointer _PADDING7;


  /*< public >*/
  void  (*get_edge_vertices)(CrankShape3Polyhedron *shape,
                             const guint             eid,
                             guint                  *vids);

  void  (*get_edge_faces)   (CrankShape3Polyhedron *shape,
                             const guint             eid,
                             guint                  *fids);

  /*< private >*/
  gpointer _PADDING10;
  gpointer _PADDING11;


  /*< public >*/
  guint*(*get_face_vertices)(CrankShape3Polyhedron *shape,
                             const guint             fid,
                             guint                  *nvids);

  guint*(*get_face_edges)   (CrankShape3Polyhedron *shape,
                             const guint             fid,
                             guint                  *neids);

  void  (*get_face_normal)  (CrankShape3Polyhedron *shape,
                             const guint             fid,
                             CrankVecFloat3         *nor);

  CrankShape2Polygon* (*get_face_as_shape) (CrankShape3Polyhedron *shape,
                                            const guint             fid,
                                            CrankTrans3            *pos);


  guint (*get_farthest_vertex)(CrankShape3Polyhedron *shape,
                               CrankVecFloat3         *dir);

  guint (*get_normal_face) (CrankShape3Polyhedron *shape,
                            CrankVecFloat3         *nor);

  /*< private >*/
  gpointer _PADDING18;
  gpointer _PADDING19;

};


//////// Shape Property ////////////////////////////////////////////////////////

guint crank_shape3_polyhedron_get_nvertices                   (CrankShape3Polyhedron *shape);

guint crank_shape3_polyhedron_get_nedges                      (CrankShape3Polyhedron *shape);

guint crank_shape3_polyhedron_get_nfaces                      (CrankShape3Polyhedron *shape);

//////// Vertex Property ///////////////////////////////////////////////////////

void crank_shape3_polyhedron_get_vertex_pos                   (CrankShape3Polyhedron *shape,
                                                                const guint             vid,
                                                                CrankVecFloat3         *pos);

guint *crank_shape3_polyhedron_get_vertex_edges               (CrankShape3Polyhedron *shape,
                                                                const guint             vid,
                                                                guint                  *neids);

guint *crank_shape3_polyhedron_get_vertex_faces               (CrankShape3Polyhedron *shape,
                                                                const guint             vid,
                                                                guint                  *nfids);

//////// Edge Property /////////////////////////////////////////////////////////

void crank_shape3_polyhedron_get_edge_vertices                (CrankShape3Polyhedron *shape,
                                                                const guint             eid,
                                                                guint                  *vids);

void crank_shape3_polyhedron_get_edge_faces                   (CrankShape3Polyhedron *shape,
                                                                const guint             eid,
                                                                guint                  *fids);

//////// Face Property /////////////////////////////////////////////////////////

guint *crank_shape3_polyhedron_get_face_vertices              (CrankShape3Polyhedron *shape,
                                                                const guint             fid,
                                                                guint                  *nvids);

guint *crank_shape3_polyhedron_get_face_edges                 (CrankShape3Polyhedron *shape,
                                                                const guint             fid,
                                                                guint                  *neids);

void   crank_shape3_polyhedron_get_face_normal                (CrankShape3Polyhedron *shape,
                                                                const guint             fid,
                                                                CrankVecFloat3         *nor);

CrankShape2Polygon *crank_shape3_polyhedron_get_face_as_shape (CrankShape3Polyhedron *shape,
                                                                const guint             fid,
                                                                CrankTrans3            *pos);


//////// Nearest item picker ///////////////////////////////////////////////////

guint crank_shape3_polyhedron_get_farthest_vertex             (CrankShape3Polyhedron *shape,
                                                                CrankVecFloat3         *dir);

guint crank_shape3_polyhedron_get_normal_face                 (CrankShape3Polyhedron *shape,
                                                                CrankVecFloat3         *nor);


//////// Possible functions ////////////////////////////////////////////////////
// CrankDigraph *crank_shape3_polyhedron_get_ve_digraph (CrankShape3Polyhedron *shape);
//
// void crank_shape3_polyhedron_assert_euler (CrankShape3Polyhedron);

G_END_DECLS

#endif
