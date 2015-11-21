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

#define _CRANKSHAPE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2polygon.h"
#include "crankshape2iround.h"

//////// Type definition ///////////////////////////////////////////////////////

G_DEFINE_INTERFACE (CrankShape2IRound,
                    crank_shape2_iround,
                    CRANK_TYPE_SHAPE2_FINITE)


//////// GInterface ////////////////////////////////////////////////////////////

void
crank_shape2_iround_default_init (CrankShape2IRoundInterface *i)
{
  g_object_interface_install_property (i,
                                       g_param_spec_object ("inner-shape", "inner-shape",
                                                            "Inner shape",
                                                            CRANK_TYPE_SHAPE2_POLYGON,
                                                            G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));
  g_object_interface_install_property (i,
                                       g_param_spec_float  ("round-radius", "round-radius",
                                                            "Round radius",
                                                            0, G_MAXFLOAT, 0,
                                                            G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));
}

//////// Public Functions //////////////////////////////////////////////////////

/**
 * crank_shape2_iround_get_inner_shape:
 * @iround: A Rounded shape.
 *
 * Gets inner polygonal shape of round shape.
 *
 * Returns: (transfer full): A Inner polygonal shape.
 */
CrankShape2Polygon*
crank_shape2_iround_get_inner_shape (CrankShape2IRound *iround)
{
  CrankShape2IRoundInterface *i = CRANK_SHAPE2_IROUND_GET_IFACE (iround);
  return i->get_inner_shape (iround);
}

/**
 * crank_shape2_iround_get_round_radius:
 * @iround: A Rounded shape.
 *
 * Gets round radius (margin from inner shape) of round shape.
 *
 * Returns: Round radius of shape.
 */
gfloat
crank_shape2_iround_get_round_radius (CrankShape2IRound *iround)
{
  CrankShape2IRoundInterface *i = CRANK_SHAPE2_IROUND_GET_IFACE (iround);
  return i->get_round_radius (iround);
}
