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

	GLib.Test.add_func ("/crank/base/vec/int/2/get", test_2_get);
	GLib.Test.add_func ("/carnk/base/vec/int/2/foreach", test_2_foreach);
	GLib.Test.add_func ("/crank/base/vec/int/2/hash", test_2_hash);
	GLib.Test.add_func ("/crank/base/vec/int/2/equal", test_2_equal);
	GLib.Test.add_func ("/crank/base/vec/int/2/to_string", test_2_to_string);
	GLib.Test.add_func ("/crank/base/vec/int/2/magn", test_2_magn);
	GLib.Test.add_func ("/crank/base/vec/int/2/muls", test_2_muls);
	GLib.Test.add_func ("/crank/base/vec/int/2/divs", test_2_divs);
	GLib.Test.add_func ("/crank/base/vec/int/2/mods", test_2_mods);
	GLib.Test.add_func ("/crank/base/vec/int/2/add", test_2_add);
	GLib.Test.add_func ("/crank/base/vec/int/2/sub", test_2_sub);
	GLib.Test.add_func ("/crank/base/vec/int/2/dot", test_2_dot);
	GLib.Test.add_func ("/crank/base/vec/int/2/cmpmul", test_2_cmpmul);
	GLib.Test.add_func ("/crank/base/vec/int/2/cmpdiv", test_2_cmpdiv);
	GLib.Test.add_func ("/crank/base/vec/int/2/cmpmod", test_2_cmpmod);
	GLib.Test.add_func ("/crank/base/vec/int/2/cmpless", test_2_cmpless);
	GLib.Test.add_func ("/crank/base/vec/int/2/cmpeq", test_2_cmpeq);
	GLib.Test.add_func ("/crank/base/vec/int/2/cmpgreater", test_2_cmpgreater);
	GLib.Test.add_func ("/crank/base/vec/int/2/cmpcmp", test_2_cmpcmp);
	GLib.Test.add_func ("/crank/base/vec/int/2/min", test_2_min);
	GLib.Test.add_func ("/crank/base/vec/int/2/max", test_2_max);
	
	GLib.Test.add_func ("/crank/base/vec/int/n/get", test_n_get);
	GLib.Test.add_func ("/crank/base/vec/int/n/insert", test_n_insert);
	GLib.Test.add_func ("/crank/base/vec/int/n/remove", test_n_remove);
	GLib.Test.add_func ("/carnk/base/vec/int/n/foreach", test_n_foreach);
	GLib.Test.add_func ("/crank/base/vec/int/n/hash", test_n_hash);
	GLib.Test.add_func ("/crank/base/vec/int/n/equal", test_n_equal);
	GLib.Test.add_func ("/crank/base/vec/int/n/to_string", test_n_to_string);
	GLib.Test.add_func ("/crank/base/vec/int/n/magn", test_n_magn);
	GLib.Test.add_func ("/crank/base/vec/int/n/muls", test_n_muls);
	GLib.Test.add_func ("/crank/base/vec/int/n/divs", test_n_divs);
	GLib.Test.add_func ("/crank/base/vec/int/n/mods", test_n_mods);
	GLib.Test.add_func ("/crank/base/vec/int/n/add", test_n_add);
	GLib.Test.add_func ("/crank/base/vec/int/n/sub", test_n_sub);
	GLib.Test.add_func ("/crank/base/vec/int/n/dot", test_n_dot);
	GLib.Test.add_func ("/crank/base/vec/int/n/cmpmul", test_n_cmpmul);
	GLib.Test.add_func ("/crank/base/vec/int/n/cmpdiv", test_n_cmpdiv);
	GLib.Test.add_func ("/crank/base/vec/int/n/cmpmod", test_n_cmpmod);
	GLib.Test.add_func ("/crank/base/vec/int/n/cmpless", test_n_cmpless);
	GLib.Test.add_func ("/crank/base/vec/int/n/cmpeq", test_n_cmpeq);
	GLib.Test.add_func ("/crank/base/vec/int/n/cmpgreater", test_n_cmpgreater);
	GLib.Test.add_func ("/crank/base/vec/int/n/cmpcmp", test_n_cmpcmp);
	GLib.Test.add_func ("/crank/base/vec/int/n/min", test_n_min);
	GLib.Test.add_func ("/crank/base/vec/int/n/max", test_n_max);
	
	GLib.Test.run ();
	
	return 0;
}


private void test_2_get () {
	Crank.VecInt2	a = {3, 4};
	
	assert (a[0] == 3);
	assert (a[1] == 4);
}


private void test_2_foreach () {
	Crank.VecInt2	a = {3, 4};
	int	sum = 0;

	assert (a.foreach ((v) => {
		sum += v;
		return true;
	}));
	assert (sum == 7);
}


private void test_2_hash () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {5, 12};
	Crank.VecInt2	c = {3, 4};
	
	assert (a.hash () != b.hash ());
	assert (a.hash () == c.hash ());
}


private void test_2_equal () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {5, 12};
	Crank.VecInt2	c = {3, 4};
	
	assert (! a.equal (b));
	assert (  a.equal (c));
}

private void test_2_to_string () {
	Crank.VecInt2	a = {3, 4};
	
	assert (a.to_string () == "(3, 4)");
}


private void test_2_magn () {
	Crank.VecInt2	a = {3, 4};
	
	assert (a.magn_sq == 25);
	Crank.assert_eqfloat (a.magn, 5.0f);
}

private void test_2_muls () {
	Crank.VecInt2	a = {3, 4};
	
	Crank.assert_eq_vecint2_imm (a.muls (4), 12, 16);
}


private void test_2_divs () {
	Crank.VecInt2	a = {15, 18};
	
	Crank.assert_eq_vecint2_imm (a.divs (3), 5, 6);
}


private void test_2_mods () {
	Crank.VecInt2	a = {32, 49};
	
	Crank.assert_eq_vecint2_imm (a.mods (7), 4, 0);
}


private void test_2_add () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	Crank.assert_eq_vecint2_imm (a.add (b), 12, 12);
}


private void test_2_sub () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	Crank.assert_eq_vecint2_imm (a.sub (b), -6, -4);
}


private void test_2_dot () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	assert (a.dot (b) == 59);
}


private void test_2_cmpmul () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	Crank.assert_eq_vecint2_imm (a.cmpmul (b), 27, 32);
}

private void test_2_cmpdiv () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	Crank.assert_eq_vecint2_imm (b.cmpdiv (a), 3, 2);
}

private void test_2_cmpmod () {
	Crank.VecInt2	a = {15, 18};
	Crank.VecInt2	b = {3, 7};
	
	Crank.assert_eq_vecint2_imm (a.cmpmod (b), 0, 4);
}


private void test_2_cmpless () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.assert_eq_vecbool2_imm (a.cmpless (b), true, false);
}


private void test_2_cmpeq () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 20};
	
	Crank.assert_eq_vecbool2_imm (a.cmpeq (b), false, true);
}


private void test_2_cmpgreater () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.assert_eq_vecbool2_imm (a.cmpgreater (b), false, true);
}


private void test_2_cmpcmp () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.VecInt2	c = a.cmpcmp (b);
	
	assert (c.x < 0);
	assert (c.y > 0);
}


private void test_2_min () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.assert_eq_vecint2_imm (a.min (b), 17, 19);
}


private void test_2_max () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.assert_eq_vecint2_imm (a.max (b), 53, 20);
}





private void test_n_get () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	
	assert (a.data[0] == 3);
	assert (a.data[1] == 4);
}


private void test_n_insert () {
	Crank.VecIntN	a = Crank.VecIntN(2, 3, 4);
	a.insert (1, 12);
	
	Crank.assert_eq_vecint_n_imm (a, 3 ,12, 4);
}


private void test_n_remove () {
	Crank.VecIntN	a = Crank.VecIntN(2, 3, 4);
	a.remove (1);

	Crank.assert_eq_vecint_n_imm (a, 3);
}


private void test_n_foreach () {
	Crank.VecIntN	a = Crank.VecIntN(2, 3, 4);
	int	sum = 0;

	assert (a.foreach ((v) => {
		sum += v;
		return true;
	}));
	assert (sum == 7);
}


private void test_n_hash () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 5, 12);
	Crank.VecIntN	c = Crank.VecIntN (2, 3, 4);
	
	assert (a.hash () != b.hash ());
	assert (a.hash () == c.hash ());
}


private void test_n_equal () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 5, 12);
	Crank.VecIntN	c = Crank.VecIntN (2, 3, 4);
	
	assert (! a.equal (b));
	assert (  a.equal (c));
}

private void test_n_to_string () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	
	assert (a.to_string () == "(3, 4)");
}


private void test_n_magn () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	
	assert (a.magn_sq == 25);
	Crank.assert_eqfloat (a.magn, 5.0f);
}

private void test_n_muls () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	
	Crank.assert_eq_vecint_n_imm (a.muls (4), 12, 16);
}


private void test_n_divs () {
	Crank.VecIntN	a = Crank.VecIntN (2, 15, 18);
	
	Crank.assert_eq_vecint_n_imm (a.divs (3), 5, 6);
}


private void test_n_mods () {
	Crank.VecIntN	a = Crank.VecIntN (2, 32, 49);
	
	Crank.assert_eq_vecint_n_imm (a.mods (7), 4, 0);
}


private void test_n_add () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	Crank.assert_eq_vecint_n_imm (a.add (b), 12, 12);
}


private void test_n_sub () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	Crank.assert_eq_vecint_n_imm (a.sub (b), -6, -4);
}


private void test_n_dot () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	assert (a.dot (b) == 59);
}


private void test_n_cmpmul () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	Crank.assert_eq_vecint_n_imm (a.cmpmul (b), 27, 32);
}

private void test_n_cmpdiv () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	Crank.assert_eq_vecint_n_imm (b.cmpdiv (a), 3, 2);
}

private void test_n_cmpmod () {
	Crank.VecIntN	a = Crank.VecIntN (2, 15, 18);
	Crank.VecIntN	b = Crank.VecIntN (2, 3, 7);
	
	Crank.assert_eq_vecint_n_imm (a.cmpmod (b), 0, 4);
}


private void test_n_cmpless () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.assert_eq_vecbool_n_imm (a.cmpless (b), true, false);
}


private void test_n_cmpeq () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 20);
	
	Crank.assert_eq_vecbool_n_imm (a.cmpeq (b), false, true);
}


private void test_n_cmpgreater () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.assert_eq_vecbool_n_imm (a.cmpgreater (b), false, true);
}


private void test_n_cmpcmp () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.VecIntN	c = a.cmpcmp (b);
	
	assert (c.data[0] < 0);
	assert (c.data[1] > 0);
}


private void test_n_min () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.assert_eq_vecint_n_imm (a.min (b), 17, 19);
}


private void test_n_max () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.assert_eq_vecint_n_imm (a.max (b), 53, 20);
}
