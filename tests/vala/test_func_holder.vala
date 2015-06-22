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


private static GLib.Type[] g_type_pool;

private GLib.Type rand_g_type () {
	return g_type_pool [ GLib.Test.rand_int_range (0, 9) ];
}

private bool subject_function (int a, int b) {
	return (a % b) == 0;
}

private int add_i_ii (int a, int b) {
	return a + b;
}

private float add_f_ff (float a, float b) {
	return a + b;
}

private int mul_i_ii (int a, int b) {
	return a * b;
}

private float mul_f_ff (float a, float b) {
	return a * b;
}

private int neg_i_i (int a) {
	return -a;
}

private float neg_f_f (float a) {
	return -a;
}

private enum TestFuncEnum {
	ADD,
	MUL,
	NEG
}

private struct FixtureBook {
	Crank.FuncBook book;
	Crank.FuncHolder	holder_add;
	Crank.FuncHolder	holder_mul;
	Crank.FuncHolder	holder_neg;
	
	public FixtureBook () {
		book = new Crank.FuncBook.with_name ("test-book");
		holder_add = new Crank.FuncHolder ("add");
		holder_mul = new Crank.FuncHolder ("mul");
		holder_neg = new Crank.FuncHolder ("neg");
		
		book.set (TestFuncEnum.ADD, holder_add);
		book.set (TestFuncEnum.MUL, holder_mul);
		book.set (TestFuncEnum.NEG, holder_neg);
		
		var ftype_i_ii = new Crank.FuncType (typeof (int), typeof (int), typeof (int));
		var ftype_f_ff = new Crank.FuncType (typeof (float), typeof (float), typeof (float));
		var ftype_i_i = new Crank.FuncType (typeof (int), typeof (int));
		var ftype_f_f = new Crank.FuncType (typeof (float), typeof (float));
		
		holder_add.set_func (ftype_i_ii, (Crank.Callback)add_i_ii);
		holder_add.set_func (ftype_f_ff, (Crank.Callback)add_f_ff);
		holder_mul.set_func (ftype_i_ii, (Crank.Callback)mul_i_ii);
		holder_mul.set_func (ftype_f_ff, (Crank.Callback)mul_f_ff);
		holder_neg.set_func (ftype_i_i, (Crank.Callback)neg_i_i);
		holder_neg.set_func (ftype_f_f, (Crank.Callback)neg_f_f);
	}
}


private void func_type_new () {
	Crank.FuncType ftype = new Crank.FuncType (
			typeof (bool),
			typeof (int), typeof (char)	);
	
	assert (typeof (bool) == ftype.return_type);
	assert (typeof (int) == ftype.get_param_type (0));
	assert (typeof (char) == ftype.get_param_type (1));
	assert (typeof (void) == ftype.get_param_type (2));
	
	assert (2 == ftype.nparam_types);
	
	GLib.Type[] param_types = ftype.param_types;
	
	assert (2 == param_types.length);
	assert (typeof (int) == param_types[0]);
	assert (typeof (char) == param_types[1]);
}

private void func_type_new_with_types () {
	Crank.FuncType ftype = new Crank.FuncType.with_types (
			typeof (bool),
			{typeof (int), typeof (char)} );
	
	assert (typeof (bool) == ftype.return_type);
	assert (typeof (int) == ftype.get_param_type (0));
	assert (typeof (char) == ftype.get_param_type (1));
	assert (typeof (void) == ftype.get_param_type (2));
	
	assert (2 == ftype.nparam_types);
	
	GLib.Type[] param_types = ftype.param_types;
	
	assert (2 == param_types.length);
	assert (typeof (int) == param_types[0]);
	assert (typeof (char) == param_types[1]);
}

private void func_type_hash () {
	GLib.Type r_type;
	GLib.Type p_types[2];

	r_type = rand_g_type ();
	p_types[0] = rand_g_type ();
	p_types[1] = rand_g_type ();

	Crank.FuncType ftype_a = new Crank.FuncType.with_types (r_type, p_types);
	Crank.FuncType ftype_b = new Crank.FuncType.with_types (r_type, p_types);
	
	assert (ftype_a.hash () == ftype_b.hash ());
}

private void func_type_equal () {
	GLib.Type r_type;
	GLib.Type p_types[2];

	r_type = rand_g_type ();
	p_types[0] = rand_g_type ();
	p_types[1] = rand_g_type ();

	Crank.FuncType ftype_a = new Crank.FuncType.with_types (r_type, p_types);
	Crank.FuncType ftype_b = new Crank.FuncType.with_types (r_type, p_types);
	
	assert (ftype_a.equal (ftype_b));
}

private void func_type_to_string () {
	Crank.FuncType ftype = new Crank.FuncType (
			typeof (bool),
			typeof(int), typeof(char)	);
	
	assert (ftype.to_string () == "gboolean (gint, gchar)");
}

private void func_type_compatible_to () {
	Crank.FuncType ftype_from = new Crank.FuncType (
			typeof (GLib.Binding), typeof (GLib.Object)	);
			
	Crank.FuncType ftype_to = new Crank.FuncType (
			typeof (GLib.Object), typeof (GLib.Binding)	);
	
	assert (ftype_from.compatible_to (ftype_to));
}

private void func_type_compatible_to_param_size () {
	Crank.FuncType ftype_from = new Crank.FuncType (
			typeof (bool),
			typeof (int)	);
			
	Crank.FuncType ftype_to = new Crank.FuncType (
			typeof (bool),
			typeof (int), typeof (int)	);
	
	assert (ftype_from.compatible_to (ftype_to));
}


private void func_type_arg_match_exactually () {
	GLib.Type types_a[] = {typeof (int), typeof (float)};
	GLib.Type types_b[] = {typeof (int), typeof (double)};
	GLib.Type types_c[] = {typeof (int)};
	GLib.Type types_d[] = {typeof (int), typeof (float), typeof (bool)};
	
	Crank.FuncType ftype = new Crank.FuncType (
			typeof (bool),
			typeof (int), typeof (float)	);
	
	assert (  ftype.arg_match_exactually (types_a));
	assert (! ftype.arg_match_exactually (types_b));
	assert (! ftype.arg_match_exactually (types_c));
	assert (! ftype.arg_match_exactually (types_d));
}

private void func_type_arg_match () {
	GLib.Type types_a[] = {typeof (GLib.Object), typeof (int)};
	GLib.Type types_b[] = {typeof (int), typeof (double)};
	GLib.Type types_c[] = {typeof (GLib.Binding), typeof (int)};
	
	Crank.FuncType ftype = new Crank.FuncType (
			typeof (bool),
			typeof (GLib.Object), typeof (int)	);
	
	assert (  ftype.arg_match (types_a));
	assert (! ftype.arg_match (types_b));
	assert (  ftype.arg_match (types_c));
}

private void func_type_arg_match_transformable () {
	GLib.Type types_a[] = {typeof (GLib.Object), typeof (int)};
	GLib.Type types_b[] = {typeof (GLib.Object), typeof (double)};
	GLib.Type types_c[] = {typeof (GLib.Binding), typeof (float)};
	GLib.Type types_d[] = {typeof (string), typeof (float)};
	
	Crank.FuncType ftype = new Crank.FuncType (
			typeof (bool),
			typeof (GLib.Object), typeof (int)	);
	
	assert (  ftype.arg_match_transformable (types_a));
	assert (  ftype.arg_match_transformable (types_b));
	assert (  ftype.arg_match_transformable (types_c));
	assert (! ftype.arg_match_transformable (types_d));
}



private int	subject_function_int (int a, int b) {
	return a + b;
}

private float subject_function_float (float a, float b) {
	return a + b;
}

private string subject_function_string (string a, string b) {
	return a + b;
}



private Crank.FuncHolder func_holder_create () {
	Crank.FuncHolder holder = new Crank.FuncHolder ("test-holder");
	
	holder.set_func (
			new Crank.FuncType (typeof (int), typeof (int), typeof (int)),
			(Crank.Callback)subject_function_int);
			
	holder.set_func (
			new Crank.FuncType (typeof (float), typeof (float), typeof (float)),
			(Crank.Callback)subject_function_float);
			
	holder.set_func (
			new Crank.FuncType (typeof (string), typeof (string), typeof (string)),
			(Crank.Callback)subject_function_string);
	
	return holder;
}

private void func_holder_get () {
	Crank.FuncHolder holder = func_holder_create ();
	
	Crank.FuncType ftype_int = new Crank.FuncType (typeof (int),
			typeof (int), typeof (int));
	Crank.FuncType ftype_float = new Crank.FuncType (typeof (float),
			typeof (float), typeof (float));
	Crank.FuncType ftype_string = new Crank.FuncType (typeof (string),
			typeof (string), typeof (string));
	
	GLib.Closure closure_int = holder.get (ftype_int);
	GLib.Closure closure_float = holder.get (ftype_float);
	GLib.Closure closure_string = holder.get (ftype_string);
	
	GLib.Value value_int	= GLib.Value (typeof(int));
	GLib.Value value_float	= GLib.Value (typeof(float));
	GLib.Value value_string = GLib.Value (typeof(string));
	
	Crank.closure_invoke (closure_int, ref value_int, {2, 4});
	assert (value_int.get_int () == 6);
	
	Crank.closure_invoke (closure_float, ref value_float, {3.2f, 6.8f});
	assert (value_float.get_float () == 10.0f);
	
	Crank.closure_invoke (closure_string, ref value_string, {"Piece", "Cake"});
	assert (value_string.get_string () == "PieceCake");
}


private void func_holder_get_by_param_types () {
	Crank.FuncHolder holder = func_holder_create ();
	
	GLib.Closure closure_int = holder.get_by_param_types ({typeof(int), typeof(int)});
	GLib.Closure closure_float = holder.get_by_param_types ({typeof(float), typeof(float)});
	GLib.Closure closure_string = holder.get_by_param_types ({typeof (string), typeof (string)});
	
	GLib.Value value_int	= GLib.Value (typeof(int));
	GLib.Value value_float	= GLib.Value (typeof(float));
	GLib.Value value_string = GLib.Value (typeof(string));
	
	Crank.closure_invoke (closure_int, ref value_int, {2, 4});
	assert (value_int.get_int () == 6);
	
	Crank.closure_invoke (closure_float, ref value_float, {3.2f, 6.8f});
	assert (value_float.get_float () == 10.0f);
	
	Crank.closure_invoke (closure_string, ref value_string, {"Piece", "Cake"});
	assert (value_string.get_string () == "PieceCake");
}

private void func_holder_name () {
	Crank.FuncHolder holder = new Crank.FuncHolder ("test-holder");
	
	assert (holder.name == "test-holder");
	assert (holder.qname == GLib.Quark.from_string ("test-holder"));
	
	holder.name = "another-holder";
	
	assert (holder.name == "another-holder");
	assert (holder.qname == GLib.Quark.from_string ("another-holder"));
	
	holder.qname = GLib.Quark.from_string("my-holder");
	
	assert (holder.name == "my-holder");
	assert (holder.qname == GLib.Quark.from_string ("my-holder"));
}

private void func_holder_remove () {
	Crank.FuncHolder holder = func_holder_create ();
	
	Crank.FuncType ftype_int = new Crank.FuncType (typeof (int),
			typeof (int), typeof (int));
	Crank.FuncType ftype_float = new Crank.FuncType (typeof (float),
			typeof (float), typeof (float));
	Crank.FuncType ftype_string = new Crank.FuncType (typeof (string),
			typeof (string), typeof (string));
	
	assert (  holder.remove (ftype_int));
	assert (  holder.remove (ftype_float));
	assert (! holder.remove (ftype_int));
	assert (  holder.remove (ftype_string));
}

private void func_holder_remove_by_param_types () {
	Crank.FuncHolder holder = func_holder_create ();
	
	assert (  holder.remove_by_param_types ({typeof(int), typeof(int)}));
	assert (  holder.remove_by_param_types ({typeof(float), typeof(float)}));
	assert (! holder.remove_by_param_types ({typeof(int), typeof(int)}));
	assert (  holder.remove_by_param_types ({typeof(string), typeof(string)}));
}


private void func_holder_lookup_type () {
	Crank.FuncHolder holder = func_holder_create ();
	
	assert (	holder.lookup_return_type ({typeof (int), typeof (int)})
				==
				typeof (int)	);
	
	assert (	holder.lookup_return_type ({typeof (float), typeof (float)})
				==
				typeof (float)	);
				
	assert (	holder.lookup_return_type ({typeof (string), typeof (string)})
				==
				typeof (string)	);
}

private void func_holder_invoke () {
	Crank.FuncHolder holder = func_holder_create ();
	
	GLib.Value value = GLib.Value (typeof (int));
	
	assert (holder.invoke (ref value, {2, 3}));
	assert (value.get_int () == 5);
	
	value = GLib.Value (typeof (float));
	
	assert (holder.invoke (ref value, {4.5f, 6.5f}));
	assert (value.get_float () == 11.0f);
	
	value = GLib.Value (typeof (string));
	
	assert (holder.invoke (ref value, {"Daddy ", "long leg"}));
	assert (value.get_string () == "Daddy long leg");
}

private void func_holder_invokev () {
	Crank.FuncHolder holder = func_holder_create ();
	
	GLib.Value value = GLib.Value (typeof (int));
	
	GLib.Value value_a = 2;
	GLib.Value value_b = 3;
	
	assert (holder.invokev (ref value, null, 2, value_a, value_b));
	assert (value.get_int () == 5);
}

private void func_holder_invokev_overwrite () {
	Crank.FuncHolder holder = func_holder_create ();
	
	GLib.Value value;
	
	GLib.Value value_a = 2;
	GLib.Value value_b = 3;
	
	assert (holder.invokev_overwrite (out value, null, 2, value_a, value_b));
	assert (value.get_int () == 5);
}


private void func_holder_invoke_overwrite () {
	Crank.FuncHolder holder = func_holder_create ();
	
	GLib.Value value;
	
	assert (holder.invoke_overwrite (out value, {2, 3}));
	assert (value.get_int () == 5);
	
	assert (holder.invoke_overwrite (out value, {4.5f, 6.5f}));
	assert (value.get_float () == 11.0f);
	
	assert (holder.invoke_overwrite (out value, {"Daddy ", "long leg"}));
	assert (value.get_string () == "Daddy long leg");
}

private void func_book_name () {
	Crank.FuncBook book = new Crank.FuncBook.with_name ("test-book");
	
	assert (book.name == "test-book");
	assert (book.qname == GLib.Quark.try_string ("test-book"));
	
	book.name = "another-book";
	assert (book.name == "another-book");
	assert (book.qname == GLib.Quark.try_string ("another-book"));
	
	book.qname = GLib.Quark.from_string ("necronomicon");
	assert (book.name == "necronomicon");
	assert (book.qname == GLib.Quark.try_string ("necronomicon"));
}

private void func_book_get () {
	FixtureBook fix = FixtureBook ();
	
	assert (fix.book [TestFuncEnum.ADD] == fix.holder_add);
	assert (fix.book [TestFuncEnum.MUL] == fix.holder_mul);
	assert (fix.book [TestFuncEnum.NEG] == fix.holder_neg);
}

private void func_book_index_of () {
	FixtureBook fix = FixtureBook ();
	
	assert (fix.book.index_of (fix.holder_add) == TestFuncEnum.ADD);
	assert (fix.book.index_of (fix.holder_mul) == TestFuncEnum.MUL);
	assert (fix.book.index_of (fix.holder_neg) == TestFuncEnum.NEG);
}

private void func_book_get_by_name () {
	FixtureBook fix = FixtureBook ();
	
	assert (fix.book.get_by_name ("add") == fix.holder_add);
	assert (fix.book.get_by_name ("mul") == fix.holder_mul);
	assert (fix.book.get_by_name ("neg") == fix.holder_neg);
}

private void func_book_get_by_qname () {
	FixtureBook fix = FixtureBook ();

	assert (fix.book.get_by_qname (GLib.Quark.from_string ("add")) == fix.holder_add);
	assert (fix.book.get_by_qname (GLib.Quark.from_string ("mul")) == fix.holder_mul);
	assert (fix.book.get_by_qname (GLib.Quark.from_string ("neg")) == fix.holder_neg);
}

private void func_book_remove () {
	FixtureBook fix = FixtureBook ();
	
	assert (fix.book.remove (TestFuncEnum.ADD));
	assert (fix.book.remove (TestFuncEnum.MUL));
	assert (fix.book.remove (TestFuncEnum.NEG));
	assert (! fix.book.remove (TestFuncEnum.ADD));
	
	assert (fix.book[TestFuncEnum.ADD] == null);
	assert (fix.book[TestFuncEnum.MUL] == null);
	assert (fix.book[TestFuncEnum.NEG] == null);
}

private void func_book_remove_by_name () {
	FixtureBook fix = FixtureBook ();
	
	assert (fix.book.remove_by_name ("add"));
	assert (fix.book.remove_by_name ("mul"));
	assert (fix.book.remove_by_name ("neg"));
	assert (! fix.book.remove_by_name ("add"));
	
	assert (fix.book[TestFuncEnum.ADD] == null);
	assert (fix.book[TestFuncEnum.MUL] == null);
	assert (fix.book[TestFuncEnum.NEG] == null);
}

private void func_book_remove_by_qname () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Quark addq = GLib.Quark.from_string ("add");
	GLib.Quark mulq = GLib.Quark.from_string ("mul");
	GLib.Quark negq = GLib.Quark.from_string ("neg");
	
	
	assert (fix.book.remove_by_qname (addq));
	assert (fix.book.remove_by_qname (mulq));
	assert (fix.book.remove_by_qname (negq));
	assert (! fix.book.remove_by_qname (addq));
	
	assert (fix.book[TestFuncEnum.ADD] == null);
	assert (fix.book[TestFuncEnum.MUL] == null);
	assert (fix.book[TestFuncEnum.NEG] == null);
}

private void func_book_invoke () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Value value = GLib.Value (typeof (int));
	
	assert (fix.book.invoke (TestFuncEnum.ADD, ref value, {17, 19}));
	assert (value.get_int () == 17 + 19);
	
	assert (fix.book.invoke (TestFuncEnum.MUL, ref value, {17, 19}));
	assert (value.get_int () == 17 * 19);
	
	assert (fix.book.invoke (TestFuncEnum.NEG, ref value, {32}));
	assert (value.get_int () == -32 );
	
	
	value = GLib.Value (typeof (float));
	
	assert (fix.book.invoke (TestFuncEnum.ADD, ref value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f + 14.1f);
	
	assert (fix.book.invoke (TestFuncEnum.MUL, ref value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f * 14.1f);
	
	assert (fix.book.invoke (TestFuncEnum.NEG, ref value, {14.0f}));
	assert (value.get_float () == -14.0f );
}

private void func_book_invoke_name () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Value value = GLib.Value (typeof (int));
	
	assert (fix.book.invoke_name ("add", ref value, {17, 19}));
	assert (value.get_int () == 	17 + 19);
	
	assert (fix.book.invoke_name ("mul", ref value, {17, 19}));
	assert (value.get_int () == 17 * 19);
	
	assert (fix.book.invoke_name ("neg", ref value, {32}));
	assert (value.get_int () == -32 );
	
	
	value = GLib.Value (typeof (float));
	
	assert (fix.book.invoke_name ("add", ref value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f + 14.1f);
	
	assert (fix.book.invoke_name ("mul", ref value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f * 14.1f);
	
	assert (fix.book.invoke_name ("neg", ref value, {14.0f}));
	assert (value.get_float () == -14.0f );
}

private void func_book_invoke_qname () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Quark addq = GLib.Quark.try_string ("add");
	GLib.Quark mulq = GLib.Quark.try_string ("mul");
	GLib.Quark negq = GLib.Quark.try_string ("neg");
	
	GLib.Value value = GLib.Value (typeof (int));
	
	assert (fix.book.invoke_qname (addq, ref value, {17, 19}));
	assert (value.get_int () == 	17 + 19);
	
	assert (fix.book.invoke_qname (mulq, ref value, {17, 19}));
	assert (value.get_int () == 17 * 19);
	
	assert (fix.book.invoke_qname (negq, ref value, {32}));
	assert (value.get_int () == -32 );
	
	
	value = GLib.Value (typeof (float));
	
	assert (fix.book.invoke_qname (addq, ref value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f + 14.1f);
	
	assert (fix.book.invoke_qname (mulq, ref value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f * 14.1f);
	
	assert (fix.book.invoke_qname (negq, ref value, {14.0f}));
	assert (value.get_float () == -14.0f );
}


private void func_book_invoke_overwrite () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Value value;
	
	assert (fix.book.invoke_overwrite (TestFuncEnum.ADD, out value, {17, 19}));
	assert (value.get_int () == 17 + 19);
	
	assert (fix.book.invoke_overwrite (TestFuncEnum.MUL, out value, {17, 19}));
	assert (value.get_int () == 17 * 19);
	
	assert (fix.book.invoke_overwrite (TestFuncEnum.NEG, out value, {32}));
	assert (value.get_int () == -32 );
	
	
	assert (fix.book.invoke_overwrite (TestFuncEnum.ADD, out value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f + 14.1f);
	
	assert (fix.book.invoke_overwrite (TestFuncEnum.MUL, out value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f * 14.1f);
	
	assert (fix.book.invoke_overwrite (TestFuncEnum.NEG, out value, {14.0f}));
	assert (value.get_float () == -14.0f );
}

private void func_book_invoke_overwrite_name () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Value value;
	
	assert (fix.book.invoke_overwrite_name ("add", out value, {17, 19}));
	assert (value.get_int () == 	17 + 19);
	
	assert (fix.book.invoke_overwrite_name ("mul", out value, {17, 19}));
	assert (value.get_int () == 17 * 19);
	
	assert (fix.book.invoke_overwrite_name ("neg", out value, {32}));
	assert (value.get_int () == -32 );
	
	assert (fix.book.invoke_overwrite_name ("add", out value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f + 14.1f);
	
	assert (fix.book.invoke_overwrite_name ("mul", out value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f * 14.1f);
	
	assert (fix.book.invoke_overwrite_name ("neg", out value, {14.0f}));
	assert (value.get_float () == -14.0f );
}

private void func_book_invoke_overwrite_qname () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Quark addq = GLib.Quark.try_string ("add");
	GLib.Quark mulq = GLib.Quark.try_string ("mul");
	GLib.Quark negq = GLib.Quark.try_string ("neg");
	
	GLib.Value value;
	
	assert (fix.book.invoke_overwrite_qname (addq, out value, {17, 19}));
	assert (value.get_int () == 	17 + 19);
	
	assert (fix.book.invoke_overwrite_qname (mulq, out value, {17, 19}));
	assert (value.get_int () == 17 * 19);
	
	assert (fix.book.invoke_overwrite_qname (negq, out value, {32}));
	assert (value.get_int () == -32 );
	
	
	assert (fix.book.invoke_overwrite_qname (addq, out value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f + 14.1f);
	
	assert (fix.book.invoke_overwrite_qname (mulq, out value, {33.2f, 14.1f}));
	assert (value.get_float () == 33.2f * 14.1f);
	
	assert (fix.book.invoke_overwrite_qname (negq, out value, {14.0f}));
	assert (value.get_float () == -14.0f );
}

private void func_book_invokev () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Value value = GLib.Value (typeof (int));
	
	GLib.Value value_a = 17;
	GLib.Value value_b = 19;
	
	assert (fix.book.invokev (TestFuncEnum.ADD, ref value, null, 2, value_a, value_b));
	assert (value.get_int () == 17 + 19);
	
	assert (fix.book.invokev (TestFuncEnum.MUL, ref value, null, 2, value_a, value_b));
	assert (value.get_int () == 17 * 19);
	
	assert (fix.book.invokev (TestFuncEnum.NEG, ref value, null, 1, value_b));
	assert (value.get_int () == -19 );
	
	
	value = GLib.Value (typeof (float));
	
	value_a = 33.2f;
	value_b = 14.1f;
	
	assert (fix.book.invokev (TestFuncEnum.ADD, ref value, null, 2, value_a, value_b));
	assert (value.get_float () == 33.2f + 14.1f);
	
	assert (fix.book.invokev (TestFuncEnum.MUL, ref value, null, 2, value_a, value_b));
	assert (value.get_float () == 33.2f * 14.1f);
	
	assert (fix.book.invokev (TestFuncEnum.NEG, ref value, null, 1, value_b));
	assert (value.get_float () == -14.1f );
}

private void func_book_invokev_overwrite () {
	FixtureBook fix = FixtureBook ();
	
	GLib.Value value;
	
	GLib.Value value_a = 17;
	GLib.Value value_b = 19;
	
	assert (fix.book.invokev_overwrite (TestFuncEnum.ADD, out value, null, 2, value_a, value_b));
	assert (value.get_int () == 17 + 19);
	
	assert (fix.book.invokev_overwrite (TestFuncEnum.MUL, out value, null, 2, value_a, value_b));
	assert (value.get_int () == 17 * 19);
	
	assert (fix.book.invokev_overwrite (TestFuncEnum.NEG, out value, null, 1, value_b));
	assert (value.get_int () == -19 );
	
	value_a = 33.2f;
	value_b = 14.1f;
	
	assert (fix.book.invokev_overwrite (TestFuncEnum.ADD, out value, null, 2, value_a, value_b));
	assert (value.get_float () == 33.2f + 14.1f);
	
	assert (fix.book.invokev_overwrite (TestFuncEnum.MUL, out value, null, 2, value_a, value_b));
	assert (value.get_float () == 33.2f * 14.1f);
	
	assert (fix.book.invokev_overwrite (TestFuncEnum.NEG, out value, null, 1, value_b));
	assert (value.get_float () == -14.1f );
}


int main (string[] args) {
	GLib.Test.init (ref args);
	
	g_type_pool = {
		typeof (uchar),
		typeof (char),
		typeof (int),
		typeof (uint),
		typeof (long),
		typeof (ulong),
		typeof (int64),
		typeof (uint64),
		typeof (bool)
	};
	
	GLib.Test.add_func ("/wsid/crank/base/functype/new",
			func_type_new	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/newwithtypes",
			func_type_new_with_types	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/hash",
			func_type_hash	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/equal",
			func_type_equal	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/tostring",
			func_type_to_string	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/compatible/basic",
			func_type_compatible_to	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/compatible/paramsize",
			func_type_compatible_to_param_size	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/argmatch/exactually",
			func_type_arg_match_exactually	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/argmatch/normal",
			func_type_arg_match	);
			
	GLib.Test.add_func ("/wsid/crank/base/functype/argmatch/transformable",
			func_type_arg_match_transformable	);
	
	GLib.Test.add_func ("/wsid/crank/base/holder/name",
			func_holder_name	);
			
	GLib.Test.add_func ("/wsid/crank/base/holder/get",
			func_holder_get	);
			
	GLib.Test.add_func ("/wsid/crank/base/holder/get_by_param_type",
			func_holder_get_by_param_types	);
			
	GLib.Test.add_func ("/wsid/crank/base/holder/lookup_return_type",
			func_holder_lookup_type	);
			
	GLib.Test.add_func ("/wsid/crank/base/holder/invoke",
			func_holder_invoke	);
			
	GLib.Test.add_func ("/wsid/crank/base/holder/invokev",
			func_holder_invokev	);
			
	GLib.Test.add_func ("/wsid/crank/base/holder/invoke_overwrite",
			func_holder_invoke_overwrite	);
			
	GLib.Test.add_func ("/wsid/crank/base/holder/remove_by_param_types",
			func_holder_remove_by_param_types	);
			
	GLib.Test.add_func ("/wsid/crank/base/holder/remove",
			func_holder_remove	);
	
	GLib.Test.add_func ("/crank/base/book/name",
			func_book_name	);
			
	GLib.Test.add_func ("/crank/base/book/get",
			func_book_get	);
	
	GLib.Test.add_func ("/crank/base/book/index_of",
			func_book_index_of	);
	
	GLib.Test.add_func ("/crank/base/book/get_by_name",
			func_book_get_by_name	);

	GLib.Test.add_func ("/crank/base/book/get_by_qname",
			func_book_get_by_qname	);
	
	GLib.Test.add_func ("/crank/base/book/remove",
			func_book_remove	);
			
	GLib.Test.add_func ("/crank/base/book/remove_by_name",
			func_book_remove_by_name	);
			
	GLib.Test.add_func ("/crank/base/book/remove_by_qname",
			func_book_remove_by_qname	);
	
	GLib.Test.add_func ("/crank/base/book/invoke/index",
			func_book_invoke	);

	GLib.Test.add_func ("/crank/base/book/invoke/name",
			func_book_invoke_name	);
			
	GLib.Test.add_func ("/crank/base/book/invoke/qname",
			func_book_invoke_qname	);
	
	GLib.Test.add_func ("/crank/base/book/invoke_overwrite/index",
			func_book_invoke_overwrite	);

	GLib.Test.add_func ("/crank/base/book/invoke_overwrite/name",
			func_book_invoke_overwrite_name	);
			
	GLib.Test.add_func ("/crank/base/book/invoke_overwrite/qname",
			func_book_invoke_overwrite_qname	);
	
	GLib.Test.add_func ("/crank/base/book/invokev/index",
			func_book_invokev	);
	
	GLib.Test.run ();
	
	return 0;
}
