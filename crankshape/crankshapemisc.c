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
#include "crankbase.h"
#include "crankshapemisc.h"

/**
 * SECTION: crankshapemisc
 * @title: Miscellnous utility functions.
 * @short_description: Utility functions used for shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This section has utility functions that helps shape processing.
 */

//////// Type Definition ///////////////////////////////////////////////////////
GType
crank_winding_get_type (void)
{
  static const GEnumValue evalue[] =
    {
        {CRANK_WINDING_CW, "CRANK_WINDING_CW", "cw"},
        {CRANK_WINDING_NONE, "CRANK_WINDING_NONE", "none"},
        {CRANK_WINDING_CCW, "CRANK_WINDING_CCW", "ccw"},
        {0, NULL, NULL}
    };

  static GType type_id = 0;

  if (type_id == 0)
    type_id = g_enum_register_static ("CrankWinding", evalue);

  return type_id;
}




//////// Public Functions //////////////////////////////////////////////////////

/**
 * crank_winding_from_points
 * @p1: A point.
 * @p2: A point.
 * @p3: A point.
 *
 * Check winding of iteration.
 *
 * Returns: Winding of iteration @p1 - @p2 - @p3
 */
CrankWinding
crank_winding_from_points (CrankVecFloat2 *p1,
                           CrankVecFloat2 *p2,
                           CrankVecFloat2 *p3)
{
  CrankVecFloat2 v2;
  CrankVecFloat2 v3;

  gfloat crs;

  crank_vec_float2_sub (p2, p1, &v2);
  crank_vec_float2_sub (p3, p1, &v3);

  crs = crank_vec_float2_crs (&v2, &v3);
  return (gint)(0 < crs) - (gint)(crs < 0);
}

/**
 * crank_winding_from_point_arr
 * @pts: (array fixed-size=3): A point.
 *
 * Check winding of iteration.
 *
 * Returns: Winding of iteration @pts[0] - @pts[1] - @pts[2]
 */
CrankWinding
crank_winding_from_point_arr (CrankVecFloat2 *pts)
{
  CrankVecFloat2 v2;
  CrankVecFloat2 v3;

  gfloat crs;

  crank_vec_float2_sub (pts + 1, pts + 0, &v2);
  crank_vec_float2_sub (pts + 2, pts + 0, &v3);

  crs = crank_vec_float2_crs (&v2, &v3);
  return (gint)(0 < crs) - (gint)(crs < 0);
}

/**
 * crank_winding_from_points_against:
 * @p1: A point.
 * @p2: A point.
 * @p3: A point.
 * @v: A point that against to.
 *
 * Check winding against @v.
 */
CrankWinding
crank_winding_from_points_against (CrankVecFloat3 *p1,
                                   CrankVecFloat3 *p2,
                                   CrankVecFloat3 *p3,
                                   CrankVecFloat3 *v)
{
  CrankVecFloat3 m[3];
  gfloat det;

  crank_vec_float3_sub (p2, p1, m + 0);
  crank_vec_float3_sub (p3, p1, m + 1);
  crank_vec_float3_sub (p1, v, m + 2);

  det = crank_mat_float3_get_det ((CrankMatFloat3*)m);
  return (gint)(0 < det) - (gint)(det < 0);
}


/**
 * crank_seg_intersect:
 * @aa: A End point of segment a.
 * @ab: Another end point of segment a.
 * @ba: A End point of another segment b.
 * @bb: Another end point of segment b.
 * @i: (optional) (out): Intersection point.
 *
 * Checks two segments are intersectng, and optionally gets intersection point.
 *
 * Returns: Whether two segments are intersecting.
 */
gboolean
crank_seg_intersect (CrankVecFloat2 *aa,
                     CrankVecFloat2 *ab,
                     CrankVecFloat2 *ba,
                     CrankVecFloat2 *bb,
                     CrankVecFloat2 *i)
{
  gfloat adx = ab->x - aa->x;
  gfloat bdx = bb->x - ba->x;

  if (i == NULL)
    i = g_alloca (sizeof (CrankVecFloat2));

  if (adx == 0)
    {
      if (bdx == 0)
        {
          return FALSE;
        }
      else
        {
          gfloat mb = (bb->y - ba->y) / bdx;

          i->x = aa->x;
          i->y = ba->y + (i->x - ba->x) * mb;

          return ((ba->x - i->x) * (bb->x - i->x) < 0) &&
                 ((aa->y - i->y) * (ab->y - i->y) < 0);
        }
    }
  else if (bdx == 0)
    {
      gfloat ma = (ab->y - aa->y) / adx;

      i->x = ba->x;
      i->y = aa->y + (i->x - aa->x) * ma;

      return ((aa->x - i->x) * (ab->x - i->x) < 0) &&
             ((ba->y - i->y) * (bb->y - i->y) < 0);
    }
  else
    {
      gfloat ma = (ab->y - aa->y) / bdx;
      gfloat mb = (bb->y - ba->y) / adx;

      gfloat b_aa_x_y = ba->y + (aa->x - ba->x) * mb;

      gfloat d_ai_x = (b_aa_x_y - aa->y) / (ma - mb);
      i->x = aa->x + d_ai_x;
      i->y = aa->y + d_ai_x * ma;

      return ((aa->x - i->x) * (ab->x - i->x) < 0) &&
             ((ba->x - i->x) * (bb->x - i->x) < 0);
    }
}

/**
 * crank_tri_bcoord:
 * @tri: (array fixed-size=3): A Triangle points.
 * @pt: A Point.
 * @bcoord: (out): A Barycentric coordination of @pt.
 *
 * Gets barycentric coordination of @pt in @tri.
 */
void
crank_tri_bcoord (CrankVecFloat2 *tri,
                  CrankVecFloat2 *pt,
                  CrankVecFloat3 *bcoord)
{
  CrankVecFloat2 v2;
  CrankVecFloat2 v3;
  CrankVecFloat2 vp;
  gfloat crs_v2v3;

  crank_vec_float2_sub (tri + 1, tri + 0, &v2);
  crank_vec_float2_sub (tri + 2, tri + 0, &v3);
  crank_vec_float2_sub (pt, tri + 0, &vp);
  crs_v2v3 = crank_vec_float2_crs (&v2, &v3);

  bcoord->y = crank_vec_float2_crs (&vp, &v3) / crs_v2v3;
  bcoord->z = crank_vec_float2_crs (&v2, &vp) / crs_v2v3;
  bcoord->x = 1 - bcoord->y - bcoord->z;
}

/**
 * crank_tri_contains:
 * @tri: (array fixed-size=3): A Triangle points.
 * @pt: A Point to check.
 *
 * Checks @pt is in a triangle defined by @tri.
 *
 * Returns: Whether @pt is in @tri.
 */
gboolean
crank_tri_contains (CrankVecFloat2 *tri,
                    CrankVecFloat2 *pt)
{
  CrankVecFloat3 bcoord;
  crank_tri_bcoord (tri, pt, &bcoord);

  return (0 < bcoord.x) && (0 < bcoord.y) && (0 < bcoord.z);
}


/**
 * crank_tetra_bcoord:
 * @tetra: (array fixed-size=4): Vertices for a tetrahedron.
 * @pt: A Point.
 * @bcoord: (out): A Barycentric coordination of @pt.
 *
 * Gets barycentric coordination of @pt in @tetra.
 */
void
crank_tetra_bcoord (CrankVecFloat3 *tetra,
                    CrankVecFloat3 *pt,
                    CrankVecFloat4 *bcoord)
{
  CrankVecFloat3 v[3];
  CrankMatFloat3 cof;
  gfloat det;

  CrankVecFloat3 vp;

  crank_vec_float3_sub (tetra + 1, tetra + 0, v + 0);
  crank_vec_float3_sub (tetra + 2, tetra + 0, v + 1);
  crank_vec_float3_sub (tetra + 3, tetra + 0, v + 2);

  crank_vec_float3_sub (pt, tetra + 0, &vp);

  crank_mat_float3_get_cof ((CrankMatFloat3*)v, &cof);
  det = crank_mat_float3_get_det ((CrankMatFloat3*)v);

  if (det == 0)
    {
      crank_vec_float4_init_fill (bcoord, NAN);
      return;
    }
  else
    {
      crank_mat_float3_mulv (&cof, &vp, (CrankVecFloat3*)(& bcoord->y));
      crank_vec_float3_divs_self ((CrankVecFloat3*)(& bcoord->y), det);
      bcoord->x = 1 - bcoord->y - bcoord->z - bcoord->w;
    }
}


/**
 * crank_tetra_contains:
 * @tetra: (array fixed-size=4): Vertices for a tetrahedron
 * @pt: A Point to check.
 *
 * Checks @pt is in a tetrahedron defined by @tetra.
 *
 * Returns: Whether @pt is in @tetra.
 */
gboolean
crank_tetra_contains (CrankVecFloat3 *tetra,
                      CrankVecFloat3 *pt)
{
  CrankVecFloat4 bcoord;
  crank_tetra_bcoord (tetra, pt, &bcoord);

  return (0 < bcoord.x) && (0 < bcoord.y) && (0 < bcoord.z) && (0 < bcoord.w);
}

