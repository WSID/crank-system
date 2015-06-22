/* Copyright (C) 2015, WSID   */

/* This file is part of Crank System.
 *
 *  Crank System is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  Crank System is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with Crank System.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

private struct TestDigraphFixture {
	Crank.Digraph					graph;
	(unowned Crank.DigraphNode)[]	nodes;
	(unowned Crank.DigraphEdge)[]	edges;
	
	public TestDigraphFixture () {
		graph = new Crank.Digraph ();
		
		nodes = new (unowned Crank.DigraphNode)[9];
		edges = new (unowned Crank.DigraphEdge)[8];
		
		for (int i = 0 ; i < 9; i++) nodes[i] = graph.add (i);
		
		// 0
		
		// 1->2, 1->3, 2->3
		
		edges[0] = graph.connect (nodes[1], nodes[2], 17.3f);
		edges[1] = graph.connect (nodes[1], nodes[3], 32.1f);
		edges[2] = graph.connect (nodes[2], nodes[3], 18.3f);
		
		// 4->5, 4->6, 4->7, 5->8, 7->6
		
		edges[3] = graph.connect (nodes[4], nodes[5], 21.3f);
		edges[4] = graph.connect (nodes[4], nodes[6], 10.5f);
		edges[5] = graph.connect (nodes[4], nodes[7], 17.5f);
		edges[6] = graph.connect (nodes[5], nodes[8], 9.4f);
		edges[7] = graph.connect (nodes[7], nodes[6], 19.6f);
	}
}

int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func ("/crank/base/digraph/node", test_digraph_get_nodes);
	GLib.Test.add_func ("/crank/base/digraph/edge", test_digraph_get_edges);
	GLib.Test.add_func ("/crank/base/digraph/disconnect", test_digraph_disconnect);
	GLib.Test.add_func ("/crank/base/digraph/disconnect/edge", test_digraph_disconnect_edge);
	
	GLib.Test.add_func ("/crank/base/digraph/node/data", test_digraph_node_get_data);
	GLib.Test.add_func ("/crank/base/digraph/node/in/edge", test_digraph_node_get_in_edges);
	GLib.Test.add_func ("/crank/base/digraph/node/out/edge", test_digraph_node_get_out_edges);
	GLib.Test.add_func ("/crank/base/digraph/node/in/node", test_digraph_node_get_in_nodes);
	GLib.Test.add_func ("/crank/base/digraph/node/out/node", test_digraph_node_get_out_nodes);
	GLib.Test.add_func ("/crank/base/digraph/node/in/degree", test_digraph_node_get_indegree);
	GLib.Test.add_func ("/crank/base/digraph/node/out/degree", test_digraph_node_get_outdegree);
	GLib.Test.add_func ("/crank/base/digraph/node/adjacent", test_digraph_node_is_adjacent);
	GLib.Test.add_func ("/crank/base/digraph/node/adjacent/from", test_digraph_node_is_adjacent_from);
	GLib.Test.add_func ("/crank/base/digraph/node/adjacent/to", test_digraph_node_is_adjacent_to);
	GLib.Test.add_func ("/crank/base/digraph/node/foreach/depth", test_digraph_node_foreach_depth);
	GLib.Test.add_func ("/crank/base/digraph/node/foreach/breadth", test_digraph_node_foreach_breadth);
	
	GLib.Test.add_func ("/crank/base/digraph/edge/data", test_digraph_edge_get_data);
	GLib.Test.add_func ("/crank/base/digraph/edge/tail", test_digraph_edge_get_tail);
	GLib.Test.add_func ("/crank/base/digraph/edge/head", test_digraph_edge_get_head);
			
	GLib.Test.run ();
	
	return 0;
}

private void test_digraph_get_nodes () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	unowned GLib.GenericArray<Crank.DigraphNode> nodes = fixture.graph.nodes;
	
	foreach (unowned Crank.DigraphNode node in fixture.nodes)
		assert (node in nodes.data);
}


private void test_digraph_get_edges () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	unowned GLib.GenericArray<Crank.DigraphEdge> edges = fixture.graph.edges;
	
	foreach (unowned Crank.DigraphEdge edge in fixture.edges)
		assert (edge in edges.data);
}

private void test_digraph_disconnect () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	assert (  fixture.graph.disconnect (fixture.nodes[2], fixture.nodes[3]) );
	assert (  fixture.graph.disconnect (fixture.nodes[4], fixture.nodes[6]) );
	assert (! fixture.graph.disconnect (fixture.nodes[0], fixture.nodes[1]) );
	assert (! fixture.graph.disconnect (fixture.nodes[6], fixture.nodes[7]) );
	assert (! fixture.graph.disconnect (fixture.nodes[4], fixture.nodes[8]) );
	assert (! fixture.graph.disconnect (fixture.nodes[4], fixture.nodes[6]) );
	
	unowned GLib.GenericArray<Crank.DigraphEdge>	edges = fixture.graph.edges;
	
	assert (! (fixture.edges[2] in edges.data));
	assert (! (fixture.edges[4] in edges.data));
}


private void test_digraph_disconnect_edge () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	fixture.graph.disconnect_edge (fixture.edges[2]);
	fixture.graph.disconnect_edge (fixture.edges[4]);
	
	unowned GLib.GenericArray<Crank.DigraphEdge> edges = fixture.graph.edges;
	
	assert (! (fixture.edges[2] in edges.data));
	assert (! (fixture.edges[4] in edges.data));
}

private void test_digraph_node_get_data () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	GLib.Value node_v = GLib.Value (typeof (int));
	
	for (int i = 0; i < 9; i++) {
		fixture.nodes[i].get_data (ref node_v);
		assert (node_v.get_int () == i);
	}
}

private void test_digraph_node_get_in_edges () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	unowned GLib.GenericArray <unowned Crank.DigraphEdge> edges =
			fixture.nodes[3].in_edges;
	
	assert (fixture.edges[1] in edges.data);
	assert (fixture.edges[2] in edges.data);
}

private void test_digraph_node_get_out_edges () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	unowned GLib.GenericArray <unowned Crank.DigraphEdge> edges =
			fixture.nodes[4].out_edges;
	
	assert (fixture.edges[3] in edges.data);
	assert (fixture.edges[4] in edges.data);
	assert (fixture.edges[5] in edges.data);
}

private void test_digraph_node_get_in_nodes () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	GLib.List <unowned Crank.DigraphNode> nodes =
			fixture.nodes[3].in_nodes;
	
	assert (nodes.find (fixture.nodes[1]) != null);
	assert (nodes.find (fixture.nodes[2]) != null);
}


private void test_digraph_node_get_out_nodes () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	GLib.List <unowned Crank.DigraphNode> nodes =
			fixture.nodes[4].out_nodes;
	
	assert (nodes.find (fixture.nodes[5]) != null);
	assert (nodes.find (fixture.nodes[6]) != null);
	assert (nodes.find (fixture.nodes[7]) != null);
}

private void test_digraph_node_get_indegree () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	assert (fixture.nodes[2].indegree == 1);
	assert (fixture.nodes[5].indegree == 1);
	assert (fixture.nodes[6].indegree == 2);
}

private void test_digraph_node_get_outdegree () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	assert (fixture.nodes[2].outdegree == 1);
	assert (fixture.nodes[5].outdegree == 1);
	assert (fixture.nodes[6].outdegree == 0);
}

private void test_digraph_node_is_adjacent () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	assert (  fixture.nodes[2].is_adjacent (fixture.nodes[3]));
	assert (  fixture.nodes[4].is_adjacent (fixture.nodes[6]));
	
	assert (  fixture.nodes[6].is_adjacent (fixture.nodes[7]));
	
	assert (! fixture.nodes[0].is_adjacent (fixture.nodes[2]));
	assert (! fixture.nodes[4].is_adjacent (fixture.nodes[8]));
}

private void test_digraph_node_is_adjacent_from () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	assert (  fixture.nodes[3].is_adjacent_from (fixture.nodes[2]));
	assert (  fixture.nodes[6].is_adjacent_from (fixture.nodes[4]));
	
	assert (! fixture.nodes[7].is_adjacent_from (fixture.nodes[6]));
	
	assert (! fixture.nodes[2].is_adjacent_from (fixture.nodes[0]));
	assert (! fixture.nodes[8].is_adjacent_from (fixture.nodes[4]));
}

private void test_digraph_node_is_adjacent_to () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	assert (  fixture.nodes[2].is_adjacent_to (fixture.nodes[3]));
	assert (  fixture.nodes[4].is_adjacent_to (fixture.nodes[6]));
	
	assert (! fixture.nodes[6].is_adjacent_to (fixture.nodes[7]));
	
	assert (! fixture.nodes[0].is_adjacent_to (fixture.nodes[2]));
	assert (! fixture.nodes[4].is_adjacent_to (fixture.nodes[8]));
}

private void test_digraph_node_foreach_depth () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	GLib.List <unowned Crank.DigraphNode> node_list;
	node_list = new GLib.List <unowned Crank.DigraphNode> ();
	
	Crank.DigraphNodeFunc	accum = (n) => {
		node_list.append (n);
		return true;
	};
	
	
	fixture.nodes[0].foreach_depth (accum);	
	assert (node_list.length () == 1);
	assert (node_list.nth_data (0) == fixture.nodes[0]);	
	
	node_list = new GLib.List <unowned Crank.DigraphNode> ();
	fixture.nodes[1].foreach_depth (accum);	
	assert (node_list.length () == 3);
	assert (node_list.nth_data (0) == fixture.nodes[1]);
	assert (node_list.nth_data (1) == fixture.nodes[3]);
	assert (node_list.nth_data (2) == fixture.nodes[2]);
	
	node_list = new GLib.List <unowned Crank.DigraphNode> ();
	fixture.nodes[4].foreach_depth (accum);	
	assert (node_list.length () == 5);
	assert (node_list.nth_data (0) == fixture.nodes[4]);
	assert (node_list.nth_data (1) == fixture.nodes[7]);
	assert (node_list.nth_data (2) == fixture.nodes[6]);
	assert (node_list.nth_data (3) == fixture.nodes[5]);
	assert (node_list.nth_data (4) == fixture.nodes[8]);

}

private void test_digraph_node_foreach_breadth () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	
	GLib.List <unowned Crank.DigraphNode> node_list;
	node_list = new GLib.List <unowned Crank.DigraphNode> ();
	
	Crank.DigraphNodeFunc	accum = (n) => {
		node_list.append (n);
		return true;
	};
	
	
	fixture.nodes[0].foreach_breadth (accum);	
	assert (node_list.length () == 1);
	assert (node_list.nth_data (0) == fixture.nodes[0]);	
	
	node_list = new GLib.List <unowned Crank.DigraphNode> ();
	fixture.nodes[1].foreach_breadth (accum);	
	assert (node_list.length () == 3);
	assert (node_list.nth_data (0) == fixture.nodes[1]);
	assert (node_list.nth_data (1) == fixture.nodes[2]);
	assert (node_list.nth_data (2) == fixture.nodes[3]);
	
	node_list = new GLib.List <unowned Crank.DigraphNode> ();
	fixture.nodes[4].foreach_breadth (accum);	
	assert (node_list.length () == 5);
	assert (node_list.nth_data (0) == fixture.nodes[4]);
	assert (node_list.nth_data (1) == fixture.nodes[5]);
	assert (node_list.nth_data (2) == fixture.nodes[6]);
	assert (node_list.nth_data (3) == fixture.nodes[7]);
	assert (node_list.nth_data (4) == fixture.nodes[8]);

}

private void test_digraph_edge_get_data () {
	TestDigraphFixture	fixture = TestDigraphFixture ();
	
	GLib.Value edge_v = GLib.Value (typeof (float));
	
	fixture.edges[5].get_data (ref edge_v);
	
	assert (edge_v.get_float () == 17.5f);
}

private void test_digraph_edge_get_tail () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	assert (fixture.edges[3].tail == fixture.nodes[4]);
	assert (fixture.edges[5].tail == fixture.nodes[4]);
	assert (fixture.edges[7].tail == fixture.nodes[7]);
}

private void test_digraph_edge_get_head () {
	TestDigraphFixture fixture = TestDigraphFixture ();
	assert (fixture.edges[1].head == fixture.nodes[3]);
	assert (fixture.edges[2].head == fixture.nodes[3]);
	assert (fixture.edges[4].head == fixture.nodes[6]);
}
