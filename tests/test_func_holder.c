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


gboolean  subject_function (gint a, gint b);


void  test_func_holder_new (void);


gint
main (gint   argc,
      gchar *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/wsid/crank/base/funcholder",
      test_func_holder_new);

  g_test_run ();

  return 0;
}



gboolean
subject_function (gint a, gint b)
{
  return (a % b) == 0;
}



void
test_func_holder_new (void)
{
  
  CrankFuncHolder* holder = crank_func_holder_new (
      G_CALLBACK(subject_function), NULL,
      G_TYPE_BOOLEAN,
      G_TYPE_INT,
      G_TYPE_INT);
  
  crank_func_holder_free (holder);
  
}
