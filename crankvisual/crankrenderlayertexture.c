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
 * SECTION: crankrenderlayertexture
 * @title: CrankRenderLayerTexture
 * @short_description: A CrankRenderLayer with renderable texture.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * This is a layer that has texture.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>

#include "crankrenderlayer.h"
#include "crankrenderlayertexture.h"


//////// List of virtual functions /////////////////////////////////////////////

static void     crank_render_layer_texture_g_initable_iface_init (GInitableIface *iface);

static gboolean crank_render_layer_texture_g_initable_init (GInitable     *initable,
                                                            GCancellable  *cancellable,
                                                            GError       **error);

static void   crank_render_layer_texture_constructed (GObject *object);

static void   crank_render_layer_texture_finalize    (GObject *object);

static void   crank_render_layer_texture_get_property (GObject    *object,
                                                       guint       prop_id,
                                                       GValue     *value,
                                                       GParamSpec *pspec);

static void   crank_render_layer_texture_set_property (GObject      *object,
                                                       guint         prop_id,
                                                       const GValue *value,
                                                       GParamSpec   *pspec);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_COGL_CONTEXT,
  PROP_WIDTH,
  PROP_HEIGHT,
  PROP_COMPONENTS,

  PROP_TEXTURE,
  PROP_FRAMEBUFFER,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definitions //////////////////////////////////////////////////////

struct _CrankRenderLayerTexture
{
  CrankRenderLayer _parent;

  CoglTexture      *texture;
  CoglFramebuffer  *framebuffer;
};

G_DEFINE_TYPE_WITH_CODE (CrankRenderLayerTexture,
                         crank_render_layer_texture,
                         CRANK_TYPE_RENDER_LAYER,
                         {
                           G_IMPLEMENT_INTERFACE (G_TYPE_INITABLE,
                                                  crank_render_layer_texture_g_initable_iface_init);
                         });


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_layer_texture_init (CrankRenderLayerTexture *self)
{
}


static void
crank_render_layer_texture_class_init (CrankRenderLayerTextureClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->constructed = crank_render_layer_texture_constructed;
  c_gobject->finalize = crank_render_layer_texture_finalize;

  c_gobject->get_property = crank_render_layer_texture_get_property;
  c_gobject->set_property = crank_render_layer_texture_set_property;

  /**
   * CrankRenderLayerTexture:cogl-context: (type CoglContext)
   *
   * CoglContext to initialize.
   */
  pspecs[PROP_COGL_CONTEXT] = g_param_spec_pointer ("cogl-context", "CoglContext",
                                                    "CoglContext to initialize",
                                                    G_PARAM_WRITABLE |
                                                    G_PARAM_CONSTRUCT_ONLY |
                                                    G_PARAM_STATIC_STRINGS );

  pspecs[PROP_WIDTH] = g_param_spec_uint ("width", "width", "width of texture",
                                          0, G_MAXUINT, 0,
                                          G_PARAM_READWRITE |
                                          G_PARAM_CONSTRUCT_ONLY |
                                          G_PARAM_STATIC_STRINGS);

  pspecs[PROP_HEIGHT] = g_param_spec_uint ("height", "height", "height of texture",
                                           0, G_MAXUINT, 0,
                                           G_PARAM_READWRITE |
                                           G_PARAM_CONSTRUCT_ONLY |
                                           G_PARAM_STATIC_STRINGS);

  /**
   * CrankRenderLayerTexture:components: (type CoglTextureComponents)
   *
   * Component enum value for texture.
   */
  pspecs[PROP_COMPONENTS] = g_param_spec_uint ("components", "components",
                                               "Pixel components of texture",
                                               0, G_MAXUINT, COGL_TEXTURE_COMPONENTS_RGBA,
                                               G_PARAM_READWRITE |
                                               G_PARAM_CONSTRUCT_ONLY |
                                               G_PARAM_STATIC_STRINGS );

  /**
   * CrankRenderLayerTexture:texture: (type CoglTexture)
   *
   * Texture of this layer.
   */
  pspecs[PROP_TEXTURE] = g_param_spec_pointer ("texture", "Texture",
                                               "Texture of this layer.",
                                               G_PARAM_READWRITE |
                                               G_PARAM_CONSTRUCT_ONLY |
                                               G_PARAM_STATIC_STRINGS );

  /**
   * CrankRenderLayerTexture:framebuffer: (type CoglFramebuffer)
   *
   * Framebuffer of this layer. This can be used to alter or render content of
   * this layer.
   */
  pspecs[PROP_FRAMEBUFFER] = g_param_spec_pointer ("framebuffer", "Framebuffer",
                                                   "Framebuffer to write write on texture.",
                                                   G_PARAM_READABLE |
                                                   G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}


//////// GInitable /////////////////////////////////////////////////////////////

static void
crank_render_layer_texture_g_initable_iface_init (GInitableIface *iface)
{
  iface->init = crank_render_layer_texture_g_initable_init;
}


static gboolean
crank_render_layer_texture_g_initable_init (GInitable     *initable,
                                            GCancellable  *cancellable,
                                            GError       **error)
{
  CrankRenderLayerTexture *self = (CrankRenderLayerTexture*) initable;
  GError *merr = NULL;

  cogl_texture_allocate (self->texture, &merr);
  if (merr != NULL)
    {
      g_propagate_error (error, merr);
      return FALSE;
    }

  if (g_cancellable_set_error_if_cancelled (cancellable, error))
    return FALSE;

  cogl_framebuffer_allocate (self->framebuffer, &merr);
  if (merr != NULL)
    {
      g_propagate_error (error, merr);
      return FALSE;
    }

  return TRUE;
}



//////// GObject ///////////////////////////////////////////////////////////////


static void
crank_render_layer_texture_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec)
{
  CrankRenderLayerTexture *self = (CrankRenderLayerTexture*)object;

  switch (prop_id)
    {
    case PROP_WIDTH:
      g_value_set_uint (value, crank_render_layer_texture_get_width (self));
      break;

    case PROP_HEIGHT:
      g_value_set_uint (value, crank_render_layer_texture_get_height (self));
      break;

    case PROP_COMPONENTS:
      g_value_set_uint (value, crank_render_layer_texture_get_components (self));
      break;

    case PROP_TEXTURE:
      g_value_set_pointer (value, self->texture);
      break;

    case PROP_FRAMEBUFFER:
      g_value_set_pointer (value, self->framebuffer);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_render_layer_texture_set_property (GObject    *object,
                                         guint       prop_id,
                                         const GValue     *value,
                                         GParamSpec *pspec)
{
  CrankRenderLayerTexture *self = (CrankRenderLayerTexture*)object;

  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
      g_object_set_data (object, "prop-cogl-context", g_value_get_pointer (value));
      break;

    case PROP_WIDTH:
      g_object_set_data (object, "prop-width", GUINT_TO_POINTER (g_value_get_uint (value)));
      break;

    case PROP_HEIGHT:
      g_object_set_data (object, "prop-height", GUINT_TO_POINTER (g_value_get_uint (value)));
      break;

    case PROP_COMPONENTS:
      g_object_set_data (object, "prop-components", GUINT_TO_POINTER (g_value_get_uint (value)));
      break;

    case PROP_TEXTURE:
      self->texture = cogl_object_ref (g_value_get_pointer (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
crank_render_layer_texture_constructed (GObject *object)
{
  CrankRenderLayerTexture *self = (CrankRenderLayerTexture*)object;
  GObjectClass *pc = crank_render_layer_texture_parent_class;

  pc->constructed (object);

  if (self->texture == NULL)
    {
      CoglContext *cogl_context = g_object_get_data (object, "prop-cogl-context");
      guint width =  GPOINTER_TO_UINT (g_object_get_data (object, "prop-width"));
      guint height = GPOINTER_TO_UINT (g_object_get_data (object, "prop-height"));
      CoglTextureComponents components = GPOINTER_TO_UINT (g_object_get_data (object, "prop-components"));

      self->texture = cogl_texture_2d_new_with_size (cogl_context, width, height);
      cogl_texture_set_components (self->texture, components);
    }
  else
    {
      if (! cogl_is_primitive_texture (self->texture))
        g_warning ("The texture is not a primitive texture.");

      else if (! cogl_is_texture_2d (self->texture))
        g_warning ("Only 2D texture is supported for now.");
    }

  self->framebuffer = cogl_offscreen_new_with_texture (self->texture);
}

static void
crank_render_layer_texture_finalize (GObject *object)
{
  CrankRenderLayerTexture *self = (CrankRenderLayerTexture*)object;
  GObjectClass *pc = crank_render_layer_texture_parent_class;

  cogl_object_unref (self->framebuffer);
  cogl_object_unref (self->texture);

  pc->finalize (object);
}



//////// Public Functions //////////////////////////////////////////////////////

//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_render_layer_texture_new:
 * @cogl_context: (transfer none): A Cogl Context.
 * @width: Width of texture.
 * @height: Height of texture.
 * @cancellable: (nullable): Cancellable.
 * @error: Error.
 *
 * Constructs layer with given size.
 *
 * Returns: (transfer full): Newly constructed layer.
 */
CrankRenderLayerTexture*
crank_render_layer_texture_new (CoglContext   *cogl_context,
                                const guint    width,
                                const guint    height,
                                GCancellable  *cancellable,
                                GError       **error)
{
  return g_initable_new (CRANK_TYPE_RENDER_LAYER_TEXTURE,
                         cancellable,
                         error,
                         "cogl-context", cogl_context,
                         "width", width,
                         "height", height,
                         NULL);
}

/**
 * crank_render_layer_texture_new_with_components:
 * @cogl_context: (transfer none): A Cogl Context.
 * @width: Width of texture.
 * @height: Height of texture.
 * @components: Components of texture.
 * @cancellable: (nullable): Cancellable.
 * @error: Error.
 *
 * Constructs layer with given size, with components.
 *
 * Returns: (transfer full): Newly constructed layer.
 */
CrankRenderLayerTexture*
crank_render_layer_texture_new_with_components (CoglContext                  *cogl_context,
                                                const guint                   width,
                                                const guint                   height,
                                                const CoglTextureComponents   components,
                                                GCancellable                 *cancellable,
                                                GError                      **error)
{
  return g_initable_new (CRANK_TYPE_RENDER_LAYER_TEXTURE,
                         cancellable,
                         error,
                         "cogl-context", cogl_context,
                         "components", components,
                         "width", width,
                         "height", height,
                         NULL);
}

/**
 * crank_render_layer_texture_new_with_texture:
 * @texture: (transfer none): A texture.
 * @cancellable: (nullable): Cancellable.
 * @error: Error.
 *
 * Constructs layer with given texture.
 *
 * Returns: (transfer full): Newly constructed layer.
 */
CrankRenderLayerTexture*
crank_render_layer_texture_new_with_texture (CoglTexture   *texture,
                                             GCancellable  *cancellable,
                                             GError       **error)
{
  return g_initable_new (CRANK_TYPE_RENDER_LAYER_TEXTURE,
                         cancellable,
                         error,
                         "texture", texture,
                         NULL);
}


//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_render_layer_texture_get_width:
 * @layer: A Layer.
 *
 * Gets width of layer.
 *
 * Returns: Width of layer.
 */
guint
crank_render_layer_texture_get_width (CrankRenderLayerTexture *layer)
{
  return cogl_texture_get_width (layer->texture);
}

/**
 * crank_render_layer_texture_get_height:
 * @layer: A Layer.
 *
 * Gets height of layer.
 *
 * Returns: Height of layer.
 */
guint
crank_render_layer_texture_get_height (CrankRenderLayerTexture *layer)
{
  return cogl_texture_get_height (layer->texture);
}

/**
 * crank_render_layer_texture_get_components:
 * @layer: A Layer.
 *
 * Gets components enum of layer.
 *
 * Returns: Component enums of texture.
 */
CoglTextureComponents
crank_render_layer_texture_get_components (CrankRenderLayerTexture *layer)
{
  return cogl_texture_get_components (layer->texture);
}



/**
 * crank_render_layer_texture_get_texture:
 * @layer: A Layer.
 *
 * Gets texture of the layer.
 *
 * Returns: (transfer none): Texture of a layer.
 */
CoglTexture*
crank_render_layer_texture_get_texture (CrankRenderLayerTexture *layer)
{
  return layer->texture;
}

/**
 * crank_render_layer_texture_get_framebuffer:
 * @layer: A Layer.
 *
 * Gets framebuffer of the layer. This framebuffer is associated to the texture,
 * so that texture can be altered.
 *
 * Returns: (transfer none): Framebuffer of a layer.
 */
CoglFramebuffer*
crank_render_layer_texture_get_framebuffer (CrankRenderLayerTexture *layer)
{
  return layer->framebuffer;
}

