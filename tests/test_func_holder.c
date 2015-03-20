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


void	test_func_type_new (void);
void	test_func_holder_new (void);


gint
main (gint   argc,
      gchar *argv[])
{
  g_test_init (&argc, &argv, NULL);
	
  g_test_add_func ("/wsid/crank/base/functype",
      test_func_type_new);

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
test_func_type_new (void)
{
	GType*  param_types;
	guint   param_length;
  
	CrankFuncType* ftype = crank_func_type_new (
		G_TYPE_BOOLEAN,
		G_TYPE_INT,
		G_TYPE_CHAR,
		G_TYPE_NONE);

	g_assert (G_TYPE_BOOLEAN == crank_func_type_get_return_type (ftype));
	g_assert (G_TYPE_INT == crank_func_type_get_param_type (ftype, 0));
	g_assert (G_TYPE_CHAR == crank_func_type_get_param_type (ftype, 1));
	g_assert (G_TYPE_NONE == crank_func_type_get_param_type (ftype, 2));

	g_assert (2 == crank_func_type_get_nparam_types (ftype));

	// Tests crank_func_type_get_param_types ()
	param_types = crank_func_type_get_param_types(ftype, &param_length);

	g_assert_cmpuint (2, ==, param_length);
	g_assert (G_TYPE_INT == param_types[0]);
	g_assert (G_TYPE_CHAR == param_types[1]);

	crank_func_type_unref (ftype);
  
}

void
test_func_holder_new (void)
{
  
  CrankFuncHolder* holder = crank_func_holder_new (
      G_CALLBACK(subject_function), NULL,
      G_TYPE_BOOLEAN,
      G_TYPE_INT,
      G_TYPE_INT,
      G_TYPE_NONE);
  
  crank_func_holder_free (holder);
  
}
