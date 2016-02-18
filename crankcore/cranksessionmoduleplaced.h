#ifndef CRANKSESSIONMODULEPLACED_H
#define CRANKSESSIONMODULEPLACED_H

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
#error cranksessionmoduleplaced.h cannot included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"


//////// Forward declarations //////////////////////////////////////////////////

typedef struct _CrankPlace CrankPlace;
typedef struct _CrankEntity CrankEntity;


//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SESSION_MODULE_PLACED (crank_session_module_placed_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSessionModulePlaced,
                          crank_session_module_placed,
                          CRANK, SESSION_MODULE_PLACED,
                          CrankCompositable1N)

/**
 * CrankSessionModulePlaced:
 *
 * Instance structure.
 */

/**
 * CrankSessionModulePlacedClass:
 * @place_created: Slot for CrankSessionModulePlaced:place_created
 * @place_disposed: Slot for CrankSessionModulePlaced:place_disposed
 * @entity_created: Slot for CrankSessionModulePlaced:entity_created
 * @entity_disposed: Slot for CrankSessionModulePlaced:entity_disposed
 * @entity_added: Slot for CrankSessionModulePlaced:entity_added
 * @entity_removed: Slot for CrankSessionModulePlaced:entity_removed
 *
 * Virtual function table for #CrankSessionModulePlaced.
 */

struct _CrankSessionModulePlacedClass {
  /*< private >*/
  CrankCompositable1NClass _parent;

  /*< public >*/

  // Place and entity construction/destruction

  void    (*place_created) (CrankSessionModulePlaced *module,
                            CrankPlace               *place);

  void    (*place_disposed)(CrankSessionModulePlaced *module,
                            CrankPlace               *place);

  void    (*entity_created)(CrankSessionModulePlaced *module,
                            CrankEntity              *entity);

  void    (*entity_disposed)(CrankSessionModulePlaced *module,
                             CrankEntity              *entity);

  // Entity addition/removal to places.

  void    (*entity_added)   (CrankSessionModulePlaced *module,
                             CrankPlace               *place,
                             CrankEntity              *entity);

  void    (*entity_removed) (CrankSessionModulePlaced *module,
                             CrankPlace               *place,
                             CrankEntity              *entity);

  // Compositable addition/removal

  void    (*place_added_compositable) (CrankSessionModulePlaced *module,
                                       CrankPlace               *place,
                                       CrankCompositable        *compositable);

  void    (*place_removed_compositable) (CrankSessionModulePlaced *module,
                                         CrankPlace               *place,
                                         CrankCompositable        *compositable);

  void    (*entity_added_compositable) (CrankSessionModulePlaced *module,
                                        CrankEntity              *entity,
                                        CrankCompositable        *compositable);

  void    (*entity_removed_compositable) (CrankSessionModulePlaced *module,
                                          CrankEntity              *entity,
                                          CrankCompositable        *compositable);
};




//////// Constructors //////////////////////////////////////////////////////////

CrankSessionModulePlaced*  crank_session_module_placed_new (const gsize place_base_size,
                                                            const gsize entity_base_size);






//////// Properties ////////////////////////////////////////////////////////////

GType   crank_session_module_placed_get_place_type  (CrankSessionModulePlaced* module);

GType   crank_session_module_placed_get_entity_type (CrankSessionModulePlaced* module);


#endif
