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

typedef enum _CrankEulerType CrankEulerType;

typedef struct _CrankEuler CrankEuler;

#define CRANK_TYPE_EULER_TYPE crank_euler_type_get_type ()
GType   crank_euler_type_get_type (void);

#define CRANK_TYPE_EULER crank_euler_get_type ()
GType   crank_euler_get_type (void);

/**
 * CrankEulerType:
 * @CRANK_EULER_INVALID: Indicates an invalid type.
 * @CRANK_EULER_IN_ZYX: Tait-Bryan angle type of z y' x''
 *
 * Indicates type of euler angles, for which axes are rotated.
 *
 * Prefix indicates intrinsic and extrinsic types.
 *  * IN: Intrinsic
 *  * EX: Extrinsic
 */
enum _CrankEulerType {
  // Tait-Bryan Angles in intrinsic rotations.
  CRANK_EULER_INVALID,
  CRANK_EULER_IN_ZYX,
  CRANK_EULER_IN_YXZ,
  CRANK_EULER_IN_XZY,

  CRANK_EULER_IN_XYZ,
  CRANK_EULER_IN_ZXY,
  CRANK_EULER_IN_YZX,

  // Proper Euler Angles in intrinsic rotations.
  CRANK_EULER_IN_XYX,
  CRANK_EULER_IN_YZY,
  CRANK_EULER_IN_ZXZ,

  CRANK_EULER_IN_YXY,
  CRANK_EULER_IN_ZYZ,
  CRANK_EULER_IN_XZX,

  // Tait-Bryan Angles in extrinsic rotations.
  CRANK_EULER_EX_XYZ = -CRANK_EULER_IN_ZYX,
  CRANK_EULER_EX_ZXY = -CRANK_EULER_IN_YXZ,
  CRANK_EULER_EX_YZX = -CRANK_EULER_IN_XZY,

  CRANK_EULER_EX_ZYX = -CRANK_EULER_IN_XYZ,
  CRANK_EULER_EX_YXZ = -CRANK_EULER_IN_ZXY,
  CRANK_EULER_EX_XZY = -CRANK_EULER_IN_YZX,

  // Proper Euler Angles in extrinsic rotations.
  CRANK_EULER_EX_XYX = -CRANK_EULER_IN_XYX,
  CRANK_EULER_EX_YZY = -CRANK_EULER_IN_YZY,
  CRANK_EULER_EX_ZXZ = -CRANK_EULER_IN_ZXZ,

  CRANK_EULER_EX_YXY = -CRANK_EULER_IN_YXY,
  CRANK_EULER_EX_ZYZ = -CRANK_EULER_IN_ZYZ,
  CRANK_EULER_EX_XZX = -CRANK_EULER_IN_XZX
};


/**
 * CrankEuler:
 * @angle1: First rotation angle.
 * @angle2: Second rotation angle.
 * @angle3: Third rotation angle.
 * @etype: Type of euler angles.
 *
 * Represents Euler rotation.
 */
struct _CrankEuler {
  gfloat angle1;
  gfloat angle2;
  gfloat angle3;
  CrankEulerType etype;
};

//////// Initialize functions //////////////////////////////////////////////////

void            crank_euler_init                       (CrankEuler     *euler);

void            crank_euler_init_identity              (CrankEuler     *euler,
                                                        CrankEulerType  etype);

void            crank_euler_init_angle                 (CrankEuler     *euler,
                                                        const gfloat    angle1,
                                                        const gfloat    angle2,
                                                        const gfloat    angle3,
                                                        CrankEulerType  etype);

void            crank_euler_init_from_quaternion       (CrankEuler     *euler,
                                                        CrankQuatFloat *quat,
                                                        CrankEulerType  etype);

void            crank_euler_init_from_matrix3          (CrankEuler     *euler,
                                                        CrankMatFloat3 *mat,
                                                        CrankEulerType  etype);

void            crank_euler_init_from_matrix4          (CrankEuler     *euler,
                                                        CrankMatFloat4 *mat,
                                                        CrankEulerType  etype);



void            crank_euler_copy                       (CrankEuler     *euler,
                                                        CrankEuler     *other);

CrankEuler     *crank_euler_dup                        (CrankEuler     *euler);




void            crank_euler_to_quaternion              (CrankEuler     *euler,
                                                        CrankQuatFloat *quat);

void            crank_euler_to_matrix3                 (CrankEuler     *euler,
                                                        CrankMatFloat3 *mat);

void            crank_euler_to_matrix4                 (CrankEuler     *euler,
                                                        CrankMatFloat4 *mat);



/* TODO: Add declared functions in comment block.

void            crank_euler_transform                  (CrankEuler     *euler,
                                                        CrankEuler     *other);

 */



G_END_DECLS

#endif
