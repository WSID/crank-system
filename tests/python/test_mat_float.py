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


from gi.repository import GObject
from gi.repository import CrankBase

class TestMatFloat(unittest.TestCase):

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

	def test_2_equal (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		b = CrankBase.MatFloat2 (1, 2,	3, 4)
		c = CrankBase.MatFloat2 (0, 0, 	0, 0)

		assert (a.equal (b))
		assert (not a.equal (c))

	def test_2_to_string (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)

		self.assertEqual (a.to_string (), "[[1, 2], [3, 4]]");

	def test_2_get (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)

		self.assertFloat (a.get (0, 0), 1)
		self.assertFloat (a.get (0, 1), 2)
		self.assertFloat (a.get (1, 0), 3)
		self.assertFloat (a.get (1, 1), 4)

	def test_2_get_row (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)

		rv = a.get_row (0)

		self.assertFloat (a.x, 1)
		self.assertFloat (a.y, 2)

		rv = a.get_row (1)

		self.assertFloat (a.x, 3)
		self.assertFloat (a.y, 4)

	def test_2_get_col (self):
		a = CrankBase.MatFloat2 (1, 2,  3, 4)

		cv = a.get_col (0)

		self.assertFloat (a.x, 1)
		self.assertFloat (a.x, 3)

		cv = a.get_col (1)

		self.assertFloat (a.x, 2)
		self.assertFloat (a.x, 4)

	def test_2_tr (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		self.assertFloat (a.get_tr (), 5)

	def test_2_det (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		self.assertFloat (a.get_det (), -2)

	def test_2_cof (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		cof = a.get_cof ();

		self.assertFloat (cof.m00, 4)
		self.assertFloat (cof.m01, -3)
		self.assertFloat (cof.m10, -2)
		self.assertFloat (cof.m11, 1)

	def test_2_adj (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		adj = a.get_cof ();

		self.assertFloat (adj.m00, 4)
		self.assertFloat (adj.m01, -2)
		self.assertFloat (adj.m10, -3)
		self.assertFloat (adj.m11, 1)

	def test_2_neg (self):
		a = CrankBase.MatFloat2 (1, 2, 	3, 4)
		a = a.neg ()

		self.assertFloat (a.m00, -1)
		self.assertFloat (a.m01, -2)
		self.assertFloat (a.m10, -3)
		self.assertFloat (a.m11, -4)

	def test_2_transpose (self):
		a = CrankBase.MatFloat2 (1, 2, 	3, 4)
		a = a.transpose ()

		self.assertFloat (a.m00, 1)
		self.assertFloat (a.m01, 3)
		self.assertFloat (a.m10, 2)
		self.assertFloat (a.m11, 4)

	def test_2_inverse (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		a = a.inverse ()

		self.assertFloat (a.m00, -2.0)
		self.assertFloat (a.m01,  1.0)
		self.assertFloat (a.m10,  1.5)
		self.assertFloat (a.m11, -0.5)

	def test_2_muls (self):
		a = CrankBase.MatFloat2 (1, 2, 	3, 4)
		a = a.muls (2)

		self.assertFloat (a.m00, 2)
		self.assertFloat (a.m01, 4)
		self.assertFloat (a.m10, 6)
		self.assertFloat (a.m11, 8)

	def test_2_divs (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		a = a.divs (2)

		self.assertFloat (a.m00, 0.5)
		self.assertFloat (a.m01, 1)
		self.assertFloat (a.m10, 1.5)
		self.assertFloat (a.m11, 2)

	def test_2_mulv (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		b = CrankBase.VecFloat2 (3, 4)
		b = a.mulv (b)

		self.assertFloat (b.x, 11)
		self.assertFloat (b.y, 25)

	def test_2_mul (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		b = CrankBase.MatFloat2 (3, 6,	9, 12)
		a = a.mul (b)

		self.assertFloat (a.m00, 21)
		self.assertFloat (a.m01, 30)
		self.assertFloat (a.m10, 45)
		self.assertFloat (a.m11, 54)

	def test_2_mixs (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		b = CrankBase.MatFloat2 (3, 6,	9, 12)
		a = a.mixs (0.5)

		self.assertFloat (a.m00, 2)
		self.assertFloat (a.m01, 4)
		self.assertFloat (a.m10, 6)
		self.assertFloat (a.m11, 8)

	def test_2_mixs (self):
		a = CrankBase.MatFloat2 (1, 2,		3, 4)
		b = CrankBase.MatFloat2 (3, 6,		9, 12)
		c = CrankBase.MatFloat2 (0, 0.25,	0.5, 0.75)
		a = a.mixs (0.5)

		self.assertFloat (a.m00, 1)
		self.assertFloat (a.m01, 3)
		self.assertFloat (a.m10, 6)
		self.assertFloat (a.m11, 12)
