#ifndef CRANKSHAPEBASICS2_H
#define CRANKSHAPEBASICS2_H

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
#error crankshapebasics2.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"


/**
 * CrankSegment2
 * @p0: First point; Begining point
 * @p1: Second point; Ending point
 *
 * Represents a segment as a form of structure.
 */
typedef struct _CrankSegment2 {
  CrankVecFloat2 p0;
  CrankVecFloat2 p1;
} CrankSegment2;


/**
 * CrankTriangle2
 * @p0: First point.
 * @p1: Second point.
 * @p2: Third point.
 *
 * Represents a triangle as a form of structure.
 */
typedef struct _CrankTriangle2 {
  CrankVecFloat2 p0;
  CrankVecFloat2 p1;
  CrankVecFloat2 p2;
} CrankTriangle2;


/**
 * CrankSegment3
 * @p0: First point; Begining point
 * @p1: Second point; Ending point
 *
 * Represents a segment as a form of structure.
 */
typedef struct _CrankSegment3 {
  CrankVecFloat3 p0;
  CrankVecFloat3 p1;
} CrankSegment3;


/**
 * CrankTriangle3
 * @p0: First point.
 * @p1: Second point.
 * @p2: Third point.
 *
 * Represents a triangle as a form of structure.
 */
typedef struct _CrankTriangle3 {
  CrankVecFloat3 p0;
  CrankVecFloat3 p1;
  CrankVecFloat3 p2;
} CrankTriangle3;


/**
 * CrankTetrahedreon3
 * @p0: First point.
 * @p1: Second point.
 * @p2: Third point.
 * @p3: Fourth point.
 */
typedef struct _CrankTetrahedreon3 {
  CrankVecFloat3 p0;
  CrankVecFloat3 p1;
  CrankVecFloat3 p2;
  CrankVecFloat3 p3;
} CrankTetrahedreon3;


/**
 * CrankVoronoiSegment
 * @CRANK_VORONOI_SEG_P0: Region of #CrankSegment2.p0 or #CrankSegment3.p0
 * @CRANK_VORONOI_SEG_P1: Region of #CrankSegment2.p1 or #CrankSegment3.p1
 * @CRANK_VORONOI_SEG_LEFT: Region of left side of direction of segment.
 * @CRANK_VORONOI_SEG_RIGHT: Region of right side of direction of segment.
 * @CRANK_VORONOI_SEG_S01: Region of segment body.
 */
typedef enum {
  CRANK_VORONOI_SEG_P0,
  CRANK_VORONOI_SEG_P1,
  CRANK_VORONOI_SEG_LEFT,
  CRANK_VORONOI_SEG_RIGHT,
  CRANK_VORONOI_SEG_SEGMENT
} CrankVoronoiSegment;


/**
 * CrankVoronoiTriangle
 * @CRANK_VORONOI_TRI_P0:
 * @CRANK_VORONOI_TRI_P1:
 * @CRANK_VORONOI_TRI_P2:
 * @CRANK_VORONOI_TRI_S01:
 * @CRANK_VORONOI_TRI_S02:
 * @CRANK_VORONOI_TRI_S12:
 * @CRANK_VORONOI_TRI_IN:
 * @CRANK_VORONOI_TRI_UP:
 * @CRANK_VORONOI_TRI_DOWN:
 */
typedef enum {
  CRANK_VORONOI_TRI_P0,
  CRANK_VORONOI_TRI_P1,
  CRANK_VORONOI_TRI_P2,
  CRANK_VORONOI_TRI_S01,
  CRANK_VORONOI_TRI_S02,
  CRANK_VORONOI_TRI_S12,
  CRANK_VORONOI_TRI_IN,
  CRANK_VORONOI_TRI_UP,
  CRANK_VORONOI_TRI_DOWN
} CrankVoronoiTriangle;


#define CRANK_TYPE_SEGMENT2 crank_segment2_get_type()
GType               crank_segment2_get_type ();


void                crank_segment2_init(CrankSegment2 *seg,
                                        CrankVecFloat2 *p0,
                                        CrankVecFloat2 *p1);

void                crank_segment2_init_uv (CrankSegment2 *seg,
                                            const gfloat   p0x,
                                            const gfloat   p0y,
                                            const gfloat   p1x,
                                            const gfloat   p1y);


void                crank_segment2_copy (CrankSegment2 *seg,
                                         CrankSegment2 *other);

CrankSegment2      *crank_segment2_dup (CrankSegment2 *seg);


void                crank_segment2_get_displacement (CrankSegment2 *seg,
                                                     CrankVecFloat2 *disp);

void                crank_segment2_get_direction (CrankSegment2  *seg,
                                                  CrankVecFloat2 *dir);

void                crank_segment2_get_left (CrankSegment2  *seg,
                                             CrankVecFloat2 *left);

void                crank_segment2_get_right (CrankSegment2  *seg,
                                              CrankVecFloat2 *right);


gfloat              crank_segment2_get_length (CrankSegment2 *seg);




CrankVoronoiSegment crank_segment2_get_voronoi_region (CrankSegment2  *seg,
                                                       CrankVecFloat2 *ptr);

gfloat              crank_segment2_get_distance_from (CrankSegment2 *seg,
                                                      CrankVecFloat2 *ptr);

void                crank_segment2_get_nearest_point (CrankSegment2  *seg,
                                                      CrankVecFloat2 *ptr,
                                                      CrankVecFloat2 *near);






#endif
