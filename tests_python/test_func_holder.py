#!/usr/bin/python

import random
import unittest

from gi.repository import GObject
from gi.repository import CrankBase

class TestFuncHolder(unittest.TestCase):
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
		

if __name__ == '__main__':
	unittest.main ()
