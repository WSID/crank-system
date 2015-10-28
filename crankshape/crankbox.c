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
#include "crankbox.h"

/**
 * SECTION: crankbox
 * @title: Box Types.
 * @short_descroption: Box shaped vector range representations.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Represents box shaped range for #CrankVecFloat2.
 *
 * As it represents range, this has similarities to [ranges][crank-Range-of-primitives]
 */

//////// Type Definitions //////////////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankBox2, crank_box2, crank_box2_dup, g_free)

//////// Public Functions //////////////////////////////////////////////////////

/**
 * crank_box2_init:
 * @box: (out): A Box.
 * @start: A Start of box.
 * @end: A End of box.
 *
 * Initialize a box with @start and @end.
 */
void
crank_box2_init (CrankBox2      *box,
                 CrankVecFloat2 *start,
                 CrankVecFloat2 *end)
{
  crank_vec_float2_copy (start, & box->start);
  crank_vec_float2_copy (end,   & box->end);
}

/**
 * crank_box2_init_uvec:
 * @box: (out): A Box.
 * @start_x: X Coord of start.
 * @start_y: Y Coord of start.
 * @end_x: X Coord of end.
 * @end_y: Y Coord of end.
 *
 * Initialize a box with start and end.
 */
void
crank_box2_init_uvec (CrankBox2    *box,
                      const gfloat  start_x,
                      const gfloat  start_y,
                      const gfloat  end_x,
                      const gfloat  end_y)
{
  box->start.x = start_x;
  box->start.y = start_y;
  box->end.x = end_x;
  box->end.y = end_y;
}

/**
 * crank_box2_init_range:
 * @box: (out): A Box.
 * @x: Range of x coord.
 * @y: Range of y coord.
 *
 * Initialize a box with range of each coordination.
 */
void
crank_box2_init_range (CrankBox2     *box,
                       CrankRanFloat *x,
                       CrankRanFloat *y)
{
  box->start.x = x->start;
  box->start.y = y->start;
  box->end.x = x->end;
  box->end.y = y->end;
}

/**
 * crank_box2_init_unit:
 * @box: (out): A Box.
 *
 * Initialize a unit box with 1x1 size.
 */
void
crank_box2_init_unit (CrankBox2 *box)
{
  box->start.x = 0;
  box->start.y = 0;
  box->end.x = 1;
  box->end.y = 1;
}

/**
 * crank_box2_copy:
 * @box: A Box.
 * @other: (out): Another box.
 *
 * Copies a box.
 */
void
crank_box2_copy (CrankBox2 *box,
                 CrankBox2 *other)
{
  crank_vec_float2_copy (& box->start, & other->start);
  crank_vec_float2_copy (& box->end, & other->end);
}

/**
 * crank_box2_dup:
 * @box: A Box.
 *
 * Duplicates a boxed type.
 *
 * Returns: (transfer full): Duplicated box.
 */
CrankBox2*
crank_box2_dup (CrankBox2 *box)
{
  CrankBox2 *result = g_new (CrankBox2, 1);
  crank_box2_copy (box, result);
  return result;
}

/**
 * crank_box2_has_inf:
 * @box: A Box.
 *
 * Checks whether box has infinite.
 *
 * Returns: Whether box has infinite.
 */
gboolean
crank_box2_has_inf (CrankBox2 *box)
{
  return isinff (box->start.x) ||
         isinff (box->start.y) ||
         isinff (box->end.x) ||
         isinff (box->end.y);
}


/**
 * crank_box2_has_nan:
 * @box: A Box.
 *
 * Checks whether box has NaN.
 *
 * Returns: Whether box has NaN.
 */
gboolean
crank_box2_has_nan (CrankBox2 *box)
{
  return isnanf (box->start.x) ||
         isnanf (box->start.y) ||
         isnanf (box->end.x) ||
         isnanf (box->end.y);
}



/**
 * crank_box2_get_x:
 * @box: A Box.
 * @x: (out): Range of x coord.
 *
 * Gets range of x of box.
 */
void
crank_box2_get_x (CrankBox2     *box,
                  CrankRanFloat *x)
{
  x->start = box->start.x;
  x->end = box->end.x;
}

/**
 * crank_box2_get_y:
 * @box: A Box.
 * @y: (out): Range of y coord.
 *
 * Gets range of y of box.
 */
void
crank_box2_get_y (CrankBox2     *box,
                  CrankRanFloat *y)
{
  y->start = box->start.y;
  y->end = box->end.y;
}

/**
 * crank_box2_get_dimen:
 * @box: A Box.
 * @dimen: (out):
 *
 * Gets dimension of @box. This is analogy to crank_ran_float_get_length()
 */
void
crank_box2_get_dimen (CrankBox2      *box,
                      CrankVecFloat2 *dimen)
{
  crank_vec_float2_sub (& box->end, & box->start, dimen);
}

/**
 * crank_box2_get_diaglen:
 * @box: A Box.
 *
 * Gets length of diagonal line.
 *
 * Returns: Length of diagonal line.
 */
gfloat
crank_box2_get_diaglen (CrankBox2 *box)
{
  CrankVecFloat2 dimen;
  crank_box2_get_dimen (box, &dimen);
  return crank_vec_float2_get_magn (&dimen);
}



/**
 * crank_box2_contains:
 * @box: A Box.
 * @value: Value to check.
 *
 * Checks @value is in @box.
 *
 * Returns: Whether @value is in @box.
 */
gboolean
crank_box2_contains (CrankBox2      *box,
                     CrankVecFloat2 *value)
{
  return (box->start.x < value->x) && (value->x < box->end.x) &&
         (box->start.y < value->y) && (value->y < box->end.y);
}

/**
 * crank_box2_get:
 * @box: A Box.
 * @index: A Index.
 * @res: (out): A Result value.
 *
 * Gets value of @box at @index. As box is 2 dimensional, @index is also vector.
 * Index {0, 0} for @box->start, index {1, 1} for @box->end.
 *
 * If @index is out of a box [0, 1] x [0, 1], the value also out of @box.
 */
void
crank_box2_get (CrankBox2      *box,
                CrankVecFloat2 *index,
                CrankVecFloat2 *res)
{
  res->x = (box->end.x * index->x) + (box->start.x * (1 - index->x));
  res->y = (box->end.y * index->y) + (box->start.y * (1 - index->y));
}

/**
 * crank_box2_index_of:
 * @box: A Box.
 * @value: A Value to get index.
 * @index: (out): A Index.
 *
 * Gets index of @value. As value is 2 dimensional, @index is alos vector.
 *
 * If @value is out of @box, @index also out of a box [0, 1] x [0, 1].
 */
void
crank_box2_index_of (CrankBox2      *box,
                     CrankVecFloat2 *value,
                     CrankVecFloat2 *index)
{
  CrankVecFloat2 dimen;
  CrankVecFloat2 mval;

  crank_box2_get_dimen (box, &dimen);
  crank_vec_float2_sub (value, & box->start, & mval);
  crank_vec_float2_cmpdiv (& mval, & dimen, index);
}

/**
 * crank_box2_clamp:
 * @box: A Box.
 * @value: A Value to clamp.
 * @res: (out): A Clamped value.
 *
 * Clamp a value in @box by component wise.
 *
 * Clamped value is on edge or vertex, at least.
 */
void
crank_box2_clamp (CrankBox2      *box,
                  CrankVecFloat2 *value,
                  CrankVecFloat2 *res)
{
  res->x = MAX(box->start.x, value->x);
  res->x = MIN(box->end.x, res->x);

  res->y = MAX(box->start.y, value->y);
  res->y = MIN(box->end.y, res->y);
}

/**
 * crank_box2_get_intersection:
 * @box: A Box.
 * @other: A other box.
 * @intersect: (out): Intersection.
 *
 * Get intersecion of two items. If two does not intersect, %FALSE will be
 * returned, and @intersect will be set to [0, 0] x [0, 0]
 *
 * Returns: Whether two boxes has intersection, and @intersect has been set.
 */
gboolean
crank_box2_get_intersection (CrankBox2 *box,
                             CrankBox2 *other,
                             CrankBox2 *intersect)
{
  CrankRanFloat box_x;
  CrankRanFloat other_x;

  CrankRanFloat box_y;
  CrankRanFloat other_y;

  CrankRanFloat ix;
  CrankRanFloat iy;

  gboolean      result;

  crank_box2_get_x (box, &box_x);
  crank_box2_get_x (other, &other_x);
  crank_box2_get_y (box, &box_y);
  crank_box2_get_y (other, &other_y);

  result = crank_ran_float_intersection (&box_x, &other_x, &ix) &&
           crank_ran_float_intersection (&box_y, &other_y, &iy);

  if (intersect != NULL)
    crank_box2_init_range (intersect, &ix, &iy);

  return result;
}
