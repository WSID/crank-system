/* Copyright (C) 2015, WSID   */

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
