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


class TestVecInt(unittest.TestCase):

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
		a = CrankBase.CplxFloat.init (3, 4)
		b = CrankBase.CplxFloat.init (3, 4)
		c = CrankBase.CplxFloat.init (4, 3)
		
		assert (a.equal (b))
		assert (not a.equal (c))
	
	def test_get_norm (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		self.assertFloat (a.get_norm (), 5)
	
	def test_neg (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.neg ()
		
		self.assertFloat (a.real, -3)
		self.assertFloat (a.imag, -4)
		
	def test_inverse (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.inverse ()
		
		self.assertFloat (a.real, 0.12)
		self.assertFloat (a.imag, -0.16)
	
	def test_conjugate (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.conjugate ()
		
		self.assertFloat (a.real, 3)
		self.assertFloat (a.imag, -4)
	
	def test_addr (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.addr (2)
		
		self.assertFloat (a.real, 5)
		self.assertFloat (a.imag, 4)
	
	def test_subr (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.subr (2)
		
		self.assertFloat (a.real, 1)
		self.assertFloat (a.imag, 4)
		
	def test_mulr (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.mulr (2)
		
		self.assertFloat (a.real, 6)
		self.assertFloat (a.imag, 8)
		
	def test_divr (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.divr (2)
		
		self.assertFloat (a.real, 1.5)
		self.assertFloat (a.imag, 2)
		
	def test_rsubr (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.rsubr (2)
		
		self.assertFloat (a.real, -1)
		self.assertFloat (a.imag, -4)
		
	def test_rdivr (self):
		a = CrankBase.CplxFloat.init (3, 4)
		
		a = a.rdivr (2)
		
		self.assertFloat (a.real, 0.24)
		self.assertFloat (a.imag, -0.32)
		
	def test_add (self):
		a = CrankBase.CplxFloat.init (3, 4)
		b = CrankBase.CplxFloat.init (5, 12)
		
		a = a.add (b)
		
		self.assertFloat (a.real, 8)
		self.assertFloat (a.imag, 16)
		
	def test_sub (self):
		a = CrankBase.CplxFloat.init (3, 4)
		b = CrankBase.CplxFloat.init (5, 12)
		
		a = a.sub (b)
		
		self.assertFloat (a.real, -2)
		self.assertFloat (a.imag, -8)
		
	def test_mul (self):
		a = CrankBase.CplxFloat.init (3, 4)
		b = CrankBase.CplxFloat.init (5, 12)
		
		a = a.mul (b)
		
		self.assertFloat (a.real, -33)
		self.assertFloat (a.imag, 56)
		
	def test_div (self):
		a = CrankBase.CplxFloat.init (3, 4)
		b = CrankBase.CplxFloat.init (5, 12)
		
		a = a.div (b)
		
		self.assertFloat (a.real, 63.0/169.0)
		self.assertFloat (a.imag, -16.0/169.0)

	def test_mul_conj (self):
		a = CrankBase.CplxFloat.init (3, 4)
		b = CrankBase.CplxFloat.init (5, 12)
		
		a = a.mul_conj (b)
		
		self.assertFloat (a.real, 63.0)
		self.assertFloat (a.imag, -16.0)
		
	def test_mix (self):
		a = CrankBase.CplxFloat.init (3, 4)
		b = CrankBase.CplxFloat.init (5, 12)
		
		a = a.mix (b, 0.25)
		
		self.assertFloat (a.real, 3.5)
		self.assertFloat (a.imag, 6.0)
		
if __name__ == '__main__':
	unittest.main ()
