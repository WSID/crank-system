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


class TestVecCplxFloat(unittest.TestCase):

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

	def accumulation (self, value):
        	self.sum = self.sum.add (value)
        	return True



	def test_n_get (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		
		v = a.get (0)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 4)
		
		v = a.get (1)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 12)

	def test_n_insert (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		a.insert (1, CrankBase.CplxFloat.init (5, 10))

		
		v = a.get (0)
		self.assertFloat (v.real, 3)
		self.assertFloat (v.imag, 4)
		
		v = a.get (1)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 10)
		
		v = a.get (2)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 12)

	def test_n_remove (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		a.remove (0)

		self.assertEqual (a.get_size (), 1)
		
		v = a.get (0)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 12)


	def test_n_foreach (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		self.sum = CrankBase.CplxFloat.init (0, 0)

		assert (a.foreach (self.accumulation))
		self.assertEqual (self.sum.real, 8)
		self.assertEqual (self.sum.imag, 16)

	def test_n_equal (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (4, 3),
				CrankBase.CplxFloat.init (5, 12)])
		c = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		
		assert (not (a.equal (b)))
		assert (a.equal (c))
	
	def test_n_magn (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		
		self.assertFloat (a.get_magn_sq (), 194.0)
		self.assertFloat (a.get_magn (), 13.9284)
		
	def test_n_unit (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		a = a.unit ()
		
		v = a.get (0)
		self.assertFloat (v.real, 0.2154)
		self.assertFloat (v.imag, 0.2872)
		
		v = a.get (1)
		self.assertFloat (v.real, 0.3590)
		self.assertFloat (v.imag, 0.8615)

	def test_n_muls (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		a = a.muls (CrankBase.CplxFloat.init (2, 3))
		
		v = a.get (0)
		self.assertFloat (v.real, -6)
		self.assertFloat (v.imag, 17)
		
		v = a.get (1)
		self.assertFloat (v.real, -26)
		self.assertFloat (v.imag, 39)
	
	def test_n_divs (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		a = a.divs (CrankBase.CplxFloat.init (2, 3))
		
		v = a.get (0)
		self.assertFloat (v.real, 1.3846)
		self.assertFloat (v.imag, -0.0769)
		
		v = a.get (1)
		self.assertFloat (v.real, 3.5385)
		self.assertFloat (v.imag, 0.6923)
	
	def test_n_mulrs (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		a = a.mulrs (2)
		
		v = a.get (0)
		self.assertFloat (v.real, 6)
		self.assertFloat (v.imag, 8)
		
		v = a.get (1)
		self.assertFloat (v.real, 10)
		self.assertFloat (v.imag, 24)
	
	def test_n_divrs (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)])
		a = a.divrs (2)
		
		v = a.get (0)
		self.assertFloat (v.real, 1.5)
		self.assertFloat (v.imag, 2.0)
		
		v = a.get (1)
		self.assertFloat (v.real, 2.5)
		self.assertFloat (v.imag, 6.0)
				
	def test_n_add (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)	])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 3),
				CrankBase.CplxFloat.init (5, 10)	])

		a = a.add (b)
		
		v = a.get (0)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 7)
		
		v = a.get (1)
		self.assertFloat (v.real, 10)
		self.assertFloat (v.imag, 22)
		
	def test_n_sub (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)	])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 3),
				CrankBase.CplxFloat.init (5, 10)	])

		a = a.sub (b)
		
		v = a.get (0)
		self.assertFloat (v.real, 1)
		self.assertFloat (v.imag, 1)
		
		v = a.get (1)
		self.assertFloat (v.real, 0)
		self.assertFloat (v.imag, 2)

	def test_n_dot (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)	])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 3),
				CrankBase.CplxFloat.init (5, 10)	])
		
		v = a.dot (b)
		
		self.assertFloat (v.real, 163)
		self.assertFloat (v.imag, 9)
	
	def test_n_cmpmul (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)	])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 3),
				CrankBase.CplxFloat.init (5, 10)	])
		
		a = a.cmpmul (b)
		
		v = a.get (0)
		self.assertFloat (v.real, -6)
		self.assertFloat (v.imag, 17)
		
		v = a.get (1)
		self.assertFloat (v.real, -95)
		self.assertFloat (v.imag, 110)
	
	def test_n_cmpdiv (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)	])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 3),
				CrankBase.CplxFloat.init (5, 10)	])
		
		a = a.cmpdiv (b)
		
		v = a.get (0)
		self.assertFloat (v.real, 1.3846)
		self.assertFloat (v.imag, -0.0769)
		
		v = a.get (1)
		self.assertFloat (v.real, 1.16)
		self.assertFloat (v.imag, 0.08)

	def test_n_cmpeq (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 3),
				CrankBase.CplxFloat.init (4, 6),
				CrankBase.CplxFloat.init (17, 20)	])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 2),
				CrankBase.CplxFloat.init (4, 6),
				CrankBase.CplxFloat.init (53, 55)		])
		
		r = a.cmpeq (b)
		
		self.assertEqual (r.data[0], False)
		self.assertEqual (r.data[1], True)
		self.assertEqual (r.data[2], False)

	def test_n_mulrm (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12),
				CrankBase.CplxFloat.init (2, 3)	])
		b = CrankBase.MatFloatN.init_arr (3, 2,
                		[1, 2,
                  		 3, 4,
                     	 5, 6])

		a = a.mulrm (b)
		v = a.get (0)
		self.assertFloat (v.real, 28)
		self.assertFloat (v.imag, 55)
		
		v = a.get (1)
		self.assertFloat (v.real, 38)
		self.assertFloat (v.imag, 74)
		
	
	def test_n_mixs (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)	])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 3),
				CrankBase.CplxFloat.init (5, 10)	])
		
		c = a.mixs (b, 0.2)
		
		v = c.get (0)
		self.assertFloat (v.real, 2.8)
		self.assertFloat (v.imag, 3.8)
		
		v = c.get (1)
		self.assertFloat (v.real, 5)
		self.assertFloat (v.imag, 11.6)
	
	def test_n_mix (self):
		a = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (3, 4),
				CrankBase.CplxFloat.init (5, 12)	])
		b = CrankBase.VecCplxFloatN.init_arr ([
				CrankBase.CplxFloat.init (2, 3),
				CrankBase.CplxFloat.init (5, 10)	])
		c = CrankBase.VecFloatN.init_arr ([0.6, 0.5])
		
		d = a.mix (b, c)
		
		v = d.get (0)
		self.assertFloat (v.real, 2.4)
		self.assertFloat (v.imag, 3.4)
		
		v = d.get (1)
		self.assertFloat (v.real, 5.0)
		self.assertFloat (v.imag, 11.0)
		
if __name__ == '__main__':
	unittest.main ()
