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

//////// Private Type Declaration //////////////////////////////////////////////

#define CRANK_TYPE_RENDER_PDATA (crank_render_pdata_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderPData,
                      crank_render_pdata,
                      CRANK, RENDER_PDATA,
                      GObject);

struct _CrankRenderPData
{
  GObject parent;

  // Entities store.
  // TODO: Replace it with octree structure.
  GPtrArray *entities;


};

//////// Private Type functions ////////////////////////////////////////////////

static void crank_render_pdata_add_entity (CrankRenderPData *pdata,
                                           CrankEntityBase  *entity);

static void crank_render_pdata_remove_entity (CrankRenderPData *pdata,
                                              CrankEntityBase  *entity);

//////// Private type vfuncs ///////////////////////////////////////////////////

static void crank_render_pdata_dispose (GObject *object);

static void crank_render_pdata_finalize (GObject *object);

//////// Private type definition ///////////////////////////////////////////////

G_DEFINE_TYPE (CrankRenderPData, crank_render_pdata, G_TYPE_OBJECT)


//////// Private type: GTypeInstance ///////////////////////////////////////////

static void crank_render_pdata_init (CrankRenderPData *pdata)
{
  pdata->entities = g_ptr_array_new ();
}

static void crank_render_pdata_class_init (CrankRenderPDataClass *c)
{
  GObjectClass *c_gobject;

  c_gobject->dispose = crank_render_pdata_dispose;
  c_gobject->finalize = crank_render_pdata_finalize;
}


//////// Private type: GObject /////////////////////////////////////////////////

static void crank_render_pdata_dispose (GObject *object)
{
  CrankRenderPData *pdata = (CrankRenderPData*) object;

  g_ptr_array_set_size (pdata->entities, 0);
}

static void crank_render_pdata_finalize (GObject *object)
{
  CrankRenderPData *pdata = (CrankRenderPData*) object;

  g_ptr_array_unref (pdata->entities);
}

//////// Private type functions ////////////////////////////////////////////////

static void crank_render_pdata_add_entity (CrankRenderPData *pdata,
                                           CrankEntityBase  *entity)
{
  g_ptr_array_add (pdata->entities, entity);
}

static void crank_render_pdata_remove_entity (CrankRenderPData *pdata,
                                              CrankEntityBase  *entity)
{
  g_ptr_array_remove (pdata->entities, entity);
}




//////// List of virtual functions /////////////////////////////////////////////

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

//////// Unused spare functions ////////////////////////////////////////////////

static void       crank_render_module_attached_data (CrankRenderModule *module,
                                                     CrankEntityBase   *entity,
                                                     GObject           *data);

static void       crank_render_module_detached_data (CrankRenderModule *module,
                                                     CrankEntityBase   *entity,
                                                     GObject           *data);

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankRenderModule
{
  CrankSessionModule  _parent;

  goffset     offset_pdata;

  goffset     offset_renderable;

  GPtrArray   *cameras;
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
  CrankSessionModuleClass *c_sessionmodule;

  c_sessionmodule = CRANK_SESSION_MODULE_CLASS (c);

  c_sessionmodule->session_init = crank_render_module_session_init;
}

//////// CrankSessionModule ///////////////////////////////////////////////////

static void
crank_render_module_session_init (CrankSessionModule  *module,
                                  CrankSession        *session,
                                  GError             **error)
{
  CrankRenderModule *rmodule = (CrankRenderModule*)module;
  CrankSessionModulePlaced *pmodule;
  CrankSessionModuleTick *tmodule;
  // Placed Module

  pmodule = (CrankSessionModulePlaced*) crank_session_get_module_by_gtype (session,
                                               CRANK_TYPE_SESSION_MODULE_PLACED);

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
  tmodule = (CrankSessionModuleTick*) crank_session_get_module_by_gtype (session, CRANK_TYPE_SESSION_MODULE_TICK);

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

      place = crank_entity3_get_place (entity);
      if (place == NULL)
        continue;

      CrankTrans3 position;
      CrankProjection *projection;

      crank_entity3_get_position (entity, &position);
      projection = crank_camera_get_projection (camera);

      crank_render_module_render_at (rmodule,
                                     place,
                                     &position,
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
      g_object_new (CRANK_TYPE_RENDER_PDATA, NULL);
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


//////// CrankSession3EntityModule /////////////////////////////////////////////

static GObject*
crank_render_module_make_place_data (CrankSession3EntityModule *module,
                                     CrankPlace3               *place)
{
  // TODO: Get boundary of place and apply it.
  return g_object_new (CRANK_TYPE_RENDER_PDATA, NULL);
}


static void
crank_render_module_attached_data (CrankRenderModule *module,
                                   CrankEntityBase   *entity,
                                   GObject           *data)
{
  CrankPlaceBase *place;
  CrankRenderPData *pdata;

  place = crank_entity_base_get_place (entity);

  if (place == NULL)
    return;

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

  crank_render_pdata_add_entity (pdata, entity);
}


static void
crank_render_module_detached_data (CrankRenderModule *module,
                                   CrankEntityBase   *entity,
                                   GObject           *data)
{
  CrankPlaceBase *place;
  CrankRenderPData *pdata;

  place = crank_entity_base_get_place (entity);

  if (place == NULL)
    return;

  pdata = G_STRUCT_MEMBER (CrankRenderPData*, place, module->offset_pdata);

  crank_render_pdata_remove_entity (pdata, entity);
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
  CrankTrans3 ipos;
  guint i;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  // TODO: Replace it with octree based version
  pdata = (CrankRenderPData*) crank_session3_entity_module_get_place_data ((CrankSession3EntityModule*)module, place);

  crank_trans3_inverse (position, &ipos);

  for (i = 0; i < pdata->entities->len; i++)
    {
      CrankEntity3 *entity = (CrankEntity3*) pdata->entities->pdata[i];
      CrankRenderable *renderable = (CrankRenderable*) crank_session3_entity_module_get_entity_data ((CrankSession3EntityModule*)module, entity);
      CrankTrans3 pos;


      CrankTrans3 rpos;

      // TODO: Directly access position when it is available.
      // Copying will be less efficiently.

      crank_entity3_get_position (entity, &pos);
      crank_trans3_compose (&ipos, &pos, &rpos);

      crank_renderable_render_geom (renderable, &rpos, projection, framebuffer);
    }
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
  CrankTrans3 ipos;
  guint i;

  cogl_framebuffer_clear4f (framebuffer, COGL_BUFFER_BIT_DEPTH | COGL_BUFFER_BIT_COLOR,
                            0, 0, 0, 1);
  cogl_framebuffer_set_projection_matrix (framebuffer,
                                          (const CoglMatrix*) & projection->matrix_t);

  // TODO: Replace it with octree based version
  pdata = (CrankRenderPData*) crank_session3_entity_module_get_place_data ((CrankSession3EntityModule*)module, place);

  crank_trans3_inverse (position, &ipos);

  for (i = 0; i < pdata->entities->len; i++)
    {
      CrankEntity3 *entity = (CrankEntity3*) pdata->entities->pdata[i];
      CrankRenderable *renderable = (CrankRenderable*) crank_session3_entity_module_get_entity_data ((CrankSession3EntityModule*)module, entity);
      CrankTrans3 pos;


      CrankTrans3 rpos;

      // TODO: Directly access position when it is available.
      // Copying will be less efficiently.

      crank_entity3_get_position (entity, &pos);
      crank_trans3_compose (&ipos, &pos, &rpos);

      crank_renderable_render_color (renderable, &rpos, projection, framebuffer);
    }
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
