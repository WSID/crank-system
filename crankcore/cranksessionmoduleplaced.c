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


#define CRANKCORE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "crankplaceentity.h"

#include "cranksession.h"
#include "cranksessionmodule.h"
#include "cranksessionmoduleplaced.h"


//////// Virtual function override /////////////////////////////////////////////

static void crank_session_module_placed_constructed (GObject *object);

static void crank_session_module_placed_dispose (GObject *object);



//////// Private functions /////////////////////////////////////////////////////

static void alloc_data_fini (gpointer alloc_data);

static void fini_pointer (gpointer data,
                          gpointer userdata);

static void fini_boxed (gpointer data,
                        gpointer userdata);

//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _AllocData {
  goffset         offset;
  gssize          size;
  GFunc           fini;
  gpointer        fini_userdata;
  GDestroyNotify  fini_destroy;
} AllocData;

typedef struct _CrankSessionModulePlacedPrivate {
  // Allocation Data
  GArray *alloc_place;
  GArray *alloc_entity;

  gsize place_base_size;
  gsize entity_base_size;
  gsize place_size;
  gsize entity_size;

  // Places
  GPtrArray *places;
  //GPtrArray *places_active;

  // Entities
  GPtrArray *entities;
  GPtrArray *entities_placeless;

} CrankSessionModulePlacedPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CrankSessionModulePlaced,
                            crank_session_module_placed,
                            CRANK_TYPE_SESSION_MODULE)


//////// GTypeInstance /////////////////////////////////////////////////////////

static void
crank_session_module_placed_init (CrankSessionModulePlaced *self)
{
}

static void
crank_session_module_placed_class_init (CrankSessionModulePlacedClass *c)
{
  GObjectClass *c_gobject = G_OBJECT_CLASS (c);

  c_gobject->constructed =crank_session_module_placed_constructed;
  c_gobject->dispose = crank_session_module_placed_dispose;
}


//////// GObject ///////////////////////////////////////////////////////////////

static void
crank_session_module_placed_constructed (GObject *object)
{
  GObjectClass *pc_gobject;
  CrankSessionModulePlaced *module;
  CrankSessionModulePlacedPrivate *priv;

  pc_gobject = (GObjectClass*) crank_session_module_placed_parent_class;
  pc_gobject->constructed (object);

  module = (CrankSessionModulePlaced*) object;
  priv = crank_session_module_placed_get_instance_private (module);

  priv->alloc_place = g_array_new(FALSE, TRUE, sizeof(AllocData));
  priv->alloc_entity = g_array_new(FALSE, TRUE, sizeof(AllocData));
  g_array_set_clear_func (priv->alloc_place, alloc_data_fini);
  g_array_set_clear_func (priv->alloc_entity, alloc_data_fini);

  priv->place_size = priv->place_base_size;
  priv->entity_size = priv->entity_base_size;

  priv->places = g_ptr_array_new ();
  priv->entities = g_ptr_array_new ();
  priv->entities_placeless = g_ptr_array_new ();
}

static void
crank_session_module_placed_dispose (GObject *object)
{
  GObjectClass *pc_gobject;
  CrankSessionModulePlaced* module;
  CrankSessionModulePlacedPrivate* priv;

  pc_gobject = (GObjectClass*) crank_session_module_placed_parent_class;

  module = (CrankSessionModulePlaced*)object;
  priv = crank_session_module_placed_get_instance_private (module);

  g_array_unref (priv->alloc_place);
  g_array_unref (priv->alloc_entity);

  if (priv->places->len != 0)
    g_error ("Places are left and module is being disposed.");

  if (priv->entities->len != 0)
    g_error ("Entities are left and module is being disposed.");

  g_ptr_array_unref (priv->places);
  g_ptr_array_unref (priv->entities);
  g_ptr_array_unref (priv->entities_placeless);

  pc_gobject->dispose (object);
}



//////// Private Functions /////////////////////////////////////////////////////

static void
alloc_data_fini (gpointer data)
{
  AllocData *alloc_data = (AllocData*) data;

  alloc_data->fini_destroy (alloc_data->fini_userdata);
}

static void
fini_pointer (gpointer data,
              gpointer userdata)
{
  gpointer *pptr = (gpointer*)data;
  GDestroyNotify free_func = (GDestroyNotify)userdata;

  if (*pptr != NULL)
    free_func (*pptr);
}

static void
fini_boxed (gpointer data,
            gpointer userdata)
{
  gpointer *pptr = (gpointer*)data;
  GType gtype = (GType) userdata;

  if (*pptr != NULL)
    g_boxed_free (gtype, *pptr);
}


//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_session_module_placed_get_place_base_size:
 * @module: A Module.
 *
 * Get base size for #CrankPlaceBase, without attachments.
 *
 * Returns: Base size of #CrankPlaceBase.
 */
gsize
crank_session_module_placed_get_place_base_size (CrankSessionModulePlaced *module)
{
  CrankSessionModulePlacedPrivate *priv;
  priv = crank_session_module_placed_get_instance_private (module);

  return priv->place_base_size;
}

/**
 * crank_session_module_placed_get_entity_base_size:
 * @module: A Module.
 *
 * Get base size for #CrankEntityBase, without attachments.
 *
 * Returns: Base size of #CrankEntityBase.
 */
gsize
crank_session_module_placed_get_entity_base_size (CrankSessionModulePlaced *module)
{
  CrankSessionModulePlacedPrivate *priv;
  priv = crank_session_module_placed_get_instance_private (module);

  return priv->entity_base_size;
}


/**
 * crank_session_module_placed_get_place_size:
 * @module: A Module.
 *
 * Get allocated size for #CrankPlaceBase.
 *
 * Returns: Allocated size of #CrankPlaceBase.
 */
gsize
crank_session_module_placed_get_place_size (CrankSessionModulePlaced *module)
{
  CrankSessionModulePlacedPrivate *priv;
  priv = crank_session_module_placed_get_instance_private (module);

  return priv->place_size;
}



/**
 * crank_session_module_placed_get_entity_size:
 * @module: A Module.
 *
 * Get allocated size for #CrankEntityBase.
 *
 * Returns: Allocated size of #CrankEntityBase.
 */
gsize
crank_session_module_placed_get_entity_size (CrankSessionModulePlaced* module)
{
  CrankSessionModulePlacedPrivate *priv;
  priv = crank_session_module_placed_get_instance_private (module);

  return priv->entity_size;
}



//////// Attaching allocations /////////////////////////////////////////////////

/**
 * crank_session_module_placed_attach_place_alloc_full:
 * @module: A Module.
 * @size: Size of attached allocation.
 * @fini: (scope notified): Finalize function for attached allocation.
 * @fini_userdata: (closure fini): Userdata for @fini.
 * @fini_destroy: (destroy fini_userdata): Destroy function for @fini_userdata.
 * @offset: (out caller-allocates): Offset of allocation.
 *
 * Attaches allocation to #CrankPlaceBase.
 *
 * Returns: A ticket for this attachment.
 */
guint
crank_session_module_placed_attach_place_alloc_full (CrankSessionModulePlaced *module,
                                                     const gsize               size,
                                                     GFunc                     fini,
                                                     gpointer                  fini_userdata,
                                                     GDestroyNotify            fini_destroy,
                                                     goffset                  *offset)
{
  CrankSessionModulePlacedPrivate *priv;
  AllocData alloc_data;
  guint     ticket;

  priv = crank_session_module_placed_get_instance_private (module);

  alloc_data.offset = priv->place_size;
  alloc_data.size = size;
  alloc_data.fini = fini;
  alloc_data.fini_userdata = fini_userdata;
  alloc_data.fini_destroy = fini_destroy;

  ticket = priv->alloc_place->len;
  *offset = alloc_data.offset;

  g_array_append_val (priv->alloc_place, alloc_data);

  priv->place_size += size;

  return ticket;
}

/**
 * crank_session_module_placed_attach_place_alloc:
 * @module: A Module.
 * @size: Size of attached allocation.
 * @fini: Finalize function for allocated attachement.
 * @offset: (out): Offset of allocation.
 *
 * Attaches allocation to #CrankPlaceBase.
 *
 * Returns: A Ticket for this allocation.
 */
guint
crank_session_module_placed_attach_place_alloc (CrankSessionModulePlaced *module,
                                                const gsize               size,
                                                GDestroyNotify            fini,
                                                goffset                  *offset)
{
  return crank_session_module_placed_attach_place_alloc_full (module,
                                                              size,
                                                              (GFunc) fini, NULL, NULL,
                                                              offset);
}


/**
 * crank_session_module_placed_attach_place_alloc_pointer:
 * @module: A Module.
 * @fini: Free function for attached pointer.
 * @offset: (out): Offset of allocation.
 *
 * Attaches pointer allocation to #CrankPlaceBase. @fini will be passed to
 * the pointer itself, not the allocation.
 *
 * Returns: A Ticket for this allocation.
 */
guint
crank_session_module_placed_attach_place_alloc_pointer (CrankSessionModulePlaced *module,
                                                        GDestroyNotify            fini,
                                                        goffset                  *offset)
{
  return crank_session_module_placed_attach_place_alloc_full (module,
                                                              sizeof (gpointer),
                                                              fini_pointer, fini, NULL,
                                                              offset);
}

/**
 * crank_session_module_placed_attach_place_alloc_boxed:
 * @module: A Module.
 * @btype: #GType of boxed pointer.
 * @offset: (out): Offset of allocaiton.
 *
 * Attaches boxed pointer allocation to #CrankPlaceBase. attached pointer will
 * be finalized through g_boxed_free().
 *
 * Returns: A Ticket for this allocation.
 */
guint
crank_session_module_placed_attach_place_alloc_boxed (CrankSessionModulePlaced *module,
                                                      const GType               btype,
                                                      goffset                  *offset)
{
  return crank_session_module_placed_attach_place_alloc_full (module,
                                                              sizeof (gpointer),
                                                              fini_boxed, (gpointer)btype, NULL,
                                                              offset);
}

/**
 * crank_session_module_placed_attach_place_alloc_object:
 * @module: A Module.
 * @offset: (out): Offset of allocaiton.
 *
 * Attaches #GObject pointer to #CrankPlaceBase. attached pointer will
 * be finalized through g_object_unref().
 *
 * Returns: A Ticket for this allocation.
 */
guint
crank_session_module_placed_attach_place_alloc_object (CrankSessionModulePlaced *module,
                                                       goffset                  *offset)
{
  return crank_session_module_placed_attach_place_alloc_pointer (module, g_object_unref, offset);
}



/**
 * crank_session_module_placed_attach_entity_alloc_full:
 * @module: A Module.
 * @size: Size of attached allocation.
 * @fini: (scope notified): Finalize function for attached allocation.
 * @fini_userdata: (closure fini): Userdata for @fini.
 * @fini_destroy: (destroy fini_userdata): Destroy function for @fini_userdata.
 * @offset: (out caller-allocates): Offset of allocation.
 *
 * Attaches allocation to #CrankEntityBase.
 *
 * Returns: A ticket for this attachment.
 */
guint
crank_session_module_placed_attach_entity_alloc_full (CrankSessionModulePlaced *module,
                                                      const gsize               size,
                                                      GFunc                     fini,
                                                      gpointer                  fini_userdata,
                                                      GDestroyNotify            fini_destroy,
                                                      goffset                  *offset)
{
  CrankSessionModulePlacedPrivate *priv;
  AllocData alloc_data;
  guint     ticket;

  priv = crank_session_module_placed_get_instance_private (module);

  alloc_data.offset = priv->entity_size;
  alloc_data.size = size;
  alloc_data.fini = fini;
  alloc_data.fini_userdata = fini_userdata;
  alloc_data.fini_destroy = fini_destroy;

  ticket = priv->alloc_entity->len;
  *offset = alloc_data.offset;

  g_array_append_val (priv->alloc_entity, alloc_data);

  priv->entity_size += size;

  return ticket;
}

/**
 * crank_session_module_placed_attach_entity_alloc:
 * @module: A Module.
 * @size: Size of attached allocation.
 * @fini: Finalize function for attached allocation.
 * @offset: (out caller-allocates): Offset of allocation.
 *
 * Attaches allocation to #CrankEntityBase.
 *
 * Returns: A ticket for this attachment.
 */
guint
crank_session_module_placed_attach_entity_alloc (CrankSessionModulePlaced *module,
                                                 const gsize               size,
                                                 GDestroyNotify            fini,
                                                 goffset                  *offset)
{
  return crank_session_module_placed_attach_entity_alloc_full (module,
                                                               size,
                                                               (GFunc) fini, NULL, NULL,
                                                               offset);
}

/**
 * crank_session_module_placed_attach_entity_alloc_pointer:
 * @module: A Module.
 * @fini: Finalize function for attached allocation.
 * @offset: (out caller-allocates): Offset of allocation.
 *
 * Attaches pointer allocation to #CrankEntityBase. @fini will be passed to
 * the pointer itself, not the allocation.
 *
 * Returns: A Ticket for this allocation.
 */
guint
crank_session_module_placed_attach_entity_alloc_pointer (CrankSessionModulePlaced *module,
                                                         GDestroyNotify            fini,
                                                         goffset                  *offset)
{
  return crank_session_module_placed_attach_entity_alloc_full (module,
                                                               sizeof (gpointer),
                                                               fini_pointer, (gpointer) fini, NULL,
                                                               offset);
}

/**
 * crank_session_module_placed_attach_entity_alloc_boxed:
 * @module: A Module.
 * @btype: #GType of boxed pointer.
 * @offset: (out): Offset of allocaiton.
 *
 * Attaches boxed pointer allocation to #CrankEntityBase. attached pointer will
 * be finalized through g_boxed_free().
 *
 * Returns: A Ticket for this allocation.
 */
guint
crank_session_module_placed_attach_entity_alloc_boxed (CrankSessionModulePlaced *module,
                                                       const GType               btype,
                                                       goffset                  *offset)
{
  return crank_session_module_placed_attach_entity_alloc_full (module,
                                                               sizeof (gpointer),
                                                               fini_pointer, (gpointer) btype, NULL,
                                                               offset);
}

/**
 * crank_session_module_placed_attach_entity_alloc_object:
 * @module: A Module.
 * @offset: (out): Offset of allocaiton.
 *
 * Attaches object pointer allocation to #CrankEntityBase. Attached pointer will
 * be finalized through g_object_unref().
 *
 * Returns: A Ticket for this allocation.
 */
guint
crank_session_module_placed_attach_entity_alloc_object (CrankSessionModulePlaced *module,
                                                        goffset                  *offset)
{
  return crank_session_module_placed_attach_entity_alloc_pointer (module,
                                                                  g_object_unref,
                                                                  offset);
}


//////// Allocations ///////////////////////////////////////////////////////////

/**
 * crank_session_module_placed_get_place_alloc_offset:
 * @module: A Module.
 * @ticket: index of attachment.
 *
 * Gets offset of attachement in #CrankPlaceBase.
 *
 * Returns: offset of attachment.
 */
goffset
crank_session_module_placed_get_place_alloc_offset (CrankSessionModulePlaced *module,
                                                    const guint               ticket)
{
  CrankSessionModulePlacedPrivate *priv;
  AllocData *allocation;
  priv = crank_session_module_placed_get_instance_private (module);

  allocation = & g_array_index (priv->alloc_place, AllocData, ticket);

  return allocation->offset;
}

/**
 * crank_session_module_placed_get_place_alloc_size:
 * @module: A Module.
 * @ticket: Index of attachment.
 *
 * Gets size of attachment in #CrankPlaceBase.
 *
 * Returns: Size of attachment.
 */
gsize
crank_session_module_placed_get_place_alloc_size (CrankSessionModulePlaced *module,
                                                  const guint               ticket)
{
  CrankSessionModulePlacedPrivate *priv;
  AllocData *allocation;
  priv = crank_session_module_placed_get_instance_private (module);

  allocation = & g_array_index (priv->alloc_place, AllocData, ticket);

  return allocation->size;
}

/**
 * crank_session_module_placed_get_entity_alloc_offset:
 * @module: A Module.
 * @ticket: index of attachment.
 *
 * Gets offset of attachement in #CrankEntityBase.
 *
 * Returns: offset of attachment.
 */
goffset
crank_session_module_placed_get_entity_alloc_offset (CrankSessionModulePlaced *module,
                                                     const guint               ticket)
{
  CrankSessionModulePlacedPrivate *priv;
  AllocData *allocation;
  priv = crank_session_module_placed_get_instance_private (module);

  allocation = & g_array_index (priv->alloc_entity, AllocData, ticket);

  return allocation->offset;
}


/**
 * crank_session_module_placed_get_entity_alloc_size:
 * @module: A Module.
 * @ticket: Index of attachment.
 *
 * Gets size of attachment in #CrankEntityBase.
 *
 * Returns: Size of attachment.
 */
goffset
crank_session_module_placed_get_entity_alloc_size (CrankSessionModulePlaced *module,
                                                   const guint               ticket)
{
  CrankSessionModulePlacedPrivate *priv;
  AllocData *allocation;
  priv = crank_session_module_placed_get_instance_private (module);

  allocation = & g_array_index (priv->alloc_entity, AllocData, ticket);

  return allocation->size;
}

