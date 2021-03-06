#ifndef CRANKRENDERMODULE_H
#define CRANKRENDERMODULE_H

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

#ifndef _CRANKVISUAL_INSIDE
#error crankrendermodule.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankrenderable.h"
#include "cranklightable.h"

#include "crankfilm.h"
#include "crankcamera.h"

#include "crankrenderprocess.h"

//////// Type Definition ///////////////////////////////////////////////////////

#define CRANK_TYPE_RENDER_MODULE (crank_render_module_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderModule,
                      crank_render_module,
                      CRANK, RENDER_MODULE,
                      CrankCompositable)

/**
 * CrankRenderModule:
 *
 * Instance Structure.
 */


//////// Constructors //////////////////////////////////////////////////////////

CrankRenderModule *crank_render_module_new (CoglContext *cogl_context);






//////// Property getter / setters /////////////////////////////////////////////

guint   crank_render_module_get_n_camera (CrankRenderModule *module);


CrankRenderProcess* crank_render_module_get_process (CrankRenderModule *module);

void                crank_render_module_set_process (CrankRenderModule  *module,
                                                     CrankRenderProcess *process);



guint     crank_render_module_get_n_visible_types (CrankRenderModule *module);




//////// Public functions //////////////////////////////////////////////////////

void    crank_render_module_add_camera (CrankRenderModule *module,
                                        CrankCamera       *camera);

void    crank_render_module_remove_camera (CrankRenderModule *module,
                                           CrankCamera       *camera);



gint    crank_render_module_add_visible_type (CrankRenderModule *module,
                                              GType              type);

GType   crank_render_module_get_visible_type (CrankRenderModule *module,
                                              guint              index);

gint    crank_render_module_index_of_visible_type (CrankRenderModule *module,
                                                   GType              type);



#endif
