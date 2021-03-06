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

static void test_assert_float_real (const gchar *file,
                                    const guint  line,
                                    const gchar *func,
                                    const gchar *a_str,
                                    const gchar *b_str,
                                    gfloat       a,
                                    gfloat       b);

static void test_2_equal (void);
static void test_2_to_string (void);

static void test_2_get (void);
static void test_2_get_row (void);
static void test_2_get_col (void);

static void test_2_tr (void);
static void test_2_det (void);
static void test_2_cof (void);
static void test_2_adj (void);

static void test_2_neg (void);
static void test_2_transpose (void);
static void test_2_inverse (void);

static void test_2_muls (void);
static void test_2_divs (void);
static void test_2_mulv (void);
static void test_2_add (void);
static void test_2_sub (void);
static void test_2_mul (void);
static void test_2_mixs (void);
static void test_2_mix (void);

static void test_3_init_rot (void);
static void test_3_get_rot (void);


static void test_n_equal (void);
static void test_n_to_string (void);

static void test_n_get (void);
static void test_n_get_row (void);
static void test_n_get_col (void);
static void test_n_slice (void);

static void test_n_tr (void);
static void test_n_det (void);
static void test_n_cof (void);
static void test_n_adj (void);
static void test_n_diag (void);

static void test_n_neg (void);
static void test_n_transpose (void);
static void test_n_inverse (void);

static void test_n_muls (void);
static void test_n_divs (void);
static void test_n_mulv (void);
static void test_n_add (void);
static void test_n_sub (void);
static void test_n_mul (void);
static void test_n_mixs (void);
static void test_n_mix (void);

static void test_n_shuffle_row (void);
static void test_n_shuffle_col (void);

static void test_n_init_row (void);
static void test_n_init_row_arr (void);
static void test_n_init_row_parr (void);
static void test_n_init_col (void);
static void test_n_init_col_arr (void);
static void test_n_init_col_parr (void);

static void test_n_upper_tri_inverse (void);
static void test_n_lower_tri_inverse (void);
static void test_n_diag_inverse (void);


//////// Main //////////////////////////////////////////////////////////////////

gint
main (gint    argc,
      gchar **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank/base/mat/float/2/equal",       test_2_equal);
  g_test_add_func ("/crank/base/mat/float/2/to_string",   test_2_to_string);
  g_test_add_func ("/crank/base/mat/float/2/get",         test_2_get);
  g_test_add_func ("/crank/base/mat/float/2/get_row",     test_2_get_row);
  g_test_add_func ("/crank/base/mat/float/2/get_col",     test_2_get_col);
  g_test_add_func ("/crank/base/mat/float/2/tr",          test_2_tr);
  g_test_add_func ("/crank/base/mat/float/2/det",         test_2_det);
  g_test_add_func ("/crank/base/mat/float/2/cof",         test_2_cof);
  g_test_add_func ("/crank/base/mat/float/2/adj",         test_2_adj);
  g_test_add_func ("/crank/base/mat/float/2/neg",         test_2_neg);
  g_test_add_func ("/crank/base/mat/float/2/transpose",   test_2_transpose);
  g_test_add_func ("/crank/base/mat/float/2/inverse",     test_2_inverse);
  g_test_add_func ("/crank/base/mat/float/2/muls",        test_2_muls);
  g_test_add_func ("/crank/base/mat/float/2/divs",        test_2_divs);
  g_test_add_func ("/crank/base/mat/float/2/mulv",        test_2_mulv);
  g_test_add_func ("/crank/base/mat/float/2/add",         test_2_add);
  g_test_add_func ("/crank/base/mat/float/2/sub",         test_2_sub);
  g_test_add_func ("/crank/base/mat/float/2/mul",         test_2_mul);
  g_test_add_func ("/crank/base/mat/float/2/mixs",        test_2_mixs);
  g_test_add_func ("/crank/base/mat/float/2/mix",         test_2_mix);

  g_test_add_func ("/crank/base/mat/float/3/rot/init",    test_3_init_rot);
  g_test_add_func ("/crank/base/mat/float/3/rot/get",     test_3_get_rot);

  g_test_add_func ("/crank/base/mat/float/n/equal",       test_n_equal);
  g_test_add_func ("/crank/base/mat/float/n/to_string",   test_n_to_string);
  g_test_add_func ("/crank/base/mat/float/n/get",         test_n_get);
  g_test_add_func ("/crank/base/mat/float/n/get_row",     test_n_get_row);
  g_test_add_func ("/crank/base/mat/float/n/get_col",     test_n_get_col);
  g_test_add_func ("/crank/base/mat/float/n/slice",       test_n_slice);
  g_test_add_func ("/crank/base/mat/float/n/tr",          test_n_tr);
  g_test_add_func ("/crank/base/mat/float/n/det",         test_n_det);
  g_test_add_func ("/crank/base/mat/float/n/cof",         test_n_cof);
  g_test_add_func ("/crank/base/mat/float/n/adj",         test_n_adj);
  g_test_add_func ("/crank/base/mat/float/n/neg",         test_n_neg);
  g_test_add_func ("/crank/base/mat/float/n/diag",        test_n_diag);
  g_test_add_func ("/crank/base/mat/float/n/transpose",   test_n_transpose);
  g_test_add_func ("/crank/base/mat/float/n/inverse",     test_n_inverse);
  g_test_add_func ("/crank/base/mat/float/n/muls",        test_n_muls);
  g_test_add_func ("/crank/base/mat/float/n/divs",        test_n_divs);
  g_test_add_func ("/crank/base/mat/float/n/mulv",        test_n_mulv);
  g_test_add_func ("/crank/base/mat/float/n/add",         test_n_add);
  g_test_add_func ("/crank/base/mat/float/n/sub",         test_n_sub);
  g_test_add_func ("/crank/base/mat/float/n/mul",         test_n_mul);
  g_test_add_func ("/crank/base/mat/float/n/mixs",        test_n_mixs);
  g_test_add_func ("/crank/base/mat/float/n/mix",         test_n_mix);

  g_test_add_func ("/crank/base/mat/float/n/shuffle/row", test_n_shuffle_row);
  g_test_add_func ("/crank/base/mat/float/n/shuffle/col", test_n_shuffle_col);

  g_test_add_func ("/crank/base/mat/float/n/init/row",        test_n_init_row);
  g_test_add_func ("/crank/base/mat/float/n/init/row/arr",
                   test_n_init_row_arr);
  g_test_add_func ("/crank/base/mat/float/n/init/row/parr",
                   test_n_init_row_parr);
  g_test_add_func ("/crank/base/mat/float/n/init/col",        test_n_init_col);
  g_test_add_func ("/crank/base/mat/float/n/init/col/arr",
                   test_n_init_col_arr);
  g_test_add_func ("/crank/base/mat/float/n/init/col/parr",
                   test_n_init_col_parr);

  g_test_add_func ("/crank/base/mat/float/n/supple/inverse/upper",
                   test_n_upper_tri_inverse);
  g_test_add_func ("/crank/base/mat/float/n/supple/inverse/lower",
                   test_n_lower_tri_inverse);
  g_test_add_func ("/crank/base/mat/float/n/supple/inverse/diag",
                   test_n_diag_inverse);

  g_test_run ();
  return 0;
}


//////// Definition ////////////////////////////////////////////////////////////

static void
test_assert_float_real (const gchar *file,
                        const guint  line,
                        const gchar *func,
                        const gchar *a_str,
                        const gchar *b_str,
                        gfloat       a,
                        gfloat       b)
{
  if ((a < b - 0.0001f) || (b + 0.0001f < a))
    {
      g_error (
        "%s:%u:%s: assertion failed: (%s == %s): (%g == %g)"
        " (with diff of %g)",
        file, line, func,
        a_str, b_str,
        a, b, b - a);
    }
}

#define test_assert_float(a, b) \
  test_assert_float_real( \
    __FILE__, \
    __LINE__, \
    G_STRFUNC, \
    G_STRINGIFY(a), \
    G_STRINGIFY(b), \
    a, \
    b)


static void
test_2_equal (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 b = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 c = {0.0f, 0.0f,     0.0f, 0.0f};

  g_assert (crank_mat_float2_equal (&a, &b));
  g_assert (!crank_mat_float2_equal (&a, &c));
}

static void
test_2_to_string (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f, 3.0f, 4.0f};
  gchar *astr = crank_mat_float2_to_string (&a);

  g_assert_cmpstr (astr, ==, "[[1, 2], [3, 4]]");

  g_free (astr);
}


static void
test_2_get (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f };

  test_assert_float (crank_mat_float2_get (&a, 0, 0), 1.0f);
  test_assert_float (crank_mat_float2_get (&a, 0, 1), 2.0f);
  test_assert_float (crank_mat_float2_get (&a, 1, 0), 3.0f);
  test_assert_float (crank_mat_float2_get (&a, 1, 1), 4.0f);
}

static void
test_2_get_row (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankVecFloat2 rv;

  crank_mat_float2_get_row (&a, 0, &rv);

  test_assert_float (rv.x, 1.0f);
  test_assert_float (rv.y, 2.0f);

  crank_mat_float2_get_row (&a, 1, &rv);

  test_assert_float (rv.x, 3.0f);
  test_assert_float (rv.y, 4.0f);
}

static void
test_2_get_col (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankVecFloat2 cv;

  crank_mat_float2_get_col (&a, 0, &cv);

  test_assert_float (cv.x, 1.0f);
  test_assert_float (cv.y, 3.0f);

  crank_mat_float2_get_col (&a, 1, &cv);

  test_assert_float (cv.x, 2.0f);
  test_assert_float (cv.y, 4.0f);
}

static void
test_2_tr (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};

  test_assert_float (crank_mat_float2_get_tr (&a), 5.0f);
}

static void
test_2_det (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};

  test_assert_float (crank_mat_float2_get_det (&a), -2.0f);
}

static void
test_2_cof (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 cof;

  crank_mat_float2_get_cof (&a, &cof);

  test_assert_float (cof.m00,  4.0f);
  test_assert_float (cof.m01, -3.0f);
  test_assert_float (cof.m10, -2.0f);
  test_assert_float (cof.m11,  1.0f);
}

static void
test_2_adj (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 adj;

  crank_mat_float2_get_adj (&a, &adj);

  test_assert_float (adj.m00,  4.0f);
  test_assert_float (adj.m01, -2.0f);
  test_assert_float (adj.m10, -3.0f);
  test_assert_float (adj.m11,  1.0f);
}

static void
test_2_neg (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 r;

  crank_mat_float2_neg (&a, &r);

  test_assert_float (r.m00, -1.0f);
  test_assert_float (r.m01, -2.0f);
  test_assert_float (r.m10, -3.0f);
  test_assert_float (r.m11, -4.0f);
}

static void
test_2_transpose (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 r;

  crank_mat_float2_transpose (&a, &r);

  test_assert_float (r.m00, 1.0f);
  test_assert_float (r.m01, 3.0f);
  test_assert_float (r.m10, 2.0f);
  test_assert_float (r.m11, 4.0f);
}

static void
test_2_inverse (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 r;

  crank_mat_float2_inverse (&a, &r);

  test_assert_float (r.m00, -2.0f);
  test_assert_float (r.m01,  1.0f);
  test_assert_float (r.m10,  1.5f);
  test_assert_float (r.m11, -0.5f);
}


static void
test_2_muls (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 r;

  crank_mat_float2_muls (&a, 2.0f, &r);

  test_assert_float (r.m00, 2.0f);
  test_assert_float (r.m01, 4.0f);
  test_assert_float (r.m10, 6.0f);
  test_assert_float (r.m11, 8.0f);
}

static void
test_2_divs (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 r;

  crank_mat_float2_divs (&a, 2.0f, &r);

  test_assert_float (r.m00, 0.5f);
  test_assert_float (r.m01, 1.0f);
  test_assert_float (r.m10, 1.5f);
  test_assert_float (r.m11, 2.0f);
}

static void
test_2_mulv (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankVecFloat2 b = {3.0f, 4.0f};
  CrankVecFloat2 r;

  crank_mat_float2_mulv (&a, &b, &r);

  test_assert_float (r.x, 11.0f);
  test_assert_float (r.y, 25.0f);
}

static void
test_2_add (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,    3.0f, 4.0f};
  CrankMatFloat2 b = {2.0f, 3.0f,    5.0f, 7.0f};
  CrankMatFloat2 r;

  crank_mat_float2_add (&a, &b, &r);

  test_assert_float (r.m00, 3.0f);
  test_assert_float (r.m01, 5.0f);
  test_assert_float (r.m10, 8.0f);
  test_assert_float (r.m11, 11.0f);
}

static void
test_2_sub (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,    3.0f, 4.0f};
  CrankMatFloat2 b = {2.0f, 3.0f,    5.0f, 7.0f};
  CrankMatFloat2 r;

  crank_mat_float2_sub (&a, &b, &r);

  test_assert_float (r.m00, -1.0f);
  test_assert_float (r.m01, -1.0f);
  test_assert_float (r.m10, -2.0f);
  test_assert_float (r.m11, -3.0f);
}


static void
test_2_mul (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 b = {3.0f, 6.0f,     9.0f, 12.0f};
  CrankMatFloat2 r;

  crank_mat_float2_mul (&a, &b, &r);

  test_assert_float (r.m00, 21.0f);
  test_assert_float (r.m01, 30.0f);
  test_assert_float (r.m10, 45.0f);
  test_assert_float (r.m11, 66.0f);
}

static void
test_2_mixs (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 b = {3.0f, 6.0f,     9.0f, 12.0f};
  CrankMatFloat2 r;

  crank_mat_float2_mixs (&a, &b, 0.5f, &r);

  test_assert_float (r.m00, 2.0f);
  test_assert_float (r.m01, 4.0f);
  test_assert_float (r.m10, 6.0f);
  test_assert_float (r.m11, 8.0f);
}

static void
test_2_mix (void)
{
  CrankMatFloat2 a = {1.0f, 2.0f,     3.0f, 4.0f};
  CrankMatFloat2 b = {3.0f, 6.0f,     9.0f, 12.0f};
  CrankMatFloat2 c = {0.0f, 0.25f,    0.5f, 0.75f};
  CrankMatFloat2 r;

  crank_mat_float2_mix (&a, &b, &c, &r);

  test_assert_float (r.m00, 1.0f);
  test_assert_float (r.m01, 3.0f);
  test_assert_float (r.m10, 6.0f);
  test_assert_float (r.m11, 10.0f);
}


static void
test_3_init_rot (void)
{
  CrankMatFloat3 m;

  crank_mat_float3_init_urot (&m, G_PI_4, 0.5774f, 0.5774f, 0.5774f);

  crank_assert_cmpfloat (m.m00, ==,  0.8048f);
  crank_assert_cmpfloat (m.m01, ==, -0.3106f);
  crank_assert_cmpfloat (m.m02, ==,  0.5058f);

  crank_assert_cmpfloat (m.m10, ==,  0.5058f);
  crank_assert_cmpfloat (m.m11, ==,  0.8048f);
  crank_assert_cmpfloat (m.m12, ==, -0.3106f);

  crank_assert_cmpfloat (m.m20, ==, -0.3106f);
  crank_assert_cmpfloat (m.m21, ==,  0.5058f);
  crank_assert_cmpfloat (m.m22, ==,  0.8048f);
}

static void
test_3_get_rot (void)
{
  CrankMatFloat3 m;
  CrankVecFloat3 axis;

  crank_mat_float3_init (&m,
                          0.8048f, -0.3106f,  0.5058f,
                          0.5058f,  0.8048f, -0.3106f,
                         -0.3106f,  0.5058f,  0.8048f);

  crank_assert_cmpfloat_d (crank_mat_float3_get_rangle (&m), ==, G_PI_4, 0.0002);

  crank_mat_float3_get_raxis (&m, &axis);
  crank_assert_cmpfloat (axis.x, ==,  0.5774f);
  crank_assert_cmpfloat (axis.y, ==,  0.5774f);
  crank_assert_cmpfloat (axis.z, ==,  0.5774f);
}



static void
test_n_equal (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};
  CrankMatFloatN c = {0};

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_init (&b, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_init (&c, 3, 2,
                          1.0f, 2.0f,
                          3.0f, 4.0f,
                          5.0f, 6.0f);

  g_assert (crank_mat_float_n_equal (&a, &b));
  g_assert (!crank_mat_float_n_equal (&a, &c));

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&c);
}

static void
test_n_to_string (void)
{
  CrankMatFloatN a = {0};
  gchar *astr;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  astr = crank_mat_float_n_to_string (&a);

  g_assert_cmpstr (astr, ==, "[[1, 2, 3], [4, 5, 6]]");

  crank_mat_float_n_fini (&a);
}

static void
test_n_get (void)
{
  CrankMatFloatN a = {0};

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  test_assert_float (crank_mat_float_n_get (&a, 0, 0), 1.0f);
  test_assert_float (crank_mat_float_n_get (&a, 0, 1), 2.0f);
  test_assert_float (crank_mat_float_n_get (&a, 0, 2), 3.0f);
  test_assert_float (crank_mat_float_n_get (&a, 1, 0), 4.0f);
  test_assert_float (crank_mat_float_n_get (&a, 1, 1), 5.0f);
  test_assert_float (crank_mat_float_n_get (&a, 1, 2), 6.0f);

  crank_mat_float_n_fini (&a);
}

static void
test_n_get_row (void)
{
  CrankMatFloatN a = {0};
  CrankVecFloatN r = {0};

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_get_row (&a, 0, &r);

  g_assert_cmpuint (r.n, ==, 3);
  test_assert_float (r.data[0], 1.0f);
  test_assert_float (r.data[1], 2.0f);
  test_assert_float (r.data[2], 3.0f);

  crank_mat_float_n_get_row (&a, 1, &r);

  g_assert_cmpuint (r.n, ==, 3);
  test_assert_float (r.data[0], 4.0f);
  test_assert_float (r.data[1], 5.0f);
  test_assert_float (r.data[2], 6.0f);

  crank_mat_float_n_fini (&a);
  crank_vec_float_n_fini (&r);
}

static void
test_n_get_col (void)
{
  CrankMatFloatN a = {0};
  CrankVecFloatN c = {0};

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_get_col (&a, 0, &c);

  g_assert_cmpuint (c.n, ==, 2);
  test_assert_float (c.data[0], 1.0f);
  test_assert_float (c.data[1], 4.0f);

  crank_mat_float_n_get_col (&a, 1, &c);

  g_assert_cmpuint (c.n, ==, 2);
  test_assert_float (c.data[0], 2.0f);
  test_assert_float (c.data[1], 5.0f);

  crank_mat_float_n_get_col (&a, 2, &c);

  g_assert_cmpuint (c.n, ==, 2);
  test_assert_float (c.data[0], 3.0f);
  test_assert_float (c.data[1], 6.0f);

  crank_mat_float_n_fini (&a);
  crank_vec_float_n_fini (&c);
}

static void
test_n_slice (void)
{
  CrankMatFloatN a;
  CrankMatFloatN b;

  crank_mat_float_n_init (&a, 3, 3,
                          1.0f,   2.0f,   3.0f,
                          4.0f,   5.0f,   6.0f,
                          7.0f,   8.0f,   9.0f);

  crank_mat_float_n_slice (&a, 1, 1, 3, 2, &b);

  g_assert_cmpuint (b.rn, ==, 2);
  g_assert_cmpuint (b.cn, ==, 1);

  test_assert_float (b.data[0], 5.0f);
  test_assert_float (b.data[1], 8.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
}

static void
test_n_tr (void)
{
  CrankMatFloatN a = {0};

  crank_mat_float_n_init (&a, 5, 5,
                          1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 2.0f, 0.0f, 3.0f, 1.0f,
                          0.0f, 0.0f, 3.0f, 0.0f, 0.0f,
                          1.0f, 3.0f, 0.0f, 4.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f, 5.0f);

  test_assert_float (crank_mat_float_n_get_tr (&a), 15.0f);

  crank_mat_float_n_fini (&a);
}

static void
test_n_det (void)
{
  CrankMatFloatN a = {0};

  crank_mat_float_n_init (&a, 5, 5,
                          1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 2.0f, 0.0f, 3.0f, 1.0f,
                          0.0f, 0.0f, 3.0f, 0.0f, 0.0f,
                          1.0f, 3.0f, 0.0f, 4.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f, 5.0f);

  test_assert_float (crank_mat_float_n_get_det (&a), -54.0f);

  crank_mat_float_n_fini (&a);
}

static void
test_n_cof (void)
{
  CrankMatFloatN a;
  CrankMatFloatN r;

  CrankVecFloatN rv;

  crank_mat_float_n_init (&a, 5, 5,
                          4.0f, 3.0f, 2.0f, 1.0f, 4.0f,
                          3.0f, 4.0f, 3.0f, 2.0f, 1.0f,
                          2.0f, 3.0f, 4.0f, 3.0f, 2.0f,
                          1.0f, 2.0f, 3.0f, 4.0f, 3.0f,
                          4.0f, 1.0f, 2.0f, 3.0f, 4.0f);

  crank_mat_float_n_get_cof (&a, &r);

  crank_mat_float_n_get_row (&r, 3, &rv);

  crank_assert_eq_vecfloat_n_imm (&rv, 40, -48, 64, -48, -24);

  crank_vec_float_n_fini (&rv);
  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&r);
}

static void
test_n_adj (void)
{
  CrankMatFloatN a;
  CrankMatFloatN r;

  CrankVecFloatN rv;

  crank_mat_float_n_init (&a, 5, 5,
                          4.0f, 3.0f, 2.0f, 1.0f, 4.0f,
                          3.0f, 4.0f, 3.0f, 2.0f, 1.0f,
                          2.0f, 3.0f, 4.0f, 3.0f, 2.0f,
                          1.0f, 2.0f, 3.0f, 4.0f, 3.0f,
                          4.0f, 1.0f, 2.0f, 3.0f, 4.0f);

  crank_mat_float_n_get_adj (&a, &r);

  crank_mat_float_n_get_row (&r, 3, &rv);

  crank_assert_eq_vecfloat_n_imm (&rv, 40, -48, 64, -48, -24);

  crank_vec_float_n_fini (&rv);
  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&r);
}

static void
test_n_diag (void)
{
  CrankMatFloatN a = {0};
  CrankVecFloatN b = {0};

  crank_mat_float_n_init (&a, 5, 5,
                          1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 2.0f, 0.0f, 3.0f, 1.0f,
                          0.0f, 0.0f, 3.0f, 0.0f, 0.0f,
                          1.0f, 3.0f, 0.0f, 4.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f, 5.0f);

  crank_mat_float_n_get_diag (&a, &b);

  crank_assert_eq_vecfloat_n_imm (&b, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f);

  crank_mat_float_n_fini (&a);
}

static void
test_n_neg (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_neg (&a, &r);

  test_assert_float (r.data[0], -1.0f);
  test_assert_float (r.data[1], -2.0f);
  test_assert_float (r.data[2], -3.0f);
  test_assert_float (r.data[3], -4.0f);
  test_assert_float (r.data[4], -5.0f);
  test_assert_float (r.data[5], -6.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&r);
}

static void
test_n_transpose (void)
{

  CrankMatFloatN a = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_transpose (&a, &r);

  g_assert_cmpuint (r.rn, ==, 3);
  g_assert_cmpuint (r.cn, ==, 2);

  test_assert_float (r.data[0], 1.0f);
  test_assert_float (r.data[1], 4.0f);
  test_assert_float (r.data[2], 2.0f);
  test_assert_float (r.data[3], 5.0f);
  test_assert_float (r.data[4], 3.0f);
  test_assert_float (r.data[5], 6.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&r);
}

static void
test_n_inverse (void)
{
  CrankMatFloatN a;
  CrankMatFloatN r;

  CrankVecFloatN rv;

  crank_mat_float_n_init (&a, 5, 5,
                          4.0f, 3.0f, 2.0f, 1.0f, 4.0f,
                          3.0f, 4.0f, 3.0f, 2.0f, 1.0f,
                          2.0f, 3.0f, 4.0f, 3.0f, 2.0f,
                          1.0f, 2.0f, 3.0f, 4.0f, 3.0f,
                          4.0f, 1.0f, 2.0f, 3.0f, 4.0f);

  crank_mat_float_n_inverse (&a, &r);

  crank_mat_float_n_get_row (&r, 3, &rv);

  crank_assert_eq_vecfloat_n_imm (&rv, -0.3125f, 0.375f, -0.5f, 0.375f,
                                  0.1875f);

  crank_vec_float_n_fini (&rv);
  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&r);
}

static void
test_n_muls (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_muls (&a, 3, &r);

  test_assert_float (r.data[0], 3.0f);
  test_assert_float (r.data[1], 6.0f);
  test_assert_float (r.data[2], 9.0f);
  test_assert_float (r.data[3], 12.0f);
  test_assert_float (r.data[4], 15.0f);
  test_assert_float (r.data[5], 18.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&r);
}

static void
test_n_divs (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_muls (&a, 0.5, &r);

  test_assert_float (r.data[0], 0.5f);
  test_assert_float (r.data[1], 1.0f);
  test_assert_float (r.data[2], 1.5f);
  test_assert_float (r.data[3], 2.0f);
  test_assert_float (r.data[4], 2.5f);
  test_assert_float (r.data[5], 3.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&r);
}

static void
test_n_mulv (void)
{
  CrankMatFloatN a = {0};
  CrankVecFloatN b = {0};
  CrankVecFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_vec_float_n_init (&b, 3, 2.0f, 3.0f, 5.0f);

  crank_mat_float_n_mulv (&a, &b, &r);

  test_assert_float (r.data[0], 23.0f);
  test_assert_float (r.data[1], 53.0f);

  crank_vec_float_n_fini (&b);
  crank_mat_float_n_fini (&a);
}

static void
test_n_add (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);
  crank_mat_float_n_init (&b, 2, 3,
                          10.0f, 8.0f, 1.0f,
                          2.0f, 5.0f, 7.0f);

  crank_mat_float_n_add (&a, &b, &r);

  test_assert_float (r.data[0], 11.0f);
  test_assert_float (r.data[1], 10.0f);
  test_assert_float (r.data[2], 4.0f);
  test_assert_float (r.data[3], 6.0f);
  test_assert_float (r.data[4], 10.0f);
  test_assert_float (r.data[5], 13.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&r);
}

static void
test_n_sub (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);
  crank_mat_float_n_init (&b, 2, 3,
                          10.0f, 8.0f, 1.0f,
                          2.0f, 5.0f, 7.0f);

  crank_mat_float_n_sub (&a, &b, &r);

  test_assert_float (r.data[0], -9.0f);
  test_assert_float (r.data[1], -6.0f);
  test_assert_float (r.data[2], 2.0f);
  test_assert_float (r.data[3], 2.0f);
  test_assert_float (r.data[4], 0.0f);
  test_assert_float (r.data[5], -1.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&r);
}

static void
test_n_mul (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_init (&b, 3, 3,
                          3.0f, 2.0f, 1.0f,
                          2.0f, 1.0f, 0.0f,
                          1.0f, 0.0f, -1.0f);

  crank_mat_float_n_mul (&a, &b, &r);

  g_assert_cmpuint (r.rn, ==, 2);
  g_assert_cmpuint (r.cn, ==, 3);
  test_assert_float (r.data[0], 10.0f);
  test_assert_float (r.data[1], 4.0f);
  test_assert_float (r.data[2], -2.0f);
  test_assert_float (r.data[3], 28.0f);
  test_assert_float (r.data[4], 13.0f);
  test_assert_float (r.data[5], -2.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&r);
}

static void
test_n_mixs (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_init (&b, 2, 3,
                          3.0f, 6.0f, 9.0f,
                          12.0f, 15.0f, 18.0f);

  crank_mat_float_n_mixs (&a, &b, 0.5, &r);

  test_assert_float (r.data[0], 2.0f);
  test_assert_float (r.data[1], 4.0f);
  test_assert_float (r.data[2], 6.0f);
  test_assert_float (r.data[3], 8.0f);
  test_assert_float (r.data[4], 10.0f);
  test_assert_float (r.data[5], 12.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&r);
}

static void
test_n_mix (void)
{
  CrankMatFloatN a = {0};
  CrankMatFloatN b = {0};
  CrankMatFloatN c = {0};
  CrankMatFloatN r;

  crank_mat_float_n_init (&a, 2, 3,
                          1.0f, 2.0f, 3.0f,
                          4.0f, 5.0f, 6.0f);

  crank_mat_float_n_init (&b, 2, 3,
                          3.0f, 6.0f, 9.0f,
                          12.0f, 15.0f, 18.0f);

  crank_mat_float_n_init (&c, 2, 3,
                          0.0f, 0.2f, 0.4f,
                          0.6f, 0.8f, 1.0f);

  crank_mat_float_n_mix (&a, &b, &c, &r);

  test_assert_float (r.data[0], 1.0f);
  test_assert_float (r.data[1], 2.8f);
  test_assert_float (r.data[2], 5.4f);
  test_assert_float (r.data[3], 8.8f);
  test_assert_float (r.data[4], 13.0f);
  test_assert_float (r.data[5], 18.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&c);
  crank_mat_float_n_fini (&r);
}

static void
test_n_shuffle_row (void)
{
  CrankMatFloatN a;
  CrankMatFloatN b;
  CrankPermutation p;

  crank_mat_float_n_init (&a, 4, 2,
                          1.0f, 3.0f,
                          7.0f, 2.0f,
                          1.0f, 4.0f,
                          3.0f, 1.0f);

  crank_permutation_init (&p, 4,
                          1, 3, 0, 2);

  crank_mat_float_n_shuffle_row (&a, &p, &b);

  test_assert_float (b.data[0], 7.0f);
  test_assert_float (b.data[1], 2.0f);
  test_assert_float (b.data[2], 3.0f);
  test_assert_float (b.data[3], 1.0f);
  test_assert_float (b.data[4], 1.0f);
  test_assert_float (b.data[5], 3.0f);
  test_assert_float (b.data[6], 1.0f);
  test_assert_float (b.data[7], 4.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_permutation_fini (&p);
}
static void
test_n_shuffle_col (void)
{
  CrankMatFloatN a;
  CrankMatFloatN b;
  CrankPermutation p;

  crank_mat_float_n_init (&a, 2, 4,
                          1.0f, 7.0f, 1.0f, 3.0f,
                          3.0f, 2.0f, 4.0f, 1.0f);

  crank_permutation_init (&p, 4,
                          1, 3, 0, 2);

  crank_mat_float_n_shuffle_col (&a, &p, &b);

  test_assert_float (b.data[0], 7.0f);
  test_assert_float (b.data[1], 3.0f);
  test_assert_float (b.data[2], 1.0f);
  test_assert_float (b.data[3], 1.0f);
  test_assert_float (b.data[4], 2.0f);
  test_assert_float (b.data[5], 1.0f);
  test_assert_float (b.data[6], 3.0f);
  test_assert_float (b.data[7], 4.0f);

  crank_mat_float_n_fini (&a);
  crank_mat_float_n_fini (&b);
  crank_permutation_fini (&p);
}

static void
test_n_init_row (void)
{
  CrankVecFloatN rows[3];
  CrankMatFloatN a;

  crank_vec_float_n_init (rows + 0, 3, 0.0f, 1.0f, 2.0f);
  crank_vec_float_n_init (rows + 1, 3, 3.0f, 4.0f, 5.0f);
  crank_vec_float_n_init (rows + 2, 3, 6.0f, 7.0f, 8.0f);

  crank_mat_float_n_init_row (&a, 3, rows + 0, rows + 1, rows + 2);

  test_assert_float (a.data[0], 0.0f);
  test_assert_float (a.data[1], 1.0f);
  test_assert_float (a.data[2], 2.0f);
  test_assert_float (a.data[3], 3.0f);
  test_assert_float (a.data[4], 4.0f);
  test_assert_float (a.data[5], 5.0f);
  test_assert_float (a.data[6], 6.0f);
  test_assert_float (a.data[7], 7.0f);
  test_assert_float (a.data[8], 8.0f);

  crank_vec_float_n_fini (rows + 0);
  crank_vec_float_n_fini (rows + 1);
  crank_vec_float_n_fini (rows + 2);
}

static void
test_n_init_row_arr (void)
{
  CrankVecFloatN rows[3];
  CrankMatFloatN a;

  crank_vec_float_n_init (rows + 0, 3, 0.0f, 1.0f, 2.0f);
  crank_vec_float_n_init (rows + 1, 3, 3.0f, 4.0f, 5.0f);
  crank_vec_float_n_init (rows + 2, 3, 6.0f, 7.0f, 8.0f);

  crank_mat_float_n_init_row_arr (&a, 3, rows);

  test_assert_float (a.data[0], 0.0f);
  test_assert_float (a.data[1], 1.0f);
  test_assert_float (a.data[2], 2.0f);
  test_assert_float (a.data[3], 3.0f);
  test_assert_float (a.data[4], 4.0f);
  test_assert_float (a.data[5], 5.0f);
  test_assert_float (a.data[6], 6.0f);
  test_assert_float (a.data[7], 7.0f);
  test_assert_float (a.data[8], 8.0f);

  crank_vec_float_n_fini (rows + 0);
  crank_vec_float_n_fini (rows + 1);
  crank_vec_float_n_fini (rows + 2);
}

static void
test_n_init_row_parr (void)
{
  CrankVecFloatN *rows[3];
  CrankMatFloatN a;

  rows[0] = g_new (CrankVecFloatN, 1);
  rows[1] = g_new (CrankVecFloatN, 1);
  rows[2] = g_new (CrankVecFloatN, 1);

  crank_vec_float_n_init (rows[0], 3, 0.0f, 1.0f, 2.0f);
  crank_vec_float_n_init (rows[1], 3, 3.0f, 4.0f, 5.0f);
  crank_vec_float_n_init (rows[2], 3, 6.0f, 7.0f, 8.0f);

  crank_mat_float_n_init_row_parr (&a, 3, rows);

  test_assert_float (a.data[0], 0.0f);
  test_assert_float (a.data[1], 1.0f);
  test_assert_float (a.data[2], 2.0f);
  test_assert_float (a.data[3], 3.0f);
  test_assert_float (a.data[4], 4.0f);
  test_assert_float (a.data[5], 5.0f);
  test_assert_float (a.data[6], 6.0f);
  test_assert_float (a.data[7], 7.0f);
  test_assert_float (a.data[8], 8.0f);

  crank_vec_float_n_fini (rows[0]);
  crank_vec_float_n_fini (rows[1]);
  crank_vec_float_n_fini (rows[2]);
}


static void
test_n_init_col (void)
{
  CrankVecFloatN cols[3];
  CrankMatFloatN a;

  crank_vec_float_n_init (cols + 0, 3, 0.0f, 1.0f, 2.0f);
  crank_vec_float_n_init (cols + 1, 3, 3.0f, 4.0f, 5.0f);
  crank_vec_float_n_init (cols + 2, 3, 6.0f, 7.0f, 8.0f);

  crank_mat_float_n_init_col (&a, 3, cols + 0, cols + 1, cols + 2);

  test_assert_float (a.data[0], 0.0f);
  test_assert_float (a.data[1], 3.0f);
  test_assert_float (a.data[2], 6.0f);
  test_assert_float (a.data[3], 1.0f);
  test_assert_float (a.data[4], 4.0f);
  test_assert_float (a.data[5], 7.0f);
  test_assert_float (a.data[6], 2.0f);
  test_assert_float (a.data[7], 5.0f);
  test_assert_float (a.data[8], 8.0f);

  crank_vec_float_n_fini (cols + 0);
  crank_vec_float_n_fini (cols + 1);
  crank_vec_float_n_fini (cols + 2);
}

static void
test_n_init_col_arr (void)
{
  CrankVecFloatN cols[3];
  CrankMatFloatN a;

  crank_vec_float_n_init (cols + 0, 3, 0.0f, 1.0f, 2.0f);
  crank_vec_float_n_init (cols + 1, 3, 3.0f, 4.0f, 5.0f);
  crank_vec_float_n_init (cols + 2, 3, 6.0f, 7.0f, 8.0f);

  crank_mat_float_n_init_col_arr (&a, 3, cols);

  test_assert_float (a.data[0], 0.0f);
  test_assert_float (a.data[1], 3.0f);
  test_assert_float (a.data[2], 6.0f);
  test_assert_float (a.data[3], 1.0f);
  test_assert_float (a.data[4], 4.0f);
  test_assert_float (a.data[5], 7.0f);
  test_assert_float (a.data[6], 2.0f);
  test_assert_float (a.data[7], 5.0f);
  test_assert_float (a.data[8], 8.0f);

  crank_vec_float_n_fini (cols + 0);
  crank_vec_float_n_fini (cols + 1);
  crank_vec_float_n_fini (cols + 2);
}

static void
test_n_init_col_parr (void)
{
  CrankVecFloatN *cols[3];
  CrankMatFloatN a;

  cols[0] = g_new (CrankVecFloatN, 1);
  cols[1] = g_new (CrankVecFloatN, 1);
  cols[2] = g_new (CrankVecFloatN, 1);

  crank_vec_float_n_init (cols[0], 3, 0.0f, 1.0f, 2.0f);
  crank_vec_float_n_init (cols[1], 3, 3.0f, 4.0f, 5.0f);
  crank_vec_float_n_init (cols[2], 3, 6.0f, 7.0f, 8.0f);

  crank_mat_float_n_init_col_parr (&a, 3, cols);

  test_assert_float (a.data[0], 0.0f);
  test_assert_float (a.data[1], 3.0f);
  test_assert_float (a.data[2], 6.0f);
  test_assert_float (a.data[3], 1.0f);
  test_assert_float (a.data[4], 4.0f);
  test_assert_float (a.data[5], 7.0f);
  test_assert_float (a.data[6], 2.0f);
  test_assert_float (a.data[7], 5.0f);
  test_assert_float (a.data[8], 8.0f);

  crank_vec_float_n_fini (cols[0]);
  crank_vec_float_n_fini (cols[1]);
  crank_vec_float_n_fini (cols[2]);
}




static void
test_n_upper_tri_inverse (void)
{
  CrankMatFloatN a;
  CrankMatFloatN b;
  CrankVecFloatN r;

  crank_mat_float_n_init (&a, 5, 5,
                          4.0f, 4.0f, 2.0f, 1.0f, 1.0f,
                          0.0f, 4.0f, 4.0f, 2.0f, 1.0f,
                          0.0f, 0.0f, 4.0f, 4.0f, 2.0f,
                          0.0f, 0.0f, 0.0f, 4.0f, 4.0f,
                          0.0f, 0.0f, 0.0f, 0.0f, 4.0f);

  crank_mat_float_n_upper_tri_inverse (&a, &b);

  crank_mat_float_n_get_row (&b, 0, &r);

  crank_assert_eq_vecfloat_n_imm (&r, 0.25f, -0.25f, 0.125f, -0.0625f, 0.0f);

  crank_vec_float_n_fini (&r);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&a);
}

static void
test_n_lower_tri_inverse (void)
{
  CrankMatFloatN a;
  CrankMatFloatN b;
  CrankVecFloatN r;

  crank_mat_float_n_init (&a, 5, 5,
                          4.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          4.0f, 4.0f, 0.0f, 0.0f, 0.0f,
                          2.0f, 4.0f, 4.0f, 0.0f, 0.0f,
                          1.0f, 2.0f, 4.0f, 4.0f, 0.0f,
                          1.0f, 1.0f, 2.0f, 4.0f, 4.0f);

  crank_mat_float_n_lower_tri_inverse (&a, &b);

  crank_mat_float_n_get_col (&b, 0, &r);

  crank_assert_eq_vecfloat_n_imm (&r, 0.25f, -0.25f, 0.125f, -0.0625f, 0.0f);

  crank_vec_float_n_fini (&r);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&a);
}

static void
test_n_diag_inverse (void)
{
  CrankMatFloatN a;
  CrankMatFloatN b;
  CrankVecFloatN r;

  crank_mat_float_n_init (&a, 5, 5,
                          4.0f, 4.0f, 2.0f, 1.0f, 1.0f,
                          0.0f, 4.0f, 4.0f, 2.0f, 1.0f,
                          0.0f, 0.0f, 4.0f, 4.0f, 2.0f,
                          0.0f, 0.0f, 0.0f, 4.0f, 4.0f,
                          0.0f, 0.0f, 0.0f, 0.0f, 4.0f);

  crank_mat_float_n_diag_inverse (&a, &b);

  crank_mat_float_n_get_diag (&b, &r);

  crank_assert_eq_vecfloat_n_imm (&r, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);

  crank_vec_float_n_fini (&r);
  crank_mat_float_n_fini (&b);
  crank_mat_float_n_fini (&a);
}
