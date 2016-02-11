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

#include <string.h>

#include <glib.h>
#include <glib-object.h>

#include "crankvalue.h"
#include "crankbits.h"
#include "crankvecuint.h"
#include "crankcellspace3.h"

/**
 * SECTION: crankcellspace3
 * @title: CrankCellSpace3
 * @short_description: Cell based storage.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Represents 2 dimensional #GValue array, with resizability. For convinience,
 * it provides getters and setters for basic types.
 *
 * # Reserved Spaces
 *
 * For performance, CrankCellSpace3 may allocate more than it needs, to avoid
 * frequent reallocation.
 * When cell space is reallocating its space, it will grow reserved size twice.
 *
 * Initially created cell space will have power of 2 of size.
 */

//////// Private Macros ////////////////////////////////////////////////////////

#define CELL_INDEX(_w,_h,_x,_y,_z)     (((_z) * (_h) + (_y)) * (_w) + (_x))
#define CELL_SPACE_INDEX(cs,_x,_y,_z)  CELL_INDEX((cs)->reserved_size.x, (cs)->reserved_size.y, _x,_y,_z)


//////// Private functions /////////////////////////////////////////////////////

static void   crank_cell_space3_extend_reserv_rows (CrankCellSpace3 *cs,
                                                    const guint      width);

static void   crank_cell_space3_shrink_reserv_rows (CrankCellSpace3 *cs,
                                                    const guint      width);

static void   crank_cell_space3_extend_rows (CrankCellSpace3 *cs,
                                             const guint      width);

static void   crank_cell_space3_shrink_rows (CrankCellSpace3 *cs,
                                             const guint      width);


static void   crank_cell_space3_extend_reserv_cols (CrankCellSpace3 *cs,
                                                    const guint      heights);

static void   crank_cell_space3_shrink_reserv_cols (CrankCellSpace3 *cs,
                                                    const guint      heights);

static void   crank_cell_space3_extend_cols (CrankCellSpace3 *cs,
                                             const guint      heights);

static void   crank_cell_space3_shrink_cols (CrankCellSpace3 *cs,
                                             const guint      heights);


static void   crank_cell_space3_extend_reserv_pins (CrankCellSpace3 *cs,
                                                    const guint      depth);

static void   crank_cell_space3_shrink_reserv_pins (CrankCellSpace3 *cs,
                                                    const guint      depth);

static void   crank_cell_space3_extend_pins (CrankCellSpace3 *cs,
                                             const guint      depth);

static void   crank_cell_space3_shrink_pins (CrankCellSpace3 *cs,
                                             const guint      depth);



static void   crank_cell_space3_set_size_xy (CrankCellSpace3     *cs,
                                             const CrankVecUint3 *size);

static void   crank_cell_space3_set_resize_size_xy (CrankCellSpace3     *cs,
                                                    const CrankVecUint3 *size);

//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankCellSpace3,
                     crank_cell_space3,
                     crank_cell_space3_ref,
                     crank_cell_space3_unref);

struct _CrankCellSpace3
{
  guint           _refc;

  GArray         *varray;
  CrankVecUint3   size;
  CrankVecUint3   reserved_size;
};


//////// Private functions /////////////////////////////////////////////////////

static void
crank_cell_space3_extend_reserv_rows (CrankCellSpace3 *cs,
                                      const guint      width)
{
  gsize   rowsize;
  guint   i;
  guint   j;

  // Reallocate extended size.
  g_array_set_size (cs->varray,
                    width *
                    cs->reserved_size.y *
                    cs->reserved_size.z);

  // Shift from last rows.
  // The first row does not need to move.
  rowsize = sizeof (GValue) * cs->size.x;

  for (i = cs->size.z; 0 < i ;)
    {
      i--;
      for (j = cs->size.y; 0 < j; )
        {
          j--;
          guint index_row;
          guint nindex_row;

          index_row =  CELL_SPACE_INDEX (cs, 0, j, i);
          nindex_row = CELL_INDEX (width,
                                   cs->reserved_size.y,
                                   0, j, i);

          memmove (&g_array_index (cs->varray, GValue, nindex_row),
                   &g_array_index (cs->varray, GValue, index_row),
                   rowsize);
        }
    }

  cs->reserved_size.x = width;
}

static void
crank_cell_space3_shrink_reserv_rows (CrankCellSpace3 *cs,
                                      const guint      width)
{
  gsize   rowsize;
  guint   i;
  guint   j;

  // Shift from second rows.
  // The first row does not need to move.
  rowsize = sizeof (GValue) * cs->size.x;

  for (i = 0; i < cs->size.z; i++)
    {
      for (j = 0; j < cs->size.y; i++)
        {
          guint index_row;
          guint nindex_row;

          index_row =  CELL_SPACE_INDEX (cs, 0, j, i);
          nindex_row = CELL_INDEX (width,
                                   cs->reserved_size.y,
                                   0, j, i);

          memmove (&g_array_index (cs->varray, GValue, nindex_row),
                   &g_array_index (cs->varray, GValue, index_row),
                   rowsize);
        }
    }

  // Reallocate shrunk size.
  g_array_set_size (cs->varray,
                    width *
                    cs->reserved_size.y *
                    cs->reserved_size.z);

  cs->reserved_size.x = width;
}


static void
crank_cell_space3_extend_rows (CrankCellSpace3 *cs,
                               const guint      width)
{
  gsize   extend_size;
  guint   i;
  guint   j;

  // Extend reserved size, if needed.
  if (cs->reserved_size.x < width)
    {
      guint nrwidth = cs->reserved_size.x;

      while (nrwidth <= width)
        nrwidth <<= 1;

      crank_cell_space3_extend_reserv_rows (cs, nrwidth);
    }

  // Janitor jobs.
  extend_size = sizeof (GValue) * (width - cs->size.x);

  for (i = 0; i < cs->size.z; i++)
    {
      for (j = 0; j < cs->size.y; j++)
        {
          guint index_extend = CELL_SPACE_INDEX (cs, cs->size.x, j, i);

          memset (&g_array_index (cs->varray, GValue, index_extend),
                  0,
                  extend_size);
        }
    }

  cs->size.x = width;
}

static void
crank_cell_space3_shrink_rows (CrankCellSpace3 *cs,
                               const guint      width)
{
  guint i;
  guint j;

  // Clean out truncated values.
  for (i = 0; i < cs->size.z; i++)
    {
      for (j = 0; j < cs->size.y; i++)
        {
          guint rowindex = CELL_SPACE_INDEX (cs, 0, j, i);
          guint kend = rowindex + cs->size.x;
          guint k    = rowindex + width;

          for (; k < kend; k++)
            {
              GValue *value = &g_array_index (cs->varray, GValue, j);
              crank_value_unset (value);
            }
        }
    }

  cs->size.x = width;
}



static void
crank_cell_space3_extend_reserv_cols (CrankCellSpace3 *cs,
                                      const guint      height)
{
  gsize rowsize;
  guint i;
  guint j;

  // Reallocate array.
  g_array_set_size (cs->varray,
                    cs->reserved_size.x *
                    height *
                    cs->reserved_size.z);

  // Shift from last rows.
  rowsize = sizeof (GValue) * cs->reserved_size.x;
  for (i = cs->size.z - 1; 0 < i;i--)
    {
      for (j = cs->size.y; 0 < j;)
        {
          guint index;
          guint nindex;
          j--;

          index  = CELL_SPACE_INDEX (cs, 0, i, j);
          nindex = CELL_INDEX (cs->reserved_size.x,
                               height,
                               0, j, i);

          memmove (& g_array_index (cs->varray, GValue, nindex),
                   & g_array_index (cs->varray, GValue, index),
                   rowsize);
        }
    }

  cs->reserved_size.y = height;
}

static void
crank_cell_space3_shrink_reserv_cols (CrankCellSpace3 *cs,
                                      const guint      height)
{
  gsize rowsize;
  guint i;
  guint j;

  // Shift from first rows
  rowsize = sizeof (GValue) * cs->reserved_size.x;
  for (i = 0; i < cs->size.z; i++)
    {
      for (j = 0; j < cs->size.y; i++)
        {
          guint index;
          guint nindex;

          index  = CELL_SPACE_INDEX (cs, 0, i, j);
          nindex = CELL_INDEX (cs->reserved_size.x,
                               height,
                               0, j, i);

          memmove (& g_array_index (cs->varray, GValue, nindex),
                   & g_array_index (cs->varray, GValue, index),
                   rowsize);
        }
    }

  // Reallocate shrunk array.
  g_array_set_size (cs->varray,
                    cs->reserved_size.x *
                    height *
                    cs->reserved_size.z);

  cs->reserved_size.y = height;
}


static void
crank_cell_space3_extend_cols (CrankCellSpace3 *cs,
                               const guint      height)
{
  gsize extend_size;
  guint i;
  guint j;

  // Extend reserved size, if needed.

  if (cs->reserved_size.y < height)
    {
      guint nrheight = cs->reserved_size.y;

      while (nrheight <= height)
        nrheight <<= 1;

      crank_cell_space3_extend_reserv_rows (cs, nrheight);
    }


  // Janitor jobs.

  extend_size = sizeof (GValue) * cs->size.x;
  for (i = 0; i < cs->size.z; i++)
    {
      for (j = cs->size.y; j < height; j++)
        {
          guint rowindex = CELL_SPACE_INDEX (cs, 0, j, i);
          memset (&g_array_index (cs->varray, GValue, rowindex),
                  0,
                  extend_size);
        }
    }

  cs->size.y = height;
}

static void
crank_cell_space3_shrink_cols (CrankCellSpace3 *cs,
                               const guint      height)
{
  guint i;
  guint j;

  // Clear out truncated values.
  for (i = 0; cs->size.z; i++)
    {
      for (j = height; j < cs->size.y; j++)
        {
          guint rowindex = CELL_SPACE_INDEX (cs, 0, j, i);
          guint k =    rowindex;
          guint kend = rowindex + cs->size.x;

          for (; k < kend; k++)
            {
              GValue *value = &g_array_index (cs->varray, GValue, j);
              crank_value_unset (value);
            }
        }
    }

  cs->size.y = height;
}


static void
crank_cell_space3_extend_reserv_pins (CrankCellSpace3 *cs,
                                      const guint      depth)
{
  // Reallocate array.
  g_array_set_size (cs->varray,
                    cs->reserved_size.x *
                    cs->reserved_size.y *
                    depth);

  cs->reserved_size.z = depth;
}


static void
crank_cell_space3_shrink_reserv_pins (CrankCellSpace3 *cs,
                                      const guint      depth)
{
  // Reallocate array
  g_array_set_size (cs->varray,
                    cs->reserved_size.x *
                    cs->reserved_size.y *
                    depth);

  cs->reserved_size.z = depth;
}


static void
crank_cell_space3_extend_pins (CrankCellSpace3 *cs,
                               const guint      depth)
{
  gsize rowsize;
  guint i;
  guint j;

  // Extend reserved size, if needed.
  if (cs->reserved_size.z < depth)
    {
      guint nrdepth = cs->reserved_size.z;

      while (nrdepth <= depth)
        nrdepth <<= 1;

      crank_cell_space3_extend_reserv_pins (cs, nrdepth);
    }

  // Janitory job.
  rowsize = sizeof (GValue) * cs->size.x;
  for (i = cs->size.z; i < depth; i++)
    {
      for (j = 0; j < cs->size.y; j++)
        {
          guint rowindex = CELL_SPACE_INDEX (cs, 0, j, i);
          memset (& g_array_index (cs->varray, GValue, rowindex),
                  0,
                  rowsize);
        }
    }

  cs->size.z = depth;
}

static void
crank_cell_space3_shrink_pins (CrankCellSpace3 *cs,
                               const guint      depth)
{
  guint i;
  guint j;

  // Clear out truncated values.
  for (i = depth; cs->size.z; i++)
    {
      for (j = 0; cs->size.y; j++)
        {
          guint rowindex = CELL_SPACE_INDEX (cs, 0, j, i);
          guint k =    rowindex;
          guint kend = rowindex + cs->size.x;

          for (k = 0; k < kend; k++)
            {
              GValue *value = & g_array_index (cs->varray, GValue, k);
              crank_value_unset (value);
            }
        }
    }

  cs->size.z = depth;
}



static void
crank_cell_space3_set_size_xy (CrankCellSpace3     *cs,
                               const CrankVecUint3 *size)
{
  if (size->y < cs->size.y)
    {
      crank_cell_space3_shrink_cols (cs, size->y);
      crank_cell_space3_set_width (cs, size->x);
    }
  else
    {
      crank_cell_space3_set_width (cs, size->x);
      if (size->y > cs->size.y)
        crank_cell_space3_extend_cols (cs, size->y);
    }
}


static void
crank_cell_space3_set_reserved_size_xy (CrankCellSpace3     *cs,
                                        const CrankVecUint3 *size)
{
  g_return_if_fail (cs->size.y < size->y);

  if (size->y < cs->reserved_size.y)
    {
      crank_cell_space3_shrink_reserv_cols (cs, size->y);
      crank_cell_space3_set_reserved_width (cs, size->x);
    }
  else
    {
      crank_cell_space3_set_reserved_width (cs, size->x);
      if (size->y > cs->size.y)
        crank_cell_space3_extend_reserv_cols (cs, size->y);
    }
}



//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_cell_space3_new:
 *
 * Constructs an empty cell space.
 *
 * Returns: (transfer full): Newly constructed cell space.
 */
CrankCellSpace3*
crank_cell_space3_new (void)
{
  return crank_cell_space3_new_with_size (0, 0, 0);
}



/**
 * crank_cell_space3_new_with_size:
 * @width: Number of elements in a row.
 * @height: Number of elements in a column.
 *
 * Constructs a sized cell space.
 *
 * Returns: (transfer full): Newly constructed cell space.
 */
CrankCellSpace3*
crank_cell_space3_new_with_size (const guint width,
                                 const guint height,
                                 const guint depth)
{
  CrankCellSpace3 *cs = g_new (CrankCellSpace3, 1);

  cs->_refc = 1;

  crank_vec_uint3_init (& cs->size, width, height, depth);
  cs->reserved_size.x = crank_bits_least_pow2_32 (width);
  cs->reserved_size.y = crank_bits_least_pow2_32 (height);
  cs->reserved_size.z = crank_bits_least_pow2_32 (depth);

  cs->varray = g_array_sized_new (FALSE, TRUE,
                                  sizeof (GValue),
                                  cs->reserved_size.x *
                                  cs->reserved_size.y *
                                  cs->reserved_size.z);

  return cs;
}



/**
 * crank_cell_space3_new_with_sizev:
 * @size: Size of cell space.
 *
 * Same as crank_cell_space3_new_with_size() but accepts single #CrankVecUint3
 * instead of two #guint parameters.
 *
 * Returns: (transfer full): Newly constructed cell space.
 */
CrankCellSpace3*
crank_cell_space3_new_with_sizev (const CrankVecUint3 *size)
{
  return crank_cell_space3_new_with_size (size->x, size->y, size->z);
}



/**
 * crank_cell_space3_ref:
 * @cs: A Cell Space.
 *
 * Increase reference count of cell space.
 *
 * Returns: (transfer full): @cs with increased reference counter.
 */
CrankCellSpace3*
crank_cell_space3_ref (CrankCellSpace3 *cs)
{
  g_atomic_int_inc (&cs->_refc);
  return cs;
}



/**
 * crank_cell_space3_unref:
 * @cs: A Cell Space.
 *
 * Decrease reference count of cell space.
 */
void
crank_cell_space3_unref (CrankCellSpace3 *cs)
{
  if (g_atomic_int_dec_and_test (&cs->_refc))
    {
      crank_cell_space3_unset_all (cs);
      g_array_unref (cs->varray);
    }
}




//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_cell_space3_get_width:
 * @cs: A Cell Space.
 *
 * Gets number of values in a row of a cell space.
 *
 * Returns: Number of values in a row of cell space.
 */
guint
crank_cell_space3_get_width (CrankCellSpace3 *cs)
{
  return cs->size.x;
}



/**
 * crank_cell_space3_set_width:
 * @cs: A Cell Space.
 * @width: Number of values in a row.
 *
 * Sets number of values in a row of a cell space.
 *
 * This may cause reallocation.
 */
void
crank_cell_space3_set_width (CrankCellSpace3 *cs,
                             const guint      width)
{
  if (cs->size.x < width)
    crank_cell_space3_extend_rows (cs, width);
  else if (width < cs->size.x)
    crank_cell_space3_shrink_rows (cs, width);
}



/**
 * crank_cell_space3_get_height:
 * @cs: A Cell Space.
 *
 * Gets number of values in a column of a cell space.
 *
 * Returns: Number of values in a column of cell space.
 */
guint
crank_cell_space3_get_height (CrankCellSpace3 *cs)
{
  return cs->size.y;
}


/**
 * crank_cell_space3_set_height:
 * @cs: A Cell Space.
 * @height: Number of values in a column of cell space.
 *
 * Sets number of values in a column of a cell space.
 */
void
crank_cell_space3_set_height (CrankCellSpace3 *cs,
                              const guint      height)
{
  if (cs->size.y < height)
    crank_cell_space3_extend_cols (cs, height);
  else if (height < cs->size.y)
    crank_cell_space3_shrink_cols (cs, height);
}

/**
 * crank_cell_space3_get_depth:
 * @cs: A Cell Space.
 *
 * Gets number of values in depth direction in cell space.
 *
 * Returns: Number of values in depth direction in cell space.
 */
guint
crank_cell_space3_get_depth (CrankCellSpace3 *cs)
{
  return cs->size.z;
}

/**
 * crank_cell_space3_set_depth:
 * @cs: A Cell Space.
 * @depth: Number of values in depth direction.
 *
 * Sets number of values in the depth.
 */
void
crank_cell_space3_set_depth (CrankCellSpace3 *cs,
                             const guint      depth)
{
  if (cs->size.z < depth)
    crank_cell_space3_extend_pins (cs, depth);
  else if (depth < cs->size.z)
    crank_cell_space3_shrink_pins (cs, depth);
}


/**
 * crank_cell_space3_get_size:
 * @cs: A Cell Space.
 * @size: (out): A Size.
 *
 * Gets number of values in row and column of a cell space.
 */
void
crank_cell_space3_get_size (CrankCellSpace3 *cs,
                            CrankVecUint3   *size)
{
  crank_vec_uint3_copy (&cs->size, size);
}


/**
 * crank_cell_space3_set_size:
 * @cs: A Cell Space.
 * @size: A Size.
 *
 * Sets number of values in row and column of a cell space.
 */
void
crank_cell_space3_set_size (CrankCellSpace3     *cs,
                            const CrankVecUint3 *size)
{
  if (size->z < cs->size.z)
    {
      crank_cell_space3_shrink_pins (cs, size->z);
      crank_cell_space3_set_size_xy (cs, size);
    }
  else
    {
      crank_cell_space3_set_size_xy (cs, size);
      if (size->z > cs->size.z)
        crank_cell_space3_extend_pins (cs, size->z);
    }
}


/**
 * crank_cell_space3_get_reserved_width:
 * @cs: A Cell Space.
 *
 * Gets actual allocated number for a row.
 *
 * Returns: allocated number for a row.
 */
guint
crank_cell_space3_get_reserved_width (CrankCellSpace3 *cs)
{
  return cs->reserved_size.x;
}



/**
 * crank_cell_space3_set_reserved_width:
 * @cs: A Cell Space.
 * @width: Allocated number for a row.
 *
 * Sets actual allocated number for a row. This requires @width to be larger
 * than used size which can be queried by crank_cell_space3_get_width().
 */
void
crank_cell_space3_set_reserved_width (CrankCellSpace3 *cs,
                                      const guint      width)
{
  g_return_if_fail (cs->size.x <= width);

  if (width < cs->reserved_size.x)
    crank_cell_space3_shrink_reserv_rows (cs, width);
  else if (cs->reserved_size.x < width)
    crank_cell_space3_extend_reserv_rows (cs, width);
}


/**
 * crank_cell_space3_get_reserved_height:
 * @cs: A Cell Space.
 *
 * Gets actual allocated number for a column.
 *
 * Returns: allocated number for a column.
 */
guint
crank_cell_space3_get_reserved_height (CrankCellSpace3 *cs)
{
  return cs->reserved_size.y;
}


/**
 * crank_cell_space3_set_reserved_height:
 * @cs: A Cell Space.
 * @height: Allocated number for a column.
 *
 * Sets actual allocated number for a column. This requires @height to be larger
 * than used size which can be queried by crank_cell_space3_get_height().
 */
void
crank_cell_space3_set_reserved_height (CrankCellSpace3 *cs,
                                       const guint      height)
{
  g_return_if_fail (cs->size.y <= height);

  if (height < cs->reserved_size.y)
    crank_cell_space3_shrink_reserv_rows (cs, height);
  else if (cs->reserved_size.y < height)
    crank_cell_space3_extend_reserv_rows (cs, height);
}


/**
 * crank_cell_space3_get_reserved_depth:
 * @cs: A Cell Space.
 *
 * Gets actual allocated number for depth direction.
 *
 * Returns: allocated number for depth direction.
 */
guint
crank_cell_space3_get_reserved_depth (CrankCellSpace3 *cs)
{
  return cs->reserved_size.z;
}


/**
 * crank_cell_space3_set_reserved_depth:
 * @cs: A Cell Space.
 * @depth: Allocated number for depth direction.
 *
 * Sets actual allocated number for depth direction. This requires @depth to be
 * larger than used size which can be queried by crank_cell_space3_get_depth().
 */
void
crank_cell_space3_set_reserved_depth (CrankCellSpace3 *cs,
                                      const guint      depth)
{
  g_return_if_fail (cs->size.z <= depth);

  if (depth < cs->reserved_size.z)
    crank_cell_space3_shrink_reserv_pins (cs, depth);
  else if (cs->reserved_size.z < depth)
    crank_cell_space3_extend_reserv_pins (cs, depth);
}


/**
 * crank_cell_space3_get_reserved_size:
 * @cs: A Cell Space.
 * @size: (out): Size of cell space.
 *
 * Gets actual allocated size for a space.
 */
void
crank_cell_space3_get_reserved_size (CrankCellSpace3 *cs,
                                     CrankVecUint3   *size)
{
  crank_vec_uint3_copy (& cs->reserved_size, size);
}

/**
 * crank_cell_space3_set_reserved_size:
 * @cs: A Cell Space.
 * @size: Size of cell space.
 *
 * Sets actual allocated size for a space. This requires @size to be larger than
 * used size which can be queried by crank_cell_space3_get_size().
 */
void
crank_cell_space3_set_reserved_size (CrankCellSpace3     *cs,
                                    const CrankVecUint3 *size)
{
  g_return_if_fail (cs->size.z <= size->z);

  if (size->z < cs->reserved_size.z)
    {
      crank_cell_space3_shrink_reserv_pins (cs, size->z);
      crank_cell_space3_set_reserved_size_xy (cs, size);
    }
  else
    {
      crank_cell_space3_set_reserved_size_xy (cs, size);
      if (cs->size.z < size->z)
        crank_cell_space3_extend_reserv_pins (cs, size->z);
    }
}





//////// Data Access ///////////////////////////////////////////////////////////

/**
 * crank_cell_space3_get:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @di: Depth-side index
 * @value: (out): Cell Value.
 *
 * Gets value on @wi, @hi.
 */
void
crank_cell_space3_get (const CrankCellSpace3 *cs,
                       const guint            wi,
                       const guint            hi,
                       const guint            di,
                       GValue                *value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);

  crank_value_overwrite (value,
                         &g_array_index (cs->varray, GValue, index));
}

/**
 * crank_cell_space3_set:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @di: Depth-side index
 * @value: Cell Value
 *
 * Sets value on @wi, @hi.
 */
void
crank_cell_space3_set (CrankCellSpace3 *cs,
                       const guint      wi,
                       const guint      hi,
                       const guint      di,
                       const GValue    *value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite (vcell, value);
}

/**
 * crank_cell_space3_dup:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @di: Depth-side index
 *
 * Duplicates value structure on @wi, @hi.
 *
 * Returns: (nullable) (transfer full): A duplicated #GValue or %NULL if the
 *     cell is empty.
 */
GValue*
crank_cell_space3_dup (const CrankCellSpace3 *cs,
                       const guint            wi,
                       const guint            hi,
                       const guint            di)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  return crank_value_dup (&g_array_index (cs->varray, GValue, index));
}


/**
 * crank_cell_space3_peek: (skip)
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @di: Depth-side index
 *
 * Gets value structure on cell.
 *
 * Returns: (transfer none): The #GValue on the cell.
 */
const GValue*
crank_cell_space3_peek (const CrankCellSpace3 *cs,
                        const guint            wi,
                        const guint            hi,
                        const guint            di)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  return &g_array_index (cs->varray, GValue, index);
}


/**
 * crank_cell_space3_unset:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @di: Depth-side index
 *
 * Unsets value on @wi, @hi.
 *
 * Returns: Whether the cell contained value, and unsetted.
 */
gboolean
crank_cell_space3_unset (CrankCellSpace3 *cs,
                         const guint      wi,
                         const guint      hi,
                         const guint      di)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);
  gboolean result = G_IS_VALUE (vcell);

  crank_value_unset (vcell);
  return result;
}


/**
 * crank_cell_space3_is_unset:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @di: Depth-side index
 *
 * Checks whether the cell does not contains any data and unsetted.
 *
 * Returns: Whether the cell is unset.
 */
gboolean
crank_cell_space3_is_unset (const CrankCellSpace3 *cs,
                            const guint            wi,
                            const guint            hi,
                            const guint            di)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  return G_IS_VALUE (vcell);
}


/**
 * crank_cell_space3_type_of:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @di: Depth-side index
 *
 * Gets #GType that value setted for on the cell.
 *
 * Returns: #GType that the value is initialized.
 */
GType
crank_cell_space3_type_of (const CrankCellSpace3 *cs,
                           const guint            wi,
                           const guint            hi,
                           const guint            di)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  return G_IS_VALUE (vcell) ? G_VALUE_TYPE (vcell) : G_TYPE_INVALID;
}


/**
 * crank_cell_space3_unset_all:
 * @cs: A Cell Space.
 *
 * Unset all of values.
 */
void
crank_cell_space3_unset_all (CrankCellSpace3 *cs)
{
  guint i;
  guint j;
  guint k;
  guint kend;

  for (i = 0; i < cs->size.z; i++)
    {
      for (j = 0; j < cs->size.y; j++)
        {
          guint rowindex = CELL_SPACE_INDEX (cs, 0, j, i);
          k =    rowindex;
          kend = rowindex + cs->size.x;
          for (;k < kend; k++)
            crank_value_unset (& g_array_index (cs->varray, GValue, k));
        }
    }
}






//////// Typed Data Access /////////////////////////////////////////////////////

/**
 * crank_cell_space3_get_boolean:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @def: Failback default value.
 *
 * Gets boolean value on the cell.
 *
 * Returns: Boolean value, or @def if the cell does not contain boolean value.
 */
gboolean
crank_cell_space3_get_boolean (const CrankCellSpace3 *cs,
                               const guint            wi,
                               const guint            hi,
                               const guint            di,
                               const gboolean         def)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  return G_VALUE_HOLDS_BOOLEAN (vcell) ? g_value_get_boolean (vcell) : def;
}

/**
 * crank_cell_space3_set_boolean:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @value: A Boolean value.
 *
 * Sets boolean value on the cell.
 */
void
crank_cell_space3_set_boolean (CrankCellSpace3 *cs,
                               const guint      wi,
                               const guint      hi,
                               const guint      di,
                               const gboolean   value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_boolean (vcell, value);
}





/**
 * crank_cell_space3_get_uint:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @def: Failback default value.
 *
 * Gets uint value on the cell.
 *
 * Returns: Uint value, or @def if the cell does not contain uint value.
 */
guint
crank_cell_space3_get_uint (const CrankCellSpace3 *cs,
                            const guint            wi,
                            const guint            hi,
                            const guint            di,
                            const guint            def)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  return G_VALUE_HOLDS_UINT (vcell) ? g_value_get_uint (vcell) : def;
}

/**
 * crank_cell_space3_set_uint:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @value: A uint value.
 *
 * Sets uint value on the cell.
 */
void
crank_cell_space3_set_uint (CrankCellSpace3 *cs,
                            const guint      wi,
                            const guint      hi,
                            const guint      di,
                            const guint      value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_uint (vcell, value);
}



/**
 * crank_cell_space3_get_int:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @def: Failback default value.
 *
 * Gets int value on the cell.
 *
 * Returns: Int value, or @def if the cell does not contain int value.
 */
gint
crank_cell_space3_get_int (const CrankCellSpace3 *cs,
                           const guint            wi,
                           const guint            hi,
                           const guint            di,
                           const gint             def)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  return G_VALUE_HOLDS_INT (vcell) ? g_value_get_int (vcell) : def;
}

/**
 * crank_cell_space3_set_int:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @value: A int value.
 *
 * Sets int value on the cell.
 */
void
crank_cell_space3_set_int (CrankCellSpace3 *cs,
                           const guint      wi,
                           const guint      hi,
                           const guint      di,
                           const gint       value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_int (vcell, value);
}



/**
 * crank_cell_space3_get_float:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @def: Failback default value.
 *
 * Gets float value on the cell.
 *
 * Returns: Float value, or @def if the cell does not contain float value.
 */
gfloat
crank_cell_space3_get_float (const CrankCellSpace3 *cs,
                             const guint            wi,
                             const guint            hi,
                             const guint            di,
                             const gfloat           def)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  return G_VALUE_HOLDS_FLOAT (vcell) ? g_value_get_float (vcell) : def;
}



/**
 * crank_cell_space3_set_float:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @value: A float value.
 *
 * Sets float value on the cell.
 */
void
crank_cell_space3_set_float (CrankCellSpace3 *cs,
                             const guint      wi,
                             const guint      hi,
                             const guint      di,
                             const gfloat     value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_float (vcell, value);
}



/**
 * crank_cell_space3_get_pointer:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @type: (optional) (out): A optional type receiver.
 *
 * Gets pointer value on the cell. GType may be returned as a GType may derive
 * from a pointer type.
 *
 * Returns: (nullable): Pointer value, or %NULL if the cell does not contain
 * pointer value.
 */
gpointer
crank_cell_space3_get_pointer (const CrankCellSpace3 *cs,
                               const guint            wi,
                               const guint            hi,
                               const guint            di,
                               GType                 *type)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);
  gboolean holds_value = G_VALUE_HOLDS_POINTER (vcell);

  if (type != NULL)
    *type = holds_value ? G_VALUE_TYPE (type) : G_TYPE_INVALID;

  return holds_value ? g_value_get_pointer (vcell) : NULL;
}



/**
 * crank_cell_space3_set_pointer:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @type: GType of pointer type.
 * @value: A float value.
 *
 * Sets pointer value on the cell. If @type is 0, G_TYPE_POINTER will be used.
 */
void
crank_cell_space3_set_pointer (CrankCellSpace3 *cs,
                               const guint      wi,
                               const guint      hi,
                               const guint      di,
                               const GType      type,
                               const gpointer   value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_pointer (vcell, type, value);
}



/**
 * crank_cell_space3_get_boxed:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @type: (optional) (out): A optional type receiver.
 *
 * Gets boxed value on the cell. GType may be returned for type identification.
 *
 * Returns: (nullable) (transfer none): Boxed value, or %NULL if the cell does
 * not contain pointer value.
 */
gpointer
crank_cell_space3_get_boxed (const CrankCellSpace3 *cs,
                             const guint            wi,
                             const guint            hi,
                             const guint            di,
                             GType                 *type)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);
  gboolean holds_value = G_VALUE_HOLDS_BOXED (vcell);

  if (type != NULL)
    *type = holds_value ? G_VALUE_TYPE (type) : G_TYPE_INVALID;

  return holds_value ? g_value_get_boxed (vcell) : NULL;
}



/**
 * crank_cell_space3_set_boxed:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @type: GType of pointer type.
 * @value: (transfer none): A boxed value.
 *
 * Sets (duplicated) boxed value on the cell.
 */
void
crank_cell_space3_set_boxed (CrankCellSpace3 *cs,
                             const guint      wi,
                             const guint      hi,
                             const guint      di,
                             const GType      type,
                             const gpointer   value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_boxed (vcell, type, value);
}


/**
 * crank_cell_space3_dup_boxed:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @type: (optional) (out): A optional type receiver.
 *
 * Duplicates boxed value on the cell. #GType may be returned for type
 * identification.
 *
 * Returns: (nullable) (transfer full): Boxed value, or %NULL if the cell does not contain
 * pointer value. Free/unref with g_boxed_free() with #GType.
 */
gpointer
crank_cell_space3_dup_boxed (const CrankCellSpace3 *cs,
                             const guint            wi,
                             const guint            hi,
                             const guint            di,
                             GType                 *type)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);
  gboolean holds_value = G_VALUE_HOLDS_BOXED (vcell);

  if (type != NULL)
    *type = holds_value ? G_VALUE_TYPE (type) : G_TYPE_INVALID;

  return holds_value ? g_value_dup_boxed (vcell) : NULL;
}



/**
 * crank_cell_space3_take_boxed:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @type: GType of pointer type.
 * @value: (transfer full): A boxed value.
 *
 * Take boxed value to the cell. The cell will take the owneership of @value.
 */
void
crank_cell_space3_take_boxed (CrankCellSpace3 *cs,
                             const guint      wi,
                             const guint      hi,
                             const guint      di,
                             const GType      type,
                             const gpointer   value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_init (vcell, type);
  g_value_take_boxed (vcell, value);
}



/**
 * crank_cell_space3_get_object:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 *
 * Gets #GObject value on the cell.
 *
 * Returns: (nullable) (transfer none) (type GObject) : #GObject value, or %NULL
 * if the cell does not contain #GObject value.
 */
gpointer
crank_cell_space3_get_object (const CrankCellSpace3 *cs,
                              const guint            wi,
                              const guint            hi,
                              const guint            di)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);
  gboolean holds_value = G_VALUE_HOLDS_OBJECT (vcell);

  return holds_value ? g_value_get_object (vcell) : NULL;
}



/**
 * crank_cell_space3_set_object:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @value: (transfer none) (type GObject): A object value.
 *
 * Sets #GObject value on the cell.
 */
void
crank_cell_space3_set_object (CrankCellSpace3 *cs,
                              const guint      wi,
                              const guint      hi,
                              const guint      di,
                              const gpointer   value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_object (vcell, (GObject*) value);
}



/**
 * crank_cell_space3_dup_object:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 *
 * Gets #GObject value on the cell.
 *
 * Returns: (nullable) (transfer full) (type GObject) : #GObject value, or %NULL
 * if the cell does not contain #GObject value.
 */
gpointer
crank_cell_space3_dup_object (const CrankCellSpace3 *cs,
                              const guint            wi,
                              const guint            hi,
                              const guint            di)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);
  gboolean holds_value = G_VALUE_HOLDS_OBJECT (vcell);

  return holds_value ? g_value_dup_object (vcell) : NULL;
}



/**
 * crank_cell_space3_take_object:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @di: Depth-side index
 * @value: (transfer full) (type GObject): A object value.
 *
 * Sets #GObject value on the cell. The cell will take ownership for @value.
 */
void
crank_cell_space3_take_object (CrankCellSpace3 *cs,
                               const guint      wi,
                               const guint      hi,
                               const guint      di,
                               const gpointer   value)
{
  guint index = CELL_SPACE_INDEX (cs, wi, hi, di);
  GValue *vcell = & g_array_index (cs->varray, GValue, index);

  crank_value_overwrite_init (vcell, G_TYPE_OBJECT);
  g_value_take_object (vcell, (GObject*) value);
}
