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

#include <math.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankbox.h"
#include "cranktrans.h"

#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2vertexed.h"

#include "crankshape2cpolygon.h"

#include "crankshape2segment.h"

/**
 * SECTION:crankshape2segment
 * @title: CrankShape2Segment
 * @short_description: Segment shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Represents a segment of shape.
 */

//////// List of virtual functions /////////////////////////////////////////////
// GObject
static void     crank_shape2_segment_get_property (GObject *object,
                                                   guint prop_id,
                                                   GValue *value,
                                                   GParamSpec *pspec);

static void     crank_shape2_segment_set_property (GObject      *object,
                                                   guint         prop_id,
                                                   const GValue *value,
                                                   GParamSpec   *pspec);

// CrankShape2

static gboolean crank_shape2_segment_contains (CrankShape2    *shape,
                                               CrankVecFloat2 *point);

// CrankShape2Finite

static gfloat   crank_shape2_segment_get_bound_radius (CrankShape2Finite *shape);


// CrankShape2vertexed
static guint    crank_shape2_segment_get_dimension (CrankShape2Vertexed *shape);

static guint    crank_shape2_segment_get_nvertices (CrankShape2Vertexed *shape);

static guint    crank_shape2_segment_get_nedges (CrankShape2Vertexed *shape);


static void     crank_shape2_segment_get_vertex_pos (CrankShape2Vertexed *shape,
                                                     guint                vid,
                                                     CrankVecFloat2      *pos);

static void     crank_shape2_segment_get_vertex_edges (CrankShape2Vertexed  *shape,
                                                       guint                 vid,
                                                       guint               **eids,
                                                       guint                *neids);

static void     crank_shape2_segment_get_edge_vertices (CrankShape2Vertexed *shape,
                                                        guint                eid,
                                                        guint               *vids);

static guint    crank_shape2_segment_get_farthest_vertex (CrankShape2Vertexed *shape,
                                                          CrankVecFloat2      *dir);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_LENGTH,
  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definition ///////////////////////////////////////////////////////

/**
 * CrankShape2Segment:
 *
 * Structure represents a segment shape.
 */
struct _CrankShape2Segment {
  CrankShape2Vertexed _parent;

  gfloat hlength;
};

G_DEFINE_TYPE (CrankShape2Segment,
               crank_shape2_segment,
               CRANK_TYPE_SHAPE2_POLYGON)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_segment_init (CrankShape2Segment *inst)
{
}

static void
crank_shape2_segment_class_init (CrankShape2SegmentClass *c)
{
  GObjectClass *c_gobject;
  CrankShape2Class *c_shape2;
  CrankShape2FiniteClass *c_shape2finite;
  CrankShape2VertexedClass *c_shape2vertexed;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape2_segment_get_property;
  c_gobject->set_property = crank_shape2_segment_set_property;

  pspecs[PROP_LENGTH] = g_param_spec_float ("length", "length", "length",
                                            0, G_MAXFLOAT, 0,
                                            G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_shape2 = CRANK_SHAPE2_CLASS (c);

  c_shape2->contains = crank_shape2_segment_contains;


  c_shape2finite = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2finite->get_bound_radius = crank_shape2_segment_get_bound_radius;


  c_shape2vertexed = CRANK_SHAPE2_VERTEXED_CLASS (c);

  c_shape2vertexed->get_dimension = crank_shape2_segment_get_dimension;
  c_shape2vertexed->get_nvertices = crank_shape2_segment_get_nvertices;
  c_shape2vertexed->get_nedges = crank_shape2_segment_get_nedges;
  c_shape2vertexed->get_vertex_pos = crank_shape2_segment_get_vertex_pos;
  c_shape2vertexed->get_vertex_edges = crank_shape2_segment_get_vertex_edges;
  c_shape2vertexed->get_edge_vertices = crank_shape2_segment_get_edge_vertices;
  c_shape2vertexed->get_farthest_vertex = crank_shape2_segment_get_farthest_vertex;
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape2_segment_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  switch (prop_id)
    {
    case PROP_LENGTH:
      g_value_set_float (value, ((CrankShape2Segment*)object)->hlength * 2);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_shape2_segment_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  switch (prop_id)
    {
    case PROP_LENGTH:
      crank_shape2_segment_set_length ((CrankShape2Segment*)object,
                                       g_value_get_float (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}




//////// CrankShape2 ///////////////////////////////////////////////////////////

static gboolean
crank_shape2_segment_contains (CrankShape2    *shape,
                               CrankVecFloat2 *point)
{
  gfloat hlength = ((CrankShape2Segment*)shape)->hlength;

  return (point->y == 0) &&
         (-hlength <= point->x) &&
         (point->x <= hlength);
}




//////// CrankShape2Finite /////////////////////////////////////////////////////

static gfloat
crank_shape2_segment_get_bound_radius (CrankShape2Finite *shape)
{
  return ((CrankShape2Segment*)shape)->hlength;
}




//////// CrankShape2Vertexed ////////////////////////////////////////////////////

static guint
crank_shape2_segment_get_dimension (CrankShape2Vertexed *shape)
{
  return 1;
}

static guint
crank_shape2_segment_get_nvertices (CrankShape2Vertexed *shape)
{
  return 2;
}

static guint
crank_shape2_segment_get_nedges (CrankShape2Vertexed *shape)
{
  return 1;
}

static void
crank_shape2_segment_get_vertex_pos (CrankShape2Vertexed *shape,
                                     guint                vid,
                                     CrankVecFloat2      *pos)
{
  CrankShape2Segment *self = (CrankShape2Segment*)shape;

  switch (vid)
    {
    case 0:
      crank_vec_float2_init (pos, self->hlength, 0.0f);
      break;

    case 1:
      crank_vec_float2_init (pos, -self->hlength, 0.0f);
      break;

    default:
      g_warning ("Invalid vertex id: %u", vid);
      crank_vec_float2_init (pos, NAN, NAN);
    }
}

static void
crank_shape2_segment_get_vertex_edges (CrankShape2Vertexed  *shape,
                                       guint                 vid,
                                       guint               **eids,
                                       guint                *neids)
{
  switch (vid)
    {
    case 0:
    case 1:
      *neids = 1;
      *eids = g_new (guint, 1);
      *eids[0] = 0;
      break;

    default:
      g_warning ("Invalid vertex id: %u", vid);
      *neids = 0;
      *eids = NULL;
    }
}

static void
crank_shape2_segment_get_edge_vertices (CrankShape2Vertexed *shape,
                                        guint                eid,
                                        guint               *vids)
{
  if (eid == 0)
    {
      vids[0] = 0;
      vids[1] = 1;
    }
  else
    {
      g_warning ("Invalid edge id: %u", eid);
      vids[0] = 0;
      vids[1] = 0;
    }
}

static guint
crank_shape2_segment_get_farthest_vertex (CrankShape2Vertexed *shape,
                                          CrankVecFloat2      *dir)
{
  return (dir->x < 0) ? 1 : 0;
}





//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_shape2_segment_new:
 * @length: Length of segment.
 *
 * Constructes new segment shape.
 *
 * Returns: (transfer full): New shape.
 */
CrankShape2Segment*
crank_shape2_segment_new (const gfloat length)
{
  return (CrankShape2Segment*) g_object_new (CRANK_TYPE_SHAPE2_SEGMENT,
                                             "length", length,
                                             NULL);
}

//////// Property getter / setters /////////////////////////////////////////////

/**
 * crank_shape2_segment_get_length:
 * @shape: A Shape.
 *
 * Gets a length of shape.
 *
 * Returns: length of segment.
 */
gfloat
crank_shape2_segment_get_length (CrankShape2Segment *shape)
{
  return shape->hlength * 2;
}

/**
 * crank_shape2_segment_set_length:
 * @shape: A Shape.
 * @length: A length.
 *
 * Sets a length of shape.
 */
void
crank_shape2_segment_set_length (CrankShape2Segment *shape,
                                 const gfloat        length)
{
  shape->hlength = length / 2;

  g_object_notify_by_pspec ((GObject*)shape, pspecs[PROP_LENGTH]);
  g_object_notify ((GObject*)shape, "bound-radius");
}
