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
#include "crankshape3vertexed.h"

G_BEGIN_DECLS

#define CRANK_TYPE_SHAPE3_POLYHEDRON crank_shape3_polyhedron_get_type()
G_DECLARE_DERIVABLE_TYPE (CrankShape3Polyhedron,
                          crank_shape3_polyhedron,
                          CRANK, SHAPE3_POLYHEDRON,
                          CrankShape3Vertexed)

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
 * @get_face_normal: Slot for crank_shape3_polyhedron_get_face_normal()
 * @get_normal_face: Slot for crank_shape3_polyhedron_get_normal_face()
 *
 * Virtual function table for #CrankShape3PolyhedronClass
 */
struct _CrankShape3PolyhedronClass {
  /*< private >*/
  CrankShape3VertexedClass _parent;

  /*< public >*/
  void  (*get_face_normal)  (CrankShape3Polyhedron *shape,
                             const guint             fid,
                             CrankVecFloat3         *nor);

  guint (*get_normal_face) (CrankShape3Polyhedron *shape,
                            CrankVecFloat3         *nor);

  /*< private >*/
  gpointer _PADDING2;
  gpointer _PADDING3;

};

//////// Face Properties ///////////////////////////////////////////////////////

void   crank_shape3_polyhedron_get_face_normal                (CrankShape3Polyhedron *shape,
                                                               const guint            fid,
                                                               CrankVecFloat3        *nor);


//////// Nearest item picker ///////////////////////////////////////////////////

guint crank_shape3_polyhedron_get_normal_face                 (CrankShape3Polyhedron *shape,
                                                               CrankVecFloat3        *nor);

G_END_DECLS

#endif
