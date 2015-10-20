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


class TestQuaternion(unittest.TestCase):

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
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.QuatFloat.init (3, 4, 5, 12)
		c = CrankBase.QuatFloat.init (4, 3, 5, 12)
		
		assert (a.equal (b))
		assert (not a.equal (c))


	def test_equal_delta (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.QuatFloat.init (3.2, 4.1, 5, 11.9)
		c = CrankBase.QuatFloat.init (4, 3, 5, 11)
		
		assert (a.equal_delta (b, 1))
		assert (not a.equal_delta (c, 1))
	
	
	def test_get_norm (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		self.assertFloat (a.get_norm (), 13.9284)
	
	
	def test_get_rangle (self):
		a = CrankBase.QuatFloat.init (0.4794, 0.5067, 0.5067, 0.5067)
		
		self.assertFloat (a.get_rangle (), 2.1416)
	
	
	def test_get_raxis (self):
		a = CrankBase.QuatFloat.init (0.4794, 0.5067, 0.5067, 0.5067)
		axis = a.get_raxis ()
		
		self.assertFloat (axis.x, 0.5774);
		self.assertFloat (axis.y, 0.5774);
		self.assertFloat (axis.z, 0.5774);
	
	
	def test_neg (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.neg ()
		
		self.assertFloat (a.w, -3)
		self.assertFloat (a.x, -4)
		self.assertFloat (a.y, -5)
		self.assertFloat (a.z, -12)
		
		
	def test_inverse (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.inverse ()
		
		self.assertFloat (a.w,  0.0155)
		self.assertFloat (a.x, -0.0206)
		self.assertFloat (a.y, -0.0258)
		self.assertFloat (a.z, -0.0619)
	
	
	def test_conjugate (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.conjugate ()
		
		self.assertFloat (a.w, 3)
		self.assertFloat (a.x, -4)
		self.assertFloat (a.y, -5)
		self.assertFloat (a.z, -12)
	
	
	def test_unit (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.unit ()
		
		self.assertFloat (a.w, 0.2154)
		self.assertFloat (a.x, 0.2872)
		self.assertFloat (a.y, 0.3590)
		self.assertFloat (a.z, 0.8615)
	
	
	def test_addr (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.addr (2)
		
		self.assertFloat (a.w, 5)
		self.assertFloat (a.x, 4)
		self.assertFloat (a.y, 5)
		self.assertFloat (a.z, 12)
	
	
	def test_subr (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.subr (2)
		
		self.assertFloat (a.w, 1)
		self.assertFloat (a.x, 4)
		self.assertFloat (a.y, 5)
		self.assertFloat (a.z, 12)
		
		
	def test_mulr (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.mulr (2)
		
		self.assertFloat (a.w, 6)
		self.assertFloat (a.x, 8)
		self.assertFloat (a.y, 10)
		self.assertFloat (a.z, 24)
		
		
	def test_divr (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.divr (2)
		
		self.assertFloat (a.w, 1.5)
		self.assertFloat (a.x, 2)
		self.assertFloat (a.y, 2.5)
		self.assertFloat (a.z, 6)
		
		
	def test_rsubr (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.rsubr (2)
		
		self.assertFloat (a.w, -1)
		self.assertFloat (a.x, -4)
		self.assertFloat (a.y, -5)
		self.assertFloat (a.z, -12)
		
		
	def test_rdivr (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.rdivr (2)
		
		self.assertFloat (a.w, 0.0309)
		self.assertFloat (a.x,-0.0412)
		self.assertFloat (a.y,-0.0515)
		self.assertFloat (a.z,-0.1237)
		
		
	def test_addc (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.CplxFloat.init (2, 3)
		
		a = a.addc (b)
		
		self.assertFloat (a.w, 5)
		self.assertFloat (a.x, 7)
		self.assertFloat (a.y, 5)
		self.assertFloat (a.z, 12)
		
		
	def test_subc (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.CplxFloat.init (2, 3)
		
		a = a.subc (b)
		
		self.assertFloat (a.w, 1)
		self.assertFloat (a.x, 1)
		self.assertFloat (a.y, 5)
		self.assertFloat (a.z, 12)
		
		
	def test_mulc (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.CplxFloat.init (2, 3)
		
		a = a.mulc (b)
		
		self.assertFloat (a.w, -6)
		self.assertFloat (a.x, 17)
		self.assertFloat (a.y, 46)
		self.assertFloat (a.z, 9)
		
		
	def test_add (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.QuatFloat.init (2, 3, 5, 8)
		
		a = a.add (b)
		
		self.assertFloat (a.w, 5)
		self.assertFloat (a.x, 7)
		self.assertFloat (a.y, 10)
		self.assertFloat (a.z, 20)
		
		
	def test_sub (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.QuatFloat.init (2, 3, 5, 8)
		
		a = a.sub (b)
		
		self.assertFloat (a.w, 1)
		self.assertFloat (a.x, 1)
		self.assertFloat (a.y, 0)
		self.assertFloat (a.z, 4)
		
		
	def test_mul (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.QuatFloat.init (2, 3, 5, 8)
		
		a = a.mul (b)
		
		self.assertFloat (a.w, -127)
		self.assertFloat (a.x, -3)
		self.assertFloat (a.y, 29)
		self.assertFloat (a.z, 53)


	def test_mul_conj (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.QuatFloat.init (2, 3, 5, 8)
		
		a = a.mul_conj (b)
		
		self.assertFloat (a.w, 139.0)
		self.assertFloat (a.x, 19.0)
		self.assertFloat (a.y, -9.0)
		self.assertFloat (a.z, -5.0)
		
		
	def test_mix (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		b = CrankBase.QuatFloat.init (2, 3, 5, 8)
		
		a = a.mix (b, 0.25)
		
		self.assertFloat (a.w, 2.75)
		self.assertFloat (a.x, 3.75)
		self.assertFloat (a.y, 5)
		self.assertFloat (a.z, 11)
	
	
	def test_ln (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.ln ()
		
		self.assertFloat (a.w, 2.6339)
		self.assertFloat (a.x, 0.3981)
		self.assertFloat (a.y, 0.4976)
		self.assertFloat (a.z, 1.1943)
	
	
	def test_exp (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.exp ()
		
		self.assertFloat (a.w, 10.2525)
		self.assertFloat (a.x, 5.0794)
		self.assertFloat (a.y, 6.3492)
		self.assertFloat (a.z, 15.2382)
	
	
	def test_powr (self):
		a = CrankBase.QuatFloat.init (3, 4, 5, 12)
		
		a = a.powr (2.5)
		
		self.assertFloat (a.w, -702.8075)
		self.assertFloat (a.x, -51.1662)
		self.assertFloat (a.y, -63.9578)
		self.assertFloat (a.z, -153.4986, 0.0005)
		
	
	def test_rotatev (self):
		a = CrankBase.QuatFloat.init (0.4794, 0.5067, 0.5067, 0.5067)
		v = CrankBase.VecFloat3.init (1, 2, 3)
		
		rv = a.rotatev (v)
		
		self.assertFloat (rv.x, 3.0264)
		self.assertFloat (rv.y, 1.0285)
		self.assertFloat (rv.z, 1.9455)
		
if __name__ == '__main__':
	unittest.main ()
