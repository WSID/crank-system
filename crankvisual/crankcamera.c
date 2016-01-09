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

#include <math.h>

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"
#include "crankcore.h"

#include "crankprojection.h"
#include "crankfilm.h"
#include "crankcamera.h"

/**
 * SECTION: crankcamera
 * @title: CrankCamera
 * @short_description: Camera representation.
 * @stability: unstable
 * @include: crankvisual.h
 *
 * #CrankCamera contains information to render a scene for user, like tracking
 * entities and projection of the scene.
 *
 * # Projection
 *
 * CrankCamera holds view properties like CrankCamera:left and CrankCamera:right
 * and so on. One of preferred to use crank_camera_perspective() and its
 * familes. Thes functions will change and emit signal at once.
 *
 * Alternatively you may use g_object_freeze_notify() for setting properties.
 * this will hold notify signal until g_object_thaw_notify() so that you don't
 * have notify::matrix per single property change.
 */



//////// List of virtual functions /////////////////////////////////////////////

static void   crank_camera_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec);

static void   crank_camera_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec);

static void   crank_camera_dispose (GObject *object);

static void   crank_camera_finalize (GObject *object);

//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_FILM,
  PROP_ENTITY,
  PROP_PROJECTION,

  PROP_PROJECTION_TYPE,
  PROP_LEFT,
  PROP_RIGHT,
  PROP_BOTTOM,
  PROP_TOP,
  PROP_NEAR,
  PROP_FAR,

  PROP_MATRIX,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankCamera {
  GObject _parent;

  CrankFilm    *film;
  CrankEntity3 *entity;

  CrankProjection *projection;
};
G_DEFINE_TYPE (CrankCamera, crank_camera, G_TYPE_OBJECT);

//////// GTypeInstance /////////////////////////////////////////////////////////

static void crank_camera_init (CrankCamera *self)
{
  self->projection = crank_projection_new ();
}

static void crank_camera_class_init (CrankCameraClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->dispose = crank_camera_dispose;
  c_gobject->finalize = crank_camera_finalize;
  c_gobject->get_property = crank_camera_get_property;
  c_gobject->set_property = crank_camera_set_property;

  pspecs[PROP_FILM] = g_param_spec_object ("film", "film", "film to render on",
                                           CRANK_TYPE_FILM,
                                           G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  /**
   * CrankCamera:entity: (type CrankEntity3)
   *
   * Entity to track on
   */
  pspecs[PROP_ENTITY] = g_param_spec_pointer ("entity", "entity", "Entity to track on",
                                              G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_PROJECTION] = g_param_spec_boxed ("projection", "projection", "Projection of camera",
                                                CRANK_TYPE_PROJECTION,
                                                G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_PROJECTION_TYPE] =
  g_param_spec_enum ("projection-type", "projection type", "Projection type of camera.",
                     CRANK_TYPE_PROJECTION_TYPE, CRANK_PROJECTION_ORTHO,
                     G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_LEFT] = g_param_spec_float ("left", "left", "Left of camera",
                                          -G_MAXFLOAT, G_MAXFLOAT, -1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_RIGHT] = g_param_spec_float ("right", "right", "Right of camera",
                                          -G_MAXFLOAT, G_MAXFLOAT, 1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_BOTTOM] = g_param_spec_float ("bottom", "bottom", "Bottom of camera",
                                          -G_MAXFLOAT, G_MAXFLOAT, -1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_TOP] = g_param_spec_float ("top", "top", "Top of camera",
                                          -G_MAXFLOAT, G_MAXFLOAT, 1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_NEAR] = g_param_spec_float ("near", "near", "Near of camera",
                                          -G_MAXFLOAT, G_MAXFLOAT, -1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_FAR] = g_param_spec_float ("far", "far", "Far of camera",
                                          -G_MAXFLOAT, G_MAXFLOAT, 1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );


  pspecs[PROP_MATRIX] = g_param_spec_boxed ("matrix", "Matrix",
                                            "Projection matrix",
                                            CRANK_TYPE_MAT_FLOAT4,
                                            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_camera_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  CrankCamera *camera = (CrankCamera*) object;

  switch (prop_id)
    {
    case PROP_FILM:
      g_value_set_object (value, camera->film);
      break;

    case PROP_ENTITY:
      g_value_set_pointer (value, camera->entity);
      break;

    case PROP_PROJECTION:
      g_value_set_boxed (value, camera->projection);
      break;

    case PROP_PROJECTION_TYPE:
      g_value_set_enum (value, camera->projection->proj_type);
      break;

    case PROP_LEFT:
      g_value_set_float (value, camera->projection->left);
      break;

    case PROP_RIGHT:
      g_value_set_float (value, camera->projection->right);
      break;

    case PROP_BOTTOM:
      g_value_set_float (value, camera->projection->bottom);
      break;

    case PROP_TOP:
      g_value_set_float (value, camera->projection->top);
      break;

    case PROP_NEAR:
      g_value_set_float (value, camera->projection->near);
      break;

    case PROP_FAR:
      g_value_set_float (value, camera->projection->far);
      break;

    case PROP_MATRIX:
      g_value_set_boxed (value, & camera->projection->matrix);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);

    }
}

static void
crank_camera_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  CrankCamera *camera = (CrankCamera*) object;

  switch (prop_id)
    {
    case PROP_FILM:
      crank_camera_set_film (camera,
                             (CrankFilm*)g_value_get_object (value));
      break;

    case PROP_ENTITY:
      crank_camera_set_entity (camera,
                               (CrankEntity3*)g_value_get_pointer (value));
      break;

    case PROP_PROJECTION:
      crank_camera_set_projection (camera,
                                   (CrankProjection*) g_value_get_boxed (value));
      break;

    case PROP_PROJECTION_TYPE:
      crank_camera_set_projection_type (camera, g_value_get_enum (value));
      break;

    case PROP_LEFT:
      crank_camera_set_left (camera, g_value_get_float (value));
      break;

    case PROP_RIGHT:
      crank_camera_set_right (camera, g_value_get_float (value));
      break;

    case PROP_BOTTOM:
      crank_camera_set_bottom (camera, g_value_get_float (value));
      break;

    case PROP_TOP:
      crank_camera_set_top (camera, g_value_get_float (value));
      break;

    case PROP_NEAR:
      crank_camera_set_near (camera, g_value_get_float (value));
      break;

    case PROP_FAR:
      crank_camera_set_far (camera, g_value_get_float (value));
      break;

    case PROP_MATRIX:
      crank_camera_set_matrix (camera,
                               (CrankMatFloat4*) g_value_get_boxed (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);

    }
}

static void
crank_camera_dispose (GObject *object)
{
  CrankCamera *camera = (CrankCamera*) object;
  GObjectClass *pc_gobject = (GObjectClass*) crank_camera_parent_class;

  g_clear_object (& camera->film);
  camera->entity = NULL;

  pc_gobject->dispose (object);
}

static void
crank_camera_finalize (GObject *object)
{
  CrankCamera *camera = (CrankCamera*) object;
  GObjectClass *pc_gobject = (GObjectClass*) crank_camera_parent_class;

  crank_projection_unref (camera->projection);

  pc_gobject->finalize (object);
}


//////// Properties ////////////////////////////////////////////////////////////




/**
 * crank_camera_get_film:
 * @camera: A Camera.
 *
 * Gets @film of @camera.
 *
 * Returns: (transfer none) (nullable): A Film.
 */
CrankFilm*
crank_camera_get_film (CrankCamera *camera)
{
  return camera->film;
}

/**
 * crank_camera_set_film:
 * @camera: A Camera.
 * @film: (nullable): A Film.
 *
 * Sets @film of @camera, so that @film would hold what @camera would see in the
 * place.
 */
void
crank_camera_set_film (CrankCamera *camera,
                       CrankFilm   *film)
{
  if (g_set_object (& camera->film, film))
    g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_FILM]);
}



/**
 * crank_camera_get_entity:
 * @camera: A Camera.
 *
 * Gets entity to track.
 *
 * Returns: (transfer none) (nullable): Entity to track.
 */
CrankEntity3*
crank_camera_get_entity (CrankCamera *camera)
{
  return camera->entity;
}

/**
 * crank_camera_set_entity:
 * @camera: A Camera.
 * @entity: (transfer none) (nullable): Entity to track
 *
 * Sets @entity to track. @camera will track @entity. If set %NULL, camera will
 * be inactive.
 */
void
crank_camera_set_entity (CrankCamera  *camera,
                         CrankEntity3 *entity)
{
  if (entity != camera->entity)
    {
      camera->entity = entity;
      g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_ENTITY]);
    }
}

/**
 * crank_camera_get_projection:
 * @camera: A Camera.
 *
 * Gets projection of camera.
 *
 * Returns: (transfer none): Projection of camera.
 */
CrankProjection*
crank_camera_get_projection (CrankCamera *camera)
{
  return camera->projection;
}

/**
 * crank_camera_set_projection:
 * @camera: A Camera.
 * @projection: (transfer none): A Projection.
 *
 * Sets projection of camera.
 */
void
crank_camera_set_projection (CrankCamera     *camera,
                             CrankProjection *projection)
{
  crank_projection_unref (camera->projection);
  camera->projection = crank_projection_ref (projection);
}

/**
 * crank_camera_get_projection_type:
 * @camera: A Camera.
 *
 * Gets view type of camera.
 *
 * Returns: View type of camera.
 */
CrankProjectionType
crank_camera_get_projection_type (CrankCamera *camera)
{
  return camera->projection->proj_type;
}

/**
 * crank_camera_set_projection_type:
 * @camera: A Camera:
 * @projection_type: View type of camera.
 *
 * Sets view type of camera.
 */
void
crank_camera_set_projection_type (CrankCamera         *camera,
                                  CrankProjectionType  proj_type)
{
  if (proj_type != camera->projection->proj_type)
    {
      camera->projection->proj_type = proj_type;

      crank_projection_update_matrix (camera->projection);

      g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_PROJECTION_TYPE]);
      g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
    }
}



/**
 * crank_camera_get_left:
 * @camera: A Camera.
 *
 * Gets left of camera view.
 *
 * Returns: left view of camera.
 */
gfloat
crank_camera_get_left (CrankCamera *camera)
{
  return camera->projection->left;
}

/**
 * crank_camera_set_left:
 * @camera: A Camera.
 * @cleft: Left view of camera.
 *
 * Sets left of camera view.
 */
void
crank_camera_set_left (CrankCamera *camera,
                       const gfloat cleft)
{
  camera->projection->left = cleft;

  crank_projection_update_matrix (camera->projection);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_LEFT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}



/**
 * crank_camera_get_right:
 * @camera: A Camera.
 *
 * Gets right of camera view.
 *
 * Returns: right view of camera.
 */
gfloat
crank_camera_get_right (CrankCamera *camera)
{
  return camera->projection->right;
}

/**
 * crank_camera_set_right:
 * @camera: A Camera.
 * @cright: Right view of camera.
 *
 * Sets right of camera view.
 */
void
crank_camera_set_right (CrankCamera *camera,
                        const gfloat cright)
{
  camera->projection->right = cright;

  crank_projection_update_matrix (camera->projection);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_RIGHT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}



/**
 * crank_camera_get_bottom:
 * @camera: A Camera.
 *
 * Gets bottom of camera view.
 *
 * Returns: left view of camera.
 */
gfloat
crank_camera_get_bottom (CrankCamera *camera)
{
  return camera->projection->bottom;
}

/**
 * crank_camera_set_bottom:
 * @camera: A Camera.
 * @cbottom: Bottom view of camera.
 *
 * Sets bottom of camera view.
 */
void
crank_camera_set_bottom (CrankCamera *camera,
                         const gfloat cbottom)
{
  camera->projection->bottom = cbottom;

  crank_projection_update_matrix (camera->projection);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_BOTTOM]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}



/**
 * crank_camera_get_top:
 * @camera: A Camera.
 *
 * Gets top of camera view.
 *
 * Returns: top view of camera.
 */
gfloat
crank_camera_get_top (CrankCamera *camera)
{
  return camera->projection->top;
}

/**
 * crank_camera_set_top:
 * @camera: A Camera.
 * @ctop: Top view of camera.
 *
 * Sets top of camera view.
 */
void
crank_camera_set_top (CrankCamera *camera,
                      const gfloat ctop)
{
  camera->projection->top = ctop;

  crank_projection_update_matrix (camera->projection);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_TOP]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}



/**
 * crank_camera_get_near:
 * @camera: A Camera.
 *
 * Gets near of camera view.
 *
 * Returns: Near view of camera.
 */
gfloat
crank_camera_get_near (CrankCamera *camera)
{
  return camera->projection->near;
}

/**
 * crank_camera_set_near:
 * @camera: A Camera.
 * @cnear: Near view of camera.
 *
 * Sets near of camera view.
 */
void
crank_camera_set_near (CrankCamera  *camera,
                       const gfloat  cnear)
{
  camera->projection->near = cnear;

  crank_projection_update_matrix (camera->projection);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_NEAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}



/**
 * crank_camera_get_far:
 * @camera: A Camera.
 *
 * Gets far of camera view.
 *
 * Returns: Far view of camera.
 */
gfloat
crank_camera_get_far (CrankCamera *camera)
{
  return camera->projection->far;
}

/**
 * crank_camera_set_far:
 * @camera: A Camera.
 * @cfar: Near view of camera.
 *
 * Sets near of camera view.
 */
void
crank_camera_set_far (CrankCamera  *camera,
                      const gfloat  cfar)
{
  camera->projection->far = cfar;

  crank_projection_update_matrix (camera->projection);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_FAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}



/**
 * crank_camera_get_matrix:
 * @camera: A Camera.
 * @mat: (out): A Matrix.
 *
 * Get projection matrix from camera.
 */
void
crank_camera_get_matrix (CrankCamera    *camera,
                         CrankMatFloat4 *mat)
{
  crank_mat_float4_copy (& camera->projection->matrix, mat);
}

/**
 * crank_camera_set_matrix:
 * @camera: A Camera.
 * @mat: A Matrix.
 *
 * Set projection matrix. See crank_projection_set_matrix() for detail.
 */
void
crank_camera_set_matrix (CrankCamera    *camera,
                         CrankMatFloat4 *mat)
{
  crank_projection_set_matrix (camera->projection, mat);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_PROJECTION_TYPE]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_LEFT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_RIGHT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_BOTTOM]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_TOP]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_NEAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_FAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}



//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_camera_ortho:
 * @camera: A Camera.
 * @left: left view of camera.
 * @right: Right view of camera.
 * @bottom: Bottom view of camera.
 * @top: Top view of camera.
 * @nval: Near view of camera.
 * @fval: Far view of camera.
 *
 * Sets camera's view as orthogonal view.
 *
 * It is preferable to set view properties through this function familes, as they
 * will set properties and emit GObject::notify() at once.
 */
void
crank_camera_ortho (CrankCamera  *camera,
                    const gfloat  left,
                    const gfloat  right,
                    const gfloat  bottom,
                    const gfloat  top,
                    const gfloat  nval,
                    const gfloat  fval)
{
  crank_projection_set_ortho (camera->projection,
                              left,
                              right,
                              bottom,
                              top,
                              nval,
                              fval);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_PROJECTION_TYPE]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_LEFT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_RIGHT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_BOTTOM]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_TOP]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_NEAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_FAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}


/**
 * crank_camera_frustum:
 * @camera: A Camera.
 * @left: left view of camera.
 * @right: Right view of camera.
 * @bottom: Bottom view of camera.
 * @top: Top view of camera.
 * @nval: Near view of camera.
 * @fval: Far view of camera.
 *
 * Sets camera's view as frustum view.
 *
 * It is preferable to set view properties through this function familes, as they
 * will set properties and emit GObject::notify() at once.
 */
void
crank_camera_frustum (CrankCamera  *camera,
                      const gfloat  left,
                      const gfloat  right,
                      const gfloat  bottom,
                      const gfloat  top,
                      const gfloat  nval,
                      const gfloat  fval)
{
  crank_projection_set_frustum (camera->projection,
                                left,
                                right,
                                bottom,
                                top,
                                nval,
                                fval);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_PROJECTION_TYPE]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_LEFT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_RIGHT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_BOTTOM]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_TOP]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_NEAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_FAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}


/**
 * crank_camera_perspective:
 * @camera: A Camera.
 * @fovy: Field of view in screen y.
 * @aspect: Aspect ratio of x to y which is (X / Y)
 * @nval: Near view of camera.
 * @fval: Far view of camera.
 *
 * Sets camera's view as orthogonal view.
 *
 * It is preferable to set view properties through this function familes, as they
 * will set properties and emit GObject::notify() at once.
 */
void
crank_camera_perspective (CrankCamera  *camera,
                          const gfloat  fovy,
                          const gfloat  aspect,
                          const gfloat  nval,
                          const gfloat  fval)
{
  crank_projection_set_perspective (camera->projection,
                                    fovy,
                                    aspect,
                                    nval,
                                    fval);

  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_PROJECTION_TYPE]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_LEFT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_RIGHT]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_BOTTOM]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_TOP]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_NEAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_FAR]);
  g_object_notify_by_pspec ((GObject*)camera, pspecs[PROP_MATRIX]);
}
