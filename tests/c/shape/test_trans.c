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
#include "crankshape.h"

void    test_2_translate (void);

void    test_2_rotate (void);

void    test_2_scale (void);

void    test_2_inverse (void);

void    test_2_compose (void);


int main (int    argc,
          char **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank/shape/trans/2/translate",
                   test_2_translate);

  g_test_add_func ("/crank/shape/trans/2/rotate",
                   test_2_rotate);

  g_test_add_func ("/crank/shape/trans/2/scale",
                   test_2_scale);

  g_test_add_func ("/crank/shape/trans/2/inverse",
                   test_2_inverse);

  g_test_add_func ("/crank/shape/trans/2/compose",
                   test_2_compose);

  return g_test_run ();
}


void
test_2_translate (void)
{
  CrankTrans2 a;
  CrankVecFloat2 trans;
  CrankTrans2 b;

  crank_vec_float2_init (& a.mtrans, 3, 4);
  a.mrot = G_PI_4;
  a.mscl = 2;

  crank_vec_float2_init (&trans, 6, 1);

  crank_trans2_translate (&a, &trans, &b);

  crank_assert_cmpfloat (b.mtrans.x, ==, 9);
  crank_assert_cmpfloat (b.mtrans.y, ==, 5);

  crank_assert_cmpfloat (b.mrot, ==, G_PI_4);
  crank_assert_cmpfloat (b.mscl, ==, 2);
}

void
test_2_rotate (void)
{
  CrankTrans2 a;
  CrankTrans2 b;

  crank_vec_float2_init (& a.mtrans, 3, 4);
  a.mrot = G_PI_4;
  a.mscl = 2;

  crank_trans2_rotate (&a, G_PI_4, &b);

  crank_assert_cmpfloat (b.mtrans.x, ==, -0.7071f);
  crank_assert_cmpfloat (b.mtrans.y, ==, 4.9497f);

  crank_assert_cmpfloat (b.mrot, ==, G_PI_2);
  crank_assert_cmpfloat (b.mscl, ==, 2);
}

void
test_2_scale (void)
{
  CrankTrans2 a;
  CrankTrans2 b;

  crank_vec_float2_init (& a.mtrans, 3, 4);
  a.mrot = G_PI_4;
  a.mscl = 2;

  crank_trans2_scale (&a, 2, &b);

  crank_assert_cmpfloat (b.mtrans.x, ==, 6);
  crank_assert_cmpfloat (b.mtrans.y, ==, 8);

  crank_assert_cmpfloat (b.mrot, ==, G_PI_4);
  crank_assert_cmpfloat (b.mscl, ==, 4);
}

void
test_2_inverse (void)
{
  CrankTrans2 a;
  CrankTrans2 b;

  crank_vec_float2_init (& a.mtrans, 3, 4);
  a.mrot = G_PI_4;
  a.mscl = 2;

  crank_trans2_inverse (&a, &b);

  crank_assert_cmpfloat (b.mtrans.x, ==, 2.4749f);
  crank_assert_cmpfloat (b.mtrans.y, ==, 0.3536f);

  crank_assert_cmpfloat (b.mrot, ==, -G_PI_4);
  crank_assert_cmpfloat (b.mscl, ==, 0.5f);
}

void
test_2_compose (void)
{

  CrankTrans2 a;
  CrankTrans2 b;
  CrankTrans2 c;

  crank_vec_float2_init (& a.mtrans, 3, 4);
  a.mrot = G_PI_4;
  a.mscl = 2;

  crank_vec_float2_init (& b.mtrans, 1, 2);
  b.mrot = G_PI_2;
  b.mscl = 1.5;

  crank_trans2_compose (&a, &b, &c);

  crank_assert_cmpfloat (c.mtrans.x, ==, 1.5858f);
  crank_assert_cmpfloat (c.mtrans.y, ==, 8.2426f);
  crank_assert_cmpfloat (c.mrot, ==, G_PI_2 + G_PI_4);
  crank_assert_cmpfloat (c.mscl, ==, 3.0f);
}
