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

/**
 * SECTION: crankvecbool
 * @title: Boolean vector
 * @short_description: Boolean 값을 가지는 벡터입니다.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 부울 값을 가지는 벡터를 상징합니다. 원소들은 #gboolean 형의 값을 가집니다.
 *
 * 수학적으로는 참, 거짓은 벡터의 원소로는 구성되지 않습니다만, 여기서는 벡터의
 * 원소로서 구성합니다. #gboolean의 특성상 부동소수 벡터와 다른 점을 가집니다.
 *
 * * 덧셈 뺄셈 등이 정의 되는 부동 소수 벡터와는 달리, 논리 연산을 정의합니다.
 * * 전체 또는 일부가 %TRUE이면 %TRUE를 반환하는 getter 함수
 *
 * 현재 지원되는 동작은 다음과 같습니다.
 *
 * * 초기화: 인자, 배열 그리고 <structname>va_list</structname>에서 초기화
 * * 성분별 논리 연산: and, or, xor, not
 * * 특성: all, any
 *
 * 제공되는 매크로는 다음과 같습니다.
 *
 * * %TRUE, %FALSE: 모든 값이 %TRUE이거나 %FALSE인 초기화 목록
 * * I, J, K, L: 해당 성분 값이 %TRUE인 초기화 목록
 *
 * GLSL의 bvec와 대응됩니다.
 */

#include <stdarg.h>

#include <glib.h>
#include <glib-object.h>

#include "crankbasemacro.h"
#include "crankvecbool.h"

G_DEFINE_BOXED_TYPE (CrankVecBool2, crank_vec_bool2, crank_vec_bool2_copy, g_free)


/**
 * crank_vec_bool2_init:
 * @vec: (out): 초기화할 벡터입니다.
 * @x: 1번째 원소입니다.
 * @y: 2번째 원소입니다.
 *
 * 주어진 인자에서 초기화합니다.
 */
void
crank_vec_bool2_init	(	CrankVecBool2*	vec,
							gboolean		x,
							gboolean		y	)
{
	vec->x = x;
	vec->y = y;
}

/**
 * crank_vec_bool2_init_arr:
 * @vec: (out): 초기화할 벡터입니다.
 * @arr: (array fixed-size=2): 원소들의 배열입니다.
 *
 * 배열에서 원소들을 초기화 합니다.
 */
void
crank_vec_bool2_init_arr	(	CrankVecBool2*	vec,
								gboolean*		arr	)
{
	vec->x = arr[0];
	vec->y = arr[1];
}

/**
 * crank_vec_bool2_init_valist:
 * @vec: (out): 초기화할 벡터입니다.
 * @varargs: 가변인자 목록입니다.
 *
 * 가변인자 목록에서 #gboolean 2개를 가져와서 초기화합니다.
 */
void
crank_vec_bool2_init_valist	(	CrankVecBool2*	vec,
								va_list			varargs	)
{
	vec->x = va_arg (varargs, gboolean);
	vec->y = va_arg (varargs, gboolean);
}

/**
 * crank_vec_bool2_init_fill:
 * @vec: (out): 초기화할 벡터입니다.
 * @fill: 채울 값입니다.
 *
 * 모든 성분을 @fill으로 채웁니다.
 */
void
crank_vec_bool2_init_fill	(	CrankVecBool2*	vec,
								const gboolean	fill	)
{
	vec->x = fill;
	vec->y = fill;
}


/**
 * crank_vec_bool2_copy:
 * @vec: 복사할 벡터입니다.
 *
 * 벡터를 복사합니다. 사용이 끝나면, g_free()로 해제해야 합니다.
 *
 * Returns: (transfer full): 복사된 벡터입니다. g_free()로 해제합니다.
 */
CrankVecBool2*
crank_vec_bool2_copy	(	CrankVecBool2*	vec	)
{
	return (CrankVecBool2*) g_memdup (vec, sizeof (CrankVecBool2));
}


/**
 * crank_vec_bool2_get:
 * @vec: 원소를 얻을 벡터입니다.
 * @index: 원소의 인덱스입니다.
 * 
 * 주어진 벡터로부터 원소를 얻습니다.
 *
 * Returns: @vec의 @index번째 원소입니다.
 */
gboolean
crank_vec_bool2_get	(	CrankVecBool2*	vec,
						const guint		index	)
{
	return ((gboolean*)vec)[index];
}

/**
 * crank_vec_bool2_set:
 * @vec: 원소를 얻을 벡터입니다.
 * @index: 원소의 인덱스입니다.
 * @value: 설정할 원소입니다.
 * 
 * 주어진 벡터의 원소를 설정합니다.
 */
void
crank_vec_bool2_set	(	CrankVecBool2*	vec,
						const guint		index,
						const gboolean	value	)
{
	((gboolean*)vec)[index] = value;
}

/**
 * crank_vec_bool2_and:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a & @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 논리곱을 구합니다. 각 원소별로 논리곱을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool2_and	(	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	r->x = a->x && b->x;
	r->y = a->y && b->y;
}

/**
 * crank_vec_bool2_or:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a | @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 논리합을 구합니다. 각 원소별로 논리합을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool2_or	(	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	r->x = a->x || b->x;
	r->y = a->y || b->y;
}

/**
 * crank_vec_bool2_xor:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a ^ @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 배타적 논리합을 구합니다. 각 원소별로 배타적 논리합을 구한 결과가
 * 저장됩니다.
 */
void
crank_vec_bool2_xor	(	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	r->x = a->x != b->x;
	r->y = a->y != b->y;
}


/**
 * crank_vec_bool2_not:
 * @a: 벡터입니다.
 * @r: (out): ~@a의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 부정을 구합니다. 각 원소별로 부정을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool2_not	(	CrankVecBool2*	a,
						CrankVecBool2*	r	)
{
	r->x = ! a->x;
	r->y = ! a->y;
}

/**
 * crank_vec_bool2_andv:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): a & b를 저장할 벡터입니다.
 *
 * crank_vec_bool2_and()의 다른 이름입니다. and를 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool2_andv (	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	crank_vec_bool2_and (a, b, r);
}

/**
 * crank_vec_bool2_orv:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): a | b를 저장할 벡터입니다.
 *
 * crank_vec_bool2_or()의 다른 이름입니다. or을 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool2_orv (	CrankVecBool2*	a,
						CrankVecBool2*	b,
						CrankVecBool2*	r	)
{
	crank_vec_bool2_or (a, b, r);
}

/**
 * crank_vec_bool2_notv:
 * @a: 벡터입니다.
 * @r: (out): ! a 를 저장할 벡터입니다.
 *
 * crank_vec_bool2_not()의 다른 이름입니다. not을 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool2_notv (	CrankVecBool2*	a,
						CrankVecBool2*	r	)
{
	crank_vec_bool2_not (a, r);
}

/**
 * crank_vec_bool2_get_any:
 * @vec: 벡터입니다.
 * 
 * 벡터의 일부 원소가 %TRUE인지 아닌지 확인합니다.
 *
 * Returns: 일부 원소가 %TRUE이면 %TRUE입니다.
 */
gboolean
crank_vec_bool2_get_any	(	CrankVecBool2*	vec	)
{
	return (vec->x || vec->y);
}

/**
 * crank_vec_bool2_get_all:
 * @vec: 벡터입니다.
 * 
 * 벡터의 모든 원소가 %TRUE인지 아닌지 확인합니다.
 *
 * Returns: 모든 원소가 %TRUE이면 %TRUE입니다.
 */
gboolean
crank_vec_bool2_get_all	(	CrankVecBool2*	vec	)
{
	return (vec->x && vec->y);
}

/**
 * crank_vec_bool2_equal:
 * @a: (type CrankVecBool2): 비교할 벡터입니다.
 * @b: (type CrankVecBool2): 비교할 벡터입니다.
 *
 * 두 벡터를 비교하여 같은지 다른지 확인합니다.
 *
 * Returns: 두 벡터가 같으면 %TRUE입니다.
 */
gboolean
crank_vec_bool2_equal	(	gconstpointer a,
							gconstpointer b	)
{
	const CrankVecBool2* veca = (const CrankVecBool2*) a;
	const CrankVecBool2* vecb = (const CrankVecBool2*) b;

	return (veca->x == vecb->x) && (veca->y == vecb->y);
}


/**
 * crank_vec_bool2_hash:
 * @a: (type CrankVecBool2): 해쉬를 얻을 벡터입니다.
 *
 * 주어진 벡터의 해쉬를 얻습니다.
 *
 * Returns: 주어진 벡터의 해쉬값입니다.
 */
guint
crank_vec_bool2_hash	(	gconstpointer a	)
{
	const CrankVecBool2* vec = (const CrankVecBool2*) a;
	
	return g_direct_hash (GINT_TO_POINTER((vec->x) + (vec->y << 1)));
}

/**
 * crank_vec_bool2_to_string:
 * @vec: 벡터입니다.
 *
 * 주어진 벡터를 문자열로 만듭니다.
 *
 * Returns: 주어진 벡터의 문자열 형입니다.
 */
gchar*
crank_vec_bool2_to_string	(	CrankVecBool2*	vec	)
{
	return crank_vec_bool2_to_string_full (vec, "(", ", ", ")", "true", "false");
}

/**
 * crank_vec_bool2_to_string_full:
 * @vec: 벡터입니다.
 * @left: 왼쪽 막음입니다.
 * @in: 중간 구분자입니다.
 * @right: 오른 막음입니다.
 * @on_true: 참 값을 표현할 문자열입니다.
 * @on_false: 거짓 값을 포현할 문자열입니다.
 *
 * 주어진 벡터를 문자열로 만듭니다. 주어진 문자열들의 조합으로 구성합니다.
 *
 * Returns: 주어진 벡터의 문자열 형입니다.
 */
gchar*
crank_vec_bool2_to_string_full (CrankVecBool2*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	on_true,
								const gchar*	on_false	)
{
	return g_strdup_printf ("%s%s%s%s%s",
			left,
			vec->x ? on_true : on_false,
			in,
			vec->y ? on_true : on_false,
			right	);
}





G_DEFINE_BOXED_TYPE (CrankVecBool3, crank_vec_bool3, crank_vec_bool3_copy, g_free)

/**
 * crank_vec_bool3_init:
 * @vec: (out): 초기화할 벡터입니다.
 * @x: 1번째 원소입니다.
 * @y: 2번째 원소입니다.
 * @z: 3번째 원소입니다.
 *
 * 주어진 인자에서 초기화합니다.
 */
void
crank_vec_bool3_init	(	CrankVecBool3*	vec,
							gboolean		x,
							gboolean		y,
							gboolean		z	)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

/**
 * crank_vec_bool3_init_arr:
 * @vec: (out): 초기화할 벡터입니다.
 * @arr: (array fixed-size=3): 원소들의 배열입니다.
 *
 * 배열에서 원소들을 초기화 합니다.
 */
void
crank_vec_bool3_init_arr	(	CrankVecBool3*	vec,
								gboolean*		arr	)
{
	vec->x = arr[0];
	vec->y = arr[1];
	vec->z = arr[2];
}

/**
 * crank_vec_bool3_init_valist:
 * @vec: (out): 초기화할 벡터입니다.
 * @varargs: 가변인자 목록입니다.
 *
 * 가변인자 목록에서 #gboolean 3개를 가져와서 초기화합니다.
 */
void
crank_vec_bool3_init_valist	(	CrankVecBool3*	vec,
								va_list			varargs	)
{
	vec->x = va_arg (varargs, gboolean);
	vec->y = va_arg (varargs, gboolean);
	vec->z = va_arg (varargs, gboolean);
}


/**
 * crank_vec_bool3_init_fill:
 * @vec: (out): 초기화할 벡터입니다.
 * @fill: 채울 값입니다.
 *
 * 모든 성분을 @fill으로 채웁니다.
 */
void
crank_vec_bool3_init_fill	(	CrankVecBool3*	vec,
								const gboolean	fill	)
{
	vec->x = fill;
	vec->y = fill;
	vec->z = fill;
}


/**
 * crank_vec_bool3_copy:
 * @vec: 복사할 벡터입니다.
 *
 * 벡터를 복사합니다. 사용이 끝나면, g_free()로 해제해야 합니다.
 *
 * Returns: (transfer full): 복사된 벡터입니다. g_free()로 해제합니다.
 */
CrankVecBool3*
crank_vec_bool3_copy	(	CrankVecBool3*	vec	)
{
	return (CrankVecBool3*) g_memdup (vec, sizeof (CrankVecBool3));
}

/**
 * crank_vec_bool3_get:
 * @vec: 원소를 얻을 벡터입니다.
 * @index: 원소의 인덱스입니다.
 * 
 * 주어진 벡터로부터 원소를 얻습니다.
 *
 * Returns: @vec의 @index번째 원소입니다.
 */
gboolean
crank_vec_bool3_get	(	CrankVecBool3*	vec,
						const guint		index	)
{
	return ((gboolean*)vec)[index];
}

/**
 * crank_vec_bool3_set:
 * @vec: 원소를 얻을 벡터입니다.
 * @index: 원소의 인덱스입니다.
 * @value: 설정할 원소입니다.
 * 
 * 주어진 벡터의 원소를 설정합니다.
 */
void
crank_vec_bool3_set	(	CrankVecBool3*	vec,
						const guint		index,
						const gboolean	value	)
{
	((gboolean*)vec)[index] = value;
}

/**
 * crank_vec_bool3_and:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a & @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 논리곱을 구합니다. 각 원소별로 논리곱을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool3_and	(	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	r->x = a->x && b->x;
	r->y = a->y && b->y;
	r->z = a->z && b->z;
}

/**
 * crank_vec_bool3_or:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a | @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 논리합을 구합니다. 각 원소별로 논리합을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool3_or	(	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	r->x = a->x || b->x;
	r->y = a->y || b->y;
	r->z = a->z || b->z;
}

/**
 * crank_vec_bool3_xor:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a ^ @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 배타적 논리합을 구합니다. 각 원소별로 배타적 논리합을 구한 결과가
 * 저장됩니다.
 */
void
crank_vec_bool3_xor	(	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	r->x = a->x != b->x;
	r->y = a->y != b->y;
	r->z = a->z != b->z;
}

/**
 * crank_vec_bool3_not:
 * @a: 벡터입니다.
 * @r: (out): ~@a의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 부정을 구합니다. 각 원소별로 부정을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool3_not	(	CrankVecBool3*	a,
						CrankVecBool3*	r	)
{
	r->x = ! a->x;
	r->y = ! a->y;
}

/**
 * crank_vec_bool3_andv:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): a & b를 저장할 벡터입니다.
 *
 * crank_vec_bool3_and()의 다른 이름입니다. and를 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool3_andv (	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	crank_vec_bool3_and (a, b, r);
}

/**
 * crank_vec_bool3_orv:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): a | b를 저장할 벡터입니다.
 *
 * crank_vec_bool3_or()의 다른 이름입니다. or을 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool3_orv (	CrankVecBool3*	a,
						CrankVecBool3*	b,
						CrankVecBool3*	r	)
{
	crank_vec_bool3_or (a, b, r);
}

/**
 * crank_vec_bool3_notv:
 * @a: 벡터입니다.
 * @r: (out): ! a 를 저장할 벡터입니다.
 *
 * crank_vec_bool3_not()의 다른 이름입니다. not을 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool3_notv (	CrankVecBool3*	a,
						CrankVecBool3*	r	)
{
	crank_vec_bool3_not (a, r);
}


/**
 * crank_vec_bool3_get_any:
 * @vec: 벡터입니다.
 * 
 * 벡터의 일부 원소가 %TRUE인지 아닌지 확인합니다.
 *
 * Returns: 일부 원소가 %TRUE이면 %TRUE입니다.
 */
gboolean
crank_vec_bool3_get_any	(	CrankVecBool3*	vec	)
{
	return (vec->x || vec->y || vec->z);
}

/**
 * crank_vec_bool3_get_all:
 * @vec: 벡터입니다.
 * 
 * 벡터의 모든 원소가 %TRUE인지 아닌지 확인합니다.
 *
 * Returns: 모든 원소가 %TRUE이면 %TRUE입니다.
 */
gboolean
crank_vec_bool3_get_all	(	CrankVecBool3*	vec	)
{
	return (vec->x && vec->y && vec->z);
}

/**
 * crank_vec_bool3_equal:
 * @a: 비교할 벡터입니다.
 * @b: 비교할 벡터입니다.
 *
 * 두 벡터를 비교하여 같은지 다른지 확인합니다.
 *
 * Returns: 두 벡터가 같으면 %TRUE입니다.
 */
gboolean
crank_vec_bool3_equal	(	CrankVecBool3* a,
							CrankVecBool3* b	)
{
	return (a->x == b->x) && (a->y == b->y) && (a->z == b->z);
}

/**
 * crank_vec_bool3_hash:
 * @vec: 해쉬를 얻을 벡터입니다.
 *
 * 주어진 벡터의 해쉬를 얻습니다.
 *
 * Returns: 주어진 벡터의 해쉬값입니다.
 */
guint
crank_vec_bool3_hash	(	CrankVecBool3* vec	)
{
	return g_direct_hash (
			GINT_TO_POINTER(	(vec->x) +
								(vec->y << 1) +
								(vec->z << 2)	));
}

/**
 * crank_vec_bool3_to_string:
 * @vec: 벡터입니다.
 *
 * 주어진 벡터를 문자열로 만듭니다.
 *
 * Returns: 주어진 벡터의 문자열 형입니다.
 */
gchar*
crank_vec_bool3_to_string	(	CrankVecBool3*	vec	)
{
	return crank_vec_bool3_to_string_full (vec, "(", ", ", ")", "true", "false");
}

/**
 * crank_vec_bool3_to_string_full:
 * @vec: 벡터입니다.
 * @left: 왼쪽 막음입니다.
 * @in: 중간 구분자입니다.
 * @right: 오른 막음입니다.
 * @on_true: 참 값을 표현할 문자열입니다.
 * @on_false: 거짓 값을 포현할 문자열입니다.
 *
 * 주어진 벡터를 문자열로 만듭니다. 주어진 문자열들의 조합으로 구성합니다.
 *
 * Returns: 주어진 벡터의 문자열 형입니다.
 */
gchar*
crank_vec_bool3_to_string_full (CrankVecBool3*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	on_true,
								const gchar*	on_false	)
{
	return g_strdup_printf ("%s%s%s%s%s%s%s",
			left,
			vec->x ? on_true : on_false,
			in,
			vec->y ? on_true : on_false,
			in,
			vec->z ? on_true : on_false,
			right	);
}






G_DEFINE_BOXED_TYPE (CrankVecBool4, crank_vec_bool4, crank_vec_bool4_copy, g_free)

/**
 * crank_vec_bool4_init:
 * @vec: (out): 초기화할 벡터입니다.
 * @x: 1번째 원소입니다.
 * @y: 2번째 원소입니다.
 * @z: 3번째 원소입니다.
 * @w: 4번째 원소입니다.
 *
 * 주어진 인자에서 초기화합니다.
 */
void
crank_vec_bool4_init	(	CrankVecBool4*	vec,
							gboolean		x,
							gboolean		y,
							gboolean		z,
							gboolean		w	)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}


/**
 * crank_vec_bool4_init_arr:
 * @vec: (out): 초기화할 벡터입니다.
 * @arr: (array fixed-size=4): 원소들의 배열입니다.
 *
 * 배열에서 원소들을 초기화 합니다.
 */
void
crank_vec_bool4_init_arr	(	CrankVecBool4*	vec,
								gboolean*		arr	)
{
	vec->x = arr[0];
	vec->y = arr[1];
	vec->z = arr[2];
	vec->w = arr[3];
}

/**
 * crank_vec_bool4_init_valist:
 * @vec: (out): 초기화할 벡터입니다.
 * @varargs: 가변인자 목록입니다.
 *
 * 가변인자 목록에서 #gboolean 4개를 가져와서 초기화합니다.
 */
void
crank_vec_bool4_init_valist	(	CrankVecBool4*	vec,
								va_list			varargs	)
{
	vec->x = va_arg (varargs, gboolean);
	vec->y = va_arg (varargs, gboolean);
	vec->z = va_arg (varargs, gboolean);
	vec->w = va_arg (varargs, gboolean);
}


/**
 * crank_vec_bool4_init_fill:
 * @vec: (out): 초기화할 벡터입니다.
 * @fill: 채울 값입니다.
 *
 * 모든 성분을 @fill으로 채웁니다.
 */
void
crank_vec_bool4_init_fill	(	CrankVecBool4*	vec,
								const gboolean	fill	)
{
	vec->x = fill;
	vec->y = fill;
	vec->z = fill;
	vec->w = fill;
}

/**
 * crank_vec_bool4_copy:
 * @vec: 복사할 벡터입니다.
 *
 * 벡터를 복사합니다. 사용이 끝나면, g_free()로 해제해야 합니다.
 *
 * Returns: (transfer full): 복사된 벡터입니다. g_free()로 해제합니다.
 */
CrankVecBool4*
crank_vec_bool4_copy	(	CrankVecBool4*	vec	)
{
	return (CrankVecBool4*) g_memdup (vec, sizeof (CrankVecBool4));
}

/**
 * crank_vec_bool4_get:
 * @vec: 원소를 얻을 벡터입니다.
 * @index: 원소의 인덱스입니다.
 * 
 * 주어진 벡터로부터 원소를 얻습니다.
 *
 * Returns: @vec의 @index번째 원소입니다.
 */
gboolean
crank_vec_bool4_get	(	CrankVecBool4*	vec,
						const guint		index	)
{
	return ((gboolean*)vec)[index];
}

/**
 * crank_vec_bool4_set:
 * @vec: 원소를 얻을 벡터입니다.
 * @index: 원소의 인덱스입니다.
 * @value: 설정할 원소입니다.
 * 
 * 주어진 벡터의 원소를 설정합니다.
 */
void
crank_vec_bool4_set	(	CrankVecBool4*	vec,
						const guint		index,
						const gboolean	value	)
{
	((gboolean*)vec)[index] = value;
}

/**
 * crank_vec_bool4_and:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a & @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 논리곱을 구합니다. 각 원소별로 논리곱을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool4_and	(	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	r->x = a->x && b->x;
	r->y = a->y && b->y;
	r->z = a->z && b->z;
	r->w = a->w && b->w;
}

/**
 * crank_vec_bool4_or:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a | @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 논리합을 구합니다. 각 원소별로 논리합을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool4_or	(	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	r->x = a->x || b->x;
	r->y = a->y || b->y;
	r->z = a->z || b->z;
	r->w = a->w || b->w;
}

/**
 * crank_vec_bool4_xor:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a ^ @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 배타적 논리합을 구합니다. 각 원소별로 배타적 논리합을 구한 결과가
 * 저장됩니다.
 */
void
crank_vec_bool4_xor	(	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	r->x = a->x != b->x;
	r->y = a->y != b->y;
	r->z = a->z != b->z;
	r->w = a->w != b->w;
}

/**
 * crank_vec_bool4_not:
 * @a: 벡터입니다.
 * @r: (out): ~@a의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 부정을 구합니다. 각 원소별로 부정을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool4_not	(	CrankVecBool4*	a,
						CrankVecBool4*	r	)
{
	r->x = ! a->x;
	r->y = ! a->y;
	r->z = ! a->z;
	r->w = ! a->w;
}
/**
 * crank_vec_bool4_andv:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): a & b를 저장할 벡터입니다.
 *
 * crank_vec_bool4_and()의 다른 이름입니다. and를 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool4_andv (	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	crank_vec_bool4_and (a, b, r);
}

/**
 * crank_vec_bool4_orv:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): a | b를 저장할 벡터입니다.
 *
 * crank_vec_bool4_or()의 다른 이름입니다. or을 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool4_orv (	CrankVecBool4*	a,
						CrankVecBool4*	b,
						CrankVecBool4*	r	)
{
	crank_vec_bool4_or (a, b, r);
}

/**
 * crank_vec_bool4_notv:
 * @a: 벡터입니다.
 * @r: (out): ! a 를 저장할 벡터입니다.
 *
 * crank_vec_bool4_not()의 다른 이름입니다. not을 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool4_notv (	CrankVecBool4*	a,
						CrankVecBool4*	r	)
{
	crank_vec_bool4_not (a, r);
}


/**
 * crank_vec_bool4_get_any:
 * @vec: 벡터입니다.
 * 
 * 벡터의 일부 원소가 %TRUE인지 아닌지 확인합니다.
 *
 * Returns: 일부 원소가 %TRUE이면 %TRUE입니다.
 */
gboolean
crank_vec_bool4_get_any	(	CrankVecBool4*	vec	)
{
	return (vec->x || vec->y || vec->z || vec->w);
}


/**
 * crank_vec_bool4_get_all:
 * @vec: 벡터입니다.
 * 
 * 벡터의 모든 원소가 %TRUE인지 아닌지 확인합니다.
 *
 * Returns: 모든 원소가 %TRUE이면 %TRUE입니다.
 */
gboolean
crank_vec_bool4_get_all	(	CrankVecBool4*	vec	)
{
	return (vec->x && vec->y && vec->z && vec->w);
}

/**
 * crank_vec_bool4_equal:
 * @a: 비교할 벡터입니다.
 * @b: 비교할 벡터입니다.
 *
 * 두 벡터를 비교하여 같은지 다른지 확인합니다.
 *
 * Returns: 두 벡터가 같으면 %TRUE입니다.
 */
gboolean
crank_vec_bool4_equal	(	CrankVecBool4* a,
							CrankVecBool4* b	)
{
	return (a->x == b->x) && (a->y == b->y) && (a->z == b->z) && (a->w == b->w);
}

/**
 * crank_vec_bool4_hash:
 * @vec: 해쉬를 얻을 벡터입니다.
 *
 * 주어진 벡터의 해쉬를 얻습니다.
 *
 * Returns: 주어진 벡터의 해쉬값입니다.
 */
guint
crank_vec_bool4_hash	(	CrankVecBool4* vec	)
{
	return g_direct_hash (
			GINT_TO_POINTER(	(vec->x) +
								(vec->y << 1) +
								(vec->z << 2) +
								(vec->w << 3)	));
}

/**
 * crank_vec_bool4_to_string:
 * @vec: 벡터입니다.
 *
 * 주어진 벡터를 문자열로 만듭니다.
 *
 * Returns: 주어진 벡터의 문자열 형입니다.
 */
gchar*
crank_vec_bool4_to_string	(	CrankVecBool4*	vec	)
{
	return crank_vec_bool4_to_string_full (vec, "(", ", ", ")", "true", "false");
}


/**
 * crank_vec_bool4_to_string_full:
 * @vec: 벡터입니다.
 * @left: 왼쪽 막음입니다.
 * @in: 중간 구분자입니다.
 * @right: 오른 막음입니다.
 * @on_true: 참 값을 표현할 문자열입니다.
 * @on_false: 거짓 값을 포현할 문자열입니다.
 *
 * 주어진 벡터를 문자열로 만듭니다. 주어진 문자열들의 조합으로 구성합니다.
 *
 * Returns: 주어진 벡터의 문자열 형입니다.
 */
gchar*
crank_vec_bool4_to_string_full (CrankVecBool4*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	on_true,
								const gchar*	on_false	)
{
	return g_strdup_printf ("%s%s%s%s%s%s%s%s%s",
			left,
			vec->x ? on_true : on_false,
			in,
			vec->y ? on_true : on_false,
			in,
			vec->z ? on_true : on_false,
			in,
			vec->w ? on_true : on_false,
			right	);
}





G_DEFINE_BOXED_TYPE (CrankVecBoolN, crank_vec_bool_n,
		crank_vec_bool_n_copy,
		crank_vec_bool_n_free)

/**
 * crank_vec_bool_n_init:
 * @vec: (out): 초기화할 벡터입니다.
 * @n: 초기화할 벡터의 길이입니다.
 * @...: 벡터의 성분들입니다.
 *
 * 주어진 가변 인자에서 벡터를 초기화 합니다. 사용이 끝나면
 * crank_vec_bool_n_fini()으로 해제합니다.
 */
void
crank_vec_bool_n_init	(	CrankVecBoolN*	vec,
							const guint		n,
							...	)
{
	va_list varargs;
	
	va_start (varargs, n);
	
	crank_vec_bool_n_init_valist (vec, n, varargs);
	
	va_end (varargs);
}

/**
 * crank_vec_bool_n_init_arr:
 * @vec: (out): 초기화할 벡터입니다.
 * @n: 벡터의 길이입니다.
 * @arr: (array length=n): 원소들의 배열입니다.
 *
 * 배열에서 원소들을 초기화 합니다. 사용이 끝나면
 * crank_vec_bool_n_fini()으로 해제합니다.
 */
void
crank_vec_bool_n_init_arr	(	CrankVecBoolN*	vec,
								const guint		n,
								gboolean*		arr	)
{
	if (vec->data != NULL) g_free (vec->data);
	vec->data = CRANK_ARRAY_DUP(arr, gboolean, n);
	vec->n = n;
}

/**
 * crank_vec_bool_n_init_valist:
 * @vec: (out): 초기화할 벡터입니다.
 * @n: 벡터의 길이입니다.
 * @varargs: 가변인자 목록입니다.
 *
 * 가변인자 목록에서 #gboolean 2개를 가져와서 초기화합니다. 사용이 끝나면
 * crank_vec_bool_n_fini()으로 해제합니다.
 */
void
crank_vec_bool_n_init_valist	(	CrankVecBoolN*	vec,
									const guint		n,
									va_list			varargs	)
{
	guint	i;
	
	if (vec->data != NULL) g_free (vec->data);
	vec->n = n;
	vec->data = g_new (gboolean, n);
	
	for (i = 0; i < n; i++) vec->data[i] = va_arg (varargs, gboolean);
	
}

/**
 * crank_vec_bool_n_init_fill:
 * @vec: (out): 초기화할 벡터입니다.
 * @n: 벡터의 크기입니다.
 * @fill: 채울 값입니다.
 *
 * 모든 성분을 @fill으로 채웁니다.
 */
void
crank_vec_bool_n_init_fill	(	CrankVecBoolN*	vec,
								const guint		n,
								const gboolean	fill	)
{
	guint	i;
	
	if (vec->data != NULL) g_free (vec->data);
	vec->n = n;
	vec->data = g_new (gboolean, n);
	
	for (i = 0; i < n; i++) vec->data[i] = fill;
	
}


/**
 * crank_vec_bool_n_fini:
 * @vec: 리셋할 벡터입니다.
 *
 * 자원을 해제합니다.
 */
void
crank_vec_bool_n_fini	(	CrankVecBoolN*	vec	)
{
	g_free (vec->data);
	vec->n = 0;
}

/**
 * crank_vec_bool_n_free:
 * @vec: 해제할 벡터입니다.
 *
 * 연관된 자원을 해제하고, 벡터도 메모리에서 해제합니다.
 */
void
crank_vec_bool_n_free	(	CrankVecBoolN*	vec	)
{
	crank_vec_bool_n_fini (vec);
	g_free (vec);
}


/**
 * crank_vec_bool_n_copy:
 * @vec: 복사할 벡터입니다.
 *
 * 벡터를 복사합니다. 사용이 끝나면, crank_vec_bool_n_free()로 해제해야 합니다.
 *
 * Returns: (transfer full): 복사된 벡터입니다.
 */
CrankVecBoolN*
crank_vec_bool_n_copy	(	CrankVecBoolN*	vec	)
{
	CrankVecBoolN* result = g_new0 (CrankVecBoolN, 1);
	
	crank_vec_bool_n_init_arr (result, vec->n, vec->data);
	return result;
}

/**
 * crank_vec_bool_n_get_size:
 * @vec: 크기를 얻을 벡터입니다.
 *
 * 주어진 벡터의 크기를 얻습니다. @vec->n으로도 얻을 수 있습니다.
 *
 * Returns: 벡터의 크기입니다.
 */
guint
crank_vec_bool_n_get_size	(	CrankVecBoolN*	vec	)
{
	return vec->n;
}


/**
 * crank_vec_bool_n_get:
 * @vec: 원소를 얻을 벡터입니다.
 * @index: 원소의 인덱스입니다.
 * 
 * 주어진 벡터로부터 원소를 얻습니다.
 *
 * Returns: @vec의 @index번째 원소입니다.
 */
gboolean
crank_vec_bool_n_get	(	CrankVecBoolN*	vec,
							const guint		index	)
{
	return vec->data[index];
}

/**
 * crank_vec_bool_n_set:
 * @vec: 원소를 얻을 벡터입니다.
 * @index: 원소의 인덱스입니다.
 * @value: 설정할 원소입니다.
 * 
 * 주어진 벡터의 원소를 설정합니다.
 */
void
crank_vec_bool_n_set	(	CrankVecBoolN*	vec,
							const guint		index,
							const gboolean	value	)
{
	vec->data[index] = value;
}

/**
 * crank_vec_bool_n_and:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a & @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 논리곱을 구합니다. 만일 크기가 맞지 않을 경우, 크기가 작은 벡터의 길이
 * 만을 계산한 뒤 반환합니다.
 */
void
crank_vec_bool_n_and	(	CrankVecBoolN*	a,
							CrankVecBoolN*	b,
							CrankVecBoolN*	r	)
{
	guint i;
	
	if (r->data != NULL) g_free (r->data);
	
	r->n = MIN(a->n, b->n);
	r->data = g_new (gboolean, r->n);
	
	for (i = 0; i < r->n; i++)
		r->data[i] = (a->data[i]) && (b->data[i]);
}


/**
 * crank_vec_bool_n_or:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a | @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 논리합을 구합니다. 만일 크기가 맞지 않을 경우, 크기가 긴 벡터의 길이
 * 에 맞추어 계산한 뒤 반환합니다.
 */
void
crank_vec_bool_n_or	(	CrankVecBoolN*	a,
						CrankVecBoolN*	b,
						CrankVecBoolN*	r	)
{
	CrankVecBoolN* l;
	CrankVecBoolN* s;
	
	guint i;
	
	if (r->data != NULL) g_free (r->data);
	
	if (a->n < b->n) {
		l = b;
		s = a;
	}
	else {
		l = a;
		s = b;
	}
	
	r->n =		l->n;
	r->data = 	g_new (gboolean, r->n);
	
	for (i = 0; i < s->n; i++)
		r->data[i] = a->data[i] || b->data[i] ;
	
	memcpy (	(r->data + s->n),
				(l->data + s->n),
				sizeof(gboolean) *(l->n - s->n)	);
}
/**
 * crank_vec_bool_n_xor:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): @a ^ @b의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 배타적 논리합을 구합니다. 각 원소별로 배타적 논리합을 구한 결과가
 * 저장됩니다.
 */
void
crank_vec_bool_n_xor	(	CrankVecBoolN*	a,
							CrankVecBoolN*	b,
							CrankVecBoolN*	r	)
{
	CrankVecBoolN* l;
	CrankVecBoolN* s;
	
	guint i;
	
	if (r->data != NULL) g_free (r->data);
	
	if (a->n < b->n) {
		l = b;
		s = a;
	}
	else {
		l = a;
		s = b;
	}
	
	r->n =		l->n;
	r->data = 	g_new (gboolean, r->n);
	
	for (i = 0; i < s->n; i++) r->data[i] = a->data[i] != b->data[i] ;
	
	memcpy (	(r->data + s->n),
				(l->data + s->n),
				sizeof(gboolean) *(l->n - s->n)	);
}


/**
 * crank_vec_bool_n_not:
 * @a: 벡터입니다.
 * @r: (out): ~@a의 결과를 저장할 벡터입니다.
 * 
 * 벡터의 부정을 구합니다. 각 원소별로 부정을 구한 결과가 저장됩니다.
 */
void
crank_vec_bool_n_not	(	CrankVecBoolN*	a,
							CrankVecBoolN*	r	)
{
	guint i;
	
	if (r->data != NULL) g_free (r->data);

	r->n = a->n;
	r->data = g_new (gboolean, r->n);
	
	for (i = 0; i < r->n; i++) r->data[i] = !(a->data[i]);
}

/**
 * crank_vec_bool_n_andv:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): a & b를 저장할 벡터입니다.
 *
 * crank_vec_bool_n_and()의 다른 이름입니다. and를 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool_n_andv (	CrankVecBoolN*	a,
						CrankVecBoolN*	b,
						CrankVecBoolN*	r	)
{
	crank_vec_bool_n_and (a, b, r);
}

/**
 * crank_vec_bool_n_orv:
 * @a: 벡터입니다.
 * @b: 벡터입니다.
 * @r: (out): a | b를 저장할 벡터입니다.
 *
 * crank_vec_bool_n_or()의 다른 이름입니다. or을 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool_n_orv (	CrankVecBoolN*	a,
						CrankVecBoolN*	b,
						CrankVecBoolN*	r	)
{
	crank_vec_bool_n_or (a, b, r);
}

/**
 * crank_vec_bool_n_notv:
 * @a: 벡터입니다.
 * @r: (out): ! a 를 저장할 벡터입니다.
 *
 * crank_vec_bool_n_not()의 다른 이름입니다. not을 연산자로 사용하는 일부 언어에
 * 사용하기 위해 만들어졌습니다.
 */
void
crank_vec_bool_n_notv (	CrankVecBoolN*	a,
						CrankVecBoolN*	r	)
{
	crank_vec_bool_n_not (a, r);
}

/**
 * crank_vec_bool_n_get_any:
 * @vec: 벡터입니다.
 * 
 * 벡터의 일부 원소가 %TRUE인지 아닌지 확인합니다.
 *
 * Returns: 일부 원소가 %TRUE이면 %TRUE입니다.
 */
gboolean
crank_vec_bool_n_get_any	(	CrankVecBoolN*	vec	)
{
	CRANK_FOREACH_ARRAY_BEGIN (vec->data, gboolean, e, vec->n)
		if (e) return TRUE;
	CRANK_FOREACH_ARRAY_END
	
	return FALSE;
}

/**
 * crank_vec_bool_n_get_all:
 * @vec: 벡터입니다.
 * 
 * 벡터의 모든 원소가 %TRUE인지 아닌지 확인합니다.
 *
 * Returns: 모든 원소가 %TRUE이면 %TRUE입니다.
 */
gboolean
crank_vec_bool_n_get_all	(	CrankVecBoolN*	vec	)
{
	CRANK_FOREACH_ARRAY_BEGIN (vec->data, gboolean, e, vec->n)
		if (! e) return FALSE;
	CRANK_FOREACH_ARRAY_END
	
	return TRUE;
}

/**
 * crank_vec_bool_n_equal:
 * @a: 비교할 벡터입니다.
 * @b: 비교할 벡터입니다.
 *
 * 두 벡터를 비교하여 같은지 다른지 확인합니다.
 *
 * Returns: 두 벡터가 같으면 %TRUE입니다.
 */
gboolean
crank_vec_bool_n_equal	(	CrankVecBoolN* a,
							CrankVecBoolN* b	)
{
	guint i;
	if (a->n != b->n) return FALSE;
	
	for (i = 0; i < a->n; i++)
		if (a->data[i] != b->data[i]) return FALSE;
	
	return TRUE;
}


/**
 * crank_vec_bool_n_hash:
 * @vec: 해쉬를 얻을 벡터입니다.
 *
 * 주어진 벡터의 해쉬를 얻습니다.
 *
 * Returns: 주어진 벡터의 해쉬값입니다.
 */
guint
crank_vec_bool_n_hash	(	CrankVecBoolN* vec	)
{
	guint	i;
	guint	value = 0;
	
	for (i = 0; i < vec->n; i++)
		value = value ^ ((vec->data[i] ? 1 : 0) << (i && 31));

	return g_direct_hash (GINT_TO_POINTER (value));
}

/**
 * crank_vec_bool_n_to_string:
 * @vec: 벡터입니다.
 *
 * 주어진 벡터를 문자열로 만듭니다.
 *
 * Returns: 주어진 벡터의 문자열 형입니다.
 */
gchar*
crank_vec_bool_n_to_string	(	CrankVecBoolN*	vec	)
{
	return crank_vec_bool_n_to_string_full (vec, "(", ", ", ")", "true", "false");
}

/**
 * crank_vec_bool_n_to_string_full:
 * @vec: 벡터입니다.
 * @left: 왼쪽 막음입니다.
 * @in: 중간 구분자입니다.
 * @right: 오른 막음입니다.
 * @on_true: 참 값을 표현할 문자열입니다.
 * @on_false: 거짓 값을 포현할 문자열입니다.
 *
 * 주어진 벡터를 문자열로 만듭니다. 주어진 문자열들의 조합으로 구성합니다.
 *
 * Returns: 주어진 벡터의 문자열 형입니다.
 */
gchar*
crank_vec_bool_n_to_string_full (CrankVecBoolN*	vec,
								const gchar*	left,
								const gchar*	in,
								const gchar*	right,
								const gchar*	on_true,
								const gchar*	on_false	)
{
	GString*	str;
	gchar*		result;
	
	str = g_string_new (left);
	
	if (0 < vec->n) {
		g_string_append (str, vec->data[0] ? on_true : on_false );
		
		CRANK_FOREACH_ARRAY_BEGIN (vec->data, gboolean, e, vec->n)
			g_string_append (str, in );
			g_string_append (str, e ? on_true : on_false );
		CRANK_FOREACH_ARRAY_END
	}
	
	g_string_append (str, right);
	
	result = str->str;
	g_string_free (str, FALSE);
	
	return result;
}

