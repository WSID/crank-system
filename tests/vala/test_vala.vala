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

[CCode (has_target=false)]
private delegate int	SubjectFuncTypeR (int* userdata);

private delegate int	SubjectFuncType ();

private int
subject_int_0 (int* userdata) {
	int prev = *userdata;
	*userdata = *userdata + 1;
	
	return prev;
}


private void
test_func_join () {
	int subject = 41;
	
	SubjectFuncType	func =
		(SubjectFuncType) Crank.func_join ((GLib.Callback)subject_int_0, &subject);
	
	assert (func () == 41);
	assert (subject == 42);
}


private void
test_func_split () {
	int subject = 42;
	
	SubjectFuncType		func_join = () => {
			subject = subject * 2;
			return subject;
	};
	
	void*				func_userdata;
	SubjectFuncTypeR	func =
		(SubjectFuncTypeR) Crank.func_split ((Crank.Callback)func_join, out func_userdata);
	
	assert (func (func_userdata) == 84);
	assert (subject == 84);
}

private void
test_generic_unowned () {
	assert (  Crank.generic_unowned<int> ());
	assert (! Crank.generic_unowned<float?> ());
	assert (  Crank.generic_unowned<unowned string> ());
	assert (! Crank.generic_unowned<string> ());
}


private void
test_create_closure () {
	SubjectFuncType func = () => 733;
	GLib.Closure closure = Crank.create_closure ((Crank.Callback)func);
	GLib.Value value = GLib.Value (typeof (int));
	
	Crank.closure_invoke (closure, ref value, {(void*)null}, null);
	
	assert (value.get_int () == 733);
}


int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func ("/wsid/crank/base/function/join",
			test_func_join);
	
	GLib.Test.add_func ("/wsid/crank/base/function/split",
			test_func_split);
	
	GLib.Test.add_func ("/wsid/crank/base/generic/unowned",
			test_generic_unowned);
	
	GLib.Test.add_func ("/wsid/crank/base/closure",
			test_create_closure);
			
	GLib.Test.run ();
	
	return 0;
}
