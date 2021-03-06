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
	
	
	namespace Bench {
		[CCode (free_function="crank_bench_param_node_free")]
		public class ParamNode {
			public ParamNode ();

			public GLib.GenericArray<Crank.Bench.ParamNode>	children {get;}
			public Crank.Bench.ParamNode			parent {get;}
			public GLib.HashTable<GLib.Quark, GLib.Value?> 	table {get; set;}
		}

		[CCode (free_function="crank_bench_suite_free")]
		public class Suite {
			public Suite 	(string			name,
					 Crank.Bench.ParamNode?	param = null);

			public string			name {get; set;}
			public Crank.Bench.ParamNode?	param {get; set;}

			public string			path {owned get;}
			public Crank.Bench.Suite     	parent {get;}

			public GLib.GenericArray<Crank.Bench.Suite>  suites {get;}
			public GLib.GenericArray<Crank.Bench.Case>	cases {get;}
		}
	
		[CCode (free_function="crank_bench_case_free")]
		public class Case {
			public Case 	(string			name,
					 Crank.Bench.ParamNode?	param,
					 owned Crank.Bench.Func func);

			public string			name {get; set;}
			public Crank.Bench.ParamNode?	param {get; set;}

			public string			path {owned get;}
			public Crank.Bench.Suite     	parent {get;}
		}

		[CCode (free_function="crank_bench_run_free")]
		public class Run {
			public Run (Crank.Bench.Case bcase,
				    GLib.HashTable<GLib.Quark, GLib.Value?> param,
				    uint run_no);

			public GLib.HashTable<GLib.Quark, GLib.Value?> @params {get;}
			public GLib.HashTable<GLib.Quark, GLib.Value?> results {get;}
			public uint run_no {get;}
			public bool running {[CCode(name="is_running")]get;}
			public bool processed {[CCode(name="is_processed")]get;}
			public bool failed {[CCode(name="is_failed")]get;}
			public bool skipped {[CCode(name="is_skipped")]get;}
			public Crank.Bench.RunState state {get;}
			public Crank.Bench.RunMark mark {get;}
			public string? message {get;}
		}

		[CCode (free_function="crank_bench_result_suite_free")]
		public class ResultSuite {
			public ResultSuite (Crank.Bench.Suite suite);

			public Crank.Bench.Suite	suite {get;}
			public Crank.Bench.ResultSuite  parent {get;}

			public GLib.GenericArray<Crank.Bench.ResultSuite>	sresults {get;}
			public GLib.GenericArray<Crank.Bench.ResultCase>	cresults {get;}

			public GLib.List<Crank.Bench.ResultCase>		cresults_flat {owned get;}
			public GLib.List<Crank.Bench.Run>			runs {owned get;}
			public GLib.List<Crank.Bench.Run>			runs_flat {owned get;}
		}


		[CCode (free_function="crank_bench_result_case_free")]
		public class ResultCase {
			public ResultCase (Crank.Bench.Case bcase);

			public Crank.Bench.Case		bcase {[CCode (name="crank_bench_result_get_case")]get;}
			public Crank.Bench.Suite	parent {get;}

			public GLib.GenericArray<Crank.Bench.Run>	runs {get;}
			public GLib.List<Crank.Bench.Run>		run_list {owned get;}
		}

		[CCode (cprefix="CRANK_BENCH_RUN_")]
		public enum RunState {
			NOT_RUN,
			RUNNING,
			FINISHED,
			PROCESSED
		}

		[CCode (cprefix="CRANK_BENCH_RUN_")]
		public enum RunMark {
			SUCCESS,
			FAIL,
			SKIP
		}
	}





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
	
	
	public struct PairUint {
		public PairUint (uint a = 0,
		                 uint b = 0);
		public PairUint.array ([CCode (array_length=false)]
		                       uint array[2]);
	}

	[CCode (simple_generics=true)]
	public struct PairPointer <A, B> {
		public unowned A a;
		public unowned B b;

		public PairPointer (A a = null,
		                    B b = null);
		public PairPointer.array (void*[] array);

		public PairPointer<A, B> copy ();
		public PairPointer<A, B>? dup ();
		public PairPointer<B, A> swap ();
		public void swap_self ();

		public void @foreach (GLib.Func<void*> func);
	}
	
	public struct CplxFloat {
	
		public CplxFloat		(float	real=0.0f,	float	imag=0.0f);
		public CplxFloat.arr	([CCode (array_length=false)]float	parts[2]);
		public CplxFloat.valist	(va_list	varargs);
		public CplxFloat.fill	(float		fill);
		public CplxFloat.polar	(float		norm,	float		arg);
	
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
		public QuatFloat.urot			(float		angle,
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
		
		public Permutation.compare_sarray (			uint 				n,
													size_t				gsz,
													void*				garr,
													GLib.CompareFunc	gcmp	);
												
		public Permutation.compare_sarray_data (	uint 					n,
													size_t					gsz,
													void*					garr,
													GLib.CompareDataFunc	gcmp);

		[CCode (cname="crank_permutation__vala_init_compare_parray", simple_generics=true)]
		public static Permutation compare_parray<G> (	[CCode (array_length_pos=0)]
														G[]						garr,
														GLib.CompareFunc<G>		gcmp	);

		[CCode (cname="crank_permutation__vala_init_compare_parray_data", simple_generics=true)]
		public static Permutation compare_parray_data<G> (	[CCode (array_length_pos=0)]
															G[]						garr,
															GLib.CompareDataFunc<G>	gcmp	);
		
		public uint size { get; }
		public uint inversion { get; }
		public int sign { get; }
		public uint[] ascents { get; }
		public uint[] descents { get; }
		public uint[] excedances { get; }
		
		[CCode (simple_generics=true, cname="crank_permutation__vala_shuffle_parray")]
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
		
		public VecCplxFloatN.uc			(uint n, ...);
		public VecCplxFloatN.valistuc	(uint n, ...);
		public VecCplxFloatN.ucarr		([CCode (array_length_pos=0)]float[] real,
										 [CCode (array_length_pos=0)]float[] imag);
										 
		public VecCplxFloatN.arruc		(uint n, [CCode (array_length=false)]float[] arr);
		public VecCplxFloatN.fill_uc	(uint n, float real=0.0f, float imag=0.0f);
		public VecCplxFloatN.ucv		(VecFloatN	real, VecFloatN	imag);

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
		public MatFloat2.row (VecFloat2 row0, VecFloat2 row1);
		public MatFloat2.row_arr (VecFloat2 row_arr[2]);
		public MatFloat2.row_parr (VecFloat2? row_parr[]);
		public MatFloat2.col (VecFloat2 col0, VecFloat2 col1);
		public MatFloat2.col_arr (VecFloat2 col_arr[2]);
		public MatFloat2.col_parr (VecFloat2? col_parr[]);
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
		public MatFloat3.row (VecFloat3 row0, VecFloat3 row1, VecFloat3 row2);
		public MatFloat3.row_arr (VecFloat3 row_arr[3]);
		public MatFloat3.row_parr (VecFloat3? row_parr[]);
		public MatFloat3.col (VecFloat3 col0, VecFloat3 col1, VecFloat3 col2);
		public MatFloat3.col_arr (VecFloat3 col_arr[3]);
		public MatFloat3.col_parr (VecFloat3? col_parr[]);
		public MatFloat3.diag (float m00, float m11, float m22);
		public MatFloat3.diag_arr (float darr[3]);
		public MatFloat3.fill (float fill);
		public MatFloat3.rot (float angle, Crank.VecFloat3 axis);
		public MatFloat3.urot (float angle, float axis_x, float axis_y, float axis_z);

		public float		tr { get; }
		public float		det { get; }
		public MatFloat3	cof { owned get; }
		public MatFloat3	adj { owned get; }
		public float		rangle { get; }
		public VecFloat3    raxis { owned get; }
	}

	public struct MatFloat4 {

		public MatFloat4 (	float m00, float m01, float m02, float m03,
							float m10, float m11, float m12, float m13,
							float m20, float m21, float m22, float m23,
							float m30, float m31, float m32, float m33	);
		public MatFloat4.arr (float marr[16]);
		public MatFloat4.row (VecFloat4 row0, VecFloat4 row1, VecFloat4 row2, VecFloat4 row3);
		public MatFloat4.row_arr (VecFloat4 row_arr[4]);
		public MatFloat4.row_parr (VecFloat4? row_parr[]);
		public MatFloat4.col (VecFloat4 col0, VecFloat4 col1, VecFloat4 col2, VecFloat4 col3);
		public MatFloat4.col_arr (VecFloat4 col_arr[4]);
		public MatFloat4.col_parr (VecFloat4? col_parr[]);
		public MatFloat4.diag (float m00, float m11, float m22, float m33);
		public MatFloat4.diag_arr (float darr[4]);
		public MatFloat4.fill (float fill);
		public MatFloat4.rot (float angle, Crank.VecFloat3 axis);
		public MatFloat4.urot (float angle, float axis_x, float axis_y, float axis_z);

		public float		tr { get; }
		public float		det { get; }
		public MatFloat4	cof { owned get; }
		public MatFloat4	adj { owned get; }
		public float		rangle { get; }
		public VecFloat3    raxis { owned get; }
	}

	[CCode (	copy_function="crank_mat_float_n_copy",
				destroy_function="crank_mat_float_n_fini",
				free_function="crank_mat_float_n_free"	)]
	public struct MatFloatN {

		public MatFloatN (uint rn, uint cn, ...);
		public MatFloatN.arr ([CCode (array_length_pos=0)]float[,] marr);
		public MatFloatN.arr_take ([CCode (array_length_pos=0)]owned float[,] marr);
		public MatFloatN.row (uint rn, ...);
		public MatFloatN.row_arr ([CCode (array_length_pos=0)]VecFloat4[] row_arr);
		public MatFloatN.row_parr ([CCode (array_length_pos=0)]VecFloat4?[] row_parr);
		public MatFloatN.col (uint cn, ...);
		public MatFloatN.col_arr ([CCode (array_length_pos=0)]VecFloat4[] col_arr);
		public MatFloatN.col_parr ([CCode (array_length_pos=0)]VecFloat4?[] col_parr);
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
	

	[CCode (	copy_function="crank_mat_cplx_float_n_copy",
				destroy_function="crank_mat_cplx_float_n_fini",
				free_function="crank_mat_cplx_float_n_free"	)]
	public struct MatCplxFloatN {

		public MatCplxFloatN (uint rn, uint cn, ...);
		public MatCplxFloatN.arr ([CCode (array_length_pos=0)]CplxFloat[,] marr);
		public MatCplxFloatN.arr_take ([CCode (array_length_pos=0)]owned CplxFloat[,] marr);
		public MatCplxFloatN.row (uint rn, ...);
		public MatCplxFloatN.row_arr ([CCode (array_length_pos=0)]VecCplxFloatN[] row_arr);
		public MatCplxFloatN.row_parr ([CCode (array_length_pos=0)]VecCplxFloatN?[] row_parr);
		public MatCplxFloatN.col (uint cn, ...);
		public MatCplxFloatN.col_arr ([CCode (array_length_pos=0)]VecCplxFloatN[] col_arr);
		public MatCplxFloatN.col_parr ([CCode (array_length_pos=0)]VecCplxFloatN?[] col_parr);
		public MatCplxFloatN.diag (uint n, ...);
		public MatCplxFloatN.diag_arr ([CCode (array_length_pos=0)]CplxFloat[] darr);
		public MatCplxFloatN.fill (uint rn, uint cn, CplxFloat fill);
		
		public MatCplxFloatN.uc (uint rn, uint cn, ...);
		public MatCplxFloatN.arruc (uint rn, uint cn, [CCode (array_length=false)]float[] mucarr);
		public MatCplxFloatN.ucarr ([CCode (array_length_pos=0)]float[,] real, [CCode (array_length_pos=0)]float[,] imag);
		public MatCplxFloatN.ucm (MatFloatN real, MatFloatN imag);
		public MatCplxFloatN.row_uc (uint rn, ...);
		public MatCplxFloatN.row_arruc (uint rn, [CCode (array_length=false)]VecFloatN[] row_arruc);
		public MatCplxFloatN.row_parruc (uint rn, [CCode (array_length=false)]VecFloatN?[] row_parruc);
		public MatCplxFloatN.col_uc (uint cn, ...);
		public MatCplxFloatN.col_arruc (uint cn, [CCode (array_length=false)]VecFloatN[] col_arruc);
		public MatCplxFloatN.col_parruc (uint cn, [CCode (array_length=false)]VecFloatN?[] col_parruc);
		public MatCplxFloatN.diag_uc (uint n, ...);
		public MatCplxFloatN.diag_arruc (uint n, [CCode (array_length=false)]float[] arruc);
		public MatCplxFloatN.diag_ucarr ([CCode (array_length_pos=0)]float[] real, [CCode (array_length_pos=0)]float[] imag);
		public MatCplxFloatN.diag_ucv (VecFloatN real, VecFloatN imag);
		public MatCplxFloatN.fill_uc (uint rn, uint cn, float real, float imag);
		
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

	[CCode (cname="crank_assert_eqcplxfloat_d_uc")]
	public void assert_eqcplxfloat_uc (CplxFloat a, float r, float i, float d = 0.0001f);
}
