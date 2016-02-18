/* No header guards */

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

/* This header file declares private function.
 * This used only for their friends.
 */

#include <glib.h>
#include <glib-object.h>

#include "cranksession.h"
#include "cranksessionmoduleplaced.h"

#ifndef __GTK_DOC_IGNORE__

G_GNUC_INTERNAL
void      crank_session_module_placed_fini_place (CrankSessionModulePlaced *module,
                                                  CrankPlace               *place);
G_GNUC_INTERNAL
void      crank_session_module_placed_fini_entity (CrankSessionModulePlaced *module,
                                                   CrankEntity              *entity);

G_GNUC_INTERNAL
void      crank_session_module_placed_place_created (CrankSessionModulePlaced *module,
                                                     CrankPlace               *place);

G_GNUC_INTERNAL
void      crank_session_module_placed_entity_created (CrankSessionModulePlaced *module,
                                                      CrankEntity              *entity);


G_GNUC_INTERNAL
void      crank_session_module_placed_place_disposed (CrankSessionModulePlaced *module,
                                                      CrankPlace               *place);

G_GNUC_INTERNAL
void      crank_session_module_placed_entity_disposed (CrankSessionModulePlaced *module,
                                                       CrankEntity              *entity);


G_GNUC_INTERNAL
void      crank_session_module_placed_entity_added (CrankSessionModulePlaced *module,
                                                    CrankPlace               *place,
                                                    CrankEntity              *entity);

G_GNUC_INTERNAL
void      crank_session_module_placed_entity_removed (CrankSessionModulePlaced *module,
                                                      CrankPlace               *place,
                                                      CrankEntity              *entity);


G_GNUC_INTERNAL
void      crank_session_module_placed_place_added_compositable (CrankSessionModulePlaced *module,
                                                                CrankPlace               *place,
                                                                CrankCompositable        *compositable);

G_GNUC_INTERNAL
void      crank_session_module_placed_place_removed_compositable (CrankSessionModulePlaced *module,
                                                                  CrankPlace               *place,
                                                                  CrankCompositable        *compositable);


G_GNUC_INTERNAL
void      crank_session_module_placed_entity_added_compositable (CrankSessionModulePlaced *module,
                                                                 CrankEntity              *entity,
                                                                 CrankCompositable        *compositable);

G_GNUC_INTERNAL
void      crank_session_module_placed_entity_removed_compositable (CrankSessionModulePlaced *module,
                                                                   CrankEntity              *entity,
                                                                   CrankCompositable        *compositable);
#endif
