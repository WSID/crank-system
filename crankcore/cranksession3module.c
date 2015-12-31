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
#include "cranksession3.h"
#include "cranksession3module.h"


/**
 * SECTION: cranksession3module
 * @title: CrankSession3Module
 * @short_description: Base class for modulized logic of CrankSession3
 * @stability: unstable
 * @include: crankcore.h
 *
 * A CrankSession3Module represents modulized common logic for #CrankSession3.
 * This may be rendering system so that, it can render #CrankEntity3 in the
 * sessions. Or it may be physics system so that it can perform simulations.
 */

//////// Default implementations ///////////////////////////////////////////////

static void crank_session3_module_def_session_init (CrankSession3Module  *self,
                                                    CrankSession3        *session,
                                                    GError              **error);

static void crank_session3_module_def_tick (CrankSession3Module *self);



//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSession3ModulePrivate
{
  CrankSession3 *session;
} CrankSession3ModulePrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankSession3Module,
                                     crank_session3_module,
                                     G_TYPE_OBJECT)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session3_module_init (CrankSession3Module *self)
{

}

static void
crank_session3_module_class_init (CrankSession3ModuleClass *c)
{
  c->session_init = crank_session3_module_def_session_init;
  c->tick = crank_session3_module_def_tick;
}



static void
{
}

//////// Default implementations ///////////////////////////////////////////////

static void
crank_session3_module_def_session_init (CrankSession3Module  *self,
                                        CrankSession3        *session,
                                        GError              **error)
{
  CrankSession3ModulePrivate *priv = crank_session3_module_get_instance_private (self);
  priv->session = session;
}

static void
crank_session3_module_def_tick (CrankSession3Module *self)
{
  return;  // Does nothing on every tick.
}



//////// Common ////////////////////////////////////////////////////////////////

/**
 * crank_session3_module_session_init:
 * @module: A Module.
 * @session: A Session.
 * @error: Error.
 *
 * Initialize a module for session.
 */
void
crank_session3_module_session_init (CrankSession3Module *module,
                                    CrankSession3       *session,
                                    GError             **error)
{
  CrankSession3ModuleClass *c = CRANK_SESSION3_MODULE_GET_CLASS (module);

  c->session_init (module, session, error);
}

/**
 * crank_session3_module_tick:
 * @module: A Module.
 *
 * Performs single tick action, for example, iterate physics simulation, or
 * rendering scene on a surface.
 */
void
crank_session3_module_tick (CrankSession3Module *module)
{
  CrankSession3ModuleClass *c = CRANK_SESSION3_MODULE_GET_CLASS (module);

  c->tick (module);
}

/**
 * crank_session3_module_is_initialized:
 * @module: A Module
 *
 * Check whether it is initialized for a session.
 *
 * An alternative way to check is crank_session3_module_get_session(), which
 * will return #CrankSession3 which the module is initialized for.
 */
gboolean
crank_session3_module_is_initialized (CrankSession3Module *module)
{
  CrankSession3ModulePrivate *priv = crank_session3_module_get_instance_private (module);

  return (priv->session != NULL);
}

/**
 * crank_session3_module_get_session:
 * @module: A Module.
 *
 * Gets the session that the @module is initialized for.
 *
 * Returns: (transfer none) (nullable): The session that this module is initialized for.
 */
CrankSession3*
crank_session3_module_get_session (CrankSession3Module *module)
{
  CrankSession3ModulePrivate *priv = crank_session3_module_get_instance_private (module);

  return priv->session;
}