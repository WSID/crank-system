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
 * SECTION: crankcompositable
 * @title: CrankCompositable
 * @short_description: Compositable objects that can be added to Composite.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Represents a compositable objects that can be added to a composite.
 *
 * # Basic Relation
 *
 * Relation of #CrankCompositable and #CrankComposite is "N to N" relationship.
 * This means single #CrankComposite may have multiple #CrankCompositable,
 * while multiple #CrankComposite s have single #CrankCompositable.
 *
 * #CrankCompositable does not track #crankComposite that holds it, while
 * #CrankComposite tracks #CrankCompositable that it holds.
 *
 * If tracking is required, then override #CrankCompositableClass.adding() and
 * #CrankCompositableClass.removing() to have chance to start and stop tracking.
 *
 *
 * # Requisition
 *
 * A #CrankCompositable carrys requisition informations, that describes required
 * #GType s for it to work properly. When this has requisitions, all requisitions
 * should be met in each #CrankComposite that holds the compositable.
 *
 * There are 2 kind of requisition for this.
 *
 * ## Composite Requisition.
 *
 * This describes requirements of #CrankComposite that holds this. All interface
 * requisition that does not require #CrankCompositable will be added to this
 * category.
 *
 * The compositable won't added to composite which does not implement / inherit
 * from these type.
 *
 * ## Compositable Requisition.
 *
 * This describes requirements of #CrankCompositable that are added to the
 * composite. A Compositable type may have multiple requisitions of
 * compositable class types, as multiple compositable may be added.
 *
 * The compositable can be added, after all compositables of required types, are
 * added.
 */

#define _CRANKBASE_INSIDE

#include <string.h>

#include <glib.h>
#include <glib-object.h>

#include "crankvalue.h"

#include "crankcomposite.h"
#include "crankcompositable.h"

//////// Type Private datas ////////////////////////////////////////////////////


typedef struct _CrankCompositableClassPrivate
{
  // Requisitions.
  GArray  *req_composite;
  GArray  *req_compositables;

} CrankCompositableClassPrivate;

static inline CrankCompositableClassPrivate*
crank_compositable_class_get_private (CrankCompositableClass *c)
{
  return G_TYPE_CLASS_GET_PRIVATE (c,
                                   CRANK_TYPE_COMPOSITABLE,
                                   CrankCompositableClassPrivate);
}










//////// Private Functions /////////////////////////////////////////////////////

//////// List of virtual functions /////////////////////////////////////////////

static gboolean crank_compositable_def_adding (CrankCompositable  *compositable,
                                               CrankComposite     *composite,
                                               GError            **error);

static gboolean crank_compositable_def_removing (CrankCompositable  *compositable,
                                                 CrankComposite     *composite,
                                                 GError            **error);










//////// Type Definitions //////////////////////////////////////////////////////

G_DEFINE_TYPE_WITH_CODE (CrankCompositable,
                         crank_compositable,
                         G_TYPE_INITIALLY_UNOWNED,
                         g_type_add_class_private (g_define_type_id,
                                                   sizeof (CrankCompositableClassPrivate)))







//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_compositable_init (CrankCompositable *self)
{
}

static void
crank_compositable_class_init (CrankCompositableClass *c)
{
  c->adding = crank_compositable_def_adding;
  c->removing = crank_compositable_def_removing;
}







//////// CrankCompositable /////////////////////////////////////////////////////

static gboolean
crank_compositable_def_adding (CrankCompositable  *compositable,
                               CrankComposite     *composite,
                               GError            **error)
{
  CrankCompositableClass *c;
  CrankCompositableClassPrivate *cpriv;

  c = CRANK_COMPOSITABLE_GET_CLASS (compositable);
  cpriv = crank_compositable_class_get_private (c);

  // Check for requisition.
  // 1. composite requisitions.
    {
      GType type_composite = G_OBJECT_TYPE (composite);
      guint i;
      for (i = 0; i < cpriv->req_composite->len; i++)
        {
          GType type_req = g_array_index (cpriv->req_composite, GType, i);

          if (! g_type_is_a (type_composite, type_req))
            {
              g_set_error (error,
                           CRANK_COMPOSITE_ERROR,
                           CRANK_COMPOSITE_ERROR_REQ_NOT_MEET,
                           "Composite requisition not met:\n"
                           "  %s: %s@%p is not a %s",
                           G_OBJECT_TYPE_NAME (compositable),
                           G_OBJECT_TYPE_NAME (composite), composite,
                           g_type_name (type_req));
              return FALSE;
            }
        }
    }

  // 2. compositable requisitions.
    {
      guint i;

      for (i = 0; i < cpriv->req_compositables->len; i++)
        {
          GType type_req = g_array_index (cpriv->req_compositables, GType, i);

          if (crank_composite_get_compositable_by_gtype (composite, type_req) == NULL)
            {
              g_set_error (error,
                           CRANK_COMPOSITE_ERROR,
                           CRANK_COMPOSITE_ERROR_REQ_NOT_MEET,
                           "Composite requisition not met:\n"
                           "  %s: %s@%p does not have compositable %s",
                           G_OBJECT_TYPE_NAME (compositable),
                           G_OBJECT_TYPE_NAME (composite), composite,
                           g_type_name (type_req));
              return FALSE;
            }
        }
    }

  return TRUE;
}



static gboolean
crank_compositable_def_removing (CrankCompositable  *compositable,
                                 CrankComposite     *composite,
                                 GError            **error)
{
  GType type = G_OBJECT_TYPE (compositable);
  // Checks rest compositables' requisitions.
  {
    guint i = 0;
    guint n = crank_composite_get_ncompositables (composite);

    for (i = 0; i < n; i++)
      {
        CrankCompositable *rest;
        CrankCompositableClass *rest_c = CRANK_COMPOSITABLE_GET_CLASS (rest);

        rest = crank_composite_get_compositable (composite, i);

        if (crank_compositable_class_is_required (rest_c, type))
          {
            g_set_error (error,
                         CRANK_COMPOSITE_ERROR,
                         CRANK_COMPOSITE_ERROR_REQ_NOT_MEET,
                         "Composite requisition not met:\n"
                         "  %s: %s is being removed from %s@%p, and still required by %s@%p",
                         g_type_name (type),
                         g_type_name (type),
                         G_OBJECT_TYPE_NAME (composite), composite,
                         G_OBJECT_TYPE_NAME (rest), rest);
            return FALSE;
          }
      }
  }

  return TRUE;
}








//////// Type Functions ////////////////////////////////////////////////////////

/**
 * crank_compositable_class_add_requisition:
 * @c: A Class.
 * @req: A Required #GType.
 *
 * Adds dependency for the requisition.
 */
void
crank_compositable_class_add_requisition (CrankCompositableClass *c,
                                          const GType             req)
{
  CrankCompositableClassPrivate *priv;
  GArray *array;

  priv = crank_compositable_class_get_private (c);
  array = (g_type_is_a (req, CRANK_TYPE_COMPOSITABLE)) ?
          priv->req_compositables :
          priv->req_composite;

  g_array_append_val (array, req);
}

/**
 * crank_compositable_class_is_required:
 * @c: A Class.
 * @req: A #GType to check.
 *
 * Checks whether the type is required.
 *
 * Returns: Whether the type is required.
 */
gboolean
crank_compositable_class_is_required (CrankCompositableClass *c,
                                      const GType             req)
{
  CrankCompositableClassPrivate *priv;
  GArray *array;
  guint i;

  priv = crank_compositable_class_get_private (c);
  array = (g_type_is_a (req, CRANK_TYPE_COMPOSITABLE)) ?
          priv->req_compositables :
          priv->req_composite;

  for (i = 0; i < array->len; i++)
    {
      GType reqtype = g_array_index (array, GType, i);

      if (g_type_is_a (req, reqtype))
        return TRUE;
    }
  return FALSE;
}

/**
 * crank_compositable_class_get_req_composite:
 * @c: A Class.
 * @nreq: (out): Number of requisitions.
 *
 * Gets required types for composite.
 *
 * Returns: (array length=nreq) (transfer container): Required types.
 */
GType*
crank_compositable_class_get_req_composite (CrankCompositableClass *c,
                                            guint                  *nreq)
{
  CrankCompositableClassPrivate *priv;
  priv = crank_compositable_class_get_private (c);

  return g_memdup (priv->req_composite->data,
                   priv->req_composite->len * sizeof (GType));
}


/**
 * crank_compositable_class_get_req_compositable:
 * @c: A Class.
 * @nreq: (out): Number of requisitions.
 *
 * Gets required types for compositables.
 *
 * Returns: (array length=nreq) (transfer container): Required types.
 */
GType*
crank_compositable_class_get_req_compositable(CrankCompositableClass *c,
                                              guint                  *nreq)
{
  CrankCompositableClassPrivate *priv;
  priv = crank_compositable_class_get_private (c);

  return g_memdup (priv->req_composite->data,
                   priv->req_composite->len * sizeof (GType));
}


/**
 * crank_compositable_class_get_requisitions:
 * @c: A Class.
 * @nreq: (out): Number of requisitions.
 *
 * Gets required types for compositables.
 *
 * Returns: (array length=nreq) (transfer container): Required types.
 */
GType*
crank_compositable_class_get_requisitions (CrankCompositableClass *c,
                                           guint                  *nreq)
{
  CrankCompositableClassPrivate *priv;
  GType *result;

  priv = crank_compositable_class_get_private (c);

  result = g_new (GType, priv->req_composite->len + priv->req_compositables->len);

  memcpy (result + 0,
          priv->req_composite->data,
          priv->req_composite->len * sizeof (GType));

  memcpy (result + priv->req_composite->len,
          priv->req_compositables->data,
          priv->req_compositables->len * sizeof (GType));

  return result;
}










//////// Public Functions //////////////////////////////////////////////////////

//////// Compositable Adding / Removing ////////////////////////////////////////


/**
 * crank_compositable_adding:
 * @compositable: A Compositable.
 * @composite: A Composite.
 * @error: A Error
 *
 * Checks @compositable can be added to @composite, and throw error if not.
 *
 * Default Implementation:
 *   Checks whether requisition is met, and throw error if requisitions are not
 *   met.
 *
 * Returns: whether it was succesful.
 */
gboolean
crank_compositable_adding (CrankCompositable  *compositable,
                           CrankComposite     *composite,
                           GError            **error)
{
  CrankCompositableClass *c = CRANK_COMPOSITABLE_GET_CLASS (compositable);
  return c->adding (compositable, composite, error);
}

/**
 * crank_compositable_removing:
 * @compositable: A Compositable.
 * @composite: A Composite.
 * @error: A Error
 *
 * Checks @compositable can be removed from @composite, and throw error if not.
 *
 * Default Implementation:
 *   Checks whether this action would break requisition, and throw error if it
 *   would occur.
 *
 * Returns: whether it was succesful.
 */
gboolean
crank_compositable_removing (CrankCompositable  *compositable,
                             CrankComposite     *composite,
                             GError            **error)
{
  CrankCompositableClass *c = CRANK_COMPOSITABLE_GET_CLASS (compositable);
  return c->removing (compositable, composite, error);
}
