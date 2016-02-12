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
#include "crankcamera.h"
#include "crankvisible.h"

/**
 * SECTION: crankrenderable
 * @title: CrankRenderable
 * @short_description: Base Class for renderable class.
 *
 * #CrankRenderable class provides common interface for rendering.
 */



//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankRenderable,
                        crank_renderable,
                        CRANK_TYPE_VISIBLE)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_renderable_init (CrankRenderable *self)
{
}

static void
crank_renderable_class_init (CrankRenderableClass *c)
{
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
 * @position: Relative position from view.
 * @projection: Projection of view.
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
                              CrankProjection *projection,
                              CoglFramebuffer *framebuffer)
{
  CrankRenderableClass *c = CRANK_RENDERABLE_GET_CLASS (renderable);

  return c->render_geom (renderable, position, projection, framebuffer);
}

/**
 * crank_renderable_render_color:
 * @renderable: A Renderable.
 * @position: Relative position from view.
 * @projection: Projection of view.
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
                               CrankProjection *projection,
                               CoglFramebuffer *framebuffer)
{
  CrankRenderableClass *c = CRANK_RENDERABLE_GET_CLASS (renderable);

  return c->render_color (renderable, position, projection, framebuffer);
}

/**
 * crank_renderable_render_material:
 * @renderable: A Renderable.
 * @position: Relative position from view.
 * @projection: Projection of view.
 * @framebuffer: A Framebuffer
 *
 * Render material information on given framebuffer.
 *
 * TODO: add material param to there.
 */
void
crank_renderable_render_material (CrankRenderable *renderable,
                                  CrankTrans3     *position,
                                  CrankProjection *projection,
                                  CoglFramebuffer *framebuffer)
{
  CrankRenderableClass *c = CRANK_RENDERABLE_GET_CLASS (renderable);

  return c->render_material (renderable, position, projection, framebuffer);
}
