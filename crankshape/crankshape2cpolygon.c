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

static void _shape2_ipolygon_init (CrankShape2IPolygonInterface *iface);

static CrankShape2IPolygon     *_shape2_approximate_polygon    (CrankShape2  *self,
                                                                const gfloat  vdistance);

static guint _shape2_ipolygon_get_nvertices (CrankShape2IPolygon *shape);

static void _shape2_ipolygon_get_vertex (CrankShape2IPolygon *shape,
                                         guint                index,
                                         CrankVecFloat2      *vertex);



//////// Type definition ///////////////////////////////////////////////////////

struct _CrankShape2CPolygon {
  CrankShape2   _parent_instance;

  GArray *vertices;
};

G_DEFINE_TYPE_WITH_CODE(CrankShape2CPolygon,
                        crank_shape2_cpolygon,
                        CRANK_TYPE_SHAPE2,
                        {
                          G_IMPLEMENT_INTERFACE (CRANK_TYPE_SHAPE2_IPOLYGON,
                                                 _shape2_ipolygon_init);
                        })




//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_cpolygon_init (CrankShape2CPolygon *self)
{
  self->vertices = g_array_new (FALSE, FALSE, sizeof (CrankVecFloat2));
}

static void
crank_shape2_cpolygon_class_init (CrankShape2CPolygonClass *c)
{
  CrankShape2Class*     c_shape2;

  c_shape2 = CRANK_SHAPE2_CLASS(c);

  c_shape2->approximate_polygon = _shape2_approximate_polygon;
}

static void
_shape2_ipolygon_init (CrankShape2IPolygonInterface *iface)
{
  iface->get_nvertices = _shape2_ipolygon_get_nvertices;
  iface->get_vertex = _shape2_ipolygon_get_vertex;
}



//////// CrankShape2 ///////////////////////////////////////////////////////////

static CrankShape2IPolygon*
_shape2_approximate_polygon (CrankShape2  *self,
                             const gfloat  vdistance)
{
  // For now, we just return reference to self.
  return (CrankShape2IPolygon*)g_object_ref (self);
}



//////// CrankShape2IPolygon ///////////////////////////////////////////////////

static guint
_shape2_ipolygon_get_nvertices (CrankShape2IPolygon *shape)
{
  CrankShape2CPolygon *self = (CrankShape2CPolygon*)shape;

  return self->vertices->len;
}


static void
_shape2_ipolygon_get_vertex (CrankShape2IPolygon *shape,
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

