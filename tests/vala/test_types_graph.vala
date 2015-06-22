public class Test.A: GLib.Object {}
public class Test.B: Test.A {}
public class Test.C: Test.B {}
public class Test.D: Test.B {}
public class Test.E: Test.A {}

public class Test.X: GLib.Object {}

GLib.Type key1_a[1];
GLib.Type key1_b[1];
GLib.Type key1_c[1];
GLib.Type key1_d[1];
GLib.Type key1_e[1];
GLib.Type key1_x[1];

GLib.Type key2_aa[2];
GLib.Type key2_ab[2];
GLib.Type key2_ad[2];
GLib.Type key2_ae[2];
GLib.Type key2_bc[2];
GLib.Type key2_ca[2];
GLib.Type key2_ce[2];
GLib.Type key2_ea[2];
GLib.Type key2_ed[2];

GLib.Type key2_ax[2];
GLib.Type key2_xa[2];


public int main (string[] args) {
	GLib.Test.init (ref args);
	
	test_init_types_graph ();
	
	GLib.Test.add_func ("/wsid/crank/base/typesgraph/get",		test_get);
	GLib.Test.add_func ("/wsid/crank/base/typesgraph/has",		test_has);
	GLib.Test.add_func ("/wsid/crank/base/typesgraph/lookup/basic",	test_lookup);
	GLib.Test.add_func ("/wsid/crank/base/typesgraph/lookup/types",	test_lookup_types);
	GLib.Test.add_func ("/wsid/crank/base/typesgraph/lookup/full",	test_lookup_full);
	
	GLib.Test.run ();
	return 0;
}

public bool type_array_equal (GLib.Type[]? a, GLib.Type[]? b) {
	if (a == null) return (b == null);
	
	if (b == null) return false;

	for (int i = 0; i < a.length; i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}

public void test_init_types_graph () {
	GLib.Type a = typeof (Test.A);
	GLib.Type b = typeof (Test.B);
	GLib.Type c = typeof (Test.C);
	GLib.Type d = typeof (Test.D);
	GLib.Type e = typeof (Test.E);
	GLib.Type x = typeof (Test.X);
	
	key1_a = {a};
	key1_b = {b};
	key1_c = {c};
	key1_d = {d};
	key1_e = {e};
	
	key2_aa = {a, a};
	key2_ab = {a, b};
	key2_ad = {a, d};
	key2_ae = {a, e};
	key2_bc = {b, c};
	key2_ca = {c, a};
	key2_ce = {c, e};
	key2_ea = {e, a};
	key2_ed = {e, d};
	key2_ax = {a, x};
	key2_xa = {x, a};
}

public Crank.TypesGraph	create_test_subject () {
	Crank.TypesGraph graph = new Crank.TypesGraph ();
	
	graph[key1_a] = "value for A";
	graph[key1_d] = "value for D";
	graph[key1_e] = "value for E";
	
	graph[key2_aa] = "value for AA";
	graph[key2_ad] = "value for AD";
	graph[key2_ae] = "value for AE";
	graph[key2_ea] = "value for EA";
	graph[key2_ed] = "value for ED";
	return graph;
}

public void test_get () {
	Crank.TypesGraph graph = create_test_subject ();
	
	Value value = Value (typeof (string));
	
	assert (graph.get (key1_a, ref value));
	message ("%s", value.get_string());
	assert (value.get_string () == "value for A");
	
	assert (! graph.get (key1_b, ref value));
	
	assert (! graph.get (key1_c, ref value));
	
	assert (graph.get (key1_d, ref value));
	assert (value.get_string () == "value for D");
	
	assert (graph.get (key1_e, ref value));
	assert (value.get_string () == "value for E");
	
	assert (! graph.get (key1_x, ref value));
	
	
	assert (graph.get (key2_aa, ref value));
	assert (value.get_string () == "value for AA");
	
	assert (! graph.get (key2_ab, ref value));
	
	assert (graph.get (key2_ad, ref value));
	assert (value.get_string () == "value for AD");
	
	assert (graph.get (key2_ae, ref value));
	assert (value.get_string () == "value for AE");
	
	assert (! graph.get (key2_bc, ref value));
	
	assert (! graph.get (key2_ca, ref value));
	
	assert (! graph.get (key2_ce, ref value));
	
	assert (graph.get (key2_ea, ref value));
	assert (value.get_string () == "value for EA");
	
	assert (graph.get (key2_ed, ref value));
	assert (value.get_string () == "value for ED");
	
	assert (! graph.get (key2_ax, ref value));
	assert (! graph.get (key2_xa, ref value));
}

void test_has () {
	var graph = create_test_subject ();
	
	assert (graph.has (key1_a));
	assert (! graph.has (key1_b));
	assert (! graph.has (key1_c));
	assert (graph.has (key1_d));
	assert (graph.has (key1_e));
	assert (! graph.has (key1_x));
	
	assert (graph.has (key2_aa));
	assert (! graph.has (key2_ab));
	assert (graph.has (key2_ad));
	assert (graph.has (key2_ae));
	assert (! graph.has (key2_bc));
	assert (! graph.has (key2_ca));
	assert (! graph.has (key2_ce));
	assert (graph.has (key2_ea));
	assert (graph.has (key2_ed));
	assert (! graph.has (key2_ax));
	assert (! graph.has (key2_xa));
}

void test_lookup () {
	var graph = create_test_subject ();
	
	Value value = Value (typeof (string));
	
	assert (graph.lookup (key1_a, ref value));
	assert (value.get_string () == "value for A");
	assert (graph.lookup (key1_b, ref value));
	assert (value.get_string () == "value for A");
	assert (graph.lookup (key1_c, ref value));
	assert (value.get_string () == "value for A");
	assert (graph.lookup (key1_d, ref value));
	assert (value.get_string () == "value for D");
	assert (graph.lookup (key1_e, ref value));
	assert (value.get_string () == "value for E");
	
	assert (! graph.lookup (key1_x, ref value));
	
	assert (graph.lookup (key2_aa, ref value));
	assert (value.get_string () == "value for AA");
	assert (graph.lookup (key2_ab, ref value));
	assert (value.get_string () == "value for AA");
	assert (graph.lookup (key2_ad, ref value));
	assert (value.get_string () == "value for AD");
	assert (graph.lookup (key2_ae, ref value));
	assert (value.get_string () == "value for AE");
	assert (graph.lookup (key2_bc, ref value));
	assert (value.get_string () == "value for AA");
	assert (graph.lookup (key2_ca, ref value));
	assert (value.get_string () == "value for AA");
	assert (graph.lookup (key2_ce, ref value));
	assert (value.get_string () == "value for AE");
	assert (graph.lookup (key2_ea, ref value));
	assert (value.get_string () == "value for EA");
	assert (graph.lookup (key2_ed, ref value));
	assert (value.get_string () == "value for ED");
	
	assert (! graph.lookup (key2_ax, ref value));
	assert (! graph.lookup (key2_xa, ref value));
}


void test_lookup_types () {
	var graph = create_test_subject ();

	assert (type_array_equal(graph.lookup_types (key1_a), key1_a));
	assert (type_array_equal(graph.lookup_types (key1_b), key1_a));
	assert (type_array_equal(graph.lookup_types (key1_c), key1_a));
	assert (type_array_equal(graph.lookup_types (key1_d), key1_d));
	assert (type_array_equal(graph.lookup_types (key1_e), key1_e));
	assert (type_array_equal(graph.lookup_types (key1_x), null));
	
	
	assert (type_array_equal(graph.lookup_types (key2_aa), key2_aa));
	assert (type_array_equal(graph.lookup_types (key2_ab), key2_aa));
	assert (type_array_equal(graph.lookup_types (key2_ad), key2_ad));
	assert (type_array_equal(graph.lookup_types (key2_ae), key2_ae));
	assert (type_array_equal(graph.lookup_types (key2_bc), key2_aa));
	assert (type_array_equal(graph.lookup_types (key2_ca), key2_aa));
	assert (type_array_equal(graph.lookup_types (key2_ce), key2_ae));
	assert (type_array_equal(graph.lookup_types (key2_ea), key2_ea));
	assert (type_array_equal(graph.lookup_types (key2_ed), key2_ed));
	assert (type_array_equal(graph.lookup_types (key2_ax), null));
	assert (type_array_equal(graph.lookup_types (key2_xa), null));
}


void test_lookup_full () {
	var graph = create_test_subject ();
	
	var value = Value (typeof (string));
	
	GLib.Type[] lookup1_a;
	GLib.Type[] lookup1_b;
	GLib.Type[] lookup1_c;
	GLib.Type[] lookup1_d;
	GLib.Type[] lookup1_e;
	GLib.Type[] lookup1_x;
	
	GLib.Type[] lookup2_aa;
	GLib.Type[] lookup2_ab;
	GLib.Type[] lookup2_ad;
	GLib.Type[] lookup2_ae;
	GLib.Type[] lookup2_bc;
	GLib.Type[] lookup2_ca;
	GLib.Type[] lookup2_ce;
	GLib.Type[] lookup2_ea;
	GLib.Type[] lookup2_ed;
	GLib.Type[] lookup2_ax;
	GLib.Type[] lookup2_xa;

	assert (graph.lookup_full (key1_a, out lookup1_a, ref value));
	assert (graph.lookup_full (key1_b, out lookup1_b, ref value));
	assert (graph.lookup_full (key1_c, out lookup1_c, ref value));
	assert (graph.lookup_full (key1_d, out lookup1_d, ref value));
	assert (graph.lookup_full (key1_e, out lookup1_e, ref value));
	assert (! graph.lookup_full (key1_x, out lookup1_x, ref value));
	
	assert (type_array_equal(lookup1_a, key1_a));
	assert (type_array_equal(lookup1_b, key1_a));
	assert (type_array_equal(lookup1_c, key1_a));
	assert (type_array_equal(lookup1_d, key1_d));
	assert (type_array_equal(lookup1_e, key1_e));
	assert (type_array_equal(lookup1_x, null));
}

