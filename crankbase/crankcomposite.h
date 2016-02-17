#ifndef CRANKCOMPOSITE_H
#define CRANKCOMPOSITE_H

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
#error crankcomposite.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

//////// Forward Declarations //////////////////////////////////////////////////

typedef struct _CrankCompositable CrankCompositable;


//////// Error Declarations ////////////////////////////////////////////////////
/**
 * CRANK_COMPOSITE_ERROR:
 *
 * Error domain for #CrankComposite.
 */
#define CRANK_COMPOSITE_ERROR crank_composite_error_quark ()
GQuark  crank_composite_error_quark (void);

/**
 * CrankCompositeError:
 * @CRANK_COMPOSITE_ERROR_REJECTED:
 *   The composite or compositable rejected.
 * @CRANK_COMPOSITE_ERROR_REQ_NOT_MEET:
 *   The requisition of compostable, is not met.
 * @CRANK_COMPOSITE_ERROR_NOT_HAVE_COMPOSITABLE:
 *   The compositable is not in the composite.
 * @CRANK_COMPOSITE_ERROR_ALREADY_HAS_COMPOSITE:
 *   The compositable accepts one composite, and already has composite.
 * @CRANK_COMPOSITE_ERROR_ALREADY_HAS_COMPOSITABLE:
 *   The composite already has a type of compositable, and should not be two or
 *   more of them.
 *
 * Represents error codes for #CrankComposite.
 */
typedef enum _CrankCompositeError
{
  CRANK_COMPOSITE_ERROR_REJECTED,
  CRANK_COMPOSITE_ERROR_REQ_NOT_MEET,
  CRANK_COMPOSITE_ERROR_NOT_HAVE_COMPOSITABLE,
  CRANK_COMPOSITE_ERROR_ALREADY_HAS_COMPOSITE,
  CRANK_COMPOSITE_ERROR_ALREADY_HAS_COMPOSITABLE
} CrankCompositeError;


//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_COMPOSITE (crank_composite_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankComposite,
                          crank_composite,
                          CRANK, COMPOSITE,
                          GObject)

/**
 * CrankComposite:
 *
 * Represents a composite object.
 */

/**
 * CrankCompositeClass:
 * @add_compositable: Slot for crank_composite_add_compositable()
 * @remove_compositable: Slot for crank_composite_remove_compositable()
 *
 * Virtual function table for #CrankComposite.
 */
struct _CrankCompositeClass
{
  /*< private >*/
  GObjectClass parent;

  /*< public >*/
  gboolean  (*add_compositable)       (CrankComposite     *composite,
                                       CrankCompositable  *compositable,
                                       GError            **error);

  gboolean  (*remove_compositable)    (CrankComposite     *composite,
                                       CrankCompositable  *compositable,
                                       GError            **error);
  /*< private >*/
  gpointer _DUMMY2;
  gpointer _DUMMY3;
};


//////// Public Functions //////////////////////////////////////////////////////

//////// Compositable add / remove /////////////////////////////////////////////

gboolean    crank_composite_add_compositable    (CrankComposite     *composite,
                                                 CrankCompositable  *compositable,
                                                 GError            **error);

gboolean    crank_composite_remove_compositable (CrankComposite     *composite,
                                                 CrankCompositable  *compositable,
                                                 GError            **error);


//////// Compositable getting //////////////////////////////////////////////////

CrankCompositable *crank_composite_get_compositable           (CrankComposite *composite,
                                                               const guint     index);

CrankCompositable *crank_composite_get_compositable_by_gtype  (CrankComposite *composite,
                                                               const GType     type);

guint              crank_composite_get_ncompositables         (CrankComposite *composite);


gboolean    crank_composite_contains_compositable   (CrankComposite    *composite,
                                                     CrankCompositable *compositable);


void        crank_composite_foreach_compositable    (CrankComposite    *composite,
                                                     GFunc              func,
                                                     gpointer           userdata);






G_END_DECLS

#endif 
