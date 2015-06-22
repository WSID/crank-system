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


class TestBaseBook(unittest.TestCase):
	def test_add (self):
		self.assertEqual (CrankBase.base_add (12, 32), (True, 12 + 32))
	
	def test_sub (self):
		self.assertEqual (CrankBase.base_sub (43.2, 21.4), (True, 43.2 - 21.4))
	
	def test_mul (self):
		self.assertEqual (CrankBase.base_mul (15, 65), (True, 15 * 65))
	
	def test_div (self):
		self.assertEqual (CrankBase.base_div (32.1, 11.1), (True, 32.1 / 11.1))
	
	def test_neg (self):
		self.assertEqual (CrankBase.base_neg (-44), (True, 44))
	
	def test_inc (self):
		self.assertEqual (CrankBase.base_inc (7), (True, 8))
	
	def test_dec (self):
		self.assertEqual (CrankBase.base_dec (8), (True, 7))
		
	def test_lshift (self):
		lshv = GObject.Value (py_value=3, value_type=GObject.GType.from_name ("guint"))
		self.assertEqual (CrankBase.base_lshift (342, lshv), (True, 342 * 8))
	
	def test_rshift (self):
		rshv = GObject.Value (py_value=3, value_type=GObject.GType.from_name ("guint"))
		self.assertEqual (CrankBase.base_rshift (342, rshv), (True, 342 / 8))
	
	def test_leq (self):
		self.assertEqual (CrankBase.base_leq (173, 7), (True, False))
		
	def test_eq (self):
		self.assertEqual (CrankBase.base_eq (173, 7), (True, False))
		
	def test_geq (self):
		self.assertEqual (CrankBase.base_geq (173, 7), (True, True))

if __name__ == '__main__':
	unittest.main ()
