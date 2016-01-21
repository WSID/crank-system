#ifndef CRANKPLACEENTITY_H
#define CRANKPLACEENTITY_H

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
#error crankplaceentity.h cannot included directly: include crankcore.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"

#include "cranksession.h"
#include "cranksessionmodule.h"
#include "cranksessionmoduleplaced.h"


//////// Type Declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_PLACE_BASE (crank_place_base_get_type())
GType crank_place_base_get_type (void);

#define CRANK_TYPE_ENTITY_BASE (crank_entity_base_get_type())
GType crank_entity_base_get_type (void);

typedef struct _CrankPlaceBase CrankPlaceBase;
typedef struct _CrankEntityBase CrankEntityBase;

typedef struct _CrankPlace3 CrankPlace3;
typedef struct _CrankEntity3 CrankEntity3;

/**
 * CrankPlaceBase:
 * @object: Object that holds this place.
 *
 * A Pointer type.
 */
struct _CrankPlaceBase
{
  GObject *object;
};

/**
 * CrankEntityBase:
 * @object: Object that holds this entity.
 *
 * A Pointer type.
 */
struct _CrankEntityBase
{
  GObject *object;
};


/**
 * CrankPlace3:
 * @object: Object that holds this place.
 * @boundary: Boundary of place.
 *
 * Place representation for 3D space.
 */
struct _CrankPlace3
{
  GObject   *object;
  CrankBox3 *boundary;
};

/**
 * CrankEntity3:
 * @object: Object that holds this place.
 * @position: Position of the entity.
 *
 * Entity represention for 3D space.
 */
struct _CrankEntity3
{
  GObject     *object;
  CrankTrans3  position;
};


//////// Allocation ////////////////////////////////////////////////////////////


CrankPlaceBase*  crank_place_base_new (CrankSessionModulePlaced *module);

CrankEntityBase* crank_entity_base_new (CrankSessionModulePlaced *module);


CrankPlaceBase*  crank_place_base_ref (CrankPlaceBase* place);

void      crank_place_base_unref (CrankPlaceBase* place);


CrankEntityBase* crank_entity_base_ref (CrankEntityBase* entity);

void      crank_entity_base_unref (CrankEntityBase* entity);



//////// Public functions //////////////////////////////////////////////////////

CrankSessionModulePlaced* crank_place_base_get_module (CrankPlaceBase* place);

CrankSessionModulePlaced* crank_entity_base_get_module (CrankEntityBase* entity);


guint           crank_place_base_get_n_entities (CrankPlaceBase *place);


CrankPlaceBase *crank_entity_base_get_place (CrankEntityBase *entity);


//////// Place Functions ///////////////////////////////////////////////////////

void    crank_place_base_add_entity   (CrankPlaceBase  *place,
                                       CrankEntityBase *entity);

void    crank_place_base_remove_entity(CrankPlaceBase  *place,
                                       CrankEntityBase *entity);





G_DEFINE_AUTOPTR_CLEANUP_FUNC (CrankPlaceBase, crank_place_base_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CrankEntityBase, crank_entity_base_unref)


#endif
