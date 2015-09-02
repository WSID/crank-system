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
#include "crankmatcplxfloat.h"

/**
 * SECTION:crankveccplxfloat
 * @title: Complex Float Vectors
 * @short_description: Vectors with complex float components.
 * @usability: unstable
 * @include: crankbase.h
 *
 * Crank System provides complex float vectors for convenience.
 *
 * # Type Conversion
 *
 * <table><title>Type Conversion of #CrankVecCplxFloatN</title>
 *   <tgroup cols="3" align="left">
 *     <thead> <row> <entry>Type</entry>
 *                   <entry>Related Functions</entry>
 *                   <entry>Remarks</entry> </row> </thead>
 *     <tbody>
 *       <row> <entry>From #CrankVecBoolN </entry>
 *             <entry>crank_vec_cplx_float_n_init_from_vb() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry>From #CrankVecIntN </entry>
 *             <entry>crank_vec_cplx_float_n_init_from_vi() </entry>
 *             <entry>GValue Transform </entry> </row>
 *
 *       <row> <entry>From #CrankVecFloatN</entry>
 *             <entry>crank_vec_cplx_float_n_init_from_vf()</entry>
 *             <entry>GValue Transform</entry> </row>
 *
 *       <row> <entry morerows="1">To string.</entry>
 *             <entry>crank_vec_cplx_float_n_to_string()</entry>
 *             <entry>GValue Transform</entry> </row>
 *       <row> <entry>crank_vec_cplx_float_n_to_string_full()</entry> </row>
 *     </tbody>
 *   </tgroup>
 * </table>
 */



static void crank_vec_cplx_float_n_transform_from_vbn (	const GValue*	src,
														GValue*			dest );

static void crank_vec_cplx_float_n_transform_from_vin (	const GValue*	src,
														GValue*			dest );

static void crank_vec_cplx_float_n_transform_from_vfn (	const GValue*	src,
														GValue*			dest );


static void crank_vec_cplx_float_n_transform_to_string (const GValue*	src,
														GValue*			dest );
/**
 * CrankVecCplxFloatN:
 * @data: (array length=n): Array to store elements.
 * @n: size of data.
 *
 * Struct to point variable size of float vector.
 */
G_DEFINE_BOXED_TYPE_WITH_CODE (
		CrankVecCplxFloatN,
		crank_vec_cplx_float_n,
		crank_vec_cplx_float_n_dup,
		crank_vec_cplx_float_n_free,
		{

			g_value_register_transform_func (
					CRANK_TYPE_VEC_BOOL_N,
					g_define_type_id,
					crank_vec_cplx_float_n_transform_from_vbn );

			g_value_register_transform_func (
					CRANK_TYPE_VEC_INT_N,
					g_define_type_id,
					crank_vec_cplx_float_n_transform_from_vin );

			g_value_register_transform_func (
					CRANK_TYPE_VEC_FLOAT_N,
					g_define_type_id,
					crank_vec_cplx_float_n_transform_from_vfn );


			g_value_register_transform_func (
					g_define_type_id,
					G_TYPE_STRING,
					crank_vec_cplx_float_n_transform_to_string );
		}	)

//////// Private functions ////////


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
	
	CRANK_VEC_ALLOC(vec,CrankCplxFloat,n);
	
	for (i = 0; i < n; i++)		crank_cplx_float_copy (arr + i, vec->data + i);
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
{;
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
	
	CRANK_VEC_ALLOC(vec,CrankCplxFloat,n);
	
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
	
	CRANK_VEC_ALLOC(vec,CrankCplxFloat,n);
	
	for (i = 0; i < n; i++) crank_cplx_float_copy (fill, vec->data + i);
}


/**
 * crank_vec_cplx_float_n_init_uc:
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
crank_vec_cplx_float_n_init_uc	(	CrankVecCplxFloatN*	vec,
									const guint		n,
									...	)
{
	va_list	varargs;
	
	va_start (varargs, n);
	
	crank_vec_cplx_float_n_init_valistuc (vec, n, varargs);
	
	va_end (varargs);
}

/**
 * crank_vec_cplx_float_n_init_valistuc:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @varargs: va_list that contains elements.
 *
 * Initializes vector with given array.
 */
void
crank_vec_cplx_float_n_init_valistuc	(	CrankVecCplxFloatN*	vec,
											const guint		n,
											va_list			varargs	)
{
	guint	i;
	
	CRANK_VEC_ALLOC(vec,CrankCplxFloat,n);
	
	for (i = 0; i < n; i++)
		crank_cplx_float_init_valist (vec->data + i, varargs);
}

/**
 * crank_vec_cplx_float_n_init_ucarr:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @real: (array length=n): An array of real entities.
 * @imag: (array length=n): An array of imaginary entities.
 *
 * Initialize vector with given two arrays, one for real, the other for
 * imaginary.
 */
void
crank_vec_cplx_float_n_init_ucarr (CrankVecCplxFloatN*	vec,
								   const guint			n,
								   const gfloat*		real,
								   const gfloat*		imag )
{
  guint i;

  CRANK_VEC_ALLOC (vec, CrankCplxFloat, n);

  for (i = 0; i < n; i++)	crank_cplx_float_init (vec->data + i, real[i], imag[i]);
}

/**
 * crank_vec_cplx_float_n_init_arruc:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @arr: (array): An array of @n pairs of (real, imag) float values.
 *
 * Initialize vector with given an array of pairs.
 *
 * Difference to crank_vec_cplx_float_n_init_arr_uc() is, this function receives
 * a single array, rather than 2 arrays.
 */
void
crank_vec_cplx_float_n_init_arruc (CrankVecCplxFloatN* vec,
								   const guint			n,
								   const gfloat*		arr )
{
  guint i;

  CRANK_VEC_ALLOC (vec, CrankCplxFloat, n);

  for (i = 0; i < n; i++)
	crank_cplx_float_init (vec->data + i, arr[2*i], arr[2*i + 1]);
}

/**
 * crank_vec_cplx_float_n_init_fill_uc:
 * @vec: (out): Vector to initialize.
 * @n: Size of vector.
 * @real: real part of element to fill @vec
 * @imag: imaginary part of element to fill @vec
 *
 * Initializes vector by filling single value.
 */
void
crank_vec_cplx_float_n_init_fill_uc	(CrankVecCplxFloatN* vec,
									 const guint		 n,
									 const gfloat		 real,
									 const gfloat		 imag	)
{
  guint	i;

  CRANK_VEC_ALLOC(vec,CrankCplxFloat,n);

  for (i = 0; i < n; i++) crank_cplx_float_init (vec->data + i, real, imag);
}

/**
 * crank_vec_cplx_float_n_init_ucv:
 * @vec: (out): Vector to initialize.
 * @real: Real part of vector.
 * @imag: Imaginary part of vector.
 *
 * Initialize vector from given two vectors, one for real, the other for imaginary.
 * If one is smaller than other, the result vector will have same length as longer
 * part and missing parts will be filled with 0.
 */
void
crank_vec_cplx_float_n_init_ucv (CrankVecCplxFloatN*	vec,
								 CrankVecFloatN*		real,
								 CrankVecFloatN*		imag	)
{
  guint i;
  guint n;

  n = MAX (real != NULL ? real->n : 0,
		   imag != NULL ? imag->n : 0);

  CRANK_VEC_ALLOC0(vec, CrankCplxFloat, n);

  for (i = 0; i < real->n; i++)	vec->data[i].real = real->data[i];
  for (i = 0; i < imag->n; i++)	vec->data[i].imag = imag->data[i];
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
	
	CRANK_VEC_ALLOC(vec,CrankCplxFloat,vb->n);
	
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
	
	CRANK_VEC_ALLOC(vec,CrankCplxFloat,vi->n);
	
	for (i = 0; i < vi->n; i++)
		crank_cplx_float_init (vec->data + i,
				vi->data[i],
				0);
}

/**
 * crank_vec_cplx_float_n_init_from_vf:
 * @vec: (out): Vector to initialize.
 * @vf: A Float vector.
 *
 * Initialize vector from integer vector.
 */
void
crank_vec_cplx_float_n_init_from_vf	(	CrankVecCplxFloatN*	vec,
										CrankVecFloatN*	vf		)
{
	guint	i;

	CRANK_VEC_ALLOC(vec,CrankCplxFloat,vf->n);

	for (i = 0; i < vf->n; i++)
		crank_cplx_float_init (vec->data + i,
				vf->data[i],
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

//////// Classification ////////////////////////////////////////////////////////

/**
 * crank_vec_cplx_float_n_is_zero:
 * @vec: A Vector
 *
 * Checks whether the vector is "Zero Vector", whose all components are 0.
 *
 * Returns: Whether the vector has all components as 0.
 */
gboolean
crank_vec_cplx_float_n_is_zero	(	CrankVecCplxFloatN*	vec	)
{
	guint	i;
	
	for (i = 0; i < vec->n; i++) {
		if (! crank_cplx_float_is_zero (vec->data + i)) return FALSE;
	}
	return TRUE;
}

/**
 * crank_vec_cplx_float_n_is_one:
 * @vec: A Vector.
 *
 * Check whether the vector has all components as 1.
 *
 * Returns: Whether the vector has all components as 1.
 */
gboolean
crank_vec_cplx_float_n_is_one	(	CrankVecCplxFloatN*	vec	)
{
	guint	i;
	
	for (i = 0; i < vec->n; i++) {
		if (! crank_cplx_float_is_one (vec->data + i)) return FALSE;
	}
	return TRUE;
}

/**
 * crank_vec_cplx_float_n_is_unit:
 * @vec: A Vector.
 *
 * Check whether the vector is unit vector.
 *
 * Returns: whether the vector is unit vector.
 */
gboolean
crank_vec_cplx_float_n_is_unit	(	CrankVecCplxFloatN*	vec	)
{
	gfloat magnsq = crank_vec_cplx_float_n_get_magn_sq (vec);
	
	return (0.9999f <= magnsq) && (1.0001f <= magnsq);
}

/**
 * crank_vec_cplx_float_n_is_empty:
 * @vec: A Vector.
 *
 * Checks whether the vector is empty vector.
 *
 * Returns: Whether the vector is empty.
 */
gboolean
crank_vec_cplx_float_n_is_empty	(	CrankVecCplxFloatN*	vec	)
{
	return vec->n == 0;
}

/**
 * crank_vec_cplx_float_n_is_pure_real:
 * @vec: A Vector.
 *
 * Checks a vector is a real vector, whose all component has 0 imaginary part.
 *
 * Returns: Whether a vector is pure real.
 */
gboolean
crank_vec_cplx_float_n_is_pure_real	(	CrankVecCplxFloatN*	vec	)
{
	guint	i;
	
	for (i = 0; i < vec->n; i++) {
		if (! crank_cplx_float_is_pure_real (vec->data + i)) return FALSE;
	}
	return TRUE;
}

/**
 * crank_vec_cplx_float_n_is_pure_imag:
 * @vec: A Vector.
 *
 * Checks a vector is a pure imaginary vector, whose all component has 0 real
 * part.
 *
 * Returns: Whether a vector is pure imaginary.
 */
gboolean
crank_vec_cplx_float_n_is_pure_imag	(	CrankVecCplxFloatN*	vec	)
{
	guint	i;
	
	for (i = 0; i < vec->n; i++) {
		if (! crank_cplx_float_is_pure_imag (vec->data + i)) return FALSE;
	}
	return TRUE;
}

/**
 * crank_vec_cplx_float_n_has_nan:
 * @vec: A Vector
 *
 * Check a vector has NaN in either real and imaginary part.
 *
 * Returns: Whether a vector has NaN.
 */
gboolean
crank_vec_cplx_float_n_has_nan (	CrankVecCplxFloatN*	vec	)
{
	guint	i;
	
	for (i = 0; i < vec->n; i++) {
		if (crank_cplx_float_has_nan (vec->data + i)) return TRUE;
	}
	return FALSE;
}

/**
 * crank_vec_cplx_float_n_has_inf:
 * @vec: A Vector
 *
 * Check a vector has infinity in either real and imaginary part.
 *
 * Returns: Whether a vector has infinity.
 */
gboolean
crank_vec_cplx_float_n_has_inf	(	CrankVecCplxFloatN*	vec	)
{
	guint	i;
	
	for (i = 0; i < vec->n; i++) {
		if (crank_cplx_float_has_inf (vec->data + i)) return TRUE;
	}
	return FALSE;
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

/**
 * crank_vec_cplx_float_n_get_real:
 * @vec: A Vector
 * @real: (out): A vector.
 *
 * Gets real part of vector.
 */
void
crank_vec_cplx_float_n_get_real (	CrankVecCplxFloatN*	vec,
									CrankVecFloatN*		real	)
{
	guint	i;

	CRANK_VEC_ALLOC (real, gfloat, vec->n);
	for (i = 0; i < vec->n; i++)	real->data[i] = vec->data[i].real;
}

/**
 * crank_vec_cplx_float_n_get_imag:
 * @vec: A Vector
 * @imag: (out): A vector.
 *
 * Gets real part of vector.
 */
void
crank_vec_cplx_float_n_get_imag (	CrankVecCplxFloatN*	vec,
									CrankVecFloatN*		imag	)
{
	guint	i;

	CRANK_VEC_ALLOC (imag, gfloat, vec->n);
	for (i = 0; i < vec->n; i++)	imag->data[i] = vec->data[i].imag;
}

/**
 * crank_vec_cplx_float_n_set_real:
 * @vec: A Vector
 * @real: A vector.
 *
 * Sets real part of vector.
 */
void
crank_vec_cplx_float_n_set_real (	CrankVecCplxFloatN*	vec,
									CrankVecFloatN*		real	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2("VecCplxFloatN", "set-real", vec, real);
	for (i = 0; i < vec->n; i++)	vec->data[i].real = real->data[i];
}

/**
 * crank_vec_cplx_float_n_set_imag:
 * @vec: A Vector
 * @imag: A vector.
 *
 * Sets real part of vector.
 */
void
crank_vec_cplx_float_n_set_imag (	CrankVecCplxFloatN*	vec,
									CrankVecFloatN*		imag	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "set-imag", vec, imag);
	for (i = 0; i < vec->n; i++)	vec->data[i].imag = imag->data[i];
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
	
	CRANK_VEC_ALLOC(r,CrankCplxFloat,a->n);
	
	for (i = 0; i < a->n; i++) crank_cplx_float_neg (a->data + i, r->data + i);
}

/**
 * crank_vec_cplx_float_n_neg_self:
 * @a: A vector
 *
 * Applies negation.
 */
void
crank_vec_cplx_float_n_neg_self (	CrankVecCplxFloatN*	a	)
{
	guint	i;

	for (i = 0; i < a->n; i++) crank_cplx_float_neg_self (a->data + i);
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

/**
 * crank_vec_cplx_float_n_unit_self:
 * @a: A vector
 *
 * Gets unit length of vector with same direction of @a
 */
void
crank_vec_cplx_float_n_unit_self (	CrankVecCplxFloatN*	a	)
{
	crank_vec_cplx_float_n_divrs_self (a, crank_vec_cplx_float_n_get_magn (a));
}

/**
 * crank_vec_cplx_float_n_conjugate:
 * @a: A vector
 * @r: (out): A vector to store result.
 *
 * Gets conjugation of vector.
 */
void
crank_vec_cplx_float_n_conjugate (	CrankVecCplxFloatN*	a,
								CrankVecCplxFloatN*	r	)
{
	guint	i;

	CRANK_VEC_ALLOC(r,CrankCplxFloat,a->n);

	for (i = 0; i < a->n; i++) crank_cplx_float_conjugate (a->data + i, r->data + i);
}

/**
 * crank_vec_cplx_float_n_conjugate_self:
 * @a: A vector
 *
 * Gets conjugation of vector.
 */
void
crank_vec_cplx_float_n_conjugate_self (	CrankVecCplxFloatN*	a	)
{
	guint	i;
	
	for (i = 0; i < a->n; i++) crank_cplx_float_conjugate_self (a->data + i);
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
	
	g_return_if_fail (a != r);
	CRANK_VEC_ALLOC(r,CrankCplxFloat,a->n);
	
	for (i = 0; i < a->n; i++) crank_cplx_float_mul (a->data + i, b, r->data + i);
}

/**
 * crank_vec_cplx_float_n_muls_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_cplx_float_n_muls_self	(	CrankVecCplxFloatN*	a,
										CrankCplxFloat*		b	)
{
	guint	i;
	for (i = 0; i < a->n; i++) crank_cplx_float_mul_self (a->data + i, b);
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
	
	g_return_if_fail (a != r);
	CRANK_VEC_ALLOC(r, CrankCplxFloat, a->n);
	
	for (i = 0; i < a->n; i++) crank_cplx_float_mulr (a->data + i, b, r->data + i);
}

/**
 * crank_vec_cplx_float_n_mulrs_self:
 * @a: A vector.
 * @b: A real scalar.
 *
 * Applies scalar multiplication.
 */
void
crank_vec_cplx_float_n_mulrs_self	(	CrankVecCplxFloatN*	a,
										const gfloat		b	)
{
	guint	i;

	for (i = 0; i < a->n; i++) crank_cplx_float_mulr_self (a->data + i, b);
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

	g_return_if_fail (a != r);
	crank_cplx_float_inverse (b, &binv);

	crank_vec_cplx_float_n_muls (a, &binv, r);
}

/**
 * crank_vec_cplx_float_n_divs_self:
 * @a: A vector.
 * @b: A scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_cplx_float_n_divs_self	(	CrankVecCplxFloatN*	a,
										CrankCplxFloat*		b	)
{
	CrankCplxFloat	binv;
	
	crank_cplx_float_inverse (b, &binv);
	crank_vec_cplx_float_n_muls_self (a, &binv);
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
	g_return_if_fail (a != r);
	crank_vec_cplx_float_n_mulrs (a, 1.0f / b, r);
}

/**
 * crank_vec_cplx_float_n_divrs_self:
 * @a: A vector.
 * @b: A real scalar.
 *
 * Applies scalar division.
 */
void
crank_vec_cplx_float_n_divrs_self	(	CrankVecCplxFloatN*	a,
										const gfloat		b	)
{
	crank_vec_cplx_float_n_mulrs_self (a, 1.0f / b);
}



//////// Standard vector operations ////////
/**
 * crank_vec_cplx_float_n_addr:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Adds two vectors.
 */
void
crank_vec_cplx_float_n_addr		(	CrankVecCplxFloatN*	a,
									CrankVecFloatN*		b,
									CrankVecCplxFloatN*	r	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "addr", a, b);
	CRANK_VEC_ALLOC(r, CrankCplxFloat, a->n);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_addr (a->data + i, b->data[i], r->data + i);
}

/**
 * crank_vec_cplx_float_n_addr_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_cplx_float_n_addr_self	(	CrankVecCplxFloatN*	a,
										CrankVecFloatN*		b	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "addr-self", a, b);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_addr_self (a->data + i, b->data[i]);
}

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
	guint	i;

	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "add", a, b);
	CRANK_VEC_ALLOC(r, CrankCplxFloat, a->n);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_add (a->data + i, b->data + i, r->data + i);
}

/**
 * crank_vec_cplx_float_n_add_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Adds two vectors.
 */
void
crank_vec_cplx_float_n_add_self	(	CrankVecCplxFloatN*	a,
									CrankVecCplxFloatN*	b	)
{
	guint	i;
	
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "add-self", a, b);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_add_self (a->data + i, b->data + i);
}


/**
 * crank_vec_cplx_float_n_subr:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_cplx_float_n_subr	(	CrankVecCplxFloatN*	a,
								CrankVecFloatN*		b,
								CrankVecCplxFloatN*	r	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "subr", a, b);
	CRANK_VEC_ALLOC (r, CrankCplxFloat, a->n);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_subr (a->data + i, b->data[i], r->data + i);
}

/**
 * crank_vec_cplx_float_n_subr_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_cplx_float_n_subr_self	(	CrankVecCplxFloatN*	a,
										CrankVecFloatN*		b	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "subr-self", a, b);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_subr_self (a->data + i, b->data[i]);
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
	guint	i;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "sub", a, b);
	CRANK_VEC_ALLOC (r, CrankCplxFloat, a->n);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_sub (a->data + i, b->data + i, r->data + i);
}

/**
 * crank_vec_cplx_float_n_sub_self:
 * @a: A vector.
 * @b: A vector.
 *
 * Subtracts @a by @b.
 */
void
crank_vec_cplx_float_n_sub_self	(	CrankVecCplxFloatN*	a,
									CrankVecCplxFloatN*	b	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "sub-self", a, b);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_sub_self (a->data + i, b->data + i);
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
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "dot", a, b);

	r->real = 0;
	r->imag = 0;
	for (i = 0; i < a->n; i++) {
		CrankCplxFloat	mul_conj;
		crank_cplx_float_mul_conj (a->data + i, b->data + i, &mul_conj);
		crank_cplx_float_add_self (r, &mul_conj);
	}
}

//////// Component vector operations ////////
/**
 * crank_vec_cplx_float_n_cmpmulr:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_cplx_float_n_cmpmulr	(	CrankVecCplxFloatN*	a,
									CrankVecFloatN*		b,
									CrankVecCplxFloatN*	r	)
{
	guint	i;
		
	g_return_if_fail (a != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpmulr", a, b);
	CRANK_VEC_ALLOC (r, CrankCplxFloat, a->n);
	
	for (i = 0; i < a->n; i++)
		crank_cplx_float_mulr (a->data + i, b->data[i], r->data + i);
}

/**
 * crank_vec_cplx_float_n_cmpmulr_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_cplx_float_n_cmpmulr_self	(	CrankVecCplxFloatN*	a,
										CrankVecFloatN*		b	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpmulr-self", a, b);
	for (i = 0; i < a->n; i++)
		crank_cplx_float_mulr_self (a->data + i, b->data[i]);
}

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
	guint	i;

	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpmul", a, b);
	CRANK_VEC_ALLOC (r, CrankCplxFloat, a->n);
	
	for (i = 0; i < a->n; i++)
		crank_cplx_float_mul (a->data + i, b->data + i, r->data + i);
}

/**
 * crank_vec_cplx_float_n_cmpmul_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise multiplication.
 */
void
crank_vec_cplx_float_n_cmpmul_self	(	CrankVecCplxFloatN*	a,
										CrankVecCplxFloatN*	b	)
{
	guint	i;
	
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpmul-self", a, b);
	for (i = 0; i < a->n; i++)
		crank_cplx_float_mul_self (a->data + i, b->data + i);
}

/**
 * crank_vec_cplx_float_n_cmpdivr:
 * @a: A vector.
 * @b: A vector.
 * @r: (out): A vector to store result.
 * 
 * Gets component-wise division.
 */
void
crank_vec_cplx_float_n_cmpdivr	(	CrankVecCplxFloatN*	a,
									CrankVecFloatN*		b,
									CrankVecCplxFloatN*	r	)
{
	guint	i;

	g_return_if_fail (a != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpdivr", a, b);
	CRANK_VEC_ALLOC (r, CrankCplxFloat, a->n);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_divr (a->data + i, b->data[i], r->data + i);
}

/**
 * crank_vec_cplx_float_n_cmpdivr_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise division.
 */
void
crank_vec_cplx_float_n_cmpdivr_self	(	CrankVecCplxFloatN*	a,
										CrankVecFloatN*		b	)
{
	guint	i;

	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpdivr-self", a, b);
	for (i = 0; i < a->n; i++)
		crank_cplx_float_divr_self (a->data + i, b->data[i]);
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
	guint	i;

	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpdiv", a, b);
	CRANK_VEC_ALLOC (r, CrankCplxFloat, a->n);

	for (i = 0; i < a->n; i++)
		crank_cplx_float_div (a->data + i, b->data + i, r->data + i);
}

/**
 * crank_vec_cplx_float_n_cmpdiv_self:
 * @a: A vector.
 * @b: A vector.
 * 
 * Gets component-wise division.
 */
void
crank_vec_cplx_float_n_cmpdiv_self	(	CrankVecCplxFloatN*	a,
										CrankVecCplxFloatN*	b	)
{
	guint	i;
	
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpdiv-self", a, b);
	for (i = 0; i < a->n; i++)
		crank_cplx_float_div_self (a->data + i, b->data + i);
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
	
	guint	i;
		
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "cmpeq", a, b);
	CRANK_VEC_ALLOC(r, gboolean, a->n);

	for (i = 0; i < a->n; i++)
		r->data[i] = crank_cplx_float_equal (a->data + i, b->data + i);
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
	g_return_if_fail (a != r);
  	if (a->n == b->rn) {
		guint	i;
	  	guint	j;
	  	CrankCplxFloat*	data;

	  	data = g_new0 (CrankCplxFloat, b->cn);

	  	for (i = 0; i < b->cn; i++) {
	  		for (j = 0; j < a->n; j++) {
	  			CrankCplxFloat	mul;
	  			crank_cplx_float_mulr (a->data + j, b->data[(b->cn * j) + i], &mul);
	  			crank_cplx_float_add_self (data + i, &mul);
	  		}
	  	}

	  	crank_vec_cplx_float_n_init_arr_take (r, b->cn, data);
	}
  	else g_warning ("VecCplxFloatN: mulrm: size mismatch: %u, %ux%u", a->n, b->rn, b->cn);
}	

/**
 * crank_vec_cplx_float_n_mulrm_self:
 * @a: A vector.
 * @b: A Matrox.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_cplx_float_n_mulrm_self (	CrankVecCplxFloatN*	a,
									CrankMatFloatN*		b	)
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
	  			crank_cplx_float_add_self (data + i, &mul);
	  		}
	  	}

		g_free (a->data);
	  	crank_vec_cplx_float_n_init_arr_take (a, b->cn, data);
	}
  	else g_warning ("VecCplxFloatN: mulrm-self: size mismatch: %u, %ux%u", a->n, b->rn, b->cn);
}	

/**
 * crank_vec_cplx_float_n_mulm:
 * @a: A vector.
 * @b: A Matrox.
 * @r: (out): A vector to store result.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_cplx_float_n_mulm (	CrankVecCplxFloatN*	a,
								CrankMatCplxFloatN*	b,
								CrankVecCplxFloatN*	r	)
{
	g_return_if_fail (a != r);

  	if (a->n == b->rn) {
		guint	i;
	  	guint	j;
	  	CrankCplxFloat*	data;

	  	data = g_new0 (CrankCplxFloat, b->cn);

	  	for (i = 0; i < b->cn; i++) {
	  		for (j = 0; j < a->n; j++) {
	  			CrankCplxFloat	mul;
	  			crank_cplx_float_mul (a->data + j, b->data + (b->cn * j) + i, &mul);
	  			crank_cplx_float_add_self (data + i, &mul);
	  		}
	  	}

	  	crank_vec_cplx_float_n_init_arr_take (r, b->cn, data);
	}
  	else g_warning ("VecCplxFloatN: mulm: size mismatch: %u, %ux%u", a->n, b->rn, b->cn);
}	

/**
 * crank_vec_cplx_float_n_mulm_self:
 * @a: A vector.
 * @b: A Matrox.
 *
 * Multiplies transpose of vector by matrix. (Vector transpose * Matrix)
 */
void
crank_vec_cplx_float_n_mulm_self (	CrankVecCplxFloatN*	a,
									CrankMatCplxFloatN*	b	)
{
  	if (a->n == b->rn) {
		guint	i;
	  	guint	j;
	  	CrankCplxFloat*	data;

	  	data = g_new0 (CrankCplxFloat, b->cn);

	  	for (i = 0; i < b->cn; i++) {
	  		for (j = 0; j < a->n; j++) {
	  			CrankCplxFloat	mul;
	  			crank_cplx_float_mul (a->data + j, b->data + (b->cn * j) + i, &mul);
	  			crank_cplx_float_add_self (data + i, &mul);
	  		}
	  	}

		g_free (a->data);
	  	crank_vec_cplx_float_n_init_arr_take (a, b->cn, data);
	}
  	else g_warning ("VecCplxFloatN: mulm-self: size mismatch: %u, %ux%u", a->n, b->rn, b->cn);
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
	guint	i;
	gfloat d = 1.0f - c;
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH2 ("VecCplxFloatN", "mix-scalar", a, b);
	CRANK_VEC_ALLOC (r, CrankCplxFloat, a->n);

	for (i = 0; i < a->n; i++) {
		r->data[i].real = a->data[i].real * d + b->data[i].real * c;
		r->data[i].imag = a->data[i].imag * d + b->data[i].imag * c;
	}
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
	gfloat	d;
	guint	i;	
	
	g_return_if_fail (a != r);
	g_return_if_fail (b != r);
	CRANK_VEC_WARN_IF_SIZE_MISMATCH3 ("VecCplxFloatN", "mix-scalar", a, b, c);
	CRANK_VEC_ALLOC (r, CrankCplxFloat, a->n);

	for (i = 0; i < a->n; i++) {
		crank_cplx_float_mix (a->data + i, b->data + i, c->data[i], r->data + i);
	}
}


//////// GValue Transform //////////////////////////////////////////////////////


static void
crank_vec_cplx_float_n_transform_from_vbn (	const GValue*	src,
											GValue*			dest )
{
	CrankVecCplxFloatN*	res = g_new (CrankVecCplxFloatN, 1);

	crank_vec_cplx_float_n_init_from_vb (
			res,
			(CrankVecBoolN*) g_value_get_boxed (src) );

	g_value_take_boxed (dest, res);
}

static void
crank_vec_cplx_float_n_transform_from_vin (	const GValue*	src,
											GValue*			dest )

{
	CrankVecCplxFloatN*	res = g_new (CrankVecCplxFloatN, 1);

	crank_vec_cplx_float_n_init_from_vi (
			res,
			(CrankVecIntN*) g_value_get_boxed (src) );

	g_value_take_boxed (dest, res);
}

static void
crank_vec_cplx_float_n_transform_from_vfn (	const GValue*	src,
											GValue*			dest )
{
	CrankVecCplxFloatN*	res = g_new (CrankVecCplxFloatN, 1);

	crank_vec_cplx_float_n_init_from_vf (
			res,
			(CrankVecFloatN*) g_value_get_boxed (src) );

	g_value_take_boxed (dest, res);
}


static void
crank_vec_cplx_float_n_transform_to_string (const GValue*	src,
											GValue*			dest )
{
	g_value_take_string (dest,
		crank_vec_cplx_float_n_to_string (
			(CrankVecCplxFloatN*) g_value_get_boxed (dest) ) );
}
