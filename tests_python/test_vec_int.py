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
	def test_2_get (self):
		a = CrankBase.VecInt2.init (3, 4)
		
		self.assertEqual (a.get (0), 3)
		self.assertEqual (a.get (1), 4)
		
	def test_2_hash (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		c = CrankBase.VecInt2.init (3, 4)
		
		self.assertNotEqual (a.hash (), b.hash ())
		self.assertEqual (a.hash (), c.hash ())

	def test_2_equal (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		c = CrankBase.VecInt2.init (3, 4)
		
		assert (not (a.equal (b)))
		assert (a.equal (c))
	
	def test_2_to_string (self):
		a = CrankBase.VecInt2.init (3, 4)
		
		self.assertEqual (a.to_string (), "(3, 4)")
	
	def test_2_magn (self):
		a = CrankBase.VecInt2.init (3, 4)
		
		self.assertEqual (a.get_magn_sq (), 25)
		self.assertEqual (a.get_magn (), 5.0)

	def test_2_muls (self):
		a = CrankBase.VecInt2.init (3, 4)
		a = a.muls (3)
		
		self.assertEqual (a.x, 9)
		self.assertEqual (a.y, 12)
	
	def test_2_divs (self):
		a = CrankBase.VecInt2.init (3, 4)
		a = a.divs (3)
		
		self.assertEqual (a.x, 1)
		self.assertEqual (a.y, 1)
				
	def test_2_mods (self):
		a = CrankBase.VecInt2.init (3, 4)
		a = a.mods (3)
		
		self.assertEqual (a.x, 0)
		self.assertEqual (a.y, 1)
		
	def test_2_add (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		
		a = a.add (b)
		
		self.assertEqual (a.x, 8)
		self.assertEqual (a.y, 16)
		
	def test_2_sub (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		
		a = a.sub (b)
		
		self.assertEqual (a.x, -2)
		self.assertEqual (a.y, -8)

	def test_2_dot (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		
		self.assertEqual (a.dot (b), 63)
	
	def test_2_cmpmul (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		
		a = a.cmpmul (b)
		
		self.assertEqual (a.x, 15)
		self.assertEqual (a.y, 48)
	
	def test_2_cmpdiv (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		
		b = b.cmpdiv (a)
		
		self.assertEqual (b.x, 1)
		self.assertEqual (b.y, 3)
	
	def test_2_cmpmod (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		
		b = b.cmpmod (a)
		
		self.assertEqual (b.x, 2)
		self.assertEqual (b.y, 0)

	def test_2_cmpless (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		
		assert (a.cmpless (b).get_all ())
	
	def test_2_cmpeq (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (3, 5)
		
		assert (a.cmpeq (b).get_any ())
	
	def test_2_cmpgreater (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (5, 12)
		
		assert (not a.cmpgreater (b).get_any ())

	def test_2_cmpcmp (self):
		a = CrankBase.VecInt2.init (3, 4)
		b = CrankBase.VecInt2.init (3, 5)
		
		c = a.cmpcmp (b)
		
		self.assertEqual (c.x, 0)
		self.assertEqual (c.y, -1)
	
	def test_2_min (self):
		a = CrankBase.VecInt2.init (27, 12)
		b = CrankBase.VecInt2.init (12, 34)
		
		c = a.min (b)
		
		self.assertEqual (c.x, 12)
		self.assertEqual (c.y, 12)
		
	def test_2_max (self):
		a = CrankBase.VecInt2.init (27, 12)
		b = CrankBase.VecInt2.init (12, 34)
		
		c = a.max (b)
		
		self.assertEqual (c.x, 27)
		self.assertEqual (c.y, 34)
		
		
		
		
	def test_n_get (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		
		self.assertEqual (a.get (0), 3)
		self.assertEqual (a.get (1), 4)
		
	def test_n_hash (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		c = CrankBase.VecIntN.init_arr ([3, 4])
		
		self.assertNotEqual (a.hash (), b.hash ())
		self.assertEqual (a.hash (), c.hash ())

	def test_n_equal (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		c = CrankBase.VecIntN.init_arr ([3, 4])
		
		assert (not (a.equal (b)))
		assert (a.equal (c))
	
	def test_n_to_string (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		
		self.assertEqual (a.to_string (), "(3, 4)")
	
	def test_n_magn (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		
		self.assertEqual (a.get_magn_sq (), 25)
		self.assertEqual (a.get_magn (), 5.0)

	def test_n_muls (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		a = a.muls (3)
		
		self.assertEqual (a.data, [9, 12])
	
	def test_n_divs (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		a = a.divs (3)
		
		self.assertEqual (a.data, [1, 1])
				
	def test_n_mods (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		a = a.mods (3)
		
		self.assertEqual (a.data, [0, 1])
		
	def test_n_add (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		
		a = a.add (b)
		
		self.assertEqual (a.data, [8, 16])
		
	def test_n_sub (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		
		a = a.sub (b)
		
		self.assertEqual (a.data, [-2, -8])

	def test_n_dot (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		
		self.assertEqual (a.dot (b), 63)
	
	def test_n_cmpmul (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		
		a = a.cmpmul (b)
		
		self.assertEqual (a.data, [15, 48])
	
	def test_n_cmpdiv (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		
		b = b.cmpdiv (a)
		
		self.assertEqual (b.data, [1, 3])
	
	def test_n_cmpmod (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		
		b = b.cmpmod (a)
		
		self.assertEqual (b.data, [2, 0])

	def test_n_cmpless (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		
		assert (a.cmpless (b).get_all ())
	
	def test_n_cmpeq (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([3, 5])
		
		assert (a.cmpeq (b).get_any ())
	
	def test_n_cmpgreater (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([5, 12])
		
		assert (not a.cmpgreater (b).get_any ())

	def test_n_cmpcmp (self):
		a = CrankBase.VecIntN.init_arr ([3, 4])
		b = CrankBase.VecIntN.init_arr ([3, 5])
		
		c = a.cmpcmp (b)
		
		self.assertEqual (c.data, [0, -1])
	
	def test_n_min (self):
		a = CrankBase.VecIntN.init_arr ([27, 12])
		b = CrankBase.VecIntN.init_arr ([12, 34])
		
		c = a.min (b)
		
		self.assertEqual (c.data, [12, 12])
		
	def test_n_max (self):
		a = CrankBase.VecIntN.init_arr ([27, 12])
		b = CrankBase.VecIntN.init_arr ([12, 34])
		
		c = a.max (b)
		
		self.assertEqual (c.data, [27, 34])

if __name__ == '__main__':
	unittest.main ()
