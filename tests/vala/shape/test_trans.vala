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

    GLib.Test.add_func ("/crank/shape/trans/2/translate",
        test_2_translate);

    GLib.Test.add_func ("/crank/shape/trans/2/rotate",
        test_2_rotate);

    GLib.Test.add_func ("/crank/shape/trans/2/scale",
        test_2_scale);

    GLib.Test.add_func ("/crank/shape/trans/2/inverse",
        test_2_inverse);

    GLib.Test.add_func ("/crank/shape/trans/2/compose",
        test_2_compose);

    GLib.Test.add_func ("/crank/shape/trans/2/transv",
        test_2_transv);

    return GLib.Test.run ();
}

void test_2_translate () {
    Crank.Trans2 a = Crank.Trans2 ();

    a.mtrans = {3, 4};
    a.mrot = (float)GLib.Math.PI_4;
    a.mscl = 2;

    Crank.Trans2 b = a.translate ({6, 1});

    Crank.assert_eqfloat (b.mtrans.x, 9);
    Crank.assert_eqfloat (b.mtrans.y, 5);

    Crank.assert_eqfloat (b.mrot, (float)GLib.Math.PI_4);
    Crank.assert_eqfloat (b.mscl, 2.0f);
}

void test_2_rotate () {
    Crank.Trans2 a = Crank.Trans2 ();

    a.mtrans = {3, 4};
    a.mrot = (float)GLib.Math.PI_4;
    a.mscl = 2;

    Crank.Trans2 b = a.rotate ((float)GLib.Math.PI_4);

    Crank.assert_eqfloat (b.mtrans.x, -0.7071f);
    Crank.assert_eqfloat (b.mtrans.y, 4.9497f);

    Crank.assert_eqfloat (b.mrot, (float)GLib.Math.PI_2);
    Crank.assert_eqfloat (b.mscl, 2.0f);
}

void test_2_scale () {
    Crank.Trans2 a = Crank.Trans2 ();

    a.mtrans = {3, 4};
    a.mrot = (float)GLib.Math.PI_4;
    a.mscl = 2;

    Crank.Trans2 b = a.scale (2.0f);

    Crank.assert_eqfloat (b.mtrans.x, 6);
    Crank.assert_eqfloat (b.mtrans.y, 8);

    Crank.assert_eqfloat (b.mrot, (float)GLib.Math.PI_4);
    Crank.assert_eqfloat (b.mscl, 4);
}

void test_2_inverse () {
    Crank.Trans2 a = Crank.Trans2 ();

    a.mtrans = {3, 4};
    a.mrot = (float)GLib.Math.PI_4;
    a.mscl = 2;

    Crank.Trans2 b = a.inverse ();

    Crank.assert_eqfloat (b.mtrans.x, -2.4749f);
    Crank.assert_eqfloat (b.mtrans.y, -0.3536f);

    Crank.assert_eqfloat (b.mrot, (float)(-GLib.Math.PI_4));
    Crank.assert_eqfloat (b.mscl, 0.5f);
}


void test_2_compose () {
    Crank.Trans2 a = Crank.Trans2 ();

    a.mtrans = {3, 4};
    a.mrot = (float)GLib.Math.PI_4;
    a.mscl = 2;

    Crank.Trans2 b = Crank.Trans2 ();

    b.mtrans = {1, 2};
    b.mrot = (float)GLib.Math.PI_2;
    b.mscl = 1.5f;

    Crank.Trans2 c = a.compose (b);

    Crank.assert_eqfloat (c.mtrans.x, 1.5858f);
    Crank.assert_eqfloat (c.mtrans.y, 8.2426f);

    Crank.assert_eqfloat (c.mrot, (float)(GLib.Math.PI_4 + GLib.Math.PI_2));
    Crank.assert_eqfloat (c.mscl, 3.0f);
}

void test_2_transv () {
    Crank.Trans2 a = Crank.Trans2 ();

    a.mtrans = {3, 4};
    a.mrot = (float)GLib.Math.PI_4;
    a.mscl = 2;

    Crank.VecFloat2 c = a.transv ({5, 12});

    Crank.assert_eqfloat (c.x, -6.8995f);
    Crank.assert_eqfloat (c.y, 28.0416f);
}
