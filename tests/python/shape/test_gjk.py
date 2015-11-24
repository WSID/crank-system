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

        apos = CrankBase.VecFloat2.init (-2, 1)
        bpos = CrankBase.VecFloat2.init (3, 2)

        a.props.pos_trans = apos;
        b.props.pos_trans = bpos;

        assert (not CrankShape.gjk2 (a, b, None))


        b.props.pos_rot = math.pi * 7 / 6

        assert (not CrankShape.gjk2 (a, b, None))


        apos.x = -1
        apos.y = 3
        bpos.x = 0
        bpos.y = -2

        a.props.pos_trans = apos
        b.props.pos_trans = bpos
        a.props.pos_rot = math.pi * 2 / 3
        b.props.pos_rot = 0
        a.props.pos_scl = 0.5
        b.props.pos_scl = 2

        assert (CrankShape.gjk2 (a, b, None))


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

        apos = CrankBase.VecFloat2.init (-2, 1)
        bpos = CrankBase.VecFloat2.init (3, 2)

        a.props.pos_trans = apos;
        b.props.pos_trans = bpos;

        self.assertFloat (CrankShape.gjk2_distance (a, b, None), 1.0)


        b.props.pos_rot = math.pi * 7 / 12

        self.assertFloat (CrankShape.gjk2_distance (a, b, None), 0.0389)


        apos.x = -5
        apos.y = 3
        bpos.x = 0
        bpos.y = -2

        a.props.pos_trans = apos
        b.props.pos_trans = bpos
        a.props.pos_rot = math.pi * 2 / 3
        b.props.pos_rot = math.pi * 7 / 12
        a.props.pos_scl = 0.5
        b.props.pos_scl = 2

        self.assertFloat (CrankShape.gjk2_distance (a, b, None), 1.3496)


if __name__ == '__main__':
    unittest.main ()
