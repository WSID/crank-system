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
 * # Modules
 *
 *
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
  PROP_N_MODULES,

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


static void crank_session_def_resume (CrankSession *session);

static void crank_session_def_pause (CrankSession *session);


//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSessionPrivate {
  gboolean      initialized;
  GPtrArray    *modules;

  gboolean      running;

  gfloat        uptime_base;
  GTimer       *uptime_timer;

} CrankSessionPrivate;

G_DEFINE_TYPE_WITH_CODE (CrankSession,
                         crank_session,
                         G_TYPE_OBJECT,
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

  c_gobject->get_property = crank_session_get_property;
  c_gobject->set_property = crank_session_set_property;

  pspecs[PROP_INITIALIZED] = g_param_spec_boolean ("initialized", "Initialized",
                                                   "Whether this session is initialized",
                                                   FALSE,
                                                   G_PARAM_READABLE |
                                                   G_PARAM_STATIC_STRINGS );

  pspecs[PROP_N_MODULES] = g_param_spec_uint ("n-modules", "Number of modules",
                                              "Number of modules.",
                                              0, G_MAXUINT, 0,
                                              G_PARAM_READABLE |
                                              G_PARAM_STATIC_STRINGS );

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
    case PROP_INITIALIZED:
      g_value_set_boolean (value,
                           crank_session_is_initialized (session));
      break;

    case PROP_N_MODULES:
      g_value_set_uint (value,
                        crank_session_get_n_modules (session));
      break;

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
 * crank_session_is_initialized:
 * @session: A Session.
 *
 * Checks whether it is initialized or not.
 *
 * Returns: Whether it is initialized.
 */
gboolean
crank_session_is_initialized (CrankSession *session)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  return priv->initialized;
}


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
        {
          if (! priv->initialized)
            g_warning ("crank_session_set_running: Attempt to resume uninitialized session.");
          else
            crank_session_resume (session);
        }
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


//////// Modules ///////////////////////////////////////////////////////////////

/**
 * crank_session_add_module:
 * @session: Session to add module.
 * @module: (transfer none): A Module.
 *
 * Adds a module to session. Already initialized session cannot add a module.
 */
void
crank_session_add_module (CrankSession       *session,
                          CrankSessionModule *module)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  if (crank_session_module_is_initialized (module))
    g_warning ("crank_session_add_module: Attempt to add already initialized module.");
  else if (priv->initialized)
    g_warning ("crank_session_add_module: Attempt to add module to initialized session.");
  else
    g_ptr_array_add (priv->modules, g_object_ref (module));
}

/**
 * crank_session_remove_module:
 * @session: Session to add module.
 * @module: (transfer none): A Module.
 *
 * Removes a module from session. Already initialized session cannot remove a module.
 */
void
crank_session_remove_module (CrankSession       *session,
                             CrankSessionModule *module)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  if (crank_session_module_is_initialized (module))
    g_warning ("crank_session_remove_module: Attempt to remove already initialized module.");
  else if (priv->initialized)
    g_warning ("crank_session_remove_module: Attempt to remove module to initialized session.");
  else
    g_ptr_array_remove (priv->modules, module);
}

/**
 * crank_session_get_n_modules:
 * @session: A Session.
 *
 * Gets number of modules in session.
 *
 * Returns: Number of modules in session.
 */
guint
crank_session_get_n_modules (CrankSession *session)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  return priv->modules->len;
}

/**
 * crank_session_get_module:
 * @session: A Session.
 * @index: Index of module.
 *
 * Gets module at index.
 *
 * Returns: (transfer none): Module in the session.
 */
CrankSessionModule*
crank_session_get_module (CrankSession *session,
                          const guint   index)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  return (CrankSessionModule*) priv->modules->pdata[index];
}

/**
 * crank_session_index_of_module:
 * @session: A Session.
 * @module: (transfer none): A Module.
 *
 * Gets index of a module in this session.
 *
 * Returns: index of a module, or -1 if it does not belongs to session.
 */
gint
crank_session_index_of_module (CrankSession       *session,
                               CrankSessionModule *module)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);
  guint i;

  for (i = 0; i < priv->modules->len; i++)
    {
      if (module == priv->modules->pdata[i])
        return i;
    }
  return -1;
}

/**
 * crank_session_get_module_by_gtype:
 * @session: A Session.
 * @gtype: GType of module. should be descendant of %CRANK_TYPE_SESSION_MODULE
 *
 * Gets a module with given @gtype or one of its descendants.
 *
 * Returns: (transfer none) (nullable): A Module or %NULL if not found.
 */
CrankSessionModule*
crank_session_get_module_by_gtype (CrankSession *session,
                                   const GType   gtype)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);
  guint i;

  for (i = 0; i < priv->modules->len; i++)
    {
      if (gtype == G_OBJECT_TYPE (priv->modules->pdata[i]))
        return priv->modules->pdata[i];
    }
  return NULL;
}


/**
 * crank_session_index_of_module_by_gtype:
 * @session: A Session.
 * @gtype: GType of module. should be descendant of %CRANK_TYPE_SESSION_MODULE
 *
 * Gets index of module with given @gtype or one of its descendants.
 *
 * Returns: Index of a module or -1 if not found.
 */
gint
crank_session_index_of_module_by_gtype (CrankSession *session,
                                        const GType   gtype)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);
  guint i;

  for (i = 0; i < priv->modules->len; i++)
    {
      if (gtype == G_OBJECT_TYPE (priv->modules->pdata[i]))
        return i;
    }
  return -1;
}


/**
 * crank_session_foreach_modules:
 * @session: A Session.
 * @func: (scope call): A Function.
 * @userdata: (closure func): Userdata for @func.
 *
 * Iterates @func over modules in the session.
 */
void
crank_session_foreach_modules (CrankSession *session,
                               GFunc         func,
                               gpointer      userdata)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  g_ptr_array_foreach (priv->modules, func, userdata);
}

/**
 * crank_session_init_modules:
 * @session: A Session.
 * @error: Error.
 *
 * Initialize a session with modules.
 */
void
crank_session_init_modules (CrankSession  *session,
                            GError       **error)
{
  CrankSessionPrivate *priv = crank_session_get_instance_private (session);

  if (! priv->initialized)
    {
      GError *merr = NULL;
      guint i;

      for (i = 0; i < priv->modules->len; i++)
        {
          CrankSessionModule *module;
          module = (CrankSessionModule*) priv->modules->pdata[i];

          crank_session_module_session_init (module, session, &merr);

          if (merr != NULL)
            {
              g_propagate_prefixed_error (error, merr, "crank_session_init_modules: ");
              // Fini
            }
        }

      priv->initialized = TRUE;
    }
  else
    {
      g_warning ("crank_session_init_module: Attempt to initialize already initialized session.");
    }
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
  if (! crank_session_is_initialized (session))
    {
      g_warning ("crank_session_resume: Attempt to resume uninitialized session.");
      return;
    }

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
