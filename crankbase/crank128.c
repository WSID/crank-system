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
#define CRANK_NO_C11_GENERIC_SELECTOR

#include <ctype.h>
#include <string.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbits.h"
#include "crank128.h"
/**
 * SECTION: crank128
 * @title: 128bit Unsigned Integer.
 * @short_description: An 128-bit unsigned integer.
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
 * This is [simple function][simple-function].
 */
void
(crank_uint128_init_add)    (CrankUint128 *i,
                             guint64       a,
                             guint64       b)
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
crank_uint128_init_mul (CrankUint128 *i,
                        guint64       a,
                        guint64       b)
{
  guint64 ah = a >> 32;
  guint64 al = a & 0xFFFFFFFF;
  guint64 bh = b >> 32;
  guint64 bl = b & 0xFFFFFFFF;

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
 *
 * This is [simple function][simple-function].
 */
void
(crank_uint128_copy)    (CrankUint128 *i,
                         CrankUint128 *r)
{
  r->h = i->h;    r->l = i->l;
}

/**
 * crank_uint128_inc:
 * @i: A instance.
 *
 * Increase 128-bit integer by one.
 *
 * This is [simple function][simple-function].
 */
void
(crank_uint128_inc) (CrankUint128 *i)
{
  i->l++;
  i->h += !(i->l);
}

/**
 * crank_uint128_dec:
 * @i: A instance.
 *
 * Decrease 128-bit integer by one.
 *
 * This is [simple function][simple-function].
 */
void
(crank_uint128_dec) (CrankUint128 *i)
{
  i->h -= !(i->l);
  i->l--;
}


/**
 * crank_uint128_add64:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 * @r: (out): A Result.
 *
 * Adds 64-bit integer to 128-bit integer.
 *
 * This is [simple function][simple-function].
 */
void
(crank_uint128_add64)   (CrankUint128 *a,
                         guint64       b,
                         CrankUint128 *r)
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
 * This is [simple function][simple-function].
 */
void
(crank_uint128_add64_self)  (CrankUint128 *a,
                             guint64       b)
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
 * This is [simple function][simple-function] and
 * [representative function][representative-function].
 */
void
(crank_uint128_add) (CrankUint128 *a,
                     CrankUint128 *b,
                     CrankUint128 *r)
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
 * This is [simple function][simple-function] and
 * [representative function][representative-function].
 */
void
(crank_uint128_add_self)    (CrankUint128 *a,
                             CrankUint128 *b)
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
 * This is [simple function][simple-function].
 */
void
(crank_uint128_sub64)   (CrankUint128 *a,
                         guint64       b,
                         CrankUint128 *r)
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
 * This is [simple function][simple-function].
 */
void
(crank_uint128_sub64_self)  (CrankUint128 *a,
                             guint64       b)
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
 * This is [simple function][simple-function] and
 * [representative function][representative-function].
 */
void
(crank_uint128_sub) (CrankUint128 *a,
                     CrankUint128 *b,
                     CrankUint128 *r)
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
 * This is [simple function][simple-function] and
 * [representative function][representative-function].
 */
void
(crank_uint128_sub_self)    (CrankUint128 *a,
                             CrankUint128 *b)
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
crank_uint128_mul64 (CrankUint128 *a,
                     guint64       b,
                     CrankUint128 *r)
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
crank_uint128_mul64_self (CrankUint128 *a,
                          guint64       b)
{
  CrankUint128 na;
  crank_uint128_copy (a, &na);
  crank_uint128_mul64 (&na, b, a);
}

/**
 * crank_uint128_div:
 * @a: A 128-bit integer.
 * @b: A 128-bit integer.
 * @r: (out): A Result.
 *
 * Divides 128-bit integer with 128-bit integer.
 *
 * This function is [representative function][representative-function].
 */
void
crank_uint128_div (CrankUint128 *a,
                   CrankUint128 *b,
                   CrankUint128 *r)
{

  CrankUint128 ac;
  CrankUint128 bc;
  guint64 add = 1;

  if (b->h == 0)
    crank_uint128_div64 (a, b->l, r);
  else
    {
      r->h = 0;
      r->l = 0;

      crank_uint128_copy (a, &ac);
      crank_uint128_copy (b, &bc);

      // Shifts to left!
      guint sha = crank_bits_shift_to_left64 (&(bc.h));
      bc.h |= (bc.l >> (64 - sha));
      bc.l <<= sha;
      add <<= sha;


      while (add)
        {
          if ((bc.h < ac.h) || ((bc.h == ac.h) && (bc.l <= ac.l)))
            {
              crank_uint128_sub_self (&ac, &bc);
              r->l |= add;
            }
          crank_uint128_rsh_self (&bc, 1);
          add >>= 1;
        }
    }
}

/**
 * crank_uint128_div_self:
 * @a: A 128-bit integer.
 * @b: A 128-bit integer.
 *
 * Divides 128-bit integer with 128-bit integer.
 *
 * This function is [representative function][representative-function].
 */
void
crank_uint128_div_self (CrankUint128 *a,
                        CrankUint128 *b)
{

  CrankUint128 ac;
  CrankUint128 bc;
  guint64 add = 1;

  if (b->h == 0)
    crank_uint128_div64_self (a, b->l);
  else
    {
      crank_uint128_copy (a, &ac);
      crank_uint128_copy (b, &bc);

      a->h = 0;
      a->l = 0;

      // Shifts to left!
      guint sha = crank_bits_shift_to_left64 (&(bc.h));
      bc.h |= (bc.l >> (64 - sha));
      bc.l <<= sha;
      add <<= sha;


      while (add)
        {
          if ((bc.h < ac.h) || ((bc.h == ac.h) && (bc.l <= ac.l)))
            {
              crank_uint128_sub_self (&ac, &bc);
              a->l |= add;
            }
          crank_uint128_rsh_self (&bc, 1);
          add >>= 1;
        }
    }
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
crank_uint128_div64 (CrankUint128 *a,
                     guint64       b,
                     CrankUint128 *r)
{

  CrankUint128 ac;
  guint64 add;

  // Initial calculation.

  r->h = a->h / b;
  ac.h = a->h % b;

  r->l = 0;
  ac.l = a->l;

  // Shift right and subtract.
  add = 0x8000000000000000LU;
  crank_uint128_lsh_self (&ac, 1);
  while (add)
    {
      if (b <= ac.h)
        {
          ac.h -= b;
          r->l |= add;
        }

      crank_uint128_lsh_self (&ac, 1);
      add >>= 1;
    }
}


/**
 * crank_uint128_div64_self:
 * @a: A 128-bit integer.
 * @b: A 64-bit integer.
 *
 * Divides 128-bit integer with 64-bit integer.
 */
void
crank_uint128_div64_self (CrankUint128 *a,
                          guint64       b)
{

  CrankUint128 ac;
  guint64 add;

  // Initial calculation.

  ac.h = a->h % b;
  a->h = a->h / b;

  ac.l = a->l;
  a->l = 0;

  // Shift right and subtract.
  add = 0x8000000000000000LU;
  crank_uint128_lsh_self (&ac, 1);
  while (add)
    {
      if (b <= ac.h)
        {
          ac.h -= b;
          a->l |= add;
        }

      crank_uint128_lsh_self (&ac, 1);
      add >>= 1;
    }
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
crank_uint128_div32 (CrankUint128 *a,
                     guint32       b,
                     CrankUint128 *r)
{
  // this is about modular.
  guint64 mod64;
  guint64 q64;

  CrankUint128 ap = {0, 0};
  CrankUint128 ac = {0, 0};

  guint64 hr;
  guint64 lr;

  guint64 hrr;

  // Performs division on (2^64 - 1)
  mod64 = 0xFFFFFFFFFFFFFFFF % b;
  q64 = 0xFFFFFFFFFFFFFFFF / b;

  // Make results of (2^64 /% b) from ((2^64 - 1) /% b).
  mod64++;
  if (mod64 == b)
    {
      mod64 = 0;
      q64++;
    }

  r->h = a->h / b;
  r->l = a->l / b;

  hr = a->h % b;
  lr = a->l % b;

  hrr = mod64 * hr + lr;

  crank_uint128_add64_self (r, q64 * hr);
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
crank_uint128_div32_self (CrankUint128 *a,
                          guint32       b)
{
  // this is about modular.
  guint64 mod64;
  guint64 q64;

  CrankUint128 ap = {0, 0};
  CrankUint128 ac = {0, 0};

  guint64 hr;
  guint64 lr;

  guint64 hrr;

  // Performs division on (2^64 - 1)
  mod64 = 0xFFFFFFFFFFFFFFFF % b;
  q64 = 0xFFFFFFFFFFFFFFFF / b;

  // Make results of (2^64 /% b) from ((2^64 - 1) /% b).
  mod64++;
  if (mod64 == b)
    {
      mod64 = 0;
      q64++;
    }

  hr = a->h % b;
  lr = a->l % b;

  a->h = a->h / b;
  a->l = a->l / b;

  hrr = mod64 * hr + lr;

  crank_uint128_add64_self (a, q64 * hr);
  crank_uint128_add64_self (a, hrr / b);
}

/**
 * crank_uint128_remquo32:
 * @a: A 128-bit integer.
 * @b: A 32-bit integer.
 * @q: (out): A Quotient.
 * @r: (out): A Reminder.
 *
 * Divides 128-bit integer by 32-bit integer.
 *
 * As it does not worry about overflowing remainer, it is much faster than
 * 64-bit version.
 */
void
crank_uint128_remquo32 (CrankUint128 *a,
                        guint32       b,
                        CrankUint128 *q,
                        guint32      *r)
{
  // this is about modular.
  guint64 mod64;
  guint64 q64;

  guint64 hr;
  guint64 lr;

  guint64 hrr;

  // Performs division on (2^64 - 1)
  mod64 = 0xFFFFFFFFFFFFFFFF % b;
  q64 = 0xFFFFFFFFFFFFFFFF / b;

  // Make results of (2^64 /% b) from ((2^64 - 1) /% b).
  mod64++;
  if (mod64 == b)
    {
      mod64 = 0;
      q64++;
    }

  q->h = a->h / b;
  q->l = a->l / b;

  hr = a->h % b;
  lr = a->l % b;

  hrr = mod64 * hr + lr;

  crank_uint128_add64_self (q, q64 * hr);
  crank_uint128_add64_self (q, hrr / b);
  *r = hrr % b;
}

/**
 * crank_uint128_remquo32_self:
 * @a: A 128-bit integer.
 * @b: A 32-bit integer.
 * @r: (out): A Reminder.
 *
 * Divides 128-bit integer by 32-bit integer.
 *
 * As it does not worry about overflowing remainer, it is much faster than
 * 64-bit version.
 */
void
crank_uint128_remquo32_self (CrankUint128 *a,
                             guint32       b,
                             guint32      *r)
{
  // this is about modular.
  guint64 mod64;
  guint64 q64;

  CrankUint128 ap = {0, 0};
  CrankUint128 ac = {0, 0};

  guint64 hr;
  guint64 lr;

  guint64 hrr;

  // Performs division on (2^64 - 1)
  mod64 = 0xFFFFFFFFFFFFFFFF % b;
  q64 = 0xFFFFFFFFFFFFFFFF / b;

  // Make results of (2^64 /% b) from ((2^64 - 1) /% b).
  mod64++;
  if (mod64 == b)
    {
      mod64 = 0;
      q64++;
    }

  hr = a->h % b;
  lr = a->l % b;

  a->h = a->h / b;
  a->l = a->l / b;

  hrr = mod64 * hr + lr;

  crank_uint128_add64_self (a, q64 * hr);
  crank_uint128_add64_self (a, hrr / b);
  *r = hrr % b;
}

/**
 * crank_uint128_lsh:
 * @a: A 128-bit integer.
 * @b: Shift amount.
 * @r: (out): A Result.
 *
 * Shifts a integer.
 *
 * This is [simple function][simple-function].
 */
void
(crank_uint128_lsh) (CrankUint128 *a,
                     const guint   b,
                     CrankUint128 *r)
{
  r->h = (a->h << b) | (a->l >> (64 - b));
  r->l = (a->l << b);
}

/**
 * crank_uint128_lsh_self:
 * @a: A 128-bit integer.
 * @b: Shift amount.
 *
 * Shifts a integer.
 *
 * This is [simple function][simple-function].
 */
void
(crank_uint128_lsh_self) (CrankUint128 *a,
                          const guint   b)
{
  a->h = (a->h << b) | (a->l >> (64 - b));
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
 * This is [simple function][simple-function].
 */
void
(crank_uint128_rsh) (CrankUint128 *a,
                     const guint   b,
                     CrankUint128 *r)
{
  r->h = a->h >> b;
  r->l = (a->h << (64 - b)) | (a->l >> b);
}

/**
 * crank_uint128_rsh_self:
 * @a: A 128-bit integer.
 * @b: Shift amount.
 *
 * Shifts a integer.
 *
 * This is [simple function][simple-function].
 */
void
(crank_uint128_rsh_self) (CrankUint128 *a,
                          const guint   b)
{
  a->l = (a->h << (64 - b)) | (a->l >> b);
  a->h >>= a->h;
}
