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

#include <math.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankbox.h"
#include "cranktrans.h"
#include "crankrotation.h"
#include "crankshapemisc.h"

#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2vertexed.h"
#include "crankshape2polygon.h"
#include "crankshape2triangle.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polygon.h"
#include "crankshape3triangle.h"

/**
 * SECTION:crankshape3triangle
 * @title: CrankShape3Triangle
 * @short_description: Triangle shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Represents a triangle shape.
 */

//////// List of virtual functions /////////////////////////////////////////////

// CrankShape3
static gboolean crank_shape3_triangle_contains (CrankShape3    *shape,
                                               CrankVecFloat3 *point);

// CrankShape3Finite
static gboolean crank_shape3_triangle_is_convex (CrankShape3Finite *shape);

static gfloat   crank_shape3_triangle_get_bound_radius (CrankShape3Finite *shape);


// CrankShape3Vertexed
static guint    crank_shape3_triangle_get_nvertices (CrankShape3Vertexed *shape);

// CrankShape2Polygon
static CrankWinding crank_shape3_triangle_get_winding (CrankShape3Polygon *shape);

static void     crank_shape3_triangle_get_vertex_pos2 (CrankShape3Polygon *shape,
                                                     guint                vid,
                                                     CrankVecFloat2      *pos);


//////// Type Definition ///////////////////////////////////////////////////////

/**
 * CrankShape3Triangle:
 *
 * Structure represents a segment shape.
 */
struct _CrankShape3Triangle {
  CrankShape3Polygon _parent;

  CrankWinding   wind;
  CrankVecFloat2 vertices[3];
};

G_DEFINE_TYPE (CrankShape3Triangle,
               crank_shape3_triangle,
               CRANK_TYPE_SHAPE3_POLYGON)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_triangle_init (CrankShape3Triangle *inst)
{
}

static void
crank_shape3_triangle_class_init (CrankShape3TriangleClass *c)
{
  CrankShape3Class *c_shape3;
  CrankShape3FiniteClass *c_shape3finite;
  CrankShape3VertexedClass *c_shape3vertexed;
  CrankShape3PolygonClass *c_shape3polygon;

  c_shape3 = CRANK_SHAPE3_CLASS (c);

  c_shape3->contains = crank_shape3_triangle_contains;


  c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);

  c_shape3finite->is_convex = crank_shape3_triangle_is_convex;
  c_shape3finite->get_bound_radius = crank_shape3_triangle_get_bound_radius;


  c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);

  c_shape3vertexed->get_nvertices = crank_shape3_triangle_get_nvertices;


  c_shape3polygon = CRANK_SHAPE3_POLYGON_CLASS (c);

  c_shape3polygon->get_winding = crank_shape3_triangle_get_winding;
  c_shape3polygon->get_vertex_pos2 = crank_shape3_triangle_get_vertex_pos2;
}


//////// CrankShape2 ///////////////////////////////////////////////////////////

static gboolean
crank_shape3_triangle_contains (CrankShape3    *shape,
                                CrankVecFloat3 *point)
{
  CrankShape3Triangle *tri = CRANK_SHAPE3_TRIANGLE (shape);

  return crank_tri_contains (tri->vertices, (CrankVecFloat2*)point) &&
         (point->z == 0);
}




//////// CrankShape2Finite /////////////////////////////////////////////////////

static gboolean
crank_shape3_triangle_is_convex (CrankShape3Finite *shape)
{
  return TRUE;
}


static gfloat
crank_shape3_triangle_get_bound_radius (CrankShape3Finite *shape)
{
  CrankShape3Triangle *tri = CRANK_SHAPE3_TRIANGLE (shape);
  gfloat rad[3];

  rad[0] = crank_vec_float2_get_magn_sq (tri->vertices + 0);
  rad[1] = crank_vec_float2_get_magn_sq (tri->vertices + 1);
  rad[2] = crank_vec_float2_get_magn_sq (tri->vertices + 2);

  rad[0] = MAX (rad[0], rad[1]);
  rad[0] = MAX (rad[0], rad[2]);

  return sqrtf (rad[0]);
}




//////// CrankShape2Vertexed ////////////////////////////////////////////////////

static guint
crank_shape3_triangle_get_nvertices (CrankShape3Vertexed *shape)
{
  return 3;
}


//////// CrankShape2Polygon ////////////////////////////////////////////////////

static void
crank_shape3_triangle_get_vertex_pos2 (CrankShape3Polygon *shape,
                                     guint                vid,
                                     CrankVecFloat2      *pos)
{
  CrankShape3Triangle *tri = CRANK_SHAPE3_TRIANGLE (shape);

  if (vid < 3)
    crank_vec_float2_copy (tri->vertices + vid, pos);
  else
    g_warning ("Invalid vertex id: %u", vid);
}


static CrankWinding
crank_shape3_triangle_get_winding (CrankShape3Polygon *shape)
{
  CrankShape3Triangle *tri = (CrankShape3Triangle*) shape;

  return tri->wind;
}

//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_shape3_triangle_new:
 * @vertices: (array fixed-size=3): Vertices.
 *
 * Constructs a triangle shape.
 *
 * Returns: (transfer full): New triangle.
 */
CrankShape3Triangle*
crank_shape3_triangle_new (CrankVecFloat2 *vertices)
{
  CrankShape3Triangle *self;
  gfloat crs;

  self = (CrankShape3Triangle*) g_object_new (CRANK_TYPE_SHAPE3_TRIANGLE,
                                              NULL);

  crank_vec_float2_copy (vertices + 0, self->vertices + 0);
  crank_vec_float2_copy (vertices + 1, self->vertices + 1);
  crank_vec_float2_copy (vertices + 2, self->vertices + 2);

  self->wind = crank_winding_from_point_arr (self->vertices);
  return self;
}

/**
 * crank_shape3_triangle_new_regular:
 * @radius: Radius of vertices;
 *
 * Constructs a triangle shape.
 *
 * Returns: (transfer full): New triangle.
 */
CrankShape3Triangle*
crank_shape3_triangle_new_regular (const gfloat radius)
{
  CrankShape3Triangle *self;
  self = (CrankShape3Triangle*) g_object_new (CRANK_TYPE_SHAPE3_TRIANGLE,
                                              NULL);



  crank_vec_float2_init (self->vertices + 0, 0, radius);
  crank_vec_float2_init (self->vertices + 1, -0.866025404f * radius, 0.5f * radius);
  crank_vec_float2_init (self->vertices + 2,  0.866025404f * radius, 0.5f * radius);

  self->wind = CRANK_WINDING_CCW;
  return self;
}
