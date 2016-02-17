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

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"

#include "crankvertexstruct.h"

/**
 * SECTION: crankvertexstruct
 * @title: Vertex Structures
 * @short_description: Structure definition for CoglPrimitives
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * This section defines vertex structures with normal attribute.
 */

//////// Public Functions //////////////////////////////////////////////////////

/**
 * crank_cogl_primitive_new_p3n3:
 * @context: A CoglContext.
 * @mode: Vertices mode.
 * @n_vertices: Number of vertices.
 * @data: (array length=n_vertices): Number of vertices.
 *
 * Constructs #CoglPrimitive with structure.
 *
 * Returns: (transfer full): Newly constructed primitive.
 */
CoglPrimitive*
crank_cogl_primitive_new_p3n3 (CoglContext           *context,
                               CoglVerticesMode       mode,
                               gint                   n_vertices,
                               const CrankVertexP3N3 *data)
{
  CoglPrimitive *primitive;

  CoglAttributeBuffer *buffer;
  CoglAttribute *attrs[2];

  buffer = cogl_attribute_buffer_new (context,
                                      n_vertices * sizeof (CrankVertexP3N3),
                                      data);

  attrs [0] = cogl_attribute_new (buffer,
                                  "cogl_position_in",
                                  sizeof (CrankVertexP3N3),
                                  G_STRUCT_OFFSET (CrankVertexP3N3, x),
                                  3,
                                  COGL_ATTRIBUTE_TYPE_FLOAT);

  attrs [1] = cogl_attribute_new (buffer,
                                  "cogl_normal_in",
                                  sizeof (CrankVertexP3N3),
                                  G_STRUCT_OFFSET (CrankVertexP3N3, nx),
                                  3,
                                  COGL_ATTRIBUTE_TYPE_FLOAT);

  primitive = cogl_primitive_new_with_attributes (mode, n_vertices, attrs, 2);

  cogl_object_unref (attrs[0]);
  cogl_object_unref (attrs[1]);

  return primitive;
}

/**
 * crank_cogl_primitive_new_p3n3c4:
 * @context: A CoglContext.
 * @mode: Vertices mode.
 * @n_vertices: Number of vertices.
 * @data: (array length=n_vertices): Number of vertices.
 *
 * Constructs #CoglPrimitive with structure.
 *
 * Returns: (transfer full): Newly constructed primitive.
 */
CoglPrimitive*
crank_cogl_primitive_new_p3n3c4 (CoglContext             *context,
                                 CoglVerticesMode         mode,
                                 gint                     n_vertices,
                                 const CrankVertexP3N3C4 *data)
{
  CoglPrimitive *primitive;

  CoglAttributeBuffer *buffer;
  CoglAttribute *attrs[3];

  buffer = cogl_attribute_buffer_new (context,
                                      n_vertices * sizeof (CrankVertexP3N3C4),
                                      data);

  attrs [0] = cogl_attribute_new (buffer,
                                  "cogl_position_in",
                                  sizeof (CrankVertexP3N3C4),
                                  G_STRUCT_OFFSET (CrankVertexP3N3C4, x),
                                  3,
                                  COGL_ATTRIBUTE_TYPE_FLOAT);

  attrs [1] = cogl_attribute_new (buffer,
                                  "cogl_normal_in",
                                  sizeof (CrankVertexP3N3C4),
                                  G_STRUCT_OFFSET (CrankVertexP3N3C4, nx),
                                  3,
                                  COGL_ATTRIBUTE_TYPE_FLOAT);

  attrs [2] = cogl_attribute_new (buffer,
                                  "cogl_color_in",
                                  sizeof (CrankVertexP3N3C4),
                                  G_STRUCT_OFFSET (CrankVertexP3N3C4, r),
                                  4,
                                  COGL_ATTRIBUTE_TYPE_UNSIGNED_BYTE);

  primitive = cogl_primitive_new_with_attributes (mode, n_vertices, attrs, 3);

  cogl_object_unref (attrs[0]);
  cogl_object_unref (attrs[1]);
  cogl_object_unref (attrs[2]);

  return primitive;
}

/**
 * crank_cogl_primitive_new_p3n3t2:
 * @context: A CoglContext.
 * @mode: Vertices mode.
 * @n_vertices: Number of vertices.
 * @data: (array length=n_vertices): Number of vertices.
 *
 * Constructs #CoglPrimitive with structure.
 *
 * Returns: (transfer full): Newly constructed primitive.
 */
CoglPrimitive*
crank_cogl_primitive_new_p3n3t2 (CoglContext             *context,
                                 CoglVerticesMode         mode,
                                 gint                     n_vertices,
                                 const CrankVertexP3N3T2 *data)
{
  CoglPrimitive *primitive;

  CoglAttributeBuffer *buffer;
  CoglAttribute *attrs[3];

  buffer = cogl_attribute_buffer_new (context,
                                      n_vertices * sizeof (CrankVertexP3N3),
                                      data);

  attrs [0] = cogl_attribute_new (buffer,
                                  "cogl_position_in",
                                  sizeof (CrankVertexP3N3T2),
                                  G_STRUCT_OFFSET (CrankVertexP3N3T2, x),
                                  3,
                                  COGL_ATTRIBUTE_TYPE_FLOAT);

  attrs [1] = cogl_attribute_new (buffer,
                                  "cogl_normal_in",
                                  sizeof (CrankVertexP3N3T2),
                                  G_STRUCT_OFFSET (CrankVertexP3N3T2, nx),
                                  3,
                                  COGL_ATTRIBUTE_TYPE_FLOAT);

  attrs [2] = cogl_attribute_new (buffer,
                                  "cogl_texcoord0_in",
                                  sizeof (CrankVertexP3N3T2),
                                  G_STRUCT_OFFSET (CrankVertexP3N3T2, s),
                                  2,
                                  COGL_ATTRIBUTE_TYPE_FLOAT);

  primitive = cogl_primitive_new_with_attributes (mode, n_vertices, attrs, 3);

  cogl_object_unref (attrs[0]);
  cogl_object_unref (attrs[1]);
  cogl_object_unref (attrs[2]);

  return primitive;
}

