#ifndef CRANKCOMPOSITABLE1N_H
#define CRANKCOMPOSITABLE1N_H

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
#error crankcompositable1n.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankcomposite.h"
#include "crankcompositable.h"

G_BEGIN_DECLS
//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_COMPOSITABLE_1N (crank_compositable_1n_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankCompositable1N,
                          crank_compositable_1n,
                          CRANK, COMPOSITABLE_1N,
                          CrankCompositable)

/**
 * CrankCompositable1N:
 *
 * Represents a compositable objects that can be added to one composite at a
 * time.
 */

/**
 * CrankCompositable1NClass:
 *
 * Virtual function table for #CrankCompositable1N.
 */
struct _CrankCompositable1NClass
{
  /*< private >*/
  CrankCompositableClass parent;
};





//////// Public Functions //////////////////////////////////////////////////////

CrankComposite  *crank_compositable_1n_get_composite  (CrankCompositable1N  *compositable);

G_END_DECLS

#endif
