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
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankvisible.h"
#include "crankrenderable.h"
#include "cranklightable.h"
#include "crankprojection.h"
#include "crankfilm.h"

#include "crankrenderplacedata.h"
#include "crankrenderprocess.h"
#include "crankcamera.h"

#include "crankrenderlayer.h"
#include "crankrenderlayerarray.h"


//////// Private structures ////////////////////////////////////////////////////

typedef struct _LayerDescriptor
{
  GQuark  name;
  GType   type;
} LayerDescriptor;







//////// List of virtual functions /////////////////////////////////////////////

static void   crank_render_process_get_property (GObject    *object,
                                                 guint       prop_id,
                                                 GValue     *value,
                                                 GParamSpec *pspec);







//////// Private Functions /////////////////////////////////////////////////////

static LayerDescriptor* crank_render_process_get_ld (CrankRenderProcess *process,
                                                     const guint         index);








//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_RESULT_LAYER_INDEX,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};








//////// Type Definitions //////////////////////////////////////////////////////

typedef struct _CrankRenderProcessPrivate
{
  GArray    *layer_descriptors;
}
CrankRenderProcessPrivate;


G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankRenderProcess,
                                     crank_render_process,
                                     G_TYPE_OBJECT)





//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_process_init (CrankRenderProcess *self)
{
  CrankRenderProcessPrivate *priv;
  priv = crank_render_process_get_instance_private (self);

  priv->layer_descriptors = g_array_new (FALSE, FALSE, sizeof (LayerDescriptor));
}

static void
crank_render_process_class_init (CrankRenderProcessClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_render_process_get_property;

  pspecs[PROP_RESULT_LAYER_INDEX] =
  g_param_spec_uint ("result-layer-index", "Result layer index",
                     "Index of resulting layer for presentation.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}







//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_render_process_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  CrankRenderProcess *self = (CrankRenderProcess*) object;

  switch (prop_id)
    {
    case PROP_RESULT_LAYER_INDEX:
      g_value_set_uint (value, crank_render_process_get_result_layer_index (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}








//////// Private Functions /////////////////////////////////////////////////////

static LayerDescriptor*
crank_render_process_get_ld (CrankRenderProcess *process,
                             const guint         index)
{
  CrankRenderProcessPrivate *priv;

  priv = crank_render_process_get_instance_private (process);

  if (priv->layer_descriptors->len <= index)
    {
      g_warning ("crank_render_process_get_ld: Out of bound.\n"
                 "  %u / %u",
                 index, priv->layer_descriptors->len);

      return NULL;
    }

  return & g_array_index (priv->layer_descriptors, LayerDescriptor, index);
}





//////// Public Functions //////////////////////////////////////////////////////

//////// Layer Descriptors /////////////////////////////////////////////////////

/**
 * crank_render_process_get_nlayers:
 * @process: A Process.
 *
 * Gets number of layers that this process uses.
 *
 * Returns: Number of layers.
 */
guint
crank_render_process_get_nlayers (CrankRenderProcess *process)
{
  CrankRenderProcessPrivate *priv;

  priv = crank_render_process_get_instance_private (process);

  return priv->layer_descriptors->len;
}

/**
 * crank_render_process_get_layer_type:
 * @process: A Process.
 * @index: A Index.
 *
 * Gets required layer type.
 *
 * Returns: A Type of layer which is subtype of #CrankRenderLayer.
 */
GType
crank_render_process_get_layer_type (CrankRenderProcess *process,
                                     const guint         index)
{
  LayerDescriptor *ld;

  ld = crank_render_process_get_ld (process, index);

  return (ld != NULL) ? ld->type : G_TYPE_INVALID;
}

/**
 * crank_render_process_get_layer_name:
 * @process: A Process.
 * @index: A Index.
 *
 * Gets required layer's name. This name does not have to match to film's layer
 * name. Actual layer is passed by map of (process layer index: film layer index)
 *
 * Returns: Name of layer in form of GQuark.
 */
GQuark
crank_render_process_get_layer_name (CrankRenderProcess *process,
                                     const guint         index)
{
  LayerDescriptor *ld;

  ld = crank_render_process_get_ld (process, index);

  return (ld != NULL) ? ld->name : 0;
}


/**
 * crank_render_process_insert_layer:
 * @process: A Process.
 * @index: A Index to insert layer requirement..
 * @name: Name of layer requirement.
 * @type: GType of layer requirement.
 *
 * Inserts layer requirement to the process. Then this may use the layer to
 * store intermediate or result data.
 */
void
crank_render_process_insert_layer (CrankRenderProcess *process,
                                   const guint         index,
                                   const GQuark        name,
                                   const GType         type)
{
  CrankRenderProcessPrivate *priv;
  LayerDescriptor ld;

  priv = crank_render_process_get_instance_private (process);

  ld.name = name;
  ld.type = type;

  g_array_insert_val (priv->layer_descriptors, index, ld);
}

/**
 * crank_render_process_append_layer:
 * @process: A Process.
 * @name: Name of layer requirement.
 * @type: GType of layer requirement.
 *
 * Append layer requirement to the process.
 */
void
crank_render_process_append_layer (CrankRenderProcess *process,
                                   const GQuark        name,
                                   const GType         type)
{
  CrankRenderProcessPrivate *priv;
  LayerDescriptor ld;

  priv = crank_render_process_get_instance_private (process);

  ld.name = name;
  ld.type = type;

  g_array_append_val (priv->layer_descriptors, ld);
}

/**
 * crank_render_process_prepend_layer:
 * @process: A Process.
 * @name: Name of layer requirement.
 * @type: GType of layer requirement.
 *
 * Prepend layer requirement to the process.
 */
void
crank_render_process_prepend_layer (CrankRenderProcess *process,
                                    const GQuark        name,
                                    const GType         type)
{
  CrankRenderProcessPrivate *priv;
  LayerDescriptor ld;

  priv = crank_render_process_get_instance_private (process);

  ld.name = name;
  ld.type = type;

  g_array_prepend_val (priv->layer_descriptors, ld);
}

/**
 * crank_render_process_index_of_layer:
 * @procss: A Process.
 * @name: A Name.
 *
 * Gets index of layer by name.
 *
 * Returns: Index of layer, or -1 if not found.
 */
gint
crank_render_process_index_of_layer (CrankRenderProcess *process,
                                     const GQuark        name)
{
  CrankRenderProcessPrivate *priv;
  guint i;

  priv = crank_render_process_get_instance_private (process);

  for (i = 0; i < priv->layer_descriptors->len; i++)
    {
      LayerDescriptor *ld = & g_array_index (priv->layer_descriptors, LayerDescriptor, i);

      if (ld->name == name)
        return i;
    }
  return -1;
}

guint
crank_render_process_get_result_layer_index (CrankRenderProcess *process)
{
  return 7;
}










//////// Rendering Operations //////////////////////////////////////////////////

/**
 * crank_render_process_render_at:
 * @process: A Module.
 * @place: A Place.
 * @position: A Position.
 * @projection: A Projection.
 * @film: A Film.
 * @layer_map: (array) (nullable); Layer mapping.
 *
 * Renders a scene to a film.
 */
void
crank_render_process_render_at (CrankRenderProcess *process,
                                CrankPlace3        *place,
                                CrankTrans3        *position,
                                CrankProjection    *projection,
                                CrankFilm          *film,
                                const gint         *layer_map)
{
  CrankRenderProcessClass *c = CRANK_RENDER_PROCESS_GET_CLASS (process);

  return c->render_at (process, place, position, projection, film, layer_map);
}

/**
 * crank_render_process_render_for:
 * @process: A Process.
 * @camera: A Camera.
 * @film: A Film.
 *
 * Renders the scene on the @film for a @camera.
 *
 * Sometimes, rendering cannot be happened by various reason. In this case, it
 * will return %FALSE.
 *
 * Returns: Whether the rendering was actually happens.
 */
gboolean
crank_render_process_render_for (CrankRenderProcess *process,
                                 CrankCamera        *camera)
{
  CrankRenderProcessClass *c = CRANK_RENDER_PROCESS_GET_CLASS (process);

  return c->render_for (process, camera);
}







//////// Checking //////////////////////////////////////////////////////////////

/**
 * crank_render_process_check_layer:
 * @process: A Process.
 * @index: A index, or negative value to pick by name.
 * @layer: A Rendering layer.
 *
 * Checks whether @layer can be used for @index.
 *
 * Returns: whether @layer can be used for @index.
 */
gboolean
crank_render_process_check_layer (CrankRenderProcess *process,
                                  const gint          index,
                                  CrankRenderLayer   *layer)
{
  LayerDescriptor *ld;
  GType layer_type;
  gint r_index;

  // Get index by layer name, if index is negative.
  if (index < 0)
    {
      GQuark name = crank_render_layer_get_qname (layer);
      r_index = crank_render_process_index_of_layer (process, name);
    }
  else
    {
      r_index = index;
    }

  // Layer checking
  ld = crank_render_process_get_ld (process, r_index);

  // Type check.
  layer_type = G_OBJECT_TYPE (layer);

  if (! g_type_is_a (layer_type, ld->type))
    return FALSE;


  return TRUE;
}


/**
 * crank_render_process_check_film:
 * @process: A Process.
 * @film: A Film.
 * @layer_map: (array) (nullable): Layer mapping, or %NULL to use original index.
 *
 * Checks whether @film can be used for @process.
 *
 * Returns: Whether @film can be used for @process.
 */
gboolean
crank_render_process_check_film (CrankRenderProcess *process,
                                 CrankFilm          *film,
                                 const gint         *layer_map)
{
  guint nlayer;
  guint i;

  nlayer = crank_render_process_get_nlayers (process);

  if (layer_map == NULL)
    {
      for (i = 0; i < nlayer; i++)
        {
          CrankRenderLayer *layer;

          layer = crank_film_get_layer (film, i);
          if (! crank_render_process_check_layer (process, i, layer))
            return FALSE;
        }
    }
  else
    {
      for (i = 0; i < nlayer; i++)
        {
          CrankRenderLayer *layer;

          layer = crank_film_get_layer (film, layer_map[i]);
          if (! crank_render_process_check_layer (process, i, layer))
            return FALSE;
        }
    }
  return TRUE;
}
