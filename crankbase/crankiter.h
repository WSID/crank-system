#ifndef CRANKITER_H
#define CRANKITER_H

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
#error crankiter.h cannot be included directly.
#endif

#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankrange.h"

//////// Struct declaration ////////////////////////////////////////////////////
/**
 * CrankIterMemBool:
 * @range: Memory range to iterate.
 * @ptr: Current Iteration position.
 *
 * Iterator for memory range (for example, plain #gboolean arrays.)
 */
typedef struct _CrankIterMemBool {
  CrankRanPtr range;
  gboolean *ptr;
} CrankIterMemBool;

/**
 * CrankIterMemUint:
 * @range: Memory range to iterate.
 * @ptr: Current Iteration position.
 *
 * Iterator for memory range (for example, plain #guint arrays.)
 */
typedef struct _CrankIterMemUint {
  CrankRanPtr range;
  guint *ptr;
} CrankIterMemUint;

/**
 * CrankIterMemInt:
 * @range: Memory range to iterate.
 * @ptr: Current Iteration position.
 *
 * Iterator for memory range (for example, plain #gint arrays.)
 */
typedef struct _CrankIterMemInt {
  CrankRanPtr range;
  gint *ptr;
} CrankIterMemInt;

/**
 * CrankIterMemFloat:
 * @range: Memory range to iterate.
 * @ptr: Current Iteration position.
 *
 * Iterator for memory range (for example, plain #gfloat arrays.)
 */
typedef struct _CrankIterMemFloat {
  CrankRanPtr range;
  gfloat *ptr;
} CrankIterMemFloat;

/**
 * CrankIterMemPtr:
 * @range: Memory range to iterate.
 * @ptr: Current Iteration position.
 *
 * Iterator for memory range for pointers.
 */
typedef struct _CrankIterMemPtr {
  CrankRanPtr range;
  gpointer *ptr;
} CrankIterMemPtr;

/**
 * CrankIterMemStruct:
 * @range: Memory range to iterate.
 * @ptr: Current Iteration position.
 * @size: Size of structure.
 *
 * Iterator for memory range for structures.
 */
typedef struct _CrankIterMemStruct {
  CrankRanPtr range;
  gpointer ptr;
  gsize size;
} CrankIterMemStruct;



//////// Boolean Memory Iterator ///////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void     crank_iter_mem_bool_init (CrankIterMemBool *iter,
                                   gboolean         *from,
                                   gboolean         *to);

void     crank_iter_mem_bool_init_with_count (CrankIterMemBool *iter,
                                              gboolean         *from,
                                              guint             count);

void     crank_iter_mem_bool_init_with_range (CrankIterMemBool *iter,
                                              CrankRanPtr      *range);

//////// Iteration /////////////////////////////////////////////////////////////

gboolean crank_iter_mem_bool_is_valid (CrankIterMemBool *iter);

gboolean crank_iter_mem_bool_next (CrankIterMemBool *iter);

gboolean crank_iter_mem_bool_get (CrankIterMemBool *iter);


gboolean crank_iter_mem_bool_foreach (CrankIterMemBool *iter,
                                      CrankBoolBoolFunc func,
                                      gpointer          userdata);



//////// Uint Memory Iterator //////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void     crank_iter_mem_uint_init (CrankIterMemUint *iter,
                                   guint            *from,
                                   guint            *to);

void     crank_iter_mem_uint_init_with_count (CrankIterMemUint *iter,
                                              guint            *from,
                                              guint             count);

void     crank_iter_mem_uint_init_with_range (CrankIterMemUint *iter,
                                              CrankRanPtr      *range);

//////// Iteration /////////////////////////////////////////////////////////////

gboolean crank_iter_mem_uint_is_valid (CrankIterMemUint *iter);

gboolean crank_iter_mem_uint_next (CrankIterMemUint *iter);

guint    crank_iter_mem_uint_get (CrankIterMemUint *iter);


gboolean crank_iter_mem_uint_foreach (CrankIterMemUint *iter,
                                      CrankBoolUintFunc func,
                                      gpointer          userdata);



//////// Int Memory Iterator ///////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void     crank_iter_mem_int_init (CrankIterMemInt *iter,
                                  gint            *from,
                                  gint            *to);

void     crank_iter_mem_int_init_with_count (CrankIterMemInt *iter,
                                             gint            *from,
                                             guint            count);

void     crank_iter_mem_int_init_with_range (CrankIterMemInt *iter,
                                             CrankRanPtr     *range);

//////// Iteration /////////////////////////////////////////////////////////////

gboolean crank_iter_mem_int_is_valid (CrankIterMemInt *iter);

gboolean crank_iter_mem_int_next (CrankIterMemInt *iter);

gint     crank_iter_mem_int_get (CrankIterMemInt *iter);


gboolean crank_iter_mem_int_foreach (CrankIterMemInt *iter,
                                     CrankBoolIntFunc func,
                                     gpointer         userdata);



//////// Float Memory Iterator ///////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void     crank_iter_mem_float_init (CrankIterMemFloat *iter,
                                    gfloat            *from,
                                    gfloat            *to);

void     crank_iter_mem_float_init_with_count (CrankIterMemFloat *iter,
                                               gfloat            *from,
                                               guint              count);

void     crank_iter_mem_float_init_with_range (CrankIterMemFloat *iter,
                                               CrankRanPtr       *range);

//////// Iteration /////////////////////////////////////////////////////////////

gboolean crank_iter_mem_float_is_valid (CrankIterMemFloat *iter);

gboolean crank_iter_mem_float_next (CrankIterMemFloat *iter);

gfloat   crank_iter_mem_float_get (CrankIterMemFloat *iter);


gboolean crank_iter_mem_float_foreach (CrankIterMemFloat *iter,
                                       CrankBoolFloatFunc func,
                                       gpointer           userdata);



//////// Pointer Memory Iterator ///////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void     crank_iter_mem_ptr_init (CrankIterMemPtr *iter,
                                  gpointer        *from,
                                  gpointer        *to);

void     crank_iter_mem_ptr_init_with_count (CrankIterMemPtr *iter,
                                             gpointer        *from,
                                             guint            count);

void     crank_iter_mem_ptr_init_with_range (CrankIterMemPtr *iter,
                                             CrankRanPtr     *range);

//////// Iteration /////////////////////////////////////////////////////////////

gboolean crank_iter_mem_ptr_is_valid (CrankIterMemPtr *iter);

gboolean crank_iter_mem_ptr_next (CrankIterMemPtr *iter);

gpointer crank_iter_mem_ptr_get (CrankIterMemPtr *iter);


gboolean crank_iter_mem_ptr_foreach (CrankIterMemPtr *iter,
                                     CrankBoolPtrFunc func,
                                     gpointer         userdata);



//////// Pointer Memory Iterator ///////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void     crank_iter_mem_struct_init (CrankIterMemStruct *iter,
                                     gpointer            from,
                                     gpointer            to,
                                     gsize               size);

void     crank_iter_mem_struct_init_with_count (CrankIterMemStruct *iter,
                                                gpointer            from,
                                                guint               count,
                                                gsize               size);

void     crank_iter_mem_struct_init_with_range (CrankIterMemStruct *iter,
                                                CrankRanPtr        *range,
                                                gsize               size);

//////// Iteration /////////////////////////////////////////////////////////////

gboolean crank_iter_mem_struct_is_valid (CrankIterMemStruct *iter);

gboolean crank_iter_mem_struct_next (CrankIterMemStruct *iter);

gpointer crank_iter_mem_struct_get (CrankIterMemStruct *iter);


gboolean crank_iter_mem_struct_foreach (CrankIterMemStruct *iter,
                                        CrankBoolPtrFunc    func,
                                        gpointer            userdata);

//////// Typed initialization //////////////////////////////////////////////////
/**
 * crank_iter_mem_struct_init_typed:
 * @iter: A #CrankIterMemStruct.
 * @G: Type of structure/chunk. It should be known at time of use.
 * @from: starting point.
 * @to: ending point.
 *
 * Initialize a iterator with typename.
 */
#define crank_iter_mem_struct_init_typed(iter, G, from, to) \
  G_STMT_START {          \
    G *nf = from;      \
    G *nt = to;         \
    crank_iter_mem_struct_init(iter,nf,nt,sizeof(G)); \
  } G_STMT_END

/**
 * crank_iter_mem_struct_init_with_count_typed:
 * @iter: A #CrankIterMemStruct.
 * @G: Type of structure/chunk. It should be known at time of use.
 * @from: starting point.
 * @count: number of structure/chunks.
 *
 * Initialize a iterator with count and typename.
 */
#define crank_iter_mem_struct_init_with_count_typed(iter, G, from, count)   \
  G_STMT_START {          \
    G *nf = from;      \
    crank_iter_mem_struct_init_with_count(iter,nf,count,sizeof(G)); \
  } G_STMT_END

/**
 * crank_iter_mem_struct_init_with_range_typed:
 * @iter: A #CrankIterMemStruct.
 * @G: Type of structure/chunk. It should be known at time of use.
 * @range: A Memory range to iterate.
 *
 * Initialize a iterator with range and typename.
 */
#define crank_iter_mem_struct_init_with_range_typed(iter, G, range) \
  crank_iter_mem_struct_init_with_range (iter,range,sizeof(G)

#endif