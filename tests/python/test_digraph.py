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
		
		self.nodes = [self.graph.add (i) for i in range (9)]
		self.edges = []
		
		# 0
		
		# 1->2, 1->3, 2->3
		self.edges.append (self.graph.connect (self.nodes[1], self.nodes[2], 17.3))
		self.edges.append (self.graph.connect (self.nodes[1], self.nodes[3], 32.1))
		self.edges.append (self.graph.connect (self.nodes[2], self.nodes[3], 18.3))
		
		# 4->5, 4->6, 4->7, 5->8, 7->6
		self.edges.append (self.graph.connect (self.nodes[4], self.nodes[5], 21.3))
		self.edges.append (self.graph.connect (self.nodes[4], self.nodes[6], 10.5))
		self.edges.append (self.graph.connect (self.nodes[4], self.nodes[7], 17.5))
		self.edges.append (self.graph.connect (self.nodes[5], self.nodes[8], 9.4))
		self.edges.append (self.graph.connect (self.nodes[7], self.nodes[6], 19.6))

	def test_get_nodes (self):
		self.assertEqual (self.graph.get_nodes (), self.nodes)
	
	def test_get_edges (self):
		self.assertEqual (self.graph.get_edges (), self.edges)
	
	def test_disconnect (self):
		assert (self.graph.disconnect (self.nodes[2], self.nodes[3]))
		assert (self.graph.disconnect (self.nodes[4], self.nodes[6]))
		
		assert (not self.graph.disconnect (self.nodes[0], self.nodes[1]))
		assert (not self.graph.disconnect (self.nodes[6], self.nodes[7]))
		assert (not self.graph.disconnect (self.nodes[4], self.nodes[8]))
		assert (not self.graph.disconnect (self.nodes[4], self.nodes[6]))
	
		edge_list = self.graph.get_edges ();
		
		assert (not (self.edges[2] in edge_list))
		assert (not (self.edges[4] in edge_list))
	
	def test_disconnect_edge (self):
		self.graph.disconnect_edge (self.edges[2])
		self.graph.disconnect_edge (self.edges[4])
		
		edge_list = self.graph.get_edges ();
		
		assert (not (self.edges[2] in edge_list))
		assert (not (self.edges[4] in edge_list))

	def test_node_get_data (self):
		node_v = GObject.Value (value_type=int)
		
		for i in range (9):
			self.nodes[i].get_data (node_v)
			self.assertEqual (node_v.get_int (), i)
	
	def test_node_get_in_edges (self):
		self.assertEqual (
				self.nodes[3].get_in_edges (),
				[self.edges[1], self.edges[2]]
		)
	
	def test_node_get_out_edges (self):
		self.assertEqual (
				self.nodes[4].get_out_edges (),
				[self.edges[3], self.edges[4], self.edges[5]]
		)
	
	def test_node_get_in_nodes (self):
		self.assertEqual (
				self.nodes[3].get_in_nodes (),
				[self.nodes[1], self.nodes[2]]
		)
	
	def test_node_get_indegree (self):
		self.assertEqual (self.nodes[2].get_indegree (), 1)
		self.assertEqual (self.nodes[5].get_indegree (), 1)
		self.assertEqual (self.nodes[6].get_indegree (), 2)

	def test_node_get_outdegree (self):
		self.assertEqual (self.nodes[2].get_outdegree (), 1)
		self.assertEqual (self.nodes[5].get_outdegree (), 1)
		self.assertEqual (self.nodes[6].get_outdegree (), 0)
	
	def test_node_is_adjacent (self):
		assert (self.nodes[2].is_adjacent (self.nodes[3]))
		assert (self.nodes[4].is_adjacent (self.nodes[6]))
		
		assert (self.nodes[6].is_adjacent (self.nodes[7]))
		
		assert (not self.nodes[0].is_adjacent (self.nodes[2]))
		assert (not self.nodes[4].is_adjacent (self.nodes[8]))
	
	def test_node_is_adjacent_from (self):
		assert (self.nodes[3].is_adjacent_from (self.nodes[2]))
		assert (self.nodes[6].is_adjacent_from (self.nodes[4]))
		
		assert (not self.nodes[7].is_adjacent_from (self.nodes[6]))
		
		assert (not self.nodes[2].is_adjacent_from (self.nodes[3]))
		assert (not self.nodes[8].is_adjacent_from (self.nodes[8]))
	
	def test_node_is_adjacent_to (self):
		assert (self.nodes[2].is_adjacent_to (self.nodes[3]))
		assert (self.nodes[4].is_adjacent_to (self.nodes[6]))
		
		assert (not self.nodes[6].is_adjacent_to (self.nodes[7]))
		
		assert (not self.nodes[0].is_adjacent_to (self.nodes[2]))
		assert (not self.nodes[4].is_adjacent_to (self.nodes[8]))

	def test_node_foreach_depth (self):
		
		iter_nodes = []
		
		def accum (n):
			iter_nodes.append (n)
			return True
	
	
		self.nodes[0].foreach_depth (accum)
		self.assertEqual (iter_nodes, [self.nodes[0]]);
		
		iter_nodes = []
		self.nodes[1].foreach_depth (accum)
		self.assertEqual (iter_nodes,
				[self.nodes[1],
				self.nodes[3],
				self.nodes[2]]	)
				
		iter_nodes = []
		self.nodes[4].foreach_depth (accum)
		self.assertEqual (iter_nodes,
				[self.nodes[4],
				self.nodes[7],
				self.nodes[6],
				self.nodes[5],
				self.nodes[8]]	)
				
	def test_node_foreach_breadth (self):
		
		iter_nodes = []
		
		def accum (n):
			iter_nodes.append (n)
			return True
	
	
		self.nodes[0].foreach_breadth (accum)
		self.assertEqual (iter_nodes, [self.nodes[0]]);
		
		iter_nodes = []
		self.nodes[1].foreach_breadth (accum)
		self.assertEqual (iter_nodes,
				[self.nodes[1],
				self.nodes[2],
				self.nodes[3]]	)
				
		iter_nodes = []
		self.nodes[4].foreach_breadth (accum)
		self.assertEqual (iter_nodes,
				[self.nodes[4],
				self.nodes[5],
				self.nodes[6],
				self.nodes[7],
				self.nodes[8]]	)

	def test_edge_get_data (self):
		edge_v = GObject.Value (value_type=float)
		
		self.edges[5].get_data (edge_v);
		
		self.assertEqual (edge_v.get_double (), 17.5)
	
	def test_edge_get_tail (self):
		self.assertEqual (self.edges[3].get_tail (), self.nodes[4])
		self.assertEqual (self.edges[5].get_tail (), self.nodes[4])
		self.assertEqual (self.edges[7].get_tail (), self.nodes[7])
	
	def test_edge_get_head (self):
		self.assertEqual (self.edges[1].get_head (), self.nodes[3])
		self.assertEqual (self.edges[2].get_head (), self.nodes[3])
		self.assertEqual (self.edges[4].get_head (), self.nodes[6])
	
if __name__ == '__main__':
	unittest.main ()
