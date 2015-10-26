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
