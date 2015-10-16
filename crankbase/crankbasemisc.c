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

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankbasemisc.h"

/**
 * crank_qarray_to_strv: (skip):
 * @qarray: (array length=nqarray): A GQuark array.
 * @nqarray: Length of @qarray.
 *
 * Constructs string array from #GQuark array.
 *
 * Each elements in same position are associated to each other.
 *
 * Returns: (array zero-terminated) (transfer container): A string array.
 */
const gchar**
crank_qarray_to_strv (GQuark      *qarray,
                      const guint  nqarray)
{
  const gchar **strv;
  guint   i;

  strv = g_new (const gchar*, nqarray + 1);

  for (i = 0; i < nqarray; i++)
    strv[i] = g_quark_to_string (qarray[i]);

  strv[nqarray] = NULL;
  return strv;
}
/**
 * crank_qarray_try_strv: (skip):
 * @strv: (array zero-terminated): A string array.
 * @nqarray: (out): Length of returned value.
 *
 * Constructs #GQuark array from string array. If string element has no #GQuark
 * association, 0 will placed for that position.
 *
 * Each elements in same position are associated to each other.
 *
 * Returns: (array length=nqarray) (transfer container): A #GQuark array.
 */
GQuark*
crank_qarray_try_strv (const gchar **strv,
                       guint        *nqarray)
{
  GQuark *qarray;
  guint   n;
  guint   i;

  n = g_strv_length ((gchar**)strv);
  qarray = g_new (GQuark, n);

  for (i = 0; i < n; i++)
    qarray[i] = g_quark_try_string (strv[i]);

  *nqarray = n;
  return qarray;
}

/**
 * crank_qarray_from_strv: (skip):
 * @strv: (array zero-terminated): A string array.
 * @nqarray: (out): Length of returned value.
 *
 * Constructs #GQuark array from string array. If string element has no #GQuark
 * association, new #GQuark value will be associated for that string.
 *
 * Each elements in same position are associated to each other.
 *
 * Returns: (array length=nqarray) (transfer container): A #GQuark array.
 */
GQuark*
crank_qarray_from_strv (const gchar **strv,
                        guint        *nqarray)
{
  GQuark *qarray;
  guint   n;
  guint   i;

  n = g_strv_length ((gchar**)strv);
  qarray = g_new (GQuark, n);

  for (i = 0; i < n; i++)
    qarray[i] = g_quark_from_string (strv[i]);

  *nqarray = n;
  return qarray;
}


/**
 * crank_table_dup: (skip)
 * @table: A Hash table to copy.
 * @keyhash: A hash function given for @table.
 * @keyequal: A Equal function given for @table.
 *
 * Duplicate hash table, instead of increasing reference count.
 *
 * This is shallow copy for both of keys and values. For deep copy, use
 * crank_table_dup_full().
 *
 * Returns: (transfer container): A duplicated hash table.
 */
GHashTable*
crank_table_dup (GHashTable     *table,
                 GHashFunc       keyhash,
                 GEqualFunc      keyequal)
{
  return crank_table_dup_full (table, keyhash, keyequal, NULL, NULL, NULL, NULL);
}

/**
 * crank_table_dup_full: (skip)
 * @table: A Hash table to copy.
 * @keyhash: A hash function given for @table.
 * @keyequal: A Equal function given for @table.
 * @keycopy: (nullable): A copy function for keys or %NULL, to not copy keys.
 * @keydestroy: (nullable): A destroy function for keys.
 * @valuecopy: (nullable): A copy function for values or %NULL, to not copy keys.
 * @valuedestroy: (nullable): A destroy function for values.
 *
 * Duplicate hash table, instead of increasing reference count.
 *
 * Returns: (transfer full): A duplicated hash table.
 */
GHashTable*
crank_table_dup_full (GHashTable     *table,
                      GHashFunc       keyhash,
                      GEqualFunc      keyequal,
                      GBoxedCopyFunc  keycopy,
                      GDestroyNotify  keydestroy,
                      GBoxedCopyFunc  valuecopy,
                      GDestroyNotify  valuedestroy)
{
  GHashTable *dup;

  GHashTableIter i;
  gpointer ik, iv;

  dup = g_hash_table_new_full (keyhash, keyequal, keydestroy, valuedestroy);

  g_hash_table_iter_init (&i, table);
  while (g_hash_table_iter_next (&i, &ik, &iv))
    {
      gpointer nik, niv;

      nik = (keycopy != NULL) ? keycopy (ik) : ik;
      niv = (valuecopy != NULL) ? valuecopy (iv) : iv;

      g_hash_table_insert (dup, nik, niv);
    }

  return dup;
}


/**
 * crank_table_overlay: (skip)
 * @table: A hash table.
 * @overlay: A overlaying table.
 *
 * Overlays @overlay over @table. As a result, @table will have all keys in
 * @overlay, and get replaced all values to @overlay's one for common keys.
 *
 * This performs shallow copy. If @table has destroy functions for keys or
 * values, use crank_table_overlay_full().
 */
void
crank_table_overlay (GHashTable *table,
                     GHashTable *overlay)
{
  crank_table_overlay_full (table, overlay, NULL, NULL);
}


/**
 * crank_table_overlay_full: (skip)
 * @table: A hash table.
 * @overlay: A overlaying table.
 * @keycopy: (nullable): A copy function for key or %NULL, to not copy keys.
 * @valuecopy: (nullable): A copy function for key or %NULL, to not copy values.
 *
 * Overlays @overlay over @table. As a result, @table will have all keys in
 * @overlay, and get replaced all values to @overlay's one for common keys.
 *
 * This performs shallow copy. If @table has destroy functions for keys or
 * values, use crank_table_overlay_full().
 */
void
crank_table_overlay_full (GHashTable     *table,
                          GHashTable     *overlay,
                          GBoxedCopyFunc  keycopy,
                          GBoxedCopyFunc  valuecopy)
{
  GHashTableIter i;
  gpointer ik, iv;

  g_hash_table_iter_init (&i, overlay);
  while (g_hash_table_iter_next (&i, &ik, &iv))
    {
      gpointer nik, niv;

      nik = (keycopy != NULL) ? keycopy (ik) : ik;
      niv = (valuecopy != NULL) ? valuecopy (iv) : iv;

      g_hash_table_insert (table, nik, niv);
    }
}


/**
 * crank_set_dup: (skip)
 * @set: A set.
 * @hash: A hash function
 * @equal: A Equal function.
 *
 * Duplicate a set.
 *
 * This is shallow copy. For deep copy, use crank_set_dup_full().
 *
 * Returns: A duplicated set.
 */
GHashTable*
crank_set_dup (GHashTable *set,
               GHashFunc   hash,
               GEqualFunc  equal)
{
  return crank_set_dup_full (set, hash, equal, NULL, NULL);
}

/**
 * crank_set_dup_full: (skip)
 * @set: A set.
 * @hash: A hash function
 * @equal: A Equal function.
 * @copy: (nullable): A copy function to copy elements, or %NULL to not copy.
 * @destroy: (nullable): A destroy function.
 *
 * Duplicate a set.
 *
 * Returns: A duplicated set.
 */
GHashTable*
crank_set_dup_full (GHashTable     *set,
                    GHashFunc       hash,
                    GEqualFunc      equal,
                    GBoxedCopyFunc  copy,
                    GDestroyNotify  destroy)
{
  GHashTable *dup;

  GHashTableIter i;
  gpointer ik;

  dup = g_hash_table_new_full (hash, equal, destroy, NULL);

  g_hash_table_iter_init (&i, set);
  while (g_hash_table_iter_next (&i, &ik, NULL))
    {
      gpointer nik = (copy != NULL) ? copy (ik) : ik;
      g_hash_table_add (dup, nik);
    }

  return dup;
}

/**
 * crank_set_overlay: (skip)
 * @set: A set.
 * @overlay: A overlay.
 *
 * Overlay @overlay over @set. As a result, @set will have all of elements in
 * @overlay.
 *
 * This is shallow copy. If @set has destroy function, use
 * crank_set_overlay_full().
 */
void
crank_set_overlay (GHashTable *set,
                   GHashTable *overlay)
{
  crank_set_overlay_full (set, overlay, NULL);
}

/**
 * crank_set_overlay_full: (skip)
 * @set: A set.
 * @overlay: A overlay.
 * @copy: (nullable): Copy function to copy elements or %NULL, not to copy.
 *
 * Overlay @overlay over @set. As a result, @set will have all of elements in
 * @overlay.
 */
void
crank_set_overlay_full (GHashTable     *set,
                        GHashTable     *overlay,
                        GBoxedCopyFunc  copy)
{
  GHashTableIter i;
  gpointer ik;

  if (overlay == NULL)
    return;

  g_hash_table_iter_init (&i, overlay);
  while (g_hash_table_iter_next (&i, &ik, NULL))
    {
      gpointer nik = (copy != NULL) ? copy (ik) : ik;
      g_hash_table_add (set, nik);
    }
}

/**
 * crank_set_map: (skip)
 * @set: A set.
 * @hash: A hash function for new set.
 * @equal: A equal function for new set.
 * @map: A map function. Should return unowned pointers.
 * @userdata: (closure): userdata for @map.
 *
 * Map @set to create new set.
 *
 * This is shallow copy. If @map returns owned pointers, or deep copy is
 * required, use crank_set_map_full().
 *
 * Returns: (transfer container): Mapped @set.
 */
GHashTable*
crank_set_map (GHashTable      *set,
               GHashFunc        hash,
               GEqualFunc       equal,
               CrankPtrPtrFunc  map,
               gpointer         userdata)
{
  return crank_set_map_full (set, hash, equal, NULL, NULL, map, userdata);
}


/**
 * crank_set_map_full: (skip)
 * @set: A set.
 * @hash: A hash function for new set.
 * @equal: A equal function for new set.
 * @copy: (nullable): A copy function for elements.
 * @destroy: (nullable): A destroy function for elements.
 * @map: A map function. Should return unowned pointers.
 * @userdata: (closure): userdata for @map.
 *
 * Map @set to create new set.
 *
 * For ownership of elements, there are 3 cases.
 *
 * 1. Unowned values.
 *    @copy is %NULL, and @map returns unowned value. @destroy may be %NULL.
 *
 * 2. Copy unowned values.
 *    @map returns unowned value, and value copied through @copy. @destroy frees
 *    value from @copy.
 *
 * 3. accept owned values.
 *    @map returns owned value, and @copy is %NULL. @destroy frees value from
 *    @map.
 *
 * Any case out of them, will lead to memory leakage or double free.
 *
 * Returns: (transfer container): Mapped @set.
 */
GHashTable*
crank_set_map_full (GHashTable      *set,
                    GHashFunc        hash,
                    GEqualFunc       equal,
                    GBoxedCopyFunc   copy,
                    GDestroyNotify   destroy,
                    CrankPtrPtrFunc  map,
                    gpointer         userdata)
{
  GHashTable *nset;

  GHashTableIter i;
  gpointer ik;

  nset = g_hash_table_new_full (hash, equal, destroy, NULL);

  g_hash_table_iter_init (&i, set);
  while (g_hash_table_iter_next (&i, &ik, NULL))
    {
      gpointer nik = map (ik, userdata);
      nik = (copy != NULL) ? copy (nik) : nik;

      g_hash_table_add (nset, nik);
    }

  return nset;
}
