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
#include "crankplane.h"

G_BEGIN_DECLS

//////// Type declaration //////////////////////////////////////////////////////


#define CRANK_TYPE_TRANS2 crank_trans2_get_type ()
GType           crank_trans2_get_type (void);

typedef struct _CrankTrans2 CrankTrans2;

/**
 * CrankTrans2:
 * @mtrans: Translation from origin.
 * @mrot: Rotation.
 * @mscl: Scale
 *
 * Represents translation.
 */
struct _CrankTrans2 {
  CrankVecFloat2        mtrans;
  gfloat                mrot;
  gfloat                mscl;
};

#define CRANK_TYPE_TRANS3 crank_trans3_get_type ()
GType           crank_trans3_get_type (void);

typedef struct _CrankTrans3 CrankTrans3;

/**
 * CrankTrans3:
 * @mtrans: Translation from origin.
 * @mrot: Rotation
 * @mscl: Scale
 *
 * Represents transformation.
 */
struct _CrankTrans3 {
  CrankVecFloat3        mtrans;
  CrankQuatFloat        mrot;
  gfloat                mscl;
};

//////// Initialization functions. /////////////////////////////////////////////////

void            crank_trans2_init              (CrankTrans2    *trans);

void            crank_trans2_init_from_matrix  (CrankTrans2    *trans,
                                                CrankMatFloat3 *mat);

void            crank_trans2_to_matrix         (CrankTrans2    *trans,
                                                CrankMatFloat3 *mat);

void            crank_trans2_to_matrix_transpose(CrankTrans2    *trans,
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


void            crank_trans2_relative_to       (CrankTrans2    *a,
                                                CrankTrans2    *b,
                                                CrankTrans2    *r);

//////// Transformation ////////////////////////////////////////////////////////

void            crank_trans2_transv            (CrankTrans2    *a,
                                                CrankVecFloat2 *b,
                                                CrankVecFloat2 *r);



//////// Initialization functions. /////////////////////////////////////////////////

void            crank_trans3_init              (CrankTrans3    *trans);

void            crank_trans3_init_from_matrix  (CrankTrans3    *trans,
                                                CrankMatFloat4 *mat);

void            crank_trans3_to_matrix         (CrankTrans3    *trans,
                                                CrankMatFloat4 *mat);

void            crank_trans3_to_matrix_transpose(CrankTrans3    *trans,
                                                 CrankMatFloat4 *mat);


void            crank_trans3_copy              (CrankTrans3    *trans,
                                                CrankTrans3    *other);

CrankTrans3    *crank_trans3_dup               (CrankTrans3    *trans);


//////// Operations ////////////////////////////////////////////////////////////

void            crank_trans3_translate         (CrankTrans3    *a,
                                                CrankVecFloat3 *b,
                                                CrankTrans3    *r);

void            crank_trans3_translate_self    (CrankTrans3    *a,
                                                CrankVecFloat3 *b);

void            crank_trans3_rotate            (CrankTrans3    *a,
                                                CrankQuatFloat *b,
                                                CrankTrans3    *r);

void            crank_trans3_rotate_self       (CrankTrans3    *a,
                                                CrankQuatFloat *b);

void            crank_trans3_scale             (CrankTrans3    *a,
                                                const gfloat    b,
                                                CrankTrans3    *r);

void            crank_trans3_scale_self        (CrankTrans3    *a,
                                                const gfloat    b);


void            crank_trans3_inverse           (CrankTrans3    *a,
                                                CrankTrans3    *r);

void            crank_trans3_inverse_self      (CrankTrans3    *a);


void            crank_trans3_compose           (CrankTrans3    *a,
                                                CrankTrans3    *b,
                                                CrankTrans3    *r);

void            crank_trans3_compose_self      (CrankTrans3    *a,
                                                CrankTrans3    *b);


void            crank_trans3_relative_to       (CrankTrans3    *a,
                                                CrankTrans3    *b,
                                                CrankTrans3    *r);


//////// Transformation ////////////////////////////////////////////////////////

void            crank_trans3_transv            (CrankTrans3    *a,
                                                CrankVecFloat3 *b,
                                                CrankVecFloat3 *r);

void            crank_trans3_trans_plane       (CrankTrans3 *a,
                                                CrankPlane3 *b,
                                                CrankPlane3 *r);

G_END_DECLS

#endif
