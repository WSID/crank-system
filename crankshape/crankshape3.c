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

#include "crankshape3.h"

/**
 * SECTION: crankshape3
 * @title: CrankShape3
 * @short_description: Base class for 3 dimsensional shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This class is base class for 3 dimensional shapes without separated parts.
 *
 * # Abstract functions
 *
 * * #CrankShape3Class.contains()
 * * #CrankShape3Class.finitize()
 */

//////// List of virtual functions /////////////////////////////////////////////

static void     crank_shape3_get_property (GObject    *object,
                                           guint       prop_id,
                                           GValue     *value,
                                           GParamSpec *pspec);

static void     crank_shape3_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);

//////// Type definition ///////////////////////////////////////////////////////

typedef struct _CrankShape3Private {
  CrankTrans3   position;
} CrankShape3Private;


G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE(CrankShape3, crank_shape3, G_TYPE_OBJECT)


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_POSITION,
  PROP_POS_TRANS,
  PROP_POS_ROT,
  PROP_POS_SCL,
  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape3_init (CrankShape3 *self)
{
  crank_trans3_init(& G_PRIVATE_FIELD (CrankShape3, self, CrankTrans3, position));
}

static void
crank_shape3_class_init (CrankShape3Class *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape3_get_property;
  c_gobject->set_property = crank_shape3_set_property;

  pspecs[PROP_POSITION] = g_param_spec_boxed ("position", "position", "position",
                                              CRANK_TYPE_TRANS3,
                                              G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  pspecs[PROP_POS_TRANS] = g_param_spec_boxed ("pos-trans", "pos-trans", "translational position",
                                               CRANK_TYPE_VEC_FLOAT3,
                                               G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  pspecs[PROP_POS_ROT] = g_param_spec_boxed ("pos-rot", "pos-rot", "rotational position",
                                             CRANK_TYPE_QUAT_FLOAT,
                                             G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  pspecs[PROP_POS_SCL] = g_param_spec_float ("pos-scl", "pos-scl", "scale",
                                             0, G_MAXFLOAT, 0,
                                             G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape3_get_property (GObject *object,
                           guint prop_id,
                           GValue *value,
                           GParamSpec *pspec)
{
  switch (prop_id)
    {
    case PROP_POSITION:
      g_value_set_boxed (value,
                         & G_PRIVATE_FIELD (CrankShape3, object, CrankTrans3, position));
      break;

    case PROP_POS_TRANS:
      g_value_set_boxed (value,
                         & G_PRIVATE_FIELD (CrankShape3, object, CrankVecFloat3, position.mtrans));
      break;

    case PROP_POS_ROT:
      g_value_set_boxed (value,
                         & G_PRIVATE_FIELD (CrankShape3, object, CrankQuatFloat, position.mrot));
      break;

    case PROP_POS_SCL:
      g_value_set_float (value,
                         G_PRIVATE_FIELD (CrankShape3, object, gfloat, position.mscl));

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_shape3_set_property (GObject *object,
                           guint prop_id,
                           const GValue *value,
                           GParamSpec *pspec)
{
  switch (prop_id)
    {
    case PROP_POSITION:
      crank_trans3_copy ((CrankTrans3*) g_value_get_boxed (value),
                         & G_PRIVATE_FIELD (CrankShape3, object, CrankTrans3, position));
      break;

    case PROP_POS_TRANS:
      crank_vec_float3_copy ((CrankVecFloat3*) g_value_get_boxed (value),
                             & G_PRIVATE_FIELD (CrankShape3, object, CrankVecFloat3, position.mtrans));
      break;

    case PROP_POS_ROT:
      crank_quat_float_copy ((CrankQuatFloat*) g_value_get_boxed (value),
                             & G_PRIVATE_FIELD (CrankShape3, object, CrankQuatFloat, position.mrot));
      break;

    case PROP_POS_SCL:
      G_PRIVATE_FIELD (CrankShape3, object, gfloat, position.mscl) =
        g_value_get_float (value);

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_shape3_get_position:
 * @shape: A Shape.
 * @position: (out): Position of a shape.
 *
 * Gets position of shape.
 */
void
crank_shape3_get_position (CrankShape3 *shape,
                           CrankTrans3 *position)
{
  crank_trans3_copy (& G_PRIVATE_FIELD (CrankShape3, shape, CrankTrans3, position) ,
                     position);
}

/**
 * crank_shape3_set_position:
 * @shape: A Shape
 * @position: Position of a shape.
 *
 * Sets position of shape.
 */
void
crank_shape3_set_position (CrankShape3 *shape,
                           CrankTrans3 *position)
{
  crank_trans3_copy (position,
                     & G_PRIVATE_FIELD (CrankShape3, shape, CrankTrans3, position));
}

/**
 * crank_shape3_get_pos_trans:
 * @shape: A Shape
 * @trans: (out): Translation (linear position) of a shape.
 *
 * Gets translation of shape
 */
void
crank_shape3_get_pos_trans (CrankShape3    *shape,
                            CrankVecFloat3 *trans)
{
  crank_vec_float3_copy (& G_PRIVATE_FIELD (CrankShape3, shape,
                                            CrankVecFloat3, position.mtrans),
                         trans);
}

/**
 * crank_shape3_set_pos_trans:
 * @shape: A Shape
 * @trans: Translation (linear position) of a shape.
 *
 * Sets translation of shape
 */
void
crank_shape3_set_pos_trans (CrankShape3    *shape,
                            CrankVecFloat3 *trans)
{
  crank_vec_float3_copy (trans,
                         & G_PRIVATE_FIELD (CrankShape3, shape,
                                            CrankVecFloat3, position.mtrans));
}

/**
 * crank_shape3_get_pos_rot:
 * @shape: A Shape
 * @rot: (out): Rotation of shape.
 *
 * Gets rotation of shape.
 */
void
crank_shape3_get_pos_rot (CrankShape3    *shape,
                          CrankQuatFloat *rot)
{
  crank_quat_float_copy (& G_PRIVATE_FIELD (CrankShape3, shape, CrankQuatFloat, position.mrot),
                         rot);
}

/**
 * crank_shape3_set_pos_rot:
 * @shape: A Shape
 * @rot: rotation
 *
 * Gets rotation of shape.
 *
 * Returns: rotation of shape.
 */
void
crank_shape3_set_pos_rot (CrankShape3    *shape,
                          CrankQuatFloat *rot)
{
  crank_quat_float_copy (rot,
                         & G_PRIVATE_FIELD (CrankShape3, shape, CrankQuatFloat, position.mrot));
}

/**
 * crank_shape3_get_pos_scl:
 * @shape: A Shape.
 *
 * Gets scale of shape.
 *
 * Returns: scale of shape.
 */
gfloat
crank_shape3_get_pos_scl (CrankShape3 *shape)
{
  return G_PRIVATE_FIELD (CrankShape3, shape, gfloat, position.mscl);
}

/**
 * crank_shape3_set_pos_scl:
 * @shape: A Shape
 * @scl: Scale of shape.
 *
 * Sets scale of shape.
 */
void
crank_shape3_set_pos_scl (CrankShape3 *shape,
                          gfloat scl)
{
  G_PRIVATE_FIELD (CrankShape3, shape, gfloat, position.mscl) = scl;
}




/**
 * crank_shape3_contains:
 * @shape: A Shape.
 * @point: A Point.
 *
 * Checks @shape is containing @point.
 *
 * Returns: Whether the @point contains @shape.
 */
gboolean
crank_shape3_contains (CrankShape3    *shape,
                       CrankVecFloat3 *point)
{
  CrankShape3Class *c;

  c = CRANK_SHAPE3_GET_CLASS (shape);

  return c->contains (shape, point);
}


/**
 * crank_shape3_finitize:
 * @shape: A Shape.
 * @box: A Finite box
 *
 * Gets a finite part of shape that usable with @box.
 *
 * Returns: (transfer full) (element-type CrankShape2Finite):
 *      Finite parts of shape.
 */
GList*
crank_shape3_finitize (CrankShape3 *shape,
                       CrankBox3   *box)
{
  CrankShape3Class *c;

  c = CRANK_SHAPE3_GET_CLASS (shape);

  return c->finitize (shape, box);
}
