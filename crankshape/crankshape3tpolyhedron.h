#ifndef CRANKSHAPE3TPOLYHEDRON_H
#define CRANKSHAPE3TPOLYHEDRON_H

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
#error crankshape3tpolyhedron.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>
#include "crankbase.h"

#include "crankshapemisc.h"
#include "crankpolystruct3.h"

#include "crankshape3.h"
#include "crankshape3finite.h"
#include "crankshape3vertexed.h"
#include "crankshape3polyhedron.h"

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE3_TPOLYHEDRON crank_shape3_tpolyhedron_get_type ()

G_DECLARE_DERIVABLE_TYPE (CrankShape3TPolyhedron,
                          crank_shape3_tpolyhedron,
                          CRANK, SHAPE3_TPOLYHEDRON,
                          CrankShape3Polyhedron)


struct _CrankShape3TPolyhedronClass {
  CrankShape3PolyhedronClass  _parent;
};



//////// Class properties //////////////////////////////////////////////////////

CrankPolyStruct3*   crank_shape3_tpolyhedron_class_get_template (CrankShape3TPolyhedronClass *c);


void                crank_shape3_tpolyhedron_class_set_template (CrankShape3TPolyhedronClass *c,
                                                                 CrankPolyStruct3            *pstruct);

#endif
