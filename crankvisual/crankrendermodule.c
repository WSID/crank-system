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

#include "crankrenderplacedata.h"
#include "crankrenderprocess.h"
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

  CrankRenderProcess *process;
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

  module->process = (CrankRenderProcess*)
      g_object_new (CRANK_TYPE_RENDER_PROCESS, NULL);
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

      crank_render_process_render_at (rmodule->process,
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
      (CrankCompositable*) g_object_new (CRANK_TYPE_RENDER_PLACE_DATA,
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
  CrankRenderPlaceData *pdata;

  guint i;
  guint n;

  pdata = (CrankRenderPlaceData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PLACE_DATA);

  n = crank_composite_get_ncompositables ((CrankComposite*)entity);

  for (i = 0; i < n; i++)
    {
      CrankCompositable *compositable =
          crank_composite_get_compositable ((CrankComposite*)entity, i);

      if (! CRANK_IS_VISIBLE (compositable))
        continue;


      gint tindex = crank_render_module_get_tindex (module, G_OBJECT_TYPE(compositable));
      crank_render_place_data_add_entity (pdata, entity, (CrankVisible*)compositable, tindex);
    }
}


static void
crank_render_module_entity_removed (CrankSessionModulePlaced *pmodule,
                                    CrankPlace               *place,
                                    CrankEntity              *entity,
                                    gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;
  CrankRenderPlaceData *pdata;

  guint i;
  guint n;

  pdata = (CrankRenderPlaceData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PLACE_DATA);

  n = crank_composite_get_ncompositables ((CrankComposite*)entity);

  for (i = 0; i < n; i++)
    {
      CrankCompositable *compositable =
          crank_composite_get_compositable ((CrankComposite*)entity, i);

      if (! CRANK_IS_VISIBLE (compositable))
        continue;


      gint tindex = crank_render_module_get_tindex (module, G_OBJECT_TYPE(compositable));
      crank_render_place_data_remove_entity (pdata, entity, (CrankVisible*)compositable, tindex);
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
  CrankRenderPlaceData *pdata;

  place = crank_entity_get_primary_place (entity);

  if (place == NULL)
    return;

  pdata = (CrankRenderPlaceData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PLACE_DATA);


  if (CRANK_IS_VISIBLE (compositable))
    {
      gint tindex = crank_render_module_get_tindex (module, G_OBJECT_TYPE(compositable));
      crank_render_place_data_add_entity (pdata, entity, (CrankVisible*)compositable, tindex);
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
  CrankRenderPlaceData *pdata;

  place = crank_entity_get_primary_place (entity);

  if (place == NULL)
    return;

  pdata = (CrankRenderPlaceData*) crank_composite_get_compositable_by_gtype (
      (CrankComposite*) place, CRANK_TYPE_RENDER_PLACE_DATA);


  if (CRANK_IS_VISIBLE (compositable))
    {
      gint tindex = crank_render_module_get_tindex (module, G_OBJECT_TYPE(compositable));
      crank_render_place_data_remove_entity (pdata, entity, (CrankVisible*)compositable, tindex);
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







//////// Property getter / setters /////////////////////////////////////////////

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









//////// Public functions //////////////////////////////////////////////////////


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
