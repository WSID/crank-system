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
	

	GLib.Test.run ();

	return 0;
}


private bool float_eq (float a, float b, float delta = 0.0001f) {
	bool result = ((b-delta < a) && (a < b+delta));

	if (! result) printerr ("%g != %g (diff=%g)", a, b, b - a);

	return result;
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
	
	assert (float_eq (a.norm, 5.0f));
}

private void test_neg () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.neg ();
	
	assert (float_eq (a.real, -3.0f));
	assert (float_eq (a.imag, -4.0f));
}

private void test_inverse () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.inverse ();
	
	assert (float_eq (a.real, 0.12f));
	assert (float_eq (a.imag, -0.16f));
}

private void test_conjugate () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.conjugate ();
	
	assert (float_eq (a.real, 3.0f));
	assert (float_eq (a.imag, -4.0f));
}

private void test_unit () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.unit ();
	
	assert (float_eq (a.real, 0.6f));
	assert (float_eq (a.imag, 0.8f));
}

private void test_addr () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.addr (2);
	
	assert (float_eq (a.real, 5.0f));
	assert (float_eq (a.imag, 4.0f));
}

private void test_subr () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.subr (2);
	
	assert (float_eq (a.real, 1.0f));
	assert (float_eq (a.imag, 4.0f));
}

private void test_mulr () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.mulr (2);
	
	assert (float_eq (a.real, 6.0f));
	assert (float_eq (a.imag, 8.0f));
}

private void test_divr () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.divr (2);
	
	assert (float_eq (a.real, 1.5f));
	assert (float_eq (a.imag, 2.0f));
}

private void test_rsubr () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.rsubr (2);
	
	assert (float_eq (a.real, -1.0f));
	assert (float_eq (a.imag, -4.0f));
}

private void test_rdivr () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.rdivr (2);
	
	assert (float_eq (a.real, 0.24f));
	assert (float_eq (a.imag, -0.32f));
}

private void test_add () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};
	
	a = a.add (b);
	
	assert (float_eq (a.real, 8.0f));
	assert (float_eq (a.imag, 16.0f));
}

private void test_sub () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};
	
	a = a.sub (b);
	
	assert (float_eq (a.real, -2.0f));
	assert (float_eq (a.imag, -8.0f));
}

private void test_mul () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};
	
	a = a.mul (b);
	
	assert (float_eq (a.real, -33.0f));
	assert (float_eq (a.imag, 56.0f));
}

private void test_div () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};
	
	a = a.div (b);
	
	assert (float_eq (a.real, 63.0f / 169.0f));
	assert (float_eq (a.imag, -16.0f / 169.0f));
}

private void test_mul_conj () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};
	
	a = a.mul_conj (b);
	
	assert (float_eq (a.real, 63.0f));
	assert (float_eq (a.imag, -16.0f));
}

private void test_mix () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	Crank.CplxFloat b = {5.0f, 12.0f};
	
	a = a.mix (b, 0.25f);
	
	assert (float_eq (a.real, 3.5f));
	assert (float_eq (a.imag, 6.0f));
}

private void test_ln () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.ln ();
	
	assert (float_eq (a.real, 1.6094f));
	assert (float_eq (a.imag, 0.9273f));
}

private void test_exp () {
	Crank.CplxFloat a = {3.0f, 4.0f};
	
	a = a.exp ();
	
	assert (float_eq (a.real, -15.2008f));
	assert (float_eq (a.imag, -13.1287f));
}
