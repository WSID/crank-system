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
 * SECTION: cranksessionmodulesimtimed
 * @title: CrankSessionModuleSimTimed
 * @short_description: Session module for simulated time.
 * @stability: Unstable
 * @include: crankcore.h
 *
 * This module provides functionality to manage in-game simulated time, for
 * turn-based or real-time sessions.
 */

#define CRANKCORE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "cranksession.h"
#include "cranksessionmodule.h"
#include "cranksessionmodulesimtimed.h"

//////// List of virtual functions /////////////////////////////////////////////

static void crank_session_module_sim_timed_get_property (GObject    *object,
                                                         guint       prop_id,
                                                         GValue     *value,
                                                         GParamSpec *pspec);

static void crank_session_module_sim_timed_set_property (GObject      *object,
                                                         guint         prop_id,
                                                         const GValue *value,
                                                         GParamSpec   *pspec);


static void crank_session_module_sim_timed_def_flow_time (CrankSessionModuleSimTimed *self,
                                                          const gfloat                time);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_SIM_TIME,
  PROP_SIM_STEPS,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


static guint sig_flow_time;


//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSessionModuleSimTimedPrivate
{
  gfloat  sim_time;
  guint   sim_steps;
} CrankSessionModuleSimTimedPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CrankSessionModuleSimTimed,
                            crank_session_module_sim_timed,
                            CRANK_TYPE_SESSION_MODULE)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session_module_sim_timed_init (CrankSessionModuleSimTimed* self)
{

}

static void
crank_session_module_sim_timed_class_init (CrankSessionModuleSimTimedClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);
  c_gobject->get_property = crank_session_module_sim_timed_get_property;
  c_gobject->set_property = crank_session_module_sim_timed_set_property;

  pspecs[PROP_SIM_TIME] = g_param_spec_float ("sim-time", "Simulate time",
                                              "Simulated time",
                                              0, G_MAXFLOAT, 0,
                                              G_PARAM_READWRITE |
                                              G_PARAM_EXPLICIT_NOTIFY |
                                              G_PARAM_STATIC_STRINGS );

  pspecs[PROP_SIM_STEPS] = g_param_spec_uint ("sim-steps", "Simulate steps",
                                              "Simulated steps",
                                              0, G_MAXUINT, 0,
                                              G_PARAM_READWRITE |
                                              G_PARAM_EXPLICIT_NOTIFY |
                                              G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  c->flow_time = crank_session_module_sim_timed_def_flow_time;

  /**
   * CrankSessionModuleSimTimed::flow-time:
   * @time: Time to flow.
   *
   * Performs flow time to this module. Other modules can connect to this signal
   * so that they can simulate for given time.
   */
  sig_flow_time = g_signal_new ("flow-time", CRANK_TYPE_SESSION_MODULE_SIM_TIMED,
                                G_SIGNAL_RUN_LAST,
                                G_STRUCT_OFFSET (CrankSessionModuleSimTimedClass, flow_time),
                                NULL, NULL,
                                NULL,
                                G_TYPE_NONE,
                                1, G_TYPE_FLOAT);
}





//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_session_module_sim_timed_get_property (GObject    *object,
                                             guint       prop_id,
                                             GValue     *value,
                                             GParamSpec *pspec)
{
  CrankSessionModuleSimTimed *module;
  module = (CrankSessionModuleSimTimed*) object;

  switch (prop_id)
    {
    case PROP_SIM_TIME:
      g_value_set_float (value,
                         crank_session_module_sim_timed_get_sim_time (module));
      break;

    case PROP_SIM_STEPS:
      g_value_set_uint (value,
                        crank_session_module_sim_timed_get_sim_steps (module));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_session_module_sim_timed_set_property (GObject    *object,
                                             guint       prop_id,
                                             const GValue     *value,
                                             GParamSpec *pspec)
{
  CrankSessionModuleSimTimed *module;
  module = (CrankSessionModuleSimTimed*) object;

  switch (prop_id)
    {
    case PROP_SIM_TIME:
      crank_session_module_sim_timed_set_sim_time (module,
                                                   g_value_get_float (value));
      break;

    case PROP_SIM_STEPS:
      crank_session_module_sim_timed_set_sim_steps (module,
                                                    g_value_get_uint (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}





//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_session_module_sim_timed_get_sim_time:
 * @module: A Module.
 *
 * Gets simulated time of @module.
 *
 * Returns: Simulated time.
 */
gfloat
crank_session_module_sim_timed_get_sim_time (CrankSessionModuleSimTimed *module)
{
  CrankSessionModuleSimTimedPrivate *priv;
  priv = crank_session_module_sim_timed_get_instance_private (module);

  return priv->sim_time;
}

/**
 * crank_session_module_sim_timed_set_sim_time:
 * @module: A Module.
 * @sim_time: Simultated time.
 *
 * Sets simulated time of @module. This is useful when rebuilding session with
 * saved state.
 */
void
crank_session_module_sim_timed_set_sim_time (CrankSessionModuleSimTimed *module,
                                             const gfloat                sim_time)
{
  CrankSessionModuleSimTimedPrivate *priv;
  priv = crank_session_module_sim_timed_get_instance_private (module);

  priv->sim_time = sim_time;
}

/**
 * crank_session_module_sim_timed_get_sim_steps:
 * @module: A Module.
 *
 * Gets simulated steps of @module. Generally, this is count of emission of
 * #CrankSessionModuleSimTimed:flow-time.
 *
 * Returns: Simulated steps of @module.
 */
guint
crank_session_module_sim_timed_get_sim_steps (CrankSessionModuleSimTimed *module)
{
  CrankSessionModuleSimTimedPrivate *priv;
  priv = crank_session_module_sim_timed_get_instance_private (module);

  return priv->sim_steps;
}

/**
 * crank_session_module_sim_timed_set_sim_steps:
 * @module: A Module.
 * @sim_steps: Simultated steps.
 *
 * Sets simulated steps of @module. This is useful when rebuilding session with
 * saved state.
 */
void
crank_session_module_sim_timed_set_sim_steps (CrankSessionModuleSimTimed *module,
                                              const guint                 sim_steps)
{
  CrankSessionModuleSimTimedPrivate *priv;
  priv = crank_session_module_sim_timed_get_instance_private (module);

  priv->sim_steps = sim_steps;
}





//////// CrankSessionModuleSimTimed ////////////////////////////////////////////

static void
crank_session_module_sim_timed_def_flow_time (CrankSessionModuleSimTimed *module,
                                              const gfloat                time)
{
  CrankSessionModuleSimTimedPrivate *priv;
  priv = crank_session_module_sim_timed_get_instance_private (module);

  priv->sim_time += time;
  priv->sim_steps ++;
}






//////// Functions /////////////////////////////////////////////////////////////

/**
 * crank_session_module_sim_timed_flow_time:
 * @module: A Module.
 * @time: A Time.
 *
 * Flow time for @module.
 */
void
crank_session_module_sim_timed_flow_time (CrankSessionModuleSimTimed *module,
                                          const gfloat                time)
{
  g_signal_emit (module, sig_flow_time, 0, time);
}

/**
 * crank_session_module_sim_timed_flow_time_n:
 * @module: A Module.
 * @time: A Time.
 * @step: Count of steps.
 *
 * Flow time for @module for @steps.
 */
void
crank_session_module_sim_timed_flow_time_n (CrankSessionModuleSimTimed *module,
                                            const gfloat                time,
                                            const guint                 step)
{
  guint i;
  for (i = 0; i < step; i++)
    crank_session_module_sim_timed_flow_time (module, time);
}


/**
 * crank_session_module_sim_timed_flow_time_till:
 * @module: A Module.
 * @till: Time to simulate.
 *
 * Flow time for @module, till @till.
 */
void
crank_session_module_sim_timed_flow_time_till (CrankSessionModuleSimTimed *module,
                                               const gfloat                till)
{
  gfloat now;

  now = crank_session_module_sim_timed_get_sim_time (module);

  if (now < till)
    crank_session_module_sim_timed_flow_time (module, till - now);
}

/**
 * crank_session_module_sim_timed_flow_time_till_n:
 * @module: A Module.
 * @till: Time to simulate.
 * @time: A Time step.
 *
 * Flow time for @module, till @till, step by step of interval @time.
 */
void
crank_session_module_sim_timed_flow_time_till_n (CrankSessionModuleSimTimed *module,
                                                 const gfloat                till,
                                                 const gfloat                time)
{
  gfloat now;
  guint steps;

  now = crank_session_module_sim_timed_get_sim_time (module);

  if (now < till)
    {
      steps = (guint) ((till - now) / time);
      crank_session_module_sim_timed_flow_time_n (module, time, steps);
    }
}
