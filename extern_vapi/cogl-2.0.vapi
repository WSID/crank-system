/* This vapi was written by hand, by referencing to Reference manual and header files.
 * 
 * This might have deprecated functions and not have newly added functions.
 */

[CCode (cheader_filename="cogl/cogl2-experimental.h")]
namespace Cogl{





	public struct UserDataKey {
		public int unused;
	}

	[CCode (type_id="cogl_object_get_gtype ()",
		ref_function="cogl_object_ref",
		unref_function="cogl_object_unref",
		set_value_function="cogl_object_value_set_object",
		get_value_function="cogl_object_value_get_object")]
	public class Object {
		[CCode(simple_generics=true)]
		public unowned T get_user_data <T> (UserDataKey* key);

		[CCode(simple_generics=true)]
		public void set_user_data <T> (UserDataKey* key, owned T user_data);
	}
	
	public delegate void DebugObjectForeachTypeCallback (DebugObjectTypeInfo info);
	
	public struct DebugObjectTypeInfo {
		public string name;
		public ulong instance_count;
	}
	
	/* COGL_ENABLE_EXPERIMENTAL_API */
	public void debug_object_foreach_type (DebugObjectForeachTypeCallback func);
	
	public void debug_object_print_instances ();
	
	
	
	

	[CCode (has_type_id=false)]
	public struct VertexP2 {
		public float x;
		public float y;
	}
	
	public struct VertexP3 {
		public float x;
		public float y;
		public float z;
	}

	public struct VertexP2C4 {
		public float x;
		public float y;
		public uint8 r;
		public uint8 g;
		public uint8 b;
		public uint8 a;
	}

	public struct VertexP3C4 {
		public float x;
		public float y;
		public float z;
		public uint8 r;
		public uint8 g;
		public uint8 b;
		public uint8 a;
	}

	public struct VertexP2T2 {
		public float x;
		public float y;
		public float s;
		public float t;
	}

	public struct VertexP3T2 {
		public float x;
		public float y;
		public float z;
		public float s;
		public float t;
	}

	public struct VertexP2T2C4 {
		public float x;
		public float y;
		public float s;
		public float t;
		public uint8 r;
		public uint8 g;
		public uint8 b;
		public uint8 a;
	}

	public struct VertexP3T2C4 {
		public float x;
		public float y;
		public float z;
		public float s;
		public float t;
		public uint8 r;
		public uint8 g;
		public uint8 b;
		public uint8 a;
	}

	public enum VerticesMode {
		POINTS,
		LINES,
		LINE_LOOP,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN
	}

	public enum PixelFormat {
		ANY,
		A_8,
		RGB_565,
		RGBA_4444,
		RGBA_5551,
		YUV,
		G_8,
		RG_88,
		RGB_888,
		BGR_888,
		RGBA_8888,
		BGRA_8888,
		ARGB_8888,
		ABGR_8888,
		RGBA_1010102,
		BGRA_1010102,
		ARGB_2101010,
		ABGR_2101010,
		RGBA_8888_PRE,
		BGRA_8888_PRE,
		ARGB_8888_PRE,
		ABGR_8888_PRE,
		RGBA_4444_PRE,
		RGBA_5551_PRE,
		RGBA_1010102_PRE,
		BGRA_1010102_PRE,
		ARGB_2101010_PRE,
		ABGR_2101010_PRE,

		DEPTH_16,
		DEPTH_32,
		DEPTH_24_STENCIL_8
	}

	[Flags]
	public enum BufferTarget {
		WINDOW_BUFFER,
		OFFSCREEN_BUFFER
	}

	[Flags]
	public enum BufferBit {
		COLOR,
		DEPTH,
		STENCIL
	}

	public enum AttributeType {
		BYTE,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		FLOAT
	}

	[Flags]
	public enum ColorMask {
		NONE,
		RED,
		GREEN,
		BLUE,
		ALPHA,
		ALL
	}

	[Flags]
	public enum TextureFlags {
		NONE,
		NO_AUTO_MIPMAP,
		NO_SLICING,
		NO_ATLAS
	}






	public enum WinsysID {
		ANY,
		STUB,
		GLX,
		EGL_XLIB,
		EGL_NULL,
		EGL_GDL,
		EGL_WAYLAND,
		EGL_KMS,
		EGL_ANDROID,
		WGL,
		SDL
	}
	
	public enum Driver {
		ANY,
		NOP,
		GL,
		GL3,
		GLES1,
		GLES2,
		WEBGL
	}

	[flags]
	public enum RendererConstraint {
		USES_X11,
		USES_XLIB,
		USES_EGL,
		SUPPORTS_COGL_GLES2
	}
	
	public delegate void OutputCallback (Output output);


	[CCode (type_id="cogl_renderer_get_gtype()",
			type_check_function="cogl_is_renderer")]
	public class Renderer: Object {
		public Renderer ();

		public int n_fragment_texture_units { get; }
		public WinsysID winsys_id { get; set; }
		public Driver driver { get; set; }

		public bool check_onscreen_template (OnscreenTemplate onscreen_template) throws GLib.Error;
		public bool connect () throws GLib.Error;
		
		public void add_constraint (RendererConstraint constraint);
		public void remove_constraint (RendererConstraint constraint);
		
		public void foreach_output (OutputCallback callback);
		
		
		[CCode (cname="cogl_poll_renderer_get_info")]
		int poll_get_info (out PollFD[] poll_fds, out int64 timeout);
		
		[CCode (cname="cogl_poll_renderer_dispatch")]
		void poll_dispatch (PollFD[] poll_fds);
		
		
		
	}
	
	[CCode (type_id="cogl_swap_chain_get_gtype()",
			type_check_function="cogl_is_swap_chain")]
	public class SwapChain: Object {
		public SwapChain ();
		
		public bool has_alpha { set; }
		public int length { set; }
	}

	/* CoglOnscreenTemplate */
	[CCode (type_check_function="cogl_is_onscreen_template")]
	public class OnscreenTemplate: Object {
		public OnscreenTemplate (SwapChain swap_chain);
		public bool has_alpha { set; }
		public bool swap_throttled { set; }
		public int samples_per_pixel { set; }
		public bool stereo_enabled { set; }
	}

	/* CoglDisplay */
	[CCode (type_check_function="cogl_is_display")]
	public class Display: Object {
		public Display (OnscreenTemplate onscreen_template);

		public Renderer renderer { get; }

		public bool setup () throws GLib.Error;
	}

	/* CoglContext */
	public enum FeatureID {
		TEXTURE_NPOT_BASIC,
		TEXTURE_NPOT_MIPMAP,
		TEXTURE_NPOT_REPEAT,
		TEXTURE_NPOT,
		TEXTURE_RECTANGLE,
		TEXTURE_3D,
		GLSL,
		ARBFP,
		OFFSCREEN,
		OFFSCREEN_MULTISAMPLE,
		ONSCREEN_MULTIPLE,
		UNSIGNED_INT_INDICES,
		DEPTH_RANGE,
		POINT_SPRITE,
		MAP_BUFFER_FOR_READ,
		MAP_BUFFER_FOR_WRITE,
		MIRRORED_REPEAT,
		SWAP_BUFFERS_EVENT,
		GLES2_CONTEXT,
		DEPTH_TEXTURE,
		PRESENTATION_TIME,
		FENCE,
		PER_VERTEX_POINT_SIZE,
		TEXTURE_RG,
		BUFFER_AGE
	}

	public delegate void FeatureCallback (FeatureID feature);

	[Flags]
	public enum ReadPixelsFlags {
		COLOR_BUFFER
	}

	[CCode (type_id="cogl_context_get_gtype()",
			type_check_function="cogl_is_context")]
	public class Context: Object {
		public Context (Display? display) throws GLib.Error;
		
		public Display display { get; }
		public Renderer renderer { get; }
		
		public int64 clock_time { get; }

		[CCode (cname="cogl_has_feature")]
		public bool has_feature (FeatureID feature);
		[CCode (cname="cogl_has_features")]
		public bool has_features (...);

		[CCode (cname="cogl_foreach_feature")]
		public void foreach_feature (FeatureCallback callback);

		#if COGL_HAS_EGL_PLATFORM_ANDRIOD_SUPPORT
		[CCode (cname="cogl_android_set_native_window")]
		public Android.NativeWindow { set; }
		#endif
	}

	/* CoglPipeline */

	public enum PipelineAlphaFunc {
		NEVER,
		LESS,
		EQUAL,
		LEQUAL,
		GREATER,
		NOTEQUAL,
		GEQUAL,
		ALWAYS
	}

	public enum PipelineCullFaceMode {
		NONE,
		FRONT,
		BACK,
		BOTH
	}

	public enum Winding {
		CLOCKWISE,
		COUNTER_CLOCKWISE
	}

	public enum PipelineFilter {
		NEAREST,
		LINEAR,
		NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR
	}

	public enum PipelineWrapMode {
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		AUTOMATIC
	}

	public delegate bool PipelineLayerCallback (Pipeline pipeline, int layer_index);

	[CCode (type_id="cogl_pipeline_get_gtype()",
			type_check_function="cogl_is_pipeline")]
	public class Pipeline: Object {
		public Pipeline (Context context);
		
		public Pipeline copy ();

		public Color color { get; set; }
		public void set_color4ub (uint8 red, uint8 green, uint8 blue, uint8 alpha);
		public void set_color4f (float red, float green, float blue, float alpha);

		public void set_alpha_test_function (PipelineAlphaFunc alpha_func, float alpha_reference);
		public PipelineAlphaFunc get_alpha_test_function ();
		public float get_alpha_test_reference ();

		public bool set_blend (string blend_string) throws GLib.Error;
		public Color blend_constant { set; }
		
		public float point_size { get; set; }
		public bool set_per_vertex_point_size (bool enable) throws GLib.Error;
		public bool get_per_vertex_point_size ();

		public ColorMask color_mask { get; set; }

		public bool set_depth_state (DepthState state) throws GLib.Error;
		public DepthState get_depth_state ();

		public PipelineCullFaceMode cull_face_mode { get; set; }
		public Winding front_face_winding { get; set; }

		public void set_layer_texture (int layer_index, Texture? texture);
		public void set_layer_null_texture (int layer_index, TextureType texture_type);

		public unowned Texture? get_layer_texture (int layer_index);
		public unowned Texture? remove_layer_texture (int layer_index);

		public void set_layer_filters (int layer_index, PipelineFilter min_filter, PipelineFilter mag_filter);
		public PipelineFilter get_layer_min_filter (int layer_index);
		public PipelineFilter get_layer_mag_filter (int layer_index);

		public void set_layer_wrap_mode (int layer_index, PipelineWrapMode mode);
		public void set_layer_wrap_mode_s (int layer_index, PipelineWrapMode mode);
		public void set_layer_wrap_mode_t (int layer_index, PipelineWrapMode mode);
		public void set_layer_wrap_mode_p (int layer_index, PipelineWrapMode mode);

		public void set_layer_combine (int layer_index, string blend_string) throws BlendStringError;
		public void set_layer_combine_constant (int layer_index, Color constant);

		public void set_layer_matrix (int layer_index, Matrix matrix);

		public bool set_layer_point_sprite_coords_enabled (int layer_index, bool enabled) throws GLib.Error;
		public bool get_layer_point_sprite_coords_enabled (int layer_index);

		public void remove_layer (int layer_index);

		public int n_layers { get; }

		public void foreach_layer (PipelineLayerCallback callback);


		public int get_uniform_location (string uniform_mane);

		public void set_uniform_1f (int uniform_location, float value);
		public void set_uniform_1i (int uniform_location, int value);
		public void set_uniform_float (int uniform_location, int n_components, int count, float* value);
		public void set_uniform_int (int uniform_location, int n_components, int count, int* value);

		public void set_uniform_matrix (int uniform_location, int dimension, int count, bool transpose, float* value);
		public void add_snippet (Snippet snippet);
		public void add_layer_snippet (int layer, Snippet snippet);
	}

	public errordomain BlendStringError {
		PARSE_ERROR,
		ARGUMENT_PARSE_ERROR,
		INVALID_ERROR,
		GPU_UNSUPPORTED_ERROR
	}


	/* Depth State */
	public enum DepthTestFunction {
		NEVER,
		LESS,
		EQUAL,
		LEQUAL,
		GREATER,
		NOTEQUAL,
		GEQUAL,
		ALWAYS
	}

	public struct DepthState {
		public DepthState ();

		public bool test_enabled { get; set; }
		public DepthTestFunction test_function { get; set; }
		public bool write_enabled { get; set; }

		public void set_range (float near_val, float far_val);
		public void get_range (out float near_val, out float far_val);
	}


	/* Shader Snippet */
	public enum SnippetHook {
		VERTEX,
		VERTEX_TRANSFORM,
		VERTEX_GLOBALS,
		POINT_SIZE,

		FRAGMENT,
		FRAGMENT_GLOBALS,

		TEXTURE_COORD_TRANSFORM,

		LAYER_FRAGMENT,
		TEXTURE_LOOKUP
	}

	[CCode (type_id="cogl_snippet_get_gtype()",
			type_check_function="cogl_is_snippet")]
	public class Snippet: Object {
		public Snippet (SnippetHook hook, string? declaration, string? post);

		public SnippetHook hook { get; }

		public string? declarations { get; set; }
		public string? pre { get; set; }
		public string? replace { get; set; }
		public string? post { get; set; }
	}




	/* CoglBuffer */
	public errordomain BufferError {
		MAP
	}
	
	public enum BufferUpdateHint {
		STATIC,
		DYNAMIC,
		STREAM
	}

	[Flags]
	public enum BufferAccess {
		READ,
		WRITE,
		READ_WRITE
	}

	[Flags]
	public enum BufferMapHint {
		DISCARD,
		DISCARD_RANGE
	} 

	[CCode (type_id="cogl_buffer_get_gtype()",
			type_check_function="cogl_is_buffer")]
	public class Buffer: Object {
		public uint size { get; }

		public BufferUpdateHint update_hint { get; set; }

		public void* map (BufferAccess access, BufferMapHint hints);
		public void* map_range (size_t offset, size_t size, BufferAccess access, BufferMapHint hints) throws GLib.Error;
		public void unmap ();

		public bool set_data (size_t offset, void* data, size_t size);
	}



	[CCode (type_id="cogl_pixel_buffer_get_type()",
			type_check_function="cogl_is_pixel_buffer")]
	public class PixelBuffer: Buffer {
		public PixelBuffer (Context context, size_t size, void* data);
	}

	[CCode (type_id="cogl_attribute_buffer_get_gtype()",
			type_check_function="cogl_is_attribute_buffer")]
	public class AttributeBuffer: Buffer {
		public AttributeBuffer (Context context, size_t bytes, void* data);
		public AttributeBuffer.with_size (Context context, size_t btyes);
	}

	[CCode (type_id="cogl_index_buffer_get_gtype()",
			type_check_function="cogl_is_index_buffer")]
	public class IndexBuffer: Buffer {
		public IndexBuffer (Context context, size_t bytes);
	}





	/* Vertex Attributes */
	[CCode (type_check_function="cogl_is_attribute")]
	public class Attribute: Object {
		public Attribute (AttributeBuffer attribute_buffer,
				string name,
				size_t stride,
				size_t offset,
				int componenets,
				AttributeType type );

		public Attribute.const_1f (Context context,
					   string name,
					   float value);

		public Attribute.const_2f (Context context,
					   string name,
					   float component0,
					   float component1);

		public Attribute.const_3f (Context context,
					   string name,
					   float component0,
					   float component1,
					   float component2);

		public Attribute.const_4f (Context context,
					   string name,
					   float component0,
					   float component1,
					   float component2,
					   float component3);

		public Attribute.const_2fv (Context context,
					    string name,
					    [CCode (array_length=false)]float[] value);

		public Attribute.const_3fv (Context context,
					    string name,
					    [CCode (array_length=false)]float[] value);

		public Attribute.const_4fv (Context context,
					    string name,
					    [CCode (array_length=false)]float[] value);

		public Attribute.const_2x2fv (Context context,
					      string name,
					      [CCode (array_length=false)]float[] value);

		public Attribute.const_3x3fv (Context context,
					      string name,
					      [CCode (array_length=false)]float[] value);

		public Attribute.const_4x4fv (Context context,
					      string name,
					      [CCode (array_length=false)]float[] value);


		
		public bool normalized { get; set; }
		public AttributeBuffer buffer { get; set; }
	}




	/* Indices */
	public enum IndicesType {
		UNSIGNED_BYTE,
		UNSIGNED_SHORT,
		UNSIGNED_INT
	}

	[CCode (type_id="cogl_indices_get_gtype()",
			type_check_function="cogl_is_indices")]
	public class Indices: Object {
		public Indices (Context context, IndicesType type, void* indices_data, int n_indices);
		public Indices.for_buffer (IndicesType type, IndexBuffer buffer, size_t offset);

		[CCode (cname="cogl_get_rectangle_indices")]
		public static Indices get_rectangle_indices (Context context, int n_rectangles);
		
		public IndexBuffer buffer { get; }
		public IndicesType type { get; }
		public size_t offset { get; set; }
	}




	/* Primitives */
	public delegate bool PrimitiveAttributeCallback (Primitive primitive, Attribute attribute);

	[CCode (type_id="cogl_primitive_get_gtype()",
			type_check_function="cogl_is_primitive")]
	public class Primitive: Object {
		public Primitive (VerticesMode mode, int n_vertices, ...);
		public Primitive.with_attributes (VerticesMode mode, int n_vertices, Attribute[] attributes);
		public Primitive.p2 (Context context, VerticesMode mode, [CCode(array_length_pos=2.5)]VertexP2[] data);
		public Primitive.p3 (Context context, VerticesMode mode, [CCode(array_length_pos=2.5)]VertexP3[] data);
		public Primitive.p2c4 (Context context, VerticesMode mode, [CCode(array_length_pos=2.5)]VertexP2C4[] data);
		public Primitive.p3c4 (Context context, VerticesMode mode, [CCode(array_length_pos=2.5)]VertexP3C4[] data);
		public Primitive.p2t2 (Context context, VerticesMode mode, [CCode(array_length_pos=2.5)]VertexP2T2[] data);
		public Primitive.p3t2 (Context context, VerticesMode mode, [CCode(array_length_pos=2.5)]VertexP3T2[] data);
		public Primitive.p2t2c4 (Context context, VerticesMode mode, [CCode(array_length_pos=2.5)]VertexP2T2C4[] data);
		public Primitive.p3t2c4 (Context context, VerticesMode mode, [CCode(array_length_pos=2.5)]VertexP3T2C4[] data);

		public int first_vertex {get; set;}
		public int n_vertices {get; set;}
		public VerticesMode mode {get; set;}

		public Attribute[] attributes {set; }

		public unowned Indices get_indices ();
		public void set_indices (Indices indices, int n_indices);

		public Primitive copy ();

		public void foreach_attribute (PrimitiveAttributeCallback callback);
		public void draw (Framebuffer framebuffer, Pipeline pipeline);
	}

	/* Bitmap */
	public errordomain BitmapError {
		FAILED,
		UNKNOWN_TYPE,
		CORRUPT_IMAGE
	}

	[CCode (type_id="cogl_bitmap_get_gtype ()",
			type_check_function="cogl_is_bitmap")]
	public class Bitmap: Object {
		public static bool get_size_from_file (string filename, out int width, out int height);
	
		public Bitmap.from_file (string filename) throws GLib.Error, BitmapError;
		public Bitmap.from_buffer (Buffer buffer, PixelFormat format, int width, int height, int rowstride, int offset);
		public Bitmap.with_size (Context context, uint width, uint height, PixelFormat format);
		public Bitmap.for_data (Context context, int width, int height, PixelFormat format, int rowstride, uint8* data);

		public PixelFormat format { get; }
		public int width { get; }
		public int height { get; }
		public int rowstride { get; }
		public PixelBuffer? buffer { get; }

		#if COGL_HAS_ANDRIOD_SUPPORT
		public Bitmap.from_asset (Context context,
					  Android.AssetManager manager,
					  string filename) throws GLib.Error, BitmapError;
		#endif
	}

	/* Texture */
	public errordomain TextureError {
		SIZE,
		FORMAT,
		BAD_PARAMETER,
		TYPE
	}

	public enum TextureType {
		2D,
		3D,
		RECTANGLE
	}

	public enum TextureComponents {
		A,
		RG,
		RGB,
		RGBA,
		DEPTH
	}

	[CCode (type_id="cogl_texture_get_gtype()",
			type_check_function="cogl_is_texture")]
	public class Texture: Object {
		[CCode(cname="COGL_TEXTURE_MAX_WASTE")]
		public const int MAX_WASTE;
	
		public uint width { get; }
		public uint height { get; }
		public PixelFormat format { get; }
		public bool sliced {	[CCode (cname="cogl_texture_is_sliced")]get; }
		
		public TextureComponents components { get; set; }
		public bool premultiplied { get; set; }
		
		public int max_waste { get; }
		
		public bool get_gl_texture (out uint out_gl_handle, out uint out_gl_target);

		public bool allocate () throws GLib.Error;

		public int get_data (PixelFormat format, uint rowstride, uint8* data);
		public bool set_data (PixelFormat format, int rowstride, uint8* data, int level) throws GLib.Error;

		public bool set_region (
				int src_x, int src_y, int dst_x, int dst_y,
				uint dst_width, uint dst_height, int width, int height,
				PixelFormat format,
				int rowstride,
				uint8* data) throws GLib.Error;
				
		public bool set_region_from_bitmap (
				int src_x, int src_y, int dst_x, int dst_y,
				uint dst_width, uint dst_height,
				Cogl.Bitmap bitmap);
	}

	/* High Level Meta Textures */
	public delegate void MetaTextureCallback (
			Texture sub_texture,
			float* sub_texture_coords,
			float* meta_coords	);

	[CCode (type_id="cogl_meta_texture_get_gtype()",
			type_check_function="cogl_is_meta_texture")]
	public class MetaTexture: Texture {
		public void foreach_in_region (float tx_1, float ty_1, float tx_2, float ty_2,
				PipelineWrapMode wrap_s,
				PipelineWrapMode wrap_t,
				MetaTextureCallback callback);
	}


	[CCode (type_id="cogl_sub_texture_get_gtype()",
			type_check_function="cogl_is_sub_texture")]
	public class SubTexture: MetaTexture {
		public SubTexture (Context ctx, Texture parent_texture, int sub_x, int sub_y, int sub_width, int sub_height);
		
		public Texture parent { get; }
	}


	[CCode (type_id="cogl_texture_2d_sliced_get_gtype()",
			type_check_function="cogl_is_texture_2d_sliced",
			cprefix="cogl_texture_2d_sliced_")]
	public class Texture2DSliced: MetaTexture {
		public Texture2DSliced.with_size (Context ctx,
				int width, int height, int max_waste);
		public Texture2DSliced.from_file (Context ctx,
				string filename, int max_waste) throws GLib.Error;
		public Texture2DSliced.from_data (Context ctx,
				int width, int height, int max_waste, PixelFormat format,
				int rowstride, uint8* data) throws GLib.Error;
		public Texture2DSliced.from_bitmap (Bitmap bmp, int max_waste) throws GLib.Error;
	}


	[CCode (type_id="cogl_atlas_texture_get_gtype()",
			type_check_function="cogl_is_atlas_texture")]
	public class AtlasTexture: MetaTexture {
		public AtlasTexture.with_size (int width, int height);
		public AtlasTexture.from_file (Context ctx, string filename) throws GLib.Error;
		public AtlasTexture.from_data (Context ctx,
				int width, int height,
				PixelFormat format,
				int rowstride,
				uint8* data)	throws GLib.Error;
		public AtlasTexture.from_bitmap (Bitmap bmp);
	}
	


	/* Low-level primitive textures */
	[CCode (type_id="cogl_primitive_texture_get_gtype()",
			type_check_function="cogl_is_primitive_texture")]
	public class PrimitiveTexture: Texture {
		public bool auto_mipmap { set; }
	}
	
	

	[CCode (type_id="cogl_texture_2d_get_gtype()",
			type_check_function="cogl_is_texture_2d",
			cprefix="cogl_texture_2d_")]
	public class Texture2D: PrimitiveTexture {
		public Texture2D.with_size (Context ctx, int width, int height);
		public Texture2D.from_file (Context ctx, string filename) throws GLib.Error;
		public Texture2D.from_bitmap (Bitmap bitmap) throws GLib.Error;
		public Texture2D.from_data (Context ctx,
				int width, int height,
				PixelFormat format,
				int rowstride,
				uint8* data) throws GLib.Error;
		public Texture2D.gl_from_foreign (uint gl_handle, int width, int height, PixelFormat format);
	}

	[CCode (type_id="cogl_texture_3d_get_gtype",
			type_check_function="cogl_is_texture_3d",
			cprefix="cogl_texture_3d_")]
	public class Texture3D: PrimitiveTexture {
		public Texture3D.with_size (Context ctx, int width, int height, int depth);
		public Texture3D.from_bitmap (Bitmap bitmap, int height, int depth);
		public Texture3D.from_data (Context ctx,
				int width, int height, int depth,
				PixelFormat format,
				int rowstride, int image_stride, uint8* data) throws GLib.Error;
	}

	[CCode (type_id="cogl_texture_rectangle_get_gtype()",
			type_check_function="cogl_is_texture_rectangle")]
	public class TextureRectangle: PrimitiveTexture {
		public TextureRectangle.with_size (Context ctx, int width, int height);
		public TextureRectangle.from_bitmap (Bitmap bitmap);
		public TextureRectangle.from_foreign (Context ctx,
				uint gl_handle, int width, int height, 
				PixelFormat format	);
	}





	/* CoglFrameBuffer */
	public errordomain FramebufferError {
		ALLOCATE
	}
	
	[CCode (type_id="cogl_framebuffer_get_gtype()")]
	public class Framebuffer: Object {
		public bool allocate () throws GLib.Error;

		public int width { get; }
		public int height { get; }

		public void set_viewport (float x, float y, float width, float height);
		public float viewport_x { get; }
		public float viewport_y { get; }
		public float viewport_width { get; }
		public float viewport_height { get; }

		public void get_viewport4fv (float* viewport);

		public PixelFormat color_format { get; }

		public int red_bits { get; }
		public int green_bits { get; }
		public int blut_bits { get; }
		public int alpha_bits { get; }
		public int depth_bits { get; }
		public ColorMask color_mask { get; set; }

		public bool stereo { [CCode (cname="cogl_framebuffer_is_stereo")] get; }
		public StereoMode stereo_mode { get; set; }

		public int samples_per_pixel { get; set; }

		public void resolve_samples ();
		public void resolve_samples_region (int x, int y, int width, int height);

		public Context context { get; }


		public void clear (BufferBit buffers, Color color);
		public void clear4f (BufferBit buffers, float red, float greee, float blue, float alpha);
		public bool read_pixels_into_bitmap (int x, int y, ReadPixelsFlags source, Bitmap bitmap);
		public bool read_pixels (int x, int y, int width, int height, PixelFormat format, uint8[] pixels);

		public bool dither_enabled { get; set; }

		public void draw_rectangle (Pipeline pipeline, float x_1, float y_1, float x_2, float y_2);
		public void draw_textured_rectangle (Pipeline pipeline,
				float x_1, float y_1, float x_2, float y_2,
				float s_1, float t_1, float s_2, float t_2);
		public void draw_multitextured_rectangle (Pipeline pipeline,
				float x_1, float y_1, float x_2, float y_2, float[] tex_coords);
		public void draw_rectangles (Pipeline pipeline, float[] coordinates, uint n_rectangles);
		public void draw_textured_rectangles (Pipeline pipeline, float[] coordinates, uint n_rectangles);
	
		public void discard_buffers (BufferBit buffers);

		public void finish ();

		public bool read_pixels_into_bitmap (int x, int y, ReadPixelsFlags source, Bitmap bitmap);
		public bool read_pixels (int x, int y, int width, int height, PixelFormat format, uint8 *pixels);


		public void push_matrix ();
		public void pop_matrix ();
		public void identity_matrix ();

		public void scale (float x, float y, float z);
		public void translate (float x, float y, float z);
		public void rotate (float angle, float x, float y, float z);
		public void rotate_euler (Euler euler);
		public void rotate_quaternion (Quaternion quaternion);

		public void transform (Matrix matrix);
		public Matrix modelview_matrix { owned get; set; }

		public void perspective (float fov_y, float aspect, float z_near, float z_far);
		public void frustum (float left, float right, float bottom,  float top, float z_near, float z_far);
		public void orthographic (float x_1, float y_1, float x_2, float y_2, float near, float far);

		public Matrix projection_matrix { owned get; set; }
		

		public void push_scissor_clip (int x, int y, int width, int height);
		public void push_rectangle_clip (int x, int y, int width, int height);
		public void push_primitive_clip (Primitive primitive,
				float bounds_x1, float bounds_y1, float bounds_x2, float bounds_y2);
		
		public void pop_clip ();

		public bool depth_write_enabled { get; set; }
		public bool depth_texture_enabled { get; set; }
		public Texture depth_texture { get; }
		
		// Cogl Fence
		public FenceClosure* add_fence_callback (FenceCallback callback);
		public void cancel_fence_callback (FenceClosure* closure);
	}

	public enum FrameEvent {
		SYNC,
		COMPLETE
	}
	
	public enum SubpixelOrder {
		UNKNOWN,
		NONE,
		HORIZONTAL_RGB,
		HORIZONTAL_BGR,
		VERTICAL_RGB,
		VERTICAL_BGR
	}
	
	
	[CCode (type_id="cogl_output_get_gtype()",
			type_check_function="cogl_is_output")]
	public class Output: Object {
		public int x { get; }
		public int y { get; }
		public int width { get; }
		public int height { get; }
		public int mm_width { get; }
		public int mm_height { get; }
		public SubpixelOrder subpixel_order { get; }
		public float refresh_rate { get; }
	}

	[CCode (type_id="cogl_frame_info_get_gtype()",
			type_check_function="cogl_is_frame_info")]
	public class FrameInfo: Object {
		public int64 frame_counter { get; }
		public int64 presentation_time { get; }
		public float refresh_rate { get; }
		public Output output { get; }
	}

	/* CoglOnscreen */
	public delegate void FrameCallback (Onscreen onscreen, FrameEvent event, FrameInfo info);

	public delegate void OnscreenDirtyCallback (Onscreen onscreen, OnscreenDirtyInfo info);

	public delegate void OnscreenResizeCallback (Onscreen onscreen, int width, int height);

	public struct OnscreenDirtyInfo {
		int x;
		int y;
		int width;
		int height;
	}

	[CCode (type_id="cogl_frame_closure_get_gtype()")]
	[Compact]
	public class FrameClosure {
	}

	[CCode (type_id="cogl_oncscreen_dirty_closure_get_gtype()")]
	[Compact]
	public class OnscreenDirtyClosure {
	}
	
	[CCode (type_id="cogl_oncscreen_resize_closure_get_gtype()")]
	[Compact]
	public class OnscreenResizeClosure {
	}


	[CCode (type_id="cogl_onscreen_get_gtype ()",
			type_check_function="cogl_is_onscreen")]
	public class Onscreen: Framebuffer {
		public Onscreen (Context context, int width, int height);
		
		public void show ();
		public void hide ();

		public FrameClosure* add_frame_callback (owned FrameCallback callback);
		public void remove_frame_callback (FrameClosure* closure);

		public OnscreenDirtyClosure* add_dirty_callback (owned OnscreenDirtyCallback callback);
		public void remove_dirty_callback (OnscreenDirtyClosure closure);

		public OnscreenResizeClosure add_resize_callback (owned OnscreenResizeCallback callback);
		public void remove_resize_callback (OnscreenResizeClosure closure);

		public void swap_buffers ();
		public void swap_buffers_with_damage (int* rectangles, int n_rectangles);
		public void swap_region (int* rectangles, int n_rectangles);
		
		public bool swap_throttled { set; }
		public int buffer_age { get; }
		
		public bool resizable { get; set; }
		public int64 frame_counter { get; }
	}

	/* CoglOffscreen */
	[CCode (type_id="cogl_offscreen_get_gtype()",
			type_check_function="cogl_is_offscreen")]
	public class Offscreen: Framebuffer {
		public Offscreen.with_texture (Texture texture);
	}


	/* Color type */
	[CCode (type_id="cogl_color_get_gtype()",
		copy_function="cogl_color_copy",
		free_function="cogl_color_free")]
	[Compact]
	public class Color {

		public Color ();

		public void Color.init_from_4ub (uint8 red, uint8 green, uint8 blue, uint8 alpha);
		public void Color.init_from_4f (float red, float green, float blue, float alpha);
		public void Color.init_from_4fv (float* color_array);

		public uchar red_byte { get; set; }
		public uchar green_byte { get; set; }
		public uchar blue_byte { get; set; }
		public uchar alpha_byte { get; set; }

		public float red_float { get; set; }
		public float green_float { get; set; }
		public float blue_float { get; set; }
		public float alpha_float { get; set; }

		public void premultiply ();
		public void unpremultiply ();

		public static bool equal (Color v1, Color v2);

		public void Color.init_from_hsl (float hue, float saturation, float luminance);
		public void to_hsl (out float hue, out float saturation, out float luminanace);
	}
	
	
	
	

	/* Matrices */
	[CCode (type_id="cogl_matrix_get_gtype()",
		copy_function="cogl_matrix_copy",
		free_function="cogl_matrix_free")]
	public struct Matrix {
		public float xx;
		public float yx;
		public float zx;
		public float wx;

		public float xy;
		public float yy;
		public float zy;
		public float wy;

		public float xz;
		public float yz;
		public float zz;
		public float wz;

		public float xw;
		public float yw;
		public float zw;
		public float ww;

		public Matrix.identity ();
		public Matrix.translation (float tx, float ty, float tz);
		
		public Matrix.from_array (float* array);
		public Matrix.from_quaternion (Quaternion quaternion);
		public Matrix.from_euler (Euler euler);
		
		public void frustum (float left, float right,
				float bottom, float top,
				float z_near, float z_far);
		public void orthographic (float x_1, float y_1,
				float x_2, float y_2,
				float near, float far);
		public void perspective (float fov_y, float aspect, float z_near, float z_far);

		public void look_at (
				float eye_position_x,
				float eye_position_y,
				float eye_position_z,
				float object_x,
				float object_y,
				float object_z,
				float world_up_x,
				float world_up_y,
				float world_up_z);
		
		public void view_2d_in_frustum (
				float left,
				float right,
				float bottom,
				float top,
				float z_near,
				float z_2d,
				float width_2d,
				float height_2d	);

		public void view_2d_in_perspective (
				float fov_y,
				float aspect,
				float z_near,
				float z_2d,
				float width_2d,
				float height_2d	);
				
		public Matrix.multiply (Matrix a, Matrix b);

		public void rotate (float angle, float x, float y, float z);
		public void rotate_quaternion (Quaternion quaternion);
		public void rotate_euler (Euler euler);
		
		public void translate (float x, float y, float z);
		public void scale (float sx, float sy, float sz);

		public void transpose ();

		public float* array { get; }
		
		public bool is_identity ();
		
		public bool get_inverse (out Matrix inverse);
		
		public static bool equal (Matrix v1, Matrix v2);

		public void transform_point (ref float x, ref float y, ref float z, ref float w);
		public void transform_points (int n_components, size_t stride_in, void* points_in, size_t stride_out, void* points_out, int n_points);
		public void project_points (int n_components, size_t stride_in, void* points_in, size_t stride_out, void* points_out, int n_points);

		[CCode (cname="cogl_debug_matrix_print")]
		public void debug_print ();
	}





	[CCode (type_id="cogl_matrix_stack_get_gtype()",
			type_check_function="cogl_is_matrix_stack")]
	[Compact]
	public class MatrixStack {
		public MatrixStack (Context ctx);


		public void push ();
		public void pop ();

		public void load_identity ();
		public void scale (float x, float y, float z);
		public void translate (float x, float y, float z);
		public void rotate (float angle, float x, float y, float z);
		public void rotate_quaternion (Quaternion quaternion);
		public void rotate_euler (Euler euler);

		public void multiply (Matrix matrix);

		public void frustum (	float left,		float right,
								float bottom,	float top,
								float z_near,	float z_far		);
		public void perspective (float fov_y, float aspect, float z_near, float z_far);
		public void orthographic (float x_1, float y_1, float x_2, float y_2, float near, float far);

		public bool get_inverse (out Matrix inverse);

		public MatrixEntry entry { get; }

		public unowned Matrix? get (out Matrix matrix);
		public void set (Matrix matrix);
		
	}
	
	

	[Compact]
	[CCode (type_id="cogl_matrix_entry_get_gtype()",
		ref_function="cogl_matrix_entry_ref",
		unref_function="cogl_matrix_entry_unref")]
	public class MatrixEntry {
		public unowned Matrix? get (out Matrix matrix);

		public bool calculate_translation (MatrixEntry entry0, MatrixEntry entry1,
				out float x, out float y, out float z);

		public bool is_identity ();

		public static bool equal (MatrixEntry entry0, MatrixEntry entry1);
		
		[CCode(cname="cogl_debug_matrix_entry_print")]
		public void debug_print ();
	}





	[CCode (type="float*",
		copy_function="cogl_vector3_copy",
		free_function="cogl_vector3_free")]
	public struct Vector3 {
		public float x;
		public float y;
		public float z;

		public Vector3 (float x, float y, float z);
		public Vector3.zero ();
		public static bool equal (Vector3 v1, Vector3 v2);
		public static bool equal_with_epsilon (Vector3 vector0, Vector3 vector1, float epsilon);

		public void invert ();
		public Vector3.add (Vector3 a, Vector3 b);
		public Vector3.subtract (Vector3 a, Vector3 b);
		public void multiply_scalar (float scalar);
		public void divide_scalar (float scalar);
		public void normalize ();
		public float magnitude ();
		public Vector3.cross_product (Vector3 u, Vector3 v);
		public float dot_product (Vector3 b);
		public float distance (Vector3 b);
	}

	[CCode (type_id="cogl_euler_get_gtype()",
		copy_function="cogl_euler_copy",
		free_function="cogl_euler_free")]
	public struct Euler {
		public float heading;
		public float pitch;
		public float roll;

		public Euler (float heading, float pitch, float roll);
		public Euler.from_matrix (Matrix matrix);
		public Euler.from_quaternion (Quaternion quaternion);

		public static bool equal (Euler v1, Euler v2);
	}

	[CCode (type_id="cgol_quaternion_get_gtype()",
		copy_function="cogl_quaternion_copy",
		free_function="cogl_quaternion_free")]
	public struct Quaternion {
		public static Quaternion static_identity_quaternion { get; }
		public static Quaternion static_zero_quaternion { get; }
	
		public float w;
		public float x;
		public float y;
		public float z;
		
		public float rotation_angle { get; }
		public Vector3 rotation_axis { get; }
		
		public void normalize ();
		public void invert ();
		
		public void multiply (Quaternion left, Quaternion right);
		public void pow (float exponent);
		public void slerp (Quaternion a, Quaternion b, float t);
		public void nlerp (Quaternion a, Quaternion b, float t);
		public void squad (Quaternion prev, Quaternion a, Quaternion b, Quaternion next, float t);
		
		public float dot_product (Quaternion b);

		public Quaternion.identity ();
		public Quaternion (float angle, float x, float y, float z);
		public Quaternion.from_angle_vector (float angle, Vector3 axis3f);
		public Quaternion.from_array (float* array);
		public Quaternion.from_x_rotation (float angle);
		public Quaternion.from_y_rotation (float angle);
		public Quaternion.from_z_rotation (float angle);
		public Quaternion.from_euler (Euler euler);
		public Quaternion.from_quaternion (Quaternion src);
		public Quaternion.from_matrix (Matrix matrix);
		
		public static bool equal (Quaternion v1, Quaternion v2);
	}

	public delegate void FenceCallback (Fence fence);


	// Cogl Fence - GPU Synchronization
	[Compact]
	public class Fence {
	}

	[Compact]
	public class FenceClosure {
		public void*	user_data { get; }
	}


	// Versioning utility macros

	[CCode (cname="COGL_VERSION_MAJOR")]
	public static const uint VERSION_MAJOR;
	public static const uint VERSION_MINOR;
	public static const uint VERSION_MICRO;
	public static const string VERSION_STRING;

	public static uint VERSION_ENCODE (uint major, uint minor, uint micro);
	public static bool VERSION_CHECK (uint major, uint minor, uint micro);

	public static uint VERSION_GET_MAJOR (uint version);
	public static uint VERSION_GET_MINOR (uint version);
	public static uint VERSION_GET_MICRO (uint version);


	// Main loop integration
	public enum PollFDEvent {
		IN,
		PRI,
		OUT,
		ERR,
		HUP,
		NVAL
	}

	public struct PollFD {
		public int fd;
		public short events;
		public short revents;
	}
	
	[CCode (cname="GSource")]
	public class GLibSource: GLib.Source {
		public GLibSource (Context context, int priority = GLib.Priority.DEFAULT);
		[CCode (cname="cogl_glib_render_source_new")]
		public GLibSource.render (Context context, int priority = GLib.Priority.DEFAULT);
	}
	
	

	// A Potrable api to access OpenGLES 2.0

	namespace GLES2 {
		public errordomain ContextError {
			UNSUPPORTED,
			DRIVER
		}

		[CCode (type_id="cogl_gles2_context_get_gtype()",
			type_check_function="cogl_is_gles2_context")]
		public class Context {
			public Context (Cogl.Context ctx) throws ContextError;
			public Vtable { get; }
		}
		public struct Vtable {}

		[CCode (cname="cogl_push_gles2_context")]
		public bool push_context (Cogl.Context ctx,
					  Cogl.GLES2.Context gles2_ctx,
					  Framebuffer read_bufer,
					  Framebuffer write_buffer) throws GLib.Error;

		[CCode (cname="cogl_pop_gles2_context")]
		public void pop_context (Cogl.Context ctx);

		public unowned Vtable? get_current_vtable ();

		public Texture2D texture_2d_new_from_handle (Cogl.Context ctx,
							     Cogl.GLES2.Context gles2_ctx,
							     uint handle,
							     int width,
							     int height,
							     PixelFormat format);

		public bool texture_get_handle (Texture texture,
						out uint handle,
						out uint target);
	}
	
	
	
	
	[SimpleType]
	[PointerType]
	public struct Handle {
	}
	
	[Compact]
	public class Material{
	}
	
	[SimpleType]
	[IntegerType]
	public struct Fixed: int32 {
	}
	
	public struct TextureVertex {
		public float x;
		public float y;
		public float z;
		public float tx;
		public float ty;
		public Color color;
	}
}

