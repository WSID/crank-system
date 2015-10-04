#ifndef CRANKCOMPLEX_H
#define CRANKCOMPLEX_H

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
#error crankcomplex.h cannot be included directly.
#endif

#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>

//////// External typedefs /////////////////////////////////////////////////////

typedef struct _CrankQuatFloat CrankQuatFloat;


//////// Struct declaration ////////////////////////////////////////////////////

/**
 * CRANK_CPLX_FLOAT_DEFFORMAT:
 *
 * Default format for crank_cplx_float_to_string_full().
 */
#define CRANK_CPLX_FLOAT_DEFFORMAT "%g + (%gi)"

/**
 * CrankCplxFloat:
 * @real: Real part of complex.
 * @imag: Imaginary part of complex.
 *
 * Represents a float complex value
 */
typedef struct _CrankCplxFloat {
  gfloat real;
  gfloat imag;
} CrankCplxFloat;

GType           crank_cplx_float_get_type (void);

#define CRANK_TYPE_CPLX_FLOAT (crank_cplx_float_get_type())


//////// Initialization ////////////////////////////////////////////////////////

void            crank_cplx_float_init (CrankCplxFloat *cplx,
                                       gfloat          real,
                                       gfloat          imag);

void            crank_cplx_float_init_arr (CrankCplxFloat *cplx,
                                           gfloat         *parts);

void            crank_cplx_float_init_valist (CrankCplxFloat *cplx,
                                              va_list         varargs);

void            crank_cplx_float_init_fill (CrankCplxFloat *cplx,
                                            gfloat          fill);

void            crank_cplx_float_init_polar (CrankCplxFloat *cplx,
                                             const gfloat    norm,
                                             const gfloat    arg);

//////// Basic Operations //////////////////////////////////////////////////////

void            crank_cplx_float_copy (CrankCplxFloat *cplx,
                                       CrankCplxFloat *other);

CrankCplxFloat *crank_cplx_float_dup (CrankCplxFloat *cplx);

gboolean        crank_cplx_float_equal (gconstpointer a,
                                        gconstpointer b);

gboolean        crank_cplx_float_equal_delta (CrankCplxFloat *a,
                                              CrankCplxFloat *b,
                                              const gfloat    d);

guint           crank_cplx_float_hash (gconstpointer a);

guint           crank_cplx_float_hash1 (gconstpointer a);

gchar          *crank_cplx_float_to_string (CrankCplxFloat *cplx);

gchar          *crank_cplx_float_to_string_full (CrankCplxFloat *cplx,
                                                 const gchar    *format);

//////// Attributes ////////////////////////////////////////////////////////////

gboolean        crank_cplx_float_is_zero (CrankCplxFloat *cplx);

gboolean        crank_cplx_float_is_one (CrankCplxFloat *cplx);

gboolean        crank_cplx_float_is_unit (CrankCplxFloat *cplx);

gboolean        crank_cplx_float_is_pure_real (CrankCplxFloat *cplx);

gboolean        crank_cplx_float_is_pure_imag (CrankCplxFloat *cplx);

gboolean        crank_cplx_float_has_nan (CrankCplxFloat *cplx);

gboolean        crank_cplx_float_has_inf (CrankCplxFloat *cplx);

gfloat          crank_cplx_float_get_norm_sq (CrankCplxFloat *cplx);

gfloat          crank_cplx_float_get_norm (CrankCplxFloat *cplx);

gfloat          crank_cplx_float_get_arg (CrankCplxFloat *cplx);

//////// Unary Operations //////////////////////////////////////////////////////

void            crank_cplx_float_neg (CrankCplxFloat *a,
                                      CrankCplxFloat *r);

void            crank_cplx_float_inverse (CrankCplxFloat *a,
                                          CrankCplxFloat *r);

void            crank_cplx_float_conjugate (CrankCplxFloat *a,
                                            CrankCplxFloat *r);

void            crank_cplx_float_unit (CrankCplxFloat *a,
                                       CrankCplxFloat *r);

void            crank_cplx_float_sqrt (CrankCplxFloat *a,
                                       CrankCplxFloat *r);


void            crank_cplx_float_neg_self (CrankCplxFloat *a);

void            crank_cplx_float_inverse_self (CrankCplxFloat *a);

void            crank_cplx_float_conjugate_self (CrankCplxFloat *a);

void            crank_cplx_float_unit_self (CrankCplxFloat *a);

void            crank_cplx_float_sqrt_self (CrankCplxFloat *a);

//////// Airthmetics  //////////////////////////////////////////////////////////

void            crank_cplx_float_addr (CrankCplxFloat *a,
                                       gfloat          b,
                                       CrankCplxFloat *r);

void            crank_cplx_float_add (CrankCplxFloat *a,
                                      CrankCplxFloat *b,
                                      CrankCplxFloat *r);

void            crank_cplx_float_addr_self (CrankCplxFloat *a,
                                            gfloat          b);

void            crank_cplx_float_add_self (CrankCplxFloat *a,
                                           CrankCplxFloat *b);

void            crank_cplx_float_subr (CrankCplxFloat *a,
                                       gfloat          b,
                                       CrankCplxFloat *r);

void            crank_cplx_float_sub (CrankCplxFloat *a,
                                      CrankCplxFloat *b,
                                      CrankCplxFloat *r);

void            crank_cplx_float_subq (CrankCplxFloat *a,
                                       CrankQuatFloat *b,
                                       CrankQuatFloat *r);

void            crank_cplx_float_subr_self (CrankCplxFloat *a,
                                            gfloat          b);

void            crank_cplx_float_sub_self (CrankCplxFloat *a,
                                           CrankCplxFloat *b);

void            crank_cplx_float_mulr (CrankCplxFloat *a,
                                       gfloat          b,
                                       CrankCplxFloat *r);

void            crank_cplx_float_mul (CrankCplxFloat *a,
                                      CrankCplxFloat *b,
                                      CrankCplxFloat *r);

void            crank_cplx_float_mulq (CrankCplxFloat *a,
                                       CrankQuatFloat *b,
                                       CrankQuatFloat *r);

void            crank_cplx_float_mulr_self (CrankCplxFloat *a,
                                            gfloat          b);

void            crank_cplx_float_mul_self (CrankCplxFloat *a,
                                           CrankCplxFloat *b);

void            crank_cplx_float_divr (CrankCplxFloat *a,
                                       gfloat          b,
                                       CrankCplxFloat *r);

void            crank_cplx_float_div (CrankCplxFloat *a,
                                      CrankCplxFloat *b,
                                      CrankCplxFloat *r);

void            crank_cplx_float_divr_self (CrankCplxFloat *a,
                                            gfloat          b);

void            crank_cplx_float_div_self (CrankCplxFloat *a,
                                           CrankCplxFloat *b);

//////// Swapped Operations ////////////////////////////////////////////////////

void            crank_cplx_float_rsubr (CrankCplxFloat *a,
                                        gfloat          b,
                                        CrankCplxFloat *r);

void            crank_cplx_float_rdivr (CrankCplxFloat *a,
                                        gfloat          b,
                                        CrankCplxFloat *r);

//////// Misc Operations ///////////////////////////////////////////////////////


void            crank_cplx_float_mul_conj (CrankCplxFloat *a,
                                           CrankCplxFloat *b,
                                           CrankCplxFloat *r);

//////// Ternary Operations ////////////////////////////////////////////////////

void            crank_cplx_float_mix (CrankCplxFloat *a,
                                      CrankCplxFloat *b,
                                      gfloat          c,
                                      CrankCplxFloat *r);


//////// Exponential Operations ////////////////////////////////////////////////

void            crank_cplx_float_ln (CrankCplxFloat *a,
                                     CrankCplxFloat *r);

void            crank_cplx_float_exp (CrankCplxFloat *a,
                                      CrankCplxFloat *r);

void            crank_cplx_float_pow (CrankCplxFloat *a,
                                      CrankCplxFloat *b,
                                      CrankCplxFloat *r);

//////// Hyperbolic Operations /////////////////////////////////////////////////

void            crank_cplx_float_sinh (CrankCplxFloat *a,
                                       CrankCplxFloat *r);

void            crank_cplx_float_cosh (CrankCplxFloat *a,
                                       CrankCplxFloat *r);

void            crank_cplx_float_tanh (CrankCplxFloat *a,
                                       CrankCplxFloat *r);

//////// Trigonometric Operations //////////////////////////////////////////////

void            crank_cplx_float_sin (CrankCplxFloat *a,
                                      CrankCplxFloat *r);

void            crank_cplx_float_cos (CrankCplxFloat *a,
                                      CrankCplxFloat *r);

void            crank_cplx_float_tan (CrankCplxFloat *a,
                                      CrankCplxFloat *r);



//////// Generic Selectors /////////////////////////////////////////////////////

#if !defined (CRANK_NO_C11_GENERIC_SELECTOR) && (__STDC_VERSION__ >= 201112L)
#define crank_cplx_float_add(a, b, r) \
  _Generic((b),   gfloat:             crank_cplx_float_addr,  \
           CrankCplxFloat * :    crank_cplx_float_add)   \
  (a, b, r)

#define crank_cplx_float_add_self(a, b) \
  _Generic((b),   gfloat:             crank_cplx_float_addr_self, \
           CrankCplxFloat * :    crank_cplx_float_add_self)  \
  (a, b)

#define crank_cplx_float_sub(a, b, r) \
  _Generic((b),   gfloat:             crank_cplx_float_subr,  \
           CrankCplxFloat * :    crank_cplx_float_sub,   \
           CrankQuatFloat * :    crank_cplx_float_subq)  \
  (a, b, r)

#define crank_cplx_float_sub_self(a, b) \
  _Generic((b),   gfloat:             crank_cplx_float_subr_self, \
           CrankCplxFloat * :    crank_cplx_float_sub_self)  \
  (a, b)

#define crank_cplx_float_mul(a, b, r) \
  _Generic((b),   gfloat:             crank_cplx_float_mulr,  \
           CrankCplxFloat * :    crank_cplx_float_mul,   \
           CrankQuatFloat * :    crank_cplx_float_mulq)  \
  (a, b, r)

#define crank_cplx_float_mul_self(a, b) \
  _Generic((b),   gfloat:             crank_cplx_float_mulr_self, \
           CrankCplxFloat * :    crank_cplx_float_mul_self)  \
  (a, b)



#define crank_cplx_float_div(a, b, r) \
  _Generic((b),   gfloat:         crank_cplx_float_divr,  \
           CrankCplxFloat * :    crank_cplx_float_div)   \
  (a, b, r)

#define crank_cplx_float_div_self(a, b) \
  _Generic((b),   gfloat:             crank_cplx_float_divr_self, \
           CrankCplxFloat * :    crank_cplx_float_div_self)  \
  (a, b)

#endif

#ifndef CRANK_NO_SIMPLE_FUNCTION_MACRO
#define crank_cplx_float_init(c,r,i)    \
  G_STMT_START {                      \
    (c)->real = (r);                \
    (c)->imag = (i);                \
  } G_STMT_END

#define crank_cplx_float_init_arr(c,p)  \
  G_STMT_START {                      \
    (c)->real = (p)[0];             \
    (c)->imag = (p)[1];             \
  } G_STMT_END

#define crank_cplx_float_init_valist(c,v)               \
  G_STMT_START {                                      \
    (c)->real = (gfloat) (va_arg((v), gdouble));    \
    (c)->imag = (gfloat) (va_arg((v), gdouble));    \
  } G_STMT_END

#define crank_cplx_float_init_fill(c,f) \
  G_STMT_START {                      \
    (c)->real = (f);                \
    (c)->imag = (f);                \
  } G_STMT_END


#define crank_cplx_float_copy(c,o)  \
  G_STMT_START {                  \
    (o)->real = (c)->real;      \
    (o)->imag = (c)->imag;      \
  } G_STMT_END



#define crank_cplx_float_to_string(c)   \
  (crank_cplx_float_to_string_full(c, CRANK_CPLX_FLOAT_DEFFORMAT))

#define crank_cplx_float_to_string_full(c,f)    \
  (g_strdup_printf((f), (c)->real, (c)->imag))



#define crank_cplx_float_is_zero(c) \
  (((c)->real == 0) && ((c)->imag == 0))

#define crank_cplx_float_is_one(c)  \
  (((c)->real == 1) && ((c)->imag == 1))

#define crank_cplx_float_is_pure_real(c)    \
  ((c)->imag == 0)

#define crank_cplx_float_is_pure_imag(c)    \
  ((c)->real == 0)

#define crank_cplx_float_has_nan(c) \
  (isnanf((c)->real) || isnanf((c)->imag))

#define crank_cplx_float_has_inf(c) \
  (isinff((c)->real) || isinff((c)->imag))



#endif

#endif