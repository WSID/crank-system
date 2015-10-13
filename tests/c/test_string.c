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
#include <math.h>
#include <glib.h>

#include "crankbase.h"
#include "crankstring.h"


//////// Declaration ///////////////////////////////////////////////////////////

static void test_read_space (void);

static void test_read_word (void);

static void test_read_uint64 (void);

static void test_read_int64 (void);

static void test_read_double (void);

static void test_read_path (void);

static void test_scan_char (void);

static void test_scan_word (void);

static void test_check_char (void);

static void test_check_chars (void);

static void test_check_chars_str (void);

static void test_check_words (void);


//////// Main //////////////////////////////////////////////////////////////////
gint
main (gint    argc,
      gchar **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank/base/string/read/space",
                   test_read_space);

  g_test_add_func ("/crank/base/string/read/word",
                   test_read_word);

  g_test_add_func ("/crank/base/string/read/uint64",
                   test_read_uint64);

  g_test_add_func ("/crank/base/string/read/int64",
                   test_read_int64);

  g_test_add_func ("/crank/base/string/read/double",
                   test_read_double);

  g_test_add_func ("/crank/base/string/read/path",
                   test_read_path);

  g_test_add_func ("/crank/base/string/scan/char",
                   test_scan_char);

  g_test_add_func ("/crank/base/string/scan/word",
                   test_scan_word);

  g_test_add_func ("/crank/base/string/check/char",
                   test_check_char);

  g_test_add_func ("/crank/base/string/check/chars",
                   test_check_chars);

  g_test_add_func ("/crank/base/string/check/chars_str",
                   test_check_chars_str);

  g_test_add_func ("/crank/base/string/check/words",
                   test_check_words);

  g_test_run ();
  return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static void
test_read_space (void)
{

  const gchar *subject = "  A string!";
  guint pos = 0;
  guint space = 0;

  g_assert (crank_str_read_space (subject, &pos, &space));
  g_assert_cmpuint (pos, ==, 2);
  g_assert_cmpuint (space, ==, 2);

  g_assert (!crank_str_read_space (subject, &pos, &space));
  g_assert_cmpuint (pos, ==, 2);
  g_assert_cmpuint (space, ==, 0);

  pos = 3;
  g_assert (crank_str_read_space (subject, &pos, &space));
  g_assert_cmpuint (pos, ==, 4);
  g_assert_cmpuint (space, ==, 1);

  pos = 7;
  g_assert (!crank_str_read_space (subject, &pos, &space));
  g_assert_cmpuint (pos, ==, 7);
  g_assert_cmpuint (space, ==, 0);
}

static void
test_read_word (void)
{
  const gchar *subject =   "A quick brown fox jumps over the lazy dog";
  guint pos =       0;
  gchar *word;

  g_assert (crank_str_read_word (subject, &pos, &word));
  g_assert_cmpuint (pos, ==, 1);
  g_assert_cmpstr (word, ==, "A");
  g_free (word);

  g_assert (!crank_str_read_word (subject, &pos, &word));

  pos = 10;
  g_assert (crank_str_read_word (subject, &pos, &word));
  g_assert_cmpuint (pos, ==, 13);
  g_assert_cmpstr (word, ==, "own");
  g_free (word);

  pos = 20;
  g_assert (crank_str_read_word (subject, &pos, &word));
  g_assert_cmpuint (pos, ==, 23);
  g_assert_cmpstr (word, ==, "mps");
  g_free (word);
}

static void
test_read_uint64 (void)
{
  const gchar *subject =
    "12 seven 1948889382 18446744073709551615 19073283471829393945 007";
  guint pos =       0;
  guint64 value;
  gboolean overflow;

  g_assert (crank_str_read_uint64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 2);
  g_assert_cmpuint (value, ==, 12);
  g_assert_false (overflow);

  pos = 3;
  g_assert (!crank_str_read_uint64 (subject, &pos, &value, &overflow));

  pos = 9;
  g_assert (crank_str_read_uint64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 19);
  g_assert_cmpuint (value, ==, G_GUINT64_CONSTANT(1948889382));
  g_assert_false (overflow);

  pos = 20;
  g_assert (crank_str_read_uint64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 40);
  g_assert_cmpuint (value, ==, G_GUINT64_CONSTANT(18446744073709551615));
  g_assert_false (overflow);

  pos = 41;
  g_assert (crank_str_read_uint64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 61);
  g_assert_cmpuint (value, ==, G_MAXUINT64);
  g_assert_true (overflow);

  pos = 62;
  g_assert (crank_str_read_uint64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 65);
  g_assert_cmpuint (value, ==, 7);
  g_assert_false (overflow);
}

static void
test_read_int64 (void)
{
  const gchar *subject =
    "EE -492 +32948398 555518394892988392 -38293887837878789218884 007";
  guint pos =       0;
  gint64 value;
  gint overflow;

  g_assert (!crank_str_read_int64 (subject, &pos, &value, &overflow));

  pos = 3;
  g_assert (crank_str_read_int64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 7);
  g_assert_cmpint (value, ==, -492);
  g_assert_cmpint (overflow, ==, 0);

  pos = 8;
  g_assert (crank_str_read_int64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 17);
  g_assert_cmpuint (value, ==, G_GINT64_CONSTANT(32948398));
  g_assert_cmpint (overflow, ==, 0);

  pos = 18;
  g_assert (crank_str_read_int64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 36);
  g_assert_cmpuint (value, ==, G_GINT64_CONSTANT(555518394892988392));
  g_assert_cmpint (overflow, ==, 0);

  pos = 37;
  g_assert (crank_str_read_int64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 61);
  g_assert_cmpuint (value, ==, G_MININT64);
  g_assert_cmpint (overflow, <, 0);

  pos = 62;
  g_assert (crank_str_read_int64 (subject, &pos, &value, &overflow));
  g_assert_cmpuint (pos, ==, 65);
  g_assert_cmpuint (value, ==, 7);
  g_assert_cmpint (overflow, ==, 0);
}

static void
test_read_double (void)
{
  const gchar *subject =
    "INF nemo 15 +3.141259 88e52 -1.433e-670 7.49292e-310 1.999e275 1.0e02";

  guint pos;
  gdouble value;
  CrankReadDecResult result;

  pos = 0;
  g_assert (crank_str_read_double (subject, &pos, &value, &result));
  g_assert_cmpuint (pos, ==, 3);
  g_assert (isinf (value) && (0 < value));
  g_assert (result & CRANK_READ_DEC_SYMBOL);

  pos = 4;
  g_assert (!crank_str_read_double (subject, &pos, &value, &result));

  pos = 9;
  g_assert (crank_str_read_double (subject, &pos, &value, &result));
  g_assert_cmpuint (pos, ==, 11);
  crank_assert_cmpfloat (value, ==, 15);

  pos = 12;
  g_assert (crank_str_read_double (subject, &pos, &value, &result));
  g_assert_cmpuint (pos, ==, 21);
  crank_assert_cmpfloat (value, ==, 3.141259);

  pos = 22;
  g_assert (crank_str_read_double (subject, &pos, &value, &result));
  g_assert_cmpuint (pos, ==, 27);
  crank_assert_cmpfloat (value, ==, 8.8e53);

  pos = 28;
  g_assert (crank_str_read_double (subject, &pos, &value, &result));
  g_assert_cmpuint (pos, ==, 39);
  crank_assert_cmpfloat (value, ==, 0);
  g_assert (result & CRANK_READ_DEC_UNDERFLOW);

  pos = 40;
  g_assert (crank_str_read_double (subject, &pos, &value, &result));
  g_assert_cmpuint (pos, ==, 52);
  crank_assert_cmpfloat (value, ==, 7.49292e-310);

  pos = 53;
  g_assert (crank_str_read_double (subject, &pos, &value, &result));
  g_assert_cmpuint (pos, ==, 62);
  crank_assert_cmpfloat (value, ==, 1.999e275);

  pos = 63;
  g_assert (crank_str_read_double (subject, &pos, &value, &result));
  g_assert_cmpuint (pos, ==, 69);
  crank_assert_cmpfloat (value, ==, 1.0e2);
}

static void
test_read_path (void)
{
  gchar *subject = "/home/wsid/Downloads/Incoming/";
  guint pos = 0;
  gchar **pathlist;

  g_assert (crank_str_read_path (subject,
                                 &pos,
                                 &pathlist,
                                 (CrankReadStrFunc)crank_str_read_word,
                                 NULL));

  g_assert_cmpstr (pathlist[0], ==, "");
  g_assert_cmpstr (pathlist[1], ==, "home");
  g_assert_cmpstr (pathlist[2], ==, "wsid");
  g_assert_cmpstr (pathlist[3], ==, "Downloads");
  g_assert_cmpstr (pathlist[4], ==, "Incoming");
  g_assert_cmpstr (pathlist[5], ==, "");
  g_assert_cmpstr (pathlist[6], ==, NULL);

  g_strfreev (pathlist);


  subject = "Documents/projects/crank-system/configure-ac";
  pos = 0;

  g_assert (crank_str_read_path (subject,
                                 &pos,
                                 &pathlist,
                                 (CrankReadStrFunc)crank_str_read_canonical_word,
                                 NULL));

  g_assert_cmpstr (pathlist[0], ==, "Documents");
  g_assert_cmpstr (pathlist[1], ==, "projects");
  g_assert_cmpstr (pathlist[2], ==, "crank-system");
  g_assert_cmpstr (pathlist[3], ==, "configure-ac");
  g_assert_cmpstr (pathlist[4], ==, NULL);

  g_strfreev (pathlist);
}

static void
test_scan_char (void)
{
  const gchar *subject =   "( : )";
  guint pos =       0;
  gchar sym;

  g_assert (crank_str_scan_char (subject, &pos, &sym));
  g_assert_cmpint (sym, ==, '(');

  g_assert (crank_str_scan_char (subject, &pos, &sym));
  g_assert_cmpint (sym, ==, ':');

  g_assert (crank_str_scan_char (subject, &pos, &sym));
  g_assert_cmpint (sym, ==, ')');

  g_assert (!crank_str_scan_char (subject, &pos, &sym));
}

static void
test_scan_word (void)
{
  const gchar *subject =   "Cookie cake strawberry";
  guint pos =       0;
  gchar *word;

  g_assert (crank_str_scan_word (subject, &pos, &word));
  g_assert_cmpstr (word, ==, "Cookie");
  g_free (word);

  g_assert (crank_str_scan_word (subject, &pos, &word));
  g_assert_cmpstr (word, ==, "cake");
  g_free (word);

  g_assert (crank_str_scan_word (subject, &pos, &word));
  g_assert_cmpstr (word, ==, "strawberry");
  g_free (word);
}

static void
test_check_char (void)
{
  const gchar *subject =   "( : )";
  guint pos =       0;

  g_assert (!crank_str_check_char (subject, &pos, ':'));
  g_assert (crank_str_check_char (subject, &pos, '('));
  g_assert (!crank_str_check_char (subject, &pos, ')'));
  g_assert (crank_str_check_char (subject, &pos, ':'));
  g_assert (crank_str_check_char (subject, &pos, ')'));
}

static void
test_check_chars (void)
{
  const gchar *subject =   "( : ) ,";
  guint pos =       0;

  static gchar *chars = "(:)";

  g_assert_cmpint (0, ==, crank_str_check_chars (subject, &pos, chars, 3));
  g_assert_cmpint (1, ==, crank_str_check_chars (subject, &pos, chars, 3));
  g_assert_cmpint (2, ==, crank_str_check_chars (subject, &pos, chars, 3));
  g_assert_cmpint (-1, ==, crank_str_check_chars (subject, &pos, chars, 3));

}

static void
test_check_chars_str (void)
{
  const gchar *subject =   "( : ) ,";
  guint pos =       0;

  static gchar *chars = "(:)";

  g_assert_cmpint (0, ==, crank_str_check_chars_str (subject, &pos, chars));
  g_assert_cmpint (1, ==, crank_str_check_chars_str (subject, &pos, chars));
  g_assert_cmpint (2, ==, crank_str_check_chars_str (subject, &pos, chars));
  g_assert_cmpint (-1, ==, crank_str_check_chars_str (subject, &pos, chars));

}

static void
test_check_words (void)
{
  const gchar *subject = "Apple pie and strawberry shortcake or graph juice";
  guint pos = 0;

  static gchar *fruits[] = {
    "apple",
    "graph",
    "orange",
    "pear",
    "strawberry",
    NULL
  };

  g_assert_cmpint (-1, ==, crank_str_check_words (subject, &pos, fruits, 0));
  g_assert_cmpint (0, ==, crank_str_check_words (subject,
                                                 &pos,
                                                 fruits,
                                                 CRANK_STR_CHECK_CI_IN_LOWERCASE));

  g_assert_cmpint (-1, ==, crank_str_check_words (subject, &pos, fruits, 0));

  pos = 9;
  g_assert_cmpint (-1, ==, crank_str_check_words (subject, &pos, fruits, 0));

  pos = 13;
  g_assert_cmpint (4, ==, crank_str_check_words (subject, &pos, fruits, 0));

  g_assert_cmpint (-1, ==, crank_str_check_words (subject, &pos, fruits, 0));

  pos = 34;
  g_assert_cmpint (-1, ==, crank_str_check_words (subject, &pos, fruits, 0));

  pos = 37;
  g_assert_cmpint (1, ==, crank_str_check_words (subject, &pos, fruits, 0));
  g_assert_cmpint (-1, ==, crank_str_check_words (subject, &pos, fruits, 0));
}
