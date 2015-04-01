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
	
	GLib.Test.run ();
	
	return 0;
}
