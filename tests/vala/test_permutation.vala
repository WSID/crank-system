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
	
	GLib.Test.add_func ("/crank/base/permutation/check_valid",
		test_check_valid );
	
	GLib.Test.add_func ("/crank/base/permutation/sign",
		test_sign );
	
	GLib.Test.add_func ("/crank/base/permutation/swap",
		test_swap );
	
	GLib.Test.add_func ("/crank/base/permutation/reverse",
		test_reverse );
	
	GLib.Test.add_func ("/crank/base/permutation/inverse",
		test_inverse );
		
	GLib.Test.add_func ("/crank/base/permutatino/shuffle",
		test_shuffle );
	
	GLib.Test.run ();
	
	return 0;
}



private void test_check_valid () {
	Crank.Permutation	p = Crank.Permutation (5,	0, 1, 2, 3, 4);
	Crank.Permutation	q = Crank.Permutation (5,	0, 3, 0, 1, 2);
	Crank.Permutation	r = Crank.Permutation (5,	0, 7, 4, 3, 6);
	
	assert (p.check_valid ());
	assert (! q.check_valid ());
	assert (! r.check_valid ());
}

private void test_sign () {
	Crank.Permutation	p = Crank.Permutation (5,	2, 1, 3, 4, 0);
	
	assert (p.sign == -1);
}

private void test_swap () {
	Crank.Permutation	p = Crank.Permutation (5,	0, 1, 3, 2, 4);
	
	p.swap (2, 3);
	
	assert (p[2] == 2);
	assert (p[3] == 3);
}

private void test_reverse () {
	Crank.Permutation	p = Crank.Permutation (5,	0, 1, 3, 2, 4);

	p = p.reverse ();
	
	assert (p[0] == 4);
	assert (p[1] == 2);
	assert (p[2] == 3);
	assert (p[3] == 1);
	assert (p[4] == 0);
}

private void test_inverse () {
	Crank.Permutation	p = Crank.Permutation (5,	0, 1, 3, 2, 4);

	p = p.inverse ();
	
	assert (p[0] == 0);
	assert (p[1] == 1);
	assert (p[2] == 3);
	assert (p[3] == 2);
	assert (p[4] == 4);
}

private void test_shuffle () {
	Crank.Permutation	p = Crank.Permutation (4,	0, 1, 3, 2);
	Crank.Permutation	q = Crank.Permutation (4,	1, 0, 2, 3);
	
	p = p.shuffle (q);
	
	assert (p[0] == 1);
	assert (p[1] == 0);
	assert (p[2] == 3);
	assert (p[3] == 2);
}
