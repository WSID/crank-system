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


class TestMatCplxFloatN(unittest.TestCase):

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


	def test_equal (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])
			
		b = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])

		c = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (4, 5),
			CrankBase.CplxFloat.init (6, 7)  ])
		
		assert (a.equal (b))
		assert (not a.equal (c))
	
	def test_to_string (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (4, 5),
			CrankBase.CplxFloat.init (6, 7)  ])
		
		self.assertEqual (a.to_string (), "[[1 + (2i), 3 + (4i)], [4 + (5i), 6 + (7i)]]");
		
	def test_get (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])

		v = a.get (0, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 2)
		
		v = a.get (0, 1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 4)
		
		v = a.get (1, 0)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 6)

		v = a.get (1, 1)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 8)
	
	def test_get_row (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])
		
		r = a.get_row (0)
		
		self.assertEqual (r.get_size (), 2)
		
		v = r.get (0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 2)
		
		v = r.get (1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 4)
		
		r = a.get_row (1)
		
		self.assertEqual (r.get_size (), 2)
		
		v = r.get (0)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 6)
		
		v = r.get (1)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 8)
	
	def test_get_col (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])
		
		r = a.get_col (0)
		
		self.assertEqual (r.get_size (), 2)
		
		v = r.get (0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 2)
		
		v = r.get (1)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 6)
		
		r = a.get_col (1)
		
		self.assertEqual (r.get_size (), 2)
		
		v = r.get (0)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 4)
		
		v = r.get (1)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 8)
	
	
	def test_slice (self):
		a = CrankBase.MatCplxFloatN.init_arr (3, 3, [
			CrankBase.CplxFloat.init (1, 1.5),
			CrankBase.CplxFloat.init (2, 2.5),
			CrankBase.CplxFloat.init (3, 4.5),
			CrankBase.CplxFloat.init (4, 4.5),
			CrankBase.CplxFloat.init (5, 5.5),
			CrankBase.CplxFloat.init (6, 6.5),
			CrankBase.CplxFloat.init (7, 3.5),
			CrankBase.CplxFloat.init (8, 4.0),
			CrankBase.CplxFloat.init (9, 4.5)  ])
		
		b = a.slice (1, 1, 3, 2)
	
		v = b.get (0, 0);
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 5.5)

		v = b.get (1, 0);
		self.assertFloat (v.real, 8)
		self.assertFloat (v.imag, 4)

	def test_tr (self):
		a = CrankBase.MatCplxFloatN.init_arr (3, 3, [
			CrankBase.CplxFloat.init (1, 1.5),
			CrankBase.CplxFloat.init (2, 2.5),
			CrankBase.CplxFloat.init (3, 4.5),
			CrankBase.CplxFloat.init (4, 4.5),
			CrankBase.CplxFloat.init (5, 5.5),
			CrankBase.CplxFloat.init (6, 6.5),
			CrankBase.CplxFloat.init (7, 3.5),
			CrankBase.CplxFloat.init (8, 4.0),
			CrankBase.CplxFloat.init (9, 4.5)  ])
			
		v = a.get_tr ();
		
		self.assertFloat (v.real, 15)
		self.assertFloat (v.imag, 11.5)
		
	def test_det (self):
		a = CrankBase.MatCplxFloatN.init_arr (3, 3, [
			CrankBase.CplxFloat.init (1, 1.5),
			CrankBase.CplxFloat.init (2, 2.5),
			CrankBase.CplxFloat.init (3, 4.5),
			CrankBase.CplxFloat.init (4, 4.5),
			CrankBase.CplxFloat.init (5, 5.5),
			CrankBase.CplxFloat.init (6, 6.5),
			CrankBase.CplxFloat.init (7, 3.5),
			CrankBase.CplxFloat.init (8, 4.0),
			CrankBase.CplxFloat.init (9, 4.5)  ])

		v = a.get_det ();
		
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, -1.75)
		
	def test_cof (self):
		a = CrankBase.MatCplxFloatN.init_arr (3, 3, [
			CrankBase.CplxFloat.init (1, 1.5),
			CrankBase.CplxFloat.init (2, 2.5),
			CrankBase.CplxFloat.init (3, 4.5),
			CrankBase.CplxFloat.init (4, 4.5),
			CrankBase.CplxFloat.init (5, 5.5),
			CrankBase.CplxFloat.init (6, 6.5),
			CrankBase.CplxFloat.init (7, 3.5),
			CrankBase.CplxFloat.init (8, 4.0),
			CrankBase.CplxFloat.init (9, 4.5)  ])

		cof = a.get_cof ();
		
		v = cof.get (0, 0)
		self.assertFloat (v.real, -1.7500)
		self.assertFloat (v.imag, -4.0000)
		v = cof.get (0, 1)
		self.assertFloat (v.real,  3.5000)
		self.assertFloat (v.imag,  8.0000)
		v = cof.get (0, 2)
		self.assertFloat (v.real, -1.7500)
		self.assertFloat (v.imag, -4.0000)
		v = cof.get (1, 2)
		self.assertFloat (v.real,  3.2500)
		self.assertFloat (v.imag,  8.5000)
		v = cof.get (2, 2)
		self.assertFloat (v.real,  0.0000)
		self.assertFloat (v.imag, -6.0000)


	def test_adj (self):
		a = CrankBase.MatCplxFloatN.init_arr (3, 3, [
			CrankBase.CplxFloat.init (1, 1.5),
			CrankBase.CplxFloat.init (2, 2.5),
			CrankBase.CplxFloat.init (3, 4.5),
			CrankBase.CplxFloat.init (4, 4.5),
			CrankBase.CplxFloat.init (5, 5.5),
			CrankBase.CplxFloat.init (6, 6.5),
			CrankBase.CplxFloat.init (7, 3.5),
			CrankBase.CplxFloat.init (8, 4.0),
			CrankBase.CplxFloat.init (9, 4.5)  ])

		adj = a.get_adj ();
		
		v = adj.get (0, 0)
		self.assertFloat (v.real, -1.7500)
		self.assertFloat (v.imag, -4.0000)
		v = adj.get (0, 1)
		self.assertFloat (v.real, -0.7500)
		self.assertFloat (v.imag, 16.5000)
		v = adj.get (0, 2)
		self.assertFloat (v.real,  5.5000)
		self.assertFloat (v.imag,-11.0000)
		v = adj.get (1, 2)
		self.assertFloat (v.real, -4.5000)
		self.assertFloat (v.imag, 16.0000)
		v = adj.get (2, 2)
		self.assertFloat (v.real,  0.0000)
		self.assertFloat (v.imag, -6.0000)

	def test_diag (self):
		a = CrankBase.MatCplxFloatN.init_arr (3, 3, [
			CrankBase.CplxFloat.init (1, 1.5),
			CrankBase.CplxFloat.init (2, 2.5),
			CrankBase.CplxFloat.init (3, 4.5),
			CrankBase.CplxFloat.init (4, 4.5),
			CrankBase.CplxFloat.init (5, 5.5),
			CrankBase.CplxFloat.init (6, 6.5),
			CrankBase.CplxFloat.init (7, 3.5),
			CrankBase.CplxFloat.init (8, 4.0),
			CrankBase.CplxFloat.init (9, 4.5)  ])
		
		b = a.get_diag ()
		
		v = b.get (0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 1.5)
		
		v = b.get (1)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 5.5)
		
		v = b.get (2)
		self.assertFloat (v.real, 9)
		self.assertFloat (v.imag, 4.5)
		
	
	def test_neg (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])
		
		b = a.neg ()
		
		v = b.get (0, 0)
		self.assertFloat (v.real, -1)
		self.assertFloat (v.imag, -2)
		v = b.get (0, 1)
		self.assertFloat (v.real, -3)
		self.assertFloat (v.imag, -4)
		v = b.get (1, 0)
		self.assertFloat (v.real, -5)
		self.assertFloat (v.imag, -6)
		v = b.get (1, 1)
		self.assertFloat (v.real, -7)
		self.assertFloat (v.imag, -8)

	def test_transpose (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 3, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8),
			CrankBase.CplxFloat.init (9, 10),
			CrankBase.CplxFloat.init (11, 12)  ])
		
		b = a.transpose ()
		
		self.assertEqual(b.get_row_size (), 3)
		self.assertEqual(b.get_col_size (), 2)
		
		v = b.get (0, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 2)
		v = b.get (0, 1)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 8)
		v = b.get (1, 0)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 4)
		v = b.get (1, 1)
		self.assertFloat (v.real, 9)
		self.assertFloat (v.imag, 10)
		v = b.get (2, 0)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 6)
		v = b.get (2, 1)
		self.assertFloat (v.real, 11)
		self.assertFloat (v.imag, 12)

	def test_inverse (self):
		a = CrankBase.MatCplxFloatN.init_arr (3, 3, [
			CrankBase.CplxFloat.init (1, 1.5),
			CrankBase.CplxFloat.init (2, 2.5),
			CrankBase.CplxFloat.init (3, 4.5),
			CrankBase.CplxFloat.init (4, 4.5),
			CrankBase.CplxFloat.init (5, 5.5),
			CrankBase.CplxFloat.init (6, 6.5),
			CrankBase.CplxFloat.init (7, 3.5),
			CrankBase.CplxFloat.init (8, 4.0),
			CrankBase.CplxFloat.init (9, 4.5)  ])
			
		b = a.inverse ()
		
		v = b.get (0, 0)
		self.assertFloat (v.real,   0.0000)
		self.assertFloat (v.imag, - 1.0000)
		v = b.get (0, 1)
		self.assertFloat (v.real, - 1.6721)
		self.assertFloat (v.imag,   3.3934)
		v = b.get (0, 2)
		self.assertFloat (v.real,   2.1639)
		self.assertFloat (v.imag, - 1.8033)
		v = b.get (1, 0)
		self.assertFloat (v.real,   0.0000)
		self.assertFloat (v.imag,   2.0000)
		v = b.get (1, 1)
		self.assertFloat (v.real,   1.5738)
		self.assertFloat (v.imag, - 5.3115)
		v = b.get (1, 2)
		self.assertFloat (v.real, - 2.4131)
		self.assertFloat (v.imag,   2.9443)
		v = b.get (2, 0)
		self.assertFloat (v.real,   0.0000)
		self.assertFloat (v.imag, - 1.0000)
		v = b.get (2, 1)
		self.assertFloat (v.real, - 0.0984)
		self.assertFloat (v.imag,   2.0820)
		v = b.get (2, 2)
		self.assertFloat (v.real,   0.5508)
		self.assertFloat (v.imag, - 1.2590)

	def test_mulrs (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])
		
		b = a.mulrs (2)
		
		v = b.get (0, 0)
		self.assertFloat (v.real, 2)
		self.assertFloat (v.imag, 4)
		v = b.get (0, 1)
		self.assertFloat (v.real, 6)
		self.assertFloat (v.imag, 8)
		v = b.get (1, 0)
		self.assertFloat (v.real, 10)
		self.assertFloat (v.imag, 12)
		v = b.get (1, 1)
		self.assertFloat (v.real, 14)
		self.assertFloat (v.imag, 16)
		
	def test_divrs (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])
		
		b = a.divrs (2)
		
		v = b.get (0, 0)
		self.assertFloat (v.real, 0.5)
		self.assertFloat (v.imag, 1)
		v = b.get (0, 1)
		self.assertFloat (v.real, 1.5)
		self.assertFloat (v.imag, 2)
		v = b.get (1, 0)
		self.assertFloat (v.real, 2.5)
		self.assertFloat (v.imag, 3)
		v = b.get (1, 1)
		self.assertFloat (v.real, 3.5)
		self.assertFloat (v.imag, 4)
		
	def test_mulv (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (4, 5),
			CrankBase.CplxFloat.init (6, 7)  ])
		
		b = CrankBase.VecCplxFloatN.init_arr ([
			CrankBase.CplxFloat.init (2, 3),
			CrankBase.CplxFloat.init (5, 7)	])
		
		c = a.mulv (b)
		
		v = c.get (0)
		self.assertFloat (v.real, -17)
		self.assertFloat (v.imag,  48)
		v = c.get (1)
		self.assertFloat (v.real, -26)
		self.assertFloat (v.imag,  99)
	
	def test_add (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])

		b = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (2, 3),
			CrankBase.CplxFloat.init (5, 7),
			CrankBase.CplxFloat.init (4, 2),
			CrankBase.CplxFloat.init (1, 3)  ])
		
		c = a.add (b)
		
		v = c.get (0, 0)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 5)
		v = c.get (0, 1)
		self.assertFloat (v.real, 8)
		self.assertFloat (v.imag, 11)
		v = c.get (1, 0)
		self.assertFloat (v.real, 9)
		self.assertFloat (v.imag, 8)
		v = c.get (1, 1)
		self.assertFloat (v.real, 8)
		self.assertFloat (v.imag, 11)
	
	def test_sub (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (5, 6),
			CrankBase.CplxFloat.init (7, 8)  ])

		b = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (2, 3),
			CrankBase.CplxFloat.init (5, 7),
			CrankBase.CplxFloat.init (4, 2),
			CrankBase.CplxFloat.init (1, 3)  ])
		
		c = a.sub (b)
		
		v = c.get (0, 0)
		self.assertFloat (v.real, -1)
		self.assertFloat (v.imag, -1)
		v = c.get (0, 1)
		self.assertFloat (v.real, -2)
		self.assertFloat (v.imag, -3)
		v = c.get (1, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 4)
		v = c.get (1, 1)
		self.assertFloat (v.real, 6)
		self.assertFloat (v.imag, 5)
	
	def test_mul (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (4, 5),
			CrankBase.CplxFloat.init (6, 7)  ])

		b = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (2, 3),
			CrankBase.CplxFloat.init (5, 7),
			CrankBase.CplxFloat.init (4, 2),
			CrankBase.CplxFloat.init (1, 3)  ])
		
		c = a.mul (b)
		
		v = c.get (0, 0)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 29)
		v = c.get (0, 1)
		self.assertFloat (v.real, -18)
		self.assertFloat (v.imag, 30)
		v = c.get (1, 0)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 62)
		v = c.get (1, 1)
		self.assertFloat (v.real, -30)
		self.assertFloat (v.imag, 78)
		
	def test_mixs (self):
		a = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (1, 2),
			CrankBase.CplxFloat.init (3, 4),
			CrankBase.CplxFloat.init (4, 5),
			CrankBase.CplxFloat.init (6, 7)  ])

		b = CrankBase.MatCplxFloatN.init_arr (2, 2, [
			CrankBase.CplxFloat.init (2, 3),
			CrankBase.CplxFloat.init (5, 7),
			CrankBase.CplxFloat.init (4, 2),
			CrankBase.CplxFloat.init (1, 3)  ])
		
		c = a.mixs (b, 0.5)
		
		v = c.get (0, 0)
		self.assertFloat (v.real, 1.5)
		self.assertFloat (v.imag, 2.5)
		v = c.get (0, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 5.5)
		v = c.get (1, 0)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 3.5)
		v = c.get (1, 1)
		self.assertFloat (v.real, 3.5)
		self.assertFloat (v.imag, 5)
	
	def test_shuffle_row (self):
		a = CrankBase.MatCplxFloatN.init_arr(4, 1, [
			CrankBase.CplxFloat.init (1, 3),
			CrankBase.CplxFloat.init (7, 2),
			CrankBase.CplxFloat.init (1, 4),
			CrankBase.CplxFloat.init (3, 1)	])

		p = CrankBase.Permutation.init_arr ([1, 3, 0, 2])
		
		c = a.shuffle_row (p)
		
		v = c.get (0, 0)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 2)
		v = c.get (1, 0)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 1)
		v = c.get (2, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 3)
		v = c.get (3, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 4)
		
	def test_shuffle_col (self):
		a = CrankBase.MatCplxFloatN.init_arr(1, 4, [
			CrankBase.CplxFloat.init (1, 7),
			CrankBase.CplxFloat.init (1, 3),
			CrankBase.CplxFloat.init (3, 2),
			CrankBase.CplxFloat.init (4, 1)	])

		p = CrankBase.Permutation.init_arr ([1, 3, 0, 2])
		
		c = a.shuffle_col (p)
		
		v = c.get (0, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 3)
		v = c.get (0, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 1)
		v = c.get (0, 2)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 7)
		v = c.get (0, 3)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 2)
	
	def test_init_ucarr (self):
		a = CrankBase.MatCplxFloatN.init_ucarr (2, 3,
			[2, 3, 5,
			 1, 4, 7],
			[8, 9, 2,
			 0, 3, 0] )
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 2)
		self.assertFloat (v.imag, 8)
		v = a.get (0, 1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 9)
		v = a.get (0, 2)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 2)
		v = a.get (1, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 3)
		v = a.get (1, 2)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 0)
	
	def test_init_arruc (self):
		a = CrankBase.MatCplxFloatN.init_arruc (2, 3,
			[2, 8,	3, 9,	5, 2,
			 1, 0,	4, 3,	7, 0] )
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 2)
		self.assertFloat (v.imag, 8)
		v = a.get (0, 1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 9)
		v = a.get (0, 2)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 2)
		v = a.get (1, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 3)
		v = a.get (1, 2)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 0)
	
	def test_init_ucm (self):
		a = CrankBase.MatCplxFloatN.init_ucm (
			CrankBase.MatFloatN.init_arr (2, 3,	[2, 3, 5,
												 1, 4, 7] ),
												 
			CrankBase.MatFloatN.init_arr (2, 3, [8, 9, 2,
												 0, 3, 0] ) )
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 2)
		self.assertFloat (v.imag, 8)
		v = a.get (0, 1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 9)
		v = a.get (0, 2)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 2)
		v = a.get (1, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 3)
		v = a.get (1, 2)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 0)
	
	def test_init_row_arruc (self):
		a = CrankBase.MatCplxFloatN.init_row_arruc (2, 
				[CrankBase.VecFloatN.init_arr ([2, 3, 5]),
				 CrankBase.VecFloatN.init_arr ([8, 9, 2]),
				 
				 CrankBase.VecFloatN.init_arr ([1, 4, 7]),
				 CrankBase.VecFloatN.init_arr ([0, 3, 0])] )
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 2)
		self.assertFloat (v.imag, 8)
		v = a.get (0, 1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 9)
		v = a.get (0, 2)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 2)
		v = a.get (1, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 3)
		v = a.get (1, 2)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 0)
	
	def test_init_row_parruc (self):
		a = CrankBase.MatCplxFloatN.init_row_parruc (2, 
				[CrankBase.VecFloatN.init_arr ([2, 3, 5]),
				 CrankBase.VecFloatN.init_arr ([8, 9, 2]),
				 
				 CrankBase.VecFloatN.init_arr ([1, 4, 7]),
				 CrankBase.VecFloatN.init_arr ([0, 3, 0])] )
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 2)
		self.assertFloat (v.imag, 8)
		v = a.get (0, 1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 9)
		v = a.get (0, 2)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 2)
		v = a.get (1, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 3)
		v = a.get (1, 2)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 0)
		
	
	def test_init_col_arruc (self):
		a = CrankBase.MatCplxFloatN.init_col_arruc (3, 
				[CrankBase.VecFloatN.init_arr ([2, 1]),
				 CrankBase.VecFloatN.init_arr ([8, 0]),
				 
				 CrankBase.VecFloatN.init_arr ([3, 4]),
				 CrankBase.VecFloatN.init_arr ([9, 3]),
				 
				 CrankBase.VecFloatN.init_arr ([5, 7]),
				 CrankBase.VecFloatN.init_arr ([2, 0])] )
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 2)
		self.assertFloat (v.imag, 8)
		v = a.get (0, 1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 9)
		v = a.get (0, 2)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 2)
		v = a.get (1, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 3)
		v = a.get (1, 2)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 0)
	
	def test_init_col_parruc (self):
		a = CrankBase.MatCplxFloatN.init_col_parruc (3, 
				[CrankBase.VecFloatN.init_arr ([2, 1]),
				 CrankBase.VecFloatN.init_arr ([8, 0]),
				 
				 CrankBase.VecFloatN.init_arr ([3, 4]),
				 CrankBase.VecFloatN.init_arr ([9, 3]),
				 
				 CrankBase.VecFloatN.init_arr ([5, 7]),
				 CrankBase.VecFloatN.init_arr ([2, 0])] )
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 2)
		self.assertFloat (v.imag, 8)
		v = a.get (0, 1)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 9)
		v = a.get (0, 2)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 2)
		v = a.get (1, 0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 4)
		self.assertFloat (v.imag, 3)
		v = a.get (1, 2)
		self.assertFloat (v.real, 7)
		self.assertFloat (v.imag, 0)
	
	def test_init_diag_arruc (self):
		a = CrankBase.MatCplxFloatN.init_diag_arruc (3,
				[1.0, 1.5,	 3.0, 2.0,	 4.5, 3.5])
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 1.0)
		self.assertFloat (v.imag, 1.5)
		v = a.get (0, 1)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (0, 2)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 0)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 3.0)
		self.assertFloat (v.imag, 2.0)
		v = a.get (1, 2)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 0)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 1)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 2)
		self.assertFloat (v.real, 4.5)
		self.assertFloat (v.imag, 3.5)
	
	def test_init_diag_ucarr (self):
		a = CrankBase.MatCplxFloatN.init_diag_ucarr (
				[1.0, 3.0, 4.5], [1.5, 2.0, 3.5])
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 1.0)
		self.assertFloat (v.imag, 1.5)
		v = a.get (0, 1)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (0, 2)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 0)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 3.0)
		self.assertFloat (v.imag, 2.0)
		v = a.get (1, 2)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 0)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 1)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 2)
		self.assertFloat (v.real, 4.5)
		self.assertFloat (v.imag, 3.5)
	
	def test_init_diag_ucv (self):
		a = CrankBase.MatCplxFloatN.init_diag_ucv (
				CrankBase.VecFloatN.init_arr ([1.0, 3.0, 4.5]),
				CrankBase.VecFloatN.init_arr ([1.5, 2.0, 3.5]) )
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 1.0)
		self.assertFloat (v.imag, 1.5)
		v = a.get (0, 1)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (0, 2)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 0)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 3.0)
		self.assertFloat (v.imag, 2.0)
		v = a.get (1, 2)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 0)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 1)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 0)
		v = a.get (2, 2)
		self.assertFloat (v.real, 4.5)
		self.assertFloat (v.imag, 3.5)
	
	def test_init_fill_uc (self):
		a = CrankBase.MatCplxFloatN.init_fill_uc (2, 2, 1.5, 2.0)
		
		v = a.get (0, 0)
		self.assertFloat (v.real, 1.5)
		self.assertFloat (v.imag, 2.0)
		v = a.get (0, 1)
		self.assertFloat (v.real, 1.5)
		self.assertFloat (v.imag, 2.0)
		v = a.get (1, 0)
		self.assertFloat (v.real, 1.5)
		self.assertFloat (v.imag, 2.0)
		v = a.get (1, 1)
		self.assertFloat (v.real, 1.5)
		self.assertFloat (v.imag, 2.0)
		
if __name__ == '__main__':
	unittest.main ()
