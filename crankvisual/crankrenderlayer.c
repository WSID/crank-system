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
 * SECTION: crankrenderlayer
 * @title: CrankRenderLayer
 * @short_description: Represents rendering layer.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * Represents single layer that rendered. Generally #CrankRenderLayerTexture
 * is used as layer, which holds a texture and framebuffer associated to it.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankrenderlayer.h"




//////// List of virtual functions /////////////////////////////////////////////

static void crank_render_layer_get_property (GObject    *object,
                                             guint       prop_id,
                                             GValue     *value,
                                             GParamSpec *pspec);

static void crank_render_layer_set_property (GObject      *object,
                                             guint         prop_id,
                                             const GValue *value,
                                             GParamSpec   *pspec);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_NAME,
  PROP_QNAME,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankRenderLayerPrivate {
  GQuark name;
} CrankRenderLayerPrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankRenderLayer,
                                     crank_render_layer,
                                     G_TYPE_OBJECT)



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_layer_init (CrankRenderLayer *self)
{

}

static void
crank_render_layer_class_init (CrankRenderLayerClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_render_layer_get_property;
  c_gobject->set_property = crank_render_layer_set_property;

  pspecs[PROP_NAME] = g_param_spec_string ("name", "Name", "Name of layer",
                                           NULL,
                                           G_PARAM_READWRITE |
                                           G_PARAM_STATIC_STRINGS );

  pspecs[PROP_QNAME] = g_param_spec_uint ("qname", "Name as GQuark", "Name of layer as GQuark",
                                          0, G_MAXUINT, 0,
                                          G_PARAM_READWRITE |
                                          G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}



//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_render_layer_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  CrankRenderLayer *self = (CrankRenderLayer*) object;

  switch (prop_id)
    {
    case PROP_NAME:
      g_value_set_string (value, crank_render_layer_get_name(self));
      break;

    case PROP_QNAME:
      g_value_set_uint (value, crank_render_layer_get_qname (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_render_layer_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  CrankRenderLayer *self = (CrankRenderLayer*) object;

  switch (prop_id)
    {
    case PROP_NAME:
      crank_render_layer_set_name (self, g_value_get_string (value));
      break;

    case PROP_QNAME:
      crank_render_layer_set_qname (self, g_value_get_uint (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}



//////// Public functions //////////////////////////////////////////////////////

//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_render_layer_get_qname:
 * @layer: A Layer.
 *
 * Get name of the layer as #GQuark.
 *
 * Returns: Name of layer.
 */
GQuark
crank_render_layer_get_qname (CrankRenderLayer *layer)
{
  return G_PRIVATE_FIELD (CrankRenderLayer, layer,
                          GQuark,           name);
}

/**
 * crank_render_layer_set_qname:
 * @layer: A Layer.
 * @name: Name of layer.
 *
 * Set name of the layer by #GQuark.
 */
void
crank_render_layer_set_qname (CrankRenderLayer *layer,
                              GQuark            name)
{
  G_PRIVATE_FIELD (CrankRenderLayer, layer,
                   GQuark,           name) = name;

  g_object_notify_by_pspec ((GObject*)layer, pspecs[PROP_QNAME]);
  g_object_notify_by_pspec ((GObject*)layer, pspecs[PROP_NAME]);
}




/**
 * crank_render_layer_get_name:
 * @layer: A Layer.
 *
 * Get name of the layer as string.
 *
 * Returns: (transfer none): Name of layer.
 */
const gchar*
crank_render_layer_get_name (CrankRenderLayer *layer)
{
  return g_quark_to_string (G_PRIVATE_FIELD (CrankRenderLayer, layer,
                                             GQuark,           name));
}

/**
 * crank_render_layer_set_name:
 * @layer: A Layer.
 * @name: (transfer none): Name of layer.
 *
 * Set name of the layer by string.
 */
void
crank_render_layer_set_name (CrankRenderLayer *layer,
                             const gchar      *name)
{
  G_PRIVATE_FIELD (CrankRenderLayer, layer,
                   GQuark,           name) = g_quark_from_string (name);

  g_object_notify_by_pspec ((GObject*)layer, pspecs[PROP_QNAME]);
  g_object_notify_by_pspec ((GObject*)layer, pspecs[PROP_NAME]);
}

/**
 * crank_render_layer_set_name_static:
 * @layer: A Layer.
 * @name: (transfer none): Name of layer.
 *
 * Set name of the layer by string. This uses g_quark_from_static_string().
 */
void
crank_render_layer_set_name_static (CrankRenderLayer *layer,
                                    const gchar      *name)
{
  G_PRIVATE_FIELD (CrankRenderLayer, layer,
                   GQuark,           name) = g_quark_from_static_string (name);

  g_object_notify_by_pspec ((GObject*)layer, pspecs[PROP_QNAME]);
  g_object_notify_by_pspec ((GObject*)layer, pspecs[PROP_NAME]);
}
