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

#include "crankvecbool.h"
#include "crankvecint.h"

G_BEGIN_DECLS

/**
 * CrankVecFloat2:
 * @x: First element.
 * @y: Second element.
 *
 * Float vector. Compared to vec2 in GLSL.
 */
typedef struct _CrankVecFloat2 {
	gfloat	x;
	gfloat	y;
} CrankVecFloat2;

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
#define CRANK_VEC_FLOAT2_J	{0.0f, 1.0f)

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



G_END_DECLS

#endif //CRANKBOOLVEC_H
