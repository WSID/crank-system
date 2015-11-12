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
 * @bpos: Relative position of @a and @b.
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
 * @bpos: Relative position of @a and @b.
 * @triangle: (out caller-allocate) (array fixed-size=3) (optional): A Triangle.
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
  crank_trans2_compose_self (&brpos, bpos);
  crank_trans2_compose_self (&brpos, &bobjp);

  //////// Build initial starting segments.
  crank_vec_float2_neg (&bpos->mtrans, &dir);
  crank_gjk2_support (a, b, bpos, & bpos->mtrans, triangle + 0);
  crank_gjk2_support (a, b, bpos, &dir, triangle + 1);

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

      crank_gjk2_support (a, b, bpos, &ldir, triangle + 2);

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

  crank_rot_vec2_rot (dir, bpos->mrot, &bdir);
  crank_vec_float2_neg_self (&bdir);

  crank_shape2_polygon_get_farthest_vertex (a, dir, &avert);
  crank_shape2_polygon_get_farthest_vertex (b, &bdir, &bvert);

  crank_trans2_transv (bpos, &bvert, &abvert);

  crank_vec_float2_sub (&avert, &abvert, vertex);
}

