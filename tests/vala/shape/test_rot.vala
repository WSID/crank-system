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

public int main (string[] args) {
	GLib.Test.init (ref args);

	GLib.Test.add_func ("/crank/shape/rot/vec2/rot",
			    test_vec2_rot);

	GLib.Test.add_func ("/crank/shape/rot/vec2/left",
			    test_vec2_left);

	GLib.Test.add_func ("/crank/shape/rot/vec2/right",
			    test_vec2_right);

	return GLib.Test.run ();
}

public void test_vec2_rot () {
	Crank.VecFloat2 a = {0.9950f, 0.0998f};
	Crank.VecFloat2 b = Crank.rot_vec2_rot (a, 0.5f);

	Crank.assert_eqfloat (b.x, 0.8253f);
	Crank.assert_eqfloat (b.y, 0.5646f);
}

public void test_vec2_left () {
	Crank.VecFloat2 a = {0.9950f, 0.0998f};
	Crank.VecFloat2 b = Crank.rot_vec2_left (a);

	Crank.assert_eqfloat (b.x, -0.0998f);
	Crank.assert_eqfloat (b.y, 0.9950f);
}

public void test_vec2_right () {
	Crank.VecFloat2 a = {0.9950f, 0.0998f};
	Crank.VecFloat2 b = Crank.rot_vec2_right (a);

	Crank.assert_eqfloat (b.x, 0.0998f);
	Crank.assert_eqfloat (b.y, -0.9950f);
}
