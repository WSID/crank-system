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

/**
 * SECTION: cranksessionmoduletick
 * @title: CrankSessionModuleTick
 * @short_description: Ticking module with interval.
 * @stability: Unstable
 * @include: crankcore.h
 *
 * This module provides ticking function for other modules.
 *
 * # CrankSessionModuleTick as #CrankCompositable
 *
 * Composite Requisition: #CrankSession
 */

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"
#include "cranksessionmoduletick.h"


//////// List of virtual functions /////////////////////////////////////////////

static void crank_session_module_tick_get_property (GObject    *object,
                                                    guint       prop_id,
                                                    GValue     *value,
                                                    GParamSpec *pspec);

static void crank_session_module_tick_set_property (GObject      *object,
                                                    guint         prop_id,
                                                    const GValue *value,
                                                    GParamSpec   *pspec);

static void crank_session_module_tick_dispose (GObject *object);


static gboolean crank_session_module_tick_adding (CrankCompositable  *compositable,
                                                  CrankComposite     *composite,
                                                  GError            **error);

static gboolean crank_session_module_tick_removing(CrankCompositable  *compositable,
                                                   CrankComposite     *composite,
                                                   GError            **error);



//////// Private functions /////////////////////////////////////////////////////

static void crank_session_module_tick_build_source (CrankSessionModuleTick *module);

static void crank_session_module_tick_destroy_source (CrankSessionModuleTick *module);

static void crank_session_module_tick_rebuild_source (CrankSessionModuleTick *module);

static gboolean crank_session_module_tick_real_tick (gpointer userdata);


//////// Property and signals //////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_TICK_CONTEXT,
  PROP_TICK_INTERVAL,

  PROP_COUNTS
};

static guint sig_tick;

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankSessionModuleTick {
  CrankCompositable _parent;

  GMainContext *tick_context;
  guint         tick_interval;

  GSource      *tick_source;
};

G_DEFINE_TYPE (CrankSessionModuleTick,
               crank_session_module_tick,
               CRANK_TYPE_COMPOSITABLE)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session_module_tick_init (CrankSessionModuleTick *self)
{
  self->tick_context = g_main_context_ref (g_main_context_default ());
}

static void
crank_session_module_tick_class_init (CrankSessionModuleTickClass *c)
{
  GObjectClass *c_gobject;
  CrankCompositableClass *c_compositable;

  c_gobject = G_OBJECT_CLASS (c);
  c_gobject->get_property = crank_session_module_tick_get_property;
  c_gobject->set_property = crank_session_module_tick_set_property;
  c_gobject->dispose = crank_session_module_tick_dispose;

  pspecs[PROP_TICK_CONTEXT] = g_param_spec_boxed ("tick-context", "Ticking Main Context",
                                                  "Ticking main context that execute tick functions",
                                                  G_TYPE_MAIN_CONTEXT,
                                                  G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  pspecs[PROP_TICK_INTERVAL] = g_param_spec_uint ("tick-interval", "Ticking interval",
                                                  "Ticking interval in microseconds.",
                                                  0, G_MAXUINT, 0,
                                                  G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_compositable = CRANK_COMPOSITABLE_CLASS (c);

  c_compositable->adding = crank_session_module_tick_adding;
  c_compositable->removing = crank_session_module_tick_removing;

  crank_compositable_class_add_requisition (c_compositable,
                                            CRANK_TYPE_SESSION);

  /**
   * CrankSessionModuleTick::tick:
   *
   * Performs single tick.
   *
   * Emitted on each tick. Other modules can connect to this signal to perform
   * per-tick tasks.
   */
  sig_tick = g_signal_new ("tick", CRANK_TYPE_SESSION_MODULE_TICK,
                           G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION ,
                           0,
                           NULL, NULL,
                           g_cclosure_marshal_VOID__VOID,
                           G_TYPE_NONE,
                           0);
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_session_module_tick_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
  CrankSessionModuleTick *module = (CrankSessionModuleTick*) object;

  switch (prop_id)
    {
    case PROP_TICK_CONTEXT:
      g_value_set_boxed (value, crank_session_module_tick_get_tick_context (module));
      break;

    case PROP_TICK_INTERVAL:
      g_value_set_uint (value, crank_session_module_tick_get_tick_interval (module));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_session_module_tick_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
  CrankSessionModuleTick *module = (CrankSessionModuleTick*) object;

  switch (prop_id)
    {
    case PROP_TICK_CONTEXT:
      crank_session_module_tick_set_tick_context (module,
                                                  (GMainContext*) g_value_get_boxed (value));
      break;

    case PROP_TICK_INTERVAL:
      crank_session_module_tick_set_tick_interval(module,
                                                  g_value_get_uint (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
crank_session_module_tick_dispose (GObject *object)
{
  CrankSessionModuleTick *module = (CrankSessionModuleTick*) object;

  if (module->tick_source != NULL)
    {
      g_source_destroy (module->tick_source);
      g_source_unref (module->tick_source);
      module->tick_source = NULL;
    }

  g_main_context_unref (module->tick_context);
  module->tick_context= NULL;
}


//////// CrankCompositable /////////////////////////////////////////////////////

static gboolean
crank_session_module_tick_adding (CrankCompositable  *compositable,
                                  CrankComposite     *composite,
                                  GError            **error)
{
  CrankCompositableClass *pc;
  pc = crank_session_module_tick_parent_class;

  if (! pc->adding (compositable, composite, error))
    return FALSE;

  g_signal_connect_swapped (composite, "resume",
                            (GCallback)crank_session_module_tick_build_source, compositable);

  g_signal_connect_swapped (composite, "pause",
                            (GCallback)crank_session_module_tick_destroy_source, compositable);

  return TRUE;
}

static gboolean
crank_session_module_tick_removing (CrankCompositable  *compositable,
                                    CrankComposite     *composite,
                                    GError            **error)
{
  CrankCompositableClass *pc;
  pc = crank_session_module_tick_parent_class;

  if (! pc->removing (compositable, composite, error))
    return FALSE;

  g_signal_handlers_disconnect_by_data (composite, compositable);

  return TRUE;
}



//////// Private functions /////////////////////////////////////////////////////

static void
crank_session_module_tick_build_source (CrankSessionModuleTick *module)
{
  if ((module->tick_source == NULL) && (module->tick_context != NULL))
    {
      module->tick_source = g_timeout_source_new (module->tick_interval);

      g_source_set_callback (module->tick_source,
                             crank_session_module_tick_real_tick, module, NULL);

      g_source_attach (module->tick_source, module->tick_context);
    }
}

static void
crank_session_module_tick_destroy_source (CrankSessionModuleTick *module)
{
  if (module->tick_source != NULL)
    {
      g_source_destroy (module->tick_source);
      g_source_unref (module->tick_source);

      module->tick_source = NULL;
    }
}

static void
crank_session_module_tick_rebuild_source (CrankSessionModuleTick *module)
{
  if (module->tick_source != NULL)
    {
      crank_session_module_tick_destroy_source (module);
      crank_session_module_tick_build_source (module);
    }
}

static gboolean
crank_session_module_tick_real_tick (gpointer userdata)
{
  g_signal_emit (userdata, sig_tick, 0);
  return TRUE;
}




//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_session_module_tick_new:
 * @tick_interval: Tick interval.
 *
 * Constructs an instance with tick interval.
 *
 * Returns: (transfer full): Newly constructed instance.
 */
CrankSessionModuleTick*
crank_session_module_tick_new (const guint tick_interval)
{
  return (CrankSessionModuleTick*) g_object_new (CRANK_TYPE_SESSION_MODULE_TICK,
                                                 "tick-interval",
                                                 tick_interval,
                                                 NULL);
}



//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_session_module_tick_get_tick_context:
 * @module: A Module.
 *
 * Gets a #GMainContext that performs tick.
 *
 * Returns: (transfer none): Ticking context.
 */
GMainContext*
crank_session_module_tick_get_tick_context (CrankSessionModuleTick *module)
{
  return module->tick_context;
}

/**
 * crank_session_module_tick_set_tick_context:
 * @module: A Module.
 * @tick_context: (transfer none) (nullable): Ticking Context.
 *
 * Sets a #GMainContext to perform tick.
 */
void
crank_session_module_tick_set_tick_context (CrankSessionModuleTick *module,
                                            GMainContext           *tick_context)
{
  if (tick_context == NULL)
    tick_context = g_main_context_default ();

  if (module->tick_context != tick_context)
    {
      g_main_context_unref (module->tick_context);
      module->tick_context = g_main_context_ref (tick_context);

      crank_session_module_tick_rebuild_source (module);

      g_object_notify_by_pspec ((GObject*)module, pspecs[PROP_TICK_CONTEXT]);
    }
}



/**
 * crank_session_module_tick_get_tick_interval:
 * @module: A Module.
 *
 * Gets ticking interval of this module, in milliseconds.
 *
 * Returns: ticking interval in milliseconds.
 */
guint
crank_session_module_tick_get_tick_interval (CrankSessionModuleTick *module)
{
  return module->tick_interval;
}

/**
 * crank_session_module_tick_set_tick_interval:
 * @module: A Module.
 * @tick_interval: Ticking interval.
 *
 * Sets ticking interval of this module.
 */
void
crank_session_module_tick_set_tick_interval (CrankSessionModuleTick *module,
                                             const guint             tick_interval)
{
  if (module->tick_interval != tick_interval)
    {
      module->tick_interval = tick_interval;
      crank_session_module_tick_rebuild_source (module);
      g_object_notify_by_pspec ((GObject*) module, pspecs[PROP_TICK_INTERVAL]);
    }
}


/**
 * crank_session_module_tick_tick:
 * @module: A Module.
 *
 * Ticks once. See CrankSessionModuleTick::tick
 */
void
crank_session_module_tick_tick (CrankSessionModuleTick *module)
{
  g_signal_emit (module, sig_tick, 0);
}
