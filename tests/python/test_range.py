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


class TestRange(unittest.TestCase):

	def test_uint_equal (self):
		a = CrankBase.RanUint.init (3, 5)
		b = CrankBase.RanUint.init (0, 4)
		c = CrankBase.RanUint.init (3, 5)
		
		assert (not a.equal (b))
		assert (a.equal (c))
		
	def test_uint_hash (self):
		a = CrankBase.RanUint.init (3, 5)
		b = CrankBase.RanUint.init (0, 4)
		c = CrankBase.RanUint.init (3, 5)
		
		self.assertNotEqual (a.hash (), b.hash ())
		self.assertEqual (a.hash (), c.hash ());

	def test_uint_to_string (self):
		a = CrankBase.RanUint.init (3, 5)
		
		self.assertEqual (a.to_string (), "[3, 5)")
	
	def test_uint_is_empty (self):
		a = CrankBase.RanUint.init (2, 3)
		assert (not a.is_empty())
		
		a = CrankBase.RanUint.init (4, 4)
		assert (a.is_empty())
	
	def test_uint_is_unit (self):
		a = CrankBase.RanUint.init (2, 3)
		assert (a.is_unit())
		
		a = CrankBase.RanUint.init (4, 4)
		assert (not a.is_unit())
		
	def test_uint_get_length (self):
		a = CrankBase.RanUint.init (7, 12)
		self.assertEqual (a.get_length (), 5)

	def test_uint_contains (self):
		a = CrankBase.RanUint.init (10, 23)
		assert (a.contains (15))
		assert (not a.contains (55))

	def test_uint_get (self):
		a = CrankBase.RanUint.init (10, 110)
		self.assertEqual (a.get (0.25), 35)

	def test_uint_index_of (self):
		a = CrankBase.RanUint.init (10, 110)
		self.assertEqual (a.index_of (85), 0.75)
	
	def test_uint_clamp (self):
		a = CrankBase.RanUint.init (10, 100)
		self.assertEqual (a.clamp (4), 10)
		self.assertEqual (a.clamp (44), 44)
		self.assertEqual (a.clamp (200), 100)
	
	def test_uint_intersection (self):
		a = CrankBase.RanUint.init (14, 45)
		b = CrankBase.RanUint.init (55, 74)
		c = CrankBase.RanUint.init (30, 60)
		
		(res, d) = a.intersection (b)
		
		assert (not res)
		
		(res, e) = a.intersection (c)
		
		assert (res)
		self.assertEqual (e.start, 30)
		self.assertEqual (e.end, 45)
		
if __name__ == '__main__':
	unittest.main ()
