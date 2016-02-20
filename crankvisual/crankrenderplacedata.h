#ifndef CRANKRENDERPLACEDATA_H
#define CRANKRENDERPLACEDATA_H

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

/* This header defines private types. */

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"
#include "crankshape.h"
#include "crankcore.h"

#include "crankprojection.h"
#include "crankvisible.h"

#ifndef _CRANKVISUAL_INSIDE
#error crankrenderplacedata.h cannot be included directly: include crankvisual.h
#endif






//////// Properties of private types ///////////////////////////////////////////

enum {
  PROP_PRIV_0,
  PROP_PRIV_VISIBLE_TYPES,

  PROP_PRIV_COUNTS
};

static GParamSpec *pspecs_priv[PROP_PRIV_COUNTS] = {NULL};






//////// Private Type Declaration //////////////////////////////////////////////

#define CRANK_TYPE_RENDER_PLACE_DATA (crank_render_place_data_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderPlaceData,
                      crank_render_place_data,
                      CRANK, RENDER_PLACE_DATA,
                      CrankCompositable1N);






//////// Internal Functions ////////////////////////////////////////////////////

G_GNUC_INTERNAL
void  crank_render_place_data_add_entity        (CrankRenderPlaceData *pdata,
                                                 CrankEntity          *entity,
                                                 CrankVisible         *visible,
                                                 const guint           tindex);

G_GNUC_INTERNAL
void  crank_render_place_data_remove_entity     (CrankRenderPlaceData *pdata,
                                                 CrankEntity          *entity,
                                                 CrankVisible         *visible,
                                                 const guint           tindex);




//////// Public functions //////////////////////////////////////////////////////

GPtrArray   *crank_render_place_data_get_culled_array (CrankRenderPlaceData *pdata,
                                                       GPtrArray            *entities,
                                                       const CrankPlane3    *culls,
                                                       const guint           nculls,
                                                       const guint           tindex);



#endif
