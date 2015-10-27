#ifndef CRANKRANGE_H
#define CRANKRANGE_H

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
#error crankrange.h cannot be included directly.
#endif

#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>

#include "crankcomplex.h"
#include "crankveccommon.h"

//////// Struct declaration ////////////////////////////////////////////////////

/**
 * CrankRanUint:
 * @start: Start of range.
 * @end: End of range.
 *
 * Represents range of unsigned int.
 */
typedef struct _CrankRanUint {
  guint start;
  guint end;
} CrankRanUint;

/**
 * CrankRanInt:
 * @start: Start of range.
 * @end: End of range.
 *
 * Represents range of signed int.
 */
typedef struct _CrankRanInt {
  gint start;
  guint end;
} CrankRanInt;

/**
 * CrankRanFloat:
 * @start: Start of range.
 * @end: End of range.
 *
 * Represents range of float.
 */
typedef struct _CrankRanFloat {
  gfloat start;
  gfloat end;
} CrankRanFloat;

/**
 * CrankRanPtr:
 * @start: Start of range.
 * @end: End of range.
 *
 * Represents range of two pointer.
 */
typedef struct _CrankRanPtr {
  gpointer start;
  gpointer end;
} CrankRanPtr;


//////// Type Macros ///////////////////////////////////////////////////////////

#define CRANK_TYPE_RAN_UINT     (crank_ran_uint_get_type ())
GType crank_ran_uint_get_type (void);

#define CRANK_TYPE_RAN_INT      (crank_ran_int_get_type ())
GType crank_ran_int_get_type (void);

#define CRANK_TYPE_RAN_FLOAT        (crank_ran_float_get_type ())
GType crank_ran_float_get_type (void);

#define CRANK_TYPE_RAN_PTR      (crank_ran_ptr_get_type ())
GType crank_ran_ptr_get_type (void);



/**
 * CRANK_RAN_UINT_DEFFORMAT:
 *
 * A default format which is used in crank_ran_uint_to_string()
 */
#define CRANK_RAN_UINT_DEFFORMAT    "[%u, %u)"

/**
 * CRANK_RAN_INT_DEFFORMAT:
 *
 * A default format which is used in crank_ran_int_to_string()
 */
#define CRANK_RAN_INT_DEFFORMAT     "[%d, %d)"

/**
 * CRANK_RAN_FLOAT_DEFFORMAT:
 *
 * A default format which is used in crank_ran_float_to_string()
 */
#define CRANK_RAN_FLOAT_DEFFORMAT   "[%g, %g)"

/**
 * CRANK_RAN_PTR_DEFFORMAT:
 *
 * A default format which is used in crank_ran_ptr_to_string()
 */
#define CRANK_RAN_PTR_DEFFORMAT     "[%p, %p)"

//////// Uint Ranges ///////////////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void           crank_ran_uint_init (CrankRanUint *ran,
                                    const guint   start,
                                    const guint   end);

void           crank_ran_uint_init_diff (CrankRanUint *ran,
                                         const guint   start,
                                         const guint   diff);

void           crank_ran_uint_init_unit (CrankRanUint *ran,
                                         const guint   start);


//////// Basic Functions ///////////////////////////////////////////////////////

void           crank_ran_uint_copy (CrankRanUint *ran,
                                    CrankRanUint *other);

CrankRanUint  *crank_ran_uint_dup (CrankRanUint *ran);

gboolean       crank_ran_uint_equal (gconstpointer a,
                                     gconstpointer b);

guint          crank_ran_uint_hash (gconstpointer a);

gchar         *crank_ran_uint_to_string (CrankRanUint *ran);

gchar         *crank_ran_uint_to_string_full (CrankRanUint *ran,
                                              const gchar  *format);


//////// Classification ////////////////////////////////////////////////////////

gboolean       crank_ran_uint_is_empty (CrankRanUint *ran);

gboolean       crank_ran_uint_is_unit (CrankRanUint *ran);


//////// Attributes ////////////////////////////////////////////////////////////

guint          crank_ran_uint_get_length (CrankRanUint *ran);


//////// Range function ////////////////////////////////////////////////////////

gboolean       crank_ran_uint_contains (CrankRanUint *ran,
                                        const guint   value);

guint          crank_ran_uint_get (CrankRanUint *ran,
                                   const gfloat  index);

gfloat         crank_ran_uint_index_of (CrankRanUint *ran,
                                        const guint   value);

guint          crank_ran_uint_clamp (CrankRanUint *ran,
                                     const guint   value);

//////// Range - Range operations //////////////////////////////////////////////

gboolean       crank_ran_uint_intersection (CrankRanUint *a,
                                            CrankRanUint *b,
                                            CrankRanUint *r);




//////// Int Ranges ////////////////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void           crank_ran_int_init (CrankRanInt *ran,
                                   const gint   start,
                                   const gint   end);

void           crank_ran_int_init_diff (CrankRanInt *ran,
                                        const gint   start,
                                        const guint  diff);

void           crank_ran_int_init_unit (CrankRanInt *ran,
                                        const gint   start);

//////// Basic Functions ///////////////////////////////////////////////////////

void           crank_ran_int_copy (CrankRanInt *ran,
                                   CrankRanInt *other);

CrankRanInt   *crank_ran_int_dup (CrankRanInt *ran);

gboolean       crank_ran_int_equal (gconstpointer a,
                                    gconstpointer b);

guint          crank_ran_int_hash (gconstpointer a);

gchar         *crank_ran_int_to_string (CrankRanInt *ran);

gchar         *crank_ran_int_to_string_full (CrankRanInt *ran,
                                             const gchar *format);


//////// Classification ////////////////////////////////////////////////////////

gboolean       crank_ran_int_is_empty (CrankRanInt *ran);

gboolean       crank_ran_int_is_unit (CrankRanInt *ran);

//////// Attributes ////////////////////////////////////////////////////////////

guint          crank_ran_int_get_length (CrankRanInt *ran);


//////// Range function ////////////////////////////////////////////////////////

gboolean       crank_ran_int_contains (CrankRanInt *ran,
                                       const gint   value);

gint           crank_ran_int_get (CrankRanInt *ran,
                                  const gfloat index);

gfloat         crank_ran_int_index_of (CrankRanInt *ran,
                                       const gint   value);

gint           crank_ran_int_clamp (CrankRanInt *ran,
                                    const gint   value);

//////// Range - Range operations //////////////////////////////////////////////

gboolean       crank_ran_int_intersection (CrankRanInt *a,
                                           CrankRanInt *b,
                                           CrankRanInt *r);




//////// Float Ranges //////////////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void           crank_ran_float_init (CrankRanFloat *ran,
                                     const gfloat   start,
                                     const gfloat   end);

void           crank_ran_float_init_diff (CrankRanFloat *ran,
                                          const gfloat   start,
                                          const gfloat   diff);

void           crank_ran_float_init_unit (CrankRanFloat *ran,
                                          const gfloat   start);


//////// Basic Functions ///////////////////////////////////////////////////////

void           crank_ran_float_copy (CrankRanFloat *ran,
                                     CrankRanFloat *other);

CrankRanFloat *crank_ran_float_dup (CrankRanFloat *ran);

gboolean       crank_ran_float_equal (gconstpointer a,
                                      gconstpointer b);

gboolean       crank_ran_float_equal_delta (gconstpointer a,
                                            gconstpointer b,
                                            const gfloat  d);


guint          crank_ran_float_hash (gconstpointer a);

gchar         *crank_ran_float_to_string (CrankRanFloat *ran);

gchar         *crank_ran_float_to_string_full (CrankRanFloat *ran,
                                               const gchar   *format);


//////// Classification ////////////////////////////////////////////////////////

gboolean       crank_ran_float_is_empty (CrankRanFloat *ran);

gboolean       crank_ran_float_is_unit (CrankRanFloat *ran);

gboolean       crank_ran_float_is_nan (CrankRanFloat *ran);

gboolean       crank_ran_float_has_inf (CrankRanFloat *ran);

gboolean       crank_ran_float_has_pinf (CrankRanFloat *ran);

gboolean       crank_ran_float_has_ninf (CrankRanFloat *ran);

//////// Attributes ////////////////////////////////////////////////////////////

gfloat         crank_ran_float_get_length (CrankRanFloat *ran);


//////// Range function ////////////////////////////////////////////////////////

gboolean       crank_ran_float_contains (CrankRanFloat *ran,
                                         const gfloat   value);

gfloat         crank_ran_float_get (CrankRanFloat *ran,
                                    const gfloat   index);

gfloat         crank_ran_float_index_of (CrankRanFloat *ran,
                                         const gfloat   value);

gfloat         crank_ran_float_clamp (CrankRanFloat *ran,
                                      const gfloat   value);


//////// Range - Range operations //////////////////////////////////////////////

gboolean        crank_ran_float_intersection (CrankRanFloat *a,
                                              CrankRanFloat *b,
                                              CrankRanFloat *r);



//////// Pointer Ranges ////////////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

void           crank_ran_ptr_init (CrankRanPtr *ran,
                                   gpointer     start,
                                   gpointer     end);

void           crank_ran_ptr_init_diff (CrankRanPtr *ran,
                                        gpointer     start,
                                        gsize        diff);

/**
 * crank_ran_ptr_init_typed:
 * @ran: (out): A Range
 * @T: Type of chunk.
 * @start: Start of range,
 * @n: Count of chunk
 *
 * Initialize a range with start and given count of sized chunk.
 */
#define crank_ran_ptr_init_typed(ran,T,start,n) \
  crank_ran_ptr_init_diff(ran,start,sizeof(T) * n)

/**
 * crank_ran_ptr_init_typed_unit:
 * @ran: (out): A Range
 * @T: Type of chunk.
 * @start: Start of range
 *
 * Initialize a range for single sized chunk.
 */
#define crank_ran_ptr_init_typed_unit(ran,T,start) \
  crank_ran_ptr_init_typed(ran,T,start,1)


//////// Basic Functions ///////////////////////////////////////////////////////

void         crank_ran_ptr_copy (CrankRanPtr *ran,
                                 CrankRanPtr *other);

CrankRanPtr *crank_ran_ptr_dup (CrankRanPtr *ran);

gboolean     crank_ran_ptr_equal (gconstpointer a,
                                  gconstpointer b);

guint        crank_ran_ptr_hash (gconstpointer a);

gchar       *crank_ran_ptr_to_string (CrankRanPtr *ran);

gchar       *crank_ran_ptr_to_string_full (CrankRanPtr *ran,
                                           const gchar *format);


//////// Classification ////////////////////////////////////////////////////////

gboolean     crank_ran_ptr_is_empty (CrankRanPtr *ran);

/**
 * crank_ran_ptr_is_unit_typed:
 * @ran: (out): A Range
 * @T: Type of chunk.
 *
 * Checks whether the range has unit length. For pointer range, unit length is
 * size of structure.
 *
 * Returns: Whether the range has unit length.
 */
#define crank_ran_ptr_is_unit_typed(ran,T)  \
  (crank_ran_ptr_get_length(ran) == sizeof(T))

//////// Attributes ////////////////////////////////////////////////////////////

gsize        crank_ran_ptr_get_length (CrankRanPtr *ran);

//////// Range function ////////////////////////////////////////////////////////

guint        crank_ran_ptr_get_count (CrankRanPtr *ran,
                                      const gsize  size);


/**
 * crank_ran_ptr_get_count_typed:
 * @ran: A Range.
 * @T: Type of chunk.
 *
 * Gets count of chunk in range. This might be useful if the range represents
 * array.
 *
 * Returns: The count of chunk.
 */
#define crank_ran_ptr_get_count_typed(ran,T)    \
  (crank_ran_ptr_get_count(ran,sizeof(T)))

gboolean     crank_ran_ptr_contains (CrankRanPtr *ran,
                                     gpointer     value);

gpointer     crank_ran_ptr_get (CrankRanPtr *ran,
                                const gfloat index);

gfloat       crank_ran_ptr_index_of (CrankRanPtr *ran,
                                     gpointer     value);

gpointer     crank_ran_ptr_clamp (CrankRanPtr *ran,
                                  gpointer     value);


gpointer     crank_ran_ptr_get_step  (CrankRanPtr *ran,
                                      const guint  step,
                                      const gsize  step_size);

guint        crank_ran_ptr_n_step (CrankRanPtr *ran,
                                   gpointer     value,
                                   const gsize  step_size);

/**
 * crank_ran_ptr_get_step_typed:
 * @ran: A Range.
 * @T: Type of chunks.
 * @step: Count of steps.
 *
 * Gets pointer that away given step from start. It might be useful for working
 * with arrays.
 *
 * Returns: A Stepped pointer from start.
 */
#define crank_ran_ptr_get_step_typed(ran,T,step)    \
  (crank_ran_ptr_get_step(ran,step,sizeof(T)))

/**
 * crank_ran_ptr_n_step_typed:
 * @ran: A Range.
 * @T: Type of chunks.
 * @value: value to count steps.
 *
 * Count the steps to @value. It might be useful for working with arrays.
 *
 * Returns: Count of step to @value.
 */
#define crank_ran_ptr_n_step_typed(ran,T,value) \
  (crank_ran_ptr_n_step(ran,value,sizeof(T)))

#endif
