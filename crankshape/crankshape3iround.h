#ifndef CRANKSHAPE3IROUND_H
#define CRANKSHAPE3IROUND_H

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
#error crankshape3iround.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3polyhedron.h"

G_BEGIN_DECLS
//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE3_IROUND crank_shape3_iround_get_type()

G_DECLARE_INTERFACE(CrankShape3IRound,
                    crank_shape3_iround,
                    CRANK, SHAPE3_IROUND,
                    CrankShape3Finite)
/**
 * CrankShape3IRound:
 *
 * A Interface Instance Structure.
 */

/**
 * CrankShape3IRoundInterface:
 * @get_inner_shape: slot for crank_shape2_iround_get_inner_shape()
 * @get_round_radius: slot for crank_shape2_iround_get_round_radius()
 *
 * Virtual function table for #CrankShape3IRound.
 */

struct _CrankShape3IRoundInterface
{
  /*< private >*/
  GTypeInterface _parent;

  /*< public >*/
  CrankShape3Polyhedron* (*get_inner_shape) (CrankShape3IRound *iround);

  gfloat              (*get_round_radius) (CrankShape3IRound *iround);

};



//////// Public functions //////////////////////////////////////////////////////

CrankShape3Polyhedron* crank_shape3_iround_get_inner_shape (CrankShape3IRound *iround);

gfloat              crank_shape3_iround_get_round_radius (CrankShape3IRound *iround);



G_END_DECLS


#endif
