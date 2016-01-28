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

#include "cranklightable.h"
#include "cranklightablearanged.h"

//////// GLSL Snippet code. ////////////////////////////////////////////////////

static CoglUserDataKey key_template;

static CoglSnippet *vert_snippet;
static gchar *vert_decl =
"uniform CrankProjection crank_render_projection;\n"
"varying vec3            crank_render_tex_coord_vert;\n"
"varying vec3            crank_frag_near;\n"
"varying vec3            crank_frag_far;\n"

"#define crank_render_tex_coord_out crank_render_tex_coord_vert\n";

static gchar *vert_post =
"crank_render_tex_coord_out.xy = cogl_position_out.xy +\n"
"                                vec2 (cogl_position_out.w);\n"
"crank_render_tex_coord_out.z = cogl_position_out.w * 2;"

"float nf = mix (1,\n"
"                crank_projection_get_far (crank_render_projection) /\n"
"                crank_projection_get_near (crank_render_projection),\n"
"                crank_render_projection.proj_type);\n"

"vec2 base_lb = vec2 (crank_projection_get_left (crank_render_projection),\n"
"                     crank_projection_get_bottom (crank_render_projection));\n"
"vec2 base_rt = vec2 (crank_projection_get_right (crank_render_projection),\n"
"                     crank_projection_get_top (crank_render_projection));\n"
"vec2 base_xy = mix (base_lb, base_rt, crank_render_tex_coord_out.xy);\n"

"crank_frag_near = vec3 (base_xy,\n"
"                        -crank_projection_get_near (crank_render_projection));\n"

"crank_frag_far = vec3 (base_xy * nf,\n"
"                       -crank_projection_get_far (crank_render_projection));\n";


static gchar *frag_decl =
"uniform CrankProjection crank_render_projection;\n"
"varying vec3 crank_render_tex_coord_vert;\n"
"varying vec3 crank_frag_near;\n"
"varying vec3 crank_frag_far;\n"
"uniform sampler2D  crank_render_geom;\n"
"uniform sampler2D  crank_render_color;\n"
"uniform vec3 crank_lightable_position;\n"
"float crank_frag_depth;\n"
"vec3 crank_frag_normal;\n"
"vec3 crank_frag_pos;\n";

static gchar *frag_post =
"vec2 tc = crank_render_tex_coord_vert.xy / crank_render_tex_coord_vert.z;\n"
"vec4  crank_geom_value = texture2D (crank_render_geom, tc);\n"
"crank_geom_unpack (crank_geom_value, crank_frag_normal, crank_frag_depth);\n"

"crank_frag_pos = mix (crank_frag_near, crank_frag_far, crank_frag_depth);\n"


"cogl_color_out = vec4 (crank_frag_near, 1);"
;

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
crank_lightable_a_ranged_get_visible_radius (CrankLightable *lightable);

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
  CoglPrimitive *bounding_volume;
} CrankLightableARangedTemp;

struct _CrankLightableARanged
{
  CrankLightable _parent;

  gfloat  radius;
  gfloat  intensity;

  CoglContext  *cogl_context;
  CoglPipeline *pipe_line;
  CoglPrimitive *bound_volume;

  gint        uniform_render_projection[2];
  gint        uniform_lightable_position;
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

  c_lightable->render = crank_lightable_a_ranged_render;
  c_lightable->get_visible_radius = crank_lightable_a_ranged_get_visible_radius;
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
      CoglSnippet *snippet_frag;

      template = g_new (CrankLightableARangedTemp, 1);

      template->pipeline = cogl_pipeline_new (lightable->cogl_context);
      cogl_pipeline_set_cull_face_mode (template->pipeline,
                                        COGL_PIPELINE_CULL_FACE_MODE_FRONT);
      template->bounding_volume = crank_make_mesh_sphere_uv_p3n3 (lightable->cogl_context, 10, 10);

      vert_snippet = cogl_snippet_new (COGL_SNIPPET_HOOK_VERTEX,
                                       vert_decl,
                                       vert_post);

      snippet_frag = cogl_snippet_new (COGL_SNIPPET_HOOK_FRAGMENT,
                                       frag_decl,
                                       frag_post);

      cogl_pipeline_set_layer_null_texture (template->pipeline, 0, COGL_TEXTURE_TYPE_2D);
      cogl_pipeline_set_layer_null_texture (template->pipeline, 1, COGL_TEXTURE_TYPE_2D);

      cogl_pipeline_add_snippet (template->pipeline,
                                 crank_material_get_snippet_geom_unpack ());
      cogl_pipeline_add_snippet (template->pipeline,
                                 crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_VERTEX));
      cogl_pipeline_add_snippet (template->pipeline,
                                 crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_FRAGMENT));

      cogl_pipeline_add_snippet (template->pipeline, vert_snippet);
      cogl_pipeline_add_snippet (template->pipeline, snippet_frag);

      cogl_object_unref (snippet_frag);

      cogl_object_set_user_data ((CoglObject*) lightable->cogl_context,
                                 &key_template,
                                 template,
                                 crank_lightable_a_ranged_temp_free);
    }

  lightable->pipe_line = template->pipeline;
  lightable->bound_volume = template->bounding_volume;

  crank_projection_get_uniform_locations (lightable->pipe_line,
                                         "crank_render_projection",
                                         lightable->uniform_render_projection);
  lightable->uniform_lightable_position =
  cogl_pipeline_get_uniform_location (lightable->pipe_line,
                                      "crank_lightable_position");
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
crank_lightable_a_ranged_get_visible_radius (CrankLightable *lightable)
{
  CrankLightableARanged *self = (CrankLightableARanged*)lightable;

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

  position->mscl *= self->radius;
  crank_trans3_to_matrix_transpose (position, & mv_matrix);

  cogl_framebuffer_set_modelview_matrix (framebuffer, (CoglMatrix*)&mv_matrix);

  cogl_pipeline_set_layer_texture (self->pipe_line, 0, tex_geom);
  cogl_pipeline_set_layer_texture (self->pipe_line, 1, tex_color);

  crank_projection_set_uniform_value (projection,
                                      self->pipe_line,
                                      self->uniform_render_projection);

  cogl_pipeline_set_uniform_float (self->pipe_line,
                                   self->uniform_lightable_position,
                                   3, 1, (gfloat*) & position->mtrans);


  //cogl_primitive_draw (self->bound_volume, framebuffer, self->pipe_line);
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
