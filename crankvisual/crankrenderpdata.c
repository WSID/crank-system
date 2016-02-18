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

G_DEFINE_TYPE_WITH_CODE (CrankRenderPData,
                         crank_render_pdata,
                         CRANK_TYPE_COMPOSITABLE,
                         {
                           crank_gtype_compositable_add_requisition (g_define_type_id,
                                                                     CRANK_TYPE_PLACE3);
                         })


//////// Private type: GTypeInstance ///////////////////////////////////////////

void crank_render_pdata_init (CrankRenderPData *pdata)
{
}

void crank_render_pdata_class_init (CrankRenderPDataClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankCompositableClass *c_compositable = CRANK_COMPOSITABLE_CLASS (c);

  c_gobject->constructed = crank_render_pdata_constructed;
  c_gobject->set_property = crank_render_pdata_set_property;
  c_gobject->dispose = crank_render_pdata_dispose;
  c_gobject->finalize = crank_render_pdata_finalize;

  c_compositable->adding = crank_render_pdata_adding;
  c_compositable->removing = crank_render_pdata_removing;

  pspecs_priv[PROP_PRIV_VISIBLE_TYPES] =
      g_param_spec_uint ("visible-types", "Visible types", "Visible types",
                         0, 16, 2,
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
    case PROP_PRIV_VISIBLE_TYPES:
      g_object_set_data (object, "visible-types",
                         GINT_TO_POINTER (g_value_get_uint (value)));
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



gboolean
crank_render_pdata_adding (CrankCompositable  *compositable,
                           CrankComposite     *composite,
                           GError            **error)
{
  CrankCompositableClass *pc = crank_render_pdata_parent_class;
  CrankRenderPData *pdata;
  CrankPlace3 *place;

  if (! pc->adding (compositable, composite, error))
    return FALSE;

  pdata = (CrankRenderPData*) compositable;
  place = (CrankPlace3*)composite;

  pdata->rentities = crank_octree_set_new (& place->boundary,
        crank_render_pdata_get_pos, NULL, NULL,
        crank_render_pdata_get_rad, NULL, NULL);

  pdata->lentities = crank_octree_set_new (& place->boundary,
        crank_render_pdata_get_pos, NULL, NULL,
        crank_render_pdata_get_rad, NULL, NULL);

  pdata->entity_sets = g_new (CrankOctreeSet*, pdata->nentity_sets);
  pdata->entity_sets[0] = pdata->rentities;
  pdata->entity_sets[1] = pdata->lentities;

  return TRUE;
}

gboolean
crank_render_pdata_removing (CrankCompositable  *compositable,
                             CrankComposite     *composite,
                             GError            **error)
{
  CrankCompositableClass *pc = crank_render_pdata_parent_class;
  CrankRenderPData *pdata;
  CrankPlace3 *place;
  guint i;

  pdata = (CrankRenderPData*) compositable;
  place = (CrankPlace3*)composite;

  if (! pc->removing (compositable, composite, error))
    return FALSE;

  for (i = 0; i < pdata->nentity_sets; i++)
    crank_octree_set_remove_all (pdata->entity_sets[i]);

  g_free (pdata->entity_sets);

  pdata->entity_sets = NULL;
  pdata->rentities = NULL;
  pdata->lentities = NULL;

  return TRUE;
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
  CrankEntity3 *entity = (CrankEntity3*)data;
  CrankVisible *visible =
    (CrankVisible*) crank_composite_get_compositable_by_gtype (
        (CrankComposite*)entity,
        CRANK_TYPE_VISIBLE  );

  return entity->position.mscl *
         crank_visible_get_visible_radius (visible);
}


void
crank_render_pdata_add_entity (CrankRenderPData *pdata,
                               CrankEntity      *entity,
                               CrankVisible     *visible,
                               const guint       tindex)
{
  CrankOctreeSet *octree = pdata->entity_sets[tindex];
  crank_octree_set_add (octree, entity);

}

void
crank_render_pdata_remove_entity (CrankRenderPData *pdata,
                                  CrankEntity      *entity,
                                  CrankVisible     *visible,
                                  const guint       tindex)
{
  CrankOctreeSet *octree = pdata->entity_sets[tindex];
  crank_octree_set_remove (octree, entity);
}
