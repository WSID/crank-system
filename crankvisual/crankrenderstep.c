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
#include <gio/gio.h>

#include <cogl/cogl2-experimental.h>

#include "crankshape.h"
#include "crankprojection.h"
#include "crankrenderlayer.h"
#include "crankrenderstep.h"



//////// List of Virtual functions /////////////////////////////////////////////

static void     crank_render_step_get_property (GObject    *object,
                                                guint       prop_id,
                                                GValue     *value,
                                                GParamSpec *psepc);

static void     crank_render_step_set_property (GObject      *object,
                                                guint         prop_id,
                                                const GValue *value,
                                                GParamSpec   *pspec);

static void     crank_render_step_finalize     (GObject *object);



//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_NAME,
  PROP_QNAME,

  PROP_NREQUIRED_ITEMS,
  PROP_NREQUIRED_STEPS,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};



//////// Type Definitions //////////////////////////////////////////////////////

typedef struct _CrankRenderStepPrivate
{
  GQuark    name;

  GArray   *required_items;
  GArray   *required_steps;
} CrankRenderStepPrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankRenderStep,
                                     crank_render_step,
                                     G_TYPE_OBJECT)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_step_init (CrankRenderStep *self)
{
  CrankRenderStepPrivate *priv = crank_render_step_get_instance_private (self);
  priv->required_items = g_array_new (FALSE, FALSE, sizeof (GType));
  priv->required_steps = g_array_new (FALSE, FALSE, sizeof (GQuark));
}

static void
crank_render_step_class_init (CrankRenderStepClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_render_step_get_property;
  c_gobject->set_property = crank_render_step_set_property;
  c_gobject->finalize = crank_render_step_finalize;

  pspecs[PROP_NAME] = g_param_spec_string ("name", "Name", "Name",
                                           "",
                                           G_PARAM_READWRITE |
                                           G_PARAM_STATIC_STRINGS );

  pspecs[PROP_QNAME] = g_param_spec_uint ("qname", "Name as quark", "Name as quark",
                                          0, G_MAXUINT, 0,
                                          G_PARAM_READWRITE |
                                          G_PARAM_STATIC_STRINGS );

  pspecs[PROP_NREQUIRED_ITEMS] = g_param_spec_uint ("nrequired-items",
                                                    "Number of required items",
                                                    "Number of required items",
                                                    0, G_MAXUINT, 0,
                                                    G_PARAM_READABLE |
                                                    G_PARAM_STATIC_STRINGS );

  pspecs[PROP_NREQUIRED_STEPS] = g_param_spec_uint ("nrequired-steps",
                                                    "Number of required steps",
                                                    "Number of required steps",
                                                    0, G_MAXUINT, 0,
                                                    G_PARAM_READABLE |
                                                    G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}



//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_render_step_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  CrankRenderStep *step = (CrankRenderStep*) object;

  switch (prop_id)
    {
    case PROP_NAME:
      g_value_set_string (value, crank_render_step_get_name (step));
      break;

    case PROP_QNAME:
      g_value_set_uint (value, crank_render_step_get_qname (step));
      break;

    case PROP_NREQUIRED_ITEMS:
      g_value_set_uint (value, crank_render_step_get_nrequired_items (step));
      break;

    case PROP_NREQUIRED_STEPS:
      g_value_set_uint (value, crank_render_step_get_nrequired_steps (step));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_render_step_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  CrankRenderStep *step = (CrankRenderStep*) object;

  switch (prop_id)
    {
    case PROP_NAME:
      crank_render_step_set_name (step, g_value_get_string (value));
      break;

    case PROP_QNAME:
      crank_render_step_set_qname (step, g_value_get_uint (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_render_step_finalize (GObject *object)
{
  GObjectClass *pc = crank_render_step_parent_class;
  CrankRenderStep *self = (CrankRenderStep*) object;
  CrankRenderStepPrivate *priv = crank_render_step_get_instance_private (self);

  g_array_unref (priv->required_items);
  g_array_unref (priv->required_items);

  pc->finalize (object);
}


//////// Public Functions //////////////////////////////////////////////////////

//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_render_step_get_name:
 * @step: A Step.
 *
 * Gets name of the step.
 *
 * Returns: (transfer none): A Name of step.
 */
const gchar*
crank_render_step_get_name (CrankRenderStep *step)
{
  GQuark name = G_PRIVATE_FIELD (CrankRenderStep, step,
                                 GQuark, name);

  return g_quark_to_string (name);
}

/**
 * crank_render_step_set_name:
 * @step: A Step.
 * @name: A Name of step.
 *
 * Sets name of the step.
 */
void
crank_render_step_set_name (CrankRenderStep *step,
                            const gchar     *name)
{
  G_PRIVATE_FIELD (CrankRenderStep, step,
                   GQuark,          name) = g_quark_from_string (name);
}

/**
 * crank_render_step_set_name_static:
 * @step: A Step.
 * @name: A Name of step.
 *
 * Sets name of the step. This uses g_quark_from_static_string() so string might
 * avoid duplication into #GQuark string pool.
 */
void
crank_render_step_set_name_static (CrankRenderStep *step,
                                   const gchar     *name)
{
  G_PRIVATE_FIELD (CrankRenderStep, step,
                   GQuark,          name) = g_quark_from_static_string (name);
}


/**
 * crank_render_step_get_qname:
 * @step: A Step.
 *
 * Gets name of the step, as #GQuark.
 *
 * Returns: A Name of step.
 */
GQuark
crank_render_step_get_qname (CrankRenderStep *step)
{
  return G_PRIVATE_FIELD (CrankRenderStep, step,
                          GQuark,          name);
}

/**
 * crank_render_step_set_qname:
 * @step: A Step.
 * @name: A Name of step.
 *
 * Sets name of the step, by #GQuark.
 */
void
crank_render_step_set_qname (CrankRenderStep *step,
                             const GQuark     name)
{
  G_PRIVATE_FIELD (CrankRenderStep, step,
                   GQuark,          name) = name;
}


/**
 * crank_render_step_get_nrequired_items:
 * @step: A Step.
 *
 * Gets number of required item types for this step.
 */
guint
crank_render_step_get_nrequired_items (CrankRenderStep *step)
{
  GArray *array = G_PRIVATE_FIELD (CrankRenderStep, step,
                                   GArray*,         required_items);

  return array->len;
}

/**
 * crank_render_step_get_nrequired_steps:
 * @step: A Step.
 *
 * Gets number of required steps for this step.
 */
guint
crank_render_step_get_nrequired_steps (CrankRenderStep *step)
{
  GArray *array = G_PRIVATE_FIELD (CrankRenderStep, step,
                                   GArray*,         required_steps);

  return array->len;
}




//////// Adding requirements ///////////////////////////////////////////////////

/**
 * crank_render_step_add_required_item:
 * @step: A Step.
 * @item_type: A Item type, that descendant of #CrankVisible.
 *
 * Adds requirement for this step, about item type. Once it is added, the step
 * will be provided #GPtrArray of items with that type.
 */
void
crank_render_step_add_required_item   (CrankRenderStep *step,
                                       const GType      item_type)
{
  GArray *array = G_PRIVATE_FIELD (CrankRenderStep, step,
                                   GArray*,         required_items);

  g_array_append_val (array, item_type);
}

/**
 * crank_render_step_add_required_step:
 * @step: A Step.
 * @step_name: A name of other step.
 *
 * Adds requirement for this step, about other step. Once it is added, the step
 * will be provided #CrankRenderLayer that has been rendered by that step.
 */
void
crank_render_step_add_required_step   (CrankRenderStep *step,
                                       const gchar     *step_name)
{
  GArray *array = G_PRIVATE_FIELD (CrankRenderStep, step,
                                   GArray*,         required_steps);

  GQuark quark = g_quark_from_string (step_name);

  g_array_append_val (array, quark);
}

/**
 * crank_render_step_add_required_step_quark:
 * @step: A Step.
 * @step_name: A name of other step.
 *
 * Same as crank_render_step_add_required_step() but accepts @GQuark.
 */
void
crank_render_step_add_required_step_quark (CrankRenderStep *step,
                                           const GQuark     step_name)
{
  GArray *array = G_PRIVATE_FIELD (CrankRenderStep, step,
                                   GArray*,         required_steps);

  g_array_append_val (array, step_name);
}


/**
 * crank_render_step_get_required_item:
 * @step: A Step.
 * @index: Index of required item type.
 *
 * Gets required item type for this step.
 *
 * Returns: Type of required item type.
 */
GType
crank_render_step_get_required_item (CrankRenderStep *step,
                                     const guint      index)
{
  GArray *array = G_PRIVATE_FIELD (CrankRenderStep, step,
                                   GArray*,         required_items);

  return g_array_index (array, GType, index);
}

/**
 * crank_render_step_get_required_step:
 * @step: A Step.
 * @index: Index of required step.
 *
 * Gets required step for this step.
 *
 * Returns: Name of required step.
 */
GQuark
crank_render_step_get_required_step   (CrankRenderStep *step,
                                       const guint      index)
{
  GArray *array = G_PRIVATE_FIELD (CrankRenderStep, step,
                                   GArray*,         required_steps);

  return g_array_index (array, GQuark, index);
}



//////// Rendering operations //////////////////////////////////////////////////

/**
 * crank_render_step_render:
 * @step: A Step.
 * @items: (array) (nullable) (element-type CrankVisible): Array of List of
 *     required items or %NULL if @step does not require items.
 * @layers: (array) (nullable): Array of layers or %NULL if @step does not
 *     require steps.
 * @position: Position of rendering view.
 * @projection: Projection of rendering view.
 * @target_layer: Layer to render.
 *
 * Renders to a layer.
 */
void
crank_render_step_render (CrankRenderStep   *step,
                          GPtrArray        **items,
                          CrankRenderLayer **layers,
                          CrankTrans3       *position,
                          CrankProjection   *projection,
                          CrankRenderLayer  *target_layer)
{
  CrankRenderStepClass *c = CRANK_RENDER_STEP_GET_CLASS (step);

  if (c->render == NULL)
    g_warning ("%s: Virtual Func not implemented: %s",
               G_STRFUNC, G_OBJECT_TYPE_NAME (step));
  else
    c->render (step, items, layers, position, projection, target_layer);
}


/**
 * crank_render_step_create_layer:
 * @step: A Step.
 * @width: Width of screen.
 * @height: Height of screen.
 * @cancellable: (nullable): A Cancellable.
 * @error: A Error.
 *
 * Creates new layer that @step can render to.
 *
 * Returns: (transfer full) (nullable): Newly created render layer.
 */
CrankRenderLayer*
crank_render_step_create_layer (CrankRenderStep  *step,
                                const guint       width,
                                const guint       height,
                                GCancellable     *cancellable,
                                GError          **error)
{
  CrankRenderStepClass *c = CRANK_RENDER_STEP_GET_CLASS (step);

  if (c->create_layer == NULL)
    {
      g_warning ("%s: Virtual Func not implemented: %s",
                 G_STRFUNC, G_OBJECT_TYPE_NAME (step));
      return NULL;
    }
  else
    {
      return c->create_layer (step, width, height, cancellable, error);
    }
}
