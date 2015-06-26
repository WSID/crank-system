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

class TestDigraph(unittest.TestCase):

	def setUp (self):
		self.graph = CrankBase.Digraph ()

		self.nodes = []
		self.edges = []

		# The nodes are positioned According to below map. (lines are edges)
		#
		#    -5-4-3-2-1 0 1 2 3 4 5 6
		#  6                        0
		#  5                    ---/|
		#  4                ---/    |
		#  3              4/        |
		#  2    5-\       |\        |
		#  1   /   --\    2|        7
		#  0   |      --3/ |       /
		# -1   |     /   \ \      /
		# -2  /    /-     \ |   -/
		# -3  |  /-        \|  /
		# -4  |/-           \ /
		# -5  1-------------6/

		# 0 at (6, 6)
		self.nodes.append (self.graph.add (CrankBase.VecInt2.init (6, 6)))

		# 1 at (-5, -5)
		self.nodes.append (self.graph.add (CrankBase.VecInt2.init (-5, -5)))

		# 2 at (1, 1)
		self.nodes.append (self.graph.add (CrankBase.VecInt2.init (1, 1)))

		# 3 at (0, 0)
		self.nodes.append (self.graph.add (CrankBase.VecInt2.init (0, 0)))

		# 4 at (1, 3)
		self.nodes.append (self.graph.add (CrankBase.VecInt2.init (1, 3)))

		# 5 at (-4, 2)
		self.nodes.append (self.graph.add (CrankBase.VecInt2.init (-4, 2)))

		# 6 at (2, -5)
		self.nodes.append (self.graph.add (CrankBase.VecInt2.init (2, -5)))

		# 7 at (6, 1)
		self.nodes.append (self.graph.add (CrankBase.VecInt2.init (6, 1)))

		# edge for 0-4
		self.edges.append (self.graph.connect_void (self.nodes[0], self.nodes[4]))
		self.edges.append (self.graph.connect_void (self.nodes[4], self.nodes[0]))

		# edge for 0-7
		self.edges.append (self.graph.connect_void (self.nodes[0], self.nodes[7]))
		self.edges.append (self.graph.connect_void (self.nodes[7], self.nodes[0]))

		# edge for 1-3
		self.edges.append (self.graph.connect_void (self.nodes[1], self.nodes[3]))
		self.edges.append (self.graph.connect_void (self.nodes[3], self.nodes[1]))

		# edge for 1-5
		self.edges.append (self.graph.connect_void (self.nodes[1], self.nodes[5]))
		self.edges.append (self.graph.connect_void (self.nodes[5], self.nodes[1]))

		# edge for 1-6
		self.edges.append (self.graph.connect_void (self.nodes[1], self.nodes[6]))
		self.edges.append (self.graph.connect_void (self.nodes[6], self.nodes[1]))

		# edge for 2-3
		self.edges.append (self.graph.connect_void (self.nodes[2], self.nodes[3]))
		self.edges.append (self.graph.connect_void (self.nodes[3], self.nodes[2]))

		# edge for 2-4
		self.edges.append (self.graph.connect_void (self.nodes[2], self.nodes[4]))
		self.edges.append (self.graph.connect_void (self.nodes[4], self.nodes[2]))

		# edge for 2-5
		self.edges.append (self.graph.connect_void (self.nodes[2], self.nodes[5]))
		self.edges.append (self.graph.connect_void (self.nodes[5], self.nodes[2]))

		# edge for 3-6
		self.edges.append (self.graph.connect_void (self.nodes[3], self.nodes[6]))
		self.edges.append (self.graph.connect_void (self.nodes[6], self.nodes[3]))

		# edge for 4-6
		self.edges.append (self.graph.connect_void (self.nodes[4], self.nodes[6]))
		self.edges.append (self.graph.connect_void (self.nodes[6], self.nodes[4]))

		# edge for 6-7
		self.edges.append (self.graph.connect_void (self.nodes[6], self.nodes[7]))
		self.edges.append (self.graph.connect_void (self.nodes[7], self.nodes[6]))

	@staticmethod
	def edge_distance (e):
		node_v = GObject.Value (value_type=CrankBase.VecInt2)

		e.get_head().get_data (node_v);
		disp = node_v.get_boxed();

		e.get_tail().get_data (node_v);
		disp = disp.sub (node_v.get_boxed ());

		return disp.get_magn ();

	@staticmethod
	def heuristic (f, t):
		node_v = GObject.Value (value_type=CrankBase.VecInt2)

		t.get_data (node_v);
		disp = node_v.get_boxed();

		f.get_data (node_v);
		disp = disp.sub (node_v.get_boxed ());

		return disp.get_magn ();

	def test_dijkstra (self):
		path = CrankBase.dijkstra_digraph (self.nodes[0], self.nodes[1], self.edge_distance)

		self.assertEqual (path,
			[self.nodes[0],
			self.nodes[4],
			self.nodes[2],
			self.nodes[3],
			self.nodes[1]])

	@unittest.skip ("Current Python GI does not support callbacks more than 1.")
	def test_astar (self):
		path = CrankBase.astar_digraph (self.nodes[5], self.nodes[7], self.edge_distance, None, self.heuristic, None)

		self.assertEqual (path,
			[self.nodes[5],
			self.nodes[2],
			self.nodes[4],
			self.nodes[0],
			self.nodes[7]])


if __name__ == '__main__':
	unittest.main ()
