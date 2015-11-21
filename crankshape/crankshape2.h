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
 * CrankShape2:
 *
 * Structure for 2D shape representations.
 */

/**
 * CrankShape2Class:
 * @contains: Slot for crank_shape2_contains()
 * @finitize: Slot for crank_shape2_finitize()
 *
 * Virtual Function table and signal handler table for shape class.
 */
struct _CrankShape2Class {
  /* <private> */
  GObjectClass          _parent_class;

  /* <public> */
  //Geometric property

  gboolean            (*contains) (CrankShape2    *shape,
                                   CrankVecFloat2 *point);


  /* <private> */
  gpointer _PADDING1;
  gpointer _PADDING2;
  gpointer _PADDING3;


  /* <public> */
  // Reduce to finite shapes.

  GList              *(*finitize)            (CrankShape2  *shape,
                                              CrankBox2    *box);
  /* <private> */
  gpointer _PADDING5;
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


void                    crank_shape2_get_rel_position  (CrankShape2    *shape,
                                                        CrankTrans2    *origin_rel_pos,
                                                        CrankShape2    *other,
                                                        CrankTrans2    *res);



//////// Geometric stuff ///////////////////////////////////////////////////////

gboolean                crank_shape2_contains          (CrankShape2    *shape,
                                                        CrankVecFloat2 *point);


//////// Reduce to finite shapes ///////////////////////////////////////////////

GList                  *crank_shape2_finitize          (CrankShape2 *shape,
                                                        CrankBox2   *box);


G_END_DECLS

#endif 
