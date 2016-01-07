#ifndef CRANKMATERIAL_H
#define CRANKMATERIAL_H

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
#error crankmaterial.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <cogl/cogl2-experimental.h>

//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_MATERIAL (crank_material_get_type())
G_DECLARE_FINAL_TYPE (CrankMaterial,
                      crank_material,
                      CRANK, MATERIAL,
                      GObject)



//////// Public Functions //////////////////////////////////////////////////////

CrankMaterial *crank_material_new (CoglContext *cogl_context);


//////// Properties ////////////////////////////////////////////////////////////

CoglPipeline *crank_material_get_pipeline_geom (CrankMaterial *material);

CoglPipeline *crank_material_get_pipeline_color (CrankMaterial *material);

CoglPipeline *crank_material_get_pipeline_material (CrankMaterial *material);



CoglTexture *crank_material_get_texture_normal (CrankMaterial *material);

void         crank_material_set_texture_normal (CrankMaterial *material,
                                                CoglTexture   *texture);

CoglTexture *crank_material_get_texture_color (CrankMaterial *material);

void         crank_material_set_texture_color (CrankMaterial *material,
                                               CoglTexture   *texture);



#endif
