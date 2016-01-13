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

#include "cranksession.h"
#include "cranksessionelement.h"

//////// Type Definition ///////////////////////////////////////////////////////
//
typedef struct _CrankSessionElementPrivate {
  CrankSession *session;
  guint session_type_index;
} CrankSessionElementPrivate;

struct _CrankSessionElement
{
  GTypeInstance _basement;
  guint         _refc;
};

struct _CrankSessionElementClass
{
  GTypeClass _basement;
};

//////// Type Functions ////////////////////////////////////////////////////////

GType crank_session_element_get_type (void)
{
  static const GTypeInfo tinfo = {
    sizeof (CrankSessionElementClass), // class_size

    NULL,                              // Base init,fini
    NULL,

    NULL,                              // Class init,fini,data
    NULL,
    NULL,

    sizeof (CrankSessionElement),      // Instance size
    0,                                 // dummy
    NULL,                              // Instance init

    NULL                              // VTable
  };
  static const GTypeFundamentalInfo ftinfo = {
    G_TYPE_FLAG_CLASSED |
    G_TYPE_FLAG_INSTANTIATABLE |
    G_TYPE_FLAG_DERIVABLE |
    G_TYPE_FLAG_DEEP_DERIVABLE
  };

  static GType type_id = G_TYPE_INVALID;

  if (g_once_init_enter (&type_id))
    {
      GType m_tid = g_type_fundamental_next ();
      g_type_register_fundamental (m_tid,
                                   "CrankSessionElement",
                                   &tinfo,
                                   &ftinfo,
                                   G_TYPE_FLAG_ABSTRACT |
                                   G_TYPE_FLAG_VALUE_ABSTRACT);

      g_type_add_instance_private (m_tid, sizeof (CrankSessionElementPrivate));

      g_once_init_leave (&type_id, m_tid);
    }

  return type_id;
}



//////// Type Functions ////////////////////////////////////////////////////////


//////// Public functions //////////////////////////////////////////////////////

/**
 * crank_session_element_ref:
 * @inst: (type CrankSessionElement) (transfer none): A CrankSessionElement.
 *
 * Increases reference count of @inst.
 *
 * Returns: (type CrankSessionElement) (transfer full): @inst with increased refc.
 */
gpointer crank_session_element_ref (gpointer inst)
{
  CrankSessionElement *self = (CrankSessionElement*)inst;

  g_atomic_int_inc (& self->_refc);
  return self;
}

/**
 * crank_session_element_unref:
 * @inst: (type CrankSessionElement) (transfer full): A CrankSessionElement.
 *
 * Decreases reference count of @inst.
 */
void crank_session_element_unref (gpointer inst)
{
  CrankSessionElement *self = (CrankSessionElement*)inst;

  if (g_atomic_int_dec_and_test (& self->_refc))
    {
      // do some!
    }
}
