#ifndef CRANKENTITY_H
#define CRANKENTITY_H

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
#error crankentity.h cannot included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "cranksessionmoduleplaced.h"

G_BEGIN_DECLS

//////// Forward declarations //////////////////////////////////////////////////

typedef struct _CrankPlace CrankPlace;


//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_ENTITY (crank_entity_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankEntity,
                          crank_entity,
                          CRANK, ENTITY,
                          CrankComposite)

/**
 * CrankEntity:
 *
 * Represents an entity object.
 */

/**
 * CrankEntityClass:
 *
 * Virtual function table for #CrankEntity.
 */
struct _CrankEntityClass
{
  /*< private >*/
  CrankCompositeClass _parent;
};






//////// Public functions //////////////////////////////////////////////////////

CrankSessionModulePlaced *crank_entity_get_module (CrankEntity *entity);

CrankPlace *crank_entity_get_primary_place (CrankEntity *entity);

guint       crank_entity_get_nplaces       (CrankEntity *entity);

gboolean    crank_entity_is_placeless      (CrankEntity *entity);



//////// Places ////////////////////////////////////////////////////////////////

CrankPlace *crank_entity_get_place         (CrankEntity *entity,
                                            const guint  index);

gint        crank_entity_index_of_place    (CrankEntity *entity,
                                            CrankPlace  *place);

G_END_DECLS

#endif
