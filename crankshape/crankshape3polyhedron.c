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

#include "crankbox.h"
#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3polyhedron.h"


/**
 * SECTION: crankshape3polyhedron
 * @title: CrankShape3Polyhedron
 * @short_description: Polyhedron shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Represents polyhedron shape.
 *
 * # Abstract Functions left
 *
 * * #CrankShape3VertexedClass.get_nvertices()
 * * #CrankShape3VertexedClass.get_nedges()
 * * #CrankShape3VertexedClass.get_nfaces()
 * * #CrankShape3VertexedClass.get_vertex_pos()
 * * #CrankShape3VertexedClass.get_vertex_edges()
 * * #CrankShape3VertexedClass.get_vertex_faces()
 * * #CrankShape3VertexedClass.get_edge_vertices()
 * * #CrankShape3VertexedClass.get_edge_faces()
 * * #CrankShape3VertexedClass.get_face_winding()
 * * #CrankShape3VertexedClass.get_face_vertices()
 * * #CrankShape3VertexedClass.get_face_edges()
 * * #CrankShape3FiniteClass.is_convex()
 * * #CrankShape3FiniteClass.get_bound_radius()
 * * #CrankShape3Class.contains()
 *
 * # Virtual Functions
 *
 * * #CrankShape3PolyhedronClass.get_face_normal()
 * * #CrankShape3PolyhedronClass.get_normal_face()
 */

//////// List of virtual functions /////////////////////////////////////////////

static guint crank_shape3_polyhedron_get_dimension (CrankShape3Vertexed *shape);

static void crank_shape3_polyhedron_def_get_face_normal (CrankShape3Polyhedron *shape,
                                                          const guint             fid,
                                                          CrankVecFloat3         *nor);

static guint crank_shape3_polyhedron_def_get_normal_face (CrankShape3Polyhedron *shape,
                                                          CrankVecFloat3         *nor);


//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape3Polyhedron,
                        crank_shape3_polyhedron,
                        CRANK_TYPE_SHAPE3_VERTEXED)


//////// GTypeInstance /////////////////////////////////////////////////////////

void
crank_shape3_polyhedron_init (CrankShape3Polyhedron *self)
{

}

void
crank_shape3_polyhedron_class_init (CrankShape3PolyhedronClass *c)
{
  CrankShape3VertexedClass *c_shape3vertexed;

  c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);

  c_shape3vertexed->get_dimension = crank_shape3_polyhedron_get_dimension;

  c->get_face_normal = crank_shape3_polyhedron_def_get_face_normal;
  c->get_normal_face = crank_shape3_polyhedron_def_get_normal_face;
}

//////// CrankShape3Vertexed ///////////////////////////////////////////////////

static guint
crank_shape3_polyhedron_get_dimension (CrankShape3Vertexed *shape)
{
  return 3;
}

//////// Default Implementations ///////////////////////////////////////////////

static void
crank_shape3_polyhedron_def_get_face_normal (CrankShape3Polyhedron *shape,
                                              const guint             fid,
                                              CrankVecFloat3         *nor)
{
  CrankShape3Vertexed *vertexed;

  guint *vids;
  guint nvids;

  CrankVecFloat3 vert_a;
  CrankVecFloat3 vert_b;

  CrankVecFloat3 seg_a;
  CrankVecFloat3 seg_b;

  vertexed = (CrankShape3Vertexed*)shape;

  vids = crank_shape3_vertexed_get_face_vertices (vertexed, fid, &nvids);

  crank_shape3_vertexed_get_vertex_pos (vertexed, vids[0], &vert_a);
  crank_shape3_vertexed_get_vertex_pos (vertexed, vids[1], &vert_b);

  crank_vec_float3_sub (&vert_b, &vert_a, &seg_a);

  crank_shape3_vertexed_get_vertex_pos (vertexed, vids[2], &vert_a);

  crank_vec_float3_sub (&vert_a, &vert_b, &seg_b);

  crank_vec_float3_crs (&seg_a, &seg_b, nor);
  crank_vec_float3_unit_self (nor);
}

static guint
crank_shape3_polyhedron_def_get_normal_face (CrankShape3Polyhedron *shape,
                                              CrankVecFloat3         *nor)
{
  CrankShape3Vertexed *vertexed;

  guint vid;
  guint *fids;
  guint nfids;

  guint i;

  guint r;
  gfloat dot;
  CrankVecFloat3 facenor;

  vertexed = (CrankShape3Vertexed*)shape;

  vid = crank_shape3_vertexed_get_farthest_vertex (vertexed, nor);
  fids = crank_shape3_vertexed_get_vertex_faces (vertexed, vid, &nfids);

  r = fids[0];
  crank_shape3_polyhedron_get_face_normal (shape, r, &facenor);
  dot = crank_vec_float3_dot (nor, &facenor);

  for (i = 1; i < nfids; i++)
    {
      gfloat ndot;

      crank_shape3_polyhedron_get_face_normal (shape, fids[i], &facenor);
      ndot = crank_vec_float3_dot (nor, &facenor);

      if (dot < ndot)
        {
          r = fids[i];
          dot = ndot;
        }
    }
  return r;
}



//////// Face properties ///////////////////////////////////////////////////////

/**
 * crank_shape3_polyhedron_get_face_normal:
 * @shape: A Shape.
 * @fid: Face ID.
 * @nor: (out): Normal of face.
 *
 * Gets normal of face.
 */
void
crank_shape3_polyhedron_get_face_normal (CrankShape3Polyhedron *shape,
                                          const guint             fid,
                                          CrankVecFloat3         *nor)
{
  CrankShape3PolyhedronClass *c = CRANK_SHAPE3_POLYHEDRON_GET_CLASS (shape);

  c->get_face_normal (shape, fid, nor);
}


//////// Item picker ///////////////////////////////////////////////////////////

/**
 * crank_shape3_polyhedron_get_normal_face:
 * @shape: A Shape
 * @nor: Normal/
 *
 * Gets the face which normal is most towards to @nor in the polyhedron.
 *
 * Returns: A Face ID.
 */
guint
crank_shape3_polyhedron_get_normal_face (CrankShape3Polyhedron *shape,
                                          CrankVecFloat3         *nor)
{
  CrankShape3PolyhedronClass *c = CRANK_SHAPE3_POLYHEDRON_GET_CLASS (shape);

  return c->get_normal_face (shape, nor);
}
