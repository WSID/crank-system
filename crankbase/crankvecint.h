#ifndef CRANKVECINT_H
#define CRANKVECINT_H

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
#error crankvecint.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankfunction.h"
#include "crankveccommon.h"

G_BEGIN_DECLS

/**
 * CrankVecInt2:
 * @x: First element.
 * @y: Second element.
 *
 * integer vector. Compared to ivec2 in GLSL.
 */
struct _CrankVecInt2 {
	gint	x;
	gint	y;
};

#define CRANK_TYPE_VEC_INT2	(crank_vec_int2_get_type ())
GType			crank_vec_int2_get_type	(void);

/**
 * CRANK_VEC_INT2_0:
 * 
 * Zero vector initializing list.
 */
#define CRANK_VEC_INT2_0	{0, 0}

/**
 * CRANK_VEC_INT2_I:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT2_I	{1, 0}

/**
 * CRANK_VEC_INT2_J:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT2_J	{0, 1)

void			crank_vec_int2_init			(	CrankVecInt2*	vec,
												gint			x,
												gint			y	);

void			crank_vec_int2_init_arr		(	CrankVecInt2*	vec,
												gint*			arr	);

void			crank_vec_int2_init_valist	(	CrankVecInt2*	vec,
												va_list			varargs	);

void			crank_vec_int2_init_fill	(	CrankVecInt2*	vec,
												gint			fill	);
												
void			crank_vec_int2_init_from_vb (	CrankVecInt2*	vec,
												CrankVecBool2*	vb		);

void			crank_vec_int2_copy			(	CrankVecInt2*	vec,
							  					CrankVecInt2*	other	);

CrankVecInt2*	crank_vec_int2_dup			(	CrankVecInt2*	vec	);

gint			crank_vec_int2_get			(	CrankVecInt2*	vec,
												const guint		index	);

void			crank_vec_int2_set			(	CrankVecInt2*	vec,
												const guint		index,
												const gint		value	);

gboolean		crank_vec_int2_foreach		(	CrankVecInt2*		vec,
												CrankBoolIntFunc	func,
												gpointer			userdata	);
												
void			crank_vec_int2_iterator 	(	CrankVecInt2*		vec,
												CrankIterMemInt*	iter	);

//////// Basic operation ////////

guint			crank_vec_int2_hash (			gconstpointer	a	);

gboolean		crank_vec_int2_equal (			gconstpointer	a,
												gconstpointer	b	);

gchar*			crank_vec_int2_to_string (		CrankVecInt2*	vec	);

gchar*			crank_vec_int2_to_string_full (	CrankVecInt2*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	format	);


//////// Standard vector property ///////

guint			crank_vec_int2_get_magn_sq		(	CrankVecInt2*	vec	);

gfloat			crank_vec_int2_get_magn			(	CrankVecInt2*	vec	);


//////// Standard unary operations ////////

void			crank_vec_int2_neg			(	CrankVecInt2*	a,
												CrankVecInt2*	r	);

void			crank_vec_int2_neg_self		(	CrankVecInt2*	a	);

//////// Scalar operations ////////

void			crank_vec_int2_muls			(	CrankVecInt2*	a,
												const gint		b,
												CrankVecInt2*	r	);

void			crank_vec_int2_divs			(	CrankVecInt2*	a,
												const gint		b,
												CrankVecInt2*	r	);

void			crank_vec_int2_mods			(	CrankVecInt2*	a,
												const gint		b,
												CrankVecInt2*	r	);

void			crank_vec_int2_muls_self	(	CrankVecInt2*	a,
												const gint		b	);

void			crank_vec_int2_divs_self	(	CrankVecInt2*	a,
												const gint		b	);

void			crank_vec_int2_mods_self	(	CrankVecInt2*	a,
												const gint		b	);


//////// Standard vector operations ////////

void			crank_vec_int2_add			(	CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecInt2*	r	);

void			crank_vec_int2_sub			(	CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecInt2*	r	);

gint			crank_vec_int2_dot			(	CrankVecInt2*	a,
												CrankVecInt2*	b	);

void			crank_vec_int2_add_self		(	CrankVecInt2*	a,
												CrankVecInt2*	b	);

void			crank_vec_int2_sub_self		(	CrankVecInt2*	a,
												CrankVecInt2*	b	);

//////// Component vector operations ////////

void			crank_vec_int2_cmpmul		(	CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecInt2*	r	);
												
void			crank_vec_int2_cmpdiv		(	CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecInt2*	r	);

void			crank_vec_int2_cmpmod		(	CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecInt2*	r	);

void			crank_vec_int2_cmpless		(	CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecBool2*	r	);
												
void			crank_vec_int2_cmpeq		(	CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecBool2*	r	);
												
void			crank_vec_int2_cmpgreater	(	CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecBool2*	r	);
												
void			crank_vec_int2_cmpcmp	(		CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecInt2*	r	);

void			crank_vec_int2_min	(			CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecInt2*	r	);

void			crank_vec_int2_max	(			CrankVecInt2*	a,
												CrankVecInt2*	b,
												CrankVecInt2*	r	);

void			crank_vec_int2_cmpmul_self	(	CrankVecInt2*	a,
												CrankVecInt2*	b	);
												
void			crank_vec_int2_cmpdiv_self	(	CrankVecInt2*	a,
												CrankVecInt2*	b	);

void			crank_vec_int2_cmpmod_self	(	CrankVecInt2*	a,
												CrankVecInt2*	b	);





/**
 * CrankVecInt3:
 * @x: First element.
 * @y: Second element.
 * @z: Third element.
 *
 * integer vector. Compared to ivec3 in GLSL.
 */
struct _CrankVecInt3 {
	gint	x;
	gint	y;
	gint	z;
};

#define CRANK_TYPE_VEC_INT3	(crank_vec_int3_get_type ())
GType			crank_vec_int3_get_type	(void);

/**
 * CRANK_VEC_INT3_0:
 * 
 * Zero vector initializing list.
 */
#define CRANK_VEC_INT3_0	{0, 0, 0}

/**
 * CRANK_VEC_INT3_I:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT3_I	{1, 0, 0}

/**
 * CRANK_VEC_INT3_J:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT3_J	{0, 1, 0)

/**
 * CRANK_VEC_INT3_k:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT3_k	{0, 0, 1)

void			crank_vec_int3_init			(	CrankVecInt3*	vec,
												gint			x,
												gint			y,
												gint			z	);

void			crank_vec_int3_init_arr		(	CrankVecInt3*	vec,
												gint*			arr	);

void			crank_vec_int3_init_valist	(	CrankVecInt3*	vec,
												va_list			varargs	);

void			crank_vec_int3_init_fill	(	CrankVecInt3*	vec,
												gint			fill	);
												
void			crank_vec_int3_init_from_vb (	CrankVecInt3*	vec,
												CrankVecBool3*	vb		);

void			crank_vec_int3_copy			(	CrankVecInt3*	vec,
							  					CrankVecInt3*	other	);

CrankVecInt3*	crank_vec_int3_dup			(	CrankVecInt3*	vec	);

gint			crank_vec_int3_get			(	CrankVecInt3*	vec,
												const guint		index	);

void			crank_vec_int3_set			(	CrankVecInt3*	vec,
												const guint		index,
												const gint		value	);

gboolean		crank_vec_int3_foreach		(	CrankVecInt3*		vec,
												CrankBoolIntFunc	func,
												gpointer			userdata	);
												
void			crank_vec_int3_iterator 	(	CrankVecInt3*		vec,
												CrankIterMemInt*	iter	);

//////// Basic operation ////////

guint			crank_vec_int3_hash (			gconstpointer	a	);

gboolean		crank_vec_int3_equal (			gconstpointer	a,
												gconstpointer	b	);

gchar*			crank_vec_int3_to_string (		CrankVecInt3*	vec	);

gchar*			crank_vec_int3_to_string_full (	CrankVecInt3*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	format	);


//////// Standard vector property ///////

guint			crank_vec_int3_get_magn_sq		(	CrankVecInt3*	vec	);

gfloat			crank_vec_int3_get_magn			(	CrankVecInt3*	vec	);


//////// Standard unary operations ////////

void			crank_vec_int3_neg			(	CrankVecInt3*	a,
												CrankVecInt3*	r	);

void			crank_vec_int3_neg_self		(	CrankVecInt3*	a	);


//////// Scalar operations ////////

void			crank_vec_int3_muls			(	CrankVecInt3*	a,
												const gint		b,
												CrankVecInt3*	r	);

void			crank_vec_int3_divs			(	CrankVecInt3*	a,
												const gint		b,
												CrankVecInt3*	r	);

void			crank_vec_int3_mods			(	CrankVecInt3*	a,
												const gint		b,
												CrankVecInt3*	r	);

void			crank_vec_int3_muls_self	(	CrankVecInt3*	a,
												const gint		b	);

void			crank_vec_int3_divs_self	(	CrankVecInt3*	a,
												const gint		b	);

void			crank_vec_int3_mods_self	(	CrankVecInt3*	a,
												const gint		b	);


//////// Standard vector operations ////////

void			crank_vec_int3_add			(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);

void			crank_vec_int3_sub			(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);

gint			crank_vec_int3_dot			(	CrankVecInt3*	a,
												CrankVecInt3*	b	);

void			crank_vec_int3_crs			(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);

void			crank_vec_int3_add_self		(	CrankVecInt3*	a,
												CrankVecInt3*	b	);

void			crank_vec_int3_sub_self		(	CrankVecInt3*	a,
												CrankVecInt3*	b	);

void			crank_vec_int3_crs_self		(	CrankVecInt3*	a,
												CrankVecInt3*	b	);

//////// Component vector operations ////////

void			crank_vec_int3_cmpmul		(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);
												
void			crank_vec_int3_cmpdiv		(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);

void			crank_vec_int3_cmpmod		(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);

void			crank_vec_int3_cmpless		(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecBool3*	r	);
												
void			crank_vec_int3_cmpeq		(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecBool3*	r	);
												
void			crank_vec_int3_cmpgreater	(	CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecBool3*	r	);
												
void			crank_vec_int3_cmpcmp	(		CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);

void			crank_vec_int3_min	(			CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);

void			crank_vec_int3_max	(			CrankVecInt3*	a,
												CrankVecInt3*	b,
												CrankVecInt3*	r	);
												

void			crank_vec_int3_cmpmul_self	(	CrankVecInt3*	a,
												CrankVecInt3*	b	);
												
void			crank_vec_int3_cmpdiv_self	(	CrankVecInt3*	a,
												CrankVecInt3*	b	);

void			crank_vec_int3_cmpmod_self	(	CrankVecInt3*	a,
												CrankVecInt3*	b	);





/**
 * CrankVecInt4:
 * @x: First element.
 * @y: Second element.
 * @z: Third element.
 * @w: Fourth element.
 *
 * integer vector. Compared to ivec4 in GLSL.
 */
struct _CrankVecInt4 {
	gint	x;
	gint	y;
	gint	z;
	gint	w;
};

#define CRANK_TYPE_VEC_INT4	(crank_vec_int4_get_type ())
GType			crank_vec_int4_get_type	(void);

/**
 * CRANK_VEC_INT4_0:
 * 
 * Zero vector initializing list.
 */
#define CRANK_VEC_INT4_0	{0, 0, 0, 0}

/**
 * CRANK_VEC_INT4_I:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT4_I	{1, 0, 0, 0}

/**
 * CRANK_VEC_INT4_J:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT4_J	{0, 1, 0, 0}

/**
 * CRANK_VEC_INT4_K:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT4_K	{0, 0, 1, 0}

/**
 * CRANK_VEC_INT4_L:
 * 
 * Standard basis.
 */
#define CRANK_VEC_INT4_L	{0, 0, 0, 1}

void			crank_vec_int4_init			(	CrankVecInt4*	vec,
												gint			x,
												gint			y,
												gint			z,
												gint			w	);

void			crank_vec_int4_init_arr		(	CrankVecInt4*	vec,
												gint*			arr	);

void			crank_vec_int4_init_valist	(	CrankVecInt4*	vec,
												va_list			varargs	);

void			crank_vec_int4_init_fill	(	CrankVecInt4*	vec,
												gint			fill	);
												
void			crank_vec_int4_init_from_vb (	CrankVecInt4*	vec,
												CrankVecBool4*	vb		);

void			crank_vec_int4_copy			(	CrankVecInt4*	vec,
												CrankVecInt4*	other	);

CrankVecInt4*	crank_vec_int4_dup			(	CrankVecInt4*	vec	);

gint			crank_vec_int4_get			(	CrankVecInt4*	vec,
												const guint		index	);

void			crank_vec_int4_set			(	CrankVecInt4*	vec,
												const guint		index,
												const gint		value	);

gboolean		crank_vec_int4_foreach		(	CrankVecInt4*		vec,
												CrankBoolIntFunc	func,
												gpointer			userdata	);
												
void			crank_vec_int4_iterator 	(	CrankVecInt4*		vec,
												CrankIterMemInt*	iter	);

//////// Basic operation ////////

guint			crank_vec_int4_hash (			gconstpointer	a	);

gboolean		crank_vec_int4_equal (			gconstpointer	a,
												gconstpointer	b	);

gchar*			crank_vec_int4_to_string (		CrankVecInt4*	vec	);

gchar*			crank_vec_int4_to_string_full (	CrankVecInt4*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	format	);


//////// Standard vector property ///////

guint			crank_vec_int4_get_magn_sq		(	CrankVecInt4*	vec	);

gfloat			crank_vec_int4_get_magn			(	CrankVecInt4*	vec	);


//////// Standard unary operations ////////

void			crank_vec_int4_neg			(	CrankVecInt4*	a,
												CrankVecInt4*	r	);

void			crank_vec_int4_neg_self		(	CrankVecInt4*	a	);


//////// Scalar operations ////////

void			crank_vec_int4_muls			(	CrankVecInt4*	a,
												const gint		b,
												CrankVecInt4*	r	);

void			crank_vec_int4_divs			(	CrankVecInt4*	a,
												const gint		b,
												CrankVecInt4*	r	);

void			crank_vec_int4_mods			(	CrankVecInt4*	a,
												const gint		b,
												CrankVecInt4*	r	);

void			crank_vec_int4_muls_self	(	CrankVecInt4*	a,
												const gint		b	);

void			crank_vec_int4_divs_self	(	CrankVecInt4*	a,
												const gint		b	);

void			crank_vec_int4_mods_self	(	CrankVecInt4*	a,
												const gint		b	);


//////// Standard vector operations ////////

void			crank_vec_int4_add			(	CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecInt4*	r	);

void			crank_vec_int4_sub			(	CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecInt4*	r	);

gint			crank_vec_int4_dot			(	CrankVecInt4*	a,
												CrankVecInt4*	b	);
												

void			crank_vec_int4_add_self		(	CrankVecInt4*	a,
												CrankVecInt4*	b	);

void			crank_vec_int4_sub_self		(	CrankVecInt4*	a,
												CrankVecInt4*	b	);

//////// Component vector operations ////////

void			crank_vec_int4_cmpmul		(	CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecInt4*	r	);
												
void			crank_vec_int4_cmpdiv		(	CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecInt4*	r	);

void			crank_vec_int4_cmpmod		(	CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecInt4*	r	);

void			crank_vec_int4_cmpless		(	CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecBool4*	r	);
												
void			crank_vec_int4_cmpeq		(	CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecBool4*	r	);
												
void			crank_vec_int4_cmpgreater	(	CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecBool4*	r	);
												
void			crank_vec_int4_cmpcmp	(		CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecInt4*	r	);

void			crank_vec_int4_min	(			CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecInt4*	r	);

void			crank_vec_int4_max	(			CrankVecInt4*	a,
												CrankVecInt4*	b,
												CrankVecInt4*	r	);

void			crank_vec_int4_cmpmul_self	(	CrankVecInt4*	a,
												CrankVecInt4*	b	);
												
void			crank_vec_int4_cmpdiv_self	(	CrankVecInt4*	a,
												CrankVecInt4*	b	);

void			crank_vec_int4_cmpmod_self	(	CrankVecInt4*	a,
												CrankVecInt4*	b	);





/**
 * CrankVecIntN:
 * @data: (array length=n): data
 * @n: size of vector.
 *
 * Variable sized integer vector.
 */
struct _CrankVecIntN {
	gint*	data;
	guint	n;
};

#define CRANK_TYPE_VEC_INT_N	(crank_vec_int_n_get_type ())
GType			crank_vec_int_n_get_type	(void);

void			crank_vec_int_n_init		(	CrankVecIntN*	vec,
												guint			n,
												...	);

void			crank_vec_int_n_init_arr	(	CrankVecIntN*	vec,
												guint			n,
												gint*			arr	);

void			crank_vec_int_n_init_valist	(	CrankVecIntN*	vec,
												guint			n,
												va_list			varargs	);

void			crank_vec_int_n_init_fill	(	CrankVecIntN*	vec,
												guint			n,
												gint			fill	);
												
void			crank_vec_int_n_init_from_vb (	CrankVecIntN*	vec,
												CrankVecBoolN*	vb		);
												
void			crank_vec_int_n_fini		(	CrankVecIntN*	vec	);

void			crank_vec_int_n_copy		(	CrankVecIntN*	vec,
									 			CrankVecIntN*	other	);

CrankVecIntN*	crank_vec_int_n_dup			(	CrankVecIntN*	vec	);

void			crank_vec_int_n_free		(	CrankVecIntN*	vec		);

guint			crank_vec_int_n_get_size	(	CrankVecIntN*	vec		);

gint			crank_vec_int_n_get			(	CrankVecIntN*	vec,
												const guint		index	);

void			crank_vec_int_n_set			(	CrankVecIntN*	vec,
												const guint		index,
												const gint		value	);

void			crank_vec_int_n_prepend		(	CrankVecIntN*	vec,
								 				const gint		value	);

void			crank_vec_int_n_append		(	CrankVecIntN*	vec,
												const gint		value	);

void			crank_vec_int_n_insert		(	CrankVecIntN*	vec,
												const guint		index,
												const gint		value	);

void			crank_vec_int_n_remove		(	CrankVecIntN*	vec,
												const guint		index	);

gboolean		crank_vec_int_n_foreach		(	CrankVecIntN*		vec,
								 				CrankBoolIntFunc	func,
								 				gpointer			userdata	);
												
void			crank_vec_int_n_iterator 	(	CrankVecIntN*		vec,
												CrankIterMemInt*	iter	);

//////// Basic operation ////////

guint			crank_vec_int_n_hash (			gconstpointer	a	);

gboolean		crank_vec_int_n_equal (			gconstpointer	a,
												gconstpointer	b	);

gchar*			crank_vec_int_n_to_string (		CrankVecIntN*	vec	);

gchar*			crank_vec_int_n_to_string_full (	CrankVecIntN*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	format	);


//////// Standard vector property ///////

guint			crank_vec_int_n_get_magn_sq		(	CrankVecIntN*	vec	);

gfloat			crank_vec_int_n_get_magn		(	CrankVecIntN*	vec	);


//////// Standard unary operations ////////

void			crank_vec_int_n_neg			(	CrankVecIntN*	a,
												CrankVecIntN*	r	);

void			crank_vec_int_n_neg_self	(	CrankVecIntN*	a	);


//////// Scalar operations ////////

void			crank_vec_int_n_muls		(	CrankVecIntN*	a,
												const gint		b,
												CrankVecIntN*	r	);

void			crank_vec_int_n_divs		(	CrankVecIntN*	a,
												const gint		b,
												CrankVecIntN*	r	);

void			crank_vec_int_n_mods		(	CrankVecIntN*	a,
												const gint		b,
												CrankVecIntN*	r	);


void			crank_vec_int_n_muls_self	(	CrankVecIntN*	a,
												const gint		b	);

void			crank_vec_int_n_divs_self	(	CrankVecIntN*	a,
												const gint		b	);

void			crank_vec_int_n_mods_self	(	CrankVecIntN*	a,
												const gint		b	);
												

//////// Standard vector operations ////////

void			crank_vec_int_n_add			(	CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecIntN*	r	);

void			crank_vec_int_n_sub			(	CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecIntN*	r	);

gint			crank_vec_int_n_dot			(	CrankVecIntN*	a,
												CrankVecIntN*	b	);

void			crank_vec_int_n_add_self	(	CrankVecIntN*	a,
												CrankVecIntN*	b	);

void			crank_vec_int_n_sub_self	(	CrankVecIntN*	a,
												CrankVecIntN*	b	);

//////// Component vector operations ////////

void			crank_vec_int_n_cmpmul		(	CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecIntN*	r	);
												
void			crank_vec_int_n_cmpdiv		(	CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecIntN*	r	);

void			crank_vec_int_n_cmpmod		(	CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecIntN*	r	);

void			crank_vec_int_n_cmpless		(	CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecBoolN*	r	);
												
void			crank_vec_int_n_cmpeq		(	CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecBoolN*	r	);
												
void			crank_vec_int_n_cmpgreater	(	CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecBoolN*	r	);
												
void			crank_vec_int_n_cmpcmp	(		CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecIntN*	r	);

void			crank_vec_int_n_min	(			CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecIntN*	r	);

void			crank_vec_int_n_max	(			CrankVecIntN*	a,
												CrankVecIntN*	b,
												CrankVecIntN*	r	);
												

void			crank_vec_int_n_cmpmul_self	(	CrankVecIntN*	a,
												CrankVecIntN*	b	);
												
void			crank_vec_int_n_cmpdiv_self	(	CrankVecIntN*	a,
												CrankVecIntN*	b	);

void			crank_vec_int_n_cmpmod_self	(	CrankVecIntN*	a,
												CrankVecIntN*	b	);


G_END_DECLS

#endif //CRANKBOOLVEC_H
