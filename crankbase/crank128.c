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

#define _CRANKBASE_INSIDE

#include <ctype.h>
#include <string.h>

#include <glib.h>
#include <glib-object.h>

#include "crank128.h"
/**
 * SECTION: crank128
 * @title: Operations on 128-bit.
 * @short_description: An 128-bit integer.
 *
 * 128-bit integers are not used frequently. As most of operations are done by
 * multiple 64-bit operations, they are much slower than 64-bit ones.
 *
 * Sometimes, 128-bit operations are needed. For this, crank system provides
 * simple implementation of these operations.
 */


/**
 * crank_uint128_init_add:
 * @i: (out): Instance to initialize.
 * @a: a 64-bit int.
 * @b: a 64-bit int.
 *
 * Initialize 128 from sum of 64-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_init_add)	(CrankUint128*	i,
							 guint64		a,
							 guint64		b	)
{
	i->h = CRANK_ADD_CARRY64 (a, b, &(i->l));
}


/**
 * crank_uint128_init_mul:
 * @i: (out): Instance to initialize.
 * @a: a 64-bit int.
 * @b: a 64-bit int.
 *
 * Initialize 128 from product of 64-bit integer.
 */
void
crank_uint128_init_mul	(CrankUint128*	i,
						 guint64		a,
						 guint64		b	)
{
	guint64 ah = a >> 32;
	guint64	al = a & 0xFFFFFFFF;
	guint64 bh = b >> 32;
	guint64	bl = b & 0xFFFFFFFF;

	guint64 m1;
	guint64 m2;

	i->h = ah * bh;
	m1 = ah * bl;
	m2 = al * bh;
	i->l = al * bl;

	i->h += ((guint64)CRANK_IADD_CARRY64(&m1, m2)) << 32;
	i->h += m1 >> 32;

	m2 = m1 << 32;
	i->h += CRANK_IADD_CARRY64(&(i->l), m2);
}


/**
 * crank_uint128_copy:
 * @i: A instance.
 * @r: (out): A instance.
 *
 * Copys a 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_copy)	(CrankUint128*	i,
						 CrankUint128*	r	)
{
	r->h = i->h;	r->l = i->l;
}


/**
 * crank_uint128_add64:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 * @r: (out): A Result.
 *
 * Adds 64-bit integer to 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_add64)	(CrankUint128*	a,
						 guint64		b,
						 CrankUint128*	r	)
{
	r->h = a->h + CRANK_ADD_CARRY64(a->l, b, &(r->l));
}

/**
 * crank_uint128_add64_self:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 *
 * Adds 64-bit integer to 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_add64_self)	(CrankUint128*	a,
							 guint64		b	)
{
	a->h += CRANK_IADD_CARRY64(&(a->l), b);
}

/**
 * crank_uint128_add:
 * @a: A 128-bit integer.
 * @b: A 128-bit integer.
 * @r: (out): A Result.
 *
 * Adds 128-bit integer to 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_add)	(CrankUint128*	a,
					 CrankUint128*	b,
					 CrankUint128*	r	)
{
	r->h = a->h + b->h + CRANK_ADD_CARRY64(a->l, b->l, &(r->l));
}

/**
 * crank_uint128_add_self:
 * @a: A 128-bit integer.
 * @b: A 128-bit integer.
 *
 * Adds 128-bit integer to 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_add_self)	(CrankUint128*	a,
							 CrankUint128*	b	)
{
	a->h += b->h;
	a->h += CRANK_IADD_CARRY64(&(a->l), b->l);
}

/**
 * crank_uint128_sub64:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 * @r: (out): A Result.
 *
 * Subtracts 64-bit integer from 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_sub64)	(CrankUint128*	a,
						 guint64		b,
						 CrankUint128*	r	)
{
	r->h = a->h - CRANK_SUB_CARRY64(a->l, b, &(r->l));
}

/**
 * crank_uint128_sub64_self:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 *
 * Subtracts 64-bit integer from 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_sub64_self)	(CrankUint128*	a,
							 guint64		b	)
{
	a->h -= (a->l < b);
	a->l -= b;
}

/**
 * crank_uint128_sub:
 * @a: A 128-bit integer.
 * @b: A 128-bit integer.
 * @r: (out): A Result.
 *
 * Subtracts 128-bit integer from 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_sub)	(CrankUint128*	a,
					 CrankUint128*	b,
					 CrankUint128*	r	)
{
	r->h = a->h - b->h - CRANK_SUB_CARRY64(a->l, b->l, &(r->l));
}

/**
 * crank_uint128_sub_self:
 * @a: A 128-bit integer.
 * @b: A 128-bit integer.
 *
 * Subtracts 128-bit integer from 128-bit integer.
 *
 * This is simple function.
 */
void
(crank_uint128_sub_self)	(CrankUint128*	a,
							 CrankUint128*	b	)
{
	a->h -= b->h + ((a->l) < (b->l));
	a->l -= b->l;
}


/**
 * crank_uint128_mul64:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 * @r: (out): A Result.
 *
 * Multiplies 64-bit integer to 128-bit integer.
 */
void
crank_uint128_mul64	(CrankUint128*	a,
					 guint64		b,
					 CrankUint128*	r	)
{
	crank_uint128_init_mul (r, a->l, b);
	r->h += a->h * b;
}

/**
 * crank_uint128_mul64_self:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 *
 * Multiplies 64-bit integer to 128-bit integer.
 */
void
crank_uint128_mul64_self	(CrankUint128*	a,
							 guint64		b	)
{
  	CrankUint128	na;
  	crank_uint128_copy (a, &na);
  	crank_uint128_mul64 (&na, b, a);
}

/**
 * crank_uint128_div64:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 * @r: (out): A Result.
 *
 * Divides 128-bit integer with 64-bit integer.
 */
void
crank_uint128_div64	(CrankUint128*	a,
					 guint64		b,
					 CrankUint128*	r)
{
	// this is about modular.
	guint64 		mod64;
	guint64			q64;

  	CrankUint128	ap = {0, 0};
  	CrankUint128	ac = {0, 0};

	// Performs division on (2^64 - 1)
	mod64 = 0xFFFFFFFFFFFFFFFF % b;
	q64 = 0xFFFFFFFFFFFFFFFF / b;

	// Make results of (2^64 /% b) from ((2^64 - 1) /% b).
	mod64++;
	if (mod64 == b) {
		mod64 = 0;
		q64++;
	}

	// Initial calculation.
	r->h = a->h / b;
  	ac.h = a->h % b;

  	r->l = 0;
  	ac.l = a->l;

  	// Iterative calculation.
	// continuously retrieve reminder by, until a_next come in 64-bit range.
	//
	//   a_next = a_h * 64_reminder + a_l_reminder.
	//   q += a_h * 64_quotient + a_l_quotient.
	//

  	while (ac.h != 0) {
		guint64	lr = ac.l % b;
	  	guint64	lq = ac.l / b;

	  	crank_uint128_copy (&ac, &ap);

		crank_uint128_init_mul (&ac, ap.h, mod64);
	  	crank_uint128_add64_self (&ac, lr);

	  	crank_uint128_add64_self (r, ap.h * q64);
	  	crank_uint128_add64_self (r, lq);
	}

  	crank_uint128_add64_self (r, ac.l / b);
}


/**
 * crank_uint128_div64_self:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 *
 * Divides 128-bit integer with 64-bit integer.
 */
void
crank_uint128_div64_self	(CrankUint128*	a,
							 guint64		b)
{
	// this is about modular.
	guint64 		mod64;
	guint64			q64;

  	CrankUint128	ap = {0, 0};
  	CrankUint128	ac = {0, 0};

	// Performs division on (2^64 - 1)
	mod64 = 0xFFFFFFFFFFFFFFFF % b;
	q64 = 0xFFFFFFFFFFFFFFFF / b;

	// Make results of (2^64 /% b) from ((2^64 - 1) /% b).
	mod64++;
	if (mod64 == b) {
		mod64 = 0;
		q64++;
	}

	// Initial calculation.
  	ac.h = a->h % b;
	a->h /= a->h / b;

  	ac.l = a->l;
  	a->l = 0;

  	// Iterative calculation.
	// continuously retrieve reminder by, until a_next come in 64-bit range.
	//
	//   a_next = a_h * 64_reminder + a_l_reminder.
	//   q += a_h * 64_quotient + a_l_quotient.
	//

  	while (ac.h != 0) {
		guint64	lr = ac.l % b;
	  	guint64	lq = ac.l / b;

	  	crank_uint128_copy (&ac, &ap);

		crank_uint128_init_mul (&ac, ap.h, mod64);
	  	crank_uint128_add64_self (&ac, lr);

	  	crank_uint128_add64_self (a, ap.h * q64);
	  	crank_uint128_add64_self (a, lq);
	}

  	crank_uint128_add64_self (a, ac.l / b);
}

/**
 * crank_uint128_div32:
 * @a: A 128-bit integer.
 * @b: A 32-bit integer.
 * @r: (out): A Result.
 *
 * Divides 128-bit integer by 32-bit integer.
 *
 * As it does not worry about overflowing remainer, it is much faster than
 * 64-bit version.
 */
void
crank_uint128_div32 (CrankUint128*	a,
					 guint32		b,
					 CrankUint128*	r)
{
	// this is about modular.
	guint64 		mod64;
	guint64			q64;

  	CrankUint128	ap = {0, 0};
  	CrankUint128	ac = {0, 0};

	guint64			hr;
  	guint64			lr;

  	guint64			hrr;

	// Performs division on (2^64 - 1)
	mod64 = 0xFFFFFFFFFFFFFFFF % b;
	q64 = 0xFFFFFFFFFFFFFFFF / b;

	// Make results of (2^64 /% b) from ((2^64 - 1) /% b).
	mod64++;
	if (mod64 == b) {
		mod64 = 0;
		q64++;
	}

  	r->h = a->h / b;
  	r->l = a->l / b;

  	hr = a->h % b;
  	lr = a->l % b;

	hrr = mod64 * hr + lr;

  	crank_uint128_add64_self (r, hrr / b);
}

/**
 * crank_uint128_div32_self:
 * @a: A 128-bit integer.
 * @b: A 32-bit integer.
 *
 * Divides 128-bit integer by 32-bit integer.
 *
 * As it does not worry about overflowing remainer, it is much faster than
 * 64-bit version.
 */
void
crank_uint128_div32_self (CrankUint128*	a,
						 guint32		b)
{
	// this is about modular.
	guint64 		mod64;
	guint64			q64;

  	CrankUint128	ap = {0, 0};
  	CrankUint128	ac = {0, 0};

	guint64			hr;
  	guint64			lr;

  	guint64			hrr;

	// Performs division on (2^64 - 1)
	mod64 = 0xFFFFFFFFFFFFFFFF % b;
	q64 = 0xFFFFFFFFFFFFFFFF / b;

	// Make results of (2^64 /% b) from ((2^64 - 1) /% b).
	mod64++;
	if (mod64 == b) {
		mod64 = 0;
		q64++;
	}

  	hr = a->h % b;
  	lr = a->l % b;

  	a->h = a->h / b;
  	a->l = a->l / b;

	hrr = mod64 * hr + lr;

  	crank_uint128_add64_self (a, hrr / b);
}

/**
 * crank_uint128_lsh:
 * @a: A 128-bit integer.
 * @b: Shift amount.
 * @r: (out): A Result.
 *
 * Shifts a integer.
 *
 * This is simple function.
 */
void
(crank_uint128_lsh) (	CrankUint128*	a,
						const guint		b,
						CrankUint128*	r	)
{
	r->h = (a->h << b) | (a->l >> (64-b));
	r->l = (a->l << b);
}

/**
 * crank_uint128_lsh_self:
 * @a: A 128-bit integer.
 * @b: Shift amount.
 *
 * Shifts a integer.
 *
 * This is simple function.
 */
void
(crank_uint128_lsh_self) (	CrankUint128*	a,
							const guint		b	)
{
	a->h = (a->h << b) | (a->l >> (64-b));
	a->l <<= b;
}

/**
 * crank_uint128_rsh:
 * @a: A 128-bit integer.
 * @b: Shift amount.
 * @r: (out): A Result.
 *
 * Shifts a integer.
 *
 * This is simple function.
 */
void
(crank_uint128_rsh) (	CrankUint128*	a,
						const guint		b,
						CrankUint128*	r	)
{
	r->h = a->h >> b;
	r->l = (a->h << (64-b)) | (a->l >> b);
}

/**
 * crank_uint128_rsh_self:
 * @a: A 128-bit integer.
 * @b: Shift amount.
 *
 * Shifts a integer.
 *
 * This is simple function.
 */
void
(crank_uint128_rsh_self) (	CrankUint128*	a,
							const guint		b	)
{
	a->l = (a->h << (64-b)) | (a->l >> b);
	a->h >>= a->h;
}
