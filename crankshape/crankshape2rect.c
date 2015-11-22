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
#include "crankshape2rect.h"

//////// List of virtual functions /////////////////////////////////////////////

static void crank_shape2_rect_get_property (GObject    *object,
                                            guint       prop_id,
                                            GValue     *value,
                                            GParamSpec *pspec);

static void crank_shape2_rect_set_property (GObject      *object,
                                            guint         prop_id,
                                            const GValue *value,
                                            GParamSpec   *pspec);

static gboolean crank_shape2_rect_contains (CrankShape2    *shape,
                                            CrankVecFloat2 *point);


static gboolean crank_shape2_rect_is_convex (CrankShape2Finite *shape);

static gfloat crank_shape2_rect_get_bound_radius (CrankShape2Finite *shape);



static guint crank_shape2_rect_get_nvertices (CrankShape2Polygon *shape);

static void crank_shape2_rect_get_vertex (CrankShape2Polygon *shape,
                                          guint               index,
                                          CrankVecFloat2     *vertex);

static void crank_shape2_rect_get_edge_normal (CrankShape2Polygon *shape,
                                               guint               index,
                                               CrankVecFloat2     *nor);

static guint crank_shape2_rect_get_farthest_vertex (CrankShape2Polygon *shape,
                                                    CrankVecFloat2     *direction);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_SIZE,
  PROP_WIDTH,
  PROP_HEIGHT,
  PROP_COUNTS
};

GParamSpec *pspecs[PROP_COUNTS] = {NULL};


//////// Type Declaration //////////////////////////////////////////////////////

struct _CrankShape2Rect
{
  CrankShape2Polygon _parent;

  CrankVecFloat2 hsize;
};

G_DEFINE_TYPE (CrankShape2Rect,
               crank_shape2_rect,
               CRANK_TYPE_SHAPE2_POLYGON);


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_shape2_rect_init (CrankShape2Rect *self)
{
  crank_vec_float2_init (& self->hsize, 0.5f, 0.5f);
}

static void
crank_shape2_rect_class_init (CrankShape2RectClass *c)
{
  GObjectClass *c_gobject;
  CrankShape2Class *c_shape2;
  CrankShape2FiniteClass *c_shape2finite;
  CrankShape2PolygonClass *c_shape2polygon;

  c_gobject = G_OBJECT_CLASS (c);

  c_gobject->get_property = crank_shape2_rect_get_property;
  c_gobject->set_property = crank_shape2_rect_set_property;

  pspecs[PROP_SIZE] = g_param_spec_boxed ("size", "size", "size of rect shape",
                                          CRANK_TYPE_VEC_FLOAT2,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_WIDTH] = g_param_spec_float ("width", "width", "Width of rect shape",
                                          0, G_MAXFLOAT, 1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  pspecs[PROP_HEIGHT] = g_param_spec_float ("height", "height", "Height of rect shape",
                                          0, G_MAXFLOAT, 1,
                                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (c_gobject, PROP_COUNTS, pspecs);


  c_shape2 = CRANK_SHAPE2_CLASS (c);

  c_shape2->contains = crank_shape2_rect_contains;


  c_shape2finite = CRANK_SHAPE2_FINITE_CLASS (c);

  c_shape2finite->is_convex = crank_shape2_rect_is_convex;
  c_shape2finite->get_bound_radius = crank_shape2_rect_get_bound_radius;


  c_shape2polygon = CRANK_SHAPE2_POLYGON_CLASS (c);

  c_shape2polygon->get_nvertices = crank_shape2_rect_get_nvertices;
  c_shape2polygon->get_vertex = crank_shape2_rect_get_vertex;

  c_shape2polygon->get_edge_normal = crank_shape2_rect_get_edge_normal;
  c_shape2polygon->get_farthest_vertex = crank_shape2_rect_get_farthest_vertex;
}

//////// GObject ///////////////////////////////////////////////////////////////

void
crank_shape2_rect_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  CrankShape2Rect *self = CRANK_SHAPE2_RECT (object);
  CrankVecFloat2 *size;

  switch (prop_id)
    {
    case PROP_SIZE:
      size = g_new (CrankVecFloat2, 1);
      crank_vec_float2_muls (& self->hsize, 2, size);
      g_value_take_boxed (value, size);
      break;

    case PROP_WIDTH:
      g_value_set_float (value, self->hsize.x * 2);
      break;

    case PROP_HEIGHT:
      g_value_set_float (value, self->hsize.y * 2);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

void
crank_shape2_rect_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  CrankShape2Rect *self = CRANK_SHAPE2_RECT (object);

  switch (prop_id)
    {
    case PROP_SIZE:
      crank_shape2_rect_set_size (self, (CrankVecFloat2*)g_value_get_boxed (value));
      break;

    case PROP_WIDTH:
      crank_shape2_rect_set_width (self, g_value_get_float (value));
      break;

    case PROP_HEIGHT:
      crank_shape2_rect_set_height (self, g_value_get_float (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

//////// CrankShape2 ///////////////////////////////////////////////////////////

static gboolean
crank_shape2_rect_contains (CrankShape2    *shape,
                            CrankVecFloat2 *point)
{
  CrankShape2Rect *self = CRANK_SHAPE2_RECT (shape);
  return ((- self->hsize.x) < point->x) && (point->x < (self->hsize.x)) &&
         ((- self->hsize.y) < point->y) && (point->y < (self->hsize.y));
}


//////// CrankShape2Finite /////////////////////////////////////////////////////

static gboolean
crank_shape2_rect_is_convex (CrankShape2Finite *shape)
{
  return TRUE;
}

static gfloat
crank_shape2_rect_get_bound_radius (CrankShape2Finite* shape)
{
  CrankShape2Rect *self = CRANK_SHAPE2_RECT (shape);
  return crank_vec_float2_get_magn (& self->hsize);
}

//////// CrankShape2Polygon ////////////////////////////////////////////////////

static guint
crank_shape2_rect_get_nvertices (CrankShape2Polygon *shape)
{
  return 4;
}

static void
crank_shape2_rect_get_vertex (CrankShape2Polygon *shape,
                              guint index,
                              CrankVecFloat2 *vertex)
{
  CrankShape2Rect *self = CRANK_SHAPE2_RECT (shape);
  switch (index)
    {
    case CRANK_SHAPE2_RECT_VERTEX_LEFTUP:
      crank_vec_float2_init (vertex, self->hsize.x, self->hsize.y);
      break;

    case CRANK_SHAPE2_RECT_VERTEX_RIGHTUP:
      crank_vec_float2_init (vertex, -self->hsize.x, self->hsize.y);
      break;

    case CRANK_SHAPE2_RECT_VERTEX_RIGHTDOWN:
      crank_vec_float2_init (vertex, -self->hsize.x, -self->hsize.y);
      break;

    case CRANK_SHAPE2_RECT_VERTEX_LEFTDOWN:
      crank_vec_float2_init (vertex, self->hsize.x, -self->hsize.y);
      break;

    default:
      g_warning ("Invalid index: %u", index);
    }
}

static void
crank_shape2_rect_get_edge_normal (CrankShape2Polygon *shape,
                                   guint               index,
                                   CrankVecFloat2     *nor)
{
  switch (index)
    {
    case CRANK_SHAPE2_RECT_VERTEX_LEFTUP:
      crank_vec_float2_init (nor, 0, 1);
      break;

    case CRANK_SHAPE2_RECT_VERTEX_RIGHTUP:
      crank_vec_float2_init (nor, -1, 0);
      break;

    case CRANK_SHAPE2_RECT_VERTEX_RIGHTDOWN:
      crank_vec_float2_init (nor, 0, -1);
      break;

    case CRANK_SHAPE2_RECT_VERTEX_LEFTDOWN:
      crank_vec_float2_init (nor, 1, 0);
      break;

    default:
      g_warning ("Invalid index: %u", index);
    }
}


static guint
crank_shape2_rect_get_farthest_vertex (CrankShape2Polygon *shape,
                                       CrankVecFloat2     *direction)
{
  if (0 < direction->x)
    {
      if (0 < direction->y)
        return CRANK_SHAPE2_RECT_VERTEX_LEFTUP;
      else
        return CRANK_SHAPE2_RECT_VERTEX_LEFTDOWN;
    }
  else
    {
      if (0 < direction->y)
        return CRANK_SHAPE2_RECT_VERTEX_RIGHTUP;
      else
        return CRANK_SHAPE2_RECT_VERTEX_RIGHTDOWN;
    }
}



//////// Constructors //////////////////////////////////////////////////////////
/**
 * crank_shape2_rect_new:
 * @size: A Size of rect.
 *
 * Constructs a rect with size.
 *
 * Returns: (transfer full): A Rect
 */
CrankShape2Rect*
crank_shape2_rect_new (CrankVecFloat2 *size)
{
  return (CrankShape2Rect*) g_object_new (CRANK_TYPE_SHAPE2_RECT,
                                          "size", size,
                                          NULL);
}

/**
 * crank_shape2_rect_new_with_wh:
 * @width: Width of rect.
 * @height: Height of rect.
 *
 * Constructs a rect with width and height.
 *
 * Returns: (transfer full): A Rect
 */
CrankShape2Rect*
crank_shape2_rect_new_with_wh (gfloat width,
                               gfloat height)
{
  return (CrankShape2Rect*) g_object_new (CRANK_TYPE_SHAPE2_RECT,
                                          "widht", width,
                                          "height", height,
                                          NULL);
}

/**
 * crank_shape2_rect_new_unit:
 *
 * Constructs a unit rect.
 *
 * Returns: (transfer full): A Rect
 */
CrankShape2Rect*
crank_shape2_rect_new_unit (void)
{
  return crank_shape2_rect_new_with_wh (1, 1);
}

/**
 * crank_shape2_rect_new_square:
 * @size: Size of rect.
 *
 * Constructs a unit rect.
 *
 * Returns: (transfer full): A Rect
 */
CrankShape2Rect*
crank_shape2_rect_new_square (gfloat size)
{
  return crank_shape2_rect_new_with_wh (size, size);
}



//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_shape2_rect_get_size:
 * @shape: A Shape.
 * @size: (out): A Size.
 *
 * Gets a size of rect.
 */
void
crank_shape2_rect_get_size (CrankShape2Rect *shape,
                            CrankVecFloat2 *size)
{
  crank_vec_float2_muls (& shape->hsize, 2.0f, size);
}

/**
 * crank_shape2_rect_set_size:
 * @shape: A Shape.
 * @size: A Size.
 *
 * Sets size of rect.
 */
void
crank_shape2_rect_set_size (CrankShape2Rect *shape,
                            CrankVecFloat2  *size)
{
  crank_vec_float2_muls (size, 0.5f, & shape->hsize);

  shape->hsize.x = ABS (shape->hsize.x);
  shape->hsize.y = ABS (shape->hsize.y);

  g_object_notify_by_pspec ((GObject*) shape, pspecs[PROP_SIZE]);
  g_object_notify_by_pspec ((GObject*) shape, pspecs[PROP_WIDTH]);
  g_object_notify_by_pspec ((GObject*) shape, pspecs[PROP_HEIGHT]);
  g_object_notify ((GObject*) shape, "bound-radius");
}


/**
 * crank_shape2_rect_get_width:
 * @shape: A Shape.
 *
 * Gets width of rect.
 *
 * Returns: width of rect.
 */
gfloat
crank_shape2_rect_get_width (CrankShape2Rect *shape)
{
  return shape->hsize.x * 2;
}

/**
 * crank_shape2_rect_set_width:
 * @shape: A Shape.
 * @width: Width of rect.
 *
 * Sets width of rect.
 */
void
crank_shape2_rect_set_width (CrankShape2Rect *shape,
                             const gfloat width)
{
  shape->hsize.x = width * 0.5f;

  g_object_notify_by_pspec ((GObject*) shape, pspecs[PROP_SIZE]);
  g_object_notify_by_pspec ((GObject*) shape, pspecs[PROP_WIDTH]);
  g_object_notify ((GObject*) shape, "bound-radius");
}


/**
 * crank_shape2_rect_get_height:
 * @shape: A Shape.
 *
 * Gets height of rect.
 *
 * Returns: height of rect.
 */
gfloat
crank_shape2_rect_get_height (CrankShape2Rect *shape)
{
  return shape->hsize.y * 2;
}

/**
 * crank_shape2_rect_set_height:
 * @shape: A Shape.
 * @height: Height of rect.
 *
 * Sets height of rect.
 */
void
crank_shape2_rect_set_height (CrankShape2Rect *shape,
                             const gfloat height)
{
  shape->hsize.y = height * 0.5f;

  g_object_notify_by_pspec ((GObject*) shape, pspecs[PROP_SIZE]);
  g_object_notify_by_pspec ((GObject*) shape, pspecs[PROP_HEIGHT]);
  g_object_notify ((GObject*) shape, "bound-radius");
}


/**
 * crank_shape2_rect_is_square:
 * @shape: A Shape.
 *
 * Checks a rect is a square.
 *
 * Returns: Whether the rect is square.
 */
gboolean
crank_shape2_rect_is_square (CrankShape2Rect *shape)
{
  return (shape->hsize.x == shape->hsize.y);
}
