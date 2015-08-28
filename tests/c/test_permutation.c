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

static gboolean	test_foreach_func (const guint v,	gpointer	userdata);



static void		test_is_valid (void);

static void		test_hash (void);

static void		test_equal (void);

static void 	test_to_string (void);


static void		test_is_empty (void);

static void		test_slice (void);

static void		test_foreach (void);


static void		test_is_identity (void);

static void		test_inversion (void);

static void		test_sign (void);

static void		test_ascends (void);

static void		test_descends (void);

static void		test_excedances (void);

static void		test_swap (void);

static void		test_reverse (void);

static void		test_inverse (void);

static void		test_shuffle (void);


static void		test_reverse_self (void);

static void		test_inverse_self (void);

static void		test_shuffle_self (void);


static void		test_shuffle_array (void);

static void		test_shuffle_parray (void);

static void		test_shuffle_array_boolean (void);

static void		test_shuffle_array_int (void);

static void		test_shuffle_array_float (void);


static void		test_init_compare_array_data (void);

static void		test_init_compare_parray_data (void);

//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint argc, gchar** argv)
{
	g_test_init (&argc, &argv, NULL);

  	g_test_add_func ("/crank/base/permutation/is_valid",
					test_is_valid);

  	g_test_add_func ("/crank/base/permutation/hash",
					test_hash);

  	g_test_add_func ("/crank/base/permutation/equal",
					test_equal);

  	g_test_add_func ("/crank/base/permutation/to_string",
					test_to_string);
					
	
	g_test_add_func ("/crank/base/permutation/is_empty",
					test_is_empty);

  	g_test_add_func ("/crank/base/permutation/slice",
					test_slice);
	
	g_test_add_func ("/crank/base/permutation/foreach",
					test_foreach);
	
	
	g_test_add_func ("/crank/base/permutation/is_identity",
					test_is_identity);
					
  	g_test_add_func ("/crank/base/permutation/inversion",
					test_inversion);
					
  	g_test_add_func ("/crank/base/permutation/sign",
					test_sign);
					
	g_test_add_func ("/crank/base/permutation/ascends",
					test_ascends);

	g_test_add_func ("/crank/base/permutation/descends",
					test_descends);

	g_test_add_func ("/crank/base/permutation/excedances",
					test_excedances);
					
  	g_test_add_func ("/crank/base/permutation/swap",
					test_swap);
					

					
  	g_test_add_func ("/crank/base/permutation/reverse",
					test_reverse);
					
  	g_test_add_func ("/crank/base/permutation/inverse",
					test_inverse);
					
  	g_test_add_func ("/crank/base/permutation/shuffle",
					test_shuffle);
					
					
  	g_test_add_func ("/crank/base/permutation/reverse/self",
					test_reverse_self);
					
  	g_test_add_func ("/crank/base/permutation/inverse/self",
					test_inverse_self);
					
  	g_test_add_func ("/crank/base/permutation/shuffle/self",
					test_shuffle_self);
					
					
  	g_test_add_func ("/crank/base/permutation/shuffle_array",
					test_shuffle_array);
					
  	g_test_add_func ("/crank/base/permutation/shuffle_parray",
					test_shuffle_parray);

	g_test_add_func ("/crank/base/permutation/shuffle_array/boolean",
					test_shuffle_array_boolean);

	g_test_add_func ("/crank/base/permutation/shuffle_array/int",
					test_shuffle_array_int);

	g_test_add_func ("/crank/base/permutation/shuffle_array/float",
					test_shuffle_array_float);


	g_test_add_func ("/crank/base/permutation/init/compare/array",
					test_init_compare_array_data);
					
	g_test_add_func ("/crank/base/permutation/init/compare/parray",
					test_init_compare_parray_data);

  	g_test_run ();
  	return 0;
}

//////// Definition ////////////////////////////////////////////////////////////

static gboolean
test_foreach_func (	const guint	v, gpointer	userdata	)
{
	guint* acc = (guint*)	userdata;
	
	*acc += v;
	
	return TRUE;
}





static void
test_is_valid (void)
{
	CrankPermutation	p;
	CrankPermutation	q;
	CrankPermutation	r;
	
	crank_permutation_init (&p, 5, 0, 1, 2, 3, 4);
	crank_permutation_init (&q, 5, 0, 3, 0, 2, 4);
	crank_permutation_init (&r, 5, 0, 6, 3, 4, 7);
	
	g_assert (  crank_permutation_is_valid (&p));
	g_assert (! crank_permutation_is_valid (&q));
	g_assert (! crank_permutation_is_valid (&r));
	
	crank_permutation_fini (&p);
	crank_permutation_fini (&q);
	crank_permutation_fini (&r);
}

static void
test_hash (void)
{
	CrankPermutation	p;
	CrankPermutation	q;
	CrankPermutation	r;
	
	guint	ph;
	guint	qh;
	guint	rh;
	
	crank_permutation_init (&p, 5, 0, 3, 2, 1, 4);
	crank_permutation_init (&q, 5, 0, 3, 2, 1, 4);
	crank_permutation_init (&r, 5, 1, 2, 0, 3, 4);
	
	ph = crank_permutation_hash (&p);
	qh = crank_permutation_hash (&q);
	rh = crank_permutation_hash (&r);
	
	g_assert_cmpuint (ph, ==, qh);
	g_assert_cmpuint (ph, !=, rh);
	
	crank_permutation_fini (&p);
	crank_permutation_fini (&q);
	crank_permutation_fini (&r);
}

static void
test_equal (void)
{
	CrankPermutation	p;
	CrankPermutation	q;
	CrankPermutation	r;
	
	crank_permutation_init (&p, 5, 0, 3, 2, 1, 4);
	crank_permutation_init (&q, 5, 0, 3, 2, 1, 4);
	crank_permutation_init (&r, 5, 1, 2, 0, 3, 4);
	
	g_assert (  crank_permutation_equal (&p, &q));
	g_assert (! crank_permutation_equal (&p, &r));
	
	crank_permutation_fini (&p);
	crank_permutation_fini (&q);
	crank_permutation_fini (&r);
}

static void
test_to_string (void)
{
	CrankPermutation	p;
	gchar*				pstr;
	
	crank_permutation_init (&p, 5, 1, 2, 0, 3, 4);
	
	pstr = crank_permutation_to_string (&p);
	
	g_assert_cmpstr (pstr, ==, "(1, 2, 0, 3, 4)");
	
	g_free (pstr);
	crank_permutation_fini (&p);
}

static void
test_is_empty (void)
{
	CrankPermutation	p;
	
	crank_permutation_init (&p, 2, 0, 1);
	
	g_assert (! crank_permutation_is_empty (&p));
	
	crank_permutation_fini (&p);
	
	crank_permutation_init (&p, 0);
	
	g_assert (crank_permutation_is_empty (&p));
	
	crank_permutation_fini (&p);
}

static void
test_slice (void)
{
	CrankPermutation	p;
	guint*				slice;
	
	crank_permutation_init (&p, 5, 0, 3, 2, 1, 4);
	
	slice = crank_permutation_slice (&p, 1, 4);
	
	g_assert_cmpuint (slice[0], ==, 3);
	g_assert_cmpuint (slice[1], ==, 2);
	g_assert_cmpuint (slice[2], ==, 1);
	
	g_free (slice);
	crank_permutation_fini (&p);
}

static void
test_foreach (void)
{
	guint				acc;
	CrankPermutation	p;
	
	crank_permutation_init (&p, 5, 2, 1, 3, 4, 0);
	
	crank_permutation_foreach (&p, test_foreach_func, &acc);
	
	g_assert_cmpuint (acc, ==, 10);
	
	crank_permutation_fini (&p);
	
}

static void
test_is_identity (void)
{
	CrankPermutation	p;
	
	crank_permutation_init (&p, 2, 0, 1);
	
	g_assert (crank_permutation_is_identity (&p));
	
	crank_permutation_fini (&p);
	
	crank_permutation_init (&p, 3, 0, 2, 1);
	
	g_assert (! crank_permutation_is_identity (&p));
	
	crank_permutation_fini (&p);
}

static void
test_inversion (void)
{
	CrankPermutation	p;
	
	crank_permutation_init (&p, 5, 2, 1, 3, 4, 0);
	
	g_assert_cmpuint (crank_permutation_get_inversion (&p), ==, 5);
	
	crank_permutation_fini (&p);
}


static void
test_sign (void)
{
	CrankPermutation	p;
	
	crank_permutation_init (&p, 5, 2, 1, 3, 4, 0);
	
	g_assert_cmpint (crank_permutation_get_sign (&p), ==, -1);
	
	crank_permutation_fini (&p);
}

static void
test_ascends (void)
{
	CrankPermutation	p;
	guint*				ascends;
	guint				nascends;
	
	crank_permutation_init (&p, 5, 2, 1, 3, 4, 0);
	
	ascends = crank_permutation_get_ascents(&p, &nascends);
	
	// TODO: Add crank_assert_eqarray_uint_imm
	// 1,2
	g_assert_cmpuint (nascends, ==, 2);
	g_assert_cmpuint (ascends[0], ==, 1);
	g_assert_cmpuint (ascends[1], ==, 2);
	
	g_free (ascends);
	crank_permutation_fini (&p);
}

static void
test_descends (void)
{
	CrankPermutation	p;
	guint*				descends;
	guint				ndescends;
	
	crank_permutation_init (&p, 5, 2, 1, 3, 4, 0);
	
	descends = crank_permutation_get_descents(&p, &ndescends);
	
	// TODO: Add crank_assert_eqarray_uint_imm
	// 1,2
	g_assert_cmpuint (ndescends, ==, 2);
	g_assert_cmpuint (descends[0], ==, 0);
	g_assert_cmpuint (descends[1], ==, 3);
	
	g_free (descends);
	crank_permutation_fini (&p);
}

static void
test_excedances (void)
{
	CrankPermutation	p;
	guint*				excedances;
	guint				nexcedances;
	
	crank_permutation_init (&p, 5, 2, 1, 3, 4, 0);
	
	excedances = crank_permutation_get_excedances(&p, &nexcedances);
	
	// TODO: Add crank_assert_eqarray_uint_imm
	g_assert_cmpuint (nexcedances, ==, 3);
	g_assert_cmpuint (excedances[0], ==, 0);
	g_assert_cmpuint (excedances[1], ==, 2);
	g_assert_cmpuint (excedances[2], ==, 3);
	
	g_free (excedances);
	crank_permutation_fini (&p);
}

static void
test_swap (void)
{
	CrankPermutation	p;
	
	crank_permutation_init (&p, 5, 0, 1, 3, 2, 4);
	
	crank_permutation_swap (&p, 2, 3);
	
	g_assert_cmpuint (crank_permutation_get (&p, 2), ==, 2);
	g_assert_cmpuint (crank_permutation_get (&p, 3), ==, 3);
	
	crank_permutation_fini (&p);
}

static void
test_reverse (void)
{
	CrankPermutation	p;
	CrankPermutation	q;
	
	crank_permutation_init (&p, 5, 0, 1, 3, 2, 4);
	
	crank_permutation_reverse (&p, &q);
	
	crank_assert_eq_permutation_imm (&q, 4, 2, 3, 1, 0);
	
	crank_permutation_fini (&p);
	crank_permutation_fini (&q);
}

static void
test_inverse (void)
{
	CrankPermutation	p;
	CrankPermutation	q;
	
	crank_permutation_init (&p, 5, 0, 1, 3, 2, 4);
	
	crank_permutation_inverse (&p, &q);
	
	crank_assert_eq_permutation_imm (&q, 0 ,1, 3, 2, 4);
	
	crank_permutation_fini (&p);
	crank_permutation_fini (&q);
}

static void
test_shuffle (void)
{
	CrankPermutation	p;
	CrankPermutation	q;
	CrankPermutation	r;
	
	crank_permutation_init (&p, 4,	0, 1, 3, 2);
	crank_permutation_init (&q, 4,	1, 0, 2, 3);
	
	crank_permutation_shuffle (&p, &q, &r);
	
	crank_assert_eq_permutation_imm (&r, 1, 0, 3, 2);
	
	crank_permutation_fini (&p);
	crank_permutation_fini (&q);
	crank_permutation_fini (&r);
}


static void
test_reverse_self (void)
{
	CrankPermutation	p;
	
	crank_permutation_init (&p, 5, 0, 1, 3, 2, 4);
	
	crank_permutation_reverse_self (&p);
	
	crank_assert_eq_permutation_imm (&p, 4, 2, 3, 1, 0);
	
	crank_permutation_fini (&p);
}

static void
test_inverse_self (void)
{
	CrankPermutation	p;
	
	crank_permutation_init (&p, 5, 0, 1, 3, 2, 4);
	
	crank_permutation_inverse_self (&p);
	
	crank_assert_eq_permutation_imm (&p, 0 ,1, 3, 2, 4);
	
	crank_permutation_fini (&p);
}

static void
test_shuffle_self (void)
{
	CrankPermutation	p;
	CrankPermutation	q;
	
	crank_permutation_init (&p, 4,	0, 1, 3, 2);
	crank_permutation_init (&q, 4,	1, 0, 2, 3);
	
	crank_permutation_shuffle_self (&p, &q);
	
	crank_assert_eq_permutation_imm (&p, 1, 0, 3, 2);
	
	crank_permutation_fini (&p);
	crank_permutation_fini (&q);
}

static void
test_shuffle_array (void)
{
	CrankPermutation	p;
	gfloat				arr[4] = {1, 2, 3, 4};
	gfloat*				narr;
	
	crank_permutation_init (&p, 4,	0, 1, 3, 2);
	
	narr = crank_permutation_shuffle_array (&p, gfloat, arr);
	
	crank_assert_eqarray_float_imm (narr, 4, 1, 2, 4, 3);
	
	g_free (narr);
	crank_permutation_fini (&p);
}

static void
test_shuffle_parray (void)
{
	CrankPermutation	p;
	gfloat				arr[4] = {1, 2, 3, 4};
	gfloat*				parr[4] = {arr, arr+1, arr+2, arr+3};
	gfloat**			nparr;
	
	crank_permutation_init (&p, 4,	0, 1, 3, 2);
	
	nparr = (gfloat**)crank_permutation_shuffle_parray (&p, (gpointer*)parr);
	
	crank_assert_eqarray_pointer_imm (nparr, 4, arr, arr+1, arr+3, arr+2);
	
	g_free (nparr);
	crank_permutation_fini (&p);
}

static void
test_shuffle_array_boolean (void)
{
	CrankPermutation	p;
	gboolean			arr[4] = {TRUE, FALSE, FALSE, TRUE};
	gboolean*			narr;
	
	crank_permutation_init (&p, 4,	0, 1, 3, 2);
	
	narr = crank_permutation_shuffle_array_boolean (&p, arr);
	
	crank_assert_eqarray_bool_imm (narr, 4, TRUE, FALSE, TRUE, FALSE);
	
	g_free (narr);
	crank_permutation_fini (&p);
}

static void
test_shuffle_array_int (void)
{
	CrankPermutation	p;
	gint			arr[4] = {3, 4, 5, 12};
	gint*			narr;
	
	crank_permutation_init (&p, 4,	0, 1, 3, 2);
	
	narr = crank_permutation_shuffle_array_int (&p, arr);
	
	crank_assert_eqarray_int_imm (narr, 4, 3, 4, 12, 5);
	
	g_free (narr);
	crank_permutation_fini (&p);
}

static void
test_shuffle_array_float (void)
{
	CrankPermutation	p;
	gfloat			arr[4] = {1.1f, 3.2f, 14.0f, 9.0f};
	gfloat*			narr;
	
	crank_permutation_init (&p, 4,	0, 1, 3, 2);
	
	narr = crank_permutation_shuffle_array_float (&p, arr);
	
	crank_assert_eqarray_float_imm (narr, 4, 1.1f, 3.2f, 9.0f, 14.0f);
	
	g_free (narr);
	crank_permutation_fini (&p);
}


static gint
test_compare_double (gconstpointer	a,	gconstpointer b, gpointer userdata)
{
	gdouble	ad = *(gdouble*)a;
	gdouble	bd = *(gdouble*)b;
	
	return (bd < ad) - (ad < bd);
}

static gint
test_compare_ptr (gconstpointer	a,	gconstpointer b, gpointer userdata)
{
	gint	ad = GPOINTER_TO_INT(a);
	gint	bd = GPOINTER_TO_INT(b);
	
	return (bd < ad) - (ad < bd);
}


static void
test_init_compare_array_data (void) {
	CrankPermutation	p;
	
	gdouble	items[4] = {1.3, 5.2, 1.0, 9.0};
	
	crank_permutation_init_compare_array_data(&p, 4, gdouble, items, test_compare_double, NULL);
	
	crank_assert_eq_permutation_imm (&p, 2, 0, 1, 3);
}

static void
test_init_compare_parray_data (void) {
	CrankPermutation	p;
	
	gpointer items[4] = {
		GINT_TO_POINTER(0x4021),
		GINT_TO_POINTER(0x4005),
		GINT_TO_POINTER(0x4062),
		GINT_TO_POINTER(0x4015)
	};
	
	crank_permutation_init_compare_parray_data(&p, 4, items, test_compare_ptr, NULL);
	
	crank_assert_eq_permutation_imm (&p, 1, 3, 0, 2);
}
