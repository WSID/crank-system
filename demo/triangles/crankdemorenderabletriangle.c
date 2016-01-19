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

/* This is Part of demo */

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include <crankbase.h>
#include <crankcore.h>
#include <crankvisual.h>

#include "crankdemorenderabletriangle.h"


//////// Private constant values ///////////////////////////////////////////////

static CrankVertexP3N3C4 vertices[3] = {
    {1, -1, -1,   0.0f, -0.7071f, 0.7071f,    255, 0, 0, 255},
    {0, 1,   1,   0.0f, -0.7071f, 0.7071f,    0, 255, 0, 255},
    {-1, -1,-1,   0.0f, -0.7071f, 0.7071f,    0, 0, 255, 255}
};


//////// List of virtual functions /////////////////////////////////////////////

static void crank_demo_renderable_triangle_finalize (GObject *object);

static void crank_demo_renderable_triangle_set_property (GObject      *object,
                                                         guint         prop_id,
                                                         const GValue *value,
                                                         GParamSpec   *pspec);

static void crank_demo_renderable_triangle_constructed (GObject *object);


static gfloat crank_demo_renderable_triangle_get_visible_radius (CrankRenderable *renderable);

static CoglPrimitive *crank_demo_renderable_triangle_get_primitive (
    CrankRenderablePrimitive *renderable,
    CrankTrans3 *position,
    CrankProjection *projection);

static CrankMaterial *crank_demo_renderable_triangle_get_material (
    CrankRenderablePrimitive *renderable,
    CrankTrans3 *position,
    CrankProjection *projection);


//////// Properties and Signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_COGL_CONTEXT,

  PROP_COUNTS
};


//////// Type Definition ///////////////////////////////////////////////////////

struct _CrankDemoRenderableTriangle
{
  CrankRenderablePrimitive _parent;

  CoglContext *cogl_context;

  CoglPrimitive *primitive;
  CrankMaterial *material;
};

G_DEFINE_TYPE (CrankDemoRenderableTriangle,
               crank_demo_renderable_triangle,
               CRANK_TYPE_RENDERABLE_PRIMITIVE)

//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_demo_renderable_triangle_init (CrankDemoRenderableTriangle *self)
{
}

static void
crank_demo_renderable_triangle_class_init (CrankDemoRenderableTriangleClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankRenderableClass *c_renderable = CRANK_RENDERABLE_CLASS (c);
  CrankRenderablePrimitiveClass *c_renderableprimitive =
      CRANK_RENDERABLE_PRIMITIVE_CLASS (c);

  c_gobject->finalize = crank_demo_renderable_triangle_finalize;
  c_gobject->set_property = crank_demo_renderable_triangle_set_property;
  c_gobject->constructed = crank_demo_renderable_triangle_constructed;

  g_object_class_install_property (c_gobject, PROP_COGL_CONTEXT,
                                   g_param_spec_pointer ("cogl-context", "CoglContext",
                                                         "CoglContext to initialize this renderable.",
                                                         G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS ));

  c_renderable->get_visible_radius = crank_demo_renderable_triangle_get_visible_radius;

  c_renderableprimitive->get_primitive = crank_demo_renderable_triangle_get_primitive;
  c_renderableprimitive->get_material = crank_demo_renderable_triangle_get_material;
}

//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_demo_renderable_triangle_finalize (GObject *object)
{
  CrankDemoRenderableTriangle *renderable;
  GObjectClass *pc_gobject;

  renderable = (CrankDemoRenderableTriangle*) object;

  pc_gobject = (GObjectClass*) crank_demo_renderable_triangle_parent_class;

  cogl_object_unref (renderable->primitive);
  g_object_unref (renderable->material);

  pc_gobject->finalize (object);
}

static void
crank_demo_renderable_triangle_set_property (GObject      *object,
                                             guint         prop_id,
                                             const GValue *value,
                                             GParamSpec   *pspec)
{
  CrankDemoRenderableTriangle *renderable;

  renderable = (CrankDemoRenderableTriangle*) object;

  switch (prop_id)
    {
    case PROP_COGL_CONTEXT:
      renderable->cogl_context = (CoglContext*) g_value_get_pointer (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
crank_demo_renderable_triangle_constructed (GObject *object)
{
  CrankDemoRenderableTriangle *renderable;
  GObjectClass *pc_gobject;

  renderable = (CrankDemoRenderableTriangle*) object;

  pc_gobject = (GObjectClass*) crank_demo_renderable_triangle_parent_class;

  pc_gobject->constructed (object);

  renderable->primitive = crank_cogl_primitive_new_p3n3c4 (renderable->cogl_context,
                                                           COGL_VERTICES_MODE_TRIANGLES,
                                                           3,
                                                           vertices);

  renderable->material = crank_material_new (renderable->cogl_context);
}


//////// CrankRenderable ///////////////////////////////////////////////////////

static gfloat
crank_demo_renderable_triangle_get_visible_radius (CrankRenderable *renderable)
{
  return 1.7320f;
}


//////// CrankRenderablePrimitive //////////////////////////////////////////////

static CoglPrimitive*
crank_demo_renderable_triangle_get_primitive (CrankRenderablePrimitive *renderable,
                                              CrankTrans3              *position,
                                              CrankProjection          *projection)
{
  CrankDemoRenderableTriangle *r;

  r = (CrankDemoRenderableTriangle*) renderable;

  return r->primitive;
}

static CrankMaterial*
crank_demo_renderable_triangle_get_material (CrankRenderablePrimitive *renderable,
                                             CrankTrans3              *position,
                                             CrankProjection          *projection)
{
  CrankDemoRenderableTriangle *r;

  r = (CrankDemoRenderableTriangle*) renderable;

  return r->material;
}


//////// Constructors //////////////////////////////////////////////////////////

CrankDemoRenderableTriangle*
crank_demo_renderable_triangle_new (CoglContext *cogl_context)
{
  return (CrankDemoRenderableTriangle*)
      g_object_new (CRANK_DEMO_TYPE_RENDERABLE_TRIANGLE,
                    "cogl-context", cogl_context,
                    NULL);
}
