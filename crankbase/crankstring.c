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
 * For complex string functions like parsing, Libraries that provides these
 * function should be consulted.
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

#define PEN16 G_GUINT64_CONSTANT(0x2386F26FC1)
#define PEN8  0x5F5E1
#define PEN4  0x271
#define PEN2  0x19

#define PEN16_BIT	38
#define PEN8_BIT	19
#define PEN4_BIT	10
#define PEN2_BIT	5
#define PEN1_BIT	3

#define I64_D10 G_GUINT64_CONSTANT(1844674407370955161)
#define I64_R10 6
#define I64_N10 20

#define I63		G_GUINT64_CONSTANT(9223372036854775807)
#define I63N	G_GUINT64_CONSTANT(9223372036854775808)

#define I64_D5		G_GUINT64_CONSTANT(3689348814741910323)
#define I64_D5_2	G_GUINT64_CONSTANT(737869762948382064)
#define I64_D5_4	G_GUINT64_CONSTANT(29514790517935282)
#define I64_D5_8	G_GUINT64_CONSTANT(47223664828696)
#define I64_D5_16	G_GUINT64_CONSTANT(120892581)

#define FLT_EBIT	(8)
#define FLT_MBIT	(23)
#define FLT_BIAS	(127)

#define DBL_EBIT	(11)
#define DBL_MBIT	(52)
#define DBL_BIAS	(1023)

#define DBL_EMIN	(-1022)
#define DBL_EMAX	(1023)
#define DBL_EDNORM	(-1074)

#define DBL_DEMIN	(-308)
#define	DBL_DEMAX	(308)
#define DBL_DEDNORM	(-323)

static guint
crank_str_shift128_to_left (	CrankUint128*	subject	)
{
  	guint	result = 0;
  	guint64	nsubject = 0;
  	
  	if (subject->h == 0) {
  		result = 64 + crank_bits_shift_to_left64(&(subject->l));
  		
  		subject->h = subject->l;
  		subject->l = 0;
  	}
  	else {
  		result = crank_bits_shift_to_left64(&(subject->h));
  		
  		subject->h |= (subject->l) >> (64 - result);
  		subject->l <<= result;
  	}
  	
  	return result;
}

static gboolean
crank_str_read_decstring (	const gchar*	str,
						  	guint*			position,
						  	guint			n_numbox,
						  	gchar*			numbox,
						  	guint*			eend,
						  	gint*			dp,
						  	gint64*			expon	)
{
	guint si;	//string iteration
	gint bi;	//number box iteration
	
	bi = 0;

  	// Read preceeding zeros.
  	for (si = *position; str[si] == '0'; si++) {}

	
  	// Read integer part.
  	for (; isdigit (str[si]); si++) {
		if (str[si] != '0')	*eend = bi + 1;
  		if (bi < n_numbox)	numbox[bi] = str[si];
		bi++;
  	}
  	

  	// Read decimal point.
	*dp = bi;
  	if (str[si] == '.') {
  		si++;
  		
  		// If it is still reading preceeding zeroes,
  		if (bi == 0) {
  			for (; str[si] == '0'; si++) { bi --; }
  			*dp = bi;
  			bi = 0;
  		}
  	}

  	// Read numbers.
  	for (; isdigit (str[si]); si++) {
  		if (str[si] != '0') *eend = bi + 1;
  		if (bi < n_numbox) numbox[bi] = str[si];
		bi++;
	}

	// Read exponential.
	if(str[si] == 'e' || str[si] == 'E') {
		si++;
		if (! crank_str_read_int64 (str, &si, expon, NULL)) si--;
	}

	if (*position != si) {
		*position = si;
		return TRUE;
	}
  	else return FALSE;
}


static gdouble
crank_str_build_double_norm (	const gboolean	sign,
								const gint		exp,
								const guint64	mantissa	)
{
	guint64	mantissa_shift = mantissa >> 11;
	guint64 mantissa_rest = 0x7FFLU & mantissa;
	gint	nexp = exp;
	
	union {
		gdouble	value;
		guint64	bits;
	} result;
	
	// Round it up
	// This is middle case: round to even
	if (mantissa_rest == 0x400LU) {
		if (mantissa_shift % 2 == 1) mantissa_shift++;
	}
	else if (mantissa_rest > 0x400LU) {
		mantissa_shift++;
	}
	
	// If rounding caused exponential increase.
	if (0x20000000000000LU <= mantissa_shift) {
		mantissa_shift >>= 1;
		nexp++;
	}
	
	result.bits =	((guint)sign << 31) |
					((0x7FF00000) & ((nexp+DBL_BIAS) << 20));
	
	result.bits = 	(result.bits << 32) |
					(0xFFFFFFFFFFFFFLU & mantissa_shift);
	
	return result.value;
}

static gdouble
crank_str_build_double_denorm (	const gboolean	sign,
								const gint		exp,
								const guint64	mantissa	)
{	
	guint	sha = DBL_BIAS - exp + 14;
	guint64	mantissa_shift = mantissa >> sha;
	guint64 mantissa_rest = mantissa << sha;
	
	union {
		gdouble	value;
		guint64	bits;
	} result;
	
	// Round it up
	if (mantissa_rest == 0x8000000000000000LU) {
		if (mantissa_shift % 2 == 1) mantissa_shift ++;
	}
	else if (mantissa_rest > 0x8000000000000000LU) {
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
crank_str_read_space (	const gchar*		str,
						guint*				position,
						guint*				space	)
{
	guint		i_start;
	guint		i;

	i_start = *position;

	for (i = i_start; g_ascii_isspace (str[i]); i++) {}

	if (space != NULL)
		*space = i - i_start;

	*position = i;
	return (i != i_start);
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
crank_str_read_word (	const gchar*		str,
						guint*				position,
						gchar**				word_ptr	)
{
	guint		i_start;
	guint		i;

	guint		i_len;

	i_start = *position;

	for (i = i_start; g_ascii_isalnum (str[i]); i++) {}
	i_len = i - i_start;

	if (word_ptr != NULL)
		*word_ptr = (i_len != 0) ? g_strndup (str + i_start, i_len) : NULL;

	*position = i;
	return (i != i_start);
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
crank_str_read_uint64 (	const gchar*		str,
						guint*				position,
						guint64*			uint_ptr,
						gboolean*			overflowed	)
{
  guint	rstart;
  guint nzstart;
  guint	rend;

  guint i;
  guint n;
  guint n1;

  guint64  m_value = 0;
  gboolean m_overflowed = 0;

  rstart = *position;

  // Get range for numeric numbers.
  for (nzstart = rstart; str[nzstart] == '0'; nzstart ++) {}
  for (rend = nzstart; isdigit (str[rend]); rend++) {}

  n = rend - nzstart;
  n1 = MIN(n, I64_N10 - 1);

  // Obviously overflow: Too long numbers.
  if (I64_N10 < n) {
	m_overflowed = TRUE;
	m_value = G_MAXUINT64;
  }
  else if (0 < n) {
    for (i = 0; i < n1; i++)
	  m_value = m_value * 10 + (guint64)(str[rstart + i] - '0');

	if (I64_N10 == n) {
	  guint	vi = (guint)(str[rstart + n1] - '0');

	  if ((m_value < I64_D10) ||  ((m_value == I64_D10) && (vi < I64_R10)))
	 	m_value = m_value * 10 + vi;
	  else {
	 	m_overflowed = TRUE;
	 	m_value = G_MAXUINT64;
	  }
	}
  }


  *position = rend;
  if (uint_ptr != NULL) *uint_ptr = m_value;
  if (overflowed != NULL) *overflowed = m_overflowed;
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
crank_str_read_int64 (	const gchar*		str,
						guint*				position,
						gint64*				int_ptr,
						gint*				overflowed	)
{
	guint	m_pos;

	gboolean	success;
	guint64		m_uvalue;
	gint64		m_value = 0;
	gint		m_overflowed = 0;
	gboolean	negate = FALSE;

	m_pos = *position;
	if (str[m_pos] == '+') {
		m_pos ++;
		negate = FALSE;
		crank_str_read_space (str, &m_pos, NULL);
	}
	else if (str[m_pos] == '-') {
		m_pos ++;
		negate = TRUE;
		crank_str_read_space (str, &m_pos, NULL);
	}

	success = crank_str_read_uint64 (str, &m_pos, &m_uvalue, NULL);
	if (success) {
		if (((negate)?I63N:I63) < m_uvalue) {
			m_overflowed = (negate)?-1:1;
			m_value = (negate)?G_MININT64:G_MAXINT64;
		}
		else {
			m_value = (gint64)m_uvalue;
			m_value = (negate)? -m_value : m_value;
		}
	}

	if (int_ptr != NULL) *int_ptr = m_value;
	if (overflowed != NULL) *overflowed = m_overflowed;

	if (success) *position = m_pos;

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
 * Reads @str and moves position into non-numeric character. This function may
 * read special words like "NaN" or "inf". If so, @CRANK_READ_DEC_SYMBOL
 * is returned through @read_flags.
 *
 * This implementation uses naive implementation but using 36 digits of mantissa.
 * Some precision loss might be expected.
 */
gboolean
crank_str_read_double (	const gchar*		str,
						guint*				position,
						gdouble*			value_ptr,
						CrankReadDecResult*	read_flags	)
{
	gchar		numbox[36] = {0};

	guint		mpos;

	guint		mend;
	gint		mdp;
	
	guint		wpos;

	gchar*		lsymbol;
	gchar*		symbol;

	gboolean	negate = FALSE;

	guint64			mantisa10_temp = 0;
	CrankUint128	mantisa10 = {0, 0};
	gint64			exp10 = 0;
  	gint			exp10_p = 0;


	CrankUint128	mantisa2;
	gint			exp2;

	guint		i;
	guint		n;
  	guint		nb;

	GDoubleIEEE754 		mvalue;
	CrankReadDecResult	mres;

	mpos = *position;

	//// Read string.
	// Read sign.
	if (str[mpos] == '-') {
		mpos ++;
		crank_str_read_space (str, &mpos, NULL);
		negate = TRUE;
	}
	else if (str[mpos] == '+') {
		mpos ++;
		crank_str_read_space (str, &mpos, NULL);
	}

	//// Read words
	wpos = mpos;
	if (isalpha (str[wpos]) && (crank_str_read_word (str, &wpos, &symbol))) {
		lsymbol = g_ascii_strdown (symbol, -1);

		if ((strcmp (lsymbol, "inf") == 0) || (strcmp (lsymbol, "infinity") == 0)) {
			mvalue.v_double = INFINITY;
			mres = CRANK_READ_DEC_SYMBOL;
			mpos = wpos;
		}
		else if (strcmp (lsymbol, "nan") == 0) {
			mvalue.v_double = NAN;
			mres = CRANK_READ_DEC_SYMBOL;
			mpos = wpos;
		}
		else {
			g_free (symbol);
			g_free (lsymbol);
			return FALSE;
		}
			
		
		g_free (symbol);
		g_free (lsymbol);
	}

	//// Read mantissa
	else if (crank_str_read_decstring (str, &mpos, 36, numbox, &mend, &mdp, &exp10)) {
		exp10 += mdp;
		exp10 -= MIN(mend, 36);
		
		exp10_p = exp10 + mend - 1;

		// Some noticable things can be detected.
		// overflow
		if (DBL_DEMAX < exp10_p) {
			mvalue.v_double = INFINITY;
			mres = CRANK_READ_DEC_OVERFLOW;
		}

		// underflow
		else if (exp10_p < DBL_DEDNORM) {
			mvalue.v_double = 0.0;
			mres = CRANK_READ_DEC_UNDERFLOW;
		}

		// truncation
		else if (36 < mend) {
			mres = CRANK_READ_DEC_TRUNC_PRECISE;
			mend = 36;
		}


		//// Constructs numeric structure.
		// Construct N for N x 10 exp.
		nb = mend - 18;
		
		i = 0;
		if (18 < mend) {
			for (; i < nb; i++) {
				mantisa10_temp = mantisa10_temp * 10 + (guint64)(numbox[i] - '0');
			}
			crank_uint128_init_mul(&mantisa10, mantisa10_temp, DEC18);
			mantisa10_temp = 0;
		}
		
		for (; i < mend; i++) {
			mantisa10_temp = mantisa10_temp * 10 + (guint64)(numbox[i] - '0');
			n++;
		}
	  	crank_uint128_add64_self (&mantisa10, mantisa10_temp);
	

		// Constructs float base 2.
		exp2 = exp10;

	  	if (mantisa10.h == 0) {
		  	mantisa10_temp = mantisa10.l;
			exp2 += 63;
		  	exp2 -= crank_bits_shift_to_left64 (&mantisa10_temp);
			mantisa2.h = mantisa10_temp;
		  	mantisa2.l = 0;

		}
	  	else {
		  	mantisa10_temp = mantisa10.h;
		  	exp2 += 127;
			i = crank_bits_shift_to_left64 (&mantisa10_temp);

			exp2 -= i;
			crank_uint128_lsh(&mantisa10, i, &mantisa2);
		}
	  	

	  	if (exp10 < 0) {
			while (exp10 <= -8) {
				crank_uint128_div32_self (&mantisa2, PEN8);
				exp10 += 8;
				exp2 -= crank_str_shift128_to_left (&mantisa2);
			}
			
			if (exp10 <= -4) {
				crank_uint128_div32_self (&mantisa2, PEN4);
				exp10 += 4;
				exp2 -= crank_str_shift128_to_left (&mantisa2);
			}
			if (exp10 <= -2) {
				crank_uint128_div32_self (&mantisa2, PEN2);
				exp10 += 2;
				exp2 -= crank_str_shift128_to_left (&mantisa2);
			}
			if (exp10 <= -1) {
				crank_uint128_div32_self (&mantisa2, 5);
				exp10 += 1;
				exp2 -= crank_str_shift128_to_left (&mantisa2);
			}
		  }
	  	else if (0 < exp10) {
	  		while (8 <= exp10) {
	  			if (mantisa2.h > I64_D5_8) {
	  				crank_uint128_rsh_self (&mantisa2, PEN8_BIT);
	  				exp2 += PEN8_BIT;
	  			}
	  			crank_uint128_mul64_self (&mantisa2, PEN8);
	  			exp10 -= 8;
	  		}
	  		
	  		if (4 <= exp10) {
	  			if (mantisa2.h > I64_D5_4) {
	  				crank_uint128_rsh_self (&mantisa2, PEN4_BIT);
	  				exp2 += PEN4_BIT;
	  			}
	  			crank_uint128_mul64_self (&mantisa2, PEN4);
	  			exp10 -= 4;
	  		}
	  		if (2 <= exp10) {
	  			if (mantisa2.h > I64_D5_2) {
	  				crank_uint128_rsh_self (&mantisa2, PEN2_BIT);
	  				exp2 += PEN2_BIT;
	  			}
	  			crank_uint128_mul64_self (&mantisa2, PEN2);
	  			exp10 -= 2;
	  		}
			if (1 <= exp10) {
	  			if (mantisa2.h > I64_D5) {
	  				if (mantisa2.l & 8) { crank_uint128_add64_self (&mantisa2, 8);}
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
		if (exp2 < DBL_EDNORM) {
			mvalue.v_double = 0;
			mres |= CRANK_READ_DEC_UNDERFLOW;
		}
	
		// Denormalized cases.
		else if (exp2 < DBL_EMIN) {
			mvalue.v_double = crank_str_build_double_denorm (negate, exp2, mantisa2.h);
		}
	
		// Overflow cases
		else if (exp2 > DBL_EMAX) {
			mvalue.v_double = INFINITY;
			mres |= CRANK_READ_DEC_OVERFLOW;
		}
		
		else {
			mvalue.v_double = crank_str_build_double_norm (negate, exp2, mantisa2.h);
		}
	}
	else return FALSE;
	mvalue.mpn.sign = negate;

	*position = mpos;
	if (value_ptr != NULL) *value_ptr = mvalue.v_double;
	if (read_flags != NULL) *read_flags = mres;	
	
	return TRUE;
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
crank_str_scan_char (	const gchar*		str,
						guint*				position,
						gchar*				char_ptr	)
{
	guint	i;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	if (char_ptr != NULL) *char_ptr = str[i];
	
	if (str[i] != '\0') {
		*position = i + 1;
		return TRUE;
	}
	else {
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
crank_str_scan_word (	const gchar*		str,
						guint*				position,
						gchar**				word_ptr	)
{
	guint	i;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	if (crank_str_read_word (str, &i, word_ptr)) {
		*position = i;
		return TRUE;
	}
	else {
		if (word_ptr != NULL) *word_ptr = NULL;
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
crank_str_scan_uint64 (	const gchar*		str,
						guint*				position,
						guint64*			uint_ptr,
						gboolean*			overflowed	)
{
	guint	i;
	
	i = *position;
	
	crank_str_read_space (str, &i, NULL);
	if (crank_str_read_uint64 (str, &i, uint_ptr, overflowed)) {
		*position = i;
		return TRUE;
	}
	else {
		if (uint_ptr != NULL) *uint_ptr = 0;
		if (overflowed != NULL) overflowed = FALSE;
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
crank_str_scan_int64 (	const gchar*	str,
						guint*			position,
						gint64*			int_ptr,
						gint*			overflowed	)
{
	guint	i;
	
	i = *position;
	
	crank_str_read_space (str, &i, NULL);
	if (crank_str_read_int64 (str, &i, int_ptr, overflowed)) {
		*position = i;
		return TRUE;
	}
	else {
		if (int_ptr != NULL) *int_ptr = 0;
		if (overflowed != NULL) *overflowed = 0;
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
crank_str_scan_double (	const gchar*	str,
						guint*			position,
						gdouble*		value_ptr,
						CrankReadDecResult*	result	)
{
	guint	i;
	
	i = *position;
	
	crank_str_read_space (str, &i, NULL);
	if (crank_str_read_double (str, &i, value_ptr, result)) {
		*position = i;
		return TRUE;
	}
	else {
		if (value_ptr != NULL) *value_ptr = 0.0;
		if (result != NULL) *result = 0;
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
crank_str_check_char (	const gchar*		str,
						guint*				position,
						gchar				check_item	)
{
	guint	i;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	if (str[i] == check_item) {
		*position = i + 1;
		return TRUE;
	}
	else return FALSE;
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
crank_str_check_chars (	const gchar*		str,
						guint*				position,
						const gchar*		check_items,
						guint				ncheck_items	)
{
	guint	i;
	guint	j;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	for (j = 0; j < ncheck_items; j++) {
		if (str[i] == check_items[j]) {
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
crank_str_check_chars_str (	const gchar*		str,
							guint*				position,
							const gchar*		check_items	)
{
	guint	i;
	guint	j;

	i = *position;

	crank_str_read_space (str, &i, NULL);

	for (j = 0; check_items[j] != '\0'; j++) {
		if (str[i] == check_items[j]) {
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
crank_str_check_words (	const gchar*		str,
						guint*				position,
						const gchar**		check_words,
						CrankStrCheckFlags	flags		)
{
	guint	i;
	guint	j;
	gchar*	word;
	gchar*	cword;
	
	gchar* (*convfunc) (const gchar*, gssize) = NULL;
	gchar*	ccword = NULL;
	
	guint	case_insensitive;
	
	
	i = *position;
	
	crank_str_read_space (str, &i, NULL);
	
	if (! crank_str_scan_word (str, &i, &word)) return -1;
	
	// Prepare case insensitive comparsion
	case_insensitive = flags & CRANK_STR_CHECK_MASK_CASE_INSENSITIVE;
	
	if (case_insensitive != 0) {
		convfunc = (case_insensitive == CRANK_STR_CHECK_CI_IN_UPPERCASE) ?
					g_ascii_strup : g_ascii_strdown ;
		
		cword = convfunc (word, -1);
	}
	else {
		cword = word;
	}
	
	
	// Check by comparsion.
	if (case_insensitive == CRANK_STR_CHECK_CI_NORMAL) {
		for (j = 0; check_words[j] != NULL; j++) {
			gchar*		ccword = convfunc (check_words[j], -1);
			gboolean	cmpresult = (strcmp (cword, ccword) == 0);
			
			g_free (ccword);
			if (cmpresult) break;
		}
	}
	else {
		for (j = 0; check_words[j] != NULL; j++) {
			if (strcmp (cword, check_words[j]) == 0) break;
		}
	}
	
	// wrap up!
	if (case_insensitive != 0) g_free (cword);
	g_free (word);
	
	// Return result
	if (check_words[j] == NULL) {
		return -1;
	}
	else {
		*position = i;
		return j;
	}
}
