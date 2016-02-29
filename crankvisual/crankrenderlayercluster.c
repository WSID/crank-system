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

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankprojection.h"
#include "crankvisible.h"

#include "crankrenderlayer.h"
#include "crankrenderlayercluster.h"






//////// List of virtual functions /////////////////////////////////////////////

static void   crank_render_layer_cluster_get_property (GObject    *object,
                                                       guint       prop_id,
                                                       GValue     *value,
                                                       GParamSpec *pspec);

static void   crank_render_layer_cluster_set_property (GObject      *object,
                                                       guint         prop_id,
                                                       const GValue *value,
                                                       GParamSpec   *pspec);

static void   crank_render_layer_cluster_constructed (GObject *object);

static void   crank_render_layer_cluster_finalize    (GObject *object);







//////// Private functions /////////////////////////////////////////////////////

static void   crank_render_layer_cluster_bsweep_plane (CrankPlane3    *planes,
                                                       const guint     nplanes,
                                                       CrankVecFloat3 *pos,
                                                       const gfloat    rad,
                                                       guint          *from,
                                                       guint          *to);









//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_WIDTH,
  PROP_HEIGHT,
  PROP_DEPTH,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};







//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_TYPE (CrankRenderLayerCluster,
               crank_render_layer_cluster,
               CRANK_TYPE_RENDER_LAYER)









//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_layer_cluster_init (CrankRenderLayerCluster *self)
{
  self->cluster = crank_cell_space3_new ();
}

static void
crank_render_layer_cluster_class_init (CrankRenderLayerClusterClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_render_layer_cluster_get_property;
  c_gobject->set_property = crank_render_layer_cluster_set_property;
  c_gobject->constructed = crank_render_layer_cluster_constructed;
  c_gobject->finalize = crank_render_layer_cluster_finalize;

  pspecs[PROP_WIDTH] =
  g_param_spec_uint ("width", "width", "Number of cluster cells from left to right.",
                     0, G_MAXUINT, 32,
                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_HEIGHT] =
  g_param_spec_uint ("height", "height", "Number of cluster cells from bottom to top.",
                     0, G_MAXUINT, 32,
                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_DEPTH] =
  g_param_spec_uint ("depth", "depth", "Number of cluster cells from front to back.",
                     0, G_MAXUINT, 16,
                     G_PARAM_READWRITE | G_PARAM_CONSTRUCT | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}









//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_render_layer_cluster_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec)
{
  CrankRenderLayerCluster *self = (CrankRenderLayerCluster*) object;

  switch (prop_id)
    {
    case PROP_WIDTH:
      g_value_set_uint (value, self->width);
      break;

    case PROP_HEIGHT:
      g_value_set_uint (value, self->height);
      break;

    case PROP_DEPTH:
      g_value_set_uint (value, self->depth);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
crank_render_layer_cluster_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec)
{
  CrankRenderLayerCluster *self = (CrankRenderLayerCluster*) object;

  switch (prop_id)
    {
    case PROP_WIDTH:
      self->width = g_value_get_uint (value);
      break;

    case PROP_HEIGHT:
      self->height = g_value_get_uint (value);
      break;

    case PROP_DEPTH:
      self->depth = g_value_get_uint (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
crank_render_layer_cluster_constructed (GObject *object)
{
  GObjectClass *pc = crank_render_layer_cluster_parent_class;
  CrankRenderLayerCluster *self = (CrankRenderLayerCluster*) object;

  guint i;
  guint j;
  guint k;

  pc->constructed (object);

  self->cluster = crank_cell_space3_new_with_size (self->width,
                                                   self->height,
                                                   self->depth);

  for (i = 0; i < self->width; i++)
    {
      for (j = 0; j < self->height; j++)
        {
          for (k = 0; k < self->depth; k++)
            {
              crank_cell_space3_set_boxed (self->cluster,
                                           i, j, k,
                                           G_TYPE_PTR_ARRAY,
                                           g_ptr_array_new () );
            }
        }
    }

  self->planes_w = g_new (CrankPlane3, self->width);
  self->planes_h = g_new (CrankPlane3, self->height);
  self->planes_d = g_new (CrankPlane3, self->depth);
}


static void
crank_render_layer_cluster_finalize (GObject *object)
{
  GObjectClass *pc = crank_render_layer_cluster_parent_class;
  CrankRenderLayerCluster *self = (CrankRenderLayerCluster*) object;

  crank_cell_space3_unref (self->cluster);

  g_free (self->planes_w);
  g_free (self->planes_h);
  g_free (self->planes_d);

  pc->finalize (object);
}








//////// Private Functions /////////////////////////////////////////////////////

static void
crank_render_layer_cluster_bsweep_plane (CrankPlane3    *planes,
                                         const guint     nplanes,
                                         CrankVecFloat3 *pos,
                                         const gfloat    rad,
                                         guint          *from,
                                         guint          *to)
{
  guint i;
  guint j;

  guint nfrom;
  guint nto;

  i = 0;
  j = nplanes;

  while (i == j)
    {
      guint m = (i + j) / 2;
      gfloat dist = crank_plane3_get_distance (planes + m, pos);

      if (rad < dist)
        i = m;
      else
        j = m;
    }
  nfrom = i;


  i = 0;
  j = nplanes;

  while (i == j)
    {
      guint m = (i + j) / 2;
      gfloat dist = crank_plane3_get_distance (planes + m, pos);

      if (dist < -rad)
        j = m;
      else
        i = m;
    }
  nto = i;

  *from = nfrom;
  *to = nto;
}








//////// Public functions //////////////////////////////////////////////////////

//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_render_layer_cluster_new:
 * @width: Number of cluster in width direction.
 * @height: Number of cluster in height direction.
 * @depth; Number of cluster in depth direction.
 *
 * Constructs a cluster layer.
 *
 * Returns: (transfer full): Newly constructed instance.
 */
CrankRenderLayerCluster*
crank_render_layer_cluster_new (const guint width,
                                const guint height,
                                const guint depth)
{
  return (CrankRenderLayerCluster*)
      g_object_new (CRANK_TYPE_RENDER_LAYER_CLUSTER,
                    "width", width,
                    "height", height,
                    "depth", depth,
                    NULL);
}









//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_render_layer_cluster_get_width:
 * @layer: A Layer.
 *
 * Gets number of cluster in width direction.
 *
 * Returns: Number of cluster in width direction.
 */
guint
crank_render_layer_cluster_get_width (CrankRenderLayerCluster *layer)
{
  return layer->width;
}


/**
 * crank_render_layer_cluster_get_height:
 * @layer: A Layer.
 *
 * Gets number of cluster in height direction.
 *
 * Returns: Number of cluster in height direction.
 */
guint
crank_render_layer_cluster_get_height (CrankRenderLayerCluster *layer)
{
  return layer->height;
}


/**
 * crank_render_layer_cluster_get_depth:
 * @layer: A Layer.
 *
 * Gets number of cluster in dpeth direction.
 *
 * Returns: Number of cluster in depth direction.
 */
guint
crank_render_layer_cluster_get_depth (CrankRenderLayerCluster *layer)
{
  return layer->depth;
}










//////// Prepare ///////////////////////////////////////////////////////////////

void
crank_render_layer_cluster_prepare (CrankRenderLayerCluster *layer,
                                    CrankTrans3             *position,
                                    CrankProjection         *projection)
{
  CrankPlane3 *p_planes_w = g_newa (CrankPlane3, layer->width);
  CrankPlane3 *p_planes_h = g_newa (CrankPlane3, layer->height);
  CrankPlane3 *p_planes_d = g_newa (CrankPlane3, layer->depth);

  CrankVecFloat3  normal;
  guint i;

  if (projection->proj_type == CRANK_PROJECTION_FRUSTUM)
    {
      normal.x = projection->near;
      normal.y = 0;

      for (i = 0; i < layer->width; i++)
        {
          float proportion = ((float)i) / (layer->width);
          normal.x = projection->left  * (1 - proportion) +
                     projection->right * proportion;

          crank_plane3_init (p_planes_w + i,
                             crank_vec_float3_static_zero,
                             &normal);
        }

      normal.z = 0;

      for (i = 0; i < layer->height; i++)
        {
          float proportion = ((float)i) / (layer->height);
          normal.y = projection->bottom * (1 - proportion) +
                     projection->top    * proportion;

          crank_plane3_init (p_planes_h + i,
                             crank_vec_float3_static_zero,
                             &normal);
        }

      // TODO: Add advance formula to get
      for (i = 0; i < layer->depth; i++)
        {
          float proportion = ((float)i) / (layer->depth);
          p_planes_d[i].dist_origin = - ( projection->near * (1 - proportion) +
                                          projection->far * proportion );

          crank_vec_float3_init (& p_planes_d[i].normal, 0, 0, 1);
        }
    }

  else if (projection->proj_type == CRANK_PROJECTION_ORTHO)
    {
      for (i = 0; i < layer->width; i++)
        {
          float proportion = ((float)i) / (layer->width);
          p_planes_w[i].dist_origin = projection->left  * (1 - proportion) +
                                      projection->right * proportion;

          crank_vec_float3_init (& p_planes_w[i].normal, 1, 0, 0);
        }

      for (i = 0; i < layer->height; i++)
        {
          float proportion = ((float)i) / (layer->height);
          p_planes_h[i].dist_origin = projection->bottom * (1 - proportion) +
                                      projection->top    * proportion;

          crank_vec_float3_init (& p_planes_h[i].normal, 0, 1, 0);
        }

      for (i = 0; i < layer->depth; i++)
        {
          float proportion = ((float)i) / (layer->depth);
          p_planes_d[i].dist_origin = - ( projection->near * (1 - proportion) +
                                          projection->far * proportion );

          crank_vec_float3_init (& p_planes_d[i].normal, 0, 0, 1);
        }
    }


  // Transform planes with position.

  for (i = 0; i < layer->width; i++)
    crank_trans3_trans_plane (position, p_planes_w + i, layer->planes_w + i);

  for (i = 0; i < layer->height; i++)
    crank_trans3_trans_plane (position, p_planes_h + i, layer->planes_h + i);

  for (i = 0; i < layer->depth; i++)
    crank_trans3_trans_plane (position, p_planes_d + i, layer->planes_d + i);
}








//////// Operations ////////////////////////////////////////////////////////////

void
crank_render_layer_cluster_add_entity (CrankRenderLayerCluster *layer,
                                       CrankEntity3            *entity,
                                       CrankVisible            *visible)
{
  guint wfrom;
  guint wto;

  guint hfrom;
  guint hto;

  guint dfrom;
  guint dto;

  guint i;
  guint j;
  guint k;

  gfloat vradius = entity->position.mscl * crank_visible_get_visible_radius (visible);

  // For width side.
  crank_render_layer_cluster_bsweep_plane (layer->planes_w,
                                           layer->width,
                                           & entity->position.mtrans,
                                           vradius,
                                           &wfrom,
                                           &wto);

  crank_render_layer_cluster_bsweep_plane (layer->planes_h,
                                           layer->height,
                                           & entity->position.mtrans,
                                           vradius,
                                           &hfrom,
                                           &hto);

  crank_render_layer_cluster_bsweep_plane (layer->planes_d,
                                           layer->depth,
                                           & entity->position.mtrans,
                                           vradius,
                                           &dfrom,
                                           &dto);

  for (i = wfrom; i < wto; i++)
    {
      for (j = hfrom; j < hto; j++)
        {
          for (k = dfrom; k < dto; k++)
            {
              GPtrArray *array = crank_render_layer_cluster_get_array (layer, i, j, k);
              g_ptr_array_add (array, entity);
            }
        }
    }
}


GPtrArray*
crank_render_layer_cluster_get_array (CrankRenderLayerCluster *layer,
                                      const guint              wi,
                                      const guint              hi,
                                      const guint              di)
{
  return crank_cell_space3_get_boxed (layer->cluster, wi, hi, di, NULL);
}

void
crank_render_layer_cluster_clear (CrankRenderLayerCluster *layer)
{
  guint i;
  guint j;
  guint k;

  for (i = 0; i < layer->width; i++)
    {
      for (j = 0; j < layer->height; j++)
        {
          for (k = 0; k < layer->depth; k++)
            {
              GPtrArray *array = crank_render_layer_cluster_get_array (layer, i, j, k);
              g_ptr_array_set_size (array, 0);
            }
        }
    }
}
