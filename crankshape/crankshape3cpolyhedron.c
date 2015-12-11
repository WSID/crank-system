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

#include "crankpolystruct3.h"

#include "crankshapemisc.h"
#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polyhedron.h"

#include "crankshape3cpolyhedron.h"


//////// List of virtual functions /////////////////////////////////////////////

static gboolean   crank_shape3_cpolyhedron_contains (CrankShape3    *shape,
                                                     CrankVecFloat3 *ptr);


static gboolean   crank_shape3_cpolyhedron_is_convex     (CrankShape3Finite *shape);

static gfloat     crank_shape3_cpolyhedron_get_bound_radius (CrankShape3Finite *shape);


static guint      crank_shape3_cpolyhedron_get_nvertices (CrankShape3Vertexed *shape);

static guint      crank_shape3_cpolyhedron_get_nedges (CrankShape3Vertexed *shape);

static guint      crank_shape3_cpolyhedron_get_nfaces (CrankShape3Vertexed *shape);

static void       crank_shape3_cpolyhedron_get_vertex_pos (CrankShape3Vertexed *shape,
                                                           const guint          vid,
                                                           CrankVecFloat3      *pos);

static guint     *crank_shape3_cpolyhedron_get_vertex_edges (CrankShape3Vertexed *shape,
                                                             const guint          vid,
                                                             guint               *neids);

static guint     *crank_shape3_cpolyhedron_get_vertex_faces (CrankShape3Vertexed *shape,
                                                             const guint          vid,
                                                             guint               *nfids);

static void       crank_shape3_cpolyhedron_get_edge_vertices(CrankShape3Vertexed *shape,
                                                             const guint          eid,
                                                             guint                *vids);

static guint     *crank_shape3_cpolyhedron_get_edge_faces   (CrankShape3Vertexed *shape,
                                                             const guint          eid,
                                                             guint               *nfids);

static guint     *crank_shape3_cpolyhedron_get_face_vertices(CrankShape3Vertexed *shape,
                                                             const guint          fid,
                                                             guint               *nvids);

static guint     *crank_shape3_cpolyhedron_get_face_edges   (CrankShape3Vertexed *shape,
                                                             const guint          fid,
                                                             guint               *neids);

static CrankWinding crank_shape3_cpolyhedron_get_face_winding (CrankShape3Vertexed *shape,
                                                             const guint            fid);

static void       crank_shape3_cpolyhedron_get_face_normal  (CrankShape3Polyhedron *shape,
                                                             const guint            fid,
                                                             CrankVecFloat3        *nor);


//////// Private functions /////////////////////////////////////////////////////

static gfloat     crank_shape3_cpolyhedron_get_edge_y      (CrankVecFloat3         *pt0,
                                                            CrankVecFloat3         *pt1,
                                                            const gfloat            x);

static gboolean   crank_shape3_cpolyhedron_face_contains_xy (CrankShape3CPolyhedron *shape,
                                                             const guint             fid,
                                                             CrankVecFloat2         *xy);

static gfloat     crank_shape3_cpolyhedron_get_face_z       (CrankShape3CPolyhedron *shape,
                                                             const guint             fid,
                                                             CrankVecFloat2         *xy);


static void       crank_shape3_cpolyhedron_build_cache (CrankShape3CPolyhedron *shape);


static void       crank_shape3_cpolyhedron_build_bound_radius (CrankShape3CPolyhedron *shape);

static void       crank_shape3_cpolyhedron_build_face_normal (CrankShape3CPolyhedron *shape);

static void       crank_shape3_cpolyhedron_build_convex (CrankShape3CPolyhedron *shape);

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankShape3CPolyhedron {
  CrankShape3Polyhedron _parent;

  gboolean convex;
  gfloat   bound_radius;
  GArray *vert_pos;
  GArray *face_norm;
  CrankPolyStruct3 *pstruct;
};


G_DEFINE_TYPE (CrankShape3CPolyhedron,
               crank_shape3_cpolyhedron,
               CRANK_TYPE_SHAPE3_POLYHEDRON)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_cpolyhedron_init (CrankShape3CPolyhedron *self)
{
  self->vert_pos = g_array_new (FALSE, FALSE, sizeof (CrankVecFloat3));
  self->face_norm = g_array_new (FALSE, FALSE, sizeof (CrankVecFloat3));
  self->pstruct = NULL;
}

static void
crank_shape3_cpolyhedron_class_init (CrankShape3CPolyhedronClass *c)
{
  CrankShape3Class *c_shape3;
  CrankShape3FiniteClass *c_shape3finite;
  CrankShape3VertexedClass *c_shape3vertexed;
  CrankShape3PolyhedronClass *c_shape3polyhedron;

  c_shape3 = CRANK_SHAPE3_CLASS (c);

  c_shape3->contains = crank_shape3_cpolyhedron_contains;

  c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);

  c_shape3finite->is_convex = crank_shape3_cpolyhedron_is_convex;
  c_shape3finite->get_bound_radius = crank_shape3_cpolyhedron_get_bound_radius;

  c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);

  c_shape3vertexed->get_nvertices = crank_shape3_cpolyhedron_get_nvertices;
  c_shape3vertexed->get_nedges = crank_shape3_cpolyhedron_get_nedges;
  c_shape3vertexed->get_nfaces = crank_shape3_cpolyhedron_get_nfaces;

  c_shape3vertexed->get_vertex_edges = crank_shape3_cpolyhedron_get_vertex_edges;
  c_shape3vertexed->get_vertex_faces = crank_shape3_cpolyhedron_get_vertex_faces;
  c_shape3vertexed->get_edge_vertices = crank_shape3_cpolyhedron_get_edge_vertices;
  c_shape3vertexed->get_edge_faces = crank_shape3_cpolyhedron_get_edge_faces;
  c_shape3vertexed->get_face_vertices = crank_shape3_cpolyhedron_get_face_vertices;
  c_shape3vertexed->get_face_edges = crank_shape3_cpolyhedron_get_face_edges;
  c_shape3vertexed->get_face_winding = crank_shape3_cpolyhedron_get_face_winding;

  c_shape3polyhedron = CRANK_SHAPE3_POLYHEDRON_CLASS (c);

  c_shape3polyhedron->get_face_normal = crank_shape3_cpolyhedron_get_face_normal;
}

//////// CrankShape3 ///////////////////////////////////////////////////////////

static gboolean
crank_shape3_cpolyhedron_contains (CrankShape3    *shape,
                                   CrankVecFloat3 *ptr)
{
  CrankShape3Vertexed *self_vertexed = (CrankShape3Vertexed*) shape;
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;
  CrankVecFloat2 *ptr_xy = (CrankVecFloat2*) ptr;
  guint count;
  guint i, n;

  count = 0;
  n = crank_shape3_vertexed_get_nfaces (self_vertexed);
  for (i = 0; i < n; i++)
    {
      if ((0 < crank_shape3_cpolyhedron_get_face_z (self, i, ptr_xy)) &&
          (crank_shape3_cpolyhedron_face_contains_xy (self, i, ptr_xy)) )
        count ++;
    }

  return (count & 1) == 1;
}




//////// CrankShape3Finite /////////////////////////////////////////////////////

static gboolean
crank_shape3_cpolyhedron_is_convex (CrankShape3Finite *shape)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return self->convex;
}

static gfloat
crank_shape3_cpolyhedron_get_bound_radius (CrankShape3Finite *shape)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return self->bound_radius;
}




//////// CrankShape3Vertexed ///////////////////////////////////////////////////

static guint
crank_shape3_cpolyhedron_get_nvertices (CrankShape3Vertexed *shape)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_nvertices (self->pstruct);
}


static guint
crank_shape3_cpolyhedron_get_nedges (CrankShape3Vertexed *shape)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_nedges (self->pstruct);
}


static guint
crank_shape3_cpolyhedron_get_nfaces (CrankShape3Vertexed *shape)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_nfaces (self->pstruct);
}


static guint*
crank_shape3_cpolyhedron_get_vertex_edges (CrankShape3Vertexed *shape,
                                           const guint          vid,
                                           guint               *neids)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_vertex_edges (self->pstruct, vid, neids);
}

static guint*
crank_shape3_cpolyhedron_get_vertex_faces (CrankShape3Vertexed *shape,
                                           const guint          vid,
                                           guint               *nfids)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_vertex_faces (self->pstruct, vid, nfids);
}


static void
crank_shape3_cpolyhedron_get_edge_vertices (CrankShape3Vertexed *shape,
                                           const guint          eid,
                                           guint               *vids)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_edge_vertices (self->pstruct, eid, vids);
}

static guint*
crank_shape3_cpolyhedron_get_edge_faces (CrankShape3Vertexed *shape,
                                           const guint          eid,
                                           guint               *nfids)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_edge_faces (self->pstruct, eid, nfids);
}


static guint*
crank_shape3_cpolyhedron_get_face_vertices (CrankShape3Vertexed *shape,
                                            const guint          fid,
                                            guint               *nvids)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_face_vertices (self->pstruct, fid, nvids);
}

static guint*
crank_shape3_cpolyhedron_get_face_edges (CrankShape3Vertexed *shape,
                                           const guint          fid,
                                           guint               *neids)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;

  return crank_poly_struct3_get_face_edges (self->pstruct, fid, neids);
}

static CrankWinding
crank_shape3_cpolyhedron_get_face_winding (CrankShape3Vertexed *shape,
                                           const guint          fid)
{
  return CRANK_WINDING_CCW;
}


static void
crank_shape3_cpolyhedron_get_face_normal (CrankShape3Polyhedron *shape,
                                          const guint            fid,
                                          CrankVecFloat3        *nor)
{
  CrankShape3CPolyhedron *self = (CrankShape3CPolyhedron*) shape;
  CrankVecFloat3 *nreal;

  nreal = & g_array_index (self->face_norm, CrankVecFloat3, fid);

  crank_vec_float3_copy (nreal, nor);
}

//////// Private functions /////////////////////////////////////////////////////

static gfloat
crank_shape3_cpolyhedron_get_edge_y (CrankVecFloat3         *pt0,
                                     CrankVecFloat3         *pt1,
                                     const gfloat            x)
{
  gfloat bcoord = (x - pt0->x) / (pt1->x - pt0->x);

  return pt0->y * (1 - bcoord) + pt1->y * bcoord;
}

static gboolean
crank_shape3_cpolyhedron_face_contains_xy (CrankShape3CPolyhedron *shape,
                                           const guint             fid,
                                           CrankVecFloat2         *xy)
{
  guint *vertices;
  guint nvertices;

  CrankVecFloat3 *v[2];

  guint count = 0;

  guint i;
  guint n1;

  vertices = crank_poly_struct3_get_face_vertices (shape->pstruct, fid, &nvertices);
  n1 = nvertices - 1;

  v[0] = & g_array_index (shape->vert_pos, CrankVecFloat3, vertices[n1]);
  v[1] = & g_array_index (shape->vert_pos, CrankVecFloat3, vertices[0]);

  if ((v[0]->x - xy->x) * (v[1]->x - xy->x) < 0)
    {
      if (0 < crank_shape3_cpolyhedron_get_edge_y (v[0], v[1], xy->x))
        count++;
    }

  for (i = 1; i < nvertices; i++)
    {
      v[0] = v[1];
      v[1] = & g_array_index (shape->vert_pos, CrankVecFloat3, vertices[i]);

    if ((v[0]->x - xy->x) * (v[1]->x - xy->x) < 0)
      {
        if (0 < crank_shape3_cpolyhedron_get_edge_y (v[0], v[1], xy->x))
          count++;
      }
    }

  g_free (vertices);

  return (count & 1) == 1;
}

static gfloat
crank_shape3_cpolyhedron_get_face_z (CrankShape3CPolyhedron *shape,
                                     const guint             fid,
                                     CrankVecFloat2         *xy)
{
  guint *vertices;
  guint nvertices;
  CrankVecFloat3 bcoord;

  CrankVecFloat3 *v[3];
  CrankVecFloat2 tri[3];

  vertices = crank_poly_struct3_get_face_vertices (shape->pstruct, fid, &nvertices);

  v[0] = & g_array_index (shape->vert_pos, CrankVecFloat3, vertices[0]);
  v[1] = & g_array_index (shape->vert_pos, CrankVecFloat3, vertices[1]);
  v[2] = & g_array_index (shape->vert_pos, CrankVecFloat3, vertices[2]);

  tri[0].x = v[0]->x;
  tri[0].y = v[0]->y;
  tri[1].x = v[1]->x;
  tri[1].y = v[1]->y;
  tri[2].x = v[2]->x;
  tri[2].y = v[2]->y;

  crank_tri_bcoord (tri, xy, &bcoord);

  g_free (vertices);

  return (v[0]->z * bcoord.x) + (v[1]->z * bcoord.y) + (v[2]->z * bcoord.z);
}


void
crank_shape3_cpolyhedron_build_cache (CrankShape3CPolyhedron *shape)
{
  crank_shape3_cpolyhedron_build_bound_radius (shape);
  crank_shape3_cpolyhedron_build_face_normal (shape);
  crank_shape3_cpolyhedron_build_convex (shape);
}



void
crank_shape3_cpolyhedron_build_bound_radius (CrankShape3CPolyhedron *shape)
{
  gfloat bradius_sq;

  CrankVecFloat3 *vert;
  guint i;

  vert = & g_array_index (shape->vert_pos, CrankVecFloat3, 0);
  bradius_sq = crank_vec_float3_get_magn_sq (vert);

  for (i = 1; i < shape->vert_pos->len; i++)
    {
      gfloat bradius_sq_c;

      vert = & g_array_index (shape->vert_pos, CrankVecFloat3, i);

      bradius_sq_c = crank_vec_float3_get_magn_sq (vert);

      bradius_sq = MAX (bradius_sq, bradius_sq_c);
    }

  shape->bound_radius = sqrtf (bradius_sq);
}


void
crank_shape3_cpolyhedron_build_face_normal (CrankShape3CPolyhedron *shape)
{
  guint nfaces;
  guint i;

  nfaces = crank_poly_struct3_get_nfaces (shape->pstruct);
  g_array_set_size (shape->face_norm, nfaces);
  for (i = 0; i < nfaces; i++)
    {
      CrankVecFloat3 disp_ab;
      CrankVecFloat3 disp_bc;
      CrankVecFloat3 *norm;

      guint *fvertices;
      guint nfvertices;

      fvertices = crank_poly_struct3_get_face_vertices (shape->pstruct, i, &nfvertices);

      crank_vec_float3_sub (& g_array_index (shape->vert_pos, CrankVecFloat3, 1),
                            & g_array_index (shape->vert_pos, CrankVecFloat3, 0),
                            & disp_ab);

      crank_vec_float3_sub (& g_array_index (shape->vert_pos, CrankVecFloat3, 2),
                            & g_array_index (shape->vert_pos, CrankVecFloat3, 1),
                            & disp_bc);

      norm = & g_array_index (shape->face_norm, CrankVecFloat3, i);

      crank_vec_float3_crs (& disp_ab, & disp_bc, norm);
      crank_vec_float3_unit_self (norm);

      g_free (fvertices);
    }
}

void
crank_shape3_cpolyhedron_build_convex (CrankShape3CPolyhedron *shape)
{
  guint i, j;

  shape->convex = TRUE;
  for (i = 0; i < shape->vert_pos->len; i++)
    {
      CrankVecFloat3 *vi;

      guint *edges;
      guint nedges;

      guint *faces;
      guint nfaces;

      guint *vert_vert;

      vi = & g_array_index (shape->vert_pos, CrankVecFloat3, i);
      edges = crank_poly_struct3_get_vertex_edges (shape->pstruct, i, &nedges);
      faces = crank_poly_struct3_get_vertex_faces (shape->pstruct, i, &nfaces);
      vert_vert = g_new (guint, nedges);

      // Build vert - vert association.
      for (j = 0; j < nedges; j++)
        {
          guint everts[2];

          crank_poly_struct3_get_edge_vertices (shape->pstruct, edges[j], everts);

          vert_vert[j] = (everts[0] == i) ? everts[1] : everts[0];
        }

      // Check each vertices are behind of faces.
      for (j = 0; j < nfaces; j++)
        {
          CrankVecFloat3 *norm;

          guint k;

          norm = & g_array_index (shape->face_norm, CrankVecFloat3, j);

          for (k = 0; k < nedges; k++)
            {
              CrankVecFloat3 *vk;
              CrankVecFloat3 disp;
              gfloat dot;

              vk = & g_array_index (shape->vert_pos, CrankVecFloat3, vert_vert[k]);

              crank_vec_float3_sub (vi, vk, &disp);
              dot = crank_vec_float3_dot (norm, &disp);

              if (0.0001f < dot)
                {
                  shape->convex = FALSE;
                }
            }
          if (! shape->convex)
            break;
        }

      g_free (vert_vert);
      g_free (edges);
      g_free (faces);

      if (! shape->convex)
        break;
    }
}


//////// Constructors //////////////////////////////////////////////////////////

CrankShape3CPolyhedron*
crank_shape3_cpolyhedron_new (CrankVecFloat3   *vertices,
                              const guint       nvertices,
                              CrankPolyStruct3 *pstruct)
{
  CrankShape3CPolyhedron *self;

  self = (CrankShape3CPolyhedron*) g_object_new (CRANK_TYPE_SHAPE3_CPOLYHEDRON,
                                                 NULL);

  g_array_append_vals (self->vert_pos, vertices, nvertices);

  crank_shape3_cpolyhedron_build_cache (self);

  return self;
}



CrankShape3CPolyhedron*
crank_shape3_cpolyhedron_new_from_polyhedron (CrankShape3Polyhedron *polyhedron)
{
  CrankShape3CPolyhedron *self;

  CrankShape3Vertexed *polyhedron_vertexed;
  CrankPolyStruct3 *pstruct;

  guint i, j, n;


  self = (CrankShape3CPolyhedron*) g_object_new (CRANK_TYPE_SHAPE3_CPOLYHEDRON,
                                                 NULL);

  polyhedron_vertexed = CRANK_SHAPE3_VERTEXED (polyhedron);
  pstruct = crank_poly_struct3_new ();



  n = crank_shape3_vertexed_get_nvertices (polyhedron_vertexed);

  g_array_set_size (self->vert_pos, n);
  crank_poly_struct3_set_nvertices (pstruct, n);

  for (i = 0; i < n; i++)
    {
      CrankVecFloat3 *v = & g_array_index (self->vert_pos, CrankVecFloat3, i);

      crank_shape3_vertexed_get_vertex_pos (polyhedron_vertexed, i, v);
    }



  n = crank_shape3_vertexed_get_nedges (polyhedron_vertexed);
  for (i = 0; i < n; i++)
    {
      guint vertices[2];

      crank_shape3_vertexed_get_edge_vertices (polyhedron_vertexed, i, vertices);
      crank_poly_struct3_add_edge (pstruct, vertices[0], vertices[1]);
    }


  n = crank_shape3_vertexed_get_nfaces (polyhedron_vertexed);
  for (i = 0; i < n; i++)
    {
      guint *vertices;
      guint nvertices;

      vertices = crank_shape3_vertexed_get_face_vertices (polyhedron_vertexed, i, &nvertices);
      crank_poly_struct3_add_face_vertex_array (pstruct, vertices, nvertices);

      g_free (vertices);
    }

  self->pstruct = pstruct;

  crank_shape3_cpolyhedron_build_cache (self);

  return self;
}
