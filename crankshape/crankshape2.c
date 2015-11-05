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

/**
 * SECTION: crankshape2
 * @title: CrankShape2
 * @short_description: Base class for 2 dimsensional shape.
 * @stability: Unstable
 * @include: crankshape.h
 *
 * This class is base class for 2 dimensional shapes without separated parts.
 *
 * # Abstract functions
 *
 * * #CrankShape2Class.contains()
 * * #CrankShape2Class.finitize()
 */

//////// List of virtual functions /////////////////////////////////////////////

static void     crank_shape2_get_property (GObject    *object,
                                           guint       prop_id,
                                           GValue     *value,
                                           GParamSpec *pspec);

static void     crank_shape2_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);

//////// Type definition ///////////////////////////////////////////////////////

typedef struct _CrankShape2Private {
  CrankTrans2   position;
} CrankShape2Private;


G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE(CrankShape2, crank_shape2, G_TYPE_OBJECT)


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
crank_shape2_init (CrankShape2 *self)
{
  crank_trans2_init(& G_PRIVATE_FIELD (CrankShape2, self, CrankTrans2, position));
}

static void
crank_shape2_class_init (CrankShape2Class *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape2_get_property;
  c_gobject->set_property = crank_shape2_set_property;

  pspecs[PROP_POSITION] = g_param_spec_boxed ("position", "position", "position",
                                              CRANK_TYPE_TRANS2,
                                              G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  pspecs[PROP_POS_TRANS] = g_param_spec_boxed ("pos-trans", "pos-trans", "translational position",
                                               CRANK_TYPE_VEC_FLOAT2,
                                               G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  pspecs[PROP_POS_ROT] = g_param_spec_float ("pos-rot", "pos-rot", "rotational position",
                                             - G_MAXFLOAT, G_MAXFLOAT, 0,
                                             G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  pspecs[PROP_POS_SCL] = g_param_spec_float ("pos-scl", "pos-scl", "scale",
                                             0, G_MAXFLOAT, 0,
                                             G_PARAM_STATIC_STRINGS | G_PARAM_READWRITE);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_shape2_get_property (GObject *object,
                           guint prop_id,
                           GValue *value,
                           GParamSpec *pspec)
{
  switch (prop_id)
    {
    case PROP_POSITION:
      g_value_set_boxed (value,
                         & G_PRIVATE_FIELD (CrankShape2, object, CrankTrans2, position));
      break;

    case PROP_POS_TRANS:
      g_value_set_boxed (value,
                         & G_PRIVATE_FIELD (CrankShape2, object, CrankVecFloat2, position.mtrans));
      break;

    case PROP_POS_ROT:
      g_value_set_float (value,
                         G_PRIVATE_FIELD (CrankShape2, object, gfloat, position.mrot));
      break;

    case PROP_POS_SCL:
      g_value_set_float (value,
                         G_PRIVATE_FIELD (CrankShape2, object, gfloat, position.mscl));

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_shape2_set_property (GObject *object,
                           guint prop_id,
                           const GValue *value,
                           GParamSpec *pspec)
{
  switch (prop_id)
    {
    case PROP_POSITION:
      crank_trans2_copy ((CrankTrans2*) g_value_get_boxed (value),
                         & G_PRIVATE_FIELD (CrankShape2, object, CrankTrans2, position));
      break;

    case PROP_POS_TRANS:
      crank_vec_float2_copy ((CrankVecFloat2*) g_value_get_boxed (value),
                             & G_PRIVATE_FIELD (CrankShape2, object, CrankVecFloat2, position.mtrans));
      break;

    case PROP_POS_ROT:
      G_PRIVATE_FIELD (CrankShape2, object, gfloat, position.mrot) =
        g_value_get_float (value);
      break;

    case PROP_POS_SCL:
      G_PRIVATE_FIELD (CrankShape2, object, gfloat, position.mscl) =
        g_value_get_float (value);

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_shape2_get_position:
 * @shape: A Shape.
 * @position: (out): Position of a shape.
 *
 * Gets position of shape.
 */
void
crank_shape2_get_position (CrankShape2 *shape,
                           CrankTrans2 *position)
{
  crank_trans2_copy (& G_PRIVATE_FIELD (CrankShape2, shape, CrankTrans2, position) ,
                     position);
}

/**
 * crank_shape2_set_position:
 * @shape: A Shape
 * @position: Position of a shape.
 *
 * Sets position of shape.
 */
void
crank_shape2_set_position (CrankShape2 *shape,
                           CrankTrans2 *position)
{
  crank_trans2_copy (position,
                     & G_PRIVATE_FIELD (CrankShape2, shape, CrankTrans2, position));
}

/**
 * crank_shape2_get_pos_trans:
 * @shape: A Shape
 * @trans: (out): Translation (linear position) of a shape.
 *
 * Gets translation of shape
 */
void
crank_shape2_get_pos_trans (CrankShape2    *shape,
                            CrankVecFloat2 *trans)
{
  crank_vec_float2_copy (& G_PRIVATE_FIELD (CrankShape2, shape,
                                            CrankVecFloat2, position.mtrans),
                         trans);
}

/**
 * crank_shape2_set_pos_trans:
 * @shape: A Shape
 * @trans: Translation (linear position) of a shape.
 *
 * Sets translation of shape
 */
void
crank_shape2_set_pos_trans (CrankShape2    *shape,
                            CrankVecFloat2 *trans)
{
  crank_vec_float2_copy (trans,
                         & G_PRIVATE_FIELD (CrankShape2, shape,
                                            CrankVecFloat2, position.mtrans));
}

/**
 * crank_shape2_get_pos_rot:
 * @shape: A Shape
 *
 * Gets rotation of shape.
 *
 * Returns: rotation of shape.
 */
gfloat
crank_shape2_get_pos_rot (CrankShape2 *shape)
{
  return G_PRIVATE_FIELD (CrankShape2, shape, gfloat, position.mrot);
}

/**
 * crank_shape2_set_pos_rot:
 * @shape: A Shape
 * @rot: rotation
 *
 * Gets rotation of shape.
 *
 * Returns: rotation of shape.
 */
void
crank_shape2_set_pos_rot (CrankShape2 *shape,
                          gfloat rot)
{
  G_PRIVATE_FIELD (CrankShape2, shape, gfloat, position.mrot) = rot;
}

/**
 * crank_shape2_get_pos_scl:
 * @shape: A Shape.
 *
 * Gets scale of shape.
 *
 * Returns: scale of shape.
 */
gfloat
crank_shape2_get_pos_scl (CrankShape2 *shape)
{
  return G_PRIVATE_FIELD (CrankShape2, shape, gfloat, position.mscl);
}

/**
 * crank_shape2_set_pos_scl:
 * @shape: A Shape
 * @scl: Scale of shape.
 *
 * Sets scale of shape.
 */
void
crank_shape2_set_pos_scl (CrankShape2 *shape,
                          gfloat scl)
{
  G_PRIVATE_FIELD (CrankShape2, shape, gfloat, position.mscl) = scl;
}




/**
 * crank_shape2_contains:
 * @shape: A Shape.
 * @point: A Point.
 *
 * Checks @shape is containing @point.
 *
 * Returns: Whether the @point contains @shape.
 */
gboolean
crank_shape2_contains (CrankShape2    *shape,
                       CrankVecFloat2 *point)
{
  CrankShape2Class *c;

  c = CRANK_SHAPE2_GET_CLASS (shape);

  return c->contains (shape, point);
}


/**
 * crank_shape2_finitize:
 * @shape: A Shape.
 * @box: A Finite box
 *
 * Gets a finite part of shape that usable with @box.
 *
 * Returns: (transfer full) (element-type CrankShape2Finite):
 *      Finite parts of shape.
 */
GList*
crank_shape2_finitize (CrankShape2 *shape,
                       CrankBox2   *box)
{
  CrankShape2Class *c;

  c = CRANK_SHAPE2_GET_CLASS (shape);

  return c->finitize (shape, box);
}
