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

	GLib.Test.add_func ("/crank/base/quat/float/equal",		test_equal	);
	GLib.Test.add_func ("/crank/base/quat/float/equal/delta",test_equal_delta	);
	GLib.Test.add_func ("/crank/base/quat/float/get_norm",	test_get_norm	);
	GLib.Test.add_func ("/crank/base/quat/float/get_rangle",test_get_rangle	);
	GLib.Test.add_func ("/crank/base/quat/float/get_raxis",	test_get_raxis	);
	GLib.Test.add_func ("/crank/base/quat/float/neg",		test_neg	);
	GLib.Test.add_func ("/crank/base/quat/float/inverse",	test_inverse	);
	GLib.Test.add_func ("/crank/base/quat/float/conjgate",	test_conjugate	);
	GLib.Test.add_func ("/crank/base/quat/float/unit",		test_unit	);
	GLib.Test.add_func ("/crank/base/quat/float/addr",		test_addr	);
	GLib.Test.add_func ("/crank/base/quat/float/subr",		test_subr	);
	GLib.Test.add_func ("/crank/base/quat/float/mulr",		test_mulr	);
	GLib.Test.add_func ("/crank/base/quat/float/divr",		test_divr	);
	GLib.Test.add_func ("/crank/base/quat/float/rsubr",		test_rsubr	);
	GLib.Test.add_func ("/crank/base/quat/float/rdivr",		test_rdivr	);
	GLib.Test.add_func ("/crank/base/quat/float/addc",		test_addc	);
	GLib.Test.add_func ("/crank/base/quat/float/subc",		test_subc	);
	GLib.Test.add_func ("/crank/base/quat/float/mulc",		test_mulc	);
	GLib.Test.add_func ("/crank/base/quat/float/add",		test_add	);
	GLib.Test.add_func ("/crank/base/quat/float/sub",		test_sub	);
	GLib.Test.add_func ("/crank/base/quat/float/mul",		test_mul	);
	GLib.Test.add_func ("/crank/base/quat/float/mul_conj",	test_mul_conj	);
	GLib.Test.add_func ("/crank/base/quat/float/mix",		test_mix	);
	GLib.Test.add_func ("/crank/base/quat/float/ln",		test_ln	);
	GLib.Test.add_func ("/crank/base/quat/float/exp",		test_exp	);
	GLib.Test.add_func ("/crank/base/quat/float/powr",		test_powr	);
	GLib.Test.add_func ("/crank/base/quat/float/rotatev",	test_rotatev);
	

	GLib.Test.run ();

	return 0;
}


private bool float_eq (float a, float b, float delta = 0.0001f) {
	bool result = ((b-delta < a) && (a < b+delta));

	if (! result) message ("%g != %g (diff=%g)", a, b, b - a);

	return result;
}


private void test_equal () {
	Crank.QuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.QuatFloat b = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.QuatFloat c = {4.0f, 3.0f, 5.0f, 11.0f};
	
	assert (a.equal (b));
	assert (! a.equal (c));
}

private void test_equal_delta () {
	Crank.QuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.QuatFloat b = {3.2f, 4.1f, 5.0f, 11.9f};
	Crank.QuatFloat c = {4.0f, 3.0f, 5.0f, 12.0f};
	
	assert (a.equal_delta (b, 1.0f));
	assert (! a.equal_delta (c, 1.0f));
}

private void test_get_norm () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	assert (float_eq (a.norm, 13.9284f));
}


private void test_get_rangle () {
	Crank.QuatFloat a = {0.4794f, 0.5067f, 0.5067f, 0.5067f};
	
	Crank.assert_eqfloat (a.rangle, 2.1416f);
}


private void test_get_raxis () {
	Crank.QuatFloat a = {0.4794f, 0.5067f, 0.5067f, 0.5067f};
	
	Crank.assert_eq_vecfloat3_imm (a.raxis, 0.5774f, 0.5774f, 0.5774f);
}

private void test_neg () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.neg ();
	
	assert (float_eq (a.w, -3.0f));
	assert (float_eq (a.x, -4.0f));
	assert (float_eq (a.y, -5.0f));
	assert (float_eq (a.z, -12.0f));
}

private void test_inverse () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.inverse ();
	
	assert (float_eq (a.w,  0.0155f));
	assert (float_eq (a.x, -0.0206f));
	assert (float_eq (a.y, -0.0258f));
	assert (float_eq (a.z, -0.0619f));
}

private void test_conjugate () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.conjugate ();
	
	assert (float_eq (a.w, 3.0f));
	assert (float_eq (a.x, -4.0f));
	assert (float_eq (a.y, -5.0f));
	assert (float_eq (a.z, -12.0f));
}

private void test_unit () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.unit ();
	
	assert (float_eq (a.w, 0.2154f));
	assert (float_eq (a.x, 0.2872f));
	assert (float_eq (a.y, 0.3590f));
	assert (float_eq (a.z, 0.8615f));
}

private void test_addr () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.addr (2);
	
	assert (float_eq (a.w, 5.0f));
	assert (float_eq (a.x, 4.0f));
	assert (float_eq (a.y, 5.0f));
	assert (float_eq (a.z, 12.0f));
}

private void test_subr () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.subr (2);
	
	assert (float_eq (a.w, 1.0f));
	assert (float_eq (a.x, 4.0f));
	assert (float_eq (a.y, 5.0f));
	assert (float_eq (a.z, 12.0f));
}

private void test_mulr () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.mulr (2);
	
	assert (float_eq (a.w, 6.0f));
	assert (float_eq (a.x, 8.0f));
	assert (float_eq (a.y, 10.0f));
	assert (float_eq (a.z, 24.0f));
}

private void test_divr () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.divr (2);
	
	assert (float_eq (a.w, 1.5f));
	assert (float_eq (a.x, 2.0f));
	assert (float_eq (a.y, 2.5f));
	assert (float_eq (a.z, 6.0f));
}

private void test_rsubr () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.rsubr (2);
	
	assert (float_eq (a.w, -1.0f));
	assert (float_eq (a.x, -4.0f));
	assert (float_eq (a.y, -5.0f));
	assert (float_eq (a.z, -12.0f));
}

private void test_rdivr () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.rdivr (2);
	
	assert (float_eq (a.w, 0.0309f));
	assert (float_eq (a.x, -0.0412f));
	assert (float_eq (a.y, -0.0515f));
	assert (float_eq (a.z, -0.1237f));
}

private void test_addc () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.CplxFloat b = {2.0f, 3.0f};
	
	a = a.addc (b);
	
	assert (float_eq (a.w, 5.0f));
	assert (float_eq (a.x, 7.0f));
	assert (float_eq (a.y, 5.0f));
	assert (float_eq (a.z, 12.0f));
}

private void test_subc () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.CplxFloat b = {2.0f, 3.0f};
	
	a = a.subc (b);
	
	assert (float_eq (a.w, 1.0f));
	assert (float_eq (a.x, 1.0f));
	assert (float_eq (a.y, 5.0f));
	assert (float_eq (a.z, 12.0f));
}

private void test_mulc () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.CplxFloat b = {2.0f, 3.0f};
	
	a = a.mulc (b);
	
	assert (float_eq (a.w, -6.0f));
	assert (float_eq (a.x, 17.0f));
	assert (float_eq (a.y, 46.0f));
	assert (float_eq (a.z, 9.0f));
}

private void test_add () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.QuatFloat b = {2.0f, 3.0f, 5.0f, 8.0f};
	
	a = a.add (b);
	
	assert (float_eq (a.w, 5.0f));
	assert (float_eq (a.x, 7.0f));
	assert (float_eq (a.y, 10.0f));
	assert (float_eq (a.z, 20.0f));
}

private void test_sub () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.QuatFloat b = {2.0f, 3.0f, 5.0f, 8.0f};
	
	a = a.sub (b);
	
	assert (float_eq (a.w, 1.0f));
	assert (float_eq (a.x, 1.0f));
	assert (float_eq (a.y, 0.0f));
	assert (float_eq (a.z, 4.0f));
}

private void test_mul () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.QuatFloat b = {2.0f, 3.0f, 5.0f, 8.0f};
	
	a = a.mul (b);
	
	assert (float_eq (a.w, -127.0f));
	assert (float_eq (a.x, -3.0f));
	assert (float_eq (a.y, 29.0f));
	assert (float_eq (a.z, 53.0f));
}

private void test_mul_conj () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.QuatFloat b = {2.0f, 3.0f, 5.0f, 8.0f};
	
	a = a.mul_conj (b);
	
	assert (float_eq (a.w, 139.0f));
	assert (float_eq (a.x, 19.0f));
	assert (float_eq (a.y, -9.0f));
	assert (float_eq (a.z, -5.0f));
}

private void test_mix () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	Crank.QuatFloat b = {2.0f, 3.0f, 5.0f, 8.0f};
	
	a = a.mix (b, 0.25f);
	
	assert (float_eq (a.w, 2.75f));
	assert (float_eq (a.x, 3.75f));
	assert (float_eq (a.y, 5.0f));
	assert (float_eq (a.z, 11.0f));
}

private void test_ln () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.ln ();
	
	assert (float_eq (a.w, 2.6339f));
	assert (float_eq (a.x, 0.3981f));
	assert (float_eq (a.y, 0.4976f));
	assert (float_eq (a.z, 1.1943f));
}

private void test_exp () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.exp ();
	
	assert (float_eq (a.w, 10.2525f));
	assert (float_eq (a.x, 5.0794f));
	assert (float_eq (a.y, 6.3492f));
	assert (float_eq (a.z, 15.2382f));
}

private void test_powr () {
	Crank.QuatFloat a = {3.0f, 4.0f, 5.0f, 12.0f};
	
	a = a.powr (2.5f);
	
	assert (float_eq (a.w, -702.8075f));
	assert (float_eq (a.x, -51.1662f));
	assert (float_eq (a.y, -63.9578f));
	assert (float_eq (a.z, -153.4986f, 0.0005f));
}

private void test_rotatev () {
	Crank.QuatFloat a = {0.4794f, 0.5067f, 0.5067f, 0.5067f};
	Crank.VecFloat3	vec	= {1.0f, 2.0f, 3.0f};
	
	Crank.VecFloat3 rvec = a.rotatev (vec);
	
	Crank.assert_eq_vecfloat3_imm (rvec, 3.0264f, 1.0285f, 1.9455f);
}
