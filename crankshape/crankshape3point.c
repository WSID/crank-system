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
#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"

#include "crankshape3point.h"


/**
 * SECTION: crankshape3point
 * @title: CrankShape3Point
 * @short_description: Point in 3d space.
 * @stability: Unstable
 * @include: crankshape.h
 *
 *
 * A Point in space.
 */

//////// List of virtual functions /////////////////////////////////////////////

static gboolean crank_shape3_point_contains (CrankShape3    *shape,
                                             CrankVecFloat3 *point);


static gboolean crank_shape3_point_is_convex (CrankShape3Finite *shape);

static gfloat crank_shape3_point_get_bound_radius (CrankShape3Finite *shape);


static guint crank_shape3_point_get_nvertices (CrankShape3Vertexed *shape);

static guint crank_shape3_point_get_nedges (CrankShape3Vertexed *shape);

static guint crank_shape3_point_get_nfaces (CrankShape3Vertexed *shape);


static void crank_shape3_point_get_vertex_pos (CrankShape3Vertexed *shape,
                                                const guint            vid,
                                                CrankVecFloat3        *pos);

static guint *crank_shape3_point_get_vertex_edges (CrankShape3Vertexed *shape,
                                                   const guint            vid,
                                                   guint                 *neids);

static guint *crank_shape3_point_get_vertex_faces (CrankShape3Vertexed *shape,
                                                   const guint            vid,
                                                   guint                 *nfids);


static void crank_shape3_point_get_edge_vertices (CrankShape3Vertexed *shape,
                                                  const guint            eid,
                                                  guint                 *vids);

static void crank_shape3_point_get_edge_faces (CrankShape3Vertexed *shape,
                                               const guint            eid,
                                               guint                 *fids);

static guint *crank_shape3_point_get_face_vertices (CrankShape3Vertexed *shape,
                                                    const guint            fid,
                                                    guint                 *nvids);

static guint *crank_shape3_point_get_face_edges (CrankShape3Vertexed *shape,
                                                 const guint            fid,
                                                 guint                 *neids);

static void crank_shape3_point_get_face_normal (CrankShape3Vertexed *shape,
                                                const guint            fid,
                                                CrankVecFloat3        *nor);;

static guint crank_shape3_point_get_farthest_vertex (CrankShape3Vertexed *shape,
                                                    CrankVecFloat3        *dir);

static guint crank_shape3_point_get_normal_face (CrankShape3Vertexed *shape,
                                                CrankVecFloat3        *nor);


//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankShape3Point {
  CrankShape3Vertexed _parent;
};

G_DEFINE_TYPE (CrankShape3Point,
               crank_shape3_point,
               CRANK_TYPE_SHAPE3_VERTEXED)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void crank_shape3_point_init (CrankShape3Point *self)
{
}

static void crank_shape3_point_class_init (CrankShape3PointClass *c)
{
  CrankShape3Class *c_shape3;
  CrankShape3FiniteClass *c_shape3finite;
  CrankShape3VertexedClass *c_shape3vertexed;

  c_shape3 = CRANK_SHAPE3_CLASS (c);

  c_shape3->contains = crank_shape3_point_contains;

  c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);

  c_shape3finite->is_convex = crank_shape3_point_is_convex;
  c_shape3finite->get_bound_radius = crank_shape3_point_get_bound_radius;

  c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);

  c_shape3vertexed->get_nvertices = crank_shape3_point_get_nvertices;
  c_shape3vertexed->get_nedges = crank_shape3_point_get_nedges;
  c_shape3vertexed->get_nfaces = crank_shape3_point_get_nfaces;
  c_shape3vertexed->get_vertex_pos = crank_shape3_point_get_vertex_pos;
  c_shape3vertexed->get_vertex_edges = crank_shape3_point_get_vertex_edges;
  c_shape3vertexed->get_vertex_faces = crank_shape3_point_get_vertex_faces;
  c_shape3vertexed->get_face_vertices = crank_shape3_point_get_face_vertices;
  c_shape3vertexed->get_face_edges = crank_shape3_point_get_face_edges;
  c_shape3vertexed->get_farthest_vertex = crank_shape3_point_get_farthest_vertex;
}

//////// CrankShape3 ///////////////////////////////////////////////////////////

static gboolean
crank_shape3_point_contains (CrankShape3    *shape,
                             CrankVecFloat3 *point)
{
  return (point->x == 0) && (point->y == 0) && (point->z == 0);
}


//////// CrankShape3Finite /////////////////////////////////////////////////////

static gboolean
crank_shape3_point_is_convex (CrankShape3Finite *shape)
{
  return TRUE;
}

static gfloat
crank_shape3_point_get_bound_radius (CrankShape3Finite *shape)
{
  return 0;
}


//////// CrankShape3Vertexed /////////////////////////////////////////////////

static guint
crank_shape3_point_get_nvertices (CrankShape3Vertexed *shape)
{
  return 1;
}

static guint
crank_shape3_point_get_nedges (CrankShape3Vertexed *shape)
{
  return 0;
}

static guint
crank_shape3_point_get_nfaces (CrankShape3Vertexed *shape)
{
  return 0;
}

static void
crank_shape3_point_get_vertex_pos (CrankShape3Vertexed *shape,
                                   const guint            vid,
                                   CrankVecFloat3        *pos)
{
  if (vid != 0)
    g_warning ("Invalid Vertex ID: %u", vid);
  else
    crank_vec_float3_init (pos, 0.0f, 0.0f, 0.0f);
}

static guint*
crank_shape3_point_get_vertex_edges (CrankShape3Vertexed *shape,
                                     const guint            vid,
                                     guint                 *neids)
{
  *neids = 0;
  return NULL;
}

static guint*
crank_shape3_point_get_vertex_faces (CrankShape3Vertexed *shape,
                                     const guint            vid,
                                     guint                 *nfids)
{
  *nfids = 0;
  return NULL;
}


static void
crank_shape3_point_get_edge_vertices (CrankShape3Vertexed *shape,
                                      const guint            eid,
                                      guint                 *vids)
{
  g_warning ("This shape has no edge.");
}

static void
crank_shape3_point_get_edge_faces (CrankShape3Vertexed *shape,
                                   const guint            eid,
                                   guint                 *fids)
{
  g_warning ("This shape has no face.");
}

static guint*
crank_shape3_point_get_face_vertices (CrankShape3Vertexed *shape,
                                      const guint            fid,
                                      guint                 *nvids)
{
  g_warning ("This shape has no face.");
  *nvids = 0;
  return NULL;
}

static guint*
crank_shape3_point_get_face_edges (CrankShape3Vertexed *shape,
                                   const guint            fid,
                                   guint                 *neids)
{
  g_warning ("This shape has no face.");
  *neids = 0;
  return NULL;
}

static guint
crank_shape3_point_get_farthest_vertex (CrankShape3Vertexed *shape,
                                        CrankVecFloat3        *dir)
{
  return 0;
}



//////// Constructor ///////////////////////////////////////////////////////////

CrankShape3Point*
crank_shape3_point_new (void)
{
  return (CrankShape3Point*) g_object_new (CRANK_TYPE_SHAPE3_POINT, NULL);
}
