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

#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2vertexed.h"
#include "crankshape2polygon.h"
#include "crankshape2rect.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polyhedron.h"
#include "crankshape3cuboid.h"

/**
 * SECTION: crankshape3cuboid
 * @title: CrankShape3Cuboid
 * @short_description: Cuboid Shape.
 * @stability: unstable
 * @include: crankshape.h
 *
 * Represents a cuboid shape.
 */

//////// List of virtual functions /////////////////////////////////////////////

static void     crank_shape3_cuboid_get_property         (GObject    *object,
                                                          guint       prop_id,
                                                          GValue     *value,
                                                          GParamSpec *pspec);

static void     crank_shape3_cuboid_set_property         (GObject      *object,
                                                          guint         prop_id,
                                                          const GValue *value,
                                                          GParamSpec   *pspec);


static gboolean crank_shape3_cuboid_contains             (CrankShape3    *shape,
                                                          CrankVecFloat3 *pos);

static gfloat   crank_shape3_cuboid_get_bound_radius     (CrankShape3Finite *shape);

static gboolean crank_shape3_cuboid_is_convex            (CrankShape3Finite *shape);


static void     crank_shape3_cuboid_get_vertex_pos       (CrankShape3Vertexed *shape,
                                                          const guint          vid,
                                                          CrankVecFloat3      *pos);

static CrankWinding crank_shape3_cuboid_get_face_winding (CrankShape3Vertexed *shape,
                                                          const guint          fid);

static CrankShape2Polygon *crank_shape3_cuboid_get_face_as_shape(CrankShape3Vertexed *shape,
                                                                 const guint          fid,
                                                                 CrankTrans3         *pos);

static guint    crank_shape3_cuboid_get_farthest_vertex  (CrankShape3Vertexed *shape,
                                                          CrankVecFloat3      *dir);


static void     crank_shape3_cuboid_get_face_normal (CrankShape3Polyhedron *shape,
                                                     const guint            fid,
                                                     CrankVecFloat3        *nor);

static guint    crank_shape3_cuboid_get_normal_face (CrankShape3Polyhedron *shape,
                                                     CrankVecFloat3        *nor);

//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_SIZE,
  PROP_WIDTH,
  PROP_HEIGHT,
  PROP_DEPTH,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankShape3Cuboid {
  CrankShape3TPolyhedron _parent;

  CrankVecFloat3          hsize;
};

G_DEFINE_TYPE (CrankShape3Cuboid,
               crank_shape3_cuboid,
               CRANK_TYPE_SHAPE3_TPOLYHEDRON);


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_cuboid_init (CrankShape3Cuboid *self)
{
}


static void
crank_shape3_cuboid_class_init (CrankShape3CuboidClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankShape3Class *c_shape3 = CRANK_SHAPE3_CLASS (c);
  CrankShape3FiniteClass *c_shape3finite = CRANK_SHAPE3_FINITE_CLASS (c);
  CrankShape3VertexedClass *c_shape3vertexed = CRANK_SHAPE3_VERTEXED_CLASS (c);
  CrankShape3PolyhedronClass *c_shape3polyhedron = CRANK_SHAPE3_POLYHEDRON_CLASS (c);
  CrankShape3TPolyhedronClass *c_shape3tpolyhedron = CRANK_SHAPE3_TPOLYHEDRON_CLASS (c);

  CrankPolyStruct3 *pstruct = crank_poly_struct3_new ();

  c_gobject->get_property = crank_shape3_cuboid_get_property;
  c_gobject->set_property = crank_shape3_cuboid_set_property;

  pspecs[PROP_SIZE] = g_param_spec_boxed ("size", "size", "size of cuboid",
                                          CRANK_TYPE_VEC_FLOAT3,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_WIDTH] = g_param_spec_float ("width", "width", "width or size in x-coordination.",
                                           0, G_MAXFLOAT, 1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_HEIGHT] = g_param_spec_float ("height", "height", "height or size in y-coordination.",
                                           0, G_MAXFLOAT, 1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_DEPTH] = g_param_spec_float ("depth", "depth", "depth or size in z-coordination.",
                                           0, G_MAXFLOAT, 1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_shape3->contains = crank_shape3_cuboid_contains;


  c_shape3finite->is_convex = crank_shape3_cuboid_is_convex;
  c_shape3finite->get_bound_radius = crank_shape3_cuboid_get_bound_radius;


  c_shape3vertexed->get_vertex_pos = crank_shape3_cuboid_get_vertex_pos;
  c_shape3vertexed->get_face_winding = crank_shape3_cuboid_get_face_winding;
  c_shape3vertexed->get_face_as_shape = crank_shape3_cuboid_get_face_as_shape;
  c_shape3vertexed->get_farthest_vertex = crank_shape3_cuboid_get_farthest_vertex;


  c_shape3polyhedron->get_face_normal = crank_shape3_cuboid_get_face_normal;
  c_shape3polyhedron->get_normal_face = crank_shape3_cuboid_get_normal_face;


  crank_poly_struct3_set_nvertices (pstruct, 8);

  crank_poly_struct3_add_edge (pstruct, 0, 1);
  crank_poly_struct3_add_edge (pstruct, 1, 2);
  crank_poly_struct3_add_edge (pstruct, 2, 3);
  crank_poly_struct3_add_edge (pstruct, 3, 0);
  crank_poly_struct3_add_edge (pstruct, 0, 4);
  crank_poly_struct3_add_edge (pstruct, 1, 5);
  crank_poly_struct3_add_edge (pstruct, 2, 6);
  crank_poly_struct3_add_edge (pstruct, 3, 7);
  crank_poly_struct3_add_edge (pstruct, 4, 5);
  crank_poly_struct3_add_edge (pstruct, 5, 6);
  crank_poly_struct3_add_edge (pstruct, 6, 7);
  crank_poly_struct3_add_edge (pstruct, 7, 8);

  crank_poly_struct3_add_face_vertices (pstruct, 4, 0, 1, 2, 3);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 0, 4, 5, 1);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 1, 5, 6, 2);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 2, 6, 7, 3);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 3, 7, 4, 0);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 7, 6, 5, 4);

  crank_shape3_tpolyhedron_class_set_template (c_shape3tpolyhedron, pstruct);

  crank_poly_struct3_unref (pstruct);
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape3_cuboid_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  CrankShape3Cuboid *self = (CrankShape3Cuboid*)object;
  CrankVecFloat3 *vf;

  switch (prop_id)
    {
    case PROP_SIZE:
      vf = g_new (CrankVecFloat3, 1);
      crank_vec_float3_muls (& self->hsize, 2.0f, vf);
      g_value_take_boxed (value, vf);
      break;

    case PROP_WIDTH:
      g_value_set_float (value, self->hsize.x * 2.0f);
      break;

    case PROP_HEIGHT:
      g_value_set_float (value, self->hsize.y * 2.0f);
      break;

    case PROP_DEPTH:
      g_value_set_float (value, self->hsize.z * 2.0f);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_shape3_cuboid_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
  CrankShape3Cuboid *self = (CrankShape3Cuboid*)object;

  switch (prop_id)
    {
    case PROP_SIZE:
      crank_shape3_cuboid_set_size (self,
                                    (CrankVecFloat3*) g_value_get_boxed (value));
      break;

    case PROP_WIDTH:
      crank_shape3_cuboid_set_width (self, g_value_get_float (value));
      break;

    case PROP_HEIGHT:
      crank_shape3_cuboid_set_height (self, g_value_get_float (value));
      break;

    case PROP_DEPTH:
      crank_shape3_cuboid_set_depth (self, g_value_get_float (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}




//////// CrankShape3 ///////////////////////////////////////////////////////////

static gboolean
crank_shape3_cuboid_contains (CrankShape3    *shape,
                              CrankVecFloat3 *pos)
{
  CrankShape3Cuboid *self = (CrankShape3Cuboid*) shape;
  CrankVecFloat3 apos = {
    ABS (pos->x),
    ABS (pos->y),
    ABS (pos->z)
  };

  return (apos.x < self->hsize.x) &&
         (apos.y < self->hsize.y) &&
         (apos.z < self->hsize.z);
}



//////// CrankShape3Finite /////////////////////////////////////////////////////

static gfloat
crank_shape3_cuboid_get_bound_radius (CrankShape3Finite *shape)
{
  CrankShape3Cuboid *self = (CrankShape3Cuboid*) shape;
  return crank_vec_float3_get_magn (& self->hsize);
}


static gboolean
crank_shape3_cuboid_is_convex (CrankShape3Finite *shape)
{
  return TRUE;
}


/////// CrankShape3Vertexed ////////////////////////////////////////////////////

static void
crank_shape3_cuboid_get_vertex_pos (CrankShape3Vertexed *shape,
                                    const guint          vid,
                                    CrankVecFloat3      *pos)
{
  CrankShape3Cuboid *self = (CrankShape3Cuboid*) shape;

  pos->z = ((vid & 4) == 0) ? self->hsize.z : - self->hsize.z;

  switch (vid & 2)
    {
    case 0:
      pos->x = self->hsize.x;
      pos->y = self->hsize.y;
      break;

    case 1:
      pos->x = - self->hsize.x;
      pos->y = self->hsize.y;
      break;

    case 2:
      pos->x = - self->hsize.x;
      pos->y = - self->hsize.y;
      break;

    case 3:
      pos->x = self->hsize.x;
      pos->y = - self->hsize.y;
      break;
    }

  crank_vec_float3_muls_self (pos, 0.5f);
}

static CrankWinding
crank_shape3_cuboid_get_face_winding (CrankShape3Vertexed *shape,
                                      const guint          fid)
{
  return CRANK_WINDING_CCW;
}

static CrankShape2Polygon*
crank_shape3_cuboid_get_face_as_shape (CrankShape3Vertexed *shape,
                                       const guint          fid,
                                       CrankTrans3         *pos)
{
  return NULL;
}


static guint
crank_shape3_cuboid_get_farthest_vertex (CrankShape3Vertexed *shape,
                                         CrankVecFloat3      *dir)
{
  guint res;

  res = (0 < dir->z) ? 0 : 4;

  if (0 < dir->x)
    res += (0 < dir->y) ? 0 : 3;
  else
    res += (0 < dir->y) ? 1 : 2;

  return res;
}


//////// CrankShape3Polyhedron /////////////////////////////////////////////////

static void
crank_shape3_cuboid_get_face_normal (CrankShape3Polyhedron *shape,
                                     const guint            fid,
                                     CrankVecFloat3        *nor)
{
  switch (fid)
    {
    case 0:
      crank_vec_float3_init (nor, 0, 0, 1);
      break;

    case 1:
      crank_vec_float3_init (nor, 0, 1, 0);
      break;

    case 2:
      crank_vec_float3_init (nor, -1, 0, 0);
      break;

    case 3:
      crank_vec_float3_init (nor, 0, -1, 0);
      break;

    case 4:
      crank_vec_float3_init (nor, 1, 0, 0);
      break;

    case 5:
      crank_vec_float3_init (nor, 0, 0, -1);
      break;

    default:
      g_warning ("Invalid face id: %u", fid);
      crank_vec_float3_init (nor, NAN, NAN, NAN);
    }
}


static guint
crank_shape3_cuboid_get_normal_face (CrankShape3Polyhedron *shape,
                                     CrankVecFloat3        *nor)
{
  CrankVecFloat3 anor = {
    ABS (nor->x),
    ABS (nor->y),
    ABS (nor->z)
  };

  if (anor.x < anor.y)
    {
      if (anor.y < anor.z)
        return (0 < nor->z) ? 0 : 5;
      else
        return (0 < nor->y) ? 1 : 3;
    }
  else
    {
      if (anor.x < anor.z)
        return (0 < nor->z) ? 0 : 5;
      else
        return (0 < nor->x) ? 4 : 2;
    }
}


//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_shape3_cuboid_new:
 * @size: Size of cuboid.
 *
 * Constructs new cuboid shape with @size.
 *
 * Returns: (transfer full): Constructed shape.
 */
CrankShape3Cuboid*
crank_shape3_cuboid_new (CrankVecFloat3 *size)
{
  return (CrankShape3Cuboid*) g_object_new (CRANK_TYPE_SHAPE3_CUBOID,
                                            "size", size,
                                            NULL);
}


/**
 * crank_shape3_cuboid_new_with_whd:
 * @width: Width of cuboid.
 * @height: Height of cuboid.
 * @depth: Depth of cuboid.
 *
 * Constructs new cuboid shape with given dimensions.
 *
 * Returns: (transfer full): Constructed shape.
 */
CrankShape3Cuboid*
crank_shape3_cuboid_new_with_whd (const gfloat width,
                                  const gfloat height,
                                  const gfloat depth)
{
  return (CrankShape3Cuboid*) g_object_new (CRANK_TYPE_SHAPE3_CUBOID,
                                            "width", width,
                                            "height", height,
                                            "depth", depth,
                                            NULL);
}


/**
 * crank_shape3_cuboid_new_cube:
 * @size: Size of cuboid.
 *
 * Constructs new cube shape with @size.
 *
 * Returns: (transfer full): Constructed shape.
 */
CrankShape3Cuboid*
crank_shape3_cuboid_new_cube (const gfloat size)
{
  return crank_shape3_cuboid_new_with_whd (size, size, size);
}


//////// Properties ////////////////////////////////////////////////////////////


/**
 * crank_shape3_cuboid_get_size:
 * @self: Cuboid shape.
 * @size: (out): Size of cuboid
 *
 * Gets size of cuboid shape.
 */
void
crank_shape3_cuboid_get_size (CrankShape3Cuboid *self,
                              CrankVecFloat3    *size)
{
  crank_vec_float3_muls (& self->hsize, 2.0f, size);
}


/**
 * crank_shape3_cuboid_set_size:
 * @self: Cuboid shape.
 * @size: Size of cuboid
 *
 * Sets size of cuboid shape.
 */
void
crank_shape3_cuboid_set_size (CrankShape3Cuboid *self,
                              CrankVecFloat3    *size)
{
  GObject *self_gobject = (GObject*)self;

  crank_vec_float3_muls (size, 0.5f, & self->hsize);

  g_object_notify (self_gobject, "bound-radius");
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_SIZE]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_WIDTH]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_HEIGHT]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_DEPTH]);
}

/**
 * crank_shape3_cuboid_get_width:
 * @self: Cuboid shape.
 *
 * Gets width of cuboid shape, which is size in x-coordination.
 *
 * Returns: Width of cuboid shape.
 */
gfloat
crank_shape3_cuboid_get_width (CrankShape3Cuboid *self)
{
  return self->hsize.x * 2;
}

/**
 * crank_shape3_cuboid_get_shape:
 * @self: Cuboid shape.
 * @width: Width of cuboid shape.
 *
 * Sets width of cuboid shape, which is size in x-coordination.
 */
void
crank_shape3_cuboid_set_width (CrankShape3Cuboid *self,
                               const gfloat       width)
{
  GObject *self_gobject = (GObject*)self;

  self->hsize.x = width * 0.5f;

  g_object_notify (self_gobject, "bound-radius");
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_SIZE]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_WIDTH]);
}

/**
 * crank_shape3_cuboid_get_height:
 * @self: Cuboid shape.
 *
 * Gets height of cuboid shape, which is size in y-coordination.
 *
 * Returns: Height of cuboid shape.
 */
gfloat
crank_shape3_cuboid_get_height (CrankShape3Cuboid *self)
{
  return self->hsize.y * 2;
}

/**
 * crank_shape3_cuboid_set_height:
 * @self: Cuboid shape.
 * @height: Height of cuboid shape.
 *
 * Sets height of cuboid shape, which is size in y-coordination.
 */
void
crank_shape3_cuboid_set_height (CrankShape3Cuboid *self,
                                const gfloat       height)
{
  GObject *self_gobject = (GObject*)self;

  self->hsize.y = height * 0.5f;

  g_object_notify (self_gobject, "bound-radius");
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_SIZE]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_HEIGHT]);
}

/**
 * crank_shape3_cuboid_get_depth:
 * @self: Cuboid shape.
 *
 * Gets depth of cuboid shape, which is size in z-coordination.
 *
 * Returns: Depth of cuboid shape.
 */
gfloat
crank_shape3_cuboid_get_depth (CrankShape3Cuboid *self)
{
  return self->hsize.z * 2;
}

/**
 * crank_shape3_cuboid_set_depth:
 * @self: Cuboid shape.
 * @depth: Depth of cuboid shape.
 *
 * Sets depth of cuboid shape, which is size in z-coordination.
 */
void
crank_shape3_cuboid_set_depth (CrankShape3Cuboid *self,
                               const gfloat       depth)
{
  GObject *self_gobject = (GObject*)self;

  self->hsize.z = depth * 0.5f;

  g_object_notify (self_gobject, "bound-radius");
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_SIZE]);
  g_object_notify_by_pspec (self_gobject, pspecs[PROP_DEPTH]);
}
