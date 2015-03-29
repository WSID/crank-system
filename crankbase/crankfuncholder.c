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



// 내부 전용 함수
static void			_transform_crank_func_type_string (	const GValue* value_ftype,
														GValue* value_string	);
/**
 * CrankFuncType:
 * 
 * 함수의 반환형과 인자의 형을 저장합니다.
 */
struct _CrankFuncType {
	GType   return_type;
	GType*  param_types;
	uint    nparam_types;
	
	uint	  _refc;
};

G_DEFINE_BOXED_TYPE_WITH_CODE (
        CrankFuncType,
        crank_func_type,
        crank_func_type_ref,
        crank_func_type_unref,
        {
			g_value_register_transform_func (
			        g_define_type_id,
			        G_TYPE_STRING,
			        _transform_crank_func_type_string);
		} );





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

	ftype->_refc = 1;

	return ftype;
}


/**
 * crank_func_type_new_with_types:
 * @return_type: 함수의 반환형입니다.
 * @param_types: (array length=nparam_types): 함수가 받아들이는 인자 형입니다.
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
	
	// return_type을 채워 넣습니다.
	ftype = g_new(CrankFuncType, 1);

	ftype->return_type = return_type;
	
	// param_types를 채워 넣습니다.
	ftype->nparam_types = nparam_types;
	ftype->param_types = CRANK_ARRAY_DUP (param_types, GType, nparam_types);
	
	ftype->_refc = 1;

	return ftype;
}



/**
 * crank_func_type_ref:
 * @ftype: 참조를 증가시킬 #CrankFuncType
 *
 * #CrankFuncType의 참조를 1 증가시킵니다. 
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
 *
 * #CrankFuncType의 참조를 1 감소시킵니다. 레퍼런스 카운트가 0이되면 자원이 해제됩니다.
 */
void
crank_func_type_unref (CrankFuncType* ftype)
{
	if (g_atomic_int_dec_and_test(&ftype->_refc)) {
		g_free (ftype->param_types);
		g_free (ftype);
	}
}



/**
 * crank_func_type_hash:
 * @v: (type CrankFuncType): 해시 값을 얻을 #CrankFuncType
 *
 * #CrankFuncType을 #GHashTable 등에 키 값으로 사용할 경우 이 함수를 사용할 수
 * 있습니다.
 * 
 * Returns: 해시 값입니다.
 */
guint
crank_func_type_hash (gconstpointer v)
{
	CrankFuncType* ftype;
	guint hash;
	guint i;

	ftype = (CrankFuncType*)v;
	hash = 0;

	hash += g_direct_hash ((gconstpointer) ftype->return_type);

	for (i = 0; i < ftype->nparam_types; i++) 
		hash += g_direct_hash ((gconstpointer) ftype->param_types[i]);

	hash += g_direct_hash ((gconstpointer) ftype->nparam_types);
	return hash;
}

/**
 * crank_func_type_equal:
 * @a: (type CrankFuncType): 비교할 #CrankFuncType
 * @b: (type CrankFuncType): 비교할 #CrankFuncType
 *
 * #CrankFuncType을 #GHashTable 등에 키 값으로 사용할 경우 이 함수를 사용할 수
 * 있습니다.
 * 
 * Returns: 두 타입이 같은지를 알려줍니다.
 */
gboolean
crank_func_type_equal (gconstpointer a, gconstpointer b) {
	CrankFuncType* ftype_a;
	CrankFuncType* ftype_b;
	guint i;

	ftype_a = (CrankFuncType*)a;
	ftype_b = (CrankFuncType*)b;

	if (ftype_a->return_type != ftype_b->return_type) return FALSE;

	if (ftype_a->nparam_types != ftype_b->nparam_types) return FALSE;
	for (i = 0; i < ftype_a->nparam_types; i++)
		if (ftype_a->param_types[i] != ftype_b->param_types[i]) return FALSE;
	

	return TRUE;
}

/**
 * crank_func_type_to_string:
 * @ftype: 문자열로 변환할 #CrankFuncType
 * 
 * #CrankFuncType을 문자열로 변환합니다. 형식은 다음과 같습니다.
 * 
 * <programlisting>
 * RTYPE (PARAM, PARAM)
 * </programlisting>
 *
 * 만일 형식 gchar* (*)(gint, gint)를 나타내는 경우 다음으로 표현됩니다.
 * 
 * <programlisting>
 * guchararray (gint, gint)
 * </programlisting>
 * 
 * Returns: (transfer full): 문자열입니다. 사용이 끝난 후 g_free()로 해제해야 합니다.
 */
gchar*
crank_func_type_to_string (const CrankFuncType* ftype) {
	GString*	result;
	gchar*		result_str;
	guint		i;

	result = g_string_new (NULL);

	g_string_append (result, g_type_name (ftype->return_type));
	g_string_append (result, " (");

	if (ftype->nparam_types != 0)
	    g_string_append (result, g_type_name (ftype->param_types[0]));
	
	for (i = 1; i < ftype->nparam_types; i++) {
		g_string_append (result, ", ");
		g_string_append (result, g_type_name(ftype->param_types[i]));
	}
	
	g_string_append_c (result, ')');

	result_str = result->str;

	g_string_free (result, FALSE);
	
	return result_str;
}




/**
 * crank_func_type_get_return_type:
 * @ftype: 반환형을 조회할 #CrankFuncType
 *
 * 반환형을 조회합니다.
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
 * @index번째 인자의 형을 조회합니다. 
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
 * 인자의 갯수를 조회합니다.
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
 * 인자 형을 배열로 조회합니다.
 *
 * Returns: (array length=length) (transfer container): 인자 형의 배열입니다. 사용후 g_free()로 해제합니다.
 */
GType*
crank_func_type_get_param_types (const CrankFuncType* ftype,
        guint* length)
{
	if (length != NULL) *length = ftype->nparam_types;

	return CRANK_ARRAY_DUP (ftype->param_types, GType, ftype->nparam_types);
}


/**
 * crank_func_type_compatible_to:
 * @from: 비교될 원 함수 형입니다.
 * @to: 비교할 함수 형입니다.
 * 
 * 두 형을 비교하여 @from이 @to에 대입될 수 있는지 확인합니다.
 * 
 * 이는 다음과 같습니다.
 * 
 * - @from의 반환형은 @to의 반환형의 하위 종류입니다.
 * - @from의 인자 수는 @to의 인자 수보다 적거나 같습니다.
 * - @to의 각 인자 형은 @from의 인자 형의 하위 종류입니다.
 * 
 * 간단히 is-a 관계라고 생각하면 됩니다.
 * 
 * Returns: @to가 @from에 대입될 수 있는 경우 %TRUE입니다.
 */
gboolean
crank_func_type_compatible_to  (	const CrankFuncType* from,
    								const CrankFuncType* to		)
{
	guint i;
	guint i_end;

	if (	(! g_type_is_a (from->return_type, to->return_type)) ||
	        (to->nparam_types < from->nparam_types)				)
		return FALSE;
	
	i_end = from->nparam_types;

	for (i = 0; i < i_end; i++) {
		if (! g_type_is_a (to->param_types[i], from->param_types[i]))
			return FALSE;
	}
	return TRUE;	
}
	

/**
 * crank_func_type_arg_match_exactually:
 * @ftype: 주어진 인자목록과 비교할 #CrankFuncType입니다.
 * @args: (array length=arg_length): 인자 목록입니다.
 * @arg_length: @args의 길이입니다.
 *
 * 주어진 인자 타입 목록과 비교하여, 정확히 일치하는지 확인합니다.
 *
 * Returns: 정확히 일치하는지 입니다.
 */
gboolean
crank_func_type_arg_match_exactually (	const CrankFuncType* ftype,
										const GType*		 args,
										const uint			 arg_length	)
{
	if (ftype->nparam_types != arg_length) return FALSE;
	
	return (CRANK_ARRAY_CMP (ftype->param_types, args, GType, arg_length) == 0);
}

/**
 * crank_func_type_arg_match:
 * @ftype: 주어진 인자목록과 비교할 #CrankFuncType입니다.
 * @args: (array length=arg_length): 인자 목록입니다.
 * @arg_length: @args의 길이입니다.
 *
 * 주어진 인자 타입 목록과 비교하여, 해당 타입들이 사용 가능한지 확인합니다..
 *
 * Returns: 해당 타입을 사용할 수 있는지 입니다.
 */
gboolean
crank_func_type_arg_match (	const CrankFuncType* ftype,
							const GType*		 args,
							const guint			 arg_length	)
{
	gint i;
	
	if (ftype->nparam_types != arg_length) return FALSE;
	
	for (i = 0; i < arg_length; i ++) {
		if (! g_type_is_a (args[i], ftype->param_types[i]))
			return FALSE;
	}
	return TRUE;
}

/**
 * crank_func_type_arg_match_transformable:
 * @ftype: 주어진 인자목록과 비교할 #CrankFuncType입니다.
 * @args: (array length=arg_length): 인자 목록입니다.
 * @arg_length: @args의 길이입니다.
 *
 * 주어진 인자 타입 목록과 비교하여, 해당 타입들을 변환을 통해서라도 사용 가능한지
 * 확인합니다. 
 *
 * Returns: 해당 타입을 사용할 수 있는지 입니다.
 */
gboolean
crank_func_type_arg_match_transformable (	const CrankFuncType* ftype,
											const GType*		 args,
											const guint			 arg_length	)
{
	gint i;
	
	if (ftype->nparam_types != arg_length) return FALSE;
	
	for (i = 0; i < arg_length; i ++) {
		if (! g_value_type_transformable (args[i], ftype->param_types[i]))
			return FALSE;
	}
	return TRUE;
}



static void
_transform_crank_func_type_string (	const GValue* value_ftype,
									GValue* value_string	)
{
	CrankFuncType* ftype;

	ftype = g_value_get_boxed (value_ftype);
	g_value_take_string (value_string, crank_func_type_to_string (ftype));
}








/**
 * CrankFuncHolder:
 * 
 * 함수와 인자의 형을 모두 저장하는 홀더입니다.
 *
 * 일반적으로 프로그램에서 쓰이지 않고, Crank System에서 내부적으로 사용합니다.
 */
struct _CrankFuncHolder {
	GClosure parent_instance;
	
	// TODO: GClosure 그래프 : 타입에 해당하는 GClusure를 저장하고 조회해야 합니다.
};
