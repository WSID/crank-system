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
#include "crankshape3polyhedron.h"

#include "crankshape3segment.h"


/**
 * SECTION: crankshape3segment
 * @title: CrankShape3Segment
 * @short_description: Segment in 3d space.
 * @stability: Unstable
 * @include: crankshape.h
 *
 *
 * A Segment in space.
 */

//////// List of virtual functions /////////////////////////////////////////////

static void     crank_shape3_segment_get_property (GObject    *object,
                                                   guint       prop_id,
                                                   GValue     *value,
                                                   GParamSpec *pspec);

static void     crank_shape3_segment_set_property (GObject      *object,
                                                   guint         prop_id,
                                                   const GValue *value,
                                                   GParamSpec   *pspec);


static gboolean crank_shape3_segment_contains (CrankShape3    *shape,
                                             CrankVecFloat3 *point);


static gboolean crank_shape3_segment_is_convex (CrankShape3Finite *shape);

static gfloat crank_shape3_segment_get_bound_radius (CrankShape3Finite *shape);


static guint crank_shape3_segment_get_nvertices (CrankShape3Vertexed *shape);

static guint crank_shape3_segment_get_nedges (CrankShape3Vertexed *shape);

static guint crank_shape3_segment_get_nfaces (CrankShape3Vertexed *shape);


static void crank_shape3_segment_get_vertex_pos (CrankShape3Vertexed *shape,
                                                const guint            vid,
                                                CrankVecFloat3        *pos);

static guint *crank_shape3_segment_get_vertex_edges (CrankShape3Vertexed *shape,
                                                   const guint            vid,
                                                   guint                 *neids);

static guint *crank_shape3_segment_get_vertex_faces (CrankShape3Vertexed *shape,
                                                   const guint            vid,
                                                   guint                 *nfids);


static void crank_shape3_segment_get_edge_vertices (CrankShape3Vertexed *shape,
                                                  const guint            eid,
                                                  guint                 *vids);

static guint *crank_shape3_segment_get_edge_faces (CrankShape3Vertexed *shape,
                                                   const guint          eid,
                                                   guint               *nfids);

static guint *crank_shape3_segment_get_face_vertices (CrankShape3Vertexed *shape,
                                                    const guint            fid,
                                                    guint                 *nvids);

static guint *crank_shape3_segment_get_face_edges (CrankShape3Vertexed *shape,
                                                 const guint            fid,
                                                 guint                 *neids);

static void crank_shape3_segment_get_face_normal (CrankShape3Vertexed *shape,
                                                const guint            fid,
                                                CrankVecFloat3        *nor);;

static guint crank_shape3_segment_get_farthest_vertex (CrankShape3Vertexed *shape,
                                                    CrankVecFloat3        *dir);

static guint crank_shape3_segment_get_normal_face (CrankShape3Vertexed *shape,
                                                CrankVecFloat3        *nor);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_LENGTH,
  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankShape3Segment {
  CrankShape3Vertexed _parent;

  gfloat  hlength;
};

G_DEFINE_TYPE (CrankShape3Segment,
               crank_shape3_segment,
               CRANK_TYPE_SHAPE3_VERTEXED)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void crank_shape3_segment_init (CrankShape3Segment *self)
{
}

static void crank_shape3_segment_class_init (CrankShape3SegmentClass *c)
{
  GObjectClass *c_gobject;
  CrankShape3Class *c_shape3;
  CrankShape3FiniteClass *c_shape3finite;
  CrankShape3VertexedClass *c_shape3vertexed;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape3_segment_get_property;
  c_gobject->set_property = crank_shape3_segment_set_property;

  pspecs[PROP_LENGTH] = g_param_spec_float ("length", "length", "length of segment.",
                                            0, G_MAXFLOAT, 1,
                                            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  c_shape3 = CRANK_SHAPE3_CLASS (c);

  c_shape3->contains = crank_shape3_segment_contains;

  c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);

  c_shape3finite->is_convex = crank_shape3_segment_is_convex;
  c_shape3finite->get_bound_radius = crank_shape3_segment_get_bound_radius;

  c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);

  c_shape3vertexed->get_nvertices = crank_shape3_segment_get_nvertices;
  c_shape3vertexed->get_nedges = crank_shape3_segment_get_nedges;
  c_shape3vertexed->get_nfaces = crank_shape3_segment_get_nfaces;
  c_shape3vertexed->get_vertex_pos = crank_shape3_segment_get_vertex_pos;
  c_shape3vertexed->get_vertex_edges = crank_shape3_segment_get_vertex_edges;
  c_shape3vertexed->get_vertex_faces = crank_shape3_segment_get_vertex_faces;
  c_shape3vertexed->get_face_vertices = crank_shape3_segment_get_face_vertices;
  c_shape3vertexed->get_face_edges = crank_shape3_segment_get_face_edges;
  c_shape3vertexed->get_farthest_vertex = crank_shape3_segment_get_farthest_vertex;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape3_segment_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  CrankShape3Segment *segment = CRANK_SHAPE3_SEGMENT (object);

  switch (prop_id)
    {
    case PROP_LENGTH:
      g_value_set_float (value, segment->hlength * 2.0f);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_shape3_segment_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  CrankShape3Segment *segment = CRANK_SHAPE3_SEGMENT (object);

  switch (prop_id)
    {
    case PROP_LENGTH:
      crank_shape3_segment_set_length (segment,
                                       g_value_get_float (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// CrankShape3 ///////////////////////////////////////////////////////////

static gboolean
crank_shape3_segment_contains (CrankShape3    *shape,
                             CrankVecFloat3 *point)
{
  CrankShape3Segment *self = CRANK_SHAPE3_SEGMENT (shape);
  return (- self->hlength <= point->x) &&
         (point->x <= self->hlength) &&
         (point->y == 0) &&
         (point->z == 0);
}


//////// CrankShape3Finite /////////////////////////////////////////////////////

static gboolean
crank_shape3_segment_is_convex (CrankShape3Finite *shape)
{
  return TRUE;
}

static gfloat
crank_shape3_segment_get_bound_radius (CrankShape3Finite *shape)
{
  CrankShape3Segment *self = CRANK_SHAPE3_SEGMENT (shape);
  return self->hlength;
}


//////// CrankShape3Vertexed /////////////////////////////////////////////////

static guint
crank_shape3_segment_get_nvertices (CrankShape3Vertexed *shape)
{
  return 2;
}

static guint
crank_shape3_segment_get_nedges (CrankShape3Vertexed *shape)
{
  return 1;
}

static guint
crank_shape3_segment_get_nfaces (CrankShape3Vertexed *shape)
{
  return 0;
}

static void
crank_shape3_segment_get_vertex_pos (CrankShape3Vertexed *shape,
                                   const guint            vid,
                                   CrankVecFloat3        *pos)
{
  CrankShape3Segment *self = CRANK_SHAPE3_SEGMENT (shape);
  switch (vid)
    {
    case 0:
      crank_vec_float3_init (pos,  self->hlength, 0.0f, 0.0f);
      break;

    case 1:
      crank_vec_float3_init (pos, -self->hlength, 0.0f, 0.0f);
      break;

    default:
      g_warning ("Invalid vertex id: %u", vid);
    }
}

static guint*
crank_shape3_segment_get_vertex_edges (CrankShape3Vertexed *shape,
                                     const guint            vid,
                                     guint                 *neids)
{
  if (vid == 0 || vid == 1)
    {
      *neids = 1;
      return g_new0 (guint, 1);
    }
  else
    {
      g_warning ("Invaild vertex id: %u", vid);
      *neids = 0;
      return NULL;
    }
}

static guint*
crank_shape3_segment_get_vertex_faces (CrankShape3Vertexed *shape,
                                     const guint            vid,
                                     guint                 *nfids)
{
  *nfids = 0;
  return NULL;
}


static void
crank_shape3_segment_get_edge_vertices (CrankShape3Vertexed *shape,
                                      const guint            eid,
                                      guint                 *vids)
{
  if (eid == 0)
    {
      vids[0] = 0;
      vids[1] = 1;
    }
  else
    {
      g_warning ("Invaild edge id: %u", eid);
    }
}

static guint*
crank_shape3_segment_get_edge_faces (CrankShape3Vertexed *shape,
                                   const guint            eid,
                                   guint                 *nfids)
{
  if (eid == 0)
    {
      *nfids = 0;
      return NULL;
    }
  else
    {
      g_warning ("Invaild edge id: %u", eid);
      *nfids = 0;
      return NULL;
    }
}

static guint*
crank_shape3_segment_get_face_vertices (CrankShape3Vertexed *shape,
                                      const guint            fid,
                                      guint                 *nvids)
{
  g_warning ("This shape has no face.");
  *nvids = 0;
  return NULL;
}

static guint*
crank_shape3_segment_get_face_edges (CrankShape3Vertexed *shape,
                                   const guint            fid,
                                   guint                 *neids)
{
  g_warning ("This shape has no face.");
  *neids = 0;
  return NULL;
}

static guint
crank_shape3_segment_get_farthest_vertex (CrankShape3Vertexed *shape,
                                        CrankVecFloat3        *dir)
{
  return (dir->x < 0) ? 1 : 0;
}


//////// Constructor ///////////////////////////////////////////////////////////

CrankShape3Segment*
crank_shape3_segment_new (const gfloat length)
{
  return (CrankShape3Segment*) g_object_new (CRANK_TYPE_SHAPE3_SEGMENT,
                                             "length", length,
                                             NULL);
}


//////// Property getter/setter ////////////////////////////////////////////////

gfloat
crank_shape3_segment_get_length (CrankShape3Segment *shape)
{
  return shape->hlength * 2.0f;
}

void
crank_shape3_segment_set_length(CrankShape3Segment *shape,
                                const gfloat        length)
{
  shape->hlength = length * 0.5f;

  g_object_notify ((GObject*)shape, "bound-radius");
  g_object_notify_by_pspec ((GObject*)shape, pspecs[PROP_LENGTH]);
}
