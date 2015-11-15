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

#include <glib.h>

#include "crankcomplex.h"
#include "crankfunction.h"


/**
 * SECTION: crankfunction
 * @title: Function Definitions
 * @short_description: Contains function and function types that frequently used.
 * @include: crankbase.h
 * @stability: unstable
 *
 * Any library usually defines their own function types, as required function
 * types are very specific to their use, and not really useful for generic uses.
 *
 * No exception to Crank System, too. Most of function type defined in Crank
 * System, are defined in their specific section. But some of function types are
 * frequently used and might be useful for generic uses.
 *
 * # Function types
 *
 * This section contains frequently used function types, for examples, boolean
 * evaluation functions (CrankBool{Type}Func).
 *
 * There are three kind of function, like
 * * Boolean evaluation function type.
 * * String evaluation function type.
 * * Delta-Equality function type.
 *   (if different of two are evaluated less than delta, then assume they are
 *   same)
 *
 * # Predefined Functions
 *
 * This section contains predefined functions, for examples, stringifies
 * pointers to primitives like float.
 *
 * There are three kind of functions, like *
 * * Hashing for #gfloat.
 * * Equality testing.
 * * Delta-Equality testing for #gfloat.
 * * comparsion.
 * * stringify functions.
 */

/**
 * crank_float_hash:
 * @a: (type gfloat*): A Pointer pointing a float value.
 *
 * Hashs a float value that suitable for normal float values.
 *
 * Handles [%G_MININT, %G_MAXINT], with over 1 of distance between neighborhood.
 *
 * If value is less than %G_MININT, then hash will be %G_MININT value, and
 * in case of greater than %G_MAXINT, hash will be %G_MAXINT.
 *
 * Returns: Hash of float values.
 */
guint
crank_float_hash (gconstpointer a)
{
  gfloat fvalue = *(gfloat*)a;
  gint ivalue =    (fvalue < G_MININT) ? G_MININT :
                (G_MAXINT < fvalue) ? G_MAXINT :
                /*default*/ (gint)fvalue;

  return (guint) ivalue;
}

/**
 * crank_float_hash1:
 * @a: (type gfloat*): A Pointer pointing a float value.
 *
 * Hashs a float value that suitable for float values that near 1 or 0.
 *
 * Current implementation just multiply by 1048576 on value and hashes.
 *
 * Returns: Hash of float values.
 */
guint
crank_float_hash1 (gconstpointer a)
{
  gfloat fvalue = *(gfloat*)a * 1048576;
  gint ivalue =    (fvalue < G_MININT) ? G_MININT :
                (G_MAXINT < fvalue) ? G_MAXINT :
                /*default*/ (gint)fvalue;

  return (guint) ivalue;
}

/**
 * crank_bool_equal:
 * @a: A Pointer pointing a boolean value.
 * @b: A Pointer pointing a boolean value.
 *
 * Check equality of boolean values. This function will work for non-normalized
 * values. (other values rather than 0 or 1)
 *
 * Returns: whether (*@a) and (*@b) are equal.
 */
gboolean
crank_bool_equal (gconstpointer a,
                  gconstpointer b)
{
  gboolean av = !*(gboolean*)a;
  gboolean bv = !*(gboolean*)b;
  return av == bv;
}

/**
 * crank_uint_equal:
 * @a: A Pointer pointing a guint value.
 * @b: A Pointer pointing a guint value.
 *
 * Check equality of guint values.
 *
 * Returns: whether (*@a) and (*@b) are equal.
 */
gboolean
crank_uint_equal (gconstpointer a,
                  gconstpointer b)
{
  guint av = *(guint*)a;
  guint bv = *(guint*)b;
  return av == bv;
}

/**
 * crank_float_equal:
 * @a: A Pointer pointing a float value.
 * @b: A Pointer pointing a float value.
 *
 * Check equality of float values, with 0.0001f of error range.
 *
 * Returns: whether (*@a) and (*@b) are equal.
 */
gboolean
crank_float_equal (gconstpointer a,
                   gconstpointer b)
{
  return crank_float_equal_delta(a, b, 0.0001f);
}




/**
 * crank_float_equal_delta:
 * @a: A Pointer pointing a float value.
 * @b: A Pointer pointing a float value.
 * @d: A delta value.
 *
 * Checks *@a and *@b are sufficiently equal:
 * This means (*@b - @d < *@a) && (*@a < *@b + @d).
 *
 * Returns: Whether @a and @b are sufficiently equal.
 */
gboolean
crank_float_equal_delta (gconstpointer a,
                         gconstpointer b,
                         const gfloat  d)
{
  gfloat av = *(gfloat*)a;
  gfloat bv = *(gfloat*)b;
  return (bv - d < av) && (av < bv + d);
}



/**
 * crank_int_compare:
 * @a: A Pointer pointing a integer value.
 * @b: A Pointer pointing a integer value.
 *
 * Compares *@a and *@b.
 *
 * Returns: Comparsion result.
 */
gint
crank_int_compare (gconstpointer a,
                   gconstpointer b)
{
  gint av = *(gint*) a;
  gint bv = *(gint*) b;

  return (bv < av) - (av < bv);
}

/**
 * crank_uint_compare:
 * @a: A Pointer pointing a unsigned integer value.
 * @b: A Pointer pointing a unsigned integer value.
 *
 * Compares *@a and *@b.
 *
 * Returns: Comparsion result.
 */
gint
crank_uint_compare (gconstpointer a,
                    gconstpointer b)
{
  guint av = *(guint*) a;
  guint bv = *(guint*) b;

  return (bv < av) - (av < bv);
}

/**
 * crank_float_compare:
 * @a: A Pointer pointing a float value.
 * @b: A Pointer pointing a float value.
 *
 * Compares *@a and *@b.
 *
 * Returns: Comparsion result.
 */
gint
crank_float_compare (gconstpointer a,
                     gconstpointer b)
{
  gfloat av = *(gfloat*) a;
  gfloat bv = *(gfloat*) b;

  return (bv < av) - (av < bv);
}



/**
 * crank_bool_to_string:
 * @value: A Pointer pointing a boolean value.
 * @userdata: (nullable): unused.
 *
 * Stringify a boolean value.
 *
 * Returns: string represents of float. free with g_free()
 */
gchar*
crank_bool_to_string (gpointer value,
                      gpointer userdata)
{
  return g_strdup (*(gboolean*)value ? "TRUE" : "FALSE");
}

/**
 * crank_int_to_string:
 * @value: A Pointer pointing a int value.
 * @userdata: (nullable): Format for stringification.
 *
 * Stringify a integer value.
 *
 * Returns: string representf integer value. free with g_free()
 */
gchar*
crank_int_to_string (gpointer value,
                     gpointer userdata)
{
  gchar *format = (userdata != NULL) ? (gchar*)userdata : "%d";
  return g_strdup_printf (format, *(gint*)value);
}

/**
 * crank_uint_to_string:
 * @value: A Pointer pointing a int value.
 * @userdata: (nullable): Format for stringification.
 *
 * Stringify a integer value.
 *
 * Returns: string representf integer value. free with g_free()
 */
gchar*
crank_uint_to_string (gpointer value,
                      gpointer userdata)
{
  gchar *format = (userdata != NULL) ? (gchar*)userdata : "%u";
  return g_strdup_printf (format, *(gint*)value);
}


/**
 * crank_float_to_string:
 * @value: A pointer pointing a float value.
 * @userdata: (nullable): Format for stringification.
 *
 * Stringify a float value.
 *
 * Returns: string represents of float. free with g_free()
 */
gchar*
crank_float_to_string (gpointer value,
                       gpointer userdata)
{
  gchar *format = (userdata != NULL) ? (gchar*)userdata : "%g";
  return g_strdup_printf (format, *(gfloat*)value);
}

/**
 * crank_pointer_to_string:
 * @value: A pointer.
 * @userdata: (nullable): Format for stringification.
 *
 * Stringify a pointer.
 *
 * Returns: string represents pointer. free with g_free()
 */
gchar*
crank_pointer_to_string (gpointer value,
                         gpointer userdata)
{
  gchar *format = (userdata != NULL) ? (gchar*)userdata : "%p";
  return g_strdup_printf (format, value);
}
