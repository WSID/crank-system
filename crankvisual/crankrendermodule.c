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
 * SECTION: crankrendermodule
 * @title: CrankRenderModule
 * @short_description: Rendering Module.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * Represents Rendering function.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankrenderable.h"
#include "crankfilm.h"
#include "crankcamera.h"

#include "crankrenderpdata.h"
#include "crankrendermodule.h"




//////// List of virtual functions /////////////////////////////////////////////

static void       crank_render_module_get_property (GObject    *object,
                                                    guint       prop_id,
                                                    GValue     *value,
                                                    GParamSpec *pspec);

static void       crank_render_module_set_property (GObject      *object,
                                                    guint         prop_id,
                                                    const GValue *value,
                                                    GParamSpec   *pspec);

static void       crank_render_module_session_init (CrankSessionModule  *module,
                                                    CrankSession        *session,
                                                    GError             **error);


//////// Functions for other modules ///////////////////////////////////////////

static void       crank_render_module_tick (CrankSessionModuleTick *module,
                                            gpointer                user_data);

static void       crank_render_module_place_created (CrankSessionModulePlaced *pmodule,
                                                     CrankPlaceBase           *place,
                                                     gpointer                  user_data);

static void       crank_render_module_entity_added (CrankSessionModulePlaced *pmodule,
                                                    CrankPlaceBase           *place,
                                                    CrankEntityBase          *entity,
                                                    gpointer                  userdata);

static void       crank_render_module_entity_removed (CrankSessionModulePlaced *pmodule,
                                                      CrankPlaceBase           *place,
                                                      CrankEntityBase          *entity,
                                                      gpointer                  userdata);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_COGL_CONTEXT,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankRenderModule
{
  CrankSessionModule  _parent;

  CoglContext *cogl_context;

  goffset     offset_pdata;
  goffset     offset_renderable;
  goffset     offset_lightable;

  GPtrArray   *cameras;

  GPtrArray   *render_entities;
};

G_DEFINE_TYPE (CrankRenderModule,
               crank_render_module,
               CRANK_TYPE_SESSION_MODULE)



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_module_init (CrankRenderModule *module)
{
  module->cameras = g_ptr_array_new_with_free_func (g_object_unref);
  module->render_entities = g_ptr_array_new ();
}



static void
crank_render_module_class_init (CrankRenderModuleClass *c)
{
  GObjectClass *c_gobject;
  CrankSessionModuleClass *c_sessionmodule;

  c_gobject = G_OBJECT_CLASS (c);
  c_gobject->get_property = crank_render_module_get_property;
  c_gobject->set_property = crank_render_module_set_property;

  pspecs[PROP_COGL_CONTEXT] = g_param_spec_pointer ("cogl-context", "CoglContext",
                                                    "CoglContext to initialize with.",
                                                    G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                                                    G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_sessionmodule = CRANK_SESSION_MODULE_CLASS (c);
  c_sessionmodule->session_init = crank_render_module_session_init;
}





//////// GObject ///////////////////////////////////////////////////////////////


static void
crank_render_module_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspecs)
{
  CrankRenderModule *module = (CrankRenderModule*) object;

  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
      g_value_set_pointer (value, module->cogl_context);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspecs);
    }
}



static void
crank_render_module_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspecs)
{
  CrankRenderModule *module = (CrankRenderModule*) object;

  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
      module->cogl_context = g_value_get_pointer (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspecs);
    }
}


//////// CrankSessionModule ////////////////////////////////////////////////////

static void
crank_render_module_session_init (CrankSessionModule  *module,
                                  CrankSession        *session,
                                  GError             **error)
{
  CrankRenderModule *rmodule = (CrankRenderModule*)module;
  CrankSessionModulePlaced *pmodule;
  CrankSessionModuleTick *tmodule;
  // Placed Module

  pmodule = CRANK_SESSION_MODULE_PLACED (crank_session_get_module_by_gtype (session,
                                               CRANK_TYPE_SESSION_MODULE_PLACED));

  if (pmodule == NULL)
    g_error ("CrankRenderModule: requires CrankSessionModulePlaced.");

  crank_session_module_placed_attach_place_alloc_object (pmodule,
                                                         & rmodule->offset_pdata);

  crank_session_module_placed_attach_entity_alloc_object (pmodule,
                                                          & rmodule->offset_renderable);

  crank_session_module_placed_attach_entity_alloc_object (pmodule,
                                                          & rmodule->offset_lightable);

  g_signal_connect (pmodule, "place-created",
                    (GCallback)crank_render_module_place_created, rmodule);

  g_signal_connect (pmodule, "entity-added",
                    (GCallback)crank_render_module_entity_added, rmodule);

  g_signal_connect (pmodule, "entity-removed",
                    (GCallback)crank_render_module_entity_removed, rmodule);


  // Tick Module
  tmodule = CRANK_SESSION_MODULE_TICK (crank_session_get_module_by_gtype (session, CRANK_TYPE_SESSION_MODULE_TICK));

  if (tmodule == NULL)
    return;

  g_signal_connect (tmodule, "tick", (GCallback)crank_render_module_tick, rmodule);
}


//////// Callback functions for other modules //////////////////////////////////

static void
crank_render_module_tick (CrankSessionModuleTick *tmodule,
                          gpointer                user_data)
{
  CrankRenderModule *rmodule = (CrankRenderModule*) user_data;

  guint i;

  for (i = 0; i < rmodule->cameras->len; i++)
    {
      CrankCamera *camera;
      CrankFilm *film;
      CrankEntity3 *entity;
      CrankPlace3 *place;

      camera = rmodule->cameras->pdata[i];

      film = crank_camera_get_film (camera);
      if (film == NULL)
        continue;

      entity = crank_camera_get_entity (camera);
      if (entity == NULL)
        continue;

      place = (CrankPlace3*)crank_entity_base_get_place ((CrankEntityBase*)entity);
      if (place == NULL)
        continue;

      CrankTrans3 position;
      CrankProjection *projection;

      projection = crank_camera_get_projection (camera);

      crank_render_module_render_at (rmodule,
                                     place,
                                     & entity->position,
                                     projection,
                                     film);

      crank_camera_rendered (camera);
    }
}

static void
crank_render_module_place_created (CrankSessionModulePlaced *pmodule,
                                   CrankPlaceBase           *place,
                                   gpointer                  userdata)
{
  CrankRenderModule *module  = (CrankRenderModule*) userdata;

  G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata) =
      g_object_new (CRANK_TYPE_RENDER_PDATA,
                    "place", place,
                    "renderable-offset", module->offset_renderable,
                    "lightable-offset", module->offset_lightable,
                    NULL);
}


static void
crank_render_module_entity_added (CrankSessionModulePlaced *pmodule,
                                  CrankPlaceBase           *place,
                                  CrankEntityBase          *entity,
                                  gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;

  CrankRenderPData *pdata;
  CrankRenderable *renderable;
  CrankLightable *lightable;

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

  renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
  lightable = G_STRUCT_MEMBER (CrankLightable*, entity, module->offset_lightable);

  if (renderable != NULL)
    crank_render_pdata_add_rentity (pdata, entity);

  if (lightable != NULL)
    crank_render_pdata_add_lentity (pdata, entity);


}


static void
crank_render_module_entity_removed (CrankSessionModulePlaced *pmodule,
                                    CrankPlaceBase           *place,
                                    CrankEntityBase          *entity,
                                    gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;

  CrankRenderPData *pdata;
  CrankRenderable *renderable;
  CrankLightable *lightable;

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

  renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
  lightable = G_STRUCT_MEMBER (CrankLightable*, entity, module->offset_lightable);

  if (renderable != NULL)
    crank_render_pdata_remove_rentity (pdata, entity);

  if (lightable != NULL)
    crank_render_pdata_remove_lentity (pdata, entity);
}







//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_render_module_new:
 * @cogl_context: A Cogl Context.
 *
 * Constructs a rendering module.
 *
 * Returns: (transfer full): Newly constructed module.
 */
CrankRenderModule*
crank_render_module_new (CoglContext *cogl_context)
{
  return (CrankRenderModule*) g_object_new (CRANK_TYPE_RENDER_MODULE,
                                            "cogl-context", cogl_context,
                                            NULL);
}

//////// Entities and places functions /////////////////////////////////////////

/**
 * crank_render_module_set_renderable:
 * @module: A Module.
 * @entity: A Entity.
 * @renderable: (nullable): A Renderable.
 *
 * Sets a renderable for the entity. The renderable may be %NULL, for non-visible
 * entity. (For example, camera hook, spawn point, etc...)
 */
void
crank_render_module_set_renderable (CrankRenderModule *module,
                                    CrankEntityBase   *entity,
                                    CrankRenderable   *renderable)
{
  CrankPlaceBase *place;
  CrankRenderPData *pdata;
  CrankRenderable **renderable_ptr;
  CrankRenderable *renderable_prev;

  renderable_ptr = G_STRUCT_MEMBER_P (entity, module->offset_renderable);
  renderable_prev = *renderable_ptr;

  if (! g_set_object (renderable_ptr, renderable))
    return;


  place = crank_entity_base_get_place (entity);

  if (place != NULL)
    {
      pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

      if (renderable_prev == NULL)
          crank_render_pdata_add_rentity (pdata, entity);

      else if (renderable == NULL)
        crank_render_pdata_remove_rentity (pdata, entity);
    }
}


/**
 * crank_render_module_get_renderable:
 * @module: A Module.
 * @entity: A Entity.
 *
 * Gets a renderable from entity. Non-visible entities does not have renderable.
 *
 * Returns: (transfer none) (nullable): Renderable, or %NULL if it does not have.
 */
CrankRenderable*
crank_render_module_get_renderable (CrankRenderModule *module,
                                    CrankEntityBase   *entity)
{
  return G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
}

/**
 * crank_render_module_set_lightable:
 * @module: A Module.
 * @entity: A Entity.
 * @lightable: (nullable): A Lightable.
 *
 * Sets a lightable for the entity. The lightable may be %NULL, for non-lighting
 * entities like chairs, doors,..
 */
void
crank_render_module_set_lightable (CrankRenderModule *module,
                                   CrankEntityBase   *entity,
                                   CrankLightable    *lightable)
{
  CrankPlaceBase *place;
  CrankRenderPData *pdata;
  CrankLightable **lightable_ptr;
  CrankLightable *lightable_prev;

  lightable_ptr = G_STRUCT_MEMBER_P (entity, module->offset_lightable);
  lightable_prev = *lightable_ptr;

  if (! g_set_object (lightable_ptr, lightable))
    return;


  place = crank_entity_base_get_place (entity);

  if (place != NULL)
    {
      pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

      if (lightable_prev == NULL)
          crank_render_pdata_add_lentity (pdata, entity);

      else if (lightable == NULL)
        crank_render_pdata_remove_lentity (pdata, entity);
    }
}


/**
 * crank_render_module_get_lightable:
 * @module: A Module.
 * @entity: A Entity.
 *
 * Gets a lightable from entity.
 *
 * Returns: (transfer none) (nullable): Lightable, or %NULL if it does not have.
 */
CrankLightable*
crank_render_module_get_lightable (CrankRenderModule *module,
                                   CrankEntityBase   *entity)
{
  return G_STRUCT_MEMBER (CrankLightable*, entity, module->offset_lightable);
}


//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_render_module_get_culled_rlist:
 * @module: A Module.
 * @place: A Place.
 * @position: A Position.
 * @projection: A Projection.
 *
 * Gets culled list of entities.
 *
 * Returns: (transfer container) (element-type CrankEntity3): Entities.
 */
GList*
crank_render_module_get_culled_rlist (CrankRenderModule *module,
                                      CrankPlace3       *place,
                                      CrankTrans3       *position,
                                      CrankProjection   *projection)
{
  CrankRenderPData *pdata;
  CrankPlane3 cullplane_t[6];

  guint i;

  for (i = 0; i < 6; i++)
    crank_trans3_trans_plane (position, projection->cull_plane + i, cullplane_t + i);

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);
  return crank_octree_set_get_culled_list (pdata->rentities, cullplane_t, 6);
}

/**
 * crank_render_module_get_culled_llist:
 * @module: A Module.
 * @place: A Place.
 * @position: A Position.
 * @projection: A Projection.
 *
 * Gets culled list of entities.
 *
 * Returns: (transfer container) (element-type CrankEntity3): Entities.
 */
GList*
crank_render_module_get_culled_llist (CrankRenderModule *module,
                                      CrankPlace3       *place,
                                      CrankTrans3       *position,
                                      CrankProjection   *projection)
{
  CrankRenderPData *pdata;
  CrankPlane3 cullplane_t[6];

  guint i;

  for (i = 0; i < 6; i++)
    crank_trans3_trans_plane (position, projection->cull_plane + i, cullplane_t + i);

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);
  return crank_octree_set_get_culled_list (pdata->lentities, cullplane_t, 6);
}



/**
 * crank_render_module_get_culled_rarray:
 * @module: A Module.
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
crank_render_module_get_culled_rarray (CrankRenderModule *module,
                                       GPtrArray         *entities,
                                       CrankPlace3       *place,
                                       CrankTrans3       *position,
                                       CrankProjection   *projection)
{
  CrankRenderPData *pdata;
  CrankPlane3 cullplane_t[6];

  guint i;

  for (i = 0; i < 6; i++)
    crank_trans3_trans_plane (position, projection->cull_plane + i, cullplane_t + i);

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);
  return crank_octree_set_add_culled_array (pdata->rentities, entities, cullplane_t, 6);
}

/**
 * crank_render_module_get_culled_larray:
 * @module: A Module.
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
crank_render_module_get_culled_larray (CrankRenderModule *module,
                                       GPtrArray         *entities,
                                       CrankPlace3       *place,
                                       CrankTrans3       *position,
                                       CrankProjection   *projection)
{
  CrankRenderPData *pdata;
  CrankPlane3 cullplane_t[6];

  guint i;

  for (i = 0; i < 6; i++)
    crank_trans3_trans_plane (position, projection->cull_plane + i, cullplane_t + i);

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);
  return crank_octree_set_add_culled_array (pdata->lentities, entities, cullplane_t, 6);
}





/**
 * crank_render_module_render_geom_at:
 * @module: A Module.
 * @place: A Place.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders @place which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_geom_at (CrankRenderModule *module,
                                    CrankPlace3       *place,
                                    CrankTrans3       *position,
                                    CrankProjection   *projection,
                                    CoglFramebuffer   *framebuffer)
{
  GList *list = crank_render_module_get_culled_rlist (module, place, position, projection);

  crank_render_module_render_geom_list (module, list, position, projection, framebuffer);

  g_list_free (list);
}

/**
 * crank_render_module_render_color_at:
 * @module: A Module.
 * @place: A Place.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders @place which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_color_at (CrankRenderModule *module,
                                     CrankPlace3       *place,
                                     CrankTrans3       *position,
                                     CrankProjection   *projection,
                                     CoglFramebuffer   *framebuffer)
{
  GList *list = crank_render_module_get_culled_rlist (module, place, position, projection);

  crank_render_module_render_color_list (module, list, position, projection, framebuffer);

  g_list_free (list);
}


/**
 * crank_render_module_render_light_at:
 * @module: A Module.
 * @place: A Place.
 * @position: Position of view.
 * @projection: Projection of view.
 * @tex_geom: Texture that holds geometry info.
 * @tex_color: Texture that holds color info.
 * @tex_mater: Texture that holds material info.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders light info ont @framebuffer.
 */
void
crank_render_module_render_light_at (CrankRenderModule *module,
                                     CrankPlace3       *place,
                                     CrankTrans3       *position,
                                     CrankProjection   *projection,
                                     CoglTexture       *tex_geom,
                                     CoglTexture       *tex_color,
                                     CoglTexture       *tex_mater,
                                     CoglFramebuffer   *framebuffer)
{
  GList *list = crank_render_module_get_culled_llist (module, place, position, projection);

  crank_render_module_render_light_list (module, list, position, projection, tex_geom, tex_color, tex_mater, framebuffer);

  g_list_free (list);
}

/**
 * crank_render_module_render_geom_list:
 * @module: A Module.
 * @entities: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_geom_list (CrankRenderModule *module,
                                      GList             *entities,
                                      CrankTrans3       *position,
                                      CrankProjection   *projection,
                                      CoglFramebuffer   *framebuffer)
{
  CrankTrans3 ipos;
  guint i;

  GList *iter;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 1, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  crank_trans3_inverse (position, &ipos);

  for (iter = entities; iter != NULL; iter = iter->next)
    {
      CrankEntity3 *entity = (CrankEntity3*) iter->data;
      CrankRenderable *renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
      CrankTrans3 rpos;

      crank_trans3_compose (&ipos, & entity->position, &rpos);

      crank_renderable_render_geom (renderable, &rpos, projection, framebuffer);
    }
}

/**
 * crank_render_module_render_color_list:
 * @module: A Module.
 * @entities: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_color_list (CrankRenderModule *module,
                                       GList             *entities,
                                       CrankTrans3       *position,
                                       CrankProjection   *projection,
                                       CoglFramebuffer   *framebuffer)
{
  CrankTrans3 ipos;
  guint i;

  GList *iter;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  crank_trans3_inverse (position, &ipos);

  for (iter = entities; iter != NULL; iter = iter->next)
    {
      CrankEntity3 *entity = (CrankEntity3*) iter->data;
      CrankRenderable *renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
      CrankTrans3 rpos;

      crank_trans3_compose (&ipos, & entity->position, &rpos);

      crank_renderable_render_color (renderable, &rpos, projection, framebuffer);
    }
}

/**
 * crank_render_module_render_light_list:
 * @module: A Module.
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
crank_render_module_render_light_list (CrankRenderModule *module,
                                       GList             *entities,
                                       CrankTrans3       *position,
                                       CrankProjection   *projection,
                                       CoglTexture       *tex_geom,
                                       CoglTexture       *tex_color,
                                       CoglTexture       *tex_mater,
                                       CoglFramebuffer   *framebuffer)
{
  CrankTrans3 ipos;
  guint i;

  GList *iter;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  crank_trans3_inverse (position, &ipos);

  for (iter = entities; iter != NULL; iter = iter->next)
    {
      CrankEntity3 *entity = (CrankEntity3*) iter->data;
      CrankLightable *lightable = G_STRUCT_MEMBER (CrankLightable*, entity, module->offset_lightable);
      CrankTrans3 rpos;

      crank_trans3_compose (&ipos, & entity->position, &rpos);

      crank_lightable_render (lightable, &rpos, projection, tex_geom, tex_color, tex_mater, 1, framebuffer);
    }
}


/**
 * crank_render_module_render_geom_array:
 * @module: A Module.
 * @entities: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_geom_array(CrankRenderModule *module,
                                      GPtrArray         *entities,
                                      CrankTrans3       *position,
                                      CrankProjection   *projection,
                                      CoglFramebuffer   *framebuffer)
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
      CrankRenderable *renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
      CrankTrans3 rpos;

      crank_trans3_compose (&ipos, & entity->position, &rpos);

      crank_renderable_render_geom (renderable, &rpos, projection, framebuffer);
    }
}

/**
 * crank_render_module_render_color_array:
 * @module: A Module.
 * @entities: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_color_array(CrankRenderModule *module,
                                       GPtrArray         *entities,
                                       CrankTrans3       *position,
                                       CrankProjection   *projection,
                                       CoglFramebuffer   *framebuffer)
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
      CrankRenderable *renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
      CrankTrans3 rpos;

      crank_trans3_compose (&ipos, & entity->position, &rpos);

      crank_renderable_render_color (renderable, &rpos, projection, framebuffer);
    }
}

/**
 * crank_render_module_render_light_array:
 * @module: A Module.
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
crank_render_module_render_light_array (CrankRenderModule *module,
                                       GPtrArray          *entities,
                                       CrankTrans3       *position,
                                       CrankProjection   *projection,
                                       CoglTexture       *tex_geom,
                                       CoglTexture       *tex_color,
                                       CoglTexture       *tex_mater,
                                       CoglFramebuffer   *framebuffer)
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
      CrankLightable *lightable = G_STRUCT_MEMBER (CrankLightable*, entity, module->offset_lightable);
      CrankTrans3 rpos;

      crank_trans3_compose (&ipos, & entity->position, &rpos);

      crank_lightable_render (lightable, &rpos, projection, tex_geom, tex_color, tex_mater, 1, framebuffer);
    }
}

/**
 * crank_render_module_render_at:
 * @module: A Module.
 * @place: A Place.
 * @position: A Position.
 * @projection: A Projection.
 * @film: A Film.
 *
 * Renders a scene to a film.
 */
void
crank_render_module_render_at (CrankRenderModule *module,
                               CrankPlace3       *place,
                               CrankTrans3       *position,
                               CrankProjection   *projection,
                               CrankFilm         *film)
{
  g_ptr_array_set_size (module->render_entities, 0);
  crank_render_module_get_culled_rarray (module, module->render_entities, place, position, projection);


  crank_render_module_render_geom_array (module,
                                         module->render_entities,
                                         position,
                                         projection,
                                         crank_film_get_framebuffer (film, 0));

  crank_render_module_render_color_array (module,
                                          module->render_entities,
                                          position,
                                          projection,
                                          crank_film_get_framebuffer (film, 1));

  g_ptr_array_set_size (module->render_entities, 0);
  crank_render_module_get_culled_larray (module, module->render_entities, place, position, projection);


  crank_render_module_render_light_array (module,
                                          module->render_entities,
                                          position,
                                          projection,
                                          crank_film_get_texture (film, 0),
                                          crank_film_get_texture (film, 1),
                                          crank_film_get_texture (film, 2),
                                          crank_film_get_framebuffer (film, 5));

  /*
  crank_render_module_render_pos (module,
                                  crank_film_get_texture (film, 0),
                                  projection,
                                  crank_film_get_framebuffer (film, 5));
 * */
  // XXX: For now, rendering a color buffer on result buffer.

  // TODO: Render to other buffers.
  //
  //
}

/**
 * crank_render_module_add_camera:
 * @module: A Module.
 * @camera: A Camera.
 *
 * Adds @camera to this module.
 */
void
crank_render_module_add_camera (CrankRenderModule *module,
                                CrankCamera       *camera)
{
  g_ptr_array_add (module->cameras, g_object_ref (camera));
}

/**
 * crank_render_module_remove_camera:
 * @module: A Module.
 * @camera: A Camera.
 *
 * Removes a @camera from this module.
 */
void
crank_render_module_remove_camera (CrankRenderModule *module,
                                   CrankCamera       *camera)
{
  g_ptr_array_remove (module->cameras, camera);
}


/**
 * crank_render_module_get_n_camera:
 * @module: A Module.
 *
 * Get count of cameras in this module.
 *
 * Returns: Number of cameras in this module.
 */
guint
crank_render_module_get_n_camera (CrankRenderModule *module)
{
  return module->cameras->len;
}
