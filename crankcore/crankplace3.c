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
#include "cranksessionmoduleplaced.h"

#include "crankplace.h"
#include "crankentity.h"

#include "crankplace3.h"


//////// List of virtual functions /////////////////////////////////////////////

static void   crank_place3_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec);

static void   crank_place3_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec);




//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_BOUNDARY,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};






//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_TYPE (CrankPlace3,
               crank_place3,
               CRANK_TYPE_PLACE)




//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_place3_init (CrankPlace3 *self)
{
  crank_box3_init_uvec (& self->boundary, -1000, -1000, -1000, 1000, 1000, 1000);
}


static void
crank_place3_class_init (CrankPlace3Class *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_place3_get_property;
  c_gobject->set_property = crank_place3_set_property;

  pspecs[PROP_BOUNDARY] =
  g_param_spec_boxed ("boundary", "Boundary", "Boundary of place.",
                      CRANK_TYPE_BOX3,
                      G_PARAM_READWRITE |
                      G_PARAM_EXPLICIT_NOTIFY |
                      G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}





//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_place3_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  CrankPlace3 *self = (CrankPlace3*)object;

  switch (prop_id)
    {
    case PROP_BOUNDARY:
      g_value_set_boxed (value, & self->boundary);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
crank_place3_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  CrankPlace3 *self = (CrankPlace3*)object;

  switch (prop_id)
    {
    case PROP_BOUNDARY:
        {
          CrankBox3 *vbox = g_value_get_boxed (value);
          crank_box3_copy (vbox, & self->boundary);
        }
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}





//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_place3_new:
 * @module: A Module that this place belongs to.
 *
 * Constructs a module with boundary of [-1000, 1000]³
 *
 * Returns: (transfer full): A Place.
 */
CrankPlace3*
crank_place3_new (CrankSessionModulePlaced *module)
{
  return (CrankPlace3*) g_object_new (CRANK_TYPE_PLACE3,
                                      "module", module,
                                      NULL);
}


/**
 * crank_place3_new_with_boundary:
 * @module: A Module that this place belongs to.
 * @boundary: A Boundary.
 *
 * Constructs a module with given boundary.
 *
 * Returns: (transfer full): A Place.
 */
CrankPlace3*
crank_place3_new_with_boundary (CrankSessionModulePlaced *module,
                                const CrankBox3          *boundary)
{
  return (CrankPlace3*) g_object_new (CRANK_TYPE_PLACE3,
                                      "module", module,
                                      "boundary", boundary,
                                      NULL);
}


//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_place3_get_boundary:
 * @module: A Module that this place belongs to.
 * @boundary: (out): A Boundary.
 *
 * Gets boundary of module.
 */
void
crank_place3_get_boundary (CrankPlace3 *place,
                           CrankBox3   *boundary)
{
  crank_box3_copy (& place->boundary, boundary);
}


/**
 * crank_place3_set_boundary:
 * @module: A Module that this place belongs to.
 * @boundary: A Boundary.
 *
 * Sets boundary of module.
 */
void
crank_place3_set_boundary (CrankPlace3     *place,
                           const CrankBox3 *boundary)
{
  crank_box3_copy (boundary, & place->boundary);
}

