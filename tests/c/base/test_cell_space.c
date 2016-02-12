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
#include <glib-object.h>

#include "crankbase.h"


//////// Test Functions ////////////////////////////////////////////////////////

static void test_2_new (void);
static void test_2_resize (void);
static void test_2_set (void);

static void test_3_new (void);
static void test_3_resize (void);
static void test_3_set (void);


//////// Main functions ////////////////////////////////////////////////////////

gint main (gint    argc,
           gchar **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank/base/cellspace/2/new",       test_2_new);
  g_test_add_func ("/crank/base/cellspace/2/resize",    test_2_resize);
  g_test_add_func ("/crank/base/cellspace/2/set",       test_2_set);

  g_test_add_func ("/crank/base/cellspace/3/new",       test_3_new);
  g_test_add_func ("/crank/base/cellspace/3/resize",    test_3_resize);
  g_test_add_func ("/crank/base/cellspace/3/set",       test_3_set);

  return g_test_run();
}


//////// Test Functions ////////////////////////////////////////////////////////

static void
test_2_new (void)
{
  guint i;
  guint j;

  CrankCellSpace2 *cs = crank_cell_space2_new_with_size (4, 4);

  g_assert_cmpuint (crank_cell_space2_get_width (cs), ==, 4);
  g_assert_cmpuint (crank_cell_space2_get_height (cs), ==, 4);
  for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
        {
          g_assert (crank_cell_space2_is_unset (cs, i, j));
        }
    }

  crank_cell_space2_set_int (cs, 2, 2, 15);

  crank_cell_space2_unref (cs);
}

static void
test_2_resize (void)
{
  guint i;
  guint j;

  CrankCellSpace2 *cs = crank_cell_space2_new ();
  crank_cell_space2_set_width (cs, 4);
  crank_cell_space2_set_height (cs, 4);

  g_assert_cmpuint (crank_cell_space2_get_width (cs), ==, 4);
  g_assert_cmpuint (crank_cell_space2_get_height (cs), ==, 4);
  for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
        {
          g_assert (crank_cell_space2_is_unset (cs, i, j));
        }
    }

  crank_cell_space2_set_int (cs, 2, 2, 15);

  crank_cell_space2_unref (cs);
}

static void
test_2_set (void)
{
  CrankCellSpace2 *cs = crank_cell_space2_new ();
  crank_cell_space2_set_width (cs, 4);
  crank_cell_space2_set_height (cs, 4);

  crank_cell_space2_set_int (cs, 2, 2, 15);
  crank_cell_space2_set_float (cs, 2, 2, 4.5f);

  g_assert (crank_cell_space2_type_of (cs, 2, 2) == G_TYPE_FLOAT);

  crank_cell_space2_unref (cs);
}

static void
test_3_new (void)
{
  guint i;
  guint j;
  guint k;

  CrankCellSpace3 *cs = crank_cell_space3_new_with_size (4, 4, 4);

  g_assert_cmpuint (crank_cell_space3_get_width (cs), ==, 4);
  g_assert_cmpuint (crank_cell_space3_get_height (cs), ==, 4);
  g_assert_cmpuint (crank_cell_space3_get_depth (cs), ==, 4);
  for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
        {
          for (k = 0; k < 4; k++)
            {
              g_assert (crank_cell_space3_is_unset (cs, i, j, k));
            }
        }
    }

  crank_cell_space3_set_int (cs, 2, 2, 2, 15);

  crank_cell_space3_unref (cs);
}

static void
test_3_resize (void)
{
  guint i;
  guint j;
  guint k;

  CrankCellSpace3 *cs = crank_cell_space3_new ();
  crank_cell_space3_set_width (cs, 4);
  crank_cell_space3_set_height (cs, 4);
  crank_cell_space3_set_depth (cs, 4);

  g_assert_cmpuint (crank_cell_space3_get_width (cs), ==, 4);
  g_assert_cmpuint (crank_cell_space3_get_height (cs), ==, 4);
  g_assert_cmpuint (crank_cell_space3_get_depth (cs), ==, 4);
  for (i = 0; i < 4; i++)
    {
      for (j = 0; j < 4; j++)
        {
          for (k = 0;k < 4; k++)
            {
              g_assert (crank_cell_space3_is_unset (cs, i, j, k));
            }
        }
    }

  crank_cell_space3_set_int (cs, 2, 2, 2, 15);

  crank_cell_space3_unref (cs);
}

static void
test_3_set (void)
{
  CrankCellSpace3 *cs = crank_cell_space3_new ();
  crank_cell_space3_set_width (cs, 4);
  crank_cell_space3_set_height (cs, 4);
  crank_cell_space3_set_depth (cs, 4);

  crank_cell_space3_set_int (cs, 2, 2, 2, 15);
  crank_cell_space3_set_float (cs, 2, 2, 2, 4.5f);

  g_assert (crank_cell_space3_type_of (cs, 2, 2, 2) == G_TYPE_FLOAT);

  crank_cell_space3_unref (cs);
}
