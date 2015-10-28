#ifndef CRANKROTATION_H
#define CRANKROTATION_H

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
#error crankrotation.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankbase.h"

G_BEGIN_DECLS

//////// Coversions between rotation representations ///////////////////////////

void            crank_rot_quat_float_to_mat_float3       (CrankQuatFloat *quat,
                                                          CrankMatFloat3 *mat);

void            crank_rot_quat_float_to_mat_float4       (CrankQuatFloat *quat,
                                                          CrankMatFloat4 *mat);

void            crank_rot_mat_float3_to_quat_float       (CrankMatFloat3 *mat,
                                                          CrankQuatFloat *quat);

void            crank_rot_mat_float4_to_quat_float       (CrankMatFloat4 *mat,
                                                          CrankQuatFloat *quat);

G_END_DECLS

#endif 