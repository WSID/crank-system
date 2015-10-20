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

#include <string.h>
#include <glib.h>

#include "crankbase.h"


//////// Declaration ///////////////////////////////////////////////////////////

static void test_always_pass (void);
static void test_always_fail (void);


static void test_test_expected_fail_onpass (void);

static void test_test_timeout_1000 (void);

static void test_assert_eqarray_bool (void);
static void test_assert_eqarray_bool_fail (void);

static void test_assert_eqarray_bool_imm (void);
static void test_assert_eqarray_bool_imm_fail (void);

static void test_assert_eqarray_int (void);
static void test_assert_eqarray_int_fail (void);

static void test_assert_eqarray_int_imm (void);
static void test_assert_eqarray_int_imm_fail (void);

static void test_assert_eqarray_uint (void);
static void test_assert_eqarray_uint_fail (void);

static void test_assert_eqarray_uint_imm (void);
static void test_assert_eqarray_uint_imm_fail (void);

static void test_assert_eqarray_float (void);
static void test_assert_eqarray_float_fail (void);

static void test_assert_eqarray_float_imm (void);
static void test_assert_eqarray_float_imm_fail (void);

static void test_assert_eqarray_pointer (void);
static void test_assert_eqarray_pointer_fail (void);

static void test_assert_eqarray_pointer_imm (void);
static void test_assert_eqarray_pointer_imm_fail (void);

static void test_assert_eqarray_pointer_imm (void);
static void test_assert_eqarray_pointer_imm_fail (void);

static void test_assert_eq_glist_imm (void);
static void test_assert_eq_glist_imm_fail (void);

static void test_assert_eq_gptrarray_imm (void);
static void test_assert_eq_gptrarray_imm_fail (void);

static void test_assert_cmpfloat (void);
static void test_assert_cmpfloat_fail (void);

static void test_assert_eqcplxfloat (void);
static void test_assert_eqcplxfloat_fail (void);

static void test_assert_eqcplxfloat_cimm (void);
static void test_assert_eqcplxfloat_cimm_fail (void);

static void test_assert_eq_permutation_imm (void);
static void test_assert_eq_permutation_imm_fail (void);

static void test_assert_eq_vecbool2_imm (void);
static void test_assert_eq_vecbool2_imm_fail (void);

static void test_assert_eq_vecbool_n_imm (void);
static void test_assert_eq_vecbool_n_imm_fail (void);

static void test_assert_eq_vecint2_imm (void);
static void test_assert_eq_vecint2_imm_fail (void);

static void test_assert_eq_vecint_n_imm (void);
static void test_assert_eq_vecint_n_imm_fail (void);

static void test_assert_eq_vecfloat2_imm (void);
static void test_assert_eq_vecfloat2_imm_fail (void);

static void test_assert_eq_vecfloat_n_imm (void);
static void test_assert_eq_vecfloat_n_imm_fail (void);


//////// Main //////////////////////////////////////////////////////////////////
gint
main (gint    argc,
      gchar **argv)
{
  g_test_init (&argc, &argv, NULL);

  crank_test_add_func_expected_fail (
    "/crank/base/test/expected_fail",
    test_always_fail);


  g_test_add_func (
    "/crank/base/test/expected_fail/onpass",
    test_test_expected_fail_onpass);

  crank_test_add_func_expected_fail (
    "/crank/base/test/expected_fail/subprocess",
    test_always_pass);


  crank_test_add_func_timeout (
    "/crank/base/test/timeout",
    test_test_timeout_1000,
    10000000);

  g_test_add_func (
    "/crank/base/test/eq/array/bool",
    test_assert_eqarray_bool);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/bool/fail",
    test_assert_eqarray_bool_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/bool/imm",
    test_assert_eqarray_bool_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/bool/imm/fail",
    test_assert_eqarray_bool_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/int",
    test_assert_eqarray_int);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/int/fail",
    test_assert_eqarray_int_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/int/imm",
    test_assert_eqarray_int_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/int/imm/fail",
    test_assert_eqarray_int_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/uint",
    test_assert_eqarray_uint);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/uint/fail",
    test_assert_eqarray_uint_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/uint/imm",
    test_assert_eqarray_uint_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/uint/imm/fail",
    test_assert_eqarray_uint_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/float",
    test_assert_eqarray_float);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/float/fail",
    test_assert_eqarray_float_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/float/imm",
    test_assert_eqarray_float_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/float/imm/fail",
    test_assert_eqarray_float_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/pointer",
    test_assert_eqarray_pointer);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/pointer/fail",
    test_assert_eqarray_pointer_fail);


  g_test_add_func (
    "/crank/base/test/eq/array/pointer/imm",
    test_assert_eqarray_pointer_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/array/pointer/imm/fail",
    test_assert_eqarray_pointer_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/glist/imm",
    test_assert_eq_glist_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/glist/imm/fail",
    test_assert_eq_glist_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/gptrarray/imm",
    test_assert_eq_gptrarray_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/gptrarray/imm/fail",
    test_assert_eq_gptrarray_imm_fail);




  g_test_add_func (
    "/crank/base/test/cmpfloat",
    test_assert_cmpfloat);

  crank_test_add_func_expected_fail (
    "/crank/base/test/cmpfloat/fail",
    test_assert_cmpfloat_fail);



  g_test_add_func (
    "/crank/base/test/eq/cplxfloat",
    test_assert_eqcplxfloat);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/cplxfloat/fail",
    test_assert_eqcplxfloat_fail);


  g_test_add_func (
    "/crank/base/test/eq/cplxfloat/cimm",
    test_assert_eqcplxfloat_cimm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/cplxfloat/cimm/fail",
    test_assert_eqcplxfloat_cimm_fail);


  g_test_add_func (
    "/crank/base/test/eq/permutation/imm",
    test_assert_eq_permutation_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/permutation/imm/fail",
    test_assert_eq_permutation_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/vecbool/2/imm",
    test_assert_eq_vecbool2_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/vecbool/2/imm/fail",
    test_assert_eq_vecbool2_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/vecbool/n/imm",
    test_assert_eq_vecbool_n_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/vecbool/n/imm/fail",
    test_assert_eq_vecbool_n_imm_fail);



  g_test_add_func (
    "/crank/base/test/eq/vecint/2/imm",
    test_assert_eq_vecint2_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/vecint/2/imm/fail",
    test_assert_eq_vecint2_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/vecint/n/imm",
    test_assert_eq_vecint_n_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/vecint/n/imm/fail",
    test_assert_eq_vecint_n_imm_fail);



  g_test_add_func (
    "/crank/base/test/eq/vecfloat/2/imm",
    test_assert_eq_vecfloat2_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/vecfloat/2/imm/fail",
    test_assert_eq_vecfloat2_imm_fail);


  g_test_add_func (
    "/crank/base/test/eq/vecfloat/n/imm",
    test_assert_eq_vecfloat_n_imm);

  crank_test_add_func_expected_fail (
    "/crank/base/test/eq/vecfloat/n/imm/fail",
    test_assert_eq_vecfloat_n_imm_fail);



  g_test_run ();
  return 0;
}


//////// Definition ////////////////////////////////////////////////////////////


static void
test_always_pass (void)
{
  // Tests 1 + 1 == 2
  g_assert_cmpuint ((1 + 1), ==, 2);
}

static void
test_always_fail (void)
{
  // Tests 0 == 1, which is obviously wrong.
  g_assert_cmpuint (0, ==, 1);
}


static void
test_test_expected_fail_onpass (void)
{
  g_test_trap_subprocess (
    "/crank/base/test/expected_fail/subprocess",
    0,
    G_TEST_SUBPROCESS_INHERIT_STDERR);
  g_test_trap_assert_failed ();
}


static void
test_test_timeout_1000 (void)
{
  // Sleep for 0.001 sec
  g_usleep (1000);
}


static void
test_assert_eqarray_bool (void)
{
  gboolean a[4] = {TRUE,  TRUE,   FALSE,  FALSE};
  gboolean b[4] = {TRUE,  TRUE,   FALSE,  FALSE};

  crank_assert_eqarray_bool (a, 4, b, 4);
}

static void
test_assert_eqarray_bool_fail (void)
{
  gboolean a[4] = {TRUE,  TRUE,   TRUE,   FALSE};
  gboolean b[4] = {TRUE,  TRUE,   FALSE,  FALSE};

  crank_assert_eqarray_bool (a, 4, b, 4);
}




static void
test_assert_eqarray_bool_imm (void)
{
  gboolean a[4] = {TRUE,  TRUE,   FALSE,  FALSE};

  crank_assert_eqarray_bool_imm (a, 4,    TRUE, TRUE, FALSE, FALSE);
}

static void
test_assert_eqarray_bool_imm_fail (void)
{
  gboolean a[4] = {TRUE,  TRUE,   TRUE,   FALSE};

  crank_assert_eqarray_bool_imm (a, 4,    TRUE, TRUE, FALSE, FALSE);
}




static void
test_assert_eqarray_int (void)
{
  gint a[4] = {1, 1, 2, 3};
  gint b[4] = {1, 1, 2, 3};

  crank_assert_eqarray_int (a, 4, b, 4);
}

static void
test_assert_eqarray_int_fail (void)
{
  gint a[4] = {1, 2, 3, 5};
  gint b[4] = {1, 1, 2, 3};

  crank_assert_eqarray_int (a, 4, b, 4);
}




static void
test_assert_eqarray_int_imm (void)
{
  gint a[4] = {1, 1, 2, 3};

  crank_assert_eqarray_int_imm (a, 4, 1, 1, 2, 3);
}

static void
test_assert_eqarray_int_imm_fail (void)
{
  gint a[4] = {1, 2, 3, 5};

  crank_assert_eqarray_int_imm (a, 4, 1, 1, 2, 3);
}




static void
test_assert_eqarray_uint (void)
{
  guint a[4] = {1, 1, 2, 3};
  guint b[4] = {1, 1, 2, 3};

  crank_assert_eqarray_uint (a, 4, b, 4);
}

static void
test_assert_eqarray_uint_fail (void)
{
  guint a[4] = {1, 2, 3, 5};
  guint b[4] = {1, 1, 2, 3};

  crank_assert_eqarray_uint (a, 4, b, 4);
}




static void
test_assert_eqarray_uint_imm (void)
{
  guint a[4] = {1, 1, 2, 3};

  crank_assert_eqarray_uint_imm (a, 4,    1, 1, 2, 3);
}

static void
test_assert_eqarray_uint_imm_fail (void)
{
  guint a[4] = {1, 2, 3, 5};

  crank_assert_eqarray_uint_imm (a, 4,    1, 1, 2, 3);
}





static void
test_assert_eqarray_float (void)
{

  gfloat a[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  gfloat b[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};

  crank_assert_eqarray_float (a, 10, b, 10);
}

static void
test_assert_eqarray_float_fail (void)
{
  gfloat a[10] = { 1.0f, 2.1f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
  gfloat b[10] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};

  crank_assert_eqarray_float (a, 10, b, 10);
}




static void
test_assert_eqarray_float_imm (void)
{

  gfloat a[4] = { 1.0f, 2.0f, 3.0f, 4.0f };

  crank_assert_eqarray_float_imm (a, 4, 1.0f, 2.0f, 3.0f, 4.0f);
}

static void
test_assert_eqarray_float_imm_fail (void)
{

  gfloat a[4] = { 1.0f, 2.0f, 3.0f, 4.0f };

  crank_assert_eqarray_float_imm (a, 4, 1.0f, 2.1f, 3.0f, 4.0f);
}



static void
test_assert_eqarray_pointer (void)
{
  gpointer a[4] = {
    GINT_TO_POINTER(0x1111),
    GINT_TO_POINTER(0x2222),
    GINT_TO_POINTER(0x3333),
    GINT_TO_POINTER(0x4444)
  };
  gpointer b[4] = {
    GINT_TO_POINTER(0x1111),
    GINT_TO_POINTER(0x2222),
    GINT_TO_POINTER(0x3333),
    GINT_TO_POINTER(0x4444)
  };

  crank_assert_eqarray_pointer (a, 4, b, 4);
}

static void
test_assert_eqarray_pointer_fail (void)
{
  gpointer a[4] = {
    GINT_TO_POINTER(0x1111),
    GINT_TO_POINTER(0x1112),
    GINT_TO_POINTER(0x3333),
    GINT_TO_POINTER(0x4444)
  };
  gpointer b[4] = {
    GINT_TO_POINTER(0x1111),
    GINT_TO_POINTER(0x2222),
    GINT_TO_POINTER(0x3333),
    GINT_TO_POINTER(0x4444)
  };

  crank_assert_eqarray_pointer (a, 4, b, 4);
}



static void
test_assert_eqarray_pointer_imm (void)
{
  gpointer a[4] = {
    GINT_TO_POINTER(0x1111),
    GINT_TO_POINTER(0x2222),
    GINT_TO_POINTER(0x3333),
    GINT_TO_POINTER(0x4444)
  };

  crank_assert_eqarray_pointer_imm (a, 4,
                                    GINT_TO_POINTER(0x1111),
                                    GINT_TO_POINTER(0x2222),
                                    GINT_TO_POINTER(0x3333),
                                    GINT_TO_POINTER(0x4444) );
}

static void
test_assert_eqarray_pointer_imm_fail (void)
{
  gpointer a[4] = {
    GINT_TO_POINTER(0x1111),
    GINT_TO_POINTER(0x2220),
    GINT_TO_POINTER(0x3333),
    GINT_TO_POINTER(0x4444)
  };

  crank_assert_eqarray_pointer_imm (a, 4,
                                    GINT_TO_POINTER(0x1111),
                                    GINT_TO_POINTER(0x2222),
                                    GINT_TO_POINTER(0x3333),
                                    GINT_TO_POINTER(0x4444) );
}



static void
test_assert_eq_glist_imm (void)
{
  GList *a = NULL;

  a = g_list_append (a, GINT_TO_POINTER(0x1000));
  a = g_list_append (a, GINT_TO_POINTER(0x2000));
  a = g_list_append (a, GINT_TO_POINTER(0x3000));
  a = g_list_append (a, GINT_TO_POINTER(0x4000));

  crank_assert_eq_glist_imm (a,
                             GINT_TO_POINTER(0x1000),
                             GINT_TO_POINTER(0x2000),
                             GINT_TO_POINTER(0x3000),
                             GINT_TO_POINTER(0x4000) );

  g_list_free (a);
}

static void
test_assert_eq_glist_imm_fail (void)
{
  GList *a = NULL;

  a = g_list_append (a, GINT_TO_POINTER(0x1000));
  a = g_list_append (a, GINT_TO_POINTER(0x2000));
  a = g_list_append (a, GINT_TO_POINTER(0x3100));
  a = g_list_append (a, GINT_TO_POINTER(0x4000));

  crank_assert_eq_glist_imm (a,
                             GINT_TO_POINTER(0x1000),
                             GINT_TO_POINTER(0x2000),
                             GINT_TO_POINTER(0x3000),
                             GINT_TO_POINTER(0x4000) );

  g_list_free (a);
}



static void
test_assert_eq_gptrarray_imm (void)
{
  GPtrArray *a = g_ptr_array_new ();

  g_ptr_array_add (a, GINT_TO_POINTER(0x1000));
  g_ptr_array_add (a, GINT_TO_POINTER(0x2000));
  g_ptr_array_add (a, GINT_TO_POINTER(0x3000));
  g_ptr_array_add (a, GINT_TO_POINTER(0x4000));

  crank_assert_eq_gptrarray_imm (a,
                                 GINT_TO_POINTER(0x1000),
                                 GINT_TO_POINTER(0x2000),
                                 GINT_TO_POINTER(0x3000),
                                 GINT_TO_POINTER(0x4000) );

  g_ptr_array_unref (a);
}

static void
test_assert_eq_gptrarray_imm_fail (void)
{
  GPtrArray *a = g_ptr_array_new ();

  g_ptr_array_add (a, GINT_TO_POINTER(0x4000));
  g_ptr_array_add (a, GINT_TO_POINTER(0x3000));
  g_ptr_array_add (a, GINT_TO_POINTER(0x2000));
  g_ptr_array_add (a, GINT_TO_POINTER(0x1000));

  crank_assert_eq_gptrarray_imm (a,
                                 GINT_TO_POINTER(0x1000),
                                 GINT_TO_POINTER(0x2000),
                                 GINT_TO_POINTER(0x3000),
                                 GINT_TO_POINTER(0x4000) );

  g_ptr_array_unref (a);
}


static void
test_assert_cmpfloat (void)
{
  // Tests whether assertion actually allows errors within given errors.
  crank_assert_cmpfloat_d (3.0f, ==, 3.5f, 1.0f);
  crank_assert_cmpfloat_d (2.0f, <, 3.5f, 1.0f);
}

static void
test_assert_cmpfloat_fail (void)
{
  // Tests whether assertion can actually fails.
  crank_assert_cmpfloat_d (7.5f, <, 3.5f, 1.0f);
}


static void
test_assert_eqcplxfloat (void)
{
  CrankCplxFloat a = {3.0f, 2.0f};
  CrankCplxFloat b = {3.5f, 2.1f};
  CrankCplxFloat c = {2.9f, 1.4f};

  // Tests whether assertion actually allows errors within given errors.
  crank_assert_eqcplxfloat_d (&a, &b, 1.0f);
  crank_assert_eqcplxfloat_d (&a, &c, 1.0f);
}

static void
test_assert_eqcplxfloat_fail (void)
{
  // Tests whether assertion can actually fails.
  CrankCplxFloat a = {3.0f, 2.0f};
  CrankCplxFloat b = {4.2f, 2.0f};

  crank_assert_eqcplxfloat_d (&a, &b, 1.0f);
}


static void
test_assert_eqcplxfloat_cimm (void)
{
  CrankCplxFloat a = {3.0f, 2.0f};

  // Tests whether assertion actually allows errors within given errors.
  crank_assert_eqcplxfloat_d_cimm (&a, 3.5f, 2.1f, 1.0f);
  crank_assert_eqcplxfloat_d_cimm (&a, 2.9f, 1.4f, 1.0f);
}

static void
test_assert_eqcplxfloat_cimm_fail (void)
{
  // Tests whether assertion can actually fails.
  CrankCplxFloat a = {3.0f, 2.0f};

  crank_assert_eqcplxfloat_d_cimm (&a, 4.2f, 2.0f, 1.0f);
}


static void
test_assert_eq_permutation_imm (void)
{
  CrankPermutation a = {0};
  crank_permutation_init (&a, 4, 0, 1, 3, 2);

  crank_assert_eq_permutation_imm (&a, 0, 1, 3, 2);
  crank_permutation_fini (&a);
}

static void
test_assert_eq_permutation_imm_fail (void)
{
  CrankPermutation a = {0};
  crank_permutation_init (&a, 4, 0, 1, 2, 3);

  crank_assert_eq_permutation_imm (&a, 0, 1, 3, 2);
  crank_permutation_fini (&a);
}



static void
test_assert_eq_vecbool2_imm (void)
{
  CrankVecBool2 a = {TRUE, FALSE};

  crank_assert_eq_vecbool2_imm (&a, TRUE, FALSE);
}

static void
test_assert_eq_vecbool2_imm_fail (void)
{
  CrankVecBool2 a = {TRUE, TRUE};

  crank_assert_eq_vecbool2_imm (&a, TRUE, FALSE);
}




static void
test_assert_eq_vecbool_n_imm (void)
{
  CrankVecBoolN a = {0};
  crank_vec_bool_n_init (&a, 5, TRUE, FALSE, FALSE, TRUE, TRUE);

  crank_assert_eq_vecbool_n_imm (&a, TRUE, FALSE, FALSE, TRUE, TRUE);
  crank_vec_bool_n_fini (&a);
}

static void
test_assert_eq_vecbool_n_imm_fail (void)
{
  CrankVecBoolN a = {0};
  crank_vec_bool_n_init (&a, 5, TRUE, TRUE, FALSE, TRUE, TRUE);

  crank_assert_eq_vecbool_n_imm (&a, TRUE, FALSE, FALSE, TRUE, TRUE);
  crank_vec_bool_n_fini (&a);
}



static void
test_assert_eq_vecint2_imm (void)
{
  CrankVecInt2 a = {3, 4};

  crank_assert_eq_vecint2_imm (&a, 3, 4);
}

static void
test_assert_eq_vecint2_imm_fail (void)
{
  CrankVecInt2 a = {3, 4};

  crank_assert_eq_vecint2_imm (&a, 0, 0);
}




static void
test_assert_eq_vecint_n_imm (void)
{
  CrankVecIntN a = {0};
  crank_vec_int_n_init (&a, 5, 1, 2, 3, 4, 5);

  crank_assert_eq_vecint_n_imm (&a, 1, 2, 3, 4, 5);
  crank_vec_int_n_fini (&a);
}

static void
test_assert_eq_vecint_n_imm_fail (void)
{
  CrankVecIntN a = {0};
  crank_vec_int_n_init (&a, 5, 1, 2, 3, 4, 6);

  crank_assert_eq_vecint_n_imm (&a, 1, 2, 3, 4, 5);
  crank_vec_int_n_fini (&a);
}



static void
test_assert_eq_vecfloat2_imm (void)
{
  CrankVecFloat2 a = {3.0f, 4.0f};

  crank_assert_eq_vecfloat2_imm (&a, 3.0f, 4.0f);
}

static void
test_assert_eq_vecfloat2_imm_fail (void)
{
  CrankVecFloat2 a = {3.0f, 4.0f};

  crank_assert_eq_vecfloat2_imm (&a, 0.0f, 0.0f);
}




static void
test_assert_eq_vecfloat_n_imm (void)
{
  CrankVecFloatN a = {0};
  crank_vec_float_n_init (&a, 5, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f);

  crank_assert_eq_vecfloat_n_imm (&a, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
  crank_vec_float_n_fini (&a);
}

static void
test_assert_eq_vecfloat_n_imm_fail (void)
{
  CrankVecFloatN a = {0};
  crank_vec_float_n_init (&a, 5, 2.0f, 2.0f, 3.0f, 4.0f, 5.0f);

  crank_assert_eq_vecfloat_n_imm (&a, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
  crank_vec_float_n_fini (&a);
}