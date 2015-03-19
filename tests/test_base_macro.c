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

#include <stdarg.h>

#include <glib.h>

#include "crankbase.h"



gint  subject_function_FOREACH_VALIST (gint a, ...);
gint  subject_function_FOREACH_VARARG (gint a, ...);



void  test_macro_FOREACH_VALIST (void);
void  test_macro_FOREACH_VARARG (void);



gint
main (gint   argc,
      gchar *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/wsid/crank/base/macro/foreach/valist",
      test_macro_FOREACH_VALIST);
      
  g_test_add_func ("/wsid/crank/base/macro/foreach/vararg",
      test_macro_FOREACH_VARARG);

  g_test_run ();

  return 0;
}



gint
subject_function_FOREACH_VALIST (gint a, ...)
{
  va_list vararg;
  gint    result;
  
  va_start (vararg, a);
  
  result = a;
  CRANK_FOREACH_VALIST_BEGIN (vararg, gint, e, 0)
  	result += e;
  CRANK_FOREACH_VALIST_END
  
  return result;
}


gint
subject_function_FOREACH_VARARG (gint a, ...)
{
  gint result = a;
  
  CRANK_FOREACH_VARARG_BEGIN (a, gint, e, 0)
    result += e;
  CRANK_FOREACH_VARARG_END
  
  return result;
}



void
test_macro_FOREACH_VALIST (void)
{
  g_assert_cmpint (subject_function_FOREACH_VALIST (3, 2, 5, 1, 0), ==, 11);
}

void
test_macro_FOREACH_VARARG (void)
{
  g_assert_cmpint (subject_function_FOREACH_VARARG (2, 4, 8, 1, 0), ==, 15);
}
