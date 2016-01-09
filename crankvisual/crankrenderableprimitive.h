#ifndef CRANKRENDERABLEPRIMITIVE_H
#define CRANKRENDERABLEPRIMITIVE_H

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

#ifndef _CRANKVISUAL_INSIDE
#error crankrenderableprimitive.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

#include "crankprojection.h"
#include "crankmaterial.h"
#include "crankrenderable.h"

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_RENDERABLE_PRIMITIVE (crank_renderable_primitive_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankRenderablePrimitive,
                          crank_renderable_primitive,
                          CRANK, RENDERABLE_PRIMITIVE,
                          CrankRenderable)

/**
 * CrankRenderablePrimitiveClass
 * @get_primitive: Slot for crank_renderable_primitive_get_primitive()
 * @get_material: Slot fo crank_renderable_primitive_get_material()
 *
 * Virtual function table for #CrankRenderablePrimitive
 */
struct _CrankRenderablePrimitiveClass
{
  CrankRenderableClass _parent;

  CoglPrimitive *(*get_primitive) (CrankRenderablePrimitive *renderable,
                                   CrankTrans3              *position,
                                   CrankProjection          *projection);

  CrankMaterial *(*get_material)  (CrankRenderablePrimitive *renderable,
                                   CrankTrans3              *position,
                                   CrankProjection          *projection);
};


//////// Virtual Function Wrapper //////////////////////////////////////////////

CoglPrimitive *crank_renderable_primitive_get_primitive (CrankRenderablePrimitive *renderable,
                                                         CrankTrans3              *position,
                                                         CrankProjection          *projection);

CrankMaterial *crank_renderable_primitive_get_material  (CrankRenderablePrimitive *renderable,
                                                         CrankTrans3              *position,
                                                         CrankProjection          *projection);

#endif
