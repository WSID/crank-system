#ifndef CRANK_RENDER_STEPSIMPLE_H
#define CRANK_RENDER_STEPSIMPLE_H

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
#include "crankrenderstep.h"


G_BEGIN_DECLS


//////// Type Declaration //////////////////////////////////////////////////////

typedef void (*CrankRenderStepFunc) (CrankRenderStep   *step,
                                     GPtrArray        **items,
                                     CrankRenderLayer **layers,
                                     CrankTrans3       *position,
                                     CrankProjection   *projection,
                                     CrankRenderLayer  *layer,
                                     gpointer           userdata);

typedef CrankRenderLayer *(*CrankRenderStepLayerFunc) (CrankRenderStep  *step,
                                                       const guint       width,
                                                       const guint       height,
                                                       GCancellable     *cancellable,
                                                       GError          **errors,
                                                       gpointer          userdata);


#define CRANK_TYPE_RENDER_STEP_SIMPLE (crank_render_step_simple_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankRenderStepSimple,
                          crank_render_step_simple,
                          CRANK, RENDER_STEP_SIMPLE,
                          CrankRenderStep)

struct _CrankRenderStepSimpleClass
{
  CrankRenderStepClass parent;
};



//////// Public Functions //////////////////////////////////////////////////////

//////// Constructors //////////////////////////////////////////////////////////

CrankRenderStepSimple*        crank_render_step_simple_new (void);


//////// Callbacks /////////////////////////////////////////////////////////////

void    crank_render_step_simple_set_render_func  (CrankRenderStepSimple *step,
                                                   CrankRenderStepFunc    func,
                                                   gpointer               userdata,
                                                   GDestroyNotify         destroy);

void    crank_render_step_simple_set_layer_func   (CrankRenderStepSimple    *step,
                                                   CrankRenderStepLayerFunc  func,
                                                   gpointer                  userdata,
                                                   GDestroyNotify            destroy);


G_END_DECLS

#endif /* CRANK_RENDER_STEP_H */
