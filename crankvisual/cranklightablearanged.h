#ifndef CRANKLIGHTABLEARANGED_H
#define CRANKLIGHTABLEARANGED_H

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
#error cranklightablearanged.h cannot be included directly: include crankvisual.h
#endif

#include <glib.h>
#include <glib-object.h>

#include <cogl/cogl2-experimental.h>

#include "crankshape.h"

#include "crankprojection.h"
#include "crankvisible.h"
#include "cranklightable.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_LIGHTABLE_A_RANGED (crank_lightable_a_ranged_get_type ())
G_DECLARE_FINAL_TYPE (CrankLightableARanged,
                      crank_lightable_a_ranged,
                      CRANK, LIGHTABLE_A_RANGED,
                      CrankLightable)

/**
 * CrankLightableARanged:
 *
 * Represents Ambient light with limited range.
 */


//////// Constructor ///////////////////////////////////////////////////////////

CrankLightableARanged*
crank_lightable_a_ranged_new (CoglContext          *cogl_context,
                              const CrankVecFloat3 *primary_color,
                              const gfloat          radius,
                              const gfloat          intensity);


//////// Public functions //////////////////////////////////////////////////////

gfloat  crank_lightable_a_ranged_get_radius (CrankLightableARanged *lightable);

void    crank_lightable_a_ranged_set_radius (CrankLightableARanged *lightable,
                                             const gfloat          radius);

gfloat  crank_lightable_a_ranged_get_intensity (CrankLightableARanged *lightable);

void    crank_lightable_a_ranged_set_intensity (CrankLightableARanged *lightable,
                                                const gfloat           intensity);

G_END_DECLS

#endif
