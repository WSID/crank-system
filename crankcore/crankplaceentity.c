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

#include "cranksessionmoduleplaced.h"
#include "cranksessionmoduleplaced-private.h"
#include "crankplaceentity.h"


//////// Private Types /////////////////////////////////////////////////////////

typedef struct _CrankPlaceHeader
{
  guint                     _refc;
  CrankSessionModulePlaced *module;
  GPtrArray                *entities;

  gchar                     place_data[];
} CrankPlaceHeader;

typedef struct _CrankEntityHeader
{
  guint                     _refc;
  CrankSessionModulePlaced *module;
  CrankPlaceBase           *place;

  gchar                     entity_data[];
} CrankEntityHeader;




//////// Private Functions /////////////////////////////////////////////////////

static CrankPlaceHeader  *crank_place_base_get_header (CrankPlaceBase* place);

static CrankEntityHeader *crank_entity_base_get_header (CrankEntityBase* entity);



//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankPlaceBase,
                     crank_place_base,
                     crank_place_base_ref,
                     crank_place_base_unref);

G_DEFINE_BOXED_TYPE (CrankEntityBase,
                     crank_entity_base,
                     crank_entity_base_ref,
                     crank_entity_base_unref);

//////// Private Functions /////////////////////////////////////////////////////

static CrankPlaceHeader*
crank_place_base_get_header (CrankPlaceBase* place)
{
  return (CrankPlaceHeader*) CRANK_PTR_DIFF (place, sizeof (CrankPlaceHeader));
}

static CrankEntityHeader*
crank_entity_base_get_header (CrankEntityBase* place)
{
  return (CrankEntityHeader*) CRANK_PTR_DIFF (place, sizeof (CrankEntityHeader));
}


//////// Allocation ////////////////////////////////////////////////////////////

/**
 * crank_place_base_new:
 * @module: (transfer none): A Module.
 *
 * Allocates a place structure.
 *
 * Returns: (transfer full): Newly allocated place structure.
 */
CrankPlaceBase*
crank_place_base_new (CrankSessionModulePlaced *module)
{
  CrankPlaceHeader* header;
  CrankPlaceBase* place;
  gsize size;

  size = sizeof (CrankPlaceHeader) +
         crank_session_module_placed_get_place_size (module);

  header = g_slice_alloc0 (size);

  header->_refc = 1;
  header->module = g_object_ref (module);
  header->entities = g_ptr_array_new ();

  place = (CrankPlaceBase*) header->place_data;

  crank_session_module_placed_place_created (module, place);
  return place;
}

/**
 * crank_entity_base_new:
 * @module: (transfer none): A Module.
 *
 * Allocates a entity structure.
 *
 * Returns: (transfer full): Newly allocated place structure.
 */
CrankEntityBase*
crank_entity_base_new (CrankSessionModulePlaced *module)
{
  CrankEntityHeader *header;
  CrankEntityBase *entity;
  gsize size;

  size = sizeof (CrankEntityHeader) +
         crank_session_module_placed_get_entity_size (module);

  header = g_slice_alloc0 (size);

  header->_refc = 1;
  header->module = g_object_ref (module);

  entity = (CrankEntityBase*) header->entity_data;

  crank_session_module_placed_entity_created (module, entity);
  return entity;
}

/**
 * crank_place_base_ref:
 * @place: (transfer none): A Place.
 *
 * Increase ref count for the place.
 *
 * Returns: (transfer full): Place with increased reference count.
 */
CrankPlaceBase*
crank_place_base_ref (CrankPlaceBase* place)
{
  CrankPlaceHeader* header = crank_place_base_get_header (place);

  g_atomic_int_inc (& header->_refc);

  return place;
}

/**
 * crank_place_base_unref:
 * @place: (transfer full): A Place.
 *
 * Decreases ref count for the place.
 */
void
crank_place_base_unref (CrankPlaceBase* place)
{

  CrankPlaceHeader* header = crank_place_base_get_header (place);

  if (g_atomic_int_dec_and_test (& header->_refc))
    {
      gsize sz = crank_session_module_placed_get_place_size (header->module) +
                 sizeof (CrankPlaceHeader);
      guint i;

      for (i = 0; i < header->entities->len; i++)
        {
          CrankEntityBase *entity;
          CrankEntityHeader *entity_header;

          entity = (CrankEntityBase*) header->entities->pdata[i];
          entity_header = crank_entity_base_get_header (entity);

          crank_session_module_placed_entity_removed (header->module, place, entity);

          entity_header->place = NULL;
        }

      crank_session_module_placed_fini_place (header->module, place);
      crank_session_module_placed_place_disposed (header->module, place);

      g_ptr_array_unref (header->entities);
      g_object_unref (header->module);
      g_slice_free1 (sz, header);
    }
}


/**
 * crank_entity_base_ref:
 * @entity: (transfer none): A Entity.
 *
 * Increase ref count for the entity.
 *
 * Returns: (transfer full): A Entity, with increased ref count.
 */
CrankEntityBase*
crank_entity_base_ref (CrankEntityBase* entity)
{
  CrankEntityHeader* header = crank_entity_base_get_header (entity);

  g_atomic_int_inc (& header->_refc);

  return entity;
}

/**
 * crank_entity_base_unref:
 * @entity: (transfer full): A Entity.
 *
 * Decrease ref count for the entity.
 */
void
crank_entity_base_unref (CrankEntityBase* entity)
{

  CrankEntityHeader* header = crank_entity_base_get_header (entity);

  if (g_atomic_int_dec_and_test (& header->_refc))
    {
      gsize sz = crank_session_module_placed_get_place_size (header->module) +
                 sizeof (CrankEntityHeader);

      if (header->place != NULL)
        {
          CrankPlaceHeader *place_header = crank_place_base_get_header (header->place);

          crank_session_module_placed_entity_removed (header->module,
                                                      header->place,
                                                      entity);

          g_ptr_array_remove (place_header->entities, entity);
        }

      crank_session_module_placed_fini_entity (header->module, entity);
      crank_session_module_placed_entity_disposed (header->module, entity);

      g_object_unref (header->module);
      g_slice_free1 (sz, header);
    }
}


//////// Public Functions //////////////////////////////////////////////////////

/**
 * crank_place_base_get_module:
 * @place: A Place.
 *
 * Gets module of place.
 *
 * Returns: (transfer none): A Module.
 */
CrankSessionModulePlaced*
crank_place_base_get_module (CrankPlaceBase* place)
{
  CrankPlaceHeader* header = crank_place_base_get_header (place);

  return header->module;
}

/**
 * crank_entity_base_get_module:
 * @entity: A Entnty.
 *
 * Gets module of entity.
 *
 * Returns: (transfer none): A Module.
 */
CrankSessionModulePlaced*
crank_entity_base_get_module (CrankEntityBase* entity)
{
  CrankEntityHeader* header = crank_entity_base_get_header (entity);

  return header->module;
}


/**
 * crank_place_base_get_n_entities:
 * @place: A Place.
 *
 * Get number of entities in the place.
 *
 * Returns: Number of entities.
 */
guint
crank_place_base_get_n_entities (CrankPlaceBase *place)
{
  CrankPlaceHeader *header = crank_place_base_get_header (place);

  return header->entities->len;
}

/**
 * crank_entity_base_get_place:
 * @entity: A Entity.
 *
 * Get place where this belongs to.
 *
 * Returns: (nullable): Place that holds entity, or %NULL if it does not belong
 *                      to nowhere.
 */
CrankPlaceBase*
crank_entity_base_get_place (CrankEntityBase *entity)
{
  CrankEntityHeader *header = crank_entity_base_get_header (entity);

  return header->place;
}


//////// Place Functions ///////////////////////////////////////////////////////

/**
 * crank_place_base_add_entity:
 * @place: A Place.
 * @entity: A Entity.
 *
 * Add entity to place.
 */
void
crank_place_base_add_entity (CrankPlaceBase  *place,
                             CrankEntityBase *entity)
{
  CrankPlaceHeader *place_header = crank_place_base_get_header (place);
  CrankEntityHeader *entity_header = crank_entity_base_get_header (entity);

  if (entity_header->module != place_header->module)
    {
      g_warning ("crank_place_base_add_entity: place and entity belong to different module.");
      return;
    }

  else if (entity_header->place == place)
    {
      g_warning ("crank_place_base_add_entity: Attempt to add entity that already added to the place.");
      return;
    }
  else if (entity_header->place != NULL)
    {
      g_warning ("crank_place_base_add_entity: Attempt to add entity that belongs to other place.");
      return;
    }
  else
    {
      g_ptr_array_add (place_header->entities, entity);
      entity_header->place = place;

      crank_session_module_placed_entity_added (entity_header->module,
                                                place,
                                                entity);
    }
}

/**
 * crank_place_base_remove_entity:
 * @place: A Place.
 * @entity: A Entity.
 *
 * Remove entity from place.
 */
void
crank_place_base_remove_entity (CrankPlaceBase  *place,
                                CrankEntityBase *entity)
{
  CrankPlaceHeader *place_header = crank_place_base_get_header (place);
  CrankEntityHeader *entity_header = crank_entity_base_get_header (entity);

  if (entity_header->module != place_header->module)
    {
      g_warning ("crank_place_base_remove_entity: place and entity belong to different module.");
      return;
    }

  else if (entity_header->place == NULL)
    {
      g_warning ("crank_place_base_remove_entity: Attempt to remove entity that belongs to nowhere.");
      return;
    }
  else if (entity_header->place != place)
    {
      g_warning ("crank_place_base_remove_entity: Attempt to remove entity that does not belong the place.");
      return;
    }
  else
    {
      crank_session_module_placed_entity_removed (entity_header->module,
                                                  place,
                                                  entity);

      g_ptr_array_remove (place_header->entities, entity);
      entity_header->place = NULL;
    }
}
