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
 * SECTION: crankrendermodule
 * @title: CrankRenderModule
 * @short_description: Rendering Module.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * Represents Rendering function.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankrenderable.h"
#include "crankfilm.h"
#include "crankcamera.h"

#include "crankrendermodule.h"


//////// Snippet declarations //////////////////////////////////////////////////

static gchar *pos_vert_decl =
"uniform CrankProjection crank_deferr_proj;\n"
"varying vec3 crank_deferr_near;\n"
"varying vec3 crank_deferr_far;";

static gchar *pos_vert_replace =
"cogl_tex_coord0_out = vec4 (0, 0, 0, 1);\n"
"cogl_tex_coord0_out.xy = vec2 (0.5) + cogl_position_in.xy * 0.5;\n"
"cogl_position_out = cogl_position_in;\n"

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


static gchar *pos_frag_decl =
"uniform CrankProjection crank_deferr_proj;\n"
"varying vec3 crank_deferr_near;\n"
"varying vec3 crank_deferr_far;\n"
"uniform sampler2D  crank_deferr_geom;";

static gchar *pos_frag_replace =
"vec4  crank_geom_value = texture2D (crank_deferr_geom, cogl_tex_coord0_in.xy);\n"
"float crank_depth =      dot (crank_geom_value.ba, vec2 (1, 1 / 256));\n"
"vec3  crank_normal =     vec3 (crank_geom_value.rg, 0);\n"
"crank_normal.z = sqrt (1 - dot (crank_normal.xy, crank_normal.xy));\n"

"vec3  crank_frag_position = mix (crank_deferr_near, crank_deferr_far, crank_depth);\n"

"cogl_color_out = vec4 (crank_frag_position, 1);"
;

//////// Properties of private types ///////////////////////////////////////////

enum {
  PROP_PRIV_0,
  PROP_PRIV_PLACE,
  PROP_PRIV_RENDERABLE_OFFSET,

  PROP_PRIV_COUNTS
};

static GParamSpec *pspecs_priv[PROP_PRIV_COUNTS] = {NULL};

//////// Private Type Declaration //////////////////////////////////////////////

#define CRANK_TYPE_RENDER_PDATA (crank_render_pdata_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderPData,
                      crank_render_pdata,
                      CRANK, RENDER_PDATA,
                      GObject);

struct _CrankRenderPData
{
  GObject parent;

  CrankOctreeSet *entities;
};

//////// Private Type functions ////////////////////////////////////////////////

static void crank_render_pdata_add_entity (CrankRenderPData *pdata,
                                           CrankEntityBase  *entity);

static void crank_render_pdata_remove_entity (CrankRenderPData *pdata,
                                              CrankEntityBase  *entity);

//////// Private type vfuncs ///////////////////////////////////////////////////

static void crank_render_pdata_constructed (GObject *object);

static void crank_render_pdata_set_property (GObject      *object,
                                             guint         prop_id,
                                             const GValue *value,
                                             GParamSpec   *pspec);

static void crank_render_pdata_dispose (GObject *object);

static void crank_render_pdata_finalize (GObject *object);


//////// Private type callbacks ////////////////////////////////////////////////

static CrankVecFloat3 *crank_render_pdata_get_pos (gpointer data,
                                                   gpointer userdata);

static gfloat crank_render_pdata_get_rad (gpointer data,
                                          gpointer userdata);


//////// Private type definition ///////////////////////////////////////////////

G_DEFINE_TYPE (CrankRenderPData, crank_render_pdata, G_TYPE_OBJECT)


//////// Private type: GTypeInstance ///////////////////////////////////////////

static void crank_render_pdata_init (CrankRenderPData *pdata)
{
}

static void crank_render_pdata_class_init (CrankRenderPDataClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->constructed = crank_render_pdata_constructed;
  c_gobject->set_property = crank_render_pdata_set_property;
  c_gobject->dispose = crank_render_pdata_dispose;
  c_gobject->finalize = crank_render_pdata_finalize;

  pspecs_priv[PROP_PRIV_PLACE] = g_param_spec_pointer ("place", "place", "Place",
                                                      G_PARAM_PRIVATE |
                                                      G_PARAM_WRITABLE |
                                                      G_PARAM_CONSTRUCT_ONLY |
                                                      G_PARAM_STATIC_STRINGS );

  pspecs_priv[PROP_PRIV_RENDERABLE_OFFSET] =
      g_param_spec_int64 ("renderable-offset", "Renderable offset",
                          "Renderable offset",
                          0, G_MAXINT64, 0,
                          G_PARAM_PRIVATE |
                          G_PARAM_WRITABLE |
                          G_PARAM_CONSTRUCT_ONLY |
                          G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_PRIV_COUNTS, pspecs_priv);
}




//////// Private type: GObject /////////////////////////////////////////////////

static void
crank_render_pdata_constructed (GObject *object)
{
  CrankRenderPData *pdata = (CrankRenderPData*) object;
  CrankPlace3 *place = g_object_get_data (object, "place");
  gpointer renderable_offset = g_object_get_data (object, "renderable-offset");

  CrankBox3 box;

  crank_box3_init_uvec (& box, -1000, -1000, -1000, 1000, 1000, 1000);

  pdata->entities = crank_octree_set_new (& box,
                                          crank_render_pdata_get_pos, NULL, NULL,
                                          crank_render_pdata_get_rad, renderable_offset, NULL);
}

static void
crank_render_pdata_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  switch (prop_id)
    {
    case PROP_PRIV_PLACE:
      g_object_set_data (object, "place",
                         g_value_get_pointer (value));
      break;

    case PROP_PRIV_RENDERABLE_OFFSET:
      g_object_set_data (object, "renderable-offset",
                         GINT_TO_POINTER (g_value_get_int64 (value)));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_render_pdata_dispose (GObject *object)
{
  CrankRenderPData *pdata = (CrankRenderPData*) object;

  crank_octree_set_remove_all (pdata->entities);
}

static void
crank_render_pdata_finalize (GObject *object)
{
  CrankRenderPData *pdata = (CrankRenderPData*) object;

  crank_octree_set_unref (pdata->entities);
}

//////// Private type callbacks ////////////////////////////////////////////////

static CrankVecFloat3*
crank_render_pdata_get_pos (gpointer data,
                            gpointer userdata)
{
  CrankEntity3 *entity = (CrankEntity3*)data;

  return & entity->position.mtrans;
}

static gfloat
crank_render_pdata_get_rad (gpointer data,
                            gpointer userdata)
{
  goffset offset = (goffset) userdata;

  CrankEntity3 *entity = (CrankEntity3*)data;
  CrankRenderable *renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, offset);

  return entity->position.mscl *
         crank_renderable_get_visible_radius (renderable);
}

//////// Private type functions ////////////////////////////////////////////////

static void crank_render_pdata_add_entity (CrankRenderPData *pdata,
                                           CrankEntityBase  *entity)
{
  crank_octree_set_add (pdata->entities, entity);
}

static void crank_render_pdata_remove_entity (CrankRenderPData *pdata,
                                              CrankEntityBase  *entity)
{
  crank_octree_set_remove (pdata->entities, entity);
}




//////// List of virtual functions /////////////////////////////////////////////

static void       crank_render_module_constructed (GObject *object);

static void       crank_render_module_get_property (GObject    *object,
                                                    guint       prop_id,
                                                    GValue     *value,
                                                    GParamSpec *pspec);

static void       crank_render_module_set_property (GObject      *object,
                                                    guint         prop_id,
                                                    const GValue *value,
                                                    GParamSpec   *pspec);

static void       crank_render_module_dispose (GObject *object);

static void       crank_render_module_session_init (CrankSessionModule  *module,
                                                    CrankSession        *session,
                                                    GError             **error);


//////// Functions for other modules ///////////////////////////////////////////

static void       crank_render_module_tick (CrankSessionModuleTick *module,
                                            gpointer                user_data);

static void       crank_render_module_place_created (CrankSessionModulePlaced *pmodule,
                                                     CrankPlaceBase           *place,
                                                     gpointer                  user_data);

static void       crank_render_module_entity_added (CrankSessionModulePlaced *pmodule,
                                                    CrankPlaceBase           *place,
                                                    CrankEntityBase          *entity,
                                                    gpointer                  userdata);

static void       crank_render_module_entity_removed (CrankSessionModulePlaced *pmodule,
                                                      CrankPlaceBase           *place,
                                                      CrankEntityBase          *entity,
                                                      gpointer                  userdata);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_COGL_CONTEXT,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankRenderModule
{
  CrankSessionModule  _parent;

  CoglContext *cogl_context;

  goffset     offset_pdata;
  goffset     offset_renderable;

  GPtrArray   *cameras;

  CoglPipeline *pipe_position;
  gint          pipe_position_deferr_proj[2];
};

G_DEFINE_TYPE (CrankRenderModule,
               crank_render_module,
               CRANK_TYPE_SESSION_MODULE)



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_module_init (CrankRenderModule *module)
{
  module->cameras = g_ptr_array_new_with_free_func (g_object_unref);
}



static void
crank_render_module_class_init (CrankRenderModuleClass *c)
{
  GObjectClass *c_gobject;
  CrankSessionModuleClass *c_sessionmodule;

  c_gobject = G_OBJECT_CLASS (c);
  c_gobject->constructed = crank_render_module_constructed;
  c_gobject->get_property = crank_render_module_get_property;
  c_gobject->set_property = crank_render_module_set_property;
  c_gobject->dispose = crank_render_module_dispose;

  pspecs[PROP_COGL_CONTEXT] = g_param_spec_pointer ("cogl-context", "CoglContext",
                                                    "CoglContext to initialize with.",
                                                    G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY |
                                                    G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_sessionmodule = CRANK_SESSION_MODULE_CLASS (c);
  c_sessionmodule->session_init = crank_render_module_session_init;
}





//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_render_module_constructed (GObject *object)
{
  CrankRenderModule *module = (CrankRenderModule*) object;

  CoglSnippet *pos_snippet_vert;
  CoglSnippet *pos_snippet_frag;

  module->pipe_position = cogl_pipeline_new (module->cogl_context);

  pos_snippet_vert = cogl_snippet_new (COGL_SNIPPET_HOOK_VERTEX, NULL, NULL);
  cogl_snippet_set_declarations (pos_snippet_vert, pos_vert_decl);
  cogl_snippet_set_replace (pos_snippet_vert, pos_vert_replace);

  pos_snippet_frag = cogl_snippet_new (COGL_SNIPPET_HOOK_FRAGMENT, NULL, NULL);
  cogl_snippet_set_declarations (pos_snippet_frag, pos_frag_decl);
  cogl_snippet_set_replace (pos_snippet_frag, pos_frag_replace);

  cogl_pipeline_add_snippet (module->pipe_position,
                             crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_VERTEX));
  cogl_pipeline_add_snippet (module->pipe_position,
                             crank_projection_get_snippet_def (COGL_SNIPPET_HOOK_FRAGMENT));

  cogl_pipeline_add_snippet (module->pipe_position, pos_snippet_vert);
  cogl_pipeline_add_snippet (module->pipe_position, pos_snippet_frag);

  cogl_object_unref (pos_snippet_vert);
  cogl_object_unref (pos_snippet_frag);



  crank_projection_get_uniform_locations (module->pipe_position,
                                          "crank_deferr_proj",
                                          module->pipe_position_deferr_proj);
}



static void
crank_render_module_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspecs)
{
  CrankRenderModule *module = (CrankRenderModule*) object;

  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
      g_value_set_pointer (value, module->cogl_context);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspecs);
    }
}



static void
crank_render_module_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspecs)
{
  CrankRenderModule *module = (CrankRenderModule*) object;

  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
      module->cogl_context = g_value_get_pointer (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspecs);
    }
}



static void
crank_render_module_dispose (GObject *object)
{
  CrankRenderModule *module = (CrankRenderModule*) object;

  cogl_object_unref (module->pipe_position);
  module->pipe_position = NULL;
}


//////// CrankSessionModule ////////////////////////////////////////////////////

static void
crank_render_module_session_init (CrankSessionModule  *module,
                                  CrankSession        *session,
                                  GError             **error)
{
  CrankRenderModule *rmodule = (CrankRenderModule*)module;
  CrankSessionModulePlaced *pmodule;
  CrankSessionModuleTick *tmodule;
  // Placed Module

  pmodule = CRANK_SESSION_MODULE_PLACED (crank_session_get_module_by_gtype (session,
                                               CRANK_TYPE_SESSION_MODULE_PLACED));

  if (pmodule == NULL)
    g_error ("CrankRenderModule: requires CrankSessionModulePlaced.");

  crank_session_module_placed_attach_place_alloc_object (pmodule,
                                                         & rmodule->offset_pdata);

  crank_session_module_placed_attach_entity_alloc_object (pmodule,
                                                          & rmodule->offset_renderable);

  g_signal_connect (pmodule, "place-created",
                    (GCallback)crank_render_module_place_created, rmodule);

  g_signal_connect (pmodule, "entity-added",
                    (GCallback)crank_render_module_entity_added, rmodule);

  g_signal_connect (pmodule, "entity-removed",
                    (GCallback)crank_render_module_entity_removed, rmodule);


  // Tick Module
  tmodule = CRANK_SESSION_MODULE_TICK (crank_session_get_module_by_gtype (session, CRANK_TYPE_SESSION_MODULE_TICK));

  if (tmodule == NULL)
    return;

  g_signal_connect (tmodule, "tick", (GCallback)crank_render_module_tick, rmodule);
}


//////// Callback functions for other modules //////////////////////////////////

static void
crank_render_module_tick (CrankSessionModuleTick *tmodule,
                          gpointer                user_data)
{
  CrankRenderModule *rmodule = (CrankRenderModule*) user_data;

  guint i;

  for (i = 0; i < rmodule->cameras->len; i++)
    {
      CrankCamera *camera;
      CrankFilm *film;
      CrankEntity3 *entity;
      CrankPlace3 *place;

      camera = rmodule->cameras->pdata[i];

      film = crank_camera_get_film (camera);
      if (film == NULL)
        continue;

      entity = crank_camera_get_entity (camera);
      if (entity == NULL)
        continue;

      place = (CrankPlace3*)crank_entity_base_get_place ((CrankEntityBase*)entity);
      if (place == NULL)
        continue;

      CrankTrans3 position;
      CrankProjection *projection;

      projection = crank_camera_get_projection (camera);

      crank_render_module_render_at (rmodule,
                                     place,
                                     & entity->position,
                                     projection,
                                     film);

      crank_camera_rendered (camera);
    }
}

static void
crank_render_module_place_created (CrankSessionModulePlaced *pmodule,
                                   CrankPlaceBase           *place,
                                   gpointer                  userdata)
{
  CrankRenderModule *module  = (CrankRenderModule*) userdata;

  G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata) =
      g_object_new (CRANK_TYPE_RENDER_PDATA,
                    "place", place,
                    "renderable-offset", module->offset_renderable,
                    NULL);
}


static void
crank_render_module_entity_added (CrankSessionModulePlaced *pmodule,
                                  CrankPlaceBase           *place,
                                  CrankEntityBase          *entity,
                                  gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;

  CrankRenderPData *pdata;
  CrankRenderable *renderable;

  renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);

  if (renderable == NULL)
    return;

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

  crank_render_pdata_add_entity (pdata, entity);
}


static void
crank_render_module_entity_removed (CrankSessionModulePlaced *pmodule,
                                    CrankPlaceBase           *place,
                                    CrankEntityBase          *entity,
                                    gpointer                  userdata)
{
  CrankRenderModule *module = (CrankRenderModule*) userdata;

  CrankRenderPData *pdata;
  CrankRenderable *renderable;

  renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);

  if (renderable == NULL)
    return;

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

  crank_render_pdata_remove_entity (pdata, entity);
}







//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_render_module_new:
 * @cogl_context: A Cogl Context.
 *
 * Constructs a rendering module.
 *
 * Returns: (transfer full): Newly constructed module.
 */
CrankRenderModule*
crank_render_module_new (CoglContext *cogl_context)
{
  return (CrankRenderModule*) g_object_new (CRANK_TYPE_RENDER_MODULE,
                                            "cogl-context", cogl_context,
                                            NULL);
}

//////// Entities and places functions /////////////////////////////////////////

/**
 * crank_render_module_set_renderable:
 * @module: A Module.
 * @entity: A Entity.
 * @renderable: (nullable): A Renderable.
 *
 * Sets a renderable for the entity. The renderable may be %NULL, for non-visible
 * entity. (For example, camera hook, spawn point, etc...)
 */
void
crank_render_module_set_renderable (CrankRenderModule *module,
                                    CrankEntityBase   *entity,
                                    CrankRenderable   *renderable)
{
  CrankPlaceBase *place;
  CrankRenderPData *pdata;
  CrankRenderable **renderable_ptr;
  CrankRenderable *renderable_prev;

  renderable_ptr = G_STRUCT_MEMBER_P (entity, module->offset_renderable);
  renderable_prev = *renderable_ptr;

  if (! g_set_object (renderable_ptr, renderable))
    return;


  place = crank_entity_base_get_place (entity);

  if (place != NULL)
    {
      pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

      if (renderable_prev == NULL)
          crank_render_pdata_add_entity (pdata, entity);

      else if (renderable == NULL)
        crank_render_pdata_remove_entity (pdata, entity);
    }

}


/**
 * crank_render_module_get_renderable:
 * @module: A Module.
 * @entity: A Entity.
 *
 * Gets a renderable from entity. Non-visible entities does not have renderable.
 *
 * Returns: (nullable): Renderable, or %NULL if it does not have.
 */
CrankRenderable*
crank_render_module_get_renderable (CrankRenderModule *module,
                                    CrankEntityBase   *entity)
{
  return G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
}


//////// Public functions //////////////////////////////////////////////////////


/**
 * crank_render_module_render_geom_at:
 * @module: A Module.
 * @place: A Place.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders @place which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_geom_at (CrankRenderModule *module,
                                    CrankPlace3       *place,
                                    CrankTrans3       *position,
                                    CrankProjection   *projection,
                                    CoglFramebuffer   *framebuffer)
{
  CrankRenderPData *pdata;
  GList *list;

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);
  list = crank_octree_set_get_data_list (pdata->entities);

  crank_render_module_render_geom_list (module, list, position, projection, framebuffer);

  g_list_free (list);
}

/**
 * crank_render_module_render_color_at:
 * @module: A Module.
 * @place: A Place.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders @place which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_color_at (CrankRenderModule *module,
                                     CrankPlace3       *place,
                                     CrankTrans3       *position,
                                     CrankProjection   *projection,
                                     CoglFramebuffer   *framebuffer)
{
  CrankRenderPData *pdata;
  GList *list;

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);
  list = crank_octree_set_get_data_list (pdata->entities);

  crank_render_module_render_color_list (module, list, position, projection, framebuffer);

  g_list_free (list);
}

/**
 * crank_render_module_render_geom_list:
 * @module: A Module.
 * @list: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_geom_list (CrankRenderModule *module,
                                      GList *list,
                                      CrankTrans3       *position,
                                      CrankProjection   *projection,
                                      CoglFramebuffer   *framebuffer)
{
  CrankTrans3 ipos;
  guint i;

  GList *iter;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  crank_trans3_inverse (position, &ipos);

  for (iter = list; iter != NULL; iter = iter->next)
    {
      CrankEntity3 *entity = (CrankEntity3*) iter->data;
      CrankRenderable *renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
      CrankTrans3 rpos;

      crank_trans3_compose (&ipos, & entity->position, &rpos);

      crank_renderable_render_geom (renderable, &rpos, projection, framebuffer);
    }
}

/**
 * crank_render_module_render_color_list:
 * @module: A Module.
 * @list: (element-type CrankEntity3): entities.
 * @position: A Position
 * @projection: A Projection.
 * @framebuffer: A Framebuffer to render.
 *
 * Renders entities in @list which looked at @position, on @framebuffer.
 */
void
crank_render_module_render_color_list (CrankRenderModule *module,
                                       GList *list,
                                       CrankTrans3       *position,
                                       CrankProjection   *projection,
                                       CoglFramebuffer   *framebuffer)
{
  CrankTrans3 ipos;
  guint i;

  GList *iter;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  crank_trans3_inverse (position, &ipos);

  for (iter = list; iter != NULL; iter = iter->next)
    {
      CrankEntity3 *entity = (CrankEntity3*) iter->data;
      CrankRenderable *renderable = G_STRUCT_MEMBER (CrankRenderable*, entity, module->offset_renderable);
      CrankTrans3 rpos;

      crank_trans3_compose (&ipos, & entity->position, &rpos);

      crank_renderable_render_color (renderable, &rpos, projection, framebuffer);
    }
}



/**
 * crank_render_module_render_pos:
 * @module: A Module.
 * @geom_tex: Geometry texture.
 * @framebuffer: Framebuffer to render.
 *
 * Renders fragment position from @geom_tex.
 *
 * Hmm.
 */
void
crank_render_module_render_pos (CrankRenderModule *module,
                                CoglTexture       *geom_tex,
                                CrankProjection   *projection,
                                CoglFramebuffer   *framebuffer)
{
  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);

  crank_projection_set_uniform_value (projection,
                                      module->pipe_position,
                                      module->pipe_position_deferr_proj);

  cogl_pipeline_set_layer_texture (module->pipe_position, 0, geom_tex);

  cogl_framebuffer_draw_rectangle (framebuffer,
                                   module->pipe_position,
                                   -1, -1, 1, 1);
}

/**
 * crank_render_module_render_at:
 * @module: A Module.
 * @place: A Place.
 * @position: A Position.
 * @projection: A Projection.
 * @film: A Film.
 *
 * Renders a scene to a film.
 */
void
crank_render_module_render_at (CrankRenderModule *module,
                               CrankPlace3       *place,
                               CrankTrans3       *position,
                               CrankProjection   *projection,
                               CrankFilm         *film)
{

/*
  crank_render_module_render_color_at (module,
                                       place,
                                       position,
                                       projection,
                                       crank_film_get_framebuffer (film, 5));
 */
  crank_render_module_render_geom_at (module,
                                      place,
                                      position,
                                      projection,
                                      crank_film_get_framebuffer (film, 0));

  crank_render_module_render_pos (module,
                                  crank_film_get_texture (film, 0),
                                  projection,
                                  crank_film_get_framebuffer (film, 5));
  // XXX: For now, rendering a color buffer on result buffer.

  // TODO: Render to other buffers.
  //
}

/**
 * crank_render_module_add_camera:
 * @module: A Module.
 * @camera: A Camera.
 *
 * Adds @camera to this module.
 */
void
crank_render_module_add_camera (CrankRenderModule *module,
                                CrankCamera       *camera)
{
  g_ptr_array_add (module->cameras, g_object_ref (camera));
}

/**
 * crank_render_module_remove_camera:
 * @module: A Module.
 * @camera: A Camera.
 *
 * Removes a @camera from this module.
 */
void
crank_render_module_remove_camera (CrankRenderModule *module,
                                   CrankCamera       *camera)
{
  g_ptr_array_remove (module->cameras, camera);
}


/**
 * crank_render_module_get_n_camera:
 * @module: A Module.
 *
 * Get count of cameras in this module.
 *
 * Returns: Number of cameras in this module.
 */
guint
crank_render_module_get_n_camera (CrankRenderModule *module)
{
  return module->cameras->len;
}
