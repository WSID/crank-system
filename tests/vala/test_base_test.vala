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


	Crank.Test.add_func_expected_fail (	"/crank/base/test/expected_fail",
										test_always_fail	);

	GLib.Test.add_func				(	"/crank/base/test/expected_fail/onpass",
										test_test_expected_fail_onpass	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/expected_fail/subprocess",
										test_always_pass								);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/bool",
										test_assert_eqarray_bool	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/bool/fail",
										test_assert_eqarray_bool_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/bool/imm",
										test_assert_eqarray_bool_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/bool/imm/fail",
										test_assert_eqarray_bool_imm_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/int",
										test_assert_eqarray_int	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/int/fail",
										test_assert_eqarray_int_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/int/imm",
										test_assert_eqarray_int_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/int/imm/fail",
										test_assert_eqarray_int_imm_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/uint",
										test_assert_eqarray_uint	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/uint/fail",
										test_assert_eqarray_uint_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/uint/imm",
										test_assert_eqarray_uint_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/uint/imm/fail",
										test_assert_eqarray_uint_imm_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/float",
										test_assert_eqarray_float	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/float/fail",
										test_assert_eqarray_float_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/float/imm",
										test_assert_eqarray_float_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/float/imm/fail",
										test_assert_eqarray_float_imm_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/pointer",
										test_assert_eqarray_pointer	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/pointer/fail",
										test_assert_eqarray_pointer_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/array/pointer/imm",
										test_assert_eqarray_pointer_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/array/pointer/imm/fail",
										test_assert_eqarray_pointer_imm_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/glist/imm",
										test_assert_eq_glist_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/glist/imm/fail",
										test_assert_eq_glist_imm_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/gptrarray/imm",
										test_assert_eq_gptrarray_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/gptrarray/imm/fail",
										test_assert_eq_gptrarray_imm_fail					);
										



	GLib.Test.add_func				(	"/crank/base/test/cmp/float",
										test_assert_cmpfloat	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/cmp/float/fail",
										test_assert_cmpfloat_fail					);
										

	GLib.Test.add_func				(	"/crank/base/test/eq/cplxfloat",
										test_assert_eqcplxfloat	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/cplxfloat/fail",
										test_assert_eqcplxfloat_fail					);
										

	GLib.Test.add_func				(	"/crank/base/test/eq/cplxfloat/cimm",
										test_assert_eqcplxfloat_cimm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/cplxfloat/cimm/fail",
										test_assert_eqcplxfloat_cimm_fail					);
										

	GLib.Test.add_func				(	"/crank/base/test/eq/permutation/imm",
										test_assert_eq_permutation_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/permutation/imm/fail",
										test_assert_eq_permutation_imm_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/vecbool/2/imm",
										test_assert_eq_vecbool2_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/vecbool/2/imm/fail",
										test_assert_eq_vecbool2_imm_fail					);
										

	GLib.Test.add_func				(	"/crank/base/test/eq/vecbool/n/imm",
										test_assert_eq_vecbool_n_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/vecbool/n/imm/fail",
										test_assert_eq_vecbool_n_imm_fail					);
										


	GLib.Test.add_func				(	"/crank/base/test/eq/vecint/2/imm",
										test_assert_eq_vecint2_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/vecint/2/imm/fail",
										test_assert_eq_vecint2_imm_fail					);
										

	GLib.Test.add_func				(	"/crank/base/test/eq/vecint/n/imm",
										test_assert_eq_vecint_n_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/vecint/n/imm/fail",
										test_assert_eq_vecint_n_imm_fail					);
										
										

	GLib.Test.add_func				(	"/crank/base/test/eq/vecfloat/2/imm",
										test_assert_eq_vecfloat2_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/vecfloat/2/imm/fail",
										test_assert_eq_vecfloat2_imm_fail					);
										

	GLib.Test.add_func				(	"/crank/base/test/eq/vecfloat/n/imm",
										test_assert_eq_vecfloat_n_imm	);
	
	Crank.Test.add_func_expected_fail (	"/crank/base/test/eq/vecfloat/n/imm/fail",
										test_assert_eq_vecfloat_n_imm_fail					);
	GLib.Test.run ();
	
	return 0;
}

private void test_always_pass () {
	assert (1 + 1 == 2);
}

private void test_always_fail () {
	assert (0 == 1);
}


private void test_test_expected_fail_onpass () {
	GLib.Test.trap_subprocess (
			"/crank/base/test/expected_fail/subprocess",
			0,
			GLib.TestSubprocessFlags.STDERR );
	GLib.Test.trap_assert_failed ();
}




private void test_assert_eqarray_bool () {
	bool[]	a = {true, true, false, false};
	bool[]	b = {true, true, false, false};
	
	Crank.assert_eqarray_bool (a, b);
}

private void test_assert_eqarray_bool_fail () {
	bool[]	a = {true, true, true, false};
	bool[]	b = {true, true, false, false};
	
	Crank.assert_eqarray_bool (a, b);
}



private void test_assert_eqarray_bool_imm () {
	bool[]	a = {true, true, false, false};
	
	Crank.assert_eqarray_bool_imm (a, true, true, false, false);
}

private void test_assert_eqarray_bool_imm_fail () {
	bool[]	a = {true, true, true, false};
	
	Crank.assert_eqarray_bool_imm (a, true, true, false, false);
}




private void test_assert_eqarray_int () {
	int[] a = {1, 2, 3, 4};
	int[] b = {1, 2, 3, 4};
	
	Crank.assert_eqarray_int (a, b);
}

private void test_assert_eqarray_int_fail () {
	int[] a = {1, 2, 3, 5};
	int[] b = {1, 2, 3, 4};
	
	Crank.assert_eqarray_int (a, b);
}



private void test_assert_eqarray_int_imm () {
	int[] a = {1, 2, 3, 4};
	
	Crank.assert_eqarray_int_imm (a, 1, 2, 3, 4);
}

private void test_assert_eqarray_int_imm_fail () {
	int[] a = {1, 2, 3, 5};
	
	Crank.assert_eqarray_int_imm (a, 1, 2, 3, 4);
}




private void test_assert_eqarray_uint () {
	uint[] a = {1, 2, 3, 4};
	uint[] b = {1, 2, 3, 4};
	
	Crank.assert_eqarray_uint (a, b);
}

private void test_assert_eqarray_uint_fail () {
	uint[] a = {1, 2, 3, 5};
	uint[] b = {1, 2, 3, 4};
	
	Crank.assert_eqarray_uint (a, b);
}



private void test_assert_eqarray_uint_imm () {
	uint[] a = {1, 2, 3, 4};
	
	Crank.assert_eqarray_uint_imm (a, 1, 2, 3, 4);
}

private void test_assert_eqarray_uint_imm_fail () {
	uint[] a = {1, 2, 3, 5};
	
	Crank.assert_eqarray_uint_imm (a, 1, 2, 3, 4);
}




private void test_assert_eqarray_float () {
	float[] a = {1.0f, 2.0f, 3.0f, 4.0f};
	float[] b = {1.0f, 2.0f, 3.0f, 4.0f};
	
	Crank.assert_eqarray_float (a, b);
}

private void test_assert_eqarray_float_fail () {
	float[] a = {1.0f, 2.0f, 3.0f, 4.1f};
	float[] b = {1.0f, 2.0f, 3.0f, 4.0f};
	
	Crank.assert_eqarray_float (a, b);
}



private void test_assert_eqarray_float_imm () {
	float[] a = {1.0f, 2.0f, 3.0f, 4.0f};
	
	Crank.assert_eqarray_float_imm (a, 1.0f, 2.0f, 3.0f, 4.0f);
}

private void test_assert_eqarray_float_imm_fail () {
	float[] a = {1.0f, 2.0f, 2.9f, 4.0f};
	
	Crank.assert_eqarray_float_imm (a, 1.0f, 2.0f, 3.0f, 4.0f);
}



private void test_assert_eqarray_pointer () {
	void*[]	a = {
			(0x0001).to_pointer(),
			(0x0002).to_pointer(),
			(0x0003).to_pointer(),
			(0x0004).to_pointer() };
	
	void*[]	b = {
			(0x0001).to_pointer(),
			(0x0002).to_pointer(),
			(0x0003).to_pointer(),
			(0x0004).to_pointer() };

	Crank.assert_eqarray_pointer <void*> (a, b);
}

private void test_assert_eqarray_pointer_fail () {
	void*[]	a = {
			(0x0004).to_pointer(),
			(0x0002).to_pointer(),
			(0x0003).to_pointer(),
			(0x0004).to_pointer() };
	
	void*[]	b = {
			(0x0001).to_pointer(),
			(0x0002).to_pointer(),
			(0x0003).to_pointer(),
			(0x0004).to_pointer() };

	Crank.assert_eqarray_pointer <void*> (a, b);
}



private void test_assert_eqarray_pointer_imm () {
	void*[]	a = {
			(0x0001).to_pointer(),
			(0x0002).to_pointer(),
			(0x0003).to_pointer(),
			(0x0004).to_pointer() };
	
	Crank.assert_eqarray_pointer_imm <void*> (a,
			(0x0001).to_pointer(),
			(0x0002).to_pointer(),
			(0x0003).to_pointer(),
			(0x0004).to_pointer() );
}

private void test_assert_eqarray_pointer_imm_fail () {
	void*[]	a = {
			(0x0004).to_pointer(),
			(0x0002).to_pointer(),
			(0x0003).to_pointer(),
			(0x0004).to_pointer() };
	
	Crank.assert_eqarray_pointer_imm <void*> (a,
			(0x0001).to_pointer(),
			(0x0002).to_pointer(),
			(0x0003).to_pointer(),
			(0x0004).to_pointer() );
}


private void test_assert_eq_glist_imm () {
	GLib.List<int>	a = new GLib.List<int> ();
	
	a.append (2);
	a.append (3);
	a.append (7);
	
	Crank.assert_eq_glist_imm <int> (a, 2, 3, 7);
}

private void test_assert_eq_glist_imm_fail () {
	GLib.List<int>	a = new GLib.List<int> ();
	
	a.append (2);
	a.append (3);
	a.append (6);
	
	Crank.assert_eq_glist_imm <int> (a, 2, 3, 7);
}



private void test_assert_eq_gptrarray_imm () {
	GLib.GenericArray<int>	a = new GLib.GenericArray<int> ();
	
	a.add (2);
	a.add (3);
	a.add (5);
	a.add (8);
	
	Crank.assert_eq_gptrarray_imm <int> (a, 2, 3, 5, 8);
}

private void test_assert_eq_gptrarray_imm_fail () {
	GLib.GenericArray<int>	a = new GLib.GenericArray<int> ();
	
	a.add (2);
	a.add (3);
	a.add (5);
	a.add (8);
	
	Crank.assert_eq_gptrarray_imm <int> (a, 2, 3, 5, 7, 9);
}


private void test_assert_cmpfloat () {
	Crank.assert_eqfloat (3.0f, 3.5f, 1.0f);
	Crank.assert_lefloat (2.0f, 3.5f, 1.0f);
}

private void test_assert_cmpfloat_fail () {
	Crank.assert_lefloat (7.5f, 3.5f, 1.0f);
}


private void test_assert_eqcplxfloat () {
	Crank.CplxFloat	a = {3.0f, 2.0f};
	Crank.CplxFloat	b = {3.5f, 2.1f};
	Crank.CplxFloat c = {2.9f, 1.4f};
	
	Crank.assert_eqcplxfloat (a, b, 1.0f);
	Crank.assert_eqcplxfloat (a, c, 1.0f);
}

private void test_assert_eqcplxfloat_fail () {
	Crank.CplxFloat	a = {3.0f, 2.0f};
	Crank.CplxFloat	b = {4.2f, 2.1f};
	
	Crank.assert_eqcplxfloat (a, b, 1.0f);
}


private void test_assert_eqcplxfloat_cimm () {
	Crank.CplxFloat	a = {3.0f, 2.0f};
	
	Crank.assert_eqcplxfloat_cimm (a, 3.5f, 2.1f, 1.0f);
	Crank.assert_eqcplxfloat_cimm (a, 2.9f, 1.4f, 1.0f);
}

private void test_assert_eqcplxfloat_cimm_fail () {
	Crank.CplxFloat	a = {3.0f, 2.0f};
	Crank.CplxFloat	b = {4.2f, 2.1f};
	
	Crank.assert_eqcplxfloat_cimm (a, 4.2f, 2.1f, 1.0f);
}


private void test_assert_eq_permutation_imm () {
	Crank.Permutation a = Crank.Permutation (4, 0, 1, 3, 2);
	
	Crank.assert_eq_permutation_imm (a, 0, 1, 3, 2);
}

private void test_assert_eq_permutation_imm_fail () {
	Crank.Permutation a = Crank.Permutation (4, 0, 1, 2, 3);
	
	Crank.assert_eq_permutation_imm (a, 0, 1, 3, 2);
}


private void test_assert_eq_vecbool2_imm () {
	Crank.VecBool2 a = {true, false};
	
	Crank.assert_eq_vecbool2_imm (a, true, false);
}

private void test_assert_eq_vecbool2_imm_fail () {
	Crank.VecBool2 a = {true, true};
	
	Crank.assert_eq_vecbool2_imm (a, true, false);
}



private void test_assert_eq_vecbool_n_imm () {
	Crank.VecBoolN a = Crank.VecBoolN.arr ({true, false, false, true, true});
	
	Crank.assert_eq_vecbool_n_imm (a, true, false, false, true, true);
}

private void test_assert_eq_vecbool_n_imm_fail () {
	Crank.VecBoolN a = Crank.VecBoolN.arr ({true, true, false, true, true});
	
	Crank.assert_eq_vecbool_n_imm (a, true, false, false, true, true);
}


private void test_assert_eq_vecint2_imm () {
	Crank.VecInt2 a = {2, 3};
	
	Crank.assert_eq_vecint2_imm (a, 2, 3);
}

private void test_assert_eq_vecint2_imm_fail () {
	Crank.VecInt2 a = {2, 2};
	
	Crank.assert_eq_vecint2_imm (a, 2, 3);
}



private void test_assert_eq_vecint_n_imm () {
	Crank.VecIntN a = Crank.VecIntN.arr ({3, 4, 5, 12});
	
	Crank.assert_eq_vecint_n_imm (a, 3, 4, 5, 12);
}

private void test_assert_eq_vecint_n_imm_fail () {
	Crank.VecIntN a = Crank.VecIntN.arr ({3, 4, 5, 13});
	
	Crank.assert_eq_vecint_n_imm (a, 3, 4, 5, 12);
}


private void test_assert_eq_vecfloat2_imm () {
	Crank.VecFloat2 a = {2.0f, 3.0f};
	
	Crank.assert_eq_vecfloat2_imm (a, 2.0f, 3.0f);
}

private void test_assert_eq_vecfloat2_imm_fail () {
	Crank.VecFloat2 a = {2.0f, 2.9f};
	
	Crank.assert_eq_vecfloat2_imm (a, 2.0f, 3.0f);
}



private void test_assert_eq_vecfloat_n_imm () {
	Crank.VecFloatN a = Crank.VecFloatN.arr ({3.0f, 4.0f, 5.0f, 12.0f});
	
	Crank.assert_eq_vecfloat_n_imm (a, 3.0f, 4.0f, 5.0f, 12.0f);
}

private void test_assert_eq_vecfloat_n_imm_fail () {
	Crank.VecFloatN a = Crank.VecFloatN.arr ({3.0f, 4.0f, 5.1f, 12.0f});
	
	Crank.assert_eq_vecfloat_n_imm (a, 3.0f, 4.0f, 5.0f, 12.0f);
}
