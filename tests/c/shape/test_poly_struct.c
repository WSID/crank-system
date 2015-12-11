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
#include "crankshape.h"

//////// Test cases ////////////////////////////////////////////////////////////

static void test_tetrahedron (void);

static void test_cube (void);


//////// Main //////////////////////////////////////////////////////////////////

int main (int    argc,
          char **argv)
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/crank_shape/poly_struct/tetrahedron",
                   test_tetrahedron);

  g_test_add_func ("/crank_shape/poly_struct/cube",
                   test_cube);

  return g_test_run ();
}

//////// Test Cases ////////////////////////////////////////////////////////////

static void
test_tetrahedron (void)
{
  CrankPolyStruct3 *pstruct = crank_poly_struct3_new ();
  guint fverts[3];

  crank_poly_struct3_set_nvertices (pstruct, 4);

  crank_poly_struct3_add_face_vertices (pstruct, 3, 0, 2, 1);
  crank_poly_struct3_add_face_vertices (pstruct, 3, 3, 0 ,1);
  crank_poly_struct3_add_face_vertices (pstruct, 3, 3, 1, 2);
  crank_poly_struct3_add_face_vertices (pstruct, 3, 3, 2, 0);

  g_assert_cmpuint (crank_poly_struct3_get_nvertices (pstruct), ==, 4);
  g_assert_cmpuint (crank_poly_struct3_get_nedges (pstruct), ==, 6);
  g_assert_cmpuint (crank_poly_struct3_get_nfaces (pstruct), ==, 4);

  g_assert (crank_poly_struct3_check_valid (pstruct));

  crank_poly_struct3_unref (pstruct);
}

static void
test_cube (void)
{
  CrankPolyStruct3 *pstruct = crank_poly_struct3_new ();
  guint fverts[4];

  crank_poly_struct3_set_nvertices (pstruct, 8);

  crank_poly_struct3_add_face_vertices (pstruct, 4, 0, 1, 2, 3);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 0, 4, 5, 1);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 1, 5, 6, 2);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 2, 6, 7, 3);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 3, 7, 4, 0);
  crank_poly_struct3_add_face_vertices (pstruct, 4, 7, 6, 5, 4);

  g_assert_cmpuint (crank_poly_struct3_get_nvertices (pstruct), ==, 8);
  g_assert_cmpuint (crank_poly_struct3_get_nedges (pstruct), ==, 12);
  g_assert_cmpuint (crank_poly_struct3_get_nfaces (pstruct), ==, 6);

  g_assert (crank_poly_struct3_check_valid (pstruct));

  crank_poly_struct3_unref (pstruct);
} 
