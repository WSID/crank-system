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
#include "crankshapemisc.h"
#include "crankrotation.h"
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2vertexed.h"
#include "crankshape2polygon.h"
#include "crankshape2cpolygon.h"

/**
 * SECTION: crankshape2cpolygon
 * @title: CrankShape2CPolygon
 * @short_description: Concrete polygon representation.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This represents non-abstract polygon descriptions, with vertices and segments.
 *
 * The shape is immutable.
 */

//////// List of virtual functions /////////////////////////////////////////////

static gboolean crank_shape2_cpolygon_contains (CrankShape2    *shape,
                                                CrankVecFloat2 *point);


static gfloat crank_shape2_cpolygon_get_bound_radius (CrankShape2Finite *shape);


static guint crank_shape2_cpolygon_get_nvertices (CrankShape2Vertexed *shape);

static void crank_shape2_cpolygon_get_vertex_pos (CrankShape2Vertexed *shape,
                                                  guint                index,
                                                  CrankVecFloat2      *vertex);

static void crank_shape2_cpolygon_get_edge_normal (CrankShape2Polygon *shape,
                                                   guint               index,
                                                   CrankVecFloat2     *normal);

static CrankWinding crank_shape2_cpolygon_get_winding (CrankShape2Polygon *shape);


//////// Private functions /////////////////////////////////////////////////////

static gfloat crank_shape2_cpolygon_get_seg_angle (CrankVecFloat2 *seg_a,
                                                   CrankVecFloat2 *seg_b);

static void crank_shape2_cpolygon_build_cache (CrankShape2CPolygon *cpolygon);

static void crank_shape2_cpolygon_build_cache_bound (CrankShape2CPolygon *cpolygon);

static void crank_shape2_cpolygon_build_cache_wind  (CrankShape2CPolygon *cpolygon);

//////// Type definition ///////////////////////////////////////////////////////

/**
 * CrankShape2CPolygon:
 *
 * A Polygon shape. Please refer section description.
 */
struct _CrankShape2CPolygon {
  CrankShape2   _parent_instance;

  guint nvertices;
  CrankVecFloat2 *vertices;
  CrankVecFloat2 *normals;


  //////// Cached space
  // Bound cache
  gfloat          bound_radius;
  CrankBox2       bound_box;
  CrankVecFloat2  center;

  // Winding cache
  gboolean        convex;
  CrankWinding    winding;
};

G_DEFINE_TYPE(CrankShape2CPolygon,
                        crank_shape2_cpolygon,
                        CRANK_TYPE_SHAPE2_POLYGON)




//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_cpolygon_init (CrankShape2CPolygon *self)
{
  self->vertices = NULL;
  self->normals = NULL;
}

static void
crank_shape2_cpolygon_class_init (CrankShape2CPolygonClass *c)
{
  CrankShape2Class       *c_shape2;
  CrankShape2FiniteClass *c_shape2_finite;
  CrankShape2VertexedClass *c_shape2_vertexed;
  CrankShape2PolygonClass *c_shape2_polygon;

  c_shape2 = CRANK_SHAPE2_CLASS(c);

  c_shape2->contains = crank_shape2_cpolygon_contains;


  c_shape2_finite = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2_finite->get_bound_radius = crank_shape2_cpolygon_get_bound_radius;


  c_shape2_vertexed = CRANK_SHAPE2_VERTEXED_CLASS (c);

  c_shape2_vertexed->get_nvertices = crank_shape2_cpolygon_get_nvertices;
  c_shape2_vertexed->get_vertex_pos = crank_shape2_cpolygon_get_vertex_pos;

  c_shape2_polygon = CRANK_SHAPE2_POLYGON_CLASS (c);

  c_shape2_polygon->get_winding = crank_shape2_cpolygon_get_winding;
  c_shape2_polygon->get_edge_normal = crank_shape2_cpolygon_get_edge_normal;
}

//////// CrankShape2 ///////////////////////////////////////////////////////////

static gboolean
crank_shape2_cpolygon_contains (CrankShape2    *shape,
                  CrankVecFloat2 *point)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*) shape;
  guint i;

  guint pass_count = 0;

  for (i = 0; i < self->nvertices; i++)
    {
      guint in = (i + 1) % self->nvertices;
      CrankVecFloat2* v = self->vertices + i;
      CrankVecFloat2* vn = self->vertices + in;
      gboolean edge_pass;

      edge_pass = (v->x != vn->x) &&                    // Not parrael to x axis.
                  (((v->x <= point->x) && (point->x <= vn->x)) ||     // 0 in range.
                   ((v->x >= point->x) && (point->x >= vn->x)));

      if (edge_pass) pass_count++;
    }

  return pass_count % 2 != 0;
}

//////// CrankShape2Finite ////////////////////////////////////////////////////

static gfloat
crank_shape2_cpolygon_get_bound_radius (CrankShape2Finite *shape)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*)shape;
  guint i;

  gfloat radius = 0;

  for (i = 0; i < self->nvertices; i++)
    {
      gfloat radius_current =
        crank_vec_float2_get_magn (self->vertices + i);

      radius = MAX (radius, radius_current);
    }
  return radius;
}


//////// CrankShape2Polygon ///////////////////////////////////////////////////

static guint
crank_shape2_cpolygon_get_nvertices (CrankShape2Vertexed *shape)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*)shape;

  return self->nvertices;
}


static void
crank_shape2_cpolygon_get_vertex_pos (CrankShape2Vertexed *shape,
                                      guint                vid,
                                      CrankVecFloat2      *pos)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*)shape;

  crank_vec_float2_copy (self->vertices + vid,
                         pos);
}

static void
crank_shape2_cpolygon_get_edge_normal (CrankShape2Polygon *shape,
                                       guint               index,
                                       CrankVecFloat2     *nor)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*)shape;

  crank_vec_float2_copy (self->normals + index,
                         nor);
}

static CrankWinding
crank_shape2_cpolygon_get_winding (CrankShape2Polygon *shape)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*) shape;

  return self->winding;
}


//////// Private Functions /////////////////////////////////////////////////////
static gfloat
crank_shape2_cpolygon_get_seg_angle (CrankVecFloat2 *seg_a,
                                     CrankVecFloat2 *seg_b)
{
  return atan2f (crank_vec_float2_crs (seg_a, seg_b),
                 crank_vec_float2_dot (seg_a, seg_b));
}

static void
crank_shape2_cpolygon_build_cache (CrankShape2CPolygon *shape)
{
  crank_shape2_cpolygon_build_cache_bound (shape);
  crank_shape2_cpolygon_build_cache_wind (shape);
}

static void
crank_shape2_cpolygon_build_cache_bound (CrankShape2CPolygon *shape)
{
  guint i;
  guint n;

  gfloat bradius_sq;
  gfloat distance_sq;

  CrankVecFloat2 *vertex = shape->vertices + 0;

  // Process for initial vertex.
  bradius_sq = crank_vec_float2_get_magn_sq (vertex);

  crank_vec_float2_copy (vertex, & shape->bound_box.start);
  crank_vec_float2_copy (vertex, & shape->bound_box.end);

  for (i = 1; i < n; i++)
    {
      vertex = shape->vertices + i;

      // Bound radius
      distance_sq = crank_vec_float2_get_magn_sq (vertex);

      if (bradius_sq < distance_sq)
        bradius_sq = distance_sq;

      // Bounding box
      shape->bound_box.end.x = MAX (shape->bound_box.end.x, vertex->x);
      shape->bound_box.end.y = MAX (shape->bound_box.end.y, vertex->y);
      shape->bound_box.start.x = MIN (shape->bound_box.start.x, vertex->x);
      shape->bound_box.start.y = MIN (shape->bound_box.start.y, vertex->y);
    }

  shape->bound_radius = sqrtf (bradius_sq);
  crank_vec_float2_mixs (& shape->bound_box.start,
                         & shape->bound_box.end,
                         0.5f,
                         & shape->center);
}

static void
crank_shape2_cpolygon_build_cache_wind (CrankShape2CPolygon *shape)
{
  guint i;
  guint j;
  guint n;
  guint n1;

  gfloat angle_sum;

  CrankVecFloat2 *v;
  CrankVecFloat2 seg_p;
  CrankVecFloat2 seg;


  n = shape->nvertices;
  n1 = n - 1;

  // Initial setting.
  shape->convex = TRUE;

  // Process last point.
  crank_vec_float2_sub (shape->vertices + n1, shape->vertices + (n1 - 1), &seg_p);
  crank_vec_float2_sub (shape->vertices + 0, shape->vertices + n1, &seg);
  angle_sum = crank_shape2_cpolygon_get_seg_angle (&seg_p, &seg);

  crank_rot_vec2_right (&seg, shape->normals + 0);
  crank_vec_float2_unit_self (shape->normals + 0);

  // Iterate on segments.
  for (i = 0; i < n1; i++)
    {
      gfloat angle;
      crank_vec_float2_copy (&seg, &seg_p);
      crank_vec_float2_sub (shape->vertices + (i + 1), shape->vertices + i, &seg);

      angle = crank_shape2_cpolygon_get_seg_angle (&seg_p, &seg);

      if (angle * angle_sum < 0)
        shape->convex = FALSE;

      angle_sum += angle;

      crank_rot_vec2_right (&seg, shape->normals + i);
      crank_vec_float2_unit_self (shape->normals + i);
    }

  // Checking winding.
  if (0 < angle_sum)
    {
      shape->winding = 1;
    }
  else
    {
      shape->winding = -1;

      for (i = 0; i < shape->nvertices; i++)
        crank_vec_float2_neg_self (shape->normals + i);
    }
}


//////// Constructors //////////////////////////////////////////////////////////
/**
 * crank_shape2_cpolygon_new:
 * @vertices: (array length=nvertices): Vertices
 * @nvertices: length of @vertices.
 *
 * Construct a polygon with given vertices.
 *
 * Returns: (transfer full): An polygon.
 */
CrankShape2CPolygon*
crank_shape2_cpolygon_new (CrankVecFloat2 *vertices,
                           guint           nvertices)
{
  CrankShape2CPolygon *self;
  guint i;

  if (nvertices < 2)
    {
      g_warning ("Not sufficient vertices!");
      return NULL;
    }

  self = (CrankShape2CPolygon*) g_object_new (CRANK_TYPE_SHAPE2_CPOLYGON, NULL);

  self->nvertices = nvertices;
  self->vertices = g_memdup (vertices, sizeof (CrankVecFloat2) * nvertices);
  self->normals = g_new (CrankVecFloat2, nvertices);
  crank_shape2_cpolygon_build_cache (self);

  return self;
}

/**
 * crank_shape2_cpolygon_new_from_polygon:
 * @poly: A Polygon representation.
 *
 * Construct a polygon with other polygon representation.
 *
 * Returns: (transfer full): An polygon.
 */
CrankShape2CPolygon*
crank_shape2_cpolygon_new_from_polygon (CrankShape2Polygon *poly)
{
  CrankShape2Vertexed *poly_vertexed;
  CrankShape2CPolygon *result;
  CrankVecFloat2 *vertices;
  guint n;
  guint i;

  poly_vertexed = (CrankShape2Vertexed*)poly;

  n = crank_shape2_vertexed_get_nvertices (poly_vertexed);
  vertices = g_new (CrankVecFloat2, n);

  for (i = 0; i < n; i++)
    crank_shape2_vertexed_get_vertex_pos (poly_vertexed, i, vertices + i);

  result = crank_shape2_cpolygon_new (vertices, n);

  g_free (vertices);
  return result;
}
