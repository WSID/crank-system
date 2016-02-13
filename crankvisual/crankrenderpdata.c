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
#include "crankshape.h"
#include "crankcore.h"

#include "crankrenderable.h"
#include "cranklightable.h"
#include "crankrenderpdata.h"

//////// Private type definition ///////////////////////////////////////////////

G_DEFINE_TYPE (CrankRenderPData, crank_render_pdata, G_TYPE_OBJECT)


//////// Private type: GTypeInstance ///////////////////////////////////////////

void crank_render_pdata_init (CrankRenderPData *pdata)
{
}

void crank_render_pdata_class_init (CrankRenderPDataClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->constructed = crank_render_pdata_constructed;
  c_gobject->set_property = crank_render_pdata_set_property;
  c_gobject->dispose = crank_render_pdata_dispose;
  c_gobject->finalize = crank_render_pdata_finalize;

  pspecs_priv[PROP_PRIV_VISIBLE_TYPES] =
      g_param_spec_uint ("visible-types", "Visible types", "Visible types",
                         0, 16, 2,
                         G_PARAM_PRIVATE |
                         G_PARAM_WRITABLE |
                         G_PARAM_CONSTRUCT_ONLY |
                         G_PARAM_STATIC_STRINGS );

  pspecs_priv[PROP_PRIV_PLACE] = g_param_spec_pointer ("place", "place", "Place",
                                                      G_PARAM_PRIVATE |
                                                      G_PARAM_WRITABLE |
                                                      G_PARAM_CONSTRUCT_ONLY |
                                                      G_PARAM_STATIC_STRINGS );

  pspecs_priv[PROP_PRIV_VISIBLE_OFFSET] =
      g_param_spec_int64 ("visible-offset", "Visible offset",
                          "Visible offset",
                          0, G_MAXINT64, 0,
                          G_PARAM_PRIVATE |
                          G_PARAM_WRITABLE |
                          G_PARAM_CONSTRUCT_ONLY |
                          G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_PRIV_COUNTS, pspecs_priv);
}




//////// Private type: GObject /////////////////////////////////////////////////

void
crank_render_pdata_constructed (GObject *object)
{
  CrankRenderPData *pdata = (CrankRenderPData*) object;
  CrankPlace3 *place = g_object_get_data (object, "place");
  guint visible_types = GPOINTER_TO_UINT (g_object_get_data (object, "visible-types"));
  gpointer visible_offset = g_object_get_data (object, "visible-offset");

  CrankBox3 box;

  crank_box3_init_uvec (& box, -1000, -1000, -1000, 1000, 1000, 1000);

  pdata->nentity_sets = visible_types;
  pdata->entity_sets = g_new (CrankOctreeSet*, pdata->nentity_sets);

  pdata->rentities = crank_octree_set_new (& box,
        crank_render_pdata_get_pos, NULL, NULL,
        crank_render_pdata_get_rad, visible_offset, NULL);

  pdata->lentities = crank_octree_set_new (& box,
        crank_render_pdata_get_pos, NULL, NULL,
        crank_render_pdata_get_rad, visible_offset, NULL);

  pdata->entity_sets[0] = pdata->rentities;
  pdata->entity_sets[1] = pdata->lentities;
}

void
crank_render_pdata_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  switch (prop_id)
    {
    case PROP_PRIV_PLACE:
      g_object_set_data (object, "place",
                         g_value_get_pointer (value));
      break;

    case PROP_PRIV_VISIBLE_TYPES:
      g_object_set_data (object, "visible-types",
                         GINT_TO_POINTER (g_value_get_uint (value)));
      break;

    case PROP_PRIV_VISIBLE_OFFSET:
      g_object_set_data (object, "visible-offset",
                         GINT_TO_POINTER (g_value_get_int64 (value)));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

void
crank_render_pdata_dispose (GObject *object)
{
  GObjectClass *pc = crank_render_pdata_parent_class;
  CrankRenderPData *pdata = (CrankRenderPData*) object;
  guint i;

  for (i = 0; i < pdata->nentity_sets; i++)
    crank_octree_set_remove_all (pdata->entity_sets[i]);

  pc->dispose (object);
}

void
crank_render_pdata_finalize (GObject *object)
{
  GObjectClass *pc = crank_render_pdata_parent_class;
  CrankRenderPData *pdata = (CrankRenderPData*) object;
  guint i;

  for (i = 0; i < pdata->nentity_sets; i++)
    crank_octree_set_unref (pdata->entity_sets[i]);
  g_free (pdata->entity_sets);

  pc->finalize (object);
}

//////// Private type callbacks ////////////////////////////////////////////////

CrankVecFloat3*
crank_render_pdata_get_pos (gpointer data,
                           gpointer userdata)
{
  CrankEntity3 *entity = (CrankEntity3*)data;
  return & entity->position.mtrans;
}

gfloat
crank_render_pdata_get_rad (gpointer data,
                            gpointer userdata)
{
  goffset offset = (goffset) userdata;

  CrankEntity3 *entity = (CrankEntity3*)data;
  CrankVisible *visible = G_STRUCT_MEMBER (CrankVisible*, entity, offset);

  return entity->position.mscl *
         crank_visible_get_visible_radius (visible);
}

//////// Private type functions ////////////////////////////////////////////////

void
crank_render_pdata_add_entity (CrankRenderPData *pdata,
                               CrankEntityBase  *entity,
                               const guint       tindex)
{
  crank_octree_set_add (pdata->entity_sets[tindex], entity);
}

gboolean
crank_render_pdata_remove_entity (CrankRenderPData *pdata,
                                  CrankEntityBase  *entity,
                                  const guint       tindex)
{
  return crank_octree_set_remove (pdata->entity_sets[tindex], entity);
}
