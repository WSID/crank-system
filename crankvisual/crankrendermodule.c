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
#include "crankcamera-private.h"

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
  PROP_NVISIBLE_TYPES,
  PROP_NCAMERAS,

  PROP_PROCESS,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankRenderModule
{
  CrankCompositable  _parent;

  CoglContext *cogl_context;

  GArray      *visible_types;

  GPtrArray   *cameras;

  CrankRenderProcess *process;
};

G_DEFINE_TYPE (CrankRenderModule,
               crank_render_module,
               CRANK_TYPE_COMPOSITABLE_1N)



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_module_init (CrankRenderModule *module)
{
  GType types[2];

  module->visible_types = g_array_new (FALSE, FALSE, sizeof (GType));
  module->cameras = g_ptr_array_new_with_free_func (g_object_unref);

  types[0] = CRANK_TYPE_RENDERABLE;
  types[1] = CRANK_TYPE_LIGHTABLE;

  g_array_append_vals (module->visible_types, types, 2);
}



static void
crank_render_module_class_init (CrankRenderModuleClass *c)
{
  GObjectClass *c_gobject;
  CrankCompositableClass *c_compositable;

  c_gobject = G_OBJECT_CLASS (c);
  c_gobject->get_property = crank_render_module_get_property;
  c_gobject->set_property = crank_render_module_set_property;

  pspecs[PROP_COGL_CONTEXT] =
  g_param_spec_pointer ("cogl-context", "CoglContext",
                        "CoglContext to initialize with.",
                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                        G_PARAM_STATIC_STRINGS );

  pspecs[PROP_NVISIBLE_TYPES] =
  g_param_spec_uint ("nvisible-types", "Number of visible types",
                     "Number of visible types to track.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_NCAMERAS] =
  g_param_spec_uint ("ncameras", "Number of cameras",
                     "Number of cameras added to this module.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_PROCESS] =
  g_param_spec_object ("process", "Rendering process",
                       "Rendering process.",
                       CRANK_TYPE_RENDER_PROCESS,
                       G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  c_compositable = CRANK_COMPOSITABLE_CLASS (c);
  c_compositable->adding = crank_render_module_adding;
  c_compositable->removing = crank_render_module_removing;


  crank_compositable_class_add_requisition (c_compositable,
                                            CRANK_TYPE_SESSION);

  crank_compositable_class_add_requisition (c_compositable,
                                            CRANK_TYPE_SESSION_MODULE_TICK);

  crank_compositable_class_add_requisition (c_compositable,
                                            CRANK_TYPE_SESSION_MODULE_PLACED);
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

    case PROP_NVISIBLE_TYPES:
      g_value_set_uint (value, module->visible_types->len);
      break;

    case PROP_NCAMERAS:
      g_value_set_uint (value, module->cameras->len);
      break;

    case PROP_PROCESS:
      g_value_set_object (value, module->process);
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

    case PROP_PROCESS:
      crank_render_module_set_process (module,
                                       g_value_get_object (value));
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
      CrankRenderProcess *process;

      camera = rmodule->cameras->pdata[i];
      process = crank_camera_get_render_process (camera);

      process = (process != NULL) ? process : rmodule->process;

      if ((process != NULL) &&
          crank_render_process_render_for (process, camera))
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
                                         "visible-types", module->visible_types->len,
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
  guint i;

  for (i = 0; i < module->visible_types->len; i++)
    {
      GType vtype = g_array_index (module->visible_types, GType, i);

      if (g_type_is_a (type, vtype))
        return i;
    }

  return -1;
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

/**
 * crank_render_module_get_process:
 * @module: A Module.
 *
 * Gets module-default rendering process in this module. For cameras without
 * rendering process, this will be used.
 *
 * Returns: (transfer none) (nullable): Module-default rendering process.
 */
CrankRenderProcess*
crank_render_module_get_process (CrankRenderModule *module)
{
  return module->process;
}

/**
 * crank_render_module_set_process:
 * @module: A Module.
 * @process: (transfer none) (nullable): A Process.
 *
 * Sets module-default rendering process in this module.
 */
void
crank_render_module_set_process (CrankRenderModule  *module,
                                 CrankRenderProcess *process)
{
  if (g_set_object (& module->process, process))
    g_object_notify_by_pspec ((GObject*)module, pspecs[PROP_PROCESS]);
}


/**
 * crank_render_module_get_n_visible_types:
 * @module: A Module.
 *
 * Gets number of #CrankVisible types to track.
 *
 * Returns: Number of visible types.
 */
guint
crank_render_module_get_n_visible_types (CrankRenderModule *module)
{
  return module->visible_types->len;
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
  CrankRenderModule *camera_module = crank_camera_get_module (camera);

  if (camera_module != NULL)
    {
      g_warning ("crank_render_module_add_camera: Adding camera that belongs to other module.\n"
                 "  %s@%p <= %s@%p, %s@%p",
                 G_OBJECT_TYPE_NAME (module), module,
                 G_OBJECT_TYPE_NAME (camera), camera,
                 G_OBJECT_TYPE_NAME (camera_module), camera_module);
      return;
    }

  g_ptr_array_add (module->cameras, g_object_ref (camera));
  crank_camera_module_set_module (camera, module);
  g_object_notify_by_pspec ((GObject*)module, pspecs[PROP_NCAMERAS]);
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
  CrankRenderModule *camera_module = crank_camera_get_module (camera);

  if (camera_module != module)
    {
      g_warning ("crank_render_module_remove_camera: Removing camera that does not belong to this module.\n"
                 "  %s@%p <= %s@%p, %s@%p",
                 G_OBJECT_TYPE_NAME (module), module,
                 G_OBJECT_TYPE_NAME (camera), camera,
                 G_OBJECT_TYPE_NAME (camera_module), camera_module);
      return;
    }
  g_ptr_array_remove (module->cameras, camera);
  crank_camera_module_set_module (camera, NULL);
  g_object_notify_by_pspec ((GObject*)module, pspecs[PROP_NCAMERAS]);
}


/**
 * crank_render_module_add_visible_type:
 * @module: A Module.
 * @type: A Type which is subtype of #CrankVisible.
 *
 * Adds a visible type to track.
 *
 * Returns: index of added @type.
 */
gint
crank_render_module_add_visible_type (CrankRenderModule *module,
                                      GType              type)
{
  gint index;

  if (! g_type_is_a (type, CRANK_TYPE_VISIBLE))
    {
      g_warning ("crank_render_module_add_visible_type: Adding non CrankVisible type.\n"
                 "  %s", g_type_name (type));
      return -1;
    }

  index = module->visible_types->len;
  g_array_append_val (module->visible_types, type);

  g_object_notify_by_pspec ((GObject*) module, pspecs[PROP_NVISIBLE_TYPES]);

  return index;
}

/**
 * crank_render_module_get_visible_type:
 * @module: A Module.
 * @index: Index of type.
 *
 * Gets visible tyoe at the index.
 *
 * Returns: Visible type at index.
 */
GType
crank_render_module_get_visible_type (CrankRenderModule *module,
                                      guint              index)
{
  if (module->visible_types->len <= index)
    {
      g_warning ("crank_render_module_get_visible_type: Out of bound.\n"
                 "  %u / %u", index, module->visible_types->len);
      return G_TYPE_INVALID;
    }

  return g_array_index (module->visible_types, GType, index);
}

/**
 * crank_render_module_index_of_visible_type:
 * @module: A Module.
 * @type: A Type which is subtype of #CrankVisible.
 *
 * Look up for index of @type.
 *
 * Returns: Index of @type, or -1 if not found.
 */
gint
crank_render_module_index_of_visible_type (CrankRenderModule *module,
                                           GType              type)
{
  guint i;

  for (i = 0; i < module->visible_types->len; i++)
    {
      // This is not is-a test.
      // Do equality test.
      if (type == g_array_index (module->visible_types, GType, i))
        return i;
    }

  return -1;
}

