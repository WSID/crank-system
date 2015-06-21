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
 * @title: Vala Support Utility
 * @short_description: Vala Support Utility
 * @stability: Unstable
 * @include: crankbase.h
 *
 * The functions and macros are defined for Vala, to support various features.
 *
 * # Function Utility
 *
 * In Vala, functions are stored with their user data. But user datas are
 * generally hidden from programmers, and it requires some tricks to take out
 * hidden user datas.
 *
 * Crank System provides macros to simplify these tasks.
 *
 * * Gets function pointer and user data from delegate typed variable.
 * * Joining function pointer (has_target=false) and user data into
 *   delegate type (has_target=true).
 * * Spliting function pointer (has_target=false) and user data from
 *   delegate type (has_target=true).
 *
 * Because of limitation of Vala and macro, the returned values should be
 * casted for appropriate type.
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
 * # Generics Utility
 *
 * When generics come into, Vala adds additional hidden arguments. Functions can
 * pick useful properties from it.
 *
 * # Provided functions.
 *
 * Most of provided functions are actually macro. So these may have different
 * name in Vala, and may be multiple functions are bound to same macro.
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
 * @fp:	Function pointer.
 * @userdata: Hidden user data argument for @fp
 *
 * Gets function pointer as #GCallback.
 *
 * |[ <-- language="vala" --!>
 *    GLib.Callback fp = Crank.func_get_pointer ((Crank.Callback)some_func);
 * ]|
 *
 * Returns: (type GCallback): Function pointer
 */
#define CRANK_VALA_FUNC_GET_POINTER(fp, userdata)	((GCallback)(fp))

/**
 * CRANK_VALA_FUNC_GET_USERDATA: (skip)
 * @fp:	Function pointer.
 * @userdata: (closure fp): Hidden user data argument for @fp
 *
 * Gets user data as (void*)
 *
 * |[ <-- language="vala" --!>
 *    void* userdata = Crank.func_get_userdata ((Crank.Callback)some_func);
 * ]|
 *
 * Returns: user data for @fp.
 */
#define CRANK_VALA_FUNC_GET_USERDATA(fp, userdata)	((void*)(userdata))


/**
 * CRANK_VALA_FUNC_JOIN_SPLIT: (skip)
 * @fp: Function pointer.
 * @userdata: Hidden user data for @fp.
 * @userdata_out: (out): Out for @userdata.
 *
 * This macro is for joining into or splitting @userdata from delegate types.
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
 * Returns: @fp.
 */
#define CRANK_VALA_FUNC_JOIN_SPLIT(fp, userdata, userdata_out)	\
		(*(userdata_out)=(userdata), (fp))

/**
 * CRANK_VALA_FUNC_JOIN_SPLIT_OWNED: (skip)
 * @fp: Function pointer.
 * @userdata: Hidden user data for @fp.
 * @destroy: Function to destroy @userdata.
 * @userdata_out: (out): Out for @userdata.
 * @destroy_out: (out): Out for @destroy.
 *
 * This macro is for joining into or splitting @userdata from delegate types.
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
 * @t: A hidden generic parameter #GType.
 * @copy: A hidden copy function.
 * @destroy: A hidden destroy function.
 *
 * This macro determine generic type is owned or unowned by checking @copy
 * function.
 *
 * |[ <-- language="vala" --!>
 *    assert ( Crank.generic_unowned <unowned string> () );
 *    assert ( ! Crank.generic_unowned <string> () );
 *    assert ( Crank.generic_unowned <int> () );
 * ]|
 *
 * Returns: %TRUE if generic type is unowned (no transfer ownership).
 */
#define CRANK_VALA_GENERIC_UNOWNED(t, copy, destroy) (copy == NULL)


GClosure*		crank_vala_create_closure (	CrankCallback	callback,
											gpointer		userdata,
											GDestroyNotify	destroy,
											GClosureMarshal	marshal);

G_END_DECLS

#endif //CRANKFUNCTION_H
