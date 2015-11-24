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
	
	GLib.Test.add_func ("/crank/shape/gjk2", test_gjk2);

	return GLib.Test.run ();
}

public void test_gjk2 () {
    Crank.VecFloat2 avert[6] = {
        Crank.VecFloat2 (2.0f, 1.0f),
        Crank.VecFloat2 (-2.0f, 1.0f),
        Crank.VecFloat2 (-3.0f, 0.0f),
        Crank.VecFloat2 (-3.0f, -1.0f),
        Crank.VecFloat2 (-1.0f, -2.0f),
        Crank.VecFloat2 (2.0f, -1.0f)
    };
    
    Crank.VecFloat2 bvert[7] = {
        Crank.VecFloat2 (2.0f, 3.0f),
        Crank.VecFloat2 (1.0f, 3.0f),
        Crank.VecFloat2 (-2.0f, 1.0f),
        Crank.VecFloat2 (-2.0f, -1.0f),
        Crank.VecFloat2 (-1.0f, -2.0f),
        Crank.VecFloat2 (0.0f, -2.0f),
        Crank.VecFloat2 (2.0f, 0.0f)
    };
    
    Crank.Shape2CPolygon a = new Crank.Shape2CPolygon (avert);
    Crank.Shape2CPolygon b = new Crank.Shape2CPolygon (bvert);
    
    a.pos_trans = {-2.0f, 1.0f};
    b.pos_trans = {3.0f, 2.0f};
    
    assert (! Crank.gjk2 (a, b, null));
    
    
    b.pos_rot = (float)(Math.PI * 7 / 6);
    
    assert (! Crank.gjk2 (a, b, null));
    
    a.pos_trans = {-1, 3};
    b.pos_trans = {0, -2};
    a.pos_rot = (float)(Math.PI * 2 / 3);
    b.pos_rot = 0;
    a.pos_scl = 0.5f;
    b.pos_scl = 2.0f;
    
    assert (Crank.gjk2 (a, b, null));
}


public void test_gjk2_distance () {
    Crank.VecFloat2 avert[6] = {
        Crank.VecFloat2 (2.0f, 1.0f),
        Crank.VecFloat2 (-2.0f, 1.0f),
        Crank.VecFloat2 (-3.0f, 0.0f),
        Crank.VecFloat2 (-3.0f, -1.0f),
        Crank.VecFloat2 (-1.0f, -2.0f),
        Crank.VecFloat2 (2.0f, -1.0f)
    };

    Crank.VecFloat2 bvert[7] = {
        Crank.VecFloat2 (2.0f, 3.0f),
        Crank.VecFloat2 (1.0f, 3.0f),
        Crank.VecFloat2 (-2.0f, 1.0f),
        Crank.VecFloat2 (-2.0f, -1.0f),
        Crank.VecFloat2 (-1.0f, -2.0f),
        Crank.VecFloat2 (0.0f, -2.0f),
        Crank.VecFloat2 (2.0f, 0.0f)
    };

    Crank.Shape2CPolygon a = new Crank.Shape2CPolygon (avert);
    Crank.Shape2CPolygon b = new Crank.Shape2CPolygon (bvert);

    a.pos_trans = {-2.0f, 1.0f};
    b.pos_trans = {3.0f, 2.0f};

    Crank.assert_eqfloat (Crank.gjk2_distance (a, b, null), 1.0f);


    b.pos_rot = (float)(Math.PI * 7 / 12);

    Crank.assert_eqfloat (Crank.gjk2_distance (a, b, null), 0.0389f);

    a.pos_trans = {-5, 3};
    b.pos_trans = {0, -2};
    a.pos_rot = (float)(Math.PI * 2 / 3);
    b.pos_rot = (float)(Math.PI * 7 / 12);
    a.pos_scl = 0.5f;
    b.pos_scl = 2.0f;

    Crank.assert_eqfloat (Crank.gjk2_distance (a, b, null), 1.3496f);
}

