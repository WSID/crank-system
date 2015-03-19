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
#define _CRANKBASE_INSIDE

#include <stdarg.h>
#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankfuncholder.h"

/**
 * SECTION: crankfuncholder
 * @short_description: 함수와 타입을 저장하는 자료 구조
 * @title: CrankFuncHolder
 * @stability: Unstable
 * @include: crankbase.h
 */

/**
 * CrankFuncHolder:
 * 함수와 인자의 형을 모두 저장하는 홀더입니다.
 *
 * 일반적으로 프로그램에서 쓰이지 않고, Crank System에서 내부적으로 사용합니다.
 */
struct _CrankFuncHolder {
  GCallback function;
  gboolean  is_value_function;


  GType   return_type;
  GType*  param_types;
  uint    nparam_types;
};

/**
 * crank_func_holder_new:
 * @callback: 추가할 콜백 함수입니다.
 * @userdata: @callback이 가지고 있는 추가적인 함수입니다.
 * @return_type: @callback이 반환하는 종류
 * @...: @callback이 받아들이는 인자 목록
 *
 * Returns: 새로 생성된 #CrankFuncHolder
 *
 */
CrankFuncHolder*
crank_func_holder_new_rawc (const GCallback callback,
                            const gpointer useradata,
                            const GType return_type,
                            ... )
{
  CrankFuncHolder*  holder;

  uint              param_types_alloc;

  holder = g_new (CrankFuncHolder, 1);

  holder->function = callback;
  holder->is_value_function = FALSE;

  holder->return_type = return_type;

  // Read varargs
  param_types_alloc = 0;
  holder->nparam_types = 0;
  
  CRANK_FOREACH_VARARG_BEGIN (return_type, GType, varargs_type, G_TYPE_NONE)
  
    if (param_types_alloc == 0) {
      param_types_alloc = 1;
      holder->param_types = g_new (GType, 1);
    }
    else if (param_types_alloc <= holder->nparam_types) {
      param_types_alloc <<= 1;
      holder->param_types = g_renew (GType, holder->param_types, param_types_alloc);
    }
    holder->param_types[holder->nparam_types] = varargs_type;
    holder->nparam_types++;
    
  CRANK_FOREACH_VARARG_END

  holder->param_types = g_renew (GType, holder->param_types, holder->nparam_types);

  return holder;
}

/**
 * crank_func_holder_free:
 * @holder: 메모리 해제할 #CrankFuncHolder입니다.
 */
void
crank_func_holder_free (CrankFuncHolder* holder) {
  g_free (holder->param_types);
  g_free (holder);
}
