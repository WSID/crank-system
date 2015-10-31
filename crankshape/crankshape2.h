#ifndef CRANKSHAPE2_H
#define CRANKSHAPE2_H

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
#error crankshape2.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankbox.h"
#include "cranktrans.h"



G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////


typedef struct _CrankShape2Polygon CrankShape2Polygon;
typedef struct _CrankShape2Finite CrankShape2Finite;


#define CRANK_TYPE_SHAPE2 crank_shape2_get_type ()

G_DECLARE_DERIVABLE_TYPE (CrankShape2, crank_shape2, CRANK, SHAPE2, GObject)

/**
 * CrankShape2Class:
 * @approximate_polygon: Slot for crank_shape2_approximate_polygon().
 * @clip: Slot for crank_shape2_clip().
 *
 * Virtual Function table and signal handler table for shape class.
 */
struct _CrankShape2Class {
  /* <private> */
  GObjectClass          _parent_class;

  /* <public> */
  gboolean            (*contains) (CrankShape2    *shape,
                                   CrankVecFloat2 *point);


  /* <private> */
  gpointer _PADDING1;
  gpointer _PADDING2;
  gpointer _PADDING3;


  /* <public> */
  CrankShape2Polygon*(*approximate_polygon) (CrankShape2  *shape,
                                              const gfloat  vdistance);

  GList              *(*finitize)            (CrankShape2  *shape,
                                              CrankBox2    *box,
                                              CrankTrans2  *position);
  /* <private> */
  gpointer _PADDING6;
  gpointer _PADDING7;

};





//////// Property getter / setters /////////////////////////////////////////////

void                    crank_shape2_get_position      (CrankShape2    *shape,
                                                        CrankTrans2    *position);

void                    crank_shape2_set_position      (CrankShape2    *shape,
                                                        CrankTrans2    *position);


void                    crank_shape2_get_pos_trans     (CrankShape2    *shape,
                                                        CrankVecFloat2 *trans);

void                    crank_shape2_set_pos_trans     (CrankShape2    *shape,
                                                        CrankVecFloat2 *trans);


gfloat                  crank_shape2_get_pos_rot       (CrankShape2    *shape);

void                    crank_shape2_set_pos_rot       (CrankShape2    *shape,
                                                        gfloat          rot);


gfloat                  crank_shape2_get_pos_scl       (CrankShape2    *shape);

void                    crank_shape2_set_pos_scl       (CrankShape2    *shape,
                                                        gfloat          scl);



gboolean                crank_shape2_contains (CrankShape2    *shape,
                                               CrankVecFloat2 *point);


CrankShape2Polygon  *crank_shape2_approximate_polygon (CrankShape2  *shape,
                                                  const gfloat  vdistance);
//////// Reduce to finite shapes ///////////////////////////////////////////////

GList                  *crank_shape2_finitize          (CrankShape2 *shape,
                                                        CrankBox2   *box,
                                                        CrankTrans2 *position);


G_END_DECLS

#endif 
