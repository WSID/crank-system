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

/* This declares private functions */

#ifndef CRANKCORE_INSIDE
#error crankentity.h cannot included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "cranksessionmoduleplaced.h"

#ifndef __GTK_DOC_IGNORE__

//////// Forward Declarations //////////////////////////////////////////////////

typedef struct _CrankPlace CrankPlace;
typedef struct _CrankEntity CrankEntity;


//////// Private Function for CrankPlace ///////////////////////////////////////

G_GNUC_INTERNAL
void      _crank_entity_place_add_place             (CrankEntity *entity,
                                                     CrankPlace  *place);

G_GNUC_INTERNAL
gboolean  _crank_entity_place_remove_place          (CrankEntity *entity,
                                                     CrankPlace  *place);

G_GNUC_INTERNAL
gboolean  _crank_entity_place_switch_primary_place  (CrankEntity *entity,
                                                     CrankPlace  *place);

G_GNUC_INTERNAL
gboolean  _crank_entity_place_belongs_to            (CrankEntity *entity,
                                                     CrankPlace  *place);

#endif
