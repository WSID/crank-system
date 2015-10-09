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

/**
 * SECTION: crankvalue
 * @title: GValue Utility
 * @short_description: Utility function to manipulate GValues
 * @stability: Unstable
 * @include: crankbase.h
 *
 * The functions defined here are used to manipulate #GValue, which
 * Crank System uses frequently.
 *
 * #GValue needs to be initialized before use. Functions in this section
 * initializes and sets values at once, for convenience.
 *
 * Crank System provides two kind of functions.
 *
 * * Manipulates single #GValue.
 * * Manipulates an array of #GValue
 *
 * These functions are meant to be used in C. In other language, use each of
 * support functions.
 */

#define _CRANKBASE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankvalue.h"

/**
 * crank_value_overwrite_init: (skip)
 * @value: (out caller-allocates): #GValue to overwrite
 * @type: Type to initialize value.
 *
 * Unset @value if it holds value, and re-initialize it with @type.
 */
void
crank_value_overwrite_init (GValue     *value,
                            const GType type)
{
  if (G_IS_VALUE(value))
    g_value_unset (value);

  g_value_init (value, type);
}

/**
 * crank_value_overwrite: (skip)
 * @value: (out caller-allocates): #GValue to overwrite
 * @from: (nullable): GValue to copy
 *
 * Unset @value if it holds value, and initialize it with type of @from, and
 * copy value of @from onto @value.
 */
void
crank_value_overwrite (GValue       *value,
                       const GValue *from)
{
  if (G_IS_VALUE (value))
    g_value_unset (value);

  if ((from != NULL) && (G_IS_VALUE (from)))
    {
      crank_value_overwrite_init (value, G_VALUE_TYPE(from));
      g_value_copy (from, value);
    }
}

/**
 * crank_value_overwrite_boolean: (skip)
 * @value: (out caller-allocates): #GValue to overwrite
 * @bool_value: boolean value to set @value.
 *
 * Overwrites boolean value to @value.
 */
void
crank_value_overwrite_boolean (GValue        *value,
                               const gboolean bool_value)
{
  crank_value_overwrite_init (value, G_TYPE_BOOLEAN);
  g_value_set_boolean (value, bool_value);
}

/**
 * crank_value_overwrite_int: (skip)
 * @value: (out caller-allocates): #GValue to overwrite
 * @int_value: int value to set @value.
 *
 * Overwrites integer value to @value.
 */
void
crank_value_overwrite_int (GValue    *value,
                           const gint int_value)
{
  crank_value_overwrite_init (value, G_TYPE_INT);
  g_value_set_int (value, int_value);
}

/**
 * crank_value_overwrite_string: (skip)
 * @value: (out caller-allocates): #GValue to overwrite
 * @str_value: string value to set @value.
 *
 * Overwrites string value to @value.
 */
void
crank_value_overwrite_string (GValue      *value,
                              const gchar *str_value)
{
  crank_value_overwrite_init (value, G_TYPE_STRING);
  g_value_set_string (value, str_value);
}

/**
 * crank_value_overwrite_object: (skip)
 * @value: (out caller-allocates): GValue to overwrite
 * @obj_value: #GObject value to set @value.
 *
 * Overwrites #GObject value to @value.
 */
void
crank_value_overwrite_object (GValue  *value,
                              GObject *obj_value)
{
  crank_value_overwrite_init (value, G_TYPE_OBJECT);
  g_value_set_object (value, obj_value);
}

/**
 * crank_value_overwrite_boxed: (skip)
 * @value: (out caller-allocates): #GValue to overwrite.
 * @value_type: #GType of @boxed_value.
 * @boxed_value: Boxed value to set @value.
 *
 * Overwrites boxed value to @value. As boxed type does not hold type
 * information by itself, GType should be provided.
 */
void
crank_value_overwrite_boxed (GValue     *value,
                             const GType value_type,
                             gpointer    boxed_value)
{
  crank_value_overwrite_init (value, value_type);
  g_value_set_boxed (value, boxed_value);
}



/**
 * crank_value_overwrite_pointer: (skip)
 * @value: (out caller-allocates): #GValue to overwrite.
 * @value_type: #GType of @pointer_value.
 * @pointer_value: pointer to set @value.
 *
 * Overwrites pointer to @value. Generally you can pass %G_TYPE_POINTER to
 * @value_type. You can pass other %G_TYPE_POINTER derived type to mark @value
 * holds other pointer type.
 */
void
crank_value_overwrite_pointer (GValue     *value,
                               const GType value_type,
                               gpointer    pointer_value)
{
  crank_value_overwrite_init (value, value_type);
  g_value_set_pointer (value, pointer_value);
}


/**
 * crank_value_dup: (skip)
 * @value: #GValue to duplicate.
 *
 * Duplicates @value. This returns %NULL if @value is not initialized, frequently
 * when @value is left un-initialized to be used as 'void' #GValue.
 *
 * Returns: (nullable): Duplicated @value, or %NULL if @value is not initialized.
 */
GValue*
crank_value_dup (GValue *value)
{
  GValue *result = NULL;

  if (G_IS_VALUE (value))
    {
      result = g_slice_new0 (GValue);
      crank_value_overwrite (result, value);
    }

  return result;
}


/**
 * crank_value_array_overwrite: (skip)
 * @array: (array length=nitem) (out caller-allocates): array of GValue to overwrite.
 * @nitem: Number of items to overwrite on @array
 * @...: (type GValue): variadic arguments of GValue to copy.
 *
 * Copies #GValue from variadic arguments to array.
 */
void
crank_value_array_overwrite (GValue *array,
                             gint    nitem,
                             ...)
{
  va_list varargs;

  va_start (varargs, nitem);

  crank_value_array_overwrite_va (array, nitem, varargs);

  va_end (varargs);
}


/**
 * crank_value_array_overwrite_va: (skip)
 * @array: (array length=nitem) (out caller-allocates): array of GValue to overwrite.
 * @nitem: Number of items to overwrite on @array
 * @varargs: va_list of GValue to copy
 *
 * Cpoies #GValue from <struct>va_list</struct> to array. This function is used
 * to convert <struct>va_list</struct> into array.
 */
void
crank_value_array_overwrite_va (GValue *array,
                                gint    nitem,
                                va_list varargs)
{
  guint i;

  for (i = 0; i < nitem; i++)
    crank_value_overwrite (array + i, va_arg (varargs, GValue*));
}

/**
 * crank_value_array_overwrite_array: (skip)
 * @array: (array length=nitem) (out caller-allocates): array of GValue to overwrite.
 * @nitem: Number of items to overwrite on @array
 * @other: (array length=nitem): array of GValue to copy.
 *
 * Copies array of #GValue to other array.
 */
void
crank_value_array_overwrite_array (GValue *array,
                                   gint    nitem,
                                   GValue *other)
{
  guint i;

  for (i = 0; i < nitem; i++)
    crank_value_overwrite (array + i, other + i);
}

/**
 * crank_value_array_unset: (skip)
 * @array: (array length=narray): array of GValues to unset.
 * @narray: length of @array.
 *
 * Unsets each #GValue of @array.
 */
void
crank_value_array_unset (GValue *array,
                         guint   narray)
{
  guint i;

  for (i = 0; i < narray; i++)
    g_value_unset (array + i);
}
