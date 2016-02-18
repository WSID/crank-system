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

static gboolean   crank_render_module_adding (CrankCompositable  *compositable,
                                              CrankComposite     *composite,
                                              GError            **error);

static gboolean   crank_render_module_removing (CrankCompositable  *compositable,
                                                CrankComposite     *composite,
                                                GError            **error);


//////// Functions for other modules ///////////////////////////////////////////

static void       crank_render_module_tick (CrankSessionModuleTick *module,
                                            gpointer                user_data);

static void       crank_render_module_place_created (CrankSessionModulePlaced *pmodule,
                                                     CrankPlace               *place,
                                                     gpointer                  user_data);

static void       crank_render_module_entity_added (CrankSessionModulePlaced *pmodule,
                                                    CrankPlace               *place,
                                                    CrankEntity              *entity,
                                                    gpointer                  userdata);

static void       crank_render_module_entity_removed (CrankSessionModulePlaced *pmodule,
                                                      CrankPlace               *place,
                                                      CrankEntity              *entity,
                                                      gpointer                  userdata);


static void       crank_render_module_entity_added_compositable (CrankSessionModulePlaced *pmodule,
                                                                 CrankEntity              *entity,
                                                                 CrankCompositable        *compositable,
                                                                 gpointer                  userdata);

static void       crank_render_module_entity_removed_compositable (CrankSessionModulePlaced *pmodule,
                                                                   CrankEntity              *entity,
                                                                   CrankCompositable        *compositable,
                                                                   gpointer                  userdata);


//////// Private functions /////////////////////////////////////////////////////

static gint      crank_render_module_get_tindex (CrankRenderModule *module,
                                                  GType              type);


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
  CrankCompositable  _parent;

  CoglContext *cogl_context;

  GPtrArray   *cameras;

  GPtrArray   *render_entities;
};

G_DEFINE_TYPE_WITH_CODE (CrankRenderModule,
                         crank_render_module,
                         CRANK_TYPE_COMPOSITABLE_1N,
                         {
                          crank_gtype_compositable_add_requisition (
                              g_define_type_id,
                              CRANK_TYPE_SESSION);

                          crank_gtype_compositable_add_requisition (
                              g_define_type_id,
                              CRANK_TYPE_SESSION_MODULE_PLACED);

                          crank_gtype_compositable_add_requisition (
                              g_define_type_id,
                              CRANK_TYPE_SESSION_MODULE_TICK);
                         })



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
  CrankCompositableClass *c_compositable;

  c_gobject = G_OBJECT_CLASS (c);
  c_gobject->get_property = crank_render_module_get_property;
  c_gobject->set_property = crank_render_module_set_property;

  pspecs[PROP_COGL_CONTEXT] = g_param_spec_pointer ("cogl-context", "CoglContext",
                                                    "CoglContext to initialize with.",
                                                    G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                                                    G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  c_compositable = CRANK_COMPOSITABLE_CLASS (c);
  c_compositable->adding = crank_render_module_adding;
  c_compositable->removing = crank_render_module_removing;
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

static gboolean
crank_render_module_adding (CrankCompositable  *compositable,
                            CrankComposite     *composite,
                            GError            **error)
{
  CrankCompositableClass *pc = crank_render_module_parent_class;
  CrankRenderModule *rmodule = (CrankRenderModule*)compositable;
  CrankSessionModulePlaced *pmodule;
  CrankSessionModuleTick *tmodule;


  if (! pc->adding (compositable, composite, error))
    return FALSE;

  // Placed Module
  pmodule = CRANK_SESSION_MODULE_PLACED (
      crank_composite_get_compositable_by_gtype (
            composite,
            CRANK_TYPE_SESSION_MODULE_PLACED));

  if ((crank_session_module_placed_get_place_type (pmodule) != CRANK_TYPE_PLACE3) ||
      (crank_session_module_placed_get_entity_type (pmodule) != CRANK_TYPE_ENTITY3))
    {
      GType ptype = crank_session_module_placed_get_place_type (pmodule);
      GType etype = crank_session_module_placed_get_entity_type (pmodule);

      g_set_error (error,
                   CRANK_COMPOSITE_ERROR,
                   CRANK_COMPOSITE_ERROR_REJECTED,
                   "CrankRenderModule requires CrankPlace3 and CrankEntity3\n"
                   "  But %s@%p provides %s and %s",
                   G_OBJECT_TYPE_NAME (pmodule), pmodule,
                   g_type_name (ptype), g_type_name (etype));

      return FALSE;
    }



  g_signal_connect (pmodule, "place-created",
                    (GCallback)crank_render_module_place_created, rmodule);

  g_signal_connect (pmodule, "entity-added",
                    (GCallback)crank_render_module_entity_added, rmodule);

  g_signal_connect (pmodule, "entity-removed",
                    (GCallback)crank_render_module_entity_removed, rmodule);

  g_signal_connect (pmodule, "entity-added-compositable",
                    (GCallback)crank_render_module_entity_added_compositable, rmodule);

  g_signal_connect (pmodule, "entity-removed-compositable",
                    (GCallback)crank_render_module_entity_removed_compositable, rmodule);


  // Tick Module
  tmodule = CRANK_SESSION_MODULE_TICK (
      crank_composite_get_compositable_by_gtype (
          composite,
          CRANK_TYPE_SESSION_MODULE_TICK));

  g_signal_connect (tmodule, "tick", (GCallback)crank_render_module_tick, rmodule);
  return TRUE;
}


static gboolean
crank_render_module_removing (CrankCompositable  *compositable,
                              CrankComposite     *composite,
                              GError            **error)
{
  g_set_error (error,
               CRANK_COMPOSITE_ERROR,
               CRANK_COMPOSITE_ERROR_REJECTED,
               "CrankRenderModule does not support removing.\n"
               "  %s@%p : %s@%p",
               G_OBJECT_TYPE_NAME (composite), composite,
               G_OBJECT_TYPE_NAME (compositable), compositable);
  return FALSE;
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

      place = (CrankPlace3*)crank_entity_get_primary_place ((CrankEntity*)entity);
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
                                   CrankPlace               *place,
                                   gpointer                  userdata)
{
  CrankRenderModule *module  = (CrankRenderModule*) userdata;

  crank_composite_add_compositable (
      (CrankComposite*) place,
      (CrankCompositable*) g_object_new (CRANK_TYPE_RENDER_PDATA,
                                         "visible-types", 2,
                                         NULL),
      NULL);
}


static void
crank_render_module_entity_added (CrankSessionModulePlaced *pmodule,
                                  CrankPlace               *place,
                                  CrankEntity              *entity,
                                  gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;
  CrankRenderPData *pdata;

  guint i;
  guint n;

  pdata = (CrankRenderPData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PDATA);

  n = crank_composite_get_ncompositables ((CrankComposite*)entity);

  for (i = 0; i < n; i++)
    {
      CrankCompositable *compositable =
          crank_composite_get_compositable ((CrankComposite*)entity, i);

      if (! CRANK_IS_VISIBLE (compositable))
        continue;


      gint tindex = crank_render_module_get_tindex (module, G_OBJECT_TYPE(compositable));
      crank_render_pdata_add_entity (pdata, entity, (CrankVisible*)compositable, tindex);
    }
}


static void
crank_render_module_entity_removed (CrankSessionModulePlaced *pmodule,
                                    CrankPlace               *place,
                                    CrankEntity              *entity,
                                    gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;
  CrankRenderPData *pdata;

  guint i;
  guint n;

  pdata = (CrankRenderPData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PDATA);

  n = crank_composite_get_ncompositables ((CrankComposite*)entity);

  for (i = 0; i < n; i++)
    {
      CrankCompositable *compositable =
          crank_composite_get_compositable ((CrankComposite*)entity, i);

      if (! CRANK_IS_VISIBLE (compositable))
        continue;


      gint tindex = crank_render_module_get_tindex (module, G_OBJECT_TYPE(compositable));
      crank_render_pdata_remove_entity (pdata, entity, (CrankVisible*)compositable, tindex);
    }
}


static void
crank_render_module_entity_added_compositable (CrankSessionModulePlaced *pmodule,
                                               CrankEntity              *entity,
                                               CrankCompositable        *compositable,
                                               gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;
  CrankPlace *place;
  CrankRenderPData *pdata;

  place = crank_entity_get_primary_place (entity);

  if (place == NULL)
    return;

  pdata = (CrankRenderPData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PDATA);


  if (CRANK_IS_VISIBLE (compositable))
    {
      gint tindex = crank_render_module_get_tindex (module, G_OBJECT_TYPE(compositable));
      crank_render_pdata_add_entity (pdata, entity, (CrankVisible*)compositable, tindex);
    }
}

static void
crank_render_module_entity_removed_compositable (CrankSessionModulePlaced *pmodule,
                                                 CrankEntity              *entity,
                                                 CrankCompositable        *compositable,
                                                 gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;
  CrankPlace *place;
  CrankRenderPData *pdata;

  place = crank_entity_get_primary_place (entity);

  if (place == NULL)
    return;

  pdata = (CrankRenderPData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PDATA);


  if (CRANK_IS_VISIBLE (compositable))
    {
      gint tindex = crank_render_module_get_tindex (module, G_OBJECT_TYPE(compositable));
      crank_render_pdata_remove_entity (pdata, entity, (CrankVisible*)compositable, tindex);
    }
}


//////// Private functions /////////////////////////////////////////////////////

static gint
crank_render_module_get_tindex (CrankRenderModule *module,
                                GType              type)
{
  if (g_type_is_a (type, CRANK_TYPE_RENDERABLE))
    return 0;
  else if (g_type_is_a (type, CRANK_TYPE_LIGHTABLE))
    return 1;

  else return -1;
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

  pdata = (CrankRenderPData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PDATA);

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


  pdata = (CrankRenderPData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PDATA);

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


  pdata = (CrankRenderPData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PDATA);

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


  pdata = (CrankRenderPData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PDATA);

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
      CrankRenderable *renderable = (CrankRenderable*)
          crank_composite_get_compositable_by_gtype ((CrankComposite*)entity, CRANK_TYPE_RENDERABLE);

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
      CrankRenderable *renderable = (CrankRenderable*)
          crank_composite_get_compositable_by_gtype ((CrankComposite*)entity, CRANK_TYPE_RENDERABLE);
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
      CrankLightable *lightable = (CrankLightable*)
          crank_composite_get_compositable_by_gtype ((CrankComposite*)entity, CRANK_TYPE_LIGHTABLE);
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
      CrankRenderable *renderable = (CrankRenderable*)
          crank_composite_get_compositable_by_gtype ((CrankComposite*)entity, CRANK_TYPE_RENDERABLE);
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
      CrankRenderable *renderable = (CrankRenderable*)
          crank_composite_get_compositable_by_gtype ((CrankComposite*)entity, CRANK_TYPE_RENDERABLE);
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
      CrankLightable *lightable = (CrankLightable*)
          crank_composite_get_compositable_by_gtype ((CrankComposite*)entity, CRANK_TYPE_LIGHTABLE);
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
