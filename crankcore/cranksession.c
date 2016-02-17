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

#define CRANKCORE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

#include "cranksession.h"
#include "cranksessionmodule.h"

/**
 * SECTION: cranksession
 * @title: CrankSession
 * @short_description: Base Class for game session
 * @stability: unstable
 * @include: crankcore.h
 *
 * #CrankSession represents a single game session.
 *
 * # Uptime
 *
 * Every session has uptime property, which means how long user has interacted to
 * the session. In other words, this is play time. If the session is serializable,
 * up time should be recovered when session is deserialized.
 *
 * Uptime timer can be paused and resumed by crank_session_pause() and
 * crank_session_resume().
 */



//////// Properties and signals ////////////////////////////////////////////////

enum {
  RROP_0,

  PROP_INITIALIZED,

  PROP_RUNNING,
  PROP_UPTIME,

  PROP_COUNTS
};

static guint SIG_RESUME = 0;
static guint SIG_PAUSE = 0;

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// List of VFuncs ////////////////////////////////////////////////////////

static void crank_session_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec);

static void crank_session_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *psepc);

static gboolean crank_session_add_compositable (CrankComposite     *composite,
                                                CrankCompositable  *compositable,
                                                GError            **error);

static gboolean crank_session_remove_compositable (CrankComposite     *composite,
                                                   CrankCompositable  *compositable,
                                                   GError            **error);


static void crank_session_def_resume (CrankSession *session);

static void crank_session_def_pause (CrankSession *session);


//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSessionPrivate {
  GPtrArray    *modules;

  gboolean      running;

  gfloat        uptime_base;
  GTimer       *uptime_timer;

} CrankSessionPrivate;

G_DEFINE_TYPE_WITH_CODE (CrankSession,
                         crank_session,
                         CRANK_TYPE_COMPOSITE,
                         {
                          G_ADD_PRIVATE (CrankSession)
                         })



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session_init (CrankSession *session)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  priv->modules = g_ptr_array_new_with_free_func (g_object_unref);

  priv->uptime_timer = g_timer_new ();
}

static void
crank_session_class_init (CrankSessionClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankCompositeClass *c_composite = CRANK_COMPOSITE_CLASS (c);

  c_gobject->get_property = crank_session_get_property;
  c_gobject->set_property = crank_session_set_property;

  pspecs[PROP_RUNNING] = g_param_spec_boolean ("running", "Running",
                                               "Running",
                                               FALSE,
                                               G_PARAM_READWRITE |
                                               G_PARAM_STATIC_STRINGS );

  pspecs[PROP_UPTIME] = g_param_spec_float ("uptime", "Uptime",
                                            "Uptime",
                                            0, G_MAXFLOAT, 0,
                                            G_PARAM_READWRITE |
                                            G_PARAM_EXPLICIT_NOTIFY |
                                            G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  /**
   * CrankSession::resume:
   *
   * Emitted when session is starting or resuming.
   */
  SIG_RESUME = g_signal_new ("resume",
                             CRANK_TYPE_SESSION,
                             G_SIGNAL_RUN_LAST,
                             G_STRUCT_OFFSET (CrankSessionClass, resume),
                             NULL, NULL,
                             NULL,
                             G_TYPE_NONE,
                             0);

  /**
   * CrankSession::pause:
   *
   * Emitted when session is pausing or finishing.
   */
  SIG_PAUSE = g_signal_new ("pause",
                             CRANK_TYPE_SESSION,
                             G_SIGNAL_RUN_LAST,
                             G_STRUCT_OFFSET (CrankSessionClass, pause),
                             NULL, NULL,
                             NULL,
                             G_TYPE_NONE,
                             0);

  c_composite->add_compositable = crank_session_add_compositable;
  c_composite->remove_compositable = crank_session_remove_compositable;


  c->resume = crank_session_def_resume;
  c->pause = crank_session_def_pause;
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_session_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  CrankSession *session = (CrankSession*)object;

  switch (prop_id)
    {
    case PROP_RUNNING:
      g_value_set_boolean (value,
                           crank_session_is_running (session));
      break;

    case PROP_UPTIME:
      g_value_set_float (value,
                         crank_session_get_uptime (session));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_session_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  CrankSession *session = (CrankSession*)object;


  switch (prop_id)
    {
    case PROP_RUNNING:
      crank_session_set_running (session, g_value_get_boolean (value));
      break;

    case PROP_UPTIME:
      crank_session_set_uptime (session, g_value_get_float (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}





//////// CrankComposite ////////////////////////////////////////////////////////

static gboolean
crank_session_add_compositable (CrankComposite     *composite,
                                CrankCompositable  *compositable,
                                GError            **error)
{
  CrankCompositeClass *pc = crank_session_parent_class;
  CrankSession *self = (CrankSession*) composite;
  CrankSessionPrivate *priv = crank_session_get_instance_private (self);

  if (priv->running)
    {
      g_set_error (error,
                   CRANK_COMPOSITE_ERROR,
                   CRANK_COMPOSITE_ERROR_REJECTED,
                   "Attempt to add compositable to running session.\n"
                   "  %s@%p : %s@%p",
                   G_OBJECT_TYPE_NAME (self), self,
                   G_OBJECT_TYPE_NAME (compositable), compositable);
      return FALSE;
    }

  return pc->add_compositable (composite, compositable, error);
}


static gboolean
crank_session_remove_compositable (CrankComposite     *composite,
                                   CrankCompositable  *compositable,
                                   GError            **error)
{
  CrankCompositeClass *pc = crank_session_parent_class;
  CrankSession *self = (CrankSession*) composite;
  CrankSessionPrivate *priv = crank_session_get_instance_private (self);

  if (priv->running)
    {
      g_set_error (error,
                   CRANK_COMPOSITE_ERROR,
                   CRANK_COMPOSITE_ERROR_REJECTED,
                   "Attempt to remove compositable from running session.\n"
                   "  %s@%p : %s@%p",
                   G_OBJECT_TYPE_NAME (self), self,
                   G_OBJECT_TYPE_NAME (compositable), compositable);
      return FALSE;
    }

  return pc->remove_compositable (composite, compositable, error);
}



//////// Default implementations ///////////////////////////////////////////////

static void
crank_session_def_resume (CrankSession *session)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  priv->running = TRUE;
  g_timer_start (priv->uptime_timer);
}

static void
crank_session_def_pause (CrankSession *session)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  priv->running = FALSE;
  priv->uptime_base += (gfloat) g_timer_elapsed (priv->uptime_timer, NULL);
}




//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_session_new:
 *
 * Constructs new instance.
 *
 * Returns: (transfer full): Newly constructed instance.
 */
CrankSession*
crank_session_new (void)
{
  return (CrankSession*) g_object_new (CRANK_TYPE_SESSION,
                                       NULL);
}




//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_session_is_running:
 * @session: A Session.
 *
 * Gets whether @session is running or not.
 *
 * Returns: Whether the session is running or not.
 */
gboolean
crank_session_is_running (CrankSession *session)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  return priv->running;
}


/**
 * crank_session_set_running:
 * @session: A Session.
 * @running: Running.
 *
 * Sets whether @session is running or not. this may emit #CrankSession::resume
 * or #CrankSession::pause
 */
void
crank_session_set_running (CrankSession   *session,
                           const gboolean  running)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  if (! priv->running)
    {
      if (running)
        crank_session_resume (session);
    }
  else
    {
      if (! running)
        crank_session_pause (session);
    }
}

/**
 * crank_session_get_uptime:
 * @session: A Session.
 *
 * Gets uptime of session.
 *
 * Returns: Uptime of the session.
 */
gfloat
crank_session_get_uptime (CrankSession *session)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);
  gfloat uptime = (gfloat) priv->uptime_base;

  if (priv->running)
    uptime += (gfloat) g_timer_elapsed (priv->uptime_timer, NULL);

  return uptime;
}

/**
 * crank_session_set_uptime:
 * @session: A Session.
 * @uptime: Uptime of session.
 *
 * Sets uptime of session. This is mainly for serializable sessions, to restore
 * uptime from file.
 *
 * You may not set uptime while session is running.
 */
void
crank_session_set_uptime (CrankSession *session,
                          const gfloat  uptime)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  if (priv->running)
    g_warning ("Setting uptime while it is running.");

  else
    priv->uptime_base = uptime;
}



//////// Objects ///////////////////////////////////////////////////////////////

/**
 * crank_session_resume:
 * @session: A Session
 *
 * Runs or resume session.
 *
 * When overriden, it should chain up from parent.
 */
void
crank_session_resume (CrankSession *session)
{
  g_signal_emit (session, SIG_RESUME, 0, NULL);

  if (! G_PRIVATE_FIELD (CrankSession, session, gboolean, running))
    g_error ("crank_session_resume: Chain up required: %s", G_OBJECT_TYPE_NAME (session));
}

/**
 * crank_session_pause:
 * @session: A Session.
 *
 * Pauses a session.
 *
 * When overriden, it should chain up from parent.
 */
void
crank_session_pause (CrankSession *session)
{
  g_signal_emit (session, SIG_PAUSE, 0, NULL);

  if (G_PRIVATE_FIELD (CrankSession, session, gboolean, running))
    g_error ("crank_session_pause: Chain up required: %s", G_OBJECT_TYPE_NAME (session));
}
