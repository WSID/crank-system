#ifndef CRANKSESSIONMODULETICK_H
#define CRANKSESSIONMODULETICK_H

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
#error cranksessionmodule.h cannot be included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"
#include "cranksessionmodule.h"


//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SESSION_MODULE_TICK (crank_session_module_tick_get_type())
G_DECLARE_FINAL_TYPE (CrankSessionModuleTick,
                      crank_session_module_tick,
                      CRANK, SESSION_MODULE_TICK,
                      CrankSessionModule)


//////// Properties ////////////////////////////////////////////////////////////

GMainContext  *crank_session_module_tick_get_tick_context (CrankSessionModuleTick *module);

void           crank_session_module_tick_set_tick_context (CrankSessionModuleTick *module,
                                                           GMainContext           *tick_context);


guint crank_session_module_tick_get_tick_interval (CrankSessionModuleTick *module);

void  crank_session_module_tick_set_tick_interval (CrankSessionModuleTick *module,
                                                   const guint             tick_interval);



void  crank_session_module_tick_tick (CrankSessionModuleTick *module);


#endif
