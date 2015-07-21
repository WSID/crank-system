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

#include "crankfunction.h"

/**
 * crank_float_equal:
 * @a: A Pointer pointing a float value.
 * @b: A Pointer pointing a float value.
 *
 * Check equality of float values, with 0.0001f of error range.
 *
 * Returns: string represents of float. free with g_free()
 */
gboolean
crank_float_equal (	gconstpointer	a,
					gconstpointer	b	)
{
	gfloat av = *(gfloat*)a;
	gfloat bv = *(gfloat*)b;
	return (bv - 0.0001f < av) && (av < bv + 0.0001f);
}

/**
 * crank_float_to_string:
 * @value: A pointer pointing a float value.
 * @userdata: (nullable): Format for stringification.
 *
 * Stringify a float value.
 *
 * Returns: string represents of float. free with g_free()
 */
gchar*
crank_float_to_string (	gpointer	value,
						gpointer	userdata)
{
	gchar* format = (userdata != NULL) ? (gchar*)userdata : "%g";
	return g_strdup_printf (format, *(gfloat*)value); 
}

/**
 * crank_pointer_to_string:
 * @value: A pointer.
 * @userdata: (nullable): Format for stringification.
 *
 * Stringify a pointer.
 *
 * Returns: string represents pointer. free with g_free()
 */
gchar*
crank_pointer_to_string (	gpointer	value,
						gpointer	userdata)
{
	gchar* format = (userdata != NULL) ? (gchar*)userdata : "%p";
	return g_strdup_printf (format, value); 
}

/**
 * crank_compare_nondata_wrapf:
 * @a: A Pointer
 * @b: A Pointer
 * @userdata: A Function, which is #GCompareFunc
 * 
 * wraps a compare function which does not receive userdata.
 *
 * Returns: invoke result of @userdata.
 */
gint
crank_compare_nondata_wrapf (	gconstpointer	a,
								gconstpointer	b,
								gpointer		userdata	)
{
	GCompareFunc	function = (GCompareFunc)userdata;
	
	return function (a, b);
}

/**
 * crank_str_ptr_nondata_wrapf:
 * @value: A Pointer.
 * @userdata: A function, which is gchar*(*)(gconstpointer)
 *
 * wraps a stringification function which does not receive userdata.
 *
 * Wrapped function should return allocated string, so that it can be freed with
 * g_free()
 *
 * Returns: Invoke result of @userdata. free with g_free()
 */
gchar*
crank_str_ptr_nondata_wrapf (	gpointer	value,
								gpointer	userdata	)
{
	gchar* (*function) (gpointer);
	
	function = (gchar* (*)(gpointer)) userdata;
	
	return function (value);
}
