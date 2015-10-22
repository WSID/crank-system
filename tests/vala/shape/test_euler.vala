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

	quat = Crank.QuatFloat (0.84462f, 0.19134f, 0.46194f, 0.19134f);
	euler = Crank.Euler.from_quaternion (quat, Crank.EulerType.IN_ZYX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI_4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI_4);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI_4);
}

void test_euler_from_mat () {
	Crank.Euler euler;
	Crank.MatFloat3 mat;

	mat = Crank.MatFloat3 (0.5000f, -0.1464f,  0.8536f,
						   0.5000f,  0.8536f, -0.1464f,
						  -0.7071f,  0.5000f,  0.5000f);
	euler = Crank.Euler.from_matrix3 (mat, Crank.EulerType.IN_ZYX);

	Crank.assert_eqfloat (euler.angle1, (float)Math.PI_4);
	Crank.assert_eqfloat (euler.angle2, (float)Math.PI_4);
	Crank.assert_eqfloat (euler.angle3, (float)Math.PI_4);
}

void test_euler_to_quat () {
	Crank.Euler euler = Crank.Euler.angle ((float)Math.PI_4,
											(float)Math.PI_4,
											(float)Math.PI_4,
											Crank.EulerType.IN_ZYX);
	Crank.QuatFloat quat = euler.to_quaternion ();

	Crank.assert_eqfloat (quat.w, 0.84462f);
	Crank.assert_eqfloat (quat.x, 0.19134f);
	Crank.assert_eqfloat (quat.y, 0.46194f);
	Crank.assert_eqfloat (quat.z, 0.19134f);
}

void test_euler_to_mat () {
	Crank.Euler euler = Crank.Euler.angle ((float)Math.PI_4,
											(float)Math.PI_4,
											(float)Math.PI_4,
											Crank.EulerType.IN_ZYX);
	Crank.MatFloat3 mat = euler.to_matrix3 ();

	Crank.assert_eqfloat (mat.m00,  0.5000f);
	Crank.assert_eqfloat (mat.m01, -0.1464f);
	Crank.assert_eqfloat (mat.m02,  0.8536f);
	Crank.assert_eqfloat (mat.m10,  0.5000f);
	Crank.assert_eqfloat (mat.m11,  0.8536f);
	Crank.assert_eqfloat (mat.m12, -0.1464f);
	Crank.assert_eqfloat (mat.m20, -0.7071f);
	Crank.assert_eqfloat (mat.m21,  0.5000f);
	Crank.assert_eqfloat (mat.m22,  0.5000f);
}
