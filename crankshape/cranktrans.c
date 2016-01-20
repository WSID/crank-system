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
#include "crankrotation.h"

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
G_DEFINE_BOXED_TYPE (CrankTrans3, crank_trans3, crank_trans3_dup, g_free);


//////// Initialization functions. /////////////////////////////////////////////

/**
 * crank_trans2_init:
 * @trans: (out): A Transformation.
 *
 * Initialize a identity transformation.
 */
void
crank_trans2_init (CrankTrans2 *trans)
{
  crank_vec_float2_init_fill (& trans->mtrans, 0.0f);

  trans->mrot = 0.0f;
  trans->mscl = 1.0f;
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
  trans->mtrans.x = mat->m02;
  trans->mtrans.y = mat->m12;
  trans->mrot = atan2 (mat->m10, mat->m00);
  trans->mscl = sqrtf ((mat->m00 * mat->m00) + (mat->m10 * mat->m10));

  if ((trans->mscl * mat->m00) < 0.0f)
    trans->mscl = -trans->mscl;
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

  ss = trans->mscl * sinf (trans->mrot);
  sc = trans->mscl * cosf (trans->mrot);

  crank_mat_float3_init (mat,   sc, -ss, trans->mtrans.x,
                                ss, sc,  trans->mtrans.y,
                                0.0f, 0.0f, 1.0f);
}

/**
 * crank_trans2_to_matrix_transpose:
 * @trans: A Transformation.
 * @mat: (out): A Matrix.
 *
 * Converts transformation into matrix form.
 *
 * This is useful when column-major matrices are required.
 */
void
crank_trans2_to_matrix_transpose (CrankTrans2    *trans,
                                  CrankMatFloat3 *mat)
{
  gfloat ss;
  gfloat sc;

  ss = trans->mscl * sinf (trans->mrot);
  sc = trans->mscl * cosf (trans->mrot);

  crank_mat_float3_init (mat,    sc,             ss,              0.0f,
                                -ss,             sc,              0.0f,
                                trans->mtrans.x, trans->mtrans.y, 1.0f);
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
  crank_vec_float2_copy (& trans->mtrans, & other->mtrans);
  other->mrot = trans->mrot;
  other->mscl  = trans->mscl;
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
  crank_vec_float2_add (& a->mtrans, b, & r->mtrans);
  r->mrot = a->mrot;
  r->mscl = a->mscl;
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
  crank_vec_float2_add_self (& a->mtrans, b);
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
  crank_rot_vec2_rot (& a->mtrans, b, & r->mtrans);

  r->mrot = a->mrot + b;

  r->mscl = a->mscl;
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
  crank_rot_vec2_rot_inplace (& a->mtrans, b);
  a->mrot += b;
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
  crank_vec_float2_muls (& a->mtrans, b, & r->mtrans);
  r->mrot = a->mrot;
  r->mscl = a->mscl * b;
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
  crank_vec_float2_muls_self (& a->mtrans, b);
  a->mscl *= b;
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
  crank_rot_vec2_rot (& a->mtrans, - a->mrot, & r->mtrans);
  crank_vec_float2_divs_self (& r->mtrans, a->mscl);
  crank_vec_float2_neg_self (& r->mtrans);

  r->mrot = - a->mrot;
  r->mscl = 1 / a->mscl;
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
  crank_rot_vec2_rot_inplace (& a->mtrans, - a->mrot);
  crank_vec_float2_divs_self (& a->mtrans, a->mscl);

  a->mrot = - a->mrot;
  a->mscl = 1 / a->mscl;
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
  crank_rot_vec2_rot (& b->mtrans, a->mrot, & r->mtrans);
  crank_vec_float2_muls_self (& r->mtrans, a->mscl);
  crank_vec_float2_add_self (& r->mtrans, & a->mtrans);

  r->mrot = a->mrot + b->mrot;
  r->mscl = a->mscl * b->mscl;
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
  CrankVecFloat2 mtrans;
  
  crank_rot_vec2_rot (& b->mtrans, a->mrot, & mtrans);
  crank_vec_float2_muls_self (& mtrans, a->mscl);

  crank_vec_float2_add_self (& a->mtrans, & mtrans);

  a->mrot += b->mrot;
  a->mscl *= b->mscl;
}

/**
 * crank_trans2_relative_to:
 * @a: A Transformation.
 * @b: Another transformation.
 * @r: (out): A resulting transformation.
 *
 * Gets relative transformation from @a to @b, which resulting to @b when applied
 * to @a.
 */
void
crank_trans2_relative_to (CrankTrans2 *a,
                          CrankTrans2 *b,
                          CrankTrans2 *r)
{
  crank_trans2_inverse (a, r);
  crank_trans2_compose_self (r, b);
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
  crank_rot_vec2_rot (b, a->mrot, r);
  
  crank_vec_float2_muls_self (r, a->mscl);
  crank_vec_float2_add_self (r, & a->mtrans);
}





//////// Initialization functions. /////////////////////////////////////////////

/**
 * crank_trans3_init:
 * @trans: (out): A Transformation.
 *
 * Initialize a identity transformation.
 */
void
crank_trans3_init (CrankTrans3 *trans)
{
  crank_vec_float3_init_fill (& trans->mtrans, 0.0f);
  crank_quat_float_init (& trans->mrot, 1.0f, 0.0f, 0.0f, 0.0f);

  trans->mscl = 1.0f;
}

/**
 * crank_trans3_init_from_matrix:
 * @trans: (out): A Transformation.
 * @mat: A Matrix.
 *
 * Initialize a transformation from matrix.
 */
void
crank_trans3_init_from_matrix (CrankTrans3    *trans,
                               CrankMatFloat4 *mat)
{
  CrankMatFloat3 rm = {
    mat->m00, mat->m01, mat->m02,
    mat->m10, mat->m11, mat->m12,
    mat->m20, mat->m21, mat->m22
  };

  trans->mtrans.x = mat->m02;
  trans->mtrans.y = mat->m12;
  trans->mtrans.z = mat->m13;

  trans->mscl = crank_mat_float3_get_det (&rm);
  trans->mscl = sqrtf ((0 < trans->mscl) ? trans->mscl : - trans->mscl);

  crank_mat_float3_divs_self (&rm, trans->mscl);
  crank_rot_mat_float3_to_quat_float (&rm, &trans->mrot);
}


/**
 * crank_trans3_to_matrix:
 * @trans: A Transformation.
 * @mat: (out): A Matrix.
 *
 * Converts transformation into matrix form.
 */
void
crank_trans3_to_matrix (CrankTrans3    *trans,
                        CrankMatFloat4 *mat)
{
  // Rotating.
  crank_rot_quat_float_to_mat_float4 (&trans->mrot, mat);

  // Scaling..
  mat->m00 *= trans->mscl;
  mat->m01 *= trans->mscl;
  mat->m02 *= trans->mscl;
  mat->m10 *= trans->mscl;
  mat->m11 *= trans->mscl;
  mat->m12 *= trans->mscl;
  mat->m20 *= trans->mscl;
  mat->m21 *= trans->mscl;
  mat->m22 *= trans->mscl;

  // Translating.
  mat->m03 = trans->mtrans.x;
  mat->m13 = trans->mtrans.y;
  mat->m23 = trans->mtrans.z;
}


/**
 * crank_trans3_to_matrix_transpose:
 * @trans: A Transformation.
 * @mat: (out): A Matrix.
 *
 * Converts transformation into matrix form.
 *
 * This is useful when column-major matrices are required.
 */
void
crank_trans3_to_matrix_transpose (CrankTrans3    *trans,
                                  CrankMatFloat4 *mat)
{
  // Rotating.
  crank_rot_quat_float_to_mat_float4_t (&trans->mrot, mat);

  // Scaling..
  mat->m00 *= trans->mscl;
  mat->m01 *= trans->mscl;
  mat->m02 *= trans->mscl;
  mat->m10 *= trans->mscl;
  mat->m11 *= trans->mscl;
  mat->m12 *= trans->mscl;
  mat->m20 *= trans->mscl;
  mat->m21 *= trans->mscl;
  mat->m22 *= trans->mscl;

  // Translating.
  mat->m30 = trans->mtrans.x;
  mat->m31 = trans->mtrans.y;
  mat->m32 = trans->mtrans.z;
}


/**
 * crank_trans3_copy:
 * @trans: A Transformation.
 * @other: (out): A Transformation.
 *
 * Copies a transformation to other.
 */
void
crank_trans3_copy (CrankTrans3 *trans,
                   CrankTrans3 *other)
{
  crank_vec_float3_copy (& trans->mtrans, & other->mtrans);
  crank_quat_float_copy (& trans->mrot, & other->mrot);
  other->mscl  = trans->mscl;
}

/**
 * crank_trans3_dup:
 * @trans: A Transformation.
 *
 * Duplicates a transformation to other.
 *
 * Returns: (transfer full): A Transformation.
 */
CrankTrans3*
crank_trans3_dup (CrankTrans3 *trans)
{
  CrankTrans3 *other = g_new (CrankTrans3, 1);

  crank_trans3_copy (trans, other);
  return other;
}


//////// Operations ////////////////////////////////////////////////////////////

/**
 * crank_trans3_translate:
 * @a: A Transformation.
 * @b: Translation amount.
 * @r: (out): A result.
 *
 * Apply translation to a transformation.
 */
void
crank_trans3_translate (CrankTrans3    *a,
                        CrankVecFloat3 *b,
                        CrankTrans3    *r)
{
  crank_vec_float3_add (& a->mtrans, b, & r->mtrans);
  r->mrot = a->mrot;
  r->mscl = a->mscl;
}

/**
 * crank_trans3_translate_self:
 * @a: A transformation.
 * @b: Translation amount.
 *
 * Apply translation to a transformation.
 */
void
crank_trans3_translate_self (CrankTrans3    *a,
                             CrankVecFloat3 *b)
{
  crank_vec_float3_add_self (& a->mtrans, b);
}


/**
 * crank_trans3_rotate:
 * @a: A Transformation.
 * @b: Rotation amount.
 * @r: (out): A result.
 *
 * Apply rotation to a transformation.
 */
void
crank_trans3_rotate (CrankTrans3    *a,
                     CrankQuatFloat *b,
                     CrankTrans3    *r)
{
  crank_quat_float_rotatev (b, & a->mtrans, & r->mtrans);

  crank_quat_float_mul (b, & a->mrot, & r->mrot);

  r->mscl = a->mscl;
}

/**
 * crank_trans3_rotate_self:
 * @a: A Transformation.
 * @b: Rotation amount.
 *
 * Apply rotation to a transformation.
 */
void
crank_trans3_rotate_self (CrankTrans3    *a,
                          CrankQuatFloat *b)
{
  CrankVecFloat3 atrans;
  CrankQuatFloat arot;

  crank_vec_float3_copy (& a->mtrans, & atrans);
  crank_quat_float_copy (& a->mrot, & arot);

  crank_quat_float_rotatev (b, & atrans, & a->mtrans);
  crank_quat_float_mul (b, & arot, & a->mrot);
}

/**
 * crank_trans3_scale:
 * @a: A Transformation.
 * @b: Scale amount.
 * @r: (out): A result.
 *
 * Apply scaling to a transformation.
 */
void
crank_trans3_scale (CrankTrans3  *a,
                    const gfloat  b,
                    CrankTrans3  *r)
{
  crank_vec_float3_muls (& a->mtrans, b, & r->mtrans);
  r->mrot = a->mrot;
  r->mscl = a->mscl * b;
}

/**
 * crank_trans3_scale_self:
 * @a: A Transformation.
 * @b: Scale amount.
 *
 * Apply scaling to a transformation.
 */
void
crank_trans3_scale_self (CrankTrans3  *a,
                         const gfloat  b)
{
  crank_vec_float3_muls_self (& a->mtrans, b);
  a->mscl *= b;
}

/**
 * crank_trans3_inverse:
 * @a: A Transformation.
 * @r: (out): A result.
 *
 * Inverses a transformation.
 */
void
crank_trans3_inverse (CrankTrans3 *a,
                      CrankTrans3 *r)
{
  r->mscl = 1 / a->mscl;
  crank_quat_float_conjugate (&a->mrot, &r->mrot);

  crank_quat_float_rotatev (&r->mrot, &a->mtrans, &r->mtrans);
  crank_vec_float3_divs_self (& r->mtrans, - a->mscl);
}

/**
 * crank_trans3_inverse_self:
 * @a: A Transformation.
 *
 * Inverses a transformation.
 */
void
crank_trans3_inverse_self (CrankTrans3 *a)
{
  CrankVecFloat3 atrans;
  crank_vec_float3_copy (& a->mtrans, &atrans);

  a->mscl = 1 / a->mscl;
  crank_quat_float_conjugate_self (& a->mrot);

  crank_quat_float_rotatev (&a->mrot, & atrans, &a->mtrans);
  crank_vec_float3_muls_self (& a->mtrans, a->mscl);

}


/**
 * crank_trans3_compose:
 * @a: A Transformation.
 * @b: Another transformation.
 * @r: (out): A result.
 *
 * Applies @a to @b.
 */
void
crank_trans3_compose (CrankTrans3 *a,
                      CrankTrans3 *b,
                      CrankTrans3 *r)
{
  crank_quat_float_rotatev (& a->mrot, & b->mtrans, & r->mtrans);
  crank_vec_float3_muls_self (& r->mtrans, a->mscl);
  crank_vec_float3_add_self (& r->mtrans, & a->mtrans);

  crank_quat_float_mul (&a->mrot, &b->mrot, &r->mrot);
  r->mscl = a->mscl * b->mscl;
}

/**
 * crank_trans3_compose_self:
 * @a: A Transformation.
 * @b: Another transformation.
 *
 * Applies @a to @b.
 */
void
crank_trans3_compose_self (CrankTrans3 *a,
                           CrankTrans3 *b)
{
  CrankVecFloat3 mtrans;

  crank_quat_float_rotatev (&a->mrot, & b->mtrans, & mtrans);
  crank_vec_float3_muls_self (& mtrans, a->mscl);
  crank_vec_float3_add_self (& a->mtrans, & mtrans);

  crank_quat_float_mul_self (& a->mrot, & b->mrot);
  a->mscl *= b->mscl;
}

/**
 * crank_trans3_relative_to:
 * @a: A Transformation.
 * @b: Another transformation.
 * @r: (out): Resulting transformation.
 *
 * Gets a relative transformation from @a to @b.
 */
void
crank_trans3_relative_to (CrankTrans3 *a,
                          CrankTrans3 *b,
                          CrankTrans3 *r)
{
  crank_trans3_inverse (a, r);
  crank_trans3_compose_self (r, b);
}

//////// Transformation ////////////////////////////////////////////////////////

/**
 * crank_trans3_transv:
 * @a: A transformation.
 * @b: A vector.
 * @r: (out): A result.
 *
 * Transform a vector.
 */
void
crank_trans3_transv (CrankTrans3    *a,
                     CrankVecFloat3 *b,
                     CrankVecFloat3 *r)
{
  crank_quat_float_rotatev (&a->mrot, b, r);
  crank_vec_float3_muls_self (r, a->mscl);
  crank_vec_float3_add_self (r, & a->mtrans);
}

/**
 * crank_trans3_trans_plane:
 * @a: A transformation.
 * @b: A Plane.
 * @r: (out): A result.
 *
 * Transform a plane representation.
 */
void
crank_trans3_trans_plane (CrankTrans3 *a,
                          CrankPlane3 *p,
                          CrankPlane3 *r)
{
  crank_quat_float_rotatev (& a->mrot, & p->normal, & r->normal);

  r->dist_origin = crank_vec_float3_dot (& a->mtrans, & r->normal) +
                   a->mscl * p->dist_origin;
}
