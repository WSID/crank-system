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

	public delegate void	FuncPointer ();

	public delegate R	Func0 <R> ();
	
	public delegate R	Func1 <R, A1>
			(A1 arg1);
			
	public delegate R	Func2 <R, A1, A2>
			(A1 arg1, A2 arg2);
		
	public delegate R	Func3 <R, A1, A2, A3>
			(A1 arg1, A2 arg2, A3 arg3);
	
	public delegate R	Func4 <R, A1, A2, A3, A4>
			(A1 arg1, A2 arg2, A3 arg3, A4 arg4);
			
	public delegate R	Func5 <R, A1, A2, A3, A4, A5>
			(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5);
	
	public delegate R	Func6 <R, A1, A2, A3, A4, A5, A6>
			(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6);
			
	public delegate R	Func7 <R, A1, A2, A3, A4, A5, A6, A7>
			(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7);
	
	[CCode (cname="CrankFunc0", has_target=false)]
	public delegate R	RFunc0 <R, U>
			(U userdata);
	
	[CCode (cname="CrankFunc1", has_target=false)]
	public delegate R	RFunc1 <R, A1, U>
			(A1 arg1,
			 U userdata);
			
	[CCode (cname="CrankFunc2", has_target=false)]
	public delegate R	RFunc2 <R, A1, A2, U>
			(A1 arg1, A2 arg2,
			 U userdata);
			
	[CCode (cname="CrankFunc3", has_target=false)]
	public delegate R	RFunc3 <R, A1, A2, A3, U>
			(A1 arg1, A2 arg2, A3 arg3,
			 U userdata);
			
	[CCode (cname="CrankFunc4", has_target=false)]
	public delegate R	RFunc4 <R, A1, A2, A3, A4, U>
			(A1 arg1, A2 arg2, A3 arg3, A4 arg4,
			 U userdata);
			
	[CCode (cname="CrankFunc5", has_target=false)]
	public delegate R	RFunc5 <R, A1, A2, A3, A4, A5, U>
			(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5,
			 U userdata);
			 
	[CCode (cname="CrankFunc6", has_target=false)]
	public delegate R	RFunc6 <R, A1, A2, A3, A4, A5, A6, U>
			(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6,
			 U userdata);
			 
	[CCode (cname="CrankFunc7", has_target=false)]
	public delegate R	RFunc7 <R, A1, A2, A3, A4, A5, A6, A7, U>
			(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7,
			 U userdata);
	
	[CCode (simple_generics=true, cname="CRANK_FUNC_POINTER_VALA_GET_POINTER")]
	public FP	func_pointer_get_pointer<FP> (FuncPointer pointer);
	
	[CCode (simple_generics=true, cname="CRANK_FUNC_POINTER_VALA_GET_USERDATA")]
	public U	func_pointer_get_userdata<U> (FuncPointer pointer);
	
	
	
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public unowned Func0<R>
	func_0_join <R, U>
			(	RFunc0<R, U>								fp,
				U											userdata	);	
	
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public unowned Func1<R, A1>
	func_1_join <R, A1, U>
			(	RFunc1<R, A1, U>							fp,
				U											userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public unowned Func2<R, A1, A2>
	func_2_join <R, A1, A2, U>
			(	RFunc2<R, A1, A2, U>						fp,
				U											userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public unowned Func3<R, A1, A2, A3>
	func_3_join <R, A1, A2, A3, U>
			(	RFunc3<R, A1, A2, A3, U>					fp,
				U											userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public unowned Func4<R, A1, A2, A3, A4>
	func_4_join <R, A1, A2, A3, A4, U>
			(	RFunc4<R, A1, A2, A3, A4, U>				fp,
				U											userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public unowned Func5<R, A1, A2, A3, A4, A5>
	func_5_join <R, A1, A2, A3, A4, A5, U>
			(	RFunc5<R, A1, A2, A3, A4, A5, U>			fp,
				U											userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public unowned Func6<R, A1, A2, A3, A4, A5, A6>
	func_6_join <R, A1, A2, A3, A4, A5, A6, U>
			(	RFunc6<R, A1, A2, A3, A4, A5, A6, U>		fp,
				U											userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public unowned Func7<R, A1, A2, A3, A4, A5, A6, A7>
	func_7_join <R, A1, A2, A3, A4, A5, A6, A7, U>
			(	RFunc7<R, A1, A2, A3, A4, A5, A6, A7, U>	fp,
				U											userdata	);
				
				
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public RFunc0<R, U>
	func_0_split <R, U>
			(	Func0<R>								fp,
				out unowned U							userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public RFunc1<R, A1, U>
	func_1_split <R, A1, U>
			(	Func1<R, A1>							fp,
				out unowned U							userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public RFunc2<R, A1, A2, U>
	func_2_split <R, A1, A2, U>
			(	Func2<R, A1, A2>						fp,
				out unowned U							userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public RFunc3<R, A1, A2, A3, U>
	func_3_split <R, A1, A2, A3, U>
			(	Func3<R, A1, A2, A3>					fp,
				out unowned U							userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public RFunc4<R, A1, A2, A3, A4, U>
	func_4_split <R, A1, A2, A3, A4, U>
			(	Func4<R, A1, A2, A3, A4>				fp,
				out unowned U							userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public RFunc5<R, A1, A2, A3, A4, A5, U>
	func_5_split <R, A1, A2, A3, A4, A5, U>
			(	Func5<R, A1, A2, A3, A4, A5>			fp,
				out unowned U							userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public RFunc6<R, A1, A2, A3, A4, A5, A6, U>
	func_6_split <R, A1, A2, A3, A4, A5, A6, U>
			(	Func6<R, A1, A2, A3, A4, A5, A6>		fp,
				out unowned U							userdata	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT")]
	public RFunc7<R, A1, A2, A3, A4, A5, A6, A7, U>
	func_7_split <R, A1, A2, A3, A4, A5, A6, A7, U>
			(	Func7<R, A1, A2, A3, A4, A5, A6, A7>	fp,
				out unowned U							userdata	);
	

	
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public Func0<R>
	func_0_join_owned <R, U>
			(	RFunc0<R, U>								fp,
				U											userdata,
				GLib.DestroyNotify							destroy	);
	
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public Func1<R, A1>
	func_1_join_owned <R, A1, U>
			(	RFunc1<R, A1, U>							fp,
				U											userdata,
				GLib.DestroyNotify							destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public Func2<R, A1, A2>
	func_2_join_owned <R, A1, A2, U>
			(	RFunc2<R, A1, A2, U>						fp,
				U											userdata,
				GLib.DestroyNotify							destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public Func3<R, A1, A2, A3>
	func_3_join_owned <R, A1, A2, A3, U>
			(	RFunc3<R, A1, A2, A3, U>					fp,
				U											userdata,
				GLib.DestroyNotify							destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public Func4<R, A1, A2, A3, A4>
	func_4_join_owned <R, A1, A2, A3, A4, U>
			(	RFunc4<R, A1, A2, A3, A4, U>				fp,
				U											userdata,
				GLib.DestroyNotify							destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public Func5<R, A1, A2, A3, A4, A5>
	func_5_join_owned <R, A1, A2, A3, A4, A5, U>
			(	RFunc5<R, A1, A2, A3, A4, A5, U>			fp,
				U											userdata,
				GLib.DestroyNotify							destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public Func6<R, A1, A2, A3, A4, A5, A6>
	func_6_join_owned <R, A1, A2, A3, A4, A5, A6, U>
			(	RFunc6<R, A1, A2, A3, A4, A5, A6, U>		fp,
				U											userdata,
				GLib.DestroyNotify							destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public Func7<R, A1, A2, A3, A4, A5, A6, A7>
	func_7_join_owned <R, A1, A2, A3, A4, A5, A6, A7, U>
			(	RFunc7<R, A1, A2, A3, A4, A5, A6, A7, U>	fp,
				U											userdata,
				GLib.DestroyNotify							destroy	);
				
				
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public RFunc0<R, U>
	func_0_split_owned <R, U>
			(	Func0<R>								fp,
				out unowned U							userdata,
				out GLib.DestroyNotify					destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public RFunc1<R, A1, U>
	func_1_split_owned <R, A1, U>
			(	Func1<R, A1>							fp,
				out unowned U							userdata,
				out GLib.DestroyNotify					destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public RFunc2<R, A1, A2, U>
	func_2_split_owned <R, A1, A2, U>
			(	Func2<R, A1, A2>						fp,
				out unowned U							userdata,
				out GLib.DestroyNotify					destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public RFunc3<R, A1, A2, A3, U>
	func_3_split_owned <R, A1, A2, A3, U>
			(	Func3<R, A1, A2, A3>					fp,
				out unowned U							userdata,
				out GLib.DestroyNotify					destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public RFunc4<R, A1, A2, A3, A4, U>
	func_4_split_owned <R, A1, A2, A3, A4, U>
			(	Func4<R, A1, A2, A3, A4>				fp,
				out unowned U							userdata,
				out GLib.DestroyNotify					destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public RFunc5<R, A1, A2, A3, A4, A5, U>
	func_5_split_owned <R, A1, A2, A3, A4, A5, U>
			(	Func5<R, A1, A2, A3, A4, A5>			fp,
				out unowned U							userdata,
				out GLib.DestroyNotify					destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public RFunc6<R, A1, A2, A3, A4, A5, A6, U>
	func_6_split_owned <R, A1, A2, A3, A4, A5, A6, U>
			(	Func6<R, A1, A2, A3, A4, A5, A6>		fp,
				out unowned U							userdata,
				out GLib.DestroyNotify					destroy	);
				
	[CCode (simple_generics=true, cname="CRANK_FUNC_VALA_JOIN_SPLIT_OWNED")]
	public RFunc7<R, A1, A2, A3, A4, A5, A6, A7, U>
	func_7_split_owned <R, A1, A2, A3, A4, A5, A6, A7, U>
			(	Func7<R, A1, A2, A3, A4, A5, A6, A7>	fp,
				out unowned U							userdata,
				out GLib.DestroyNotify					destroy	);

	[CCode (cname="CRANK_VALA_GENERIC_UNOWNED")]
	public bool	generic_unowned <G> ();


	public class FuncType {
		[CCode (sentinel="G_TYPE_NONE")]
		public FuncType (GLib.Type return_type, ...);
		
		public GLib.Type		return_type 		{	get;	}
		public uint				nparam_types 		{	get;	}
		public GLib.Type[]		param_types			{	get;	}
	}
}
