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
		
		self.assertEqual (c.x, False)
		self.assertEqual (c.y, True)
	
	def test_2_not (self):
		a = CrankBase.VecBool2.init (True, False)
		
		c = a.notv ()
		
		self.assertEqual (c.x, False)
		self.assertEqual (c.y, True)
	
	def test_2_any (self):
		a = CrankBase.VecBool2.init (True, False)
		b = CrankBase.VecBool2.init (False, False)
		
		self.assertEqual (a.get_any (), True)
		self.assertEqual (b.get_any (), False)
	
	def test_2_all (self):
		a = CrankBase.VecBool2.init (True, True)
		b = CrankBase.VecBool2.init (True, False)
		
		self.assertEqual (a.get_all (), True)
		self.assertEqual (b.get_all (), False)

	def test_2_equal (self):
		a = CrankBase.VecBool2.init (True, True)
		b = CrankBase.VecBool2.init (True, True)
		c = CrankBase.VecBool2.init (True, False)
		
		assert (    a.equal (b))
		assert (not a.equal (c))
	
	def test_2_hash (self):
		a = CrankBase.VecBool2.init (True, True)
		b = CrankBase.VecBool2.init (True, True)
		c = CrankBase.VecBool2.init (True, False)
		
		self.assertEqual (a.hash (), b.hash ())
		self.assertNotEqual (a.hash (), c.hash ())
	
	def test_2_to_string (self):
		a = CrankBase.VecBool2.init (True, False)
		self.assertEqual (a.to_string(), "(true, false)")



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

	def test_n_equal (self):
		a = CrankBase.VecBoolN.init_arr ([True, True])
		b = CrankBase.VecBoolN.init_arr ([True, True])
		c = CrankBase.VecBoolN.init_arr ([True, False])
		
		assert (    a.equal (b))
		assert (not a.equal (c))
	
	def test_n_hash (self):
		a = CrankBase.VecBoolN.init_arr ([True, True])
		b = CrankBase.VecBoolN.init_arr ([True, True])
		c = CrankBase.VecBoolN.init_arr ([True, False])
		
		self.assertEqual (a.hash (), b.hash ())
		self.assertNotEqual (a.hash (), c.hash ())
		
	def test_2_to_string (self):
		a = CrankBase.VecBool2.init_arr ([True, False, False, True])
		self.assertEqual (a.to_string(), "(true, false, false, true)")

if __name__ == '__main__':
	unittest.main ()
