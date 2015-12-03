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

static void     test_winding (void);

static void     test_seg_intersect (void);

static void     test_tri_bcoord (void);

static void     test_tetra_bcoord (void);


//////// Main //////////////////////////////////////////////////////////////////

gint main (gint argc, gchar **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank/shape/misc/winding", test_winding);

  g_test_add_func ("/crank/shape/misc/seg/intersect", test_seg_intersect);

  g_test_add_func ("/crank/shape/misc/tri/bcoord", test_tri_bcoord);

  g_test_add_func ("/crank/shape/misc/tetra/bcoord", test_tetra_bcoord);

  return g_test_run ();
}

/////// Test Functions /////////////////////////////////////////////////////////

static void
test_winding (void)
{
  CrankVecFloat2 pts[3];

  crank_vec_float2_init (pts + 0, 3, 4);
  crank_vec_float2_init (pts + 1, 2, 2);
  crank_vec_float2_init (pts + 2, 1, 0);
  g_assert (crank_winding_from_point_arr (pts) == CRANK_WINDING_NONE);

  crank_vec_float2_init (pts + 0, 1, 7);
  crank_vec_float2_init (pts + 1, 3, 5);
  crank_vec_float2_init (pts + 2, 2, 8);
  g_assert (crank_winding_from_point_arr (pts) == CRANK_WINDING_CCW);

  crank_vec_float2_init (pts + 0, 5, 5);
  crank_vec_float2_init (pts + 1, 3, 3);
  crank_vec_float2_init (pts + 2, 0, 2);
  g_assert (crank_winding_from_point_arr (pts) == CRANK_WINDING_CW);
}

static void
test_seg_intersect (void)
{
  CrankVecFloat2 aa;
  CrankVecFloat2 ab;
  CrankVecFloat2 ba;
  CrankVecFloat2 bb;

  CrankVecFloat2 i;

  crank_vec_float2_init (&aa, 3.0,  4.0);
  crank_vec_float2_init (&ab, 5.0,  12.0);

  crank_vec_float2_init (&ba, 12.0, 5.0);
  crank_vec_float2_init (&bb, 4.0,  3.0);

  g_assert (! crank_seg_intersect (&aa, &ab, &ba, &bb, &i));

  crank_vec_float2_init (&aa, 2.0,  1.0);
  crank_vec_float2_init (&ab, 5.0,  9.0);

  crank_vec_float2_init (&ba, 1.0,  5.0);
  crank_vec_float2_init (&bb, 4.0,  3.0);

  g_assert (crank_seg_intersect (&aa, &ab, &ba, &bb, &i));

  crank_assert_eq_vecfloat2_imm (&i, 3, (11.0f / 3.0f));
}

static void
test_tri_bcoord (void)
{
  CrankVecFloat2 tri[3];
  CrankVecFloat2 pt;
  CrankVecFloat3 bcoord;

  crank_vec_float2_init (tri + 0, 5, 4);
  crank_vec_float2_init (tri + 1, 1, 2);
  crank_vec_float2_init (tri + 2, 3, 6);

  crank_vec_float2_init (&pt, 3, 4);
  crank_tri_bcoord (tri, &pt, &bcoord);
  crank_assert_eq_vecfloat3_imm (&bcoord, 0.3333f, 0.3333f, 0.3333f);

  crank_vec_float2_init (&pt, 5, 12);
  crank_tri_bcoord (tri, &pt, &bcoord);
  crank_assert_eq_vecfloat3_imm (&bcoord, -0.3333f, -1.3333f, 2.6667f);
}

static void
test_tetra_bcoord (void)
{
  CrankVecFloat3 tetra[4];
  CrankVecFloat3 pt;
  CrankVecFloat4 bcoord;

  crank_vec_float3_init (tetra + 0, 2, 3, 0);
  crank_vec_float3_init (tetra + 1, 0, 1, 1);
  crank_vec_float3_init (tetra + 2, 3, 1, 2);
  crank_vec_float3_init (tetra + 3, 1, 2, 3);

  crank_vec_float3_init (&pt, 2, 2, 2);
  crank_tetra_bcoord (tetra, &pt, &bcoord);
  crank_assert_eq_vecfloat4_imm (&bcoord, 0.2667f, -0.0667f, 0.3333f, 0.4667f);

  crank_vec_float3_init (&pt, 1, 1, 3);
  crank_tetra_bcoord (tetra, &pt, &bcoord);
  crank_assert_eq_vecfloat4_imm (&bcoord, -0.3333f, 0.3333f, 0.3333f, 0.6667f);
}
