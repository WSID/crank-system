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
gint  subject_function_FOREACH_VALIST_DO (gint a, ...);
gint  subject_function_FOREACH_VARARG_DO (gint a, ...);


void	test_macro_ARRAY_DUP (void);
void	test_macro_ARRAY_CMP (void);
void	test_macro_ARRAY_ADD (void);
void	test_macro_ARRAY_FILL (void);

void	test_macro_FOREACH_RANGE (void);
void	test_macro_FOREACH_IRANGE (void);
void	test_macro_FOREACH_ARRAY (void);
void	test_macro_FOREACH_VALIST (void);
void	test_macro_FOREACH_VARARG (void);
void	test_macro_FOREACH_GLIST (void);
void	test_macro_FOREACH_G_PTR_ARRAY (void);

void	test_macro_FOREACH_RANGE_DO (void);
void	test_macro_FOREACH_IRANGE_DO (void);
void	test_macro_FOREACH_ARRAY_DO (void);
void	test_macro_FOREACH_VALIST_DO (void);
void	test_macro_FOREACH_VARARG_DO (void);
void	test_macro_FOREACH_GLIST_DO (void);
void	test_macro_FOREACH_G_PTR_ARRAY_DO (void);



gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/wsid/crank/base/macro/arraydup",
		test_macro_ARRAY_DUP);
		
	g_test_add_func ("/wsid/crank/base/macro/arraycmp",
		test_macro_ARRAY_CMP);
		
	g_test_add_func ("/wsid/crank/base/macro/arrayadd",
		test_macro_ARRAY_ADD);
		
	g_test_add_func ("/crank/base/macro/array/fill",
		test_macro_ARRAY_FILL);

  	g_test_add_func ("/crank/base/macro/foreach/range",
		test_macro_FOREACH_RANGE);

  	g_test_add_func ("/crank/base/macro/foreach/irange",
		test_macro_FOREACH_IRANGE);

	g_test_add_func ("/wsid/crank/base/macro/foreach/array",
		test_macro_FOREACH_ARRAY);

	g_test_add_func ("/wsid/crank/base/macro/foreach/valist",
		test_macro_FOREACH_VALIST);

	g_test_add_func ("/wsid/crank/base/macro/foreach/vararg",
		test_macro_FOREACH_VARARG);
	
	g_test_add_func ("/crank/base/macro/foreach/glist",
		test_macro_FOREACH_GLIST);
		
	g_test_add_func ("/wsid/crank/base/macro/foreach/g_ptr_array",
		test_macro_FOREACH_G_PTR_ARRAY);
		
		

  	g_test_add_func ("/crank/base/macro/foreach/range_do",
		test_macro_FOREACH_RANGE_DO);

  	g_test_add_func ("/crank/base/macro/foreach/irange_do",
		test_macro_FOREACH_IRANGE_DO);

	g_test_add_func ("/wsid/crank/base/macro/foreach/array_do",
		test_macro_FOREACH_ARRAY_DO);
	
	g_test_add_func ("/wsid/crank/base/macro/foreach/valist_do",
		test_macro_FOREACH_VALIST_DO);

	g_test_add_func ("/wsid/crank/base/macro/foreach/vararg_do",
		test_macro_FOREACH_VARARG_DO);
		
	g_test_add_func ("/crank/base/macro/foreach/glist",
		test_macro_FOREACH_GLIST_DO);

	g_test_add_func ("/wsid/crank/base/macro/foreach/g_ptr_array_do",
		test_macro_FOREACH_G_PTR_ARRAY_DO);

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


gint
subject_function_FOREACH_VALIST_DO (gint a, ...)
{
  va_list vararg;
  gint    result;
  
  va_start (vararg, a);
  
  result = a;
  CRANK_FOREACH_VALIST_DO (vararg, gint, e, 0, {result += e;})
  
  return result;
}


gint
subject_function_FOREACH_VARARG_DO (gint a, ...)
{
  gint result = a;
  
  CRANK_FOREACH_VARARG_DO (a, gint, e, 0, {result += e;})
  
  return result;
}


void
test_macro_ARRAY_DUP (void)
{
	guint subject[4] = {1, 9, 9, 8};

	guint* subject_dup = CRANK_ARRAY_DUP (subject, guint, 4);

	g_assert_cmpint (subject[0], ==, subject_dup[0]);
	g_assert_cmpint (subject[1], ==, subject_dup[1]);
	g_assert_cmpint (subject[2], ==, subject_dup[2]);
	g_assert_cmpint (subject[3], ==, subject_dup[3]);

	g_free (subject_dup);
}

void
test_macro_ARRAY_CMP (void)
{
	guint subject_a[4] = {1, 9, 9, 8};
	guint subject_b[4] = {1, 4, 0, 5};

	g_assert (CRANK_ARRAY_CMP (subject_a, subject_b, guint, 4) > 0);

	g_assert (CRANK_ARRAY_CMP (subject_a, subject_a, guint, 4) == 0);
}

void
test_macro_ARRAY_ADD (void)
{
	gint*	subject = NULL;
	guint	nsubject = 0;
	guint	subject_alloc = 0;

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

void
test_macro_ARRAY_FILL (void)
{
	gint	subject[3];

	CRANK_ARRAY_FILL (subject, gint, 3, 20);

	g_assert_cmpint (subject[0], ==, 20);
	g_assert_cmpint (subject[1], ==, 20);
	g_assert_cmpint (subject[2], ==, 20);
}


void
test_macro_FOREACH_RANGE (void)
{
	gint	fact = 1;

	CRANK_FOREACH_RANGE_BEGIN (gint, i, 2, 7, 1)
		fact *= i;
	CRANK_FOREACH_RANGE_END

	g_assert_cmpint (fact, ==, 720);
}

void
test_macro_FOREACH_IRANGE (void)
{
	gint	sum = 0;

  	CRANK_FOREACH_IRANGE_BEGIN (i, 10)
		sum += i;
 	CRANK_FOREACH_IRANGE_END

  	g_assert_cmpint (sum, ==, 45);
}

void
test_macro_FOREACH_ARRAY (void)
{
	gint	subject[7] = {1, 1, 2, 3, 5, 8, 13};
	gint	sum = 0;

	CRANK_FOREACH_ARRAY_BEGIN(subject, gint, e, 7)
		sum += e;
	CRANK_FOREACH_ARRAY_END

	g_assert_cmpint (sum, ==, 33);
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

void
test_macro_FOREACH_GLIST (void)
{
	GList*	subject = NULL;
	gint	sum = 0;
	
	subject = g_list_append (subject, GINT_TO_POINTER (3));
	subject = g_list_append (subject, GINT_TO_POINTER (4));
	subject = g_list_append (subject, GINT_TO_POINTER (1));
	subject = g_list_append (subject, GINT_TO_POINTER (7));
	
	CRANK_FOREACH_GLIST_BEGIN (subject, gpointer, e)
		sum += GPOINTER_TO_INT(e);
	CRANK_FOREACH_GLIST_END
	
	g_assert_cmpint (sum, ==, 15);
}

void
test_macro_FOREACH_G_PTR_ARRAY (void)
{
	// 일단 포인터 형에 정수를 담습니다.
	GPtrArray* subject;
	gint sum;
	
	subject = g_ptr_array_new ();
	sum = 0;
	
	g_ptr_array_add(subject, GINT_TO_POINTER(2));
	g_ptr_array_add(subject, GINT_TO_POINTER(3));
	g_ptr_array_add(subject, GINT_TO_POINTER(5));
	g_ptr_array_add(subject, GINT_TO_POINTER(7));
	g_ptr_array_add(subject, GINT_TO_POINTER(11));
	
	CRANK_FOREACH_G_PTR_ARRAY_BEGIN(subject, gpointer, e)
		sum += GPOINTER_TO_INT(e);
	CRANK_FOREACH_G_PTR_ARRAY_END
	
	g_assert_cmpint (sum, ==, 28);
}


void
test_macro_FOREACH_RANGE_DO (void)
{
	gint	fact = 1;

	CRANK_FOREACH_RANGE_DO (gint, i, 2, 7, 1, fact *= i;)



	g_assert_cmpint (fact, ==, 720);
}

void
test_macro_FOREACH_IRANGE_DO (void)
{
	gint	sum = 0;

  	CRANK_FOREACH_IRANGE_DO (i, 10, sum += i;)

  	g_assert_cmpint (sum, ==, 45);
}
void
test_macro_FOREACH_ARRAY_DO (void)
{
	gint	subject[7] = {1, 1, 2, 3, 5, 8, 13};
	gint	sum = 0;
	
	CRANK_FOREACH_ARRAY_DO (subject, gint, e, 7, {sum += e;})
	
	g_assert_cmpint (sum, ==, 33);
}

void
test_macro_FOREACH_VALIST_DO (void)
{
  g_assert_cmpint (subject_function_FOREACH_VALIST_DO (18, 3, 7, 2, 4, 0), ==, 34);
}

void
test_macro_FOREACH_VARARG_DO (void)
{
  g_assert_cmpint (subject_function_FOREACH_VARARG_DO (9, 6, 3, 0), ==, 18);
}

void
test_macro_FOREACH_G_PTR_ARRAY_DO (void)
{
	// 일단 포인터 형에 정수를 담습니다.
	GPtrArray* subject;
	gint sum;
	
	subject = g_ptr_array_new ();
	sum = 0;
	
	g_ptr_array_add(subject, GINT_TO_POINTER(2));
	g_ptr_array_add(subject, GINT_TO_POINTER(3));
	g_ptr_array_add(subject, GINT_TO_POINTER(5));
	g_ptr_array_add(subject, GINT_TO_POINTER(7));
	g_ptr_array_add(subject, GINT_TO_POINTER(11));
	
	CRANK_FOREACH_G_PTR_ARRAY_DO(subject, gpointer, e, {sum += GPOINTER_TO_INT(e);})
	
	g_assert_cmpint (sum, ==, 28);
}

void
test_macro_FOREACH_GLIST_DO (void)
{
	GList*	subject = NULL;
	gint	sum = 0;
	
	subject = g_list_append (subject, GINT_TO_POINTER (3));
	subject = g_list_append (subject, GINT_TO_POINTER (4));
	subject = g_list_append (subject, GINT_TO_POINTER (1));
	subject = g_list_append (subject, GINT_TO_POINTER (7));
	
	CRANK_FOREACH_GLIST_DO (subject, gpointer, e, {sum += GPOINTER_TO_INT(e);})
	
	g_assert_cmpint (sum, ==, 15);
}
