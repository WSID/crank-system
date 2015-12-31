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

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"
#include "cranksession3.h"
#include "cranksession3module.h"


/**
 * SECTION: cranksession3module
 * @title: CrankSession3Module
 * @short_description: Base class for modulized logic of CrankSession3
 * @stability: unstable
 * @include: crankcore.h
 *
 * A CrankSession3Module represents modulized common logic for #CrankSession3.
 * This may be rendering system so that, it can render #CrankEntity3 in the
 * sessions. Or it may be physics system so that it can perform simulations.
 */

//////// Default implementations ///////////////////////////////////////////////

static void crank_session3_module_def_session_init (CrankSession3Module  *self,
                                                    CrankSession3        *session,
                                                    GError              **error);

static void crank_session3_module_def_tick (CrankSession3Module *self);

static void crank_session3_place_module_def_session_init (CrankSession3Module  *self,
                                                          CrankSession3        *session,
                                                          GError              **error);

static void crank_session3_entity_module_def_session_init (CrankSession3Module  *self,
                                                           CrankSession3        *session,
                                                           GError              **error);


//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSession3ModulePrivate
{
  CrankSession3 *session;
} CrankSession3ModulePrivate;

typedef struct _CrankSession3PlaceModulePrivate
{
  guint   index;
} CrankSession3PlaceModulePrivate;

typedef struct _CrankSession3EntityModulePrivate
{
  guint   place_index;
  guint   index;
} CrankSession3EntityModulePrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankSession3Module,
                                     crank_session3_module,
                                     G_TYPE_OBJECT)

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankSession3PlaceModule,
                                     crank_session3_place_module,
                                     CRANK_TYPE_SESSION3_MODULE)

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankSession3EntityModule,
                                     crank_session3_entity_module,
                                     CRANK_TYPE_SESSION3_MODULE)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session3_module_init (CrankSession3Module *self)
{

}

static void
crank_session3_module_class_init (CrankSession3ModuleClass *c)
{
  c->session_init = crank_session3_module_def_session_init;
  c->tick = crank_session3_module_def_tick;
}


static void
crank_session3_place_module_init (CrankSession3PlaceModule *self)
{

}

static void
crank_session3_place_module_class_init (CrankSession3PlaceModuleClass *c)
{
  CrankSession3ModuleClass *c_session3module;

  c_session3module = CRANK_SESSION3_MODULE_CLASS (c);
  c_session3module->session_init = crank_session3_place_module_def_session_init;
}

static void
crank_session3_entity_module_init (CrankSession3EntityModule *self)
{

}

static void
crank_session3_entity_module_class_init (CrankSession3EntityModuleClass *c)
{
  CrankSession3ModuleClass *c_session3module;

  c_session3module = CRANK_SESSION3_MODULE_CLASS (c);
  c_session3module->session_init = crank_session3_entity_module_def_session_init;
}

//////// Default implementations ///////////////////////////////////////////////

static void
crank_session3_module_def_session_init (CrankSession3Module  *self,
                                        CrankSession3        *session,
                                        GError              **error)
{
  CrankSession3ModulePrivate *priv = crank_session3_module_get_instance_private (self);
  priv->session = session;
}

static void
crank_session3_module_def_tick (CrankSession3Module *self)
{
  return;  // Does nothing on every tick.
}

static void
crank_session3_place_module_def_session_init (CrankSession3Module  *self,
                                              CrankSession3        *session,
                                              GError              **error)
{
  CrankSession3ModuleClass *pc;
  CrankSession3PlaceModule *s;
  CrankSession3PlaceModulePrivate *priv;

  pc = (CrankSession3ModuleClass*)crank_session3_place_module_parent_class;
  pc->session_init (self, session, error);

  s = (CrankSession3PlaceModule*)self;
  priv = crank_session3_place_module_get_instance_private (s);

  priv->index = crank_session3_index_of_place_module (session, s);
}

static void
crank_session3_entity_module_def_session_init (CrankSession3Module  *self,
                                               CrankSession3        *session,
                                               GError              **error)
{
  CrankSession3ModuleClass *pc;
  CrankSession3EntityModule *s;
  CrankSession3EntityModulePrivate *priv;

  pc = (CrankSession3ModuleClass*)crank_session3_entity_module_parent_class;
  pc->session_init (self, session, error);

  s = (CrankSession3EntityModule*)self;
  priv = crank_session3_entity_module_get_instance_private (s);

  priv->index = crank_session3_index_of_entity_module (session, s);
  priv->place_index = crank_session3_get_n_place_modules (session) + priv->index;
}



//////// Common ////////////////////////////////////////////////////////////////

/**
 * crank_session3_module_session_init:
 * @module: A Module.
 * @session: A Session.
 * @error: Error.
 *
 * Initialize a module for session.
 */
void
crank_session3_module_session_init (CrankSession3Module *module,
                                    CrankSession3       *session,
                                    GError             **error)
{
  CrankSession3ModuleClass *c = CRANK_SESSION3_MODULE_GET_CLASS (module);

  c->session_init (module, session, error);
}

/**
 * crank_session3_module_tick:
 * @module: A Module.
 *
 * Performs single tick action, for example, iterate physics simulation, or
 * rendering scene on a surface.
 */
void
crank_session3_module_tick (CrankSession3Module *module)
{
  CrankSession3ModuleClass *c = CRANK_SESSION3_MODULE_GET_CLASS (module);

  c->tick (module);
}


//////// Place Modules /////////////////////////////////////////////////////////

/**
 * crank_session3_place_module_attached_data:
 * @module: A Module.
 * @place: (transfer none): A Place that attached data.
 * @data: (transfer none): A data attached.
 *
 * This will be called when place data is attached to a #CrankPlace3.
 */
void
crank_session3_place_module_attached_data (CrankSession3PlaceModule *module,
                                           CrankPlace3              *place,
                                           GObject                  *data)
{
  CrankSession3PlaceModuleClass *c = CRANK_SESSION3_PLACE_MODULE_GET_CLASS (module);

  c->attached_data (module, place, data);
}

/**
 * crank_session3_place_module_detached_data:
 * @module: A Module.
 * @place: (transfer none): A Place that detached data.
 * @data: (transfer none): A data detached.
 *
 * This will be called when data is detached from a #CrankPlace3.
 */
void
crank_session3_place_module_detached_data (CrankSession3PlaceModule *module,
                                           CrankPlace3              *place,
                                           GObject                  *data)
{
  CrankSession3PlaceModuleClass *c = CRANK_SESSION3_PLACE_MODULE_GET_CLASS (module);

  c->detached_data (module, place, data);
}



//////// Entity Module /////////////////////////////////////////////////////////

/**
 * crank_session3_entity_module_make_place_data:
 * @module: A Module.
 * @place: A Place data.
 *
 * This will be called when #CrankPlace3 is constructed. Through this, it can
 * pass data structure to manage entities. (like octree)
 *
 * Returns: (transfer full) (nullable): Place data for this module.
 */
GObject*
crank_session3_entity_module_make_place_data (CrankSession3EntityModule *module,
                                              CrankPlace3               *place)
{
  CrankSession3EntityModuleClass *c = CRANK_SESSION3_ENTITY_MODULE_GET_CLASS (module);

  return c->make_place_data (module, place);
}

/**
 * crank_session3_entity_module_attached_data:
 * @module: A Module.
 * @entity: (transfer none): A Entity.
 * @data: (transfer none): Data for @entity.
 *
 * This will be called when data is attached to an entity.
 */
void
crank_session3_entity_module_attached_data (CrankSession3EntityModule *module,
                                            CrankEntity3              *entity,
                                            GObject                   *data)
{
  CrankSession3EntityModuleClass *c = CRANK_SESSION3_ENTITY_MODULE_GET_CLASS (module);

  c->attached_data (module, entity, data);
}

/**
 * crank_session3_entity_module_detached_data:
 * @module: A Module.
 * @entity: (transfer none): A Entity.
 * @data: (transfer none): Data for @entity.
 *
 * This will be called when data is detached from an entity.
 */
void
crank_session3_entity_module_detached_data (CrankSession3EntityModule *module,
                                            CrankEntity3              *entity,
                                            GObject                   *data)
{
  CrankSession3EntityModuleClass *c = CRANK_SESSION3_ENTITY_MODULE_GET_CLASS (module);

  c->detached_data (module, entity, data);
}

/**
 * crank_session3_entity_module_entity_added:
 * @module: A Module.
 * @place: (transfer none): A Place.
 * @entity: (transfer none): A Entity.
 *
 * This will be called when an entity is added to a place. In this function,
 * module can add entity in managed list.
 */
void
crank_session3_entity_module_entity_added (CrankSession3EntityModule *module,
                                           CrankPlace3               *place,
                                           CrankEntity3              *entity)
{
  CrankSession3EntityModuleClass *c = CRANK_SESSION3_ENTITY_MODULE_GET_CLASS (module);

  c->entity_added (module, place, entity);
}

/**
 * crank_session3_entity_module_entity_removed:
 * @module: A Module.
 * @place: (transfer none): A Place.
 * @entity: (transfer none): A Entity.
 *
 * This will be called when an entity is removed from a place. In this function,
 * module can remove entity from managed list.
 */
void
crank_session3_entity_module_entity_removed (CrankSession3EntityModule *module,
                                             CrankPlace3               *place,
                                             CrankEntity3              *entity)
{
  CrankSession3EntityModuleClass *c = CRANK_SESSION3_ENTITY_MODULE_GET_CLASS (module);

  c->entity_removed (module, place, entity);
}

