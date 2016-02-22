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
 * SECTION: crankrenderlayerarray
 * @title: CrankRenderLayerArray
 * @short_description: Array layer.
 * @stability: Unstable
 * @include: crankvisual.h
 *
 * This represents an array of pointers as rendering layer. This is primarily
 * used as list of rendered items. Steps may push data to this.
 */

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankvisible.h"
#include "crankrenderlayer.h"
#include "crankrenderlayerarray.h"




//////// List of virtual funxtions /////////////////////////////////////////////

static void crank_render_layer_array_finalize  (GObject *object);






//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_TYPE (CrankRenderLayerArray,
               crank_render_layer_array,
               CRANK_TYPE_RENDER_LAYER)




//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_layer_array_init (CrankRenderLayerArray *self)
{
  self->array = g_ptr_array_new ();
}


static void
crank_render_layer_array_class_init (CrankRenderLayerArrayClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->finalize = crank_render_layer_array_finalize;
}





//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_render_layer_array_finalize (GObject *object)
{
  GObjectClass *pc = crank_render_layer_array_parent_class;
  CrankRenderLayerArray *self = (CrankRenderLayerArray*) object;

  g_ptr_array_unref (self->array);
  pc->finalize (object);
}





//////// Constructor ///////////////////////////////////////////////////////////

/**
 * crank_render_layer_array:
 *
 * Constructs a Array layer.
 *
 * Returns: Newly constructed layer.
 */
CrankRenderLayerArray*
crank_render_layer_array_new (void)
{
  return (CrankRenderLayerArray*) g_object_new (CRANK_TYPE_RENDER_LAYER_ARRAY, NULL);
}
