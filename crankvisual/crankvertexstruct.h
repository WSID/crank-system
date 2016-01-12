#ifndef CRANKVERTEXSTRUCT_H
#define CRANKVERTEXSTRUCT_H

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

#ifndef _CRANKVISUAL_INSIDE
#error crankrendermodule.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"

//////// Type Declaration //////////////////////////////////////////////////////

/**
 * CrankVertexP3N3
 * @x: X component of position attribute.
 * @y: Y component of position attribute.
 * @z: Z component of position attribute.
 * @nx: X component of normal attribute.
 * @ny: Y component of normal attribute.
 * @nz: Z component of normal attribute.
 *
 * A structure to hold position and normal information.
 */
typedef struct _CrankVertexP3N3 {
  gfloat  x;
  gfloat  y;
  gfloat  z;

  gfloat  nx;
  gfloat  ny;
  gfloat  nz;
} CrankVertexP3N3;

/**
 * CrankVertexP3N3C4
 * @x: X component of position attribute.
 * @y: Y component of position attribute.
 * @z: Z component of position attribute.
 * @nx: X component of normal attribute.
 * @ny: Y component of normal attribute.
 * @nz: Z component of normal attribute.
 * @r: Red component of color attribute.
 * @g: Green component of color attribute.
 * @b: Blue component of color attribute.
 * @a: Alpha component of color attribute.
 *
 * A structure to hold position and normal, and color information.
 */
typedef struct _CrankVertexP3N3C4 {
  gfloat  x;
  gfloat  y;
  gfloat  z;

  gfloat  nx;
  gfloat  ny;
  gfloat  nz;

  guint8  r;
  guint8  g;
  guint8  b;
  guint8  a;
} CrankVertexP3N3C4;

/**
 * CrankVertexP3N3T2
 * @x: X component of position attribute.
 * @y: Y component of position attribute.
 * @z: Z component of position attribute.
 * @nx: X component of normal attribute.
 * @ny: Y component of normal attribute.
 * @nz: Z component of normal attribute.
 * @s: S component of texture coordinate attribute.
 * @t: T component of texture coordinate attribute.
 *
 * A structure to hold position and normal, and texture coordinate information.
 */
typedef struct _CrankVertexP3N3T2 {
  gfloat  x;
  gfloat  y;
  gfloat  z;

  gfloat  nx;
  gfloat  ny;
  gfloat  nz;

  gfloat  s;
  gfloat  t;
} CrankVertexP3N3T2;


//////// Alternative Type Declarations /////////////////////////////////////////
/**
 * CrankVertexP3N3V:
 * @position: Position attribute.
 * @normal: Normal attribute.
 *
 * Alternative struct declaration of #CrankVertexP3N3
 */
typedef struct _CrankVertexP3N3V {
  CrankVecFloat3 position;
  CrankVecFloat3 normal;
} CrankVertexP3N3V;

/**
 * CrankVertexP3N3C4V:
 * @position: Position attribute.
 * @normal: Normal attribute.
 * @r: Red component of color attribute.
 * @g: Green component of color attribute.
 * @b: Blue component of color attribute.
 * @a: Alpha component of color attribute.
 *
 * Alternative struct declaration of #CrankVertexP3N3C4
 */
typedef struct _CrankVertexP3N3C4V {
  CrankVecFloat3 position;
  CrankVecFloat3 normal;

  guint8  r;
  guint8  g;
  guint8  b;
  guint8  a;
} CrankVertexP3N3C4V;

/**
 * CrankVertexP3N3T2V:
 * @position: Position attribute.
 * @normal: Normal attribute.
 * @texcoord: Texture coordinate attribute.
 *
 * Alternative struct declaration of #CrankVertexP3N3T2
 */
typedef struct _CrankVertexP3N3T2V {
  CrankVecFloat3 position;
  CrankVecFloat3 normal;
  CrankVecFloat2 texcoord;
} CrankVertexP3N3T2V;


//////// Public Functions //////////////////////////////////////////////////////

CoglPrimitive  *crank_cogl_primitive_new_p3n3 (CoglContext           *context,
                                               CoglVerticesMode       mode,
                                               gint                   n_vertices,
                                               const CrankVertexP3N3 *data);

CoglPrimitive  *crank_cogl_primitive_new_p3n3c4 (CoglContext             *context,
                                                 CoglVerticesMode         mode,
                                                 gint                     n_vertices,
                                                 const CrankVertexP3N3C4 *data);

CoglPrimitive  *crank_cogl_primitive_new_p3n3t2 (CoglContext             *context,
                                                 CoglVerticesMode         mode,
                                                 gint                     n_vertices,
                                                 const CrankVertexP3N3T2 *data);

#endif
