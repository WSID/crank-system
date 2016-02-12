#ifndef CRANKRENDERABLE_H
#define CRANKRENDERABLE_H

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

#ifndef _CRANKVISUAL_INSIDE
#error crankrenderable.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankshape.h"
#include "crankprojection.h"
#include "crankvisible.h"

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_RENDERABLE (crank_renderable_get_type ())
G_DECLARE_DERIVABLE_TYPE (CrankRenderable,
                          crank_renderable,
                          CRANK, RENDERABLE,
                          CrankVisible)

/**
 * CrankRenderable:
 *
 * Instance Structure.
 */

/**
 * CrankRenderableClass:
 * @render_geom: Slot for crank_renderable_render_geom()
 * @render_color: Slot for crank_renderable_render_color()
 * @render_material: Slot for crank_renderable_render_material()
 *
 * Virtual function table for #CrankRenderable.
 */
struct _CrankRenderableClass
{
  /*< private >*/
  CrankVisibleClass _parent;

  /*< public >*/

  void  (*render_geom)  (CrankRenderable *renderable,
                         CrankTrans3     *position,
                         CrankProjection *projection,
                         CoglFramebuffer *framebuffer);

  void  (*render_color) (CrankRenderable *renderable,
                         CrankTrans3     *position,
                         CrankProjection *projection,
                         CoglFramebuffer *framebuffer);

  void  (*render_material) (CrankRenderable *renderable,
                            CrankTrans3     *position,
                            CrankProjection *projection,
                            CoglFramebuffer *framebuffer);
};



//////// Public functions //////////////////////////////////////////////////////
//
void
crank_renderable_render_geom (CrankRenderable *renderable,
                              CrankTrans3     *position,
                              CrankProjection *projection,
                              CoglFramebuffer *framebuffer);

void
crank_renderable_render_color (CrankRenderable *renderable,
                               CrankTrans3     *position,
                               CrankProjection *projection,
                               CoglFramebuffer *framebuffer);

void
crank_renderable_render_material (CrankRenderable *renderable,
                                  CrankTrans3     *position,
                                  CrankProjection *projection,
                                  CoglFramebuffer *framebuffer);

#endif
