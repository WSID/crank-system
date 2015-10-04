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

#include <glib.h>

#include "crankbase.h"

//////// Declaration ///////////////////////////////////////////////////////////

static void		test_equal ( void );

static void		test_equal_delta ( void );

static void		test_get_norm ( void );

static void		test_get_rangle ( void );

static void		test_get_raxis ( void );

static void		test_neg ( void );

static void		test_inverse ( void );

static void		test_conjugate ( void );

static void		test_unit ( void );

static void		test_addr ( void );

static void		test_subr ( void );

static void		test_mulr ( void );

static void		test_divr ( void );

static void		test_rsubr ( void );

static void		test_rdivr ( void );

static void		test_addc ( void );

static void		test_subc ( void );

static void 	test_mulc ( void );

static void		test_add ( void );

static void		test_sub ( void );

static void 	test_mul ( void );

static void		test_mul_conj ( void );

static void		test_mix ( void );

static void		test_ln ( void );

static void		test_exp ( void );

static void		test_powr ( void );

static void		test_rotatev (void);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (	gint   argc,
      	gchar *argv[] )
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/crank/base/quat/float/equal",		test_equal		);
	g_test_add_func ("/crank/base/quat/float/equal/delta",	test_equal_delta);
	g_test_add_func ("/crank/base/quat/float/get_norm",		test_get_norm	);
	g_test_add_func ("/crank/base/quat/float/get_rangle",	test_get_rangle	);
	g_test_add_func ("/crank/base/quat/float/get_raxis",	test_get_raxis	);
	g_test_add_func ("/crank/base/quat/float/neg",			test_neg		);
	g_test_add_func ("/crank/base/quat/float/inverse",		test_inverse	);
	g_test_add_func ("/crank/base/quat/float/conjugate",	test_conjugate	);
	g_test_add_func ("/crank/base/quat/float/unit",			test_unit		);
	g_test_add_func ("/crank/base/quat/float/addr",			test_addr		);
	g_test_add_func ("/crank/base/quat/float/subr",			test_subr		);
	g_test_add_func ("/crank/base/quat/float/mulr",			test_mulr		);
	g_test_add_func ("/crank/base/quat/float/divr",			test_divr		);
	g_test_add_func ("/crank/base/quat/float/rsubr",		test_rsubr		);
	g_test_add_func ("/crank/base/quat/float/rdivr",		test_rdivr		);
	g_test_add_func ("/crank/base/quat/float/addc",			test_addc		);
	g_test_add_func ("/crank/base/quat/float/subc",			test_subc		);
	g_test_add_func ("/crank/base/quat/float/mulc",			test_mulc		);
	g_test_add_func ("/crank/base/quat/float/add",			test_add		);
	g_test_add_func ("/crank/base/quat/float/sub",			test_sub		);
	g_test_add_func ("/crank/base/quat/float/mul",			test_mul		);
	g_test_add_func ("/crank/base/quat/float/mul_conj",		test_mul_conj	);
	g_test_add_func ("/crank/base/quat/float/mix",			test_mix		);
	g_test_add_func ("/crank/base/quat/float/ln",			test_ln			);
	g_test_add_func ("/crank/base/quat/float/exp",			test_exp		);
	g_test_add_func ("/crank/base/quat/float/powr",			test_powr		);
	g_test_add_func ("/crank/base/quat/float/rotatev",		test_rotatev	);
	
	g_test_run ();

	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static void
test_equal ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	c = {4.0f, 3.0f, 5.0f, 12.0f};
	
	g_assert (crank_quat_float_equal (&a, &b));
	g_assert (! crank_quat_float_equal (&a, &c));
}

static void
test_equal_delta ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b = {3.2f, 4.1f, 5.0f, 11.9f};
	CrankQuatFloat	c = {4.0f, 3.0f, 5.0f, 11.0f};
	
	g_assert (crank_quat_float_equal_delta (&a, &b, 1.0f));
	g_assert (! crank_quat_float_equal_delta (&a, &c, 1.0f));
}

static void
test_get_norm ( void )
{
	CrankQuatFloat	quat = {3.0f, 4.0f, 5.0f, 12.0f};
	
	crank_assert_cmpfloat (crank_quat_float_get_norm (&quat), ==, 13.9284f);
}

static void
test_get_rangle ( void )
{
	CrankQuatFloat	quat = {0.4794f, 0.5067f, 0.5067f, 0.5067f};
	
	crank_assert_cmpfloat (crank_quat_float_get_rangle (&quat), ==, 2.1416f);
}

static void
test_get_raxis ( void )
{
	CrankQuatFloat	quat = {0.4794f, 0.5067f, 0.5067f, 0.5067f};
	CrankVecFloat3	axis;
	
	crank_quat_float_get_raxis (&quat, &axis);
	
	crank_assert_eq_vecfloat3_imm (&axis, 0.5774f, 0.5774f, 0.5774f);
}

static void
test_neg ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_neg (&a, &b);
	
	crank_assert_cmpfloat (b.w, ==, -3.0f);
	crank_assert_cmpfloat (b.x, ==, -4.0f);
	crank_assert_cmpfloat (b.y, ==, -5.0f);
	crank_assert_cmpfloat (b.z, ==, -12.0f);
}

static void
test_inverse ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_inverse (&a, &b);
	
	crank_assert_cmpfloat (b.w, ==,  0.0155f);
	crank_assert_cmpfloat (b.x, ==, -0.0206f);
	crank_assert_cmpfloat (b.y, ==, -0.0258f);
	crank_assert_cmpfloat (b.z, ==, -0.0619f);
}

static void
test_conjugate ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_conjugate (&a, &b);
	
	crank_assert_cmpfloat (b.w, ==, 3.0f);
	crank_assert_cmpfloat (b.x, ==, -4.0f);
	crank_assert_cmpfloat (b.y, ==, -5.0f);
	crank_assert_cmpfloat (b.z, ==, -12.0f);
}

static void
test_unit ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_unit (&a, &b);
	
	crank_assert_cmpfloat (b.w, ==, 0.2154f);
	crank_assert_cmpfloat (b.x, ==, 0.2872f);
	crank_assert_cmpfloat (b.y, ==, 0.3590f);
	crank_assert_cmpfloat (b.z, ==, 0.8615f);
}

static void
test_addr ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_addr (&a, 2.0f, &b);
	
	crank_assert_cmpfloat (b.w, ==, 5.0f);
	crank_assert_cmpfloat (b.x, ==, 4.0f);
	crank_assert_cmpfloat (b.y, ==, 5.0f);
	crank_assert_cmpfloat (b.z, ==, 12.0f);
}

static void
test_subr ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_subr (&a, 2.0f, &b);
	
	crank_assert_cmpfloat (b.w, ==, 1.0f);
	crank_assert_cmpfloat (b.x, ==, 4.0f);
	crank_assert_cmpfloat (b.y, ==, 5.0f);
	crank_assert_cmpfloat (b.z, ==, 12.0f);
}

static void
test_mulr ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_mulr (&a, 2.0f, &b);
	
	crank_assert_cmpfloat (b.w, ==, 6.0f);
	crank_assert_cmpfloat (b.x, ==, 8.0f);
	crank_assert_cmpfloat (b.y, ==, 10.0f);
	crank_assert_cmpfloat (b.z, ==, 24.0f);
}

static void
test_divr ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_divr (&a, 2.0f, &b);
	
	crank_assert_cmpfloat (b.w, ==, 1.5f);
	crank_assert_cmpfloat (b.x, ==, 2.0f);
	crank_assert_cmpfloat (b.y, ==, 2.5f);
	crank_assert_cmpfloat (b.z, ==, 6.0f);
}

static void
test_rsubr ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_rsubr (&a, 2.0f, &b);
	
	crank_assert_cmpfloat (b.w, ==, -1.0f);
	crank_assert_cmpfloat (b.x, ==, -4.0f);
	crank_assert_cmpfloat (b.y, ==, -5.0f);
	crank_assert_cmpfloat (b.z, ==, -12.0f);
}

static void
test_rdivr ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_rdivr (&a, 2.0f, &b);
	
	crank_assert_cmpfloat (b.w, ==,  0.0309f);
	crank_assert_cmpfloat (b.x, ==, -0.0412f);
	crank_assert_cmpfloat (b.y, ==, -0.0515f);
	crank_assert_cmpfloat (b.z, ==, -0.1237f);
}



static void
test_addc ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankCplxFloat	b = {2.0f, 3.0f};
	CrankQuatFloat	c;
	
	crank_quat_float_addc (&a, &b, &c);
	
	crank_assert_cmpfloat (c.w, ==, 5.0f);
	crank_assert_cmpfloat (c.x, ==, 7.0f);
	crank_assert_cmpfloat (c.y, ==, 5.0f);
	crank_assert_cmpfloat (c.z, ==, 12.0f);
}

static void
test_subc ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankCplxFloat	b = {2.0f, 3.0f};
	CrankQuatFloat	c;
	
	crank_quat_float_subc (&a, &b, &c);
	
	crank_assert_cmpfloat (c.w, ==, 1.0f);
	crank_assert_cmpfloat (c.x, ==, 1.0f);
	crank_assert_cmpfloat (c.y, ==, 5.0f);
	crank_assert_cmpfloat (c.z, ==, 12.0f);
}

static void
test_mulc ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankCplxFloat	b = {2.0f, 3.0f};
	CrankQuatFloat	c;
	
	crank_quat_float_mulc (&a, &b, &c);
	
	crank_assert_cmpfloat (c.w, ==, -6.0f);
	crank_assert_cmpfloat (c.x, ==, 17.0f);
	crank_assert_cmpfloat (c.y, ==, 46.0f);
	crank_assert_cmpfloat (c.z, ==, 9.0f);
}



static void
test_add ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b = {2.0f, 3.0f, 5.0f, 8.0f};
	CrankQuatFloat	c;
	
	crank_quat_float_add (&a, &b, &c);
	
	crank_assert_cmpfloat (c.w, ==, 5.0f);
	crank_assert_cmpfloat (c.x, ==, 7.0f);
	crank_assert_cmpfloat (c.y, ==, 10.0f);
	crank_assert_cmpfloat (c.z, ==, 20.0f);
}

static void
test_sub ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b = {2.0f, 3.0f, 5.0f, 8.0f};
	CrankQuatFloat	c;
	
	crank_quat_float_sub (&a, &b, &c);
	
	crank_assert_cmpfloat (c.w, ==, 1.0f);
	crank_assert_cmpfloat (c.x, ==, 1.0f);
	crank_assert_cmpfloat (c.y, ==, 0.0f);
	crank_assert_cmpfloat (c.z, ==, 4.0f);
}

static void
test_mul ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b = {2.0f, 3.0f, 5.0f, 8.0f};
	CrankQuatFloat	c;
	
	crank_quat_float_mul (&a, &b, &c);
	
	crank_assert_cmpfloat (c.w, ==, -127.0f);
	crank_assert_cmpfloat (c.x, ==, -3.0f);
	crank_assert_cmpfloat (c.y, ==, 29.0f);
	crank_assert_cmpfloat (c.z, ==, 53.0f);
}


static void
test_mul_conj ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b = {2.0f, 3.0f, 5.0f, 8.0f};
	CrankQuatFloat	c;
	
	crank_quat_float_mul_conj (&a, &b, &c);
	
	crank_assert_cmpfloat (c.w, ==, 139.0f);
	crank_assert_cmpfloat (c.x, ==, 19.0f);
	crank_assert_cmpfloat (c.y, ==, -9.0f);
	crank_assert_cmpfloat (c.z, ==, -5.0f);
}

static void
test_mix ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b = {2.0f, 3.0f, 5.0f, 8.0f};
	CrankQuatFloat	c;
	
	crank_quat_float_mix (&a, &b, 0.25f, &c);
	
	crank_assert_cmpfloat (c.w, ==, 2.75f);
	crank_assert_cmpfloat (c.x, ==, 3.75f);
	crank_assert_cmpfloat (c.y, ==, 5.0f);
	crank_assert_cmpfloat (c.z, ==, 11.0f);
}

static void
test_ln ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_ln (&a, &b);
	
	crank_assert_cmpfloat (b.w, ==, 2.6339f);
	crank_assert_cmpfloat (b.x, ==, 0.3981f);
	crank_assert_cmpfloat (b.y, ==, 0.4976f);
	crank_assert_cmpfloat (b.z, ==, 1.1943f);
}

static void
test_exp ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_exp (&a, &b);
	
	crank_assert_cmpfloat (b.w, ==, 10.2525f);
	crank_assert_cmpfloat (b.x, ==, 5.0794f);
	crank_assert_cmpfloat (b.y, ==, 6.3492f);
	crank_assert_cmpfloat (b.z, ==, 15.2382f);
}

static void
test_powr ( void )
{
	CrankQuatFloat	a = {3.0f, 4.0f, 5.0f, 12.0f};
	CrankQuatFloat	b;
	
	crank_quat_float_powr (&a, 2.5f, &b);
	
	crank_assert_cmpfloat (b.w, ==, -702.8075f);
	crank_assert_cmpfloat (b.x, ==, -51.1662f);
	crank_assert_cmpfloat (b.y, ==, -63.9578f);
	crank_assert_cmpfloat_d (b.z, ==, -153.4986f, 0.0005f);
}

static void
test_rotatev (void)
{
	CrankQuatFloat	quat = {0.4794f, 0.5067f, 0.5067f, 0.5067f};
	CrankVecFloat3	vec	= {1.0f, 2.0f, 3.0f};
	CrankVecFloat3	rvec;
	
	crank_quat_float_rotatev (&quat, &vec, &rvec);
	crank_assert_eq_vecfloat3_imm (&rvec, 3.0264f, 1.0285f, 1.9455f);
}
