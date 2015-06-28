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

[CCode (has_target=false)]
private delegate int	SubjectFuncTypeR (int* userdata);

private delegate int	SubjectFuncType ();


int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func ("/crank/base/vala/function/join",
			test_func_join);
	
	GLib.Test.add_func ("/crank/base/vala/function/split",
			test_func_split);
	
	GLib.Test.add_func ("/crank/base/vala/generic/unowned",
			test_generic_unowned);
	
	GLib.Test.add_func ("/crank/base/vala/closure",
			test_create_closure);
			
	GLib.Test.run ();
	
	return 0;
}


private int
subject_int_0 (int* userdata) {
	int prev = *userdata;
	*userdata = *userdata + 1;
	
	return prev;
}


private void test_func_join () {
	int subject = 41;
	
	SubjectFuncType	func =
		(SubjectFuncType) Crank.func_join ((GLib.Callback)subject_int_0, &subject);
	
	assert (func () == 41);
	assert (subject == 42);
}


private void test_func_split () {
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

private void test_generic_unowned () {
	assert (  Crank.generic_unowned<int> ());
	assert (! Crank.generic_unowned<float?> ());
	assert (  Crank.generic_unowned<unowned string> ());
	assert (! Crank.generic_unowned<string> ());
}


private void test_create_closure () {
	SubjectFuncType func = () => 733;
	GLib.Closure closure = Crank.create_closure ((Crank.Callback)func);
	GLib.Value value = GLib.Value (typeof (int));
	
	Crank.closure_invoke (closure, ref value, {(void*)null}, null);
	
	assert (value.get_int () == 733);
}
