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

typedef struct _CrankSession3PlaceModule CrankSession3PlaceModule;
typedef struct _CrankSession3EntityModule CrankSession3EntityModule;


//////// Type Definition ///////////////////////////////////////////////////////

#define CRANK_TYPE_SESSION3 (crank_session3_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSession3,
                          crank_session3,
                          CRANK, SESSION3,
                          CrankSession)

struct _CrankSession3Class {
  CrankSessionClass parent;
};



typedef struct _CrankPlace3 CrankPlace3;
typedef struct _CrankEntity3 CrankEntity3;

/**
 * CrankPlace3:
 * @object: (transfer none): A #GObject that place belongs to.
 * @boundary: Boundary box for place.
 * @entities: Entities in the place.
 * @misc: Additional Information for session systems.
 *
 * Represents 3D space that entities are taking place.
 */
struct _CrankPlace3 {
  CrankSession3 *session;
  GObject       *object;

  CrankBox3 boundary;

  GPtrArray *entities;

  gpointer misc[];
};


/**
 * CrankEntity3:
 * @object: (transfer none): A #GObject that entity belongs to.
 * @place: Place that the entity take place in.
 * @pos: Position of entity.
 * @misc: Additional Information for session systems.
 */
struct _CrankEntity3 {
  CrankSession3 *session;
  GObject       *object;

  CrankPlace3 *place;
  CrankTrans3  pos;

  gpointer misc[];
};

//////// Public functions //////////////////////////////////////////////////////

void    crank_session3_add_entity_module (CrankSession3       *session,
                                          CrankSession3EntityModule *module);

void    crank_session3_remove_entity_module (CrankSession3             *session,
                                             CrankSession3EntityModule *module);

gint    crank_session3_index_of_entity_module (CrankSession3       *session,
                                               CrankSession3EntityModule *module);


void    crank_session3_lock_and_init_modules (CrankSession3 *session);



CrankPlace3    *crank_session3_make_place (CrankSession3 *session);

CrankEntity3   *crank_session3_make_entity (CrankSession3 *session);


void            crank_session3_dispose_place (CrankSession3 *session,
                                              CrankPlace3   *place);

void            crank_session3_dispose_entity (CrankSession3 *session,
                                               CrankEntity3  *entity);
#endif
