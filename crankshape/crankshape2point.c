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
#include "crankbase.h"
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2polygon.h"

#include "crankshape2point.h"

/**
 * SECTION:crankshape2point
 * @title: CrankShape2Point
 * @short_description: Point Shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This represents a point as a shape.
 */

//////// List of virtual functions /////////////////////////////////////////////

// CrankShape2
static gboolean crank_shape2_point_contains (CrankShape2    *shape,
                                             CrankVecFloat2 *point);

// CrankShape2Finite

static gfloat crank_shape2_point_get_bound_radius (CrankShape2Finite *shape);

// CrankShape2Polygon
static guint    crank_shape2_point_get_nvertices (CrankShape2Polygon *shape);

static void     crank_shape2_point_get_vertex (CrankShape2Polygon *shape,
                                               guint               index,
                                               CrankVecFloat2     *vertex);


//////// Type definition ///////////////////////////////////////////////////////

struct _CrankShape2Point {
  CrankShape2Polygon _parent;
};

G_DEFINE_TYPE (CrankShape2Point,
               crank_shape2_point,
               CRANK_TYPE_SHAPE2_POLYGON)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_point_init (CrankShape2Point *inst)
{
}

static void
crank_shape2_point_class_init (CrankShape2PointClass *c)
{
  CrankShape2Class *c_shape2;
  CrankShape2FiniteClass *c_shape2finite;
  CrankShape2PolygonClass *c_shape2polygon;

  c_shape2 = CRANK_SHAPE2_CLASS (c);

  c_shape2->contains = crank_shape2_point_contains;


  c_shape2finite  = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2finite->get_bound_radius = crank_shape2_point_get_bound_radius;



  c_shape2polygon = CRANK_SHAPE2_POLYGON_CLASS (c);

  c_shape2polygon->get_nvertices = crank_shape2_point_get_nvertices;
  c_shape2polygon->get_vertex = crank_shape2_point_get_vertex;
}

//////// CrankShape2 ///////////////////////////////////////////////////////////

static gboolean
crank_shape2_point_contains (CrankShape2    *shape,
                             CrankVecFloat2 *point)
{
  return (point->x == 0) && (point->y == 0);
}

//////// CrankShape2Finite /////////////////////////////////////////////////////

static gfloat
crank_shape2_point_get_bound_radius (CrankShape2Finite *shape)
{
  return 0.0f;
}

//////// CrankShape2Polygon ////////////////////////////////////////////////////

static guint
crank_shape2_point_get_nvertices (CrankShape2Polygon *shape)
{
  return 1;
}

static void
crank_shape2_point_get_vertex (CrankShape2Polygon *shape,
                               guint index,
                               CrankVecFloat2 *vertex)
{
  crank_vec_float2_init (vertex, 0.0f, 0.0f);
}



//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_shape2_point_new:
 *
 * Constructs a point shape.
 *
 * Returns: (transfer full): A Shape
 */
CrankShape2Point*
crank_shape2_point_new (void)
{
  return (CrankShape2Point*) g_object_new (CRANK_TYPE_SHAPE2_POINT, NULL);
}
