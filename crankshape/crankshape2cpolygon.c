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
#include "crankshape2cpolygon.h"

/**
 * SECTION: crankshape2cpolygon
 * @title: CrankShape2CPolygon
 * @short_description: Concrete polygon representation.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This represents non-abstract polygon descriptions, with vertices and segments.
 */

//////// Type definition ///////////////////////////////////////////////////////

struct _CrankShape2CPolygon {
  CrankShape2   _parent_instance;
};

G_DEFINE_TYPE(CrankShape2CPolygon,
              crank_shape2_cpolygon,
              CRANK_TYPE_SHAPE2)



//////// List of virtual functions /////////////////////////////////////////////

static CrankShape2CPolygon     *_shape2_approximate_polygon    (CrankShape2  *self,
                                                                const gfloat  vdistance);


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_cpolygon_init (CrankShape2CPolygon *self)
{
}

static void
crank_shape2_cpolygon_class_init (CrankShape2CPolygonClass *c)
{
  CrankShape2Class*     c_shape2;

  c_shape2 = CRANK_SHAPE2_CLASS(c);

  c_shape2->approximate_polygon = _shape2_approximate_polygon;
}

//////// CrankShape2 ///////////////////////////////////////////////////////////

static CrankShape2CPolygon*
_shape2_approximate_polygon (CrankShape2  *self,
                             const gfloat  vdistance)
{
  // For now, we just return reference to self.
  return (CrankShape2CPolygon*)g_object_ref (self);
}

//////// Public functions //////////////////////////////////////////////////////

