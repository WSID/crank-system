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

#include <ffi.h>

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

// 내부 전용 함수
static ffi_type*   _crank_func_type_ffit_from_gtype (   const GType type);
static ffi_type**  _crank_func_type_ffits_from_gtypes ( const GType* types,
     													const guint ntypes);




/**
 * CrankFuncType:
 * 
 * 함수의 반환형과 인자의 형을 저장합니다.
 */
struct _CrankFuncType {
	GType   return_type;
	GType*  param_types;
	uint    nparam_types;

	ffi_type**		param_types_ffi;
	ffi_cif			func_type_ffi;

	uint	  _refc;
};

G_DEFINE_BOXED_TYPE (CrankFuncType, crank_func_type, crank_func_type_ref, crank_func_type_unref);


/**
 * crank_func_type_new:
 * @return_type: 함수의 반환형입니다.
 * @...: 함수의 인자형 들입니다. %G_TYPE_NONE으로 끝을 표시합니다.
 * 
 * 새로운 #CrankFuncType을 만듭니다.
 * 
 * Returns: (transfer full): 새로운 CrankFuncType입니다.
 */
CrankFuncType*
crank_func_type_new (const GType return_type, ...)
{
	CrankFuncType*  ftype;
	va_list			varargs;

	va_start (varargs, return_type);
	ftype = crank_func_type_new_va (return_type, varargs);
	va_end (varargs);

	return ftype;
}


/**
 * crank_func_type_new_va:
 * @return_type: 함수의 반환형입니다.
 * @varargs: 함수의 인자형 들입니다. %G_TYPE_NONE으로 끝을 표시합니다.
 * 
 * 새로운 #CrankFuncType을 만듭니다.
 * 
 * Returns: (transfer full): 새로운 CrankFuncType입니다.
 */
CrankFuncType*
crank_func_type_new_va (const GType return_type, va_list varargs)
{
	CrankFuncType*  ftype;
	guint			param_types_alloc;
	guint			i;
	ffi_status		func_type_ffi_status;
	
	// return_type을 채워 넣습니다.
	ftype = g_new(CrankFuncType, 1);

	ftype->return_type = return_type;
	
	// param_types를 채워 넣습니다.
	param_types_alloc = 0;
	ftype->param_types = NULL;
	ftype->nparam_types = 0;

	CRANK_FOREACH_VALIST_BEGIN (varargs, GType, varargs_type, G_TYPE_NONE)

		if (param_types_alloc <= ftype->nparam_types) {
			param_types_alloc = (param_types_alloc == 0) ?
				1 :
				param_types_alloc << 1;
			
			ftype->param_types = g_renew (GType, ftype->param_types, param_types_alloc);
		}
	
		ftype->param_types[ftype->nparam_types] = varargs_type;
		ftype->nparam_types++;

	CRANK_FOREACH_VALIST_END

	ftype->param_types = g_renew (GType, ftype->param_types, ftype->nparam_types);

	
	// param_types_ffi를 생성합니다.
	ftype->param_types_ffi =
		_crank_func_type_ffits_from_gtypes (ftype->param_types, ftype->nparam_types);

	// func_type_ffi를 생성합니다.
	func_type_ffi_status = ffi_prep_cif (&ftype->func_type_ffi,
	        FFI_DEFAULT_ABI,
	        ftype->nparam_types,
	        _crank_func_type_ffit_from_gtype (ftype->return_type),
	        ftype->param_types_ffi  );

	if (func_type_ffi_status != FFI_OK) {
		g_warning ("ffi_cif preparation failed!");
	}
	
	ftype->_refc = 1;

	return ftype;
}


/**
 * crank_func_type_new_with_types:
 * @return_type: 함수의 반환형입니다.
 * @param_types: 함수가 받아들이는 인자 형입니다.
 * @nparam_types: @param_types의 길이입니다.
 * 
 * 새로운 #CrankFuncType을 만듭니다.
 * 
 * Returns: (transfer full): 새로운 #CrankFuncType입니다.
 */
CrankFuncType*
crank_func_type_new_with_types (
         const GType return_type,
         const GType* param_types,
         const guint nparam_types)
{
	CrankFuncType*  ftype;
	guint			i;
	ffi_status		func_type_ffi_status;
	
	// return_type을 채워 넣습니다.
	ftype = g_new(CrankFuncType, 1);

	ftype->return_type = return_type;
	
	// param_types를 채워 넣습니다.
	ftype->nparam_types = nparam_types;
	ftype->param_types = CRANK_ARRAY_DUP (param_types, GType, nparam_types);
	
	// param_types_ffi를 생성합니다.
	ftype->param_types_ffi =
		_crank_func_type_ffits_from_gtypes (ftype->param_types, ftype->nparam_types);

	// func_type_ffi를 생성합니다.
	func_type_ffi_status = ffi_prep_cif (&ftype->func_type_ffi,
	        FFI_DEFAULT_ABI,
	        ftype->nparam_types,
	        _crank_func_type_ffit_from_gtype (ftype->return_type),
	        ftype->param_types_ffi  );

	if (func_type_ffi_status != FFI_OK) {
		g_warning ("ffi_cif preparation failed!");
	}
	
	ftype->_refc = 1;

	return ftype;
}

/**
 * crank_func_type_ref:
 * @ftype: 참조를 증가시킬 #CrankFuncType
 * 
 * Returns: 참조가 증가된 @ftype
 */
CrankFuncType*
crank_func_type_ref (CrankFuncType* ftype)
{
	g_atomic_int_inc (&ftype->_refc);
	return ftype;
}

/**
 * crank_func_type_unref:
 * @ftype: 참조를 감소시킬 #CrankFuncType
 */
void
crank_func_type_unref (CrankFuncType* ftype)
{
	if (g_atomic_int_dec_and_test(&ftype->_refc)) {
		g_free (ftype->param_types);
		g_free (ftype->param_types_ffi);
		g_free (ftype);
	}
}

/**
 * crank_func_type_get_return_type:
 * @ftype: 반환형을 조회할 #CrankFuncType
 * 
 * Returns: 함수 반환 형입니다.
 */
GType
crank_func_type_get_return_type (const CrankFuncType* ftype) {
	return ftype->return_type;
}

/**
 * crank_func_type_get_param_type:
 * @ftype: 인자 형을 조회할 #CrankFuncType
 * @index: 인자의 위치입니다.
 * 
 * Returns: 함수 반환 형입니다. 부적절한 @index에 대해 %G_TYPE_NONE을 반환합니다.
 */
GType
crank_func_type_get_param_type (const CrankFuncType* ftype,
        const guint index)
{
	return (index < ftype->nparam_types) ? ftype->param_types[index] : G_TYPE_NONE;
}

/**
 * crank_func_type_get_nparam_types:
 * @ftype: 인자의 개수를 조회할 #CrankFuncType
 * 
 * Returns: 인자의 개수입니다.
 */
guint
crank_func_type_get_nparam_types (const CrankFuncType* ftype)
{
	return ftype->nparam_types;
}

/**
 * crank_func_type_get_param_types:
 * @ftype: 인자의 형을 조회할 #CrankFuncType
 * @length: 인자의 형의 갯수입니다.
 * 
 * Returns: 인자 형의 배열입니다.
 */
GType*
crank_func_type_get_param_types (const CrankFuncType* ftype,
        guint* length)
{
	if (length != NULL) *length = ftype->nparam_types;

	return CRANK_ARRAY_DUP (ftype->param_types, GType, ftype->nparam_types);
}

/*
 * _crank_func_type_ffit_from_gtype:
 * @type: ffi_type을 얻을 #GType
 * 
 * GType에 해당하는 기본 ffi_type을 얻습니다. 구조체나 공유체를 함수로 넘길 일이
 * 없으므로 이에 대한 처리는 하지 않습니다.
 * 
 * Returns: (transfer none): ffi_type입니다.
 */
ffi_type*
_crank_func_type_ffit_from_gtype (const GType type) {
	switch (type) {
		case G_TYPE_INVALID:
			return NULL;
		case G_TYPE_NONE:
			return &ffi_type_void;
		case G_TYPE_CHAR:
			return &ffi_type_schar;
		case G_TYPE_UCHAR:
			return &ffi_type_uchar;
		case G_TYPE_BOOLEAN:
			return &ffi_type_sint;
		case G_TYPE_INT:
			return &ffi_type_sint;
		case G_TYPE_UINT:
			return &ffi_type_uint;
		case G_TYPE_LONG:
			return &ffi_type_slong;
		case G_TYPE_ULONG:
			return &ffi_type_ulong;
		case G_TYPE_INT64:
			return &ffi_type_sint64;
		case G_TYPE_UINT64:
			return &ffi_type_uint64;
		case G_TYPE_ENUM:
		case G_TYPE_FLAGS:
			return &ffi_type_sint;
		case G_TYPE_FLOAT:
			return &ffi_type_float;
		case G_TYPE_DOUBLE:
			return &ffi_type_double;
		case G_TYPE_POINTER:
		case G_TYPE_STRING:
		case G_TYPE_BOXED:
		case G_TYPE_PARAM:
		case G_TYPE_OBJECT:
		case G_TYPE_VARIANT:
		case G_TYPE_INTERFACE:
			return &ffi_type_pointer;
		default:
			if (type == G_TYPE_GTYPE)
				return &ffi_type_ulong;
			else if (G_TYPE_IS_ENUM(type) || G_TYPE_IS_FLAGS(type))
				return &ffi_type_sint;
			
			else return &ffi_type_pointer;
	}
}

/*
 * _crank_func_type_ffits_from_gtypes:
 * @types: (array length=ntypes): ffi_type 배열을 얻을 #GType입니다.
 * @ntypes: types의 길이입니다.
 * 
 * ffi_type의 배열을 생성합니다.
 * 
 * Returns: (transfer container): ffi_type의 배열입니다. 사용이 끝나면 g_free()로 해제해야 합니다.
 */
ffi_type**
_crank_func_type_ffits_from_gtypes (const GType* types,
									const guint ntypes)
{
	ffi_type** ffits;
	uint i;
	
	ffits = g_new(ffi_type*, ntypes);

	for (i = 0; i < ntypes; i++)
		ffits[i] = _crank_func_type_ffit_from_gtype (types[i]);

	return ffits;
}


/**
 * CrankFuncHolder:
 * 
 * 함수와 인자의 형을 모두 저장하는 홀더입니다.
 *
 * 일반적으로 프로그램에서 쓰이지 않고, Crank System에서 내부적으로 사용합니다.
 */
struct _CrankFuncHolder {
	GCallback		function;
	void* 			userdata;
	GDestroyNotify  userdata_destroy;
	
	gboolean  is_value_function;


	GType   return_type;
	GType*  param_types;
	uint    nparam_types;
};

G_DEFINE_BOXED_TYPE (CrankFuncHolder, crank_func_holder, crank_func_holder_copy, crank_func_holder_free)



/**
 * crank_func_holder_new:
 * @callback: (scope notified): 콜백 함수입니다.
 * @userdata: (closure): @callback이 가지고 있는 추가적인 내용입니다.
 * @userdata_destroy: @userdata을 해제할 함수입니다.
 * @return_type: @callback이 반환하는 종류
 * @...: @callback이 받아들이는 인자 목록
 *
 * Returns: (transfer full): 새로 생성된 #CrankFuncHolder
 */
CrankFuncHolder*
crank_func_holder_new (const GCallback callback,
                            const gpointer userdata,
                            const GDestroyNotify userdata_destroy,
                            const GType return_type,
                            ... )
{
	CrankFuncHolder*  holder;

	uint              param_types_alloc;

	holder = g_new (CrankFuncHolder, 1);

	holder->function = callback;
	holder->userdata = userdata;
	holder->userdata_destroy = userdata_destroy;

	holder->is_value_function = FALSE;

	holder->return_type = return_type;

	// Read varargs
	param_types_alloc = 0;
	holder->param_types = NULL;
	holder->nparam_types = 0;

	CRANK_FOREACH_VARARG_BEGIN (return_type, GType, varargs_type, G_TYPE_NONE)

		if (param_types_alloc <= holder->nparam_types) {
			param_types_alloc = (param_types_alloc == 0) ?
				1 :
				param_types_alloc << 1;
			
			holder->param_types = g_renew (GType, holder->param_types, param_types_alloc);
		}
	
		holder->param_types[holder->nparam_types] = varargs_type;
		holder->nparam_types++;

	CRANK_FOREACH_VARARG_END

	holder->param_types = g_renew (GType, holder->param_types, holder->nparam_types);

	return holder;
}

/**
 * crank_func_holder_new_with_type:
 * @callback: (scope notified): 추가할 콜백 함수입니다.
 * @userdata: (closure): @callback이 가지고 있는 추가적인 함수입니다.
 * @userdata_destroy: @userdata을 해제할 함수입니다.
 * @return_type: @callback이 반환하는 종류
 * @param_types: (array length=nparam_types) (allow-none): @callback이 받아들이는 인자 목록
 * @nparam_types: @param_types의 갯수
 *
 * Returns: (transfer full): 새로 생성된 #CrankFuncHolder
 *
 */
CrankFuncHolder*
crank_func_holder_new_with_type (const GCallback callback,
                                 const gpointer userdata,
                                 const GDestroyNotify userdata_destroy,
                                 const GType return_type,
                                 const GType* param_types,
                                 const uint nparam_types)
{
	CrankFuncHolder*  holder;

	uint              param_types_alloc;

	holder = g_new (CrankFuncHolder, 1);

	holder->function = callback;
	holder->userdata = userdata;
	holder->userdata_destroy = userdata_destroy;
	holder->is_value_function = FALSE;

	holder->return_type = return_type;

	holder->param_types = g_memdup (param_types, nparam_types * sizeof (GType));
	holder->nparam_types = nparam_types;

	return holder;
}

CrankFuncHolder*
crank_func_holder_copy (const CrankFuncHolder* holder)
{
  return crank_func_holder_new_with_type (
  		holder->function,
  		holder->userdata,
  		holder->userdata_destroy,
  		holder->return_type,
  		holder->param_types,
  		holder->nparam_types);
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
