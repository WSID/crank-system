#!/usr/bin/python

# Copyright (C) 2015, WSID

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import unittest
import math;

from gi.repository import GObject
from gi.repository import CrankBase
from gi.repository import CrankShape

class TestGJK (unittest.TestCase):

    def assertFloat (self, a, b, delta=0.0001):
        """A simple custom assert that given values are same.

        It takes into delta values into account, so that test can endure little
        errors.
        """
        try:	#if they are both of list type.
            if (len(a) != len(b)):
                raise AssertionError ("array length: %d != %d" % (len(a), len(b)))

                for i in range (0, len(a)):
                    if ((a[i] < b[i] - delta) or (b[i] + delta < a[i])):
                        raise AssertionError ("%g != %g (diff=%g)" % (a[i], b[i], b[i]-a[i]))

        except TypeError: #then they are numeric type.
            if ((a < b - delta) or (b + delta < a)):
                raise AssertionError ("%g != %g (diff=%g)" % (a, b, b-a))


    def test_gjk (self):
        a = CrankShape.Shape2CPolygon.new( [
            CrankBase.VecFloat2.init (2, 1),
            CrankBase.VecFloat2.init (-2, 1),
            CrankBase.VecFloat2.init (-3, 0),
            CrankBase.VecFloat2.init (-3, -1),
            CrankBase.VecFloat2.init (-1, -2),
            CrankBase.VecFloat2.init (2, -1)
        ] )
        b = CrankShape.Shape2CPolygon.new( [
            CrankBase.VecFloat2.init (2, 3),
            CrankBase.VecFloat2.init (1, 3),
            CrankBase.VecFloat2.init (-2, 1),
            CrankBase.VecFloat2.init (-2, -1),
            CrankBase.VecFloat2.init (-1, -2),
            CrankBase.VecFloat2.init (0, -2),
            CrankBase.VecFloat2.init (2, 0)
        ])

        apos = CrankShape.Trans2.init ();
        bpos = CrankShape.Trans2.init ();

        apos.mtrans = CrankBase.VecFloat2.init (-2, 1)
        bpos.mtrans = CrankBase.VecFloat2.init (3, 2)

        abpos = apos.inverse().compose (bpos)

        assert (not CrankShape.gjk2 (a, b, abpos))

        bpos.mrot = math.pi * 7 / 6

        abpos = apos.inverse().compose (bpos);

        assert (not CrankShape.gjk2 (a, b, abpos))

        apos.mtrans = CrankBase.VecFloat2.init (-1, 3)
        bpos.mtrans = CrankBase.VecFloat2.init (0, -2)
        apos.mrot = math.pi * 2 / 3
        bpos.mrot = 0
        apos.mscl = 0.5
        bpos.mscl = 2

        abpos = apos.inverse().compose (bpos);
        assert (CrankShape.gjk2 (a, b, abpos))


    def test_gjk_distance (self):
        a = CrankShape.Shape2CPolygon.new( [
            CrankBase.VecFloat2.init (2, 1),
            CrankBase.VecFloat2.init (-2, 1),
            CrankBase.VecFloat2.init (-3, 0),
            CrankBase.VecFloat2.init (-3, -1),
            CrankBase.VecFloat2.init (-1, -2),
            CrankBase.VecFloat2.init (2, -1)
        ] )
        b = CrankShape.Shape2CPolygon.new( [
            CrankBase.VecFloat2.init (2, 3),
            CrankBase.VecFloat2.init (1, 3),
            CrankBase.VecFloat2.init (-2, 1),
            CrankBase.VecFloat2.init (-2, -1),
            CrankBase.VecFloat2.init (-1, -2),
            CrankBase.VecFloat2.init (0, -2),
            CrankBase.VecFloat2.init (2, 0)
        ])

        apos = CrankShape.Trans2.init ();
        bpos = CrankShape.Trans2.init ();

        apos.mtrans = CrankBase.VecFloat2.init (-2, 1)
        bpos.mtrans = CrankBase.VecFloat2.init (3, 2)

        abpos = apos.inverse().compose (bpos)

        self.assertFloat (CrankShape.gjk2_distance (a, b, abpos), 1.0)


        bpos.mrot = math.pi * 7 / 12

        abpos = apos.inverse().compose (bpos);

        self.assertFloat (CrankShape.gjk2_distance (a, b, abpos), 0.0389)


        apos.mtrans = CrankBase.VecFloat2.init (-5, 3)
        bpos.mtrans = CrankBase.VecFloat2.init (0, -2)
        apos.mrot = math.pi * 2 / 3
        bpos.mrot = math.pi * 7 / 12
        apos.mscl = 0.5
        bpos.mscl = 2

        abpos = apos.inverse().compose (bpos);

        self.assertFloat (CrankShape.gjk2_distance (a, b, abpos), 1.3496)


if __name__ == '__main__':
    unittest.main ()
