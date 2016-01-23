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

/**
 * SECTION: crankmeshutil
 * @title; Mesh Utility
 * @short_description: Mesh generation utility.
 * @stability: Unstable
 *
 * This section provides functions for generating basic meshes for various use.
 */

#define _CRANKVISUAL_INSIDE

#include <math.h>
#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"
#include "crankvertexstruct.h"


typedef gushort TriIndices[3];

//////// Private functions /////////////////////////////////////////////////////

CoglVertexP3*
crank_make_v_p3_sphere_uv (const guint  uc,
                           const guint  vc,
                           guint       *len)
{
  guint mlen;

  CoglVertexP3 *vertices;

  CoglVertexP3 *sides;

  gfloat vang_inc = G_PI / (vc + 1);
  gfloat vang_base = - G_PI_2 + vang_inc;

  gfloat uang_inc =  G_PI * 2 / uc;

  guint top_vert;

  guint j;
  guint i;


  mlen = 2 + uc * vc;
  vertices = g_new (CoglVertexP3, mlen);

  sides = vertices + 1;

  vertices[0].x = 0;
  vertices[0].y = 0;
  vertices[0].z = -1;

  for (j = 0; j < vc; j++)
    {
      CoglVertexP3 *row = sides + (uc * j);

      gfloat vang = fmaf (j, vang_inc, vang_base);
      gfloat vcos = cosf (vang);
      gfloat vsin = sinf (vang);

      for (i = 0; i < uc; i++)
        {
          gfloat uang = i * uang_inc;
          gfloat ucos = cosf (uang);
          gfloat usin = sinf (uang);

          row[i].x = ucos * vcos;
          row[i].y = usin * vcos;
          row[i].z = vsin;
        }
    }

  top_vert = uc * vc + 1;

  vertices[top_vert].x = 0;
  vertices[top_vert].y = 0;
  vertices[top_vert].z = -1;


  if (len != NULL)
    *len = mlen;

  return vertices;
}

CrankVertexP3N3*
crank_make_v_p3n3_sphere_uv (const guint  uc,
                             const guint  vc,
                             guint       *len)
{
  guint mlen;

  CrankVertexP3N3V *vertices;

  CrankVertexP3N3V *sides;

  gfloat vang_inc = G_PI / (vc + 1);
  gfloat vang_base = - G_PI_2 + vang_inc;

  gfloat uang_inc =  G_PI * 2 / uc;

  guint top_vert;

  guint j;
  guint i;


  mlen = 2 + uc * vc;
  vertices = g_new (CrankVertexP3N3V, mlen);

  sides = vertices + 1;

  crank_vec_float3_init (& vertices[0].position , 0, 0, -1);
  crank_vec_float3_copy (& vertices[0].position, & vertices[0].normal);

  for (j = 0; j < vc; j++)
    {
      CrankVertexP3N3V *row = sides + (uc * j);

      gfloat vang = fmaf (j, vang_inc, vang_base);
      gfloat vcos = cosf (vang);
      gfloat vsin = sinf (vang);
      for (i = 0; i < uc; i++)
        {
          gfloat uang = i * uang_inc;
          gfloat ucos = cosf (uang);
          gfloat usin = sinf (uang);

          crank_vec_float3_init (& row[i].position, ucos * vcos, usin * vcos, vsin);
          crank_vec_float3_copy (& row[i].position, & row[i].normal);
        }
    }

  top_vert = uc * vc + 1;

  crank_vec_float3_init (& vertices[top_vert].position , 0, 0, 1);
  crank_vec_float3_copy (& vertices[top_vert].position , & vertices[top_vert].normal);


  if (len != NULL)
    *len = mlen;

  return (CrankVertexP3N3*)vertices;
}


TriIndices*
crank_make_indices_sphere_uv (const guint  uc,
                              const guint  vc,
                              guint       *len)
{
  guint mlen;

  TriIndices *indices;

  TriIndices *sides;
  TriIndices *top;

  guint uc1 = uc - 1;
  guint vc1 = vc - 1;

  guint tstr_vert;
  guint top_vert;

  guint i;
  guint j;

  mlen = uc * 2+ (uc * vc1) * 2;
  indices = g_new (TriIndices, mlen);



  // Set bottom cap.

  for (i = 0; i < uc1; i++)
    {
      TriIndices *face = indices + i;

      face[0][0] = 0;
      face[0][1] = 1 + i;
      face[0][2] = 2 + i;
    }

  indices[uc1][0] = 0;
  indices[uc1][1] = 1;
  indices[uc1][2] = uc;


  // Set sides.
  sides = indices + uc;

  for (j = 0; j < vc1; j++)
    {
      TriIndices *row = sides + (2 * uc * j);
      guint vert_row = 1 + uc * j;

      TriIndices *face;

      guint vert;
      guint vert_u;
      guint vert_v;
      guint vert_uv;

      for (i = 0; i < uc1; i++)
        {
          face = row + (2 * i);

          guint vert = vert_row + i;
          guint vert_u = vert + 1;
          guint vert_v = vert + uc;
          guint vert_uv = vert_v + 1;

          face[0][0] = vert;
          face[0][1] = vert_u;
          face[0][2] = vert_v;
          face[1][0] = vert_u;
          face[1][1] = vert_uv;
          face[1][2] = vert_v;
        }

      face = row + (2 * uc1);

      vert = vert_row + uc1;
      vert_u = vert_row;
      vert_v = vert + uc;
      vert_uv = vert_u + uc;

      face[0][0] = vert;
      face[0][1] = vert_u;
      face[0][2] = vert_v;
      face[1][0] = vert_u;
      face[1][1] = vert_uv;
      face[1][2] = vert_v;
    }

  // Set top.
  top = indices + (2 * uc * vc1 + uc);
  tstr_vert = 1 + uc * vc1;
  top_vert = 1 + uc * vc;

  for (i = 0; i < uc1; i++)
    {
      TriIndices *face = top + i;
      face[0][0] = tstr_vert + i;
      face[0][1] = tstr_vert + i + 1;
      face[0][2] = top_vert;
    }

  top[uc1][0] = tstr_vert + uc1;
  top[uc1][1] = tstr_vert;
  top[uc1][2] = top_vert;

  if (len != NULL)
    *len = mlen;

  return indices;
}



//////// Public functions //////////////////////////////////////////////////////

CoglPrimitive*
crank_make_mesh_sphere_uv_p3 (CoglContext *context,
                              const guint  uc,
                              const guint  vc)
{
  CoglPrimitive *primitive;

  CoglIndices *indices;

  CoglVertexP3 *vdata;
  TriIndices *idata;

  guint lvdata;
  guint lidata;

  vdata = crank_make_v_p3_sphere_uv (uc, vc, &lvdata);
  idata = crank_make_indices_sphere_uv (uc, vc, &lidata);

  indices = cogl_indices_new (context, COGL_INDICES_TYPE_UNSIGNED_SHORT,
                              idata, lidata * 3);

  primitive = cogl_primitive_new_p3 (context,
                                     COGL_VERTICES_MODE_TRIANGLES,
                                     lvdata,
                                     vdata);

  cogl_primitive_set_indices (primitive, indices, lvdata);

  cogl_object_unref (indices);

  g_free (vdata);
  g_free (idata);

  return primitive;
}

CoglPrimitive*
crank_make_mesh_sphere_uv_p3n3 (CoglContext *context,
                                const guint  uc,
                                const guint  vc)
{
  CoglPrimitive *primitive;

  CoglIndices *indices;

  CrankVertexP3N3 *vdata;
  TriIndices      *idata;

  guint lvdata;
  guint lidata;

  vdata = crank_make_v_p3n3_sphere_uv (uc, vc, &lvdata);
  idata = crank_make_indices_sphere_uv (uc, vc, &lidata);


  indices = cogl_indices_new (context, COGL_INDICES_TYPE_UNSIGNED_SHORT,
                              idata, lidata * 3);

  primitive = crank_cogl_primitive_new_p3n3 (context,
                                             COGL_VERTICES_MODE_TRIANGLES,
                                             lvdata,
                                             vdata);

  cogl_primitive_set_indices (primitive, indices, lidata * 3);

  cogl_object_unref (indices);

  g_free (vdata);
  g_free (idata);

  return primitive;
}
