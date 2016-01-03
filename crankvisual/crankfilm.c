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

#include "crankfilm.h"

//////// List of virtual functions /////////////////////////////////////////////

static void   crank_film_get_property (GObject    *object,
                                       guint       prop_id,
                                       GValue     *value,
                                       GParamSpec *pspec);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_N_TEXTURES,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankFilm
{
  GObject parent;

  GPtrArray *textures;
  GPtrArray *buffers;
};

G_DEFINE_TYPE (CrankFilm,
               crank_film,
               G_TYPE_OBJECT)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_film_init (CrankFilm *self)
{
  self->textures = g_ptr_array_new_with_free_func ((GDestroyNotify)cogl_object_unref);
  self->buffers = NULL;
}

static void
crank_film_class_init (CrankFilmClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_film_get_property;

  pspecs[PROP_N_TEXTURES] =
  g_param_spec_uint ("n-textures", "Number of textures",
                     "Number of textures in this film",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_film_get_property (GObject    *object,
                         guint       prop_id,
                         GValue     *value,
                         GParamSpec *pspec)
{
  CrankFilm *film = (CrankFilm*) object;
  switch (prop_id)
    {
    case PROP_N_TEXTURES:
      g_value_set_uint (value, crank_film_get_n_textures (film));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_film_new:
 *
 * Constructs an empty film.
 *
 * Returns: (transfer full): Newly created film.
 */
CrankFilm*
crank_film_new ()
{
  CrankFilm *film = g_object_new (CRANK_TYPE_FILM, NULL);

  film->textures = g_ptr_array_new_with_free_func (cogl_object_unref);

  return film;
}

/**
 * crank_film_add_texture:
 * @film: A Film.
 * @texture: A texture.
 *
 * Adds a texture to a film.
 */
void
crank_film_add_texture (CrankFilm   *film,
                        CoglTexture *texture)
{
  if (film->buffers != NULL)
    {
      g_warning ("Framebuffers are allocated!");
      return;
    }

  g_ptr_array_add (film->textures, texture);
}

/**
 * crank_film_remove_texture:
 * @film: A Film.
 * @texture: A texture.
 *
 * Removes a texture from a film.
 */
void
crank_film_remove_texture (CrankFilm   *film,
                           CoglTexture *texture)
{
  if (film->buffers != NULL)
    {
      g_warning ("Framebuffers are allocated!");
      return;
    }

  g_ptr_array_remove (film->textures, texture);
}

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
  return (CoglTexture*) g_ptr_array_index (film->textures, index);
}

/**
 * crank_film_get_n_textures:
 * @film: A Film.
 *
 * Gets count of textures in the film.
 *
 * Returns: number of textures in film.
 */
guint
crank_film_get_n_textures (CrankFilm *film)
{
  return film->textures->len;
}


/**
 * crank_film_allocate:
 * @film: A Film.
 * @error: Error pointer to receive error if happens.
 *
 * Allocates textures and build framebuffers, or nop if they are already created.
 */
void
crank_film_allocate (CrankFilm  *film,
                     GError    **error)
{
  guint i;

  if (film->buffers != NULL)
    return;

  film->buffers = g_ptr_array_new_full (film->textures->len,
                                        cogl_object_unref);

  for (i = 0; i < film->textures->len; i++)
    {
      CoglTexture *texture = (CoglTexture*) film->textures->pdata[i];
      CoglOffscreen *buffer = cogl_offscreen_new_with_texture (texture);
      GError *merr = NULL;

      g_ptr_array_add (film->buffers, buffer);

      cogl_framebuffer_allocate ((CoglFramebuffer*)buffer, &merr);

      if (merr != NULL)
        {
          g_propagate_prefixed_error (error, merr, "Film allocate[%u]: ", i);
          g_ptr_array_unref (film->buffers);
          return;
        }
    }
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
  if (film->buffers == NULL)
    return NULL;

  return (CoglOffscreen*) film->buffers->pdata[index];
}
