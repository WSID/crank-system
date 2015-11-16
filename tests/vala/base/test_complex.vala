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

	GLib.Test.add_func ("/crank/base/cplx/float/equal",		test_equal	);
	GLib.Test.add_func ("/crank/base/cplx/float/equal/delta",test_equal_delta	);
	GLib.Test.add_func ("/crank/base/cplx/float/get_norm",	test_get_norm	);
	GLib.Test.add_func ("/crank/base/cplx/float/neg",		test_neg	);
	GLib.Test.add_func ("/crank/base/cplx/float/inverse",	test_inverse	);
	GLib.Test.add_func ("/crank/base/cplx/float/conjgate",	test_conjugate	);
	GLib.Test.add_func ("/crank/base/cplx/float/unit",		test_unit	);
	GLib.Test.add_func ("/crank/base/cplx/float/sqrt",		test_sqrt	);
	GLib.Test.add_func ("/crank/base/cplx/float/addr",		test_addr	);
	GLib.Test.add_func ("/crank/base/cplx/float/subr",		test_subr	);
	GLib.Test.add_func ("/crank/base/cplx/float/mulr",		test_mulr	);
	GLib.Test.add_func ("/crank/base/cplx/float/divr",		test_divr	);
	GLib.Test.add_func ("/crank/base/cplx/float/rsubr",		test_rsubr	);
	GLib.Test.add_func ("/crank/base/cplx/float/rdivr",		test_rdivr	);
	GLib.Test.add_func ("/crank/base/cplx/float/add",		test_add	);
	GLib.Test.add_func ("/crank/base/cplx/float/sub",		test_sub	);
	GLib.Test.add_func ("/crank/base/cplx/float/mul",		test_mul	);
	GLib.Test.add_func ("/crank/base/cplx/float/div",		test_div	);
	GLib.Test.add_func ("/crank/base/cplx/float/mul_conj",	test_mul_conj	);
	GLib.Test.add_func ("/crank/base/cplx/float/mix",		test_mix	);
	GLib.Test.add_func ("/crank/base/cplx/float/ln",		test_ln	);
	GLib.Test.add_func ("/crank/base/cplx/float/exp",		test_exp	);
	GLib.Test.add_func ("/crank/base/cplx/float/pow",		test_pow	);
	GLib.Test.add_func ("/crank/base/cplx/float/sinh",		test_sinh	);
	GLib.Test.add_func ("/crank/base/cplx/float/cosh",		test_cosh	);
	GLib.Test.add_func ("/crank/base/cplx/float/tanh",		test_tanh	);
	GLib.Test.add_func ("/crank/base/cplx/float/sin",		test_sin	);
	GLib.Test.add_func ("/crank/base/cplx/float/cos",		test_cos	);
	GLib.Test.add_func ("/crank/base/cplx/float/tan",		test_tan	);
	

	GLib.Test.run ();

	return 0;
}


private void test_equal () {
	Crank.CplxFloat	a = {3.0f, 4.0f};
	Crank.CplxFloat b = {3.0f, 4.0f};
	Crank.CplxFloat c = {4.0f, 3.0f};

	assert (a.equal (b));
	assert (! a.equal (c));
}

private void test_equal_delta () {
	Crank.CplxFloat	a = {3.0f, 4.0f};
	Crank.CplxFloat b = {3.2f, 4.1f};
	Crank.CplxFloat c = {4.0f, 3.0f};

	assert (a.equal_delta (b, 1.0f));
	assert (! a.equal_delta (c, 1.0f));
}

private void test_get_norm () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	Crank.assert_eqfloat (a.norm, 5.0f);
}

private void test_neg () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	Crank.assert_eqcplxfloat_uc (a.neg (), -3.0f, -4.0f);
}

private void test_inverse () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	Crank.assert_eqcplxfloat_uc (a.inverse (), 0.12f, -0.16f);
}

private void test_conjugate () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.conjugate (), 3.0f, -4.0f);
}

private void test_unit () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.unit (), 0.6f, 0.8f);
}

private void test_sqrt () {
	Crank.CplxFloat a = {7.0f, 8.0f};
	
	Crank.assert_eqcplxfloat_uc (a.sqrt (), 2.9690f, 1.3472f);
}


private void test_addr () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.addr (2), 5.0f, 4.0f);
}

private void test_subr () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.subr (2), 1.0f, 4.0f);
}

private void test_mulr () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	Crank.assert_eqcplxfloat_uc (a.mulr (2), 6.0f, 8.0f);
}

private void test_divr () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.divr (2), 1.5f, 2.0f);
}

private void test_rsubr () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.rsubr (2), -1.0f, -4.0f);
}

private void test_rdivr () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.rdivr (2), 0.24f, -0.32f);
}

private void test_add () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};

	Crank.assert_eqcplxfloat_uc (a.add (b), 8.0f, 16.0f);
}

private void test_sub () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};

	Crank.assert_eqcplxfloat_uc (a.sub (b), -2.0f, -8.0f);
}

private void test_mul () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};

	Crank.assert_eqcplxfloat_uc (a.mul (b), -33.0f, 56.0f);
}

private void test_div () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};

	Crank.assert_eqcplxfloat_uc (a.div (b), 63.0f/169.0f, -16.0f/169.0f);
}

private void test_mul_conj () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};

	Crank.assert_eqcplxfloat_uc (a.mul_conj (b), 63.0f, -16.0f);
}

private void test_mix () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};

	Crank.assert_eqcplxfloat_uc (a.mix (b, 0.25f), 3.5f, 6.0f);
}

private void test_ln () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	a = a.ln ();

	Crank.assert_eqcplxfloat_uc (a, 1.6094f, 0.9273f);
}

private void test_exp () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	a = a.exp ();

	Crank.assert_eqcplxfloat_uc (a, -13.1287f, -15.2008f);
}

private void test_pow () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {1.0f, 2.0f};

	Crank.assert_eqcplxfloat_uc (a.pow (b), -0.4198f, -0.6605f);
}

private void test_sinh () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.sinh (), -6.5481f, -7.6192f);
}

private void test_cosh () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.cosh (), -6.5807f, -7.5816f);
}

private void test_tanh () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.tanh (), 1.0007f, 0.0049f);
}

private void test_sin () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	Crank.assert_eqcplxfloat_uc (a.sin (), 3.8537f, -27.0168f);
}

private void test_cos () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.cos (), -27.0349f, -3.8512f);
}

private void test_tan () {
	Crank.CplxFloat a = {3.0f, 4.0f};

	Crank.assert_eqcplxfloat_uc (a.tan (), -0.0001f, 0.9994f);
}
