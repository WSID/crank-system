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
 * SECTION: crankentity
 * @title: CrankEntity
 * @short_description: Base class for Entity representations.
 * @stability: Unstable
 * @include: crankcore.h
 *
 * This is a base class for entity type.
 */

#define CRANKCORE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "cranksessionmoduleplaced.h"
#include "cranksessionmoduleplaced-private.h"
#include "crankplace.h"

#include "crankentity.h"
#include "crankentity-private.h"




//////// List of virtual functions /////////////////////////////////////////////

static void   crank_entity_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *psepc);

static void   crank_entity_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *psepc);


static void   crank_entity_constructed (GObject *object);

static void   crank_entity_dispose (GObject *object);

static void   crank_entity_finalize (GObject *object);


static gboolean crank_entity_add_compositable (CrankComposite     *composite,
                                              CrankCompositable  *compositable,
                                              GError            **error);

static gboolean crank_entity_remove_compositable (CrankComposite     *composite,
                                                 CrankCompositable  *compositable,
                                                 GError            **error);






//////// Propertites and signals ///////////////////////////////////////////////

enum {
  PROP_0,
  PROP_MODULE,
  PROP_NPLACES,
  PROP_PRIMARY_PLACE,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};







//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankEntityPrivate
{
  CrankSessionModulePlaced *module;
  GPtrArray *places;
} CrankEntityPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CrankEntity,
                            crank_entity,
                            CRANK_TYPE_COMPOSITE)






//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_entity_init (CrankEntity *self)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (self);

  priv->places = g_ptr_array_new ();
}

static void
crank_entity_class_init (CrankEntityClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankCompositeClass *c_composite = CRANK_COMPOSITE_CLASS (c);

  c_gobject->get_property = crank_entity_get_property;
  c_gobject->set_property = crank_entity_set_property;
  c_gobject->constructed = crank_entity_constructed;
  c_gobject->dispose = crank_entity_dispose;
  c_gobject->finalize = crank_entity_finalize;

  c_composite->add_compositable = crank_entity_add_compositable;
  c_composite->remove_compositable = crank_entity_remove_compositable;

  pspecs[PROP_MODULE] =
  g_param_spec_object ("module", "Module of entity",
                      "Module of entity",
                      CRANK_TYPE_SESSION_MODULE_PLACED,
                      G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                      G_PARAM_STATIC_STRINGS );

  pspecs[PROP_NPLACES] =
  g_param_spec_uint ("nplaces", "Number of Places",
                     "Number of Places for this entity.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_PRIMARY_PLACE] =
  g_param_spec_object ("primary-place", "Primary place",
                       "Primary place for this entity.",
                       CRANK_TYPE_PLACE,
                       G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}






//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_entity_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  CrankEntity *self = (CrankEntity*) object;

  switch (prop_id)
    {
    case PROP_MODULE:
      g_value_set_object (value, crank_entity_get_module (self));
      break;

    case PROP_NPLACES:
      g_value_set_uint (value, crank_entity_get_nplaces(self));
      break;

    case PROP_PRIMARY_PLACE:
      g_value_set_object (value, crank_entity_get_primary_place(self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}




static void
crank_entity_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  CrankEntity *self = (CrankEntity*) object;
  CrankEntityPrivate *priv = crank_entity_get_instance_private (self);

  switch (prop_id)
    {
    case PROP_MODULE:
      priv->module = g_value_get_object (value);
      if (priv->module == NULL)
        g_error ("Entity: module is NULL!");
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}




static void
crank_entity_constructed (GObject *object)
{
  GObjectClass *pc = crank_entity_parent_class;
  CrankEntity *self = (CrankEntity*) object;
  CrankEntityPrivate *priv = crank_entity_get_instance_private (self);

  pc->constructed (object);
  crank_session_module_placed_add_placeless (priv->module, self);
  crank_session_module_placed_entity_created (priv->module, self);
}




static void
crank_entity_dispose (GObject *object)
{
  GObjectClass *pc = crank_entity_parent_class;
  CrankEntity *self = (CrankEntity*) object;
  CrankEntityPrivate *priv = crank_entity_get_instance_private (self);

  crank_session_module_placed_entity_disposed (priv->module, self);

  g_ptr_array_set_size (priv->places, 0);
  pc->dispose (object);
}



static void
crank_entity_finalize (GObject *object)
{
  GObjectClass *pc = crank_entity_parent_class;
  CrankEntity *self = (CrankEntity*) object;
  CrankEntityPrivate *priv = crank_entity_get_instance_private (self);

  g_ptr_array_unref (priv->places);
  pc->finalize (object);
}







//////// CrankCompositable /////////////////////////////////////////////////////

static gboolean
crank_entity_add_compositable (CrankComposite    *composite,
                              CrankCompositable *compositable,
                              GError            **error)
{
  CrankCompositeClass *pc = crank_entity_parent_class;
  CrankEntity *self = (CrankEntity*) composite;
  CrankEntityPrivate *priv = crank_entity_get_instance_private (self);

  if (! pc->add_compositable (composite, compositable, error))
    return FALSE;

  crank_session_module_placed_entity_added_compositable (priv->module, self, compositable);
  return TRUE;
}



static gboolean
crank_entity_remove_compositable (CrankComposite     *composite,
                                 CrankCompositable  *compositable,
                                 GError            **error)
{
  CrankCompositeClass *pc = crank_entity_parent_class;
  CrankEntity *self = (CrankEntity*) composite;
  CrankEntityPrivate *priv = crank_entity_get_instance_private (self);

  if (! pc->remove_compositable (composite, compositable, error))
    return FALSE;

  crank_session_module_placed_entity_removed_compositable (priv->module, self, compositable);
  return TRUE;
}








//////// Private Function for CrankPlace ///////////////////////////////////////

/*
 * _crank_entity_place_add_place:
 * @entity: A Entity.
 * @place: A Place.
 *
 * Friendship: #CrankPlace, for private.
 *
 * Adds a @place to place list of @entity.
 */
G_GNUC_INTERNAL void
_crank_entity_place_add_place (CrankEntity *entity,
                               CrankPlace  *place)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (entity);
  g_ptr_array_add (priv->places, place);

  if (priv->places->len == 1)
    {
      g_object_notify_by_pspec ((GObject*)entity, pspecs[PROP_PRIMARY_PLACE]);
      crank_session_module_placed_remove_placeless (priv->module, entity);
    }
}

/*
 * _crank_entity_place_remove_place:
 * @entity: A Entity.
 * @place: A Place.
 *
 * Friendship: #CrankPlace, for private.
 *
 * Removes a @place from place list of @entity.
 *
 * Returns: Whether the removal was succesful.
 */
G_GNUC_INTERNAL gboolean
_crank_entity_place_remove_place (CrankEntity *entity,
                                  CrankPlace  *place)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (entity);
  gboolean switch_primary_place;

  if (priv->places->len == 0)
    return FALSE;

  switch_primary_place = (priv->places->pdata[0] == place);

  if (! g_ptr_array_remove_fast (priv->places, place))
    return FALSE;

  if (switch_primary_place)
    g_object_notify_by_pspec ((GObject*)entity, pspecs[PROP_PRIMARY_PLACE]);

  if (priv->places->len == 0)
    crank_session_module_placed_add_placeless (priv->module, entity);

  return TRUE;
}

/*
 * _crank_entity_place_switch_primary_place:
 * @entity: A Entity.
 * @place: A Place.
 *
 * Friendship: #CrankPlace, for private.
 *
 * Switchs primary place. This is used by #CrankPlace for hand over entity to
 * other #CrankPlace.
 *
 * Returns: Whether the primary place is switched.
 */
G_GNUC_INTERNAL gboolean
_crank_entity_place_switch_primary_place (CrankEntity *entity,
                                          CrankPlace  *place)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (entity);
  gpointer primary_curr;

  guint i;

  if (priv->places->len <= 1)
    return FALSE;

  primary_curr = priv->places->pdata[0];

  if (primary_curr == place)
    return TRUE;

  for (i = 1; i < priv->places->len; i++)
    {
      if (priv->places->pdata[i] == place)
          break;
    }

  if (i == priv->places->len)
    return FALSE;

  priv->places->pdata[i] = primary_curr;
  priv->places->pdata[0] = place;
  g_object_notify_by_pspec ((GObject*)entity, pspecs[PROP_PRIMARY_PLACE]);


  return TRUE;
}

/*
 * _crank_entity_place_belongs_to:
 * @entity: A Entity.
 * @place: A Place.
 *
 * Friendship: #CrankPlace, for private.
 *
 * Checks whether entity is belongs to place.
 *
 * Returns: Whether the entity is belongs to place.
 */
G_GNUC_INTERNAL gboolean
_crank_entity_place_belongs_to (CrankEntity *entity,
                                CrankPlace  *place)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (entity);
  guint i;

  for (i = 0; i < priv->places->len; i++)
    {
      if (priv->places->pdata[i] == place)
          return TRUE;
    }
  return FALSE;
}




//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_entity_get_module:
 * @entity: A Entity.
 *
 * Gets module that this entity belongs to.
 *
 * Returns: (transfer none): A Module.
 */
CrankSessionModulePlaced*
crank_entity_get_module (CrankEntity *entity)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (entity);
  return priv->module;
}

/**
 * crank_entity_get_primary_place:
 * @entity: A Entity.
 *
 * Gets primary place.
 *
 * Returns: (transfer none): A Place.
 */
CrankPlace*
crank_entity_get_primary_place (CrankEntity *entity)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (entity);
  return (CrankPlace*) priv->places->pdata[0];
}

/**
 * crank_entity_get_nplaces:
 * @entity: A Entity.
 *
 * Gets number of places.
 *
 * Returns: number of places.
 */
guint
crank_entity_get_nplaces (CrankEntity *entity)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (entity);
  return priv->places->len;
}





//////// Places ////////////////////////////////////////////////////////////////

/**
 * crank_entity_get_place:
 * @entity: A Entity.
 * @index: A Index.
 *
 * Gets place.
 *
 * Returns: (transfer none): A Place.
 */
CrankPlace*
crank_entity_get_place (CrankEntity *entity,
                        const guint  index)
{
  CrankEntityPrivate *priv = crank_entity_get_instance_private (entity);
  return (CrankPlace*) priv->places->pdata[index];
}
