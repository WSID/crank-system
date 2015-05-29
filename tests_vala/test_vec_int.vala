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

void test_2_get () {
	Crank.VecInt2	a = {3, 4};
	
	assert (a.x == 3);
	assert (a.y == 4);
}


void test_2_hash () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {5, 12};
	Crank.VecInt2	c = {3, 4};
	
	assert (Crank.VecInt2.hash (a) != Crank.VecInt2.hash (b));
	assert (Crank.VecInt2.hash (a) == Crank.VecInt2.hash (c));
}


void test_2_equal () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {5, 12};
	Crank.VecInt2	c = {3, 4};
	
	assert (! Crank.VecInt2.equal (a, b));
	assert (  Crank.VecInt2.equal (a, c));
}

void test_2_to_string () {
	Crank.VecInt2	a = {3, 4};
	
	assert (a.to_string () == "(3, 4)");
}


void test_2_magn () {
	Crank.VecInt2	a = {3, 4};
	
	assert (a.magn_sq == 25);
	assert (a.magn == 5.0f);
}

void test_2_muls () {
	Crank.VecInt2	a = {3, 4};
	
	a = a.muls (4);
	
	assert (a.x == 12);
	assert (a.y == 16);
}


void test_2_divs () {
	Crank.VecInt2	a = {15, 18};
	
	a = a.divs (3);
	
	assert (a.x == 5);
	assert (a.y == 6);
}


void test_2_mods () {
	Crank.VecInt2	a = {32, 49};
	
	a = a.mods (7);
	
	assert (a.x == 4);
	assert (a.y == 0);
}


void test_2_add () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	a = a.add (b);
	
	assert (a.x == 12);
	assert (a.y == 12);
}


void test_2_sub () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	a = a.sub (b);
	
	assert (a.x == -6);
	assert (a.y == -4);
}


void test_2_dot () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	assert (a.dot (b) == 59);
}


void test_2_cmpmul () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	a = a.cmpmul (b);
	
	assert (a.x == 27);
	assert (a.y == 32);
}

void test_2_cmpdiv () {
	Crank.VecInt2	a = {3, 4};
	Crank.VecInt2	b = {9, 8};
	
	b = b.cmpdiv (a);

	assert (b.x == 3);
	assert (b.y == 2);
}

void test_2_cmpmod () {
	Crank.VecInt2	a = {15, 18};
	Crank.VecInt2	b = {3, 7};
	
	a = a.cmpmod (b);

	assert (a.x == 0);
	assert (a.y == 4);
}


void test_2_cmpless () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.VecBool2	r = a.cmpless (b);
	
	assert (  r.x);
	assert (! r.y);
}


void test_2_cmpeq () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 20};
	
	Crank.VecBool2	r = a.cmpeq (b);
	
	assert (! r.x);
	assert (  r.y);
}


void test_2_cmpgreater () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.VecBool2	r = a.cmpgreater (b);
	
	assert (! r.x);
	assert (  r.y);
}


void test_2_cmpcmp () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.VecInt2	c = a.cmpcmp (b);
	
	assert (c.x < 0);
	assert (c.y > 0);
}


void test_2_min () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.VecInt2	c = a.min (b);
	
	assert (c.x == 17);
	assert (c.y == 19);
}


void test_2_max () {
	Crank.VecInt2	a = {17, 20};
	Crank.VecInt2	b = {53, 19};
	
	Crank.VecInt2	c = a.max (b);
	
	assert (c.x == 53);
	assert (c.y == 20);
}





void test_n_get () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	
	assert (a.data[0] == 3);
	assert (a.data[1] == 4);
}


void test_n_hash () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 5, 12);
	Crank.VecIntN	c = Crank.VecIntN (2, 3, 4);
	
	assert (Crank.VecIntN.hash (a) != Crank.VecIntN.hash (b));
	assert (Crank.VecIntN.hash (a) == Crank.VecIntN.hash (c));
}


void test_n_equal () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 5, 12);
	Crank.VecIntN	c = Crank.VecIntN (2, 3, 4);
	
	assert (! Crank.VecIntN.equal (a, b));
	assert (  Crank.VecIntN.equal (a, c));
}

void test_n_to_string () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	
	assert (a.to_string () == "(3, 4)");
}


void test_n_magn () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	
	assert (a.magn_sq == 25);
	assert (a.magn == 5.0f);
}

void test_n_muls () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	
	a = a.muls (4);
	
	assert (a.data[0] == 12);
	assert (a.data[1] == 16);
}


void test_n_divs () {
	Crank.VecIntN	a = Crank.VecIntN (2, 15, 18);
	
	a = a.divs (3);
	
	assert (a.data[0] == 5);
	assert (a.data[1] == 6);
}


void test_n_mods () {
	Crank.VecIntN	a = Crank.VecIntN (2, 32, 49);
	
	a = a.mods (7);
	
	assert (a.data[0] == 4);
	assert (a.data[1] == 0);
}


void test_n_add () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	a = a.add (b);
	
	assert (a.data[0] == 12);
	assert (a.data[1] == 12);
}


void test_n_sub () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	a = a.sub (b);
	
	assert (a.data[0] == -6);
	assert (a.data[1] == -4);
}


void test_n_dot () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	assert (a.dot (b) == 59);
}


void test_n_cmpmul () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	a = a.cmpmul (b);
	
	assert (a.data[0] == 27);
	assert (a.data[1] == 32);
}

void test_n_cmpdiv () {
	Crank.VecIntN	a = Crank.VecIntN (2, 3, 4);
	Crank.VecIntN	b = Crank.VecIntN (2, 9, 8);
	
	b = b.cmpdiv (a);

	assert (b.data[0] == 3);
	assert (b.data[1] == 2);
}

void test_n_cmpmod () {
	Crank.VecIntN	a = Crank.VecIntN (2, 15, 18);
	Crank.VecIntN	b = Crank.VecIntN (2, 3, 7);
	
	a = a.cmpmod (b);

	assert (a.data[0] == 0);
	assert (a.data[1] == 4);
}


void test_n_cmpless () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.VecBoolN	r = a.cmpless (b);
	
	assert (  r.data[0] );
	assert (! r.data[1] );
}


void test_n_cmpeq () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 20);
	
	Crank.VecBoolN	r = a.cmpeq (b);
	
	assert (! r.data[0] );
	assert (  r.data[1] );
}


void test_n_cmpgreater () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.VecBoolN	r = a.cmpgreater (b);
	
	assert (! r.data[0] );
	assert (  r.data[1] );
}


void test_n_cmpcmp () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.VecIntN	c = a.cmpcmp (b);
	
	assert (c.data[0] < 0);
	assert (c.data[1] > 0);
}


void test_n_min () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.VecIntN	c = a.min (b);
	
	assert (c.data[0] == 17);
	assert (c.data[1] == 19);
}


void test_n_max () {
	Crank.VecIntN	a = Crank.VecIntN (2, 17, 20);
	Crank.VecIntN	b = Crank.VecIntN (2, 53, 19);
	
	Crank.VecIntN	c = a.max (b);
	
	assert (c.data[0] == 53);
	assert (c.data[1] == 20);
}


int main (string[] args) {
	GLib.Test.init (ref args);

	GLib.Test.add_func ("/crank/base/vec/int/2/get", test_2_get);
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
