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
 * SECTION: crankcomposite
 * @title: CrankComposite
 * @short_description: Composite objects that multiple compositable can be added to.
 * @stabilit: Unstable
 * @include: crankbase.h
 *
 * Represents a composite objects that compositable objects can be added.
 *
 * # Basic Relation
 *
 * Relation of #CrankCompositable and #CrankComposite is "N to N" relationship.
 * This means single #CrankComposite may have multiple #CrankCompositable,
 * while multiple #CrankComposite s have single #CrankCompositable.
 *
 * Added compositable may be queried. See crank_composite_get_compositable().
 *
 *
 * # Adding and Removing Compositable.
 *
 * A Composite and compositable is for extending functionality of composite
 * object in a different way from subclassing, but rather to compositing
 * "function"s in a object.
 *
 * As a result, adding and removing requires some checking. Upon adding and
 * removing, following will be checked.
 *
 * * Checking for already added / removed compositables.
 * * Checking for requisition of compositables.
 *   See #CrankCompositable.
 * * Custom checking.
 *
 * ## Custom checking.
 *
 * When more advanced checking is required, either implementation of
 * #CrankComposite, #CrankCompositable may insert checks when adding and
 * removing, by overriding any of,
 *
 * * #CrankCompositeClass.add_compositable()
 * * #CrankCompositeClass.remove_compositable()
 * * #CrankCompositableClass.adding()
 * * #CrankCompositableClass.removing()
 */

#define _CRANKBASE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankvalue.h"

#include "crankcomposite.h"
#include "crankcompositable.h"


//////// Quark Definition //////////////////////////////////////////////////////

G_DEFINE_QUARK (crank-composite-error-quark, crank_composite_error);


//////// Private functions /////////////////////////////////////////////////////

//////// GObject ///////////////////////////////////////////////////////////////

static void   crank_composite_dispose   (GObject *object);

static void   crank_composite_finalize  (GObject *object);


//////// CrankComposite ////////////////////////////////////////////////////////

static gboolean accumulator_false_to_quit (GSignalInvocationHint *hint,
                                           GValue                *retval,
                                           const GValue          *handler_retval,
                                           gpointer               data);

static gboolean crank_composite_def_add_compositable (CrankComposite     *composite,
                                                      CrankCompositable  *compositable,
                                                      GError            **error);

static gboolean crank_composite_def_remove_compositable (CrankComposite     *composite,
                                                         CrankCompositable  *compositable,
                                                         GError            **error);

//////// Properties and signals ////////////////////////////////////////////////


//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankCompositePrivate
{
  GPtrArray *compositables;
} CrankCompositePrivate;


G_DEFINE_TYPE_WITH_PRIVATE (CrankComposite,
                            crank_composite,
                            G_TYPE_OBJECT);


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_composite_init (CrankComposite *composite)
{
  CrankCompositePrivate *priv = crank_composite_get_instance_private (composite);
  priv->compositables = g_ptr_array_new_with_free_func (g_object_unref);
}


static void
crank_composite_class_init (CrankCompositeClass *c)
{
  GObjectClass *c_gobject;

  c_gobject = G_OBJECT_CLASS (c);
  c_gobject->dispose = crank_composite_dispose;
  c_gobject->finalize = crank_composite_finalize;

  c->add_compositable = crank_composite_def_add_compositable;
  c->remove_compositable = crank_composite_def_remove_compositable;
}






//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_composite_dispose (GObject *object)
{
  GObjectClass *pc = crank_composite_parent_class;
  CrankComposite *self = (CrankComposite*)object;
  CrankCompositePrivate *priv = crank_composite_get_instance_private (self);

  g_ptr_array_set_size (priv->compositables, 0);

  pc->dispose (object);
}


static void
crank_composite_finalize (GObject *object)
{
  GObjectClass *pc = crank_composite_parent_class;
  CrankComposite *self = (CrankComposite*)object;
  CrankCompositePrivate *priv = crank_composite_get_instance_private (self);

  g_ptr_array_unref (priv->compositables);

  pc->finalize (object);
}




//////// CrankComposite ////////////////////////////////////////////////////////

static gboolean
crank_composite_def_add_compositable (CrankComposite     *composite,
                                      CrankCompositable  *compositable,
                                      GError            **error)
{
  CrankCompositePrivate *priv = crank_composite_get_instance_private (composite);
  guint     i;

  // First check a compositable is already.
  if (crank_composite_contains_compositable (composite, compositable))
    {
      g_set_error (error, CRANK_COMPOSITE_ERROR,
                   CRANK_COMPOSITE_ERROR_ALREADY_HAS_COMPOSITABLE,
                   "Compositable is already added to compositable.\n"
                   "%s@%p <= %s@%p",
                   G_OBJECT_TYPE_NAME (composite), composite,
                   G_OBJECT_TYPE_NAME (compositable), compositable);
      return FALSE;
    }

  // Do adding
  if (crank_compositable_adding (compositable, composite, error))
    {
      g_ptr_array_add (priv->compositables, compositable);
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

static gboolean
crank_composite_def_remove_compositable (CrankComposite     *composite,
                                         CrankCompositable  *compositable,
                                         GError            **error)
{
  CrankCompositePrivate *priv = crank_composite_get_instance_private (composite);
  guint     i;

  // First check a compositable is already.
  if (! crank_composite_contains_compositable (composite, compositable))
    {
      g_set_error (error, CRANK_COMPOSITE_ERROR,
                   CRANK_COMPOSITE_ERROR_NOT_HAVE_COMPOSITABLE,
                   "Compositable is not in the compositable.\n"
                   "%s@%p <= %s@%p",
                   G_OBJECT_TYPE_NAME (composite), composite,
                   G_OBJECT_TYPE_NAME (compositable), compositable);
      return FALSE;
    }

  // Do removing
  if (crank_compositable_removing (compositable, composite, error))
    {
      g_ptr_array_remove (priv->compositables, compositable);
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}







//////// Public Functions //////////////////////////////////////////////////////

//////// Compositable add / remove /////////////////////////////////////////////

/**
 * crank_composite_add_compositable:
 * @composite: A Compositable.
 * @compositable: A Compositable.
 * @error: Error.
 *
 * Adds compositable to the composite. Implementation may override this to
 * reject compositable.
 *
 * Throwables:
 * * CRANK_COMPOSITE_ERROR_REJECTED:
 *   Implementation should throw a error if it is rejecting a compositable.
 *
 * * CRANK_COMPOSITE_ERROR_ALREADY_HAS_COMPOSITABLE:
 *   @composite already has @compositable.
 *
 * Returns: (skip): Whether adding was succesful.
 */
gboolean
crank_composite_add_compositable (CrankComposite     *composite,
                                  CrankCompositable  *compositable,
                                  GError            **error)
{
  CrankCompositeClass *c = CRANK_COMPOSITE_GET_CLASS (composite);
  return c->add_compositable (composite, compositable, error);
}


/**
 * crank_composite_remove_compositable:
 * @composite: A Compositable.
 * @compositable: A Compositable.
 * @error: Error.
 *
 * Adds compositable to the composite. Implementation may override this to
 * prevent compositable to be removed from.
 *
 * Throwables:
 * * CRANK_COMPOSITE_ERROR_REJECTED:
 *   Implementation should throw a error if it is preventing a compositable from
 *   removing.
 *
 * * CRANK_COMPOSITE_ERROR_NOT_HAVE_COMPOSITABLE:
 *   @composite does not have @compositable.
 *
 * Returns: (skip): Whether removing was succesful.
 */
gboolean
crank_composite_remove_compositable (CrankComposite     *composite,
                                     CrankCompositable  *compositable,
                                     GError            **error)
{
  CrankCompositeClass *c = CRANK_COMPOSITE_GET_CLASS (composite);
  return c->remove_compositable (composite, compositable, error);
}


//////// Compositable getting //////////////////////////////////////////////////

/**
 * crank_composite_get_compositable:
 * @composite: A Composite.
 * @index: A Index.
 *
 * Gets compositable in this composite.
 *
 * Returns: (transfer none): A Compositable.
 */
CrankCompositable*
crank_composite_get_compositable (CrankComposite *composite,
                                  const guint     index)
{
  CrankCompositePrivate *priv = crank_composite_get_instance_private (composite);
  return (CrankCompositable*) priv->compositables->pdata[index];
}

/**
 * crank_composite_get_compositable_by_gtype:
 * @composite: A Composite.
 * @type: A #GType of #CrankCompositable
 *
 * Gets compositable by type.
 *
 * A Composite may contains multiple compositables that inherits from @type. In
 * this case, first one is returned.
 *
 * If @type is not a type of #CrankCompositable, warning will be issued.
 *
 * Returns: (transfer none) (nullable): A Compositable.
 */
CrankCompositable*
crank_composite_get_compositable_by_gtype  (CrankComposite *composite,
                                            const GType     type)
{
  CrankCompositePrivate *priv = crank_composite_get_instance_private (composite);
  guint i;

  g_return_val_if_fail (g_type_is_a (type, CRANK_TYPE_COMPOSITABLE), NULL);

  for (i = 0; i < priv->compositables->len; i++)
    {
      CrankCompositable* compositable = priv->compositables->pdata[i];
      if (g_type_is_a (G_OBJECT_TYPE (compositable), type))
        return compositable;
    }
  return NULL;
}

/**
 * crank_composite_get_ncompositables:
 * @composite: A Composite.
 *
 * Gets number of compositable that @composite holds.
 *
 * Returns: Number of compositable.
 */
guint
crank_composite_get_ncompositables (CrankComposite *composite)
{
  CrankCompositePrivate *priv = crank_composite_get_instance_private (composite);
  return priv->compositables->len;
}



/**
 * crank_composite_contains_compositable:
 * @composite: A Composite.
 * @compositable: (transfer none): A Compositable.
 *
 * Checks whether compositable instance is in this composite.
 *
 * Returns: Whether @compositable is in @composite.
 */
gboolean
crank_composite_contains_compositable   (CrankComposite    *composite,
                                         CrankCompositable *compositable)
{
  CrankCompositePrivate *priv = crank_composite_get_instance_private (composite);
  guint i;

  for (i = 0; i < priv->compositables->len; i++)
    {
      if (compositable == priv->compositables->pdata[i])
        return TRUE;
    }
  return FALSE;
}


/**
 * crank_composite_foreach_compositable:
 * @composite: A Composite.
 * @func: (scope call): Function to iterate.
 * @userdata: (closure func): Userdata for @func.
 *
 * Iterate @func for each compositable in @composite.
 */
void
crank_composite_foreach_compositable (CrankComposite *composite,
                                      GFunc           func,
                                      gpointer        userdata)
{
  CrankCompositePrivate *priv = crank_composite_get_instance_private (composite);

  g_ptr_array_foreach (priv->compositables, func, userdata);
}
