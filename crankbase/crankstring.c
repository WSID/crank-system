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
#include <math.h>

#include <glib.h>
#include <glib-object.h>

#define _CRANKBASE_INSIDE

#include "crank128.h"
#include "crankstring.h"

/**
 * SECTION: crankstring
 * @title: Simple String Reading
 * @short_description: Utility for String read and manipulation.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * The functions provides simple function to read data from string.
 *
 * Note that this functions provides only for basic functions, and not capable
 * to perform complex parsing like JSON or etc.
 *
 * If possible, when using other language like python, use their own string
 * functions rather than using this functions.
 *
 * # Reading string.
 *
 * crankbase.h has simple functions to read string and retrieve their value.
 * Currently, these functions are in 3 groups.
 *
 *
 * 1. read family.
 *
 *    The function reads string in given position. read and scan families
 *    returns gboolean for iterated processing. Actual values are returned
 *    through out parameters.
 *
 *    Eg: Reading/scanning name of entry.
 *
 *    |[ <-- language="C" --!>
 *        gboolean      read_[something] (  const gchar* str,
 *                                          guint* pos,
 *                                          something* stn
 *                                          [, additional item per function]);
 *    ]|
 *
 *    They can be used like this.
 *    |[ <-- language="C" --!>
 *        crank_str_read_space (str, &i, NULL);
 *        if (! crank_str_read_word (str, &i, &amp;word_a)) return NULL;
 *
 *        crank_str_read_space (str, &i, NULL);
 *        if (! crank_str_read_word (str, &i, &word_b)) {
 *            g_free (word_a);
 *            return NULL;
 *        }
 *        ....
 *    ]|
 *
 * 2. scan family.
 *
 *    These functions skips spaces before reading string.
 *    |[ <-- language="C" --!>
 *        gboolean      scan_[something] (  const gchar* str,
 *                                          guint* pos,
 *                                          something* stn
 *                                          [, additional item per function]);
 *    ]|
 *
 *    They can be used like this.
 *    |[ <-- language="C" --!>
 *        if (! crank_str_scan_word (str, &i, &word_a)) return NULL;
 *
 *        if (! crank_str_scan_word (str, &i, &word_b)) {
 *            g_free (word_a);
 *            return NULL;
 *        }
 *        ....
 *    ]|
 *
 * 3. check family
 *
 *    The functions will check that certain item is on the string. It skips
 *    spaces before reading.
 *    Some function might return other type rather than #gboolean, if it checks
 *    multiple items.
 *
 *    Eg: Checking for some symbols.

 *    |[ <-- language="C" --!>
 *        gboolean      check_[something] ( const gchar* str,
 *                                          guint* pos,
 *                                          something stn
 *                                          [, additional item per function]);
 *
 *        gint          check_[something]s (const gchar* str,
 *                                          guint* pos,
 *                                          something* stn,
 *                                          guint nstn
 *                                          [, additional item per function]);
 *
 *        ....
 *    ]|
 */

#define MASK_32 G_GUINT64_CONSTANT(0xFFFFFFFF)

#define DEC18 G_GUINT64_CONSTANT(1000000000000000000)

#define PEN16 0x2386F26FC1UL
#define PEN8  0x5F5E1
#define PEN4  0x271
#define PEN2  0x19

#define PEN16_BIT   38
#define PEN8_BIT    19
#define PEN4_BIT    10
#define PEN2_BIT    5
#define PEN1_BIT    3

#define I64_D10 G_GUINT64_CONSTANT(1844674407370955161)
#define I64_R10 6
#define I64_N10 20

#define I63     G_GUINT64_CONSTANT(9223372036854775807)
#define I63N    G_GUINT64_CONSTANT(9223372036854775808)

#define I64_D5      G_GUINT64_CONSTANT(3689348814741910323)
#define I64_D5_2    G_GUINT64_CONSTANT(737869762948382064)
#define I64_D5_4    G_GUINT64_CONSTANT(29514790517935282)
#define I64_D5_8    G_GUINT64_CONSTANT(47223664828696)
#define I64_D5_16   G_GUINT64_CONSTANT(120892581)

#define FLT_EBIT    (8)
#define FLT_MBIT    (23)
#define FLT_BIAS    (127)

#define DBL_EBIT    (11)
#define DBL_MBIT    (52)
#define DBL_BIAS    (1023)

#define DBL_EMIN    (-1022)
#define DBL_EMAX    (1023)
#define DBL_EDNORM  (-1074)

#define DBL_DEMIN   (-308)
#define DBL_DEMAX   (308)
#define DBL_DEDNORM (-323)

static gchar *float_symwords [] =
{
  "inf",
  "infinity",
  "nan",
  NULL
};



static gboolean
crank_str_g_isalnum (const gchar value,
                     gpointer    userdata)
{
  return g_ascii_isalnum (value);
  // That function is 'macro', so it cannot used as function.
}

static gboolean
crank_str_is_canonical_char (const gchar value,
                             gpointer    userdata)
{
  return g_ascii_isalnum (value) || (value == '-');
}



static guint
crank_str_shift128_to_left (CrankUint128 *subject)
{
  guint result = 0;
  guint64 nsubject = 0;

  if (subject->h == 0)
    {
      result = 64 + crank_bits_shift_to_left64(&(subject->l));

      subject->h = subject->l;
      subject->l = 0;
    }
  else
    {
      result = crank_bits_shift_to_left64(&(subject->h));

      subject->h |= (subject->l) >> (64 - result);
      subject->l <<= result;
    }

  return result;
}

static gboolean
crank_str_read_decstring (const gchar *str,
                          guint       *position,
                          guint        n_numbox,
                          gchar       *numbox,
                          guint       *eend,
                          gint        *dp,
                          gint64      *expon)
{
  gint bi;      //number box iteration
  bi = 0;

  guint i;
  gint dp_pp = 0;

  guint ss;
  guint se;
  guint sd;
  guint ee;
  //// Phase 1: Check effective range.
  // Read leading zeros.
  for (i = *position; str[i] == '0'; i++) {}
  if (str[i] == '.')
    {
      dp_pp = 1;
      sd = i;
      for (i++; str[i] == '0'; i++) {}
    }

  // Read numbers.
  ss = i;
  for (; isdigit (str[i]); i++) {}
  if ((str[i] == '.') && (dp_pp == 0))
    {
      dp_pp = 2;
      sd = i;
      for (i++; isdigit (str[i]); i++) {}
    }

  // If decimal point is not found, think decimal point is at end of numbers.
  if (dp_pp == 0)
    sd = i;

  // Trace back numbers.
  if (ss < i)
    {
      for (se = i - 1; str[se] == '0'; se--) {}
      if (str[se] == '.')
        {
          for (se--; str[se] == '0'; se--) {}
          dp_pp = 3;
        }
      se++;
    }
  else
    se = ss;

  // Read exponential
  if (str[i] == 'e' || str[i] == 'E')
    {
      ee = i + 1;
      if (!crank_str_read_int64 (str, &ee, expon, NULL))
        ee--;
    }
  else
    ee = i;


  //// Phase 2: Fill numbox.
  if (dp_pp == 2)
    {
      guint nd = (sd <= ss + n_numbox) ? sd : ss + n_numbox;
      guint ne = (se <= ss + n_numbox + 1) ? se : ss + n_numbox + 1;

      for (i = ss; i < nd; i++)
        numbox[bi++] = str[i];
      for (i = sd + 1; i < ne; i++)
        numbox[bi++] = str[i];
    }
  else
    {
      guint ne = (se < ss + n_numbox) ? se : ss + n_numbox;
      for (i = ss; i < ne; i++)
        numbox[bi++] = str[i];
    }


  //// Phase 3: Fill out information.
  *eend = se - ss - (guint)(dp_pp == 2);
  *dp = (gint)(sd) - (gint)(ss) + (gint)(sd < ss);

  if (*position != ee)
    {
      *position = ee;
      return TRUE;
    }

  return FALSE;

}


static gdouble
crank_str_build_double_norm (const gboolean sign,
                             const gint     exp,
                             const guint64  mantissa)
{
  guint64 mantissa_shift = mantissa >> 11;
  guint64 mantissa_rest = 0x7FFLU & mantissa;
  gint nexp = exp;

  union {
    gdouble value;
    guint64 bits;
  } result;

  // Round it up
  // This is middle case: round to even
  if (mantissa_rest == 0x400LU)
    {
      if (mantissa_shift % 2 == 1)
        mantissa_shift++;
    }
  else if (mantissa_rest > 0x400LU)
    {
      mantissa_shift++;
    }

  // If rounding caused exponential increase.
  if (0x20000000000000LU <= mantissa_shift)
    {
      mantissa_shift >>= 1;
      nexp++;
    }

  result.bits =   ((guint)sign << 31) |
                ((0x7FF00000) & ((nexp + DBL_BIAS) << 20));

  result.bits =   (result.bits << 32) |
                (0xFFFFFFFFFFFFFLU & mantissa_shift);

  return result.value;
}

static gdouble
crank_str_build_double_denorm (const gboolean sign,
                               const gint     exp,
                               const guint64  mantissa)
{
  guint sha = DBL_BIAS - exp + 14;
  guint64 mantissa_shift = mantissa >> sha;
  guint64 mantissa_rest = mantissa << sha;

  union {
    gdouble value;
    guint64 bits;
  } result;

  // Round it up
  if (mantissa_rest == 0x8000000000000000LU)
    {
      if (mantissa_shift % 2 == 1)
        mantissa_shift++;
    }
  else if (mantissa_rest > 0x8000000000000000LU)
    {
      mantissa_shift++;
    }

  // We don't care adout exponential increase, as it is denormalized doubles.

  result.bits = (guint)sign;
  result.bits = (result.bits << 63) | mantissa_shift;

  return result.value;
}


/**
 * crank_str_read_space:
 * @str: string to read.
 * @position: (inout): position.
 * @space: (out) (optional): count of space characters.
 *
 * Reads @str for space and moves @position into the non-space character.
 *
 * Returns: %TRUE if there is a space.
 */
gboolean
crank_str_read_space (const gchar *str,
                      guint       *position,
                      guint       *space)
{
  guint i_start;
  guint i;

  i_start = *position;

  for (i = i_start; g_ascii_isspace (str[i]); i++) {}

  if (space != NULL)
    *space = i - i_start;

  *position = i;
  return (i != i_start);
}

/**
 * crank_str_read_plusminus:
 * @str: string to read.
 * @position: (inout): position.
 * @negate: (out): Whether it read minus. If it cannot read, %FALSE is returned.
 *
 * Reads '+' or '-' within @str and move @position if is.
 *
 * This is used to implement numeric reading function.
 *
 * Returns: %TRUE if it read a sign.
 */
gboolean
crank_str_read_plusminus (const gchar *str,
                          guint       *position,
                          gboolean    *negate)
{
  gchar c = str[*position];
  gboolean mnegate;

  switch (c)
    {
    case '+':
      mnegate = FALSE;
      break;

    case '-':
      mnegate = TRUE;
      break;

    default:
      if (negate != NULL)
        *negate = FALSE;
      return FALSE;
    }

  (*position)++;
  crank_str_read_space (str, position, NULL);

  if (negate != NULL)
    *negate = mnegate;
  return TRUE;
}

/**
 * crank_str_read_string:
 * @str: string to read
 * @position: (inout): position
 * @str_ptr: (nullable) (optional) (out): Read string. If it cannot read, %NULL
 *     will be returned.
 * @func: (scope call): A function to determine to read or stop.
 * @userdata: (closure): Userdata of @func.
 *
 * Reads @str and moves till @func returns %FALSE.
 *
 * Returns: %TRUE if it read a string.
 */
gboolean
crank_str_read_string (const gchar        *str,
                       guint              *position,
                       gchar             **str_ptr,
                       CrankBoolCharFunc   func,
                       gpointer            userdata)
{
  guint start;
  guint length;

  guint i;

  start = *position;
  for (i = start; func (str[i], userdata); i++) {}

  length = i - start;


  if (str_ptr != NULL)
    *str_ptr = (length != 0) ? g_strndup (str + start, length) : NULL;

  *position = i;
  return (i != start);
}

/**
 * crank_str_read_word:
 * @str: string to read.
 * @position: (inout): position.
 * @word_ptr: (nullable) (optional) (out): Read word. If it cannot read, %NULL
 *        will be returned. free with g_free() after use.
 *
 * Reads @str and moves position into non-word character.
 *
 * Returns: %TRUE if it read a word.
 */
gboolean
crank_str_read_word (const gchar *str,
                     guint       *position,
                     gchar      **word_ptr)
{
  return crank_str_read_string (str,
                                position,
                                word_ptr,
                                crank_str_g_isalnum,
                                NULL);
}

/**
 * crank_str_read_canonical_word:
 * @str: string to read.
 * @position: (inout): position.
 * @word_ptr: (nullable) (optional) (out): Read word. If it cannot read, %NULL
 *        will be returned. free with g_free() after use.
 *
 * Reads @str and moves position into non-word character.
 *
 * Returns: %TRUE if it read a word.
 */
gboolean
crank_str_read_canonical_word (const gchar  *str,
                               guint        *position,
                               gchar       **word_ptr)
{
  return crank_str_read_string (str,
                                position,
                                word_ptr,
                                crank_str_is_canonical_char,
                                NULL);
}

/**
 * crank_str_read_uint64:
 * @str: string to read.
 * @position: (inout): position.
 * @uint_ptr: (optional) (out): Read integer. If it cannot read, 0
 *             will be returned. In case of overflow, it will be
 *             %G_MAXUINT64.
 * @overflowed: (optional) (out): Whether overflow has been happened.
 *
 * Reads @str and moves position into non-numeric character.
 *
 * Returns: %TRUE if it read a integer.
 */
gboolean
crank_str_read_uint64 (const gchar *str,
                       guint       *position,
                       guint64     *uint_ptr,
                       gboolean    *overflowed)
{
  guint rstart;
  guint nzstart;
  guint rend;

  guint i;
  guint n;
  guint n1;

  guint64 m_value = 0;
  gboolean m_overflowed = 0;

  rstart = *position;

  // Get range for numeric numbers.
  for (nzstart = rstart; str[nzstart] == '0'; nzstart++) {}
  for (rend = nzstart; isdigit (str[rend]); rend++) {}

  n = rend - nzstart;
  n1 = MIN(n, I64_N10 - 1);

  // Obviously overflow: Too long numbers.
  if (I64_N10 < n)
    {
      m_overflowed = TRUE;
      m_value = G_MAXUINT64;
    }
  else if (0 < n)
    {
      for (i = 0; i < n1; i++)
        m_value = m_value * 10 + (guint64)(str[nzstart + i] - '0');

      if (I64_N10 == n)
        {
          guint vi = (guint)(str[nzstart + n1] - '0');

          if ((m_value < I64_D10) ||  ((m_value == I64_D10) && (vi < I64_R10)))
            m_value = m_value * 10 + vi;
          else
            {
              m_overflowed = TRUE;
              m_value = G_MAXUINT64;
            }
        }
    }


  *position = rend;
  if (uint_ptr != NULL)
    *uint_ptr = m_value;
  if (overflowed != NULL)
    *overflowed = m_overflowed;
  return (rstart != rend);
}

/**
 * crank_str_read_int64:
 * @str: string to read.
 * @position: (inout): position.
 * @int_ptr: (optional) (out): Read integer. If it cannot read, 0 will
 *           be returned. In case of over/underflow, %G_MAXINT64 or
 *           %G_MININT64 will be returned.
 * @overflowed: (optional) (out): Whether overflow has been happened.
 *        0 for success, 1 for overflow, -1 for underflow.
 *
 * Reads @str and moves position into non-numeric character.
 *
 * Returns: %TRUE if it read a integer.
 */
gboolean
crank_str_read_int64 (const gchar *str,
                      guint       *position,
                      gint64      *int_ptr,
                      gint        *overflowed)
{
  guint m_pos;

  gboolean success;
  guint64 m_uvalue;
  gint64 m_value = 0;
  gint m_overflowed = 0;
  gboolean negate;

  m_pos = *position;
  crank_str_read_plusminus (str, &m_pos, &negate);

  success = crank_str_read_uint64 (str, &m_pos, &m_uvalue, NULL);
  if (success)
    {
      if (((negate) ? I63N : I63) < m_uvalue)
        {
          m_overflowed = (negate) ? -1 : 1;
          m_value = (negate) ? G_MININT64 : G_MAXINT64;
        }
      else
        {
          m_value = (gint64)m_uvalue;
          m_value = (negate) ? -m_value : m_value;
        }
    }

  if (int_ptr != NULL)
    *int_ptr = m_value;
  if (overflowed != NULL)
    *overflowed = m_overflowed;

  if (success)
    *position = m_pos;

  return success;
}

/**
 * crank_str_read_double:
 * @str: string to read.
 * @position: (inout): position.
 * @value_ptr: (optional) (out): Read value. If it cannot read, 0.0 will be
 *             returned. In case of overflow, %G_MAXDOUBLE or -G_MAXDOUBLE can
 *             be returned.
 * @read_flags: (optional) (out): Flags about @value_ptr.
 *
 * Reads @str and moves position into non-numeric character.
 *
 * This function reads following patterns.
 *
 * * Symbolic words (Case Insensitive and this results %CRANK_READ_DEC_SYMBOL)
 *   * "inf", "infinity", "nan"
 * * Numeric
 *   * (0 or more numbers) \[.(0 or more numbers)\] \[(e or E)(1 or more numbers)\]
 *
 *     or
 *
 *     (1 or more numbres) \[(e or E)(1 or more numbers)\]
 *
 * This implementation uses naive implementation but using 18 digits of mantissa.
 * Some precision loss might be expected.
 */
gboolean
crank_str_read_double (const gchar        *str,
                       guint              *position,
                       gdouble            *value_ptr,
                       CrankReadDecResult *read_flags)
{
  gchar numbox[18];

  gboolean success = TRUE;
  guint mpos;
  guint mend;
  gint mdp;

  gboolean negate;

  guint64 mantisa10 = 0;
  gint64 exp10 = 0;
  gint exp10_p = 0;


  CrankUint128 mantisa2;
  gint exp2;

  guint i;

  gdouble mvalue = 0;
  CrankReadDecResult mres = 0;

  mpos = *position;

  //// Read string.
  // Read sign.
  crank_str_read_plusminus (str, &mpos, &negate);

  //// Read words
  if (isalpha (str[mpos]))
    {
      gint symno = crank_str_check_words (str, &mpos, float_symwords,
                                          CRANK_STR_CHECK_CI_IN_LOWERCASE);

      if (symno == -1)
        {
          success = FALSE;
        }
      else
        {
          mres = CRANK_READ_DEC_SYMBOL;

          mvalue = (symno == 2) ? NAN : INFINITY;
          mvalue = (negate) ? -mvalue : mvalue;
        }
    }

  //// Read mantissa
  else if (crank_str_read_decstring (str, &mpos, 18, numbox, &mend, &mdp,
                                     &exp10))
    {
      exp10 += mdp;
      exp10 -= MIN(mend, 18);

      exp10_p = exp10 + mend - 1;

      // Some noticable things can be detected.
      // overflow
      if (DBL_DEMAX < exp10_p)
        {
          mvalue = INFINITY;
          mres = CRANK_READ_DEC_OVERFLOW;
        }

      // underflow
      else if (exp10_p < DBL_DEDNORM)
        {
          mvalue = 0.0;
          mres = CRANK_READ_DEC_UNDERFLOW;
        }

      // truncation
      else if (18 < mend)
        {
          mres = CRANK_READ_DEC_TRUNC_PRECISE;
          mend = 18;
        }


      //// Constructs numeric structure.
      // Construct N for N x 10 exp.
      for (i = 0; i < mend; i++)
        mantisa10 = mantisa10 * 10 + (guint64)(numbox[i] - '0');

      // Constructs float base 2.
      exp2 = exp10;

      exp2 += 63;
      exp2 -= crank_bits_shift_to_left64 (&mantisa10);
      mantisa2.h = mantisa10;
      mantisa2.l = 0;

      if (exp10 < 0)
        {
          while (exp10 <= -16)
            {
              crank_uint128_div64_self (&mantisa2, PEN16);
              exp10 += 16;
              exp2 -= crank_str_shift128_to_left (&mantisa2);
            }

          if (exp10 <= -8)
            {
              crank_uint128_div32_self (&mantisa2, PEN8);
              exp10 += 8;
            }

          if (exp10 <= -4)
            {
              crank_uint128_div32_self (&mantisa2, PEN4);
              exp10 += 4;
            }
          if (exp10 <= -2)
            {
              crank_uint128_div32_self (&mantisa2, PEN2);
              exp10 += 2;
            }
          if (exp10 <= -1)
            {
              crank_uint128_div32_self (&mantisa2, 5);
              exp10 += 1;
            }
          exp2 -= crank_str_shift128_to_left (&mantisa2);
        }
      else if (0 < exp10)
        {
          while (16 <= exp10)
            {
              if (mantisa2.h > I64_D5_16)
                {
                  crank_uint128_rsh_self (&mantisa2, PEN16_BIT);
                  exp2 += PEN16_BIT;
                }
              crank_uint128_mul64_self (&mantisa2, PEN16);
              exp10 -= 16;
            }

          if (8 <= exp10)
            {
              if (mantisa2.h > I64_D5_8)
                {
                  crank_uint128_rsh_self (&mantisa2, PEN8_BIT);
                  exp2 += PEN8_BIT;
                }
              crank_uint128_mul64_self (&mantisa2, PEN8);
              exp10 -= 8;
            }

          if (4 <= exp10)
            {
              if (mantisa2.h > I64_D5_4)
                {
                  crank_uint128_rsh_self (&mantisa2, PEN4_BIT);
                  exp2 += PEN4_BIT;
                }
              crank_uint128_mul64_self (&mantisa2, PEN4);
              exp10 -= 4;
            }
          if (2 <= exp10)
            {
              if (mantisa2.h > I64_D5_2)
                {
                  crank_uint128_rsh_self (&mantisa2, PEN2_BIT);
                  exp2 += PEN2_BIT;
                }
              crank_uint128_mul64_self (&mantisa2, PEN2);
              exp10 -= 2;
            }
          if (1 <= exp10)
            {
              if (mantisa2.h > I64_D5)
                {
                  if (mantisa2.l & 8)
                    {
                      crank_uint128_add64_self (&mantisa2, 8);
                    }
                  crank_uint128_rsh_self (&mantisa2, 3);
                  exp2 += 3;
                }
              crank_uint128_mul64_self (&mantisa2, 5);
              exp10 -= 1;
            }

          exp2 -= crank_str_shift128_to_left (&mantisa2);
        }
      //// Check sepcialities
      // Underflow cases
      if (exp2 < DBL_EDNORM)
        {
          mvalue = 0;
          mres |= CRANK_READ_DEC_UNDERFLOW;
        }

      // Denormalized cases.
      else if (exp2 < DBL_EMIN)
        {
          mvalue = crank_str_build_double_denorm (negate, exp2, mantisa2.h);
        }

      // Overflow cases
      else if (exp2 > DBL_EMAX)
        {
          mvalue = INFINITY;
          mres |= CRANK_READ_DEC_OVERFLOW;
        }

      else
        {
          mvalue = crank_str_build_double_norm (negate, exp2, mantisa2.h);
        }
    }
  else
    success = FALSE;

  if (success)
    *position = mpos;

  if (value_ptr != NULL)
    *value_ptr = mvalue;
  if (read_flags != NULL)
    *read_flags = mres;

  return success;
}

/**
 * crank_str_read_path:
 * @str: String to read.
 * @position: (inout): position
 * @path: (nullable) (optional) (out) (array zero-terminated):
 *     Path entries.
 * @func: (scope call): function to read entries. Should not accept '/'.
 * @userdata: (closure): userdata for @func.
 *
 * Reads @path from @str and moves @position into next non-path characters.
 *
 * This function does not overwrap @func, so @func should not accept '/', or
 * @func will read path as single string chunk.
 *
 * If path portion of @str ends with '/', @path will have empty string at the
 * end. If it starts with '/', @path will have empty string at the start.
 */
gboolean
crank_str_read_path (const gchar        *str,
                     guint              *position,
                     gchar            ***path,
                     CrankReadStrFunc    func,
                     gpointer            userdata)
{
  guint start = *position;

  if (path != NULL)
    {
      GPtrArray *path_ptrarray = g_ptr_array_new ();
      while (TRUE)
        {
          gchar *entry;

          if (! func (str, position, &entry, userdata))
            g_ptr_array_add (path_ptrarray, g_strdup (""));
          else
            g_ptr_array_add (path_ptrarray, entry);

          if (str[*position] != '/') break;
          (*position) ++;
        }

      g_ptr_array_add (path_ptrarray, NULL); // Append NULL to make sure null-terminated
                                             //
      *path = (gchar**)g_ptr_array_free (path_ptrarray, start == *position);
    }

  else
    {
      while (TRUE)
        {
          func (str, position, NULL, userdata);

          if (str[*position] != '/') break;
          (*position) ++;
        }
    }

  return start != *position;
}


//////// Scanning Function

/**
 * crank_str_scan_char:
 * @str: String to scan.
 * @position: (inout): position.
 * @char_ptr: (type gchar) (optional) (out): Scanned char. If it cannot read,
 *        '\0' will be stored.
 *
 * Reads @str and moves position into next character. Skips space before
 * it reads.
 *
 * Returns: %TRUE if it reads a non-space character.
 */
gboolean
crank_str_scan_char (const gchar *str,
                     guint       *position,
                     gchar       *char_ptr)
{
  guint i;

  i = *position;

  crank_str_read_space (str, &i, NULL);

  if (char_ptr != NULL)
    *char_ptr = str[i];

  if (str[i] != '\0')
    {
      *position = i + 1;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

/**
 * crank_str_scan_word:
 * @str: String to scan.
 * @position: (inout): position.
 * @word_ptr: (nullable) (optional) (out): Scanned word. If it cannot read,
 *        %NULL will be stored. free with g_free() after use.
 *
 * Reads @str and moves position into non-word character. Skips space before
 * it reads.
 *
 * Returns: %TRUE if it read a word.
 */
gboolean
crank_str_scan_word (const gchar *str,
                     guint       *position,
                     gchar      **word_ptr)
{
  guint i;

  i = *position;

  crank_str_read_space (str, &i, NULL);

  if (crank_str_read_word (str, &i, word_ptr))
    {
      *position = i;
      return TRUE;
    }
  else
    {
      if (word_ptr != NULL)
        *word_ptr = NULL;
      return FALSE;
    }
}

/**
 * crank_str_scan_uint64:
 * @str: String to scan.
 * @position: (inout): position.
 * @uint_ptr: (optional) (out): Read integer. If it cannot read, 0
 *             will be returned. In case of overflow, it will be
 *             %G_MAXUINT64.
 * @overflowed: (optional) (out): Whether overflow has been happened.
 *
 * Reads @str and moves position into non-numeric character.
 *
 * Returns: %TRUE if it read a integer.
 */
gboolean
crank_str_scan_uint64 (const gchar *str,
                       guint       *position,
                       guint64     *uint_ptr,
                       gboolean    *overflowed)
{
  guint i;

  i = *position;

  crank_str_read_space (str, &i, NULL);
  if (crank_str_read_uint64 (str, &i, uint_ptr, overflowed))
    {
      *position = i;
      return TRUE;
    }
  else
    {
      if (uint_ptr != NULL)
        *uint_ptr = 0;
      if (overflowed != NULL)
        overflowed = FALSE;
      return FALSE;
    }
}

/**
 * crank_str_scan_int64:
 * @str: String to scan.
 * @position: (inout): position.
 * @int_ptr: (optional) (out): Read integer. If it cannot read, 0 will
 *           be returned. In case of over/underflow, %G_MAXINT64 or
 *           %G_MININT64 will be returned.
 * @overflowed: (optional) (out): Whether overflow has been happened.
 *        0 for success, 1 for overflow, -1 for underflow.
 *
 * Reads @str and moves position into non-numeric character.
 *
 * Returns: %TRUE if it read a integer.
 */
gboolean
crank_str_scan_int64 (const gchar *str,
                      guint       *position,
                      gint64      *int_ptr,
                      gint        *overflowed)
{
  guint i;

  i = *position;

  crank_str_read_space (str, &i, NULL);
  if (crank_str_read_int64 (str, &i, int_ptr, overflowed))
    {
      *position = i;
      return TRUE;
    }
  else
    {
      if (int_ptr != NULL)
        *int_ptr = 0;
      if (overflowed != NULL)
        *overflowed = 0;
      return FALSE;
    }
}

/**
 * crank_str_scan_double:
 * @str: String to scan.
 * @position: (inout): position.
 * @value_ptr: (optional) (out): Read value. If it cannot read, 0.0 will be
 *             returned. In case of overflow, %G_MAXDOUBLE or -G_MAXDOUBLE can
 *             be returned.
 * @result: (optional) (out): Read results about @value_ptr.
 *
 * Reads @str and moves position into non-numeric character. This function may
 * read special words like "NaN" or "inf". If so, @CRANK_READ_DEC_SYMBOL
 * is returned through @result.
 *
 * This implementation uses naive implementation but using 36 digits of mantissa.
 * Some precision loss might be expected.
 */
gboolean
crank_str_scan_double (const gchar        *str,
                       guint              *position,
                       gdouble            *value_ptr,
                       CrankReadDecResult *result)
{
  guint i;

  i = *position;

  crank_str_read_space (str, &i, NULL);
  if (crank_str_read_double (str, &i, value_ptr, result))
    {
      *position = i;
      return TRUE;
    }
  else
    {
      if (value_ptr != NULL)
        *value_ptr = 0.0;
      if (result != NULL)
        *result = 0;
      return FALSE;
    }
}
//////// Checking Function

/**
 * crank_str_check_char:
 * @str: String to check.
 * @position: (inout): position.
 * @check_item: item to check.
 *
 * Checks next character is @check_item and moves @position to next if it is.
 * Skips space before it reads.
 *
 * Returns: Whether the scanned character is equal to check_item.
 */
gboolean
crank_str_check_char (const gchar *str,
                      guint       *position,
                      gchar        check_item)
{
  guint i;

  i = *position;

  crank_str_read_space (str, &i, NULL);

  if (str[i] == check_item)
    {
      *position = i + 1;
      return TRUE;
    }
  else
    return FALSE;
}


/**
 * crank_str_check_chars:
 * @str: String to check.
 * @position: (inout): position.
 * @check_items: (type gchar) (array length=ncheck_items): Items to check.
 * @ncheck_items: Length of @check_items.
 *
 * Checks next character is one of @check_items, and moves @position to next if it is.
 * Skips space before it reads.
 *
 * Returns: The index of read character at @check_items, or -1 for absences.
 */
gint
crank_str_check_chars (const gchar *str,
                       guint       *position,
                       const gchar *check_items,
                       guint        ncheck_items)
{
  guint i;
  guint j;

  i = *position;

  crank_str_read_space (str, &i, NULL);

  for (j = 0; j < ncheck_items; j++)
    {
      if (str[i] == check_items[j])
        {
          *position = i + 1;
          return j;
        }
    }

  return -1;
}


/**
 * crank_str_check_chars_str:
 * @str: String to check.
 * @position: (inout): position.
 * @check_items: Items to check.
 *
 * Checks next character is one of @check_items, and moves @position ot next if it is.
 * Skips space before it reads.
 *
 * Returns: The index of read character at @check_items, or -1 for absences
 */
gint
crank_str_check_chars_str (const gchar *str,
                           guint       *position,
                           const gchar *check_items)
{
  guint i;
  guint j;

  i = *position;

  crank_str_read_space (str, &i, NULL);

  for (j = 0; check_items[j] != '\0'; j++)
    {
      if (str[i] == check_items[j])
        {
          *position = i + 1;
          return j;
        }
    }

  return -1;
}

/**
 * crank_str_check_words:
 * @str: String to check.
 * @position: (inout): position.
 * @check_words: (array zero-terminated=1): Items to check.
 * @flags: A flags to adjust function behavior.
 *
 * Checks next words is one of @check_words, and move @position to next if it is.
 * Skip spaces before it reads.
 *
 * Returns: The index of read word at @check_words, or -1 for absences.
 */
gint
crank_str_check_words (const gchar       *str,
                       guint             *position,
                       gchar            **check_words,
                       CrankStrCheckFlags flags)
{
  guint i;
  guint j;
  gchar *word;
  gchar *cword;

  gchar*(*convfunc) (const gchar*, gssize) = NULL;
  gchar *ccword = NULL;

  guint case_insensitive;


  i = *position;

  crank_str_read_space (str, &i, NULL);

  if (!crank_str_scan_word (str, &i, &word))
    return -1;

  // Prepare case insensitive comparsion
  case_insensitive = flags & CRANK_STR_CHECK_MASK_CASE_INSENSITIVE;

  if (case_insensitive != 0)
    {
      convfunc = (case_insensitive == CRANK_STR_CHECK_CI_IN_UPPERCASE) ?
                 g_ascii_strup : g_ascii_strdown;

      cword = convfunc (word, -1);
    }
  else
    {
      cword = word;
    }


  // Check by comparsion.
  if (case_insensitive == CRANK_STR_CHECK_CI_NORMAL)
    {
      for (j = 0; check_words[j] != NULL; j++)
        {
          gchar *ccword = convfunc (check_words[j], -1);
          gboolean cmpresult = (strcmp (cword, ccword) == 0);

          g_free (ccword);
          if (cmpresult)
            break;
        }
    }
  else
    {
      for (j = 0; check_words[j] != NULL; j++)
        {
          if (strcmp (cword, check_words[j]) == 0)
            break;
        }
    }

  // wrap up!
  if (case_insensitive != 0)
    g_free (cword);
  g_free (word);

  // Return result
  if (check_words[j] == NULL)
    {
      return -1;
    }
  else
    {
      *position = i;
      return j;
    }
}
