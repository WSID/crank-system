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

//////// Test functions ////////////////////////////////////////////////////////

static void     test_gjk2 (void);

static void     test_gjk2_distance (void);


//////// Main //////////////////////////////////////////////////////////////////

gint main (gint argc, gchar **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank/shape/gjk/2", test_gjk2);

  g_test_add_func ("/crank/shape/gjk/2/distance", test_gjk2_distance);

  return g_test_run ();
}



//////// Test Functions ////////////////////////////////////////////////////////

static void
test_gjk2 (void)
{
  CrankShape2CPolygon *a;
  CrankShape2CPolygon *b;

  CrankTrans2 apos;
  CrankTrans2 bpos;
  CrankTrans2 abpos;

  static CrankVecFloat2 avert[] = {
      {2.0f, 1.0f},
      {-2.0f, 1.0f},
      {-3.0f, 0.0f},
      {-3.0f, -1.0f},
      {-1.0f, -2.0f},
      {2.0f, -1.0f}
  };

  static CrankVecFloat2 bvert[] = {
      {2.0f, 3.0f},
      {1.0f, 3.0f},
      {-2.0f, 1.0f},
      {-2.0f, -1.0f},
      {-1.0f, -2.0f},
      {0.0f, -2.0f},
      {2.0f, 0.0f}
  };

  crank_trans2_init (&apos);
  crank_trans2_init (&bpos);

  crank_vec_float2_init (&apos.mtrans, -2.0f, 1.0f);
  crank_vec_float2_init (&bpos.mtrans, 3.0f, 2.0f);

  a = crank_shape2_cpolygon_new (avert, 6);
  b = crank_shape2_cpolygon_new (bvert, 7);

  crank_trans2_inverse (&apos, &abpos);
  crank_trans2_compose_self (&abpos, &bpos);

  g_assert (! crank_gjk2 (CRANK_SHAPE2_VERTEXED(a),
                        CRANK_SHAPE2_VERTEXED(b),
                        &abpos));


  bpos.mrot = G_PI * 7 / 6;

  crank_trans2_inverse (&apos, &abpos);
  crank_trans2_compose_self (&abpos, &bpos);

  g_assert (! crank_gjk2 (CRANK_SHAPE2_VERTEXED(a),
                        CRANK_SHAPE2_VERTEXED(b),
                        &abpos));


  crank_vec_float2_init (&apos.mtrans, -1.0f, 3.0f);
  apos.mrot = G_PI * 2 / 3;
  apos.mscl = 0.5f;

  crank_vec_float2_init (&bpos.mtrans, 0.0f, -2.0f);
  bpos.mrot = 0;
  bpos.mscl = 2.0f;

  crank_trans2_inverse (&apos, &abpos);
  crank_trans2_compose_self (&abpos, &bpos);

  g_assert (crank_gjk2 (CRANK_SHAPE2_VERTEXED(a),
                        CRANK_SHAPE2_VERTEXED(b),
                        &abpos));
}

static void
test_gjk2_distance (void)
{
  CrankShape2CPolygon *a;
  CrankShape2CPolygon *b;

  CrankTrans2 apos;
  CrankTrans2 bpos;
  CrankTrans2 abpos;

  static CrankVecFloat2 avert[] = {
      {2.0f, 1.0f},
      {-2.0f, 1.0f},
      {-3.0f, 0.0f},
      {-3.0f, -1.0f},
      {-1.0f, -2.0f},
      {2.0f, -1.0f}
  };

  static CrankVecFloat2 bvert[] = {
      {2.0f, 3.0f},
      {1.0f, 3.0f},
      {-2.0f, 1.0f},
      {-2.0f, -1.0f},
      {-1.0f, -2.0f},
      {0.0f, -2.0f},
      {2.0f, 0.0f}
  };

  crank_trans2_init (&apos);
  crank_trans2_init (&bpos);

  crank_vec_float2_init (&apos.mtrans, -2.0f, 1.0f);
  crank_vec_float2_init (&bpos.mtrans, 3.0f, 2.0f);

  a = crank_shape2_cpolygon_new (avert, 6);
  b = crank_shape2_cpolygon_new (bvert, 7);

  crank_trans2_inverse (&apos, &abpos);
  crank_trans2_compose_self (&abpos, &bpos);

  crank_assert_cmpfloat (crank_gjk2_distance (CRANK_SHAPE2_VERTEXED(a),
                                              CRANK_SHAPE2_VERTEXED(b),
                                              &abpos),
                         ==,
                         1.0f);


  bpos.mrot = G_PI * 7 / 12;

  crank_trans2_inverse (&apos, &abpos);
  crank_trans2_compose_self (&abpos, &bpos);

  crank_assert_cmpfloat (crank_gjk2_distance (CRANK_SHAPE2_VERTEXED(a),
                                              CRANK_SHAPE2_VERTEXED(b),
                                              &abpos),
                         ==,
                         0.0389f);

  crank_vec_float2_init (& apos.mtrans, -5, 3);
  apos.mrot = G_PI * 2 / 3;
  apos.mscl = 0.5f;

  crank_vec_float2_init (& bpos.mtrans, 0, -2);
  bpos.mrot = G_PI * 7 / 12;
  bpos.mscl = 2.0f;

  crank_trans2_inverse (&apos, &abpos);
  crank_trans2_compose_self (&abpos, &bpos);

  crank_assert_cmpfloat (crank_gjk2_distance (CRANK_SHAPE2_VERTEXED(a),
                                              CRANK_SHAPE2_VERTEXED(b),
                                              &abpos),
                         ==,
                         1.3496f);
}
