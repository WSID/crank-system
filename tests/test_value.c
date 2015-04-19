/* Copyright (C) 2015, WSID   */

/* This file is part of Crank System.
 *
 *  Crank System is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  Crank System is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with Crank System.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>

#include "crankbase.h"

static
void		test_value_overwrite	(void);


gint
main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);

  	g_test_add_func ("/wsid/crank/base/value/overwrite",
					test_value_overwrite);

  	g_test_run ();

  	return 0;
}

static void
test_value_overwrite (void)
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

  	crank_value_overwrite_pointer (&value, &value);
  	g_assert (g_value_get_pointer(&value) == &value);

  	g_value_unset (&value);
  	g_object_unref (obj);
  	g_date_free (date);
}
