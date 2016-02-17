#ifndef CRANKSHAPE3FINITE_H
#define CRANKSHAPE3FINITE_H

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
#error crankshape3finite.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankbox.h"
#include "cranktrans.h"


G_BEGIN_DECLS

//////// Forward declarations //////////////////////////////////////////////////
typedef struct _CrankShape3Vertexed CrankShape3Vertexed;


//////// Type Definition ///////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE3_FINITE crank_shape3_finite_get_type()

G_DECLARE_DERIVABLE_TYPE (CrankShape3Finite,
                          crank_shape3_finite,
                          CRANK, SHAPE3_FINITE,
                          CrankShape3)

/**
 * CrankShape3Finite:
 *
 * Shape Structure representation.
 */

/**
 * CrankShape3FiniteClass:
 * @is_convex: Slot for crank_shape3_finite_is_convex().
 * @get_bound_radius: Slot for crank_shape3_finite_get_bound_radius().
 * @approximate_vertexed: Slot for crank_shape3_finite_approximate_vertexed().
 *
 * Virtual function table for #CrankShape3Finite
 */
struct _CrankShape3FiniteClass {
  /*< private >*/
  CrankShape3Class      _parent;

  /*< public >*/
  gboolean    (*is_convex)             (CrankShape3Finite      *shape);

  gfloat      (*get_bound_radius)      (CrankShape3Finite      *shape);

  /*< private >*/

  gpointer      _PADDING2;

  gpointer      _PADDING3;


  /*< public >*/
  CrankShape3Vertexed *(*approximate_vertexed)      (CrankShape3Finite      *shape);

  /*< private >*/
  gpointer      _PADDING5;

  gpointer      _PADDING6;

  gpointer      _PADDING7;
};

//////// Property getter / setters /////////////////////////////////////////////

gboolean        crank_shape3_finite_is_convex  (CrankShape3Finite              *shape);

gfloat          crank_shape3_finite_get_bound_radius (CrankShape3Finite        *shape);

CrankShape3Vertexed *crank_shape3_finite_approximate_vertexed (CrankShape3Finite *shape);


G_END_DECLS

#endif
