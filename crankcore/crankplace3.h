#ifndef CRANKPLACE3_H
#define CRANKPLACE3_H

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
#error crankplace3.h cannot included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "cranksessionmoduleplaced.h"

#include "crankplace.h"
#include "crankentity.h"

G_BEGIN_DECLS
//////// Forward declarations //////////////////////////////////////////////////

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_PLACE3 (crank_place3_get_type())
G_DECLARE_FINAL_TYPE (CrankPlace3,
                      crank_place3,
                      CRANK, PLACE3,
                      CrankComposite)

/**
 * CrankPlace3:
 * @boundary: A Boundary.
 *
 * Represents a place for 3D space.
 */

struct _CrankPlace3
{
  /*< private >*/
  CrankPlace _parent;

  /*< public >*/
  CrankBox3   boundary;
};



//////// Constructors //////////////////////////////////////////////////////////

CrankPlace3*
crank_place3_new (CrankSessionModulePlaced *module);

CrankPlace3*
crank_place3_new_with_boundary (CrankSessionModulePlaced *module,
                                const CrankBox3          *boundary);


//////// Public functions //////////////////////////////////////////////////////

void    crank_place3_get_boundary (CrankPlace3 *place,
                                   CrankBox3   *boundary);

void    crank_place3_set_boundary (CrankPlace3     *place,
                                   const CrankBox3 *boundary);


G_END_DECLS

#endif
