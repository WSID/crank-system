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
import enum

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
		
		self.ftype_int = CrankBase.FuncType.new_with_types(int, [int, int])
		self.ftype_float = CrankBase.FuncType.new_with_types(float, [float, float])
		self.ftype_string = CrankBase.FuncType.new_with_types(str, [str, str])
		
		self.holder.set (self.ftype_int,	lambda x,y: x+y)
		
		self.holder.set (self.ftype_float,	lambda x,y: x*y)
		
		self.holder.set (self.ftype_string,	lambda x,y: str(x)+str(y))

	def tearDown (self):
		self.holder = None;
	
	def test_name (self):
		self.assertEqual (self.holder.get_name (), "test-holder");
		
		self.holder.set_name ("another-holder");
		
		self.assertEqual (self.holder.get_name (), "another-holder");

	def test_get (self):
		closure_int = self.holder.get (self.ftype_int)
		closure_float = self.holder.get (self.ftype_float)
		closure_string = self.holder.get (self.ftype_string)

		value = GObject.Value (value_type=int)
		closure_int.invoke (value, [2, 6], None)
		self.assertEqual (value.get_int (), 8)

		value = GObject.Value (value_type=float)
		closure_float.invoke (value, [6, 2.5], None)
		self.assertEqual (value.get_double (), 15.0)

		value = GObject.Value (value_type=str)
		closure_string.invoke (value, ["asdf", "qwer"], None)
		self.assertEqual (value.get_string (), "asdfqwer")
		
	def test_get_by_param_types (self):
		closure_int = self.holder.get_by_param_types ([int, int])
		closure_float = self.holder.get_by_param_types ([float, float])
		closure_string = self.holder.get_by_param_types ([str, str])

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
		assert (self.holder.remove (self.ftype_int))
		assert (self.holder.remove (self.ftype_float))
		assert (self.holder.remove (self.ftype_string))
		assert (not self.holder.remove (self.ftype_int))

	def test_remove_by_param_types (self):
		assert (self.holder.remove_by_param_types ([int, int]))
		assert (self.holder.remove_by_param_types ([float, float]))
		assert (self.holder.remove_by_param_types ([str, str]))
		assert (not self.holder.remove_by_param_types ([float, float]))
		
	def test_lookup_return_type (self):
		self.assertEqual (self.holder.lookup_return_type ([int, int]),
							GObject.GType (int))
		self.assertEqual (self.holder.lookup_return_type ([float, float]),
							GObject.GType (float))
		self.assertEqual (self.holder.lookup_return_type ([str, str]),
							GObject.GType (str))

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

class TestFuncBookEnum (enum.IntEnum):
	add = 0
	mul = 1
	neg = 2

class TestFuncBook (unittest.TestCase):
	def setUp (self):
		self.book = CrankBase.FuncBook.new_with_name ("test-book")
		self.holder_add = CrankBase.FuncHolder ("add")
		self.holder_mul = CrankBase.FuncHolder ("mul")
		self.holder_neg = CrankBase.FuncHolder ("neg")
		
		self.book.set (TestFuncBookEnum.add, self.holder_add)
		self.book.set (TestFuncBookEnum.mul, self.holder_mul)
		self.book.set (TestFuncBookEnum.neg, self.holder_neg)
		
		ftype_i_ii = CrankBase.FuncType.new_with_types (int, [int, int])
		ftype_f_ff = CrankBase.FuncType.new_with_types (float, [float, float])
		
		ftype_i_i = CrankBase.FuncType.new_with_types (int, [int])
		ftype_f_f = CrankBase.FuncType.new_with_types (float, [float])
		
		adder = lambda x,y: x+y
		muler = lambda x,y: x*y
		neger = lambda x: -x
		
		self.holder_add.set (ftype_i_ii, adder)
		self.holder_add.set (ftype_f_ff, adder)
		
		self.holder_mul.set (ftype_i_ii, muler)
		self.holder_mul.set (ftype_f_ff, muler)
		
		self.holder_neg.set (ftype_i_i, neger)
		self.holder_neg.set (ftype_f_f, neger)
	
	def test_get_name (self):
		self.assertEqual (self.book.get_name (), "test-book")
		
		self.book.set_name ("necronomicon")		
		self.assertEqual (self.book.get_name (), "necronomicon")
	
	def test_get (self):
		self.assertEqual (self.book.get (TestFuncBookEnum.add), self.holder_add)
		self.assertEqual (self.book.get (TestFuncBookEnum.mul), self.holder_mul)
		self.assertEqual (self.book.get (TestFuncBookEnum.neg), self.holder_neg)	
		
	def test_index_of (self):
		self.assertEqual (self.book.index_of (self.holder_add), TestFuncBookEnum.add)
		self.assertEqual (self.book.index_of (self.holder_mul), TestFuncBookEnum.mul)
		self.assertEqual (self.book.index_of (self.holder_neg), TestFuncBookEnum.neg)
		
	def test_get_by_name (self):
		self.assertEqual (self.book.get_by_name ("add"), self.holder_add)
		self.assertEqual (self.book.get_by_name ("mul"), self.holder_mul)
		self.assertEqual (self.book.get_by_name ("neg"), self.holder_neg)
	
	def test_remove (self):
		assert (self.book.remove (TestFuncBookEnum.add))
		assert (self.book.remove (TestFuncBookEnum.mul))
		assert (self.book.remove (TestFuncBookEnum.neg))
		assert (not self.book.remove (TestFuncBookEnum.add))
		
		self.assertIsNone (self.book.get (TestFuncBookEnum.add))
		self.assertIsNone (self.book.get (TestFuncBookEnum.mul))
		self.assertIsNone (self.book.get (TestFuncBookEnum.neg))
		
	def test_remove_by_name (self):
		assert (self.book.remove_by_name ("add"))
		assert (self.book.remove_by_name ("mul"))
		assert (self.book.remove_by_name ("neg"))
		assert (not self.book.remove_by_name ("add"))
		
		self.assertIsNone (self.book.get (TestFuncBookEnum.add))
		self.assertIsNone (self.book.get (TestFuncBookEnum.mul))
		self.assertIsNone (self.book.get (TestFuncBookEnum.neg))
	
	def test_invoke (self):
		ret = GObject.Value (value_type=int)
		
		assert (self.book.invoke (TestFuncBookEnum.add, ret, [13, 57], None))
		self.assertEqual (ret.get_int (), 13 + 57)
		
		assert (self.book.invoke (TestFuncBookEnum.mul, ret, [13, 57], None))
		self.assertEqual (ret.get_int (), 13 * 57)
		
		assert (self.book.invoke (TestFuncBookEnum.neg, ret, [42], None))
		self.assertEqual (ret.get_int (), -42)
		
		
		
		ret = GObject.Value (value_type=float)
		
		assert (self.book.invoke (TestFuncBookEnum.add, ret, [13.0, 57.0], None))
		self.assertEqual (ret.get_double (), 13.0 + 57.0)
		
		assert (self.book.invoke (TestFuncBookEnum.mul, ret, [13.0, 57.0], None))
		self.assertEqual (ret.get_double (), 13.0 * 57.0)
		
		assert (self.book.invoke (TestFuncBookEnum.neg, ret, [74.0], None))
		self.assertEqual (ret.get_double (), -74.0)
		
		
		
	def test_invoke_name (self):
		ret = GObject.Value (value_type=int)
		
		assert (self.book.invoke_name ("add", ret, [13, 57], None))
		self.assertEqual (ret.get_int (), 13 + 57)
		
		assert (self.book.invoke_name ("mul", ret, [13, 57], None))
		self.assertEqual (ret.get_int (), 13 * 57)
		
		assert (self.book.invoke_name ("neg", ret, [42], None))
		self.assertEqual (ret.get_int (), -42)
		
		
		
		ret = GObject.Value (value_type=float)
		
		assert (self.book.invoke_name ("add", ret, [13.0, 57.0], None))
		self.assertEqual (ret.get_double (), 13.0 + 57.0)
		
		assert (self.book.invoke_name ("mul", ret, [13.0, 57.0], None))
		self.assertEqual (ret.get_double (), 13.0 * 57.0)
		
		assert (self.book.invoke_name ("neg", ret, [74.0], None))
		self.assertEqual (ret.get_double (), -74.0)

if __name__ == '__main__':
	random.seed ()
	unittest.main ()
