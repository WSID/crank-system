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
#include <glib-object.h>

#include "crankfunction.h"
#include "crankbasetest.h"

//////// Private structures ////////////////////////////////////////////////////
typedef struct _CrankTestMetaTimeout {
  GTestFunc func;
  guint64 time;
} CrankTestMetaTimeout;


//////// Private functions /////////////////////////////////////////////////////
static void crank_test_meta_expected_fail (gconstpointer userdata);

static void crank_test_meta_timeout (gconstpointer userdata);


//////// Adding meta test-case /////////////////////////////////////////////////
/**
 * crank_test_add_func_expected_fail: (skip)
 * @path: A Test path.
 * @func: A testing function, supposed to fail.
 *
 * Adds a test case that checks given test fails.
 *
 * If given function does not fail, then the test is considered to be failed.
 */
void
crank_test_add_func_expected_fail (const gchar *path,
                                   GTestFunc    func)
{
  gchar *func_path = g_strdup_printf ("/_crank/subprocess/efail%s", path);

  g_test_add_func (func_path, func);
  g_test_add_data_func_full (path,
                             func_path,
                             crank_test_meta_expected_fail,
                             g_free);
}

/**
 * crank_test_add_func_timeout: (skip)
 * @path: A Test path.
 * @func: A testing function, supposed to be done in time.
 * @time: Time in microseconds.
 *
 * Adds a test case that checks given test done in time.
 *
 * If given function does not end in time, then the test is considered to be failed.
 */
void
crank_test_add_func_timeout (const gchar  *path,
                             GTestFunc     func,
                             const guint64 time)
{
  CrankTestMetaTimeout *meta = g_new (CrankTestMetaTimeout, 1);

  meta->func = func;
  meta->time = time;

  g_test_add_data_func_full (path, meta, crank_test_meta_timeout, g_free);
}


//////// Assertion helper functions ////////////////////////////////////////////

void
crank_assert_message_eq (const gchar *domain,
                         const gchar *file,
                         const gint   line,
                         const gchar *func,
                         const gchar *name_a,
                         const gchar *name_b,
                         const gchar *str_a,
                         const gchar *str_b)
{
  GString *msg = g_string_new (NULL);

  g_string_printf (msg, "%s and %s are not equal.\n", name_a, name_b);
  g_string_append_printf (msg, "    %s\t: %s\n", name_a, str_a);
  g_string_append_printf (msg, "    %s\t: %s", name_b, str_b);

  g_assertion_message (domain, file, line, func, msg->str);

  g_string_free (msg, TRUE);
}

gchar*
crank_assert_stringify_sarray (const void* arr,
                               const guint arr_length,
                               const gsize element_size,
                               CrankStrPtrFunc stringify_func,
                               gpointer userdata)
{
  if (arr_length == 0)
    return NULL;

  GString *str;

  void *ptr;
  gchar *element_str;
  guint i;

  ptr = (void*)arr;
  element_str = stringify_func (ptr, userdata);

  str = g_string_new (element_str);
  g_free (element_str);

  for (i = 1; i < arr_length; i++)
    {
      ptr += element_size;
      element_str = stringify_func (ptr, userdata);
      g_string_append_printf (str, ",\n    %s", element_str);
      g_free (element_str);
    }

  return g_string_free (str, FALSE);
}

gchar*
crank_assert_stringify_parray (const gpointer  *arr,
                               const guint      arr_length,
                               CrankStrPtrFunc  stringify_func,
                               gpointer         userdata)
{
  if (arr_length == 0)
    return NULL;

  GString *str;

  gpointer *ptr;
  gchar *element_str;
  guint i;

  ptr = (void*)arr;
  element_str = stringify_func (*ptr, userdata);

  str = g_string_new (element_str);
  g_free (element_str);

  for (i = 1; i < arr_length; i++)
    {
      ptr ++;
      element_str = stringify_func (*ptr, userdata);
      g_string_append_printf (str, ",\n    %s", element_str);
      g_free (element_str);
    }

  return g_string_free (str, FALSE);
}


//////// Meta testcases ////////////////////////////////////////////////////////
static void
crank_test_meta_expected_fail (gconstpointer userdata)
{
  gchar *efail_path = (gchar*) userdata;

  g_test_trap_subprocess (efail_path, 0, G_TEST_SUBPROCESS_INHERIT_STDERR);
  g_test_trap_assert_failed ();
}

static void
crank_test_meta_timeout (gconstpointer userdata)
{
  CrankTestMetaTimeout *meta = (CrankTestMetaTimeout*) userdata;

  if (g_test_subprocess ())
    {
      meta->func ();
    }
  else
    {
      g_test_trap_subprocess (NULL, meta->time,
                              G_TEST_SUBPROCESS_INHERIT_STDOUT |
                              G_TEST_SUBPROCESS_INHERIT_STDERR);

      g_test_trap_assert_passed ();
    }
}
