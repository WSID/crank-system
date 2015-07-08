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
		public unowned GLib.GenericArray <DigraphNode> nodes { get; }
		public unowned GLib.GenericArray <DigraphEdge> edges { get; }
	}
	
	[Compact]
	public class DigraphNode {
		public GLib.GenericArray <unowned DigraphEdge>	in_edges { get; }
		public GLib.GenericArray <unowned DigraphEdge>	out_edges { get; }
		
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
	
	[CCode (copy_function="crank_permutation_copy",
			destroy_function="crank_permutation_fini",
			free_function="crank_permutation_free")]
	public struct Permutation {
		public Permutation (uint n, ...);
		public Permutation.arr ([CCode (array_length_pos=0)]uint[] data);
		public Permutation.arr_take ([CCode (array_length_pos=0)]owned uint[] data);
		
		public Permutation.identity (uint n);
		
		public Permutation? dup();
		
		public uint size { get; }
		
		public uint get (uint i);
		public int index_of (uint v);
		
		public int sign { get; }
		
		public bool check_valid ();
		public void	swap (uint i, uint j);
		
		public Permutation reverse ();
		public Permutation inverse ();
		
		public Permutation shuffle (Permutation q);
	}
	

	[CCode (copy_function="crank_vec_bool2_copy")]
	public struct VecBool2 {
		public bool	x;
		public bool y;
		
		public VecBool2 		(bool x, bool y);
		public VecBool2.arr		(bool arr[2]);
		public VecBool2.valist	(va_list varargs);
		
		public VecBool2?	dup ();

		public bool			get (uint	index);
		public void			set (uint	index, bool value);
		public bool			foreach (Crank.BoolBoolFunc func);
		
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
	
	[CCode (copy_function="crank_vec_bool3_copy")]
	public struct VecBool3 {
		public bool	x;
		public bool y;
		public bool z;
		
		public VecBool3 		(bool x, bool y);
		public VecBool3.arr		(bool arr[3]);
		public VecBool3.valist	(va_list varargs);
		
		public VecBool3?	dup ();

		public bool			get (uint	index);
		public void			set (uint	index, bool value);
		public bool			foreach (Crank.BoolBoolFunc func);
		
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
	
	[CCode (copy_function="crank_vec_bool4_copy")]
	public struct VecBool4 {
		public bool	x;
		public bool y;
		public bool z;
		public bool w;
		
		public VecBool4 		(bool x, bool y);
		public VecBool4.arr		(bool arr[4]);
		public VecBool4.valist	(va_list varargs);
		
		public VecBool4?	dup ();

		public bool			get (uint	index);
		public void			set (uint	index, bool value);
		public bool			foreach (Crank.BoolBoolFunc func);
		
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
	
	[CCode (	copy_function="crank_vec_bool_n_copy",
				destroy_function="crank_vec_bool_n_fini",
				free_function="crank)vec_bool_n_free"	)]
	public struct VecBoolN {
		[CCode (	array_length_cname="n"	)]
		public bool[]	data;
		
		public VecBoolN 		(uint n, ...);
		public VecBoolN.arr		([CCode (array_length_pos=0.5)]bool arr[]);
		public VecBoolN.valist	(uint n, va_list varargs);
		
		public VecBoolN?	dup ();

		public uint			size {	get; }
		
		public bool			get (uint	index);
		public void			set (uint	index, bool value);
		public void			prepend (bool value);
		public void			append (bool value);
		public void			insert (uint index, bool value);
		public void			remove (uint index);
		public bool			foreach (Crank.BoolBoolFunc func);
		
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
	
	
	[CCode (copy_function="crank_vec_int2_copy")]
	public struct VecInt2 {
		public int x;
		public int y;
		
		public VecInt2 		(int x, int y);
		public VecInt2.arr		(int arr[2]);
		public VecInt2.valist	(va_list varargs);
		public VecInt2.fill		(int	fill);
		public VecInt2.from_vb	(VecBool2	vb);
		
		public VecInt2?	dup	();
		
		public int			get (uint	index);
		public void			set (uint	index, int value);
		public bool			foreach (Crank.BoolIntFunc func);
		
		public static uint	hash (VecInt2	a);
		public static bool	equal (VecInt2	a, VecInt2	b);
		
		[CCode (cname="crank_vec_int2_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string format	= "%d"	);
		public uint			magn_sq {get;}
		public float		magn {get;}
		
		public VecInt2		neg		();
		
		public VecInt2		muls	(	int b	);
		public VecInt2		divs	(	int	b	);
		public VecInt2		mods	(	int b	);
		
		public VecInt2		add		(	VecInt2 b	);
		public VecInt2		sub		(	VecInt2	b	);
		public int			dot		(	VecInt2	b	);
		
		public VecInt2		cmpmul	(	VecInt2	b	);
		public VecInt2		cmpdiv	(	VecInt2	b	);
		public VecInt2		cmpmod	(	VecInt2	b	);
		
		public VecBool2		cmpless	(	VecInt2 b	);
		public VecBool2		cmpeq	(	VecInt2	b	);
		public VecBool2		cmpgreater	(	VecInt2	b	);
		public VecInt2		cmpcmp	(	VecInt2	b	);

		public VecInt2		min (		VecInt2 b	);
		public VecInt2		max (		VecInt2 b	);
	}
	
	[CCode (copy_function="crank_vec_int3_copy")]
	public struct VecInt3 {
		public int x;
		public int y;
		public int z;
		
		public VecInt3 		(int x, int y, int z);
		public VecInt3.arr		(int arr[3]);
		public VecInt3.valist	(va_list varargs);
		public VecInt3.fill		(int	fill);
		public VecInt3.from_vb	(VecBool3	vb);
		
		public VecInt3?	dup	();
		
		public int			get (uint	index);
		public void			set (uint	index, int value);
		public bool			foreach (Crank.BoolIntFunc func);
		
		public static uint	hash (VecInt3	a);
		public static bool	equal (VecInt3	a, VecInt3	b);
		
		[CCode (cname="crank_vec_int3_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string format	= "%d"	);
		public uint			magn_sq {get;}
		public float		magn {get;}
		
		public VecInt3		neg		();
		
		public VecInt3		muls	(	int b	);
		public VecInt3		divs	(	int	b	);
		public VecInt3		mods	(	int b	);
		
		public VecInt3		add		(	VecInt3 b	);
		public VecInt3		sub		(	VecInt3	b	);
		public int			dot		(	VecInt3	b	);
		public VecInt3		crs		(	VecInt3	b	);
		
		public VecInt3		cmpmul	(	VecInt3	b	);
		public VecInt3		cmpdiv	(	VecInt3	b	);
		public VecInt3		cmpmod	(	VecInt3	b	);
		
		public VecBool3		cmpless	(	VecInt3 b	);
		public VecBool3		cmpeq	(	VecInt3	b	);
		public VecBool3		cmpgreater	(	VecInt3	b	);
		public VecInt3		cmpcmp	(	VecInt3	b	);

		public VecInt3		min (		VecInt3 b	);
		public VecInt3		max (		VecInt3 b	);
	}
	
	[CCode (copy_function="crank_vec_int4_copy")]
	public struct VecInt4 {
		public int x;
		public int y;
		public int z;
		public int w;
		
		public VecInt4 		(int x, int y, int z, int w);
		public VecInt4.arr		(int arr[4]);
		public VecInt4.valist	(va_list varargs);
		public VecInt4.fill		(int	fill);
		public VecInt4.from_vb	(VecBool4	vb);
		
		public VecInt4?	dup	();
		
		public int			get (uint	index);
		public void			set (uint	index, int value);
		public bool			foreach (Crank.BoolIntFunc func);
		
		public static uint	hash (VecInt4	a);
		public static bool	equal (VecInt4	a, VecInt4	b);
		
		[CCode (cname="crank_vec_int4_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string format	= "%d"	);
		public uint			magn_sq {get;}
		public float		magn {get;}
		
		public VecInt4		neg		();
		
		public VecInt4		muls	(	int b	);
		public VecInt4		divs	(	int	b	);
		public VecInt4		mods	(	int b	);
		
		public VecInt4		add		(	VecInt4 b	);
		public VecInt4		sub		(	VecInt4	b	);
		public int			dot		(	VecInt4	b	);
		
		public VecInt4		cmpmul	(	VecInt4	b	);
		public VecInt4		cmpdiv	(	VecInt4	b	);
		public VecInt4		cmpmod	(	VecInt4	b	);
		
		public VecBool4		cmpless	(	VecInt4 b	);
		public VecBool4		cmpeq	(	VecInt4	b	);
		public VecBool4		cmpgreater	(	VecInt4	b	);
		public VecInt4		cmpcmp	(	VecInt4	b	);

		public VecInt4		min (		VecInt4 b	);
		public VecInt4		max (		VecInt4 b	);
	}
	
	
	[CCode (	copy_function="crank_vec_int_n_copy",
				destroy_function="crank_vec_int_n_fini",
				free_function="crank_vec_int_n_free"	)]
	public struct VecIntN {
		[CCode (array_length_cname="n")]
		public int[] data;
		
		public VecIntN 		(uint n, ...);
		public VecIntN.arr		([CCode (array_length_pos=0.5)] int[] arr);
		public VecIntN.valist	(uint n, va_list varargs);
		public VecIntN.fill		(uint n, int	fill);
		public VecIntN.from_vb	(VecBoolN	vb);
		
		public VecIntN?	dup	();
		
		public uint			size { get; }

		public int			get (uint	index);
		public void			set (uint	index, int value);
		public void			prepend (int value);
		public void			append (int value);
		public void			insert (uint index, int value);
		public void			remove (uint index);
		public bool			foreach (Crank.BoolIntFunc func);
		
		public static uint	hash (VecIntN	a);
		public static bool	equal (VecIntN	a, VecIntN	b);
		
		[CCode (cname="crank_vec_int_n_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string format	= "%d"	);
		public uint			magn_sq {get;}
		public float		magn {get;}
		
		public VecIntN		neg		();
		
		public VecIntN		muls	(	int b	);
		public VecIntN		divs	(	int	b	);
		public VecIntN		mods	(	int b	);
		
		public VecIntN		add		(	VecIntN b	);
		public VecIntN		sub		(	VecIntN	b	);
		public int			dot		(	VecIntN	b	);
		
		public VecIntN		cmpmul	(	VecIntN	b	);
		public VecIntN		cmpdiv	(	VecIntN	b	);
		public VecIntN		cmpmod	(	VecIntN	b	);
		
		public VecBoolN		cmpless	(	VecIntN b	);
		public VecBoolN		cmpeq	(	VecIntN	b	);
		public VecBoolN		cmpgreater	(	VecIntN	b	);
		public VecIntN		cmpcmp	(	VecIntN	b	);

		public VecIntN		min (		VecIntN b	);
		public VecIntN		max (		VecIntN b	);
	}
	
	[CCode (copy_function="crank_vec_float2_copy")]
	public struct VecFloat2 {
		public float x;
		public float y;
		
		public VecFloat2 		(float x, float y);
		public VecFloat2.arr		(float arr[2]);
		public VecFloat2.valist	(va_list varargs);
		public VecFloat2.fill		(int	fill);
		public VecFloat2.from_vb	(VecBool2	vb);
		public VecFloat2.from_vi	(VecInt2	vi);
		
		public VecFloat2?	dup	();
		
		public float		get (uint	index);
		public void			set (uint	index, float value);
		public bool			foreach (Crank.BoolFloatFunc func);
		
		public static uint	hash (VecFloat2	a);
		public static bool	equal (VecFloat2	a, VecFloat2	b);
		
		[CCode (cname="crank_vec_float2_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string format	= "%g"	);
		public float		magn_sq {get;}
		public float		magn {get;}
		
		public VecFloat2		neg		();
		public VecFloat2		unit	();
		
		public VecFloat2		muls	(	float b	);
		public VecFloat2		divs	(	float	b	);
		
		public VecFloat2		add		(	VecFloat2 	b	);
		public VecFloat2		sub		(	VecFloat2	b	);
		public float			dot		(	VecFloat2	b	);
		
		public VecFloat2		cmpmul	(	VecFloat2	b	);
		public VecFloat2		cmpdiv	(	VecFloat2	b	);
		
		public VecBool2		cmpless	(	VecFloat2 b	);
		public VecBool2		cmpeq	(	VecFloat2	b	);
		public VecBool2		cmpgreater	(	VecFloat2	b	);
		public VecInt2		cmpcmp	(	VecFloat2	b	);

		public VecFloat2		min (		VecFloat2 b	);
		public VecFloat2		max (		VecFloat2 b	);
		
		public VecFloat2		mulm (		MatFloat2 b	);

		public VecFloat2		mixs (		VecFloat2 b, float c	);
		public VecFloat2		mix (		VecFloat2 b, VecFloat2 c	);
	}
	

	[CCode (copy_function="crank_vec_float3_copy")]
	public struct VecFloat3 {
		public float x;
		public float y;
		public float z;
		
		public VecFloat3 			(float x, float y, float z);
		public VecFloat3.arr		(float arr[3]);
		public VecFloat3.valist		(va_list varargs);
		public VecFloat3.fill		(int	fill);
		public VecFloat3.from_vb	(VecBool3	vb);
		public VecFloat3.from_vi	(VecInt3	vi);
		
		public VecFloat3?	copy	();
		
		public float		get (uint	index);
		public void			set (uint	index, float value);
		public bool			foreach (Crank.BoolFloatFunc func);
		
		public static uint	hash (VecFloat3	a);
		public static bool	equal (VecFloat3	a, VecFloat3	b);
		
		[CCode (cname="crank_vec_float3_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string format	= "%g"	);
		public float		magn_sq {get;}
		public float		magn {get;}
		
		public VecFloat3		neg		();
		public VecFloat3		unit	();
		
		public VecFloat3		muls	(	float b	);
		public VecFloat3		divs	(	float	b	);
		
		public VecFloat3		add		(	VecFloat3 	b	);
		public VecFloat3		sub		(	VecFloat3	b	);
		public float			dot		(	VecFloat3	b	);
		public VecFloat3		crs		(	VecFloat3	b	);
		
		public VecFloat3		cmpmul	(	VecFloat3	b	);
		public VecFloat3		cmpdiv	(	VecFloat3	b	);
		
		public VecBool3		cmpless	(	VecFloat3 b	);
		public VecBool3		cmpeq	(	VecFloat3	b	);
		public VecBool3		cmpgreater	(	VecFloat3	b	);
		public VecInt3		cmpcmp	(	VecFloat3	b	);

		public VecFloat3		min (		VecFloat3 b	);
		public VecFloat3		max (		VecFloat3 b	);
		
		public VecFloat3		mulm (		MatFloat3 b	);

		public VecFloat3		mixs (		VecFloat3 b, float c	);
		public VecFloat3		mix (		VecFloat3 b, VecFloat3 c	);
	}
	
	[CCode (copy_function="crank_vec_float4_copy")]
	public struct VecFloat4 {
		public float x;
		public float y;
		public float z;
		public float w;
		
		public VecFloat4 			(float x, float y, float z, float w);
		public VecFloat4.arr		(float arr[4]);
		public VecFloat4.valist		(va_list varargs);
		public VecFloat4.fill		(int	fill);
		public VecFloat4.from_vb	(VecBool4	vb);
		public VecFloat4.from_vi	(VecInt4	vi);
		
		public VecFloat4?	dup	();
		
		public float		get (uint	index);
		public void			set (uint	index, float value);
		public bool			foreach (Crank.BoolFloatFunc func);
		
		public static uint	hash (VecFloat4	a);
		public static bool	equal (VecFloat4	a, VecFloat4	b);
		
		[CCode (cname="crank_vec_float3_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string format	= "%g"	);
		public float		magn_sq {get;}
		public float		magn {get;}
		
		public VecFloat4		neg		();
		public VecFloat4		unit	();
		
		public VecFloat4		muls	(	float b	);
		public VecFloat4		divs	(	float	b	);
		
		public VecFloat4		add		(	VecFloat4 	b	);
		public VecFloat4		sub		(	VecFloat4	b	);
		public float			dot		(	VecFloat4	b	);
		
		public VecFloat4		cmpmul	(	VecFloat4	b	);
		public VecFloat4		cmpdiv	(	VecFloat4	b	);
		
		public VecBool4		cmpless	(	VecFloat4 b	);
		public VecBool4		cmpeq	(	VecFloat4	b	);
		public VecBool4		cmpgreater	(	VecFloat4	b	);
		public VecInt4		cmpcmp	(	VecFloat4	b	);

		public VecFloat4		min (		VecFloat4 b	);
		public VecFloat4		max (		VecFloat4 b	);
		
		public VecFloat4		mulm (		MatFloat4 b	);

		public VecFloat4		mixs (		VecFloat4 b, float c	);
		public VecFloat4		mix (		VecFloat4 b, VecFloat4 c	);
	}
	
	
	[CCode (	copy_function="crank_vec_float_n_copy",
				destroy_function="crank_vec_float_n_fini",
				free_function="crank_vec_float_n_free"	)]
	public struct VecFloatN {
		[CCode (array_length_cname="n")]
		public float[]	data;
		
		public VecFloatN 			(uint	n,	...);
		public VecFloatN.arr		([CCode (array_length_pos=0)]float arr[]);
		public VecFloatN.arr_take	([CCode (array_length_pos=0)]owned float arr[]);
		public VecFloatN.valist		(uint	n, va_list varargs);
		public VecFloatN.fill		(uint	n, float	fill);
		public VecFloatN.from_vb	(VecBoolN	vb);
		public VecFloatN.from_vi	(VecIntN	vi);
		
		public VecFloatN?	dup	();
		
		public uint			size { get; }

		public float		get (uint	index);
		public void			set (uint	index, float value);
		public void			prepend (float value);
		public void			append (float value);
		public void			insert (uint index, float value);
		public void			remove (uint index);
		public bool			foreach (Crank.BoolFloatFunc func);
		
		public static uint	hash (VecFloatN	a);
		public static bool	equal (VecFloatN	a, VecFloatN	b);
		
		[CCode (cname="crank_vec_float_n_to_string_full")]
		public string		to_string (	string left		= "(",
										string @in		= ", ",
										string right	= ")",
										string format	= "%g"	);
		public float		magn_sq {get;}
		public float		magn {get;}
		
		public VecFloatN		neg		();
		public VecFloatN		unit	();
		
		public VecFloatN		muls	(	float b	);
		public VecFloatN		divs	(	float	b	);
		
		public VecFloatN		add		(	VecFloatN 	b	);
		public VecFloatN		sub		(	VecFloatN	b	);
		public float			dot		(	VecFloatN	b	);
		
		public VecFloatN		cmpmul	(	VecFloatN	b	);
		public VecFloatN		cmpdiv	(	VecFloatN	b	);
		
		public VecBoolN		cmpless	(	VecFloatN b	);
		public VecBoolN		cmpeq	(	VecFloatN	b	);
		public VecBoolN		cmpgreater	(	VecFloatN	b	);
		public VecIntN		cmpcmp	(	VecFloatN	b	);

		public VecFloatN		min (		VecFloatN b	);
		public VecFloatN		max (		VecFloatN b	);
		
		public VecFloatN		mulm (		MatFloatN b	);

		public VecFloatN		mixs (		VecFloatN b, float c	);
		public VecFloatN		mix (		VecFloatN b, VecFloatN c	);
	}


	public struct MatFloat2 {
		public float m00;
		public float m01;
		public float m10;
		public float m11;

		public MatFloat2 (float m00, float m01, float m10, float m11);
		public MatFloat2.arr (float marr[4]);
		public MatFloat2.rv (VecFloat2 rv0, VecFloat2 rv1);
		public MatFloat2.rvarr (VecFloat2 rvarr[2]);
		public MatFloat2.cv (VecFloat2 cv0, VecFloat2 cv1);
		public MatFloat2.cvarr (VecFloat2 cvarr[2]);
		public MatFloat2.diag (float m00, float m11);
		public MatFloat2.diag_arr (float darr[2]);
		public MatFloat2.fill (float fill);

		public MatFloat2	copy ();
		public MatFloat2?	dup ();

		public static uint	hash (	MatFloat2?	a);
		public static bool	equal (	MatFloat2?	a, MatFloat2?	b);

		[CCode (cname="crank_mat_float2_to_string_full")]
		public string	to_string (	string	mat_left = "[",
									string	mat_in = ", ",
									string	mat_right = "]",
									string	row_left = "[",
									string	row_in = ", ",
									string	row_right = "]",
									string	format = "%g"	);

		public float	get (uint i, uint j);
		public void		set (uint i, uint j, float value);

		public VecFloat2	get_row (uint index);
		public void			set_row (uint index, VecFloat2 row);
		public VecFloat2	get_col (uint index);
		public void			set_col (uint index, VecFloat2 col);

		public float		tr { get; }
		public float		det { get; }
		public MatFloat2	cof { owned get; }
		public MatFloat2	adj { owned get; }

		public MatFloat2	neg ();
		public MatFloat2	transpose ();
		public MatFloat2	inverse ();

		public MatFloat2	muls (float b);
		public MatFloat2	divs (float b);
		public VecFloat2	mulv (VecFloat2 b);

		public MatFloat2	add (MatFloat2 b);
		public MatFloat2	sub (MatFloat2 b);

		public MatFloat2	mul (MatFloat2 b);

		public MatFloat2	mixs (MatFloat2 b, float c);
		public MatFloat2	mix (MatFloat2 b, MatFloat2 c);

	}

	public struct MatFloat3 {
		public float m00;
		public float m01;
		public float m02;
		public float m10;
		public float m11;
		public float m12;
		public float m20;
		public float m21;
		public float m22;

		public MatFloat3 (	float m00, float m01, float m02,
							float m10, float m11, float m12,
							float m20, float m21, float m22);
		public MatFloat3.arr (float marr[9]);
		public MatFloat3.rv (VecFloat3 rv0, VecFloat3 rv1, VecFloat3 rv2);
		public MatFloat3.rvarr (VecFloat3 rvarr[3]);
		public MatFloat3.cv (VecFloat3 cv0, VecFloat3 cv1, VecFloat3 cv2);
		public MatFloat3.cvarr (VecFloat3 cvarr[3]);
		public MatFloat3.diag (float m00, float m11, float m22);
		public MatFloat3.diag_arr (float darr[3]);
		public MatFloat3.fill (float fill);

		public MatFloat3	copy ();
		public MatFloat3?	dup ();

		public static uint	hash (	MatFloat3?	a);
		public static bool	equal (	MatFloat3?	a, MatFloat3?	b);

		[CCode (cname="crank_mat_float3_to_string_full")]
		public string	to_string (	string	mat_left = "[",
									string	mat_in = ", ",
									string	mat_right = "]",
									string	row_left = "[",
									string	row_in = ", ",
									string	row_right = "]",
									string	format = "%g"	);

		public float	get (uint i, uint j);
		public void		set (uint i, uint j, float value);

		public VecFloat3	get_row (uint index);
		public void			set_row (uint index, VecFloat3 row);
		public VecFloat3	get_col (uint index);
		public void			set_col (uint index, VecFloat3 col);

		public float		tr { get; }
		public float		det { get; }
		public MatFloat3	cof { owned get; }
		public MatFloat3	adj { owned get; }

		public MatFloat3	neg ();
		public MatFloat3	transpose ();
		public MatFloat3	inverse ();

		public MatFloat3	muls (float b);
		public MatFloat3	divs (float b);
		public VecFloat3	mulv (VecFloat3 b);

		public MatFloat3	add (MatFloat3 b);
		public MatFloat3	sub (MatFloat3 b);
		public MatFloat3	mul (MatFloat3 b);

		public MatFloat3	mixs (MatFloat3 b, float c);
		public MatFloat3	mix (MatFloat3 b, MatFloat3 c);
	}

	public struct MatFloat4 {
		public float m00;
		public float m01;
		public float m02;
		public float m03;
		public float m10;
		public float m11;
		public float m12;
		public float m13;
		public float m20;
		public float m21;
		public float m22;
		public float m23;
		public float m30;
		public float m31;
		public float m32;
		public float m33;

		public MatFloat4 (	float m00, float m01, float m02, float m03,
							float m10, float m11, float m12, float m13,
							float m20, float m21, float m22, float m23,
							float m30, float m31, float m32, float m33	);
		public MatFloat4.arr (float marr[16]);
		public MatFloat4.rv (VecFloat4 rv0, VecFloat4 rv1, VecFloat4 rv2, VecFloat4 rv3);
		public MatFloat4.rvarr (VecFloat4 rvarr[4]);
		public MatFloat4.cv (VecFloat4 cv0, VecFloat4 cv1, VecFloat4 cv2, VecFloat4 cv3);
		public MatFloat4.cvarr (VecFloat4 cvarr[4]);
		public MatFloat4.diag (float m00, float m11, float m22, float m33);
		public MatFloat4.diag_arr (float darr[4]);
		public MatFloat4.fill (float fill);

		public MatFloat4	copy ();
		public MatFloat4?	dup ();

		public static uint	hash (	MatFloat4?	a);
		public static bool	equal (	MatFloat4?	a, MatFloat4?	b);

		[CCode (cname="crank_mat_float4_to_string_full")]
		public string	to_string (	string	mat_left = "[",
									string	mat_in = ", ",
									string	mat_right = "]",
									string	row_left = "[",
									string	row_in = ", ",
									string	row_right = "]",
									string	format = "%g"	);

		public float	get (uint i, uint j);
		public void		set (uint i, uint j, float value);

		public VecFloat4	get_row (uint index);
		public void			set_row (uint index, VecFloat4 row);
		public VecFloat4	get_col (uint index);
		public void			set_col (uint index, VecFloat4 col);

		public float		tr { get; }
		public float		det { get; }
		public MatFloat4	cof { owned get; }
		public MatFloat4	adj { owned get; }

		public MatFloat4	neg ();
		public MatFloat4	transpose ();
		public MatFloat4	inverse ();

		public MatFloat4	muls (float b);
		public MatFloat4	divs (float b);
		public VecFloat4	mulv (VecFloat4 b);

		public MatFloat4	add (MatFloat4 b);
		public MatFloat4	sub (MatFloat4 b);

		public MatFloat4	mul (MatFloat4 b);

		public MatFloat4	mixs (MatFloat4 b, float c);
		public MatFloat4	mix (MatFloat4 b, MatFloat4 c);
	}

	[CCode (	copy_function="crank_mat_float_n_copy",
				destroy_function="crank_mat_float_n_fini",
				free_function="crank_mat_float_n_free"	)]
	public struct MatFloatN {
		public float*	data;
		public uint		rn;
		public uint		cn;

		public MatFloatN (uint rn, uint cn, ...);
		public MatFloatN.arr ([CCode (array_length_pos=0)]float[,] marr);
		public MatFloatN.arr_take ([CCode (array_length_pos=0)]owned float[,] marr);
		public MatFloatN.rv (uint rn, ...);
		public MatFloatN.rvarr ([CCode (array_length_pos=0)]VecFloat4[] rvarr);
		public MatFloatN.cv (uint cn, ...);
		public MatFloatN.cvarr ([CCode (array_length_pos=0)]VecFloat4[] cvarr);
		public MatFloatN.diag (uint n, ...);
		public MatFloatN.diag_arr ([CCode (array_length_pos=0)]float[] darr);
		public MatFloatN.fill (uint rn, uint cn, float fill);

		public MatFloatN	copy ();
		public MatFloatN?	dup ();

		public static uint	hash (	MatFloatN?	a);
		public static bool	equal (	MatFloatN?	a, MatFloatN?	b);

		[CCode (cname="crank_mat_float_n_to_string_full")]
		public string	to_string (	string	mat_left = "[",
									string	mat_in = ", ",
									string	mat_right = "]",
									string	row_left = "[",
									string	row_in = ", ",
									string	row_right = "]",
									string	format = "%g"	);
		
		public uint		row_size { get; }
		public uint		col_size { get; }

		public float	get (uint i, uint j);
		public void		set (uint i, uint j, float value);

		public VecFloatN	get_row (uint index);
		public void			set_row (uint index, VecFloatN row);
		public VecFloatN	get_col (uint index);
		public void			set_col (uint index, VecFloatN col);

		public float		tr { get; }
		public float		det { get; }
		public MatFloatN	cof { owned get; }
		public MatFloatN	adj { owned get; }

		public MatFloatN	neg ();
		public MatFloatN	transpose ();
		public MatFloatN	inverse ();

		public MatFloatN	muls (float b);
		public MatFloatN	divs (float b);
		public VecFloatN	mulv (VecFloatN b);

		public MatFloatN	add (MatFloatN b);
		public MatFloatN	sub (MatFloatN b);

		public MatFloatN	mul (MatFloatN b);

		public MatFloatN	mixs (MatFloatN b, float c);
		public MatFloatN	mix (MatFloatN b, MatFloatN c);
	}
}
