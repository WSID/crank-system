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
#include "crankrotation.h"
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2polygon.h"

/**
 * SECTION:crankshape2polygon
 * @title: CrankSahpe2Polygon
 * @short_description: Interface for polygon shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This represents a polygonal shape.
 *
 * # Index of vertices and edges.
 *
 * In ordinary polygon shape, there are same number of edges as vertices. So
 * a vertex and edge shares same index. The edge has same index of starting
 * vertex.
 *
 * # Default implementation.
 *
 * This class has default implementations. They are implemented with following
 * assumptions.
 *
 * * Vertices are
 *
 * # Abstract functions.
 *
 * * #CrankShape2PolygonClass.get_nvertices
 * * #CrankShape2PolygonClass.get_vertex
 *
 * # Virtual functions.
 *
 * * #CrankShape2FiniteClass.approximate_polygon()
 *
 *   Default Implementation: As it is already polygon, it returns itself
 *
 * * #CrankShape2PolygonClass.get_edge_normal()
 * * #CrankShape2PolygonClass.get_farthest_vertex()
 * * #CrankShape2PolygonClass.get_normal_edge()
 */

//////// Virtual function implementations //////////////////////////////////////

static gboolean                 crank_shape2_polygon_is_convex (CrankShape2Finite *shape);

static CrankShape2Polygon      *crank_shape2_polygon_approximate_polygon (CrankShape2Finite *shape);


//////// Default implementation prototype //////////////////////////////////////

static void            crank_shape2_polygon_get_edge_normal_def (CrankShape2Polygon *shape,
                                                                  guint                index,
                                                                  CrankVecFloat2      *normal);

static guint           crank_shape2_polygon_get_farthest_vertex_def (CrankShape2Polygon *shape,
                                                                     CrankVecFloat2     *direction);

static guint           crank_shape2_polygon_get_normal_edge_def   (CrankShape2Polygon *shape,
                                                                   CrankVecFloat2     *normal);

//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape2Polygon,
                        crank_shape2_polygon,
                        CRANK_TYPE_SHAPE2_FINITE)

//////// GTypeInstance /////////////////////////////////////////////////////////

void
crank_shape2_polygon_init (CrankShape2Polygon *shape)
{
}


void
crank_shape2_polygon_class_init (CrankShape2PolygonClass *c)
{
  CrankShape2FiniteClass *c_shape2_finite;

  c_shape2_finite = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2_finite->is_convex = crank_shape2_polygon_is_convex;
  c_shape2_finite->approximate_polygon = crank_shape2_polygon_approximate_polygon;

  c->get_edge_normal = crank_shape2_polygon_get_edge_normal_def;
  c->get_farthest_vertex = crank_shape2_polygon_get_farthest_vertex_def;
  c->get_normal_edge = crank_shape2_polygon_get_normal_edge_def;
}

//////// CrankShape2Finite /////////////////////////////////////////////////////

static gboolean
crank_shape2_polygon_is_convex (CrankShape2Finite *shape)
{
  CrankShape2Polygon *self = (CrankShape2Polygon*) shape;
  guint i, n;

  CrankVecFloat2 cvert[3];
  CrankVecFloat2 seg[2];
  gfloat crs;

  n = crank_shape2_polygon_get_nvertices (self);

  if (n < 4) return TRUE; // Triangle is always convex.

  crank_shape2_polygon_get_vertex (self, 0, cvert + 0);
  crank_shape2_polygon_get_vertex (self, 1, cvert + 1);
  crank_shape2_polygon_get_vertex (self, 2, cvert + 2);

  crank_vec_float2_sub (cvert + 1, cvert + 0, seg + 0);
  crank_vec_float2_sub (cvert + 2, cvert + 1, seg + 1);

  crs = seg[0].x * seg[1].y - seg[1].x * seg[0].y;

  for (i = 3; i < n; i++)
    {
      gfloat vcrs;
      crank_shape2_polygon_get_vertex (self, i, cvert + (i % 3));
      crank_vec_float2_sub (cvert + 1, cvert + 0, seg + 0);
      crank_vec_float2_sub (cvert + 2, cvert + 1, seg + 1);
      vcrs = seg[0].x * seg[1].y - seg[1].x * seg[0].y;

      if (crs * vcrs < 0) return FALSE;
    }

  return TRUE;
}

CrankShape2Polygon*
crank_shape2_polygon_approximate_polygon (CrankShape2Finite *shape)
{
  return (CrankShape2Polygon*) g_object_ref (shape);
}

//////// Default implementations ///////////////////////////////////////////////

static void
crank_shape2_polygon_get_edge_normal_def (CrankShape2Polygon *shape,
                                           guint                index,
                                           CrankVecFloat2*      normal)
{
  guint index_next;
  CrankVecFloat2 vertex[2];
  CrankVecFloat2 seg;

  index_next = (index + 1) % crank_shape2_polygon_get_nvertices (shape);

  crank_shape2_polygon_get_vertex (shape, index, vertex + 0);
  crank_shape2_polygon_get_vertex (shape, index_next, vertex + 1);

  crank_vec_float2_sub (vertex + 1, vertex + 0, &seg);

  crank_rot_vec2_right (&seg, normal);
  crank_vec_float2_unit_self (normal);
}


static guint
crank_shape2_polygon_get_farthest_vertex_def (CrankShape2Polygon *shape,
                                              CrankVecFloat2     *direction)
{
  guint n = crank_shape2_polygon_get_nvertices (shape);
  guint i;
  guint j;

  CrankVecFloat2 vertex;
  gfloat dot;

  crank_shape2_polygon_get_vertex (shape, 0, &vertex);
  j = 0;
  dot = crank_vec_float2_dot (direction, &vertex);

  for (i = 1; i < n; i++)
    {
      gfloat ndot;

      crank_shape2_polygon_get_vertex (shape, i, &vertex);
      ndot = crank_vec_float2_dot (direction, &vertex);

      if (dot < ndot)
        {
          dot = ndot;
          j = i;
        }
    }

  return j;
}

static guint
crank_shape2_polygon_get_normal_edge_def (CrankShape2Polygon *shape,
                                          CrankVecFloat2     *normal)
{
  guint nvertices;
  guint vert_p;
  guint vert;
  guint vert_n;

  CrankVecFloat2 vp_p;
  CrankVecFloat2 vp;
  CrankVecFloat2 vp_n;

  CrankVecFloat2 seg_a;
  CrankVecFloat2 seg_b;

  gfloat dot_a;
  gfloat dot_b;

  nvertices = crank_shape2_polygon_get_nvertices (shape);
  vert = crank_shape2_polygon_get_farthest_vertex (shape, normal);

  vert_p = ((vert != 0) ? vert  : nvertices) - 1;
  vert_n = vert + 1;

  vert_n = (vert_n != nvertices) ? vert_n : 0;

  crank_shape2_polygon_get_vertex (shape, vert_p, &vp_p);
  crank_shape2_polygon_get_vertex (shape, vert, &vp);
  crank_shape2_polygon_get_vertex (shape, vert_n, &vp_n);

  crank_vec_float2_sub (&vp, &vp_p, &seg_a);
  crank_vec_float2_sub (&vp_n, &vp, &seg_b);

  dot_a = crank_vec_float2_dot (&seg_a, &vp_p) / crank_vec_float2_get_magn (&seg_a);
  dot_b = crank_vec_float2_dot (&seg_b, &vp_p) / crank_vec_float2_get_magn (&seg_b);

  return (dot_a < dot_b) ? vert_p : vert;
}

//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_shape2_polygon_get_nvertices:
 * @shape: A Shape.
 *
 * Get numbers of vertices.
 *
 * Returns: Number of vertices.
 */
guint
crank_shape2_polygon_get_nvertices (CrankShape2Polygon *shape)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  return c->get_nvertices (shape);
}



/**
 * crank_shape2_polygon_get_vertex:
 * @shape: A Shape.
 * @index: Index of vertex to get.
 * @vertex: (out): A Vertex.
 *
 * Gets position of a vertex in the shape.
 */
void
crank_shape2_polygon_get_vertex (CrankShape2Polygon *shape,
                                  guint                index,
                                  CrankVecFloat2      *vertex)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  c->get_vertex (shape, index, vertex);
}


/**
 * crank_shape2_polygon_get_edge_normal:
 * @shape: A shape.
 * @index: index of edge.
 * @normal: A normal of edge.
 *
 * Get normal of edge of given index.
 *
 * Default implementation: Assumes edges are winding counter-clockwise.
 *   Guess edge from crank_shape2_ipolygon_get_edge_vertices() and returns left
 *   orthogonal direction of edge.
 */
void
crank_shape2_polygon_get_edge_normal (CrankShape2Polygon *shape,
                                       guint                index,
                                       CrankVecFloat2      *normal)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  c->get_edge_normal (shape, index, normal);
}




/**
 * crank_shape2_polygon_get_farthest_vertex:
 * @shape: A Shape.
 * @direction: A Direction.
 *
 * Gets the farthest vertex towards to direction.
 *
 * Default implementation: performs dot product for all vertices and returns
 *   most farthest vertex.
 *
 * Returns: index of vertex in shape.
 */
guint
crank_shape2_polygon_get_farthest_vertex (CrankShape2Polygon *shape,
                                           CrankVecFloat2      *direction)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  return c->get_farthest_vertex (shape, direction);
}


/**
 * crank_shape2_polygon_get_normal_edge:
 * @shape: A Shape.
 * @normal: A Normal.
 *
 * Gets the edge whose has nearest normal to @normal.
 *
 * Returns: index of edge in shape.
 */
guint
crank_shape2_polygon_get_normal_edge (CrankShape2Polygon *shape,
                                      CrankVecFloat2     *normal)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  return c->get_normal_edge (shape, normal);
}

