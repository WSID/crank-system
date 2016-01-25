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
 * SECTION: crankrenderableprimitive
 * @title: CrankRenderablePrimitive
 * @short_description: Primitive based renderable.
 * @stability: unstable
 * @include: crankvisual.h
 *
 * Primitive based renderable base class.
 */


#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankprojection.h"
#include "crankmaterial.h"
#include "crankrenderable.h"
#include "crankrenderableprimitive.h"


//////// List of virtual functions /////////////////////////////////////////////

static void crank_renderable_primitive_render_geom (CrankRenderable *renderable,
                                                    CrankTrans3     *position,
                                                    CrankProjection *projection,
                                                    CoglFramebuffer *framebuffer);

static void crank_renderable_primitive_render_color(CrankRenderable *renderable,
                                                    CrankTrans3     *position,
                                                    CrankProjection *projection,
                                                    CoglFramebuffer *framebuffer);

static void crank_renderable_primitive_render_material (CrankRenderable *renderable,
                                                        CrankTrans3     *position,
                                                        CrankProjection *projection,
                                                        CoglFramebuffer *framebuffer);


//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_ABSTRACT_TYPE (CrankRenderablePrimitive,
                        crank_renderable_primitive,
                        CRANK_TYPE_RENDERABLE)



//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_renderable_primitive_init (CrankRenderablePrimitive *renderable)
{
}

static void
crank_renderable_primitive_class_init (CrankRenderablePrimitiveClass *c)
{
  CrankRenderableClass *c_renderable;

  c_renderable = CRANK_RENDERABLE_CLASS (c);

  c_renderable->render_geom = crank_renderable_primitive_render_geom;
  c_renderable->render_color = crank_renderable_primitive_render_color;
  c_renderable->render_material = crank_renderable_primitive_render_material;
}


//////// CrankRenderable ///////////////////////////////////////////////////////

static void
crank_renderable_primitive_render_geom (CrankRenderable *renderable,
                                        CrankTrans3     *position,
                                        CrankProjection *projection,
                                        CoglFramebuffer *framebuffer)
{
  CrankRenderablePrimitive *prenderable;
  CoglPrimitive *primitive;
  CrankMaterial *material;
  CoglPipeline *pipeline;
  CrankMatFloat4 mv_matrix;

  prenderable = (CrankRenderablePrimitive*) renderable;

  primitive = crank_renderable_primitive_get_primitive (prenderable,
                                                        position,
                                                        projection);

  material = crank_renderable_primitive_get_material (prenderable,
                                                      position,
                                                      projection);

  pipeline = crank_material_get_pipeline_geom (material);

  crank_material_geom_set_render_projection (material, projection);

  crank_trans3_to_matrix_transpose (position, & mv_matrix);
  cogl_framebuffer_set_modelview_matrix (framebuffer, (CoglMatrix*)&mv_matrix);

  cogl_primitive_draw (primitive, framebuffer, pipeline);
}

static void
crank_renderable_primitive_render_color (CrankRenderable *renderable,
                                         CrankTrans3     *position,
                                         CrankProjection *projection,
                                         CoglFramebuffer *framebuffer)
{
  CrankRenderablePrimitive *prenderable;
  CoglPrimitive *primitive;
  CrankMaterial *material;
  CoglPipeline *pipeline;
  CrankMatFloat4 mv_matrix;

  prenderable = (CrankRenderablePrimitive*) renderable;

  primitive = crank_renderable_primitive_get_primitive (prenderable,
                                                        position,
                                                        projection);

  material = crank_renderable_primitive_get_material (prenderable,
                                                      position,
                                                      projection);

  pipeline = crank_material_get_pipeline_color (material);

  crank_trans3_to_matrix_transpose (position, & mv_matrix);

  cogl_framebuffer_set_modelview_matrix (framebuffer, (CoglMatrix*)&mv_matrix);
  cogl_primitive_draw (primitive, framebuffer, pipeline);
}


static void
crank_renderable_primitive_render_material (CrankRenderable *renderable,
                                            CrankTrans3     *position,
                                            CrankProjection *projection,
                                            CoglFramebuffer *framebuffer)
{
  CrankRenderablePrimitive *prenderable;
  CoglPrimitive *primitive;
  CrankMaterial *material;
  CoglPipeline *pipeline;
  CrankMatFloat4 mv_matrix;

  prenderable = (CrankRenderablePrimitive*) renderable;

  primitive = crank_renderable_primitive_get_primitive (prenderable,
                                                        position,
                                                        projection);

  material = crank_renderable_primitive_get_material (prenderable,
                                                      position,
                                                      projection);

  pipeline = crank_material_get_pipeline_material (material);

  crank_trans3_to_matrix_transpose (position, & mv_matrix);

  cogl_framebuffer_set_modelview_matrix (framebuffer, (CoglMatrix*)&mv_matrix);
  cogl_primitive_draw (primitive, framebuffer, pipeline);
}



//////// Virtual Function wrappers /////////////////////////////////////////////

/**
 * crank_renderable_primitive_get_primitive:
 * @renderable: A Renderable.
 * @position: Relative position of @renderable from view.
 * @projection: A Projection.
 *
 * Gets primitive to render.
 *
 * Returns: (transfer none): A Primitive to be rendered.
 */
CoglPrimitive*
crank_renderable_primitive_get_primitive (CrankRenderablePrimitive *renderable,
                                          CrankTrans3              *position,
                                          CrankProjection          *projection)
{
  CrankRenderablePrimitiveClass *c;

  c = CRANK_RENDERABLE_PRIMITIVE_GET_CLASS (renderable);

  return c->get_primitive (renderable, position, projection);
}

/**
 * crank_renderable_primitive_get_material:
 * @renderable: A Renderable.
 * @position: Relative position of @renderable from view.
 * @projection: A Projection.
 *
 * Gets material to render.
 *
 * Returns: (transfer none): A Material to be rendered.
 */
CrankMaterial*
crank_renderable_primitive_get_material (CrankRenderablePrimitive *renderable,
                                         CrankTrans3              *position,
                                         CrankProjection          *projection)
{
  CrankRenderablePrimitiveClass *c;

  c = CRANK_RENDERABLE_PRIMITIVE_GET_CLASS (renderable);

  return c->get_material (renderable, position, projection);
}
