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
#include "crankshape2polygon.h"

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
 * crank_gjk2_support: (private)
 * @a: A Polygonal shape.
 * @b: A Polygonal shape.
 * @bpos: A Relative position of a and b, which contains positions of @a and @b.
 * @dir: Direction to look for.
 * @vertex: (out): A Vertex of minkowski different.
 *
 * Gets a farthest vertex of minkowski different of @a and @b.
 */
void    crank_gjk2_support (CrankShape2Polygon *a,
                            CrankShape2Polygon *b,
                            CrankTrans2        *bpos,
                            CrankVecFloat2     *dir,
                            CrankVecFloat2     *vertex);



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
crank_gjk2 (CrankShape2Polygon *a,
            CrankShape2Polygon *b,
            CrankTrans2 *bpos)
{
  return crank_gjk2_full (a, b, bpos, NULL);
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
crank_gjk2_full (CrankShape2Polygon *a,
                 CrankShape2Polygon *b,
                 CrankTrans2        *bpos,
                 CrankVecFloat2     *triangle)
{
  CrankVecFloat2 dir;
  CrankVecFloat2 dir1;

  CrankVecFloat2 seg;
  gfloat crs;

  CrankTrans2   aobjp;
  CrankTrans2   bobjp;

  CrankTrans2   brpos;

  // Check convex
  if (! (crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(a)) &&
         crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(b))))
    return FALSE;


  if (triangle == NULL)
    triangle = g_alloca ( sizeof (CrankVecFloat2) * 3 );

  // TODO: Gets position.
  crank_shape2_get_position ((CrankShape2*)a, &aobjp);
  crank_shape2_get_position ((CrankShape2*)b, &bobjp);

  crank_trans2_inverse (&aobjp, &brpos);
  if (bpos != NULL)
    crank_trans2_compose_self (&brpos, bpos);
  crank_trans2_compose_self (&brpos, &bobjp);

  //////// Build initial starting segments.
  crank_vec_float2_neg (&brpos.mtrans, &dir);
  crank_gjk2_support (a, b, &brpos, & brpos.mtrans, triangle + 0);
  crank_gjk2_support (a, b, &brpos, &dir, triangle + 1);

  crank_vec_float2_sub (triangle + 1, triangle + 0, &seg);

  if (crank_vec_float2_dot (triangle + 1, &seg) *
      crank_vec_float2_dot (triangle + 0, &seg) > 0)
    {
      crank_vec_float2_copy (triangle + 0, triangle + 2);
      return FALSE;
    }

  crs = crank_vec_float2_crs (triangle + 0, triangle + 1);

  // Loop through triangles

  while (TRUE)
    {
      CrankVecFloat2 ldir;
      gfloat crs_ca;
      gfloat crs_bc;

      crank_vec_float2_sub (triangle + 1, triangle + 0, &seg);

      if (0 < crs)
        crank_rot_vec2_left (&seg, &ldir);
      else
        crank_rot_vec2_right (&seg, &ldir);

      crank_gjk2_support (a, b, &brpos, &ldir, triangle + 2);


      if (crank_vec_float2_dot (triangle + 0, &ldir) *
          crank_vec_float2_dot (triangle + 2, &ldir) > 0)
        return FALSE;

      crs_ca = crank_vec_float2_crs (triangle + 2, triangle + 0);
      crs_bc = crank_vec_float2_crs (triangle + 1, triangle + 2);

      if (crs * crs_ca < 0)
        crank_vec_float2_copy (triangle + 2, triangle + 1);
      else if (crs * crs_bc < 0)
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
 * @init_polys: (array length=ninit_polys): Initial Polygon as array.
 * @ninit_polys: Length of @init_polys
 * @segment: (out) (optional) (array fixed-size=2): Segment of minkowski difference.
 * @normal: (out) (optional): Normal of segment.
 *
 * Performs EPA on shapes, and gets a segment as result.
 */
gfloat
crank_epa2      (CrankShape2Polygon *a,
                 CrankShape2Polygon *b,
                 CrankTrans2        *bpos,
                 CrankVecFloat2     *init_polys,
                 const guint         ninit_polys,
                 CrankVecFloat2     *segment,
                 CrankVecFloat2     *normal)
{
  CrankVecFloat2 dir;
  CrankVecFloat2 dir1;

  CrankVecFloat2 seg;
  gfloat crs;

  CrankTrans2   aobjp;
  CrankTrans2   bobjp;

  CrankTrans2   brpos;

  GArray *poly_array;

  // Check convex
  if (! (crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(a)) &&
         crank_shape2_finite_is_convex (CRANK_SHAPE2_FINITE(b))))
    return NAN;


  // TODO: Gets position.
  crank_shape2_get_position ((CrankShape2*)a, &aobjp);
  crank_shape2_get_position ((CrankShape2*)b, &bobjp);

  crank_trans2_inverse (&aobjp, &brpos);
  if (bpos != NULL)
    crank_trans2_compose_self (&brpos, bpos);
  crank_trans2_compose_self (&brpos, &bobjp);


  // Prepare simplex polygon.
  poly_array = g_array_sized_new (FALSE, FALSE, sizeof (CrankVecFloat2), ninit_polys);
  g_array_append_vals (poly_array, init_polys, ninit_polys);

  // Get winding of through cross
    {
      CrankVecFloat2 sega;
      CrankVecFloat2 segb;

      crank_vec_float2_sub (& g_array_index (poly_array, CrankVecFloat2, 0),
                            & g_array_index (poly_array, CrankVecFloat2, 1),
                            & sega);

      crank_vec_float2_sub (& g_array_index (poly_array, CrankVecFloat2, 1),
                            & g_array_index (poly_array, CrankVecFloat2, 2),
                            & segb);

      crs = crank_vec_float2_crs (&sega, &segb);
    }

  // Iterate and expand polygon.
  if (crs < 0)
    {
      while (TRUE)
        {
          // Iterate and figure out which segment is closest to origin.
          guint i;
          guint ei;
          gfloat pene;

          CrankVecFloat2 left;

          CrankVecFloat2 seg;

          CrankVecFloat2 *ptra;
          CrankVecFloat2 *ptrb;

          ptra = & g_array_index (poly_array, CrankVecFloat2, poly_array->len - 1);
          ptrb = & g_array_index (poly_array, CrankVecFloat2, 0);

          crank_vec_float2_sub (ptra, ptrb, & seg);

          crank_rot_vec2_left (& seg, & left);
          crank_vec_float2_unit_self (& left);

          ei = poly_array->len - 1;
          pene = crank_vec_float2_dot (ptra, &left);

          for (i = 0; i < poly_array->len - 1; i++)
            {
              gfloat pene_c;
              CrankVecFloat2 left_c;

              ptra = & g_array_index (poly_array, CrankVecFloat2, i);
              ptrb = & g_array_index (poly_array, CrankVecFloat2, i +1);

              crank_vec_float2_sub (ptra, ptrb, & seg);

              crank_rot_vec2_left (& seg, & left_c);
              crank_vec_float2_unit_self (& left_c);

              pene_c = crank_vec_float2_dot (ptra, &left_c);

              if (pene_c < pene)
                {
                  ei = i;
                  crank_vec_float2_copy (&left_c, &left);
                }
            }

          // Expand polygon
          CrankVecFloat2 sup;

          crank_gjk2_support (a, b, &brpos, &left, &sup);

          if (ABS (crank_vec_float2_dot (&left, &sup) - pene) < 0.0001)
            {
              if (segment != NULL)
                {
                  crank_vec_float2_copy (& g_array_index (poly_array, CrankVecFloat2, (i < poly_array->len - 1) ? i + 1 : 0),
                                         segment + 0);

                  crank_vec_float2_copy (& g_array_index (poly_array, CrankVecFloat2, i),
                                         segment + 1);
                }
              if (normal != NULL)
                {
                  crank_vec_float2_copy (&left, normal);
                }
              g_array_free (poly_array, TRUE);
              return pene;
            }
          else
            {
              g_array_insert_val (poly_array, ei, sup);
            }
        }
    }
  else
    {
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

          crank_gjk2_support (a, b, &brpos, &right, &sup);

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
    }
  g_assert_not_reached ();
  return NAN;
}


//////// Private functions /////////////////////////////////////////////////////

void
crank_gjk2_support (CrankShape2Polygon *a,
                    CrankShape2Polygon *b,
                    CrankTrans2        *bpos,
                    CrankVecFloat2     *dir,
                    CrankVecFloat2     *vertex)
{
  CrankVecFloat2 bdir;

  CrankVecFloat2 avert;
  CrankVecFloat2 bvert;
  CrankVecFloat2 abvert;

  crank_rot_vec2_rot (dir, -bpos->mrot, &bdir);
  crank_vec_float2_neg_self (&bdir);

  crank_shape2_polygon_get_farthest_vertex (a, dir, &avert);
  crank_shape2_polygon_get_farthest_vertex (b, &bdir, &bvert);

  crank_trans2_transv (bpos, &bvert, &abvert);
  crank_vec_float2_sub (&avert, &abvert, vertex);
}

