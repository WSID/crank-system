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

#include "crankrenderable.h"

/**
 * SECTION: crankrenderable
 * @title: CrankRenderable
 * @short_description: Base Class for renderable class.
 *
 * #CrankRenderable class provides common interface for rendering.
 */

//////// List of virtual functions /////////////////////////////////////////////

static void crank_renderable_get_property (GObject    *object,
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

G_DEFINE_ABSTRACT_TYPE (CrankRenderable,
                        crank_renderable,
                        G_TYPE_OBJECT)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_renderable_init (CrankRenderable *self)
{
}

static void
crank_renderable_class_init (CrankRenderableClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_renderable_get_property;

  pspecs[PROP_VISIBLE_RADIUS] =
  g_param_spec_float ("visible-radius", "Visible Radius", "Visible radius of renderable.",
                      0, G_MAXFLOAT, 0,
                      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_renderable_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  CrankRenderable *renderable = (CrankRenderable*)object;

  switch (prop_id)
    {
    case PROP_VISIBLE_RADIUS:
      g_value_set_float (value, crank_renderable_get_visible_radius (renderable));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_renderable_get_visible_radius:
 * @renderable: A Renderable.
 *
 * Gets visible radius of this renderable.
 *
 * Returns: visible radius of @renderable.
 */
gfloat
crank_renderable_get_visible_radius (CrankRenderable *renderable)
{
  CrankRenderableClass *c = CRANK_RENDERABLE_GET_CLASS (renderable);

  return c->get_visible_radius (renderable);
}

/**
 * crank_renderable_render_geom:
 * @renderable: A Renderable.
 * @position: Relative position from camera.
 * @framebuffer: A Framebuffer
 *
 * Render geometry information on given framebuffer.
 *
 * On framebuffer, RG channel will be used for depth, BA channel will be used
 * for normals.
 */
void
crank_renderable_render_geom (CrankRenderable *renderable,
                              CrankTrans3     *position,
                              CoglFramebuffer *framebuffer)
{
  CrankRenderableClass *c = CRANK_RENDERABLE_GET_CLASS (renderable);

  return c->render_geom (renderable, position, framebuffer);
}

/**
 * crank_renderable_render_color:
 * @renderable: A Renderable.
 * @position: Relative position from camera.
 * @framebuffer: A Framebuffer
 *
 * Render color information on given framebuffer.
 *
 * On framebuffer, RGB channel will be used for color value. for A, currently
 * not used.
 */
void
crank_renderable_render_color (CrankRenderable *renderable,
                               CrankTrans3     *position,
                               CoglFramebuffer *framebuffer)
{
  CrankRenderableClass *c = CRANK_RENDERABLE_GET_CLASS (renderable);

  return c->render_color (renderable, position, framebuffer);
}

/**
 * crank_renderable_render_material:
 * @renderable: A Renderable.
 * @position: Relative position from camera.
 * @framebuffer: A Framebuffer
 *
 * Render material information on given framebuffer.
 *
 * TODO: add material param to there.
 */
void
crank_renderable_render_material (CrankRenderable *renderable,
                                  CrankTrans3     *position,
                                  CoglFramebuffer *framebuffer)
{
  CrankRenderableClass *c = CRANK_RENDERABLE_GET_CLASS (renderable);

  return c->render_material (renderable, position, framebuffer);
}
