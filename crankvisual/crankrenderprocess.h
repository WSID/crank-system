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
  /*< private >*/
  GObjectClass  _parent;


  /*< public >*/
  void      (*render_at)  (CrankRenderProcess *process,
                           CrankPlace3        *place,
                           CrankTrans3        *position,
                           CrankProjection    *projection,
                           CrankFilm          *film,
                           const gint         *layer_map);


  gboolean  (*render_for) (CrankRenderProcess *process,
                           CrankCamera        *camera);


  /*< private >*/
  gpointer _DUMMY2;

  gpointer _DUMMY3;
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



guint   crank_render_process_get_result_layer_index (CrankRenderProcess *process);





//////// Rendering operations //////////////////////////////////////////////////

void    crank_render_process_render_at (CrankRenderProcess *process,
                                        CrankPlace3        *place,
                                        CrankTrans3        *position,
                                        CrankProjection    *projection,
                                        CrankFilm          *film,
                                        const gint         *layer_map);


gboolean crank_render_process_render_for (CrankRenderProcess *process,
                                          CrankCamera        *camera);




gboolean crank_render_process_check_layer (CrankRenderProcess *process,
                                           const gint          index,
                                           CrankRenderLayer   *layer);

gboolean crank_render_process_check_film (CrankRenderProcess *process,
                                          CrankFilm          *film,
                                          const gint         *layer_map);







#endif
