#ifndef CRANKFUNCCLOSURE_H
#define CRANKFUNCCLOSURE_H

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

struct _CrankFuncHolder;
typedef struct _CrankFuncHolder CrankFuncHolder;

#define crank_func_holder_new(callback, userdata, ...) \
    crank_func_holder_new_rawc (callback, userdata, __VA_ARGS__, G_TYPE_NONE)


G_GNUC_MALLOC
CrankFuncHolder*  crank_func_holder_new_rawc (const GCallback callback,
                                              const gpointer useradata,
                                              const GType return_type,
                                              ... );

/*
GClosure  crank_func_closure_new_with_type (GCallback callback,
											gpointer userdata,
											GType return_type,
											GType* param_type,
											uint   nparam_type);
*/

void  crank_func_holder_free (CrankFuncHolder*  holder);

//gboolean  crank_func_closure_check_type (GType *types,
//                                         uint   ntypes);

//gboolean  crank_func_closure_check (GValue *values, uint nvalues);

G_END_DECLS

#endif /* CRANKFUNCCLOSURE_H */
