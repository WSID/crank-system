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
 * * Manipulates an #GHashTable of gpointer and #GValue.
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
 * crank_value_unset: (skip)
 * @value: (nullable) (type GValue): #GValue to unset.
 *
 * Unsets @value if it is initialized. If @value is not initialized or %NULL,
 * this function does nothing.
 *
 * This is useful for clear function. For free function, use crank_value_free().
 */
void
crank_value_unset (gpointer value)
{
  GValue *value_real = value;

  if (G_IS_VALUE (value_real))
    g_value_unset (value_real);
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
crank_value_dup (const GValue *value)
{
  GValue *result = NULL;

  if (G_IS_VALUE (value))
    {
      result = g_new0 (GValue, 1);
      crank_value_overwrite (result, value);
    }

  return result;
}

/**
 * crank_value_free: (skip)
 * @value: #GValue to free.
 *
 * Frees duplicated value.
 */
void
crank_value_free (GValue *value)
{
  crank_value_unset (value);
  g_free (value);
}


/**
 * crank_value_to_string: (skip)
 * @value: #GValue to stringify
 * @transform_fail: (transfer none) (nullable): Default value when transform
 *     fails.
 *
 * Stringify @value, utilizing transformation. If fails, duplication of
 * @transform_fail will be returned. If @value is %NULL or unsetted, %NULL is
 * returned whether @transform_fail is %NULL or not.
 *
 * Returns: (nullable) (transfer full): A stringified value or @transform_fail,
 * if transformation failed or %NULL, if @value is %NULL.
 */
gchar*
crank_value_to_string (GValue      *value,
                       const gchar *transform_fail)
{
  gchar *result = NULL;
  if ((value != NULL) && (G_IS_VALUE (value)))
    {
      GValue strval = {0};
      g_value_init (&strval, G_TYPE_STRING);

      if (g_value_transform (value, &strval))
        result = g_value_dup_string (&strval);
      else
        result = g_strdup (transform_fail);

      g_value_unset (&strval);
    }
  return result;
}



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
 * crank_value_overwrite_uint: (skip)
 * @value: (out caller-allocates): #GValue to overwrite
 * @uint_value: int value to set @value.
 *
 * Overwrites unsigned integer value to @value.
 */
void
crank_value_overwrite_uint (GValue     *value,
                            const guint uint_value)
{
  crank_value_overwrite_init (value, G_TYPE_UINT);
  g_value_set_uint (value, uint_value);
}

/**
 * crank_value_overwrite_float: (skip)
 * @value: (out caller-allocates): #GValue to overwrite
 * @float_value: float value to set @value.
 *
 * Overwrites float value to @value.
 */
void
crank_value_overwrite_float (GValue       *value,
                             const gfloat  float_value)
{
  crank_value_overwrite_init (value, G_TYPE_FLOAT);
  g_value_set_float (value, float_value);
}

/**
 * crank_value_overwrite_double: (skip)
 * @value: (out caller-allocates): #GValue to overwrite
 * @double_value: double value to set @value.
 *
 * Overwrites double value to @value.
 */
void
crank_value_overwrite_double (GValue        *value,
                              const gdouble  double_value)
{
  crank_value_overwrite_init (value, G_TYPE_DOUBLE);
  g_value_set_double (value, double_value);
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
  GType real_value_type = (value_type != G_TYPE_INVALID) ? value_type : G_TYPE_POINTER;

  crank_value_overwrite_init (value, real_value_type);
  g_value_set_pointer (value, pointer_value);
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
 * Copies #GValue from <structname>va_list</structname> to array. This function is used
 * to convert <structname>va_list</structname> into array.
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


/**
 * crank_value_table_create: (skip)
 * @hash_func: Key Hash function.
 * @key_equal_func: Key Equality function.
 *
 * Creates a hash table that holds #GValue* as value type, so that arbitarily
 * type can be used as value.
 *
 * Returns: (transfer full) (element-type gpointer GValue):
 *     Newly constructed #GHashTable.
 */
GHashTable*
crank_value_table_create (GHashFunc  hash_func,
                          GEqualFunc key_equal_func)
{
  return crank_value_table_create_full (hash_func, key_equal_func, NULL);
}

/**
 * crank_value_table_create_full: (skip)
 * @hash_func: Key Hash function.
 * @key_equal_func: Key Equality function.
 * @key_destroy_func: Key destroy function.
 *
 * Creates a hash table that holds #GValue* as value type, so that arbitarily
 * type can be used as value.
 *
 * Returns: (transfer full) (element-type gpointer GValue):
 *     Newly constructed #GHashTable.
 */
GHashTable*
crank_value_table_create_full (GHashFunc      hash_func,
                               GEqualFunc     key_equal_func,
                               GDestroyNotify key_destroy_func)
{
  return g_hash_table_new_full (hash_func,
                                key_equal_func,
                                key_destroy_func,
                                (GDestroyNotify)crank_value_free);
}

/**
 * crank_value_table_get_boolean: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 * @defval: Default value in such case of missing key, or incompatible GValue.
 *
 * Gets #gboolean value from @table.
 *
 * Returns: #gboolean value or @defval if boolean value cannot be retrieved.
 */
gboolean
crank_value_table_get_boolean (GHashTable     *table,
                               gconstpointer   key,
                               const gboolean  defval)
{
  GValue *value = g_hash_table_lookup (table, key);

  if (value != NULL &&
      G_IS_VALUE (value) &&
      g_value_type_compatible (G_VALUE_TYPE(value), G_TYPE_BOOLEAN))
    return g_value_get_boolean (value);
  else
    return defval;
}

/**
 * crank_value_table_get_uint: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 * @defval: Default value in such case of missing key, or incompatible GValue.
 *
 * Gets #guint value from @table.
 *
 * Returns: #guint value or @defval if unsigned int value cannot be retrieved.
 */
guint
crank_value_table_get_uint (GHashTable    *table,
                            gconstpointer  key,
                            const guint    defval)
{
  GValue *value = g_hash_table_lookup (table, key);

  if (value != NULL &&
      G_IS_VALUE (value) &&
      g_value_type_compatible (G_VALUE_TYPE(value), G_TYPE_UINT))
    return g_value_get_uint (value);
  else
    return defval;
}

/**
 * crank_value_table_get_int: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 * @defval: Default value in such case of missing key, or incompatible GValue.
 *
 * Gets #gint value from @table.
 *
 * Returns: #gint value or @defval if int value cannot be retrieved.
 */
gint
crank_value_table_get_int (GHashTable    *table,
                           gconstpointer  key,
                           const gint     defval)
{
  GValue *value = g_hash_table_lookup (table, key);

  if (value != NULL &&
      G_IS_VALUE (value) &&
      g_value_type_compatible (G_VALUE_TYPE(value), G_TYPE_INT))
    return g_value_get_int (value);
  else
    return defval;
}

/**
 * crank_value_table_get_float: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 * @defval: Default value in such case of missing key, or incompatible GValue.
 *
 * Gets #gfloat value from @table.
 *
 * Returns: #gfloat value or @defval if float value cannot be retrieved.
 */
gfloat
crank_value_table_get_float (GHashTable    *table,
                             gconstpointer  key,
                             const gfloat   defval)
{
  GValue *value = g_hash_table_lookup (table, key);


  if (value != NULL &&
      G_IS_VALUE (value) &&
      g_value_type_compatible (G_VALUE_TYPE(value), G_TYPE_FLOAT))
    return g_value_get_float (value);
  else
    return defval;
}

/**
 * crank_value_table_get_double: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 * @defval: Default value in such case of missing key, or incompatible GValue.
 *
 * Gets #gdouble value from @table.
 *
 * Returns: #gdouble value or @defval if double value cannot be retrieved.
 */
gdouble
crank_value_table_get_double (GHashTable    *table,
                              gconstpointer  key,
                              const gdouble  defval)
{
  GValue *value = g_hash_table_lookup (table, key);


  if (value != NULL &&
      G_IS_VALUE (value) &&
      g_value_type_compatible (G_VALUE_TYPE(value), G_TYPE_DOUBLE))
    return g_value_get_double (value);
  else
    return defval;
}

/**
 * crank_value_table_get_string: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 *
 * Gets string value from @table.
 *
 * Returns: string value or %NULL if string value cannot be retrieved.
 */
const gchar*
crank_value_table_get_string (GHashTable    *table,
                              gconstpointer  key)
{
  GValue *value = g_hash_table_lookup (table, key);

  if (value != NULL &&
      G_IS_VALUE (value) &&
      g_value_type_compatible (G_VALUE_TYPE(value), G_TYPE_STRING))
    return g_value_get_string (value);
  else
    return NULL;
}

/**
 * crank_value_table_get_object: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 *
 * Gets #GObject value from @table.
 *
 * Returns: #GObject value or %NULL if GObject value cannot be retrieved.
 */
GObject*
crank_value_table_get_object (GHashTable    *table,
                              gconstpointer  key)
{
  GValue *value = g_hash_table_lookup (table, key);

  if (value != NULL &&
      G_IS_VALUE (value) &&
      g_value_type_compatible (G_VALUE_TYPE(value), G_TYPE_OBJECT))
    return g_value_get_object (value);
  else
    return NULL;
}

/**
 * crank_value_table_get_boxed: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 * @type: (out) (optional): Type of returned value.
 *
 * Gets Boxed value and #GType from @table.
 *
 * Returns: #GObject value or %NULL if boxed value cannot be retrieved.
 */
gpointer
crank_value_table_get_boxed (GHashTable    *table,
                             gconstpointer  key,
                             GType         *type)
{
  GValue *value = g_hash_table_lookup (table, key);
  GType   mtype;

  if (value != NULL && G_IS_VALUE (value))
    {
      mtype = G_VALUE_TYPE (value);
      if (g_value_type_compatible (mtype, G_TYPE_BOXED))
        {
          if (type != NULL) *type = mtype;
          return g_value_get_boxed (value);
        }
    }
  return NULL;
}

/**
 * crank_value_table_get_pointer: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 * @type: (out) (optional): Type of returned value.
 *
 * Gets pointer value and #GType from @table.
 *
 * Returns: #GObject value or %NULL if pointer value cannot be retrieved.
 */
gpointer
crank_value_table_get_pointer   (GHashTable    *table,
                                 gconstpointer  key,
                                 GType         *type)
{
  GValue *value = g_hash_table_lookup (table, key);
  GType   mtype;

  if (value != NULL && G_IS_VALUE (value))
    {
      mtype = G_VALUE_TYPE (value);
      if (g_value_type_compatible (mtype, G_TYPE_POINTER))
        {
          if (type != NULL) *type = mtype;
          return g_value_get_boxed (value);
        }
    }
  return NULL;
}

/**
 * crank_value_table_set: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @key: A key.
 * @value: A Value
 *
 * Sets @value to given key.
 */
void
crank_value_table_set (GHashTable   *table,
                       gpointer      key,
                       const GValue *value)
{
  GValue *tableval = g_hash_table_lookup (table, key);

  if (tableval != NULL)
    crank_value_overwrite (tableval, value);
  else
    g_hash_table_insert (table, key, crank_value_dup (value));
}

/**
 * crank_value_table_set_boolean: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @value: A Value.
 *
 * Sets #gboolean value to given key.
 */
void
crank_value_table_set_boolean (GHashTable     *table,
                               gpointer        key,
                               const gboolean  value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_boolean (gvalue, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_boolean (gvalue, value);
      g_hash_table_insert (table, key, gvalue);
    }
}

/**
 * crank_value_table_set_uint: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @value: A Value.
 *
 * Sets #guint value to given key.
 */
void
crank_value_table_set_uint (GHashTable  *table,
                            gpointer     key,
                            const guint  value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_uint (gvalue, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_uint (gvalue, value);
      g_hash_table_insert (table, key, gvalue);
    }
}

/**
 * crank_value_table_set_int: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @value: A Value.
 *
 * Sets #gint value to given key.
 */
void
crank_value_table_set_int (GHashTable *table,
                           gpointer    key,
                           const gint  value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_int (gvalue, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_int (gvalue, value);
      g_hash_table_insert (table, key, gvalue);
    }
}

/**
 * crank_value_table_set_float: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @value: A Value.
 *
 * Sets #gfloat value to given key.
 */
void
crank_value_table_set_float (GHashTable   *table,
                             gpointer      key,
                             const gfloat  value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_float (gvalue, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_float (gvalue, value);
      g_hash_table_insert (table, key, gvalue);
    }
}
/**
 * crank_value_table_set_double: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @value: A Value.
 *
 * Sets #gdouble value to given key.
 */
void
crank_value_table_set_double (GHashTable    *table,
                              gpointer       key,
                              const gdouble  value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_double (gvalue, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_double (gvalue, value);
      g_hash_table_insert (table, key, gvalue);
    }
}

/**
 * crank_value_table_set_string: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @value: A Value.
 *
 * Sets string value to given key.
 */
void
crank_value_table_set_string (GHashTable  *table,
                              gpointer     key,
                              const gchar *value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_string (gvalue, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_string (gvalue, value);
      g_hash_table_insert (table, key, gvalue);
    }
}

/**
 * crank_value_table_set_object: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @value: A Value.
 *
 * Sets #GObject value to given key.
 */
void
crank_value_table_set_object (GHashTable *table,
                              gpointer    key,
                              GObject    *value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_object (gvalue, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_object (gvalue, value);
      g_hash_table_insert (table, key, gvalue);
    }
}

/**
 * crank_value_table_set_boxed: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @type: #GType of @value
 * @value: A Value.
 *
 * Sets boxed value to given key.
 */
void
crank_value_table_set_boxed (GHashTable *table,
                             gpointer    key,
                             GType       type,
                             gpointer    value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_boxed (gvalue, type, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_boxed (gvalue, type, value);
      g_hash_table_insert (table, key, gvalue);
    }
}

/**
 * crank_value_table_set_pointer: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *      A hash table.
 * @key: A key.
 * @type: #GType of @value
 * @value: A Value.
 *
 * Sets pointer value to given key.
 */
void
crank_value_table_set_pointer (GHashTable *table,
                               gpointer    key,
                               GType       type,
                               gpointer    value)
{
  GValue *gvalue = g_hash_table_lookup (table, key);

  if (gvalue != NULL)
    {
      crank_value_overwrite_pointer (gvalue, type, value);
    }
  else
    {
      gvalue = g_new0 (GValue, 1);
      crank_value_overwrite_pointer (gvalue, type, value);
      g_hash_table_insert (table, key, gvalue);
    }
}


/**
 * crank_value_table_dup: (skip)
 * @table: (transfer none) (element-type gpointer GValue) (nullable):
 *     A hash table.
 * @keyhash: (scope call): A Hash function.
 * @keyequal: (scope call): A Equal function.
 * @keycopy: (scope call) (nullable): A Key copy function to provide duplicated
 *     key to newly duplicated table, or %NULL to not copy keys.
 * @keydestroy: (scope call) (nullable): A Key destroy function to destroy keys
 *     in new table. Generally it is %NULL if @keycopy is %NULL.
 *
 * Duplicates a hash table with #GValue. For %NULL, it simply returns %NULL.
 *
 * Returns: (transfer full) (element-type gpointer GValue) (nullable):
 *     Duplicated table or %NULL, if @table is %NULL.
 */
GHashTable*
crank_value_table_dup (GHashTable *table,
                       GHashFunc keyhash,
                       GEqualFunc keyequal,
                       GBoxedCopyFunc keycopy,
                       GDestroyNotify keydestroy)
{
  GHashTable *dup;

  GHashTableIter i;
  gpointer ik;
  gpointer iv;

  if (table == NULL)
    return NULL;

  dup = crank_value_table_create_full (keyhash, keyequal, keydestroy);

  g_hash_table_iter_init (&i, table);
  while (g_hash_table_iter_next (&i, &ik, &iv))
    {
      g_hash_table_insert (dup,
                           (keycopy != NULL) ? keycopy (ik) : ik,
                           crank_value_dup ((GValue*)iv));
    }
  return dup;
}

/**
 * crank_value_table_overlay: (skip)
 * @table: (transfer none) (element-type gpointer GValue):
 *     A hash table.
 * @overlay: (transfer none) (element-type gpointer GValue) (nullable):
 *     A overlaying hash table.
 * @keycopy: (scope call) (nullable): A Key copy function to provide duplicated
 *     key to @table, or %NULL to not copy keys.
 *
 * Overlays content of @overlay to @table, which means @table will have all key
 * and values in @overlay.
 */
void
crank_value_table_overlay (GHashTable     *table,
                           GHashTable     *overlay,
                           GBoxedCopyFunc  keycopy)
{
  GHashTableIter i;
  gpointer ik;
  gpointer iv;

  if (overlay == NULL)
    return;

  g_hash_table_iter_init (&i, overlay);
  while (g_hash_table_iter_next (&i, &ik, &iv))
    {
      crank_value_table_set (table,
                             (keycopy != NULL) ? keycopy (ik) : ik,
                             (GValue*)iv );
    }
}
