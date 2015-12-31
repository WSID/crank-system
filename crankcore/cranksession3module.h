#ifndef CRANKSESSION3MODULE_H
#define CRANKSESSION3MODULE_H

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
#error cranksession3module.h cannot be included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"
#include "cranksession3.h"

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SESSION3_MODULE (crank_session3_module_get_type())
G_DECLARE_DERIVABLE_TYPE (CrankSession3Module,
                          crank_session3_module,
                          CRANK, SESSION3_MODULE,
                          GObject)


/**
 * CrankSession3ModuleClass:
 * @session_init: Slot for crank_session3_module_session_init().
 * @tick: Slot for crank_session3_module_tick().
 *
 * Virtual function table for #CrankSession3Module.
 */
struct _CrankSession3ModuleClass {
  /*< private >*/
  GObjectClass parent;

  /*< public >*/
  void    (*session_init) (CrankSession3Module *module,
                           CrankSession3       *session,
                           GError             **error);

  void    (*tick) (CrankSession3Module *module);
};

//////// Virtual functions /////////////////////////////////////////////////////

void      crank_session3_module_session_init (CrankSession3Module  *module,
                                              CrankSession3        *session,
                                              GError              **error);


void      crank_session3_module_tick (CrankSession3Module *module);

gboolean       crank_session3_module_is_initialized (CrankSession3Module *module);

CrankSession3 *crank_session3_module_get_session (CrankSession3Module *module);




#endif
