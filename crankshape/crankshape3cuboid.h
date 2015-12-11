#ifndef CRANKSHAPE3CUBOID_H
#define CRANKSHAPE3CUBOID_H

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
#error crankshape3cubiod.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"
#include "crankshapemisc.h"
#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polyhedron.h"
#include "crankshape3tpolyhedron.h"

//////// Type Definition ///////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE3_CUBOID crank_shape3_cuboid_get_type()
G_DECLARE_FINAL_TYPE (CrankShape3Cuboid,
                      crank_shape3_cuboid,
                      CRANK, SHAPE3_CUBOID,
                      CrankShape3TPolyhedron)


//////// Constructor ///////////////////////////////////////////////////////////

CrankShape3Cuboid*
crank_shape3_cuboid_new (CrankVecFloat3 *size);

CrankShape3Cuboid*
crank_shape3_cuboid_new_with_whd (const gfloat width,
                                  const gfloat height,
                                  const gfloat depth);

CrankShape3Cuboid*
crank_shape3_cuboid_new_cube (const gfloat size);


//////// Properties ////////////////////////////////////////////////////////////

void    crank_shape3_cuboid_get_size (CrankShape3Cuboid *self,
                                      CrankVecFloat3    *size);

void    crank_shape3_cuboid_set_size (CrankShape3Cuboid *self,
                                      CrankVecFloat3    *size);

gfloat  crank_shape3_cuboid_get_width (CrankShape3Cuboid *self);

void    crank_shape3_cuboid_set_width (CrankShape3Cuboid *self,
                                       const gfloat       width);

gfloat  crank_shape3_cuboid_get_height (CrankShape3Cuboid *self);

void    crank_shape3_cuboid_set_height (CrankShape3Cuboid *self,
                                        const gfloat       height);

gfloat  crank_shape3_cuboid_get_depth (CrankShape3Cuboid *self);

void    crank_shape3_cuboid_set_depth (CrankShape3Cuboid *self,
                                       const gfloat       depth);

#endif
