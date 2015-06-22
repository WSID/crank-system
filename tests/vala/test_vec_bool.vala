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

int main (string[] args) {
	GLib.Test.init (ref args);

	GLib.Test.add_func ("/crank/base/vec/bool/2/get", test_2_get);
	GLib.Test.add_func ("/crank/base/vec/bool/2/and", test_2_and);
	GLib.Test.add_func ("/crank/base/vec/bool/2/or", test_2_or);
	GLib.Test.add_func ("/crank/base/vec/bool/2/xor", test_2_xor);
	GLib.Test.add_func ("/crank/base/vec/bool/2/any", test_2_any);
	GLib.Test.add_func ("/crank/base/vec/bool/2/all", test_2_all);
	GLib.Test.add_func ("/crank/base/vec/bool/2/equal", test_2_equal);
	GLib.Test.add_func ("/crank/base/vec/bool/2/hash", test_2_hash);
	
	GLib.Test.add_func ("/crank/base/vec/bool/n/get", test_n_get);
	GLib.Test.add_func ("/crank/base/vec/bool/n/and", test_n_and);
	GLib.Test.add_func ("/crank/base/vec/bool/n/or", test_n_or);
	GLib.Test.add_func ("/crank/base/vec/bool/n/xor", test_n_xor);
	GLib.Test.add_func ("/crank/base/vec/bool/n/any", test_n_any);
	GLib.Test.add_func ("/crank/base/vec/bool/n/all", test_n_all);
	GLib.Test.add_func ("/crank/base/vec/bool/n/equal", test_n_equal);
	GLib.Test.add_func ("/crank/base/vec/bool/n/hash", test_n_hash);
	GLib.Test.run ();
	
	return 0;
}

void test_2_get () {
	Crank.VecBool2 a = {true, false};
	
	assert (a[0] == true);
	assert (a[1] == false);
}

void test_2_and () {
	Crank.VecBool2 a = {true, true};
	Crank.VecBool2 b = {false, true};
	
	Crank.VecBool2 c = a.and (b);
	
	assert (c.x == false);
	assert (c.y == true);
}

void test_2_or () {
	Crank.VecBool2 a = {false, false};
	Crank.VecBool2 b = {false, true};
	
	Crank.VecBool2 c = a.or (b);
	
	assert (c.x == false);
	assert (c.y == true);
}

void test_2_xor () {
	Crank.VecBool2 a = {true, false};
	Crank.VecBool2 b = {true, true};
	
	Crank.VecBool2 c = a.xor (b);
	
	assert (c.x == false);
	assert (c.y == true);
}

void test_2_not () {
	Crank.VecBool2 a = {true, false};
	
	Crank.VecBool2 c = a.not ();
	
	assert (c.x == false);
	assert (c.y == true);
}

void test_2_any () {
	Crank.VecBool2 a = {false, false};
	Crank.VecBool2 b = {false, true};
	
	assert (a.any == false);
	assert (b.any == true);
}

void test_2_all () {
	Crank.VecBool2 a = {true, false};
	Crank.VecBool2 b = {true, true};
	
	assert (a.all == false);
	assert (b.all == true);
}

void test_2_equal () {
	Crank.VecBool2 a = {true, true};
	Crank.VecBool2 b = {true, true};
	Crank.VecBool2 c = {true, false};
	
	assert (  Crank.VecBool2.equal (a, b));
	assert (! Crank.VecBool2.equal (a, c));
}

void test_2_hash () {
	Crank.VecBool2 a = {true, true};
	Crank.VecBool2 b = {true, true};
	Crank.VecBool2 c = {true, false};
	
	assert (Crank.VecBool2.hash (a) == Crank.VecBool2.hash (b));
	assert (Crank.VecBool2.hash (a) != Crank.VecBool2.hash (c));
}




void test_n_get () {
	Crank.VecBoolN a = Crank.VecBoolN(4, true, false, false, true);
	
	assert (a[0] == true);
	assert (a[1] == false);
	assert (a[2] == false);
	assert (a[3] == true);
}

void test_n_and () {
	Crank.VecBoolN a = Crank.VecBoolN (4, true, false, false, true);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	
	Crank.VecBoolN c = a.and (b);
	
	assert (c.size == 2);
	assert (c[0] == true);
	assert (c[1] == false);
}

void test_n_or () {
	Crank.VecBoolN a = Crank.VecBoolN (4, true, false, false, true);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	
	Crank.VecBoolN c = a.or (b);
	
	assert (c.size == 4);
	assert (c[0] == true);
	assert (c[1] == true);
	assert (c[2] == false);
	assert (c[3] == true);
}

void test_n_xor () {
	Crank.VecBoolN a = Crank.VecBoolN (4, true, false, false, true);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	
	Crank.VecBoolN c = a.xor (b);
	
	assert (c.size == 4);
	assert (c[0] == false);
	assert (c[1] == true);
	assert (c[2] == false);
	assert (c[3] == true);
}

void test_n_not () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, false);
	
	Crank.VecBoolN c = a.not ();
	
	assert (c.size == 2);
	assert (c[0] == false);
	assert (c[1] == true);
}

void test_n_any () {
	Crank.VecBoolN a = Crank.VecBoolN (2, false, false);
	Crank.VecBoolN b = Crank.VecBoolN (2, false, true);
	
	assert (a.any == false);
	assert (b.any == true);
}

void test_n_all () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, false);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	
	assert (a.all == false);
	assert (b.all == true);
}

void test_n_equal () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, true);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	Crank.VecBoolN c = Crank.VecBoolN (2, true, false);
	
	assert (  Crank.VecBoolN.equal (a, b));
	assert (! Crank.VecBoolN.equal (a, c));
}

void test_n_hash () {
	Crank.VecBoolN a = Crank.VecBoolN (2, true, true);
	Crank.VecBoolN b = Crank.VecBoolN (2, true, true);
	Crank.VecBoolN c = Crank.VecBoolN (2, true, false);
	
	assert (Crank.VecBoolN.hash (a) == Crank.VecBoolN.hash (b));
	assert (Crank.VecBoolN.hash (a) != Crank.VecBoolN.hash (c));
}        
