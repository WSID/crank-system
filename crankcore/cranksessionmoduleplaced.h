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
#include "cranksessionmodule.h"


//////// Forward declarations //////////////////////////////////////////////////

typedef struct _CrankPlaceBase CrankPlaceBase;
typedef struct _CrankEntityBase CrankEntityBase;


//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SESSION_MODULE_PLACED (crank_session_module_placed_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSessionModulePlaced,
                          crank_session_module_placed,
                          CRANK, SESSION_MODULE_PLACED,
                          CrankSessionModule)

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
  CrankSessionModuleClass _parent;

  /*< public >*/
  void    (*place_created) (CrankSessionModulePlaced *module,
                            CrankPlaceBase           *place);

  void    (*place_disposed)(CrankSessionModulePlaced *module,
                            CrankPlaceBase           *place);

  void    (*entity_created)(CrankSessionModulePlaced *module,
                            CrankEntityBase          *entity);

  void    (*entity_disposed)(CrankSessionModulePlaced *module,
                             CrankEntityBase          *entity);

  void    (*entity_added)   (CrankSessionModulePlaced *module,
                             CrankPlaceBase           *place,
                             CrankEntityBase          *entity);

  void    (*entity_removed) (CrankSessionModulePlaced *module,
                             CrankPlaceBase           *place,
                             CrankEntityBase          *entity);
};




//////// Constructors //////////////////////////////////////////////////////////

CrankSessionModulePlaced*  crank_session_module_placed_new (const gsize place_base_size,
                                                            const gsize entity_base_size);


//////// Properties ////////////////////////////////////////////////////////////

gsize       crank_session_module_placed_get_place_base_size (CrankSessionModulePlaced *module);

gsize       crank_session_module_placed_get_entity_base_size (CrankSessionModulePlaced *module);


gsize       crank_session_module_placed_get_place_size (CrankSessionModulePlaced *module);



gsize       crank_session_module_placed_get_entity_size (CrankSessionModulePlaced* module);



//////// Attaching allocations /////////////////////////////////////////////////

guint       crank_session_module_placed_attach_place_alloc_full (CrankSessionModulePlaced *module,
                                                                 const gsize               size,
                                                                 GFunc                     fini,
                                                                 gpointer                  fini_userdata,
                                                                 GDestroyNotify            fini_destroy,
                                                                 goffset                  *offset);

guint       crank_session_module_placed_attach_place_alloc (CrankSessionModulePlaced *module,
                                                            const gsize               size,
                                                            GDestroyNotify            fini,
                                                            goffset                  *offset);

guint       crank_session_module_placed_attach_place_alloc_pointer (CrankSessionModulePlaced *module,
                                                                    GDestroyNotify            fini,
                                                                    goffset                  *offset);

guint       crank_session_module_placed_attach_place_alloc_boxed (CrankSessionModulePlaced *module,
                                                                  const GType               btype,
                                                                  goffset                  *offset);

guint       crank_session_module_placed_attach_place_alloc_object (CrankSessionModulePlaced *module,
                                                                   goffset                  *offset);





guint       crank_session_module_placed_attach_entity_alloc_full (CrankSessionModulePlaced *module,
                                                                  const gsize               size,
                                                                  GFunc                     fini,
                                                                  gpointer                  fini_userdata,
                                                                  GDestroyNotify            fini_destroy,
                                                                  goffset                  *offset);

guint       crank_session_module_placed_attach_entity_alloc (CrankSessionModulePlaced *module,
                                                             const gsize               size,
                                                             GDestroyNotify            fini,
                                                             goffset                  *offset);

guint       crank_session_module_placed_attach_entity_alloc_pointer (CrankSessionModulePlaced *module,
                                                                     GDestroyNotify            fini,
                                                                     goffset                  *offset);

guint       crank_session_module_placed_attach_entity_alloc_boxed (CrankSessionModulePlaced *module,
                                                                   const GType               btype,
                                                                   goffset                  *offset);

guint       crank_session_module_placed_attach_entity_alloc_object (CrankSessionModulePlaced *module,
                                                                    goffset                  *offset);


//////// Allocations ///////////////////////////////////////////////////////////

goffset     crank_session_module_placed_get_place_alloc_offset (CrankSessionModulePlaced *module,
                                                                const guint               ticket);

gsize       crank_session_module_placed_get_place_alloc_size (CrankSessionModulePlaced *module,
                                                              const guint               ticket);

goffset     crank_session_module_placed_get_entity_alloc_offset (CrankSessionModulePlaced *module,
                                                                 const guint               ticket);

goffset     crank_session_module_placed_get_entity_alloc_size (CrankSessionModulePlaced *module,
                                                               const guint               ticket);


#endif
