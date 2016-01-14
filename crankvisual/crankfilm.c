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

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <cogl/cogl2-experimental.h>

#include "crankfilm.h"

//////// List of virtual functions /////////////////////////////////////////////

static void     crank_film_initable_init (GInitableIface* iface);

static void     crank_film_constructed (GObject *object);

static void     crank_film_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec);

static void     crank_film_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec);

static void     crank_film_dispose (GObject *object);

static gboolean crank_film_initable_inst_init (GInitable     *initable,
                                               GCancellable  *cancellable,
                                               GError       **error);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_COGL_CONTEXT,
  PROP_WIDTH,
  PROP_HEIGHT,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankFilm
{
  GObject parent;

  CoglContext *cogl_context;
  guint width;
  guint height;

  CoglTexture   *textures[6];
  CoglOffscreen *fbuffers[6];
};

G_DEFINE_TYPE_WITH_CODE (CrankFilm,
                         crank_film,
                         G_TYPE_OBJECT,
                         {
                           G_IMPLEMENT_INTERFACE (G_TYPE_INITABLE, crank_film_initable_init);
                         })

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_film_init (CrankFilm *self)
{
}

static void
crank_film_class_init (CrankFilmClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->constructed = crank_film_constructed;
  c_gobject->get_property = crank_film_get_property;
  c_gobject->set_property = crank_film_set_property;
  c_gobject->dispose = crank_film_dispose;


  /**
   * CrankFilm:cogl-context: (type CoglContext)
   *
   * CoglContext to initialize textures and framebuffers
   */
  pspecs[PROP_COGL_CONTEXT] =
  g_param_spec_pointer ("cogl-context", "CoglContext",
                        "CoglContext to initialize textures and framebuffers",
                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_WIDTH] =
  g_param_spec_uint ("width", "width",
                     "Width of film",
                     0, G_MAXUINT, 0,
                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_HEIGHT] =
  g_param_spec_uint ("height", "height",
                     "Height of film",
                     0, G_MAXUINT, 0,
                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}

static void
crank_film_initable_init (GInitableIface *iface)
{
  iface->init = crank_film_initable_inst_init;
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_film_constructed (GObject *object)
{
  CrankFilm *film = (CrankFilm*) object;

  // Build Textures
  film->textures[0] = cogl_texture_2d_new_with_size (film->cogl_context, film->width, film->height);
  film->textures[1] = cogl_texture_2d_new_with_size (film->cogl_context, film->width, film->height);
  film->textures[2] = cogl_texture_2d_new_with_size (film->cogl_context, film->width, film->height);
  film->textures[3] = cogl_texture_2d_new_with_size (film->cogl_context, film->width, film->height);
  film->textures[4] = cogl_texture_2d_new_with_size (film->cogl_context, film->width / 4, film->height / 4);
  film->textures[5] = cogl_texture_2d_new_with_size (film->cogl_context, film->width, film->height);

  film->fbuffers[0] = cogl_offscreen_new_with_texture (film->textures[0]);
  film->fbuffers[1] = cogl_offscreen_new_with_texture (film->textures[1]);
  film->fbuffers[2] = cogl_offscreen_new_with_texture (film->textures[2]);
  film->fbuffers[3] = cogl_offscreen_new_with_texture (film->textures[3]);
  film->fbuffers[4] = cogl_offscreen_new_with_texture (film->textures[4]);
  film->fbuffers[5] = cogl_offscreen_new_with_texture (film->textures[5]);
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
    case PROP_COGL_CONTEXT:
      g_value_set_pointer (value, film->cogl_context);
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
crank_film_set_property (GObject      *object,
                         guint         prop_id,
                         const GValue *value,
                         GParamSpec   *pspec)
{
  CrankFilm *film = (CrankFilm*) object;
  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
      film->cogl_context = g_value_get_pointer (value);
      break;

    case PROP_WIDTH:
      film->width = g_value_get_uint (value);
      break;

    case PROP_HEIGHT:
      film->height = g_value_get_uint (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_film_dispose (GObject *object)
{
  CrankFilm *film = (CrankFilm*) object;

  if (film->width != 0)
    {
      film->width = 0;
      film->height = 0;

      cogl_object_unref (film->fbuffers[0]);
      cogl_object_unref (film->fbuffers[1]);
      cogl_object_unref (film->fbuffers[2]);
      cogl_object_unref (film->fbuffers[3]);
      cogl_object_unref (film->fbuffers[4]);
      cogl_object_unref (film->fbuffers[5]);

      cogl_object_unref (film->textures[0]);
      cogl_object_unref (film->textures[1]);
      cogl_object_unref (film->textures[2]);
      cogl_object_unref (film->textures[3]);
      cogl_object_unref (film->textures[4]);
      cogl_object_unref (film->textures[5]);

      film->fbuffers[0] = NULL;
      film->fbuffers[1] = NULL;
      film->fbuffers[2] = NULL;
      film->fbuffers[3] = NULL;
      film->fbuffers[4] = NULL;
      film->fbuffers[5] = NULL;

      film->textures[0] = NULL;
      film->textures[1] = NULL;
      film->textures[2] = NULL;
      film->textures[3] = NULL;
      film->textures[4] = NULL;
      film->textures[5] = NULL;
    }
}

//////// GInitable /////////////////////////////////////////////////////////////

static gboolean
crank_film_initable_inst_init (GInitable     *initable,
                               GCancellable  *cancellable,
                               GError       **error)
{
  CrankFilm *film = (CrankFilm*) initable;
  guint i;

  for (i = 0; i < 6; i++)
    {
      GError *merr = NULL;
      cogl_framebuffer_allocate (film->fbuffers[i], &merr);

      if (merr != NULL)
        {
          g_propagate_prefixed_error (error, merr, "framebuffer %u: ", i);
          crank_film_dispose ((GObject*)film);
          return FALSE;
        }
    }
  return TRUE;
}

//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_film_new:
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
crank_film_new (CoglContext  *cogl_context,
                const guint   width,
                const guint   height,
                GError      **error)
{
  return (CrankFilm*) g_initable_new (CRANK_TYPE_FILM,
                                      NULL,
                                      error,
                                      "cogl-context", cogl_context,
                                      "width", width,
                                      "height", height,
                                      NULL);

}

//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_film_get_cogl_context:
 * @film: A Film.
 *
 * Gets #CoglContext of film.
 *
 * Returns: (transfer none): #CoglContext for this film.
 */
CoglContext*
crank_film_get_cogl_context (CrankFilm *film)
{
  return film->cogl_context;
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
  return film->textures[index];
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
  return film->fbuffers[index];
}
