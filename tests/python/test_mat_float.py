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

	def test_2_add (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		b = CrankBase.MatFloat2 (3, 6,	9, 12)
		a = a.add (b)

		self.assertFloat (a.m00, 4)
		self.assertFloat (a.m01, 8)
		self.assertFloat (a.m10, 12)
		self.assertFloat (a.m11, 16)

	def test_2_sub (self):
		a = CrankBase.MatFloat2 (1, 2,	3, 4)
		b = CrankBase.MatFloat2 (3, 6,	9, 12)
		a = a.sub (b)

		self.assertFloat (a.m00, -2)
		self.assertFloat (a.m01, -4)
		self.assertFloat (a.m10, -6)
		self.assertFloat (a.m11, -8)

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
		
	def test_n_equal (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
		b = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
		c = CrankBase.MatFloatN.init_arr (3, 2,
				[1, 2,
				 3, 4,
				 5, 6])
		
		assert (a.equal (b))
		assert (not a.equal (c))
		
	def test_n_to_string (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])

		self.assertEqual (a.to_string (), "[[1, 2, 3], [4, 5, 6]]")
		
	def test_n_get (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])

		self.assertFloat(a.get (0,0), 1)
		self.assertFloat(a.get (0,1), 2)
		self.assertFloat(a.get (0,2), 3)
		self.assertFloat(a.get (1,0), 4)
		self.assertFloat(a.get (1,1), 5)
		self.assertFloat(a.get (1,2), 6)
		
	def test_n_get_row (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])

		rv = a.get_row (0)
		self.assertFloat (rv.get(0), 1)
		self.assertFloat (rv.get(1), 2)
		self.assertFloat (rv.get(2), 3)
		
		rv = a.get_row (1)
		self.assertFloat (rv.get(0), 4)
		self.assertFloat (rv.get(1), 5)
		self.assertFloat (rv.get(2), 6)
		
	def test_n_get_col (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])

		cv = a.get_col (0)
		self.assertFloat (cv.get(0), 1)
		self.assertFloat (cv.get(1), 4)
		
		cv = a.get_col (1)
		self.assertFloat (cv.get(0), 2)
		self.assertFloat (cv.get(1), 5)
		
		cv = a.get_col (2)
		self.assertFloat (cv.get(0), 3)
		self.assertFloat (cv.get(1), 6)
	
	def test_n_tr (self):
		a = CrankBase.MatFloatN.init_arr (5, 5,
				[1, 0, 0, 1, 0,
				 0, 2, 0, 3, 1,
				 0, 0, 3, 0, 0,
				 1, 3, 0, 4, 0,
				 0, 1, 0, 0, 5]);

		self.assertFloat (a.get_tr (), 15);
	
	@unittest.skip ("Determinent for variable size matrix is in progress.")
	def test_n_det (self):
		pass
	
	@unittest.skip ("Determinent for variable size matrix is in progress.")
	def test_n_cof (self):
		pass
	
	@unittest.skip ("Determinent for variable size matrix is in progress.")
	def test_n_adj (self):
		pass
	
		
	def test_n_neg (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
		
		a = a.neg ()
		
		self.assertFloat(a.get (0, 0), -1)
		self.assertFloat(a.get (0, 1), -2)
		self.assertFloat(a.get (0, 2), -3)
		self.assertFloat(a.get (1, 0), -4)
		self.assertFloat(a.get (1, 1), -5)
		self.assertFloat(a.get (1, 2), -6)
		
	def test_n_transpose (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
		
		a = a.transpose ()
		
		self.assertEqual (a.get_row_size(), 3)
		self.assertEqual (a.get_col_size(), 2)
		self.assertFloat(a.get (0, 0), 1)
		self.assertFloat(a.get (0, 1), 4)
		self.assertFloat(a.get (1, 0), 2)
		self.assertFloat(a.get (1, 1), 5)
		self.assertFloat(a.get (2, 0), 3)
		self.assertFloat(a.get (2, 1), 6)
		
	@unittest.skip ("Determinent for variable size matrix is in progress.")
	def test_n_inverse (self):
		pass
	
	def test_n_muls (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
		
		a = a.muls (3)
		
		self.assertFloat(a.get (0, 0), 3)
		self.assertFloat(a.get (0, 1), 6)
		self.assertFloat(a.get (0, 2), 9)
		self.assertFloat(a.get (1, 0), 12)
		self.assertFloat(a.get (1, 1), 15)
		self.assertFloat(a.get (1, 2), 18)
	
	def test_n_divs (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
		
		a = a.divs (2)
		
		self.assertFloat(a.get (0, 0), 0.5)
		self.assertFloat(a.get (0, 1), 1.0)
		self.assertFloat(a.get (0, 2), 1.5)
		self.assertFloat(a.get (1, 0), 2.0)
		self.assertFloat(a.get (1, 1), 2.5)
		self.assertFloat(a.get (1, 2), 3.0)
		
	def test_n_mulv (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
		
		b = CrankBase.MatFloatN.init_arr (3, [2, 3, 5])
		
		b = a.mulv (b)
		
		self.assertFloat(b.get(0), 23)
		self.assertFloat(b.get(1), 53)
		
	def test_n_add (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])

		b = CrankBase.MatFloatN.init_arr (2, 3,
				[3, 2, 1,
				 2, 1, 0])

		a = a.add (b)

		self.assertFloat (a.get (0, 0), 4)
		self.assertFloat (a.get (0, 1), 4)
		self.assertFloat (a.get (0, 2), 4)
		self.assertFloat (a.get (1, 0), 6)
		self.assertFloat (a.get (1, 1), 6)
		self.assertFloat (a.get (1, 2), 6)

	def test_n_sub (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
				 
		b = CrankBase.MatFloatN.init_arr (2, 3,
				[3, 2, 1,
				 2, 1, 0])

		a = a.sub (b)

		self.assertFloat (a.get (0, 0), -2)
		self.assertFloat (a.get (0, 1), 0)
		self.assertFloat (a.get (0, 2), -2)
		self.assertFloat (a.get (1, 0), 2)
		self.assertFloat (a.get (1, 1), 4)
		self.assertFloat (a.get (1, 2), 6)

	def test_n_mul (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])

		b = CrankBase.MatFloatN.init_arr (3, 3,
				[3, 2, 1,
				 2, 1, 0,
				 1, 0, -1])

		a = a.mul (b)
		
		self.assertEqual (a.get_row_size(), 2)
		self.assertEqual (a.get_col_size(), 3)
		self.assertFloat (a.get (0, 0), 10)
		self.assertFloat (a.get (0, 1), 4)
		self.assertFloat (a.get (0, 2), -2)
		self.assertFloat (a.get (1, 0), 28)
		self.assertFloat (a.get (1, 1), 13)
		self.assertFloat (a.get (1, 2), -2)
	
	def test_n_mixs (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
				 
		b = CrankBase.MatFloatN.init_arr (2, 3,
				[3, 6, 9,
				 12, 15, 18])

		a = a.mixs (b, 0.5)
		
		self.assertFloat (a.get (0, 0), 2)
		self.assertFloat (a.get (0, 1), 4)
		self.assertFloat (a.get (0, 2), 6)
		self.assertFloat (a.get (1, 0), 8)
		self.assertFloat (a.get (1, 1), 10)
		self.assertFloat (a.get (1, 2), 12)
	
	def test_n_mix (self):
		a = CrankBase.MatFloatN.init_arr (2, 3,
				[1, 2, 3,
				 4, 5, 6])
				 
		b = CrankBase.MatFloatN.init_arr (2, 3,
				[3, 6, 9,
				 12, 15, 18])
				 
		c = CrankBase.MatFloatN.init_arr (2, 3,
				[0.0, 0.2, 0.4,
				 0.6, 0.8, 1.0])

		a = a.mix (b, c)
		
		self.assertFloat (a.get (0, 0), 1.0)
		self.assertFloat (a.get (0, 1), 2.4)
		self.assertFloat (a.get (0, 2), 5.4)
		self.assertFloat (a.get (1, 0), 8.8)
		self.assertFloat (a.get (1, 1), 13.0)
		self.assertFloat (a.get (1, 2), 18.0)

	def test_n_shuffle_row (self):
		a = CrankBase.MatFloatN.init_arr (4, 2,
				[1, 3,
				 7, 2,
				 1, 4,
				 3, 1])
		p = CrankBase.Permutation.init_arr ([1, 3, 0, 2])
		
		a = a.shuffle_row (p)
		
		self.assertFloat (a.get (0, 0), 7)
		self.assertFloat (a.get (0, 1), 2)
		self.assertFloat (a.get (1, 0), 3)
		self.assertFloat (a.get (1, 1), 1)
		self.assertFloat (a.get (2, 0), 1)
		self.assertFloat (a.get (2, 1), 3)
		self.assertFloat (a.get (3, 0), 1)
		self.assertFloat (a.get (3, 1), 4)
		
	def test_n_shuffle_col (self):
		a = CrankBase.MatFloatN.init_arr (2, 4,
				[1, 7, 1, 3,
				 3, 2, 4, 1])
		p = CrankBase.Permutation.init_arr ([1, 3, 0, 2])
		
		a = a.shuffle_col (p)
		
		self.assertFloat (a.get (0, 0), 7)
		self.assertFloat (a.get (0, 1), 3)
		self.assertFloat (a.get (0, 2), 1)
		self.assertFloat (a.get (0, 3), 1)
		self.assertFloat (a.get (1, 0), 2)
		self.assertFloat (a.get (1, 1), 1)
		self.assertFloat (a.get (1, 2), 3)
		self.assertFloat (a.get (1, 3), 4)
