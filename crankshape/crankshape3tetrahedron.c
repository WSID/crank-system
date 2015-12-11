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
#include "crankshapemisc.h"
#include "crankpolystruct3.h"
#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polyhedron.h"
#include "crankshape3tpolyhedron.h"
#include "crankshape3tetrahedron.h"


//////// List of virtual functions /////////////////////////////////////////////

static gboolean crank_shape3_tetrahedron_contains (CrankShape3    *shape,
                                                   CrankVecFloat3 *point);

static gboolean crank_shape3_tetrahedron_is_convex (CrankShape3Finite *shape);

static gfloat   crank_shape3_tetrahedron_get_bound_radius (CrankShape3Finite *shape);


static CrankWinding crank_shape3_tetrahedron_get_face_winding (CrankShape3Vertexed *shape,
                                                               const guint          fid);
//////// Type definition ///////////////////////////////////////////////////////

struct _CrankShape3Tetrahedron {
  CrankShape3TPolyhedron _parent;

  CrankVecFloat3 vertices[4];
  CrankWinding   winding;
};

G_DEFINE_TYPE (CrankShape3Tetrahedron,
               crank_shape3_tetrahedron,
               CRANK_TYPE_SHAPE3_TPOLYHEDRON)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_tetrahedron_init (CrankShape3Tetrahedron *self)
{
}

static void
crank_shape3_tetrahedron_class_init (CrankShape3TetrahedronClass *c)
{
  CrankShape3Class *c_shape3 = CRANK_SHAPE3_CLASS (c);
  CrankShape3FiniteClass *c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);
  CrankShape3VertexedClass *c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);
  CrankShape3TPolyhedronClass *c_shape3tpolyhedron = CRANK_SHAPE3_TPOLYHEDRON_CLASS (c);

  CrankPolyStruct3 *pstruct;

  c_shape3->contains = crank_shape3_tetrahedron_contains;

  c_shape3finite->is_convex = crank_shape3_tetrahedron_is_convex;
  c_shape3finite->get_bound_radius = crank_shape3_tetrahedron_get_bound_radius;

  c_shape3vertexed->get_face_winding = crank_shape3_tetrahedron_get_face_winding;

  pstruct = crank_poly_struct3_new ();
  crank_poly_struct3_set_nvertices (pstruct, 4);
  crank_poly_struct3_add_edge (pstruct, 0, 1);
  crank_poly_struct3_add_edge (pstruct, 0, 2);
  crank_poly_struct3_add_edge (pstruct, 0, 3);
  crank_poly_struct3_add_edge (pstruct, 1, 2);
  crank_poly_struct3_add_edge (pstruct, 2, 3);
  crank_poly_struct3_add_edge (pstruct, 3, 1);

  crank_poly_struct3_add_face_vertices (pstruct, 3, 0, 1, 2);
  crank_poly_struct3_add_face_vertices (pstruct, 3, 0, 2, 3);
  crank_poly_struct3_add_face_vertices (pstruct, 3, 0, 3, 1);
  crank_poly_struct3_add_face_vertices (pstruct, 3, 3, 2, 1);

  crank_shape3_tpolyhedron_class_set_template (c_shape3tpolyhedron, pstruct);
}

//////// CrankShape3 ///////////////////////////////////////////////////////////

static gboolean
crank_shape3_tetrahedron_contains (CrankShape3    *shape,
                                   CrankVecFloat3 *point)
{
  CrankShape3Tetrahedron *self = (CrankShape3Tetrahedron*)shape;

  return crank_tetra_contains (self->vertices, point);
}


//////// CrankShape3Finite /////////////////////////////////////////////////////

static gboolean
crank_shape3_tetrahedron_is_convex (CrankShape3Finite *shape)
{
  return TRUE;
}


static gfloat
crank_shape3_tetrahedron_get_bound_radius (CrankShape3Finite *shape)
{
  CrankShape3Tetrahedron *self = (CrankShape3Tetrahedron*)shape;
  gfloat r[4];

  r[0] = crank_vec_float3_get_magn_sq (self->vertices + 0);
  r[1] = crank_vec_float3_get_magn_sq (self->vertices + 1);
  r[2] = crank_vec_float3_get_magn_sq (self->vertices + 2);
  r[3] = crank_vec_float3_get_magn_sq (self->vertices + 3);

  r[0] = MAX (r[0], r[1]);
  r[0] = MAX (r[0], r[2]);
  r[0] = MAX (r[0], r[3]);

  return sqrtf (r[0]);
}

//////// CrankShape3Vertexed ///////////////////////////////////////////////////


static CrankWinding
crank_shape3_tetrahedron_get_face_winding (CrankShape3Vertexed *shape,
                                           const guint          fid)
{
  CrankShape3Tetrahedron *self = (CrankShape3Tetrahedron*)shape;
  return self->winding;
}

//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_shape3_tetrahedron_new:
 * @vertices: (array fixed-size=4): Vertices.
 *
 * Constructs a tetrahedron shape.
 *
 * Returns: (transfer full): Newly constructed shape.
 */
CrankShape3Tetrahedron*
crank_shape3_tetrahedron_new (CrankVecFloat3 *vertices)
{
  CrankShape3Tetrahedron *self;

  self = (CrankShape3Tetrahedron*) g_object_new (CRANK_TYPE_SHAPE3_TETRAHEDRON,
                                                 NULL);

  memcpy (self->vertices, vertices, sizeof (CrankVecFloat3) * 4);
  self->winding = crank_winding_from_points_against (vertices + 1,
                                                     vertices + 2,
                                                     vertices + 3,
                                                     vertices + 0);

  return self;
}
