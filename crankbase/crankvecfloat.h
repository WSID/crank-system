#ifndef CRANKVECFLOAT_H
#define CRANKVECFLOAT_H

/* Copyright (C) 2015, WSID   */

/* This file is part of Crank System.
 *
 *  Crank System is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  Crank System is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with Crank System.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CRANKBASE_INSIDE
#error crankvecfloat.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankveccommon.h"

G_BEGIN_DECLS

/**
 * CrankVecFloat2:
 * @x: First element.
 * @y: Second element.
 *
 * Float vector. Compared to vec2 in GLSL.
 */
struct _CrankVecFloat2 {
	gfloat	x;
	gfloat	y;
};

#define CRANK_TYPE_VEC_FLOAT2	(crank_vec_float2_get_type ())
GType			crank_vec_float2_get_type	(void);

/**
 * CRANK_VEC_FLOAT2_0:
 * 
 * Zero vector initializing list.
 */
#define CRANK_VEC_FLOAT2_0	{0.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT2_I:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT2_I	{1.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT2_J:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT2_J	{0.0f, 1.0f}

void			crank_vec_float2_init		(	CrankVecFloat2*	vec,
												gfloat			x,
												gfloat			y	);

void			crank_vec_float2_init_arr	(	CrankVecFloat2*	vec,
												gfloat*			arr	);

void			crank_vec_float2_init_valist (	CrankVecFloat2*	vec,
												va_list			varargs	);

void			crank_vec_float2_init_fill	(	CrankVecFloat2*	vec,
												gfloat			fill	);

void			crank_vec_float2_init_from_vb (	CrankVecFloat2*	vec,
												CrankVecBool2*	vb		);
												
void			crank_vec_float2_init_from_vi (	CrankVecFloat2*	vec,
												CrankVecInt2*	vi		);

CrankVecFloat2*	crank_vec_float2_copy		(	CrankVecFloat2*	vec	);

gfloat			crank_vec_float2_get		(	CrankVecFloat2*	vec,
												const guint		index	);

void			crank_vec_float2_set		(	CrankVecFloat2*	vec,
												const guint		index,
												const gfloat	value	);

//////// Basic operation ////////

guint			crank_vec_float2_hash		(	gconstpointer	a	);

gboolean		crank_vec_float2_equal		(	gconstpointer	a,
												gconstpointer	b	);

gchar*			crank_vec_float2_to_string	(	CrankVecFloat2*	vec	);

gchar*			crank_vec_float2_to_string_full (	CrankVecFloat2*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	format	);


//////// Standard vector property ///////

gfloat			crank_vec_float2_get_magn_sq		(	CrankVecFloat2*	vec	);

gfloat			crank_vec_float2_get_magn			(	CrankVecFloat2*	vec	);


//////// Standard unary operations ////////

void			crank_vec_float2_neg			(	CrankVecFloat2*	a,
													CrankVecFloat2*	r	);

void			crank_vec_float2_unit			(	CrankVecFloat2*	a,
													CrankVecFloat2*	r	);


//////// Scalar operations ////////

void			crank_vec_float2_muls			(	CrankVecFloat2*	a,
													const gfloat	b,
													CrankVecFloat2*	r	);

void			crank_vec_float2_divs			(	CrankVecFloat2*	a,
													const gfloat	b,
													CrankVecFloat2*	r	);

//////// Standard vector operations ////////

void			crank_vec_float2_add			(	CrankVecFloat2*	a,
													CrankVecFloat2*	b,
													CrankVecFloat2*	r	);

void			crank_vec_float2_sub			(	CrankVecFloat2*	a,
													CrankVecFloat2*	b,
													CrankVecFloat2*	r	);

gfloat			crank_vec_float2_dot			(	CrankVecFloat2*	a,
													CrankVecFloat2*	b	);

//////// Component vector operations ////////

void			crank_vec_float2_cmpmul		(	CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecFloat2*	r	);
												
void			crank_vec_float2_cmpdiv		(	CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecFloat2*	r	);

void			crank_vec_float2_cmpless	(	CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecBool2*	r	);
												
void			crank_vec_float2_cmpeq		(	CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecBool2*	r	);
												
void			crank_vec_float2_cmpgreater	(	CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecBool2*	r	);
												
void			crank_vec_float2_cmpcmp	(		CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecInt2*	r	);

void			crank_vec_float2_min	(		CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecFloat2*	r	);

void			crank_vec_float2_max	(		CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecFloat2*	r	);

//////// Ternary Operations ////////

void			crank_vec_float2_mixs	(		CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												gfloat			c,
												CrankVecFloat2*	r	);

void			crank_vec_float2_mix	(		CrankVecFloat2*	a,
												CrankVecFloat2*	b,
												CrankVecFloat2*	c,
												CrankVecFloat2*	r	);






/**
 * CrankVecFloat3:
 * @x: First element.
 * @y: Second element.
 * @z: Third element.
 *
 * Float vector. Compared to vec3 in GLSL.
 */
struct _CrankVecFloat3 {
	gfloat	x;
	gfloat	y;
	gfloat	z;
};

#define CRANK_TYPE_VEC_FLOAT3	(crank_vec_float3_get_type ())
GType			crank_vec_float3_get_type	(void);

/**
 * CRANK_VEC_FLOAT3_0:
 * 
 * Zero vector initializing list.
 */
#define CRANK_VEC_FLOAT3_0	{0.0f, 0.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT3_I:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT3_I	{1.0f, 0.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT3_J:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT3_J	{0.0f, 1.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT3_K:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT3_K	{0.0f, 0.0f, 1.0f}

void			crank_vec_float3_init		(	CrankVecFloat3*	vec,
												gfloat			x,
												gfloat			y,
												gfloat			z	);

void			crank_vec_float3_init_arr	(	CrankVecFloat3*	vec,
												gfloat*			arr	);

void			crank_vec_float3_init_valist (	CrankVecFloat3*	vec,
												va_list			varargs	);

void			crank_vec_float3_init_fill	(	CrankVecFloat3*	vec,
												gfloat			fill	);

void			crank_vec_float3_init_from_vb (	CrankVecFloat3*	vec,
												CrankVecBool3*	vb		);
												
void			crank_vec_float3_init_from_vi (	CrankVecFloat3*	vec,
												CrankVecInt3*	vi		);

CrankVecFloat3*	crank_vec_float3_copy		(	CrankVecFloat3*	vec	);

gfloat			crank_vec_float3_get		(	CrankVecFloat3*	vec,
												const guint		index	);

void			crank_vec_float3_set		(	CrankVecFloat3*	vec,
												const guint		index,
												const gfloat	value	);

//////// Basic operation ////////

guint			crank_vec_float3_hash		(	gconstpointer	a	);

gboolean		crank_vec_float3_equal		(	gconstpointer	a,
												gconstpointer	b	);

gchar*			crank_vec_float3_to_string	(	CrankVecFloat3*	vec	);

gchar*			crank_vec_float3_to_string_full (	CrankVecFloat3*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	format	);


//////// Standard vector property ///////

gfloat			crank_vec_float3_get_magn_sq		(	CrankVecFloat3*	vec	);

gfloat			crank_vec_float3_get_magn			(	CrankVecFloat3*	vec	);


//////// Standard unary operations ////////

void			crank_vec_float3_neg			(	CrankVecFloat3*	a,
													CrankVecFloat3*	r	);

void			crank_vec_float3_unit			(	CrankVecFloat3*	a,
													CrankVecFloat3*	r	);


//////// Scalar operations ////////

void			crank_vec_float3_muls			(	CrankVecFloat3*	a,
													const gfloat	b,
													CrankVecFloat3*	r	);

void			crank_vec_float3_divs			(	CrankVecFloat3*	a,
													const gfloat	b,
													CrankVecFloat3*	r	);

//////// Standard vector operations ////////

void			crank_vec_float3_add			(	CrankVecFloat3*	a,
													CrankVecFloat3*	b,
													CrankVecFloat3*	r	);

void			crank_vec_float3_sub			(	CrankVecFloat3*	a,
													CrankVecFloat3*	b,
													CrankVecFloat3*	r	);

gfloat			crank_vec_float3_dot			(	CrankVecFloat3*	a,
													CrankVecFloat3*	b	);

void			crank_vec_float3_crs			(	CrankVecFloat3*	a,
													CrankVecFloat3*	b,
													CrankVecFloat3*	r	);

//////// Component vector operations ////////

void			crank_vec_float3_cmpmul		(	CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecFloat3*	r	);
												
void			crank_vec_float3_cmpdiv		(	CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecFloat3*	r	);

void			crank_vec_float3_cmpless	(	CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecBool3*	r	);
												
void			crank_vec_float3_cmpeq		(	CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecBool3*	r	);
												
void			crank_vec_float3_cmpgreater	(	CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecBool3*	r	);
												
void			crank_vec_float3_cmpcmp	(		CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecInt3*	r	);

void			crank_vec_float3_min	(		CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecFloat3*	r	);

void			crank_vec_float3_max	(		CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecFloat3*	r	);

//////// Ternary Operations ////////

void			crank_vec_float3_mixs	(		CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												gfloat			c,
												CrankVecFloat3*	r	);

void			crank_vec_float3_mix	(		CrankVecFloat3*	a,
												CrankVecFloat3*	b,
												CrankVecFloat3*	c,
												CrankVecFloat3*	r	);






/**
 * CrankVecFloat4:
 * @x: First element.
 * @y: Second element.
 * @z: Third element.
 * @w: Fourth element.
 *
 * Float vector. Compared to vec3 in GLSL.
 */
struct _CrankVecFloat4 {
	gfloat	x;
	gfloat	y;
	gfloat	z;
	gfloat	w;
};

#define CRANK_TYPE_VEC_FLOAT4	(crank_vec_float4_get_type ())
GType			crank_vec_float4_get_type	(void);

/**
 * CRANK_VEC_FLOAT4_0:
 * 
 * Zero vector initializing list.
 */
#define CRANK_VEC_FLOAT4_0	{0.0f, 0.0f, 0.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT4_I:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT4_I	{1.0f, 0.0f, 0.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT4_J:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT4_J	{0.0f, 1.0f, 0.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT4_K:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT4_K	{0.0f, 0.0f, 1.0f, 0.0f}

/**
 * CRANK_VEC_FLOAT4_L:
 * 
 * Standard basis.
 */
#define CRANK_VEC_FLOAT4_L	{0.0f, 0.0f, 0.0f, 1.0f}

void			crank_vec_float4_init		(	CrankVecFloat4*	vec,
												gfloat			x,
												gfloat			y,
												gfloat			z,
												gfloat			w	);

void			crank_vec_float4_init_arr	(	CrankVecFloat4*	vec,
												gfloat*			arr	);

void			crank_vec_float4_init_valist (	CrankVecFloat4*	vec,
												va_list			varargs	);

void			crank_vec_float4_init_fill	(	CrankVecFloat4*	vec,
												gfloat			fill	);

void			crank_vec_float4_init_from_vb (	CrankVecFloat4*	vec,
												CrankVecBool4*	vb		);
												
void			crank_vec_float4_init_from_vi (	CrankVecFloat4*	vec,
												CrankVecInt4*	vi		);

CrankVecFloat4*	crank_vec_float4_copy		(	CrankVecFloat4*	vec	);

gfloat			crank_vec_float4_get		(	CrankVecFloat4*	vec,
												const guint		index	);

void			crank_vec_float4_set		(	CrankVecFloat4*	vec,
												const guint		index,
												const gfloat	value	);

//////// Basic operation ////////

guint			crank_vec_float4_hash		(	gconstpointer	a	);

gboolean		crank_vec_float4_equal		(	gconstpointer	a,
												gconstpointer	b	);

gchar*			crank_vec_float4_to_string	(	CrankVecFloat4*	vec	);

gchar*			crank_vec_float4_to_string_full (	CrankVecFloat4*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	format	);


//////// Standard vector property ///////

gfloat			crank_vec_float4_get_magn_sq		(	CrankVecFloat4*	vec	);

gfloat			crank_vec_float4_get_magn			(	CrankVecFloat4*	vec	);


//////// Standard unary operations ////////

void			crank_vec_float4_neg			(	CrankVecFloat4*	a,
													CrankVecFloat4*	r	);

void			crank_vec_float4_unit			(	CrankVecFloat4*	a,
													CrankVecFloat4*	r	);


//////// Scalar operations ////////

void			crank_vec_float4_muls			(	CrankVecFloat4*	a,
													const gfloat	b,
													CrankVecFloat4*	r	);

void			crank_vec_float4_divs			(	CrankVecFloat4*	a,
													const gfloat	b,
													CrankVecFloat4*	r	);

//////// Standard vector operations ////////

void			crank_vec_float4_add			(	CrankVecFloat4*	a,
													CrankVecFloat4*	b,
													CrankVecFloat4*	r	);

void			crank_vec_float4_sub			(	CrankVecFloat4*	a,
													CrankVecFloat4*	b,
													CrankVecFloat4*	r	);

gfloat			crank_vec_float4_dot			(	CrankVecFloat4*	a,
													CrankVecFloat4*	b	);

//////// Component vector operations ////////

void			crank_vec_float4_cmpmul		(	CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecFloat4*	r	);
												
void			crank_vec_float4_cmpdiv		(	CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecFloat4*	r	);

void			crank_vec_float4_cmpless	(	CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecBool4*	r	);
												
void			crank_vec_float4_cmpeq		(	CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecBool4*	r	);
												
void			crank_vec_float4_cmpgreater	(	CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecBool4*	r	);
												
void			crank_vec_float4_cmpcmp	(		CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecInt4*	r	);

void			crank_vec_float4_min	(		CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecFloat4*	r	);

void			crank_vec_float4_max	(		CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecFloat4*	r	);

//////// Ternary Operations ////////

void			crank_vec_float4_mixs	(		CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												gfloat			c,
												CrankVecFloat4*	r	);

void			crank_vec_float4_mix	(		CrankVecFloat4*	a,
												CrankVecFloat4*	b,
												CrankVecFloat4*	c,
												CrankVecFloat4*	r	);






/**
 * CrankVecFloatN:
 * @data: (array length=n): Array to store elements.
 * @n: size of data.
 *
 * Struct to point variable size of float vector.
 */
struct _CrankVecFloatN {
	gfloat*	data;
	guint	n;
};

#define CRANK_TYPE_VEC_FLOAT_N	(crank_vec_float_n_get_type ())
GType			crank_vec_float_n_get_type	(void);

void			crank_vec_float_n_init		(	CrankVecFloatN*	vec,
												const guint		n,
												...	);

void			crank_vec_float_n_init_arr	(	CrankVecFloatN*	vec,
												const guint		n,
												gfloat*			arr	);

void			crank_vec_float_n_init_valist (	CrankVecFloatN*	vec,
												const guint		n,
												va_list			varargs	);

void			crank_vec_float_n_init_fill	(	CrankVecFloatN*	vec,
												const guint		n,
												gfloat			fill	);

void			crank_vec_float_n_init_from_vb (	CrankVecFloatN*	vec,
													CrankVecBoolN*	vb		);
												
void			crank_vec_float_n_init_from_vi (	CrankVecFloatN*	vec,
												CrankVecIntN*	vi		);

void			crank_vec_float_n_fini		(	CrankVecFloatN*	vec	);

CrankVecFloatN*	crank_vec_float_n_copy		(	CrankVecFloatN*	vec	);

void			crank_vec_float_n_free		(	CrankVecFloatN*	vec	);

gfloat			crank_vec_float_n_get		(	CrankVecFloatN*	vec,
												const guint		index	);

void			crank_vec_float_n_set		(	CrankVecFloatN*	vec,
												const guint		index,
												const gfloat	value	);

//////// Basic operation ////////

guint			crank_vec_float_n_hash		(	gconstpointer	a	);

gboolean		crank_vec_float_n_equal		(	gconstpointer	a,
												gconstpointer	b	);

gchar*			crank_vec_float_n_to_string	(	CrankVecFloatN*	vec	);

gchar*			crank_vec_float_n_to_string_full (	CrankVecFloatN*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	format	);


//////// Standard vector property ///////

gfloat			crank_vec_float_n_get_magn_sq		(	CrankVecFloatN*	vec	);

gfloat			crank_vec_float_n_get_magn			(	CrankVecFloatN*	vec	);


//////// Standard unary operations ////////

void			crank_vec_float_n_neg			(	CrankVecFloatN*	a,
													CrankVecFloatN*	r	);

void			crank_vec_float_n_unit			(	CrankVecFloatN*	a,
													CrankVecFloatN*	r	);


//////// Scalar operations ////////

void			crank_vec_float_n_muls			(	CrankVecFloatN*	a,
													const gfloat	b,
													CrankVecFloatN*	r	);

void			crank_vec_float_n_divs			(	CrankVecFloatN*	a,
													const gfloat	b,
													CrankVecFloatN*	r	);

//////// Standard vector operations ////////

void			crank_vec_float_n_add			(	CrankVecFloatN*	a,
													CrankVecFloatN*	b,
													CrankVecFloatN*	r	);

void			crank_vec_float_n_sub			(	CrankVecFloatN*	a,
													CrankVecFloatN*	b,
													CrankVecFloatN*	r	);

gfloat			crank_vec_float_n_dot			(	CrankVecFloatN*	a,
													CrankVecFloatN*	b	);

//////// Component vector operations ////////

void			crank_vec_float_n_cmpmul		(	CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecFloatN*	r	);
												
void			crank_vec_float_n_cmpdiv		(	CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecFloatN*	r	);

void			crank_vec_float_n_cmpless	(	CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecBoolN*	r	);
												
void			crank_vec_float_n_cmpeq		(	CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecBoolN*	r	);
												
void			crank_vec_float_n_cmpgreater	(	CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecBoolN*	r	);
												
void			crank_vec_float_n_cmpcmp	(		CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecIntN*	r	);

void			crank_vec_float_n_min	(		CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecFloatN*	r	);

void			crank_vec_float_n_max	(		CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecFloatN*	r	);

//////// Ternary Operations ////////

void			crank_vec_float_n_mixs	(		CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												gfloat			c,
												CrankVecFloatN*	r	);

void			crank_vec_float_n_mix	(		CrankVecFloatN*	a,
												CrankVecFloatN*	b,
												CrankVecFloatN*	c,
												CrankVecFloatN*	r	);

G_END_DECLS

#endif //CRANKBOOLVEC_H
