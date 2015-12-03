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
#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polyhedron.h"
#include "crankshape3tetrahedron.h"

static guint assoc_ve[4][3] =
{
    {2, 0, 3},
    {0, 1, 4},
    {1, 2, 5},
    {3, 4, 5}
};

static guint assoc_vf[4][3] =
{
    {0, 1, 3},
    {0, 2, 1},
    {0, 3, 2},
    {1, 2, 3}
};

static guint assoc_ev[6][2] =
{
    {0, 1}, {1, 2}, {2, 0},
    {0, 3}, {1, 3}, {2, 3}
};

static guint assoc_ef[6][2] =
{
    {0, 1}, {0, 2}, {0, 3},
    {3, 1}, {1, 2}, {2, 3}
};

static guint assoc_fv[4][3] =
{
    {0, 2, 1},
    {0, 1, 3},
    {1, 2, 3},
    {2, 0, 3}
};

static guint assoc_fe[4][3] =
{
    {0, 2, 1},
    {0, 4, 3},
    {1, 5, 4},
    {2, 3, 5}
};


//////// List of virtual functions /////////////////////////////////////////////

static gboolean crank_shape3_tetrahedron_contains (CrankShape3    *shape,
                                                   CrankVecFloat3 *point);

static gboolean crank_shape3_tetrahedron_is_convex (CrankShape3Finite *shape);

static gfloat   crank_shape3_tetrahedron_get_bound_radius (CrankShape3Finite *shape);

static guint    crank_shape3_tetrahedron_get_nvertices (CrankShape3Vertexed *shape);

static guint    crank_shape3_tetrahedron_get_nedges (CrankShape3Vertexed *shape);

static guint    crank_shape3_tetrahedron_get_nfaces (CrankShape3Vertexed *shape);

static guint   *crank_shape3_tetrahedron_get_vertex_edges (CrankShape3Vertexed *shape,
                                                           const guint          vid,
                                                           guint               *neids);

static guint   *crank_shape3_tetrahedron_get_vertex_faces (CrankShape3Vertexed *shape,
                                                           const guint          vid,
                                                           guint               *nfids);

static void     crank_shape3_tetrahedron_get_edge_vertices (CrankShape3Vertexed *shape,
                                                            const guint          eid,
                                                            guint               *vids);

static void     crank_shape3_tetrahedron_get_edge_faces (CrankShape3Vertexed *shape,
                                                         const guint          eid,
                                                         guint               *eids);

static CrankWinding crank_shape3_tetrahedron_get_face_winding (CrankShape3Vertexed *shape,
                                                               const guint          fid);

static guint   *crank_shape3_tetrahedron_get_face_vertices (CrankShape3Vertexed *shape,
                                                            const guint          fid,
                                                            guint               *nvids);

static guint   *crank_shape3_tetrahedron_get_face_edges (CrankShape3Vertexed *shape,
                                                         const guint          fid,
                                                         guint               *neids);
//////// Type definition ///////////////////////////////////////////////////////

struct _CrankShape3Tetrahedron {
  CrankShape3Polyhedron _parent;

  CrankVecFloat3 vertices[4];
  CrankWinding   winding[4];
};

G_DEFINE_TYPE (CrankShape3Tetrahedron,
               crank_shape3_tetrahedron,
               CRANK_TYPE_SHAPE3_POLYHEDRON)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_tetrahedron_init (CrankShape3Tetrahedron *self)
{
}

static void
crank_shape3_tetrahedron_class_init (CrankShape3TetrahedronClass *c)
{
  CrankShape3Class *c_shape3 = CRANK_SHAPE3_CLASS (c);
  CrankShape3FiniteClass *c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);
  CrankShape3VertexedClass *c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);

  c_shape3->contains = crank_shape3_tetrahedron_contains;

  c_shape3finite->is_convex = crank_shape3_tetrahedron_is_convex;
  c_shape3finite->get_bound_radius = crank_shape3_tetrahedron_get_bound_radius;

  c_shape3vertexed->get_nvertices = crank_shape3_tetrahedron_get_nvertices;
  c_shape3vertexed->get_nedges = crank_shape3_tetrahedron_get_nedges;
  c_shape3vertexed->get_nfaces = crank_shape3_tetrahedron_get_nfaces;
  c_shape3vertexed->get_vertex_edges = crank_shape3_tetrahedron_get_vertex_edges;
  c_shape3vertexed->get_vertex_faces = crank_shape3_tetrahedron_get_vertex_faces;
  c_shape3vertexed->get_edge_vertices = crank_shape3_tetrahedron_get_edge_vertices;
  c_shape3vertexed->get_edge_faces = crank_shape3_tetrahedron_get_edge_faces;
  c_shape3vertexed->get_face_winding = crank_shape3_tetrahedron_get_face_winding;
  c_shape3vertexed->get_face_vertices = crank_shape3_tetrahedron_get_face_vertices;
  c_shape3vertexed->get_face_edges = crank_shape3_tetrahedron_get_face_edges;
}

//////// CrankShape3 ///////////////////////////////////////////////////////////

static gboolean
crank_shape3_tetrahedron_contains (CrankShape3    *shape,
                                   CrankVecFloat3 *point)
{
  CrankShape3Tetrahedron *self = (CrankShape3Tetrahedron*)shape;

  return crank_tetra_contains (self->vertices, point);
}


//////// CrankShape3Finite /////////////////////////////////////////////////////

static gboolean
crank_shape3_tetrahedron_is_convex (CrankShape3Finite *shape)
{
  return TRUE;
}


static gfloat
crank_shape3_tetrahedron_get_bound_radius (CrankShape3Finite *shape)
{
  CrankShape3Tetrahedron *self = (CrankShape3Tetrahedron*)shape;
  gfloat r[4];

  r[0] = crank_vec_float3_get_magn_sq (self->vertices + 0);
  r[1] = crank_vec_float3_get_magn_sq (self->vertices + 1);
  r[2] = crank_vec_float3_get_magn_sq (self->vertices + 2);
  r[3] = crank_vec_float3_get_magn_sq (self->vertices + 3);

  r[0] = MAX (r[0], r[1]);
  r[0] = MAX (r[0], r[2]);
  r[0] = MAX (r[0], r[3]);

  return sqrtf (r[0]);
}

//////// CrankShape3Vertexed ///////////////////////////////////////////////////

static guint
crank_shape3_tetrahedron_get_nvertices (CrankShape3Vertexed *shape)
{
  return 4;
}


static guint
crank_shape3_tetrahedron_get_nedges (CrankShape3Vertexed *shape)
{
  return 6;
}

static guint
crank_shape3_tetrahedron_get_nfaces (CrankShape3Vertexed *shape)
{
  return 4;
}

static guint*
crank_shape3_tetrahedron_get_vertex_edges (CrankShape3Vertexed *shape,
                                           const guint          vid,
                                           guint               *neids)
{
  *neids = 3;
  return g_memdup (assoc_ve[vid], sizeof(guint) * 3);
}

static guint*
crank_shape3_tetrahedron_get_vertex_faces (CrankShape3Vertexed *shape,
                                           const guint          vid,
                                           guint               *nfids)
{
  *nfids = 3;
  return g_memdup (assoc_vf[vid], sizeof(guint) * 3);
}

static void
crank_shape3_tetrahedron_get_edge_vertices (CrankShape3Vertexed *shape,
                                            const guint          eid,
                                            guint               *vids)
{
  vids[0] = assoc_ev[eid][0];
  vids[1] = assoc_ev[eid][1];
}

static void
crank_shape3_tetrahedron_get_edge_faces (CrankShape3Vertexed *shape,
                                         const guint          eid,
                                         guint               *fids)
{
  fids[0] = assoc_fv[eid][0];
  fids[1] = assoc_fv[eid][1];
}

static CrankWinding
crank_shape3_tetrahedron_get_face_winding (CrankShape3Vertexed *shape,
                                           const guint          fid)
{
  CrankShape3Tetrahedron *self = (CrankShape3Tetrahedron*)shape;
  return self->winding[fid];
}

static guint*
crank_shape3_tetrahedron_get_face_vertices (CrankShape3Vertexed *shape,
                                            const guint          fid,
                                            guint               *nvids)
{
  *nvids = 3;
  return g_memdup (assoc_fv[fid], sizeof(guint) * 3);
}

static guint*
crank_shape3_tetrahedron_get_face_edges (CrankShape3Vertexed *shape,
                                         const guint          fid,
                                         guint               *neids)
{
  *neids = 3;
  return g_memdup (assoc_fe[fid], sizeof(guint) * 3);
}


//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_shape3_tetrahedron_new:
 * @vertices: (array fixed-size=4): Vertices.
 *
 * Constructs a tetrahedron shape.
 *
 * Returns: (transfer full): Newly constructed shape.
 */
CrankShape3Tetrahedron*
crank_shape3_tetrahedron_new (CrankVecFloat3 *vertices)
{
  CrankShape3Tetrahedron *self;

  self = (CrankShape3Tetrahedron*) g_object_new (CRANK_TYPE_SHAPE3_TETRAHEDRON,
                                                 NULL);

  memcpy (self->vertices, vertices, sizeof (CrankVecFloat3) * 4);
  self->winding[0] = crank_winding_from_points_against (vertices + 0,
                                                        vertices + 2,
                                                        vertices + 1,
                                                        vertices + 3);

  self->winding[1] = crank_winding_from_points_against (vertices + 0,
                                                        vertices + 1,
                                                        vertices + 3,
                                                        vertices + 2);

  self->winding[2] = crank_winding_from_points_against (vertices + 1,
                                                        vertices + 2,
                                                        vertices + 3,
                                                        vertices + 0);

  self->winding[3] = crank_winding_from_points_against (vertices + 2,
                                                        vertices + 0,
                                                        vertices + 3,
                                                        vertices + 1);

  return self;
}
