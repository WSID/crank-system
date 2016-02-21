#ifndef CRANKRENDERPROCESS_H
#define CRANKRENDERPROCESS_H

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
#error crankrenderprocess.h cannot be included directly: include crankvisual.h
#endif

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankprojection.h"
#include "crankfilm.h"
#include "crankcamera.h"


//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_PROCESS (crank_render_process_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankRenderProcess,
                          crank_render_process,
                          CRANK, RENDER_PROCESS,
                          GObject)

/**
 * CrankRenderProcess:
 *
 * Represents a render process.
 */

/**
 * CrankRenderProcessClass:
 *
 * Virtual function table for #CrankRenderProcess.
 */
struct _CrankRenderProcessClass
{
  GObjectClass  _parent;
};






//////// Public functions //////////////////////////////////////////////////////

//////// Layer functinos ///////////////////////////////////////////////////////

guint   crank_render_process_get_nlayers    (CrankRenderProcess *process);

GType   crank_render_process_get_layer_type (CrankRenderProcess *process,
                                             const guint         index);

GQuark  crank_render_process_get_layer_name (CrankRenderProcess *process,
                                             const guint         index);


void    crank_render_process_insert_layer   (CrankRenderProcess *process,
                                             const guint         index,
                                             const GQuark        name,
                                             const GType         type);

void    crank_render_process_append_layer   (CrankRenderProcess *process,
                                             const GQuark        name,
                                             const GType         type);

void    crank_render_process_prepend_layer  (CrankRenderProcess *process,
                                             const GQuark        name,
                                             const GType         type);


gint    crank_render_process_index_of_layer (CrankRenderProcess *process,
                                             const GQuark        name);






//////// Rendering operations //////////////////////////////////////////////////

GList  *crank_render_process_get_culled_list (CrankRenderProcess *process,
                                             CrankPlace3       *place,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection,
                                             const guint        tindex);

GList  *crank_render_process_get_culled_rlist(CrankRenderProcess *process,
                                             CrankPlace3       *place,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection);

GList  *crank_render_process_get_culled_llist(CrankRenderProcess *process,
                                             CrankPlace3       *place,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection);


GPtrArray  *crank_render_process_get_culled_array (CrankRenderProcess *process,
                                                  GPtrArray         *entities,
                                                  CrankPlace3       *place,
                                                  CrankTrans3       *position,
                                                  CrankProjection   *projection,
                                                  const guint        tindex);

GPtrArray  *crank_render_process_get_culled_rarray(CrankRenderProcess *process,
                                                  GPtrArray         *entities,
                                                  CrankPlace3       *place,
                                                  CrankTrans3       *position,
                                                  CrankProjection   *projection);

GPtrArray  *crank_render_process_get_culled_larray(CrankRenderProcess *process,
                                                  GPtrArray         *entities,
                                                  CrankPlace3       *place,
                                                  CrankTrans3       *position,
                                                  CrankProjection   *projection);


void    crank_render_process_render_geom_at (CrankRenderProcess *process,
                                             CrankPlace3        *place,
                                             CrankTrans3        *position,
                                             CrankProjection    *projection,
                                             CoglFramebuffer    *framebuffer);

void    crank_render_process_render_color_at (CrankRenderProcess *process,
                                              CrankPlace3        *place,
                                              CrankTrans3        *position,
                                              CrankProjection    *projection,
                                              CoglFramebuffer    *framebuffer);

void    crank_render_process_render_light_at (CrankRenderProcess *process,
                                              CrankPlace3        *place,
                                              CrankTrans3        *position,
                                              CrankProjection    *projection,
                                              CoglTexture        *tex_geom,
                                              CoglTexture        *tex_color,
                                              CoglTexture        *tex_mater,
                                              CoglFramebuffer    *framebuffer);


void    crank_render_process_render_geom_list (CrankRenderProcess *process,
                                               GList              *entities,
                                               CrankTrans3        *position,
                                               CrankProjection    *projection,
                                               CoglFramebuffer    *framebuffer);

void    crank_render_process_render_color_list(CrankRenderProcess *process,
                                               GList              *entities,
                                               CrankTrans3        *position,
                                               CrankProjection    *projection,
                                               CoglFramebuffer    *framebuffer);

void    crank_render_process_render_light_list (CrankRenderProcess *process,
                                                GList              *entities,
                                                CrankTrans3        *position,
                                                CrankProjection    *projection,
                                                CoglTexture        *tex_geom,
                                                CoglTexture        *tex_color,
                                                CoglTexture        *tex_mater,
                                                CoglFramebuffer    *framebuffer);


void    crank_render_process_render_geom_array(CrankRenderProcess *process,
                                               GPtrArray          *entities,
                                               CrankTrans3        *position,
                                               CrankProjection    *projection,
                                               CoglFramebuffer    *framebuffer);

void    crank_render_process_render_color_array(CrankRenderProcess *process,
                                                GPtrArray          *entities,
                                                CrankTrans3        *position,
                                                CrankProjection    *projection,
                                                CoglFramebuffer    *framebuffer);

void    crank_render_process_render_light_array(CrankRenderProcess *process,
                                                GPtrArray          *entities,
                                                CrankTrans3        *position,
                                                CrankProjection    *projection,
                                                CoglTexture        *tex_geom,
                                                CoglTexture        *tex_color,
                                                CoglTexture        *tex_mater,
                                                CoglFramebuffer    *framebuffer);


void    crank_render_process_render_geom_entity (CrankRenderProcess *process,
                                                 CrankEntity3       *entity,
                                                 CrankTrans3        *ipos,
                                                 CrankProjection    *projection,
                                                 CoglFramebuffer    *framebuffer);

void    crank_render_process_render_color_entity(CrankRenderProcess *process,
                                                 CrankEntity3       *entity,
                                                 CrankTrans3        *ipos,
                                                 CrankProjection    *projection,
                                                 CoglFramebuffer    *framebuffer);

void    crank_render_process_render_light_entity(CrankRenderProcess *process,
                                                 CrankEntity3       *entity,
                                                 CrankTrans3        *ipos,
                                                 CrankProjection    *projection,
                                                 CoglTexture        *tex_geom,
                                                 CoglTexture        *tex_color,
                                                 CoglTexture        *tex_mater,
                                                 CoglFramebuffer    *framebuffer);



void    crank_render_process_render_at (CrankRenderProcess *process,
                                        CrankPlace3        *place,
                                        CrankTrans3        *position,
                                        CrankProjection    *projection,
                                        CrankFilm          *film);


gboolean crank_render_process_render_for (CrankRenderProcess *process,
                                          CrankCamera        *camera);


gboolean crank_render_process_check_layer (CrankRenderProcess *process,
                                           const gint          index,
                                           CrankRenderLayer   *layer);

gboolean crank_render_process_check_film (CrankRenderProcess *process,
                                          CrankFilm          *film,
                                          const gint         *layer_map);







#endif
