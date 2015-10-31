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
#error crankshape2finite.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "crankbox.h"
#include "crankshape2.h"


//////// Type declaration //////////////////////////////////////////////////////
//
#define CRANK_TYPE_SHAPE2_FINITE crank_shape2_finite_get_type ()

G_DECLARE_DERIVABLE_TYPE (CrankShape2Finite,
                          crank_shape2_finite,
                          CRANK, SHAPE2_FINITE,
                          CrankShape2)

/**
 * CrankShape2FiniteClass:
 * @get_bound_radius: Slot for crank_shape2_finite_get_bound_radius()
 *
 * A Virtual function table for the interface.
 */
struct _CrankShape2FiniteClass {
  /*< private >*/
  CrankShape2Class        _parent;

  /*< public >*/
  gfloat      (*get_bound_radius)    (CrankShape2Finite  *shape);


};


//////// Function prototypes ///////////////////////////////////////////////////

gfloat          crank_shape2_finite_get_bound_radius(CrankShape2Finite     *shape);

#endif