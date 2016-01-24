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

static void     crank_lightable_set_property (GObject      *object,
                                              guint         prop_id,
                                              const GValue *value,
                                              GParamSpec   *pspec);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_VISIBLE_RADIUS,
  PROP_PRIMARY_COLOR,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definitions //////////////////////////////////////////////////////

typedef struct _CrankLightablePrivate
{
  CrankVecFloat3 primary_color;
} CrankLightablePrivate;


G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankLightable, crank_lightable, G_TYPE_OBJECT);



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_lightable_init (CrankLightable *lightable)
{
  CrankLightablePrivate *priv;

  priv = crank_lightable_get_instance_private (lightable);

  crank_vec_float3_init_fill (& priv->primary_color, 1);
}

static void
crank_lightable_class_init (CrankLightableClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_lightable_get_property;
  c_gobject->set_property = crank_lightable_set_property;

  pspecs[PROP_VISIBLE_RADIUS] = g_param_spec_float (
      "visible-radius", "Visible Radius",
      "Visible radius for lightable.\n"
      "This may used when culling lights that does not affects.",
      0, G_MAXFLOAT, 0,
      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_PRIMARY_COLOR] = g_param_spec_boxed (
      "primary-color", "Primary Color",
      "Primary color of lightable",
      CRANK_TYPE_VEC_FLOAT3,
      G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

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
  CrankLightablePrivate *priv = crank_lightable_get_instance_private (lightable);

  switch (prop_id)
    {
    case PROP_VISIBLE_RADIUS:
      g_value_set_float (value, crank_lightable_get_visible_radius (lightable));
      break;

    case PROP_PRIMARY_COLOR:
      g_value_set_boxed (value, & priv->primary_color);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

void
crank_lightable_set_property (GObject      *object,
                              guint         prop_id,
                              const GValue *value,
                              GParamSpec   *pspec)
{
  CrankLightable *lightable = (CrankLightable*) object;

  switch (prop_id)
    {
    case PROP_PRIMARY_COLOR:
      crank_lightable_set_primary_color (lightable,
                                         (CrankVecFloat3*) g_value_get_boxed (value));
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

/**
 * crank_lightable_get_primary_color:
 * @lightable: A Lightable.
 * @color: (out): light's primary color.
 *
 * Gets primary color of this lightable.
 */
void
crank_lightable_get_primary_color (CrankLightable *lightable,
                                   CrankVecFloat3 *color)
{
  CrankLightablePrivate *priv = crank_lightable_get_instance_private (lightable);

  crank_vec_float3_copy (& priv->primary_color, color);
}

/**
 * crank_lightable_set_primary_color:
 * @lightable: A Lightable.
 * @color: light's primary color.
 *
 * Sets primary color of this lightable.
 */
void
crank_lightable_set_primary_color (CrankLightable *lightable,
                                   CrankVecFloat3 *color)
{
  CrankLightablePrivate *priv = crank_lightable_get_instance_private (lightable);

  crank_vec_float3_copy (color, & priv->primary_color);
}


/**
 * crank_lightable_render:
 * @lightable: A Lightable.
 * @position: Position of lightable in view's space.
 * @projection: Projection of view.
 * @tex_geom: Geometry buffer.
 * @tex_color: Color buffer.
 * @tex_mater: Material buffer.
 * @lscale: Light scaling.
 * @framebuffer: Framebuffer to render.
 *
 * Renders light with given material informations.
 */
void
crank_lightable_render (CrankLightable  *lightable,
                        CrankTrans3     *position,
                        CrankProjection *projection,
                        CoglTexture     *tex_geom,
                        CoglTexture     *tex_color,
                        CoglTexture     *tex_mater,
                        const gfloat     lscale,
                        CoglFramebuffer *framebuffer)
{
  CrankLightableClass *c = CRANK_LIGHTABLE_GET_CLASS (lightable);

  c->render (lightable, position, projection, tex_geom, tex_color, tex_mater, lscale, framebuffer);
}
