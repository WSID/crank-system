#ifndef CRANKFUNCTION_H
#define CRANKFUNCTION_H

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
#error crankbasemacro.h cannot be included directly.
#endif

/**
 * SECTION:crankfunction
 * @short_description: Crank System 함수 타입 및 매크로입니다.
 * @title: Crank System 함수 타입 및 매크로
 * @stability: Unstable
 * @include: crankbase.h
 *
 * Crank System은 다양한 함수 형을 취급하기 쉽도록 여러 정의와 함수 그리고
 * 매크로를 포함하고 있습니다.
 */

G_BEGIN_DECLS

/**
 * CrankFuncPointer: (skip)
 * @userdata: (closure): 더미입니다.
 *
 * 이는 실질적인 함수 형으로 사용되기 보다는 임의의 함수를 받아들일수 있는
 * 인자를 표시하는 목적으로 사용됩니다.
 */
typedef void		(*CrankFuncPointer) (	gpointer	userdata	);

/**
 * CrankFunc0: (skip)
 * @userdata: (closure): 함수에 추가적으로 전달할 데이터입니다.
 *
 * 인자를 받지 않는 함수를 상징합니다.
 *
 * Returns: 반환 값입니다.
 */
typedef gpointer	(*CrankFunc0)		(	gpointer	userdata	);

/**
 * CrankFunc1: (skip)
 * @arg1: 함수에 전달할 인자입니다.
 * @userdata: (closure): 함수에 추가적으로 전달할 데이터입니다.
 *
 * 한 개의 인자를 받는 함수를 상징합니다.
 *
 * Returns: 반환 값입니다.
 */
typedef gpointer	(*CrankFunc1)		(	gpointer	arg1,
											gpointer	userdata	);

/**
 * CrankFunc2: (skip)
 * @arg1: 함수에 전달할 인자입니다.
 * @arg2: 함수에 전달할 인자입니다.
 * @userdata: (closure): 함수에 추가적으로 전달할 데이터입니다.
 *
 * 두 개의 인자를 받는 함수를 상징합니다.
 *
 * Returns: 반환 값입니다.
 */
typedef gpointer	(*CrankFunc2)		(	gpointer	arg1,
											gpointer	arg2,
											gpointer	userdata	);

/**
 * CrankFunc3: (skip)
 * @arg1: 함수에 전달할 인자입니다.
 * @arg2: 함수에 전달할 인자입니다.
 * @arg3: 함수에 전달할 인자입니다.
 * @userdata: (closure): 함수에 추가적으로 전달할 데이터입니다.
 *
 * 세 개의 인자를 받는 함수를 상징합니다.
 *
 * Returns: 반환 값입니다.
 */
typedef gpointer	(*CrankFunc3)		(	gpointer	arg1,
											gpointer	arg2,
											gpointer	arg3,
											gpointer	userdata	);

/**
 * CrankFunc4: (skip)
 * @arg1: 함수에 전달할 인자입니다.
 * @arg2: 함수에 전달할 인자입니다.
 * @arg3: 함수에 전달할 인자입니다.
 * @arg4: 함수에 전달할 인자입니다.
 * @userdata: (closure): 함수에 추가적으로 전달할 데이터입니다.
 *
 * 네 개의 인자를 받는 함수를 상징합니다.
 *
 * Returns: 반환 값입니다.
 */
typedef gpointer	(*CrankFunc4)		(	gpointer	arg1,
											gpointer	arg2,
											gpointer	arg3,
											gpointer	arg4,
											gpointer	userdata	);

/**
 * CrankFunc5: (skip)
 * @arg1: 함수에 전달할 인자입니다.
 * @arg2: 함수에 전달할 인자입니다.
 * @arg3: 함수에 전달할 인자입니다.
 * @arg4: 함수에 전달할 인자입니다.
 * @arg5: 함수에 전달할 인자입니다.
 * @userdata: (closure): 함수에 추가적으로 전달할 데이터입니다.
 *
 * 다섯 개의 인자를 받는 함수를 상징합니다.
 *
 * Returns: 반환 값입니다.
 */
typedef gpointer	(*CrankFunc5)		(	gpointer	arg1,
											gpointer	arg2,
											gpointer	arg3,
											gpointer	arg4,
											gpointer	arg5,
											gpointer	userdata	);
										
/**
 * CrankFunc6: (skip)
 * @arg1: 함수에 전달할 인자입니다.
 * @arg2: 함수에 전달할 인자입니다.
 * @arg3: 함수에 전달할 인자입니다.
 * @arg4: 함수에 전달할 인자입니다.
 * @arg5: 함수에 전달할 인자입니다.
 * @arg6: 함수에 전달할 인자입니다.
 * @userdata: (closure): 함수에 추가적으로 전달할 데이터입니다.
 *
 * 여섯 개의 인자를 받는 함수를 상징합니다.
 *
 * Returns: 반환 값입니다.
 */	
typedef gpointer	(*CrankFunc6)		(	gpointer	arg1,
											gpointer	arg2,
											gpointer	arg3,
											gpointer	arg4,
											gpointer	arg5,
											gpointer	arg6,
											gpointer	userdata	);
										
/**
 * CrankFunc7: (skip)
 * @arg1: 함수에 전달할 인자입니다.
 * @arg2: 함수에 전달할 인자입니다.
 * @arg3: 함수에 전달할 인자입니다.
 * @arg4: 함수에 전달할 인자입니다.
 * @arg5: 함수에 전달할 인자입니다.
 * @arg6: 함수에 전달할 인자입니다.
 * @arg7: 함수에 전달할 인자입니다.
 * @userdata: (closure): 함수에 추가적으로 전달할 데이터입니다.
 *
 * 일곱 개의 인자를 받는 함수를 상징합니다.
 *
 * Returns: 반환 값입니다.
 */	
typedef gpointer	(*CrankFunc7)		(	gpointer	arg1,
											gpointer	arg2,
											gpointer	arg3,
											gpointer	arg4,
											gpointer	arg5,
											gpointer	arg6,
											gpointer	arg7,
											gpointer	userdata	);

/**
 * CRANK_FUNC_POINTER_VALA_GET_POINTER: (skip)
 * @fp:	함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 *
 * 함수 포인터를 void* 형으로 얻습니다.
 * Vala에서 사용하기 위해 정의 되었습니다.
 *
 * Returns: 함수 포인터를 void*형으로 얻습니다.
 */
#define CRANK_FUNC_POINTER_VALA_GET_POINTER(fp, userdata)	(fp)

/**
 * CRANK_FUNC_POINTER_VALA_GET_USERDATA: (skip)
 * @fp:	함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 *
 * 함수에 추가적으로 전달할 데이터를 void* 형으로 얻습니다.
 * Vala에서 사용하기 위해 정의 되었습니다.
 *
 * Returns: 함수에 추가적으로 전달할 데이터를 void*형으로 얻습니다.
 */
#define CRANK_FUNC_POINTER_VALA_GET_USERDATA(fp, userdata)	(userdata)


/**
 * CRANK_FUNC_VALA_JOIN_SPLIT: (skip)
 * @fp: 함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 * @userdata_out: (out): 함수 추가 데이터를 얻기 위한 포인터입니다.
 *
 * 이 매크로는 Vala에서 delegate 형에서 @userdata를 분리하거나 합치는 역할을
 * 합니다.
 *
 * Returns: @fp입니다.
 */
#define CRANK_FUNC_VALA_JOIN_SPLIT(fp, userdata, userdata_out)	\
		(*(userdata_out)=(userdata), (fp))

/**
 * CRANK_FUNC_VALA_JOIN_SPLIT_OWNED: (skip)
 * @fp: 함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 * @destroy: @userdata를 해제할 함수입니다.
 * @userdata_out: (out): 함수 추가 데이터를 얻기 위한 포인터입니다.
 * @destroy_out: (out): 함수 추가 데이터를 해제하기 위한 함수 포인터에 대한 포인터입니다.
 *
 * 이 매크로는 Vala에서 delegate 형에서 @userdata를 분리하거나 합치는 역할을
 * 합니다.
 *
 * Returns: @fp입니다.
 */
#define CRANK_FUNC_VALA_JOIN_SPLIT_OWNED(fp, userdata, destroy, userdata_out, destroy_out)	\
		(*(userdata_out)=(userdata), *(destroy_out)=(destroy), (fp))

/**
 * CRANK_VALA_GENERIC_UNOWNED: (skip)
 * @t: #GType입니다.
 * @copy: 복사 함수입니다.
 * @destroy: 해제 함수입니다.
 *
 * 이 매크로는 복사 함수가 비어있는지 확인하여, 주어진 타입이 비소유 타입인지
 * 판별합니다.
 */
#define CRANK_VALA_GENERIC_UNOWNED(t, copy, destroy) (copy == NULL)

G_END_DECLS

#endif //CRANKFUNCTION_H
