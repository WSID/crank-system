/* Copyright (C) 2015, WSID   */

/* This file is part of Crank System.
 *
 *  Crank System is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  Crank System is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with Crank System.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

private void test_add () {
	GLib.Value value;
	
	assert (Crank.base_add (out value, 73, 5));
	assert (value.get_int () == 73 + 5);
}

private void test_sub () {
	GLib.Value value;
	
	assert (Crank.base_sub (out value, 73, 5));
	assert (value.get_int () == 73 - 5);
}

private void test_mul () {
	GLib.Value value;
	
	assert (Crank.base_mul (out value, 73, 5));
	assert (value.get_int () == 73 * 5);
}

private void test_div () {
	GLib.Value value;
	
	assert (Crank.base_div (out value, 73, 5));
	assert (value.get_int () == 73 / 5);
}

private void test_neg () {
	GLib.Value value;
	
	assert (Crank.base_neg (out value, 73));
	assert (value.get_int () == -73);
}

private void test_inc () {
	GLib.Value value;
	
	assert (Crank.base_inc (out value, 73));
	assert (value.get_int () == 74);
}

private void test_dec () {
	GLib.Value value;
	
	assert (Crank.base_dec (out value, 73));
	assert (value.get_int () == 72);
}

private void test_lshift () {
	GLib.Value value;
	
	assert (Crank.base_lshift (out value, 73, (uint)5));
	assert (value.get_int () == 73 << 5);
}

private void test_rshift () {
	GLib.Value value;
	
	assert (Crank.base_rshift (out value, 73, (uint)5));
	assert (value.get_int () == 73 >> 5);
}

private void test_leq () {
	GLib.Value value;
	
	assert (Crank.base_leq (out value, 73, 5));
	assert (value.get_boolean () == false);
}

private void test_eq () {
	GLib.Value value;
	
	assert (Crank.base_eq (out value, 73, 5));
	assert (value.get_boolean () == false);
}

private void test_geq () {
	GLib.Value value;
	
	assert (Crank.base_geq (out value, 73, 5));
	assert (value.get_boolean () == true);
}

private void test_std_lshift () {
	GLib.Value value;
	
	Crank.base_std_lshift (out value, 157, 3);
	
	assert (value.get_int () == 157 << 3);
}

private void test_std_rshift () {
	GLib.Value value;
	
	Crank.base_std_rshift (out value, 157, 3);
	
	assert (value.get_int () == 157 >> 3);
}

private void test_std_leq () {
	assert (! Crank.base_std_leq (153, 7));
}

private void test_std_eq () {
	assert (! Crank.base_std_eq (153, 7));
}

private void test_std_geq () {
	assert (  Crank.base_std_geq (153, 7));
}

int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func ("/crank/base/book/add", test_add);
	GLib.Test.add_func ("/crank/base/book/sub", test_sub);
	GLib.Test.add_func ("/crank/base/book/mul", test_mul);
	GLib.Test.add_func ("/crank/base/book/div", test_div);
	GLib.Test.add_func ("/crank/base/book/neg", test_neg);
	GLib.Test.add_func ("/crank/base/book/inc", test_inc);
	GLib.Test.add_func ("/crank/base/book/dec", test_dec);
	GLib.Test.add_func ("/crank/base/book/lshift", test_lshift);
	GLib.Test.add_func ("/crank/base/book/rshift", test_rshift);
	GLib.Test.add_func ("/crank/base/book/leq", test_leq);
	GLib.Test.add_func ("/crank/base/book/eq", test_eq);
	GLib.Test.add_func ("/crank/base/book/geq", test_geq);
	
	GLib.Test.add_func ("/crank/base/book/std_lshift", test_std_lshift);
	GLib.Test.add_func ("/crank/base/book/std_rshift", test_std_rshift);
	GLib.Test.add_func ("/crank/base/book/std_leq", test_std_leq);
	GLib.Test.add_func ("/crank/base/book/std_eq", test_std_eq);
	GLib.Test.add_func ("/crank/base/book/std_geq", test_std_geq);
			
	GLib.Test.run ();
	
	return 0;
}
