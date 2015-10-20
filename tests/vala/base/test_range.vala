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

	GLib.Test.add_func ("/crank/base/range/uint/equal",		test_uint_equal	);
	GLib.Test.add_func ("/crank/base/range/uint/hash",		test_uint_hash	);
	GLib.Test.add_func ("/crank/base/range/uint/to_string",	test_uint_to_string	);
	GLib.Test.add_func ("/crank/base/range/uint/is_empty",	test_uint_is_empty	);
	GLib.Test.add_func ("/crank/base/range/uint/is_unit",	test_uint_is_unit	);
	GLib.Test.add_func ("/crank/base/range/uint/get_length",test_uint_get_length	);
	GLib.Test.add_func ("/crank/base/range/uint/contains",	test_uint_contains	);
	GLib.Test.add_func ("/crank/base/range/uint/get",		test_uint_get	);
	GLib.Test.add_func ("/crank/base/range/uint/index_of",	test_uint_index_of	);
	GLib.Test.add_func ("/crank/base/range/uint/clamp",		test_uint_clamp	);
	GLib.Test.add_func ("/crank/base/range/uint/intersection",test_uint_intersection	);
	
	GLib.Test.run ();

	return 0;
}


private void	test_uint_equal () {
	Crank.RanUint	a = {3, 5};
	Crank.RanUint	b = {0, 4};
	Crank.RanUint	c = {3, 5};
	
	assert (! a.equal (b));
	assert (a.equal (c));
}

private void	test_uint_hash () {
	Crank.RanUint	a = {3, 5};
	Crank.RanUint	b = {0, 4};
	Crank.RanUint	c = {3, 5};
	
	assert (a.hash () != b.hash ());
	assert (a.hash () == c.hash ());
}

private void 	test_uint_to_string () {
	Crank.RanUint	a = {3, 5};
	
	assert (a.to_string () == "[3, 5)");
}

private void	test_uint_is_empty () {
	Crank.RanUint	a;
	
	a = {3, 5};
	assert (! a.is_empty ());
	
	a = {6, 6};
	assert (a.is_empty ());
}

private void	test_uint_is_unit () {
	Crank.RanUint	a;
	
	a = {3, 4};
	assert (a.is_unit ());
	
	a = {6, 6};
	assert (! a.is_unit ());
}

private void	test_uint_get_length () {
	Crank.RanUint	a = {3, 5};
	
	assert (a.length == 2);
}

private void 	test_uint_contains () {
	Crank.RanUint	a = {4, 8};
	
	assert (! (3 in a));
	assert (! (8 in a));
	assert (6 in a);
}

private void	test_uint_get () {
	Crank.RanUint	a = {10, 110};
	
	assert (a[0.25f] == 35);
}

private void	test_uint_index_of () {
	Crank.RanUint	a = {10, 110};
	
	assert (a.index_of (60) == 0.5f);
}

private void	test_uint_clamp () {
	Crank.RanUint	a = {10, 100};
	
	assert (a.clamp (4) == 10);
	assert (a.clamp (200) == 100);
	assert (a.clamp (59) == 59);
}

private void	test_uint_intersection () {
	Crank.RanUint	a = {14, 45};
	Crank.RanUint	b = {55, 74};
	Crank.RanUint	c = {30, 60};
	
	Crank.RanUint	d;
	Crank.RanUint	e;
	
	assert (! a.intersection (b, out d));
	assert (a.intersection (c, out e));
	
	assert (e.start == 30);
	assert (e.end == 45);
}
