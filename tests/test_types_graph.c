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

	
static GType key1_a[1];
static GType key1_b[1];
static GType key1_c[1];
static GType key1_d[1];
static GType key1_e[1];
static GType key1_x[1];

static GType key2_aa[2]; // <
static GType key2_ab[2];
static GType key2_ad[2]; // <
static GType key2_ae[2]; // <
static GType key2_bc[2];
static GType key2_ca[2];
static GType key2_ce[2];
static GType key2_ea[2]; // <
static GType key2_ed[2]; // <

static GType key2_ax[2];
static GType key2_xa[2];

//////// Test Subjects Types ///////////////////////////////////////////////////

/*
 * TEST_DEFINE_TEST_TYPE:
 * @Type: 테스트용 타입의 CamelCase
 * @type: 테스트용 타입의 lower_case
 * @NS: 테스트용 타입의 이름 공간 - 보통 TEST
 * @T: 테스트용 타입의 이름 - 보통 알파벳
 * @parent: 부모 타입의 CamelCase
 * @parent_GTYPE: 부모 타입의 GType
 * 
 * private 변수가 없는 타입을 간편하게 정의합니다.
 *
 * 오로지 테스트만을 위한 타입을 정의할 때 사용합니다.
 */
#define TEST_DEFINE_TEST_TYPE(Type, type, NS, T, parent, parent_GTYPE) \
		typedef struct _##Type##Class { \
			parent##Class	parent_class; \
		} Type##Class; \
		\
		G_DECLARE_DERIVABLE_TYPE (Type, type, NS, T, parent); \
		G_DEFINE_TYPE (Type, type, parent_GTYPE); \
		\
		static void type##_class_init ( Type##Class* c) {} \
		static void type##_init (Type* i) {}

/* 테스트를 위해서만 만들어진 클래스들입니다.
 *
 * TestA
 * - TestB
 *   - TestC
 *   - TestD
 * - TestE
 */

#define TEST_TYPE_A	(test_a_get_type ())
TEST_DEFINE_TEST_TYPE(TestA, test_a, TEST, A, GObject, G_TYPE_OBJECT);

#define TEST_TYPE_B	(test_b_get_type ())
TEST_DEFINE_TEST_TYPE(TestB, test_b, TEST, B, TestA, TEST_TYPE_A);

#define TEST_TYPE_C	(test_c_get_type ())
TEST_DEFINE_TEST_TYPE(TestC, test_c, TEST, C, TestB, TEST_TYPE_B);

#define TEST_TYPE_D	(test_d_get_type ())
TEST_DEFINE_TEST_TYPE(TestD, test_d, TEST, D, TestB, TEST_TYPE_B);

#define TEST_TYPE_E	(test_e_get_type ())
TEST_DEFINE_TEST_TYPE(TestE, test_e, TEST, E, TestA, TEST_TYPE_A);

#define TEST_TYPE_X	(test_x_get_type ())
TEST_DEFINE_TEST_TYPE(TestX, test_x, TEST, X, GObject, G_TYPE_OBJECT);


//////// Test Cases ////////////////////////////////////////////////////////////

typedef void	(*TestTypeGraphFunc) (	CrankTypesGraph**	fixture,
										gconstpointer		userdata	);

void	test_init_types_graph (void);



static inline
void	test_add_types_graph (		const gchar*		test_path,
									gconstpointer		userdata,
									TestTypeGraphFunc	func		);



void	test_types_graph_setup (		CrankTypesGraph**	graph_ptr,
                                		gconstpointer		userdata	);
void	test_types_graph_teardown (		CrankTypesGraph**	graph_ptr,
                                 	  	gconstpointer		userdata	);


void	test_types_graph_new (void);

void	test_types_graph_get (			CrankTypesGraph**	fixture,
                              			gconstpointer	userdata	);
void	test_types_graph_has (			CrankTypesGraph**	fixture,
										gconstpointer		userdata	);
									
void	test_types_graph_lookup (		CrankTypesGraph**	fixture,
										gconstpointer		userdata	);
void	test_types_graph_lookup_types (	CrankTypesGraph**	fixture,
										gconstpointer		userdata	);
void	test_types_graph_lookup_full (	CrankTypesGraph**	fixture,
										gconstpointer		userdata	);
void	test_types_graph_remove (		CrankTypesGraph**	fixture,
										gconstpointer		userdata	);

void	test_types_graph_get_key_lengths (	CrankTypesGraph**	fixture,
											gconstpointer		userdata	);
											
void	test_types_graph_get_keys (		CrankTypesGraph**	fixture,
										gconstpointer		userdata	);

void	test_types_graph_get_values (	CrankTypesGraph**	fixture,
										gconstpointer		userdata	);


gint
main (gint   argc,
      gchar *argv[])
{
	g_test_init (&argc, &argv, NULL);
	
	test_init_types_graph ();
	
	g_test_add_func ("/wsid/crank/base/types_graph/new",
			test_types_graph_new);
	
	test_add_types_graph ("/wsid/crank/base/types_graph/get",
			NULL,	test_types_graph_get	);
	test_add_types_graph ("/wsid/crank/base/types_graph/has",
			NULL,	test_types_graph_has	);
			
	test_add_types_graph("/wsid/crank/base/types_graph/lookup/basic",
			NULL,	test_types_graph_lookup);
	test_add_types_graph ("/wsid/crank/base/types_graph/lookup/types",
			NULL,	test_types_graph_lookup_types);
	test_add_types_graph ("/wsid/crank/base/types_graph/lookup/full",
			NULL,	test_types_graph_lookup_full);
	test_add_types_graph ("/wsid/crank/base/types_graph/remove",
			NULL,	test_types_graph_remove);

	test_add_types_graph ("/wsid/crank/base/types_graph/get_key_lengths",
			NULL,	test_types_graph_get_key_lengths);
			
	test_add_types_graph ("/wsid/crank/base/types_graph/get_keys",
			NULL,	test_types_graph_get_keys);
			
	test_add_types_graph ("/wsid/crank/base/types_graph/get_values",
			NULL,	test_types_graph_get_values);
	g_test_run ();

	return 0;
}



void
test_init_types_graph (void)
{
	key1_a[0] = TEST_TYPE_A;
	key1_b[0] = TEST_TYPE_B;
	key1_c[0] = TEST_TYPE_C;
	key1_d[0] = TEST_TYPE_D;
	key1_e[0] = TEST_TYPE_E;
	key1_x[0] = TEST_TYPE_X;
	
	key2_aa[0] = TEST_TYPE_A;
	key2_aa[1] = TEST_TYPE_A;
	key2_ab[0] = TEST_TYPE_A;
	key2_ab[1] = TEST_TYPE_B;
	key2_ad[0] = TEST_TYPE_A;
	key2_ad[1] = TEST_TYPE_D;
	key2_ae[0] = TEST_TYPE_A;
	key2_ae[1] = TEST_TYPE_E;
	
	key2_bc[0] = TEST_TYPE_B;
	key2_bc[1] = TEST_TYPE_C;
	
	key2_ca[0] = TEST_TYPE_C;
	key2_ca[1] = TEST_TYPE_A;
	key2_ce[0] = TEST_TYPE_C;
	key2_ce[1] = TEST_TYPE_E;
	
	key2_ea[0] = TEST_TYPE_E;
	key2_ea[1] = TEST_TYPE_A;
	key2_ed[0] = TEST_TYPE_E;
	key2_ed[1] = TEST_TYPE_D;
	
	key2_ax[0] = TEST_TYPE_A;
	key2_ax[1] = TEST_TYPE_X;
	key2_xa[0] = TEST_TYPE_X;
	key2_xa[1] = TEST_TYPE_A;
}


static inline void
test_add_types_graph (	const gchar*		test_path,
						gconstpointer		userdata,
						TestTypeGraphFunc	func		)
{
	g_test_add (test_path,
			CrankTypesGraph*,
			userdata,
			test_types_graph_setup,
			func,
			test_types_graph_teardown	);
}




void
test_types_graph_setup (	CrankTypesGraph**	graph_ptr,
                            gconstpointer		userdata	)
{
	*graph_ptr = crank_types_graph_new ();
	
	GValue value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_value_set_string (&value, "value for A");
	crank_types_graph_set (*graph_ptr, key1_a, 1, &value);
	
	g_value_set_string (&value, "value for D");
	crank_types_graph_set (*graph_ptr, key1_d, 1, &value);
	
	g_value_set_string (&value, "value for E");
	crank_types_graph_set (*graph_ptr, key1_e, 1, &value);
	
	g_value_set_string (&value, "value for AA");
	crank_types_graph_set (*graph_ptr, key2_aa, 2, &value);
	
	g_value_set_string (&value, "value for AD");
	crank_types_graph_set (*graph_ptr, key2_ad, 2, &value);
	
	g_value_set_string (&value, "value for AE");
	crank_types_graph_set (*graph_ptr, key2_ae, 2, &value);
	
	g_value_set_string (&value, "value for EA");
	crank_types_graph_set (*graph_ptr, key2_ea, 2, &value);
	
	g_value_set_string (&value, "value for ED");
	crank_types_graph_set (*graph_ptr, key2_ed, 2, &value);
}

void
test_types_graph_teardown (	CrankTypesGraph**	graph_ptr,
                           	gconstpointer		userdata	)
{
	crank_types_graph_unref (*graph_ptr);
}





void
test_types_graph_new (void)
{
	CrankTypesGraph* graph = crank_types_graph_new ();
	
	crank_types_graph_unref (graph);
}

void
test_types_graph_get (	CrankTypesGraph**	fixture,
                        gconstpointer		userdata	)
{
	CrankTypesGraph*	graph = *(CrankTypesGraph**) fixture;
	
	GValue				value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	// Test for 1
	g_assert (crank_types_graph_get(graph, key1_a, 1, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for A");
	
	g_assert (! crank_types_graph_get(graph, key1_b, 1, &value));
	
	g_assert (! crank_types_graph_get(graph, key1_c, 1, &value));
	
	g_assert (crank_types_graph_get(graph, key1_d, 1, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for D");
	
	g_assert (crank_types_graph_get(graph, key1_e, 1, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for E");
	
	g_assert (! crank_types_graph_get(graph, key1_x, 1, &value));
	
	
	// Test for 2
	g_assert (crank_types_graph_get(graph, key2_aa, 2, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for AA");
	
	g_assert (! crank_types_graph_get(graph, key2_ab, 2, &value));
	
	g_assert (crank_types_graph_get(graph, key2_ad, 2, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for AD");
	
	g_assert (crank_types_graph_get(graph, key2_ae, 2, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for AE");
	
	g_assert (! crank_types_graph_get(graph, key2_bc, 2, &value));
	
	g_assert (! crank_types_graph_get(graph, key2_ca, 2, &value));
	
	g_assert (! crank_types_graph_get(graph, key2_ce, 2, &value));
	
	g_assert (crank_types_graph_get(graph, key2_ea, 2, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for EA");
	
	g_assert (crank_types_graph_get(graph, key2_ed, 2, &value));
	g_assert_cmpstr ( g_value_get_string (&value), ==, "value for ED");
	
	g_assert (! crank_types_graph_get(graph, key2_ax, 2, &value));
	
	g_assert (! crank_types_graph_get(graph, key2_xa, 2, &value));
}

void
test_types_graph_has (	CrankTypesGraph**	fixture,
                        gconstpointer		userdata	)
{
	CrankTypesGraph* graph = *(CrankTypesGraph**) fixture;

	GValue				value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_assert_true (crank_types_graph_has (graph, key1_a, 1));
	g_assert_false (crank_types_graph_has (graph, key1_b, 1));
	g_assert_false (crank_types_graph_has (graph, key1_c, 1));
	g_assert_true (crank_types_graph_has (graph, key1_d, 1));
	g_assert_true (crank_types_graph_has (graph, key1_e, 1));
	g_assert_false (crank_types_graph_has (graph, key1_x, 1));
	
	g_assert_true (crank_types_graph_has (graph, key2_aa, 2));
	g_assert_false (crank_types_graph_has (graph, key2_ab, 2));
	g_assert_true (crank_types_graph_has (graph, key2_ad, 2));
	g_assert_true (crank_types_graph_has (graph, key2_ae, 2));
	g_assert_false (crank_types_graph_has (graph, key2_bc, 2));
	g_assert_false (crank_types_graph_has (graph, key2_ca, 2));
	g_assert_false (crank_types_graph_has (graph, key2_ce, 2));
	g_assert_true (crank_types_graph_has (graph, key2_ea, 2));
	g_assert_true (crank_types_graph_has (graph, key2_ed, 2));
	g_assert_false (crank_types_graph_has (graph, key2_ax, 2));
	g_assert_false (crank_types_graph_has (graph, key2_xa, 2));
}

void
test_types_graph_lookup (	CrankTypesGraph**	fixture,
							gconstpointer		userdata	)
{
	CrankTypesGraph* graph = *(CrankTypesGraph**) fixture;

	GValue				value = G_VALUE_INIT;

	g_value_init (&value, G_TYPE_STRING);
	
	
	g_assert (crank_types_graph_lookup(graph, key1_a, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for A");
	
	g_assert (crank_types_graph_lookup(graph, key1_b, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for A");
	
	g_assert (crank_types_graph_lookup(graph, key1_c, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for A");
	
	g_assert (crank_types_graph_lookup(graph, key1_d, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for D");
	
	g_assert (crank_types_graph_lookup(graph, key1_e, 1, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for E");
	
	g_assert (! crank_types_graph_lookup(graph, key1_x, 1, &value));
			
			
			
	g_assert (crank_types_graph_lookup(graph, key2_aa, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for AA");
			
	g_assert (crank_types_graph_lookup(graph, key2_ab, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for AA");
			
	g_assert (crank_types_graph_lookup(graph, key2_ad, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for AD");
			
	g_assert (crank_types_graph_lookup(graph, key2_ae, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for AE");
			
	g_assert (crank_types_graph_lookup(graph, key2_bc, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for AA");
			
	g_assert (crank_types_graph_lookup(graph, key2_ca, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for AA");
			
	g_assert (crank_types_graph_lookup(graph, key2_ce, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for AE");
			
	g_assert (crank_types_graph_lookup(graph, key2_ea, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for EA");
			
	g_assert (crank_types_graph_lookup(graph, key2_ed, 2, &value));
	g_assert_cmpstr( g_value_get_string (&value), ==, "value for ED");
	
			
	g_assert (! crank_types_graph_lookup(graph, key2_xa, 2, &value));
			
	g_assert (! crank_types_graph_lookup(graph, key2_ax, 2, &value));
}

void
test_types_graph_lookup_types (	CrankTypesGraph**	fixture,
								gconstpointer		userdata	)
{
	const GType*	lookup_key1_a;
	const GType*	lookup_key1_b;
	const GType*	lookup_key1_c;
	const GType*	lookup_key1_d;
	const GType*	lookup_key1_e;
	const GType*	lookup_key1_x;
	
	const GType*	lookup_key2_aa;
	const GType*	lookup_key2_ab;
	const GType*	lookup_key2_ad;
	const GType*	lookup_key2_ae;
	const GType*	lookup_key2_bc;
	const GType*	lookup_key2_ca;
	const GType*	lookup_key2_ce;
	const GType*	lookup_key2_ea;
	const GType*	lookup_key2_ed;
	const GType*	lookup_key2_xa;
	const GType*	lookup_key2_ax;
	

	CrankTypesGraph* graph = *(CrankTypesGraph**) fixture;

	lookup_key1_a = crank_types_graph_lookup_types (graph, key1_a, 1);
	lookup_key1_b = crank_types_graph_lookup_types (graph, key1_b, 1);
	lookup_key1_c = crank_types_graph_lookup_types (graph, key1_c, 1);
	lookup_key1_d = crank_types_graph_lookup_types (graph, key1_d, 1);
	lookup_key1_e = crank_types_graph_lookup_types (graph, key1_e, 1);
	lookup_key1_x = crank_types_graph_lookup_types (graph, key1_x, 1);
	
 	lookup_key2_aa = crank_types_graph_lookup_types (graph, key2_aa, 2);
 	lookup_key2_ab = crank_types_graph_lookup_types (graph, key2_ab, 2);
 	lookup_key2_ad = crank_types_graph_lookup_types (graph, key2_ad, 2);
 	lookup_key2_ae = crank_types_graph_lookup_types (graph, key2_ae, 2);
 	lookup_key2_bc = crank_types_graph_lookup_types (graph, key2_bc, 2);
 	lookup_key2_ca = crank_types_graph_lookup_types (graph, key2_ca, 2);
 	lookup_key2_ce = crank_types_graph_lookup_types (graph, key2_ce, 2);
 	lookup_key2_ea = crank_types_graph_lookup_types (graph, key2_ea, 2);
 	lookup_key2_ed = crank_types_graph_lookup_types (graph, key2_ed, 2);
 	lookup_key2_xa = crank_types_graph_lookup_types (graph, key2_xa, 2);
 	lookup_key2_ax = crank_types_graph_lookup_types (graph, key2_ax, 2);
	
	g_assert (CRANK_ARRAY_CMP (lookup_key1_a, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_b, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_c, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_d, key1_d, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_e, key1_e, GType, 1) == 0);
	g_assert_null (lookup_key1_x);
	
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_aa, key2_aa, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ab, key2_aa, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ad, key2_ad, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ae, key2_ae, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_bc, key2_aa, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ca, key2_aa, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ce, key2_ae, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ea, key2_ea, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ed, key2_ed, GType, 2) == 0);
	g_assert_null (lookup_key2_xa);
	g_assert_null (lookup_key2_ax);
}

void
test_types_graph_lookup_full (	CrankTypesGraph**	fixture,
								gconstpointer		userdata	)
{
	GType*	lookup_key1_a = NULL;
	GType*	lookup_key1_b = NULL;
	GType*	lookup_key1_c = NULL;
	GType*	lookup_key1_d = NULL;
	GType*	lookup_key1_e = NULL;
	GType*	lookup_key1_x = NULL;
	
	GType*	lookup_key2_aa = NULL;
	GType*	lookup_key2_ab = NULL;
	GType*	lookup_key2_ad = NULL;
	GType*	lookup_key2_ae = NULL;
	GType*	lookup_key2_bc = NULL;
	GType*	lookup_key2_ca = NULL;
	GType*	lookup_key2_ce = NULL;
	GType*	lookup_key2_ea = NULL;
	GType*	lookup_key2_ed = NULL;
	GType*	lookup_key2_xa = NULL;
	GType*	lookup_key2_ax = NULL;
	
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;
	
	GValue				value = G_VALUE_INIT;
	
	g_value_init (&value, G_TYPE_STRING);
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_a, 1, &lookup_key1_a, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for A");
			
	g_assert_true (crank_types_graph_lookup_full (graph, key1_b, 1, &lookup_key1_b, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for A");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_c, 1, &lookup_key1_c, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for A");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_d, 1, &lookup_key1_d, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for D");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key1_e, 1, &lookup_key1_e, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for E");
	
	g_assert_false (crank_types_graph_lookup_full (graph, key1_x, 1, &lookup_key1_x, &value));
			
	
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_aa, 2, &lookup_key2_aa, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for AA");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_ab, 2, &lookup_key2_ab, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for AA");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_ad, 2, &lookup_key2_ad, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for AD");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_ae, 2, &lookup_key2_ae, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for AE");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_bc, 2, &lookup_key2_bc, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for AA");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_ca, 2, &lookup_key2_ca, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for AA");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_ce, 2, &lookup_key2_ce, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for AE");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_ea, 2, &lookup_key2_ea, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for EA");
	
	g_assert_true (crank_types_graph_lookup_full (graph, key2_ed, 2, &lookup_key2_ed, &value));
	g_assert_cmpstr (g_value_get_string(&value), ==, "value for ED");
			
	g_assert_false (crank_types_graph_lookup_full (graph, key2_ax, 2, &lookup_key2_ax, &value));
	g_assert_false (crank_types_graph_lookup_full (graph, key2_xa, 2, &lookup_key2_xa, &value));
	
	g_assert (CRANK_ARRAY_CMP (lookup_key1_a, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_b, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_c, key1_a, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_d, key1_d, GType, 1) == 0);
	g_assert (CRANK_ARRAY_CMP (lookup_key1_e, key1_e, GType, 1) == 0);
	g_assert_null (lookup_key1_x);
	
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_aa, key2_aa, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ab, key2_aa, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ad, key2_ad, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ae, key2_ae, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_bc, key2_aa, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ca, key2_aa, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ce, key2_ae, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ea, key2_ea, GType, 2) == 0);
	g_assert_true (CRANK_ARRAY_CMP (lookup_key2_ed, key2_ed, GType, 2) == 0);
	g_assert_null (lookup_key2_xa);
	g_assert_null (lookup_key2_ax);
}

void
test_types_graph_remove (	CrankTypesGraph**	fixture,
							gconstpointer		userdata	)
{
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;

	g_assert_false (crank_types_graph_remove (graph, key1_b, 1));	
	g_assert_false (crank_types_graph_remove (graph, key1_c, 1));
	g_assert_false (crank_types_graph_remove (graph, key1_x, 1));
	g_assert_true (crank_types_graph_remove (graph, key1_d, 1));
	g_assert_true (crank_types_graph_remove (graph, key1_a, 1));
	g_assert_true (crank_types_graph_remove (graph, key1_e, 1));
	
	g_assert_true (crank_types_graph_remove (graph, key2_aa, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_ab, 2));
	g_assert_true (crank_types_graph_remove (graph, key2_ad, 2));
	g_assert_true (crank_types_graph_remove (graph, key2_ae, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_bc, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_ca, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_ce, 2));
	g_assert_true (crank_types_graph_remove (graph, key2_ea, 2));
	g_assert_true (crank_types_graph_remove (graph, key2_ed, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_ax, 2));
	g_assert_false (crank_types_graph_remove (graph, key2_xa, 2));
	
}

gint
test_cmp_key1 (gconstpointer a, gconstpointer b)
{
	return CRANK_ARRAY_CMP (a, b, GType, 1);
}

gint
test_cmp_key2 (gconstpointer a, gconstpointer b)
{
	return CRANK_ARRAY_CMP (a, b, GType, 2);
}

void
test_types_graph_get_key_lengths (	CrankTypesGraph**	fixture,
									gconstpointer		userdata	)
{
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;
	
	GList*	key_lengths = crank_types_graph_get_key_lengths (graph);
	
	g_assert_cmpint (g_list_length (key_lengths), ==, 2);
	g_assert_nonnull (g_list_find (key_lengths, GINT_TO_POINTER(1)));
	g_assert_nonnull (g_list_find (key_lengths, GINT_TO_POINTER(2)));
}

void
test_types_graph_get_keys (	CrankTypesGraph**	fixture,
							gconstpointer		userdata	)
{
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;
	
	GList*	keys_1 = crank_types_graph_get_keys_by_length (graph, 1);
	GList*	keys_2 = crank_types_graph_get_keys_by_length (graph, 2);

	g_assert_cmpint (g_list_length (keys_1), ==, 3);
	g_assert_nonnull (g_list_find_custom (keys_1, key1_a, test_cmp_key1));
	g_assert_nonnull (g_list_find_custom (keys_1, key1_d, test_cmp_key1));
	g_assert_nonnull (g_list_find_custom (keys_1, key1_e, test_cmp_key1));
	
	
	g_assert_cmpint (g_list_length (keys_2), ==, 5);
	g_assert_nonnull (g_list_find_custom (keys_2, key2_aa, test_cmp_key2));
	g_assert_nonnull (g_list_find_custom (keys_2, key2_ad, test_cmp_key2));
	g_assert_nonnull (g_list_find_custom (keys_2, key2_ae, test_cmp_key2));
	g_assert_nonnull (g_list_find_custom (keys_2, key2_ea, test_cmp_key2));
	g_assert_nonnull (g_list_find_custom (keys_2, key2_ed, test_cmp_key2));
	
	g_list_free (keys_1);
	g_list_free (keys_2);
}

gint
test_cmp_value_str (gconstpointer a, gconstpointer b)
{
	return g_strcmp0 (g_value_get_string((GValue*)a), (gchar*)b);
}

void
test_types_graph_get_values (	CrankTypesGraph**	fixture,
								gconstpointer		userdata	)
{
	CrankTypesGraph* graph = * (CrankTypesGraph**) fixture;
	
	GList* values_1 = crank_types_graph_get_values_by_length (graph, 1);
	GList* values_2 = crank_types_graph_get_values_by_length (graph, 2);
	
	g_assert_cmpint (g_list_length (values_1), ==, 3);
	g_assert_nonnull (g_list_find_custom (values_1, "value for A", test_cmp_value_str));
	g_assert_nonnull (g_list_find_custom (values_1, "value for D", test_cmp_value_str));
	g_assert_nonnull (g_list_find_custom (values_1, "value for E", test_cmp_value_str));
	
	g_assert_cmpint (g_list_length (values_2), ==, 5);
	g_assert_nonnull (g_list_find_custom (values_2, "value for AA", test_cmp_value_str));
	g_assert_nonnull (g_list_find_custom (values_2, "value for AD", test_cmp_value_str));
	g_assert_nonnull (g_list_find_custom (values_2, "value for AD", test_cmp_value_str));
	g_assert_nonnull (g_list_find_custom (values_2, "value for EA", test_cmp_value_str));
	g_assert_nonnull (g_list_find_custom (values_2, "value for ED", test_cmp_value_str));
}
