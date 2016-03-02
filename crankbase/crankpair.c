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
#include "crankpair.h"

/**
 * SECTION: crankpair
 * @title: Pairs
 * @short_description: Pair types.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Type described here is pair structure types.
 */

//////// Type definition /////////////////////////////////////

G_DEFINE_BOXED_TYPE (CrankPairUint,
                     crank_pair_uint,
                     crank_pair_uint_dup,
                     g_free)

G_DEFINE_BOXED_TYPE (CrankPairPointer,
                     crank_pair_pointer,
                     crank_pair_pointer_dup,
                     g_free)

G_DEFINE_BOXED_TYPE (CrankPairObject,
                     crank_pair_object,
                     crank_pair_object_dup,
                     g_free)

//////// Public functions ///////////////////////////////////

/**
 * crank_pair_uint_init:
 * @pair: (out): A Pair.
 * @a: A element.
 * @b: A element.
 *
 * Initialize a pair with member.
 */
void
crank_pair_uint_init (CrankPairUint *pair,
                      const guint    a,
                      const guint    b)
{
  pair->a = a;
  pair->b = b;
}

/**
 * crank_pair_uint_init_array:
 * @pair: (out): A Pair.
 * @array: (array fixed-size=2): Array of elements
 *
 * Initialize a pair with array.
 */
void
crank_pair_uint_init_array (CrankPairUint *pair,
                            const guint   *array)
{
  pair->a = array[0];
  pair->b = array[1];
}

/**
 * crank_pair_uint_copy:
 * @pair: A Pair.
 * @other: (out): A Pair same as @pair.
 *
 * Copy a @pair to @other.
 */
void
crank_pair_uint_copy (const CrankPairUint *pair,
                      CrankPairUint       *other)
{
  other->a = pair->a;
  other->b = pair->b;
}

/**
 * crank_pair_uint_dup:
 * @pair: A Pair.
 *
 * Duplicates a @pair on heap.
 *
 * Returns: (transfer full): A Pair same as @pair.
 */
CrankPairUint*
crank_pair_uint_dup (const CrankPairUint *pair)
{
  CrankPairUint *result = g_new (CrankPairUint, 1);

  crank_pair_uint_copy (pair, result);

  return result;
}


/**
 * crank_pair_uint_hash:
 * @key: (type CrankPairUint): A Pair.
 *
 * Gets hash value of pair.
 *
 * Returns: Hash value of pair, by its element values.
 */
guint
crank_pair_uint_hash (gconstpointer key)
{
  const CrankPairUint *pair = key;

  if (key == 0)
    return 0;

  return g_int_hash (& pair->a) * 37 +
         g_int_hash (& pair->b);
}

/**
 * crank_pair_uint_equal:
 * @a: (type CrankPairUint): A Pair.
 * @b: (type CrankPairUint): A Pair.
 *
 * Checks whether two pairs are equal.
 *
 * Returns: Whether two pairs are equal.
 */
gboolean
crank_pair_uint_equal (gconstpointer a,
                       gconstpointer b)
{
  const CrankPairUint *pa = a;
  const CrankPairUint *pb = b;

  if (a == b)
    return TRUE;

  if ((a == NULL) || (b == NULL))
    return FALSE;

  return (pa->a == pb->a) && (pa->b == pb->b);
}


/**
 * crank_pair_uint_swap:
 * @a: A Pair.
 * @r: (out): A Pair with swapped members.
 *
 * Swap elements in a pair.
 */
void
crank_pair_uint_swap (const CrankPairUint *a,
                      CrankPairUint       *r)
{
  r->b = a->a;
  r->a = a->b;
}

/**
 * crank_pair_uint_swap_self:
 * @a: A Pair.
 *
 * Swap elements in a pair.
 */
void
crank_pair_uint_swap_self (CrankPairUint *a)
{
  guint temp = a->a;
  a->a = a->b;
  a->b = temp;
}



/**
 * crank_pair_pointer_init:
 * @pair: (out): A Pair.
 * @a: (transfer none): A Pointer.
 * @b: (transfer none): A Pointer.
 *
 * Initialize a pointer pair.
 */
void
crank_pair_pointer_init (CrankPairPointer *pair,
                         gpointer          a,
                         gpointer          b)
{
  pair->a = a;
  pair->b = b;
}

/**
 * crank_pair_pointer_init_array: (skip)
 * @pair: (out): A Pair.
 * @array: (array fixed-size=2) (transfer none): Pointer array.
 *
 * Initialize a pointer pair from pointer array.
 */
void
crank_pair_pointer_init_array (CrankPairPointer *pair,
                               gpointer         *array)
{
  pair->a = array[0];
  pair->b = array[1];
}

/**
 * crank_pair_pointer_copy:
 * @pair: A Pair.
 * @other: (out): Another pair.
 *
 * Copies a pointer pair.
 */
void
crank_pair_pointer_copy (const CrankPairPointer *pair,
                         CrankPairPointer       *other)
{
  other->a = pair->a;
  other->b = pair->b;
}

/**
 * crank_pair_pointer_dup:
 * @pair: A Pair.
 *
 * Duplicates a pointer pair on the heap.
 *
 * Returns: (transfer full): A Pair.
 */
CrankPairPointer*
crank_pair_pointer_dup (const CrankPairPointer *pair)
{
  CrankPairPointer *res = g_new (CrankPairPointer, 1);
  crank_pair_pointer_copy (pair, res);
  return res;
}


/**
 * crank_pair_pointer_hash:
 * @key: (type CrankPairPointer): A Pair.
 *
 * Gets hash value of pair. g_direct_hash() will be used for element.
 *
 * Returns: Hash value of pair, by its element values.
 */
guint
crank_pair_pointer_hash (gconstpointer key)
{
  const CrankPairPointer *pair = key;

  if (key == 0)
    return 0;

  return g_direct_hash (pair->a) * 37 +
         g_direct_hash (pair->b);
}

/**
 * crank_pair_pointer_equal:
 * @a: (type CrankPairPointer): A Pair.
 * @b: (type CrankPairPointer): A Pair.
 *
 * Checks whether two pairs are equal. Elements are compared directly.
 *
 * Returns: Whether two pairs are equal.
 */
gboolean
crank_pair_pointer_equal (gconstpointer a,
                          gconstpointer b)
{
  const CrankPairPointer *pa = a;
  const CrankPairPointer *pb = b;

  if (a == b)
    return TRUE;

  if ((a == NULL) || (b == NULL))
    return FALSE;

  return (pa->a == pb->a) && (pa->b == pb->b);
}


/**
 * crank_pair_pointer_swap:
 * @a: A Pair.
 * @r: (out): Another Pair.
 *
 * Initialize another pair with swapped order.
 */
void
crank_pair_pointer_swap (const CrankPairPointer *a,
                         CrankPairPointer       *r)
{
  r->a = a->b;
  r->b = a->a;
}

/**
 * crank_pair_pointer_swap_self:
 * @a: A Pair.
 *
 * Swaps two element in the pair.
 */
void
crank_pair_pointer_swap_self (CrankPairPointer *a)
{
  gpointer temp = a->a;
  a->a = a->b;
  a->b = temp;
}


/**
 * crank_pair_pointer_foreach:
 * @pair: A Pair.
 * @func: (scope call): A Function.
 * @userdata: (closure func): A Userdata.
 *
 * Calls @func for each element.
 */
void
crank_pair_pointer_foreach (CrankPairPointer *pair,
                            GFunc             func,
                            gpointer          userdata)
{
  func (pair->a, userdata);
  func (pair->b, userdata);
}













/**
 * crank_pair_object_init:
 * @pair: (out): A Pair.
 * @a: A Object.
 * @b: An Object.
 *
 * Initialize a object pair.
 */
void
crank_pair_object_init (CrankPairObject *pair,
                        GObject         *a,
                        GObject         *b)
{
  pair->a = a;
  pair->b = b;
}

/**
 * crank_pair_object_init_array:
 * @pair: (out): A Pair.
 * @array: (array fixed-size=2): An array of objects.
 *
 * Initialize a object pair from an array.
 */
void
crank_pair_object_init_array  (CrankPairObject  *pair,
                               GObject         **array)
{
  pair->a = array[0];
  pair->b = array[1];
}


/**
 * crank_pair_object_copy:
 * @pair: A Pair.
 * @other: (out): A Pair with same objects.
 *
 * Shallow copys a object pair.
 */
void
crank_pair_object_copy (const CrankPairObject *pair,
                        CrankPairObject       *other)
{
  other->a = pair->a;
  other->b = pair->b;
}

/**
 * crank_pair_object_dup:
 * @pair: A Pair.
 *
 * Shallow duplicates an object pair.
 *
 * Returns: (transfer full): Duplicated pair.
 */
CrankPairObject*
crank_pair_object_dup (const CrankPairObject *pair)
{
  CrankPairObject *result = g_new (CrankPairObject, 1);
  result->a = pair->a;
  result->b = pair->b;

  return result;
}


/**
 * crank_pair_object_copy_ref:
 * @pair: A Pair.
 * @other: (out): A Pair.
 *
 * Deep copys an object pair. Reference counts of each elements are increased.
 */
void
crank_pair_object_copy_ref (const CrankPairObject *pair,
                            CrankPairObject       *other)
{
  other->a = g_object_ref (pair->a);
  other->b = g_object_ref (pair->b);
}


/**
 * crank_pair_object_dup_ref:
 * @pair: A Pair.
 *
 * Deep duplicates an object pair. Reference counts of each elements are
 * increased.
 *
 * Returns: (transfer full): Duplicated pair.
 */
CrankPairObject*
crank_pair_object_dup_ref (const CrankPairObject *pair)
{
  CrankPairObject *result = g_new (CrankPairObject, 1);
  result->a = g_object_ref (pair->a);
  result->b = g_object_ref (pair->b);
  return result;
}


/**
 * crank_pair_object_free_unref:
 * @pair: (type CrankPairObject): A Pair.
 *
 * Decreases reference counts of elements, as well as freeing @pair itself.
 *
 * This is useful when freeing pairs duplicated by crank_pair_object_dup_ref().
 */
void
crank_pair_object_free_unref  (gpointer pair)
{
  CrankPairObject *p = pair;

  g_object_unref (p->a);
  g_object_unref (p->b);

  g_free (p);
}


/**
 * crank_pair_object_element_ref:
 * @pair: A Pair.
 *
 * Increase reference counts of elements.
 *
 * Returns: (transfer none): @pair.
 */
CrankPairObject*
crank_pair_object_element_ref (CrankPairObject       *pair)
{
  g_object_ref (pair->a);
  g_object_ref (pair->b);

  return pair;
}

/**
 * crank_pair_object_element_unref:
 * @pair: A Pair.
 *
 * Decrease reference counts of elements.
 */
void
crank_pair_object_element_unref(CrankPairObject      *pair)
{
  g_object_unref (pair->a);
  g_object_unref (pair->b);
}

/**
 * crank_pair_object_hash:
 * @key: (type CrankPairObject): A Pair.
 *
 * Gets hash value of the pair. g_direct_hash() will be used for getting hash
 * value of each elements.
 *
 * Returns: Hash value of a pair.
 */
guint
crank_pair_object_hash (gconstpointer key)
{
  const CrankPairObject *pair = key;

  if (pair == NULL)
    return 0;

  return g_direct_hash (pair->a) * 37 +
         g_direct_hash (pair->b);
}


/**
 * crank_pair_object_equal:
 * @a: (type CrankPairObject): A Pair.
 * @b: (type CrankPairObject): A Pair.
 *
 * Checks both pairs are equal.
 *
 * Returns: Whether the both objects are equal.
 */
gboolean
crank_pair_object_equal (gconstpointer a,
                         gconstpointer b)
{
  const CrankPairObject *pa = a;
  const CrankPairObject *pb = b;

  if (a == b)
    return TRUE;

  if ((a == NULL) || (b == NULL))
    return FALSE;

  return (pa->a == pb->a) && (pa->b == pb->b);
}


/**
 * crank_pair_object_swap:
 * @a: A Pair.
 * @r: (out): A Pair.
 *
 * Initialzie a swapped pair.
 */
void
crank_pair_object_swap (const CrankPairObject *a,
                        CrankPairObject       *r)
{
  r->a = a->b;
  r->b = a->a;
}


/**
 * crank_pair_object_swap_self:
 * @a: A Pair.
 *
 * Swaps elements in the pair.
 */
void
crank_pair_object_swap_self (CrankPairObject       *a)
{
  GObject *temp = a->a;
  a->a = a->b;
  a->b = temp;
}


/**
 * crank_pair_object_foreach:
 * @pair: A Pair.
 * @func: (scope call): A Function.
 * @userdata: (closure func): Userdata for @func.
 *
 * Calls @func on both of elements.
 */
void
crank_pair_object_foreach (CrankPairObject *pair,
                           GFunc            func,
                           gpointer         userdata)
{
  func (pair->a, userdata);
  func (pair->b, userdata);
}
