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

private int
subject_int_0 (int* userdata) {
	int prev = *userdata;
	*userdata = *userdata + 1;
	
	return prev;
}

private int
subject_int_1 (int arg1, int* userdata) {
	int prev = *userdata;
	
	*userdata = prev + arg1;
	
	return prev;
}

private int
subject_int_2 (int arg1, int arg2, int* userdata) {
	int prev = *userdata;
	
	*userdata = prev + arg1 * arg2;
	
	return prev;
}



private void
test_func_join () {
	int subject = 41;
	
	Crank.Func0<int>	func_join_0 =
		Crank.func_0_join <int, int*> (subject_int_0, &subject);
	
	assert (func_join_0 () == 41);
	assert (subject == 42);
	

	subject = 15;
	
	Crank.Func1<int, int>	func_join_1 =
		Crank.func_1_join <int, int, int*> (subject_int_1, &subject);
	
	assert (func_join_1 (45) == 15);
	assert (subject == 60);
	
	
	subject = 6;

	Crank.Func2<int, int, int>	func_join_2 =
		Crank.func_2_join <int, int, int, int*> (subject_int_2, &subject);
	
	assert (func_join_2 (12, 5) == 6);
	assert (subject == 66);
	
}


private void
test_func_split () {
	int subject = 42;
	
	Crank.Func0<int>	func_split_0 = ()=> {
			subject = subject * 2;
			return subject;
	};
	
	void*						func_split_r_0_userdata;
	Crank.RFunc0<int, void*>	func_split_r_0 =
		Crank.func_0_split <int, void*>	(func_split_0, out func_split_r_0_userdata);
	
	assert (func_split_r_0 (func_split_r_0_userdata) == 84);
	assert (subject == 84);
	
	subject = 7;
	
	
	
	Crank.Func1<int, int>	func_split_1 = (a)=> {
			subject = subject * a;
			return subject;
	};
	
	void*							func_split_r_1_userdata;
	Crank.RFunc1<int, int, void*>	func_split_r_1 =
		Crank.func_1_split <int, int, void*> (
				func_split_1, out func_split_r_1_userdata);
	
	assert (func_split_r_1 (9, func_split_r_1_userdata) == 63);
	assert (subject == 63);
}

private void
test_generic_unowned () {
	assert (  Crank.generic_unowned<int> ());
	assert (! Crank.generic_unowned<float?> ());
	assert (  Crank.generic_unowned<unowned string> ());
	assert (! Crank.generic_unowned<string> ());
}



int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func ("/wsid/crank/base/function/join",
			test_func_join);
	
	GLib.Test.add_func ("/wsid/crank/base/function/split",
			test_func_split);
	
	GLib.Test.add_func ("/wsid/crank/base/generic/unowned",
			test_generic_unowned);
	
	GLib.Test.run ();
	
	return 0;
}
