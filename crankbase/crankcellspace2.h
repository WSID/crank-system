#ifndef CRANKCELLSPACE2_H
#define CRANKCELLSPACE2_H

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
#error crankcellspace2.h cannot be included directly: include crankbase.h
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankvecuint.h"

G_BEGIN_DECLS

//////// Type Declarations /////////////////////////////////////////////////////

#define CRANK_TYPE_CELL_SPACE2 (crank_cell_space2_get_type())
GType   crank_cell_space2_get_type (void);

typedef struct _CrankCellSpace2 CrankCellSpace2;


//////// Constructors //////////////////////////////////////////////////////////

CrankCellSpace2  *crank_cell_space2_new (void);

CrankCellSpace2  *crank_cell_space2_new_with_size  (const guint       width,
                                                    const guint       height);

CrankCellSpace2  *crank_cell_space2_new_with_sizev (const CrankVecUint2 *size);


CrankCellSpace2  *crank_cell_space2_ref            (CrankCellSpace2  *cs);

void              crank_cell_space2_unref          (CrankCellSpace2  *cs);



//////// Properties ////////////////////////////////////////////////////////////

guint             crank_cell_space2_get_width      (CrankCellSpace2  *cs);

void              crank_cell_space2_set_width      (CrankCellSpace2  *cs,
                                                    const guint       width);

guint             crank_cell_space2_get_height     (CrankCellSpace2  *cs);

void              crank_cell_space2_set_height     (CrankCellSpace2  *cs,
                                                    const guint       height);

void              crank_cell_space2_get_size       (CrankCellSpace2  *cs,
                                                    CrankVecUint2    *size);

void              crank_cell_space2_set_size       (CrankCellSpace2     *cs,
                                                    const CrankVecUint2 *size);



guint             crank_cell_space2_get_reserved_width (CrankCellSpace2 *cs);

void              crank_cell_space2_set_reserved_width (CrankCellSpace2 *cs,
                                                        const guint      width);

guint             crank_cell_space2_get_reserved_height (CrankCellSpace2 *cs);

void              crank_cell_space2_set_reserved_height (CrankCellSpace2 *cs,
                                                         const guint      height);

void              crank_cell_space2_get_reserved_size (CrankCellSpace2 *cs,
                                                       CrankVecUint2   *size);

void              crank_cell_space2_set_reserved_size (CrankCellSpace2     *cs,
                                                       const CrankVecUint2 *size);


//////// Data access ///////////////////////////////////////////////////////////

void              crank_cell_space2_get            (const CrankCellSpace2 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    GValue                *value);

void              crank_cell_space2_set            (CrankCellSpace2  *cs,
                                                    const guint       wi,
                                                    const guint       hi,
                                                    const GValue     *value);

GValue           *crank_cell_space2_dup            (const CrankCellSpace2 *cs,
                                                    const guint            wi,
                                                    const guint            hi);

const GValue     *crank_cell_space2_peek           (const CrankCellSpace2 *cs,
                                                    const guint            wi,
                                                    const guint            hi);

gboolean          crank_cell_space2_unset          (CrankCellSpace2  *cs,
                                                    const guint       wi,
                                                    const guint       hi);

gboolean          crank_cell_space2_is_unset       (const CrankCellSpace2 *cs,
                                                    const guint            wi,
                                                    const guint            hi);

GType             crank_cell_space2_type_of        (const CrankCellSpace2 *cs,
                                                    const guint            wi,
                                                    const guint            hi);



void              crank_cell_space2_unset_all      (CrankCellSpace2  *cs);



//////// Typed data access /////////////////////////////////////////////////////

gboolean          crank_cell_space2_get_boolean    (const CrankCellSpace2 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const gboolean         def);

void              crank_cell_space2_set_boolean    (CrankCellSpace2       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const gboolean         value);


guint             crank_cell_space2_get_uint       (const CrankCellSpace2 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            def);

void              crank_cell_space2_set_uint       (CrankCellSpace2       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const guint            value);


gint              crank_cell_space2_get_int        (const CrankCellSpace2 *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const gint             def);

void              crank_cell_space2_set_int        (CrankCellSpace2       *cs,
                                                    const guint            wi,
                                                    const guint            hi,
                                                    const gint             value);




G_END_DECLS

#endif
