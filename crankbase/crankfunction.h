#ifndef _CRANK_FUNCTION_HEADER
#define _CRANK_FUNCTION_HEADER

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
#error "crankfunction.h cannot be directly included."
#endif

#include <glib.h>

#include "crankcomplex.h"

/**
 * SECTION: crankfunction
 * @title: Function Definitions
 * @short_description: Contains function types that frequently used.
 * @include: crankbase.h
 * @stability: unstable
 *
 * Any library usually defines their own function types, as required function
 * types are very specific to their use, and not really useful for generic uses.
 *
 * No exception to Crank System, too. Most of function type defined in Crank
 * System, are defined in their specific section. But some of function types are
 * frequently used and might be useful for generic uses.
 */

G_BEGIN_DECLS

//////// Function Definitions //////////////////////////////////////////////////

/**
 * CrankCallback: (skip)
 * @userdata: (closure): A userdata for callback.
 *
 * It represents any functions that accept @userdata.
 *
 * This is not used for actual callback type, but a placeholder for any function
 * type.
 */
typedef void		(*CrankCallback) (		gpointer		userdata	);

/**
 * CrankBoolBoolFunc:
 * @value: Value for function.
 * @userdata: (closure): A userdata for callback.
 *
 * This function receives #gboolean and returns #gboolean.
 *
 * This is mainly used for iteration functions and the return value is checked
 * to determine whether to keep iteration.
 *
 * Returns: A boolean value.
 */
typedef gboolean	(*CrankBoolBoolFunc) (	const gboolean	value,
											gpointer		userdata	);

/**
 * CrankBoolIntFunc:
 * @value: Value for function.
 * @userdata: (closure): A userdata for callback.
 *
 * This function receives #gint and returns #gboolean.
 *
 * This is mainly used for iteration functions and the return value is checked
 * to determine whether to keep iteration.
 *
 * Returns: A boolean value.
 */
typedef gboolean	(*CrankBoolIntFunc) (	const gint		value,
											gpointer		userdata	);


/**
 * CrankBoolFloatFunc:
 * @value: Value for function.
 * @userdata: (closure): A userdata for callback.
 *
 * This function receives #gfloat and returns #gboolean.
 *
 * This is mainly used for iteration functions and the return value is checked
 * to determine whether to keep iteration.
 *
 * Returns: A boolean value.
 */
typedef gboolean	(*CrankBoolFloatFunc) (	const gfloat	value,
											gpointer		userdata	);


/**
 * CrankBoolCplxFloatFunc:
 * @value: Value for function.
 * @userdata: (closure): A userdata for callback.
 *
 * This function receives #CrankCplxFloat and returns #gboolean.
 *
 * This is mainly used for iteration functions and the return value is checked
 * to determine whether to keep iteration.
 *
 * Returns: A boolean value.
 */
typedef gboolean	(*CrankBoolCplxFloatFunc) (	CrankCplxFloat*	value,
												gpointer		userdata	);
												
												
												
		
/**
 * CrankStrPtrFunc:
 * @value: Value for function.
 * @userdata: (closure): A userdata for callback.
 *
 * This function receives #gpointer and returns allocated string. It will be
 * freed with g_free().
 *
 * Returns: (transfer full): A String value.
 */
typedef gchar*		(*CrankStrPtrFunc) (		gpointer		value,
												gpointer		userdata	);
												
gboolean	crank_float_equal (			gconstpointer	a,
										gconstpointer	b	);


gchar*		crank_float_to_string (		gpointer	value,
										gpointer	userdata	);
G_END_DECLS

#endif
