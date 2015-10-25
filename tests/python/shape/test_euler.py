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
		# Test for ZYX
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 1, 0, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_ZYX )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for YXZ
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 0, 1)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_YXZ )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for XZY
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 1, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_XZY )
		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for XYZ
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 0, 1)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_XYZ )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for ZXY
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 1, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_ZXY )
		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for YZX
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 1, 0, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_YZX )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for XYX
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 1, 0, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_XYX )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for YZY
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 1, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_YZY )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for ZXZ
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 0, 1)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_ZXZ )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for YXY
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 1, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_YXY )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for ZYZ
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 0, 1)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_ZYZ )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for XZX
		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 1, 0, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		euler = CrankShape.Euler.init_from_quaternion (
				quat_res,
				CrankShape.EulerType.IN_XZX )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)


	def test_from_from_mat (self):
		# Test for ZYX
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 1, 0, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_ZYX )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for YXZ
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 0, 1)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_YXZ )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for XZY
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 1, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_XZY )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for XYZ
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 0, 1)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_XYZ )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for ZXY
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 1, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_ZXY )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for YZX
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 1, 0, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_YZX )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for XYX
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 1, 0, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_XYX )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for YZY
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 1, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_YZY )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for ZXZ
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 0, 1)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_ZXZ )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for YXY
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 1, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_YXY )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for ZYZ
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 0, 1)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_ZYZ )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)

		# Test for XZX
		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 1, 0, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

  		euler = CrankShape.Euler.init_from_matrix3 (
				mat_res,
				CrankShape.EulerType.IN_XZX )

		self.assertFloat (euler.angle1, math.pi / 4)
		self.assertFloat (euler.angle2, math.pi / 3)
		self.assertFloat (euler.angle3, math.pi / 2)


	def test_to_quat (self):
		# Test for ZYX
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_ZYX )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 1, 0, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for YXZ
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_YXZ )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 0, 1)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for XZY
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_XZY )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 1, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for XYZ
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_XYZ )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 0, 1)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for ZXY
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_ZXY )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 1, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for YZX
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_YZX )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 1, 0, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for XYX
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_XYX )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 1, 0, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for YZY
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_YZY )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 1, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for ZXZ
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_ZXZ )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 0, 1)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for YXY
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_YXY )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 1, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for ZYZ
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_ZYZ )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 1, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 0, 0, 1)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)

		# Test for XZX
		euler = CrankShape.Euler.init_angle (
				math.pi / 4, math.pi / 3, math.pi / 2,
				CrankShape.EulerType.IN_XZX )
		quat = euler.to_quaternion ()

		quat_rot = [	CrankBase.QuatFloat.init_urot(math.pi / 4, 1, 0, 0),
				CrankBase.QuatFloat.init_urot(math.pi / 3, 0, 0, 1),
				CrankBase.QuatFloat.init_urot(math.pi / 2, 1, 0, 0)	]
		quat_res = quat_rot[0].mul (quat_rot[1]).mul (quat_rot[2])

		self.assertFloat (quat.w, quat_res.w)
		self.assertFloat (quat.x, quat_res.x)
		self.assertFloat (quat.y, quat_res.y)
		self.assertFloat (quat.z, quat_res.z)


	def test_to_mat (self):
		# Test for ZYX
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_ZYX )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 1, 0, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for YXZ
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_YXZ )
		mat = euler.to_matrix3 ()

		print (euler.angle1, euler.angle2, euler.angle3, euler.etype)

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 0, 1)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for XZY
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_XZY )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 1, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for XYZ
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_XYZ )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 0, 1)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for ZXY
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_ZXY )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 1, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for YZX
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_YZX )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 1, 0, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for XYX
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_XYX )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 1, 0, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for YZY
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_YZY )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 1, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for ZXZ
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_ZXZ )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 0, 1)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for YXY
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_YXY )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 1, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for ZYZ
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_ZYZ )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 1, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 0, 0, 1)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

		# Test for XZX
		euler = CrankShape.Euler.init_angle (
				math.pi / 4,
				math.pi / 3,
				math.pi / 2,
				CrankShape.EulerType.IN_XZX )
		mat = euler.to_matrix3 ()

		mat_rot = [	CrankBase.MatFloat3.init_urot (math.pi / 4, 1, 0, 0),
				CrankBase.MatFloat3.init_urot (math.pi / 3, 0, 0, 1),
				CrankBase.MatFloat3.init_urot (math.pi / 2, 1, 0, 0)	]
		mat_res = mat_rot[0].mul (mat_rot[1]).mul (mat_rot[2])

		self.assertFloat (mat.m00, mat_res.m00)
		self.assertFloat (mat.m01, mat_res.m01)
		self.assertFloat (mat.m02, mat_res.m02)
		self.assertFloat (mat.m10, mat_res.m10)
		self.assertFloat (mat.m11, mat_res.m11)
		self.assertFloat (mat.m12, mat_res.m12)
		self.assertFloat (mat.m20, mat_res.m20)
		self.assertFloat (mat.m21, mat_res.m21)
		self.assertFloat (mat.m22, mat_res.m22)

if __name__ == '__main__':
	unittest.main ()
