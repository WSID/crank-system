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



void				crank_func_holder_set (			CrankFuncHolder*	holder,
							   						const GType*		types,
							   						const guint			ntypes,
							   						GClosure*			closure	);

GClosure*			crank_func_holder_get (			CrankFuncHolder*	holder,
                                   					const GType*		types,
                                   					const guint      	ntypes);

GClosure*			crank_func_holder_lookup (		CrankFuncHolder*	holder,
									  				const GType*		types,
									  				const guint			ntypes	);

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

G_END_DECLS

#endif /* CRANKFUNCHOLDER_H */
