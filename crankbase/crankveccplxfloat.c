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

#include <math.h>
#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankfunction.h"
#include "crankveccommon.h"
#include "crankvecbool.h"
#include "crankvecint.h"
#include "crankvecfloat.h"
#include "crankveccplxfloat.h"
#include "crankmatfloat.h"

/**
 * SECTION:crankveccplxfloat
 * @title: Complex Float Vectors.
 * @short_description: Vectors with complex float components.
 * @usability: unstable
 * @include: crankbase.h
 *
 * Crank System provides complex float vectors for convenience.
 */

/**
 * CrankVecCplxFloatN:
 * @data: (array length=n): Array to store elements.
 * @n: size of data.
 *
 * Struct to point variable size of float vector.
 */
G_DEFINE_BOXED_TYPE (
		CrankVecCplxFloatN,
		crank_vec_cplx_float_n,
		crank_vec_cplx_float_n_dup,
		crank_vec_cplx_float_n_free	)

//////// Private functions ////////

void		crank_vec_cplx_float_n_realloc	(	CrankVecCplxFloatN*	vec, const guint n	);



void
crank_vec_cplx_float_n_realloc (	CrankVecCplxFloatN*	vec,
								const guint		n	)
{
	vec->data = g_renew (CrankCplxFloat, vec->data, n);
	vec->n = n;
}



/**
 * crank_vec_cplx_float_n_init:
 * @vec: (out): Vector to initialize.
 * @n: size of vector.
 * @...: element of vector.
 *
 * Initializes vector with given components.
 */
void
crank_vec_cplx_float_n_init	(	CrankVecCplxFloatN*	vec,
							const guint		n,
							...	)
{
	va_list	varargs;
	
	va_start (varargs, n);
	
	crank_vec_cplx_float_n_init_valist (vec, n, varargs);
	
	va_end (varargs);
}

/**
 * crank_vec_cplx_float_n_init_arr:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @arr: (array length=n): Array that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_cplx_float_n_init_arr	(	CrankVecCplxFloatN*	vec,
									const guint		n,
									CrankCplxFloat*	arr	)
{
	guint	i;
	
	crank_vec_cplx_float_n_realloc (vec, n);
	
	for (i = 0; i < n; i++)
		crank_cplx_float_copy (arr + i, vec->data + i);
}

/**
 * crank_vec_cplx_float_n_init_arr_take:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @arr: (transfer full): Array that contains elements.
 *
 * Initializes vector by taking array as data.
 */
void
crank_vec_cplx_float_n_init_arr_take (	CrankVecCplxFloatN*	vec,
								 		const guint		n,
								 		CrankCplxFloat*			arr	)
{
  	g_free (vec->data);
  	vec->n = n;
  	vec->data = arr;
}

/**
 * crank_vec_cplx_float_n_init_valist:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_cplx_float_n_init_valist	(	CrankVecCplxFloatN*	vec,
										const guint		n,
										va_list			varargs	)
{
	guint	i;
	
	crank_vec_cplx_float_n_realloc (vec, n);
	
	for (i = 0; i < n; i++)
		crank_cplx_float_copy (va_arg (varargs, CrankCplxFloat*), vec->data + i);
}

/**
 * crank_vec_cplx_float_n_init_fill:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @fill: element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_cplx_float_n_init_fill	(	CrankVecCplxFloatN*	vec,
								const guint		n,
								CrankCplxFloat*			fill	)
{
	guint	i;
	
	crank_vec_cplx_float_n_realloc (vec, n);
	
	for (i = 0; i < n; i++) crank_cplx_float_copy (fill, vec->data + i);
}


/**
 * crank_vec_cplx_float_n_init_imm:
 * @vec: (out): Vector to initialize.
 * @n: size of vector.
 * @...: element of vector.
 *
 * Initializes vector with pairs of real, imaginary components.
 *
 * Note that this function requires 2*@n elements in @..., as a pair of item
 * makes a element.
 */
void
crank_vec_cplx_float_n_init_imm	(	CrankVecCplxFloatN*	vec,
									const guint		n,
									...	)
{
	va_list	varargs;
	
	va_start (varargs, n);
	
	crank_vec_cplx_float_n_init_valist_imm (vec, n, varargs);
	
	va_end (varargs);
}

/**
 * crank_vec_cplx_float_n_init_valist_imm:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_cplx_float_n_init_valist_imm	(	CrankVecCplxFloatN*	vec,
											const guint		n,
											va_list			varargs	)
{
	guint	i;
	
	crank_vec_cplx_float_n_realloc (vec, n);
	
	for (i = 0; i < n; i++)
		crank_cplx_float_init_valist (vec->data + i, varargs);
}

/**
 * crank_vec_cplx_float_n_init_fill_imm:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @real: real part of element to fill @vec
 * @imag: imaginary part of element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_cplx_float_n_init_fill_imm	(	CrankVecCplxFloatN*	vec,
								const guint		n,
								const gfloat	real,
								const gfloat	imag	)
{
	guint	i;
	
	crank_vec_cplx_float_n_realloc (vec, n);
	
	for (i = 0; i < n; i++) crank_cplx_float_init (vec->data + i, real, imag);
}


/**
 * crank_vec_cplx_float_n_init_from_vb:
 * @vec: (out): Vector to initialize.
 * @vb: Boolean vector.
 *
 * Initialize vector from boolean vector.
 */
void
crank_vec_cplx_float_n_init_from_vb	(	CrankVecCplxFloatN*	vec,
									CrankVecBoolN*	vb		)
{
	guint	i;
	
	crank_vec_cplx_float_n_realloc (vec, vb->n);
	
	for (i = 0; i < vb->n; i++) 
		crank_cplx_float_init (vec->data + i,
				vb->data[i] ? 1.0f: 0.0f,
				0.0f);
}

/**
 * crank_vec_cplx_float_n_init_from_vi:
 * @vec: (out): Vector to initialize.
 * @vi: Integer vector.
 *
 * Initialize vector from integer vector.
 */
void
crank_vec_cplx_float_n_init_from_vi	(	CrankVecCplxFloatN*	vec,
									CrankVecIntN*	vi		)
{
	guint	i;
	
	crank_vec_cplx_float_n_realloc (vec, vi->n);
	
	for (i = 0; i < vi->n; i++)
		crank_cplx_float_init (vec->data + i,
				vi->data[i],
				0);
}


/**
 * crank_vec_cplx_float_n_fini:
 * @vec: Vector to finalize.
 *
 * Frees all allocated memory and unsets @vec to point 0-sized vector at %NULL.
 */
void
crank_vec_cplx_float_n_fini (	CrankVecCplxFloatN*	vec	)
{
	g_free (vec->data);
	vec->data = NULL;
	vec->n = 0;
}


/**
 * crank_vec_cplx_float_n_copy:
 * @vec: Vector to copy.
 * @other: (out): Other vector to paste.
 *
 * Copies vector.
 */
void
crank_vec_cplx_float_n_copy			(	CrankVecCplxFloatN*	vec,
							 			CrankVecCplxFloatN*	other	)
{
  	crank_vec_cplx_float_n_init_arr (other, vec->n, vec->data);
}

/**
 * crank_vec_cplx_float_n_dup:
 * @vec: Vector to copy.
 *
 * Copies vector. The returned pointer should be freed by crank_vec_cplx_float_n_free().
 *
 * Returns: (transfer full): copied vector
 */
CrankVecCplxFloatN*
crank_vec_cplx_float_n_dup			(	CrankVecCplxFloatN*	vec	)
{
  	CrankVecCplxFloatN*	result = g_new0 (CrankVecCplxFloatN, 1);
  	crank_vec_cplx_float_n_init_arr (result, vec->n, vec->data);
  	return result;
}

/**
 * crank_vec_cplx_float_n_free:
 * @vec: Vector to free.
 *
 * Frees all allocated memory and frees struct too.
 */
void
crank_vec_cplx_float_n_free (	CrankVecCplxFloatN*	vec	)
{
	crank_vec_cplx_float_n_fini (vec);
	g_free (vec);
}

/**
 * crank_vec_cplx_float_n_get_size:
 * @vec: A Vector.
 *
 * Gets size of a vector.
 *
 * Returns: Size of vector.
 */
guint
crank_vec_cplx_float_n_get_size (	CrankVecCplxFloatN*	vec	)
{
	return vec->n;
}

/**
 * crank_vec_cplx_float_n_get:
 * @vec: Vector to get element.
 * @index: index to get element at.
 * @value: (out): Element of vector
 *
 * Gets element of vector at @index.
 */
void
crank_vec_cplx_float_n_get	(	CrankVecCplxFloatN*	vec,
								const guint			index,
								CrankCplxFloat*		value	)
{
	crank_cplx_float_copy (vec->data + index, value);
}

/**
 * crank_vec_cplx_float_n_set:
 * @vec: Vector to set element.
 * @index: index to set element at.
 * @value: value of element.
 *
 * Sets element of vector at @index, by @value.
 */
void
crank_vec_cplx_float_n_set			(	CrankVecCplxFloatN*	vec,
										const guint		index,
										CrankCplxFloat*	value	)
{
	crank_cplx_float_copy (value, vec->data + index);
}

/**
 * crank_vec_cplx_float_n_prepend:
 * @vec: Vector to insert element.
 * @value: Value of element.
 *
 * Prepends an element to vector.
 */
void
crank_vec_cplx_float_n_prepend (	CrankVecCplxFloatN*	vec,
						   			CrankCplxFloat*		value	)
{
	crank_vec_cplx_float_n_insert (vec, 0, value);
}

/**
 * crank_vec_cplx_float_n_append:
 * @vec: Vector to insert element.
 * @value: Value of element.
 *
 * Appends an element to vector.
 */
void
crank_vec_cplx_float_n_append (	CrankVecCplxFloatN* vec,
						  		CrankCplxFloat*		value	)
{
	crank_vec_cplx_float_n_insert (vec, vec->n, value);
}

/**
 * crank_vec_cplx_float_n_insert:
 * @vec: Vector to insert element.
 * @index: Index to insert element.
 * @value: Value of element.
 *
 * Inserts an element to vector.
 */
void
crank_vec_cplx_float_n_insert (	CrankVecCplxFloatN*	vec,
							  	const guint			index,
							  	CrankCplxFloat*		value	)
{
  	guint	i;

	g_return_if_fail (index <= vec->n);

  	vec->n++;
  	vec->data = g_renew (CrankCplxFloat, vec->data, vec->n);

  	for (i = vec->n - 1; index < i; i--)
  		crank_cplx_float_copy (vec->data + (i - 1), vec->data + i);

	crank_cplx_float_copy (value, vec->data + index);
}

/**
 * crank_vec_cplx_float_n_remove:
 * @vec: Vector to remove element.
 * @index: Index to remove element.
 *
 * Removes an element from vector.
 */
void
crank_vec_cplx_float_n_remove (	CrankVecCplxFloatN*	vec,
						  		const guint		index	)
{
	guint	i;

  	g_return_if_fail (index < vec->n);

	vec->n--;

  	for (i = index; i < vec->n; i++)
  		crank_cplx_float_copy (vec->data + (i + 1), vec->data + i);

  	vec->data = g_renew (CrankCplxFloat, vec->data, vec->n);
}

/**
 * crank_vec_cplx_float_n_foreach:
 * @vec: Vector to iterate.
 * @func: (scope call): Function to iterate over.
 * @userdata: (closure): Userdata for @func.
 *
 * Iterates over a float vector.
 *
 * Return #TRUE to continue iteration, #FALSE to stop iteration.
 *
 * Returns: Whether iteration was stopped.
 */
gboolean
crank_vec_cplx_float_n_foreach (	CrankVecCplxFloatN*		vec,
							  		CrankBoolCplxFloatFunc	func,
								  	gpointer			userdata	)
{
  	guint	i;

  	for (i = 0; i < vec->n; i++)
	  	if (! func (vec->data + i, userdata)) return FALSE;

	return TRUE;
}

/**
 * crank_vec_cplx_float_n_iterator:
 * @vec: A Vector.
 * @iter: (out): A Iterator.
 *
 * Initialize a iterator for a vector.
 */
void
crank_vec_cplx_float_n_iterator (	CrankVecCplxFloatN*	vec,
									CrankIterMemStruct*	iter	)
{
	crank_iter_mem_struct_init_with_count_typed (iter, CrankCplxFloat, vec->data, vec->n);
}

//////// Basic operation ////////

/**
 * crank_vec_cplx_float_n_hash:
 * @a: (type CrankVecCplxFloatN): Vector to get hash
 *
 * Gets hash value of vector. This can be used when using vectors as key for
 * hashing structures like #GHashTable.
 *
 * Returns: hash value of vector.
 */
guint
crank_vec_cplx_float_n_hash (	gconstpointer	a	)
{
	const CrankVecCplxFloatN*	vec = a;
	
	guint	i;
	guint	hash = 0;
	
	for (i = 0; i < vec->n; i++)
		hash += 37 + crank_cplx_float_hash (vec->data + i);
	
	return hash;
}

/**
 * crank_vec_cplx_float_n_equal:
 * @a: (type CrankVecCplxFloatN): Vector to compare.
 * @b: (type CrankVecCplxFloatN): Vector to compare.
 *
 * Compares two vector for equality.
 *
 * Returns: whether that the two vectors are same.
 */
gboolean		crank_vec_cplx_float_n_equal (	gconstpointer	a,
											gconstpointer	b	)
{
	CrankVecCplxFloatN*	veca = (CrankVecCplxFloatN*)a;
	CrankVecCplxFloatN*	vecb = (CrankVecCplxFloatN*)b;
	
	guint	n;
	guint	i;
	
	if (veca->n != vecb->n) return FALSE;
	
	n = veca->n;
	
	for (i = 0; i < n; i++)
		if (! crank_cplx_float_equal (veca->data + i, vecb->data + i))
			return FALSE;
	
	return TRUE;
}

/**
 * crank_vec_cplx_float_n_to_string:
 * @vec: Vector to string.
 *
 * Constructs string from vector. The strings are in form of,
 *
 *    (3 + (4i), 5 + (12i))
 *
 * Returns: (transfer full): string representation of value.
 */
gchar*
crank_vec_cplx_float_n_to_string (	CrankVecCplxFloatN*	vec	)
{
	return crank_vec_cplx_float_n_to_string_full (vec, "(", ", ", ")",
			CRANK_CPLX_FLOAT_DEFFORMAT);
}

/**
 * crank_vec_cplx_float_n_to_string_full:
 * @vec: Vector to string.
 * @left: Left string, which indicates that vector's start.
 * @in: Delimiter, which is inserted between elements.
 * @right: Right string. which indicates that vector's end.
 * @format: Format to use with elements.
 *
 * Construct string from vector, with given format.
 *
 * Returns: (transfer full): stringified items of value.
 */
gchar*
crank_vec_cplx_float_n_to_string_full (	CrankVecCplxFloatN*	vec,
										const gchar*	vec_left,
										const gchar*	vec_in,
										const gchar*	vec_right,
										const gchar*	format	)
{
	GString*	strb = g_string_new (vec_left);
	gchar*		result;
	
	guint		i;
	
	if (vec->n != 0) {
		g_string_append (strb,
				crank_cplx_float_to_string_full (vec->data + i, format));
		
		for (i = 1; i < vec->n; i++) {
			g_string_append (strb, vec_in);
			g_string_append (strb,
					crank_cplx_float_to_string_full (vec->data + i, format));
		}
	}
	g_string_append (strb, vec_right);
	
	result = strb->str;
	
	g_string_free (strb, FALSE);
	
	return result;
}


//////// Standard vector property ///////

/**
 * crank_vec_cplx_float_n_get_magn_sq:
 * @vec: A Vector.
 *
 * Gets square of magn/norm of @vec.
 *
 * Returns: square of magn/norm of @vec.
 */
gfloat
crank_vec_cplx_float_n_get_magn_sq	(	CrankVecCplxFloatN*	vec	)
{
	gfloat	result = 0;
	guint	i;
	
	for (i = 0; i < vec->n; i++)
		result += crank_cplx_float_get_norm_sq (vec->data + i);
	
	return result;
}

/**
 * crank_vec_cplx_float_n_get_magn:
 * @vec: A Vector.
 *
 * Gets magn/norm of @vec.
 *
 * Returns: magn/norm of @vec.
 */
gfloat
crank_vec_cplx_float_n_get_magn	(	CrankVecCplxFloatN*	vec	)
{
	gfloat sq = crank_vec_cplx_float_n_get_magn_sq (vec);
	return sqrtf (sq);
}




//////// Standard unary operations ////////

/**
 * crank_vec_cplx_float_n_neg:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Applies negation.
 */
void
crank_vec_cplx_float_n_neg (	CrankVecCplxFloatN*	a,
								CrankVecCplxFloatN*	r	)
{
	guint	i;
	
	if (a != r) crank_vec_cplx_float_n_realloc (r, a->n);
	
	for (i = 0; i < a->n; i++) crank_cplx_float_neg (a->data + i, r->data + i);
}


/**
 * crank_vec_cplx_float_n_unit:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_cplx_float_n_unit (	CrankVecCplxFloatN*	a,
								CrankVecCplxFloatN*	r	)
{
	crank_vec_cplx_float_n_divrs (a, crank_vec_cplx_float_n_get_magn (a), r);
}


//////// Scalar operations ////////

/**
 * crank_vec_cplx_float_n_muls:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_cplx_float_n_muls	(	CrankVecCplxFloatN*	a,
								CrankCplxFloat*		b,
								CrankVecCplxFloatN*	r	)
{
	guint	i;
	
	if (a != r) crank_vec_cplx_float_n_realloc (r, a->n);
	
	for (i = 0; i < a->n; i++) crank_cplx_float_mul (a->data + i, b, r->data + i);
}

/**
 * crank_vec_cplx_float_n_divs:
 * @a: A vector.
 * @b: A scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_cplx_float_n_divs	(	CrankVecCplxFloatN*	a,
								CrankCplxFloat*		b,
								CrankVecCplxFloatN*	r	)
{
	CrankCplxFloat	binv;
	
	crank_cplx_float_inverse (b, &binv);
	
	crank_vec_cplx_float_n_muls (a, &binv, r);
}

/**
 * crank_vec_cplx_float_n_mulrs:
 * @a: A vector.
 * @b: A real scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_cplx_float_n_mulrs	(	CrankVecCplxFloatN*	a,
									const gfloat		b,
									CrankVecCplxFloatN*	r	)
{
	guint	i;
	
	if (a != r) crank_vec_cplx_float_n_realloc (r, a->n);
	
	for (i = 0; i < a->n; i++) crank_cplx_float_mulr (a->data + i, b, r->data + i);
}

/**
 * crank_vec_cplx_float_n_divrs:
 * @a: A vector.
 * @b: A real scalar.
 * @r: (out): A vector to store result.
 *
 * Applies scalar division.
 */
void
crank_vec_cplx_float_n_divrs	(	CrankVecCplxFloatN*	a,
									const gfloat		b,
									CrankVecCplxFloatN*	r	)
{
	crank_vec_cplx_float_n_mulrs (a, 1.0f / b, r);
}


//////// Standard vector operations ////////

/**
 * crank_vec_cplx_float_n_add:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void			crank_vec_cplx_float_n_add			(	CrankVecCplxFloatN*	a,
													CrankVecCplxFloatN*	b,
													CrankVecCplxFloatN*	r	)
{
	if (a->n == b->n) {
		guint	i;
		
		if ((a != r) && (b != r)) crank_vec_cplx_float_n_realloc (r, a->n);
	
		for (i = 0; i < a->n; i++)
			crank_cplx_float_add (a->data + i, b->data + i, r->data + i);
	}
	else g_warning ("VecCplxFloatN: add: size mismatch: %u, %u", a->n, b->n);
}

/**
 * crank_vec_cplx_float_n_sub:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_cplx_float_n_sub	(	CrankVecCplxFloatN*	a,
							CrankVecCplxFloatN*	b,
							CrankVecCplxFloatN*	r	)
{
	if (a->n == b->n) {
		guint	i;
		
		if ((a != r) && (b != r)) crank_vec_cplx_float_n_realloc (r, a->n);
	
		for (i = 0; i < a->n; i++)
			crank_cplx_float_sub (a->data + i, b->data + i, r->data + i);
	}
	else g_warning ("VecCplxFloatN: sub: size mismatch: %u, %u", a->n, b->n);
}

/**
 * crank_vec_cplx_float_n_dot:
 * @a: A vector
 * @b: A vector
 * @r: (out): Dot product of two vectors.
 *
 * Gets dot product of two vectors.
 */
void
crank_vec_cplx_float_n_dot	(	CrankVecCplxFloatN*	a,
								CrankVecCplxFloatN*	b,
								CrankCplxFloat*		r	)
{	
	if (a->n == b->n) {
		guint	i;
	
		r->real = 0;
		r->imag = 0;
		for (i = 0; i < a->n; i++) {
			CrankCplxFloat	mul_conj;
			crank_cplx_float_mul_conj (a->data + i, b->data + i, &mul_conj);
			crank_cplx_float_add (r, &mul_conj, r);
		}
	}
	else g_warning ("VecCplxFloatN: dot: size mismatch: %u, %u", a->n, b->n);
}

//////// Component vector operations ////////

/**
 * crank_vec_cplx_float_n_cmpmul:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_cplx_float_n_cmpmul	(	CrankVecCplxFloatN*	a,
									CrankVecCplxFloatN*	b,
									CrankVecCplxFloatN*	r	)
{
	if (a->n == b->n) {
		guint	i;
		
		crank_vec_cplx_float_n_realloc (r, a->n);
	
		for (i = 0; i < a->n; i++)
			crank_cplx_float_mul (a->data + i, b->data + i, r->data + i);
	}
	else g_warning ("VecCplxFloatN: cmpmul: size mismatch: %u, %u", a->n, b->n);
}

/**
 * crank_vec_cplx_float_n_cmpdiv:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise division.
 */
void
crank_vec_cplx_float_n_cmpdiv	(	CrankVecCplxFloatN*	a,
									CrankVecCplxFloatN*	b,
									CrankVecCplxFloatN*	r	)
{
	if (a->n == b->n) {
		guint	i;
		
		crank_vec_cplx_float_n_realloc (r, a->n);
	
		for (i = 0; i < a->n; i++)
			crank_cplx_float_div (a->data + i, b->data + i, r->data + i);
	}
	else g_warning ("VecCplxFloatN: cmpdiv: size mismatch: %u, %u", a->n, b->n);
}
												
/**
 * crank_vec_cplx_float_n_cmpeq:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets each component of @a equals to counterpart of @b
 */
void
crank_vec_cplx_float_n_cmpeq	(	CrankVecCplxFloatN*	a,
									CrankVecCplxFloatN*	b,
									CrankVecBoolN*	r	)
{
	if (a->n == b->n) {
		guint	i;
		
		if (r->n != a->n) {
			r->data = g_renew (gboolean, r->data, a->n);
			r->n = a->n;
		}
	
		for (i = 0; i < a->n; i++)
			r->data[i] = crank_cplx_float_equal (a->data + i, b->data + i);
	}
	else g_warning ("VecCplxFloatN: cmpeq: size mismatch: %u, %u", a->n, b->n);
}



/**
 * crank_vec_cplx_float_n_mulrm:
 * @a: A vector.
 * @b: A Matrox.
 * @r: (out): A vector to store result.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_cplx_float_n_mulrm (	CrankVecCplxFloatN*	a,
								CrankMatFloatN*		b,
								CrankVecCplxFloatN*	r	)
{
  	if (a->n == b->rn) {
		guint	i;
	  	guint	j;
	  	CrankCplxFloat*	data;

	  	data = g_new0 (CrankCplxFloat, b->cn);

	  	for (i = 0; i < b->cn; i++) {
	  		for (j = 0; j < a->n; j++) {
	  			CrankCplxFloat	mul;
	  			crank_cplx_float_mulr (a->data + j, b->data[(b->cn * j) + i], &mul);
	  			crank_cplx_float_add (data + i, &mul, data + i);
	  		}
	  	}

	  	crank_vec_cplx_float_n_init_arr_take (r, b->cn, data);
	}
  	else g_warning ("VecCplxFloatN: mulrm: size mismatch: %u, %ux%u", a->n, b->rn, b->cn);
}	


/**
 * crank_vec_cplx_float_n_mixs:
 * @a: A vector.
 * @b: A vector.
 * @c: A scalar factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a * (1-c)) + (b * c)
 */
void
crank_vec_cplx_float_n_mixs (	CrankVecCplxFloatN*	a,
								CrankVecCplxFloatN*	b,
								const gfloat	c,
								CrankVecCplxFloatN*	r	)
{
	if (a->n == b->n) {
		guint	i;
		gfloat d = 1.0f - c;
		
		if ((a != r) && (b != r)) crank_vec_cplx_float_n_realloc (r, a->n);
	
		for (i = 0; i < a->n; i++) {
			r->data[i].real = a->data[i].real * d + b->data[i].real * c;
			r->data[i].imag = a->data[i].imag * d + b->data[i].imag * c;
		}
	}
	else g_warning ("VecCplxFloatN: min: size mismatch: %u, %u", a->n, b->n);
}


/**
 * crank_vec_cplx_float_n_mix:
 * @a: A vector.
 * @b: A vector.
 * @c: A factor.
 * @r: (out): A vector to store result.
 *
 * Gets linear interpolation of @a and @b by @c.
 * So the result will be
 *
 *    (a cmpmul c) + (b cmpmul ({1, 1, ..., 1} - c))
 */
void
crank_vec_cplx_float_n_mix (	CrankVecCplxFloatN*	a,
								CrankVecCplxFloatN*	b,
								CrankVecFloatN*	c,
								CrankVecCplxFloatN*	r	)
{
	if ((a->n == b->n) && (a->n == c->n)) {
		gfloat	d;
		guint	i;
		
		if ((a != r) && (b != r)) crank_vec_cplx_float_n_realloc (r, a->n);
	
		for (i = 0; i < a->n; i++) {
			crank_cplx_float_mix (a->data + i, b->data + i, c->data[i], r->data + i);
		}
	}
	else g_warning ("VecCplxFloatN: min: size mismatch: %u, %u, %u", a->n, b->n, c->n);
}
