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
    def test_gjk (self):
        a = CrankShape.Shape2CPolygon.new_from_vertices( [
            CrankBase.VecFloat2.init (2, 1),
            CrankBase.VecFloat2.init (-2, 1),
            CrankBase.VecFloat2.init (-3, 0),
            CrankBase.VecFloat2.init (-3, -1),
            CrankBase.VecFloat2.init (-1, -2),
            CrankBase.VecFloat2.init (2, -1)
        ] )
        b = CrankShape.Shape2CPolygon.new_from_vertices( [
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


if __name__ == '__main__':
    unittest.main ()
