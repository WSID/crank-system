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

#include "crankvisible.h"
#include "crankprojection.h"
#include "crankrenderplacedata.h"





//////// Private Functions /////////////////////////////////////////////////////

//////// List of virtual functions /////////////////////////////////////////////

void crank_render_place_data_constructed (GObject *object);

void crank_render_place_data_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);

void crank_render_place_data_dispose (GObject *object);

void crank_render_place_data_finalize (GObject *object);



gboolean crank_render_place_data_adding (CrankCompositable  *compositable,
                                         CrankComposite     *composite,
                                         GError            **error);

gboolean crank_render_place_data_removing (CrankCompositable  *compositable,
                                           CrankComposite     *composite,
                                           GError            **error);





//////// Private function for callback /////////////////////////////////////////

CrankVecFloat3 *crank_render_place_data_get_pos (gpointer data,
                                                 gpointer userdata);

gfloat          crank_render_place_data_get_rad (gpointer data,
                                                 gpointer userdata);







//////// Private type definition ///////////////////////////////////////////////

struct _CrankRenderPlaceData
{
  CrankCompositable1N parent;

  GHashTable     **entity_counts;
  CrankOctreeSet **entity_sets;
  guint           nentity_sets;
};

G_DEFINE_TYPE_WITH_CODE (CrankRenderPlaceData,
                         crank_render_place_data,
                         CRANK_TYPE_COMPOSITABLE,
                         {
                           crank_gtype_compositable_add_requisition (g_define_type_id,
                                                                     CRANK_TYPE_PLACE3);
                         })






//////// GTypeInstance /////////////////////////////////////////////////////////

void crank_render_place_data_init (CrankRenderPlaceData *pdata)
{
}

void crank_render_place_data_class_init (CrankRenderPlaceDataClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankCompositableClass *c_compositable = CRANK_COMPOSITABLE_CLASS (c);

  c_gobject->constructed = crank_render_place_data_constructed;
  c_gobject->set_property = crank_render_place_data_set_property;
  c_gobject->dispose = crank_render_place_data_dispose;
  c_gobject->finalize = crank_render_place_data_finalize;

  c_compositable->adding = crank_render_place_data_adding;
  c_compositable->removing = crank_render_place_data_removing;

  pspecs_priv[PROP_PRIV_VISIBLE_TYPES] =
      g_param_spec_uint ("visible-types", "Visible types", "Visible types",
                         0, 16, 2,
                         G_PARAM_PRIVATE |
                         G_PARAM_WRITABLE |
                         G_PARAM_CONSTRUCT_ONLY |
                         G_PARAM_STATIC_STRINGS );

  g_object_class_install_properties (c_gobject, PROP_PRIV_COUNTS, pspecs_priv);
}








//////// GObject ///////////////////////////////////////////////////////////////

void
crank_render_place_data_constructed (GObject *object)
{
  CrankRenderPlaceData *pdata = (CrankRenderPlaceData*) object;
  CrankPlace3 *place = g_object_get_data (object, "place");
  guint visible_types = GPOINTER_TO_UINT (g_object_get_data (object, "visible-types"));
  gpointer visible_offset = g_object_get_data (object, "visible-offset");

  pdata->nentity_sets = visible_types;
  pdata->entity_sets = g_new (CrankOctreeSet*, pdata->nentity_sets);
}

void
crank_render_place_data_set_property (GObject      *object,
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
crank_render_place_data_dispose (GObject *object)
{
  GObjectClass *pc = crank_render_place_data_parent_class;
  CrankRenderPlaceData *pdata = (CrankRenderPlaceData*) object;
  guint i;

  for (i = 0; i < pdata->nentity_sets; i++)
    crank_octree_set_remove_all (pdata->entity_sets[i]);

  pc->dispose (object);
}

void
crank_render_place_data_finalize (GObject *object)
{
  GObjectClass *pc = crank_render_place_data_parent_class;
  CrankRenderPlaceData *pdata = (CrankRenderPlaceData*) object;
  guint i;

  for (i = 0; i < pdata->nentity_sets; i++)
    crank_octree_set_unref (pdata->entity_sets[i]);
  g_free (pdata->entity_sets);

  pc->finalize (object);
}







//////// CrankCompositable /////////////////////////////////////////////////////

gboolean
crank_render_place_data_adding (CrankCompositable  *compositable,
                           CrankComposite     *composite,
                           GError            **error)
{
  CrankCompositableClass *pc = crank_render_place_data_parent_class;
  CrankRenderPlaceData *pdata;
  CrankPlace3 *place;
  guint i;

  if (! pc->adding (compositable, composite, error))
    return FALSE;

  pdata = (CrankRenderPlaceData*) compositable;
  place = (CrankPlace3*)composite;

  pdata->entity_counts = g_new (GHashTable*, pdata->nentity_sets);
  pdata->entity_sets = g_new (CrankOctreeSet*, pdata->nentity_sets);

  for (i = 0; i < pdata->nentity_sets; i++)
    {
      pdata->entity_counts[i] = g_hash_table_new (g_direct_hash, g_direct_equal);

      pdata->entity_sets[i] = crank_octree_set_new (& place->boundary,
            crank_render_place_data_get_pos, NULL, NULL,
            crank_render_place_data_get_rad, NULL, NULL);
    }

  return TRUE;
}

gboolean
crank_render_place_data_removing (CrankCompositable  *compositable,
                             CrankComposite     *composite,
                             GError            **error)
{
  CrankCompositableClass *pc = crank_render_place_data_parent_class;
  CrankRenderPlaceData *pdata;
  CrankPlace3 *place;
  guint i;

  pdata = (CrankRenderPlaceData*) compositable;
  place = (CrankPlace3*)composite;

  if (! pc->removing (compositable, composite, error))
    return FALSE;

  for (i = 0; i < pdata->nentity_sets; i++)
    {
      g_hash_table_unref (pdata->entity_counts[i]);
      crank_octree_set_remove_all (pdata->entity_sets[i]);
    }

  g_free (pdata->entity_sets);

  pdata->entity_sets = NULL;

  return TRUE;
}







//////// Private type callbacks ////////////////////////////////////////////////

CrankVecFloat3*
crank_render_place_data_get_pos (gpointer data,
                           gpointer userdata)
{
  CrankEntity3 *entity = (CrankEntity3*)data;
  return & entity->position.mtrans;
}

gfloat
crank_render_place_data_get_rad (gpointer data,
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







//////// Internal Functions ////////////////////////////////////////////////////

G_GNUC_INTERNAL void
crank_render_place_data_add_entity (CrankRenderPlaceData *pdata,
                                    CrankEntity          *entity,
                                    CrankVisible         *visible,
                                    const guint           tindex)
{
  GHashTable *entity_count = pdata->entity_counts[tindex];
  CrankOctreeSet *entity_set = pdata->entity_sets[tindex];

  if (crank_mset_add (entity_count, entity) == 1)
    crank_octree_set_add (entity_set, entity);

}

G_GNUC_INTERNAL void
crank_render_place_data_remove_entity (CrankRenderPlaceData *pdata,
                                       CrankEntity          *entity,
                                       CrankVisible         *visible,
                                       const guint           tindex)
{
  GHashTable *entity_count = pdata->entity_counts[tindex];
  CrankOctreeSet *entity_set = pdata->entity_sets[tindex];

  if (crank_mset_remove (entity_count, entity) == 0)
    crank_octree_set_remove (entity_set, entity);
}




//////// Public Functions //////////////////////////////////////////////////////

/**
 * crank_render_place_data_get_culled_array:
 * @pdata: A Place Data.
 * @entities: (transfer none): Array of entities.
 * @position: Position of view.
 * @projection: Projection of view.
 * @tindex: Type index.
 *
 * Adds items to @entities, which is frustum culled.
 *
 * Returns: (transfer none): @entities, with added entities.
 */
GPtrArray*
crank_render_place_data_get_culled_array (CrankRenderPlaceData *pdata,
                                          GPtrArray            *entities,
                                          const CrankPlane3    *culls,
                                          const guint           nculls,
                                          const guint           tindex)
{
  return crank_octree_set_add_culled_array (pdata->entity_sets[tindex],
                                            entities,
                                            culls, nculls);
}
