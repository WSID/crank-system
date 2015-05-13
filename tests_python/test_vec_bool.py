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


class TestVecBool(unittest.TestCase):
	def test_2_get (self):
		a = CrankBase.VecBool2.init (True, False)
		
		self.assertEqual (a.get (0), True)
		self.assertEqual (a.get (1), False)
		
	def test_2_and (self):
		a = CrankBase.VecBool2.init (True, True)
		b = CrankBase.VecBool2.init (False, True)
		
		c = a.andv (b)
		
		self.assertEqual (c.x, False)
		self.assertEqual (c.y, True)
		
	def test_2_or (self):
		a = CrankBase.VecBool2.init (False, False)
		b = CrankBase.VecBool2.init (False, True)
		
		c = a.orv (b)
		
		self.assertEqual (c.x, False)
		self.assertEqual (c.y, True)
	
	def test_2_xor (self):
		a = CrankBase.VecBool2.init (True, True)
		b = CrankBase.VecBool2.init (True, False)
		
		c = a.xor (b)
		
		self.assertEqual (c.x, False);
		self.assertEqual (c.y, True);
	
	def test_2_not (self):
		a = CrankBase.VecBool2.init (True, False)
		
		c = a.notv ();
		
		self.assertEqual (c.x, False);
		self.assertEqual (c.y, True);
	
	def test_2_any (self):
		a = CrankBase.VecBool2.init (True, False);
		b = CrankBase.VecBool2.init (False, False);
		
		self.assertEqual (a.get_any (), True);
		self.assertEqual (b.get_any (), False);
	
	def test_2_all (self):
		a = CrankBase.VecBool2.init (True, True);
		b = CrankBase.VecBool2.init (True, False);
		
		self.assertEqual (a.get_all (), True);
		self.assertEqual (b.get_all (), False);



	def test_n_get (self):
		a = CrankBase.VecBoolN.init_arr ([True, False, False, True])
		
		self.assertEqual (a.get (0), True)
		self.assertEqual (a.get (1), False)
		self.assertEqual (a.get (2), False)
		self.assertEqual (a.get (3), True)
		
	def test_n_and (self):
		a = CrankBase.VecBoolN.init_arr ([True, True, False, True])
		b = CrankBase.VecBoolN.init_arr ([False, True])
		
		c = a.andv (b)
		
		self.assertEqual (c.get_size (), 2)
		self.assertEqual (c.get (0), False)
		self.assertEqual (c.get (1), True)
		
	def test_n_or (self):
		a = CrankBase.VecBoolN.init_arr ([True, False, False, True])
		b = CrankBase.VecBoolN.init_arr ([False, False])
		
		c = a.orv (b)
		
		self.assertEqual (c.get_size (), 4)
		self.assertEqual (c.get (0), True)
		self.assertEqual (c.get (1), False)
		self.assertEqual (c.get (2), False)
		self.assertEqual (c.get (3), True)
	
	def test_n_xor (self):
		a = CrankBase.VecBoolN.init_arr ([True, True, False, True])
		b = CrankBase.VecBoolN.init_arr ([False, True])
		
		c = a.xor (b)
		
		self.assertEqual (c.get_size (), 4)
		self.assertEqual (c.get (0), True);
		self.assertEqual (c.get (1), False);
		self.assertEqual (c.get (2), False);
		self.assertEqual (c.get (3), True);
	
	def test_n_not (self):
		a = CrankBase.VecBoolN.init_arr ([True, False])
		
		c = a.notv ();
		
		self.assertEqual (c.get_size (), 2);
		self.assertEqual (c.get (0), False);
		self.assertEqual (c.get (1), True);
	
	def test_n_any (self):
		a = CrankBase.VecBoolN.init_arr ([True, False]);
		b = CrankBase.VecBoolN.init_arr ([False, False]);
		
		self.assertEqual (a.get_any (), True);
		self.assertEqual (b.get_any (), False);
	
	def test_n_all (self):
		a = CrankBase.VecBoolN.init_arr ([True, True]);
		b = CrankBase.VecBoolN.init_arr ([True, False]);
		
		self.assertEqual (a.get_all (), True);
		self.assertEqual (b.get_all (), False);

if __name__ == '__main__':
	unittest.main ()
