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

  CrankVecFloat2 apos = {-2.0f, 1.0f};
  CrankVecFloat2 bpos = {3.0f, 2.0f};

  a = crank_shape2_cpolygon_new (avert, 6);

  b = crank_shape2_cpolygon_new (bvert, 7);

  crank_shape2_set_pos_trans (CRANK_SHAPE2 (a), &apos);
  crank_shape2_set_pos_trans (CRANK_SHAPE2 (b), &bpos);

  g_assert (! crank_gjk2 (CRANK_SHAPE2_POLYGON(a),
                          CRANK_SHAPE2_POLYGON(b),
                          NULL));


  crank_shape2_set_pos_rot (CRANK_SHAPE2 (b), G_PI * 7 / 6);

  g_assert (! crank_gjk2 (CRANK_SHAPE2_POLYGON(a),
                          CRANK_SHAPE2_POLYGON(b),
                          NULL));


  apos.x = -1;
  apos.y = 3;
  bpos.x = 0;
  bpos.y = -2;

  crank_shape2_set_pos_trans (CRANK_SHAPE2 (a), &apos);
  crank_shape2_set_pos_rot (CRANK_SHAPE2 (a), G_PI * 2 / 3);
  crank_shape2_set_pos_scl (CRANK_SHAPE2 (a), 0.5f);

  crank_shape2_set_pos_trans (CRANK_SHAPE2 (b), &bpos);
  crank_shape2_set_pos_rot (CRANK_SHAPE2 (b), 0);
  crank_shape2_set_pos_scl (CRANK_SHAPE2 (b), 2.0f);

  g_assert (crank_gjk2 (CRANK_SHAPE2_POLYGON(a),
                        CRANK_SHAPE2_POLYGON(b),
                        NULL));
}

static void
test_gjk2_distance (void)
{
  CrankShape2CPolygon *a;
  CrankShape2CPolygon *b;

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

  CrankVecFloat2 apos = {-2.0f, 1.0f};
  CrankVecFloat2 bpos = {3.0f, 2.0f};

  a = crank_shape2_cpolygon_new (avert, 6);

  b = crank_shape2_cpolygon_new (bvert, 7);

  crank_shape2_set_pos_trans (CRANK_SHAPE2 (a), &apos);
  crank_shape2_set_pos_trans (CRANK_SHAPE2 (b), &bpos);

  crank_assert_cmpfloat (crank_gjk2_distance (CRANK_SHAPE2_POLYGON(a),
                                              CRANK_SHAPE2_POLYGON(b),
                                              NULL),
                         ==,
                         1.0f);


  crank_shape2_set_pos_rot (CRANK_SHAPE2 (b), G_PI * 7 / 12);

  crank_assert_cmpfloat (crank_gjk2_distance (CRANK_SHAPE2_POLYGON(a),
                                              CRANK_SHAPE2_POLYGON(b),
                                              NULL),
                         ==,
                         0.0389f);


  apos.x = -5;
  apos.y = 3;
  bpos.x = 0;
  bpos.y = -2;

  crank_shape2_set_pos_trans (CRANK_SHAPE2 (a), &apos);
  crank_shape2_set_pos_rot (CRANK_SHAPE2 (a), G_PI * 2 / 3);
  crank_shape2_set_pos_scl (CRANK_SHAPE2 (a), 0.5f);

  crank_shape2_set_pos_trans (CRANK_SHAPE2 (b), &bpos);
  crank_shape2_set_pos_rot (CRANK_SHAPE2 (b), G_PI * 7 / 12);
  crank_shape2_set_pos_scl (CRANK_SHAPE2 (b), 2.0f);

  crank_assert_cmpfloat (crank_gjk2_distance (CRANK_SHAPE2_POLYGON(a),
                                              CRANK_SHAPE2_POLYGON(b),
                                              NULL),
                         ==,
                         1.3496f);
}
