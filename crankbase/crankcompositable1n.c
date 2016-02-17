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
 * SECTION: crankcompositable1n
 * @title: CrankCompositable1N
 * @short_description: A compositable that can be added up to 1 composite.
 * @include: crankbase.h
 * @stability: Unstable
 *
 * Sometimes, #CrankCompositable may be useful to be added up to 1 composite,
 * so that it can manage composite much better.
 *
 * This class is provided for base class of this kind of compositables.
 *
 * The name comes from relation of composite and compositable is 1 to N.
 */

#define _CRANKBASE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankcomposite.h"
#include "crankcompositable.h"
#include "crankcompositable1n.h"

//////// List of virtual functions /////////////////////////////////////////////

static void   crank_compositable_1n_get_property (GObject    *object,
                                                  guint       prop_id,
                                                  GValue     *value,
                                                  GParamSpec *pspec);

static gboolean crank_compositable_1n_adding (CrankCompositable  *compositable,
                                              CrankComposite     *composite,
                                              GError            **error);

static gboolean crank_compositable_1n_removing (CrankCompositable  *compositable,
                                                CrankComposite     *composite,
                                                GError            **error);





//////// Properties and signals ////////////////////////////////////////////////

enum {
  PROP_0,
  PROP_COMPOSITE,

  PROP_COUNTS
};

static GParamSpec *pspecs[PROP_COUNTS] = {NULL};




//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankCompositable1NPrivate
{
  CrankComposite *composite;
} CrankCompositable1NPrivate;


G_DEFINE_TYPE_WITH_PRIVATE (CrankCompositable1N,
                            crank_compositable_1n,
                            CRANK_TYPE_COMPOSITABLE)






//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_compositable_1n_init (CrankCompositable1N *self)
{
}

static void
crank_compositable_1n_class_init (CrankCompositable1NClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);
  CrankCompositableClass *c_compositable = CRANK_COMPOSITABLE_CLASS (c);

  c_gobject->get_property = crank_compositable_1n_get_property;
  c_compositable->adding = crank_compositable_1n_adding;
  c_compositable->removing = crank_compositable_1n_removing;

  pspecs[PROP_COMPOSITE] =
  g_param_spec_object ("composite", "Composite", "Composite object that holds this",
                       CRANK_TYPE_COMPOSITE,
                       G_PARAM_READABLE |
                       G_PARAM_STATIC_STRINGS );
}





//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_compositable_1n_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  CrankCompositable1N *self = (CrankCompositable1N*) object;

  switch (prop_id)
    {
    case PROP_COMPOSITE:
      g_value_set_object (value,
                          crank_compositable_1n_get_composite (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}





//////// CrankCompositable /////////////////////////////////////////////////////

static gboolean
crank_compositable_1n_adding (CrankCompositable  *compositable,
                              CrankComposite     *composite,
                              GError            **error)
{
  CrankCompositableClass *pc = crank_compositable_1n_parent_class;
  CrankCompositable1N *self = (CrankCompositable1N*) compositable;
  CrankCompositable1NPrivate *priv;

  priv = crank_compositable_1n_get_instance_private (self);

  if (priv->composite != NULL)
    {
      g_set_error (error,
                   CRANK_COMPOSITE_ERROR,
                   CRANK_COMPOSITE_ERROR_ALREADY_HAS_COMPOSITE,
                   "Compositable already has composite object.\n"
                   "  %s@%p has %s@%p but being added to %s@%p",
                   G_OBJECT_TYPE_NAME (self), self,
                   G_OBJECT_TYPE_NAME (priv->composite), priv->composite,
                   G_OBJECT_TYPE_NAME (composite), composite);
      return FALSE;
    }

  else if (pc->adding (compositable, composite, error))
    {
      priv->composite = composite;
      g_object_notify_by_pspec ((GObject*)compositable, pspecs[PROP_COMPOSITE]);
      return TRUE;
    }

  else
    {
      return FALSE;
    }
}

static gboolean
crank_compositable_1n_removing (CrankCompositable  *compositable,
                                CrankComposite     *composite,
                                GError            **error)
{
  CrankCompositableClass *pc = crank_compositable_1n_parent_class;
  CrankCompositable1N *self = (CrankCompositable1N*) compositable;
  CrankCompositable1NPrivate *priv;

  priv = crank_compositable_1n_get_instance_private (self);

  g_assert (priv->composite == composite);

  if (pc->removing (compositable, composite, error))
    {
      priv->composite = NULL;
      g_object_notify_by_pspec ((GObject*)compositable, pspecs[PROP_COMPOSITE]);
      return TRUE;
    }

  else
    {
      return FALSE;
    }
}





//////// Public Functions //////////////////////////////////////////////////////

/**
 * crank_compositable_1n_get_composite:
 * @compositable: A Compositable.
 *
 * Gets a composite that holds this compositable. If no composite holds this,
 * %NULL will be returned.
 *
 * Returns: (nullable) (transfer none): A Compositable.
 */
CrankComposite*
crank_compositable_1n_get_composite (CrankCompositable1N *compositable)
{
  return G_PRIVATE_FIELD (CrankCompositable1N, compositable,
                          CrankComposite*, composite);
}
