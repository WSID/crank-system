#ifndef CRANKRENDERLAYER_H
#define CRANKRENDERLAYER_H

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
#error crankrenderlayer.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>


G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_LAYER (crank_render_layer_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankRenderLayer,
                          crank_render_layer,
                          CRANK, RENDER_LAYER,
                          GObject)

/**
 * CrankRenderLayer:
 *
 * Represents a renderable layer.
 */

/**
 * CrankRenderLayerClass:
 *
 * This contains no virtual functions. This type just marks it is intermediate
 * layer that be contained in #CrankFilm.
 */
struct _CrankRenderLayerClass {
  /*< private >*/
  GObjectClass _parent;
};



//////// Properties ////////////////////////////////////////////////////////////

GQuark        crank_render_layer_get_qname        (CrankRenderLayer *layer);
const gchar  *crank_render_layer_get_name         (CrankRenderLayer *layer);

void          crank_render_layer_set_qname        (CrankRenderLayer *layer,
                                                   const GQuark      name);
void          crank_render_layer_set_name         (CrankRenderLayer *layer,
                                                   const gchar      *name);
void          crank_render_layer_set_name_static  (CrankRenderLayer *layer,
                                                   const gchar      *name);


G_END_DECLS

#endif
