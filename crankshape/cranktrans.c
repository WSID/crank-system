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

#define _CRANKSHAPE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "cranktrans.h"

/**
 * SECTION: cranktrans
 * @title: Transformation
 * @short_description: Transformations packed into translate, rotate, scale.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * Defines translations packed into translate, rotate and scale variables.
 *
 * Currently, different scaling factor by axes is not supported, as it introduces
 * shear in play.
 */

//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankTrans2, crank_trans2, crank_trans2_dup, g_free);


//////// Initialization functions. /////////////////////////////////////////////////

/**
 * crank_trans2_init:
 * @trans: (out): A Transformation.
 *
 * Initialize a identity transformation.
 */
void
crank_trans2_init (CrankTrans2 *trans)
{
  crank_vec_float2_init_fill (& trans->translate, 0.0f);

  trans->rotate = 0.0f;
  trans->scale = 1.0f;
}

/**
 * crank_trans2_init_from_matrix:
 * @trans: (out): A Transformation.
 * @mat: A Matrix.
 *
 * Initialize a transformation from matrix.
 */
void
crank_trans2_init_from_matrix (CrankTrans2    *trans,
                               CrankMatFloat3 *mat)
{
  trans->translate.x = mat->m02;
  trans->translate.y = mat->m12;
  trans->rotate = atan2 (mat->m10, mat->m00);
  trans->scale = sqrtf ((mat->m00 * mat->m00) + (mat->m10 * mat->m10));

  if ((trans->scale * mat->m00) < 0.0f)
    trans->scale = -trans->scale;
}


/**
 * crank_trans2_to_matrix:
 * @trans: A Transformation.
 * @mat: (out): A Matrix.
 *
 * Converts transformation into matrix form.
 */
void
crank_trans2_to_matrix (CrankTrans2    *trans,
                        CrankMatFloat3 *mat)
{
  gfloat ss;
  gfloat sc;

  ss = trans->scale * sinf (trans->rotate);
  sc = trans->scale * cosf (trans->rotate);

  crank_mat_float3_init (mat,   sc, -ss, trans->translate.x,
                                ss, sc,  trans->translate.y,
                                0.0f, 0.0f, 1.0f);
}


/**
 * crank_trans2_copy:
 * @trans: A Transformation.
 * @other: (out): A Transformation.
 *
 * Copies a transformation to other.
 */
void
crank_trans2_copy (CrankTrans2 *trans,
                   CrankTrans2 *other)
{
  crank_vec_float2_copy (& trans->translate, & other->translate);
  trans->rotate = other->rotate;
  trans->scale  = other->scale;
}

/**
 * crank_trans2_dup:
 * @trans: A Transformation.
 *
 * Duplicates a transformation to other.
 *
 * Returns: (transfer full): A Transformation.
 */
CrankTrans2*
crank_trans2_dup (CrankTrans2 *trans)
{
  CrankTrans2 *other = g_new (CrankTrans2, 1);

  crank_trans2_copy (trans, other);
  return other;
}


//////// Operations ////////////////////////////////////////////////////////////

/**
 * crank_trans2_translate:
 * @a: A Transformation.
 * @b: Translation amount.
 * @r: (out): A result.
 *
 * Apply translation to a transformation.
 */
void
crank_trans2_translate (CrankTrans2    *a,
                        CrankVecFloat2 *b,
                        CrankTrans2    *r)
{
  crank_vec_float2_add (& a->translate, b, & r->translate);
  r->rotate = a->rotate;
  r->scale = a->scale;
}

/**
 * crank_trans2_translate_self:
 * @a: A transformation.
 * @b: Translation amount.
 *
 * Apply translation to a transformation.
 */
void
crank_trans2_translate_self (CrankTrans2    *a,
                             CrankVecFloat2 *b)
{
  crank_vec_float2_add_self (& a->translate, b);
}


/**
 * crank_trans2_rotate:
 * @a: A Transformation.
 * @b: Rotation amount.
 * @r: (out): A result.
 *
 * Apply rotation to a transformation.
 */
void
crank_trans2_rotate (CrankTrans2  *a,
                     const gfloat  b,
                     CrankTrans2  *r)
{
  gfloat s;
  gfloat c;

  gfloat mx;
  gfloat my;

  s = sinf (b);
  c = cosf (b);

  mx = a->translate.x;
  my = a->translate.y;

  r->translate.x = mx * c - my * s;
  r->translate.y = mx * s + my * c;

  r->rotate = a->rotate + b;

  r->scale = a->scale;
}

/**
 * crank_trans2_rotate_self:
 * @a: A Transformation.
 * @b: Rotation amount.
 *
 * Apply rotation to a transformation.
 */
void
crank_trans2_rotate_self (CrankTrans2  *a,
                          const gfloat  b)
{
  gfloat s;
  gfloat c;

  gfloat mx;
  gfloat my;

  s = sinf (b);
  c = cosf (b);

  mx = a->translate.x;
  my = a->translate.y;

  a->translate.x = mx * c - my * s;
  a->translate.y = mx * s + my * c;

  a->rotate += b;
}

/**
 * crank_trans2_scale:
 * @a: A Transformation.
 * @b: Scale amount.
 * @r: (out): A result.
 *
 * Apply scaling to a transformation.
 */
void
crank_trans2_scale (CrankTrans2  *a,
                    const gfloat  b,
                    CrankTrans2  *r)
{
  crank_vec_float2_muls (& a->translate, b, & r->translate);
  r->rotate = a->rotate;
  r->scale = a->scale * b;
}

/**
 * crank_trans2_scale_self:
 * @a: A Transformation.
 * @b: Scale amount.
 *
 * Apply scaling to a transformation.
 */
void
crank_trans2_scale_self (CrankTrans2  *a,
                         const gfloat  b)
{
  crank_vec_float2_muls_self (& a->translate, b);
  a->scale *= b;
}

/**
 * crank_trans2_inverse:
 * @a: A Transformation.
 * @r: (out): A result.
 *
 * Inverses a transformation.
 */
void
crank_trans2_inverse (CrankTrans2 *a,
                      CrankTrans2 *r)
{
  gfloat s;
  gfloat c;

  gfloat mx;
  gfloat my;

  s = sinf (a->rotate);
  c = cosf (a->rotate);

  mx = a->translate.x / a->scale;
  my = a->translate.y / a->scale;

  r->translate.x = -mx * c - my * s;
  r->translate.y =  mx * s - my * c;

  r->rotate = - a->rotate;
  r->scale = 1 / a->scale;
}

/**
 * crank_trans2_inverse_self:
 * @a: A Transformation.
 *
 * Inverses a transformation.
 */
void
crank_trans2_inverse_self (CrankTrans2 *a)
{
  gfloat s;
  gfloat c;

  gfloat mx;
  gfloat my;

  s = sinf (a->rotate);
  c = cosf (a->rotate);

  mx = a->translate.x / a->scale;
  my = a->translate.y / a->scale;

  a->translate.x = -mx * c - my * s;
  a->translate.y =  mx * s - my * c;

  a->rotate = - a->rotate;
  a->scale = 1 / a->scale;
}


/**
 * crank_trans2_compose:
 * @a: A Transformation.
 * @b: Another transformation.
 * @r: (out): A result.
 *
 * Applies @a to @b.
 */
void
crank_trans2_compose (CrankTrans2 *a,
                      CrankTrans2 *b,
                      CrankTrans2 *r)
{
  gfloat s;
  gfloat c;

  gfloat mx;
  gfloat my;

  s = sinf (a->rotate);
  c = cosf (a->rotate);

  mx = b->translate.x * a->scale;
  my = b->translate.y * a->scale;

  r->translate.x = a->translate.x + (mx * c - my * s);
  r->translate.y = a->translate.y + (mx * s + my * c);

  r->rotate = a->rotate + b->rotate;
  r->scale = a->scale * b->scale;
}

/**
 * crank_trans2_compose_self:
 * @a: A Transformation.
 * @b: Another transformation.
 *
 * Applies @a to @b.
 */
void
crank_trans2_compose_self (CrankTrans2 *a,
                           CrankTrans2 *b)
{
  gfloat s;
  gfloat c;

  gfloat mx;
  gfloat my;

  s = sinf (a->rotate);
  c = cosf (a->rotate);

  mx = b->translate.x * a->scale;
  my = b->translate.y * a->scale;

  a->translate.x += (mx * c - my * s);
  a->translate.y += (mx * s + my * c);

  a->rotate += b->rotate;
  a->scale *= b->scale;
}

//////// Transformation ////////////////////////////////////////////////////////

/**
 * crank_trans2_transv:
 * @a: A transformation.
 * @b: A vector.
 * @r: (out): A result.
 *
 * Transform a vector.
 */
void
crank_trans2_transv (CrankTrans2    *a,
                     CrankVecFloat2 *b,
                     CrankVecFloat2 *r)
{
  gfloat s;
  gfloat c;

  s = sinf (a->rotate);
  c = cosf (a->rotate);

  r->x = a->translate.x * c - a->translate.y * s;
  r->y = a->translate.x * s + a->translate.y * c;

  crank_vec_float2_muls_self (r, a->scale);
  crank_vec_float2_add_self (r, & a->translate);
}
