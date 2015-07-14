#ifndef CRANKADVMAT_H
#define CRANKADVMAT_H

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

#ifndef _CRANKBASE_INSIDE
#error "crankadvmat.h cannot be included directly."
#endif

#include <glib.h>
#include <glib-object.h>

#include "crankpermutation.h"
#include "crankveccommon.h"
#include "crankmatfloat.h"

G_BEGIN_DECLS

gboolean	crank_lu_mat_float_n (	CrankMatFloatN*	a,
									CrankMatFloatN*	l,
									CrankMatFloatN*	u	);
									
gboolean	crank_lu_p_mat_float_n (	CrankMatFloatN*		a,
										CrankPermutation*	p,
										CrankMatFloatN*		l,
										CrankMatFloatN*		u	);


gboolean	crank_gram_schmidt_mat_float_n (	CrankMatFloatN*	a,
												CrankMatFloatN*	q,
												CrankMatFloatN*	r	);

gboolean	crank_qr_householder_mat_float_n (	CrankMatFloatN*	a,
												CrankMatFloatN*	r	);

gboolean	crank_qr_givens_mat_float_n (	CrankMatFloatN*	a,
											CrankMatFloatN*	r	);

GHashTable*	crank_eval_qr_mat_float_n (	CrankMatFloatN*	a	);

G_END_DECLS

#endif /* CRANKADVMAT_H */
