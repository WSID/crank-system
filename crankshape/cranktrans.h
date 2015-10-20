#ifndef CRANKTRANS2_H
#define CRANKTRANS2_H

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

G_BEGIN_DECLS

//////// Type declaration //////////////////////////////////////////////////////


#define CRANK_TYPE_TRANS2 crank_trans2_get_type ()
GType           crank_trans2_get_type (void);

typedef struct _CrankTrans2 CrankTrans2;

/**
 * CrankTrans2:
 * @translate: Translation from origin.
 * @rotate: Rotation.
 * @scale: Scale
 *
 * Represents translation.
 */
struct _CrankTrans2 {
  CrankVecFloat2        mtrans;
  gfloat                mrot;
  gfloat                mscl;
};

//////// Initialization functions. /////////////////////////////////////////////////

void            crank_trans2_init              (CrankTrans2    *trans);

void            crank_trans2_init_from_matrix  (CrankTrans2    *trans,
                                                CrankMatFloat3 *mat);

void            crank_trans2_to_matrix         (CrankTrans2    *trans,
                                                CrankMatFloat3 *mat);


void            crank_trans2_copy              (CrankTrans2    *trans,
                                                CrankTrans2    *other);

CrankTrans2    *crank_trans2_dup               (CrankTrans2    *trans);


//////// Operations ////////////////////////////////////////////////////////////

void            crank_trans2_translate         (CrankTrans2    *a,
                                                CrankVecFloat2 *b,
                                                CrankTrans2    *r);

void            crank_trans2_translate_self    (CrankTrans2    *a,
                                                CrankVecFloat2 *b);

void            crank_trans2_rotate            (CrankTrans2    *a,
                                                const gfloat    b,
                                                CrankTrans2    *r);

void            crank_trans2_rotate_self       (CrankTrans2    *a,
                                                const gfloat    b);

void            crank_trans2_scale             (CrankTrans2    *a,
                                                const gfloat    b,
                                                CrankTrans2    *r);

void            crank_trans2_scale_self        (CrankTrans2    *a,
                                                const gfloat    b);


void            crank_trans2_inverse           (CrankTrans2    *a,
                                                CrankTrans2    *r);

void            crank_trans2_inverse_self      (CrankTrans2    *a);


void            crank_trans2_compose           (CrankTrans2    *a,
                                                CrankTrans2    *b,
                                                CrankTrans2    *r);

void            crank_trans2_compose_self      (CrankTrans2    *a,
                                                CrankTrans2    *b);

//////// Transformation ////////////////////////////////////////////////////////

void            crank_trans2_transv            (CrankTrans2    *a,
                                                CrankVecFloat2 *b,
                                                CrankVecFloat2 *r);

G_END_DECLS

#endif
