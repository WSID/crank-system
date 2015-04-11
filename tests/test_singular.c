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

//////// 시험에 사용될 클래스입니다. ///////////////////////////////////////////

enum TestSubjectProps {
	DUMMY,
	TEST_SUBJECT_PROPS_INT_ITEM,
	TEST_SUBJECT_PROPS_FIRST_CONSTRUCT_TIMES
};

typedef struct _TestSubjectPrivate {
	gint				int_item;
	gint				first_construct_times;
} TestSubjectPrivate;

typedef struct _TestSubject {
	CrankSingular		parent_instance;
	TestSubjectPrivate*	priv;
} TestSubject;

typedef struct _TestSubjectClass {
	CrankSingularClass	parent_class;
} TestSubjectClass;


//////// 타입 매크로

#define TEST_TYPE_SUBJECT	(test_subject_get_type())
#define TEST_SUBJECT(i)		(G_TYPE_CHECK_INSTANCE_CAST((i), TEST_TYPE_SUBJECT, TestSubject))
#define TEST_IS_SUBJECT(i)	(G_TYPE_CHECK_INSTANCE_TYPE((i), TEST_TYPE_SUBJECT))
#define TEST_SUBJECT_CLASS(c)		(G_TYPE_CHECK_CLASS_CAST((c), TEST_TYPE_SUBJECT, TestSubjectClass))
#define TEST_IS_SUBJECT_CLASS(c)	(G_TYPE_CHECK_CLASS_TYPE((c), TEST_TYPE_SUBJECT))
#define TEST_SUBJECT_GET_CLASS(i)	(G_TYPE_INSTANCE_GET_CLASS((i), TEST_TYPE_SUBJECT, TestSubjectClass))


//////// 시험에 사용될 클래스 구현 /////////////////////////////////////////////

G_DEFINE_TYPE_WITH_CODE(TestSubject, test_subject, CRANK_TYPE_SINGULAR, {
	G_ADD_PRIVATE(TestSubject);
})

//////// GObject 가상 함수들

static void
test_subject_set_property (	GObject*		self_gobject,
							guint			prop_id,
							const GValue*	value,
							GParamSpec*		pspec			)
{
	TestSubject*	self;

	self = TEST_SUBJECT(self_gobject);

	switch (prop_id) {
		case TEST_SUBJECT_PROPS_INT_ITEM:
			self->priv->int_item = g_value_get_int (value);
			break;
			
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(self_gobject, prop_id, pspec);
	}
}

static void
test_subject_get_property (	GObject*	self_gobject,
							guint		prop_id,
							GValue*		value,
							GParamSpec*	pspec			)
{
	TestSubject*	self;

	self = TEST_SUBJECT(self_gobject);

	switch (prop_id) {
		case TEST_SUBJECT_PROPS_INT_ITEM:
			g_value_set_int (value, self->priv->int_item);
			break;

		case TEST_SUBJECT_PROPS_FIRST_CONSTRUCT_TIMES:
			g_value_set_int (value, self->priv->first_construct_times);
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(self_gobject, prop_id, pspec);
	}
}

//////// CrankSingular 함수들

static void
test_subject_first_construct (	CrankSingular*			self_crank_singular,
								guint					n_construct_props,
								GObjectConstructParam	construct_props		)
{
	TestSubject* self = TEST_SUBJECT (self_crank_singular);
	
	g_usleep (1000); // 0.01초도 흔들기 충분하다.
	
	self->priv->first_construct_times++;
}


//////// GTypeInstance 함수들

static void
test_subject_init (TestSubject* i) {
	i->priv = G_TYPE_INSTANCE_GET_PRIVATE (i, TEST_TYPE_SUBJECT, TestSubjectPrivate);
	
	i->priv->first_construct_times = 0;
}

static void
test_subject_class_init (TestSubjectClass* c) {
	GObjectClass* 		c_g_object;
	CrankSingularClass*	c_crank_singular;

	c_g_object = G_OBJECT_CLASS(c);

	c_g_object->set_property = test_subject_set_property;
	c_g_object->get_property = test_subject_get_property;

	g_object_class_install_property (c_g_object,
			TEST_SUBJECT_PROPS_INT_ITEM,
			g_param_spec_int (	"int-item",
								"int item",
								"Item to see functions are effectivetly affecting singular instance",
								G_MININT,	G_MAXINT,	0,
								G_PARAM_STATIC_STRINGS |
								G_PARAM_READWRITE |
								G_PARAM_CONSTRUCT	)	);

	g_object_class_install_property (c_g_object,
			TEST_SUBJECT_PROPS_FIRST_CONSTRUCT_TIMES,
			g_param_spec_boolean (	"first-construct-times",
									"First Construct times",
									"Item to see first_construct() is working!",
									FALSE,
									G_PARAM_STATIC_STRINGS |
									G_PARAM_READABLE	)	);

	c_crank_singular = CRANK_SINGULAR_CLASS(c);
	
	c_crank_singular->first_construct = test_subject_first_construct;
}

//////// 외부 공개 함수들

gint
test_subject_get_int_item (TestSubject*	subject)
{
	return subject->priv->int_item;
}

void
test_subject_set_int_item (TestSubject*	subject, gint int_item)
{
	subject->priv->int_item = int_item;
}


gint
test_subject_get_first_construct_times (TestSubject*	subject)
{
	return subject->priv->first_construct_times;
}


TestSubject*
test_subject_new (gint	int_item) {
	return TEST_SUBJECT(
		g_object_new (TEST_TYPE_SUBJECT, "int-item", int_item, NULL)	);
}




//////// 테스트 케이스 /////////////////////////////////////////////////////////

void		test_singular_new				(void);
void		test_singular_has				(void);
void		test_singular_get				(void);
void		test_singular_first_construct	(void);
void		test_singular_thread_construct	(void);

TestSubject*	test_singular_thread_construct_func (gpointer userdata);


gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);

	g_test_add_func ("/wsid/crank/base/singular/new",
			test_singular_new);
			
	g_test_add_func ("/wsid/crank/base/singular/has",
			test_singular_has);

	g_test_add_func ("/wsid/crank/base/singular/get",
			test_singular_get);
			
	g_test_add_func ("/wsid/crank/base/singular/first_construct",
			test_singular_first_construct);

	g_test_add_func ("/wsid/crank/base/singular/thread_construct",
			test_singular_thread_construct);
			
	g_test_run ();

	return 0;
}

void
test_singular_new (void)
{
	TestSubject*	singular_a;
	TestSubject*	singular_b;

	if (g_test_subprocess()) {
		singular_a = test_subject_new (1);
		singular_b = test_subject_new (2);

		g_assert (singular_a == singular_b);
		g_assert_cmpint (test_subject_get_int_item (singular_b), ==, 1);

		return;
	}

	g_test_trap_subprocess (NULL, 0, 0);
	g_test_trap_assert_passed ();
}

void
test_singular_has (void)
{
	TestSubject*	singular;
	
	if (g_test_subprocess()) {
		g_assert_false (crank_singular_has (TEST_TYPE_SUBJECT));
		
		singular = test_subject_new (10);
		
		g_assert_true (crank_singular_has (TEST_TYPE_SUBJECT));
		
		return;
	}
	
	g_test_trap_subprocess (NULL, 0, 0);
	g_test_trap_assert_passed ();
}

void
test_singular_get (void)
{
	TestSubject*	singular_a;
	TestSubject*	singular_b;

	if (g_test_subprocess()) {
		singular_a = (TestSubject*) crank_singular_get (TEST_TYPE_SUBJECT);

		g_assert_null (singular_a);

		singular_b = test_subject_new (3);
		singular_a = TEST_SUBJECT(crank_singular_get (TEST_TYPE_SUBJECT));

		g_assert_nonnull (singular_a);
		g_assert_cmpint (test_subject_get_int_item (singular_a), ==, 3);
		return;
	}

	g_test_trap_subprocess (NULL, 0, 0);
	g_test_trap_assert_passed ();
}

void
test_singular_first_construct (void)
{
	TestSubject*	singular_a;
	TestSubject*	singular_b;

	if (g_test_subprocess()) {
		singular_a = test_subject_new (7);

		g_assert_cmpint (test_subject_get_first_construct_times (singular_a), ==, 1);

		singular_b = test_subject_new (3);

		g_assert_cmpint (test_subject_get_first_construct_times (singular_a), ==, 1);
		return;
	}

	g_test_trap_subprocess (NULL, 0, 0);
	g_test_trap_assert_passed ();
}

void
test_singular_thread_construct (void)
{
	if (g_test_subprocess()) {
		TestSubject**	singulars;
		GThread**		threads;
		gint			n = 100;
		
		singulars = g_new (TestSubject*, n);
		threads = g_new (GThread*, n);
		
		gint			i;
		
		for (i = 0; i < n; i++) {
			threads[i] = g_thread_new (NULL, test_singular_thread_construct_func, NULL);
		}
		
		for (i = 0; i < n; i++) {
			singulars[i] = TEST_SUBJECT (g_thread_join (threads[i]));
		}
		
		for (i = 0; i < n - 1; i++) {
			g_assert (singulars[i] == singulars[i + 1]);
		}
		
		return;
	}

	g_test_trap_subprocess (NULL, 0, 0);
	g_test_trap_assert_passed ();
}

TestSubject*
test_singular_thread_construct_func (gpointer userdata)
{
	return test_subject_new (0);
}
