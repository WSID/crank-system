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

	GLib.Test.add_func ("/crank/base/iter/uint",		test_uint	);
	GLib.Test.add_func ("/crank/base/iter/uint/foreach",		test_uint_foreach	);
	
	GLib.Test.run ();

	return 0;
}

private void test_uint () {
	uint	array[] = {3, 9, 1, 3, 2, 5, 5, 9, 7};
	
	uint	prod = 1;
	uint	sum = 0;
	
	Crank.IterMemUint	iter = Crank.IterMemUint.with_array (array);
	
	while (iter.next ()) {
		uint val = iter.get ();
		
		prod *= val;
		sum += val;
	}
	
	assert (prod == 255150);
	assert (sum == 44);
}

private void test_uint_foreach () {
	uint	array[] = {3, 9, 1, 3, 2, 5, 5, 9, 7};
	
	uint	prod = 1;
	uint	sum = 0;
	
	Crank.IterMemUint	iter = Crank.IterMemUint.with_array (array);
	
	iter.foreach ( (val) => {
		prod *= val;
		sum += val;
		
		return true;
	} );
	
	assert (prod == 255150);
	assert (sum == 44);
}
