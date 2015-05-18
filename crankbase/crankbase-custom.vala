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

/*
 * 이 파일은 생성된 vapi에 추가될 파일입니다.
 */

[CCode (cheader_filename="crankbase.h")]
namespace Crank {

	public delegate void	Callback ();
	
	[CCode (simple_generics=true, cname="CRANK_VALA_FUNC_GET_POINTER")]
	public GLib.Callback	func_get_pointer (Crank.Callback pointer);
	
	[CCode (simple_generics=true, cname="CRANK_VALA_FUNC_GET_USERDATA")]
	public void*	func_get_userdata (Crank.Callback pointer);
	
	
	
	[CCode (simple_generics=true, cname="CRANK_VALA_FUNC_JOIN_SPLIT")]
	public unowned Crank.Callback func_join	(
			GLib.Callback	fp,
			void*			userdata);
	
	[CCode (simple_generics=true, cname="CRANK_VALA_FUNC_JOIN_SPLIT")]
	public GLib.Callback func_split (
			Crank.Callback	cb,
			out void*		userdata);

	
	[CCode (simple_generics=true, cname="CRANK_VALA_FUNC_JOIN_SPLIT_OWNED")]
	public Crank.Callback func_join_owned (
			GLib.Callback		fp,
			void*				userdata,
			GLib.DestroyNotify	destroy);
				
				
	[CCode (simple_generics=true, cname="CRANK_VALA_FUNC_JOIN_SPLIT_OWNED")]
	public GLib.Callback func_split_owned (
				Crank.Callback				fp,
				out void*					userdata,
				out GLib.DestroyNotify		destroy	);

	[CCode (cname="CRANK_VALA_GENERIC_UNOWNED")]
	public bool	generic_unowned <G> ();
	
	[CCode (cname="crank_vala_create_closure")]
	public GLib.Closure	create_closure (	owned Crank.Callback callback,
											GLib.ClosureMarshal? marshal = null	);
	
	[CCode (cname="g_closure_invoke")]
	public void closure_invoke (	GLib.Closure	closure,
									ref GLib.Value	return_value,
										[CCode (array_length_pos=2.5)]
									GLib.Value[]	param_types,
									void*			invocation_hint = null);
	
	
	
	[Compact]
	public class Digraph {
		public unowned GLib.List <DigraphNode> nodes { get; }
		public unowned GLib.List <DigraphEdge> edges { get; }
	}
	
	[Compact]
	public class DigraphNode {
		public GLib.List <unowned DigraphEdge>	in_edges { get; }
		public GLib.List <unowned DigraphEdge>	out_edges { get; }
		
		public GLib.List <unowned DigraphNode>	in_nodes { owned get; }
		public GLib.List <unowned DigraphNode>	out_nodes { owned get; }
		
		public uint	indegree { get; }
		public uint outdegree { get; }
	}
	
	[Compact]
	public class DigraphEdge {
		public DigraphNode	tail { get; }
		public DigraphNode	head { get; }
	}
	
	public struct VecBool2 {
		public bool	x;
		public bool y;
		
		public VecBool2 		(bool x, bool y);
		public VecBool2.arr		(bool arr[2]);
		public VecBool2.valist	(va_list varargs);
		
		public bool			get (uint	index);
		public void			set (uint	index, bool value);
		
		public VecBool2		and (VecBool2 b);
		public VecBool2		or (VecBool2 b);
		public VecBool2		xor (VecBool2 b);
		
		public VecBool2		not	();
		
		public bool			any { get; }
		public bool			all { get; }
		
		public static bool	equal (VecBool2 a, VecBool2 b);
		public static uint	hash (VecBool2 vec);
		
		[CCode (cname="crank_vec_bool2_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string on_true	= "true",
										string on_false = "false" );
	}
	
	public struct VecBool3 {
		public bool	x;
		public bool y;
		public bool z;
		
		public VecBool3 		(bool x, bool y);
		public VecBool3.arr		(bool arr[3]);
		public VecBool3.valist	(va_list varargs);
		
		public bool			get (uint	index);
		public void			set (uint	index, bool value);
		
		public VecBool3		and (VecBool3 b);
		public VecBool3		or (VecBool3 b);
		public VecBool3		xor (VecBool3 b);
		
		public VecBool3		not	();
		
		public bool			any { get; }
		public bool			all { get; }
		
		public static bool	equal (VecBool3 a, VecBool3 b);
		public static uint	hash (VecBool3 vec);
		
		[CCode (cname="crank_vec_bool3_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string on_true	= "true",
										string on_false = "false" );
	}
	
	public struct VecBool4 {
		public bool	x;
		public bool y;
		public bool z;
		public bool w;
		
		public VecBool4 		(bool x, bool y);
		public VecBool4.arr		(bool arr[4]);
		public VecBool4.valist	(va_list varargs);
		
		public bool			get (uint	index);
		public void			set (uint	index, bool value);
		
		public VecBool4		and (VecBool4 b);
		public VecBool4		or (VecBool4 b);
		public VecBool4		xor (VecBool4 b);
		
		public VecBool4		not	();
		
		public bool			any { get; }
		public bool			all { get; }
		
		public static bool	equal (VecBool4 a, VecBool4 b);
		public static uint	hash (VecBool4 vec);
		
		[CCode (cname="crank_vec_bool4_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string on_true	= "true",
										string on_false = "false" );
	}
	
	[CCode (	destroy_function="crank_vec_bool_n_fini",
				free_function="crank)vec_bool_n_free"	)]
	public struct VecBoolN {
		[CCode (	array_length_cname="n"	)]
		public bool[]	data;
		
		public VecBoolN 		(uint n, ...);
		public VecBoolN.arr		([CCode (array_length_pos=0.5)]bool arr[]);
		public VecBoolN.valist	(uint n, va_list varargs);
		
		public uint			size {	get; }
		
		public bool			get (uint	index);
		public void			set (uint	index, bool value);
		
		public VecBoolN		and (VecBoolN b);
		public VecBoolN		or (VecBoolN b);
		public VecBoolN		xor (VecBoolN b);
		
		public VecBoolN		not	();
		
		public bool			any { get; }
		public bool			all { get; }
		
		public static bool	equal (VecBoolN a, VecBoolN b);
		public static uint	hash (VecBoolN vec);
		
		[CCode (cname="crank_vec_bool_n_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string on_true	= "true",
										string on_false = "false" );
	}
	

	public class FuncType {
		[CCode (sentinel="G_TYPE_NONE")]
		public FuncType (GLib.Type return_type, ...);
		
		public GLib.Type		return_type 		{	get;	}
		public uint				nparam_types 		{	get;	}
		public GLib.Type[]		param_types			{	get;	}
	}
	
	public class FuncHolder {
		public string			name				{	get;set;	}
		public GLib.Quark		qname				{	get;set;	}
	
		public void set_func (	Crank.FuncType 			types,
								owned Crank.Callback 	func,
								GLib.ClosureMarshal? 	marshal=null	);
		
		public bool invokev (	ref GLib.Value			return_value,
								void*					invocation_hint,
								uint					narg_values,
								...	);
		
		public bool invoke_va (	ref GLib.Value			return_value,
								void*					invocation_hint,
								uint					narg_values,
								va_list					varargs	);
								
		public bool invokev_overwrite (
								out GLib.Value			return_value,
								void*					invocation_hint,
								uint					narg_values,
								...	);
		
		public bool invoke_va_overwrite (
								out GLib.Value			return_value,
								void*					invocation_hint,
								uint					narg_values,
								va_list					varargs	);
	}
	
	public class FuncBook {
		public string?			name				{	get;set;	}
		public GLib.Quark		qname				{	get;set;	}
		
		
		public bool invokev (	uint					index,
								ref GLib.Value			return_value,
								void*					invocation_hint,
								uint					narg_values,
								...	);
		
		public bool invoke_va (	uint					index,
								ref GLib.Value			return_value,
								void*					invocation_hint,
								uint					narg_values,
								va_list					varargs	);
		
		public bool invokev_overwrite (
								uint					index,
								out GLib.Value			return_value,
								void*					invocation_hint,
								uint					narg_values,
								...	);
		
		public bool invoke_va_overwrite (	
								uint					index,
								out GLib.Value			return_value,
								void*					invocation_hint,
								uint					narg_values,
								va_list					varargs	);
	}
}
