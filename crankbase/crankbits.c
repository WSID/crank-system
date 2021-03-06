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

#include "crankbits.h"
/**
 * SECTION: crankbits
 * @title: Bit Manipulation Utility.
 * @short_description: Bit manipulation.
 * @stability: unstable
 * @include: crankbase.h
 *
 * Programmers don't have to manipulate bits, in recent days. Because of
 * increased memory space and automatic optimizations done by compilers.
 *
 * But sometimes, low level bit manipulation is done, for implementing little
 * bit complex data structures.
 */

/**
 * crank_bits_shift_to_left32:
 * @subject: (inout): A integer to shift.
 *
 * Shifts @subject till most significant bit become 1.
 *
 * If @subject is 0, it returns 32.
 */
guint
crank_bits_shift_to_left32 (guint32 *subject)
{
  guint result = 0;
  guint32 msubject = *subject;

  if (msubject == 0)
    return 32;

  if ((msubject & 0xFFFF0000) == 0)
    {
      result += 16;
      msubject <<= 16;
    }

  if ((msubject & 0xFF000000) == 0)
    {
      result += 8;
      msubject <<= 8;
    }

  if ((msubject & 0xF0000000) == 0)
    {
      result += 4;
      msubject <<= 4;
    }

  if ((msubject & 0xC0000000) == 0)
    {
      result += 2;
      msubject <<= 2;
    }

  if ((msubject & 0x80000000) == 0)
    {
      result += 1;
      msubject <<= 1;
    }

  *subject = msubject;
  return result;
}

/**
 * crank_bits_shift_to_left64:
 * @subject: (inout): A integer to shift.
 *
 * Shifts @subject till most significant bit become 1.
 *
 * If @subject is 0, it returns 64.
 */
guint
crank_bits_shift_to_left64 (guint64 *subject)
{
  guint result = 0;
  guint64 msubject = *subject;

  if (msubject == 0)
    return 64;

  if ((msubject & 0xFFFFFFFF00000000) == 0)
    {
      result += 32;
      msubject <<= 32;
    }

  if ((msubject & 0xFFFF000000000000) == 0)
    {
      result += 16;
      msubject <<= 16;
    }

  if ((msubject & 0xFF00000000000000) == 0)
    {
      result += 8;
      msubject <<= 8;
    }

  if ((msubject & 0xF000000000000000) == 0)
    {
      result += 4;
      msubject <<= 4;
    }

  if ((msubject & 0xC000000000000000) == 0)
    {
      result += 2;
      msubject <<= 2;
    }

  if ((msubject & 0x8000000000000000) == 0)
    {
      result += 1;
      msubject <<= 1;
    }

  *subject = msubject;
  return result;
}

/**
 * crank_bits_remquo_2_64:
 * @divisor: A divisor
 * @remainder: (out): A Remainder
 *
 * divide 2<superscript>64</superscript> by given @divisor.
 *
 * Returns: Quotient of this division.
 */
guint64
crank_bits_remquo_2_64 (guint64  divisor,
                        guint64 *remainder)
{
  guint64 mquotient;
  guint64 mremainder;
  gboolean muptake;

  mquotient = 0xFFFFFFFFFFFFFFFFLU / divisor;
  mremainder = 0xFFFFFFFFFFFFFFFFLU % divisor;

  mremainder++;
  muptake = (mremainder == divisor);

  mquotient += (guint)muptake;
  mremainder = (muptake) ? 0 : mremainder;

  *remainder = mremainder;
  return mquotient;
}

/**
 * crank_bits_least_pow2_32:
 * @number: A Number.
 *
 * Returns least power of 2 which is bigger than @number.
 * If @number is %G_MAXUINT32, 0 will be returned. This is due to shifting
 * overflow.
 *
 * Returns: Power of 2 which is bigger than @number, or 0 if @number is
 *     %G_MAXUINT32.
 */
guint32
crank_bits_least_pow2_32 (const guint32 number)
{
  guint32 value = 0x00010000;

  value = (value > number) ? (value >> 8) : (value << 8);
  value = (value > number) ? (value >> 4) : (value << 4);
  value = (value > number) ? (value >> 2) : (value << 2);
  value = (value > number) ? (value >> 1) : (value << 1);
  value = (value > number) ? (value >> 1) : (value << 1);
  return (value == number) ? (value << 1) : (value);
}

/**
 * crank_bits_least_pow2_64:
 * @number: A Number.
 *
 * Returns least power of 2 which is bigger than @number.
 * If @number is %G_MAXUINT64, 0 will be returned. This is due to shifting
 * overflow.
 *
 * Returns: Power of 2 which is bigger than @number.
 */
guint64
crank_bits_least_pow2_64 (const guint64 number)
{
  guint64 value = 0x0000000100000000;

  value = (value > number) ? (value >> 16) : (value << 16);
  value = (value > number) ? (value >> 8) : (value << 8);
  value = (value > number) ? (value >> 4) : (value << 4);
  value = (value > number) ? (value >> 2) : (value << 2);
  value = (value > number) ? (value >> 1) : (value << 1);
  value = (value > number) ? (value >> 1) : (value << 1);
  return (value == number) ? (value << 1) : (value);
}
