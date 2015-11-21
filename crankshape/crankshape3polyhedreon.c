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
#include "crankshape3polyhedreon.h"


/**
 * SECTION: crankshape3polyhedreon
 * @title: CrankShape3Polyhedreon
 * @short_description: Polyhedron shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Represents polyhedreon shape.
 */

//////// List of virtual functions /////////////////////////////////////////////

static void  crank_shape3_polyhedreon_get_property (GObject    *object,
                                                    guint       prop_id,
                                                    GValue     *value,
                                                    GParamSpec *pspec);

static CrankShape3Polyhedreon *crank_shape3_polyhedreon_approximate_polyhedreon (CrankShape3Finite *shape);


static void crank_shape3_polyhedreon_def_get_face_normal (CrankShape3Polyhedreon *shape,
                                                          const guint             fid,
                                                          CrankVecFloat3         *nor);

static CrankShape2Polygon* crank_shape3_polyhedreon_def_get_face_as_shape (CrankShape3Polyhedreon *shape,
                                                                           const guint             fid,
                                                                           CrankTrans3            *pos);


static guint crank_shape3_polyhedreon_def_get_farthest_vertex (CrankShape3Polyhedreon *shape,
                                                              CrankVecFloat3         *dir);

static guint crank_shape3_polyhedreon_def_get_normal_face (CrankShape3Polyhedreon *shape,
                                                          CrankVecFloat3         *nor);



//////// Prioerty and signals //////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_NVERTICES,
  PROP_NEDGES,
  PROP_NFACES,

  PROP_COUNTS
};

GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankShape3Polyhedreon,
                        crank_shape3_polyhedreon,
                        CRANK_TYPE_SHAPE3_FINITE)


//////// GTypeInstance /////////////////////////////////////////////////////////

void
crank_shape3_polyhedreon_init (CrankShape3Polyhedreon *self)
{

}

void
crank_shape3_polyhedreon_class_init (CrankShape3PolyhedreonClass *c)
{
  GObjectClass *c_gobject;
  CrankShape3FiniteClass *c_shape3finite;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape3_polyhedreon_get_property;

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

  c_shape3finite->approximate_polyhedreon = crank_shape3_polyhedreon_approximate_polyhedreon;


  c->get_face_normal = crank_shape3_polyhedreon_def_get_face_normal;
  c->get_face_as_shape = crank_shape3_polyhedreon_def_get_face_as_shape;
  c->get_farthest_vertex = crank_shape3_polyhedreon_def_get_farthest_vertex;
  c->get_normal_face = crank_shape3_polyhedreon_def_get_normal_face;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape3_polyhedreon_get_property (GObject    *object,
                                       guint       prop_id,
                                       GValue     *value,
                                       GParamSpec *pspec)
{
  CrankShape3Polyhedreon *self = CRANK_SHAPE3_POLYHEDREON (object);
  switch (prop_id)
    {
    case PROP_NVERTICES:
      g_value_set_uint (value, crank_shape3_polyhedreon_get_nvertices (self));
      break;
    case PROP_NEDGES:
      g_value_set_uint (value, crank_shape3_polyhedreon_get_nedges (self));
      break;
    case PROP_NFACES:
      g_value_set_uint (value, crank_shape3_polyhedreon_get_nfaces (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// CrankShape3Finite /////////////////////////////////////////////////////

static CrankShape3Polyhedreon*
crank_shape3_polyhedreon_approximate_polyhedreon (CrankShape3Finite *shape)
{
  return CRANK_SHAPE3_POLYHEDREON (g_object_ref (shape));
}


//////// Default Implementations ///////////////////////////////////////////////

static void
crank_shape3_polyhedreon_def_get_face_normal (CrankShape3Polyhedreon *shape,
                                              const guint             fid,
                                              CrankVecFloat3         *nor)
{
  guint *vids;
  guint nvids;

  CrankVecFloat3 vert_a;
  CrankVecFloat3 vert_b;

  CrankVecFloat3 seg_a;
  CrankVecFloat3 seg_b;

  vids = crank_shape3_polyhedreon_get_face_vertices (shape, fid, &nvids);

  crank_shape3_polyhedreon_get_vertex_pos (shape, vids[0], &vert_a);
  crank_shape3_polyhedreon_get_vertex_pos (shape, vids[1], &vert_b);

  crank_vec_float3_sub (&vert_b, &vert_a, &seg_a);

  crank_shape3_polyhedreon_get_vertex_pos (shape, vids[2], &vert_a);

  crank_vec_float3_sub (&vert_a, &vert_b, &seg_b);

  crank_vec_float3_crs (&seg_a, &seg_b, nor);
  crank_vec_float3_unit_self (nor);
}

static CrankShape2Polygon*
crank_shape3_polyhedreon_def_get_face_as_shape (CrankShape3Polyhedreon *shape,
                                                const guint             fid,
                                                CrankTrans3            *pos)
{
  return NULL;
}


static guint
crank_shape3_polyhedreon_def_get_farthest_vertex (CrankShape3Polyhedreon *shape,
                                                  CrankVecFloat3         *dir)
{
  guint i;
  guint n;

  guint r;
  gfloat dist;
  CrankVecFloat3 vertpos;

  r = 0;
  crank_shape3_polyhedreon_get_vertex_pos (shape, 0, &vertpos);
  dist = crank_vec_float3_dot (&vertpos, dir);

  n = crank_shape3_polyhedreon_get_nvertices (shape);
  for (i = 1; i < n; i ++)
    {
      gfloat ndist;

      crank_shape3_polyhedreon_get_vertex_pos (shape, 0, &vertpos);
      ndist = crank_vec_float3_dot (&vertpos, dir);

      if (dist < ndist)
        {
          r = i;
          dist = ndist;
        }
    }
  return r;
}

static guint
crank_shape3_polyhedreon_def_get_normal_face (CrankShape3Polyhedreon *shape,
                                              CrankVecFloat3         *nor)
{
  guint vid;
  guint *fids;
  guint nfids;

  guint i;

  guint r;
  gfloat dot;
  CrankVecFloat3 facenor;

  vid = crank_shape3_polyhedreon_get_farthest_vertex (shape, nor);
  fids = crank_shape3_polyhedreon_get_vertex_faces (shape, vid, &nfids);

  r = fids[0];
  crank_shape3_polyhedreon_get_face_normal (shape, r, &facenor);
  dot = crank_vec_float3_dot (nor, &facenor);

  for (i = 1; i < nfids; i++)
    {
      gfloat ndot;

      crank_shape3_polyhedreon_get_face_normal (shape, fids[i], &facenor);
      ndot = crank_vec_float3_dot (nor, &facenor);

      if (dot < ndot)
        {
          r = fids[i];
          dot = ndot;
        }
    }
  return r;
}





//////// Shape Properties //////////////////////////////////////////////////////

/**
 * crank_shape3_polyhedreon_get_nvertices:
 * @shape: A Shape.
 *
 * Gets number of vertices.
 *
 * Returns: Number of vertices in the shape.
 */
guint
crank_shape3_polyhedreon_get_nvertices (CrankShape3Polyhedreon *shape)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_nvertices (shape);
}

/**
 * crank_shape3_polyhedreon_get_nedges:
 * @shape: A Shape.
 *
 * Gets number of edges.
 *
 * Returns: Number of edges in the shape.
 */
guint
crank_shape3_polyhedreon_get_nedges (CrankShape3Polyhedreon *shape)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_nedges (shape);
}

/**
 * crank_shape3_polyhedreon_get_nfaces:
 * @shape: A Shape.
 *
 * Gets number of vertices.
 *
 * Returns: Number of faces in the shape.
 */
guint
crank_shape3_polyhedreon_get_nfaces (CrankShape3Polyhedreon *shape)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_nfaces (shape);
}



//////// Vertex Properties /////////////////////////////////////////////////////

/**
 * crank_shape3_polyhedreon_get_vertex_pos:
 * @shape: A Shape.
 * @vid: Vertex ID
 * @pos: (out): Position of vertex.
 *
 * Gets position of a vertex.
 */
void
crank_shape3_polyhedreon_get_vertex_pos (CrankShape3Polyhedreon *shape,
                                         const guint             vid,
                                         CrankVecFloat3         *pos)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  c->get_vertex_pos (shape, vid, pos);
}

/**
 * crank_shape3_polyhedreon_get_vertex_edges:
 * @shape: A Shape.
 * @vid: Vertex ID
 * @neids: (out): Length of edge array.
 *
 * Gets array of edges that shares vertex @vid.
 *
 * Returns: (array length=neids) (transfer full): Edges that shares a vertex.
 */
guint*
crank_shape3_polyhederon_get_vertex_edges (CrankShape3Polyhedreon *shape,
                                           const guint             vid,
                                           guint                  *neids)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_vertex_edges (shape, vid, neids);
}

/**
 * crank_shape3_polyhedreon_get_vertex_faces:
 * @shape: A Shape.
 * @vid: Vertex ID
 * @nfids: (out): Length of face array.
 *
 * Gets array of faces that shares vertex @vid.
 *
 * Returns: (array length=nfids) (transfer full): Edges that shares a vertex.
 */
guint*
crank_shape3_polyhedreon_get_vertex_faces (CrankShape3Polyhedreon *shape,
                                           const guint             vid,
                                           guint                  *nfids)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_vertex_faces (shape, vid, nfids);
}


/**
 * crank_shape3_polyhedreion_get_edge_vertices:
 * @shape: A Shape.
 * @eid: Edge ID
 * @vids: (out caller-allocates) (array fixed-size=2): Vertex IDs.
 *
 * Gets vertices of an edge.
 */
void
crank_shape3_polyhedreon_get_edge_vertices (CrankShape3Polyhedreon *shape,
                                            const guint             eid,
                                            guint                  *vids)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_edge_vertices (shape, eid, vids);
}

/**
 * crank_shape3_polyhedreion_get_edge_faces:
 * @shape: A Shape.
 * @eid: Edge ID
 * @fids: (out caller-allocates) (array fixed-size=2): Face IDs.
 *
 * Gets faces that share an edge.
 */
void
crank_shape3_polyhedreon_get_edge_faces (CrankShape3Polyhedreon *shape,
                                            const guint             eid,
                                            guint                  *fids)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_edge_faces (shape, eid, fids);
}

/**
 * crank_shape3_polyhedreon_get_face_vertices:
 * @shape: A Shape.
 * @fid: Face ID.
 * @nvids: (out): Length of vertices array.
 *
 * Gets vertices array that the face has.
 *
 * Returns: (array length=nvids) (transfer full): Array of vertices.
 */
guint*
crank_shape3_polyhedreon_get_face_vertices (CrankShape3Polyhedreon *shape,
                                            const guint             fid,
                                            guint                  *nvids)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_face_vertices (shape, fid, nvids);
}

/**
 * crank_shape3_polyhedreon_get_face_edges:
 * @shape: A Shape.
 * @fid: Face ID.
 * @neids: (out): Length of edges array.
 *
 * Gets edges array that the face has.
 *
 * Returns: (array length=neids) (transfer full): Array of edges.
 */
guint*
crank_shape3_polyhedreon_get_face_edges (CrankShape3Polyhedreon *shape,
                                         const guint             fid,
                                         guint                  *neids)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_face_vertices (shape, fid, neids);
}

/**
 * crank_shape3_polyhedreon_get_face_normal:
 * @shape: A Shape.
 * @fid: Face ID.
 * @nor: (out): Normal of face.
 *
 * Gets normal of face.
 */
void
crank_shape3_polyhedreon_get_face_normal (CrankShape3Polyhedreon *shape,
                                          const guint             fid,
                                          CrankVecFloat3         *nor)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  c->get_face_normal (shape, fid, nor);
}



/**
 * crank_shape3_polyhedreon_get_face_as_shape:
 * @shape: A Shape.
 * @fid: Face ID.
 * @pos: (out): Position of face in @shape
 *
 * Gets a face as a #CrankShape2Polygon.
 *
 * Returns: (transfer full) (nullable): A Shape, or %NULL if not supported.
 */
CrankShape2Polygon*
crank_shape3_polyhedreon_get_face_as_shape (CrankShape3Polyhedreon *shape,
                                            const guint             fid,
                                            CrankTrans3            *pos)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_face_as_shape (shape, fid, pos);
}

/**
 * crank_shape3_polyhedreon_get_farthest_vertex:
 * @shape: A Shape
 * @dir: Direction
 *
 * Gets the farthest vertex in the polyhedreon.
 *
 * Returns: A Vertex ID.
 */
guint
crank_shape3_polyhedreon_get_farthest_vertex (CrankShape3Polyhedreon *shape,
                                              CrankVecFloat3         *dir)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_farthest_vertex (shape, dir);
}

/**
 * crank_shape3_polyhedreon_get_normal_face:
 * @shape: A Shape
 * @nor: Normal/
 *
 * Gets the face which normal is most towards to @nor in the polyhedreon.
 *
 * Returns: A Face ID.
 */
guint
crank_shape3_polyhedreon_get_normal_face (CrankShape3Polyhedreon *shape,
                                          CrankVecFloat3         *nor)
{
  CrankShape3PolyhedreonClass *c = CRANK_SHAPE3_POLYHEDREON_GET_CLASS (shape);

  return c->get_normal_face (shape, nor);
}
