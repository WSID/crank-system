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

#define _CRANKSHAPE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankeuler.h"
#include "crankrotation.h"

/**
 * SECTION: crankrotation
 * @title: Rotation utility
 * @short_description: Utility functions for rotation representations.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Crank System provides 4 types of rotation representations.
 *
 * * Crank Base
 *   * #CrankQuatFloat
 *   * #CrankMatFloat3
 *   * #CrankMatFloat4
 * * Crank Shape
 *   * #CrankEuler
 *
 * Except for #CrankEuler, each rotation types provides various operations
 * like compositing rotations.
 *
 * For rotating points, matrix types are most efficient. For compositing,
 * quaternion types are efficient. For human reading, euler angles types are
 * pretty and easily understandable.
 *
 * In this section, conversion are provided between quaternions and matrices.
 */


/**
 * crank_rot_quat_float_to_mat_float3:
 * @quat: A Rotation Quaternion.
 * @mat: (out): A Rotation Matrix.
 *
 * Converts a quaternion to a matrix that represents same rotation.
 */
void
crank_rot_quat_float_to_mat_float3 (CrankQuatFloat *quat,
                                  CrankMatFloat3 *mat)
{
  gfloat ww  = quat->w * quat->w;
  gfloat xx  = quat->x * quat->x;
  gfloat yy  = quat->y * quat->y;
  gfloat zz  = quat->z * quat->z;

  gfloat wz  = quat->w * quat->z;
  gfloat xy  = quat->x * quat->y;

  gfloat wy  = quat->w * quat->y;
  gfloat xz  = quat->x * quat->z;

  gfloat wx  = quat->w * quat->x;
  gfloat yz  = quat->y * quat->z;

  mat->m00 = (ww + xx - yy - zz);
  mat->m01 = 2 * (xy - wz);
  mat->m02 = 2 * (wy + xz);

  mat->m10 = 2 * (wz + xy);
  mat->m11 = (ww - xx + yy - zz);
  mat->m12 = 2 * (yz - wx);

  mat->m20 = 2 * (xz - wy);
  mat->m21 = 2 * (wx + yz);
  mat->m22 = (ww - xx - yy + zz);

}

/**
 * crank_rot_quat_float_to_mat_float4:
 * @quat: A Rotation Quaternion.
 * @mat: (out): A Rotation Matrix.
 *
 * Converts a quaternion to a matrix that represents same rotation.
 */
void
crank_rot_quat_float_to_mat_float4 (CrankQuatFloat *quat,
                                  CrankMatFloat4 *mat)
{
  gfloat ww  = quat->w * quat->w;
  gfloat xx  = quat->x * quat->x;
  gfloat yy  = quat->y * quat->y;
  gfloat zz  = quat->z * quat->z;

  gfloat wz  = quat->w * quat->z;
  gfloat xy  = quat->x * quat->y;

  gfloat wy  = quat->w * quat->y;
  gfloat xz  = quat->x * quat->z;

  gfloat wx  = quat->w * quat->x;
  gfloat yz  = quat->y * quat->z;

  mat->m00 = (ww + xx - yy - zz);
  mat->m01 = 2 * (xy - wz);
  mat->m02 = 2 * (wy + xz);
  mat->m03 = 0;

  mat->m10 = 2 * (wz + xy);
  mat->m11 = (ww - xx + yy - zz);
  mat->m12 = 2 * (yz - wx);
  mat->m13 = 0;

  mat->m20 = 2 * (xz - wy);
  mat->m21 = 2 * (wx + yz);
  mat->m22 = (ww - xx - yy + zz);
  mat->m23 = 0;

  mat->m30 = 0;
  mat->m31 = 0;
  mat->m32 = 0;
  mat->m33 = 1;

}

/**
 * crank_rot_mat_float3_to_quat_float:
 * @mat: A Rotation Matrix.
 * @quat: (out): A Rotation Quaternion.
 *
 * Converts a matrix to a quaternion that represents same rotation.
 */
void
crank_rot_mat_float3_to_quat_float (CrankMatFloat3 *mat,
                                  CrankQuatFloat *quat)
{
  gfloat t = mat->m00 + mat->m11 + mat->m22;
  gfloat r = sqrt (1 + t);
  gfloat s = 0.5 / r;

  quat->w = 0.5 * r;
  quat->x = (mat->m21 - mat->m12) * s;
  quat->y = (mat->m02 - mat->m20) * s;
  quat->z = (mat->m10 - mat->m01) * s;
}

/**
 * crank_rot_mat_float4_to_quat_float:
 * @mat: A Rotation Matrix.
 * @quat: (out): A Rotation Quaternion.
 *
 * Converts a matrix to a quaternion that represents same rotation.
 */
void
crank_rot_mat_float4_to_quat_float (CrankMatFloat4 *mat,
                                  CrankQuatFloat *quat)
{
  gfloat t = mat->m00 + mat->m11 + mat->m22;
  gfloat r = sqrt (1 + t);
  gfloat s = 0.5 / r;

  quat->w = 0.5 * r;
  quat->x = (mat->m21 - mat->m12) * s;
  quat->y = (mat->m02 - mat->m20) * s;
  quat->z = (mat->m10 - mat->m01) * s;
}
