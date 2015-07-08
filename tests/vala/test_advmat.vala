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

int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func ("/crank/base/advmat/lu/mat/float/n",
		test_lu );
	
	GLib.Test.run ();
	
	return 0;
}


private bool float_eq (float a, float b, float delta = 0.0001f) {
	bool result = ((b-delta < a) && (a < b+delta));

	if (! result) warning ("%g != %g (diff=%g)", a, b, delta);

	return result;
}



private void test_lu () {
	Crank.MatFloatN	a = Crank.MatFloatN.arr ( {
		{3.0f,	12.0f,	21.0f},
		{8.0f,	39.0f,	84.0f},
		{2.0f,	16.0f,	49.0f}}	);
	
	Crank.MatFloatN l;
	Crank.MatFloatN u;
	
	Crank.lu_mat_float_n (a, out l, out u);
	
	assert (float_eq (l[0, 0], 3));
	assert (float_eq (l[0, 1], 0));
	assert (float_eq (l[0, 2], 0));
	
	assert (float_eq (l[1, 0], 8));
	assert (float_eq (l[1, 1], 7));
	assert (float_eq (l[1, 2], 0));
	
	assert (float_eq (l[2, 0], 2));
	assert (float_eq (l[2, 1], 8));
	assert (float_eq (l[2, 2], 3));
	
	
	assert (float_eq (u[0, 0], 1));
	assert (float_eq (u[0, 1], 4));
	assert (float_eq (u[0, 2], 7));
	
	assert (float_eq (u[1, 0], 0));
	assert (float_eq (u[1, 1], 1));
	assert (float_eq (u[1, 2], 4));
	
	assert (float_eq (u[2, 0], 0));
	assert (float_eq (u[2, 1], 0));
	assert (float_eq (u[2, 2], 1));
}

