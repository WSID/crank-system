#ifndef _CRANK_MAT_COMMON_HEADER
#define _CRANK_MAT_COMMON_HEADER

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
#error "crankmatcommon.h cannot be included directly."
#endif

typedef struct _CrankVecBool2 CrankVecBool2;
typedef struct _CrankVecBool3 CrankVecBool3;
typedef struct _CrankVecBool4 CrankVecBool4;
typedef struct _CrankVecBoolN CrankVecBoolN;

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
 * SECTION: crankmatcommon
 * @title: Common Macros for Matrix Type
 * @short_description: Common Macros for matrix types.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * In crank system, matrix types are defined in similar style for consistence.
 *
 * |[ <!- language="C" -->
 * typedef struct _SomeMatTypeN {
 *     Type*   data;
 *     guint   rn;
 *     guint   cn;
 * } SomeMatTypeN;
 * ]|
 *
 * This enables Crank System to factoring out specific operations as macros.
 */

//////// Allocator /////////////////////////////////////////////////////////////

/**
 * CRANK_MAT_ALLOC:
 * @m: Variable sized matrix item.
 * @G: Type of matrix type.
 * @_rn: Row count of matrix.
 * @_cn: Column count of matrix.
 *
 * Allocates variable size matrix's storage.
 */
#define CRANK_MAT_ALLOC(m,G,_rn,_cn)                                        \
  G_STMT_START {                                                          \
    (m)->data = g_new (G, _rn * _cn);                                   \
    (m)->rn = _rn;                                                      \
    (m)->cn = _cn;                                                      \
  } G_STMT_END

/**
 * CRANK_MAT_ALLOC0:
 * @m: Variable sized matrix item.
 * @G: Type of matrix type.
 * @_rn: Row count of matrix.
 * @_cn: Column count of matrix.
 *
 * Allocates variable size matrix's storage, with 0-initialized.
 */
#define CRANK_MAT_ALLOC0(m,G,_rn,_cn)                                       \
  G_STMT_START {                                                          \
    (m)->data = g_new0 (G, _rn * _cn);                                  \
    (m)->rn = _rn;                                                      \
    (m)->cn = _cn;                                                      \
  } G_STMT_END

//////// Getter and setter /////////////////////////////////////////////////////

/**
 * CRANK_MAT_GET:
 * @m: Variable sized matrix item.
 * @_ri: Row index to get.
 * @_ci: Col index to get.
 *
 * Gets a item at (@_ri, @_ci).
 *
 * Returns: an item at (@_ri, @_ci).
 */
#define CRANK_MAT_GET(m,_ri, \
                      _ci)    ((m)->data[CRANK_MAT_FLAT_INDEX(m, _ri, _ci)])

/**
 * CRANK_MAT_SET:
 * @m: Variable sized matrix item.
 * @_ri: Row index to get.
 * @_ci: Col index to get.
 * @_value: A Value to set.
 *
 * Sets an item at (@_ri, @_ci) as @_value.
 */
#define CRANK_MAT_SET(m,_ri,_ci,_value) \
  ((m)->data[CRANK_MAT_FLAT_INDEX(m, _ri, _ci)] = (_value))

/**
 * CRANK_MAT_GETP:
 * @m: Variable sized matrix item.
 * @_ri: Row index to get.
 * @_ci: Col index to get.
 *
 * Gets a pointer to item at (@_ri, @_ci).
 *
 * Returns: a pointer to an item at (@_ri, @_ci).
 */
#define CRANK_MAT_GETP(m,_ri,_ci)   \
  ((m)->data + CRANK_MAT_FLAT_INDEX (m, _ri, _ci))

/**
 * CRANK_MAT_GET_ROWP:
 * @m: Variable sized matrix item.
 * @_ri: Row index to get.
 *
 * Gets a pointer to row at @_ri.
 *
 * Returns: a pointer to a row at @_ri.
 */
#define CRANK_MAT_GET_ROWP(m,_ri)   \
  ((m)->data + CRANK_MAT_FLAT_ROW_INDEX (m, _ri))



//////// Miscellnous Macros ////////////////////////////////////////////////////

/**
 * CRANK_MAT_FLAT_INDEX:
 * @m: Variable sized matrix item.
 * @_ri: Row index.
 * @_ci: Column index.
 *
 * Gets flatten element index from 2-dimensional indices.
 *
 * Returns: Flatten index.
 */
#define CRANK_MAT_FLAT_INDEX(m,_ri, \
                             _ci) (CRANK_MAT_FLAT_ROW_INDEX(m,_ri) + (_ci))

/**
 * CRANK_MAT_FLAT_ROW_INDEX:
 * @m: Variable sized matrix item.
 * @_ri: Row index.
 *
 * Gets flatten element index of first item in given row.
 *
 * Returns: Flatten index of first element in the row.
 */
#define CRANK_MAT_FLAT_ROW_INDEX(m,_ri) ((m)->cn * (_ri))


//////// Warning macro /////////////////////////////////////////////////////////

/**
 * CRANK_MAT_WARN_IF_SIZE_MISMATCH2:
 * @t: (type gchar*): Type name that operation takes places of.
 * @op: (type gchar*): Operation name that checks size.
 * @a: Variable sized matrix item.
 * @b: Variable sized matrix item.
 *
 * Warns and return if two matrices has different size.
 */
#define CRANK_MAT_WARN_IF_SIZE_MISMATCH2(t,op,a,b)                          \
  G_STMT_START {                                                          \
    if (G_UNLIKELY(((a)->rn != (b)->rn) && ((a)->cn != (b)->cn))) {     \
        g_warning ("%s: %s: size mismatch: %ux%u, %ux%u",               \
                   t, op, (a)->rn, (a)->cn, (b)->rn, (b)->cn);      \
        return;                                                         \
      }                                                                   \
  } G_STMT_END


/**
 * CRANK_MAT_WARN_IF_SIZE_MISMATCH3:
 * @t: (type gchar*): Type name that operation takes places of.
 * @op: (type gchar*): Operation name that checks size.
 * @a: Variable sized matrix item.
 * @b: Variable sized matrix item.
 * @c: Variable sized matrix item.
 *
 * Warns and return if three matrices has different size.
 */
#define CRANK_MAT_WARN_IF_SIZE_MISMATCH3(t,op,a,b,c)                        \
  G_STMT_START {                                                          \
    if (G_UNLIKELY(((a)->rn != (b)->rn) && ((a)->cn != (b)->cn) &&      \
                   ((a)->rn != (c)->rn) && ((a)->cn != (c)->cn) )) {   \
        g_warning ("%s: %s: size mismatch: %ux%u, %ux%u, %ux%u",        \
                   t, op,                                              \
                   (a)->rn, (a)->cn,                                   \
                   (b)->rn, (b)->cn,                                   \
                   (c)->rn, (c)->cn);                              \
        return;                                                         \
      }                                                                   \
  } G_STMT_END


/**
 * CRANK_MAT_WARN_IF_NON_SQUARE:
 * @t: (type gchar*): Type name that operation takes places of.
 * @op: (type gchar*): Operation name that checks size.
 * @a: Variable sized matrix item.
 *
 * Warns and return if the matrix is not square.
 */
#define CRANK_MAT_WARN_IF_NON_SQUARE(t,op,a)                            \
  G_STMT_START {                                                          \
    if (G_UNLIKELY((a)->rn != (a)->cn)) {       \
        g_warning ("%s: %s: non square: %ux%u",             \
                   t, op, (a)->rn, (a)->cn);       \
        return;                                                         \
      }                                                                   \
  } G_STMT_END

/**
 * CRANK_MAT_WARN_IF_NON_SQUARE_RET:
 * @t: (type gchar*): Type name that operation takes places of.
 * @op: (type gchar*): Operation name that checks size.
 * @a: Variable sized matrix item.
 * @r: Return value
 *
 * Warns and return if the matrix is not square.
 */
#define CRANK_MAT_WARN_IF_NON_SQUARE_RET(t,op,a,r)                          \
  G_STMT_START {                                                          \
    if (G_UNLIKELY((a)->rn != (a)->cn)) {       \
        g_warning ("%s: %s: non square: %ux%u",             \
                   t, op, (a)->rn, (a)->cn);       \
        return (r);                                                         \
      }                                                                   \
  } G_STMT_END

#endif