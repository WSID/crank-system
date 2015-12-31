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
#include "cranksession3placemodule.h"

/**
 * SECTION: cranksession3placemodule
 * @title: CrankSession3PlaceModule
 * @short_description: Modulized logic that affects on places.
 * @stability: unstable
 * @include: crankcore.h
 *
 */

//////// List of virtual functions /////////////////////////////////////////////

static void crank_session3_place_module_get_property (GObject    *object,
                                                      guint       prop_id,
                                                      GValue     *value,
                                                      GParamSpec *pspec);

static void crank_session3_place_module_session_init (CrankSession3Module  *self,
                                                      CrankSession3        *session,
                                                      GError              **error);


//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_INDEX,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};

//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSession3PlaceModulePrivate
{
  guint   index;
} CrankSession3PlaceModulePrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CrankSession3PlaceModule,
                                     crank_session3_place_module,
                                     CRANK_TYPE_SESSION3_MODULE)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session3_place_module_init (CrankSession3PlaceModule *self)
{
  CrankSession3PlaceModulePrivate *priv = crank_session3_place_module_get_instance_private (self);

  priv->index = 0;
}

static void
crank_session3_place_module_class_init (CrankSession3PlaceModuleClass *c)
{
  GObjectClass *c_gobject;
  CrankSession3ModuleClass *c_session3module;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_session3_place_module_get_property;

  pspecs[PROP_INDEX] =
  g_param_spec_uint ("index", "index",
                     "Index of module in session.",
                     0, G_MAXUINT, 0,
                     G_PARAM_READABLE | G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

  c_session3module = CRANK_SESSION3_MODULE_CLASS (c);
  c_session3module->session_init = crank_session3_place_module_session_init;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_session3_place_module_get_property (GObject    *object,
                                          guint       prop_id,
                                          GValue     *value,
                                          GParamSpec *pspec)
{
  CrankSession3PlaceModule *module = (CrankSession3PlaceModule*) object;

  switch (prop_id)
    {
    case PROP_INDEX:
      g_value_set_uint (value,
                        crank_session3_place_module_get_index (module));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// CrankSession3Module ///////////////////////////////////////////////////

static void
crank_session3_place_module_session_init (CrankSession3Module  *self,
                                          CrankSession3        *session,
                                          GError              **error)
{
  CrankSession3ModuleClass *pc;
  CrankSession3PlaceModule *s;
  CrankSession3PlaceModulePrivate *priv;

  pc = (CrankSession3ModuleClass*)crank_session3_place_module_parent_class;
  pc->session_init (self, session, error);

  s = (CrankSession3PlaceModule*)self;
  priv = crank_session3_place_module_get_instance_private (s);

  priv->index = crank_session3_index_of_place_module (session, s);
}


//////// Public functions /////////////////////////////////////////////////////////

/**
 * crank_session3_place_module_get_index:
 * @module: A Module.
 *
 * Gets index of this module in the session. This will be available only when
 * it is initialized. Otherwise, it returns 0.
 *
 * Returns: index of this module, or 0 if it is not initialized.
 */
guint
crank_session3_place_module_get_index (CrankSession3PlaceModule *module)
{
  CrankSession3PlaceModulePrivate *priv = crank_session3_place_module_get_instance_private (module);

  return priv->index;
}


/**
 * crank_session3_place_module_attached_data:
 * @module: A Module.
 * @place: (transfer none): A Place that attached data.
 * @data: (transfer none): A data attached.
 *
 * This will be called when place data is attached to a #CrankPlace3.
 */
void
crank_session3_place_module_attached_data (CrankSession3PlaceModule *module,
                                           CrankPlace3              *place,
                                           GObject                  *data)
{
  CrankSession3PlaceModuleClass *c = CRANK_SESSION3_PLACE_MODULE_GET_CLASS (module);

  c->attached_data (module, place, data);
}

/**
 * crank_session3_place_module_detached_data:
 * @module: A Module.
 * @place: (transfer none): A Place that detached data.
 * @data: (transfer none): A data detached.
 *
 * This will be called when data is detached from a #CrankPlace3.
 */
void
crank_session3_place_module_detached_data (CrankSession3PlaceModule *module,
                                           CrankPlace3              *place,
                                           GObject                  *data)
{
  CrankSession3PlaceModuleClass *c = CRANK_SESSION3_PLACE_MODULE_GET_CLASS (module);

  c->detached_data (module, place, data);
}




