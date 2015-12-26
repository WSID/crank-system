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

/**
 * SECTION: cranksession3
 * @title: CrankSession3
 * @short_description: A Session for 3D Environment.
 * @stability: unstable
 * @include: crankcore.h
 *
 * This represents a session with 3d envorinment.
 */


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

}


//////// Public functions //////////////////////////////////////////////////////

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

  if (priv->mod_lock_init)
    {
      g_error ("Session's module setting has been locked, and being added module."
               "\n  Session: %s, Module: %s",
               G_OBJECT_TYPE_NAME (session), G_OBJECT_TYPE_NAME (module));
    }

  g_ptr_array_add (priv->entity_modules, module);
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
crank_session3_remove_module (CrankSession3             *session,
                              CrankSession3EntityModule *module)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);

  if (priv->mod_lock_init)
    {
      g_error ("Session's module setting has been locked, and being added module."
               "\n  Session: %s, Module: %s",
               G_OBJECT_TYPE_NAME (session), G_OBJECT_TYPE_NAME (module));
    }

  g_ptr_array_remove (priv->entity_modules, module);
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
 * crank_session3_lock_and_init_modules:
 * @session: A Session.
 *
 * Lock module settings and initialize them for this session. After this,
 * session is able to construct #CrankPlace3 and #CrankEntity3.
 *
 * If the session is already locked, it just does nothing.
 *
 * After locking, adding or removing module is considered as error.
 */
void
crank_session3_lock_and_init_modules (CrankSession3 *session)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);

  if (! priv->mod_lock_init)
    {
      guint place_misc_count = priv->place_modules->len + priv->entity_modules->len;
      guint entity_misc_count = priv->entity_modules->len;

      priv->place_sz = sizeof (CrankPlace3) + (sizeof (gpointer) * place_misc_count);
      priv->entity_sz = sizeof (CrankEntity3) + (sizeof (gpointer) * entity_misc_count);

      priv->places = g_ptr_array_new ();
      priv->entities = g_ptr_array_new ();
      priv->entities_placeless = g_ptr_array_new ();
      // TODO: do initialize module.
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

  g_return_val_if_fail (priv->mod_lock_init, NULL);

  place = (CrankPlace3*) g_slice_alloc0 (priv->place_sz);

  place->session = session;
  place->entities = g_ptr_array_new ();

  // TODO: Attach entity modules' data to place.

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
 * crank_session3_dispose_place:
 * @session: A Session.
 * @place: (transfer none): A Place to dispose.
 *
 * Disposes a #CrankPlace3. entities staying in it are become placeless. (which
 * does not belongs to anywhere.)
 */
void
crank_session3_dispose_place (CrankSession3 *session,
                              CrankPlace3   *place)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);
  guint i;

  g_ptr_array_remove (priv->places, place);

  // TODO: Dispose modules' data from place

  for (i = 0; i < place->entities->len; i++)
    {
      CrankEntity3 *entity = (CrankEntity3*) place->entities->pdata[i];

      entity->place = NULL;
    }
  g_ptr_array_free (place->entities, TRUE);
  g_slice_free1 (priv->place_sz, place);
}


/**
 * crank_session3_dispose_entity:
 * @session: A Session.
 * @entity: (transfer none): An entity to dispose.
 *
 * Dispose a #CrankEntity3. It will be removed from place too.
 */
void
crank_session3_dispose_entity (CrankSession3 *session,
                               CrankEntity3  *entity)
{
  CrankSession3Private *priv = crank_session3_get_instance_private (session);

  g_ptr_array_remove (priv->entities, entity);

  if (entity->place == NULL)
    g_ptr_array_remove (priv->entities_placeless, entity);
  else
    g_ptr_array_remove (entity->place->entities, entity);

  // TODO: Dispose modules; data from entity.


  g_slice_free1 (priv->entity_sz, entity);
}
