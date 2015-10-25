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

#include <glib.h>

#include "crankbase.h"
#include "crankshape.h"

//////// Declaration ///////////////////////////////////////////////////////////

static void test_euler_from_quat (void);

static void test_euler_from_mat (void);

static void test_euler_to_quat (void);

static void test_euler_to_mat (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint    argc,
      gchar **argv)
{
  g_test_init (&argc, &argv, NULL);
  g_test_set_nonfatal_assertions ();

  g_test_add_func ("/crank/shape/euler/from/quat",
                   test_euler_from_quat);

  g_test_add_func ("/crank/shape/euler/from/mat",
                   test_euler_from_mat);

  g_test_add_func ("/crank/shape/euler/to/quat",
                   test_euler_to_quat);

  g_test_add_func ("/crank/shape/euler/to/mat",
                   test_euler_to_mat);

  return g_test_run ();
}

//////// Definitino ////////////////////////////////////////////////////////////

static void
test_euler_from_quat (void)
{
  CrankEuler euler;
  CrankQuatFloat quat_euler;

  CrankQuatFloat quat_rot[3];

  // Test to construct [PI/4, PI/3, PI/2]
  // For ZYX
  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 0, 0, 1);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 0, 1, 0);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 1, 0, 0);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);
  crank_euler_init_from_quaternion (&euler, &quat_euler, CRANK_EULER_IN_ZYX);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For YXZ
  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 0, 1, 0);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 1, 0, 0);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 0, 0, 1);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);
  crank_euler_init_from_quaternion (&euler, &quat_euler, CRANK_EULER_IN_YXZ);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For XZY
  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 1, 0, 0);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 0, 0, 1);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 0, 1, 0);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);
  crank_euler_init_from_quaternion (&euler, &quat_euler, CRANK_EULER_IN_XZY);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For XYZ
  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 1, 0, 0);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 0, 1, 0);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 0, 0, 1);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);
  crank_euler_init_from_quaternion (&euler, &quat_euler, CRANK_EULER_IN_XYZ);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For ZXY
  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 0, 0, 1);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 1, 0, 0);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 0, 1, 0);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);
  crank_euler_init_from_quaternion (&euler, &quat_euler, CRANK_EULER_IN_ZXY);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For YZX
  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 0, 1, 0);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 0, 0, 1);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 1, 0, 0);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);
  crank_euler_init_from_quaternion (&euler, &quat_euler, CRANK_EULER_IN_YZX);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);
}

static void
test_euler_from_mat (void)
{
  CrankEuler euler;
  CrankMatFloat3 mat;

  CrankMatFloat3 mat_rot[3];

  // Test to construct [PI/4, PI/3, PI/2]
  // For ZYX
  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 0, 0, 1);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 0, 1, 0);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 1, 0, 0);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat);
  crank_mat_float3_mul_self (&mat, mat_rot + 2);

  crank_euler_init_from_matrix3 (&euler, &mat, CRANK_EULER_IN_ZYX);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For YXZ
  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 0, 1, 0);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 1, 0, 0);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 0, 0, 1);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat);
  crank_mat_float3_mul_self (&mat, mat_rot + 2);

  crank_euler_init_from_matrix3 (&euler, &mat, CRANK_EULER_IN_YXZ);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For XZY
  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 1, 0, 0);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 0, 0, 1);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 0, 1, 0);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat);
  crank_mat_float3_mul_self (&mat, mat_rot + 2);

  crank_euler_init_from_matrix3 (&euler, &mat, CRANK_EULER_IN_XZY);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For XYZ
  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 1, 0, 0);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 0, 1, 0);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 0, 0, 1);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat);
  crank_mat_float3_mul_self (&mat, mat_rot + 2);

  crank_euler_init_from_matrix3 (&euler, &mat, CRANK_EULER_IN_XYZ);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For ZXY
  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 0, 0, 1);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 1, 0, 0);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 0, 1, 0);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat);
  crank_mat_float3_mul_self (&mat, mat_rot + 2);

  crank_euler_init_from_matrix3 (&euler, &mat, CRANK_EULER_IN_ZXY);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);

  // For YZX
  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 0, 1, 0);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 0, 0, 1);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 1, 0, 0);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat);
  crank_mat_float3_mul_self (&mat, mat_rot + 2);

  crank_euler_init_from_matrix3 (&euler, &mat, CRANK_EULER_IN_YZX);

  crank_assert_cmpfloat (euler.angle1, ==, G_PI / 4);
  crank_assert_cmpfloat (euler.angle2, ==, G_PI / 3);
  crank_assert_cmpfloat (euler.angle3, ==, G_PI / 2);
}

static void
test_euler_to_quat (void)
{
  CrankEuler euler;
  CrankQuatFloat quat;
  CrankQuatFloat quat_euler;

  CrankQuatFloat quat_rot[3];

  // Test for ZYX
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_ZYX);
  crank_euler_to_quaternion (&euler, &quat);

  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 0, 0, 1);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 0, 1, 0);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 1, 0, 0);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);

  crank_assert_cmpfloat (quat.w, ==, quat_euler.w);
  crank_assert_cmpfloat (quat.x, ==, quat_euler.x);
  crank_assert_cmpfloat (quat.y, ==, quat_euler.y);
  crank_assert_cmpfloat (quat.z, ==, quat_euler.z);

  // Test for YXZ
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_YXZ);
  crank_euler_to_quaternion (&euler, &quat);

  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 0, 1, 0);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 1, 0, 0);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 0, 0, 1);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);

  crank_assert_cmpfloat (quat.w, ==, quat_euler.w);
  crank_assert_cmpfloat (quat.x, ==, quat_euler.x);
  crank_assert_cmpfloat (quat.y, ==, quat_euler.y);
  crank_assert_cmpfloat (quat.z, ==, quat_euler.z);

  // Test for XZY
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_XZY);
  crank_euler_to_quaternion (&euler, &quat);

  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 1, 0, 0);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 0, 0, 1);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 0, 1, 0);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);

  crank_assert_cmpfloat (quat.w, ==, quat_euler.w);
  crank_assert_cmpfloat (quat.x, ==, quat_euler.x);
  crank_assert_cmpfloat (quat.y, ==, quat_euler.y);
  crank_assert_cmpfloat (quat.z, ==, quat_euler.z);

  // Test for XYZ
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_XYZ);
  crank_euler_to_quaternion (&euler, &quat);

  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 1, 0, 0);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 0, 1, 0);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 0, 0, 1);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);

  crank_assert_cmpfloat (quat.w, ==, quat_euler.w);
  crank_assert_cmpfloat (quat.x, ==, quat_euler.x);
  crank_assert_cmpfloat (quat.y, ==, quat_euler.y);
  crank_assert_cmpfloat (quat.z, ==, quat_euler.z);

  // Test for YXZ
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_YZX);
  crank_euler_to_quaternion (&euler, &quat);

  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 0, 1, 0);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 0, 0, 1);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 1, 0, 0);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);

  crank_assert_cmpfloat (quat.w, ==, quat_euler.w);
  crank_assert_cmpfloat (quat.x, ==, quat_euler.x);
  crank_assert_cmpfloat (quat.y, ==, quat_euler.y);
  crank_assert_cmpfloat (quat.z, ==, quat_euler.z);

  // Test for XZY
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_ZXY);
  crank_euler_to_quaternion (&euler, &quat);

  crank_quat_float_init_urot (quat_rot + 0, G_PI / 4, 0, 0, 1);
  crank_quat_float_init_urot (quat_rot + 1, G_PI / 3, 1, 0, 0);
  crank_quat_float_init_urot (quat_rot + 2, G_PI / 2, 0, 1, 0);

  crank_quat_float_mul (quat_rot + 0, quat_rot + 1, &quat_euler);
  crank_quat_float_mul_self (&quat_euler, quat_rot + 2);

  crank_assert_cmpfloat (quat.w, ==, quat_euler.w);
  crank_assert_cmpfloat (quat.x, ==, quat_euler.x);
  crank_assert_cmpfloat (quat.y, ==, quat_euler.y);
  crank_assert_cmpfloat (quat.z, ==, quat_euler.z);
}

static void
test_euler_to_mat (void)
{
  CrankEuler euler;
  CrankMatFloat3 mat;

  CrankMatFloat3 mat_rot[3];
  CrankMatFloat3 mat_res;

  // Test for ZYX
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_ZYX);
  crank_euler_to_matrix3 (&euler, &mat);

  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 0, 0, 1);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 0, 1, 0);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 1, 0, 0);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat_res);
  crank_mat_float3_mul_self (&mat_res, mat_rot + 2);

  crank_assert_cmpfloat (mat.m00, ==, mat_res.m00);
  crank_assert_cmpfloat (mat.m01, ==, mat_res.m01);
  crank_assert_cmpfloat (mat.m02, ==, mat_res.m02);
  crank_assert_cmpfloat (mat.m10, ==, mat_res.m10);
  crank_assert_cmpfloat (mat.m11, ==, mat_res.m11);
  crank_assert_cmpfloat (mat.m12, ==, mat_res.m12);
  crank_assert_cmpfloat (mat.m20, ==, mat_res.m20);
  crank_assert_cmpfloat (mat.m21, ==, mat_res.m21);
  crank_assert_cmpfloat (mat.m22, ==, mat_res.m22);

  // Test for YXZ
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_YXZ);
  crank_euler_to_matrix3 (&euler, &mat);

  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 0, 1, 0);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 1, 0, 0);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 0, 0, 1);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat_res);
  crank_mat_float3_mul_self (&mat_res, mat_rot + 2);

  crank_assert_cmpfloat (mat.m00, ==, mat_res.m00);
  crank_assert_cmpfloat (mat.m01, ==, mat_res.m01);
  crank_assert_cmpfloat (mat.m02, ==, mat_res.m02);
  crank_assert_cmpfloat (mat.m10, ==, mat_res.m10);
  crank_assert_cmpfloat (mat.m11, ==, mat_res.m11);
  crank_assert_cmpfloat (mat.m12, ==, mat_res.m12);
  crank_assert_cmpfloat (mat.m20, ==, mat_res.m20);
  crank_assert_cmpfloat (mat.m21, ==, mat_res.m21);
  crank_assert_cmpfloat (mat.m22, ==, mat_res.m22);

  // Test for XZY
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_XZY);
  crank_euler_to_matrix3 (&euler, &mat);

  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 1, 0, 0);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 0, 0, 1);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 0, 1, 0);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat_res);
  crank_mat_float3_mul_self (&mat_res, mat_rot + 2);

  crank_assert_cmpfloat (mat.m00, ==, mat_res.m00);
  crank_assert_cmpfloat (mat.m01, ==, mat_res.m01);
  crank_assert_cmpfloat (mat.m02, ==, mat_res.m02);
  crank_assert_cmpfloat (mat.m10, ==, mat_res.m10);
  crank_assert_cmpfloat (mat.m11, ==, mat_res.m11);
  crank_assert_cmpfloat (mat.m12, ==, mat_res.m12);
  crank_assert_cmpfloat (mat.m20, ==, mat_res.m20);
  crank_assert_cmpfloat (mat.m21, ==, mat_res.m21);
  crank_assert_cmpfloat (mat.m22, ==, mat_res.m22);

  // Test for XYZ
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_XYZ);
  crank_euler_to_matrix3 (&euler, &mat);

  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 1, 0, 0);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 0, 1, 0);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 0, 0, 1);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat_res);
  crank_mat_float3_mul_self (&mat_res, mat_rot + 2);

  crank_assert_cmpfloat (mat.m00, ==, mat_res.m00);
  crank_assert_cmpfloat (mat.m01, ==, mat_res.m01);
  crank_assert_cmpfloat (mat.m02, ==, mat_res.m02);
  crank_assert_cmpfloat (mat.m10, ==, mat_res.m10);
  crank_assert_cmpfloat (mat.m11, ==, mat_res.m11);
  crank_assert_cmpfloat (mat.m12, ==, mat_res.m12);
  crank_assert_cmpfloat (mat.m20, ==, mat_res.m20);
  crank_assert_cmpfloat (mat.m21, ==, mat_res.m21);
  crank_assert_cmpfloat (mat.m22, ==, mat_res.m22);

  // Test for YZX
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_YZX);
  crank_euler_to_matrix3 (&euler, &mat);

  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 0, 1, 0);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 0, 0, 1);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 1, 0, 0);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat_res);
  crank_mat_float3_mul_self (&mat_res, mat_rot + 2);

  crank_assert_cmpfloat (mat.m00, ==, mat_res.m00);
  crank_assert_cmpfloat (mat.m01, ==, mat_res.m01);
  crank_assert_cmpfloat (mat.m02, ==, mat_res.m02);
  crank_assert_cmpfloat (mat.m10, ==, mat_res.m10);
  crank_assert_cmpfloat (mat.m11, ==, mat_res.m11);
  crank_assert_cmpfloat (mat.m12, ==, mat_res.m12);
  crank_assert_cmpfloat (mat.m20, ==, mat_res.m20);
  crank_assert_cmpfloat (mat.m21, ==, mat_res.m21);
  crank_assert_cmpfloat (mat.m22, ==, mat_res.m22);

  // Test for ZXY
  crank_euler_init_angle (&euler, G_PI / 4, G_PI / 3, G_PI / 2, CRANK_EULER_IN_ZXY);
  crank_euler_to_matrix3 (&euler, &mat);

  crank_mat_float3_init_urot (mat_rot + 0, G_PI / 4, 0, 0, 1);
  crank_mat_float3_init_urot (mat_rot + 1, G_PI / 3, 1, 0, 0);
  crank_mat_float3_init_urot (mat_rot + 2, G_PI / 2, 0, 1, 0);

  crank_mat_float3_mul (mat_rot + 0, mat_rot + 1, &mat_res);
  crank_mat_float3_mul_self (&mat_res, mat_rot + 2);

  crank_assert_cmpfloat (mat.m00, ==, mat_res.m00);
  crank_assert_cmpfloat (mat.m01, ==, mat_res.m01);
  crank_assert_cmpfloat (mat.m02, ==, mat_res.m02);
  crank_assert_cmpfloat (mat.m10, ==, mat_res.m10);
  crank_assert_cmpfloat (mat.m11, ==, mat_res.m11);
  crank_assert_cmpfloat (mat.m12, ==, mat_res.m12);
  crank_assert_cmpfloat (mat.m20, ==, mat_res.m20);
  crank_assert_cmpfloat (mat.m21, ==, mat_res.m21);
  crank_assert_cmpfloat (mat.m22, ==, mat_res.m22);
}
