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

#define _CRANKSHAPE_INSIDE


#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"

#include "crankshapemisc.h"
#include "crankpolystruct3.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polyhedron.h"
#include "crankshape3tpolyhedron.h"

/**
 * SECTION: crankshape3tpolyhedron
 * @title: CrankShape3TPolyhedron
 * @short_description: Templated Polyhedral Shape.
 * @stability: unstable
 * @include: crankshape.h
 *
 * Base class for templated shape classes, whose instances share same structure.
 *
 * # Abstract Functions left
 *
 * * #CrankShape3VertexedClass.get_vertex_pos()
 * * #CrankShape3VertexedClass.get_face_winding()
 * * #CrankShape3FiniteClass.is_convex()
 * * #CrankShape3FiniteClass.get_bound_radius()
 * * #CrankShape3Class.contains()
 *
 * # Virtual functions
 *
 * * #CrankShape3VertexedClass.get_nvertices()
 * * #CrankShape3VertexedClass.get_nedges()
 * * #CrankShape3VertexedClass.get_nfaces()
 * * #CrankShape3VertexedClass.get_vertex_edges()
 * * #CrankShape3VertexedClass.get_vertex_faces()
 * * #CrankShape3VertexedClass.get_edge_vertices()
 * * #CrankShape3VertexedClass.get_edge_faces()
 * * #CrankShape3VertexedClass.get_face_vertices()
 * * #CrankShape3VertexedClass.get_face_edges()
 */

//////// List of Virtual functions /////////////////////////////////////////////

static guint    crank_shape3_tpolyhedron_get_nvertices (CrankShape3Vertexed *shape);

static guint    crank_shape3_tpolyhedron_get_nedges    (CrankShape3Vertexed *shape);

static guint    crank_shape3_tpolyhedron_get_nfaces    (CrankShape3Vertexed *shape);


static guint   *crank_shape3_tpolyhedron_get_vertex_edges (CrankShape3Vertexed *shape,
                                                           const guint          vid,
                                                           guint               *neids);

static guint   *crank_shape3_tpolyhedron_get_vertex_faces (CrankShape3Vertexed *shape,
                                                           const guint          vid,
                                                           guint               *nfids);

static void     crank_shape3_tpolyhedron_get_edge_vertices (CrankShape3Vertexed *shape,
                                                            const guint          eid,
                                                            guint               *vids);

static guint   *crank_shape3_tpolyhedron_get_edge_faces (CrankShape3Vertexed *shape,
                                                         const guint          eid,
                                                         guint               *nfids);

static guint   *crank_shape3_tpolyhedron_get_face_vertices (CrankShape3Vertexed *shape,
                                                            const guint          fid,
                                                            guint               *nvids);

static guint   *crank_shape3_tpolyhedron_get_face_edges (CrankShape3Vertexed *shape,
                                                         const guint          fid,
                                                         guint               *neids);


//////// Private functions /////////////////////////////////////////////////////

static CrankPolyStruct3 *crank_shape3_tpolyhedron_get_template (gpointer shape);


//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankShape3TPolyhedronClassPrivate
{
  CrankPolyStruct3  *t;
} CrankShape3TPolyhedronClassPrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_CODE (CrankShape3TPolyhedron,
                                  crank_shape3_tpolyhedron,
                                  CRANK_TYPE_SHAPE3_POLYHEDRON,
                                  {
                                    g_type_add_class_private (g_define_type_id,
                                                              sizeof (CrankShape3TPolyhedronClassPrivate));
                                  })


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_tpolyhedron_init (CrankShape3TPolyhedron *self)
{
}

static void
crank_shape3_tpolyhedron_class_init (CrankShape3TPolyhedronClass *c)
{
  CrankShape3VertexedClass *c_shape3vertexed;
  CrankShape3TPolyhedronClassPrivate *priv;

  c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);

  c_shape3vertexed->get_nvertices = crank_shape3_tpolyhedron_get_nvertices;
  c_shape3vertexed->get_nedges = crank_shape3_tpolyhedron_get_nedges;
  c_shape3vertexed->get_nfaces = crank_shape3_tpolyhedron_get_nfaces;

  c_shape3vertexed->get_vertex_edges = crank_shape3_tpolyhedron_get_vertex_edges;
  c_shape3vertexed->get_vertex_faces = crank_shape3_tpolyhedron_get_vertex_faces;
  c_shape3vertexed->get_edge_vertices = crank_shape3_tpolyhedron_get_edge_vertices;
  c_shape3vertexed->get_edge_faces = crank_shape3_tpolyhedron_get_edge_faces;
  c_shape3vertexed->get_face_vertices = crank_shape3_tpolyhedron_get_face_vertices;
  c_shape3vertexed->get_face_edges = crank_shape3_tpolyhedron_get_face_edges;

  priv = G_TYPE_CLASS_GET_PRIVATE (c,
                                   CRANK_TYPE_SHAPE3_TPOLYHEDRON,
                                   CrankShape3TPolyhedronClassPrivate);

  priv->t = NULL;
}


//////// CrankShape3Vertexed ///////////////////////////////////////////////////

static guint
crank_shape3_tpolyhedron_get_nvertices (CrankShape3Vertexed *shape)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  return crank_poly_struct3_get_nvertices (pstruct);
}

static guint
crank_shape3_tpolyhedron_get_nedges (CrankShape3Vertexed *shape)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  return crank_poly_struct3_get_nedges (pstruct);
}

static guint
crank_shape3_tpolyhedron_get_nfaces (CrankShape3Vertexed *shape)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  return crank_poly_struct3_get_nfaces (pstruct);
}

static guint*
crank_shape3_tpolyhedron_get_vertex_edges (CrankShape3Vertexed *shape,
                                           const guint          vid,
                                           guint               *neids)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  return crank_poly_struct3_get_vertex_edges (pstruct, vid, neids);
}

static guint*
crank_shape3_tpolyhedron_get_vertex_faces (CrankShape3Vertexed *shape,
                                           const guint          vid,
                                           guint               *nfids)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  return crank_poly_struct3_get_vertex_faces (pstruct, vid, nfids);
}

static void
crank_shape3_tpolyhedron_get_edge_vertices (CrankShape3Vertexed *shape,
                                            const guint          eid,
                                            guint               *vids)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  crank_poly_struct3_get_edge_vertices (pstruct, eid, vids);
}

static guint*
crank_shape3_tpolyhedron_get_edge_faces (CrankShape3Vertexed *shape,
                                         const guint          eid,
                                         guint               *nfids)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  return crank_poly_struct3_get_edge_faces (pstruct, eid, nfids);
}

static guint*
crank_shape3_tpolyhedron_get_face_vertices (CrankShape3Vertexed *shape,
                                            const guint          fid,
                                            guint               *nvids)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  return crank_poly_struct3_get_face_vertices (pstruct, fid, nvids);
}

static guint*
crank_shape3_tpolyhedron_get_face_edges (CrankShape3Vertexed *shape,
                                                 const guint          fid,
                                                 guint               *neids)
{
  CrankPolyStruct3 *pstruct = crank_shape3_tpolyhedron_get_template (shape);
  return crank_poly_struct3_get_face_edges (pstruct, fid, neids);
}


//////// Private functions /////////////////////////////////////////////////////

static CrankPolyStruct3*
crank_shape3_tpolyhedron_get_template (gpointer shape)
{
  CrankShape3TPolyhedronClass *c;
  CrankShape3TPolyhedronClassPrivate *cpriv;

  c = CRANK_SHAPE3_TPOLYHEDRON_GET_CLASS (shape);
  cpriv = G_TYPE_CLASS_GET_PRIVATE (c,
                                    CRANK_TYPE_SHAPE3_TPOLYHEDRON,
                                    CrankShape3TPolyhedronClassPrivate);

  return cpriv->t;
}


//////// Class Properties //////////////////////////////////////////////////////

/**
 * crank_shape3_tpolyhedron_class_get_template:
 * @c: Class
 *
 * Gets template for the class.
 *
 * Returns: (transfer none): Polygonal structure as template.
 */
CrankPolyStruct3*
crank_shape3_tpolyhedron_class_get_template (CrankShape3TPolyhedronClass *c)
{
  CrankShape3TPolyhedronClassPrivate *cpriv;

  cpriv = G_TYPE_CLASS_GET_PRIVATE (c,
                                    CRANK_TYPE_SHAPE3_TPOLYHEDRON,
                                    CrankShape3TPolyhedronClassPrivate);

  return cpriv->t;
}

/**
 * crank_shape3_tpolyhedron_class_set_template:
 * @c: Class
 * @t: (transfer none): Polygonal structure as template.
 *
 * Stage: Class initialization.
 *
 * Sets template for the class. A class should set template in its initialization.
 */
void
crank_shape3_tpolyhedron_class_set_template (CrankShape3TPolyhedronClass *c,
                                             CrankPolyStruct3            *t)
{
  CrankShape3TPolyhedronClassPrivate *cpriv;

  cpriv = G_TYPE_CLASS_GET_PRIVATE (c,
                                    CRANK_TYPE_SHAPE3_TPOLYHEDRON,
                                    CrankShape3TPolyhedronClassPrivate);

  if (cpriv->t != NULL)
    crank_poly_struct3_unref (cpriv->t);

  if (t != NULL)
    cpriv->t = crank_poly_struct3_ref (t);
  else
    cpriv->t = NULL;
}
