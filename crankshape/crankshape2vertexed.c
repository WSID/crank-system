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

#include "crankshape2vertexed.h"


//////// List of virtual functions /////////////////////////////////////////////

static void crank_shape2_vertexed_get_property (GObject    *object,
                                                guint       prop_id,
                                                GValue     *value,
                                                GParamSpec *pspec);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_DIMENSION,
  PROP_NVERTICES,
  PROP_NEDGES,
  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape2Vertexed,
                        crank_shape2_vertexed,
                        CRANK_TYPE_SHAPE2_FINITE)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_vertexed_init (CrankShape2Vertexed *self)
{
}

static void
crank_shape2_vertexed_class_init (CrankShape2VertexedClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);
  c_gobject->get_property = crank_shape2_vertexed_get_property;

  pspecs[PROP_DIMENSION] = g_param_spec_uint (
      "dimension", "dimension", "Dimension of vertexed shape.",
      0, 2, 0,
      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_NVERTICES] = g_param_spec_uint (
      "nvertices", "nvertices", "Number of vertices.",
      0, G_MAXUINT, 0,
      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_NEDGES] = g_param_spec_uint (
      "nedges", "nedges", "Number of edges.",
      0, G_MAXUINT, 0,
      G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape2_vertexed_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  CrankShape2Vertexed *shape = CRANK_SHAPE2_VERTEXED (shape);

  switch (prop_id)
    {
    case PROP_DIMENSION:
      g_value_set_uint (value,
                        crank_shape2_vertexed_get_dimension (shape));
      break;

    case PROP_NVERTICES:
      g_value_set_uint (value,
                        crank_shape2_vertexed_get_nvertices (shape));
      break;

    case PROP_NEDGES:
      g_value_set_uint (value,
                        crank_shape2_vertexed_get_nedges (shape));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// Shape Properties //////////////////////////////////////////////////////

/**
 * crank_shape2_vertexed_get_dimension:
 * @shape: A Shape.
 *
 * Gets a dimension of vertexed shape.
 * * 0: This is a point. probably #CrankShape2Point
 * * 1: This is a line. probably #CrankShape2Segment
 * * 2: An ordinary polygonal shape.
 *
 * Returns: Dimension of shape.
 */
guint
crank_shape2_vertexed_get_dimension (CrankShape2Vertexed *shape)
{
  CrankShape2VertexedClass *c = CRANK_SHAPE2_VERTEXED_GET_CLASS (shape);
  return c->get_dimension (shape);
}

/**
 * crank_shape2_vertexed_get_nvertices:
 * @shape: A Shape.
 *
 * Gets number of vertices in shape.
 *
 * if it is 1, then probably point shape, like #CrankShape2Point
 *
 * Returns: Number of vertices.
 */
guint
crank_shape2_vertexed_get_nvertices (CrankShape2Vertexed *shape)
{
  CrankShape2VertexedClass *c = CRANK_SHAPE2_VERTEXED_GET_CLASS (shape);
  return c->get_nvertices (shape);
}

/**
 * crank_shape2_vertexed_get_nedges:
 * @shape: A Shape.
 *
 * Gets number of edges in shape.
 *
 * if it is 1, then probably line shape, like #CrankShape2Segment
 *
 * Returns: Number of edges.
 */
guint
crank_shape2_vertexed_get_nedges (CrankShape2Vertexed *shape)
{
  CrankShape2VertexedClass *c = CRANK_SHAPE2_VERTEXED_GET_CLASS (shape);
  return c->get_nedges (shape);
}


//////// Vertex Properties /////////////////////////////////////////////////////

/**
 * crank_shape2_vertexed_get_vertex_pos:
 * @shape: A Shape.
 * @vid: Index of vertex.
 * @pos: (out): Position of vertex.
 *
 * Gets position of vertex in shape's space.
 */
void
crank_shape2_vertexed_get_vertex_pos   (CrankShape2Vertexed *shape,
                                        guint                vid,
                                        CrankVecFloat2      *pos)
{
  CrankShape2VertexedClass *c = CRANK_SHAPE2_VERTEXED_GET_CLASS (shape);
  return c->get_vertex_pos (shape, vid, pos);
}

/**
 * crank_shape2_vertexed_get_vertex_edges:
 * @shape: A Shape.
 * @vid: Index of vertex.
 * @eids: (out callee-allocates) (array length=neids):
 *      Edge ids that associated to @vid.
 * @neids: (out): Number of edge ids that associated to.
 *
 * Gets edges that associated to a vertex.
 */
void
crank_shape2_vertexed_get_vertex_edges (CrankShape2Vertexed  *shape,
                                        guint                 vid,
                                        guint               **eids,
                                        guint               *neids)
{
  CrankShape2VertexedClass *c = CRANK_SHAPE2_VERTEXED_GET_CLASS (shape);
  return c->get_vertex_edges (shape, vid, eids, neids);
}

//////// Edge Properties ///////////////////////////////////////////////////////

/**
 * crank_shape2_vertexed_get_edge_vertices:
 * @shape: A Shape.
 * @eid: Index of edge.
 * @vids: (out caller-allocates) (array fixed-size=2):
 *      Vertex ids that associated to @eid.
 *
 * Get vertices that associated to edges.
 */
void
crank_shape2_vertexed_get_edge_vertices (CrankShape2Vertexed *shape,
                                         guint                index,
                                         guint               *vertices)
{
  CrankShape2VertexedClass *c = CRANK_SHAPE2_VERTEXED_GET_CLASS (shape);
  return c->get_edge_vertices (shape, index, vertices);
}


//////// Element picker ////////////////////////////////////////////////////////

/**
 * crank_shape2_vertexed_get_farthest_vertex:
 * @shape: A Shape.
 * @direction: Direction to check.
 *
 * Returns: Id of farthest vertex.
 */
guint
crank_shape2_vertexed_get_farthest_vertex (CrankShape2Vertexed *shape,
                                           CrankVecFloat2      *direction)
{
  CrankShape2VertexedClass *c = CRANK_SHAPE2_VERTEXED_GET_CLASS (shape);
  return c->get_farthest_vertex (shape, direction);
}

