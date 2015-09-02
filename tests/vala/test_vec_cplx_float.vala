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
	
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/get", test_n_get);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/insert", test_n_insert);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/remove", test_n_remove);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/foreach", test_n_foreach);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/equal", test_n_equal);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/magn", test_n_magn);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/unit", test_n_unit);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/muls", test_n_muls);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/divs", test_n_divs);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/mulrs", test_n_mulrs);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/divrs", test_n_divrs);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/add", test_n_add);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/sub", test_n_sub);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/dot", test_n_dot);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/cmpmul", test_n_cmpmul);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/cmpdiv", test_n_cmpdiv);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/cmpeq", test_n_cmpeq);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/mulrm", test_n_mulrm);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/mixs", test_n_mixs);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/mix", test_n_mix);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/init/arruc", test_n_init_arruc);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/init/ucarr", test_n_init_ucarr);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/init/ucv", test_n_init_ucv);
	GLib.Test.add_func ("/crank/base/vec/cplx/float/n/init/fill_uc", test_n_init_fill_uc);
	
	
	GLib.Test.run ();
	
	return 0;
}


private bool float_eq (float a, float b, float delta = 0.0001f) {
	bool result = ((b-delta < a) && (a < b+delta));
	
	if (! result) warning ("%g != %g (diff=%g)", a, b, delta);
	
	return result;
}




private void test_n_get () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 3.0f));
	assert (float_eq (v.imag, 4.0f));
	
	v = a[1];
	assert (float_eq (v.real, 5.0f));
	assert (float_eq (v.imag, 12.0f));
}


private void test_n_insert () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	a.insert (1, {5.0f, 10.0f});

	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 3.0f));
	assert (float_eq (v.imag, 4.0f));
	
	v = a[1];
	assert (float_eq (v.real, 5.0f));
	assert (float_eq (v.imag, 10.0f));
	
	v = a[2];
	assert (float_eq (v.real, 5.0f));
	assert (float_eq (v.imag, 12.0f));
}


private void test_n_remove () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	a.remove (0);

	Crank.CplxFloat	v = a[0];
	
	assert (a.size == 1);
	assert (float_eq (v.real, 5.0f));
	assert (float_eq (v.imag, 12.0f));
}


private void test_n_foreach () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.CplxFloat		sum = {0.0f, 0.0f};

	a.foreach ((v) => {
		sum = sum.add (v);
		return true;
	});

	assert (float_eq (sum.real, 8.0f));
	assert (float_eq (sum.imag, 16.0f));
}


private void test_n_equal () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(2, 2.0f, 3.0f, 5.0f, 10.0f);
	Crank.VecCplxFloatN	c = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	assert (! a.equal (b));
	assert (  a.equal (c));
}

private void test_n_magn () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	assert (float_eq (a.magn_sq, 194.0f));
	assert (float_eq (a.magn, 13.9284f));
}


private void test_n_unit () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);

	a = a.unit ();
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 0.2154f));
	assert (float_eq (v.imag, 0.2872f));
	
	v = a[1];
	assert (float_eq (v.real, 0.3590f));
	assert (float_eq (v.imag, 0.8615f));
}

private void test_n_muls () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	a = a.muls ({2.0f, 3.0f});
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, -6.0f));
	assert (float_eq (v.imag, 17.0f));
	
	v = a[1];
	assert (float_eq (v.real, -26.0f));
	assert (float_eq (v.imag, 39.0f));
}


private void test_n_divs () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	a = a.divs ({2.0f, 3.0f});
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 1.3846f));
	assert (float_eq (v.imag, -0.0769f));
	
	v = a[1];
	assert (float_eq (v.real, 3.5385f));
	assert (float_eq (v.imag, 0.6923f));
}

private void test_n_mulrs () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	a = a.mulrs (2.0f);
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 6.0f));
	assert (float_eq (v.imag, 8.0f));
	
	v = a[1];
	assert (float_eq (v.real, 10.0f));
	assert (float_eq (v.imag, 24.0f));
}


private void test_n_divrs () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	
	a = a.divrs (2.0f);
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 1.5f));
	assert (float_eq (v.imag, 2.0f));
	
	v = a[1];
	assert (float_eq (v.real, 2.5f));
	assert (float_eq (v.imag, 6.0f));
}



private void test_n_add () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	a = a.add (b);
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 5.0f));
	assert (float_eq (v.imag, 7.0f));
	
	v = a[1];
	assert (float_eq (v.real, 10.0f));
	assert (float_eq (v.imag, 22.0f));
}


private void test_n_sub () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	a = a.sub (b);
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 1.0f));
	assert (float_eq (v.imag, 1.0f));
	
	v = a[1];
	assert (float_eq (v.real, 0.0f));
	assert (float_eq (v.imag, 2.0f));
}


private void test_n_dot () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	Crank.CplxFloat v = a.dot (b);
	assert (float_eq (v.real, 163.0f));
	assert (float_eq (v.imag, 9.0f));
}


private void test_n_cmpmul () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	a = a.cmpmul (b);
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, -6.0f));
	assert (float_eq (v.imag, 17.0f));
	
	v = a[1];
	assert (float_eq (v.real, -95.0f));
	assert (float_eq (v.imag, 110.0f));
}

private void test_n_cmpdiv () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	a = a.cmpdiv (b);

	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 1.3846f));
	assert (float_eq (v.imag, -0.0769f));
	
	v = a[1];
	assert (float_eq (v.real, 1.16f));
	assert (float_eq (v.imag, 0.08f));
}

private void test_n_cmpeq () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(3, 2.0f, 3.0f, 4.0f, 6.0f, 17.0f, 20.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(3, 2.0f, 2.0f, 4.0f, 6.0f, 53.0f, 55.0f);
	
	Crank.VecBoolN	r = a.cmpeq (b);
	
	assert (! r[0]);
	assert (  r[1]);
	assert (! r[2]);
}


private void test_n_mulrm () {
	Crank.VecCplxFloatN a = Crank.VecCplxFloatN.uc(3, 3.0f, 4.0f, 5.0f, 12.0f, 2.0f, 3.0f);
	Crank.MatFloatN b = Crank.MatFloatN(3, 2,
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f);

	a = a.mulrm (b);

	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 28.0f));
	assert (float_eq (v.imag, 55.0f));
	
	v = a[1];
	assert (float_eq (v.real, 38.0f));
	assert (float_eq (v.imag, 74.0f));
}


private void test_n_mixs () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(2, 2.0f, 3.0f, 5.0f, 10.0f);
	
	a = a.mixs (b, 0.2f);
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 2.8f));
	assert (float_eq (v.imag, 3.8f));
	
	v = a[1];
	assert (float_eq (v.real, 5.0f));
	assert (float_eq (v.imag, 11.6f));
}


private void test_n_mix () {
	Crank.VecCplxFloatN	a = Crank.VecCplxFloatN.uc(2, 3.0f, 4.0f, 5.0f, 12.0f);
	Crank.VecCplxFloatN	b = Crank.VecCplxFloatN.uc(2, 2.0f, 3.0f, 5.0f, 10.0f);
	Crank.VecFloatN c = Crank.VecFloatN(2, 0.6f, 0.5f);
	
	a = a.mix (b, c);
	
	Crank.CplxFloat	v = a[0];
	assert (float_eq (v.real, 2.4f));
	assert (float_eq (v.imag, 3.4f));
	
	v = a[1];
	assert (float_eq (v.real, 5.0f));
	assert (float_eq (v.imag, 11.0f));
}


private void test_n_init_arruc () {
	Crank.VecCplxFloatN a = Crank.VecCplxFloatN.arruc (3,
			{2.0f, 4.0f,    1.0f, 3.0f,    6.0f, 4.0f});
	
	assert (a.size == 3);
	
	Crank.assert_eqcplxfloat (a[0], {2.0f, 4.0f});
	Crank.assert_eqcplxfloat (a[1], {1.0f, 3.0f});
	Crank.assert_eqcplxfloat (a[2], {6.0f, 4.0f});
}

private void test_n_init_ucarr () {
	Crank.VecCplxFloatN a = Crank.VecCplxFloatN.ucarr (
			{2.0f, 1.0f, 6.0f}, {4.0f, 3.0f, 4.0f} );
	
	assert (a.size == 3);
	
	Crank.assert_eqcplxfloat (a[0], {2.0f, 4.0f});
	Crank.assert_eqcplxfloat (a[1], {1.0f, 3.0f});
	Crank.assert_eqcplxfloat (a[2], {6.0f, 4.0f});
}

private void test_n_init_ucv () {
	Crank.VecCplxFloatN a = Crank.VecCplxFloatN.ucv (
			Crank.VecFloatN.arr({2.0f, 1.0f, 6.0f}),
			Crank.VecFloatN.arr({4.0f, 3.0f, 4.0f}) );
	
	assert (a.size == 3);

	Crank.assert_eqcplxfloat (a[0], {2.0f, 4.0f});
	Crank.assert_eqcplxfloat (a[1], {1.0f, 3.0f});
	Crank.assert_eqcplxfloat (a[2], {6.0f, 4.0f});
}

private void test_n_init_fill_uc () {
	Crank.VecCplxFloatN a = Crank.VecCplxFloatN.fill_uc (3, 1.0f, 2.0f);
	
	assert (a.size == 3);

	Crank.assert_eqcplxfloat (a[0], {1.0f, 2.0f});
	Crank.assert_eqcplxfloat (a[1], {1.0f, 2.0f});
	Crank.assert_eqcplxfloat (a[2], {1.0f, 2.0f});
}
