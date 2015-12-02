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

/**
 * SECTION:crankshape2triangle
 * @title: CrankShape2Triangle
 * @short_description: Triangle shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Represents a triangle shape.
 */

//////// List of virtual functions /////////////////////////////////////////////

// CrankShape2
static gboolean crank_shape2_triangle_contains (CrankShape2    *shape,
                                               CrankVecFloat2 *point);

// CrankShape2Finite
static gboolean crank_shape2_triangle_is_convex (CrankShape2Finite *shape);

static gfloat   crank_shape2_triangle_get_bound_radius (CrankShape2Finite *shape);


// CrankShape2vertexed
static guint    crank_shape2_triangle_get_nvertices (CrankShape2Vertexed *shape);

static void     crank_shape2_triangle_get_vertex_pos (CrankShape2Vertexed *shape,
                                                     guint                vid,
                                                     CrankVecFloat2      *pos);

// CrankShape2Polygon
static void     crank_shape2_triangle_get_edge_normal (CrankShape2Polygon *shape,
                                                       guint               eid,
                                                       CrankVecFloat2     *nor);


//////// Type Definition ///////////////////////////////////////////////////////

/**
 * CrankShape2Triangle:
 *
 * Structure represents a segment shape.
 */
struct _CrankShape2Triangle {
  CrankShape2Polygon _parent;

  CrankWinding   wind;
  CrankVecFloat2 vertices[3];
};

G_DEFINE_TYPE (CrankShape2Triangle,
               crank_shape2_triangle,
               CRANK_TYPE_SHAPE2_POLYGON)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_triangle_init (CrankShape2Triangle *inst)
{
}

static void
crank_shape2_triangle_class_init (CrankShape2TriangleClass *c)
{
  CrankShape2Class *c_shape2;
  CrankShape2FiniteClass *c_shape2finite;
  CrankShape2VertexedClass *c_shape2vertexed;
  CrankShape2PolygonClass *c_shape2polygon;

  c_shape2 = CRANK_SHAPE2_CLASS (c);

  c_shape2->contains = crank_shape2_triangle_contains;


  c_shape2finite = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2finite->is_convex = crank_shape2_triangle_is_convex;
  c_shape2finite->get_bound_radius = crank_shape2_triangle_get_bound_radius;


  c_shape2vertexed = CRANK_SHAPE2_VERTEXED_CLASS (c);

  c_shape2vertexed->get_nvertices = crank_shape2_triangle_get_nvertices;
  c_shape2vertexed->get_vertex_pos = crank_shape2_triangle_get_vertex_pos;


  c_shape2polygon = CRANK_SHAPE2_POLYGON_CLASS (c);

  c_shape2polygon->get_edge_normal = crank_shape2_triangle_get_edge_normal;
}


//////// CrankShape2 ///////////////////////////////////////////////////////////

static gboolean
crank_shape2_triangle_contains (CrankShape2    *shape,
                                CrankVecFloat2 *point)
{
  CrankShape2Triangle *tri = CRANK_SHAPE2_TRIANGLE (shape);

  return crank_tri_contains (tri->vertices, point);
}




//////// CrankShape2Finite /////////////////////////////////////////////////////

static gboolean
crank_shape2_triangle_is_convex (CrankShape2Finite *shape)
{
  return TRUE;
}


static gfloat
crank_shape2_triangle_get_bound_radius (CrankShape2Finite *shape)
{
  CrankShape2Triangle *tri = CRANK_SHAPE2_TRIANGLE (shape);
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
crank_shape2_triangle_get_nvertices (CrankShape2Vertexed *shape)
{
  return 3;
}

static void
crank_shape2_triangle_get_vertex_pos (CrankShape2Vertexed *shape,
                                     guint                vid,
                                     CrankVecFloat2      *pos)
{
  CrankShape2Triangle *tri = CRANK_SHAPE2_TRIANGLE (shape);

  if (vid < 3)
    crank_vec_float2_copy (tri->vertices + vid, pos);
  else
    g_warning ("Invalid vertex id: %u", vid);
}


//////// CrankShape2Polygon ////////////////////////////////////////////////////

static void
crank_shape2_triangle_get_edge_normal (CrankShape2Polygon *shape,
                                       guint               eid,
                                       CrankVecFloat2     *nor)
{
  CrankShape2Triangle *tri = CRANK_SHAPE2_TRIANGLE (shape);

  if (eid < 3)
    {
      CrankVecFloat2 disp;

      guint sa = eid;
      guint sb = (eid == 2) ? 0 : eid + 1;

      crank_vec_float2_sub (tri->vertices + sb, tri->vertices + sa, &disp);

      if (tri->wind < 0)
        crank_rot_vec2_left (& disp, nor);
      else
        crank_rot_vec2_right (& disp, nor);

      crank_vec_float2_unit_self (nor);
    }
  else
    {
      g_warning ("Invalid edge id: %u", eid);
    }
}



//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_shape2_triangle_new:
 * @vertices: (array fixed-size=3): Vertices.
 *
 * Constructs a triangle shape.
 *
 * Returns: (transfer full): New triangle.
 */
CrankShape2Triangle*
crank_shape2_triangle_new (CrankVecFloat2 *vertices)
{
  CrankShape2Triangle *self;
  gfloat crs;

  self = (CrankShape2Triangle*) g_object_new (CRANK_TYPE_SHAPE2_TRIANGLE,
                                              NULL);

  crank_vec_float2_copy (vertices + 0, self->vertices + 0);
  crank_vec_float2_copy (vertices + 1, self->vertices + 1);
  crank_vec_float2_copy (vertices + 2, self->vertices + 2);

  self->wind = crank_winding_from_point_arr (self->vertices);
  return self;
}

/**
 * crank_shape2_triangle_new_regular:
 * @radius: Radius of vertices;
 *
 * Constructs a triangle shape.
 *
 * Returns: (transfer full): New triangle.
 */
CrankShape2Triangle*
crank_shape2_triangle_new_regular (const gfloat radius)
{
  CrankShape2Triangle *self;
  self = (CrankShape2Triangle*) g_object_new (CRANK_TYPE_SHAPE2_TRIANGLE,
                                              NULL);



  crank_vec_float2_init (self->vertices + 0, 0, radius);
  crank_vec_float2_init (self->vertices + 1, -0.866025404f * radius, 0.5f * radius);
  crank_vec_float2_init (self->vertices + 2,  0.866025404f * radius, 0.5f * radius);

  self->wind = CRANK_WINDING_CCW;
  return self;
}
