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

using GLib;
using Crank;

int main (string[] args) {
	GLib.Test.init (ref args);

	GLib.Test.set_nonfatal_assertions ();

	GLib.Test.add_func ("/crank/shape/euler/from/quat",
				        test_euler_from_quat);

	GLib.Test.add_func ("/crank/shape/euler/from/mat",
				        test_euler_from_mat);

	GLib.Test.add_func ("/crank/shape/euler/to/quat",
				        test_euler_to_quat);

	GLib.Test.add_func ("/crank/shape/euler/to/mat",
				        test_euler_to_mat);

	return GLib.Test.run ();
}

void test_euler_from_quat () {
	Crank.Euler euler;
	Crank.QuatFloat quat;

	Crank.QuatFloat quat_rot[3];

	GLib.Test.message ("ZYX");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 0, 1);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 1, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 1, 0, 0);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_ZYX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("YXZ");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 1, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 1, 0, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 0, 1);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_YXZ);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("XZY");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 1, 0, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 0, 1);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 1, 0);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_XZY);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("XYZ");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 1, 0, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 1, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 0, 1);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_XYZ);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("ZXY");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 0, 1);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 1, 0, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 1, 0);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_ZXY);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);

	GLib.Test.message ("YZX");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 1, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 0, 1);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 1, 0, 0);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_YZX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);




	GLib.Test.message ("XYX");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 1, 0, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 1, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 1, 0, 0);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_XYX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);

	GLib.Test.message ("YZY");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 1, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 0, 1);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 1, 0);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_YZY);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);

	GLib.Test.message ("ZXZ");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 0, 1);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 1, 0, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 0, 1);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_ZXZ);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);

	GLib.Test.message ("YXY");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 1, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 1, 0, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 1, 0);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_YXY);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);

	GLib.Test.message ("ZYZ");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 0, 1);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 1, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 0, 1);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_ZYZ);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);

	GLib.Test.message ("XZX");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 1, 0, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 0, 1);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 1, 0, 0);

	quat = quat_rot[0].mul (quat_rot[1]);
	quat.mul_self (quat_rot[2]);

	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_XZX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);
}

void test_euler_from_mat () {
	Crank.Euler euler;
	Crank.MatFloat3 mat;

	Crank.MatFloat3 mat_rot[3];

	GLib.Test.message ("ZYX");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 0, 1);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 1, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 1, 0, 0);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_ZYX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("YXZ");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 1, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 1, 0, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 0, 1);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_YXZ);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("XZY");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 1, 0, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 0, 1);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 1, 0);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_XZY);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("XYZ");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 1, 0, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 1, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 0, 1);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_XYZ);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("ZXY");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 0, 1);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 1, 0, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 1, 0);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_ZXY);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("YZX");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 1, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 0, 1);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 1, 0, 0);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_YZX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("XYX");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 1, 0, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 1, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 1, 0, 0);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_XYX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("YZY");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 1, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 0, 1);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 1, 0);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_YZY);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("ZXZ");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 0, 1);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 1, 0, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 0, 1);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_ZXZ);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("YXY");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 1, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 1, 0, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 1, 0);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_YXY);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("ZYZ");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 0, 1);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 1, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 0, 1);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_ZYZ);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);


	GLib.Test.message ("XZX");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 1, 0, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 0, 1);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 1, 0, 0);

	mat = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_XZX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI / 4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI / 3);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI / 2);
}

void test_euler_to_quat () {
	Crank.Euler euler;
	Crank.QuatFloat quat;

	Crank.QuatFloat quat_rot[3];
	Crank.QuatFloat quat_res;


	GLib.Test.message ("ZYX");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 0, 1);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 1, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 1, 0, 0);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_ZYX);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("YXZ");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 1, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 1, 0, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 0, 1);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_YXZ);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("XZY");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 1, 0, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 0, 1);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 1, 0);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_XZY);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("XYZ");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 1, 0, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 1, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 0, 1);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_XYZ);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("ZXY");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 0, 1);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 1, 0, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 1, 0);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_ZXY);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("YZX");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 1, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 0, 1);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 1, 0, 0);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_YZX);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("XYX");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 1, 0, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 1, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 1, 0, 0);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_XYX);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("YZY");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 1, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 0, 1);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 1, 0);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_YZY);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("ZXZ");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 0, 1);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 1, 0, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 0, 1);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_ZXZ);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("YXY");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 1, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 1, 0, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 1, 0);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_YXY);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("ZYZ");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 0, 0, 1);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 1, 0);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 0, 0, 1);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_ZYZ);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);


	GLib.Test.message ("XZX");
	quat_rot[0] = Crank.QuatFloat.urot ((float)Math.PI / 4, 1, 0, 0);
	quat_rot[1] = Crank.QuatFloat.urot ((float)Math.PI / 3, 0, 0, 1);
	quat_rot[2] = Crank.QuatFloat.urot ((float)Math.PI / 2, 1, 0, 0);
	quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2]);

	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_XZX);
	quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, quat_res.w);
	Crank.assert_eqfloat (quat.x, quat_res.x);
	Crank.assert_eqfloat (quat.y, quat_res.y);
	Crank.assert_eqfloat (quat.z, quat_res.z);
}

void test_euler_to_mat () {
	Crank.Euler euler;
	Crank.MatFloat3 mat;

	Crank.MatFloat3 mat_res;
	Crank.MatFloat3 mat_rot[3];


	GLib.Test.message ("ZYX");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 0, 1);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 1, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 1, 0, 0);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_ZYX);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("YXZ");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 1, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 1, 0, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 0, 1);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_YXZ);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("XZY");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 1, 0, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 0, 1);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 1, 0);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_XZY);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("XYZ");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 1, 0, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 1, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 0, 1);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_XYZ);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("ZXY");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 0, 1);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 1, 0, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 1, 0);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_ZXY);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("YZX");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 1, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 0, 1);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 1, 0, 0);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_YZX);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);




	GLib.Test.message ("XYX");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 1, 0, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 1, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 1, 0, 0);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_XYX);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("YZY");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 1, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 0, 1);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 1, 0);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_YZY);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("ZXZ");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 0, 1);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 1, 0, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 0, 1);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_ZXZ);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("YXY");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 1, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 1, 0, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 1, 0);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_YXY);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("ZYZ");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 0, 0, 1);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 1, 0);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 0, 0, 1);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_ZYZ);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);

	GLib.Test.message ("XZX");
	mat_rot[0] = Crank.MatFloat3.urot ((float)Math.PI / 4, 1, 0, 0);
	mat_rot[1] = Crank.MatFloat3.urot ((float)Math.PI / 3, 0, 0, 1);
	mat_rot[2] = Crank.MatFloat3.urot ((float)Math.PI / 2, 1, 0, 0);

	mat_res = mat_rot[0].mul (mat_rot[1]). mul (mat_rot[2]);
	euler = Crank.Euler.angle ((float)Math.PI / 4,
							   (float)Math.PI / 3,
							   (float)Math.PI / 2,
							   Crank.EulerType.IN_XZX);
	mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00, mat_res.m00);
	Crank.assert_eqfloat (mat.m01, mat_res.m01);
	Crank.assert_eqfloat (mat.m02, mat_res.m02);
	Crank.assert_eqfloat (mat.m10, mat_res.m10);
	Crank.assert_eqfloat (mat.m11, mat_res.m11);
	Crank.assert_eqfloat (mat.m12, mat_res.m12);
	Crank.assert_eqfloat (mat.m20, mat_res.m20);
	Crank.assert_eqfloat (mat.m21, mat_res.m21);
	Crank.assert_eqfloat (mat.m22, mat_res.m22);
}
