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

#include <glib.h>
#include <glib-object.h>

#include "crankfuncholder.h"

/**
 * SECTION:crankvala
 * @title: Vala 지원 유틸리티
 * @short_description: Vala 지원 유틸리티 모음.
 * @stability: Unstable
 * @include: crankbase.h
 *
 * 이 함수들과 매크로들은 Vala에서 C 중심적인 함수들을 사용할 수 있도록 보조하는
 * 역할을 합니다.
 *
 * # 함수 유틸리티
 *
 * Vala에서는 함수를 userdata와 묶어서 저장합니다. 그러나 이 userdata는 숨겨저
 * 있으며, 프로그래머가 Vala내에서 임의로 빼오는 것은 여러 트릭 등을 사용해야
 * 합니다.
 *
 * 이러한 작업을 단순화하기 위해 여러 매크로를 제공하고 있습니다.
 *
 * * delegate형 변수에서 함수 포인터와 데이터를 조회
 * * has_target=false인 delegate형과 userdata를 has_target=true인 delegate형으로
 *   합치기.
 * * has_target=true인 delegate형을 has_target=false인 delegate형과 userdata로
 *   분리
 *
 * 매크로와 Vala의 한계로 인하여, 이러한 함수들을 사용할 경우 해당 형으로 수동으로
 * Cast 해야 합니다.
 *
 * |[ <-- language="vala" --!>
 *    delegate int UserOperation (int a, int b);
 *    delegate int UserOperationR (int a, int b, void* userdata);
 *
 *    ....
 *    public int my_operation (int a, int b, void* userdata) {
 *        int c = (int) userdata;
 *        return a * b + c;
 *    }
 *
 *    ....
 *    public void do_something () {
 *        ....
 *        UserOperation op = (UserOperation) Crank.func_join (
 *                (GLib.Callback) my_operation, (void*) 32);
 *    }
 * ]|
 *
 * # 제네릭스 유틸리티
 *
 * Vala에서는 제네릭스를 처리할 때, 제네릭스 처리를 위한 추가 인자를 첨부합니다.
 * 이때, 이 함수들은 이 인자들에 작용하여 유용한 값을 얻을 수 있습니다.
 *
 * # 제공되는 함수들
 *
 * 제공되는 함수들은 대부분 매크로입니다. 따라서 Vala에서는 이름이 다를 수
 * 있으며, 경우에 따라서는 같은 매크로에 여러 함수가 묶여 있을 수 있습니다.
 *
 * |[ <-- language="vala" --!>
 *    namespace Crank {
 *        public GLib.Callback	func_get_pointer (	Crank.Callback  pointer	);
 *				// CRANK_VALA_FUNC_GET_POINTER
 *
 *        public void*			func_get_userdata (	Crank.Callback	pointer	);
 *				// CRANK_VALA_FUNC_GET_USERDATA
 *
 *
 *        public unowned Crank.Callback	func_join (	GLib.Callback	cb,
 * 													void*			userdata );
 *				// CRANK_VALA_FUNC_JOIN_SPLIT
 *
 *        public GLib.Callback			func_split (Crank.Callback	cb,
 * 													out void*		userdata );
 *				// CRANK_VALA_FUNC_JOIN_SPLIT
 *
 *        public Crank.Callback	func_join_owned (	GLib.Callback	fp,
 * 													void*			userdata,
 * 													GLib.DestroyNotify destroy);
 * 				// CRANK_VALA_FUNC_JOIN_SPLIT_OWNED
 *
 *        public GLib.Callback  func_split_owned (	Crank.Callback	cb,
 * 													out void*		userdata,
 * 													out GLib.DestroyNotify	destroy);
 * 				// CRANK_VALA_FUNC_JOIN_SPLIT_OWNED
 *
 *        public bool generic_unowned <G> ();
 * 				// CRANK_VALA_GENERIC_UNOWNED
 *
 *
 *        public GLib.Closure	create_closure (	owned Crank.Callback callback,
 *													GLib.ClosureMarshal? marshal=null	);
 *				// crank_vala_create_closure
 *
 *        public void			closure_invoke (	GLib.Closure 	closure,
 * 		                                            ref GLib.Value	return_value,
 *		                                            GLib.Value[]	param_types,
 * 		                                            void*			invocation_hint = null	);
 *    }
 * ]|
 */

G_BEGIN_DECLS

/**
 * CRANK_VALA_FUNC_GET_POINTER: (skip)
 * @fp:	함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 *
 * 함수 포인터를 #GCallback으로 얻습니다.
 *
 * |[ <-- language="vala" --!>
 *    GLib.Callback fp = Crank.func_get_pointer ((Crank.Callback)some_func);
 * ]|
 *
 * Returns: (type GCallback): 함수 포인터를 #GCallback으로 얻습니다.
 */
#define CRANK_VALA_FUNC_GET_POINTER(fp, userdata)	((GCallback)(fp))

/**
 * CRANK_VALA_FUNC_GET_USERDATA: (skip)
 * @fp:	함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 *
 * 함수에 추가적으로 전달할 데이터를 void* 형으로 얻습니다.
 *
 * |[ <-- language="vala" --!>
 *    void* userdata = Crank.func_get_userdata ((Crank.Callback)some_func);
 * ]|
 *
 * Returns: 함수에 추가적으로 전달할 데이터를 void*형으로 얻습니다.
 */
#define CRANK_VALA_FUNC_GET_USERDATA(fp, userdata)	((void*)(userdata))


/**
 * CRANK_VALA_FUNC_JOIN_SPLIT: (skip)
 * @fp: 함수 포인터입니다.
 * @userdata: 함수에 추가적으로 전달할 데이터입니다.
 * @userdata_out: (out): 함수 추가 데이터를 얻기 위한 포인터입니다.
 *
 * 이 매크로는 delegate 형에서 @userdata를 분리하거나 합칩니다.
 *
 * |[ <-- language="vala" --!>
 *    UserOperation op = (UserOperation) Crank.func_join (
 *            (GLib.Callback)op_raw, userdata);
 *
 *    void* raw_userdata;
 *    UserOperationR raw = (UserOperationR) Crank.func_split (
 *            (Crank.Callback)op, out raw_userdata);
 * ]|
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
 * 이 매크로는 delegate 형에서 @userdata를 분리하거나 합칩니다.
 *
 * |[ <-- language="vala" --!>
 *    UserOperation op = (owned) (UserOperation) Crank.func_join_owned (
 *            (GLib.Callback)op_raw, userdata, GLib.free);
 *
 *    void* raw_userdata;
 *    UserOperationR raw = (UserOperationR) Crank.func_split (
 *            (owned)(Crank.Callback)op, out raw_userdata, out userdata_destroy);
 * ]|
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
 *
 * |[ <-- language="vala" --!>
 *    assert ( Crank.generic_unowned <unowned string> () );
 *    assert ( ! Crank.generic_unowned <string> () );
 *    assert ( Crank.generic_unowned <int> () );
 * ]|
 */
#define CRANK_VALA_GENERIC_UNOWNED(t, copy, destroy) (copy == NULL)


GClosure*		crank_vala_create_closure (	CrankCallback	callback,
											gpointer		userdata,
											GDestroyNotify	destroy,
											GClosureMarshal	marshal);

G_END_DECLS

#endif //CRANKFUNCTION_H
