#ifndef CRANKRENDERLAYERTEXTURE_H
#define CRANKRENDERLAYERTEXTURE_H

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
#error crankrenderlayertexture.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>

#include <cogl/cogl2-experimental.h>

#include "crankrenderlayer.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_LAYER_TEXTURE (crank_render_layer_texture_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderLayerTexture,
                      crank_render_layer_texture,
                      CRANK, RENDER_LAYER_TEXTURE,
                      CrankRenderLayer)


//////// Constructors //////////////////////////////////////////////////////////

CrankRenderLayerTexture    *crank_render_layer_texture_new (CoglContext   *cogl_context,
                                                            const guint    width,
                                                            const guint    height,
                                                            GCancellable  *cancellable,
                                                            GError       **error);

CrankRenderLayerTexture    *crank_render_layer_texture_new_with_components (CoglContext                  *cogl_context,
                                                                            const guint                   width,
                                                                            const guint                   height,
                                                                            const CoglTextureComponents   components,
                                                                            GCancellable                 *cancellable,
                                                                            GError                      **error);

CrankRenderLayerTexture    *crank_render_layer_texture_new_with_texture (CoglTexture  *texture,
                                                                         GCancellable *cancellable,
                                                                         GError      **error);


//////// Properties ////////////////////////////////////////////////////////////

guint                 crank_render_layer_texture_get_width       (CrankRenderLayerTexture *layer);

guint                 crank_render_layer_texture_get_height      (CrankRenderLayerTexture *layer);

CoglTextureComponents  crank_render_layer_texture_get_components (CrankRenderLayerTexture *layer);



CoglTexture          *crank_render_layer_texture_get_texture     (CrankRenderLayerTexture *layer);

CoglFramebuffer      *crank_render_layer_texture_get_framebuffer (CrankRenderLayerTexture *layer);




G_END_DECLS

#endif
