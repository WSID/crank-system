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

int main (string[] args) {
    GLib.Test.init (ref args);

    GLib.Test.add_func ("/crank/shape/poly_struct/tetrahedron",
                        test_tetrahedron);

    GLib.Test.add_func ("/crank/shape/poly_struct/cube",
                        test_cube);

    return GLib.Test.run ();
}

private void test_tetrahedron () {
    Crank.PolyStruct3 pstruct = new Crank.PolyStruct3();

    pstruct.nvertices = 4;

    pstruct.add_face_vertices (3, 0, 2, 1);
    pstruct.add_face_vertices (3, 3, 0, 1);
    pstruct.add_face_vertices (3, 3, 1, 2);
    pstruct.add_face_vertices (3, 3, 2, 0);

    assert (pstruct.nvertices == 4);
    assert (pstruct.nedges == 6);
    assert (pstruct.nfaces == 4);

    assert (pstruct.check_valid ());
}

private void test_cube () {
    Crank.PolyStruct3 pstruct = new Crank.PolyStruct3();

    pstruct.nvertices = 8;

    pstruct.add_face_vertices (4, 0, 1, 2, 3);
    pstruct.add_face_vertices (4, 0, 4, 5, 1);
    pstruct.add_face_vertices (4, 1, 5, 6, 2);
    pstruct.add_face_vertices (4, 2, 6, 7, 3);
    pstruct.add_face_vertices (4, 3, 7, 4, 0);
    pstruct.add_face_vertices (4, 7, 6, 5, 4);

    assert (pstruct.nvertices == 8);
    assert (pstruct.nedges == 12);
    assert (pstruct.nfaces == 6);

    assert (pstruct.check_valid ());
}
