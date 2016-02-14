#ifndef CRANK_RENDER_STEP_H
#define CRANK_RENDER_STEP_H

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

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>

#include "crankshape.h"
#include "crankprojection.h"
#include "crankrenderlayer.h"


G_BEGIN_DECLS

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_STEP (crank_render_step_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankRenderStep,
                          crank_render_step,
                          CRANK, RENDER_STEP,
                          GObject)

struct _CrankRenderStepClass
{
  GObjectClass parent;

  void (*render)  (CrankRenderStep   *step,
                   GPtrArray        **items,
                   CrankRenderLayer **layers,
                   CrankTrans3       *position,
                   CrankProjection   *projection,
                   CrankRenderLayer  *target_layer);

  CrankRenderLayer *(*create_layer) (CrankRenderStep  *step,
                                     const guint       width,
                                     const guint       height,
                                     GCancellable     *cancellable,
                                     GError          **error);
};



//////// Public Functions //////////////////////////////////////////////////////

//////// Properties ////////////////////////////////////////////////////////////

const gchar  *crank_render_step_get_name            (CrankRenderStep *step);

void          crank_render_step_set_name            (CrankRenderStep *step,
                                                     const gchar     *name);

void          crank_render_step_set_name_static     (CrankRenderStep *step,
                                                     const gchar     *name);


GQuark        crank_render_step_get_qname           (CrankRenderStep *step);

void          crank_render_step_set_qname           (CrankRenderStep *step,
                                                     const GQuark     name);



guint         crank_render_step_get_nrequired_items (CrankRenderStep *step);

guint         crank_render_step_get_nrequired_steps (CrankRenderStep *step);



//////// Adding requirements ///////////////////////////////////////////////////

void          crank_render_step_add_required_item   (CrankRenderStep *step,
                                                     const GType      item_type);

void          crank_render_step_add_required_step   (CrankRenderStep *step,
                                                     const gchar     *step_name);

void          crank_render_step_add_required_step_quark (CrankRenderStep *step,
                                                         const GQuark     step_name);


GType         crank_render_step_get_required_item   (CrankRenderStep *step,
                                                     const guint      index);

GQuark        crank_render_step_get_required_step   (CrankRenderStep *step,
                                                     const guint      index);


//////// Rendering operations //////////////////////////////////////////////////

void          crank_render_step_render              (CrankRenderStep   *step,
                                                     GPtrArray        **items,
                                                     CrankRenderLayer **layers,
                                                     CrankTrans3       *position,
                                                     CrankProjection   *projection,
                                                     CrankRenderLayer  *target_layer);

CrankRenderLayer *crank_render_step_create_layer    (CrankRenderStep  *step,
                                                     const guint       width,
                                                     const guint       height,
                                                     GCancellable     *cancellable,
                                                     GError          **error);


G_END_DECLS

#endif /* CRANK_RENDER_STEP_H */
