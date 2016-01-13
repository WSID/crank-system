#ifndef CRANKSESSIONELEMENT_H
#define CRANKSESSIONELEMENT_H

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

#ifndef CRANKCORE_INSIDE
#error cranksessionelement.h cannot be included directly: include crankcore.h
#endif


#include <glib.h>
#include <glib-object.h>

//////// Type Definition ///////////////////////////////////////////////////////

typedef struct _CrankSessionElement       CrankSessionElement;
typedef struct _CrankSessionElementClass  CrankSessionElementClass;

/**
 * CrankSessionElement: (ref-func crank_session_element_ref) (unref-func crank_session_element_unref)
 *
 * Structure for all CrankSessionElement type.
 */
/**
 * CrankSessionElementClass:
 */

GType crank_session_element_get_type (void);

//////// Type Functions ////////////////////////////////////////////////////////

/**
 * CRANK_TYPE_SESSION_ELEMENT:
 *
 * Fundamental type for #CrankSessionElement.
 */
#define CRANK_TYPE_SESSION_ELEMENT (crank_session_element_get_type())


static inline CrankSessionElement*      CRANK_SESSION_ELEMENT (gpointer instance);
static inline gboolean                  CRANK_IS_SESSION_ELEMENT (gpointer instance);
static inline CrankSessionElementClass* CRANK_SESSION_ELEMENT_GET_CLASS (gpointer instance);
static inline CrankSessionElementClass* CRANK_SESSION_ELEMENT_CLASS (gpointer c);
static inline gboolean                  CRANK_IS_SESSION_ELEMENT_CLASS (gpointer c);



//////// Type Function definitions /////////////////////////////////////////////

/**
 * CRANK_SESSION_ELEMENT: (skip)
 * @instance: #CrankSessionElement instance.
 *
 * Checked casting for CrankSessionElement types.
 *
 * Returns: (transfer none): @instance.
 */
static inline CrankSessionElement*
CRANK_SESSION_ELEMENT (gpointer instance)
{
  return G_TYPE_CHECK_INSTANCE_CAST (instance,
                                     CRANK_TYPE_SESSION_ELEMENT,
                                     CrankSessionElement);
}

/**
 * CRANK_IS_SESSION_ELEMENT: (skip)
 * @instance: A #GTypeInstance instance.
 *
 * Checks whether @instance is #CrankSessionElement or not.
 *
 * Returns: Whether @instance is #CrankSessionElement.
 */
static inline gboolean
CRANK_IS_SESSION_ELEMENT (gpointer instance)
{
  return G_TYPE_CHECK_INSTANCE_FUNDAMENTAL_TYPE (instance,
                                                 CRANK_TYPE_SESSION_ELEMENT);
}

/**
 * CRANK_SESSION_ELEMENT_GET_CLASS: (skip)
 * @instance: A #GTypeInstance instance.
 *
 * Retrieves class structure from @instance.
 *
 * Returns: (transfer none): Class structure of @instance.
 */
static inline CrankSessionElementClass*
CRANK_SESSION_ELEMENT_GET_CLASS (gpointer instance)
{
  return G_TYPE_INSTANCE_GET_CLASS (instance,
                                    CRANK_TYPE_SESSION_ELEMENT,
                                    CrankSessionElementClass);
}

/**
 * CRANK_SESSION_ELEMENT_CLASS: (skip)
 * @c: Class structure.
 *
 * Checked casting for CrankSessionElementClass structures.
 *
 * Returns: (transfer none): @c
 */
static inline CrankSessionElementClass*
CRANK_SESSION_ELEMENT_CLASS (gpointer c)
{
  return G_TYPE_CHECK_CLASS_CAST (c,
                                  CRANK_TYPE_SESSION_ELEMENT,
                                  CrankSessionElementClass);
}

/**
 * CRANK_IS_SESSION_ELEMENT_CLASS: (skip)
 * @c: Class structure.
 *
 * Checks whether @c is #CrankSessionElementClass or not.
 *
 * Returns: Whether @c is #CrankSessionElementClass.
 */
static inline gboolean
CRANK_IS_SESSION_ELEMENT_CLASS (gpointer c)
{
  return G_TYPE_CHECK_CLASS_TYPE (c,
                                  CRANK_TYPE_SESSION_ELEMENT);
}


//////// Public functions //////////////////////////////////////////////////////

gpointer crank_session_element_ref (gpointer inst);

void     crank_session_element_unref (gpointer inst);


#endif
