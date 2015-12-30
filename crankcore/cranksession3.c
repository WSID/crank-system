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

#define CRANKCORE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"
#include "cranksession3.h"
#include "cranksession3module.h"

/**
 * SECTION: cranksession3
 * @title: CrankSession3
 * @short_description: A Session for 3D Environment.
 * @stability: unstable
 * @include: crankcore.h
 *
 * This represents a session with 3d envorinment.
 *
 * # Modules
 *
 * CrankSession3 has module system. This will enable application to replace some
 * system (physics or others) with other implementation.
 *
 * Oncee session is constructed, modules can be added and removed. Before
 * running, module should be initialized for this.
 *
 * Once initialized, place and entity structure will get pointer data for each
 * modules, at allocation. place will get data from both of place module and
 * entity module.
 *
 */


//////// Properties ////////////////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_N_PLACE_MODULES,
  PROP_N_ENTITY_MODULES,
  PROP_PLACE_MODULES,
  PROP_ENTITY_MODULES,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// List of Virtual functions /////////////////////////////////////////////


static void  crank_session3_get_property (GObject    *object,
                                          guint       prop_id,
                                          GValue     *value,
                                          GParamSpec *pspec);

//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSession3Private {
  // Module Management
  gboolean  mod_lock_init;

  GPtrArray *place_modules;
  GPtrArray *entity_modules;

  gsize     place_sz;
  gsize     entity_sz;

  // Places and entities

  GPtrArray *places;
  GPtrArray *entities;
  GPtrArray *entities_placeless;

} CrankSession3Private;

G_DEFINE_TYPE_WITH_CODE (CrankSession3,
                         crank_session3,
                         CRANK_TYPE_SESSION,
                         {
                          G_ADD_PRIVATE (CrankSession3)
                         })

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session3_init (CrankSession3 *self)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (self);

  priv->mod_lock_init = FALSE;

  priv->place_modules = g_ptr_array_new_with_free_func ((GDestroyNotify)g_object_unref);
  priv->entity_modules = g_ptr_array_new_with_free_func ((GDestroyNotify)g_object_unref);

  priv->place_sz = 0;
  priv->entity_sz = 0;

  priv->places = NULL;
  priv->entities = NULL;
  priv->entities_placeless = NULL;
}

static void
crank_session3_class_init (CrankSession3Class *c)
{

  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_session3_get_property;

  pspecs[PROP_N_PLACE_MODULES] =
  g_param_spec_uint ("n-place-modules", "NPlaceModules",
                     "Number of place modules.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_N_ENTITY_MODULES] =
  g_param_spec_uint ("n-entity-modules", "NEntityModules",
                     "Number of entity modules.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_PLACE_MODULES] =
  g_param_spec_boxed ("place-modules", "Place Modules",
                      "Place Modules",
                      G_TYPE_PTR_ARRAY,
                      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_ENTITY_MODULES] =
  g_param_spec_boxed ("entity-modules", "Entity Modules",
                      "Entity Modules",
                      G_TYPE_PTR_ARRAY,
                      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_session3_get_property (GObject    *object,
                             guint       prop_id,
                             GValue     *value,
                             GParamSpec *pspec)
{
  CrankSession3 *session = (CrankSession3*) object;
  switch (prop_id)
    {
    case PROP_N_PLACE_MODULES:
      g_value_set_uint (value,
                        crank_session3_get_n_place_modules (session));
      break;

    case PROP_N_ENTITY_MODULES:
      g_value_set_uint (value,
                        crank_session3_get_n_entity_modules (session));
      break;

    case PROP_PLACE_MODULES:
      g_value_set_boxed (value,
                         crank_session3_get_place_modules (session));
      break;

    case PROP_ENTITY_MODULES:
      g_value_set_boxed (value,
                         crank_session3_get_entity_modules (session));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}



//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_session3_add_place_module:
 * @session: A Session.
 * @module: A module.
 *
 * Add module to session. If session has locked and initialized module, this
 * operation will abort the application.
 */
void
crank_session3_add_place_module (CrankSession3            *session,
                                 CrankSession3PlaceModule *module)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  GObject *self_gobject = (GObject*) session;

  if (priv->mod_lock_init)
    {
      g_error ("Session's module setting has been locked, and being added module."
               "\n  Session: %s, Module: %s",
               G_OBJECT_TYPE_NAME (session), G_OBJECT_TYPE_NAME (module));
    }

  g_ptr_array_add (priv->place_modules, module);

  g_object_notify_by_pspec (self_gobject, pspecs[PROP_N_PLACE_MODULES]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_PLACE_MODULES]);
}

/**
 * crank_session3_remove_place_module:
 * @session: A Session.
 * @module: A Module.
 *
 * Remove a module from session. If session has locked and initialized module,
 * this operation will abort the application.
 */
void
crank_session3_remove_place_module (CrankSession3            *session,
                                    CrankSession3PlaceModule *module)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  GObject *self_gobject = (GObject*) session;

  if (priv->mod_lock_init)
    {
      g_error ("Session's module setting has been locked, and being added module."
               "\n  Session: %s, Module: %s",
               G_OBJECT_TYPE_NAME (session), G_OBJECT_TYPE_NAME (module));
    }

  g_ptr_array_remove (priv->place_modules, module);

  g_object_notify_by_pspec (self_gobject, pspecs[PROP_N_PLACE_MODULES]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_PLACE_MODULES]);
}


/**
 * crank_session3_index_of_place_module:
 * @session: A Session.
 * @module: A Module.
 *
 * Gets index of module from session.
 *
 * Returns: index of module or -1 if module not found.
 */
gint
crank_session3_index_of_place_module (CrankSession3            *session,
                                      CrankSession3PlaceModule *module)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  guint i;

  for (i = 0; i < priv->place_modules->len; i++)
    {
      if (priv->place_modules->pdata[i] == module)
        return i;
    }
  return -1;
}

/**
 * crank_session3_get_n_place_modules:
 * @session: A Session.
 *
 * Gets number of place module.
 */
guint
crank_session3_get_n_place_modules (CrankSession3 *session)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);

  return priv->place_modules->len;
}

/**
 * crank_session3_get_place_module:
 * @session: A Session.
 * @index: Index of place module.
 *
 * Gets a place module.
 *
 * Returns: (transfer none): A Place module.
 */
CrankSession3PlaceModule*
crank_session3_get_place_module (CrankSession3 *session,
                                 const guint    index)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);

  return (CrankSession3PlaceModule*) g_ptr_array_index (priv->place_modules,
                                                        index);
}

/**
 * crank_session3_get_place_modules:
 * @session: A Session.
 *
 * Gets place modules as #GPtrArray.
 *
 * Returns: (transfer none) (element-type CrankSession3PlaceModule):
 *    #GPtrArray of place modules.
 */
const GPtrArray*
crank_session3_get_place_modules (CrankSession3 *session)
{
  return G_PRIVATE_FIELD (CrankSession3, session,
                          GPtrArray*, place_modules);
}


/**
 * crank_session3_add_entity_module:
 * @session: A Session.
 * @module: A module.
 *
 * Add module to session. If session has locked and initialized module, this
 * operation will abort the application.
 */
void
crank_session3_add_entity_module (CrankSession3             *session,
                                  CrankSession3EntityModule *module)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  GObject *self_gobject = (GObject*) session;

  if (priv->mod_lock_init)
    {
      g_error ("Session's module setting has been locked, and being added module."
               "\n  Session: %s, Module: %s",
               G_OBJECT_TYPE_NAME (session), G_OBJECT_TYPE_NAME (module));
    }

  g_ptr_array_add (priv->entity_modules, module);

  g_object_notify_by_pspec (self_gobject, pspecs[PROP_N_ENTITY_MODULES]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_ENTITY_MODULES]);
}


/**
 * crank_session3_remove_entity_module:
 * @session: A Session.
 * @module: A Module.
 *
 * Remove a module from session. If session has locked and initialized module,
 * this operation will abort the application.
 */
void
crank_session3_remove_entity_module (CrankSession3             *session,
                                     CrankSession3EntityModule *module)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  GObject *self_gobject = (GObject*) session;

  if (priv->mod_lock_init)
    {
      g_error ("Session's module setting has been locked, and being added module."
               "\n  Session: %s, Module: %s",
               G_OBJECT_TYPE_NAME (session), G_OBJECT_TYPE_NAME (module));
    }

  g_ptr_array_remove (priv->entity_modules, module);

  g_object_notify_by_pspec (self_gobject, pspecs[PROP_N_ENTITY_MODULES]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_ENTITY_MODULES]);
}


/**
 * crank_session3_index_of_entity_module:
 * @session: A Session.
 * @module: A Module.
 *
 * Gets index of module from session.
 *
 * Returns: index of module or -1 if module not found.
 */
gint
crank_session3_index_of_entity_module (CrankSession3             *session,
                                       CrankSession3EntityModule *module)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  guint i;

  for (i = 0; i < priv->entity_modules->len; i++)
    {
      if (priv->entity_modules->pdata[i] == module)
        return i;
    }
  return -1;
}

/**
 * crank_session3_get_n_entity_modules:
 * @session: A Session.
 *
 * Gets number of entity module.
 */
guint
crank_session3_get_n_entity_modules (CrankSession3 *session)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);

  return priv->entity_modules->len;
}

/**
 * crank_session3_get_entity_module:
 * @session: A Session.
 * @index: Index of module.
 *
 * Gets single entity module.
 *
 * Returns: (transfer none): Entity module.
 */
CrankSession3EntityModule*
crank_session3_get_entity_module (CrankSession3 *session,
                                  const guint    index)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);

  return (CrankSession3EntityModule*) g_ptr_array_index (priv->entity_modules,
                                                         index);
}

/**
 * crank_session3_get_entity_modules:
 * @session: A Session.
 *
 * Gets entity modules as #GPtrArray.
 *
 * Returns: (transfer none) (element-type CrankSession3EntityModule):
 *    Entity modules as #GPtrArray
 */
const GPtrArray*
crank_session3_get_entity_modules (CrankSession3 *session)
{
  return G_PRIVATE_FIELD (CrankSession3, session,
                          GPtrArray*, entity_modules);
}




/**
 * crank_session3_lock_and_init_modules:
 * @session: A Session.
 * @error: A Error.
 *
 * Lock module settings and initialize them for this session. After this,
 * session is able to construct #CrankPlace3 and #CrankEntity3.
 *
 * If the session is already locked, it just does nothing.
 *
 * After locking, adding or removing module is considered as error.
 */
void
crank_session3_lock_and_init_modules (CrankSession3  *session,
                                      GError        **error)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  guint i;

  if (! priv->mod_lock_init)
    {
      guint place_misc_count = priv->place_modules->len + priv->entity_modules->len;
      guint entity_misc_count = priv->entity_modules->len;

      priv->place_sz = sizeof (CrankPlace3) + (sizeof (gpointer) * place_misc_count);
      priv->entity_sz = sizeof (CrankEntity3) + (sizeof (gpointer) * entity_misc_count);

      priv->places = g_ptr_array_new ();
      priv->entities = g_ptr_array_new ();
      priv->entities_placeless = g_ptr_array_new ();

      for (i = 0; i < priv->place_modules->len; i++)
        {
          CrankSession3Module *module;
          GError *merr = NULL;

          module = (CrankSession3Module*)priv->place_modules->pdata[i];
          crank_session3_module_session_init (module, session, &merr);

          if (merr != NULL)
            {
              g_propagate_prefixed_error (error, merr, "%s: ", G_OBJECT_TYPE_NAME (module));
              return;
            }
        }

      for (i = 0; i < priv->entity_modules->len; i++)
        {
          CrankSession3Module *module;
          GError *merr = NULL;

          module = (CrankSession3Module*)priv->entity_modules->pdata[i];
          crank_session3_module_session_init (module, session, &merr);

          if (merr != NULL)
            {
              g_propagate_prefixed_error (error, merr, "%s: ", G_OBJECT_TYPE_NAME (module));
              return;
            }
        }

      priv->mod_lock_init = TRUE;
    }
}


/**
 * crank_session3_make_place:
 * @session: A Session.
 *
 * Allocates a #CrankPlace3. If place is not disposed, it will be disposed when
 * session is destroyed.
 *
 * Returns: (transfer none): A Constructed place. If module setting is not locked,
 * it returns %NULL
 */
CrankPlace3*
crank_session3_make_place (CrankSession3 *session)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  CrankPlace3 *place;
  guint i;

  g_return_val_if_fail (priv->mod_lock_init, NULL);

  place = (CrankPlace3*) g_slice_alloc0 (priv->place_sz);

  place->session = session;
  place->entities = g_ptr_array_new ();

  for (i = 0; i < priv->entity_modules->len; i++)
    {
      CrankSession3EntityModule *module;

      module = (CrankSession3EntityModule*) priv->entity_modules->pdata[i];

      place->misc[i + priv->place_modules->len] =
          crank_session3_entity_module_make_place_data (module, place);
    }

  return place;
}

/**
 * crank_session3_make_entity:
 * @session: A Session.
 *
 * Allocates a #CrankEntity3. If entity is not disposed, it will be disposed when
 * session is destroyed.
 *
 * Returns: (transfer none): A Constructed entity. If module setting is not
 * locked, it returns %NULL
 */
CrankEntity3*
crank_session3_make_entity (CrankSession3 *session)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  CrankEntity3 *entity;

  g_return_val_if_fail (priv->mod_lock_init, NULL);

  entity = (CrankEntity3*) g_slice_alloc0 (priv->entity_sz);

  entity->session = session;

  return entity;
}


/**
 * crank_place3_dispose:
 * @place: A Place to dispose.
 *
 * Disposes a #CrankPlace3. entities staying in it are become placeless. (which
 * does not belongs to anywhere.)
 */
void
crank_place3_dispose (CrankPlace3   *place)
{
  CrankSession3 *session = place->session;
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  guint i;

  g_ptr_array_remove (priv->places, place);

  for (i = 0; i < priv->place_modules->len; i++)
    {
      if (place->misc[i] != NULL)
        {
          CrankSession3PlaceModule *module = priv->place_modules->pdata[i];
          crank_session3_place_module_detached_data (module, place, place->misc[i]);
          g_object_unref (place->misc[i]);
        }
    }

  for (i = 0; i < priv->entity_modules->len; i++)
    {
      guint ni = i + priv->place_modules->len;
      if (place->misc[ni] != NULL)
        g_object_unref (place->misc[ni]);
    }

  for (i = 0; i < place->entities->len; i++)
    {
      CrankEntity3 *entity = (CrankEntity3*) place->entities->pdata[i];

      entity->place = NULL;
    }
  g_ptr_array_free (place->entities, TRUE);
  g_slice_free1 (priv->place_sz, place);
}


/**
 * crank_entity3_dispose:
 * @entity: An entity to dispose.
 *
 * Dispose a #CrankEntity3. It will be removed from place too.
 */
void
crank_entity3_dispose (CrankEntity3  *entity)
{
  CrankSession3 *session = entity->session;
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  guint i;

  for (i = 0; i < priv->entity_modules->len; i++)
    {
      if (entity->misc[i] != NULL)
        {
          CrankSession3EntityModule *module = priv->entity_modules->pdata[i];
          crank_session3_entity_module_detached_data (module, entity, entity->misc[i]);
          g_object_unref (entity->misc[i]);
        }
    }

  g_ptr_array_remove (priv->entities, entity);

  if (entity->place == NULL)
    g_ptr_array_remove (priv->entities_placeless, entity);
  else
    g_ptr_array_remove (entity->place->entities, entity);

  g_slice_free1 (priv->entity_sz, entity);
}




/**
 * crank_place3_atatch_data:
 * @place: A Place.
 * @index: Index of data.
 * @data: (transfer none): A Data.
 *
 * Attaches a data on place.
 */
void
crank_place3_attach_data (CrankPlace3 *place,
                          const guint  index,
                          GObject     *data)
{
  CrankSession3 *session = place->session;
  CrankSession3Private *spriv = crank_session3_get_instance_private (session);

  CrankSession3PlaceModule *module = spriv->place_modules->pdata[index];

  if (place->misc[index] != NULL)
    {
      crank_session3_place_module_detached_data (module, place, place->misc[index]);
      g_object_unref (place->misc[index]);
    }

  if (data != NULL)
    {
      place->misc[index] = g_object_ref (data);
      crank_session3_place_module_attached_data (module, place, data);
    }
  else
    {
      place->misc[index] = NULL;
    }
}

/**
 * crank_place3_detach_data:
 * @place: A Place.
 * @index: Index of data.
 *
 * Detaches a data from place. If there is no data, it does nothing.
 */
void
crank_place3_detach_data (CrankPlace3 *place,
                          const guint  index)
{
  CrankSession3 *session = place->session;
  CrankSession3Private *spriv = crank_session3_get_instance_private (session);

  CrankSession3PlaceModule *module = spriv->place_modules->pdata[index];

  if (place->misc[index] != NULL)
    {
      crank_session3_place_module_detached_data (module, place, place->misc[index]);
      g_object_unref (place->misc[index]);
      place->misc[index] = NULL;
    }
}

/**
 * crank_place3_get_data:
 * @place: A Place.
 * @index: Index of data.
 *
 * Gets data attached to a place.
 *
 * Returns: (transfer none) (nullable): Data of place.
 */
GObject*
crank_place3_get_data (CrankPlace3 *place,
                       const guint  index)
{
  return place->misc[index];
}

/**
 * crank_place3_get_entity_data:
 * @place: A Place.
 * @index: Index of data.
 *
 * Gets entity data from a place.
 *
 * Returns: (transfer none) (nullable): Data of place.
 */
GObject*
crank_place3_get_entity_data (CrankPlace3 *place,
                              const guint  index)
{
  CrankSession3 *session = place->session;
  CrankSession3Private *spriv = crank_session3_get_instance_private (session);

  return place->misc[spriv->place_modules->len + index];
}

/**
 * crank_entity3_attach_data:
 * @entity: A Entity.
 * @index: The index.
 * @data: (nullable): The data, or %NULL to detach data.
 *
 * Attaches a data to entity. If there is alerady attached data, it will be
 * detached.
 */
void
crank_entity3_attach_data (CrankEntity3 *entity,
                           const guint   index,
                           GObject      *data)
{
  CrankSession3 *session = entity->session;
  CrankSession3Private *spriv = crank_session3_get_instance_private (session);
  CrankSession3EntityModule *module;
  module = spriv->entity_modules->pdata[index];

  if (entity->misc[index] != NULL)
    {
      crank_session3_entity_module_detached_data (module, entity, entity->misc[index]);
      g_object_unref (entity->misc[index]);
    }

  if (data != NULL)
    {
      entity->misc[index] = g_object_ref (data);
      crank_session3_entity_module_attached_data (module, entity, data);
    }
  else
    {
      entity->misc[index] = NULL;
    }
}

/**
 * crank_entity3_get_data:
 * @entity: A Entity.
 * @index: The index.
 *
 * Gets entity data from an entity.
 *
 * Returns: (transfer none) (nullable): Data of entity, or %NULL if no data is
 * attached.
 */
GObject*
crank_entity3_get_data (CrankEntity3 *entity,
                        const guint   index)
{
  return entity->misc[index];
}
