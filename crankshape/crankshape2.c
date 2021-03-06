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

#define _CRANKSHAPE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankshape2.h"

/**
 * SECTION: crankshape2
 * @title: CrankShape2
 * @short_description: Base class for 2 dimsensional shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This class is base class for 2 dimensional shapes without separated parts.
 *
 * # Abstract functions
 *
 * * #CrankShape2Class.contains()
 * * #CrankShape2Class.finitize()
 */

//////// Type definition ///////////////////////////////////////////////////////
//
G_DEFINE_ABSTRACT_TYPE (CrankShape2, crank_shape2, G_TYPE_OBJECT)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_init (CrankShape2 *self)
{
}

static void
crank_shape2_class_init (CrankShape2Class *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
}


//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_shape2_contains:
 * @shape: A Shape.
 * @point: A Point.
 *
 * Checks @shape is containing @point.
 *
 * Returns: Whether the @point contains @shape.
 */
gboolean
crank_shape2_contains (CrankShape2    *shape,
                       CrankVecFloat2 *point)
{
  CrankShape2Class *c;

  c = CRANK_SHAPE2_GET_CLASS (shape);

  return c->contains (shape, point);
}


/**
 * crank_shape2_finitize:
 * @shape: A Shape.
 * @box: A Finite box
 *
 * Gets a finite part of shape that usable with @box.
 *
 * Returns: (transfer full) (element-type CrankShape2Finite):
 *      Finite parts of shape.
 */
GList*
crank_shape2_finitize (CrankShape2 *shape,
                       CrankBox2   *box)
{
  CrankShape2Class *c;

  c = CRANK_SHAPE2_GET_CLASS (shape);

  return c->finitize (shape, box);
}
