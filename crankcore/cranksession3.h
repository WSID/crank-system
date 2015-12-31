#ifndef CRANKPLACE3_H
#define CRANKPLACE3_H

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
#error crankplace3.h cannot be included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"


//////// Forward Declaration ///////////////////////////////////////////////////

typedef struct _CrankSession3Module CrankSession3Module;
typedef struct _CrankSession3PlaceModule CrankSession3PlaceModule;
typedef struct _CrankSession3EntityModule CrankSession3EntityModule;


//////// Type Definition ///////////////////////////////////////////////////////

#define CRANK_TYPE_SESSION3 (crank_session3_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSession3,
                          crank_session3,
                          CRANK, SESSION3,
                          CrankSession)

/**
 * CrankSession3Class:
 *
 * Virtual function table for #CrankSession3.
 */
struct _CrankSession3Class {
  /*< private >*/
  CrankSessionClass parent;
};



typedef struct _CrankPlace3 CrankPlace3;
typedef struct _CrankEntity3 CrankEntity3;

/**
 * CrankPlace3:
 *
 * Represents 3D space that entities are taking place.
 */

/**
 * CrankEntity3:
 *
 * Represents an entity.
 */


//////// Public functions //////////////////////////////////////////////////////

void    crank_session3_add_place_module (CrankSession3            *session,
                                         CrankSession3PlaceModule *module);

void    crank_session3_remove_place_module (CrankSession3            *session,
                                            CrankSession3PlaceModule *module);

gint    crank_session3_index_of_place_module (CrankSession3            *session,
                                              CrankSession3PlaceModule *module);

guint   crank_session3_get_n_place_modules (CrankSession3 *session);

CrankSession3PlaceModule *crank_session3_get_place_module (CrankSession3 *session,
                                                           const guint    index);

const GPtrArray *crank_session3_get_place_modules (CrankSession3 *session);




void    crank_session3_add_entity_module (CrankSession3       *session,
                                          CrankSession3EntityModule *module);

void    crank_session3_remove_entity_module (CrankSession3             *session,
                                             CrankSession3EntityModule *module);

gint    crank_session3_index_of_entity_module (CrankSession3             *session,
                                               CrankSession3EntityModule *module);

guint   crank_session3_get_n_entity_modules (CrankSession3 *session);

CrankSession3EntityModule *crank_session3_get_entity_module (CrankSession3 *session,
                                                             const guint    index);

const GPtrArray *crank_session3_get_entity_modules (CrankSession3 *session);



void    crank_session3_lock_and_init_modules (CrankSession3        *session,
                                              GError              **error);



void    crank_session3_set_tick_interval (CrankSession3 *session,
                                          guint          interval);

guint   crank_session3_get_tick_interval (CrankSession3 *session);




CrankPlace3    *crank_session3_make_place (CrankSession3 *session);

CrankEntity3   *crank_session3_make_entity (CrankSession3 *session);


void            crank_place3_dispose (CrankPlace3 *place);

void            crank_entity3_dispose (CrankEntity3 *entity);



CrankSession3  *crank_place3_get_session (CrankPlace3 *place);

GObject        *crank_place3_get_object (CrankPlace3 *place);

void            crank_place3_set_object (CrankPlace3 *place,
                                         GObject     *object);

void            crank_place3_get_boundary (CrankPlace3 *place,
                                           CrankBox3   *boundary);

void            crank_place3_set_boundary (CrankPlace3 *place,
                                           CrankBox3   *boundary);

const GPtrArray*crank_place3_get_entities (CrankPlace3 *place);



void            crank_place3_attach_data (CrankPlace3 *place,
                                          const guint  index,
                                          GObject     *data);

void            crank_place3_detach_data (CrankPlace3 *place,
                                          const guint  index);

GObject        *crank_place3_get_data (CrankPlace3 *place,
                                       const guint  index);

GObject        *crank_place3_get_entity_data (CrankPlace3 *place,
                                              const guint  index);


CrankSession3  *crank_entity3_get_session (CrankEntity3 *entity);

GObject        *crank_entity3_get_object (CrankEntity3 *entity);

void            crank_entity3_set_object (CrankEntity3 *entity,
                                          GObject      *object);

CrankPlace3    *crank_entity3_get_place (CrankEntity3 *entity);

void            crank_entity3_get_position (CrankEntity3 *entity,
                                            CrankTrans3  *pos);

void            crank_entity3_set_position (CrankEntity3 *entity,
                                            CrankTrans3  *pos);


void            crank_entity3_attach_data (CrankEntity3 *entity,
                                           const guint   index,
                                           GObject      *data);

void            crank_entity3_detach_data (CrankEntity3 *entity,
                                           const guint   index);

GObject        *crank_entity3_get_data (CrankEntity3 *entity,
                                        const guint   index);
#endif
