#ifndef CRANKGJK_H
#define CRANKGJK_H

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

#ifndef _CRANKSHAPE_INSIDE
#error crankgjk.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

#include "crankbox.h"
#include "crankshape2.h"
#include "crankshape2finite.h"
#include "crankshape2polygon.h"

G_BEGIN_DECLS

gboolean        crank_gjk2     (CrankShape2Polygon *a,
                                CrankShape2Polygon *b,
                                CrankTrans2        *bpos);

gboolean        crank_gjk2_full (CrankShape2Polygon *a,
                                 CrankShape2Polygon *b,
                                 CrankTrans2        *bpos,
                                 CrankVecFloat2     *triangle);

gfloat          crank_epa2      (CrankShape2Polygon *a,
                                 CrankShape2Polygon *b,
                                 CrankTrans2        *bpos,
                                 CrankVecFloat2     *init_polys,
                                 const guint        ninit_polys,
                                 CrankVecFloat2     *segment,
                                 CrankVecFloat2     *normal);

G_END_DECLS

#endif
