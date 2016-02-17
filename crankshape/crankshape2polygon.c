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
#include "crankshape2vertexed.h"
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
 * # Abstract Functions
 *
 * #CrankShape2PolygonClass.get_winding()
 *
 * # Abstract Functions left
 *
 * * #CrankShape2Class.contains()
 * * #CrankShape2FiniteClass.get_bound_radius()
 * * #CrankShape2VertexedClass.get_nvertices()
 * * #CrankShape2VertexedClass.get_vertex_pos()
 *
 * # Virtual functions.
 *
 * * #CrankShape2FiniteClass.is_convex()
 * * #CrankShape2VertexedClass.get_dimension()
 * * #CrankShape2VertexedClass.get_nedges()
 * * #CrankShape2VertexedClass.get_vertex_edges()
 * * #CrankShape2VertexedClass.get_edge_vertices()
 * * #CrankShape2PolygonClass.get_edge_normal()
 * * #CrankShape2PolygonClass.get_normal_edge()
 */

//////// Virtual function implementations //////////////////////////////////////

static void           crank_shape2_polygon_get_property (GObject    *shape,
                                                         guint       prop_id,
                                                         GValue     *value,
                                                         GParamSpec *pspec);

static gboolean       crank_shape2_polygon_is_convex (CrankShape2Finite *shape);


static guint          crank_shape2_polygon_get_dimension (CrankShape2Vertexed *vertexed);

static guint          crank_shape2_polygon_get_nedges (CrankShape2Vertexed *vertexed);

static void           crank_shape2_polygon_get_vertex_edges (CrankShape2Vertexed  *vertexed,
                                                             guint                 vids,
                                                             guint               **eids,
                                                             guint                *neids);

static void           crank_shape2_polygon_get_edge_vertices (CrankShape2Vertexed *vertexed,
                                                              guint                eid,
                                                              guint               *vids);


//////// Default implementation prototype //////////////////////////////////////

static void            crank_shape2_polygon_get_edge_normal_def (CrankShape2Polygon *shape,
                                                                  guint                index,
                                                                  CrankVecFloat2      *normal);
static guint           crank_shape2_polygon_get_normal_edge_def   (CrankShape2Polygon *shape,
                                                                   CrankVecFloat2     *normal);

//////// Properties and Signals ////////////////////////////////////////////////
enum {
  PROP_0,
  PROP_WINDING,
  PROP_COUNTS
};

static GParamSpec  *pspecs[PROP_COUNTS] = {NULL};



//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape2Polygon,
                        crank_shape2_polygon,
                        CRANK_TYPE_SHAPE2_VERTEXED)

//////// GTypeInstance /////////////////////////////////////////////////////////

void
crank_shape2_polygon_init (CrankShape2Polygon *shape)
{
}


void
crank_shape2_polygon_class_init (CrankShape2PolygonClass *c)
{
  GObjectClass *c_gobject;
  CrankShape2FiniteClass *c_shape2_finite;
  CrankShape2VertexedClass *c_shape2_vertexed;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape2_polygon_get_property;

  pspecs[PROP_WINDING] = g_param_spec_enum (
      "winding", "winding", "Winding of wertices list",
      CRANK_TYPE_WINDING, CRANK_WINDING_NONE,
      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_shape2_finite = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2_finite->is_convex = crank_shape2_polygon_is_convex;


  c_shape2_vertexed = CRANK_SHAPE2_VERTEXED_CLASS (c);

  c_shape2_vertexed->get_dimension = crank_shape2_polygon_get_dimension;
  c_shape2_vertexed->get_nedges = crank_shape2_polygon_get_nedges;
  c_shape2_vertexed->get_vertex_edges = crank_shape2_polygon_get_vertex_edges;
  c_shape2_vertexed->get_edge_vertices = crank_shape2_polygon_get_edge_vertices;


  c->get_edge_normal = crank_shape2_polygon_get_edge_normal_def;
  c->get_normal_edge = crank_shape2_polygon_get_normal_edge_def;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape2_polygon_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  CrankShape2Polygon *self = (CrankShape2Polygon*)object;

  switch (prop_id)
    {
    case PROP_WINDING:
      g_value_set_enum (value, crank_shape2_polygon_get_winding (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


//////// CrankShape2Finite /////////////////////////////////////////////////////

static gboolean
crank_shape2_polygon_is_convex (CrankShape2Finite *shape)
{
  CrankShape2Vertexed *self_vertexed = (CrankShape2Vertexed*)shape;
  CrankShape2Polygon *self = (CrankShape2Polygon*) shape;
  guint i, n;

  CrankVecFloat2 cvert[3];
  CrankVecFloat2 seg[2];
  gfloat crs;

  n = crank_shape2_vertexed_get_nvertices (self_vertexed);

  if (n < 4) return TRUE; // Triangle is always convex.

  crank_shape2_vertexed_get_vertex_pos (self_vertexed, 0, cvert + 0);
  crank_shape2_vertexed_get_vertex_pos (self_vertexed, 1, cvert + 1);
  crank_shape2_vertexed_get_vertex_pos (self_vertexed, 2, cvert + 2);

  crank_vec_float2_sub (cvert + 1, cvert + 0, seg + 0);
  crank_vec_float2_sub (cvert + 2, cvert + 1, seg + 1);

  crs = seg[0].x * seg[1].y - seg[1].x * seg[0].y;

  for (i = 3; i < n; i++)
    {
      gfloat vcrs;
      crank_shape2_vertexed_get_vertex_pos (self_vertexed, i, cvert + (i % 3));
      crank_vec_float2_sub (cvert + 1, cvert + 0, seg + 0);
      crank_vec_float2_sub (cvert + 2, cvert + 1, seg + 1);
      vcrs = seg[0].x * seg[1].y - seg[1].x * seg[0].y;

      if (crs * vcrs < 0) return FALSE;
    }

  return TRUE;
}

//////// CrankShape2Vertexed ///////////////////////////////////////////////////

static guint
crank_shape2_polygon_get_dimension (CrankShape2Vertexed *vertexed)
{
  return 2;
}

static guint
crank_shape2_polygon_get_nedges (CrankShape2Vertexed *vertexed)
{
  return crank_shape2_vertexed_get_nvertices (vertexed);
}

static void
crank_shape2_polygon_get_vertex_edges (CrankShape2Vertexed  *vertexed,
                                       guint                 vid,
                                       guint               **eids,
                                       guint                *neids)
{
  guint n = crank_shape2_vertexed_get_nvertices (vertexed);

  *eids = g_new (guint, 2);
  *neids = 2;

  *eids[0] = (vid == 0) ? (n - 1) : (vid - 1);
  *eids[1] = vid;
}

static void
crank_shape2_polygon_get_edge_vertices (CrankShape2Vertexed *vertexed,
                                        guint                eid,
                                        guint               *vids)
{
  guint n = crank_shape2_vertexed_get_nvertices (vertexed);

  vids[0] = eid;
  vids[1] = (eid == n - 1) ? 0 : (eid + 1);
}

//////// Default implementations ///////////////////////////////////////////////

static void
crank_shape2_polygon_get_edge_normal_def (CrankShape2Polygon *shape,
                                           guint                index,
                                           CrankVecFloat2*      normal)
{
  CrankShape2Vertexed *shape_vertexed = (CrankShape2Vertexed*) shape;

  guint index_next;
  CrankVecFloat2 vertex[2];
  CrankVecFloat2 seg;

  CrankWinding winding = crank_shape2_polygon_get_winding (shape);

  index_next = (index + 1) % crank_shape2_vertexed_get_nvertices (shape_vertexed);

  crank_shape2_vertexed_get_vertex_pos (shape_vertexed, index, vertex + 0);
  crank_shape2_vertexed_get_vertex_pos (shape_vertexed, index_next, vertex + 1);

  crank_vec_float2_sub (vertex + 1, vertex + 0, &seg);

  if (0 < winding)
    crank_rot_vec2_right (&seg, normal);
  else
    crank_rot_vec2_left (&seg, normal);
  crank_vec_float2_unit_self (normal);
}


static guint
crank_shape2_polygon_get_normal_edge_def (CrankShape2Polygon *shape,
                                          CrankVecFloat2     *normal)
{
  CrankShape2Vertexed *shape_vertexed = (CrankShape2Vertexed*) shape;
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

  nvertices = crank_shape2_vertexed_get_nvertices (shape_vertexed);
  vert = crank_shape2_vertexed_get_farthest_vertex (shape_vertexed, normal);

  vert_p = ((vert != 0) ? vert  : nvertices) - 1;
  vert_n = vert + 1;

  vert_n = (vert_n != nvertices) ? vert_n : 0;

  crank_shape2_vertexed_get_vertex_pos (shape_vertexed, vert_p, &vp_p);
  crank_shape2_vertexed_get_vertex_pos (shape_vertexed, vert, &vp);
  crank_shape2_vertexed_get_vertex_pos (shape_vertexed, vert_n, &vp_n);

  crank_vec_float2_sub (&vp, &vp_p, &seg_a);
  crank_vec_float2_sub (&vp_n, &vp, &seg_b);

  dot_a = crank_vec_float2_dot (&seg_a, &vp_p) / crank_vec_float2_get_magn (&seg_a);
  dot_b = crank_vec_float2_dot (&seg_b, &vp_p) / crank_vec_float2_get_magn (&seg_b);

  return (dot_a < dot_b) ? vert_p : vert;
}

//////// Public functions //////////////////////////////////////////////////////
/**
 * crank_shape2_polygon_get_winding:
 * @shape: A Shape.
 *
 * Get winding of a polygon, along with vertices list of it.
 *
 * Returns: Winding of shape, or CRANK_WINDING_NONE if all vertices are on a line.
 */
CrankWinding
crank_shape2_polygon_get_winding (CrankShape2Polygon *shape)
{
  CrankShape2PolygonClass *c;
  c = CRANK_SHAPE2_POLYGON_GET_CLASS (shape);

  return c->get_winding (shape);
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
 *   Guess edge from crank_shape2_vertexed_get_edge_vertices() and returns left
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

