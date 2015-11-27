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

// CrankShape2Vertexed
static guint    crank_shape2_point_get_dimension (CrankShape2Vertexed *shape);

static guint    crank_shape2_point_get_nvertices (CrankShape2Vertexed *shape);

static guint    crank_shape2_point_get_nedges (CrankShape2Vertexed *shape);



static void     crank_shape2_point_get_vertex_pos (CrankShape2Vertexed *shape,
                                                   guint               index,
                                                   CrankVecFloat2     *vertex);

static void     crank_shape2_point_get_vertex_edges (CrankShape2Vertexed  *shape,
                                                     guint                 vid,
                                                     guint               **eids,
                                                     guint                *neids);

static void     crank_shape2_point_get_edge_vertices (CrankShape2Vertexed *shape,
                                                      guint                eid,
                                                      guint               *vids);

static guint    crank_shape2_point_get_farthest_vertex (CrankShape2Vertexed *shape,
                                                        CrankVecFloat2      *direction);

//////// Type definition ///////////////////////////////////////////////////////

/**
 * CrankShape2Point:
 *
 * Structure represents a point shape.
 */
struct _CrankShape2Point {
  CrankShape2Polygon _parent;
};

G_DEFINE_TYPE (CrankShape2Point,
               crank_shape2_point,
               CRANK_TYPE_SHAPE2_VERTEXED)

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
  CrankShape2VertexedClass *c_shape2vertexed;

  c_shape2 = CRANK_SHAPE2_CLASS (c);

  c_shape2->contains = crank_shape2_point_contains;



  c_shape2finite  = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2finite->get_bound_radius = crank_shape2_point_get_bound_radius;



  c_shape2vertexed = CRANK_SHAPE2_VERTEXED_CLASS (c);

  c_shape2vertexed->get_dimension = crank_shape2_point_get_dimension;
  c_shape2vertexed->get_nvertices = crank_shape2_point_get_nvertices;
  c_shape2vertexed->get_nedges = crank_shape2_point_get_nedges;

  c_shape2vertexed->get_vertex_pos = crank_shape2_point_get_vertex_pos;
  c_shape2vertexed->get_vertex_edges = crank_shape2_point_get_vertex_edges;
  c_shape2vertexed->get_edge_vertices = crank_shape2_point_get_edge_vertices;
  c_shape2vertexed->get_farthest_vertex = crank_shape2_point_get_farthest_vertex;
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
crank_shape2_point_get_dimension (CrankShape2Vertexed *shape)
{
  return 0;
}

static guint
crank_shape2_point_get_nvertices (CrankShape2Vertexed *shape)
{
  return 1;
}

static guint
crank_shape2_point_get_nedges (CrankShape2Vertexed *shape)
{
  return 0;
}

static void
crank_shape2_point_get_vertex_pos (CrankShape2Vertexed *shape,
                                   guint                vid,
                                   CrankVecFloat2      *pos)
{
  crank_vec_float2_init (pos, 0.0f, 0.0f);
}

static void
crank_shape2_point_get_vertex_edges (CrankShape2Vertexed  *shape,
                                     guint                 vid,
                                     guint               **eids,
                                     guint                *neids)
{
  *eids = NULL;
  *neids = 0;
}


static void
crank_shape2_point_get_edge_vertices (CrankShape2Vertexed *shape,
                                      guint                eid,
                                      guint               *vids)
{
  g_warning ("Invalid edge id: Point does not have edge: %u", eid);
  vids[0] = 0;
  vids[1] = 0;
}

static guint
crank_shape2_point_get_farthest_vertex (CrankShape2Vertexed *shape,
                                        CrankVecFloat2      *direction)
{
  return 0;
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
