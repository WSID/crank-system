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

#include <string.h>
#include <glib.h>

#include "crankbase.h"


//////// Declaration ///////////////////////////////////////////////////////////

static void test_addinit (void);
static void test_mulinit (void);

static void test_add64 (void);
static void test_add (void);
static void test_sub64 (void);
static void test_sub (void);
static void test_mul64 (void);
static void test_div (void);
static void test_div64 (void);
static void test_div32 (void);
static void test_div32_self (void);
static void test_shift (void);

//////// Main //////////////////////////////////////////////////////////////////
gint
main	(gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/crank/base/128/add/init",
					test_addinit				);

	g_test_add_func ("/crank/base/128/mul/init",
					test_mulinit				);


	g_test_add_func ("/crank/base/128/add/64",
					test_add64					);

	g_test_add_func ("/crank/base/128/add/128",
					test_add					);

	g_test_add_func ("/crank/base/128/sub/64",
					test_sub64					);

	g_test_add_func ("/crank/base/128/sub/128",
					test_sub					);

	g_test_add_func ("/crank/base/128/mul/64",
					test_mul64					);

	g_test_add_func ("/crank/base/128/div/128",
					test_div					);

	g_test_add_func ("/crank/base/128/div/64",
					test_div64					);
					
	g_test_add_func ("/crank/base/128/div/32",
					test_div32					);
	g_test_add_func ("/crank/base/128/div/32/self",
					test_div32_self				);

	g_test_add_func ("/crank/base/128/shift",
				  	test_shift 					);

	g_test_run ();
	return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static void
test_addinit (void)
{
	CrankUint128	a;

	crank_uint128_init_add (&a, 0xEADE3825DEED1243, 0x7432AEEB32B369DE);

	g_assert_cmpuint (a.h, ==, 1);
	g_assert_cmpuint (a.l, ==, 0x5F10E71111A07C21);

	(crank_uint128_init_add) (&a, 0xEADE3825DEED1243, 0x7432AEEB32B369DE);

	g_assert_cmpuint (a.h, ==, 1);
	g_assert_cmpuint (a.l, ==, 0x5F10E71111A07C21);
}

static void
test_mulinit (void)
{
	CrankUint128	a;

	crank_uint128_init_mul (&a, 0xEADE3825DEED1243, 0x7432AEEB32B369DE);

	g_assert_cmpuint (a.h, ==, 0x6A9B3152F3144056);
	g_assert_cmpuint (a.l, ==, 0x2CE0B41C68EC511A);
}

static void
test_add64 (void)
{
	CrankUint128 a;
	CrankUint128 b;

	a.h = 0x0;
	a.l = 0xEADE3825DEED1243;

	crank_uint128_add64 (&a, 0x7432AEEB32B369DE, &b);

	g_assert_cmpuint (b.h, ==, 1);
	g_assert_cmpuint (b.l, ==, 0x5F10E71111A07C21);

	(crank_uint128_add64) (&a, 0x7432AEEB32B369DE, &b);

	g_assert_cmpuint (b.h, ==, 1);
	g_assert_cmpuint (b.l, ==, 0x5F10E71111A07C21);
}

static void
test_add (void)
{
	CrankUint128 a;
	CrankUint128 b;
	CrankUint128 c;

	a.h = 0xDE2398;
	a.l = 0xC52EE22003AAB200;
	b.h = 0x16AFFE7;
	b.l = 0x39B3EED3234D8891;

	crank_uint128_add (&a, &b, &c);

	g_assert_cmpuint (c.h, ==, 0x249237F);
	g_assert_cmpuint (c.l, ==, 0xFEE2D0F326F83A91);

	(crank_uint128_add) (&a, &b, &c);

	g_assert_cmpuint (c.h, ==, 0x249237F);
	g_assert_cmpuint (c.l, ==, 0xFEE2D0F326F83A91);
}

static void
test_sub64 (void)
{
	CrankUint128	a;
	CrankUint128	b;

	a.h = 0x32FF3;
	a.l = 0xB3239DEFFFE20F00;

	crank_uint128_sub64 (&a, 0xEF2293DEED39DED2, &b);

	g_assert_cmpuint (b.h, ==, 0x32FF2);
	g_assert_cmpuint (b.l, ==, 0xC4010A1112A8302E);

	(crank_uint128_sub64) (&a, 0xEF2293DEED39DED2, &b);

	g_assert_cmpuint (b.h, ==, 0x32FF2);
	g_assert_cmpuint (b.l, ==, 0xC4010A1112A8302E);
}

static void
test_sub (void)
{
	CrankUint128	a;
	CrankUint128	b;
	CrankUint128	c;

	a.h = 0x16AFFE7;
	a.l = 0x39B3EED3234D8891;
	b.h = 0xDE2398;
	b.l = 0xC52EE22003AAB200;

	crank_uint128_sub (&a, &b, &c);

	g_assert_cmpuint (c.h, ==, 0x8CDC4E);
	g_assert_cmpuint (c.l, ==, 0x74850CB31FA2D691);

	(crank_uint128_sub) (&a, &b, &c);

	g_assert_cmpuint (c.h, ==, 0x8CDC4E);
	g_assert_cmpuint (c.l, ==, 0x74850CB31FA2D691);
}

static void
test_mul64 (void)
{
	CrankUint128	a;
	CrankUint128	b;

	a.h = 0x8CDC4E;
	a.l = 0x74850CB31FA2D691;

	CrankUint128	c;
	crank_uint128_init_mul (&c, a.l, 0xFFE32234);

	g_assert_cmpuint (c.h, ==, 0x7477E932);
	g_assert_cmpuint (c.l, ==, 0x060E9FB4BF25D774);

	// a.l * 0xFFE32234 =        7477E932 060E9FB4 BF25D774
	// a.h * 0xFFE32234 = 8CCC6B DD091BD8

	crank_uint128_mul64 (&a, 0xFFE32234, &b);

	g_assert_cmpuint (b.h, ==, 0x8CCC6C5181050A);
	g_assert_cmpuint (b.l, ==, 0x060E9FB4BF25D774);
}

static void
test_div (void)
{
	CrankUint128	a;
	CrankUint128	b;
	CrankUint128	r;

	a.h =     0x7855DEEDCAC4;
	a.l = 0x999205EEDE323355;
	
	b.h =           0x492EA4;
	b.l = 0x2DB593A439DE6393;

  	crank_uint128_div (&a, &b, &r);
  	
  	g_assert_cmpuint (r.h, ==, 0);
  	g_assert_cmpuint (r.l, ==, 0x1A4F298);
}

static void
test_div64 (void)
{
	CrankUint128	a;
	CrankUint128	b;

  	a.h = 0;
  	a.l = 97;

  	crank_uint128_div64 (&a, 13, &b);

  	g_assert_cmpuint (b.h, ==, 0);
  	g_assert_cmpuint (b.l, ==, 7);

  	a.h = 0x32DE9;
 	a.l = 0x9CAAC323DEFFFE3E;

	crank_uint128_div64 (&a, 0x467DDDCF, &b);

  	g_assert_cmpuint (b.h, ==, 0);
  	g_assert_cmpuint (b.l, ==, 0xB8BD5521EDDEF);

	a.h = 0x8C213d9dLU;
	a.l = 0xa242dd2467d0b232LU;
	
	crank_uint128_div64 (&a, 5, &b);

  	g_assert_cmpuint (b.h, ==, 0x1C06A5ECLU);
  	g_assert_cmpuint (b.l, ==, 0x53A6F90747F68A0ALU);

}

static void
test_div32 (void)
{
	CrankUint128	a;
	CrankUint128	b;

  	a.h = 0;
  	a.l = 97;

  	crank_uint128_div32 (&a, 13, &b);

  	g_assert_cmpuint (b.h, ==, 0);
  	g_assert_cmpuint (b.l, ==, 7);

  	a.h = 0x32DE9;
 	a.l = 0x9CAAC323DEFFFE3E;

	crank_uint128_div32 (&a, 0x467DDDCF, &b);

  	g_assert_cmpuint (b.h, ==, 0);
  	g_assert_cmpuint (b.l, ==, 0xB8BD5521EDDEF);

	a.h = 0x8C213d9dLU;
	a.l = 0xa242dd2467d0b232LU;
	
	crank_uint128_div32 (&a, 5, &b);

  	g_assert_cmpuint (b.h, ==, 0x1C06A5ECLU);
  	g_assert_cmpuint (b.l, ==, 0x53A6F90747F68A0ALU);

}

static void
test_div32_self (void)
{
	CrankUint128	a;

  	a.h = 0;
  	a.l = 97;

  	crank_uint128_div32_self (&a, 13);

  	g_assert_cmpuint (a.h, ==, 0);
  	g_assert_cmpuint (a.l, ==, 7);

  	a.h = 0x32DE9;
 	a.l = 0x9CAAC323DEFFFE3E;

	crank_uint128_div32_self (&a, 0x467DDDCF);

  	g_assert_cmpuint (a.h, ==, 0);
  	g_assert_cmpuint (a.l, ==, 0xB8BD5521EDDEF);

	a.h = 0x8C213d9dLU;
	a.l = 0xa242dd2467d0b232LU;
	
	crank_uint128_div32_self (&a, 5);

  	g_assert_cmpuint (a.h, ==, 0x1C06A5ECLU);
  	g_assert_cmpuint (a.l, ==, 0x53A6F90747F68A0ALU);

}

static void
test_shift (void)
{
	CrankUint128	a = {0x12, 0x3456789ABCDEF000};
  	CrankUint128	b;

  	crank_uint128_lsh (&a, 8, &b);

	g_assert_cmpuint (b.h, ==, 0x1234);
	g_assert_cmpuint (b.l, ==, 0x56789ABCDEF00000);

  	crank_uint128_rsh (&b, 16, &a);

	g_assert_cmpuint (a.h, ==, 0x0);
	g_assert_cmpuint (a.l, ==, 0x123456789ABCDEF0);
	
	a.h = 0x1C06A5ECLU;
	a.l = 0x53A6F90747F68A0ALU;
	
	crank_uint128_lsh (&a, 3, &b);
	
  	g_assert_cmpuint (b.h, ==, 0xE0352F62LU);
  	g_assert_cmpuint (b.l, ==, 0x9D37C83A3FB45050LU);
}
