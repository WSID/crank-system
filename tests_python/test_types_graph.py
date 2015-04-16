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

class TestA (GObject.Object):
	pass

class TestB (TestA):
	pass
	
class TestC (TestB):
	pass
	
class TestD (TestB):
	pass

class TestE (TestA):
	pass

class TestX (GObject.Object):
	pass


class TestTypesGraph(unittest.TestCase):
	key1_a = [TestA];
	key1_b = [TestB];
	key1_c = [TestC];
	key1_d = [TestD];
	key1_e = [TestE];
	key1_x = [TestX];
	
	key2_aa = [TestA, TestA];
	key2_ab = [TestA, TestB];
	key2_ad = [TestA, TestD];
	key2_ae = [TestA, TestE];
	key2_bc = [TestB, TestC];
	key2_ca = [TestC, TestA];
	key2_ce = [TestC, TestE];
	key2_ea = [TestE, TestA];
	key2_ed = [TestE, TestD];
	key2_ax = [TestA, TestX];
	key2_xa = [TestX, TestA];

	def assertTypes (self, a, b):
		if (a == None):
			if (b == None):	return True
			else:			return False
		if (b == None):
			return False
		
		A = [GObject.GType (e) for e in a]
		B = [GObject.GType (e) for e in b]
		
		self.assertEqual (A, B);
	

	def setUp (self):
		self.graph = CrankBase.TypesGraph ()
		
		self.graph.set (self.key1_a, "Value for A");
		self.graph.set (self.key1_d, "Value for D");
		self.graph.set (self.key1_e, "Value for E");
		
		self.graph.set (self.key2_aa, "Value for AA");
		self.graph.set (self.key2_ad, "Value for AD");
		self.graph.set (self.key2_ae, "Value for AE");
		self.graph.set (self.key2_ea, "Value for EA");
		self.graph.set (self.key2_ed, "Value for ED");

	def test_get (self):
		value = GObject.Value (value_type=str)
		
		self.assertTrue (self.graph.get (self.key1_a, value))
		self.assertEqual (value.get_string (), "Value for A")
		self.assertFalse (self.graph.get (self.key1_b, value))
		
		self.assertFalse (self.graph.get (self.key1_c, value))
		
		self.assertTrue (self.graph.get (self.key1_d, value))
		self.assertEqual (value.get_string (), "Value for D")
		self.assertTrue (self.graph.get (self.key1_e, value))
		self.assertEqual (value.get_string (), "Value for E")
		self.assertFalse (self.graph.get (self.key1_x, value))
		
		
		self.assertTrue (self.graph.get (self.key2_aa, value))
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertFalse (self.graph.get (self.key2_ab, value))
		
		self.assertTrue (self.graph.get (self.key2_ad, value))
		self.assertEqual (value.get_string (), "Value for AD")
		self.assertTrue (self.graph.get (self.key2_ae, value))
		self.assertEqual (value.get_string (), "Value for AE")
		self.assertFalse (self.graph.get (self.key2_bc, value))
		
		self.assertFalse (self.graph.get (self.key2_ca, value))
		
		self.assertFalse (self.graph.get (self.key2_ce, value))
		
		self.assertTrue (self.graph.get (self.key2_ea, value))
		self.assertEqual (value.get_string (), "Value for EA")
		self.assertTrue (self.graph.get (self.key2_ed, value))
		self.assertEqual (value.get_string (), "Value for ED")
		self.assertFalse (self.graph.get (self.key2_ax, value))
		
		self.assertFalse (self.graph.get (self.key2_xa, value))

	def test_has (self):
		self.assertTrue (self.graph.has (self.key1_a));
		self.assertFalse (self.graph.has (self.key1_b));
		self.assertFalse (self.graph.has (self.key1_c));
		self.assertTrue (self.graph.has (self.key1_d));
		self.assertTrue (self.graph.has (self.key1_e));
		self.assertFalse (self.graph.has (self.key1_x));
		
		self.assertTrue (self.graph.has (self.key2_aa));
		self.assertFalse (self.graph.has (self.key2_ab));
		self.assertTrue (self.graph.has (self.key2_ad));
		self.assertTrue (self.graph.has (self.key2_ae));
		self.assertFalse (self.graph.has (self.key2_bc));
		self.assertFalse (self.graph.has (self.key2_ca));
		self.assertFalse (self.graph.has (self.key2_ce));
		self.assertTrue (self.graph.has (self.key2_ea));
		self.assertTrue (self.graph.has (self.key2_ed));
		self.assertFalse (self.graph.has (self.key2_ax));
		self.assertFalse (self.graph.has (self.key2_xa));
	
	def test_lookup (self):
		value = GObject.Value (value_type=str)
		
		self.assertTrue (self.graph.lookup (self.key1_a, value))
		self.assertEqual (value.get_string (), "Value for A")
		self.assertTrue (self.graph.lookup (self.key1_b, value))
		self.assertEqual (value.get_string (), "Value for A")
		self.assertTrue (self.graph.lookup (self.key1_c, value))
		self.assertEqual (value.get_string (), "Value for A")
		self.assertTrue (self.graph.lookup (self.key1_d, value))
		self.assertEqual (value.get_string (), "Value for D")
		self.assertTrue (self.graph.lookup (self.key1_e, value))
		self.assertEqual (value.get_string (), "Value for E")
		self.assertFalse (self.graph.lookup (self.key1_x, value))
		
		self.assertTrue (self.graph.lookup (self.key2_aa, value))
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertTrue (self.graph.lookup (self.key2_ab, value))
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertTrue (self.graph.lookup (self.key2_ad, value))
		self.assertEqual (value.get_string (), "Value for AD")
		self.assertTrue (self.graph.lookup (self.key2_ae, value))
		self.assertEqual (value.get_string (), "Value for AE")
		self.assertTrue (self.graph.lookup (self.key2_bc, value))
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertTrue (self.graph.lookup (self.key2_ca, value))
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertTrue (self.graph.lookup (self.key2_ce, value))
		self.assertEqual (value.get_string (), "Value for AE")
		self.assertTrue (self.graph.lookup (self.key2_ea, value))
		self.assertEqual (value.get_string (), "Value for EA")
		self.assertTrue (self.graph.lookup (self.key2_ed, value))
		self.assertEqual (value.get_string (), "Value for ED")
		
		self.assertFalse (self.graph.lookup (self.key2_ax, value))
		self.assertFalse (self.graph.lookup (self.key2_xa, value))
		
	def test_lookup_types (self):
		self.assertTypes (self.graph.lookup_types (self.key1_a), self.key1_a)
		self.assertTypes (self.graph.lookup_types (self.key1_b), self.key1_a)
		self.assertTypes (self.graph.lookup_types (self.key1_c), self.key1_a)
		self.assertTypes (self.graph.lookup_types (self.key1_d), self.key1_d)
		self.assertTypes (self.graph.lookup_types (self.key1_e), self.key1_e)
		self.assertTypes (self.graph.lookup_types (self.key1_x), None)
		
		self.assertTypes (self.graph.lookup_types (self.key2_aa), self.key2_aa)
		self.assertTypes (self.graph.lookup_types (self.key2_ab), self.key2_aa)
		self.assertTypes (self.graph.lookup_types (self.key2_ad), self.key2_ad)
		self.assertTypes (self.graph.lookup_types (self.key2_ae), self.key2_ae)
		self.assertTypes (self.graph.lookup_types (self.key2_bc), self.key2_aa)
		self.assertTypes (self.graph.lookup_types (self.key2_ca), self.key2_aa)
		self.assertTypes (self.graph.lookup_types (self.key2_ce), self.key2_ae)
		self.assertTypes (self.graph.lookup_types (self.key2_ea), self.key2_ea)
		self.assertTypes (self.graph.lookup_types (self.key2_ed), self.key2_ed)
		self.assertTypes (self.graph.lookup_types (self.key2_ax), None)
		self.assertTypes (self.graph.lookup_types (self.key2_xa), None)
		
	def test_lookup_full (self):
		value = GObject.Value (value_type=str)
		
		lookup = self.graph.lookup_full (self.key1_a, value)
		self.assertEqual (value.get_string (), "Value for A")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key1_a)
		
		lookup = self.graph.lookup_full (self.key1_b, value)
		self.assertEqual (value.get_string (), "Value for A")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key1_a)
		
		lookup = self.graph.lookup_full (self.key1_c, value)
		self.assertEqual (value.get_string (), "Value for A")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key1_a)
		
		lookup = self.graph.lookup_full (self.key1_d, value)
		self.assertEqual (value.get_string (), "Value for D")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key1_d)
		
		lookup = self.graph.lookup_full (self.key1_e, value)
		self.assertEqual (value.get_string (), "Value for E")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key1_e)
		
		lookup = self.graph.lookup_full (self.key1_x, value)
		self.assertFalse (lookup[0])
		self.assertTypes (lookup[1], None)
		
		
		lookup = self.graph.lookup_full (self.key2_aa, value)
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_aa)
		
		lookup = self.graph.lookup_full (self.key2_ab, value)
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_aa)
		
		lookup = self.graph.lookup_full (self.key2_ad, value)
		self.assertEqual (value.get_string (), "Value for AD")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_ad)
		
		lookup = self.graph.lookup_full (self.key2_ae, value)
		self.assertEqual (value.get_string (), "Value for AE")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_ae)
		
		lookup = self.graph.lookup_full (self.key2_bc, value)
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_aa)
		
		lookup = self.graph.lookup_full (self.key2_ca, value)
		self.assertEqual (value.get_string (), "Value for AA")
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_aa)
		
		lookup = self.graph.lookup_full (self.key2_ce, value)
		self.assertEqual (value.get_string (), "Value for AE");
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_ae)
		
		lookup = self.graph.lookup_full (self.key2_ea, value)
		self.assertEqual (value.get_string (), "Value for EA");
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_ea)
		
		lookup = self.graph.lookup_full (self.key2_ed, value)
		self.assertEqual (value.get_string (), "Value for ED");
		self.assertTrue (lookup[0])
		self.assertTypes (lookup[1], self.key2_ed)
		
		lookup = self.graph.lookup_full (self.key2_ax, value)
		self.assertFalse (lookup[0])
		self.assertTypes (lookup[1], None)
		
		lookup = self.graph.lookup_full (self.key2_xa, value)
		self.assertFalse (lookup[0])
		self.assertTypes (lookup[1], None)
	
	def test_remove (self):
		self.assertTrue (self.graph.remove (self.key1_d))
		self.assertTrue (self.graph.remove (self.key1_a))
		self.assertTrue (self.graph.remove (self.key1_e))
		self.assertFalse (self.graph.remove (self.key1_b))
		self.assertFalse (self.graph.remove (self.key1_c))
		self.assertFalse (self.graph.remove (self.key1_x))
		
		self.assertTrue (self.graph.remove (self.key2_aa))
		self.assertFalse (self.graph.remove (self.key2_ab))
		self.assertTrue (self.graph.remove (self.key2_ad))
		self.assertTrue (self.graph.remove (self.key2_ae))
		self.assertFalse (self.graph.remove (self.key2_bc))
		self.assertFalse (self.graph.remove (self.key2_ca))
		self.assertFalse (self.graph.remove (self.key2_ce))
		self.assertTrue (self.graph.remove (self.key2_ea))
		self.assertTrue (self.graph.remove (self.key2_ed))
		self.assertFalse (self.graph.remove (self.key2_ax))
		self.assertFalse (self.graph.remove (self.key2_xa))

if __name__ == '__main__':
	unittest.main ()
