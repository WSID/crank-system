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

	GLib.Test.add_func ("/crank/base/mat/float/2/equal", test_2_equal);
	GLib.Test.add_func ("/crank/base/mat/float/2/to_string", test_2_to_string);
	GLib.Test.add_func ("/crank/base/mat/float/2/get", test_2_get);
	GLib.Test.add_func ("/crank/base/mat/float/2/get_row", test_2_get_row);
	GLib.Test.add_func ("/crank/base/mat/float/2/get_col", test_2_get_col);
	GLib.Test.add_func ("/crank/base/mat/float/2/tr", test_2_tr);
	GLib.Test.add_func ("/crank/base/mat/float/2/det", test_2_det);
	GLib.Test.add_func ("/crank/base/mat/float/2/cof", test_2_cof);
	GLib.Test.add_func ("/crank/base/mat/float/2/adj", test_2_adj);
	GLib.Test.add_func ("/crank/base/mat/float/2/neg", test_2_neg);
	GLib.Test.add_func ("/crank/base/mat/float/2/transpose", test_2_transpose);
	GLib.Test.add_func ("/crank/base/mat/float/2/inverse", test_2_inverse);
	GLib.Test.add_func ("/crank/base/mat/float/2/muls", test_2_muls);
	GLib.Test.add_func ("/crank/base/mat/float/2/divs", test_2_divs);
	GLib.Test.add_func ("/crank/base/mat/float/2/mulv", test_2_mulv);
	GLib.Test.add_func ("/crank/base/mat/float/2/add", test_2_add);
	GLib.Test.add_func ("/crank/base/mat/float/2/sub", test_2_sub);
	GLib.Test.add_func ("/crank/base/mat/float/2/mul", test_2_mul);
	GLib.Test.add_func ("/crank/base/mat/float/2/mixs", test_2_mixs);
	GLib.Test.add_func ("/crank/base/mat/float/2/mix", test_2_mix);
	
	GLib.Test.add_func ("/crank/base/mat/float/n/equal", test_n_equal);
	GLib.Test.add_func ("/crank/base/mat/float/n/to_string", test_n_to_string);
	GLib.Test.add_func ("/crank/base/mat/float/n/get", test_n_get);
	GLib.Test.add_func ("/crank/base/mat/float/n/get_row", test_n_get_row);
	GLib.Test.add_func ("/crank/base/mat/float/n/get_col", test_n_get_col);
	GLib.Test.add_func ("/crank/base/mat/float/n/tr", test_n_tr);
	GLib.Test.add_func ("/crank/base/mat/float/n/det", test_n_det);
	GLib.Test.add_func ("/crank/base/mat/float/n/cof", test_n_cof);
	GLib.Test.add_func ("/crank/base/mat/float/n/adj", test_n_adj);
	GLib.Test.add_func ("/crank/base/mat/float/n/neg", test_n_neg);
	GLib.Test.add_func ("/crank/base/mat/float/n/transpose", test_n_transpose);
	GLib.Test.add_func ("/crank/base/mat/float/n/inverse", test_n_inverse);
	GLib.Test.add_func ("/crank/base/mat/float/n/muls", test_n_muls);
	GLib.Test.add_func ("/crank/base/mat/float/n/divs", test_n_divs);
	GLib.Test.add_func ("/crank/base/mat/float/n/mulv", test_n_mulv);
	GLib.Test.add_func ("/crank/base/mat/float/n/add", test_n_add);
	GLib.Test.add_func ("/crank/base/mat/float/n/sub", test_n_sub);
	GLib.Test.add_func ("/crank/base/mat/float/n/mul", test_n_mul);
	GLib.Test.add_func ("/crank/base/mat/float/n/mixs", test_n_mixs);
	GLib.Test.add_func ("/crank/base/mat/float/n/mix", test_n_mix);
	
	GLib.Test.add_func ("/crank/base/mat/float/n/shuffle/row", test_n_shuffle_row);
	GLib.Test.add_func ("/crank/base/mat/float/n/shuffle/col", test_n_shuffle_col);

	GLib.Test.run ();

	return 0;
}


private bool float_eq (float a, float b, float delta = 0.0001f) {
	bool result = ((b-delta < a) && (a < b+delta));

	if (! result) warning ("%g != %g (diff=%g)", a, b, delta);

	return result;
}


private void test_2_equal () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 b = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 c = {0.0f, 0.0f,	0.0f, 0.0f};

	assert (  Crank.MatFloat2.equal (a, b));
	assert (! Crank.MatFloat2.equal (a, c));
}

private void test_2_to_string () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	assert (a.to_string () == "[[1, 2], [3, 4]]");
}

private void test_2_get () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};

	float_eq (a[0, 0], 1.0f);
	float_eq (a[0, 1], 2.0f);
	float_eq (a[1, 0], 3.0f);
	float_eq (a[1, 1], 4.0f);
}

private void test_2_get_row () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};

	Crank.VecFloat2 rv = a.get_row (0);

	float_eq (rv.x, 1.0f);
	float_eq (rv.y, 2.0f);

	rv = a.get_row (1);

	float_eq (rv.x, 3.0f);
	float_eq (rv.y, 4.0f);
}

private void test_2_get_col () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};

	Crank.VecFloat2 cv = a.get_col (0);

	float_eq (cv.x, 1.0f);
	float_eq (cv.y, 3.0f);

	cv = a.get_col (1);

	float_eq (cv.x, 2.0f);
	float_eq (cv.y, 4.0f);
}

private void test_2_tr () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	float_eq (a.tr, 5.0f);
}

private void test_2_det () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	float_eq (a.det, -2.0f);
}

private void test_2_cof () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 cof = a.cof;
	float_eq (cof.m00, 4.0f);
	float_eq (cof.m01, -3.0f);
	float_eq (cof.m10, -2.0f);
	float_eq (cof.m11, 1.0f);
}

private void test_2_adj () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 adj = a.adj;
	float_eq (adj.m00,  4.0f);
	float_eq (adj.m01, -2.0f);
	float_eq (adj.m10, -3.0f);
	float_eq (adj.m11,  1.0f);
}

private void test_2_neg () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	a = a.neg ();
	float_eq (a.m00, -1.0f);
	float_eq (a.m01, -2.0f);
	float_eq (a.m10, -3.0f);
	float_eq (a.m11, -4.0f);
}

private void test_2_transpose () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	a = a.transpose ();
	float_eq (a.m00, 1.0f);
	float_eq (a.m01, 3.0f);
	float_eq (a.m10, 2.0f);
	float_eq (a.m11, 4.0f);
}

private void test_2_inverse () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	a = a.inverse ();
	float_eq (a.m00, -2.0f);
	float_eq (a.m01,  1.0f);
	float_eq (a.m10,  1.5f);
	float_eq (a.m11, -0.5f);
}

private void test_2_muls () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	a = a.muls (2.0f);
	float_eq (a.m00, 2.0f);
	float_eq (a.m01, 4.0f);
	float_eq (a.m10, 6.0f);
	float_eq (a.m11, 8.0f);
}

private void test_2_divs () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	a = a.divs (2.0f);
	float_eq (a.m00, 0.5f);
	float_eq (a.m01, 1.0f);
	float_eq (a.m10, 1.5f);
	float_eq (a.m11, 2.0f);
}

private void test_2_mulv () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.VecFloat2 b = {3.0f, 4.0f};
	b = a.mulv (b);

	float_eq (b.x, 11.0f);
	float_eq (b.y, 25.0f);
}


private void test_2_add () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 b = {2.0f, 3.0f, 	5.0f, 7.0f};

	a = a.add (b);

	float_eq (a.m00, 3.0f);
	float_eq (a.m01, 5.0f);
	float_eq (a.m10, 8.0f);
	float_eq (a.m11, 11.0f);
}

private void test_2_sub () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 b = {2.0f, 3.0f, 	5.0f, 7.0f};

	a = a.sub (b);

	float_eq (a.m00, -1.0f);
	float_eq (a.m01, -1.0f);
	float_eq (a.m10, -2.0f);
	float_eq (a.m11, -3.0f);
}

private void test_2_mul () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 b = {3.0f, 6.0f, 	9.0f, 12.0f};
	
	a = a.mul (b);

	float_eq (a.m00, 21.0f);
	float_eq (a.m01, 30.0f);
	float_eq (a.m10, 45.0f);
	float_eq (a.m11, 66.0f);
}

private void test_2_mixs () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 b = {3.0f, 6.0f,	9.0f, 12.0f};
	a = a.mixs (b, 0.5f);

	float_eq (a.m00, 2.0f);
	float_eq (a.m01, 4.0f);
	float_eq (a.m10, 6.0f);
	float_eq (a.m11, 8.0f);
}

private void test_2_mix () {
	Crank.MatFloat2 a = {1.0f, 2.0f,	3.0f, 4.0f};
	Crank.MatFloat2 b = {3.0f, 6.0f,	9.0f, 12.0f};
	Crank.MatFloat2 c = {0.0f, 0.25f,	0.5f, 0.75f};
	a = a.mix (b, c);

	float_eq (a.m00, 1.0f);
	float_eq (a.m01, 3.0f);
	float_eq (a.m10, 6.0f);
	float_eq (a.m11, 10.0f);
}





private void test_n_equal () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
	Crank.MatFloatN b = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
	Crank.MatFloatN c = Crank.MatFloatN.arr (
		{{1.0f, 2.0f},
		 {3.0f, 4.0f},
		 {5.0f, 6.0f}});
		 
	assert (  Crank.MatFloatN.equal (a, b));
	assert (! Crank.MatFloatN.equal (a, c));
}

private void test_n_to_string () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});

	message (a.to_string ());
	assert (a.to_string () == "[[1, 2, 3], [4, 5, 6]]");
}

private void test_n_get () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});

	float_eq (a[0, 0], 1.0f);
	float_eq (a[0, 1], 2.0f);
	float_eq (a[0, 2], 3.0f);
	float_eq (a[1, 0], 4.0f);
	float_eq (a[1, 1], 5.0f);
	float_eq (a[1, 2], 6.0f);
}

private void test_n_get_row () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});

	Crank.VecFloatN rv = a.get_row (0);

	float_eq (rv[0], 1.0f);
	float_eq (rv[1], 2.0f);
	float_eq (rv[2], 3.0f);

	rv = a.get_row (1);

	float_eq (rv[0], 4.0f);
	float_eq (rv[1], 5.0f);
	float_eq (rv[2], 6.0f);
}

private void test_n_get_col () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});

	Crank.VecFloatN cv = a.get_col (0);

	float_eq (cv[0], 1.0f);
	float_eq (cv[1], 4.0f);

	cv = a.get_col (1);

	float_eq (cv[0], 2.0f);
	float_eq (cv[1], 5.0f);
	
	cv = a.get_col (2);

	float_eq (cv[0], 3.0f);
	float_eq (cv[1], 6.0f);
}

private void test_n_tr () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		 {0.0f, 2.0f, 0.0f, 3.0f, 1.0f},
		 {0.0f, 0.0f, 3.0f, 0.0f, 0.0f},
		 {1.0f, 3.0f, 0.0f, 4.0f, 0.0f},
		 {0.0f, 1.0f, 0.0f, 0.0f, 5.0f}} );
	float_eq (a.tr, 15.0f);
}

private void test_n_det () {
	GLib.Test.skip ("");
}

private void test_n_cof ()  {
	GLib.Test.skip ("");
}

private void test_n_adj ()  {
	GLib.Test.skip ("");
}

private void test_n_neg () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
		 
	a = a.neg ();
	
	//float_eq (a[0, 0], -1.0f);
	float_eq (a[0, 1], -2.0f);
	float_eq (a[0, 2], -3.0f);
	float_eq (a[1, 0], -4.0f);
	float_eq (a[1, 1], -5.0f);
	float_eq (a[1, 2], -6.0f);
}

private void test_n_transpose () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});

	a = a.transpose ();
	assert (a.row_size == 3);
	message ("%u", a.col_size);
	assert (a.col_size == 2);
	float_eq (a[0, 0], 1.0f);
	float_eq (a[0, 1], 4.0f);
	float_eq (a[1, 0], 2.0f);
	float_eq (a[1, 1], 5.0f);
	float_eq (a[2, 0], 3.0f);
	float_eq (a[2, 1], 6.0f);
}

private void test_n_inverse () {
	GLib.Test.skip ("");
}

private void test_n_muls () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
		 
	a = a.muls (3.0f);
	
	float_eq (a[0, 0], 3.0f);
	float_eq (a[0, 1], 6.0f);
	float_eq (a[0, 2], 9.0f);
	float_eq (a[1, 0], 12.0f);
	float_eq (a[1, 1], 15.0f);
	float_eq (a[1, 2], 18.0f);
}

private void test_n_divs () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
		 
	a = a.divs (2.0f);
	
	float_eq (a[0, 0], 0.5f);
	float_eq (a[0, 1], 1.0f);
	float_eq (a[0, 2], 1.5f);
	float_eq (a[1, 0], 2.0f);
	float_eq (a[1, 1], 2.5f);
	float_eq (a[1, 2], 3.0f);
}

private void test_n_mulv () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
	Crank.VecFloatN b = Crank.VecFloatN.arr (
		{2.0f, 3.0f, 5.0f});
		
	b = a.mulv (b);

	assert (b.size == 2);
	float_eq (b[0], 23.0f);
	float_eq (b[1], 53.0f);
}

private void test_n_add () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
	Crank.MatFloatN b = Crank.MatFloatN.arr (
		{{2.0f, 3.0f, 5.0f},
		 {7.0f, 11.0f, 13.0f}});

	a = a.add (b);

	float_eq (a[0, 0], 3.0f);
	float_eq (a[0, 1], 5.0f);
	float_eq (a[0, 2], 8.0f);
	float_eq (a[1, 0], 11.0f);
	float_eq (a[1, 1], 16.0f);
	float_eq (a[1, 2], 19.0f);
}

private void test_n_sub () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
	Crank.MatFloatN b = Crank.MatFloatN.arr (
		{{2.0f, 3.0f, 5.0f},
		 {7.0f, 11.0f, 13.0f}});

	a = a.sub (b);

	float_eq (a[0, 0], -1.0f);
	float_eq (a[0, 1], -1.0f);
	float_eq (a[0, 2], -2.0f);
	float_eq (a[1, 0], -3.0f);
	float_eq (a[1, 1], -6.0f);
	float_eq (a[1, 2], -7.0f);
}


private void test_n_mul () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
	Crank.MatFloatN b = Crank.MatFloatN.arr (
		{{3.0f, 2.0f, 1.0f},
		 {2.0f, 1.0f, 0.0f},
		 {1.0f, 0.0f, -1.0f}});

	a = a.mul (b);
	
	assert (a.row_size == 2);
	assert (a.col_size == 3);
	float_eq (a[0, 0], 10.0f);
	float_eq (a[0, 1], 4.0f);
	float_eq (a[0, 2], -2.0f);
	float_eq (a[1, 0], 28.0f);
	float_eq (a[1, 1], 13.0f);
	float_eq (a[1, 2], -2.0f);
}

private void test_n_mixs () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
	Crank.MatFloatN b = Crank.MatFloatN.arr (
		{{3.0f, 6.0f, 9.0f},
		 {12.0f, 15.0f, 18.0f}});
		 
	a = a.mixs (b, 0.5f);

	float_eq (a[0, 0], 2.0f);
	float_eq (a[0, 1], 4.0f);
	float_eq (a[0, 2], 6.0f);
	float_eq (a[1, 0], 8.0f);
	float_eq (a[1, 1], 10.0f);
	float_eq (a[1, 2], 12.0f);
}

private void test_n_mix () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 2.0f, 3.0f},
		 {4.0f, 5.0f, 6.0f}});
	Crank.MatFloatN b = Crank.MatFloatN.arr (
		{{3.0f, 6.0f, 9.0f},
		 {12.0f, 15.0f, 18.0f}});
	Crank.MatFloatN c = Crank.MatFloatN.arr (
		{{0.0f, 0.2f, 0.4f},
		 {0.6f, 0.8f, 1.0f}});
	a = a.mix (b, c);

	float_eq (a[0, 0], 1.0f);
	float_eq (a[0, 1], 2.8f);
	float_eq (a[0, 2], 5.4f);
	float_eq (a[1, 0], 8.8f);
	float_eq (a[1, 1], 13.0f);
	float_eq (a[1, 2], 18.0f);
}

private void test_n_shuffle_row () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 3.0f},
		 {7.0f, 2.0f},
		 {1.0f, 4.0f},
		 {3.0f, 1.0f}} );
	
	Crank.Permutation p = Crank.Permutation.arr ({1, 3, 0, 2});
	
	a = a.shuffle_row (p);
	
	assert (float_eq (a[0, 0], 7.0f));
	assert (float_eq (a[0, 1], 2.0f));
	assert (float_eq (a[1, 0], 3.0f));
	assert (float_eq (a[1, 1], 1.0f));
	assert (float_eq (a[2, 0], 1.0f));
	assert (float_eq (a[2, 1], 3.0f));
	assert (float_eq (a[3, 0], 1.0f));
	assert (float_eq (a[3, 1], 4.0f));
}

private void test_n_shuffle_col () {
	Crank.MatFloatN a = Crank.MatFloatN.arr (
		{{1.0f, 7.0f, 1.0f, 3.0f},
		 {3.0f, 2.0f, 4.0f, 1.0f}});
	
	Crank.Permutation p = Crank.Permutation.arr ({1, 3, 0, 2});
	
	a = a.shuffle_col (p);
	
	assert (float_eq (a[0, 0], 7.0f));
	assert (float_eq (a[0, 1], 3.0f));
	assert (float_eq (a[0, 2], 1.0f));
	assert (float_eq (a[0, 3], 1.0f));
	assert (float_eq (a[1, 0], 2.0f));
	assert (float_eq (a[1, 1], 1.0f));
	assert (float_eq (a[1, 2], 3.0f));
	assert (float_eq (a[1, 3], 4.0f));
}
