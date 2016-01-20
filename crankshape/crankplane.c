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
#include "crankplane.h"


//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankPlane3,
                     crank_plane3,
                     crank_plane3_dup,
                     g_free);


//////// CrankPlane3 Functions /////////////////////////////////////////////////

/**
 * crank_plane3_init:
 * @plane: (out): A Plane.
 * @anchor: A anchor point on a plane.
 * @normal: A Normal in positive direction.
 *
 * Initialize a #CrankPlane3.
 */
void
crank_plane3_init (CrankPlane3    *plane,
                   const CrankVecFloat3 *anchor,
                   const CrankVecFloat3 *normal)
{
  plane->dist_origin = crank_vec_float3_dot (normal, anchor);
  crank_vec_float3_unit (normal, & plane->normal);
}

/**
 * crank_plane3_copy:
 * @plane: A Plane.
 * @other: (out): Another plane.
 *
 * Copy a #CrankPlane3.
 */
void
crank_plane3_copy (const CrankPlane3 *plane,
                   CrankPlane3       *other)
{
  other->dist_origin = plane->dist_origin;
  crank_vec_float3_copy (& plane->normal, & other->normal);
}

/**
 * crank_plane3_dup:
 * @plane: A Plane.
 *
 * Duplicates a #CrankPlane3 structure.
 *
 * Returns: (transfer full): Duplicated structure.
 */
CrankPlane3*
crank_plane3_dup (const CrankPlane3 *plane)
{
  CrankPlane3 *result = g_new (CrankPlane3, 1);
  crank_plane3_copy (plane, result);
  return result;
}

/**
 * crank_plane3_get_distance:
 * @plane: A Plane.
 * @point: A Point.
 *
 * Gets signed distance of point from plane.
 */
gfloat
crank_plane3_get_distance (const CrankPlane3    *plane,
                           const CrankVecFloat3 *point)
{
  gfloat dot_point = crank_vec_float3_dot (& plane->normal, point);
  return dot_point - plane->dist_origin;
}



