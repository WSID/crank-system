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
      {CRANK_EULER_INVALID, "CRANK_EULER_INVALID", "invalid"},

      {CRANK_EULER_IN_ZYX, "CRANK_EULER_IN_ZYX", "in-zyx"},
      {CRANK_EULER_IN_YXZ, "CRANK_EULER_IN_YXZ", "in-yxz"},
      {CRANK_EULER_IN_XZY, "CRANK_EULER_IN_XZY", "in-xzy"},

      {CRANK_EULER_IN_XYZ, "CRANK_EULER_IN_XYZ", "in-xyz"},
      {CRANK_EULER_IN_ZXY, "CRANK_EULER_IN_ZXY", "in-zxy"},
      {CRANK_EULER_IN_YZX, "CRANK_EULER_IN_YZX", "in-yzx"},

      {CRANK_EULER_IN_XYX, "CRANK_EULER_IN_XYX", "in-xyx"},
      {CRANK_EULER_IN_YZY, "CRANK_EULER_IN_YZY", "in-yzy"},
      {CRANK_EULER_IN_ZXZ, "CRANK_EULER_IN_ZXZ", "in-zxz"},

      {CRANK_EULER_IN_YXY, "CRANK_EULER_IN_YXY", "in-yxy"},
      {CRANK_EULER_IN_ZYZ, "CRANK_EULER_IN_ZYZ", "in-zyz"},
      {CRANK_EULER_IN_XZX, "CRANK_EULER_IN_XZX", "in-xzx"},

      {CRANK_EULER_EX_ZYX, "CRANK_EULER_EX_ZYX", "ex-zyx"},
      {CRANK_EULER_EX_YXZ, "CRANK_EULER_EX_YXZ", "ex-yxz"},
      {CRANK_EULER_EX_XZY, "CRANK_EULER_EX_XZY", "ex-xzy"},

      {CRANK_EULER_EX_XYZ, "CRANK_EULER_EX_XYZ", "ex-xyz"},
      {CRANK_EULER_EX_ZXY, "CRANK_EULER_EX_ZXY", "ex-zxy"},
      {CRANK_EULER_EX_YZX, "CRANK_EULER_EX_YZX", "ex-yzx"},

      {CRANK_EULER_EX_XYX, "CRANK_EULER_EX_XYX", "ex-xyx"},
      {CRANK_EULER_EX_YZY, "CRANK_EULER_EX_YZY", "ex-yzy"},
      {CRANK_EULER_EX_ZXZ, "CRANK_EULER_EX_ZXZ", "ex-zxz"},

      {CRANK_EULER_EX_YXY, "CRANK_EULER_EX_YXY", "ex-yxy"},
      {CRANK_EULER_EX_ZYZ, "CRANK_EULER_EX_ZYZ", "ex-zyz"},
      {CRANK_EULER_EX_XZX, "CRANK_EULER_EX_XZX", "ex-xzx"},
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
  gfloat xx = quat->x * quat->x;
  gfloat yy = quat->y * quat->y;
  gfloat zz = quat->z * quat->z;

  gfloat wx = quat->w * quat->x;
  gfloat wy = quat->w * quat->y;
  gfloat wz = quat->w * quat->z;

  gfloat xy = quat->x * quat->y;
  gfloat xz = quat->x * quat->z;
  gfloat yz = quat->y * quat->z;

  gfloat *qa = (gfloat*) quat;

  CrankEulerType  inetype = ABS (etype);

  // TODO: support other etype.
  switch (inetype)
    {
    case CRANK_EULER_IN_ZYX:
      euler->angle1 = atan2f (2 * (wz + xy), (1 - 2 * (yy + zz)) );
      euler->angle2 = asinf  (2 * (wy - xz) );
      euler->angle3 = atan2f (2 * (wx + yz), (1 - 2 * (xx + yy)) );
      break;

    case CRANK_EULER_IN_YXZ:
      euler->angle1 = atan2f (2 * (xz + wy), (1 - 2 * (xx + yy)) );
      euler->angle2 = asinf  (2 * (wx - yz) );
      euler->angle3 = atan2f (2 * (xy + wz), (1 - 2 * (xx + zz)) );
      break;

    case CRANK_EULER_IN_XZY:
      euler->angle1 = atan2f (2 * (yz + wx), (1 - 2 * (xx + zz)) );
      euler->angle2 = asinf  (2 * (wz - xy) );
      euler->angle3 = atan2f (2 * (xz + wy), (1 - 2 * (yy + zz)) );
      break;

    case CRANK_EULER_IN_XYZ:
      euler->angle1 = atan2f (2 * (wx - yz), (1 - 2 * (xx + yy)) );
      euler->angle2 = asinf (2 * (wy + xz));
      euler->angle3 = atan2f (2 * (wz - xy), (1 - 2 * (yy + zz)) );
      break;

    case CRANK_EULER_IN_ZXY:
      euler->angle1 = atan2f (2 * (wz - xy), (1 - 2 * (xx + zz)) );
      euler->angle2 = asinf (2 * (wx + yz));
      euler->angle3 = atan2f (2 * (wy - xz), (1 - 2 * (xx + yy)) );
      break;

    case CRANK_EULER_IN_YZX:
      euler->angle1 = atan2f (2 * (wy - xz), (1 - 2 * (yy + zz)) );
      euler->angle2 = asinf (2 * (xy + wz));
      euler->angle3 = atan2f (2 * (wx - yz), (1 - 2 * (xx + zz)) );
      break;

    case CRANK_EULER_IN_XYX:
      euler->angle1 = atan2f ((xy + wz), (wy - xz));
      euler->angle2 = acosf (1 - 2 * (yy + zz));
      euler->angle3 = atan2f ((xy - wz), (xz + wy));
      break;

    case CRANK_EULER_IN_YZY:
      euler->angle1 = atan2f ((yz + wx), (wz - xy));
      euler->angle2 = acosf (1 - 2 * (xx + zz));
      euler->angle3 = atan2f ((yz - wx), (xy + wz));
      break;

    case CRANK_EULER_IN_ZXZ:
      euler->angle1 = atan2f ((wx - yz),(xz + wy));
      euler->angle2 = acosf (1 - 2 * (xx + yy));
      euler->angle3 = atan2f ((xz - wy), (yz + wx));
      break;

    case CRANK_EULER_IN_YXY:
      euler->angle1 = atan2f ((xy - wz), (yz + wx));
      euler->angle2 = acosf (1 - 2 * (xx + zz));
      euler->angle3 = atan2f ((xy + wz), (wx - yz));
      break;

    case CRANK_EULER_IN_ZYZ:
      euler->angle1 = atan2f ((yz - wx), (xz + wy));
      euler->angle2 = acosf (1 - 2 * (xx + yy));
      euler->angle3 = atan2f ((yz + wx), (wy - xz));
      break;

    case CRANK_EULER_IN_XZX:
      euler->angle1 = atan2f ((xz - wy), (xy + wz));
      euler->angle2 = acosf (1 - 2 * (yy + zz));
      euler->angle3 = atan2f ((xz + wy), (wz - xy));
      break;

    default:
      euler->angle1 = 0.0f;
      euler->angle2 = 0.0f;
      euler->angle3 = 0.0f;
      g_warning ("Invalid EulerType: %d", (gint) etype);
      break;
    }

  if (etype < 0)
    {
      gfloat temp = euler->angle1;
      euler->angle1 = euler->angle3;
      euler->angle3 = temp;
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
  CrankEulerType  inetype = ABS (etype);

  switch (inetype)
    {
    case CRANK_EULER_IN_ZYX:
      euler->angle1 = atan2f (mat->m10, mat->m00);
      euler->angle2 = asinf (- mat->m20);
      euler->angle3 = atan2f (mat->m21, mat->m22);
      break;

    case CRANK_EULER_IN_YXZ:
      euler->angle1 = atan2f (mat->m02, mat->m22);
      euler->angle2 = asinf  (- mat->m12);
      euler->angle3 = atan2f (mat->m10, mat->m11);
      break;

    case CRANK_EULER_IN_XZY:
      euler->angle1 = atan2f (mat->m21, mat->m11);
      euler->angle2 = asinf (- mat->m01);
      euler->angle3 = atan2f (mat->m02, mat->m00);
      break;

    case CRANK_EULER_IN_XYZ:
      euler->angle1 = atan2f (-mat->m12, mat->m22);
      euler->angle2 = asinf (mat->m02);
      euler->angle3 = atan2f (-mat->m01, mat->m00);
      break;

    case CRANK_EULER_IN_ZXY:
      euler->angle1 = atan2f (-mat->m01, mat->m11);
      euler->angle2 = asinf (mat->m21);
      euler->angle3 = atan2f (-mat->m20, mat->m22);
      break;

    case CRANK_EULER_IN_YZX:
      euler->angle1 = atan2f (-mat->m20, mat->m00);
      euler->angle2 = asinf (mat->m10);
      euler->angle3 = atan2f (-mat->m12, mat->m11);
      break;

    case CRANK_EULER_IN_XYX:
      euler->angle1 = atan2f (mat->m10, -mat->m20);
      euler->angle2 = acosf (mat->m00);
      euler->angle3 = atan2f (mat->m01, mat->m02);
      break;

    case CRANK_EULER_IN_YZY:
      euler->angle1 = atan2f (mat->m21, -mat->m01);
      euler->angle2 = acosf (mat->m11);
      euler->angle3 = atan2f (mat->m12, mat->m10);
      break;

    case CRANK_EULER_IN_ZXZ:
      euler->angle1 = atan2f (-mat->m12, mat->m02);
      euler->angle2 = acosf (mat->m22);
      euler->angle3 = atan2f (mat->m20, mat->m21);
      break;

    case CRANK_EULER_IN_YXY:
      euler->angle1 = atan2f (mat->m01, mat->m21);
      euler->angle2 = acosf (mat->m11);
      euler->angle3 = atan2f (mat->m10, -mat->m12);
      break;

    case CRANK_EULER_IN_ZYZ:
      euler->angle1 = atan2f (mat->m12, mat->m02);
      euler->angle2 = acosf (mat->m22);
      euler->angle3 = atan2f (mat->m21, -mat->m20);
      break;

    case CRANK_EULER_IN_XZX:
      euler->angle1 = atan2f (mat->m20, mat->m10);
      euler->angle2 = acosf (mat->m00);
      euler->angle3 = atan2f (mat->m02, -mat->m01);
      break;

    default:
      euler->angle1 = 0.0f;
      euler->angle2 = 0.0f;
      euler->angle3 = 0.0f;
      g_warning ("Invalid EulerType: %d", (gint) etype);
      break;
    }

  if (etype < 0) {
    gfloat temp = euler->angle1;
    euler->angle1 = euler->angle3;
    euler->angle3 = temp;
  }

  euler->etype = etype;
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
  CrankEulerType  inetype = ABS (etype);

  switch (inetype)
    {
    case CRANK_EULER_IN_ZYX:
      euler->angle1 = atan2f (mat->m10, mat->m00);
      euler->angle2 = asinf (- mat->m20);
      euler->angle3 = atan2f (mat->m21, mat->m22);
      break;

    case CRANK_EULER_IN_YXZ:
      euler->angle1 = atan2f (mat->m02, mat->m22);
      euler->angle2 = asinf  (- mat->m12);
      euler->angle3 = atan2f (mat->m10, mat->m11);
      break;

    case CRANK_EULER_IN_XZY:
      euler->angle1 = atan2f (mat->m21, mat->m11);
      euler->angle2 = asinf (- mat->m01);
      euler->angle3 = atan2f (mat->m02, mat->m00);
      break;

    case CRANK_EULER_IN_XYZ:
      euler->angle1 = atan2f (-mat->m12, mat->m22);
      euler->angle2 = asinf (mat->m02);
      euler->angle3 = atan2f (-mat->m01, mat->m00);
      break;

    case CRANK_EULER_IN_ZXY:
      euler->angle1 = atan2f (-mat->m01, mat->m11);
      euler->angle2 = asinf (mat->m21);
      euler->angle3 = atan2f (-mat->m20, mat->m22);
      break;

    case CRANK_EULER_IN_YZX:
      euler->angle1 = atan2f (-mat->m20, mat->m00);
      euler->angle2 = asinf (mat->m10);
      euler->angle3 = atan2f (-mat->m12, mat->m11);
      break;

    case CRANK_EULER_IN_XYX:
      euler->angle1 = atan2f (mat->m10, -mat->m20);
      euler->angle2 = acosf (mat->m00);
      euler->angle3 = atan2f (mat->m01, mat->m02);
      break;

    case CRANK_EULER_IN_YZY:
      euler->angle1 = atan2f (mat->m21, -mat->m01);
      euler->angle2 = acosf (mat->m11);
      euler->angle3 = atan2f (mat->m12, mat->m10);
      break;

    case CRANK_EULER_IN_ZXZ:
      euler->angle1 = atan2f (-mat->m12, mat->m02);
      euler->angle2 = acosf (mat->m22);
      euler->angle3 = atan2f (mat->m20, mat->m21);
      break;

    case CRANK_EULER_IN_YXY:
      euler->angle1 = atan2f (mat->m01, mat->m21);
      euler->angle2 = acosf (mat->m11);
      euler->angle3 = atan2f (mat->m10, -mat->m12);
      break;

    case CRANK_EULER_IN_ZYZ:
      euler->angle1 = atan2f (mat->m12, mat->m02);
      euler->angle2 = acosf (mat->m22);
      euler->angle3 = atan2f (mat->m21, -mat->m20);
      break;

    case CRANK_EULER_IN_XZX:
      euler->angle1 = atan2f (mat->m20, mat->m10);
      euler->angle2 = acosf (mat->m00);
      euler->angle3 = atan2f (mat->m02, -mat->m01);
      break;

    default:
      euler->angle1 = 0.0f;
      euler->angle2 = 0.0f;
      euler->angle3 = 0.0f;
      g_warning ("Invalid EulerType: %d", (gint) etype);
      break;
    }
  if (etype < 0) {
    gfloat temp = euler->angle1;
    euler->angle1 = euler->angle3;
    euler->angle3 = temp;
  }

  euler->etype = etype;
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
 * Returns: (transfer full): A duplicated euler angle.
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
  CrankEulerType inetype;

  gfloat ina1;
  gfloat ina3;

  gfloat c1, s1;
  gfloat c2, s2;
  gfloat c3, s3;

  if (euler->etype < 0)
    {
      ina1 = euler->angle3;
      ina3 = euler->angle1;
    }
  else
    {
      ina1 = euler->angle1;
      ina3 = euler->angle3;
    }

  inetype = ABS (euler->etype);

  c1 = cosf (ina1 / 2);
  s1 = sinf (ina1 / 2);

  c2 = cosf (euler->angle2 / 2);
  s2 = sinf (euler->angle2 / 2);

  c3 = cosf (ina3 / 2);
  s3 = sinf (ina3 / 2);


  switch (inetype)
    {
    case CRANK_EULER_IN_ZYX:
      quat->w = c1 * c2 * c3 + s1 * s2 * s3;
      quat->x = c1 * c2 * s3 - s1 * s2 * c3;
      quat->y = c1 * s2 * c3 + s1 * c2 * s3;
      quat->z = - c1 * s2 * s3 + s1 * c2 * c3;
      break;

    case CRANK_EULER_IN_YXZ:
      quat->w = c1 * c2 * c3 + s1 * s2 * s3;
      quat->x = c1 * s2 * c3 + s1 * c2 * s3;
      quat->y = s1 * c2 * c3 - c1 * s2 * s3;
      quat->z = -s1 * s2 * c3 + c1 * c2 * s3;
      break;

    case CRANK_EULER_IN_XZY:
      quat->w = c1 * c2 * c3 + s1 * s2 * s3;
      quat->x = s1 * c2 * c3 - c1 * s2 * s3;
      quat->y = c1 * c2 * s3 - s1 * s2 * c3;
      quat->z = c1 * s2 * c3 + s1 * c2 * s3;
      break;

    case CRANK_EULER_IN_XYZ:
      quat->w = c1 * c2 * c3 - s1 * s2 * s3;
      quat->x = c1 * s2 * s3 + s1 * c2 * c3;
      quat->y = c1 * s2 * c3 - s1 * c2 * s3;
      quat->z = c1 * c2 * s3 + s1 * s2 * c3;
      break;

    case CRANK_EULER_IN_ZXY:
      quat->w = c1 * c2 * c3 - s1 * s2 * s3;
      quat->x = c1 * s2 * c3 - s1 * c2 * s3;
      quat->y = c1 * c2 * s3 + s1 * s2 * c3;
      quat->z = c1 * s2 * s3 + s1 * c2 * c3;
      break;

    case CRANK_EULER_IN_YZX:
      quat->w = c1 * c2 * c3 - s1 * s2 * s3;
      quat->x = c1 * c2 * s3 + s1 * s2 * c3;
      quat->y = c1 * s2 * s3 + s1 * c2 * c3;
      quat->z = c1 * s2 * c3 - s1 * c2 * s3;
      break;

    case CRANK_EULER_IN_XYX:
      quat->w = c1 * c2 * c3 - s1 * c2 * s3;
      quat->x = s1 * c2 * c3 + c1 * c2 * s3;
      quat->y = c1 * s2 * c3 + s1 * s2 * s3;
      quat->z = s1 * s2 * c3 - c1 * s2 * s3;
      break;

    case CRANK_EULER_IN_YZY:
      quat->w = c1 * c2 * c3 - s1 * c2 * s3;
      quat->x = s1 * s2 * c3 - c1 * s2 * s3;
      quat->y = s1 * c2 * c3 + c1 * c2 * s3;
      quat->z = c1 * s2 * c3 + s1 * s2 * s3;
      break;

    case CRANK_EULER_IN_ZXZ:
      quat->w = c1 * c2 * c3 - s1 * c2 * s3;
      quat->x = c1 * s2 * c3 + s1 * s2 * s3;
      quat->y = s1 * s2 * c3 - c1 * s2 * s3;
      quat->z = s1 * c2 * c3 + c1 * c2 * s3;
      break;

    case CRANK_EULER_IN_YXY:
      quat->w = c1 * c2 * c3 - s1 * c2 * s3;
      quat->x = c1 * s2 * c3 + s1 * s2 * s3;
      quat->y = c1 * c2 * s3 + s1 * c2 * c3;
      quat->z = c1 * s2 * s3 - s1 * s2 * c3;
      break;

    case CRANK_EULER_IN_ZYZ:
      quat->w = c1 * c2 * c3 - s1 * c2 * s3;
      quat->x = c1 * s2 * s3 - s1 * s2 * c3;
      quat->y = c1 * s2 * c3 + s1 * s2 * s3;
      quat->z = c1 * c2 * s3 + s1 * c2 * c3;
      break;

    case CRANK_EULER_IN_XZX:
      quat->w = c1 * c2 * c3 - s1 * c2 * s3;
      quat->x = c1 * c2 * s3 + s1 * c2 * c3;
      quat->y = c1 * s2 * s3 - s1 * s2 * c3;
      quat->z = c1 * s2 * c3 + s1 * s2 * s3;
      break;

    default:
      g_warning ("Trying to convert invalid value to quaternion.");
      break;
    }
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
  CrankEulerType inetype;

  gfloat ina1;
  gfloat ina3;

  gfloat c1, s1;
  gfloat c2, s2;
  gfloat c3, s3;

  if (euler->etype < 0)
    {
      ina1 = euler->angle3;
      ina3 = euler->angle1;
    }
  else
    {
      ina1 = euler->angle1;
      ina3 = euler->angle3;
    }

  inetype = ABS (euler->etype);

  c1 = cosf (ina1);
  s1 = sinf (ina1);

  c2 = cosf (euler->angle2);
  s2 = sinf (euler->angle2);

  c3 = cosf (ina3);
  s3 = sinf (ina3);

  switch (inetype)
    {
    case CRANK_EULER_IN_ZYX:
      mat->m00 =   c1 * c2;
      mat->m01 =   c1 * s2 * s3 - s1 * c3;
      mat->m02 =   c1 * s2 * c3 + s1 * s3;

      mat->m10 =   s1 * c2;
      mat->m11 =   s1 * s2 * s3 + c1 * c3;
      mat->m12 =   s1 * s2 * c3 - c1 * s3;

      mat->m20 = - s2;
      mat->m21 =   c2 * s3;
      mat->m22 =   c2 * c3;
      break;

    case CRANK_EULER_IN_YXZ:
      mat->m00 =   s1 * s2 * s3 + c1 * c3;
      mat->m01 =   s1 * s2 * c3 - c1 * s3;
      mat->m02 =   s1 * c2;

      mat->m10 =   c2 * s3;
      mat->m11 =   c2 * c3;
      mat->m12 = - s2;

      mat->m20 =   c1 * s2 * s3 - s1 * c3;
      mat->m21 =   c1 * s2 * c3 + s1 * s3;
      mat->m22 =   c1 * c2;
      break;

    case CRANK_EULER_IN_XZY:
      mat->m00 =   c2 * c3;
      mat->m01 = - s2;
      mat->m02 =   c2 * s3;

      mat->m10 =   c1 * s2 * c3 + s1 * s3;
      mat->m11 =   c1 * c2;
      mat->m12 =   c1 * s2 * s3 - s1 * c3;

      mat->m20 =   s1 * s2 * c3 - c1 * s3;
      mat->m21 =   s1 * c2;
      mat->m22 =   s1 * s2 * s3 + c1 * c3;
      break;

    case CRANK_EULER_IN_XYZ:
      mat->m00 =   c3 * c2;
      mat->m01 = - s3 * c2;
      mat->m02 =   s2;

      mat->m10 =   c3 * s2 * s1 + s3 * c1;
      mat->m11 = - s3 * s2 * s1 + c3 * c1;
      mat->m12 = - c2 * s1;

      mat->m20 = - c3 * s2 * c1 + s3 * s1;
      mat->m21 =   s3 * s2 * c1 + c3 * s1;
      mat->m22 =   c2 * c1;
      break;

    case CRANK_EULER_IN_YZX:
      mat->m00 =   c1 * c2;
      mat->m01 = - c1 * s2 * c3 + s1 * s3;
      mat->m02 =   c1 * s2 * s3 + s1 * c3;

      mat->m10 =   s2;
      mat->m11 =   c2 * c3;
      mat->m12 = - c2 * s3;

      mat->m20 = - s1 * c2;
      mat->m21 =   s1 * s2 * c3 + c1 * s3;
      mat->m22 = - s1 * s2 * s3 + c1 * c3;
      break;

    case CRANK_EULER_IN_ZXY:
      mat->m00 = - s1 * s2 * s3 + c1 * c3;
      mat->m01 = - s1 * c2;
      mat->m02 =   s1 * s2 * c3 + c1 * s3;

      mat->m10 =   c1 * s2 * s3 + s1 * c3;
      mat->m11 =   c1 * c2;
      mat->m12 = - c1 * s2 * c3 + s1 * s3;

      mat->m20 = - c2 * s3;
      mat->m21 =   s2;
      mat->m22 =   c2 * c3;
      break;

    case CRANK_EULER_IN_XYX:
      mat->m00 =   c2;
      mat->m01 =   s2 * s3;
      mat->m02 =   s2 * c3;

      mat->m10 =   s1 * s2;
      mat->m11 =   c1 * c3 - s1 * c2 * s3;
      mat->m12 = - c1 * s3 + s1 * c2 * c3;

      mat->m20 = - c1 * s2;
      mat->m21 =   s1 * c3 + c1 * c2 * s3;
      mat->m22 = - s1 * s3 + c1 * c2 * c3;
      break;

    case CRANK_EULER_IN_YZY:
      mat->m00 =   c1 * c2 * c3 - s1 * s3;
      mat->m01 = - c1 * s2;
      mat->m02 =   c1 * c2 * s3 + s1 * c3;

      mat->m10 =   s2 * c3;
      mat->m11 =   c2;
      mat->m12 =   s2 * s3;

      mat->m20 = - s1 * c2 * c3 - c1 * s3;
      mat->m21 =   s1 * s2;
      mat->m22 = - s1 * c2 * s3 + c1 * c3;
      break;

    case CRANK_EULER_IN_ZXZ:
      mat->m00 = - s1 * c2 * s3 + c1 * c3;
      mat->m01 = - s1 * c2 * c3 - c1 * s3;
      mat->m02 =   s1 * s2;

      mat->m10 =   c1 * c2 * s3 + s1 * c3;
      mat->m11 = - s1 * s3 + c1 * c2 * c3;
      mat->m12 = - c1 * s2;

      mat->m20 =   s2 * s3;
      mat->m21 =   s2 * c3;
      mat->m22 =   c2;
      break;

    case CRANK_EULER_IN_YXY:
      mat->m00 = - s1 * c2 * s3 + c1 * c3;
      mat->m01 =   s1 * s2;
      mat->m02 =   s1 * c2 * c3 + c1 * s3;

      mat->m10 =   s2 * s3;
      mat->m11 =   c2;
      mat->m12 = - s2 * c3;

      mat->m20 = - c1 * c2 * s3 - s1 * c3;
      mat->m21 =   c1 * s2;
      mat->m22 =   c1 * c2 * c3 - s1 * s3;
      break;

    case CRANK_EULER_IN_ZYZ:
      mat->m00 =   c1 * c2 * c3 - s1 * s3;
      mat->m01 = - c1 * c2 * s3 - s1 * c3;
      mat->m02 =   c1 * s2;

      mat->m10 =   s1 * c2 * c3 + c1 * s3;
      mat->m11 = - s1 * c2 * s3 + c1 * c3;
      mat->m12 =   s1 * s2;

      mat->m20 = - s2 * c3;
      mat->m21 =   s2 * s3;
      mat->m22 =   c2;
      break;

    case CRANK_EULER_IN_XZX:
      mat->m00 =   c2;
      mat->m01 = - s2 * c3;
      mat->m02 =   s2 * s3;

      mat->m10 =   c1 * s2;
      mat->m11 =   c1 * c2 * c3 - s1 * s3;
      mat->m12 = - c1 * c2 * s3 - s1 * c3;

      mat->m20 =   s1 * s2;
      mat->m21 =   s1 * c2 * c3 + c1 * s3;
      mat->m22 = - s1 * c2 * s3 + c1 * c3;
      break;


    default:
      g_warning ("Trying to convert invalid value to matrix.");
      break;
    }
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
  CrankEulerType inetype;

  gfloat ina1;
  gfloat ina3;

  gfloat c1, s1;
  gfloat c2, s2;
  gfloat c3, s3;

  if (euler->etype < 0)
    {
      ina1 = euler->angle3;
      ina3 = euler->angle1;
    }
  else
    {
      ina1 = euler->angle1;
      ina3 = euler->angle3;
    }

  inetype = ABS (euler->etype);

  c1 = cosf (ina1 / 2);
  s1 = sinf (ina1 / 2);

  c2 = cosf (euler->angle2 / 2);
  s2 = sinf (euler->angle2 / 2);

  c3 = cosf (ina3 / 2);
  s3 = sinf (ina3 / 2);


  switch (inetype)
    {
    case CRANK_EULER_IN_ZYX:
      mat->m00 =   c1 * c2;
      mat->m01 =   c1 * s2 * s3 - s1 * c3;
      mat->m02 =   c1 * s2 * c3 + s1 * s3;

      mat->m10 =   s1 * c2;
      mat->m11 =   s1 * s2 * s3 + c1 * c3;
      mat->m12 =   s1 * s2 * c3 - c1 * s3;

      mat->m20 = - s2;
      mat->m21 =   c2 * s3;
      mat->m22 =   c2 * c3;
      break;

    case CRANK_EULER_IN_YXZ:
      mat->m00 =   s1 * s2 * s3 + c1 * c3;
      mat->m01 =   s1 * s2 * c3 - c1 * s3;
      mat->m02 =   s1 * c2;

      mat->m10 =   c2 * s3;
      mat->m11 =   c2 * c3;
      mat->m12 = - s2;

      mat->m20 =   c1 * s2 * s3 - s1 * c3;
      mat->m21 =   c1 * s2 * c3 + s1 * s3;
      mat->m22 =   c1 * c2;
      break;

    case CRANK_EULER_IN_XZY:
      mat->m00 =   c2 * c3;
      mat->m01 = - s2;
      mat->m02 =   c2 * s3;

      mat->m10 =   c1 * s2 * c3 + s1 * s3;
      mat->m11 =   c1 * c2;
      mat->m12 =   c1 * s2 * s3 - s1 * c3;

      mat->m20 =   s1 * s2 * c3 - c1 * s3;
      mat->m21 =   s1 * c2;
      mat->m22 =   s1 * s2 * s3 + c1 * c3;
      break;

    case CRANK_EULER_IN_XYZ:
      mat->m00 =   c3 * c2;
      mat->m01 = - s3 * c2;
      mat->m02 =   s2;

      mat->m10 =   c3 * s2 * s1 + s3 * c1;
      mat->m11 = - s3 * s2 * s1 + c3 * c1;
      mat->m12 = - c2 * s1;

      mat->m20 = - c3 * s2 * c1 + s3 * s1;
      mat->m21 =   s3 * s2 * c1 + c3 * s1;
      mat->m22 =   c2 * c1;
      break;

    case CRANK_EULER_IN_YZX:
      mat->m00 =   c1 * c2;
      mat->m01 = - c1 * s2 * c3 + s1 * s3;
      mat->m02 =   c1 * s2 * s3 + s1 * c3;

      mat->m10 =   s2;
      mat->m11 =   c2 * c3;
      mat->m12 = - c2 * s3;

      mat->m20 = - s1 * c2;
      mat->m21 =   s1 * s2 * c3 + c1 * s3;
      mat->m22 = - s1 * s2 * s3 + c1 * c3;
      break;

    case CRANK_EULER_IN_ZXY:
      mat->m00 = - s1 * s2 * s3 + c1 * c3;
      mat->m01 = - s1 * c2;
      mat->m02 =   s1 * s2 * c3 + c1 * s3;

      mat->m10 =   c1 * s2 * s3 + s1 * c3;
      mat->m11 =   c1 * c2;
      mat->m12 = - c1 * s2 * c3 + s1 * s3;

      mat->m20 = - c2 * s3;
      mat->m21 =   s2;
      mat->m22 =   c2 * c3;
      break;

    case CRANK_EULER_IN_XYX:
      mat->m00 =   c2;
      mat->m01 =   s2 * s3;
      mat->m02 =   s2 * c3;

      mat->m10 =   s1 * s2;
      mat->m11 =   c1 * c3 - s1 * c2 * s3;
      mat->m12 = - c1 * s3 + s1 * c2 * c3;

      mat->m20 = - c1 * s2;
      mat->m21 =   s1 * c3 + c1 * c2 * s3;
      mat->m22 = - s1 * s3 + c1 * c2 * c3;
      break;

    case CRANK_EULER_IN_YZY:
      mat->m00 =   c1 * c2 * c3 - s1 * s3;
      mat->m01 = - c1 * s2;
      mat->m02 =   c1 * c2 * s3 + s1 * c3;

      mat->m10 =   s2 * c3;
      mat->m11 =   c2;
      mat->m12 =   s2 * s3;

      mat->m20 = - s1 * c2 * c3 - c1 * s3;
      mat->m21 =   s1 * s2;
      mat->m22 = - s1 * c2 * s3 + c1 * c3;
      break;

    case CRANK_EULER_IN_ZXZ:
      mat->m00 = - s1 * c2 * s3 + c1 * c3;
      mat->m01 = - s1 * c2 * c3 - c1 * s3;
      mat->m02 =   s1 * s2;

      mat->m10 =   c1 * c2 * s3 + s1 * c3;
      mat->m11 = - s1 * s3 + c1 * c2 * c3;
      mat->m12 = - c1 * s2;

      mat->m20 =   s2 * s3;
      mat->m21 =   s2 * c3;
      mat->m22 =   c2;
      break;

    case CRANK_EULER_IN_YXY:
      mat->m00 = - s1 * c2 * s3 + c1 * c3;
      mat->m01 =   s1 * s2;
      mat->m02 =   s1 * c2 * c3 + c1 * s3;

      mat->m10 =   s2 * s3;
      mat->m11 =   c2;
      mat->m12 = - s2 * c3;

      mat->m20 = - c1 * c2 * s3 - s1 * c3;
      mat->m21 =   c1 * s2;
      mat->m22 =   c1 * c2 * c3 - s1 * s3;
      break;

    case CRANK_EULER_IN_ZYZ:
      mat->m00 =   c1 * c2 * c3 - s1 * s3;
      mat->m01 = - c1 * c2 * s3 - s1 * c3;
      mat->m02 =   c1 * s2;

      mat->m10 =   s1 * c2 * c3 + c1 * s3;
      mat->m11 = - s1 * c2 * s3 + c1 * c3;
      mat->m12 =   s1 * s2;

      mat->m20 = - s2 * c3;
      mat->m21 =   s2 * s3;
      mat->m22 =   c2;
      break;

    case CRANK_EULER_IN_XZX:
      mat->m00 =   c2;
      mat->m01 = - s2 * c3;
      mat->m02 =   s2 * s3;

      mat->m10 =   c1 * s2;
      mat->m11 =   c1 * c2 * c3 - s1 * s3;
      mat->m12 = - c1 * c2 * s3 - s1 * c3;

      mat->m20 =   s1 * s2;
      mat->m21 =   s1 * c2 * c3 + c1 * s3;
      mat->m22 = - s1 * c2 * s3 + c1 * c3;
      break;



    default:
      g_warning ("Trying to convert invalid value to matrix.");
      break;
    }

  mat->m03 = 0.0f;
  mat->m13 = 0.0f;
  mat->m23 = 0.0f;

  mat->m30 = 0.0f;
  mat->m31 = 0.0f;
  mat->m32 = 0.0f;

  mat->m33 = 1.0f;
}
