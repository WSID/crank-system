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

#define _CRANKBASE_INSIDE

#include <math.h>

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankrange.h"
#include "crankiter.h"

/**
 * SECTION: crankiter
 * @title: Basic Iterators
 * @short_description: Basic Iterators
 * @usability: unstable
 * @include: crankbase.h
 *
 * Crank System provides simple iterators.
 *
 * # Basic protocol
 *
 * There are some way to define protocol of iterators,
 * <itemizedlist>
 *   <listitem>T? next (): Retrieve value by next () till it returns %NULL
 *             - python, vala (uses next_value () instead)
 *   </listitem>
 *   <listitem>bool next (), T get (): Proceed by next (), get value by get ()
 *             - Java Collection, vala (supports two protocols)
 *   </listitem>
 * </itemizedlist>
 *
 * Crank System follows second protocol, as it enables iterators on primitive
 * collections.
 */

//////// Boolean Memory Iterators //////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_iter_mem_bool_init:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @to: End of memory range.
 *
 * Initialize memory iterator by start and end points.
 */
void
crank_iter_mem_bool_init (CrankIterMemBool *iter,
                          gboolean         *from,
                          gboolean         *to)
{
  crank_ran_ptr_init (&(iter->range), from, to);
  iter->ptr = from - 1;
}

/**
 * crank_iter_mem_bool_init_with_count:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @count: Number of #guint from start point.
 *
 * Initialize memory iterator by start point and count.
 *
 * Useful especially for array of #guint.
 */
void
crank_iter_mem_bool_init_with_count (CrankIterMemBool *iter,
                                     gboolean         *from,
                                     guint             count)
{
  crank_iter_mem_bool_init (iter, from, from + count);
}

/**
 * crank_iter_mem_bool_init_with_range:
 * @iter: (out): Iterator to initialize.
 * @range: Memory range to iterate.
 *
 * Initialize memory iterator by memory range.
 */
void
crank_iter_mem_bool_init_with_range (CrankIterMemBool *iter,
                                     CrankRanPtr      *range)
{
  crank_ran_ptr_copy (range, &(iter->range));
  iter->ptr = (guint*)(range->start) - 1;
}

//////// Iteration /////////////////////////////////////////////////////////////

/**
 * crank_iter_mem_bool_is_valid:
 * @iter: A Iterator.
 *
 * Checks iterator is valid and can return valid value.
 *
 * Returns: Whether iterator is valid
 */
gboolean
crank_iter_mem_bool_is_valid (CrankIterMemBool *iter)
{
  return (crank_ran_ptr_contains (&(iter->range), iter->ptr));
}

/**
 * crank_iter_mem_bool_next:
 * @iter: A Iterator.
 *
 * Proceed iterator to next position.
 *
 * Returns: Whether iterator proceed to next position.
 */
gboolean
crank_iter_mem_bool_next (CrankIterMemBool *iter)
{
  if (iter->ptr + 1 < (gboolean*)((iter->range).end))
    {
      iter->ptr++;
      return TRUE;
    }
  else
    return FALSE;
}

/**
 * crank_iter_mem_bool_get:
 * @iter: A Iterator.
 *
 * Retrieve value positioned at iterator's position.
 *
 * Returns: A Value.
 */
gboolean
crank_iter_mem_bool_get (CrankIterMemBool *iter)
{
  if (crank_iter_mem_bool_is_valid (iter))
    {
      return (*iter->ptr);
    }
  else
    return 0;
}

/**
 * crank_iter_mem_bool_foreach:
 * @iter: A Iterator
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterate a iterator with given @func.
 *
 * To continue, @func should return %TRUE and, to break, return %FALSE.
 *
 * This will consume @iter to end, unless @func returns %FALSE at the some point
 * in the middle.
 *
 * Returns: Whether the function doesn't return %FALSE.
 */
gboolean
crank_iter_mem_bool_foreach (CrankIterMemBool *iter,
                             CrankBoolBoolFunc func,
                             gpointer          userdata)
{
  if (!crank_iter_mem_bool_is_valid(iter) &&
      !crank_iter_mem_bool_next (iter))
    return TRUE;

  do
    {
      if (!func (crank_iter_mem_bool_get(iter), userdata))
        return FALSE;
    }
  while (crank_iter_mem_bool_next (iter));

  return TRUE;
}




//////// Uint Memory Iterators /////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_iter_mem_uint_init:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @to: End of memory range.
 *
 * Initialize memory iterator by start and end points.
 */
void
crank_iter_mem_uint_init (CrankIterMemUint *iter,
                          guint            *from,
                          guint            *to)
{
  crank_ran_ptr_init (&(iter->range), from, to);
  iter->ptr = from - 1;
}

/**
 * crank_iter_mem_uint_init_with_count:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @count: Number of #guint from start point.
 *
 * Initialize memory iterator by start point and count.
 *
 * Useful especially for array of #guint.
 */
void
crank_iter_mem_uint_init_with_count (CrankIterMemUint *iter,
                                     guint            *from,
                                     guint             count)
{
  crank_iter_mem_uint_init (iter, from, from + count);
}

/**
 * crank_iter_mem_uint_init_with_range:
 * @iter: (out): Iterator to initialize.
 * @range: Memory range to iterate.
 *
 * Initialize memory iterator by memory range.
 */
void
crank_iter_mem_uint_init_with_range (CrankIterMemUint *iter,
                                     CrankRanPtr      *range)
{
  crank_ran_ptr_copy (range, &(iter->range));
  iter->ptr = (guint*)(range->start) - 1;
}

//////// Iteration /////////////////////////////////////////////////////////////

/**
 * crank_iter_mem_uint_is_valid:
 * @iter: A Iterator.
 *
 * Checks iterator is valid and can return valid value.
 *
 * Returns: Whether iterator is valid
 */
gboolean
crank_iter_mem_uint_is_valid (CrankIterMemUint *iter)
{
  return (crank_ran_ptr_contains (&(iter->range), iter->ptr));
}

/**
 * crank_iter_mem_uint_next:
 * @iter: A Iterator.
 *
 * Proceed iterator to next position.
 *
 * Returns: Whether iterator proceed to next position.
 */
gboolean
crank_iter_mem_uint_next (CrankIterMemUint *iter)
{
  if (iter->ptr + 1 < (guint*)((iter->range).end))
    {
      iter->ptr++;
      return TRUE;
    }
  else
    return FALSE;
}

/**
 * crank_iter_mem_uint_get:
 * @iter: A Iterator.
 *
 * Retrieve value positioned at iterator's position.
 *
 * Returns: A Value.
 */
guint
crank_iter_mem_uint_get (CrankIterMemUint *iter)
{
  if (crank_iter_mem_uint_is_valid (iter))
    {
      return (*iter->ptr);
    }
  else
    return 0;
}

/**
 * crank_iter_mem_uint_foreach:
 * @iter: A Iterator
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterate a iterator with given @func.
 *
 * To continue, @func should return %TRUE and, to break, return %FALSE.
 *
 * This will consume @iter to end, unless @func returns %FALSE at the some point
 * in the middle.
 *
 * Returns: Whether the function doesn't return %FALSE.
 */
gboolean
crank_iter_mem_uint_foreach (CrankIterMemUint *iter,
                             CrankBoolUintFunc func,
                             gpointer          userdata)
{
  if (!crank_iter_mem_uint_is_valid(iter) &&
      !crank_iter_mem_uint_next (iter))
    return TRUE;

  do
    {
      if (!func (crank_iter_mem_uint_get(iter), userdata))
        return FALSE;
    }
  while (crank_iter_mem_uint_next (iter));

  return TRUE;
}




//////// Int Memory Iterators //////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_iter_mem_int_init:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @to: End of memory range.
 *
 * Initialize memory iterator by start and end points.
 */
void
crank_iter_mem_int_init (CrankIterMemInt *iter,
                         gint            *from,
                         gint            *to)
{
  crank_ran_ptr_init (&(iter->range), from, to);
  iter->ptr = from - 1;
}

/**
 * crank_iter_mem_int_init_with_count:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @count: Number of #guint from start point.
 *
 * Initialize memory iterator by start point and count.
 *
 * Useful especially for array of #guint.
 */
void
crank_iter_mem_int_init_with_count (CrankIterMemInt *iter,
                                    gint            *from,
                                    guint            count)
{
  crank_iter_mem_int_init (iter, from, from + count);
}

/**
 * crank_iter_mem_int_init_with_range:
 * @iter: (out): Iterator to initialize.
 * @range: Memory range to iterate.
 *
 * Initialize memory iterator by memory range.
 */
void
crank_iter_mem_int_init_with_range (CrankIterMemInt *iter,
                                    CrankRanPtr     *range)
{
  crank_ran_ptr_copy (range, &(iter->range));
  iter->ptr = (gint*)(range->start) - 1;
}

//////// Iteration /////////////////////////////////////////////////////////////

/**
 * crank_iter_mem_int_is_valid:
 * @iter: A Iterator.
 *
 * Checks iterator is valid and can return valid value.
 *
 * Returns: Whether iterator is valid
 */
gboolean
crank_iter_mem_int_is_valid (CrankIterMemInt *iter)
{
  return (crank_ran_ptr_contains (&(iter->range), iter->ptr));
}

/**
 * crank_iter_mem_int_next:
 * @iter: A Iterator.
 *
 * Proceed iterator to next position.
 *
 * Returns: Whether iterator proceed to next position.
 */
gboolean
crank_iter_mem_int_next (CrankIterMemInt *iter)
{
  if (iter->ptr + 1 < (gint*)((iter->range).end))
    {
      iter->ptr++;
      return TRUE;
    }
  else
    return FALSE;
}

/**
 * crank_iter_mem_int_get:
 * @iter: A Iterator.
 *
 * Retrieve value positioned at iterator's position.
 *
 * Returns: A Value.
 */
gint
crank_iter_mem_int_get (CrankIterMemInt *iter)
{
  if (crank_iter_mem_int_is_valid (iter))
    {
      return (*iter->ptr);
    }
  else
    return 0;
}

/**
 * crank_iter_mem_int_foreach:
 * @iter: A Iterator
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterate a iterator with given @func.
 *
 * To continue, @func should return %TRUE and, to break, return %FALSE.
 *
 * This will consume @iter to end, unless @func returns %FALSE at the some point
 * in the middle.
 *
 * Returns: Whether the function doesn't return %FALSE.
 */
gboolean
crank_iter_mem_int_foreach (CrankIterMemInt *iter,
                            CrankBoolIntFunc func,
                            gpointer         userdata)
{
  if (!crank_iter_mem_int_is_valid(iter) &&
      !crank_iter_mem_int_next (iter))
    return TRUE;

  do
    {
      if (!func (crank_iter_mem_int_get(iter), userdata))
        return FALSE;
    }
  while (crank_iter_mem_int_next (iter));

  return TRUE;
}




//////// Float Memory Iterators ////////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_iter_mem_float_init:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @to: End of memory range.
 *
 * Initialize memory iterator by start and end points.
 */
void
crank_iter_mem_float_init (CrankIterMemFloat *iter,
                           gfloat            *from,
                           gfloat            *to)
{
  crank_ran_ptr_init (&(iter->range), from, to);
  iter->ptr = from - 1;
}

/**
 * crank_iter_mem_float_init_with_count:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @count: Number of #guint from start point.
 *
 * Initialize memory iterator by start point and count.
 *
 * Useful especially for array of #guint.
 */
void
crank_iter_mem_float_init_with_count (CrankIterMemFloat *iter,
                                      gfloat            *from,
                                      guint              count)
{
  crank_iter_mem_float_init (iter, from, from + count);
}

/**
 * crank_iter_mem_float_init_with_range:
 * @iter: (out): Iterator to initialize.
 * @range: Memory range to iterate.
 *
 * Initialize memory iterator by memory range.
 */
void
crank_iter_mem_float_init_with_range (CrankIterMemFloat *iter,
                                      CrankRanPtr       *range)
{
  crank_ran_ptr_copy (range, &(iter->range));
  iter->ptr = (gfloat*)(range->start) - 1;
}

//////// Iteration /////////////////////////////////////////////////////////////

/**
 * crank_iter_mem_float_is_valid:
 * @iter: A Iterator.
 *
 * Checks iterator is valid and can return valid value.
 *
 * Returns: Whether iterator is valid
 */
gboolean
crank_iter_mem_float_is_valid (CrankIterMemFloat *iter)
{
  return (crank_ran_ptr_contains (&(iter->range), iter->ptr));
}

/**
 * crank_iter_mem_float_next:
 * @iter: A Iterator.
 *
 * Proceed iterator to next position.
 *
 * Returns: Whether iterator proceed to next position.
 */
gboolean
crank_iter_mem_float_next (CrankIterMemFloat *iter)
{
  if (iter->ptr + 1 < (gfloat*)((iter->range).end))
    {
      iter->ptr++;
      return TRUE;
    }
  else
    return FALSE;
}

/**
 * crank_iter_mem_float_get:
 * @iter: A Iterator.
 *
 * Retrieve value positioned at iterator's position.
 *
 * Returns: A Value.
 */
gfloat
crank_iter_mem_float_get (CrankIterMemFloat *iter)
{
  if (crank_iter_mem_float_is_valid (iter))
    {
      return (*iter->ptr);
    }
  else
    return 0;
}

/**
 * crank_iter_mem_float_foreach:
 * @iter: A Iterator
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterate a iterator with given @func.
 *
 * To continue, @func should return %TRUE and, to break, return %FALSE.
 *
 * This will consume @iter to end, unless @func returns %FALSE at the some point
 * in the middle.
 *
 * Returns: Whether the function doesn't return %FALSE.
 */
gboolean
crank_iter_mem_float_foreach (CrankIterMemFloat *iter,
                              CrankBoolFloatFunc func,
                              gpointer           userdata)
{
  if (!crank_iter_mem_float_is_valid(iter) &&
      !crank_iter_mem_float_next (iter))
    return TRUE;

  do
    {
      if (!func (crank_iter_mem_float_get(iter), userdata))
        return FALSE;
    }
  while (crank_iter_mem_float_next (iter));

  return TRUE;
}




//////// Pointer Memory Iterators //////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_iter_mem_ptr_init:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @to: End of memory range.
 *
 * Initialize memory iterator by start and end points.
 */
void
crank_iter_mem_ptr_init (CrankIterMemPtr *iter,
                         gpointer        *from,
                         gpointer        *to)
{
  crank_ran_ptr_init (&(iter->range), from, to);
  iter->ptr = from - 1;
}

/**
 * crank_iter_mem_ptr_init_with_count:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @count: Number of #guint from start point.
 *
 * Initialize memory iterator by start point and count.
 *
 * Useful especially for array of #guint.
 */
void
crank_iter_mem_ptr_init_with_count (CrankIterMemPtr *iter,
                                    gpointer        *from,
                                    guint            count)
{
  crank_iter_mem_ptr_init (iter, from, from + count);
}

/**
 * crank_iter_mem_ptr_init_with_range:
 * @iter: (out): Iterator to initialize.
 * @range: Memory range to iterate.
 *
 * Initialize memory iterator by memory range.
 */
void
crank_iter_mem_ptr_init_with_range (CrankIterMemPtr *iter,
                                    CrankRanPtr     *range)
{
  crank_ran_ptr_copy (range, &(iter->range));
  iter->ptr = (gpointer)(range->start) - 1;
}

//////// Iteration /////////////////////////////////////////////////////////////

/**
 * crank_iter_mem_ptr_is_valid:
 * @iter: A Iterator.
 *
 * Checks iterator is valid and can return valid value.
 *
 * Returns: Whether iterator is valid
 */
gboolean
crank_iter_mem_ptr_is_valid (CrankIterMemPtr *iter)
{
  return (crank_ran_ptr_contains (&(iter->range), iter->ptr));
}

/**
 * crank_iter_mem_ptr_next:
 * @iter: A Iterator.
 *
 * Proceed iterator to next position.
 *
 * Returns: Whether iterator proceed to next position.
 */
gboolean
crank_iter_mem_ptr_next (CrankIterMemPtr *iter)
{
  if (iter->ptr + 1 < (gpointer*)((iter->range).end))
    {
      iter->ptr++;
      return TRUE;
    }
  else
    return FALSE;
}

/**
 * crank_iter_mem_ptr_get:
 * @iter: A Iterator.
 *
 * Retrieve value positioned at iterator's position.
 *
 * Returns: (transfer none) (nullable): A Value or %NULL if invalid.
 */
gpointer
crank_iter_mem_ptr_get (CrankIterMemPtr *iter)
{
  if (crank_iter_mem_ptr_is_valid (iter))
    {
      return (*iter->ptr);
    }
  else
    return NULL;
}

/**
 * crank_iter_mem_ptr_foreach:
 * @iter: A Iterator
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterate a iterator with given @func.
 *
 * To continue, @func should return %TRUE and, to break, return %FALSE.
 *
 * This will consume @iter to end, unless @func returns %FALSE at the some point
 * in the middle.
 *
 * Returns: Whether the function doesn't return %FALSE.
 */
gboolean
crank_iter_mem_ptr_foreach (CrankIterMemPtr *iter,
                            CrankBoolPtrFunc func,
                            gpointer         userdata)
{
  if (!crank_iter_mem_ptr_is_valid(iter) &&
      !crank_iter_mem_ptr_next (iter))
    return TRUE;

  do
    {
      if (!func (crank_iter_mem_ptr_get(iter), userdata))
        return FALSE;
    }
  while (crank_iter_mem_ptr_next (iter));

  return TRUE;
}




//////// Structure Memory Iterators ////////////////////////////////////////////
//////// Initialization ////////////////////////////////////////////////////////

/**
 * crank_iter_mem_struct_init:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @to: End of memory range.
 * @size: Size of structure.
 *
 * Initialize memory iterator by start and end points.
 */
void
crank_iter_mem_struct_init (CrankIterMemStruct *iter,
                            gpointer            from,
                            gpointer            to,
                            gsize               size)
{
  crank_ran_ptr_init (&(iter->range), from, to);
  iter->ptr = (gpointer)((gsize)from - size);
  iter->size = size;
}

/**
 * crank_iter_mem_struct_init_with_count:
 * @iter: (out): Iterator to initialize.
 * @from: Start of memory range.
 * @count: Number of #guint from start point.
 * @size: Size of structure
 *
 * Initialize memory iterator by start point and count.
 *
 * Useful especially for array of #guint.
 */
void
crank_iter_mem_struct_init_with_count (CrankIterMemStruct *iter,
                                       gpointer            from,
                                       guint               count,
                                       gsize               size)
{
  crank_iter_mem_struct_init (iter, from, from + count, size);
}

/**
 * crank_iter_mem_struct_init_with_range:
 * @iter: (out): Iterator to initialize.
 * @range: Memory range to iterate.
 * @size: Size of structure.
 *
 * Initialize memory iterator by memory range.
 */
void
crank_iter_mem_struct_init_with_range (CrankIterMemStruct *iter,
                                       CrankRanPtr        *range,
                                       gsize               size)
{
  crank_ran_ptr_copy (range, &(iter->range));
  iter->ptr = (gpointer)((gsize)(range->start) - size);
  iter->size = size;
}

//////// Iteration /////////////////////////////////////////////////////////////

/**
 * crank_iter_mem_struct_is_valid:
 * @iter: A Iterator.
 *
 * Checks iterator is valid and can return valid value.
 *
 * Returns: Whether iterator is valid
 */
gboolean
crank_iter_mem_struct_is_valid (CrankIterMemStruct *iter)
{
  return (crank_ran_ptr_contains (&(iter->range), iter->ptr));
}

/**
 * crank_iter_mem_struct_next:
 * @iter: A Iterator.
 *
 * Proceed iterator to next position.
 *
 * Returns: Whether iterator proceed to next position.
 */
gboolean
crank_iter_mem_struct_next (CrankIterMemStruct *iter)
{
  if ((gpointer)((gsize)iter->ptr + iter->size) < iter->range.end)
    {
      iter->ptr = (gpointer)((gsize)iter->ptr + iter->size);
      return TRUE;
    }
  else
    return FALSE;
}

/**
 * crank_iter_mem_struct_get:
 * @iter: A Iterator.
 *
 * Retrieve address of value, where iterator is positioned.
 *
 * Returns: (transfer none) (nullable): A Value, or %NULL if it is invalid.
 */
gpointer
crank_iter_mem_struct_get (CrankIterMemStruct *iter)
{
  if (crank_iter_mem_struct_is_valid (iter))
    {
      return iter->ptr;
    }
  else
    return NULL;
}

/**
 * crank_iter_mem_struct_foreach:
 * @iter: A Iterator
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterate a iterator with given @func.
 *
 * To continue, @func should return %TRUE and, to break, return %FALSE.
 *
 * This will consume @iter to end, unless @func returns %FALSE at the some point
 * in the middle.
 *
 * Returns: Whether the function doesn't return %FALSE.
 */
gboolean
crank_iter_mem_struct_foreach (CrankIterMemStruct *iter,
                               CrankBoolPtrFunc    func,
                               gpointer            userdata)
{
  if (!crank_iter_mem_struct_is_valid(iter) &&
      !crank_iter_mem_struct_next (iter))
    return TRUE;

  do
    {
      if (!func (crank_iter_mem_struct_get(iter), userdata))
        return FALSE;
    }
  while (crank_iter_mem_struct_next (iter));

  return TRUE;
}