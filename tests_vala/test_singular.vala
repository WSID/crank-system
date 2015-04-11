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

private class TestSubject: Crank.Singular {
	public int int_item { get; construct set; }
	public int first_construct_times { get; private set; }
	
	public override void first_construct () {
		first_construct_times++;
	}
	
	public TestSubject (int int_item) {
		Object (int_item: int_item);
	}
}


public void test_singular_new () {
	TestSubject		singular_a;
	TestSubject		singular_b;
	
	if (GLib.Test.subprocess()) {
		singular_a = new TestSubject(1);
		singular_b = new TestSubject(2);
		
		assert (singular_a == singular_b);
		assert (singular_b.int_item == 1);
		
		return;
	}
	
	GLib.Test.trap_subprocess (null, 0, 0);
	GLib.Test.trap_assert_passed ();
}

public void test_singular_has () {
	TestSubject		singular;
	
	if (GLib.Test.subprocess()) {
		assert (! Crank.Singular.has (typeof (TestSubject)));
		
		singular = new TestSubject(3);
		
		assert ( Crank.Singular.has (typeof (TestSubject)));
		
		return;
	}
	
	GLib.Test.trap_subprocess (null, 0, 0);
	GLib.Test.trap_assert_passed ();
}

public void test_singular_get () {
	TestSubject?	singular_a;
	TestSubject		singular_b;
	
	if (GLib.Test.subprocess()) {
		singular_a = (TestSubject) Crank.Singular.get (typeof (TestSubject));
		
		assert (singular_a == null);
		
		singular_b = new TestSubject(3);
		singular_a = (TestSubject) Crank.Singular.get (typeof (TestSubject));
		
		assert (singular_a != null);
		assert (singular_b.int_item == 3);
		return;
	}
	
	GLib.Test.trap_subprocess (null, 0, 0);
	GLib.Test.trap_assert_passed ();
}


public void test_singular_first_construct () {
	TestSubject		singular_a;
	TestSubject		singular_b;
	
	if (GLib.Test.subprocess()) {
		singular_a = new TestSubject (7);
		
		assert (singular_a.first_construct_times == 1);

		singular_b = new TestSubject (3);
		
		assert (singular_a.first_construct_times == 1);
		
		return;
	}
	
	GLib.Test.trap_subprocess (null, 0, 0);
	GLib.Test.trap_assert_passed ();
}

int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func ("/wsid/crank/base/singular/new",
			test_singular_new);
	
	GLib.Test.add_func ("/wsid/crank/base/singular/has",
			test_singular_has);
			
	GLib.Test.add_func ("/wsid/crank/base/singular/get",
			test_singular_get);
	
	GLib.Test.add_func ("/wsid/crank/base/singular/first_construct",
			test_singular_first_construct);
			
	GLib.Test.run ();
	
	return 0;
}
