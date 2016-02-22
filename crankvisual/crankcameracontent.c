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
#include <clutter/clutter.h>

#include "crankbase.h"
#include "crankcore.h"

#include "crankprojection.h"
#include "crankfilm.h"
#include "crankcamera.h"
#include "crankcameracontent.h"

/**
 * SECTION: crankcameracontent
 * @title: CrankCameraContent
 * @short_description: ClutterContent that presents CrankCamera
 * @stability: unstable
 * @include: crankvisual.h
 *
 * This is used to present what #CrankCamera is seeing in Clutter scenes.
 *
 */


static const ClutterColor BLACK = {
  0, 0, 0, 255
};

//////// List of virtual functions /////////////////////////////////////////////

static void     crank_camera_content_content_iface_init (ClutterContentIface *iface);


static void     crank_camera_content_get_property (GObject    *object,
                                                   guint       prop_id,
                                                   GValue     *value,
                                                   GParamSpec *pspec);

static void     crank_camera_content_set_property (GObject      *object,
                                                   guint         prop_id,
                                                   const GValue *value,
                                                   GParamSpec   *pspec);

static void     crank_camera_content_dispose (GObject *object);


static gboolean crank_camera_content_get_preferred_size (ClutterContent *content,
                                                         gfloat         *width,
                                                         gfloat         *height);

static void     crank_camera_content_paint_content (ClutterContent   *conetnt,
                                                    ClutterActor     *actor,
                                                    ClutterPaintNode *node);

static void     crank_camera_content_attached (ClutterContent *content,
                                               ClutterActor   *actor);

static void     crank_camera_content_detached (ClutterContent *content,
                                               ClutterActor   *actor);

//////// Private functions /////////////////////////////////////////////////////

//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_CAMERA,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankCameraContent
{
  GObject _parent;

  CrankCamera *camera;
};

G_DEFINE_TYPE_WITH_CODE (CrankCameraContent,
                         crank_camera_content,
                         G_TYPE_OBJECT,
                         {
                           G_IMPLEMENT_INTERFACE (CLUTTER_TYPE_CONTENT,
                                                  crank_camera_content_content_iface_init);
                         })



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_camera_content_init (CrankCameraContent *self)
{
  self->camera = NULL;
}

static void
crank_camera_content_class_init (CrankCameraContentClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_camera_content_get_property;
  c_gobject->set_property = crank_camera_content_set_property;
  c_gobject->dispose = crank_camera_content_dispose;

  pspecs[PROP_CAMERA] =
  g_param_spec_object ("camera", "camera", "Camera to associate to this content",
                       CRANK_TYPE_CAMERA,
                       G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}

static void
crank_camera_content_content_iface_init (ClutterContentIface *iface)
{
  iface->get_preferred_size = crank_camera_content_get_preferred_size;
  iface->paint_content = crank_camera_content_paint_content;
  iface->attached = crank_camera_content_attached;
  iface->detached = crank_camera_content_detached;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_camera_content_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  CrankCameraContent *content = (CrankCameraContent*)object;

  switch (prop_id)
    {
    case PROP_CAMERA:
      g_value_set_object (value, content->camera);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_camera_content_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  CrankCameraContent *content = (CrankCameraContent*)object;

  switch (prop_id)
    {
    case PROP_CAMERA:
      crank_camera_content_set_camera (content,
                                       (CrankCamera*) g_value_get_object(value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_camera_content_dispose (GObject *object)
{
  GObjectClass *pc_gobject = (GObjectClass*)crank_camera_content_parent_class;
  CrankCameraContent *content = (CrankCameraContent*)object;

  g_clear_object (& content->camera);

  pc_gobject->dispose (object);
}




//////// ClutterContent ////////////////////////////////////////////////////////

static gboolean
crank_camera_content_get_preferred_size (ClutterContent *content,
                                         gfloat *width,
                                         gfloat *height)
{
  CrankCameraContent *ccontent = (CrankCameraContent*) content;
  CrankFilm *film;

  if (ccontent->camera == NULL)
    return FALSE;

  film = crank_camera_get_film (ccontent->camera);
  *width = crank_film_get_width (film);
  *height = crank_film_get_height (film);

  return TRUE;
}

static void
crank_camera_content_paint_content (ClutterContent   *content,
                                    ClutterActor     *actor,
                                    ClutterPaintNode *node)
{
  CrankCameraContent *ccontent = (CrankCameraContent*) content;
  CrankFilm *film;
  ClutterPaintNode *child_node;
  ClutterActorBox actor_allocation;

  if (ccontent->camera == NULL)
    return;

  film = crank_camera_get_film (ccontent->camera);

  if (film == NULL)
    return;

  child_node = clutter_texture_node_new (crank_film_get_texture (film,
                                                                 crank_film_get_result_index (film)),
                                         NULL,
                                         CLUTTER_SCALING_FILTER_LINEAR,
                                         CLUTTER_SCALING_FILTER_LINEAR);

  clutter_actor_get_allocation_box (actor, & actor_allocation);

  clutter_paint_node_add_texture_rectangle (child_node, & actor_allocation,
                                            0, 0,
                                            1, 1);
  clutter_paint_node_add_child (node, child_node);
  clutter_paint_node_unref (child_node);
}

static void
crank_camera_content_attached (ClutterContent *content,
                               ClutterActor   *actor)
{

}

static void
crank_camera_content_detached (ClutterContent *content,
                               ClutterActor   *actor)
{

}



//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_camera_content_new:
 *
 * Creates newly created content.
 *
 * Returns: (transfer full): Newly created instance.
 */
CrankCameraContent*
crank_camera_content_new (void)
{
  return (CrankCameraContent*) g_object_new (CRANK_TYPE_CAMERA_CONTENT,
                                             NULL);
}



//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_camera_content_get_camera:
 * @content: A Content.
 *
 * Gets camera associated to this content.
 *
 * Returns: (transfer none): A Camera.
 */
CrankCamera*
crank_camera_content_get_camera (CrankCameraContent *content)
{
  return content->camera;
}

/**
 * crank_camera_content_set_camera:
 * @content: A Content.
 * @camera: (transfer none): A Camera.
 *
 * Sets camera associated to this content.
 */
void
crank_camera_content_set_camera (CrankCameraContent *content,
                                 CrankCamera        *camera)
{
  if (content->camera != camera)
    {
      if (content->camera != NULL)
        {
          g_signal_handlers_disconnect_by_data (content->camera, content);
          g_object_unref (content->camera);
        }



      if (camera != NULL)
        {
          g_signal_connect_swapped (camera, "rendered",
                                    (GCallback)clutter_content_invalidate, content);
          content->camera = g_object_ref (camera);
        }
      else
        {
          content->camera = NULL;
        }

      g_object_notify_by_pspec ((GObject*)content, pspecs[PROP_CAMERA]);
    }
}
