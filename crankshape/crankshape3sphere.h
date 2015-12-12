#ifndef CRANKSHAPE3SPHERE_H
#define CRANKSHAPE3SPHERE_H

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
#error crankshape3sphere.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3iround.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE3_SPHERE crank_shape3_sphere_get_type ()

G_DECLARE_FINAL_TYPE (CrankShape3Sphere,
                      crank_shape3_sphere,
                      CRANK, SHAPE3_SPHERE,
                      CrankShape3Finite)


//////// Constructors //////////////////////////////////////////////////////////

CrankShape3Sphere      *crank_shape3_sphere_new (const gfloat radius);


//////// Property getter/setters ///////////////////////////////////////////////

gfloat                  crank_shape3_sphere_get_radius (CrankShape3Sphere *sphere);

void                    crank_shape3_sphere_set_radius (CrankShape3Sphere *sphere,
                                                        const gfloat       radius);


G_END_DECLS

#endif
