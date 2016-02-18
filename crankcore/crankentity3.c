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
#include "crankshape.h"
#include "cranksessionmoduleplaced.h"

#include "crankplace.h"
#include "crankentity.h"
#include "crankentity3.h"

//////// List of virtual functions /////////////////////////////////////////////

static void crank_entity3_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec);

static void crank_entity3_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec);





//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_POSITION,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};






//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_TYPE (CrankEntity3,
               crank_entity3,
               CRANK_TYPE_ENTITY)





//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_entity3_init (CrankEntity3 *self)
{
  crank_trans3_init (& self->position);
}


static void
crank_entity3_class_init (CrankEntity3Class *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_entity3_get_property;
  c_gobject->set_property = crank_entity3_set_property;


  pspecs[PROP_POSITION] =
  g_param_spec_boxed ("position", "position",
                      "Position of the entity.",
                      CRANK_TYPE_TRANS3,
                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY |
                      G_PARAM_STATIC_STRINGS );


  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);

}





//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_entity3_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  CrankEntity3 *self = (CrankEntity3*) object;

  switch (prop_id)
    {
    case PROP_POSITION:
      g_value_set_boxed (value, & self->position);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_entity3_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  CrankEntity3 *self = (CrankEntity3*) object;

  switch (prop_id)
    {
    case PROP_POSITION:
      crank_trans3_copy ((CrankTrans3*)g_value_get_boxed (value),
                         & self->position);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}







//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_entity3_new:
 * @module: A Session Module.
 *
 * Constructs a entity.
 *
 * Returns: (transfer none): A Entity.
 */
CrankEntity3*
crank_entity3_new (CrankSessionModulePlaced *module)
{
  return (CrankEntity3*) g_object_new (CRANK_TYPE_ENTITY3,
                                       "module", module,
                                       NULL);
}






//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_entity3_get_position:
 * @entity: A Entity.
 * @position: (out): Position of entity.
 *
 * Gets position of entity.
 */
void
crank_entity3_get_position (CrankEntity3 *entity,
                            CrankTrans3  *position)
{
  crank_trans3_copy (& entity->position, position);
}


/**
 * crank_entity3_set_position:
 * @entity: A Entity.
 * @position: Position of entity.
 *
 * Sets position of entity.
 */
void
crank_entity3_set_position (CrankEntity3      *entity,
                            const CrankTrans3 *position)
{
  crank_trans3_copy (position, & entity->position);
}

