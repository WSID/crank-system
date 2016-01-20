#ifndef CRANKPLANE_H
#define CRANKPLANE_H

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

#ifndef _CRANKSHAPE_INSIDE
#error crankbox.h cannot be included directly: include crankshape.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

/**
 * CrankPlane3:
 * @anchor: Anchor point for plane.
 * @normal: Normal in positive direction.
 * @dot_anchor: Dot product result of @anchor and @normal.
 *
 * Represents an infinite plane in 3D Space. This structure holds additional
 * precomputed value for faster computation.
 */
typedef struct _CrankPlane3
{
  CrankVecFloat3  anchor;
  CrankVecFloat3  normal;

  gfloat          dot_anchor;
} CrankPlane3;

#define CRANK_TYPE_PLANE3 (crank_plane3_get_type ())
GType crank_plane3_get_type(void);



//////// Public Functions //////////////////////////////////////////////////////

void        crank_plane3_init (CrankPlane3          *plane,
                               const CrankVecFloat3 *anchor,
                               const CrankVecFloat3 *normal);

void        crank_plane3_copy (const CrankPlane3 *plane,
                               CrankPlane3       *other);

CrankPlane3 *crank_plane3_dup (const CrankPlane3 *plane);




gfloat    crank_plane3_get_distance (const CrankPlane3    *plane,
                                     const CrankVecFloat3 *point);


G_END_DECLS

#endif
