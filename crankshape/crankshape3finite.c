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

#include "crankshape3.h"
#include "crankshape3finite.h"

/**
 * SECTION: crankshape3finite
 * @title: CrankShape3Finite
 * @short_description: Base class for finite shape
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This class is finite...
 *
 * # Abstract Functions
 *
 * * #CrankShape3FiniteClass.is_convex()
 * * #CrankShape3FiniteClass.get_bound_radius()
 *
 * # Default implementation from parent classes.
 *
 * * #CrankShape3Class.finitize()
 */


//////// List of virtual functions /////////////////////////////////////////////

static void     crank_shape3_finite_get_property       (GObject        *object,
                                                        guint           prop_id,
                                                        GValue         *value,
                                                        GParamSpec     *pspec);

static GList   *crank_shape3_finite_finitize           (CrankShape3    *shape,
                                                        CrankBox3      *box);


//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape3Finite, crank_shape3_finite, CRANK_TYPE_SHAPE3);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_CONVEX,
  PROP_BOUND_RADIUS,
  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_finite_init (CrankShape3Finite *self)
{
}

static void
crank_shape3_finite_class_init (CrankShape3FiniteClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankShape3Class *c_shape3 = CRANK_SHAPE3_CLASS (c);

  c_gobject->get_property = crank_shape3_finite_get_property;

  pspecs[PROP_CONVEX] = g_param_spec_boolean (
      "convex", "convex", "Convexity of shape",
      FALSE,
      G_PARAM_STATIC_STRINGS | G_PARAM_READABLE);

  pspecs[PROP_BOUND_RADIUS] = g_param_spec_float (
      "bound-radius", "bound-radius", "Bounding radius",
      0, G_MAXFLOAT, 0,
      G_PARAM_STATIC_STRINGS | G_PARAM_READABLE);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_shape3->finitize = crank_shape3_finite_finitize;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape3_finite_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  CrankShape3FiniteClass *c = CRANK_SHAPE3_FINITE_GET_CLASS (object);
  CrankShape3Finite *self = CRANK_SHAPE3_FINITE (object);

  switch (prop_id)
    {
    case PROP_CONVEX:
      g_value_set_boolean (value, c->is_convex (self));
      break;

    case PROP_BOUND_RADIUS:
      g_value_set_float (value, c->get_bound_radius (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


//////// CrankShape3 ///////////////////////////////////////////////////////////

static GList*
crank_shape3_finite_finitize (CrankShape3 *shape,
                              CrankBox3   *box)
{
  return g_list_append (NULL, shape);
}



//////// Property getter / setters /////////////////////////////////////////////

/**
 * crank_shape3_finite_is_convex:
 * @shape: A Shape
 *
 * Checks whether the shape is convex shape.
 *
 * Returns: Whether the shape is convex.
 */
gboolean
crank_shape3_finite_is_convex (CrankShape3Finite *shape)
{
  CrankShape3FiniteClass *c = CRANK_SHAPE3_FINITE_GET_CLASS (shape);

  return c->is_convex (shape);
}

/**
 * crank_shape3_finite_get_bound_radius:
 * @shape: A Shape
 *
 * Gets bound radius of shape.
 *
 * Returns: Bounding radius.
 */
gfloat
crank_shape3_finite_get_bound_radius (CrankShape3Finite *shape)
{
  CrankShape3FiniteClass *c = CRANK_SHAPE3_FINITE_GET_CLASS (shape);

  return c->get_bound_radius (shape);
}
