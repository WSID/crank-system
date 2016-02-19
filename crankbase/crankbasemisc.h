#ifndef CRANKBASEMISC_H
#define CRANKBASEMISC_H

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

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"


G_BEGIN_DECLS

//////// GQuark manipulation

/**
 * CRANK_QUARK_TO_STRING:
 * @p: (transfer none): A #GQuark casted into #gpointer.
 *
 * Gets string associated to a quark casted in pointer. This is useful when
 * using #GQuark with container types.
 *
 * Returns: (transfer none): A string.
 */
#define CRANK_QUARK_TO_STRING(p) g_quark_to_string(GPOINTER_TO_INT(p))

/**
 * CRANK_QUARK_TRY_STRING:
 * @s: A string to try get #GQuark
 *
 * Gets #GQuark associated to the string. This is useful when using #GQuark with
 * container types.
 *
 * Returns: (transfer none): A #GQuark, casted into #gpointer
 */
#define CRANK_QUARK_TRY_STRING(s) GINT_TO_POINTER(g_quark_try_string(s))

/**
 * CRANK_QUARK_FROM_STRING:
 * @s: A string to try get #GQuark
 *
 * Gets #GQuark associated to the string. This is useful when using #GQuark with
 * container types.
 *
 * Returns: (transfer none): A #GQuark, casted into #gpointer
 */
#define CRANK_QUARK_FROM_STRING(s) GINT_TO_POINTER(g_quark_from_string(s))




const gchar   **crank_qarray_to_strv    (GQuark         *qarray,
                                         const guint     nqarray);

GQuark         *crank_qarray_try_strv   (const gchar   **strv,
                                         guint          *nqarray);

GQuark         *crank_qarray_from_strv  (const gchar   **strv,
                                         guint          *nqarray);

//////// Table manipulation (GHashTable <K, V>)

GHashTable     *crank_table_dup         (GHashTable     *table,
                                         GHashFunc       keyhash,
                                         GEqualFunc      keyequal);

GHashTable     *crank_table_dup_full    (GHashTable     *table,
                                         GHashFunc       keyhash,
                                         GEqualFunc      keyequal,
                                         GBoxedCopyFunc  keycopy,
                                         GDestroyNotify  keydestroy,
                                         GBoxedCopyFunc  valuecopy,
                                         GDestroyNotify  valuedestroy);

void            crank_table_overlay     (GHashTable *table,
                                         GHashTable *overlay);

void            crank_table_overlay_full(GHashTable     *table,
                                         GHashTable     *overlay,
                                         GBoxedCopyFunc  keycopy,
                                         GBoxedCopyFunc  valuecopy);

//////// Set manipulation (GHashTable <G, G>)

GHashTable     *crank_set_dup           (GHashTable     *set,
                                         GHashFunc       hash,
                                         GEqualFunc      equal);

GHashTable     *crank_set_dup_full      (GHashTable     *set,
                                         GHashFunc       hash,
                                         GEqualFunc      equal,
                                         GBoxedCopyFunc  copy,
                                         GDestroyNotify  destroy);

void            crank_set_overlay       (GHashTable     *set,
                                         GHashTable     *overlay);

void            crank_set_overlay_full  (GHashTable     *set,
                                         GHashTable     *overlay,
                                         GBoxedCopyFunc  copy);

GHashTable     *crank_set_map           (GHashTable     *set,
                                         GHashFunc       hash,
                                         GEqualFunc      equal,
                                         CrankPtrPtrFunc map,
                                         gpointer        userdata);

GHashTable     *crank_set_map_full      (GHashTable     *set,
                                         GHashFunc       hash,
                                         GEqualFunc      equal,
                                         GBoxedCopyFunc  copy,
                                         GDestroyNotify  destroy,
                                         CrankPtrPtrFunc map,
                                         gpointer        userdata);




//////// Multiset manipulation (GHashTable <G, guint>)

guint            crank_mset_add         (GHashTable *mset,
                                         gpointer    item);

gint             crank_mset_remove      (GHashTable *mset,
                                         gpointer    item);

guint            crank_mset_get         (GHashTable *mset,
                                         gpointer    item);

void             crank_mset_destroy     (GHashTable     *mset,
                                         GDestroyNotify  destroy);

G_END_DECLS

#endif
