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

import threading
import unittest


from gi.repository import GObject
from gi.repository import CrankBase



class TestSubjectA (CrankBase.Singular):
	int_item = GObject.property (type=int)
	
	def __init__ (self):
		CrankBase.Singular.__init__(self)


class TestSubjectB (CrankBase.Singular):
	pass


class TestSubjectC (CrankBase.Singular):
	pass


class TestSubjectD (CrankBase.Singular):
	first_construct_times = GObject.property (type=int, default=0)
	int_item = GObject.property (type=int)

	def do_first_construct(self):
		self.first_construct_times = self.first_construct_times + 1



class TestSingular(unittest.TestCase):

	def test_new (self):
		singular_a = TestSubjectA()
		singular_b = TestSubjectA()

		singular_b.int_item = 1
		singular_a.int_item = 3
		
		self.assertEqual (singular_a, singular_b)
		
		# two python object shares single CrankSingular, so same prop value
		self.assertEqual (singular_b.int_item, 3)
	
	
	def test_has (self):
		singular = TestSubjectB()
		self.assertTrue (CrankBase.Singular.has (TestSubjectB))
		
	def test_get (self):
		singular_b = TestSubjectB()
		singular_a = CrankBase.Singular.get(TestSubjectB);
		
		self.assertIsNotNone (singular_a);
	
	def test_first_construct(self):
		singular_a = TestSubjectD()
		self.assertEqual(singular_a.first_construct_times, 1)
		
		singular_b = TestSubjectD()
		self.assertEqual(singular_a.first_construct_times, 1)
		
	def test_thread_construct(self):
		threads = []
		singulars = []
		
		def thread_func ():
			s = TestSubjectC()
			singulars.append (s)
		
		for i in range(1000):
			threads.append(
				threading.Thread (None, thread_func)
				)
		
		for t in threads:
			t.start ()
		
		for t in threads:
			t.join ()
		
		for i in range(999):
			self.assertEqual (singulars[i], singulars[i+1])

if __name__ == '__main__':
	unittest.main ()
