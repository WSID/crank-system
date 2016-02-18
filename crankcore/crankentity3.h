#ifndef CRANKENTITY3_H
#define CRANKENTITY3_H

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
#error crankentity3.h cannot included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"
#include "cranksessionmoduleplaced.h"

#include "crankplace.h"
#include "crankentity.h"

G_BEGIN_DECLS
//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_ENTITY3 (crank_entity3_get_type())
G_DECLARE_FINAL_TYPE (CrankEntity3,
                      crank_entity3,
                      CRANK, ENTITY3,
                      CrankEntity)

/**
 * CrankEntity3:
 * @position: Position of entity.
 *
 * Represents an entity for 3D space.
 */

struct _CrankEntity3
{
  /*< private >*/
  CrankEntity _parent;

  /*< public >*/
  CrankTrans3 position;
};



//////// Constructors //////////////////////////////////////////////////////////

CrankEntity3     *crank_entity3_new (CrankSessionModulePlaced *module);






//////// Public functions //////////////////////////////////////////////////////

void    crank_entity3_get_position (CrankEntity3 *entity,
                                    CrankTrans3  *position);

void    crank_entity3_set_position (CrankEntity3      *entity,
                                    const CrankTrans3 *position);


G_END_DECLS

#endif
