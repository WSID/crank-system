#ifndef _CRANK_VEC_COMMON_HEADER
#define _CRANK_VEC_COMMON_HEADER

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
#error "crankveccommon.h cannot be included directly."
#endif

typedef struct _CrankVecBool2 CrankVecBool2;
typedef struct _CrankVecBool3 CrankVecBool3;
typedef struct _CrankVecBool4 CrankVecBool4;
typedef struct _CrankVecBoolN CrankVecBoolN;

typedef struct _CrankVecUint2 CrankVecUint2;
typedef struct _CrankVecUint3 CrankVecUint3;
typedef struct _CrankVecUint4 CrankVecUint4;
typedef struct _CrankVecUintN CrankVecUintN;

typedef struct _CrankVecInt2 CrankVecInt2;
typedef struct _CrankVecInt3 CrankVecInt3;
typedef struct _CrankVecInt4 CrankVecInt4;
typedef struct _CrankVecIntN CrankVecIntN;

typedef struct _CrankVecFloat2 CrankVecFloat2;
typedef struct _CrankVecFloat3 CrankVecFloat3;
typedef struct _CrankVecFloat4 CrankVecFloat4;
typedef struct _CrankVecFloatN CrankVecFloatN;

typedef struct _CrankVecCplxFloatN CrankVecCplxFloatN;

typedef struct _CrankMatFloat2 CrankMatFloat2;
typedef struct _CrankMatFloat3 CrankMatFloat3;
typedef struct _CrankMatFloat4 CrankMatFloat4;
typedef struct _CrankMatFloatN CrankMatFloatN;

typedef struct _CrankMatCplxFloatN CrankMatCplxFloatN;

/**
 * SECTION: crankveccommon
 * @title: Common Macros for Vector Type
 * @short_description: Common Macros for vector types.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * In crank system, vectorized types are defined in similar style for consistence.
 *
 * |[ <!- language="C" -->
 * typedef struct _SomeVecTypeN {
 *     Type*   data;
 *     guint   n;
 * } SomeVecTypeN;
 * ]|
 *
 * This enables Crank System to factoring out specific operations as macros.
 */

//////// Allocator /////////////////////////////////////////////////////////////

/**
 * CRANK_VEC_ALLOC:
 * @v: Variable sized vector item.
 * @G: Type of vector type.
 * @_n: Size of vector.
 *
 * Allocates variable size vector's storage.
 */
#define CRANK_VEC_ALLOC(v,G,_n)                                             \
  G_STMT_START {                                                          \
    (v)->data = g_new (G, _n);                                          \
    (v)->n = _n;                                                        \
  } G_STMT_END

/**
 * CRANK_VEC_ALLOC0:
 * @v: Variable sized vector item.
 * @G: Type of vector type.
 * @_n: Size of vector.
 *
 * Allocates variable size vector's storage, with 0-initialized.
 */
#define CRANK_VEC_ALLOC0(v,G,_n)                                                \
  G_STMT_START {                                                          \
    (v)->data = g_new0 (G, _n);                                         \
    (v)->n = _n;                                                        \
  } G_STMT_END

//////// Getter and setter /////////////////////////////////////////////////////

/**
 * CRANK_VEC_GET:
 * @v: Variable sized vector item.
 * @_i: Index to get.
 *
 * Gets a item at @_i.
 *
 * Returns: an item at @_i
 */
#define CRANK_VEC_GET(v,_i) ((v)->data[(_i)])

/**
 * CRANK_VEC_SET:
 * @v: Variable sized vector item.
 * @_i: Index to get.
 * @_value: A Value to set.
 *
 * Sets an item at @_i as @_value.
 */
#define CRANK_VEC_SET(v,_i,_value)  ((v)->data[(_i)] = (_value))

/**
 * CRANK_VEC_GETP:
 * @v: Variable sized vector item.
 * @_i: Index to get.
 *
 * Gets a pointer to item at @_i.
 *
 * Returns: a pointer to an item at @_i
 */
#define CRANK_VEC_GETP(v,_i)    ((v)->data + (_i))



//////// Warning macro /////////////////////////////////////////////////////////
/**
 * CRANK_VEC_WARN_IF_SIZE_MISMATCH2:
 * @t: (type gchar*): Type name that operation takes places of.
 * @op: (type gchar*): Operation name that checks size.
 * @a: Variable sized vector item.
 * @b: Variable sized vector item.
 *
 * Warns and return if two given vector has different size.
 */
#define CRANK_VEC_WARN_IF_SIZE_MISMATCH2(t,op,a,b)                          \
  G_STMT_START {                                                          \
    if (G_UNLIKELY((a)->n != (b)->n)) {                                 \
        g_warning ("%s: %s: size mismatch: %u, %u", t, op, a->n, b->n); \
        return;                                                         \
      }                                                                   \
  } G_STMT_END

/**
 * CRANK_VEC_WARN_IF_SIZE_MISMATCH2_RET:
 * @t: (type gchar*): Type name that operation takes places of.
 * @op: (type gchar*): Operation name that checks size.
 * @a: Variable sized vector item.
 * @b: Variable sized vector item.
 * @r: Return values.
 *
 * Warns and return if two given vector has different size.
 */
#define CRANK_VEC_WARN_IF_SIZE_MISMATCH2_RET(t,op,a,b,r)                    \
  G_STMT_START {                                                          \
    if (G_UNLIKELY((a)->n != (b)->n)) {                                 \
        g_warning ("%s: %s: size mismatch: %u, %u", t, op, a->n, b->n); \
        return (r);                                                     \
      }                                                                   \
  } G_STMT_END

/**
 * CRANK_VEC_WARN_IF_SIZE_MISMATCH3:
 * @t: (type gchar*): Type name that operation takes places of.
 * @op: (type gchar*): Operation name that checks size.
 * @a: Variable sized vector item.
 * @b: Variable sized vector item.
 * @c: Variable sized vector item.
 *
 * Warns and return if three given vector has different size.
 */
#define CRANK_VEC_WARN_IF_SIZE_MISMATCH3(t,op,a,b,c)                        \
  G_STMT_START {                                                          \
    if (G_UNLIKELY(((a)->n != (b)->n) && ((a)->n != (c)->n))) {         \
        g_warning ("%s: %s: size mismatch: %u, %u, %u",                 \
                   t, op, (a)->n, (b)->n, (c)->n);                  \
        return;                                                         \
      }                                                                   \
  } G_STMT_END

/**
 * CRANK_VEC_WARN_IF_SIZE_MISMATCH3_RET:
 * @t: (type gchar*): Type name that operation takes places of.
 * @op: (type gchar*): Operation name that checks size.
 * @a: Variable sized vector item.
 * @b: Variable sized vector item.
 * @c: Variable sized vector item.
 * @r: Return values.
 *
 * Warns and return if three given vector has different size.
 */
#define CRANK_VEC_WARN_IF_SIZE_MISMATCH3_RET(t,op,a,b,c,r)                  \
  G_STMT_START {                                                          \
    if (G_UNLIKELY(((a)->n != (b)->n) && ((a)->n != (c)->n))) {         \
        g_warning ("%s: %s: size mismatch: %u, %u, %u",                 \
                   t, op, (a)->n, (b)->n, (c)->n);                  \
        return (r);                                                     \
      }                                                                   \
  } G_STMT_END

#endif
