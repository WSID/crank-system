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

	//////// Function //////////////////////////////////////////////////////////

	public delegate void	Callback ();
	
	[CCode (simple_generics=true)]
	public delegate bool BoolPtrFunc<G> (	G	value	);
	
	[CCode (simple_generics=true)]
	public delegate string StrPtrFunc<G> (	G	value	);
	
	[CCode (simple_generics=true, has_target=false)]
	public delegate string EqualDeltaFunc<G> (	G		a,
												G		b,
												float	d	);
	
	public GLib.HashFunc<float?>	float_hash;
	public GLib.HashFunc<float?>	float_hash1;
	
	public GLib.EqualFunc<bool?>	bool_equal;
	public GLib.EqualFunc<uint?>	uint_equal;
	public GLib.EqualFunc<float?>	float_equal;
	
	public EqualDeltaFunc<float?>	float_equal_delta;
	
	public GLib.CompareFunc<uint?>		uint_compare;
	public GLib.CompareFunc<int?>		int_compare;
	public GLib.CompareFunc<float?>		float_compare;
	
	public StrPtrFunc<bool?>		bool_to_string;
	public StrPtrFunc<int?>			int_to_string;
	public StrPtrFunc<uint?>		uint_to_string;
	public StrPtrFunc<float?>		float_to_string;
	public StrPtrFunc<void*>		pointer_to_string;
	
	
	
	
	
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
	
	
	
	public struct RanUint {
		public RanUint		(uint	start, uint		end);
		public RanUint.diff (uint	start, uint		diff);
		public RanUint.unit (uint	start);
		
		public uint	length {get;}
	}
	
	public struct RanInt {
		public RanInt		(int	start, int		end);
		public RanInt.diff	(int	start, uint		diff);
		public RanInt.unit	(int	start);
		
		public uint	length {get;}
	}
	
	public struct RanFloat {
		public RanFloat			(float	start, float		end);
		public RanFloat.diff	(float	start, float		diff);
		public RanFloat.unit	(float	start);
		
		public float	length {get;}
	}
	
	public struct RanPtr {
		public RanPtr		(void*	start,	void*	end);
		public RanPtr.diff	(void*	start,	size_t	end);
		
		public size_t 	length {get;}
		public uint		count {get;}
	}
	
	public struct IterMemBool {
		public IterMemBool				(bool*	from,	bool*	to);
		public IterMemBool.with_count	(bool*	from,	uint	count);
		public IterMemBool.with_range	(RanPtr	range);
		
		[CCode (cname="crank_iter_mem_bool_init_with_count")]
		public IterMemBool.with_array	(bool[]	arr);
	}
	
	public struct IterMemUint {
		public IterMemUint				(uint*	from,	uint*	to);
		public IterMemUint.with_count	(uint*	from,	uint	count);
		public IterMemUint.with_range	(RanPtr	range);
		
		[CCode (cname="crank_iter_mem_uint_init_with_count")]
		public IterMemUint.with_array	(uint[]	arr);
	}
	
	public struct IterMemInt {
		public IterMemInt				(int*	from,	int*	to);
		public IterMemInt.with_count	(int*	from,	uint	count);
		public IterMemInt.with_range	(RanPtr	range);
		
		[CCode (cname="crank_iter_mem_int_init_with_count")]
		public IterMemInt.with_array	(int[]	arr);
	}
	
	public struct IterMemFloat {
		public IterMemFloat				(float*	from,	float*	to);
		public IterMemFloat.with_count	(float*	from,	uint	count);
		public IterMemFloat.with_range	(RanPtr	range);
		
		[CCode (cname="crank_iter_mem_float_init_with_count")]
		public IterMemFloat.with_array	(float[]	arr);
	}
	
	[CCode(simple_generics=true)]
	public struct IterMemPtr<G> {
		public IterMemPtr				(void**	from,	void**	to);
		public IterMemPtr.with_count	(void**	from,	uint	count);
		public IterMemPtr.with_range	(RanPtr	range);
		
		[CCode (cname="crank_iter_mem_ptr_init_with_count")]
		public IterMemPtr.with_array	(G[]	arr);
		
		public bool	is_valid ();
		public bool	next ();
		public unowned G	get ();
		public bool	foreach (BoolPtrFunc<G>	func);
	}
	
	[CCode(simple_generics=true)]
	public struct IterMemStruct<G> {
		public IterMemStruct			(void*	from,	void*	to,	size_t size);
		public IterMemStruct.with_count	(void*	from,	uint	count, size_t size);
		public IterMemStruct.with_range	(RanPtr	range,	size_t	size);
		
		[CCode (cname="crank_iter_mem_struct_init_with_count")]
		public IterMemStruct.with_array	(void*[]	arr);

		public bool is_valid ();
		public bool next ();
		public unowned G	get ();
		public bool foreach (BoolPtrFunc<G> func);
	}
	
	
	public struct CplxFloat {
	
		public CplxFloat		(float	real=0.0f,	float	imag=0.0f);
		public CplxFloat.arr	([CCode (array_length=false)]float	parts[2]);
		public CplxFloat.valist	(va_list	varargs);
		public CplxFloat.fill	(float		fill);
	
		public float arg { get; }
		public float norm { get; }
		public float norm_sq { get; }
	}
	
	public struct QuatFloat {
	
		public QuatFloat				(float	w=0.0f,	float	x=0.0f,
										 float	y=0.0f,	float	z=0.0f);
		
		public QuatFloat.cplx			(CplxFloat	wx,	CplxFloat	yz);
		
		public QuatFloat.arr			([CCode (array_length=false)]float	parts[4]);
		public QuatFloat.valist			(va_list	varargs);
		public QuatFloat.valist_cplx	(va_list	varargs);
		public QuatFloat.fill			(float		fill);

		public QuatFloat.rot			(float		angle,
										 VecFloat3	axis	);
		public QuatFloat.rotimm			(float		angle,
										 float		x,
										 float		y,
										 float		z	);
	
		public CplxFloat	wx { get; }
		public CplxFloat	yz { get; }
		public VecFloat3	imag { get; }
		public float 		norm { get; }
		public float 		norm_sq { get; }
		public float		rangle { get; }
		public VecFloat3	raxis { get; }
	}
	
	[CCode (copy_function="crank_permutation_copy",
			destroy_function="crank_permutation_fini",
			free_function="crank_permutation_free")]
	public struct Permutation {
	
		public Permutation		(uint n,	...);
		public Permutation.valist (uint n, va_list	varargs);
		public Permutation.arr 	([CCode (array_length_pos=0)]uint[] arr);
		public Permutation.arr_take([CCode (array_length_pos=0)]owned uint[] arr);
		public Permutation.identity(uint n);
		
		public Permutation.compare_array_int (	[CCode (array_length_pos=0)]
												int[]				arr,
												GLib.CompareFunc<int?>?	cmp	);
												
		public Permutation.compare_array_uint (	[CCode (array_length_pos=0)]
												uint[]				arr,
												GLib.CompareFunc<uint?>?	cmp	);
												
		public Permutation.compare_array_float ([CCode (array_length_pos=0)]
												float[]				arr,
												GLib.CompareFunc<float?>?	cmp	);
		
		public Permutation.compare_array_int_data (		[CCode (array_length_pos=0)]
														int[]				arr,
														GLib.CompareDataFunc<int?>?	cmp	);
												
		public Permutation.compare_array_uint_data (	[CCode (array_length_pos=0)]
														uint[]				arr,
														GLib.CompareDataFunc<uint?>?	cmp	);
												
		public Permutation.compare_array_float_data (	[CCode (array_length_pos=0)]
														float[]				arr,
														GLib.CompareDataFunc<float?>?	cmp	);
		
		[CCode (cname="crank_permutation_init_vala_compare_sarray", simple_generics=true)]
		public static Permutation compare_sarray<G> (	uint 				n,
														size_t				gsz,
														void*				garr,
														GLib.CompareFunc<G>	gcmp);
												
		[CCode (cname="crank_permutation_init_vala_compare_sarray_data", simple_generics=true)]
		public static Permutation compare_sarray_data<G> (	uint 					n,
															size_t					gsz,
															void*					garr,
															GLib.CompareDataFunc<G>	gcmp);

		[CCode (cname="crank_permutation_init_vala_compare_parray", simple_generics=true)]
		public static Permutation compare_parray<G> (	[CCode (array_length_pos=0)]
														G[]						garr,
														GLib.CompareFunc<G>		gcmp	);

		[CCode (cname="crank_permutation_init_vala_compare_parray_data", simple_generics=true)]
		public static Permutation compare_parray_data<G> (	[CCode (array_length_pos=0)]
															G[]						garr,
															GLib.CompareDataFunc<G>	gcmp	);
		
		public uint size { get; }
		public uint inversion { get; }
		public int sign { get; }
		public uint[] ascents { get; }
		public uint[] descents { get; }
		public uint[] excedances { get; }
		
		[CCode (simple_generics=true, cname="crank_permutation_vala_shuffle_parray")]
		public (unowned G)[] shuffle_parray <G> ([CCode (array_length=false)]G[] arr);
	}
	
	

	[CCode (copy_function="crank_vec_bool2_copy")]
	public struct VecBool2 {
	
		public VecBool2			(bool x=false, bool y=false);
		public VecBool2.arr		([CCode (array_length=false)]bool	arr[2]);
		public VecBool2.valist	(va_list	varargs);
		public VecBool2.fill	(bool		fill=false);
		
		public bool			any { get; }
		public bool			all { get; }
		public uint			count { get; }
		public float		ratio { get; }
	}
	
	[CCode (copy_function="crank_vec_bool3_copy")]
	public struct VecBool3 {
	
		public VecBool3			(bool x=false, bool y=false, bool z=false);
		public VecBool3.arr		([CCode (array_length=false)]bool	arr[3]);
		public VecBool3.valist	(va_list	varargs);
		public VecBool3.fill	(bool		fill=false);
	
		public bool			any { get; }
		public bool			all { get; }
		public uint			count { get; }
		public float		ratio { get; }
		
	}
	
	[CCode (copy_function="crank_vec_bool4_copy")]
	public struct VecBool4 {
	
		public VecBool4			(bool x=false, bool y=false, bool z=false, bool w=false);
		public VecBool4.arr		([CCode (array_length=false)]bool	arr[4]);
		public VecBool4.valist	(va_list	varargs);
		public VecBool4.fill	(bool		fill=false);
		
		public bool			any { get; }
		public bool			all { get; }
		public uint			count { get; }
		public float		ratio { get; }

	}
	
	[CCode (	copy_function="crank_vec_bool_n_copy",
				destroy_function="crank_vec_bool_n_fini",
				free_function="crank)vec_bool_n_free"	)]
	public struct VecBoolN {
	
		public VecBoolN			(uint n, ...);
		public VecBoolN.arr		([CCode (array_length_pos=0)]bool[] arr);
		public VecBoolN.valist	(uint n, va_list	varargs);
		public VecBoolN.fill	(uint n, bool fill=false);
		
		public uint			size {	get; }
		
		public bool			any { get; }
		public bool			all { get; }
		public uint			count { get; }
		public float		ratio { get; }
	}
	
	
	[CCode (copy_function="crank_vec_int2_copy")]
	public struct VecInt2 {
	
		public VecInt2			(int x=0, int y=0);
		public VecInt2.arr		([CCode (array_length=false)]int	arr[2]);
		public VecInt2.valist	(va_list	varargs);
		public VecInt2.fill		(int		fill=0);
		
		public VecInt2.from_vb	(VecBool2	vb);
	
		public uint			magn_sq {get;}
		public float		magn {get;}
		
	}
	
	[CCode (copy_function="crank_vec_int3_copy")]
	public struct VecInt3 {
	
		public VecInt3			(int x=0, int y=0, int z=0);
		public VecInt3.arr		([CCode (array_length=false)]int	arr[3]);
		public VecInt3.valist	(va_list	varargs);
		public VecInt3.fill		(int		fill=0);
		
		public VecInt3.from_vb	(VecBool3	vb);
	
		public uint			magn_sq {get;}
		public float		magn {get;}
		
	}
	
	[CCode (copy_function="crank_vec_int4_copy")]
	public struct VecInt4 {
	
		public VecInt4			(int x=0, int y=0, int z=0, int w=0);
		public VecInt4.arr		([CCode (array_length=false)]int	arr[4]);
		public VecInt4.valist	(va_list	varargs);
		public VecInt4.fill		(int		fill=0);
		
		public VecInt4.from_vb	(VecBool4	vb);
	
		public uint			magn_sq {get;}
		public float		magn {get;}
	}
	
	
	[CCode (	copy_function="crank_vec_int_n_copy",
				destroy_function="crank_vec_int_n_fini",
				free_function="crank_vec_int_n_free"	)]
	public struct VecIntN {
	
		public VecIntN			(uint n, ...);
		public VecIntN.arr		([CCode (array_length_pos=0)]int[]	arr);
		public VecIntN.valist	(uint n, va_list	varargs);
		public VecIntN.fill		(uint n, int		fill=0);
		
		public VecIntN.from_vb	(VecBoolN	vb);
		
		public uint			size { get; }
		public uint			magn_sq {get;}
		public float		magn {get;}
	}
	
	[CCode (copy_function="crank_vec_float2_copy")]
	public struct VecFloat2 {
	
		public VecFloat2			(float x=0, float y=0);
		public VecFloat2.arr		([CCode (array_length=false)]float	arr[2]);
		public VecFloat2.valist		(va_list	varargs);
		public VecFloat2.fill		(float		fill=0);
		
		public VecFloat2.from_vb	(VecBool2	vb);
		public VecFloat2.from_vi	(VecInt2	vi);
		
		public float		magn_sq {get;}
		public float		magn {get;}
	}
	

	[CCode (copy_function="crank_vec_float3_copy")]
	public struct VecFloat3 {
	
		public VecFloat3			(float x=0, float y=0, float z=0);
		public VecFloat3.arr		([CCode (array_length=false)]float	arr[3]);
		public VecFloat3.valist		(va_list	varargs);
		public VecFloat3.fill		(float		fill=0);
		
		public VecFloat3.from_vb	(VecBool3	vb);
		public VecFloat3.from_vi	(VecInt3	vi);
		
		public float		magn_sq {get;}
		public float		magn {get;}
	}
	
	[CCode (copy_function="crank_vec_float4_copy")]
	public struct VecFloat4 {
	
		public VecFloat4			(float x=0, float y=0, float z=0, float w=0);
		public VecFloat4.arr		([CCode (array_length=false)]float	arr[4]);
		public VecFloat4.valist		(va_list	varargs);
		public VecFloat4.fill		(float		fill=0);
		
		public VecFloat4.from_vb	(VecBool4	vb);
		public VecFloat4.from_vi	(VecInt4	vi);
		
		public float		magn_sq {get;}
		public float		magn {get;}
	}
	
	
	[CCode (	copy_function="crank_vec_float_n_copy",
				destroy_function="crank_vec_float_n_fini",
				free_function="crank_vec_float_n_free"	)]
	public struct VecFloatN {
	
		public VecFloatN			(uint n, ...);
		public VecFloatN.arr		([CCode (array_length_pos=0)]float[]	arr);
		public VecFloatN.arr_take	([CCode (array_length_pos=0)]owned float[]	arr);
		public VecFloatN.valist		(uint n, va_list	varargs);
		public VecFloatN.fill		(uint n, float		fill);
		
		public VecFloatN.from_vb	(VecBoolN	vb);
		public VecFloatN.from_vi	(VecIntN	vi);
		
		public uint			size {get; }
		public float		magn_sq {get;}
		public float		magn {get;}
	}

	
	[CCode (copy_function="crank_vec_cplx_float_n_copy",
			destroy_function="crank_vec_cplx_float_n_fini",
			free_function="crank_vec_cplx_float_n_free")]
	public struct VecCplxFloatN {
	
		public VecCplxFloatN			(uint n, ...);
		public VecCplxFloatN.arr		([CCode (array_length_pos=0)]CplxFloat	arr);
		public VecCplxFloatN.arr_take	([CCode (array_length_pos=0)]owned CplxFloat	arr);
		public VecCplxFloatN.valist		(uint n, va_list	varargs);
		public VecCplxFloatN.fill		(uint n, CplxFloat	fill);
		
		public VecCplxFloatN.imm		(uint n, ...);
		public VecCplxFloatN.valist_imm	(uint n, ...);
		public VecCplxFloatN.fill_imm	(uint n, float real=0.0f, float imag=0.0f);

		public VecCplxFloatN.from_vb	(VecBoolN	vb);
		public VecCplxFloatN.from_vi	(VecIntN	vi);
		
		public uint			size { get; }
		public float		magn_sq {get;}
		public float		magn {get;}

		public VecFloatN	real {get; set;}
		public VecFloatN	imag {get; set;}
		
		public IterMemStruct<CplxFloat?>	iterator ();
	}
	

	public struct MatFloat2 {
		public MatFloat2 (float m00, float m01, float m10, float m11);
		public MatFloat2.arr (float marr[4]);
		public MatFloat2.rv (VecFloat2 rv0, VecFloat2 rv1);
		public MatFloat2.rvarr (VecFloat2 rvarr[2]);
		public MatFloat2.rvparr (VecFloat2? rvparr[2]);
		public MatFloat2.cv (VecFloat2 cv0, VecFloat2 cv1);
		public MatFloat2.cvarr (VecFloat2 cvarr[2]);
		public MatFloat2.cvparr (VecFloat2? cvparr[2]);
		public MatFloat2.diag (float m00, float m11);
		public MatFloat2.diag_arr (float darr[2]);
		public MatFloat2.fill (float fill);

		public float		tr { get; }
		public float		det { get; }
		public MatFloat2	cof { owned get; }
		public MatFloat2	adj { owned get; }
	}

	public struct MatFloat3 {

		public MatFloat3 (	float m00, float m01, float m02,
							float m10, float m11, float m12,
							float m20, float m21, float m22);
		public MatFloat3.arr (float marr[9]);
		public MatFloat3.rv (VecFloat3 rv0, VecFloat3 rv1, VecFloat3 rv2);
		public MatFloat3.rvarr (VecFloat3 rvarr[3]);
		public MatFloat3.rvparr (VecFloat3? rvparr[3]);
		public MatFloat3.cv (VecFloat3 cv0, VecFloat3 cv1, VecFloat3 cv2);
		public MatFloat3.cvarr (VecFloat3 cvarr[3]);
		public MatFloat3.cvparr (VecFloat3? cvparr[3]);
		public MatFloat3.diag (float m00, float m11, float m22);
		public MatFloat3.diag_arr (float darr[3]);
		public MatFloat3.fill (float fill);

		public float		tr { get; }
		public float		det { get; }
		public MatFloat3	cof { owned get; }
		public MatFloat3	adj { owned get; }
	}

	public struct MatFloat4 {

		public MatFloat4 (	float m00, float m01, float m02, float m03,
							float m10, float m11, float m12, float m13,
							float m20, float m21, float m22, float m23,
							float m30, float m31, float m32, float m33	);
		public MatFloat4.arr (float marr[16]);
		public MatFloat4.rv (VecFloat4 rv0, VecFloat4 rv1, VecFloat4 rv2, VecFloat4 rv3);
		public MatFloat4.rvarr (VecFloat4 rvarr[4]);
		public MatFloat4.rvparr (VecFloat4? rvparr[4]);
		public MatFloat4.cv (VecFloat4 cv0, VecFloat4 cv1, VecFloat4 cv2, VecFloat4 cv3);
		public MatFloat4.cvarr (VecFloat4 cvarr[4]);
		public MatFloat4.cvparr (VecFloat4? cvparr[4]);
		public MatFloat4.diag (float m00, float m11, float m22, float m33);
		public MatFloat4.diag_arr (float darr[4]);
		public MatFloat4.fill (float fill);

		public float		tr { get; }
		public float		det { get; }
		public MatFloat4	cof { owned get; }
		public MatFloat4	adj { owned get; }
	}

	[CCode (	copy_function="crank_mat_float_n_copy",
				destroy_function="crank_mat_float_n_fini",
				free_function="crank_mat_float_n_free"	)]
	public struct MatFloatN {

		public MatFloatN (uint rn, uint cn, ...);
		public MatFloatN.arr ([CCode (array_length_pos=0)]float[,] marr);
		public MatFloatN.arr_take ([CCode (array_length_pos=0)]owned float[,] marr);
		public MatFloatN.rv (uint rn, ...);
		public MatFloatN.rvarr ([CCode (array_length_pos=0)]VecFloat4[] rvarr);
		public MatFloatN.rvparr ([CCode (array_length_pos=0)]VecFloat4?[] rvparr);
		public MatFloatN.cv (uint cn, ...);
		public MatFloatN.cvarr ([CCode (array_length_pos=0)]VecFloat4[] cvarr);
		public MatFloatN.cvparr ([CCode (array_length_pos=0)]VecFloat4?[] cvparr);
		public MatFloatN.diag (uint n, ...);
		public MatFloatN.diag_arr ([CCode (array_length_pos=0)]float[] darr);
		public MatFloatN.fill (uint rn, uint cn, float fill);

		public float		tr { get; }
		public float		det { get; }
		public MatFloatN	cof { owned get; }
		public MatFloatN	adj { owned get; }
		public VecFloatN	diagv {
			[CCode(cname="crank_mat_float_n_get_diag")]owned get; }
		
		public uint			row_size { get; }
		public uint			col_size { get; }
	}
	

	[CCode (	copy_function="crank_mat_float_n_copy",
				destroy_function="crank_mat_float_n_fini",
				free_function="crank_mat_float_n_free"	)]
	public struct MatCplxFloatN {

		public MatCplxFloatN (uint rn, uint cn, ...);
		public MatCplxFloatN.arr ([CCode (array_length_pos=0)]CplxFloat[,] marr);
		public MatCplxFloatN.arr_take ([CCode (array_length_pos=0)]owned CplxFloat[,] marr);
		public MatCplxFloatN.rv (uint rn, ...);
		public MatCplxFloatN.rvarr ([CCode (array_length_pos=0)]VecCplxFloatN[] rvarr);
		public MatCplxFloatN.rvparr ([CCode (array_length_pos=0)]VecCplxFloatN?[] rvparr);
		public MatCplxFloatN.cv (uint cn, ...);
		public MatCplxFloatN.cvarr ([CCode (array_length_pos=0)]VecCplxFloatN[] cvarr);
		public MatCplxFloatN.cvparr ([CCode (array_length_pos=0)]VecCplxFloatN?[] cvparr);
		public MatCplxFloatN.diag (uint n, ...);
		public MatCplxFloatN.diag_arr ([CCode (array_length_pos=0)]CplxFloat[] darr);
		public MatCplxFloatN.fill (uint rn, uint cn, CplxFloat fill);

		public CplxFloat		tr { owned get; }
		public CplxFloat		det { owned get; }
		public MatCplxFloatN	cof { owned get; }
		public MatCplxFloatN	adj { owned get; }
		public VecCplxFloatN	diagv {
			[CCode(cname="crank_mat_cplx_float_n_get_diag")]owned get; }
		
		public uint			row_size { get; }
		public uint			col_size { get; }
	}
	
	
	
	
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
	
	namespace Test {
		#if GLIB_2_26
		public void	add_func_expected_fail (	string			path,
												GLib.TestFunc	func	);
		#else
		public void	add_func_expected_fail (	string			path,
												GLib.Callback	func	);
		#endif
	}

	public void	assert_eqarray_bool (		bool[]	a,
											bool[]	b	);
	
	[CCode (sentinel="")]
	public void	assert_eqarray_bool_imm (	bool[]	a,
											...	);

	public void	assert_eqarray_int (		int[]	a,
											int[]	b	);
	
	[CCode (sentinel="")]
	public void	assert_eqarray_int_imm (	int[]	a,
											...	);

	public void	assert_eqarray_uint (		uint[]	a,
											uint[]	b	);
	
	[CCode (sentinel="")]
	public void	assert_eqarray_uint_imm (	uint[]	a,
											...	);

	public void	assert_eqarray_float (		float[]	a,
											float[]	b	);
	
	[CCode (sentinel="")]
	public void	assert_eqarray_float_imm (	float[]	a,
											...	);

	[CCode (simple_generics=true)]
	public void	assert_eqarray_pointer <G> (G[]		a,
											G[]		b	);

	[CCode (simple_generics=true, sentinel="")]
	public void	assert_eqarray_pointer_imm <G>	(	G[]	a,
												 	... );

	[CCode (simple_generics=true, sentinel="")]
	public void	assert_eq_glist_imm <G> (	GLib.List<G>	a,
											...	);

	[CCode (simple_generics=true, sentinel="")]
	public void	assert_eq_gptrarray_imm <G> (	GLib.GenericArray<G>	a,
												... );

	[CCode (sentinel="")]
	public void assert_eq_permutation_imm (	Permutation	a,	...);
	

	public void assert_eq_vecbool2_imm	( 	VecBool2 a,	bool x, bool y);
	public void assert_eq_vecbool3_imm	( 	VecBool3 a,	bool x, bool y, bool z);
	public void assert_eq_vecbool4_imm	( 	VecBool4 a,	bool x, bool y, bool z, bool w);
	
	[CCode (sentinel="")]
	public void assert_eq_vecbool_n_imm (	VecBoolN a,	...);
	

	public void assert_eq_vecint2_imm	( 	VecInt2 a,	int x, int y);
	public void assert_eq_vecint3_imm	( 	VecInt3 a,	int x, int y, int z);
	public void assert_eq_vecint4_imm	( 	VecInt4 a,	int x, int y, int z, int w);
	
	[CCode (sentinel="")]
	public void assert_eq_vecint_n_imm (	VecIntN a,	...);
	

	public void assert_eq_vecfloat2_imm	( 	VecFloat2 a,	float x, float y);
	public void assert_eq_vecfloat3_imm	( 	VecFloat3 a,	float x, float y, float z);
	public void assert_eq_vecfloat4_imm	( 	VecFloat4 a,	float x, float y, float z, float w);
	
	[CCode (sentinel="")]
	public void assert_eq_vecfloat_n_imm (	VecFloatN a,	...);
											

	public void	assert_lefloat(	float a, float b, float d = 0.0001f	);
	public void	assert_eqfloat(	float a, float b, float d = 0.0001f	);
	public void	assert_gefloat(	float a, float b, float d = 0.0001f	);

	[CCode (cname="crank_assert_eqcplxfloat_d")]
	public void	assert_eqcplxfloat (CplxFloat a, CplxFloat b, float d = 0.0001f);

	[CCode (cname="crank_assert_eqcplxfloat_d_cimm")]
	public void assert_eqcplxfloat_cimm (CplxFloat a, float r, float i, float d = 0.0001f);
}
