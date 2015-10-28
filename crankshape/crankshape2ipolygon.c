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
#include "crankshape2ipolygon.h"

/**
 * SECTION:crankshape2ipolygon
 * @title: CrankSahpe2IPolygon
 * @short_description: Interface for polygon shape.
 * @stability: Unstable
 * @include crankshape.h
 *
 * This interface describes operations that can be done on polygons.
 *
 * Default implementation assumes the shape will have vertices in order of
 * counter-clockwise, and edges also in counter-clockwise.
 */

//////// Default implementation prototype //////////////////////////////////////

static CrankVecFloat2* crank_shape2_ipolygon_get_vertices_def (CrankShape2IPolygon *shape,
                                                               guint               *nvertices);

static guint           crank_shape2_ipolygon_get_nedges_def (CrankShape2IPolygon *shape);

static void            crank_shape2_ipolygon_get_edge_vertices_def (CrankShape2IPolygon *shape,
                                                                    guint                index,
                                                                    guint               *vert0,
                                                                    guint               *vert1);

static void            crank_shape2_ipolygon_get_edge_normal_def (CrankShape2IPolygon *shape,
                                                                  guint                index,
                                                                  CrankVecFloat2      *normal);

static void            crank_shape2_ipolygon_get_farthest_vertex_def (CrankShape2IPolygon *shape,
                                                                      CrankVecFloat2      *direction,
                                                                      CrankVecFloat2      *vertex);

//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_INTERFACE (CrankShape2IPolygon,
                    crank_shape2_ipolygon,
                    CRANK_TYPE_SHAPE2)

//////// GTypeInterface ////////////////////////////////////////////////////////

void
crank_shape2_ipolygon_default_init (CrankShape2IPolygonInterface *iface)
{
  iface->get_vertices = crank_shape2_ipolygon_get_vertices_def;
  iface->get_nedges = crank_shape2_ipolygon_get_nedges_def;
  iface->get_edge_vertices = crank_shape2_ipolygon_get_edge_vertices_def;
  iface->get_edge_normal = crank_shape2_ipolygon_get_edge_normal_def;
  iface->get_farthest_vertex = NULL;
}

//////// Default implementations ///////////////////////////////////////////////

static CrankVecFloat2*
crank_shape2_ipolygon_get_vertices_def (CrankShape2IPolygon *shape,
                                        guint               *nvertices)
{
  guint                 retlen;
  CrankVecFloat2       *ret;

  guint                 i;

  retlen = crank_shape2_ipolygon_get_nvertices (shape);
  ret = g_new (CrankVecFloat2, retlen);

  for (i = 0; i < retlen; i++)
    crank_shape2_ipolygon_get_vertex (shape, i, ret + i);

  if (nvertices != NULL)
    *nvertices = retlen;

  return ret;
}


static guint
crank_shape2_ipolygon_get_nedges_def (CrankShape2IPolygon *shape)
{
  return crank_shape2_ipolygon_get_nvertices (shape);
}


static void
crank_shape2_ipolygon_get_edge_vertices_def (CrankShape2IPolygon *shape,
                                             guint                index,
                                             guint               *vert0,
                                             guint               *vert1)
{
  guint nvertices = crank_shape2_ipolygon_get_nvertices (shape);

  *vert0 = index;
  *vert1 = (index + 1 == nvertices) ? 0 : index + 1;
}


static void
crank_shape2_ipolygon_get_edge_normal_def (CrankShape2IPolygon *shape,
                                           guint                index,
                                           CrankVecFloat2*      normal)
{
  guint vert0;
  guint vert1;
  CrankVecFloat2 vertex[2];
  CrankVecFloat2 seg;

  crank_shape2_ipolygon_get_edge_vertices (shape, index, &vert0, &vert1);
  crank_shape2_ipolygon_get_vertex (shape, vert0, vertex + 0);
  crank_shape2_ipolygon_get_vertex (shape, vert1, vertex + 1);

  crank_vec_float2_sub (vertex + 1, vertex + 0, &seg);

  normal->x =   seg.y;
  normal->y = - seg.x;

  crank_vec_float2_unit_self (normal);
}


static void
crank_shape2_ipolygon_get_farthest_vertex_def (CrankShape2IPolygon *shape,
                                               CrankVecFloat2      *direction,
                                               CrankVecFloat2      *vertex)
{
  guint n = crank_shape2_ipolygon_get_nvertices (shape);
  guint i;
  guint j;

  gfloat dot;


  crank_shape2_ipolygon_get_vertex (shape, 0, vertex);
  j = 0;
  dot = crank_vec_float2_dot (direction, vertex);

  for (i = 1; i < n; i++)
    {
      CrankVecFloat2 nvertex;
      gfloat ndot;

      crank_shape2_ipolygon_get_vertex (shape, i, &nvertex);
      ndot = crank_vec_float2_dot (vertex, &nvertex);

      if (dot < ndot)
        {
          dot = ndot;
          j = i;
          crank_vec_float2_copy (&nvertex, vertex);
        }
    }
}

//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_shape2_ipolygon_get_nvertex:
 * @shape: A Shape.
 *
 * Get numbers of vertices.
 *
 * Returns: Number of vertices.
 */
guint
crank_shape2_ipolygon_get_nvertices (CrankShape2IPolygon *shape)
{
  CrankShape2IPolygonInterface *iface;
  iface = CRANK_SHAPE2_IPOLYGON_GET_IFACE (shape);

  return iface->get_nvertices (shape);
}

/**
 * crank_shape2_ipolygon_get_vertex:
 * @shape: A Shape.
 * @index: Index of vertex to get.
 * @vertex: (out): A Vertex.
 *
 * Gets position of a vertex in the shape.
 */
void
crank_shape2_ipolygon_get_vertex (CrankShape2IPolygon *shape,
                                  guint                index,
                                  CrankVecFloat2      *vertex)
{
  CrankShape2IPolygonInterface *iface;
  iface = CRANK_SHAPE2_IPOLYGON_GET_IFACE (shape);

  iface->get_vertex (shape, index, vertex);
}

/**
 * crank_shape2_ipolygon_get_vertices:
 * @shape: A Shape.
 * @nvertices: (out): Number of vertices.
 *
 * Gets all vertices of shape.
 *
 * Returns: (array length=nvertices): All vertices.
 */
CrankVecFloat2*
crank_shape2_ipolygon_get_vertices (CrankShape2IPolygon *shape,
                                    guint               *nvertices)
{
  CrankShape2IPolygonInterface *iface;
  iface = CRANK_SHAPE2_IPOLYGON_GET_IFACE (shape);

  return iface->get_vertices (shape, nvertices);
}

/**
 * crank_shape2_ipolygon_get_nedges:
 * @shape: A Shape.
 *
 * Gets number of edges of this shape.
 *
 * Returns: Number of edges.
 */
guint
crank_shape2_ipolygon_get_nedges (CrankShape2IPolygon *shape)
{
  CrankShape2IPolygonInterface *iface;
  iface = CRANK_SHAPE2_IPOLYGON_GET_IFACE (shape);

  return iface->get_nedges (shape);
}

void
crank_shape2_ipolygon_get_edge_vertices (CrankShape2IPolygon *shape,
                                         guint                index,
                                         guint               *vert0,
                                         guint               *vert1)
{
  CrankShape2IPolygonInterface *iface;
  iface = CRANK_SHAPE2_IPOLYGON_GET_IFACE (shape);

  return iface->get_edge_vertices (shape, index, vert0, vert1);
}

/**
 * crank_shape2_ipolygon_get_edge_normal:
 * @shape: A shape.
 * @index: index of edge.
 * @normal: A normal of edge.
 *
 * Get normal of edge of given index.
 */
void
crank_shape2_ipolygon_get_edge_normal (CrankShape2IPolygon *shape,
                                       guint                index,
                                       CrankVecFloat2      *normal)
{
  CrankShape2IPolygonInterface *iface;
  iface = CRANK_SHAPE2_IPOLYGON_GET_IFACE (shape);

  iface->get_edge_normal (shape, index, normal);
}


/**
 * crank_shape2_ipolygon_get_farthest_vertex:
 * @shape: A Shape.
 * @direction: A Direction.
 * @vertex: (out): A Vertex.
 *
 * Gets the farthest vertex towards to direction.
 */
void
crank_shape2_ipolygon_get_farthest_vertex (CrankShape2IPolygon *shape,
                                           CrankVecFloat2      *direction,
                                           CrankVecFloat2      *vertex)
{
  CrankShape2IPolygonInterface *iface;
  iface = CRANK_SHAPE2_IPOLYGON_GET_IFACE (shape);

  iface->get_farthest_vertex (shape, direction, vertex);
}
