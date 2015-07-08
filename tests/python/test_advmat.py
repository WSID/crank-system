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

class TestAdvMat(unittest.TestCase):

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


	def test_lu (self):
		a = CrankBase.MatFloatN.init_arr (3, 3, [
				3,	12,	21,
				8,	39,	84,
				2,	16,	49	])
				
		(r, l, u) = CrankBase.lu_mat_float_n (a)
		
		assert (r)
		
		self.assertFloat (l.get (0, 0), 3)
		self.assertFloat (l.get (0, 1), 0)
		self.assertFloat (l.get (0, 2), 0)
		self.assertFloat (l.get (1, 0), 8)
		self.assertFloat (l.get (1, 1), 7)
		self.assertFloat (l.get (1, 2), 0)
		self.assertFloat (l.get (2, 0), 2)
		self.assertFloat (l.get (2, 1), 8)
		self.assertFloat (l.get (2, 2), 3)
		
		self.assertFloat (u.get (0, 0), 1)
		self.assertFloat (u.get (0, 1), 4)
		self.assertFloat (u.get (0, 2), 7)
		self.assertFloat (u.get (1, 0), 0)
		self.assertFloat (u.get (1, 1), 1)
		self.assertFloat (u.get (1, 2), 4)
		self.assertFloat (u.get (2, 0), 0)
		self.assertFloat (u.get (2, 1), 0)
		self.assertFloat (u.get (2, 2), 1)


	def test_lu_p (self):
		a = CrankBase.MatFloatN.init_arr (3, 3, [
				0,	4,	3,
				3,	6,	6,
				2,	20,	8	])
				
		(r, p, l, u) = CrankBase.lu_p_mat_float_n (a)
		
		assert (r)
		
		self.assertEqual (p.get (0), 1)
		self.assertEqual (p.get (1), 2)
		self.assertEqual (p.get (2), 0)
		
		self.assertFloat (l.get (0, 0), 3)
		self.assertFloat (l.get (0, 1), 0)
		self.assertFloat (l.get (0, 2), 0)
		self.assertFloat (l.get (1, 0), 2)
		self.assertFloat (l.get (1, 1), 16)
		self.assertFloat (l.get (1, 2), 0)
		self.assertFloat (l.get (2, 0), 0)
		self.assertFloat (l.get (2, 1), 4)
		self.assertFloat (l.get (2, 2), 2)
		
		self.assertFloat (u.get (0, 0), 1)
		self.assertFloat (u.get (0, 1), 2)
		self.assertFloat (u.get (0, 2), 2)
		self.assertFloat (u.get (1, 0), 0)
		self.assertFloat (u.get (1, 1), 1)
		self.assertFloat (u.get (1, 2), 0.25)
		self.assertFloat (u.get (2, 0), 0)
		self.assertFloat (u.get (2, 1), 0)
		self.assertFloat (u.get (2, 2), 1)


if __name__ == '__main__':
	unittest.main ()
