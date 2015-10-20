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

#include <math.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankeuler.h"

/**
 * SECTION: crankeuler
 * @title: CrankEuler.
 * @short_description: Euler angle as rotation representation.
 * @stability: Unstable.
 * @include: crankshape.h
 *
 * Euler angle represents 3 rotations along specific coordination axes.
 *
 * In Crank system, this uses z-y-x Tait-Bryan Angle system.
 *
 * # #CrankEuler as Rotation representation.
 *
 * Euler angle system is intuitive for peoples, but it is slower to compose and
 * perform rotation than other representations.
 *
 * ## Condition to represent rotation.
 * Euler angle represents via 3 rotations, It always represents a rotation.
 *
 * ## Initialize by rotation.
 *
 * TODO add functions.
 *
 *
 * ## Getting rotation attributes.
 *
 * TODO add functions.
 *
 *
 * ## Rotating a #CrankVecFloat3.
 *
 * TODO add functions
 *
 *
 * ## Composited Rotations and inverted rotations.
 *
 * TODO add functions
 */

//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_BOXED_TYPE(CrankEuler, crank_euler, crank_euler_dup, g_free);


//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_euler_init:
 * @euler: (out): An euler angle.
 *
 * Initialize an identity euler angle.
 */
void
crank_euler_init (CrankEuler *euler)
{
  euler->yaw = 0;
  euler->pitch = 0;
  euler->roll = 0;
}

/**
 * crank_euler_init_angle:
 * @euler: (out): An euler angle.
 * @yaw: Yaw angle component.
 * @pitch: Pitch angle component.
 * @roll: Roll angle component.
 *
 * Initialize an euler angle with components.
 */
void
crank_euler_init_angle (CrankEuler   *euler,
                        const gfloat  yaw,
                        const gfloat  pitch,
                        const gfloat  roll)
{
  euler->yaw = yaw;
  euler->pitch = pitch;
  euler->roll = roll;
}

/**
 * crank_euler_init_from_quaternion:
 * @euler: (out): An euler angle.
 * @quat: A Quaternion represents rotation.
 *
 * Initialize an euler angle with quaternion.
 */
void
crank_euler_init_from_quaternion (CrankEuler     *euler,
                                  CrankQuatFloat *quat)
{
  euler->yaw =   atanf (    2 * (quat->w * quat->x + quat->y * quat->z) /
                       (1 - 2 * (quat->x * quat->x + quat->y * quat->y)) );

  euler->pitch = asinf (    2 * (quat->w * quat->y - quat->x * quat->z) );

  euler->roll =  atanf (    2 * (quat->w * quat->z + quat->x * quat->y) /
                       (1 - 2 * (quat->y * quat->y + quat->z * quat->z)) );
}

/**
 * crank_euler_init_from_matrix3:
 * @euler: (out): An euler angle.
 * @mat: A matrix represents a rotation.
 *
 * Initialize an euler angle with matrix.
 */
void
crank_euler_init_from_matrix3 (CrankEuler     *euler,
                               CrankMatFloat3 *mat)
{
  euler->pitch = asinf (-mat->m02);

  euler->yaw =   atan2f (-mat->m01, mat->m00);

  euler->roll =  atan2f (-mat->m12, mat->m22);
}

/**
 * crank_euler_init_from_matrix4:
 * @euler: (out): An euler angle.
 * @mat: A matrix represents a rotation.
 *
 * Initialize an euler angle with matrix.
 */
void
crank_euler_init_from_matrix4 (CrankEuler     *euler,
                               CrankMatFloat4 *mat)
{
  euler->pitch = asinf (-mat->m02);

  euler->yaw =   atan2f (-mat->m01, mat->m00);

  euler->roll =  atan2f (-mat->m12, mat->m22);
}



/**
 * crank_euler_copy:
 * @euler: An euler angle.
 * @other: (out): A copy.
 *
 * Copies an euler angle to @other.
 */
void
crank_euler_copy (CrankEuler *euler,
                  CrankEuler *other)
{
  other->pitch = euler->pitch;
  other->yaw   = euler->yaw;
  other->roll  = euler->roll;
}

/**
 * crank_euler_dup:
 * @euler: An euler angle.
 *
 * Duplicates an euler angle.
 *
 * Returns: (trnasfer full): A duplicated euler angle.
 */
CrankEuler*
crank_euler_dup (CrankEuler     *euler)
{
  CrankEuler *other = g_new (CrankEuler, 1);

  crank_euler_copy (euler, other);

  return other;
}


/**
 * crank_euler_to_quaternion:
 * @euler: An euler angle.
 * @quat: (out): A rotation quaternion.
 *
 * Converts an euler angle to rotation quaternion.
 */
void
crank_euler_to_quaternion (CrankEuler     *euler,
                           CrankQuatFloat *quat)
{
  gfloat yc, ys;
  gfloat pc, ps;
  gfloat rc, rs;

  yc = cosf (euler->yaw);
  ys = sinf (euler->yaw);

  pc = cosf (euler->pitch);
  ps = sinf (euler->pitch);

  rc = cosf (euler->roll);
  rs = sinf (euler->roll);

  quat->w = yc * pc * rc - ys * ps * rs;
  quat->x = yc * pc * rs + ys * ps * rc;
  quat->y = yc * ps * rc - ys * pc * rs;
  quat->z = yc * ps * rs + ys * pc * rc;
}

/**
 * crank_euler_to_matrix3:
 * @euler: An euler angle.
 * @mat: (out): A rotation matrix.
 *
 * Converts an euler angle to rotation matrix.
 *
 * For 4x4 matrix, use crank_euler_to_matrix4().
 */
void
crank_euler_to_matrix3 (CrankEuler     *euler,
                        CrankMatFloat3 *mat)
{
  gfloat yc, ys;
  gfloat pc, ps;
  gfloat rc, rs;

  yc = cosf (euler->yaw);
  ys = sinf (euler->yaw);

  pc = cosf (euler->pitch);
  ps = sinf (euler->pitch);

  rc = cosf (euler->roll);
  rs = sinf (euler->roll);

  mat->m00 =   yc * pc;
  mat->m01 = - ys * pc;
  mat->m02 = - ps;

  mat->m10 = ys * rc - yc * ps * rs;
  mat->m11 = yc * rc + ys * ps * rs;
  mat->m12 = - pc * rs;

  mat->m20 = ys * rs + yc * ps * rc;
  mat->m21 = yc * rs - ys * ps * rc;
  mat->m22 = pc * rc;
}

/**
 * crank_euler_to_matrix4:
 * @euler: An euler angle.
 * @mat: (out): A rotation matrix.
 *
 * Converts an euler angle to rotation matrix.
 *
 * For 3x3 matrix, use crank_euler_to_matrix3().
 */
void
crank_euler_to_matrix4 (CrankEuler     *euler,
                        CrankMatFloat4 *mat)
{
  gfloat yc, ys;
  gfloat pc, ps;
  gfloat rc, rs;

  yc = cosf (euler->yaw);
  ys = sinf (euler->yaw);

  pc = cosf (euler->pitch);
  ps = sinf (euler->pitch);

  rc = cosf (euler->roll);
  rs = sinf (euler->roll);

  mat->m00 =   yc * pc;
  mat->m01 = - ys * pc;
  mat->m02 = - ps;
  mat->m03 = 0.0f;

  mat->m10 = ys * rc - yc * ps * rs;
  mat->m11 = yc * rc + ys * ps * rs;
  mat->m12 = - pc * rs;
  mat->m13 = 0.0f;

  mat->m20 = ys * rs + yc * ps * rc;
  mat->m21 = yc * rs - ys * ps * rc;
  mat->m22 = pc * rc;
  mat->m23 = 0.0f;

  mat->m30 = 0.0f;
  mat->m31 = 0.0f;
  mat->m32 = 0.0f;
  mat->m33 = 1.0f;
}
