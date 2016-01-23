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

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankprojection.h"

#include "crankmaterial.h"

/**
 * SECTION: crankmaterial
 * @title: CrankMaterial
 * @short_description: Material Representation.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * #CrankMaterial holds information to render #CoglPrimitive to framebuffers for
 * deferred shading. (Geometry, color, material parameters)
 *
 * # Geometry pipeline.
 *
 * Crank System maintains 6 buffers for rendering basic scene. (Geometry, color,
 * material for lighting information, Light, Extra light for lights, and last for
 * results)
 *
 * On Geometry buffer, RG is used for depth, BA is used for surface normal.
 */

static const gchar *geom_vert_decl =
"varying float crank_geom_depth_vert;\n"
"varying vec3  crank_geom_normal_vert;\n"

"#define crank_geom_depth_out crank_geom_depth_vert\n"
"#define crank_geom_normal_out crank_geom_normal_vert\n";

static const gchar *geom_vert_replace = ""
// Only write position
"cogl_position_out = cogl_modelview_projection_matrix * cogl_position_in;\n"
"cogl_color_out = vec4(0.0);\n"
"cogl_tex_coord_out[0] = cogl_tex_coord_in;\n"

// Get relative position of vertex.
"vec4 crank_vpos = cogl_modelview_matrix * cogl_position_in;\n"

// Make linear depth.
"crank_geom_depth_out = -crank_vpos.z * crank_vpos.w;\n"
"crank_geom_normal_out =\n"
"    ( cogl_modelview_matrix * \n"
"      vec4 (cogl_normal_in, 0.0) ).xyz; \n";




static const gchar *geom_frag_decl =
"uniform CrankProjection crank_render_projection;\n"

"varying float crank_geom_depth_vert;\n"
"varying vec3  crank_geom_normal_vert;\n"

"float crank_geom_depth_frag;\n"
"vec3  crank_geom_normal_frag;\n"

"#define crank_geom_depth_in crank_geom_depth_vert\n"
"#define crank_geom_normal_in crank_geom_normal_vert\n"
"#define crank_geom_depth_out crank_geom_depth_frag\n"
"#define crank_geom_normal_out crank_geom_normal_frag\n";


static const gchar *geom_frag_replace =
"crank_geom_depth_out = crank_geom_depth_in;\n"
"crank_geom_normal_out = crank_geom_normal_in;\n";

static const gchar *geom_frag_post =
"vec2 normal_result;\n"

"cogl_color_out.b =\n"
"           ((crank_geom_depth_out -\n"
"             crank_projection_get_near (crank_render_projection)) /\n"
"            (crank_projection_get_far (crank_render_projection) -  \n"
"             crank_projection_get_near (crank_render_projection)));\n"

"cogl_color_out.a = fract (cogl_color_out.b * 256.0);\n"
"cogl_color_out.b -= cogl_color_out.a / 256;\n"

"normal_result = normalize (crank_geom_normal_out).xy;\n"
"cogl_color_out.rg = vec2 (0.5) + normal_result * 0.5;";


static CoglSnippet *geom_vert_snippet;
static CoglSnippet *geom_frag_snippet;

//////// List of virtual functions /////////////////////////////////////////////

static void crank_material_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec);

static void crank_material_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec);

static void crank_material_dispose (GObject *object);



//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_COGL_CONTEXT,
  PROP_PIPELINE_GEOM,
  PROP_PIPELINE_COLOR,
  PROP_PIPELINE_MATERIAL,
  PROP_TEXTURE_NORMAL,
  PROP_TEXTURE_COLOR,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankMaterial
{
  GObject _parent;

  CoglPipeline *pipe_geom;
  CoglPipeline *pipe_color;
  CoglPipeline *pipe_mat;
};

G_DEFINE_TYPE (CrankMaterial,
               crank_material,
               G_TYPE_OBJECT);

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_material_init (CrankMaterial *self)
{
}

static void
crank_material_class_init (CrankMaterialClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_material_get_property;
  c_gobject->set_property = crank_material_set_property;
  c_gobject->dispose = crank_material_dispose;

  /**
   * CrankMaterial::cogl-context: (type CoglContext)
   *
   * Cogl context to make pipeline.
   */
  pspecs[PROP_COGL_CONTEXT] =
  g_param_spec_pointer ("cogl-context", "Cogl Context", "Cogl Context to make pipeline.",
                        G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS );

  /**
   * CrankMaterial::pipeline-geom: (type CoglPipeline)
   *
   * Pipeline for geometry.
   */
  pspecs[PROP_PIPELINE_GEOM] =
  g_param_spec_pointer ("pipeline-geom", "Pipeline Geometry",
                        "Pipeline for geometry",
                        G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  /**
   * CrankMaterial::pipeline-color: (type CoglPipeline)
   *
   * Pipeline for color.
   */
  pspecs[PROP_PIPELINE_COLOR] =
  g_param_spec_pointer ("pipeline-color", "Pipeline Color",
                        "Pipeline for color",
                        G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  /**
   * CrankMaterial::pipeline-material: (type CoglPipeline)
   *
   * Pipeline for material.
   */
  pspecs[PROP_PIPELINE_MATERIAL] =
  g_param_spec_pointer ("pipeline-material", "Pipeline Material",
                        "Pipeline for material",
                        G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  /**
   * CrankMaterial::texture-normal: (type CoglTexture)
   *
   * Texture for normal.
   */
  pspecs[PROP_TEXTURE_NORMAL] =
  g_param_spec_pointer ("texture-normal", "Texture Normal",
                        "Texture for normal",
                        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  /**
   * CrankMaterial::texture-color: (type CoglTexture)
   *
   * Texture for color.
   */
  pspecs[PROP_TEXTURE_COLOR] =
  g_param_spec_pointer ("texture-color", "Texture Color",
                        "Texture for color",
                        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  // Snippet

  geom_vert_snippet = cogl_snippet_new (COGL_SNIPPET_HOOK_VERTEX,
                                        geom_vert_decl,
                                        NULL);
  cogl_snippet_set_replace (geom_vert_snippet, geom_vert_replace);


  geom_frag_snippet = cogl_snippet_new (COGL_SNIPPET_HOOK_FRAGMENT,
                                        geom_frag_decl,
                                        geom_frag_post);
  cogl_snippet_set_replace (geom_frag_snippet, geom_frag_replace);
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_material_get_property (GObject    *object,
                             guint       prop_id,
                             GValue     *value,
                             GParamSpec *pspec)
{
  CrankMaterial *material = (CrankMaterial*) object;

  switch (prop_id)
    {
    case PROP_PIPELINE_GEOM:
      g_value_set_pointer (value, material->pipe_geom);
      break;

    case PROP_PIPELINE_COLOR:
      g_value_set_pointer (value, material->pipe_color);
      break;

    case PROP_PIPELINE_MATERIAL:
      g_value_set_pointer (value, material->pipe_mat);
      break;

    case PROP_TEXTURE_NORMAL:
      g_value_set_pointer (value, cogl_pipeline_get_layer_texture (material->pipe_geom, 0));
      break;

    case PROP_TEXTURE_COLOR:
      g_value_set_pointer (value, cogl_pipeline_get_layer_texture (material->pipe_color, 0));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_material_set_property (GObject      *object,
                             guint         prop_id,
                             const GValue *value,
                             GParamSpec   *pspec)
{
  CrankMaterial *material = (CrankMaterial*) object;

  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
        {
          CoglContext *context = (CoglContext*) g_value_get_pointer (value);

          CoglSnippet *snippet_geom_vert;
          CoglSnippet *snippet_geom_frag;
          CoglDepthState depth_state;

          cogl_depth_state_init (& depth_state);

          cogl_depth_state_set_test_enabled (& depth_state, TRUE);
          cogl_depth_state_set_write_enabled (& depth_state, TRUE);

          material->pipe_geom = cogl_pipeline_new (context);
          material->pipe_color = cogl_pipeline_new (context);
          material->pipe_mat = cogl_pipeline_new (context);

          cogl_pipeline_set_depth_state (material->pipe_geom,
                                         & depth_state,
                                         NULL);

          cogl_pipeline_set_depth_state (material->pipe_color,
                                         & depth_state,
                                         NULL);

          cogl_pipeline_set_depth_state (material->pipe_mat,
                                         & depth_state,
                                         NULL);

          // Disable alpha blend, as alpha value also contains parameter value.
          cogl_pipeline_set_blend (material->pipe_geom,
                                   "RGBA = ADD(SRC_COLOR, 0)",
                                   NULL);

          cogl_pipeline_set_blend (material->pipe_color,
                                   "RGBA = ADD(SRC_COLOR, 0)",
                                   NULL);

          cogl_pipeline_set_blend (material->pipe_mat,
                                   "RGBA = ADD(SRC_COLOR, 0)",
                                   NULL);

          cogl_pipeline_set_layer_null_texture (material->pipe_geom, 0,
                                                COGL_TEXTURE_TYPE_2D);

          cogl_pipeline_set_layer_null_texture (material->pipe_color, 0,
                                                COGL_TEXTURE_TYPE_2D);

          cogl_pipeline_add_snippet (material->pipe_geom, geom_vert_snippet);
          cogl_pipeline_add_snippet (material->pipe_geom, geom_frag_snippet);
          cogl_pipeline_add_snippet (material->pipe_geom,
                                     crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_FRAGMENT));

        }
      break;

    case PROP_TEXTURE_NORMAL:
        {
          CoglTexture *texture = (CoglTexture*) g_value_get_pointer (value);
          crank_material_set_texture_normal (material, texture);
        }
      break;

    case PROP_TEXTURE_COLOR:
        {
          CoglTexture *texture = (CoglTexture*) g_value_get_pointer (value);
          crank_material_set_texture_color (material, texture);
        }
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }

}


static void
crank_material_dispose (GObject *object)
{
  CrankMaterial *material = (CrankMaterial*) object;
  cogl_object_unref (material->pipe_geom);
  cogl_object_unref (material->pipe_color);
  cogl_object_unref (material->pipe_mat);

  material->pipe_geom = NULL;
  material->pipe_color = NULL;
  material->pipe_mat = NULL;
}

//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_material_new:
 * @cogl_context: A Cogl context
 *
 * Constructs a material from @Cogl_context.
 *
 * Returns: (transfer full): Newly constructed material.
 */
CrankMaterial*
crank_material_new (CoglContext *cogl_context)
{
  CrankMaterial *material = g_object_new (CRANK_TYPE_MATERIAL,
                                          "cogl-context", cogl_context,
                                          NULL);

  return material;
}

//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_material_get_pipeline_geom:
 * @material: A Material
 *
 * Gets a pipeline for rendering for geometry buffer.
 *
 * Returns: (transfer none): A Pipeline
 */
CoglPipeline*
crank_material_get_pipeline_geom (CrankMaterial *material)
{
  return material->pipe_geom;
}

/**
 * crank_material_get_pipeline_color:
 * @material: A Material
 *
 * Gets a pipeline for rendering for color buffer.
 *
 * Returns: (transfer none): A Pipeline
 */
CoglPipeline*
crank_material_get_pipeline_color (CrankMaterial *material)
{
  return material->pipe_color;
}

/**
 * crank_material_get_pipeline_material:
 * @material: A Material
 *
 * Gets a pipeline for rendering for material buffer.
 *
 * Returns: (transfer none): A Pipeline
 */
CoglPipeline*
crank_material_get_pipeline_material (CrankMaterial *material)
{
  return material->pipe_mat;
}




/**
 * crank_material_get_texture_normal:
 * @material: A Material.
 *
 * Get normal texture for normal mapping.
 *
 * Returns: (transfer none): Normal texture.
 */
CoglTexture*
crank_material_get_texture_normal (CrankMaterial *material)
{
  return cogl_pipeline_get_layer_texture (material->pipe_geom, 0);
}

/**
 * crank_material_set_texture_normal:
 * @material: A Material.
 * @texture: (transfer none): Normal texture.
 *
 * sets normal texture for normal mapping.
 */
void
crank_material_set_texture_normal (CrankMaterial *material,
                                   CoglTexture *texture)
{
  cogl_pipeline_set_layer_texture (material->pipe_geom, 0, texture);

  g_object_notify_by_pspec ((GObject*)material, pspecs[PROP_TEXTURE_NORMAL]);
}



/**
 * crank_material_get_texture_color:
 * @material: A Material.
 *
 * Get color texture for coloring.
 *
 * Returns: (transfer none): Color texture.
 */
CoglTexture*
crank_material_get_texture_color (CrankMaterial *material)
{
  return cogl_pipeline_get_layer_texture (material->pipe_color, 0);
}

/**
 * crank_material_set_texture_color:
 * @material: A Material.
 * @texture: (transfer none): Color texture.
 *
 * Sets color texture for coloring.
 */
void
crank_material_set_texture_color (CrankMaterial *material,
                                  CoglTexture   *texture)
{
  cogl_pipeline_set_layer_texture (material->pipe_color, 0, texture);

  g_object_notify_by_pspec ((GObject*)material, pspecs[PROP_TEXTURE_COLOR]);
}
