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

#define _CRANKVISUAL_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankcore.h"
#include "crankvisible.h"
#include "crankrenderlayer.h"
#include "crankrenderlayervisible.h"








/////// List of virtual functions //////////////////////////////////////////////

static void crank_render_layer_visible_finalize (GObject *object);








//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_TYPE (CrankRenderLayerVisible,
               crank_render_layer_visible,
               CRANK_TYPE_RENDER_LAYER)







//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_render_layer_visible_init (CrankRenderLayerVisible *self)
{
  self->array = g_array_new (FALSE, FALSE, sizeof (CrankVisibleElement));
}

static void
crank_render_layer_visible_class_init (CrankRenderLayerVisibleClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->finalize = crank_render_layer_visible_finalize;
}








//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_render_layer_visible_finalize (GObject *object)
{
  GObjectClass *pc = crank_render_layer_visible_parent_class;
  CrankRenderLayerVisible *layer = (CrankRenderLayerVisible*)object;

  g_array_unref (layer->array);

  pc->finalize (object);
}







//////// Public Functions //////////////////////////////////////////////////////

//////// Constructor ///////////////////////////////////////////////////////////

CrankRenderLayerVisible*
crank_render_layer_visible_new (void)
{
  return (CrankRenderLayerVisible*) g_object_new (
      CRANK_TYPE_RENDER_LAYER_VISIBLE, NULL);
}









//////// Operations ////////////////////////////////////////////////////////////

void
crank_render_layer_visible_add_visible_at (CrankRenderLayerVisible *layer,
                                           CrankEntity3            *entity,
                                           CrankVisible            *visible,
                                           CrankTrans3             *position)
{
  CrankVisibleElement element = {
    entity, visible, {}
  };

  crank_trans3_copy (position, & element.position);

  g_array_append_val (layer->array, element);
}
