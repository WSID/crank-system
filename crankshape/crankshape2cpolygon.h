#ifndef CRANKCPOLYGON_H
#define CRANKCPOLYGON_H

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
#error crankcpolygon.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankshape2.h"

G_BEGIN_DECLS
//////// Type declaration //////////////////////////////////////////////////////

#define CRANK_TYPE_SHAPE2_CPOLYGON crank_shape2_cpolygon_get_type ()

G_DECLARE_FINAL_TYPE (CrankShape2CPolygon,
                      crank_shape2_cpolygon,
                      CRANK, SHAPE2_CPOLYGON,
                      CrankShape2)



//////// Constructors //////////////////////////////////////////////////////////

CrankShape2CPolygon *crank_shape2_cpolygon_new (void);

CrankShape2CPolygon *crank_shape2_cpolygon_new_from_vertices (CrankVecFloat2 *vertices,
                                                              guint           nvertices);

//////// Vertices //////////////////////////////////////////////////////////////

void            crank_shape2_cpolygon_set_vertex (CrankShape2CPolygon *polygon,
                                                  guint                index,
                                                  CrankVecFloat2      *vertex);

void            crank_shape2_cpolygon_insert_vertex (CrankShape2CPolygon *polygon,
                                                     guint                index,
                                                     CrankVecFloat2      *vertex);

void            crank_shape2_cpolygon_append_vertex (CrankShape2CPolygon *polygon,
                                                     CrankVecFloat2      *vertex);

void            crank_shape2_cpolygon_remove_vertex (CrankShape2CPolygon *polygon,
                                                     guint                index);


G_END_DECLS

#endif 
