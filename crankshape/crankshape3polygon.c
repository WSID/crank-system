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
#include "crankrotation.h"
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2vertexed.h"
#include "crankshape2polygon.h"
#include "crankshape2cpolygon.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polygon.h"

/**
 * SECTION: crankshape3polygon
 * @title: CrankShape3Polygon
 * @short_description: Base class for polygonal shape.
 * @stability: unstable
 * @include: crankshape.h
 *
 * Base class for polygonal shape.
 *
 * # Abstract Functions
 *
 * * #CrankShape3Polygon.get_winding()
 * * #CrankShape3Polygon.get_vertex_pos2()
 *
 * # Abstract Functions left
 *
 * * #CrankShape3VertexedClass.get_nvertices()
 * * #CrankShape3FiniteClass.get_bound_radius()
 * * #CrankShape3Class.contains()
 *
 * # Virtual functions
 *
 * * #CrankShape3Polygon.get_edge_normal()
 * * #CrankShape3Polygon.get_normal_edge()
 *
 */

//////// List of virtual functions /////////////////////////////////////////////

static void crank_shape3_polygon_get_property (GObject    *object,
                                               guint       prop_id,
                                               GValue     *value,
                                               GParamSpec *pspec);

static gboolean crank_shape3_polygon_is_convex (CrankShape3Finite *shape);


static guint crank_shape3_polygon_get_dimension (CrankShape3Vertexed *shape);

static guint crank_shape3_polygon_get_nedges (CrankShape3Vertexed *shape);

static guint crank_shape3_polygon_get_nfaces (CrankShape3Vertexed *shape);

static void  crank_shape3_polygon_get_vertex_pos (CrankShape3Vertexed *shape,
                                                  const guint          vid,
                                                  CrankVecFloat3      *pos);

static guint* crank_shape3_polygon_get_vertex_edges (CrankShape3Vertexed *shape,
                                                     const guint          vid,
                                                     guint               *neids);

static guint* crank_shape3_polygon_get_vertex_faces (CrankShape3Vertexed *shape,
                                                     const guint          vid,
                                                     guint               *nfids);

static void crank_shape3_polygon_get_edge_vertices (CrankShape3Vertexed *shape,
                                                    const guint          eid,
                                                    guint               *vids);

static guint* crank_shape3_polygon_get_edge_faces (CrankShape3Vertexed *shape,
                                                 const guint          eid,
                                                 guint               *nfids);

static CrankWinding crank_shape3_polygon_get_face_winding (CrankShape3Vertexed *shape,
                                                           const guint          fid);

static guint *crank_shape3_polygon_get_face_vertices (CrankShape3Vertexed *shape,
                                                      const guint          fid,
                                                      guint               *nvids);

static guint *crank_shape3_polygon_get_face_edges (CrankShape3Vertexed *shape,
                                                   const guint          fid,
                                                   guint               *neids);

static CrankShape2Polygon *crank_shape3_polygon_get_face_as_shape (CrankShape3Vertexed *shape,
                                                                   const guint          fid,
                                                                   CrankTrans3         *pos);

static guint crank_shape3_polygon_get_farthest_vertex (CrankShape3Vertexed *shape,
                                                       CrankVecFloat3      *dir);

//////// Default Implementaion /////////////////////////////////////////////////

static void crank_shape3_polygon_def_get_edge_normal (CrankShape3Polygon *shape,
                                                      guint               eid,
                                                      CrankVecFloat2     *normal);

static guint crank_shape3_polygon_def_get_normal_edge (CrankShape3Polygon *shape,
                                                       CrankVecFloat2     *normal);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_WINDING,
  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape3Polygon,
                        crank_shape3_polygon,
                        CRANK_TYPE_SHAPE3_VERTEXED)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_polygon_init (CrankShape3Polygon *self)
{
}

static void
crank_shape3_polygon_class_init (CrankShape3PolygonClass *c)
{
  GObjectClass *c_gobject;
  CrankShape3FiniteClass *c_shape3finite;
  CrankShape3VertexedClass *c_shape3vertexed;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape3_polygon_get_property;

  pspecs[PROP_WINDING] = g_param_spec_enum (
      "winding", "winding", "winding of vertices list",
      CRANK_TYPE_WINDING, CRANK_WINDING_NONE,
      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);

  c_shape3finite->is_convex = crank_shape3_polygon_is_convex;


  c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);

  c_shape3vertexed->get_dimension = crank_shape3_polygon_get_dimension;
  c_shape3vertexed->get_nedges = crank_shape3_polygon_get_nedges;
  c_shape3vertexed->get_nfaces = crank_shape3_polygon_get_nfaces;
  c_shape3vertexed->get_vertex_pos = crank_shape3_polygon_get_vertex_pos;
  c_shape3vertexed->get_vertex_edges = crank_shape3_polygon_get_vertex_edges;
  c_shape3vertexed->get_vertex_faces = crank_shape3_polygon_get_vertex_faces;
  c_shape3vertexed->get_edge_vertices = crank_shape3_polygon_get_edge_vertices;
  c_shape3vertexed->get_edge_faces = crank_shape3_polygon_get_edge_faces;
  c_shape3vertexed->get_face_winding = crank_shape3_polygon_get_face_winding;
  c_shape3vertexed->get_face_vertices = crank_shape3_polygon_get_face_vertices;
  c_shape3vertexed->get_face_edges = crank_shape3_polygon_get_face_edges;
  c_shape3vertexed->get_face_as_shape = crank_shape3_polygon_get_face_as_shape;
  c_shape3vertexed->get_farthest_vertex = crank_shape3_polygon_get_farthest_vertex;


  c->get_edge_normal = crank_shape3_polygon_def_get_edge_normal;
  c->get_normal_edge = crank_shape3_polygon_def_get_normal_edge;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape3_polygon_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  CrankShape3Polygon *self = (CrankShape3Polygon*)object;

  switch (prop_id)
    {
    case PROP_WINDING:
      g_value_set_enum (value, crank_shape3_polygon_get_winding (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


//////// CrankShape3Finite /////////////////////////////////////////////////////

static gboolean
crank_shape3_polygon_is_convex (CrankShape3Finite *shape)
{
  CrankShape3Vertexed *self_vertexed = (CrankShape3Vertexed*)shape;
  CrankShape3Polygon *self = (CrankShape3Polygon*)shape;

  guint i, n;

  CrankVecFloat2 cvert[3];
  CrankVecFloat2 seg[2];
  gfloat crs;

  n = crank_shape3_vertexed_get_nvertices (self_vertexed);

  if (n < 4) return TRUE;

  crank_shape3_polygon_get_vertex_pos2 (self, 0, cvert + 0);
  crank_shape3_polygon_get_vertex_pos2 (self, 1, cvert + 1);
  crank_shape3_polygon_get_vertex_pos2 (self, 2, cvert + 2);

  crank_vec_float2_sub (cvert + 1, cvert + 0, seg + 0);
  crank_vec_float2_sub (cvert + 2, cvert + 1, seg + 1);

  crs = crank_vec_float2_crs (seg + 0, seg + 1);

  for (i = 3; i < n; i++)
    {
      gfloat vcrs;
      crank_shape3_polygon_get_vertex_pos2 (self, i, cvert + (i % 3));
      crank_vec_float2_sub (cvert + 1, cvert + 0, seg + 0);
      crank_vec_float2_sub (cvert + 2, cvert + 1, seg + 1);
      vcrs = crank_vec_float2_crs (seg + 0, seg + 1);

      if (crs * vcrs < 0) return FALSE;
    }

  return TRUE;
}


//////// CrankShape3Vertexed ///////////////////////////////////////////////////

static guint
crank_shape3_polygon_get_dimension (CrankShape3Vertexed *shape)
{
  return 2;
}

static guint
crank_shape3_polygon_get_nedges (CrankShape3Vertexed *shape)
{
  return crank_shape3_vertexed_get_nvertices (shape);
}

static guint
crank_shape3_polygon_get_nfaces (CrankShape3Vertexed *shape)
{
  return 1;
}

static void
crank_shape3_polygon_get_vertex_pos (CrankShape3Vertexed *shape,
                                     const guint          vid,
                                     CrankVecFloat3      *pos)
{
  crank_shape3_polygon_get_vertex_pos2 ((CrankShape3Polygon*)shape,
                                        vid,
                                        (CrankVecFloat2*)pos);
  pos->z = 0;
}

static guint*
crank_shape3_polygon_get_vertex_edges (CrankShape3Vertexed *shape,
                                       const guint          vid,
                                       guint               *neids)
{
  guint n = crank_shape3_vertexed_get_nvertices (shape);

  guint *res = g_new (guint, 2);
  res[0] = (vid == 0) ? (n - 1) : (vid - 1);
  res[1] = vid;

  *neids = 2;

  return res;
}

static guint*
crank_shape3_polygon_get_vertex_faces (CrankShape3Vertexed *shape,
                                       const guint          vid,
                                       guint               *nfids)
{
  guint *res = g_new (guint, 1);
  res[0] = 0;

  *nfids = 1;
  return res;
}

static void
crank_shape3_polygon_get_edge_vertices (CrankShape3Vertexed *shape,
                                        const guint          eid,
                                        guint               *vids)
{
  guint n = crank_shape3_vertexed_get_nvertices (shape);

  vids[0] = eid;
  vids[1] = (eid == (n - 1)) ? 0 : (eid + 1);
}

static guint*
crank_shape3_polygon_get_edge_faces (CrankShape3Vertexed *shape,
                                     const guint          eid,
                                     guint               *nfids)
{
  guint n = crank_shape3_vertexed_get_nedges (shape);

  if (eid < n)
    {
      guint *fids = g_new (guint, 1);

      fids[0] = 0;

      *nfids = 1;
      return fids;
    }
  else
    {
      g_message ("Invalid edge id: %u", eid);
      *nfids = 0;
      return NULL;
    }
}

static guint*
crank_shape3_polygon_get_face_vertices (CrankShape3Vertexed *shape,
                                        const guint          fid,
                                        guint               *nvids)
{
  guint n = crank_shape3_vertexed_get_nvertices (shape);
  guint i;

  guint *res = g_new (guint, n);

  for (i = 0; i < n; i++)
    res[i] = i;

  *nvids = n;
  return res;
}

static CrankWinding
crank_shape3_polygon_get_face_winding (CrankShape3Vertexed *shape,
                                       const guint          fid)
{
  CrankShape3Polygon *self = (CrankShape3Polygon*) shape;

  if (fid != 0)
    {
      g_warning ("Invalid Face ID: %u", fid);
      return CRANK_WINDING_NONE;
    }

  return crank_shape3_polygon_get_winding (self);
}

static guint*
crank_shape3_polygon_get_face_edges (CrankShape3Vertexed *shape,
                                     const guint          fid,
                                     guint               *neids)
{
  guint n = crank_shape3_vertexed_get_nvertices (shape);
  guint i;

  guint *res = g_new (guint, n);

  for (i = 0; i < n; i++)
    res[i] = i;

  *neids = n;
  return res;
}

static CrankShape2Polygon*
crank_shape3_polygon_get_face_as_shape (CrankShape3Vertexed *shape,
                                        const guint          fid,
                                        CrankTrans3         *pos)
{
  CrankShape3Polygon *self = CRANK_SHAPE3_POLYGON (shape);
  CrankShape2CPolygon *cpolygon;

  guint n = crank_shape3_vertexed_get_nvertices (shape);
  guint i;

  CrankVecFloat2 *vertices;

  vertices = g_new (CrankVecFloat2, n);

  for (i = 0; i < n; i++)
    crank_shape3_polygon_get_vertex_pos2 (self, i, vertices + i);

  cpolygon = crank_shape2_cpolygon_new (vertices, n);

  g_free (vertices);
  return (CrankShape2Polygon*)cpolygon;
}

static guint
crank_shape3_polygon_get_farthest_vertex (CrankShape3Vertexed *shape,
                                          CrankVecFloat3      *dir)
{
  CrankShape3Polygon *self = (CrankShape3Polygon*)shape;
  CrankVecFloat2 *dir2 = (CrankVecFloat2*)dir;

  guint n = crank_shape3_vertexed_get_nvertices (shape);
  guint i;
  guint j;

  CrankVecFloat2 vertex;
  gfloat dot;

  crank_shape3_polygon_get_vertex_pos2 (self, 0, &vertex);
  j = 0;
  dot = crank_vec_float2_dot (dir2, &vertex);

  for (i = 1; i < n; i++)
    {
      gfloat ndot;

      crank_shape3_polygon_get_vertex_pos2 (self, i, &vertex);
      ndot = crank_vec_float2_dot (dir2, &vertex);

      if (dot < ndot)
        {
          dot = ndot;
          j = i;
        }
    }

  return j;

}

//////// Default Implementations ///////////////////////////////////////////////

static void
crank_shape3_polygon_def_get_edge_normal (CrankShape3Polygon *shape,
                                          guint               eid,
                                          CrankVecFloat2     *normal)
{
  CrankShape3Vertexed *shape_vertexed = (CrankShape3Vertexed*) shape;
  guint eidn;
  CrankVecFloat2 vertex[2];
  CrankVecFloat2 seg;

  eidn = (eid + 1) % crank_shape3_vertexed_get_nvertices (shape_vertexed);

  crank_shape3_polygon_get_vertex_pos2 (shape, eid, vertex + 0);
  crank_shape3_polygon_get_vertex_pos2 (shape, eidn, vertex + 1);

  crank_vec_float2_sub (vertex + 1, vertex + 0, &seg);

  crank_rot_vec2_right (&seg, normal);
  crank_vec_float2_unit_self (normal);
}

static guint
crank_shape3_polygon_def_get_normal_edge (CrankShape3Polygon *shape,
                                          CrankVecFloat2     *normal)
{
  CrankShape3Vertexed *shape_vertexed = (CrankShape3Vertexed*) shape;
  guint nvertices;
  guint vert_p;
  guint vert;
  guint vert_n;

  CrankVecFloat3 normal3;

  CrankVecFloat2 vp_p;
  CrankVecFloat2 vp;
  CrankVecFloat2 vp_n;

  CrankVecFloat2 seg_a;
  CrankVecFloat2 seg_b;

  gfloat dot_a;
  gfloat dot_b;

  crank_vec_float3_init (& normal3, normal->x, normal->y, 0);

  nvertices = crank_shape3_vertexed_get_nvertices (shape_vertexed);
  vert = crank_shape3_vertexed_get_farthest_vertex (shape_vertexed, &normal3);

  vert_p = ((vert != 0) ? vert  : nvertices) - 1;
  vert_n = vert + 1;

  vert_n = (vert_n != nvertices) ? vert_n : 0;

  crank_shape3_polygon_get_vertex_pos2 (shape, vert_p, &vp_p);
  crank_shape3_polygon_get_vertex_pos2 (shape, vert, &vp);
  crank_shape3_polygon_get_vertex_pos2 (shape, vert_n, &vp_n);

  crank_vec_float2_sub (&vp, &vp_p, &seg_a);
  crank_vec_float2_sub (&vp_n, &vp, &seg_b);

  dot_a = crank_vec_float2_dot (&seg_a, &vp_p) / crank_vec_float2_get_magn (&seg_a);
  dot_b = crank_vec_float2_dot (&seg_b, &vp_p) / crank_vec_float2_get_magn (&seg_b);

  return (dot_a < dot_b) ? vert_p : vert;
}

//////// Shape Properties //////////////////////////////////////////////////////

CrankWinding
crank_shape3_polygon_get_winding (CrankShape3Polygon *shape)
{
  CrankShape3PolygonClass *c = CRANK_SHAPE3_POLYGON_GET_CLASS (shape);

  return c->get_winding (shape);
}



//////// VFunc Wrappers ////////////////////////////////////////////////////////

void
crank_shape3_polygon_get_vertex_pos2 (CrankShape3Polygon *shape,
                                      guint               vid,
                                      CrankVecFloat2     *pos)
{
  CrankShape3PolygonClass *c = CRANK_SHAPE3_POLYGON_GET_CLASS (shape);

  c->get_vertex_pos2 (shape, vid, pos);
}

void
crank_shape3_polygon_get_edge_normal (CrankShape3Polygon *shape,
                                      guint               eid,
                                      CrankVecFloat2     *normal)
{
  CrankShape3PolygonClass *c = CRANK_SHAPE3_POLYGON_GET_CLASS (shape);

  c->get_edge_normal (shape, eid, normal);
}

guint
crank_shape3_polygon_get_normal_edge (CrankShape3Polygon *shape,
                                      CrankVecFloat2     *normal)
{
  CrankShape3PolygonClass *c = CRANK_SHAPE3_POLYGON_GET_CLASS (shape);

  return c->get_normal_edge (shape, normal);
}
