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

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include <cogl/cogl2-experimental.h>

#include "cranklightable.h"

/**
 * SECTION: cranklightable
 * @title: CrankLightable
 * @short_description: Lightable Base Class
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * Represents a lightable.
 *
 * Abstract function:
 *
 * * CrankLightableClass.get_visible_radius()
 */


//////// List of virtual functions /////////////////////////////////////////////

static void     crank_lightable_get_property (GObject    *object,
                                              guint       prop_id,
                                              GValue     *value,
                                              GParamSpec *pspec);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_VISIBLE_RADIUS,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definitions //////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankLightable, crank_lightable, G_TYPE_OBJECT);



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_lightable_init (CrankLightable *lightable)
{
}

static void
crank_lightable_class_init (CrankLightableClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_lightable_get_property;

  pspecs[PROP_VISIBLE_RADIUS] = g_param_spec_float (
      "visible-radius", "Visible Radius",
      "Visible radius for lightable.\n"
      "This may used when culling lights that does not affects.",
      0, G_MAXFLOAT, 0,
      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}



//////// GObject ///////////////////////////////////////////////////////////////

void
crank_lightable_get_property (GObject    *object,
                              guint       prop_id,
                              GValue     *value,
                              GParamSpec *pspec)
{
  CrankLightable *lightable = (CrankLightable*) object;

  switch (prop_id)
    {
    case PROP_VISIBLE_RADIUS:
      g_value_set_float (value, crank_lightable_get_visible_radius (lightable));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_lightable_get_visible_radius:
 * @lightable: A Lightable.
 *
 * Gets light's visible radius.
 *
 * Returns: light's visible radius, or %INFINITY if it applied to fullscreen.
 */
gfloat
crank_lightable_get_visible_radius (CrankLightable *lightable)
{
  CrankLightableClass *c = CRANK_LIGHTABLE_GET_CLASS (lightable);

  return c->get_visible_radius (lightable);
}
