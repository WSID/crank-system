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
                          GObject)

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


//////// Type Functions ////////////////////////////////////////////////////////

void      crank_gtype_compositable_add_requisition        (GType  type,
                                                           GType  req);

gboolean  crank_gtype_compositable_is_required            (GType  type,
                                                           GType  req);


GType    *crank_gtype_compositable_get_req_composite      (GType  type,
                                                           guint *nreq);

GType    *crank_gtype_compositable_get_req_compositable   (GType  type,
                                                           guint *nreq);

GType    *crank_gtype_compositable_get_requisitions       (GType  type,
                                                           guint *nreq);




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
