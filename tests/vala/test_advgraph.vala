/* Copyright (C) 2015, WSID   */

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

public struct TestFixture {
	public	Crank.Digraph				graph;
	public	unowned Crank.DigraphNode	nodes[16];
	public	unowned Crank.DigraphEdge	edges[32];
	
	public TestFixture () {
		Crank.VecInt2	pos;
		
		graph = new Crank.Digraph ();
		
		// The nodes are positioned According to below map. (lines are edges)
		//
		//    -5-4-3-2-1 0 1 2 3 4 5 6
		//  6                        0
		//  5                    ---/|
		//  4                ---/    |
		//  3              4/        |
		//  2    5-\       |\        |
		//  1   /   --\    2|        7
		//  0   |      --3/ |       /
		// -1   |     /   \ \      /
		// -2  /    /-     \ |   -/
		// -3  |  /-        \|  /
		// -4  |/-           \ /
		// -5  1-------------6/     

		// 0 at (6, 6)
		pos = {6, 6};
		nodes[0] = graph.add (pos);
		
		// 1 at (-5, -5)
		pos = {-5, -5};
		nodes[1] = graph.add (pos);
		
		// 2 at (1, 1)
		pos = {1, 1};
		nodes[2] = graph.add (pos);
		
		// 3 at (0, 0)
		pos = {0, 0};
		nodes[3] = graph.add (pos);
		
		// 4 at (1, 3)
		pos = {1, 3};
		nodes[4] = graph.add (pos);
		
		// 5 at (-4, 2)
		pos = {-4, 2};
		nodes[5] = graph.add (pos);
		
		// 6 at (2, -5)
		pos = {2, -5};
		nodes[6] = graph.add (pos);
		
		// 7 at (6, 1)
		pos = {6, 1};
		nodes[7] = graph.add (pos);
		
		
		// edge for 0-4
		edges[0] = graph.connect_void (nodes[0], nodes[4]);
		edges[1] = graph.connect_void (nodes[4], nodes[0]);
		
		// edge for 0-7
		edges[2] = graph.connect_void (nodes[0], nodes[7]);
		edges[3] = graph.connect_void (nodes[7], nodes[0]);
		
		// edge for 1-3
		edges[4] = graph.connect_void (nodes[1], nodes[3]);
		edges[5] = graph.connect_void (nodes[3], nodes[1]);
		
		// edge for 1-5
		edges[6] = graph.connect_void (nodes[1], nodes[5]);
		edges[7] = graph.connect_void (nodes[5], nodes[1]);
		
		// edge for 1-6
		edges[8] = graph.connect_void (nodes[1], nodes[6]);
		edges[9] = graph.connect_void (nodes[6], nodes[1]);
		
		// edge for 2-3
		edges[10] = graph.connect_void (nodes[2], nodes[3]);
		edges[11] = graph.connect_void (nodes[3], nodes[2]);
		
		// edge for 2-4
		edges[12] = graph.connect_void (nodes[2], nodes[4]);
		edges[13] = graph.connect_void (nodes[4], nodes[2]);
		
		// edge for 2-5
		edges[14] = graph.connect_void (nodes[2], nodes[5]);
		edges[15] = graph.connect_void (nodes[5], nodes[2]);
		
		// edge for 3-6
		edges[16] = graph.connect_void (nodes[3], nodes[6]);
		edges[17] = graph.connect_void (nodes[6], nodes[3]);
		
		// edge for 4-6
		edges[18] = graph.connect_void (nodes[4], nodes[6]);
		edges[19] = graph.connect_void (nodes[6], nodes[4]);
		
		// edge for 6-7
		edges[20] = graph.connect_void (nodes[6], nodes[7]);
		edges[21] = graph.connect_void (nodes[7], nodes[6]);
	}
}

private float	edge_distance (Crank.DigraphEdge	edge)
{
	Crank.VecInt2	disp;
	
	disp = (Crank.VecInt2?) edge.head.get_boxed ();
	disp = disp.sub ((Crank.VecInt2?) edge.tail.get_boxed ());
	
	return disp.magn;
}

private float	heuristic (Crank.DigraphNode from, Crank.DigraphNode to)
{
	Crank.VecInt2	disp;
	
	disp = (Crank.VecInt2?) to.get_boxed ();
	disp = disp.sub ((Crank.VecInt2?) from.get_boxed ());
	
	return disp.magn;	
}

private void test_dijkstra ()
{
	TestFixture	ft = TestFixture ();
	
	GLib.List<unowned Crank.DigraphNode> path =
		Crank.dijkstra_digraph (ft.nodes[0], ft.nodes[1], edge_distance);
	
	assert (path.length () == 5);
	assert (path.nth_data (0) == ft.nodes[0]);
	assert (path.nth_data (1) == ft.nodes[4]);
	assert (path.nth_data (2) == ft.nodes[2]);
	assert (path.nth_data (3) == ft.nodes[3]);
	assert (path.nth_data (4) == ft.nodes[1]);
}

private void test_astar ()
{
	TestFixture	ft = TestFixture ();
	
	GLib.List<unowned Crank.DigraphNode> path =
		Crank.astar_digraph (ft.nodes[5], ft.nodes[7], edge_distance, heuristic);
	
	assert (path.length () == 5);
	assert (path.nth_data (0) == ft.nodes[5]);
	assert (path.nth_data (1) == ft.nodes[2]);
	assert (path.nth_data (2) == ft.nodes[4]);
	assert (path.nth_data (3) == ft.nodes[0]);
	assert (path.nth_data (4) == ft.nodes[7]);
}

int main (string[] args) {
	GLib.Test.init (ref args);
	
	GLib.Test.add_func ("/crank/base/advgraph/dijkstra/digraph",
		test_dijkstra );
	
	GLib.Test.add_func ("/crank/base/advgraph/astar/digraph",
		test_astar);
	
	GLib.Test.run ();
	
	return 0;
}
