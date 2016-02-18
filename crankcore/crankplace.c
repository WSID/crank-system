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

#include "crankentity-private.h"



typedef struct _CrankPlacePrivate CrankPlacePrivate;

//////// List of virtual functions /////////////////////////////////////////////

static void   crank_place_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *psepc);

static void   crank_place_dispose (GObject *object);

static void   crank_place_finalize (GObject *object);


static gboolean crank_place_add_compositable (CrankComposite     *composite,
                                              CrankCompositable  *compositable,
                                              GError            **error);

static gboolean crank_place_remove_compositable (CrankComposite     *composite,
                                                 CrankCompositable  *compositable,
                                                 GError            **error);





//////// Private Functions /////////////////////////////////////////////////////

static void   crank_place__remove_entity (CrankPlace  *priv,
                                          CrankEntity *entity)







//////// Propertites and signals ///////////////////////////////////////////////

enum {
  PROP_0,
  PROP_NENTITIES,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};







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
  c_gobject->dispose = crank_place_dispose;
  c_gobject->finalize = crank_place_finalize;

  c_composite->add_compositable = crank_place_add_compositable;
  c_composite->remove_compositable = crank_place_remove_compositable;

  pspecs[PROP_NENTITIES] =
  g_param_spec_uint ("nentities", "Number of Entities",
                     "Number of entities in this place.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
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
    case PROP_NENTITIES:
      g_value_set_uint (value, crank_place_get_nentities(self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_place_dispose (GObject *object)
{
  GObjectClass *pc = crank_place_parent_class;
  CrankPlace *self = (CrankPlace*) object;
  CrankPlacePrivate *priv = crank_place_get_instance_private (self);

  guint i;

  for (i = priv->entities->len; 0 < i;)
    {
      CrankEntity *entity;

      i--;
      entity = priv->entities->pdata[i];
      crank_place__remove_entity (place, entity);
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


static gboolean
crank_place_add_compositable (CrankComposite    *composite,
                              CrankCompositable *compositable,
                              GError            **error)
{
  CrankCompositeClass *pc = crank_place_parent_class;
  return pc->add_compositable (composite, compositable, error);

  // TODO: Notify
}

static gboolean
crank_place_remove_compositable (CrankComposite     *composite,
                                 CrankCompositable  *compositable,
                                 GError            **error)
{
  CrankCompositeClass *pc = crank_place_parent_class;
  return pc->remove_compositable (composite, compositable, error);

  // TODO: Notify
}





//////// Private functions /////////////////////////////////////////////////////

static void
crank_place__remove_entity (CrankPlace  *place,
                            CrankEntity *entity)
{
  _crank_entity_place_remove_place (entity, place);
  // TODO: Notify and such things...!
}




//////// Public functions //////////////////////////////////////////////////////

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

  // TODO: Check membership of entity.
  g_ptr_array_add (priv->entities, entity);
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

  // TODO: Check membership of entity.
  if (g_ptr_array_remove_fast (priv->entities, entity))
    {
      crank_place__remove_entity (priv, entity);
      g_object_notify_by_pspec ((GObject*)place, pspecs[PROP_NENTITIES]);
    }
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
