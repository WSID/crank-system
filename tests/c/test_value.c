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

static void		test_value_overwrite (void);

static void		test_value_overwrite_value (void);

static void		test_value_array_overwrite (void);

static void		test_value_array_overwrite_array (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);

  	g_test_add_func ("/crank/base/value/overwrite",
					test_value_overwrite);
  	g_test_add_func ("/crank/base/value/overwrite_value",
					test_value_overwrite_value);
					
  	g_test_add_func ("/crank/base/value/array/overwrite",
					test_value_array_overwrite);
  	g_test_add_func ("/crank/base/value/array/overwrite_array",
					test_value_array_overwrite_array);

  	g_test_run ();
  	return 0;
}

//////// Definition ////////////////////////////////////////////////////////////

static void
test_value_overwrite (void)
{
	GValue	value_a = G_VALUE_INIT;
  	GValue	value_b = G_VALUE_INIT;

  	g_value_init (&value_b, G_TYPE_BOOLEAN);

  	g_value_set_boolean (&value_b, TRUE);
  	crank_value_overwrite (&value_a, &value_b);

  	g_assert_true (g_value_get_boolean (&value_a));

  	g_value_unset (&value_b);
  	g_value_init (&value_b, G_TYPE_INT);
  	g_value_set_int (&value_b, 42);
  	crank_value_overwrite (&value_a, &value_b);

  	g_assert_cmpint (g_value_get_int (&value_a), ==, 42);
}

static void
test_value_overwrite_value (void)
{
  	GValue value = G_VALUE_INIT;
  	GObject* obj = g_object_new (G_TYPE_OBJECT, NULL);
  	GDate*	date = g_date_new_dmy (26, G_DATE_OCTOBER, 1990);

	crank_value_overwrite_boolean (&value, TRUE);
  	g_assert_true (g_value_get_boolean (&value));

  	crank_value_overwrite_int (&value, 42);
  	g_assert_cmpint (g_value_get_int (&value), ==, 42);

  	crank_value_overwrite_string (&value, "Where is he!??");
  	g_assert_cmpstr (g_value_get_string (&value), ==, "Where is he!??");

  	crank_value_overwrite_object (&value, obj);
	g_assert (g_value_get_object (&value) == obj);

  	crank_value_overwrite_boxed (&value, G_TYPE_DATE, date);
	g_assert (g_date_compare ((GDate*)g_value_get_boxed (&value), date) == 0);

  	crank_value_overwrite_pointer (&value, G_TYPE_POINTER, &value);
  	g_assert (g_value_get_pointer(&value) == &value);

  	g_value_unset (&value);
  	g_object_unref (obj);
  	g_date_free (date);
}

static void
test_value_array_overwrite (void)
{
	GValue values[3] = { {0} };
	
	GValue value_a = {0};
	GValue value_b = {0};
	GValue value_c = {0};
	
	g_value_init (&value_a, G_TYPE_BOOLEAN);
	g_value_init (&value_b, G_TYPE_INT);
	g_value_init (&value_c, G_TYPE_STRING);
	
	g_value_set_boolean (&value_a, TRUE);
	g_value_set_int (&value_b, 42);
	g_value_set_string (&value_c, "Applepie");
	
	crank_value_array_overwrite (values, 3, &value_a, &value_b, &value_c);
	
	g_assert (G_VALUE_TYPE (values + 0) == G_TYPE_BOOLEAN);
	g_assert (G_VALUE_TYPE (values + 1) == G_TYPE_INT);
	g_assert (G_VALUE_TYPE (values + 2) == G_TYPE_STRING);
	
	g_assert (g_value_get_boolean (values + 0) == TRUE);
	g_assert_cmpint (g_value_get_int (values + 1), ==, 42);
	g_assert_cmpstr (g_value_get_string (values + 2), ==, "Applepie");
	
	crank_value_array_unset (values, 3);
	g_value_unset (&value_a);
	g_value_unset (&value_b);
	g_value_unset (&value_c);
}

static void
test_value_array_overwrite_array (void)
{
	GValue values[3] = { {0} };
	
	GValue values_other[3] = { {0} };
	
	g_value_init (values_other + 0, G_TYPE_BOOLEAN);
	g_value_init (values_other + 1, G_TYPE_INT);
	g_value_init (values_other + 2, G_TYPE_STRING);
	
	g_value_set_boolean (values_other + 0, TRUE);
	g_value_set_int (values_other + 1, 42);
	g_value_set_string (values_other + 2, "Applepie");
	
	crank_value_array_overwrite_array (values, 3, values_other);
	
	g_assert (G_VALUE_TYPE (values + 0) == G_TYPE_BOOLEAN);
	g_assert (G_VALUE_TYPE (values + 1) == G_TYPE_INT);
	g_assert (G_VALUE_TYPE (values + 2) == G_TYPE_STRING);
	
	g_assert (g_value_get_boolean (values + 0) == TRUE);
	g_assert_cmpint (g_value_get_int (values + 1), ==, 42);
	g_assert_cmpstr (g_value_get_string (values + 2), ==, "Applepie");
	
	crank_value_array_unset (values, 3);
	g_value_unset (values_other + 0);
	g_value_unset (values_other + 1);
	g_value_unset (values_other + 2);
}
