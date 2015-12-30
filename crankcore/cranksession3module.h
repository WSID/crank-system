#ifndef CRANKSESSION3MODULE_H
#define CRANKSESSION3MODULE_H

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
#error cranksession3module.h cannot be included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"
#include "cranksession3.h"

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SESSION3_MODULE (crank_session3_module_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSession3Module,
                          crank_session3_module,
                          CRANK, SESSION3_MODULE,
                          GObject)


#define CRANK_TYPE_SESSION3_PLACE_MODULE (crank_session3_place_module_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSession3PlaceModule,
                          crank_session3_place_module,
                          CRANK, SESSION3_PLACE_MODULE,
                          CrankSession3Module)


#define CRANK_TYPE_SESSION3_ENTITY_MODULE (crank_session3_entity_module_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSession3EntityModule,
                          crank_session3_entity_module,
                          CRANK, SESSION3_ENTITY_MODULE,
                          CrankSession3Module)


struct _CrankSession3ModuleClass {
  GObjectClass parent;

  void    (*session_init) (CrankSession3Module *module,
                           CrankSession3       *session,
                           GError             **error);

  void    (*tick) (CrankSession3Module *module);
};

struct _CrankSession3PlaceModuleClass {
  CrankSession3ModuleClass parent;

  void (*attached_data) (CrankSession3PlaceModule *module,
                         CrankPlace3              *place,
                         GObject                  *data);


  void (*detached_data) (CrankSession3PlaceModule *module,
                         CrankPlace3              *place,
                         GObject                  *data);
};


struct _CrankSession3EntityModuleClass {
  CrankSession3ModuleClass parent;

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

//////// Virtual functions /////////////////////////////////////////////////////

void      crank_session3_module_session_init (CrankSession3Module  *module,
                                              CrankSession3        *session,
                                              GError              **error);


void      crank_session3_module_tick (CrankSession3Module *module);

void      crank_session3_place_module_attached_data (CrankSession3PlaceModule *module,
                                                     CrankPlace3              *place,
                                                     GObject                  *data);

void      crank_session3_place_module_detached_data (CrankSession3PlaceModule *module,
                                                     CrankPlace3              *place,
                                                     GObject                  *data);


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
