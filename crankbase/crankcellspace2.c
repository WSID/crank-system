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
#include "crankcellspace2.h"

/**
 * SECTION: crankcellspace2
 * @title: CrankCellSpace2
 * @short_description: Cell based storage.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Represents 2 dimensional #GValue array, with resizability. For convinience,
 * it provides getters and setters for basic types.
 *
 * # Reserved Spaces
 *
 * For performance, CrankCellSpace2 may allocate more than it needs, to avoid
 * frequent reallocation.
 * When cell space is reallocating its space, it will grow reserved size twice.
 *
 * Initially created cell space will have power of 2 of size.
 */


//////// Private macro /////////////////////////////////////////////////////////

#define CELL_INDEX(_w, _x, _y) (((_w) * (_y)) + (_x))
#define CELL_SPACE_INDEX(cs,_x,_y) CELL_INDEX((cs)->reserved_size.x, _x, _y)

#define CELL_INDEX_VALUE(cs,_i) (&g_array_index((cs)->varray, GValue, _i))
#define CELL_VALUE(cs,_x,_y) CELL_INDEX_VALUE (cs, CELL_SPACE_INDEX(cs,_x,_y))


//////// Private functions /////////////////////////////////////////////////////

static void   crank_cell_space2_clean_rows (CrankCellSpace2 *cs,
                                            const guint      ws,
                                            const guint      we,
                                            const guint      hs,
                                            const guint      he);

static void   crank_cell_space2_unset_rows (CrankCellSpace2 *cs,
                                            const guint      ws,
                                            const guint      we,
                                            const guint      hs,
                                            const guint      he);


static void   crank_cell_space2_extend_reserv_rows (CrankCellSpace2 *cs,
                                                    const guint      width);

static void   crank_cell_space2_shrink_reserv_rows (CrankCellSpace2 *cs,
                                                    const guint      width);

static void   crank_cell_space2_extend_rows (CrankCellSpace2 *cs,
                                             const guint      width);

static void   crank_cell_space2_shrink_rows (CrankCellSpace2 *cs,
                                             const guint      width);

static void   crank_cell_space2_extend_reserv_cols (CrankCellSpace2 *cs,
                                                    const guint      heights);

static void   crank_cell_space2_extend_cols (CrankCellSpace2 *cs,
                                             const guint      heights);

static void   crank_cell_space2_shrink_cols (CrankCellSpace2 *cs,
                                             const guint      heights);

//////// Type Definition ///////////////////////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankCellSpace2,
                     crank_cell_space2,
                     crank_cell_space2_ref,
                     crank_cell_space2_unref);

struct _CrankCellSpace2
{
  guint           _refc;

  GArray         *varray;
  CrankVecUint2   size;
  CrankVecUint2   reserved_size;
};


//////// Private functions /////////////////////////////////////////////////////

static void
crank_cell_space2_clean_rows (CrankCellSpace2 *cs,
                              const guint      ws,
                              const guint      we,
                              const guint      hs,
                              const guint      he)
{
  gsize row_size;
  guint i;

  row_size = sizeof (GValue) * (we - ws);
  for (i = hs; i < he; i++)
    {
      guint row_index = CELL_SPACE_INDEX (cs, ws, i);

      memset (CELL_INDEX_VALUE (cs, row_index), 0, row_size);
    }
}

static void
crank_cell_space2_unset_rows (CrankCellSpace2 *cs,
                              const guint      ws,
                              const guint      we,
                              const guint      hs,
                              const guint      he)
{
  guint i;
  guint j;
  guint je;

  for (i = hs; i < he; i++)
    {
      guint row_index = CELL_SPACE_INDEX (cs, 0, i);
      j =  row_index + ws;
      je = row_index + we;

      for (; j < je; j++)
        crank_value_unset (CELL_INDEX_VALUE(cs, j));
    }
}


static void
crank_cell_space2_extend_reserv_rows (CrankCellSpace2 *cs,
                                      const guint      width)
{
  gsize   rowsize;
  guint   i;

  // Reallocate extended size.
  g_array_set_size (cs->varray,
                    width *
                    cs->reserved_size.y);

  // Shift from last rows.
  // The first row does not need to move.
  rowsize = sizeof (GValue) * cs->size.x;

  if (cs->size.y != 0)
    {
      for (i = cs->size.y - 1; 0 < i ; i--)
        {
          guint index_row;
          guint nindex_row;

          index_row = CELL_SPACE_INDEX (cs, 0, i);
          nindex_row = CELL_INDEX (width, 0, i);

          memmove (CELL_INDEX_VALUE (cs, nindex_row),
                   CELL_INDEX_VALUE (cs, index_row),
                   rowsize);
        }
    }

  cs->reserved_size.x = width;
}

static void
crank_cell_space2_shrink_reserv_rows (CrankCellSpace2 *cs,
                                      const guint      width)
{
  gsize   rowsize;
  guint   i;

  // Shift from second rows.
  // The first row does not need to move.
  rowsize = sizeof (GValue) * cs->size.x;

  for (i = 1; i < cs->size.y; i++)
    {
      guint index_row;
      guint nindex_row;

      index_row = CELL_SPACE_INDEX (cs, 0, i);
      nindex_row = CELL_INDEX (width, 0, i);

      memmove (CELL_INDEX_VALUE (cs, nindex_row),
               CELL_INDEX_VALUE (cs, index_row),
               rowsize);
    }

  // Reallocate shrunk size.
  g_array_set_size (cs->varray, width *cs->reserved_size.y);

  cs->reserved_size.x = width;
}


static void
crank_cell_space2_extend_rows (CrankCellSpace2 *cs,
                               const guint      width)
{
  gsize   extend_size;
  guint   i;

  // Extend reserved size, if needed.
  if (cs->reserved_size.x < width)
    {
      guint nrwidth = cs->reserved_size.x;

      while (nrwidth <= width)
        nrwidth <<= 1;

      crank_cell_space2_extend_reserv_rows (cs, nrwidth);
    }

  // Janitor jobs.
  crank_cell_space2_clean_rows (cs, cs->size.x, width, 0, cs->size.y);

  cs->size.x = width;
}

static void
crank_cell_space2_shrink_rows (CrankCellSpace2 *cs,
                               const guint      width)
{
  guint i;

  // Clean out truncated values.
  crank_cell_space2_unset_rows (cs, width, cs->size.x, 0, cs->size.y);

  cs->size.x = width;
}



static void
crank_cell_space2_extend_reserv_cols (CrankCellSpace2 *cs,
                                      const guint      height)
{
  // Reallocate array.
  g_array_set_size (cs->varray, cs->reserved_size.x * height);

  cs->reserved_size.y = height;
}

static void
crank_cell_space2_shrink_reserv_cols (CrankCellSpace2 *cs,
                                      const guint      height)
{
  // Reallocate shrunk array.
  g_array_set_size (cs->varray, cs->reserved_size.x * height);

  cs->reserved_size.y = height;
}


static void
crank_cell_space2_extend_cols (CrankCellSpace2 *cs,
                               const guint      height)
{
  gsize extend_size;
  guint i;

  // Extend reserved size, if needed.
  if (cs->reserved_size.y < height)
    {
      guint nrheight = cs->reserved_size.y;

      while (nrheight <= height)
        nrheight <<= 1;

      crank_cell_space2_extend_reserv_cols (cs, nrheight);
    }

  // Janitor jobs.
  crank_cell_space2_clean_rows (cs, 0, cs->size.x, cs->size.y, height);

  cs->size.y = height;
}

static void
crank_cell_space2_shrink_cols (CrankCellSpace2 *cs,
                               const guint      height)
{
  guint i;
  guint j;

  // Clear out truncated values.
  crank_cell_space2_unset_rows (cs, 0, cs->size.x, height, cs->size.y);

  cs->size.y = height;
}


//////// Constructors //////////////////////////////////////////////////////////

/**
 * crank_cell_space2_new:
 *
 * Constructs an empty cell space.
 *
 * Returns: (transfer full): Newly constructed cell space.
 */
CrankCellSpace2*
crank_cell_space2_new (void)
{
  return crank_cell_space2_new_with_size (0, 0);
}



/**
 * crank_cell_space2_new_with_size:
 * @width: Number of elements in a row.
 * @height: Number of elements in a column.
 *
 * Constructs a sized cell space.
 *
 * Returns: (transfer full): Newly constructed cell space.
 */
CrankCellSpace2*
crank_cell_space2_new_with_size (const guint width,
                                 const guint height)
{
  CrankCellSpace2 *cs = g_new (CrankCellSpace2, 1);

  cs->_refc = 1;

  crank_vec_uint2_init (& cs->size, width, height);
  cs->reserved_size.x = crank_bits_least_pow2_32 (width);
  cs->reserved_size.y = crank_bits_least_pow2_32 (height);

  cs->varray = g_array_sized_new (FALSE, FALSE,
                                  sizeof (GValue),
                                  cs->reserved_size.x *
                                  cs->reserved_size.y);

  crank_cell_space2_clean_rows (cs, 0, width, 0, height);

  return cs;
}



/**
 * crank_cell_space2_new_with_sizev:
 * @size: Size of cell space.
 *
 * Same as crank_cell_space2_new_with_size() but accepts single #CrankVecUint2
 * instead of two #guint parameters.
 *
 * Returns: (transfer full): Newly constructed cell space.
 */
CrankCellSpace2*
crank_cell_space2_new_with_sizev (const CrankVecUint2 *size)
{
  return crank_cell_space2_new_with_size (size->x, size->y);
}



/**
 * crank_cell_space2_ref:
 * @cs: A Cell Space.
 *
 * Increase reference count of cell space.
 *
 * Returns: (transfer full): @cs with increased reference counter.
 */
CrankCellSpace2*
crank_cell_space2_ref (CrankCellSpace2 *cs)
{
  g_atomic_int_inc (&cs->_refc);
  return cs;
}



/**
 * crank_cell_space2_unref:
 * @cs: A Cell Space.
 *
 * Decrease reference count of cell space.
 */
void
crank_cell_space2_unref (CrankCellSpace2 *cs)
{
  if (g_atomic_int_dec_and_test (&cs->_refc))
    {
      crank_cell_space2_unset_all (cs);
      g_array_unref (cs->varray);
      g_free (cs);
    }
}




//////// Properties ////////////////////////////////////////////////////////////

/**
 * crank_cell_space2_get_width:
 * @cs: A Cell Space.
 *
 * Gets number of values in a row of a cell space.
 *
 * Returns: Number of values in a row of cell space.
 */
guint
crank_cell_space2_get_width (CrankCellSpace2 *cs)
{
  return cs->size.x;
}



/**
 * crank_cell_space2_set_width:
 * @cs: A Cell Space.
 * @width: Number of values in a row.
 *
 * Sets number of values in a row of a cell space.
 *
 * This may cause reallocation.
 */
void
crank_cell_space2_set_width (CrankCellSpace2 *cs,
                             const guint      width)
{
  if (cs->size.x < width)
    crank_cell_space2_extend_rows (cs, width);
  else if (width < cs->size.x)
    crank_cell_space2_shrink_rows (cs, width);
}



/**
 * crank_cell_space2_get_height:
 * @cs: A Cell Space.
 *
 * Gets number of values in a column of a cell space.
 *
 * Returns: Number of values in a column of cell space.
 */
guint
crank_cell_space2_get_height (CrankCellSpace2 *cs)
{
  return cs->size.y;
}


/**
 * crank_cell_space2_set_height:
 * @cs: A Cell Space.
 * @height: Number of values in a column of cell space.
 *
 * Sets number of values in a column of a cell space.
 */
void
crank_cell_space2_set_height (CrankCellSpace2 *cs,
                              const guint      height)
{

  if (cs->size.y < height)
    crank_cell_space2_extend_cols (cs, height);
  else if (height < cs->size.y)
    crank_cell_space2_shrink_cols (cs, height);
}


/**
 * crank_cell_space2_get_size:
 * @cs: A Cell Space.
 * @size: (out): A Size.
 *
 * Gets number of values in row and column of a cell space.
 */
void
crank_cell_space2_get_size (CrankCellSpace2 *cs,
                            CrankVecUint2   *size)
{
  crank_vec_uint2_copy (&cs->size, size);
}


/**
 * crank_cell_space2_set_size:
 * @cs: A Cell Space.
 * @size: A Size.
 *
 * Sets number of values in row and column of a cell space.
 */
void
crank_cell_space2_set_size (CrankCellSpace2     *cs,
                            const CrankVecUint2 *size)
{
  if (size->y < cs->size.y)
    {
      crank_cell_space2_shrink_cols (cs, size->y);
      crank_cell_space2_set_width (cs, size->x);
    }
  else
    {
      crank_cell_space2_set_width (cs, size->x);
      if (cs->size.y < size->y)
        crank_cell_space2_extend_cols (cs, size->y);
    }
}


/**
 * crank_cell_space2_get_reserved_width:
 * @cs: A Cell Space.
 *
 * Gets actual allocated number for a row.
 *
 * Returns: allocated number for a row.
 */
guint
crank_cell_space2_get_reserved_width (CrankCellSpace2 *cs)
{
  return cs->reserved_size.x;
}



/**
 * crank_cell_space2_set_reserved_width:
 * @cs: A Cell Space.
 * @width: Allocated number for a row.
 *
 * Sets actual allocated number for a row. This requires @width to be larger
 * than used size which can be queried by crank_cell_space2_get_width().
 */
void
crank_cell_space2_set_reserved_width (CrankCellSpace2 *cs,
                                      const guint      width)
{
  g_return_if_fail (cs->size.x <= width);

  if (width < cs->reserved_size.x)
    crank_cell_space2_shrink_reserv_rows (cs, width);
  else if (cs->reserved_size.x < width)
    crank_cell_space2_extend_reserv_rows (cs, width);
}


/**
 * crank_cell_space2_get_reserved_height:
 * @cs: A Cell Space.
 *
 * Gets actual allocated number for a column.
 *
 * Returns: allocated number for a column.
 */
guint
crank_cell_space2_get_reserved_height (CrankCellSpace2 *cs)
{
  return cs->reserved_size.y;
}



/**
 * crank_cell_space2_set_reserved_height:
 * @cs: A Cell Space.
 * @height: Allocated number for a column.
 *
 * Sets actual allocated number for a column. This requires @height to be larger
 * than used size which can be queried by crank_cell_space2_get_height().
 */
void
crank_cell_space2_set_reserved_height (CrankCellSpace2 *cs,
                                       const guint      height)
{
  g_return_if_fail (cs->size.y <= height);

  if (height < cs->reserved_size.y)
    crank_cell_space2_shrink_reserv_rows (cs, height);
  else if (cs->reserved_size.y < height)
    crank_cell_space2_extend_reserv_rows (cs, height);
}


/**
 * crank_cell_space2_get_reserved_size:
 * @cs: A Cell Space.
 * @size: (out): Size of cell space.
 *
 * Gets actual allocated size for a space.
 */
void
crank_cell_space2_get_reserved_size (CrankCellSpace2 *cs,
                                     CrankVecUint2   *size)
{
  crank_vec_uint2_copy (& cs->reserved_size, size);
}

/**
 * crank_cell_space2_set_reserved_size:
 * @cs: A Cell Space.
 * @size: Size of cell space.
 *
 * Sets actual allocated size for a space. This requires @size to be larger than
 * used size which can be queried by crank_cell_space2_get_size().
 */
void
crank_cell_space2_set_reserved_size (CrankCellSpace2     *cs,
                                    const CrankVecUint2 *size)
{
  g_return_if_fail (cs->size.y <= size->y);

  if (size->y < cs->reserved_size.y)
    {
      crank_cell_space2_shrink_reserv_cols (cs, size->y);
      crank_cell_space2_set_reserved_width (cs, size->x);
    }
  else
    {
      crank_cell_space2_set_reserved_width (cs, size->x);
      if (cs->size.y < size->y)
        crank_cell_space2_extend_reserv_cols (cs, size->y);
    }
}





//////// Data Access ///////////////////////////////////////////////////////////

/**
 * crank_cell_space2_get:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @value: (out): Cell Value.
 *
 * Gets value on @wi, @hi.
 */
void
crank_cell_space2_get (const CrankCellSpace2 *cs,
                       const guint            wi,
                       const guint            hi,
                       GValue                *value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite (value, vcell);
}

/**
 * crank_cell_space2_set:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 * @value: Cell Value
 *
 * Sets value on @wi, @hi.
 */
void
crank_cell_space2_set (CrankCellSpace2 *cs,
                       const guint      wi,
                       const guint      hi,
                       const GValue    *value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite (vcell, value);
}

/**
 * crank_cell_space2_dup:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 *
 * Duplicates value structure on @wi, @hi.
 *
 * Returns: (nullable) (transfer full): A duplicated #GValue or %NULL if the
 *     cell is empty.
 */
GValue*
crank_cell_space2_dup (const CrankCellSpace2 *cs,
                       const guint            wi,
                       const guint            hi)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);

  return crank_value_dup (vcell);
}


/**
 * crank_cell_space2_peek:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 *
 * Gets value structure on cell, for both read and write.
 *
 * Returns: (transfer none): The #GValue on the cell.
 */
GValue*
crank_cell_space2_peek (CrankCellSpace2 *cs,
                        const guint      wi,
                        const guint      hi)
{
  return CELL_VALUE (cs, wi, hi);
}



/**
 * crank_cell_space2_peek_const:
 * @cs: A Cell Space.
 * @wi: Width-side index
 * @hi: Height-side index
 *
 * Same as crank_cell_space2_peek() but for read.
 *
 * Returns: (transfer none): The #GValue on the cell.
 */
const GValue*
crank_cell_space2_peek_const (const CrankCellSpace2 *cs,
                              const guint            wi,
                              const guint            hi)
{
  return CELL_VALUE (cs, wi, hi);
}


/**
 * crank_cell_space2_unset:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 *
 * Unsets value on @wi, @hi.
 *
 * Returns: Whether the cell contained value, and unsetted.
 */
gboolean
crank_cell_space2_unset (CrankCellSpace2 *cs,
                         const guint      wi,
                         const guint      hi)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  gboolean result = G_IS_VALUE(vcell);
  crank_value_unset (vcell);
  return result;
}


/**
 * crank_cell_space2_is_unset:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 *
 * Checks whether the cell does not contains any data and unsetted.
 *
 * Returns: Whether the cell is unset.
 */
gboolean
crank_cell_space2_is_unset (const CrankCellSpace2 *cs,
                            const guint            wi,
                            const guint            hi)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  return ! G_IS_VALUE (vcell);
}


/**
 * crank_cell_space2_type_of:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 *
 * Gets #GType that value setted for on the cell.
 *
 * Returns: #GType that the value is initialized.
 */
GType
crank_cell_space2_type_of (const CrankCellSpace2 *cs,
                           const guint            wi,
                           const guint            hi)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  return G_IS_VALUE (vcell) ? G_VALUE_TYPE (vcell) : G_TYPE_INVALID;
}


/**
 * crank_cell_space2_unset_all:
 * @cs: A Cell Space.
 *
 * Unset all of values.
 */
void
crank_cell_space2_unset_all (CrankCellSpace2 *cs)
{
  crank_cell_space2_unset_rows (cs, 0, cs->size.x, 0, cs->size.y);
}






//////// Typed Data Access /////////////////////////////////////////////////////

/**
 * crank_cell_space2_get_boolean:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @def: Failback default value.
 *
 * Gets boolean value on the cell.
 *
 * Returns: Boolean value, or @def if the cell does not contain boolean value.
 */
gboolean
crank_cell_space2_get_boolean (const CrankCellSpace2 *cs,
                               const guint            wi,
                               const guint            hi,
                               const gboolean         def)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);

  return G_VALUE_HOLDS_BOOLEAN (vcell) ? g_value_get_boolean (vcell) : def;
}

/**
 * crank_cell_space2_set_boolean:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @value: A Boolean value.
 *
 * Sets boolean value on the cell.
 */
void
crank_cell_space2_set_boolean (CrankCellSpace2 *cs,
                               const guint      wi,
                               const guint      hi,
                               const gboolean   value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_boolean (vcell, value);
}





/**
 * crank_cell_space2_get_uint:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @def: Failback default value.
 *
 * Gets uint value on the cell.
 *
 * Returns: Uint value, or @def if the cell does not contain uint value.
 */
guint
crank_cell_space2_get_uint (const CrankCellSpace2 *cs,
                            const guint            wi,
                            const guint            hi,
                            const guint            def)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);

  return G_VALUE_HOLDS_UINT (vcell) ? g_value_get_uint (vcell) : def;
}

/**
 * crank_cell_space2_set_uint:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @value: A uint value.
 *
 * Sets uint value on the cell.
 */
void
crank_cell_space2_set_uint (CrankCellSpace2 *cs,
                            const guint      wi,
                            const guint      hi,
                            const guint      value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_uint (vcell, value);
}



/**
 * crank_cell_space2_get_int:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @def: Failback default value.
 *
 * Gets int value on the cell.
 *
 * Returns: Int value, or @def if the cell does not contain int value.
 */
gint
crank_cell_space2_get_int (const CrankCellSpace2 *cs,
                           const guint            wi,
                           const guint            hi,
                           const gint             def)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);

  return G_VALUE_HOLDS_INT (vcell) ? g_value_get_int (vcell) : def;
}

/**
 * crank_cell_space2_set_int:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @value: A int value.
 *
 * Sets int value on the cell.
 */
void
crank_cell_space2_set_int (CrankCellSpace2 *cs,
                           const guint      wi,
                           const guint      hi,
                           const gint       value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_int (vcell, value);
}



/**
 * crank_cell_space2_get_float:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @def: Failback default value.
 *
 * Gets float value on the cell.
 *
 * Returns: Float value, or @def if the cell does not contain float value.
 */
gfloat
crank_cell_space2_get_float (const CrankCellSpace2 *cs,
                             const guint            wi,
                             const guint            hi,
                             const gfloat           def)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  return G_VALUE_HOLDS_FLOAT (vcell) ? g_value_get_float (vcell) : def;
}



/**
 * crank_cell_space2_set_float:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @value: A float value.
 *
 * Sets float value on the cell.
 */
void
crank_cell_space2_set_float (CrankCellSpace2 *cs,
                             const guint      wi,
                             const guint      hi,
                             const gfloat     value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_float (vcell, value);
}



/**
 * crank_cell_space2_get_pointer:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @type: (optional) (out): A optional type receiver.
 *
 * Gets pointer value on the cell. GType may be returned as a GType may derive
 * from a pointer type.
 *
 * Returns: (nullable) (transfer none): Pointer value, or %NULL if the cell does
 * not contain pointer value.
 */
gpointer
crank_cell_space2_get_pointer (const CrankCellSpace2 *cs,
                               const guint            wi,
                               const guint            hi,
                               GType                 *type)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  gboolean holds_value = G_VALUE_HOLDS_POINTER (vcell);

  if (type != NULL)
    *type = holds_value ? G_VALUE_TYPE (type) : G_TYPE_INVALID;

  return holds_value ? g_value_get_pointer (vcell) : NULL;
}



/**
 * crank_cell_space2_set_pointer:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @type: GType of pointer type.
 * @value: (transfer none): A float value.
 *
 * Sets pointer value on the cell. If @type is 0, G_TYPE_POINTER will be used.
 */
void
crank_cell_space2_set_pointer (CrankCellSpace2 *cs,
                               const guint      wi,
                               const guint      hi,
                               const GType      type,
                               const gpointer   value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_pointer (vcell, type, value);
}



/**
 * crank_cell_space2_get_boxed:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @type: (optional) (out): A optional type receiver.
 *
 * Gets boxed value on the cell. GType may be returned for type identification.
 *
 * Returns: (nullable) (transfer none): Boxed value, or %NULL if the cell does
 * not contain pointer value.
 */
gpointer
crank_cell_space2_get_boxed (const CrankCellSpace2 *cs,
                             const guint            wi,
                             const guint            hi,
                             GType                 *type)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  gboolean holds_value = G_VALUE_HOLDS_BOXED (vcell);

  if (type != NULL)
    *type = holds_value ? G_VALUE_TYPE (type) : G_TYPE_INVALID;

  return holds_value ? g_value_get_boxed (vcell) : NULL;
}



/**
 * crank_cell_space2_set_boxed:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @type: GType of pointer type.
 * @value: (transfer none): A boxed value.
 *
 * Sets (duplicated) boxed value on the cell.
 */
void
crank_cell_space2_set_boxed (CrankCellSpace2 *cs,
                             const guint      wi,
                             const guint      hi,
                             const GType      type,
                             const gpointer   value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_boxed (vcell, type, value);
}


/**
 * crank_cell_space2_dup_boxed:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @type: (optional) (out): A optional type receiver.
 *
 * Duplicates boxed value on the cell. #GType may be returned for type
 * identification.
 *
 * Returns: (nullable) (transfer full): Boxed value, or %NULL if the cell does not contain
 * pointer value. Free/unref with g_boxed_free() with #GType.
 */
gpointer
crank_cell_space2_dup_boxed (const CrankCellSpace2 *cs,
                             const guint            wi,
                             const guint            hi,
                             GType                 *type)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  gboolean holds_value = G_VALUE_HOLDS_BOXED (vcell);

  if (type != NULL)
    *type = holds_value ? G_VALUE_TYPE (type) : G_TYPE_INVALID;

  return holds_value ? g_value_dup_boxed (vcell) : NULL;
}



/**
 * crank_cell_space2_take_boxed:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @type: GType of pointer type.
 * @value: (transfer full): A boxed value.
 *
 * Take boxed value to the cell. The cell will take the owneership of @value.
 */
void
crank_cell_space2_take_boxed (CrankCellSpace2 *cs,
                             const guint      wi,
                             const guint      hi,
                             const GType      type,
                             const gpointer   value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_init (vcell, type);
  g_value_take_boxed (vcell, value);
}



/**
 * crank_cell_space2_get_object:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 *
 * Gets #GObject value on the cell.
 *
 * Returns: (nullable) (transfer none) (type GObject) : #GObject value, or %NULL
 * if the cell does not contain #GObject value.
 */
gpointer
crank_cell_space2_get_object (const CrankCellSpace2 *cs,
                               const guint            wi,
                               const guint            hi)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  gboolean holds_value = G_VALUE_HOLDS_OBJECT (vcell);

  return holds_value ? g_value_get_object (vcell) : NULL;
}



/**
 * crank_cell_space2_set_object:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @value: (transfer none) (type GObject): A object value.
 *
 * Sets #GObject value on the cell.
 */
void
crank_cell_space2_set_object (CrankCellSpace2 *cs,
                              const guint      wi,
                              const guint      hi,
                              const gpointer   value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_object (vcell, (GObject*) value);
}



/**
 * crank_cell_space2_dup_object:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 *
 * Gets #GObject value on the cell.
 *
 * Returns: (nullable) (transfer full) (type GObject) : #GObject value, or %NULL
 * if the cell does not contain #GObject value.
 */
gpointer
crank_cell_space2_dup_object (const CrankCellSpace2 *cs,
                              const guint            wi,
                              const guint            hi)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  gboolean holds_value = G_VALUE_HOLDS_OBJECT (vcell);

  return holds_value ? g_value_dup_object (vcell) : NULL;
}



/**
 * crank_cell_space2_take_object:
 * @cs: A Cell Space.
 * @wi: Width-side index.
 * @hi: Height-side index.
 * @value: (transfer full) (type GObject): A object value.
 *
 * Sets #GObject value on the cell. The cell will take ownership for @value.
 */
void
crank_cell_space2_take_object (CrankCellSpace2 *cs,
                               const guint      wi,
                               const guint      hi,
                               const gpointer   value)
{
  GValue *vcell = CELL_VALUE (cs, wi, hi);
  crank_value_overwrite_init (vcell, G_TYPE_OBJECT);
  g_value_take_object (vcell, (GObject*) value);
}
