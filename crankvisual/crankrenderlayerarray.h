#ifndef CRANKRENDERLAYERENTITY_H
#define CRANKRENDERLAYERENTITY_H

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
#error crankrenderlayerentity.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>

#include "crankvisible.h"
#include "crankrenderlayer.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_LAYER_ARRAY (crank_render_layer_array_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderLayerArray,
                      crank_render_layer_array,
                      CRANK, RENDER_LAYER_ARRAY,
                      CrankRenderLayer)

/**
 * CrankRenderLayerArray:
 *
 * Represents a layer that holds list or data structures of entities.
 */

struct _CrankRenderLayerArray
{
  /*< private >*/
  CrankRenderLayer _parent;

  /*< public >*/
  GPtrArray *array;
};

//////// Constructors //////////////////////////////////////////////////////////

CrankRenderLayerArray    *crank_render_layer_array_new (void);



G_END_DECLS

#endif
