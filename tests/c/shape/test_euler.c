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

  g_test_add_func ("/crank/shape/euler/from/quat",
                   test_euler_from_quat);

  g_test_add_func ("/crank/shape/euler/from/mat",
                   test_euler_from_mat);

  g_test_add_func ("/crank/shape/euler/to/quat",
                   test_euler_to_quat);

  g_test_add_func ("/crank/shape/euler/to/mat",
                   test_euler_to_quat);

  return g_test_run ();
}

//////// Definitino ////////////////////////////////////////////////////////////

static void
test_euler_from_quat (void)
{
  CrankEuler euler;
  CrankQuatFloat quat;

  crank_quat_float_init (&quat, 0.84462f, 0.19134f, 0.46194f, 0.19134f);
  crank_euler_init_from_quaternion (&euler, &quat);

  crank_assert_cmpfloat (euler.yaw, ==, G_PI_4);
  crank_assert_cmpfloat (euler.pitch, ==, G_PI_4);
  crank_assert_cmpfloat (euler.roll, ==, G_PI_4);
}

static void
test_euler_from_mat (void)
{
  CrankEuler euler;
  CrankMatFloat3 mat;

  crank_mat_float3_init (&mat,
                         0.5000f, -0.5000f,  0.7071f,
                         0.8536f,  0.1464f, -0.5000f,
                         0.1464f,  0.8536f,  0.5000f);
  crank_euler_init_from_matrix3 (&euler, &mat);

  crank_assert_cmpfloat (euler.yaw, ==, G_PI_4);
  crank_assert_cmpfloat (euler.pitch, ==, G_PI_4);
  crank_assert_cmpfloat (euler.roll, ==, G_PI_4);
}

static void
test_euler_to_quat (void)
{
  CrankEuler euler;
  CrankQuatFloat quat;

  crank_euler_init_angle (&euler, G_PI_4, G_PI_4, G_PI_4);
  crank_euler_to_quaternion (&euler, &quat);

  crank_assert_cmpfloat (quat.w, ==, 0.84462f);
  crank_assert_cmpfloat (quat.x, ==, 0.19134f);
  crank_assert_cmpfloat (quat.y, ==, 0.46194f);
  crank_assert_cmpfloat (quat.z, ==, 0.19134f);
}

static void
test_euler_to_mat (void)
{
  CrankEuler euler;
  CrankMatFloat3 mat;

  crank_euler_init_angle (&euler, G_PI_4, G_PI_4, G_PI_4);
  crank_euler_to_matrix3 (&euler, &mat);

  crank_assert_cmpfloat (mat.m00, ==,  0.5000f);
  crank_assert_cmpfloat (mat.m01, ==, -0.5000f);
  crank_assert_cmpfloat (mat.m02, ==, -0.7071f);
  crank_assert_cmpfloat (mat.m10, ==,  0.1464f);
  crank_assert_cmpfloat (mat.m11, ==,  0.8536f);
  crank_assert_cmpfloat (mat.m12, ==, -0.5000f);
  crank_assert_cmpfloat (mat.m20, ==,  0.8536f);
  crank_assert_cmpfloat (mat.m21, ==,  0.1464f);
  crank_assert_cmpfloat (mat.m22, ==,  0.5000f);
}
