#ifndef CRANKLIGHTABLE_H
#define CRANKLIGHTABLE_H

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
#error cranklightable.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>

#include <cogl/cogl2-experimental.h>

#include "crankshape.h"

#include "crankprojection.h"

G_BEGIN_DECLS

///////// Type Definitions /////////////////////////////////////////////////////

G_DECLARE_DERIVABLE_TYPE (CrankLightable,
                          crank_lightable,
                          CRANK, LIGHTABLE,
                          GObject)

struct _CrankLightableClass
{
  GObjectClass _parent;

  gfloat  (*get_visible_radius)  (CrankLightable *lightable);

  void    (*render)              (CrankLightable  *lightable,
                                  CrankTrans3     *position,
                                  CrankProjection *projection,
                                  CoglTexture     *tex_geom,
                                  CoglTexture     *tex_color,
                                  CoglTexture     *tex_mater,
                                  const gfloat     lscale,
                                  CoglFramebuffer *framebuffer);
};


//////// Public functions //////////////////////////////////////////////////////

gfloat  crank_lightable_get_visible_radius (CrankLightable *lightable);


void    crank_lightable_get_primary_color (CrankLightable *lightable,
                                           CrankVecFloat3 *color);

void    crank_lightable_set_primary_color (CrankLightable *lightable,
                                           CrankVecFloat3 *color);


void    crank_lightable_render (CrankLightable  *lightable,
                                CrankTrans3     *position,
                                CrankProjection *projection,
                                CoglTexture     *tex_geom,
                                CoglTexture     *tex_color,
                                CoglTexture     *tex_mater,
                                const gfloat     lscale,
                                CoglFramebuffer *framebuffer);

G_END_DECLS


#endif
