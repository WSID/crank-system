#ifndef CRANKSHAPE3_H
#define CRANKSHAPE3_H

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
#error crankshape3.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankbox.h"
#include "cranktrans.h"



G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////


typedef struct _CrankShape3Polygon CrankShape3Polygon;
typedef struct _CrankShape3Finite CrankShape3Finite;


#define CRANK_TYPE_SHAPE3 crank_shape3_get_type ()

G_DECLARE_DERIVABLE_TYPE (CrankShape3, crank_shape3, CRANK, SHAPE3, GObject)

/**
 * CrankShape3:
 *
 * Structure for 3D shape representations.
 */

/**
 * CrankShape3Class:
 * @contains: Slot for crank_shape3_contains()
 * @finitize: Slot for crank_shape3_finitize()
 *
 * Virtual Function table and signal handler table for shape class.
 */
struct _CrankShape3Class {
  /* <private> */
  GObjectClass          _parent_class;

  /* <public> */
  //Geometric property

  gboolean            (*contains) (CrankShape3    *shape,
                                   CrankVecFloat3 *point);


  /* <private> */
  gpointer _PADDING1;
  gpointer _PADDING2;
  gpointer _PADDING3;


  /* <public> */
  // Reduce to finite shapes.

  GList              *(*finitize)            (CrankShape3  *shape,
                                              CrankBox3    *box);
  /* <private> */
  gpointer _PADDING5;
  gpointer _PADDING6;
  gpointer _PADDING7;

};





//////// Property getter / setters /////////////////////////////////////////////

void                    crank_shape3_get_position      (CrankShape3    *shape,
                                                        CrankTrans3    *position);

void                    crank_shape3_set_position      (CrankShape3    *shape,
                                                        CrankTrans3    *position);


void                    crank_shape3_get_pos_trans     (CrankShape3    *shape,
                                                        CrankVecFloat3 *trans);

void                    crank_shape3_set_pos_trans     (CrankShape3    *shape,
                                                        CrankVecFloat3 *trans);


void                    crank_shape3_get_pos_rot       (CrankShape3    *shape,
                                                        CrankQuatFloat *rot);

void                    crank_shape3_set_pos_rot       (CrankShape3    *shape,
                                                        CrankQuatFloat *rot);


gfloat                  crank_shape3_get_pos_scl       (CrankShape3    *shape);

void                    crank_shape3_set_pos_scl       (CrankShape3    *shape,
                                                        gfloat          scl);



//////// Geometric stuff ///////////////////////////////////////////////////////

gboolean                crank_shape3_contains          (CrankShape3    *shape,
                                                        CrankVecFloat3 *point);


//////// Reduce to finite shapes ///////////////////////////////////////////////

GList                  *crank_shape3_finitize          (CrankShape3 *shape,
                                                        CrankBox3   *box);


G_END_DECLS

#endif 
