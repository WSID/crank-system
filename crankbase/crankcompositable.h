#ifndef CRANKCOMPOSITABLE_H
#define CRANKCOMPOSITABLE_H

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

#ifndef _CRANKBASE_INSIDE
#error crankcompositable.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankcomposite.h"

G_BEGIN_DECLS
//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_COMPOSITABLE (crank_compositable_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankCompositable,
                          crank_compositable,
                          CRANK, COMPOSITABLE,
                          GInitiallyUnowned)

/**
 * CrankCompositable:
 *
 * Represents a compositable objects that can be added to composite object.
 */

/**
 * CrankCompositableClass:
 * @adding: Slot for crank_compositable_adding()
 * @removing: Slot for crank_compositable_removing()
 *
 * Virtual function table for #CrankCompositable.
 */
struct _CrankCompositableClass
{
  /*< private >*/
  GObjectClass parent;

  /*< public >*/
  gboolean  (*adding)                 (CrankCompositable  *compositable,
                                       CrankComposite     *composite,
                                       GError            **error);

  gboolean  (*removing)               (CrankCompositable  *compositable,
                                       CrankComposite     *composite,
                                       GError            **error);

  /*< private >*/
  gpointer _DUMMY2;
  gpointer _DUMMY3;
};









//////// Class Functions ///////////////////////////////////////////////////////

void      crank_compositable_class_add_requisition     (CrankCompositableClass *c,
                                                        const GType             req);

gboolean  crank_compositable_class_is_required         (CrankCompositableClass *c,
                                                        const GType             req);

GType    *crank_compositable_class_get_req_composite   (CrankCompositableClass *c,
                                                        guint                  *nreq);

GType    *crank_compositable_class_get_req_compositable(CrankCompositableClass *c,
                                                        guint                  *nreq);

GType    *crank_compositable_class_get_requisitions    (CrankCompositableClass *c,
                                                        guint                  *nreq);





//////// Public Functions //////////////////////////////////////////////////////

//////// Compositable Adding / Removing ////////////////////////////////////////

gboolean    crank_compositable_adding           (CrankCompositable  *compositable,
                                                 CrankComposite     *composite,
                                                 GError            **error);

gboolean    crank_compositable_removing         (CrankCompositable  *compositable,
                                                 CrankComposite     *composite,
                                                 GError            **error);

G_END_DECLS

#endif 
