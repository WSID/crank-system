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

/**
 * SECTION: crankprojection
 * @title: CrankProjection
 * @short_description: Projeciton Representation.
 * @stability: unstable
 * @include: crankvisual.h
 *
 * Represents a projection. As it is large, it is allocated from slice.
 *
 * # Using it with #CoglSnippet
 *
 * This struct provides definition snippet via crank_projection_get_snippet_def().
 * And its data can be sent by crank_projection_set_uniform_value().
 *
 * For performance reason, this defines structure of int and float[6], so it is
 * adviced to use with getter functions.
 *
 * the snippet contains following definition.
 *
 * * #<!---->define CrankProjectionType int
 *   * It can be used just as in C.
 * * struct CrankProjection
 *   * CrankProjectionType proj_type
 *   * float params[6]
 * * float crank_projection_get_left (#CrankProjection projection)
 * * float crank_projection_get_right (#CrankProjection projection)
 * * float crank_projection_get_bottom (#CrankProjection projection)
 * * float crank_projection_get_top (#CrankProjection projection)
 * * float crank_projection_get_near (#CrankProjection projection)
 * * float crank_projection_get_far (#CrankProjection projection)
 * * void crank_projection_get_nf_points (#CrankProjection projection,
 *                                        vec2 screen_coord,
 *                                        out vec3 near_point,
 *                                        out vec3 far_point)
 *   Gets @near_point and @far_point of given @screen_coord.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"
#include "crankprojection.h"

//////// Snippet Definition ////////////////////////////////////////////////////

static const gchar *snippet_definition =
"#define CrankProjectionType int\n"
"const CrankProjectionType CRANK_PROJECTION_ORTHO = 0;\n"
"const CrankProjectionType CRANK_PROJECTION_FRUSTUM = 1;\n"
"struct CrankProjection {\n"
"  CrankProjectionType proj_type;\n"
"  float params[6];\n"
"};\n"

"float crank_projection_get_left (CrankProjection projection) {\n"
"  return projection.params[0];\n"
"}\n"
"float crank_projection_get_right (CrankProjection projection) {\n"
"  return projection.params[1];\n"
"}\n"
"float crank_projection_get_bottom (CrankProjection projection) {\n"
"  return projection.params[2];\n"
"}\n"
"float crank_projection_get_top (CrankProjection projection) {\n"
"  return projection.params[3];\n"
"}\n"
"float crank_projection_get_near (CrankProjection projection) {\n"
"  return projection.params[4];\n"
"}\n"
"float crank_projection_get_far (CrankProjection projection) {\n"
"  return projection.params[5];\n"
"}\n"
"void crank_projection_get_nf_points (CrankProjection projection,\n"
"                                     vec2            screen_coord,"
"                                     out vec3        near_point,"
"                                     out vec3        far_point)"
"{"
"  vec2 base_lb = vec2 (crank_projection_get_left (projection),\n"
"                       crank_projection_get_bottom (projection));\n"
"  vec2 base_rt = vec2 (crank_projection_get_right (projection),\n"
"                       crank_projection_get_top (projection));\n"
"  float nf_base_ratio = mix (1,\n"
"                             crank_projection_get_far (projection) /\n"
"                             crank_projection_get_near (projection),\n"
"                             projection.proj_type);\n"
"  vec2 base = mix (base_lb, base_rt, screen_coord);\n"
"  near_point = vec3 (base, crank_projection_get_near (projection));\n"
"  far_point = vec3 (base * nf_base_ratio, crank_projection_get_far (projection));\n"
"}"
;


//////// Private Functions /////////////////////////////////////////////////////

static void crank_projection_build_ortho_param (CrankProjection *projection);

static void crank_projection_build_frustum_param (CrankProjection *projection);

static void crank_projection_build_ortho_mat (CrankProjection *projection);

static void crank_projection_build_frustum_mat (CrankProjection *projection);

static void crank_projection_build_ortho_cull_plane (CrankProjection *projection);

static void crank_projection_build_frustum_cull_plane (CrankProjection *projection);


//////// Type Definition ///////////////////////////////////////////////////////
GType crank_projection_type_get_type (void)
{
  static const GEnumValue values[] = {
      {CRANK_PROJECTION_ORTHO, "CRANK_PROJECTION_ORTHO", "ortho"},
      {CRANK_PROJECTION_FRUSTUM, "CRANK_PROJECTION_FRUSTUM", "frustum"},
      {0, NULL, NULL}
  };

  static GType type_id = G_TYPE_INVALID;

  if (g_once_init_enter (&type_id))
    {
      GType type = g_enum_register_static ("CrankProjectionType", values);
      g_once_init_leave (&type_id, (gsize) type);
    }

  return type_id;
}




G_DEFINE_BOXED_TYPE (CrankProjection,
                     crank_projection,
                     crank_projection_ref,
                     crank_projection_unref);


/////// Constructors ///////////////////////////////////////////////////////////

/**
 * crank_projection_new:
 *
 * Constructs new identity projection struct.
 *
 * Returns: (transfer full): New Projection struct.
 */
CrankProjection*
crank_projection_new (void)
{
  CrankProjection *proj = g_slice_new (CrankProjection);
  crank_projection_set_identity (proj);

  return proj;
}

/**
 * crank_projection_new_ortho:
 * @left: Left of projection.
 * @right: Rigth of projection.
 * @top: Top of projection.
 * @bottom: Bottom of projection.
 * @near: Near of projection.
 * @far: Far of projection.
 *
 * Constructs new orthogonal projection struct.
 *
 * Returns: (transfer full): New Projection struct.
 */
CrankProjection*
crank_projection_new_ortho (const gfloat left,
                            const gfloat right,
                            const gfloat bottom,
                            const gfloat top,
                            const gfloat near,
                            const gfloat far)
{
  CrankProjection *proj = g_slice_new (CrankProjection);
  crank_projection_set_ortho (proj, left, right, bottom, top, near, far);

  return proj;
}

/**
 * crank_projection_new_frustum:
 * @left: Left of projection.
 * @right: Rigth of projection.
 * @bottom: Bottom of projection.
 * @top: Top of projection.
 * @near: Near of projection.
 * @far: Far of projection.
 *
 * Constructs new frustum projection struct.
 *
 * Returns: (transfer full): New Projection struct.
 */
CrankProjection*
crank_projection_new_frustum (const gfloat left,
                              const gfloat right,
                              const gfloat bottom,
                              const gfloat top,
                              const gfloat near,
                              const gfloat far)
{
  CrankProjection *proj = g_slice_new (CrankProjection);
  crank_projection_set_frustum (proj, left, right, bottom, top, near, far);

  return proj;
}


/**
 * crank_projection_new_perspective:
 * @fovy: Left of projection.
 * @aspect: Rigth of projection.
 * @near: Near of projection.
 * @far: Far of projection.
 *
 * Constructs new perspective projection struct.
 *
 * As perspective projection is frustum, so projection type will be
 * %CRANK_PROJECTION_FRUSTUM
 *
 * Returns: (transfer full): New Projection struct.
 */
CrankProjection*
crank_projection_new_perspective (const gfloat fovy,
                                  const gfloat aspect,
                                  const gfloat near,
                                  const gfloat far)
{
  CrankProjection *proj = g_slice_new (CrankProjection);
  crank_projection_set_perspective (proj, fovy, aspect, near, far);

  return proj;
}


/**
 * crank_projection_ref:
 * @projection: (type CrankProjection): A Projection.
 *
 * Increase ref count of projection.
 *
 * As structure is large, it is allocated on heap.
 *
 * Returns: (transfer full): @projection, with increased ref count.
 */
gpointer
crank_projection_ref (gpointer projection)
{
  g_atomic_int_inc (& ((CrankProjection*)projection)->_refc);
  return projection;
}

/**
 * crank_projection_unref:
 * @projection: (transfer full) (type CrankProjection): A Projection.
 *
 * Decrease ref count of projection.
 */
void
crank_projection_unref (gpointer projection)
{
  CrankProjection *proj = (CrankProjection*) projection;

  if (g_atomic_int_dec_and_test (& proj->_refc))
    g_slice_free (CrankProjection, proj);
}


//////// Setter ////////////////////////////////////////////////////////////////

/**
 * crank_projection_set_identity:
 * @projection: A Projection.
 *
 * Set the projection into identity.
 */
void
crank_projection_set_identity (CrankProjection *projection)
{
  projection->proj_type = CRANK_PROJECTION_ORTHO;
  projection->left = -1;
  projection->right = 1;
  projection->bottom = -1;
  projection->top = 1;
  projection->near = 1;
  projection->far = -1;

  crank_mat_float4_init_diag (& projection->matrix,   1, 1, 1, 1);
  crank_mat_float4_init_diag (& projection->matrix_t, 1, 1, 1, 1);

  crank_projection_build_ortho_cull_plane (projection);
}

/**
 * crank_projection_set_ortho:
 * @projection: A Projection
 * @left: Left of projection.
 * @right: Rigth of projection.
 * @bottom: Bottom of projection.
 * @top: Top of projection.
 * @near: Near of projection.
 * @far: Far of projection.
 *
 * Set the projection into orthogonal.
 */
void
crank_projection_set_ortho (CrankProjection *projection,
                            const gfloat     left,
                            const gfloat     right,
                            const gfloat     bottom,
                            const gfloat     top,
                            const gfloat     near,
                            const gfloat     far)
{
  projection->proj_type = CRANK_PROJECTION_ORTHO;
  projection->left = left;
  projection->right = right;
  projection->bottom = bottom;
  projection->top = top;
  projection->near = near;
  projection->far = far;

  crank_projection_build_ortho_mat (projection);
  crank_projection_build_ortho_cull_plane (projection);
}

/**
 * crank_projection_set_frustum:
 * @projection: A Projection
 * @left: Left of projection.
 * @right: Rigth of projection.
 * @bottom: Bottom of projection.
 * @top: Top of projection.
 * @near: Near of projection.
 * @far: Far of projection.
 *
 * Set the projection into orthogonal.
 */
void
crank_projection_set_frustum (CrankProjection *projection,
                              const gfloat     left,
                              const gfloat     right,
                              const gfloat     bottom,
                              const gfloat     top,
                              const gfloat     near,
                              const gfloat     far)
{
  projection->proj_type = CRANK_PROJECTION_FRUSTUM;
  projection->left = left;
  projection->right = right;
  projection->bottom = bottom;
  projection->top = top;
  projection->near = near;
  projection->far = far;

  crank_projection_build_frustum_mat (projection);
  crank_projection_build_frustum_cull_plane (projection);
}

/**
 * crank_projection_set_perspective:
 * @projection: A Projection
 * @fovy: Left of projection.
 * @aspect: Rigth of projection.
 * @near: Near of projection.
 * @far: Far of projection.
 *
 * Set the projection into orthogonal.
 */
void
crank_projection_set_perspective (CrankProjection *projection,
                                  const gfloat     fovy,
                                  const gfloat     aspect,
                                  const gfloat     near,
                                  const gfloat     far)
{
  projection->proj_type = CRANK_PROJECTION_FRUSTUM;
  projection->top = 1 / tanf (fovy * 0.5f);
  projection->bottom = - projection->top;

  projection->right = projection->top * aspect;
  projection->left = - projection->right;

  projection->near = near;
  projection->far = far;

  crank_projection_build_frustum_mat (projection);
  crank_projection_build_frustum_cull_plane (projection);
}

/**
 * crank_projection_set_matrix:
 * @projection: A Projection.
 * @matrix: A Projection Matrix.
 *
 * Set projection from matrix.
 *
 * This function performs only minimal check. If @matrix is not a projection
 * matrix, the projection might not fit for this matrix.
 */
void
crank_projection_set_matrix (CrankProjection *projection,
                             CrankMatFloat4  *matrix)
{
  // Chech projection type.
  if (matrix->m32 == -1)
    {
      projection->proj_type = CRANK_PROJECTION_FRUSTUM;
      crank_mat_float4_copy (matrix, & projection->matrix);
      crank_mat_float4_transpose (matrix, & projection->matrix_t);
      crank_projection_build_frustum_param (projection);
      crank_projection_build_frustum_cull_plane (projection);
    }
  else if (matrix->m33 == 1)
    {
      projection->proj_type = CRANK_PROJECTION_ORTHO;
      crank_mat_float4_copy (matrix, & projection->matrix);
      crank_mat_float4_transpose (matrix, & projection->matrix_t);
      crank_projection_build_ortho_param (projection);
      crank_projection_build_ortho_cull_plane (projection);
    }
  else
    {
      gchar *matrix_string =
      crank_mat_float4_to_string_full (matrix,
                                       "[", ",\n     ", "]",
                                       "[", ", "      , "]",
                                       "%g");

      g_warning ("set_matrix: Given matrix is not supported.\n    %s",
                 matrix_string);

      g_free (matrix_string);
      return;
    }
}

//////// Maintaining Consistency ///////////////////////////////////////////////

/**
 * crank_projection_update_params:
 * @projection: A Projection.
 *
 * Updates parameters from matrix. This is used when user updates matrix by itselt.
 */
void
crank_projection_update_params (CrankProjection *projection)
{
  // Chech projection type.
  if (projection->matrix.m32 == -1)
    {
      projection->proj_type = CRANK_PROJECTION_FRUSTUM;
      crank_projection_build_frustum_param (projection);
    }
  else if (projection->matrix.m33 == 1)
    {
      projection->proj_type = CRANK_PROJECTION_ORTHO;
      crank_projection_build_ortho_param (projection);
    }
  else
    {
      gchar *matrix_string =
      crank_mat_float4_to_string_full (& projection->matrix,
                                       "[", ",\n     ", "]",
                                       "[", ", "      , "]",
                                       "%g");

      g_warning ("update_params: Given matrix is not supported.\n"
                 "    The projection setted as identity projection\n    %s",
                 matrix_string);

      g_free (matrix_string);

      crank_projection_set_identity (projection);
      return;
    }
}

/**
 * crank_projection_update_matrix:
 * @projection: A Projection.
 *
 * Updates matrix from parameters. This is used when user updates parameters by
 * itself.
 */
void
crank_projection_update_matrix (CrankProjection *projection)
{
  if (projection->proj_type == CRANK_PROJECTION_FRUSTUM)
    crank_projection_build_frustum_mat (projection);

  else if (projection->proj_type == CRANK_PROJECTION_ORTHO)
    crank_projection_build_ortho_mat (projection);

  else
    g_error ("update_matrix: Unsupported projection type: %u", projection->proj_type);
}

/**
 * crank_projection_update_cull_plane:
 * @projection: A Projection.
 *
 * Updates cull plane from parameters. This is used when user updates parameter
 * by itself.
 */
void
crank_projection_update_cull_plane (CrankProjection *projection)
{
  if (projection->proj_type == CRANK_PROJECTION_FRUSTUM)
    crank_projection_build_frustum_cull_plane (projection);

  else if (projection->proj_type == CRANK_PROJECTION_ORTHO)
    crank_projection_build_ortho_cull_plane (projection);

  else
    g_error ("update_matrix: Unsupported projection type: %u", projection->proj_type);
}



//////// Cogl Snippets /////////////////////////////////////////////////////////

/**
 * crank_projection_get_snippet_def:
 * @hook: Hook type for snippet.
 *
 * Gets a snippet that defines a structure type for using #CrankProjection in
 * Other snippets.
 *
 * Returns: (transfer none): A snippet that contains definition.
 */
CoglSnippet*
crank_projection_get_snippet_def (CoglSnippetHook hook)
{
  static CoglSnippet *snippet_vertex;
  static CoglSnippet *snippet_fragment;

  if (hook == COGL_SNIPPET_HOOK_VERTEX)
    {
      if (snippet_vertex == NULL)
        snippet_vertex = cogl_snippet_new (COGL_SNIPPET_HOOK_VERTEX_GLOBALS,
                                           snippet_definition,
                                           NULL);

      return snippet_vertex;
    }

  else if (hook == COGL_SNIPPET_HOOK_FRAGMENT)
    {
      if (snippet_fragment == NULL)
        snippet_fragment = cogl_snippet_new (COGL_SNIPPET_HOOK_FRAGMENT_GLOBALS,
                                             snippet_definition,
                                             NULL);

      return snippet_fragment;
    }

  else
    {
      return NULL;
    }
}

/**
 * crank_projection_get_uniform_locations:
 * @pipeline: A Pipeline that contains uniform.
 * @uniform_name: Name of uniform variable in @pipeline.
 * @locations: (array fixed-size=2) (out caller-allocates):
 *     Uniform locations of members in the structures.
 *
 * Gets array of uniform locations that #CrankProjection needs to know in order
 * to set its data on uniform variables.
 */
void
crank_projection_get_uniform_locations (CoglPipeline *pipeline,
                                        const gchar  *uniform_name,
                                        gint         *locations)
{
  GString *member_name;
  guint member_prefix_len;

  member_name = g_string_new (uniform_name);
  g_string_append_c (member_name, '.');

  member_prefix_len = member_name->len;

  g_string_append (member_name, "proj_type");
  locations[0] = cogl_pipeline_get_uniform_location (pipeline, member_name->str);

  g_string_truncate (member_name, member_prefix_len);
  g_string_append (member_name, "params");
  locations[1] = cogl_pipeline_get_uniform_location (pipeline, member_name->str);
  g_string_free (member_name, TRUE);
}

/**
 * crank_projection_set_uniform_value:
 * @projection: A Projection.
 * @pipeline: A Pipeline that contains uniform.
 * @locations: (array fixed-size=2): Uniform locations that obtained from
 *     crank_projection_get_uniform_locations().
 *
 * Sets uniform value in @pipeline at @locations.
 */
void
crank_projection_set_uniform_value (CrankProjection *projection,
                                    CoglPipeline    *pipeline,
                                    const gint      *locations)
{
  cogl_pipeline_set_uniform_1i (pipeline, locations[0], projection->proj_type);
  cogl_pipeline_set_uniform_float (pipeline, locations[1], 1, 6, & projection->left);
}




//////// Private Functions /////////////////////////////////////////////////////

static void
crank_projection_build_ortho_param (CrankProjection *projection)
{
  CrankMatFloat4 *mat = & projection->matrix;

  projection->left =   (mat->m03 + 1) * mat->m00;
  projection->right =  (mat->m03 - 1) * mat->m00;

  projection->bottom = (mat->m13 + 1) * mat->m11;
  projection->top =    (mat->m13 - 1) * mat->m11;

  projection->near = - (mat->m23 + 1) * mat->m22;
  projection->far =  - (mat->m23 - 1) * mat->m22;
}

static void
crank_projection_build_frustum_param (CrankProjection *projection)
{
  CrankMatFloat4 *mat = & projection->matrix;

  projection->far = (1 - mat->m22) * mat->m23 * 0.5f;
  projection->near = - (1 - mat->m22) * mat->m23 * 0.5f;

  projection->left =  - mat->m00 * (mat->m02 - 1) * projection->near;
  projection->right = - mat->m00 * (mat->m02 + 1) * projection->near;

  projection->bottom = - mat->m11 * (mat->m12 - 1) * projection->near;
  projection->top =    - mat->m11 * (mat->m12 + 1) * projection->near;
}

static void
crank_projection_build_ortho_mat (CrankProjection *projection)
{
  CrankMatFloat4 *mat = & projection->matrix;

  gfloat rl = 1 / (projection->right - projection->left);
  gfloat tb = 1 / (projection->top - projection->bottom);
  gfloat fn = 1 / (projection->far - projection->near);

  mat->m00 = 2 * rl;
  mat->m01 = 0;
  mat->m02 = 0;
  mat->m03 = - (projection->right + projection->left) * rl;

  mat->m10 = 0;
  mat->m11 = 2 * tb;
  mat->m12 = 0;
  mat->m13 = - (projection->top + projection->bottom) * tb;

  mat->m20 = 0;
  mat->m21 = 0;
  mat->m22 = - 2 * fn;
  mat->m23 = - (projection->far + projection->near) * fn;

  mat->m30 = 0;
  mat->m31 = 0;
  mat->m32 = 0;
  mat->m33 = 1;

  crank_mat_float4_transpose (mat, & projection->matrix_t);
}


static void
crank_projection_build_frustum_mat (CrankProjection *projection)
{
  CrankMatFloat4 *mat = & projection->matrix;

  gfloat rl = 1 / (projection->right - projection->left);
  gfloat tb = 1 / (projection->top - projection->bottom);
  gfloat fn = 1 / (projection->far - projection->near);

  mat->m00 = 2 * projection->near * rl;
  mat->m01 = 0;
  mat->m02 = (projection->right + projection->left) * rl;
  mat->m03 = 0;

  mat->m10 = 0;
  mat->m11 = 2 * projection->near * tb;
  mat->m12 = (projection->top + projection->bottom) * tb;
  mat->m13 = 0;

  mat->m20 = 0;
  mat->m21 = 0;
  mat->m22 = - (projection->far + projection->near) * fn;
  mat->m23 = - 2 * projection->far * projection->near * fn;

  mat->m30 = 0;
  mat->m31 = 0;
  mat->m32 = -1;
  mat->m33 = 0;

  crank_mat_float4_transpose (mat, & projection->matrix_t);
}

static void
crank_projection_build_ortho_cull_plane (CrankProjection *projection)
{
  projection->cull_plane[0].dist_origin = projection->left;
  crank_vec_float3_init (& projection->cull_plane[0].normal, 1, 0, 0);

  projection->cull_plane[1].dist_origin = -projection->right;
  crank_vec_float3_init (& projection->cull_plane[1].normal, -1, 0, 0);

  projection->cull_plane[2].dist_origin = projection->bottom;
  crank_vec_float3_init (& projection->cull_plane[2].normal, 0, 1, 0);

  projection->cull_plane[3].dist_origin = -projection->top;
  crank_vec_float3_init (& projection->cull_plane[3].normal, 0, -1, 0);

  projection->cull_plane[4].dist_origin = projection->near;
  crank_vec_float3_init (& projection->cull_plane[4].normal, 0, 0, -1);

  projection->cull_plane[5].dist_origin = -projection->far;
  crank_vec_float3_init (& projection->cull_plane[5].normal, 0, 0, 1);
}


static void
crank_projection_build_frustum_cull_plane (CrankProjection *projection)
{
  projection->cull_plane[0].dist_origin = 0;     // Left
  crank_vec_float3_init (& projection->cull_plane[0].normal, projection->near, 0, projection->left);
  crank_vec_float3_unit_self (& projection->cull_plane[0].normal);

  projection->cull_plane[1].dist_origin = 0;     // Right
  crank_vec_float3_init (& projection->cull_plane[1].normal, -projection->near, 0, -projection->right);
  crank_vec_float3_unit_self (& projection->cull_plane[1].normal);

  projection->cull_plane[2].dist_origin = 0;     // Bottom
  crank_vec_float3_init (& projection->cull_plane[2].normal, 0, projection->near, projection->bottom);
  crank_vec_float3_unit_self (& projection->cull_plane[2].normal);

  projection->cull_plane[3].dist_origin = 0;     // top
  crank_vec_float3_init (& projection->cull_plane[3].normal, 0, -projection->near, -projection->top);
  crank_vec_float3_unit_self (& projection->cull_plane[3].normal);

  projection->cull_plane[4].dist_origin = projection->near;     // near
  crank_vec_float3_init (& projection->cull_plane[4].normal, 0, 0, -1);

  projection->cull_plane[5].dist_origin = -projection->far;     // far
  crank_vec_float3_init (& projection->cull_plane[5].normal, 0, 0, 1);
}
