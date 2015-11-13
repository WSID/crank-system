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

class TestTrans (unittest.TestCase):
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


    def test_2_translate(self):
        a = CrankShape.Trans2 ()

        a.mtrans = CrankBase.VecFloat2.init (3, 4)
        a.mrot = math.pi * 0.25
        a.mscl = 2

        trans = CrankBase.VecFloat2.init (6, 1)

        b = a.translate (trans)

        self.assertFloat (b.mtrans.x, 9)
        self.assertFloat (b.mtrans.y, 5)

        self.assertFloat (b.mrot, math.pi * 0.25)
        self.assertFloat (b.mscl, 2)

    def test_2_rotate (self):
        a = CrankShape.Trans2 ()

        a.mtrans = CrankBase.VecFloat2.init (3, 4)
        a.mrot = math.pi * 0.25
        a.mscl = 2

        b = a.rotate (math.pi * 0.25)

        self.assertFloat (b.mtrans.x, -0.7071)
        self.assertFloat (b.mtrans.y, 4.9497)

        self.assertFloat (b.mrot, math.pi * 0.25)
        self.assertFloat (b.mscl, 2)

    def test_2_scale (self):
        a = CrankShape.Trans2 ()

        a.mtrans = CrankBase.VecFloat2.init (3, 4)
        a.mrot = math.pi * 0.25
        a.mscl = 2

        b = a.scale (2)

        self.assertFloat (b.mtrans.x, 6)
        self.assertFloat (b.mtrans.y, 8)
        self.assertFloat (b.mrot, math.pi * 0.25)
        self.assertFloat (b.mscl, 4)

    def test_2_inverse (self):
        a = CrankShape.Trans2 ()

        a.mtrans = CrankBase.VecFloat2.init (3, 4)
        a.mrot = math.pi * 0.25
        a.mscl = 2

        b = a.inverse ()

        self.assertFloat (b.mtrans.x, -2.4749)
        self.assertFloat (b.mtrans.y, -0.3536)
        self.assertFloat (b.mrot, -math.pi * 0.25)
        self.assertFloat (b.mscl, 0.5)

    def test_2_compose (self):
        a = CrankShape.Trans2 ()

        a.mtrans = CrankBase.VecFloat2.init (3, 4)
        a.mrot = math.pi * 0.25
        a.mscl = 2

        b = CrankShape.Trans2 ()

        b.mtrans = CrankBase.VecFloat2.init (1, 2)
        b.mrot = math.pi * 0.5
        b.mscl = 1.5

        c = a.compose (b)

        self.assertFloat (c.mtrans.x, 1.5858)
        self.assertFloat (c.mtrans.y, 8.2426)
        self.assertFloat (c.mrot, math.pi * 0.75)
        self.assertFloat (c.mscl, 3.0)

    def test_2_transv (self):
        a = CrnakShape.Trans2 ()

        a.mtrans = CrankBase.VecFloat2.init (3, 4)
        a.mrot = math.pi * 0.25
        a.mscl = 2

        b = CrankBase.VecFloat2.init (5, 12)

        c = a.transv (b)

        self.assertFloat (c.x, -6.8995)
        self.assertFloat (c.y, 28.0416)

        
