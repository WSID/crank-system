#ifndef CRANKEULER_H
#define CRANKEULER_H

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
#error crankeuler.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////

typedef struct _CrankEuler CrankEuler;

#define CRANK_TYPE_EULER crank_euler_get_type ()
GType   crank_euler_get_type (void);

/**
 * CrankEuler:
 * @yaw: Yawing rotation, by Z axis.
 * @pitch: Rolling rotation, by X axis.
 * @roll: Pitching rotation, by Y axis.
 *
 * Represents Euler rotation.
 */
struct _CrankEuler {
  gfloat yaw;
  gfloat pitch;
  gfloat roll;
  guint dummy;
};

//////// Initialize functions //////////////////////////////////////////////////

void            crank_euler_init                       (CrankEuler     *euler);

void            crank_euler_init_angle                 (CrankEuler     *euler,
                                                        const gfloat    yaw,
                                                        const gfloat    pitch,
                                                        const gfloat    roll);

void            crank_euler_init_from_quaternion       (CrankEuler     *euler,
                                                        CrankQuatFloat *quat);

void            crank_euler_init_from_matrix3          (CrankEuler     *euler,
                                                        CrankMatFloat3 *mat);

void            crank_euler_init_from_matrix4          (CrankEuler     *euler,
                                                        CrankMatFloat4 *mat);



void            crank_euler_copy                       (CrankEuler     *euler,
                                                        CrankEuler     *other);

CrankEuler     *crank_euler_dup                        (CrankEuler     *euler);




void            crank_euler_to_quaternion              (CrankEuler     *euler,
                                                        CrankQuatFloat *quat);

void            crank_euler_to_matrix3                 (CrankEuler     *euler,
                                                        CrankMatFloat3 *mat);

void            crank_euler_to_matrix4                 (CrankEuler     *euler,
                                                        CrankMatFloat4 *mat);



G_END_DECLS

#endif
