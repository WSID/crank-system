#ifndef CRANKBASETEST_H
#define CRANKBASETEST_H

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

#ifndef _CRANKBASE_INSIDE
#error crankbasetest.h cannot be included directly.
#endif

#include <math.h>
#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"

G_BEGIN_DECLS

/**
 * SECTION: crankbasetest
 * @title: Testing with Base.
 * @short_description: Testing with base structures.
 * @usability: unstable
 * @include: crankbase.h
 *
 * Crank System provides testing functions for convenience.
 *
 * For now, this provides assertions to check structures has right values.
 */

//////// Adding meta-testcases /////////////////////////////////////////////////

void crank_test_add_func_expected_fail (const gchar *path,
                                        GTestFunc    func);

void crank_test_add_func_timeout     (const gchar  *path,
                                      GTestFunc     func,
                                      const guint64 time);



//////// Assertion helpers /////////////////////////////////////////////////////

void    crank_assert_message_eq (const gchar *domain,
                                 const gchar *file,
                                 const gint   line,
                                 const gchar *func,
                                 const gchar *name_a,
                                 const gchar *name_b,
                                 const gchar *str_a,
                                 const gchar *str_b);

gchar  *crank_assert_stringify_sarray (const void      *arr,
                                       const guint      arr_length,
                                       const gsize      element_size,
                                       CrankStrPtrFunc  element_stringify,
                                       gpointer         userdata);

gchar  *crank_assert_stringify_parray (const gpointer  *arr,
                                       const guint      arr_length,
                                       CrankStrPtrFunc  element_stringify,
                                       gpointer         userdata);


//////// Array equal assertions ////////////////////////////////////////////////

/**
 * crank_assert_eqarray_bool: (skip)
 * @a: (element-type gboolean) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type gboolean) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 *
 * Asserts two boolean arrays are equals.
 */
#define crank_assert_eqarray_bool(a,an,b,bn)    \
  _crank_assert_eqarray(gboolean, \
                        a, \
                        an, \
                        b, \
                        bn, \
                        crank_bool_equal, \
                        crank_bool_to_string, \
                        NULL)
/**
 * crank_assert_eqarray_bool_imm: (skip)
 * @a: (element-type gboolean) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @...: Variadic list of boolean to compare with @a.
 *
 * Asserts a given boolean array has same element with given list
 */
#define crank_assert_eqarray_bool_imm(a,an,...) \
  _crank_assert_eqarray_imm(gboolean, \
                            a, \
                            an, \
                            crank_bool_equal, \
                            crank_bool_to_string, \
                            NULL, \
                            __VA_ARGS__)

/**
 * crank_assert_eqarray_int: (skip)
 * @a: (element-type gint) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type gint) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 *
 * Asserts two gint arrays are equals.
 */
#define crank_assert_eqarray_int(a,an,b,bn) \
  _crank_assert_eqarray(gint,a,an,b,bn,g_int_equal,crank_int_to_string,NULL)
/**
 * crank_assert_eqarray_int_imm: (skip)
 * @a: (element-type gint) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @...: Variadic list of int to compare with @a.
 *
 * Asserts a given gint array has same element with given list
 */
#define crank_assert_eqarray_int_imm(a,an,...)  \
  _crank_assert_eqarray_imm(gint, \
                            a, \
                            an, \
                            g_int_equal, \
                            crank_int_to_string, \
                            NULL, \
                            __VA_ARGS__)

/**
 * crank_assert_eqarray_uint: (skip)
 * @a: (element-type guint) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type guint) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 *
 * Asserts two guint arrays are equals.
 */
#define crank_assert_eqarray_uint(a,an,b,bn)    \
  _crank_assert_eqarray(guint, \
                        a, \
                        an, \
                        b, \
                        bn, \
                        crank_uint_equal, \
                        crank_uint_to_string, \
                        NULL)
/**
 * crank_assert_eqarray_uint_imm: (skip)
 * @a: (element-type guint) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @...: Variadic list of uint to compare with @a.
 *
 * Asserts a given guint array has same element with given list
 */
#define crank_assert_eqarray_uint_imm(a,an,...) \
  _crank_assert_eqarray_imm(guint, \
                            a, \
                            an, \
                            crank_uint_equal, \
                            crank_uint_to_string, \
                            NULL, \
                            __VA_ARGS__)


/**
 * crank_assert_eqarray_float: (skip)
 * @a: (element-type gfloat) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type gfloat) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 *
 * Asserts two float arrays are equals.
 */
#define crank_assert_eqarray_float(a,an,b,bn)   crank_assert_eqarray_float_d(a, \
                                                                             an, \
                                                                             b, \
                                                                             bn, \
                                                                             0.0001f)
/**
 * crank_assert_eqarray_float_imm: (skip)
 * @a: (element-type gfloat) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @...: Variadic list of float to compare with @a.
 *
 * Asserts a given boolean array has same element with given list
 */
#define crank_assert_eqarray_float_imm(a,an, \
                                       ...)    crank_assert_eqarray_float_d_imm( \
    a, \
    an, \
    0.0001f, \
    __VA_ARGS__)

/**
 * crank_assert_eqarray_float_d: (skip)
 * @a: (element-type gfloat) (array length=an): A array
 * @an: (type gfloat): Length of elements.
 * @b: (element-type gfloat) (array length=bn): A array
 * @bn: (type gfloat): Length of elements.
 * @d: (type gfloat): Delta value.
 *
 * Asserts two float arrays are equals.
 */
#define crank_assert_eqarray_float_d(a,an,b,bn,d)   \
  G_STMT_START { \
    gfloat _crank_eqafd_delta = (d); \
    _crank_assert_eqarray(gfloat, \
                          a, \
                          an, \
                          b, \
                          bn, \
                          _crank_float_equal_delta, \
                          crank_float_to_string, \
                          NULL); \
  } G_STMT_END

/**
 * crank_assert_eqarray_float_d_imm: (skip)
 * @a: (element-type gfloat) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @d: (type gfloat): Delta value.
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given boolean array has same element with given list
 */
#define crank_assert_eqarray_float_d_imm(a,an,d,...)    \
  G_STMT_START { \
    gfloat _crank_eqafd_delta = (d); \
    _crank_assert_eqarray_imm (gfloat, \
                               a, \
                               an, \
                               _crank_float_equal_delta, \
                               crank_float_to_string, \
                               NULL, \
                               __VA_ARGS__); \
  } G_STMT_END


/**
 * crank_assert_eqarray_pointer: (skip)
 * @a: (element-type gpointer) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @b: (element-type gpointer) (array length=bn): A array
 * @bn: (type guint): Length of elements.
 *
 * Asserts two pointer arrays are equals.
 */
#define crank_assert_eqarray_pointer(a,an,b,bn) \
  _crank_assert_eqparray(a,an,b,bn,g_direct_equal,crank_pointer_to_string,NULL)

/**
 * crank_assert_eqarray_pointer_imm: (skip)
 * @a: (element-type gpointer) (array length=an): A array
 * @an: (type guint): Length of elements.
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given boolean array has same element with given list
 */
#define crank_assert_eqarray_pointer_imm(a,an,...) \
  _crank_assert_eqparray_imm(a, \
                             an, \
                             g_direct_equal, \
                             crank_pointer_to_string, \
                             NULL, \
                             __VA_ARGS__)


//////// GLib Collection equal assertions //////////////////////////////////////

/**
 * crank_assert_eq_glist_imm: (skip)
 * @a: (type GList): A #GList
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given GList has same elements with given variadic list.
 */
#define crank_assert_eq_glist_imm(a,...) \
  _crank_assert_eqp_collection_imm( \
    GList*, \
    (a),g_list_length(a),G_STRINGIFY(a),g_list_nth_data, \
    g_direct_equal, crank_pointer_to_string, NULL, __VA_ARGS__)

/**
 * crank_assert_eq_gptrarray_imm: (skip)
 * @a: (type GPtrArray): A #GPtrArray
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given GPtrArray has same elements with given variadic list.
 */
#define crank_assert_eq_gptrarray_imm(a,...) \
  _crank_assert_eqp_collection_imm( \
    gpointer*, \
    ((a)->pdata),((a)->len),G_STRINGIFY(a),_crank_array_index, \
    g_direct_equal, crank_pointer_to_string, NULL, __VA_ARGS__)



//////// Crank Collection equal assertions /////////////////////////////////////

/**
 * crank_assert_eq_permutation_imm: (skip)
 * @a: (type CrankPermutaion): A #CrankPermutaion
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given permutation has same elements with given variadic list.
 */
#define crank_assert_eq_permutation_imm(a,...) \
  crank_assert_eqarray_uint_imm((a)->data, (a)->n, __VA_ARGS__)


/**
 * crank_assert_eq_vecbool2_imm: (skip)
 * @a: (type CrankVecBool2): A #CrankVecBool2
 * @x: (type gboolean): First element to compare.
 * @y: (type gboolean): Second element to compare.
 *
 * Asserts a given boolean vector has same elements with given elements.
 */
#define crank_assert_eq_vecbool2_imm(a,x,y) \
  crank_assert_eqarray_bool_imm((gboolean*)(a), 2, x,y)
/**
 * crank_assert_eq_vecbool3_imm: (skip)
 * @a: (type CrankVecFloat3): A #CrankVecBool3
 * @x: (type gboolean): First element to compare.
 * @y: (type gboolean): Second element to compare.
 * @z: (type gboolean): Third element to compare.
 *
 * Asserts a given boolean vector has same elements with given elements.
 */
#define crank_assert_eq_vecbool3_imm(a,x,y,z) \
  crank_assert_eqarray_bool_imm((gboolean*)(a), 3, x,y,z)
/**
 * crank_assert_eq_vecbool4_imm: (skip)
 * @a: (type CrankVecBool4): A #CrankVecBool4
 * @x: (type gboolean): First element to compare.
 * @y: (type gboolean): Second element to compare.
 * @z: (type gboolean): Third element to compare.
 * @w: (type gboolean): Fourth elements to compare.
 *
 * Asserts a given boolean vector has same elements with given elements.
 */
#define crank_assert_eq_vecbool4_imm(a,x,y,z,w) \
  crank_assert_eqarray_bool_imm((gboolean*)(a), 4, x,y,z,w)
/**
 * crank_assert_eq_vecbool_n_imm: (skip)
 * @a: (type CrankVecBoolN): A #CrankVecBoolN
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given boolean vector has same elements with given variadic list.
 *
 * You don't have to pass length of list, as macro catches length of list.
 */
#define crank_assert_eq_vecbool_n_imm(a,...) \
  crank_assert_eqarray_bool_imm((a)->data, (a)->n, __VA_ARGS__)


/**
 * crank_assert_eq_vecint2_imm: (skip)
 * @a: (type CrankVecInt2): A #CrankVecInt2
 * @x: (type gint): First element to compare.
 * @y: (type gint): Second element to compare.
 *
 * Asserts a given int vector has same elements with given elements.
 */
#define crank_assert_eq_vecint2_imm(a,x,y) \
  crank_assert_eqarray_int_imm((gint*)(a), 2, x,y)
/**
 * crank_assert_eq_vecint3_imm: (skip)
 * @a: (type CrankVecFloat3): A #CrankVecInt3
 * @x: (type gint): First element to compare.
 * @y: (type gint): Second element to compare.
 * @z: (type gint): Third element to compare.
 *
 * Asserts a given int vector has same elements with given elements.
 */
#define crank_assert_eq_vecint3_imm(a,x,y,z) \
  crank_assert_eqarray_int_imm((gint*)(a), 3, x,y,z)
/**
 * crank_assert_eq_vecint4_imm: (skip)
 * @a: (type CrankVecInt4): A #CrankVecInt4
 * @x: (type gint): First element to compare.
 * @y: (type gint): Second element to compare.
 * @z: (type gint): Third element to compare.
 * @w: (type gint): Fourth element to compare.
 *
 * Asserts a given int vector has same elements with given elements.
 */
#define crank_assert_eq_vecint4_imm(a,x,y,z,w) \
  crank_assert_eqarray_int_imm((gint*)(a), 4, x,y,z,w)
/**
 * crank_assert_eq_vecint_n_imm: (skip)
 * @a: (type CrankVecIntN): A #CrankVecIntN
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given int vector has same elements with given variadic list.
 *
 * You don't have to pass length of list, as macro catches length of list.
 */
#define crank_assert_eq_vecint_n_imm(a,...) \
  crank_assert_eqarray_int_imm((a)->data, (a)->n, __VA_ARGS__)


/**
 * crank_assert_eq_vecfloat2_imm: (skip)
 * @a: (type CrankVecFloat2): A #CrankVecFloat2
 * @x: (type gfloat): First element to compare.
 * @y: (type gfloat): Second element to compare.
 *
 * Asserts a given float vector has same elements with given elements.
 */
#define crank_assert_eq_vecfloat2_imm(a,x,y) \
  crank_assert_eqarray_float_imm((gfloat*)(a), 2, x,y)
/**
 * crank_assert_eq_vecfloat3_imm: (skip)
 * @a: (type CrankVecFloat3): A #CrankVecFloat3
 * @x: (type gfloat): First element to compare.
 * @y: (type gfloat): Second element to compare.
 * @z: (type gfloat): Third element to compare.
 *
 * Asserts a given float vector has same elements with given elements.
 */
#define crank_assert_eq_vecfloat3_imm(a,x,y,z) \
  crank_assert_eqarray_float_imm((gfloat*)(a), 3, x,y,z)
/**
 * crank_assert_eq_vecfloat4_imm: (skip)
 * @a: (type CrankVecFloat4): A #CrankVecFloat4
 * @x: (type gfloat): First element to compare.
 * @y: (type gfloat): Second element to compare.
 * @z: (type gfloat): Third element to compare.
 * @w: (type gfloat): Fourth element to compare.
 *
 * Asserts a given float vector has same elements with given elements.
 */
#define crank_assert_eq_vecfloat4_imm(a,x,y,z,w) \
  crank_assert_eqarray_float_imm((gfloat*)(a), 4, x,y,z,w)
/**
 * crank_assert_eq_vecfloat_n_imm: (skip)
 * @a: (type CrankVecFloatN): A #CrankVecFloatN
 * @...: Variadic list to compare with @a.
 *
 * Asserts a given float vector has same elements with given variadic list.
 *
 * You don't have to pass length of list, as macro catches length of list.
 */
#define crank_assert_eq_vecfloat_n_imm(a,...) \
  crank_assert_eqarray_float_imm((a)->data, (a)->n, __VA_ARGS__)






/**
 * crank_assert_cmpfloat: (skip)
 * @a: (type gfloat): A #gfloat
 * @cmp: A comparsion operator.
 * @b: (type gfloat): A #gfloat
 *
 * Asserts comparsion of two #gfloat with tolerance of 0.0001f of error.
 */
#define crank_assert_cmpfloat(a,cmp,b)  crank_assert_cmpfloat_d (a,cmp,b, \
                                                                 0.0001f)

/**
 * crank_assert_cmpfloat_d: (skip)
 * @a: (type gfloat): A #gfloat
 * @cmp: A comparsion operator.
 * @b: (type gfloat): A #gfloat
 * @d: (type gfloat): Delta
 *
 * Asserts comparsion of two #gfloat with tolerance of given delta of error.
 */
#define crank_assert_cmpfloat_d(a,cmp,b,d)  \
  G_STMT_START { \
    gfloat _crank_macro_cf_a = (a); \
    gfloat _crank_macro_cf_b = (b); \
    gfloat _crank_macro_cf_diff = (_crank_macro_cf_b - _crank_macro_cf_a); \
    gfloat _crank_macro_cf_d = (d); \
    gint _crank_macro_cf_cres = \
      (_crank_macro_cf_diff < -_crank_macro_cf_d) - \
      (_crank_macro_cf_d < _crank_macro_cf_diff); \
    if (G_UNLIKELY(!(_crank_macro_cf_cres cmp 0))) { \
        gchar *_crank_macro_cf_message = g_strdup_printf ( \
          "%s %s %s" \
          "\n\tActual: %g %s %g (with diff = %g)", \
          G_STRINGIFY(a), \
          G_STRINGIFY(cmp), \
          G_STRINGIFY(b), \
          _crank_macro_cf_a, \
          G_STRINGIFY(cmp), \
          _crank_macro_cf_b, \
          _crank_macro_cf_diff); \
        g_assertion_message ( \
          G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
          _crank_macro_cf_message); \
        g_free (_crank_macro_cf_message); \
      } \
  } G_STMT_END

/**
 * crank_assert_lefloat:
 * @a: (type gfloat): A float value.
 * @b: (type gfloat): A float value.
 * @d: (type gfloat): A acceptable error size.
 *
 * Asserts a is less than b. (a < b)
 *
 * This is used for Vala, which does not support operation as argument.
 */
#define crank_assert_lefloat(a,b,d) crank_assert_cmpfloat_d(a, <, b, d)

/**
 * crank_assert_eqfloat:
 * @a: (type gfloat): A float value.
 * @b: (type gfloat): A float value.
 * @d: (type gfloat): A acceptable error size.
 *
 * Asserts a is equal to b. (a == b)
 *
 * This is used for Vala, which does not support operation as argument.
 */
#define crank_assert_eqfloat(a,b,d) crank_assert_cmpfloat_d(a, ==, b, d)

/**
 * crank_assert_gefloat:
 * @a: (type gfloat): A float value.
 * @b: (type gfloat): A float value.
 * @d: (type gfloat): A acceptable error size.
 *
 * Asserts a is greater than b. (a > b)
 *
 * This is used for Vala, which does not support operation as argument.
 */
#define crank_assert_gefloat(a,b,d) crank_assert_cmpfloat_d(a, >, b, d)

/**
 * crank_assert_eqcplxfloat: (skip)
 * @a: (type CrankCplxFloat): A complex
 * @b: (type CrankCplxFloat): A complex
 *
 * Asserts comparsion of two #CrankCplxFloat with tolerance of 0.0001f of
 * error.
 *
 * The difference is calculated from distance on complex plane.
 */
#define crank_assert_eqcplxfloat(a,b) crank_assert_eqcplxfloat_d(a,b,0.0001f)

/**
 * crank_assert_eqcplxfloat_cimm: (skip)
 * @a: (type CrankCplxFloat): A complex
 * @r: (type gfloat): A real part.
 * @i: (type gfloat): A imaginary part.
 *
 * Asserts a given #CrankCplxFloat has same data with tolerance of 0.0001f of
 * error.
 *
 * The difference is calculated from distance on complex plane.
 */
#define crank_assert_eqcplxfloat_cimm(a,r,i) crank_assert_eqcplxfloat_d_cimm(a, \
                                                                             r, \
                                                                             i, \
                                                                             0.0001f)

/**
 * crank_assert_eqcplxfloat_d: (skip)
 * @a: (type CrankCplxFloat): A complex
 * @b: (type CrankCplxFloat): A complex
 * @d: (type gfloat): Delta
 *
 * Asserts comparsion of two #CrankCplxFloat with tolerance of given delta of
 * error.
 *
 * The difference is calculated from distance on complex plane.
 */
#define crank_assert_eqcplxfloat_d(a,b,d) \
  G_STMT_START { \
    CrankCplxFloat *_crank_macro_ecfd_a = (a); \
    CrankCplxFloat *_crank_macro_ecfd_b = (b); \
    gfloat _crank_macro_ecfd_d = (d); \
            \
    if (!G_LIKELY(crank_cplx_float_equal_delta( \
                    _crank_macro_ecfd_a, \
                    _crank_macro_ecfd_b, \
                    _crank_macro_ecfd_d))) { \
        CrankCplxFloat _crank_macro_ecfd_diff; \
                \
        crank_cplx_float_sub ( \
          _crank_macro_ecfd_b, \
          _crank_macro_ecfd_a, \
          &_crank_macro_ecfd_diff); \
                \
        gchar *_crank_macro_ecfd_astr = \
          crank_cplx_float_to_string (_crank_macro_ecfd_a); \
                \
        gchar *_crank_macro_ecfd_bstr = \
          crank_cplx_float_to_string (_crank_macro_ecfd_b); \
                \
        gchar *_crank_macro_ecfd_diffstr = \
          crank_cplx_float_to_string (&_crank_macro_ecfd_diff); \
                \
        gchar *_crank_macro_ecfd_message = g_strdup_printf ( \
          "%s == %s" \
          "\n\tActual: %s == %s (with diff = %s, norm = %g)", \
          G_STRINGIFY(a), \
          G_STRINGIFY(b), \
          _crank_macro_ecfd_astr, \
          _crank_macro_ecfd_bstr, \
          _crank_macro_ecfd_diffstr, \
          crank_cplx_float_get_norm (&_crank_macro_ecfd_diff) ); \
        g_assertion_message ( \
          G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
          _crank_macro_ecfd_message); \
        g_free (_crank_macro_ecfd_message); \
        g_free (_crank_macro_ecfd_astr); \
        g_free (_crank_macro_ecfd_bstr); \
        g_free (_crank_macro_ecfd_diffstr); \
      } \
  } G_STMT_END

/**
 * crank_assert_eqcplxfloat_d_cimm: (skip)
 * @a: (type CrankCplxFloat): A complex
 * @r: (type gfloat): A real part.
 * @i: (type gfloat): A imaginary part.
 * @d: (type gfloat): Delta
 *
 * Asserts a given #CrankCplxFloat has same data with tolerance of given delta of
 * error.
 *
 * The difference is calculated from distance on complex plane.
 */
#define crank_assert_eqcplxfloat_d_cimm(a,r,i,d) \
  G_STMT_START { \
    CrankCplxFloat _crank_aecfd_b = {r,i}; \
    crank_assert_eqcplxfloat_d (a, &_crank_aecfd_b, d); \
  } G_STMT_END



//////// Private Macros ////////////////////////////////////////////////////////
#define _crank_float_equal_delta(a,b) \
  (isnanf(*(float*)a) ? isnanf(*(float*)b) : (((*(float*)b) - \
                                               _crank_eqafd_delta < \
                                               (*(float*)a)) && \
                                              ((*(float*)a) < (*(float*)b) + \
                                               _crank_eqafd_delta)))

#define _crank_array_index(a,i) ((a)[i])

#define _crank_array_add(a,i) ((a) + i)

#define _crank_append_collection_content(s,a,n,aname,getter,strf,strfu) \
  G_STMT_START { \
    gchar *item_str; \
    guint i; \
            \
    g_string_append_printf (s, \
                            "\n\tContent of %s (length: %u)", \
                            aname, n); \
            \
    for (i = 0; i < n; i++) { \
        item_str = strf (getter (a, i), strfu); \
        g_string_append_printf (s, "\n\t\t%s", item_str); \
        g_free (item_str); \
      } \
  } G_STMT_END

#define _crank_assert_eq_collection(G, \
                                    AT, \
                                    BT, \
                                    a, \
                                    an, \
                                    aname, \
                                    agetter, \
                                    b, \
                                    bn, \
                                    bname, \
                                    bgetter, \
                                    eqf, \
                                    strf, \
                                    strfu)   \
  G_STMT_START { \
    gboolean _crank_fails = FALSE; \
    AT _crank_na =     (a); \
    guint _crank_nan =    (an); \
    BT _crank_nb =     (b); \
    guint _crank_nbn =    (bn); \
    gpointer _crank_nstrfu = (strfu); \
    guint _crank_i; \
    if (_crank_nan != _crank_nbn) _crank_fails = TRUE; \
    else for (_crank_i = 0; _crank_i < _crank_nan; _crank_i++) { \
          if (!eqf (agetter(_crank_na,_crank_i), bgetter(_crank_nb,_crank_i))) { \
              _crank_fails = TRUE; \
              break; \
            } \
        } \
    if (_crank_fails) { \
        GString *_crank_msg_build = g_string_new (NULL); \
        g_string_printf (_crank_msg_build, "%s == %s", \
                         aname, bname); \
                \
        _crank_append_collection_content(_crank_msg_build, \
                                         _crank_na, \
                                         _crank_nan, \
                                         aname, \
                                         agetter, \
                                         strf, \
                                         _crank_nstrfu); \
        _crank_append_collection_content(_crank_msg_build, \
                                         _crank_nb, \
                                         _crank_nbn, \
                                         bname, \
                                         bgetter, \
                                         strf, \
                                         _crank_nstrfu); \
        g_assertion_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, \
                             _crank_msg_build->str); \
        g_string_free (_crank_msg_build, TRUE); \
                \
      } \
  } G_STMT_END

#define _crank_assert_eq_collection_imm(G, \
                                        AT, \
                                        a, \
                                        an, \
                                        aname, \
                                        agetter, \
                                        eqf, \
                                        strf, \
                                        strfu, \
                                        ...) \
  G_STMT_START { \
    G _crank_b[] = { __VA_ARGS__ }; \
    guint _crank_bn = G_N_ELEMENTS (_crank_b); \
            \
    _crank_assert_eq_collection ( \
      G,AT,G*, \
      a,an,aname,agetter, \
      _crank_b,_crank_bn,"list",_crank_array_add, \
      eqf, strf, strfu); \
            \
  } G_STMT_END

#define _crank_assert_eqp_collection_imm(AT, \
                                         a, \
                                         an, \
                                         aname, \
                                         agetter, \
                                         eqf, \
                                         strf, \
                                         strfu, \
                                         ...) \
  G_STMT_START { \
    gpointer _crank_b[] = { __VA_ARGS__ }; \
    guint _crank_bn = G_N_ELEMENTS (_crank_b); \
            \
    _crank_assert_eq_collection ( \
      gpointer, AT, gpointer*, \
      a,an,aname,agetter, \
      _crank_b,_crank_bn,"list",_crank_array_index, \
      eqf, strf, strfu); \
            \
  } G_STMT_END





#define _crank_assert_eqarray(G,a,an,b,bn,eqf,strf,strfu) \
  _crank_assert_eq_collection( \
    G,G*,G*, \
    a,an,G_STRINGIFY(a),_crank_array_add, \
    b,bn,G_STRINGIFY(b),_crank_array_add, \
    eqf, strf, strfu)

#define _crank_assert_eqarray_imm(G,a,an,eqf,strf,strfu,...) \
  _crank_assert_eq_collection_imm( \
    G,G*, \
    a,an,G_STRINGIFY(a),_crank_array_add, \
    eqf, strf, strfu, \
    __VA_ARGS__)



#define _crank_assert_eqparray(a,an,b,bn,eqf,strf,strfu) \
  _crank_assert_eq_collection( \
    gpointer, gpointer*, gpointer*, \
    a,an,G_STRINGIFY(a),_crank_array_index, \
    b,bn,G_STRINGIFY(b),_crank_array_index, \
    eqf, strf, strfu)

#define _crank_assert_eqparray_imm(a,an,eqf,strf,strfu,...) \
  _crank_assert_eqp_collection_imm( \
    gpointer*, \
    a,an,G_STRINGIFY(a),_crank_array_index, \
    eqf, strf, strfu, __VA_ARGS__)


G_END_DECLS

#endif