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

import random
import unittest

from gi.repository import GObject
from gi.repository import CrankBase

class TestFuncType(unittest.TestCase):
	_py_type_pool = [bool, int, long, float, str]

	def test_new (self):
		ftype = CrankBase.FuncType.new_with_types (bool, [int, str])
		
		self.assertEqual (GObject.GType(bool), ftype.get_return_type())
		self.assertEqual (GObject.GType(int), ftype.get_param_type(0))
		self.assertEqual (GObject.GType(str), ftype.get_param_type(1))
		self.assertEqual (GObject.GType(None), ftype.get_param_type(2))
		
		self.assertEqual (2, ftype.get_nparam_types ())
		
		param_types = ftype.get_param_types ()
		
		self.assertListEqual ([GObject.GType(pt) for pt in [int, str]], param_types)
	
	def test_hash (self):
		r_type = random.choice (self._py_type_pool);
		p_types = random.sample (self._py_type_pool, random.randint (0, 4));
		
		ftype_a = CrankBase.FuncType.new_with_types (r_type, p_types);
		ftype_b = CrankBase.FuncType.new_with_types (r_type, p_types);
		
		hash_a = ftype_a.hash ();
		hash_b = ftype_b.hash ();
		
		self.assertEqual (hash_a, hash_b);
	
	def test_equal (self):
		r_type = random.choice (self._py_type_pool);
		p_types = random.sample (self._py_type_pool, random.randint (0, 4));
		
		ftype_a = CrankBase.FuncType.new_with_types (r_type, p_types);
		ftype_b = CrankBase.FuncType.new_with_types (r_type, p_types);
		
		self.assertTrue (ftype_a.equal (ftype_b))
	
	def test_to_string (self):
		ftype = CrankBase.FuncType.new_with_types (bool, [int, str]);
		
		self.assertEqual (ftype.to_string(), "gboolean (gint, gchararray)")
	
	def test_compatible_to (self):
		ftype_from = CrankBase.FuncType.new_with_types (GObject.Binding, [GObject.Object])
		ftype_to = CrankBase.FuncType.new_with_types (GObject.Object, [GObject.Binding])
		
		self.assertTrue (ftype_from.compatible_to (ftype_to));
	
	def test_compatible_to_param_size (self):
		ftype_from = CrankBase.FuncType.new_with_types (bool, [int])
		ftype_to = CrankBase.FuncType.new_with_types (bool, [int, int])
		
		self.assertTrue (ftype_from.compatible_to (ftype_to));
		
		
	def test_arg_match_exactually (self):
		ftype = CrankBase.FuncType.new_with_types (bool, [int, float])
		
		self.assertTrue (ftype.arg_match_exactually ([int, float]))
		self.assertFalse(ftype.arg_match_exactually ([int, int]))
		self.assertFalse(ftype.arg_match_exactually ([int]))
		self.assertFalse(ftype.arg_match_exactually ([int, float, int]))
		
	
	def test_arg_match (self):
		ftype = CrankBase.FuncType.new_with_types (bool, [GObject.Object, int])
		
		self.assertTrue (ftype.arg_match ([GObject.Object, int]))
		self.assertFalse(ftype.arg_match ([int, float]))
		self.assertTrue (ftype.arg_match ([GObject.Binding, int]))
	
	def test_arg_match_transformable (self):
		ftype = CrankBase.FuncType.new_with_types (bool, [GObject.Object, int])
		
		self.assertTrue (ftype.arg_match_transformable ([GObject.Object, int]))
		self.assertTrue (ftype.arg_match_transformable ([GObject.Object, float]))
		self.assertTrue (ftype.arg_match_transformable ([GObject.Binding, float]))
		self.assertFalse(ftype.arg_match_transformable ([str, float]))

class TestFuncHolder (unittest.TestCase):
	def setUp (self):
		self.holder = CrankBase.FuncHolder ("test-holder")
		self.holder.set ([int, int], lambda x,y: x+y)
		self.holder.set ([float, float], lambda x,y: x*y)
		self.holder.set ([str, str], lambda x,y: str(x)+str(y))

	def tearDown (self):
		self.holder = None;
	
	def test_name (self):
		self.assertEqual (self.holder.get_name (), "test-holder");
		
		self.holder.set_name ("another-holder");
		
		self.assertEqual (self.holder.get_name (), "another-holder");

	def test_get (self):
		closure_int = self.holder.get ([int, int])
		closure_float = self.holder.get ([float, float])
		closure_string = self.holder.get ([str, str])

		value = GObject.Value (value_type=int)
		closure_int.invoke (value, [2, 6], None)
		self.assertEqual (value.get_int (), 8)

		value = GObject.Value (value_type=float)
		closure_float.invoke (value, [6, 2.5], None)
		self.assertEqual (value.get_double (), 15.0)

		value = GObject.Value (value_type=str)
		closure_string.invoke (value, ["asdf", "qwer"], None)
		self.assertEqual (value.get_string (), "asdfqwer")


	def test_remove (self):
		assert (self.holder.remove ([int, int]))
		assert (self.holder.remove ([float, float]))
		assert (self.holder.remove ([str, str]))
		assert (not self.holder.remove ([float, float]))

	def test_invoke(self):
		value = GObject.Value (value_type=int)
		assert (self.holder.invoke (value, [2, 4], None))
		self.assertEqual (value.get_int(), 6)

		value = GObject.Value (value_type=float)
		assert (self.holder.invoke (value, [2.5, 4.0], None))
		self.assertEqual (value.get_double(), 10.0)

		value = GObject.Value (value_type=str)
		assert (self.holder.invoke (value, ["Take My ", "Money"], None))
		self.assertEqual (value.get_string(), "Take My Money")

if __name__ == '__main__':
	random.seed ()
	unittest.main ()
