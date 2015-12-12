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

#include "crankpolystruct3.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3sphere.h"
#include "crankshape3vertexed.h"
#include "crankshape3polyhedron.h"
#include "crankshape3tpolyhedron.h"
#include "crankshape3cpolyhedron.h"
#include "crankshape3point.h"

#include "crankshape3sphere.h"



//////// List of virtual functions /////////////////////////////////////////////

// Interfaces

static void   crank_shape3_sphere_init_iround (CrankShape3IRoundInterface *iface);

// GObject

static void   crank_shape3_sphere_get_property (GObject    *object,
                                                guint       prop_id,
                                                GValue     *value,
                                                GParamSpec *pspec);

static void   crank_shape3_sphere_set_property (GObject      *object,
                                                guint         prop_id,
                                                const GValue *value,
                                                GParamSpec   *pspec);

// CrankShape3

static gboolean crank_shape3_sphere_contains (CrankShape3    *shape,
                                              CrankVecFloat3 *point);


// CrankSape3Finite

static gboolean crank_shape3_sphere_is_convex (CrankShape3Finite *shape);

static gfloat crank_shape3_sphere_get_bound_radius (CrankShape3Finite *shape);

static CrankShape3Vertexed *crank_shape3_sphere_approximate_vertexed (CrankShape3Finite *shape);


// CrankShape3IRound

static gfloat crank_shape3_sphere_get_round_radius (CrankShape3IRound *shape);

static CrankShape3Vertexed *crank_shape3_sphere_get_inner_shape (CrankShape3IRound *shape);

//////// Properties and Signals ////////////////////////////////////////////////


enum {
  PROP_0,
  PROP_ROUND_RADIUS,
  PROP_INNER_SHAPE,

  PROP_RADIUS,
  PROP_COUNTS
};

GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankShape3Sphere {
  CrankShape3Finite _parent;

  gfloat radius;
};


G_DEFINE_TYPE_WITH_CODE (CrankShape3Sphere,
                         crank_shape3_sphere,
                         CRANK_TYPE_SHAPE3_FINITE,
                         {
                          G_IMPLEMENT_INTERFACE ( CRANK_TYPE_SHAPE3_IROUND,
                                                  crank_shape3_sphere_init_iround);
                         })

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_sphere_init (CrankShape3Sphere *self)
{
}

static void
crank_shape3_sphere_class_init (CrankShape3SphereClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankShape3Class *c_shape3 = CRANK_SHAPE3_CLASS (c);
  CrankShape3FiniteClass *c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);

  c_gobject->get_property = crank_shape3_sphere_get_property;
  c_gobject->set_property = crank_shape3_sphere_set_property;

  pspecs[PROP_ROUND_RADIUS] = g_param_spec_float (
    "round-radius", "round-radius", "Round radius of shape.",
    0, G_MAXFLOAT, 0,
    G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_INNER_SHAPE] = g_param_spec_object (
    "inner-shape", "inner-shape", "Inner polyhedral shape.",
    CRANK_TYPE_SHAPE3_VERTEXED,
    G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);


  pspecs[PROP_RADIUS] = g_param_spec_float (
    "radius", "radius", "Radius of sphere.",
    0, G_MAXFLOAT, 1,
    G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_shape3->contains = crank_shape3_sphere_contains;


  c_shape3finite->is_convex = crank_shape3_sphere_is_convex;
  c_shape3finite->get_bound_radius = crank_shape3_sphere_get_bound_radius;
}

//////// Interfaces ////////////////////////////////////////////////////////////

static void
crank_shape3_sphere_init_iround (CrankShape3IRoundInterface *iface)
{
  iface->get_round_radius = crank_shape3_sphere_get_round_radius;
  iface->get_inner_shape = crank_shape3_sphere_get_inner_shape;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape3_sphere_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  CrankShape3Sphere *self = (CrankShape3Sphere*)object;

  switch (prop_id)
    {
    case PROP_ROUND_RADIUS:
    case PROP_RADIUS:
      g_value_set_float (value, self->radius);
      break;

    case PROP_INNER_SHAPE:
      g_value_take_object (value, (GObject*) crank_shape3_point_new ());
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_shape3_sphere_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
  CrankShape3Sphere *self = (CrankShape3Sphere *)object;

  switch (prop_id)
    {
    case PROP_RADIUS:
      crank_shape3_sphere_set_radius (self,
                                      g_value_get_float (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


//////// CrankShape3 ///////////////////////////////////////////////////////////

static gboolean
crank_shape3_sphere_contains (CrankShape3    *shape,
                              CrankVecFloat3 *point)
{
  CrankShape3Sphere *self = (CrankShape3Sphere*) shape;

  return crank_vec_float3_get_magn_sq (point) < (self->radius * self->radius);
}


//////// CrankShape3Finite /////////////////////////////////////////////////////

static gboolean
crank_shape3_sphere_is_convex (CrankShape3Finite *shape)
{
  return TRUE;
}

static gfloat
crank_shape3_sphere_get_bound_radius (CrankShape3Finite *shape)
{
  CrankShape3Sphere *self = (CrankShape3Sphere*)shape;

  return self->radius;
}

static CrankShape3Vertexed*
crank_shape3_sphere_approximate_vertexed (CrankShape3Finite *shape)
{
  // TODO: Approximation!
  return NULL;
}

//////// CrankShape3IRound /////////////////////////////////////////////////////

static gfloat
crank_shape3_sphere_get_round_radius (CrankShape3IRound *shape)
{
  CrankShape3Sphere *self = (CrankShape3Sphere*)shape;

  return self->radius;
}

static CrankShape3Vertexed*
crank_shape3_sphere_get_inner_shape (CrankShape3IRound *shape)
{
  return (CrankShape3Vertexed*)crank_shape3_point_new ();
}


//////// Constructor ///////////////////////////////////////////////////////////


/**
 * crank_shape3_sphere_new:
 * @radius: Radius of sphere.
 *
 * Constructs a sphere shape.
 *
 * Returns: (transfer full): Newly constructed sphere shape.
 */
CrankShape3Sphere*
crank_shape3_sphere_new (const gfloat radius)
{
  return (CrankShape3Sphere*)
    g_object_new (CRANK_TYPE_SHAPE3_SPHERE, "radius", radius, NULL);
}


//////// Property getter/setters ///////////////////////////////////////////////

/**
 * crank_shape3_sphere_get_radius:
 * @sphere: Sphere shape.
 *
 * Gets radius of sphere.
 *
 * Returns: Radius of sphere.
 */
gfloat
crank_shape3_sphere_get_radius (CrankShape3Sphere *sphere)
{
  return sphere->radius;
}

/**
 * crank_shape3_sphere_set_radius:
 * @sphere: Sphere shape.
 * @radius: Radius of sphere.
 *
 * Sets radius of sphere.
 */
void
crank_shape3_sphere_set_radius (CrankShape3Sphere *sphere,
                                const gfloat       radius)
{
  GObject *self_gobject = (GObject*) sphere;

  sphere->radius = radius;

  g_object_notify (self_gobject, "bound-radius");
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_ROUND_RADIUS]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_RADIUS]);

}
