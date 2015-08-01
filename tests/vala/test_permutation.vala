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

	GLib.Test.add_func ("/crank/base/permutation/hash",
		test_hash );

	GLib.Test.add_func ("/crank/base/permutation/equal",
		test_equal );

	GLib.Test.add_func ("/crank/base/permutation/to_string",
		test_to_string );

	GLib.Test.add_func ("/crank/base/permutation/is_empty",
		test_is_empty );

	GLib.Test.add_func ("/crank/base/permutation/slice",
		test_slice );
	
	GLib.Test.add_func ("/crank/base/permutation/is_identity",
		test_is_identity );
	
	GLib.Test.add_func ("/crank/base/permutation/inversion",
		test_inversion );
	
	GLib.Test.add_func ("/crank/base/permutation/sign",
		test_sign );
		
	GLib.Test.add_func ("/carnk/base/permutation/ascents",
		test_ascents );
	
	GLib.Test.add_func ("/crank/base/permutation/descents",
		test_descents );
	
	GLib.Test.add_func ("/crank/base/permutation/excedances",
		test_excedances );
	
	GLib.Test.add_func ("/crank/base/permutation/swap",
		test_swap );
	
	GLib.Test.add_func ("/crank/base/permutation/reverse",
		test_reverse );
	
	GLib.Test.add_func ("/crank/base/permutation/inverse",
		test_inverse );
		
	GLib.Test.add_func ("/crank/base/permutation/shuffle",
		test_shuffle );
		
	GLib.Test.add_func ("/crank/base/permutation/shuffle_sarray",
		test_shuffle_sarray );
		
	GLib.Test.add_func ("/crank/base/permutation/shuffle_parray",
		test_shuffle_parray );
		
	GLib.Test.add_func ("/crank/base/permutation/shuffle_array/boolean",
		test_shuffle_array_boolean );
		
	GLib.Test.add_func ("/crank/base/permutation/shuffle_array/int",
		test_shuffle_array_int );
		
	GLib.Test.add_func ("/crank/base/permutation/shuffle_array/float",
		test_shuffle_array_float );

	GLib.Test.add_func ("/crank/base/permutation/init/compare/sarray",
		test_init_compare_sarray );

	GLib.Test.add_func ("/crank/base/permutation/init/compare/parray",
		test_init_compare_parray );
	
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

private void test_hash () {
	Crank.Permutation	p = Crank.Permutation (5,	0, 1, 2, 4, 3);
	Crank.Permutation	q = Crank.Permutation (5,	0, 1, 2, 4, 3);
	Crank.Permutation	r = Crank.Permutation (5,	0, 1, 4, 2, 3);
	
	assert (p.hash () == q.hash ());
	assert (p.hash () != r.hash ());
}

private void test_equal () {
	Crank.Permutation	p = Crank.Permutation (5,	0, 1, 2, 4, 3);
	Crank.Permutation	q = Crank.Permutation (5,	0, 1, 2, 4, 3);
	Crank.Permutation	r = Crank.Permutation (5,	0, 1, 4, 2, 3);
	
	assert (p.equal (q));
	assert (! p.equal (r));
}

private void test_to_string () {
	Crank.Permutation	p = Crank.Permutation (5,	0, 1, 2, 4, 3);
	
	assert (p.to_string () == "(0, 1, 2, 4, 3)");
}



private void test_is_empty () {
	Crank.Permutation	p = Crank.Permutation (1,	0);
	assert (! p.is_empty ());
	
	p = Crank.Permutation (0);
	assert (p.is_empty ());
}

private void test_slice () {
	Crank.Permutation	p = Crank.Permutation (5, 	0, 1, 2, 4, 3);
	
	uint[]	slice = p[1:4];
	
	assert (slice[0] == 1);
	assert (slice[1] == 2);
	assert (slice[2] == 4);
}

private void test_is_identity () {
	Crank.Permutation	p = Crank.Permutation (3,	0, 1, 2);
	assert (p.is_identity ());
	
	p = Crank.Permutation (3,	2, 1, 0);
	assert (! p.is_identity ());
}

private void test_inversion () {
	Crank.Permutation	p = Crank.Permutation (5,	2, 1, 3, 4, 0);
	assert (p.inversion == 5);
}

private void test_sign () {
	Crank.Permutation	p = Crank.Permutation (5,	2, 1, 3, 4, 0);
	
	assert (p.sign == -1);
}

private void test_ascents () {
	Crank.Permutation	p = Crank.Permutation (5,	2, 1, 3, 4, 0);
	uint[] ascents = p.ascents;
	
	assert (ascents.length == 2);
	assert (ascents[0] == 1);
	assert (ascents[1] == 2);
}

private void test_descents () {
	Crank.Permutation	p = Crank.Permutation (5,	2, 1, 3, 4, 0);
	uint[] descents = p.descents;
	
	assert (descents.length == 2);
	assert (descents[0] == 0);
	assert (descents[1] == 3);
}

private void test_excedances () {
	Crank.Permutation	p = Crank.Permutation (5,	2, 1, 3, 4, 0);
	uint[] excedances = p.excedances;
	
	assert (excedances.length == 3);
	assert (excedances[0] == 0);
	assert (excedances[1] == 2);
	assert (excedances[2] == 3);
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

private void test_shuffle_sarray () {
	Crank.Permutation	p = Crank.Permutation (4,	0, 1, 3, 2);
	float				arr[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	float*				narr;
	
	narr = (float*) p.shuffle_sarray(sizeof (float), arr);
	
	assert (narr[0] == 1.0f);
	assert (narr[1] == 2.0f);
	assert (narr[2] == 4.0f);
	assert (narr[3] == 3.0f);
	
	free (narr);
}

private void test_shuffle_parray () {
	Crank.Permutation	p = Crank.Permutation (4,	0, 1, 3, 2);
	// TODO: Use generic pointers. This test will broke in 32-bit systems.
	int64				arr[4] = {0, 1, 2, 3};
	int64[]				narr;
	
	narr = p.shuffle_parray<int64> (arr);
	
	
}


private void test_shuffle_array_boolean () {
	Crank.Permutation	p = Crank.Permutation (4,	0, 1, 3, 2);
	bool				arr[4] = {true, false, false, true};
	bool[]				narr;
	
	narr = p.shuffle_array_boolean (arr);
	
	Crank.assert_eqarray_bool_imm (narr, 	true, false, true, false);
}


private void test_shuffle_array_int () {
	Crank.Permutation	p = Crank.Permutation (4,	0, 1, 3, 2);
	int					arr[4] = {3, 4, 5, 12};
	int[]				narr;
	
	narr = p.shuffle_array_int (arr);
	
	Crank.assert_eqarray_int_imm (narr, 	3, 4, 12, 5);
}


private void test_shuffle_array_float () {
	Crank.Permutation	p = Crank.Permutation (4,	0, 1, 3, 2);
	float				arr[4] = {1.1f, 2.4f, 5.9f, 4.0f};
	float[]				narr;
	
	narr = p.shuffle_array_float (arr);
	
	Crank.assert_eqarray_float_imm (narr, 	1.1f, 2.4f, 4.0f, 5.9f);
}



private void test_init_compare_sarray () {
	double	arr[4] = {1.5, 8.8, 4.5, 2.9};

	Crank.Permutation p = Crank.Permutation.compare_sarray<double?> (
			4, sizeof (double), (void*)arr,
			(a, b) => ((int)(b < a) - (int)(a < b)) );

	Crank.assert_eq_permutation_imm (p, 0, 3, 2, 1);
}

private void test_init_compare_parray () {
	int? arr[4] = {4, 19, 2, 44};

	Crank.Permutation p = Crank.Permutation.compare_parray<int?> (arr,
			(a, b) => ((int)(b < a) - (int)(a < b)) );

	Crank.assert_eq_permutation_imm (p, 2, 0, 1, 3);
}
