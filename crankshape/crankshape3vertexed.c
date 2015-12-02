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

#include "crankbox.h"
#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"


/**
 * SECTION: crankshape3vertexed
 * @title: CrankShape3Vertexed
 * @short_description: Vertex based shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Represents vertex based shapes.
 *
 * # Abstract Functions
 *
 * * #CrankShape3VertexedClass.get_dimension()
 * * #CrankShape3VertexedClass.get_nvertices()
 * * #CrankShape3VertexedClass.get_nedges()
 * * #CrankShape3VertexedClass.get_nfaces()
 * * #CrankShape3VertexedClass.get_edge_vertices()
 * * #CrankShape3VertexedClass.get_edge_faces()
 * * #CrankShape3VertexedClass.get_face_vertices()
 * * #CrankShape3VertexedClass.get_face_edges()
 *
 * # Abstract Functions left
 *
 * * #CrankShape3FiniteClass.is_convex()
 * * #CrankShape3FiniteClass.get_bound_radius()
 * * #CrankShape3Class.contains()
 *
 * # Virtual Functions
 *
 * * #CrankShape3VertexedClass.get_face_as_shape()
 * * CrankShape3VertexedClass.get_farthest_vertex()
 */

//////// List of virtual functions /////////////////////////////////////////////

static void  crank_shape3_vertexed_get_property (GObject    *object,
                                                    guint       prop_id,
                                                    GValue     *value,
                                                    GParamSpec *pspec);

static CrankShape3Vertexed* crank_shape3_vertexed_approximate_vertexed (CrankShape3Finite *shape);

static CrankShape2Polygon* crank_shape3_vertexed_def_get_face_as_shape (CrankShape3Vertexed *shape,
                                                                        const guint          fid,
                                                                        CrankTrans3         *pos);


static guint crank_shape3_vertexed_def_get_farthest_vertex (CrankShape3Vertexed *shape,
                                                              CrankVecFloat3         *dir);



//////// Prioerty and signals //////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_DIMENSION,
  PROP_NVERTICES,
  PROP_NEDGES,
  PROP_NFACES,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape3Vertexed,
                        crank_shape3_vertexed,
                        CRANK_TYPE_SHAPE3_FINITE)


//////// GTypeInstance /////////////////////////////////////////////////////////

void
crank_shape3_vertexed_init (CrankShape3Vertexed *self)
{

}

void
crank_shape3_vertexed_class_init (CrankShape3VertexedClass *c)
{
  GObjectClass *c_gobject;
  CrankShape3FiniteClass *c_shape3finite;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape3_vertexed_get_property;

  pspecs[PROP_DIMENSION] = g_param_spec_uint ("dimension", "dimension",
                                              "Dimension of shape",
                                              0, 3, 0,
                                              G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_NVERTICES] = g_param_spec_uint ("nvertices", "nvertices",
                                              "Number of vertices",
                                              1, G_MAXUINT, 4,
                                              G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_NEDGES] = g_param_spec_uint ("nedges", "nedges",
                                           "Number of edges",
                                           0, G_MAXUINT, 4,
                                           G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_NFACES] = g_param_spec_uint ("nfaces", "nfaces",
                                           "Number of faces",
                                           0, G_MAXUINT, 4,
                                           G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);

  c_shape3finite->approximate_vertexed = crank_shape3_vertexed_approximate_vertexed;


  c->get_face_as_shape = crank_shape3_vertexed_def_get_face_as_shape;
  c->get_farthest_vertex = crank_shape3_vertexed_def_get_farthest_vertex;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape3_vertexed_get_property (GObject    *object,
                                       guint       prop_id,
                                       GValue     *value,
                                       GParamSpec *pspec)
{
  CrankShape3Vertexed *self = CRANK_SHAPE3_VERTEXED (object);
  switch (prop_id)
    {
    case PROP_DIMENSION:
      g_value_set_uint (value, crank_shape3_vertexed_get_dimension (self));
      break;
    case PROP_NVERTICES:
      g_value_set_uint (value, crank_shape3_vertexed_get_nvertices (self));
      break;
    case PROP_NEDGES:
      g_value_set_uint (value, crank_shape3_vertexed_get_nedges (self));
      break;
    case PROP_NFACES:
      g_value_set_uint (value, crank_shape3_vertexed_get_nfaces (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


//////// CrankShape3Finite /////////////////////////////////////////////////////

static CrankShape3Vertexed*
crank_shape3_vertexed_approximate_vertexed (CrankShape3Finite *shape)
{
  return (CrankShape3Vertexed*) g_object_ref (shape);
}


//////// Default Implementations ///////////////////////////////////////////////

static CrankShape2Polygon*
crank_shape3_vertexed_def_get_face_as_shape (CrankShape3Vertexed *shape,
                                                const guint             fid,
                                                CrankTrans3            *pos)
{
  return NULL;
}


static guint
crank_shape3_vertexed_def_get_farthest_vertex (CrankShape3Vertexed *shape,
                                                  CrankVecFloat3         *dir)
{
  guint i;
  guint n;

  guint r;
  gfloat dist;
  CrankVecFloat3 vertpos;

  r = 0;
  crank_shape3_vertexed_get_vertex_pos (shape, 0, &vertpos);
  dist = crank_vec_float3_dot (&vertpos, dir);

  n = crank_shape3_vertexed_get_nvertices (shape);
  for (i = 1; i < n; i ++)
    {
      gfloat ndist;

      crank_shape3_vertexed_get_vertex_pos (shape, 0, &vertpos);
      ndist = crank_vec_float3_dot (&vertpos, dir);

      if (dist < ndist)
        {
          r = i;
          dist = ndist;
        }
    }
  return r;
}

//////// Shape Properties //////////////////////////////////////////////////////
/**
 * crank_shape3_vertexed_get_dimension:
 * @shape: A Shape.
 *
 * Gets dimension of a shape.
 *
 * 0 correspond to point shapes. 3 correspond to polyhedron.
 *
 * Returns: Dimension of shape.
 */
guint
crank_shape3_vertexed_get_dimension (CrankShape3Vertexed *shape)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_dimension (shape);
}

/**
 * crank_shape3_vertexed_get_nvertices:
 * @shape: A Shape.
 *
 * Gets number of vertices.
 *
 * Returns: Number of vertices in the shape.
 */
guint
crank_shape3_vertexed_get_nvertices (CrankShape3Vertexed *shape)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_nvertices (shape);
}

/**
 * crank_shape3_vertexed_get_nedges:
 * @shape: A Shape.
 *
 * Gets number of edges.
 *
 * Returns: Number of edges in the shape.
 */
guint
crank_shape3_vertexed_get_nedges (CrankShape3Vertexed *shape)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_nedges (shape);
}

/**
 * crank_shape3_vertexed_get_nfaces:
 * @shape: A Shape.
 *
 * Gets number of vertices.
 *
 * Returns: Number of faces in the shape.
 */
guint
crank_shape3_vertexed_get_nfaces (CrankShape3Vertexed *shape)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_nfaces (shape);
}



//////// Vertex Properties /////////////////////////////////////////////////////

/**
 * crank_shape3_vertexed_get_vertex_pos:
 * @shape: A Shape.
 * @vid: Vertex ID
 * @pos: (out): Position of vertex.
 *
 * Gets position of a vertex.
 */
void
crank_shape3_vertexed_get_vertex_pos (CrankShape3Vertexed *shape,
                                         const guint             vid,
                                         CrankVecFloat3         *pos)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  c->get_vertex_pos (shape, vid, pos);
}

/**
 * crank_shape3_vertexed_get_vertex_edges:
 * @shape: A Shape.
 * @vid: Vertex ID
 * @neids: (out): Length of edge array.
 *
 * Gets array of edges that shares vertex @vid.
 *
 * Returns: (array length=neids) (transfer full): Edges that shares a vertex.
 */
guint*
crank_shape3_vertexed_get_vertex_edges (CrankShape3Vertexed *shape,
                                        const guint          vid,
                                        guint               *neids)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_vertex_edges (shape, vid, neids);
}

/**
 * crank_shape3_vertexed_get_vertex_faces:
 * @shape: A Shape.
 * @vid: Vertex ID
 * @nfids: (out): Length of face array.
 *
 * Gets array of faces that shares vertex @vid.
 *
 * Returns: (array length=nfids) (transfer full): Edges that shares a vertex.
 */
guint*
crank_shape3_vertexed_get_vertex_faces (CrankShape3Vertexed *shape,
                                           const guint             vid,
                                           guint                  *nfids)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_vertex_faces (shape, vid, nfids);
}


/**
 * crank_shape3_vertexed_get_edge_vertices:
 * @shape: A Shape.
 * @eid: Edge ID
 * @vids: (out caller-allocates) (array fixed-size=2): Vertex IDs.
 *
 * Gets vertices of an edge.
 */
void
crank_shape3_vertexed_get_edge_vertices (CrankShape3Vertexed *shape,
                                            const guint             eid,
                                            guint                  *vids)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_edge_vertices (shape, eid, vids);
}

/**
 * crank_shape3_vertexed_get_edge_faces:
 * @shape: A Shape.
 * @eid: Edge ID
 * @fids: (out caller-allocates) (array fixed-size=2): Face IDs.
 *
 * Gets faces that share an edge.
 */
void
crank_shape3_vertexed_get_edge_faces (CrankShape3Vertexed *shape,
                                            const guint             eid,
                                            guint                  *fids)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_edge_faces (shape, eid, fids);
}

/**
 * crank_shape3_vertexed_get_face_vertices:
 * @shape: A Shape.
 * @fid: Face ID.
 * @nvids: (out): Length of vertices array.
 *
 * Gets vertices array that the face has.
 *
 * Returns: (array length=nvids) (transfer full): Array of vertices.
 */
guint*
crank_shape3_vertexed_get_face_vertices (CrankShape3Vertexed *shape,
                                            const guint             fid,
                                            guint                  *nvids)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_face_vertices (shape, fid, nvids);
}

/**
 * crank_shape3_vertexed_get_face_edges:
 * @shape: A Shape.
 * @fid: Face ID.
 * @neids: (out): Length of edges array.
 *
 * Gets edges array that the face has.
 *
 * Returns: (array length=neids) (transfer full): Array of edges.
 */
guint*
crank_shape3_vertexed_get_face_edges (CrankShape3Vertexed *shape,
                                         const guint             fid,
                                         guint                  *neids)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_face_vertices (shape, fid, neids);
}


/**
 * crank_shape3_vertexed_get_face_as_shape:
 * @shape: A Shape.
 * @fid: Face ID.
 * @pos: (out): Position of face in @shape
 *
 * Gets a face as a #CrankShape2Polygon.
 *
 * Returns: (transfer full) (nullable): A Shape, or %NULL if not supported.
 */
CrankShape2Polygon*
crank_shape3_vertexed_get_face_as_shape (CrankShape3Vertexed *shape,
                                            const guint             fid,
                                            CrankTrans3            *pos)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_face_as_shape (shape, fid, pos);
}

/**
 * crank_shape3_vertexed_get_farthest_vertex:
 * @shape: A Shape
 * @dir: Direction
 *
 * Gets the farthest vertex in the polyhedron.
 *
 * Returns: A Vertex ID.
 */
guint
crank_shape3_vertexed_get_farthest_vertex (CrankShape3Vertexed *shape,
                                              CrankVecFloat3         *dir)
{
  CrankShape3VertexedClass *c = CRANK_SHAPE3_VERTEXED_GET_CLASS (shape);

  return c->get_farthest_vertex (shape, dir);
}
