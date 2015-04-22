#ifndef CRANKFUNCHOLDER_H
#define CRANKFUNCHOLDER_H

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
#error crankfuncholder.h cannot be included directly.
#endif

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/**
 * CrankCallback: (skip)
 * @userdata: (closure): 더미입니다.
 *
 * @userdata를 받아들이는 임이의 함수를 상징합니다.
 *
 * 이는 실질적인 함수 형으로 사용되기 보다는 임의의 함수를 받아들일수 있는
 * 인자를 표시하는 목적으로 사용됩니다.
 */
typedef void		(*CrankCallback) (	gpointer	userdata	);


struct _CrankFuncType;
typedef struct _CrankFuncType CrankFuncType;

#define CRANK_TYPE_FUNC_TYPE (crank_func_type_get_type ())

GType crank_func_type_get_type (void);



G_GNUC_MALLOC
CrankFuncType*  crank_func_type_new (
        const GType return_type,
        ...);

G_GNUC_MALLOC
CrankFuncType*  crank_func_type_new_va (
        const GType return_type,
        va_list varargs);

G_GNUC_MALLOC
CrankFuncType*  crank_func_type_new_with_types (
        const GType return_type,
        const GType* param_types,
        const guint nparam_types);

CrankFuncType*  crank_func_type_ref (				CrankFuncType*			ftype);
void			crank_func_type_unref (				CrankFuncType*			ftype);

guint			crank_func_type_hash (				gconstpointer			v);
gboolean		crank_func_type_equal (				gconstpointer			a,
								 					gconstpointer			b);
gchar*			crank_func_type_to_string (			const CrankFuncType*	ftype);


GType			crank_func_type_get_return_type (	const CrankFuncType*	ftype);
GType			crank_func_type_get_param_type (	const CrankFuncType*	ftype,
    												const guint 			index);
guint			crank_func_type_get_nparam_types (	const CrankFuncType*	ftype);
GType*			crank_func_type_get_param_types (	const CrankFuncType*	ftype,
    												guint*					length);

gboolean		crank_func_type_compatible_to  (	const CrankFuncType*	from,
    												const CrankFuncType*	to);


gboolean		crank_func_type_arg_match_exactually (	const CrankFuncType* ftype,
														const GType*		 args,
														const uint			 arg_length	);

gboolean		crank_func_type_arg_match (			const CrankFuncType* 	ftype,
													const GType*		 	args,
													const guint			 	arg_length	);

gboolean		crank_func_type_arg_match_transformable (	const CrankFuncType* ftype,
															const GType*		 args,
															const guint			 arg_length	);




struct _CrankFuncHolder;
typedef struct _CrankFuncHolder CrankFuncHolder;

#define	CRANK_TYPE_FUNC_HOLDER	(crank_func_holder_get_type())
GType				crank_func_holder_get_type (void);


G_GNUC_MALLOC
CrankFuncHolder*	crank_func_holder_new (			const gchar*		name	);

G_GNUC_MALLOC
CrankFuncHolder*	crank_func_holder_new_quark (	const GQuark		name	);


CrankFuncHolder*	crank_func_holder_ref (			CrankFuncHolder*	holder	);

void				crank_func_holder_unref (		CrankFuncHolder*	holder	);


void				crank_func_holder_set_name (	CrankFuncHolder*	holder,
													const gchar*		name	);

const gchar*		crank_func_holder_get_name (	CrankFuncHolder*	holder	);

void				crank_func_holder_set_qname (	CrankFuncHolder*	holder,
													const GQuark		name	);

GQuark				crank_func_holder_get_qname (	CrankFuncHolder*	holder	);


void				crank_func_holder_set (			CrankFuncHolder*	holder,
													CrankFuncType*		ftype,
							   						GClosure*			closure	);
							   						
void				crank_func_holder_set_func (	CrankFuncHolder*	holder,
													CrankFuncType*		ftype,
							   						CrankCallback		func,
							   						gpointer			userdata,
							   						GDestroyNotify		userdata_destroy,
							   						GClosureMarshal		marshal	);

GClosure*			crank_func_holder_get (			CrankFuncHolder*	holder,
													CrankFuncType*		ftype	);

GClosure*			crank_func_holder_get_by_param_types (	CrankFuncHolder*	holder,
													const GType*		param_types,
													const guint			nparam_types	);

GClosure*			crank_func_holder_lookup (		CrankFuncHolder*	holder,
													CrankFuncType*		ftype	);
	
GClosure*			crank_func_holder_lookup_by_param_types (	CrankFuncHolder*	holder,
													const GType*		param_types,
													const guint			nparam_types	);
	
GType				crank_func_holder_lookup_return_type (	CrankFuncHolder*	holder,
													const GType*		param_types,
													const guint			nparam_types	);

gboolean			crank_func_holder_remove (		CrankFuncHolder*	holder,
													CrankFuncType*		ftype	);

gboolean			crank_func_holder_remove_by_param_types (		CrankFuncHolder*	holder,
													const GType*		param_types,
													const guint			nparam_types	);

gboolean			crank_func_holder_invoke (		CrankFuncHolder*	holder,
						                      		GValue*				return_value,
						                      		const guint      	narg_values,
						                      		const GValue*   	arg_values,
						                      		gpointer         	invocation_hint);

//gboolean  crank_func_closure_check_type (GType *types,
//                                         uint   ntypes);

//gboolean  crank_func_closure_check (GValue *values, uint nvalues);



struct _CrankFuncBook;
typedef struct _CrankFuncBook CrankFuncBook;

#define CRANK_TYPE_FUNC_BOOK	(crank_func_book_get_type())
GType	crank_func_book_get_type (void);

CrankFuncBook*		crank_func_book_new (void);

CrankFuncBook*		crank_func_book_new_with_name (	const gchar*		name	);

CrankFuncBook*		crank_func_book_new_with_qname (const GQuark		name	);

CrankFuncBook*		crank_func_book_ref (			CrankFuncBook*		book	);

void				crank_func_book_unref (			CrankFuncBook*		book	);

void				crank_func_book_set_name (		CrankFuncBook*		book,
													const gchar*		name	);

const gchar*		crank_func_book_get_name (		CrankFuncBook*		book	);

void				crank_func_book_set_qname (		CrankFuncBook*		book,
													const GQuark		name	);

GQuark				crank_func_book_get_qname (		CrankFuncBook*		book	);


void				crank_func_book_add (			CrankFuncBook*		book,
													CrankFuncHolder*	holder	);

CrankFuncHolder*	crank_func_book_get (			CrankFuncBook*		book,
													const gchar*		name	);

CrankFuncHolder*	crank_func_book_getq (			CrankFuncBook*		book,
													const GQuark		name	);

gboolean			crank_func_book_remove_by_name (CrankFuncBook*		book,
													const gchar*		name	);

gboolean			crank_func_book_remove(			CrankFuncBook*	book,
													CrankFuncHolder*	holder	);


void				crank_func_book_add_closure (	CrankFuncBook*		book,
													const gchar*		name,
													CrankFuncType*		ftype,
													GClosure*			closure	);

gboolean			crank_func_book_invoke (		CrankFuncBook*		book,
													const gchar*		name,
													GValue*				return_value,
													const guint			narg_values,
													const GValue*		arg_values,
													gpointer			invocation_hint	);
													
gboolean			crank_func_book_invoke_quark (	CrankFuncBook*		book,
													const GQuark		name,
													GValue*				return_value,
													const guint			narg_values,
													const GValue*		arg_values,
													gpointer			invocation_hint	);


G_END_DECLS

#endif /* CRANKFUNCHOLDER_H */
