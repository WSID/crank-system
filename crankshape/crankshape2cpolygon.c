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
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2polygon.h"
#include "crankshape2cpolygon.h"

/**
 * SECTION: crankshape2cpolygon
 * @title: CrankShape2CPolygon
 * @short_description: Concrete polygon representation.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This represents non-abstract polygon descriptions, with vertices and segments.
 */

//////// List of virtual functions /////////////////////////////////////////////

static gboolean                 _shape2_contains (CrankShape2    *shape,
                                                  CrankVecFloat2 *point);

static CrankShape2Polygon     *_shape2_approximate_polygon    (CrankShape2  *shape,
                                                                const gfloat  vdistance);

static CrankShape2Finite       *_shape2_finitize (CrankShape2 *shape,
                                                  CrankBox2   *box,
                                                  CrankTrans2 *position);


static guint _shape2_polygon_get_nvertices (CrankShape2Polygon *shape);

static void _shape2_polygon_get_vertex (CrankShape2Polygon *shape,
                                         guint                index,
                                         CrankVecFloat2      *vertex);


static gfloat crank_shape2_cpolygon_get_bound_radius (CrankShape2Finite *shape);


//////// Type definition ///////////////////////////////////////////////////////

/**
 * CrankShape2CPolygon:
 *
 * A Polygon shape. Please refer section description.
 */
struct _CrankShape2CPolygon {
  CrankShape2   _parent_instance;

  GArray *vertices;
};

G_DEFINE_TYPE(CrankShape2CPolygon,
                        crank_shape2_cpolygon,
                        CRANK_TYPE_SHAPE2_POLYGON)




//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_cpolygon_init (CrankShape2CPolygon *self)
{
  self->vertices = g_array_new (FALSE, FALSE, sizeof (CrankVecFloat2));
}

static void
crank_shape2_cpolygon_class_init (CrankShape2CPolygonClass *c)
{
  CrankShape2Class       *c_shape2;
  CrankShape2FiniteClass *c_shape2_finite;
  CrankShape2PolygonClass *c_shape2_polygon;

  c_shape2 = CRANK_SHAPE2_CLASS(c);

  c_shape2->approximate_polygon = _shape2_approximate_polygon;
  c_shape2->finitize = _shape2_finitize;


  c_shape2_finite = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2_finite->get_bound_radius = crank_shape2_cpolygon_get_bound_radius;


  c_shape2_polygon = CRANK_SHAPE2_POLYGON_CLASS (c);

  c_shape2_polygon->get_nvertices = _shape2_polygon_get_nvertices;
  c_shape2_polygon->get_vertex = _shape2_polygon_get_vertex;
}

//////// CrankShape2 ///////////////////////////////////////////////////////////

static gboolean
_shape2_contains (CrankShape2    *shape,
                  CrankVecFloat2 *point)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*) shape;
  guint i;

  guint pass_count = 0;

  for (i = 0; i < self->vertices->len; i++)
    {
      guint in = (i + 1) % self->vertices->len;
      CrankVecFloat2* v = &g_array_index (self->vertices, CrankVecFloat2, i);
      CrankVecFloat2* vn = &g_array_index (self->vertices, CrankVecFloat2, in);
      gboolean edge_pass;

      edge_pass = (v->x != vn->x) &&                    // Not parrael to x axis.
                  (((v->x <= point->x) && (point->x <= vn->x)) ||     // 0 in range.
                   ((v->x >= point->x) && (point->x >= vn->x)));

      if (edge_pass) pass_count++;
    }

  return pass_count % 2 != 0;
}



static CrankShape2Polygon*
_shape2_approximate_polygon (CrankShape2  *shape,
                             const gfloat  vdistance)
{
  // For now, we just return reference to self.
  return (CrankShape2Polygon*)g_object_ref (shape);
}



static CrankShape2Finite*
_shape2_finitize (CrankShape2 *shape,
                  CrankBox2   *box,
                  CrankTrans2 *position)
{
  return NULL;
}


//////// CrankShape2Finite ////////////////////////////////////////////////////

static gfloat
crank_shape2_cpolygon_get_bound_radius (CrankShape2Finite *shape)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*)shape;
  guint i;

  gfloat radius = 0;

  for (i = 0; i < self->vertices->len; i++)
    {
      gfloat radius_current =
        crank_vec_float2_get_magn (& g_array_index (self->vertices, CrankVecFloat2, i));

      radius = MAX (radius, radius_current);
    }
  return radius;
}


//////// CrankShape2Polygon ///////////////////////////////////////////////////

static guint
_shape2_polygon_get_nvertices (CrankShape2Polygon *shape)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*)shape;

  return self->vertices->len;
}


static void
_shape2_polygon_get_vertex (CrankShape2Polygon *shape,
                             guint                index,
                             CrankVecFloat2      *vertex)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*)shape;

  crank_vec_float2_copy (&g_array_index (self->vertices, CrankVecFloat2, index),
                         vertex);
}

//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_shape2_cpolygon_new:
 *
 * Constructs an empty polygon.
 *
 * After constructing, vertices can be added by
 * crank_shape2_cpolygon_insert_vertex() or crank_shape2_cpolygon_append_vertex().
 *
 * Returns: (transfer full): An empty #CrankShape2CPolygon.
 */
CrankShape2CPolygon*
crank_shape2_cpolygon_new (void)
{
  return (CrankShape2CPolygon*) g_object_new (CRANK_TYPE_SHAPE2_CPOLYGON, NULL);
}

/**
 * crank_shape2_cpolygon_new_from_vertices:
 * @vertices: (array length=nvertices): Vertices
 * @nvertices: length of @vertices.
 *
 * Construct a polygon with given vertices.
 *
 * Returns: (transfer full): An polygon.
 */
CrankShape2CPolygon*
crank_shape2_cpolygon_new_from_vertices (CrankVecFloat2 *vertices,
                                         guint           nvertices)
{
  CrankShape2CPolygon *self = crank_shape2_cpolygon_new ();
  guint i;

  for (i = 0; i < nvertices; i++ )
    crank_shape2_cpolygon_append_vertex (self, vertices + i);

  return self;
}

//////// Vertices //////////////////////////////////////////////////////////////

/**
 * crank_shape2_cpolygon_set_vertex:
 * @polygon: A Polygon.
 * @index: A Index.
 * @vertex: A Vertex.
 *
 * Sets a vertex of polygon.
 */
void
crank_shape2_cpolygon_set_vertex (CrankShape2CPolygon *polygon,
                                  guint                index,
                                  CrankVecFloat2      *vertex)
{
  crank_vec_float2_copy (vertex,
                         &g_array_index(polygon->vertices, CrankVecFloat2, index));
}

/**
 * crank_shape2_cpolygon_insert_vertex:
 * @polygon: A Polygon.
 * @index: A Index.
 * @vertex: A Vertex.
 *
 * Inserts a vertex in given position.
 */
void
crank_shape2_cpolygon_insert_vertex (CrankShape2CPolygon *polygon,
                                     guint index,
                                     CrankVecFloat2 *vertex)
{
  g_array_insert_val (polygon->vertices, index, vertex);
}

/**
 * crank_shape2_cpolygon_append_vertex:
 * @polygon: A Polygon.
 * @vertex: A Vertex.
 *
 * Appends a vertex to last position.
 */
void
crank_shape2_cpolygon_append_vertex (CrankShape2CPolygon *polygon,
                                     CrankVecFloat2      *vertex)
{
  g_array_append_val (polygon->vertices, vertex);
}

/**
 * crank_shape2_cpolygon_remove_vertex:
 * @polygon: A Polygon.
 * @index: A Index.
 *
 * Removes a vertex on given index.
 */
void
crank_shape2_cpolygon_remove_vertex (CrankShape2CPolygon *polygon,
                                     guint                index)
{
  g_array_remove_index (polygon->vertices, index);
}

