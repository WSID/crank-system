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

	GLib.Test.add_func ("/crank/base/vec/bool/2/get", test_2_get);
	GLib.Test.add_func ("/crank/base/vec/bool/2/foreach", test_2_foreach);
	GLib.Test.add_func ("/crank/base/vec/bool/2/and", test_2_and);
	GLib.Test.add_func ("/crank/base/vec/bool/2/or", test_2_or);
	GLib.Test.add_func ("/crank/base/vec/bool/2/xor", test_2_xor);
	GLib.Test.add_func ("/crank/base/vec/bool/2/not", test_2_not);
	GLib.Test.add_func ("/crank/base/vec/bool/2/any", test_2_any);
	GLib.Test.add_func ("/crank/base/vec/bool/2/all", test_2_all);
	GLib.Test.add_func ("/crank/base/vec/bool/2/equal", test_2_equal);
	GLib.Test.add_func ("/crank/base/vec/bool/2/hash", test_2_hash);
	GLib.Test.add_func ("/crank/base/vec/bool/2/to_string", test_2_to_string);
	
	GLib.Test.add_func ("/crank/base/vec/bool/n/get", test_n_get);
	GLib.Test.add_func ("/crank/base/vec/bool/n/insert", test_n_insert);
	GLib.Test.add_func ("/crank/base/vec/bool/n/remove", test_n_remove);
	GLib.Test.add_func ("/crank/base/vec/bool/n/foreach", test_n_foreach);
	GLib.Test.add_func ("/crank/base/vec/bool/n/and", test_n_and);
	GLib.Test.add_func ("/crank/base/vec/bool/n/or", test_n_or);
	GLib.Test.add_func ("/crank/base/vec/bool/n/xor", test_n_xor);
	GLib.Test.add_func ("/crank/base/vec/bool/n/not", test_n_not);
	GLib.Test.add_func ("/crank/base/vec/bool/n/any", test_n_any);
	GLib.Test.add_func ("/crank/base/vec/bool/n/all", test_n_all);
	GLib.Test.add_func ("/crank/base/vec/bool/n/equal", test_n_equal);
	GLib.Test.add_func ("/crank/base/vec/bool/n/hash", test_n_hash);
	GLib.Test.add_func ("/crank/base/vec/bool/n/to_string", test_n_to_string);
	GLib.Test.run ();
	
	return 0;
}

private void test_2_get () {
	Crank.VecBool2 a = {true, false};
	
	assert (a[0] == true);
	assert (a[1] == false);
}

private void test_2_foreach () {
	Crank.VecBool2	a = {true, false};
	uint			count = 0;

	assert (	a.foreach ((v) => {
		if (v) count++;
		return true;
	}) );

	assert (count == 1);
}

private void test_2_and () {
	Crank.VecBool2 a = {true, true};
	Crank.VecBool2 b = {false, true};
	
	Crank.VecBool2 c = a.and (b);
	
	assert (c.x == false);
	assert (c.y == true);
}

private void test_2_or () {
	Crank.VecBool2 a = {false, false};
	Crank.VecBool2 b = {false, true};
	
	Crank.VecBool2 c = a.or (b);
	
	assert (c.x == false);
	assert (c.y == true);
}

private void test_2_xor () {
	Crank.VecBool2 a = {true, false};
	Crank.VecBool2 b = {true, true};
	
	Crank.VecBool2 c = a.xor (b);
	
	assert (c.x == false);
	assert (c.y == true);
}

private void test_2_not () {
	Crank.VecBool2 a = {true, false};
	
	Crank.VecBool2 c = a.not ();
	
	assert (c.x == false);
	assert (c.y == true);
}

private void test_2_any () {
	Crank.VecBool2 a = {false, false};
	Crank.VecBool2 b = {false, true};
	
	assert (a.any == false);
	assert (b.any == true);
}

private void test_2_all () {
	Crank.VecBool2 a = {true, false};
	Crank.VecBool2 b = {true, true};
	
	assert (a.all == false);
	assert (b.all == true);
}

private void test_2_equal () {
	Crank.VecBool2 a = {true, true};
	Crank.VecBool2 b = {true, true};
	Crank.VecBool2 c = {true, false};
	
	assert (  Crank.VecBool2.equal (a, b));
	assert (! Crank.VecBool2.equal (a, c));
}

private void test_2_hash () {
	Crank.VecBool2 a = {true, true};
	Crank.VecBool2 b = {true, true};
	Crank.VecBool2 c = {true, false};
	
	assert (Crank.VecBool2.hash (a) == Crank.VecBool2.hash (b));
	assert (Crank.VecBool2.hash (a) != Crank.VecBool2.hash (c));
}

private void test_2_to_string () {
	Crank.VecBool2 a = {true, true};
	
	assert (a.to_string () == "(true, true)");
}




private void test_n_get () {
	Crank.VecBoolN a = Crank.VecBoolN(4, true, false, false, true);
	
	assert (a[0] == true);
	assert (a[1] == false);
	assert (a[2] == false);
	assert (a[3] == true);
}

private void test_n_insert () {
	Crank.VecBoolN a = Crank.VecBoolN(4, true, false, false, true);

	a.insert (2, true);

	assert (a[0] == true);
	assert (a[1] == false);
	assert (a[2] == true);
	assert (a[3] == false);
	assert (a[4] == true);
}

private void test_n_remove () {
	Crank.VecBoolN a = Crank.VecBoolN(4, true, false, false, true);

	a.remove (2);

	assert (a[0] == true);
	assert (a[1] == false);
	assert (a[2] == true);
}

private void test_n_foreach () {
	Crank.VecBoolN	a = Crank.VecBoolN (4, true, false, false, true);
	uint			count = 0;

	assert (	a.foreach ((v) => {
		if (v) count++;
		return true;
	}) );

	assert (count == 2);
}

private void test_n_and () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, false);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	
	Crank.VecBoolN c = a.and (b);
	
	assert (c.size == 2);
	assert (c[0] == true);
	assert (c[1] == false);
}

private void test_n_or () {
	Crank.VecBoolN a = Crank.VecBoolN (4, true, false, false, true);
	Crank.VecBoolN b = Crank.VecBoolN (4, true, true, false, true);
	
	Crank.VecBoolN c = a.or (b);
	
	assert (c.size == 4);
	assert (c[0] == true);
	assert (c[1] == true);
	assert (c[2] == false);
	assert (c[3] == true);
}

private void test_n_xor () {
	Crank.VecBoolN a = Crank.VecBoolN (4, true, false, false, true);
	Crank.VecBoolN b = Crank.VecBoolN (4, true, true, false, false);
	
	Crank.VecBoolN c = a.xor (b);
	
	assert (c.size == 4);
	assert (c[0] == false);
	assert (c[1] == true);
	assert (c[2] == false);
	assert (c[3] == true);
}

private void test_n_not () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, false);
	
	Crank.VecBoolN c = a.not ();
	
	assert (c.size == 2);
	assert (c[0] == false);
	assert (c[1] == true);
}

private void test_n_any () {
	Crank.VecBoolN a = Crank.VecBoolN (2, false, false);
	Crank.VecBoolN b = Crank.VecBoolN (2, false, true);
	
	assert (a.any == false);
	assert (b.any == true);
}

private void test_n_all () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, false);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	
	assert (a.all == false);
	assert (b.all == true);
}

private void test_n_equal () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, true);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	Crank.VecBoolN c = Crank.VecBoolN (2, true, false);
	
	assert (  Crank.VecBoolN.equal (a, b));
	assert (! Crank.VecBoolN.equal (a, c));
}

private void test_n_hash () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, true);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	Crank.VecBoolN c = Crank.VecBoolN (2, true, false);
	
	assert (Crank.VecBoolN.hash (a) == Crank.VecBoolN.hash (b));
	assert (Crank.VecBoolN.hash (a) != Crank.VecBoolN.hash (c));
}

private void test_n_to_string () {
	Crank.VecBoolN a = Crank.VecBoolN (4, true, true, false, false);
	
	assert (a.to_string () == "(true, true, false, false)");
}
