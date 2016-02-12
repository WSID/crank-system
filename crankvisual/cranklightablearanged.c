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
 * SECTION: cranklightablearanged
 * @title: CrankLightableARanged
 * @short_description: Ranged ambient light
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * This represents ambient light with limited range.
 *
 * This light lits fragments regrardless of its angle, but just distance from
 * light.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include <cogl/cogl2-experimental.h>

#include "crankshape.h"

#include "crankprojection.h"
#include "crankmaterial.h"
#include "crankmeshutil.h"

#include "crankvisible.h"
#include "cranklightable.h"
#include "cranklightablearanged.h"

//////// GLSL Snippet code. ////////////////////////////////////////////////////

static CoglUserDataKey key_template;


static CoglSnippet *v_snippet;
static CoglSnippet *f_snippet;


static gchar* v_decl =
"uniform CrankProjection crank_render_proj;\n"
"varying vec2 crank_frag_coord;\n"
"varying vec3 crank_frag_near;\n"
"varying vec3 crank_frag_far;\n"
;

static gchar* v_replace =
// Write vertex position for screen quad.
"cogl_position_out = vec4 (cogl_position_in.xy, -1, 1);\n"

// Write fragment coordination.
"crank_frag_coord = cogl_position_out.xy * 0.5 + vec2 (0.5);\n"

// Write near point and far point position of fragment coordination.
"crank_projection_get_nf_points (crank_render_proj,\n"
"                                crank_frag_coord,\n"
"                                crank_frag_near,\n"
"                                crank_frag_far);\n"
;

static gchar* f_decl =
// G-Buffer sampler.
"uniform sampler2D crank_geom_sampler;\n"
"uniform sampler2D crank_color_sampler;\n"

// Lightable info
"uniform vec3  crank_lightable_pos;\n"
"uniform vec3  crank_lightable_primary_color;\n"
"uniform float crank_lightable_intensity;\n"
"uniform float crank_lightable_radius;\n"

// Fragment info that available by vertices.
"varying vec2  crank_frag_coord;\n"
"varying vec3  crank_frag_near;\n"
"varying vec3  crank_frag_far;\n"

// Fragment info that available by G-Buffers
"vec3 crank_frag_nor;\n"
"float crank_frag_depth;\n"
"vec3 crank_frag_pos;\n"
"vec3 crank_frag_color;\n"
;

static gchar* f_replace =
// Fetch texel value from G-Buffers
"vec4 layer_geom_value = texture2D (crank_geom_sampler, crank_frag_coord);\n"
"vec4 layer_color_value = texture2D (crank_color_sampler, crank_frag_coord);\n"

// Unpack Geometry buffer content.
"crank_geom_unpack (layer_geom_value, crank_frag_nor, crank_frag_depth);\n"

// Set Fragment information.
"crank_frag_pos = mix (crank_frag_near, crank_frag_far, crank_frag_depth);\n"
"crank_frag_color = layer_color_value.xyz;\n"

// Light calculation
"vec3  pos_diff = crank_frag_pos - crank_lightable_pos;\n"
"float distance = length (pos_diff);\n"
"float strength = max (crank_lightable_radius - distance, 0) /\n"
"                 crank_lightable_radius *\n"
"                 crank_lightable_intensity;\n"


"cogl_color_out = vec4 (crank_lightable_primary_color *\n"
"                       crank_frag_color *\n"
"                       strength, 1);\n"

;


static CoglVertexP2 screen_quadv[4] = {
    {-1, -1}, {1, -1}, {1, 1}, {-1, 1}
};

//////// List of virtual functions /////////////////////////////////////////////

static void
crank_lightable_a_ranged_constructed (GObject *object);

static void
crank_lightable_a_ranged_get_property (GObject    *object,
                                       guint       prop_id,
                                       GValue     *value,
                                       GParamSpec *pspec);

static void
crank_lightable_a_ranged_set_property (GObject      *objet,
                                       guint         prop_id,
                                       const GValue *value,
                                       GParamSpec   *pspec);

static void
crank_lightable_a_ranged_dispose (GObject *object);


static gfloat
crank_lightable_a_ranged_get_visible_radius (CrankVisible *visible);

static void
crank_lightable_a_ranged_render (CrankLightable  *lightable,
                                 CrankTrans3     *position,
                                 CrankProjection *projection,
                                 CoglTexture     *tex_geom,
                                 CoglTexture     *tex_color,
                                 CoglTexture     *tex_mater,
                                 const gfloat     lscale,
                                 CoglFramebuffer *framebuffer);



//////// Private functions /////////////////////////////////////////////////////

static void
crank_lightable_a_ranged_temp_free (gpointer data);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_COGL_CONTEXT,
  PROP_RADIUS,
  PROP_INTENSITY,

  PROP_COUNTS
};

GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definitions //////////////////////////////////////////////////////

typedef struct _CrankLightableARangedTemp
{
  CoglPipeline *pipeline;
  CoglPipeline *pipeline_depth;
  CoglPrimitive *bounding_volume;
  CoglPrimitive *screen_quad;
} CrankLightableARangedTemp;

struct _CrankLightableARanged
{
  CrankLightable _parent;

  gfloat  radius;
  gfloat  intensity;

  CoglContext  *cogl_context;
  CoglPipeline *pipe_line;
  CoglPipeline *pipeline_depth;
  CoglPrimitive *bound_volume;
  CoglPrimitive *screen_quad;

  gint        uniform_render_proj[2];
  gint        uniform_geom_sampler;
  gint        uniform_color_sampler;
  gint        uniform_lightable_pos;
  gint        uniform_lightable_primary_color;
  gint        uniform_lightable_intensity;
  gint        uniform_lightable_radius;
};

G_DEFINE_TYPE (CrankLightableARanged,
               crank_lightable_a_ranged,
               CRANK_TYPE_LIGHTABLE);



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_lightable_a_ranged_init (CrankLightableARanged *lightable)
{
}

static void
crank_lightable_a_ranged_class_init (CrankLightableARangedClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankVisibleClass *c_visible = CRANK_VISIBLE_CLASS (c);
  CrankLightableClass *c_lightable = CRANK_LIGHTABLE_CLASS (c);

  c_gobject->constructed = crank_lightable_a_ranged_constructed;
  c_gobject->get_property = crank_lightable_a_ranged_get_property;
  c_gobject->set_property = crank_lightable_a_ranged_set_property;
  c_gobject->dispose = crank_lightable_a_ranged_dispose;

  /**
   * CrankLightableARanged:cogl-context: (type CoglContext)
   *
   */
  pspecs[PROP_COGL_CONTEXT] = g_param_spec_pointer ("cogl-context", "CoglContext",
                                                    "A CoglContext to initialize with.",
                                                    G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_RADIUS] = g_param_spec_float ("radius", "Radius",
                                            "Radius to lit.",
                                            0, G_MAXFLOAT, 1,
                                            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_INTENSITY] = g_param_spec_float ("intensity", "Intensity",
                                               "Intensity to light.",
                                               0, G_MAXFLOAT, 1,
                                               G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  c_visible->get_visible_radius = crank_lightable_a_ranged_get_visible_radius;


  c_lightable->render = crank_lightable_a_ranged_render;
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_lightable_a_ranged_constructed (GObject *object)
{
  GObjectClass *pc_gobject;

  CrankLightableARanged *lightable;
  CrankLightableARangedTemp *template;
  pc_gobject = (GObjectClass*)crank_lightable_a_ranged_parent_class;
  pc_gobject->constructed (object);

  lightable = (CrankLightableARanged*) object;

  if (lightable->cogl_context == NULL)
    g_error ("CrankLightableARanged: Requires cogl-context at construction.");

  template = cogl_object_get_user_data ((CoglObject*) lightable->cogl_context,
                                        &key_template);

  if (template == NULL)
    {
      CoglDepthState dstate;
      CoglDepthState dstate_depth;

      template = g_new (CrankLightableARangedTemp, 1);

      template->pipeline = cogl_pipeline_new (lightable->cogl_context);
      template->pipeline_depth = cogl_pipeline_new (lightable->cogl_context);

      template->bounding_volume = crank_make_mesh_sphere_uv_p3 (lightable->cogl_context, 6, 4);

      template->screen_quad = cogl_primitive_new_p2 (lightable->cogl_context,
                                                     COGL_VERTICES_MODE_TRIANGLE_FAN,
                                                     4, screen_quadv);


      cogl_pipeline_set_alpha_test_function (template->pipeline, COGL_PIPELINE_ALPHA_FUNC_ALWAYS, 0);
      cogl_pipeline_set_blend (template->pipeline, "RGBA = ADD (SRC_COLOR, DST_COLOR)", NULL);

      cogl_depth_state_init (&dstate);
      cogl_depth_state_set_test_enabled (&dstate, TRUE);
      cogl_depth_state_set_write_enabled (&dstate, FALSE);
      cogl_depth_state_set_test_function (&dstate, COGL_DEPTH_TEST_FUNCTION_LESS);
      cogl_pipeline_set_depth_state (template->pipeline, &dstate, NULL);

      cogl_pipeline_set_layer_null_texture (template->pipeline, 0, COGL_TEXTURE_TYPE_2D);
      cogl_pipeline_set_layer_null_texture (template->pipeline, 1, COGL_TEXTURE_TYPE_2D);



      cogl_pipeline_set_alpha_test_function (template->pipeline_depth, COGL_PIPELINE_ALPHA_FUNC_ALWAYS, 0);

      cogl_depth_state_init (&dstate_depth);
      cogl_depth_state_set_test_enabled (&dstate_depth, FALSE);
      cogl_depth_state_set_write_enabled (&dstate_depth, TRUE);
      cogl_pipeline_set_depth_state (template->pipeline_depth, &dstate_depth, NULL);
      cogl_pipeline_set_color4f (template->pipeline_depth, 1, 0, 0, 1);


      // Snippet construction
      v_snippet = cogl_snippet_new (COGL_SNIPPET_HOOK_VERTEX, v_decl, NULL);
      cogl_snippet_set_replace (v_snippet, v_replace);

      f_snippet = cogl_snippet_new (COGL_SNIPPET_HOOK_FRAGMENT, f_decl, NULL);
      cogl_snippet_set_replace (f_snippet, f_replace);

      cogl_pipeline_add_snippet (template->pipeline,
                                 crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_VERTEX));

      cogl_pipeline_add_snippet (template->pipeline,
                                 crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_FRAGMENT));

      cogl_pipeline_add_snippet (template->pipeline,
                                 crank_material_get_snippet_geom_unpack ());

      cogl_pipeline_add_snippet (template->pipeline, v_snippet);
      cogl_pipeline_add_snippet (template->pipeline, f_snippet);

      cogl_object_set_user_data ((CoglObject*) lightable->cogl_context,
                                 &key_template,
                                 template,
                                 crank_lightable_a_ranged_temp_free);
    }

  lightable->pipe_line = template->pipeline;
  lightable->pipeline_depth = template->pipeline_depth;
  lightable->bound_volume = template->bounding_volume;
  lightable->screen_quad = template->screen_quad;

  crank_projection_get_uniform_locations (lightable->pipe_line,
                                         "crank_render_proj",
                                         lightable->uniform_render_proj);

  lightable->uniform_geom_sampler =
  cogl_pipeline_get_uniform_location (lightable->pipe_line,
                                      "crank_geom_sampler");

  lightable->uniform_color_sampler =
  cogl_pipeline_get_uniform_location (lightable->pipe_line,
                                      "crank_color_sampler");

  lightable->uniform_lightable_pos =
  cogl_pipeline_get_uniform_location (lightable->pipe_line,
                                      "crank_lightable_pos");


  lightable->uniform_lightable_primary_color =
  cogl_pipeline_get_uniform_location (lightable->pipe_line,
                                      "crank_lightable_primary_color");

  lightable->uniform_lightable_intensity =
  cogl_pipeline_get_uniform_location (lightable->pipe_line,
                                      "crank_lightable_intensity");

  lightable->uniform_lightable_radius =
  cogl_pipeline_get_uniform_location (lightable->pipe_line,
                                      "crank_lightable_radius");
}

static void
crank_lightable_a_ranged_get_property (GObject    *object,
                                       guint       prop_id,
                                       GValue     *value,
                                       GParamSpec *pspec)
{
  CrankLightableARanged *lightable = (CrankLightableARanged*) object;

  switch (prop_id)
    {
    case PROP_RADIUS:
      g_value_set_float (value, crank_lightable_a_ranged_get_radius (lightable));
      break;

    case PROP_INTENSITY:
      g_value_set_float (value, crank_lightable_a_ranged_get_intensity (lightable));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_lightable_a_ranged_set_property (GObject      *object,
                                       guint         prop_id,
                                       const GValue *value,
                                       GParamSpec   *pspec)
{
  CrankLightableARanged *lightable = (CrankLightableARanged*) object;

  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
      lightable->cogl_context = (CoglContext*) g_value_get_pointer (value);
      break;

    case PROP_RADIUS:
      crank_lightable_a_ranged_set_radius (lightable, g_value_get_float (value));
      break;

    case PROP_INTENSITY:
      crank_lightable_a_ranged_set_intensity (lightable, g_value_get_float (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_lightable_a_ranged_dispose (GObject *object)
{
  CrankLightableARanged *lightable;
  GObjectClass *pc_gobject;
  pc_gobject = (GObjectClass*)crank_lightable_a_ranged_parent_class;

  lightable->cogl_context = NULL;
  cogl_object_unref (lightable->pipe_line);
  cogl_object_unref (lightable->bound_volume);

  pc_gobject->dispose (object);
}




//////// CrankLightable ////////////////////////////////////////////////////////

static gfloat
crank_lightable_a_ranged_get_visible_radius (CrankVisible *visible)
{
  CrankLightableARanged *self = (CrankLightableARanged*)visible;

  return self->radius;
}

static void
crank_lightable_a_ranged_render (CrankLightable  *lightable,
                                 CrankTrans3     *position,
                                 CrankProjection *projection,
                                 CoglTexture     *tex_geom,
                                 CoglTexture     *tex_color,
                                 CoglTexture     *tex_mater,
                                 const gfloat     lscale,
                                 CoglFramebuffer *framebuffer)
{
  CrankLightableARanged *self = (CrankLightableARanged*) lightable;

  CrankMatFloat4 mv_matrix;
  CrankVecFloat3 primary_color;

  position->mscl *= self->radius;
  crank_trans3_to_matrix_transpose (position, & mv_matrix);

  cogl_framebuffer_set_modelview_matrix (framebuffer, (CoglMatrix*)&mv_matrix);

  // Draw depth.
  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH, 1, 1, 1, 1);
  cogl_framebuffer_set_color_mask (framebuffer, COGL_COLOR_MASK_NONE);
  cogl_primitive_draw (self->bound_volume, framebuffer, self->pipeline_depth);


  // Draw lights.
  cogl_framebuffer_set_color_mask (framebuffer, COGL_COLOR_MASK_ALL);

  cogl_pipeline_set_layer_texture (self->pipe_line, 0, tex_geom);
  cogl_pipeline_set_layer_texture (self->pipe_line, 1, tex_color);

  crank_projection_set_uniform_value (projection,
                                      self->pipe_line,
                                      self->uniform_render_proj);

  cogl_pipeline_set_uniform_float (self->pipe_line,
                                   self->uniform_lightable_pos,
                                   3, 1, (gfloat*) & position->mtrans);

  cogl_pipeline_set_uniform_1i (self->pipe_line,
                                self->uniform_geom_sampler,
                                0);

  cogl_pipeline_set_uniform_1i (self->pipe_line,
                                 self->uniform_color_sampler,
                                 1);

  crank_lightable_get_primary_color (lightable, &primary_color);

  cogl_pipeline_set_uniform_float (self->pipe_line,
                                   self->uniform_lightable_primary_color,
                                   3, 1, (gfloat*) & primary_color);

  cogl_pipeline_set_uniform_1f (self->pipe_line,
                                self->uniform_lightable_radius,
                                position->mscl);

  cogl_pipeline_set_uniform_1f (self->pipe_line,
                                self->uniform_lightable_intensity,
                                self->intensity);

  cogl_primitive_draw (self->screen_quad, framebuffer, self->pipe_line);
}




//////// Private functions /////////////////////////////////////////////////////

static void
crank_lightable_a_ranged_temp_free (gpointer data)
{
  CrankLightableARangedTemp *template = (CrankLightableARangedTemp*) data;

  cogl_object_unref (template->pipeline);
  cogl_object_unref (template->bounding_volume);

  g_free (data);
}


//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_lightable_a_ranged_new:
 * @cogl_context: A CoglContext.
 * @primary_color: Primary color of this light.
 * @radius: A Radius.
 * @intensity: A Intensity.
 *
 * Constructs a lightable.
 *
 * Returns: (transfer full): Newly constructed lightable.
 */
CrankLightableARanged*
crank_lightable_a_ranged_new (CoglContext          *cogl_context,
                              const CrankVecFloat3 *primary_color,
                              const gfloat          radius,
                              const gfloat          intensity)
{
  return (CrankLightableARanged*)
          g_object_new (CRANK_TYPE_LIGHTABLE_A_RANGED,
                        "cogl-context", cogl_context,
                        "primary-color", primary_color,
                        "radius", radius,
                        "intensity", intensity,
                        NULL);
}


//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_lightable_a_randed_get_radius:
 * @lightable: A Lightable.
 *
 * Gets lightable's radius.
 *
 * Returns: Radius of lightable.
 */
gfloat
crank_lightable_a_ranged_get_radius (CrankLightableARanged *lightable)
{
  return lightable->radius;
}

/**
 * crank_lightable_a_ranged_set_radius:
 * @lightable: A Lightable.
 * @radius: Radius of lightable.
 *
 * Sets lightable's radius.
 *
 * This operation notifies CrankLightable:visible-radius, as well as
 * CrankLightableARanged:radius.
 */
void
crank_lightable_a_ranged_set_radius (CrankLightableARanged *lightable,
                                     const gfloat           radius)
{
  lightable->radius = radius;

  g_object_notify ((GObject*)lightable, "visible-radius");
  g_object_notify_by_pspec ((GObject*)lightable, pspecs[PROP_RADIUS]);
}

/**
 * crank_lightable_a_ranged_get_intensity:
 * @lightable: A Lightable.
 *
 * Gets lightable's intensity.
 *
 * Returns: intensity of lightable.
 */
gfloat
crank_lightable_a_ranged_get_intensity (CrankLightableARanged *lightable)
{
  return lightable->intensity;
}

/**
 * crank_lightable_a_ranged_set_intensity:
 * @lightable: A Lightable.
 * @intensity: Intensity of lightable.
 *
 * Sets lightable's intensity. Larger value makes lightable to be more shiny.
 */
void
crank_lightable_a_ranged_set_intensity (CrankLightableARanged *lightable,
                                        const gfloat           intensity)
{
  lightable->intensity = intensity;
}
