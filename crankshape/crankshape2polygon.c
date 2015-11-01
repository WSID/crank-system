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

/**
 * SECTION:crankshape2polygon
 * @title: CrankSahpe2Polygon
 * @short_description: Interface for polygon shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This interface describes operations that can be done on polygons.
 *
 * # Default implementations
 *
 * #CrankShape2Polygon has default implementation with several assumption.
 *
 * * The polygon has same number of edges, to the number of vertices (As ordinary
 *   polygons have same number of both.)
 * * The edges are winding polygons in counter-clockwise.
 *
 * This assumption applies to
 * * #CrankShape2PolygonInterface.get_nedges
 * * #CrankShape2PolygonInterface.get_edge
 * * #CrankShape2PolygonInterface.get_edge_vertices
 * * #CrankShape2PolygonInterface.get_edge_normal
 *
 * If implementing class does not follows assumption from above, it should
 * provide its own implementation. It may override these for more efficient
 * implementation.
 *
 * For #CrankShape2PolygonInterface.get_farthest_vertex, default implementation
 * iterates all over vertices.
 *
 * #CrankShape2Polygon does not provide default implementation for these.
 *
 * * #CrankShape2PolygonInterface.get_nvertices
 * * #CrankShape2PolygonInterface.get_vertex
 */

//////// Virtual function implementations //////////////////////////////////////

static gboolean                 crank_shape2_polygon_is_convex (CrankShape2Finite *shape);

static CrankShape2Polygon      *crank_shape2_polygon_approximate_polygon (CrankShape2Finite *shape);


//////// Default implementation prototype //////////////////////////////////////

static guint           crank_shape2_polygon_get_nedges_def (CrankShape2Polygon *shape);

static void            crank_shape2_polygon_get_edge_def (CrankShape2Polygon *shape,
                                                           guint                index,
                                                           CrankRanFloat       *edge,
                                                           CrankTrans2         *position);

static void            crank_shape2_polygon_get_edge_vertices_def (CrankShape2Polygon *shape,
                                                                    guint                index,
                                                                    CrankPairUint       *vertices);

static void            crank_shape2_polygon_get_edge_normal_def (CrankShape2Polygon *shape,
                                                                  guint                index,
                                                                  CrankVecFloat2      *normal);

static guint           crank_shape2_polygon_get_farthest_vertex_def (CrankShape2Polygon *shape,
                                                                      CrankVecFloat2      *direction,
                                                                      CrankVecFloat2      *vertex);

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

  c->get_nedges = crank_shape2_polygon_get_nedges_def;
  c->get_edge = crank_shape2_polygon_get_edge_def;
  c->get_edge_vertices = crank_shape2_polygon_get_edge_vertices_def;
  c->get_edge_normal = crank_shape2_polygon_get_edge_normal_def;
  c->get_farthest_vertex = crank_shape2_polygon_get_farthest_vertex_def;
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


static guint
crank_shape2_polygon_get_nedges_def (CrankShape2Polygon *shape)
{
  return crank_shape2_polygon_get_nvertices (shape);
}

static void
crank_shape2_polygon_get_edge_def (CrankShape2Polygon *shape,
                                    guint                index,
                                    CrankRanFloat       *edge,
                                    CrankTrans2         *position)
{
  CrankPairUint vindices;
  CrankVecFloat2 vertex[2];
  CrankVecFloat2 seg;

  crank_shape2_polygon_get_edge_vertices (shape, index, &vindices);
  crank_shape2_polygon_get_vertex (shape, vindices.a, vertex + 0);
  crank_shape2_polygon_get_vertex (shape, vindices.b, vertex + 1);
  crank_vec_float2_sub (vertex + 1, vertex + 0, &seg);

  if (edge != NULL)
    crank_ran_float_init (edge, 0, crank_vec_float2_get_magn (&seg));

  if (position != NULL)
    {
      crank_vec_float2_copy (vertex + 0, & position->mtrans);
      position->mrot = atan2f (seg.y, seg.x);
      position->mscl = 1;
    }
}


static void
crank_shape2_polygon_get_edge_vertices_def (CrankShape2Polygon *shape,
                                             guint                index,
                                             CrankPairUint       *vertices)
{
  guint nvertices = crank_shape2_polygon_get_nvertices (shape);

  vertices->a = index;
  vertices->b = (index + 1 == nvertices) ? 0 : index + 1;
}


static void
crank_shape2_polygon_get_edge_normal_def (CrankShape2Polygon *shape,
                                           guint                index,
                                           CrankVecFloat2*      normal)
{
  CrankPairUint vindices;
  CrankVecFloat2 vertex[2];
  CrankVecFloat2 seg;

  crank_shape2_polygon_get_edge_vertices (shape, index, &vindices);
  crank_shape2_polygon_get_vertex (shape, vindices.a, vertex + 0);
  crank_shape2_polygon_get_vertex (shape, vindices.b, vertex + 1);

  crank_vec_float2_sub (vertex + 1, vertex + 0, &seg);

  normal->x =   seg.y;
  normal->y = - seg.x;

  crank_vec_float2_unit_self (normal);
}


static guint
crank_shape2_polygon_get_farthest_vertex_def (CrankShape2Polygon *shape,
                                               CrankVecFloat2      *direction,
                                               CrankVecFloat2      *vertex)
{
  guint n = crank_shape2_polygon_get_nvertices (shape);
  guint i;
  guint j;

  gfloat dot;


  crank_shape2_polygon_get_vertex (shape, 0, vertex);
  j = 0;
  dot = crank_vec_float2_dot (direction, vertex);

  for (i = 1; i < n; i++)
    {
      CrankVecFloat2 nvertex;
      gfloat ndot;

      crank_shape2_polygon_get_vertex (shape, i, &nvertex);
      ndot = crank_vec_float2_dot (vertex, &nvertex);

      if (dot < ndot)
        {
          dot = ndot;
          j = i;
          crank_vec_float2_copy (&nvertex, vertex);
        }
    }

  return j;
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
 * crank_shape2_ipolygon_get_nedges:
 * @shape: A Shape.
 *
 * Gets number of edges of this shape.
 *
 * Default implementation: Returns number of vertices, as ordinary polygon will
 *   have same number of edges to vertices.
 *
 * Returns: Number of edges.
 */
guint
crank_shape2_polygon_get_nedges (CrankShape2Polygon *shape)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  return c->get_nedges (shape);
}



/**
 * crank_shape2_polygon_get_edge:
 * @shape: A Shape
 * @index: A Index of edge.
 * @edge: (out): Edge as range.
 * @position: (out): Position of @edge.
 *
 * Get edge of polygon.
 *
 * Default implementation: Guess edge from
 *   crank_shape2_ipolygon_get_edge_vertices() and fill @edge and @position.
 * * @edge will be [0, (length of edge)).
 * * @position will have mtrans = (vert0), mrot = (atan2 of (vert1 - vert0)).
 */
void
crank_shape2_polygon_get_edge (CrankShape2Polygon *shape,
                                guint                index,
                                CrankRanFloat       *edge,
                                CrankTrans2         *position)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  c->get_edge (shape, index, edge, position);
}



/**
 * crank_shape2_polygon_get_edge_vertices:
 * @shape: A Shape
 * @index: A index of edge.
 * @vertices: (out): A Pair of indices of vertices.
 *
 * Gets indices of vertices belongs to the given index.
 *
 * Default implementation: return {@index, @index + 1} or {@index, 0} if index
 *   is last index of vertices.
 */
void
crank_shape2_polygon_get_edge_vertices (CrankShape2Polygon *shape,
                                         guint                index,
                                         CrankPairUint       *position)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  return c->get_edge_vertices (shape, index, position);
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
 * @vertex: (out): A Vertex.
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
                                           CrankVecFloat2      *direction,
                                           CrankVecFloat2      *vertex)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  return c->get_farthest_vertex (shape, direction, vertex);
}

