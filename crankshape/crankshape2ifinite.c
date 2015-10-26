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
#include "crankbase.h"
#include "crankshape2.h"
#include "crankshape2ifinite.h"

/**
 * SECTION: crankshape2ifinite
 * @title: CrankShape2IFinite
 * @short_description: Interface for finite shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This interface defines methods for finite shapes.
 *
 * Finite shape will have limited range of placement of points. Thus, it will
 * have limited bounding boxes.
 *
 * <note> <para>
 *   This interface requires implementor to implement properties by themselves.
 * </para> </note>
 */

//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_INTERFACE (CrankShape2IFinite,
                    crank_shape2_ifinite,
                    CRANK_TYPE_SHAPE2)


//////// GTypeInterface ////////////////////////////////////////////////////////

static void
crank_shape2_ifinite_default_init (CrankShape2IFiniteInterface *iface)
{
  iface->get_aabb = NULL;
  iface->get_obb = NULL;

  // Install property
  /**
   * CrankShape2IFinite:bradius:
   *
   * Radius of bounding circle.
   */
  g_object_interface_install_property (iface,
      g_param_spec_float ("bradius", "bradius", "bradius",
                          0, G_MAXFLOAT, 0,
                          G_PARAM_STATIC_STRINGS | G_PARAM_READABLE));
  /**
   * CrankShape2IFinite:obb:
   *
   * OBB (Oriented bounding box) as #CrankBox2.
   */
  g_object_interface_install_property (iface,
      g_param_spec_boxed ("obb", "obb", "obb",
                          CRANK_TYPE_BOX2,
                          G_PARAM_STATIC_STRINGS | G_PARAM_READABLE));
}


//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_shape2_ifinite_get_bradius:
 * @shape: A Shape.
 *
 * Get a radius of bounding circle.
 *
 * Returns: A Radius.
 */
gfloat
crank_shape2_ifinite_get_bradius (CrankShape2IFinite *shape)
{
  CrankShape2IFiniteInterface *iface;
  iface = CRANK_SHAPE2_IFINITE_GET_IFACE (shape);

  return iface->get_bradius (shape);
}

/**
 * crank_shape2_ifinite_get_aabb
 * @shape: A Shape.
 * @rot: Rotation of @shape.
 * @aabb: (out): AABB
 *
 * Gets AABB (Axis aligned bounding box) of @shape rotated by @rot.
 */
void
crank_shape2_ifinite_get_aabb (CrankShape2IFinite *shape,
                               const gfloat        rot,
                               CrankBox2          *aabb)
{
  CrankShape2IFiniteInterface *iface;
  iface = CRANK_SHAPE2_IFINITE_GET_IFACE (shape);

  iface->get_aabb (shape, rot, aabb);
}

/**
 * crank_shape2_ifinite_get_obb:
 * @shape: A Shape.
 * @obb: (out): OBB
 *
 * Gets OBB of @shape.
 */
void
crank_shape2_ifinite_get_obb (CrankShape2IFinite *shape,
                              CrankBox2          *obb)
{
  CrankShape2IFiniteInterface *iface;
  iface = CRANK_SHAPE2_IFINITE_GET_IFACE (shape);

  iface->get_obb (shape, obb);
}
