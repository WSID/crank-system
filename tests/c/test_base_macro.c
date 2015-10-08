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

static void test_macro_ARRAY_DUP (void);
static void test_macro_ARRAY_CMP (void);
static void test_macro_ARRAY_ADD (void);
static void test_macro_ARRAY_FILL (void);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint    argc,
      gchar **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank/base/macro/arraydup",
                   test_macro_ARRAY_DUP);

  g_test_add_func ("/crank/base/macro/arraycmp",
                   test_macro_ARRAY_CMP);

  g_test_add_func ("/crank/base/macro/arrayadd",
                   test_macro_ARRAY_ADD);

  g_test_add_func ("/crank/base/macro/array/fill",
                   test_macro_ARRAY_FILL);


  g_test_run ();

  return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static void
test_macro_ARRAY_DUP (void)
{
  guint subject[4] = {1, 9, 9, 8};

  guint *subject_dup = CRANK_ARRAY_DUP (subject, guint, 4);

  g_assert_cmpint (subject[0], ==, subject_dup[0]);
  g_assert_cmpint (subject[1], ==, subject_dup[1]);
  g_assert_cmpint (subject[2], ==, subject_dup[2]);
  g_assert_cmpint (subject[3], ==, subject_dup[3]);

  g_free (subject_dup);
}

static void
test_macro_ARRAY_CMP (void)
{
  guint subject_a[4] = {1, 9, 9, 8};
  guint subject_b[4] = {1, 4, 0, 5};

  g_assert (CRANK_ARRAY_CMP (subject_a, subject_b, guint, 4) > 0);

  g_assert (CRANK_ARRAY_CMP (subject_a, subject_a, guint, 4) == 0);
}

static void
test_macro_ARRAY_ADD (void)
{
  gint *subject = NULL;
  guint nsubject = 0;
  guint subject_alloc = 0;

  CRANK_ARRAY_ADD (gint, subject, nsubject, subject_alloc, 3);
  CRANK_ARRAY_ADD (gint, subject, nsubject, subject_alloc, 8);
  CRANK_ARRAY_ADD (gint, subject, nsubject, subject_alloc, 5);
  CRANK_ARRAY_ADD (gint, subject, nsubject, subject_alloc, 2);

  g_assert_cmpint (subject[0], ==, 3);
  g_assert_cmpint (subject[1], ==, 8);
  g_assert_cmpint (subject[2], ==, 5);
  g_assert_cmpint (subject[3], ==, 2);

  g_assert_cmpint (nsubject, ==, 4);
  g_assert_cmpint (nsubject, <=, subject_alloc);

  g_free (subject);
}

static void
test_macro_ARRAY_FILL (void)
{
  gint subject[3];

  CRANK_ARRAY_FILL (subject, gint, 3, 20);

  g_assert_cmpint (subject[0], ==, 20);
  g_assert_cmpint (subject[1], ==, 20);
  g_assert_cmpint (subject[2], ==, 20);
}


