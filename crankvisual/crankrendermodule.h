#ifndef CRANKRENDERMODULE_H
#define CRANKRENDERMODULE_H

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
#error crankrendermodule.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankrenderable.h"
#include "cranklightable.h"

#include "crankfilm.h"
#include "crankcamera.h"

//////// Type Definition ///////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_MODULE (crank_render_module_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderModule,
                      crank_render_module,
                      CRANK, RENDER_MODULE,
                      CrankCompositable)

/**
 * CrankRenderModule:
 *
 * Instance Structure.
 */


//////// Constructors //////////////////////////////////////////////////////////

CrankRenderModule *crank_render_module_new (CoglContext *cogl_context);







//////// Public functions //////////////////////////////////////////////////////
GList  *crank_render_module_get_culled_list (CrankRenderModule *module,
                                             CrankPlace3       *place,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection,
                                             const guint        tindex);

GList  *crank_render_module_get_culled_rlist(CrankRenderModule *module,
                                             CrankPlace3       *place,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection);

GList  *crank_render_module_get_culled_llist(CrankRenderModule *module,
                                             CrankPlace3       *place,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection);


GPtrArray  *crank_render_module_get_culled_array (CrankRenderModule *module,
                                                  GPtrArray         *entities,
                                                  CrankPlace3       *place,
                                                  CrankTrans3       *position,
                                                  CrankProjection   *projection,
                                                  const guint        tindex);

GPtrArray  *crank_render_module_get_culled_rarray(CrankRenderModule *module,
                                                  GPtrArray         *entities,
                                                  CrankPlace3       *place,
                                                  CrankTrans3       *position,
                                                  CrankProjection   *projection);

GPtrArray  *crank_render_module_get_culled_larray(CrankRenderModule *module,
                                                  GPtrArray         *entities,
                                                  CrankPlace3       *place,
                                                  CrankTrans3       *position,
                                                  CrankProjection   *projection);





void    crank_render_module_render_geom_at (CrankRenderModule *module,
                                            CrankPlace3       *place,
                                            CrankTrans3       *position,
                                            CrankProjection   *projection,
                                            CoglFramebuffer   *framebuffer);

void    crank_render_module_render_color_at (CrankRenderModule *module,
                                             CrankPlace3       *place,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection,
                                             CoglFramebuffer   *framebuffer);

void    crank_render_module_render_light_at (CrankRenderModule *module,
                                             CrankPlace3       *place,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection,
                                             CoglTexture       *tex_geom,
                                             CoglTexture       *tex_color,
                                             CoglTexture       *tex_mater,
                                             CoglFramebuffer   *framebuffer);


void    crank_render_module_render_geom_list (CrankRenderModule *module,
                                              GList             *entities,
                                              CrankTrans3       *position,
                                              CrankProjection   *projection,
                                              CoglFramebuffer   *framebuffer);

void    crank_render_module_render_color_list(CrankRenderModule *module,
                                              GList             *entities,
                                              CrankTrans3       *position,
                                              CrankProjection   *projection,
                                              CoglFramebuffer   *framebuffer);

void    crank_render_module_render_light_list (CrankRenderModule *module,
                                               GList             *entities,
                                               CrankTrans3       *position,
                                               CrankProjection   *projection,
                                               CoglTexture       *tex_geom,
                                               CoglTexture       *tex_color,
                                               CoglTexture       *tex_mater,
                                               CoglFramebuffer   *framebuffer);


void    crank_render_module_render_geom_array(CrankRenderModule *module,
                                              GPtrArray         *entities,
                                              CrankTrans3       *position,
                                              CrankProjection   *projection,
                                              CoglFramebuffer   *framebuffer);

void    crank_render_module_render_color_array(CrankRenderModule *module,
                                              GPtrArray          *entities,
                                              CrankTrans3       *position,
                                              CrankProjection   *projection,
                                              CoglFramebuffer   *framebuffer);

void    crank_render_module_render_light_array(CrankRenderModule *module,
                                               GPtrArray         *entities,
                                               CrankTrans3       *position,
                                               CrankProjection   *projection,
                                               CoglTexture       *tex_geom,
                                               CoglTexture       *tex_color,
                                               CoglTexture       *tex_mater,
                                               CoglFramebuffer   *framebuffer);


void    crank_render_module_render_geom_entity (CrankRenderModule *module,
                                                CrankEntity3      *entity,
                                                CrankTrans3       *ipos,
                                                CrankProjection   *projection,
                                                CoglFramebuffer   *framebuffer);

void    crank_render_module_render_color_entity(CrankRenderModule *module,
                                                CrankEntity3      *entity,
                                                CrankTrans3       *ipos,
                                                CrankProjection   *projection,
                                                CoglFramebuffer   *framebuffer);

void    crank_render_module_render_light_entity(CrankRenderModule *module,
                                                CrankEntity3      *entity,
                                                CrankTrans3       *ipos,
                                               CrankProjection   *projection,
                                               CoglTexture       *tex_geom,
                                               CoglTexture       *tex_color,
                                               CoglTexture       *tex_mater,
                                               CoglFramebuffer   *framebuffer);



void    crank_render_module_render_at (CrankRenderModule *module,
                                       CrankPlace3       *place,
                                       CrankTrans3       *position,
                                       CrankProjection   *projection,
                                       CrankFilm         *film);



void    crank_render_module_add_camera (CrankRenderModule *module,
                                        CrankCamera       *camera);

void    crank_render_module_remove_camera (CrankRenderModule *module,
                                           CrankCamera       *camera);

guint   crank_render_module_get_n_camera (CrankRenderModule *module);




#endif
