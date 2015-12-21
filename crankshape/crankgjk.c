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

#include "crankbox.h"
#include "crankrotation.h"
#include "cranktrans.h"
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2vertexed.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"

#include "crankgjk.h"

/**
 * SECTION:crankgjk
 * @title: GJK Operations
 * @short_description: Intersection detection with GJK Algorithm.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Performs GJK Algorithms on ...
 */


//////// Private functions /////////////////////////////////////////////////////

/*
 * crank_gjk_contains_zero: (private)
 * @a: (type number): A value.
 * @b: (type number): Other value
 *
 * Checks whetehr 0 is in a and b.
 *
 * Returns: Whether 0 is in between a and b.
 */
#define crank_gjk_contains_zero(a,b) (((a) * (b)) < 0)


/*
 * crank_gjk2_support: (private)
 * @a: A Polygonal shape.
 * @b: A Polygonal shape.
 * @bpos: A Relative position of a and b, which contains positions of @a and @b.
 * @dir: Direction to look for.
 * @vertex: (out): A Vertex of minkowski different.
 *
 * Gets a farthest vertex of minkowski different of @a and @b.
 */
void    crank_gjk2_support (CrankShape2Vertexed *a,
                            CrankShape2Vertexed *b,
                            CrankTrans2        *bpos,
                            CrankVecFloat2     *dir,
                            CrankVecFloat2     *vertex);
/*
 * crank_gjk2_support_point: (private)
 * @a: A Polygonal shape.
 * @b: A Polygonal shape.
 * @bpos: A Relative position of a and b, which contains positions of @a and @b.
 * @dir: Direction to look for.
 * @vertex: (out): A Vertex of minkowski different.
 * @vida: (out): Farthest vertex in @a.
 * @vidb: (out): Farthest vertex in @b.
 *
 * Gets a farthest vertex of minkowski different of @a and @b.
 *
 * This carrys additional information of which vertices are corresponds to this
 * vertex on minkowski difference.
 */
void    crank_gjk2_support_point (CrankShape2Vertexed *a,
                                  CrankShape2Vertexed *b,
                                  CrankTrans2        *bpos,
                                  CrankVecFloat2     *dir,
                                  CrankVecFloat2     *vertex,
                                  guint              *vida,
                                  guint              *vidb);


void    crank_gjk3_support (CrankShape3Vertexed *a,
                            CrankShape3Vertexed *b,
                            CrankTrans3         *bpos,
                            CrankVecFloat3      *dir,
                            CrankVecFloat3      *vertex,
                            guint               *vida,
                            guint               *vidb);



//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_gjk2:
 * @a: A Polygonal shape.
 * @b: A Polygonal shape.
 * @bpos: (nullable): Relative position of @a and @b.
 *
 * Checks whether two shapes have intersection.
 *
 * This function will only work with convex shape.
 *
 * Returns: Whether @a and @b has intersection.
 */
gboolean
crank_gjk2 (CrankShape2Vertexed *a,
            CrankShape2Vertexed *b,
            CrankTrans2 *bpos)
{
  return crank_gjk2_full (a, b, bpos, NULL);
}

/**
 * crank_gjk2_distance:
 * @a: A Polygonal shape.
 * @b: A Polygonal shape.
 * @bpos: (nullable): Relative position of @a and @b.
 *
 * Gets minimum distance between @a and @b. This is minimum possible distance
 * of points from each @a and @b.
 *
 * Returns: Minimum distance between @a and @b, or 0 if intersects, or #NAN if
 *     GJK cannot be performed.
 */
gfloat
crank_gjk2_distance (CrankShape2Vertexed *a,
                     CrankShape2Vertexed *b,
                     CrankTrans2        *bpos)
{
  CrankVecFloat2 dir;
  CrankVecFloat2 dir1;

  CrankVecFloat2 seg;

  CrankVecFloat2 ptr0;
  CrankVecFloat2 ptr1;

  // Check convex
  if (! (crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(a)) &&
         crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(b))))
    return NAN;

  //////// Build initial starting segments.
  crank_vec_float2_neg (& bpos->mtrans, &dir);
  crank_gjk2_support (a, b, bpos, & bpos->mtrans, &ptr0);
  crank_gjk2_support (a, b, bpos, &dir, &ptr1);

  crank_vec_float2_sub (&ptr1, &ptr0, &seg);

  if (crank_vec_float2_crs (&ptr0, &ptr1) < 0)
    {
      CrankVecFloat2 temp;
      crank_vec_float2_copy (&ptr0, &temp);
      crank_vec_float2_copy (&ptr1, &ptr0);
      crank_vec_float2_copy (&temp, &ptr1);
    }

  // Loop through triangles

  while (TRUE)
    {
      CrankVecFloat2 ldir;
      CrankVecFloat2 ptr2;

      gfloat dotc;
      gfloat dota;
      gfloat crs_02;
      gfloat crs_21;

      crank_vec_float2_sub (&ptr1, &ptr0, &seg);
      crank_rot_vec2_left (&seg, &ldir);
      crank_gjk2_support (a, b, bpos, &ldir, &ptr2);

      // Checks that we are closer to origin.
      dotc = crank_vec_float2_dot (&ldir, &ptr2);
      dota = crank_vec_float2_dot (&ldir, &ptr0);
      if ((dotc - dota) < 0.0001f)
        {
          if (0 < crank_vec_float2_dot (&seg, &ptr0))
            return crank_vec_float2_get_magn (&ptr0);
          else if (crank_vec_float2_dot (&seg, &ptr1) < 0)
            return crank_vec_float2_get_magn (&ptr1);

          return crank_vec_float2_crs (&ptr0, &ptr1) /
                 crank_vec_float2_get_magn (&seg);
        }

      crs_02 = crank_vec_float2_crs (&ptr0, &ptr2);
      crs_21 = crank_vec_float2_crs (&ptr2, &ptr1);

      if ((crs_02 < 0) && (crs_21 < 0))
        return -1;
      else if (crank_vec_float2_dot (&seg, &ptr2) < 0)
        crank_vec_float2_copy (&ptr2, &ptr0);
      else
        crank_vec_float2_copy (&ptr2, &ptr1);
    }
}

/**
 * crank_gjk2_closest_points:
 * @a: A Polygonal shape.
 * @b: A Polygonal shape.
 * @bpos: (nullable): Relative position of @a and @b.
 * @ptra: (out): Point on @a that closest to @b.
 * @ptrb: (out): Point on @b that closest to @a.
 *
 * Gets minimum distance between @a and @b. This is minimum possible distance
 * of points from each @a and @b.
 *
 * Returns: Minimum distance between @a and @b, or 0 if intersects, or #NAN if
 *     GJK cannot be performed.
 */
gfloat
crank_gjk2_closest_points (CrankShape2Vertexed *a,
                           CrankShape2Vertexed *b,
                           CrankTrans2        *bpos,
                           CrankVecFloat2     *ptra,
                           CrankVecFloat2     *ptrb)
{
  CrankVecFloat2 dir;
  CrankVecFloat2 dir1;

  CrankVecFloat2 seg;
  CrankVecFloat2 ptr0;
  CrankVecFloat2 ptr1;

  guint vida0;
  guint vida1;
  guint vidb0;
  guint vidb1;


  // Check convex
  if (! (crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(a)) &&
         crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(b))))
    return NAN;

  //////// Build initial starting segments.
  crank_vec_float2_neg (& bpos->mtrans, &dir);
  crank_gjk2_support_point (a, b, bpos, & bpos->mtrans, &ptr0, &vida0, &vidb0);
  crank_gjk2_support_point (a, b, bpos, &dir, &ptr1, &vida1, &vidb1);

  crank_vec_float2_sub (&ptr1, &ptr0, &seg);

  if (crank_vec_float2_crs (&ptr0, &ptr1) < 0)
    {
      CrankVecFloat2 temp;
      crank_vec_float2_copy (&ptr0, &temp);
      crank_vec_float2_copy (&ptr1, &ptr0);
      crank_vec_float2_copy (&temp, &ptr1);
    }

  // Loop through triangles

  while (TRUE)
    {
      CrankVecFloat2 ldir;
      CrankVecFloat2 ptr2;

      guint vida2;
      guint vidb2;

      gfloat dotc;
      gfloat dota;
      gfloat crs_02;
      gfloat crs_21;

      crank_vec_float2_sub (&ptr1, &ptr0, &seg);
      crank_rot_vec2_left (&seg, &ldir);
      crank_gjk2_support_point (a, b, bpos, &ldir, &ptr2, &vida2, &vidb2);

      // Checks that we are closer to origin.
      dotc = crank_vec_float2_dot (&ldir, &ptr2);
      dota = crank_vec_float2_dot (&ldir, &ptr0);
      if ((dotc - dota) < 0.0001f)
        {
          gfloat qa = crank_vec_float2_dot (&seg, &ptr0);
          gfloat qb = crank_vec_float2_dot (&seg, &ptr1);
          gfloat q;

          if (0 < qa)
            {
              crank_shape2_vertexed_get_vertex_pos (a, vida0, ptra);
              crank_shape2_vertexed_get_vertex_pos (b, vidb0, ptrb);
              return crank_vec_float2_get_magn (&ptr0);
            }
          else if (qb < 0)
            {
              crank_shape2_vertexed_get_vertex_pos (a, vida1, ptra);
              crank_shape2_vertexed_get_vertex_pos (b, vidb1, ptrb);
              return crank_vec_float2_get_magn (&ptr1);
            }
          else
            {
              CrankVecFloat2 ptra0;
              CrankVecFloat2 ptrb0;
              CrankVecFloat2 ptra1;
              CrankVecFloat2 ptrb1;
              crank_shape2_vertexed_get_vertex_pos (a, vida0, &ptra0);
              crank_shape2_vertexed_get_vertex_pos (a, vida1, &ptra1);
              crank_shape2_vertexed_get_vertex_pos (a, vidb0, &ptrb0);
              crank_shape2_vertexed_get_vertex_pos (a, vidb1, &ptrb1);

              crank_vec_float2_mixs (&ptra0, &ptra1, q, ptra);
              crank_vec_float2_mixs (&ptrb0, &ptrb1, q, ptrb);

              return crank_vec_float2_crs (&ptr0, &ptr1) /
                     crank_vec_float2_get_magn (&seg);
            }
        }

      crs_02 = crank_vec_float2_crs (&ptr0, &ptr2);
      crs_21 = crank_vec_float2_crs (&ptr2, &ptr1);

      if ((crs_02 < 0) && (crs_21 < 0))
        {
          return -1;
        }
      else if (crank_vec_float2_dot (&seg, &ptr2) < 0)
        {
          crank_vec_float2_copy (&ptr2, &ptr0);
          vida0 = vida2;
          vidb0 = vidb2;
        }
      else
        {
          crank_vec_float2_copy (&ptr2, &ptr1);
          vida1 = vida2;
          vidb1 = vidb2;
        }
    }
}


/**
 * crank_gjk2_full:
 * @a: A Polygonal shape.
 * @b: A Polygonal shape.
 * @bpos: (nullable): Relative position of @a and @b.
 * @triangle: (out caller-allocates) (array fixed-size=3) (optional): A Triangle.
 *
 * Checks whether two shapes have intersection, with resulting @triangle within
 * minkowski different.
 *
 * This function will only work with convex shape.
 *
 * This will enable various processes like EPA.
 *
 * Returns: Whether @a and @b has intersections.
 */
gboolean
crank_gjk2_full (CrankShape2Vertexed *a,
                 CrankShape2Vertexed *b,
                 CrankTrans2        *bpos,
                 CrankVecFloat2     *triangle)
{
  CrankVecFloat2 dir;
  CrankVecFloat2 dir1;

  CrankVecFloat2 seg;

  // Check convex
  if (! (crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(a)) &&
         crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(b))))
    return FALSE;


  if (triangle == NULL)
    triangle = g_alloca ( sizeof (CrankVecFloat2) * 3 );

  //////// Build initial starting segments.
  crank_vec_float2_neg (& bpos->mtrans, &dir);
  crank_gjk2_support (a, b, bpos, & bpos->mtrans, triangle + 0);
  crank_gjk2_support (a, b, bpos, &dir, triangle + 1);

  crank_vec_float2_sub (triangle + 1, triangle + 0, &seg);

  if (! crank_gjk_contains_zero (crank_vec_float2_dot (triangle + 0, &seg),
                                 crank_vec_float2_dot (triangle + 1, &seg)))
    {
      crank_vec_float2_copy (triangle + 0, triangle + 2);
      return FALSE;
    }

  if (crank_vec_float2_crs (triangle + 0, triangle + 1) < 0)
    {
      CrankVecFloat2 temp;
      crank_vec_float2_copy (triangle + 0, &temp);
      crank_vec_float2_copy (triangle + 1, triangle + 0);
      crank_vec_float2_copy (&temp, triangle + 1);
    }

  // Loop through triangles

  while (TRUE)
    {
      CrankVecFloat2 ldir;
      gfloat crs_ca;
      gfloat crs_bc;

      crank_vec_float2_sub (triangle + 1, triangle + 0, &seg);

      crank_rot_vec2_left (&seg, &ldir);

      crank_gjk2_support (a, b, bpos, &ldir, triangle + 2);


      if (! crank_gjk_contains_zero (crank_vec_float2_dot (triangle + 0, &ldir),
                                     crank_vec_float2_dot (triangle + 2, &ldir)))
        return FALSE;

      crs_ca = crank_vec_float2_crs (triangle + 2, triangle + 0);
      crs_bc = crank_vec_float2_crs (triangle + 1, triangle + 2);

      if (crs_ca < 0)
        crank_vec_float2_copy (triangle + 2, triangle + 1);
      else if (crs_bc < 0)
        crank_vec_float2_copy (triangle + 2, triangle + 0);
      else
        return TRUE;
    }
}

/**
 * crank_epa2:
 * @a: A Polygonal shape.
 * @b: A Polygonal shape.
 * @bpos: Relative position of @b from @a.
 * @triangle: (array fixed-size=3): Resulting triangle from crank_gjk2_full()
 * @segment: (out) (optional) (array fixed-size=2): Segment of minkowski difference.
 * @normal: (out) (optional): Normal of segment.
 *
 * Performs EPA on shapes, and gets a segment as result. Triangle should wind in
 * CCW.
 */
gfloat
crank_epa2      (CrankShape2Vertexed *a,
                 CrankShape2Vertexed *b,
                 CrankTrans2        *bpos,
                 CrankVecFloat2     *triangle,
                 CrankVecFloat2     *segment,
                 CrankVecFloat2     *normal)
{
  CrankVecFloat2 dir;
  CrankVecFloat2 dir1;

  CrankVecFloat2 seg;
  gfloat crs;

  GArray *poly_array;

  // Check convex
  if (! (crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(a)) &&
         crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(b))))
    return NAN;


  // Prepare simplex polygon.
  poly_array = g_array_sized_new (FALSE, FALSE, sizeof (CrankVecFloat2), 3);
  g_array_append_vals (poly_array, triangle, 3);

  // Iterate and expand polygon.
  while (TRUE)
    {
      // Iterate and figure out which segment is closest to origin.
      guint i;
      guint ei;
      gfloat pene;

      CrankVecFloat2 right;

      CrankVecFloat2 seg;

      CrankVecFloat2 *ptra;
      CrankVecFloat2 *ptrb;

      ptra = & g_array_index (poly_array, CrankVecFloat2, poly_array->len - 1);
      ptrb = & g_array_index (poly_array, CrankVecFloat2, 0);

      crank_vec_float2_sub (ptra, ptrb, & seg);

      crank_rot_vec2_right (& seg, & right);
      crank_vec_float2_unit_self (& right);

      ei = poly_array->len - 1;
      pene = crank_vec_float2_dot (ptra, &right);

      for (i = 0; i < poly_array->len - 1; i++)
        {
          gfloat pene_c;
          CrankVecFloat2 right_c;

          ptra = & g_array_index (poly_array, CrankVecFloat2, i);
          ptrb = & g_array_index (poly_array, CrankVecFloat2, i +1);

          crank_vec_float2_sub (ptra, ptrb, & seg);

          crank_rot_vec2_right (& seg, & right_c);
          crank_vec_float2_unit_self (& right_c);

          pene_c = crank_vec_float2_dot (ptra, &right_c);

          if (pene_c < pene)
            {
              ei = i;
              crank_vec_float2_copy (&right_c, &right);
            }
        }

      // Expand polygon
      CrankVecFloat2 sup;

      crank_gjk2_support (a, b, bpos, &right, &sup);

      if (ABS (crank_vec_float2_dot (&right, &sup) - pene) < 0.0001)
        {
          if (segment != NULL)
            {
              crank_vec_float2_copy (& g_array_index (poly_array, CrankVecFloat2, i),
                                     segment + 0);
              crank_vec_float2_copy (& g_array_index (poly_array, CrankVecFloat2, (i < poly_array->len - 1) ? i + 1 : 0),
                                     segment + 1);
            }
          if (normal != NULL)
            {
              crank_vec_float2_copy (&right, normal);
            }
          g_array_free (poly_array, TRUE);
          return pene;
        }
      else
        {
          g_array_insert_val (poly_array, ei, sup);
        }
    }
  g_assert_not_reached ();
  return NAN;
}

//////// Private functions /////////////////////////////////////////////////////

void
crank_gjk2_support (CrankShape2Vertexed *a,
                    CrankShape2Vertexed *b,
                    CrankTrans2        *bpos,
                    CrankVecFloat2     *dir,
                    CrankVecFloat2     *vertex)
{
  CrankVecFloat2 bdir;

  guint vida;
  guint vidb;

  CrankVecFloat2 avert;
  CrankVecFloat2 bvert;
  CrankVecFloat2 abvert;

  crank_rot_vec2_rot (dir, -bpos->mrot, &bdir);
  crank_vec_float2_neg_self (&bdir);

  vida = crank_shape2_vertexed_get_farthest_vertex (a, dir);
  vidb = crank_shape2_vertexed_get_farthest_vertex (b, &bdir);

  crank_shape2_vertexed_get_vertex_pos (a, vida, &avert);
  crank_shape2_vertexed_get_vertex_pos (b, vidb, &bvert);

  crank_trans2_transv (bpos, &bvert, &abvert);
  crank_vec_float2_sub (&avert, &abvert, vertex);
}


void
crank_gjk2_support_point (CrankShape2Vertexed *a,
                          CrankShape2Vertexed *b,
                          CrankTrans2        *bpos,
                          CrankVecFloat2     *dir,
                          CrankVecFloat2     *vertex,
                          guint              *vida,
                          guint              *vidb)
{
  CrankVecFloat2 bdir;

  CrankVecFloat2 avert;
  CrankVecFloat2 bvert;
  CrankVecFloat2 abvert;

  crank_rot_vec2_rot (dir, -bpos->mrot, &bdir);
  crank_vec_float2_neg_self (&bdir);

  *vida = crank_shape2_vertexed_get_farthest_vertex (a, dir);
  *vidb = crank_shape2_vertexed_get_farthest_vertex (b, &bdir);

  crank_shape2_vertexed_get_vertex_pos (a, *vida, &avert);
  crank_shape2_vertexed_get_vertex_pos (b, *vidb, &bvert);

  crank_trans2_transv (bpos, &bvert, &abvert);
  crank_vec_float2_sub (&avert, &abvert, vertex);
}


void
crank_gjk3_support (CrankShape3Vertexed *a,
                    CrankShape3Vertexed *b,
                    CrankTrans3         *bpos,
                    CrankVecFloat3      *dir,
                    CrankVecFloat3      *vertex,
                    guint               *vida,
                    guint               *vidb)
{
  CrankVecFloat3 bdir;

  CrankVecFloat3 avert;
  CrankVecFloat3 bvert;
  CrankVecFloat3 abvert;

  CrankQuatFloat invrot;

  crank_quat_float_conjugate (& bpos->mrot, &invrot);

  crank_quat_float_rotatev (&invrot, dir, &bdir);
  crank_vec_float3_neg_self (&bdir);

  *vida = crank_shape3_vertexed_get_farthest_vertex (a, dir);
  *vidb = crank_shape3_vertexed_get_farthest_vertex (b, &bdir);

  crank_shape3_vertexed_get_vertex_pos (a, *vida, &avert);
  crank_shape3_vertexed_get_vertex_pos (b, *vidb, &bvert);

  crank_trans3_transv (bpos, &bvert, &abvert);
  crank_vec_float3_sub (&avert, &abvert, vertex);
}

