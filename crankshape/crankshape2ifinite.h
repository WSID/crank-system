#ifndef CRANKSHAPE2IFINITE_H
#define CRANKSHAPE2IFINITE_H

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

#ifndef _CRANKSHAPE_INSIDE
#error crankshape2ifinite.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "crankbox.h"
#include "crankshape2.h"


//////// Type declaration //////////////////////////////////////////////////////
//
#define CRANK_TYPE_SHAPE2_IFINITE crank_shape2_ifinite_get_type ()

G_DECLARE_INTERFACE (CrankShape2IFinite,
                     crank_shape2_ifinite,
                     CRANK, SHAPE2_IFINITE,
                     CrankShape2)

/**
 * CrankShape2IFiniteInterface:
 * @get_bradius: Slot for crank_shape2_ifinite_get_bradius()
 * @get_aabb: Slot for crank_shape2_ifinite_get_aabb()
 * @get_obb: Slot for crank_shape2_ifinite_get_obb()
 *
 * A Virtual function table for the interface.
 */
struct _CrankShape2IFiniteInterface {
  /*< private >*/
  GTypeInterface        _interface;

  /*< public >*/
  gfloat      (*get_bradius)    (CrankShape2IFinite  *shape);

  void        (*get_aabb)      (CrankShape2IFinite  *shape,
                                const gfloat         rot,
                                CrankBox2           *aabb);

  void        (*get_obb)       (CrankShape2IFinite  *shape,
                                CrankBox2           *obb);
};


//////// Function prototypes ///////////////////////////////////////////////////

gfloat          crank_shape2_ifinite_get_bradius(CrankShape2IFinite     *shape);

void            crank_shape2_ifinite_get_aabb  (CrankShape2IFinite     *shape,
                                                const gfloat            rot,
                                                CrankBox2              *aabb);

void            crank_shape2_ifinite_get_obb   (CrankShape2IFinite     *shape,
                                                CrankBox2              *obb);

#endif
