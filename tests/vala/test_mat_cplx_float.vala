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

	
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/equal", test_n_equal);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/to_string", test_n_to_string);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/get", test_n_get);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/get_row", test_n_get_row);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/get_col", test_n_get_col);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/slice", test_n_slice);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/tr", test_n_tr);
	GLib.Test.add_func ("/crank/base/mat/cplxfloat/n/det", test_n_det);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/cof", test_n_cof);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/adj", test_n_adj);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/diag", test_n_diagv);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/neg", test_n_neg);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/transpose", test_n_transpose);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/inverse", test_n_inverse);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/mulrs", test_n_mulrs);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/divrs", test_n_divrs);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/mulv", test_n_mulv);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/add", test_n_add);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/sub", test_n_sub);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/mul", test_n_mul);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/mixs", test_n_mixs);
	
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/shuffle/row", test_n_shuffle_row);
	GLib.Test.add_func ("/crank/base/mat/cplx/float/n/shuffle/col", test_n_shuffle_col);

	GLib.Test.run ();

	return 0;
}



private void test_n_equal () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f );
	Crank.MatCplxFloatN b = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f );
	Crank.MatCplxFloatN c = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f );
		 
	assert (  a.equal (b));
	assert (! a.equal (c));
}

private void test_n_to_string () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f );

	assert (a.to_string () == "[[1 + (2i), 3 + (4i)], [5 + (6i), 7 + (8i)]]");
}

private void test_n_get () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f );

	Crank.assert_eqcplxfloat_cimm (a[0, 0], 1.0f, 2.0f);
	Crank.assert_eqcplxfloat_cimm (a[0, 1], 3.0f, 4.0f);
	Crank.assert_eqcplxfloat_cimm (a[1, 0], 5.0f, 6.0f);
	Crank.assert_eqcplxfloat_cimm (a[1, 1], 7.0f, 8.0f);
}

private void test_n_get_row () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f);

	Crank.VecCplxFloatN rv = a.get_row (0);

	Crank.assert_eqcplxfloat_cimm (rv[0], 1.0f, 2.0f);
	Crank.assert_eqcplxfloat_cimm (rv[1], 3.0f, 4.0f);

	rv = a.get_row (1);

	Crank.assert_eqcplxfloat_cimm (rv[0], 5.0f, 6.0f);
	Crank.assert_eqcplxfloat_cimm (rv[1], 7.0f, 8.0f);
}

private void test_n_get_col () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f);

	Crank.VecCplxFloatN rv = a.get_col (0);

	Crank.assert_eqcplxfloat_cimm (rv[0], 1.0f, 2.0f);
	Crank.assert_eqcplxfloat_cimm (rv[1], 5.0f, 6.0f);

	rv = a.get_col (1);

	Crank.assert_eqcplxfloat_cimm (rv[0], 3.0f, 4.0f);
	Crank.assert_eqcplxfloat_cimm (rv[1], 7.0f, 8.0f);
}


private void test_n_slice () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (3, 3,
		1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
		4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
		7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);
	
	Crank.MatCplxFloatN b = a.slice (1, 1, 3, 2);
	assert (b.row_size == 2);
	assert (b.col_size == 1);
	Crank.assert_eqcplxfloat_cimm (b[0,0], 5.0f, 5.5f);
	Crank.assert_eqcplxfloat_cimm (b[1,0], 8.0f, 4.0f);
}

private void test_n_tr () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (3, 3,
		1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
		4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
		7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);
	
	Crank.assert_eqcplxfloat_cimm  (a.tr, 15.0f, 11.5f);
}

private void test_n_det () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (3, 3,
		1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
		4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
		7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);
	
	Crank.assert_eqcplxfloat_cimm  (a.det, 4.0f, -1.75f);
}

private void test_n_diagv () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (3, 3,
		1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
		4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
		7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);

	Crank.VecCplxFloatN d = a.diagv;
	
	assert (d.size == 3);
	Crank.assert_eqcplxfloat_cimm  (d[0], 1.0f, 1.5f);
	Crank.assert_eqcplxfloat_cimm  (d[1], 5.0f, 5.5f);
	Crank.assert_eqcplxfloat_cimm  (d[2], 9.0f, 4.5f);
}

private void test_n_cof ()  {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (3, 3,
		1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
		4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
		7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);
	
	Crank.MatCplxFloatN r = a.cof;
	
	Crank.assert_eqcplxfloat_cimm (r[0,0],	-1.7500f,  -4.0000f);
	Crank.assert_eqcplxfloat_cimm (r[0,1],	 3.5000f,   8.0000f);
	Crank.assert_eqcplxfloat_cimm (r[0,2],	-1.7500f,  -4.0000f);
	Crank.assert_eqcplxfloat_cimm (r[1,0],	-0.7500f,  16.5000f);
	Crank.assert_eqcplxfloat_cimm (r[1,1],	-3.0000f, -24.0000f);
	Crank.assert_eqcplxfloat_cimm (r[1,2],	 3.2500f,   8.5000f);
	Crank.assert_eqcplxfloat_cimm (r[2,0],	 5.5000f, -11.0000f);
	Crank.assert_eqcplxfloat_cimm (r[2,1],	-4.5000f,  16.0000f);
	Crank.assert_eqcplxfloat_cimm (r[2,2],	 0.0000f,  -6.0000f);
}

private void test_n_adj ()  {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (3, 3,
		1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
		4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
		7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);
	
	Crank.MatCplxFloatN r = a.adj;
	
	Crank.assert_eqcplxfloat_cimm (r[0, 0],	-1.7500f,  -4.0000f);
	Crank.assert_eqcplxfloat_cimm (r[0, 1],	-0.7500f,  16.5000f);
	Crank.assert_eqcplxfloat_cimm (r[0, 2],	 5.5000f, -11.0000f);
	Crank.assert_eqcplxfloat_cimm (r[1, 0],	 3.5000f,   8.0000f);
	Crank.assert_eqcplxfloat_cimm (r[1, 1],	-3.0000f, -24.0000f);
	Crank.assert_eqcplxfloat_cimm (r[1, 2],	-4.5000f,  16.0000f);
	Crank.assert_eqcplxfloat_cimm (r[2, 0],	-1.7500f,  -4.0000f);
	Crank.assert_eqcplxfloat_cimm (r[2, 1],	 3.2500f,   8.5000f);
	Crank.assert_eqcplxfloat_cimm (r[2, 2],	 0.0000f,  -6.0000f);
}

private void test_n_neg () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f);
		 
	Crank.MatCplxFloatN b = a.neg ();
	
	Crank.assert_eqcplxfloat_cimm (b[0, 0], -1.0f, -2.0f);
	Crank.assert_eqcplxfloat_cimm (b[0, 1], -3.0f, -4.0f);
	Crank.assert_eqcplxfloat_cimm (b[1, 0], -5.0f, -6.0f);
	Crank.assert_eqcplxfloat_cimm (b[1, 1], -7.0f, -8.0f);
}

private void test_n_transpose () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 3,
		1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);

	Crank.MatCplxFloatN b = a.transpose ();
	
	assert (b.row_size == 3);
	assert (b.col_size == 2);
	
	Crank.assert_eqcplxfloat_cimm  (b[0, 0], 1.0f, 2.0f);
	Crank.assert_eqcplxfloat_cimm  (b[0, 1], 7.0f, 8.0f);
	Crank.assert_eqcplxfloat_cimm  (b[1, 0], 3.0f, 4.0f);
	Crank.assert_eqcplxfloat_cimm  (b[1, 1], 9.0f, 10.0f);
	Crank.assert_eqcplxfloat_cimm  (b[2, 0], 5.0f, 6.0f);
	Crank.assert_eqcplxfloat_cimm  (b[2, 1], 11.0f, 12.0f);
}

private void test_n_inverse () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (3, 3,
		1.0f, 1.5f,		2.0f, 2.5f,		3.0f, 4.5f,
		4.0f, 4.5f,		5.0f, 5.5f,		6.0f, 6.5f,
		7.0f, 3.5f,		8.0f, 4.0f,		9.0f, 4.5f	);
	
	Crank.MatCplxFloatN r = a.inverse ();
	
	Crank.assert_eqcplxfloat_cimm (r[0,0],	 0.0000f,   -1.0000f);
	Crank.assert_eqcplxfloat_cimm (r[0,1],	-1.6721f,    3.3934f);
	Crank.assert_eqcplxfloat_cimm (r[0,2],	 2.1639f,   -1.8033f);
	Crank.assert_eqcplxfloat_cimm (r[1,0],	 0.0000f,    2.0000f);
	Crank.assert_eqcplxfloat_cimm (r[1,1],	 1.5738f,   -5.3115f);
	Crank.assert_eqcplxfloat_cimm (r[1,2],	-2.4131f,    2.9443f);
	Crank.assert_eqcplxfloat_cimm (r[2,0],	 0.0000f,   -1.0000f);
	Crank.assert_eqcplxfloat_cimm (r[2,1],	-0.0984f,    2.0820f);
	Crank.assert_eqcplxfloat_cimm (r[2,2],	 0.5508f,   -1.2590f);
}

private void test_n_mulrs () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f);
		 
	a = a.mulrs (2.0f);
	
	Crank.assert_eqcplxfloat_cimm  (a[0, 0], 2.0f, 4.0f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 1], 6.0f, 8.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 0], 10.0f, 12.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 1], 14.0f, 16.0f);
}

private void test_n_divrs () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f);
		 
	a = a.divrs (2.0f);
	
	Crank.assert_eqcplxfloat_cimm  (a[0, 0], 0.5f, 1.0f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 1], 1.5f, 2.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 0], 2.5f, 3.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 1], 3.5f, 4.0f);
}

private void test_n_mulv () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	Crank.VecCplxFloatN b = Crank.VecCplxFloatN.uc (2,
		2.0f, 3.0f, 5.0f, 7.0f);
		
	b = a.mulv (b);

	assert (b.size == 2);
	Crank.assert_eqcplxfloat_cimm  (b[0], -17.0f, 48.0f);
	Crank.assert_eqcplxfloat_cimm  (b[1], -26.0f, 99.0f);
}

private void test_n_add () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	Crank.MatCplxFloatN b = Crank.MatCplxFloatN.uc (2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f);

	a = a.add (b);

	Crank.assert_eqcplxfloat_cimm  (a[0, 0], 3.0f, 5.0f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 1], 8.0f, 11.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 0], 8.0f, 7.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 1], 7.0f, 10.0f);
}

private void test_n_sub () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	Crank.MatCplxFloatN b = Crank.MatCplxFloatN.uc (2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f);

	a = a.sub (b);

	Crank.assert_eqcplxfloat_cimm  (a[0, 0], -1.0f, -1.0f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 1], -2.0f, -3.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 0], 0.0f, 3.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 1], 5.0f, 4.0f);
}


private void test_n_mul () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	Crank.MatCplxFloatN b = Crank.MatCplxFloatN.uc (2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f);

	a = a.sub (b);

	Crank.assert_eqcplxfloat_cimm  (a[0, 0], -1.0f, -1.0f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 1], -2.0f, -3.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 0], 0.0f, 3.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 1], 5.0f, 4.0f);
}

private void test_n_mixs () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (2, 2,
		1.0f, 2.0f, 3.0f, 4.0f,
		4.0f, 5.0f, 6.0f, 7.0f);
	Crank.MatCplxFloatN b = Crank.MatCplxFloatN.uc (2, 2,
		2.0f, 3.0f, 5.0f, 7.0f,
		4.0f, 2.0f, 1.0f, 3.0f);
		 
	a = a.mixs (b, 0.5f);

	Crank.assert_eqcplxfloat_cimm  (a[0, 0], 1.5f, 2.5f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 1], 4.0f, 5.5f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 0], 4.0f, 3.5f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 1], 3.5f, 5.0f);
}

private void test_n_shuffle_row () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (4, 1,
		1.0f, 3.0f,
		7.0f, 2.0f,
		1.0f, 4.0f,
		3.0f, 1.0f );
	
	Crank.Permutation p = Crank.Permutation.arr ({1, 3, 0, 2});
	
	a = a.shuffle_row (p);

	Crank.assert_eqcplxfloat_cimm  (a[0, 0], 7.0f, 2.0f);
	Crank.assert_eqcplxfloat_cimm  (a[1, 0], 3.0f, 1.0f);
	Crank.assert_eqcplxfloat_cimm  (a[2, 0], 1.0f, 3.0f);
	Crank.assert_eqcplxfloat_cimm  (a[3, 0], 1.0f, 4.0f);
}

private void test_n_shuffle_col () {
	Crank.MatCplxFloatN a = Crank.MatCplxFloatN.uc (1, 4,
		1.0f, 3.0f,		7.0f, 2.0f,		1.0f, 4.0f,		3.0f, 1.0f );
	
	Crank.Permutation p = Crank.Permutation.arr ({1, 3, 0, 2});
	
	a = a.shuffle_col (p);

	Crank.assert_eqcplxfloat_cimm  (a[0, 0], 7.0f, 2.0f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 1], 3.0f, 1.0f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 2], 1.0f, 3.0f);
	Crank.assert_eqcplxfloat_cimm  (a[0, 3], 1.0f, 4.0f);
}
