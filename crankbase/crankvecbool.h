#ifndef CRANKBOOLVEC_H
#define CRANKBOOLVEC_H

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
#error crankboolvec.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/**
 * CrankVecBool2:
 * @x: First vector element.
 * @y: Second vector element.
 *
 * Represents a boolean vector. Compared to bvec2 in GLSL.
 */
typedef struct _CrankVecBool2 {
	gboolean	x;
	gboolean	y;
} CrankVecBool2;

#define CRANK_TYPE_VEC_BOOL2	(crank_vec_bool2_get_type ())
GType			crank_vec_bool2_get_type	(void);

/**
 * CRANK_VEC_BOOL2_FALSE:
 *
 * Initialization list that all elements are %FALSE.
 */
#define CRANK_VEC_BOOL2_FALSE	{FALSE, FALSE}

/**
 * CRANK_VEC_BOOL2_TRUE:
 *
 * Initialization list that all elements are %TRUE.
 */
#define CRANK_VEC_BOOL2_TRUE	{TRUE, TRUE}

/**
 * CRANK_VEC_BOOL2_I:
 *
 * Initialization list that only first vector element is %TRUE
 */
#define CRANK_VEC_BOOL2_I		{TRUE, FALSE}

/**
 * CRANK_VEC_BOOL2_J:
 *
 * Initialization list that only second vector element is %TRUE
 */
#define CRANK_VEC_BOOL2_J		{FALSE, TRUE}


void			crank_vec_bool2_init 		(	CrankVecBool2*	vec,
												gboolean		x,
												gboolean		y	);

void			crank_vec_bool2_init_arr	(	CrankVecBool2*	vec,
												gboolean*		arr	);

void			crank_vec_bool2_init_valist	(	CrankVecBool2*	vec,
												va_list			varargs	);
												
void			crank_vec_bool2_init_fill	(	CrankVecBool2*	vec,
												const gboolean	fill	);

CrankVecBool2*	crank_vec_bool2_copy		(	CrankVecBool2*	vec	);

gboolean		crank_vec_bool2_get			(	CrankVecBool2*	vec,
												const guint		index	);

void			crank_vec_bool2_set			(	CrankVecBool2*	vec,
												const guint		index,
												const gboolean	value	);

void			crank_vec_bool2_and			(	CrankVecBool2*	a,
												CrankVecBool2*	b,
												CrankVecBool2*	r	);

void			crank_vec_bool2_or			(	CrankVecBool2*	a,
												CrankVecBool2*	b,
												CrankVecBool2*	r	);

void			crank_vec_bool2_xor			(	CrankVecBool2*	a,
												CrankVecBool2*	b,
												CrankVecBool2*	r	);

void			crank_vec_bool2_not			(	CrankVecBool2*	a,
												CrankVecBool2*	r	);

void			crank_vec_bool2_andv		(	CrankVecBool2*	a,
												CrankVecBool2*	b,
												CrankVecBool2*	r	);

void			crank_vec_bool2_orv			(	CrankVecBool2*	a,
												CrankVecBool2*	b,
												CrankVecBool2*	r	);

void			crank_vec_bool2_notv		(	CrankVecBool2*	a,
												CrankVecBool2*	r	);

gboolean		crank_vec_bool2_get_any		(	CrankVecBool2*	vec	);

gboolean		crank_vec_bool2_get_all		(	CrankVecBool2*	vec	);


gboolean		crank_vec_bool2_equal		(	gconstpointer	a,
												gconstpointer	b	);

guint			crank_vec_bool2_hash		(	gconstpointer	a	);


gchar*			crank_vec_bool2_to_string	(	CrankVecBool2*	vec	);

gchar*			crank_vec_bool2_to_string_full (CrankVecBool2*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	on_true,
												const gchar*	on_false	);



/**
 * CrankVecBool3:
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 *
 * Represents a boolean vector. Compared to bvec3 in GLSL.
 */
typedef struct _CrankVecBool3 {
	gboolean	x;
	gboolean	y;
	gboolean	z;
} CrankVecBool3;

#define CRANK_TYPE_VEC_BOOL3	(crank_vec_bool3_get_type ())
GType			crank_vec_bool3_get_type	(void);

/**
 * CRANK_VEC_BOOL3_FALSE:
 *
 * Initialization list that all elements are %FALSE.
 */
#define CRANK_VEC_BOOL3_FALSE	{FALSE, FALSE, FALSE}

/**
 * CRANK_VEC_BOOL3_TRUE:
 *
 * Initialization list that all elements are %TRUE.
 */
#define CRANK_VEC_BOOL3_TRUE	{TRUE, TRUE, TRUE}

/**
 * CRANK_VEC_BOOL3_I:
 *
 * Initialization list that only first vector element is %TRUE
 */
#define CRANK_VEC_BOOL3_I		{TRUE, FALSE, FALSE}

/**
 * CRANK_VEC_BOOL3_J:
 *
 * Initialization list that only second vector element is %TRUE
 */
#define CRANK_VEC_BOOL3_J		{FALSE, TRUE, FALSE}

/**
 * CRANK_VEC_BOOL3_K:
 *
 * Initialization list that only third vector element is %TRUE
 */
#define CRANK_VEC_BOOL3_K		{FALSE, FALSE, TRUE}


void			crank_vec_bool3_init 		(	CrankVecBool3*	vec,
												gboolean		x,
												gboolean		y,
												gboolean		z	);

void			crank_vec_bool3_init_arr	(	CrankVecBool3*	vec,
												gboolean*		arr	);

void			crank_vec_bool3_init_valist	(	CrankVecBool3*	vec,
												va_list			varargs	);

void			crank_vec_bool3_init_fill	(	CrankVecBool3*	vec,
												const gboolean	fill	);

CrankVecBool3*	crank_vec_bool3_copy		(	CrankVecBool3*	vec	);

gboolean		crank_vec_bool3_get			(	CrankVecBool3*	vec,
												const guint		index	);

void			crank_vec_bool3_set			(	CrankVecBool3*	vec,
												const guint		index,
												const gboolean	value	);

void			crank_vec_bool3_and			(	CrankVecBool3*	a,
												CrankVecBool3*	b,
												CrankVecBool3*	r	);

void			crank_vec_bool3_or			(	CrankVecBool3*	a,
												CrankVecBool3*	b,
												CrankVecBool3*	r	);

void			crank_vec_bool3_xor			(	CrankVecBool3*	a,
												CrankVecBool3*	b,
												CrankVecBool3*	r	);

void			crank_vec_bool3_not			(	CrankVecBool3*	a,
												CrankVecBool3*	r	);

void			crank_vec_bool3_andv		(	CrankVecBool3*	a,
												CrankVecBool3*	b,
												CrankVecBool3*	r	);

void			crank_vec_bool3_orv			(	CrankVecBool3*	a,
												CrankVecBool3*	b,
												CrankVecBool3*	r	);
void			crank_vec_bool3_notv		(	CrankVecBool3*	a,
												CrankVecBool3*	r	);

gboolean		crank_vec_bool3_get_any		(	CrankVecBool3*	vec	);

gboolean		crank_vec_bool3_get_all		(	CrankVecBool3*	vec	);

gboolean		crank_vec_bool3_equal		(	gconstpointer	a,
												gconstpointer	b	);

guint			crank_vec_bool3_hash		(	gconstpointer	a	);

gchar*			crank_vec_bool3_to_string	(	CrankVecBool3*	vec	);

gchar*			crank_vec_bool3_to_string_full (CrankVecBool3*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	on_true,
												const gchar*	on_false	);


/**
 * CrankVecBool4:
 * @x: First vector element.
 * @y: Second vector element.
 * @z: Third vector element.
 * @w: Fourth vector element.
 *
 * Represents a boolean vector. Compared to bvec4 in GLSL.
 */
typedef struct _CrankVecBool4 {
	gboolean	x;
	gboolean	y;
	gboolean	z;
	gboolean	w;
} CrankVecBool4;

#define CRANK_TYPE_VEC_BOOL4	(crank_vec_bool4_get_type ())
GType			crank_vec_bool4_get_type	(void);

/**
 * CRANK_VEC_BOOL4_FALSE:
 *
 * Initialization list that all elements are %FALSE.
 */
#define CRANK_VEC_BOOL4_FALSE	{FALSE, FALSE, FALSE, FALSE}

/**
 * CRANK_VEC_BOOL4_TRUE:
 *
 * Initialization list that all elements are %TRUE.
 */
#define CRANK_VEC_BOOL4_TRUE	{TRUE, TRUE, TRUE, TRUE}

/**
 * CRANK_VEC_BOOL4_I:
 *
 * Initialization list that only first vector element is %TRUE
 */
#define CRANK_VEC_BOOL4_I		{TRUE, FALSE, FALSE, FALSE}

/**
 * CRANK_VEC_BOOL4_J:
 *
 * Initialization list that only second vector element is %TRUE
 */
#define CRANK_VEC_BOOL4_J		{FALSE, TRUE, FALSE, FALSE}

/**
 * CRANK_VEC_BOOL4_K:
 *
 * Initialization list that only third vector element is %TRUE
 */
#define CRANK_VEC_BOOL4_K		{FALSE, FALSE, TRUE, FALSE}

/**
 * CRANK_VEC_BOOL4_L:
 *
 * Initialization list that only fourth vector element is %TRUE
 */
#define CRANK_VEC_BOOL4_L		{FALSE, FALSE, FALSE, TRUE}


void			crank_vec_bool4_init 		(	CrankVecBool4*	vec,
												gboolean		x,
												gboolean		y,
												gboolean		z,
												gboolean		w	);

void			crank_vec_bool4_init_arr	(	CrankVecBool4*	vec,
												gboolean*		arr	);

void			crank_vec_bool4_init_valist	(	CrankVecBool4*	vec,
												va_list			varargs	);

void			crank_vec_bool4_init_fill	(	CrankVecBool4*	vec,
												const gboolean	fill	);

CrankVecBool4*	crank_vec_bool4_copy		(	CrankVecBool4*	vec	);

gboolean		crank_vec_bool4_get			(	CrankVecBool4*	vec,
												const guint		index	);

void			crank_vec_bool4_set			(	CrankVecBool4*	vec,
												const guint		index,
												const gboolean	value	);

void			crank_vec_bool4_and			(	CrankVecBool4*	a,
												CrankVecBool4*	b,
												CrankVecBool4*	r	);

void			crank_vec_bool4_or			(	CrankVecBool4*	a,
												CrankVecBool4*	b,
												CrankVecBool4*	r	);

void			crank_vec_bool4_xor			(	CrankVecBool4*	a,
												CrankVecBool4*	b,
												CrankVecBool4*	r	);

void			crank_vec_bool4_not			(	CrankVecBool4*	a,
												CrankVecBool4*	r	);


void			crank_vec_bool4_andv		(	CrankVecBool4*	a,
												CrankVecBool4*	b,
												CrankVecBool4*	r	);

void			crank_vec_bool4_orv			(	CrankVecBool4*	a,
												CrankVecBool4*	b,
												CrankVecBool4*	r	);

void			crank_vec_bool4_notv		(	CrankVecBool4*	a,
												CrankVecBool4*	r	);

gboolean		crank_vec_bool4_get_any		(	CrankVecBool4*	vec	);

gboolean		crank_vec_bool4_get_all		(	CrankVecBool4*	vec	);

gboolean		crank_vec_bool4_equal		(	gconstpointer	a,
												gconstpointer	b	);

guint			crank_vec_bool4_hash		(	gconstpointer	a	);

gchar*			crank_vec_bool4_to_string	(	CrankVecBool4*	vec	);

gchar*			crank_vec_bool4_to_string_full (CrankVecBool4*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	on_true,
												const gchar* 	on_false	);
/**
 * CrankVecBoolN:
 * @data: (array length=n): Data of boolean vector.
 * @n: Size of vector.
 *
 * Arbitarily sized boolean vector.
 */
typedef struct _CrankVecBoolN {
	gboolean*	data;
	guint		n;
} CrankVecBoolN;

#define CRANK_TYPE_VEC_BOOL_N	(crank_vec_bool4_get_type ())
GType			crank_vec_bool_n_get_type	(void);


void			crank_vec_bool_n_init 		(	CrankVecBoolN*	vec,
												const guint		n,
												...	);

void			crank_vec_bool_n_init_arr	(	CrankVecBoolN*	vec,
												const guint		n,
												gboolean*		arr	);

void			crank_vec_bool_n_init_valist (	CrankVecBoolN*	vec,
												const guint		n,
												va_list			varargs	);

void			crank_vec_bool_n_init_fill	(	CrankVecBoolN*	vec,
												const guint		n,
												const gboolean	fill	);

void			crank_vec_bool_n_fini		(	CrankVecBoolN*	vec	);

CrankVecBoolN*	crank_vec_bool_n_copy		(	CrankVecBoolN*	vec	);

void			crank_vec_bool_n_free		(	CrankVecBoolN*	vec	);

gboolean		crank_vec_bool_n_get		(	CrankVecBoolN*	vec,
												const guint		index	);

void			crank_vec_bool_n_set		(	CrankVecBoolN*	vec,
												const guint		index,
												const gboolean	value	);

void			crank_vec_bool_n_and		(	CrankVecBoolN*	a,
												CrankVecBoolN*	b,
												CrankVecBoolN*	r	);

void			crank_vec_bool_n_or			(	CrankVecBoolN*	a,
												CrankVecBoolN*	b,
												CrankVecBoolN*	r	);

void			crank_vec_bool_n_xor		(	CrankVecBoolN*	a,
												CrankVecBoolN*	b,
												CrankVecBoolN*	r	);

void			crank_vec_bool_n_not		(	CrankVecBoolN*	a,
												CrankVecBoolN*	r	);


void			crank_vec_bool_n_andv		(	CrankVecBoolN*	a,
												CrankVecBoolN*	b,
												CrankVecBoolN*	r	);

void			crank_vec_bool_n_orv		(	CrankVecBoolN*	a,
												CrankVecBoolN*	b,
												CrankVecBoolN*	r	);

void			crank_vec_bool_n_notv		(	CrankVecBoolN*	a,
												CrankVecBoolN*	r	);

guint			crank_vec_bool_n_get_size	(	CrankVecBoolN*	vec	);

gboolean		crank_vec_bool_n_get_any	(	CrankVecBoolN*	vec	);

gboolean		crank_vec_bool_n_get_all	(	CrankVecBoolN*	vec	);

gboolean		crank_vec_bool_n_equal		(	gconstpointer	a,
												gconstpointer	b	);

guint			crank_vec_bool_n_hash		(	gconstpointer	a	);

gchar*			crank_vec_bool_n_to_string	(	CrankVecBoolN*	vec	);

gchar*			crank_vec_bool_n_to_string_full (CrankVecBoolN*	vec,
												const gchar*	left,
												const gchar*	in,
												const gchar*	right,
												const gchar*	on_true,
												const gchar* 	on_false	);
						
G_END_DECLS

#endif //CRANKBOOLVEC_H
