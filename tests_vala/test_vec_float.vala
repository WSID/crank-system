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

bool	float_eq (float a, float b, float delta = 0.0001f) {
	bool result = ((b-delta < a) && (a < b+delta));
	
	if (! result) warning ("%g != %g (diff=%g)", a, b, delta);
	
	return result;
}


void test_2_get () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	
	assert (float_eq (a.x, 3.0f));
	assert (float_eq (a.y, 4.0f));
}


void test_2_equal () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {5.0f, 12.0f};
	Crank.VecFloat2	c = {3.0f, 4.0f};
	
	assert (! Crank.VecFloat2.equal (a, b));
	assert (  Crank.VecFloat2.equal (a, c));
}

void test_2_to_string () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	
	assert (a.to_string () == "(3, 4)");
}


void test_2_magn () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	
	assert (float_eq (a.magn_sq, 25.0f));
	assert (float_eq (a.magn, 5.0f));
}


void test_2_unit () {
	Crank.VecFloat2 a = {3.0f, 4.0f};

	a = a.unit ();
	
	assert (float_eq (a.x, 0.6f));
	assert (float_eq (a.y, 0.8f));
}

void test_2_muls () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	
	a = a.muls (4.0f);
	
	assert (float_eq (a.x, 12.0f));
	assert (float_eq (a.y, 16.0f));
}


void test_2_divs () {
	Crank.VecFloat2	a = {15.0f, 18.0f};
	
	a = a.divs (3.0f);
	
	assert (float_eq (a.x, 5.0f));
	assert (float_eq (a.y, 6.0f));
}


void test_2_add () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	a = a.add (b);
	
	assert (float_eq (a.x, 12.0f));
	assert (float_eq (a.y, 12.0f));
}


void test_2_sub () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	a = a.sub (b);
	
	assert (float_eq (a.x, -6.0f));
	assert (float_eq (a.y, -4.0f));
}


void test_2_dot () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	assert (float_eq (a.dot (b), 59.0f));
}


void test_2_cmpmul () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	a = a.cmpmul (b);
	
	assert (float_eq (a.x, 27.0f));
	assert (float_eq (a.y, 32.0f));
}

void test_2_cmpdiv () {
	Crank.VecFloat2	a = {3.0f, 4.0f};
	Crank.VecFloat2	b = {9.0f, 8.0f};
	
	b = b.cmpdiv (a);

	assert (float_eq (b.x, 3.0f));
	assert (float_eq (b.y, 2.0f));
}


void test_2_cmpless () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecBool2	r = a.cmpless (b);
	
	assert (  r.x);
	assert (! r.y);
}


void test_2_cmpeq () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 20.0f};
	
	Crank.VecBool2	r = a.cmpeq (b);
	
	assert (! r.x);
	assert (  r.y);
}


void test_2_cmpgreater () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecBool2	r = a.cmpgreater (b);
	
	assert (! r.x);
	assert (  r.y);
}


void test_2_cmpcmp () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecInt2	c = a.cmpcmp (b);
	
	assert (c.x < 0);
	assert (c.y > 0);
}


void test_2_min () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecFloat2	c = a.min (b);
	
	assert (float_eq (c.x, 17.0f));
	assert (float_eq (c.y, 19.0f));
}


void test_2_max () {
	Crank.VecFloat2	a = {17.0f, 20.0f};
	Crank.VecFloat2	b = {53.0f, 19.0f};
	
	Crank.VecFloat2	c = a.max (b);

	assert (float_eq (c.x, 53.0f));
	assert (float_eq (c.y, 20.0f));
}


void test_2_mixs () {
	Crank.VecFloat2 a = {15.0f, 21.0f};
	Crank.VecFloat2 b = {30.0f, 11.0f};
	
	Crank.VecFloat2 d = a.mixs (b, 0.2f);
	
	assert (float_eq (d.x, 18.0f));
	assert (float_eq (d.y, 19.0f));
}


void test_2_mix () {
	Crank.VecFloat2 a = {15.0f, 21.0f};
	Crank.VecFloat2 b = {30.0f, 11.0f};
	Crank.VecFloat2 c = {0.3f, 0.7f};
	
	Crank.VecFloat2 d = a.mix (b, c);
	
	assert (float_eq (d.x, 19.5f));
	assert (float_eq (d.y, 14.0f));
}







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
	
	GLib.Test.run ();
	
	return 0;
}
