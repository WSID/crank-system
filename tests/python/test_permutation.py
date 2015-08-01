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

class TestPermutation(unittest.TestCase):

	def test_check_valid (self):
		p = CrankBase.Permutation.init_arr ([0, 1, 2, 3, 4])
		q = CrankBase.Permutation.init_arr ([0, 3, 0, 2, 4])
		r = CrankBase.Permutation.init_arr ([0, 6, 3, 4, 7])
		
		assert (p.check_valid ())
		assert (not q.check_valid ())
		assert (not r.check_valid ())
	
	def test_is_empty (self):
		p = CrankBase.Permutation.init_arr ([1, 0])
		assert (not p.is_empty ())
		
		p = CrankBase.Permutation.init_arr ([])
		assert (p.is_empty ())

	def test_slice (self):
		p = CrankBase.Permutation.init_arr ([2, 1, 3, 4, 0])
		
		self.assertEqual (p.slice (1, 4), [1, 3, 4])


	def test_is_identity (self):
		p = CrankBase.Permutation.init_arr ([2, 1, 0])
		assert (not p.is_identity())
		
		p = CrankBase.Permutation.init_arr ([0, 1, 2])
		assert (p.is_identity ())

	def test_inversion (self):
		p = CrankBase.Permutation.init_arr ([2, 1, 3, 4, 0])
		self.assertEqual (p.get_inversion (), 5)

	def test_sign (self):
		p = CrankBase.Permutation.init_arr ([2, 1, 3, 4, 0])
		
		self.assertEqual (p.get_sign (), -1);
	
	def test_ascents (self):
		p = CrankBase.Permutation.init_arr ([2, 1, 3, 4, 0])
		
		self.assertEqual (p.get_ascents (), [1, 2])
	
	def test_descents (self):
		p = CrankBase.Permutation.init_arr ([2, 1, 3, 4, 0])
		
		self.assertEqual (p.get_descents (), [0, 3])
		
	def test_excedances (self):
		p = CrankBase.Permutation.init_arr ([2, 1, 3, 4, 0])
		
		self.assertEqual (p.get_excedances (), [0, 2, 3])
	
	def test_swap (self):
		p = CrankBase.Permutation.init_arr ([0, 1, 3, 2, 4])
		
		p.swap (2, 3)
		
		self.assertEqual (p.get (2), 2)
		self.assertEqual (p.get (3), 3)

	def test_reverse (self):
		p = CrankBase.Permutation.init_arr ([0, 1, 3, 2, 4])
		
		q = p.reverse ()
		
		self.assertEqual (q.get (0), 4)
		self.assertEqual (q.get (1), 2)
		self.assertEqual (q.get (2), 3)
		self.assertEqual (q.get (3), 1)
		self.assertEqual (q.get (4), 0)

	def test_inverse (self):
		p = CrankBase.Permutation.init_arr ([0, 1, 3, 2, 4])
		
		q = p.inverse ()
		
		self.assertEqual (q.get (0), 0)
		self.assertEqual (q.get (1), 1)
		self.assertEqual (q.get (2), 3)
		self.assertEqual (q.get (3), 2)
		self.assertEqual (q.get (4), 4)

	def test_shuffle (self):
		p = CrankBase.Permutation.init_arr ([0, 1, 3, 2])
		q = CrankBase.Permutation.init_arr ([1, 0, 2, 3])

		p = p.shuffle (q)

		self.assertEqual (p.get (0), 1);
		self.assertEqual (p.get (1), 0);
		self.assertEqual (p.get (2), 3);
		self.assertEqual (p.get (3), 2);

if __name__ == '__main__':
	unittest.main ()
