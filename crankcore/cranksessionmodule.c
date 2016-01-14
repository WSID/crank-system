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

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"
#include "cranksessionmodule.h"


/**
 * SECTION: cranksessionmodule
 * @title: CrankSessionModule
 * @short_description: Base class for modulized logic of CrankSession
 * @stability: unstable
 * @include: crankcore.h
 *
 * A CrankSessionModule represents modulized common logic for #CrankSession.
 */


//////// List of Virtual Functions /////////////////////////////////////////////

static void crank_session_module_get_property (GObject    *object,
                                               guint       prop_id,
                                               GValue     *value,
                                               GParamSpec *pspec);


//////// Default implementations ///////////////////////////////////////////////

static void crank_session_module_def_session_init (CrankSessionModule  *self,
                                                   CrankSession        *session,
                                                   GError             **error);




//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_INITIALIZED,
  PROP_SESSION,
  PROP_SESSION_INDEX,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSessionModulePrivate
{
  CrankSession *session;
  guint         session_index;
} CrankSessionModulePrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankSessionModule,
                                     crank_session_module,
                                     G_TYPE_OBJECT)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session_module_init (CrankSessionModule *self)
{
}

static void
crank_session_module_class_init (CrankSessionModuleClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_session_module_get_property;

  pspecs[PROP_INITIALIZED] =
  g_param_spec_boolean ("initialized", "initialized",
                        "Whether it is initialized",
                        FALSE,
                        G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_SESSION] =
  g_param_spec_object ("session", "Session",
                       "Session that it is initialized for",
                       CRANK_TYPE_SESSION,
                       G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_SESSION_INDEX] =
  g_param_spec_uint ("session-index", "Session Index",
                     "Index of this module in the session.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  c->session_init = crank_session_module_def_session_init;
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_session_module_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  CrankSessionModule *module = (CrankSessionModule*) object;

  switch (prop_id)
    {
    case PROP_INITIALIZED:
      g_value_set_boolean (value,
                           crank_session_module_is_initialized (module));
      break;

    case PROP_SESSION:
      g_value_set_object (value,
                          crank_session_module_get_session (module));
      break;

    case PROP_SESSION_INDEX:
      g_value_set_uint (value,
                        crank_session_module_get_session_index (module));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


//////// Default implementations ///////////////////////////////////////////////

static void
crank_session_module_def_session_init (CrankSessionModule  *self,
                                       CrankSession        *session,
                                       GError             **error)
{
  CrankSessionModulePrivate *priv = crank_session_module_get_instance_private (self);
  priv->session = session;
  priv->session_index = crank_session_index_of_module (session, self);
}


//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_session_module_is_initialized:
 * @module: A Module
 *
 * Check whether it is initialized for a session.
 *
 * An alternative way to check is crank_session_module_get_session(), which
 * will return #CrankSession which the module is initialized for.
 */
gboolean
crank_session_module_is_initialized (CrankSessionModule *module)
{
  CrankSessionModulePrivate *priv = crank_session_module_get_instance_private (module);

  return (priv->session != NULL);
}

/**
 * crank_session_module_get_session:
 * @module: A Module.
 *
 * Gets the session that the @module is initialized for.
 *
 * Returns: (transfer none) (nullable): The session that this module is initialized for.
 */
CrankSession*
crank_session_module_get_session (CrankSessionModule *module)
{
  CrankSessionModulePrivate *priv = crank_session_module_get_instance_private (module);

  return priv->session;
}

/**
 * crank_session_module_get_session_index:
 * @module: A Module.
 *
 * Gets index of this module for the session. This is only available when this
 * module is initialized for session.
 *
 * Returns: Index of this module in the sessions.
 */
guint
crank_session_module_get_session_index (CrankSessionModule *module)
{
  CrankSessionModulePrivate *priv = crank_session_module_get_instance_private (module);

  return priv->session_index;
}




//////// Session Initialization ////////////////////////////////////////////////

/**
 * crank_session_module_session_init:
 * @module: A Module.
 * @session: A Session.
 * @error: Error.
 *
 * Initialize a module for session.
 */
void
crank_session_module_session_init (CrankSessionModule  *module,
                                   CrankSession        *session,
                                   GError             **error)
{
  CrankSessionModuleClass *c = CRANK_SESSION_MODULE_GET_CLASS (module);

  c->session_init (module, session, error);
}
