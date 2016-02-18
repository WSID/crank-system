#ifndef CRANKPLACE_H
#define CRANKPLACE_H

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
#error crankplace.h cannot included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "cranksessionmoduleplaced.h"

G_BEGIN_DECLS

//////// Forward declarations //////////////////////////////////////////////////

typedef struct _CrankEntity CrankEntity;


//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_PLACE (crank_place_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankPlace,
                          crank_place,
                          CRANK, PLACE,
                          CrankComposite)

/**
 * CrankPlace:
 *
 * Represents a place object.
 */

/**
 * CrankPlaceClass:
 *
 * Virtual function table for #CrankPlace.
 */
struct _CrankPlaceClass
{
  /*< private >*/
  CrankCompositeClass _parent;
};




//////// Public functions //////////////////////////////////////////////////////

CrankSessionModulePlaced *crank_place_get_module (CrankPlace *place);

guint   crank_place_get_nentities (CrankPlace *place);



//////// Entiites //////////////////////////////////////////////////////////////

gboolean  crank_place_add_entity (CrankPlace *place,
                                  CrankEntity *entity);

gboolean  crank_place_remove_entity (CrankPlace  *place,
                                     CrankEntity *entity);

gboolean  crank_place_contains_entity (CrankPlace  *place,
                                       CrankEntity *entity);

void      crank_place_foreach_entity (CrankPlace *place,
                                      GFunc       func,
                                      gpointer    userdata);


G_END_DECLS

#endif
