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

/**
 * SECTION: crankvisible
 * @title: CrankVisible
 * @short_description: Represents a visible item.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * Represents a visible item that can be rendered. This object only carray
 * visibility volume information. Positional and projection information come
 * from #CrankEntityBase.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankcore.h"
#include "crankvisible.h"


//////// List of virtual functions /////////////////////////////////////////////

static void crank_visible_get_property (GObject    *object,
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


//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankVisible,
                        crank_visible,
                        CRANK_TYPE_COMPOSITABLE);




//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_visible_init (CrankVisible *self)
{
}

static void
crank_visible_class_init (CrankVisibleClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankCompositableClass *c_compositable = CRANK_COMPOSITABLE_CLASS (c);

  c_gobject->get_property = crank_visible_get_property;

  pspecs[PROP_VISIBLE_RADIUS] = g_param_spec_float ("visible-radius",
                                                    "Visible radius",
                                                    "Visible radius of object",
                                                    0, G_MAXFLOAT, 0,
                                                    G_PARAM_READABLE |
                                                    G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  crank_compositable_class_add_requisition (c_compositable,
                                            CRANK_TYPE_ENTITY3);
}



//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_visible_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  CrankVisible *self = (CrankVisible*) object;

  switch (prop_id)
    {
    case PROP_VISIBLE_RADIUS:
      g_value_set_float (value, crank_visible_get_visible_radius (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}



//////// Public Functions //////////////////////////////////////////////////////

//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_visible_get_visible_radius:
 * @visible: A visible object.
 *
 * Gets visible radius of @visible. This information can be used for culling out
 * items that cannot affect results.
 *
 * Returns: Visible radius.
 */
gfloat
crank_visible_get_visible_radius (CrankVisible *visible)
{
  CrankVisibleClass *c = CRANK_VISIBLE_GET_CLASS (visible);

  return c->get_visible_radius (visible);
}
