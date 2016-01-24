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
#include "crankmeshutil.h"

#include "cranklightable.h"
#include "cranklightablearanged.h"

//////// GLSL Snippet code. ////////////////////////////////////////////////////


static gchar *vert_decl =
"uniform CrankProjection crank_deferr_proj;\n"
"varying vec3 crank_deferr_near;\n"
"varying vec3 crank_deferr_far;";

static gchar *vert_replace =
"cogl_position_out = cogl_modelview_projection_matrix * cogl_position_in;\n"
"cogl_tex_coord0_out = vec4 (0, 0, 0, 1);\n"
"cogl_tex_coord0_out.xy = vec2 (0.5) + cogl_position_out.xy / cogl_position_out.w * 0.5;\n"

"float nf = mix (1,"
"                crank_projection_get_far (crank_deferr_proj) /\n"
"                crank_projection_get_near (crank_deferr_proj),\n"
"                crank_deferr_proj.proj_type);\n"

"vec2 base_lb = vec2 (crank_projection_get_left (crank_deferr_proj),\n"
"                     crank_projection_get_top (crank_deferr_proj));\n"
"vec2 base_rt = vec2 (crank_projection_get_right (crank_deferr_proj),\n"
"                     crank_projection_get_bottom (crank_deferr_proj));\n"
"vec2 base_xy = mix (base_lb, base_rt, cogl_tex_coord0_out.xy);\n"

"crank_deferr_near = vec3 (base_xy,\n"
"                          -crank_projection_get_near (crank_deferr_proj));\n"

"crank_deferr_far = vec3 (base_xy * nf,\n"
"                         -crank_projection_get_far (crank_deferr_proj));\n";


static gchar *frag_decl =
"uniform CrankProjection crank_deferr_proj;\n"
"varying vec3 crank_deferr_near;\n"
"varying vec3 crank_deferr_far;\n"
"uniform sampler2D  crank_deferr_geom;\n"
"uniform sampler2D  crank_deferr_color;";

static gchar *frag_replace =
"vec4  crank_geom_value = texture2D (crank_deferr_geom, cogl_tex_coord0_in.xy);\n"
"float crank_depth =      dot (crank_geom_value.ba, vec2 (1, 1 / 256));\n"
"vec3  crank_normal =     vec3 (crank_geom_value.rg, 0);\n"
"crank_normal.z = sqrt (1 - dot (crank_normal.xy, crank_normal.xy));\n"

"vec3  crank_frag_position = mix (crank_deferr_near, crank_deferr_far, crank_depth);\n"

"cogl_color_out = texture2D (crank_deferr_color, cogl_tex_coord0_in.xy);"
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

struct _CrankLightableARanged
{
  CrankLightable _parent;

  gfloat  radius;
  gfloat  intensity;

  CoglContext  *cogl_context;
  CoglPipeline *pipe_line;
  CoglPrimitive *bound_volume;
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
  CrankLightableARanged *lightable;
  GObjectClass *pc_gobject;

  CoglSnippet *snippet_vert;
  CoglSnippet *snippet_frag;

  pc_gobject = (GObjectClass*)crank_lightable_a_ranged_parent_class;

  pc_gobject->constructed (object);

  lightable = (CrankLightableARanged*) object;

  if (lightable->cogl_context == NULL)
    g_error ("CrankLightableARanged: Requires cogl-context at construction.");

  lightable->pipe_line = cogl_pipeline_new (lightable->cogl_context);
  lightable->bound_volume = crank_make_mesh_sphere_uv_p3n3 (lightable->cogl_context, 10, 10);

  snippet_vert = cogl_snippet_new (COGL_SNIPPET_HOOK_VERTEX,
                                   vert_decl,
                                   NULL);
  cogl_snippet_set_replace (snippet_vert, vert_replace);

  snippet_frag = cogl_snippet_new (COGL_SNIPPET_HOOK_FRAGMENT,
                                   frag_decl,
                                   NULL);
  cogl_snippet_set_replace (snippet_frag, frag_replace);

  cogl_pipeline_set_layer_null_texture (lightable->pipe_line, 0, COGL_TEXTURE_TYPE_2D);
  cogl_pipeline_set_layer_null_texture (lightable->pipe_line, 1, COGL_TEXTURE_TYPE_2D);

  cogl_pipeline_add_snippet (lightable->pipe_line,
                             crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_VERTEX));
  cogl_pipeline_add_snippet (lightable->pipe_line,
                             crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_FRAGMENT));

  cogl_pipeline_add_snippet (lightable->pipe_line, snippet_vert);
  cogl_pipeline_add_snippet (lightable->pipe_line, snippet_frag);

  cogl_object_unref (snippet_vert);
  cogl_object_unref (snippet_frag);
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

  crank_trans3_to_matrix_transpose (position, & mv_matrix);

  cogl_framebuffer_set_modelview_matrix (framebuffer, (CoglMatrix*)&mv_matrix);

  cogl_pipeline_set_layer_texture (self->pipe_line, 0, tex_geom);
  cogl_pipeline_set_layer_texture (self->pipe_line, 1, tex_color);

  cogl_primitive_draw (self->bound_volume, framebuffer, self->pipe_line);
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
