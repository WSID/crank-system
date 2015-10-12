#ifndef CRANKVALUE_H
#define CRANKVALUE_H

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
#error crankvalue.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

void    crank_value_overwrite_init         (GValue      *value,
                                            const GType  type);

void    crank_value_overwrite              (GValue       *value,
                                            const GValue *from);

void    crank_value_overwrite_boolean      (GValue         *value,
                                            const gboolean  bool_value);

void    crank_value_overwrite_int          (GValue     *value,
                                            const gint  int_value);

void    crank_value_overwrite_uint         (GValue     *value,
                                            const guint uint_value);

void    crank_value_overwrite_float        (GValue      *value,
                                            const gfloat float_value);

void    crank_value_overwrite_double       (GValue       *value,
                                            const gdouble double_value);

void    crank_value_overwrite_string       (GValue      *value,
                                            const gchar *str_value);

void    crank_value_overwrite_object       (GValue  *value,
                                            GObject *obj_value);

void    crank_value_overwrite_boxed        (GValue      *value,
                                            const GType  value_type,
                                            gpointer     boxed_value);

void    crank_value_overwrite_pointer      (GValue      *value,
                                            const GType  value_type,
                                            gpointer     pointer_value);

GValue *crank_value_dup                    (GValue      *value);

void    crank_value_free                   (GValue      *value);


void    crank_value_array_overwrite        (GValue *array,
                                            gint    nitem,
                                            ...);

void    crank_value_array_overwrite_va     (GValue  *array,
                                            gint     nitem,
                                            va_list  varargs);

void    crank_value_array_overwrite_array  (GValue *array,
                                            gint    nitem,
                                            GValue *other);

void    crank_value_array_unset            (GValue *array,
                                            guint   narray);

GHashTable     *crank_value_table_create        (GHashFunc      hash_func,
                                                 GEqualFunc     key_equal_func);

GHashTable     *crank_value_table_create_full   (GHashFunc      hash_func,
                                                 GEqualFunc     key_equal_func,
                                                 GDestroyNotify key_destroy_func);

gboolean        crank_value_table_get_boolean   (GHashTable    *table,
                                                 gconstpointer  key,
                                                 const gboolean defval);

guint           crank_value_table_get_uint      (GHashTable    *table,
                                                 gconstpointer  key,
                                                 const guint    defval);

gint            crank_value_table_get_int       (GHashTable    *table,
                                                 gconstpointer  key,
                                                 const gint     defval);

gfloat          crank_value_table_get_float     (GHashTable    *table,
                                                 gconstpointer  key,
                                                 const gfloat   defval);

gdouble         crank_value_table_get_double    (GHashTable    *table,
                                                 gconstpointer  key,
                                                 const gdouble  defval);

const gchar*    crank_value_table_get_string    (GHashTable    *table,
                                                 gconstpointer  key);

GObject*        crank_value_table_get_object    (GHashTable    *table,
                                                 gconstpointer  key);

gpointer        crank_value_table_get_boxed     (GHashTable    *table,
                                                 gconstpointer  key,
                                                 GType         *type);

gpointer        crank_value_table_get_pointer   (GHashTable    *table,
                                                 gconstpointer  key,
                                                 GType         *type);


void            crank_value_table_set_boolean   (GHashTable    *table,
                                                 gpointer       key,
                                                 const gboolean value);

void            crank_value_table_set_uint      (GHashTable    *table,
                                                 gpointer       key,
                                                 const guint    value);

void            crank_value_table_set_int       (GHashTable    *table,
                                                 gpointer       key,
                                                 const gint     value);

void            crank_value_table_set_float     (GHashTable    *table,
                                                 gpointer       key,
                                                 const gfloat   value);

void            crank_value_table_set_double    (GHashTable    *table,
                                                 gpointer       key,
                                                 const gdouble  value);

void            crank_value_table_set_string    (GHashTable    *table,
                                                 gpointer       key,
                                                 const gchar   *value);

void            crank_value_table_set_object    (GHashTable    *table,
                                                 gpointer       key,
                                                 GObject       *value);

void            crank_value_table_set_boxed     (GHashTable    *table,
                                                 gpointer       key,
                                                 GType          type,
                                                 gpointer       value);

void            crank_value_table_set_pointer   (GHashTable    *table,
                                                 gpointer       key,
                                                 GType          type,
                                                 gpointer       value);




G_END_DECLS

#endif //CRANKVALUE_H
