#ifndef CRANKRENDERPDATA_H
#define CRANKRENDERPDATA_H

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

#include "crankrenderable.h"

#ifndef _CRANKVISUAL_INSIDE
#error crankrendermodule.h cannot be included directly: include crankvisual.h
#endif


//////// Properties of private types ///////////////////////////////////////////

enum {
  PROP_PRIV_0,
  PROP_PRIV_PLACE,
  PROP_PRIV_RENDERABLE_OFFSET,

  PROP_PRIV_COUNTS
};

static GParamSpec *pspecs_priv[PROP_PRIV_COUNTS] = {NULL};

//////// Private Type Declaration //////////////////////////////////////////////

#define CRANK_TYPE_RENDER_PDATA (crank_render_pdata_get_type())
G_DECLARE_FINAL_TYPE (CrankRenderPData,
                      crank_render_pdata,
                      CRANK, RENDER_PDATA,
                      GObject);

struct _CrankRenderPData
{
  GObject parent;

  CrankOctreeSet *entities;
};

//////// Private Type functions ////////////////////////////////////////////////

void crank_render_pdata_add_entity (CrankRenderPData *pdata,
                                           CrankEntityBase  *entity);

void crank_render_pdata_remove_entity (CrankRenderPData *pdata,
                                              CrankEntityBase  *entity);

//////// Private type vfuncs ///////////////////////////////////////////////////

void crank_render_pdata_constructed (GObject *object);

void crank_render_pdata_set_property (GObject      *object,
                                             guint         prop_id,
                                             const GValue *value,
                                             GParamSpec   *pspec);

void crank_render_pdata_dispose (GObject *object);

void crank_render_pdata_finalize (GObject *object);


//////// Private type callbacks ////////////////////////////////////////////////

CrankVecFloat3 *crank_render_pdata_get_pos (gpointer data,
                                                   gpointer userdata);

gfloat crank_render_pdata_get_rad (gpointer data,
                                          gpointer userdata);




#endif
