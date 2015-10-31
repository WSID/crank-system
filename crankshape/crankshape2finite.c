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
#include "crankshape2.h"
#include "crankshape2finite.h"

/**
 * SECTION: crankshape2finite
 * @title: CrankShape2Finite
 * @short_description: Interface for finite shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This interface defines methods for finite shapes.
 *
 * Finite shape will have limited range of placement of points. Thus, it will
 * have limited bounding boxes.
 */

//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape2Finite,
                        crank_shape2_finite,
                        CRANK_TYPE_SHAPE2)


//////// Virtual functions /////////////////////////////////////////////////////

static void     crank_shape2_finite_get_property       (GObject        *object,
                                                        guint           prop_id,
                                                        GValue         *value,
                                                        GParamSpec     *pspec);

//////// Signals and properties ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_BOUND_RADIUS,
  PROP_COUNT
};

static GParamSpec *pspecs[PROP_COUNT] = {NULL};



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_finite_init (CrankShape2Finite *shape)
{
}

static void
crank_shape2_finite_class_init (CrankShape2FiniteClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape2_finite_get_property;

  pspecs[PROP_BOUND_RADIUS] = g_param_spec_float (
        "bound-radius", "bound radius", "A bound radius for shape.",
        0, G_MAXFLOAT, 0,
        G_PARAM_STATIC_STRINGS | G_PARAM_READABLE);

  g_object_class_install_properties (c_gobject, PROP_COUNT, pspecs);
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape2_finite_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  switch (prop_id)
    {
    case PROP_BOUND_RADIUS:
      g_value_set_float (value,
                         crank_shape2_finite_get_bound_radius (
                         (CrankShape2Finite*)object));
      break;

    case PROP_0:
    case PROP_COUNT:
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_shape2_finite_get_bound_radius:
 * @shape: A Shape.
 *
 * Get a radius of bounding circle.
 *
 * Returns: A Radius.
 */
gfloat
crank_shape2_finite_get_bound_radius (CrankShape2Finite *shape)
{
  CrankShape2FiniteClass *c_shape;
  c_shape = CRANK_SHAPE2_FINITE_GET_CLASS (shape);

  return c_shape->get_bound_radius (shape);
}
