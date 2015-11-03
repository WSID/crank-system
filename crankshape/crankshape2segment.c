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
#include "crankshape2polygon.h"

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


// CrankShape2Polygon

static guint    crank_shape2_segment_get_nvertices (CrankShape2Polygon *shape);

static void     crank_shape2_segment_get_vertex (CrankShape2Polygon *shape,
                                                 guint               index,
                                                 CrankVecFloat2     *vertex);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_LENGTH,
  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankShape2Segment {
  CrankShape2Polygon _parent;

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
  CrankShape2PolygonClass *c_shape2polygon;

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


  c_shape2polygon = CRANK_SHAPE2_POLYGON_CLASS (c);

  c_shape2polygon->get_nvertices = crank_shape2_segment_get_nvertices;
  c_shape2polygon->get_vertex = crank_shape2_segment_get_vertex;
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
      ((CrankShape2Segment*)object)->hlength = g_value_get_float (value) / 2;
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

//////// CrankShape2Polygon ////////////////////////////////////////////////////

static guint
crank_shape2_segment_get_nvertices (CrankShape2Polygon *shape)
{
  return 2;
}

static void
crank_shape2_segment_get_vertex (CrankShape2Polygon *shape,
                                 guint               index,
                                 CrankVecFloat2     *vertex)
{
  CrankShape2Segment *self = (CrankShape2Segment*)shape;

  switch (index)
    {
    case 0:
      crank_vec_float2_init (vertex, - self->hlength, 0.0f);
      break;

    case 1:
      crank_vec_float2_init (vertex, self->hlength, 0.0f);
      break;

    default:
      crank_vec_float2_init (vertex, NAN, NAN);
    }
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

/**
 * crank_shape2_segment_new_with_position:
 * @length: Length of segment.
 * @position: A Position.
 *
 * Constructes new segment shape with position.
 *
 * Returns: (transfer full): New shape.
 */
CrankShape2Segment*
crank_shape2_segment_new_with_position (const gfloat  length,
                                        CrankTrans2  *position)
{
  return (CrankShape2Segment*) g_object_new (CRANK_TYPE_SHAPE2_SEGMENT,
                                             "length", length,
                                             "position", position,
                                             NULL);
}

/**
 * crank_shape2_segment_new_with_points:
 * @a: A end point.
 * @b: A end point.
 *
 * Constructes new segment shape with points as end points.
 *
 * Returns: (transfer full): New shape.
 */
CrankShape2Segment*
crank_shape2_segment_new_with_points (CrankVecFloat2 *a,
                                      CrankVecFloat2 *b)
{
  CrankVecFloat2 seg;
  CrankTrans2 pos;

  crank_vec_float2_mixs (a, b, 0.5, & pos.mtrans);

  crank_vec_float2_sub (b, a, &seg);
  pos.mrot = atan2f (seg.y, seg.x);
  pos.mscl = 1.0f;

  return crank_shape2_segment_new_with_position (crank_vec_float2_get_magn (&seg),
                                                 &pos);
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
}
