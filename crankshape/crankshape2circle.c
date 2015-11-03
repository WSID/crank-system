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

#include "crankshape2circle.h"


//////// Properties and signal enums ///////////////////////////////////////////

enum {
  PROP_0,
  PROP_RADIUS,
  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// List of virtual function implementation. //////////////////////////////

// GObject
static void _object_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec);

static void _object_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec);

// CrankShape2
static gboolean crank_shape2_circle_contains (CrankShape2    *shape,
                                          CrankVecFloat2 *point);

// CrankShape2Finite
static gboolean crank_shape2_circle_is_convex (CrankShape2Finite *shape);

static gfloat crank_shape2_circle_get_bound_radius (CrankShape2Finite *shape);

static CrankShape2Polygon *crank_shape2_circle_approximate_polygon (CrankShape2Finite *shape);


//////// Type definition ///////////////////////////////////////////////////////

struct _CrankShape2Circle {
  CrankShape2Finite _parent;

  gfloat        radius;
};

G_DEFINE_TYPE (CrankShape2Circle,
               crank_shape2_circle,
               CRANK_TYPE_SHAPE2_FINITE)



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_circle_init (CrankShape2Circle *inst)
{
}

static void
crank_shape2_circle_class_init (CrankShape2CircleClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankShape2Class *c_shape2 = CRANK_SHAPE2_CLASS (c);
  CrankShape2FiniteClass *c_shape2finite = CRANK_SHAPE2_FINITE_CLASS (c);

  pspecs[PROP_RADIUS] = g_param_spec_float ("radius", "radius", "radius",
                                            0, G_MAXFLOAT, 1,
                                            G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  c_gobject->get_property = _object_get_property;
  c_gobject->set_property = _object_set_property;


  c_shape2->contains = crank_shape2_circle_contains;


  c_shape2finite->is_convex = crank_shape2_circle_is_convex;
  c_shape2finite->get_bound_radius = crank_shape2_circle_get_bound_radius;
  c_shape2finite->approximate_polygon = crank_shape2_circle_approximate_polygon;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
_object_get_property (GObject    *object,
                      guint       prop_id,
                      GValue     *value,
                      GParamSpec *pspec)
{
  switch (prop_id)
    {
    case PROP_RADIUS:
      g_value_set_float (value,
                         ((CrankShape2Circle*)object)->radius);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
_object_set_property (GObject      *object,
                      guint         prop_id,
                      const GValue *value,
                      GParamSpec   *pspec)
{
  switch (prop_id)
    {
    case PROP_RADIUS:
      ((CrankShape2Circle*)object)->radius = g_value_get_float (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// CrankShape2 ///////////////////////////////////////////////////////////

static gboolean
crank_shape2_circle_contains (CrankShape2    *shape,
                              CrankVecFloat2 *point)
{
  CrankShape2Circle *self = (CrankShape2Circle*)shape;

  return crank_vec_float2_get_magn_sq (point) <= (self->radius * self->radius);
}


//////// CrankShape2Finite /////////////////////////////////////////////////////

static gboolean
crank_shape2_circle_is_convex (CrankShape2Finite *shape)
{
  return TRUE;  // Circle is always convex.
}

static gfloat
crank_shape2_circle_get_bound_radius (CrankShape2Finite *shape)
{
  return ((CrankShape2Circle*)shape)->radius;
}

static CrankShape2Polygon*
crank_shape2_circle_approximate_polygon (CrankShape2Finite *shape)
{
  guint i, n;
  CrankVecFloat2 vertices[64];

  n = 64;

  for (i = 0; i < n; i++)
    {
      gfloat angle = (gfloat) (G_PI * 2 * i / n);

      vertices[i].x = cosf (angle);
      vertices[i].y = sinf (angle);
    }

  return (CrankShape2Polygon*)crank_shape2_cpolygon_new_from_vertices (vertices, n);
}

//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_shape2_circle_new:
 * @radius: A Radius
 *
 * Constructs a circle shape.
 *
 * Returns: (transfer full): A Shape.
 */
CrankShape2Circle*
crank_shape2_circle_new (gfloat radius)
{
  return (CrankShape2Circle*) g_object_new (CRANK_TYPE_SHAPE2_CIRCLE, "radius", radius, NULL);
}


//////// Property getter/setters ///////////////////////////////////////////////

/**
 * crank_shape2_circle_get_radius:
 * @circle: A Circle.
 *
 * Gets a radius of circle.
 *
 * Returns: Radius of a circle.
 */
gfloat
crank_shape2_circle_get_radius (CrankShape2Circle *circle)
{
  return circle->radius;
}

/**
 * crank_shape2_circle_set_radius:
 * @circle: A Circle.
 * @radius: A Radius.
 *
 * Sets a radius of circle.
 */
void
crank_shape2_circle_set_radius (CrankShape2Circle *circle,
                                const gfloat       radius)
{
  circle->radius = radius;
  g_object_notify_by_pspec ((GObject*)circle, pspecs[PROP_RADIUS]);
}
