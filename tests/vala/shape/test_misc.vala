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

public int main (string[] args) {
	GLib.Test.init (ref args);

	GLib.Test.add_func ("/crank/shape/misc/winding", test_winding);

	GLib.Test.add_func ("/crank/shape/misc/seg/intersect", test_seg_intersect);

	GLib.Test.add_func ("/crank/shape/misc/tri/bcoord", test_tri_bcoord);

	return GLib.Test.run ();
}

private void test_winding () {
    Crank.VecFloat2 pts[3];

    pts[0] = {3, 4};
    pts[1] = {2, 2};
    pts[2] = {1, 0};
    assert (Crank.Winding.from_point_arr (pts) == Crank.Winding.NONE);

    pts[0] = {1, 7};
    pts[1] = {3, 5};
    pts[2] = {2, 8};
    assert (Crank.Winding.from_point_arr (pts) == Crank.Winding.CCW);

    pts[0] = {5, 5};
    pts[1] = {3, 3};
    pts[2] = {0, 2};
    assert (Crank.Winding.from_point_arr (pts) == Crank.Winding.CW);
}

private void test_seg_intersect () {
    Crank.VecFloat2 aa = {3.0f, 4.0f};
    Crank.VecFloat2 ab = {5.0f, 12.0f};
    Crank.VecFloat2 ba = {12.0f, 5.0f};
    Crank.VecFloat2 bb = {4.0f, 3.0f};

    Crank.VecFloat2 i;

    assert (! Crank.seg_intersect (aa, ab, ba, bb, out i));

    aa = {2.0f, 1.0f};
    ab = {5.0f, 9.0f};
    ba = {1.0f, 5.0f};
    bb = {4.0f, 3.0f};

    assert (Crank.seg_intersect (aa, ab, ba, bb, out i));
    Crank.assert_eq_vecfloat2_imm (i, 3, (11.0f / 3.0f));
}

private void test_tri_bcoord () {
  Crank.VecFloat2 tri[3] = {
      Crank.VecFloat2 (5, 4),
      Crank.VecFloat2 (1, 2),
      Crank.VecFloat2 (3, 6)
  };

  Crank.VecFloat3 bcoord;
  bcoord = Crank.tri_bcoord (tri, {3, 4});
  Crank.assert_eq_vecfloat3_imm (bcoord, 0.3333f, 0.3333f, 0.3333f);

  bcoord = Crank.tri_bcoord (tri, {5, 12});
  Crank.assert_eq_vecfloat3_imm (bcoord, -0.3333f, -1.3333f, 2.6667f);
}
