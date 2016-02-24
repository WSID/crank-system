#ifndef CRANKSHADERHOOK_H
#define CRANKSHADERHOOK_H

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
#error crankcameracontent.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>





//////// Type Declarations /////////////////////////////////////////////////////

G_DECLARE_FINAL_TYPE (CrankShaderHook,
                      crank_shader_hook,
                      CRANK, SHADER_HOOK,
                      GObject)








//////// Public Functions //////////////////////////////////////////////////////

//////// Properties ////////////////////////////////////////////////////////////

const gchar*    crank_shader_hook_get_name (CrankShaderHook *hook);

const gchar*    crank_shader_hook_get_nick (CrankShaderHook *hook);

const gchar*    crank_shader_hook_get_blurb (CrankShaderHook *hook);


guint           crank_shader_hook_get_n_params (CrankShaderHook *hook);








//////// Parameters ////////////////////////////////////////////////////////////

guint           crank_shader_hook_add_param       (CrankShaderHook *hook,
                                                   GParamSpec      *param);

gboolean        crank_shader_hook_remove_param    (CrankShaderHook *hook,
                                                   GParamSpec      *param);

GParamSpec     *crank_shader_hook_get_param       (CrankShaderHook *hook,
                                                   const guint      index);

gint            crank_shader_hook_index_of_param  (CrankShaderHook *hook,
                                                   GParamSpec      *param);

GParamSpec    **crank_shader_hook_get_params      (CrankShaderHook *hook,
                                                   guint           *nparams);








//////// Generate //////////////////////////////////////////////////////////////

gchar         *crank_shader_hook_generate_signiture (CrankShaderHook *hook,
                                                     const gchar     *func_name)


#endif
