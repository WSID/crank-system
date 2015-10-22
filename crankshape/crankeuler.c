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
 */
//////// Type definition ///////////////////////////////////////////////////////

GType
crank_euler_type_get_type (void)
{
  static GType __g_type_define = 0;
  static const GEnumValue enum_descriptors [] = {
      {0, "CRANK_EULER_INVALID", "invalid"},
      {1, "CRANK_EULER_IN_ZYX", "in-zyx"},
      {0, NULL, NULL}
  };

  if (__g_type_define == 0)
    {
      __g_type_define = g_enum_register_static ("CrankEulerType",
                                                enum_descriptors);
    }

  return __g_type_define;
}


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
  euler->angle1 = 0;
  euler->angle2 = 0;
  euler->angle3 = 0;
  euler->etype  = CRANK_EULER_INVALID;
}

/**
 * crank_euler_init_angle:
 * @euler: (out): An euler angle.
 * @angle1: First rotation angle.
 * @angle2: Second rotation angle.
 * @angle3: Third rotation angle.
 * @etype: Type of euler angles.
 *
 * Initialize an euler angle with components.
 */
void
crank_euler_init_angle (CrankEuler     *euler,
                        const gfloat    angle1,
                        const gfloat    angle2,
                        const gfloat    angle3,
                        CrankEulerType  etype)
{
  euler->angle1 = angle1;
  euler->angle2 = angle2;
  euler->angle3 = angle3;
  euler->etype = etype;
}

/**
 * crank_euler_init_from_quaternion:
 * @euler: (out): An euler angle.
 * @quat: A Quaternion represents rotation.
 * @etype: Type of euler angles.
 *
 * Initialize an euler angle with quaternion.
 */
void
crank_euler_init_from_quaternion (CrankEuler     *euler,
                                  CrankQuatFloat *quat,
                                  CrankEulerType  etype)
{
  // TODO: support other etype.
  switch (etype)
    {
    case CRANK_EULER_IN_ZYX:
      euler->angle1 = atan2f (    2 * (quat->w * quat->x + quat->y * quat->z),
                              (1 - 2 * (quat->x * quat->x + quat->y * quat->y)) );

      euler->angle2 = asinf (    2 * (quat->w * quat->y - quat->x * quat->z) );

      euler->angle3 = atan2f (    2 * (quat->w * quat->z + quat->x * quat->y) ,
                              (1 - 2 * (quat->y * quat->y + quat->z * quat->z)) );
      break;

    case CRANK_EULER_INVALID:
    default:
      euler->angle1 = 0.0f;
      euler->angle2 = 0.0f;
      euler->angle3 = 0.0f;
      g_warning ("Invalid EulerType: %d", (gint) etype);
      break;
    }

  euler->etype = etype;
}

/**
 * crank_euler_init_from_matrix3:
 * @euler: (out): An euler angle.
 * @mat: A matrix represents a rotation.
 * @etype: Type of euler angles.
 *
 * Initialize an euler angle with matrix.
 */
void
crank_euler_init_from_matrix3 (CrankEuler     *euler,
                               CrankMatFloat3 *mat,
                               CrankEulerType  etype)
{
  euler->angle1 = asinf (mat->m02);

  euler->angle2 = atan2f (-mat->m01, mat->m00);

  euler->angle3 = atan2f (-mat->m12, mat->m22);
}

/**
 * crank_euler_init_from_matrix4:
 * @euler: (out): An euler angle.
 * @mat: A matrix represents a rotation.
 * @etype: Type of euler angles.
 *
 * Initialize an euler angle with matrix.
 */
void
crank_euler_init_from_matrix4 (CrankEuler     *euler,
                               CrankMatFloat4 *mat,
                               CrankEulerType  etype)
{
  euler->angle1 = asinf (mat->m02);

  euler->angle2 = atan2f (-mat->m01, mat->m00);

  euler->angle3 = atan2f (-mat->m21, mat->m22);
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
  other->angle1 = euler->angle1;
  other->angle2 = euler->angle2;
  other->angle3 = euler->angle3;
  other->etype = euler->etype;
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
crank_euler_dup (CrankEuler *euler)
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

  yc = cosf (euler->angle1 / 2);
  ys = sinf (euler->angle1 / 2);

  pc = cosf (euler->angle2 / 2);
  ps = sinf (euler->angle2 / 2);

  rc = cosf (euler->angle3 / 2);
  rs = sinf (euler->angle3 / 2);

  quat->w = yc * pc * rc + ys * ps * rs;
  quat->x = yc * pc * rs - ys * ps * rc;
  quat->y = yc * ps * rc + ys * pc * rs;
  quat->z = - yc * ps * rs + ys * pc * rc;
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

  yc = cosf (euler->angle1);
  ys = sinf (euler->angle1);

  pc = cosf (euler->angle2);
  ps = sinf (euler->angle2);

  rc = cosf (euler->angle3);
  rs = sinf (euler->angle3);

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

  yc = cosf (euler->angle1);
  ys = sinf (euler->angle1);

  pc = cosf (euler->angle2);
  ps = sinf (euler->angle2);

  rc = cosf (euler->angle3);
  rs = sinf (euler->angle3);

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
