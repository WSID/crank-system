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

G_END_DECLS

#endif //CRANKVALUE_H
