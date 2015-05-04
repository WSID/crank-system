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
	}
}
