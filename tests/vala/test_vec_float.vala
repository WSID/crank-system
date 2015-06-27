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

	GLib.Test.add_func ("/crank/base/vec/float/2/get", test_2_get);
	GLib.Test.add_func ("/crank/base/vec/float/2/equal", test_2_equal);
	GLib.Test.add_func ("/crank/base/vec/float/2/to_string", test_2_to_string);
	GLib.Test.add_func ("/crank/base/vec/float/2/magn", test_2_magn);
	GLib.Test.add_func ("/crank/base/vec/float/2/unit", test_2_unit);
	GLib.Test.add_func ("/crank/base/vec/float/2/muls", test_2_muls);
	GLib.Test.add_func ("/crank/base/vec/float/2/divs", test_2_divs);
	GLib.Test.add_func ("/crank/base/vec/float/2/add", test_2_add);
	GLib.Test.add_func ("/crank/base/vec/float/2/sub", test_2_sub);
	GLib.Test.add_func ("/crank/base/vec/float/2/dot", test_2_dot);
	GLib.Test.add_func ("/crank/base/vec/float/2/cmpmul", test_2_cmpmul);
	GLib.Test.add_func ("/crank/base/vec/float/2/cmpdiv", test_2_cmpdiv);
	GLib.Test.add_func ("/crank/base/vec/float/2/cmpless", test_2_cmpless);
	GLib.Test.add_func ("/crank/base/vec/float/2/cmpeq", test_2_cmpeq);
	GLib.Test.add_func ("/crank/base/vec/float/2/cmpgreater", test_2_cmpgreater);
	GLib.Test.add_func ("/crank/base/vec/float/2/cmpcmp", test_2_cmpcmp);
	GLib.Test.add_func ("/crank/base/vec/float/2/min", test_2_min);
	GLib.Test.add_func ("/crank/base/vec/float/2/max", test_2_max);
	GLib.Test.add_func ("/crank/base/vec/float/2/mixs", test_2_mixs);
	GLib.Test.add_func ("/crank/base/vec/float/2/mix", test_2_mix);
	
	GLib.Test.add_func ("/crank/base/vec/float/n/get", test_n_get);
	GLib.Test.add_func ("/crank/base/vec/float/n/equal", test_n_equal);
	GLib.Test.add_func ("/crank/base/vec/float/n/to_string", test_n_to_string);
	GLib.Test.add_func ("/crank/base/vec/float/n/magn", test_n_magn);
	GLib.Test.add_func ("/crank/base/vec/float/n/unit", test_n_unit);
	GLib.Test.add_func ("/crank/base/vec/float/n/muls", test_n_muls);
	GLib.Test.add_func ("/crank/base/vec/float/n/divs", test_n_divs);
	GLib.Test.add_func ("/crank/base/vec/float/n/add", test_n_add);
	GLib.Test.add_func ("/crank/base/vec/float/n/sub", test_n_sub);
	GLib.Test.add_func ("/crank/base/vec/float/n/dot", test_n_dot);
	GLib.Test.add_func ("/crank/base/vec/float/n/cmpmul", test_n_cmpmul);
	GLib.Test.add_func ("/crank/base/vec/float/n/cmpdiv", test_n_cmpdiv);
	GLib.Test.add_func ("/crank/base/vec/float/n/cmpless", test_n_cmpless);
	GLib.Test.add_func ("/crank/base/vec/float/n/cmpeq", test_n_cmpeq);
	GLib.Test.add_func ("/crank/base/vec/float/n/cmpgreater", test_n_cmpgreater);
	GLib.Test.add_func ("/crank/base/vec/float/n/cmpcmp", test_n_cmpcmp);
	GLib.Test.add_func ("/crank/base/vec/float/n/min", test_n_min);
	GLib.Test.add_func ("/crank/base/vec/float/n/max", test_n_max);
	GLib.Test.add_func ("/crank/base/vec/float/n/mixs", test_n_mixs);
	GLib.Test.add_func ("/crank/base/vec/float/n/mix", test_n_mix);
	
	GLib.Test.run ();
	
	return 0;
}


private bool float_eq (float a, float b, float delta = 0.0001f) {
	bool result = ((b-delta < a) && (a < b+delta));
	
	if (! result) warning ("%g != %g (diff=%g)", a, b, delta);
	
	return result;
}


private void test_2_get () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	
	assert (float_eq (a.x, 3.0f));
	assert (float_eq (a.y, 4.0f));
}


private void test_2_equal () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {5.0f, 12.0f};
	Crank.VecFloat2	c = {3.0f, 4.0f};
	
	assert (! Crank.VecFloat2.equal (a, b));
	assert (  Crank.VecFloat2.equal (a, c));
}

private void test_2_to_string () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	
	assert (a.to_string () == "(3, 4)");
}


private void test_2_magn () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	
	assert (float_eq (a.magn_sq, 25.0f));
	assert (float_eq (a.magn, 5.0f));
}


private void test_2_unit () {
	Crank.VecFloat2 a = {3.0f, 4.0f};

	a = a.unit ();
	
	assert (float_eq (a.x, 0.6f));
	assert (float_eq (a.y, 0.8f));
}

private void test_2_muls () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	
	a = a.muls (4.0f);
	
	assert (float_eq (a.x, 12.0f));
	assert (float_eq (a.y, 16.0f));
}


private void test_2_divs () {
	Crank.VecFloat2	a = {15.0f, 18.0f};
	
	a = a.divs (3.0f);
	
	assert (float_eq (a.x, 5.0f));
	assert (float_eq (a.y, 6.0f));
}


private void test_2_add () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	a = a.add (b);
	
	assert (float_eq (a.x, 12.0f));
	assert (float_eq (a.y, 12.0f));
}


private void test_2_sub () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	a = a.sub (b);
	
	assert (float_eq (a.x, -6.0f));
	assert (float_eq (a.y, -4.0f));
}


private void test_2_dot () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	assert (float_eq (a.dot (b), 59.0f));
}


private void test_2_cmpmul () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	a = a.cmpmul (b);
	
	assert (float_eq (a.x, 27.0f));
	assert (float_eq (a.y, 32.0f));
}

private void test_2_cmpdiv () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	b = b.cmpdiv (a);

	assert (float_eq (b.x, 3.0f));
	assert (float_eq (b.y, 2.0f));
}


private void test_2_cmpless () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecBool2	r = a.cmpless (b);
	
	assert (  r.x);
	assert (! r.y);
}


private void test_2_cmpeq () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 20.0f};
	
	Crank.VecBool2	r = a.cmpeq (b);
	
	assert (! r.x);
	assert (  r.y);
}


private void test_2_cmpgreater () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecBool2	r = a.cmpgreater (b);
	
	assert (! r.x);
	assert (  r.y);
}


private void test_2_cmpcmp () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecInt2	c = a.cmpcmp (b);
	
	assert (c.x < 0);
	assert (c.y > 0);
}


private void test_2_min () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecFloat2	c = a.min (b);
	
	assert (float_eq (c.x, 17.0f));
	assert (float_eq (c.y, 19.0f));
}


private void test_2_max () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecFloat2	c = a.max (b);

	assert (float_eq (c.x, 53.0f));
	assert (float_eq (c.y, 20.0f));
}


private void test_2_mixs () {
	Crank.VecFloat2 a = {15.0f, 21.0f};
	Crank.VecFloat2 b = {30.0f, 11.0f};
	
	Crank.VecFloat2 d = a.mixs (b, 0.2f);
	
	assert (float_eq (d.x, 18.0f));
	assert (float_eq (d.y, 19.0f));
}


private void test_2_mix () {
	Crank.VecFloat2 a = {15.0f, 21.0f};
	Crank.VecFloat2 b = {30.0f, 11.0f};
	Crank.VecFloat2 c = {0.3f, 0.7f};
	
	Crank.VecFloat2 d = a.mix (b, c);
	
	assert (float_eq (d.x, 19.5f));
	assert (float_eq (d.y, 14.0f));
}







private void test_n_get () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	
	assert (float_eq (a[0], 3.0f));
	assert (float_eq (a[1], 4.0f));
}


private void test_n_equal () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 5.0f, 12.0f);
	Crank.VecFloatN	c = Crank.VecFloatN(2, 3.0f, 4.0f);
	
	assert (! Crank.VecFloatN.equal (a, b));
	assert (  Crank.VecFloatN.equal (a, c));
}

private void test_n_to_string () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	
	assert (a.to_string () == "(3, 4)");
}


private void test_n_magn () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	
	assert (float_eq (a.magn_sq, 25.0f));
	assert (float_eq (a.magn, 5.0f));
}


private void test_n_unit () {
	Crank.VecFloatN a = Crank.VecFloatN(2, 3.0f, 4.0f);

	a = a.unit ();
	
	assert (float_eq (a[0], 0.6f));
	assert (float_eq (a[1], 0.8f));
}

private void test_n_muls () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	
	a = a.muls (4.0f);
	
	assert (float_eq (a[0], 12.0f));
	assert (float_eq (a[1], 16.0f));
}


private void test_n_divs () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 15.0f, 18.0f);
	
	a = a.divs (3.0f);
	
	assert (float_eq (a[0], 5.0f));
	assert (float_eq (a[1], 6.0f));
}


private void test_n_add () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 9.0f, 8.0f);
	
	a = a.add (b);
	
	assert (float_eq (a[0], 12.0f));
	assert (float_eq (a[1], 12.0f));
}


private void test_n_sub () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 9.0f, 8.0f);
	
	a = a.sub (b);
	
	assert (float_eq (a[0], -6.0f));
	assert (float_eq (a[1], -4.0f));
}


private void test_n_dot () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 9.0f, 8.0f);
	
	assert (float_eq (a.dot (b), 59.0f));
}


private void test_n_cmpmul () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 9.0f, 8.0f);
	
	a = a.cmpmul (b);
	
	assert (float_eq (a[0], 27.0f));
	assert (float_eq (a[1], 32.0f));
}

private void test_n_cmpdiv () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 3.0f, 4.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 9.0f, 8.0f);
	
	b = b.cmpdiv (a);

	assert (float_eq (b[0], 3.0f));
	assert (float_eq (b[1], 2.0f));
}


private void test_n_cmpless () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 17.0f, 20.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 53.0f, 19.0f);
	
	Crank.VecBoolN	r = a.cmpless (b);
	
	assert (  r[0]);
	assert (! r[1]);
}


private void test_n_cmpeq () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 17.0f, 20.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 53.0f, 20.0f);
	
	Crank.VecBoolN	r = a.cmpeq (b);
	
	assert (! r[0]);
	assert (  r[1]);
}


private void test_n_cmpgreater () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 17.0f, 20.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 53.0f, 19.0f);
	
	Crank.VecBoolN	r = a.cmpgreater (b);
	
	assert (! r[0]);
	assert (  r[1]);
}


private void test_n_cmpcmp () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 17.0f, 20.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 53.0f, 19.0f);
	
	Crank.VecIntN	c = a.cmpcmp (b);
	
	assert (c[0] < 0);
	assert (c[1] > 0);
}


private void test_n_min () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 17.0f, 20.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 53.0f, 19.0f);
	
	Crank.VecFloatN	c = a.min (b);
	
	assert (float_eq (c[0], 17.0f));
	assert (float_eq (c[1], 19.0f));
}


private void test_n_max () {
	Crank.VecFloatN	a = Crank.VecFloatN(2, 17.0f, 20.0f);
	Crank.VecFloatN	b = Crank.VecFloatN(2, 53.0f, 19.0f);
	
	Crank.VecFloatN	c = a.max (b);

	assert (float_eq (c[0], 53.0f));
	assert (float_eq (c[1], 20.0f));
}


private void test_n_mixs () {
	Crank.VecFloatN a = Crank.VecFloatN(2, 15.0f, 21.0f);
	Crank.VecFloatN b = Crank.VecFloatN(2, 30.0f, 11.0f);
	
	Crank.VecFloatN d = a.mixs (b, 0.2f);
	
	assert (float_eq (d[0], 18.0f));
	assert (float_eq (d[1], 19.0f));
}


private void test_n_mix () {
	Crank.VecFloatN a = Crank.VecFloatN(2, 15.0f, 21.0f);
	Crank.VecFloatN b = Crank.VecFloatN(2, 30.0f, 11.0f);
	Crank.VecFloatN c = Crank.VecFloatN(2, 0.3f, 0.7f);
	
	Crank.VecFloatN d = a.mix (b, c);
	
	assert (float_eq (d[0], 19.5f));
	assert (float_eq (d[1], 14.0f));
}
