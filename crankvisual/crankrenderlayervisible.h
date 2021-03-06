#ifndef CRANKRENDERLAYERVISIBLE_H
#define CRANKRENDERLAYERVISIBLE_H

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
#error crankrenderlayervisible.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankcore.h"
#include "crankvisible.h"
#include "crankrenderlayer.h"






//////// Type Declaration //////////////////////////////////////////////////////

typedef struct _CrankVisibleElement {
  CrankEntity3  *entity;
  CrankVisible  *visible;
  CrankTrans3    position;
} CrankVisibleElement;

#define CRANK_TYPE_RENDER_LAYER_VISIBLE (crank_render_layer_visible_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderLayerVisible,
                      crank_render_layer_visible,
                      CRANK, RENDER_LAYER_VISIBLE,
                      CrankRenderLayer)

struct _CrankRenderLayerVisible
{
  CrankRenderLayer _parent;

  GArray  *array;
};









//////// Public functions //////////////////////////////////////////////////////

//////// Constructor ///////////////////////////////////////////////////////////

CrankRenderLayerVisible*
crank_render_layer_visible_new (void);








//////// Public functions //////////////////////////////////////////////////////

void
crank_render_layer_visible_add_visible_at (CrankRenderLayerVisible *layer,
                                           CrankEntity3            *entity,
                                           CrankVisible            *visible,
                                           CrankTrans3             *position);

void
crank_render_layer_visible_clean (CrankRenderLayerVisible *layer);
#endif
