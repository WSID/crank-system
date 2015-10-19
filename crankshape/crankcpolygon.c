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
#include "crankcpolygon.h"

/**
 * SECTION: crankcpolygon
 * @title: CrankCPolygon
 * @short_description: Concrete polygon representation.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This represents non-abstract polygon descriptions, with vertices and segments.
 */

//////// Type definition ///////////////////////////////////////////////////////

struct _CrankCPolygon {
  CrankShape2   _parent_instance;

  // TODO: Fill this things.
};

G_DEFINE_TYPE(CrankCPolygon, crank_cpolygon, CRANK_TYPE_SHAPE2)



//////// List of virtual functions /////////////////////////////////////////////

static CrankCPolygon   *_shape2_approximate_polygon (CrankShape2  *self,
                                                     const gfloat  vdistance);


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_cpolygon_init (CrankCPolygon *self)
{
}

static void
crank_cpolygon_class_init (CrankCPolygonClass *c)
{
  CrankShape2Class*     c_shape2;

  c_shape2 = CRANK_SHAPE2_CLASS(c);

  c_shape2->approximate_polygon = _shape2_approximate_polygon;
}

//////// CrankShape2 ///////////////////////////////////////////////////////////

static CrankCPolygon*
_shape2_approximate_polygon (CrankShape2  *self,
                             const gfloat  vdistance)
{
  // For now, we just return reference to self.
  return (CrankCPolygon*)g_object_ref (self);
}

//////// Public functions //////////////////////////////////////////////////////

