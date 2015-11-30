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

	GLib.Test.add_func ("/crank/shape/gjk2/distance", test_gjk2_distance);

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
    
    Crank.Trans2 apos = Crank.Trans2 ();
    Crank.Trans2 bpos = Crank.Trans2 ();

    apos.mtrans = {-2.0f, 1.0f};
    bpos.mtrans = {3.0f, 2.0f};
    
    Crank.Trans2 abpos = apos.inverse ().compose (bpos);

    assert (! Crank.gjk2 (a, b, abpos));


    bpos.mrot = (float)(Math.PI * 7 / 6);

    abpos = apos.inverse ().compose (bpos);

    assert (! Crank.gjk2 (a, b, abpos));
    
    apos.mtrans = {-1, 3};
    bpos.mtrans = {0, -2};
    apos.mrot = (float)(Math.PI * 2 / 3);
    bpos.mrot = 0;
    apos.mscl = 0.5f;
    bpos.mscl = 2.0f;
    
    abpos = apos.inverse ().compose (bpos);
    
    assert (Crank.gjk2 (a, b, abpos));
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

    Crank.Trans2 apos = Crank.Trans2 ();
    Crank.Trans2 bpos = Crank.Trans2 ();

    apos.mtrans = {-2.0f, 1.0f};
    bpos.mtrans = {3.0f, 2.0f};

    Crank.Trans2 abpos = apos.inverse ().compose (bpos);

    Crank.assert_eqfloat (Crank.gjk2_distance (a, b, abpos), 1.0f);


    bpos.mrot = (float)(Math.PI * 7 / 12);

    abpos = apos.inverse ().compose (bpos);

    Crank.assert_eqfloat (Crank.gjk2_distance (a, b, abpos), 0.0389f);


    apos.mtrans = {-5, 3};
    bpos.mtrans = {0, -2};
    apos.mrot = (float)(Math.PI * 2 / 3);
    bpos.mrot = (float)(Math.PI * 7 / 12);
    apos.mscl = 0.5f;
    bpos.mscl = 2.0f;

    abpos = apos.inverse ().compose (bpos);

    Crank.assert_eqfloat (Crank.gjk2_distance (a, b, abpos), 1.3496f);
}

