#ifndef CRANKRENDERPROCESSDEFERRED_H
#define CRANKRENDERPROCESSDEFERRED_H

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
#error crankrenderprocessdeferred.h cannot be included directly: include crankvisual.h
#endif

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankprojection.h"

#include "crankrenderable.h"

#include "crankrenderlayercluster.h"

#include "crankfilm.h"
#include "crankcamera.h"


//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_PROCESS_DEFERRED (crank_render_process_deferred_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderProcessDeferred,
                      crank_render_process_deferred,
                      CRANK, RENDER_PROCESS_DEFERRED,
                      CrankRenderProcess)

/**
 * CrankRenderProcessDeferred:
 *
 * Represents a render process.
 */







//////// Public functions //////////////////////////////////////////////////////

//////// Constructors //////////////////////////////////////////////////////////

CrankRenderProcessDeferred *crank_render_process_deferred_new (void);








//////// Rendering operations //////////////////////////////////////////////////

GPtrArray  *crank_render_process_deferred_get_culled_array (CrankRenderProcessDeferred *process,
                                                            GPtrArray                  *entities,
                                                            CrankPlace3                *place,
                                                            CrankTrans3                *position,
                                                            CrankProjection            *projection,
                                                            const guint                 tindex);

GPtrArray  *crank_render_process_deferred_get_culled_rarray(CrankRenderProcessDeferred *process,
                                                            GPtrArray                  *entities,
                                                            CrankPlace3                *place,
                                                            CrankTrans3                *position,
                                                            CrankProjection            *projection);

GPtrArray  *crank_render_process_deferred_get_culled_larray(CrankRenderProcessDeferred *process,
                                                            GPtrArray                  *entities,
                                                            CrankPlace3                *place,
                                                            CrankTrans3                *position,
                                                            CrankProjection            *projection);

void    crank_render_process_deferred_render_geom_cluster(CrankRenderProcessDeferred *process,
                                                          CrankRenderLayerCluster    *entities,
                                                          CrankTrans3                *position,
                                                          CrankProjection            *projection,
                                                          CoglFramebuffer            *framebuffer);

void    crank_render_process_deferred_render_color_cluster(CrankRenderProcessDeferred *process,
                                                           CrankRenderLayerCluster    *entities,
                                                           CrankTrans3                *position,
                                                           CrankProjection            *projection,
                                                           CoglFramebuffer            *framebuffer);

void    crank_render_process_deferred_render_light_cluster(CrankRenderProcessDeferred *process,
                                                           CrankRenderLayerCluster    *entities,
                                                           CrankTrans3                *position,
                                                           CrankProjection            *projection,
                                                           CoglTexture                *tex_geom,
                                                           CoglTexture                *tex_color,
                                                           CoglTexture                *tex_mater,
                                                           CoglFramebuffer            *framebuffer);

void    crank_render_process_deferred_render_geom_array(CrankRenderProcessDeferred *process,
                                                        GPtrArray                  *entities,
                                                        CrankTrans3                *position,
                                                        CrankProjection            *projection,
                                                        CoglFramebuffer            *framebuffer);

void    crank_render_process_deferred_render_color_array(CrankRenderProcessDeferred *process,
                                                         GPtrArray                  *entities,
                                                         CrankTrans3                *position,
                                                         CrankProjection            *projection,
                                                         CoglFramebuffer            *framebuffer);

void    crank_render_process_deferred_render_light_array(CrankRenderProcessDeferred *process,
                                                         GPtrArray                  *entities,
                                                         CrankTrans3                *position,
                                                         CrankProjection            *projection,
                                                         CoglTexture                *tex_geom,
                                                         CoglTexture                *tex_color,
                                                         CoglTexture                *tex_mater,
                                                         CoglFramebuffer            *framebuffer);


void    crank_render_process_deferred_render_geom_entity (CrankRenderProcessDeferred *process,
                                                          CrankEntity3               *entity,
                                                          CrankRenderable            *renderable,
                                                          CrankTrans3                *ipos,
                                                          CrankProjection            *projection,
                                                          CoglFramebuffer            *framebuffer);

void    crank_render_process_deferred_render_color_entity(CrankRenderProcessDeferred *process,
                                                          CrankEntity3               *entity,
                                                          CrankRenderable            *renderable,
                                                          CrankTrans3                *ipos,
                                                          CrankProjection            *projection,
                                                          CoglFramebuffer            *framebuffer);

void    crank_render_process_deferred_render_light_entity(CrankRenderProcessDeferred *process,
                                                          CrankEntity3               *entity,
                                                          CrankLightable             *lightable,
                                                          CrankTrans3                *ipos,
                                                          CrankProjection            *projection,
                                                          CoglTexture                *tex_geom,
                                                          CoglTexture                *tex_color,
                                                          CoglTexture                *tex_mater,
                                                          CoglFramebuffer            *framebuffer);







#endif
