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
 * 이 함수들과 매크로들은 Vala에서 C 중심적인 함수들을 사용할 수 있도록 보조하는
 * 역할을 합니다.
 */

G_BEGIN_DECLS

/**
 * CrankCallback: (skip)
 * @userdata: (closure): 더미입니다.
 *
 * 이는 실질적인 함수 형으로 사용되기 보다는 임의의 함수를 받아들일수 있는
 * 인자를 표시하는 목적으로 사용됩니다.
 */
typedef void		(*CrankCallback) (	gpointer	userdata	);

/**
 * CRANK_VALA_FUNC_GET_POINTER: (skip)
 * @fp:	함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 *
 * 함수 포인터를 GCallback으로 얻습니다.
 * Vala에서 사용하기 위해 정의 되었습니다.
 *
 * Returns: (type GCallback): 함수 포인터를 GCallback으로 얻습니다.
 */
#define CRANK_VALA_FUNC_GET_POINTER(fp, userdata)	(fp)

/**
 * CRANK_VALA_FUNC_GET_USERDATA: (skip)
 * @fp:	함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 *
 * 함수에 추가적으로 전달할 데이터를 void* 형으로 얻습니다.
 * Vala에서 사용하기 위해 정의 되었습니다.
 *
 * Returns: 함수에 추가적으로 전달할 데이터를 void*형으로 얻습니다.
 */
#define CRANK_VALA_FUNC_GET_USERDATA(fp, userdata)	(userdata)


/**
 * CRANK_VALA_FUNC_JOIN_SPLIT: (skip)
 * @fp: 함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 * @userdata_out: (out): 함수 추가 데이터를 얻기 위한 포인터입니다.
 *
 * 이 매크로는 Vala에서 delegate 형에서 @userdata를 분리하거나 합치는 역할을
 * 합니다.
 *
 * Returns: @fp입니다.
 */
#define CRANK_VALA_FUNC_JOIN_SPLIT(fp, userdata, userdata_out)	\
		(*(userdata_out)=(userdata), (fp))

/**
 * CRANK_VALA_FUNC_JOIN_SPLIT_OWNED: (skip)
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
#define CRANK_VALA_FUNC_JOIN_SPLIT_OWNED(fp, userdata, destroy, userdata_out, destroy_out)	\
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


#define CRANK_VALA_CLOSURE_NEW(fp, userdata, destroy) (g_cclosure_new (fp, userdata, (GDestroyNotify)destroy))

G_END_DECLS

#endif //CRANKFUNCTION_H
