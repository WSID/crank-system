#ifndef CRANKCELLSPACE3_H
#define CRANKCELLSPACE3_H

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

#ifndef _CRANKBASE_INSIDE
#error crankcellspace3.h cannot be included directly: include crankbase.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankvecuint.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_CELL_SPACE3 (crank_cell_space3_get_type())
GType   crank_cell_space3_get_type (void);

typedef struct _CrankCellSpace3 CrankCellSpace3;


//////// Constructors //////////////////////////////////////////////////////////

CrankCellSpace3  *crank_cell_space3_new (void);

CrankCellSpace3  *crank_cell_space3_new_with_size  (const guint       width,
                                                    const guint       height,
                                                    const guint       depth);

CrankCellSpace3  *crank_cell_space3_new_with_sizev (const CrankVecUint3 *size);


CrankCellSpace3  *crank_cell_space3_ref            (CrankCellSpace3  *cs);

void              crank_cell_space3_unref          (CrankCellSpace3  *cs);



//////// Properties ////////////////////////////////////////////////////////////

guint             crank_cell_space3_get_width      (CrankCellSpace3  *cs);

void              crank_cell_space3_set_width      (CrankCellSpace3  *cs,
                                                    const guint       width);

guint             crank_cell_space3_get_height     (CrankCellSpace3  *cs);

void              crank_cell_space3_set_height     (CrankCellSpace3  *cs,
                                                    const guint       height);

guint             crank_cell_space3_get_depth      (CrankCellSpace3  *cs);

void              crank_cell_space3_set_depth      (CrankCellSpace3  *cs,
                                                    const guint       depth);

void              crank_cell_space3_get_size       (CrankCellSpace3  *cs,
                                                    CrankVecUint3    *size);

void              crank_cell_space3_set_size       (CrankCellSpace3     *cs,
                                                    const CrankVecUint3 *size);



guint             crank_cell_space3_get_reserved_width (CrankCellSpace3 *cs);

void              crank_cell_space3_set_reserved_width (CrankCellSpace3 *cs,
                                                        const guint      width);

guint             crank_cell_space3_get_reserved_height (CrankCellSpace3 *cs);

void              crank_cell_space3_set_reserved_height (CrankCellSpace3 *cs,
                                                         const guint      height);

guint             crank_cell_space3_get_reserved_depth (CrankCellSpace3 *cs);

void              crank_cell_space3_set_reserved_depth (CrankCellSpace3 *cs,
                                                        const guint      depth);

void              crank_cell_space3_get_reserved_size (CrankCellSpace3 *cs,
                                                       CrankVecUint3   *size);

void              crank_cell_space3_set_reserved_size (CrankCellSpace3     *cs,
                                                       const CrankVecUint3 *size);


//////// Data access ///////////////////////////////////////////////////////////

void              crank_cell_space3_get            (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    GValue                *value);

void              crank_cell_space3_set            (CrankCellSpace3  *cs,
                                                    const guint       wi,
                                                    const guint       hi,
                                                    const guint       di,
                                                    const GValue     *value);

GValue           *crank_cell_space3_dup            (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di);

const GValue     *crank_cell_space3_peek           (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di);

gboolean          crank_cell_space3_unset          (CrankCellSpace3  *cs,
                                                    const guint       wi,
                                                    const guint       hi,
                                                    const guint       di);

gboolean          crank_cell_space3_is_unset       (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di);

GType             crank_cell_space3_type_of        (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di);



void              crank_cell_space3_unset_all      (CrankCellSpace3  *cs);



//////// Typed data access /////////////////////////////////////////////////////

gboolean          crank_cell_space3_get_boolean    (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const gboolean         def);

void              crank_cell_space3_set_boolean    (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const gboolean         value);


guint             crank_cell_space3_get_uint       (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const guint            def);

void              crank_cell_space3_set_uint       (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const guint            value);


gint              crank_cell_space3_get_int        (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const gint             def);

void              crank_cell_space3_set_int        (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const gint             value);


gfloat            crank_cell_space3_get_float      (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const gfloat           def);

void              crank_cell_space3_set_float      (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const gfloat           value);


gpointer          crank_cell_space3_get_pointer    (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    GType                 *type);

void              crank_cell_space3_set_pointer    (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const GType            type,
                                                    const gpointer         value);


gpointer          crank_cell_space3_get_boxed      (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    GType                 *type);

void              crank_cell_space3_set_boxed      (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const GType            type,
                                                    const gpointer         value);


gpointer          crank_cell_space3_dup_boxed      (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    GType                 *type);

void              crank_cell_space3_take_boxed     (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    const GType            type,
                                                    gpointer               value);

gpointer          crank_cell_space3_get_object     (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di);

void              crank_cell_space3_set_object     (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    gpointer               value);

gpointer          crank_cell_space3_dup_object     (const CrankCellSpace3 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di);

void              crank_cell_space3_take_object    (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di,
                                                    gpointer               value);


gpointer          crank_cell_space3_peek_pointer   (CrankCellSpace3       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            di);




G_END_DECLS

#endif
