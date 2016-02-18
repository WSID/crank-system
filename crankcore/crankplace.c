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
 * SECTION: crankplace
 * @title: CrankPlace
 * @short_description: Base class for Place representations.
 * @stability: Unstable
 * @include: crankcore.h
 *
 * This is a base class for placed type.
 */

#define CRANKCORE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "cranksessionmoduleplaced.h"
#include "crankplace.h"
#include "crankentity.h"

#include "crankplace-private.h"
#include "crankentity-private.h"
#include "cranksessionmoduleplaced-private.h"



typedef struct _CrankPlacePrivate CrankPlacePrivate;

//////// List of virtual functions /////////////////////////////////////////////

static void   crank_place_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *psepc);

static void   crank_place_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *psepc);

static void   crank_place_constructed (GObject *object);

static void   crank_place_dispose (GObject *object);

static void   crank_place_finalize (GObject *object);


static gboolean crank_place_add_compositable (CrankComposite     *composite,
                                              CrankCompositable  *compositable,
                                              GError            **error);

static gboolean crank_place_remove_compositable (CrankComposite     *composite,
                                                 CrankCompositable  *compositable,
                                                 GError            **error);







//////// Propertites and signals ///////////////////////////////////////////////

enum {
  PROP_0,
  PROP_MODULE,
  PROP_NENTITIES,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

static guint  sig_entity_added;
static guint  sig_entity_removed;





//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankPlacePrivate
{
  CrankSessionModulePlaced *module;
  GPtrArray *entities;
} CrankPlacePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CrankPlace,
                            crank_place,
                            CRANK_TYPE_COMPOSITE)






//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_place_init (CrankPlace *place)
{
  CrankPlacePrivate *priv = crank_place_get_instance_private (place);

  priv->entities = g_ptr_array_new_with_free_func (g_object_unref);
}

static void
crank_place_class_init (CrankPlaceClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankCompositeClass *c_composite = CRANK_COMPOSITE_CLASS (c);

  c_gobject->get_property = crank_place_get_property;
  c_gobject->set_property = crank_place_set_property;
  c_gobject->constructed = crank_place_constructed;
  c_gobject->dispose = crank_place_dispose;
  c_gobject->finalize = crank_place_finalize;

  c_composite->add_compositable = crank_place_add_compositable;
  c_composite->remove_compositable = crank_place_remove_compositable;

  pspecs[PROP_MODULE] =
  g_param_spec_object ("module", "Module",
                       "Module",
                       CRANK_TYPE_SESSION_MODULE_PLACED,
                       G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                       G_PARAM_STATIC_STRINGS );

  pspecs[PROP_NENTITIES] =
  g_param_spec_uint ("nentities", "Number of Entities",
                     "Number of entities in this place.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  /**
   * CrankPlace::entity-added:
   * @place: A Place.
   * @entity: A Entity.
   *
   * This is emitted when a entity is added to a place.
   */
  sig_entity_added =
  g_signal_new ("entity-added", CRANK_TYPE_PLACE,     // Signal name and owner type
                G_SIGNAL_RUN_LAST,                  // Signal flags
                0,                                  // VF offset
                NULL, NULL,                         // Accumulator
                NULL,                               // Marshaller
                G_TYPE_NONE, 1, CRANK_TYPE_ENTITY); // Returns, parameters

  /**
   * CrankPlace::entity-removed:
   * @place: A Place.
   * @entity: A Entity.
   *
   * This is emitted when a entity is removed from a place.
   */
  sig_entity_removed =
  g_signal_new ("entity-removed", CRANK_TYPE_PLACE,  // Signal name and owner type
                G_SIGNAL_RUN_LAST,                  // Signal flags
                0,                                  // VF offset
                NULL, NULL,                         // Accumulator
                NULL,                               // Marshaller
                G_TYPE_NONE, 1, CRANK_TYPE_ENTITY); // Returns, parameters
}






//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_place_get_property (GObject    *object,
                          guint       prop_id,
                          GValue     *value,
                          GParamSpec *pspec)
{
  CrankPlace *self = (CrankPlace*) object;

  switch (prop_id)
    {
    case PROP_MODULE:
      g_value_set_object (value, crank_place_get_module (self));
      break;

    case PROP_NENTITIES:
      g_value_set_uint (value, crank_place_get_nentities(self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}



static void
crank_place_set_property (GObject      *object,
                          guint         prop_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
  CrankPlace *self = (CrankPlace*) object;
  CrankPlacePrivate *priv = crank_place_get_instance_private (self);

  switch (prop_id)
    {
    case PROP_MODULE:
      priv->module = g_value_get_object (value);
      if (priv->module == NULL)
        g_error ("CrankPlace: module is NULL!");
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
crank_place_constructed (GObject *object)
{
  GObjectClass *pc = crank_place_parent_class;
  CrankPlace *self = (CrankPlace*) object;
  CrankPlacePrivate *priv = crank_place_get_instance_private (self);

  pc->constructed (object);
  crank_session_module_placed_place_created (priv->module, self);
}


static void
crank_place_dispose (GObject *object)
{
  GObjectClass *pc = crank_place_parent_class;
  CrankPlace *self = (CrankPlace*) object;
  CrankPlacePrivate *priv = crank_place_get_instance_private (self);
  guint i;

  crank_session_module_placed_place_disposed (priv->module, self);

  priv->module = NULL;
  for (i = 0; i < priv->entities->len; i++)
    {
      CrankEntity *entity = priv->entities->pdata[i];

      _crank_place_disconnect_entity (self, entity);
      _crank_entity_place_remove_place (entity, self);
    }

  g_ptr_array_set_size (priv->entities, 0);
  pc->dispose (object);
}



static void
crank_place_finalize (GObject *object)
{
  GObjectClass *pc = crank_place_parent_class;
  CrankPlace *self = (CrankPlace*) object;
  CrankPlacePrivate *priv = crank_place_get_instance_private (self);

  g_ptr_array_unref (priv->entities);
  pc->finalize (object);
}






//////// CrankCompositable /////////////////////////////////////////////////////

static gboolean
crank_place_add_compositable (CrankComposite    *composite,
                              CrankCompositable *compositable,
                              GError            **error)
{
  CrankCompositeClass *pc = crank_place_parent_class;
  CrankPlace *self = (CrankPlace*)composite;
  CrankPlacePrivate *priv = crank_place_get_instance_private (self);

  if (! pc->add_compositable (composite, compositable, error))
    return FALSE;

  crank_session_module_placed_place_added_compositable (priv->module, self, compositable);
  return TRUE;
}



static gboolean
crank_place_remove_compositable (CrankComposite     *composite,
                                 CrankCompositable  *compositable,
                                 GError            **error)
{
  CrankCompositeClass *pc = crank_place_parent_class;
  CrankPlace *self = (CrankPlace*)composite;
  CrankPlacePrivate *priv = crank_place_get_instance_private (self);

  if (! pc->remove_compositable (composite, compositable, error))
    return FALSE;

  crank_session_module_placed_place_removed_compositable (priv->module, self, compositable);
  return TRUE;
}





//////// Internal functions /////////////////////////////////////////////////////

#ifndef __GTK_DOC_IGNORED__

/*
 * _crank_place_disconnect_entity:
 * @place: A Place.
 * @entity: A Entity.
 *
 * Performs notifications operations for modules and signals that connected to
 * this.
 */
G_GNUC_INTERNAL void
_crank_place_disconnect_entity (CrankPlace  *place,
                                CrankEntity *entity)
{
  CrankPlacePrivate *priv = crank_place_get_instance_private (place);

  crank_session_module_placed_entity_removed (priv->module, place, entity);
  g_signal_emit (place, sig_entity_removed, 0, entity);
}


/*
 * _crank_place_entity_remove_entity:
 * @place: A Place.
 * @entity: A Entity.
 *
 * Performs internal state update for performing remove operation.
 */
G_GNUC_INTERNAL void
_crank_place_entity_remove_entity (CrankPlace  *place,
                                   CrankEntity *entity)
{
  CrankPlacePrivate *priv = crank_place_get_instance_private (place);

  g_ptr_array_remove_fast (priv->entities, entity);
  g_object_notify_by_pspec ((GObject*)place, pspecs[PROP_NENTITIES]);
}


#endif







//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_place_get_module:
 * @place: A Place.
 *
 * Gets module of places.
 *
 * Returns: (transfer none): Module of place.
 */
CrankSessionModulePlaced*
crank_place_get_module (CrankPlace *place)
{
  CrankPlacePrivate *priv = crank_place_get_instance_private (place);
  return priv->module;
}

/**
 * crank_place_get_nentities:
 * @place: A Place.
 *
 * Gets number of entities in the place.
 *
 * Returns: Number of entities in the place.
 */
guint
crank_place_get_nentities (CrankPlace *place)
{
  CrankPlacePrivate *priv = crank_place_get_instance_private (place);
  return priv->entities->len;
}






//////// Entiites //////////////////////////////////////////////////////////////

/**
 * crank_place_add_entity:
 * @place: A Place.
 * @entity: A Entity.
 *
 * Adds entity to the place. If entity is already in the place, %FALSE will be
 * returned.
 *
 * Returns: whether entity was added to the place.
 */
gboolean
crank_place_add_entity (CrankPlace  *place,
                        CrankEntity *entity)
{
  CrankPlacePrivate *priv = crank_place_get_instance_private (place);

  if (priv->module != crank_entity_get_module (entity))
    {
      CrankSessionModulePlaced *pmod = priv->module;
      CrankSessionModulePlaced *emod = crank_entity_get_module (entity);

      g_warning ("crank_place_add_entity: Attempt to add entity of differnet module.\n"
                 "  %s@%p belongs to %s@%p\n"
                 "  %s@%p belongs to %s@%p",
                 G_OBJECT_TYPE_NAME (place), place,
                 G_OBJECT_TYPE_NAME (pmod), pmod,
                 G_OBJECT_TYPE_NAME (entity), entity,
                 G_OBJECT_TYPE_NAME (emod), emod);
      return FALSE;
    }

  if (crank_place_contains_entity (place, entity))
    return FALSE;

  _crank_entity_place_add_place (entity, place);
  g_ptr_array_add (priv->entities, g_object_ref (entity));

  crank_session_module_placed_entity_added (priv->module, place, entity);
  g_signal_emit (place, sig_entity_added, 0, entity);
  g_object_notify_by_pspec ((GObject*)place, pspecs[PROP_NENTITIES]);

  return TRUE;
}

/**
 * crank_place_remove_entity:
 * @place: A Place.
 * @entity: A Entity.
 *
 * Removes entity from the place. If entity is not in the place, %FALSE will be
 * returned.
 *
 * Returns: whether entity was removed from the place.
 */
gboolean
crank_place_remove_entity (CrankPlace  *place,
                           CrankEntity *entity)
{
  CrankPlacePrivate *priv = crank_place_get_instance_private (place);

  if (priv->module != crank_entity_get_module (entity))
    {
      CrankSessionModulePlaced *pmod = priv->module;
      CrankSessionModulePlaced *emod = crank_entity_get_module (entity);

      g_warning ("crank_place_remove_entity: Attempt to remove entity of differnet module.\n"
                 "  %s@%p belongs to %s@%p\n"
                 "  %s@%p belongs to %s@%p",
                 G_OBJECT_TYPE_NAME (place), place,
                 G_OBJECT_TYPE_NAME (pmod), pmod,
                 G_OBJECT_TYPE_NAME (entity), entity,
                 G_OBJECT_TYPE_NAME (emod), emod);
      return FALSE;
    }

  if (! crank_place_contains_entity (place, entity))
    return FALSE;

  _crank_place_disconnect_entity (place, entity);
  _crank_place_entity_remove_entity (place, entity);
  _crank_entity_place_remove_place (entity, place);
  return TRUE;
}

/**
 * crank_place_contains_entity:
 * @place: A Place.
 * @entity: A Entity.
 *
 * Checks whether the entity belongs to the place.
 *
 * Returns: Whether the entity belongs to the place.
 */
gboolean
crank_place_contains_entity (CrankPlace  *place,
                             CrankEntity *entity)
{
  return _crank_entity_place_belongs_to (entity, place);
}


/**
 * crank_place_foreach_entity:
 * @place: A Place.
 * @func: (scope call): A Function to be called for each entity.
 * @userdata: (closure func): A userdata.
 *
 * Calls @func for each entities in the @place.
 */
void
crank_place_foreach_entity (CrankPlace *place,
                            GFunc       func,
                            gpointer    userdata)
{
  CrankPlacePrivate *priv = crank_place_get_instance_private (place);

  g_ptr_array_foreach (priv->entities, func, userdata);
}
