#ifndef CRANKSESSION3ENTITYMODULE_H
#define CRANKSESSION3ENTITYMODULE_H

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

#ifndef CRANKCORE_INSIDE
#error cranksession3entitymodule.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession3.h"
#include "cranksession3module.h"

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SESSION3_ENTITY_MODULE (crank_session3_entity_module_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSession3EntityModule,
                          crank_session3_entity_module,
                          CRANK, SESSION3_ENTITY_MODULE,
                          CrankSession3Module)

/**
 * CrankSession3EntityModuleClass:
 * @make_place_data: Slot for crank_session3_entity_module_make_place_data().
 * @attached_data: Slot for crank_session3_entity_module_attached_data().
 * @detached_data: Slot for crank_session3_entity_module_detached_data().
 * @entity_added: Slot for crank_session3_entity_module_entity_added().
 * @entity_removed: Slot for crank_session3_entity_module_entity_removed().
 *
 * Virtual function table for #CrankSession3Module.
 */
struct _CrankSession3EntityModuleClass {
  /*< private >*/
  CrankSession3ModuleClass parent;

  /*< public >*/
  GObject *(*make_place_data) (CrankSession3EntityModule *module,
                               CrankPlace3               *place);

  void (*attached_data) (CrankSession3EntityModule *module,
                         CrankEntity3              *entity,
                         GObject                   *data);


  void (*detached_data) (CrankSession3EntityModule *module,
                         CrankEntity3              *entity,
                         GObject                   *data);

  void (*entity_added) (CrankSession3EntityModule *module,
                        CrankPlace3               *place,
                        CrankEntity3              *entity);

  void (*entity_removed) (CrankSession3EntityModule *module,
                          CrankPlace3               *place,
                          CrankEntity3              *entity);
};

//////// Public functions //////////////////////////////////////////////////////

guint     crank_session3_entity_module_get_index (CrankSession3EntityModule *module);

guint     crank_session3_entity_module_get_place_index (CrankSession3EntityModule *module);

GObject  *crank_session3_entity_module_get_place_data (CrankSession3EntityModule *module,
                                                       CrankPlace3               *place);

GObject  *crank_session3_entity_module_get_entity_data (CrankSession3EntityModule *module,
                                                        CrankEntity3              *entity);


GObject  *crank_session3_entity_module_make_place_data (CrankSession3EntityModule *module,
                                                        CrankPlace3               *place);


void      crank_session3_entity_module_attached_data (CrankSession3EntityModule *module,
                                                      CrankEntity3              *entity,
                                                      GObject                   *data);

void      crank_session3_entity_module_detached_data (CrankSession3EntityModule *module,
                                                      CrankEntity3              *entity,
                                                      GObject                   *data);

void      crank_session3_entity_module_entity_added (CrankSession3EntityModule *module,
                                                     CrankPlace3               *place,
                                                     CrankEntity3              *entity);

void      crank_session3_entity_module_entity_removed(CrankSession3EntityModule *module,
                                                     CrankPlace3               *place,
                                                     CrankEntity3              *entity);

#endif 
