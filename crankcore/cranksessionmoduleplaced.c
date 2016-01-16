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

#include "cranksession.h"
#include "cranksessionmodule.h"
#include "cranksessionmoduleplaced.h"


//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_TYPE (CrankSessionModulePlaced,
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
}



//////// Properties ////////////////////////////////////////////////////////////


gsize
crank_session_module_placed_get_place_base_size (CrankSessionModulePlaced *module)
{
  return CRANK_SESSION_MODULE_PLACED_GET_CLASS (module)->get_place_base_size (module);
}

gsize
crank_session_module_placed_get_place_size (CrankSessionModulePlaced *module)
{
  return CRANK_SESSION_MODULE_PLACED_GET_CLASS (module)->get_place_base_size (module);
}



gsize
crank_session_module_placed_get_entity_base_size (CrankSessionModulePlaced *module)
{
  return CRANK_SESSION_MODULE_PLACED_GET_CLASS (module)->get_entity_base_size (module);
}

gsize
crank_session_module_placed_get_entity_size (CrankSessionModulePlaced* module)
{
  return CRANK_SESSION_MODULE_PLACED_GET_CLASS (module)->get_entity_base_size (module);
}



//////// Attaching allocations /////////////////////////////////////////////////

guint
crank_session_module_placed_attach_place_alloc_full (CrankSessionModulePlaced *module,
                                                     const gsize               size,
                                                     GFunc                     fini,
                                                     gpointer                  fini_userdata,
                                                     GDestroyNotify            fini_destroy,
                                                     goffset                  *offset)
{
  return 0;
}

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

guint
crank_session_module_placed_attach_place_alloc_pointer (CrankSessionModulePlaced *module,
                                                        GDestroyNotify            fini,
                                                        goffset                  *offset)
{
  return 0;
}

guint
crank_session_module_placed_attach_place_alloc_boxed (CrankSessionModulePlaced *module,
                                                      const GType               btype,
                                                      goffset                  *offset)
{
  return 0;
}

guint
crank_session_module_placed_attach_place_alloc_object (CrankSessionModulePlaced *module,
                                                       goffset                  *offset)
{
  return crank_session_module_placed_attach_place_alloc_pointer (module, g_object_unref, offset);
}





guint
crank_session_module_placed_attach_entity_alloc_full (CrankSessionModulePlaced *module,
                                                      const gsize               size,
                                                      GFunc                     fini,
                                                      gpointer                  fini_userdata,
                                                      GDestroyNotify            fini_destroy,
                                                      goffset                  *offset)
{
  return 0;
}

guint
crank_session_module_placed_attach_entity_alloc (CrankSessionModulePlaced *module,
                                                 const gsize               size,
                                                 GDestroyNotify            fini,
                                                 goffset                  *offset)
{
  return 0;
}

guint
crank_session_module_placed_attach_entity_alloc_pointer (CrankSessionModulePlaced *module,
                                                         GDestroyNotify            fini,
                                                         goffset                  *offset)
{
  return 0;
}

guint
crank_session_module_placed_attach_entity_alloc_boxed (CrankSessionModulePlaced *module,
                                                       const GType               btype,
                                                       goffset                  *offset)
{
  return 0;
}

guint
crank_session_module_placed_attach_entity_alloc_object (CrankSessionModulePlaced *module,
                                                        goffset                  *offset)
{
  return 0;
}


//////// Allocations ///////////////////////////////////////////////////////////

goffset
crank_session_module_placed_get_place_alloc_offset (CrankSessionModulePlaced *module,
                                                    const guint               ticket)
{
  return 0;
}

gsize
crank_session_module_placed_get_place_alloc_size (CrankSessionModulePlaced *module,
                                                  const guint               ticket)
{
  return 0;
}

goffset
crank_session_module_placed_get_entity_alloc_offset (CrankSessionModulePlaced *module,
                                                     const guint               ticket)
{
  return 0;
}

goffset
crank_session_module_placed_get_entity_alloc_size (CrankSessionModulePlaced *module,
                                                   const guint               ticket)
{
  return 0;
}


