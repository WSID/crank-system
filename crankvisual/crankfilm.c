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
 * SECTION: crankfilm
 * @title: CrankFilm
 * @short_description: Group of framebuffers for deferred shading.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * This represents a set of framebuffers.
 */

#define _CRANKVISUAL_INSIDE

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <cogl/cogl2-experimental.h>

#include "crankrenderlayerarray.h"
#include "crankrenderlayertexture.h"
#include "crankfilm.h"

//////// List of virtual functions /////////////////////////////////////////////

static void     crank_film_constructed (GObject *object);

static void     crank_film_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec);

static void     crank_film_dispose (GObject *object);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_NLAYERS,
  PROP_WIDTH,
  PROP_HEIGHT,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankFilm
{
  GObject parent;

  guint width;
  guint height;

  GPtrArray *layers;
};

G_DEFINE_TYPE (CrankFilm,
               crank_film,
               G_TYPE_OBJECT)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_film_init (CrankFilm *self)
{
  self->layers = g_ptr_array_new_with_free_func (g_object_unref);
}

static void
crank_film_class_init (CrankFilmClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->constructed = crank_film_constructed;
  c_gobject->get_property = crank_film_get_property;
  c_gobject->dispose = crank_film_dispose;

  pspecs[PROP_NLAYERS] =
  g_param_spec_uint ("nlayers", "nlayers",
                     "Number of layers",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_WIDTH] =
  g_param_spec_uint ("width", "width",
                     "Width of film",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_HEIGHT] =
  g_param_spec_uint ("height", "height",
                     "Height of film",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}



//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_film_constructed (GObject *object)
{
  CrankFilm *film = (CrankFilm*) object;
}


static void
crank_film_get_property (GObject    *object,
                         guint       prop_id,
                         GValue     *value,
                         GParamSpec *pspec)
{
  CrankFilm *film = (CrankFilm*) object;
  switch (prop_id)
    {
    case PROP_NLAYERS:
      g_value_set_uint (value, film->layers->len);
      break;

    case PROP_WIDTH:
      g_value_set_uint (value, film->width);
      break;

    case PROP_HEIGHT:
      g_value_set_uint (value, film->height);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
crank_film_dispose (GObject *object)
{
  CrankFilm *film = (CrankFilm*) object;
  g_ptr_array_unref (film->layers);
}


//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_film_new:
 * @render_layer: (transfer none): First render layer.
 * @...: Rest list of render layer ends with %NULL.
 *
 * Constructs a film with given layers.
 *
 * Returns: (transfer full): Newly constructed film.
 */
CrankFilm*
crank_film_new (CrankRenderLayer *render_layer, ...)
{
  CrankFilm *self;
  va_list varargs;

  va_start (varargs, render_layer);

  self = crank_film_new_va (render_layer, varargs);

  va_end (varargs);

  return self;
}

/**
 * crank_film_new_va:
 * @render_layer: (transfer none): First render layer.
 * @varargs: Rest list of render layer ends with %NULL.
 *
 * Constructs a film with given layers.
 *
 * Returns: (transfer full): Newly constructed film.
 */
CrankFilm*
crank_film_new_va (CrankRenderLayer *render_layer, va_list varargs)
{
  CrankFilm *self = g_object_new (CRANK_TYPE_FILM, NULL);

  g_ptr_array_add (self->layers, g_object_ref (render_layer));

  for (render_layer = va_arg (varargs, CrankRenderLayer*);
       render_layer != NULL;
       render_layer = va_arg (varargs, CrankRenderLayer*))
    {
      g_ptr_array_add (self->layers, g_object_ref (render_layer));
    }
  return self;
}

/**
 * crank_film_new_with_layers:
 * @render_layers: (array length=nrender_layers): Render layers.
 * @nrender_layers: Length of @render_layers
 *
 * Constructs a film with given layers.
 *
 * Returns: (transfer full): Newly constructed film.
 */
CrankFilm*
crank_film_new_with_layers (CrankRenderLayer **render_layers,
                            const guint        nrender_layers)
{
  CrankFilm *self = g_object_new (CRANK_TYPE_FILM, NULL);
  guint i;

  for (i = 0; i < nrender_layers; i++)
    {
      g_ptr_array_add (self->layers, g_object_ref (render_layers[i]));
    }
  return self;
}


/**
 * crank_film_new_old:
 * @cogl_context: A CoglContext to initialize with.
 * @width: Width of film.
 * @height: Height of film.
 * @error: Error
 *
 * Constructs a film with given size.
 *
 * Returns: (transfer full): Newly created film.
 */
CrankFilm*
crank_film_new_old (CoglContext  *cogl_context,
                    const guint   width,
                    const guint   height,
                    GError      **error)
{
  CrankRenderLayer *layers[8];
  GError *merr = NULL;
  guint i;

  for (i = 0; i < 2;i++)
    {
      layers[i] = (CrankRenderLayer*) crank_render_layer_array_new ();
    }

  for (i = 2; i < 8;i++)
    {
      layers[i] = (CrankRenderLayer*) crank_render_layer_texture_new (cogl_context,
                                                                      width,
                                                                      height,
                                                                      NULL,
                                                                      &merr);

      if (merr != NULL)
        {
          g_propagate_error (error, merr);
          return NULL;
        }
    }

  crank_render_layer_set_name (layers[0], "renderables");
  crank_render_layer_set_name (layers[1], "lightables");

  crank_render_layer_set_name (layers[2], "geom");
  crank_render_layer_set_name (layers[3], "color");
  crank_render_layer_set_name (layers[4], "mat");
  crank_render_layer_set_name (layers[5], "light");
  crank_render_layer_set_name (layers[6], "light-ex");
  crank_render_layer_set_name (layers[7], "result");

  return crank_film_new_with_layers (layers, 8);
}

//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_film_get_nlayers:
 * @film: A Film.
 *
 * Gets number of layers in the @film.
 *
 * Returns: Number of layers.
 */
guint
crank_film_get_nlayers (CrankFilm *film)
{
  return film->layers->len;
}


/**
 * crank_film_get_width:
 * @film: A Film.
 *
 * Gets width of this film.
 *
 * Returns: Width of film.
 */
guint
crank_film_get_width (CrankFilm *film)
{
  return film->width;
}

/**
 * crank_film_get_height:
 * @film: A Film.
 *
 * Gets height of this film.
 *
 * Returns: Height of film.
 */
guint
crank_film_get_height (CrankFilm *film)
{
  return film->height;
}







///////// Layers ///////////////////////////////////////////////////////////////

/**
 * crank_film_get_layer:
 * @film: A Film.
 * @index: A Index.
 *
 * Gets layer on @film at @index.
 *
 * Returns: (transfer none): A Layer.
 */
CrankRenderLayer*
crank_film_get_layer (CrankFilm   *film,
                      const guint  index)
{
  return film->layers->pdata[index];
}

/**
 * crank_film_get_layer_by_qname:
 * @film: A Film.
 * @name: Name of layer.
 *
 * Gets layer on @film by @name.
 *
 * Returns: (transfer none) (nullable): A Layer with @name.
 */
CrankRenderLayer*
crank_film_get_layer_by_qname (CrankFilm    *film,
                               const GQuark  name)
{
  guint i;

  for (i = 0; i < film->layers->len; i++)
    {
      CrankRenderLayer *layer = film->layers->pdata[i];

      if (name == crank_render_layer_get_qname (layer))
        return layer;
    }

  return NULL;
}

/**
 * crank_film_index_of_layer:
 * @film: A Film.
 * @layer: A Layer.
 *
 * Gets index of layer.
 *
 * Returns: index of layer, or -1 if not found.
 */
gint
crank_film_index_of_layer (CrankFilm        *film,
                           CrankRenderLayer *layer)
{
  guint i;

  for (i = 0; i < film->layers->len; i++)
    {
      if (film->layers->pdata[i] == layer)
        return i;
    }
  return -1;
}

/**
 * crank_film_index_of_layer_by_qname:
 * @film: A Film.
 * @name: Name of layer.
 *
 * Gets index of layer by its name.
 *
 * Returns: index of layer, or -1 if not found.
 */
gint
crank_film_index_of_layer_by_qname (CrankFilm    *film,
                                    const GQuark  name)
{
  guint i;

  for (i = 0; i < film->layers->len; i++)
    {
      CrankRenderLayer *layer = film->layers->pdata[i];
      if (crank_render_layer_get_qname (layer) == name)
        return i;
    }
  return -1;
}






//////// Textures and Framebuffers /////////////////////////////////////////////

/**
 * crank_film_get_texture:
 * @film: A Film.
 * @index: Index of texture.
 *
 * Gets a texture at @index.
 *
 * Returns: (transfer none): Texture at @index.
 */
CoglTexture*
crank_film_get_texture (CrankFilm   *film,
                        const guint  index)
{
  return crank_render_layer_texture_get_texture (
      (CrankRenderLayerTexture*) film->layers->pdata[index] );
}


/**
 * crank_film_get_framebuffer:
 * @film: A Film.
 * @index: Index of framebuffer to get.
 *
 * Gets a framebuffer associated to a texture.
 *
 * Returns: (transfer none) (type CoglFramebuffer): A Framebuffer.
 */
CoglOffscreen*
crank_film_get_framebuffer (CrankFilm   *film,
                            const guint  index)
{
  return crank_render_layer_texture_get_framebuffer (
      (CrankRenderLayerTexture*) film->layers->pdata[index] );
}
