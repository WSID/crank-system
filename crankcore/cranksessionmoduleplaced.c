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
 * SECTION: cranksessionmoduleplaced
 * @title: CrankSessionModulePlaced
 * @short_description: Module with place and entity.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * Represents a session module that adds feature to track entities and places.
 *
 * # CrankSessionModulePlaced as #CrankCompositable
 *
 * Composite Requisition: #CrankSession
 *
 */

#define CRANKCORE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "crankplace.h"
#include "crankentity.h"

#include "cranksession.h"
#include "cranksessionmoduleplaced.h"
#include "cranksessionmoduleplaced-private.h"


//////// Virtual function override /////////////////////////////////////////////

static void crank_session_module_placed_constructed (GObject *object);

static void crank_session_module_placed_get_property (GObject    *object,
                                                      guint       prop_id,
                                                      GValue     *value,
                                                      GParamSpec *pspec);

static void crank_session_module_placed_set_property (GObject      *object,
                                                      guint         prop_id,
                                                      const GValue *value,
                                                      GParamSpec   *pspec);

static void crank_session_module_placed_dispose (GObject *object);



//////// Private functions /////////////////////////////////////////////////////

static void alloc_data_fini (gpointer alloc_data);

static void fini_pointer (gpointer data,
                          gpointer userdata);

static void fini_boxed (gpointer data,
                        gpointer userdata);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_PLACE_TYPE,
  PROP_ENTITY_TYPE,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

static guint sig_place_created;
static guint sig_place_disposed;

static guint sig_entity_created;
static guint sig_entity_disposed;

static guint sig_entity_added;
static guint sig_entity_removed;

static guint sig_place_added_compositable;
static guint sig_place_removed_compositable;

static guint sig_entity_added_compositable;
static guint sig_entity_removed_compositable;


//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSessionModulePlacedPrivate {
  // Allocation Data
  GType place_type;
  GType entity_type;

  // Places
  GPtrArray *places;
  //GPtrArray *places_active;

  // Entities
  GPtrArray *entities;
  GPtrArray *entities_placeless;

} CrankSessionModulePlacedPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CrankSessionModulePlaced,
                            crank_session_module_placed,
                            CRANK_TYPE_COMPOSITABLE_1N)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session_module_placed_init (CrankSessionModulePlaced *self)
{
}

static void
crank_session_module_placed_class_init (CrankSessionModulePlacedClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankCompositableClass *c_compositable = CRANK_COMPOSITABLE_CLASS (c);

  c_gobject->constructed =crank_session_module_placed_constructed;
  c_gobject->get_property = crank_session_module_placed_get_property;
  c_gobject->set_property = crank_session_module_placed_set_property;
  c_gobject->dispose = crank_session_module_placed_dispose;

  pspecs[PROP_PLACE_TYPE] =
  g_param_spec_gtype ("place-type", "Place type",
                      "GType of place",
                      CRANK_TYPE_PLACE,
                      G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                      G_PARAM_STATIC_STRINGS );

  pspecs[PROP_ENTITY_TYPE] =
  g_param_spec_gtype ("entity-type", "Entity type",
                      "GType of entity",
                      CRANK_TYPE_ENTITY,
                      G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                      G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);



  crank_compositable_class_add_requisition (c_compositable,
                                            CRANK_TYPE_SESSION);


  /**
   * CrankSessionModulePlaced::place-created:
   * @module: A Module.
   * @place: A Newly created place.
   *
   * Emitted when a place is constructed with this module.
   */
  sig_place_created = g_signal_new ("place-created",
                                    CRANK_TYPE_SESSION_MODULE_PLACED,
                                    G_SIGNAL_RUN_LAST,
                                    G_STRUCT_OFFSET (CrankSessionModulePlacedClass,
                                                     place_created),
                                    NULL, NULL,
                                    g_cclosure_marshal_VOID__BOXED,
                                    G_TYPE_NONE,
                                    1, CRANK_TYPE_PLACE);

  /**
   * CrankSessionModulePlaced::place-disposed:
   * @module: A Module.
   * @place: A place to be disposed.
   *
   * Emitted when a place is disposed.
   */
  sig_place_disposed = g_signal_new ("place-disposed",
                                    CRANK_TYPE_SESSION_MODULE_PLACED,
                                    G_SIGNAL_RUN_LAST,
                                    G_STRUCT_OFFSET (CrankSessionModulePlacedClass,
                                                     place_disposed),
                                    NULL, NULL,
                                    g_cclosure_marshal_VOID__BOXED,
                                    G_TYPE_NONE,
                                    1, CRANK_TYPE_PLACE);

  /**
   * CrankSessionModulePlaced::entity-created:
   * @module: A Module.
   * @entity: A Newly created entity.
   *
   * Emitted when an entity is constructed with this module.
   */
  sig_entity_created = g_signal_new ("entity-created",
                                    CRANK_TYPE_SESSION_MODULE_PLACED,
                                    G_SIGNAL_RUN_LAST,
                                    G_STRUCT_OFFSET (CrankSessionModulePlacedClass,
                                                     entity_created),
                                    NULL, NULL,
                                    g_cclosure_marshal_VOID__BOXED,
                                    G_TYPE_NONE,
                                    1, CRANK_TYPE_ENTITY);

  /**
   * CrankSessionModulePlaced::entity-disposed:
   * @module: A Module.
   * @entity: A entity to be disposed.
   *
   * Emitted when an entity is disposed.
   */
  sig_entity_disposed = g_signal_new ("entity-disposed",
                                    CRANK_TYPE_SESSION_MODULE_PLACED,
                                    G_SIGNAL_RUN_LAST,
                                    G_STRUCT_OFFSET (CrankSessionModulePlacedClass,
                                                     entity_disposed),
                                    NULL, NULL,
                                    g_cclosure_marshal_VOID__BOXED,
                                    G_TYPE_NONE,
                                    1, CRANK_TYPE_ENTITY);

  /**
   * CrankSessionModulePlaced::entity-added:
   * @module: A Module.
   * @place: A Place.
   * @entity: A Entity.
   *
   * Emitted when entity is added to a place.
   */
  sig_entity_added = g_signal_new ("entity-added",
                                   CRANK_TYPE_SESSION_MODULE_PLACED,
                                   G_SIGNAL_RUN_LAST,
                                   G_STRUCT_OFFSET (CrankSessionModulePlacedClass,
                                                    entity_added),
                                   NULL, NULL,
                                   NULL,
                                   G_TYPE_NONE,
                                   2, CRANK_TYPE_PLACE, CRANK_TYPE_ENTITY);

  /**
   * CrankSessionModulePlaced::entity-removed:
   * @module: A Module.
   * @place: A Place.
   * @entity: A Entity.
   *
   * Emitted when entity is removed from a place.
   */
  sig_entity_removed = g_signal_new ("entity-removed",
                                   CRANK_TYPE_SESSION_MODULE_PLACED,
                                   G_SIGNAL_RUN_LAST,
                                   G_STRUCT_OFFSET (CrankSessionModulePlacedClass,
                                                    entity_removed),
                                   NULL, NULL,
                                   NULL,
                                   G_TYPE_NONE,
                                   2, CRANK_TYPE_PLACE, CRANK_TYPE_ENTITY);

  /**
   * CrankSessionModulePlaced::place-added-compositable:
   * @module: A Module.
   * @place: A Place.
   * @compositable: A Compositable.
   *
   * Emitted when @compositable is added to a place.
   */
  sig_place_added_compositable =
  g_signal_new ("place-added-compositable", CRANK_TYPE_SESSION_MODULE_PLACED,
                G_SIGNAL_RUN_LAST,
                G_STRUCT_OFFSET (CrankSessionModulePlacedClass, place_added_compositable),
                NULL, NULL,
                NULL,
                G_TYPE_NONE, 2, CRANK_TYPE_PLACE, CRANK_TYPE_COMPOSITABLE);

  /**
   * CrankSessionModulePlaced::place-removed-compositable:
   * @module: A Module.
   * @place: A Place.
   * @compositable: A Compositable.
   *
   * Emitted when @compositable is removed from a place.
   */
  sig_place_removed_compositable =
  g_signal_new ("place-removed-compositable", CRANK_TYPE_SESSION_MODULE_PLACED,
                G_SIGNAL_RUN_LAST,
                G_STRUCT_OFFSET (CrankSessionModulePlacedClass, place_removed_compositable),
                NULL, NULL,
                NULL,
                G_TYPE_NONE, 2, CRANK_TYPE_PLACE, CRANK_TYPE_COMPOSITABLE);

  /**
   * CrankSessionModulePlaced::entity-added-compositable:
   * @module: A Module.
   * @place: A Place.
   * @compositable: A Compositable.
   *
   * Emitted when @compositable is added to a place.
   */
  sig_entity_added_compositable =
  g_signal_new ("entity-added-compositable", CRANK_TYPE_SESSION_MODULE_PLACED,
                G_SIGNAL_RUN_LAST,
                G_STRUCT_OFFSET (CrankSessionModulePlacedClass, entity_added_compositable),
                NULL, NULL,
                NULL,
                G_TYPE_NONE, 2, CRANK_TYPE_PLACE, CRANK_TYPE_COMPOSITABLE);

  /**
   * CrankSessionModulePlaced::entity-removed-compositable:
   * @module: A Module.
   * @place: A Place.
   * @compositable: A Compositable.
   *
   * Emitted when @compositable is removed from a place.
   */
  sig_entity_removed_compositable =
  g_signal_new ("entity-removed-compositable", CRANK_TYPE_SESSION_MODULE_PLACED,
                G_SIGNAL_RUN_LAST,
                G_STRUCT_OFFSET (CrankSessionModulePlacedClass, entity_removed_compositable),
                NULL, NULL,
                NULL,
                G_TYPE_NONE, 2, CRANK_TYPE_PLACE, CRANK_TYPE_COMPOSITABLE);

}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_session_module_placed_constructed (GObject *object)
{
  GObjectClass *pc_gobject;
  CrankSessionModulePlaced *module;
  CrankSessionModulePlacedPrivate *priv;

  pc_gobject = (GObjectClass*) crank_session_module_placed_parent_class;
  pc_gobject->constructed (object);

  module = (CrankSessionModulePlaced*) object;
  priv = crank_session_module_placed_get_instance_private (module);

  priv->places = g_ptr_array_new ();
  priv->entities = g_ptr_array_new ();
  priv->entities_placeless = g_ptr_array_new ();
}

static void
crank_session_module_placed_get_property (GObject    *object,
                                          guint       prop_id,
                                          GValue     *value,
                                          GParamSpec *pspec)
{
  CrankSessionModulePlaced *module;
  module = (CrankSessionModulePlaced*) object;

  switch (prop_id)
    {
    case PROP_PLACE_TYPE:
      g_value_set_gtype (value, crank_session_module_placed_get_place_type (module));
      break;

    case PROP_ENTITY_TYPE:
      g_value_set_gtype (value, crank_session_module_placed_get_entity_type (module));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_session_module_placed_set_property (GObject      *object,
                                          guint         prop_id,
                                          const GValue *value,
                                          GParamSpec   *pspec)
{
  CrankSessionModulePlaced *module;
  CrankSessionModulePlacedPrivate *priv;

  module = (CrankSessionModulePlaced*) object;
  priv = crank_session_module_placed_get_instance_private (module);

  switch (prop_id)
    {
    case PROP_PLACE_TYPE:
      priv->place_type = g_value_get_gtype (value);
      break;

    case PROP_ENTITY_TYPE:
      priv->entity_type = g_value_get_gtype (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_session_module_placed_dispose (GObject *object)
{
  GObjectClass *pc_gobject;
  CrankSessionModulePlaced* module;
  CrankSessionModulePlacedPrivate* priv;

  pc_gobject = (GObjectClass*) crank_session_module_placed_parent_class;

  module = (CrankSessionModulePlaced*)object;
  priv = crank_session_module_placed_get_instance_private (module);

  if (priv->places->len != 0)
    g_error ("Places are left and module is being disposed.");

  if (priv->entities->len != 0)
    g_error ("Entities are left and module is being disposed.");

  g_ptr_array_unref (priv->places);
  g_ptr_array_unref (priv->entities);
  g_ptr_array_unref (priv->entities_placeless);

  pc_gobject->dispose (object);
}



//////// Private Functions /////////////////////////////////////////////////////


//////// Internal Functions ////////////////////////////////////////////////////
#ifndef __GTK_DOC_IGNORE__


G_GNUC_INTERNAL
void
crank_session_module_placed_add_placeless (CrankSessionModulePlaced *module,
                                           CrankEntity              *entity)
{
  CrankSessionModulePlacedPrivate *priv;
  priv = crank_session_module_placed_get_instance_private (module);

  g_ptr_array_add (priv->entities_placeless, entity);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_remove_placeless (CrankSessionModulePlaced *module,
                                              CrankEntity              *entity)
{
  CrankSessionModulePlacedPrivate *priv;
  priv = crank_session_module_placed_get_instance_private (module);

  g_ptr_array_remove_fast (priv->entities_placeless, entity);
}


G_GNUC_INTERNAL
void
crank_session_module_placed_place_created (CrankSessionModulePlaced *module,
                                           CrankPlace               *place)
{
  g_signal_emit (module, sig_place_created, 0, place);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_place_disposed (CrankSessionModulePlaced *module,
                                            CrankPlace               *place)
{
  g_signal_emit (module, sig_place_disposed, 0, place);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_entity_created (CrankSessionModulePlaced *module,
                                            CrankEntity              *entity)
{
  g_signal_emit (module, sig_entity_created, 0, entity);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_entity_disposed (CrankSessionModulePlaced *module,
                                             CrankEntity              *entity)
{
  g_signal_emit (module, sig_entity_disposed, 0, entity);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_entity_added (CrankSessionModulePlaced *module,
                                          CrankPlace               *place,
                                          CrankEntity              *entity)
{
  g_signal_emit (module, sig_entity_added, 0, place, entity);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_entity_removed (CrankSessionModulePlaced *module,
                                            CrankPlace               *place,
                                            CrankEntity              *entity)
{
  g_signal_emit (module, sig_entity_removed, 0, place, entity);
}


G_GNUC_INTERNAL
void
crank_session_module_placed_place_added_compositable (CrankSessionModulePlaced *module,
                                                      CrankPlace               *place,
                                                      CrankCompositable        *compositable)
{
  g_signal_emit (module, sig_place_added_compositable, 0, place, compositable);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_place_removed_compositable (CrankSessionModulePlaced *module,
                                                        CrankPlace               *place,
                                                        CrankCompositable        *compositable)
{
  g_signal_emit (module, sig_place_removed_compositable, 0, place, compositable);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_entity_added_compositable (CrankSessionModulePlaced *module,
                                                       CrankEntity              *entity,
                                                       CrankCompositable        *compositable)
{
  g_signal_emit (module, sig_entity_added_compositable, 0, entity, compositable);
}

G_GNUC_INTERNAL
void
crank_session_module_placed_entity_removed_compositable (CrankSessionModulePlaced *module,
                                                         CrankEntity              *entity,
                                                         CrankCompositable        *compositable)
{
  g_signal_emit (module, sig_entity_removed_compositable, 0, entity, compositable);
}

#endif


//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_session_module_placed_new:
 * @place_base_size: Base size for #CrankPlaceBase.
 * @entity_base_size: Base size for #CrankEntityBase.
 *
 * Constructs new instance.
 *
 * Returns: (transfer full): Newly constructed instance.
 */
CrankSessionModulePlaced*
crank_session_module_placed_new (const GType place_type,
                                 const GType entity_type)
{
  return (CrankSessionModulePlaced*)
      g_object_new (CRANK_TYPE_SESSION_MODULE_PLACED,
                    "place-type", place_type,
                    "entity-type", entity_type,
                    NULL);
}



//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_session_module_placed_get_place_type:
 * @module: A Module.
 *
 * Get #GType of #CrankPlace.
 *
 * Returns: #GType of #CrankPlace.
 */
GType
crank_session_module_placed_get_place_type (CrankSessionModulePlaced *module)
{
  CrankSessionModulePlacedPrivate *priv;
  priv = crank_session_module_placed_get_instance_private (module);

  return priv->place_type;
}

/**
 * crank_session_module_placed_get_entity_type:
 * @module: A Module.
 *
 * Get #GType of #CrankPlace.
 *
 * Returns: #GType of #CrankEntity.
 */
GType
crank_session_module_placed_get_entity_type (CrankSessionModulePlaced *module)
{
  CrankSessionModulePlacedPrivate *priv;
  priv = crank_session_module_placed_get_instance_private (module);

  return priv->entity_type;
}
