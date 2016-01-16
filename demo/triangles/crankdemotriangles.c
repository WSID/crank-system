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

/* This is Part of demo */

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>

#include <crankbase.h>
#include <crankcore.h>
#include <crankvisual.h>

#include "crankdemorenderabletriangle.h"

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_DEMO_TYPE_TRIANGLE_APP (crank_demo_triangle_app_get_type())
G_DECLARE_FINAL_TYPE (CrankDemoTriangleApp,
                      crank_demo_triangle_app,
                      CRANK_DEMO, TRIANGLE_APP,
                      GtkApplication)


//////// Constructor ///////////////////////////////////////////////////////////

CrankDemoTriangleApp *crank_demo_triangle_app_new (void);



//////// Main //////////////////////////////////////////////////////////////////

int main (int argc, char **argv)
{
  CrankDemoTriangleApp *app;

  if (gtk_clutter_init (NULL, NULL) != CLUTTER_INIT_SUCCESS)
    return -1;


  app = crank_demo_triangle_app_new ();

  return g_application_run ((GApplication*)app,
                            argc, argv);
}


//////// List of virtual functions /////////////////////////////////////////////

static void crank_demo_triangle_app_startup (GApplication *application);

static void crank_demo_triangle_app_activate (GApplication *application);


//////// Private functions /////////////////////////////////////////////////////

static void crank_demo_triangle_app_build_ui (CrankDemoTriangleApp *app,
                                              CoglContext          *cogl_context);

static void crank_demo_triangle_app_build_session (CrankDemoTriangleApp *app,
                                                   CoglContext          *cogl_context);

static void crank_demo_triangle_app_add_triangle (CrankDemoTriangleApp *app);


//////// Private Functions /////////////////////////////////////////////////////

static gboolean move_cam_pos (gpointer ptr)
{
  CrankEntity3* entity = (CrankEntity3*)ptr;

  CrankTrans3 pos;

  crank_entity3_get_position (entity, &pos);

  pos.mtrans.z += 0.01;

  crank_entity3_set_position (entity, &pos);

  return TRUE;
}


//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankDemoTriangleApp
{
  GtkApplication _parent;

  // UI Part
  GtkApplicationWindow *window;
  GtkClutterEmbed  *embed;
  ClutterStage     *stage;
  ClutterActor     *actor;


  // Session part.
  CrankSession3    *session;
  CrankRenderModule *rmodule;

  CrankPlace3       *place;
  CrankEntity3      *camera_hook;

  CrankDemoRenderableTriangle  *renderable;

  CrankCamera       *camera;
  CrankCameraContent *content;
  CrankFilm         *film;
};

G_DEFINE_TYPE (CrankDemoTriangleApp,
               crank_demo_triangle_app,
               GTK_TYPE_APPLICATION);


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_demo_triangle_app_init (CrankDemoTriangleApp *app)
{
}

static void
crank_demo_triangle_app_class_init (CrankDemoTriangleAppClass *c)
{
  GApplicationClass *c_gapplication;

  c_gapplication = G_APPLICATION_CLASS (c);

  c_gapplication->startup = crank_demo_triangle_app_startup;
  c_gapplication->activate = crank_demo_triangle_app_activate;
}



//////// GApplication //////////////////////////////////////////////////////////

static void
crank_demo_triangle_app_startup (GApplication *application)
{
  GApplicationClass *pc_gapplication;
  CrankDemoTriangleApp *app;
  ClutterBackend *backend;
  CoglContext *cogl_context;

  ClutterLayoutManager *layout;

  pc_gapplication = (GApplicationClass*) crank_demo_triangle_app_parent_class;

  pc_gapplication->startup (application);

  app = (CrankDemoTriangleApp*) application;


  //// CoglContext
  backend = clutter_get_default_backend ();
  cogl_context = clutter_backend_get_cogl_context (backend);

  crank_demo_triangle_app_build_ui (app, cogl_context);
  crank_demo_triangle_app_build_session (app, cogl_context);
}


static void
crank_demo_triangle_app_activate (GApplication *application)
{
  GApplicationClass *pc_gapplication;
  CrankDemoTriangleApp *app;

  pc_gapplication = (GApplicationClass*) crank_demo_triangle_app_parent_class;

  pc_gapplication->startup (application);

  app = (CrankDemoTriangleApp*) application;

  gtk_window_present ((GtkWindow*) app->window);

  crank_session_resume ((CrankSession*) app->session);
}


//////// Private functions /////////////////////////////////////////////////////

static void
crank_demo_triangle_app_build_ui (CrankDemoTriangleApp *app,
                                  CoglContext          *cogl_context)
{
  ClutterLayoutManager *layout;
  GError *error = NULL;

  app->window = (GtkApplicationWindow*)gtk_application_window_new ((GtkApplication*)app);
  app->embed =  (GtkClutterEmbed*) gtk_clutter_embed_new ();
  app->stage = (ClutterStage*) gtk_clutter_embed_get_stage (app->embed);
  app->actor = clutter_actor_new ();

  app->film = crank_film_new (cogl_context, 1024, 1024, &error);
  if (error != NULL)
    g_error ("Film cannot be initialized: %s", error->message);

  app->camera = (CrankCamera*) g_object_new (CRANK_TYPE_CAMERA,
                                             "film", app->film,
                                             NULL);

  app->content = (CrankCameraContent*) g_object_new (CRANK_TYPE_CAMERA_CONTENT,
                                                     "camera", app->camera,
                                                     NULL);


  layout = clutter_bin_layout_new (0, 0);
  clutter_actor_set_layout_manager ((ClutterActor*)app->stage, layout);

  // Add ui!
  gtk_container_add ((GtkContainer*) app->window,
                     (GtkWidget*) app->embed);

  clutter_actor_add_child ((ClutterActor*) app->stage,
                           app->actor);

  clutter_actor_set_x_align (app->actor, CLUTTER_ACTOR_ALIGN_FILL);
  clutter_actor_set_y_align (app->actor, CLUTTER_ACTOR_ALIGN_FILL);
  clutter_actor_set_x_expand (app->actor, TRUE);
  clutter_actor_set_y_expand (app->actor, TRUE);

  gtk_widget_show_all ((GtkWidget*) app->embed);
  clutter_actor_show ((ClutterActor*)app->actor);

  clutter_actor_set_content (app->actor, (ClutterContent*) app->content);
}

static void
crank_demo_triangle_app_build_session (CrankDemoTriangleApp *app,
                                       CoglContext          *cogl_context)
{
  app->session = (CrankSession3*) g_object_new (CRANK_TYPE_SESSION3,
                                                "tick-interval", 17,
                                                NULL);
  app->rmodule = (CrankRenderModule*) g_object_new (CRANK_TYPE_RENDER_MODULE, NULL);

  crank_session3_add_entity_module (app->session,
                                    (CrankSession3EntityModule*) app->rmodule);

  crank_session_init_modules (app->session, NULL);
  crank_session3_lock_and_init_modules (app->session, NULL);


  // Make entities.
  app->place = crank_session3_make_place (app->session);
  app->camera_hook = crank_session3_make_entity (app->session);

  app->renderable = crank_demo_renderable_triangle_new (cogl_context);

  // Add session!
  crank_place3_add_entity (app->place, app->camera_hook);
  crank_render_module_add_camera (app->rmodule, app->camera);
  crank_camera_set_entity (app->camera, app->camera_hook);

  for (int i = 0; i < 100; i++)
    crank_demo_triangle_app_add_triangle (app);

    {
      CrankTrans3 campos = {{0, 0, 0}, {1, 0, 0, 0}, 1};

      crank_entity3_set_position (app->camera_hook, &campos);
      crank_camera_perspective (app->camera, G_PI * 0.7, 1, 0.2, 1000);
    }

  g_timeout_add (17, move_cam_pos, app->camera_hook);
}

static void
crank_demo_triangle_app_add_triangle (CrankDemoTriangleApp *app)
{
  CrankEntity3 *entity = crank_session3_make_entity (app->session);

  CrankTrans3 pos = {{
    g_random_double_range (-100, 100),
    g_random_double_range (-100, 100),
    g_random_double_range (-100, 100)
  }, {
    g_random_double_range (-1, 1),
    g_random_double_range (-1, 1),
    g_random_double_range (-1, 1),
    g_random_double_range (-1, 1)
  }, g_random_double_range (0.5, 10)};

  crank_quat_float_unit_self (& pos.mrot);

  crank_entity3_attach_data (entity, 0, (GObject*) app->renderable);
  crank_entity3_set_position (entity, &pos);
  crank_place3_add_entity (app->place, entity);
}


//////// Constructors //////////////////////////////////////////////////////////

CrankDemoTriangleApp*
crank_demo_triangle_app_new (void)
{
  return (CrankDemoTriangleApp*) g_object_new (CRANK_DEMO_TYPE_TRIANGLE_APP,
                                               "application-id", "crank.demo.triangles",
                                               NULL);
}
