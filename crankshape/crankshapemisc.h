#ifndef CRANKSHAPEMISC_H
#define CRANKSHAPEMISC_H

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

#include <glib.h>
#include "crankbase.h"

#ifndef _CRANKSHAPE_INSIDE
#error crankshapemisc.h cannot be included directly.
#endif

G_BEGIN_DECLS

//////// Type definitions //////////////////////////////////////////////////////

/**
 * CrankWinding:
 * @CRANK_WINDING_CW: Points are winding clock-wise.
 * @CRANK_WINDING_NONE: Points are on a line.
 * @CRANK_WINDING_CCW: Points are winding counter-clock-wise.
 *
 * Windinig of points.
 */
typedef enum {
  CRANK_WINDING_CW = -1,
  CRANK_WINDING_NONE = 0,
  CRANK_WINDING_CCW = 1
} CrankWinding;

#define CRANK_TYPE_WINDING crank_winding_get_type()
GType crank_winding_get_type (void);

//////// Functions /////////////////////////////////////////////////////////////

CrankWinding crank_winding_from_points (CrankVecFloat2 *p1,
                                        CrankVecFloat2 *p2,
                                        CrankVecFloat2 *p3);

CrankWinding crank_winding_from_point_arr (CrankVecFloat2 *pts);

gboolean  crank_seg_intersect (CrankVecFloat2 *aa,
                               CrankVecFloat2 *ab,
                               CrankVecFloat2 *ba,
                               CrankVecFloat2 *bb,
                               CrankVecFloat2 *i);

void      crank_tri_bcoord   (CrankVecFloat2 *tri,
                              CrankVecFloat2 *pt,
                              CrankVecFloat3 *bcoord);

gboolean  crank_tri_contains (CrankVecFloat2 *tri,
                              CrankVecFloat2 *pt);

void      crank_tetra_bcoord (CrankVecFloat3 *tetra,
                              CrankVecFloat3 *pt,
                              CrankVecFloat4 *bcoord);

gboolean  crank_tetra_contains (CrankVecFloat3 *tetra,
                                CrankVecFloat3 *pt);


G_END_DECLS

#endif
