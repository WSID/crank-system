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


#include "crankrenderprocessdeferred.h"

//////// Private structures ////////////////////////////////////////////////////







//////// List of virtual functions /////////////////////////////////////////////

static void
crank_render_process_deferred_render_at (CrankRenderProcess *process,
                                         CrankPlace3        *place,
                                         CrankTrans3        *position,
                                         CrankProjection    *projection,
                                         CrankFilm          *film,
                                         const gint         *layer_map);

static gboolean
crank_render_process_deferred_render_for (CrankRenderProcess *process,
                                          CrankCamera        *camera);





//////// Private Functions /////////////////////////////////////////////////////








//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_RESULT_LAYER_INDEX,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};








//////// Type Definitions //////////////////////////////////////////////////////

struct _CrankRenderProcessDeferred
{
  CrankRenderProcess _parent;
};


G_DEFINE_TYPE (CrankRenderProcessDeferred,
               crank_render_process_deferred,
               CRANK_TYPE_RENDER_PROCESS)





//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_process_deferred_init (CrankRenderProcessDeferred *self)
{
}

static void
crank_render_process_deferred_class_init (CrankRenderProcessDeferredClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankRenderProcessClass *c_process = CRANK_RENDER_PROCESS_CLASS (c);

  c_process->render_at = crank_render_process_deferred_render_at;
  c_process->render_for = crank_render_process_deferred_render_for;
}







//////// GObject ///////////////////////////////////////////////////////////////









//////// CrankRenderProcess ////////////////////////////////////////////////////

static void
crank_render_process_deferred_render_at (CrankRenderProcess *process,
                                         CrankPlace3        *place,
                                         CrankTrans3        *position,
                                         CrankProjection    *projection,
                                         CrankFilm          *film,
                                         const gint         *layer_map)
{
  CrankRenderProcessDeferred *self;
  CrankRenderLayerArray *layer_renderable;
  CrankRenderLayerArray *layer_lightable;

  if (layer_map == NULL)
    {
      gint *layer_map_real = g_alloca (8 * sizeof (gint));
      layer_map_real[0] = 0;
      layer_map_real[1] = 1;
      layer_map_real[2] = 2;
      layer_map_real[3] = 3;
      layer_map_real[4] = 4;
      layer_map_real[5] = 5;
      layer_map_real[6] = 6;
      layer_map_real[7] = 7;

      layer_map = layer_map_real;
    }

  layer_renderable =
      (CrankRenderLayerArray*) crank_film_get_layer (film, layer_map[0]);

  layer_lightable =
      (CrankRenderLayerArray*) crank_film_get_layer (film, layer_map[1]);

  g_ptr_array_set_size (layer_renderable->array, 0);
  crank_render_process_deferred_get_culled_rarray (self, layer_renderable->array, place, position, projection);


  crank_render_process_deferred_render_geom_array (self,
                                         layer_renderable->array,
                                         position,
                                         projection,
                                         crank_film_get_framebuffer (film, layer_map[2]));

  crank_render_process_deferred_render_color_array (self,
                                          layer_renderable->array,
                                          position,
                                          projection,
                                          crank_film_get_framebuffer (film, layer_map[3]));

  g_ptr_array_set_size (layer_lightable->array, 0);
  crank_render_process_deferred_get_culled_larray (self, layer_lightable->array, place, position, projection);


  crank_render_process_deferred_render_light_array (self,
                                          layer_lightable->array,
                                          position,
                                          projection,
                                          crank_film_get_texture (film, layer_map[2]),
                                          crank_film_get_texture (film, layer_map[3]),
                                          crank_film_get_texture (film, layer_map[4]),
                                          crank_film_get_framebuffer (film, layer_map[7]));


  // XXX: For now, rendering a color buffer on result buffer.

  // TODO: Render to other buffers.
  //
  //
}

static gboolean
crank_render_process_deferred_render_for (CrankRenderProcess *process,
                                          CrankCamera        *camera)
{
  CrankEntity3    *entity;
  CrankPlace3     *place;
  CrankTrans3      position;
  CrankProjection *projection;
  CrankFilm       *film;

  film = crank_camera_get_film (camera);
  if (film == NULL)
    return FALSE;

  entity = crank_camera_get_entity (camera);
  if (entity == NULL)
    return FALSE;

  place = (CrankPlace3*)crank_entity_get_primary_place ((CrankEntity*)entity);
  if (place == NULL)
    return FALSE;

  projection = crank_camera_get_projection (camera);

  crank_render_process_deferred_render_at (process,
                                  place,
                                  & entity->position,
                                  projection,
                                  film,
                                  crank_camera_get_layer_map (camera, NULL));

  return TRUE;
}









//////// Private Functions /////////////////////////////////////////////////////







//////// Public Functions //////////////////////////////////////////////////////

//////// Constructors //////////////////////////////////////////////////////////

CrankRenderProcessDeferred*
crank_render_process_deferred_new (void)
{
  return (CrankRenderProcessDeferred*) g_object_new (CRANK_TYPE_RENDER_PROCESS_DEFERRED, NULL);
}








//////// Rendering Operations //////////////////////////////////////////////////

/**
 * crank_render_process_deferred_get_culled_array:
 * @process: A Module.
 * @entities: (transfer none) (element-type CrankEntity3): Entitiy array.
 * @place: A Place.
 * @position: A Position.
 * @projection: A Projection.
 * @tindex: A Type index.
 *
 * Gets culled list of entities.
 *
 * Returns: (transfer none) (element-type CrankEntity3): @entities.
 */
GPtrArray*
crank_render_process_deferred_get_culled_array (CrankRenderProcessDeferred *process,
                                                GPtrArray                  *entities,
                                                CrankPlace3                *place,
                                                CrankTrans3                *position,
                                                CrankProjection            *projection,
                                                const guint                 tindex)
{
  CrankRenderPlaceData *pdata;
  CrankPlane3 cullplane_t[6];

  crank_projection_get_cull_plane_transformed (projection, position, cullplane_t);

  pdata = (CrankRenderPlaceData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PLACE_DATA);

  return crank_render_place_data_get_culled_array (pdata, entities, cullplane_t, 6, tindex);
}

/**
 * crank_render_process_deferred_get_culled_rarray:
 * @process: A Module.
 * @entities: (transfer none) (element-type CrankEntity3): Entitiy array.
 * @place: A Place.
 * @position: A Position.
 * @projection: A Projection.
 *
 * Gets culled list of entities.
 *
 * Returns: (transfer none) (element-type CrankEntity3): @entities.
 */
GPtrArray*
crank_render_process_deferred_get_culled_rarray (CrankRenderProcessDeferred *process,
                                                 GPtrArray                  *entities,
                                                 CrankPlace3                *place,
                                                 CrankTrans3                *position,
                                                 CrankProjection            *projection)
{
  return crank_render_process_deferred_get_culled_array (process, entities, place, position, projection, 0);
}

/**
 * crank_render_process_deferred_get_culled_larray:
 * @process: A Module.
 * @entities: (transfer none) (element-type CrankEntity3): Entity array.
 * @place: A Place.
 * @position: A Position.
 * @projection: A Projection.
 *
 * Gets culled list of entities.
 *
 * Returns: (transfer none) (element-type CrankEntity3): @entities.
 */
GPtrArray*
crank_render_process_deferred_get_culled_larray (CrankRenderProcessDeferred *process,
                                                 GPtrArray                  *entities,
                                                 CrankPlace3                *place,
                                                 CrankTrans3                *position,
                                                 CrankProjection            *projection)
{
  return crank_render_process_deferred_get_culled_array (process, entities, place, position, projection, 1);
}







/**
 * crank_render_process_deferred_render_geom_array:
 * @process: A Module.
 * @entities: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_process_deferred_render_geom_array(CrankRenderProcessDeferred *process,
                                                GPtrArray                  *entities,
                                                CrankTrans3                *position,
                                                CrankProjection            *projection,
                                                CoglFramebuffer            *framebuffer)
{
  CrankTrans3 ipos;
  guint i;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 1, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  crank_trans3_inverse (position, &ipos);

  for (i = 0; i < entities->len; i++)
    {
      CrankEntity3 *entity = (CrankEntity3*) entities->pdata[i];
      crank_render_process_deferred_render_geom_entity (process, entity, &ipos, projection, framebuffer);
    }
}

/**
 * crank_render_process_deferred_render_color_array:
 * @process: A Module.
 * @entities: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_process_deferred_render_color_array(CrankRenderProcessDeferred *process,
                                                 GPtrArray                  *entities,
                                                 CrankTrans3                *position,
                                                 CrankProjection            *projection,
                                                 CoglFramebuffer            *framebuffer)
{
  CrankTrans3 ipos;
  guint i;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  crank_trans3_inverse (position, &ipos);

  for (i = 0; i < entities->len; i++)
    {
      CrankEntity3 *entity = (CrankEntity3*) entities->pdata[i];
      crank_render_process_deferred_render_color_entity (process, entity, &ipos, projection, framebuffer);
    }
}

/**
 * crank_render_process_deferred_render_light_array:
 * @process: A Module.
 * @entities: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @tex_geom: Texture that holds geometry info.
 * @tex_color: Texture that holds color info.
 * @tex_mater: Texture that holds material info.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_process_deferred_render_light_array (CrankRenderProcessDeferred *process,
                                                  GPtrArray                  *entities,
                                                  CrankTrans3                *position,
                                                  CrankProjection            *projection,
                                                  CoglTexture                *tex_geom,
                                                  CoglTexture                *tex_color,
                                                  CoglTexture                *tex_mater,
                                                  CoglFramebuffer            *framebuffer)
{
  CrankTrans3 ipos;
  guint i;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  crank_trans3_inverse (position, &ipos);

  for (i = 0; i < entities->len; i++)
    {
      CrankEntity3 *entity = (CrankEntity3*) entities->pdata[i];
      crank_render_process_deferred_render_light_entity (process, entity, &ipos, projection, tex_geom, tex_color, tex_mater, framebuffer);
    }
}


/**
 * crank_render_process_deferred_render_geom_entity:
 * @process: A Module.
 * @entity: A Entity.
 * @ipos: Inverse of position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_process_deferred_render_geom_entity(CrankRenderProcessDeferred *process,
                                                 CrankEntity3               *entity,
                                                 CrankTrans3                *ipos,
                                                 CrankProjection            *projection,
                                                 CoglFramebuffer            *framebuffer)
{
  guint i;
  guint n;
  CrankTrans3 rpos;
  crank_trans3_compose (ipos, & entity->position, &rpos);

  n = crank_composite_get_ncompositables ((CrankComposite*)entity);
  for (i = 0; i < n; i++)
    {
      CrankCompositable *compositable =
          crank_composite_get_compositable ((CrankComposite*)entity, i);

      if (CRANK_IS_RENDERABLE (compositable))
        crank_renderable_render_geom ((CrankRenderable*)compositable,
                                      &rpos, projection, framebuffer);
    }
}

/**
 * crank_render_process_deferred_render_color_entity:
 * @process: A Module.
 * @entity: A Entity.
 * @ipos: Inverse of position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_process_deferred_render_color_entity(CrankRenderProcessDeferred *process,
                                                  CrankEntity3               *entity,
                                                  CrankTrans3                *ipos,
                                                  CrankProjection            *projection,
                                                  CoglFramebuffer            *framebuffer)
{
  guint i;
  guint n;
  CrankTrans3 rpos;
  crank_trans3_compose (ipos, & entity->position, &rpos);

  n = crank_composite_get_ncompositables ((CrankComposite*)entity);
  for (i = 0; i < n; i++)
    {
      CrankCompositable *compositable =
          crank_composite_get_compositable ((CrankComposite*)entity, i);

      if (CRANK_IS_RENDERABLE (compositable))
        crank_renderable_render_color ((CrankRenderable*)compositable,
                                      &rpos, projection, framebuffer);
    }
}

/**
 * crank_render_process_deferred_render_light_entity:
 * @process: A Module.
 * @entity: A Entity.
 * @ipos: Inverse of position
 * @projection: A Projection.
 * @tex_geom: Texture that holds geometry info.
 * @tex_color: Texture that holds color info.
 * @tex_mater: Texture that holds material info.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_process_deferred_render_light_entity(CrankRenderProcessDeferred *process,
                                                  CrankEntity3               *entity,
                                                  CrankTrans3                *ipos,
                                                  CrankProjection            *projection,
                                                  CoglTexture                *tex_geom,
                                                  CoglTexture                *tex_color,
                                                  CoglTexture                *tex_mater,
                                                  CoglFramebuffer            *framebuffer)
{
  guint i;
  guint n;
  CrankTrans3 rpos;
  crank_trans3_compose (ipos, & entity->position, &rpos);

  n = crank_composite_get_ncompositables ((CrankComposite*)entity);
  for (i = 0; i < n; i++)
    {
      CrankCompositable *compositable =
          crank_composite_get_compositable ((CrankComposite*)entity, i);

      if (CRANK_IS_LIGHTABLE (compositable))
        crank_lightable_render ((CrankLightable*) compositable,
                                &rpos, projection, tex_geom, tex_color, tex_mater, 1, framebuffer);
    }
}
