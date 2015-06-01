#!/usr/bin/python

# Copyright (C) 2015, WSID

# This file is part of Crank System.
#
#  Crank System is free software: you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation, either
#  version 3 of the License, or (at your option) any later version.
#
#  Crank System is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with Crank System.
#  If not, see <http://www.gnu.org/licenses/>.

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

	def test_2_get (self):
		a = CrankBase.VecFloat2.init (3, 4)
		
		self.assertFloat (a.get (0), 3)
		self.assertFloat (a.get (1), 4)

	def test_2_equal (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (5, 12)
		c = CrankBase.VecFloat2.init (3, 4)
		
		assert (not (a.equal (b)))
		assert (a.equal (c))
	
	def test_2_to_string (self):
		a = CrankBase.VecFloat2.init (3, 4)
		
		self.assertEqual (a.to_string (), "(3, 4)")
	
	def test_2_magn (self):
		a = CrankBase.VecFloat2.init (3, 4)
		
		self.assertFloat (a.get_magn_sq (), 25.0)
		self.assertFloat (a.get_magn (), 5.0)
		
	def test_2_unit (self):
		a = CrankBase.VecFloat2.init (3, 4)
		a = a.unit ()
		
		self.assertFloat (a.x, 3.0 / 5.0)
		self.assertFloat (a.y, 0.8)

	def test_2_muls (self):
		a = CrankBase.VecFloat2.init (3, 4)
		a = a.muls (3)
		
		self.assertFloat (a.x, 9)
		self.assertFloat (a.y, 12)
	
	def test_2_divs (self):
		a = CrankBase.VecFloat2.init (3, 4)
		a = a.divs (3)
		
		self.assertFloat (a.x, 1)
		self.assertFloat (a.y, 4.0 / 3.0)
				
	def test_2_add (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (5, 12)
		
		a = a.add (b)
		
		self.assertFloat (a.x, 8)
		self.assertFloat (a.y, 16)
		
	def test_2_sub (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (5, 12)
		
		a = a.sub (b)
		
		self.assertFloat (a.x, -2)
		self.assertFloat (a.y, -8)

	def test_2_dot (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (5, 12)
		
		self.assertFloat (a.dot (b), 63)
	
	def test_2_cmpmul (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (5, 12)
		
		a = a.cmpmul (b)
		
		self.assertFloat (a.x, 15)
		self.assertFloat (a.y, 48)
	
	def test_2_cmpdiv (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (5, 12)
		
		b = b.cmpdiv (a)
		
		self.assertFloat (b.x, 5.0 / 3.0)
		self.assertFloat (b.y, 3)

	def test_2_cmpless (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (5, 12)
		
		assert (a.cmpless (b).get_all ())
	
	def test_2_cmpeq (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (3, 5)
		
		assert (a.cmpeq (b).get_any ())
	
	def test_2_cmpgreater (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (5, 12)
		
		assert (not a.cmpgreater (b).get_any ())

	def test_2_cmpcmp (self):
		a = CrankBase.VecFloat2.init (3, 4)
		b = CrankBase.VecFloat2.init (3, 5)
		
		c = a.cmpcmp (b)
		
		self.assertEqual (c.x, 0)
		self.assertEqual (c.y, -1)
	
	def test_2_min (self):
		a = CrankBase.VecFloat2.init (27, 12)
		b = CrankBase.VecFloat2.init (12, 34)
		
		c = a.min (b)
		
		self.assertFloat (c.x, 12)
		self.assertFloat (c.y, 12)
		
	def test_2_max (self):
		a = CrankBase.VecFloat2.init (27, 12)
		b = CrankBase.VecFloat2.init (12, 34)
		
		c = a.max (b)
		
		self.assertFloat (c.x, 27)
		self.assertFloat (c.y, 34)
		
	
	def test_2_mixs (self):
		a = CrankBase.VecFloat2.init (15, 27)
		b = CrankBase.VecFloat2.init (30, 17)
		
		c = a.mixs (b, 0.2)
		
		self.assertFloat (c.x, 18)
		self.assertFloat (c.y, 25)
	
	def test_2_mix (self):
		a = CrankBase.VecFloat2.init (15, 27)
		b = CrankBase.VecFloat2.init (30, 17)
		c = CrankBase.VecFloat2.init (0.2, 0.8)
		
		d = a.mix (b, c)
		
		self.assertFloat (d.x, 18)
		self.assertFloat (d.y, 19)




	def test_n_get (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		
		self.assertFloat (a.get (0), 3)
		self.assertFloat (a.get (1), 4)

	def test_n_equal (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([5, 12])
		c = CrankBase.VecFloatN.init_arr ([3, 4])
		
		assert (not (a.equal (b)))
		assert (a.equal (c))
	
	def test_n_to_string (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		
		self.assertEqual (a.to_string (), "(3, 4)")
	
	def test_n_magn (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		
		self.assertFloat (a.get_magn_sq (), 25.0)
		self.assertFloat (a.get_magn (), 5.0)
		
	def test_n_unit (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		a = a.unit ()
		
		self.assertFloat (a.data, [3.0 / 5.0, 0.8])

	def test_n_muls (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		a = a.muls (3)
		
		self.assertFloat (a.data, [9, 12])
	
	def test_n_divs (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		a = a.divs (3)
		
		self.assertFloat (a.data, [1, 4.0 / 3.0])
				
	def test_n_add (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([5, 12])
		
		a = a.add (b)
		
		self.assertFloat (a.data, [8, 16])
		
	def test_n_sub (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([5, 12])
		
		a = a.sub (b)
		
		self.assertFloat (a.data, [-2, -8])

	def test_n_dot (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([5, 12])
		
		self.assertFloat (a.dot (b), 63)
	
	def test_n_cmpmul (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([5, 12])
		
		a = a.cmpmul (b)
		
		self.assertFloat (a.data, [15, 48])
	
	def test_n_cmpdiv (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([5, 12])
		
		b = b.cmpdiv (a)
		
		self.assertFloat (b.data, [5.0 / 3.0, 3])

	def test_n_cmpless (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([5, 12])
		
		assert (a.cmpless (b).get_all ())
	
	def test_n_cmpeq (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([3, 5])
		
		assert (a.cmpeq (b).get_any ())
	
	def test_n_cmpgreater (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([5, 12])
		
		assert (not a.cmpgreater (b).get_any ())

	def test_n_cmpcmp (self):
		a = CrankBase.VecFloatN.init_arr ([3, 4])
		b = CrankBase.VecFloatN.init_arr ([3, 5])
		
		c = a.cmpcmp (b)
		
		self.assertEqual (c.data, [0, -1])
	
	def test_n_min (self):
		a = CrankBase.VecFloatN.init_arr ([27, 12])
		b = CrankBase.VecFloatN.init_arr ([12, 34])
		
		c = a.min (b)
		
		self.assertFloat (c.data, [12, 12])
		
	def test_n_max (self):
		a = CrankBase.VecFloatN.init_arr ([27, 12])
		b = CrankBase.VecFloatN.init_arr ([12, 34])
		
		c = a.max (b)
		
		self.assertFloat (c.data, [27, 34])
		
	
	def test_n_mixs (self):
		a = CrankBase.VecFloatN.init_arr ([15, 27])
		b = CrankBase.VecFloatN.init_arr ([30, 17])
		
		c = a.mixs (b, 0.2)
		
		self.assertFloat (c.data, [18, 25])
	
	def test_n_mix (self):
		a = CrankBase.VecFloatN.init_arr ([15, 27])
		b = CrankBase.VecFloatN.init_arr ([30, 17])
		c = CrankBase.VecFloatN.init_arr ([0.2, 0.8])
		
		d = a.mix (b, c)
		
		self.assertFloat (d.data, [18, 19])
		
if __name__ == '__main__':
	unittest.main ()
