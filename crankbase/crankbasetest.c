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

/**
 * crank_assert_message_eq: (skip)
 * @domain: A logging domain.
 * @file: File name of source file.
 * @line: Line number of source file.
 * @func: Function name of source file.
 * @name_a: Name of argument 'a'
 * @name_b: Name of argument 'b'
 * @str_a: Stringification of argument 'a'
 * @str_b: Stringification of argument 'b'
 *
 * Report that argument 'a' and 'b' are not equal.
 *
 * This function might not return, but abort test instead.
 */
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

/**
 * crank_assert_message_eq_free: (skip)
 * @domain: A logging domain.
 * @file: File name of source file.
 * @line: Line number of source file.
 * @func: Function name of source file.
 * @name_a: Name of argument 'a'
 * @name_b: Name of argument 'b'
 * @str_a: (transfer full): Stringification of argument 'a'
 * @str_b: (transfer full): Stringification of argument 'b'
 *
 * Report that argument 'a' and 'b' are not equal.
 *
 * This function will free @str_a and @str_b which might be allocated strings.
 *
 * This function might not return, but abort test instead.
 */
void
crank_assert_message_eq_free (const gchar *domain,
                              const gchar *file,
                              const gint   line,
                              const gchar *func,
                              const gchar *name_a,
                              const gchar *name_b,
                              gchar       *str_a,
                              gchar       *str_b)
{
  crank_assert_message_eq (domain, file, line, func, name_a, name_b, str_a, str_b);

  g_free (str_a);
  g_free (str_b);
}

/**
 * crank_equal_sarray: (skip)
 * @element_size: Size of a element.
 * @arr_a: Structure array.
 * @arr_length_a: Length of array.
 * @arr_b: Structure array.
 * @arr_length_b: Length of array.
 * @equal_func: (scope call): Equal function.
 *
 * Compare two structure array and checks that twos are equal.
 *
 * Returns: Whether two are same array.
 */
gboolean
crank_equal_sarray (const gsize  element_size,
                    const void  *arr_a,
                    const guint  arr_length_a,
                    const void  *arr_b,
                    const guint  arr_length_b,
                    GEqualFunc   equal_func)
{
  if (arr_length_a == arr_length_b)
    {
      guint i;
      gpointer ptr_a = (gpointer)arr_a;
      gpointer ptr_b = (gpointer)arr_b;

      for (i = 0; i < arr_length_a; i++)
        {
          if (! equal_func (ptr_a, ptr_b))
            return FALSE;

          ptr_a += element_size;
          ptr_b += element_size;
        }

      return TRUE;
    }
  return FALSE;
}

/**
 * crank_equal_parray: (skip)
 * @arr_a: Pointer array.
 * @arr_length_a: Length of array.
 * @arr_b: Pointer array.
 * @arr_length_b: Length of array.
 * @equal_func: (scope call): Equal function.
 *
 * Compare two pointer array and checks that twos are equal.
 *
 * Returns: Whether two are same array.
 */
gboolean
crank_equal_parray (const gpointer *arr_a,
                    const guint     arr_length_a,
                    const gpointer *arr_b,
                    const guint     arr_length_b,
                    GEqualFunc      equal_func)
{
  if (arr_length_a == arr_length_b)
    {
      guint i;
      gpointer* ptr_a = (gpointer*)arr_a;
      gpointer* ptr_b = (gpointer*)arr_b;

      for (i = 0; i < arr_length_a; i++)
        {
          if (! equal_func (*ptr_a, *ptr_b))
            return FALSE;

          ptr_a ++;
          ptr_b ++;
        }

      return TRUE;
    }
  return FALSE;
}

/**
 * crank_equal_delta_sarray: (skip)
 * @element_size: Size of a element.
 * @arr_a: Structure array.
 * @arr_length_a: Length of array.
 * @arr_b: Structure array.
 * @arr_length_b: Length of array.
 * @equal_func: (scope call): Equal function.
 * @delta: Delta, or allowed difference.
 *
 * Compare two structure array and checks that twos are equal.
 *
 * Returns: Whether two are same array.
 */
gboolean
crank_equal_delta_sarray (const gsize          element_size,
                          const void          *arr_a,
                          const guint          arr_length_a,
                          const void          *arr_b,
                          const guint          arr_length_b,
                          CrankEqualDeltaFunc  equal_func,
                          const gfloat         delta)
{
  if (arr_length_a == arr_length_b)
    {
      guint i;
      gpointer ptr_a = (gpointer)arr_a;
      gpointer ptr_b = (gpointer)arr_b;

      for (i = 0; i < arr_length_a; i++)
        {
          if (! equal_func (ptr_a, ptr_b, delta))
            return FALSE;

          ptr_a += element_size;
          ptr_b += element_size;
        }

      return TRUE;
    }
  return FALSE;
}

/**
 * crank_equal_delta_parray: (skip)
 * @arr_a: Pointer array.
 * @arr_length_a: Length of array.
 * @arr_b: Pointer array.
 * @arr_length_b: Length of array.
 * @equal_func: (scope call): Equal function.
 * @delta: Delta, or allowed difference.
 *
 * Compare two pointer array and checks that twos are equal.
 *
 * Returns: Whether two are same array.
 */
gboolean
crank_equal_delta_parray (const gpointer      *arr_a,
                          const guint          arr_length_a,
                          const gpointer      *arr_b,
                          const guint          arr_length_b,
                          CrankEqualDeltaFunc  equal_func,
                          const gfloat         delta)
{
  if (arr_length_a == arr_length_b)
    {
      guint i;
      gpointer* ptr_a = (gpointer*)arr_a;
      gpointer* ptr_b = (gpointer*)arr_b;

      for (i = 0; i < arr_length_a; i++)
        {
          if (! equal_func (*ptr_a, *ptr_b, delta))
            return FALSE;

          ptr_a ++;
          ptr_b ++;
        }

      return TRUE;
    }
  return FALSE;
}

/**
 * crank_equal_glist_arr: (skip)
 * @list: (element-type gpointer): A Pointer list.
 * @arr: Poitner array.
 * @arr_length: Length of array.
 * @equal_func: (scope call): Equal function.
 *
 * Compare a #GList and pointer array and checks that twos are equal.
 *
 * Returns: Whether two has same element in same order.
 */
gboolean
crank_equal_glist_arr (GList          *list,
                       const gpointer *arr,
                       const guint     arr_length,
                       GEqualFunc      equal_func)
{
  GList *iter;
  gpointer *ptr;
  guint i;

  iter = list;
  ptr = (gpointer*) arr;
  for (i = 0; i < arr_length; i++)
    {
      if (iter == NULL)
        return FALSE;

      if (! equal_func (iter->data, *ptr))
        return FALSE;

      ptr ++;
      iter = iter->next;
    }

  return (iter == NULL);
}

/**
 * crank_equal_gptrarray_arr: (skip)
 * @ptrarray: (element-type gpointer): A Pointer list.
 * @arr: Poitner array.
 * @arr_length: Length of array.
 * @equal_func: (scope call): Equal function.
 *
 * Compare a #GList and pointer array and checks that twos are equal.
 *
 * Returns: Whether two has same element in same order.
 */
gboolean
crank_equal_gptrarray_arr (GPtrArray      *ptrarray,
                           const gpointer *arr,
                           const guint     arr_length,
                           GEqualFunc      equal_func)
{
  if (ptrarray == NULL)
    return arr == NULL || arr_length == 0;

  return crank_equal_parray (ptrarray->pdata, ptrarray->len, arr, arr_length, equal_func);
}


/**
 * crank_assert_stringify_sarray: (skip)
 * @arr: Structure array.
 * @arr_length: Length of array.
 * @element_size: Size of elements.
 * @element_stringify: (scope call): Stringifying function.
 * @userdata: (closure): Userdata for @stringify_func.
 *
 * Stringify a structure array with given stringify function. Elements are
 * seaparated by ",\n        " (8 space indentation).
 *
 * Returns: (transfer full): Stringification.
 */
gchar*
crank_assert_stringify_sarray (const void* arr,
                               const guint arr_length,
                               const gsize element_size,
                               CrankStrPtrFunc element_stringify,
                               gpointer userdata)
{
  if (arr_length == 0)
    return NULL;

  GString *str;

  gchar *element_str;
  void *ptr;
  guint i;

  str = g_string_new (NULL);

  ptr = (void*)arr;
  element_str = element_stringify (ptr, userdata);
  g_string_printf (str, "\n        %s", element_str);
  g_free (element_str);

  for (i = 1; i < arr_length; i++)
    {
      ptr += element_size;

      element_str = element_stringify (ptr, userdata);
      g_string_append_printf (str, ",\n        %s", element_str);
      g_free (element_str);

    }

  return g_string_free (str, FALSE);
}

/**
 * crank_assert_stringify_parray: (skip)
 * @arr: (array length=arr_length): Pointer array.
 * @arr_length: Length of array.
 * @element_stringify: (scope call): Stringifying function.
 * @userdata: (closure): Userdata for @stringify_func.
 *
 * Stringify a pointer array with given stringify function. Elements are
 * seaparated by ",\n        " (8 space indentation).
 *
 * Returns: (transfer full): Stringification.
 */
gchar*
crank_assert_stringify_parray (const gpointer  *arr,
                               const guint      arr_length,
                               CrankStrPtrFunc  element_stringify,
                               gpointer         userdata)
{
  if (arr_length == 0)
    return NULL;

  GString *str;

  gchar *element_str;
  gpointer *ptr;
  guint i;

  str = g_string_new (NULL);

  ptr = (void*)arr;
  element_str = element_stringify (*ptr, userdata);
  g_string_printf (str, "\n        %s", element_str);
  g_free (element_str);

  for (i = 0; i < arr_length; i++)
    {
      ptr ++;

      element_str = element_stringify (*ptr, userdata);
      g_string_append_printf (str, ",\n        %s", element_str);
      g_free (element_str);
    }

  return g_string_free (str, FALSE);
}

/**
 * crank_assert_stringify_glist: (skip)
 * @list: (element-type gpointer): GList to strinigify.
 * @element_stringify: (scope call): Stringifying function.
 * @userdata: (closure): Userdata for @stringify_func.
 *
 * Stringify a #GList with given stringify function. Elements are seaparated by
 * ",\n        " (8 space indentation).
 *
 * Returns: (transfer full): Stringification.
 */
gchar*
crank_assert_stringify_glist (GList           *list,
                              CrankStrPtrFunc  element_stringify,
                              gpointer         userdata)
{
  if (list == NULL)
    return NULL;

  GString *str;

  gchar *element_str;
  GList *iter;

  str = g_string_new (NULL);

  iter = list;
  element_str = element_stringify (iter->data, userdata);
  g_string_printf (str, "\n        %s", element_str);
  g_free (element_str);

  for (iter = iter->next; iter != NULL; iter = iter->next)
    {
      element_str = element_stringify (iter->data, userdata);
      g_string_append_printf (str, ",\n        %s", element_str);
      g_free (element_str);
    }

  return g_string_free (str, FALSE);
}

/**
 * crank_assert_stringify_gptrarray: (skip)
 * @ptrarray: (element-type gpointer): GList to strinigify.
 * @element_stringify: (scope call): Stringifying function.
 * @userdata: (closure): Userdata for @stringify_func.
 *
 * Stringify a #GList with given stringify function. Elements are seaparated by
 * ",\n        " (8 space indentation).
 *
 * Returns: (transfer full): Stringification.
 */
gchar*
crank_assert_stringify_gptrarray (GPtrArray       *ptrarray,
                                  CrankStrPtrFunc  element_stringify,
                                  gpointer         userdata)
{
  if (ptrarray == NULL)
    return NULL;

  return crank_assert_stringify_parray (ptrarray->pdata, ptrarray->len, element_stringify, userdata);
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
