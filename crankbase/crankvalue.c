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

/**
 * SECTION: crankvalue
 * @short_description: GValue을 사용하기 위한 함수 모음입니다.
 * @title: GValue 사용 유틸리티
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 이 섹션의 함수 목록은 #GValue을 취급하기 위한 함수들의 목록입니다.
 *
 * #GValue은 사용에 앞서 초기화를 해주어야 합니다. 이 함수들은 이러한 과정을
 * 수행하여, 번거로움을 감소시킵니다.
 *
 * Crank System은 두 부류의 함수를 제공합니다.
 *
 * * 단일의 #GValue를 조작하는 함수들.
 * * #GValue의 C 배열을 조작하는 함수들.
 *
 * 이 함수들은 C/C++에서 사용하기 위해 만들어 졌습니다. Vala나 pyGObject등에서는
 * 각각 지원 기능이 있으므로 해당 기능을 사용하기 바랍니다.
 */

#define _CRANKBASE_INSIDE

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankvalue.h"

/**
 * crank_value_overwrite_init: (skip)
 * @value: (out caller-allocates): 설정할 GValue입니다.
 * @type: 설정할 타입입니다.
 *
 * 값을 초기화하고 기타 자원들을 해제한 후, 해당 @type으로 초기화합니다.
 */
void
crank_value_overwrite_init	(	GValue*		value,
							  	const GType	type	)
{
	if (G_IS_VALUE(value)) g_value_unset (value);

  	g_value_init (value, type);
}

/**
 * crank_value_overwrite: (skip)
 * @value: (out caller-allocates): 설정할 GValue입니다.
 * @from: @value의 값으로 설정할 GValue입니다.
 *
 * @value의 값을 @from의 값으로 설정합니다.
 */
void
crank_value_overwrite (	GValue*			value,
					   	const GValue*	from	)
{
	if (G_IS_VALUE (value)) g_value_unset (value);
	
	if ((from != NULL) && (G_IS_VALUE (from))) {
	  	crank_value_overwrite_init (value, G_VALUE_TYPE(from));
	  	g_value_copy (from, value);
	}
}

/**
 * crank_value_overwrite_boolean: (skip)
 * @value: (out caller-allocates): 설정할 GValue입니다.
 * @bool_value: @value에 설정할 값입니다.
 *
 * @value의 값을 해당 #gboolean의 값으로 설정합니다.
 */
void
crank_value_overwrite_boolean (	GValue*			value,
							   	const gboolean	bool_value	)
{
	crank_value_overwrite_init (value, G_TYPE_BOOLEAN);
	g_value_set_boolean (value, bool_value);
}

/**
 * crank_value_overwrite_int: (skip)
 * @value: (out caller-allocates): 설정할 GValue입니다.
 * @int_value: @value에 설정할 값입니다.
 *
 * @value의 값을 해당 #gint의 값으로 설정합니다.
 */
void
crank_value_overwrite_int (	GValue*			value,
						   	const gint		int_value	)
{
  	crank_value_overwrite_init (value, G_TYPE_INT);
  	g_value_set_int (value, int_value);
}

/**
 * crank_value_overwrite_string: (skip)
 * @value: (out caller-allocates): 설정할 GValue입니다.
 * @str_value: @value에 설정할 값입니다.
 *
 * @value의 값을 해당 문자열로 설정합니다.
 */
void
crank_value_overwrite_string (	GValue*			value,
							  	const gchar*	str_value	)
{
  	crank_value_overwrite_init (value, G_TYPE_STRING);
  	g_value_set_string (value, str_value);
}

/**
 * crank_value_overwrite_object: (skip)
 * @value: (out caller-allocates): 설정할 GValue입니다.
 * @obj_value: @value에 설정할 값입니다.
 *
 * @value의 값을 해당 #GObject로 설정합니다.
 */
void
crank_value_overwrite_object (	GValue*		value,
							  	GObject*	obj_value	)
{
	crank_value_overwrite_init (value, G_TYPE_OBJECT);
	g_value_set_object (value, obj_value);
}

/**
 * crank_value_overwrite_boxed: (skip)
 * @value: (out caller-allocates): 설정할 GValue입니다.
 * @value_type: @value에 설정할 타입입니다.
 * @boxed_value: @value에 설정할 값입니다.
 *
 * @value의 값을 해당 @boxed_value로 설정합니다. boxed type들은 자체적으로 타입
 * 정보를 가지지 않기 때문에 @value_type이 제공되어야 합니다.
 */
void
crank_value_overwrite_boxed (	GValue*		value,
							 	GType		value_type,
							 	gpointer	boxed_value	)
{
	crank_value_overwrite_init (value, value_type);
	g_value_set_boxed (value, boxed_value);
}



/**
 * crank_value_overwrite_pointer: (skip)
 * @value: (out caller-allocates): 설정할 GValue입니다.
 * @pointer_value: @value에 설정할 값입니다.
 *
 * @value의 값을 해당 @pointer_value로 설정합니다.
 */
void
crank_value_overwrite_pointer (	GValue*		value,
							   	gpointer	pointer_value	)
{
	crank_value_overwrite_init (value, G_TYPE_POINTER);
  	g_value_set_pointer (value, pointer_value);
}


/**
 * crank_value_array_overwrite: (skip)
 * @array: (out caller-allocates): 설정할 #GValue 배열입니다.
 * @nitem: @array에 덮어쓸 #GValue의 개수입니다.
 * @...: (type GValue): @array에 덮어쓸 #GValue입니다.
 *
 * 주어진 #GValue들을 배열위에 덮어씁니다.
 * 함수의 입력으로 들어온 #GValue들을 배열로 전환할 때 사용합니다.
 */
void
crank_value_array_overwrite (	GValue*		array,
								gint		nitem,
								...	)
{
	va_list		varargs;
	
	va_start (varargs, nitem);
	
	crank_value_array_overwrite_va (array, nitem, varargs);
	
	va_end (varargs);
}


/**
 * crank_value_array_overwrite_va: (skip)
 * @array: (out caller-allocates): 설정할 #GValue 배열입니다.
 * @nitem: @array에 덮어쓸 개수입니다.
 * @varargs: @array에 덮어쓸 #GValue입니다.
 *
 * 주어진 #GValue들을 배열위에 덮어씁니다.
 * 함수의 입력으로 들어온 #GValue들을 배열로 전환할 때 사용합니다.
 */
void
crank_value_array_overwrite_va (GValue*		array,
								gint		nitem,
								va_list		varargs	)
{
	guint	i;
	
	for (i = 0; i < nitem; i++)
		crank_value_overwrite (array + i, va_arg (varargs, GValue*));
}

/**
 * crank_value_array_overwrite_array: (skip)
 * @array: (out caller-allocates): 설정할 #GValue 배열입니다.
 * @nitem: @array에 덮어쓸 개수입니다.
 * @other: (array length=nitem): @array에 덮어 쓸 배열입니다.
 *
 * @other의 @nitem개의 내용을 @array에 덮어씁니다.
 */
void
crank_value_array_overwrite_array ( GValue*	array,
									gint	nitem,
									GValue*	other	)
{
	guint	i;
	
	for (i = 0; i < nitem; i++) crank_value_overwrite (array + i, other + i);
}

/**
 * crank_value_array_unset: (skip)
 * @array: (array length=narray): 해제할 #GValue 입니다.
 * @narray: @array의 길이입니다.
 *
 * 주어진 #GValue 배열을 해제합니다.
 */
void
crank_value_array_unset (	GValue*	array,
							guint	narray	)
{
	guint	i;
	
	for (i = 0; i < narray; i ++ )	g_value_unset (array + i);
}
