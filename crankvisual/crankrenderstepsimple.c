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

/**
 * SECTION: crankrenderstepsimple
 * @title: CrankRenderStepSimple
 * @short_description: Simple Render Step with function callbacks.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * This render step is based on simple callback functions. This step is NOP
 * when no function was specified as callback, so that it can be safetly used.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>

#include "crankshape.h"
#include "crankprojection.h"
#include "crankrenderlayer.h"
#include "crankrenderstep.h"
#include "crankrenderstepsimple.h"


//////// List of virtual functions /////////////////////////////////////////////

static void crank_render_step_simple_dispose (GObject *object);

static void crank_render_step_simple_render (CrankRenderStep   *step,
                                             GPtrArray        **items,
                                             CrankRenderLayer **layers,
                                             CrankTrans3       *position,
                                             CrankProjection   *projection,
                                             CrankRenderLayer  *layer);

static CrankRenderLayer *crank_render_step_simple_create_layer (CrankRenderStep  *step,
                                                                const guint       width,
                                                                const guint       height,
                                                                GCancellable     *cancellable,
                                                                GError          **error);



//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankRenderStepSimplePrivate
{
  CrankRenderStepFunc render_func;
  gpointer            render_userdata;
  GDestroyNotify      render_destroy;

  CrankRenderStepLayerFunc layer_func;
  gpointer                 layer_userdata;
  GDestroyNotify           layer_destroy;
} CrankRenderStepSimplePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CrankRenderStepSimple,
                            crank_render_step_simple,
                            CRANK_TYPE_RENDER_STEP)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_step_simple_init (CrankRenderStepSimple *self)
{
}

static void
crank_render_step_simple_class_init (CrankRenderStepSimpleClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankRenderStepClass *c_renderstep = CRANK_RENDER_STEP_CLASS (c);

  c_gobject->dispose = crank_render_step_simple_dispose;

  c_renderstep->render = crank_render_step_simple_render;
  c_renderstep->create_layer = crank_render_step_simple_create_layer;
}



//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_render_step_simple_dispose (GObject *object)
{
  GObjectClass *pc = crank_render_step_simple_parent_class;
  CrankRenderStepSimple *self = (CrankRenderStepSimple*) object;
  CrankRenderStepSimplePrivate *priv;

  priv = crank_render_step_simple_get_instance_private (self);

  g_clear_pointer (& priv->render_userdata, priv->render_destroy);
  g_clear_pointer (& priv->layer_userdata, priv->layer_destroy);

  pc->dispose (object);
}


//////// CrankRenderStep ///////////////////////////////////////////////////////

static void
crank_render_step_simple_render (CrankRenderStep   *step,
                                 GPtrArray        **items,
                                 CrankRenderLayer **layers,
                                 CrankTrans3       *position,
                                 CrankProjection   *projection,
                                 CrankRenderLayer  *layer)
{
  CrankRenderStepSimple *self = (CrankRenderStepSimple*) step;
  CrankRenderStepSimplePrivate *priv;

  priv = crank_render_step_simple_get_instance_private (self);

  if (priv->render_func != NULL)
    {
      priv->render_func (step,
                         items,
                         layers,
                         position,
                         projection,
                         layer,
                         priv->render_userdata);
    }
}

static CrankRenderLayer*
crank_render_step_simple_create_layer (CrankRenderStep  *step,
                                       const guint       width,
                                       const guint       height,
                                       GCancellable     *cancellable,
                                       GError          **error)
{
  CrankRenderStepSimple *self = (CrankRenderStepSimple*) step;
  CrankRenderStepSimplePrivate *priv;

  priv = crank_render_step_simple_get_instance_private (self);

  if (priv->layer_func != NULL)
    {
      return priv->layer_func (step,
                               width,
                               height,
                               cancellable,
                               error,
                               priv->layer_userdata);
    }
  else
    {
      return NULL;
    }
}




//////// Public Functions //////////////////////////////////////////////////////

//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_render_step_simple_new:
 *
 * Constructs a render step.
 *
 * Returns: (transfer full): Newly constructed render step.
 */
CrankRenderStepSimple*
crank_render_step_simple_new (void)
{
  return (CrankRenderStepSimple*) g_object_new (CRANK_TYPE_RENDER_STEP_SIMPLE, NULL);
}


//////// Callbacks /////////////////////////////////////////////////////////////

/**
 * crank_render_step_simple_set_render_func:
 * @step: A Step.
 * @func: (scope notified): Rendering function.
 * @userdata: (closure func): A userdata for @func.
 * @destroy: (destroy userdata): Destroy function for @userdata.
 *
 * Sets rendering function.
 */
void
crank_render_step_simple_set_render_func  (CrankRenderStepSimple *step,
                                           CrankRenderStepFunc    func,
                                           gpointer               userdata,
                                           GDestroyNotify         destroy)
{
  CrankRenderStepSimplePrivate *priv;

  priv = crank_render_step_simple_get_instance_private (step);

  g_clear_pointer (& priv->render_userdata, priv->render_destroy);
  priv->render_func = func;
  priv->render_userdata = userdata;
  priv->render_destroy = destroy;
}

/**
 * crank_render_step_simple_set_layer_func:
 * @step: A Step.
 * @func: (scope notified): Layer construction function.
 * @userdata: (closure func): A userdata for @func.
 * @destroy: (destroy userdata): Destroy function for @userdata.
 *
 * Sets layer construction function.
 */
void
crank_render_step_simple_set_layer_func   (CrankRenderStepSimple    *step,
                                           CrankRenderStepLayerFunc  func,
                                           gpointer                  userdata,
                                           GDestroyNotify            destroy)
{
  CrankRenderStepSimplePrivate *priv;

  priv = crank_render_step_simple_get_instance_private (step);

  g_clear_pointer (& priv->layer_userdata, priv->layer_destroy);
  priv->layer_func = func;
  priv->layer_userdata = userdata;
  priv->layer_destroy = destroy;
}

