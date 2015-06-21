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
 * @callback: (scope async): A function to wrap in GClosure.
 * @userdata: (closure): userdata for @callback.
 * @destroy: A function to destroy @userdata.
 * @marshal: (nullable): A #GClosureMarshal to marshal arguments to @callback.
 *
 * Constructs a #GCClosure.
 *
 * In Vala, it is hard to create #GClosure (No binding for #GCClosure and
 * #GClosureMarshal)
 *
 * Therefore, Crank System provides these service until Vala adds its own support
 * for #GClosure.
 *
 * |[ <-- language="Vala" --!>
 *    GLib.Closure closure = Crank.create_closure (
 *        (Crank.Callback) some_func    );
 * ]|
 *
 * Returns: (transfer full): Newly created #GClosure.
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
