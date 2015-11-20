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
#include "crankrotation.h"
#include "crankshapebasics.h"

/**
 * SECTION: crankshapebasics
 * @title: Shape Basics
 * @short_description: Simple shape items as structure.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Basic elemental shape as structures.
 *
 * These are used in various functions.
 */


G_DEFINE_BOXED_TYPE (CrankSegment2,
                     crank_segment2,
                     crank_segment2_dup,
                     g_free);



/**
 * crank_segment2_init:
 * @seg: (out): A Segment.
 * @p0: First point; starting point.
 * @p1: Second point; ending point.
 *
 * Initialize a segment with two points.
 */
void
crank_segment2_init (CrankSegment2  *seg,
                     CrankVecFloat2 *p0,
                     CrankVecFloat2 *p1)
{
  crank_vec_float2_copy (p0, & seg->p0);
  crank_vec_float2_copy (p1, & seg->p1);
}


/**
 * crank_segment2_init_uv:
 * @seg: (out): A Segment.
 * @p0x: X coordination of p0.
 * @p0y: Y coordination of p0.
 * @p1x: X coordination of p1.
 * @p1y: Y coordination of p1.
 *
 * Initialize a segment with coordinations.
 */
void
crank_segment2_init_uv (CrankSegment2 *seg,
                        const gfloat   p0x,
                        const gfloat   p0y,
                        const gfloat   p1x,
                        const gfloat   p1y)
{
  seg->p0.x = p0x;
  seg->p0.y = p0y;
  seg->p1.x = p1x;
  seg->p1.y = p1y;
}

/**
 * crank_segment2_copy:
 * @seg: A Segment.
 * @other: (out): A Segment.
 *
 * Copys a segment structure to @other.
 */
void
crank_segment2_copy (CrankSegment2 *seg,
                     CrankSegment2 *other)
{
  crank_vec_float2_copy (& seg->p0, & other->p0);
  crank_vec_float2_copy (& seg->p1, & other->p1);
}

/**
 * crank_segment2_dup:
 * @seg: A Segment
 *
 * Duplicates a segment structure on heap
 *
 * Returns: (transfer full): A duplicated segment.
 */
CrankSegment2*
crank_segment2_dup (CrankSegment2 *seg)
{
  CrankSegment2* result = g_new (CrankSegment2, 1);
  crank_segment2_copy (seg, result);
  return result;
}

/**
 * crank_segment2_get_displacement:
 * @seg: A Segment.
 * @disp: (out): A Displacement.
 *
 * Gets displacement of #CrankSegment2.p1 from #CrankSegment2.p0.
 */
void
crank_segment2_get_displacement (CrankSegment2 *seg,
                                 CrankVecFloat2 *disp)
{
  gchar *p0s = crank_vec_float2_to_string (& seg->p0);
  gchar *p1s = crank_vec_float2_to_string (& seg->p1);

  g_message ("\n  %s\n  %s", p0s, p1s);
  crank_vec_float2_sub (& seg->p1, & seg->p0, disp);

  g_free (p0s);
  g_free (p1s);
}

/**
 * crank_segment2_get_direction:
 * @seg: A Segment.
 * @dir: (out): A Direction.
 *
 * Gets direction of the segment, from #CrankSegment2.p0 to #CrankSegment2.p1.
 *
 * The direction will be unit vector.
 */
void
crank_segment2_get_direction (CrankSegment2 *seg,
                              CrankVecFloat2 *dir)
{
  crank_segment2_get_displacement (seg, dir);
  crank_vec_float2_unit_self (dir);
}

/**
 * crank_segment2_get_left:
 * @seg: A Segment
 * @left: (out): Left direction.
 *
 * Gets left direction of segment.
 */
void
crank_segment2_get_left (CrankSegment2   *seg,
                         CrankVecFloat2 *left)
{
  CrankVecFloat2 dir;
  crank_segment2_get_direction (seg, &dir);
  crank_rot_vec2_left (&dir, left);
}


/**
 * crank_segment2_get_right:
 * @seg: A Segment
 * @right: (out): Left direction.
 *
 * Gets right direction of segment.
 */
void
crank_segment2_get_right (CrankSegment2   *seg,
                          CrankVecFloat2 *right)
{
  CrankVecFloat2 dir;
  crank_segment2_get_direction (seg, &dir);
  crank_rot_vec2_right (&dir, right);
}

/**
 * crank_segment2_get_length:
 * @seg: A Segment.
 *
 * Gets length of segment.
 *
 * Returns: Length of segment.
 */
gfloat
crank_segment2_get_length (CrankSegment2 *seg)
{
  CrankVecFloat2 disp;
  crank_segment2_get_displacement (seg, &disp);
  return crank_vec_float2_get_magn (&disp);
}



/**
 * crank_segment2_get_voronoi_region:
 * @seg: A Segment.
 * @ptr: A Point.
 *
 * Gets voronoi region enum that @ptr belongs to.
 *
 * Returns: Voronoi region enum value.
 */
CrankVoronoiSegment
crank_segment2_get_voronoi_region (CrankSegment2  *seg,
                                   CrankVecFloat2 *ptr)
{
  CrankVecFloat2 disp;
  CrankVecFloat2 tptr;

  gfloat dot;
  gfloat disp_magn_sq;

  crank_segment2_get_displacement (seg, &disp);
  crank_vec_float2_sub (ptr, & seg->p0, &tptr);

  dot = crank_vec_float2_dot (&disp, &tptr) / crank_vec_float2_get_magn_sq (&disp);


  if (dot <= 0)
    {
      return CRANK_VORONOI_SEG_P0;
    }
  else if (1 <= dot)
    {
      return CRANK_VORONOI_SEG_P1;
    }
  else
    {
      gfloat crs = crank_vec_float2_crs (& disp, & tptr);

      return (crs < 0) ? CRANK_VORONOI_SEG_RIGHT : CRANK_VORONOI_SEG_LEFT;
    }
}

/**
 * crank_segment2_get_distance_from:
 * @seg: A Segment.
 * @ptr: A Point
 *
 * Gets distance from nearest point on the segment.
 *
 * Returns: Distance from segment.
 */
gfloat
crank_segment2_get_distance_from (CrankSegment2  *seg,
                                  CrankVecFloat2 *ptr)
{
  CrankVecFloat2 disp;
  CrankVecFloat2 tptr;

  gfloat dot;
  gfloat disp_magn_sq;

  crank_segment2_get_displacement (seg, &disp);
  crank_vec_float2_sub (ptr, & seg->p0, &tptr);

  dot = crank_vec_float2_dot (&disp, &tptr) / crank_vec_float2_get_magn_sq (&disp);


  if (dot <= 0)
    {
      return crank_vec_float2_get_magn (& tptr);
    }
  else if (1 <= dot)
    {
      crank_vec_float2_sub (ptr, & seg->p1, &tptr);
      return crank_vec_float2_get_magn (& tptr);
    }
  else
    {
      gfloat crs = crank_vec_float2_crs (& disp, & tptr) / crank_vec_float2_get_magn (&disp);
      return ABS (crs);
    }
}


/**
 * crank_segment2_get_nearest_point:
 * @seg: A Segment.
 * @ptr: A Point
 * @near: (out): A nearest point in segment.
 *
 * Gets a nearest point to ptr, in segment.
 */
void
crank_segment2_get_nearest_point (CrankSegment2  *seg,
                                 CrankVecFloat2 *ptr,
                                 CrankVecFloat2 *near)
{
  CrankVecFloat2 disp;
  CrankVecFloat2 tptr;

  gfloat dot;
  gfloat disp_magn_sq;

  crank_segment2_get_displacement (seg, &disp);
  crank_vec_float2_sub (ptr, & seg->p0, &tptr);

  dot = crank_vec_float2_dot (&disp, &tptr) / crank_vec_float2_get_magn_sq (&disp);


  if (dot <= 0)
    {
      crank_vec_float2_copy (& seg->p0, near);
    }
  else if (1 <= dot)
    {
      crank_vec_float2_copy (& seg->p1, near);
    }
  else
    {
      crank_vec_float2_muls_self (& disp, dot);
      crank_vec_float2_add (& seg->p0, & disp, near);
    }
}
