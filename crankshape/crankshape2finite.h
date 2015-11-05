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
 * CrankShape2Finite:
 *
 * Structure represents a finite shape.
 */

/**
 * CrankShape2FiniteClass:
 * @is_convex: Slot for crank_shape2_finite_is_convex()
 * @get_bound_radius: Slot for crank_shape2_finite_get_bound_radius()
 * @approximate_polygon: Slot for crank_shape2_finite_approximate_polygon()
 *
 * A Virtual function table for the interface.
 */
struct _CrankShape2FiniteClass {
  /*< private >*/
  CrankShape2Class        _parent;

  /*< public >*/
  // Geometry property
  gboolean    (*is_convex)             (CrankShape2Finite      *shape);

  // Boundings
  gfloat      (*get_bound_radius)      (CrankShape2Finite      *shape);


  /*< private >*/
  gpointer      _PADDING1;
  gpointer      _PADDING2;
  gpointer      _PADDING3;


  /*< public >*/
  // Reduce to Polygonal shape.

  CrankShape2Polygon *(*approximate_polygon)   (CrankShape2Finite      *shape);

  /*< private >*/
  gpointer      _PADDING5;
  gpointer      _PADDING6;
  gpointer      _PADDING7;

};


//////// Function prototypes ///////////////////////////////////////////////////
gboolean        crank_shape2_finite_is_convex (CrankShape2Finite *shape);


gfloat          crank_shape2_finite_get_bound_radius(CrankShape2Finite     *shape);


CrankShape2Polygon     *crank_shape2_finite_approximate_polygon(CrankShape2Finite *shape);

#endif
