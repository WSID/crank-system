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

void    test_vec2_rot (void);

void    test_vec2_left (void);

void    test_vec2_right (void);


//////// Main function /////////////////////////////////////////////////////////

gint main (gint    argc,
           gchar **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank/shape/rot/vec2/rot",
                   test_vec2_rot);

  g_test_add_func ("/crank/shape/rot/vec2/left",
                   test_vec2_left);

  g_test_add_func ("/crank/shape/rot/vec2/right",
                   test_vec2_right);

  return g_test_run ();
}


//////// Test functions ////////////////////////////////////////////////////////

void
test_vec2_rot (void)
{
  CrankVecFloat2 a = {0.9950f, 0.0998f}; // cos (0.1), sin (0.1)
  CrankVecFloat2 b;

  crank_rot_vec2_rot (&a, 0.5f, &b);

  crank_assert_cmpfloat (b.x, ==, 0.8253f);
  crank_assert_cmpfloat (b.y, ==, 0.5646f);
}

void
test_vec2_left (void)
{
  CrankVecFloat2 a = {0.9950f, 0.0998f}; // cos (0.1), sin (0.1)
  CrankVecFloat2 b;

  crank_rot_vec2_left (&a, &b);

  crank_assert_cmpfloat (b.x, ==, -0.0998f);
  crank_assert_cmpfloat (b.y, ==, 0.9950f);
}

void
test_vec2_right (void)
{
  CrankVecFloat2 a = {0.9950f, 0.0998f}; // cos (0.1), sin (0.1)
  CrankVecFloat2 b;

  crank_rot_vec2_right (&a, &b);

  crank_assert_cmpfloat (b.x, ==, 0.0998f);
  crank_assert_cmpfloat (b.y, ==, -0.9950f);
}
