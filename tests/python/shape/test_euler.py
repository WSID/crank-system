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

class TestEuler(unittest.TestCase):

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


	def test_from_quat (self):
		quat = CrankBase.QuatFloat.init(0.84462, 0.19134, 0.46194, 0.19134)
		euler = CrankShape.Euler.init_from_quaternion (quat)

		self.assertFloat (euler.yaw, math.pi / 4)
		self.assertFloat (euler.pitch, math.pi / 4)
		self.assertFloat (euler.roll, math.pi / 4)

	def test_from_from_mat (self):
		mat = CrankBase.MatFloat3.init(
				0.5000, -0.5000,  0.7071,
				0.8536,  0.1464, -0.5000,
				0.1464,  0.8536,  0.5000)
		euler = CrankShape.Euler.init_from_matrix3 (mat)

		self.assertFloat (euler.yaw, math.pi / 4)
		self.assertFloat (euler.pitch, math.pi / 4)
		self.assertFloat (euler.roll, math.pi / 4)

	def test_to_quat (self):
		euler = CrankShape.Euler.init_angle (math.pi / 4, math.pi / 4, math.pi / 4)
		quat = euler.to_quaternion ()

		self.assertFloat (quat.w, 0.84462)
		self.assertFloat (quat.x, 0.19134)
		self.assertFloat (quat.y, 0.46194)
		self.assertFloat (quat.z, 0.19134)

	def test_to_mat (self):
		euler = CrankShape.Euler.init_angle (math.pi / 4, math.pi / 4, math.pi / 4)
		mat = euler.to_matrix3 ()

		self.assertFloat (mat.m00,  0.5000)
		self.assertFloat (mat.m01, -0.5000)
		self.assertFloat (mat.m02, -0.7071)
		self.assertFloat (mat.m10,  0.1464)
		self.assertFloat (mat.m11,  0.8536)
		self.assertFloat (mat.m12, -0.5000)
		self.assertFloat (mat.m20,  0.8536)
		self.assertFloat (mat.m21,  0.1464)
		self.assertFloat (mat.m22,  0.5000)



if __name__ == '__main__':
	unittest.main ()
