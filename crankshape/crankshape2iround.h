#ifndef CRANKSHAPE2IROUND_H
#define CRANKSHAPE2IROUND_H

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
#error crankshape2iround.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2polygon.h"

G_BEGIN_DECLS
//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE2_IROUND crank_shape2_iround_get_type()

G_DECLARE_INTERFACE(CrankShape2IRound,
                    crank_shape2_iround,
                    CRANK, SHAPE2_IROUND,
                    CrankShape2Finite)
/**
 * CrankShape2IRound:
 *
 * A Interface Instance Structure.
 */

/**
 * CrankShape2IRoundInterface:
 * @get_inner_shape: slot for crank_shape2_iround_get_inner_shape()
 * @get_round_radius: slot for crank_shape2_iround_get_round_radius()
 *
 * Virtual function table for #CrankShape2IRound.
 */

struct _CrankShape2IRoundInterface
{
  /*< private >*/
  GTypeInterface _parent;

  /*< public >*/
  CrankShape2Polygon* (*get_inner_shape) (CrankShape2IRound *iround);

  gfloat              (*get_round_radius) (CrankShape2IRound *iround);

};



//////// Public functions //////////////////////////////////////////////////////

CrankShape2Polygon* crank_shape2_iround_get_inner_shape (CrankShape2IRound *iround);

gfloat              crank_shape2_iround_get_round_radius (CrankShape2IRound *iround);



G_END_DECLS


#endif
