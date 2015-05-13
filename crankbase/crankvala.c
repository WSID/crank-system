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
#include "crankvala.h"

/**
 * crank_vala_create_closure: (skip)
 * @callback: GClosure로 포장할 함수입니다.
 * @userdata: 추가적으로 사용할 데이터입니다.
 * @destroy: @userdata를 해제할 함수입니다.
 * @marshal: (nullable): @callback을 호출할 때 사용할 GClosureMarshal입니다.
 *
 * #GClosure를 생성합니다.
 *
 * Vala에서는 #GClosure를 생성하기 힘들 수 있습니다. (#GCClosure에 대한 접근이
 * 불가능함, #GClosureMarshal 함수들이 보이지 않음 등)
 *
 * 따라서 Crank System은 관려 기능이 언어에 추가되기 전까진, 함수를 지원합니다.
 *
 * |[ <-- language="vala" --!>
 *    GLib.Closure closure = Crank.create_closure (
 *        (Crank.Callback) some_func    );
 * ]|
 *
 * Returns: (transfer full): 새로 생성된 #GClosure입니다.
 */
GClosure*
crank_vala_create_closure (	CrankCallback	callback,
							gpointer		userdata,
							GDestroyNotify	destroy,
							GClosureMarshal	marshal)
{
	GClosure*	closure = g_cclosure_new (
			(GCallback) callback,
			userdata,
			(GClosureNotify) destroy	);
	
	marshal = g_cclosure_marshal_generic;
	g_closure_set_marshal (closure, marshal);
	
	return closure;
}
