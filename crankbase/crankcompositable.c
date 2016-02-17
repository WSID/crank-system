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
 * should be met in each #CrankComposite.
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

//////// Quarks ////////////////////////////////////////////////////////////////

#define CRANK_COMPOSITABLE_TPRIV_QUARK (crank_compositable_tpriv_quark())
G_DEFINE_QUARK (CrankCompositableTPriv, crank_compositable_tpriv);

//////// Type Private datas ////////////////////////////////////////////////////


typedef struct _CrankCompositableTPriv
{
  // Requisitions.
  GArray  *req_composite;
  GArray  *req_compositables;

} CrankCompositableTPriv;


//////// Private Functions /////////////////////////////////////////////////////

//////// List of virtual functions /////////////////////////////////////////////

static gboolean crank_compositable_def_adding (CrankCompositable  *compositable,
                                               CrankComposite     *composite,
                                               GError            **error);

static gboolean crank_compositable_def_removing (CrankCompositable  *compositable,
                                                 CrankComposite     *composite,
                                                 GError            **error);

//////// Type Private functions ////////////////////////////////////////////////

static CrankCompositableTPriv *get_tpriv (GType type);


//////// Type Definitions //////////////////////////////////////////////////////

G_DEFINE_TYPE (CrankCompositable,
               crank_compositable,
               G_TYPE_OBJECT)


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
  GType type;
  CrankCompositableTPriv *tpriv;

  type = G_OBJECT_TYPE (compositable);
  tpriv = get_tpriv (type);

  // Check for requisition.
  // 1. composite requisitions.
    {
      GType type_composite = G_OBJECT_TYPE (composite);
      guint i;
      for (i = 0; i < tpriv->req_composite->len; i++)
        {
          GType type_req = g_array_index (tpriv->req_composite, GType, i);

          if (! g_type_is_a (type_composite, type_req))
            {
              g_set_error (error,
                           CRANK_COMPOSITE_ERROR,
                           CRANK_COMPOSITE_ERROR_REQ_NOT_MEET,
                           "Composite requisition not met:\n"
                           "  %s: %s@%p is not a %s",
                           g_type_name (type),
                           G_OBJECT_TYPE_NAME (composite), composite,
                           g_type_name (type_req));
              return FALSE;
            }
        }
    }

  // 2. compositable requisitions.
    {
      guint i;

      for (i = 0; i < tpriv->req_compositables->len; i++)
        {
          GType type_req = g_array_index (tpriv->req_compositables, GType, i);

          if (crank_composite_get_compositable_by_gtype (composite, type_req) == NULL)
            {
              g_set_error (error,
                           CRANK_COMPOSITE_ERROR,
                           CRANK_COMPOSITE_ERROR_REQ_NOT_MEET,
                           "Composite requisition not met:\n"
                           "  %s: %s@%p does not have compositable %s",
                           g_type_name (type),
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
        GType rest_type;

        rest = crank_composite_get_compositable (composite, i);
        rest_type = G_OBJECT_TYPE (rest);

        if (crank_gtype_compositable_is_required (rest_type, type))
          {
            g_set_error (error,
                         CRANK_COMPOSITE_ERROR,
                         CRANK_COMPOSITE_ERROR_REQ_NOT_MEET,
                         "Composite requisition not met:\n"
                         "  %s: %s is being removed from %s@%p, and still required by %s@%p",
                         g_type_name (type),
                         g_type_name (type),
                         G_OBJECT_TYPE_NAME (composite), composite,
                         g_type_name (rest_type), rest);
            return FALSE;
          }
      }
  }

  return TRUE;
}


//////// Type Private functions ////////////////////////////////////////////////

static CrankCompositableTPriv*
get_tpriv (GType gtype)
{
  CrankCompositableTPriv *result;

  result = g_type_get_qdata (gtype, CRANK_COMPOSITABLE_TPRIV_QUARK);

  if (result == NULL)
    {
      result = g_new (CrankCompositableTPriv, 1);
      result->req_composite     = g_array_new (FALSE, FALSE, sizeof (GType));
      result->req_compositables = g_array_new (FALSE, FALSE, sizeof (GType));
      g_type_set_qdata (gtype, CRANK_COMPOSITABLE_TPRIV_QUARK, result);
    }

  return result;
}




//////// Type Functions ////////////////////////////////////////////////////////

/**
 * crank_gtype_compositable_add_requisition:
 * @type: A GType
 * @req: A Required GType.
 *
 * Adds dependency for the requisition.
 */
void
crank_gtype_compositable_add_requisition (GType type,
                                          GType req)
{
  CrankCompositableTPriv *tpriv;
  GArray *array;

  g_return_if_fail (g_type_is_a (type, CRANK_TYPE_COMPOSITABLE));

  tpriv = get_tpriv(type);
  array = (g_type_is_a (req, CRANK_TYPE_COMPOSITABLE)) ?
          tpriv->req_compositables :
          tpriv->req_composite;

  g_array_append_val (array, req);
}

/**
 * crank_gtype_compositable_is_required:
 * @type: A GType
 * @req: A GType.
 *
 * Checks whether @req is required type for @type. It takes subtypes into
 * account, so that this function may return %TRUE for subtypes.
 */
gboolean
crank_gtype_compositable_is_required (GType type,
                                      GType req)
{
  CrankCompositableTPriv *tpriv;
  GArray *array;
  guint i;

  g_return_val_if_fail (g_type_is_a (type, CRANK_TYPE_COMPOSITABLE), FALSE);

  tpriv = get_tpriv(type);
  array = (g_type_is_a (req, CRANK_TYPE_COMPOSITABLE)) ?
          tpriv->req_compositables :
          tpriv->req_composite;

  for (i = 0 ; i < array->len; i++)
    {
      GType mreq = g_array_index (array, GType, i);
      if (g_type_is_a (req, mreq))
        return TRUE;
    }

  return FALSE;
}


/**
 * crank_gtype_compositable_get_req_composite:
 * @type: A GType
 * @nreq: (out): Number of required types.
 *
 * Gets requisitions on thsi type for type of composite.
 *
 * Returns: (transfer full) (array length=nreq): Composite requirements.
 */
GType*
crank_gtype_compositable_get_req_composite (GType  type,
                                            guint *nreq)
{
  CrankCompositableTPriv *tpriv;

  if (! g_type_is_a (type, CRANK_TYPE_COMPOSITABLE))
    {
      g_warning ("Type %s is not a compositable type.", g_type_name (type));
      *nreq = 0;
      return NULL;
    }

  tpriv = get_tpriv (type);

  *nreq = tpriv->req_composite->len;
  return g_memdup (tpriv->req_composite->data,
                   tpriv->req_composite->len * sizeof (GType));
}


/**
 * crank_gtype_compositable_get_req_compositable:
 * @type: A GType
 * @nreq: (out): Number of required types.
 *
 * Gets requisitions on thsi type for type of compositables.
 *
 * Returns: (transfer full) (array length=nreq): Compositable requirements.
 */
GType*
crank_gtype_compositable_get_req_compositable (GType  type,
                                               guint *nreq)
{
  CrankCompositableTPriv *tpriv;

  if (! g_type_is_a (type, CRANK_TYPE_COMPOSITABLE))
    {
      g_warning ("Type %s is not a compositable type.", g_type_name (type));
      *nreq = 0;
      return NULL;
    }

  tpriv = get_tpriv (type);

  *nreq = tpriv->req_compositables->len;
  return g_memdup (tpriv->req_compositables->data,
                   tpriv->req_compositables->len * sizeof (GType));
}


/**
 * crank_gtype_compositable_get_requisitions:
 * @type: A GType
 * @nreq: (out): Number of required types.
 *
 * Gets requisitions on this type.
 *
 * Returns: (transfer full) (array length=nreq): Composite requirements.
 */
GType*
crank_gtype_compositable_get_requisitions (GType  type,
                                           guint *nreq)
{
  CrankCompositableTPriv *tpriv;
  GType *result;

  if (! g_type_is_a (type, CRANK_TYPE_COMPOSITABLE))
    {
      g_warning ("Type %s is not a compositable type.", g_type_name (type));
      *nreq = 0;
      return NULL;
    }

  tpriv = get_tpriv (type);

  *nreq = tpriv->req_composite->len + tpriv->req_compositables->len;
  result = g_new (GType, *nreq);

  memcpy (result,
          tpriv->req_composite->data,
          tpriv->req_composite->len * sizeof (GType));

  return memcpy (result + tpriv->req_composite->len,
                 tpriv->req_compositables->data,
                 tpriv->req_compositables->len * sizeof (GType));
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
