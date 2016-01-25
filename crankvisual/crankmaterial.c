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

static CoglUserDataKey  key_template;


/*
 * crank_geom_pack: (GLSL):
 * @normal: Normal value.
 * @depth: Depth value.
 *
 * Generate texel value of geometry buffer.
 *
 * Note: Normal value should be processed per fragment.
 *
 * Returns: texel value for geometry buffer.
 */
static CoglSnippet *geom_pack = NULL;
static const gchar *geom_pack_decl =
"vec4 crank_geom_pack (vec3  normal,\n"
"                      float depth)\n"
"{\n"
"  vec4 texel;\n"


   // Pack normal into RG channel.
"  texel.rg = normalize (normal).xy * 0.5 + vec2 (0.5);\n"


   // Pack depth into BA channel.
"  texel.a = fract (depth * 256);\n"
"  texel.b = depth - (texel.a / 256);\n"

"  return texel;\n"
"}\n";


/*
 * crank_geom_unpack: (GLSL):
 * @normal: Normal value.
 * @depth: Depth value.
 *
 * Generate texel value of geometry buffer.
 *
 * Note: Normal value should be processed per fragment.
 *
 * Returns: texel value for geometry buffer.
 */
static CoglSnippet *geom_unpack = NULL;
static const gchar *geom_unpack_decl =
"vec4 crank_geom_unpack (vec4      texel,"
"                        out vec3  normal,"
"                        out float depth)"
"{"

   // Unpack normal from RG channel.
"  normal.xy = texel.xy * 2.0 - vec2 (1.0);"
"  normal.z = sqrt (1 - dot (normal.xy, normal.xy));"

   // Unpack depth into BA channel.
"  depth = dot ( vec2 (1, 1/256), texel.ba);"
"}";



static CoglSnippet *geom_vert_snippet;
static const gchar *geom_vert_decl =
"uniform CrankProjection crank_render_projection;\n"
"varying float crank_frag_depth_vert;\n"
"varying vec3  crank_frag_normal_vert;\n"

"#define crank_frag_depth_out crank_frag_depth_vert\n"
"#define crank_frag_normal_out crank_frag_normal_vert\n";

static const gchar *geom_vert_post =
"vec4 crank_position_cam = cogl_modelview_matrix * cogl_position_in;\n"


"crank_frag_depth_out = -crank_position_cam.z / crank_position_cam.w;\n"

"crank_frag_depth_out = \n"
"  (crank_frag_depth_out -\n"
"   crank_projection_get_near (crank_render_projection)) /\n"
"  (crank_projection_get_far (crank_render_projection) -\n"
"   crank_projection_get_near (crank_render_projection));\n"

"crank_frag_normal_out =\n"
"    ( cogl_modelview_matrix * \n"
"      vec4 (cogl_normal_in, 0.0) ).xyz; \n";





static CoglSnippet *geom_frag_snippet;
static const gchar *geom_frag_decl =
"uniform CrankProjection crank_render_projection;\n"

"varying float crank_frag_depth_vert;\n"
"varying vec3  crank_frag_normal_vert;\n"

"float crank_frag_depth_frag;\n"
"vec3  crank_frag_normal_frag;\n"

"#define crank_frag_depth_in crank_frag_depth_vert\n"
"#define crank_frag_normal_in crank_frag_normal_vert\n"
"#define crank_frag_depth_out crank_frag_depth_frag\n"
"#define crank_frag_normal_out crank_frag_normal_frag\n";

static const gchar *geom_frag_post =
"crank_frag_depth_out = crank_frag_depth_in;\n"
"crank_frag_normal_out = crank_frag_normal_in;\n"

"cogl_color_out = crank_geom_pack (crank_frag_normal_out, crank_frag_depth_out);"
;


//////// List of virtual functions /////////////////////////////////////////////

static void crank_material_constructed (GObject *object);

static void crank_material_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec);

static void crank_material_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec);

static void crank_material_dispose (GObject *object);



//////// Private functions /////////////////////////////////////////////////////

static void crank_material_temp_free (gpointer data);


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

typedef struct _CrankMaterialTemp
{
  CoglPipeline *pipe_base;
  CoglPipeline *pipe_geom;
  CoglPipeline *pipe_color;
  CoglPipeline *pipe_mat;
} CrankMaterialTemp;


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

  c_gobject->constructed = crank_material_constructed;
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
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_material_constructed (GObject *object)
{
  GObjectClass *pc_gobject;

  CrankMaterial      *material;
  CrankMaterialTemp  *template;

  CoglContext        *cogl_context;

  GError             *merr = NULL;

  pc_gobject = (GObjectClass*) crank_material_parent_class;
  pc_gobject->constructed (object);

  material = (CrankMaterial*) object;
  cogl_context = g_object_get_data (object, "cogl-context");
  template = cogl_object_get_user_data ((CoglObject*)cogl_context, &key_template);

  if (template == NULL)
    {
      CoglSnippet *snippet_geom_vert;
      CoglSnippet *snippet_geom_frag;
      CoglDepthState depth_state;

      template = g_new (CrankMaterialTemp, 1);

      cogl_depth_state_init (& depth_state);

      cogl_depth_state_set_test_enabled (& depth_state, TRUE);
      cogl_depth_state_set_write_enabled (& depth_state, TRUE);

      template->pipe_base=  cogl_pipeline_new (cogl_context);

      cogl_pipeline_set_cull_face_mode (template->pipe_base,
                                        COGL_PIPELINE_CULL_FACE_MODE_FRONT);

      cogl_pipeline_set_depth_state (template->pipe_base, &depth_state, &merr);
      if (merr != NULL)
        g_error ("CrankMaterial: Fail to set depth state: %s", merr->message);

      cogl_pipeline_set_blend (template->pipe_base,
                               "RGBA = ADD(SRC_COLOR, 0)",
                               &merr);
      if (merr != NULL)
        g_error ("CrankMaterial: Fail to set blend string: %s", merr->message);


      template->pipe_geom = cogl_pipeline_copy (template->pipe_base);
      template->pipe_color = cogl_pipeline_copy (template->pipe_base);
      template->pipe_mat = cogl_pipeline_copy (template->pipe_base);



      // Snippet

      geom_pack = cogl_snippet_new (COGL_SNIPPET_HOOK_FRAGMENT_GLOBALS,
                                    geom_pack_decl,
                                    NULL);

      geom_vert_snippet = cogl_snippet_new (COGL_SNIPPET_HOOK_VERTEX,
                                            geom_vert_decl,
                                            geom_vert_post);


      geom_frag_snippet = cogl_snippet_new (COGL_SNIPPET_HOOK_FRAGMENT,
                                            geom_frag_decl,
                                            geom_frag_post);


      cogl_pipeline_add_snippet (template->pipe_geom, geom_pack);
      cogl_pipeline_add_snippet (template->pipe_geom,
                                 crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_VERTEX));
      cogl_pipeline_add_snippet (template->pipe_geom,
                                 crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_FRAGMENT));
      cogl_pipeline_add_snippet (template->pipe_geom, geom_vert_snippet);
      cogl_pipeline_add_snippet (template->pipe_geom, geom_frag_snippet);

      cogl_object_set_user_data ((CoglObject*)cogl_context,
                                 &key_template,
                                 template,
                                 crank_material_temp_free);
    }

  material->pipe_geom = cogl_pipeline_copy (template->pipe_geom);
  material->pipe_color = cogl_pipeline_copy (template->pipe_color);
  material->pipe_mat = cogl_pipeline_copy (template->pipe_mat);

  cogl_pipeline_set_layer_null_texture (material->pipe_geom, 0, COGL_TEXTURE_TYPE_2D);
}


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
      g_object_set_data (object, "cogl-context", g_value_get_pointer (value));
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



//////// Private functions /////////////////////////////////////////////////////

static void
crank_material_temp_free (gpointer data)
{
  CrankMaterialTemp *template = (CrankMaterialTemp*) data;

  cogl_object_unref (template->pipe_geom);
  cogl_object_unref (template->pipe_color);
  cogl_object_unref (template->pipe_mat);

  g_free (template);
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
